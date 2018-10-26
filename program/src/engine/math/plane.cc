
#include "math.h"

namespace engine_math{


int Plane::Classify(const Polygon &polygon)
{
	int NumFront=0, NumBack=0, NumPlanar=0;
	int nClass;

	// cast away const
	Polygon *pPoly = ((Polygon*)&polygon);

	int NumPoints = pPoly->GetNumPoints();

	// loop through all points
	for (int i=0; i < NumPoints; i++)
	{
		nClass = Classify( pPoly->m_pPoints[i] );

		if (nClass == FRONT)    
			NumFront++;
		else if (nClass == BACK)
			NumBack++;
		else 
		{
			NumFront++;
			NumBack++;
			NumPlanar++;
		}
	} // for

	// all points are planar
	if (NumPlanar == NumPoints)
		return PLANAR;
	// all points are in front of plane
	else if (NumFront == NumPoints)
		return FRONT;
	// all points are on backside of plane
	else if (NumBack == NumPoints)
		return BACK;
	// poly is intersecting the plane
	else
		return CLIPPED;
}
bool Plane::Clip(const Ray *_pRay, float fL, Ray *pF, Ray *pB)
{
	Vector vcHit(0.0f,0.0f,0.0f);

	Ray *pRay = (Ray*)_pRay;

	// ray intersects plane at all?
	if ( !pRay->Intersects( *this, false, fL, NULL, &vcHit) ) 
		return false;

	int n = Classify( _pRay->m_vcOrig );

	// ray comes fron planes backside
	if ( n == BACK ) {
		if (pB) pB->Set(pRay->m_vcOrig, pRay->m_vcDir);
		if (pF) pF->Set(vcHit, pRay->m_vcDir);
	}
	// ray comes from planes front side
	else if ( n == FRONT ) {
		if (pF) pF->Set(pRay->m_vcOrig, pRay->m_vcDir);
		if (pB) pB->Set(vcHit, pRay->m_vcDir);
	}

	return true;
}

bool Plane::Intersects( const Vector &vc0, const Vector &vc1, 
                        const Vector &vc2)
{
	int n = this->Classify(vc0);

	if ( (n == this->Classify(vc1)) && 
		 (n == this->Classify(vc2)) )
		return false;
	return true;
}
bool Plane::Intersects(const Plane &plane, Ray *pIntersection)
{
	Vector vcCross;
	float  fSqrLength;

	// if crossproduct of normals 0 than planes parallel
	vcCross.Cross(this->m_vcN, plane.m_vcN);
	fSqrLength = vcCross.GetSqrLength();

	if (fSqrLength < 1e-08f) 
		return false;

	// find line of intersection
	if (pIntersection) {
		float fN00 = this->m_vcN.GetSqrLength();
		float fN01 = this->m_vcN * plane.m_vcN;
		float fN11 = plane.m_vcN.GetSqrLength();
		float fDet = fN00*fN11 - fN01*fN01;

		if (_fabs(fDet) < 1e-08f) 
			return false;

		float fInvDet = 1.0f/fDet;
		float fC0 = (fN11*this->m_fD - fN01*plane.m_fD) * fInvDet;
		float fC1 = (fN00*plane.m_fD - fN01*this->m_fD) * fInvDet;

		(*pIntersection).m_vcDir  = vcCross;
		(*pIntersection).m_vcOrig = this->m_vcN*fC0 + plane.m_vcN*fC1;
	}

	return true;
}
bool Plane::Intersects(const Aabb &aabb)
{
	Vector Vmin, Vmax;

	// x component
	if (m_vcN.x >= 0.0f)
	{
		Vmin.x = aabb.m_vcMin.x;
		Vmax.x = aabb.m_vcMax.x;
	}
	else 
	{
		Vmin.x = aabb.m_vcMax.x;
		Vmax.x = aabb.m_vcMin.x;
	}

	// y component
	if (m_vcN.y >= 0.0f)
	{
		Vmin.y = aabb.m_vcMin.y;
		Vmax.y = aabb.m_vcMax.y;
	}
	else 
	{
		Vmin.y = aabb.m_vcMax.y;
		Vmax.y = aabb.m_vcMin.y;
	}

	// z component
	if (m_vcN.z >= 0.0f) 
	{
		Vmin.z = aabb.m_vcMin.z;
		Vmax.z = aabb.m_vcMax.z;
	}
	else 
	{
		Vmin.z = aabb.m_vcMax.z;
		Vmax.z = aabb.m_vcMin.z;
	}

	if ( ((m_vcN * Vmin) + m_fD) > 0.0f)
		return false;

	if ( ((m_vcN * Vmax) + m_fD) >= 0.0f)
		return true;

	return false;
}
bool Plane::Intersects(const Obb &obb)
{
	float fRadius = _fabs( obb.m_fA0 * (m_vcN * obb.m_vcA0) ) 
		+ _fabs( obb.m_fA1 * (m_vcN * obb.m_vcA1) ) 
		+ _fabs( obb.m_fA2 * (m_vcN * obb.m_vcA2) );

	float fDistance = this->Distance(obb.m_vcCenter);
	return (fDistance <= fRadius);
}


}