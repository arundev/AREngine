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

	Geometry::Vertex* vertices = new Geometry::Vertex[3];
	vertices[0].position = Vector(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].color = Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[0].tex_coord_x[0] = 0;
	vertices[0].tex_coord_y[0] = 1;
	vertices[1].position = Vector(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].color = Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[1].tex_coord_x[0] = 0.5f;
	vertices[1].tex_coord_y[0] = 0.0f;
	vertices[2].position = Vector(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].color = Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[2].tex_coord_x[0] = 1.0f;
	vertices[2].tex_coord_y[0] = 1.0f;
	unsigned int* indices = new unsigned int[3];
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.
	mesh->geometry()->Init(vertices, 3, indices, 3);
	mesh->material()->Init("../../bin/res/color.vs", "../../bin/res/color.ps");
	mesh->material()->SetTexture("../../bin/res/stone01.tga");

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

