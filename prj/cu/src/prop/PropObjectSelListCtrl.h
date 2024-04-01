#ifndef ___PROP_OBJECT_SEL_LIST_CTRL__PH___
#define ___PROP_OBJECT_SEL_LIST_CTRL__PH___

#include <ctrl\MSTreeCtrl.h>

class CPropObjectSelComboBox;
class CPropObjectSelListCtrl : public CMSTreeCtrl
{
public:
	CPropObjectSelListCtrl();
	virtual ~CPropObjectSelListCtrl();

	//{{AFX_VIRTUAL(CPropObjListTreeCtrl)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPropObjListTreeCtrl)
	afx_msg void OnCustomdraw( NMHDR* pNMHDR, LRESULT* lpResult );
	afx_msg void OnKillFocus( CWnd* pNewWnd );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnCancelMode();
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL SendSelChangeNotify( HTREEITEM hItem, BOOL bSelect = TRUE, BOOL bMultipleSel = TRUE );
	void Close();
		
public:
	CPropObjectSelComboBox*	m_pComboBox;
	HTREEITEM				m_hMouseHoverItem;
};

#endif //!___PROP_OBJECT_SEL_LIST_CTRL__PH___
