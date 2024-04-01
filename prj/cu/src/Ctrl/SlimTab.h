#ifndef ___SLIM_TAB__PH___
#define ___SLIM_TAB__PH___

// TAB POSITIONS
#define		ST_HORIZONTAL_TABDOWN		0
#define		ST_HORIZONTAL_TABUP			1
#define		ST_VERTICAL_TABLEFT			2
#define		ST_VERTICAL_TABRIGHT		3

// Mouse On Button
#define		ST_MOUSENONE				0
#define		ST_MOUSEON_LEFT				1
#define		ST_MOUSECLICK_LEFT			2
#define		ST_MOUSEON_RIGHT			3
#define		ST_MOUSECLICK_RIGHT			4

//Mouse On Tab
#define		ST_MOUSE_DOWN				1
#define		ST_MOUSE_UP					2

// Button 
#define		ST_BTN_LEFT					0
#define		ST_BTN_RIGHT				1

typedef struct 
{
	CString		cszText;
	INT			nTabSize;
	INT			nCaptionSize;
	CRect		rctText;
	INT			x;
	INT			y;
	INT			nTabCx;
	INT			nTabCy;
}SSlimTab, *PSSlimTab;
typedef CArray<SSlimTab, SSlimTab&> CArrSlimTab;

class CU_EXT_CLASS CSlimTab : public CWnd
{
// Construction
public:
	CSlimTab();
	virtual ~CSlimTab();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlimTab)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CSlimTab)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CRect GetScrollBtnRect( INT nB );
	void DrawScrollBtn( CDC* pDC, COLORREF crfPtr, INT nBtn );
	void DrawTab( CDC* pDC, PINT pnOffset, PSSlimTab psTab );
	void InitTab();
	void OnMouseMove_Button(UINT nFlags, CPoint point);
	void OnMouseMove_Tab(UINT nFlags, CPoint point);
	BOOL OnLButtonDown_Button(UINT nFlags, CPoint point);
	BOOL OnLButtonDown_Tab(UINT nFlags, CPoint point);
	BOOL OnLButtonUp_Button(UINT nFlags, CPoint point);
	BOOL OnLButtonUp_Tab(UINT nFlags, CPoint point);

public:
	BOOL Create( CWnd* pParent,  CRect *prctWnd, INT nID);
	void SetMsgHandle( HWND hWnd);
	void SetOppositeButton();
	void SetTabStyle( INT nStyle );

	INT GetTabAt( CPoint point );
	void RenameTab( INT nIndex, PTCHAR pszTabName );
	void AddTab( PTCHAR pszTabName );
	void RemoveTab( INT nTab );
	void RemoveAll();

	void CalcTabPostion();
	INT  GetCurrentTab();
	void SetCurrentTab( INT nActive );
	PTCHAR GetTabText( INT nTab );

protected:
	INT			m_nTabSize;
	INT			m_nClicked;
	INT			m_nMouseDown;
	INT			m_nMouseOver;		// Status of Mouse 
	INT			m_nVisible;
	INT			m_nStartX;			// Tab start x
	INT			m_nStartY;			// Tab start y
	INT			m_nTabStyle;		// Tab Style
	INT			m_nCurTab;			// Selected Tab
	CPoint		m_ptDown;			
	BOOL		m_bScrollBtnSide;	// Side of Scroll Button
	BOOL		m_bRight;			// Enable For Right Button
	BOOL		m_bLeft;			// Enable For Left Button
	CArrSlimTab	m_arSlimTab;		// CArray for Tabs
	HWND		m_hMsg;				// Handle for window for sending Message
};

//{{AFX_INSERT_LOCATION}}
#endif //!___SLIM_TAB__PH___
