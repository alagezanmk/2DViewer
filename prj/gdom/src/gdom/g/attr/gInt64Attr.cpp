#include "stdafx.h"
#include <g\attr\gInt64Attr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSAInt64::CGSAInt64( LPCTSTR pctszName ) :
	CGIAttr( pctszName )
{
	m_n64 = 0;
}

void CGSAInt64::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue.Format( _T("%d"), (INT)m_n64 );
}

BOOL CGSAInt64::Validate( CString& rcszValue ) const
{
	INT64 en = (INT64)_tcstol( rcszValue, NULL, 10 );
	return Validate( en );
}

BOOL CGSAInt64::Update( CString& rcszValue )
{
	INT64 en = (INT64)_tcstol( rcszValue, NULL, 10 );
	return Update( en );
}

BOOL CGSAInt64::Set( INT64 n64Value ) 
{
	if( m_n64 == n64Value )
		return TRUE;

	if( FALSE == Validate( n64Value ) )
		return FALSE;

	if( FALSE == Update( n64Value ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSAInt64::Validate( INT64& n64Value ) const {
	return CGIAttr::Validate( &n64Value ); }

BOOL CGSAInt64::Update( INT64 n64Value )
{
	if( FALSE == CGIAttr::Update( &n64Value ) )
		return FALSE;

	m_n64 = n64Value;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSAUInt64::CGSAUInt64( LPCTSTR pctszName ) :
	CGIAttr( pctszName )
{
	m_un64 = 0;
}

void CGSAUInt64::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue.Format( _T("%d"), (INT)m_un64 );
}

BOOL CGSAUInt64::Validate( CString& rcszValue ) const
{
	UINT64 en = (UINT64)_tcstol( rcszValue, NULL, 10 );
	return Validate( en );
}

BOOL CGSAUInt64::Update( CString& rcszValue )
{
	UINT64 en = (UINT64)_tcstol( rcszValue, NULL, 10 );
	return Update( en );
}

BOOL CGSAUInt64::Set( UINT64 n64Value ) 
{
	if( m_un64 == n64Value )
		return TRUE;

	if( FALSE == Validate( n64Value ) )
		return FALSE;

	if( FALSE == Update( n64Value ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSAUInt64::Validate( UINT64& n64Value ) const {
	return CGIAttr::Validate( &n64Value ); }

BOOL CGSAUInt64::Update( UINT64 n64Value )
{
	if( FALSE == CGIAttr::Update( &n64Value ) )
		return FALSE;

	m_un64 = n64Value;
	return TRUE;
}
