#include "math.h"

namespace engine_math {

	inline void Ray::Set(Vector vcOrig, Vector vcDir)
	{
		m_vcOrig = vcOrig;
		m_vcDir = vcDir;
	}

	inline void Ray::DeTransform(const Matrix &_m)
	{
		Matrix mInv;
		Matrix m = _m;
		// invert translation
		m_vcOrig.x -= m._41;
		m_vcOrig.y -= m._42;
		m_vcOrig.z -= m._43;

		// delete it from matrix
		m._41 = m._42 = m._43 = 0.0f;
		m._44 = 1.0f;
		// invert matrix and applay to ray
		mInv.InverseOf(m);
		m_vcOrig = m_vcOrig * mInv;
		m_vcDir = m_vcDir * mInv;
	}

}
