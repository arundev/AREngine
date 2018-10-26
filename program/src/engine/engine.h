#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "engine_pch.h"
#include "renderer.h"

namespace engine_scene {
	class Scene;
}

class Mesh;

class Engine{
public:
	Engine();
	~Engine();

	bool Init(const Renderer::Window& param);
	void Update();
	void Render();
	void Free();

	engine_scene::Scene* getCurrentScene()const { return current_scene_; }
	void setCurrentScene(engine_scene::Scene* scene) { current_scene_ = scene; }
	void addOtherMesh(Mesh* mesh);

protected:
	engine_scene::Scene * current_scene_;
	std::vector<Mesh*> other_meshes_;
};

#endif // ENGINE_ENGINE_H
