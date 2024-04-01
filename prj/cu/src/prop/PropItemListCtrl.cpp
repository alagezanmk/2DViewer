#include "stdafx.h"
#include "PropItemListCtrl.h"
#include "PropBox.h"
#include "Prop.h"

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

////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CPropItemListCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CPropItemTreeCtrl)
	ON_NOTIFY_REFLECT( NM_CUSTOMDRAW, OnCustomdraw )
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT( TVN_DELETEITEM, OnDeleteItem )
	ON_NOTIFY_REFLECT( TVN_ITEMEXPANDED, OnItemExpanded )
	ON_NOTIFY_REFLECT( TVN_SELCHANGED, OnSelChanged )

	ON_NOTIFY( NM_KILLFOCUS, ID_PROP_EDIT, OnPropEditUpdate )
	ON_NOTIFY( NM_RETURN, ID_PROP_EDIT, OnPropEditUpdate )
	ON_NOTIFY( NM_UPDATE, ID_PROP_EDIT, OnPropEditUpdate )
	ON_NOTIFY( NM_CANCEL, ID_PROP_EDIT, OnPropEditCancel )

	ON_BN_CLICKED( ID_PROP_BTN, OnPropBtnClicked )
	ON_EN_CHANGE( ID_PROP_EDIT, OnPropEditChange )

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPropItemListCtrl::CPropItemListCtrl( CPropBox& rPropCtrl )
 	: m_rPropCtrl( rPropCtrl )
{
	m_bAlphatbeticalMode = FALSE;
	m_pPropDlg = NULL;
	m_nItemDiv = 100;
	m_bUserItemCtrl = FALSE;
	m_nCtrlState = _CS_NONE;
}

CPropItemListCtrl::~CPropItemListCtrl()
{}

HTREEITEM CPropItemListCtrl::InsertPropItem( SPropItem& rsItem, 
										     SPropItem* psParent /*= ROOT*/, 
											 SPropItem* psInsertAfter /*= LAST*/ )
{
	if( NULL == m_rPropCtrl.m_pProp )
		return NULL;

	HTREEITEM hItem = PropToHTREEITEM( rsItem );
	if( hItem )
		return NULL; // Already there
	
	HTREEITEM hParent = TVI_ROOT;
	if( NULL == psParent ) 
		hParent = TVI_ROOT;
	else if( ROOT != psParent )
	{
		hParent = PropToHTREEITEM( *psParent );
		if( NULL == hParent )
			return NULL; // Parent is not found
	}
	
	HTREEITEM hInsertAfter = TVI_LAST;
	if( NULL == psInsertAfter )
		hInsertAfter = TVI_LAST;
	else if( FIRST != psInsertAfter && LAST != psInsertAfter )
	{
		hInsertAfter = PropToHTREEITEM( *psInsertAfter );
		if( NULL == hInsertAfter )
			return NULL; // Insert after is not found
	}
	
	CString cszText;
	m_rPropCtrl.m_pProp->GetLabel( &rsItem, cszText );
	if( cszText.IsEmpty() )
		cszText.Format( _T("[Unknown %x]"), &rsItem );

	hItem = InsertItem( cszText, hParent, hInsertAfter );
	if( NULL == hItem )
		return NULL;	// Insert failed
	
	m_mapPropItem[&rsItem] = hItem;
	SetItemData( hItem, (DWORD)&rsItem );
	
	return hItem;
}

BOOL CPropItemListCtrl::DeletePropItem( SPropItem& rsItem )
{
	HTREEITEM hItem = PropToHTREEITEM( rsItem );
	if( NULL == hItem )
		return FALSE; // Not there
	
	if( DeleteItem( hItem ) )
	{
		BOOL bResult = m_mapPropItem.RemoveKey( &rsItem );
		return TRUE;
	}
	
	return FALSE;
}

void CPropItemListCtrl::OnDeleteItem( NMHDR* pNMHDR, LRESULT* lpResult )
{
	NMTREEVIEW* pNM = (NMTREEVIEW*)pNMHDR;
	HTREEITEM hItem = pNM->itemOld.hItem;
	SPropItem* psItem = (SPropItem*)pNM->itemOld.lParam;
	if( psItem && m_mapPropItem[psItem] )
		m_mapPropItem.RemoveKey( psItem );
}

