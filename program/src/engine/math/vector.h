#ifndef ENGINE_MATH_VECTOR_H
#define ENGINE_MATH_VECTOR_H

namespace math{
	class Vector
	{
	public:
		Vector();
		~Vector();

	public:
		float x, y, z;
	};

	Vector::Vector()
	{
	}

	Vector::~Vector()
	{
	}
}




#endif // ENGINE_MATH_VECTOR_H