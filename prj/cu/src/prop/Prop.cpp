#include "stdafx.h"
#include "Prop.h"
#include "PsPropMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define PC_BEGIN_
CPropEdit*			CProp::m_pedtProp;
CPropComboBox*		CProp::m_pcmbProp;
CPropMSComboBox*	CProp::m_pcmbMSProp;
CPropBtn*			CProp::m_pbtnProp;
CWnd*				CProp::m_pwnddynProp;

///////////////////////////////////////////////////////////////////////////////////////////////////
// CProp
BEGIN_PB_PROP_MAP(CProp,CProp)
END_PB_PROP_MAP()

BEGIN_MESSAGE_MAP(CProp,CWnd)
END_MESSAGE_MAP()

CProp::CProp()
{
	m_psPropList = NULL;
	m_nPropListCnt = 0;
	m_parsItem = NULL;

	m_psCurItem = NULL;
	m_pPropCtrl = NULL;
}

CProp::~CProp()
{
	DeleteUserItem();
	DeleteItemList();
}

// Prop. ctrl will call to get Object pointer associated with this
// property. Override this function to return the same.
void* CProp::GetObject()
{
	// Override this functions
	ASSERT( FALSE );
	return NULL;
}

// Prop. ctrl will call to set object pointer of the property
void CProp::SetObject( void* pvObject )
{
	// Override this functions
	ASSERT( FALSE );
}

// Returns whether alphabetical order tab is needed or not. 
// On creating tabs, Prop. ctrl will call this function to decide 
// whether alphabetic tab needs or not
BOOL CProp::IsAlphabeticalTab() {
	return FALSE; }

// Creates a alphabetic order property list of current non-alphabetic tab.
void CProp::CreateAlphabeticPropList()
{
	INT nCount = GetAllItemListCount();
	if( 0 == nCount )
		return;

	m_arpItem.RemoveAll();

	// Get all items
	SPropItem** ppsItem = GetAllItemList();
	INT i;
	for( i = 0; i < nCount; i++ )
	{
		if( OPST_GROUP == ppsItem[i]->psProp->nType )
			continue;

		m_arpItem.Add( ppsItem[i] );
		ppsItem[i]->pParent = NULL;
	}

	// Sort items with name
	nCount = m_arpItem.GetSize();
	INT j, nCountM1 = nCount - 1;
	SPropItem* psItem;
	ppsItem = (SPropItem**)m_arpItem.GetData();
	CString cszText1, cszText2, cszText;
	for( i = 0; i < nCountM1; i++ )
	{
		for( j = i + 1; j < nCount; j++ )
		{
			GetLabel( ppsItem[i], cszText1 );
			GetLabel( ppsItem[j], cszText2 );
			if( cszText1.CompareNoCase( cszText2 ) > 0 )
			{
				psItem = ppsItem[i];
				ppsItem[i] = ppsItem[j];
				ppsItem[j] = psItem;
			}
		}
	}

	// Find items with same name and mark by setting pParent != NULL
	for( i = 0; i < nCountM1; i++ )
	{
		GetLabel( ppsItem[i], cszText1 );
		GetLabel( ppsItem[i + 1], cszText2 );
		if( 0 == cszText1.CompareNoCase( cszText2 ) )
		{
			ppsItem[i]->pParent = ppsItem[i]->psGroup;
			ppsItem[i + 1]->pParent = ppsItem[i + 1]->psGroup;
		}
	}

	// Sort items again with name and group name if necessary
	for( i = 0; i < nCountM1; i++ )
	{
		for( INT j = i + 1; j < nCount; j++ )
		{
			GetLabel( ppsItem[i], cszText1 );
			if( ppsItem[i]->pParent )
			{
				GetLabel( ppsItem[i]->pParent, cszText );
				cszText1 += _T(":") + cszText;
			}

			GetLabel( ppsItem[j], cszText2 );
			if( ppsItem[j]->pParent )
			{
				GetLabel( ppsItem[j]->pParent, cszText );
				cszText2 += _T(":") + cszText;
			}

			if( cszText1.CompareNoCase( cszText2 ) > 0 )
			{
				psItem = ppsItem[i];
				ppsItem[i] = ppsItem[j];
				ppsItem[j] = psItem;
			}
		}
	}

	for( i = 0; i < nCount; i++ )
	{
		///?	ppsItem[i]->pParent = NULL;
		ppsItem[i]->pNext = ppsItem[i + 1];
		if( i > 0 )
			ppsItem[i]->pPrev = NULL;
		else
			ppsItem[i]->pPrev = ppsItem[i - 1];
	}

	ppsItem[i - 1]->pNext = NULL;
}

