#include "math.h"


namespace engine_math {

	inline void Plane::Set(const Vector &vN, const Vector &vP)
	{
		m_fD = -(vN * vP);
		m_vcN = vN;
		m_vcPoint = vP;
	}

	inline void Plane::Set(const Vector &vN, const Vector &vP, float d)
	{
		m_vcN = vN;
		m_vcPoint = vP;
		m_fD = d;
	}

	inline void Plane::Set(const Vector &v0, const Vector &v1, const Vector &v2)
	{
		Vector vcEdge1 = v1 - v0;
		Vector vcEdge2 = v2 - v0;

		m_vcN.Cross(vcEdge1, vcEdge2);
		m_vcN.Normalize();
		m_fD = -(m_vcN * v0);
		m_vcPoint = v0;
	}

	inline float Plane::Distance(const Vector &m_vcPoint)
	{
		return (_fabs((m_vcN * m_vcPoint) - m_fD));
	}

	inline int Plane::Classify(const Vector &m_vcPoint)
	{
		float f = (m_vcPoint * m_vcN) + m_fD;

		if (f >  0.00001) return FRONT;
		if (f < -0.00001) return BACK;
		return PLANAR;
	}
}