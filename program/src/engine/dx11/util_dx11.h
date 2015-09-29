#ifndef ENGINE_DX11_UTIL_DX11_H
#define ENGINE_DX11_UTIL_DX11_H

class RTMath::Matrix;
class D3DXMATRIX;

extern void MatrixToDx11(const RTMath::Matrix* src, D3DXMATRIX* dst);
extern void MatrixFromDx11(const D3DXMATRIX* src, RTMath::Matrix* dst);

#endif // ENGINE_DX11_UTIL_DX11_H