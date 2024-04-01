#include "stdafx.h"
#include <bld\layer.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static CString gs_cszLAYER_ELEMENT_TAGNAME = _T("layer");
LPCTSTR CGILayer::ELEMENT_TAGNAME = gs_cszLAYER_ELEMENT_TAGNAME;

IMPL_GTPYECLASS_DYNCREATE( CGILayer, CGIViewPort, CGILayer::ELEMENT_TAGNAME )
CGILayer::CGILayer()
{
	m_cszName = CGILayer::ELEMENT_TAGNAME;
	m_pgInstanceType = &GetClassType();
}

CGILayer::~CGILayer()
{}
