#include "stdafx.h"
#include "AfxPriv.h"
#include "ToolFrmWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CToolFrmWnd, CMiniFrameWnd)
BEGIN_MESSAGE_MAP(CToolFrmWnd, CMiniFrameWnd)
	//{{AFX_MSG_MAP(CToolFrmWnd)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CToolFrmWnd::CToolFrmWnd()
{}

CToolFrmWnd::~CToolFrmWnd()
{}

void CToolFrmWnd::SetBarInfo( CControlBarInfo* pInfo, CFrameWnd* pFrameWnd )
{}

void CToolFrmWnd::GetBarInfo( CControlBarInfo* pInfo )
{
	ASSERT_VALID(this);

	// get state info
	pInfo->m_nBarID = 1;
	pInfo->m_pBar = NULL;
	pInfo->m_bVisible = IsWindowVisible();
	pInfo->m_nMRUWidth = 0;

	CRect rect;
	GetWindowRect( &rect );
	pInfo->m_pointPos = rect.TopLeft();

	pInfo->m_bDocking = TRUE;
	pInfo->m_uMRUDockID = 1;
	pInfo->m_rectMRUDockPos = rect;
	pInfo->m_dwMRUFloatStyle = 0;
	pInfo->m_ptMRUFloatPos = pInfo->m_pointPos;
}

void CToolFrmWnd::SaveState( LPCTSTR lpszProfileName )
{
    CWinApp* pApp = AfxGetApp();

    TCHAR szSection[256];
    wsprintf( szSection, _T("%s-%s"), lpszProfileName,
        m_cszCtrlName );

	CRect rct;
	GetWindowRect( rct );

	pApp->WriteProfileInt( szSection, _T("left"), rct.left );
	pApp->WriteProfileInt( szSection, _T("top"), rct.top );
	pApp->WriteProfileInt( szSection, _T("visible"), IsWindowVisible() );
}

void CToolFrmWnd::LoadState( LPCTSTR lpszProfileName )
{
    CWinApp* pApp = AfxGetApp();

    TCHAR szSection[256];
    wsprintf( szSection, _T("%s-%s"), lpszProfileName,
        m_cszCtrlName );

	CRect rct;
	GetWindowRect( rct );

	CPoint pt;
    pt.x = pApp->GetProfileInt(szSection, _T("left"), rct.left );
	pt.x = max(0, pt.x);
	pt.x = min(1024 - 10, pt.x);

    pt.y = pApp->GetProfileInt(szSection, _T("top"), rct.top );
	pt.y = max(0, pt.y);
	pt.y = min(768 - 10, pt.y);

	rct.OffsetRect( -rct.TopLeft() );
	rct.OffsetRect( pt );
	MoveWindow( rct.left, rct.top, rct.Width(), rct.Height() );

	BOOL bVisible = pApp->GetProfileInt( szSection, _T("visible"), TRUE );
	ShowWindow( bVisible ?SW_SHOW: SW_HIDE );
}

void CToolFrmWnd::OnClose() {
	ShowWindow( SW_HIDE ); }
