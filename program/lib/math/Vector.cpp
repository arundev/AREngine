/*******************************************************************
* 文件名称： RTVector
* 功    能： 实现数学库中的Vector类
* 作    者： 阮复初
* 电子邮箱： arun0515@gmail.com
* 创建日期： 2009年8月3日
*******************************************************************/
#include "RTMath.h"
using namespace RTMath;


/*******************************************************************
* 函数名称： 
* 功    能： 
* 参    数： 
* 返 回 值： 
* 作    者： 阮复初
* 电子邮箱： arun0515@gmail.com
* 创建日期： 2009年8月3日
*******************************************************************/

void Vector::Set(float _x, float _y, float _z, float _w/* =1.0f */)
{
	x = _x; 
	y = _y; 
	z = _z; 
	w = _w;
}

float Vector::GetLength()const
{
	float f=0;
    
	if ( !gIsUseASM )
	{
		f = (float)sqrt(x*x + y*y + z*z); 
	}
	//使用汇编
	else
	{

	}

	return f;
}

float Vector::GetSqrLength()const
{
	 return (x*x + y*y + z*z); 
}

void Vector::Negate()
{
	x = -x;  y = -y;  z = -z;
}

void Vector::Normalize()
{
	if (!gIsUseASM) 
	{
		float f = (float)sqrt(x*x + y*y + z*z);

		if (f != 0.0f) 
		{
			x/=f; y/=f; z/=f;
		}
	}
	//使用汇编
	else
	{
	}
}

FLOAT Vector::AngleWith(const Vector& v)const
{
	return (float)acos( ((*this) * v) / (this->GetLength()*v.GetLength()) );
}

void Vector::RotateWith( const Matrix& m )
{
	float _x = x * m._11 + y * m._21 + z * m._31;
	float _y = x * m._12 + y * m._22 + z * m._32;
	float _z = x * m._13 + y * m._23 + z * m._33;
}

void Vector::InvRotateWith( const Matrix& m )
{
	float _x = x * m._11 + y * m._12 + z * m._13;
	float _y = x * m._21 + y * m._22 + z * m._23;
	float _z = x * m._31 + y * m._32 + z * m._33;
	x = _x;   y = _y;   z = _z;
}

void Vector::Difference( const Vector &v1, const Vector &v2 )
{
	x = v2.x - v1.x;
	y = v2.y - v1.y;
	z = v2.z - v1.z;
	w = 1.0f;
}





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
	//使用汇编
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