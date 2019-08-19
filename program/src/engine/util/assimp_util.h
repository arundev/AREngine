#ifndef ENGINE_UTIL_ASSIMP
#define ENGINE_UTIL_ASSIMP

#include <string>
#include <vector>

namespace engine {
	class Mesh;
	class Scene;
	class Node;
	class Material;
}

struct aiMesh;
struct aiMaterial;
struct aiNode;
//struct aiMatrix4x4;
//struct aiVector3D;
//struct aiColor4D;

namespace engine{

class AssimpUtil
{
public:
	AssimpUtil(){ ; }
	~AssimpUtil(){ ; }

	static bool LoadFile(const std::string& file_name, std::vector<engine::Mesh*>& meshes);
	static Mesh* CreateMesh(const std::string& filePath, aiMesh* src_mesh, aiMaterial* src_material);
	static Scene* CreateScene(const std::string& file_name);

private:
	static Node* CreateNode(aiNode* src_node, Node* parent, const std::vector<Mesh*>& mesh_list);
	static Mesh* CreateMesh(aiMesh* src_mesh);
	static Material* CreatMaterial(aiMaterial* src_material);

	//static void CopyData(const aiMatrix4x4* src, Matrix* dst);
	//static void CopyData(const aiVector3D* src, Vector* dst);
	//static void CopyData(const aiColor4D* src, Color* dst);

};

}


#endif // ENGINE_UTIL_ASSIMP