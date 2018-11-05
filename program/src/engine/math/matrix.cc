
#pragma once
#include "math.h"

namespace engine{


void Matrix::InverseOf(const Matrix &m)
{
	if (!gIsUseASM)
	{
		Matrix    mTrans;
		float     fTemp[12],  // cofaktors
			fDet;

		// calculate transposed matrix
		mTrans.TransposeOf(m);

		// Paare f黵 die ersten 8 Kofaktoren
		fTemp[0] = mTrans._33 * mTrans._44;
		fTemp[1] = mTrans._34 * mTrans._43;
		fTemp[2] = mTrans._32 * mTrans._44;
		fTemp[3] = mTrans._34 * mTrans._42;
		fTemp[4] = mTrans._32 * mTrans._43;
		fTemp[5] = mTrans._33 * mTrans._42;
		fTemp[6] = mTrans._31 * mTrans._44;
		fTemp[7] = mTrans._34 * mTrans._41;
		fTemp[8] = mTrans._31 * mTrans._43;
		fTemp[9] = mTrans._33 * mTrans._41;
		fTemp[10] = mTrans._31 * mTrans._42;
		fTemp[11] = mTrans._32 * mTrans._41;

		// Berechne die ersten 8 Kofaktoren
		this->_11 = fTemp[0] * mTrans._22 + fTemp[3] * mTrans._23 + fTemp[4] * mTrans._24;
		this->_11 -= fTemp[1] * mTrans._22 + fTemp[2] * mTrans._23 + fTemp[5] * mTrans._24;
		this->_12 = fTemp[1] * mTrans._21 + fTemp[6] * mTrans._23 + fTemp[9] * mTrans._24;
		this->_12 -= fTemp[0] * mTrans._21 + fTemp[7] * mTrans._23 + fTemp[8] * mTrans._24;
		this->_13 = fTemp[2] * mTrans._21 + fTemp[7] * mTrans._22 + fTemp[10] * mTrans._24;
		this->_13 -= fTemp[3] * mTrans._21 + fTemp[6] * mTrans._22 + fTemp[11] * mTrans._24;
		this->_14 = fTemp[5] * mTrans._21 + fTemp[8] * mTrans._22 + fTemp[11] * mTrans._23;
		this->_14 -= fTemp[4] * mTrans._21 + fTemp[9] * mTrans._22 + fTemp[10] * mTrans._23;
		this->_21 = fTemp[1] * mTrans._12 + fTemp[2] * mTrans._13 + fTemp[5] * mTrans._14;
		this->_21 -= fTemp[0] * mTrans._12 + fTemp[3] * mTrans._13 + fTemp[4] * mTrans._14;
		this->_22 = fTemp[0] * mTrans._11 + fTemp[7] * mTrans._13 + fTemp[8] * mTrans._14;
		this->_22 -= fTemp[1] * mTrans._11 + fTemp[6] * mTrans._13 + fTemp[9] * mTrans._14;
		this->_23 = fTemp[3] * mTrans._11 + fTemp[6] * mTrans._12 + fTemp[11] * mTrans._14;
		this->_23 -= fTemp[2] * mTrans._11 + fTemp[7] * mTrans._12 + fTemp[10] * mTrans._14;
		this->_24 = fTemp[4] * mTrans._11 + fTemp[9] * mTrans._12 + fTemp[10] * mTrans._13;
		this->_24 -= fTemp[5] * mTrans._11 + fTemp[8] * mTrans._12 + fTemp[11] * mTrans._13;

		// Paare f黵 die zweiten 8 Kofaktoren
		fTemp[0] = mTrans._13 * mTrans._24;
		fTemp[1] = mTrans._14 * mTrans._23;
		fTemp[2] = mTrans._12 * mTrans._24;
		fTemp[3] = mTrans._14 * mTrans._22;
		fTemp[4] = mTrans._12 * mTrans._23;
		fTemp[5] = mTrans._13 * mTrans._22;
		fTemp[6] = mTrans._11 * mTrans._24;
		fTemp[7] = mTrans._14 * mTrans._21;
		fTemp[8] = mTrans._11 * mTrans._23;
		fTemp[9] = mTrans._13 * mTrans._21;
		fTemp[10] = mTrans._11 * mTrans._22;
		fTemp[11] = mTrans._12 * mTrans._21;

		// Berechne die zweiten 8 Kofaktoren
		this->_31 = fTemp[0] * mTrans._42 + fTemp[3] * mTrans._43 + fTemp[4] * mTrans._44;
		this->_31 -= fTemp[1] * mTrans._42 + fTemp[2] * mTrans._43 + fTemp[5] * mTrans._44;
		this->_32 = fTemp[1] * mTrans._41 + fTemp[6] * mTrans._43 + fTemp[9] * mTrans._44;
		this->_32 -= fTemp[0] * mTrans._41 + fTemp[7] * mTrans._43 + fTemp[8] * mTrans._44;
		this->_33 = fTemp[2] * mTrans._41 + fTemp[7] * mTrans._42 + fTemp[10] * mTrans._44;
		this->_33 -= fTemp[3] * mTrans._41 + fTemp[6] * mTrans._42 + fTemp[11] * mTrans._44;
		this->_34 = fTemp[5] * mTrans._41 + fTemp[8] * mTrans._42 + fTemp[11] * mTrans._43;
		this->_34 -= fTemp[4] * mTrans._41 + fTemp[9] * mTrans._42 + fTemp[10] * mTrans._43;
		this->_41 = fTemp[2] * mTrans._33 + fTemp[5] * mTrans._34 + fTemp[1] * mTrans._32;
		this->_41 -= fTemp[4] * mTrans._34 + fTemp[0] * mTrans._32 + fTemp[3] * mTrans._33;
		this->_42 = fTemp[8] * mTrans._34 + fTemp[0] * mTrans._31 + fTemp[7] * mTrans._33;
		this->_42 -= fTemp[6] * mTrans._33 + fTemp[9] * mTrans._34 + fTemp[1] * mTrans._31;
		this->_43 = fTemp[6] * mTrans._32 + fTemp[11] * mTrans._34 + fTemp[3] * mTrans._31;
		this->_43 -= fTemp[10] * mTrans._34 + fTemp[2] * mTrans._31 + fTemp[7] * mTrans._32;
		this->_44 = fTemp[10] * mTrans._33 + fTemp[4] * mTrans._31 + fTemp[9] * mTrans._32;
		this->_44 -= fTemp[8] * mTrans._32 + fTemp[11] * mTrans._33 + fTemp[5] * mTrans._31;

		fDet = mTrans._11*this->_11 +
			mTrans._12*this->_12 +
			mTrans._13*this->_13 +
			mTrans._14*this->_14;

		fDet = 1 / fDet;

		this->_11 *= fDet;
		this->_12 *= fDet;
		this->_13 *= fDet;
		this->_14 *= fDet;

		this->_21 *= fDet;
		this->_22 *= fDet;
		this->_23 *= fDet;
		this->_24 *= fDet;

		this->_31 *= fDet;
		this->_32 *= fDet;
		this->_33 *= fDet;
		this->_34 *= fDet;

		this->_41 *= fDet;
		this->_42 *= fDet;
		this->_43 *= fDet;
		this->_44 *= fDet;
	}
	// 使用汇编
	else
	{
	}
}

Matrix Matrix::operator * (const Matrix &m)const
{
	Matrix mResult;

	if (!gIsUseASM) 
	{
		float *pA = (float*)this;
		float *pB = (float*)&m;
		float *pM = (float*)&mResult;

		memset(pM, 0, sizeof(Matrix));

		for(unsigned char i=0; i<4; i++) 
		{
			for(unsigned char j=0; j<4; j++) 
			{
				pM[4*i+j] += pA[4*i]   * pB[j];
				pM[4*i+j] += pA[4*i+1] * pB[4+j];
				pM[4*i+j] += pA[4*i+2] * pB[8+j];
				pM[4*i+j] += pA[4*i+3] * pB[12+j];
			}
		}
	}
	// 使用汇编
	else 
	{

	}
	return mResult;
}

Vector Matrix::operator * (const Vector &vc)const
{
	Vector vcResult;

	if (!gIsUseASM) 
	{
		vcResult.x = vc.x*_11 + vc.y*_21 + vc.z*_31 + _41;
		vcResult.y = vc.x*_12 + vc.y*_22 + vc.z*_32 + _42;
		vcResult.z = vc.x*_13 + vc.y*_23 + vc.z*_33 + _43;
		vcResult.w = vc.x*_14 + vc.y*_24 + vc.z*_34 + _44;

		vcResult.x = vcResult.x/vcResult.w;
		vcResult.y = vcResult.y/vcResult.w;
		vcResult.z = vcResult.z/vcResult.w;
		vcResult.w = 1.0f;
	}
	// 使用汇编
	else 
	{
	}
	return vcResult;
}


}