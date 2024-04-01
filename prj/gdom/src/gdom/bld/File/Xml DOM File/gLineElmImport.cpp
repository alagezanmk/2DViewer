#include "stdafx.h"
#include <bld\File\Xml Dom File\gLineElmImport.h>
#include <g\type\idom\giLineElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR CGILineElmImport::ELEMENT_TAGNAME = _T("line");
CGILineElmImport::CGILineElmImport() 
{}

CGILineElmImport::~CGILineElmImport() 
{}

BOOL CGILineElmImport::Read( CGIXmlDomImport& rImport, CGINode& rParentNode )  
{
	CGILineElement* pElement = new CGILineElement;
	if( NULL == pElement )
		return FALSE;

	// Read Attributes
	CXmlReader* pxmlReader = rImport.GetXmlReader();
	
	// Read X1 Attribute
	CString cszAttrValue = pxmlReader->GetAttribute( pElement->m_aX1.GetName() );
	if( FALSE == cszAttrValue.IsEmpty() )
		pElement->m_aX1 = cszAttrValue;

	// Read Y1 Attribute
	cszAttrValue = pxmlReader->GetAttribute( pElement->m_aY1.GetName() );
	if( FALSE == cszAttrValue.IsEmpty() )
		pElement->m_aY1 = cszAttrValue;

	// Read X2 Attribute
	cszAttrValue = pxmlReader->GetAttribute( pElement->m_aX2.GetName() );
	if( FALSE == cszAttrValue.IsEmpty() )
		pElement->m_aX2 = cszAttrValue;

	// Read Y21 Attribute
	cszAttrValue = pxmlReader->GetAttribute( pElement->m_aY2.GetName() );
	if( FALSE == cszAttrValue.IsEmpty() )
		pElement->m_aY2 = cszAttrValue;

	rParentNode.AppendChild( *pElement );
	rImport.ReadChildren( *pElement );
	return TRUE;
}
