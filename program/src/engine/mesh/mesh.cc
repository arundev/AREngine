#include "mesh.h"

std::vector<Mesh*> Mesh::s_mesh_list;

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

	Geometry::VertexFull* vertices = new Geometry::VertexFull[3];
	vertices[0].position = engine_math::Vector3F(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].color = engine_math::Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[0].texture1 = engine_math::Vector2F(0.0f, 1.0f);
	vertices[1].position = engine_math::Vector3F(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].color = engine_math::Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[1].texture1 = engine_math::Vector2F(0.5f, 0.0f);
	vertices[2].position = engine_math::Vector3F(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].color = engine_math::Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[2].texture1 = engine_math::Vector2F(1.0f, 1.0f);

	unsigned int* indices = new unsigned int[3];
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	mesh->geometry()->Init<Geometry::VertexFull>(vertices, 3, indices, 3);
	mesh->material()->Init("color.vs", "color.ps");
	mesh->material()->SetBaseMap("../../bin/res/jeep1.jpg");

	SAFE_DELETE_ARRAY(vertices);
	SAFE_DELETE_ARRAY(indices);

	s_mesh_list.push_back(mesh);
	return mesh;
}

Mesh* Mesh::CreateCube(){
	Mesh* mesh = new Mesh();
	return mesh;
}

bool Mesh::Init(){
	Free();
	geometry_ = Geometry::Create();
	material_ = Material::Create();

	return true;
}

void Mesh::Update(float elapse){

}

void Mesh::Render(){
	geometry_->SetDataSteam();
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

