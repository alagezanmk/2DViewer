#ifndef ___G_UI__PH___
#define ___G_UI__PH___

#include <cu\Win.h>
#include <cu\uiEvent.h>
#include <gbase\gEvent.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGUI
{
public:
	enum {	
		HT_NOTHING = 0xFFFFFFFF,
	};

public:
	CGUI();
	virtual ~CGUI();

public:
	virtual UINT HitTest( const PointF& rptf );
	virtual BOOL On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage );
	virtual BOOL UpdateCursor();

	static CGMouseEvent* CreateMouseEvent( LPCTSTR ptszEventType, void* pvView, 
									       UINT nFlags, CPoint ptScreen, CPoint point, 
										   USHORT usnButton, void* pvRelatedEventTarget );

	static BOOL InitMouseEvent( CGMouseEvent& rdstEvent, const CMouseEvent& rsrcEvent, void* pvView, void* pvRelatedEventTarget );

	virtual BOOL MouseWheel( const CGMouseEvent& rEvent );
	virtual BOOL MouseMove( const CGMouseEvent& rEvent );

	virtual BOOL LButtonDown( const CGMouseEvent& rEvent );
	virtual BOOL LButtonUp( const CGMouseEvent& rEvent );
	virtual BOOL LButtonDblClk( const CGMouseEvent& rEvent );

	virtual BOOL RButtonDown( const CGMouseEvent& rEvent );
	virtual BOOL RButtonUp( const CGMouseEvent& rEvent );
	virtual BOOL RButtonDblClk( const CGMouseEvent& rEvent );

	virtual BOOL MButtonDown( const CGMouseEvent& rEvent );
	virtual BOOL MButtonUp( const CGMouseEvent& rEvent );
	virtual BOOL MButtonDblClk( const CGMouseEvent& rEvent );

	static CGKeyboardEvent* CreateKeyboardEvent( LPCTSTR ptszEventType, void* pvView, 
												 ULONG	ulKeyIdentifier, 
												 ULONG	ulKeyLocation );

	static BOOL InitKeyboardEvent( CGKeyboardEvent& rdstEvent, const CKbdEvent& rsrcEvent, void* pvView );

	virtual BOOL KeyDown( const CGKeyboardEvent& rEvent );
	virtual BOOL KeyUp( const CGKeyboardEvent& rEvent );
};

#endif //!___G_UI__PH___
