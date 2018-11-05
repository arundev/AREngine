#ifndef ENGINE_MESH_GEOMETRY_H
#define ENGINE_MESH_GEOMETRY_H

#include "../engine_pch.h"

namespace engine {


class Geometry
{
public:
	Geometry();
	virtual ~Geometry();

	struct VertexFull
	{
		VertexFull(){
		}

		engine::Vector position;
		engine::Color color;
		engine::Vector texture1;
		engine::Vector texture2;
		engine::Vector normal;
		engine::Vector tangent;
		engine::Vector bitangent;
		unsigned char bone_indices[4];
		unsigned char bone_weights[4];
	};

	static Geometry* Create();

	template<typename t>
	bool Init(t* vertex_data, int vertex_num, unsigned int* index_data, int index_num);
	void Free();

	void SetDataSteam();
	void Flush();

protected:
	virtual bool DoInit() = 0;
	virtual void DoFree() = 0;
	virtual void DoSetDataStream() = 0;
	virtual void DoFlush() = 0;

protected:
	unsigned char* vertex_data_;
	unsigned int* index_data_;
	int vertex_stride;
	int vertex_num_;
	int index_num_;
};

template <typename t>
bool Geometry::Init(t* vertex_data, int vertex_num, unsigned int* index_data, int index_num){
	if (vertex_data == NULL){
		return false;
	}

	vertex_num_ = vertex_num;
	index_num_ = index_num;
	vertex_stride = sizeof(t);
	int vertex_byte_size = sizeof(t)*vertex_num_;
	int index_byte_size = sizeof(unsigned int)*index_num_;
	vertex_data_ = (unsigned char*)malloc(vertex_byte_size);
	index_data_ = (unsigned int*)malloc(index_byte_size);
	memcpy(vertex_data_, vertex_data, vertex_byte_size);
	memcpy(index_data_, index_data, index_byte_size);

	return DoInit();
}


}

#endif // ENGINE_MODEL_GEOMETRY_H