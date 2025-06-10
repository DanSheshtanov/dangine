#include <d3d11.h>

#include "Renderer.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void Renderer::Init()
{

}

//void Renderer::InitD3D()
//{
//    // create a struct to hold information about the swap chain
//    DXGI_SWAP_CHAIN_DESC scd;
//    // clear out the struct for use
//    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
//    // fill the swap chain description struct
//    scd.BufferCount = 1;                                    // one back buffer
//    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
//    scd.BufferDesc.Width = SCREEN_WIDTH;                    // set the back buffer width
//    scd.BufferDesc.Height = SCREEN_HEIGHT;                  // set the back buffer height
//    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
//    scd.OutputWindow = hWnd;                                // the window to be used
//    scd.SampleDesc.Count = 1;                               // how many multisamples
//    scd.Windowed = TRUE;                                    // windowed/full-screen mode
//    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching
//
//    // create a device, device context and swap chain using the information in the scd struct
//    D3D11CreateDeviceAndSwapChain(NULL,
//        D3D_DRIVER_TYPE_HARDWARE,
//        NULL,
//        /*NULL,*/ D3D11_CREATE_DEVICE_DEBUG,
//        NULL,
//        NULL,
//        D3D11_SDK_VERSION,
//        &scd,
//        &swapchain,
//        &dev,
//        NULL,
//        &devcon);
//
//}