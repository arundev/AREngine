#ifndef ENGINE_DX11_UTIL_DX11_H
#define ENGINE_DX11_UTIL_DX11_H

class Matrix;
class D3DXMATRIX;

extern void MatrixToDx11(const Matrix* src, D3DXMATRIX* dst);


#endif // ENGINE_DX11_UTIL_DX11_H