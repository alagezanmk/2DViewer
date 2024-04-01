#include "stdafx.h"
#include "PropObjectSelListCtrl.h"
#include "PropObjectSelComboBox.h"
#include <cu\Msg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Bug: Scroll Bar click and drag is not working
// Todo: Make the popup list ctrl as resizable, with a arrow drawing at right bottom

/////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CPropObjectSelListCtrl, CMSTreeCtrl)
	//{{AFX_MSG_MAP(CPropObjectSelListCtrl)
	ON_NOTIFY_REFLECT( NM_CUSTOMDRAW, OnCustomdraw )
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_CANCELMODE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPropObjectSelListCtrl::CPropObjectSelListCtrl()
{
	m_pComboBox = NULL;
	m_hMouseHoverItem = NULL;
}

CPropObjectSelListCtrl::~CPropObjectSelListCtrl()
{}

BOOL CPropObjectSelListCtrl::SendSelChangeNotify( HTREEITEM hItem, BOOL bSelect /*= TRUE*/, BOOL bMultipleSel /*= TRUE*/ )
{
	ASSERT( m_pComboBox );

	CPropObjectSelComboBox::NMSELCHANGE nm;
	nm.hItem = hItem;
	nm.bSelect = bSelect;
	nm.bMultipleSel = bMultipleSel;
	BOOL bResult = SendNotify( m_pComboBox, CPropObjectSelComboBox::NM_SELCHANGE, &nm );
	return bResult;
}

void CPropObjectSelListCtrl::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	switch( nChar )
	{
	case VK_ESCAPE:
	case VK_RETURN:
		Close();
		return;
	}
	
	CMSTreeCtrl::OnKeyDown( nChar, nRepCnt, nFlags );
}

void CPropObjectSelListCtrl::OnLButtonDown( UINT nFlags, CPoint point )
{
	CRect rctWnd;
	GetWindowRect( rctWnd );

	CPoint ptScreen = point;
	ClientToScreen( &ptScreen );

	if( FALSE == rctWnd.PtInRect( ptScreen ) )
	{
		Close();
		return;
	}

	CMSTreeCtrl::OnLButtonDown( nFlags, point );
}

// The OnKillFocus of the control overrided to close the Tree Control when it loses the Window focus
void CPropObjectSelListCtrl::OnKillFocus( CWnd* pNewWnd )
{
	CMSTreeCtrl::OnKillFocus( pNewWnd );
	Close();
}

void CPropObjectSelListCtrl::OnCancelMode()
{
	if( this == GetCapture() )
		Close();

	CMSTreeCtrl::OnCancelMode();
}

// Call this function to close the Tree control's parent which is the control site.
// It will close only if this control visible
void CPropObjectSelListCtrl::Close()
{
	if( m_pComboBox && IsWindowVisible() )
	{
		if( this == GetCapture() )
			ReleaseCapture();

		m_pComboBox->CloseListBox();
	}
}

void CPropObjectSelListCtrl::OnMouseMove( UINT nFlags, CPoint point )
{
	if( 0 == (nFlags & (MK_LBUTTON | MK_RBUTTON)) )
	{
		UINT uFlags;
		HTREEITEM hItem = HitTest( point, &uFlags );
		if( hItem && 0 == (TVHT_ONITEM & uFlags) )
			hItem = NULL;

		CRect rect;
		if( m_hMouseHoverItem && m_hMouseHoverItem != hItem )
		{
			GetItemRect( m_hMouseHoverItem, rect, TRUE );
			InvalidateRect( rect, FALSE );
			m_hMouseHoverItem = NULL;
		}

		if( hItem )
		{
			GetItemRect( hItem, rect, TRUE );
			InvalidateRect( rect, FALSE );
			m_hMouseHoverItem = hItem;
		}
	}

	CMSTreeCtrl::OnMouseMove( nFlags, point );
}

void CPropObjectSelListCtrl::OnCustomdraw( NMHDR* pNMHDR, LRESULT* lpResult )
{
	NMTVCUSTOMDRAW* nmcd = (NMTVCUSTOMDRAW*)pNMHDR;
	*lpResult = CDRF_DODEFAULT;

	switch( nmcd->nmcd.dwDrawStage )
	{
	case CDDS_PREPAINT:
		*lpResult = CDRF_NOTIFYITEMDRAW; 
		return;

	case CDDS_ITEMPREPAINT:
		*lpResult = CDRF_NOTIFYPOSTPAINT;
		return;

	case CDDS_ITEMPOSTPAINT:
		{
			HTREEITEM hItem = (HTREEITEM)nmcd->nmcd.dwItemSpec;
			if( m_hMouseHoverItem == hItem )
			{
				CDC dc;
				dc.Attach( nmcd->nmcd.hdc );

				CRect rect;
				GetItemRect( hItem, rect, TRUE );
				rect.top = rect.bottom - 1;

				COLORREF crfWindowText = GetSysColor( COLOR_WINDOWTEXT );
				dc.FillSolidRect( rect, crfWindowText );
				dc.Detach();
			}

			*lpResult = CDRF_SKIPDEFAULT;
		}
		break;
	}
}