void CPropItemListCtrl::OnItemExpanded( NMHDR* pNMHDR, LRESULT* lpResult )
{
	NMTREEVIEW* pNM = (NMTREEVIEW*)pNMHDR;
	HTREEITEM hItem = pNM->itemNew.hItem;
	SPropItem* psItem = (SPropItem*)pNM->itemNew.lParam;
	/*if( psItem && m_mapPropItem[psItem] )
	{
		psItem = psItem;
	}*/
}

void CPropItemListCtrl::OnSelChanged( NMHDR* pNMHDR, LRESULT* lpResult )
{
	NMTREEVIEW* pNM = (NMTREEVIEW*)pNMHDR;
	HTREEITEM hItem = pNM->itemNew.hItem;
	if( hItem )
	{
		SPropItem* psItem = (SPropItem*)pNM->itemNew.lParam;
		if( psItem )
		{
			INT nID = psItem->psProp->nID;
			m_rPropCtrl.SetCurPropItem( nID );
		}
	}
}

void CPropItemListCtrl::OnSize( UINT nType, int cx, int cy )
{
	CTreeCtrl::OnSize( nType, cx, cy );
}

void CPropItemListCtrl::OnCustomdraw( NMHDR* pNMHDR, LRESULT* lpResult )
{
	NMTVCUSTOMDRAW* nmcd = (NMTVCUSTOMDRAW*)pNMHDR;
    *lpResult = CDRF_DODEFAULT;

	switch( nmcd->nmcd.dwDrawStage )
	{
	case CDDS_PREPAINT:
		*lpResult = CDRF_NOTIFYITEMDRAW; 
		return;

	case CDDS_ITEMPREPAINT:
		{
			HTREEITEM hItem = (HTREEITEM)nmcd->nmcd.dwItemSpec;
			SPropItem* psItem = (SPropItem*)GetItemData( hItem );
			
			CDC dc;
			dc.Attach( nmcd->nmcd.hdc );

			// Draw Item Background
			UINT nState = GetItemState( hItem, TVIS_EXPANDED );
			BOOL bExpanded = TVIS_EXPANDED == (TVIS_EXPANDED & nState);
			BOOL bSelected = CDIS_SELECTED == (CDIS_SELECTED & nmcd->nmcd.uItemState);

			COLORREF crf = GetSysColor( COLOR_HIGHLIGHT );
			GetCrfBtnShades( crf, NULL, &crf, 0, 70 );

			BOOL bGroupItem = OPST_GROUP == psItem->psProp->nType;
			CRect rct = nmcd->nmcd.rc;

			// Draw Full Background
			COLORREF crfBkGnd;
			crfBkGnd = nmcd->clrTextBk;
			if( bGroupItem )
				crfBkGnd = crf;
			
			dc.FillSolidRect( rct, crfBkGnd );

			// Draw First Half Background for selected
			if( bSelected )
			{
				crfBkGnd = GetSysColor(  CDIS_FOCUS & nmcd->nmcd.uItemState ?COLOR_HIGHLIGHT :COLOR_BTNFACE  );
				dc.FillSolidRect( rct.left, rct.top, m_nItemDiv, rct.bottom, crfBkGnd );
			}

			// Draw Second Half Background for Item except Group
			if( FALSE == bGroupItem ) 
				dc.FillSolidRect( m_nItemDiv, rct.top, rct.right, rct.bottom, GetSysColor( COLOR_WINDOW ) );

			// Draw Group Plus / Minus
			const INT cnLeftX = 4;
			INT nItemCy = rct.Height();
			INT x = rct.left + cnLeftX + gc_nPlusCs;
			INT y = rct.top;

			if( bGroupItem )
			{
				CRect rctPlus( 0, 0, gc_nPlusCs, gc_nPlusCs );
				rctPlus.OffsetRect( x - gc_nPlusCs, y + (nItemCy - gc_nPlusCs) / 2 );

				HPEN hPen = CreatePen( PS_SOLID, 1, GetSysColor( COLOR_WINDOWTEXT ) );
				ASSERT( hPen );
				HPEN hOldPen = (HPEN)SelectObject( dc.m_hDC, hPen );

				HBRUSH hBrush = GetSysColorBrush( COLOR_WINDOW );
				HBRUSH hOldBrush = (HBRUSH)SelectObject( dc.m_hDC, hBrush );

				dc.Rectangle( rctPlus );

				const INT cnMargin = 3;
				const INT cnHLen = (gc_nPlusCs - cnMargin * 2) / 2;
				rctPlus.DeflateRect( cnMargin, cnMargin );
				dc.MoveTo( rctPlus.left, rctPlus.top + cnHLen );
				dc.LineTo( rctPlus.right, rctPlus.top + cnHLen );

				BOOL bExpanded = TVIS_EXPANDED == (TVIS_EXPANDED & nState);
				if( FALSE == bExpanded )
				{
					dc.MoveTo( rctPlus.left + cnHLen, rctPlus.top );
					dc.LineTo( rctPlus.left + cnHLen, rctPlus.bottom );
				}

				SelectObject( dc.m_hDC, hOldBrush );
				SelectObject( dc.m_hDC, hOldPen );
				DeleteObject( hOldPen );
			}

			// Draw Item Text
			INT nOldBkMode = dc.SetBkMode( TRANSPARENT );

			rct.left = x + cnLeftX;
			rct.right = m_nItemDiv;
			CString cszText = GetItemText( hItem );
			dc.DrawText( cszText, rct, DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS );

			// Draw Item Value
			const INT cnValueLeftX = 3;
			COLORREF crfOldText = dc.SetTextColor( GetSysColor( COLOR_WINDOWTEXT ) );
			
			BOOL bMultiple;
			cszText.Empty();
			m_rPropCtrl.m_msProp.GetText( psItem, cszText, &bMultiple );
			rct.left = m_nItemDiv + cnValueLeftX;
			rct.right = nmcd->nmcd.rc.right;
			dc.DrawText( cszText, rct, DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS );
			dc.SetTextColor( crfOldText );

			dc.SetBkMode( nOldBkMode );

			// Draw Vertical and Horizontal line
			rct = nmcd->nmcd.rc;
			crf = GetSysColor( COLOR_BTNFACE );
			GetCrfBtnShades( crf, NULL, &crf, 0, 3 );

			HPEN hPen = CreatePen( PS_SOLID, 1, crf );
			ASSERT( hPen );
			HPEN hOldPen = (HPEN)SelectObject( dc.m_hDC, hPen );
			
			// Draw Horizontal line
			dc.MoveTo( rct.left, rct.bottom - 1 );
			dc.LineTo( rct.right, rct.bottom - 1 );

			// Draw Vertical line
			dc.MoveTo( m_nItemDiv, rct.top );
			dc.LineTo( m_nItemDiv, rct.bottom );

			SelectObject( dc.m_hDC, hOldPen );
			DeleteObject( hPen );
			
			dc.Detach();
			*lpResult = CDRF_SKIPDEFAULT;
		}
		break;
	}
}

