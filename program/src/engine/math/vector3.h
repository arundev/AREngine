#ifndef ENGINE_MATH_VECTOR3_H
#define ENGINE_MATH_VECTOR3_H


namespace engine_math {

template <typename T>
class Vector3 {
public:
	Vector3() : x(0), y(0), z(0) {}
	Vector3(T xx) : x(xx), y(xx), z(xx) {}
	Vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
	Vector3 operator + (const Vector3 &v) const
	{ return Vector3(x + v.x, y + v.y, z + v.z);}
	Vector3 operator - (const Vector3 &v) const
	{ return Vector3(x - v.x, y - v.y, z - v.z); }
	Vector3 operator * (const T &r) const
	{ return Vector3(x * r, y * r, z * r); }
	T dotProduct(const Vector3<T> &v) const
	{ return x * v.x + y * v.y + z * v.z; }
	T crossProduct(const Vector3<T> &v) const
	{ return Vector3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	T norm() const
	{ return x * x + y * y + z * z; }
	T length() const
	{ return sqrt(norm()); } 

	const T& operator [] (uint8_t i) const { return (&x)[i]; }
	T& operator [] (uint8_t i) { return (&x)[i]; }
	Vector3& normalize(){
		T n = norm();
		if (n > 0) {
			T factor = 1 / sqrt(n);
			x *= factor, y *= factor, z *= factor;
		}
		return *this;
	}

	friend std::ostream& operator << (std::ostream &s, const Vector3<T> &v) 
	{ return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ')'; }

public:
	T x, y, z;
};

typedef Vector3<float> Vector3F;

}


#endif //ENGINE_MATH_VECTOR3_H