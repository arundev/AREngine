#include "engine.h"
#include "es2/renderer_es2.h"

extern Engine* g_engine = 0;
extern Renderer* g_renderer = 0;

Engine::Engine()
{

}

Engine::~Engine()
{

}


bool Engine::Init(int hInst, HWND hWnd)
{
	g_renderer = new RendererEs2();
	/*if (!g_renderer->init(hInst, hWnd))
	{
	return false;
	}*/


	return true;
}

void Engine::Update()
{
	static int count = 0;
	count++;
	g_renderer->Update();
}

void Engine::Free()
{
	g_renderer->Free();
	delete g_renderer;
	g_renderer = 0;
}