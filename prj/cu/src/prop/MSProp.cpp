#include "stdafx.h"
#include "PropBox.h"
#include "PsPropMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMultiSelProp::CMultiSelProp( CPropBox& rPropCtrl )
 : m_rPropCtrl( rPropCtrl )
{}

CMultiSelProp::~CMultiSelProp()
{}

void CMultiSelProp::SetCurItem( SPropItem* psItem )
{
	SPropItem* psFindItem;

	// Set the given SPropItem to all Prop
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		psFindItem = ppProp[i]->GetItem( psItem->psProp->nID );
		ppProp[i]->SetCurItem( psFindItem );
	}
}

CProp* CMultiSelProp::CreateProp( SPropHandler* psHandler, BOOL bAdd /*= TRUE*/ )
{
	CProp* pProp = (*psHandler->pfnPropHandler)( psHandler->nID );
	if( NULL == pProp )
		return NULL;

	// If wnd creation fails, delete object and set NULL
	if( FALSE == pProp->Create( NULL, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 
								CRect( -1, -1, 0, 0 ), m_rPropCtrl.m_pPropItemListCtrl, 
								3000 + m_arpProp.GetSize() ) )
	{
		delete pProp;
		pProp = NULL;
	}

	return pProp;
}

void CMultiSelProp::DeleteProp( CProp* pProp )
{
	// If pProp RemoveProp() will return TRUE
	if( RemoveProp( pProp ) )
		delete pProp;
}

void CMultiSelProp::DeleteAllProp()
{
	// Find the given Prop and remove
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
		delete ppProp[i];

	m_arpProp.RemoveAll();
}

BOOL CMultiSelProp::RemoveProp( CProp* pProp )
{
	// Find the given Prop and remove
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
		if( ppProp[i] == pProp )
		{	
			// Found, remove
			m_arpProp.RemoveAt( i );
			return TRUE;
		}	
		
		return FALSE;
}

void CMultiSelProp::RemoveAllProp()
{
	m_arpProp.RemoveAll();
}

void CMultiSelProp::AddProp( CProp* pProp )
{
	// Find the given Prop is already in the list
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
		if( ppProp[i] == pProp )
			return; // Already there

	// No duplicate, add
	m_arpProp.Add( pProp ); 
}

