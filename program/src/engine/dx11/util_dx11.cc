
#include "../engine_pch.h"
#include "util_dx11.h" 

namespace engine {

void MatrixToDx11(const Matrix* src, DirectX::XMMATRIX* dst)
{
	//dst->r[0] = src->_11;
	//dst->_12 = src->_12;
	//dst->_13 = src->_13;
	//dst->_14 = src->_14;

	//dst->_21 = src->_21;
	//dst->_22 = src->_22;
	//dst->_23 = src->_23;
	//dst->_24 = src->_24;

	//dst->_31 = src->_31;
	//dst->_32 = src->_32;
	//dst->_33 = src->_33;
	//dst->_34 = src->_34;

	//dst->_41 = src->_41;
	//dst->_42 = src->_42;
	//dst->_43 = src->_43;
	//dst->_44 = src->_44;

	dst->r[0] = { src->_11, src->_12, src->_13, src->_14 };
	dst->r[1] = { src->_21, src->_22, src->_23, src->_24 };
	dst->r[2] = { src->_31, src->_32, src->_33, src->_34 };
	dst->r[3] = { src->_41, src->_42, src->_43, src->_44 };

	//memcpy(dst->r, &src->_11, sizeof(float) * 16);
}

void MatrixFromDx11(const DirectX::XMMATRIX* src, Matrix* dst)
{
	//dst->_11 = src->_11;
	//dst->_12 = src->_12;
	//dst->_13 = src->_13;
	//dst->_14 = src->_14;

	//dst->_21 = src->_21;
	//dst->_22 = src->_22;
	//dst->_23 = src->_23;
	//dst->_24 = src->_24;

	//dst->_31 = src->_31;
	//dst->_32 = src->_32;
	//dst->_33 = src->_33;
	//dst->_34 = src->_34;

	//dst->_41 = src->_41;
	//dst->_42 = src->_42;
	//dst->_43 = src->_43;
	//dst->_44 = src->_44;

	memcpy(&dst->_11, &src->r, sizeof(float) * 16);
}

}