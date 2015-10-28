#include "RTMath.h"
#include "util_dx11.h"
#include <d3dcommon.h>   
#include <d3dx10math.h> 

using namespace RTMath;

void MatrixToDx11(const RTMath::Matrix* src, D3DXMATRIX* dst)
{
	dst->_11 = src->_11;
	dst->_12 = src->_12;
	dst->_13 = src->_13;
	dst->_14 = src->_14;

	dst->_21 = src->_21;
	dst->_22 = src->_22;
	dst->_23 = src->_23;
	dst->_24 = src->_24;

	dst->_31 = src->_31;
	dst->_32 = src->_32;
	dst->_33 = src->_33;
	dst->_34 = src->_34;

	dst->_41 = src->_41;
	dst->_42 = src->_42;
	dst->_43 = src->_43;
	dst->_44 = src->_44;
}

void MatrixFromDx11(const D3DXMATRIX* src, RTMath::Matrix* dst)
{
	dst->_11 = src->_11;
	dst->_12 = src->_12;
	dst->_13 = src->_13;
	dst->_14 = src->_14;

	dst->_21 = src->_21;
	dst->_22 = src->_22;
	dst->_23 = src->_23;
	dst->_24 = src->_24;

	dst->_31 = src->_31;
	dst->_32 = src->_32;
	dst->_33 = src->_33;
	dst->_34 = src->_34;

	dst->_41 = src->_41;
	dst->_42 = src->_42;
	dst->_43 = src->_43;
	dst->_44 = src->_44;
}