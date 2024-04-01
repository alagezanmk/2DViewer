#ifndef __G_RECT_ELM_IMPORT__PH___
#define __G_RECT_ELM_IMPORT__PH___

#include "gDomNodeImport.h"

class GDOM_EXT_CLASS CGIRectElmImport : public CGIDomNodeImport
{
public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGIRectElmImport();
	virtual ~CGIRectElmImport();

public:
	virtual BOOL Read( CGIXmlDomImport& rImport, CGINode& rParentNode );
};

#endif //!___G_RECT_ELM_IMPORT__PH___