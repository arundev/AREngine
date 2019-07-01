#include "scene.h"

#include "../util/assimp_util.h"

namespace engine {

	Scene::Scene(){

	}

	Scene::~Scene(){
		
	}

	bool Scene::Init() {
		if (!Node::Init())
		{
			return false;
		}

		return true;
	}

	void Scene::Free()
	{
		Node::Free();
	}

	void Scene::Update(float elapse)
	{
		Node::Update(elapse);
	}

	void Scene::Render() {
		Node::Render();
	}
}