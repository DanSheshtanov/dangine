#pragma once
#include <vector>

#include "Lighting.h"

class Window;

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11Buffer;
struct ID3D11DepthStencilView;
struct ID3D11DepthStencilState;
struct ID3D11RasterizerState;

class Camera;
class Entity;

class Renderer
{
public:
	int Init(Window* wnd);
	void RenderFrame(Camera& cam);

	ID3D11Device* GetDevice() { return dev; }
	ID3D11DeviceContext* GetDeviceCon() { return devcon; }

	/// <summary>
	/// Get point lights array of size MAX_POINT_LIGHTS macro.
	/// </summary>
	/// <returns>Pointer to an array of point lights.</returns>
	PointLight* GetPointLights() { return pointLights; }
	DirectionalLight& GetDirectionalLight() { return dirLight; }
	DirectX::XMVECTOR GetAmbientLight() { return ambientLight; }

	void RegisterEntity(Entity* e);
	void DestroyEntity(Entity* e);

	void SetSkybox(Entity* e);

private:
	Window* window;

	IDXGISwapChain* swapchain = NULL; // the pointer to the swap chain interface
	ID3D11Device* dev = NULL; // the pointer to our Direct3D device interface
	ID3D11DeviceContext* devcon = NULL; // the pointer to our Direct3D device context
	ID3D11RenderTargetView* backbuffer = NULL; // a view to access our back buffer
	ID3D11DepthStencilView* depthBuffer = NULL; // the pointer to our depth buffer

	ID3D11RasterizerState* rasterSolid = NULL;
	ID3D11RasterizerState* rasterSkybox = NULL;
	ID3D11DepthStencilState* depthWriteSolid = NULL;
	ID3D11DepthStencilState* depthWriteSkybox = NULL;

	ID3D11Buffer* cbufferPerFrame = NULL;
	ID3D11Buffer* cbufferPerObject = NULL;

	std::vector<Entity*> drawnEntities;
	Entity* skybox = nullptr;
	DirectX::XMVECTOR ambientLight{ 0.2f, 0.2f, 0.2f, 1 };
	DirectionalLight dirLight;
	PointLight pointLights[MAX_POINT_LIGHTS];

	int InitD3D();
	int InitDepthBuffer();
	void DrawSkybox(Camera& cam);
	void CleanD3D();
};

