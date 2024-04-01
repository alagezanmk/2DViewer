#include "stdafx.h"
#include "PropCtrl.h"

#include <gl\gl.h>
#include <cu\MemDC.h>
#include <cu\Key.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const INT gc_nPlusx = -14;
const INT gc_nPlusCs = 11;
const INT gc_nLabelx = 17;
const INT gc_nDescCy = 50;
const INT g_cnMinCx	= 50;

#define _CS_NONE			0
#define _CS_TRACKING_DIV	1
#define _CS_INTERNAL_UPT	2

BEGIN_MESSAGE_MAP(CPropItemList, CScrollView)
	//{{AFX_MSG_MAP(CPropItemList)
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETCURSOR()

	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()

	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()

	ON_NOTIFY( NM_KILLFOCUS, ID_PROP_EDIT, OnPropEditUpdate )
	ON_NOTIFY( NM_RETURN, ID_PROP_EDIT, OnPropEditUpdate )
	ON_NOTIFY( NM_UPDATE, ID_PROP_EDIT, OnPropEditUpdate )
	ON_NOTIFY( NM_CANCEL, ID_PROP_EDIT, OnPropEditCancel )

	ON_BN_CLICKED( ID_PROP_BTN, OnPropBtnClicked )
	ON_EN_CHANGE( ID_PROP_EDIT, OnPropEditChange )

	ON_NOTIFY( CMSComboBox::NM_SELCHANGE, ID_PROP_COMBO, OnPropComboSelChange )
	ON_NOTIFY( CMSComboBox::NM_UPADTESEL, ID_PROP_COMBO, OnPropComboUpdateSel )
	ON_NOTIFY( CMSComboBox::NM_CANCELSEL, ID_PROP_COMBO, OnPropComboCancelSel )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPropItemList::CPropItemList( CPropCtrl& rPropCtrl ) 
	: m_rPropCtrl( rPropCtrl )
{
	m_szCell.cx = 2000;
	m_szCell.cy = 16;
	m_nItemDiv = 100;

	m_nHorzCnt = 1;
	m_nHorzVisibleCnt = 0;
	m_nLeftIndex = 0;
	m_nTopIndex = 0;

	m_nVertCnt = 0;
	m_nVertVisibleCnt = 0;
	m_nLeftIndexX = 0;
	m_nTopIndexY = 0;

	m_pPropDlg = NULL;

	m_bUserItemCtrl = FALSE;
	m_bStaticItemCtrl = FALSE;
	m_bAlphabeticTab = FALSE;
	m_nCtrlState = _CS_NONE;
}

CPropItemList::~CPropItemList()
{}

void CPropItemList::OnNcDestroy()
{
	DeleteCtrl();
	CWnd::OnNcDestroy();
}

void CPropItemList::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CPropItemList::OnSize( UINT nType, INT cx, INT cy )
{
	CScrollView::OnSize( nType, cx, cy );
	if( m_pPropDlg )
		ReposDlg();
	else
	{
		RecalcPropList();
		CalcItemInfo();
	}

	if( m_bUserItemCtrl )
	{
		CRect rct;
		GetClientRect( rct );
		rct.left += m_nItemDiv;
		GetItemRect( m_rPropCtrl.m_nSelItemIndex, rct );

		INT nCtrlFlag = m_rPropCtrl.m_pProp->GetCurItem()->psProp->nCtrlFlag;
		if( nCtrlFlag & OPCF_USER_FROM_LABEL )
		{
			rct.left = gc_nLabelx;
			m_rPropCtrl.m_pProp->SetWindowPos( NULL, rct.left, rct.top, rct.Width(), rct.Height(), SWP_NOZORDER );
		}
		else if( nCtrlFlag & OPCF_USER_FROM_LEFT )
		{
			rct.left = 0;
			m_rPropCtrl.m_pProp->SetWindowPos( NULL, rct.left, rct.top, rct.Width(), rct.Height(), SWP_NOZORDER );
		}
		else
			m_rPropCtrl.m_pProp->SetWindowPos( NULL, rct.left, rct.top, rct.Width(), rct.Height(), SWP_NOZORDER );
	}

	CRect rct;
	GetClientRect( rct );
	rct.left += m_nItemDiv;
	GetItemRect( m_rPropCtrl.m_nSelItemIndex, rct );

	if( CProp::m_pbtnProp )
	{
		CRect rctCtrl = rct;
		rctCtrl.left = rctCtrl.right - rctCtrl.Height();
		rct.right = rctCtrl.left;
		CProp::m_pbtnProp->MoveWindow( rctCtrl );
	}

	if( CProp::m_pedtProp )
		CProp::m_pedtProp->MoveWindow( rct );

	if( CProp::m_pcmbMSProp )
		CProp::m_pcmbMSProp->MoveWindow( rct );
}

BOOL CPropItemList::OnScrollBy( CSize sizeScroll, BOOL bDoScroll )
{
	BOOL bReturn = CScrollView::OnScrollBy( sizeScroll, bDoScroll );
	CalcItemInfo();
	return bReturn;
}

HBRUSH CPropItemList::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	if( m_rPropCtrl.m_pProp && m_rPropCtrl.m_pProp->GetCurItem() && 
		CProp::m_pedtProp == pWnd && 
		(OPSF_DISABLE & m_rPropCtrl.m_pProp->GetCurItem()->psProp->nFlag) )
	{
		pDC->SetTextColor( GetSysColor( COLOR_GRAYTEXT ) ); 
		return GetSysColorBrush( COLOR_WINDOW );
	}
	return CScrollView::OnCtlColor( pDC, pWnd, nCtlColor );
}

