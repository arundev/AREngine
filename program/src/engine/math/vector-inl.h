#ifndef ENGINE_MATH_VECTOR_INL_H
#define ENGINE_MATH_VECTOR_INL_H

#include "vector.h"

namespace NMath
{
	template<typename T>
	T Vector3<T>::Length()
	{
		return sqr(x_*x_ + y_*y_ + z_*z_);
	}

	template<typename T>
	Vector3<T>& Vector3<T>::Normalize()
	{
		T len = Length();
		if (len > 0)
		{
			T inv_len = 1 / len;
			x_ *= inv_len;
			y_ *= inv_len;
			z_ *= inv_len;
		}

		return *this;
	}

	template<typename T>
	T Vector3<T>::Dot(const Vector3<T>& v)const
	{
		return x_*v.x_ + y_*v.y_ + z_*v.z_;
	}

	template<typename T>
	Vector3<T> Vector3<T>::Cross(const Vector3<T>& v)const
	{
		return Vector3<T>(
			y_*v.z_ - z_*v.y,
			z_*v.x_ - _x*v.z_,
			x_*v.y_ - y*v.x_);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator + (const Vector3<T>& v)const
	{
		return Vector3<T>(x_ + v.x_, y_ + v.y_, z_ + v.z_);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator - (const Vector3<T>& v)const
	{
		return Vector3<T>(x_ - v.x_, y_ - v.y_, z_ - v.z_);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator * (const T& v)const
	{
		return Vector3<T>(x_*v, y_*v, z_*v);
	}

	template<typename T>
	const T& Vector3<T>::operator [](uint8_t i)const
	{
		return (&x)[i];
	}

	template<typename T>
	std::ostream& operator << (std::ostream& s, const Vector3<T>& v)
	{
		return s << '(' << v.x_ << ',' << v.y_ << ',' << v.z_ << ')';
	}

}

#endif ENGINE_MATH_VECTOR_INL_H