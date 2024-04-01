#include "stdafx.h"
#include <cu\key.win.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

inline BOOL CtrlKeyState() {
	BOOL bControl = GetKeyState( VK_CONTROL ) < 0;
	return bControl; }

inline BOOL AltKeyState() {
	BOOL bAlt = GetKeyState( VK_MENU ) < 0;
	return bAlt; }

inline BOOL ShiftKeyState() {
	BOOL bShift = GetKeyState( VK_SHIFT ) < 0;
	return bShift; }

CU_EXT_DATA SAlxKeyState g_alxKeyState;

/// Checks CONTROL, SHIFT, ALT are not pressed
CU_EXT_API BOOL IsKeyNoShift()
{
	return !g_alxKeyState.bControl && !g_alxKeyState.bShift && !g_alxKeyState.bAlt;
}

/// Checks CONTROL, SHIFT, ALT are pressed
CU_EXT_API BOOL IsKeyAllShift()
{
	return g_alxKeyState.bControl && g_alxKeyState.bShift && g_alxKeyState.bAlt;
}

/// Checks CONTROL Key alone is pressed
CU_EXT_API BOOL IsKeyCtrl()
{
	return g_alxKeyState.bControl && !g_alxKeyState.bShift && !g_alxKeyState.bAlt;
}

/// Checks CONTROL Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyCtrl_()
{
	return g_alxKeyState.bControl;
}

/// Checks CONTROL Key is pressed, SHIFT is not pressed and ALT is pressed or not
CU_EXT_API BOOL IsKeyCtrl_S()
{
	return g_alxKeyState.bControl && !g_alxKeyState.bShift;
}

/// Checks CONTROL Key is pressed, ALT are not pressed and SHIFT is pressed or not
CU_EXT_API BOOL IsKeyCtrl_A()
{
	return g_alxKeyState.bControl && !g_alxKeyState.bAlt;
}

/// Checks CONTROL, SHIFT Key is pressed, and ALT is pressed
CU_EXT_API BOOL IsKeyCtrlS()
{
	return g_alxKeyState.bControl && g_alxKeyState.bShift && !g_alxKeyState.bAlt;
}

/// Checks CONTROL, SHIFT Key is pressed, and ALT is pressed or not pressed
CU_EXT_API BOOL IsKeyCtrlS_()
{
	return g_alxKeyState.bControl && g_alxKeyState.bShift;
}

/// Checks CONTROL, ALT Key is pressed, and SHIFT is pressed
CU_EXT_API BOOL IsKeyCtrlA()
{
	return g_alxKeyState.bControl && g_alxKeyState.bAlt && !g_alxKeyState.bShift;
}

/// Checks CONTROL, ALT Key is pressed, and SHIFT is pressed or not pressed
CU_EXT_API BOOL IsKeyCtrlA_()
{
	return g_alxKeyState.bControl && g_alxKeyState.bAlt;
}

/// Checks SHIFT Key alone is pressed
CU_EXT_API BOOL IsKeyShift()
{
	return g_alxKeyState.bShift && !g_alxKeyState.bControl && !g_alxKeyState.bAlt;
}

/// Checks SHIFT Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyShift_()
{
	return g_alxKeyState.bShift;
}

/// Checks SHIFT Key is pressed, CONTROL is not pressed and ALT is pressed or not
CU_EXT_API BOOL IsKeyShift_C()
{
	return g_alxKeyState.bShift && !g_alxKeyState.bControl;
}

/// Checks SHIFT Key is pressed, ALT are not pressed and CONTROL is pressed or not
CU_EXT_API BOOL IsKeyShift_A()
{
	return g_alxKeyState.bShift && !g_alxKeyState.bAlt;
}

/// Checks SHIFT, CONTROL Key is pressed, and ALT is pressed
CU_EXT_API BOOL IsKeyShiftC()
{
	return g_alxKeyState.bShift && g_alxKeyState.bControl && !g_alxKeyState.bAlt;
}

/// Checks SHIFT, CONTROL Key is pressed, and ALT is pressed or not pressed
CU_EXT_API BOOL IsKeyShiftC_()
{
	return g_alxKeyState.bShift && g_alxKeyState.bControl;
}

/// Checks SHIFT, ALT Key is pressed, and CONTROL is pressed
CU_EXT_API BOOL IsKeyShiftA()
{
	return g_alxKeyState.bShift && g_alxKeyState.bAlt && !g_alxKeyState.bControl;
}

