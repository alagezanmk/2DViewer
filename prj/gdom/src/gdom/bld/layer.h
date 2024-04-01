#ifndef __BLD_LAYER__PH___
#define __BLD_LAYER__PH___

#include <g\type\idom\giViewPort.h>

class GDOM_EXT_CLASS CGILayer : public CGIViewPort
{
	DECL_GTPYECLASS_DYNCREATE(CGILayer)
public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGILayer();
	virtual ~CGILayer();
};

#endif // !__BLD_LAYER__PH___
