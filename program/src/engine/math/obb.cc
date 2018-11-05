
#include "math.h"

namespace engine {


bool Obb::Intersects(const Ray &Ray, float *t)
{
	float e, f, t1, t2, temp;
	float tmin = -99999.9f, 
		tmax = +99999.9f;

	Vector vcP = this->m_vcCenter - Ray.m_vcOrig;

	// 1st slap
	e = this->m_vcA0 * vcP;
	f = this->m_vcA0 * Ray.m_vcDir;
	if (_fabs(f) > 0.00001f)
	{

		t1 = (e + this->m_fA0) / f;
		t2 = (e - this->m_fA0) / f;

		if (t1 > t2) { temp=t1; t1=t2; t2=temp; }
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - this->m_fA0) > 0.0f) || ((-e + this->m_fA0) < 0.0f) )
		return false;

	// 2nd slap
	e = this->m_vcA1 * vcP;
	f = this->m_vcA1 * Ray.m_vcDir;
	if (_fabs(f) > 0.00001f)
	{

		t1 = (e + this->m_fA1) / f;
		t2 = (e - this->m_fA1) / f;

		if (t1 > t2) 
		{ 
			temp=t1; 
			t1=t2; 
			t2=temp;
		}
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - this->m_fA1) > 0.0f) || ((-e + this->m_fA1) < 0.0f) )
		return false;

	// 3rd slap
	e = this->m_vcA2 * vcP;
	f = this->m_vcA2 * Ray.m_vcDir;
	if (_fabs(f) > 0.00001f) 
	{

		t1 = (e + this->m_fA2) / f;
		t2 = (e - this->m_fA2) / f;

		if (t1 > t2) 
		{ 
			temp=t1; 
			t1=t2; 
			t2=temp;
		}
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - this->m_fA2) > 0.0f) || ((-e + this->m_fA2) < 0.0f) )
		return false;

	if (tmin > 0.0f) 
	{
		if (t)
			*t = tmin;
		return true;
	}

	if (t) *t = tmax;

	return true;
}

bool Obb::Intersects(const Ray &Ray, float fL, float *t)
{
	float e, f, t1, t2, temp;
	float tmin = -99999.9f, 
		  tmax = +99999.9f;

	Vector vcP = this->m_vcCenter - Ray.m_vcOrig;

	// 1st slap
	e = this->m_vcA0 * vcP;
	f = this->m_vcA0 * Ray.m_vcDir;
	if (_fabs(f) > 0.00001f) 
	{

		t1 = (e + this->m_fA0) / f;
		t2 = (e - this->m_fA0) / f;

		if (t1 > t2) 
		{ 
			temp=t1; 
			t1=t2; 
			t2=temp;
		}
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - this->m_fA0) > 0.0f) || ((-e + this->m_fA0) < 0.0f) )
		return false;

	// 2nd slap
	e = this->m_vcA1 * vcP;
	f = this->m_vcA1 * Ray.m_vcDir;
	if (_fabs(f) > 0.00001f) 
	{

		t1 = (e + this->m_fA1) / f;
		t2 = (e - this->m_fA1) / f;

		if (t1 > t2) { temp=t1; t1=t2; t2=temp; }
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - this->m_fA1) > 0.0f) || ((-e + this->m_fA1) < 0.0f) )
		return false;

	// 3rd slap
	e = this->m_vcA2 * vcP;
	f = this->m_vcA2 * Ray.m_vcDir;
	if (_fabs(f) > 0.00001f) 
	{

		t1 = (e + this->m_fA2) / f;
		t2 = (e - this->m_fA2) / f;

		if (t1 > t2)
		{
			temp=t1; 
			t1=t2; 
			t2=temp;
		}
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - this->m_fA2) > 0.0f) || ((-e + this->m_fA2) < 0.0f) )
		return false;

	if ( (tmin > 0.0f) && (tmin <= fL) )
	{
		if (t)
			*t = tmin;
		return true;
	}

	// intersection on line but not on segment
	if (tmax > fL) 
		return false;

	if (t) *t = tmax;

	return true;
}

