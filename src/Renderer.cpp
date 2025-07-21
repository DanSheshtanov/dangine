#include "Renderer.h"

#include <d3d11.h>
#include <algorithm> // std::find()

#include "Window.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Debug.h"
#include "Entity.h"
#include "Time.h"


const UINT cbufferPerFrameIndex = 13;
const UINT cbufferPerObjectIndex = 12;
struct CBuffer_PerFrame
{
    FLOAT time;     // 4 bytes
    XMFLOAT3 packing;
};

struct CBuffer_PerObject
{
    XMMATRIX WVP;   // 64 bytes (4x4 = 16 floats. 16x4 bytes each = 64 bytes total)
};


int Renderer::Init(Window* wnd)
{
	window = wnd;

    HRESULT hr = InitD3D();;
    if (hr != S_OK)
    {
        MessageBox(NULL, L"Failed to initialise Direct3D!", L"Critical Error!", MB_ICONERROR | MB_OK);
        return hr;
    }

    hr = InitDepthBuffer();
    if (hr != S_OK)
    {
        MessageBox(NULL, L"Failed to create depth buffer!", L"Critical Error!", MB_ICONERROR | MB_OK);
        return hr;
    }

    // Set the back buffer as the current render target
    devcon->OMSetRenderTargets(1, &backbuffer, depthBuffer);

#pragma region Stinky CBuffer
    
    D3D11_BUFFER_DESC cbd;
    ZeroMemory(&cbd, sizeof(cbd));
    cbd.Usage = D3D11_USAGE_DEFAULT;
    cbd.ByteWidth = sizeof(CBuffer_PerFrame);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    if (FAILED(dev->CreateBuffer(&cbd, NULL, &cbufferPerFrame)))
    {
        LOG("Oops, failed to create CBuffer.");
        return -1;
    }

    ZeroMemory(&cbd, sizeof(cbd));
    cbd.Usage = D3D11_USAGE_DEFAULT;
    cbd.ByteWidth = sizeof(CBuffer_PerObject);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    if (FAILED(dev->CreateBuffer(&cbd, NULL, &cbufferPerObject)))
    {
        LOG("Oops, failed to create CBuffer.");
        return -1;
    }
#pragma endregion

    return S_OK;
}

