#include <stdio.h>
#include <windows.h>

class Engine;

extern HINSTANCE g_instance;
extern HWND g_wnd;

bool CreateWnd(int width, int height, const char* title);
void MsgLoop();
LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

