#include "stdafx.h"
#include <bld\gEditView.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPL_GTPYECLASS_DYNCREATE( CGIEditView, CGIView, _T("bview") )
CGIEditView::CGIEditView() :
	m_aWrkSpaceTop( _T("WorkSpaceTop") ),
	m_aWrkSpaceLeft( _T("WorkSpaceLeft") ),
	m_aWrkSpaceRight( _T("WorkSpaceRight") ),
	m_aWrkSpaceBottom( _T("WorkSpaceBottom") ),
	m_aDocRotate( _T("doc-Rotate") ),
	m_aDocSkewX( _T("doc-skewX") ),
	m_aDocSkewY( _T("doc-skewY") ),
	m_aDocScale( _T("doc-Scale") ),
	m_aDocAspectRatio( _T("doc-ApsectRatio") )
{
	m_pgInstanceType = &GetClassType();

	m_aDocScale = 1.f;
	m_aDocAspectRatio = 1.f;
}

CGIEditView::~CGIEditView()
{
	CDumpContext dc;
	dc.SetDepth( 200 );
	m_mapAttr.m_mapNameToNode.Dump( dc );
	m_mapAttr.m_mapNameToGroup.Dump( dc );
}

void CGIEditView::InitializeAttributes()
{
	CGIView::InitializeAttributes();

	AddGroupedAttributes( NULL, m_agDoc, FALSE, 
						  &m_aDocRotate, &m_aDocSkewX, &m_aDocSkewY, 
						  &m_aDocScale, &m_aDocAspectRatio, NULL );

	AddGroupedAttributes( NULL, m_agView, FALSE, 
						  &m_aWrkSpaceLeft, &m_aWrkSpaceTop, 
						  &m_aWrkSpaceRight, &m_aWrkSpaceBottom, NULL );

	SetAttrType( CGIAttr::DISPLAY_ATTR_TYPE | CGIAttr::DRAW_BBOX_ATTR_TYPE | CGIAttr::CTM_ATTR_TYPE, 
							(CGIAttr*)m_aWrkSpaceTop,	
							(CGIAttr*)m_aWrkSpaceLeft,	
							(CGIAttr*)m_aWrkSpaceRight,	
							(CGIAttr*)m_aWrkSpaceBottom,	
							(CGIAttr*)m_aDocRotate,	
							(CGIAttr*)m_aDocSkewX,	
							(CGIAttr*)m_aDocSkewY,
							(CGIAttr*)m_aDocSkewX,	
							(CGIAttr*)m_aDocScale,
							(CGIAttr*)m_aDocAspectRatio,
							NULL );
}

void CGIEditView::GetClipRect( RectF& rrcf ) const 
{
	rrcf.X = m_fOffsetToCenterX;
	rrcf.Y = m_fOffsetToCenterY;

	FLOAT fRenderCx, fRenderCy;
	GetRenderSize( fRenderCx, fRenderCy );

	rrcf.Width  = fRenderCx;
	rrcf.Height = fRenderCy;
}

BOOL CGIEditView::GetDrawBBox( GRectF& rBBox, Matrix* pmtx /*= NULL*/ ) const
{
	CGRectF& _rBBox = *((CGRectF*)&rBBox);
	_rBBox.left = 0;
	_rBBox.top = 0;
	_rBBox.right = m_aWidth;
	_rBBox.bottom = m_aHeight;

	return FALSE == _rBBox.IsRectEmpty();
}

void CGIEditView::Draw( Graphics& rGdip )
{
	CGSaveTransform st( rGdip );
	
	Matrix mtx;
	GetCTM( mtx );
	rGdip.MultiplyTransform( &mtx );
	
	DrawBkGnd( rGdip );
	CGIGroup::Draw( rGdip );
}

void CGIEditView::DrawBkGnd( Graphics& rGdip )
{
	CGSaveTransform st( rGdip );
	
	Matrix mtx;
	m_aViewBox.GetCTM( mtx );
	mtx.Invert();
	rGdip.MultiplyTransform( &mtx );

	if( 0 )
	{
		FLOAT x, y;
		GetScale( x, y );

		FLOAT fRenderCx, fRenderCy;
		GetRenderSize( fRenderCx, fRenderCy, NULL, FALSE );

		HatchBrush gbrush( HatchStyleLargeCheckerBoard, Color( 120, 125, 25, 25 ), Color( 10, 125, 25, 25 ) );
		rGdip.FillRectangle( &gbrush, -m_aWrkSpaceLeft, -m_aWrkSpaceTop,
							 fRenderCx * x + m_aWrkSpaceRight  + m_aWrkSpaceLeft, 
							 fRenderCy * y + m_aWrkSpaceBottom + m_aWrkSpaceTop );
	}
	
	SolidBrush gbrush( m_c );
	//SolidBrush gbrush( Color( 120, 25, 25, 25 ) );
	rGdip.FillRectangle( &gbrush, 0.f, 0.f, m_aDocWidth, m_aDocHeight );
}

void CGIEditView::DrawOverlay( Graphics& rGdip )
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

void CGIEditView::UpdateCTM( Matrix& rMtx )
{
	m_aViewBox.Update();
	GetCTM( rMtx, MTX_RENDER_TO_DOCUMENT );
	GetCTM( rMtx, MTX_VIEWBOX );
}

