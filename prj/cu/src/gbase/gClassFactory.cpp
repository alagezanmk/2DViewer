#include "stdafx.h"
#include "gClassFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
CGClassFactory::CGClassFactory()
{}

CGClassFactory::~CGClassFactory()
{}

BOOL CGClassFactory::IsCreatorAvailable( LPCTSTR pctszClassName ) const
{
	CLockCriticalSection cs( m_cSect );

	void* pvCreator;
	BOOL bReturn = m_mapClassName_CreateObject.Lookup( pctszClassName, pvCreator );

	return bReturn;
}

BOOL CGClassFactory::AddCreator( LPCTSTR pctszClassName, PFNCreateObjectCB pfnCreatorCB )
{
	CLockCriticalSection cs( m_cSect );
	
	if( IsCreatorAvailable( pctszClassName ) )
		return FALSE;	// Is already available

	m_mapClassName_CreateObject.SetAt( pctszClassName, pfnCreatorCB );
	return TRUE;
}

void* CGClassFactory::CreateFactoryObject( LPCTSTR pctszClassName, void* pCookie /*= NULL*/ )
{
	void* pvCreator;
	BOOL bReturn = m_mapClassName_CreateObject.Lookup( pctszClassName, pvCreator );
	if( FALSE == bReturn )
		return NULL;	// Creator is not available

	PFNCreateObjectCB pfnCreateCB = (PFNCreateObjectCB)pvCreator;
	return (*pfnCreateCB)( pctszClassName, pCookie );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CGFactoryObject::CGFactoryObject() {
	m_pClassFactory = NULL; }

CGFactoryObject::~CGFactoryObject() {
	SetClassFactory( NULL ); }

void CGFactoryObject::SetClassFactory( CGClassFactory* pClassFactory )
{
	if( m_pClassFactory == pClassFactory )
		return;

	if( m_pClassFactory ) 
	{
 		m_pClassFactory->Release();
		m_pClassFactory = NULL;
	}

	m_pClassFactory = pClassFactory;
	if( m_pClassFactory ) 
		m_pClassFactory->AddRef();
}

void* CGFactoryObject::CreateFactoryObject( LPCTSTR pctszClassName, void* pCookie /*= NULL*/ )
{
	void* pObject = NULL;
	
	LockObjectLink();
	CGFactoryObject* pNode = this;
	while( pNode )
	{
		if( pNode->m_pClassFactory )
		{
			pObject = pNode->m_pClassFactory->CreateFactoryObject( pctszClassName, pCookie );
			if( pObject )
				break;
		}
		
		pNode = pNode->GetFactoryObjectParent();
	}
	
	LockObjectLink( FALSE );
	return pObject;
}
