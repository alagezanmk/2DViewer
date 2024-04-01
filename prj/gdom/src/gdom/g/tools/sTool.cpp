#include "stdafx.h"
#include <g\tools\sTool.h>
#include <cu\RectTrackEx.h>
#include <prop\PropRes.h>
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////////////////
LPCTSTR CGSelectionEvent::EVENT = _T("Selection_Event");

CGSelectionEvent::CGSelectionEvent()  {
	m_nSelectionChange = UNKNOWN; }

CGSelectionEvent::~CGSelectionEvent() 
{}

void CGSelectionEvent::InitEvent( INT nSelectionChange, CGIElement& rElement, 
								  const GPointF* pptf /*= NULL*/ )
{
	CGEvent::InitEvent( EVENT, TRUE, TRUE );
	m_nSelectionChange = nSelectionChange;

	m_arpElements.RemoveAll();
	m_arpElements.Add( &rElement );

	if( pptf )
		m_ptfHit = *pptf;
}

void CGSelectionEvent::InitEvent( INT nSelectionChange, 
								  const CPtrArray* parpElements /*= NULL*/, 
								  const GRectF* prctf /*= NULL*/ )
{
	CGEvent::InitEvent( EVENT, TRUE, TRUE );
	m_nSelectionChange = nSelectionChange;

	if( parpElements )
	{
		m_arpElements.RemoveAll();
		m_arpElements.Copy( *parpElements );
	}

	if( prctf )
		m_rctf = *prctf;
}

//////////////////////////////////////////////////////////////////////////////////////////
IMPL_GTPYECLASS_DYNCREATE( CGISelectionTool, CGIZoomPanTool, _T("SelectionTool") )
CGISelectionTool::CGISelectionTool()
{
	m_pgInstanceType = &GetClassType();

	m_pFocusTool = NULL;
	m_pActiveTool = NULL;
	m_piActiveGroup = NULL;

	m_bUIToActiveObject = FALSE;
	m_bFirstMouseMove = FALSE;

	m_bMultipleSelect = FALSE;
	m_bChangeActive = FALSE;
	m_bLock = FALSE;
	
	m_nHitTest = CGIElementUITool::HT_NOTHING;
	m_piHitTool = NULL;
	m_piHitObject = NULL;

	m_pDefaultTool = NULL;
	m_pDefaultElementTool = NULL;

	m_bStartSelectionCalled = FALSE;
	m_nUIMode = SELECTION_UI_MODE;
	m_nDefUIMode = SELECTION_UI_MODE;
}

CGISelectionTool::~CGISelectionTool()
{
	if( m_pDefaultElementTool )
		m_pDefaultElementTool->Release();

	if( m_pDefaultTool )
		m_pDefaultTool->Release();
}

BOOL CGISelectionTool::Draw( CDC& rDC, RECT& rRect )
{
	BOOL bResult;
	if( CGIZoomPanTool::Draw( rDC, rRect, bResult ) )
		return bResult;
	
	//if( m_pDefaultTool && m_pDefaultTool->Draw( rDC, rRect ) )
	//	return TRUE;

	if( m_pFocusTool )
	{
		m_GroupTool.Draw( rDC, rRect );  

		BOOL bResult = FALSE;
		INT nCount = m_GroupTool.m_arpTool.GetSize();
		CGIElementUITool** ppElementTool = (CGIElementUITool**)m_GroupTool.m_arpTool.GetData();
		for( INT i = 0; i < nCount; i++ )
		{
			if( m_pFocusTool == ppElementTool[i] )
				bResult = m_pFocusTool->Draw( rDC, rRect );
			else
				ppElementTool[i]->Draw( rDC, rRect );
		}

		return bResult;
	}

	if( m_pDefaultElementTool )
		return m_pDefaultElementTool->Draw( rDC, rRect );

	return FALSE;
}

INT CGISelectionTool::GetDrawType() const 
{
	//if( m_pDefaultTool && m_pDefaultTool->Draw( rDC, rRect ) )
		//return TRUE;

	if( SELECTION_UI_MODE != m_nUIMode )
		return CGIZoomPanTool::GetDrawType();

	if( m_pFocusTool ) 
		return m_pFocusTool->GetDrawType();

	if( m_pDefaultElementTool )
		return m_pDefaultElementTool->GetDrawType();

	return LOWER_DRAW_TYPE; 
}

