#include "stdafx.h"
#include "ElementProp.h"

#include <prop\PropBox.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const INT cnElementID = 100;
static CElementProp	gs_ElementProp;

static CProp* _CreatePropHandler( INT nID )
{
	if( cnElementID == nID )
		return new CElementProp;

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_LINK( CElementProp, CGEventTarget )
	ON_EVT_PHASE_NODE_LINK_CHANGE( CGMutationEvent::DOMAttrModified, CGEvent::AT_TARGET, OnAttrModifiedEvent )
END_EVENT_LINK()

CElementProp::CElementProp() 
{
	m_pElement = NULL; 

	SPropHandler stmp = { _CreatePropHandler, cnElementID };
	CPropBox::AddPropHandler( &stmp );
}

CElementProp::~CElementProp() 
{
	if( m_pElement )
	{
		m_pElement->RemoveEventListener( CGMutationEvent::DOMAttrModified, *this, FALSE );
		m_pElement->Release();
	}
}

void* CElementProp::GetObject() {
	return m_pElement; }

void CElementProp::SetObject( void* pvObject ) 
{
	m_pElement = (CGIElement*)pvObject; 

	if( m_pElement )
	{
		m_pElement->AddRef();
		m_pElement->AddEventListener( CGMutationEvent::DOMAttrModified, *this, FALSE );
	}
}

INT g_nID;
void CElementProp::AddAttribute( CGIAttrGroup& rGroup )
{
	SProp sProp = { g_nID++, NULL, OPST_GROUP };
	sProp.dwItemData = (DWORD)(CGINode*)&rGroup;
	m_arrsProp.Add( sProp );

	CString cszName;
	CGIAttrGroup* pAttrGroup;
	CGIAttr* pAttr;
	CGINode* pNode = rGroup.GetFirst();
	if( pNode )
	{
		cszName = pNode->GetNodeName();
		int i = 0;
	}

	while( pNode )
	{
		if( pNode->IsDerivedFrom( CGIAttr::GetClassType() ) )
		{
			cszName = pNode->GetNodeName();
			pAttr = (CGIAttr*)pNode;
			sProp.Set( g_nID++, NULL, OPST_ITEM, 0, OPCT_EDIT | OPCT_BTN, 0, OPIDT_TEXT );
			sProp.dwItemData = (DWORD)pNode;
			m_arrsProp.Add( sProp );
		}
		else if( pNode->IsDerivedFrom( CGIAttrGroup::GetClassType() ) )
		{
			pAttrGroup = (CGIAttrGroup*)pNode;
			AddAttribute( *pAttrGroup );
		}

		pNode = pNode->GetNext();
	}
}

SProp* CElementProp::GetElementPropList()
{
	INT nCount = m_arrsProp.GetSize();
	if( nCount )
		return m_arrsProp.GetData();

	if( NULL == m_pElement )
		return NULL;
	
	CGINamedAttrMap* pmapAttr =	(CGINamedAttrMap*)m_pElement->GetAttributes();
	ASSERT( pmapAttr );

	g_nID = 0;
	CGIAttrGroup& rAttrGroup = pmapAttr->GetRootGroup();
	CGINode* pRootNode = rAttrGroup.GetFirst();
	while( pRootNode )
	{
		if( pRootNode && pRootNode->IsDerivedFrom( CGIAttrGroup::GetClassType() ) )
		{
			CGIAttrGroup& rRootGroup = *((CGIAttrGroup*)pRootNode);
			AddAttribute( rRootGroup );
		}

		pRootNode = pRootNode->GetNext();
	}

	return m_arrsProp.GetData();
}

INT CElementProp::GetPropCount( INT nTab /*= -1*/ )
{
	if( -1 == nTab )
		return m_nPropListCnt;

	switch( nTab )
	{
	case 0:
		return m_arrsProp.GetSize();

	case 1:
		return 0;
	}

	ASSERT( 0 );
	return -1;
}

SProp* CElementProp::GetPropList( INT nTab /*= -1*/ )
{
	if( -1 == nTab )
		return m_psPropList;

	switch( nTab )
	{
	case 0:
		return GetElementPropList();

	case 1:
		return NULL;
	}

	ASSERT( NULL );
	return NULL;
}

BOOL CElementProp::IsAlphabeticalTab() {
	return TRUE; }

INT CElementProp::GetTabCount() {
	return 1; }

BOOL CElementProp::GetLabel( SPropItem* psItem, CString& rcszName )
{
	if( CProp::GetLabel( psItem, rcszName ) )
		return TRUE;

	CGINode* pNode = (CGINode*)psItem->psProp->dwItemData;
	ASSERT( pNode );
	rcszName = pNode->GetName();
	
	return TRUE;
}

BOOL CElementProp::GetDesc( SPropItem* psItem, CString& rcszDesc )
{
	if( CProp::GetDesc( psItem, rcszDesc ) )
		return TRUE;

	CGINode* pNode = (CGINode*)psItem->psProp->dwItemData;
	ASSERT( pNode );
	rcszDesc = pNode->GetName();
	
	return FALSE;
}

BOOL CElementProp::GetText( SPropItem* psItem, CString& rcszText )
{
	if( CProp::GetText( psItem, rcszText ) )
		return TRUE;

	if( NULL == m_pElement )
		return FALSE;
	
	if( OPST_ITEM == psItem->psProp->nType )
	{
		CGIAttr* pAttr = (CGIAttr*)psItem->psProp->dwItemData;
		pAttr->Get( rcszText );
		return TRUE;
	}
	
	if( OPST_ITEM == psItem->psProp->nType )
	{
		CGIAttrGroup* pAttrGroup = (CGIAttrGroup*)psItem->psProp->dwItemData;
		return TRUE;
	}

	return FALSE;
}

BOOL CElementProp::UpdateTextItem( SPropItem* psItem, PTCHAR ptszText )
{
	if( CProp::UpdateTextItem( psItem, ptszText ) )
		return TRUE;

	if( OPST_ITEM == psItem->psProp->nType )
	{
		CGIAttr* pAttr = (CGIAttr*)psItem->psProp->dwItemData;
		pAttr->Set( ptszText );
		return TRUE;
	}

	return FALSE;
}

void CElementProp::OnAttrModifiedEvent( CGMutationEvent& rEvent )
{
	if( m_pPropCtrl )
		m_pPropCtrl->UpdatePropItem();
}