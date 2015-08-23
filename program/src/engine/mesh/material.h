#ifndef ENGINE_MODEL_MATERIAL_H
#define ENGINE_MODEL_MATERIAL_H

#include "../math/math.h"
#include "../dx11/renderer_dx11.h"

class Material
{
public:
	Material();
	~Material();

	struct MatrixBuffer
	{
		Matrix world_;
		Matrix view_;
		Matrix projection_;
	};

	bool Create();
	bool SetShader(const char* vs = NULL, const char* gs = NULL, const char* ps = NULL);
	void Free();
	void Apply();

protected:
	ID3D11VertexShader* vertex_shader_;
	ID3D11GeometryShader* geometry_shader_;
	ID3D11PixelShader* pixel_shader_;
	ID3D11InputLayout* input_layout_;
	ID3D11Buffer* matrix_buffer_;
};


#endif // !ENGINE_MODEL_MATERIAL_H
