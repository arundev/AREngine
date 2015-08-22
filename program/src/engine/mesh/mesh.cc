#include "mesh.h"
#include "geometry.h"
#include "material.h"

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

