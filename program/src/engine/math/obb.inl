#include "math.h"


namespace engine {

	inline void Obb::DeTransform(const Obb &obb, const Matrix &m)
	{
		Matrix mat = m;
		Vector vcT;

		// erase translation from mat
		vcT.Set(mat._41, mat._42, mat._43);
		mat._41 = mat._42 = mat._43 = 0.0f;

		// rotate center and axis to matrix coord.-space
		this->m_vcCenter = mat * obb.m_vcCenter;
		this->m_vcA0 = mat * obb.m_vcA0;
		this->m_vcA1 = mat * obb.m_vcA1;
		this->m_vcA2 = mat * obb.m_vcA2;

		// set translation
		this->m_vcCenter += vcT;

		// copy axis length
		m_fA0 = obb.m_fA0;
		m_fA1 = obb.m_fA1;
		m_fA2 = obb.m_fA2;
	}

}