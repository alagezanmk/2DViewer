#include "stdafx.h"
#include <gl\WinGC.h>
#include <gl\GdipGC.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CWinGCCreator::CWinGCCreator() 
{}

CGC* CWinGCCreator::Create( HGD hGD ) {
	return new CWinGC( hGD ); }

CGC* CWinGCCreator::Create( HWIN hWin, INT nGCType /*= CGL::enGCTypeClient*/ ) {
	return new CWinGC( hWin, nGCType ); }

////////////////////////////////////////////////////////////////////////////////////////////////////
CWinGC::CWinGC()
{
	m_hDC = NULL;
	m_hWnd = NULL;
}

CWinGC::CWinGC( HGD hGD )
{
	m_hDC = hGD;
	m_hWnd = WindowFromDC( hGD );
}

CWinGC::CWinGC( HWIN hWin, INT nGCType /*= CGL::enGCTypeClient*/ )
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
}

CWinGC::~CWinGC()
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
}

BOOL CWinGC::DrawPolygon( GPointF* pfPoint, INT nCount )
{
	ASSERT( m_hDC && nCount > 0 );
	if( 0 == nCount )
		return FALSE;

	POINT* pPoint = new POINT[nCount];
	if( NULL == pPoint )
		return FALSE;

	for( INT i = 0; i < nCount; i++ )
	{
		pPoint[i].x = (LONG)pfPoint[i].x;
		pPoint[i].y = (LONG)pfPoint[i].y;
	}
		
	BOOL bResult = Polygon( m_hDC, pPoint, nCount );
	delete pPoint;

	return bResult;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void InitGC()
{
//	CGL::SetDefaultGC( new CWinGCCreator() );
	CGL::SetDefaultGC( new CGdipGCCreator() );
}

CU_EXT_API void ReleaseGC()
{
	CGL::DeleteDefaultGC();
}