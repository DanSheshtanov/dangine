#include <Windows.h>

#include "Debug.h"
#include "Window.h"
#include "Renderer.h"
#include "Material.h"

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
            rend.RenderFrame();
        }
    }

    return 0;
}