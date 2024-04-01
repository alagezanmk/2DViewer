#ifndef ___G_VIEW_WND_BASE__PH___
#define ___G_VIEW_WND_BASE__PH___

#include "gWin.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGIViewWnd : public CGWin
{
public:
	CGIViewWnd();
	virtual ~CGIViewWnd();

	//{{AFX_VIRTUAL(CGIViewWnd)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGIViewWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual void CopyImage( CDC& rDC, RECT& rRect ) = 0;
};

#endif //!___G_VIEW_WND_BASE__PH___