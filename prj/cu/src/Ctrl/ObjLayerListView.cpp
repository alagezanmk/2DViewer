#include "stdafx.h"
#include "ObjLayerListView.h"
#include <cu\MemDC.h>
#include <cu\msg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SObjLayerItem::SObjLayerItem()
{
	pLayer = NULL;
	nFlags = enVisible;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
const int g_cnItemCy = 18;
const int g_cnVisibleCx = 16;
const int g_cnEditCx = 16;
const int g_cnLockCx = 16;

IMPLEMENT_DYNCREATE(CObjLayerListView, CScrollView)
BEGIN_MESSAGE_MAP(CObjLayerListView, CScrollView)
	//{{AFX_MSG_MAP(CObjLayerListView)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_MESSAGE( WM_SIZEPARENT, OnSizeParent )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#ifdef _DEBUG
void CObjLayerListView::AssertValid() const {
	CScrollView::AssertValid(); }

void CObjLayerListView::Dump(CDumpContext& dc) const {
	CScrollView::Dump(dc); }
#endif //_DEBUG

CObjLayerListView::CObjLayerListView() {
	m_nCurSel = -1; }

CObjLayerListView::~CObjLayerListView() {
	ResetContent(); }

void CObjLayerListView::ResetContent() 
{
	INT nCount = m_arpLayer.GetSize();
	if( 0 == nCount )
		return;

	SObjLayerItem** ppItem = (SObjLayerItem**)m_arpLayer.GetData();

	for( INT i = 0; i < nCount; i++ )
		delete ppItem[i];
	
	m_arpLayer.RemoveAll();
	InvalidateRect( NULL, FALSE );
	RecalcLayout();
}

LRESULT CObjLayerListView::OnSizeParent( WPARAM, LPARAM lParam )
{
	AFX_SIZEPARENTPARAMS* lpLayout = (AFX_SIZEPARENTPARAMS*)lParam;
	CRect& rrct = (CRect)lpLayout->rect;
	if( m_hWnd )
		SetWindowPos( NULL, rrct.left, rrct.top + 2, rrct.Width(), rrct.Height() - 2, SWP_NOZORDER );

	return 0;
}

void CObjLayerListView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	RecalcLayout();
}

void CObjLayerListView::GetVisibleBtnRect( CRect* pRect, INT nIndex /*=0*/ )
{
	pRect->left = 1;
	pRect->top = nIndex * g_cnItemCy;
	pRect->right = pRect->left + g_cnVisibleCx;
	pRect->bottom = pRect->top + g_cnItemCy - 1;
}

void CObjLayerListView::GetEditBtnRect( CRect* pRect, INT nIndex /*0*/)
{
	pRect->left = g_cnVisibleCx + 1;
	pRect->top = nIndex * g_cnItemCy;
	pRect->right = pRect->left + g_cnEditCx;
	pRect->bottom = pRect->top + g_cnItemCy - 1;
}

void CObjLayerListView::GetLabelRect( CRect* pRect, INT nIndex /*= 0*/ )
{
	CRect rcClient;
	GetClientRect( rcClient );

	pRect->left = g_cnVisibleCx + g_cnEditCx + 2;
	pRect->top = nIndex * g_cnItemCy;
	pRect->right = rcClient.right - g_cnLockCx;
	pRect->bottom = pRect->top + g_cnItemCy;
}

BOOL CObjLayerListView::OnEraseBkgnd( CDC* pDC ) {
	return TRUE; }

