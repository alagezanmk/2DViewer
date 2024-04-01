#include "stdafx.h"
#include "ODComboBox.h"
#include "ODComboBoxPriv.h"
#include <cu\msg.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////////////////
CODComboBox::SItem::SItem()
{
	dwItemData = 0;
}

CODComboBox::SItem::~SItem()
{}

/////////////////////////////////////////////////////////////////////////////////////////
#define _Is_WindowsBorder() (0 != (m_nStyle & CODComboBox::BS_WINDOWS))
#define _Is_UserBorder()	(0 != (m_nStyle & CODComboBox::BS_USER))
#define _Is_NoneBorder()	(0 != (m_nStyle & CODComboBox::BS_NONE))

BEGIN_MESSAGE_MAP(CODComboBox, CComboBox)
	//{{AFX_MSG_MAP(CODComboBox)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CODComboBox::CODComboBox()
{
	m_nStyle = 0;
	m_nCtrlHeight = 15;
	m_ptTextOffset.x = 0;
	m_ptTextOffset.y = 0;
}

CODComboBox::~CODComboBox()
{
	OnDestroyCtrl();
}

void CODComboBox::OnDestroy()
{
	OnDestroyCtrl();
	CComboBox::OnDestroy();
}

void CODComboBox::OnDestroyCtrl()
{
	if( m_hWnd )
		ResetContent();
}

void CODComboBox::OnPaint() 
{
	Default();
	CClientDC dc( this );
	CustomPaint( dc );
}

void CODComboBox::CustomPaint( CDC& rDC )
{
	if( _Is_NoneBorder() )
		return;

	NMBorderColor sColor;

	COLORREF crf3DHilite = GetSysColor( COLOR_3DLIGHT );
	COLORREF crf3DShadow = GetSysColor( COLOR_BTNSHADOW );
	COLORREF crfDkShadow = GetSysColor( COLOR_3DDKSHADOW );
	COLORREF crfDkHilite = GetSysColor( COLOR_BTNHIGHLIGHT );

	sColor.crfOTop = crf3DShadow;
	sColor.crfOLeft = crf3DShadow;
	sColor.crfOBottom = crfDkHilite;
	sColor.crfORight = crfDkHilite;

	sColor.crfiTop = crfDkShadow;
	sColor.crfiLeft = crfDkShadow;
	sColor.crfiBottom = crf3DHilite;
	sColor.crfiRight = crf3DHilite;
	if( _Is_WindowsBorder() )
	{
		COLORREF crfWindow = GetSysColor( COLOR_WINDOW );
		sColor.crfOTop = crf3DHilite;
		sColor.crfOLeft = crf3DHilite;
		sColor.crfOBottom = crf3DHilite;
		sColor.crfORight = crf3DHilite;

		sColor.crfiTop = crfWindow;
		sColor.crfiLeft = crfWindow;
		sColor.crfiBottom = crfWindow;
		sColor.crfiRight = crfWindow;
	}
	else if( _Is_UserBorder() )
	{
		INT nResult;
		nResult = SendNotify( this, NMODCB_GET_BORDER_COLOR, &sColor );
		if( 1 == nResult )
			return;	// Handle by parent
	}

	INT x1, y1, x2, y2;
	CRect rect;
	CPen pen, *pOldPen;

	GetClientRect( &rect );
	x1 = rect.left;
	y1 = rect.top;
	x2 = rect.right - 1;
	y2 = rect.bottom - 1;

	VERIFY( pen.CreatePen( PS_SOLID, 1, sColor.crfOLeft ) );
	pOldPen = rDC.SelectObject( &pen );
	rDC.MoveTo( x1, y2 - 1 );
	rDC.LineTo( x1, y1 );
	rDC.SelectObject( pOldPen );
	pen.DeleteObject();
	
	VERIFY( pen.CreatePen( PS_SOLID, 1, sColor.crfOTop ) );
	pOldPen = rDC.SelectObject( &pen );
	rDC.LineTo( x2, y1 );
	rDC.SelectObject( pOldPen );
	pen.DeleteObject();

	VERIFY( pen.CreatePen( PS_SOLID, 1, sColor.crfORight ) );
	pOldPen = rDC.SelectObject( &pen );
	rDC.LineTo( x2, y2 );
	rDC.SelectObject( pOldPen );
	pen.DeleteObject();

	VERIFY( pen.CreatePen( PS_SOLID, 1, sColor.crfOBottom ) );
	pOldPen = rDC.SelectObject( &pen );
	rDC.LineTo( x1 - 1, y2 );
	rDC.SelectObject( pOldPen );
	pen.DeleteObject();

	x1++;
	y1++;
	x2--;
	y2--;

	VERIFY( pen.CreatePen( PS_SOLID, 1, sColor.crfiLeft ) );
	pOldPen = rDC.SelectObject( &pen );
	rDC.MoveTo( x1, y2 - 1 );
	rDC.LineTo( x1, y1 );
	rDC.SelectObject( pOldPen );
	pen.DeleteObject();

	VERIFY( pen.CreatePen( PS_SOLID, 1, sColor.crfiTop ) );
	pOldPen = rDC.SelectObject( &pen );
	rDC.LineTo( x2, y1 );
	rDC.SelectObject( pOldPen );
	pen.DeleteObject();

	VERIFY( pen.CreatePen( PS_SOLID, 1, sColor.crfiRight ) );
	pOldPen = rDC.SelectObject( &pen );
	rDC.LineTo( x2, y2 );
	rDC.SelectObject( pOldPen );
	pen.DeleteObject();

	VERIFY( pen.CreatePen( PS_SOLID, 1, sColor.crfiBottom ) );
	pOldPen = rDC.SelectObject( &pen );
	rDC.LineTo( x1 - 1, y2 );
	rDC.SelectObject( pOldPen );
	pen.DeleteObject();
}	

