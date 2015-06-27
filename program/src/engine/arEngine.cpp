#include "arEngine.h"

extern arEngine* gEngine = 0;
extern arRenderer* gRenderer = 0;

arEngine::arEngine()
{

}

arEngine::~arEngine()
{

}


bool arEngine::init(int hInst, int hWnd)
{
	gRenderer = new arRenderer();
	if (!gRenderer->init(hInst, hWnd))
	{
		return false;
	}


	return true;
}

void arEngine::update()
{
	static int count = 0;
	count++;
	gRenderer->update();
}

void arEngine::free()
{
	gRenderer->free();
	delete gRenderer;
	gRenderer = 0;

}