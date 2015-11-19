#ifndef ENGINE_DX11_RENDERER_DX11_H
#define ENGINE_DX11_RENDERER_DX11_H

#include "../renderer.h"
#include "../engine_pch.h"

#pragma comment(lib, "dxgi.lib")  
#pragma comment(lib, "d3d11.lib")  
#pragma comment(lib, "d3dx11.lib")  
#pragma comment(lib, "d3dx10.lib")  
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")

class RendererDx11 : public Renderer{
public:
	RendererDx11();
	~RendererDx11();

	static RendererDx11* Instance();

	virtual void Update();
	virtual void PreRender(const Vector& clear_color);
	virtual void Render();
	virtual void PostRender();
	virtual void Free();

	virtual void SetWireframe(bool b);

	virtual void BeginEvent(const char* event);
	virtual void EndEvent();

	ID3D11Device* device(){ return device_; }
	ID3D11DeviceContext* device_context(){ return device_context_; }
	ID3D11RenderTargetView* render_target_view(){ return render_target_view_; }

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
	D3D11_RASTERIZER_DESC raster_state_desc_;

	int video_card_memory;
	char video_card_description[128];

	ID3D11Debug* debug_;
	ID3DUserDefinedAnnotation* defined_annotation_;
};


#endif // ENGINE_DX11_RENDERER_DX11_H