void CGISelectionTool::SetActiveGroup( CGIGroup* piGroup ) 
{
	if( NULL == piGroup )
	{
		ASSERT( piGroup );
		return;
	}

	m_piActiveGroup = piGroup; 
	if( m_pDefaultElementTool )
	{
		// Change Default Element tool's - new element parent
		if( m_pDefaultElementTool->IsDerivedFrom( CGIElementTool::GetClassType() ) )
		{
			CGIElementTool* pDefaultTool = (CGIElementTool*)m_pDefaultElementTool;
			if( pDefaultTool->IsNewElementMode() )
				pDefaultTool->SetNewElementMode( TRUE, piGroup );
		}
	}
}

CGClassFactory* CGISelectionTool::GetClassFactory() 
{
	if( NULL == m_pClassFactory )
	{
		CGClassFactory* pClassFactory;
		VERIFY( pClassFactory = new CGClassFactory );
		SetClassFactory( pClassFactory );
	}

	return m_pClassFactory; 
}

void CGISelectionTool::SetView( CGIView* pView )
{
	CGIZoomPanTool::SetView( pView );
	m_GroupTool.SetView( pView );
}

void* CGISelectionTool::CreateFactoryObject( LPCTSTR pctszClassName, 
										   void* pCookie /*= NULL*/ ) const 
{
	if( m_pClassFactory )
		return m_pClassFactory->CreateFactoryObject( pctszClassName, pCookie );

	return NULL; 
}

CGIElementUITool* CGISelectionTool::CreateElementTool( CGIElement& rElement ) 
{
	CGIElementUITool* pTool 
		= (CGIElementUITool*)CreateFactoryObject( rElement.GetName(), 
											    (void*)&rElement.GetInstanceType() );
	if( pTool )
		return pTool;

	return new CGIElementUITool; 
}

void CGISelectionTool::SetLock( BOOL bSet /*= TRUE*/ )
{
	m_bLock = bSet;
	if( m_bLock )
		DeselectAll(); 
}

void CGISelectionTool::SetDefaultTool( CGIUITool* pTool ) 
{
	if( m_pDefaultTool != pTool )
		return;

	if( m_pDefaultTool )
	{
		m_pDefaultTool->Release();
		m_pDefaultTool = NULL;
	}

	if( pTool )
	{
		m_pDefaultTool = pTool; 
		m_pDefaultTool->AddRef();
	}
}

void CGISelectionTool::SetDefaultElementTool( CGIElementUITool* pTool ) 
{
	if( m_pDefaultElementTool )
	{
		m_pDefaultElementTool->Release();
		m_pDefaultElementTool = NULL;
	}

	if( pTool )
	{
		m_pDefaultElementTool = pTool; 
		m_pDefaultElementTool->AddRef();
	}
}

UINT CGISelectionTool::HitTest( const CPoint& rpoint )
{
	BOOL bResult;
	if( CGIZoomPanTool::HitTest( rpoint, bResult ) )
		return bResult;

	m_piHitTool = NULL;
	m_piHitObject = NULL;

	if( m_bLock )
		return HT_NOTHING;

	{
		UINT nHitTest;

		if( m_pFocusTool )
		{
			nHitTest = m_pFocusTool->HitTest( rpoint );
			if( CGIElementUITool::HT_NOTHING != nHitTest )
			{
				if( m_pFocusTool != m_pActiveTool 
					&& (m_bMultipleSelect || m_bChangeActive) )
				{
					CGIElementUITool* pElementTool = HitTestTools( rpoint, nHitTest );
					if( pElementTool )
					{	
						m_piHitTool = pElementTool;
						return nHitTest;
					}
				}

				m_piHitTool = m_pFocusTool;
				return nHitTest;
			}
		}

		if( m_piHitObject = HitTestGroupElements( rpoint, nHitTest ) )
			return nHitTest;

		if( m_pDefaultElementTool )
		{
			nHitTest = m_pDefaultElementTool->HitTest( rpoint );
			if( CGIElementUITool::HT_NOTHING != nHitTest )
				m_piHitObject = m_pDefaultElementTool->m_piElement;
			
			return nHitTest;
		}
	}

	return HT_NOTHING;
}