/// Checks SHIFT, ALT Key is pressed, and CONTROL is pressed or not pressed
CU_EXT_API BOOL IsKeyShiftA_()
{
	return g_alxKeyState.bShift && g_alxKeyState.bAlt;
}

/// Checks ALT Key alone is pressed
CU_EXT_API BOOL IsKeyAlt()
{
	return g_alxKeyState.bAlt && !g_alxKeyState.bControl && !g_alxKeyState.bShift;
}

/// Checks ALT Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyAlt_()
{
	return g_alxKeyState.bAlt;
}

/// Checks ALT Key is pressed, CONTROL is not pressed and SHIFT is pressed or not
CU_EXT_API BOOL IsKeyAlt_C()
{
	return g_alxKeyState.bAlt && !g_alxKeyState.bControl;
}

/// Checks ALT Key is pressed, SHIFT are not pressed and CONTROL is pressed or not
CU_EXT_API BOOL IsKeyAlt_S()
{
	return g_alxKeyState.bAlt && !g_alxKeyState.bShift;
}

/// Checks ALT, SHIFT Key is pressed, and CONTROL is pressed
CU_EXT_API BOOL IsKeyAltS()
{
	return g_alxKeyState.bAlt && !g_alxKeyState.bControl && g_alxKeyState.bShift;
}

/// Checks ALT, SHIFT Key is pressed, and CONTROL is pressed or not pressed
CU_EXT_API BOOL IsKeyAltS_()
{
	return g_alxKeyState.bAlt && g_alxKeyState.bShift;
}

/// Checks ALT, CONTROL Key is pressed, and SHIFT is pressed
CU_EXT_API BOOL IsKeyAltC()
{
	return g_alxKeyState.bAlt && g_alxKeyState.bControl && !g_alxKeyState.bShift;
}

/// Checks ALT, CONTROL Key is pressed, and SHIFT is pressed or not pressed
CU_EXT_API BOOL IsKeyAltC_()
{
	return g_alxKeyState.bAlt && g_alxKeyState.bControl;
}

/// Checks LBUTTON Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyLButton_()
{
	return g_alxKeyState.bLButton;
}

/// Checks RBUTTON Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyRButton_()
{
	return g_alxKeyState.bRButton;
}

