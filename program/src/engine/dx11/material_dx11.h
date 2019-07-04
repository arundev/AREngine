#ifndef ENGINE_DX11_MATERIAL_H
#define ENGINE_DX11_MATERIAL_H

#include "engine_pch.h"
#include "mesh/material.h"
#include "dx11_include.h"

namespace engine {


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
	virtual bool CreateShader(const std::string& shader);

private:
	void ApplyShader();
	void ApplyEffect();

private:
	ID3D11VertexShader* vertex_shader_ = nullptr;
	ID3D11GeometryShader* geometry_shader_ = nullptr;
	ID3D11PixelShader* pixel_shader_ = nullptr;
	ID3D11InputLayout* shader_input_layout_ = nullptr;
	ID3D11Buffer* matrix_buffer_ = nullptr;

	ID3DX11Effect* effect_ = nullptr;
	ID3DX11EffectTechnique* technique_ = nullptr;
	ID3DX11EffectMatrixVariable* world_view_projection_mat_ = nullptr;
	ID3DX11EffectMatrixVariable* world_mat_ = nullptr;
	ID3DX11EffectMatrixVariable* view_mat_ = nullptr;
	ID3DX11EffectMatrixVariable* proj_mat_ = nullptr;
	ID3DX11EffectShaderResourceVariable* base_texture_srv_ = nullptr;
	ID3D11InputLayout* effect_input_layout_ = nullptr;
	ID3DX11EffectVectorVariable* direction_light_color_ = nullptr;
	ID3DX11EffectVectorVariable* direction_light_direction_ = nullptr;
};


}

#endif //ENGINE_DX11_MATERIAL_H