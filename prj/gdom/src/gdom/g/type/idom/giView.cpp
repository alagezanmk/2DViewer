#include "stdafx.h"
#include <g\type\idom\giView.h>
#include <g\type\gEventPriv.h>
#include <bld\gEditView.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString gs_cszVIEW_ELEMENT_TAGNAME = _T("view");
LPCTSTR CGIView::ELEMENT_TAGNAME = gs_cszVIEW_ELEMENT_TAGNAME;

IMPL_GTPYECLASS_DYNCREATE( CGIView, CGIGroup, CGIView::ELEMENT_TAGNAME )
CGIView::CGIView() :
		m_agView( _T("View") ),
		m_aX( _T("X") ),
		m_aY( _T("Y") ),
		m_aWidth( _T("view-Width") ),
		m_aHeight( _T("view-Height") ),
		m_aOrigin( _T("view-Origin") ),
		m_aScale( _T("view-Scale") ),
		m_aAspectRatio( _T("view-Aspect-Ratio") ),
		m_agDoc( _T("Document") ),
		m_aDocWidth( _T("doc-Width") ),
		m_aDocHeight( _T("doc-Height") ),
		m_aDocCenter( _T("doc-Center") ),
		m_aViewBox( _T("ViewBox") )
{
	m_cszName = CGIView::ELEMENT_TAGNAME;
	m_pgInstanceType = &GetClassType();

	m_aScale = 1.f;
	m_aAspectRatio = 1.f;

	m_c = Color::White;
	m_aDocCenter = TRUE;
	m_aViewBox.m_aEnable = FALSE;

	m_fOffsetToCenterX = 0.f;
	m_fOffsetToCenterY = 0.f;
}

CGIView::~CGIView()
{
	CDumpContext dc;
	dc.SetDepth( 200 );
	m_mapAttr.m_mapNameToNode.Dump( dc );
	m_mapAttr.m_mapNameToGroup.Dump( dc );
}

void CGIView::InitializeAttributes()
{
	CGIGroup::InitializeAttributes();

	AddAttributeGroup( m_agDoc );
	AddGroupedAttributes( NULL, m_agDoc, FALSE, 
						  &m_aDocWidth, &m_aDocHeight, 
						  &m_aDocCenter, NULL );

	AddAttributeGroup( m_agView );
	AddGroupedAttributes( NULL, m_agView, FALSE, 
						  &m_aX, &m_aY,
						  &m_aWidth, &m_aHeight,
						  &m_aScale, &m_aAspectRatio, 
						  &m_aOrigin, NULL );

	AddAttributeGroup( m_aViewBox );
	SetAttrType( CGIAttr::DISPLAY_ATTR_TYPE | CGIAttr::DRAW_BBOX_ATTR_TYPE | CGIAttr::CTM_ATTR_TYPE, 
							(CGIAttr*)m_aOrigin,
							(CGIAttr*)m_aAspectRatio,
							(CGIAttr*)m_aScale,
							(CGIAttr*)m_aDocCenter,
							(CGIAttr*)m_aWidth,		
							(CGIAttr*)m_aHeight,
							(CGIAttr*)m_aDocWidth,
							(CGIAttr*)m_aDocHeight,
							NULL );
}

BOOL CGIView::GetRect( GRectF& rBBox ) const
{
	rBBox.left = 0;
	rBBox.top = 0;
	rBBox.right = m_aDocWidth;
	rBBox.bottom = m_aDocHeight;

	return FALSE == IsRectEmpty( rBBox );
}

void CGIView::GetClipRect( RectF& rrcf ) const 
{
	rrcf.X = m_fOffsetToCenterX;
	rrcf.Y = m_fOffsetToCenterY;
	rrcf.Width = m_aWidth;
	rrcf.Height = m_aHeight;
}

void CGIView::Draw( Graphics& rGdip )
{
	CGSaveTransform st( rGdip );
	
	Matrix mtx;
	GetCTM( mtx );
	rGdip.MultiplyTransform( &mtx );
	
	DrawBkGnd( rGdip );
	CGIGroup::Draw( rGdip );
}

