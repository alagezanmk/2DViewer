#include "stdafx.h"
#include <g\attr\gFloatAttrLink.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGSAFloatLink::CGSAFloatLink( LPCTSTR pctszName )
{
	VERIFY( m_pAttr = new CGSAFloat( pctszName ) );
	ConstructAttribute();
}

BOOL CGSAFloatLink::operator=( const CString& rcszValue )
{
	if( NULL == m_pAttr )
		return FALSE;

	ASSERT( m_pAttr->IsDerivedFrom( CGSAFloat::GetClassType() ) );
	return ((CGSAFloat*)m_pAttr)->Set( rcszValue );
}

CGSAFloatLink::operator FLOAT() const 
{
	if( NULL == m_pAttr )
		return 0;

	ASSERT( m_pAttr->IsDerivedFrom( CGSAFloat::GetClassType() ) );
	return ((CGSAFloat*)m_pAttr)->Get();
}

BOOL CGSAFloatLink::operator=( FLOAT fValue )
{
	if( NULL == m_pAttr )
		return FALSE;

	ASSERT( m_pAttr->IsDerivedFrom( CGSAFloat::GetClassType() ) );
	return ((CGSAFloat*)m_pAttr)->Set( fValue );
}
