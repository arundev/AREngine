#include "scene.h"

#include "util/assimp_util.h"

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

		direction_light_ = new Light();
		direction_light_->set_light_type(DirectionalLight);
		direction_light_->set_direction(Vector(-1.0f, -1.0f, -1.0f, 1.0f));
		direction_light_->set_color(Color(1.0f, 0.0f, 0.0f));
		direction_light_->set_enable(1);

		return true;
	}

	void Scene::Free()
	{
		Node::Free();

		SAFE_DELETE(direction_light_);
	}

	void Scene::Update(float elapse)
	{
		Node::Update(elapse);
	}

	void Scene::Render() {
		Node::Render();
	}
}