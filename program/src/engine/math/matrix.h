#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

#include "vector.h"

#ifdef __cplusplus
#include <cmath>
#else
#include <math.h>
#endif

class Matrix{
public:
	Matrix();
	~Matrix();

	void Identify();

public:
	float m[4][4];
};

namespace NMath
{
	template<typename T>
	class Matrix44 
	{
	public:
		Matrix44();
		Matrix44(const Vector3<T>& scale, const Vector3<T>& rotate, const Vector3<T>& translate);

		Matrix44& Transpose();
		Matrix44& Inverse();
		T Determinant();
		Matrix44& FromeEulerAngleXYZ(T x, T y, T z);

		Matrix44& operator *(const Matrix44& mat)const;
		Matrix44& operator *=(const Matrix44& mat);

		static Matrix44& SetRotationX(T angle, Matrix44& out);
		static Matrix44& SetRotationY(T angle, Matrix44& out);
		static Matrix44& SetRotationZ(T angle, Matrix44& out);
		static Matrix44& SetRotation(const Vector3<T>& axis, T angle, Matrix44& out);
		static Matrix44& SetTranslation(const Vector3<T>& v, Matrix44& out);
		static Matrix44& SetScale(const Vector3<T>& v, Matrix44& out);
		static Matrix44& GetRotationMatrix(const Vector3<T>& from, const Vector3<T>& to, Matrix44& out);

	public:
		T m[4][4];
	};

	typedef Matrix44<float> Matrix44F;
	typedef Matrix44<int> Matrix44I;
}

#endif // ENGINE_MATH_MATRIX_H

#include "matrix-inl.h"