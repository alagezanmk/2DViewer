#ifndef ___MAIN_FRM__PH___
#define ___MAIN_FRM__PH___

#include <bld\bmainfrm.h>
class CMainFrame : public CBldMainFrm
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
	virtual ~CMainFrame();

public:
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CStatusBar	m_wndStatusBar;
	CToolBar	m_wndToolBar;
};

//{{AFX_INSERT_LOCATION}}
#endif //!___MAIN_FRM__PH___
