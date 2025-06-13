#include <Windows.h>

#include "Debug.h"
#include "Window.h"
#include "Renderer.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "Time.h"

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
    rend.Init(&wnd);

    Material mat1{ "mat1", rend.GetDevice(), "Compiled Shaders/VertexShader.cso", "Compiled Shaders/PixelShader.cso" };
    Mesh mesh1{ rend.GetDevice(), rend.GetDeviceCon() };

    // Used to hold windows event messages
    MSG msg;

    Transform t;
    t.position = XMVectorSetZ(t.position, 1);
    //t.eulerRotation = XMVectorSetX(t.eulerRotation, XM_PIDIV2);
    //t.Rotate(XMVECTOR{ 0, XM_PIDIV2, 0 });
    XMVECTOR forward = t.GetForward();

    Camera cam;
    float time = 0;

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
            Time::Update();
            // Game code here
            time += Time::GetDeltaTime();
            t.position = XMVectorSetX(t.position, sin(time));
            cam.transform.Translate(XMVECTOR{ 0, 0, 0.1f * Time::GetDeltaTime() });
            LOG(std::to_string(XMVectorGetX(t.position)));
            rend.RenderFrame(cam, &mat1, &mesh1, t);
        }
    }

    return 0;
}