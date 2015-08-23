#include <stdio.h>
#include <windows.h>

class Engine;
class Mesh;

extern HINSTANCE g_instance;
extern HWND g_wnd;
extern Mesh* g_test_trangle;

extern bool CreateWnd(int width, int height, const char* title);
extern void MsgLoop();
extern LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern void AppInit();
extern void AppUpdate();
extern void AppRender();
extern void AppFree();
