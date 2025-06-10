#pragma once

#include <Windows.h>

class Window
{
public:
	Window(int width, int hight, HINSTANCE hInstance, int nCmdShow);
	bool Exists() { return handle != NULL; }
private:
	HWND handle = 0;
	HINSTANCE hInst;
	int width = 1, height = 1;

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

