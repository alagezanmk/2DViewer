#include "stdafx.h"
#include "TabCtrlEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CTabCtrlEx, CTabCtrl)
BEGIN_MESSAGE_MAP(CTabCtrlEx, CTabCtrl)
	//{{AFX_MSG_MAP(CTabCtrlEx)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_NOTIFY_REFLECT(TCN_SELCHANGING, OnSelChanging)
	ON_CBN_SELCHANGE(ID_EVT_COMBO,OnComboSelChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTabCtrlEx::CTabCtrlEx()
{
	m_nPrevTab = 0;
	m_nMsgID = -1;
}

CTabCtrlEx::~CTabCtrlEx()
{}

void CTabCtrlEx::OnComboSelChange()
{
	if( m_nMsgID > 0 )
		::SendMessage( GetParent()->m_hWnd, m_nMsgID, 0, 0 );	
}

void CTabCtrlEx::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) 
{
	if( VK_RETURN == nChar )
		nChar = nChar;
	CTabCtrl::OnKeyDown( nChar, nRepCnt, nFlags );
}

BOOL CTabCtrlEx::OnEraseBkgnd( CDC* pDC )
{
//	INT nRectCy = 22;

	CRect rect;
	GetClientRect( rect );
//	rect.bottom = nRectCy;

	HBRUSH hBr = GetSysColorBrush( COLOR_BTNFACE );
	FillRect( pDC->m_hDC, rect, hBr );
	return TRUE;
}

BOOL CTabCtrlEx::SubclassDlgItem( UINT nID, CWnd* pParent )
{
//	if (!CTabCtrl::SubclassDlgItem(nID, pParent))
//		return FALSE;

	ModifyStyle( WS_BORDER | TCS_TABS, TCS_OWNERDRAWFIXED );

	if( !IsTabEnabled( 0 ) ) 
	{
		int nTab = NextEnabledTab( 0, TRUE );
		SetActiveTab( nTab );
	}
	return TRUE;
}

void CTabCtrlEx::DrawItem( LPDRAWITEMSTRUCT pDrawItem )
{
	int nItem = pDrawItem->itemID;

	// Get tab item info
	TCHAR text[128];
	TCITEM tci;
	tci.mask = TCIF_TEXT;
	tci.pszText = text;
	tci.cchTextMax = sizeof(text);
	GetItem( nItem, &tci );

	// Use draw item DC
	CDC dc;
	dc.Attach( pDrawItem->hDC );

	// Calculate text rectangle and color
	CRect rc = pDrawItem->rcItem;
	rc += CPoint( 1, 4 ); // ?? by trial and error

	// draw the text
	dc.SetBkMode( TRANSPARENT );
	OnDrawText(dc, rc, text, !IsTabEnabled(nItem));

	dc.Detach();
}

void CTabCtrlEx::OnDrawText( CDC& dc, CRect rc, CString cszText, BOOL bDisabled )
{
	dc.SetTextColor( GetSysColor( bDisabled ?COLOR_3DHILIGHT :COLOR_BTNTEXT ) );
	dc.DrawText( cszText, &rc, DT_CENTER | DT_VCENTER );

	if (bDisabled) 
	{
		rc += CPoint( -1,-1 );
		dc.SetTextColor( GetSysColor( COLOR_GRAYTEXT ) );
		dc.DrawText( cszText, &rc, DT_CENTER | DT_VCENTER );
	}
}

int CTabCtrlEx::SetCurSel( int nItem )
{
	if( IsTabEnabled( nItem ) )
		return CTabCtrl::SetCurSel( nItem );

	return -1;
}

void CTabCtrlEx::OnSelChanging( NMHDR* pnmh, LRESULT* lpResult )
{
	// Store the current Tab index
	m_nPrevTab = GetCurSel();

	// Figure out index of new tab we are about to go to, as opposed
	// to the current one we're at. Believe it or not, Windows doesn't
	// pass this info
	TC_HITTESTINFO htinfo;
	GetCursorPos( &htinfo.pt );
	ScreenToClient( &htinfo.pt );
	int nNewTab = HitTest( &htinfo );

	if( nNewTab >= 0 && !IsTabEnabled( nNewTab ) )
		*lpResult = TRUE;
}

