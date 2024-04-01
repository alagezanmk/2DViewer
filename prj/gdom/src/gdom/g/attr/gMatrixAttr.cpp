#include "stdafx.h"
#include <g\attr\gMatrixAttr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGSFMatrix::~CGSFMatrix()
{}

const GMatrixF& CGSFMatrix::Get() const {
	return m_mtxf; }

BOOL CGSFMatrix::Set( const GMatrixF& rmtxValue ) 
{
	m_mtxf = rmtxValue;
	return TRUE; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGMFMatrix::~CGMFMatrix()
{}

GMatrixF* CGMFMatrix::GetList() {
	return m_arrpmtxf.GetData(); }

const GMatrixF* CGMFMatrix::GetList() const {
	return m_arrpmtxf.GetData(); }
	
const GMatrixF& CGMFMatrix::GetAt( INT nIndex ) const {
	CGMFMatrix* pThis = const_cast<CGMFMatrix*>(this);
	return pThis->m_arrpmtxf.ElementAt( nIndex ); }

BOOL CGMFMatrix::SetAt( INT nIndex, const GMatrixF& rmtxValue, INT nCount /*= 1*/ )
{
	INT nLast = nIndex + nCount;
	for( INT i = nIndex; i < nLast; i++ )
		m_arrpmtxf.SetAtGrow( i, rmtxValue );

	return TRUE;
}

BOOL CGMFMatrix::InsertAt( INT nIndex, const GMatrixF& rmtxValue, INT nCount /*= 1*/ )
{
	m_arrpmtxf.InsertAt( nIndex, rmtxValue, nCount );
	return TRUE;
}

BOOL CGMFMatrix::RemoveAt( INT nIndex, INT nCount /*= 1*/ )
{
	m_arrpmtxf.RemoveAt( nIndex, nCount );
	return TRUE;
}
