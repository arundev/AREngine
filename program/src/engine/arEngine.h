#pragma once

#include "arRenderer.h"

// engine manager
class arEngine
{
public:
	arEngine();
	~arEngine();
	
	bool init(int hInst, int hWnd);
	void update();
	void free();
};


// global variables in engine
extern arEngine* gEngine;
extern arRenderer* gRenderer;
