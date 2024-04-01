#ifndef __SLIM_SCOLL_BAR__XH___
#define __SLIM_SCOLL_BAR__XH___

class CU_EXT_CLASS CSlimScollBar : public CScrollBar
{
public:
	CSlimScollBar();
	virtual ~CSlimScollBar();

	//{{AFX_VIRTUAL(CSlimScollBar)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CSlimScollBar)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();

	BOOL m_bSlim;

};

//{{AFX_INSERT_LOCATION}}
#endif // !__SLIM_SCOLL_BAR__XH___
