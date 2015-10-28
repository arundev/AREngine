#ifndef ENGINE_UTIL_ASSIMP
#define ENGINE_UTIL_ASSIMP

#include "../engine_pch.h"

class Mesh;
class aiMesh;
class aiMaterial;

class AssimpUtil
{
public:
	AssimpUtil(){ ; }
	~AssimpUtil(){ ; }

	static bool LoadFile(const char* file_name, std::vector<Mesh*>& meshes);
	static Mesh* CreateMesh(aiMesh* src_mesh, aiMaterial* src_material);

private:

};

#endif // ENGINE_UTIL_ASSIMP