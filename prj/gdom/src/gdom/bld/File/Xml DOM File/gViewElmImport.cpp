#include "stdafx.h"
#include <bld\File\Xml Dom File\gViewElmImport.h>
#include <bld\gEditView.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR CGIViewElmImport::ELEMENT_TAGNAME = _T("view");
CGIViewElmImport::CGIViewElmImport() 
{}

CGIViewElmImport::~CGIViewElmImport() 
{}

BOOL CGIViewElmImport::Read( CGIXmlDomImport& rImport, CGINode& rParentNode )  
{
	CGIEditView* pView = new CGIEditView;
	if( NULL == pView )
		return FALSE;

	rParentNode.AppendChild( *pView );
	rImport.ReadChildren( *pView );
	return TRUE; 
}
