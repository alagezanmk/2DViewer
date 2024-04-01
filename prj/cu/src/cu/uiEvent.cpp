#include "stdafx.h"
#include <cu\uiEvent.h>
#include <cu\uiState.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
CUIEvent::CUIEvent() {
	m_pctszEventType = NULL; }

void CUIEvent::InitEvent( LPCTSTR pctszEventType ) {
	m_pctszEventType = pctszEventType; }

LPCTSTR CUIEvent::GetEventType( UINT nMessage ) {
	return NULL; }

///////////////////////////////////////////////////////////////////////////////////////////////////
LPCTSTR CMouseEvent::mousewheel = _T("mousewheel");
LPCTSTR CMouseEvent::mousemove = _T("mousemove");

LPCTSTR CMouseEvent::lbuttondown = _T("lbuttondown");
LPCTSTR CMouseEvent::lbuttonup = _T("lbuttonup");
LPCTSTR CMouseEvent::lbuttondblclk = _T("lbuttondblclk");

LPCTSTR CMouseEvent::rbuttondown = _T("rbuttondown");
LPCTSTR CMouseEvent::rbuttonup = _T("rbuttondblclk");
LPCTSTR CMouseEvent::rbuttondblclk = _T("rbuttondblclk");

LPCTSTR CMouseEvent::mbuttondown = _T("mbuttondown");
LPCTSTR CMouseEvent::mbuttonup = _T("mbuttonup");
LPCTSTR CMouseEvent::mbuttondblclk = _T("mbuttondblclk");

CMouseEvent::CMouseEvent()
{
	m_ptClient.x = 0;
	m_ptClient.y = 0;

	m_ptScreen.x = 0;
	m_ptScreen.y = 0;
	m_zDelta = 0;

	m_bCtrlKey = FALSE;
	m_bShiftKey = FALSE;
	m_bAltKey = FALSE;
	m_bMetaKey = FALSE;

	m_bLButton = FALSE;
	m_bRButton = FALSE;
	m_bMButton = FALSE;
}

LPCTSTR CMouseEvent::GetEventType( UINT nMessage )
{
	LPCTSTR pctszEventType = NULL;
	switch( nMessage )
	{
	case WM_MOUSEWHEEL:
		pctszEventType = CMouseEvent::mousewheel;
		break;

	case WM_MOUSEMOVE:
		pctszEventType = CMouseEvent::mousemove;
		break;

	case WM_LBUTTONDOWN:
		pctszEventType = CMouseEvent::lbuttondown;
		break;

	case WM_RBUTTONDOWN:
		pctszEventType = CMouseEvent::rbuttondown;
		break;

	case WM_MBUTTONDOWN:
		pctszEventType = CMouseEvent::mbuttondown;
		break;

	case WM_LBUTTONUP:
		pctszEventType = CMouseEvent::lbuttonup;
		break;

	case WM_RBUTTONUP:
		pctszEventType = CMouseEvent::rbuttonup;
		break;

	case WM_MBUTTONUP:
		pctszEventType = CMouseEvent::mbuttonup;
		break;

	case WM_LBUTTONDBLCLK:
		pctszEventType = CMouseEvent::lbuttondblclk;
		break;

	case WM_RBUTTONDBLCLK:
		pctszEventType = CMouseEvent::rbuttondblclk;
		break;

	case WM_MBUTTONDBLCLK:
		pctszEventType = CMouseEvent::mbuttondblclk;
		break;
	}

	return pctszEventType;
}

void CMouseEvent::InitEvent( HWND hWnd, UINT nMessage )
{
	LPCTSTR pctszEventType = GetEventType( nMessage );
	if( NULL == pctszEventType )
	{
		ASSERT( FALSE );
		return;	// Unkown
	}

	CUIEvent::InitEvent( pctszEventType );

	GetCursorPos( &m_ptScreen );
	m_ptClient = m_ptScreen;
	if( hWnd && IsWindow( hWnd ) )
		ScreenToClient( hWnd, &m_ptClient );

	m_bCtrlKey  = SKbdUIState::IsCtrl_();
	m_bShiftKey = SKbdUIState::IsShift_();
	m_bAltKey   = SKbdUIState::IsAlt_();

	m_bLButton = SMouseUIState::IsLButton_();
	m_bRButton = SMouseUIState::IsRButton_();
	m_bMButton = SMouseUIState::IsMButton_();

	// Initialize MSG member
	m_sMsg.hwnd = hWnd;
	m_sMsg.message = nMessage;
	m_sMsg.pt = m_ptScreen;
	m_sMsg.time = GetTickCount();
	m_sMsg.lParam = MAKELONG( m_ptClient.x, m_ptClient.y );
	m_sMsg.wParam = (m_bLButton ?MK_LBUTTON :0) |
					(m_bRButton ?MK_RBUTTON :0) |
					(m_bMButton ?MK_MBUTTON :0) |
					(m_bShiftKey ?MK_SHIFT   :0) |
					(m_bCtrlKey  ?MK_CONTROL :0);
	
	m_sMsg.wParam = MAKELONG( m_sMsg.wParam, m_zDelta );
}

