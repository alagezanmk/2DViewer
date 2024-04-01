#ifndef ___G_ELEMENT_RECT_TOOL_PH___
#define ___G_ELEMENT_RECT_TOOL_PH___

#include "eTool.h"
#include <g\type\idom\giRectElement.h>

class GDOM_EXT_CLASS CGIRectElementTool : public CGIElementTool
{
	DECL_GTPYECLASS_DYNCREATE(CGIRectElementTool)

	enum HIT_TEST {
		HT_TOPLEFT		= 0, 
		HT_TOPRIGHT		= 1, 
		HT_BOTTOMRIGHT	= 2, 
		HT_BOTTOMLEFT	= 3,
		HT_TOP			= 4, 
		HT_RIGHT		= 5, 
		HT_BOTTOM		= 6, 
		HT_LEFT			= 7, 
		HT_MIDDLE		= 8,

		HT_ROTATE		= 9,
	};

	enum UI_STATE {
		NEW_UI_STATE	= 1,
		ROTATE_UI_STATE	= 2,
		MOVE_UI_STATE	= 3,
	};

	enum UI_MODE { 
		RECT_TOOL_UI_MODE = 256,
	};

public:
	CGIRectElementTool();

	virtual void GetHandlePoints( PointF* pptf, INT nCount = 4 ) const;
	void GetHandlePoints( const PointF& rptfTopLeft, 
						  const PointF& rptfBottomRight, 
						  PointF* pptf, INT nCount = 4 ) const;
	void DrawTracker( const PointF& rptfTopLeft, 
					  const PointF& rptfBottomRight, 
					  CDC& rDC, RECT& rRect );

	///{{ Reimplemented
	overrided BOOL DrawTracker( CDC& rDC, RECT& rRect );
	virtual BOOL Draw( CDC& rDC, RECT& rRect );
	overrided UINT HitTest( const CPoint& rpoint );
	virtual UINT HitTest( const Region& rrgn );
	overrided BOOL On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage );

	overrided void InvalidateRect( BOOL bTracker = FALSE ) const;
	overrided void GetTrackerPath( GraphicsPath& rgpath, const Matrix* pmtx = (Matrix*)-1 ) const;

	overrided void UpdateTracker();

	virtual BOOL OnMouseWheel( const CMouseEvent& rEvent );
	virtual BOOL OnMouseMove( const CMouseEvent& rEvent );
	overrided BOOL OnLButtonDown( const CMouseEvent& rEvent );
	virtual BOOL OnLButtonUp( const CMouseEvent& rEvent );
	///}} Reimplemented

protected:
	PointF	m_ptfTrackTopLeft;
	PointF	m_ptfTrackBottomRight;

	PointF	m_ptfTopLeft;
	PointF	m_ptfBottomRight;

	BOOL	m_bChangeWidth;
	BOOL	m_bChangeHeight;
};

#endif //!___G_ELEMENT_RECT_TOOL_PH___

