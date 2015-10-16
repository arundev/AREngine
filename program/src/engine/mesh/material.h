#ifndef ENGINE_MODEL_MATERIAL_H
#define ENGINE_MODEL_MATERIAL_H

#include "../engine_pch.h"
#include "RTMath.h"
#include "../dx11/renderer_dx11.h"
#include "texture.h"

class Material
{
public:
	Material();
	~Material();

	struct MatrixBuffer
	{
		RTMath::Matrix world_;
		RTMath::Matrix view_;
		RTMath::Matrix projection_;
	};

	virtual bool Create();
	virtual bool Create(const char* vs, const char* ps);
	bool SetShader(const char* vs = NULL, const char* ps = NULL, const char* gs = NULL);
	bool SetTexture(const char* file_name);
	void Free();
	void Apply();

protected:
	ID3D11VertexShader* vertex_shader_;
	ID3D11GeometryShader* geometry_shader_;
	ID3D11PixelShader* pixel_shader_;
	ID3D11InputLayout* input_layout_;
	ID3D11Buffer* matrix_buffer_;

	Texture* texture_;
	ID3D11SamplerState* texture_samper_state_;
};


#endif // !ENGINE_MODEL_MATERIAL_H
