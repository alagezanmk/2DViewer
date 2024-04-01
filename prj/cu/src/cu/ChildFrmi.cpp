#include "stdafx.h"
#include "ChildFrmi.h"
#include <cu\msg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CIChildFrm, CMDIChildWnd)
BEGIN_MESSAGE_MAP(CIChildFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CIChildFrm)
	ON_WM_CREATE()
	ONC_MSG( CM_CF_GET_SBAR, OnGetSBarMsg )
	ON_WM_GETMINMAXINFO()
	ON_WM_MDIACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CIChildFrm::CIChildFrm()
{}

CIChildFrm::~CIChildFrm()
{}

int CIChildFrm::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( CMDIChildWnd::OnCreate(lpCreateStruct) == -1 )
		return -1;

///	if( !m_hbViewBar.Create( _T("ViewTab"), this, CSize(180, 18), TRUE, EIDC_VIEW_TAB_BAR ) )
///	{
///		TRACE0( _T("Failed to create View Tab Bar \n") );
///		ASSERT( FALSE );
///		return FALSE;
///	}
///
///	m_hbViewBar.SetBarStyle( CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY );

	if( !m_hsbViewBar.Create( _T("ViewTab"), this, CSize(180, 18), TRUE, EIDC_VIEW_TAB_BAR + 1 ) )
	{
		TRACE( _T("Failed to create View Tab Bar \n") );
		ASSERT( FALSE );
		return FALSE;
	}

	m_hsbViewBar.SetBarStyle( CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY );

	if( !m_vsbViewBar.Create( _T("ViewTab"), this, CSize(18, 180), TRUE, EIDC_VIEW_TAB_BAR + 2 ) )
	{
		TRACE( _T("Failed to create View Tab Bar \n") );
		ASSERT( FALSE );
		return FALSE;
	}

	m_vsbViewBar.SetBarStyle( CBRS_RIGHT | CBRS_TOOLTIPS | CBRS_FLYBY );

	ShowControlBar( &m_hsbViewBar, FALSE, FALSE );
	ShowControlBar( &m_vsbViewBar, FALSE, FALSE );
	return TRUE;
}

LRESULT CIChildFrm::OnGetSBarMsg( WPARAM wParam, LPARAM lParam )
{
	if( SB_HORZ == wParam && m_hsbViewBar.m_hWnd )
		return (LRESULT)&m_hsbViewBar.m_SBar;

	if( SB_HORZ == wParam && m_hbViewBar.m_hWnd )
		return (LRESULT)&m_hbViewBar.m_SBar;

	if( SB_VERT == wParam && m_vsbViewBar.m_hWnd )
		return (LRESULT)&m_vsbViewBar.m_SBar;

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Full Screen functions
void CIChildFrm::OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI )
{
	CRect rect;
	CWnd* pFrameWnd = GetTopLevelFrame();
	if( pFrameWnd )
	{
		BOOL bFullScreen = AfsSendMsg( pFrameWnd, CM_MF_GET_FULLSCREEN, 0, (LPARAM)&rect );
		if( bFullScreen )
		{
			lpMMI->ptMaxTrackSize = lpMMI->ptMaxSize = CPoint( rect.Width(), rect.Height() );
			lpMMI->ptMinTrackSize = lpMMI->ptMaxPosition = CPoint( rect.left, rect.top );
			return;
		}
	}

	CMDIChildWnd::OnGetMinMaxInfo( lpMMI );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void CIChildFrm::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd )
{
	CMDIChildWnd::OnMDIActivate( bActivate, pActivateWnd, pDeactivateWnd );
	
	if( bActivate )
	{
		CView* pActiveView = GetActiveView();
		if( pActiveView )
		{
			CWnd* pFrameWnd = GetTopLevelFrame();
			if( pFrameWnd )
				AfsSendMsg( pFrameWnd, CM_MF_VIEW_ACTIVATE, (WPARAM)pActiveView );

			AfsSendCmd( pActiveView, CM_SV_VIEW_ACTIVATE, 1 );
		}
	}
	else
	{
		CView* pActiveView = GetActiveView();
		AfsSendCmd( pActiveView, CM_SV_VIEW_ACTIVATE, 0 );
	}
}
