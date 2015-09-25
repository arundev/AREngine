#include "vector.h"
#include "matrix.h"

Vector::Vector()
{

}

Vector::Vector(float fx, float fy, float fz, float fw/* =1.0f */) :
x_(fx),
y_(fy),
z_(fz),
w_(fw)
{

}


Vector::~Vector(){

}

Vector Vector::operator*(const Matrix& m){
	return Vector(x_*m.m[0][0] + y_*m.m[1][0] + z_*m.m[2][0] + w_*m.m[3][0],
		x_*m.m[0][1] + y_*m.m[1][1] + z_*m.m[2][1] + w_*m.m[3][1],
		x_*m.m[0][2] + y_*m.m[1][2] + z_*m.m[2][2] + w_*m.m[3][2],
		1.0f);
}

Vector& Vector::operator*=(const Matrix& m){
	Vector v = Vector(x_*m.m[0][0] + y_*m.m[1][0] + z_*m.m[2][0] + w_*m.m[3][0],
		x_*m.m[0][1] + y_*m.m[1][1] + z_*m.m[2][1] + w_*m.m[3][1],
		x_*m.m[0][2] + y_*m.m[1][2] + z_*m.m[2][2] + w_*m.m[3][2],
		1.0f);

	x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;
	w_ = 1.0f;

	return v;
}
