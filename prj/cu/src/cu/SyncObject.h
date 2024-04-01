#ifndef ___SYNC_SECTION__PH___
#define ___SYNC_SECTION__PH___

#include "uiEvent.h"

class CLockCriticalSection
{
public:
	CLockCriticalSection( CCriticalSection& rCrtSect );
	CLockCriticalSection( CRITICAL_SECTION& rCrtSect );
	~CLockCriticalSection();

	CRITICAL_SECTION* m_pCriticalSection;
};

inline CLockCriticalSection::CLockCriticalSection( CCriticalSection& rCrtSect )
{
	m_pCriticalSection = &rCrtSect.m_sect;
	ASSERT( m_pCriticalSection );
	if( m_pCriticalSection )	
		EnterCriticalSection( m_pCriticalSection );
}

inline CLockCriticalSection::CLockCriticalSection( CRITICAL_SECTION& rCrtSect )
{
	m_pCriticalSection = &rCrtSect;
	ASSERT( m_pCriticalSection );
	if( m_pCriticalSection )
		EnterCriticalSection( m_pCriticalSection );
}

inline CLockCriticalSection::~CLockCriticalSection()
{
	ASSERT( m_pCriticalSection );
	if( m_pCriticalSection )
		LeaveCriticalSection( m_pCriticalSection );
}

#endif //!___SYNC_SECTION__PH___
