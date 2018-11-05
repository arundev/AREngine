#include "math.h"

namespace engine {
	inline void Matrix::Identity()
	{
		float *f = (float*)&this->_11;
		memset(f, 0, sizeof(Matrix));
		_11 = _22 = _33 = _44 = 1.0f;
	}

	inline void Matrix::RotaX(float a)
	{
		float fCos = cosf(a);
		float fSin = sinf(a);

		_22 = fCos;
		_23 = fSin;
		_32 = -fSin;
		_33 = fCos;

		_11 = _44 = 1.0f;
		_12 = _13 = _14 = _21 = _24 = _31 = _34 = _41 = _42 = _43 = 0.0f;
	}

	inline void Matrix::RotaY(float a)
	{
		float fCos = cosf(a);
		float fSin = sinf(a);

		_11 = fCos;
		_13 = -fSin;
		_31 = fSin;
		_33 = fCos;

		_22 = _44 = 1.0f;
		_12 = _23 = _14 = _21 = _24 = _32 = _34 = _41 = _42 = _43 = 0.0f;
	}

	inline void Matrix::RotaZ(float a)
	{
		float fCos = cosf(a);
		float fSin = sinf(a);

		_11 = fCos;
		_12 = fSin;
		_21 = -fSin;
		_22 = fCos;

		_33 = _44 = 1.0f;
		_13 = _14 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = 0.0f;
	}

	inline void Matrix::Rota(const Vector &vc)
	{
		float sr, sp, sy, cr, cp, cy;

		Identity();

		sy = sinf(vc.z);
		cy = cosf(vc.z);
		sp = sinf(vc.y);
		cp = cosf(vc.y);
		sr = sinf(vc.x);
		cr = cosf(vc.x);

		_11 = cp * cy;
		_12 = cp * sy;
		_13 = -sp;
		_21 = sr * sp*cy + cr * -sy;
		_22 = sr * sp*sy + cr * cy;
		_23 = sr * cp;
		_31 = (cr*sp*cy + -sr * -sy);
		_32 = (cr*sp*sy + -sr * cy);
		_33 = cr * cp;
	}

	inline void Matrix::Rota(float x, float y, float z)
	{
		Rota(Vector(x, y, z));
	}

	inline void Matrix::RotaArbi(const Vector &_vcAxis, float a)
	{
		Vector vcAxis = _vcAxis;
		float fCos = cosf(a);
		float fSin = sinf(a);
		float fSum = 1.0f - fCos;

		if (vcAxis.GetSqrLength() != 1.0)
			vcAxis.Normalize();

		_11 = (vcAxis.x * vcAxis.x) * fSum + fCos;
		_12 = (vcAxis.x * vcAxis.y) * fSum - (vcAxis.z * fSin);
		_13 = (vcAxis.x * vcAxis.z) * fSum + (vcAxis.y * fSin);

		_21 = (vcAxis.y * vcAxis.x) * fSum + (vcAxis.z * fSin);
		_22 = (vcAxis.y * vcAxis.y) * fSum + fCos;
		_23 = (vcAxis.y * vcAxis.z) * fSum - (vcAxis.x * fSin);

		_31 = (vcAxis.z * vcAxis.x) * fSum - (vcAxis.y * fSin);
		_32 = (vcAxis.z * vcAxis.y) * fSum + (vcAxis.x * fSin);
		_33 = (vcAxis.z * vcAxis.z) * fSum + fCos;

		_14 = _24 = _34 = _41 = _42 = _43 = 0.0f;
		_44 = 1.0f;
	}

	inline void Matrix::ApplyInverseRota(Vector *pvc)
	{
		pvc->x = pvc->x * _11 + pvc->y * _12 + pvc->z * _13;
		pvc->y = pvc->x * _21 + pvc->y * _22 + pvc->z * _23;
		pvc->z = pvc->x * _31 + pvc->y * _32 + pvc->z * _33;
		pvc->w = 1.0f;
	}

	inline void Matrix::Translate(float dx, float dy, float dz)
	{
		_41 = dx;
		_42 = dy;
		_43 = dz;
	}

	inline void Matrix::Scaling(float fX, float fY, float fZ)
	{
		_11 = fX;
		_22 = fY;
		_33 = fZ;
	}
	inline void Matrix::SetTranslation(Vector vc, bool b)
	{
		if (b) Identity();
		_41 = vc.x;
		_42 = vc.y;
		_43 = vc.z;
	}

	inline Vector Matrix::GetTranslation()
	{
		return Vector(_41, _42, _43);
	}

	inline void Matrix::Billboard(Vector vcPos,
		Vector vcDir,
		Vector vcWorldUp)
	{
		Vector vcUp, vcRight;
		float  fAngle = 0.0f;

		fAngle = vcWorldUp * vcDir;

		vcUp = vcWorldUp - (vcDir * fAngle);
		vcUp.Normalize();

		vcRight.Cross(vcUp, vcDir);

		_11 = vcRight.x;
		_21 = vcUp.x;
		_31 = vcDir.x;
		_12 = vcRight.y;
		_22 = vcUp.y;
		_32 = vcDir.y;
		_13 = vcRight.z;
		_23 = vcUp.z;
		_33 = vcDir.z;

		_41 = vcPos.x;
		_42 = vcPos.y;
		_43 = vcPos.z;

		_14 = 0.0f;
		_24 = 0.0f;
		_34 = 0.0f;
		_44 = 1.0f;
	}

	inline void Matrix::LookAt(Vector vcPos, Vector vcLookAt, Vector vcWorldUp)
	{
		Vector vcDir = vcLookAt - vcPos;
		Vector vcUp, vcRight;
		float  fAngle = 0.0f;

		vcDir.Normalize();

		fAngle = vcWorldUp * vcDir;

		vcUp = vcWorldUp - (vcDir * fAngle);
		vcUp.Normalize();

		vcRight.Cross(vcUp, vcDir);

		_11 = vcRight.x; _21 = vcUp.x; _31 = vcDir.x;
		_12 = vcRight.y; _22 = vcUp.y; _32 = vcDir.y;
		_13 = vcRight.z; _23 = vcUp.z; _33 = vcDir.z;

		_41 = vcPos.x;
		_42 = vcPos.y;
		_43 = vcPos.z;

		_14 = 0.0f; _24 = 0.0f; _34 = 0.0f; _44 = 1.0f;
	}

	void Matrix::TransposeOf(const Matrix &m)
	{
		_11 = m._11;
		_21 = m._12;
		_31 = m._13;
		_41 = m._14;

		_12 = m._21;
		_22 = m._22;
		_32 = m._23;
		_42 = m._24;

		_13 = m._31;
		_23 = m._32;
		_33 = m._33;
		_43 = m._34;

		_14 = m._41;
		_24 = m._42;
		_34 = m._43;
		_44 = m._44;
	}

}