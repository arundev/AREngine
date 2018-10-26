
#include "math.h"

namespace engine_math {


bool Ray::Intersects( const Vector &vc0, const Vector &vc1, const Vector &vc2, bool bCull, float *t)
{
	Vector pvec, tvec, qvec;

	Vector edge1 = vc1 - vc0;
	Vector edge2 = vc2 - vc0;

	pvec.Cross(m_vcDir, edge2);

	// if close to 0 ray is parallel
	float det = edge1 * pvec;
	if ( (bCull) && (det < 0.0001f) )
		return false;
	else if ( (det < 0.0001f) && (det > -0.0001f) )
		return false;

	// distance to plane, < 0 means beyond plane
	tvec = m_vcOrig - vc0;
	float u = tvec * pvec;
	if (u < 0.0f || u > det)
		return false;

	qvec.Cross(tvec, edge1);
	float v = m_vcDir * qvec;
	if (v < 0.0f || u+v > det)
		return false;

	if (t) 
	{
		*t = edge2 * qvec;
		float fInvDet = 1.0f / det;
		*t *= fInvDet;
	}

	return true;
}

bool Ray::Intersects( const Vector &vc0, const Vector &vc1,
				      const Vector &vc2, bool bCull,
				      float fL, float *t)
{
	Vector pvec, tvec, qvec;

	Vector edge1 = vc1 - vc0;
	Vector edge2 = vc2 - vc0;

	pvec.Cross(m_vcDir, edge2);

	// if close to 0 ray is parallel
	float det = edge1 * pvec;
	if ( (bCull) && (det < 0.0001f) )
		return false;
	else if ( (det < 0.0001f) && (det > -0.0001f) )
		return false;

	// distance to plane, < 0 means beyond plane
	tvec = m_vcOrig - vc0;
	float u = tvec * pvec;
	if (u < 0.0f || u > det)
		return false;

	qvec.Cross(tvec, edge1);
	float v = m_vcDir * qvec;
	if (v < 0.0f || u+v > det)
		return false;

	if (t) {
		*t = edge2 * qvec;
		float fInvDet = 1.0f / det;
		*t *= fInvDet;
		// collision but not on segment?
		if (*t > fL) return false; 
	}
	else {
		// collision but not on segment?
		float f = (edge2*qvec) * (1.0f / det);
		if (f > fL) return false;
	}

	return true;
}

bool Ray::Intersects( const Plane &plane, bool bCull,
				      float *t, Vector *vcHit)
{
	float Vd = plane.m_vcN * m_vcDir;

	// ray parallel to plane
	if ( _fabs(Vd) < 0.00001f)
		return false;

	// normal pointing away from ray dir
	// => intersection backface if any
	if (bCull && (Vd > 0.0f))
		return false;

	float Vo = -( (plane.m_vcN * m_vcOrig) + plane.m_fD);

	float _t = Vo / Vd;

	// intersection behind ray origin
	if (_t < 0.0f)
		return false;

	if (vcHit) 
	{
		(*vcHit) = m_vcOrig + (m_vcDir * _t);
	}

	if (t)
		(*t) = _t;

	return true;
}

bool Ray::Intersects( const Plane &plane, bool bCull,
				      float fL, float *t, Vector *vcHit)
{
	float Vd = plane.m_vcN * m_vcDir;

	// ray parallel to plane
	if (_fabs(Vd) < 0.00001f)
		return false;

	// normal pointing away from ray dir
	// => intersection backface if any
	if (bCull && (Vd > 0.0f))
		return false;

	float Vo = -( (plane.m_vcN * m_vcOrig) + plane.m_fD);

	float _t = Vo / Vd;

	// intersection behind ray origin or beyond valid range
	if ( (_t < 0.0f) || (_t > fL) )
		return false;

	if (vcHit) {
		(*vcHit) = m_vcOrig + (m_vcDir * _t);
	}

	if (t)
		(*t) = _t;

	return true;
}

bool Ray::Intersects(const Aabb &aabb, float *t)
{
	bool bInside = true;
	float t0, t1, tmp;
	float tNear = -999999.9f;
	float tFar  =  999999.9f;
	float epsilon = 0.00001f;
	Vector MaxT;

	// first pair of planes
	if (_fabs(m_vcDir.x) < epsilon)
	{
		if ( (m_vcOrig.x < aabb.m_vcMin.x) ||
			(m_vcOrig.x > aabb.m_vcMax.x) )
			return false;
	}
	t0 = (aabb.m_vcMin.x - m_vcOrig.x) / m_vcDir.x;
	t1 = (aabb.m_vcMax.x - m_vcOrig.x) / m_vcDir.x;
	if (t0 > t1) { tmp=t0; t0=t1; t1=tmp; }
	if (t0 > tNear) tNear = t0;
	if (t1 < tFar)  tFar = t1;
	if (tNear > tFar) return false;
	if (tFar < 0) return false;

	// second pair of planes
	if (_fabs(m_vcDir.y) < epsilon) {
		if ( (m_vcOrig.y < aabb.m_vcMin.y) ||
			(m_vcOrig.y > aabb.m_vcMax.y) )
			return false;
	}
	t0 = (aabb.m_vcMin.y - m_vcOrig.y) / m_vcDir.y;
	t1 = (aabb.m_vcMax.y - m_vcOrig.y) / m_vcDir.y;
	if (t0 > t1) { tmp=t0; t0=t1; t1=tmp; }
	if (t0 > tNear) tNear = t0;
	if (t1 < tFar)  tFar = t1;
	if (tNear > tFar) return false;
	if (tFar < 0) return false;

	// third pair of planes
	if (_fabs(m_vcDir.z) < epsilon) {
		if ( (m_vcOrig.z < aabb.m_vcMin.z) ||
			(m_vcOrig.z > aabb.m_vcMax.z) )
			return false;
	}
	t0 = (aabb.m_vcMin.z - m_vcOrig.z) / m_vcDir.z;
	t1 = (aabb.m_vcMax.z - m_vcOrig.z) / m_vcDir.z;
	if (t0 > t1) { tmp=t0; t0=t1; t1=tmp; }
	if (t0 > tNear) tNear = t0;
	if (t1 < tFar)  tFar = t1;
	if (tNear > tFar) return false;
	if (tFar < 0) return false;


	if (tNear > 0) { if (t) *t = tNear; }
	else { if (t) *t = tFar; }

	return true;
}

bool Ray::Intersects(const Aabb &aabb, float fL, float *t)
{
	bool bInside = true;
	float t0, t1, tmp, tFinal;
	float tNear = -999999.9f;
	float tFar  =  999999.9f;
	float epsilon = 0.00001f;
	Vector MaxT;

	// first pair of planes
	if (_fabs(m_vcDir.x) < epsilon) {
		if ( (m_vcOrig.x < aabb.m_vcMin.x) ||
			(m_vcOrig.x > aabb.m_vcMax.x) )
			return false;
	}
	t0 = (aabb.m_vcMin.x - m_vcOrig.x) / m_vcDir.x;
	t1 = (aabb.m_vcMax.x - m_vcOrig.x) / m_vcDir.x;
	if (t0 > t1) { tmp=t0; t0=t1; t1=tmp; }
	if (t0 > tNear) tNear = t0;
	if (t1 < tFar)  tFar = t1;
	if (tNear > tFar) return false;
	if (tFar < 0) return false;

	// second pair of planes
	if (_fabs(m_vcDir.y) < epsilon) {
		if ( (m_vcOrig.y < aabb.m_vcMin.y) ||
			(m_vcOrig.y > aabb.m_vcMax.y) )
			return false;
	}
	t0 = (aabb.m_vcMin.y - m_vcOrig.y) / m_vcDir.y;
	t1 = (aabb.m_vcMax.y - m_vcOrig.y) / m_vcDir.y;
	if (t0 > t1) { tmp=t0; t0=t1; t1=tmp; }
	if (t0 > tNear) tNear = t0;
	if (t1 < tFar)  tFar = t1;
	if (tNear > tFar) return false;
	if (tFar < 0) return false;

	// third pair of planes
	if (_fabs(m_vcDir.z) < epsilon) {
		if ( (m_vcOrig.z < aabb.m_vcMin.z) ||
			(m_vcOrig.z > aabb.m_vcMax.z) )
			return false;
	}
	t0 = (aabb.m_vcMin.z - m_vcOrig.z) / m_vcDir.z;
	t1 = (aabb.m_vcMax.z - m_vcOrig.z) / m_vcDir.z;
	if (t0 > t1) { tmp=t0; t0=t1; t1=tmp; }
	if (t0 > tNear) tNear = t0;
	if (t1 < tFar)  tFar = t1;
	if (tNear > tFar) return false;
	if (tFar < 0) return false;


	if (tNear > 0) tFinal = tNear;
	else tFinal = tFar;

	if (tFinal > fL) return false;
	if (t) *t = tFinal;

	return true;
}

bool Ray::Intersects(const Obb &obb, float *t)
{
	float e, f, t1, t2, temp;
	float tmin = -99999.9f, 
		  tmax = +99999.9f;

	Vector vcP = obb.m_vcCenter - m_vcOrig;

	// 1st slap
	e = obb.m_vcA0 * vcP;
	f = obb.m_vcA0 * m_vcDir;
	if (_fabs(f) > 0.00001f) {

		t1 = (e + obb.m_fA0) / f;
		t2 = (e - obb.m_fA0) / f;

		if (t1 > t2) { temp=t1; t1=t2; t2=temp; }
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - obb.m_fA0) > 0.0f) || ((-e + obb.m_fA0) < 0.0f) )
		return false;

	// 2nd slap
	e = obb.m_vcA1 * vcP;
	f = obb.m_vcA1 * m_vcDir;
	if (_fabs(f) > 0.00001f) {

		t1 = (e + obb.m_fA1) / f;
		t2 = (e - obb.m_fA1) / f;

		if (t1 > t2) { temp=t1; t1=t2; t2=temp; }
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - obb.m_fA1) > 0.0f) || ((-e + obb.m_fA1) < 0.0f) )
		return false;

	// 3rd slap
	e = obb.m_vcA2* vcP;
	f = obb.m_vcA2* m_vcDir;
	if (_fabs(f) > 0.00001f) {

		t1 = (e + obb.m_fA2) / f;
		t2 = (e - obb.m_fA2) / f;

		if (t1 > t2) { temp=t1; t1=t2; t2=temp; }
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - obb.m_fA2) > 0.0f) || ((-e + obb.m_fA2) < 0.0f) )
		return false;

	if (tmin > 0.0f) {
		if (t) *t = tmin;
		return true;
	}

	if (t) *t = tmax;

	return true;
}

