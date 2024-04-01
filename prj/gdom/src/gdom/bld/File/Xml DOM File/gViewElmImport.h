#ifndef __G_VIEW_ELM_IMPORT__PH___
#define __G_VIEW_ELM_IMPORT__PH___

#include "gDomNodeImport.h"

class GDOM_EXT_CLASS CGIViewElmImport : public CGIDomNodeImport
{
public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGIViewElmImport();
	virtual ~CGIViewElmImport();

public:
	virtual BOOL Read( CGIXmlDomImport& rImport, CGINode& rParentNode );
};

#endif //!___G_VIEW_ELM_IMPORT__PH___