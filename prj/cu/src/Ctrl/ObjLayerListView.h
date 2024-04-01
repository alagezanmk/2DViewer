#ifndef ___OBJ_LAYER_LIST__PH___
#define ___OBJ_LAYER_LIST__PH___

typedef void* LPLayer;

///////////////////////////////////////////////////////////////////////////////////////////////////
#define CM_LAYERCTRL_MSG_				(1)
#define CM_LAYERCTRL_START				(CM_LAYERCTRL_MSG_ + 0)
	
#define CM_LC_LOCK_CLICK				(CM_LAYERCTRL_MSG_ + 0)
#define CM_LC_VISIBLE_CLICK				(CM_LAYERCTRL_MSG_ + 1)
#define CM_LC_EDIT_CLICK				(CM_LAYERCTRL_MSG_ + 2)
#define CM_LC_BUTTON_CLICK				(CM_LAYERCTRL_MSG_ + 3)
#define CM_LC_OPACITY_CHANGE			(CM_LAYERCTRL_MSG_ + 4)
#define CM_LC_LAYER_SEL					(CM_LAYERCTRL_MSG_ + 5)
#define CM_LC_LAYER_DRAG				(CM_LAYERCTRL_MSG_ + 6)

#define CM_LAYERCTRL_END				(CM_LAYERCTRL_MSG_ + 100)

struct SObjLayerItem
{
	SObjLayerItem();

	enum { enNone		= 0, 
		   enVisible	= 1, 
		   enLockAll	= 2, 
		   enEditLock	= 4, 
		   enMoveLock	= 8 };

	CString			cszName;
	LPLayer			pLayer;
	INT				nFlags;
};

class CObjLayerListView : public CScrollView
{
	DECLARE_DYNCREATE(CObjLayerListView)

public:
	CObjLayerListView();           // protected constructor used by dynamic creation
	virtual ~CObjLayerListView();

protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_VIRTUAL(CObjLayerListView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
public:
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CObjLayerListView)
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg LRESULT OnSizeParent( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();

protected:
	void GetVisibleBtnRect( CRect* pRect, INT nIndex = 0 );
	void GetEditBtnRect( CRect* pRect, INT nIndex = 0 );
	void GetLabelRect( CRect* pRect, INT nIndex = 0 );
	void GetLockRect( CRect* pRect, INT nIndex = 0 );

public:
	void RecalcLayout();
	void Connect( HWND hWnd );
	void ResetContent();

protected:
	HWND		m_hMsg;

public:
	CPtrArray	m_arpLayer;
	INT			m_nCurSel;
};

inline void CObjLayerListView::Connect( HWND hWnd ) {
	m_hMsg = hWnd; }

//{{AFX_INSERT_LOCATION}}
#endif // !___OBJ_LAYER_LIST__PH___
