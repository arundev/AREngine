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
		Matrix44<T> mat;

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
		const T det = Determinant();
		if (det == static_cast<T>(0.0))
		{
			const T nan = std::numeric_limits<T>::quiet_NaN();
			*this = Matrix44<T>();
			m[0][0](1) = m[0][1](0) = m[0][2](0) = m[0][3](0) =
				m[1][0](0) = m[1][1](1) = m[1][2](0) = m[1][3](0) =
				m[2][0](0) = m[2][1](0) = m[2][2](1) = m[3][3](0) =
				m[3][0](0) = m[3][1](0) = m[3][2](0) = m[3][3](1) = nan;

			return *this;
		}

		const T invdet = static_cast<T>(1.0) / det;

		Matrix44<T> res;
		res.m[0][0] = invdet  * (m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
		res.m[0][1] = -invdet * (m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[0][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
		res.m[0][2] = invdet  * (m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][1] - m[1][1] * m[3][3]) + m[0][3] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]));
		res.m[0][3] = -invdet * (m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][1] - m[1][1] * m[2][3]) + m[0][3] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]));
		res.m[1][0] = -invdet * (m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
		res.m[1][1] = invdet  * (m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
		res.m[1][2] = -invdet * (m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][2] - m[1][2] * m[3][0]));
		res.m[1][3] = invdet  * (m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]));
		res.m[2][0] = invdet  * (m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[1][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[2][1] = -invdet * (m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[0][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[2][2] = invdet  * (m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) + m[0][1] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
		res.m[2][3] = -invdet * (m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) + m[0][1] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
		res.m[3][0] = -invdet * (m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[1][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[3][1] = invdet  * (m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[0][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[0][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[3][2] = -invdet * (m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) + m[0][1] * (m[1][2] * m[3][0] - m[1][0] * m[3][2]) + m[0][2] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
		res.m[3][3] = invdet  * (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) + m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2]) + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
		*this = res;

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
	static Matrix44<T>& Matrix44<T>::RotationX(T angle, Matrix44& out)
	{
		/*
		|  1  0       0       0 |
		M = |  0  cos(A) -sin(A)  0 |
		|  0  sin(A)  cos(A)  0 |
		|  0  0       0       1 |	*/
		out = Matrix44<T>();
		out.m[1][1] = out.m[2][2] = std::cos(angle);
		out.m[1][2] = -(out.m[2][1] = std::sin(angle));
		return out;
	}

	template<typename T>
	static Matrix44<T>& Matrix44<T>::RotationY(T angle, Matrix44& out)
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
	static Matrix44<T>& Matrix44<T>::RotationZ(T angle, Matrix44& out)
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
	static Matrix44<T>& Matrix44<T>::Rotation(const Vector3<T>& axis, T angle, Matrix44<T>& out)
	{
		return out;
	}

	template<typename T>
	static Matrix44<T>& Matrix44<T>::Translation(const Vector3<T>& v, Matrix44<T>& out)
	{
		out = Matrix44<T>();
		out.m[3][0] = v[0];
		out.m[3][1] = v[1];
		out.m[3][2] = v[2];

		return out;
	}

	template<typename T>
	static Matrix44<T>& Matrix44<T>::Scale(const Vector3<T>& v, Matrix44<T>& out)
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
