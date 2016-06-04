#include "Stdafx.h"
#include "engine_wrap.h"

using namespace mframwork;
POINT* g_ptLastPoint;

bool EngineWrap::Init(int width, int height, IntPtr ptWnd, IntPtr ptInst){
	
	g_engine = new Engine;
	Renderer::Window* param = new Renderer::Window();
	param->width_ = width;
	param->height_ = height;
	param->wnd_ = (int)ptWnd.ToPointer();
	param->instance_ = (int)ptInst.ToPointer();
	g_engine->Init(*param);

	g_ptLastPoint = new POINT();

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

	SAFE_DELETE(g_ptLastPoint);
}

void EngineWrap::OnKeyDown(MKeyCode key){

}

void EngineWrap::OnKeyUp(MKeyCode key){

}

void EngineWrap::OnMouseDown(MKeyCode btn, MVector2^ pos){
	if (btn == MKeyCode::MouseLeft || btn == MKeyCode::MouseRight)
	{
		g_ptLastPoint->x = pos->x;
		g_ptLastPoint->y = pos->y;
	}

	g_camera->Update();
	//Matrix viewMat;
	//viewMat.Identity();
	//g_camera->GetViewMatrix(&viewMat);
}

void EngineWrap::OnMouseUp(MKeyCode btn, MVector2^ pos){
	g_camera->Update();
	//Matrix viewMat;
	//viewMat.Identity();
	//g_camera->GetViewMatrix(&viewMat);
}

void EngineWrap::OnMouseMove(MKeyCode pressBtn, MVector2^ pos){
	if (pressBtn == MKeyCode::MouseRight)
	{
		g_camera->SetRotAngleDelta((pos->y - g_ptLastPoint->y) / 150.0f, (pos->x - g_ptLastPoint->y) / 150.0f, 0.0f);
		g_ptLastPoint->x = pos->x;
		g_ptLastPoint->y = pos->y;
	}

	g_camera->Update();
	//Matrix viewMat;
	//viewMat.Identity();
	//g_camera->GetViewMatrix(&viewMat);
}