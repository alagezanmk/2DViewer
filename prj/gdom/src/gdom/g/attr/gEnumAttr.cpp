#include "stdafx.h"
#include <g\attr\gEnumAttr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSAEnum::CGSAEnum( LPCTSTR pctszName ) :
	CGIAttr( pctszName )
{
	m_en = 0;
}

void CGSAEnum::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue.Format( _T("%d"), m_en );
}

BOOL CGSAEnum::Validate( CString& rcszValue ) const
{
	ENUM en = (ENUM)_tcstol( rcszValue, NULL, 10 );
	return Validate( en );
}	

BOOL CGSAEnum::Update( CString& rcszValue )
{
	ENUM en = (ENUM)_tcstol( rcszValue, NULL, 10 );
	return Update( en );
}

BOOL CGSAEnum::Set( ENUM enValue ) 
{
	if( m_en == enValue )
		return TRUE;

	if( FALSE == Validate( enValue ) )
		return FALSE;

	if( FALSE == Update( enValue ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSAEnum::Validate( ENUM& renValue ) const {
	return CGIAttr::Validate( &renValue ); }

BOOL CGSAEnum::Update( ENUM enValue )
{
	if( FALSE == CGIAttr::Update( &enValue ) )
		return FALSE;

	m_en = enValue;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGMAEnum::~CGMAEnum()
{}

INT* CGMAEnum::GetList() {
	return m_arren.GetData(); }

const INT* CGMAEnum::GetList() const {
	return m_arren.GetData(); }

const INT CGMAEnum::GetAt( INT nIndex ) const {
	return m_arren.GetAt( nIndex ); }

BOOL CGMAEnum::SetAt( INT nIndex, INT enValue, INT nCount /*= 1*/ )
{
	INT nLast = nIndex + nCount;
	for( INT i = nIndex; i < nLast; i++ )
		m_arren.SetAtGrow( i, enValue );

	return TRUE;
}

BOOL CGMAEnum::InsertAt( INT nIndex, INT enValue, INT nCount /*= 1*/ )
{
	m_arren.InsertAt( nIndex, enValue, nCount );
	return TRUE;
}

BOOL CGMAEnum::RemoveAt( INT nIndex, INT nCount /*= 1*/ )
{
	m_arren.RemoveAt( nIndex, nCount );
	return TRUE;
}
