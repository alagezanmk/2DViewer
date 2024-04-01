#include "stdafx.h"
#include "test.h"

#include "testBldDoc.h"
#include "testBldView.h"
#include "TestBldChildFrm.h"
#include <g\tools\sTool.h>

#include <g\type\idom\giTransformElement.h>

#include <bld\layer.h>
#include <g\tools\sTool.h>
#include <g\tools\eRectTool.h>
#include <g\tools\eLineTool.h>
#include <bld\page.h>

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGIRectElement* g_pRectElm;

///////////////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CTestBldView, CGEditView )
BEGIN_MESSAGE_MAP(CTestBldView, CGEditView)
	//{{AFX_MSG_MAP(CTestView)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CGEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CGEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

BEGIN_EVENT_LINK( CTestBldView, CGEditView )
	ON_EVT_PHASE( CGViewWndEvent::DocumentChange, CGEvent::CAPTURING_PHASE, OnDocumentChangeEvent )
	ON_EVT_PHASE( CGSelectionEvent::EVENT, CGEvent::CAPTURING_PHASE, OnSelectionEvent )
	
	ON_EVT_PHASE_NODE_LINK_CHANGE( CGMutationEvent::DOMNodeInserted, CGEvent::CAPTURING_PHASE, OnNodeLinkChangeEvent )
	//ON_EVT_PHASE_NODE_LINK_CHANGE( CGMutationEvent::DOMNodeRemoved, CGEvent::CAPTURING_PHASE, OnNodeLinkChangeEvent )
	ON_EVT_PHASE_NODE_LINK_CHANGE( CGMutationEvent::DOMNodeInsertedIntoDocument, CGEvent::CAPTURING_PHASE, OnNodeLinkChangeEvent )
	ON_EVT_PHASE_NODE_LINK_CHANGE( CGMutationEvent::DOMNodeRemovedFromDocument, CGEvent::CAPTURING_PHASE, OnNodeLinkChangeEvent )
END_EVENT_LINK()

CTestBldView::CTestBldView()
{
	AddEventListener( CGViewWndEvent::DocumentChange, *this, TRUE );
}

CTestBldView::~CTestBldView()
{
	RemoveEventListener( CGViewWndEvent::DocumentChange, *this, TRUE );
}

void CTestBldView::OnDraw( CDC* pDC )
{
	CTestBldDoc* pDoc = GetDocument();
	ASSERT_VALID( pDoc );
}

#ifdef _DEBUG
void CTestBldView::AssertValid() const {
	CGEditView::AssertValid(); }

void CTestBldView::Dump( CDumpContext& dc ) const {
	CGEditView::Dump( dc ); }

CTestBldDoc* CTestBldView::GetDocument() // non-debug version is inline
{
	ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS( CTestBldDoc ) ) );
	return ( CTestBldDoc * ) m_pDocument;
}
#endif //_DEBUG

BOOL CTestBldView::OnPreparePrinting( CPrintInfo* pInfo ) {
	return DoPreparePrinting( pInfo ); }

void CTestBldView::OnBeginPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ ) 
{}

void CTestBldView::OnEndPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ ) 
{}

static HTREEITEM _FindNodeInSiblings( CTreeCtrl& rTreeCtrl, CGINode* pNode, HTREEITEM hItem )
{
	CGINode* pItemData;
	do 
	{
		pItemData = (CGINode*)rTreeCtrl.GetItemData( hItem );
		if( pItemData == pNode )
			return hItem;

	}while( hItem = rTreeCtrl.GetNextSiblingItem( hItem ) );

	return NULL;
}

