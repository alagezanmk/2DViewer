#ifndef ___VIEW_TAB_BAR__PH___
#define ___VIEW_TAB_BAR__PH___

#include <ctrl\SizeCBar.h>
#include <ctrl\SlimTab.h>
#include <ctrl\SlimScollBar.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
class CViewTabBar : public CSizingControlBar
{
public:
	CViewTabBar();
	virtual ~CViewTabBar();

	//{{AFX_VIRTUAL(CViewTabBar)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CViewTabBar)
	afx_msg INT OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnPaint();
	afx_msg void OnSize( UINT nType, INT cx, INT cy );
	afx_msg void OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp );
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CSlimTab			m_slmTab;
	CScrollBar			m_SBar;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CViewBottomSBar : public CSizingControlBar
{
public:
	CViewBottomSBar();
	virtual ~CViewBottomSBar();

	//{{AFX_VIRTUAL(CViewBottomSBar)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CViewBottomSBar)
	afx_msg INT OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, INT cx, INT cy );
	afx_msg void OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp );
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CSlimScollBar		m_SBar;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CViewRightSBar : public CSizingControlBar
{
public:
	CViewRightSBar();
	virtual ~CViewRightSBar();

	//{{AFX_VIRTUAL(CViewRightSBar)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CViewRightSBar)
	afx_msg INT OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, INT cx, INT cy );
	afx_msg void OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp );
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CSlimScollBar		m_SBar;
};

//{{AFX_INSERT_LOCATION}}
#endif //!___VIEW_TAB_BAR__PH___
