#include <windows.h>
#include "win32.h"
#include "engine.h"
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include "graphic/camera_data.h"

HINSTANCE g_instance = NULL;
HWND g_wnd = NULL;
POINT g_ptLastPoint;

//namespace engine {
//	class Engine;
//	class Renderer;
//	class FreeCamera;
//}

extern engine::Engine* g_engine;
extern engine::Renderer* g_renderer;
extern engine::FreeCamera* g_camera;

using namespace engine;

bool CreateWnd(int width, int height, const char* title) {
	WNDCLASSEX wndclass = { 0 };
	DWORD    wStyle = 0;
	RECT     windowRect;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = "opengles2.0";
	wndclass.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wndclass)) {
		return FALSE;
	}


	wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

	// Adjust the window rectangle so that the client area has
	// the correct number of pixels
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = width;
	windowRect.bottom = height;
	AdjustWindowRect(&windowRect, wStyle, FALSE);
	g_wnd = CreateWindow(
		"opengles2.0",
		title,
		wStyle,
		500,
		200,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL);


	if (g_wnd == NULL) {
		return false;
	}

	ShowWindow(g_wnd, SW_SHOW);
	SetForegroundWindow(g_wnd);
	SetFocus(g_wnd);

	g_instance = hInstance;

	return true;
}

void MsgLoop() {
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

				AppFree();
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			AppUpdate();
			AppRender();
		}
	}
}

LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT  lRet = 1;

	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		ValidateRect(g_wnd, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CHAR:
		break;
	case WM_LBUTTONDOWN:
	{
		POINT ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_wnd, &ptMouse);
		g_ptLastPoint = ptMouse;
	}
	break;
	case WM_RBUTTONDOWN:
	{
		GetCursorPos(&g_ptLastPoint);
		ScreenToClient(g_wnd, &g_ptLastPoint);
		break;
	}
	case WM_MOUSEMOVE:
	{
		switch (wParam)
		{
		case MK_LBUTTON:
		{

		}
		break;
		case MK_RBUTTON:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			g_camera->SetRotAngleDelta((pt.y - g_ptLastPoint.y) / 150.0f, (pt.x - g_ptLastPoint.x) / 150.0f, 0.0f);
			g_ptLastPoint = pt;
		}
		default:
			break;
		}
		break;
	}
	case WM_KEYDOWN:
	{
		engine::Vector *vcDirc = new engine::Vector();
		engine::Vector *vcUp = new engine::Vector();
		engine::Vector *vcRight = new engine::Vector();
		g_camera->GetDirection(vcDirc, vcUp, vcRight);
		switch (wParam)
		{
		case VK_A:
		{
			g_camera->SetMoveDirection(*vcRight);
			g_camera->SetMoveDelta(-20.0f);

			g_camera->Update();
			engine::Matrix matView;
			g_camera->GetViewMatrix(&matView);
			break;
		}
		case VK_C:
		{
			int cull_state = (int)g_renderer->get_cull_mode();
			cull_state += 1;
			cull_state = cull_state <= 2 ? cull_state : 0;
			g_renderer->set_cull_mode((Renderer::CullMode)cull_state);
		}
		break;
		case VK_F:
		{
			if (g_renderer->get_fill_mode() == Renderer::FillMode::kFillModeSolide) {
				g_renderer->set_fill_mode(Renderer::FillMode::kFillModeWireframe);
			}
			else {
				g_renderer->set_fill_mode(Renderer::FillMode::kFillModeSolide);
			}
		}
		break;
		case VK_D:
		{
			engine::Vector vcPosCamera;
			g_camera->SetMoveDirection(*vcRight);
			g_camera->SetMoveDelta(20.0f);
			g_camera->Update();
			engine::Matrix matView;
			g_camera->GetViewMatrix(&matView);
			break;
		}
		case VK_W:
		{
			g_camera->SetMoveDirection(*vcDirc);
			g_camera->SetMoveDelta(20.0f);

			g_camera->Update();
			engine::Matrix matView;
			g_camera->GetViewMatrix(&matView);
			break;
		}
		case VK_S:
		{
			g_camera->SetMoveDirection(*vcDirc);
			g_camera->SetMoveDelta(-20.0f);

			g_camera->Update();
			engine::Matrix matView;
			g_camera->GetViewMatrix(&matView);
			break;
		}
		case VK_Q:
		{
			g_camera->SetMoveDirection(*vcUp);
			g_camera->SetMoveDelta(20.0f);
			g_camera->Update();
			engine::Matrix matView;
			g_camera->GetViewMatrix(&matView);
			break;
		}
		case VK_E:
		{
			g_camera->SetMoveDirection(*vcUp);
			g_camera->SetMoveDelta(-20.0f);
			g_camera->Update();
			engine::Matrix matView;
			g_camera->GetViewMatrix(&matView);
			break;
		}
		case VK_P: 
		{
			g_renderer->SetWireframe(true);
			break;
		}
		case VK_L:
		{
			g_renderer->SetWireframe(false);
			break;
		}

		default:
			break;
		}
		g_camera->Update();
		engine::Matrix viewMat;
		viewMat.Identity();
		g_camera->GetViewMatrix(&viewMat);
	}
	break;
	default:
		lRet = DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return lRet;
}