BOOL CGISelectionTool::On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage )
{
	BOOL bResult;
	if( CGIZoomPanTool::On_SetCursor( pWnd, nHitTest, nMessage, bResult ) )
		return bResult;

	if( m_bLock )
		return FALSE;

	CGIElementUITool* pHitTool = NULL;
	if( m_piHitTool && m_piHitTool == m_pFocusTool || m_piHitTool )
	{
		pHitTool = m_pFocusTool;
		goto LBUpdateHitToolCursor;
	}

	if( m_piHitObject && m_pDefaultElementTool
		&& m_piHitObject == m_pDefaultElementTool->m_piElement )
		goto LBSetSelCursor;

	if( NULL == m_piHitObject && m_pDefaultElementTool )
	{
		pHitTool = m_pDefaultElementTool;

LBUpdateHitToolCursor:;
		ASSERT( pHitTool );
		BOOL bResult = pHitTool->On_SetCursor( pWnd, nHitTest, nMessage );
		pHitTool->SetHitTest( nHitTest );
		if( bResult )
			return TRUE;
	}

LBSetSelCursor:;
	m_nHitTest = nHitTest;
	LPCTSTR pctszCursorID = MAKEINTRESOURCE(IDC_POINTER_CUR);
	HINSTANCE hResInst = AfxFindResourceHandle( pctszCursorID, RT_GROUP_CURSOR );
	HCURSOR hCursor = ::LoadCursor( hResInst, pctszCursorID );
	::SetCursor( hCursor );
	return TRUE;
}

BOOL CGISelectionTool::OnMouseMove( const CMouseEvent& rEvent ) 
{
	BOOL bResult;
	if( CGIZoomPanTool::OnMouseMove( rEvent, bResult ) )
		return bResult;

	if( m_bLock )
		return FALSE;

	if( m_pFocusTool )
	{
		if( m_bFirstMouseMove && FALSE == m_bUIToActiveObject 
			&& m_ptClick != rEvent.m_ptClient )
		{
			m_bUIToActiveObject = TRUE;
			m_pFocusTool->OnLButtonDown( rEvent );
		}

		m_bFirstMouseMove = FALSE;

		if( m_bUIToActiveObject )
			return m_pFocusTool->OnMouseMove( rEvent );
	}

	m_bFirstMouseMove = FALSE;
	if( m_pDefaultElementTool )
		return m_pDefaultElementTool->OnMouseMove( rEvent );

	return FALSE; 
}

