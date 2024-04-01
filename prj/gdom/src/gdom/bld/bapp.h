#ifndef ___BLD_APP__PH___
#define ___BLD_APP__PH___

#include <cu\WinAppi.h>

class GDOM_EXT_CLASS CBldApp : public CIWinApp
{
public:
	CBldApp();

	//{{AFX_VIRTUAL(CBldApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CBldApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //!___BLD_APP__PH___
