#include "stdafx.h"
#include "MSComboBox.h"
#include "ODComboBoxPriv.h"
#include <cu\Key.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////////////////
struct CMSComboBox::SItem
{
	SItem();
	virtual ~SItem();
	
	INT		nSel;
	DWORD   dwItemData;
};

CMSComboBox::SItem::SItem()
{
	nSel = 0;
	dwItemData = 0;
}

CMSComboBox::SItem::~SItem()
{}

/////////////////////////////////////////////////////////////////////////////////////////
#define _CS_DD_BTN_DOWN			1	// Dropdown Button DOWN

#define _Is_DDBtnDown()				(0 != (_CS_DD_BTN_DOWN &m_nState))			///< Is Dropdown Button DOWN

#define _Is_LBSelVisible_s()		(0 != (CMSComboBox::CS_LBSEL_VISIBLE & m_nStyle))
#define _Set_LBSelVisible_s()		(m_nStyle | CMSComboBox::CS_LBSEL_VISIBLE)
#define _Reset_LBSelVisible_s()		(m_nStyle &= ~CMSComboBox::CS_LBSEL_VISIBLE)

#define _Is_ShowCurSelEdit_s()		(0 != (CMSComboBox::CS_SHOWCURSEL_EDIT & m_nStyle))
#define _Set_ShowCurSelEdit_s()		(m_nStyle | CMSComboBox::CS_SHOWCURSEL_EDIT)
#define _Reset_ShowCurSelEdit_s()	(m_nStyle &= ~CMSComboBox::CS_SHOWCURSEL_EDIT)

/////////////////////////////////////////////////////////////////////////////////////////
#define ID_LIST_CTRL 100
BEGIN_MESSAGE_MAP(CMSComboBox, CODComboBox)
	//{{AFX_MSG_MAP(CMSComboBox)
	ON_WM_PAINT()
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE( WM_MSLB_CLOSE, OnCloseListBoxMsg )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMSComboBox::CMSComboBox()
{
	m_nStyle = 0;
	m_nState = 0;
	m_pListBox = NULL;
}

CMSComboBox::~CMSComboBox()
{
	if( m_pListBox )
		CloseListBox();

	// Need to be called to cleanup the item resoures 
	// before virtual table pointer get to base class CODComboBox
	OnDestroyCtrl();
}

void CMSComboBox::OnKillFocus( CWnd* pNewWnd )
{
	CODComboBox::OnKillFocus( pNewWnd );
}

void CMSComboBox::LBSelVisible( BOOL bVisible )
{
	if( bVisible )
		_Set_LBSelVisible_s();
	else
		_Reset_LBSelVisible_s();
}

void CMSComboBox::ShowCurSelEdit( BOOL bShow /*= TRUE*/ )
{
	if( bShow )
		_Set_ShowCurSelEdit_s();
	else
		_Reset_ShowCurSelEdit_s();
}

void CMSComboBox::OnPaint()
{
	CPaintDC dc( this );
	CustomPaint( dc );
	if( -1 != GetCurSel() )
		return;
	
	CFont* pFnt = GetFont();
	CFont* pOldFnt = dc.SelectObject( pFnt );
	
	CRect rct;
	GetClientRect( rct );
	rct.DeflateRect( 2, 2 );
	rct.right -= rct.Height();

	DRAWITEMSTRUCT sDrawItem;
	sDrawItem.CtlType = ODT_COMBOBOX;
	sDrawItem.hDC = dc.m_hDC;
	sDrawItem.hwndItem = m_hWnd;
	sDrawItem.itemState = 0;
	if( this == GetFocus() )
		sDrawItem.itemState = ODS_SELECTED;

	//rct.OffsetRect( 0, -1 );
	sDrawItem.itemID = -1;
	sDrawItem.rcItem = rct;
	DrawItem( &sDrawItem );
	DrawDropDownBtn( &dc );

	dc.SelectObject( pOldFnt );
}

