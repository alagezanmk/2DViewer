#include "stdafx.h"
#include <bld\File\Xml Dom File\gXmlDomExport.h>
#include <g\type\idom\giElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGIXmlDomExport::CGIXmlDomExport( CGINode& rNode ) :
	CGIFileExport( rNode )
{}

CGIXmlDomExport::CGIXmlDomExport( CGINode& rNode, LPCTSTR pctszFileName ) :
	CGIFileExport( rNode, pctszFileName )
{}

CGIXmlDomExport::~CGIXmlDomExport()
{}

BOOL CGIXmlDomExport::Open( LPCTSTR pctszFileName ) 
{
	if( FALSE == m_xmlWriter.Open( pctszFileName ) )
		return FALSE;

	m_cszFileName = pctszFileName;
	return TRUE;
}

BOOL CGIXmlDomExport::Close()
{
	m_xmlWriter.Close();
	return TRUE;
}

BOOL CGIXmlDomExport::Write() 
{
	//if( FALSE == m_xmlWriter.IsOpen() )
	//	return FALSE;

	m_xmlWriter.WriteXMLStartTag();

	if( NULL == m_pRootNode )
		return FALSE;

	WriteNode( *m_pRootNode );
	return TRUE;
}

void CGIXmlDomExport::WriteNodeAttriute( CGINode& rNode )
{
	if( FALSE == rNode.IsDerivedFrom( CGIElement::GetClassType() ) )
		return;

	CGIElement* pElement = (CGIElement*)&rNode;
	CGINamedAttrMap* pmapAttr =	(CGINamedAttrMap*)pElement->GetAttributes();
	ASSERT( pmapAttr );
	
	CString cszName, cszGroupName, cszLookupName, cszValue;
	CGIAttr* pAttr;
	INT nCount = pmapAttr->GetLength();
	for( INT i = 0; i < nCount; i++ )
	{
		pAttr = (CGIAttr*)pmapAttr->GetItem( i );
		cszName = pAttr->GetNodeName();
		cszGroupName = pAttr->GetGroupName();
		if( cszGroupName.IsEmpty() )
			cszLookupName = cszName;
		else
			cszLookupName.Format( _T("%s%c%s"), cszGroupName, CGINamedAttrMap::GROUP_CHAR, cszName );

		pAttr->Get( cszValue );
		m_xmlWriter.Attribute( cszLookupName, cszValue );
	}
}

void CGIXmlDomExport::WriteNode( CGINode& rNode )
{
	CString cszName = rNode.GetName();
	if( cszName.IsEmpty() )
		cszName.Format( _T("Node%x"), &rNode );
	
	m_xmlWriter.StartTag( cszName );
	
	if( rNode.IsDerivedFrom( CGIElement::GetClassType() ) )
		WriteNodeAttriute( rNode );
	
	BOOL bChildFound = rNode.HasChildNodes();
	if( bChildFound )
	{
		m_xmlWriter.CloseStartTag();
		
		CGINode* pChild = rNode.GetFirst();
		while( pChild )
		{
			WriteNode( *pChild );
			pChild = pChild->GetNext();
		}
		
		m_xmlWriter.EndTag();
	}
	else
		m_xmlWriter.CloseStartTag( TRUE );
}
