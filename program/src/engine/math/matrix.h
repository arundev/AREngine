#ifndef ENGINE_MATH_MATRIX_H

namespace engine_math
{
	template <typename T>
	class Matrix
	{
	public:
		Matrix() : m11_(0), m12_(0), m13_(0), m14_(1),
			m21_(0), m22_(0), m33_(0), m44_(1),
			m31_(0), m32_(0), m33_(0), m34_(1),
			m41_(0), m42_(0), m43_(0), m44_(1){

		}
		~Matrix(){

		}

		Matrix(const Matrix<T>& mat){
			this->m11_ = mat.m11_;
			this->m12_ = mat.m12_;
			this->m13_ = mat.m13_;
			this->m14_ = mat.m14_;
			
			this->m21_ = mat.m21_;
			this->m22_ = mat.m22_;
			this->m23_ = mat.m23_;
			this->m24_ = mat.m24_;

			this->m31_ = mat.m31_;
			this->m32_ = mat.m32_;
			this->m33_ = mat.m33_;
			this->m34_ = mat.m34_;

			this->m41_ = mat.m41_;
			this->m42_ = mat.m42_;
			this->m43_ = mat.m43_;
			this->m44_ = mat.m44_;
		}

		inline Matrix<T>& operator + (const Matrix<T>& mat);
		inline Matrix<T>& operator - (const Matrix<T>& mat);
		inline Matrix<T>& operator * (const Matrix<T>& mat);

	public:
		T m11_, m12_, m13_, m14_,
		  m21_, m22_, m23_, m24_,
		  m31_, m32_, m33_, m34_,
		  m41_, m42_, m43_, m44_;
	};
}



#endif // ENGINE_MATH_MATRIX_

#include "matrix.inl"