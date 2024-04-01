#ifndef __G_PAGE_NODE_IMPORT__PH___
#define __G_PAGE_NODE_IMPORT__PH___

#include "gDomNodeImport.h"

class GDOM_EXT_CLASS CGIPageNodeImport : public CGIDomNodeImport
{
public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGIPageNodeImport();
	virtual ~CGIPageNodeImport();

public:
	virtual BOOL Read( CGIXmlDomImport& rImport, CGINode& rParentNode );
};

#endif //!___G_PAGE_NODE_IMPORT__PH___