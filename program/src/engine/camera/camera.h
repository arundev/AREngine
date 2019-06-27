#ifndef ENGINE_CAMERA_CAMERA_H
#define ENGINE_CAMERA_CAMERA_H

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
	virtual void SetPos(engine::Vector &vPos);
	virtual void GetPos(engine::Vector *vPos);

protected:
	engine::Matrix m_ViewMat;

	float m_fRotX; // 在局部坐标系下的Euler角(旋转角)
	float m_fRotY;
	float m_fRotZ;
	engine::Vector m_vPos;
	engine::Vector m_vDir;
	engine::Vector m_vUp;
	engine::Vector m_vRight;
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
	engine::Vector m_vMoveDirection;
};

}

#endif