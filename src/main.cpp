#include <Windows.h>

#include "Debug.h"
#include "Time.h"
#include "Window.h"
#include "Renderer.h"
#include "Material.h"
#include "Material_Waves.h"
#include "Mesh.h"
#include "Camera.h"
#include "Entity.h"
#include "ModelLoader.h"
#include "Texture.h"


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
    Texture* texture1 = new Texture{ rend.GetDevice(), rend.GetDeviceCon(), "assets/textures/colormap.png" };
    Material* mat1 = new Material{ "mat1", rend.GetDevice(), "Compiled Shaders/VertexShader.cso", "Compiled Shaders/PixelShader.cso", texture1 };
    Material* mat2 = new Material{ "mat2", rend.GetDevice(), "Compiled Shaders/VertexShader.cso", "Compiled Shaders/PixelShader.cso", texture1 };
    Material_Waves* mat_waves = new Material_Waves{ "Waves", rend.GetDevice(),"Compiled Shaders/VShaderWaves.cso", "Compiled Shaders/PixelShader.cso", texture1 };
    Mesh* mesh1 = new Mesh{ rend.GetDevice(), rend.GetDeviceCon(), "assets/models/sub.obj"};
    Mesh* mesh2 = new Mesh{ rend.GetDevice(), rend.GetDeviceCon(), "assets/models/cube.obj"};

    // Scene
    Camera cam;
    cam.transform.position = XMVectorSetZ(cam.transform.position, -8);

    Entity e1{ "Sub", &mesh1, (Material**)&mat_waves};
    e1.transform.scale = XMVectorSet(10, 10, 10, 1);
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

            XMVECTOR rotation = XMVectorScale({ 0.1f, 0.4f, 0.05f }, Time::GetDeltaTime());
            e2.transform.Rotate(XMVectorScale(rotation, 2.5f));
            
            auto kbState = Keyboard::Get().GetState();
            auto msState = Mouse::Get().GetState();
            if (kbState.W)
                cam.transform.Translate(cam.transform.GetForward() * 5 * Time::GetDeltaTime());
            if (kbState.S)
                cam.transform.Translate(-cam.transform.GetForward() * 5 * Time::GetDeltaTime());
            if(kbState.D)
                cam.transform.Translate(cam.transform.GetRight() * 5 * Time::GetDeltaTime());
            if (kbState.A)
                cam.transform.Translate(-cam.transform.GetRight() * 5 * Time::GetDeltaTime());
            if (kbState.E)
                cam.transform.Translate(cam.transform.GetUp() * 5 * Time::GetDeltaTime());
            if (kbState.Q)
                cam.transform.Translate(-cam.transform.GetUp() * 5 * Time::GetDeltaTime());
            if (msState.leftButton)
                cam.transform.position = XMVectorSet(0, 0, 0, 0);
            cam.transform.Rotate(XMVECTOR{ -(float)msState.y, (float)msState.x } *0.001f);

            rend.RenderFrame(cam);
        }
    }

    return 0;
}