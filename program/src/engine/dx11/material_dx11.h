#ifndef ENGINE_DX11_MATERIAL_H
#define ENGINE_DX11_MATERIAL_H

#include "../engine_pch.h"
#include "../mesh/material.h"
#include <D3DX11async.h>

class MaterialDx11 : public Material
{
public:
	MaterialDx11();
	virtual ~MaterialDx11();

protected:
	virtual bool DoInit();
	virtual void DoFree();
	virtual void DoApply();
	virtual bool CreateShader();

private:
	ID3D11VertexShader* vertex_shader_;
	ID3D11GeometryShader* geometry_shader_;
	ID3D11PixelShader* pixel_shader_;
	ID3D11InputLayout* input_layout_;
	ID3D11Buffer* matrix_buffer_;
	ID3D11Buffer* light_buffer_;
};


#endif //ENGINE_DX11_MATERIAL_H