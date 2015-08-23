#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

class Matrix{
public:
	Matrix();
	~Matrix();

	void Identify();

public:
	float m[4][4];
};




#endif // ENGINE_MATH_MATRIX_H