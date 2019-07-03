
#pragma once
#include "math.h"

namespace engine
{
	BOOL gIsUseASM = FALSE;             //  «∑Ò π”√ASM

	const double MATH_PI = 3.14159265;
	const double MATH_PI2 = 1.5707963;
	const double MATH_2PI = 6.2831853;
	const float  MATH_G = -32.174f; // ft/s^2
	const float  MATH_EPSILON = 0.00001f;

	HRESULT InitCPU()
	{
		return S_OK;
	}


	float _fabs(float f)
	{
		if (f<0.0f) 
			return -f; 
		else
			return f;
	}
}
