#include "stdafx.h"
#include "PropObjectSelComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Todo List
// 1: Fix bug: On clicking DropDown second the DropDown list is popuping correctly, 
//    It is allowing CComboBox to its DropDrop List
//	Fixed
// 2. Implementation a callback method to know whether the clicked item on the Tree Ctrl
//    can be selected or not
//	Implemented as Notification NM_SELCHANGE
// 3. Paint Problem of Highlight rectangle
//    1. Click Drop down button, don't leave button press it shows small highlight rectangle
//    2. With out leave button press, Move Mouse out if Drop down button, then highlight rectangle becomes bigger
//	Fixed
//	  1. OnPaiint DeflateRect( 2, 2 ) changed to DeflateRect( 3, 3 );
/////////////////////////////////////////////////////////////////////////////////////////
class CMSListCtrlSite : public CWnd
{
	//{{AFX_MSG(CMSListCtrlSite)
	afx_msg LRESULT OnFloatStatusMsg( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMSListCtrlSite, CWnd)
	//{{AFX_MSG_MAP(CMSListCtrlSite)
	ON_MESSAGE( WM_FLOATSTATUS, OnFloatStatusMsg )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/// To keep Main frame caption bar active state, when this gets active. 
/// Otherwise Main frame caption bar will become not focus state.
LRESULT CMSListCtrlSite::OnFloatStatusMsg( WPARAM wParam, LPARAM lParam ) {
	return 1L; }

/////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CPropObjectSelComboBox, CODComboBox)
	//{{AFX_MSG_MAP(CPropObjListCmb)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_NOTIFY_REFLECT_EX( CPropObjectSelComboBox::NM_SELCHANGE, OnComboSelChange )
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPropObjectSelComboBox::CPropObjectSelComboBox()
{
	m_pListCtrlSite = NULL;
	m_nChildItemIndex = -1;

	m_bDropBtnDown = FALSE;
	m_bDropBtnPressed = FALSE;

	m_bMultipleSelection = FALSE;
	m_bMultipleSelection = TRUE;
}

CPropObjectSelComboBox::~CPropObjectSelComboBox()
{
	if( m_pListCtrlSite )
		delete m_pListCtrlSite;
}

CMSListCtrlSite* CPropObjectSelComboBox::CreateCtrlSite()
{
	CMSListCtrlSite* pCtrlSite = new CMSListCtrlSite;
	if( NULL == pCtrlSite )
	{
		ASSERT( pCtrlSite );
		return NULL;
	}
	
	LPCTSTR lptClass = AfxRegisterWndClass( 0 );
	ASSERT( lptClass );
	
	CWnd* pMainWnd = AfxGetMainWnd();
	ASSERT( pMainWnd );
	if( FALSE == pCtrlSite->CreateEx( 0, lptClass, NULL, WS_POPUP, CRect(0,0,0,0), pMainWnd, 0 ) )
	{
		delete pCtrlSite;
		return NULL;
	}

	return pCtrlSite;
}

int CPropObjectSelComboBox::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( -1 == CODComboBox::OnCreate( lpCreateStruct ) )
		return -1;

	BOOL bSuccess = FALSE;
	do 
	{
		// Create Tree Ctrl site and Tree Ctrl
		CWnd* pMainWnd = AfxGetMainWnd();
		ASSERT( pMainWnd );

		if( NULL == m_pListCtrlSite )
			m_pListCtrlSite = new CMSListCtrlSite;

		if( NULL == m_pListCtrlSite )
			break;

		LPCTSTR lptClass = AfxRegisterWndClass( 0 );
		ASSERT( lptClass );

		if( FALSE == m_pListCtrlSite->CreateEx( 0, lptClass, NULL, WS_POPUP, CRect(0,0,0,0), this, 0 ) )
			break;

		m_ListCtrl.m_pComboBox = this;
		if( FALSE == m_ListCtrl.Create( WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS 
										| TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_FULLROWSELECT, 
										CRect(0,0,0,0), m_pListCtrlSite, 0 ) )
			break;

		bSuccess = TRUE;
	}while( 0 );

	// If failed, delete Tree Ctrl Site if created
	if( FALSE == bSuccess )
	{
		if( m_pListCtrlSite && m_pListCtrlSite->m_hWnd )
			m_pListCtrlSite->DestroyWindow();

		return -1;
	}

	return 0;
}

void CPropObjectSelComboBox::OnPaint()
{
	CPaintDC dc( this );
	CustomPaint( dc );

	CFont* pFont = GetFont();
	CFont* pOldFont = dc.SelectObject( pFont );
	
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

	TRACE( "Paint\n" );

	dc.FillSolidRect( rct, GetSysColor( COLOR_WINDOW ) );
	DrawItem( &sDrawItem );
	dc.SelectObject( pOldFont );

	DrawDropDownBtn( &dc );
}

