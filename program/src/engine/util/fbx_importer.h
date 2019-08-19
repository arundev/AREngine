#ifndef ENGINE_UTIL_FBX_IMPORTER_H
#define ENGINE_UTIL_FBX_IMPORTER_H

#include "fbxsdk.h"

class FBXImporter
{
public:
	FBXImporter();
	~FBXImporter();

	bool Init();
	void Free();

	bool LoadScene(const char* pchPath);

	FbxManager* fbx_manager()const{ return fbx_manager_; }
	FbxScene* scene()const{ return scene_; }

protected:
	bool ParseAll();
	bool ParseNode(FbxNode* node);
	bool ParseMesh(FbxNode* node);

private:
	FbxManager* fbx_manager_;
	FbxScene* scene_;
};


#endif //ENGINE_UTIL_FBX_IMPORTER_H