void CMSComboBox::DrawDropDownBtn( CDC* pDC )
{
	CClientDC dc( this );
	HDC hDC = dc.m_hDC;
	CRect rct;
	GetDropDownBtnRect( rct );
	INT nPushed = 0;
	if( _Is_DDBtnDown() )
	{
		nPushed = DFCS_PUSHED;
		rct.OffsetRect( 1, 1 );
	}
	DrawFrameControl( hDC, rct, DFC_BUTTON, DFCS_BUTTONPUSH | nPushed );

	INT nCs = 3;
	CPoint point = rct.CenterPoint();
	rct.SetRect( point, point );
	rct.InflateRect( nCs, nCs - 1 );
	
	BeginPath( hDC );
	MoveToEx( hDC, rct.left, rct.top, NULL );
	LineTo( hDC, rct.right + 1, rct.top );
	LineTo( hDC, rct.CenterPoint().x, rct.bottom );
	LineTo( hDC, rct.left, rct.top );
	EndPath( hDC );

	HBRUSH hOldBrush = (HBRUSH)SelectObject( hDC, GetSysColorBrush( COLOR_MENUTEXT ) );
	FillPath( hDC );
	SelectObject( hDC, hOldBrush );
}

void CMSComboBox::DrawItem( LPDRAWITEMSTRUCT lpDrawItem )
{
	ASSERT( ODT_COMBOBOX == lpDrawItem->CtlType );
	CODComboBox::SItem* psItem;
	CString cszText;
	if( -1 == lpDrawItem->itemID )
	{
		INT nSelCnt = GetSelCount();
		if( 0 == nSelCnt )
			cszText = _T("[None]");
		else
		{
			PINT pnSel = GetSelIndex();
			if( _Is_ShowCurSelEdit_s() )
			{
				psItem = GetItem( pnSel[0] );
				cszText = psItem->cszText;

				for( INT i = 1; i < nSelCnt; i++ )
				{
					psItem = GetItem( pnSel[i] );;
					cszText = cszText + _T(", ") + psItem->cszText;
				}
			}
			else
			{
				psItem = GetItem( pnSel[nSelCnt - 1] );
				cszText = psItem->cszText;
			}
		}
	}
	else
	{
		psItem = (CODComboBox::SItem*)lpDrawItem->itemData;
		cszText = psItem->cszText;
	}

	CDC dc;
	dc.Attach( lpDrawItem->hDC );
	
	// Save these values to restore them when done drawing.
	COLORREF crOldTextColor = dc.GetTextColor();
	COLORREF crOldBkColor = dc.GetBkColor();
	
	if( CODComboBox::m_nStyle & CODComboBox::BS_NONE )
		InflateRect( &lpDrawItem->rcItem, 2, 2 );

	// If this item is selected, set the background color 
	// and the text color to appropriate values. Erase
	// the rectangle by filling it with the background color.
	if( lpDrawItem->itemState & ODS_SELECTED )
	{
		dc.SetTextColor( ::GetSysColor(COLOR_HIGHLIGHTTEXT) );
		dc.SetBkColor( ::GetSysColor(COLOR_HIGHLIGHT) );
		dc.FillSolidRect( &lpDrawItem->rcItem, ::GetSysColor(COLOR_HIGHLIGHT) );
	}
	else
		dc.FillSolidRect( &lpDrawItem->rcItem, crOldBkColor );
	
	// Draw the text.
	INT nOldBkMode = dc.SetBkMode( TRANSPARENT );
	OffsetRect( &lpDrawItem->rcItem, m_ptTextOffset.x, m_ptTextOffset.y );
	DrawItemText( lpDrawItem->itemID, (TCHAR*)(LPCTSTR)cszText, lpDrawItem->rcItem, &dc );
	
	// Reset the background and text color to the original values.
	dc.SetTextColor( crOldTextColor );
	dc.SetBkColor( crOldBkColor );
	dc.SetBkMode( nOldBkMode );
	
	dc.Detach();
}

