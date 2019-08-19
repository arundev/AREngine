#include "../engine_pch.h"
#include "scene.h"
#include "util/assimp_util.h"
#include "renderer.h"

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

		ambient_light_ = { 0.2f, 0.4f, 0.2f, 1.0f };
		g_renderer->set_ambient_light(ambient_light_);

		Light* direction_light = new Light();
		direction_light->set_light_type(DirectionalLight);
		direction_light->set_direction(Vector(-1.0f, -1.0f, -1.0f, 1.0f));
		direction_light->set_color(Color(0.9f, 0.2f, 0.2f));
		direction_light->set_enable(1);
		AddLight(direction_light);
		
		Light* point_light1 = new Light(LightType::PointLight);
		point_light1->set_color(Color(0.2f, 0.5f, 0.2f));
		point_light1->set_constant_attenuation(1.0f);
		point_light1->set_linear_attenuation(0.08f);
		point_light1->set_quadratic_attenuation(0.0f);
		point_light1->set_translate(Vector(-20.0f, 20.0f, 0.0f));
		AddLight(point_light1);
		
		Light* point_light2 = new Light(LightType::PointLight);
		point_light2->set_color(Color(0.2f, 0.2f, 0.5f));
		point_light2->set_constant_attenuation(0.5f);
		point_light2->set_linear_attenuation(0.08f);
		point_light2->set_quadratic_attenuation(0.0f);
		point_light2->set_translate(Vector(-20.0f, 10.0f, 0.0f));
		AddLight(point_light2);

		return true;
	}

	void Scene::AddLight(const Light* light)
	{
		if (!light)
		{
			return;
		}

		Light* un_const = const_cast<Light*>(light);
		AddChild(un_const);
		light_list_.push_back(const_cast<Light*>(un_const));
	}

	void Scene::Free()
	{
		Node::Free();
	}

	void Scene::Update(float elapse)
	{
		Node::Update(elapse);

		std::vector<LightData*> light_data_list;
		for ( auto light : light_list_)
		{
			light_data_list.push_back(light->light_data_ptr());
		}
		g_renderer->set_light_list(light_data_list);
	}

	void Scene::Render() {
		Node::Render();
	}
}