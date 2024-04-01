#ifndef ___G_ZOOM_TOOL__PH___
#define ___G_ZOOM_TOOL__PH___

#include "pTool.h"

class GDOM_EXT_CLASS CGIZoomTool : public CGIPanTool
{
	DECL_GTPYECLASS_DYNCREATE(CGIZoomTool)
public:
	enum UI_MODE { 
		ZOOM_UI_MODE	 = 20, 
	};

	enum UI_STATE { 
		ZOOM_OUT_UI_STATE = 1
	};

	enum HIT_TEST {
		HT_ZOOM_IN	= 0,
		HT_ZOOM_OUT	= 1,
	};

public:
	CGIZoomTool();
	virtual ~CGIZoomTool();

	void Zoom( CRect& rRect, BOOL bZoomIn );
	void Zoom( const CPoint& rpt, FLOAT fScale, BOOL bZoomToWindowCenter = FALSE );

	overrided UINT HitTest( const CPoint& rpoint );
	overrided BOOL On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage );

	overrided BOOL OnLButtonDown( const CMouseEvent& rEvent );

	overrided BOOL OnKeyDown( const CKbdEvent& rEvent );
	overrided BOOL OnKeyUp( const CKbdEvent& rEvent );

	virtual BOOL IsUIModeKey( INT nMode, UINT nChar );
	virtual UINT GetUIModeKey( INT nMode );

	virtual BOOL IsUIStateKey( INT nMode, INT nState, UINT nChar );
	virtual UINT GetUIStateKey( INT nMode, INT nState );

protected:
	FLOAT		m_fMinScale;
	FLOAT		m_fMaxScale;

	BOOL		m_bKeepViewPoint;
	BOOL		m_bZoomOutClicked;
};

#endif //!___G_ZOOM_TOOL__PH___
