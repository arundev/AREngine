#include "camera_node.h"

namespace engine {
	Camera::Camera() : camera_data_(0){
		camera_data_ = new FreeCamera();
		camera_data_->SetPos(Vector(0.0f, 0.0f, -5.0f));
	}

	Camera::~Camera() {
		SAFE_DELETE(camera_data_);
	}

	void Camera::Update(float elapse) {
		camera_data_->Update();
	}

	void Camera::Render() {

	}

	void Camera::set_camera_data(BaseCamera* camera) {

	}
}