void CGIView::DrawBkGnd( Graphics& rGdip )
{
	CGSaveTransform st( rGdip );

	Matrix mtx;
	m_aViewBox.GetCTM( mtx );
	mtx.Invert();
	rGdip.MultiplyTransform( &mtx );

	SolidBrush gbrush( m_c );
	//SolidBrush gbrush( Color( 120, 25, 25, 25 ) );
	rGdip.FillRectangle( &gbrush, 0.f, 0.f, m_aDocWidth, m_aDocHeight );
}

void CGIView::DrawOverlay( Graphics& rGdip )
{
#ifdef _DEBUG
	Pen pen( Color::Red );
	//Pen pen( Color::Red );
	rGdip.DrawRectangle( &pen, 0.f, 0.f, m_aViewBox.m_aWidth, m_aViewBox.m_aHeight );
//	rGdip.DrawLine( &pen, 0.f, 0.f, m_aViewBox.m_aWidth, m_aViewBox.m_aHeight - 200 );
//	rGdip.DrawLine( &pen, 0.f, m_aViewBox.m_aHeight, m_aViewBox.m_aWidth, 0.f );

	rGdip.DrawLine( &pen, 0.f, 0.f, m_aViewBox.m_aWidth, m_aViewBox.m_aHeight );
	rGdip.DrawLine( &pen, 0.f, m_aViewBox.m_aHeight, m_aViewBox.m_aWidth, 0.f );

	if( 0 )
	{
		SolidBrush gbrush( Color( 200, 25, 25, 25 ) );
		rGdip.FillRectangle( &gbrush, 0.f, 0.f, m_aDocWidth, m_aDocHeight );
	}
#endif //_DEBUG
}

void CGIView::UpdateCTM( Matrix& rMtx )
{
	m_aViewBox.Update();
	GetCTM( rMtx, MTX_RENDER );
	GetCTM( rMtx, MTX_VIEWBOX );
}

void CGIView::GetRenderCTM( Matrix& rmtx ) {
	GetCTM( rmtx, MTX_RENDER ); }

BOOL CGIView::GetCTM( Matrix& rMtx ) const 
{
	GetCTM( rMtx, MTX_RENDER );
	GetCTM( rMtx, MTX_VIEWBOX );
	return FALSE == rMtx.IsIdentity();
}

BOOL CGIView::GetCTM( Matrix& rMtx, INT nType ) const
{
	CGIView* pThis = (CGIView*)this;
	switch( nType )
	{
	case MTX_RENDER:
		{
			FLOAT fCx = m_aWidth;
			FLOAT fCy = m_aHeight;
			
			// Update View Transformation
			pThis->m_fOffsetToCenterX = 0.f;
			pThis->m_fOffsetToCenterY = 0.f;
			
			// Apply View-transformation
			FLOAT x, y;
			m_aOrigin.Get( x, y );
			x = -x;
			y = -y;
			FLOAT fRenderCx, fRenderCy;
			GetRenderSize( fRenderCx, fRenderCy );
			
			BOOL bCenter = m_aDocCenter;
			if( bCenter )
			{
				if( fRenderCx < fCx )
				{
					x = (fCx - fRenderCx) / 2.f;
					pThis->m_fOffsetToCenterX = x;
				}
				
				if( fRenderCy < fCy )
				{
					y = (fCy - fRenderCy) / 2.f;
					pThis->m_fOffsetToCenterY = y;
				}
			}
			
			rMtx.Translate( x, y );
			
			GetScale( x, y );
			rMtx.Scale( x, y );
		}
		break;

	case MTX_VIEWBOX:
		if( m_aViewBox.m_aEnable )
		{
			pThis->m_aViewBox.SetViewSize( m_aDocWidth, m_aDocHeight );
			pThis->m_aViewBox.GetCTM( rMtx );
		}
		break;
	}
	
	return FALSE == rMtx.IsIdentity();
}

void CGIView::SetSize( FLOAT fWidth, FLOAT fHeight )
{
	if( fWidth < 0.f )
		fWidth = 0.f;

	if( fHeight < 0.f )
		fHeight = 0.f;

	m_aWidth = fWidth;
	m_aHeight = fHeight;
}

void CGIView::GetSize( FLOAT& rfWidth, FLOAT& rfHeight ) const
{
	rfWidth = m_aWidth;
	rfHeight = m_aHeight;
}

