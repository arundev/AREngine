#ifndef ENGINE_RES_MESH_RES_H
#define ENGINE_RES_MESH_RES_H

#include "../engine_pch.h"

class MeshRes
{
public:
	MeshRes()
	{
	}

	~MeshRes()
	{
	}

	struct Vertex
	{
		engine_math::Vector3F position;
		engine_math::Color color;
		engine_math::Vector2F uv;
		engine_math::Vector3F normal;
	};

	struct Triangle
	{
		int vertex_index[3];
	};

	struct Material
	{
		float ambient;
		float diffuse;
		float specular;
		float emit;
		float opacity;
		float shininess;
	};

	struct Mesh
	{
		int material_id;
		std::string name;
		std::vector<Vertex> vertices;
		std::vector<Triangle> triangles;
	};

	struct Animation
	{
		std::string name;
		int start_frame;
		int end_frame;
	};

	void SetVertexData(MeshRes::Vertex* data, int num);
	void SetIndexData(int* data, int num);

	bool SaveToJson(const char* path){ ; }
	
	std::vector<MeshRes::Vertex> vertices()const{ return vertices_; }
	std::vector<int> indices()const{ return indices_; }

private:
	std::vector<MeshRes::Vertex> vertices_;
	uint32_t vertex_num_;
	std::vector<int> indices_;
};


#endif // ENGINE_RES_MESH_RES_H