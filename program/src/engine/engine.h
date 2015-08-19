#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "engine_pch.h"

class Renderer;

class Engine
{
public:
	Engine();
	~Engine();
	
	bool Init(int hInst, HWND hWnd);
	void Update();
	void Free();
};


extern Engine* g_engine;
extern Renderer* g_renderer;

#endif // ENGINE_ENGINE_H