BOOL CTabCtrlEx::PreTranslateMessage( MSG* pMsg )
{
	if (pMsg->message == WM_KEYDOWN &&
		(pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT)) 
	{

		int nNewTab = pMsg->wParam == VK_LEFT
						?PrevEnabledTab(GetCurSel(), FALSE ) 
						:NextEnabledTab(GetCurSel(), FALSE );

		if( nNewTab >= 0 )
			SetActiveTab( nNewTab );

		return TRUE;
	}
	return CTabCtrl::PreTranslateMessage( pMsg );
}

BOOL CTabCtrlEx::IsTabEnabled( UINT nTab )
{
	for( INT nCount = 0; nCount < m_unarDisblTab.GetSize(); nCount++ )
		if( m_unarDisblTab.ElementAt( nCount ) == nTab )
			return FALSE;

	return TRUE;
}

void CTabCtrlEx::DisableTab( UINT nTab )
{
	if( IsTabEnabled( nTab ) )
		m_unarDisblTab.Add( nTab );
}

void CTabCtrlEx::EnableTab( UINT nTab )
{
	for( INT nCount = 0; nCount < m_unarDisblTab.GetSize(); nCount++ )
	{
		if( m_unarDisblTab.ElementAt(nCount) == nTab )
			m_unarDisblTab.RemoveAt(nCount);
	}
}

/////////////////////////////////////////////////////////////////////////////
// Helper to set the active page, when moving backwards (left-arrow and
// Control-Shift-Tab). Must simulate Windows messages to tell parent I
// am changing the tab; SetCurSel does not do this!!
//
// In normal operation, this fn will always succeed, because I don't call it
// unless I already know IsTabEnabled() = TRUE; but if you call SetActiveTab
// with a random value, it could fail.
BOOL CTabCtrlEx::SetActiveTab(UINT nNewTab)
{

	// Send the parent TCN_SELCHANGING
	NMHDR nmh;
	nmh.hwndFrom = m_hWnd;
	nmh.idFrom = GetDlgCtrlID();
	nmh.code = TCN_SELCHANGING;

	if( GetParent()->SendMessage( WM_NOTIFY, nmh.idFrom, (LPARAM)&nmh) >= 0 )
	{
		// OK to change: set the new tab
		SetCurSel( nNewTab );

		// Send parent TCN_SELCHANGE
		nmh.code = TCN_SELCHANGE;
		GetParent()->SendMessage( WM_NOTIFY, nmh.idFrom, (LPARAM)&nmh );
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Return the index of the next enabled tab after a given index, or -1 if none
// (0 = first tab).
// If bWrap is TRUE, wrap from beginning to end; otherwise stop at zero.
INT CTabCtrlEx::NextEnabledTab( INT nCurrentTab, BOOL bWrap )
{
	int nTabs = GetItemCount();
	for( int nTab = nCurrentTab + 1; nTab != nCurrentTab; nTab++ ) 
	{
		if( nTab >= nTabs ) 
		{
			if( FALSE == bWrap )
				return -1;

			nTab = 0;
		}
		if( IsTabEnabled( nTab ) ) 
			return nTab;
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////
// Return the index of the previous enabled tab before a given index, or -1.
// (0 = first tab).
// If bWrap is TRUE, wrap from beginning to end; otherwise stop at zero.
INT CTabCtrlEx::PrevEnabledTab( INT nCurrentTab, BOOL bWrap )
{
	for( INT nTab = nCurrentTab-1; nTab != nCurrentTab; nTab-- ) 
	{
		if (nTab < 0) 
		{
			if( FALSE == bWrap )
				return -1;

			nTab = GetItemCount() - 1;
		}

		if( IsTabEnabled( nTab ) ) 
			return nTab;
	}

	return -1;
}