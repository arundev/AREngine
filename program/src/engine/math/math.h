#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

#include "Vector.h"
#include "matrix.h"

namespace engine_math
{
	typedef Vector4<float> Vector4F;
	typedef Vector3<float> Vector3F;
	typedef Vector2<float> Vector2F;
	typedef Matrix<float> MatrixF;

	typedef Vector4F Color;
	typedef Vector3F Position;

	const int min_int_value = INT_MIN;
	const int max_int_value = INT_MAX;
}

#endif // ENGINE_MATH_H