#include "node.h"

namespace engine {
	Node::Node() : parent_(0) {
		scale_ = Vector(1.0f, 1.0f, 1.0f);
	}

	Node::~Node() {
		parent_ = 0;
		children_.clear();
	}

	void Node::Update(float elapse) {

	}

	void Node::Render() {

	}

	void Node::DelAllChildren() {
		children_.clear();
	}

	void Node::DelChild(int index) {
		if (index >= children_.size() ||
			index < 0){
			return;
		}

		int count = 0;
		std::vector<Node*>::iterator itr = children_.begin();
		while (count++ < index) {
			itr++;
		}

		children_.erase(itr);
	}

	void Node::AddChild(Node* node) {
		if (node == 0){
			return;
		}

		node->set_parent(this);
		children_.push_back(node);
	}

	Node* Node::GetChild(int index) const{
		if (index >= children_.size() ||
			index < 0){
			return 0;
		}

		int count = 0;
		std::vector<Node*>::const_iterator itr = children_.begin();
		while (count++ < index) {
			itr++;
		}

		return *itr;
	}

	Node* Node::GetChild(const char* name)const {
		if (name == 0){
			return 0;
		}

		std::vector<Node*>::const_iterator itr = children_.begin();
		while (itr != children_.end()) {
			if ((*itr)->name_ == name)
			{
				return *itr;
			}
		}

		return 0;
	}

}