#include "stdafx.h"
#include "PropBox.h"
#include "Resource.h"

#include <gl\gl.h>
#include <cu\MemDC.h>
#include <cu\Key.h>
#include <gbase\gObjectNode.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const INT gc_nCmbTop = 0;
const INT gc_nCmbCy = 20;
const INT gc_nCmbListCy = 100;
const INT gc_nCmbBottom = gc_nCmbTop + gc_nCmbCy;

const INT gc_nTabTop = gc_nCmbBottom;
const INT gc_nTabCy = 24;

const INT gc_nDescBorder = 2;
const INT gc_nDescCy = 45;

#define ID_OBJ_COMBO				1
#define ID_TAB_CTRL					2
#define ID_PROP_LIST				3
#define ID_DESC_WND					4
#define ID_PROP_ITEM_TREE_CTRL		5

#define _CS_NONE					0
#define _CS_TRACKING_DIV			1
#define _CS_INTERNAL_UPT			2

// Bug: document selection is now allowed, it should not be allowed
// Bug: Multiple selection is not working, 
//		1. When view is being selected
//		2. selecting another object should deselect view
/////////////////////////////////////////////////////////////////////////////
// CPropDesc class
BEGIN_MESSAGE_MAP(CPropDesc, CWnd)
	//{{AFX_MSG_MAP(CPropDesc)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPropDesc::CPropDesc()
{}

CPropDesc::~CPropDesc()
{}

void CPropDesc::OnPaint()
{
	CRect	rctClient;
	HFONT   hOldFont;
	CPaintDC dc(this);

	hOldFont = (HFONT)SelectObject( dc.m_hDC, GetStockObject( DEFAULT_GUI_FONT ) );
	HBRUSH hBrush = GetSysColorBrush( COLOR_BTNFACE );

	dc.SetBkMode( TRANSPARENT);
	GetClientRect( rctClient );
	FillRect( dc.m_hDC, rctClient, hBrush );

	rctClient.DeflateRect( gc_nDescBorder, gc_nDescBorder );
	dc.DrawText( m_cszDesc, rctClient, DT_TOP | DT_LEFT | DT_END_ELLIPSIS | DT_WORDBREAK );
	SelectObject( dc.m_hDC, hOldFont );
}

/////////////////////////////////////////////////////////////////////////////
struct CPropBox::SObj
{
	void*		pvObject;
	INT			nID;
	HTREEITEM	hItem;
};

/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CPropBox, CFrameWnd)
	//{{AFX_MSG_MAP(CPropCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY( TCN_SELCHANGE, ID_TAB_CTRL, OnTabSelChange )
	ON_COMMAND_RANGE( ID_PROP_BTN1, ID_PROP_BTN3, OnPropBtn )
	ON_UPDATE_COMMAND_UI_RANGE( ID_PROP_BTN1, ID_PROP_BTN3, OnPropBtnUI )
	ON_NOTIFY( CPropObjectSelComboBox::NM_SELCHANGE, ID_OBJ_COMBO, OnObjectSelChange )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#pragma warning(disable: 4355)  // this : used in base member initializer list
CPropBox::CPropBox() : 
	m_msProp( *this )
{
	m_nCurPropID = 0;
	m_nCurItemIndex = -1;

	m_pvObject = NULL;
	m_pProp = NULL;

	//m_msProp.m_pPropCtrl = this;
	m_pPropItemListCtrl = NULL;
	m_pfnOnSelNotify = NULL;
} 
#pragma warning(default: 4355)

CPropBox::~CPropBox()
{
	if( m_pProp )
		m_msProp.DeleteProp( m_pProp );

	INT nCount = ms_arpHandler.GetSize();
	SPropHandler** ppsHandler = (SPropHandler**)ms_arpHandler.GetData();
	for( INT i = 0; i < nCount; i++ )
		delete ppsHandler[i];

	if( m_pPropItemListCtrl )
		delete m_pPropItemListCtrl;
}

BOOL CPropBox::PreCreateWindow( CREATESTRUCT& cs )
{
	if( FALSE == CFrameWnd::PreCreateWindow( cs ) )
		return FALSE;

	cs.style |= WS_CLIPCHILDREN;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	return TRUE;
}

