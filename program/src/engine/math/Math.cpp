/*******************************************************************
* �ļ����ƣ� 
* ��    �ܣ� 
* ��    �ߣ� ���
* �������䣺 arun0515@gmail.com
* �������ڣ� 2009��8��3��
*******************************************************************/
#pragma once
#include "RTMath.h"

using namespace RTMath;

namespace RTMath
{
	BOOL gIsUseASM = FALSE;             // �Ƿ�ʹ��ASM

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
