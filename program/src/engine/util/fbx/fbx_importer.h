#ifndef ENGINE_UTIL_FBX_IMPORTER_H
#define ENGINE_UTIL_FBX_IMPORTER_H

#include "../../engine_pch.h"
#include "../../res/mesh_res.h"
#include "fbxsdk.h"

#pragma comment(lib, "libfbxsdk.lib")

class FbxImporterTool
{
public:
	FbxImporterTool();
	~FbxImporterTool();

	bool Init();
	void Free();

	bool LoadScene(const char* pchPath);

	FbxManager* fbx_manager()const{ return fbx_manager_; }
	FbxScene* scene()const{ return scene_; }
	MeshRes* mesh_data()const{ return mesh_data_; }

protected:
	bool ParseAll();
	bool ParseNode(FbxNode* node);
	bool ParseMesh(FbxNode* node);

	void ReadVertex(FbxMesh* mesh, int index, MeshRes::Vertex& vertex);
	void ReadColor(FbxMesh* mesh, int vertex_index, int index, MeshRes::Vertex& vertex);
	void ReadUV(FbxMesh* mesh, int vertex_index, int uv_index, int index, MeshRes::Vertex& vertex);
	void ReadNormal(FbxMesh* mesh, int vertex_index, int index, MeshRes::Vertex& vertex);
	void ReadTangent(FbxMesh* mesh, int vertex_index, int index, MeshRes::Vertex& vertex);

private:
	FbxManager* fbx_manager_;
	FbxScene* scene_;
	MeshRes* mesh_data_;
};


#endif //ENGINE_UTIL_FBX_IMPORTER_H