#include "stdafx.h"
#include <cu\MemDC.h>
#include "ObjLayerCtrl.h"
#include "Resource.h"
#include <cu\msg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CObjLayerCtrl, CFrameWnd)
	//{{AFX_MSG_MAP(CObjLayerCtrl)
	ON_WM_CREATE()
 	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_UPDATE_COMMAND_UI_RANGE( ID_LYR_MOVE_LOCK, ID_LYR_LOCK_ALL, OnLockBarUI )
	ON_UPDATE_COMMAND_UI_RANGE( ID_LYR_DELETE, ID_LYR_NEW_GRP, OnBottomBarUI )
	ON_COMMAND_RANGE( ID_LYR_DELETE, ID_LYR_NEW_GRP, OnBottomBar )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define ID_LAYER_LIST	1000
const int g_cnHeaderCy = 24;
const int g_cnStatusCy = 22;
CObjLayerCtrl::CObjLayerCtrl()
{
	m_plstviewLayer = NULL;
}

CObjLayerCtrl::~CObjLayerCtrl()
{}

BOOL CObjLayerCtrl::PreCreateWindow( CREATESTRUCT& cs ) 
{
	if( FALSE == CFrameWnd::PreCreateWindow( cs ) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	return TRUE;
}

INT CObjLayerCtrl::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( CFrameWnd::OnCreate(lpCreateStruct) == -1 )
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY, nullRECT, IDR_LYR_LOCKBAR ) ||
		!m_wndToolBar.LoadToolBar( IDR_LYR_LOCKBAR ) )
	{
		TRACE0("CObjLayerCtrl::OnCreate - Lock Bar create failed\n");
		return -1;      // fail to create
	}

	if (!m_wndBottomBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM
		| CBRS_TOOLTIPS | CBRS_FLYBY, nullRECT, IDR_LYR_BOTTOMBAR ) ||
		!m_wndBottomBar.LoadToolBar( IDR_LYR_BOTTOMBAR ) )
	{
		TRACE0("CObjLayerCtrl::OnCreate - Bottom Bar create failed\n");
		return -1;      // fail to create
	}

	ASSERT( NULL == m_plstviewLayer );
	m_plstviewLayer = new CObjLayerListView;
	if( FALSE == m_plstviewLayer->Create( NULL, NULL, WS_VISIBLE | WS_CHILD | WS_TABSTOP | 
										 WS_CLIPCHILDREN, nullRECT, this, ID_LAYER_LIST, NULL ) )
		return -1;

	m_plstviewLayer->OnInitialUpdate();

	return 0;
}

void CObjLayerCtrl::OnSize( UINT nType, INT cx, INT cy )
{
	CFrameWnd::OnSize( nType, cx, cy );
	CRect rct;

	if( m_wndBottomBar.m_hWnd )
	{
		INT nCount = m_wndBottomBar.GetCount();
		m_wndBottomBar.GetItemRect( nCount - 1, rct );

		INT dx = cx - rct.right;
		m_wndBottomBar.GetWindowRect( rct );
		ScreenToClient( &rct );
		rct.OffsetRect( dx, 2 );
	
		m_wndBottomBar.MoveWindow( rct );
	}
}

BOOL CObjLayerCtrl::OnEraseBkgnd( CDC* pDC ) {
	return TRUE; }

void CObjLayerCtrl::OnPaint()
{
	CPaintDC dc(this);
	CMemDC MemDC;

	INT nMaxCy = max( g_cnHeaderCy, g_cnStatusCy );

	// Draw Header Line
	CRect rcClient; 
	GetClientRect( rcClient );
	INT nCCx = rcClient.Width();
	INT nCCy = rcClient.Height();

	CRect rct = rcClient;
	VERIFY( MemDC.Create( &dc, nCCx, nMaxCy ) );

	rct.SetRect( 0, 0, nCCx, g_cnHeaderCy );
	HBRUSH hbrBtnFace = GetSysColorBrush( COLOR_BTNFACE );
	FillRect( MemDC.m_hDC, rct, hbrBtnFace );

	rct.top = rct.bottom - 2; 
	COLORREF crfBtnShadow = GetSysColor( COLOR_BTNSHADOW );
	COLORREF crfBtnHilite = GetSysColor( COLOR_BTNHIGHLIGHT );
	MemDC.Draw3dRect( rct, crfBtnShadow, crfBtnHilite );
	MemDC.BitBltTo( &dc );
	
	// Draw Status bar Line
	rct.SetRect( 0, 0, nCCx, g_cnStatusCy );
	FillRect( MemDC.m_hDC, rct, hbrBtnFace );

	rct.bottom = rct.top + 2;
	MemDC.Draw3dRect( rct, crfBtnShadow, crfBtnHilite );
	MemDC.BitBltTo( &dc, 0, rcClient.bottom - g_cnStatusCy, nCCx, g_cnStatusCy );
}

