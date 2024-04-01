#include "stdafx.h"
#include <bld\bView.h>
#include <bld\bMainFrm.h>
#include <cu\msg.h>
#include <bld\page.h>
#include <bld\layer.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGEditView, CView)
BEGIN_MESSAGE_MAP(CGEditView, CView)
	//{{AFX_MSG_MAP(CGEditView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSKEYUP()
	ONC_MSG( CM_KEY_DOWN, OnKeyDownMsg )
	ONC_MSG( CM_KEY_UP, OnKeyUpMsg )
	ONC_CMD( CM_SV_VIEW_ACTIVATE, OnViewActivate )
	ONC_CMD( CM_LC_BUTTON_CLICK, OnLayerCtrlCmd )
	ONC_MSG( CM_LC_LAYER_SEL, OnLayerSelChange )
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGEditView::CGEditView() 
{
	m_pwndEdit = NULL; 
	m_pLayerCtrl = NULL;
}

CGEditView::~CGEditView()
{
	if( m_pwndEdit )
	{
		RemoveChild( *m_pwndEdit );
		delete m_pwndEdit;
	}
}

int CGEditView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if( 1 == AfsSendMsg( AfxGetMainWnd(), CM_MF_VIEW_ADD, (WPARAM)this ) )
		AfsSendMsg( AfxGetMainWnd(), CM_MF_VIEW_ACTIVATE, (WPARAM)this );

	ModifyStyle( 0, WS_CLIPCHILDREN );

	if( NULL == m_pwndEdit )
		VERIFY( m_pwndEdit = new CGEditWnd );

	if( m_pwndEdit && NULL == m_pwndEdit->m_hWnd )
	{
		AppendChild( *m_pwndEdit );
		if( FALSE == m_pwndEdit->Create( this, EID_EDIT_WND, CRect(0, 0, 100, 100) ) )
			return FALSE;
	}

	return 0;
}

void CGEditView::OnSize( UINT nType, int cx, int cy )
{
	CView::OnSize( nType, cx, cy );
	if( m_pwndEdit && m_pwndEdit->m_hWnd )
		m_pwndEdit->MoveWindow( 0, 0, cx, cy );
}

BOOL CGEditView::OnEraseBkgnd( CDC* pDC ) {
	return TRUE; }

void CGEditView::OnPrint( CDC* pDC, CPrintInfo* pPrintInfo )
{
	ASSERT_VALID(pDC);
	CGViewWnd* pViewWnd = GetViewWindow();
	Graphics gdip( pDC->m_hDC );
	gdip.ScaleTransform( 100 / 96, 100 / 96 );
	gdip.ScaleTransform( 2.25 / 1.5, 2.25 / 1.5 );

	CRect rcPrint = pPrintInfo->m_rectDraw;

	INT nCCx = rcPrint.right;
	INT nCCy = rcPrint.bottom;

	COLORREF crfAppWrkSpace = GetSysColor( COLOR_APPWORKSPACE );
	SolidBrush gbrAppWkrSpace( Color( 255, GetRValue( crfAppWrkSpace ), GetGValue( crfAppWrkSpace ), GetBValue( crfAppWrkSpace ) ) );
	//gdip.FillRectangle( &gbrAppWkrSpace, 0, 0, nCCx, nCCy );

	gdip.SetCompositingQuality( CompositingQualityHighQuality );
	gdip.SetSmoothingMode( SmoothingModeAntiAlias );

	pViewWnd->DrawView( gdip, rcPrint, pPrintInfo->m_bPreview );
}

void CGEditView::OnDraw(CDC* pDC)
{}

BOOL CGEditView::OnPreparePrinting(CPrintInfo* pInfo) {
	return DoPreparePrinting( pInfo ); }

void CGEditView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{}

void CGEditView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}

LRESULT CGEditView::OnKeyDownMsg( WPARAM wParam, LPARAM lParam ) {
	return HandleKeyboardEvent( m_hWnd, WM_KEYDOWN, wParam, lParam ); }

LRESULT CGEditView::OnKeyUpMsg( WPARAM wParam, LPARAM lParam ) {
	return HandleKeyboardEvent( m_hWnd, WM_KEYUP, wParam, lParam ); }

void CGEditView::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )  
{
	if( HandleKeyboardEvent( m_hWnd, WM_KEYDOWN, nChar, nRepCnt, nFlags ) )
		return;

	CWnd* pMainWnd = AfxGetMainWnd();
	AfsSendMsg( pMainWnd, CM_KEY_DOWN, nChar, MAKELPARAM( nRepCnt, nFlags ) );
}

