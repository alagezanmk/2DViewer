#include "stdafx.h"
#include <g\attr\gPointFAttr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSAPointF::CGSAPointF( LPCTSTR pctszName ) :
	CGIAttr( pctszName )
{
	m_gptf.x = 0.f;
	m_gptf.y = 0.f;
}

void CGSAPointF::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		CGIAttr::Get( rcszValue );
	else
		rcszValue.Format( _T("%g, %g"), m_gptf.x, m_gptf.y );
}

BOOL CGSAPointF::Set( LPCTSTR pctszValue )
{
	if( 0 == lstrcmpi( CGIAttr::ATTR_NOT_SET_STR, pctszValue ) )
	{
		NotSet();
		return TRUE;
	}
	
	FLOAT x = m_gptf.x;
	FLOAT y = m_gptf.y;
	_stscanf( pctszValue, _T("%g, %g"), &x, &y );
	return Set( x, y );
}

BOOL CGSAPointF::Validate( CString& rcszValue ) const
{
	CGPointF gptf;
	INT nResult = _stscanf( (LPCTSTR)rcszValue, _T("%g, %g"), 
												&gptf.x, &gptf.y );

	if( nResult < 2 || FALSE == Validate( gptf ) )
		return FALSE;

	rcszValue.Format( _T("%g, %g"), 
					  gptf.x, gptf.y );
	return TRUE;
}	

BOOL CGSAPointF::Update( CString& rcszValue )
{
	CGPointF gptf;
	INT nResult = _stscanf( (LPCTSTR)rcszValue, _T("%g, %g, %g, %g"), 
												&gptf.x, &gptf.y );

	if( nResult < 2 )
		return FALSE;

	return Update( gptf );
}

BOOL CGSAPointF::Set( const GPointF& rgptfValue ) 
{
	if( m_gptf.x == rgptfValue.x && m_gptf.y == rgptfValue.y )
		return TRUE;

	GPointF gptf = rgptfValue;
	if( FALSE == Validate( gptf ) )
		return FALSE;

	if( FALSE == Update( gptf ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSAPointF::Set( FLOAT fX, FLOAT fY )
{
	if( FALSE == Validate( fX, fY ) )
		return FALSE;

	if( FALSE == Update( fX, fY ) )
		return FALSE;

	Changed();
	return TRUE; 
}

BOOL CGSAPointF::Validate( GPointF& rgptfValue ) const {
	return CGIAttr::Validate( &rgptfValue ); }

BOOL CGSAPointF::Validate( FLOAT& rfX, FLOAT& rfY ) const
{
	CGPointF gptf( rfX, rfY );
	if( FALSE == Validate( gptf ) )
		return FALSE;

	rfX = gptf.x;
	rfY = gptf.y;
	return TRUE;
}

BOOL CGSAPointF::Update( const GPointF& rgptfValue )
{
	if( FALSE == CGIAttr::Update( (void*)&rgptfValue ) )
		return FALSE;

	m_gptf = rgptfValue;
	return TRUE;
}

BOOL CGSAPointF::Update( FLOAT fX, FLOAT fY )
{
	CGPointF gptf( fX, fY );
	return Update( gptf );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGMAPointF::~CGMAPointF()
{}

GPointF* CGMAPointF::GetList() {
	return m_arrgpt.GetData(); }

const GPointF* CGMAPointF::GetList() const {
	return m_arrgpt.GetData(); }

const GPointF& CGMAPointF::GetAt( INT nIndex ) const {
	CGMAPointF* pThis = const_cast<CGMAPointF*>(this);
	return pThis->m_arrgpt.ElementAt( nIndex ); }

BOOL CGMAPointF::SetAt( INT nIndex, const GPointF& rgptValue, INT nCount /*= 1*/ )
{
	INT nLast = nIndex + nCount;
	for( INT i = nIndex; i < nLast; i++ )
			m_arrgpt.SetAtGrow( i, rgptValue );

	return TRUE;
}

BOOL CGMAPointF::InsertAt( INT nIndex, const GPointF& rgptValue, INT nCount /*= 1*/ )
{
	m_arrgpt.InsertAt( nIndex, rgptValue, nCount );
	return TRUE;
}

BOOL CGMAPointF::RemoveAt( INT nIndex, INT nCount /*= 1*/ )
{
	m_arrgpt.RemoveAt( nIndex, nCount );
	return TRUE;
}
