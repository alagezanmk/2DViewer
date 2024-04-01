#include "stdafx.h"
#include <g\wnd\gViewWnd.h>
#include <cu\key.win.h>
#include <cu\msg.h>
//#include <g\gdom\gdom.h>
#include <g\type\idom\giRectElement.h>
#include <g\type\idom\giTransformElement.h>
#include <g\type\gElementPriv.h>
#include <g\tools\sTool.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
LPCTSTR CGViewWndEvent::DocumentChange = _T("DocumentChange");
CGViewWndEvent::CGViewWndEvent() 
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
CGViewWnd::SUpdateElement::SUpdateElement()
{
	m_piElement = NULL;
	m_grctfDrawBBox.SetRectEmpty();
	m_bRemoved = FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#define _WM_UPDATE_DISPLAY	(WM_USER + 1000)

IMPL_BASE_GTPYECLASS_DYNCREATE( CGViewWnd, _T("viewWnd") )
BEGIN_MESSAGE_MAP(CGViewWnd, CGIViewWnd)
	//{{AFX_MSG_MAP(CGViewWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_MESSAGE( _WM_UPDATE_DISPLAY, OnUpdateDisplay )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENT_LINK( CGViewWnd, CGEventTarget )
	ON_EVT_PHASE( CGMutationEvent::DOMNodeInserted, CGEvent::CAPTURING_PHASE, OnNodeInsertedEvent )
	ON_EVT_PHASE( CGMutationEvent::DOMNodeRemoved, CGEvent::CAPTURING_PHASE, OnNodeRemovedEvent )
	ON_EVT_PHASE( CGMutationEvent::DOMNodeInsertedIntoDocument, CGEvent::CAPTURING_PHASE, OnNodeInsertedIntoDocumentEvent )
	ON_EVT_PHASE( CGMutationEvent::DOMNodeRemovedFromDocument, CGEvent::CAPTURING_PHASE, OnNodeRemovedFromDocumentEvent )
	ON_EVT_PHASE( CGDomMutationEvent::DOMExtUpdateAttr, CGEvent::CAPTURING_PHASE, OnUpdateAttr )

	ON_EVT_PHASE_ZOOM( CGEvent::CAPTURING_PHASE, OnZoomEvent )
	ON_EVT_PHASE_SCROLL( CGEvent::CAPTURING_PHASE, OnScrollEvent )
END_EVENT_LINK()

CGViewWnd::CGViewWnd() 
{
	m_pgInstanceType = &GetClassType();

	m_pDocument = NULL;
	m_pView = NULL;
	m_pzTool = NULL;
	m_pActiveTool = NULL;

	m_cbScrollPageSize.cx = 10;
	m_cbScrollPageSize.cy = 10;
	m_cbScrollLineSize = m_cbScrollPageSize;
	m_pgbmp = NULL;
	m_nBmpCx = 0;
	m_nBmpCy = 0;
	m_grctfUpdateElementBBox.SetRectEmpty();
	m_bPostedUpdateDisplay = FALSE;
	m_bDisplayModified = TRUE;
}

CGViewWnd::~CGViewWnd()
{
	if( m_pgbmp )
		DeleteBitmap( m_pgbmp );

	if( m_pActiveTool )
		m_pActiveTool->Release();

	if( m_pzTool )
		m_pzTool->Release();

	if( m_pDocument )
		SetDocument( NULL );

	if( m_pView )
	{
		RemoveChild( *m_pView );
		m_pView->Release();
	}

	RemoveEventListener( CGZoomEvent::EVENT, *this, TRUE );
	RemoveEventListener( CGScrollEvent::EVENT, *this, TRUE );
	RemoveEventListener( CGDomMutationEvent::DOMExtUpdateAttr, *this, TRUE );
}

CGIUITool* CGViewWnd::CreateTool( const CGType& rType )
{
	if( rType == CGIZoomTool::GetClassType() )
		return new CGIZoomTool;

	if( rType == CGIPanTool::GetClassType() )
		return new CGIPanTool;

	if( rType == CGIPanTool::GetClassType() )
		return new CGIPanTool;

	return NULL;
}

BOOL CGViewWnd::OnEraseBkgnd(CDC* pDC)  {
	return TRUE; }

void CGViewWnd::OnPaint() 
{
	CRect rctPaint;
	GetUpdateRect( rctPaint, FALSE  );

	CPaintDC dc(this); // device context for painting
	if( m_pActiveTool 
		&& CGIUITool::LOWER_DRAW_TYPE == m_pActiveTool->GetDrawType() 
		&& m_pActiveTool->Draw( dc, rctPaint ) )
		return;

	const RECT& rrcPaint = rctPaint;
	CRect rcPaint = rrcPaint;

	INT nDrawX = rcPaint.left;
	INT nDrawY = rcPaint.top;
	INT nDrawCx = rcPaint.right - rcPaint.left;
	INT nDrawCy = rcPaint.bottom - rcPaint.top;
	if( nDrawCx <= 0 || nDrawCy <= 0 )
		return;

	if( NULL == m_pgbmp || m_bDisplayModified 
		|| (m_pView && m_pView->GetModified()) )
	{
		CRect rcClient;
		GetClientRect( rcClient );

		INT nCCx = rcClient.right;
		INT nCCy = rcClient.bottom;

		if( NULL == m_pgbmp )
			VERIFY( m_pgbmp = CreateBitmap( nCCx, nCCy, PixelFormat24bppRGB ) );
	
		if( m_pgbmp )
		{
			Graphics gdip( m_pgbmp );

			COLORREF crfAppWrkSpace = GetSysColor( COLOR_APPWORKSPACE );
			SolidBrush gbrAppWkrSpace( Color( 255, GetRValue( crfAppWrkSpace ), GetGValue( crfAppWrkSpace ), GetBValue( crfAppWrkSpace ) ) );
			gdip.FillRectangle( &gbrAppWkrSpace, 0, 0, nCCx, nCCy );

			gdip.SetCompositingQuality( CompositingQualityHighQuality );
			gdip.SetSmoothingMode( SmoothingModeAntiAlias );

			DrawView( gdip, CRect( 0, 0, nCCx, nCCy ), FALSE );
			m_bDisplayModified = FALSE;

			if( m_pView )
				m_pView->SetModified( FALSE );

			//Sleep( 1000 );
		}
	}

	if( m_pgbmp )
	{
		Graphics gdip( dc.m_hDC );
		gdip.DrawImage( m_pgbmp, (FLOAT)nDrawX, (FLOAT)nDrawY, 
								(FLOAT)nDrawX, (FLOAT)nDrawY, 
								(FLOAT)nDrawCx, (FLOAT)nDrawCy,
								UnitPixel );
	}

	if( 0 && m_pView )
	{
		CDC rDC;
		rDC.Attach( dc.m_hDC );

		FLOAT ox, oy;
		FLOAT sx, sy;
		FLOAT slx, sly;

		m_pView->GetScale( sx, sy );
		m_pView->GetOrigin( ox, oy );
		m_pView->GetScrollableSize( slx, sly );
		
		CString csz;
		csz.Format( _T("View(%f, %f)\n")
					_T("ViewWnd(%f, %f)\n")
					_T("Scrollable(%f, %f)\n") 
					_T("Scale(%f, %f)\n") 
					_T("Origin(%f, %f)"), 
								m_ptfView.X, m_ptfView.Y, 
								m_ptfViewWnd.X, m_ptfViewWnd.Y,
								slx, sly,
								sx, sy, 
								ox, oy );

		rDC.SetBkMode( TRANSPARENT );
		rDC.SetTextColor( RGB( 0, 0, 0 ) );

		CRect rct;
		GetClientRect( rct );
		rDC.DrawText( csz, rct, DT_TOP | DT_LEFT );
		//rDC.TextOut( 0, 0, csz );
		rDC.Detach();
	}
}

void CGViewWnd::DrawView( Graphics& rGdip, const CRect& rrcPaint, BOOL bPrint /*= FALSE*/ )
{
	if( m_pView )
	{
		m_pView->Draw( rGdip );

		if( m_pDocument )
		{
			CGIElement* pRootElement = m_pDocument->GetRootElement();
			if( pRootElement )
			{
				CGSaveTransform st( rGdip );

				Matrix mtx;
				m_pView->GetScreenCTM( mtx );
				rGdip.MultiplyTransform( &mtx );

				pRootElement->Draw( rGdip );
			}
		}
	}
}

void CGViewWnd::CopyImage( CDC& rDC, RECT& rRect )
{
	if( NULL == m_pgbmp )
		return;

	Graphics gdip( rDC.m_hDC );
	INT nCx = rRect.right - rRect.left;
	INT nCy = rRect.bottom - rRect.top;
	gdip.DrawImage( m_pgbmp, rRect.left, rRect.top, nCx, nCy );
}	

void CGViewWnd::OnUpdateAttr( CGEvent& rEvent ) {
	UpdateElement( rEvent ); }

void CGViewWnd::OnNodeInsertedEvent( CGEvent& rEvent ){
	UpdateElement( rEvent ); }

void CGViewWnd::OnNodeRemovedEvent( CGEvent& rEvent ) {
	UpdateElement( rEvent ); }

void CGViewWnd::OnNodeInsertedIntoDocumentEvent( CGEvent& rEvent ){
	UpdateElement( rEvent ); }

void CGViewWnd::OnNodeRemovedFromDocumentEvent( CGEvent& rEvent ) {
	UpdateElement( rEvent ); }

void CGViewWnd::OnZoomEvent( CGZoomEvent& rEvent ) {
	UpdateScrollBars(); }

void CGViewWnd::OnScrollEvent( CGScrollEvent& rEvent ) {
	UpdateScrollBars(); }

BOOL CGViewWnd::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
	if( HTCLIENT == nHitTest && TRUE == UpdateCursor() )
		return TRUE;

	return CWnd::OnSetCursor( pWnd, nHitTest, message );
}

