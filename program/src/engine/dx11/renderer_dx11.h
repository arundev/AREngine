#ifndef ENGINE_DX11_RENDERER_DX11_H
#define ENGINE_DX11_RENDERER_DX11_H

#include "../renderer.h"
#include "../engine_pch.h"

class RendererDx11 : public Renderer
{
public:
	RendererDx11();
	~RendererDx11();

	bool Init(int hInst, int hWnd);
	void Update();
	void Free();

protected:
	ID3D11Device* device_;
	ID3D11Debug* debug_;
	D3D_FEATURE_LEVEL feature_level_;
};

#endif // ENGINE_DX11_RENDERER_DX11_H