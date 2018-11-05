#ifndef ENGINE_UTIL_ASSIMP
#define ENGINE_UTIL_ASSIMP

#include "../engine_pch.h"

namespace engine {
	class Mesh;
}

struct aiMesh;
struct aiMaterial;

namespace engine{

class AssimpUtil
{
public:
	AssimpUtil(){ ; }
	~AssimpUtil(){ ; }

	static bool LoadFile(const std::string& file_name, std::vector<engine::Mesh*>& meshes);
	static engine::Mesh* CreateMesh(const std::string& filePath, aiMesh* src_mesh, aiMaterial* src_material);
private:

};

}


#endif // ENGINE_UTIL_ASSIMP