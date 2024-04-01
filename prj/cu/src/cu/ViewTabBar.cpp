#include "stdafx.h"
#include "ViewTabBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CViewTabBar, CSizingControlBar)
	//{{AFX_MSG_MAP(CViewTabBar)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CViewTabBar::CViewTabBar()
{}

CViewTabBar::~CViewTabBar()
{}

INT CViewTabBar::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	SetBorders();
	if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rctNull( 0, 0, 0, 0 );
	m_slmTab.Create( this, &rctNull, 1 );
	m_slmTab.AddTab( _T("Design") );
	m_slmTab.AddTab( _T("Src") );
	m_slmTab.AddTab( _T("Preview") );
	m_slmTab.ShowWindow( SW_SHOW );

	m_SBar.Create( WS_VISIBLE | WS_CHILD | WS_HSCROLL, rctNull, this, 2 );
	return 0;
}

static const int gs_cnTabCx = 140;
static const int gs_cnSepCx = 0;
static const int gs_cnCBarCs = 20;
void CViewTabBar::OnPaint()
{
	Default();
	CClientDC dc(this);
	CRect rcClient; 
	GetClientRect( rcClient );

	HPEN hpenOld, hpen = CreatePen( PS_SOLID, 1, GetSysColor( COLOR_BTNSHADOW ) );

	hpenOld = (HPEN)SelectObject( dc.m_hDC, hpen );
	dc.Rectangle( gs_cnTabCx, 0, gs_cnTabCx + gs_cnSepCx, rcClient.bottom - 1 );
	dc.MoveTo( 0, rcClient.bottom - 2 );
	dc.LineTo( rcClient.right, rcClient.bottom - 2 );
	SelectObject( dc.m_hDC, hpenOld );
	DeleteObject( hpen );
}

void CViewTabBar::OnSize( UINT nType, INT cx, INT cy )
{
	CSizingControlBar::OnSize( nType, cx, cy );
	if( m_slmTab.m_hWnd )
	{
		m_slmTab.SetWindowPos( NULL, 0, 0, gs_cnTabCx, cy - 2, SWP_NOZORDER );
		m_SBar.SetWindowPos( NULL, gs_cnTabCx + gs_cnSepCx, 0, 
								 cx - (gs_cnTabCx + gs_cnSepCx + gs_cnCBarCs), 
								 cy - 2, SWP_NOZORDER );
	}
}

void CViewTabBar::OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp ) 
{
	CSizingControlBar::OnNcCalcSize( bCalcValidRects, lpncsp );

	// To correct border deflated in CSizingControlBar::OnNcCalcSize() 
	CRect rcClient = lpncsp->rgrc[0];
	rcClient.InflateRect(5, 5);
	lpncsp->rgrc[0] = rcClient;
}

void CViewTabBar::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if( m_SBar.m_hWnd == pScrollBar->m_hWnd )
	{
		CFrameWnd* pFrame = GetDockingFrame();
		if( pFrame )
		{
			CView* pView = pFrame->GetActiveView();
			if( pView )
				pView->SendMessage( WM_HSCROLL, MAKELONG(nSBCode, nPos), (LPARAM)pScrollBar->m_hWnd );
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CViewBottomSBar, CSizingControlBar)
	//{{AFX_MSG_MAP(CViewBottomSBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CViewBottomSBar::CViewBottomSBar()
{}

CViewBottomSBar::~CViewBottomSBar()
{}

INT CViewBottomSBar::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	SetBorders();
	if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rctNull( 0, 0, 0, 0 );
	m_SBar.Create( SBS_HORZ | WS_VISIBLE | WS_CHILD, rctNull, this, 2 );
	return 0;
}

void CViewBottomSBar::OnSize( UINT nType, INT cx, INT cy )
{
	CSizingControlBar::OnSize( nType, cx, cy );
	if( m_SBar.m_hWnd )
		m_SBar.SetWindowPos( NULL, 0, 0, cx - gs_cnCBarCs, cy, SWP_NOZORDER );
}

void CViewBottomSBar::OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp ) 
{
	CSizingControlBar::OnNcCalcSize( bCalcValidRects, lpncsp );

	// To correct border deflated in CSizingControlBar::OnNcCalcSize() 
	CRect rcClient = lpncsp->rgrc[0];
	rcClient.InflateRect(5, 5);
	lpncsp->rgrc[0] = rcClient;
}

void CViewBottomSBar::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if( m_SBar.m_hWnd == pScrollBar->m_hWnd )
	{
		CFrameWnd* pFrame = GetDockingFrame();
		if( pFrame )
		{
			CView* pView = pFrame->GetActiveView();
			if( pView )
				pView->SendMessage( WM_HSCROLL, MAKELONG(nSBCode, nPos), (LPARAM)pScrollBar->m_hWnd );
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CViewRightSBar, CSizingControlBar)
	//{{AFX_MSG_MAP(CViewRightSBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CViewRightSBar::CViewRightSBar()
{}

CViewRightSBar::~CViewRightSBar()
{}

INT CViewRightSBar::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	SetBorders();
	if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rctNull( 0, 0, 0, 0 );
	m_SBar.Create( SBS_VERT | WS_VISIBLE | WS_CHILD, rctNull, this, 2 );
	return 0;
}

void CViewRightSBar::OnSize( UINT nType, INT cx, INT cy )
{
	CSizingControlBar::OnSize( nType, cx, cy );
	if( m_SBar.m_hWnd )
		m_SBar.SetWindowPos( NULL, 0, 0, cx, cy, SWP_NOZORDER );
}

void CViewRightSBar::OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp ) 
{
	CSizingControlBar::OnNcCalcSize( bCalcValidRects, lpncsp );

	// To correct border deflated in CSizingControlBar::OnNcCalcSize() 
	CRect rcClient = lpncsp->rgrc[0];
	rcClient.InflateRect(5, 5);
	lpncsp->rgrc[0] = rcClient;
}

void CViewRightSBar::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if( m_SBar.m_hWnd == pScrollBar->m_hWnd )
	{
		CFrameWnd* pFrame = GetDockingFrame();
		if( pFrame )
		{
			CView* pView = pFrame->GetActiveView();
			if( pView )
				pView->SendMessage( WM_VSCROLL, MAKELONG(nSBCode, nPos), (LPARAM)pScrollBar->m_hWnd );
		}
	}
}
