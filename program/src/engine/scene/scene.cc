#include "scene.h"

#include "../util/assimp_util.h"

namespace engine_scene {

	Scene::Scene(){

	}

	Scene::~Scene(){
		
	}

	Scene* Scene::create(const std::string& path){
		Scene* scene = new Scene();
		if (!scene->Init(path)){
			SAFE_FREE(scene);
			return nullptr;
		}
		return scene;
	}

	bool Scene::Init(){
		return true;
	}

	bool Scene::Init(const std::string& path){
		if (!Init()){
			return false;
		}

		Free();

		if (!Loader(path, meshes_)){
			return false;
		}

		return true;
	}

	void Scene::Free(){
		for (auto& mesh : meshes_){
			if (mesh){
				mesh->Free();
				SAFE_DELETE(mesh);
			}
		}
		meshes_.clear();
	}

	void Scene::Update(float elapse){

	}

	void Scene::Render(){

	}

	void Scene::getVisibleMeshes(const BaseCamera* camera, std::vector<Mesh*>& meshes) {
		for (auto& item : meshes_){
			meshes.push_back(item);
		}
	}

	bool Scene::Loader(const std::string& path, std::vector<Mesh*>& result) {
		if (!AssimpUtil::LoadFile(path.c_str(), result)) {
			return false;
		}
		return true;
	}


}