#include "mesh.h"

Mesh::Mesh() :
geometry_(NULL),
material_(NULL){
	Init();
}

Mesh::Mesh(const std::string& path) : 
geometry_(NULL),
material_(NULL){
	Init(path);
}

Mesh::~Mesh(){
	Free();
}
 
Mesh* Mesh::CreateTriangle(){
	Mesh* mesh = new Mesh();

	Geometry::VertexFull* vertices = new Geometry::VertexFull[3];
	vertices[0].position = engine_math::Vector(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].color = engine_math::Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[0].texture1 = engine_math::Vector(0.0f, 1.0f, 0.0f);
	vertices[1].position = engine_math::Vector(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].color = engine_math::Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[1].texture1 = engine_math::Vector(0.5f, 0.0f, 0.0f);
	vertices[2].position = engine_math::Vector(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].color = engine_math::Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[2].texture1 = engine_math::Vector(1.0f, 1.0f, 0.0f);

	unsigned int* indices = new unsigned int[3];
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	mesh->geometry()->Init<Geometry::VertexFull>(vertices, 3, indices, 3);
	mesh->material()->Init("color.vs", "color.ps");
	mesh->material()->SetBaseMap("../../bin/res/jeep1.jpg");

	SAFE_DELETE_ARRAY(vertices);
	SAFE_DELETE_ARRAY(indices);

	return mesh;
}

Mesh* Mesh::CreateCube(){
	Mesh* mesh = new Mesh();
	return mesh;
}

Mesh* Mesh::CreatMesh(const std::string& path,
	void* vertex_data, int vertex_num, unsigned int* index_data, int index_num,
	const std::string& baseTex, const std::string& normalTex, const std::string& specularTex,
	const std::string& vs, const std::string& ps){

	auto mesh = new Mesh(path);
	if (!mesh){
		return nullptr;
	}

	auto vertex_list = static_cast<Geometry::VertexFull*>(vertex_data);
	if (!vertex_list)
	{
		SAFE_DELETE(mesh);
		return nullptr;
	}

	if (!mesh->geometry()->Init<Geometry::VertexFull>(vertex_list,
		vertex_num,
		index_data,
		index_num)) {
		SAFE_DELETE(vertex_list);
		SAFE_DELETE(index_data);
		SAFE_DELETE(mesh);
		return nullptr;
	}
	if (!mesh->material()->Init("color.vs", "color.ps")) {
		SAFE_DELETE(vertex_list);
		SAFE_DELETE(index_data);
		SAFE_DELETE(mesh);
		return nullptr;
	}

	std::string directory = FileUtil::getDirectory(path);
	auto baseTexPath = directory + "/" + baseTex;
	auto normalTexPath = directory + "/" + baseTex;
	auto specularTexPath = directory + "/" + baseTex;
	mesh->material()->SetBaseMap(baseTexPath.c_str());
	mesh->material()->SetNormalMap(normalTexPath.c_str());
	mesh->material()->SetSpecularMap(specularTexPath.c_str());

	return nullptr;
}

bool Mesh::Init(const std::string& path) {
	Init();

	fileDirectory_ = FileUtil::getDirectory(path);
	name_ = FileUtil::getFileName(path);

	return true;
}

bool Mesh::Init(){
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

