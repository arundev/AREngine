#include <stdio.h>
#include "win32.h"
#include "engine.h"
#include "mesh/mesh.h"
#include "util/assimp_util.h"
#include "util/file_util.h"

#include <windows.h>
#include <mmsystem.h>



Mesh* g_test_trangle = NULL;

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

	//g_test_trangle = Mesh::CreateTriangle();
	std::vector<Mesh*> meshes;
	AssimpUtil::LoadFile("models-nonbsd/FBX/2013_ASCII/duck.fbx", meshes);
		 
}

void AppUpdate(){
	g_engine->Update();
}

void AppRender(){
	g_engine->Render();
}

void AppFree(){
	SAFE_FREE(g_engine);
}