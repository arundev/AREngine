#pragma once
#include "../ARRenderer.h"

#include "../AREnginePCH.h"

class ARRenderDx11 : public ARRenderer
{
public:
	ARRenderDx11();
	~ARRenderDx11();

	bool init(int hInst, int hWnd);
	void update();
	void free();

protected:
	ID3D11Device* mDevice;

};