// Creates a property list of nTab
void CProp::CreatePropList( INT nTab /*= -1*/ )
{
	DeleteUserItem();

	if( -1 == nTab )
	{
		m_nPropListCnt = 0;
		m_psPropList = NULL;
	}
	else
	{
		m_psPropList = GetPropList( nTab );
		m_nPropListCnt = GetPropCount( nTab );
	}

	CreateAllItemList();
	AddUserItem();
	InitItemStruct();
	CreateItemList();
}

// Returns property list count of current tab if nTab is -1 or
// nTab'th 
INT CProp::GetPropCount( INT nTab /*= -1*/ )
{
	// Override this functions
	ASSERT( FALSE );
	return 0;
}

// Returns property list of current tab if nTab is -1 or
// nTab'th 
SProp* CProp::GetPropList( INT nTab /*= -1*/ )
{
	// Override this functions
	ASSERT( FALSE );
	return 0;
}

// Returns tab count
INT CProp::GetTabCount()
{
	return 0;
}

// Returns name of nTab
void CProp::GetTabText( INT nTab, CString& rcszText )
{
	switch( nTab )
	{
	case 0:
		rcszText = _T("Properties");
		break;

	case 1:
		rcszText = _T("System");
		break;

	case 2:
		rcszText = _T("Alphabetic");
		break;

	default:
		ASSERT( FALSE );
	}
}

// Returns Dialog pointer of nTab
CDialog* CProp::GetTabDlg( INT nTab )
{
	return NULL;
}

// Folds or expands prop. group having specified ID
INT CProp::FoldPropGroup( INT nID, BOOL bFold /*= TRUE*/ )
{
	INT nIndex = GetItemIndex( nID );
	if( nIndex < 0 )
		return -1;

	return FoldItemGroup( nIndex, bFold );
}

// Folds or expands prop. item having specified index
INT CProp::FoldItemGroup( INT nIndex, BOOL bFold /*= TRUE*/ )
{
	INT i, nCount = GetItemListCount();
	if( 0 == nCount || nIndex < 0 || nIndex >= nCount )
		return 0;

	SPropItem** ppsItem = GetItemList();
	SPropItem* psItem = ppsItem[nIndex];
	if( bFold )
	{
		if( OPSF_FOLD & psItem->psProp->nFlag )
			return nCount; // Already folded

		psItem->psProp->nFlag |= OPSF_FOLD;
		for( i = ++nIndex; i < nCount; i++ )
			if( OPST_GROUP == ppsItem[i]->psProp->nType )
				break;

		m_arpItem.RemoveAt( nIndex, i - nIndex );
		nCount = GetItemListCount();
		return nCount;
	}

	if( 0 == (OPSF_FOLD & psItem->psProp->nFlag) )
		return nCount; // Already expanded

	psItem->psProp->nFlag &= ~OPSF_FOLD;
	if( psItem->nChildCount > 0 )
	{
		INT nSrcIndex = -1;
		ppsItem = GetAllItemList();
		INT nCount = GetAllItemListCount();
		for( i = 0; i < nCount; i++ )
			if( ppsItem[i] == psItem )
			{
				nSrcIndex = i;
				break;
			}

		ASSERT( -1 != nSrcIndex );
		nIndex++;
		nSrcIndex++;
		for( i = 0; i < psItem->nChildCount; i++, nSrcIndex )
			m_arpItem.InsertAt( nIndex++, ppsItem[nSrcIndex++] );
	}

	nCount = GetItemListCount();
	return nCount;
}

///?x testing variable
static SProp _gs_sRectSysProp[] =
{
	{IDOPSG_GENERAL, NULL, OPST_GROUP, OPSF_FOLD},
	 {IDOPSI_NAME, NULL, OPST_ITEM, 0, OPCT_EDIT | OPCT_BTN, 0, OPIDT_TEXT, OPIDF_DATAPTR},
};

