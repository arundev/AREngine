#include "geometry.h"
#include "../dx11/geometry_dx11.h"

namespace engine {


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


}