void CPropObjectSelComboBox::DrawItemText( INT nIndex, PTCHAR ptszText, CRect rct, CDC* pDC )
{
	CFont* pOldFnt;
	CFont fnt;
	LOGFONT lf;
	CString cszText = ptszText;
	if( nIndex >= 0 )
	{
		for( INT i = 0; i < m_nChildItemIndex && i < nIndex; i++ )
			cszText = _T(" ") + cszText;
		
		if( nIndex < m_nChildItemIndex )
		{
			CFont* pFnt = GetFont();
			ASSERT( pFnt );
			
			GetObject( pFnt->m_hObject, sizeof(lf), &lf );
			lf.lfWeight = 800;
			
			fnt.CreateFontIndirect( &lf );
			pOldFnt = pDC->SelectObject( &fnt );
		}
	}
	
	pDC->DrawText( cszText, rct, DT_SINGLELINE | DT_VCENTER | DT_EDITCONTROL );
	
	if( fnt.m_hObject )
		pDC->SelectObject( pOldFnt );
}

void CPropObjectSelComboBox::DrawItem( LPDRAWITEMSTRUCT lpDrawItem )
{
	TRACE( "Draw Item\n" );
	HTREEITEM hItem = m_ListCtrl.GetFirstSelectedItem();
	if( NULL == hItem )
		return;

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
		//dc.SetBkColor( ::GetSysColor(COLOR_HIGHLIGHT) );
		dc.FillSolidRect( &lpDrawItem->rcItem, ::GetSysColor(COLOR_HIGHLIGHT) );

		CRect r = lpDrawItem->rcItem;
		TRACE( "Hilite(%d, %d, %d, %d)\n", r.left, r.top, r.right, r.bottom );
	}
	else
		dc.FillSolidRect( &lpDrawItem->rcItem, crOldBkColor );
	
	// Draw the text.
	INT nOldBkMode = dc.SetBkMode( TRANSPARENT );
	OffsetRect( &lpDrawItem->rcItem, m_ptTextOffset.x, m_ptTextOffset.y );

	CString cszText, cszItemText = m_ListCtrl.GetItemText( hItem );
	do 
	{
		cszItemText = m_ListCtrl.GetItemText( hItem );
		if( FALSE == cszText.IsEmpty() )
			cszText += (", ") ;

		cszText += cszItemText;
		hItem = m_ListCtrl.GetNextSelectedItem( hItem );
	}while( hItem );

	dc.DrawText( cszText, &lpDrawItem->rcItem, DT_SINGLELINE | DT_VCENTER | DT_EDITCONTROL );

	// Reset the background and text color to the original values.
	dc.SetTextColor( crOldTextColor );
	//dc.SetBkColor( crOldBkColor );
	dc.SetBkMode( nOldBkMode );
	
	dc.Detach();
}