void CGIView::SetDocSize( FLOAT fWidth, FLOAT fHeight )
{
	m_aDocWidth = fWidth;
	m_aDocHeight = fHeight;
	m_aViewBox.SetViewSize( fWidth, fHeight );
}

void CGIView::GetDocSize( FLOAT& rfWidth, FLOAT& rfHeight ) const
{
	rfWidth = m_aDocWidth;
	rfHeight = m_aDocHeight;
}

void CGIView::GetScrollableSize( FLOAT& rfWidth, FLOAT& rfHeight ) const
{
	FLOAT fRenderCx, fRenderCy;
	GetRenderSize( fRenderCx, fRenderCy );

	rfWidth = fRenderCx - m_aWidth;
	rfHeight = fRenderCy - m_aHeight;
	if( rfWidth < 0 )
		rfWidth = 0;

	if( rfHeight < 0 )
		rfHeight = 0;
}

void CGIView::GetScrollable( BOOL& rbHorzBar, BOOL& rbVertBar )
{
	FLOAT fScrollableCx, fScrollableCy;
	GetScrollableSize( fScrollableCx, fScrollableCy );

	rbHorzBar = fScrollableCx > 0;
	rbVertBar = fScrollableCy > 0;
}

BOOL CGIView::IsScrollable( INT nSBar )
{
	FLOAT fRenderCx, fRenderCy;
	GetRenderSize( fRenderCx, fRenderCy );
	if( SB_HORZ == nSBar )
		return m_aWidth < fRenderCx;

	if( SB_VERT == nSBar )
		return m_aHeight < fRenderCy;

	return FALSE;
}

void CGIView::Scroll( FLOAT fx, FLOAT fy, BOOL bScaled /*= TRUE*/ )
{
	if( FALSE == bScaled )
	{
		fx *= m_aScale;
		fy *= m_aScale * m_aAspectRatio;
	}

	FLOAT xOrig, yOrig;
	m_aOrigin.Get( xOrig, yOrig ); 

	FLOAT x = xOrig + fx;
	FLOAT y = yOrig + fy;
	if( x != xOrig || y != yOrig )
	SetOrigin( x, y );
}

void CGIView::SetOrigin( FLOAT x, FLOAT y, BOOL bScaled /*= TRUE*/ ) 
{
	if( FALSE == bScaled )
	{
		x *= m_aScale;
		y *= m_aScale * m_aAspectRatio;
	}

	FLOAT xOrig, yOrig;
	m_aOrigin.Get( xOrig, yOrig ); 

	FLOAT fScrollableCx, fScrollableCy;
	GetScrollableSize( fScrollableCx, fScrollableCy );
	if( fScrollableCx <= 0 )
		x = 0;
	else if( x < 0 )
		x = 0;
	else if( x > fScrollableCx )
		x = fScrollableCx;
	
	if( fScrollableCy <= 0 )
		y = 0;
	else if( y < 0 )
		y = 0;
	else if( y > fScrollableCy )
		y = fScrollableCy;
	
	if( x != xOrig || y != yOrig )
	{
		CGScrollEvent* pScrollEvent = CreateScrollEvent();
		ASSERT( pScrollEvent );
		m_aOrigin.Set( x, y ); 
		DispatchScrollEvent( *pScrollEvent );
	}
}

void CGIView::GetOrigin( FLOAT& rx, FLOAT& ry, BOOL bScaled /*= TRUE*/ ) const 
{
	m_aOrigin.Get( rx, ry ); 
	if( FALSE == bScaled )
	{
		rx /= m_aScale;
		ry /= m_aScale * m_aAspectRatio;
	}
}

const GPointF& CGIView::GetOrigin() const {
	return m_aOrigin; }

void CGIView::GetRenderSize( FLOAT& rfWidth, FLOAT& rfHeight ) const
{
	FLOAT fScale = m_aScale;
	rfWidth  = m_aDocWidth * fScale;
	rfHeight = m_aDocHeight * fScale * m_aAspectRatio;
}

FLOAT CGIView::GetScale() const {
	return m_aScale; }

FLOAT CGIView::GetScaleX() const {
	return m_aScale; }

FLOAT CGIView::GetScaleY() const {
	return m_aScale * m_aAspectRatio; }

