#include "stdafx.h"
#include <g\tools\pTool.h>
#include <prop\PropRes.h>
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPL_GTPYECLASS_DYNCREATE( CGIPanTool, CGIUITool, _T("PanTool") )
CGIPanTool::CGIPanTool()
{
	m_pgInstanceType = &GetClassType();
	m_nUIMode = PAN_UI_MODE;
	m_hPanBmp = NULL;
}

CGIPanTool::~CGIPanTool()
{}

BOOL CGIPanTool::Draw( CDC& rDC, RECT& rRect )
{
	if( PAN_UI_MODE == m_nUIMode && PANNING_UI_STATE == m_nUIState )
	{
		DrawPanImage( rDC );
		return TRUE;
	}

	return FALSE;
}

INT CGIPanTool::GetDrawType() const 
{
	if( PAN_UI_MODE == m_nUIMode && PANNING_UI_STATE == m_nUIState )
		return LOWER_DRAW_TYPE;

	return UPPER_DRAW_TYPE; 
}

UINT CGIPanTool::HitTest( const CPoint& rpoint )
{
	if( PAN_UI_MODE == m_nUIMode )
		return HT_PAN;

	return HT_NOTHING;
}

BOOL CGIPanTool::On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage )
{
	if( PAN_UI_MODE != m_nUIMode )
		return FALSE;

	if( HT_PAN == nHitTest )
	{
		LPCTSTR pctszCursorID = MAKEINTRESOURCE(IDC_HAND_CUR);
		HINSTANCE hResInst = AfxFindResourceHandle( pctszCursorID, RT_GROUP_CURSOR );
		HCURSOR hCursor = ::LoadCursor( hResInst, pctszCursorID );
		::SetCursor( hCursor );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIPanTool::OnMouseMove( const CMouseEvent& rEvent )
{
	if( PAN_UI_MODE != m_nUIMode )
		return FALSE;

	if( NULL == m_pwndView )
		return FALSE;

	if( PANNING_UI_STATE == m_nUIState )
	{
		Pan( rEvent.m_ptClient );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIPanTool::OnLButtonDown( const CMouseEvent& rEvent )
{
	if( PAN_UI_MODE != m_nUIMode )
		return FALSE;

	if( NULL == m_pwndView )
		return FALSE;

	StartPan( rEvent.m_ptClient );
	return TRUE;
}

BOOL CGIPanTool::OnLButtonUp( const CMouseEvent& rEvent )
{
	if( PAN_UI_MODE != m_nUIMode )
		return FALSE;

	if( NULL == m_pwndView )
		return FALSE;

	if( PANNING_UI_STATE == m_nUIState )
	{
		EndPan();
		return TRUE;
	}

	return FALSE; 
}

void CGIPanTool::Scroll( const CPoint& rpt )
{
	if( 0 == rpt.x && 0 == rpt.y ) 
		return;

	if( NULL == m_pwndView || NULL == m_pView )
		return;

	m_pView->Scroll( (FLOAT)rpt.x, (FLOAT)rpt.y );
}

BOOL CGIPanTool::StartPan( const CPoint& rpt )
{
	if( PANNING_UI_STATE == m_nUIState )
		return FALSE;

	if( NULL == m_pwndView )
		return FALSE;

	CopyPanImage();
	m_ptPanOffset.x = 0;
	m_ptPanOffset.y = 0;
	m_ptPanStart = rpt;

	m_gptfViewOrigin = m_pView->GetOrigin();
	m_pView->GetScrollableSize( m_gcbViewScrollSize.cx, m_gcbViewScrollSize.cy );

	m_pwndView->SetCapture();
	m_nUIState = PANNING_UI_STATE;
	return TRUE;
}

void CGIPanTool::Pan( const CPoint& rpt )
{
	if( PANNING_UI_STATE != m_nUIState )
		return;

	m_ptPanOffset = rpt - m_ptPanStart;
	if( m_gcbViewScrollSize.cx )
	{
		FLOAT fx = m_gptfViewOrigin.x -m_ptPanOffset.x;
		fx = max(fx, 0);
		fx = min(fx, m_gcbViewScrollSize.cx);
		m_ptPanOffset.x = (long)(m_gptfViewOrigin.x - fx);
	}
	else
		m_ptPanOffset.x = 0;

	if( m_gcbViewScrollSize.cy )
	{
		FLOAT fy = m_gptfViewOrigin.y - m_ptPanOffset.y;
		fy = max(fy, 0);
		fy = min(fy, m_gcbViewScrollSize.cy);
		m_ptPanOffset.y = (long)(m_gptfViewOrigin.y - fy);
	}
	else
		m_ptPanOffset.y = 0;

	if( m_pwndView )
		m_pwndView->InvalidateRect( NULL, FALSE );
}

void CGIPanTool::EndPan()
{
	if( PANNING_UI_STATE != m_nUIState )
		return;

	m_nUIState = NONE_UI_STATE;
	ASSERT( m_hPanBmp ); 
	DeleteObject( m_hPanBmp );
	m_hPanBmp = NULL;

 	Scroll( -m_ptPanOffset );

	if( m_pwndView )
	{
		m_pwndView->InvalidateRect( NULL, TRUE );
		ReleaseCapture();
	}
}

BOOL CGIPanTool::CopyPanImage()
{
	CRect rcClient;
	m_pwndView->GetClientRect( rcClient );

	HDC hDC = ::GetDC( m_pwndView->m_hWnd );
	CDC ScreenDC;
	ScreenDC.Attach( hDC );
	CDC MemDC;
	CBitmap	Bitmap;

	VERIFY( MemDC.CreateCompatibleDC( &ScreenDC ) );
	VERIFY( Bitmap.CreateCompatibleBitmap( &ScreenDC, rcClient.right, rcClient.bottom ) );

	CBitmap* pOldBitmap = MemDC.SelectObject( &Bitmap );
	m_pwndView->CopyImage( MemDC, rcClient );
	MemDC.SelectObject( pOldBitmap );
	m_hPanBmp = (HBITMAP)Bitmap.Detach();

	ScreenDC.Detach();
	::ReleaseDC( m_pwndView->m_hWnd, hDC );

	return TRUE;
}

void CGIPanTool::DrawBkgndGrid( CDC& rDC, CRect& rRect )
{
	Graphics gdip( rDC.m_hDC );
	HatchBrush gbrush( HatchStyleLargeCheckerBoard, Color( 120, 125, 25, 25 ), Color( 10, 125, 25, 25 ) );
	gdip.FillRectangle( &gbrush, rRect.left, rRect.top, rRect.Width(), rRect.Height() );
}

void CGIPanTool::DrawPanImage( CDC& rDC )
{
	if( NULL == m_hPanBmp || NULL == m_pwndView )
		return;

	CDC		MemDC;
	CDC		ImageDC;
	CBitmap	PanBmp;
	PanBmp.Attach( m_hPanBmp );

	CRect rcClient;
	m_pwndView->GetClientRect( &rcClient );

	ImageDC.CreateCompatibleDC( &rDC );
	CBitmap* pOldImageBitmap = ImageDC.SelectObject( &PanBmp );

	CBitmap Bitmap;
	MemDC.CreateCompatibleDC( &rDC );
	Bitmap.CreateCompatibleBitmap( &rDC, rcClient.Width(), rcClient.Height() );
	CBitmap* pOldBitmap = MemDC.SelectObject( &Bitmap );

	DrawBkgndGrid( MemDC, rcClient );
	MemDC.BitBlt( m_ptPanOffset.x, m_ptPanOffset.y, 
				  rcClient.right, rcClient.bottom, &ImageDC, 0, 0,SRCCOPY );
	rDC.BitBlt( 0, 0, rcClient.right,rcClient.bottom, &MemDC, 0, 0,SRCCOPY);

	MemDC.SelectObject( pOldBitmap );
	VERIFY( m_hPanBmp == PanBmp.Detach() );

	ImageDC.SelectObject( pOldImageBitmap );
}