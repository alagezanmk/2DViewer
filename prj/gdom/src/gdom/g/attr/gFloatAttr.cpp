#include "stdafx.h"
#include <g\attr\gFloatAttr.h>
#include <g\type\gElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
IMPL_GTPYECLASS_DYNCREATE( CGSAFloat, CGIAttr, _T("FloatAttr") )
CGSAFloat::CGSAFloat( LPCTSTR pctszName ) :
	CGIAttr( pctszName )
{
	m_pgInstanceType = &GetClassType();
	m_f = 0.f;
}

void* CGSAFloat::GetPreviousValuePointer() 
{
	FLOAT* pFloat = new FLOAT;
	if( pFloat )
		*pFloat = m_f;

	return pFloat; 
}

void* CGSAFloat::GetNewValuePointer() {
	return &m_f; }

void CGSAFloat::DeleteNewValuePointer( void* pPointer )
{
	ASSERT( pPointer == &m_f );	/// The address pPointer should be same of GetNewValuePointer() value
}

void CGSAFloat::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue.Format( _T("%g"), m_f );
}

FLOAT CGSAFloat::Get() const 
{
	FLOAT f = m_f;
	INT nValueType = GetValue( &f );
	if( CGIAttr::UNDEFINED_VALUE_TYPE == nValueType )
		return 0.f;

	return f;
}

BOOL CGSAFloat::Validate( CString& rcszValue ) const
{
	FLOAT f = (FLOAT)_tcstod( rcszValue, NULL );
	BOOL bResult = Validate( f );

	rcszValue.Format( _T("g"), &f );
	return bResult;
}

BOOL CGSAFloat::Update( CString& rcszValue )
{
	FLOAT f = (FLOAT)_tcstod( rcszValue, NULL );
	return Update( m_f );
}

BOOL CGSAFloat::Set( LPCTSTR pctszValue )
{
	if( 0 == lstrcmpi( CGIAttr::ATTR_NOT_SET_STR, pctszValue ) )
	{
		NotSet();
		return TRUE;
	}

	FLOAT fValue = m_f;
	_stscanf( pctszValue, _T("%g"), &fValue );
	return Set( fValue );
}

BOOL CGSAFloat::Set( FLOAT fValue ) 
{
	if( m_f == fValue )
		return TRUE;

	if( FALSE == Validate( fValue ) )
		return FALSE;

	if( FALSE == Update( fValue ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSAFloat::Validate( FLOAT& rfValue ) const {
	return CGIAttr::Validate( &rfValue ); }

BOOL CGSAFloat::Update( FLOAT fValue )
{
	if( FALSE == CGIAttr::Update( &fValue ) )
		return FALSE;

	OnUpdate( &fValue );
	m_f = fValue;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGMAFloat::~CGMAFloat()
{}

FLOAT* CGMAFloat::GetList() {
	return m_arrf.GetData(); }

const FLOAT* CGMAFloat::GetList() const {
	return m_arrf.GetData(); }

FLOAT CGMAFloat::GetAt( INT nIndex ) const {
	return m_arrf.GetAt( nIndex ); }

BOOL CGMAFloat::SetAt( INT nIndex, FLOAT fValue, INT nCount /*= 1*/ )
{
	INT nLast = nIndex + nCount;
	for( INT i = nIndex; i < nLast; i++ )
		m_arrf.SetAtGrow( i, fValue );

	return TRUE;
}

BOOL CGMAFloat::InsertAt( INT nIndex, FLOAT fValue, INT nCount /*= 1*/ )
{
	m_arrf.InsertAt( nIndex, fValue, nCount );
	return TRUE;
}

BOOL CGMAFloat::RemoveAt( INT nIndex, INT nCount /*= 1*/ )
{
	m_arrf.RemoveAt( nIndex, nCount );
	return TRUE;
}
