#include "camera.h"
#include "../dx11/util_dx11.h"
#include <D3DX10.h>
#include <directxmath.h>

using namespace DirectX;

namespace engine {

BaseCamera::BaseCamera()
{
	m_ViewMat.Identity();

	m_fRotX = 0.0f;
	m_fRotY = 0.0f;
	m_fRotZ = 0.0f;


	m_vPos.Set(0.0f, 0.0f, 0.0f);

	m_vDir.Set(0.0f, 0.0f, 1.0f);
	m_vUp.Set(0.0f, 1.0f, 0.0f);
	m_vRight.Set(1.0f, 0.0f, 0.0f);
}

BaseCamera::~BaseCamera()
{

}

void BaseCamera::GetViewMatrix(engine::Matrix *ViewMat)
{
	if (!ViewMat)
		return;

	memcpy(ViewMat, &m_ViewMat, sizeof(engine::Matrix));

}

void BaseCamera::SetPos(engine::Vector &vPos)
{
	memcpy(&m_vPos, &vPos, sizeof(engine::Vector));
}

void BaseCamera::GetPos(engine::Vector *vPos)
{
	if (!vPos)
		return;
	memcpy(vPos, &m_vPos, sizeof(engine::Vector));
}

void BaseCamera::GetDirection(engine::Vector *vDir, engine::Vector *vUp, engine::Vector *vRight)
{
	if (vDir)
		memcpy(vDir, &m_vDir, sizeof(engine::Vector));

	if (vUp)
		memcpy(vUp, &m_vUp, sizeof(engine::Vector));

	if (vRight)
		memcpy(vRight, &m_vRight, sizeof(engine::Vector));
}


/*----------------------------------------------------------------
class FreeCamera
----------------------------------------------------------------*/
FreeCamera::FreeCamera()
{
	m_vMoveDirection.Set(0.0f, 0.0f, 1.0f);
}

FreeCamera::~FreeCamera()
{
}

void FreeCamera::SetMoveDirection(engine::Vector &vMoveDirection)
{
	memcpy(&m_vMoveDirection, &vMoveDirection, sizeof(engine::Vector));

}

void FreeCamera::GetMoveDirection(engine::Vector *vMoveDirection)
{
	if (vMoveDirection)
		memcpy(vMoveDirection, &m_vMoveDirection, sizeof(engine::Vector));

}

void FreeCamera::GetRotAngle(float *fRotX, float *fRotY, float *fRotZ)
{
	if (fRotX)
		*fRotX = m_fRotX;
	if (fRotY)
		*fRotY = m_fRotY;
	if (fRotZ)
		*fRotZ = m_fRotZ;
}

void FreeCamera::SetRotAngle(float fRotX, float fRotY, float fRotZ)
{
	m_fRotX = fRotX;
	m_fRotY = fRotY;
	m_fRotZ = fRotZ;
}

void FreeCamera::SetRotAngleDelta(float fRotXDelta, float fRotYDelta, float fRotZDelta)
{

	m_fRotX += fRotXDelta;
	m_fRotY += fRotYDelta;
	m_fRotZ += fRotZDelta;

	if (m_fRotX > RT2PI)
		m_fRotX -= (float)RT2PI;
	else if(m_fRotX < -RT2PI) 
		m_fRotX += (float)RT2PI;

	if (m_fRotY > RT2PI)
		m_fRotY -= (float)RT2PI;
	else if
		(m_fRotY < -RT2PI) m_fRotY += (float)RT2PI;

	if (m_fRotZ > RT2PI)
		m_fRotZ -= (float)RT2PI;
	else if (m_fRotZ < -RT2PI) 
		m_fRotZ += (float)RT2PI;
}

void FreeCamera::SetMoveDelta(float vMoveDelta)
{
	m_vPos += m_vMoveDirection * vMoveDelta;
}


void FreeCamera::Update()
{

	Quaternion  qFrame(0, 0, 0, 1);
	qFrame.MakeFromEuler(m_fRotX, m_fRotY, m_fRotZ);
	m_ViewMat.Identity();
	qFrame.GetMatrix(&m_ViewMat);

	m_vRight.x = m_ViewMat._11;
	m_vRight.y = m_ViewMat._21;
	m_vRight.z = m_ViewMat._31;

	m_vUp.x = m_ViewMat._12;
	m_vUp.y = m_ViewMat._22;
	m_vUp.z = m_ViewMat._32;

	m_vDir.x = m_ViewMat._13;
	m_vDir.y = m_ViewMat._23;
	m_vDir.z = m_ViewMat._33;

	m_ViewMat._41 = -(m_vRight * m_vPos);
	m_ViewMat._42 = -(m_vUp * m_vPos);
	m_ViewMat._43 = -(m_vDir * m_vPos);
	m_ViewMat._44 = 1.0f;
}


}