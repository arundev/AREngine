
#include "math.h"

namespace engine_math {
	Aabb::Aabb(Vector vcMin, Vector vcMax)
	{
		m_vcMin = vcMin;
		m_vcMax = vcMax;
		m_vcCenter = (vcMax - vcMin) / 2.0f;
	}

	void Aabb::Construct(const Obb *pObb)
	{
		Vector vcA0, vcA1, vcA2;
		Vector _vcMax, _vcMin;

		vcA0 = pObb->m_vcA0 * pObb->m_fA0;
		vcA1 = pObb->m_vcA1 * pObb->m_fA1;
		vcA2 = pObb->m_vcA2 * pObb->m_fA2;

		// find x extensions
		if (vcA0.x > vcA1.x)
		{
			if (vcA0.x > vcA2.x)
			{
				m_vcMax.x = vcA0.x;
				m_vcMin.x = -vcA0.x;
			}
			else
			{
				m_vcMax.x = vcA2.x;
				m_vcMin.x = -vcA2.x;
			}
		}
		else
		{
			if (vcA1.x > vcA2.x)
			{
				m_vcMax.x = vcA1.x;
				m_vcMin.x = -vcA1.x;
			}
			else
			{
				m_vcMax.x = vcA2.x;
				m_vcMin.x = -vcA2.x;
			}
		}

		// find y extensions
		if (vcA0.y > vcA1.y)
		{
			if (vcA0.y > vcA2.y)
			{
				m_vcMax.y = vcA0.y;
				m_vcMin.y = -vcA0.y;
			}
			else
			{
				m_vcMax.y = vcA2.y;
				m_vcMin.y = -vcA2.y;
			}
		}
		else
		{
			if (vcA1.y > vcA2.y)
			{
				m_vcMax.y = vcA1.y;
				m_vcMin.y = -vcA1.y;
			}
			else
			{
				m_vcMax.y = vcA2.y;
				m_vcMin.y = -vcA2.y;
			}
		}

		// find z extensions
		if (vcA0.z > vcA1.z)
		{
			if (vcA0.z > vcA2.z)
			{
				m_vcMax.z = vcA0.z;
				m_vcMin.z = -vcA0.z;
			}
			else
			{
				m_vcMax.z = vcA2.z;
				m_vcMin.z = -vcA2.z;
			}
		}
		else
		{
			if (vcA1.z > vcA2.z)
			{
				m_vcMax.z = vcA1.z;
				m_vcMin.z = -vcA1.z;
			}
			else
			{
				m_vcMax.z = vcA2.z;
				m_vcMin.z = -vcA2.z;
			}
		}
		m_vcMax = m_vcMax + pObb->m_vcCenter;
		m_vcMin = m_vcMin + pObb->m_vcCenter;
	}

	int Aabb::Cull(const Plane *pPlanes, int nNumPlanes)
	{
		Vector  vcMin, vcMax;
		bool    bIntersects = false;

		// find and test extreme points
		for (int i = 0; i<nNumPlanes; i++)
		{
			// x coordinate
			if (pPlanes[i].m_vcN.x >= 0.0f)
			{
				vcMin.x = this->m_vcMin.x;
				vcMax.x = this->m_vcMax.x;
			}
			else
			{
				vcMin.x = this->m_vcMax.x;
				vcMax.x = this->m_vcMin.x;
			}
			// y coordinate
			if (pPlanes[i].m_vcN.y >= 0.0f)
			{
				vcMin.y = this->m_vcMin.y;
				vcMax.y = this->m_vcMax.y;
			}
			else
			{
				vcMin.y = this->m_vcMax.y;
				vcMax.y = this->m_vcMin.y;
			}
			// z coordinate
			if (pPlanes[i].m_vcN.z >= 0.0f)
			{
				vcMin.z = this->m_vcMin.z;
				vcMax.z = this->m_vcMax.z;
			}
			else
			{
				vcMin.z = this->m_vcMax.z;
				vcMax.z = this->m_vcMin.z;
			}

			if (((pPlanes[i].m_vcN*vcMin) + pPlanes[i].m_fD) > 0.0f)
				return CULLED;

			if (((pPlanes[i].m_vcN*vcMax) + pPlanes[i].m_fD) >= 0.0f)
				bIntersects = true;
		} // for

		if (bIntersects) return CLIPPED;
		return VISIBLE;
	}

	void Aabb::GetPlanes(Plane *pPlanes)
	{
		Vector vcN;

		if (!pPlanes) return;

		// right side
		vcN.Set(1.0f, 0.0f, 0.0f);
		pPlanes[0].Set(vcN, m_vcMax);

		// left side
		vcN.Set(-1.0f, 0.0f, 0.0f);
		pPlanes[1].Set(vcN, m_vcMin);

		// front side
		vcN.Set(0.0f, 0.0f, -1.0f);
		pPlanes[2].Set(vcN, m_vcMin);

		// back side
		vcN.Set(0.0f, 0.0f, 1.0f);
		pPlanes[3].Set(vcN, m_vcMax);

		// top side
		vcN.Set(0.0f, 1.0f, 0.0f);
		pPlanes[4].Set(vcN, m_vcMax);

		// bottom side
		vcN.Set(0.0f, -1.0f, 0.0f);
		pPlanes[5].Set(vcN, m_vcMin);
	}

	bool Aabb::Contains(const Ray &Ray, float fL)
	{
		Vector vcEnd = Ray.m_vcOrig + (Ray.m_vcDir*fL);

		return (Intersects(Ray.m_vcOrig) && Intersects(vcEnd));
	}

