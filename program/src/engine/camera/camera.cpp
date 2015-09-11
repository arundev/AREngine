#include "camera.h"
#include <D3DX10.h>
#include <directxmath.h>

Camera::Camera(){

}

Camera::~Camera(){

}

void Camera::SetPosition(float x, float y, float z){
	position_ = Vector(x, y, z);
}

void Camera::SetRotation(float x, float y, float z){
	rotation_ = Vector(x, y, z);
}

void Camera::Update(){
	Vector up(0.0f, 1.0f, 0.0f);
	Vector look_at(0.0f, 0.0f, 1.0f);

	float pitch = rotation_.x_ * 0.0174532925f;
	float yaw = rotation_.y_ * 0.0174532925f;
	float roll = rotation_.z_ * 0.0174532925f;

	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

}

const Matrix& Camera::GetViewMat(){
	return viewMat_;
}