void CPropItemList::OnSetFocus( CWnd* pOldWnd )
{
	InvalidateItem();
	CScrollView::OnSetFocus( pOldWnd );
}

void CPropItemList::OnKillFocus( CWnd* pNewWnd )
{
	InvalidateItem();
	CScrollView::OnKillFocus( pNewWnd );
}

BOOL CPropItemList::OnEraseBkgnd( CDC* pDC ) {
	return TRUE; }

void CPropItemList::OnDraw( CDC* pDC )
{
	if( m_pPropDlg )
		return;

	CRect  rct;
	CMemDC MemDC;

	GetClientRect( rct );
	INT nClientCx = rct.Width();
	INT nClientCy = rct.Height();

	if( FALSE == MemDC.Create( pDC, nClientCx, nClientCy ) )
	{
		TRACE( _T("PropList: Mem DC create failed\n") );
		return;
	}

	//?
	CalcItemInfo();
	HBRUSH hBrush = GetSysColorBrush( COLOR_WINDOW );
	FillRect( MemDC.m_hDC, rct, hBrush );

	INT nScrollX = GetScrollPos( SB_HORZ );
	INT nScrollY = GetScrollPos( SB_VERT );
	MemDC.SetViewportOrg( -nScrollX, -nScrollY );

	INT nClientRight = nScrollX + nClientCx;

	INT x = m_nLeftIndexX + gc_nLabelx;
	INT y = m_nTopIndexY;

	COLORREF crfWindowText = GetSysColor( COLOR_WINDOWTEXT );
	COLORREF crfGrayText = GetSysColor( COLOR_GRAYTEXT );
	COLORREF crfHiliteText = GetSysColor( COLOR_HIGHLIGHTTEXT );
	COLORREF crf = GetSysColor( COLOR_BTNFACE );
	GetCrfBtnShades( crf, NULL, &crf, 0, 3 );

	CPen *pOldPen;
	CPen pen( PS_SOLID, 1, crf );
	ASSERT( pen.m_hObject );
	pOldPen = MemDC.SelectObject( &pen );
	
	crf = GetSysColor( COLOR_HIGHLIGHT );
	GetCrfBtnShades( crf, NULL, &crf, 0, 70 );
	hBrush = CreateSolidBrush( crf );

	// Draw Horz. line
	MemDC.MoveTo( nScrollX, y );
	MemDC.LineTo( nClientRight, y );

	rct.left = nScrollX;
	rct.right = nClientRight;
	GetItemRect( m_nTopIndex, rct );

	CFont* pOldFnt;
	CFont Fnt, FntMultipleSym;

	Fnt.Attach( (HFONT)GetStockObject( DEFAULT_GUI_FONT ) );

	// Create Italic style font if multiple Prop(s) are selected
	if( m_rPropCtrl.m_msProp.m_arpProp.GetSize() > 1 )
	{
		LOGFONT lf;
		GetObject( Fnt.m_hObject, sizeof(lf), &lf );
		VERIFY( FntMultipleSym.CreateFontIndirect( &lf ) );
	}
		
	pOldFnt = MemDC.SelectObject( &Fnt );
	MemDC.SetBkMode( TRANSPARENT );

	CWnd* pFocus = GetFocus();
	BOOL bHiLite = this == pFocus || IsChild( pFocus );
	if( CProp::m_pcmbMSProp )
	{
		CWnd* pListBox = (CWnd*)CProp::m_pcmbMSProp->GetListBox();
		if( pListBox && (pFocus == pListBox || pFocus == pListBox->GetParent()) )
			bHiLite = TRUE;
	}

	BOOL bFold = FALSE;
	CString csz;
	if( m_rPropCtrl.m_pProp )
	{
		HRGN hRgn, hOldRgn = CreateRectRgn(0, 0, 0, 0);
		SPropItem** ppsItem = m_rPropCtrl.m_pProp->GetItemList();
		for( INT i = m_nTopIndex, nIndex = 0; nIndex < m_nVertVisibleCnt && i < m_nVertCnt; i++, nIndex++ )
		{
			BOOL bGroupItem = OPST_GROUP == ppsItem[i]->psProp->nType;
			BOOL bDisabledItem = 0 != (ppsItem[i]->psProp->nFlag & OPSF_DISABLE);
			INT nRgn = GetClipRgn( MemDC.m_hDC, hOldRgn );
			hRgn = CreateRectRgn( rct.left, rct.top, rct.right, rct.bottom );
			SelectClipRgn( MemDC.m_hDC, hRgn );

			if( bGroupItem )
			{
				FillRect( MemDC.m_hDC, rct, hBrush );
				if( bHiLite && m_rPropCtrl.m_nSelItemIndex == i )
				{
					rct.right = m_nItemDiv;
					FillRect( MemDC.m_hDC, rct, GetSysColorBrush( COLOR_HIGHLIGHT ) );
					rct.right = nClientRight;
				}

				HBRUSH hOldBrush, hBrush = GetSysColorBrush( COLOR_WINDOW );
				hOldBrush = (HBRUSH)SelectObject( MemDC.m_hDC, hBrush );

				CPen* pOldPen;
				CPen pen( PS_SOLID, 1, crfWindowText );
				ASSERT( pen.m_hObject );
				pOldPen = MemDC.SelectObject( &pen );

				CRect rctPlus;
				rctPlus.left = x + gc_nPlusx;
				rctPlus.top = y + (m_szCell.cy - gc_nPlusCs) / 2;
				rctPlus.right = rctPlus.left + gc_nPlusCs;
				rctPlus.bottom = rctPlus.top + gc_nPlusCs;
				MemDC.Rectangle( rctPlus );

				const INT cnMargin = 3;
				const INT cnHLen = (gc_nPlusCs - cnMargin * 2) / 2;
				rctPlus.DeflateRect( cnMargin, cnMargin );
				MemDC.MoveTo( rctPlus.left, rctPlus.top + cnHLen );
				MemDC.LineTo( rctPlus.right, rctPlus.top + cnHLen );

				if( ppsItem[i]->psProp->nFlag & OPSF_FOLD )
				{
					MemDC.MoveTo( rctPlus.left + cnHLen, rctPlus.top );
					MemDC.LineTo( rctPlus.left + cnHLen, rctPlus.bottom );
				}

				MemDC.SelectObject( pOldPen );
				SelectObject( MemDC.m_hDC, hOldBrush );
			}

			if( m_rPropCtrl.m_nSelItemIndex == i || bGroupItem )
			{
				if( bHiLite && FALSE == bGroupItem )
				{
					rct.right = m_nItemDiv;
					FillRect( MemDC.m_hDC, rct, GetSysColorBrush( COLOR_HIGHLIGHT ) );
					rct.right = nClientRight;
				}

				if( (bHiLite && FALSE == bGroupItem) || bGroupItem )
					MemDC.SetTextColor( crfHiliteText );
			}

			// Draw Item Label
			csz.Empty();
			m_rPropCtrl.m_msProp.GetLabel( ppsItem[i], csz );
			CString cszParent;

			// Append grp name with label of item if have duplicate item name
			if( m_bAlphabeticTab && ppsItem[i]->pParent )
			{
				cszParent.Empty();
				m_rPropCtrl.m_pProp->GetLabel( ppsItem[i]->pParent, cszParent );
				csz += _T(":") + cszParent;
			}

			rct.left = x;
			rct.right = m_nItemDiv - 4;
			MemDC.DrawText( csz, rct, DT_SINGLELINE | DT_END_ELLIPSIS );
			rct.left = 0;
			rct.right = nClientRight;

			if( m_rPropCtrl.m_nSelItemIndex == i || bGroupItem )
				MemDC.SetTextColor( crfWindowText );

			// Item Value
			BOOL bMultiple;
			csz.Empty();
			m_rPropCtrl.m_msProp.GetText( ppsItem[i], csz, &bMultiple );

			if( bMultiple )
				MemDC.SelectObject( FntMultipleSym );

			if( bDisabledItem )
				MemDC.SetTextColor( crfGrayText );

			rct.left = m_nItemDiv + 1;
			rct.right--;
			MemDC.DrawText( csz, rct, DT_SINGLELINE | DT_END_ELLIPSIS | DT_VCENTER );
			rct.left = 0;
			rct.right = nClientRight;

			if( bDisabledItem )
				MemDC.SetTextColor( crfWindowText );

			if( bMultiple )
				MemDC.SelectObject( &Fnt );

			// Draw Horz. line
			MemDC.MoveTo( nScrollX, rct.bottom - 1 );
			MemDC.LineTo( nClientRight, rct.bottom - 1 );

			// Offset the coords
			GetItemRect( i + 1, rct );
			y = rct.top;

			DeleteObject( hRgn );
			SelectClipRgn( MemDC.m_hDC, 1 == nRgn ?hOldRgn :NULL );
		}

		DeleteObject( hOldRgn );
	}

	MemDC.SelectObject( pOldFnt );
	Fnt.Detach();

	DeleteObject( hBrush );
	MemDC.SetViewportOrg( 0, 0 );

	// Draw Vert. line
	if( m_nVertCnt > 0 )
	{
		MemDC.MoveTo( nScrollX + m_nItemDiv, 0 );
		MemDC.LineTo( nScrollX + m_nItemDiv, nClientCy );
	}

	MemDC.SelectObject( pOldPen );

	pDC->SetViewportOrg( 0, 0 );
	MemDC.BitBltTo( pDC, 0, 0, nClientCx, nClientCy );
}

