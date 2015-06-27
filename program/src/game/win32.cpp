#pragma once

#include <windows.h>
#include "win32.h"
#include "AREngine.h"

extern HINSTANCE gMainInst = NULL;
extern HWND gMainWnd = NULL;

bool createWnd(int width, int height, const char* title)
{
	WNDCLASS wndclass = { 0 };
	DWORD    wStyle = 0;
	RECT     windowRect;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	wndclass.style = CS_OWNDC;
	wndclass.lpfnWndProc = (WNDPROC)wndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = "opengles2.0";

	if (!RegisterClass(&wndclass))
	{
		return false;
	}

	wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

	// Adjust the window rectangle so that the client area has
	// the correct number of pixels
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = width;
	windowRect.bottom = height;

	AdjustWindowRect(&windowRect, wStyle, FALSE);

	gMainWnd = CreateWindow(
		"opengles2.0",
		title,
		wStyle,
		0,
		0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (gMainWnd == NULL)
	{
		return false;
	}

	ShowWindow(gMainWnd, TRUE);
	
	gMainInst = hInstance;

	return true;
}

void msgLoop()
{
	MSG msg = { 0 };
	int done = 0;
	DWORD lastTime = GetTickCount();

	while (!done)
	{
		int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);
		DWORD curTime = GetTickCount();
		float deltaTime = (float)(curTime - lastTime) / 1000.0f;
		lastTime = curTime;

		if (gotMsg)
		{
			if (msg.message == WM_QUIT)
			{
				done = 1;

				gEngine->free();
				delete gEngine;
				gEngine = 0;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			gEngine->update();
		}
	}
}

LRESULT WINAPI wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT  lRet = 1;

	switch (uMsg)
	{
		case WM_CREATE:
			break;
		case WM_PAINT:
		{
			ValidateRect(gMainWnd, NULL);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
		case WM_CHAR:
		{
		}
		break;
		default:
			lRet = DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return lRet;
}