void CPropObjectSelComboBox::DrawDropDownBtn( CDC* pDC )
{
	CClientDC dc( this );
	HDC hDC = dc.m_hDC;
	CRect rct;
	GetDropDownBtnRect( rct );
	INT nPushed = 0;
	if( m_bDropBtnDown )
	{
		nPushed = DFCS_PUSHED;
		//rct.OffsetRect( 1, 1 );
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

BOOL CPropObjectSelComboBox::PreTranslateMessage( MSG* pMSG )
{
	if( pMSG->message >= WM_MOUSEFIRST && pMSG->message <= WM_MOUSELAST )
	{
		switch( pMSG->message )
		{
		case WM_LBUTTONUP:
			if( m_bDropBtnPressed )
			{
				if( GetCapture() == this )
					ReleaseCapture();

				ActivateListBox();

				m_bDropBtnPressed = FALSE;
				m_bDropBtnDown = FALSE;
				return TRUE;
			}

			break;
		}
	}

	return CODComboBox::PreTranslateMessage( pMSG );
}

void CPropObjectSelComboBox::OnMouseMove( UINT nFlags, CPoint point )
{
	CRect rect;
	GetDropDownBtnRect( rect );
	if( m_bDropBtnPressed )
	{
		BOOL bDropBtnDown = rect.PtInRect( point );
		if( m_bDropBtnDown != bDropBtnDown )
		{
			m_bDropBtnDown = bDropBtnDown;
			InvalidateRect( rect, FALSE );
		}

		return;
	}
	
	CODComboBox::OnMouseMove( nFlags, point );
}

void CPropObjectSelComboBox::OnLButtonDown( UINT nFlags, CPoint point )
{
	CRect rect;
	GetDropDownBtnRect( rect );

	DWORD dwStyle = GetStyle();
	if( CBS_DROPDOWNLIST & dwStyle )
		GetClientRect( rect );
				
	if( m_ListCtrl.m_hWnd && rect.PtInRect( point ) && ShowListBox() )
	{
		m_bDropBtnPressed = TRUE;
		m_bDropBtnDown = TRUE;
		DrawDropDownBtn( NULL );
		SetFocus();
		SetCapture();
		return;
	}

	CODComboBox::OnLButtonDown( nFlags, point );
}

// This is created to try logic of LButtonUP in PreTranslateMessage. 
// Reason is unknown why this OnLButtonUp can not replace the logic in PreTranslateMessage
void CPropObjectSelComboBox::OnLButtonUp( UINT nFlags, CPoint point )
{
	if( m_bDropBtnPressed )
	{
		if( GetCapture() == this )
			ReleaseCapture();
		
		ActivateListBox();
		
		m_bDropBtnPressed = FALSE;
		m_bDropBtnDown = FALSE;
		return;
	}

	CODComboBox::OnLButtonUp( nFlags, point );
}

void CPropObjectSelComboBox::ActivateListBox()
{
	m_bDropBtnDown = FALSE;
	DrawDropDownBtn( NULL );
	m_ListCtrl.SetFocus();
	m_ListCtrl.SetCapture();
}

BOOL CPropObjectSelComboBox::ShowListBox()
{	
	if( NULL == m_ListCtrl.m_hWnd )
		return FALSE;

	// Set List Height
	LOGFONT lg;
	CFont* pWndFont = GetFont();
	pWndFont->GetLogFont( &lg );
	m_ListCtrl.SetFont( pWndFont );
	
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

	nCy = 300;
	if( nCy < rctDrop.Height() )
		rctDrop.bottom = rctDrop.top + nCy;
	
	CRect rct;
	GetWindowRect( rct );
	rctDrop.OffsetRect( 0, rct.Height() );
	rct = rctDrop;
	m_pListCtrlSite->MoveWindow( rct );
	
	rct.OffsetRect( -rct.TopLeft() );
	m_ListCtrl.MoveWindow( rct );
	m_ListCtrl.ShowWindow( SW_SHOW );
	m_pListCtrlSite->ShowWindow( SW_SHOW );
	return TRUE;
}

void CPropObjectSelComboBox::CloseListBox( BOOL bCancel /*= FALSE*/ )
{
	if( m_pListCtrlSite )
	{
		m_pListCtrlSite->ShowWindow( SW_HIDE );
		InvalidateRect( NULL, FALSE );
	}
}

BOOL CPropObjectSelComboBox::OnComboSelChange( NMHDR* pNMHDR, LRESULT* plResult )
{
	NMSELCHANGE* pNM = (NMSELCHANGE*)pNMHDR;
	if( pNM->bSelect && FALSE == pNM->bMultipleSel )
		m_ListCtrl.Close();

	return FALSE;
}

HTREEITEM CPropObjectSelComboBox::GetCurSel() const 
{
	if( NULL == m_ListCtrl.m_hWnd )
		return NULL;

	return m_ListCtrl.GetSelectedItem();
}
 
BOOL CPropObjectSelComboBox::SetCurSel( HTREEITEM hItem )
{
	if( NULL == m_ListCtrl.m_hWnd )
		return NULL;

	BOOL bItemChanged = FALSE;
	HTREEITEM hParamItem = hItem;
	HTREEITEM hPrevItem = m_ListCtrl.GetFirstSelectedItem();
	while( hPrevItem )
	{
		if( hPrevItem == hParamItem )
			hItem = NULL;	// Already selected, leave as it is.
		else
		{
			m_ListCtrl.SetItemState( hPrevItem, 0, TVIS_SELECTED );
			bItemChanged = TRUE;
		}

		hPrevItem = m_ListCtrl.GetNextSelectedItem( hPrevItem );
	}

	if( hItem && m_ListCtrl.SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED ) )
		bItemChanged = TRUE;

	if( bItemChanged )
	{
		InvalidateRect( NULL, FALSE );
		return TRUE;
	}

	return FALSE;
}

BOOL CPropObjectSelComboBox::GetSel( HTREEITEM hItem ) const
{
	if( NULL == m_ListCtrl.m_hWnd )
		return FALSE;

	if( m_ListCtrl.GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
		return TRUE;

	return FALSE;
}

BOOL CPropObjectSelComboBox::SetSel( HTREEITEM hItem, BOOL bSelect /*= TRUE*/ )
{
	if( NULL == m_ListCtrl.m_hWnd )
		return FALSE;

	BOOL bItemChanged = FALSE;
	if( FALSE == m_bMultipleSelection )
	{
		if( bSelect )
			return SetCurSel( hItem );
		else
		{
			m_ListCtrl.DeselectAll();
			hItem = NULL;
			bItemChanged = TRUE;
		}
	}

	if( hItem && m_ListCtrl.SetItemState( hItem, bSelect ?TVIS_SELECTED : 0, TVIS_SELECTED ) )
		bItemChanged = TRUE;

	if( bItemChanged )
	{
		InvalidateRect( NULL, FALSE );
		return TRUE;
	}

	return FALSE;
}

void CPropObjectSelComboBox::ResetContent() 
{
	if( NULL == m_ListCtrl.m_hWnd )
		return;

	if( 0 == m_ListCtrl.GetCount() )
		return;

	m_ListCtrl.DeleteAllItems(); 
	InvalidateRect( NULL, FALSE );
}