void CMouseEvent::InitEvent( HWND hWnd, UINT nMessage, const POINT& rptClient, INT nFlags /*= 0*/, short zDelta /*= 0*/ )
{
	LPCTSTR pctszEventType = GetEventType( nMessage );
	if( NULL == pctszEventType )
	{
		ASSERT( FALSE );
		return;	// Unkown
	}

	CUIEvent::InitEvent( pctszEventType );

	m_zDelta = zDelta;
	m_ptClient = rptClient;
	m_ptScreen = rptClient;
	if( hWnd && IsWindow( hWnd ) )
		ClientToScreen( hWnd, &m_ptScreen );

	m_bCtrlKey  = 0 != (MK_CONTROL & nFlags);
	m_bShiftKey = 0 != (MK_SHIFT & nFlags);
	m_bAltKey   = SKbdUIState::IsAlt_();

	m_bLButton = 0 != (MK_LBUTTON & nFlags);
	m_bRButton = 0 != (MK_RBUTTON & nFlags);
	m_bMButton = 0 != (MK_MBUTTON & nFlags);

	// Initialize MSG member
	m_sMsg.hwnd = hWnd;
	m_sMsg.message = nMessage;
	m_sMsg.pt = m_ptScreen;
	m_sMsg.time = GetTickCount();
	m_sMsg.lParam = MAKELONG( m_ptClient.x, m_ptClient.y );
	m_sMsg.wParam = MAKELONG( nFlags, zDelta );
}

void CMouseEvent::InitEvent( const MSG& rsMsg )
{
	LPCTSTR pctszEventType = GetEventType( rsMsg.message );
	if( NULL == pctszEventType )
	{
		ASSERT( FALSE ); // Unknown type
		return;
	}

	CUIEvent::InitEvent( pctszEventType );
	m_sMsg = rsMsg;

	m_ptClient = CPoint( LOWORD(rsMsg.lParam), HIWORD(rsMsg.lParam) );
	m_ptScreen = rsMsg.pt;
	if( WM_MOUSEWHEEL == rsMsg.message )
		m_zDelta = HIWORD(rsMsg.wParam);

	m_bCtrlKey  = 0 != (MK_CONTROL & rsMsg.wParam);
	m_bShiftKey = 0 != (MK_SHIFT & rsMsg.wParam);
	m_bAltKey   = SKbdUIState::IsAlt_();

	m_bLButton = 0 != (MK_LBUTTON & rsMsg.wParam);
	m_bRButton = 0 != (MK_RBUTTON & rsMsg.wParam);
	m_bMButton = 0 != (MK_MBUTTON & rsMsg.wParam);

	m_sMsg = rsMsg;
}

void CMouseEvent::InitEvent( HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam )
{
	LPCTSTR pctszEventType = GetEventType( nMessage );
	if( NULL == pctszEventType )
	{
		ASSERT( FALSE ); // Unknown type
		return;
	}

	CUIEvent::InitEvent( pctszEventType );

	m_ptClient = CPoint( LOWORD(lParam), HIWORD(lParam) );
	if( hWnd && IsWindow( hWnd ) )
	{
		m_ptScreen = m_ptClient;
		ClientToScreen( hWnd, &m_ptScreen );
	}
	else
		GetCursorPos( &m_ptScreen );

	if( WM_MOUSEWHEEL == nMessage )
		m_zDelta = HIWORD(wParam);

	m_bCtrlKey  = 0 != (MK_CONTROL & wParam);
	m_bShiftKey = 0 != (MK_SHIFT & wParam);
	m_bAltKey   = SKbdUIState::IsAlt_();

	m_bLButton = 0 != (MK_LBUTTON & wParam);
	m_bRButton = 0 != (MK_RBUTTON & wParam);
	m_bMButton = 0 != (MK_MBUTTON & wParam);

	// Initialize MSG member
	m_sMsg.hwnd = hWnd;
	m_sMsg.message = nMessage;
	m_sMsg.pt = m_ptScreen;
	m_sMsg.time = GetTickCount();
	m_sMsg.lParam = lParam;
	m_sMsg.wParam = wParam;
}

