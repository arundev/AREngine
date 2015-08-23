#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "engine_pch.h"
#include "renderer.h"

class Engine{
public:
	Engine();
	~Engine();

	bool Init(const Renderer::Window& param);
	void Update();
	void Free();
};

#endif // ENGINE_ENGINE_H
