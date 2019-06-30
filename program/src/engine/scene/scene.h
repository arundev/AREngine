#ifndef ENGINE_SCENE_SCENE_H
#define ENGINE_SCENE_SCENE_H

#include "../engine_pch.h"
#include "node.h"


namespace engine {

	class Mesh;
	class BaseCamera;

	class Scene : public engine::Node
	{
	public:
		Scene();
		~Scene();

		static Scene* create(const std::string& path);

	protected:
		bool Init(const std::string& path);
	protected:
	};
}

#endif // !ENGINE_SCENE_SCENE_H
