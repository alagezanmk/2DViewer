#ifndef ___G_PAN_TOOL__PH___
#define ___G_PAN_TOOL__PH___

#include "uiTool.h"

class GDOM_EXT_CLASS CGIPanTool : public CGIUITool
{
	DECL_GTPYECLASS_DYNCREATE(CGIPanTool)
public:
	enum UI_MODE { 
		PAN_UI_MODE = 1 
	};

	enum UI_STATE { 
		PANNING_UI_STATE = 1,
	};

	enum HIT_TEST {
		HT_PAN = 0,
	};

public:
	CGIPanTool();

protected:
	virtual ~CGIPanTool();

public:
	void Scroll( const CPoint& rpt );
	
	///{{ Reimplemented
	virtual INT GetDrawType() const;
	virtual BOOL Draw( CDC& rDC, RECT& rRect );
	virtual void DrawBkgndGrid( CDC& rDC, CRect& rRect );

	overrided UINT HitTest( const CPoint& rpoint );
	overrided BOOL On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage );
	virtual BOOL OnMouseMove( const CMouseEvent& rEvent );
	overrided BOOL OnLButtonDown( const CMouseEvent& rEvent );
	virtual BOOL OnLButtonUp( const CMouseEvent& rEvent );
	///}} Reimplemented

protected:
	BOOL StartPan( const CPoint& rpt );
	void Pan( const CPoint& rpt );
	void EndPan();
	BOOL CopyPanImage();
	void DrawPanImage( CDC& rDC );

public:
	CGPointF	m_gptfViewOrigin;
	CGSizeF		m_gcbViewScrollSize;

	HBITMAP		m_hPanBmp;
	CPoint		m_ptPanStart;
	CPoint		m_ptPanOffset;
};

#endif //!___G_PAN_TOOL__PH___
