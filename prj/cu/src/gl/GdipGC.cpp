#include "stdafx.h"
#include <gl\GdipGC.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGdipGCCreator::CGdipGCCreator() 
{}

CGC* CGdipGCCreator::Create( HGD hGD ) {
	return new CGdipGC( hGD ); }

CGC* CGdipGCCreator::Create( HWIN hWin, INT nGCType /*= CGL::enGCTypeClient*/ ) {
	return new CGdipGC( hWin, nGCType ); }

////////////////////////////////////////////////////////////////////////////////////////////////////
CGdipGC::CGdipGC()
{
	m_hDC = NULL;
	m_hWnd = NULL;
}

CGdipGC::CGdipGC( HGD hGD )
{
	m_hDC = hGD;
	m_hWnd = WindowFromDC( hGD );
}

CGdipGC::CGdipGC( HWIN hWin, INT nGCType /*= CGL::enGCTypeClient*/ )
{
	switch( nGCType )
	{
	case CGL::enGCTypePaint:
		m_hDC = BeginPaint( hWin, &m_ps );
		break;

	case CGL::enGCTypeClient:
		m_hDC = GetDC( hWin );
		break;

	case CGL::enGCTypeWindow:
		m_hDC = GetWindowDC( hWin );
		break;

	default:
		throw _T("Unsupported GC Type");
		return;
	}

	if( NULL == m_hDC )
	{
		throw _T("GC Creation failed");
		return;
	}

	m_hWnd = hWin;
	m_nGCType = nGCType;

	VERIFY( m_pG = CreateGraphics( m_hDC ) );
	if( NULL == m_pG )
		throw _T("Gdi+ creation failed");
}

CGdipGC::~CGdipGC()
{
	if( m_hDC )
	{
		ASSERT( m_hWnd );
		switch( m_nGCType )
		{
		case CGL::enGCTypePaint:
			EndPaint( m_hWnd, &m_ps );
			break;
		
		case CGL::enGCTypeClient:
		case CGL::enGCTypeWindow:
			ReleaseDC( m_hWnd, m_hDC );
			break;

		default:
			ASSERT( FALSE );
			return;
		}

		m_hWnd = NULL;
		m_hDC = NULL;
	}

	if( m_pG )
		DeleteGraphics( m_pG );
}

BOOL CGdipGC::DrawPolygon( GPointF* pfPoint, INT nCount )
{
	ASSERT( m_pG && nCount >= 0 );
	if( 0 == nCount )
		return FALSE;

	SolidBrush brush( Color::White );
	m_pG->FillPolygon( &brush, (PointF*)pfPoint, nCount );
	return TRUE;
}