void CGIEditView::GetRenderCTM( Matrix& rMtx ) {
	GetCTM( rMtx, MTX_RENDER ); }

BOOL CGIEditView::GetCTM( Matrix& rMtx ) const 
{
	GetCTM( rMtx, MTX_RENDER_TO_DOCUMENT );
	GetCTM( rMtx, MTX_VIEWBOX );
	return FALSE == rMtx.IsIdentity(); 
}

FLOAT fWL = 60;
BOOL CGIEditView::GetCTM( Matrix& rMtx, INT nType ) const
{
	CGIEditView* pThis = (CGIEditView*)this;
	switch( nType )
	{
	case MTX_RENDER:
	case MTX_DOCUMENT:
	case MTX_RENDER_TO_DOCUMENT:
		{
			Matrix mtxRender;
			FLOAT fRenderCx, fRenderCy;
			GetRenderSize( fRenderCx, fRenderCy, &mtxRender );
			if( MTX_DOCUMENT == nType )
			{
				rMtx.Multiply( &mtxRender );
				break;
			}

			FLOAT x, y;
			m_aOrigin.Get( x, y );
			x = -x;
			y = -y;

			pThis->m_fOffsetToCenterX = 0.f;
			pThis->m_fOffsetToCenterY = 0.f;

			FLOAT fCx = m_aWidth;
			FLOAT fCy = m_aHeight;

			if( m_aDocCenter )
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

			x += m_aWrkSpaceLeft;
			y += m_aWrkSpaceTop;
			rMtx.Translate( x, y );

			GetScale( x, y );
			rMtx.Scale( x, y );

			if( MTX_RENDER_TO_DOCUMENT == nType )
				rMtx.Multiply( &mtxRender );
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

void CGIEditView::GetRenderSize( FLOAT& rfWidth, FLOAT& rfHeight, Matrix* pmtx, BOOL bScaled /*= TRUE*/ ) const
{
	Matrix mtx;

	FLOAT fAngle = m_aDocRotate;
	if( fAngle )
		mtx.Rotate( fAngle );

	FLOAT fSkewX = m_aDocSkewX;
	FLOAT fSkewY = m_aDocSkewY;
	if( fSkewX || fSkewY )
	{
		FLOAT fTanX = (FLOAT)tan( fSkewX * 22.f / (7.f * 180.f) );
		FLOAT fTanY = (FLOAT)tan( fSkewY * 22.f / (7.f * 180.f) );
		mtx.Shear( fTanX, fTanY );
	}

	FLOAT x, y;
	GetDocumentScale( x, y );
	mtx.Scale( x, y );

	FLOAT fDocCx = m_aDocWidth;
	FLOAT fDocCy = m_aDocHeight;
	RectF rctfDoc( 0, 0, fDocCx, fDocCy ); 

	GraphicsPath gpath;
	gpath.AddRectangle( rctfDoc );

	RectF rctfDocBnd;
	gpath.GetBounds( &rctfDocBnd, &mtx, NULL );
	//mtx.Translate( -rctfDocBnd.X, -rctfDocBnd.Y );

	if( bScaled )
	{
		GetScale( x, y );
		if( x != 1 || y != 1 )
		{
			rctfDocBnd.Width *= x;
			rctfDocBnd.Height *= y;
		}

		rfWidth = m_aWrkSpaceLeft + m_aWrkSpaceRight;
		rfHeight = m_aWrkSpaceTop  + m_aWrkSpaceBottom;
	}
	else
	{
		rfWidth = 0;
		rfHeight = 0;
	}

	rfWidth += rctfDocBnd.Width;
	rfHeight += rctfDocBnd.Height;
	if( pmtx )
	{
		pmtx->Translate( -rctfDocBnd.X, -rctfDocBnd.Y );
		pmtx->Multiply( &mtx );
	}
}

void CGIEditView::GetRenderSize( FLOAT& rfWidth, FLOAT& rfHeight ) const {
	GetRenderSize( rfWidth, rfHeight, NULL ); }

FLOAT CGIEditView::GetDocumentScale() const {
	return m_aDocScale; }

FLOAT CGIEditView::GetDocumentScaleX() const {
	return m_aDocScale; }

FLOAT CGIEditView::GetDocumentScaleY() const {
	return m_aDocScale * m_aDocAspectRatio; }

void CGIEditView::GetDocumentScale( FLOAT& rfX, FLOAT& rfY ) const
{
	rfX = m_aDocScale;
	rfY = m_aDocScale * m_aDocAspectRatio;
}

void CGIEditView::GetDocumentScale( CGPointF& rgptf ) const 
{
	rgptf.x = m_aDocScale;
	rgptf.y = m_aDocScale * m_aDocAspectRatio;
}

void CGIEditView::SetDocumentScale( FLOAT fScale ) {
	m_aDocScale = fScale; }

void CGIEditView::SetDocumentScale( FLOAT fScaleX, FLOAT fScaleY )
{
	m_aDocScale = fScaleX;
	m_aDocAspectRatio = fScaleY / fScaleX;
}

void CGIEditView::SetDocumentAspectRatio( FLOAT fRatio ) {
	m_aDocAspectRatio = fRatio; }

