#ifndef ENGINE_DX11_TEXTURE_H
#define ENGINE_DX11_TEXTURE_H

#include "mesh/texture.h"
#include "dx11_include.h"

namespace engine {

class TextureDx11 : public Texture
{
public:
	TextureDx11();
	virtual ~TextureDx11();

	const ID3D11ShaderResourceView* texture_view()const{ return d3d_texture_view_; }
	const ID3D11SamplerState* sampler_state()const { return texture_samper_state_; }

protected:
	virtual bool DoInit();
	virtual void DoFree();

private:
	ID3D11Texture2D* d3d_texture_;
	ID3D11ShaderResourceView* d3d_texture_view_;
	ID3D11SamplerState* texture_samper_state_;
};


}

#endif // !ENGINE_DX11_TEXTURE_H