// Adds all user prop. items here
void CProp::AddUserItem()
{
	return;
	SProp* psProp = &_gs_sRectSysProp[0];
	SPropItem* psItem = new SPropItem;
	psItem->nFlag = OPIF_USER_ITEM;
	psItem->psProp = psProp;
	GetText( psItem, *psItem->pcszText );
	psItem->bText = TRUE;
	m_arpAllItem.Add( psItem );

	psProp = &_gs_sRectSysProp[1];
	psItem = new SPropItem;
	psItem->nFlag = OPIF_USER_ITEM;
	psItem->psProp = psProp;
	GetText( psItem, *psItem->pcszText );
	psItem->bText = TRUE;
	m_arpAllItem.Add( psItem );
}

// Deletes the user prop. items which were created by AddDynItem()
void CProp::DeleteUserItem()
{
	return;
	INT nCount = m_arpAllItem.GetSize();
	SPropItem* psItem;
	for( INT i = nCount - 1; i >= 0; i-- )
	{
		psItem = (SPropItem*)m_arpAllItem.GetAt( i );
		if( psItem->psProp->nFlag & OPSF_USER_ITEM )
		{
			delete psItem->psProp;
			psItem->psProp = NULL;
		}

		if( psItem->nFlag & OPIF_USER_ITEM )
		{
			delete psItem;
			m_arpAllItem.RemoveAt( i );
		}
	}
}

// Initialize all Prop. items structure if any needed like
// initialization of data pointer member
void CProp::InitItemStruct()
{
	INT nCount = GetAllItemListCount();
	SPropItem** ppsItem = GetAllItemList();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppsItem[i]->psProp->nDataFlag & OPIDF_DATAPTR )
			InitItemDataPtr( ppsItem[i], OPIDF_DATAPTR );

		InitItemStruct( ppsItem[i], ppsItem[i]->psProp->nDataFlag );
	}
}

// Initialize Prop. item structure data pointer member
BOOL CProp::InitItemDataPtr( SPropItem* psItem, INT nFlag )
{
	// Override this function
	ASSERT( FALSE );
	return FALSE;
}

// Initialize Prop. item structure if any needed like
// initialization of data pointer member
void CProp::InitItemStruct( SPropItem* psItem, INT nFlag )
{}

// Retrieves index to Prop. item of nID. It also retrieves parent index if 
// it have a parent into pnParentIndex.
INT CProp::GetItemIndex( INT nID, INT* pnParentIndex /*= NULL*/ )
{
	INT nParentIndex;
	if( NULL == pnParentIndex )
		pnParentIndex = &nParentIndex;

	if( NULL == m_psPropList )
		return -2;

	SPropItem** ppsItem = GetItemList();
	INT nCount = GetItemListCount();
	INT i;
	for( i = 0; i < nCount; i++ )
		if( ppsItem[i]->psProp->nID == nID )
			return i;

	// Item not found. 
	// Find its group index
	SPropItem** ppsAllItem = GetAllItemList();
	INT nAllItemCnt = GetAllItemListCount();
	INT nLastGroup = -1;
	for( i = 0; i < nAllItemCnt; i++ )
	{
		if( OPST_GROUP == ppsAllItem[i]->psProp->nType )
			nLastGroup = i;

		if( ppsAllItem[i]->psProp->nID == nID )
		{
			if( -1 == nLastGroup )
				return -2; // Still not found
			
			// find group index with ID
			nID = ppsAllItem[nLastGroup]->psProp->nID;
			for( INT n = 0; n < nCount; n++ )
				if( ppsItem[i]->psProp->nID == nID )
				{
					*pnParentIndex = n;
					return n;
				}

			break; // Still not found
		}
	}

	// Still not found
	*pnParentIndex = -1;
	return -2;
}

// Creates all prop. items list and adds m_arpAllItem array.
// The array will have all prop. items list whether visible or not in the prop
INT CProp::CreateAllItemList()
{
	if( NULL == m_psPropList )
		return 0;

	m_arpAllItem.RemoveAll();
	DeleteItemList();
	INT nCount = GetPropCount();
	VERIFY( m_parsItem = new SPropItem[nCount] );
	for( INT i = 0; i < nCount; i++ )
	{
		m_parsItem[i].psProp = &m_psPropList[i];
		GetText( &m_parsItem[i], *m_parsItem[i].pcszText );
		m_parsItem[i].bText = TRUE;
		m_arpAllItem.Add( &m_parsItem[i] );
	}

///?x
//	m_psItem[0].nCy = 25;
//	m_psItem[1].nCy = 8;
//	m_psItem[5].nCy = 25;
	return nCount;
}

