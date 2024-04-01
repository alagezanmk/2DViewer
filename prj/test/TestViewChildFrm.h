#ifndef ___TEST_VIEW_CHILD_FRM__PH___
#define ___TEST_VIEW_CHILD_FRM__PH___

class CTestViewChildFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE( CTestViewChildFrm )
public:
	CTestViewChildFrm();
	virtual ~CTestViewChildFrm();

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
};

//{{AFX_INSERT_LOCATION}}
#endif //!___TEST_VIEW_CHILD_FRM__PH___
