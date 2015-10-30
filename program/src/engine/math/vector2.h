#ifndef ENGINE_MATH_VECTOR2_H
#define ENGINE_MATH_VECTOR2_H


namespace engine_math  {

template<typename T>
class Vector2
{
public:
	Vector2() : x_(0), y_(0){}
	Vector2(T xx) : x_(xx), y_(xx){}
	Vector2(T xx, T yy) : x_(xx), y_(yy){}

public:
	T x_, y_;
};

typedef Vector2<float> Vector2F;

}



#endif // ENGINE_MATH_VECTOR2_H