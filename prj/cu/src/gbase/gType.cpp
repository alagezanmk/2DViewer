#include "stdafx.h"
#include <gbase\gType.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGTypeData
{
public:
	CGTypeData( const CGType* pType, 
				const CGType* pParentType, 
				LPCTSTR pctszName );
	virtual ~CGTypeData();

public:
	static CPtrArray* m_parpTypeList;

	const CGType*	m_pType;
	const CGType*	m_pParentType;
	const CString	m_cszName;
};

CPtrArray* CGTypeData::m_parpTypeList = NULL;

CGTypeData::CGTypeData( const CGType* pType, 
						const CGType* pParentType, 
						LPCTSTR pctszName )
  : m_pType( pType ), 
	m_pParentType( pParentType ), 
	m_cszName( pctszName )
{
	if( NULL == m_parpTypeList )
		VERIFY( m_parpTypeList = new CPtrArray );

	m_parpTypeList->Add( this );
}

CGTypeData::~CGTypeData()
{
	if( NULL == m_parpTypeList )
		return;

	INT nCount = m_parpTypeList->GetSize();
	CGTypeData** ppTypeData = (CGTypeData**)m_parpTypeList->GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppTypeData[i]->m_cszName == m_cszName )
		{
			m_parpTypeList->RemoveAt( i );
			break;
		}
	}

	if( 1 == nCount )
	{
		delete m_parpTypeList;
		m_parpTypeList = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Define Type Data of a type NONE
CGTypeData	_GNoneTypeData( NULL, NULL, _T("NoneType") );

/// Define NONE Type
CGType _GNoneType( &_GNoneTypeData );

CGType::CGType( CGTypeData* pTypeData )
 : m_pTypeData( pTypeData )
{}

CGType::CGType()  {
	m_pTypeData = NULL; }

CGType::CGType( const CGType* pParentType, LPCTSTR pctszName )
{
	m_pTypeData = NULL;
	if( FALSE == InitType( pParentType, pctszName ) )
		throw "CGType::CGType: Fail to create internal structure \"TypeData\" object";
}

CGType::~CGType()
{
	if( m_pTypeData && m_pTypeData != &_GNoneTypeData )
		delete m_pTypeData;
}

BOOL CGType::InitType( const CGType* pParentType, LPCTSTR pctszName )
{
	if( m_pTypeData )
	{
		ASSERT( FALSE );
		return FALSE;	// Already initialized
	}

	VERIFY( m_pTypeData = new CGTypeData( this, pParentType, pctszName ) );
	if( NULL == m_pTypeData )
		return FALSE;

	return TRUE;
}

void CGType::operator=( const CGType& rType ) {
	m_pTypeData = rType.m_pTypeData; }

BOOL CGType::operator==( const CGType& rType ) const {
	return (rType.m_pTypeData == m_pTypeData); }

BOOL CGType::operator!=( const CGType& rType ) const {
	return (rType.m_pTypeData != m_pTypeData); }

const CGType& CGType::GetNullType() {
	return _GNoneType; }

const CGType& CGType::GetType( LPCTSTR pctszName )
{
	if( NULL == CGTypeData::m_parpTypeList )
		return _GNoneType;

	INT nCount = CGTypeData::m_parpTypeList->GetSize();
	CGTypeData** ppTypeData = (CGTypeData**)CGTypeData::m_parpTypeList->GetData();
	for( INT i = 0; i < nCount; i++ )
		if( ppTypeData[i]->m_cszName == pctszName )
			return *ppTypeData[i]->m_pType;

	return _GNoneType;
}

LPCTSTR CGType::GetName() const
{
	if( m_pTypeData )
		return m_pTypeData->m_cszName;

	return NULL;
}

BOOL CGType::IsDerivedFrom( const CGType& rType ) const
{
	if( NULL == m_pTypeData )
	{
		ASSERT( FALSE );
		return FALSE;
	}

	CGTypeData* pTypeData = m_pTypeData;
	
	do
	{
		if( pTypeData == rType.m_pTypeData )
			return TRUE;

		if( pTypeData->m_pParentType )
			pTypeData = pTypeData->m_pParentType->m_pTypeData;
		else
			pTypeData = NULL;

	}while( pTypeData );

	return FALSE;
}