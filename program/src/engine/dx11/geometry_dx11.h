#ifndef ENGINE_DX11_GEOMETRY_H
#define ENGINE_DX11_GEOMETRY_H

#include "mesh/geometry.h"
#include "dx11_include.h"

namespace engine {

class GeometryDx11 : public Geometry
{
public:
	GeometryDx11();
	virtual ~GeometryDx11();

protected:
	virtual bool DoInit();
	virtual void DoFree();
	virtual void DoSetDataStream();
	virtual void DoFlush();

private:
	ID3D11Buffer * vertex_buffer_;
	ID3D11Buffer* index_buffer_;
};


}

#endif // ENGINE_DX11_GEOMETRY_H