void CGEditView::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags ) 
{
	if( HandleKeyboardEvent( m_hWnd, WM_KEYUP, nChar, nRepCnt, nFlags ) )
		return;

	CWnd* pMainWnd = AfxGetMainWnd();
	AfsSendMsg( pMainWnd, CM_KEY_UP, nChar, MAKELPARAM( nRepCnt, nFlags ) );
}
	
void CGEditView::OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )  
{
	if( HandleKeyboardEvent( m_hWnd, WM_KEYDOWN, nChar, nRepCnt, nFlags ) )
		return;

	CWnd* pMainWnd = AfxGetMainWnd();
	AfsSendMsg( pMainWnd, CM_SYS_KEY_DOWN, nChar, MAKELPARAM( nRepCnt, nFlags ) );
}

void CGEditView::OnSysKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if( HandleKeyboardEvent( m_hWnd, WM_KEYUP, nChar, nRepCnt, nFlags )	)
		return;

	CWnd* pMainWnd = AfxGetMainWnd();
	AfsSendMsg( pMainWnd, CM_SYS_KEY_UP, nChar, MAKELPARAM( nRepCnt, nFlags ) );
}
	
BOOL CGEditView::OnKeyDown( const CKbdEvent& rEvent )
{
	if( m_pwndEdit )
	{
		CGViewWnd* pViewWnd = m_pwndEdit->GetViewWindow();
		if( pViewWnd )
			return pViewWnd->OnKeyDown( rEvent );

		CGPlayWnd* pPlayWnd = m_pwndEdit->GetPlayWindow();
		if( pPlayWnd )
			return pPlayWnd->OnKeyDown( rEvent );
		
		if( m_pwndEdit->OnKeyDown( rEvent ) )
			return TRUE;
	}

	return FALSE;
}

BOOL CGEditView::OnKeyUp( const CKbdEvent& rEvent )
{
	if( m_pwndEdit )
	{
		CGViewWnd* pViewWnd = m_pwndEdit->GetViewWindow();
		if( pViewWnd )
			return pViewWnd->OnKeyUp( rEvent );
			
		CGPlayWnd* pPlayWnd = m_pwndEdit->GetPlayWindow();
		if( pPlayWnd )
			return pPlayWnd->OnKeyUp( rEvent );
			
		if( m_pwndEdit->OnKeyUp( rEvent ) )
			return TRUE;
	}

	return FALSE;
}

const CGIEditView* CGEditView::GetView() const
{
	const CGViewWnd* pwndView = GetViewWindow();
	if( pwndView )
		return (CGIEditView*)pwndView->m_pView;

	return NULL;
}

const CGIDocument* CGEditView::GetDomDocument() const
{
	const CGViewWnd* pwndView = GetViewWindow();
	if( pwndView )
		return pwndView->GetDocument();

	return NULL;
}

const CGViewWnd* CGEditView::GetViewWindow() const 
{
	const CGPlayWnd* pwndPlay = GetPlayWindow();
	if( pwndPlay )
			return pwndPlay->GetViewWindow();

	return NULL;
}

const CGPlayWnd* CGEditView::GetPlayWindow() const
{
	if( m_pwndEdit )
		return m_pwndEdit->GetPlayWindow();

	return NULL;
}

void CGEditView::OnDestroy()
{
	BOOL bAnotherViewThere = FALSE;

	// Check another view is there
	CMDIFrameWnd* pFrameWnd = (CMDIFrameWnd*)AfxGetMainWnd();
	CMDIChildWnd* pChildWnd = pFrameWnd->MDIGetActive();
	if( pChildWnd )
	{
		CView* pView = pChildWnd->GetActiveView();
		if( pView )
			bAnotherViewThere = TRUE;
	}

	// If this is last view, empty the Navigation info
	if( FALSE == bAnotherViewThere )
	{
		OnDestroyLastView();
		AfsSendMsg( AfxGetMainWnd(), CM_MF_VIEW_ACTIVATE, (WPARAM)NULL );
	}

	AfsSendMsg( AfxGetMainWnd(), CM_MF_VIEW_CLOSE, (WPARAM)this );
	OnDestroyView();
	CView::OnDestroy();
}

void CGEditView::OnViewActivate( UINT nCmd )
{
	if( nCmd )
		OnGetFocusView();
	else
		OnKillFocusView();
}

