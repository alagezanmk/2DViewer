#include "stdafx.h"
#include <g\type\idom\giGroup.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPL_GTPYECLASS_DYNCREATE( CGIGroup, CGIShapeElement, _T("group") )
CGIGroup::CGIGroup()
{
	m_pgInstanceType = &GetClassType();
}

CGIGroup::~CGIGroup()
{}