#ifndef ___G_ELEMENT_LINE_TOOL_PH___
#define ___G_ELEMENT_LINE_TOOL_PH___

#include "eTool.h"
#include <g\type\idom\giLineElement.h>

class GDOM_EXT_CLASS CGILineElementTool : public CGIElementTool
{
	DECL_GTPYECLASS_DYNCREATE(CGILineElementTool)

	enum HIT_TEST {
		HT_LINE			= 1, 
		HT_FIRSTPOINT	= HT_POINT, 
		HT_SECONDPOINT	= HT_POINT + 1, 
	};

	enum UI_STATE {
		FIRST_POINT_DRAG_UI_STATE	= 1,
		SECOND_POINT_DRAG_UI_STATE	= 2,
		MOVE_UI_STATE				= 3,
	};

	enum UI_MODE { 
		LINE_TOOL_UI_MODE = 256,
	};

public:
	CGILineElementTool();

	virtual void GetHandlePoints( PointF* pptf ) const;
	void GetHandlePoints( const PointF& rptfStart, 
						  const PointF& rptfEnd, 
						  PointF* pptf ) const;
	void DrawTracker( const PointF& rptfStart, 
					const PointF& rptfEnd, 
					CDC& rDC, RECT& rRect );

	///{{ Reimplemented
	overrided BOOL DrawTracker( CDC& rDC, RECT& rRect );
	virtual BOOL Draw( CDC& rDC, RECT& rRect );
	overrided UINT HitTest( const CPoint& rpoint );
	virtual UINT HitTest( const Region& rrgn );
	overrided BOOL On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage );

	overrided void InvalidateRect( BOOL bTracker = FALSE ) const;
	overrided void GetTrackerPath( GraphicsPath& rgpath, const Matrix* pmtx = (Matrix*)-1 ) const;

	overrided void MoveTracker( const PointF& rptfOffset );
	overrided void UpdateTracker();

	virtual BOOL OnMouseMove( const CMouseEvent& rEvent );
	overrided BOOL OnLButtonDown( const CMouseEvent& rEvent );
	virtual BOOL OnLButtonUp( const CMouseEvent& rEvent );
	///}} Reimplemented

protected:
	PointF	m_ptfTrackStart;
	PointF	m_ptfTrackEnd;

	PointF	m_ptfLineStart;
	PointF	m_ptfLineEnd;
};

#endif //!___G_ELEMENT_LINE_TOOL_PH___

