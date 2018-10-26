#include "engine.h"
#include "dx11/renderer_dx11.h"
#include "es2/renderer_es2.h"
#include "mesh/mesh.h"
#include "camera/camera.h"
#include "util/file_util.h"
#include "scene/scene.h"

#include <assimp/Importer.hpp>
#include <BaseImporter.h>

using namespace engine_scene;

Log* g_log = nullptr;
Engine* g_engine = nullptr;
Renderer* g_renderer = nullptr;
FreeCamera* g_camera = nullptr;
FileUtil* g_file_util = nullptr;

Engine::Engine(){
	Assimp::Importer* pImp = new Assimp::Importer();
}

Engine::~Engine(){
	Free();
}

bool Engine::Init(const Renderer::Window& param){
	Plateform::Init();

	g_log = new Log();
	if (!g_log->Init()){
		return false;
	}

	g_file_util = new FileUtil();
	if (!g_file_util->Init()){
		return false;
	}
	
	if (Plateform::graphic_api() == Plateform::D3D_11){
		g_renderer = new RendererDx11();
	}
	else if (Plateform::graphic_api() == Plateform::GLES_2){
		g_renderer = new RendererEs2();
	}
	
	if (!g_renderer->Init(param)){
		return false;
	}

	g_camera = new FreeCamera();
	g_camera->SetPos(Vector(0.0f, 0.0f, -5.0f));

	return true;
}

void Engine::Update(){
	g_camera->Update();
	if (current_scene_){
		current_scene_->Update(0.0f);
	}
	g_renderer->Update();
}

void Engine::Render(){
	Vector clear_color(0, 0, 0);
	g_renderer->PreRender(clear_color);
	
	std::vector<Mesh*> meshes;
	if (current_scene_){
		current_scene_->getVisibleMeshes(g_camera, meshes);
	}
	for (auto& mesh : meshes){
		if (mesh){
			mesh->Render();
		}
	}
	for (auto&mesh : other_meshes_){
		if (mesh) {
			mesh->Render();
		}
	}

	g_renderer->PostRender();
}



void Engine::Free(){
	for (auto mesh : other_meshes_) {
		SAFE_FREE(mesh);
	}
	other_meshes_.clear();

	SAFE_FREE(current_scene_);
	SAFE_FREE(g_camera);
	SAFE_FREE(g_renderer);
}

void Engine::addOtherMesh(Mesh* mesh) {
	bool exist = false;
	for (auto item : other_meshes_) {
		if (item == mesh){
			exist = true;
			break;
		}
	}

	if (!exist)
	{
		other_meshes_.push_back(mesh);
	}
}