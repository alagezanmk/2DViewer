#ifndef ___MS_TREE_CTRL__PH___
#define ___MS_TREE_CTRL__PH___

class CMSTreeCtrl : public CTreeCtrl
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
		NM_SELCHANGE			= 2000,
	};

public:
	CMSTreeCtrl();
	virtual ~CMSTreeCtrl();

	//{{AFX_VIRTUAL(CMSTreeCtrl)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMSTreeCtrl)
	afx_msg BOOL OnSelChanging( NMHDR* pNMHDR, LRESULT* lpResult );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HTREEITEM GetNext_Item( HTREEITEM hItem ) const;
	HTREEITEM GetPrev_Item( HTREEITEM hItem ) const;

	HTREEITEM GetFirstSelectedItem() const;
	HTREEITEM GetNextSelectedItem( HTREEITEM hItem ) const;
	HTREEITEM GetPrevSelectedItem( HTREEITEM hItem ) const;
	BOOL IsMultipleSelected() const;

	void DeselectAll();

	virtual CWnd* GetSelChangeParent() const;
	virtual BOOL SendSelChangeNotify( HTREEITEM hItem, BOOL bSelect = TRUE, BOOL bMultipleSel = TRUE );
};

inline CWnd* CMSTreeCtrl::GetSelChangeParent() const {
	return GetParent(); }

#endif //!___MS_TREE_CTRL__PH___
