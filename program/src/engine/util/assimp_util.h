#ifndef ENGINE_UTIL_ASSIMP
#define ENGINE_UTIL_ASSIMP

#include "../engine_pch.h"

class Mesh;
class aiMesh;

class AssimpUtil
{
public:
	AssimpUtil(){ ; }
	~AssimpUtil(){ ; }

	static bool LoadFile(const char* file_name, std::vector<Mesh*>& meshes);
	static Mesh* CreateMesh(aiMesh* src_mesh);

private:

};

#endif // ENGINE_UTIL_ASSIMP