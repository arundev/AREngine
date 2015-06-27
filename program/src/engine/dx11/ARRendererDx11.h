#pragma once
#include "..\ARRenderer.h"

class ARRenderDx11 : public ARRenderer
{
public:
	ARRenderDx11();
	~ARRenderDx11();

	bool init(int hInst, int hWnd);
	void update();
	void free();

private:
};