	bool Aabb::Intersects(const Ray &Ray, float *t)
	{
		bool bInside = true;
		float t0, t1, tmp;
		float tNear = -999999.9f;
		float tFar = 999999.9f;
		float epsilon = 0.00001f;
		Vector MaxT;

		// first pair of planes
		if (_fabs(Ray.m_vcDir.x) < epsilon) {
			if ((Ray.m_vcOrig.x < m_vcMin.x) ||
				(Ray.m_vcOrig.x > m_vcMax.x))
				return false;
		}
		t0 = (m_vcMin.x - Ray.m_vcOrig.x) / Ray.m_vcDir.x;
		t1 = (m_vcMax.x - Ray.m_vcOrig.x) / Ray.m_vcDir.x;
		if (t0 > t1)
		{
			tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		if (t0 > tNear) tNear = t0;
		if (t1 < tFar)  tFar = t1;
		if (tNear > tFar) return false;
		if (tFar < 0) return false;

		// second pair of planes
		if (_fabs(Ray.m_vcDir.y) < epsilon)
		{
			if ((Ray.m_vcOrig.y < m_vcMin.y) ||
				(Ray.m_vcOrig.y > m_vcMax.y))
				return false;
		}
		t0 = (m_vcMin.y - Ray.m_vcOrig.y) / Ray.m_vcDir.y;
		t1 = (m_vcMax.y - Ray.m_vcOrig.y) / Ray.m_vcDir.y;
		if (t0 > t1)
		{
			tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		if (t0 > tNear) tNear = t0;
		if (t1 < tFar)  tFar = t1;
		if (tNear > tFar) return false;
		if (tFar < 0) return false;

		// third pair of planes
		if (_fabs(Ray.m_vcDir.z) < epsilon)
		{
			if ((Ray.m_vcOrig.z < m_vcMin.z) ||
				(Ray.m_vcOrig.z > m_vcMax.z))
				return false;
		}
		t0 = (m_vcMin.z - Ray.m_vcOrig.z) / Ray.m_vcDir.z;
		t1 = (m_vcMax.z - Ray.m_vcOrig.z) / Ray.m_vcDir.z;
		if (t0 > t1)
		{
			tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		if (t0 > tNear) tNear = t0;
		if (t1 < tFar)  tFar = t1;
		if (tNear > tFar) return false;
		if (tFar < 0) return false;


		if (tNear > 0)
		{
			if (t)
				*t = tNear;
		}
		else
		{
			if (t)
				*t = tFar;
		}

		return true;
	}

	bool Aabb::Intersects(const Ray &Ray, float fL, float *t)
	{
		bool bInside = true;
		float t0, t1, tmp, tFinal;
		float tNear = -999999.9f;
		float tFar = 999999.9f;
		float epsilon = 0.00001f;
		Vector MaxT;

		// first pair of planes
		if (_fabs(Ray.m_vcDir.x) < epsilon)
		{
			if ((Ray.m_vcOrig.x < m_vcMin.x) ||
				(Ray.m_vcOrig.x > m_vcMax.x))
				return false;
		}
		t0 = (m_vcMin.x - Ray.m_vcOrig.x) / Ray.m_vcDir.x;
		t1 = (m_vcMax.x - Ray.m_vcOrig.x) / Ray.m_vcDir.x;
		if (t0 > t1)
		{
			tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		if (t0 > tNear) tNear = t0;
		if (t1 < tFar)  tFar = t1;
		if (tNear > tFar) return false;
		if (tFar < 0) return false;

		// second pair of planes
		if (_fabs(Ray.m_vcDir.y) < epsilon)
		{
			if ((Ray.m_vcOrig.y < m_vcMin.y) ||
				(Ray.m_vcOrig.y > m_vcMax.y))
				return false;
		}
		t0 = (m_vcMin.y - Ray.m_vcOrig.y) / Ray.m_vcDir.y;
		t1 = (m_vcMax.y - Ray.m_vcOrig.y) / Ray.m_vcDir.y;
		if (t0 > t1)
		{
			tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		if (t0 > tNear) tNear = t0;
		if (t1 < tFar)  tFar = t1;
		if (tNear > tFar) return false;
		if (tFar < 0) return false;

		// third pair of planes
		if (_fabs(Ray.m_vcDir.z) < epsilon)
		{
			if ((Ray.m_vcOrig.z < m_vcMin.z) ||
				(Ray.m_vcOrig.z > m_vcMax.z))
				return false;
		}
		t0 = (m_vcMin.z - Ray.m_vcOrig.z) / Ray.m_vcDir.z;
		t1 = (m_vcMax.z - Ray.m_vcOrig.z) / Ray.m_vcDir.z;
		if (t0 > t1)
		{
			tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
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

	bool Aabb::Intersects(const Aabb &aabb)
	{
		if ((m_vcMin.x > aabb.m_vcMax.x) || (aabb.m_vcMin.x > m_vcMax.x))
			return false;
		if ((m_vcMin.y > aabb.m_vcMax.y) || (aabb.m_vcMin.y > m_vcMax.y))
			return false;
		if ((m_vcMin.z > aabb.m_vcMax.z) || (aabb.m_vcMin.z > m_vcMax.z))
			return false;

		return true;
	}

	bool Aabb::Intersects(const Vector &vc)
	{
		if (vc.x > m_vcMax.x) return false;
		if (vc.y > m_vcMax.y) return false;
		if (vc.z > m_vcMax.z) return false;
		if (vc.x < m_vcMin.x) return false;
		if (vc.y < m_vcMin.y) return false;
		if (vc.z < m_vcMin.z) return false;
		return true;
	}
}
