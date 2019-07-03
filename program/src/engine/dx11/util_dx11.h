#ifndef ENGINE_DX11_UTIL_DX11_H
#define ENGINE_DX11_UTIL_DX11_H

#include "../engine_pch.h"
#include "dx11_include.h"


namespace engine {

void MatrixToDx11(const Matrix* src, DirectX::XMMATRIX* dst);
void MatrixFromDx11(const DirectX::XMMATRIX* src, Matrix* dst);

}


#endif // ENGINE_DX11_UTIL_DX11_H