BOOL CGViewWnd::UpdateCursor()
{
	// If cursor is not on the View, don't change cursor
	CPoint point = g_alxKeyState.ptCursor;
	if( this != WindowFromPoint( point ) )
		return FALSE;

	ScreenToClient( &point );

	UINT nHitTest;
	if( m_pActiveTool )
	{
		nHitTest = m_pActiveTool->HitTest( point );
		if( m_pActiveTool->On_SetCursor( this, nHitTest, 0 ) )
			return TRUE;
	}

	if( m_pView )
	{
		nHitTest = m_pView->HitTest( point );
		if( m_pView->On_SetCursor( this, nHitTest, 0 ) )
			return TRUE;
	}

	return FALSE;
}

BOOL CGViewWnd::SetDocument( CGIDocument* pDocument )
{
	if( pDocument && m_pDocument == pDocument )
		return FALSE;

	if( m_pDocument )
	{
		CGViewWndEvent event;
		event.InitEvent( CGViewWndEvent::DocumentChange, TRUE, FALSE, 
						 m_pDocument, NULL, NULL, NULL, CGViewWndEvent::REMOVAL );

		DispatchEvent( event );

		m_pDocument->RemoveEventListener( CGDomMutationEvent::DOMExtUpdateAttr, *this, TRUE );

		m_pDocument->RemoveEventListener( CGMutationEvent::DOMNodeInserted, *this, TRUE );
		m_pDocument->RemoveEventListener( CGMutationEvent::DOMNodeRemoved, *this, TRUE );

		m_pDocument->RemoveEventListener( CGMutationEvent::DOMNodeInsertedIntoDocument, *this, TRUE );
		m_pDocument->RemoveEventListener( CGMutationEvent::DOMNodeRemovedFromDocument, *this, TRUE );

		m_pDocument->Release();
	}

	m_pDocument = pDocument;
	if( m_pDocument )
	{
		m_pDocument->AddRef();

		m_pDocument->AddEventListener( CGDomMutationEvent::DOMExtUpdateAttr, *this, TRUE );

		m_pDocument->AddEventListener( CGMutationEvent::DOMNodeInserted, *this, TRUE );
		m_pDocument->AddEventListener( CGMutationEvent::DOMNodeRemoved, *this, TRUE );

		m_pDocument->AddEventListener( CGMutationEvent::DOMNodeInsertedIntoDocument, *this, TRUE );
		m_pDocument->AddEventListener( CGMutationEvent::DOMNodeRemovedFromDocument, *this, TRUE );

		CGViewWndEvent event;
		event.InitEvent( CGViewWndEvent::DocumentChange, TRUE, FALSE, 
						 m_pDocument, NULL, NULL, NULL, CGViewWndEvent::ADDITION );

		DispatchEvent( event );
	}

	return TRUE;
}

