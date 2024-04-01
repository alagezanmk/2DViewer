#include "stdafx.h"
#include "MSComboBox.h"
#include "MSListBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMSListBox, CListBox)
	//{{AFX_MSG_MAP(CMSListBox)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMSListBox::CMSListBox()
{
	m_pCmbCtrl = NULL;
	m_bFirstSelected = FALSE;

	m_nPrevSelCnt = 0;
	m_pnPrevSel = NULL;
}

CMSListBox::~CMSListBox()
{}

void CMSListBox::OnKillFocus( CWnd* pNewWnd )
{
	CListBox::OnKillFocus( pNewWnd );
	m_pCmbCtrl->PostMessage( WM_MSLB_CLOSE );
}

void CMSListBox::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	switch( nChar )
	{
	case VK_ESCAPE:
	case VK_RETURN:
		m_pCmbCtrl->PostMessage( WM_MSLB_CLOSE, VK_ESCAPE == nChar );
		return;
	}

	CListBox::OnKeyDown( nChar, nRepCnt, nFlags );
}

void CMSListBox::OnMouseMove( UINT nFlags, CPoint point )
{
	if( m_bFirstSelected )
	{
		CListBox::OnMouseMove( nFlags, point );
		return;
	}

	BOOL bOutSide;
	INT nItem = ItemFromPoint( point, bOutSide );
	if( FALSE == bOutSide )
	{
		INT nSel = GetCurSel();
		if( LB_ERR != nSel )
			SetSel( nSel, FALSE );

		SetSel( nItem );
	}
}

void CMSListBox::OnLButtonUp( UINT nFlags, CPoint point )
{
	CListBox::OnLButtonUp( nFlags, point );

	BOOL bOutSide;
	INT nItem = ItemFromPoint( point, bOutSide );
	if( nItem >= 0 )
	{
		BOOL bSelection;
		
		if( NULL == m_pCmbCtrl )
		{
			m_bFirstSelected = TRUE;
			return;
		}

		CMSComboBox::NMSELCHANGE nm;
		nm.code = CMSComboBox::NM_SELCHANGE;
		nm.hwndFrom = m_pCmbCtrl->m_hWnd;
		nm.idFrom = m_pCmbCtrl->GetDlgCtrlID();
		CWnd* pCmbParent = m_pCmbCtrl->GetParent();

		if( MK_SHIFT & nFlags )
		{
			m_pCmbCtrl->SetCurSel( -1 );

			INT nSelCnt = GetSelCount();
			if( nSelCnt )
			{
				PINT pnSel = new INT[nSelCnt];
				if( NULL == pnSel )
				{
					ASSERT( pnSel );
					return;
				}

				GetSelItems( nSelCnt, pnSel );
				nm.nIndex = pnSel[0];
				nm.bSelect = TRUE;
				nm.bSetCurSel = TRUE;
				if( 1 == pCmbParent->SendMessage( WM_NOTIFY, nm.idFrom, (LPARAM)&nm ) )
				{
					bSelection = m_pCmbCtrl->GetSel( pnSel[0] );
					SetSel( pnSel[0], bSelection );
				}
				else
					m_pCmbCtrl->SetCurSel( pnSel[0] );

				for( INT i = 1; i < nSelCnt; i++ )
				{
					nm.nIndex = pnSel[i];
					nm.bSelect = TRUE;
					nm.bSetCurSel = FALSE;
					if( 1 == pCmbParent->SendMessage( WM_NOTIFY, nm.idFrom, (LPARAM)&nm ) )
					{
						bSelection = m_pCmbCtrl->GetSel( pnSel[i] );
						SetSel( pnSel[i], bSelection );
					}
					else
						m_pCmbCtrl->SetSel( pnSel[i] );
				}

				delete pnSel;
			}
		}
		else if( 0 == ((MK_CONTROL | MK_SHIFT) & nFlags) || FALSE == m_bFirstSelected )
		{
			nm.nIndex = nItem;
			nm.bSelect = TRUE;
			nm.bSetCurSel = TRUE;
			if( 1 == pCmbParent->SendMessage( WM_NOTIFY, nm.idFrom, (LPARAM)&nm ) )
			{
				bSelection = m_pCmbCtrl->GetSel( nItem );
				SetSel( nItem, bSelection );
			}
			else
			{
				m_pCmbCtrl->SetCurSel( nItem );
				SetSel( nItem, TRUE );
			}
		}
		else
		{
			bSelection = GetSel( nItem );
			nm.nIndex = nItem;
			nm.bSelect = bSelection;
			nm.bSetCurSel = FALSE;

			if( 1 == pCmbParent->SendMessage( WM_NOTIFY, nm.idFrom, (LPARAM)&nm ) )
			{
				bSelection = m_pCmbCtrl->GetSel( nItem );
				SetSel( nItem, bSelection );
			}
			else
				m_pCmbCtrl->SetSel( nItem, bSelection );
		}

		m_bFirstSelected = TRUE;
	}
}

void CMSListBox::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	CListBox::OnLButtonDblClk( nFlags, point );
	m_pCmbCtrl->PostMessage( WM_MSLB_CLOSE );
}

void CMSListBox::DrawItem( LPDRAWITEMSTRUCT lpDrawItem )
{
	lpDrawItem->CtlType = ODT_COMBOBOX;
	if( -1 == lpDrawItem->itemID )
		return;

	lpDrawItem->itemData = (DWORD)m_pCmbCtrl->GetItem( lpDrawItem->itemID );
	m_pCmbCtrl->DrawItem( lpDrawItem );
}

void CMSListBox::MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItem )
{
	if( m_pCmbCtrl )
		m_pCmbCtrl->MeasureItem( lpMeasureItem );

	HFONT hFont = (HFONT)GetFont()->m_hObject;
	ASSERT( hFont );
	HDC hDC = ::GetDC( m_hWnd );
	HFONT hOldFont = (HFONT)SelectObject( hDC, hFont );
	TEXTMETRIC tm;
	GetTextMetrics( hDC, &tm );
	if( lpMeasureItem->itemHeight < (UINT)tm.tmHeight + 1 )
		lpMeasureItem->itemHeight = tm.tmHeight + 1;

	SelectObject( hDC, hOldFont );
	::ReleaseDC( m_hWnd, hDC );
}

int CMSListBox::CompareItem( LPCOMPAREITEMSTRUCT lpCompareItem )
{
	if( m_pCmbCtrl )
		return m_pCmbCtrl->CompareItem( lpCompareItem );

	return 0;
}

void CMSListBox::DeleteItem( LPDELETEITEMSTRUCT lpDeleteItem )
{}

int CMSListBox::VKeyToItem( UINT nKey, UINT nIndex ) {
	return 0; }

int CMSListBox::CharToItem( UINT nKey, UINT nIndex ) {
	return 0; }
