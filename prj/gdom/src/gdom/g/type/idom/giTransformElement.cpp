#include "stdafx.h"
#include <g\type\idom\giTransformElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString gs_cszTRANSFORM_ELEMENT_TAGNAME = _T("transformelement");
LPCTSTR CGITransformElement::ELEMENT_TAGNAME = gs_cszTRANSFORM_ELEMENT_TAGNAME;
IMPL_GTPYECLASS_DYNCREATE( CGITransformElement, CGIElement, gs_cszTRANSFORM_ELEMENT_TAGNAME )
CGITransformElement::CGITransformElement() :
	m_aRotate( _T("rotate") )
{
	m_cszName = CGITransformElement::ELEMENT_TAGNAME;
	m_pgInstanceType = &GetClassType();

	m_aRotate = 45;
}

CGITransformElement::~CGITransformElement()
{}

void CGITransformElement::DrawElement( Graphics& rGdip )
{
	rGdip.RotateTransform( m_aRotate );
}

BOOL CGITransformElement::GetCTM( Matrix& rMtx ) const
{
	rMtx.Rotate( m_aRotate, MatrixOrderAppend );

	return FALSE;
}

void CGITransformElement::InitializeAttributes()
{
	CGIElement::InitializeAttributes();
	AddAttributeNode( m_aRotate );
}
