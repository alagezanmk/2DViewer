#include "stdafx.h"
#include "test.h"

#include "TestViewChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CTestViewChildFrm, CMDIChildWnd )
BEGIN_MESSAGE_MAP(CTestViewChildFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTestViewChildFrm::CTestViewChildFrm()
{}

CTestViewChildFrm::~CTestViewChildFrm()
{}

BOOL CTestViewChildFrm::PreCreateWindow( CREATESTRUCT& cs )
{
	if( !CMDIChildWnd::PreCreateWindow( cs ) )
		return FALSE;

	return TRUE;
}

#ifdef _DEBUG
void CTestViewChildFrm::AssertValid() const {
	CMDIChildWnd::AssertValid(); }

void CTestViewChildFrm::Dump( CDumpContext& dc ) const {
	CMDIChildWnd::Dump( dc ); }
#endif //_DEBUG

int CTestViewChildFrm::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}
