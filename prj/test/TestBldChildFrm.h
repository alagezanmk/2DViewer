#ifndef ___TEST_BLD_CHILD_FRM__PH___
#define ___TEST_BLD_CHILD_FRM__PH___

#include <cu\ChildFrmi.h>

class CTestBldChildFrm : public CIChildFrm
{
	DECLARE_DYNCREATE( CTestBldChildFrm )
public:
	CTestBldChildFrm();
	virtual ~CTestBldChildFrm();

public:
	//{{AFX_VIRTUAL(CChildFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CDialogBar m_wndDlgBar;
};

//{{AFX_INSERT_LOCATION}}
#endif //!___TEST_BLD_CHILD_FRM__PH___
