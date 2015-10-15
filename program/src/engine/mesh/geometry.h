#ifndef ENGINE_MESH_GEOMETRY_H
#define ENGINE_MESH_GEOMETRY_H

#include "../engine_pch.h"
#include "RTMath.h"
#include "../dx11/renderer_dx11.h"

class Geometry
{
public:
	Geometry();
	~Geometry();

	struct Position
	{
		Position(float xx, float yy, float zz)
		{
			x = xx;
			y = yy;
			z = zz;
		}

		Position()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		float x, y, z;
	};

	struct Vertex{
		Position position;
		Color color;
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