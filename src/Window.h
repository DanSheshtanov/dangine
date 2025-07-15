#pragma once

#include <Windows.h>
#include <Keyboard.h>
#include <Mouse.h>

class Window
{
public:
	Window(int width, int height, HINSTANCE hInstance, int nCmdShow);
	bool Exists() { return handle != NULL; }
	HWND GetHandle() { return handle; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

private:
	HWND handle = 0;
	HINSTANCE hInst;
	int width = 1, height = 1;

	DirectX::Keyboard keyboard;
	DirectX::Mouse mouse;

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