BOOL CGViewWnd::SetView( CGIView& rView ) 
{
	if( m_pView || NULL == &rView )
		return FALSE;

	m_pView = &rView;
	m_pView->AddRef();
	return TRUE;
}

BOOL CGViewWnd::OnInitialUpdate()
{
	if( NULL == m_pView ) 
	{
		VERIFY( m_pView = new CGIView );
		if( NULL == m_pView )
			return FALSE;

		m_pView->AddRef();
	}

	AppendChild( *m_pView );
	m_pView->OnInitialUpdate();

	if( NULL == m_pzTool )
	{
		CGIZoomTool* pzTool = (CGIZoomTool*)CreateTool( CGIZoomTool::GetClassType() );
		ASSERT( pzTool );
		if( pzTool )
		{
			SetZoomTool( *pzTool );
			SetActiveTool( pzTool );
		}
	}

	m_pView->LockMultipleEvent( CGScrollEvent::EVENT, CGZoomEvent::EVENT, 
								CGDomMutationEvent::DOMExtUpdateAttr, NULL );

	AddEventListener( CGZoomEvent::EVENT, *this, TRUE );
	AddEventListener( CGScrollEvent::EVENT, *this, TRUE );
	AddEventListener( CGDomMutationEvent::DOMExtUpdateAttr, *this, TRUE );

	SetScrollSizes( 10, 10 );
	
	m_pView->UnlockMultipleEvent( CGDomMutationEvent::DOMExtUpdateAttr,
								  CGScrollEvent::EVENT, 
								  CGZoomEvent::EVENT, NULL );

	return TRUE;
}

