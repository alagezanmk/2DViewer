#include "stdafx.h"
#include <bld\page.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static CString gs_cszPAGE_ELEMENT_TAGNAME = _T("page");
LPCTSTR CGIPage::ELEMENT_TAGNAME = gs_cszPAGE_ELEMENT_TAGNAME;

IMPL_GTPYECLASS_DYNCREATE( CGIPage, CGIView, CGIPage::ELEMENT_TAGNAME )
CGIPage::CGIPage()
{
	m_cszName = CGIPage::ELEMENT_TAGNAME;
	m_pgInstanceType = &GetClassType();
}

CGIPage::~CGIPage()
{}
