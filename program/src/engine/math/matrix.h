#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

namespace math{
class Matrix{
public:
	Matrix();
	~Matrix();

public:
	float m[4][4];
};

Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

}



#endif // ENGINE_MATH_MATRIX_H