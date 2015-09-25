#include "camera.h"
#include "../dx11/util_dx11.h"
#include <D3DX10.h>
#include <directxmath.h>

using namespace DirectX;

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

	D3DXMATRIX rotationMatrix_d3d;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix_d3d, yaw, pitch, roll);

	Matrix rotationMatrix;
	MatrixFromDx11(&rotationMatrix_d3d, &rotationMatrix);

	look_at *= rotationMatrix;
	up *= rotationMatrix;

	D3DXMATRIX viewMatrix_d3d;
	D3DVECTOR v;
	//D3DXMatrixLookAtLH(&viewMatrix_d3d, position_, look_at, up);
}

const Matrix& Camera::GetViewMat(){
	return viewMat_;
}