void CODComboBox::DrawItem( LPDRAWITEMSTRUCT lpDrawItem ) 
{
	ASSERT( ODT_COMBOBOX == lpDrawItem->CtlType );
	CString cszText;
	if( -1 != lpDrawItem->itemID )
	{
		SItem* psItem = (SItem*)lpDrawItem->itemData;
		cszText = psItem->cszText;
	}

	CDC dc;
	dc.Attach( lpDrawItem->hDC );
	
	// Save these values to restore them when done drawing.
	COLORREF crOldTextColor = dc.GetTextColor();
	COLORREF crOldBkColor = dc.GetBkColor();
	
	// If this item is selected, set the background color 
	// and the text color to appropriate values. Erase
	// the rectangle by filling it with the background color.
	if( (lpDrawItem->itemAction | ODA_SELECT) &&
		(lpDrawItem->itemState  & ODS_SELECTED) )
	{
		dc.SetTextColor( ::GetSysColor(COLOR_HIGHLIGHTTEXT) );
		dc.SetBkColor( ::GetSysColor(COLOR_HIGHLIGHT) );
		dc.FillSolidRect( &lpDrawItem->rcItem, ::GetSysColor(COLOR_HIGHLIGHT) );
	}
	else
		dc.FillSolidRect( &lpDrawItem->rcItem, crOldBkColor );
	
	// Draw the text.
	dc.TextOut( lpDrawItem->rcItem.left + m_ptTextOffset.x + 1,
				lpDrawItem->rcItem.top + m_ptTextOffset.y + 1,
				cszText );
	
	// Reset the background and text color to the original values.
	dc.SetTextColor( crOldTextColor );
	dc.SetBkColor( crOldBkColor );
	
	dc.Detach();
}

int CODComboBox::CompareItem( LPCOMPAREITEMSTRUCT lpCompareItem )
{
	ASSERT( ODT_COMBOBOX == lpCompareItem->CtlType );
	SItem* psItem = (SItem*)lpCompareItem->itemData1;
	LPCTSTR lpszText1 = (LPCTSTR)psItem->cszText;
	ASSERT( lpszText1 );

	psItem = (SItem*)lpCompareItem->itemData2;
	LPCTSTR lpszText2 = (LPCTSTR)psItem->cszText;
	ASSERT( lpszText2 );

   return lstrcmp( lpszText2, lpszText1 );
}

void CODComboBox::MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItem ) 
{
	lpMeasureItem->itemHeight = m_nCtrlHeight;
}

