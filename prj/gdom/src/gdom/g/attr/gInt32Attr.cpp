#include "stdafx.h"
#include <g\attr\gInt32Attr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSAInt32::CGSAInt32( LPCTSTR pctszName ) :
	CGIAttr( pctszName )
{
	m_n32 = 0;
}

void CGSAInt32::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue.Format( _T("%d"), (INT)m_n32 );
}

BOOL CGSAInt32::Validate( CString& rcszValue ) const
{
	INT32 en = (INT32)_tcstol( rcszValue, NULL, 10 );
	return Validate( en );
}

BOOL CGSAInt32::Update( CString& rcszValue )
{
	INT32 en = (INT32)_tcstol( rcszValue, NULL, 10 );
	return Update( en );
}

BOOL CGSAInt32::Set( INT32 n32Value ) 
{
	if( m_n32 == n32Value )
		return TRUE;

	if( FALSE == Validate( n32Value ) )
		return FALSE;

	if( FALSE == Update( n32Value ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSAInt32::Validate( INT32& n32Value ) const {
	return CGIAttr::Validate( &n32Value ); }

BOOL CGSAInt32::Update( INT32 n32Value )
{
	if( FALSE == CGIAttr::Update( &n32Value ) )
		return FALSE;

	m_n32 = n32Value;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSAUInt32::CGSAUInt32( LPCTSTR pctszName ) :
	CGIAttr( pctszName )
{
	m_un32 = 0;
}

void CGSAUInt32::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue.Format( _T("%d"), (INT)m_un32 );
}

BOOL CGSAUInt32::Validate( CString& rcszValue ) const
{
	UINT32 en = (UINT32)_tcstol( rcszValue, NULL, 10 );
	return Validate( en );
}

BOOL CGSAUInt32::Update( CString& rcszValue )
{
	UINT32 en = (UINT32)_tcstol( rcszValue, NULL, 10 );
	return Update( en );
}

BOOL CGSAUInt32::Set( UINT32 n32Value ) 
{
	if( m_un32 == n32Value )
		return TRUE;

	if( FALSE == Validate( n32Value ) )
		return FALSE;

	if( FALSE == Update( n32Value ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSAUInt32::Validate( UINT32& n32Value ) const {
	return CGIAttr::Validate( &n32Value ); }

BOOL CGSAUInt32::Update( UINT32 n32Value )
{
	if( FALSE == CGIAttr::Update( &n32Value ) )
		return FALSE;

	m_un32 = n32Value;
	return TRUE;
}
