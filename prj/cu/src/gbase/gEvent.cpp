#include "stdafx.h"
#include <gbase\gEvent.h>
#include <g\type\gPriv.h>
#include <gbase\gEventNode.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
const EVENT_LINK CGEventListener::eventLink =
{
	&CGEventListener::_GetBaseEventLink,
	&CGEventListener::_eventLinkEntries[0]
};

const EVENT_LINK* PASCAL CGEventListener::_GetBaseEventLink() {
	return NULL; }

const EVENT_LINK* CGEventListener::GetEventLink() const {
	return &eventLink; }

const EVENT_LINK_ENTRY CGEventListener::_eventLinkEntries[] = {
	{0, 0, 0, 0, EvtSig_end, -1, (PEventHandler)0 }     // nothing here 
};

CGEventListener::CGEventListener()
{}

void CGEventListener::HandleEvent( CGEvent& rEvent )
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGEventListenerItem : public CGObject
{
public:
	CGEventListenerItem();
	void HandleEvent( CGEvent& rEvent );
	static void HandleEvent( CGEventListener& rListener, CGEvent& rEvent );

	static void GetEventLinkParam( CGEventListener& rListener, 
								   CGEvent& rEvent, 
								   UINT& rnCode, UINT& rid );
	static const EVENT_LINK_ENTRY* 
		GetEventLinkEntry( CGEventListener& rListener, 
							LPCTSTR pctszEventType, 
							UINT nCode, UINT id, INT nPhase );

public:
	LPCTSTR				m_pctszType;
	CGEventListener*	m_pEventListener;
	BOOL				m_bUseCapture;
	INT					m_nCallType;
};

CGEventListenerItem::CGEventListenerItem()
{
	m_pEventListener = NULL;
	m_bUseCapture = FALSE;
	m_nCallType = FALSE;
}

void CGEventListenerItem::HandleEvent( CGEvent& rEvent )
{
	ASSERT( m_pEventListener );
	HandleEvent( *m_pEventListener, rEvent );
}

union UEventLinkFunctions
{
	PEventHandler	pfn;   // generic member function pointer
	void (CGEventListener::*pfn_Event)(CGEvent&);
	void (CGEventListener::*pfn_MutationEvent)(CGMutationEvent&);
	void (CGEventListener::*pfn_ZoomEvent)(CGZoomEvent&);
	void (CGEventListener::*pfn_ScrollEvent)(CGScrollEvent&);
};

void CGEventListenerItem::HandleEvent( CGEventListener& rListener, CGEvent& rEvent )
{
	LPCTSTR pctszEventType = rEvent.GetType();
	const EVENT_LINK_ENTRY* lpEntry;

	UINT nCode, id;
	GetEventLinkParam( rListener, rEvent, nCode, id );
	lpEntry = GetEventLinkEntry( rListener, pctszEventType, nCode, id, rEvent.GetEventPhase() );
	if( lpEntry )
	{
		union UEventLinkFunctions mmf;
		mmf.pfn = lpEntry->pfn;

		switch( lpEntry->nSig )
		{
		case EvtSig_vE:
			(rListener.*mmf.pfn_Event)( rEvent );
			return;

		case EvtSig_vME:
			(rListener.*mmf.pfn_MutationEvent)( *((CGMutationEvent*)&rEvent) );
			return;

		case EvtSig_vZE:
			(rListener.*mmf.pfn_ZoomEvent)( *((CGZoomEvent*)&rEvent) );
			return;

		case EvtSig_vSE:
			(rListener.*mmf.pfn_ScrollEvent)( *((CGScrollEvent*)&rEvent) );
			return;
		}
	}

	rListener.HandleEvent( rEvent );
}

