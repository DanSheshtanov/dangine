#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer;

class Mesh
{
public:
	Mesh(ID3D11Device* dev, ID3D11DeviceContext* devcon);
	void Render();

private:
	ID3D11Device* dev;
	ID3D11DeviceContext* devcon;
	ID3D11Buffer* vBuffer = NULL; // Vertex buffer
	ID3D11Buffer* iBuffer = NULL; // Index buffer

};

