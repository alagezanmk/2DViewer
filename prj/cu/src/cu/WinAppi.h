#ifndef ___WIN_APP_I__PH___
#define ___WIN_APP_I__PH___

class CU_EXT_CLASS CIWinApp : public CWinApp
{
	DECLARE_DYNCREATE(CIWinApp)
public:
	CIWinApp(); 
	virtual ~CIWinApp();

	//{{AFX_VIRTUAL(CIWinApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CIWinApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif  ___WIN_APP_I__PH___