bool Obb::Intersects(const Obb &Obb)
{
	float T[3];

	// difference vector between both obb
	Vector vcD = Obb.m_vcCenter - this->m_vcCenter;

	float matM[3][3];   // B's axis in relation to A
	float ra,           // radius A
		  rb,           // radius B
		  t;            // absolute values from T[]

	// Obb A's axis as separation axis?
	// ================================
	// first axis vcA0
	matM[0][0] = this->m_vcA0 * Obb.m_vcA0;
	matM[0][1] = this->m_vcA0 * Obb.m_vcA1;
	matM[0][2] = this->m_vcA0 * Obb.m_vcA2;
	ra   = this->m_fA0;
	rb   = Obb.m_fA0 * _fabs(matM[0][0]) + 
		   Obb.m_fA1 * _fabs(matM[0][1]) + 
		   Obb.m_fA2 * _fabs(matM[0][2]);

	T[0] = vcD * this->m_vcA0;
	t    = _fabs(T[0]);
	if(t > (ra + rb) ) 
		return false;

	// second axis vcA1
	matM[1][0] = this->m_vcA1 * Obb.m_vcA0;
	matM[1][1] = this->m_vcA1 * Obb.m_vcA1;
	matM[1][2] = this->m_vcA1 * Obb.m_vcA2;
	ra   = this->m_fA1;
	rb   = Obb.m_fA0 * _fabs(matM[1][0]) + 
		   Obb.m_fA1 * _fabs(matM[1][1]) + 
		   Obb.m_fA2 * _fabs(matM[1][2]);
	T[1] = vcD * this->m_vcA1;
	t    = _fabs(T[1]);
	if(t > (ra + rb) ) 
		return false;

	// third axis vcA2
	matM[2][0] = this->m_vcA2 * Obb.m_vcA0;
	matM[2][1] = this->m_vcA2 * Obb.m_vcA1;
	matM[2][2] = this->m_vcA2 * Obb.m_vcA2;
	ra   = this->m_fA2;
	rb   = Obb.m_fA0 * _fabs(matM[2][0]) + 
		Obb.m_fA1 * _fabs(matM[2][1]) + 
		Obb.m_fA2 * _fabs(matM[2][2]);
	T[2] = vcD * this->m_vcA2;
	t    = _fabs(T[2]);
	if(t > (ra + rb) ) 
		return false;

	// Obb B's axis as separation axis?
	// ================================
	// first axis vcA0
	ra = this->m_fA0 * _fabs(matM[0][0]) + 
		 this->m_fA1 * _fabs(matM[1][0]) + 
		 this->m_fA2 * _fabs(matM[2][0]);
	rb = Obb.m_fA0;
	t = _fabs( T[0]*matM[0][0] + T[1]*matM[1][0] + T[2]*matM[2][0] );
	if(t > (ra + rb) )
		return false;

	// second axis vcA1
	ra = this->m_fA0 * _fabs(matM[0][1]) + 
		 this->m_fA1 * _fabs(matM[1][1]) + 
		 this->m_fA2 * _fabs(matM[2][1]);
	rb = Obb.m_fA1;
	t = _fabs( T[0]*matM[0][1] + T[1]*matM[1][1] + T[2]*matM[2][1] );
	if(t > (ra + rb) )
		return false;

	// third axis vcA2
	ra = this->m_fA0 * _fabs(matM[0][2]) + 
		 this->m_fA1 * _fabs(matM[1][2]) + 
		 this->m_fA2 * _fabs(matM[2][2]);
	rb = Obb.m_fA2;
	t = _fabs( T[0]*matM[0][2] + T[1]*matM[1][2] + T[2]*matM[2][2] );
	if(t > (ra + rb) )
		return false;

	// other candidates: cross products of axis:
	// =========================================
	// axis A0xB0
	ra = this->m_fA1*_fabs(matM[2][0]) + this->m_fA2*_fabs(matM[1][0]);
	rb = Obb.m_fA1*_fabs(matM[0][2]) + Obb.m_fA2*_fabs(matM[0][1]);
	t = _fabs( T[2]*matM[1][0] - T[1]*matM[2][0] );
	if( t > ra + rb )
		return false;

	// axis A0xB1
	ra = this->m_fA1*_fabs(matM[2][1]) + this->m_fA2*_fabs(matM[1][1]);
	rb = Obb.m_fA0*_fabs(matM[0][2]) + Obb.m_fA2*_fabs(matM[0][0]);
	t = _fabs( T[2]*matM[1][1] - T[1]*matM[2][1] );
	if( t > ra + rb )
		return false;

	// axis A0xB2
	ra = this->m_fA1*_fabs(matM[2][2]) + this->m_fA2*_fabs(matM[1][2]);
	rb = Obb.m_fA0*_fabs(matM[0][1]) + Obb.m_fA1*_fabs(matM[0][0]);
	t = _fabs( T[2]*matM[1][2] - T[1]*matM[2][2] );
	if( t > ra + rb )
		return false;

	// axis A1xB0
	ra = this->m_fA0*_fabs(matM[2][0]) + this->m_fA2*_fabs(matM[0][0]);
	rb = Obb.m_fA1*_fabs(matM[1][2]) + Obb.m_fA2*_fabs(matM[1][1]);
	t = _fabs( T[0]*matM[2][0] - T[2]*matM[0][0] );
	if( t > ra + rb )
		return false;

	// axis A1xB1
	ra = this->m_fA0*_fabs(matM[2][1]) + this->m_fA2*_fabs(matM[0][1]);
	rb = Obb.m_fA0*_fabs(matM[1][2]) + Obb.m_fA2*_fabs(matM[1][0]);
	t = _fabs( T[0]*matM[2][1] - T[2]*matM[0][1] );
	if( t > ra + rb )
		return false;

	// axis A1xB2
	ra = this->m_fA0*_fabs(matM[2][2]) + this->m_fA2*_fabs(matM[0][2]);
	rb = Obb.m_fA0*_fabs(matM[1][1]) + Obb.m_fA1*_fabs(matM[1][0]);
	t = _fabs( T[0]*matM[2][2] - T[2]*matM[0][2] );
	if( t > ra + rb )
		return false;

	// axis A2xB0
	ra = this->m_fA0*_fabs(matM[1][0]) + this->m_fA1*_fabs(matM[0][0]);
	rb = Obb.m_fA1*_fabs(matM[2][2]) + Obb.m_fA2*_fabs(matM[2][1]);
	t = _fabs( T[1]*matM[0][0] - T[0]*matM[1][0] );
	if( t > ra + rb )
		return false;

	// axis A2xB1
	ra = this->m_fA0*_fabs(matM[1][1]) + this->m_fA1*_fabs(matM[0][1]);
	rb = Obb.m_fA0 *_fabs(matM[2][2]) + Obb.m_fA2*_fabs(matM[2][0]);
	t = _fabs( T[1]*matM[0][1] - T[0]*matM[1][1] );
	if( t > ra + rb )
		return false;

	// axis A2xB2
	ra = this->m_fA0*_fabs(matM[1][2]) + this->m_fA1*_fabs(matM[0][2]);
	rb = Obb.m_fA0*_fabs(matM[2][1]) + Obb.m_fA1*_fabs(matM[2][0]);
	t = _fabs( T[1]*matM[0][2] - T[0]*matM[1][2] );
	if( t > ra + rb )
		return false;

	// no separation axis found => intersection
	return true;
}

