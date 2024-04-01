#ifndef ___WIN_CU__PH___
#define ___WIN_CU__PH___

#include "ui.h"

/// This is helps to forward Mouse and Key Message to CUI version 
/// functions of Mouse and Key.

/// When trying to call OnSetCursor with CWin or any derived 
/// classes of CWin as CWin::OnSetCursor, an ambiguous error will 
/// come, saying could CWin::OnSetCursor or CWnd::OnSetCursor.
/// This can be fixed by explicit calling CWnd::OnSetCursor if to
/// CWnd OnSetCursor

class CU_EXT_CLASS CWin : public CWnd, public CUI
{
public:
	CWin();
	virtual ~CWin();

	//{{AFX_VIRTUAL(CWin)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CWin)
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt );

	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );

	afx_msg void OnRButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnRButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnRButtonDblClk( UINT nFlags, CPoint point );

	afx_msg void OnMButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnMButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnMButtonDblClk( UINT nFlags, CPoint point );

	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif ___WIN_CU__PH___