void CGIView::GetScale( FLOAT& rfX, FLOAT& rfY ) const
{
	rfX = m_aScale;
	rfY = m_aScale * m_aAspectRatio;
}

void CGIView::GetScale( CGPointF& rgptf ) const 
{
	rgptf.x = m_aScale;
	rgptf.y = m_aScale * m_aAspectRatio;
}

void CGIView::SetScale( FLOAT fScale )  {
	m_aScale = fScale; }

void CGIView::SetScale( FLOAT fScaleX, FLOAT fScaleY )
{
	m_aScale = fScaleX;
	m_aAspectRatio = fScaleY / fScaleX;
}

void CGIView::SetAspectRatio( FLOAT fRatio ) {
	m_aAspectRatio = fRatio; }

CGZoomEvent* CGIView::CreateZoomEvent()
{
	CGZoomEvent* pPendingEvent = (CGZoomEvent*)GetPendingEvent( CGZoomEvent::EVENT );
	if( pPendingEvent )
		return pPendingEvent;

	CGZoomEventPriv* pEvent = new CGZoomEventPriv( (CGIView*)this );
	ASSERT( pEvent );
	if( NULL == pEvent )
		return NULL;

	pEvent->SetPreviousAspectRatio( GetAspectRatio() );
	pEvent->SetPreviousScale( GetScale() );
	pEvent->SetPreviousTranslate( GetOrigin() );

	return pEvent;
}

void CGIView::DispatchZoomEvent( CGZoomEvent& rEvent )
{
	if( rEvent.GetType() != CGZoomEvent::EVENT )
		return;

	CGZoomEventPriv* pEvent = (CGZoomEventPriv*)GetPendingEvent( rEvent.GetType() );;
	if( pEvent && pEvent != &rEvent )
	{
		ASSERT( FALSE ); // Logic not verified
		rEvent.Release();
	}
	
	if( NULL == pEvent )
		pEvent = (CGZoomEventPriv*)&rEvent;

	// Initialize Zoom-Event value after Zoom
	pEvent->SetAspectRatio( GetAspectRatio() );
	pEvent->SetScale( GetScale() );
	pEvent->SetTranslate( GetOrigin() );
	DispatchEvent( *pEvent );
}

CGScrollEvent* CGIView::CreateScrollEvent()
{
	CGScrollEvent* pPendingEvent = (CGScrollEvent*)GetPendingEvent( CGScrollEvent::EVENT );
	if( pPendingEvent )
		return pPendingEvent;

	CGScrollEventPriv* pEvent = new CGScrollEventPriv( (CGIView*)this );
	ASSERT( pEvent );
	if( NULL == pEvent )
		return NULL;

	pEvent->SetPreviousAspectRatio( GetAspectRatio() );
	pEvent->SetPreviousScale( GetScale() );
	pEvent->SetPreviousTranslate( GetOrigin() );

	return pEvent;
}

void CGIView::DispatchScrollEvent( CGScrollEvent& rEvent )
{
	if( rEvent.GetType() != CGScrollEvent::EVENT )
		return;

	CGScrollEventPriv* pEvent = (CGScrollEventPriv*)GetPendingEvent( rEvent.GetType() );;
	if( pEvent && pEvent != &rEvent )
		rEvent.Release();
	
	if( NULL == pEvent )
		pEvent = (CGScrollEventPriv*)&rEvent;

	// Initialize Zoom-Event value after Zoom
	pEvent->SetAspectRatio( GetAspectRatio() );
	pEvent->SetScale( GetScale() );
	pEvent->SetTranslate( GetOrigin() );
	DispatchEvent( *pEvent );
}

BOOL CGIView::IsDisplayAttribute( const CGIAttr& rAttr ) const {
	return rAttr.IsAttrTypeSet( CGIAttr::DISPLAY_ATTR_TYPE ); }

void CGIView::AttributeChanged( const CGIAttr& rAttr )
{
	if( IsDisplayAttribute( rAttr ) )
	{
		CGZoomEvent* pEvent = CreateZoomEvent();
		ASSERT( pEvent );

		if( -1 == IsEventLocked( CGMutationEvent::DOMAttrModified ) )
			Update();
		
		DispatchZoomEvent( *pEvent );
	}

	CGIGroup::AttributeChanged( rAttr );
}

