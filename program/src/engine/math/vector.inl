#ifndef ENGINE_MATH_VECTOR_INL

namespace engine_math
{
	// Vector4
	template<typename T>
	inline T Vector4<T>::GetLength(){
		return (T)sqrt(x_*x_ + y_*y_ + z_*z_);
	}

	template<typename T>
	inline Vector4<T>& Vector4<T>::operator +(const Vector4<T>& vec){
		this->x_ += vec.x_;
		this->y_ += vec.y_;
		this->z_ += vec.z_;

		return *this;
	}

	template<typename T>
	inline Vector4<T>& Vector4<T>::operator -(const Vector4<T>& vec){
		this->x_ -= vec.x_;
		this->y_ -= vec.y_;
		this->z_ -= vec.z_;

		return *this;
	}

	// Vector3
	template<typename T>
	inline T Vector3<T>::GetLength(){
		return (T)sqrt(x_*x_ + y_*y_ + z_*z_);
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator +(const Vector3<T>& vec){
		this->x_ += vec.x_;
		this->y_ += vec.y_;
		this->z_ += vec.z_;

		return *this;
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator -(const Vector3<T>& vec){
		this->x_ -= vec.x_;
		this->y_ -= vec.y_;
		this->z_ -= vec.z_;

		return *this;
	}

	// Vector2
	template<typename T>
	inline T Vector2<T>::GetLength(){
		return (T)sqrt(x_*x_ + y_*y_);
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::operator +(const Vector2<T>& vec){
		this->x_ += vec.x_;
		this->y_ += vec.y_;

		return *this;
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::operator -(const Vector2<T>& vec){
		this->x_ -= vec.x_;
		this->y_ -= vec.y_;

		return *this;
	}
}



#endif // ENGINE_MATH_VECTOR_INL