#include "node.h"
#include "../util/assimp_util.h"

namespace engine {
	Node::Node() : parent_(0) {
		
	}

	Node::~Node() {
		parent_ = 0;
		children_.clear();
	}

	void Node::Update(float elapse) {

		UpdateTransform();

		for (auto& mesh : meshes_) {
			if (mesh) {
				mesh->SetTransform(transform_world_);
				mesh->Update(elapse);
			}
		}

		for (auto& child : children_) {
			if (child)
			{
				child->Update(elapse);
			}
		}
	}

	bool Node::LoadFormeFile(const std::string& file) {

		if (!AssimpUtil::LoadFile(file.c_str(), meshes_)) 
		{
			return false;
		}

		if (!Init())
		{
			return false;
		}

		return true;
	}

	bool Node::Init() {
		if (!inited)
		{
			return true;
		}

		transform_.Identity();
		transform_world_.Identity();

		return true;
	}

	void Node::Render() {

	}

	void Node::Free(){

		for (auto& child : children_) {
			if (child)
			{
				child->Free();
			}
		}
		children_.clear();

		for (auto& mesh : meshes_) {
			if (mesh) {
				mesh->Free();
				SAFE_DELETE(mesh);
			}
		}
		meshes_.clear();
	}

	void Node::DelAllChildren() {
		children_.clear();
	}

	void Node::DelChild(int index) {
		if (index >= (int)children_.size() ||
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
		if (index >= (int)children_.size() ||
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


	void Node::getVisibleMeshes(const BaseCamera* camera, std::vector<Mesh*>& meshes) {
		for (auto& item : meshes_) {
			meshes.push_back(item);
		}
	}

	void Node::UpdateTransform() 
	{
		transform_world_.Identity();
		if (parent_)
		{
			transform_world_ = parent_->transform_world() * transform_;
		}
		else
		{
			transform_world_ = transform_;
		}
	}
}