void CPropItemListCtrl::ResetContent() {
	DeleteAllItems(); }

void CPropItemListCtrl::ReposDlg()
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

INT CPropItemListCtrl::CreateStaticControl()
{
	if( NULL == m_rPropCtrl.m_pProp )
		return -1;
	
	/*CRect rct;
	GetClientRect( rct );
	rct.left = gc_nLabelx;
	rct.top = 0;
	
	BOOL bFold = FALSE;
	INT nCount = m_rPropCtrl.m_pProp->GetAllItemListCount();
	SPropItem** ppsItem = m_rPropCtrl.m_pProp->GetAllItemList();
	if( m_bAlphatbeticMode )
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
	}*/
	
	return 0;
}

INT CPropItemListCtrl::DeleteStaticControl()
{
	if( NULL == m_rPropCtrl.m_pProp )
		return -1;
	
	/*if( FALSE == m_bStaticItemCtrl )
		return 0;
	
	INT nCount = m_rPropCtrl.m_pProp->GetAllItemListCount();
	SPropItem** ppsItem = m_rPropCtrl.m_pProp->GetAllItemList();
	for( INT i = 0; i < nCount; i++ )
	{
		if( OPCT_STATIC & ppsItem[i]->psProp->nCtrlType )
			m_rPropCtrl.m_pProp->DeleteStaticCtrl( ppsItem[i] );
	}
	
	m_bStaticItemCtrl = FALSE;*/
	return 0;
}

INT CPropItemListCtrl::ReposStaticControl( SPropItem* psFromItem /*= NULL*/ )
{
	if( NULL == m_rPropCtrl.m_pProp )
		return 1;
	
	/*if( FALSE == m_bStaticItemCtrl )
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
	}*/
	
	return 0;
}