void CMultiSelProp::CreateCommonItemList()
{
	INT nPropCnt = m_arpProp.GetSize();
	if( nPropCnt < 2 )
		return;

	// Multiple Prop selection, create common SPropItem list
	SPropItem* psItem;
	INT i, j, n, nCount;
	SPropItem** ppsItem;
	CPtrArray arpCommonItem;

	CProp* pCurProp = m_rPropCtrl.m_pProp;
	INT nCurPropItemCnt = pCurProp->GetAllItemListCount();
	SPropItem** ppsCurPropItem = pCurProp->GetAllItemList();

	// Find common prop item with current prop
	nPropCnt = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( i = 0; i < nCurPropItemCnt; i++ )
	{
		for( n = 0; n < nPropCnt; n++ )
		{
			if( ppProp[n] == pCurProp )
				continue;

			nCount = ppProp[n]->GetAllItemListCount();
			ppsItem = ppProp[n]->GetAllItemList();
			for( j = 0; j < nCount; j++ )
			{
				if( ppsCurPropItem[i]->psProp->nID == ppsItem[j]->psProp->nID &&
					((ppsCurPropItem[i]->psGroup && ppsItem[j]->psGroup 
					&& ppsCurPropItem[i]->psGroup->psProp->nID == ppsItem[j]->psGroup->psProp->nID) ||
					  (NULL == ppsCurPropItem[i]->psGroup && NULL == ppsItem[j]->psGroup)) )
					break;
			}

			if( j == nCount )
				goto LBNotMatch;
		}

		arpCommonItem.Add( ppsCurPropItem[i] );
LBNotMatch:;
	}

	// Remove NULL group
	nCount = arpCommonItem.GetSize();
	for( i = 0; i < nCount; i++ )
	{
		psItem = (SPropItem*)arpCommonItem.GetAt( i );
		if( OPST_GROUP == psItem->psProp->nType )
		{
			if( i + 1 < nCount )
			{
				// If next item is also group, then this is NULL group
				psItem = (SPropItem*)arpCommonItem.GetAt( i + 1 );
				if( OPST_GROUP == psItem->psProp->nType )
				{
					arpCommonItem.RemoveAt( i-- );
					nCount--;
				}
			}
			else
			{
				// No next item, so this is NULL group
				arpCommonItem.RemoveAt( i-- );
				nCount--;
			}
		}
	}

	// Copy common prop items to current prop
	pCurProp->m_arpAllItem.Copy( arpCommonItem );
	pCurProp->m_arpItem.RemoveAll();
	pCurProp->InitItemStruct();
	pCurProp->CreateItemList();

	// Copy common prop items to all other prop
	CPtrArray arpItem;
	nCount = arpCommonItem.GetSize();
	ppsItem = (SPropItem**)arpCommonItem.GetData();
	for( n = 0; n < nPropCnt; n++ )
	{
		if( ppProp[n] == pCurProp )
			continue;

		for( i = 0; i < nCount; i++ )
		{
			psItem = ppProp[n]->GetItem( ppsItem[i]->psProp->nID );
			ASSERT( psItem );
			arpItem.Add( psItem );
		}

		ppProp[n]->m_arpAllItem.Copy( arpItem );
		ppProp[n]->m_arpItem.RemoveAll();
		ppProp[n]->InitItemStruct();
		ppProp[n]->CreateItemList();

		arpItem.RemoveAll();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMultiSelProp::GetLabel( SPropItem* psItem, CString& rcszName )
{
	ASSERT( psItem );
	
	INT nItemID = psItem->psProp->nID;
	SPropItem* psFindItem = m_rPropCtrl.m_pProp->GetItem( nItemID );
	if( m_rPropCtrl.m_pProp->SendPropMsg( PBM_GETLABEL, 0, nItemID, (UINT)psFindItem, (UINT)&rcszName ) )
		return TRUE;		

	return m_rPropCtrl.m_pProp->GetLabel( psFindItem, rcszName );
}

BOOL CMultiSelProp::GetDesc( SPropItem* psItem, CString& rcszDesc )
{
	ASSERT( psItem );
	
	INT nItemID = psItem->psProp->nID;
	SPropItem* psFindItem = m_rPropCtrl.m_pProp->GetItem( nItemID );
	if( m_rPropCtrl.m_pProp->SendPropMsg( PBM_GETDESC, 0, nItemID, (UINT)psFindItem, (UINT)&rcszDesc ) )
		return TRUE;

	return m_rPropCtrl.m_pProp->GetDesc( psFindItem, rcszDesc );
}

BOOL CMultiSelProp::GetText( SPropItem* psItem, CString& rcszText, BOOL* pbMultiple /*= NULL*/ )
{
	ASSERT( psItem );
	
	if( pbMultiple )
		*pbMultiple = FALSE;

	INT nResult, nItemID = psItem->psProp->nID;
	SPropItem* psFindItem = m_rPropCtrl.m_pProp->GetItem( nItemID );
	nResult = m_rPropCtrl.m_pProp->SendPropMsg( PBM_GETTEXT, 0, nItemID, (UINT)psFindItem, (UINT)&rcszText );
	if( TRUE != nResult && FALSE != nResult )
		return nResult;

	nResult = m_rPropCtrl.m_pProp->GetText( psFindItem, rcszText );
	if( TRUE != nResult && FALSE != nResult )
		return nResult;

	if( NULL == pbMultiple )
		return TRUE;

	CString cszText;
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		if( m_rPropCtrl.m_pProp == ppProp[i] )
			continue;

		psFindItem = ppProp[i]->GetItem( nItemID );

		nResult = ppProp[i]->SendPropMsg( PBM_GETTEXT, 0, nItemID, (UINT)psFindItem, (UINT)&cszText );
		if( TRUE != nResult && FALSE != nResult )
			return nResult;

		if( TRUE == nResult )
		{
			if( rcszText != cszText )
			{
				*pbMultiple = TRUE;
				return TRUE;
			}

			continue;
		}

		nResult = ppProp[i]->GetText( psFindItem, cszText );
		if( TRUE != nResult && FALSE != nResult )
			return nResult;

		if( TRUE == nResult && rcszText != cszText )
		{
			*pbMultiple = TRUE;
			return TRUE;
		}
	}

	return TRUE;
}

void CMultiSelProp::UpdateText()
{
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
		ppProp[i]->UpdateText();
}

void CMultiSelProp::UpdateText( INT nID )
{
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
		ppProp[i]->UpdateText( nID );
}

BOOL CMultiSelProp::EditChange( SPropItem* psItem )
{
	SPropItem* psFindItem;
	INT nResult, nItemID = psItem->psProp->nID;
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		psFindItem = ppProp[i]->GetItem( nItemID );

		nResult = ppProp[i]->EditChange( psFindItem );
		if( nResult < 0 )
			return nResult;
	}

	return FALSE;
}