/// Checks MBUTTON Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyMButton_()
{
	return g_alxKeyState.bMButton;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
class CKeyEventListener
{
public:
	CKeyEventListener();
	INT HandleEvent();

public:
	UINT			m_nChar;
	BOOL			m_bKeyDown;
	PFNKeyEventCB	m_pfnCB;
	void*			m_pUserData;
};

CKeyEventListener::CKeyEventListener()
{
	m_nChar = 0;
	m_bKeyDown = TRUE;
	m_pfnCB = NULL;
	m_pUserData = NULL;
}

INT CKeyEventListener::HandleEvent()
{
	if( m_pfnCB )
		(*m_pfnCB)( m_nChar, m_bKeyDown, m_pUserData );

	return 0;
}

static CPtrArray g_arpKeyEventListener;
static HHOOK g_hKeyHook = NULL;
static void OnKeyDown( UINT nChar, UINT nFlags )
{
	CPtrArray arpKeyEventListener;	// Since g_arpKeyEventListener 
									// may be modified during the event handling
	INT nCount = arpKeyEventListener.GetSize();
	CKeyEventListener** ppListener = (CKeyEventListener**)arpKeyEventListener.GetData();
	for( INT i = nCount - 1; i >= 0; i-- )
	{
		if( ppListener[i]->m_nChar == nChar && TRUE == ppListener[i]->m_bKeyDown )
			ppListener[i]->HandleEvent();
	}
	
	switch( nChar )
	{
	case VK_LWIN:
		g_alxKeyState.bWin = TRUE;
		g_alxKeyState.bLWin = TRUE;
		break;

	case VK_RWIN:
		g_alxKeyState.bWin = TRUE;
		g_alxKeyState.bRWin = TRUE;
		break;

	case VK_APPS:
		g_alxKeyState.bApps = TRUE;
		break;

	case VK_SHIFT:
		g_alxKeyState.bShift = TRUE;
		break;

	case VK_CONTROL:
		g_alxKeyState.bControl = TRUE;
		break;

	case VK_MENU:
		g_alxKeyState.bAlt = TRUE;
		break;

	case VK_LBUTTON:
		g_alxKeyState.bLButton = TRUE;
		break;

	case VK_RBUTTON:
		g_alxKeyState.bRButton = TRUE;
		break;

	case VK_MBUTTON:
		g_alxKeyState.bMButton = TRUE;
		break;

	case VK_SCROLL:
		g_alxKeyState.bScrollLock = TRUE;
		break;

	case VK_NUMLOCK:
		g_alxKeyState.bNumLock = TRUE;
		break;

	case VK_CAPITAL:
		g_alxKeyState.bCapsLock = TRUE;
		break;
	}
}

static void OnKeyUp( UINT nChar, UINT nFlags )
{
	CPtrArray arpKeyEventListener;	// Since g_arpKeyEventListener 
									// may be modified during the event handling
	INT nCount = arpKeyEventListener.GetSize();
	CKeyEventListener** ppListener = (CKeyEventListener**)arpKeyEventListener.GetData();
	for( INT i = nCount - 1; i >= 0; i-- )
	{
		if( ppListener[i]->m_nChar == nChar && FALSE == ppListener[i]->m_bKeyDown )
			ppListener[i]->HandleEvent();
	}

	switch( nChar )
	{
	case VK_LWIN:
		g_alxKeyState.bWin = FALSE;
		g_alxKeyState.bLWin = FALSE;
		break;

	case VK_RWIN:
		g_alxKeyState.bWin = FALSE;
		g_alxKeyState.bRWin = FALSE;
		break;

	case VK_APPS:
		g_alxKeyState.bApps = FALSE;
		break;

	case VK_SHIFT:
		g_alxKeyState.bShift = FALSE;
		break;

	case VK_CONTROL:
		g_alxKeyState.bControl = FALSE;
		break;

	case VK_MENU:
		g_alxKeyState.bAlt = FALSE;
		break;

	case VK_LBUTTON:
		g_alxKeyState.bLButton = FALSE;
		break;

	case VK_RBUTTON:
		g_alxKeyState.bRButton = FALSE;
		break;

	case VK_MBUTTON:
		g_alxKeyState.bMButton = FALSE;
		break;

	case VK_SCROLL:
		g_alxKeyState.bScrollLock = FALSE;
		break;

	case VK_NUMLOCK:
		g_alxKeyState.bNumLock = FALSE;
		break;

	case VK_CAPITAL:
		g_alxKeyState.bCapsLock = FALSE;
		break;
	}
}

static void OnKeyRepeat( UINT nChar, UINT nFlags )
{
}

static LRESULT CALLBACK KbHookProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	LPARAM lTransStateFlag = lParam, // Transition state of key
		   lPrevStateFlag  = lParam; // Prev state of key
	
	if ( (nCode<0) || (HC_NOREMOVE == nCode) )
		return CallNextHookEx( g_hKeyHook, nCode, wParam, lParam );
	
	if ( HC_ACTION == nCode )
	{
		//Unsetting all bits except the 31st bit of lParam
		lTransStateFlag &= 0x80000000;
		
		//Unsetting all bits except the 30th bit of lParam
		lPrevStateFlag  &= 0x40000000;
		
		if( lTransStateFlag && lPrevStateFlag ) // Checking for key up
			OnKeyUp( wParam, lParam );
		else if( !lTransStateFlag && lPrevStateFlag ) //Checking for repeated key press
			OnKeyRepeat( wParam, lParam );
		else if( !lTransStateFlag  && !lPrevStateFlag ) //Checking for key down
			OnKeyDown( wParam, lParam );
	}
	
	return CallNextHookEx( g_hKeyHook, nCode, wParam, lParam );
}

CU_EXT_API BOOL SetKbStatusHook( HINSTANCE hInst )
{
	if( g_hKeyHook )
		return FALSE;

	memset( &g_alxKeyState, 0, sizeof(g_alxKeyState) );
	g_alxKeyState.bControl = CtrlKeyState();
	g_alxKeyState.bShift = ShiftKeyState();
	g_alxKeyState.bAlt = AltKeyState();

	g_hKeyHook = SetWindowsHookEx( WH_KEYBOARD, (HOOKPROC)KbHookProc, 
				                   hInst, GetCurrentThreadId() );
	if( NULL == g_hKeyHook )
		return FALSE;

	return TRUE;
}

