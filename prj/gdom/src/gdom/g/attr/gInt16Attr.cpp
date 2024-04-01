#include "stdafx.h"
#include <g\attr\gInt16Attr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSAInt16::CGSAInt16( LPCTSTR pctszName ) :
	CGIAttr( pctszName )
{
	m_n16 = 0;
}

void CGSAInt16::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue.Format( _T("%d"), (INT)m_n16 );
}

BOOL CGSAInt16::Validate( CString& rcszValue ) const
{
	INT16 en = (INT16)_tcstol( rcszValue, NULL, 10 );
	return Validate( en );
}

BOOL CGSAInt16::Update( CString& rcszValue )
{
	INT16 en = (INT16)_tcstol( rcszValue, NULL, 10 );
	return Update( en );
}

BOOL CGSAInt16::Set( INT16 n16Value ) 
{
	if( m_n16 == n16Value )
		return TRUE;

	if( FALSE == Validate( n16Value ) )
		return FALSE;

	if( FALSE == Update( n16Value ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSAInt16::Validate( INT16& n16Value ) const {
	return CGIAttr::Validate( &n16Value ); }

BOOL CGSAInt16::Update( INT16 n16Value )
{
	if( FALSE == CGIAttr::Update( &n16Value ) )
		return FALSE;

	m_n16 = n16Value;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSAUInt16::CGSAUInt16( LPCTSTR pctszName ) :
	CGIAttr( pctszName )
{
	m_un16 = 0;
}

void CGSAUInt16::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue.Format( _T("%d"), (INT)m_un16 );
}

BOOL CGSAUInt16::Validate( CString& rcszValue ) const
{
	UINT16 en = (UINT16)_tcstol( rcszValue, NULL, 10 );
	return Validate( en );
}

BOOL CGSAUInt16::Update( CString& rcszValue )
{
	UINT16 en = (UINT16)_tcstol( rcszValue, NULL, 10 );
	return Update( en );
}

BOOL CGSAUInt16::Set( UINT16 n16Value ) 
{
	if( m_un16 == n16Value )
		return TRUE;

	if( FALSE == Validate( n16Value ) )
		return FALSE;

	if( FALSE == Update( n16Value ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSAUInt16::Validate( UINT16& n16Value ) const {
	return CGIAttr::Validate( &n16Value ); }

BOOL CGSAUInt16::Update( UINT16 n16Value )
{
	if( FALSE == CGIAttr::Update( &n16Value ) )
		return FALSE;

	m_un16 = n16Value;
	return TRUE;
}
