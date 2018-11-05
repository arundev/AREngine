#include "math.h"


namespace engine {
	inline void Vector::Set(float _x, float _y, float _z, float _w/* =1.0f */)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	inline float Vector::GetLength()const
	{
		float f = 0;

		if (!gIsUseASM)
		{
			f = (float)sqrt(x*x + y * y + z * z);
		}
		//使用汇编
		else
		{

		}

		return f;
	}

	inline float Vector::GetSqrLength()const
	{
		return (x*x + y * y + z * z);
	}

	inline void Vector::Negate()
	{
		x = -x;  y = -y;  z = -z;
	}

	inline void Vector::Normalize()
	{
		if (!gIsUseASM)
		{
			float f = (float)sqrt(x*x + y * y + z * z);

			if (f != 0.0f)
			{
				x /= f; y /= f; z /= f;
			}
		}
		//使用汇编
		else
		{
		}
	}

	inline FLOAT Vector::AngleWith(const Vector& v)const
	{
		return (float)acos(((*this) * v) / (this->GetLength()*v.GetLength()));
	}

	inline void Vector::RotateWith(const Matrix& m)
	{
		float _x = x * m._11 + y * m._21 + z * m._31;
		float _y = x * m._12 + y * m._22 + z * m._32;
		float _z = x * m._13 + y * m._23 + z * m._33;
	}

	inline void Vector::InvRotateWith(const Matrix& m)
	{
		float _x = x * m._11 + y * m._12 + z * m._13;
		float _y = x * m._21 + y * m._22 + z * m._23;
		float _z = x * m._31 + y * m._32 + z * m._33;
		x = _x;   y = _y;   z = _z;
	}

	inline void Vector::Difference(const Vector &v1, const Vector &v2)
	{
		x = v2.x - v1.x;
		y = v2.y - v1.y;
		z = v2.z - v1.z;
		w = 1.0f;
	}

}

