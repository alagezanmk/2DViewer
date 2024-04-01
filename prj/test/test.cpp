#include "stdafx.h"
#include "test.h"

#include "MainFrm.h"
#include "TestBldChildFrm.h"
#include "testBldDoc.h"
#include "testBldView.h"

#include "TestViewChildFrm.h"
#include "testViewDoc.h"
#include "testViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CTestApp, CBldApp)
	//{{AFX_MSG_MAP(CTestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND( ID_FILE_NEW, OnFileNew )
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CBldApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CBldApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CBldApp::OnFilePrintSetup)
END_MESSAGE_MAP()

CTestApp::CTestApp()
{}

CTestApp theApp;

BOOL CTestApp::InitInstance()
{
	if( FALSE == CBldApp::InitInstance() )
		return FALSE;

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

//#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
//#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
//#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey( _T( "Local AppWizard-Generated Applications" ) );

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate( IDR_TESTTYPE, RUNTIME_CLASS( CTestBldDoc ), RUNTIME_CLASS( CTestBldChildFrm ), // custom MDI child frame
						RUNTIME_CLASS( CTestBldView ) );

	AddDocTemplate( pDocTemplate );

	pDocTemplate = new CMultiDocTemplate( IDR_TESTVIEWTYPE, RUNTIME_CLASS( CTestViewDoc ), RUNTIME_CLASS( CTestViewChildFrm ), // custom MDI child frame
		RUNTIME_CLASS( CTestViewView ) );

	AddDocTemplate( pDocTemplate );

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if( !pMainFrame->LoadFrame( IDR_MAINFRAME ) )
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine( cmdInfo );

	// Dispatch commands specified on the command line
	if( !ProcessShellCommand( cmdInfo ) )
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow( m_nCmdShow );
	pMainFrame->UpdateWindow();

	return TRUE;
}

BOOL CTestApp::ExitInstance() {
	return CBldApp::ExitInstance(); }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg()
	 : CDialog( CAboutDlg::IDD )
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CTestApp::OnFileNew()
{
	if( m_pDocManager )
	{
		POSITION posDoc = m_pDocManager->GetFirstDocTemplatePosition();
		if( posDoc )
		{
			CDocTemplate* pTemplate = m_pDocManager->GetNextDocTemplate( posDoc );
			
			// Create Builder Type Doc view
			CDocument* pDocument = pTemplate->OpenDocumentFile( NULL );
			POSITION posView = pDocument->GetFirstViewPosition();
			if( posView )
			{
				CView* pView = pDocument->GetNextView( posView );
				ASSERT( pView );
				
				CGEditView* pEditView = (CGEditView*)pView;
				CGIDocument* pDomDocument = pEditView->GetDomDocument();
				ASSERT( pDomDocument );
				
				if( posDoc && 1 )
				{
					// Create Viewer Type Doc view
					pTemplate = m_pDocManager->GetNextDocTemplate( posDoc );	
					pDocument = pTemplate->OpenDocumentFile( NULL );
					
					POSITION posView = pDocument->GetFirstViewPosition();
					if( posView )
					{
						pView = pDocument->GetNextView( posView );
						ASSERT( pView );
						
						CTestViewView* pEditView = (CTestViewView*)pView;
						pEditView->m_pwndView->SetDocument( pDomDocument );
					}
				}
			}	
		}
	}
}