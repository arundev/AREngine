#include <stdio.h>
#include "RTMath.h"
/*******************************************************************
* �ļ����ƣ� PolygonList.cpp
* ��    �ܣ� 
* ��    �ߣ� ���
* �������䣺 arun0515@gmail.com
* �������ڣ� 2009��9��13��
*******************************************************************/
using namespace RTMath;

PolygonList::PolygonList(void)
{
	m_uNum = 0;
	m_uMax = 0;
	m_pPolygon = NULL;
}

PolygonList::~PolygonList(void)
{
	if ( m_pPolygon )
	{
		free( m_pPolygon );
	}
	m_pPolygon = NULL;
}

bool PolygonList::AddPolygon( const RTMath::Polygon& polygon )
{
	if ( !CheckMem() )
	{
		return false;
	}

	m_pPolygon[m_uNum].CopyOf( polygon );
	m_uNum++;

	return true;
}

void PolygonList::Reset()
{
	m_uNum = 0;
	m_uMax = 0;

	if ( m_pPolygon )
	{
		free( m_pPolygon );
	}
	m_pPolygon = NULL;
}

bool PolygonList::CheckMem()
{
	if ( m_uNum < m_uMax )
	{
		return true;
	}
	m_uMax += 100;
	size_t iSize = m_uMax * sizeof( Polygon );
	m_pPolygon = ( Polygon* )realloc( m_pPolygon, iSize );

	memset( &m_pPolygon[m_uNum], 0, 100 );
	return ( m_pPolygon != NULL );
}