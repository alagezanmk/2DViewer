#ifndef ___MAINFRM_I__PH___
#define ___MAINFRM_I__PH___

#include "ui.h"

#define CM_MF_MAINFRM_START				1

#define CM_MF_CREATE_PROGRESS_CTRL		1
#define CM_MF_GET_PROGRESS_CTRL			2
#define CM_MF_CLOSE_PROGRESS_CTRL		3

#define CM_MF_VIEW_ADD					4
#define CM_MF_VIEW_CLOSE				5
#define CM_MF_VIEW_ACTIVATE				6
#define CM_MF_GET_ACTIVE_VIEW			7
		
#define CM_MF_GET_FULLSCREEN			8

#define CM_MF_MAINFRM_END				50

class CU_EXT_CLASS CIMDIClient : public CWnd, public CUI
{
public:
	CIMDIClient();
	virtual ~CIMDIClient();

	void SubClassMDI( HWND hWnd );
	void UnsubClassMDI();

	//{{AFX_VIRTUAL(CIMDIClient)
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	afx_msg LRESULT OnMDISetMenu( WPARAM wParam, LPARAM lParam );
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnSysKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CIMDIClient)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CU_EXT_CLASS CIMainFrm : public CMDIFrameWnd, public CUI
{
	DECLARE_DYNCREATE(CIMainFrm)
public:
	CIMainFrm();
	virtual ~CIMainFrm();

	//{{AFX_VIRTUAL(CIMainFrm)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CIMainFrm)
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	virtual BOOL LoadFrame(UINT nIDResource,
					DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
					CWnd* pParentWnd = NULL,
					CCreateContext* pContext = NULL );

	afx_msg void OnClose();
	afx_msg void OnDropFiles( HDROP p_hDropInfo );

	afx_msg LRESULT OnKeyDownMsg( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnKeyUpMsg( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnSysKeyDownMsg( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnSysKeyUpMsg( WPARAM wParam, LPARAM lParam );

	afx_msg LRESULT OnGetFullScreen( WPARAM wParam, LPARAM lParam );
	afx_msg void OnFullScreen();
	afx_msg void OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI );

	afx_msg LRESULT OnViewAdd( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnViewClose( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnViewActivate( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnGetActiveView( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	overrided BOOL OnKeyDown( const CKbdEvent& rEvent );

	virtual void OnChangeFullScreen();
	virtual void OnCancelFullScreen();

	CStatusBar* GetStatusBar();
	virtual void ShowHideBars();

protected:
	CIMDIClient*		m_pmdiClient;
	CStatusBar			m_StatusBar;
	PVOID				m_pvFullScreen;
	BOOL				m_bBarsVisiblity;

	CPtrArray			m_arpView;
	CView*				m_pCurView;
};

inline CStatusBar* CIMainFrm::GetStatusBar() {
	return &m_StatusBar; }

//{{AFX_INSERT_LOCATION}}
#endif //!___MAINFRM_I__PH___
