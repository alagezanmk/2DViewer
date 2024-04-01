#include "stdafx.h"
#include <g\type\idom\giShapeElement.h>
#include <g\type\idom\giTransformElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPL_GTPYECLASS_DYNCREATE( CGIShapeElement, CGIElement, _T("shapeelement") )
CGIShapeElement::CGIShapeElement()
{
	m_pgInstanceType = &GetClassType();
	m_grctfDrawBBox.SetRectEmpty();
}

CGIShapeElement::~CGIShapeElement()
{}

void CGIShapeElement::Update()
{
	if( FALSE == IsNodeFlagSet( DATA_CTM_MODIFIED_NODE_FLAG ) )
		return;

	m_mtx.Reset();
	UpdateCTM( m_mtx );
	SetNodeFlag( DATA_CTM_MODIFIED_NODE_FLAG, FALSE );
}

void CGIShapeElement::UpdateCTM( Matrix& rMtx )
{}

BOOL CGIShapeElement::GetDrawBBox( GRectF& rBBox, Matrix* pmtx /*= NULL*/ ) const
{
	CGRectF& _rBBox = *((CGRectF*)&rBBox);
	_rBBox.SetRectEmpty();

	CGRectF	grctf;
	if( GetRect( grctf ) )
	{
		PointF arptf[4];
		// TopLeft
		arptf[0].X = grctf.left;
		arptf[0].Y = grctf.top;

		// TopRight
		arptf[1].X = grctf.right;
		arptf[1].Y = grctf.top;

		// BottomRight
		arptf[2].X = arptf[1].X;
		arptf[2].Y = grctf.bottom;

		// BottomLeft
		arptf[3].X = arptf[0].X;
		arptf[3].Y = arptf[2].Y;

		Matrix mtx;
		GetScreenCTM( mtx );
		mtx.TransformPoints( arptf, 4 );
		if( pmtx )
			pmtx->TransformPoints( arptf, 4 );

		GraphicsPath gpath;
		gpath.AddLines( arptf, 4 );
		gpath.CloseFigure();

		RectF rctf;
		gpath.GetBounds( &rctf );
		_rBBox = rctf;
	}

	return FALSE == _rBBox.IsRectEmpty();
}

BOOL CGIShapeElement::GetCTM( Matrix& rMtx ) const
{
	rMtx.Multiply( &m_mtx, MatrixOrderAppend );
	return FALSE == rMtx.IsIdentity();
}