void CPropItemList::InvalidateItem( INT nItem /*= -1*/ )
{
	INT nScrollX = GetScrollPos( SB_HORZ );
	INT nScrollY = GetScrollPos( SB_VERT );

	CRect rct;
	GetClientRect( rct );
	
	if( -1 == nItem )
		nItem = m_rPropCtrl.m_nSelItemIndex;

	GetItemRect( nItem, rct );
	InvalidateRect( NULL );
}

INT CPropItemList::ItemFromPoint( INT y, INT* pnItemY /*= NULL*/ )
{
	if( NULL == m_rPropCtrl.m_pProp )
	{
		if( pnItemY )
			*pnItemY = 0;

		return 0;
	}

	INT nCount = m_rPropCtrl.m_pProp->GetItemListCount();
	SPropItem** ppsItem = m_rPropCtrl.m_pProp->GetItemList();
	INT nCy, ny2, ny1 = 0;
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppsItem[i]->nCy > 0 )
			nCy = ppsItem[i]->nCy;
		else
			nCy = m_szCell.cy;
		ny2 = ny1 + nCy;

		if( y >= ny1 && y < ny2 )
		{
			if( pnItemY )
				*pnItemY = ny1;

			return i;
		}
		ny1 = ny2;
	}

	return 0;
}

