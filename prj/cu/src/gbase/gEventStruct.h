#ifndef ___G_EVENT_STRUCT__PH___
#define ___G_EVENT_STRUCT__PH___

enum EvtSig
{
	EvtSig_end = 0,     // [marks end of message map]

	EvtSig_vE,			// void (CGEvent&)
	EvtSig_ID_vE,		// void (CGEvent&)	/// Idientifed by ID
	EvtSig_vME,			// void (CGMutationEvent&)
	EvtSig_vZE,			// void (CGZoomEvent&)
	EvtSig_vSE,			// void (CGScrollEvent&)
};

class CGEventListener;
typedef void (CGEventListener::*PEventHandler)();
struct EVENT_LINK_ENTRY
{
	LPCTSTR			pctszEventType;
	UINT			nCode;      // control code or NOTIFY code
	UINT			nID;        // Attribute or control ID 
	UINT			nLastID;    // used for entries specifying a range of Attribture or control id's
	UINT			nSig;		// signature type (action) or pointer to message #
	INT				nPhase;
	PEventHandler	pfn;		// routine to call (or special value)
};

struct EVENT_LINK
{
	const EVENT_LINK* (PASCAL* pfnGetBaseEventLink)();
	const EVENT_LINK_ENTRY* lpEntries;
};

#define DECLARE_EVENT_LINK() \
private: \
	static const EVENT_LINK_ENTRY _eventLinkEntries[]; \
protected: \
	static const EVENT_LINK eventLink; \
	static const EVENT_LINK * PASCAL _GetBaseEventLink(); \
	virtual const EVENT_LINK* GetEventLink() const; 

#define BEGIN_EVENT_LINK(theClass, baseClass)  \
	const EVENT_LINK* PASCAL theClass::_GetBaseEventLink() \
		{ return &baseClass::eventLink; } \
	const EVENT_LINK* theClass::GetEventLink() const \
		{ return &theClass::eventLink; } \
	const EVENT_LINK theClass::eventLink = \
	{ &theClass::_GetBaseEventLink, &theClass::_eventLinkEntries[0] }; \
	const EVENT_LINK_ENTRY theClass::_eventLinkEntries[] = \
	{ 

#define END_EVENT_LINK() \
		{0, 0, 0, 0, EvtSig_end, 0, (PEventHandler)0 } \
	};

#define ON_EVT_PHASE( event, phase, memberFxn )	 \
	{ event, 0, 0, 0, EvtSig_vE, phase, \
			(PEventHandler)(void (CGEventListener::*)(CGEvent&))&memberFxn },

#define ON_EVT( event, memberFxn )	 \
	ON_EVT_PHASE( event, -1, memberFxn )

#define ON_EVT_PHASE_ATTR_MODIFIED( phase, memberFxn )	\
	{ CGMutationEvent::DOMAttrModified, 0, 0, 0, EvtSig_vME, phase, \
			(PEventHandler)(void (CGEventListener::*)(CGMutationEvent&))&memberFxn },

#define ON_EVT_ATTR_MODIFIED( memberFxn )	\
	ON_EVT_PHASE_ATTR_MODIFIED( -1, memberFxn )

#define ON_EVT_PHASE_NODE_LINK_CHANGE( event, phase, memberFxn )	\
	{ event, 0, 0, 0, EvtSig_vME, phase, \
			(PEventHandler)(void (CGEventListener::*)(CGMutationEvent&))&memberFxn },

#define ON_EVT_NODE_LINK_CHANGE( event, memberFxn )	\
	ON_EVT_PHASE_NODE_LINK_CHANGE( event, -1, memberFxn )

#define ON_EVT_PHASE_ZOOM( phase, memberFxn )	\
	{ CGZoomEvent::EVENT, 0, 0, 0, EvtSig_vZE, phase, \
			(PEventHandler)(void (CGEventListener::*)(CGZoomEvent&))&memberFxn },

#define ON_EVT_ZOOM( memberFxn )	\
	ON_EVT_PHASE_ZOOM( -1, memberFxn )

#define ON_EVT_PHASE_SCROLL( phase, memberFxn )	\
	{ CGScrollEvent::EVENT, 0, 0, 0, EvtSig_vSE, phase, \
			(PEventHandler)(void (CGEventListener::*)(CGScrollEvent&))&memberFxn },

#define ON_EVT_SCROLL( memberFxn )	\
	ON_EVT_PHASE_SCROLL( -1, memberFxn )

#endif //!___G_EVENT_STRUCT__PH___