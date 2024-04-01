#ifndef ___PROP_ITEM_LIST_CTRL__PH___
#define ___PROP_ITEM_LIST_CTRL__PH___

class CPropBox;
struct SPropItem;
class CPropItemListCtrl : public CTreeCtrl
{
public:
#define ROOT                ((SPropItem*)0xFFFF0000)
#define FIRST               ((SPropItem*)0xFFFF0001)
#define LAST                ((SPropItem*)0xFFFF0002)
public:
	CPropItemListCtrl( CPropBox& rPropCtrl );
	virtual ~CPropItemListCtrl();

	//{{AFX_VIRTUAL(CPropItemTreeCtrl)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPropItemTreeCtrl)
	afx_msg void OnCustomdraw( NMHDR* pNMHDR, LRESULT* lpResult );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnDeleteItem( NMHDR* pNMHDR, LRESULT* lpResult );
	afx_msg void OnItemExpanded( NMHDR* pNMHDR, LRESULT* lpResult );
	afx_msg void OnSelChanged( NMHDR* pNMHDR, LRESULT* lpResult );
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
	HTREEITEM PropToHTREEITEM( SPropItem& rsItem );
	HTREEITEM PropToHTREEITEM( SPropItem& rsItem ) const;

	HTREEITEM InsertPropItem( SPropItem& rsItem, SPropItem* psParent = ROOT, SPropItem* psInsertAfter = LAST );
	BOOL DeletePropItem( SPropItem& rsItem );
	void UpdatePropItem( SPropItem& rsItem );
	BOOL GetPropItemRect( SPropItem& rsItem, RECT& rRect ) const;
	void ResetContent();

	BOOL GetAlphatbeticalMode() const;
	void SetAlphatbeticalMode( BOOL bSet = TRUE );

	INT CreateStaticControl();
	INT DeleteStaticControl();
	INT ReposStaticControl( SPropItem* psFromItem = NULL );

	void ReposDlg();

	INT CreateControl();
	INT UpdateControl();
	INT DeleteControl();

protected:
	CMapPtrToPtr	m_mapPropItem;
	CPropBox&		m_rPropCtrl;
	INT				m_nItemDiv;
	BOOL			m_bAlphatbeticalMode;
	BOOL			m_bUserItemCtrl;
	INT				m_nCtrlState;
public:
	CDialog*		m_pPropDlg;
	INT				m_nDlgCx;
	INT				m_nDlgCy;
};

inline HTREEITEM CPropItemListCtrl::PropToHTREEITEM( SPropItem& rsItem ) {
	return (HTREEITEM)m_mapPropItem[&rsItem]; }

inline HTREEITEM CPropItemListCtrl::PropToHTREEITEM( SPropItem& rsItem ) const {
	CPropItemListCtrl* pThis = (CPropItemListCtrl*)this;
	return pThis->PropToHTREEITEM( rsItem ); }

inline void CPropItemListCtrl::SetAlphatbeticalMode( BOOL bSet /*= TRUE*/ ) {
	m_bAlphatbeticalMode = bSet; }

inline BOOL CPropItemListCtrl::GetAlphatbeticalMode() const {
	return m_bAlphatbeticalMode; }

#endif //!___PROP_ITEM_LIST_CTRL__PH___