bool Ray::Intersects(const Obb &obb, float fL, float *t)
{
	float e, f, t1, t2, temp;
	float tmin = -99999.9f, 
		  tmax = +99999.9f;

	Vector vcP = obb.m_vcCenter - m_vcOrig;

	// 1st slap
	e = obb.m_vcA0 * vcP;
	f = obb.m_vcA0 * m_vcDir;
	if (_fabs(f) > 0.00001f) {

		t1 = (e + obb.m_fA0) / f;
		t2 = (e - obb.m_fA0) / f;

		if (t1 > t2) { temp=t1; t1=t2; t2=temp; }
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - obb.m_fA0) > 0.0f) || ((-e + obb.m_fA0) < 0.0f) )
		return false;

	// 2nd slap
	e = obb.m_vcA1 * vcP;
	f = obb.m_vcA1 * m_vcDir;
	if (_fabs(f) > 0.00001f) {

		t1 = (e + obb.m_fA1) / f;
		t2 = (e - obb.m_fA1) / f;

		if (t1 > t2) { temp=t1; t1=t2; t2=temp; }
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - obb.m_fA1) > 0.0f) || ((-e + obb.m_fA1) < 0.0f) )
		return false;

	// 3rd slap
	e = obb.m_vcA2* vcP;
	f = obb.m_vcA2* m_vcDir;
	if (_fabs(f) > 0.00001f) {

		t1 = (e + obb.m_fA2) / f;
		t2 = (e - obb.m_fA2) / f;

		if (t1 > t2) { temp=t1; t1=t2; t2=temp; }
		if (t1 > tmin) tmin = t1;
		if (t2 < tmax) tmax = t2;
		if (tmin > tmax) return false;
		if (tmax < 0.0f) return false;
	}
	else if ( ((-e - obb.m_fA2) > 0.0f) || ((-e + obb.m_fA2) < 0.0f) )
		return false;

	if ( (tmin > 0.0f) && (tmin <= fL) ) {
		if (t) *t = tmin;
		return true;
	}

	// intersection on line but not on segment
	if (tmax > fL) return false;

	if (t) *t = tmax;

	return true;
}


}