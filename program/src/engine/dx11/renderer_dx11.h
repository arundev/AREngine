#ifndef ENGINE_DX11_RENDERER_DX11_H
#define ENGINE_DX11_RENDERER_DX11_H

#include "../renderer.h"
#include "../engine_pch.h"

#pragma comment(lib, "dxgi.lib")  
#pragma comment(lib, "d3d11.lib")  
#pragma comment(lib, "d3dx11.lib")  
#pragma comment(lib, "d3dx10.lib")  

#include <dxgi.h>  
#include <d3dcommon.h>  
#include <d3d11.h>  
#include <d3dx10math.h> 

class RendererDx11 : public Renderer{
public:
	RendererDx11();
	~RendererDx11();

	virtual void Update();
	virtual void Free();

protected:
	virtual bool DoInit();

private:
	void BeginScene(float red, float green, float blue, float alpha);
	void EndScene();

private:
	IDXGISwapChain* swap_chain_;
	ID3D11DeviceContext* device_context_;
	ID3D11Device* device_;
	ID3D11RenderTargetView* render_target_view_;
	ID3D11Texture2D* depth_stencil_buffer_;
	ID3D11DepthStencilState* depth_stencil_state_;
	ID3D11DepthStencilView* depth_stencil_view_;
	ID3D11RasterizerState* raster_state_;
	ID3D11Debug* debug_;
	D3D_FEATURE_LEVEL feature_level_;
	int video_card_memory;
	char video_card_description[128];

	D3DXMATRIX mat_world_;
	D3DXMATRIX mat_projection_;
	D3DXMATRIX mat_ortho_;
};


#endif // ENGINE_DX11_RENDERER_DX11_H