#include "stdafx.h"
#include <bld\File\Xml Dom File\gTransformElmImport.h>
#include <g\type\idom\giTransformElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR CGITransformElmImport::ELEMENT_TAGNAME = _T("transformelement");
CGITransformElmImport::CGITransformElmImport() 
{}

CGITransformElmImport::~CGITransformElmImport() 
{}

BOOL CGITransformElmImport::Read( CGIXmlDomImport& rImport, CGINode& rParentNode )  
{
	CGITransformElement* pElement = new CGITransformElement;
	if( NULL == pElement )
		return FALSE;

	rParentNode.AppendChild( *pElement );
	rImport.ReadChildren( *pElement );
	return TRUE; 
}
