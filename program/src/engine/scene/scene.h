#ifndef ENGINE_SCENE_SCENE_H
#define ENGINE_SCENE_SCENE_H

#include "engine_pch.h"
#include "node.h"
#include "light.h"

namespace engine {

	class Mesh;
	class BaseCamera;

	class Scene : public engine::Node
	{
	public:
		Scene();
		~Scene();

		virtual bool Init();
		virtual void Free();
		virtual void Update(float elapse);
		virtual void Render();

		const std::vector<Light*>& light_list()const { return light_list_; }

	protected:
		Color* ambient_light_;
		Light* direction_light_;
		std::vector<Light*> light_list_;
	};
}

#endif // !ENGINE_SCENE_SCENE_H
