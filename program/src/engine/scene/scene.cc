#include "scene.h"

#include "../util/assimp_util.h"

namespace engine {

	Scene::Scene(){

	}

	Scene::~Scene(){
		
	}

	Scene* Scene::create(const std::string& path){
		Scene* scene = new Scene();
		if (!scene->LoadFormeFile(path))
		{
			SAFE_FREE(scene);
			return nullptr;
		}
		return scene;
	}
}