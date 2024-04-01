#ifndef ___G_EVENT__PH___
#define ___G_EVENT__PH___

#include "gObject.h"
#include <gbase\gType.h>
#include "gEventStruct.h"
#include "gMutationEventLink.h"

typedef unsigned __int64 CGTimeStamp;
class CGEventListenerItem;
class CGEvent;
class CGEventTarget;
	class CGEventNode;

struct SGEventLock;

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGEventListener
{
public:
	enum ECallType {
		CALL_TYPE_REPEAT	= 0,
		CALL_TYPE_ONCE		= 1,
		CALL_TYPE_ANY		= 2,
	};

public:
	CGEventListener();

public:
	DECLARE_EVENT_LINK();
	virtual void HandleEvent( CGEvent& rEvent );

	friend CGEventListenerItem;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGEventTarget : public CGEventListener
{
public:
	DECL_BASE_GTPYECLASS_DYNCREATE( CGEventTarget )

	typedef BOOL (*LPFNCompareEvent)( CGEvent* pEvent, void* pParam );
	struct SCompareEventPending {
		LPFNCompareEvent	pfnCompare;
		void*				pParam;
	};

public:
	CGEventTarget();
	overrided ~CGEventTarget();

public:
	BOOL AddEventListener( LPCTSTR pctszType,
						   CGEventListener& rListener,
						   BOOL bUseCapture,
						   INT nCallType = CALL_TYPE_REPEAT );
	BOOL RemoveEventListener( LPCTSTR pctszType,
							  CGEventListener& rListener,
							  BOOL bUseCapture,
							  INT nCallType = CALL_TYPE_REPEAT );

	INT FindEventListerner( LPCTSTR pctszType, 
							const CGEventListener& rListener, 
							BOOL bUseCapture, 
							INT nCallType = CALL_TYPE_REPEAT );

	virtual void DispatchEvent( CGEvent& rEvent );
	virtual void DispatchEventNow( CGEvent& rEvent );
	virtual INT DispatchPendingEvent( LPCTSTR pctszType = NULL );
	virtual INT GetDispatchPath( CPtrArray& arpPath );

	BOOL AddPendingEvent( CGEvent& rEvent );
	INT	FindPendingEvent( CGEvent& rEvent ) const;
	INT	FindPendingEvent( LPCTSTR pctszType, 
						  CGEventTarget* pTarget = NULL, 
						  SCompareEventPending* pCompare = NULL ) const;
	CGEvent* GetPendingEvent( LPCTSTR pctszType, 
							  CGEventTarget* pTarget = NULL, 
							  SCompareEventPending* pCompare = NULL ) const;
	CGEvent* GetPendingEvent( LPCTSTR pctszType, 
							  INT& rnIndex, 
							  CGEventTarget* pTarget = NULL, 
							  SCompareEventPending* pCompare = NULL ) const;

	BOOL IsEventLocked( LPCTSTR pctszType, CGEventTarget* pTarget = NULL, void** ppsLockStruct = NULL );

	INT LockEvent( LPCTSTR pctszType, CGEventTarget* pTarget = NULL );
	void LockMultipleEvent( LPCTSTR pctszType, ... );

	INT UnlockEvent( LPCTSTR pctszType, CGEventTarget* pTarget = NULL );
	void UnlockMultipleEvent( LPCTSTR pctszType, ... );	

	void SetEventUpLink( CGEventTarget* pLink );

protected:
	INT GetEventListerner( CPtrArray& rarpListerner, LPCTSTR pctszType, BOOL bUseCapture, INT nCallType = CALL_TYPE_REPEAT );
	void RemoveAllEventListener();
	void RemoveAllPendingEvent();

protected:
	CPtrArray*		m_parpListener;
	CPtrArray*		m_parpEventPending;
	CPtrArray*		m_parpEventLock;
	CGEventTarget*	m_pEventUpLink;
};

inline void CGEventTarget::SetEventUpLink( CGEventTarget* pLink ) {
	m_pEventUpLink = pLink; }

///////////////////////////////////////////////////////////////////////////////////////////////////}
class CU_EXT_CLASS CGEvent : public CGObject
{
public:
	/// PhaseType
	enum {	CAPTURING_PHASE = 1,
			AT_TARGET		= 2,
			BUBBLING_PHASE	= 3, };
public:
	CGEvent();

	LPCTSTR GetType() const;
	LPCTSTR GetTypeName() const;

	CGEventTarget* GetTarget();
	const CGEventTarget* GetTarget() const;

	CGEventTarget* GetCurrentTarget();
	const CGEventTarget* GetCurrentTarget() const;
	unsigned short GetEventPhase() const;

	BOOL GetPreventDefault() const;

	BOOL GetBubbles() const;
	BOOL GetCancelable() const;
	CGTimeStamp GetTimeStamp() const;

	void StopPropagation();
	void PreventDefault();
	void InitEvent( LPCTSTR pctszType,
					BOOL bCanBubble,
					BOOL bCancelable );

protected:
	LPCTSTR				 m_pctszEventType;
	CGEventTarget*		 m_pEventTarget;

	BOOL				 m_bBubbles;
	BOOL				 m_bCancelable;
	CGTimeStamp	const	 m_gTimeStamp;

	CGEventTarget*			m_pCurTarget;
	unsigned short		 m_usnPhase;

	BOOL				 m_bPreventDefault;
	BOOL				 m_bStopPropagation;
	friend class CGEventTarget;
};

inline LPCTSTR CGEvent::GetType() const {
	return m_pctszEventType; }

inline LPCTSTR CGEvent::GetTypeName() const {
	return m_pctszEventType; }

inline CGEventTarget* CGEvent::GetTarget() {
	return m_pEventTarget; }

inline const CGEventTarget* CGEvent::GetTarget() const {
	return m_pEventTarget; }

inline CGEventTarget* CGEvent::GetCurrentTarget() {
	return m_pCurTarget; }

inline const CGEventTarget* CGEvent::GetCurrentTarget() const {
	return m_pCurTarget; }

inline unsigned short CGEvent::GetEventPhase() const {
	return m_usnPhase; }

inline BOOL CGEvent::GetPreventDefault() const {
	return m_bPreventDefault; }

inline BOOL CGEvent::GetBubbles() const {
	return m_bBubbles; }

inline BOOL CGEvent::GetCancelable() const {
	return m_bCancelable; }

inline CGTimeStamp CGEvent::GetTimeStamp() const {
	return m_gTimeStamp; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGZoomEvent : public CGEvent
{
public:
	static LPCTSTR EVENT;

public:
	CGZoomEvent();
	
	const GRectF& GetZoomRectScreen() const;

	float GetPreviousAspectRatio() const;
	float GetAspectRatio() const;

	float GetPreviousScale() const;
	float GetPreviousScaleX() const;
	float GetPreviousScaleY() const;
	void GetPreviousScale( FLOAT& rX, FLOAT& rY ) const;

	float GetScale() const;
	float GetScaleX() const;
	float GetScaleY() const;
	void GetScale( FLOAT& rX, FLOAT& rY ) const;

	const GPointF& GetPreviousTranslate() const;
	const GPointF& GetTranslate() const;

protected:
	CGRectF		m_grctfZoom;
	FLOAT		m_fPrevAspectRatio;
	FLOAT		m_fAspectRatio;

	FLOAT		m_fPrevScale;
	FLOAT		m_fScale;
	CGPointF	m_gptfPrevTranslate;
	CGPointF	m_gptfTranslate;

	friend CGEvent;
};

inline const GRectF& CGZoomEvent::GetZoomRectScreen() const {
	return m_grctfZoom; }

inline float CGZoomEvent::GetPreviousAspectRatio() const {
	return m_fPrevAspectRatio; }

inline float CGZoomEvent::GetAspectRatio() const {
	return m_fAspectRatio; }

inline float CGZoomEvent::GetPreviousScale() const {
	return m_fPrevScale; }

inline float CGZoomEvent::GetPreviousScaleX() const {
	return m_fPrevScale; }
	
inline float CGZoomEvent::GetPreviousScaleY() const {
	return m_fPrevScale / m_fPrevAspectRatio; }
	
inline void CGZoomEvent::GetPreviousScale( FLOAT& rX, FLOAT& rY ) const {
	rX = m_fPrevScale; rY = m_fPrevScale / m_fPrevAspectRatio; }

inline float CGZoomEvent::GetScale() const {
	return m_fScale; }

inline float CGZoomEvent::GetScaleX() const {
	return m_fScale; }
	
inline float CGZoomEvent::GetScaleY() const {
	return m_fScale / m_fAspectRatio; }
	
inline void CGZoomEvent::GetScale( FLOAT& rX, FLOAT& rY ) const {
	rX = m_fScale; rY = m_fScale / m_fAspectRatio; }

inline const GPointF& CGZoomEvent::GetPreviousTranslate() const {
	return m_gptfPrevTranslate; }

inline const GPointF& CGZoomEvent::GetTranslate() const {
	return m_gptfTranslate; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGScrollEvent : public CGZoomEvent
{
public:
	static LPCTSTR EVENT;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGMutationEvent : public CGEvent
{
public:
	static LPCTSTR	DOMSubTreeModified;
	static LPCTSTR	DOMNodeInserted;
	static LPCTSTR	DOMNodeRemoved;
	static LPCTSTR	DOMNodeInsertedIntoDocument;
	static LPCTSTR	DOMNodeRemovedFromDocument;
	static LPCTSTR	DOMAttrModified;
	static LPCTSTR	DOMCharacterDataModified;

	enum {	MODIFICATION = 1,
			ADDITION	 = 2,
			REMOVAL		 = 3,
	};

public:
	CGMutationEvent();
	overrided ~CGMutationEvent();

	LPCTSTR GetTypeName() const;

	CGEventNode* GetRelatedNode();
	void* GetPreviousValue();
	void* GetNewValue();
	LPCTSTR GetAttrName();
	INT GetAttrChange();

	void InitEvent( LPCTSTR			pctszType,
					BOOL			bCanBubble,
					BOOL			bCancelable,
					CGEventNode*	pRelatedNode,
					void*			pPreviousValue,
					void*			pvNewValue,
					LPCTSTR			ptcszAttrName,
					INT				nAttrChange );

protected:
	CGEventNode*	m_pRelatedNode;
	void*			m_pvPreviousValue;
	void*			m_pvNewValue;
	CString			m_cszAttrName;
	INT				m_nAttrChange;
};

inline CGEventNode* CGMutationEvent::GetRelatedNode() {
	return m_pRelatedNode; }

inline void* CGMutationEvent::GetPreviousValue() {
	return m_pvPreviousValue; }

inline void* CGMutationEvent::GetNewValue() {
	return m_pvNewValue; }

inline LPCTSTR CGMutationEvent::GetAttrName() {
	return m_cszAttrName; }

inline INT CGMutationEvent::GetAttrChange() {
	return m_nAttrChange; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGUIEvent : public CGEvent
{
public:
	CGUIEvent();

	void* GetView();
	long GetDetail();

	void InitEvent( LPCTSTR pctszType,
					BOOL	bCanBubble,
					BOOL	bCancelable,
					void*	pvView,
					long    lDetail );

protected:
	void*	m_pvView;
	long	m_lDetail;
};

inline void* CGUIEvent::GetView() {
	return m_pvView; }

inline long CGUIEvent::GetDetail() {
	return m_lDetail; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGMouseEvent : public CGUIEvent
{
public:
	static LPCTSTR	click;
	static LPCTSTR	mousedown;
	static LPCTSTR	mouseup;
	static LPCTSTR	mousemove;
	static LPCTSTR	mouseover;
	static LPCTSTR	mouseout;
	static LPCTSTR	mousewheel;

	enum {
		BUTTON_NONE		= 0,
		BUTTON_LEFT		= 1,
		BUTTON_RIGHT	= 2,
		BUTTON_MIDDLE	= 3,
	};

public:
	CGMouseEvent();
	void InitEvent( LPCTSTR pctszType,
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
					void*	pvRelatedTarget );

public:
	long	m_lScreenX;
	long	m_lScreenY;
	long	m_lClientX;
	long	m_lClientY;
	BOOL	m_bCtrlKey;
	BOOL	m_bShiftKey;
	BOOL	m_bAltKey;
	BOOL	m_bMetaKey;
	USHORT	m_usnButton;
	void*	m_pvRelatedTarget;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGKeyboardEvent : public CGUIEvent
{
public:
	static LPCTSTR	keydown;
	static LPCTSTR	keyup;

	enum {
		DOM_KEY_LOCATION_STANDARD	= 0x00,
		DOM_KEY_LOCATION_LEFT		= 0x01,
		DOM_KEY_LOCATION_RIGHT		= 0x02,
		DOM_KEY_LOCATION_NUMPAD		= 0x03,
	};

public:
	CGKeyboardEvent();

	BOOL GetModifierState( ULONG ulKey );

	void InitEvent( LPCTSTR pctszType,
					BOOL	bCanBubble,
					BOOL	bCancelable,
					void*	pvView,
					long    lDetail,
					BOOL	bCtrlKey,
					BOOL	bShiftKey,
					BOOL	bAltKey,
					BOOL	bMetaKey,
					ULONG	ulKeyIdentifier,
					ULONG	ulKeyLocation );

public:
	ULONG	m_ulKeyIdentifier;
	ULONG	m_ulKeyLocation;
	BOOL	m_bCtrlKey;
	BOOL	m_bShiftKey;
	BOOL	m_bAltKey;
	BOOL	m_bMetaKey;
};

#endif //!___G_EVENT__PH___