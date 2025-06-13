#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include "Debug.h"
#include "Mesh.h"


using namespace DirectX;

struct Vertex
{
    XMFLOAT3 Pos;
    XMFLOAT4 Color;
};

Mesh::Mesh(ID3D11Device* dev, ID3D11DeviceContext* devcon)
    : dev(dev), devcon(devcon)
{
    Vertex vertices[] =
    {
        { XMFLOAT3{-0.5f, -0.5f, 0.0f}, XMFLOAT4{Colors::Red} },
        { XMFLOAT3{ 0.0f,  0.5f, 0.0f}, XMFLOAT4{Colors::Lime}},
        { XMFLOAT3{ 0.5f, -0.5f, 0.0f}, XMFLOAT4{Colors::Blue}},
    };

    //Vertex vertices[] =
    //{
    //    // x     y      z      r      g      b      a
    //    { XMFLOAT3{-0.5f, -0.5f, -0.5f},  XMFLOAT4{1.0f,  0.0f,  0.0f,  1.0f}},  // Front BL
    //    { XMFLOAT3{-0.5f,  0.5f, -0.5f},  XMFLOAT4{0.0f,  1.0f,  0.0f,  1.0f}},  // Front TL
    //    { XMFLOAT3{ 0.5f,  0.5f, -0.5f},  XMFLOAT4{0.0f,  0.0f,  1.0f,  1.0f}},  // Front TR
    //    { XMFLOAT3{ 0.5f, -0.5f, -0.5f},  XMFLOAT4{1.0f,  1.0f,  1.0f,  1.0f}},  // Front BR
    //    { XMFLOAT3{-0.5f, -0.5f,  0.5f},  XMFLOAT4{0.0f,  1.0f,  1.0f,  1.0f}},  // Back BL
    //    { XMFLOAT3{-0.5f,  0.5f,  0.5f},  XMFLOAT4{1.0f,  0.0f,  1.0f,  1.0f}},  // Back TL
    //    { XMFLOAT3{ 0.5f,  0.5f,  0.5f},  XMFLOAT4{1.0f,  1.0f,  0.0f,  1.0f}},  // Back TR
    //    { XMFLOAT3{ 0.5f, -0.5f,  0.5f},  XMFLOAT4{0.0f,  0.0f,  0.0f,  1.0f}},  // Back BR
    //};

    // Create the vertex buffer
    D3D11_BUFFER_DESC bd = { 0 };
    bd.Usage = D3D11_USAGE_DYNAMIC; // Dynamic allows CPU-write and GPU-read
    bd.ByteWidth = sizeof(Vertex) * 3; // Size of buffer - sizeof vertex * num of vertices
    //bd.ByteWidth = sizeof(vertices); // Alternatively can also be this for simplicty
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Use as vertex buffer
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // Allow CPU to write in buffer
    dev->CreateBuffer(&bd, NULL, &vBuffer); // Create the buffer

    if (vBuffer == 0)
    {
        LOG("Failed... this won't fail.");
        return;
    }

    // Copy the vertices into the buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(vBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); // Map the buffer
    memcpy(ms.pData, vertices, sizeof(vertices)); // Copy the data to the buffer
    devcon->Unmap(vBuffer, NULL); // Unmap the buffer
}

void Mesh::Render()
{
    // Select which vertex buffer to use
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);

    // Select which primtive we are using
    devcon->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Draw 3 vertices
    devcon->Draw(3, 0);
}