INT CPropItemList::GetItemRect( INT nIndex, CRect& rrct )
{
	rrct.top = 0;
	rrct.bottom = 0;
	if( NULL == m_rPropCtrl.m_pProp )
		return 0;

	INT nCount = m_rPropCtrl.m_pProp->GetItemListCount();
	SPropItem** ppsItem = m_rPropCtrl.m_pProp->GetItemList();
	INT nCy, ny2, ny1 = 0;
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppsItem[i]->nCy > 0 )
			nCy = ppsItem[i]->nCy;
		else
			nCy = m_szCell.cy;

		ny2 = ny1 + nCy;

		if( nIndex == i )
		{
			rrct.top = ny1;
			rrct.bottom = ny2;
			return i;
		}

		ny1 = ny2;
	}

	return -1;
}

void CPropItemList::CalcItemInfo()
{
	CRect rct;
	GetClientRect( rct );
	if( m_pPropDlg )
	{
		CSize sizeTotal;
		sizeTotal.cx = m_nDlgCx;
		sizeTotal.cy = m_nDlgCx;
		SetScrollSizes( MM_TEXT, sizeTotal );
	}
	else
	{
		m_nHorzVisibleCnt = rct.Width() / m_szCell.cx;
		m_nVertVisibleCnt = rct.Height() / m_szCell.cy;

		INT nScrollX = GetScrollPos( SB_HORZ );
		INT nScrollY = GetScrollPos( SB_VERT );

		m_nLeftIndex = nScrollX / m_szCell.cx;
		m_nLeftIndexX = m_nLeftIndex * m_szCell.cx;

		m_nTopIndex = ItemFromPoint( nScrollY, &m_nTopIndexY );
	}
}

void CPropItemList::RecalcPropList()
{
	CSize sizeTotal;
	CSize sizeLine;
	CSize sizePage;

	sizeTotal.cx = m_szCell.cx * m_nHorzCnt;
	sizeTotal.cy = 0;

	if( m_rPropCtrl.m_pProp )
	{
		BOOL bFold = FALSE;
		INT nCount = m_rPropCtrl.m_pProp->GetItemListCount();
		SPropItem** ppsItem = m_rPropCtrl.m_pProp->GetItemList();
		for( INT i = 0; i < nCount; i++ )
		{
			if( FALSE == bFold )
			{
				if( ppsItem[i]->nCy > 0 )
					sizeTotal.cy += ppsItem[i]->nCy;
				else
					sizeTotal.cy += m_szCell.cy;
			}

			if( OPST_GROUP & ppsItem[i]->psProp->nType )
				bFold = 0 != (OPSF_FOLD & ppsItem[i]->psProp->nFlag);
		}
	}
	if( 0 == sizeTotal.cy )
		sizeTotal.cy = 1;

	sizeLine = m_szCell;

	sizePage.cx = m_szCell.cx * m_nHorzCnt / 3;
	sizePage.cy = m_szCell.cx * m_nVertCnt / 3;

	SetScrollSizes( MM_TEXT, sizeTotal, sizePage, sizeLine );
	InvalidateRect( NULL );
}

void CPropItemList::ReposDlg()
{
	if( NULL == m_pPropDlg || NULL == m_pPropDlg->m_hWnd )
		return;

	CRect rct;
	GetClientRect( rct );
	INT nCx = rct.Width();
	INT nCy = rct.Height();

	if( nCx < m_nDlgCx )
		nCx = m_nDlgCx;

	if( nCy < m_nDlgCy )
		nCy = m_nDlgCy;

	m_pPropDlg->SetWindowPos( 0, 0, 0, nCx, nCy, SWP_NOZORDER | SWP_NOMOVE );
}

