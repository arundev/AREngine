
#include "math.h"

namespace engine {

void Vector::operator+=( const Vector& v )
{
	x += v.x;  
	y += v.y;   
	z += v.z;
}

void Vector::operator+=(float f)
{
	x += f;
	y += f;
	z += f;
}

Vector Vector::operator+(const Vector &v) const
{
	return Vector( x + v.x, y + v.y, z + v.z );
}

Vector Vector::operator +( float f )const
{
	return Vector( x + f, y + f, z + f );
}

void Vector::operator-=( const Vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void Vector::operator-=( float f )
{
	x -= f;
	y -= f;
	z -= f;
}

Vector Vector::operator-( const Vector& v )const
{
	return Vector( x - v.x, y - v.y , z - v.z );
}

Vector Vector::operator-( float f )const
{
	return Vector( x - f, y - f, z - f );
}

void Vector::operator*=( float f )
{
	x *= f;
	y *= f;
	z *= f;
}

float Vector::operator*( const Vector& v )const
{
	return x * v.x + y * v.y + z * v.z ;
}

Vector Vector::operator*( float f )const
{
	return Vector( x * f, y * f, z * f );
}

Vector Vector::operator*(const Matrix &m )const
{
	Vector vcResult;

	if (!gIsUseASM )
	{
		vcResult.x = x*m._11 + y*m._21 + z*m._31 + m._41;
		vcResult.y = x*m._12 + y*m._22 + z*m._32 + m._42;
		vcResult.z = x*m._13 + y*m._23 + z*m._33 + m._43;
		vcResult.w = x*m._14 + y*m._24 + z*m._34 + m._44;

		vcResult.x = vcResult.x/vcResult.w;
		vcResult.y = vcResult.y/vcResult.w;
		vcResult.z = vcResult.z/vcResult.w;
		vcResult.w = 1.0f;
	 }
	// π”√ª„±‡
    else 
	{

	}         
	return vcResult;
}
Quaternion Vector::operator*( const Quaternion &q)const
{
	return Quaternion( q.w*x + q.z*y - q.y*z,
		               q.w*y + q.x*z - q.z*x,
		               q.w*z + q.y*x - q.x*y,
		               -(q.x*x + q.y*y + q.z*z) 
					  );
}

void Vector::operator/=(float f)
{
	x /= f;
	y /= f;
	z /= f;
}

Vector Vector::operator/(float f)const
{
	return Vector( x/f, y/f, z/f );
}

void Vector::Cross(const Vector &v1, const Vector &v2)
{
	if (!gIsUseASM )
	{
		x = v1.y * v2.z - v1.z * v2.y;
		y = v1.z * v2.x - v1.x * v2.z;
		z = v1.x * v2.y - v1.y * v2.x;
		w = 1.0f;
	}
	else
	{
	}
}


}