void CGEventListenerItem::GetEventLinkParam( CGEventListener& rListener, CGEvent& rEvent, UINT& rnCode, UINT& rid )
{
	rnCode = 0;
	rid = 0;

	LPCTSTR pctszEventType = rEvent.GetType();
	if( CGMutationEvent::DOMAttrModified == pctszEventType )
	{
		CGMutationEvent* pMutationEvent = (CGMutationEvent*)&rEvent;
		rid = 0;
	}
}

const EVENT_LINK_ENTRY* 
CGEventListenerItem::GetEventLinkEntry( CGEventListener& rListener, 
										LPCTSTR pctszEventType, 
										UINT nCode, UINT id, INT nPhase )
{
	const EVENT_LINK_ENTRY* lpEntry;
	const EVENT_LINK* pEventLink;

	for(  pEventLink = rListener.GetEventLink(); 
		  pEventLink; 
		  pEventLink = (*pEventLink->pfnGetBaseEventLink)() )
	{
		// Note: catch not so common but fatal mistake!!
		//      BEGIN_EVENT_LINK(CMyWnd, CMyWnd)
		ASSERT( pEventLink != (*pEventLink->pfnGetBaseEventLink)() );

		lpEntry = pEventLink->lpEntries;

		BOOL bFound = FALSE;
		while( lpEntry->nSig != AfxSig_end )
		{
			if( lpEntry->pctszEventType == pctszEventType 
				&& lpEntry->nCode == nCode 
				&& id >= lpEntry->nID && id <= lpEntry->nLastID
				&& (-1 == lpEntry->nPhase || nPhase == lpEntry->nPhase) )
			{
				bFound = TRUE;
				break;
			}

			lpEntry++;
		}

		if( FALSE == bFound )
			lpEntry = NULL;

		if( lpEntry )
			return lpEntry;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////}
struct SGEventPending
{
	CGEvent*		pEvent;
	CGEventTarget*	pTarget;
	INT				nLockCount;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
struct SGEventLock
{
	SGEventLock();

	INT Lock();
	INT Unlock();

protected:
	LPCTSTR			pctszType;
	CGEventTarget*	pTarget;
	INT				nLockCount;

	friend CGEventTarget;
};

SGEventLock::SGEventLock()
{
	pctszType = NULL;
	pTarget = NULL;
	nLockCount = 0;
}

INT SGEventLock::Lock()
{
	INT nLockEvent = this->nLockCount;
	if( this->nLockCount < 0 )
		this->nLockCount--;
	else
		this->nLockCount++;

	return nLockEvent;
}

INT SGEventLock::Unlock()
{
	INT nLockEvent = this->nLockCount;
	if( this->nLockCount < 0 )
		this->nLockCount++;
	else
		this->nLockCount--;

	return nLockEvent;
}

///////////////////////////////////////////////////////////////////////////////////////////////////}
IMPL_BASE_GTPYECLASS_DYNCREATE( CGEventTarget, _T("eventTarget") )
CGEventTarget::CGEventTarget()
{
	m_pgInstanceType = &GetClassType();

	m_parpListener = NULL;
	m_parpEventLock = NULL;
	m_parpEventPending = NULL;
	m_pEventUpLink = NULL;
}

CGEventTarget::~CGEventTarget()
{
	RemoveAllEventListener();
	RemoveAllPendingEvent();
}

INT CGEventTarget::FindEventListerner( LPCTSTR pctszType, 
									  const CGEventListener& rListener, 
									  BOOL bUseCapture, 
									  INT nCallType /*= CALL_TYPE_REPEAT*/ )
{
	if( NULL == m_parpListener )
		return -1;

	INT nCount = m_parpListener->GetSize();
	CGEventListenerItem** ppItem = (CGEventListenerItem**)m_parpListener->GetData();
	for( INT i = 0; i < nCount; i++ )
		if( ppItem[i]->m_pEventListener == &rListener 
		 && ppItem[i]->m_pctszType == pctszType
		 && ppItem[i]->m_bUseCapture == bUseCapture
		 && (CALL_TYPE_ANY == nCallType || ppItem[i]->m_nCallType == nCallType) )
			return i;

	return -1;
}

INT CGEventTarget::GetEventListerner( CPtrArray& rarpListerner, 
									 LPCTSTR pctszType, 
									 BOOL bUseCapture, 
									 INT nCallType /*= CALL_TYPE_REPEAT*/ )
{
	if( NULL == m_parpListener )
		return 0;

	INT nCount = m_parpListener->GetSize();
	CGEventListenerItem** ppItem = (CGEventListenerItem**)m_parpListener->GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppItem[i]->m_pctszType == pctszType 
		 && ppItem[i]->m_bUseCapture == bUseCapture
		 && (CALL_TYPE_ANY == nCallType || ppItem[i]->m_nCallType == nCallType) )
			rarpListerner.Add( ppItem[i] );
	}

	return rarpListerner.GetSize();;
}

BOOL CGEventTarget::AddEventListener( LPCTSTR pctszType,
									  CGEventListener& rListener,
									  BOOL bUseCapture, 
									  INT nCallType /*= CALL_TYPE_REPEAT*/ )
{
	INT nIndex = FindEventListerner( pctszType, rListener, bUseCapture, nCallType );
	if( -1 != nIndex )
		return FALSE;	// Already there

	if( NULL == _Create( m_parpListener ) )
		return FALSE;

	CGEventListenerItem* pListernerItem = new CGEventListenerItem;
	ASSERT( pListernerItem );
	pListernerItem->m_pctszType = pctszType;
	pListernerItem->m_pEventListener = &rListener;
	pListernerItem->m_bUseCapture = bUseCapture;
	pListernerItem->AddRef();
	
	m_parpListener->Add( pListernerItem );
	return TRUE;
}

BOOL CGEventTarget::RemoveEventListener( LPCTSTR pctszType,
										 CGEventListener& rListener,
										 BOOL bUseCapture, 
										 INT nCallType /*= CALL_TYPE_REPEAT*/ )
{
	if( NULL == m_parpListener )
		return FALSE;	// Not there

	INT nIndex = FindEventListerner( pctszType, rListener, bUseCapture, nCallType );
	if( -1 == nIndex )
		return FALSE;	// Not there

	CGEventListenerItem* pListernerItem = (CGEventListenerItem*)m_parpListener->GetAt( nIndex );
	m_parpListener->RemoveAt( nIndex );
	pListernerItem->Release();

	_DeleteIfEmpty( m_parpListener );
	return TRUE;
}

void CGEventTarget::RemoveAllEventListener()
{
	if( NULL == m_parpListener )
		return;

	INT nCount = m_parpListener->GetSize();
	CGEventListenerItem** ppItem = (CGEventListenerItem**)m_parpListener->GetData();
	for( INT i = 0; i < nCount; i++ )
		ppItem[i]->Release();

	_Delete( m_parpListener );
}

static INT _CheckCallType( CMapPtrToWord& rmapListenerToCallCount, CGEventListenerItem& rItem )
{
	WORD wCallCount;
	BOOL bFound = rmapListenerToCallCount.Lookup( rItem.m_pEventListener, wCallCount );
	if( bFound )
	{	
		if( CGEventListener::CALL_TYPE_ONCE == rItem.m_nCallType )
			return CGEventListener::CALL_TYPE_ONCE;

		wCallCount++;	// Increase time of called
	}
	else
		wCallCount = 1;	// First call

	rmapListenerToCallCount.SetAt( rItem.m_pEventListener, wCallCount );
	return CGEventListener::CALL_TYPE_REPEAT;
}

void CGEventTarget::DispatchEventNow( CGEvent& rEvent )
{
	// Initialize Event members
	rEvent.m_bPreventDefault = FALSE;

	INT t, i, nPathSize, nCount;
	CGEventListenerItem** ppItem;
	CPtrArray arpListerner, arpTargetPath;
	CGEventTarget** ppTarget;
	CMapPtrToWord mapListenerToCallCount;
	LPCTSTR ptszEventType = rEvent.GetType();

	// Get Target to Root path for Capture and Bubbling PHASE
	nPathSize = GetDispatchPath( arpTargetPath );

	// Recursively get all the Event Hook also
	while( nPathSize )
	{
		ppTarget = (CGEventTarget**)arpTargetPath.GetData();
		if( NULL == ppTarget[nPathSize - 1]->m_pEventUpLink )
			break;

		nPathSize = ppTarget[nPathSize - 1]->m_pEventUpLink->GetDispatchPath( arpTargetPath );
	}

	if( nPathSize )
	{
		ppTarget = (CGEventTarget**)arpTargetPath.GetData();

		// First Capturing Phasing
		rEvent.m_usnPhase = CGEvent::CAPTURING_PHASE;
		rEvent.m_bStopPropagation = FALSE;
		for( t = nPathSize - 1; t >= 1 && FALSE == rEvent.m_bStopPropagation; t-- )
		{
			nCount = ppTarget[t]->GetEventListerner( arpListerner, ptszEventType, TRUE, CALL_TYPE_ANY );
			if( nCount )
			{
				ppItem = (CGEventListenerItem**)arpListerner.GetData();

				rEvent.m_pCurTarget = ppTarget[t];
				for( i = 0; i < nCount; i++ )
				{
					if( CALL_TYPE_ONCE == _CheckCallType( mapListenerToCallCount, *ppItem[i] ) )
						continue;

					ppItem[i]->HandleEvent( rEvent );
				}

				arpListerner.RemoveAll();
			}
		}
	}

	// First At Target Phase
	if( FALSE == rEvent.m_bStopPropagation )
	{
		rEvent.m_usnPhase = CGEvent::AT_TARGET;
		rEvent.m_pCurTarget = (CGEventTarget*)this;		// TODO: Verify why type cast is required
		nCount = GetEventListerner( arpListerner, ptszEventType, FALSE, CALL_TYPE_ANY );
		if( nCount )
		{
			ppItem = (CGEventListenerItem**)arpListerner.GetData();
			for( i = 0; i < nCount && FALSE == rEvent.m_bStopPropagation; i++ )
			{
				if( CALL_TYPE_ONCE == _CheckCallType( mapListenerToCallCount, *ppItem[i] ) )
					continue;

				ppItem[i]->HandleEvent( rEvent );
			}

			arpListerner.RemoveAll();
		}
	}

	if( nPathSize )
	{
		// Now Bubbling Phasing
		if( FALSE == rEvent.m_bStopPropagation && 
			rEvent.m_bBubbles )
		{
			rEvent.m_usnPhase = CGEvent::BUBBLING_PHASE;
			for( t = 1; t < nPathSize && FALSE == rEvent.m_bStopPropagation; t++ )
			{
				nCount = ppTarget[t]->GetEventListerner( arpListerner, ptszEventType, FALSE, CALL_TYPE_ANY );
				if( nCount )
				{
					ppItem = (CGEventListenerItem**)arpListerner.GetData();

					rEvent.m_pCurTarget = ppTarget[t];
					for( i = 0; i < nCount; i++ )
					{
						if( CALL_TYPE_ONCE == _CheckCallType( mapListenerToCallCount, *ppItem[i] ) )
							continue;

						ppItem[i]->HandleEvent( rEvent );
					}

					arpListerner.RemoveAll();
				}
			}
		}
	}

	rEvent.Release();
}

void CGEventTarget::DispatchEvent( CGEvent& rEvent )
{
	INT nIndex = IsEventLocked( rEvent.m_pctszEventType, rEvent.m_pEventTarget );
	if( -1 != nIndex )
	{
		nIndex = FindPendingEvent( rEvent.m_pctszEventType, rEvent.m_pEventTarget );
		if( -1 == nIndex )
			AddPendingEvent( rEvent );
	
		return;
	}

	CGEvent* pEvent = GetPendingEvent( rEvent.m_pctszEventType, nIndex, rEvent.m_pEventTarget );
	if( pEvent )
	{
		ASSERT( m_parpEventPending );
		m_parpEventPending->RemoveAt( nIndex );
		pEvent->Release( TRUE );

		_DeleteIfEmpty( m_parpEventPending );
	}

	rEvent.AddRef();
	DispatchEventNow( rEvent );
}

INT CGEventTarget::GetDispatchPath( CPtrArray& rarpPath )
{
	rarpPath.Add( this );
	return rarpPath.GetSize(); 
}

INT CGEventTarget::IsEventLocked( LPCTSTR pctszType, CGEventTarget* pTarget/*= NULL*/, void** ppsLockStruct /*= NULL*/ )
{
	if( ppsLockStruct )
		*ppsLockStruct = NULL;

	if( NULL == m_parpEventLock )
		return -1;

	INT nCount = m_parpEventLock->GetSize();
	SGEventLock** ppsLockEvent = (SGEventLock**)m_parpEventLock->GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppsLockEvent[i]->pctszType == pctszType &&
			(NULL == ppsLockEvent[i]->pTarget || NULL == pTarget || ppsLockEvent[i]->pTarget == pTarget) )
		{
			if( ppsLockStruct )
				*ppsLockStruct = ppsLockEvent[i];

			return i;
		}
	}

	return -1;
}

