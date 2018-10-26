#ifndef ENGINE_MESH_MESH_H
#define ENGINE_MESH_MESH_H

#include "../engine_pch.h"
#include "material.h"
#include "geometry.h"
#include <vector>

class Mesh
{
public:
	Mesh();
	Mesh(const std::string& path);
	~Mesh();

	static Mesh* CreateTriangle();
	static Mesh* CreateCube();
	static Mesh* CreatMesh(const std::string& path,
		void* vertex_data, int vertex_num, unsigned int* index_data, int index_num,
		const std::string& baseTex = "", const std::string& normalTex = "", const std::string& specularTex = "",
		const std::string& vs = "color.vs", const std::string& ps= "color.ps");

	void Update(float elapse);
	void Render();
	void Free();

	Geometry* geometry(){ return geometry_; }
	Material* material(){ return material_; }

	const std::string& getFileDirectory() { return fileDirectory_; }

protected:
	bool Init();
	bool Init(const std::string& path);

protected:
	std::string fileDirectory_;
	std::string name_;

	Geometry* geometry_;
	Material* material_;

	Vector translate_;
	Vector scale_;
	Vector rotate_;
};


#endif // ENGINE_MODEL_MODEL_H