void CGViewWnd::SetScrollSizes( INT nViewWidth, INT nViewHeight,
							    INT nPageWidth /*= 0*/, INT nPageHeight /*= 0*/,
							    INT nLineWidth /*= 0*/, INT nLineHeight /*= 0*/ )
{
	if( NULL == m_pView )
		return;

	ASSERT( nViewWidth >= 0 && nViewHeight >= 0 );

	CRect rect;
	GetClientRect( rect );

	m_pView->LockMultipleEvent( CGScrollEvent::EVENT, CGZoomEvent::EVENT, 
								CGDomMutationEvent::DOMExtUpdateAttr, NULL );

	m_pView->SetSize( (FLOAT)rect.right, (FLOAT)rect.bottom );
	m_pView->SetDocSize( (FLOAT)nViewWidth, (FLOAT)nViewHeight );

	m_cbScrollPageSize.cx = nPageWidth;
	m_cbScrollPageSize.cy = nPageHeight;

	m_cbScrollLineSize.cx = nLineWidth;
	m_cbScrollLineSize.cy = nLineHeight;

	if( 0.f == m_cbScrollPageSize.cx )
		m_cbScrollPageSize.cx = nViewWidth / 10;

	if( 0.f == m_cbScrollPageSize.cy )
		m_cbScrollPageSize.cy = nViewHeight / 10;

	if( 0.f == m_cbScrollLineSize.cx )
		m_cbScrollLineSize.cx = m_cbScrollPageSize.cx / 10;

	if( 0.f == m_cbScrollLineSize.cy )
		m_cbScrollLineSize.cy = m_cbScrollPageSize.cy / 10;

	m_pView->UnlockMultipleEvent( CGDomMutationEvent::DOMExtUpdateAttr,
								  CGScrollEvent::EVENT, 
								  CGZoomEvent::EVENT, NULL );

	UpdateScrollBars();
}

void CGViewWnd::SetScrollSizes( const SIZE& sizeTotal,
								const SIZE& sizePage /*= nullSize*/,
								const SIZE& sizeLine /*= nullSize*/ )
{
	SetScrollSizes( sizeTotal.cx, sizeTotal.cy, 
				    sizePage.cx, sizePage.cy,
				    sizeLine.cx, sizeLine.cy );
}

void CGViewWnd::OnWindowPosChanged( WINDOWPOS* lpwndpos )
{
	CRect rctClient;
	GetClientRect( rctClient );
	INT nCCx = rctClient.Width();
	INT nCCy = rctClient.Height();
	if( m_pgbmp && (m_nBmpCx != nCCx || m_nBmpCy != nCCy) )
	{
		DeleteBitmap( m_pgbmp );
		m_pgbmp = NULL;
	}

	CGIViewWnd::OnWindowPosChanged( lpwndpos );

	if( m_nBmpCx != nCCx || m_nBmpCy != nCCy )
	{
		if( m_pView )
			m_pView->SetSize( (FLOAT)nCCx, (FLOAT)nCCy );
	}

	m_nBmpCx = nCCx;
	m_nBmpCy = nCCy;
}

void CGViewWnd::SetScrollRange( INT nBar, FLOAT fMinPos, FLOAT fMaxPos,
								BOOL bRedraw /*= TRUE*/ )
{
	INT nMinPos = (INT)fMinPos;
	INT nMaxPos = (INT)ceil( fMaxPos );
	CGIViewWnd::SetScrollRange( nBar, nMinPos, nMaxPos, bRedraw );
}

void CGViewWnd::UpdateScrollBars()
{
	if( NULL == m_pView )
		return;

	FLOAT fScrollableCx, fScrollableCy;
	m_pView->GetScrollableSize( fScrollableCx, fScrollableCy );
	
	FLOAT fScrollX, fScrollY;
	m_pView->GetOrigin( fScrollX, fScrollY );
	
	if( fScrollableCx )
	{
		SetScrollRange( SB_HORZ, 0, fScrollableCx, FALSE );
		SetScrollPos( SB_HORZ, (INT)fScrollX, TRUE );
	}
	else
		SetScrollRange( SB_HORZ, 0, 0, TRUE );
	
	if( fScrollableCy )
	{
		SetScrollRange( SB_VERT, 0, fScrollableCy, FALSE );
		SetScrollPos( SB_VERT, (INT)fScrollY, TRUE );
	}
	else
		SetScrollRange( SB_VERT, 0, 0, TRUE );

	Invalidate( FALSE );
}

void CGViewWnd::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_TRACKPOS;
	GetScrollInfo( SB_HORZ, &si, SIF_TRACKPOS );
	nPos = si.nTrackPos;

	OnScroll( MAKEWORD(nSBCode, -1), nPos );
}

void CGViewWnd::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_TRACKPOS;
	GetScrollInfo( SB_VERT, &si, SIF_TRACKPOS );
	nPos = si.nTrackPos;

	OnScroll( MAKEWORD(-1, nSBCode), nPos );
}