BOOL CGISelectionTool::OnLButtonDown( const CMouseEvent& rEvent ) 
{
	BOOL bResult;
	if( CGIZoomPanTool::OnLButtonDown( rEvent, bResult ) )
		return bResult;

	if( m_bLock )
		return FALSE;

	INT nSelectionFlags = ESF_NONE;
	if( m_bMultipleSelect )
		nSelectionFlags |= ESF_MULTIPLE_SELECTION;

	if( m_bChangeActive )
		nSelectionFlags |= ESF_MAKE_ACTIVE;

	m_ptClick = rEvent.m_ptClient;
	m_bUIToActiveObject = FALSE;
	if( m_piHitTool )
	{
		if( (m_bMultipleSelect || m_bChangeActive) 
			&& (m_pFocusTool == m_pActiveTool || m_pFocusTool != m_piHitTool) )
		{
			m_piHitObject = m_piHitTool->m_piElement;
			goto LBChangeSelection;
		}

		m_bUIToActiveObject = TRUE;
		return m_pFocusTool->OnLButtonDown( rEvent );
	}
	else 
	{
		if( m_piHitObject )
		{
			m_bFirstMouseMove = TRUE;
			m_bUIToActiveObject = FALSE;

LBChangeSelection:;
			if( ChangeSelection( *m_piHitObject, nSelectionFlags ) )
			{	
				if( m_pFocusTool )
					m_pFocusTool->SetHitTest( m_nHitTest );
			}

			return TRUE;
		}
		else
		{
			// If one or more element(s) selected and the selection 
			// is not ESF_MULTIPLE_SELECTION
			INT nSelectionCount = GetSelectedCount();
			if( nSelectionCount && FALSE == m_bMultipleSelect )
			{
				StartSelection();
				DeselectAll();
			}

			if( m_pDefaultElementTool )
			{
				BOOL bResult = m_pDefaultElementTool->OnLButtonDown( rEvent ); 

				if( m_bStartSelectionCalled )	// DeselectAll()
					EndSelection();

				return bResult;
			}

			// Use Rectangle Tracker to select for element in a rectangle
			CRectTrackerEx rctTracker;
			rctTracker.m_bMinSize = TRUE;
			rctTracker.m_szSize.cx = 7;
			rctTracker.m_szSize.cy = 7;
			rctTracker.m_pWnd = m_pwndView;
			rctTracker.m_sizeMin.cx = 1;
			rctTracker.m_sizeMin.cy = 1;
			rctTracker.m_nStyle = CRectTracker::dottedLine;
			rctTracker.m_rect.SetRect( rEvent.m_ptClient, rEvent.m_ptClient );
			if( rctTracker.TrackRubberBand( m_pwndView, rEvent.m_ptClient, TRUE ) 
				&& rctTracker.m_bMinSize )
			{
				rctTracker.m_rect.NormalizeRect();
				Select( rctTracker.m_rect, ESF_NO_END_SELECTION );
			}

			if( m_bStartSelectionCalled )	// DeselectAll() or Select( rect )
				EndSelection();
		}
	}

	return TRUE;
}

BOOL CGISelectionTool::OnLButtonUp( const CMouseEvent& rEvent ) 
{
	BOOL bResult;
	if( CGIZoomPanTool::OnLButtonUp( rEvent, bResult ) )
		return bResult;
	
	if( m_bLock )
		return FALSE;

	m_bFirstMouseMove = FALSE;
	if( m_bUIToActiveObject )
	{
		m_bUIToActiveObject = FALSE;
		if( m_pFocusTool )
			return m_pFocusTool->OnLButtonUp( rEvent );
	}

	if( m_pDefaultElementTool )
		return m_pDefaultElementTool->OnLButtonUp( rEvent );

	return FALSE; 
}

BOOL CGISelectionTool::OnMouseWheel( const CMouseEvent& rEvent ) 
{
	BOOL bResult;
	if( CGIZoomPanTool::OnMouseWheel( rEvent, bResult ) )
		return bResult;
	
	if( m_bLock )
		return FALSE;

	if( m_bUIToActiveObject )
	{
		if( m_pFocusTool )
			return m_pFocusTool->OnMouseWheel( rEvent );
	}

	if( m_pDefaultElementTool )
		return m_pDefaultElementTool->OnMouseWheel( rEvent );

	return FALSE; 
}

BOOL CGISelectionTool::OnKeyDown( const CKbdEvent& rEvent )
{
	if( FALSE == m_bLock )
	{
		// Give more precedence to the Element Tools 
		// than built in Zoom-Pan Tool
		if( m_pFocusTool && m_pFocusTool->OnKeyDown( rEvent ) )
			return TRUE;

		if( m_pDefaultElementTool && m_pDefaultElementTool->OnKeyDown( rEvent ) )
			return TRUE;
	}

	BOOL bResult;
	if( CGIZoomPanTool::OnKeyDown( rEvent, bResult ) )
		return bResult;
	
	if( m_bLock )
 		return FALSE;
	
	if( FALSE == m_bMultipleSelect 
		&& IsUIStateKey( SELECTION_UI_MODE, MULTIPLE_SELECTION_UI_STATE, rEvent.m_nKey ) )
	{
		m_bMultipleSelect = TRUE;
		VERIFY( AddListenUIStateKey( SELECTION_UI_MODE, MULTIPLE_SELECTION_UI_STATE ) );
		if( m_pwndView )
			m_pwndView->UpdateCursor();
		
		return TRUE;
	}
	else if( FALSE == m_bChangeActive 
		&& IsUIStateKey( SELECTION_UI_MODE, MAKE_ACTIVE_UI_STATE, rEvent.m_nKey ) )
	{
		m_bChangeActive = TRUE;
		
		VERIFY( AddListenUIStateKey( SELECTION_UI_MODE, MAKE_ACTIVE_UI_STATE ) );
		if( m_pwndView )
			m_pwndView->UpdateCursor();
		
		return TRUE;
	}
	
	return FALSE;
}

