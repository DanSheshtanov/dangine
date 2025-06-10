#pragma once
#include <d3d11.h>

class Window;

//class IDXGISwapChain;
//class ID3D11Device;
//class ID3D11DeviceContext;

class Renderer
{
public:
	void Init(Window* wnd);

private:
	Window* window;

	IDXGISwapChain* swapchain = NULL; // the pointer to the swap chain interface
	ID3D11Device* dev = NULL; // the pointer to our Direct3D device interface
	ID3D11DeviceContext* devcon = NULL; // the pointer to our Direct3D device context

	void InitD3D();
};

