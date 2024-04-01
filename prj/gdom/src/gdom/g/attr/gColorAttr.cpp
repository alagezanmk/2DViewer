#include "stdafx.h"
#include <g\attr\gColorAttr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGIPColor::~CGIPColor()
{}

const CGIColor& CGIPColor::Get() const {
	return m_color; }

BOOL CGIPColor::Set( const CGIColor& rcValue ) 
{
	m_color = rcValue;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGIPArrColor::~CGIPArrColor()
{}

CGIColor* CGIPArrColor::GetList() {
	return m_arrColor.GetData(); }

const CGIColor* CGIPArrColor::GetList() const {
	return m_arrColor.GetData(); }

const CGIColor& CGIPArrColor::GetAt( INT nIndex ) const {
	CGIPArrColor* pThis = const_cast<CGIPArrColor*>(this);
	return pThis->m_arrColor.ElementAt( nIndex ); }

BOOL CGIPArrColor::SetAt( INT nIndex, const CGIColor& rcValue, INT nCount /*= 1*/ )
{
	INT nLast = nIndex + nCount;
	for( INT i = nIndex; i < nLast; i++ )
		m_arrColor.SetAtGrow( i, rcValue );

	return TRUE;
}

BOOL CGIPArrColor::InsertAt( INT nIndex, const CGIColor& rcValue, INT nCount /*= 1*/ )
{
	m_arrColor.InsertAt( nIndex, rcValue, nCount );
	return TRUE;
}

BOOL CGIPArrColor::RemoveAt( INT nIndex, INT nCount /*= 1*/ )
{
	m_arrColor.RemoveAt( nIndex, nCount );
	return TRUE;
}
