#include "stdafx.h"
#include <cu\MemDC.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMemDC::CMemDC()
{
	m_hBmp = NULL;
	m_hOldBmp = NULL;
}

CMemDC::~CMemDC()
{
	if( m_hOldBmp )
	{
		ASSERT( m_hDC );
		::SelectObject( m_hDC, m_hOldBmp );
	}

	if( m_hDC )
		DeleteDC();

	if( m_hBmp )
		DeleteObject( m_hBmp );
}

BOOL CMemDC::Create( CDC* pDC, INT nWidth, INT nHeight )
{
	ASSERT( NULL == m_hDC );
	ASSERT( NULL == m_hBmp );
	ASSERT( NULL == m_hOldBmp ); 
	
	VERIFY( CreateCompatibleDC( pDC ) );
	if( NULL == m_hDC )
		return FALSE;

	VERIFY( m_hBmp = CreateCompatibleBitmap( pDC->m_hDC, nWidth, nHeight ) );
	if( NULL == m_hBmp )
		return FALSE;

	m_hOldBmp = (HBITMAP)::SelectObject( m_hDC, m_hBmp );
	return TRUE;
}