#include "engine.h"
#include "dx11/renderer_dx11.h"
#include "es2/renderer_es2.h"

Engine* g_engine = 0;
Renderer* g_renderer = 0;

Engine::Engine(){

}

Engine::~Engine(){
	Free();
}

bool Engine::Init(const Renderer::Window& param){
	//g_renderer = new RendererDx11();
	g_renderer = new RendererEs2();
	if (!g_renderer->Init(param)){
		return false;
	}

	return true;
}

void Engine::Update(){
	static int count = 0;
	count++;
	g_renderer->Update();
}

void Engine::Free(){
	g_renderer->Free();
	delete g_renderer;
	g_renderer = 0;
}