// Creates prop. items list of visible in the current tab and adds m_arpItem array.
INT CProp::CreateItemList()
{
	if( NULL == m_psPropList )
		return 0;

	BOOL bFold = FALSE;
	INT nVisibleCnt = 0;
	INT nLastGroup = -1;

	INT nCount = GetAllItemListCount();
	SPropItem** ppsItem = GetAllItemList();

	// Initialize Group pointer
	SPropItem* psLastGroup = NULL;
	INT i;
	for( i = 0; i < nCount; i++ )
	{
		if( OPST_GROUP == ppsItem[i]->psProp->nType )
		{
			psLastGroup = ppsItem[i];
			ppsItem[i]->psGroup = NULL;
		}
		else
			ppsItem[i]->psGroup = psLastGroup;
	}

	// Initialize Item Previous, Next and Parent link and Item Count
	psLastGroup = NULL;
	for( i = 0; i < nCount; i++ )
	{
		if( OPST_GROUP == ppsItem[i]->psProp->nType )
		{
			ppsItem[i]->pParent = NULL;
			ppsItem[i]->pPrev = psLastGroup;

			// Atleast one group found
			if( -1 != nLastGroup )
			{
				ppsItem[nLastGroup]->pNext = psLastGroup;
				ppsItem[nLastGroup]->nChildCount = i - nLastGroup - 1;
			}

			nLastGroup = i;
			psLastGroup = ppsItem[i];
			bFold = 0 != (OPSF_FOLD & ppsItem[i]->psProp->nFlag);
			if( i > 0 )
				ppsItem[i - 1]->pNext = NULL;	// Prev child next is NULL
		}
		else
		{
			ppsItem[i]->pParent = psLastGroup;
			ppsItem[i]->nChildCount = 0;
			ppsItem[i]->pNext = ppsItem[i + 1];
			if( i > 0 && OPST_GROUP == ppsItem[i - 1]->psProp->nType )
				ppsItem[i]->pPrev = NULL;
			else
				ppsItem[i]->pPrev = ppsItem[i - 1];
		}

		if( OPST_GROUP == ppsItem[i]->psProp->nType || FALSE == bFold )
		{
			m_arpItem.Add( ppsItem[i] );
			nVisibleCnt++;
		}
	}

	if( i > 0 )
		ppsItem[i - 1]->pNext = NULL;	// Prev child next is NULL

	if( -1 != nLastGroup )
	{
		ppsItem[nLastGroup]->nChildCount = i - nLastGroup - 1;
		ppsItem[nLastGroup]->pNext = NULL; // Last group next is NULL
	}

	return nVisibleCnt;
}

// Deletes the prop. items structures
void CProp::DeleteItemList()
{
	if( m_parsItem )
	{
		delete[] m_parsItem;
		m_parsItem = NULL;
	}

	m_arpItem.RemoveAll();
}

// Retrieves a Prop. item at the given index.
SPropItem* CProp::GetItemAt( INT nIndex )
{
	INT nCount = GetItemListCount();
	if( 0 == nCount || nIndex < 0 || nIndex >= nCount )
		return NULL;

	SPropItem** ppsItem = GetItemList();
	return ppsItem[nIndex];
}

// Retrieves a Prop. item of the given ID. It also retrieves the 
// index of it.
SPropItem* CProp::GetItem( INT nID, INT* pnIndex /*= NULL*/ )
{
	if( pnIndex )
		*pnIndex = 0;

	INT nCount = GetItemListCount();
	SPropItem** ppsItem = GetItemList();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppsItem[i]->psProp->nID == nID )
		{
			if( pnIndex )
				*pnIndex = i;

			return ppsItem[i];
		}
	}

	return NULL;
}

// Changes the current prop. item. This function can be 
// overrided in derived class to set same prop. item to 
// child prop. object in case of multiple selection
void CProp::SetCurItem( SPropItem* psItem ) {
	m_psCurItem = psItem; }

// The function creates a prop. edit control for specified style and location, It can be
// overrided to create own edit control.
CPropEdit* CProp::CreatePropEdit( SPropItem* psItem, DWORD dwStyle, CRect rct, CWnd* pParent, INT nID )
{
	CPropEdit* pEdit;
	VERIFY( pEdit = new CPropEdit );
	if( NULL == pEdit )
		return NULL;

	if( FALSE == pEdit->Create( dwStyle, rct, pParent, nID ) )
	{
		delete pEdit;
		return NULL;
	}

	return pEdit;
}