INT CPropBox::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( -1 == CFrameWnd::OnCreate( lpCreateStruct ) )
		return -1;

	CFont font;
	font.Attach( (HFONT)GetStockObject( DEFAULT_GUI_FONT ) );

	if( FALSE == m_cmbObjectSel.Create( WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_GROUP | WS_TABSTOP |
								        CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE, 
								        nullRECT, this, ID_OBJ_COMBO ) )
	{
		TRACE( _T("CPropBox::OnCreate: Object selection combo box create failed\n") );
		ASSERT( m_pPropItemListCtrl );
		return -1;
	}

	m_cmbObjectSel.SetFont( &font, FALSE );
	m_cmbObjectSel.m_ptTextOffset.x = 2;
	
	// To calculate PropItem list height
	{
		HDC hDC = ::GetDC( m_hWnd );
		HFONT hOldFont = (HFONT)::SelectObject( hDC, font.m_hObject );
		TEXTMETRIC tm;
		GetTextMetrics( hDC, &tm );
		::SelectObject( hDC, hOldFont );
		::ReleaseDC( m_hWnd, hDC );
	}

	// Create Prop Item Tree Control
	ASSERT( NULL == m_pPropItemListCtrl );
	m_pPropItemListCtrl = new CPropItemListCtrl( *this );
	if( NULL == m_pPropItemListCtrl )
	{
		TRACE( _T("CPropBox::OnCreate: Item List object create failed\n") );
		ASSERT( m_pPropItemListCtrl );
		return -1;
	}

	if( FALSE == m_pPropItemListCtrl->Create( WS_CHILD | WS_VISIBLE | TVS_HASBUTTONS 
											  | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_FULLROWSELECT, 
											   CRect(0,0,0,0), this, ID_PROP_ITEM_TREE_CTRL ) ) 
	{
		TRACE( _T("CPropBox::OnCreate: Item List Window create failed\n") );
		ASSERT( FALSE );
		return -1;
	}

	if( FALSE == m_TabCtrl.Create( WS_CHILD | 0 | WS_TABSTOP | WS_VISIBLE, 
								   CRect(0, gc_nTabTop, 120, 60), this, ID_TAB_CTRL ) )
	{
		TRACE( _T("CPropBox::OnCreate: Tab Window create failed\n") );
		ASSERT( FALSE );
		return -1;
	}

	m_TabCtrl.SetFont( &font, FALSE );
	m_TabCtrl.InsertItem( 0, _T("Properties") );

	if( FALSE == m_PropDesc.CreateEx( WS_EX_STATICEDGE, NULL, NULL, 
									  WS_CHILD | WS_VISIBLE, nullRECT,
									  this, ID_DESC_WND ) )
	{
		TRACE( _T("CPropBox::OnCreate: Description Window create failed\n") );
		ASSERT( FALSE );
		return -1;
	}

	m_PropDesc.SetString( _T("Here display description of the selected property item in the above list") );
	font.Detach();

	return 0;
}

