#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "renderer.h"

namespace engine {
	class Mesh;
	class Scene;
}

namespace engine {

class Engine {
public:
	Engine();
	~Engine();

	bool Init(const Renderer::Window& param);
	void Update();
	void Render();
	void Free();

	engine::Scene* getCurrentScene()const { return current_scene_; }
	void setCurrentScene(engine::Scene* scene) { current_scene_ = scene; }
	void addOtherMesh(Mesh* mesh);

protected:
	engine::Scene * current_scene_;
	std::vector<Mesh*> other_meshes_;
};

}

#endif // ENGINE_ENGINE_H
