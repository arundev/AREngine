#include "mesh_light.h"

namespace engine
{


struct MeshLightVertex
{
	Vector position;
	Vector normal;
};

LightMesh::LightMesh()
{

}

LightMesh::~LightMesh()
{

}


bool LightMesh::Init()
{
	if (!Mesh::Init())
	{
		return false;
	}

	MeshLightVertex vertices_temp[] =
	{
		{ Vector(-1.0f, 1.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f)},
		{ Vector(1.0f, 1.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f) },
		{ Vector(1.0f, 1.0f, 1.0f), Vector(0.0f, 1.0f, 0.0f) },
		{ Vector(-1.0f, 1.0f, 1.0f), Vector(0.0f, 1.0f, 0.0f) },

		{ Vector(-1.0f, -1.0f, -1.0f), Vector(0.0f, -1.0f, 0.0f) },
		{ Vector(1.0f, -1.0f, -1.0f), Vector(0.0f, -1.0f, 0.0f) },
		{ Vector(1.0f, -1.0f, 1.0f), Vector(0.0f, -1.0f, 0.0f) },
		{ Vector(-1.0f, -1.0f, 1.0f), Vector(0.0f, -1.0f, 0.0f) },

		{ Vector(-1.0f, -1.0f, 1.0f), Vector(-1.0f, 0.0f, 0.0f) },
		{ Vector(-1.0f, -1.0f, -1.0f), Vector(-1.0f, 0.0f, 0.0f) },
		{ Vector(-1.0f, 1.0f, -1.0f), Vector(-1.0f, 0.0f, 0.0f) },
		{ Vector(-1.0f, 1.0f, 1.0f), Vector(-1.0f, 0.0f, 0.0f) },

		{ Vector(1.0f, -1.0f, 1.0f), Vector(1.0f, 0.0f, 0.0f) },
		{ Vector(1.0f, -1.0f, -1.0f), Vector(1.0f, 0.0f, 0.0f) },
		{ Vector(1.0f, 1.0f, -1.0f), Vector(1.0f, 0.0f, 0.0f) },
		{ Vector(1.0f, 1.0f, 1.0f), Vector(1.0f, 0.0f, 0.0f) },

		{ Vector(-1.0f, -1.0f, -1.0f), Vector(0.0f, 0.0f, -1.0f) },
		{ Vector(1.0f, -1.0f, -1.0f), Vector(0.0f, 0.0f, -1.0f) },
		{ Vector(1.0f, 1.0f, -1.0f), Vector(0.0f, 0.0f, -1.0f) },
		{ Vector(-1.0f, 1.0f, -1.0f), Vector(0.0f, 0.0f, -1.0f) },

		{ Vector(-1.0f, -1.0f, 1.0f), Vector(0.0f, 0.0f, 1.0f) },
		{ Vector(1.0f, -1.0f, 1.0f), Vector(0.0f, 0.0f, 1.0f) },
		{ Vector(1.0f, 1.0f, 1.0f), Vector(0.0f, 0.0f, 1.0f) },
		{ Vector(-1.0f, 1.0f, 1.0f), Vector(0.0f, 0.0f, 1.0f) },
	};

	WORD indices_temp[] =
	{
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};

	int vertex_num = sizeof(vertices_temp)/sizeof(vertices_temp[0]);
	Geometry::VertexFull* vertex_data = new Geometry::VertexFull[vertex_num];
	for (int i = 0; i < vertex_num; i++)
	{
		vertex_data[i].position = vertices_temp[i].position;
		vertex_data[i].normal = vertices_temp[i].normal;
		vertex_data[i].color = { 1.0f, 1.0f, 0.0f };
	}

	int index_num = sizeof(indices_temp) / sizeof(indices_temp[0]);
	unsigned int* index_data = new unsigned int[index_num];
	for (int i = 0; i < index_num; i++)
	{
		index_data[i] = indices_temp[i];
	}

	if (!geometry_->Init<Geometry::VertexFull>(vertex_data, vertex_num, index_data, index_num))
	{
		return false;
	}

	if (!material_->Init("light_mesh.fx"))
	{
		return false;
	}

	return true;
}

}