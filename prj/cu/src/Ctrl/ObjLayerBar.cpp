#include "stdafx.h"
#include "ObjLayerBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CObjLayerBar, CToolFrmWnd)
	//{{AFX_MSG_MAP(CObjLayerBar)
	ON_MESSAGE( WM_FLOATSTATUS, OnFloatStatusMsg )
	ON_WM_CREATE()
 	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CObjLayerBar::CObjLayerBar()
{
	m_pLayerCtrl = NULL;
	m_cszCtrlName = _T("Layer Bar Box");
}

CObjLayerBar::~CObjLayerBar()
{}

/// To syn float status, which keeps MainFrame always have active caption, 
/// even this control get activated
LRESULT CObjLayerBar::OnFloatStatusMsg( WPARAM wParam, LPARAM lParam ) {
	return 1L; }

BOOL CObjLayerBar::Create( LPCTSTR lpszWindowName, const RECT& rect, CWnd* pParentWnd )
{
	LPCTSTR lptClass = AfxRegisterWndClass( 0, LoadCursor( NULL, MAKEINTRESOURCE(IDC_ARROW) ) );
	ASSERT( lptClass );

	CRect rctWnd( rect );
	BOOL bResult = CreateEx( WS_EX_TOOLWINDOW, lptClass, lpszWindowName, 
						     WS_VISIBLE | WS_POPUP | WS_CAPTION | 
							 WS_SYSMENU | WS_THICKFRAME,
						     rctWnd, pParentWnd, 0 );

	return bResult;
}

INT CObjLayerBar::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( CToolFrmWnd::OnCreate(lpCreateStruct) == -1 )
		return -1;

	VERIFY( m_pLayerCtrl = new CObjLayerCtrl );
	if( FALSE == m_pLayerCtrl->Create( NULL, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 
									   nullRECT, this, NULL, 0, NULL ) )
		return -1;

	return 0;
}

void CObjLayerBar::OnSize( UINT nType, INT cx, INT cy ) 
{
	CToolFrmWnd::OnSize( nType, cx, cy );
	if( m_pLayerCtrl && m_pLayerCtrl->m_hWnd )
		m_pLayerCtrl->SetWindowPos( NULL, 0, 0, cx, cy, SWP_NOZORDER );
}