// The function creates a prop. button control for specified style and location, It can be
// overrided to create own button control.
CPropBtn* CProp::CreatePropBtn( SPropItem* psItem, PTCHAR ptszCaption, DWORD dwStyle, CRect rct, CWnd* pParent, INT nID )
{
	CPropBtn* pBtn;
	VERIFY( pBtn = new CPropBtn );
	if( NULL == pBtn )
		return NULL;

	if( FALSE == pBtn->Create( ptszCaption, dwStyle, rct, pParent, nID ) )
	{
		delete pBtn;
		return NULL;
	}

	return pBtn;
}

// The function creates a prop. combo control for specified style and location, It can be
// overrided to create own combo control.
CPropMSComboBox* CProp::CreatePropCombo( SPropItem* psItem, INT nCtrlCy, DWORD dwStyle, CRect rct, CWnd* pParent, INT nID )
{
	CPropMSComboBox* pCombo;
	VERIFY( pCombo = new CPropMSComboBox );
	if( NULL == pCombo )
		return NULL;

	pCombo->SetControlHeight( nCtrlCy );
	if( FALSE == pCombo->Create( dwStyle, rct, pParent, nID ) )
	{
		delete pCombo;
		return NULL;
	}

	return pCombo;
}

// The function can be used to add dynamic prop. item control for 
// the specified prop. item
void CProp::CreateDynItemCtrl( SPropItem* psItem, CWnd* pParent, CRect rct )
{
	//[/ TEST: Code
	VERIFY( CProp::m_pedtProp = new CPropEdit );
	VERIFY( CProp::m_pedtProp->Create( WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_WANTRETURN,
		rct, this, 200 ) );

	CProp::m_pedtProp->SetMaxLength( 5 );
	CProp::m_pedtProp->SetDataType( OPIDT_HEX );

	CFont fnt;
	fnt.Attach( (HFONT)GetStockObject( DEFAULT_GUI_FONT ) );
	CProp::m_pedtProp->SetFont( &fnt, FALSE );
	fnt.Detach();

	CString csz;
	GetText( psItem, csz );
	CProp::m_pedtProp->SetWindowText( csz );
	CProp::m_pedtProp->SetSel( 0, -1 );
	m_pwnddynProp = CProp::m_pedtProp;
	CProp::m_pedtProp = NULL;
	//]/ TEST: Code
}

// The function can be used to delete dynamic prop. item control for 
// the specified prop. item which was created in AddDynItemCtrl()
void CProp::DeleteDynItemCtrl( SPropItem* psItem )
{
	if( m_pwnddynProp )
	{
		delete m_pwnddynProp;
		m_pwnddynProp = NULL;
	}
}

///?x
CButton* g_pBtn;
CComboBox* g_pCmb;
void CProp::CreateStaticCtrl( SPropItem* psItem, CWnd* pParent, CRect rct )
{
	if( NULL == g_pCmb )
	{
		g_pCmb = new CComboBox;
		g_pCmb->Create( WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST, rct, pParent, 200 );
	}
}

void CProp::DeleteStaticCtrl( SPropItem* psItem )
{
	if( g_pCmb )
	{
		delete g_pCmb;
		g_pCmb = NULL;
	}
}

void CProp::ShowStaticCtrl( SPropItem* psItem, BOOL bShow /*= TRUE*/ )
{
	if( g_pCmb )
		g_pCmb->ShowWindow( bShow ?SW_SHOW :SW_HIDE );
}

void CProp::MoveStaticCtrl( SPropItem* psItem, CRect rct )
{
	if( g_pCmb )
		g_pCmb->MoveWindow( rct );
}

void CProp::UpdateText()
{
	INT nCount = GetAllItemListCount();
	SPropItem** ppsItem = GetAllItemList();
	for( INT i = 0; i < nCount; i++ )
	{
		ppsItem[i]->bText = FALSE;
		GetText( ppsItem[i], *ppsItem[i]->pcszText );
		ppsItem[i]->bText = TRUE;
	}
}

void CProp::UpdateText( INT nID )
{
	SPropItem* psItem = GetItem( nID );
	if( NULL == psItem )
		return;

	psItem->bText = FALSE;
	GetText( psItem, *psItem->pcszText );
	psItem->bText = TRUE;
}