BOOL CGViewWnd::OnScroll( UINT nScrollCode, UINT nPos, BOOL bDoScroll /*= TRUE*/ )
{
	// calc new x position
	int x = GetScrollPos( SB_HORZ );
	int xOrig = x;

	switch( LOBYTE(nScrollCode) )
	{
	case SB_TOP:
		x = 0;
		break;
	case SB_BOTTOM:
		x = INT_MAX;
		break;

	case SB_LINEUP:
		x -= m_cbScrollLineSize.cx;
		break;

	case SB_LINEDOWN:
		x += m_cbScrollLineSize.cx;
		break;

	case SB_PAGEUP:
		x -= m_cbScrollPageSize.cx;
		break;

	case SB_PAGEDOWN:
		x += m_cbScrollPageSize.cx;
		break;

	case SB_THUMBTRACK:
		x = nPos;
		break;
	}

	// calc new y position
	int y = GetScrollPos( SB_VERT );
	int yOrig = y;

	if( SB_ENDSCROLL == LOBYTE(nScrollCode) )
	{
		x = x;
	}

	switch( HIBYTE(nScrollCode) )
	{
	case SB_TOP:
		y = 0;
		break;

	case SB_BOTTOM:
		y = INT_MAX;
		break;

	case SB_LINEUP:
		y -= m_cbScrollLineSize.cy;
		break;

	case SB_LINEDOWN:
		y += m_cbScrollLineSize.cy;
		break;

	case SB_PAGEUP:
		y -= m_cbScrollPageSize.cy;
		break;

	case SB_PAGEDOWN:
		y += m_cbScrollPageSize.cy;
		break;

	case SB_THUMBTRACK:
		y = nPos;
		break;
	}

	BOOL bResult = OnScrollBy( CSize(x - xOrig, y - yOrig), bDoScroll );
	if( bResult && bDoScroll )
		UpdateWindow();

	return bResult;
}

BOOL CGViewWnd::OnScrollBy( CSize sizeScroll, BOOL bDoScroll /*= TRUE*/ )
{
	int xOrig, x;
	int yOrig, y;

	// don't scroll if there is no valid scroll range (ie. no scroll bar)
	CScrollBar* pBar;
	DWORD dwStyle = GetStyle();
	pBar = GetScrollBarCtrl( SB_VERT );
	if( (pBar != NULL && !pBar->IsWindowEnabled() ) ||
		(pBar == NULL && !(dwStyle & WS_VSCROLL)) )
	{
		// vertical scroll bar not enabled
		sizeScroll.cy = 0;
	}

	pBar = GetScrollBarCtrl( SB_HORZ );
	if( (pBar != NULL && !pBar->IsWindowEnabled()) ||
		(pBar == NULL && !(dwStyle & WS_HSCROLL)) )
	{
		// horizontal scroll bar not enabled
		sizeScroll.cx = 0;
	}

	// adjust current x position
	xOrig = x = GetScrollPos( SB_HORZ );
	int xMax = GetScrollLimit( SB_HORZ );
	x += sizeScroll.cx;
	if( x < 0 )
		x = 0;
	else if( x > xMax )
		x = xMax - 1;

	// adjust current y position
	yOrig = y = GetScrollPos( SB_VERT );
	int yMax = GetScrollLimit( SB_VERT );
	y += sizeScroll.cy;
	if( y < 0 )
		y = 0;
	else if( y > yMax )
		y = yMax - 1;

	// did anything change?
	if( x == xOrig && y == yOrig )
		return FALSE;

	if( bDoScroll )
	{
		// do scroll and update scroll positions
		INT sx = -(x - xOrig);
		INT sy = -(y - yOrig);

		ScrollWindow( sx, sy );
		m_pView->SetOrigin( (FLOAT)x, (FLOAT)y );
		if( x != xOrig )
			SetScrollPos( SB_HORZ, x );

		if( y != yOrig )
			SetScrollPos( SB_VERT, y );
	}

	return TRUE;
}

CGIZoomTool& CGViewWnd::GetZoomTool() const {
	return *m_pzTool; }

void CGViewWnd::SetZoomTool( CGIZoomTool& rZoomTool ) 
{
	rZoomTool.AddRef();
	if( m_pzTool )
		m_pzTool->Release();

	m_pzTool = &rZoomTool; 
	m_pzTool->SetViewWindow( this );
	m_pzTool->SetView( m_pView );
}

CGIUITool* CGViewWnd::GetActiveTool() {
	return m_pActiveTool; }

void CGViewWnd::SetActiveTool( CGIUITool* pTool ) 
{
	pTool->AddRef();
	if( m_pActiveTool )
	{
		m_pActiveTool->SetView( NULL );
		m_pActiveTool->Release();
	}

	m_pActiveTool = pTool; 
	m_pActiveTool->SetViewWindow( this );
	if( m_pView )
		m_pActiveTool->SetView( m_pView );
}

BOOL CGViewWnd::OnMouseMove( const CMouseEvent& rEvent )
{
	if( 0 )
	{
		m_ptfViewWnd.X = (FLOAT)rEvent.m_ptClient.x;
		m_ptfViewWnd.Y = (FLOAT)rEvent.m_ptClient.y;

		m_ptfView = m_ptfViewWnd;
		Matrix mtxV20;
		if( m_pView )
		{
			m_pView->GetCTM( mtxV20 );
			mtxV20.Invert();
		}

		mtxV20.TransformPoints( &m_ptfView );
		Invalidate( FALSE );
	}

	if( m_pActiveTool && m_pActiveTool->OnMouseMove( rEvent ) )
		return TRUE;

	CGMouseEvent event;
	CGUI::InitMouseEvent( event, rEvent, this, m_pView );
	if( m_pView && m_pView->MouseMove( event ) )
		return TRUE;

	return CGIViewWnd::OnMouseMove( rEvent );
}