void CObjLayerListView::OnDraw(CDC* pDC)
{
	CMemDC MemDC;

	//AfsSendCmd( AfxGetMainWnd(), 1 );

	CRect rcClient;
	GetClientRect( rcClient );
	INT nCCx = rcClient.Width();
	INT nCCy = rcClient.Height();

	VERIFY( MemDC.Create( pDC, nCCx, nCCy ) );

	// Fill Background with window color
	HBRUSH hbrWnd = GetSysColorBrush( COLOR_WINDOW );
	FillRect( MemDC.m_hDC, rcClient, hbrWnd );

	// Set Scroll origin to MemDC
	INT nSx = GetScrollPos( SB_HORZ );
	INT nSy = GetScrollPos( SB_VERT );
	MemDC.SetViewportOrg( -nSx, -nSy );

	// Get Item data
	INT nCount = m_arpLayer.GetSize();
	SObjLayerItem** ppItem = (SObjLayerItem**)m_arpLayer.GetData();

	// Fill left side bar for Visible & Edit btn rects
	CRect rct, rc1, rc2;
	rct = rcClient;
	rct.right = g_cnVisibleCx + g_cnEditCx + 1;
	rct.bottom = nCount * g_cnItemCy;
	HBRUSH hbrBtnFace = GetSysColorBrush( COLOR_BTNFACE );
	HBRUSH hbrHilite = GetSysColorBrush( COLOR_HIGHLIGHT );
	FillRect( MemDC.m_hDC, rct, hbrBtnFace );

	// Draw left side bar separator
	rct.left = rct.right;
	rct.right += 2;
	COLORREF crfBtnShadow = GetSysColor( COLOR_BTNSHADOW );
	COLORREF crfBtnHilite = GetSysColor( COLOR_BTNHIGHLIGHT );
	MemDC.Draw3dRect( rct, crfBtnShadow, crfBtnHilite );

	// Initialize Label rect
	GetLabelRect( &rct );
	rct.bottom = --rct.top + 1;
	rct.right = nCCx;

	CRect rctLabel( rct );
	rctLabel.top = --(--rctLabel.bottom) - g_cnItemCy + 2;
	
	COLORREF crfHiliteText = GetSysColor( COLOR_HIGHLIGHTTEXT );
	COLORREF crfText = GetSysColor( COLOR_WINDOWTEXT );
	MemDC.SetTextColor( crfText );
	MemDC.SetBkMode( TRANSPARENT );

	CFont* pOldFnt;
	CFont Fnt;
	Fnt.Attach( (HFONT)GetStockObject( DEFAULT_GUI_FONT ) );
	pOldFnt = MemDC.SelectObject( &Fnt );

	// Initialize Visible & Edit rect
	GetVisibleBtnRect( &rc1 );
	GetEditBtnRect( &rc2 );
	for( INT i = 0; i < nCount; i++ )
	{
		MemDC.Draw3dRect( rc1, crfBtnShadow, crfBtnHilite );
		MemDC.Draw3dRect( rc2, crfBtnShadow, crfBtnHilite );

		if( SObjLayerItem::enVisible & ppItem[i]->nFlags )
		{
			MemDC.MoveTo( rc1.left + 2, rc1.top + 2 );
			MemDC.LineTo( rc1.right - 2, rc1.bottom - 2 );

			MemDC.MoveTo( rc1.right - 2, rc1.top + 2 );
			MemDC.LineTo( rc1.left + 2, rc1.bottom - 2 );
		} 

		rc1.OffsetRect( 0, g_cnItemCy );
		rc2.OffsetRect( 0, g_cnItemCy );
		rct.OffsetRect( 0, g_cnItemCy );
		rctLabel.OffsetRect( 0, g_cnItemCy );

		if( i == m_nCurSel )
		{
			FillRect( MemDC.m_hDC, rctLabel, hbrHilite );
			MemDC.SetTextColor( crfHiliteText );
			MemDC.DrawText( ppItem[i]->cszName, rctLabel, DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS );
			MemDC.SetTextColor( crfText );
		}
		else
			MemDC.DrawText( ppItem[i]->cszName, rctLabel, DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS );

		FillRect( MemDC.m_hDC, rct, hbrBtnFace );
	}

	rct = rcClient;
	rct.top = nCount * g_cnItemCy;
	rct.bottom += nSy;
	FillRect( MemDC.m_hDC, rct, hbrBtnFace );

	MemDC.SelectObject( pOldFnt );
	Fnt.Detach();

	MemDC.SetViewportOrg( 0, 0 );
	pDC->SetViewportOrg( 0, 0 );
	MemDC.BitBltTo( pDC );
}

void CObjLayerListView::OnLButtonUp( UINT nFlags, CPoint point ) 
{
	point.x += GetScrollPos( SB_HORZ );
	point.y += GetScrollPos( SB_VERT );

	INT nItem = point.y / g_cnItemCy;
	if( nItem >= m_arpLayer.GetSize() )
		return;

	CRect rct;
	GetVisibleBtnRect( &rct, nItem );
	if( rct.PtInRect( point ) )
	{
		if( m_hMsg && AfsSendMsg( m_hMsg, CM_LC_VISIBLE_CLICK, nItem ) )
		{
			SObjLayerItem* pItem = (SObjLayerItem*)m_arpLayer.GetAt( nItem );
			if( SObjLayerItem::enVisible & pItem->nFlags )
				pItem->nFlags &= ~SObjLayerItem::enVisible;
			else
				pItem->nFlags |= SObjLayerItem::enVisible;

			InvalidateRect( NULL, TRUE );
		}

		return;
	}

	GetEditBtnRect( &rct, nItem );
	if( rct.PtInRect( point ) )
	{
		if( m_hMsg && AfsSendMsg( m_hMsg, CM_LC_EDIT_CLICK, nItem ) )
		{
			SObjLayerItem* pItem = (SObjLayerItem*)m_arpLayer.GetAt( nItem );
			if( SObjLayerItem::enVisible & pItem->nFlags )
				pItem->nFlags &= ~SObjLayerItem::enVisible;
			else
				pItem->nFlags |= SObjLayerItem::enVisible;

			InvalidateRect( NULL, TRUE );
		}

		return;
	}

	GetLabelRect( &rct, nItem );
	if( rct.PtInRect( point ) )
	{
		if( m_hMsg && AfsSendMsg( m_hMsg, CM_LC_LAYER_SEL, nItem ) )
		{
			m_nCurSel = nItem;
			SObjLayerItem* pItem = (SObjLayerItem*)m_arpLayer.GetAt( nItem );
			if( SObjLayerItem::enVisible & pItem->nFlags )
				pItem->nFlags &= ~SObjLayerItem::enVisible;
			else
				pItem->nFlags |= SObjLayerItem::enVisible;

			InvalidateRect( NULL, TRUE );
		}
		return;
	}
}

void CObjLayerListView::RecalcLayout()
{
	if( NULL == m_hWnd )
		return;

	CRect rct;
	GetClientRect( rct );
	CSize sizeTotal;
	sizeTotal.cx = rct.Width();
	sizeTotal.cy = m_arpLayer.GetSize() * g_cnItemCy;
	SetScrollSizes(MM_TEXT, sizeTotal);
}