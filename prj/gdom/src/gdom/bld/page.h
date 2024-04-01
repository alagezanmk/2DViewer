#ifndef ___BLD_PAGE__PH___
#define ___BLD_PAGE__PH___

#include <g\type\idom\giView.h>

class GDOM_EXT_CLASS CGIPage : public CGIView
{
	DECL_GTPYECLASS_DYNCREATE(CGIPage)
public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGIPage();
	virtual ~CGIPage();
};

#endif // !___BLD_PAGE__PH___