BOOL CGISelectionTool::OnKeyUp( const CKbdEvent& rEvent )
{
	if( FALSE == m_bLock )
	{
		// Give more precedence to the Element Tools 
		// than built in Zoom-Pan Tool
		if( m_pFocusTool && m_pFocusTool->OnKeyUp( rEvent ) )
			return TRUE;

		if( m_pDefaultElementTool && m_pDefaultElementTool->OnKeyUp( rEvent ) )
			return TRUE;
	}

	BOOL bResult;
	if( CGIZoomPanTool::OnKeyUp( rEvent, bResult ) )
		return bResult;
	
	if( m_bLock )
		return FALSE;
	
	if( m_bMultipleSelect 
		&& IsUIStateKey( SELECTION_UI_MODE, MULTIPLE_SELECTION_UI_STATE, rEvent.m_nKey ) )
	{
		m_bMultipleSelect = FALSE;
		
		VERIFY( RemoveListenUIStateKey( SELECTION_UI_MODE, MULTIPLE_SELECTION_UI_STATE ) );
		if( m_pwndView )
			m_pwndView->UpdateCursor();
		
		return TRUE;
	}
	else if( m_bChangeActive 
		&& IsUIStateKey( SELECTION_UI_MODE, MAKE_ACTIVE_UI_STATE, rEvent.m_nKey ) )
	{
		m_bChangeActive = FALSE;
		
		VERIFY( RemoveListenUIStateKey( SELECTION_UI_MODE, MAKE_ACTIVE_UI_STATE ) );
		return TRUE;
	}
	
	return FALSE;
}

BOOL CGISelectionTool::IsUIStateKey( INT nMode, INT nState, UINT nChar )
{
	if( SELECTION_UI_MODE == nMode )
	{
		switch( nState )
		{
		case MULTIPLE_SELECTION_UI_STATE:
			return VK_CONTROL == nChar;

		case MAKE_ACTIVE_UI_STATE:
			return VK_SHIFT == nChar;
		}
	}

	return CGIZoomPanTool::IsUIStateKey( nMode, nState, nChar );
}

UINT CGISelectionTool::GetUIStateKey( INT nMode, INT nState )
{
	if( SELECTION_UI_MODE == nMode )
	{
		switch( nState )
		{
		case MULTIPLE_SELECTION_UI_STATE:
			return VK_CONTROL;

		case MAKE_ACTIVE_UI_STATE:
			return VK_SHIFT;
		}
	}

	return CGIZoomPanTool::GetUIStateKey( nMode, nState );
}

// Return value 
// 0   - Not processed, can continue with another type selection 
//       say for ex. Rectangle selection
// 1   - Selection completed or changed
// -1  - Give control to the Focused Tool
INT CGISelectionTool::Select( const CPoint& rpoint, 
							  INT nFlags /*= ESF_NO_START_SELECTION 
										   | ESF_NO_END_SELECTION*/ )
{
	UINT nHitTest;
	CGIElement* piElement = NULL;
	INT nSelectionCount = GetSelectedCount();

	// If atleast one element is selected, first hitTest the Focused element.
	if( nSelectionCount )
	{
		nHitTest = m_pFocusTool->HitTest( rpoint );
		if( CGIElementUITool::HT_NOTHING != nHitTest )
		{
			// If the selection option ESF_MAKE_ACTIVE or ESF_MULTIPLE_SELECTION is TRUE, 
			// it needs to change the hitted element
			if( (ESF_MAKE_ACTIVE | ESF_MULTIPLE_SELECTION) & nFlags )
			{
				CGIElementUITool* pElementTool = HitTestTools( rpoint, nHitTest );
				if( pElementTool )
				{	
					piElement = pElementTool->m_piElement;
					goto LBChangeSelection;
				}
			}

			// Otherwise, transfer UI to the Focus tool
			return -1;
		}
	}

	piElement = HitTestGroupElements( rpoint, nHitTest );
	if( piElement )
	{
LBChangeSelection:;
		ChangeSelection( *piElement, nFlags );
		return 1;
	}
	
	// If one or more element(s) selected and the selection is not ESF_MULTIPLE_SELECTION
	if( nSelectionCount && 0 == (ESF_MULTIPLE_SELECTION & nFlags) )
	{
		if( 0 == (ESF_NO_START_SELECTION & nFlags) )
			StartSelection();

		DeselectAll();

		if( 0 == (ESF_NO_END_SELECTION & nFlags) )
			EndSelection();
	}

	return 0;
}

