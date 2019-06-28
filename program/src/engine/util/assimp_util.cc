#include "assimp_util.h"
#include "file_util.h"
#include "../mesh/mesh.h"

#include <assimp/cimport.h>
#include <assimp/LogStream.hpp>
#include <assimp/DefaultLogger.hpp>
#include <assimp/Importer.hpp>
#include <assimp/importerdesc.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

using namespace Assimp;

namespace engine {


unsigned int ppsteps = aiProcess_CalcTangentSpace | // calculate tangents and bitangents if possible
aiProcess_JoinIdenticalVertices | // join identical vertices/ optimize indexing
aiProcess_ValidateDataStructure | // perform a full validation of the loader's output
aiProcess_ImproveCacheLocality | // improve the cache locality of the output vertices
aiProcess_RemoveRedundantMaterials | // remove redundant materials
aiProcess_FindDegenerates | // remove degenerated polygons from the import
aiProcess_FindInvalidData | // detect invalid model data, such as invalid normal vectors
aiProcess_GenUVCoords | // convert spherical, cylindrical, box and planar mapping to proper UVs
aiProcess_TransformUVCoords | // preprocess UV transformations (scaling, translation ...)
aiProcess_FindInstances | // search for instanced meshes and remove them by references to one master
aiProcess_LimitBoneWeights | // limit bone weights to 4 per vertex
aiProcess_OptimizeMeshes | // join small meshes, if possible;
aiProcess_SplitByBoneCount | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader
0;


bool AssimpUtil::LoadFile(const std::string& file_name, std::vector<engine::Mesh*>& meshes)
{
	if (file_name.empty()){
		return false;
	}

	std::string full_path = g_file_util->GetModelsFolder() + file_name;
	if (!FileUtil::FileExists(full_path)) {

		std::string log = full_path + std::string(" is not exsit!");
		g_log->Write(log);
		return false;
	}

	aiPropertyStore* props = aiCreatePropertyStore();
	aiSetImportPropertyInteger(props, AI_CONFIG_IMPORT_TER_MAKE_UVS, 1);
	aiSetImportPropertyFloat(props, AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80.0f);

	aiScene* root = (aiScene*)aiImportFileExWithProperties(full_path.c_str(),
		ppsteps |
		aiProcess_GenSmoothNormals |
		aiProcess_SplitLargeMeshes |
		aiProcess_Triangulate |
		aiProcess_ConvertToLeftHanded |
		aiProcess_SortByPType |
		0,
		NULL,
		props);

	if (root == NULL){
		string log = string("error: failed to load file: ") + file_name;
		g_log->Write(log);
		return false;
	}

	for (unsigned int i = 0; i < root->mNumMeshes; i++){
		int mat_index = root->mMeshes[i]->mMaterialIndex;
		engine::Mesh* mesh = CreateMesh(full_path, root->mMeshes[i], root->mMaterials[mat_index]);
		if (mesh != NULL)
		{
			mesh->SetName(root->mMeshes[i]->mName.C_Str());
			meshes.push_back(mesh);
		}
	}

	aiReleasePropertyStore(props);

	return true;
}


engine::Mesh* AssimpUtil::CreateMesh(const std::string& filePath, aiMesh* src_mesh, aiMaterial* src_material){

	if (src_mesh == NULL){
		return NULL;
	}

	// vertex data
	int vertex_num = src_mesh->mNumVertices;
	Geometry::VertexFull* vertex_list = new Geometry::VertexFull[vertex_num];
	if (vertex_list == NULL){
		return NULL;
	}

	for (unsigned int i = 0; i < src_mesh->mNumVertices; i++){
		// position
		vertex_list[i].position = engine::Vector(src_mesh->mVertices[i].x, 
			src_mesh->mVertices[i].y, 
			src_mesh->mVertices[i].z);
		// normal
		if (src_mesh->mNormals){
			vertex_list[i].normal = engine::Vector(src_mesh->mNormals[i].x,
				src_mesh->mNormals[i].y,
				src_mesh->mNormals[i].z);
		}
		// color
		if (src_mesh->HasVertexColors(0)){
			vertex_list[i].color = engine::Color(src_mesh->mColors[i][0].r,
				src_mesh->mColors[i][0].g,
				src_mesh->mColors[i][0].b,
				src_mesh->mColors[i][0].a);
		}
		// tangent
		if (src_mesh->mTangents){
			vertex_list[i].tangent = engine::Vector(src_mesh->mTangents[i].x,
				src_mesh->mTangents[i].y,
				src_mesh->mTangents[i].z);
		}
		// bitangent
		if (src_mesh->mBitangents){
			vertex_list[i].bitangent = engine::Vector(src_mesh->mBitangents[i].x,
				src_mesh->mBitangents[i].y,
				src_mesh->mBitangents[i].z);
		}
		 
		// tex coordinate
		if (src_mesh->HasTextureCoords(0)){
			vertex_list[i].texture1 = engine::Vector(src_mesh->mTextureCoords[0][i].x, src_mesh->mTextureCoords[0][i].y, 0.0f);
		}
		if (src_mesh->HasTextureCoords(1)){
			vertex_list[i].texture2 = engine::Vector(src_mesh->mTextureCoords[1][i].x,
				src_mesh->mTextureCoords[1][i].y, 0.0f);
		}
		// bone indices and weights
		if (src_mesh->HasBones()){
			
		}
	}

	// index data
	int nidx;
	switch (src_mesh->mPrimitiveTypes){
	case aiPrimitiveType_POINT:
		nidx = 1; break;
	case aiPrimitiveType_LINE:
		nidx = 2; break;
	case aiPrimitiveType_TRIANGLE:
		nidx = 3; break;
	default:
		SAFE_DELETE(vertex_list);
		return NULL;
		break;
	}
	int index_num = src_mesh->mNumFaces * nidx;
	unsigned int* index_list = new unsigned int[index_num];
	if (index_list == NULL){
		SAFE_DELETE(vertex_list);
		return NULL;
	}
	unsigned int* address = index_list;
	for (unsigned int i = 0; i < src_mesh->mNumFaces; i++){
		for (int j = 0; j < nidx; j++){
			*address++ = src_mesh->mFaces[i].mIndices[j];
		}
	}

	// texture
	string base_map, normal_map, specular_map;
	if (src_material != NULL){
		aiString sz_path;
		if (aiGetMaterialString(src_material, AI_MATKEY_TEXTURE_DIFFUSE(0), &sz_path) == AI_SUCCESS){
			base_map = sz_path.C_Str();
		}
		if (aiGetMaterialString(src_material, AI_MATKEY_TEXTURE_NORMALS(0), &sz_path) == AI_SUCCESS) {
			normal_map = sz_path.C_Str();
		}
		if (aiGetMaterialString(src_material, AI_MATKEY_TEXTURE_SPECULAR(0), &sz_path) == AI_SUCCESS) {
			specular_map = sz_path.C_Str();
		}
	}

	// mesh
	Mesh* dst_mesh = Mesh::CreatMesh(filePath, vertex_list, vertex_num, index_list, index_num,
		base_map, normal_map, specular_map);

	/*
	if (!dst_mesh->geometry()->Init<Geometry::VertexFull>(vertex_list,
		vertex_num, 
		index_list, 
		index_num)){
		SAFE_DELETE(vertex_list);
		SAFE_DELETE(index_list);
		SAFE_DELETE(dst_mesh);
		return NULL;
	}
	if (!dst_mesh->material()->Init("color.vs", "color.ps")){
		SAFE_DELETE(vertex_list);
		SAFE_DELETE(index_list);
		SAFE_DELETE(dst_mesh);
		return NULL;
	}
	//base_map = "Male101.png";
	if (base_map != "" && !dst_mesh->material()->SetBaseMap(base_map.c_str())){
		SAFE_DELETE(vertex_list);
		SAFE_DELETE(index_list);
		SAFE_DELETE(dst_mesh);
		return NULL;
	}
	if (normal_map != "" && !dst_mesh->material()->SetNormalMap(normal_map.c_str())) {
		SAFE_DELETE(vertex_list);
		SAFE_DELETE(index_list);
		SAFE_DELETE(dst_mesh);
		return NULL;
	}
	if (specular_map != "" && !dst_mesh->material()->SetSpecularMap(specular_map.c_str())) {
		SAFE_DELETE(vertex_list);
		SAFE_DELETE(index_list);
		SAFE_DELETE(dst_mesh);
		return NULL;
	}
	*/

	return dst_mesh;
}


}