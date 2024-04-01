#include "stdafx.h"
#include <g\type\idom\giViewPort.h>
#include <g\type\gElementPriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString gs_cszCONTAINER_TAGNAME = _T("container");
LPCTSTR CGIViewPort::ELEMENT_TAGNAME = gs_cszCONTAINER_TAGNAME;

IMPL_GTPYECLASS_DYNCREATE( CGIViewPort, CGIGroup, CGIViewPort::ELEMENT_TAGNAME )
CGIViewPort::CGIViewPort()
	: m_aX( _T("x") ),
	  m_aY( _T("y") ),
	  m_aWidth( _T("width") ),
	  m_aHeight( _T("height") ),
	  m_aEnableClip( _T("enableClip") )
{
	m_pgInstanceType = &GetClassType();
	m_cszName = CGIViewPort::ELEMENT_TAGNAME;
	m_aEnableClip = FALSE;
	m_pViewPortElement = this;
}

CGIViewPort::~CGIViewPort()
{
	RemoveAttributes( &m_aX, &m_aY, &m_aWidth, &m_aHeight, &m_aEnableClip, NULL );
	m_pViewPortElement = NULL;
}

void CGIViewPort::InitializeAttributes()
{
	CGIGroup::InitializeAttributes();
	AddAttributes( &m_aX, &m_aY, &m_aWidth, &m_aHeight, &m_aEnableClip, NULL );


	SetAttrType( CGIAttr::DISPLAY_ATTR_TYPE | CGIAttr::DRAW_BBOX_ATTR_TYPE | CGIAttr::CTM_ATTR_TYPE, 
							(CGIAttr*)m_aX,
							(CGIAttr*)m_aY,
							(CGIAttr*)m_aWidth,
							(CGIAttr*)m_aHeight,
							(CGIAttr*)m_aEnableClip,
							NULL );

	SetAttrType( CGIAttr::CTM_ATTR_TYPE,
							(CGIAttr*)m_aX,
							(CGIAttr*)m_aY,
							NULL );
}

BOOL CGIViewPort::GetRect( GRectF& rBBox ) const
{
	rBBox.left = m_aX;
	rBBox.top = m_aY;
	rBBox.right = m_aX + m_aWidth;
	rBBox.bottom = m_aY + m_aHeight;

	return FALSE == IsRectEmpty( rBBox );
}

void CGIViewPort::GetClipRect( RectF& rrcf ) const
{
	rrcf.X = m_aX;
	rrcf.Y = m_aY;
	rrcf.Width = m_aWidth;
	rrcf.Height = m_aHeight;
}

void CGIViewPort::Draw( Graphics& rGdip )
{
	CGSaveTransform st( rGdip );

	Region rgn;
	if( m_aEnableClip )
	{
		rGdip.GetClip( &rgn );
		RectF rctf;
		GetClipRect( rctf );
		//rGdip.SetClip( rctf );
	}

	Matrix mtx;
	GetCTM( mtx );
	rGdip.MultiplyTransform( &mtx );

	DrawContainer( rGdip );

	if( m_aEnableClip )
		rGdip.SetClip( &rgn );
}

void CGIViewPort::DrawContainer( Graphics& rGdip ) {
	CGIGroup::Draw( rGdip ); }

void CGIViewPort::UpdateCTM( Matrix& rMtx )
{
	FLOAT x = m_aX;
	FLOAT y = m_aY;
	rMtx.Translate( x, y );
}

