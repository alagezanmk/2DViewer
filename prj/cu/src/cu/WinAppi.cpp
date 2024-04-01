#include "stdafx.h"
#include <cu\WinAppi.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CIWinApp, CWinApp)
BEGIN_MESSAGE_MAP(CIWinApp, CWinApp)
	//{{AFX_MSG_MAP(CIWinApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CIWinApp::CIWinApp()
{}

CIWinApp::~CIWinApp()
{}

/// Should be called at starting of the overrided function in derived class
BOOL CIWinApp::InitInstance() {
	return TRUE; }

/// Should be called at end of the overrided function in derived class
int CIWinApp::ExitInstance() {
	return CWinApp::ExitInstance(); }
