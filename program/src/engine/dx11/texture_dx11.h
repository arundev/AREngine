#ifndef ENGINE_DX11_TEXTURE_H
#define ENGINE_DX11_TEXTURE_H

#include "../engine_pch.h"
#include "../mesh/texture.h"

class TextureDx11 : public Texture
{
public:
	TextureDx11();
	virtual ~TextureDx11();

	ID3D11ShaderResourceView* texture_view(){ return d3d_texture_view_; }

protected:
	virtual bool DoInit();
	virtual void DoFree();

private:
	ID3D11Texture2D* d3d_texture_;
	ID3D11ShaderResourceView* d3d_texture_view_;
};

#endif // !ENGINE_DX11_TEXTURE_H