void CGIView::Zoom( const CPoint& rpt, FLOAT fScale, BOOL bZoomToWindowCenter /*= FALSE*/ )
{
	LockMultipleEvent( CGScrollEvent::EVENT, CGZoomEvent::EVENT, CGMutationEvent::DOMAttrModified, NULL );

	// Transform point to world coordinate unit
	PointF ptfViewWnd( (float)rpt.x, (float)rpt.y );
	PointF ptfDistViewWnd = ptfViewWnd;
	if( bZoomToWindowCenter )
	{
		FLOAT fCx, fCy;
		GetSize( fCx, fCy );
		ptfDistViewWnd.X = fCx / 2;
		ptfDistViewWnd.Y = fCy / 2;
	}

	Matrix mtxW2V;
	GetRenderCTM( mtxW2V );
	mtxW2V.Invert();

	PointF ptfView = ptfViewWnd;
	mtxW2V.TransformPoints( &ptfView );

	// Update the matrix with new scale factor
	SetScale( fScale );
	SetOrigin( 0.f, 0.f );
	Update();

	Matrix mtxNewW2V;
	GetRenderCTM( mtxNewW2V );
	mtxNewW2V.Invert();

	PointF ptfDistView = ptfDistViewWnd;
	mtxNewW2V.TransformVectors( &ptfDistView );
	PointF ptfNewViewTopLeft = ptfView - ptfDistView;

	PointF ptfNewViewWndTopLeft = ptfNewViewTopLeft;
	Matrix mtxV2W;
	GetRenderCTM( mtxV2W );
	mtxV2W.TransformPoints( &ptfNewViewWndTopLeft );

	BOOL bHorzSBar, bVertSBar;
	GetScrollable( bHorzSBar, bVertSBar );

	CPoint ptMouseMove( 0, 0 );
	if( FALSE == bHorzSBar )
		ptfNewViewWndTopLeft.X = 0;

	if( FALSE == bVertSBar )
		ptfNewViewWndTopLeft.Y = 0;

	if( ptfNewViewWndTopLeft.X < 0 )
	{
		ptfNewViewWndTopLeft.X = 0;
		ptMouseMove.y += -(INT)ptfNewViewWndTopLeft.X;
	}

	if( ptfNewViewWndTopLeft.Y < 0 )
	{
		ptfNewViewWndTopLeft.Y = 0;
		ptMouseMove.y += -(INT)ptfNewViewWndTopLeft.Y;
	}

	if( 0.f != ptfView.X || 0.f != ptfView.Y )
		Scroll( ptfNewViewWndTopLeft.X, ptfNewViewWndTopLeft.Y );

	if( 0 /*&& m_bKeepViewPoint*/ )
	{
		PointF ptReCalcViewWnd = ptfView;
		mtxV2W.TransformPoints( &ptReCalcViewWnd );
		if( ptfViewWnd.X != ptReCalcViewWnd.X && ptfViewWnd.Y != ptReCalcViewWnd.Y )
		{
			ptMouseMove.x = (INT)(ptReCalcViewWnd.X - ptfViewWnd.X);
			ptMouseMove.y = (INT)(ptReCalcViewWnd.Y - ptfViewWnd.Y);
		}

		if( ptMouseMove.x || ptMouseMove.y )
		{
			HDC hDC = GetDC( NULL );
			INT nScreenCx = GetDeviceCaps( hDC, HORZRES );
			INT nScreenCy = GetDeviceCaps( hDC, VERTRES );

			ptMouseMove.x *= 65536 / nScreenCx;
			ptMouseMove.y *= 65536 / nScreenCy;
			mouse_event( MOUSEEVENTF_MOVE, ptMouseMove.x, ptMouseMove.y, 0, NULL );

			ReleaseDC( NULL, hDC );
		}
	}

	// Initialize Zoom-Event value after Zoom
	CGZoomEvent* pZoomEvent = CreateZoomEvent();
	ASSERT( pZoomEvent );
	DispatchZoomEvent( *pZoomEvent );

	UnlockMultipleEvent( CGMutationEvent::DOMAttrModified, CGScrollEvent::EVENT, CGZoomEvent::EVENT, NULL );
}
