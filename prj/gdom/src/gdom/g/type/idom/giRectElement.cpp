#include "stdafx.h"
#include <g\type\idom\giRectElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString gs_cszRECT_ELEMENT_TAGNAME = _T("rect");
LPCTSTR CGIRectElement::ELEMENT_TAGNAME = gs_cszRECT_ELEMENT_TAGNAME;

IMPL_GTPYECLASS_DYNCREATE( CGIRectElement, CGIShapeElement, CGIRectElement::ELEMENT_TAGNAME )
CGIRectElement::CGIRectElement() :
	m_aX( _T("x") ),
	m_aY( _T("y") ),
	m_aWidth( _T("width") ),
	m_aHeight( _T("height") )
{
	m_cszName = CGIRectElement::ELEMENT_TAGNAME;
	m_pgInstanceType = &GetClassType();
}

CGIRectElement::~CGIRectElement() 
{}

void CGIRectElement::InitializeAttributes()
{
	CGIShapeElement::InitializeAttributes();
	AddAttributes( &m_aX, &m_aY, &m_aWidth, &m_aHeight, NULL );

	SetAttrType( CGIAttr::DISPLAY_ATTR_TYPE | CGIAttr::DRAW_BBOX_ATTR_TYPE, 
							(CGIAttr*)m_aX,
							(CGIAttr*)m_aY,
							(CGIAttr*)m_aWidth,
							(CGIAttr*)m_aHeight,
							NULL );

	SetAttrFlag( CGIAttr::INHERITABLE_ATTR_FLAG, TRUE,
				 (CGIAttr*)m_aX, (CGIAttr*)m_aY, 
				 (CGIAttr*)m_aWidth, (CGIAttr*)m_aHeight, NULL );
}

BOOL CGIRectElement::GetRect( GRectF& rBBox ) const
{
	rBBox.left = m_aX;
	rBBox.top = m_aY;
	rBBox.right = m_aX + m_aWidth;
	rBBox.bottom = m_aY + m_aHeight;

	return FALSE == IsRectEmpty( rBBox );
}

void CGIRectElement::DrawElement( Graphics& rGdip )
{
	SolidBrush gbrush( Color( 200, 30, 15, 244 ) );

	FLOAT x = m_aX;
	FLOAT y = m_aY;
	FLOAT w = m_aWidth;
	FLOAT h = m_aHeight;
	rGdip.FillRectangle( &gbrush, x, y, w, h );

	Pen pen( Color::Red );
	rGdip.DrawRectangle( &pen, x, y, w, h );
	rGdip.DrawEllipse( &pen, x, y, w, h );
	CGIShapeElement::DrawElement( rGdip );
}

UINT CGIRectElement::HitTest( const PointF& rptf )
{
	RectF rctf( m_aX, m_aY, m_aWidth, m_aHeight );
	if( rctf.Contains( rptf ) )
		return HT_ELEMENT;

	return HT_NOTHING;
}

UINT CGIRectElement::HitTest( const Region& rrgn )
{
	RectF rctf( m_aX, m_aY, m_aWidth, m_aHeight );
	Region rgn( rctf );
	rgn.Intersect( &rrgn );

	HWND hWnd = GetDesktopWindow();
	Graphics gdip( hWnd );
	if( FALSE == rgn.IsEmpty( &gdip ) )
		return HT_ELEMENT;

	return HT_NOTHING; 
}