static HTREEITEM _FindNodeItem( CTreeCtrl& rTreeCtrl, CGINode* pNode, HTREEITEM hStartItem )
{
	if( NULL == pNode && 
		NULL == rTreeCtrl.m_hWnd && 
		FALSE == IsWindow( rTreeCtrl.m_hWnd ) )
		return NULL;

	CGINode* pStartParent = NULL;
	if( hStartItem && TVI_ROOT != hStartItem )
		pStartParent = (CGINode*)rTreeCtrl.GetItemData( hStartItem );

	// Create list of Node -> Parent -> .... -> Root parent
	CPtrArray arpPath;
	CGINode* pParent = pNode;
	
	do
	{
		arpPath.Add( pParent );

		// Add till before start parent
		pParent = pParent->GetParent();
		if( pStartParent == pParent )
			break;
	}while( pParent );

	HTREEITEM hItem = hStartItem;	// Start from ROOT item or given item
	INT nCount = arpPath.GetSize();
	CGINode** ppNode = (CGINode**)arpPath.GetData();
	for( INT i = nCount - 1; i >= 0; i-- )
	{
		// Get first child item of the given parent item
		hItem = rTreeCtrl.GetChildItem( hItem );
		if( NULL == hItem )	
			break;	// No child item available

		// Find the given node from the first child item
		hItem = _FindNodeInSiblings( rTreeCtrl, ppNode[i], hItem );
		if( NULL == hItem )	
			break;	// end node or some parent not not found
	}

	return hItem;
}

HTREEITEM CTestBldView::AddChild( CGINode* pNode, HTREEITEM hParent, BOOL bAddChilds /*= FALSE*/ )
{
	CTreeCtrl* pTreeCtrl = GetTreeCtrl();
	if( NULL == pTreeCtrl )
		return NULL;

	ASSERT( pNode );

	if( NULL == hParent )
		hParent = TVI_ROOT;

	HTREEITEM hNodeItem = _FindNodeItem( *pTreeCtrl, pNode, hParent );
	if( hNodeItem )
		return hNodeItem;

	CString cszID;
	if( pNode->IsDerivedFrom( CGIElement::GetClassType() ) )
		cszID = ((CGIElement*)pNode)->m_aID;
	else
		cszID = pNode->GetName();

	if( cszID.IsEmpty() )
		cszID.Format( _T("Node %x"), pNode );

	CBldMainFrm* pMainFrm = (CBldMainFrm*)AfxGetMainWnd();
	ASSERT( pMainFrm );
	
	CPropBox* pPropBox = pMainFrm->GetPropBox();
	ASSERT( pPropBox );
	if( pPropBox )
	{
		INT nID = 0;
		if( pNode->IsDerivedFrom( CGIElement::GetClassType() ) )
			nID = 100;

		pPropBox->InsertObject( pNode, (LPCTSTR)cszID, nID, pNode->GetParent(), pNode->GetPrev() );
	}

	HTREEITEM hItem = pTreeCtrl->InsertItem( TVIF_TEXT | TVIF_PARAM, cszID, 
											0, 0, 0, 0,			// Images
											(LPARAM)pNode,
											hParent,
											TVI_LAST );

	if( bAddChilds ) 
	{
		CGINode* pChild = pNode->GetFirst();
		while( pChild )
		{
			AddChild( pChild, hItem, bAddChilds );
			pChild = pChild->GetNext();
		}
	}

	return hItem;
}

BOOL CTestBldView::RemoveChild( CGINode* pNode, HTREEITEM hParent )
{
	CBldMainFrm* pMainFrm = (CBldMainFrm*)AfxGetMainWnd();
	ASSERT( pMainFrm );

	CPropBox* pPropBox = pMainFrm->GetPropBox();
	ASSERT( pPropBox );
	if( pPropBox )
		pPropBox->DeleteObject( pNode );

	CTreeCtrl* pTreeCtrl = GetTreeCtrl();
	if( NULL == pTreeCtrl )
		return FALSE;

	ASSERT( pNode );
	HTREEITEM hNodeItem = _FindNodeItem( *pTreeCtrl, pNode, hParent );
	if( NULL == hNodeItem )
	{
		ASSERT( FALSE );
		return FALSE;
	}

	pTreeCtrl->DeleteItem( hNodeItem );
	return TRUE;
}