bool Obb::Intersects(const Vector &v0, 
				     const Vector &v1,
                     const Vector &v2)
{
	float     fMin0, fMax0, fMin1, fMax1;
	float     fD_C;
	Vector    vcV, vcTriEdge[3], vcA[3];

	// just for looping
	vcA[0] = this->m_vcA0;
	vcA[1] = this->m_vcA1;
	vcA[2] = this->m_vcA2;

	// direction of tri-normals
	vcTriEdge[0] = v1 - v0;
	vcTriEdge[1] = v2 - v0;

	vcV.Cross(vcTriEdge[0], vcTriEdge[1]);

	fMin0 = vcV * v0;
	fMax0 = fMin0;

	this->ObbProj((*this), vcV, &fMin1, &fMax1);
	if ( fMax1 < fMin0 || fMax0 < fMin1 )
		return true;

	// direction of obb planes
	// =======================
	// axis 1:
	vcV = this->m_vcA0;
	this->TriProj(v0, v1, v2, vcV, &fMin0, &fMax0);
	fD_C = vcV * this->m_vcCenter;
	fMin1 = fD_C - this->m_fA0;
	fMax1 = fD_C + this->m_fA0;
	if ( fMax1 < fMin0 || fMax0 < fMin1 )
		return true;

	// axis 2:
	vcV = this->m_vcA1;
	this->TriProj(v0, v1, v2, vcV, &fMin0, &fMax0);
	fD_C = vcV * this->m_vcCenter;
	fMin1 = fD_C - this->m_fA1;
	fMax1 = fD_C + this->m_fA1;
	if ( fMax1 < fMin0 || fMax0 < fMin1 )
		return true;

	// axis 3:
	vcV = this->m_vcA2;
	this->TriProj(v0, v1, v2, vcV, &fMin0, &fMax0);
	fD_C = vcV * this->m_vcCenter;
	fMin1 = fD_C - this->m_fA2;
	fMax1 = fD_C + this->m_fA2;
	if ( fMax1 < fMin0 || fMax0 < fMin1 )
		return true;


	// direction of tri-obb edge-crossproducts
	vcTriEdge[2] = vcTriEdge[1] - vcTriEdge[0];
	for (int j=0; j<3; j++) {
		for (int k=0; k<3; k++) {
			vcV.Cross(vcTriEdge[j], vcA[k]);

			this->TriProj(v0, v1, v2, vcV, &fMin0, &fMax0);
			this->ObbProj((*this), vcV, &fMin1, &fMax1);

			if ( (fMax1 < fMin0) || (fMax0 < fMin1) )
				return true;
		}
	}

	return true;
}

