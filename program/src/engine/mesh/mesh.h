#ifndef ENGINE_MESH_MESH_H
#define ENGINE_MESH_MESH_H

#include "../engine_pch.h"
#include "../math/math.h"

class Material;
class Geometry;

class Mesh
{
public:
	Mesh();
	~Mesh();

	static Mesh* CreateTriangle();
	static Mesh* CreateCube();

	void Update(float elapse);
	void Render();
	void Free();

	Geometry* geometry(){ return geometry_; }
	Material* material(){ return material_; }

protected:
	bool Init();

protected:
	Geometry* geometry_;
	Material* material_;

	Vector translate_;
	Vector scale_;
	Vector rotate_;
};


#endif // ENGINE_MODEL_MODEL_H