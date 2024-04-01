#ifndef ___ITEM_LIST__PH___
#define ___ITEM_LIST__PH___

class CPropCtrl;
class CPropItemList : public CScrollView
{
protected:
	CPropItemList( CPropCtrl& rPropCtrl );           // protected constructor used by dynamic creation
	virtual ~CPropItemList();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropItemList)
	protected:
	virtual void OnDraw( CDC* pDC );      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual BOOL OnScrollBy( CSize sizeScroll, BOOL bDoScroll );
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPropItemList)
	afx_msg void OnNcDestroy();
	afx_msg void OnSize( UINT nType, INT cx, INT cy );
	afx_msg HBRUSH OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor );
	afx_msg void OnSetFocus( CWnd* pOldWnd );
	afx_msg void OnKillFocus( CWnd* pOldWnd );
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnPropEditUpdate( NMHDR* pNotifyStruct, LRESULT* plResult );
	afx_msg void OnPropEditCancel( NMHDR* pNotifyStruct, LRESULT* plResult );
	afx_msg void OnPropBtnClicked();
	afx_msg void OnPropEditChange();
	afx_msg void OnPropComboSelChange( NMHDR* pNotifyStruct, LRESULT* plResult );
	afx_msg void OnPropComboUpdateSel( NMHDR* pNotifyStruct, LRESULT* plResult );
	afx_msg void OnPropComboCancelSel( NMHDR* pNotifyStruct, LRESULT* plResult );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void InvalidateItem( INT nItem = -1 );
	BOOL TrackItemDivider( UINT nFlags, CPoint point );
	void CalcItemInfo();
	void ReposDlg();
	void RecalcPropList();

	INT ItemFromPoint( INT y, INT* pnItemY = NULL );
	INT GetItemRect( INT nIndex, CRect& rrct );

	INT CreateStaticCtrl();
	INT DeleteStaticCtrl();
	INT ReposStaticCtrl( SPropItem* psFromItem = NULL );

	INT CreateCtrl();
	INT UpdateCtrl();
	INT DeleteCtrl();

protected:
	CPropCtrl&			m_rPropCtrl;
	CSize				m_szCell;
	INT					m_nItemDiv;

	INT					m_nHorzCnt;
	INT					m_nHorzVisibleCnt;
	INT					m_nLeftIndexX;
	INT					m_nLeftIndex;

	INT					m_nVertCnt;
	INT					m_nVertVisibleCnt;
	INT					m_nTopIndexY;
	INT					m_nTopIndex;

	CDialog*			m_pPropDlg;
	INT					m_nDlgCx;
	INT					m_nDlgCy;

	BOOL				m_bUserItemCtrl;
	BOOL				m_bStaticItemCtrl;
	BOOL				m_bAlphabeticTab;
	INT					m_nCtrlState;

	friend class CPropCtrl;
};

//{{AFX_INSERT_LOCATION}}
#endif //!___ITEM_LIST__PH___
