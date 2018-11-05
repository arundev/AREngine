#ifndef ENGINE_SCENE_NODE_H
#define ENGINE_SCENE_NODE_H

#include "../engine_pch.h"
#include "../mesh/mesh.h"

namespace engine {
	class Node : public engine::Object
	{
	public:
		Node();
		~Node();

		virtual bool Init() { return true; }
		virtual void Free() { ; }
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

		Vector& translate() { return translate_; }
		void set_translate(Vector& pos) { translate_ = pos; }
		Matrix& rotate() { return rotate_; }
		void set_rotate(Matrix& mat) { rotate_ = rotate_; }
		Vector& scale() { return scale_; }
		void set_scale(Vector& v) { scale_ = v; }

	protected:
		std::string name_;
		Node* parent_;
		std::vector<Node*> children_;
		Vector translate_;
		Matrix rotate_;
		Vector scale_;
	};
}

#endif // ENGINE_SCENE_NODE_H