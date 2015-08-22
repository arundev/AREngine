#ifndef ENGINE_MESH_GEOMETRY_H
#define ENGINE_MESH_GEOMETRY_H

#include "../engine_pch.h"
#include "../math/math.h"
#include "../dx11/renderer_dx11.h"

using namespace math;

class Geometry
{
public:
	Geometry();
	~Geometry();

	struct Vertex{
		Vector pos;
		Vector color;
	};

	bool Create(Vertex* vertex_data, int vertex_num, int* index_data, int index_num);
	void Free();

protected:
	Vertex* vertex_data_;
	int* index_data_;
	ID3D11Buffer* vertex_buffer_;
	ID3D11Buffer* index_buffer_;
	int vertex_num_;
	int index_num_;
};


#endif // ENGINE_MODEL_GEOMETRY_H