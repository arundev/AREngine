#ifndef ENGINE_DX11_UTIL_DX11_H
#define ENGINE_DX11_UTIL_DX11_H

#include "../engine_pch.h"

struct D3DXMATRIX;

void MatrixToDx11(const Matrix* src, D3DXMATRIX* dst);
void MatrixFromDx11(const D3DXMATRIX* src, Matrix* dst);



#endif // ENGINE_DX11_UTIL_DX11_H