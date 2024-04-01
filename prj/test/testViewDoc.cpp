#include "stdafx.h"
#include "test.h"

#include "testViewDoc.h"
#include "testViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CTestViewDoc, CDocument)
BEGIN_MESSAGE_MAP(CTestViewDoc, CDocument)
	//{{AFX_MSG_MAP(CTestDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTestViewDoc::CTestViewDoc()
{
}

CTestViewDoc::~CTestViewDoc()
{
}

#ifdef _DEBUG
void CTestViewDoc::AssertValid() const {
	CDocument::AssertValid(); }

void CTestViewDoc::Dump( CDumpContext& dc ) const {
	CDocument::Dump( dc ); }
#endif //_DEBUG

void CTestViewDoc::Serialize( CArchive& ar )
{
	if( ar.IsStoring() )
	{	}
	else
	{	}
}


BOOL CTestViewDoc::OnSaveDocument( LPCTSTR lpszPathName )
{
	return TRUE;
}
	
BOOL CTestViewDoc::OnNewDocument()
{
	if( !CDocument::OnNewDocument() )
		return FALSE;

	return TRUE;
}

BOOL CTestViewDoc::OnOpenDocument( LPCTSTR lpszPathName )
{
	return TRUE;
}