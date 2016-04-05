#ifndef ENGINE_MATH_MATRIX_H

namespace engine_math
{
	template <typename T>
	class Matrix
	{
	public:
		Matrix() : m[0][0](0), m[0][1](0), m[0][2](0), m[0][3](1),
			m[1][0](0), m[1][1](0), m[1][2](0), m[1][3](1),
			m[2][0](0), m[2][1](0), m[2][2](0), m[2][3](1),
			m[3][0](0), m[3][1](0), m[3][2](0), m[3][3](1)
		{

		}
		~Matrix(){

		}

		Matrix(const Matrix<T>& mat){
			memcpy(this->m, m.m, sizeof(T)*row_*col_);
		}

		inline Matrix<T>& operator + (const Matrix<T>& mat);
		inline Matrix<T>& operator - (const Matrix<T>& mat);
		inline Matrix<T>& operator * (const Matrix<T>& mat);

	public:
		//T m11_, m12_, m13_, m14_,
		//  m21_, m22_, m23_, m24_,
		//  m31_, m32_, m33_, m34_,
		//  m41_, m42_, m43_, m44_;
		int row_ = 4;
		int col_ = 4
		T m[row_][col_];
	};
}



#endif // ENGINE_MATH_MATRIX_

#include "matrix.inl"