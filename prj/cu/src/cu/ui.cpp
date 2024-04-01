#include "stdafx.h"
#include <cu\ui.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CUI::CUI()
{}

CUI::~CUI()
{}

void CUI::Draw(CDC* pDC)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Cursor and HitTest virtual functions
UINT CUI::HitTest( const CPoint& rpoint ) {
	return HT_NOTHING; }

BOOL CUI::On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage )
{
	::SetCursor( LoadCursor( NULL, IDC_ARROW ) );
	return TRUE;
}

BOOL CUI::UpdateCursor()
{
	CPoint pt;
	GetCursorPos( &pt );

	UINT nHitTest = HitTest( pt );

	ASSERT( NULL ); // Decide how to pass valid first parameter for OnSetCursor
	return On_SetCursor( NULL, nHitTest, 0 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Keyboard virtual functions
BOOL CUI::On_SysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	return FALSE; }

BOOL CUI::On_SysKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	return FALSE; }

BOOL CUI::On_KeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	return FALSE; }

BOOL CUI::On_KeyUp( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	return FALSE; }

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Mouse virtual functions
BOOL CUI::On_MouseWheel( UINT nFlags, short zDelta, CPoint point ) {
	return FALSE; }

BOOL CUI::On_MouseMove( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_LButtonDown( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_LButtonUp( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_LButtonDblClk( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_RButtonDown( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_RButtonUp( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_RButtonDblClk( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_MButtonDown( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_MButtonUp( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_MButtonDblClk( UINT nFlags, CPoint point ) {
	return FALSE; }

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Nc Mouse virtual functions
BOOL CUI::On_NcMouseMove( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_NcLButtonDown( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_NcLButtonUp( UINT nFlags, CPoint point ) {
	return FALSE; }

BOOL CUI::On_NcLButtonDblClk( UINT nFlags, CPoint point ) {
	return FALSE; }

///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CUI::HandleKeyboardEvent( const CKbdEvent& rEvent )
{
	if( CKbdEvent::keydown == rEvent.m_pctszEventType )
		return OnKeyDown( rEvent );
	else if( CKbdEvent::keyup == rEvent.m_pctszEventType )
		return OnKeyUp( rEvent );
	
	return FALSE;
}

BOOL CUI::HandleKeyboardEvent( HWND hWnd, UINT nMessage, UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CKbdEvent event;
	event.InitEvent( hWnd, nMessage, nChar, nRepCnt, nFlags );

	return HandleKeyboardEvent( event );
}

BOOL CUI::HandleKeyboardEvent( HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam )
{
	CKbdEvent event;
	event.InitEvent( hWnd, nMessage, wParam, lParam );

	return HandleKeyboardEvent( event );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Keyboard virtual functions
BOOL CUI::OnSysKeyDown( const CKbdEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnSysKeyUp( const CKbdEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnKeyDown( const CKbdEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnKeyUp( const CKbdEvent& rEvent ) {
	return FALSE; }

///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CUI::HandleMouseEvent( const CMouseEvent& rEvent )
{
	if( CMouseEvent::mousewheel == rEvent.m_pctszEventType )
		return OnMouseWheel( rEvent );

	else if( CMouseEvent::mousemove == rEvent.m_pctszEventType )
		return OnMouseMove( rEvent );

	else if( CMouseEvent::lbuttondown == rEvent.m_pctszEventType )
		return OnLButtonDown( rEvent );
	else if( CMouseEvent::lbuttonup == rEvent.m_pctszEventType )
		return OnLButtonUp( rEvent );
	else if( CMouseEvent::lbuttondblclk == rEvent.m_pctszEventType )
		return OnLButtonDblClk( rEvent );

	else if( CMouseEvent::rbuttondown == rEvent.m_pctszEventType )
		return OnRButtonDown( rEvent );
	else if( CMouseEvent::rbuttonup == rEvent.m_pctszEventType )
		return OnRButtonUp( rEvent );
	else if( CMouseEvent::rbuttondblclk == rEvent.m_pctszEventType )
		return OnRButtonDblClk( rEvent );

	else if( CMouseEvent::mbuttondown == rEvent.m_pctszEventType )
		return OnMButtonDown( rEvent );
	else if( CMouseEvent::mbuttonup == rEvent.m_pctszEventType )
		return OnMButtonUp( rEvent );
	else if( CMouseEvent::mbuttondblclk == rEvent.m_pctszEventType )
		return OnMButtonDblClk( rEvent );
	
	return FALSE;
}

BOOL CUI::HandleMouseEvent( HWND hWnd, UINT nMessage, UINT nFlags, CPoint point, short zDelta /*= 0*/ )
{
	CMouseEvent event;
	event.InitEvent( hWnd, nMessage, point, nFlags, zDelta );

	return HandleMouseEvent( event );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Mouse virtual functions
BOOL CUI::OnMouseWheel( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnMouseMove( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnLButtonDown( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnLButtonUp( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnLButtonDblClk( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnRButtonDown( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnRButtonUp( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnRButtonDblClk( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnMButtonDown( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnMButtonUp( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnMButtonDblClk( const CMouseEvent& rEvent ) {
	return FALSE; }

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Nc Mouse virtual functions
BOOL CUI::OnNcMouseMove( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnNcLButtonDown( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnNcLButtonUp( const CMouseEvent& rEvent ) {
	return FALSE; }

BOOL CUI::OnNcLButtonDblClk( const CMouseEvent& rEvent ) {
	return FALSE; }
