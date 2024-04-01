#ifndef ___G_NODE_PROP__PH___
#define ___G_NODE_PROP__PH___

#include "gPropData.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSFNode : public CGPropData
{
public:
	CGSFNode();
	virtual ~CGSFNode();
};

class GDOM_EXT_CLASS CGMFNode: public CGPropArrData
{
public:
	CGMFNode();
	virtual ~CGMFNode();
};

#endif //!___G_NODE_PROP__PH___
