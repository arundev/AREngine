#ifndef ENGINE_MESH_GEOMETRY_H
#define ENGINE_MESH_GEOMETRY_H

#include "../engine_pch.h"
#include "../dx11/renderer_dx11.h"

class Geometry
{
public:
	Geometry();
	~Geometry();

	struct Vertex{
		Vector position;
		Color color;
		float tex_coord_x[1];
		float tex_coord_y[1];
	};

	bool Create(Vertex* vertex_data, int vertex_num, unsigned int* index_data, int index_num);
	void Free();
	void SetDataSteam();
	void Flush();

protected:
	Vertex* vertex_data_;
	unsigned int* index_data_;
	ID3D11Buffer* vertex_buffer_;
	ID3D11Buffer* index_buffer_;
	int vertex_num_;
	int index_num_;
};


#endif // ENGINE_MODEL_GEOMETRY_H