INT CGEventTarget::LockEvent( LPCTSTR pctszType, CGEventTarget* pTarget /*= NULL*/ )
{
	SGEventLock* psEventLock;
	INT nIndex = IsEventLocked( pctszType, pTarget, (void**)&psEventLock );
	if( -1 == nIndex )
	{
		if( NULL == m_parpEventLock )
			_Create( m_parpEventLock );

		if( NULL == m_parpEventLock )
			return -1;

		VERIFY( psEventLock = new SGEventLock );
		if( NULL == psEventLock )
			return 0;

		psEventLock->pctszType = pctszType;
		psEventLock->pTarget = pTarget;
		m_parpEventLock->Add( psEventLock );
	}

	return psEventLock->Lock();
}

void CGEventTarget::LockMultipleEvent( LPCTSTR pctszType, ... )
{
	va_list argList;
	va_start( argList, pctszType );

	while( pctszType )
	{
		LockEvent( pctszType );
		pctszType = va_arg( argList, LPCTSTR );
	}
	
	va_end( argList );
}

INT CGEventTarget::UnlockEvent( LPCTSTR pctszType, CGEventTarget* pTarget /*= NULL*/ )
{
	SGEventLock* psEventLock;
	INT nIndex = IsEventLocked( pctszType, pTarget, (void**)&psEventLock );
	if( -1 == nIndex )
		return 0;

	INT nLock = psEventLock->Unlock();

	// Is Lock Event is temp
	if( 0 == psEventLock->nLockCount )
	{
		ASSERT( m_parpEventLock );
		m_parpEventLock->RemoveAt( nIndex );
		delete psEventLock;
		_DeleteIfEmpty( m_parpEventLock );

		DispatchPendingEvent( pctszType );
	}

	return nLock;
}

