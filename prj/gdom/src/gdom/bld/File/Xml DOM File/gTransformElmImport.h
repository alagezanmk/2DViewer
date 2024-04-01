#ifndef __G_TRANSFORM_ELM_IMPORT__PH___
#define __G_TRANSFORM_ELM_IMPORT__PH___

#include "gDomNodeImport.h"

class GDOM_EXT_CLASS CGITransformElmImport : public CGIDomNodeImport
{
public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGITransformElmImport();
	virtual ~CGITransformElmImport();

public:
	virtual BOOL Read( CGIXmlDomImport& rImport, CGINode& rParentNode );
};

#endif //!___G_TRANSFORM_ELM_IMPORT__PH___