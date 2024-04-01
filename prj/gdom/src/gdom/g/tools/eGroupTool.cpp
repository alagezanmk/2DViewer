#include "stdafx.h"
#include <g\tools\eGroupTool.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGIGroupElementTool::CGIGroupElementTool()
{}

CGIGroupElementTool::~CGIGroupElementTool()
{}

BOOL CGIGroupElementTool::Draw( CDC& rDC, RECT& rRect )
{
	INT nCount = m_arpTool.GetSize();
	if( nCount > 1 )
	//if( nCount )
	{
		const GRectF& rgrctf = GetBBox();

		PointF arptf[4];
		// TopLeft
		arptf[0].X = rgrctf.left;
		arptf[0].Y = rgrctf.top;

		// TopRight
		arptf[1].X = rgrctf.right;
		arptf[1].Y = arptf[0].Y;

		// BottomRight
		arptf[2].X = arptf[1].X;
		arptf[2].Y = rgrctf.bottom;

		// BottomLeft
		arptf[3].X = arptf[0].X;
		arptf[3].Y = arptf[2].Y;

		GraphicsPath gpath;
		gpath.AddLines( arptf, 4 );
		gpath.CloseFigure();

		Pen gpen( Color::Red, 2 );
		Graphics gdip( rDC.m_hDC );
		gdip.DrawPath( &gpen, &gpath );
	}

	return FALSE;
}

INT CGIGroupElementTool::GetDrawType() const {
	return UPPER_DRAW_TYPE; }

CGIElementUITool* CGIGroupElementTool::GetElementTool( CGIElement& rElement ) 
{
	INT nCount = m_arpTool.GetSize();
	CGIElementUITool** ppElementTool = (CGIElementUITool**)m_arpTool.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppElementTool[i]->m_piElement == &rElement )
			return ppElementTool[i];
	}

	return NULL; 
}

BOOL CGIGroupElementTool::AddTool( CGIElementUITool& rTool )
{
	INT nCount = m_arpTool.GetSize();
	CGIElementUITool** ppElementTool = (CGIElementUITool**)m_arpTool.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppElementTool[i] == &rTool )
		{
			ASSERT( FALSE );
			return FALSE;
		}
	}

	InvalidateRect();
	m_arpTool.Add( &rTool );
	rTool.AddRef();
	InvalidateRect();
	return TRUE;
}

BOOL CGIGroupElementTool::RemoveTool( CGIElementUITool& rTool )
{
	INT nCount = m_arpTool.GetSize();
	CGIElementUITool** ppElementTool = (CGIElementUITool**)m_arpTool.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppElementTool[i] == &rTool )
		{
			InvalidateRect();
			ppElementTool[i]->Release();
			m_arpTool.RemoveAt( i );
			InvalidateRect();
			return TRUE;
		}
	}

	return FALSE;
}

void CGIGroupElementTool::GetBBox( GRectF& rrctf ) const 
{
	m_grctfDrawBBox.SetRectEmpty();

	Matrix mtx;
	if( m_pView )
		m_pView->GetCTM( mtx );

	GRectF rctfBBox;
	INT nCount = m_arpTool.GetSize();
	CGIElementUITool** ppElementTool = (CGIElementUITool**)m_arpTool.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		ppElementTool[i]->m_piElement->GetDrawBBox( rctfBBox, &mtx );
		m_grctfDrawBBox.UnionRect( m_grctfDrawBBox, rctfBBox );
	}

	rrctf = m_grctfDrawBBox;
}

const GRectF& CGIGroupElementTool::GetBBox() const
{
	m_grctfDrawBBox.SetRectEmpty();

	Matrix mtx;
	if( m_pView )
		m_pView->GetCTM( mtx );

	/*RectF rctf;
	Matrix mtx;
	GraphicsPath gpath;

	CGRectF grctf;*/
	GRectF rctfBBox;
	INT nCount = m_arpTool.GetSize();
	CGIElementUITool** ppElementTool = (CGIElementUITool**)m_arpTool.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		ppElementTool[i]->m_piElement->GetDrawBBox( rctfBBox, &mtx );
		/*gpath.AddRectangle( RectF( rctfBBox.left, rctfBBox.top, rctfBBox.Width(), rctfBBox.Height() ) );
		ppElementTool[i]->m_piElement->GetScreenCTM( mtx );
		gpath.GetBounds( &rctf, &mtx, NULL );
		mtx.Reset();
		gpath.Reset();

		grctf.SetRect( rctf.X, rctf.Y, rctf.X + rctf.Width, rctf.Y + rctf.Height );*/
		m_grctfDrawBBox.UnionRect( m_grctfDrawBBox, rctfBBox );
	}

	return m_grctfDrawBBox;
}

UINT CGIGroupElementTool::HitTest( const CPoint& rpoint )
{
	PointF ptf( (FLOAT)rpoint.x, (FLOAT)rpoint.y );
	const CGRectF& rrctf = GetBBox();
	RectF rctf( rrctf.left, rrctf.top, rrctf.Width(), rrctf.Height() );
	if( rctf.Contains( ptf ) )
		return HT_ELEMENT;

	return HT_NOTHING;
}

void CGIGroupElementTool::InvalidateRect( BOOL bHandle /*= FALSE*/ ) const
{
	INT nCount = m_arpTool.GetSize();
	if( 0 == nCount )
		return;
	
	const CGRectF& rgrctf = GetBBox();
	//GraphicsPath gpath;
	//gpath.AddRectangle( &rgrctf );

	RectF rctf( rgrctf.left, rgrctf.top, rgrctf.Width(), rgrctf.Height() );
	//gpath.GetBounds( &rctf );
	CGIElementTool::InvalidateRect( &rctf );
}