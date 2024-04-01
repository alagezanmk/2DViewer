#include "stdafx.h"
#include <g\attr\gBoolAttr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSABool::CGSABool( LPCTSTR pctszName ) :
	CGIAttr( pctszName )
{
	m_b = FALSE;
}

void CGSABool::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue = m_b ?_T("TRUE") :_T("FALSE");
}

BOOL CGSABool::Validate( CString& rcszValue ) const
{
	BOOL b = FALSE;
	if( 0 == rcszValue.CompareNoCase( _T("true" ) )
		|| 0 == rcszValue.CompareNoCase( _T("t" ) )
		|| 0 == rcszValue.CompareNoCase( _T("1" ) ) )
		b = TRUE;
	else if( 0 == rcszValue.CompareNoCase( _T("false" ) )
		|| 0 == rcszValue.CompareNoCase( _T("f" ) )
		|| 0 == rcszValue.CompareNoCase( _T("0" ) ) )
		b = FALSE;

	BOOL bResult = Validate( b );

	rcszValue = b ?_T("TRUE") :_T("FALSE");
	return bResult;
}	

BOOL CGSABool::Update( CString& rcszValue )
{
	BOOL b = FALSE;
	if( 0 == rcszValue.CompareNoCase( _T("true" ) )
		|| 0 == rcszValue.CompareNoCase( _T("t" ) )
		|| 0 == rcszValue.CompareNoCase( _T("1" ) ) )
		b = TRUE;
	else if( 0 == rcszValue.CompareNoCase( _T("false" ) )
		|| 0 == rcszValue.CompareNoCase( _T("f" ) )
		|| 0 == rcszValue.CompareNoCase( _T("0" ) ) )
		b = FALSE;

	return Update( b );
}

BOOL CGSABool::Set( LPCTSTR pctszValue )
{
	if( 0 == lstrcmpi( CGIAttr::ATTR_NOT_SET_STR, pctszValue ) )
	{
		NotSet();
		return TRUE;
	}

	BOOL b = m_b;
	if( 0 == lstrcmpi( pctszValue, _T("true") )
		|| 0 == lstrcmpi( pctszValue, _T("t") )
		|| 0 == lstrcmpi( pctszValue, _T("1") ) )
		b = TRUE;
	else if( 0 == lstrcmpi( pctszValue, _T("false") )
		|| 0 == lstrcmpi( pctszValue, _T("f") )
		|| 0 == lstrcmpi( pctszValue, _T("0") ) )
		b = FALSE;

	if( b == m_b )
		return TRUE;

	return Set( b );
}

BOOL CGSABool::Set( BOOL bValue ) 
{
	if( m_b == bValue )
		return TRUE;

	if( FALSE == Validate( bValue ) )
		return FALSE;

	if( FALSE == Update( bValue ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSABool::Validate( BOOL& rbValue ) const {
	return CGIAttr::Validate( &rbValue ); }

BOOL CGSABool::Update( BOOL bValue )
{
	if( FALSE == CGIAttr::Update( &bValue ) )
		return FALSE;

	OnUpdate( &bValue );
	m_b = bValue;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGMABool::~CGMABool()
{}

BOOL* CGMABool::GetList() {
	return m_arrb.GetData(); }

const BOOL* CGMABool::GetList() const {
	return m_arrb.GetData(); }

BOOL CGMABool::GetAt( INT nIndex ) const {
	return m_arrb.GetAt( nIndex ); }

BOOL CGMABool::SetAt( INT nIndex, BOOL bValue, INT nCount /*= 1*/ )
{
	INT nLast = nIndex + nCount;
	for( INT i = nIndex; i < nLast; i++ )
		m_arrb.SetAtGrow( i, bValue );

	return TRUE;
}

BOOL CGMABool::InsertAt( INT nIndex, BOOL bValue, INT nCount /*= 1*/ )
{
	m_arrb.InsertAt( nIndex, bValue, nCount );
	return TRUE;
}

BOOL CGMABool::RemoveAt( INT nIndex, INT nCount /*= 1*/ )
{
	m_arrb.RemoveAt( nIndex, nCount );
	return TRUE;
}
