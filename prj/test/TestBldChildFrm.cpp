#include "stdafx.h"
#include "test.h"

#include "TestBldChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CTestBldChildFrm, CIChildFrm )
BEGIN_MESSAGE_MAP(CTestBldChildFrm, CIChildFrm)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTestBldChildFrm::CTestBldChildFrm()
{}

CTestBldChildFrm::~CTestBldChildFrm()
{}

BOOL CTestBldChildFrm::PreCreateWindow( CREATESTRUCT& cs )
{
	if( !CIChildFrm::PreCreateWindow( cs ) )
		return FALSE;

	return TRUE;
}

#ifdef _DEBUG
void CTestBldChildFrm::AssertValid() const {
	CIChildFrm::AssertValid(); }

void CTestBldChildFrm::Dump( CDumpContext& dc ) const {
	CIChildFrm::Dump( dc ); }
#endif //_DEBUG

int CTestBldChildFrm::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CIChildFrm::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	ModifyStyle( 0, WS_CLIPCHILDREN );
	if( FALSE == m_wndDlgBar.Create( this, IDD_EXPLORER_BAR, CBRS_LEFT, IDD_EXPLORER_BAR ) )
	{
		TRACE( "CChildFrame::Dialog Bar creation failed\n" );
		return -1;
	}

	m_wndDlgBar.ModifyStyle( 0, WS_CLIPCHILDREN );

	return 0;
}
