#pragma once

class Window;

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

class Material;
class Mesh;

class Renderer
{
public:
	void Init(Window* wnd);
	void RenderFrame(Material* mat, Mesh* mesh);
	ID3D11Device* GetDevice() { return dev; }
	ID3D11DeviceContext* GetDeviceCon() { return devcon; }

private:
	Window* window;

	IDXGISwapChain* swapchain = NULL; // the pointer to the swap chain interface
	ID3D11Device* dev = NULL; // the pointer to our Direct3D device interface
	ID3D11DeviceContext* devcon = NULL; // the pointer to our Direct3D device context
	ID3D11RenderTargetView* backbuffer = NULL; // a view to access our back buffer


	int InitD3D();
	int InitPipeline();
	void CleanD3D();
};

