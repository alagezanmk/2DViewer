#include "stdafx.h"
#include <bld\File\Xml Dom File\gXmlDomImport.h>
#include <bld\File\Xml Dom File\gDomNodeImport.h>

/*#include <bld\File\Xml Dom File\gViewElmImport.h>
#include <bld\File\Xml Dom File\gPageElmImport.h>

#include <bld\File\Xml Dom File\gTransformElmImport.h>

#include <bld\File\Xml Dom File\gLineElmImport.h>
#include <bld\File\Xml Dom File\gRectElmImport.h>*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGIXmlDomImport::CGIXmlDomImport() {
	m_pRootNode = NULL; }

CGIXmlDomImport::CGIXmlDomImport( LPCTSTR pctszFileName )
{
	m_pRootNode = NULL;
	m_cszFileName = pctszFileName;
}

CGIXmlDomImport::~CGIXmlDomImport()
{}

BOOL CGIXmlDomImport::Open() 
{
	if( m_cszFileName.IsEmpty() )
		return FALSE;

	return Open( m_cszFileName );
}

BOOL CGIXmlDomImport::Open( LPCTSTR pctszFileName ) 
{
	if( FALSE == m_xmlReader.Open( pctszFileName ) )
		return FALSE;

	m_cszFileName = pctszFileName;
	return TRUE;
}

BOOL CGIXmlDomImport::Read() 
{
	if( FALSE == m_xmlReader.IsOpen() )
		return FALSE;

	if( m_pRootNode )
		m_pRootNode->Release();

	VERIFY( m_pRootNode = new CGINode );
	if( NULL == m_pRootNode )
		return FALSE;

	m_pRootNode->AddRef();

	CString cszTagName;
	m_xmlReader.GetNodeName( cszTagName );

	m_xmlReader.SetFirstChild();	// #document
	m_xmlReader.GetNodeName( cszTagName );

	m_xmlReader.Next();
	ReadNode( *m_pRootNode );
	ReadChildren( *m_pRootNode );
	return TRUE;
}

BOOL CGIXmlDomImport::ReadChildren( CGINode& rParentNode )
{
	if( FALSE == m_xmlReader.SetFirstChild() )
		return FALSE; 
	
	do
	{
		ReadNode( rParentNode );
	}while( m_xmlReader.Next() );
	return TRUE;
}

BOOL CGIXmlDomImport::ReadNode( CGINode& rParentNode )
{
	CString cszTagName;
	m_xmlReader.GetNodeName( cszTagName );
	CGIDomNodeImport* pNodeImport = CreateNodeImport( cszTagName );
	if( pNodeImport )
	{
		BOOL bResult = pNodeImport->Read( *this, rParentNode );
		delete pNodeImport;
		return bResult;
	}

	return FALSE;
}

BOOL CGIXmlDomImport::Close() 
{
	if( FALSE == m_xmlReader.IsOpen() )
		return FALSE;

	m_xmlReader.Close();
	return TRUE;
}

CGIDomNodeImport* CGIXmlDomImport::CreateNodeImport( const CString& rcszTagName ) 
{
	/*if( 0 == rcszTagName.CompareNoCase( CGIViewElmImport::ELEMENT_TAGNAME ) )
		return new CGIViewElmImport;

	if( 0 == rcszTagName.CompareNoCase( CGIPageNodeImport::ELEMENT_TAGNAME ) )
		return new CGIPageNodeImport;

	if( 0 == rcszTagName.CompareNoCase( CGITransformElmImport::ELEMENT_TAGNAME ) )
		return new CGITransformElmImport;

	if( 0 == rcszTagName.CompareNoCase( CGILineElmImport::ELEMENT_TAGNAME ) )
		return new CGILineElmImport;

	if( 0 == rcszTagName.CompareNoCase( CGIRectElmImport::ELEMENT_TAGNAME ) )
		return new CGIRectElmImport;*/

	CGIDomNodeImport* pNodeImport = (CGIDomNodeImport*)CreateFactoryObject( rcszTagName, _T("DomNodeImport") ); 
	if( pNodeImport )
		return pNodeImport;

	return new CGIDomNodeImport;
}

CGINode* CGIXmlDomImport::CreateNode( const CString& rcszTagName )
{
	CGINode* pNode = (CGINode*)CreateFactoryObject( rcszTagName, _T("Node") ); 
	return pNode;
}
