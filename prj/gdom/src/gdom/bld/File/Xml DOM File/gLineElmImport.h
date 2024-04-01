#ifndef __G_LINE_ELM_IMPORT__PH___
#define __G_LINE_ELM_IMPORT__PH___

#include "gDomNodeImport.h"

class GDOM_EXT_CLASS CGILineElmImport : public CGIDomNodeImport
{
public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGILineElmImport();
	virtual ~CGILineElmImport();

public:
	virtual BOOL Read( CGIXmlDomImport& rImport, CGINode& rParentNode );
};

#endif //!___G_LINE_ELM_IMPORT__PH___