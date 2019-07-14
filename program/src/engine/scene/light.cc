#include "light.h"

namespace engine {
	Light::Light():light_mesh_(nullptr)
	{
		Init(LightType::DirectionalLight);
	}

	Light::Light(LightType type):light_mesh_(nullptr)
	{
		Init(type);
	}

	Light::~Light() {

	}

	bool Light::Init(LightType type)
	{
		Node::Init();

		light_data_.light_type = type;

		switch (light_data_.light_type)
		{
		case LightType::PointLight:
			light_mesh_ = new LightMesh();
			light_mesh_->Init();
			meshes_.push_back(light_mesh_);
			break;
		default:
			break;
		}

		set_enable(true);

		return true;
	}
}