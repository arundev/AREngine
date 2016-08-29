#ifndef ENGINE_MESH_MESH_H
#define ENGINE_MESH_MESH_H

#include "../engine_pch.h"
#include "../res/mesh_res.h"
#include "RTMath.h"
#include "material.h"
#include "geometry.h"
#include "../renderer.h"
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	static std::vector<Mesh*> s_mesh_list;

	static Mesh* CreateTriangle();
	static Mesh* CreateCube();
	static Mesh* CreateMesh(const MeshRes& res);

	void Update(float elapse);
	void Render();
	void Free();

	void SetRenderState();

	Geometry* geometry(){ return geometry_; }
	Material* material(){ return material_; }
	bool wireframe()const{ return wireframe_; }
	void wireframe(bool b){ wireframe_ = true; }
	Renderer::ECullMode cull_mode()const{ return cull_mode_; }
	void cull_mode(Renderer::ECullMode mode){ cull_mode_ = mode; }

protected:
	bool Init();
	void UpdateAabb();

protected:
	Geometry* geometry_;
	Material* material_;
	RTMath::Aabb aabb_;

	Vector translate_;
	Vector scale_;
	Vector rotate_;

	bool wireframe_;
	Renderer::ECullMode cull_mode_;
};


#endif // ENGINE_MODEL_MODEL_H