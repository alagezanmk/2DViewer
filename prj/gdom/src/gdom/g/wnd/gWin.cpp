#include "stdafx.h"
#include <g\wnd\gWin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
/// To forward to parent
CGWin::CGWin() {
	m_pUIHook = NULL; }

void CGWin::SetUIHook( CGWin* pUIHook ) {
	m_pUIHook = pUIHook; }

BOOL CGWin::OnMouseWheel( const CMouseEvent& rEvent ) 
{
	if( m_pUIHook )
		return SendToUIHook( rEvent );

	return FALSE;
}

BOOL CGWin::OnMouseMove( const CMouseEvent& rEvent )
{
	if( m_pUIHook )
		return SendToUIHook( rEvent );

	return FALSE;
}

BOOL CGWin::OnLButtonDown( const CMouseEvent& rEvent )
{
	if( m_pUIHook )
		return SendToUIHook( rEvent );

	return FALSE;
}

BOOL CGWin::OnLButtonUp( const CMouseEvent& rEvent )
{
	if( m_pUIHook )
		return SendToUIHook( rEvent );

	return FALSE;
}

BOOL CGWin::OnLButtonDblClk( const CMouseEvent& rEvent )
{
	if( m_pUIHook )
		return SendToUIHook( rEvent );

	return FALSE;
}

BOOL CGWin::OnRButtonDown( const CMouseEvent& rEvent )
{
	if( m_pUIHook )
		return SendToUIHook( rEvent );

	return FALSE;
}

BOOL CGWin::OnRButtonUp( const CMouseEvent& rEvent )
{
	if( m_pUIHook )
		return SendToUIHook( rEvent );

	return FALSE;
}

BOOL CGWin::OnRButtonDblClk( const CMouseEvent& rEvent )
{
	if( m_pUIHook )
		return SendToUIHook( rEvent );

	return FALSE;
}

BOOL CGWin::OnMButtonDown( const CMouseEvent& rEvent )
{
	if( m_pUIHook )
		return SendToUIHook( rEvent );

	return FALSE;
}

BOOL CGWin::OnMButtonUp( const CMouseEvent& rEvent )
{
	if( m_pUIHook )
		return SendToUIHook( rEvent );

	return FALSE;
}

BOOL CGWin::OnMButtonDblClk( const CMouseEvent& rEvent )
{
	if( m_pUIHook )
		return SendToUIHook( rEvent );

	return FALSE;
}

BOOL CGWin::SendToUIHook( const CMouseEvent& rEvent )
{
	if( NULL == m_pUIHook )
		return FALSE;

	// Create a new Event with client point in coordinate space of UIHook window
	CMouseEvent event;

	// Change to Client point in MSG
	MSG msg = rEvent.m_sMsg;
	CPoint point = msg.pt;
	m_pUIHook->ScreenToClient( &point );
	msg.lParam = MAKELONG( point.x, point.y );

	event.InitEvent( msg );

	LPCTSTR pctszEventType = event.m_pctszEventType;
	if( CMouseEvent::mousewheel == pctszEventType )
		return m_pUIHook->OnMouseWheel( event );
	else if( CMouseEvent::mousemove == pctszEventType )
		return m_pUIHook->OnMouseMove( event );

	else if( CMouseEvent::lbuttondown == pctszEventType )
		return m_pUIHook->OnLButtonDown( event );
	else if( CMouseEvent::lbuttonup == pctszEventType )
		return m_pUIHook->OnLButtonUp( event );
	else if( CMouseEvent::lbuttondblclk== pctszEventType )
		return m_pUIHook->OnLButtonDblClk( event );

	else if( CMouseEvent::rbuttondown == pctszEventType )
		return m_pUIHook->OnRButtonDown( event );
	else if( CMouseEvent::rbuttonup == pctszEventType )
		return m_pUIHook->OnRButtonUp( event );
	else if( CMouseEvent::rbuttondblclk== pctszEventType )
		return m_pUIHook->OnRButtonDblClk( event );

	else if( CMouseEvent::mbuttondown == pctszEventType )
		return m_pUIHook->OnMButtonDown( event );
	else if( CMouseEvent::mbuttonup == pctszEventType )
		return m_pUIHook->OnMButtonUp( event );
	else if( CMouseEvent::mbuttondblclk== pctszEventType )
		return m_pUIHook->OnMButtonDblClk( event );

	return FALSE;
}

BOOL CGWin::OnKeyDown( const CKbdEvent& rEvent )
{
	if( m_pUIHook )
		return m_pUIHook->OnKeyDown( rEvent );
	
	return FALSE;
}

BOOL CGWin::OnKeyUp( const CKbdEvent& rEvent )
{
	if( m_pUIHook )
		return m_pUIHook->OnKeyUp( rEvent );
	
	return FALSE;
}