CTreeCtrl* CTestBldView::GetTreeCtrl() 
{
	CTestBldChildFrm* pChildFrame = (CTestBldChildFrm*)GetParent();
	ASSERT( pChildFrame );
	ASSERT_KINDOF( CTestBldChildFrm, pChildFrame );

	CTreeCtrl* pTreeCtrl = (CTreeCtrl*)pChildFrame->m_wndDlgBar.GetDlgItem( IDC_ELEMENT_TREE );
	return pTreeCtrl;
}

const CTreeCtrl* CTestBldView::GetTreeCtrl() const
{
	CTestBldChildFrm* pChildFrame = (CTestBldChildFrm*)GetParent();
	ASSERT( pChildFrame );
	ASSERT_KINDOF( CTestBldChildFrm, pChildFrame );

	CTreeCtrl* pTreeCtrl = (CTreeCtrl*)pChildFrame->m_wndDlgBar.GetDlgItem( IDC_ELEMENT_TREE );
	return pTreeCtrl;
}

void CTestBldView::OnTimer( UINT nIDEvent )
{
	return;
	if( g_pRectElm )
	{
		if( g_pRectElm->m_aX < 600 )
			g_pRectElm->m_aX = (FLOAT)g_pRectElm->m_aX + 10;
		else
			g_pRectElm->m_aX = 0;

		if( g_pRectElm->m_aY < 600 )
			g_pRectElm->m_aY = (FLOAT)g_pRectElm->m_aY + 10;
		else
			g_pRectElm->m_aY = 0;
	}
}

