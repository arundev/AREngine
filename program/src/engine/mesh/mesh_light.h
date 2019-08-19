#ifndef ENGINE_MESH_MESH_LIGHT_H
#define ENGINE_MESH_MESH_LIGHT_H

#include "mesh.h"

namespace engine {
	
class LightMesh : public Mesh 
{
public:
	LightMesh();
	~LightMesh();

	virtual bool Init();
};

}



#endif // !ENGINE_MESH_MESH_LIGHT_H
