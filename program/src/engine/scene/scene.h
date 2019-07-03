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

	protected:
		Color* ambient_light_;
		Light* direction_light_;
	};
}

#endif // !ENGINE_SCENE_SCENE_H
