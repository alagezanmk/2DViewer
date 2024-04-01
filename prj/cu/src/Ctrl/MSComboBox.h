#ifndef ___M_S_COMBO_BOX__H___
#define ___M_S_COMBO_BOX__H___

#include "MSListBox.h"
#include "ODComboBox.h"

class CU_EXT_CLASS CMSComboBox : public CODComboBox
{
protected:
	enum 
	{
		ITEMDATA_ID = 0xFFFF,
	};

public:
	struct SItem;

	struct NMSELCHANGE : public NMHDR
	{
		INT nIndex;
		BOOL bSelect;
		BOOL bSetCurSel;
	};

	enum NOTIFY_CODE
	{
		NM_SELCHANGE			= 2000,
		NM_CANCELSEL			= 2001,
		NM_UPADTESEL			= 2002,
	};

	enum MS_CLASSSTYLE
	{
		CS_LBSEL_VISIBLE		= 0x0001,
		CS_SHOWCURSEL_EDIT		= 0x0002,
	};

public:
	CMSComboBox();
	virtual ~CMSComboBox();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSComboBox)
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItem );
	virtual void DeleteItem( LPDELETEITEMSTRUCT lpDeleteItem );
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMSComboBox)
	afx_msg void OnPaint();
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	afx_msg LRESULT OnCloseListBoxMsg( WPARAM wParam, LPARAM lParam );
	afx_msg void OnKillFocus( CWnd* pNewWnd );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	virtual INT InsertItem( INT nIndex, LPCTSTR lpszString );
	virtual void DrawItemText( INT nIndex, TCHAR* ptszText, CRect rct, CDC* pDC );

	void DrawDropDownBtn( CDC* pDC );
	virtual BOOL ShowListBox();
	void CloseListBox( BOOL bCancel = FALSE );
	void ActivateListBox();
	PINT GetSelIndex();

	SItem* GetMSItem( INT nIndex );

public:
	void LBSelVisible( BOOL bVisible );
	void ShowCurSelEdit( BOOL bShow = TRUE );

	void SetModified( BOOL bModified = TRUE );
	BOOL GetModified();

	const CUIntArray& GetSelArray();
	INT GetSelCount();
	INT SetCurSel( INT nIndex );
	INT GetSel( INT nIndex );
	INT SetSel( INT nIndex, BOOL bSelect = TRUE );

	void ResetContent();

	const CMSListBox* GetListBox();

protected:
	INT				m_nStyle;
	INT				m_nState;
	CMSListBox*		m_pListBox;
	CUIntArray		m_arnSel;
	BOOL			m_bModified;

	friend CMSListBox;
};

inline const CMSListBox* CMSComboBox::GetListBox() {
	return m_pListBox; }

inline void CMSComboBox::SetModified( BOOL bModified /*= TRUE*/ ) {
	m_bModified = bModified; }

inline BOOL CMSComboBox::GetModified() {
	return m_bModified; }

inline const CUIntArray& CMSComboBox::GetSelArray() {
	return m_arnSel; }

inline INT CMSComboBox::GetSelCount() {
	return m_arnSel.GetSize(); }

inline PINT CMSComboBox::GetSelIndex() {
	return (PINT)m_arnSel.GetData(); }

#endif //!___M_S_COMBO_BOX__H___


