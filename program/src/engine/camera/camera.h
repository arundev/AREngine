#ifndef ENGINE_CAMERA_CAMERA_H
#define ENGINE_CAMERA_CAMERA_H

#include "../engine_pch.h"

class BaseCamera
{
public:
	BaseCamera();
	virtual ~BaseCamera();

	virtual bool Init() { return true; }
	virtual void Update() = 0;
	virtual void Free() { ; }

	void GetViewMatrix(Matrix *ViewMat);
	void GetDirection(Vector *vDir, Vector *vUp, Vector *vRight);
	void SetPos(Vector &vPos);
	void GetPos(Vector *vPos);

protected:
	Matrix m_ViewMat;

	float m_fRotX; // 在局部坐标系下的Euler角(旋转角)
	float m_fRotY;
	float m_fRotZ;
	Vector m_vPos;
	Vector m_vDir;
	Vector m_vUp;
	Vector m_vRight;
};

class FreeCamera : public BaseCamera
{
public:
	FreeCamera();
	~FreeCamera();

	virtual void Update();

	void SetMoveDirection(Vector &vMoveDirection);
	void GetMoveDirection(Vector *vMoveDirection);
	void GetRotAngle(float *fRotX, float *fRotY, float *fRotZ);
	void SetRotAngle(float fRotX, float fRotY, float fRotZ);
	void SetRotAngleDelta(float fRotXDelta, float fRotYDelta, float fRotZDelta);
	void SetMoveDelta(float fMoveDelta);

private:
	Vector m_vMoveDirection;
};

#endif