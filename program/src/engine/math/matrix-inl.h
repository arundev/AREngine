#ifndef ENGINE_MATH_MATRIX_INL_H
#define ENGINE_MATH_MATRIX_INL_H

#include "matrix.h"

namespace NMath
{

	template<typename T>
	Matrix44<T>::Matrix44() :
		m[0][0](1), m[0][1](0), m[0][2](0), m[0][3](0),
		m[1][0](0), m[1][1](1), m[1][2](0), m[1][3](0),
		m[2][0](0), m[2][1](0), m[2][2](1), m[3][3](0),
		m[3][0](0), m[3][1](0), m[3][2](0), m[3][3](1),
	{

	}

	template<typename T>
	Matrix44<T>::Matrix44(const Vector3<T>& scale, const Vector3<T>& rotate, const Vector3<T>& translate)
	{
		

		return mat;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::Transpose()
	{
		std::swap(m[0][1], m[1][0]);
		std::swap(m[0][2], m[2][0]);
		std::swap(m[0][3], m[3][0]);
		std::swap(m[1][2], m[2][1]);
		std::swap(m[1][3], m[3][1]);
		std::swap(m[2][2], m[3][2]);

		return *this;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::Inverse()
	{
		Matrix44<4>    mTrans;
		float fTemp[12],  // cofaktors
			  fDet;

		// calculate transposed matrix
		mTrans.TransposeOf(m);

		// Paare für die ersten 8 Kofaktoren
		fTemp[0] = mTrans.m[2][2] * mTrans.m[3][3];
		fTemp[1] = mTrans.m[2][3] * mTrans.m[3][2];
		fTemp[2] = mTrans.m[2][1] * mTrans.m[3][3];
		fTemp[3] = mTrans.m[2][3] * mTrans.m[3][1];
		fTemp[4] = mTrans.m[2][1] * mTrans.m[3][2];
		fTemp[5] = mTrans.m[2][2] * mTrans.m[3][1];
		fTemp[6] = mTrans.m[2][0] * mTrans.m[3][3];
		fTemp[7] = mTrans.m[2][3] * mTrans.m[3][0];
		fTemp[8] = mTrans.m[2][0] * mTrans.m[3][2];
		fTemp[9] = mTrans.m[2][2] * mTrans.m[3][0];
		fTemp[10] = mTrans.m[2][0] * mTrans.m[3][1];
		fTemp[11] = mTrans.m[2][1] * mTrans.m[3][0];

		// Berechne die ersten 8 Kofaktoren
		this->m[0][0] = fTemp[0] * mTrans.m[1][1] + fTemp[3] * mTrans.m[1][2] + fTemp[4] * mTrans.m[1][3];
		this->m[0][0] -= fTemp[1] * mTrans.m[1][1] + fTemp[2] * mTrans.m[1][2] + fTemp[5] * mTrans.m[1][3];
		this->m[0][1] = fTemp[1] * mTrans.m[1][0] + fTemp[6] * mTrans.m[1][2] + fTemp[9] * mTrans.m[1][3];
		this->m[0][1] -= fTemp[0] * mTrans.m[1][0] + fTemp[7] * mTrans.m[1][2] + fTemp[8] * mTrans.m[1][3];
		this->m[0][2] = fTemp[2] * mTrans.m[1][0] + fTemp[7] * mTrans.m[1][1] + fTemp[10] * mTrans.m[1][3];
		this->m[0][2] -= fTemp[3] * mTrans.m[1][0] + fTemp[6] * mTrans.m[1][1] + fTemp[11] * mTrans.m[1][3];
		this->m[0][3] = fTemp[5] * mTrans.m[1][0] + fTemp[8] * mTrans.m[1][1] + fTemp[11] * mTrans.m[1][2];
		this->m[0][3] -= fTemp[4] * mTrans.m[1][0] + fTemp[9] * mTrans.m[1][1] + fTemp[10] * mTrans.m[1][2];
		this->m[1][0] = fTemp[1] * mTrans.m[0][1] + fTemp[2] * mTrans.m[0][2] + fTemp[5] * mTrans.m[0][3];
		this->m[1][0] -= fTemp[0] * mTrans.m[0][1] + fTemp[3] * mTrans.m[0][2] + fTemp[4] * mTrans.m[0][3];
		this->m[1][1] = fTemp[0] * mTrans.m[0][0] + fTemp[7] * mTrans.m[0][2] + fTemp[8] * mTrans.m[0][3];
		this->m[1][1] -= fTemp[1] * mTrans.m[0][0] + fTemp[6] * mTrans.m[0][2] + fTemp[9] * mTrans.m[0][3];
		this->m[1][2] = fTemp[3] * mTrans.m[0][0] + fTemp[6] * mTrans.m[0][1] + fTemp[11] * mTrans.m[0][3];
		this->m[1][2] -= fTemp[2] * mTrans.m[0][0] + fTemp[7] * mTrans.m[0][1] + fTemp[10] * mTrans.m[0][3];
		this->m[1][3] = fTemp[4] * mTrans.m[0][0] + fTemp[9] * mTrans.m[0][1] + fTemp[10] * mTrans.m[0][2];
		this->m[1][3] -= fTemp[5] * mTrans.m[0][0] + fTemp[8] * mTrans.m[0][1] + fTemp[11] * mTrans.m[0][2];

		// Paare für die zweiten 8 Kofaktoren
		fTemp[0] = mTrans.m[0][2] * mTrans.m[1][3];
		fTemp[1] = mTrans.m[0][3] * mTrans.m[1][2];
		fTemp[2] = mTrans.m[0][1] * mTrans.m[1][3];
		fTemp[3] = mTrans.m[0][3] * mTrans.m[1][1];
		fTemp[4] = mTrans.m[0][1] * mTrans.m[1][2];
		fTemp[5] = mTrans.m[0][2] * mTrans.m[1][1];
		fTemp[6] = mTrans.m[0][0] * mTrans.m[1][3];
		fTemp[7] = mTrans.m[0][3] * mTrans.m[1][0];
		fTemp[8] = mTrans.m[0][0] * mTrans.m[1][2];
		fTemp[9] = mTrans.m[0][2] * mTrans.m[1][0];
		fTemp[10] = mTrans.m[0][0] * mTrans.m[1][1];
		fTemp[11] = mTrans.m[0][1] * mTrans.m[1][0];

		// Berechne die zweiten 8 Kofaktoren
		this->m[2][0] = fTemp[0] * mTrans.m[3][1] + fTemp[3] * mTrans.m[3][2] + fTemp[4] * mTrans.m[3][3];
		this->m[2][0] -= fTemp[1] * mTrans.m[3][1] + fTemp[2] * mTrans.m[3][2] + fTemp[5] * mTrans.m[3][3];
		this->m[2][1] = fTemp[1] * mTrans.m[3][0] + fTemp[6] * mTrans.m[3][2] + fTemp[9] * mTrans.m[3][3];
		this->m[2][1] -= fTemp[0] * mTrans.m[3][0] + fTemp[7] * mTrans.m[3][2] + fTemp[8] * mTrans.m[3][3];
		this->m[2][2] = fTemp[2] * mTrans.m[3][0] + fTemp[7] * mTrans.m[3][1] + fTemp[10] * mTrans.m[3][3];
		this->m[2][2] -= fTemp[3] * mTrans.m[3][0] + fTemp[6] * mTrans.m[3][1] + fTemp[11] * mTrans.m[3][3];
		this->m[2][3] = fTemp[5] * mTrans.m[3][0] + fTemp[8] * mTrans.m[3][1] + fTemp[11] * mTrans.m[3][2];
		this->m[2][3] -= fTemp[4] * mTrans.m[3][0] + fTemp[9] * mTrans.m[3][1] + fTemp[10] * mTrans.m[3][2];
		this->m[3][0] = fTemp[2] * mTrans.m[2][2] + fTemp[5] * mTrans.m[2][3] + fTemp[1] * mTrans.m[2][1];
		this->m[3][0] -= fTemp[4] * mTrans.m[2][3] + fTemp[0] * mTrans.m[2][1] + fTemp[3] * mTrans.m[2][2];
		this->m[3][1] = fTemp[8] * mTrans.m[2][3] + fTemp[0] * mTrans.m[2][0] + fTemp[7] * mTrans.m[2][2];
		this->m[3][1] -= fTemp[6] * mTrans.m[2][2] + fTemp[9] * mTrans.m[2][3] + fTemp[1] * mTrans.m[2][0];
		this->m[3][2] = fTemp[6] * mTrans.m[2][1] + fTemp[11] * mTrans.m[2][3] + fTemp[3] * mTrans.m[2][0];
		this->m[3][2] -= fTemp[10] * mTrans.m[2][3] + fTemp[2] * mTrans.m[2][0] + fTemp[7] * mTrans.m[2][1];
		this->m[3][3] = fTemp[10] * mTrans.m[2][2] + fTemp[4] * mTrans.m[2][0] + fTemp[9] * mTrans.m[2][1];
		this->m[3][3] -= fTemp[8] * mTrans.m[2][1] + fTemp[11] * mTrans.m[2][2] + fTemp[5] * mTrans.m[2][0];

		fDet = mTrans.m[0][0]*this->m[0][0] +
			mTrans.m[0][1]*this->m[0][1] +
			mTrans.m[0][2]*this->m[0][2] +
			mTrans.m[0][3]*this->m[0][3];

		fDet = 1 / fDet;

		this->m[0][0] *= fDet;
		this->m[0][1] *= fDet;
		this->m[0][2] *= fDet;
		this->m[0][3] *= fDet;

		this->m[1][0] *= fDet;
		this->m[1][1] *= fDet;
		this->m[1][2] *= fDet;
		this->m[1][3] *= fDet;

		this->m[2][0] *= fDet;
		this->m[2][1] *= fDet;
		this->m[2][2] *= fDet;
		this->m[2][3] *= fDet;

		this->m[3][0] *= fDet;
		this->m[3][1] *= fDet;
		this->m[3][2] *= fDet;
		this->m[3][3] *= fDet;

		return *this;
	}

	template<typename T>
	T Matrix44<T>::Determinant()
	{
		return m[0][0] * m[1][1] * m[2][2] * m[3][3] +
			m[0][1] * m[1][2] * m[2][3] * m[3][0] +
			m[0][2] * m[1][3] * m[2][4] * m[3][1] -
			m[0][1] * m[1][0] * m[2][3] * m[3][2] -
			m[0][2] * m[1][1] * m[2][0] * m[3][3] -
			m[0][3] * m[1][2] * m[2][1] * m[3][0];
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::FromeEulerAngleXYZ(T x, T y, T z)
	{
		Matrix44<T>& _this = *this;

		T cr = std::cos(x);
		T sr = std::sin(x);
		T cp = std::cos(y);
		T sp = std::sin(y);
		T cy = std::cos(z);
		T sy = std::sin(z);

		_this.m[0][0] = cp*cy;
		_this.m[0][1] = cp*sy;
		_this.m[0][2] = -sp;

		T srsp = sr*sp;
		T crsp = cr*sp;

		_this.m[1][0] = srsp*cy - cr*sy;
		_this.m[1][1] = srsp*sy + cr*cy;
		_this.m[1][2] = sr*cp;

		_this.m[2][0] = crsp*cy + sr*sy;
		_this.m[2][1] = crsp*sy - sr*cy;
		_this.m[2][2] = cr*cp;

		return *_this;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator *(const Matrix44<T>& mat)const
	{
		Matrix44<T> ret;

		T *pA = (T*)this;
		T *pB = (T*)&m;
		T *pM = (T*)&ret;

		memset(pM, 0, sizeof(Matrix44<T>));
		for (uint8_t i = 0; i < 4; i++)
		{
			for (uint8_t j = 0; j < 4; j++)
			{
				pM[4 * i + j] += pA[4 * i] * pB[j];
				pM[4 * i + j] += pA[4 * i + 1] * pB[4 + j];
				pM[4 * i + j] += pA[4 * i + 2] * pB[8 + j];
				pM[4 * i + j] += pA[4 * i + 3] * pB[12 + j];
			}
		}

		return ret;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator *=(const Matrix44<T>& mat)
	{
		Matrix44<T> temp = *this * mat;
		memcpy(this->m, &temp.m, sizeof(temp.m));
		return *this;
	}

	template<typename T>
	static Matrix44<T>& Matrix44<T>::SetRotationX(T angle, Matrix44& out)
	{
		/*
		|  1  0       0       0 |
	M = |  0  cos(A) -sin(A)  0 |
		|  0  sin(A)  cos(A)  0 |
		|  0  0       0       1 |	*/
		out = Matrix44<T>();

		float fCos = cosf(angle);
		float fSin = sinf(angle);
		out.m[1][1] = fCos;
		out.m[2][1] = fSin;
		out.m[1][2] = -fSin;
		out.m[2][2] = fCos;

		return out;
	}

	template<typename T>
	static Matrix44<T>& Matrix44<T>::SetRotationY(T angle, Matrix44& out)
	{
		/*
		|  cos(A)  0   sin(A)  0 |
	M = |  0       1   0       0 |
		| -sin(A)  0   cos(A)  0 |
		|  0       0   0       1 |
		*/
		out = Matrix44<T>();
		out.m[0][0] = out.m[2][2] = std::cos(angle);
		out.m[2][0] = -(out.m[0][2] = std::sin(angle));
		return out;
	}

	template<typename T>
	static Matrix44<T>& Matrix44<T>::SetRotationZ(T angle, Matrix44& out)
	{
		/*
		|  cos(A)  -sin(A)   0   0 |
	M = |  sin(A)   cos(A)   0   0 |
		|  0        0        1   0 |
		|  0        0        0   1 |	*/
		out = Matrix44<T>();
		out.m[0][0] = out.m[1][1] = std::cos(angle);
		out.m[0][1] = -(out.m[1][0] = std::sin(angle));
		return out;
	}

	template<typename T>
	static Matrix44<T>& Matrix44<T>::SetRotation(const Vector3<T>& axis, T angle, Matrix44<T>& out)
	{
		out = Matrix44<T>();

		float fCos = cosf(static_cast<float>(angle));
		float fSin = sinf(static_cast<float>(angle));
		float fSum = 1.0f - fCos;

		out.m[0][0] = (axis.x * axis.x) * fSum + fCos;
		out.m[0][1] = (axis.x * axis.y) * fSum - (axis.z * fSin);
		out.m[0][2] = (axis.x * axis.z) * fSum + (axis.y * fSin);

		out.m[1][0] = (axis.y * axis.x) * fSum + (axis.z * fSin);
		out.m[1][1] = (axis.y * axis.y) * fSum + fCos;
		out.m[1][2] = (axis.y * axis.z) * fSum - (axis.x * fSin);

		out.m[2][0] = (axis.z * axis.x) * fSum - (axis.y * fSin);
		out.m[2][1] = (axis.z * axis.y) * fSum + (axis.x * fSin);
		out.m[2][2] = (axis.z * axis.z) * fSum + fCos;

		return out;
	}

	template<typename T>
	static Matrix44<T>& Matrix44<T>::SetTranslation(const Vector3<T>& v, Matrix44<T>& out)
	{
		out = Matrix44<T>();
		out.m[3][0] = v[0];
		out.m[3][1] = v[1];
		out.m[3][2] = v[2];

		return out;
	}

	template<typename T>
	static Matrix44<T>& Matrix44<T>::SetScale(const Vector3<T>& v, Matrix44<T>& out)
	{
		out = Matrix44<T>();
		out.m[0][0] = v[0];
		out.m[1][1] = v[1];
		out.m[2][2] = v[2];

		return out;
	}

	template<typename T>
	static Matrix44<T>& Matrix44<T>::GetRotationMatrix(const Vector3<T>& from, const Vector3<T>& to, Matrix44<T>& out)
	{
		return out;
	}

}

#endif