// This function will render a single frame
void Renderer::RenderFrame(Camera& cam)
{
    // Clear back buffer with desired colour
    FLOAT bg[4] = { 0.2f, 0.3f, 0.2f, 1.0f };
    devcon->ClearRenderTargetView(backbuffer, bg);
    devcon->ClearDepthStencilView(depthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    // Alternatively, include <DirectXColors.h> and do
    // You can press F12 on the Colors or DarkSlateGray to see a list of all colours
    // Adding a using namespace DirectX will make it less cumbersome to use this
    //g_devcon->ClearRenderTargetView(g_backbuffer, DirectX::Colors::DarkSlateGray);

    XMMATRIX view = cam.GetViewMatrix();
    XMMATRIX proj = cam.GetProjectionMatrix(window->GetWidth(), window->GetHeight());

    // Per frame CBuffer
    CBuffer_PerFrame cbufferPerFrameValues;
    cbufferPerFrameValues.time = Time::GetElapsedTime();
    devcon->UpdateSubresource(cbufferPerFrame, 0, 0, &cbufferPerFrameValues, 0, 0);
    devcon->VSSetConstantBuffers(cbufferPerFrameIndex, 1, &cbufferPerFrame);

    CBuffer_PerObject cBuf1_values;

    for (auto entity : drawnEntities)
    {
        cBuf1_values.WVP = entity->transform.GetWorldMatrix() * view * proj;
        devcon->UpdateSubresource(cbufferPerObject, 0, 0, &cBuf1_values, 0, 0);
        devcon->VSSetConstantBuffers(cbufferPerObjectIndex, 1, &cbufferPerObject);

        (*entity->material)->Bind(devcon);
        (*entity->mesh)->Render();
    }

    // Flip the back and front buffers around. Display on screen
    swapchain->Present(0, 0);
}

void Renderer::RegisterEntity(Entity* e)
{
    drawnEntities.push_back(e);
    LOG("Registered " + e->GetName() + ".");
}

void Renderer::DestroyEntity(Entity* e)
{
    auto foundEntity = std::find(drawnEntities.begin(), drawnEntities.end(), e);
    if (foundEntity != drawnEntities.end())
    {
        drawnEntities.erase(foundEntity);
    }
    // Note: will affect index-based iterating
}

int Renderer::InitD3D()
{
    // Create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC scd = {};
    // Fill the swap chain description struct
    scd.BufferCount = 1;                                // One back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32-bit color
    scd.BufferDesc.Width = window->GetWidth();          // Set the back buffer width
    scd.BufferDesc.Height = window->GetHeight();        // Set the back buffer height
    scd.BufferDesc.RefreshRate.Numerator = 60;          // 60 FPS
    scd.BufferDesc.RefreshRate.Denominator = 1;         // 60/1 = 60 FPS
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // Intended swapchain use
    scd.OutputWindow = window->GetHandle();             // Window to use
    scd.SampleDesc.Count = 1;                           // Number of samples for AA
    scd.Windowed = TRUE;                                // Windowed/full-screen mode
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // Allow full-screen switching

    HRESULT hr;
    // Create a swap chain, device and device context from the scd
    hr = D3D11CreateDeviceAndSwapChain(NULL,// Use default graphics adapter
        D3D_DRIVER_TYPE_HARDWARE,           // Use hardware acceleration, can also use software or WARP renderers
        NULL,                               // Used for software driver types
        D3D11_CREATE_DEVICE_DEBUG,          // Flags can be OR'd together. We are enabling debug for better warnings and errors
        NULL,                               // Direct3D feature levels. NULL will use D3D11.0 or older
        NULL,                               // Size of array passed to above member - NULL since we passed NULL
        D3D11_SDK_VERSION,                  // Always set to D3D11_SDK_VERSION
        &scd,                               // Pointer to our swap chain description
        &swapchain,                         // Pointer to our swap chain COM object
        &dev,                               // Pointer to our device
        NULL,                               // Out param - will be set to chosen feature level
        &devcon);                           // Pointer to our immediate device context

    if (FAILED(hr))
    {
        LOG("Failed to create a Direct3D device.");
        return hr;
    }

    // Get the address of the back buffer
    ID3D11Texture2D* pBackBufferTexture = nullptr;
    // Get the back buffer from the swap chain
    hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBufferTexture);
    if (FAILED(hr)) return hr;

    // Use the back buffer address to create the render target view
    hr = dev->CreateRenderTargetView(pBackBufferTexture, NULL, &backbuffer);
    if (FAILED(hr)) return hr;

    pBackBufferTexture->Release(); // This object is no longer needed

    // Define and set the viewport
    D3D11_VIEWPORT viewport = {};
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = (float)window->GetWidth();
    viewport.Height = (float)window->GetHeight();
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1;
    devcon->RSSetViewports(1, &viewport);

    return S_OK; // The same as 0, aka no error
}

int Renderer::InitDepthBuffer()
{
    HRESULT hr;

    DXGI_SWAP_CHAIN_DESC scd = {};
    swapchain->GetDesc(&scd);

    // Z-Buffer texture description
    D3D11_TEXTURE2D_DESC tex2dDesc = { 0 };
    tex2dDesc.Width = window->GetWidth();
    tex2dDesc.Height = window->GetHeight();
    tex2dDesc.ArraySize = 1;
    tex2dDesc.MipLevels = 1;
    tex2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    tex2dDesc.SampleDesc.Count = scd.SampleDesc.Count; // Same sample count as swap chain
    tex2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    tex2dDesc.Usage = D3D11_USAGE_DEFAULT;

    // Z-Buffer texure
    ID3D11Texture2D* zBufferTexture;
    hr = dev->CreateTexture2D(&tex2dDesc, NULL, &zBufferTexture);
    if (FAILED(hr))
    {
        OutputDebugString(L"Failed to create Z-Buffer Texture!");
        return E_FAIL;
    }

    // Create the depth buffer view
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
    ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
    dsvDesc.Format = tex2dDesc.Format;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    hr = dev->CreateDepthStencilView(zBufferTexture, &dsvDesc, &depthBuffer);
    if (FAILED(hr))
    {
        OutputDebugString(L"Failed to create depth stencil view!");
        return E_FAIL;
    }
    zBufferTexture->Release();

    return S_OK;
}

void Renderer::CleanD3D()
{
    if (backbuffer) backbuffer->Release();
    if (swapchain)  swapchain->Release();
    if (dev)        dev->Release();
    if (devcon)     devcon->Release();
}
