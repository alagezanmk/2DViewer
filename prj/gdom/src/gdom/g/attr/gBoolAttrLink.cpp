#include "stdafx.h"
#include <g\attr\gBoolAttrLink.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSABoolLink::CGSABoolLink( LPCTSTR pctszName )
{
	VERIFY( m_pAttr = new CGSABool( pctszName ) );
	ConstructAttribute();
}

BOOL CGSABoolLink::operator=( const CString& rcszValue )
{
	if( NULL == m_pAttr )
		return FALSE;

	ASSERT( m_pAttr->IsDerivedFrom( CGSABool::GetClassType() ) );
	return ((CGSABool*)m_pAttr)->Set( rcszValue );
}

CGSABoolLink::operator BOOL() const 
{
	if( NULL == m_pAttr )
		return FALSE;

	ASSERT( m_pAttr->IsDerivedFrom( CGSABool::GetClassType() ) );
	return ((CGSABool*)m_pAttr)->Get();
}

BOOL CGSABoolLink::operator=( BOOL bValue )
{
	if( NULL == m_pAttr )
		return FALSE;

	ASSERT( m_pAttr->IsDerivedFrom( CGSABool::GetClassType() ) );
	return ((CGSABool*)m_pAttr)->Set( bValue );
}
