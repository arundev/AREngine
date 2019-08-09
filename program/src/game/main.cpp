#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "win32.h"
#include "engine_include.h"
#include "model_table.h"
#include "model_loader.h"

using namespace engine;

unsigned int g_wnd_width = 800;
unsigned int g_wnd_height = 600;
TwBar* g_tweak_bar = nullptr;

int main(int argc, char *argv[]){
	CreateWnd(g_wnd_width, g_wnd_height, "hello arun");
	AppInit();
	MsgLoop();
}

void AppInit(HWND hwnd, HINSTANCE inst)
{
	g_engine = new engine::Engine();
	Renderer::Window param;
	param.width_ = g_wnd_width;
	param.height_ = g_wnd_height;
	param.wnd_ = (int)hwnd;
	param.instance_ = (int)inst;
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

	/*
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

	root->set_translate(engine::Vector(10.0f, 0.0f, 0.0f));
	*/

	auto scene = new engine::Scene();
	scene->Init();
	scene->AddChild(root);
	g_engine->setCurrentScene(scene);

	InitGUI();
}

void InitGUI()
{
	g_tweak_bar = TwNewBar("Rendering Technique");
	TwDefine("'Rendering Technique' refresh=0.5");

	TwAddVarRO(g_tweak_bar, "Window Width", TW_TYPE_UINT32, &g_wnd_width, "label='Window Width' help='Window width in pixels.'");
	TwAddVarRO(g_tweak_bar, "Window Height", TW_TYPE_UINT32, &g_wnd_height, "label='Window Height' help='Window height in pixels.'");
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