BOOL CGISelectionTool::Select( const CRect& rrct, 
							   INT nFlags /*= ESF_NO_START_SELECTION 
							                | ESF_NO_END_SELECTION*/ )
{
	CPtrArray arpElement;
	INT nCount = HitTestGroupElements( rrct, arpElement );
	if( 0 == nCount )
		return FALSE;

	CGRectF grctf = rrct;
	if( FALSE == SelectionPick( arpElement, grctf, ESF_MULTIPLE_SELECTION  ) )
		return FALSE;

	BOOL bStartSelection = FALSE;
	nCount = arpElement.GetSize();
	if( nCount )
	{
		CGIElement** ppiElement = (CGIElement**)arpElement.GetData();
		for( INT i = 0; i < nCount; i++ )
		{
			if( ChangeSelection( *ppiElement[i], ESF_MULTIPLE_SELECTION 
				                               | ESF_NO_UPDATE_SELECTION | nFlags ) )
				bStartSelection = TRUE;
		}

		if( bStartSelection )
		{
			UpdateSelection();
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CGISelectionTool::Deselect( const CPoint& rpoint )
{
	UINT nHitTest;
	CGIElement* piElement = HitTestGroupElements( rpoint, nHitTest);
	if( NULL == piElement )
		return FALSE;

	return RemoveSelection( *piElement );
}

BOOL CGISelectionTool::Deselect( const CRect& rrct )
{
	CPtrArray arpElement;
	INT nCount = HitTestGroupElements( rrct, arpElement );
	if( 0 == nCount )
		return FALSE;

	CGIElement** ppiElement = (CGIElement**)arpElement.GetData();
	for( INT i = 0; i < nCount; i++ )
		RemoveSelection( *ppiElement[i], FALSE );

	UpdateSelection();
	return TRUE;
}

CGIElementUITool* CGISelectionTool::HitTestTools( const CPoint& rpoint, 
												  UINT& rnHitTest ) const
{
	INT nCount = m_GroupTool.m_arpTool.GetSize();
	CGIElementUITool** ppElementTool 
			= (CGIElementUITool**)m_GroupTool.m_arpTool.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		rnHitTest = ppElementTool[i]->HitTest( rpoint );
		if( CGIElementUITool::HT_NOTHING != rnHitTest )
			return ppElementTool[i];
	}

	return NULL;
}

CGIElement* CGISelectionTool::HitTestGroupElements( const CPoint& rpoint, 
												     UINT& rnHitTest ) const
{
	if( NULL == m_piActiveGroup )
		return NULL;

	Matrix mtx;
	if( m_pView )
		m_pView->GetCTM( mtx );

	CGIElement* piElement;
	CGINode* piNode = m_piActiveGroup->GetLast();
	while( piNode )
	{
		if( piNode->IsDerivedFrom( CGIElement::GetClassType() ) )
		{
			piElement = (CGIElement*)piNode;
			rnHitTest = piElement->HitTest( rpoint, &mtx );
			if( CGIElementUITool::HT_NOTHING != rnHitTest )
				return piElement;
		}

		piNode = piNode->GetPrev();
	}

	return NULL;
}

INT CGISelectionTool::HitTestGroupElements( const CRect& rrct, CPtrArray& rarpElement )
{
	if( NULL == m_piActiveGroup )
		return NULL;

	Matrix mtx;
	if( m_pView )
		m_pView->GetCTM( mtx );

	UINT nHitTest;
	CGIElement* piElement;
	CGINode* piNode = m_piActiveGroup->GetFirst();
	while( piNode )
	{
		if( piNode->IsDerivedFrom( CGIElement::GetClassType() ) )
		{
			piElement = (CGIElement*)piNode;
			nHitTest = piElement->HitTest( rrct, &mtx );
			if( CGIElementUITool::HT_NOTHING != nHitTest )
				rarpElement.Add( piElement );
		}

		piNode = piNode->GetNext();
	}

	return rarpElement.GetSize();
}

INT CGISelectionTool::SelectAll()
{
	CPtrArray arpElementTool;
	arpElementTool.Copy( m_GroupTool.m_arpTool );	// Take of Tool array, 
													// it will be modified 
													// on each call of AddSelection

	CGIElementUITool** ppiElementTool = (CGIElementUITool**)arpElementTool.GetData();
	INT i, nElementToolSize = arpElementTool.GetSize();

	CGIElement* piElement;
	CGINode* piNode = m_piActiveGroup->GetFirst();
	while( piNode )
	{
		if( piNode->IsDerivedFrom( CGIElement::GetClassType() ) )
		{
			piElement = (CGIElement*)piNode;
			for( i = 0; i < nElementToolSize; i++ )
			{
				if( ppiElementTool[i]->m_piElement == piElement )
					break;
			}
			
			// Is already selected
			if( i < nElementToolSize )
				AddSelection( *piElement, FALSE );
		}

		piNode = piNode->GetNext();
	}

	UpdateSelection();
	return m_GroupTool.m_arpTool.GetSize();
}

BOOL CGISelectionTool::DeselectAll()
{
	INT nCount = m_GroupTool.m_arpTool.GetSize();
	if( 0 == nCount )
		return FALSE;

	CPtrArray arpElementTool;
	arpElementTool.Copy( m_GroupTool.m_arpTool );	// Take copy of Tool array, it will be 
													// modified on each call of RemoveSelection

	CGIElementUITool** ppiElementTool = (CGIElementUITool**)arpElementTool.GetData();
	for( INT i = 0; i < nCount; i++ )
		RemoveSelection( *ppiElementTool[i]->m_piElement, FALSE );

	UpdateSelection();
	m_pActiveTool = NULL;
	m_pFocusTool = NULL;

	return TRUE;
}

BOOL CGISelectionTool::AddSelection( CGIElement& rElement, BOOL bUpdate /*= TRUE*/ ) 
{
	// If the Shape Element is already selected, leave now
	if( m_GroupTool.GetElementTool( rElement ) )
		return FALSE;

	// If Listener is not allowing the selection of the given Shape Element,
	// don't select it
	CGSelectionEvent event;
	event.InitEvent( CGSelectionEvent::SELECT, rElement );
	m_piActiveGroup->DispatchEvent( event );
	if( event.GetPreventDefault() )
		return FALSE;

	CGIElementUITool* piElementTool;
	if( m_pDefaultElementTool && m_pDefaultElementTool->m_piElement == &rElement )
		piElementTool = m_pDefaultElementTool;
	else
	{
		piElementTool = CreateElementTool( rElement );
		if( NULL == piElementTool )
		{
			ASSERT( FALSE );
			return FALSE;
		}
	}

	if( piElementTool )
	{
		piElementTool->m_piElement = &rElement;
		piElementTool->SetViewWindow( m_pwndView );
		piElementTool->SetView( m_pView );
		
		m_GroupTool.AddTool( *piElementTool );
		m_pActiveTool = piElementTool;
		m_pActiveTool->SetSelection();
		m_pActiveTool->InvalidateRect();
		if( m_pView )
			m_pView->SetModified();
	}

	if( bUpdate )
		UpdateSelection();

	return TRUE;
}

BOOL CGISelectionTool::RemoveSelection( CGIElement& rElement, BOOL bUpdate /*= TRUE*/ ) 
{
	// If the given Shape Element is not selected, leave now
	CGIElementUITool* piElementTool = m_GroupTool.GetElementTool( rElement );
	if( NULL == piElementTool )
		return FALSE;

	// If Listener is not allowing the deselection of the given Shape Element,
	// don't deselect it
	CGSelectionEvent event;
	event.InitEvent( CGSelectionEvent::DESELECT, rElement );
	m_piActiveGroup->DispatchEvent( event );
	if( event.GetPreventDefault() )
		return FALSE;

	piElementTool->InvalidateRect();
	piElementTool->SetSelection( FALSE );
	m_GroupTool.RemoveTool( *piElementTool );
	if( m_pView )
		m_pView->SetModified();

	if( bUpdate )
		UpdateSelection();

	return TRUE;
}

BOOL CGISelectionTool::ChangeSelection( CGIElement& rElement, INT nFlags /*= ESF_NONE*/ )
{
	BOOL bUpdateSelection = 0 == (ESF_NO_UPDATE_SELECTION & nFlags);
	BOOL bStartSelection = 0 == (ESF_NO_START_SELECTION & nFlags);
	BOOL bEndSelection = 0 == (ESF_NO_END_SELECTION & nFlags);
	BOOL bMultipleSelection = 0 != (ESF_MULTIPLE_SELECTION & nFlags);
	
	INT nSelectionCount = GetSelectedCount();
	if( nSelectionCount )
	{
		CGIElementUITool* pElementTool = m_GroupTool.GetElementTool( rElement );

		if( ESF_MAKE_ACTIVE & nFlags )
		{
			if( pElementTool )
			{
				if( pElementTool == m_pActiveTool )
					return TRUE;

				m_pActiveTool->InvalidateRect();
				pElementTool->InvalidateRect();
				m_pActiveTool = pElementTool;
				return TRUE;
			}
		}

		if( pElementTool && bMultipleSelection )
		{
			if( bStartSelection )
				StartSelection();

			RemoveSelection( rElement, bUpdateSelection );

			if( bEndSelection )
				EndSelection();	

			return TRUE;
		}
	}

	if( bStartSelection )
		StartSelection();

	if( FALSE == bMultipleSelection && nSelectionCount )
		DeselectAll();
	
	BOOL bResult = AddSelection( rElement, bUpdateSelection );

	if( bEndSelection )
		EndSelection();

	return bResult;
}

void CGISelectionTool::UpdateSelection()
{
	INT nSelectionCount = GetSelectedCount();
	if( nSelectionCount )
	{
		m_pActiveTool = (CGIElementUITool*)m_GroupTool.m_arpTool.GetAt( nSelectionCount - 1 );
		m_pFocusTool = 1 == nSelectionCount ?m_pActiveTool :&m_GroupTool;
	}
	else
		m_pFocusTool = m_pActiveTool = NULL;
}

void CGISelectionTool::StartSelection()
{
	// For Call back there is no use without Active Group
	if( NULL == m_piActiveGroup )
		return;

	// If already Start Selection Call back processed, leave now.
	if( m_bStartSelectionCalled )
		return;

	m_bStartSelectionCalled = TRUE;

	CGSelectionEvent event;
	event.InitEvent( CGSelectionEvent::START_SELECTION );
	m_piActiveGroup->DispatchEvent( event );
}

void CGISelectionTool::EndSelection() 
{
	// Without having called Start Selection, calling
	// the End Selection there is no action required
	if( FALSE == m_bStartSelectionCalled )
	{
		ASSERT( FALSE );
		return;
	}

	m_bStartSelectionCalled = FALSE;

	CGSelectionEvent event;
	event.InitEvent( CGSelectionEvent::END_SELECTION );
	m_piActiveGroup->DispatchEvent( event );
}

BOOL CGISelectionTool::SelectionPick( CPtrArray& _rarShapeElement, const GRectF& rrctf, INT nFlags /*= ESF_NONE*/ )
{
	CGSelectionEvent event;
	event.InitEvent( CGSelectionEvent::SELECTION_PICK, &_rarShapeElement, &rrctf );
	m_piActiveGroup->DispatchEvent( event );

	_rarShapeElement.RemoveAll();
	_rarShapeElement.Copy( event.GetShapeElementArray() );
	return TRUE;
}