INT CPropItemList::CreateCtrl()
{
	if( NULL == m_rPropCtrl.m_pProp || NULL == m_rPropCtrl.m_pProp->GetCurItem() )
		return -1;

	ASSERT( NULL == CProp::m_pedtProp && 
		    NULL == CProp::m_pcmbProp && 
			NULL == CProp::m_pcmbMSProp && 
			NULL == CProp::m_pbtnProp );

	SPropItem* psItem = m_rPropCtrl.m_pProp->GetCurItem();
	SProp* psProp = psItem->psProp;

	CFont fnt;
	fnt.Attach( (HFONT)GetStockObject( DEFAULT_GUI_FONT ) );

	CRect rct;
	GetClientRect( rct );
	rct.left += m_nItemDiv;
	GetItemRect( m_rPropCtrl.m_nSelItemIndex, rct );
	rct.bottom--;

	INT nDisableFlag = 0 != (OPSF_DISABLE & psProp->nFlag) ?WS_DISABLED :0;
	INT nCtrlType = psProp->nCtrlType;

	if( OPCT_BTN & nCtrlType )
	{
		CRect rctCtrl = rct;
		rctCtrl.left = rctCtrl.right - rctCtrl.Height();
		rct.right = rctCtrl.left;

		VERIFY( CProp::m_pbtnProp = m_rPropCtrl.m_pProp->CreatePropBtn( 
							psItem, _T("..."), nDisableFlag | WS_VISIBLE | WS_TABSTOP, 
							rctCtrl, this, ID_PROP_BTN ) );
	
		CProp::m_pbtnProp->SetFont( &fnt, FALSE );
	}

	if( nCtrlType & OPCT_USER )
	{
		INT nCtrlFlag = psProp->nCtrlFlag;
		if( nCtrlFlag & OPCF_USER_FROM_LABEL )
		{
			rct.left = gc_nLabelx;
			m_rPropCtrl.m_pProp->SetWindowPos( NULL, rct.left, rct.top, rct.Width(), rct.Height(), SWP_NOZORDER );
		}
		else if( nCtrlFlag & OPCF_USER_FROM_LEFT )
		{
			rct.left = 0;
			m_rPropCtrl.m_pProp->SetWindowPos( NULL, rct.left, rct.top, rct.Width(), rct.Height(), SWP_NOZORDER );
		}
		else
			m_rPropCtrl.m_pProp->SetWindowPos( NULL, rct.left, rct.top, rct.Width(), rct.Height(), SWP_NOZORDER );

		m_rPropCtrl.m_pProp->GetClientRect( rct );
		m_rPropCtrl.m_pProp->CreateDynItemCtrl( psItem, this, rct );

		// Can create only btn ctrl with user ctrl
		nCtrlType = 0;
		m_bUserItemCtrl = TRUE;
	}

	rct.DeflateRect( 1, 1 );
	if( OPCT_EDIT & nCtrlType )
	{
		rct.bottom++;
		VERIFY( CProp::m_pedtProp = m_rPropCtrl.m_pProp->CreatePropEdit( 
							psItem, WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_WANTRETURN | 
							(nDisableFlag ?ES_READONLY : 0), rct, this, ID_PROP_EDIT ) );

		CProp::m_pedtProp->SetDataType( psProp->nDataType );
		INT nDataFlag = psProp->nDataFlag;
/*		if( nDataFlag & OPIDF_MIN )
			CProp::m_pedtProp->SetMinLength( psProp->nDataMin );

		if( nDataFlag & OPIDF_MAX )
			CProp::m_pedtProp->SetMaxLength( psProp->nDataMax );

		if( nDataFlag & OPIDF_MAX )
			CProp::m_pedtProp->SetMaxLength( psProp->nDataMax );*/

		CProp::m_pedtProp->SetFont( &fnt, TRUE );

		CString csz;
		m_rPropCtrl.m_msProp.GetText( psItem, csz );
		CProp::m_pedtProp->SetWindowText( csz );
		CProp::m_pedtProp->SetSel( 0, -1 );

		// Can't create Combo type with edit ctrl
		nCtrlType &= ~OPCT_COMBO;
	}

	if( OPCT_COMBO & nCtrlType )
	{
		CRect rctCtrl = rct;
		rctCtrl.OffsetRect( 0, -1 );
		rctCtrl.bottom += 100;
		VERIFY( CProp::m_pcmbMSProp = m_rPropCtrl.m_pProp->CreatePropCombo( 
						psItem, m_szCell.cy - 7, WS_VISIBLE | WS_TABSTOP | nDisableFlag |
						CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE, rctCtrl, this, ID_PROP_COMBO ) );

		CProp::m_pcmbMSProp->SetBorderStyle( CODComboBox::BS_NONE );
		CProp::m_pcmbMSProp->SetFont( &fnt, FALSE );
		CProp::m_pcmbMSProp->m_ptTextOffset.x = 2;
		m_rPropCtrl.m_pProp->FillCombo( psItem );
		m_rPropCtrl.m_pProp->SetComboSel( psItem );
	}

	return 0;
}

INT CPropItemList::CreateStaticCtrl()
{
	if( NULL == m_rPropCtrl.m_pProp )
		return -1;

	CRect rct;
	GetClientRect( rct );
	rct.left = gc_nLabelx;
	rct.top = 0;

	BOOL bFold = FALSE;
	INT nCount = m_rPropCtrl.m_pProp->GetAllItemListCount();
	SPropItem** ppsItem = m_rPropCtrl.m_pProp->GetAllItemList();
	if( m_bAlphabeticTab )
	{
		nCount = m_rPropCtrl.m_pProp->GetItemListCount();
		ppsItem = m_rPropCtrl.m_pProp->GetItemList();
	}

	for( INT i = 0; i < nCount; i++ )
	{
		if( ppsItem[i]->nCy > 0 )
			rct.bottom = rct.top + ppsItem[i]->nCy;
		else
			rct.bottom = rct.top + m_szCell.cy;

		if( OPCT_STATIC & ppsItem[i]->psProp->nCtrlType )
		{
			m_bStaticItemCtrl = TRUE;
			INT nOldLeft = rct.left;
			INT nCtrlFlag = ppsItem[i]->psProp->nCtrlFlag;
			if( nCtrlFlag & OPCF_USER_FROM_LABEL )
				rct.left = gc_nLabelx;
			else if( nCtrlFlag & OPCF_USER_FROM_LEFT )
				rct.left = 0;
			m_rPropCtrl.m_pProp->CreateStaticCtrl( ppsItem[i], this, rct );
			rct.left = nOldLeft;

			if( bFold )
				m_rPropCtrl.m_pProp->ShowStaticCtrl( ppsItem[i], FALSE );
		}

		if( FALSE == bFold )
			rct.top = rct.bottom;

		if( OPST_GROUP & ppsItem[i]->psProp->nType )
			bFold = 0 != (OPSF_FOLD & ppsItem[i]->psProp->nFlag);
	}
	
	return 0;
}

