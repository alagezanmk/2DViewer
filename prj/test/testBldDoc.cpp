#include "stdafx.h"
#include "test.h"

#include "testBldDoc.h"
#include "testBldView.h"
#include <bld\gEditView.h>
#include <cu\XmlWriter.h>
#include <io.h>
#include <sys\stat.h>
#include <bld\File\Xml DOM File\gXmlDomImport.h>
#include <bld\File\Xml DOM File\gXmlDomExport.h>

#include <bld\page.h>
#include <bld\layer.h>
#include <g\type\idom\giRectElement.h>
#include <g\type\idom\giTransformElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CTestBldDoc, CDocument)
BEGIN_MESSAGE_MAP(CTestBldDoc, CDocument)
	//{{AFX_MSG_MAP(CTestDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTestBldDoc::CTestBldDoc()
{
	m_pFileNode = NULL;
}

CTestBldDoc::~CTestBldDoc()
{
	if( m_pFileNode )
		m_pFileNode->Release();
}

#ifdef _DEBUG
void CTestBldDoc::AssertValid() const {
	CDocument::AssertValid(); }

void CTestBldDoc::Dump( CDumpContext& dc ) const {
	CDocument::Dump( dc ); }
#endif //_DEBUG

void CTestBldDoc::Serialize( CArchive& ar )
{
	if( ar.IsStoring() )
	{	}
	else
	{	}
}

BOOL CTestBldDoc::OnSaveDocument( LPCTSTR lpszPathName )
{
	POSITION pos = GetFirstViewPosition();
	if( NULL == pos )
		return FALSE;
	
	CTestBldView* pView = (CTestBldView*)GetNextView( pos );
	ASSERT( pView );
	CGINode* pDocument = pView->GetDomDocument();
	ASSERT( pDocument );

	_tchmod( lpszPathName, _S_IWRITE );
	_tunlink( lpszPathName );

	CGINode* pNode = pDocument->GetFirst();
	if( pNode )
	{
		CGIXmlDomExport xmlDomExport( *pNode, lpszPathName );
		if( xmlDomExport.Open() )
		{
			xmlDomExport.Write();
			xmlDomExport.Close();
		}
	}

	return TRUE;
}
	
BOOL CTestBldDoc::OnNewDocument()
{
	if( !CDocument::OnNewDocument() )
		return FALSE;

	return TRUE;
}

void CTestBldDoc::SetFileNode( CGINode* pNode ) 
{
	if( m_pFileNode )
		m_pFileNode->Release();

	m_pFileNode = pNode; 
	if( m_pFileNode )
		m_pFileNode->AddRef();
}

void* _CreateNode( LPCTSTR pctszClassName, void* pCookie )
{
	LPCTSTR pctszType = (LPCTSTR)pCookie;
	if( 0 == lstrcmpi( pctszType, _T("Node") ) )
	{
		if( 0 == lstrcmpi( pctszClassName, _T("page") ) )
			return new CGIPage;
		else if( 0 == lstrcmpi( pctszClassName, _T("layer") ) )
			return new CGILayer;
		else if( 0 == lstrcmpi( pctszClassName, _T("rect") ) )
			return new CGIRectElement;
		else if( 0 == lstrcmpi( pctszClassName, _T("rect") ) )
			return new CGITransformElement;
	}

	return NULL;
}

BOOL CTestBldDoc::OnOpenDocument( LPCTSTR lpszPathName )
{
	CGIXmlDomImport xmlDomImport;
	if( FALSE == xmlDomImport.Open( lpszPathName ) )
		return FALSE;

	CGClassFactory* pfactory = new CGClassFactory;
	pfactory->AddCreator( _T("page"), _CreateNode );
	pfactory->AddCreator( _T("layer"), _CreateNode );
	pfactory->AddCreator( _T("rect"), _CreateNode );
	pfactory->AddCreator( _T("transformelement"), _CreateNode );

	xmlDomImport.SetClassFactory( pfactory );
	
	xmlDomImport.Read();
	m_pFileNode = xmlDomImport.GetRootNode();
	m_pFileNode->AddRef();
	xmlDomImport.Close();

	return TRUE;
}