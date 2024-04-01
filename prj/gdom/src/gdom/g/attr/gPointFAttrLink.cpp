#include "stdafx.h"
#include <g\attr\gPointFAttrLink.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CGPointF gs_gptf;
static const CGPointF& _GetDefault()
{
	gs_gptf.x = 0;
	gs_gptf.y = 0;
	return gs_gptf;
}

CGSAPointFLink::CGSAPointFLink( LPCTSTR pctszName )
{
	VERIFY( m_pAttr = new CGSAPointF( pctszName ) );
	ConstructAttribute();
}

BOOL CGSAPointFLink::operator=( const CString& rcszValue )
{
	if( NULL == m_pAttr )
		return FALSE;
	
	ASSERT( m_pAttr->IsDerivedFrom( CGSAPointF::GetClassType() ) );
	return ((CGSAPointF*)m_pAttr)->Set( rcszValue );
}

CGSAPointFLink::operator const GPointF&() const 
{
	if( NULL == m_pAttr )
		_GetDefault();
	
	ASSERT( m_pAttr->IsDerivedFrom( CGSAPointF::GetClassType() ) );
	return ((CGSAPointF*)m_pAttr)->Get();
}

BOOL CGSAPointFLink::operator=( const GPointF& rgptfValue )
{
	if( NULL == m_pAttr )
		return FALSE;
	
	ASSERT( m_pAttr->IsDerivedFrom( CGSAPointF::GetClassType() ) );
	return ((CGSAPointF*)m_pAttr)->Set( rgptfValue );
}


void CGSAPointFLink::Get( FLOAT& rfX, FLOAT& rfY ) const
{
	if( NULL == m_pAttr )
		return;

	ASSERT( m_pAttr->IsDerivedFrom( CGSAPointF::GetClassType() ) );
	((CGSAPointF*)m_pAttr)->Get( rfX, rfY );
}

BOOL CGSAPointFLink::Set( FLOAT fX, FLOAT fY )
{
	if( NULL == m_pAttr )
		return FALSE;
	
	ASSERT( m_pAttr->IsDerivedFrom( CGSAPointF::GetClassType() ) );
	return ((CGSAPointF*)m_pAttr)->Set( fX, fY );
}
