#include "mesh.h"

std::list<Mesh*> Mesh::s_mesh_list;

Mesh::Mesh() :
geometry_(NULL),
material_(NULL)
{
	Init();
}

Mesh::~Mesh(){
	Free();
}
 
Mesh* Mesh::CreateTriangle(){
	Mesh* mesh = new Mesh();

	Geometry::Vertex* vertices = new Geometry::Vertex[3];
	vertices[0].position = Vector(-1.0f, -1.0f, 0.0f, 1.0f);  // Bottom left.
	vertices[0].color = Vector(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[1].position = Vector(0.0f, 1.0f, 0.0f, 1.0f);  // Top middle.
	vertices[1].color = Vector(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[2].position = Vector(1.0f, -1.0f, 0.0f, 1.0f);  // Bottom right.
	vertices[2].color = Vector(0.0f, 1.0f, 0.0f, 1.0f);
	int* indices = new int[3];
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.
	mesh->geometry()->Create(vertices, 3, indices, 3);
	mesh->material()->Create();

	s_mesh_list.push_back(mesh);
	return mesh;
}

Mesh* Mesh::CreateCube(){
	Mesh* mesh = new Mesh();
	return mesh;
}

bool Mesh::Init(){
	Free();
	geometry_ = new Geometry();
	material_ = new Material();

	return true;
}

void Mesh::Update(float elapse){

}

void Mesh::Render(){
	material_->Apply();
	geometry_->Flush();
}

void Mesh::Free(){
	if (geometry_){
		geometry_->Free();
	}

	if (material_){
		material_->Free();
	}

	SAFE_DELETE(geometry_);
	SAFE_DELETE(material_);
}

