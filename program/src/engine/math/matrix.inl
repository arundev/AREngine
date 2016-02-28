#ifndef ENGINE_MATH_MATRIX_INL

namespace engine_math{
	template<typename T>
	Matrix<T>& Matrix<T>::operator + (const Matrix<T>& mat){
		for (int i = 0; i < row_;i++){
			for (int j = 0; j < col_;j++){
				this->m[i][j] += mat.m_[i][j];
			}
		}

		return *this;
	}

	template<typename T>
	Matrix<T>& Matrix<T>::operator - (const Matrix<T>& mat){
		for (int i = 0; i < row_; i++){
			for (int j = 0; j < col_; j++){
				this->m[i][j] -= mat.m_[i][j];
			}
		}

		return *this;
	}

	template<typename T>
	Matrix<T>& Matrix<T>::operator* (const Matrix<T>& mat){
		this->m[0][0] = this->m[0][0]*mat.m[0][0] + this->m[0][1] * mat.m[1][0] + this->m[0][2]*mat.m[2][0] + this->m[0][3]*mat.m[3][0];
		this->m[0][1] = this->m[0][0]*mat.m[0][1] + this->m[0][1] * mat.m[1][1] + this->m[0][2]*mat.m[2][1] + this->m[0][3]*mat.m[3][1];
		this->m[0][2] = this->m[0][0]*mat.m[0][2] + this->m[0][1] * mat.m[1][2] + this->m[0][2]*mat.m[2][2] + this->m[0][3]*mat.m[3][2];
		this->m[0][3] = this->m[0][0]*mat.m[0][3] + this->m[0][1] * mat.m[1][3] + this->m[0][2]*mat.m[2][3] + this->m[0][3]*mat.m[3][3];

		this->m[1][0] = this->m[1][0]*mat.m[0][0] + this->m[1][1] * mat.m[1][0] + this->m[1][2]*mat.m[2][0] + this->m[1][3]*mat.m[3][0];
		this->m[1][1] = this->m[1][0]*mat.m[0][1] + this->m[1][1] * mat.m[1][1] + this->m[2][2]*mat.m[2][1] + this->m[0][3]*mat.m[3][1];
		this->m[1][2] = this->m[1][0]*mat.m[0][2] + this->m[1][1] * mat.m[1][2] + this->m[2][2]*mat.m[2][2] + this->m[0][3]*mat.m[3][2];
		this->m[1][3] = this->m[1][0]*mat.m[0][3] + this->m[1][1] * mat.m[1][3] + this->m[2][2]*mat.m[2][3] + this->m[0][3]*mat.m[3][3];

		this->m[2][0] = this->m[2][0]*mat.m[0][0] + this->m[2][1] * mat.m[1][0] + this->m[2][2]*mat.m[2][0] + this->m[2][3]*mat.m[3][0];
		this->m[2][1] = this->m[2][0]*mat.m[0][1] + this->m[1][1] * mat.m[1][1] + this->m[2][2]*mat.m[2][1] + this->m[2][3]*mat.m[3][1];
		this->m[2][2] = this->m[2][0]*mat.m[0][2] + this->m[1][1] * mat.m[1][2] + this->m[2][2]*mat.m[2][2] + this->m[2][3]*mat.m[3][2];
		this->m[2][3] = this->m[2][0]*mat.m[0][3] + this->m[1][1] * mat.m[1][3] + this->m[2][2]*mat.m[2][3] + this->m[2][3]*mat.m[3][3];

		this->m[3][0] = this->m[3][0]*mat.m[0][0] + this->m[3][1] * mat.m[1][0] + this->m[3][2]*mat.m[2][0] + this->m[3][3]*mat.m[3][0];
		this->m[3][1] = this->m[3][0]*mat.m[0][1] + this->m[3][1] * mat.m[1][1] + this->m[3][2]*mat.m[2][1] + this->m[3][3]*mat.m[3][1];
		this->m[3][2] = this->m[3][0]*mat.m[0][2] + this->m[3][1] * mat.m[1][2] + this->m[3][2]*mat.m[2][2] + this->m[3][3]*mat.m[3][2];
		this->m[3][3] = this->m[3][0]*mat.m[0][3] + this->m[3][1] * mat.m[1][3] + this->m[3][2]*mat.m[2][3] + this->m[3][3]*mat.m[3][3];

		return *this;
	}


}

#endif ENGINE_MATH_MATRIX_INL