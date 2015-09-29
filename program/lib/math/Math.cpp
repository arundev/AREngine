/*******************************************************************
* 文件名称： 
* 功    能： 
* 作    者： 阮复初
* 电子邮箱： arun0515@gmail.com
* 创建日期： 2009年8月3日
*******************************************************************/
#pragma once
#include "RTMath.h"

using namespace RTMath;

namespace RTMath
{
	BOOL gIsUseASM = FALSE;             // 是否使用ASM

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
