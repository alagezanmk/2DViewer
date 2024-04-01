#include "stdafx.h"
#include <bld\File\Xml Dom File\gDomNodeImport.h>
#include <g\type\idom\giElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGIDomNodeImport::CGIDomNodeImport() 
{}

CGIDomNodeImport::~CGIDomNodeImport() 
{}

BOOL CGIDomNodeImport::Read( CGIXmlDomImport& rImport, CGINode& rParentNode ) 
{
	CXmlReader* pReader = rImport.GetXmlReader();
	if( NULL == pReader )
		return FALSE;
	
	CString cszTagName;
	pReader->GetNodeName( cszTagName );
	CGINode* pNode = rImport.CreateNode( cszTagName );
	if( NULL == pNode )
		return FALSE;
	
	rParentNode.AppendChild( *pNode );
	
	if( FALSE == pNode->IsDerivedFrom( CGIElement::GetClassType() ) )
		return FALSE;
	
	CGIElement* pElement = (CGIElement*)pNode;
	pElement->OnInitialUpdate();

	CMapStringToString mapAttr;
	pReader->GetAttributes( mapAttr );
	
	CGIAttr* pAttr;
	CString cszAttrName, cszAttrValue;
	POSITION pos = mapAttr.GetStartPosition();
	while( pos )
	{
		mapAttr.GetNextAssoc( pos, cszAttrName, cszAttrValue );
		pAttr = pElement->GetAttributeNode( cszAttrName );
		if( pAttr )
			pAttr->Set( cszAttrValue );
	}
	
	rImport.ReadChildren( *pNode );
	return TRUE; 
}