HINSTANCE CProp::GetResourceHandle()
{
	return NULL;
}

BOOL CProp::GetResourceString( INT nID, CString& rcszString, BOOL bLocal /*= FALSE*/ )
{
	INT nBase = -IDOPSG_GENERAL + 1;
	HINSTANCE hInst = AfxGetResourceHandle();
	if( bLocal )
	{
		hInst = GetResourceHandle();
		nBase = 65536;
	}

	if( NULL == hInst )
		return FALSE;

	if( 0 == LoadString( hInst, nID + nBase, rcszString.GetBuffer( 256 ), 255 ) )
		return FALSE;

	rcszString.ReleaseBuffer();
	return TRUE;
}

void CProp::ParseLabelString( CString& rcszString )
{
	INT nPos = rcszString.Find( _T('\n') );

	// No Desc, return as it is
	if( -1 == nPos )
		return;

	rcszString.ReleaseBuffer( nPos );
}

void CProp::ParseDescString( CString& rcszString )
{
	INT nPos = rcszString.Find( _T('\n') );

	// No Desc, return empty
	if( -1 == nPos )
	{
		rcszString.Empty();
		return;
	}

	CString csz = rcszString.Right( rcszString.GetLength() - nPos - 1 );
	rcszString = csz;
}

static BOOL _GetItemResouceString( SPropItem* psItem, CString& rcszName, CProp* pProp )
{
	if( (OPSF_LABEL_ID | OPSF_LABEL_IDLOCAL) & psItem->psProp->nFlag )
	{
		INT nID;
		CString csz;
		if( psItem->psProp->ptszLabel )
			nID = (INT)psItem->psProp->ptszLabel;
		else
			nID = psItem->psProp->nID;

		if( FALSE == pProp->GetResourceString( nID, csz, 0 != (OPSF_LABEL_IDLOCAL & psItem->psProp->nFlag) ) )
			return FALSE;

		rcszName = csz;
		return TRUE;
	}

	if( psItem->psProp->ptszLabel )
	{
		rcszName = psItem->psProp->ptszLabel;
		return TRUE;
	}

	return FALSE;
}

BOOL CProp::GetLabel( SPropItem* psItem, CString& rcszName )
{
	ASSERT( psItem );

	if( _GetItemResouceString( psItem, rcszName, this ) )
	{
		ParseLabelString( rcszName );
		return TRUE;
	}

	switch( psItem->psProp->nID )
	{
	case IDOPSG_GENERAL:
		rcszName = _T("General");
		return TRUE;

	case IDOPSG_MORE:
		rcszName = _T("More");
		return TRUE;

	case IDOPSI_NAME:
		rcszName = _T("Name");
		return TRUE;
	}

	return FALSE;
}

BOOL CProp::GetDesc( SPropItem* psItem, CString& rcszDesc )
{
	ASSERT( psItem );

	if( _GetItemResouceString( psItem, rcszDesc, this ) )
	{
		ParseDescString( rcszDesc );
		return TRUE;
	}

	switch( psItem->psProp->nID )
	{
	case IDOPSI_NAME:
		rcszDesc = _T("Specifies the name of object");
		return TRUE;
	}

	return FALSE;
}

BOOL CProp::GetText( SPropItem* psItem, CString& rcszText )
{
	ASSERT( psItem );
	
	if( psItem->bText )
	{
		// Return cache Text
		rcszText = *psItem->pcszText;
		return TRUE;
	}

	return FALSE;
}

BOOL CProp::EditChange( SPropItem* psItem )
{
	return FALSE;
}