void CTestBldView::OnInitialUpdate() 
{
	CGEditView::OnInitialUpdate(); 

	CGIEditView* pEditView = GetView();
	ASSERT( pEditView );

	CBldMainFrm* pMainFrm = (CBldMainFrm*)AfxGetMainWnd();
	ASSERT( pMainFrm );
	CPropBox* pPropBox = pMainFrm->GetPropBox();
	ASSERT( pPropBox );
	pPropBox->SetNotifyHook( CPropBox::SEL_NOTIFY_HOOK, OnPropObjectSelChange, this );

	pPropBox->InsertObject( (CGINode*)pEditView, _T("view"), 100 );

	CGIDocument* pDocument = GetDomDocument();
	{
		pDocument = new CGIDocument;
		ASSERT( pDocument );

		CGViewWnd* pwndView = GetViewWindow();
		ASSERT( pwndView );
		pwndView->SetDocument( pDocument );
	}

	HTREEITEM hDocItem = AddChild( pDocument, NULL, TRUE );

	CTestBldDoc* pDoc = GetDocument();
	ASSERT( pDoc );
	CGINode* pFileNode = pDoc->GetFileNode();
	if( pFileNode )
	{
		pFileNode->AddRef();
		pDoc->SetFileNode( NULL );

		CGINode* pNode = pFileNode->GetFirst();
		while( pNode )
		{
			pDocument->AppendChild( *pNode );
			pNode = pNode->GetNext();
		}

		pFileNode->Release();
	}

	CGINode* pRootNode = pDocument->GetFirst();
	if( 1 &&  NULL == pRootNode )
	{
		CGIPage* pPage = (CGIPage*)pDocument->CreateElement( CGIPage::ELEMENT_TAGNAME );
		ASSERT( pPage );

		pPage->m_aWidth = 300;
		pPage->m_aHeight = 200;
		pPage->m_aDocWidth = 300;
		pPage->m_aDocHeight = 200;
		//pPage->m_aRotate = 1;
		pPage->m_c = Color( 200, 0, 255, 0 );
		//pPage->SetScale( 1f );

		pPage->m_aViewBox.SetAlign( CGIViewBox::enAxMidYMid ); 
		pPage->m_aViewBox.SetAspectRatioType( CGIViewBox::enARMeet );
		pPage->m_aViewBox.m_aWidth = 200;
		pPage->m_aViewBox.m_aHeight = 300;
		pPage->m_aViewBox.m_aEnable = TRUE;
		pPage->SetNodeFlag( CGINode::DATA_CTM_MODIFIED_NODE_FLAG );
		pPage->Update();

		//pPage->m_aX = 10;
		//pPage->m_aEnableClip = TRUE;
		pDocument->AppendChild( *pPage );

		if( 1 )
		{
			CGILayer* pLayer = (CGILayer*)pDocument->CreateElement( CGILayer::ELEMENT_TAGNAME );
			ASSERT( pLayer );
			pLayer->m_aWidth = 300;
			pLayer->m_aHeight = 200;
			pRootNode = pLayer;
			pPage->AppendChild( *pLayer );
		}
	}

	//pRootNode = pEditView;

	if( 1 )
	{
		pEditView->m_aViewBox.SetAlign( CGIViewBox::enAxMidYMid ); 
		pEditView->m_aViewBox.SetAspectRatioType( CGIViewBox::enARMeet );
		pEditView->m_aViewBox.m_aWidth = 300;
		pEditView->m_aViewBox.m_aHeight = 200;
		pEditView->m_aViewBox.m_aEnable = FALSE;
		//pEditView->m_aEnableClip = TRUE;
		//pEditView->m_aRotate = 45;
		//pEditView->m_aCenter = FALSE;
		
		if( 1 )
		{
			if( 0 )
			{
				//pEditView->m_aX = 100;
				//pEditView->m_aY = 100;
			}
			
			//pEditView->m_aScale = 2.f;	
			//pEditView->m_aAspectRatio = .5f;
			//pEditView->m_aSkewX = 54.f;
			//pEditView->m_aSkewY = 54.f;
			//pEditView->SetViewScale( 1, .5f );
			//pEditView->m_aRotate = 25;
			//pEditView->m_aEnableClip = TRUE;
			//pEditView->m_aCenter = TRUE;
			
			CGIRectElement* pRectElm = (CGIRectElement*)pDocument->CreateElement( CGIRectElement::ELEMENT_TAGNAME );
			g_pRectElm = pRectElm;
			if( 1 )
			{
				pRootNode->AppendChild( *pRectElm );
				pRectElm->m_aX = 0;
				pRectElm->m_aY = 0;
				pRectElm->m_aWidth = 300;
				pRectElm->m_aHeight = 200;
			}

			if( 0 )
			{
				CGILineElement* pLineElm = (CGILineElement*)pDocument->CreateElement( CGILineElement::ELEMENT_TAGNAME );
				pRootNode->AppendChild( *pLineElm );
				pLineElm->m_aX1 = 0;
				pLineElm->m_aY1 = 0;
				pLineElm->m_aX2 = 504;
				pLineElm->m_aY2 = 200;
			}
			
			if( 1 )
			{
				CGITransformElement* piTfxElement = new CGITransformElement;
				piTfxElement->OnInitialUpdate();
				ASSERT( piTfxElement );
				pRootNode->AppendChild( *piTfxElement );
			}
			
			if( 1 )
			{
				pRectElm = (CGIRectElement*)pDocument->CreateElement( CGIRectElement::ELEMENT_TAGNAME );
				pRootNode->AppendChild( *pRectElm );
				pRectElm->m_aX = -100;
				pRectElm->m_aY = 0;
				pRectElm->m_aWidth = 100;
				pRectElm->m_aHeight = 100;
			}

			for( INT i = 0; 0 && i < 1000; i++ )
			{
				pRectElm = (CGIRectElement*)pDocument->CreateElement( CGIRectElement::ELEMENT_TAGNAME );
				pRootNode->AppendChild( *pRectElm );
				pRectElm->m_aX = i * 2.f;
				pRectElm->m_aY = i * 2.f;
				pRectElm->m_aWidth = 100;
				pRectElm->m_aHeight = 100;
			}
			
			if( 0 )
			{
				pRectElm = (CGIRectElement*)pDocument->CreateElement( CGIRectElement::ELEMENT_TAGNAME );
				pRootNode->AppendChild( *pRectElm );
				pRectElm->m_aX = 10;
				pRectElm->m_aY = 10;
				pRectElm->m_aWidth = 200;
				pRectElm->m_aHeight = 200;
				
				if( 1 )
				{
					CGIView* pgNewView = (CGIView*)pDocument->CreateElement( CGIView::ELEMENT_TAGNAME );
					pRootNode->AppendChild( *pgNewView );
					//pgNewView->m_aEnableClip = 0;
					//pgNewView->m_aX = 10;
					//pgNewView->m_aY = 10;
					pgNewView->m_aWidth = 200;
					pgNewView->m_aHeight = 200;
					pgNewView->m_aDocWidth = 200;
					pgNewView->m_aDocHeight = 200;
					//pgNewView->m_aScale = 2;
					//pgNewView->m_aAspectRatio = 2;
					//pgNewView->m_aCenter = TRUE;
					pgNewView->m_c = Color::Green;
				}
				
				if( 1 )
				{
					CGIView* pgNewView = (CGIView*)pDocument->CreateElement( CGIView::ELEMENT_TAGNAME );
					
					//pgNewView->m_aEnableClip = 0;
					//pgNewView->m_aX = 10;
					//pgNewView->m_aY = 10;
					pgNewView->m_aWidth = 200;
					pgNewView->m_aHeight = 200;
					pgNewView->m_aDocWidth = 30;
					pgNewView->m_aDocHeight = 30;
					//pgNewView->m_aScale = 2;
					//pgNewView->m_aAspectRatio = 2;
					//pgNewView->m_aRotate = 45;
					pgNewView->m_aDocCenter = TRUE;
					pgNewView->m_c = Color::Blue;

					pRootNode->AppendChild( *pgNewView );
					
					pRectElm = (CGIRectElement*)pDocument->CreateElement( CGIRectElement::ELEMENT_TAGNAME );
					pgNewView->AppendChild( *pRectElm );
					pRectElm->m_aX = 0;
					pRectElm->m_aY = 0;
					pRectElm->m_aWidth = 200;
					pRectElm->m_aHeight = 200;
					
					pRectElm = (CGIRectElement*)pDocument->CreateElement( CGIRectElement::ELEMENT_TAGNAME );
					pgNewView->AppendChild( *pRectElm );
					pRectElm->m_aX = 10;
					pRectElm->m_aY = 10;
					pRectElm->m_aWidth = 200;
					pRectElm->m_aHeight = 200;
					
					CGEditWnd* pEditWnd = GetEditWindow();
					ASSERT( pEditWnd );
					CGISelectionTool* pSelTool = 
						(CGISelectionTool*)pEditWnd->GetTool( CGISelectionTool::GetClassType() );
					
					ASSERT( pSelTool );
					//pSelTool->SetActiveGroup( pgNewView );
				}
			}
		}
	}

	//pRootNode = pDocument->GetFirst();
	//pDocument->AppendChild( *pRootNode );
	//pDocument->RemoveChild( *pRootNode );

	CGEditWnd* pwndEdit = GetEditWindow();
	ASSERT( pwndEdit );
	//pwndEdit->SetActiveGroup( (CGIGroup*)pRootNode );

	pPropBox->SetCurObject( (CGINode*)pEditView );

	SetTimer( 1, 100, NULL );

	CGViewWnd* pwndView = GetViewWindow();
	pwndView->SetScrollSizes( 300, 200 );

	// Second view
	if( 0 )
	{
		VERIFY( pEditView = new CGIEditView );

		CGViewWnd* pwndView2;
		VERIFY( pwndView2 = new CGViewWnd );

		pwndView2->SetView( *pEditView );
		pwndView2->SetDocument( pDocument );

		VERIFY( pwndView2->Create( NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0,0,0,0), pwndView, 1000 ) );
		pwndView2->OnInitialUpdate();

		pwndView2->MoveWindow( 0, 0, 400, 200 );
		pwndView2->SetScrollSizes( 400, 200 );

		pEditView->m_aScale = 0.5f;
		pEditView->m_aDocCenter = FALSE;
	}
} 

