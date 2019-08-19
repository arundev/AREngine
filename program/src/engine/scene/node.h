#ifndef ENGINE_SCENE_NODE_H
#define ENGINE_SCENE_NODE_H

#include "base/object.h"
#include "mesh/mesh.h"

class BaseCamera;

namespace engine {
	class Node : public engine_base::Object
	{
	public:
		Node();
		~Node();

		virtual bool LoadFormeFile(const std::string& path);

		virtual bool Init();
		virtual void Free();
		virtual void Update(float elapse);
		virtual void Render();

		std::string name()const { return name_; }
		void set_name(const char* str) { name_ = str; }

		Node* parent()const { return parent_; }
		void set_parent(Node* node) { parent_ = node; }
		std::vector<Node*>& children() { return children_; }
		void DelAllChildren();
		void DelChild(int index);
		void AddChild(Node* node);
		Node* GetChild(const char* name)const;
		Node* GetChild(int index)const;

		const Matrix& transform()const { return transform_; }
		void set_transform(const Matrix& ts) { transform_ = ts; }
		const Matrix& transform_world()const { return transform_world_; }
		Vector translate() { return transform_.GetTranslation(); }
		void set_translate(const Vector& move) { transform_.SetTranslation(move); }
		void set_rotate(const Vector& rot) { transform_.Rota(rot); }
		void set_scale(const Vector& scale) { transform_.Scaling(scale.x, scale.y, scale.z); }

		void getVisibleMeshes(const BaseCamera* camera, std::vector<Mesh*>& meshes);
		std::vector<Mesh*>& meshes() { return meshes_; }
		void AddMesh(Mesh* mesh) { meshes_.push_back(mesh); }

	protected:
		void UpdateTransform();

	protected:
		std::string name_;
		bool inited = false;
		Node* parent_;
		std::vector<Node*> children_;

		Matrix transform_; // local transform
		Matrix transform_world_; // world transform

		std::vector<Mesh*> meshes_;
	};
}

#endif // ENGINE_SCENE_NODE_H