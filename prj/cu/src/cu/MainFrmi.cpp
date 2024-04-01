#include "stdafx.h"
#include <cu\alx.h>
#include <cu\key.h>
#include <cu\msg.h>
#include <cu\MainFrmi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CIMDIClient, CWnd)
	//{{AFX_MSG_MAP(CIMDIClient)
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE( WM_MDISETMENU, OnMDISetMenu )
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSKEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CIMDIClient::CIMDIClient()
{}

CIMDIClient::~CIMDIClient()
{
	if( m_hWnd )
		UnsubClassMDI();
}

void CIMDIClient::SubClassMDI( HWND hWnd )
{
	ASSERT( hWnd && IsWindow( hWnd ) );
	SubclassWindow( hWnd );
}

void CIMDIClient::UnsubClassMDI()
{
	if( m_hWnd )
		UnsubclassWindow();
}

void CIMDIClient::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	INT nID = ID_FILE_NEW;
	if( FALSE == IsKeyCtrl() )
		nID = ID_FILE_OPEN;
	
	AfxGetMainWnd()->PostMessage( WM_COMMAND, nID );
}

LRESULT CIMDIClient::OnMDISetMenu( WPARAM wParam, LPARAM lParam )
{
	LRESULT lResult = Default();
	if( lParam )
		::PostMessage( (HWND)lParam, WM_MDISETMENU, wParam, lParam );

	return lResult;
}

void CIMDIClient::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	AfsSendMsg( AfxGetMainWnd(), CM_KEY_DOWN, nChar, MAKELONG(nRepCnt, nFlags) ); }

void CIMDIClient::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags ){
	AfsSendMsg( AfxGetMainWnd(), CM_KEY_UP, nChar, MAKELONG(nRepCnt, nFlags) ); }

void CIMDIClient::OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	AfsSendMsg( AfxGetMainWnd(), CM_KEY_DOWN, nChar, MAKELONG(nRepCnt, nFlags) ); }

void CIMDIClient::OnSysKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	AfsSendMsg( AfxGetMainWnd(), CM_KEY_UP, nChar, MAKELONG(nRepCnt, nFlags) ); }

IMPLEMENT_DYNCREATE(CIMainFrm, CMDIFrameWnd)
BEGIN_MESSAGE_MAP(CIMainFrm, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CIMainFrm)
	ON_WM_CLOSE()
	ON_WM_DROPFILES()

	ONC_MSG( CM_KEY_DOWN, OnKeyDownMsg )
	ONC_MSG( CM_KEY_UP, OnKeyUpMsg )
	ONC_MSG( CM_SYS_KEY_DOWN, OnSysKeyDownMsg )
	ONC_MSG( CM_SYS_KEY_UP, OnSysKeyUpMsg )

	ONC_MSG( CM_MF_GET_FULLSCREEN, OnGetFullScreen )
	///ON_COMMAND( ID_FULL_SCREEN, OnFullScreen )
	ON_WM_GETMINMAXINFO()

	ONC_MSG( CM_MF_VIEW_ADD, OnViewAdd )
	ONC_MSG( CM_MF_VIEW_CLOSE, OnViewClose )
	ONC_MSG( CM_MF_VIEW_ACTIVATE, OnViewActivate )
	ONC_MSG( CM_MF_GET_ACTIVE_VIEW, OnGetActiveView )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////////////////////////////////////

CIMainFrm::CIMainFrm()
{
	m_pvFullScreen = NULL;
	m_bBarsVisiblity = FALSE;
	m_pmdiClient = NULL;

	m_pCurView = NULL;
}

CIMainFrm::~CIMainFrm()
{
	if( m_pmdiClient )
		delete m_pmdiClient;
}

int CIMainFrm::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( -1 == CMDIFrameWnd::OnCreate( lpCreateStruct ) )
		return -1;

	return 0;
}

BOOL CIMainFrm::LoadFrame( UINT nIDResource, DWORD dwDefaultStyle,
							 CWnd* pParentWnd, CCreateContext* pContext )
{
	if( FALSE == CMDIFrameWnd::LoadFrame( nIDResource, dwDefaultStyle, pParentWnd, pContext ) )	
		return FALSE;

	VERIFY( m_pmdiClient = new CIMDIClient );
	m_pmdiClient->SubClassMDI( m_hWndMDIClient );
	SetClassLong( m_hWndMDIClient, GCL_STYLE, GetClassLong( m_hWndMDIClient, GCL_STYLE ) | CS_DBLCLKS );

	return TRUE;
}

