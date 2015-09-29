#include "engine.h"
#include "dx11/renderer_dx11.h"
#include "es2/renderer_es2.h"
#include "mesh/mesh.h"
#include "camera/camera.h"

Engine* g_engine = 0;
Renderer* g_renderer = 0;
BaseCamera* g_camera = 0;

extern Mesh* g_test_trangle;

Engine::Engine(){

}

Engine::~Engine(){
	Free();
}

bool Engine::Init(const Renderer::Window& param){
	g_renderer = new RendererDx11();
	//g_renderer = new RendererEs2();
	if (!g_renderer->Init(param)){
		return false;
	}

	g_camera = new FreeCamera();
	g_camera->SetPos(Vector(0.0f, 0.0f, -5.0f));

	return true;
}

void Engine::Update(){
	g_camera->Update();
	g_renderer->Update();
}

void Engine::Render(){
	Vector clear_color(0, 0, 0);
	g_renderer->PreRender(clear_color);

	std::vector<Mesh*>::const_iterator iter = Mesh::s_mesh_list.begin();
	for (; iter != Mesh::s_mesh_list.end(); iter++)
	{
		(*iter)->Render();
	}

	g_renderer->PostRender();
}



void Engine::Free(){

	std::vector<Mesh*>::iterator iter = Mesh::s_mesh_list.begin();
	for(; iter != Mesh::s_mesh_list.end(); iter++)
	{
		(*iter)->Free();
	}

	SAFE_FREE(g_renderer);
}