SItem* CODComboBox::GetItem( INT nIndex ) const
{
	DWORD dwItemdata = CComboBox::GetItemData( nIndex );
	if( CB_ERR == dwItemdata )
	{
		ASSERT( FALSE );
		return NULL;
	}

	SItem* psItem = (SItem*)dwItemdata;
	return psItem;
}

INT CODComboBox::InsertItem( INT nIndex, LPCTSTR lpszString )
{
	SItem* psItem;
#ifdef _DEBUG
	psItem = (SItem*)CComboBox::GetItemData( nIndex );
	ASSERT( NULL == psItem );
#endif 

	VERIFY( psItem = new SItem );
	psItem->cszText = lpszString;
	VERIFY( CB_ERR != CComboBox::SetItemData( nIndex, (DWORD)psItem ) );
	return nIndex;
}

void CODComboBox::DeleteItem( LPDELETEITEMSTRUCT lpDeleteItem )
{
	ASSERT( ODT_COMBOBOX == lpDeleteItem->CtlType );
	SItem* psItem = (SItem*)lpDeleteItem->itemData;
	ASSERT( psItem );
	if( psItem )
	{
		SetItemData( lpDeleteItem->itemID, NULL );
		delete psItem;
	}
}

DWORD CODComboBox::GetItemData( INT nIndex ) const
{
	SItem* psItem = (SItem*)CComboBox::GetItemData( nIndex );
	ASSERT( psItem );
	if( NULL == psItem )
		return 0;
	
	return psItem->dwItemData;
}

INT CODComboBox::SetItemData( INT nIndex, DWORD dwItemData )
{
	SItem* psItem = (SItem*)CComboBox::GetItemData( nIndex );
	ASSERT( psItem );
	if( NULL == psItem )
		return CB_ERR;
	
	psItem->dwItemData = dwItemData;
	return nIndex;
}

DWORD CODComboBox::GetItemData( INT nIndex, INT nID ) const
{
	SItem* psItem = GetItem( nIndex );
	if( NULL == psItem )
	{
		ASSERT( psItem );
		return CB_ERR;
	}

	DWORD dwItemData = (DWORD)psItem->mapID_ItemData[(void*)nID];
	return dwItemData;
}

INT CODComboBox::SetItemData( INT nIndex, INT nID, DWORD dwItemData )
{
	SItem* psItem = GetItem( nIndex );
	if( NULL == psItem )
	{
		ASSERT( psItem );
		return CB_ERR;
	}

	psItem->mapID_ItemData.SetAt( (void*)nID, (void*)dwItemData );
	return nIndex;
}

INT CODComboBox::AddString( LPCTSTR lpszString )
{
	INT nIndex = CComboBox::AddString( lpszString );
	ASSERT( nIndex >= 0 );
	if( nIndex < 0 )	
		return nIndex;
	
	CComboBox::SetItemData( nIndex, NULL );
	InsertItem( nIndex, lpszString );
	return nIndex;
}

INT CODComboBox::InsertString( INT nIndex, LPCTSTR lpszString )
{
	INT nResult = CComboBox::InsertString( nIndex, lpszString );
	ASSERT( nResult >= 0 );
	if( nResult < 0 )
		return nResult;
	
	CComboBox::SetItemData( nIndex, NULL );
	InsertItem( nIndex, lpszString );
	return nIndex;
}

INT CODComboBox::GetLBText( INT nIndex, LPTSTR lpszText ) const
{
	SItem* psItem = GetItem( nIndex );
	if( lpszText )
		lstrcpy( lpszText, psItem->cszText );

	INT nLen = psItem->cszText.GetLength();
	return nLen;
}

void CODComboBox::GetLBText( INT nIndex, CString& rString ) const
{
	SItem* psItem = GetItem( nIndex );
	rString = psItem->cszText;
}

INT CODComboBox::GetLBTextLen( INT nIndex ) const
{
	SItem* psItem = GetItem( nIndex );
	return psItem->cszText.GetLength();
}

void CODComboBox::GetDropDownBtnRect( CRect& rrct )
{
	GetClientRect( rrct );
	if( 0 == (CODComboBox::m_nStyle & CODComboBox::BS_NONE) )
		rrct.DeflateRect( 2, 2 );
	
	rrct.left = rrct.right - rrct.Height() - 2;
}
