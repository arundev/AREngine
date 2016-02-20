#ifndef ENGINE_MATH_VECTOR_H

#include <math.h>

namespace engine_math{

	// Vector4
	template<typename T>
	class Vector4
	{
	public:
		Vector4(T x = 0, T y = 0, T z = 0, T w = 1) :x_(x), y_(y), z_(z), w_(w){

		}

		Vector4(const Vector4<T>& vec){
			x_ = vec.x_;
			y_ = vec.y_;
			z_ = vec.z_;
			w_ = vec.w_;
		}

		inline T GetLength();
		inline Vector4<T>& operator + (const Vector4<T>& vec);
		inline Vector4<T>& operator - (const Vector4<T>& vec);

	public:
		T x_, y_, z_, w_;
	};

	// Vector3
	template<typename T>
	class Vector3
	{
	public:
		Vector3(T x = 0, T y = 0, T z = 0) :x_(x), y_(y), z_(z){
		}

		Vector3(const Vector3<T>& vec){
			this->x_ = vec.x_;
			this->y_ = vec.y_;
			this->z_ = vec.z_;
		}

		inline T GetLength();
		inline Vector3<T>& operator + (const Vector3<T>& vec);
		inline Vector3<T>& operator - (const Vector3<T>& vec);

	public:
		T x_, y_, z_;
	};

	// Vector2
	template<typename T>
	class Vector2
	{
	public:
		Vector2(T x = 0, T y = 0) :x_(x), y_(y){
		}

		Vector2(const Vector2<T>& vec){
			this->x_ = vec.x_;
			this->y_ = vec.y_;
		}

		inline T GetLength();
		inline Vector2<T>& operator + (const Vector2<T>& vec);
		inline Vector2<T>& operator - (const Vector2<T>& vec);

	public:
		T x_, y_;
	};

}

#endif // ENGINE_MATH_VECTOR_H

#include "vector.inl"