void CIMainFrm::ShowHideBars()
{
	BOOL bAllBar = IsKeyShift();

	CControlBar* pBar;
	POSITION pos = m_listControlBars.GetHeadPosition();
	while( pos )
	{
		pBar = (CControlBar*)m_listControlBars.GetNext( pos );

		if( bAllBar || pBar->IsFloating() )
			ShowControlBar( pBar, m_bBarsVisiblity, FALSE );
	}

	// Set main frame focus, if it lost its focus
	if( m_bBarsVisiblity && this != GetFocus() )
		SetFocus();

	m_bBarsVisiblity ^= 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Full screen functions
typedef struct
{
	CRect			rect;
	WINDOWPLACEMENT wndPos;
	WINDOWPLACEMENT wndMDIPos;
	BOOL			bFullScreen;
	CPtrArray		arpBar;
}_SFullScreen, *_PSFullScreen;

/// Override this function to add visible controlbar to _SFullScreen::arpBar;
void CIMainFrm::OnChangeFullScreen() 
{
	_PSFullScreen psfs = (_PSFullScreen)m_pvFullScreen;
	
	CControlBar* pBar;
	POSITION pos = m_listControlBars.GetHeadPosition();
	while( pos )
	{
		pBar = (CControlBar*)m_listControlBars.GetNext( pos );
		if( pBar->IsWindowVisible() )
		{
			psfs->arpBar.Add( pBar );
			ShowControlBar( pBar, FALSE, TRUE );
		}
	}
}

void CIMainFrm::OnCancelFullScreen()
{
	_PSFullScreen psfs = (_PSFullScreen)m_pvFullScreen;
	INT nCount = psfs->arpBar.GetSize();
	CControlBar** ppBars = (CControlBar**)psfs->arpBar.GetData();
	for( INT i = 0; i < nCount; i++ )
		ShowControlBar( ppBars[i], TRUE, FALSE );	
}

void CIMainFrm::OnFullScreen()
{
	_PSFullScreen psfs = (_PSFullScreen)m_pvFullScreen;
	if( psfs )
	{
		psfs->bFullScreen = FALSE;
		OnCancelFullScreen();
		if( SW_SHOWMAXIMIZED == psfs->wndPos.showCmd )
			ShowWindow( SW_SHOWMAXIMIZED );
		else
			SetWindowPlacement( &psfs->wndPos );

		// Restore MDI child wnd also
		CMDIChildWnd* pChildFrame = MDIGetActive();
		if( pChildFrame )
			pChildFrame->SetWindowPlacement( &psfs->wndMDIPos );
		
		delete m_pvFullScreen;
		m_pvFullScreen = NULL;
		return;
	}

	WINDOWPLACEMENT wndPos;

	psfs = new _SFullScreen;
	VERIFY( m_pvFullScreen = psfs );
	OnChangeFullScreen();

	DWORD dwExStyle = GetWindowLong( m_hWnd, GWL_EXSTYLE );
	DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );
	HWND hDesktop = ::GetDesktopWindow();

	GetWindowPlacement( &psfs->wndPos );
	::GetWindowRect( hDesktop, &psfs->rect );

	AdjustWindowRectEx( &psfs->rect, dwStyle, TRUE, dwExStyle );
	psfs->rect.InflateRect( 4, 4 ); // To remove border of ChildFrm

	// Maximize MDI child wnd also
	CMDIChildWnd* pChildFrame = MDIGetActive();
	if( pChildFrame )
	{
		pChildFrame->GetWindowPlacement( &psfs->wndMDIPos );
		pChildFrame->ShowWindow( SW_SHOWMAXIMIZED );
	}

	memcpy( &wndPos, &psfs->wndPos, sizeof(wndPos) );
	wndPos.showCmd = SW_NORMAL;
	wndPos.rcNormalPosition = psfs->rect;
	psfs->bFullScreen = TRUE;
	SetWindowPlacement( &wndPos );
}

LRESULT CIMainFrm::OnGetFullScreen( WPARAM wParam, LPARAM lParam )
{
	_PSFullScreen psfs = (_PSFullScreen)m_pvFullScreen;
	PRECT pRect = (PRECT)lParam;
	if( psfs && psfs->bFullScreen )
	{
		memcpy( pRect, psfs->rect, sizeof(RECT) );
		return 1;
	}

	return 0;
}