void CTestBldView::SelectElement( CGIShapeElement* pElement )
{
	CTreeCtrl* pTreeCtrl = GetTreeCtrl();
	ASSERT( pTreeCtrl );

	HTREEITEM hItem = _FindNodeItem( *pTreeCtrl, pElement, NULL );
	if( hItem )
	{
        pTreeCtrl->SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
        pTreeCtrl->EnsureVisible( hItem );
	}
}

void CTestBldView::DeselectElement( CGIShapeElement* pElement )
{
	CTreeCtrl* pTreeCtrl = GetTreeCtrl();
	ASSERT( pTreeCtrl );

	HTREEITEM hItem = _FindNodeItem( *pTreeCtrl, pElement, NULL );
	if( hItem )
		pTreeCtrl->SetItemState( hItem, 0, TVIS_SELECTED );
}

void CTestBldView::OnNodeLinkChangeEvent( CGMutationEvent& rEvent )
{
	LPCTSTR ptszEventType = rEvent.GetType();
	CGINode* pParent = (CGINode*)rEvent.GetRelatedNode();
	CGINode* pNode = (CGINode*)rEvent.GetTarget();

	ASSERT( CGMutationEvent::DOMNodeInsertedIntoDocument == ptszEventType 
			|| CGMutationEvent::DOMNodeRemovedFromDocument == ptszEventType 
			|| (pParent && pParent == pNode->GetParent() ) );

	pParent = pNode->GetParent();
	CTreeCtrl* pTreeCtrl = GetTreeCtrl();
	ASSERT( pTreeCtrl );
	HTREEITEM hParentItem = NULL;
	if( pParent )
	{
		hParentItem = _FindNodeItem( *pTreeCtrl, pParent, NULL );
		ASSERT( hParentItem );
	}

	if( CGMutationEvent::ADDITION == rEvent.GetAttrChange() )
		AddChild( pNode, hParentItem );
	else
		RemoveChild( pNode, hParentItem );
}

