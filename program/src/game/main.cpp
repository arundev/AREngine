#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "win32.h"
#include "engine_include.h"
#include "model_table.h"
#include "model_loader.h"

Mesh* g_test_trangle = NULL;

void TestFbxMesh();

int main(int argc, char *argv[]){
	CreateWnd(800, 600, "hello arun");
	AppInit();
	MsgLoop();
}

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

	// test trangle
	//g_test_trangle = Mesh::CreateTriangle();

	
	//ModelTable model_table;
	std::string path = g_file_util->GetConfigFolder() + "model.csv";
	ModelTable::Instance().Init(path.c_str());
	std::vector<Mesh*> meshes;
	AssimpUtil::LoadFile("models-nonbsd/X/dwarf.x", meshes);
	//AssimpUtil::LoadFile("Male101.FBX", meshes);

	// test fbx import
	//TestFbxMesh();

	g_renderer->SetWireframe(false);
	g_renderer->SetCullMode(Renderer::None);
}

void TestFbxMesh(){
	FbxImporterTool import;
	//if (import.LoadScene("E:\\work\\WorkPlace\\open_source\\AREngine\\program\\bin\\res\\model\\Male101.FBX"))
	std::string full_path = g_file_util->GetModelsFolder() + "/Male101.FBX";
	if (import.LoadScene(full_path.c_str()))
	{
		Mesh* mesh = Mesh::CreateMesh(*import.mesh_data());
	}
	else
	{
		g_log->Write("fail to load scene from fbx file");
	}
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