
#pragma once
#include "math.h"

namespace engine
{
	BOOL gIsUseASM = FALSE;             //  «∑Ò π”√ASM

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
