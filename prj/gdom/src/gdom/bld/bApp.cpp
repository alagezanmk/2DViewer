#include "stdafx.h"
#include <bld\bApp.h>
#include <bld\bView.h>

#include <gl\WinGC.h>
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CBldApp, CIWinApp)
	//{{AFX_MSG_MAP(CBldApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CBldApp::CBldApp()
{}

static GdiplusStartupInput gs_gdiplusStartupInput;
static ULONG_PTR           gs_gdiplusToken;
BOOL CBldApp::InitInstance() 
{
	// Initialize GDI+
	GdiplusStartup( &gs_gdiplusToken, &gs_gdiplusStartupInput, NULL );

	InitGC();
	return TRUE; 
}

BOOL CBldApp::ExitInstance()
{
	ReleaseGC();
	GdiplusShutdown( gs_gdiplusToken );
	return CWinApp::ExitInstance();
}