void CMSComboBox::DrawItemText( INT nIndex, TCHAR* ptszText, CRect rct, CDC* pDC )
{
	pDC->DrawText( ptszText, lstrlen(ptszText), rct, DT_SINGLELINE | DT_VCENTER | DT_EDITCONTROL );
}

CMSComboBox::SItem* CMSComboBox::GetMSItem( INT nIndex )
{
	DWORD dwItemData = GetItemData( nIndex, ITEMDATA_ID );
	if( CB_ERR == dwItemData )
	{
		ASSERT( FALSE );
		return NULL;
	}

	CMSComboBox::SItem* psItem = (CMSComboBox::SItem*)dwItemData;
	return psItem;
}

INT CMSComboBox::InsertItem( INT nIndex, LPCTSTR lpszString )
{
	INT nResult = CODComboBox::InsertItem( nIndex, lpszString );
	if( nResult < 0 )
		return nResult;

	CODComboBox::SItem* psItem = GetItem( nIndex );
	CMSComboBox::SItem* psMSItem = new CMSComboBox::SItem;
	ASSERT( psMSItem );

	psMSItem->nSel = 0;
	psMSItem->dwItemData = psItem->dwItemData;
	SetItemData( nIndex, ITEMDATA_ID, (DWORD)psMSItem );

	return nIndex;
}

void CMSComboBox::DeleteItem( LPDELETEITEMSTRUCT lpDeleteItem )
{
	ASSERT( ODT_COMBOBOX == lpDeleteItem->CtlType );
	CMSComboBox::SItem* psMSItem = GetMSItem( lpDeleteItem->itemID );
	if( psMSItem )
	{	
		SetItemData( lpDeleteItem->itemID, ITEMDATA_ID, NULL );
		delete psMSItem;
	}

	CODComboBox::DeleteItem( lpDeleteItem );
}

