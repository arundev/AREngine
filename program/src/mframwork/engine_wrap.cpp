#include "Stdafx.h"
#include "engine_wrap.h"

using namespace mframwork;

bool EngineWrap::Init(int width, int height, IntPtr ptWnd, IntPtr ptInst){
	
	g_engine = new Engine;
	Renderer::Window* param = new Renderer::Window();
	param->width_ = width;
	param->height_ = height;
	param->wnd_ = (int)ptWnd.ToPointer();
	param->instance_ = (int)ptInst.ToPointer();
	g_engine->Init(*param);

	g_file_util->SetDataFolder("../../bin/res/");
	g_file_util->SetModelsFolder("model");
	g_file_util->SetScriptsFolder("script");
	g_file_util->SetTextureFolder("texture");
	g_file_util->SetShaderFolder("shader");
	g_file_util->SetConfigFolder("config");

	std::vector<Mesh*> meshes;
	AssimpUtil::LoadFile("/nanosuit/nanosuit.obj", meshes);
	g_renderer->SetWireframe(false);
	g_renderer->SetCullMode(Renderer::None);
	
	return true;
}

void EngineWrap::Update(){
	g_engine->Update();
	g_engine->Render();
}

void EngineWrap::Free(){
	g_engine->Free();
}