void CGEventTarget::UnlockMultipleEvent( LPCTSTR pctszType, ... )
{
	va_list argList;
	va_start( argList, pctszType );

	while( pctszType )
	{
		UnlockEvent( pctszType );
		pctszType = va_arg( argList, LPCTSTR );
	}
	
	va_end( argList );
}

CGEvent* CGEventTarget::GetPendingEvent( LPCTSTR pctszType, INT& rnIndex, CGEventTarget* pTarget /*= NULL*/, SCompareEventPending* pCompare /*= NULL*/ ) const
{
	rnIndex = FindPendingEvent( pctszType, pTarget, pCompare );
	if( -1 == rnIndex )
		return NULL;

	ASSERT( m_parpEventPending );
	CGEvent* pEvent = (CGEvent*)m_parpEventPending->GetAt( rnIndex );
	return pEvent;
}

CGEvent* CGEventTarget::GetPendingEvent( LPCTSTR pctszType, CGEventTarget* pTarget /*= NULL*/, SCompareEventPending* pCompare /*= NULL*/ ) const
{
	INT nIndex = FindPendingEvent( pctszType, pTarget, pCompare );
	if( -1 == nIndex )
		return NULL;

	ASSERT( m_parpEventPending );
	CGEvent* pEvent = (CGEvent*)m_parpEventPending->GetAt( nIndex );
	return pEvent;
}