class CMSListBoxSite : public CWnd
{
	//{{AFX_MSG(CMSListBox)
	afx_msg LRESULT OnFloatStatusMsg( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMSListBoxSite, CWnd)
	//{{AFX_MSG_MAP(CMSListBoxSite)
	ON_MESSAGE( WM_FLOATSTATUS, OnFloatStatusMsg )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// To keep Main frame caption bar active state, when this gets active. 
// Otherwise Main frame caption bar will become not focus state.
LRESULT CMSListBoxSite::OnFloatStatusMsg( WPARAM wParam, LPARAM lParam )
{
	return 1L;
}

BOOL CMSComboBox::ShowListBox()
{
	CWnd* pMainWnd = AfxGetMainWnd();
	CMSListBoxSite* pCtrlWnd = new CMSListBoxSite;
	ASSERT( pCtrlWnd );
	LPCTSTR lptClass = AfxRegisterWndClass( 0 );
	ASSERT( lptClass );
	VERIFY( pCtrlWnd->CreateEx( 0, lptClass, NULL, WS_POPUP, CRect(0,0,0,0), pMainWnd, 0 ) );
	ASSERT( NULL == m_pListBox );

	VERIFY( m_pListBox = new CMSListBox );
	m_pListBox->m_pCmbCtrl = this;
	m_pListBox->Create( WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | 
						LBS_OWNERDRAWVARIABLE | LBS_EXTENDEDSEL | LBS_MULTIPLESEL | LBS_NOTIFY, 
		                CRect(0,0,0,0), pCtrlWnd, ID_LIST_CTRL );
	m_pListBox->SetOwner( this );
		
	// Set List Height
	LOGFONT lg;
	CFont* pWndFont = GetFont();
	pWndFont->GetLogFont( &lg );
	m_pListBox->SetFont( pWndFont );

	CRect rctDrop;
	GetDroppedControlRect( rctDrop );

	HDC hDC = ::GetDC( m_hWnd );
	HFONT hOldFont = (HFONT)SelectObject( hDC, pWndFont->m_hObject );
	TEXTMETRIC tm;
	GetTextMetrics( hDC, &tm );
	INT nStrCnt = GetCount();
	INT nCy = (tm.tmHeight + 2) * nStrCnt + 2;
	SelectObject( hDC, hOldFont );
	::ReleaseDC( m_hWnd, hDC );

	if( nCy < rctDrop.Height() )
		rctDrop.bottom = rctDrop.top + nCy;

	CRect rct;
	GetWindowRect( rct );
	rctDrop.OffsetRect( 0, rct.Height() );
	rct = rctDrop;
	pCtrlWnd->MoveWindow( rct );

	rct.OffsetRect( -rct.TopLeft() );
	m_pListBox->MoveWindow( rct );
	pCtrlWnd->ShowWindow( SW_SHOW );

	INT nCount = m_arnSel.GetSize();
	if( nCount )
	{
		m_pListBox->m_nPrevSelCnt = nCount;
		VERIFY( m_pListBox->m_pnPrevSel = new INT[nCount] );
		memcpy( m_pListBox->m_pnPrevSel, m_arnSel.GetData(), nCount * sizeof(INT) );
	}

	nCount = GetCount();
	INT i;
	for( i = 0; i < nCount; i++ )
	{
		CString cszText;
		GetLBText( i, cszText );
		m_pListBox->AddString( cszText );
	}

	if( _Is_LBSelVisible_s() )
	{
		nCount = m_arnSel.GetSize();
		if( 1 == nCount )
			return TRUE;

		PUINT pnSel = m_arnSel.GetData();
		for( i = 0; i < nCount; i++ )
			m_pListBox->SetSel( pnSel[i] );

		m_pListBox->m_bFirstSelected = TRUE;
	}

	return TRUE;
}

void CMSComboBox::ActivateListBox()
{
	m_nState &= ~_CS_DD_BTN_DOWN;
	DrawDropDownBtn( NULL );
	ReleaseCapture();
	m_pListBox->SetFocus();
}

LRESULT CMSComboBox::OnCloseListBoxMsg( WPARAM wParam, LPARAM lParam )
{
	CloseListBox( wParam );
	return 1L;
}

void CMSComboBox::CloseListBox( BOOL bCancel /*= FALSE*/ )
{
	if( NULL == m_pListBox )
		return;

	NMHDR nm;
	nm.code = CMSComboBox::NM_UPADTESEL;
	nm.hwndFrom = m_hWnd;
	nm.idFrom = GetDlgCtrlID();

	if( bCancel )
	{
		if( m_pListBox->m_nPrevSelCnt )
		{
			SetCurSel( m_pListBox->m_pnPrevSel[0] );
			for( INT i = 1; i <  m_pListBox->m_nPrevSelCnt; i++ )
				SetSel( m_pListBox->m_pnPrevSel[i] );
		}
		else
			SetCurSel( -1 );

		nm.code = CMSComboBox::NM_CANCELSEL;
		GetParent()->SendMessage( WM_NOTIFY, nm.idFrom, (LPARAM)&nm );
	}
	else
		GetParent()->SendMessage( WM_NOTIFY, nm.idFrom, (LPARAM)&nm );

	delete m_pListBox->GetParent();
	delete m_pListBox;
	m_pListBox = NULL;
}

void CMSComboBox::ResetContent()
{
	if( m_hWnd && IsWindow( m_hWnd ) )
		CODComboBox::ResetContent();

	if( m_arnSel.GetSize() )
	{
		SetModified();
		m_arnSel.RemoveAll();
	}
}

INT CMSComboBox::SetCurSel( INT nIndex )
{
	if( 1 == m_arnSel.GetSize() && nIndex == (INT)m_arnSel.GetAt( 0 ) )
		return nIndex;

	// First remove all previous multiple selections
	CMSComboBox::SItem* psMSItem;
	INT nCount = GetCount();
	for( INT i = 0; i < nCount; i++ )
	{
		psMSItem = GetMSItem( i );
		if( NULL == psMSItem )
		{
			ASSERT( FALSE );
			return CB_ERR;
		}

		psMSItem->nSel = 0;
	}

	// Remove selection, if invalid index
	if( nIndex < 0 || nIndex >= nCount )
	{
		if( m_arnSel.GetSize() )
			m_arnSel.RemoveAll();

		LockWindowUpdate();
		CODComboBox::SetCurSel( -1 );
		UnlockWindowUpdate();

		SetModified();
		InvalidateRect( NULL, FALSE );
		return CB_ERR;
	}

	psMSItem = GetMSItem( nIndex );
	if( NULL == psMSItem )
		return CB_ERR;

	// Is previous was single selection
	if( 1 == m_arnSel.GetSize() )
	{
		// This selection is not same as previous
		if( nIndex != (INT)m_arnSel.GetAt( 0 ) )
			m_arnSel.SetAt( 0, nIndex );
	}
	else
	{	// No item selected
		if( m_arnSel.GetSize() )
			m_arnSel.RemoveAll();

		m_arnSel.Add( nIndex );
	}

	psMSItem->nSel = 1;
	LockWindowUpdate();
	CODComboBox::SetCurSel( nIndex );
	UnlockWindowUpdate();

	SetModified();
	InvalidateRect( NULL, FALSE );
	return nIndex;
}

INT CMSComboBox::GetSel( INT nIndex )
{
	CMSComboBox::SItem* psMSItem = GetMSItem( nIndex );
	if( psMSItem )
		return (0 != psMSItem->nSel);

	return CB_ERR;
}

INT CMSComboBox::SetSel( INT nIndex, BOOL bSelect /*= TRUE*/ )
{
	CMSComboBox::SItem* psMSItem = GetMSItem( nIndex );
	if( NULL == psMSItem )
		return CB_ERR;

	if( (0 != psMSItem->nSel && 0 != bSelect) || (0 == psMSItem->nSel && 0 == bSelect) )
		return nIndex;

	// Find selection array element index 
	INT nSelCnt = m_arnSel.GetSize();
	INT nFindIndex = -1;
	PINT pnSel = (PINT)m_arnSel.GetData();
	for( INT i = 0; i < nSelCnt; i++ )
		if( pnSel[i] == nIndex )
		{
			nFindIndex = i;
			break;
		}

	if( bSelect && -1 == nFindIndex )
		m_arnSel.Add( nIndex );
	else if( FALSE == bSelect && -1 != nFindIndex )
		m_arnSel.RemoveAt( nFindIndex );

	psMSItem->nSel = bSelect;
	SetModified();
	InvalidateRect( NULL, FALSE );
	return nIndex;
}

UINT CMSComboBox::OnGetDlgCode()
{
	UINT unReturn = CODComboBox::OnGetDlgCode();
	unReturn |= DLGC_WANTARROWS | DLGC_WANTCHARS;
	return unReturn;
}

void CMSComboBox::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	switch( nChar )
	{
	case VK_F4:
		if( IsKeyNoShift() )
		{
			ShowListBox();
			ReleaseCapture();
			m_pListBox->SetFocus();
			return;
		}
		break;
	}

	CODComboBox::OnKeyDown( nChar, nRepCnt, nFlags );
}

void CMSComboBox::OnMouseMove( UINT nFlags, CPoint point )
{
	if( _Is_DDBtnDown() )
	{
		CRect rct;
		GetDropDownBtnRect( rct );
		if( FALSE == rct.PtInRect( point ) )
			ActivateListBox();
	}
}

void CMSComboBox::OnLButtonDown( UINT nFlags, CPoint point )
{
	if( m_pListBox )
		return;

	CRect rct;
	GetDropDownBtnRect( rct );
	if( rct.PtInRect( point ) && ShowListBox() )
	{
		m_nState |= _CS_DD_BTN_DOWN;
		DrawDropDownBtn( NULL );
		SetCapture();
	}
}

void CMSComboBox::OnLButtonUp( UINT nFlags, CPoint point )
{
	if( _Is_DDBtnDown() )
		ActivateListBox();
	else
		if( this != GetFocus() )
			SetFocus();
}

void CMSComboBox::OnLButtonDblClk( UINT nFlags, CPoint point )
{}