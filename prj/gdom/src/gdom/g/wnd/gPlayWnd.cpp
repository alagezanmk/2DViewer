#include "stdafx.h"
#include <g\wnd\gPlayWnd.h>
#include <cu\key.win.h>
#include <cu\msg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
IMPL_BASE_GTPYECLASS_DYNCREATE( CGPlayWnd, _T("playWnd") )
BEGIN_MESSAGE_MAP(CGPlayWnd, CGWin)
	//{{AFX_MSG_MAP(CGPlayWnd)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGPlayWnd::CGPlayWnd() 
{
	m_pgInstanceType = &GetClassType();

	m_pwndView = NULL; 
	m_pView = NULL;
}

CGPlayWnd::~CGPlayWnd()
{
	if( m_pwndView )
	{
		RemoveChild( *m_pwndView );
		delete m_pwndView;
	}
}

BOOL CGPlayWnd::SetViewWindow( CGViewWnd& rwndView ) 
{
	if( m_pwndView )
		return FALSE;

	m_pwndView = &rwndView;
	return TRUE;
}

BOOL CGPlayWnd::SetView( CGIView& rView ) 
{
	if( m_pView )
		return FALSE;

	m_pView = &rView;
	return TRUE;
}

BOOL CGPlayWnd::OnInitialUpdate()
{
	ModifyStyle( 0, WS_CLIPCHILDREN );

	/// Create View instance and initialize
	if( NULL == m_pwndView )
	{
		VERIFY( m_pwndView = new CGViewWnd );
		if( NULL == m_pwndView )
			return FALSE;
	}

	AppendChild( *m_pwndView );
	if( m_pView )
		m_pwndView->SetView( *m_pView );

	if( FALSE == m_pwndView->Create( NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, EID_VIEW_WND ) )
		return FALSE;

	m_pwndView->SetUIHook( this );

	if( FALSE == m_pwndView->OnInitialUpdate() )
		return FALSE;

	return TRUE;
}

void CGPlayWnd::OnSize(UINT nType, int cx, int cy) 
{
	CGWin::OnSize(nType, cx, cy);
	if( m_pwndView && m_pwndView->m_hWnd )
		m_pwndView->MoveWindow( 0, 0, cx, cy );	
}

