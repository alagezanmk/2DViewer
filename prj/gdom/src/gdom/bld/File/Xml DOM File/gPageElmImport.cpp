#include "stdafx.h"
#include <bld\File\Xml Dom File\gPageElmImport.h>
#include <bld\page.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR CGIPageNodeImport::ELEMENT_TAGNAME = _T("Page");
CGIPageNodeImport::CGIPageNodeImport() 
{}

CGIPageNodeImport::~CGIPageNodeImport() 
{}

BOOL CGIPageNodeImport::Read( CGIXmlDomImport& rImport, CGINode& rParentNode )  
{
	CGIPage* pPage = new CGIPage;
	if( NULL == pPage )
		return FALSE;

	rParentNode.AppendChild( *pPage );
	rImport.ReadChildren( *pPage );
	return TRUE; 
}
