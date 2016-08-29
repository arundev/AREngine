#include "Stdafx.h"
#include "scene_wrap.h"
#include "Utils.h"

using namespace mframwork;

bool SceneWrap::Init(){
	g_file_util->SetDataFolder("../../bin/res/");
	g_file_util->SetModelsFolder("model");
	g_file_util->SetScriptsFolder("script");
	g_file_util->SetTextureFolder("texture");
	g_file_util->SetShaderFolder("shader");
	g_file_util->SetConfigFolder("config");

	return true;
}

void SceneWrap::Update(){

}

void SceneWrap::Free(){

}

bool SceneWrap::LoadModel(String^ file_name){
	std::vector<Mesh*> meshes;
	if (!AssimpUtil::LoadFile(Utils::StringToCharArray(file_name), meshes))
	{
		return false;
	}
	
	g_renderer->SetWireframe(false);
	g_renderer->SetCullMode(Renderer::None);

	return true;
}