#ifndef ___TAB_CTRL_EX__PH___
#define ___TAB_CTRL_EX__PH___

#define ID_EVT_COMBO	5

class CU_EXT_CLASS CTabCtrlEx : public CTabCtrl  
{
	DECLARE_DYNAMIC(CTabCtrlEx)
public:
	CTabCtrlEx();
	virtual ~CTabCtrlEx();

protected:
	//{{AFX_MSG(CTabCtrlEx)
	afx_msg BOOL OnEraseBkgnd( CDC* );//added to avoid flicker
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg	void OnSelChanging(NMHDR* pNmh, LRESULT* pRes);
	afx_msg void OnComboSelChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//{{AFX_VIRTUAL(CTabCtrlEx)
	virtual	BOOL PreTranslateMessage( MSG* pMsg );
	virtual	void DrawItem( LPDRAWITEMSTRUCT pDrawItem );
	virtual	void OnDrawText( CDC& dc, CRect rc, CString cszText, BOOL bDisabled );
	//}}AFX_VIRTUAL

public:
	virtual	BOOL IsTabEnabled( UINT unTab );
	void DisableTab( UINT unTab );
	void EnableTab( UINT unTab );

	INT NextEnabledTab( INT nTab, BOOL bWrap );
	INT	PrevEnabledTab( INT nTab, BOOL bWrap );		
	BOOL SetActiveTab( UINT nNewTab );
	BOOL SubclassDlgItem( UINT nID, CWnd* pParent );	

	virtual int SetCurSel( int nItem );
	void SetMsgID( INT nMsgID ) { m_nMsgID = nMsgID; }

private:
	INT		m_nPrevTab; 
	INT		m_nMsgID;
	CUIntArray m_unarDisblTab;
};

#endif //!___TAB_CTRL_EX__PH___