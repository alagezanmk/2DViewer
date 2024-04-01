#include "stdafx.h"
#include <g\type\gEventPriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGZoomEventPriv::CGZoomEventPriv( CGEventTarget* pTarget )
{
	m_pctszEventType = CGZoomEvent::EVENT;
	m_pEventTarget = pTarget;
}

CGScrollEventPriv::CGScrollEventPriv( CGEventTarget* pTarget )
{
	m_pctszEventType = CGScrollEvent::EVENT;
	m_pEventTarget = pTarget;
}

CGMutationEventPriv::CGMutationEventPriv( LPCTSTR pctszEventType, CGEventTarget* pTarget )
{
	m_pctszEventType = pctszEventType;
	m_pEventTarget = pTarget;
}

void CGMutationEventPriv::SetNewValue( void* pNewValue ) {
	m_pvNewValue = pNewValue; }
