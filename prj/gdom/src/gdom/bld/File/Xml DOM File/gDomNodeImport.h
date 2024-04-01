#ifndef __G_DOM_NODE_IMPORT__PH___
#define __G_DOM_NODE_IMPORT__PH___

#include <bld\File\Xml Dom File\gXmlDomImport.h>

class GDOM_EXT_CLASS CGIDomNodeImport
{
public:
	CGIDomNodeImport();
	virtual ~CGIDomNodeImport();

public:
	virtual BOOL Read( CGIXmlDomImport& rImport, CGINode& rParentNode );
};

#endif //!___G_DOM_NODE_IMPORT__PH___