INT CPropItemList::ReposStaticCtrl( SPropItem* psFromItem /*= NULL*/ )
{
	if( NULL == m_rPropCtrl.m_pProp )
		return 1;

	if( FALSE == m_bStaticItemCtrl )
		return 0;

	CRect rct;
	GetClientRect( rct );

	rct.left = gc_nLabelx;
	rct.top = 0;

	BOOL bFold = FALSE;
	INT i = 0;
	INT nCount = m_rPropCtrl.m_pProp->GetAllItemListCount();
	SPropItem** ppsItem = m_rPropCtrl.m_pProp->GetAllItemList();
	if( psFromItem )
	{
		for( i = 0; i < nCount; i++ )
		{
			if( ppsItem[i]->nCy > 0 )
				rct.bottom = rct.top + ppsItem[i]->nCy;
			else
				rct.bottom = rct.top + m_szCell.cy;

			if( psFromItem == ppsItem[i] )
				break;

			if( FALSE == bFold )
				rct.top = rct.bottom;

			if( OPST_GROUP & ppsItem[i]->psProp->nType )
				bFold = 0 != (OPSF_FOLD & ppsItem[i]->psProp->nFlag);
		}

		// if not matched, Start from first
		if( i == nCount )
		{
			rct.top = 0;
			i = 0; 
		}
	}

	INT nScrollX = GetScrollPos( SB_HORZ );
	INT nScrollY = GetScrollPos( SB_VERT );
	rct.OffsetRect( -nScrollX, -nScrollY );

	for( ; i < nCount; i++ )
	{
		if( ppsItem[i]->nCy > 0 )
			rct.bottom = rct.top + ppsItem[i]->nCy;
		else
			rct.bottom = rct.top + m_szCell.cy;

		if( OPCT_STATIC & ppsItem[i]->psProp->nCtrlType )
		{
			if( bFold )
				m_rPropCtrl.m_pProp->ShowStaticCtrl( ppsItem[i], FALSE );
			else
			{
				if( ppsItem[i]->pParent == psFromItem )
					m_rPropCtrl.m_pProp->ShowStaticCtrl( ppsItem[i] );

				INT nOldLeft = rct.left;
				INT nCtrlFlag = ppsItem[i]->psProp->nCtrlFlag;
				if( nCtrlFlag & OPCF_USER_FROM_LABEL )
					rct.left = gc_nLabelx;
				else if( nCtrlFlag & OPCF_USER_FROM_LEFT )
					rct.left = 0;

				m_rPropCtrl.m_pProp->MoveStaticCtrl( ppsItem[i], rct );
				rct.left = nOldLeft;
			}
		}

		if( FALSE == bFold || (OPST_GROUP & ppsItem[i]->psProp->nType) )
			rct.top = rct.bottom;

		if( OPST_GROUP & ppsItem[i]->psProp->nType )
			bFold = 0 != (OPSF_FOLD & ppsItem[i]->psProp->nFlag);
	}

	return 0;
}

void CPropItemList::OnPropEditUpdate( NMHDR* pNotifyStruct, LRESULT* plResult )
{
	*plResult = 1;
	if( _CS_INTERNAL_UPT & m_nCtrlState )
		return;

	m_nCtrlState |= _CS_INTERNAL_UPT;
	INT nResult = UpdateCtrl();
	if( 0 == nResult && NM_RETURN == pNotifyStruct->code )
		SetFocus(); // Focus to property box
		
	*plResult = nResult;
	m_nCtrlState &= ~_CS_INTERNAL_UPT;
}

INT CPropItemList::UpdateCtrl()
{
	if( NULL == m_rPropCtrl.m_pProp || NULL == m_rPropCtrl.m_pProp->GetCurItem() )
		return -1;

	SPropItem* psItem = m_rPropCtrl.m_pProp->GetCurItem();

	if( CProp::m_pedtProp && CProp::m_pedtProp->GetModify() )
	{
		CProp::m_pedtProp->UpdateText();
		CProp::m_pedtProp->SetModify( FALSE );
		INT nResult = m_rPropCtrl.m_msProp.UpdateItem( psItem );;
		if( PBR_SETFOCUS == nResult )
		{
			CProp::m_pedtProp->SetSel( 0, -1 );
			CProp::m_pedtProp->PostMessage( WM_SETFOCUS );
			return PBR_SETFOCUS;
		}

		m_rPropCtrl.m_msProp.UpdateText( psItem->psProp->nID );
	}

	if( CProp::m_pbtnProp )
	{}

	if( CProp::m_pcmbProp )
	{}

	if( CProp::m_pcmbMSProp )
		m_rPropCtrl.m_msProp.UpdateCombo( psItem );

	return 0;
}

void CPropItemList::OnPropEditCancel( NMHDR* pNotifyStruct, LRESULT* plResult )
{
	*plResult = 1;
	SPropItem* psItem = m_rPropCtrl.m_pProp->GetCurItem();
	if( CProp::m_pedtProp )
	{
		CString csz;
		m_rPropCtrl.m_msProp.GetText( psItem, csz );

		BOOL bModified = CProp::m_pedtProp->GetModify();
		CProp::m_pedtProp->SetWindowText( csz );
		SetFocus();
		if( bModified )
			m_rPropCtrl.m_msProp.EditChange( psItem );
	}

	if( CProp::m_pcmbMSProp )
		m_rPropCtrl.m_msProp.ComboCancel( psItem );
}

