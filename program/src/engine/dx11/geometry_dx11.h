#ifndef ENGINE_DX11_GEOMETRY_H
#define ENGINE_DX11_GEOMETRY_H

#include <d3d11.h>
#include <D3DX11async.h>
#include "../mesh/geometry.h"

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
	ID3D11Buffer* vertex_buffer_;
	ID3D11Buffer* index_buffer_;
};


#endif // ENGINE_DX11_GEOMETRY_H