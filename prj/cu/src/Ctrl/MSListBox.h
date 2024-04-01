#ifndef ___M_S_LIST_BOX__H___
#define ___M_S_LIST_BOX__H___

class CU_EXT_CLASS CMSComboBox;
class CU_EXT_CLASS CMSListBox : public CListBox 
{
public:
	CMSListBox();
	virtual ~CMSListBox();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSListBox)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	virtual int VKeyToItem(UINT nKey, UINT nIndex);
	virtual int CharToItem(UINT nKey, UINT nIndex);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMSListBox)
	afx_msg void OnKillFocus( CWnd* pNewWnd );
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL			m_bFirstSelected;
	CMSComboBox*	m_pCmbCtrl;
	INT*			m_pnPrevSel;
	INT				m_nPrevSelCnt;
};

#define WM_MSLB_CLOSE	(WM_USER + 1010)
#endif //!___M_S_LIST_BOX__H___
