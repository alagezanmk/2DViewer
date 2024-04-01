#ifndef ___RECT_TRACK_EX__PH___
#define ___RECT_TRACK_EX__PH___

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CRectTrackerEx : public CRectTracker
{
public:
	CRectTrackerEx()
	{
		m_bSetcursor = FALSE;
		m_pWnd = NULL;
		m_bMinSize = FALSE;
		m_szSize.cx = 1;
		m_szSize.cy = 1;
	}

	BOOL TrackRubberBand( CWnd* pWnd, CPoint point, BOOL bAllowInvert = TRUE );
	BOOL TrackHandle( int nHandle, CWnd* pWnd, CPoint point, CWnd* pWndClipTo );
	virtual void DrawTrackerRect( LPCRECT lpRect, CWnd* pWndClipTo, CDC* pDC, CWnd* pWnd );

private:
	void OnChangedRect( const CRect& rectOld );
	BOOL m_bSetcursor;

public:
	CWnd*		m_pWnd;
	BOOL		m_bMinSize;
	CSize		m_szSize;
};

#endif ___RECT_TRACK_EX__PH___