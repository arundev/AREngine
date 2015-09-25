#ifndef ENGINE_MATH_VECTOR_H
#define ENGINE_MATH_VECTOR_H

#include <cstdint>
#include <iostream>

#ifdef __cplusplus
#include <cmath>
#else
#include <math.h>
#endif

class Matrix;

class Vector
{
public:
	Vector();
	Vector(float fx, float fy, float fz, float fw=1.0f);
	~Vector();

	Vector operator*(const Matrix& m);
	Vector& operator*=(const Matrix& m);

public:
	float x_, y_, z_, w_;
};

namespace NMath
{
	template<typename T>
	class Vector3
	{
	public:
		Vector3():x_(T(0)), y_(T(0)), z_(T(0)){}
		Vector3(const T& v) :x_(v), y_(v), z_(v){}
		Vector3(T x, T y, T z) :x_(x), y_(y), z_(z){}

		T Length();
		Vector3<T>& Normalize();
		T Dot(const Vector3<T>& v)const;
		Vector3<T> Cross(const Vector3<T>& v)const;
		Vector3<T> operator + (const Vector3<T>& v)const;
		Vector3<T> operator - (const Vector3<T>& v)const;
		Vector3<T> operator * (const T& v)const;
		const T& operator [](uint8_t i)const;
		friend std::ostream& operator << (std::ostream& s, const Vector3<T>& v);

	public:
		T x_, y_, z_;
	};

	typedef Vector3<float> Vector3f;
	typedef Vector3<int> Vector3i;
}

#endif // ENGINE_MATH_VECTOR_H


#include "vector-inl.h"