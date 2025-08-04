#include "Mesh.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include "ModelLoader.h"
#include "Debug.h"

using namespace DirectX;

struct Vertex
{
    XMFLOAT3 Pos;
    XMFLOAT4 Color;
};

Mesh::Mesh(ID3D11Device* dev, ID3D11DeviceContext* devcon, std::string objPath)
    : dev(dev), devcon(devcon)
{
    ModelLoader ml{ objPath };

    // Create the vertex buffer
    D3D11_BUFFER_DESC bd = { 0 };
    bd.Usage = D3D11_USAGE_DYNAMIC; // Dynamic allows CPU-write and GPU-read
    bd.ByteWidth = (unsigned int)ml.GetVertexBufferSize(); // Size of buffer - sizeof vertex * num of vertices
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
    //memcpy(ms.pData, vertices, sizeof(vertices)); // Copy the data to the buffer
    memcpy(ms.pData, ml.GetVertexData(), ml.GetVertexBufferSize()); // Copy the data to the buffer
    devcon->Unmap(vBuffer, NULL); // Unmap the buffer

    D3D11_BUFFER_DESC indexBD = { 0 };
    indexBD.Usage = D3D11_USAGE_DEFAULT;
    indexBD.ByteWidth = (int)ml.GetIndexBufferSize();
    indexBD.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = { 0 };
    initData.pSysMem = ml.GetIndexData();

    indexCount = (int)ml.GetIndexCount();

    if (FAILED(dev->CreateBuffer(&indexBD, &initData, &iBuffer)))
    {
        LOG("Failed to create index buffer.");
        return;
    }
}

Mesh::Mesh(ID3D11Device* dev, ID3D11DeviceContext* devcon)
{
    //Vertex vertices[] =
    //{
    //    { XMFLOAT3{-0.5f, -0.5f, 0.0f}, XMFLOAT4{Colors::Red} },
    //    { XMFLOAT3{ 0.0f,  0.5f, 0.0f}, XMFLOAT4{Colors::Lime}},
    //    { XMFLOAT3{ 0.5f, -0.5f, 0.0f}, XMFLOAT4{Colors::Blue}},
    //};

    /*Vertex vertices[] =
    {
        { ml.temp_vertices[0], XMFLOAT4{Colors::Red} },
        { ml.temp_vertices[1], XMFLOAT4{Colors::Lime} },
        { ml.temp_vertices[2], XMFLOAT4{Colors::Blue} },
        { ml.temp_vertices[3], XMFLOAT4{Colors::Red} },
        { ml.temp_vertices[4], XMFLOAT4{Colors::Lime} },
        { ml.temp_vertices[5], XMFLOAT4{Colors::Red} },
        { ml.temp_vertices[6], XMFLOAT4{Colors::Blue} },
        { ml.temp_vertices[7], XMFLOAT4{Colors::Red} },
    };*/
}

void Mesh::Render()
{
    // Select which primtive we are using
    devcon->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Select which vertex buffer to use
    UINT stride = sizeof(VertexPosUVNorm);
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);

    devcon->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R32_UINT, 0);
    
    devcon->DrawIndexed(indexCount, 0, 0);
}
