#ifndef ___G_VIEW_WND__PH___
#define ___G_VIEW_WND__PH___

#include "gViewWndBase.h"
#include <g\tools\zpTool.h>
#include <g\type\idom\giDocument.h>
#include <g\type\idom\giView.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGViewWndEvent : public CGMutationEvent
{
public:
	static LPCTSTR DocumentChange;

public:
	CGViewWndEvent();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGViewWnd : public CGIViewWnd, public CGEventNode
{
	DECL_BASE_GTPYECLASS_DYNCREATE( CGViewWnd )

public:
	struct SUpdateElement
	{
		SUpdateElement();

		CGIElement*	m_piElement;
		CGRectF		m_grctfDrawBBox;
		BOOL		m_bRemoved;
	};

public:
	CGViewWnd();
	virtual ~CGViewWnd();

	//{{AFX_VIRTUAL(CGViewWnd)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGViewWnd)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );
	afx_msg void OnWindowPosChanged( WINDOWPOS* lpwndpos );
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg LRESULT OnUpdateDisplay( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitialUpdate();

	CGIDocument* GetDocument();
	const CGIDocument* GetDocument() const;
	BOOL SetDocument( CGIDocument* pDocument );

	CGIView* GetView();
	const CGIView* GetView() const;
	BOOL SetView( CGIView& rView );

	virtual void DrawView( Graphics& rGdip, const CRect& rrcPaint, BOOL bPrint = FALSE );

	void SetScrollRange( INT nBar, FLOAT fMinPos, FLOAT fMaxPos,
						 BOOL bRedraw = TRUE );

	void UpdateScrollBars();

	virtual BOOL OnScroll( UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE );
	virtual BOOL OnScrollBy( CSize sizeScroll, BOOL bDoScroll = TRUE );

	void SetScrollSizes( INT nViewWidth, INT nViewHeight, 
						 INT nPageWidth = 0, INT nPageHeight = 0,
						 INT nLineWidth = 0, INT nLineHeight = 0 );
	void SetScrollSizes( const SIZE& rsizeTotal,
						 const SIZE& rsizePage = nullSize,
						 const SIZE& rsizeLine = nullSize );

	virtual CGIUITool* CreateTool( const CGType& rType );

	CGIZoomTool& GetZoomTool() const;
	void SetZoomTool( CGIZoomTool& rZoomTool );

	virtual CGIUITool* GetActiveTool();
	virtual void SetActiveTool( CGIUITool* pTool );

	virtual INT FindUpdateElementInsertPos( const CGIElement& riElement, INT* pnPosition = NULL ) const;
	virtual BOOL UpdateElement( CGEvent& rEvent );
	virtual BOOL UpdateElement( CGIElement& riElement, LPCTSTR pctszEventType, CGIAttr* piAttr = NULL );

	overrided BOOL UpdateCursor();
	overrided BOOL OnMouseWheel( const CMouseEvent& rEvent );
	overrided BOOL OnMouseMove( const CMouseEvent& rEvent );

	overrided BOOL OnLButtonDown( const CMouseEvent& rEvent );
	overrided BOOL OnLButtonUp( const CMouseEvent& rEvent );
	overrided BOOL OnLButtonDblClk( const CMouseEvent& rEvent );

	overrided BOOL OnRButtonDown( const CMouseEvent& rEvent );
	overrided BOOL OnRButtonUp( const CMouseEvent& rEvent );
	overrided BOOL OnRButtonDblClk( const CMouseEvent& rEvent );

	overrided BOOL OnMButtonDown( const CMouseEvent& rEvent );
	overrided BOOL OnMButtonUp( const CMouseEvent& rEvent );
	overrided BOOL OnMButtonDblClk( const CMouseEvent& rEvent );

	overrided BOOL OnKeyDown( const CKbdEvent& rEvent );
	overrided BOOL OnKeyUp( const CKbdEvent& rEvent );

	overrided void CopyImage( CDC& rDC, RECT& rRect );

	//{{AFX_Event_Link
	void OnUpdateAttr( CGEvent& rEvent );
	void OnNodeInsertedEvent( CGEvent& rEvent );
	void OnNodeRemovedEvent( CGEvent& rEvent );
	void OnNodeInsertedIntoDocumentEvent( CGEvent& rEvent );
	void OnNodeRemovedFromDocumentEvent( CGEvent& rEvent );
	void OnZoomEvent( CGZoomEvent& rEvent );
	void OnScrollEvent( CGScrollEvent& rEvent );
	//}}AFX_Event_Link
	DECLARE_EVENT_LINK()

public:
	PointF			m_ptfView;
	PointF			m_ptfViewWnd;
	CGIView*		m_pView;
	CGIZoomTool*	m_pzTool;
	CGIUITool*		m_pActiveTool;

protected:
	CGIDocument*	m_pDocument;
	CSize			m_cbScrollPageSize;
	CSize			m_cbScrollLineSize;

	CArray<SUpdateElement, SUpdateElement&> m_arrUpdateElement;
	CGRectF			m_grctfUpdateElementBBox;
	BOOL			m_bPostedUpdateDisplay;
	BOOL			m_bDisplayModified;

private:
	Bitmap*			m_pgbmp;
	INT				m_nBmpCx;
	INT				m_nBmpCy;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
inline CGIDocument* CGViewWnd::GetDocument() {
	return m_pDocument; }

inline const CGIDocument* CGViewWnd::GetDocument() const {
	return m_pDocument; }

inline CGIView* CGViewWnd::GetView() {
	return m_pView; }

inline const CGIView* CGViewWnd::GetView() const {
	return m_pView; }

#endif //!___G_VIEW_WND__PH___