INT CPropItemList::DeleteCtrl()
{
	if( NULL == m_rPropCtrl.m_pProp || NULL == m_rPropCtrl.m_pProp->GetCurItem() )
		return -1;

	if( m_bUserItemCtrl )
	{
		m_rPropCtrl.m_pProp->DeleteDynItemCtrl( m_rPropCtrl.m_pProp->GetCurItem() );
		if( IsWindow( m_rPropCtrl.m_pProp->m_hWnd ) )
			m_rPropCtrl.m_pProp->SetWindowPos( NULL, -1, -1, 1, 1, SWP_NOZORDER );

		m_bUserItemCtrl = FALSE;
	}

	if( CProp::m_pedtProp )
	{
		delete CProp::m_pedtProp;
		CProp::m_pedtProp = NULL;
	}
 
	if( CProp::m_pbtnProp )
	{
		delete CProp::m_pbtnProp;
		CProp::m_pbtnProp = NULL;
	}

	if( CProp::m_pcmbProp )
	{
		delete CProp::m_pcmbProp;
		CProp::m_pcmbProp = NULL;
	}

	if( CProp::m_pcmbMSProp )
	{
		delete CProp::m_pcmbMSProp;
		CProp::m_pcmbMSProp = NULL;
	}

	return 0;
}

INT CPropItemList::DeleteStaticCtrl()
{
	if( NULL == m_rPropCtrl.m_pProp )
		return -1;

	if( FALSE == m_bStaticItemCtrl )
		return 0;

	INT nCount = m_rPropCtrl.m_pProp->GetAllItemListCount();
	SPropItem** ppsItem = m_rPropCtrl.m_pProp->GetAllItemList();
	for( INT i = 0; i < nCount; i++ )
	{
		if( OPCT_STATIC & ppsItem[i]->psProp->nCtrlType )
			m_rPropCtrl.m_pProp->DeleteStaticCtrl( ppsItem[i] );
	}

	m_bStaticItemCtrl = FALSE;
	return 0;
}

void CPropItemList::OnPropEditChange()
{
	ASSERT( CProp::m_pedtProp );
	if( CProp::m_pedtProp->GetModify() )
		m_rPropCtrl.m_pProp->EditChange( m_rPropCtrl.m_pProp->GetCurItem() );
}

void CPropItemList::OnPropBtnClicked()
{
	ASSERT( CProp::m_pbtnProp );
	m_rPropCtrl.m_pProp->BtnClick( m_rPropCtrl.m_pProp->GetCurItem() );
}

void CPropItemList::OnPropComboSelChange( NMHDR* pNotifyStruct, LRESULT* plResult )
{
	ASSERT( CProp::m_pcmbMSProp );
	m_rPropCtrl.m_pProp->ComboSelChange( m_rPropCtrl.m_pProp->GetCurItem(), 
										 (CMSComboBox::NMSELCHANGE*)pNotifyStruct, plResult );
}

void CPropItemList::OnPropComboUpdateSel( NMHDR* pNotifyStruct, LRESULT* plResult )
{
	ASSERT( CProp::m_pcmbMSProp );
	m_rPropCtrl.m_pProp->UpdateCombo( m_rPropCtrl.m_pProp->GetCurItem() );
}

