#ifndef ___UI__PH___
#define ___UI__PH___

#include "uiEvent.h"

class CU_EXT_CLASS CUI
{
public:
	enum HIT_TEST {	
			HT_NOTHING	= 0xFFFFFFFF,
	};

protected:
	CUI();
	virtual ~CUI();

public:
	/// Draw functions
	virtual void Draw( CDC* pDC );

	virtual UINT HitTest( const CPoint& rpoint );
	virtual BOOL On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage );
	virtual BOOL UpdateCursor();

	/// Overidable Key functions
	virtual BOOL On_KeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual BOOL On_KeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual BOOL On_SysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual BOOL On_SysKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

	/// Overidable Mouse functions
	virtual BOOL On_MouseWheel( UINT nFlags, short zDelta, CPoint point );
	virtual BOOL On_MouseMove( UINT nFlags, CPoint point );
	virtual BOOL On_LButtonDown( UINT nFlags, CPoint point );
	virtual BOOL On_LButtonUp( UINT nFlags, CPoint point );
	virtual BOOL On_LButtonDblClk( UINT nFlags, CPoint point );
	virtual BOOL On_RButtonDown( UINT nFlags, CPoint point );
	virtual BOOL On_RButtonUp( UINT nFlags, CPoint point );
	virtual BOOL On_RButtonDblClk( UINT nFlags, CPoint point );
	virtual BOOL On_MButtonDown( UINT nFlags, CPoint point );
	virtual BOOL On_MButtonUp( UINT nFlags, CPoint point );
	virtual BOOL On_MButtonDblClk( UINT nFlags, CPoint point );

	virtual BOOL On_NcMouseMove( UINT nFlags, CPoint point );
	virtual BOOL On_NcLButtonDown( UINT nFlags, CPoint point );
	virtual BOOL On_NcLButtonUp( UINT nFlags, CPoint point );
	virtual BOOL On_NcLButtonDblClk( UINT nFlags, CPoint point );

	BOOL HandleKeyboardEvent( const CKbdEvent& rEvent );
	BOOL HandleKeyboardEvent( HWND hWnd, UINT nMessage, UINT nChar, UINT nRepCnt, UINT nFlags );
	BOOL HandleKeyboardEvent( HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam );

	/// Overidable Key functions
	virtual BOOL OnKeyDown( const CKbdEvent& rEvent );
	virtual BOOL OnKeyUp( const CKbdEvent& rEvent );
	virtual BOOL OnSysKeyDown( const CKbdEvent& rEvent );
	virtual BOOL OnSysKeyUp( const CKbdEvent& rEvent );

	BOOL HandleMouseEvent( const CMouseEvent& rEvent );
	BOOL HandleMouseEvent( HWND hWnd, UINT nMessage, UINT nFlags, CPoint point, short zDelta = 0 );
	
	/// Overidable Mouse functions
	virtual BOOL OnMouseWheel( const CMouseEvent& rEvent );
	virtual BOOL OnMouseMove( const CMouseEvent& rEvent );
	virtual BOOL OnLButtonDown( const CMouseEvent& rEvent );
	virtual BOOL OnLButtonUp( const CMouseEvent& rEvent );
	virtual BOOL OnLButtonDblClk( const CMouseEvent& rEvent );
	virtual BOOL OnRButtonDown( const CMouseEvent& rEvent );
	virtual BOOL OnRButtonUp( const CMouseEvent& rEvent );
	virtual BOOL OnRButtonDblClk( const CMouseEvent& rEvent );
	virtual BOOL OnMButtonDown( const CMouseEvent& rEvent );
	virtual BOOL OnMButtonUp( const CMouseEvent& rEvent );
	virtual BOOL OnMButtonDblClk( const CMouseEvent& rEvent );

	virtual BOOL OnNcMouseMove( const CMouseEvent& rEvent );
	virtual BOOL OnNcLButtonDown( const CMouseEvent& rEvent );
	virtual BOOL OnNcLButtonUp( const CMouseEvent& rEvent );
	virtual BOOL OnNcLButtonDblClk( const CMouseEvent& rEvent );
};

//{{AFX_INSERT_LOCATION}}
#endif //!___UI__PH___
