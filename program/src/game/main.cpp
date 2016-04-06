#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "win32.h"
#include "engine_include.h"
#include "model_table.h"
#include "model_loader.h"

//Mesh* g_test_trangle = NULL;

//int main(int argc, char *argv[]){
//	CreateWnd(800, 600, "hello arun");
//	AppInit();
//	MsgLoop();
//}

void AppInit(){
	g_engine = new Engine();
	Renderer::Window param;
	param.width_ = 800;
	param.height_ = 600;
	param.wnd_ = (int)g_wnd;
	param.instance_ = (int)g_instance;
	g_engine->Init(param);

	g_file_util->SetDataFolder("../../bin/res/");
	g_file_util->SetModelsFolder("model");
	g_file_util->SetScriptsFolder("script");
	g_file_util->SetTextureFolder("texture");
	g_file_util->SetShaderFolder("shader");
	g_file_util->SetConfigFolder("config");

	//ModelTable model_table;
	std::string path = g_file_util->GetConfigFolder() + "model.csv";
	ModelTable::Instance().Init(path.c_str());

	//g_test_trangle = Mesh::CreateTriangle();
	std::vector<Mesh*> meshes;
	//AssimpUtil::LoadFile("models-nonbsd/FBX/2013_ASCII/pyramob.fbx", meshes);

	AssimpUtil::LoadFile("models-nonbsd/X/dwarf.x", meshes);
	//AssimpUtil::LoadFile("Walker.ms3d", meshes);
	//ModelLoader::Instance().Loader(1001, meshes);
}

void AppUpdate(){
	g_engine->Update();
}

void AppRender(){
	g_engine->Render();
}

void AppFree(){
	ModelTable::Instance().Free();
	SAFE_FREE(g_engine);
}