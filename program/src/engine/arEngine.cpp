#include "AREngine.h"

#include "es2/ARRendererEs2.h"

extern AREngine* gEngine = 0;
extern ARRenderer* gRenderer = 0;

AREngine::AREngine()
{

}

AREngine::~AREngine()
{

}


bool AREngine::init(int hInst, int hWnd)
{
	gRenderer = new ARRenderEs2();
	if (!gRenderer->init(hInst, hWnd))
	{
		return false;
	}


	return true;
}

void AREngine::update()
{
	static int count = 0;
	count++;
	gRenderer->update();
}

void AREngine::free()
{
	gRenderer->free();
	delete gRenderer;
	gRenderer = 0;

}