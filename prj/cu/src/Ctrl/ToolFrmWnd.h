#ifndef ___TOOL_FRM_WND__PH___
#define ___TOOL_FRM_WND__PH___

class CU_EXT_CLASS CToolFrmWnd : public CMiniFrameWnd
{
	DECLARE_DYNCREATE(CToolFrmWnd)
protected:
	CToolFrmWnd();           // protected constructor used by dynamic creation
	virtual ~CToolFrmWnd();

	//{{AFX_VIRTUAL(CToolFrmWnd)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CToolFrmWnd)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetBarInfo( CControlBarInfo* pInfo, CFrameWnd* pFrameWnd );
	void GetBarInfo( CControlBarInfo* pInfo );

	void SaveState( LPCTSTR lpszProfileName );
	void LoadState( LPCTSTR lpszProfileName );

protected:
	CString m_cszCtrlName;
};

//{{AFX_INSERT_LOCATION}}
#endif // !___TOOL_FRM_WND__PH___