INT	CGEventTarget::FindPendingEvent( LPCTSTR pctszType, CGEventTarget* pTarget /*= NULL*/, SCompareEventPending* pCompare /*= NULL*/ ) const
{
	if( NULL == m_parpEventPending )
		return -1;

	if( pCompare && NULL == pCompare->pfnCompare )
		pCompare = NULL;

	INT nCount = m_parpEventPending->GetSize();
	CGEvent** ppEvent = (CGEvent**)m_parpEventPending->GetData();
	for( INT i = 0; i < nCount; i++ )
		if( ppEvent[i]->GetType() == pctszType && 
			(NULL == pTarget || ppEvent[i]->m_pEventTarget == pTarget) &&
			(NULL == pCompare || (*pCompare->pfnCompare)( ppEvent[i], pCompare->pParam )))
			return i;

	return -1;
}

INT	CGEventTarget::FindPendingEvent( CGEvent& rEvent ) const
{
	if( NULL == m_parpEventPending )
		return -1;

	INT nCount = m_parpEventPending->GetSize();
	CGEvent** ppEvent = (CGEvent**)m_parpEventPending->GetData();
	for( INT i = 0; i < nCount; i++ )
		if( ppEvent[i]->m_pctszEventType == rEvent.m_pctszEventType &&
			rEvent.m_pEventTarget == ppEvent[i]->m_pEventTarget )
			return i;

	return -1;
}

