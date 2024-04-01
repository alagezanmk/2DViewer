#include "stdafx.h"
#include <cu\win.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CWin, CWnd)
	//{{AFX_MSG_MAP(CWin)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()

	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()

	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MBUTTONDBLCLK()

	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CWin::CWin()
{}

CWin::~CWin()
{}

void CWin::OnMouseMove( UINT nFlags, CPoint point )
{
	CMouseEvent event;
	event.InitEvent( m_hWnd, WM_MOUSEMOVE, point, nFlags );

	// Calling OnMouseMove using CUI, otherwise 
	// compiler will give error 'OnMouseMove function does not take 1 parameters'
	CUI* pUI = this;
	if( pUI->OnMouseMove( event ) )
		return;

	CUI::OnMouseMove( event ); 
}

BOOL CWin::OnMouseWheel( UINT nFlags, short zDelta, CPoint point )
{
	CMouseEvent event;
	event.InitEvent( m_hWnd, WM_MOUSEWHEEL, point, nFlags, zDelta );

	CUI* pUI = this;
	if( pUI->OnMouseWheel( event ) )
		return TRUE;

	return CUI::OnMouseWheel( event ); 
}

void CWin::OnLButtonDown( UINT nFlags, CPoint point )
{
	CMouseEvent event;
	event.InitEvent( m_hWnd, WM_LBUTTONDOWN, point, nFlags );

	CUI* pUI = this;
	if( pUI->OnLButtonDown( event ) )
		return;

	CUI::OnLButtonDown( event ); 
}

void CWin::OnLButtonUp( UINT nFlags, CPoint point )
{
	CMouseEvent event;
	event.InitEvent( m_hWnd, WM_LBUTTONUP, point, nFlags );

	CUI* pUI = this;
	if( pUI->OnLButtonUp( event ) )
		return;

	CUI::OnLButtonUp( event ); 
}

void CWin::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	CMouseEvent event;
	event.InitEvent( m_hWnd, WM_LBUTTONDBLCLK, point, nFlags );

	CUI* pUI = this;
	if( pUI->OnLButtonDblClk( event ) )
		return;

	CUI::OnLButtonDblClk( event ); 
}

void CWin::OnRButtonDown( UINT nFlags, CPoint point )
{
	CMouseEvent event;
	event.InitEvent( m_hWnd, WM_RBUTTONDOWN, point, nFlags );

	CUI* pUI = this;
	if( pUI->OnRButtonDown( event ) )
		return;

	CUI::OnRButtonDown( event ); 
}

void CWin::OnRButtonUp( UINT nFlags, CPoint point )
{
	CMouseEvent event;
	event.InitEvent( m_hWnd, WM_RBUTTONUP, point, nFlags );

	CUI* pUI = this;
	if( pUI->OnRButtonDown( event ) )
		return;

	CUI::OnRButtonUp( event ); 
}

void CWin::OnRButtonDblClk( UINT nFlags, CPoint point )
{
	CMouseEvent event;
	event.InitEvent( m_hWnd, WM_RBUTTONDBLCLK, point, nFlags );

	CUI* pUI = this;
	if( pUI->OnRButtonDown( event ) )
		return;

	CUI::OnRButtonDblClk( event ); 
}

void CWin::OnMButtonDown( UINT nFlags, CPoint point )
{
	CMouseEvent event;
	event.InitEvent( m_hWnd, WM_MBUTTONDOWN, point, nFlags );

	CUI* pUI = this;
	if( pUI->OnMButtonDown( event ) )
		return;

	CUI::OnMButtonDown( event ); 
}

void CWin::OnMButtonUp( UINT nFlags, CPoint point )
{
	CMouseEvent event;
	event.InitEvent( m_hWnd, WM_MBUTTONUP, point, nFlags );

	CUI* pUI = this;
	if( pUI->OnMButtonDown( event ) )
		return;

	CUI::OnMButtonUp( event ); 
}

void CWin::OnMButtonDblClk( UINT nFlags, CPoint point )
{
	CMouseEvent event;
	event.InitEvent( m_hWnd, WM_MBUTTONDBLCLK, point, nFlags );

	CUI* pUI = this;
	if( pUI->OnMButtonDown( event ) )
		return;

	CUI::OnMButtonDblClk( event ); 
}

void CWin::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CKbdEvent event;
	event.InitEvent( m_hWnd, WM_KEYDOWN, nChar, nRepCnt, nFlags );

	CUI* pUI = this;
	if( pUI->OnKeyDown( event ) )
		return;

	CUI::OnKeyDown( event ); 
}

void CWin::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CKbdEvent event;
	event.InitEvent( m_hWnd, WM_KEYUP, nChar, nRepCnt, nFlags );

	CUI* pUI = this;
	if( pUI->OnKeyUp( event ) )
		return;

	CUI::OnKeyUp( event ); 
}