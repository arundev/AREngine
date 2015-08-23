#ifndef ENGINE_MATH_VECTOR_H
#define ENGINE_MATH_VECTOR_H

namespace math{
	class Vector
	{
	public:
		Vector();
		Vector(float fx, float fy, float fz, float fw);
		~Vector();

	public:
		float x_, y_, z_, w_;
	};

	Vector::Vector()
	{
	}

	Vector::~Vector()
	{
	}
}




#endif // ENGINE_MATH_VECTOR_H