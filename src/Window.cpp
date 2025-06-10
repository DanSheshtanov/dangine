#include "Window.h"
#include "Debug.h"

const wchar_t* windowName = L"DirectX Hello World!"; // Wide char array


Window::Window(int width, int hight, HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store our app handle (app memory location)

    // First we need to register our window class.
    // This is how windows stores properties for windows that we want to create.
    WNDCLASSEX wc = {}; // "= {}" sets all values to 0. Can also be achieved with "ZeroMemory(&wc, sizeof(WNDCLASSEX))" macro
    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc; // Our window procedure function, make sure it handles window creation or calls DefWindowProc(..)
    wc.hInstance = hInst;
    wc.lpszClassName = L"WindowClass1";
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW; // Background colour of the win32 app (not needed for D3D apps)
    // Register class with above struct. If it fails, if block will execute
    if (!RegisterClassEx(&wc))
    {
        //return E_FAIL; // Return fail code to be picked up by FAILED(..) macro
        LOG("Failed to register window!");
        MessageBox(NULL, L"Failed to register window!", L"Critical Error!", MB_ICONERROR | MB_OK);
        return;
    }

    // Adjust the window dimensions so that the top windows bar is not taking pixels away from our app
    RECT wr = { 0, 0, 640, 480 };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    // Create the window and use the result as the handle
    handle = CreateWindowEx(NULL,
        L"WindowClass1",    // Name of our window class
        windowName,   // Title of the window
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, // Window style with no resizing and maxmimising
        //WS_OVERLAPPEDWINDOW,    // Alternative window style that allows resizing
        100,    // x-position of the window
        100,    // y-position of the window
        wr.right - wr.left,    // Width of the window
        wr.bottom - wr.top,    // Height of the window
        NULL,    // No parent window, NULL
        NULL,    // No menus, NULL
        hInst,    // Application handle
        NULL);    // Used with multiple windows, NULL

    if (handle != NULL)
    {
        // Display the window on the screen
        ShowWindow(handle, nCmdShow);
    }
    else
    {
        //TOOD GetLastError proper error handling
        LOG("Failed to create window!");
        MessageBox(NULL, L"Failed to create window", L"Critical Error!", MB_ICONERROR | MB_OK);
    }


}

LRESULT Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        // This message is sent when the user closes the window
        // Depending on your handling of your application windows, you may not need this.
        // In this case, if a window is destroyed (e.g. when escape is pressed below), we
        // also tell the application to quit entirely by posting a quit message.
    case WM_DESTROY:
    {
        // Send a quit message to the app
        PostQuitMessage(0);
        return 0;
    }

    // Key being pressed down events
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            DestroyWindow(hWnd); // Note! Destroying the window is not the same as closing the app
            // Destroying the window will post a WM_DESTROY which will lead to
            // PostQuitMessage(0) being called.
            break;
        case 'W':
            // W key was pressed
            break;
        }

    default:
        // Let windows handle everything else with default handling
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
