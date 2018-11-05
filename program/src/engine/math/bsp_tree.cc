#include "math.h"

namespace engine {

BspTree::BspTree()
{
	m_pBackChild = NULL;
	m_pFrontChild = NULL;
	m_pPolygon = 0;

}

BspTree::~BspTree()
{
	m_nNumPolys = 0;
	if ( m_pPolygon )
	{
		free( m_pPolygon );
	}
	m_pPolygon = NULL;
	if ( m_pFrontChild )
	{
		delete m_pFrontChild;
	}
	m_pFrontChild = NULL;
	if ( m_pBackChild )
	{
		delete m_pBackChild;
	}
	m_pBackChild = NULL;
}

void BspTree::BuildTree( const Polygon* pPolygons, UINT uNum )
{
	if ( uNum < 1 )
	{
		return;
	}
	m_pParent = NULL;
	m_pRoot   = this;
	m_nNumPolys = uNum;
	size_t iSize = uNum * sizeof( Polygon );
	m_pPolygon = ( Polygon* )malloc( iSize );
	memset( m_pPolygon, 0, iSize );
	for ( UINT i=0; i<uNum; i++)
	{
		m_pPolygon[i].CopyOf( pPolygons[i]);
	}

	CreateChilds();
}

/*******************************************************************
* �������ƣ� 
* ��    �ܣ� 
* ��    ���� 
        pPolygonlist---���شӺ�ǰ˳��Ķ�����б�
        vcPos----------�ӵ�λ��
		pFrustum-------�ӽ���
* �� �� ֵ�� 
* ��    �ߣ� ���
* �������䣺 arun0515@gmail.com
* �������ڣ� 2009��9��14��
*******************************************************************/
void BspTree::TraverseBtF( PolygonList* pPolygonlist, Vector vcPos, const Plane* pFrustum )
{
	if ( CULLED == m_Aabb.Cull( pFrustum, 6 ) )
	{
		return;
	}

	// Ҷ�ӽڵ�ʱ
	if ( IsLeaf() )
	{
		for ( UINT i=0; i<m_nNumPolys; i++)
		{
			pPolygonlist->AddPolygon( m_pPolygon[i]);
		}
	}
	else
	{
		int iClassify = m_SplitePlane.Classify( vcPos );
		if ( BACK == iClassify )
		{
			m_pFrontChild->TraverseBtF( pPolygonlist, vcPos, pFrustum );
			m_pBackChild->TraverseBtF( pPolygonlist, vcPos, pFrustum );
		}
		else
		{
			m_pBackChild->TraverseBtF( pPolygonlist, vcPos, pFrustum );
			m_pFrontChild->TraverseBtF( pPolygonlist, vcPos, pFrustum );
		}
	}
}
/*******************************************************************
* �������ƣ� 
* ��    �ܣ� 
* ��    ���� 
        pPolygonlist---���ش�ǰ����˳��Ķ�����б�
        vcPos----------�ӵ�λ��
        pFrustum-------�ӽ���
* �� �� ֵ�� 
* ��    �ߣ� ���
* �������䣺 arun0515@gmail.com
* �������ڣ� 2009��9��14��
*******************************************************************/
void BspTree::TraverseFtB( PolygonList* pPolygonlist, Vector vcPos, const Plane* pFrustum )
{
	if ( CULLED == m_Aabb.Cull( pFrustum, 6 ) )
	{
		return;
	}

	// Ҷ�ӽڵ�ʱ
	if ( IsLeaf() )
	{
		for ( UINT i=0; i<m_nNumPolys; i++)
		{
			pPolygonlist->AddPolygon( m_pPolygon[i]);
		}
	}
	// ��Ҷ�ӽڵ�
	else
	{
		int iClassify = m_SplitePlane.Classify( vcPos );
		if ( BACK == iClassify )
		{
			m_pBackChild->TraverseBtF( pPolygonlist, vcPos, pFrustum );
			m_pFrontChild->TraverseBtF( pPolygonlist, vcPos, pFrustum );
		}
		else
		{
			m_pFrontChild->TraverseBtF( pPolygonlist, vcPos, pFrustum );
			m_pBackChild->TraverseBtF( pPolygonlist, vcPos, pFrustum );
		}
	}
}

/*******************************************************************
* �������ƣ� TesCollision
* ��    �ܣ� ��ײ��⣬���߶�
* ��    ���� 
        pRay----����
		fL------���ߵĳ���
		pFD-----������ײ�㵽����ԭ��ľ���
		pvcN----������ײ��ķ�����
* �� �� ֵ�� bool
* ��    �ߣ� ���
* �������䣺 arun0515@gmail.com
* �������ڣ� 2009��9��14��
*******************************************************************/
bool BspTree::TestCollision( const Ray* pRay, float fL, float* pfD, Vector* pvcN )
{
	Ray frontRay, backRay;

	// Ҷ�ӽڵ�
	if ( IsLeaf() )
	{
		for ( UINT i=0; i< m_nNumPolys; i++)
		{
			if ( m_pPolygon[i].Intersects( *pRay, false, fL, NULL ))
			{
				if ( pvcN )
				{
					*pvcN = m_pPolygon[i].GetPlane().m_vcN;
				}
				return true;
			}
		}
	}
	// ��Ҷ�ӽڵ�
	if ( m_SplitePlane.Clip( pRay, fL, &frontRay, &backRay ))
	{ // ���߱��ָ����ж�
		if ( BACK == m_SplitePlane.Classify( pRay->m_vcOrig ))
		{
			return m_pBackChild->TestCollision( &backRay, fL, pfD, pvcN )
				   || m_pFrontChild->TestCollision( &frontRay, fL, pfD, pvcN );
		}
		else
			return m_pFrontChild->TestCollision( &frontRay, fL, pfD, pvcN )
			       || m_pBackChild->TestCollision( &backRay, fL, pfD, pvcN );
	}
	else
	{ 
		if ( BACK == m_SplitePlane.Classify( pRay->m_vcOrig ))
		{
			return m_pBackChild->TestCollision( pRay, fL, pfD, pvcN );
		}
		else
			return m_pFrontChild->TestCollision( pRay, fL, pfD, pvcN );
	}
}

bool BspTree::TestCollision( const Aabb* pAabb, const Plane* pFrustum )
{
	return true;
}

bool BspTree::LineOfSight(const Vector& vcOrg, const Vector& vcDes )
{
	Ray ray;
	Vector vDir = vcDes - vcOrg;
	vDir.Normalize();
	ray.Set( vcOrg,vDir );
	return TestCollision( &ray,vDir.GetLength(), NULL, NULL );
}

void BspTree::CreateChilds()
{
	Polygon frontPolygon, backPolygon;
	UINT nFrontNum = 0;
	UINT nBackNum  = 0;

	// ����aabb
	CalcBoundingBox( m_pPolygon, m_nNumPolys );

	// Ѱ����ѷָ���
	if ( !FindBestSplitter())
	{ // �ѽ���͹�ռ�
		//BspTree::m_sNumPolyOfTree += m_nNumPolys;
		return;
	}

	// �ָ�
	m_pBackChild = new BspTree();
	m_pFrontChild = new BspTree();
	m_pFrontChild->SetRelationships( m_pRoot, this );
	m_pBackChild->SetRelationships( m_pRoot, this );

	for ( UINT i=0; i<m_nNumPolys; i++ )
	{
		int iClassify = m_SplitePlane.Classify( m_pPolygon[i]);
		if ( BACK == iClassify )
		{ // ����
			m_pBackChild->AddPolygon( m_pPolygon[i]);
		}
		else if ( FRONT == iClassify )
		{ // ǰ��
			m_pFrontChild->AddPolygon( m_pPolygon[i]);
		}
		else if ( CLIPPED == iClassify )
		{ // ���ָ����и�
			m_pPolygon[i].Clip( m_SplitePlane,&frontPolygon, &backPolygon );
			m_pFrontChild->AddPolygon( frontPolygon );
			m_pBackChild->AddPolygon( backPolygon );
		}
		else if ( PLANAR == iClassify )
		{ // �ͷָ��湲��
			float fResult = m_SplitePlane.m_vcN * m_pPolygon[i].GetPlane().m_vcN;
			if ( fResult >= 0.0f )
			{
				m_pFrontChild->AddPolygon( m_pPolygon[i] );
			}
			else
				m_pBackChild->AddPolygon( m_pPolygon[i] );
		}
	}
}

bool BspTree::FindBestSplitter()
{
	Polygon *pBestSplitter = NULL;
	Polygon *pSplitter     = NULL;
	Plane    Plane;

	// ������
	int     lFront  = 0,       
		    lBack   = 0,      
		    lPlanar = 0,      
		    lSplits = 0;     
	int     nClass;
	int     lScore,
		    lBestScore = 1000000;
	bool    bFound = false;


	for (unsigned int i=0; i<m_nNumPolys; i++) 
	{

		pSplitter = &m_pPolygon[i];
		Plane     = pSplitter->GetPlane();

		// reset counters for this splitter
		lFront = lBack = lPlanar = lSplits = 0;

		// if flag then poly already used as splitter
		if ( pSplitter->GetFlag() == 1 ) continue;

		// loop through all polys for this splitter
		for (unsigned int j=0; j<m_nNumPolys; j++) 
		{
			if (i==j) continue;

			// classify current polygon with splitter
			nClass = Plane.Classify( m_pPolygon[j] );

			// add result to count
			if      ( nClass == FRONT  ) lFront++;
			else if ( nClass == BACK   ) lBack++;
			else if ( nClass == PLANAR ) lPlanar++;
			else                         lSplits++;
		} // for

		// count splitter's score heuristic
		lScore = abs(lFront - lBack) + (lSplits * 3);

		// do we have a new best score?
		if (lScore < lBestScore) 
		{
			if ( ((lFront > 0) && (lBack > 0)) || 
				  (lSplits > 0) ) 
			{
					lBestScore = lScore;
					pBestSplitter = pSplitter;
					bFound = true;
			} 
		} // if [ulScore]

	} // for

	// we can't find a splitter at all
	if ( !bFound ) return false;

	// mark polygon as used for split
	pBestSplitter->SetFlag(1);

	// save splitting plane
	m_SplitePlane = pBestSplitter->GetPlane();

	return true;
}

void BspTree::AddPolygon(const Polygon& polygon )
{
	m_pPolygon = (Polygon*)realloc(m_pPolygon,sizeof(Polygon)*(m_nNumPolys+1));

	memset(&m_pPolygon[m_nNumPolys], 0, sizeof(Polygon));

	m_pPolygon[m_nNumPolys].CopyOf( polygon );
	m_nNumPolys++;
}

void BspTree::CalcBoundingBox(const Polygon* pPolygons, unsigned int uNum )
{
	Vector   vcMax, vcMin, vcTemp;
	Aabb     Aabb;

	// cast away const
	Polygon *pPolys = ((Polygon*)pPolygons);

	if (uNum < 1)  return;

	// get arbitrary sub bounding box
	Aabb = pPolys[0].GetAabb();
	vcMax = vcMin = Aabb.m_vcCenter;

	for (unsigned int i=0; i<uNum; i++)
	{
		Aabb = pPolys[i].GetAabb();

		// get obb one side's extreme values
		vcTemp = Aabb.m_vcMax;

		if      ( vcTemp.x > vcMax.x ) vcMax.x = vcTemp.x;
		else if ( vcTemp.x < vcMin.x ) vcMin.x = vcTemp.x;
		if      ( vcTemp.y > vcMax.y ) vcMax.y = vcTemp.y;
		else if ( vcTemp.y < vcMin.y ) vcMin.y = vcTemp.y;
		if      ( vcTemp.z > vcMax.z ) vcMax.z = vcTemp.z;
		else if ( vcTemp.z < vcMin.z ) vcMin.z = vcTemp.z;

		// get obb other side's extreme values
		vcTemp = Aabb.m_vcMin;

		if      ( vcTemp.x > vcMax.x ) vcMax.x = vcTemp.x;
		else if ( vcTemp.x < vcMin.x ) vcMin.x = vcTemp.x;
		if      ( vcTemp.y > vcMax.y ) vcMax.y = vcTemp.y;
		else if ( vcTemp.y < vcMin.y ) vcMin.y = vcTemp.y;
		if      ( vcTemp.z > vcMax.z ) vcMax.z = vcTemp.z;
		else if ( vcTemp.z < vcMin.z ) vcMin.z = vcTemp.z;
	}

	// now calculate maximum extension
	float fMax = vcMax.x - vcMin.x;
	if (fMax < (vcMax.y - vcMin.y) ) fMax = vcMax.y - vcMin.y;
	if (fMax < (vcMax.z - vcMin.z) ) fMax = vcMax.z - vcMin.z;

	// make box cubic
	m_Aabb.m_vcCenter = (vcMax + vcMin) / 2.0f;
	m_Aabb.m_vcMax    = m_Aabb.m_vcCenter + (fMax/2.0f);
	m_Aabb.m_vcMin    = m_Aabb.m_vcCenter - (fMax/2.0f);
}

void BspTree::SetRelationships( BspTree* pRoot, BspTree* pParent )
{
	m_pRoot = pRoot;
	m_pParent = pParent;
}

}