#include <Windows.h>

#include "Debug.h"
#include "Window.h"
#include "Renderer.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "Time.h"
#include "Entity.h"


// Program entry point
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    Window wnd{ 800, 600, hInstance, nCmdShow };
    if (!wnd.Exists())
    {
        LOG("Failed to create a window, quitting...");
        return -1;
    }

    Renderer rend;
    if (FAILED(rend.Init(&wnd)))
    {
        LOG("Failed to create a renderer, quitting...");
        return -1;
    }

    // Assets
    Material* mat1 = new Material{ "mat1", rend.GetDevice(), "Compiled Shaders/VertexShader.cso", "Compiled Shaders/PixelShader.cso" };
    Mesh* mesh1 = new Mesh{ rend.GetDevice(), rend.GetDeviceCon() };

    // Scene
    Camera cam;
    cam.transform.position = XMVectorSetZ(cam.transform.position, -1);
    Entity e{ "Tringle", &mesh1, &mat1};
    rend.RegisterEntity(&e);

    // Used to hold windows event messages
    MSG msg;

    // Enter the main loop:
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Translate certain messages into correct format, namely key presses
            TranslateMessage(&msg);
            // Send the message to the WindowProc function
            DispatchMessage(&msg);
            // Break out of the loop if a quit message is detected
            if (msg.message == WM_QUIT)
                break;
        }
        else
        {
            // Game code here
            Time::Update();

            cam.transform.Translate(XMVECTOR{ 0, 0, -0.05f * Time::GetDeltaTime()});
            LOG(std::to_string(XMVectorGetZ(cam.transform.position)));

            if (XMVectorGetZ(cam.transform.position) < -1.4)
            {
                rend.DestroyEntity(&e);
            }

            rend.RenderFrame(cam);
        }
    }

    return 0;
}