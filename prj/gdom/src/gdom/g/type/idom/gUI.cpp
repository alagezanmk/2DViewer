#include "stdafx.h"
#include <g\type\idom\gUI.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGUI::CGUI() 
{}

CGUI::~CGUI()
{}

UINT CGUI::HitTest( const PointF& rptf ) {
	return HT_NOTHING; }

BOOL CGUI::On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage ) 
{
	::SetCursor( LoadCursor( NULL, IDC_ARROW ) );
	return TRUE;
}

BOOL CGUI::UpdateCursor() 
{
	PointF ptf;
	UINT nHitTest = HitTest( ptf );

	ASSERT( NULL );	// Decide have to pass valid first parameter
	return On_SetCursor( NULL, nHitTest, 0 );
}

BOOL CGUI::InitMouseEvent( CGMouseEvent& rdstEvent, const CMouseEvent& rsrcEvent, void* pvView, void* pvRelatedEventTarget )
{
	LONG lDetail = 0;
	USHORT usnButton;
	LPCTSTR ptszEventType = NULL;
	if( CMouseEvent::mousemove == rsrcEvent.m_pctszEventType )
	{
		ptszEventType = CGMouseEvent::mousemove;
		usnButton = CGMouseEvent::BUTTON_NONE;
	}
	else if( CMouseEvent::mousewheel == rsrcEvent.m_pctszEventType )
	{
		ptszEventType = CGMouseEvent::mousewheel;
		usnButton = CGMouseEvent::BUTTON_NONE;
	}

	else if( CMouseEvent::lbuttondown == rsrcEvent.m_pctszEventType )
	{
		ptszEventType = CGMouseEvent::mousedown;
		usnButton = CGMouseEvent::BUTTON_LEFT;
	}
	else if( CMouseEvent::lbuttonup == rsrcEvent.m_pctszEventType )
	{
		ptszEventType = CGMouseEvent::mouseup;
		usnButton = CGMouseEvent::BUTTON_LEFT;
	}
	else if( CMouseEvent::lbuttondblclk == rsrcEvent.m_pctszEventType )
	{
		lDetail = 2;
		ptszEventType = CGMouseEvent::click;
		usnButton = CGMouseEvent::BUTTON_LEFT;
	}

	else if( CMouseEvent::rbuttondown == rsrcEvent.m_pctszEventType )
	{
		ptszEventType = CGMouseEvent::mousedown;
		usnButton = CGMouseEvent::BUTTON_RIGHT;
	}
	else if( CMouseEvent::rbuttonup == rsrcEvent.m_pctszEventType )
	{
		ptszEventType = CGMouseEvent::mouseup;
		usnButton = CGMouseEvent::BUTTON_RIGHT;
	}
	else if( CMouseEvent::rbuttondblclk == rsrcEvent.m_pctszEventType )
	{
		lDetail = 2;
		ptszEventType = CGMouseEvent::click;
		usnButton = CGMouseEvent::BUTTON_RIGHT;
	}

	else if( CMouseEvent::mbuttondown == rsrcEvent.m_pctszEventType )
	{
		ptszEventType = CGMouseEvent::mousedown;
		usnButton = CGMouseEvent::BUTTON_MIDDLE;
	}
	else if( CMouseEvent::mbuttonup == rsrcEvent.m_pctszEventType )
	{
		ptszEventType = CGMouseEvent::mouseup;
		usnButton = CGMouseEvent::BUTTON_MIDDLE;
	}
	else if( CMouseEvent::mbuttondblclk == rsrcEvent.m_pctszEventType )
	{
		lDetail = 2;
		ptszEventType = CGMouseEvent::click;
		usnButton = CGMouseEvent::BUTTON_MIDDLE;
	}
	else
	{
		ASSERT( FALSE );
		return FALSE;
	}

	rdstEvent.InitEvent( ptszEventType, TRUE, TRUE, pvView, lDetail, 
						 rsrcEvent.m_ptScreen.x, rsrcEvent.m_ptScreen.y, rsrcEvent.m_ptClient.x, rsrcEvent.m_ptClient.y, 
						 rsrcEvent.m_bCtrlKey, rsrcEvent.m_bShiftKey, rsrcEvent.m_bAltKey, rsrcEvent.m_bMetaKey, 
						 usnButton, pvRelatedEventTarget );
	return TRUE;
}

CGMouseEvent* CGUI::CreateMouseEvent( LPCTSTR ptszEventType, void* pvView, UINT nFlags, 
									  CPoint ptScreen, CPoint point, USHORT usnButton, 
									  void* pvRelatedEventTarget )
{
	CGMouseEvent* pgMouseEvent = new CGMouseEvent;
	ASSERT( pgMouseEvent );
	if( NULL == pgMouseEvent )
		return NULL;

	pgMouseEvent->InitEvent( ptszEventType, TRUE, TRUE, pvView, 0, 
							 ptScreen.x, ptScreen.y, point.x, point.y, 
							 FALSE, FALSE, FALSE, FALSE, usnButton, 
							 pvRelatedEventTarget );
	return pgMouseEvent;
}

BOOL CGUI::MouseWheel( const CGMouseEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::MouseMove( const CGMouseEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::LButtonDown( const CGMouseEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::LButtonUp( const CGMouseEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::LButtonDblClk( const CGMouseEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::RButtonDown( const CGMouseEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::RButtonUp( const CGMouseEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::RButtonDblClk( const CGMouseEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::MButtonDown( const CGMouseEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::MButtonUp( const CGMouseEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::MButtonDblClk( const CGMouseEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::InitKeyboardEvent( CGKeyboardEvent& rdstEvent, const CKbdEvent& rsrcEvent, void* pvView )
{
	LPCTSTR ptszEventType;
	if( CKbdEvent::keydown == rsrcEvent.m_pctszEventType )
		ptszEventType = CGKeyboardEvent::keydown;
	else if( CKbdEvent::keyup == rsrcEvent.m_pctszEventType )
		ptszEventType = CGKeyboardEvent::keyup;
	else
	{
		ASSERT( FALSE );
		return FALSE;
	}

	rdstEvent.InitEvent( ptszEventType, TRUE, TRUE, pvView, 0, 
						 rsrcEvent.m_bCtrlKey,  rsrcEvent.m_bShiftKey, 
						 rsrcEvent.m_bAltKey, rsrcEvent.m_bMetaKey,
						 rsrcEvent.m_nKey,
						 CGKeyboardEvent::DOM_KEY_LOCATION_STANDARD );

	return TRUE;
}

CGKeyboardEvent* CGUI::CreateKeyboardEvent(  LPCTSTR ptszEventType, void* pvView, 
											 ULONG	ulKeyIdentifier, 
											 ULONG	ulKeyLocation )
{
	CGKeyboardEvent* pgKbEvent = new CGKeyboardEvent;
	ASSERT( pgKbEvent );
	if( NULL == pgKbEvent )
		return NULL;

	pgKbEvent->InitEvent( ptszEventType, TRUE, TRUE, pvView, 0, 
						  FALSE,  FALSE, FALSE, FALSE,
						  ulKeyIdentifier,
						  ulKeyLocation );
	return pgKbEvent;
}

BOOL CGUI::KeyDown( const CGKeyboardEvent& rEvent ) {
	return FALSE; }

BOOL CGUI::KeyUp( const CGKeyboardEvent& rEvent ) {
	return FALSE; }
