#include "stdafx.h"
#include <g\attr\gStringAttr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
IMPL_GTPYECLASS_DYNCREATE( CGSAString, CGIAttr, _T("StringAttr") )
CGSAString::CGSAString( LPCTSTR pctszName ) :
	CGIAttr( pctszName ) {
	m_pgInstanceType = &GetClassType(); }

void CGSAString::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue = m_csz;
}

BOOL CGSAString::Set( LPCTSTR pctszValue ) 
{
	if( m_csz == pctszValue )
		return TRUE;

	CString csz = pctszValue;
	if( FALSE == Validate( csz ) )
		return FALSE;

	if( FALSE == Update( csz ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSAString::Validate( CString& rcszValue ) const {
	return TRUE; }

BOOL CGSAString::Update( CString& rcszValue ) 
{
	OnUpdate( &rcszValue );
	m_csz = rcszValue;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGMAString::~CGMAString()
{}

CString** CGMAString::GetList() {
	return (CString**)m_arrcsz.GetData(); }

const CString** CGMAString::GetList() const {
	return (const CString**)m_arrcsz.GetData(); }

LPCTSTR CGMAString::GetAt( INT nIndex ) const {
	return (LPCTSTR)m_arrcsz.GetAt( nIndex ); }

BOOL CGMAString::SetAt( INT nIndex, LPCTSTR pctszValue, INT nCount /*= 1*/ )
{
	INT nLast = nIndex + nCount;
	for( INT i = nIndex; i < nLast; i++ )
		m_arrcsz.SetAtGrow( i, pctszValue );

	return TRUE;
}

BOOL CGMAString::InsertAt( INT nIndex, LPCTSTR pctszValue, INT nCount /*= 1*/ )
{
	m_arrcsz.InsertAt( nIndex, pctszValue, nCount );
	return TRUE;
}

BOOL CGMAString::RemoveAt( INT nIndex, INT nCount /*= 1*/ )
{
	m_arrcsz.RemoveAt( nIndex, nCount );
	return TRUE;
}

