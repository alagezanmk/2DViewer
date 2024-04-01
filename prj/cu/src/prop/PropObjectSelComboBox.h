#ifndef ___PROP_OBJECT_SEL_COMBO_BOX__PH___
#define ___PROP_OBJECT_SEL_COMBO_BOX__PH___

#include <ctrl\MSComboBox.h>
#include "PropObjectSelListCtrl.h"
class CMSListCtrlSite;
class CPropObjectSelComboBox : public CODComboBox
{
public:
	struct NMSELCHANGE : public NMHDR
	{
		HTREEITEM hItem;
		BOOL bSelect;
		BOOL bMultipleSel;
	};
	
	enum NOTIFY_CODE
	{
		NM_SELCHANGE = 2000,
	};

public:
	CPropObjectSelComboBox();
	virtual ~CPropObjectSelComboBox();
	DECLARE_MESSAGE_MAP()

	//{{AFX_VIRTUAL(CPropObjListCmb)
	BOOL PreTranslateMessage( MSG* pMSG );
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPropObjListCmb)
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg LRESULT OnCloseListBoxMsg( WPARAM wParam, LPARAM lParam );
	afx_msg BOOL OnComboSelChange( NMHDR* pNMHDR, LRESULT* plResult );
	afx_msg void OnPaint();
	//}}AFX_MSG

protected:
	virtual void DrawItemText( INT nIndex, PTCHAR ptszText, CRect rct, CDC* pDC );
	void DrawDropDownBtn( CDC* pDC );
	void DrawItem( LPDRAWITEMSTRUCT lpDrawItem );

	virtual BOOL ShowListBox();
	void CloseListBox( BOOL bCancel = FALSE );
	void ActivateListBox();
	CMSListCtrlSite* CreateCtrlSite();

public:
	void ResetContent();
	HTREEITEM GetCurSel() const;
	BOOL SetCurSel( HTREEITEM hItem );

	BOOL GetSel( HTREEITEM hItem ) const;
	BOOL SetSel( HTREEITEM hItem, BOOL bSelect = TRUE );
	
public:
	INT						m_nChildItemIndex;
	CPropObjectSelListCtrl	m_ListCtrl;
	CMSListCtrlSite*		m_pListCtrlSite;
	BOOL					m_bDropBtnDown;
	BOOL					m_bDropBtnPressed;
	BOOL					m_bMultipleSelection;

	friend CPropObjectSelListCtrl;
};

//{{AFX_INSERT_LOCATION}}
#endif //!___PROP_OBJECT_SEL_COMBO_BOX__PH___