void CPropItemList::OnPropComboCancelSel( NMHDR* pNotifyStruct, LRESULT* plResult )
{
	ASSERT( CProp::m_pcmbMSProp );
	m_rPropCtrl.m_pProp->ComboCancel( m_rPropCtrl.m_pProp->GetCurItem() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#define DIV_MARGIN	2
BOOL CPropItemList::TrackItemDivider( UINT nFlags, CPoint point )
{
	INT nScrollX = GetScrollPos( SB_HORZ );
	point.x += nScrollX;

	if( m_nItemDiv > point.x - DIV_MARGIN &&
		m_nItemDiv < point.x + DIV_MARGIN )
	{
		CRect rctClient;
		CRectTracker rctTracker;

		GetClientRect( rctClient );
		rctTracker.m_rect.SetRect( -1, -1, point.x, rctClient.bottom + 1 );
		rctTracker.m_nHandleSize = 1 + 2 * DIV_MARGIN;
		rctTracker.m_sizeMin.cx = g_cnMinCx;
		rctTracker.m_sizeMin.cy = 0;
		rctTracker.m_nStyle = CRectTracker::resizeOutside;
		point.y = rctTracker.m_rect.CenterPoint().y;
		point.x = rctTracker.m_rect.right;
		m_nCtrlState |= _CS_TRACKING_DIV;
		if( rctTracker.Track( this, point ) )
		{
			m_nItemDiv = rctTracker.m_rect.right + nScrollX;
			if( m_nItemDiv > rctClient.right - 30 )
				m_nItemDiv = rctClient.right - 30;

			SetCursor( LoadCursor( NULL, IDC_ARROW ) );
			InvalidateRect( NULL );
		}
		m_nCtrlState &= ~_CS_TRACKING_DIV;

		return TRUE;
	}

	return FALSE;
}

void CPropItemList::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	if( m_pPropDlg )
		return;

	if( NULL == m_rPropCtrl.m_pProp )
		return;

	INT nScrollX = GetScrollPos( SB_HORZ );
	INT nScrollY = GetScrollPos( SB_VERT );
	point.x += nScrollX;
	point.y += nScrollY;

	INT nIndex = ItemFromPoint( point.y );

	SPropItem* psItem = m_rPropCtrl.m_pProp->GetItemAt( nIndex );
	if( NULL == psItem )
		return;

	if( OPST_GROUP == psItem->psProp->nType )
	{
		CRect rctPlus;
		rctPlus.left = gc_nLabelx + gc_nPlusx;
		rctPlus.right = rctPlus.left + gc_nPlusCs;
		GetItemRect( nIndex, rctPlus );
		rctPlus.top += (m_szCell.cy - gc_nPlusCs) / 2;
		rctPlus.bottom = rctPlus.top + gc_nPlusCs;
		if( rctPlus.PtInRect( point ) )
			return;

		m_rPropCtrl.ExpandPropGroup( nIndex, 0 == (OPSF_FOLD & psItem->psProp->nFlag) );
		return;
	}
}

void CPropItemList::OnLButtonDown( UINT nFlags, CPoint point )
{
	if( m_pPropDlg )
		return;

	if( TrackItemDivider( nFlags, point ) )
		return;

	if( NULL == m_rPropCtrl.m_pProp )
		return;

	INT nScrollX = GetScrollPos( SB_HORZ );
	INT nScrollY = GetScrollPos( SB_VERT );
	point.x += nScrollX;
	point.y += nScrollY;

	INT nIndex = ItemFromPoint( point.y );
	SPropItem* psItem = m_rPropCtrl.m_pProp->GetItemAt( nIndex );
	if( NULL == psItem )
		return;

	if( OPST_GROUP == psItem->psProp->nType )
	{
		CRect rctPlus;
		rctPlus.left = gc_nLabelx + gc_nPlusx;
		rctPlus.right = rctPlus.left + gc_nPlusCs;
		GetItemRect( nIndex, rctPlus );
		rctPlus.top += (m_szCell.cy - gc_nPlusCs) / 2;
		rctPlus.bottom = rctPlus.top + gc_nPlusCs;
		if( rctPlus.PtInRect( point ) )
		{
			m_rPropCtrl.ExpandPropGroup( nIndex, 0 == (OPSF_FOLD & psItem->psProp->nFlag) );
			return;
		}
	}

	if( 0 != UpdateCtrl() )
		return;

	m_rPropCtrl.SetCurPropItemByIndex( nIndex );

	point.x -= nScrollX;
	point.y -= nScrollY;
	CWnd* pWnd = ChildWindowFromPoint( point );

	// In the click point if edit ctrl is there set that active
	if( pWnd && pWnd == CProp::m_pedtProp )
		pWnd->SetFocus();
}

void CPropItemList::OnMouseMove( UINT nFlags, CPoint point )
{
	if( m_pPropDlg )
		return;

	INT nScrollX = GetScrollPos( SB_HORZ );
	point.x += nScrollX;

	if( m_nItemDiv > point.x - DIV_MARGIN &&
		m_nItemDiv < point.x + DIV_MARGIN )
		SetCursor( LoadCursor( NULL, IDC_SIZEWE ) );
}

UINT CPropItemList::OnGetDlgCode()
{
	UINT unReturn = CScrollView::OnGetDlgCode();
	if( NULL == m_pPropDlg )
		unReturn |= DLGC_WANTARROWS | DLGC_WANTCHARS | DLGC_WANTTAB;
	return unReturn;
}

void CPropItemList::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if( VK_ESCAPE == nChar && IsKeyShift() )
	{
		ShowWindow( SW_HIDE );
		return;
	}

	if( m_pPropDlg )
		return;

	if( NULL == m_rPropCtrl.m_pProp )
		return;

	if( IsKeyNoShift() )
	{
		SPropItem* psItem = m_rPropCtrl.m_pProp->GetItemAt( m_rPropCtrl.m_nSelItemIndex );
		if( psItem && OPST_GROUP == psItem->psProp->nType )
		{
			if( ((VK_RIGHT == nChar || VK_ADD == nChar) && OPSF_FOLD & psItem->psProp->nFlag) || 
				((VK_LEFT == nChar || VK_SUBTRACT == nChar) && 0 == (OPSF_FOLD & psItem->psProp->nFlag)) )
			{
				m_rPropCtrl.ExpandPropGroup( m_rPropCtrl.m_nSelItemIndex, 0 == (OPSF_FOLD & psItem->psProp->nFlag) );
				return;
			}
		}

		if( VK_UP == nChar || VK_DOWN == nChar )
		{
			INT nNewSel = m_rPropCtrl.m_nSelItemIndex;
			if( VK_DOWN == nChar )
				nNewSel++;
			else
				nNewSel--;

			psItem = m_rPropCtrl.m_pProp->GetItemAt( nNewSel );
			if( psItem )
			{
				if( 0 == UpdateCtrl() )
					m_rPropCtrl.SetCurPropItemByIndex( nNewSel );

			}

			return;
		}
	}

	if( 0 && VK_TAB == nChar )
	{
		CWnd* pWnd = GetNextWindow( GW_HWNDPREV );
		//pWnd = pWnd->GetNextWindow( GW_HWNDPREV )

		if( IsKeyShift() )
			pWnd = GetNextWindow( GW_HWNDPREV );

		if( pWnd )
			pWnd->SetFocus();

		return;
	}

	if( VK_SHIFT == nChar || VK_CONTROL == nChar )
		return;

	if( CProp::m_pedtProp && GetFocus() != CProp::m_pedtProp )
		CProp::m_pedtProp->SetFocus();
}

void CPropItemList::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{}
