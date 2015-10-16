#include "geometry.h"
#include "../dx11/geometry_dx11.h"

Geometry::Geometry() :
vertex_data_(NULL),
index_data_(NULL)
{

}

Geometry::~Geometry(){

}

Geometry* Geometry::Create(){

	Geometry* geometry = 0;
	if (Plateform::graphic_api() == Plateform::D3D_11)
	{
		geometry = new GeometryDx11();
	}

	return geometry;
}


bool Geometry::Init(Vertex* vertex_data, int vertex_num, unsigned int* index_data, int index_num){

	if (vertex_data == NULL){
		return false;
	}

	vertex_num_ = vertex_num;
	index_num_ = index_num;
	int vertex_byte_size = sizeof(Vertex)*vertex_num_;
	int index_byte_size = sizeof(unsigned int)*index_num_;
	vertex_data_ = (Vertex*)malloc(vertex_byte_size);
	index_data_ = (unsigned int*)malloc(index_byte_size);
	memcpy(vertex_data_, vertex_data, vertex_byte_size);
	memcpy(index_data_, index_data, index_byte_size);

	return DoInit();
}

void Geometry::Free(){
	DoFree();

	SAFE_DELETE(vertex_data_);
	SAFE_DELETE(index_data_);
}

void Geometry::SetDataSteam(){
	DoSetDataStream();
}

void Geometry::Flush(){
	DoFlush();
}