#pragma once
#include "..\ARRenderer.h"

class ARRenderEs2 : public ARRenderer
{
public:
	ARRenderEs2();
	~ARRenderEs2();

	bool init(int hInst, int hWnd);
	void update();
	void free();

private:
};