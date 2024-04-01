#include "stdafx.h"
#include <g\attr\gRectAttr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSARectF::CGSARectF( LPCTSTR pctszName ) :
	CGIAttr( pctszName )
{
	m_grc.left = 0.f;
	m_grc.right = 0.f;
	m_grc.right = 0.f;
	m_grc.bottom = 0.f;
}

void CGSARectF::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue.Format( _T("%g, %g, %g, %g"), m_grc.left, m_grc.top, m_grc.right, m_grc.bottom );
}

BOOL CGSARectF::Validate( CString& rcszValue ) const
{
	GRectF grc;
	INT nResult = _stscanf( (LPCTSTR)rcszValue, _T("%g, %g, %g, %g"), 
												&grc.left, &grc.top, &grc.right, &grc.bottom );

	if( nResult < 4 || FALSE == Validate( grc ) )
		return FALSE;

	rcszValue.Format( _T("%g, %g, %g, %g"), 
						grc.left, grc.top, grc.right, grc.bottom );
	return TRUE;
}	

BOOL CGSARectF::Update( CString& rcszValue )
{
	GRectF grc;
	INT nResult = _stscanf( (LPCTSTR)rcszValue, _T("%g, %g, %g, %g"), 
												&grc.left, &grc.top, &grc.right, &grc.bottom );

	if( nResult < 4 )
		return FALSE;

	return Update( grc );
}

BOOL CGSARectF::Set( const GRectF& rgrcValue ) 
{
	GRectF grcValue = rgrcValue;
	if( FALSE == Validate( grcValue ) )
		return FALSE;

	if( FALSE == Update( grcValue ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSARectF::Set( FLOAT fLeft, FLOAT fTop, FLOAT fRight, FLOAT fBottom )
{
	if( FALSE == Validate( fLeft, fTop, fRight, fBottom ) )
		return FALSE;

	if( FALSE == Update( fLeft, fTop, fRight, fBottom ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSARectF::Validate( GRectF& rgrcValue ) const {
	return CGIAttr::Validate( &rgrcValue ); }

BOOL CGSARectF::Validate( FLOAT& rfLeft, FLOAT& rfTop, FLOAT& rfRight, FLOAT& rfBottom ) const
{
	CGRectF grc( rfLeft, rfTop, rfRight, rfBottom );
	if( FALSE == Validate( grc ) )
		return FALSE;

	rfLeft = grc.left;
	rfTop = grc.top;
	rfRight = grc.right;
	rfBottom = grc.bottom;
	return TRUE;
}

BOOL CGSARectF::Update( const GRectF& rgrcValue )
{
	if( FALSE == CGIAttr::Update( (void*)&rgrcValue ) )
		return FALSE;

	m_grc = rgrcValue;
	return TRUE;
}

BOOL CGSARectF::Update( FLOAT fLeft, FLOAT fTop, FLOAT fRight, FLOAT fBottom )
{
	CGRectF grc( fLeft, fTop, fRight, fBottom );
	return Update( grc );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGMARectF::~CGMARectF()
{}

GRectF* CGMARectF::GetList() {
	return m_arrgrc.GetData(); }

const GRectF* CGMARectF::GetList() const {
	return m_arrgrc.GetData(); }

const GRectF& CGMARectF::GetAt( INT nIndex ) const {
	CGMARectF* pThis = const_cast<CGMARectF*>(this);
	return pThis->m_arrgrc.ElementAt( nIndex ); }

BOOL CGMARectF::SetAt( INT nIndex, const GRectF& rgptValue, INT nCount /*= 1*/ )
{
	INT nLast = nIndex + nCount;
	for( INT i = nIndex; i < nLast; i++ )
			m_arrgrc.SetAtGrow( i, rgptValue );

	return TRUE;
}

BOOL CGMARectF::InsertAt( INT nIndex, const GRectF& rgptValue, INT nCount /*= 1*/ )
{
	m_arrgrc.InsertAt( nIndex, rgptValue, nCount );
	return TRUE;
}

BOOL CGMARectF::RemoveAt( INT nIndex, INT nCount /*= 1*/ )
{
	m_arrgrc.RemoveAt( nIndex, nCount );
	return TRUE;
}
