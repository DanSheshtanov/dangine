#pragma once
#include <vector>

class Window;

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11Buffer;
struct ID3D11DepthStencilView;

class Camera;
class Entity;

class Renderer
{
public:
	int Init(Window* wnd);
	void RenderFrame(Camera& cam);

	ID3D11Device* GetDevice() { return dev; }
	ID3D11DeviceContext* GetDeviceCon() { return devcon; }

	void RegisterEntity(Entity* e);
	void DestroyEntity(Entity* e);

private:
	Window* window;

	IDXGISwapChain* swapchain = NULL; // the pointer to the swap chain interface
	ID3D11Device* dev = NULL; // the pointer to our Direct3D device interface
	ID3D11DeviceContext* devcon = NULL; // the pointer to our Direct3D device context
	ID3D11RenderTargetView* backbuffer = NULL; // a view to access our back buffer
	ID3D11DepthStencilView* depthBuffer = NULL; // the pointer to our depth buffer


	ID3D11Buffer* pCBuffer = NULL;

	std::vector<Entity*> drawnEntities;

	int InitD3D();
	int InitDepthBuffer();
	void CleanD3D();
};

