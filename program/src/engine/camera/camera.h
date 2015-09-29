#ifndef ENGINE_CAMERA_CAMERA_H
#define ENGINE_CAMERA_CAMERA_H

#include "../engine_pch.h"
#include "RTMath.h"

using namespace RTMath;

class BaseCamera
{
public:
	BaseCamera();
	virtual ~BaseCamera();

	void GetViewMatrix(Matrix *ViewMat);

	void SetPos(Vector &vPos);
	void GetPos(Vector *vPos);

	void GetDirection(Vector *vDir, Vector *vUp, Vector *vRight);

	virtual void Update() = 0;
protected:
	RTMath::Matrix m_ViewMat;

	float m_fRotX; // 在局部坐标系下的EULER角(旋转角)
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
	void Update();

	// 设置变化的方向
	void SetMoveDirection(Vector &vMoveDirection);
	void GetMoveDirection(Vector *vMoveDirection);

	void GetRotAngle(float *fRotX, float *fRotY, float *fRotZ);
	void SetRotAngle(float fRotX, float fRotY, float fRotZ);
	void SetRotAngleDelta(float fRotXDelta, float fRotYDelta, float fRotZDelta);

	// 设置变换量
	void SetMoveDelta(float fMoveDelta);

private:
	Vector m_vMoveDirection;
};

#endif