int Obb::Cull(const Plane *pPlanes, int nNumPlanes)
{
    Vector vN;
	int       nResult = VISIBLE;
	float     fRadius, fTest;

	// for all planes
	for (int i=0; i<nNumPlanes; i++) 
	{
		// frustrum normals pointing outwards, we need inwards
		vN = pPlanes[i].m_vcN * -1.0f;

		// calculate projected box radius
		fRadius = _fabs(m_fA0 * (vN * m_vcA0)) 
			    + _fabs(m_fA1 * (vN * m_vcA1))
			    + _fabs(m_fA2 * (vN * m_vcA2));

		// testvalue: (N*C - d) (#)
		fTest = vN * this->m_vcCenter - pPlanes[i].m_fD;

		// obb totally outside of at least one plane: (#) < -r
		if (fTest < -fRadius)
			return CULLED;
		// or maybe intersecting this plane?
		else if (!(fTest > fRadius))
			nResult = CLIPPED;
	} // for

	// if not culled then clipped or inside
	return nResult;
}

void Obb::ObbProj( const Obb &Obb, const Vector &vcV, 
	               float *pfMin, float *pfMax )
{
	float fDP = vcV * Obb.m_vcCenter;
	float fR  = Obb.m_fA0 * _fabs(vcV * Obb.m_vcA0) +
		        Obb.m_fA0 * _fabs(vcV * Obb.m_vcA1) +
		        Obb.m_fA1 * _fabs(vcV * Obb.m_vcA2);
	*pfMin = fDP - fR;
	*pfMax = fDP + fR;
}

void Obb::TriProj( const Vector &v0, const Vector &v1, 
	               const Vector &v2, const Vector &vcV, 
	               float *pfMin, float *pfMax )
{
	*pfMin = vcV * v0;
	*pfMax = *pfMin;

	float fDP = vcV * v1;
	if (fDP < *pfMin) *pfMin = fDP;
	else if (fDP > *pfMax) *pfMax = fDP;

	fDP = vcV * v2;
	if (fDP < *pfMin) *pfMin = fDP;
	else if (fDP > *pfMax) *pfMax = fDP;
}


}