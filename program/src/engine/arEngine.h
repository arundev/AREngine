#pragma once

#include "ARRenderer.h"

// engine manager
class AREngine
{
public:
	AREngine();
	~AREngine();
	
	bool init(int hInst, int hWnd);
	void update();
	void free();
};


// global variables in engine
extern AREngine* gEngine;
extern ARRenderer* gRenderer;