BOOL CGViewWnd::OnMouseWheel( const CMouseEvent& rEvent )
{
	if( m_pActiveTool && m_pActiveTool->OnMouseWheel( rEvent ) )
		return TRUE;

	CGMouseEvent event;
	CGUI::InitMouseEvent( event, rEvent, this, m_pView );
	if( m_pView && m_pView->MouseWheel( event ) )
		return TRUE;

	return CGIViewWnd::OnMouseWheel( rEvent );
}

BOOL CGViewWnd::OnLButtonDown( const CMouseEvent& rEvent )
{
	if( m_pActiveTool && m_pActiveTool->OnLButtonDown( rEvent ) )
		return TRUE;

	CGMouseEvent event;
	CGUI::InitMouseEvent( event, rEvent, this, m_pView );
	if( m_pView && m_pView->LButtonDown( event ) )
		return TRUE;

	return CGIViewWnd::OnLButtonDown( rEvent );
}

BOOL CGViewWnd::OnLButtonUp( const CMouseEvent& rEvent )
{
	if( m_pActiveTool && m_pActiveTool->OnLButtonUp( rEvent ) )
		return TRUE;

	CGMouseEvent event;
	CGUI::InitMouseEvent( event, rEvent, this, m_pView );
	if( m_pView && m_pView->LButtonUp( event ) )
		return TRUE;

	return CGIViewWnd::OnLButtonUp( rEvent );
}

BOOL CGViewWnd::OnLButtonDblClk( const CMouseEvent& rEvent )
{
	if( m_pActiveTool && m_pActiveTool->OnLButtonDblClk( rEvent ) )
		return TRUE;

	CGMouseEvent event;
	CGUI::InitMouseEvent( event, rEvent, this, m_pView );
	if( m_pView && m_pView->LButtonDblClk( event ) )
		return TRUE;

	return CGIViewWnd::OnLButtonDblClk( rEvent );
}

BOOL CGViewWnd::OnRButtonDown( const CMouseEvent& rEvent )
{
	m_pView->m_aViewBox.m_aEnable = !(BOOL)m_pView->m_aViewBox.m_aEnable;

	if( m_pActiveTool && m_pActiveTool->OnRButtonDown( rEvent ) )
		return TRUE;

	CGMouseEvent event;
	CGUI::InitMouseEvent( event, rEvent, this, m_pView );
	if( m_pView && m_pView->RButtonDown( event ) )
		return TRUE;

	return CGIViewWnd::OnRButtonDown( rEvent );
}

BOOL CGViewWnd::OnRButtonUp( const CMouseEvent& rEvent )
{
	if( m_pActiveTool && m_pActiveTool->OnRButtonUp( rEvent ) )
		return TRUE;

	CGMouseEvent event;
	CGUI::InitMouseEvent( event, rEvent, this, m_pView );
	if( m_pView && m_pView->RButtonUp( event ) )
		return TRUE;

	return CGIViewWnd::OnRButtonUp( rEvent );
}

BOOL CGViewWnd::OnRButtonDblClk( const CMouseEvent& rEvent )
{
	SetFocus();
	if( m_pActiveTool && m_pActiveTool->OnRButtonDblClk( rEvent ) )
		return TRUE;

	CGMouseEvent event;
	CGUI::InitMouseEvent( event, rEvent, this, m_pView );
	if( m_pView && m_pView->RButtonDblClk( event ) )
		return TRUE;

	return CGIViewWnd::OnRButtonDblClk( rEvent );
}

BOOL CGViewWnd::OnMButtonDown( const CMouseEvent& rEvent )
{
	if( m_pActiveTool && m_pActiveTool->OnMButtonDown( rEvent ) )
		return TRUE;

	CGMouseEvent event;
	CGUI::InitMouseEvent( event, rEvent, this, m_pView );
	if( m_pView && m_pView->MButtonDown( event ) )
		return TRUE;

	return CGIViewWnd::OnMButtonDown( rEvent );
}

BOOL CGViewWnd::OnMButtonUp( const CMouseEvent& rEvent )
{
	if( m_pActiveTool && m_pActiveTool->OnMButtonUp( rEvent ) )
		return TRUE;

	CGMouseEvent event;
	CGUI::InitMouseEvent( event, rEvent, this, m_pView );
	if( m_pView && m_pView->MButtonUp( event ) )
		return TRUE;

	return CGIViewWnd::OnMButtonUp( rEvent );
}