void CPropBox::OnSize( UINT nType, INT cx, INT cy )
{
	CFrameWnd::OnSize( nType, cx, cy );

	if( m_cmbObjectSel.m_hWnd )
		m_cmbObjectSel.SetWindowPos( NULL, 0, gc_nCmbTop, cx, gc_nCmbBottom + gc_nCmbListCy, SWP_NOZORDER );

	/*if( m_ToolBar.m_hWnd )
		m_ToolBar.SetWindowPos( NULL, 0, gc_nCmbCy - 1, cx, gc_nTabCy, SWP_NOZORDER );*/

	if( m_TabCtrl.m_hWnd )
	{
		m_TabCtrl.SetWindowPos( NULL, -2, gc_nCmbCy, cx + 6, gc_nTabCy, SWP_NOZORDER );
		//m_TabCtrl.SetWindowPos( NULL, -2, gc_nCmbCy, 1, 1, SWP_NOZORDER );
	}

	INT nListTop = gc_nCmbCy + gc_nTabCy - 1;
	INT nListCy = cy - nListTop - gc_nDescCy;

	if( m_pPropItemListCtrl->m_hWnd )
		m_pPropItemListCtrl->SetWindowPos( NULL, 0, nListTop, cx, nListCy, SWP_NOZORDER );

	if( m_PropDesc.m_hWnd )
		m_PropDesc.SetWindowPos( NULL, 0, nListTop + nListCy, cx, gc_nDescCy, SWP_NOZORDER );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void CPropBox::ResetContent()
{
	SetCurObject( NULL );
	if( m_cmbObjectSel.m_hWnd )
		m_cmbObjectSel.ResetContent();
}

void CPropBox::SetNotifyHook( NOTIFY_HOOK_TYPE enType, PFNOnNotify pfnOnNotify, void* pvParam /*= NULL*/ )
{
	switch( enType )
	{
	case SEL_NOTIFY_HOOK:
		m_pfnOnSelNotify = pfnOnNotify;
		m_pvOnSelNotifyParam = pvParam;
		break;
	}
}

void CPropBox::OnObjectSelChange( NMHDR* pNMHDR, LRESULT* plResult )
{
	if( m_pfnOnSelNotify )
	{
		(*m_pfnOnSelNotify)( pNMHDR, plResult, m_pvOnSelNotifyParam );
		if( 1 == *plResult )
			return;
	}

	CPropObjectSelComboBox::NMSELCHANGE* pNM = (CPropObjectSelComboBox::NMSELCHANGE*)pNMHDR;
	void* pvObject = (void*)m_cmbObjectSel.m_ListCtrl.GetItemData( pNM->hItem );
	ASSERT( pvObject );

	if( pNM->bMultipleSel )
		SelectObject( pvObject, pNM->bSelect );
	else
	{
		if( FALSE == pNM->bSelect )
			SetCurObject( NULL );
		else
			SetCurObject( pvObject );
	}

	if( FALSE == pNM->bMultipleSel && FALSE == pNM->bSelect )
		return;	// Allow single deselection > Alag: this case never comes

	*plResult = 1; // Always override List Ctrl to select/deselect item its own
}

void* CPropBox::HTREEITEMToObject( HTREEITEM hItem )
{
	void* pvObject = (void*)m_cmbObjectSel.m_ListCtrl.GetItemData( hItem );
	return pvObject;
}

HTREEITEM CPropBox::ObjectToHTREEITEM( void* pvObject ) 
{
	SObj* psObj = (SObj*)m_mapObjectItem[pvObject];
	if( NULL == psObj )
		return NULL;

	return psObj->hItem;
}

BOOL CPropBox::InsertObject( void* pvObject, LPCTSTR ptszName, INT nID,
						     void* pvParent /*= TVI_ROOT*/, 
						     void* pvInsertAfter /*= TVI_LAST*/ )
{
	HTREEITEM hItem = ObjectToHTREEITEM( pvObject );
	if( hItem )
		return FALSE; // Already there

	CTreeCtrl& rTreeCtrl = m_cmbObjectSel.m_ListCtrl;	

	HTREEITEM hParent = TVI_ROOT;
	if( NULL == pvParent ) 
		hParent = TVI_ROOT;
	else if( TVI_ROOT != pvParent )
	{
		hParent = ObjectToHTREEITEM( pvParent );
		if( NULL == hParent )
			return FALSE; // Parent is not found
	}

	HTREEITEM hInsertAfter = TVI_LAST;
	if( NULL == pvInsertAfter )
		hInsertAfter = TVI_LAST;
	else if( TVI_FIRST != pvInsertAfter && TVI_LAST != pvInsertAfter )
	{
		hInsertAfter = ObjectToHTREEITEM( pvInsertAfter );
		if( NULL == hInsertAfter )
			return FALSE; // Insert after is not found
	}

	SObj* psObj = new SObj;
	if( NULL == psObj )
	{
		ASSERT( psObj );
		return FALSE;
	}

	hItem = rTreeCtrl.InsertItem( ptszName, hParent, hInsertAfter );
	if( NULL == hItem )
	{
		delete psObj;
		return FALSE;	// Insert failed
	}

	psObj->pvObject = pvObject;
	psObj->hItem = hItem;
	psObj->nID = nID;
	m_mapObjectItem[pvObject] = psObj;

	rTreeCtrl.SetItemData( hItem, (DWORD)pvObject );
	
	return TRUE;
}

BOOL CPropBox::DeleteObject( void* pvObject )
{
	SObj* psObj = (SObj*)m_mapObjectItem[pvObject];
	if( NULL == psObj )
		return FALSE; // Not there

	CTreeCtrl& rTreeCtrl = m_cmbObjectSel.m_ListCtrl;	
	if( rTreeCtrl.DeleteItem( psObj->hItem ) )
	{
		m_mapObjectItem.RemoveKey( pvObject );
		delete psObj;
		return TRUE;
	}

	return FALSE;
}

CPtrArray CPropBox::ms_arpHandler;
SPropHandler* CPropBox::GetPropHandler( INT nID )
{
	INT nCount = ms_arpHandler.GetSize();
	SPropHandler** ppsHandler = (SPropHandler**)ms_arpHandler.GetData();
	for( INT i = 0; i < nCount; i++ )
		if( ppsHandler[i]->nID == nID )
			return ppsHandler[i];
	
	return NULL;
}

void CPropBox::AddPropHandler( SPropHandler* psHandler )
{
	ASSERT( psHandler );
	INT nCount = ms_arpHandler.GetSize();
	SPropHandler** ppsHandler = (SPropHandler**)ms_arpHandler.GetData();
	for( INT i = 0; i < nCount; i++ )
		if( ppsHandler[i]->nID == psHandler->nID )
		{
			ppsHandler[i]->nID = psHandler->nID;
			ppsHandler[i]->pfnPropHandler = psHandler->pfnPropHandler;
			return;
		}

	SPropHandler* psNewHandler = new SPropHandler;
	ASSERT( psNewHandler );
	psNewHandler->nID = psHandler->nID;
	psNewHandler->pfnPropHandler = psHandler->pfnPropHandler;
	
	ms_arpHandler.Add( psNewHandler );
}

void CPropBox::ResetPropList( BOOL bDeleteProp /*= TRUE*/ )
{
	m_pPropItemListCtrl->UpdateControl();
	m_pPropItemListCtrl->DeleteControl();
	m_pPropItemListCtrl->DeleteStaticControl();
	if( m_pPropItemListCtrl->m_pPropDlg )
	{
		delete m_pPropItemListCtrl->m_pPropDlg;
		m_pPropItemListCtrl->m_pPropDlg = NULL;
	}

	m_pPropItemListCtrl->ResetContent();
	if( FALSE == bDeleteProp )
		m_pPropItemListCtrl->UpdateWindow();

	if( bDeleteProp && m_pProp )
	{
		m_msProp.DeleteProp( m_pProp );
		m_pProp = NULL;
	}
}

BOOL CPropBox::SetActiveObject( void* pvObject )
{
	if( m_pProp && m_pProp->GetObject() == pvObject )
		return TRUE;

	SObj* psObj = (SObj*)m_mapObjectItem[pvObject];
	if( NULL == psObj )
		return FALSE;

	CProp** ppProp = (CProp**)m_msProp.m_arpProp.GetData();
	INT nCount = m_msProp.m_arpProp.GetSize();
	INT i;
	for( i = 0; i < nCount; i++ )
		if( ppProp[i]->GetObject() == pvObject )
			break;

	if( i == nCount )
		return FALSE;

	ResetPropList();
	m_TabCtrl.DeleteAllItems();

	m_nPropID = psObj->nID;
	m_pvObject = pvObject;
	UpdateObjectSelection();

	if( m_pvObject && NULL == m_pProp )
		return FALSE;

	m_cmbObjectSel.SetSel( psObj->hItem );
	return TRUE;
}

BOOL CPropBox::SelectObject( void* pvObject, BOOL bSelect /*= TRUE*/ ) 
{
	if( bSelect && m_pProp && m_pProp->GetObject() == pvObject )
		return TRUE;

	SObj* psObj = (SObj*)m_mapObjectItem[pvObject];
	if( NULL == psObj )
		return FALSE;

	void* pPrevObj = NULL;
	if( FALSE == bSelect )
	{
		CProp** ppProp = (CProp**)m_msProp.m_arpProp.GetData();
		INT nCount = m_msProp.m_arpProp.GetSize();
		INT i;
		for( i = 0; i < nCount; i++ )
		{
			if( ppProp[i]->GetObject() == pvObject )
				break;

			pPrevObj = ppProp[i]->GetObject();
		}

		if( i == nCount )
			return FALSE;
	}

	ResetPropList( FALSE );
	m_TabCtrl.DeleteAllItems();

	HTREEITEM hItem = ObjectToHTREEITEM( m_pvObject );
	m_cmbObjectSel.SetSel( hItem, bSelect );

	if( FALSE == bSelect )
	{
		m_nPropID = 0;
		m_pvObject = NULL;
		if( pPrevObj )
			SetActiveObject( pPrevObj );
	}
	else
	{
		m_nPropID = psObj->nID;
		m_pvObject = pvObject;
		UpdateObjectSelection();

		if( m_pvObject && NULL == m_pProp )
			return FALSE;
	}

	return TRUE; 
}

// The function sets the given object as current object in the property control.
// The previously selected multiple objects will be deselected.
BOOL CPropBox::SetCurObject( void* pvObject )
{
	if( NULL == pvObject )
	{
		if( m_pvObject )
		{
			ResetPropList();
			m_TabCtrl.DeleteAllItems();

			m_nPropID = 0;
			m_pvObject = NULL;

			m_cmbObjectSel.SetCurSel( NULL );
			m_msProp.DeleteAllProp();
		}

		return TRUE;
	}

	INT nSelectionCount = m_msProp.m_arpProp.GetSize();
	if( m_pvObject == pvObject && nSelectionCount <= 1 )
		return TRUE;

	SObj* psObj = (SObj*)m_mapObjectItem[pvObject];
	if( NULL == psObj )
		return FALSE;

	ResetPropList();
	m_TabCtrl.DeleteAllItems();
	if( nSelectionCount >= 1 )
	{
		// Multiple Props selected
		m_nPropID = 0;
		m_pvObject = NULL;

		m_cmbObjectSel.SetCurSel( NULL );
		m_msProp.DeleteAllProp();
	}

	return SelectObject( pvObject );
}

void CPropBox::UpdateObjectSelection()
{
	if( m_pvObject )
	{
		SPropHandler* psHandler;
		psHandler = GetPropHandler( m_nPropID );
		if( NULL == psHandler )
			return;

		// Create Prop object
		m_pProp = m_msProp.CreateProp( psHandler, FALSE );
		if( NULL == m_pProp )
			return;

		m_pProp->m_pPropCtrl = this;

		// Set Object to Prop
		m_pProp->SetObject( m_pvObject );
		m_msProp.AddProp( m_pProp );

		// Set the current object as selection in Object combo
		HTREEITEM hItem = ObjectToHTREEITEM( m_pvObject );
		m_cmbObjectSel.SetSel( hItem );

		INT nTabCnt = m_pProp->GetTabCount();
		if( 0 == nTabCnt ) 
		{	
			// Create default Tab 'Properties' if count is zero
			m_TabCtrl.InsertItem( 0, _T("Properties") );
			nTabCnt++;
		}
		else	
		{
			// If count greater than zero, get Tab names from Prop object and create
			CString cszText;
			for( INT i = 0; i < nTabCnt; i++ )
			{
				cszText.Empty();
				m_pProp->GetTabText( i, cszText );
				m_TabCtrl.InsertItem( i, cszText );
			}
		}

		// Create Alphabetic Tab is Prop object permits
		if( m_pProp->IsAlphabeticalTab() )
			m_TabCtrl.InsertItem( nTabCnt, _T("Alphabet") );
	}
	else
	{
		// No Object set, create default Tab Properties and 
		// set select none in Object combo
		m_TabCtrl.InsertItem( 0, _T("Properties") );
		m_cmbObjectSel.SetCurSel( NULL );
	}

	// Create Prop Item list and initialize
	UpdatePropList();
}

void CPropBox::UpdatePropList()
{
	m_pPropItemListCtrl->SetAlphatbeticalMode( FALSE );
	if( m_pvObject )
	{
		INT nTab = m_TabCtrl.GetCurSel();
		INT nTabCnt = m_pProp->GetTabCount();
		if( nTab == nTabCnt && m_pProp->IsAlphabeticalTab() )
		{
			m_pProp->CreateAlphabeticPropList();
			m_pPropItemListCtrl->SetAlphatbeticalMode();
		}
		else
		{
			ASSERT( nTab < nTabCnt || (0 == nTabCnt && 0 == nTab) );

			m_pProp->CreatePropList( nTab );
			m_pPropItemListCtrl->m_pPropDlg = m_pProp->GetTabDlg( nTab );
			if( m_pPropItemListCtrl->m_pPropDlg )
			{
				CRect rct;
				GetClientRect( rct );
				LPCTSTR lpszTemplateName = MAKEINTRESOURCE( 3000 );
				m_pPropItemListCtrl->m_pPropDlg->Create( lpszTemplateName, m_pPropItemListCtrl );
				m_pPropItemListCtrl->m_pPropDlg->GetClientRect( rct );
				m_pPropItemListCtrl->m_nDlgCx = rct.Width();
				m_pPropItemListCtrl->m_nDlgCy = rct.Height();
				m_pPropItemListCtrl->ReposDlg();
				m_pPropItemListCtrl->m_pPropDlg->ShowWindow( SW_SHOW );
			}
		}
		
		m_msProp.CreateCommonItemList();
		if( m_nCurPropID )
		{
			if( FALSE == SetCurPropItem( m_nCurPropID ) )
				SetCurPropItemByIndex( 0 );
		}
		else
			SetCurPropItemByIndex( 0 );
	}

	if( NULL == m_pPropItemListCtrl->m_pPropDlg )
	{
		DWORD dwExStyle = GetWindowLong( m_pPropItemListCtrl->m_hWnd, GWL_EXSTYLE );
		if( 0 == (dwExStyle & WS_EX_STATICEDGE) )
		{
			m_pPropItemListCtrl->ModifyStyleEx( 0, WS_EX_STATICEDGE );
			m_pPropItemListCtrl->SetWindowPos( NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED );
		}
	}

	if( m_pProp && NULL == m_pPropItemListCtrl->m_pPropDlg )
		m_pPropItemListCtrl->CreateStaticControl();

	if( m_pProp )
	{
		BOOL bAlphabetical = m_pPropItemListCtrl->GetAlphatbeticalMode();
		HTREEITEM hItem;
		BOOL bFold;
		INT nCount = m_pProp->GetItemListCount();
		SPropItem** ppsItem = m_pProp->GetItemList();
		SPropItem* pParent;
		SPropItem* pPrev;
		for( INT i = 0; i < nCount; i++ )
		{
			pParent = ppsItem[i]->psGroup;
			pPrev = ppsItem[i]->pPrev;
			if( bAlphabetical )
			{
				pParent = NULL;
				pPrev = (SPropItem*)TVI_LAST;
			}

			hItem = m_pPropItemListCtrl->InsertPropItem( *ppsItem[i], pParent, pPrev );
			if( NULL == hItem )
			{
				ASSERT( hItem );		
				break;
			}

			if( OPST_GROUP == ppsItem[i]->psProp->nType )
			{
				bFold = 0 != (OPSF_FOLD & ppsItem[i]->psProp->nFlag);
				if( FALSE == bFold )
					m_pPropItemListCtrl->SetItemState( hItem, TVIS_EXPANDED, TVIS_EXPANDED );					
			}
		}
	}
}

void CPropBox::OnItemSelChange()
{
	CString csz;
	if( m_pProp )
	{
		m_msProp.GetDesc( m_pProp->GetCurItem(), csz );
		m_nCurPropID = m_pProp->GetCurItem()->psProp->nID;
	}

	m_PropDesc.SetString( csz );
	m_pPropItemListCtrl->CreateControl();
}

void CPropBox::OnItemSelChanging()
{
	m_pPropItemListCtrl->UpdateControl();
	m_pPropItemListCtrl->DeleteControl();
}

void CPropBox::OnPropBtn( UINT nID )
{
	m_TabCtrl.SetCurSel( nID - ID_PROP_BTN1  );
	OnTabSelChange( NULL, NULL );
}

void CPropBox::OnPropBtnUI( CCmdUI* pCmdUI )
{
	pCmdUI->Enable();
	if( m_TabCtrl.m_hWnd )
		pCmdUI->SetCheck( (INT)pCmdUI->m_nID == m_TabCtrl.GetCurSel() + ID_PROP_BTN1 );
}

void CPropBox::OnTabSelChange( NMHDR* pNMHDR, LRESULT* plResult )
{
	if( NULL == m_pProp )
		return;

	ResetPropList( FALSE );
	UpdatePropList();
	m_TabCtrl.SetFocus();
}

BOOL CPropBox::UpdatePropItem()
{
	if( m_pProp )
	{
		m_msProp.UpdateText();

		if( CProp::m_pedtProp )
		{
			CString csz;
			SPropItem* pCurItem = m_pProp->GetCurItem();
			m_pProp->GetText( pCurItem, csz );
			CProp::m_pedtProp->SetWindowText( csz );
		}

		m_pPropItemListCtrl->InvalidateRect( NULL );
		return TRUE;
	}

	return FALSE;
}

BOOL CPropBox::SetCurPropItemByIndex( INT nIndex )
{
	if( NULL == m_pProp )
		return FALSE;

	INT nFindIndex;
	SPropItem* psItem = m_pProp->GetItem( m_nCurPropID, &nFindIndex );
	if( psItem && psItem->psProp->nID == m_nCurPropID && 
		nIndex == nFindIndex && m_nCurItemIndex == nFindIndex )
		return TRUE;

	psItem = m_pProp->GetItemAt( nIndex );
	if( NULL == psItem )
		return FALSE;

	OnItemSelChanging();
	m_msProp.SetCurItem( psItem );

	m_nCurItemIndex = nIndex;
	OnItemSelChange();
	return TRUE;
}

BOOL CPropBox::SetCurPropItem( INT nID )
{
	if( NULL == m_pProp )
		return FALSE;

	SPropItem* psItem = m_pProp->GetCurItem();
	/*if( psItem && psItem->psProp->nID == m_nCurPropID )
	{
		INT nFindIndex;
		m_pProp->GetItem( m_nCurPropID, &nFindIndex );
		if( m_nCurItemIndex == nFindIndex )
			return TRUE;
	}*/

	if( nID == m_nCurPropID )
		return TRUE;

	SPropItem** ppsItem = m_pProp->GetItemList();

	// Find prop's item index
	INT nParentIndex;
	INT nItemIndex = m_pProp->GetItemIndex( nID, &nParentIndex );
	if( -2 == nItemIndex ) // Invalid Item Index or NULL Prop Struct
		return FALSE;

	if( -1 == nItemIndex ) // Prop's group not Visible
	{
		ASSERT( OPST_GROUP == ppsItem[nParentIndex]->psProp->nType );

		// Make its group visible
		m_pProp->FoldItemGroup( nParentIndex, FALSE );

		// Find prop's item index again
		nItemIndex = m_pProp->GetItemIndex( nID );
		ASSERT( -1 != nItemIndex );

		OnItemSelChanging();
		m_msProp.SetCurItem( ppsItem[nItemIndex] );
		m_nCurItemIndex = nItemIndex;

		m_pPropItemListCtrl->InvalidateRect( NULL );
		OnItemSelChange();
		return TRUE;
	}	

	// Else already visible
	OnItemSelChanging();
	m_msProp.SetCurItem( ppsItem[nItemIndex] );
	m_nCurItemIndex = nItemIndex;

	m_pPropItemListCtrl->UpdatePropItem( *psItem );
	OnItemSelChange();
	return TRUE;
}

BOOL CPropBox::ExpandPropGroup( INT nIndex, BOOL bExpand /*= TRUE*/ )
{
	SPropItem* psItem = m_pProp->GetItemAt( nIndex );
	if( NULL == psItem || OPST_GROUP != psItem->psProp->nType )
		return FALSE;

	if( bExpand && OPSF_FOLD & psItem->psProp->nFlag )
		return TRUE;	// Already expand
	else if( FALSE == bExpand && 0 == (OPSF_FOLD & psItem->psProp->nFlag) )
		return TRUE;	// Already folded

	OnItemSelChanging();
	m_msProp.SetCurItem( psItem );
	m_nCurItemIndex = nIndex;
	m_pProp->FoldItemGroup( nIndex, bExpand );

	psItem = m_pProp->GetCurItem();
	m_pPropItemListCtrl->ReposStaticControl( psItem );

	OnItemSelChange();
	return TRUE;
}
