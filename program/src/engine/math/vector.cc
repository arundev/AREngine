#include "vector.h"

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