BOOL CGViewWnd::OnMButtonDblClk( const CMouseEvent& rEvent )
{
	if( m_pActiveTool && m_pActiveTool->OnMButtonDblClk( rEvent ) )
		return TRUE;

	CGMouseEvent event;
	CGUI::InitMouseEvent( event, rEvent, this, m_pView );
	if( m_pView && m_pView->MButtonDblClk( event ) )
		return TRUE;

	return CGIViewWnd::OnMButtonDblClk( rEvent );
}

BOOL CGViewWnd::OnKeyDown( const CKbdEvent& rEvent )
{
	if( m_pActiveTool && m_pActiveTool->OnKeyDown( rEvent ) )
		return TRUE;

	CGKeyboardEvent event;
	CGUI::InitKeyboardEvent( event, rEvent, this );
	if( m_pView && m_pView->KeyDown( event ) )
		return TRUE;

	return CGIViewWnd::OnKeyDown( rEvent );
}

BOOL CGViewWnd::OnKeyUp( const CKbdEvent& rEvent )
{
	if( m_pActiveTool && m_pActiveTool->OnKeyUp( rEvent ) )
		return TRUE;

	CGKeyboardEvent event;
	CGUI::InitKeyboardEvent( event, rEvent, this );
	if( m_pView && m_pView->KeyUp( event ) )
		return TRUE;

	return CGIViewWnd::OnKeyUp( rEvent );
}

static INT _Compare( const CGIElement* piElement1, const CGIElement* piElement2 )
{
	if( piElement1 == piElement2 )
		return 0;

	if( piElement1 < piElement2 )
		return -1;

	return 1;
}

INT CGViewWnd::FindUpdateElementInsertPos( const CGIElement& riElement, INT* pnPosition /*= NULL*/ ) const
{
	INT nInsertPos = 0;
	INT nCount = m_arrUpdateElement.GetSize();
	if( nCount )
	{
		INT nResult;
		const SUpdateElement* piUpdateElement = m_arrUpdateElement.GetData();
		
		/*for( INT i = nCount - 1; i >= 0 && i < 2; i-- )
		{
			if( &riElement == piUpdateElement[i].m_piElement )
			{
				if( pnPosition )
					*pnPosition = i;

				return -1;
			}

			nResult = _Compare( &riElement, piUpdateElement[i].m_piElement );
			if( 1 == nResult )
				return i;
		}

		// If size <= 2 and not statisfied the above loop condition
		// definitely insert position at zero
		if( nCount <= 2 )
			return 0;*/

		INT nTop = 0;
		INT nMiddle, nBottom = nCount - 1;

		do
		{
			nMiddle = (nBottom + nTop) / 2;
			nResult = _Compare( piUpdateElement[nMiddle].m_piElement, &riElement );
			if( 0 == nResult )
			{
				if( pnPosition )
					*pnPosition = nMiddle;

				return -1;
			}

			if( nTop == nMiddle )
				return (nResult > 0 ?nBottom :nTop);

			if( nResult < 0 )	// Middle is greater than Search item
				nBottom = nMiddle;
			else				// Middke is less than Search item
				nTop = nMiddle;
		}
		while( TRUE );
	}
	
	return 0;
}

BOOL CGViewWnd::UpdateElement( CGEvent& rEvent )
{
	if( NULL == m_hWnd )
		return FALSE;

	INT nEventPhase = rEvent.GetEventPhase(); 
	if( CGEvent::CAPTURING_PHASE != nEventPhase )
		return FALSE;

	LPCTSTR pctszEventType = rEvent.GetType();
	if( CGDomMutationEvent::DOMExtUpdateAttr == pctszEventType
		|| CGMutationEvent::DOMNodeInserted == pctszEventType
		|| CGMutationEvent::DOMNodeRemoved == pctszEventType 
		|| CGMutationEvent::DOMNodeInsertedIntoDocument == pctszEventType 
		|| CGMutationEvent::DOMNodeRemovedFromDocument == pctszEventType )
	{
		CGINode* piNode = (CGINode*)rEvent.GetTarget();
		if( piNode->IsDerivedFrom( CGIElement::GetClassType() ) )
		{
			CGIAttr* pAttr = NULL;
			if( CGDomMutationEvent::DOMExtUpdateAttr == pctszEventType )
				pAttr = (CGIAttr*)((CGMutationEvent*)&rEvent)->GetRelatedNode();
			
			UpdateElement( *((CGIElement*)piNode), pctszEventType, pAttr );
		}
	}

	return TRUE;
}

