#ifndef ENGINE_MATH_VECTOR_H
#define ENGINE_MATH_VECTOR_H

class Matrix;

class Vector
{
public:
	Vector();
	Vector(float fx, float fy, float fz, float fw=1.0f);
	~Vector();

	Vector& operator*=(const Matrix& m);

public:
	float x_, y_, z_, w_;
};




#endif // ENGINE_MATH_VECTOR_H