BOOL CGEventTarget::AddPendingEvent( CGEvent& rEvent )
{
	if( NULL == m_parpEventPending )
		_Create( m_parpEventPending );

	if( NULL == m_parpEventPending )
		return FALSE;

	CGEvent* pEvent = GetPendingEvent( rEvent.m_pctszEventType, rEvent.m_pEventTarget );
	if( pEvent )
		return TRUE;

	m_parpEventPending->Add( &rEvent );
	rEvent.AddRef();
	return TRUE;
}

void CGEventTarget::RemoveAllPendingEvent()
{
	if( NULL == m_parpEventPending )
		return;
		
	INT nCount = m_parpEventPending->GetSize();
	CGEvent** ppEvent = (CGEvent**)m_parpEventPending->GetData();
	for( INT i = 0 ; i < nCount; i++ )
		ppEvent[i]->Release();

	_Delete( m_parpEventPending );
}

INT CGEventTarget::DispatchPendingEvent( LPCTSTR pctszType /*= NULL*/ )
{
	if( NULL == m_parpEventPending )
		return 0;

	CPtrArray arpPendingList;
	INT nCount = m_parpEventPending->GetSize();
	CGEvent** ppEvent = (CGEvent**)m_parpEventPending->GetData();
	INT i;
	for( i = nCount - 1; i >= 0; i-- )
	{
		if( NULL == pctszType || (pctszType && pctszType == ppEvent[i]->GetType()) )
		{
			arpPendingList.Add( ppEvent[i] );
			ppEvent[i] = NULL;
		}
	}

	INT nPendingSize = arpPendingList.GetSize();
	if( 0 == nPendingSize )
		return 0;

	for( i = 0; i < nCount; i++ )
	{
		if( NULL == ppEvent[i] )
		{
			if( i + 1 < nCount )
				memcpy( ppEvent + i, ppEvent + i + 1, sizeof(CGEvent*) * (nCount - i - 1) );

			i--;
			nCount--;
		}
	}

	m_parpEventPending->SetSize( nCount );
	_DeleteIfEmpty( m_parpEventPending );

	INT nDispatched = 0;
	nCount = arpPendingList.GetSize();
	ppEvent = (CGEvent**)arpPendingList.GetData();
	for( i = 0; i < nCount; i++ )
	{
		DispatchEventNow( *ppEvent[i] );
		nDispatched++;
	}

	return nDispatched;
}

