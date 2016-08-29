#ifndef ENGINE_CAMERA_CAMERA_H
#define ENGINE_CAMERA_CAMERA_H

#include "../engine_pch.h"
#include "RTMath.h"


class BaseCamera
{
public:
	BaseCamera();
	virtual ~BaseCamera();

	virtual bool Init() { return true; }
	virtual void Update() = 0;
	virtual void Free() { ; }

	void GetViewMatrix(Matrix *ViewMat);
	void GetDirection(RTMath::Vector *vDir, RTMath::Vector *vUp, RTMath::Vector *vRight);
	void SetPos(RTMath::Vector &vPos);
	void GetPos(RTMath::Vector *vPos);

protected:
	RTMath::Matrix m_ViewMat;

	float m_fRotX; // 在局部坐标系下的Euler角(旋转角)
	float m_fRotY;
	float m_fRotZ;
	RTMath::Vector m_vPos;		
	RTMath::Vector m_vDir;	
	RTMath::Vector m_vUp;
	RTMath::Vector m_vRight;	
};


class FreeCamera : public BaseCamera
{
public:
	FreeCamera();
	~FreeCamera();

	virtual void Update();

	void SetMoveDirection(RTMath::Vector &vMoveDirection);
	void GetMoveDirection(RTMath::Vector *vMoveDirection);
	void GetRotAngle(float *fRotX, float *fRotY, float *fRotZ);
	void SetRotAngle(float fRotX, float fRotY, float fRotZ);
	void SetRotAngleDelta(float fRotXDelta, float fRotYDelta, float fRotZDelta);
	void SetMoveDelta(float fMoveDelta);

private:
	RTMath::Vector m_vMoveDirection;
};

#endif