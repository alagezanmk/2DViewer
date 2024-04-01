#ifndef ___TOOL_BOX__PH___
#define ___TOOL_BOX__PH___

#include "ToolFrmWnd.h"

class CU_EXT_CLASS CToolBox : public CToolFrmWnd
{
public:
	struct SImageList;
	struct SItem;
	struct SItemInfo;

	enum ITEM_TYPE
	{
		SEPARATOR_ITEM	= -1,
		CONTROL_ITEM	= 0,
	};

public:
	CToolBox();
	virtual ~CToolBox();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBox)
	public:
	virtual BOOL Create( LPCTSTR lpszWindowName, const RECT& rect, CWnd* pParentWnd );
	int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CToolBox)
	afx_msg LRESULT OnFloatStatusMsg( WPARAM wParam, LPARAM lParam );
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void ShowPopup( INT nIndex );

	SItem* GetItemGroup( INT nKey );
	INT ReCalcLayout();

	void SetItem( INT nIndex, SItem* psItem, BOOL bHilite = FALSE );
	void SwapItem( INT nIndex, INT nSel );
	INT GetItemAt( CPoint point, SItem** ppsItem = NULL );
	void GetItemRect( INT nIndex, RECT* pRect );
	
	void DrawItem( CDC* pDC, INT nIndex, CRect rct, SItem* psItem );

	BOOL AddImageList( CImageList* pList, INT nID, INT cx );
	SImageList* GetImageList( INT nID );
	void ResetContent();

	void OnSelectItem( SItem* psItem );

public:
	BOOL SetCurItem( INT nID );
	BOOL OnChar( INT nChar );
	BOOL LoadImage( INT nID, INT cx );
	BOOL AddItem( SItemInfo* psItemInfo, BOOL bUpdateFrame = TRUE );
	BOOL InsertItem( INT nIndex, SItemInfo* psItemInfo );

protected:
	INT			m_nPressed;
	INT			m_nHilite;
	INT			m_nCurItem;
	BOOL		m_bPressed;
	CSize		m_cbItem;
	CPtrArray	m_arpItem;
	CPtrArray	m_arpImageList;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
struct CToolBox::SItemInfo
{
	INT			nIndex;

	INT			nID;
	BOOL		bObjTool;		// TODO: This member is not revelant to the ToolBox.
								// So, it can be removed and instead of this 
								// nFlag can be added
	INT			nKey;

	INT			nImageID;
	INT			nImageIndex;
	INT			nCy;

	CString		cszCaption;
	DWORD		dwData;
};

#endif //!___TOOL_BOX__PH___