CU_EXT_API BOOL ReleaseKbStatusHook()
{
	if( NULL == g_hKeyHook )
		return FALSE;

	UnhookWindowsHookEx( g_hKeyHook );
	g_hKeyHook =  NULL;

	return TRUE;
}

static HHOOK g_hMouseHook = NULL;
static LRESULT CALLBACK MsHookProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( (nCode<0) || (HC_NOREMOVE == nCode) )
		return CallNextHookEx( g_hKeyHook, nCode, wParam, lParam );
	
	if ( HC_ACTION == nCode )
	{
		switch( wParam )
		{
		case WM_LBUTTONDOWN:
			g_alxKeyState.bLButton = TRUE;
			break;

		case WM_LBUTTONUP:
			g_alxKeyState.bLButton = FALSE;
			break;

		case WM_RBUTTONDOWN:
			g_alxKeyState.bRButton = TRUE;
			break;

		case WM_RBUTTONUP:
			g_alxKeyState.bRButton = FALSE;
			break;

		case WM_MBUTTONDOWN:
			g_alxKeyState.bMButton = TRUE;
			break;

		case WM_MBUTTONUP:
			g_alxKeyState.bMButton = FALSE;
			break;
		}

		MOUSEHOOKSTRUCT* psMs = (MOUSEHOOKSTRUCT*)lParam;
		g_alxKeyState.ptCursor = psMs->pt;
	}
	
	return CallNextHookEx( g_hKeyHook, nCode, wParam, lParam );
}

CU_EXT_API BOOL SetMsStatusHook( HINSTANCE hInst )
{
	if( g_hMouseHook )
		return FALSE;

	memset( &g_alxKeyState, 0, sizeof(g_alxKeyState) );
	g_alxKeyState.bLButton = GetKeyState( VK_LBUTTON ) < 0;
	g_alxKeyState.bRButton = GetKeyState( VK_RBUTTON ) < 0;
	g_alxKeyState.bMButton = GetKeyState( VK_MBUTTON ) < 0;

	g_hMouseHook = SetWindowsHookEx( WH_MOUSE, (HOOKPROC)MsHookProc, 
									 hInst, GetCurrentThreadId() );
	if( NULL == g_hMouseHook )
		return FALSE;

	return TRUE;
}

CU_EXT_API BOOL ReleaseMsStatusHook()
{
	if( NULL == g_hMouseHook )
		return FALSE;

	UnhookWindowsHookEx( g_hMouseHook );
	g_hMouseHook =  NULL;

	return TRUE;
}

CU_EXT_API INT FindKeyEventListener( UINT nChar, BOOL bKeyDown, PFNKeyEventCB pfnCB, void* pUserData )
{
	INT nCount = g_arpKeyEventListener.GetSize();
	CKeyEventListener** ppListener = (CKeyEventListener**)g_arpKeyEventListener.GetData();
	for( INT i = nCount - 1; i >= 0; i-- )
	{
		if( ppListener[i]->m_nChar == nChar && ppListener[i]->m_bKeyDown == bKeyDown 
		 && ppListener[i]->m_pUserData == pUserData && ppListener[i]->m_pfnCB == pfnCB )
			return i;
	}

	return -1;
}


CU_EXT_API BOOL AddKeyEventListener( UINT nChar, BOOL bKeyDown, PFNKeyEventCB pfnCB, void* pUserData )
{
	CKeyEventListener* pListener = new CKeyEventListener;
	ASSERT( pListener );
	pListener->m_nChar = nChar;
	pListener->m_pfnCB = pfnCB;
	pListener->m_pUserData = pUserData;
	pListener->m_bKeyDown = bKeyDown;
	g_arpKeyEventListener.Add( pListener );

	return TRUE;
}

CU_EXT_API BOOL RemoveKeyEventListener( UINT nChar, BOOL bKeyDown, PFNKeyEventCB pfnCB, void* pUserData )
{
	INT nIndex = FindKeyEventListener( nChar, bKeyDown, pfnCB, pUserData );
	if( -1 == nIndex )
		return FALSE;	// Not there

	CKeyEventListener* pListener = (CKeyEventListener*)g_arpKeyEventListener.GetAt( nIndex );
	g_arpKeyEventListener.RemoveAt( nIndex );
	delete pListener;

	return TRUE;
}