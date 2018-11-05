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

		virtual bool Init();
		virtual void Free();
		virtual void Update(float elapse);
		virtual void Render();

		void getVisibleMeshes(const BaseCamera* camera, std::vector<Mesh*>& meshes);

		std::vector<Mesh*>& meshes() { return meshes_; }
		void AddMesh(Mesh* mesh) { meshes_.push_back(mesh); }

	protected:
		static bool Loader(const std::string& path, std::vector<Mesh*>& result);
		bool Init(const std::string& path);
	protected:
		std::vector<Mesh*> meshes_;
	};
}

#endif // !ENGINE_SCENE_SCENE_H
