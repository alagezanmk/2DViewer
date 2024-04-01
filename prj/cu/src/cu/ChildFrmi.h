#ifndef ___CHILD_FRM_I__PH___
#define ___CHILD_FRM_I__PH___

#include "ViewTabBar.h"

class CU_EXT_CLASS CIChildFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CIChildFrm)

public:
	enum { 
		EIDC_VIEW_TAB_BAR	= 1
	};

protected:
	CIChildFrm();           // protected constructor used by dynamic creation
	virtual ~CIChildFrm();

	//{{AFX_VIRTUAL(CIChildFrm)
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg LRESULT OnGetSBarMsg( WPARAM wParam, LPARAM lParam );
	afx_msg void OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI );
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd );
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CIChildFrm)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CViewTabBar			m_hbViewBar;
	CViewRightSBar		m_vsbViewBar;
	CViewBottomSBar		m_hsbViewBar;
};

//{{AFX_INSERT_LOCATION}}
#endif //!___CHILD_FRM_I__PH___