INT CObjLayerCtrl::Find( LPLayer pLayer )
{
	INT nCount = m_plstviewLayer->m_arpLayer.GetSize();
	SObjLayerItem** ppItem = (SObjLayerItem**)m_plstviewLayer->m_arpLayer.GetData();

	for( INT i = 0; i < nCount; i++ )
	{
		if( ppItem[i]->pLayer == pLayer )
			return i;
	}

	return -1;
}

BOOL CObjLayerCtrl::Add( LPLayer pLayer, LPCTSTR pctszName ) 
{
	if( -1 != Find( pLayer ) )
		return FALSE;

	SObjLayerItem* pLayerItem = new SObjLayerItem;
	ASSERT( pLayerItem );
	pLayerItem->pLayer = pLayer;
	pLayerItem->cszName = pctszName;
	m_plstviewLayer->m_arpLayer.Add( pLayerItem );
	m_plstviewLayer->RecalcLayout();
	return TRUE;
}

BOOL CObjLayerCtrl::Remove( LPLayer pLayer ) 
{
	INT nIndex = Find( pLayer );
	if( -1 == nIndex )
	{
		ASSERT( FALSE );
		return FALSE;
	}

	m_plstviewLayer->m_arpLayer.RemoveAt( nIndex );
	m_plstviewLayer->RecalcLayout();
	return TRUE;
}

BOOL CObjLayerCtrl::RemoveAt( INT nIndex ) 
{
	if( nIndex >= m_plstviewLayer->m_arpLayer.GetSize() )
	{
		ASSERT( FALSE );
		return FALSE;
	}

	m_plstviewLayer->m_arpLayer.RemoveAt( nIndex );
	m_plstviewLayer->RecalcLayout();
	return TRUE;
}

void CObjLayerCtrl::ResetContent() {
	m_plstviewLayer->ResetContent(); }

void CObjLayerCtrl::SetCurSel( INT nIndex )
{
	m_plstviewLayer->m_nCurSel = nIndex;
	m_plstviewLayer->InvalidateRect( NULL, FALSE );
}

void CObjLayerCtrl::SetCurSel( LPLayer pLayer )
{
	INT nIndex = Find( pLayer );
	if( -1 == nIndex )
		return;

	SetCurSel( nIndex );
}

LPLayer CObjLayerCtrl::GetAt( INT nIndex )
{
	if( nIndex >= m_plstviewLayer->m_arpLayer.GetSize() )
		return NULL;

	return (LPLayer)((SObjLayerItem*)m_plstviewLayer->m_arpLayer.GetAt( nIndex ))->pLayer;
}

INT CObjLayerCtrl::GetCurSel() {
	return m_plstviewLayer->m_nCurSel; }

void CObjLayerCtrl::Connect( HWND hWnd ) 
{
	if( m_plstviewLayer )
	{
		m_plstviewLayer->Connect( hWnd );
		m_hMsg = hWnd; 
	}
}

void CObjLayerCtrl::OnLockBarUI( CCmdUI* pCmdUI ) {
	pCmdUI->Enable(); }

void CObjLayerCtrl::OnBottomBarUI( CCmdUI* pCmdUI ) {
	pCmdUI->Enable(); }

void CObjLayerCtrl::OnBottomBar( UINT nID )
{
	switch( nID )
	{
	case ID_LYR_NEW_GRP:
		AfsSendCmd( m_hMsg, CM_LC_BUTTON_CLICK, NEW_LAYER_GROUP );
		return;

	case ID_LYR_NEW:
		AfsSendCmd( m_hMsg, CM_LC_BUTTON_CLICK, NEW_LAYER );
		return;

	case ID_LYR_DELETE:
		AfsSendCmd( m_hMsg, CM_LC_BUTTON_CLICK, DELETE_LAYER );
		return;
	}
}	