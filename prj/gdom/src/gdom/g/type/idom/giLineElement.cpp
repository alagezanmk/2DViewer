#include "stdafx.h"
#include <g\type\idom\giLineElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString gs_cszLINE_ELEMENT_TAGNAME = _T("line");
LPCTSTR CGILineElement::ELEMENT_TAGNAME = gs_cszLINE_ELEMENT_TAGNAME;

IMPL_GTPYECLASS_DYNCREATE( CGILineElement, CGIShapeElement, CGILineElement::ELEMENT_TAGNAME )
CGILineElement::CGILineElement() :
	m_aX1( _T("x1") ),
	m_aY1( _T("y1") ),
	m_aX2( _T("x2") ),
	m_aY2( _T("y2") )
{
	m_cszName = CGILineElement::ELEMENT_TAGNAME;
	m_pgInstanceType = &GetClassType();
}

CGILineElement::~CGILineElement() 
{}

void CGILineElement::InitializeAttributes()
{
	CGIShapeElement::InitializeAttributes();
	AddAttributes( &m_aX1, &m_aY1, &m_aX2, &m_aY2, NULL );

	SetAttrType( CGIAttr::DISPLAY_ATTR_TYPE | CGIAttr::DRAW_BBOX_ATTR_TYPE, 
							(CGIAttr*)m_aX1,
							(CGIAttr*)m_aY1,
							(CGIAttr*)m_aX2,
							(CGIAttr*)m_aY2,
							NULL );
}

BOOL CGILineElement::GetRect( GRectF& rBBox ) const
{
	rBBox.left = m_aX1;
	rBBox.top = m_aY1;
	rBBox.right = m_aX2;
	rBBox.bottom = m_aY2;

	return FALSE == IsRectEmpty( rBBox );
}

void CGILineElement::DrawElement( Graphics& rGdip )
{
	Pen pen( Color::Red );
	rGdip.DrawLine( &pen, m_aX1, m_aY1, m_aX2, m_aY2 );
	CGIShapeElement::DrawElement( rGdip );
}

UINT CGILineElement::HitTest( const PointF& rptf )
{
	const INT cnPointCount = 2;
	PointF arptf[2];
	arptf[0].X = m_aX1;
	arptf[0].Y = m_aY1;
	arptf[1].X = m_aX2;
	arptf[1].Y = m_aY2;

	GraphicsPath gpath;
	gpath.AddLines( arptf, cnPointCount );

	Pen gpen( Color::Black, 6.f );
	gpath.Widen( &gpen );
	if( gpath.IsVisible( rptf ) )
		return HT_ELEMENT;

	return HT_NOTHING;
}

UINT CGILineElement::HitTest( const Region& rrgn )
{
	const INT cnPointCount = 2;
	PointF arptf[cnPointCount];
	arptf[0].X = m_aX1;
	arptf[0].Y = m_aY1;
	arptf[1].X = m_aX2;
	arptf[1].Y = m_aY2;

	GraphicsPath gpath;
	gpath.AddLines( arptf, cnPointCount );
	Pen gpen( Color::Black, 1.f );
	gpath.Widen( &gpen );

	Region rgn;
	rgn.Union( &rrgn );
	rgn.Intersect( &gpath );

	HWND hWnd = GetDesktopWindow();
	Graphics gdip( hWnd );
	if( FALSE == rgn.IsEmpty( &gdip ) )
		return HT_ELEMENT;

	return HT_NOTHING; 
}