///////////////////////////////////////////////////////////////////////////////////////////////////}
CGEvent::CGEvent() :
	m_gTimeStamp( GetTickCount() )
{
	m_pctszEventType = NULL;
	m_pEventTarget = NULL;

	m_pCurTarget = NULL;
	m_usnPhase = AT_TARGET;

	m_bBubbles = FALSE;
	m_bCancelable = FALSE;
	time( (time_t*)&m_gTimeStamp );

	m_bPreventDefault = FALSE;
	m_bStopPropagation = FALSE;
}

void CGEvent::StopPropagation()
{
	m_bStopPropagation = TRUE;
}

void CGEvent::PreventDefault()
{
	if( m_bCancelable )
		m_bPreventDefault = TRUE;
}

void CGEvent::InitEvent( LPCTSTR pctszType,
						 BOOL bCanBubble,
						 BOOL bCancelable )
{
	m_pctszEventType = pctszType;
	m_bBubbles = bCanBubble;
	m_bCancelable = bCancelable;
}

///////////////////////////////////////////////////////////////////////////////////////////////////}
LPCTSTR CGZoomEvent::EVENT = _T("Resize_Event");

///////////////////////////////////////////////////////////////////////////////////////////////////}
LPCTSTR CGScrollEvent::EVENT = _T("Scroll_Event");
CGZoomEvent::CGZoomEvent() {
	m_bBubbles = TRUE; }

///////////////////////////////////////////////////////////////////////////////////////////////////}
LPCTSTR CGMutationEvent::DOMSubTreeModified				= _T("DOMSubTreeModified");
LPCTSTR CGMutationEvent::DOMNodeInserted				= _T("DOMNodeInserted");
LPCTSTR CGMutationEvent::DOMNodeRemoved					= _T("DOMNodeRemoved");
LPCTSTR CGMutationEvent::DOMNodeRemovedFromDocument		= _T("DOMNodeRemovedFromDocument");
LPCTSTR CGMutationEvent::DOMNodeInsertedIntoDocument	= _T("DOMNodeInsertedIntoDocument");
LPCTSTR CGMutationEvent::DOMAttrModified				= _T("DOMAttrModified");
LPCTSTR CGMutationEvent::DOMCharacterDataModified		= _T("DOMCharacterDataModified");
CGMutationEvent::CGMutationEvent()
{
	m_pRelatedNode = NULL;
	m_pvPreviousValue = NULL;
	m_pvNewValue = NULL;
}

CGMutationEvent::~CGMutationEvent()
{}

