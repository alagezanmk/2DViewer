#ifndef ___TEST__PH___
#define ___TEST__PH___

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include <bld\bApp.h>
class CTestApp : public CBldApp
{
public:
	CTestApp();

	//{{AFX_VIRTUAL(CTestApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTestApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif //!___TEST__PH___
