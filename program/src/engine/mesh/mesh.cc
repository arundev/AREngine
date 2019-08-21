#include "engine_pch.h"
#include "mesh.h"

namespace engine {


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
	vertices[0].position = engine::Vector(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].color = engine::Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[0].texture1 = engine::Vector(0.0f, 1.0f, 0.0f);
	vertices[1].position = engine::Vector(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].color = engine::Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[1].texture1 = engine::Vector(0.5f, 0.0f, 0.0f);
	vertices[2].position = engine::Vector(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].color = engine::Color(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[2].texture1 = engine::Vector(1.0f, 1.0f, 0.0f);

	unsigned int* indices = new unsigned int[3];
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	mesh->geometry()->Init<Geometry::VertexFull>(vertices, 3, indices, 3);
	//mesh->material()->Init("color.vs", "color.ps");
	mesh->material()->Init("demo_dx11.fx");
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

	//if (!mesh->material()->Init("color.vs", "color.ps")) 
	//if (!mesh->material()->Init("model.fx"))
	if (!mesh->material()->Init("lighting_vs.hlsl", "lighting_ps.hlsl"))
	{
		SAFE_DELETE(vertex_list);
		SAFE_DELETE(index_data);
		SAFE_DELETE(mesh);
		return nullptr;
	}

	std::string directory = FileUtil::getDirectory(path);


	// CreateWICTextureFromFile��֧��tag��ʽ��תΪpng����
	if (!baseTex.empty())
	{
		auto baseTexPath = directory + "/" + baseTex;
		baseTexPath = engine::FormatFilePath(baseTexPath);
		baseTexPath = engine::StringReplace(baseTexPath, ".tga", ".png");
		mesh->material()->SetBaseMap(baseTexPath.c_str());
	}

	if (!normalTex.empty())
	{
		auto normalTexPath = directory + "/" + normalTex;
		normalTexPath = engine::FormatFilePath(normalTexPath);
		normalTexPath = engine::StringReplace(normalTexPath, ".tga", ".png");
		mesh->material()->SetNormalMap(normalTexPath.c_str());
	}

	if (!specularTex.empty())
	{
		auto specularTexPath = directory + "/" + specularTex;
		specularTexPath = engine::FormatFilePath(specularTexPath);
		specularTexPath = engine::StringReplace(specularTexPath, ".tga", ".png");
		mesh->material()->SetSpecularMap(specularTexPath.c_str());
	}

	return mesh;
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

	transform_.Identity();

	return true;
}

void Mesh::Update(float elapse){
	material_->set_world_transform(transform_);
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

void Mesh::set_geometry(const Geometry* data)
{
	if (data == geometry_)
	{
		return;
	}

	SAFE_FREE(geometry_);
	geometry_ = const_cast<Geometry*>(data);
}

void Mesh::set_material(const Material* data)
{
	if (data == material_)
	{
		return;
	}

	SAFE_FREE(material_);
	material_ = const_cast<Material*>(data);
}

}