void CGMutationEvent::InitEvent( LPCTSTR		pctszType,
								 BOOL			bCanBubble,
								 BOOL			bCancelable,
								 CGEventNode*	pRelatedNode,
								 void*			pvPreviousValue,
								 void*			pvNewValue,
								 LPCTSTR		ptcszAttrName,
								 INT			nAttrChange )
{
	CGEvent::InitEvent( pctszType, bCanBubble, bCancelable );
	m_pRelatedNode = pRelatedNode;
	m_pvPreviousValue = pvPreviousValue;
	m_pvNewValue = pvNewValue;
	m_cszAttrName = ptcszAttrName;
	m_nAttrChange = nAttrChange;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CGUIEvent::CGUIEvent()
{
	m_pvView = NULL;
	m_lDetail = 0;
}

void CGUIEvent::InitEvent(	LPCTSTR pctszType,
							BOOL	bCanBubble,
							BOOL	bCancelable,
							void*	pvView,
							long    lDetail )
{
	CGEvent::InitEvent( pctszType, bCanBubble, bCancelable );
	m_pvView = pvView;
	m_lDetail = lDetail;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
LPCTSTR	CGMouseEvent::click		 = _T("click");
LPCTSTR	CGMouseEvent::mousedown  = _T("mousedown");
LPCTSTR	CGMouseEvent::mouseup	 = _T("mouseup");
LPCTSTR	CGMouseEvent::mousemove	 = _T("mousemove");
LPCTSTR	CGMouseEvent::mouseover	 = _T("mouseover");
LPCTSTR	CGMouseEvent::mouseout	 = _T("mouseout");
LPCTSTR	CGMouseEvent::mousewheel = _T("mousewheel");

CGMouseEvent::CGMouseEvent()
{
	m_lScreenX = 0;
	m_lScreenY = 0;
	m_lClientX = 0;
	m_lClientY = 0;
	m_bCtrlKey = FALSE;
	m_bShiftKey = FALSE;
	m_bAltKey = FALSE;
	m_bMetaKey = FALSE;
	m_usnButton = -1;
	m_pvRelatedTarget = NULL;
}

void CGMouseEvent::InitEvent(	LPCTSTR pctszType,
								BOOL	bCanBubble,
								BOOL	bCancelable,
								void*	pvView,
								long    lDetail,
								long	lScreenX,
								long	lScreenY,
								long	lClientX,
								long	lClientY,
								BOOL	bCtrlKey,
								BOOL	bShiftKey,
								BOOL	bAltKey,
								BOOL	bMetaKey,
								USHORT	usnButton,
								void*	pvRelatedTarget )
{
	CGUIEvent::InitEvent( pctszType, bCanBubble, bCancelable, pvView, lDetail );
	m_lScreenX = lScreenX;
	m_lScreenY = lScreenY;
	m_lClientX = lClientX;
	m_lClientY = lClientY;
	m_bCtrlKey = bCtrlKey;
	m_bShiftKey = bShiftKey;
	m_bAltKey = bAltKey;
	m_bMetaKey = bMetaKey;
	m_usnButton = usnButton;
	m_pvRelatedTarget = pvRelatedTarget;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
LPCTSTR	CGKeyboardEvent::keydown = _T("keydown");
LPCTSTR	CGKeyboardEvent::keyup	 = _T("keyup");

CGKeyboardEvent::CGKeyboardEvent()
{
	m_ulKeyIdentifier = 0;
	m_ulKeyLocation	  = 0;
	m_bCtrlKey        = FALSE;
	m_bShiftKey		  = FALSE;
	m_bAltKey         = FALSE;
	m_bMetaKey        = FALSE;
}

BOOL CGKeyboardEvent::GetModifierState( ULONG ulKey )
{
	ASSERT( FALSE );
	return FALSE;
}

void CGKeyboardEvent::InitEvent(	LPCTSTR pctszType,
									BOOL	bCanBubble,
									BOOL	bCancelable,
									void*	pvView,
									long    lDetail,
									BOOL	bCtrlKey,
									BOOL	bShiftKey,
									BOOL	bAltKey,
									BOOL	bMetaKey,
									ULONG	ulKeyIdentifier,
									ULONG	ulKeyLocation )
{
	CGUIEvent::InitEvent( pctszType, bCanBubble, bCancelable, pvView, lDetail );
	m_bCtrlKey = bCtrlKey;
	m_bShiftKey = bShiftKey;
	m_bAltKey = bAltKey;
	m_bMetaKey = bMetaKey;
	m_ulKeyIdentifier = ulKeyIdentifier;
	m_ulKeyLocation = ulKeyLocation;
}
