#pragma once

class Window;

class IDXGISwapChain;
class ID3D11Device;
class ID3D11DeviceContext;
class ID3D11RenderTargetView;

class Renderer
{
public:
	void Init(Window* wnd);
	void RenderFrame();

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