void CTestBldView::OnPropObjectSelChange( NMHDR* pNMHDR, LRESULT* plResult, void* pvParam )
{
	CTestBldView* pThis = (CTestBldView*)pvParam;
	CGEditWnd* pgwndEdit = pThis->GetEditWindow();
	if( pgwndEdit )
	{
		CGISelectionTool* pSelTool = pgwndEdit->GetSelectionTool();
		if( pSelTool )
		{
			CBldMainFrm* pMainFrm = (CBldMainFrm*)AfxGetMainWnd();
			ASSERT( pMainFrm );

			CPropBox* pPropBox = pMainFrm->GetPropBox();
			ASSERT( pPropBox );
			if( pPropBox )
			{
				CPropObjectSelComboBox::NMSELCHANGE* pNM = (CPropObjectSelComboBox::NMSELCHANGE*)pNMHDR;
				void* pvObject = pPropBox->HTREEITEMToObject( pNM->hItem );
				ASSERT( pvObject );
				if( pvObject )
				{
					CGINode* pgiNode = (CGINode*)pvObject;
					if( pgiNode->IsDerivedFrom( CGIDocument::GetClassType() ) )
						return;

					if( pgiNode->IsDerivedFrom( CGIElement::GetClassType() ) )
					{
						CGIElement* pElement = (CGIElement*)pgiNode;
						*plResult = 1;	// Always Override property box selection change and 
										// handle the selection change through Selection Tool 
										// to property box

						CString cszName = pElement->GetName();

						if( pNM->bMultipleSel )
						{
							if( pNM->bSelect )
								pSelTool->AddSelection( *pElement );
							else
								pSelTool->RemoveSelection( *pElement );
						}
						else
						{
							pSelTool->DeselectAll();
							if( pNM->bSelect )
								pSelTool->AddSelection( *pElement );
						}
					}
				}
			}
		}
	}
}

