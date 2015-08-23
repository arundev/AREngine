#ifndef ENGINE_MODEL_MATERIAL_H
#define ENGINE_MODEL_MATERIAL_H

#include "../math/math.h"
#include "../dx11/renderer_dx11.h"

class Material
{
public:
	Material();
	~Material();

	bool Create(const char* vs, const char* gs, const char* ps);
	void Free();
	void Apply();

protected:
	ID3D11VertexShader* vertex_shader_;
	ID3D11GeometryShader* geometry_shader_;
	ID3D11PixelShader* pixel_shader_;
};


#endif // !ENGINE_MODEL_MATERIAL_H