#define PB_IS_ERR( v, f ) (TRUE != (v = f) && FALSE != v )
BOOL CProp::UpdateItem( SPropItem* psItem )
{
	ASSERT( psItem );

	INT nResult, nDataType = psItem->psProp->nDataType;
	if( nDataType >= OPIDT_D_FIRST && nDataType <= OPIDT_D_LAST )
	{
		CString cszText = m_pedtProp->GetText();
		PTCHAR ptszText = (PTCHAR)(LPCTSTR)cszText;
		nResult = SendPropMsg( PBM_DDT_CHECK, nDataType, psItem->psProp->nID, (UINT)psItem, (UINT)ptszText, (UINT)&nDataType );
		if( TRUE != nResult && FALSE != nResult )
			return nResult;

		//if( PB_IS_ERR( nResult, SendPropMsg( PBM_DDT_CHECK, nDataType, psItem->psProp->nID, (UINT)psItem, (UINT)ptszText, (UINT)&nDataType ) ) )
		//	return nResult;
	}

	switch( nDataType )
	{
	case OPIDT_TEXT:{
		CString cszText = m_pedtProp->GetText();
		nResult = UpdateTextItem( psItem, (PTCHAR)(LPCTSTR)cszText );
		}break;

	case OPIDT_INT: {
		INT nInt = m_pedtProp->GetInt();
		nResult = UpdateIntItem( psItem, nInt );
		}break;

	case OPIDT_FLOAT:{
		FLOAT fFloat = m_pedtProp->GetFloat();
		nResult = UpdateFloatItem( psItem, fFloat );
		}break;

	case OPIDT_DOUBLE:{
		DOUBLE fDouble = m_pedtProp->GetDouble();
		nResult = UpdateDoubleItem( psItem, fDouble );
		}break;

	default:
		return FALSE;
	}

	return nResult;
}

BOOL CProp::UpdateTextItem( SPropItem* psItem, PTCHAR ptszText )
{
	INT nResult = SendPropMsg( PBM_UPDATEITEM_FLOAT, 0, psItem->psProp->nID, (UINT)psItem, (UINT)ptszText );
	if( nResult )
		return nResult;

	if( psItem->psProp->nDataFlag & OPIDF_DATAPTR )
	{
		lstrcpy( (PTCHAR)psItem->pData, ptszText );
		return TRUE;
	}

	return FALSE;
}

BOOL CProp::UpdateIntItem( SPropItem* psItem, INT nInt )
{
	INT nResult = SendPropMsg( PBM_UPDATEITEM_FLOAT, 0, psItem->psProp->nID, (UINT)psItem, (UINT)&nInt );
	if( nResult )
		return nResult;

	if( psItem->psProp->nDataFlag & OPIDF_DATAPTR )
	{
		*((INT*)psItem->pData) = nInt;
		return TRUE;
	}

	return FALSE;
}

BOOL CProp::UpdateFloatItem( SPropItem* psItem, FLOAT fFloat )
{
	INT nResult = SendPropMsg( PBM_UPDATEITEM_FLOAT, 0, psItem->psProp->nID, (UINT)psItem, (UINT)&fFloat );
	if( nResult )
		return nResult;

	if( psItem->psProp->nDataFlag & OPIDF_DATAPTR )
	{
		*((FLOAT*)psItem->pData) = fFloat;
		return TRUE;
	}

	return FALSE;
}

BOOL CProp::UpdateDoubleItem( SPropItem* psItem, DOUBLE dfDouble )
{
	INT nResult = SendPropMsg( PBM_UPDATEITEM_DOUBLE, 0, psItem->psProp->nID, (UINT)psItem, (UINT)&dfDouble );
	if( nResult )
		return nResult;

	if( psItem->psProp->nDataFlag & OPIDF_DATAPTR )
	{
		*((DOUBLE*)psItem->pData) = dfDouble;
		return TRUE;
	}

	return FALSE;
}

BOOL CProp::BtnClick( SPropItem* psItem )
{
	if( psItem->psProp->nDataType >= OPIDT_D_FIRST && 
		psItem->psProp->nDataType <= OPIDT_D_LAST )
	{
		INT nResult = SendPropMsg( PBM_DDT_BTNCLICK, psItem->psProp->nDataType, psItem->psProp->nID, (UINT)psItem );
		if( nResult )
			return nResult;
	}

	return FALSE;
}

BOOL CProp::FillCombo( SPropItem* psItem )
{
	CProp::m_pcmbMSProp->AddString( _T("List1") );
	CProp::m_pcmbMSProp->AddString( _T("List2") );
	CProp::m_pcmbMSProp->AddString( _T("List3") );
	CProp::m_pcmbMSProp->AddString( _T("List4") );
	return FALSE;
}

BOOL CProp::SetComboSel( SPropItem* psItem ) {
	return FALSE; }

BOOL CProp::ComboSelChange( SPropItem* psItem, CMSComboBox::NMSELCHANGE* pNotifyStruct, LRESULT* plResult ) {
	return FALSE; }

BOOL CProp::UpdateCombo( SPropItem* psItem ) {
	return FALSE; }

BOOL CProp::ComboCancel( SPropItem* psItem ) {
	return FALSE; }
