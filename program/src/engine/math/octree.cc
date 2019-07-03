#include "math.h"
#include <stdio.h>

// name the childs
#define POLYS_PER_LEAF 10
#define UP_NE  0     // upper north east child
#define UP_NW  1     // upper north west child
#define UP_SE  2     // upper south east child
#define UP_SW  3     // upper south west child
#define LW_NE  4     // lower north east child
#define LW_NW  5     // lower north west child
#define LW_SE  6     // lower south east child
#define LW_SW  7     // lower south west child

namespace engine {

Octree::Octree()
{
	m_pPolygons    = NULL;
	m_pParent      = NULL;
	m_pRoot        = NULL;
	m_nNumPolygons = 0;
	m_nPos         = -1;
	for ( int i=0; i<8; i++)
	{
		m_pChild[i] = NULL;
	}
	memset( &m_Aabb, 0, sizeof( Aabb ));
}

Octree::~Octree()
{
	if ( m_pPolygons )
	{
		delete[] m_pPolygons;
	}
	m_pPolygons = NULL;
	if ( m_pRoot )
	{
		delete m_pParent;
		m_pParent = NULL;
	}
	
	if ( m_pParent )
	{
		delete m_pParent;
		m_pParent = NULL;
	}

	for ( int i=0; i<8; i++)
	{
		if ( m_pChild[i] )
		{
			delete m_pChild[i];
			m_pChild[i] = NULL;
		}
	}
}

void Octree::BuildTree( const Polygon* pPolygons, UINT nNum )
{
	m_pRoot = this;
	if ( nNum < 1 )
	{
		return;
	}

	// 计算AABB
	CalcBoundingBox( pPolygons, nNum );

	// 拷贝多边形数据
	m_nNumPolygons = nNum;
	m_pPolygons = new Polygon[nNum];
	for ( UINT i=0; i<nNum; i++)
	{
		m_pPolygons[i].CopyOf( pPolygons[i]);
	}

	// 创建子结点
	CreateChilds( this );

	// 释放多边形数据（不是叶子节点）
	if ( m_pPolygons )
	{
		delete[] m_pPolygons;
		m_pPolygons = NULL;
	}
}

void Octree::Traverse( PolygonList* pPolygons, PolygonList* pAabbPolyList, const Plane* pFrustum )
{
	// 剔除检测
	if ( CULLED == m_Aabb.Cull( pFrustum, 6 ))
	{
		return;
	}
	
	// 叶子节点操作
	if ( IsLeaf() )
	{
		for ( UINT i=0; i<m_nNumPolygons; i++)
		{
			pPolygons[i].AddPolygon( m_pPolygons[i]);
		}
		// 添加叶子节点的AABB
		if ( pAabbPolyList )
		{
			GetAabbAsPolygons( pAabbPolyList );
		}
	}
	// 非叶子节点的操作
	else
	{
		for ( UINT i=0; i<8; i++)
		{
			m_pChild[i]->Traverse( pPolygons, pAabbPolyList, pFrustum );
		}
	}
}

bool Octree::GetFloor( const Vector& vcOrg, float* fL, Plane* pPlane )
{
	bool bHit = false;
	Ray ray;
	float* fDistense = nullptr;
	Aabb polygonAabb;
	// 根节点
	if ( this == m_pRoot )
	{
		*fL = 99999.0f;
	}
	// 叶子节点
	if ( IsLeaf() )
	{
		ray.Set( vcOrg, Vector( 0.0f, -1.0f, 0.0f ));
		if ( m_pPolygons == NULL )
		{
			return false;
		}
		for ( UINT i=0; i<m_nNumPolygons; i++)
		{
			polygonAabb = m_pPolygons[i].GetAabb();
			// 射线的原点必须在该多边形的AABB范围内的上方
			if ( ray.m_vcOrig.x < polygonAabb.m_vcMin.x
				 || ray.m_vcOrig.x > polygonAabb.m_vcMax.x 
				 || ray.m_vcOrig.z < polygonAabb.m_vcMin.z
				 || ray.m_vcOrig.z > polygonAabb.m_vcMax.z
				 || ray.m_vcOrig.y < polygonAabb.m_vcMin.y )
			{
				continue;
			}
			if ( m_pPolygons[i].Intersects( ray, fL, fDistense ))
			{
				*fL = *fDistense;
                bHit = true;
			}
		}
		return bHit;
	}
	// 非叶子节点
	else
	{
		for ( UINT i=0; i<8; i++)
		{
			if ( m_pChild[i]->IntersectsDownwardsRay( vcOrg, *fL ))
			{
				if ( m_pChild[i]->GetFloor( vcOrg, fL, pPlane ) )
				{
					bHit = true;
				}
			}
		}
		return bHit;
	}
}

bool Octree::TestCollision( const Ray* pRay, float fL, float* pfD )
{
	bool bCollision = false;
	float fD;

	// 叶子节点
	if (IsLeaf())
	{
		for ( UINT i=0; i<m_nNumPolygons; i++)
		{
			if ( m_pPolygons[i].Intersects( *pRay, false, fL, &fD))
			{
				bCollision = true;
				// 寻找最近点
				if (pfD) 
				{
					if ( (*pfD<=0.0f) || ( fD < *pfD)) 
						*pfD = fD;
				}
			}
			return bCollision;
		}
		return false;
	}
	// 非叶子节点
	else
	{
		for ( UINT i=0; i<8; i++)
		{
			if ( m_pChild[i]->TestCollision( pRay, fL, pfD))
			{
				return true;
			}
		}
		return false;
	}
}

bool Octree::TestCollision( const Aabb& aabb, Plane* pPlane )
{
	if ( this != m_pRoot )
	{
		if ( !m_Aabb.Intersects( aabb ))
		{
			return false;
		}
	}
	// 叶子节点
	if ( IsLeaf() )
	{
		if ( m_pPolygons == NULL )
		{
			return false;
		}
		for ( UINT i=0; i<m_nNumPolygons; i++ )
		{
			if ( m_pPolygons[i].GetAabb().Intersects( aabb ))
			{
				if ( pPlane )
				{
					*pPlane = m_pPolygons[i].GetPlane();
					return true;
				}
			}
		}
		return false;
	}
	// 非叶子节点
	else
	{
		for ( UINT i=0; i<8; i++)
		{
			if ( m_pChild[i]->TestCollision( aabb, pPlane ))
			{
				return true;
			}
		}
		return false;
	}
}

void Octree::CalcBoundingBox( const Polygon* pPolygon, UINT nInt )
{
	Vector vcMax, vcMin, vcTemp;
	Aabb aabb;
	Polygon* polygon = ( Polygon* )pPolygon;
	vcMax = vcMin = m_pPolygons[0].GetAabb().m_vcCenter;

	for ( UINT i=0; i<m_nNumPolygons; i++ )
	{
		aabb = m_pPolygons[i].GetAabb();
		vcTemp = aabb.m_vcMax;

		//
        if ( vcTemp.x > vcMax.x )
        {
			vcMax.x = vcTemp.x;
        }
		if ( vcTemp.x < vcMin.x )
		{
			vcMin.x = vcTemp.x;
		}
		if ( vcTemp.y > vcMax.y )
		{
			vcMax.y = vcTemp.y;
		}
		if ( vcTemp.z < vcMin.z )
		{
			vcMin.z = vcTemp.z;
		}

		//
		vcTemp = aabb.m_vcMin;
		if ( vcTemp.x > vcMax.x )
		{
			vcMax.x = vcTemp.x;
		}
		if ( vcTemp.x < vcMin.x )
		{
			vcMin.x = vcTemp.x;
		}
		if ( vcTemp.y > vcMax.y )
		{
			vcMax.y = vcTemp.y;
		}
		if ( vcTemp.z < vcMin.z )
		{
			vcMin.z = vcTemp.z;
		}

	}

	// 
	float fMax = vcMax.x - vcMin.x;
	if ( fMax < (vcMax.y - vcMin.y))
	{
		fMax = vcMax.y - vcMin.y;
	}
	if ( fMax < vcMax.z - vcMin.z )
	{
		fMax = vcMax.z - vcMin.z;
	}

	m_Aabb.m_vcCenter = ( vcMax - vcMin ) / 2.0f;
	m_Aabb.m_vcMax = m_Aabb.m_vcCenter + vcMax / 2.0f;
	m_Aabb.m_vcMin = m_Aabb.m_vcCenter - vcMax / 2.0f;
}

void Octree::InitChildObject( int iChildID, Octree* pParent )
{
	Aabb aabb;

	float xmin = m_Aabb.m_vcMin.x, 
		  xcen = m_Aabb.m_vcCenter.x, 
		  xmax = m_Aabb.m_vcMax.x; 

	float ymin = m_Aabb.m_vcMin.y, 
		  ycen = m_Aabb.m_vcCenter.y, 
		  ymax = m_Aabb.m_vcMax.y; 

	float zmin = m_Aabb.m_vcMin.z, 
		  zcen = m_Aabb.m_vcCenter.z, 
		  zmax = m_Aabb.m_vcMax.z; 

	switch(iChildID) 
	{
	  case UP_NW:
		  aabb.m_vcMax = Vector(xcen, ymax, zmax);
		  aabb.m_vcMin = Vector(xmin, ycen, zcen);
		  break;
	  case UP_NE:
		  aabb.m_vcMax = m_Aabb.m_vcMax;
		  aabb.m_vcMin = m_Aabb.m_vcCenter;
		  break;
	  case UP_SW:
		  aabb.m_vcMax = Vector(xcen, ymax, zcen);
		  aabb.m_vcMin = Vector(xmin, ycen, zmin);
		  break;
	  case UP_SE:
		  aabb.m_vcMax = Vector(xmax, ymax, zcen);
		  aabb.m_vcMin = Vector(xcen, ycen, zmin);
		  break;
	  case LW_NW:
		  aabb.m_vcMax = Vector(xcen, ycen, zmax);
		  aabb.m_vcMin = Vector(xmin, ymin, zcen);
		  break;
	  case LW_NE:
		  aabb.m_vcMax = Vector(xmax, ycen, zmax);
		  aabb.m_vcMin = Vector(xcen, ymin, zcen);
		  break;
	  case LW_SW:
		  aabb.m_vcMax = m_Aabb.m_vcCenter;
		  aabb.m_vcMin = m_Aabb.m_vcMin;
		  break;
	  case LW_SE:
		  aabb.m_vcMax = Vector(xmax, ycen, zcen);
		  aabb.m_vcMin = Vector(xcen, ymin, zmin);
		  break;
	  default: break;
	}

	aabb.m_vcCenter = (aabb.m_vcMax + aabb.m_vcMin) / 2.0f;
	m_pChild[iChildID] = new Octree();
	m_pChild[iChildID]->SetBoundingBox(aabb);
	m_pChild[iChildID]->m_pParent    = pParent;
	m_pChild[iChildID]->m_nPos       = iChildID;
}

void Octree::ChopListToMe(Polygon* pPolygons, UINT nNum )
{
	Polygon tempPolygon;
	Polygon* pTemPolylist;
    int iClassify;
	// 检测和初始化
	if ( nNum < 1) return;
	if ( m_pPolygons ) 
	{ 
		delete [] m_pPolygons; 
		m_pPolygons= NULL; 
	}
	m_nNumPolygons = 0;

	pTemPolylist = new Polygon[nNum];
	for ( UINT i=0; i<nNum; i++ )
	{
		if (pPolygons[i].GetFlag() == 1) continue;
		tempPolygon.CopyOf(pPolygons[i]);
		iClassify = tempPolygon.Cull( m_Aabb );
        if ( iClassify == CULLED)
        {
			continue;
        }
		else
		{
			// 不相交，则直接添加，并设置标志(则在再次检查时可以直接跳过)
			if ( iClassify != CLIPPED )
			{
				tempPolygon.SetFlag( 1 );
			}
			// 相交，则把在AABB外的部分裁减掉
			else
				tempPolygon.Clip( m_Aabb );

			pTemPolylist[i].CopyOf( tempPolygon );
			m_nNumPolygons++;
		}
	}
	// 填充数据
	m_pPolygons = new Polygon[m_nNumPolygons];
	for (unsigned int j=0; j<m_nNumPolygons; j++)
	{
		m_pPolygons[j].CopyOf( pTemPolylist[j] );
	}
	// 释放
	delete[] pTemPolylist;
}

void Octree::CreateChilds(Octree *pRoot)
{
	m_pRoot = pRoot;

	if ( (pRoot == this) || (m_nNumPolygons > POLYS_PER_LEAF) )
	{
		// 初始化
		for (int i=0; i<8; i++) 
		{
			InitChildObject( i, this );

			m_pChild[i]->ChopListToMe( m_pPolygons, m_nNumPolygons ); 
			m_pChild[i]->CreateChilds( pRoot );
		}

		// 只有在叶子节点中保存多边形数据
		if ( m_pPolygons ) 
		{
			delete [] m_pPolygons;
			m_pPolygons = NULL;
		}
	}
	else 
		return;
}

bool Octree::IntersectsDownwardsRay(const Vector& vcOrig, float fL )
{
	// ray在下方
	if (vcOrig.y < m_Aabb.m_vcMin.y) return false;

	// not inside on x axis
	if (vcOrig.x < m_Aabb.m_vcMin.x) return false;
	if (vcOrig.x > m_Aabb.m_vcMax.x) return false;

	// not inside on z axis
	if (vcOrig.z < m_Aabb.m_vcMin.z) return false;
	if (vcOrig.z > m_Aabb.m_vcMax.z) return false;

	// 射线必须射到AABB中
	if ( fL < (fabs(m_Aabb.m_vcMax.y - vcOrig.y))) 
		return false;

	return true;
}

void Octree::GetAabbAsPolygons( PolygonList* pPolygonList )
{
	// 正方体
	Polygon   Poly;
	Vector    vcPoints[24];
	unsigned int nIndis[6] = { 0, 1, 2, 2, 3, 0 };

	float fW = m_Aabb.m_vcMax.x - m_Aabb.m_vcMin.x;
	float fH = m_Aabb.m_vcMax.y - m_Aabb.m_vcMin.y;
	float fD = m_Aabb.m_vcMax.z - m_Aabb.m_vcMin.z;

	// 上方的正方形
	vcPoints[0].Set( m_Aabb.m_vcCenter.x - (fW / 2.0f),
		             m_Aabb.m_vcCenter.y + (fH / 2.0f),
		             m_Aabb.m_vcCenter.z - (fD / 2.0f) );
	vcPoints[1].Set( m_Aabb.m_vcCenter.x - (fW / 2.0f),
		             m_Aabb.m_vcCenter.y + (fH / 2.0f),
		             m_Aabb.m_vcCenter.z + (fD / 2.0f) );
	vcPoints[2].Set( m_Aabb.m_vcCenter.x + (fW / 2.0f),
		             m_Aabb.m_vcCenter.y + (fH / 2.0f),
		             m_Aabb.m_vcCenter.z + (fD / 2.0f) );
	vcPoints[3].Set( m_Aabb.m_vcCenter.x + (fW / 2.0f),
	                 m_Aabb.m_vcCenter.y + (fH / 2.0f),
		             m_Aabb.m_vcCenter.z - (fD / 2.0f) );
	Poly.Set( &vcPoints[0], 4, nIndis, 6 );
	pPolygonList->AddPolygon( Poly );

	// 右方四边形
	vcPoints[4] = vcPoints[3];
	vcPoints[5] = vcPoints[2];
	vcPoints[6].Set( m_Aabb.m_vcCenter.x + (fW / 2.0f),
		             m_Aabb.m_vcCenter.y - (fH / 2.0f),
		             m_Aabb.m_vcCenter.z + (fD / 2.0f) );
	vcPoints[7].Set( m_Aabb.m_vcCenter.x + (fW / 2.0f),
		             m_Aabb.m_vcCenter.y - (fH / 2.0f),
		             m_Aabb.m_vcCenter.z - (fD / 2.0f) );
	Poly.Set( &vcPoints[4], 4, nIndis, 6 );
	pPolygonList->AddPolygon( Poly );

	// 左方多四边形
	vcPoints[8] = vcPoints[0];
	vcPoints[9] = vcPoints[1];
	vcPoints[10].Set( m_Aabb.m_vcCenter.x - (fW / 2.0f),
		              m_Aabb.m_vcCenter.y - (fH / 2.0f),
		              m_Aabb.m_vcCenter.z + (fD / 2.0f) );
	vcPoints[11].Set( m_Aabb.m_vcCenter.x - (fW / 2.0f),
		              m_Aabb.m_vcCenter.y - (fH / 2.0f),
		              m_Aabb.m_vcCenter.z - (fD / 2.0f) );
	Poly.Set( &vcPoints[8], 4, nIndis, 6 );
	pPolygonList->AddPolygon( Poly );

	// 后面四边形
	vcPoints[12] = vcPoints[2];
	vcPoints[13] = vcPoints[1];
	vcPoints[14] = vcPoints[10];
	vcPoints[15] = vcPoints[6];
	Poly.Set( &vcPoints[12], 4, nIndis, 6 );
	pPolygonList->AddPolygon( Poly );

	// 前方的四边形
	vcPoints[16] = vcPoints[0];
	vcPoints[17] = vcPoints[3];
	vcPoints[18] = vcPoints[7];
	vcPoints[19] = vcPoints[11];
	Poly.Set( &vcPoints[16], 4, nIndis, 6 );
	pPolygonList->AddPolygon( Poly );

	// 底部的四边形
	vcPoints[20] = vcPoints[7];
	vcPoints[21] = vcPoints[6];
	vcPoints[22] = vcPoints[10];
	vcPoints[23] = vcPoints[11];
	Poly.Set( &vcPoints[20], 4, nIndis, 6 );
	pPolygonList->AddPolygon( Poly );
}


}