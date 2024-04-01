#ifndef ___CLASS_FACTORY__PH___
#define ___CLASS_FACTORY__PH___

#include "gObject.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGClassFactory : public CGObject
{
public:
	typedef void* (*PFNCreateObjectCB)( LPCTSTR pctszClassName, void* pCookie );

public:
	CGClassFactory();
	virtual ~CGClassFactory();

public:
	BOOL IsCreatorAvailable( LPCTSTR pctszClassName ) const;
	BOOL AddCreator( LPCTSTR pctszClassName, PFNCreateObjectCB pfnCreatorCB );
	BOOL RemoveCreator( LPCTSTR pctszClassName );

	virtual void* CreateFactoryObject( LPCTSTR pctszClassName, void* pCookie = NULL );

protected: 
mutable		
	CCriticalSection	m_cSect;
	CMapStringToPtr		m_mapClassName_CreateObject;
};

inline BOOL CGClassFactory::RemoveCreator( LPCTSTR pctszClassName ) {
	return m_mapClassName_CreateObject.RemoveKey( pctszClassName ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGFactoryObject
{
public:
	CGFactoryObject();
	virtual ~CGFactoryObject();

public:
	virtual CGClassFactory* GetClassFactory();
	virtual const CGClassFactory* GetClassFactory() const;
	void SetClassFactory( CGClassFactory* pClassFactory );

	virtual void LockObjectLink( BOOL bLock = TRUE ) = 0;
	virtual CGFactoryObject* GetFactoryObjectParent() = 0;
	virtual void* CreateFactoryObject( LPCTSTR pctszClassName, void* pCookie = NULL ); 

protected:
	CGClassFactory* m_pClassFactory;
};

inline CGClassFactory* CGFactoryObject::GetClassFactory() {
	return m_pClassFactory; }

inline const CGClassFactory* CGFactoryObject::GetClassFactory() const {
	return m_pClassFactory; }

#endif //!___CLASS_FACTORY__PH___

