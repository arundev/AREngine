#pragma once
#include <windows.h>
#include <stdio.h>

class arEngine;

extern HINSTANCE gMainInst;
extern HWND gMainWnd;

// initial win32
bool createWnd(int width, int height, const char* title);

// msg loop
void msgLoop();

// windows procc
LRESULT WINAPI wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

