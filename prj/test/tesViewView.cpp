#include "stdafx.h"
#include "test.h"
#include <cu\msg.h>

#include "testViewDoc.h"
#include "testViewView.h"
#include "TestViewChildFrm.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CTestViewView, CView )
BEGIN_MESSAGE_MAP(CTestViewView, CView)
	//{{AFX_MSG_MAP(CTestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSKEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTestViewView::CTestViewView()
{
	m_pwndView = NULL;
	m_pgView = NULL;
}

CTestViewView::~CTestViewView()
{
	if( m_pwndView )
		delete m_pwndView;

	if( m_pgView )
		m_pgView->Release();
}

void CTestViewView::OnDraw( CDC* pDC )
{
	CTestViewDoc* pDoc = GetDocument();
	ASSERT_VALID( pDoc );
}

#ifdef _DEBUG
void CTestViewView::AssertValid() const {
	CView::AssertValid(); }

void CTestViewView::Dump( CDumpContext& dc ) const {
	CView::Dump( dc ); }

CTestViewDoc* CTestViewView::GetDocument() // non-debug version is inline
{
	ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS( CTestViewDoc ) ) );
	return ( CTestViewDoc * ) m_pDocument;
}
#endif //_DEBUG


void CTestViewView::OnInitialUpdate() 
{
	CView::OnInitialUpdate(); 
}

int CTestViewView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	ASSERT( NULL == m_pgView );
	VERIFY( m_pgView = new CGIView );
	m_pgView->AddRef();
	
	ASSERT( NULL == m_pwndView );
	VERIFY( m_pwndView = new CGViewWnd );
	
	m_pwndView->SetView( *m_pgView );

	FLOAT cx = m_pgView->m_aDocWidth;
	FLOAT cy = m_pgView->m_aDocHeight;
	
	VERIFY( m_pwndView->Create( NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, 1000 ) );
	m_pwndView->OnInitialUpdate();
	
	CRect rctClient;
	GetClientRect( rctClient );
	m_pwndView->MoveWindow( 0, 0, rctClient.Width(), rctClient.Height() );
	
	m_pwndView->MoveWindow( 0, 0, 400, 200 );
	m_pwndView->SetScrollSizes( 300, 200 );

	return 0;
}

void CTestViewView::OnDestroy()
{
	CView::OnDestroy();
}

void CTestViewView::OnSize( UINT nType, int cx, int cy )
{
	CView::OnSize( nType, cx, cy );

	if( m_pwndView && m_pwndView->m_hWnd )
		m_pwndView->MoveWindow( 0, 0, cx, cy );
}

void CTestViewView::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )  
{
	if( HandleKeyboardEvent( m_hWnd, WM_KEYDOWN, nChar, nRepCnt, nFlags ) )
		return;
	
	CWnd* pMainWnd = AfxGetMainWnd();
	AfsSendMsg( pMainWnd, CM_KEY_DOWN, nChar, MAKELPARAM( nRepCnt, nFlags ) );
}

void CTestViewView::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags ) 
{
	if( HandleKeyboardEvent( m_hWnd, WM_KEYUP, nChar, nRepCnt, nFlags ) )
		return;
	
	CWnd* pMainWnd = AfxGetMainWnd();
	AfsSendMsg( pMainWnd, CM_KEY_UP, nChar, MAKELPARAM( nRepCnt, nFlags ) );
}

BOOL CTestViewView::OnKeyDown( const CKbdEvent& rEvent )
{
	if( m_pwndView )
		return m_pwndView->OnKeyDown( rEvent );
	
	return FALSE;
}

BOOL CTestViewView::OnKeyUp( const CKbdEvent& rEvent )
{
	if( m_pwndView )
		return m_pwndView->OnKeyUp( rEvent );
	
	return FALSE;
}

void CTestViewView::OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )  
{
	if( HandleKeyboardEvent( m_hWnd, WM_KEYDOWN, nChar, nRepCnt, nFlags ) )
		return;
	
	CWnd* pMainWnd = AfxGetMainWnd();
	AfsSendMsg( pMainWnd, CM_SYS_KEY_DOWN, nChar, MAKELPARAM( nRepCnt, nFlags ) );
}

void CTestViewView::OnSysKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if( HandleKeyboardEvent( m_hWnd, WM_KEYUP, nChar, nRepCnt, nFlags )	)
		return;
	
	CWnd* pMainWnd = AfxGetMainWnd();
	AfsSendMsg( pMainWnd, CM_SYS_KEY_UP, nChar, MAKELPARAM( nRepCnt, nFlags ) );
}
