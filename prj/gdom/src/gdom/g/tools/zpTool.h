#ifndef ___G_ZOOM_PAN_TOOL__PH___
#define ___G_ZOOM_PAN_TOOL__PH___

#include "zTool.h"

class GDOM_EXT_CLASS CGIZoomPanTool : public CGIZoomTool
{
	DECL_GTPYECLASS_DYNCREATE(CGIZoomPanTool)

public:
	enum UI_MODE { 
		ZOOM_IN_UI_MODE		= 30, 
		ZOOM_OUT_UI_MODE	= 31,
	};

public:
	CGIZoomPanTool();
	virtual ~CGIZoomPanTool();

	///{{ Reimplemented
	virtual BOOL Draw( CDC& rDC, RECT& rRect, BOOL& rbResult );
	virtual UINT HitTest( const CPoint& rpoint, BOOL& rbResult );
	virtual BOOL On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage, BOOL& rbResult );

	virtual BOOL OnMouseWheel( const CMouseEvent& rEvent, BOOL& rbResult );
	virtual BOOL OnMouseMove( const CMouseEvent& rEvent, BOOL& rbResult );
	
	virtual BOOL OnLButtonDown( const CMouseEvent& rEvent, BOOL& rbResult );
	virtual BOOL OnLButtonUp( const CMouseEvent& rEvent, BOOL& rbResult );
	virtual BOOL OnLButtonDblClk( const CMouseEvent& rEvent, BOOL& rbResult );
	
	virtual BOOL OnRButtonDown( const CMouseEvent& rEvent, BOOL& rbResult );
	virtual BOOL OnRButtonUp( const CMouseEvent& rEvent, BOOL& rbResult );
	virtual BOOL OnRButtonDblClk( const CMouseEvent& rEvent, BOOL& rbResult );
	
	virtual BOOL OnMButtonDown( const CMouseEvent& rEvent, BOOL& rbResult );
	virtual BOOL OnMButtonUp( const CMouseEvent& rEvent, BOOL& rbResult );
	virtual BOOL OnMButtonDblClk( const CMouseEvent& rEvent, BOOL& rbResult );
	
	virtual BOOL OnKeyDown( const CKbdEvent& rEvent, BOOL& rbResult );
	virtual BOOL OnKeyUp( const CKbdEvent& rEvent, BOOL& rbResult );

	virtual BOOL IsUIModeKey( INT nMode, UINT nChar );
	virtual UINT GetUIModeKey( INT nMode );
	///}} Reimplemented
};

#endif //!CGIZoomPanTool
