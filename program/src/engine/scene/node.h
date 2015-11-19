#ifndef ENGINE_SCENE_NODE_H
#define ENGINE_SCENE_NODE_H

#include "../engine_pch.h"
#include "../mesh/mesh.h"

namespace engine_scene {
	class Node : public engine_base::Object
	{
	public:
		Node();
		~Node();

		virtual void Update(float elapse);
		virtual void Render();

		
		std::string name()const { return name_; }
		void set_name(const char* str) { name_ = str; }

		Node* parent()const { return parent_; }
		void set_parent(Node* node) { parent_ = node; }
		std::vector<Node*>& children() { return children_; }
		void DelAllChildren();
		void DelChild(const char* name);
		void DelChild(int index);
		void AddChild(Node* node);
		Node* GetChild(const char* name)const;
		Node* GetChild(int index)const;

		RTMath::Vector& translate() { return translate_; }
		void set_translate(RTMath::Vector& pos) { translate_ = pos; }
		RTMath::Matrix& rotate() { return rotate_; }
		void set_rotate(RTMath::Matrix& mat) { rotate_ = rotate_; }
		RTMath::Vector& scale() { return scale_; }
		void set_scale(RTMath::Vector& v) { scale_ = v; }

		std::vector<Mesh*>& meshes() { return meshes_; }
		void AddMesh(Mesh* mesh) { meshes_.push_back(mesh); }

	protected:
		std::string name_;
		Node* parent_;
		std::vector<Node*> children_;
		RTMath::Vector translate_;
		RTMath::Matrix rotate_;
		RTMath::Vector scale_;

		std::vector<Mesh*> meshes_;
	};
}

#endif // ENGINE_SCENE_NODE_H