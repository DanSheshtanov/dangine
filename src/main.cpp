#include <Windows.h>

#include "Debug.h"
#include "Window.h"
#include "Renderer.h"
#include "Material.h"
#include "Mesh.h"
#include "Camera.h"
#include "Time.h"
#include "Entity.h"
#include "ModelLoader.h"


// Program entry point
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{

    //ModelLoader ml;
    //ml.LoadModel("assets/models/cube.obj");

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
    Mesh* mesh1 = new Mesh{ rend.GetDevice(), rend.GetDeviceCon(), "assets/models/monkey.obj"};
    Mesh* mesh2 = new Mesh{ rend.GetDevice(), rend.GetDeviceCon(), "assets/models/cube.obj"};

    // Scene
    Camera cam;
    cam.transform.position = XMVectorSetZ(cam.transform.position, -5);

    Entity e1{ "Monkey", &mesh1, &mat1};
    rend.RegisterEntity(&e1);

    Entity e2{ "Cube", &mesh2, &mat1};
    rend.RegisterEntity(&e2);
    e2.transform.Translate({ 3, 1, 0.5f });

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

            XMVECTOR rotation = XMVectorScale({ 0.1, 0.4, 0.05 }, Time::GetDeltaTime());
            e1.transform.Rotate(rotation);
            e2.transform.Rotate(XMVectorScale(rotation, 2.5f));

            rend.RenderFrame(cam);
        }
    }

    return 0;
}