#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include <windows.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	enum EType
	{

	};

	virtual bool Init(int hInst, HWND hWnd) = 0;
	virtual void Update() = 0;
	virtual void Free() = 0;

private:

};

#endif // !ENGINE_RENDERER_H
