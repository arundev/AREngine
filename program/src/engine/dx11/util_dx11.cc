#include "util_dx11.h"
#include "../math/math.h"
#include <d3dcommon.h>  
#include <d3d11.h>  
#include <d3dx10math.h> 

void MatrixToDx11(const Matrix* src, D3DXMATRIX* dst)
{
	dst->m[0][0] = src->m[0][0];
	dst->m[0][1] = src->m[0][1];
	dst->m[0][2] = src->m[0][2];
	dst->m[0][3] = src->m[0][3];
	dst->m[1][0] = src->m[1][0];
	dst->m[1][1] = src->m[1][1];
	dst->m[1][2] = src->m[1][2];
	dst->m[1][3] = src->m[1][3];
	dst->m[2][0] = src->m[2][0];
	dst->m[2][1] = src->m[2][1];
	dst->m[2][2] = src->m[2][2];
	dst->m[2][3] = src->m[2][3];
	dst->m[3][0] = src->m[3][0];
	dst->m[3][1] = src->m[3][1];
	dst->m[3][2] = src->m[3][2];
	dst->m[3][3] = src->m[3][3];
}

void MatrixFromDx11(const D3DXMATRIX* src, Matrix* dst)
{
	dst->m[0][0] = src->m[0][0];
	dst->m[0][1] = src->m[0][1];
	dst->m[0][2] = src->m[0][2];
	dst->m[0][3] = src->m[0][3];
	dst->m[1][0] = src->m[1][0];
	dst->m[1][1] = src->m[1][1];
	dst->m[1][2] = src->m[1][2];
	dst->m[1][3] = src->m[1][3];
	dst->m[2][0] = src->m[2][0];
	dst->m[2][1] = src->m[2][1];
	dst->m[2][2] = src->m[2][2];
	dst->m[2][3] = src->m[2][3];
	dst->m[3][0] = src->m[3][0];
	dst->m[3][1] = src->m[3][1];
	dst->m[3][2] = src->m[3][2];
	dst->m[3][3] = src->m[3][3];
}