BOOL CMultiSelProp::UpdateItem( SPropItem* psItem )
{
	ASSERT( psItem && m_pedtProp );
	
	m_pedtProp->UpdateText();

	SPropItem* psFindItem;
	INT nResult, nItemID = psItem->psProp->nID;
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		psFindItem = ppProp[i]->GetItem( nItemID );

		nResult = ppProp[i]->SendPropMsg( PBM_UPDATEITEM, 0, nItemID, (UINT)psFindItem );
		if( TRUE == nResult )
			continue;

		if( TRUE != nResult && FALSE != nResult )
			return nResult;

		nResult = ppProp[i]->UpdateItem( psFindItem );
		if( TRUE != nResult && FALSE != nResult )
			return nResult;
	}

	return TRUE;
}

BOOL CMultiSelProp::BtnClick( SPropItem* psItem )
{
	SPropItem* psFindItem;
	INT nResult, nItemID = psItem->psProp->nID;
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		psFindItem = ppProp[i]->GetItem( nItemID );

		nResult = ppProp[i]->SendPropMsg( PBM_BTNCLICK, 0, nItemID, (UINT)psFindItem );
		if( TRUE == nResult )
			continue;

		if( TRUE != nResult && FALSE != nResult )
			return nResult;

		nResult = ppProp[i]->BtnClick( psFindItem );
		if( TRUE != nResult && FALSE != nResult )
			return nResult;
	}

	return TRUE;
}

BOOL CMultiSelProp::FillCombo( SPropItem* psItem )
{
	SPropItem* psFindItem;
	INT nResult, nItemID = psItem->psProp->nID;
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		psFindItem = ppProp[i]->GetItem( nItemID );

		nResult = ppProp[i]->SendPropMsg( PBM_COMBO_FILL, 0, nItemID, (UINT)psFindItem );
		if( TRUE == nResult )
			continue;

		if( TRUE != nResult && FALSE != nResult )
			return nResult;

		nResult = ppProp[i]->FillCombo( psFindItem );
		if( TRUE != nResult && FALSE != nResult )
			return nResult;
	}

	return TRUE;
}

BOOL CMultiSelProp::UpdateCombo( SPropItem* psItem )
{
	SPropItem* psFindItem;
	INT nResult, nItemID = psItem->psProp->nID;
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		psFindItem = ppProp[i]->GetItem( nItemID );

		nResult = ppProp[i]->SendPropMsg( PBM_COMBO_UPDATE, 0, nItemID, (UINT)psItem );
		if( TRUE == nResult )
			continue;

		if( TRUE != nResult && FALSE != nResult )
			return nResult;

		nResult = ppProp[i]->UpdateCombo( psFindItem );
		if( TRUE != nResult && FALSE != nResult )
			return nResult;
	}

	return TRUE;
}

BOOL CMultiSelProp::ComboSelChange( SPropItem* psItem, CMSComboBox::NMSELCHANGE* pNotifyStruct, LRESULT* plResult )
{
	SPropItem* psFindItem;
	INT nResult, nItemID = psItem->psProp->nID;
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		psFindItem = ppProp[i]->GetItem( nItemID );

		nResult = ppProp[i]->SendPropMsg( PBM_COMBO_SELCHANGE, 0, nItemID, (UINT)psFindItem, (UINT)pNotifyStruct, (UINT)plResult );
		if( TRUE == nResult )
			continue;

		if( TRUE != nResult && FALSE != nResult )
			return nResult;

		nResult = ppProp[i]->ComboSelChange( psFindItem, pNotifyStruct, plResult );
		if( TRUE != nResult && FALSE != nResult )
			return nResult;
	}

	return TRUE;
}

BOOL CMultiSelProp::SetComboSel( SPropItem* psItem )
{
	SPropItem* psFindItem;
	INT nResult, nItemID = psItem->psProp->nID;
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		psFindItem = ppProp[i]->GetItem( nItemID );

		nResult = ppProp[i]->SendPropMsg( PBM_COMBO_SETSEL, 0, nItemID, (UINT)psFindItem );
		if( TRUE == nResult )
			continue;

		if( TRUE != nResult && FALSE != nResult )
			return nResult;

		nResult = ppProp[i]->SetComboSel( psFindItem );
		if( TRUE != nResult && FALSE != nResult )
			return nResult;
	}

	return TRUE;
}

BOOL CMultiSelProp::ComboCancel( SPropItem* psItem )
{
	SPropItem* psFindItem;
	INT nResult, nItemID = psItem->psProp->nID;
	INT nCount = m_arpProp.GetSize();
	CProp** ppProp = (CProp**)m_arpProp.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		psFindItem = ppProp[i]->GetItem( nItemID );

		nResult = ppProp[i]->SendPropMsg( PBM_COMBO_CANCEL, 0, nItemID, (UINT)psFindItem );
		if( TRUE == nResult )
			continue;

		if( TRUE != nResult && FALSE != nResult )
			return nResult;

		nResult = ppProp[i]->ComboCancel( psFindItem );
		if( TRUE != nResult && FALSE != nResult )
			return nResult;
	}

	return TRUE;
}
