#include "camera_data.h"
#include "../dx11/util_dx11.h"

namespace engine {

BaseCamera::BaseCamera()
{
	view_mat_.Identity();

	rot_x_ = 0.0f;
	rot_y_ = 0.0f;
	rot_z_ = 0.0f;


	position_.Set(0.0f, 0.0f, 0.0f);

	forward_.Set(0.0f, 0.0f, 1.0f);
	up_.Set(0.0f, 1.0f, 0.0f);
	right_.Set(1.0f, 0.0f, 0.0f);
}

BaseCamera::~BaseCamera()
{

}

void BaseCamera::GetViewMatrix(engine::Matrix *ViewMat)
{
	if (!ViewMat)
		return;

	memcpy(ViewMat, &view_mat_, sizeof(engine::Matrix));

}

void BaseCamera::SetPosition(engine::Vector &vPos)
{
	memcpy(&position_, &vPos, sizeof(engine::Vector));
}

void BaseCamera::GetPosition(engine::Vector *vPos)
{
	if (!vPos)
		return;
	memcpy(vPos, &position_, sizeof(engine::Vector));
}

void BaseCamera::GetDirection(engine::Vector *vDir, engine::Vector *vUp, engine::Vector *vRight)
{
	if (vDir)
		memcpy(vDir, &forward_, sizeof(engine::Vector));

	if (vUp)
		memcpy(vUp, &up_, sizeof(engine::Vector));

	if (vRight)
		memcpy(vRight, &right_, sizeof(engine::Vector));
}


/*----------------------------------------------------------------
class FreeCamera
----------------------------------------------------------------*/
FreeCamera::FreeCamera()
{
	move_direction_.Set(0.0f, 0.0f, 1.0f);
}

FreeCamera::~FreeCamera()
{
}

void FreeCamera::SetMoveDirection(engine::Vector &vMoveDirection)
{
	memcpy(&move_direction_, &vMoveDirection, sizeof(engine::Vector));

}

void FreeCamera::GetMoveDirection(engine::Vector *vMoveDirection)
{
	if (vMoveDirection)
		memcpy(vMoveDirection, &move_direction_, sizeof(engine::Vector));

}

void FreeCamera::GetRotAngle(float *fRotX, float *fRotY, float *fRotZ)
{
	if (fRotX)
		*fRotX = rot_x_;
	if (fRotY)
		*fRotY = rot_y_;
	if (fRotZ)
		*fRotZ = rot_z_;
}

void FreeCamera::SetRotAngle(float fRotX, float fRotY, float fRotZ)
{
	rot_x_ = fRotX;
	rot_y_ = fRotY;
	rot_z_ = fRotZ;
}

void FreeCamera::SetRotAngleDelta(float fRotXDelta, float fRotYDelta, float fRotZDelta)
{

	rot_x_ += fRotXDelta;
	rot_y_ += fRotYDelta;
	rot_z_ += fRotZDelta;

	if (rot_x_ > MATH_2PI)
		rot_x_ -= (float)MATH_2PI;
	else if(rot_x_ < -MATH_2PI)
		rot_x_ += (float)MATH_2PI;

	if (rot_y_ > MATH_2PI)
		rot_y_ -= (float)MATH_2PI;
	else if(rot_y_ < -MATH_2PI) 
		rot_y_ += (float)MATH_2PI;

	if (rot_z_ > MATH_2PI)
		rot_z_ -= (float)MATH_2PI;
	else if (rot_z_ < -MATH_2PI)
		rot_z_ += (float)MATH_2PI;
}

void FreeCamera::SetMoveDelta(float vMoveDelta)
{
	position_ += move_direction_ * vMoveDelta;
}


void FreeCamera::Update()
{

	Quaternion  qFrame(0, 0, 0, 1);
	qFrame.MakeFromEuler(rot_x_, rot_y_, rot_z_);
	view_mat_.Identity();
	qFrame.GetMatrix(&view_mat_);

	right_.x = view_mat_._11;
	right_.y = view_mat_._21;
	right_.z = view_mat_._31;

	up_.x = view_mat_._12;
	up_.y = view_mat_._22;
	up_.z = view_mat_._32;

	forward_.x = view_mat_._13;
	forward_.y = view_mat_._23;
	forward_.z = view_mat_._33;

	view_mat_._41 = -(right_ * position_);
	view_mat_._42 = -(up_ * position_);
	view_mat_._43 = -(forward_ * position_);
	view_mat_._44 = 1.0f;
}


}