void CTestBldView::OnSelectionEvent( CGEvent& rEvent )
{
	CGSelectionEvent& rSelEvent = *((CGSelectionEvent*)&rEvent);

	CPtrArray& arpElement = rSelEvent.GetShapeElementArray();
	INT nCount = arpElement.GetSize();
	CGIShapeElement** ppElement = (CGIShapeElement**)arpElement.GetData();

	CBldMainFrm* pMainFrm = (CBldMainFrm*)AfxGetMainWnd();
	ASSERT( pMainFrm );
	CPropBox* pPropBox = pMainFrm->GetPropBox();
	ASSERT( pPropBox );
	if( CGSelectionEvent::SELECT == rSelEvent.GetSelectionChange() )
	{
		//pPropBox->InsertObj( ppElement[0], _T("rect") );
		//pPropBox->SetCurObject( (CGINode*)ppElement[0] );

		//rEvent.PreventDefault();
		//return;

		for( INT i = 0; i < nCount; i++ )
		{
			pPropBox->SelectObject( (CGINode*)ppElement[i] );
			SelectElement( ppElement[i] );
		}
	}
	else if( CGSelectionEvent::DESELECT == rSelEvent.GetSelectionChange() )
	{
		//rEvent.PreventDefault();
		//return;

		for( INT i = 0; i < nCount; i++ )
		{
			pPropBox->SelectObject( (CGINode*)ppElement[i], FALSE );
			DeselectElement( ppElement[i] );
		}
	}
}

void CTestBldView::OnDocumentChangeEvent( CGEvent& rEvent )
{
	CGViewWndEvent& rViewEvent = *((CGViewWndEvent*)&rEvent);
	CGIDocument* pDocument = (CGIDocument*)rViewEvent.GetRelatedNode();
	INT nAttrChange = rViewEvent.GetAttrChange();
	if( CGViewWndEvent::REMOVAL == nAttrChange )
	{
		pDocument->RemoveEventListener( CGMutationEvent::DOMNodeInserted, *this, TRUE );
		pDocument->RemoveEventListener( CGMutationEvent::DOMNodeInsertedIntoDocument, *this, TRUE );
		pDocument->RemoveEventListener( CGMutationEvent::DOMNodeRemoved, *this, TRUE );
		pDocument->RemoveEventListener( CGMutationEvent::DOMNodeRemovedFromDocument, *this, TRUE );
		pDocument->RemoveEventListener( CGSelectionEvent::EVENT, *this, TRUE );
	}
	else if( CGViewWndEvent::ADDITION == nAttrChange )
	{
		pDocument->AddEventListener( CGMutationEvent::DOMNodeInserted, *this, TRUE );
		pDocument->AddEventListener( CGMutationEvent::DOMNodeInsertedIntoDocument, *this, TRUE );
		pDocument->AddEventListener( CGMutationEvent::DOMNodeRemoved, *this, TRUE );
		pDocument->AddEventListener( CGMutationEvent::DOMNodeRemovedFromDocument, *this, TRUE );
	}	pDocument->AddEventListener( CGSelectionEvent::EVENT, *this, TRUE );
}

void CTestBldView::OnDestroy()
{
	CBldMainFrm* pMainFrm = (CBldMainFrm*)AfxGetMainWnd();
	ASSERT( pMainFrm );
	CPropBox* pPropBox = pMainFrm->GetPropBox();
	ASSERT( pPropBox );
	
	pPropBox->ResetContent();

	CGEditView::OnDestroy();
}