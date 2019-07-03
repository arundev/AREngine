#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "win32.h"
#include "engine_include.h"
#include "model_table.h"
#include "model_loader.h"

using namespace engine;

int main(int argc, char *argv[]){
	CreateWnd(800, 600, "hello arun");
	AppInit();
	MsgLoop();
}

void AppInit(){
	g_engine = new engine::Engine();
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

	/*
		test polygon
	*/
	//auto mesh = engine::Mesh::CreateTriangle();
	//g_engine->addOtherMesh(mesh);

	/*
		test model
	*/
	//ModelTable model_table;
	std::string path = g_file_util->GetConfigFolder() + "model.csv";
	ModelTable::Instance().Init(path.c_str());
	std::vector<engine::Mesh*> meshes;
	//AssimpUtil::LoadFile("models-nonbsd/FBX/2013_ASCII/pyramob.fbx", meshes);
	//AssimpUtil::LoadFile("models-nonbsd/X/dwarf.x", meshes);
	//AssimpUtil::LoadFile("models-nonbsd/FBX/2013_ASCII/jeep1.fbx", meshes);
	//AssimpUtil::LoadFile("Walker.ms3d", meshes);
	//ModelLoader::Instance().Loader(1003, meshes);



	/*
		test scene
	*/
	//auto scene = engine::Scene::create("models-nonbsd/X/dwarf.x");
	//auto scene = engine::Scene::create("models-nonbsd/FBX/2013_ASCII/jeep1.fbx");

	//std::string filePath = "models-nonbsd/X/dwarf.x";
	std::string filePath = "models-nonbsd/FBX/2013_ASCII/jeep1.fbx";
	//std::string filePath = "crytek-sponza/crytek-sponza/sponza.obj";
	auto root = new engine::Node();
	if (!root->LoadFormeFile(filePath))
	{
		return;
	}
	for (auto& m : meshes)
	{
		Matrix mat;
		mat.Identity();
		float scale = 10.5f;
		//mat.Scaling(scale, scale, scale);
		mat.Translate(20, 0.0f, 40.0f);
		//mat.RotaX(90.0f);
		//mat.RotaY(90.0f);
		mat.RotaZ(90.0f);
		m->SetTransform(mat);

		root->AddMesh(m);
	}

	auto scene = new engine::Scene();
	scene->Init();
	scene->AddChild(root);
	g_engine->setCurrentScene(scene);
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