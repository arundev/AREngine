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

	float m_fRotX; // �ھֲ�����ϵ�µ�EULER��(��ת��)
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

	// ���ñ仯�ķ���
	void SetMoveDirection(Vector &vMoveDirection);
	void GetMoveDirection(Vector *vMoveDirection);

	void GetRotAngle(float *fRotX, float *fRotY, float *fRotZ);
	void SetRotAngle(float fRotX, float fRotY, float fRotZ);
	void SetRotAngleDelta(float fRotXDelta, float fRotYDelta, float fRotZDelta);

	// ���ñ任��
	void SetMoveDelta(float fMoveDelta);

private:
	Vector m_vMoveDirection;
};

#endif