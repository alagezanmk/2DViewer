#include "stdafx.h"
#include "MSTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMSTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CMSTreeCtrl)
	//ON_NOTIFY_REFLECT_EX( TVN_SELCHANGING, OnSelChanging )
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMSTreeCtrl::CMSTreeCtrl()
{}

CMSTreeCtrl::~CMSTreeCtrl()
{}

HTREEITEM CMSTreeCtrl::GetNext_Item( HTREEITEM hTreeItem ) const
{
	if( NULL == hTreeItem )
		return NULL;

	// Find first child item
	HTREEITEM hTreeNextItem = GetChildItem( hTreeItem );
	if( hTreeNextItem )
		return hTreeNextItem;
	
	// Find next item
	do
	{
		hTreeNextItem = CTreeCtrl::GetNextItem( hTreeItem, TVGN_NEXT );
		if( hTreeNextItem )
			return hTreeNextItem;
		
		hTreeItem = GetParentItem( hTreeItem );
	}while( hTreeItem );

	return NULL;
}

HTREEITEM CMSTreeCtrl::GetPrev_Item( HTREEITEM hTreeItem ) const
{
	if( NULL == hTreeItem )
		return NULL;
	
	// Find first child item
	HTREEITEM hTreeNextItem = CTreeCtrl::GetNextItem( hTreeItem, TVGN_PREVIOUS );
	if( hTreeNextItem )
		return hTreeNextItem;
	
	hTreeNextItem = GetParentItem( hTreeItem );
	if( hTreeNextItem )
		return hTreeNextItem;

	return NULL;
}

HTREEITEM CMSTreeCtrl::GetFirstSelectedItem() const
{
	CString cszItemText;
	for( HTREEITEM hItem = GetRootItem(); hItem; hItem = GetNext_Item( hItem ) )
	{
		cszItemText = GetItemText( hItem );
		if( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
			return hItem;
	}
		
	return NULL;
}

HTREEITEM CMSTreeCtrl::GetNextSelectedItem( HTREEITEM hItem ) const
{
	CString cszItemText;
	for( hItem = GetNext_Item( hItem ); hItem; hItem = GetNext_Item( hItem ) )
	{
		cszItemText = GetItemText( hItem );
		if( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
			return hItem;
	}
		
	return NULL;
}

HTREEITEM CMSTreeCtrl::GetPrevSelectedItem( HTREEITEM hItem ) const
{
	for( hItem = GetPrev_Item( hItem ); hItem; hItem = GetPrev_Item( hItem ) )
	{
		if( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
			return hItem;
	}
		
	return NULL;
}

void CMSTreeCtrl::DeselectAll()
{
	HTREEITEM hItem = GetFirstSelectedItem();
	while( hItem )
	{
		SetItemState( hItem, 0, TVIS_SELECTED );
		hItem = GetNextSelectedItem( hItem );
	}
}

BOOL CMSTreeCtrl::IsMultipleSelected() const 
{
	HTREEITEM hItem = GetFirstSelectedItem();
	if( NULL == hItem )
		return FALSE;

	hItem = GetNextSelectedItem( hItem );
	return NULL != hItem;
}

BOOL CMSTreeCtrl::SendSelChangeNotify( HTREEITEM hItem, BOOL bSelect /*= TRUE*/, BOOL bMultipleSel /*= TRUE*/ )
{
	CWnd* pParent = GetSelChangeParent();
	if( NULL == pParent )
	{
		ASSERT( pParent );
		return TRUE;
	}

	NMSELCHANGE nm;
	nm.hItem = hItem;
	nm.bSelect = bSelect;
	nm.bMultipleSel = bMultipleSel;

	nm.code = NM_SELCHANGE;
	nm.hwndFrom = m_hWnd;
	nm.idFrom = GetDlgCtrlID();
	
	BOOL bResult = FALSE;
	if( 1 == pParent->SendMessage( WM_NOTIFY, nm.idFrom, (LPARAM)&nm ) )
		bResult = TRUE;

	return bResult;
}

void CMSTreeCtrl::OnLButtonDown( UINT nFlags, CPoint point )
{
	UINT nHittestFlags = 0;
	HTREEITEM hItem = HitTest( point, &nHittestFlags );
	if( hItem && (TVHT_ONITEM & nHittestFlags) )
	{
#ifdef _DEBUG
		CString csz = GetItemText( hItem );
#endif //_DEBUG

		BOOL bCtrlKey = GetKeyState( VK_CONTROL ) < 0;
		BOOL bShiftKey = GetKeyState( VK_SHIFT ) < 0;

		// Not Multiple Selection Click mode
		if( FALSE == bCtrlKey && FALSE == bShiftKey )
		{
			HTREEITEM hItemItr = GetFirstSelectedItem();
			while( hItemItr )
			{
#ifdef _DEBUG
				CString csz = GetItemText( hItemItr );
#endif //_DEBUG

				if( hItem != hItemItr )
				{
					if( FALSE == SendSelChangeNotify( hItemItr, FALSE, FALSE ) )
						SetItemState( hItemItr, 0, TVIS_SELECTED );
				}

				hItemItr = GetNextSelectedItem( hItemItr );
			}
		}

		if( bShiftKey )
		{
			HTREEITEM hItemItr = GetFirstSelectedItem();
			if( NULL == hItemItr )
				hItemItr = GetRootItem();

			while( hItemItr )
			{
#ifdef _DEBUG
				CString csz = GetItemText( hItemItr );
#endif //_DEBUG
				if( FALSE == SendSelChangeNotify( hItemItr, TRUE, TRUE ) )
					SetItemState( hItemItr, TVIS_SELECTED, TVIS_SELECTED );

				if( hItemItr == hItem )
					break;	// Select Items upto clicked Item 
				
				hItemItr = GetNext_Item( hItemItr );
			}
		
			// Deselect Items after the clicked item
			if( hItemItr )
			{
				hItemItr = GetNextSelectedItem( hItemItr );
				while( hItemItr )
				{
					if( FALSE == SendSelChangeNotify( hItemItr, FALSE, TRUE ) )
						SetItemState( hItemItr, 0, TVIS_SELECTED );

					hItemItr = GetNextSelectedItem( hItemItr );
				}
			}
		}
		else
		{
			BOOL bSelect = TRUE;
			if( bCtrlKey )
			{
				UINT nState = GetItemState( hItem, TVIS_SELECTED );
				bSelect = TVIS_SELECTED == (nState & TVIS_SELECTED);
				bSelect ^= 1;
			}

			if( FALSE == SendSelChangeNotify( hItem, bSelect, bCtrlKey ) )
				SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
		}

		return;
	}

	CTreeCtrl::OnLButtonDown( nFlags, point );
}
