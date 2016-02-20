#ifndef ENGINE_MATH_MATRIX_INL

namespace engine_math{
	template<typename T>
	Matrix<T>& Matrix<T>::operator + (const Matrix<T>& mat){
		this->m11_ += mat.m11_;
		this->m12_ += mat.m12_;
		this->m13_ += mat.m13_;
		this->m14_ += mat.m14_;

		this->m21_ += mat.m21_;
		this->m22_ += mat.m22_;
		this->m23_ += mat.m23_;
		this->m24_ += mat.m24_;

		this->m31_ += mat.m31_;
		this->m32_ += mat.m32_;
		this->m33_ += mat.m33_;
		this->m34_ += mat.m34_;

		this->m41_ += mat.m41_;
		this->m42_ += mat.m42_;
		this->m43_ += mat.m43_;
		this->m44_ += mat.m44_;

		return *this;
	}

	template<typename T>
	Matrix<T>& Matrix<T>::operator - (const Matrix<T>& mat){
		this->m11_ -= mat.m11_;
		this->m12_ -= mat.m12_;
		this->m13_ -= mat.m13_;
		this->m14_ -= mat.m14_;

		this->m21_ -= mat.m21_;
		this->m22_ -= mat.m22_;
		this->m23_ -= mat.m23_;
		this->m24_ -= mat.m24_;

		this->m31_ -= mat.m31_;
		this->m32_ -= mat.m32_;
		this->m33_ -= mat.m33_;
		this->m34_ -= mat.m34_;

		this->m41_ -= mat.m41_;
		this->m42_ -= mat.m42_;
		this->m43_ -= mat.m43_;
		this->m44_ -= mat.m44_;

		return *this;
	}

	template<typename T>
	Matrix<T>& Matrix<T>::operator* (const Matrix<T>& mat){
		this->m11_ = this->m11_*mat.m11_ + this->m12_ * mat.m21_ + this->m13_*mat.m31_ + this->m14_*mat.m41_;
		this->m12_ = this->m11_*mat.m12_ + this->m12_ * mat.m22_ + this->m13_*mat.m32_ + this->m14_*mat.m42_;
		this->m13_ = this->m11_*mat.m13_ + this->m12_ * mat.m23_ + this->m13_*mat.m33_ + this->m14_*mat.m43_;
		this->m14_ = this->m11_*mat.m14_ + this->m12_ * mat.m24_ + this->m13_*mat.m34_ + this->m14_*mat.m44_;

		this->m21_ = this->m21_*mat.m11_ + this->m22_ * mat.m21_ + this->m23_*mat.m31_ + this->m24_*mat.m41_;
		this->m22_ = this->m21_*mat.m12_ + this->m22_ * mat.m22_ + this->m33_*mat.m32_ + this->m14_*mat.m42_;
		this->m23_ = this->m21_*mat.m13_ + this->m22_ * mat.m23_ + this->m33_*mat.m33_ + this->m14_*mat.m43_;
		this->m24_ = this->m21_*mat.m14_ + this->m22_ * mat.m24_ + this->m33_*mat.m34_ + this->m14_*mat.m44_;

		this->m31_ = this->m31_*mat.m11_ + this->m32_ * mat.m21_ + this->m33_*mat.m31_ + this->m34_*mat.m41_;
		this->m32_ = this->m31_*mat.m12_ + this->m22_ * mat.m22_ + this->m33_*mat.m32_ + this->m34_*mat.m42_;
		this->m33_ = this->m31_*mat.m13_ + this->m22_ * mat.m23_ + this->m33_*mat.m33_ + this->m34_*mat.m43_;
		this->m34_ = this->m31_*mat.m14_ + this->m22_ * mat.m24_ + this->m33_*mat.m34_ + this->m34_*mat.m44_;

		this->m41_ = this->m41_*mat.m11_ + this->m42_ * mat.m21_ + this->m43_*mat.m31_ + this->m44_*mat.m41_;
		this->m42_ = this->m41_*mat.m12_ + this->m42_ * mat.m22_ + this->m43_*mat.m32_ + this->m44_*mat.m42_;
		this->m43_ = this->m41_*mat.m13_ + this->m42_ * mat.m23_ + this->m43_*mat.m33_ + this->m44_*mat.m43_;
		this->m44_ = this->m41_*mat.m14_ + this->m42_ * mat.m24_ + this->m43_*mat.m34_ + this->m44_*mat.m44_;

		return *this;
	}


}

#endif ENGINE_MATH_MATRIX_INL