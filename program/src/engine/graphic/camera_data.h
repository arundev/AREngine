#ifndef ENGINE_GRAPHIC_CAMERA_H
#define ENGINE_GRAPHIC_CAMERA_H

#include "../engine_pch.h"

namespace engine {

class BaseCamera
{
public:
	BaseCamera();
	virtual ~BaseCamera();

	virtual bool Init() { return true; }
	virtual void Update() = 0;
	virtual void Free() { ; }

	virtual void GetViewMatrix(engine::Matrix *ViewMat);
	virtual void GetDirection(engine::Vector *vDir, engine::Vector *vUp, engine::Vector *vRight);
	virtual void SetPosition(engine::Vector &vPos);
	virtual void GetPosition(engine::Vector *vPos);

protected:
	engine::Matrix view_mat_;

	float rot_x_; // 在局部坐标系下的Euler角(旋转角)
	float rot_y_;
	float rot_z_;
	engine::Vector position_;
	engine::Vector forward_;
	engine::Vector up_;
	engine::Vector right_;
};

class FreeCamera : public BaseCamera
{
public:
	FreeCamera();
	~FreeCamera();

	virtual void Update();

	void SetMoveDirection(engine::Vector &vMoveDirection);
	void GetMoveDirection(engine::Vector *vMoveDirection);
	void GetRotAngle(float *fRotX, float *fRotY, float *fRotZ);
	void SetRotAngle(float fRotX, float fRotY, float fRotZ);
	void SetRotAngleDelta(float fRotXDelta, float fRotYDelta, float fRotZDelta);
	void SetMoveDelta(float fMoveDelta);

private:
	engine::Vector move_direction_;
};

}

#endif