INT CPropItemListCtrl::CreateControl()
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
	//GetClientRect( rct );
	//rct.left += m_nItemDiv;
	GetPropItemRect( *m_rPropCtrl.m_pProp->m_psCurItem, rct );
	//rct.bottom--;

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
		rct.left++;
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
		CProp::m_pedtProp->SetSel( 0, 0 );

		// Can't create Combo type with edit ctrl
		nCtrlType &= ~OPCT_COMBO;
	}

	if( OPCT_COMBO & nCtrlType )
	{
		CRect rctCtrl = rct;
		rctCtrl.OffsetRect( 0, -1 );
		rctCtrl.bottom += 100;
		VERIFY( CProp::m_pcmbMSProp = m_rPropCtrl.m_pProp->CreatePropCombo( 
						psItem, rct.Height(), WS_VISIBLE | WS_TABSTOP | nDisableFlag |
						CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE, rctCtrl, this, ID_PROP_COMBO ) );

		CProp::m_pcmbMSProp->SetBorderStyle( CODComboBox::BS_NONE );
		CProp::m_pcmbMSProp->SetFont( &fnt, FALSE );
		CProp::m_pcmbMSProp->m_ptTextOffset.x = 2;
		m_rPropCtrl.m_pProp->FillCombo( psItem );
		m_rPropCtrl.m_pProp->SetComboSel( psItem );
	}

	return 0;
}

INT CPropItemListCtrl::UpdateControl()
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

INT CPropItemListCtrl::DeleteControl()
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

BOOL CPropItemListCtrl::GetPropItemRect( SPropItem& rsItem, RECT& rRect ) const
{
	HTREEITEM hItem = PropToHTREEITEM( rsItem );
	if( NULL == hItem )
		return FALSE;
	
	GetItemRect( hItem, &rRect, FALSE );
	rRect.left = m_nItemDiv;
	return TRUE;
}

void CPropItemListCtrl::UpdatePropItem( SPropItem& rsItem )
{
	CRect rect;
	if( GetPropItemRect( rsItem, rect ) )
		InvalidateRect( rect, FALSE );
}

void CPropItemListCtrl::OnPropEditUpdate( NMHDR* pNotifyStruct, LRESULT* plResult )
{
	*plResult = 1;
	if( _CS_INTERNAL_UPT & m_nCtrlState )
		return;
	
	m_nCtrlState |= _CS_INTERNAL_UPT;
	INT nResult = UpdateControl();
	if( 0 == nResult && NM_RETURN == pNotifyStruct->code )
		SetFocus(); // Focus to property box
	
	*plResult = nResult;
	m_nCtrlState &= ~_CS_INTERNAL_UPT;
}

void CPropItemListCtrl::OnPropEditCancel( NMHDR* pNotifyStruct, LRESULT* plResult )
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

void CPropItemListCtrl::OnPropEditChange()
{
	ASSERT( CProp::m_pedtProp );
	if( CProp::m_pedtProp->GetModify() )
		m_rPropCtrl.m_pProp->EditChange( m_rPropCtrl.m_pProp->GetCurItem() );
}

void CPropItemListCtrl::OnPropBtnClicked()
{
	ASSERT( CProp::m_pbtnProp );
	m_rPropCtrl.m_pProp->BtnClick( m_rPropCtrl.m_pProp->GetCurItem() );
}

void CPropItemListCtrl::OnPropComboSelChange( NMHDR* pNotifyStruct, LRESULT* plResult )
{
	ASSERT( CProp::m_pcmbMSProp );
	m_rPropCtrl.m_pProp->ComboSelChange( m_rPropCtrl.m_pProp->GetCurItem(), 
		(CMSComboBox::NMSELCHANGE*)pNotifyStruct, plResult );
}

void CPropItemListCtrl::OnPropComboUpdateSel( NMHDR* pNotifyStruct, LRESULT* plResult )
{
	ASSERT( CProp::m_pcmbMSProp );
	m_rPropCtrl.m_pProp->UpdateCombo( m_rPropCtrl.m_pProp->GetCurItem() );
}

void CPropItemListCtrl::OnPropComboCancelSel( NMHDR* pNotifyStruct, LRESULT* plResult )
{
	ASSERT( CProp::m_pcmbMSProp );
	m_rPropCtrl.m_pProp->ComboCancel( m_rPropCtrl.m_pProp->GetCurItem() );
}