void CGEditView::OnGetFocusView()
{
	CBldMainFrm* pMainFrm = (CBldMainFrm*)AfxGetMainWnd();
	m_pLayerCtrl = NULL;
	
	CObjLayerBar* pLayerBar = pMainFrm->GetLayerBar();
	if( pLayerBar )
		m_pLayerCtrl = &pLayerBar->GetLayerCtrl();

	if( m_pLayerCtrl )
	{
		m_pLayerCtrl->Connect( m_hWnd );
		FillLayerBar();
	}
}

void CGEditView::OnKillFocusView() {
	ResetLayerBar(); }

void CGEditView::OnDestroyLastView() {
	ResetLayerBar(); }

void CGEditView::OnDestroyView()
{}

void CGEditView::FillLayerBar()
{
	if( NULL == m_pLayerCtrl )
		return;

	m_pLayerCtrl->ResetContent();
	CGIDocument* pDocument = GetDomDocument();
	if( NULL == pDocument )
		return;

	CGINode* pNode = pDocument->GetFirst();
	if( pNode && pNode->IsDerivedFrom( CGIPage::GetClassType() ) )
	{
		CGIPage* pPage = (CGIPage*)pNode;
		pNode = pPage->GetFirst();
		CGILayer* pLayer;
		while( pNode )
		{
			if( pNode && pNode->IsDerivedFrom( CGILayer::GetClassType() ) )
			{
				pLayer = (CGILayer*)pNode;
				CString cszName = pLayer->m_aID;
				m_pLayerCtrl->Add( pLayer, cszName );
			}

			pNode = pNode->GetNext();
		}
	}

	CGEditWnd* pwndEdit = GetEditWindow();
	ASSERT( pwndEdit );
	pNode = pwndEdit->GetActiveGroup();
	if( pNode && pNode->IsDerivedFrom( CGILayer::GetClassType() ) )
		m_pLayerCtrl->SetCurSel( (CGILayer*)pNode );
}

void CGEditView::ResetLayerBar()
{
	if( NULL == m_pLayerCtrl )
		return;

	m_pLayerCtrl->ResetContent();
}

void CGEditView::OnLayerCtrlCmd( UINT nID )
{
	if( NULL == m_pLayerCtrl )
		return;

	CGIDocument* pDocument = GetDomDocument();
	if( NULL == pDocument )
		return;

	CGINode* pNode = pDocument->GetFirst();
	if( NULL == pNode || FALSE == pNode->IsDerivedFrom( CGIPage::GetClassType() ) )
		return;

	CGIPage* pPage = (CGIPage*)pNode;

	/*if( CObjLayerCtrl::NEW_LAYER_GROUP == nID )
	{
		ASSERT( m_pCurPage );
		CObjLayerGrp* pLayerGrp = CreateLayerGrp();
		ASSERT( pLayerGrp );
	}
	else*/ if( CObjLayerCtrl::NEW_LAYER == nID )
	{
		CGILayer* pLayer = (CGILayer*)pDocument->CreateElement( CGILayer::ELEMENT_TAGNAME );
		ASSERT( pLayer );
		pPage->AppendChild( *pLayer );

		pLayer->m_aX = 0;
		pLayer->m_aY = 0;
		pLayer->m_aWidth = 100;
		pLayer->m_aHeight = 100;

		CString cszName = pLayer->m_aID;
		m_pLayerCtrl->Add( pLayer, cszName );

		m_pLayerCtrl->SetCurSel( pLayer );

		CGEditWnd* pwndEdit = GetEditWindow();
		ASSERT( pwndEdit );
		pwndEdit->SetActiveGroup( pLayer );
	}
	else if( CObjLayerCtrl::DELETE_LAYER == nID )
	{
		/*if( 1 == m_pCurPage->GetSize() )
		{
			AfxMessageBox( _T("Cannot delete this Layer or Layer Group.\n")
						   _T("Alteast one Layer or Layer Group should be there"), 
						   MB_ICONEXCLAMATION );
			return;
		}*/

		//DeleteLayer( m_pCurLayer );
	}
}

LRESULT CGEditView::OnLayerSelChange( WPARAM wParam, LPARAM lParam )
{
	INT nIndex = wParam;
	CGILayer* pLayer = (CGILayer*)m_pLayerCtrl->GetAt( nIndex );
	CGIDocument* pDocument = pLayer->GetOwnerDocument();
	if( pDocument == GetDomDocument() )
	{
		CGEditWnd* pwndEdit = GetEditWindow();
		ASSERT( pwndEdit );
		pwndEdit->SetActiveGroup( pLayer );
	}
	
	return 1;
}