/// \brief dfgdfg dfg df
/// dfg dfgk dfgsj dgjks dgfd
/// \param lpMMI sdfsfsdfsdf
void CIMainFrm::OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI )
{
	_PSFullScreen psfs = (_PSFullScreen)m_pvFullScreen;
	if( psfs && psfs->bFullScreen )
	{
		lpMMI->ptMaxTrackSize = lpMMI->ptMaxSize = CPoint( psfs->rect.Width(), psfs->rect.Height() );
		lpMMI->ptMinTrackSize = lpMMI->ptMaxPosition = CPoint( psfs->rect.left, psfs->rect.top );
		return;
	}

	CMDIFrameWnd::OnGetMinMaxInfo( lpMMI );
}

void CIMainFrm::OnClose()
{
	if( m_pvFullScreen )
		OnCancelFullScreen();

	if( m_bBarsVisiblity )
		ShowHideBars();

	CMDIFrameWnd::OnClose();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// File drag & drop function
void CIMainFrm::OnDropFiles( HDROP hDropInfo )
{
	TCHAR	szFilePath[MAX_PATH];
	UINT	unCount;
	
	// Get number of files dropped on our window 
    unCount = DragQueryFile( hDropInfo, 0xFFFFFFFF, NULL, 0);  

	for( UINT i = 0; i < unCount; i++ )
	{
		// Get the next file name and open it
		DragQueryFile( hDropInfo, i, szFilePath, MAX_PATH ); 

		AfxGetApp()->OpenDocumentFile( szFilePath );
	}

	DragFinish( hDropInfo );
	CWnd::OnDropFiles( hDropInfo );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// View List function

/// \brief brief description.
///
/// dfg dfgk dfgsj dgjks dgfd.\n
/// This is newline
/// \param wParam sdfsfsdfsdf
/// \param lParam sdfsfsdfsdf
/// \return sfsfsdf fs
LRESULT CIMainFrm::OnViewAdd( WPARAM wParam, LPARAM lParam )
{
	CView* pView = (CView*)wParam;
	INT nViewCnt = m_arpView.GetSize();
	CView** ppView = (CView**)m_arpView.GetData();
	for( INT i = 0; i < nViewCnt; i++ )
		if( ppView[i] == pView )
		{
			ASSERT( FALSE );
			return 0L;
		}

	m_arpView.Add( (PVOID)wParam );
	return (nViewCnt + 1);
}

LRESULT CIMainFrm::OnViewClose( WPARAM wParam, LPARAM lParam )
{
	CView* pView = (CView*)wParam;
	INT nViewCnt = m_arpView.GetSize();
	CView** ppView = (CView**)m_arpView.GetData();
	for( INT i = 0; i < nViewCnt;i++ )
		if( ppView[i] == pView )
		{
			m_arpView.RemoveAt( i );
			return (nViewCnt - 1);
		}

	return 0L;
}

LRESULT CIMainFrm::OnViewActivate( WPARAM wParam, LPARAM lParam )
{
	CView* pView = (CView*)wParam;
	if( NULL == pView )
	{
		m_pCurView = pView;
		return -1L;
	}

	INT nViewCnt = m_arpView.GetSize();
	CView** ppView = (CView**)m_arpView.GetData();
	for( INT i = 0; i < nViewCnt;i++ )
		if( ppView[i] == pView )
		{
			m_pCurView = pView;
			return i;
		}

	ASSERT( FALSE );
	return -1L;
}

LRESULT CIMainFrm::OnGetActiveView( WPARAM wParam, LPARAM ) {
	return (LRESULT)m_pCurView; }

///////////////////////////////////////////////////////////////////////////////////////////////////
/// App key & mouse function
LRESULT CIMainFrm::OnKeyDownMsg( WPARAM wParam, LPARAM lParam ) {
	return HandleKeyboardEvent( m_hWnd, WM_KEYDOWN, wParam, lParam ); }

LRESULT CIMainFrm::OnKeyUpMsg( WPARAM wParam, LPARAM lParam ) {
	return HandleKeyboardEvent( m_hWnd, WM_KEYUP, wParam, lParam ); }

LRESULT CIMainFrm::OnSysKeyDownMsg( WPARAM wParam, LPARAM lParam ) {
	return HandleKeyboardEvent( m_hWnd, WM_KEYDOWN, wParam, lParam ); }

LRESULT CIMainFrm::OnSysKeyUpMsg( WPARAM wParam, LPARAM lParam ) {
	return HandleKeyboardEvent( m_hWnd, WM_KEYUP, wParam, lParam ); }

BOOL CIMainFrm::OnKeyDown( const CKbdEvent& rEvent )
{
	if( VK_TAB == rEvent.m_nKey && FALSE == rEvent.m_bCtrlKey && rEvent.m_bShiftKey )
	{
		ShowHideBars();
		return TRUE;
	}

	return FALSE; 
}