void CMouseEvent::GetWindowsParameter( UINT& rnFlags, CPoint& rpoint, short* pzDelta /*= NULL*/ ) const
{
	rnFlags = LOWORD(m_sMsg.wParam);

	rpoint.x = LOWORD(m_sMsg.lParam);
	rpoint.y = HIWORD(m_sMsg.lParam);

	if( pzDelta )
	{
		*pzDelta = 0;
		if( CMouseEvent::mousewheel == m_pctszEventType )
			*pzDelta = HIWORD(m_sMsg.wParam);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
LPCTSTR CKbdEvent::keydown = _T("keydown");
LPCTSTR CKbdEvent::keyup = _T("keyup");

CKbdEvent::CKbdEvent()
{
	m_nKey = -1;	// UNKNOWN
	m_nRepCnt = 0;

	m_bCtrlKey = FALSE;
	m_bShiftKey = FALSE;
	m_bAltKey = FALSE;
	m_bMetaKey = FALSE;
}

LPCTSTR CKbdEvent::GetEventType( UINT nMessage )
{
	LPCTSTR pctszEventType = NULL;
	switch( nMessage )
	{
	case WM_KEYDOWN:
		pctszEventType = CKbdEvent::keydown;
		break;

	case WM_KEYUP:
		pctszEventType = CKbdEvent::keyup;
		break;
	}

	return pctszEventType;
}

void CKbdEvent::InitEvent( HWND hWnd, UINT nMessage, UINT nChar )
{
	LPCTSTR pctszEventType = GetEventType( nMessage );
	if( NULL == pctszEventType )
	{
		ASSERT( FALSE );
		return; // Unknown type
	}

	CUIEvent::InitEvent( pctszEventType );

	m_nKey = nChar;
	m_nRepCnt = 0;

	m_bCtrlKey  = SKbdUIState::IsCtrl_();
	m_bShiftKey = SKbdUIState::IsShift_();
	m_bAltKey   = SKbdUIState::IsAlt_();
	m_bMetaKey  = SKbdUIState::IsMeta();

	// Initialize MSG message
	m_sMsg.hwnd = hWnd;
	m_sMsg.message = nMessage;
	m_sMsg.time = GetTickCount();
	m_sMsg.wParam = nChar;
	m_sMsg.lParam = 0;
	GetCursorPos( &m_sMsg.pt );
}

void CKbdEvent::InitEvent( HWND hWnd, UINT nMessage, UINT nChar, UINT nRepCnt, UINT nFlags )
{
	LPCTSTR pctszEventType = GetEventType( nMessage );
	if( NULL == pctszEventType )
	{
		ASSERT( FALSE );
		return; // Unknown type
	}

	CUIEvent::InitEvent( pctszEventType );

	m_nKey = nChar;
	m_nRepCnt = nRepCnt;

	m_bCtrlKey  = SKbdUIState::IsCtrl_();
	m_bShiftKey = SKbdUIState::IsShift_();
	m_bAltKey   = SKbdUIState::IsAlt_();
	m_bMetaKey  = SKbdUIState::IsMeta();

	// Initialize MSG message
	m_sMsg.hwnd = hWnd;
	m_sMsg.message = nMessage;
	m_sMsg.time = GetTickCount();
	m_sMsg.wParam = nChar;
	m_sMsg.lParam = 0;
	GetCursorPos( &m_sMsg.pt );
}

void CKbdEvent::InitEvent( const MSG& rsMsg )
{
	LPCTSTR pctszEventType = GetEventType( rsMsg.message );
	if( NULL == pctszEventType )
	{
		ASSERT( FALSE );
		return; // Unknown type
	}

	CUIEvent::InitEvent( pctszEventType );

	m_nKey = rsMsg.wParam;
	m_nRepCnt = LOWORD(rsMsg.lParam);

	m_bCtrlKey  = SKbdUIState::IsCtrl_();
	m_bShiftKey = SKbdUIState::IsShift_();
	m_bAltKey   = SKbdUIState::IsAlt_();
	m_bMetaKey  = SKbdUIState::IsMeta();

	m_sMsg = rsMsg;
}

void CKbdEvent::InitEvent( HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam )
{
	LPCTSTR pctszEventType = GetEventType( nMessage );
	if( NULL == pctszEventType )
	{
		ASSERT( FALSE );
		return; // Unknown type
	}

	CUIEvent::InitEvent( pctszEventType );

	m_nKey = wParam;
	m_nRepCnt = 0;

	m_bCtrlKey  = SKbdUIState::IsCtrl_();
	m_bShiftKey = SKbdUIState::IsShift_();
	m_bAltKey   = SKbdUIState::IsAlt_();
	m_bMetaKey  = SKbdUIState::IsMeta();

	// Initialize MSG message
	m_sMsg.hwnd = hWnd;
	m_sMsg.message = nMessage;
	m_sMsg.time = GetTickCount();
	m_sMsg.wParam = wParam;
	m_sMsg.lParam = lParam;
	GetCursorPos( &m_sMsg.pt );
}

void CKbdEvent::GetWindowsParameter( UINT& rnChar, UINT& rnRepCnt, UINT& rnFlags ) const
{
	rnChar = m_sMsg.wParam;
	rnRepCnt = LOWORD(m_sMsg.lParam);
	rnFlags = HIWORD(m_sMsg.lParam);
}