BOOL CGViewWnd::UpdateElement( CGIElement& riElement, LPCTSTR pctszEventType, CGIAttr* piAttr /*= NULL*/ )
{
	// Element updation required if any one of the Event matches, otherwise exit the function 
	BOOL bUpdateElement = CGMutationEvent::DOMNodeInserted == pctszEventType
						|| CGMutationEvent::DOMNodeRemoved == pctszEventType
						|| CGMutationEvent::DOMNodeInsertedIntoDocument == pctszEventType
						|| CGMutationEvent::DOMNodeRemovedFromDocument == pctszEventType
						|| CGDomMutationEvent::DOMExtUpdateAttr == pctszEventType;

	if( FALSE == bUpdateElement )
		return FALSE;

	// Element updation for DOMExtUpdateAttr Event cannot be updated without Attribute pointer
	ASSERT( CGDomMutationEvent::DOMExtUpdateAttr != pctszEventType 
			|| (CGDomMutationEvent::DOMExtUpdateAttr == pctszEventType && piAttr ) );

	if( CGDomMutationEvent::DOMExtUpdateAttr == pctszEventType && NULL == piAttr )
	{
		TRACE( _T("Warning Update Element was called for Event::DOMExtUpdateAttr without Attribite pointer\n") );
		return FALSE;
	}

	if( CGDomMutationEvent::DOMExtUpdateAttr == pctszEventType )
	{
		TRACE( "Update Display %x\n", GetTickCount() );

		INT nAttrType = piAttr->GetAttrType();
		if( nAttrType & CGIAttr::DISPLAY_ATTR_TYPE )
			riElement.SetNodeFlag( CGINode::DATA_DISPLAY_MODIFIED_NODE_FLAG );

		if( nAttrType & CGIAttr::CTM_ATTR_TYPE )
			riElement.SetNodeFlag( CGINode::DATA_CTM_MODIFIED_NODE_FLAG );
	}

	BOOL bPostMsg = FALSE;
	INT nFoundPosition;
	INT nInsertPos = FindUpdateElementInsertPos( riElement, &nFoundPosition );
	if( -1 != nInsertPos )
	{
		Matrix mtx;
		if( m_pView )
			m_pView->GetCTM( mtx );
			 
		SUpdateElement sUpdateElement;
		sUpdateElement.m_piElement = &riElement;
		riElement.GetDrawBBox( sUpdateElement.m_grctfDrawBBox, &mtx );
		sUpdateElement.m_bRemoved = CGMutationEvent::DOMNodeRemoved == pctszEventType 
									|| CGMutationEvent::DOMNodeRemovedFromDocument == pctszEventType;

		m_arrUpdateElement.InsertAt( nInsertPos, sUpdateElement );
		bPostMsg = TRUE;
	}
	else
	{
		SUpdateElement& rsUpdateElement = m_arrUpdateElement.ElementAt( nFoundPosition );
		ASSERT( rsUpdateElement.m_piElement == &riElement );

		if( CGMutationEvent::DOMNodeRemoved == pctszEventType 
			|| CGMutationEvent::DOMNodeRemovedFromDocument == pctszEventType )
			rsUpdateElement.m_bRemoved = TRUE;
		else if( CGMutationEvent::DOMNodeInserted == pctszEventType 
 			     || CGMutationEvent::DOMNodeInsertedIntoDocument == pctszEventType )
			rsUpdateElement.m_bRemoved = FALSE;

		bPostMsg = TRUE;
	}

	if( bPostMsg )
	{
		if( FALSE == m_bPostedUpdateDisplay )
		{
			m_bPostedUpdateDisplay = TRUE;
			PostMessage( _WM_UPDATE_DISPLAY );
		}

		return TRUE;
	}

	return FALSE;
}

LRESULT CGViewWnd::OnUpdateDisplay( WPARAM wParam, LPARAM lParam )
{
	INT nCount = m_arrUpdateElement.GetSize();
	if( 0 == nCount )
		return 0;	// Nothing there to update

	Matrix mtx;
	if( m_pView )
		m_pView->GetCTM( mtx );

	// Prepare an empty Rectangle for Bound Rect calculation
	CGRectF	grctfBBox;
	m_grctfUpdateElementBBox.SetRectEmpty();

	const SUpdateElement* piUpdateElement = m_arrUpdateElement.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		m_grctfUpdateElementBBox.UnionRect( m_grctfUpdateElementBBox, piUpdateElement[i].m_grctfDrawBBox );
		if( FALSE == piUpdateElement[i].m_bRemoved )
		{
			// Before getting Bound Rect, Update the Element
			piUpdateElement[i].m_piElement->Update();
			piUpdateElement[i].m_piElement->GetDrawBBox( grctfBBox, &mtx );
			grctfBBox.NormalizeRect();
			m_grctfUpdateElementBBox.UnionRect( m_grctfUpdateElementBBox, grctfBBox );
		}
	}

	m_arrUpdateElement.RemoveAll();

	CRect rect( (INT)floor( m_grctfUpdateElementBBox.left ),
				(INT)floor( m_grctfUpdateElementBBox.top ), 
				(INT)ceil( m_grctfUpdateElementBBox.right ), 
				(INT)ceil( m_grctfUpdateElementBBox.bottom ) );
	
	rect.InflateRect( 1, 1 );
	InvalidateRect( rect, FALSE );
	m_bDisplayModified = TRUE;
	UpdateWindow();
	m_bPostedUpdateDisplay = FALSE;
	TRACE( "Display Updated %x \n\n", GetTickCount() );
	return 0;
}