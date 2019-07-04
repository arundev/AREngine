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

		// test light
		Light* point_light1 = new Light(LightType::PointLight);
		light_list_.push_back(point_light1);
		AddChild(point_light1);

		point_light1->set_translate(Vector(-20.0f, 20.0f, 0.0f));

		Light* point_light2 = new Light(LightType::PointLight);
		light_list_.push_back(point_light2);
		AddChild(point_light2);

		point_light2->set_translate(Vector(-20.0f, 10.0f, 0.0f));

		

		return true;
	}

	void Scene::Free()
	{
		Node::Free();

		SAFE_DELETE(direction_light_);
		for (auto light : light_list_)
		{
			SAFE_DELETE(light);
		}
		light_list_.clear();
	}

	void Scene::Update(float elapse)
	{
		Node::Update(elapse);
	}

	void Scene::Render() {
		Node::Render();
	}
}