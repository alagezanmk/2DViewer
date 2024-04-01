#include "stdafx.h"
#include <bld\File\Xml Dom File\gRectElmImport.h>
#include <g\type\idom\giRectElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR CGIRectElmImport::ELEMENT_TAGNAME = _T("rect");
CGIRectElmImport::CGIRectElmImport() 
{}

CGIRectElmImport::~CGIRectElmImport() 
{}

BOOL CGIRectElmImport::Read( CGIXmlDomImport& rImport, CGINode& rParentNode )  
{
	CGIRectElement* pElement = new CGIRectElement;
	if( NULL == pElement )
		return FALSE;

	rParentNode.AppendChild( *pElement );
	rImport.ReadChildren( *pElement );
	return TRUE; 
}
