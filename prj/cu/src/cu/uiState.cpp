#include "stdafx.h"
#include <cu\uiState.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
class SBOOLPriv : public NUIState::SBOOL
{
public:
	void operator=( BOOL b ) {
		m_b = b; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class SPOINTPriv : public NUIState::SPOINT
{
public:
	void operator=( POINT pt ) {
		m_pt = pt; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class SCOLORREFPriv : public NUIState::SCOLORREF
{
public:
	void operator=( COLORREF crf ) {
		m_crf = crf; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class SHINSTANCEPriv : public NUIState::SHINSTANCE
{
public:
	void operator=( HINSTANCE hInst ) {
		m_hInst = hInst; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class SHBRUSHPriv : public NUIState::SHBRUSH
{
public:
	void operator=( HBRUSH hbr ) {
		m_hbr = hbr; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class SCStringPriv : public NUIState::SCString
{
public:
	void operator=( LPCTSTR pctsz ) {
		m_csz = pctsz; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class SCWinAppPriv : public NUIState::SCWinApp
{
public:
	void operator=( CWinApp* pApp ) {
		m_pApp = pApp; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class SCMDIFrameWndPriv : public NUIState::SCMDIFrameWnd
{
public:
	void operator=( CMDIFrameWnd* pMainFrm ) {
		m_pMainFrm = pMainFrm; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
NUIState::SCString			SAppState::cszAppFolder;
NUIState::SHINSTANCE		SAppState::hAppInst;
NUIState::SCWinApp			SAppState::pApp;
NUIState::SCMDIFrameWnd		SAppState::pMainFrm;

///////////////////////////////////////////////////////////////////////////////////////////////////
NUIState::SBOOL		SKbdUIState::NumLock;
NUIState::SBOOL		SKbdUIState::ScrollLock;
NUIState::SBOOL		SKbdUIState::CapsLock;
					
NUIState::SBOOL		SKbdUIState::Shift;
NUIState::SBOOL		SKbdUIState::Control;
NUIState::SBOOL		SKbdUIState::Alt;
NUIState::SBOOL		SKbdUIState::Meta;
NUIState::SBOOL		SKbdUIState::Apps;
					
NUIState::SBOOL		SKbdUIState::LMeta;
NUIState::SBOOL		SKbdUIState::RMeta;
					
NUIState::SBOOL		SKbdUIState::LShift;
NUIState::SBOOL		SKbdUIState::LControl;
NUIState::SBOOL		SKbdUIState::LAlt;
					
NUIState::SBOOL		SKbdUIState::RShift;
NUIState::SBOOL		SKbdUIState::RControl;
NUIState::SBOOL		SKbdUIState::RAlt;

///////////////////////////////////////////////////////////////////////////////////////////////////
#define _mShift		 *((SBOOLPriv*)&Shift)
#define _mControl	 *((SBOOLPriv*)&Control)
#define _mAlt		 *((SBOOLPriv*)&Alt)
#define _mApps		 *((SBOOLPriv*)&Apps)
#define _mMeta		 *((SBOOLPriv*)&Meta)

#define _mNumLock	 *((SBOOLPriv*)&NumLock)
#define _mScrollLock *((SBOOLPriv*)&ScrollLock)
#define _mCapsLock	 *((SBOOLPriv*)&CapsLock)

#define _mLMeta		 *((SBOOLPriv*)&LMeta)
#define _mRMeta		 *((SBOOLPriv*)&RMeta)

#define _mLShift	 *((SBOOLPriv*)&LShift)
#define _mLControl	 *((SBOOLPriv*)&LControl)
#define _mLAlt		 *((SBOOLPriv*)&LAlt)

#define _mRShift	 *((SBOOLPriv*)&RShift)
#define _mRControl	 *((SBOOLPriv*)&RControl)
#define _mRAlt		 *((SBOOLPriv*)&RAlt)

///////////////////////////////////////////////////////////////////////////////////////////////////
struct SKbdUIStatePriv : public SKbdUIState
{
public:
public:
	////////////////////////////./////////////////////.//////////////////////////.//////////////////////////
	static INT FindKeyEventListener( UINT nChar, BOOL bKeyDown, SKbdUIState::PFNKeyEventCB pfnCB, void* pUserData );

	////////////////////////////./////////////////////.//////////////////////////.//////////////////////////
	static LRESULT CALLBACK KeyboardHookProc( int nCode, WPARAM wParam, LPARAM lParam );

	static void OnKeyDown( UINT nChar, UINT nFlags );
	static void OnKeyUp( UINT nChar, UINT nFlags );
	static void OnKeyRepeat( UINT nChar, UINT nFlags );

	static BOOL CtrlKeyState() {
		BOOL bControl = GetKeyState( VK_CONTROL ) < 0;
		return bControl; }

	static BOOL AltKeyState() {
		BOOL bAlt = GetKeyState( VK_MENU ) < 0;
		return bAlt; }

	static BOOL ShiftKeyState() {
		BOOL bShift = GetKeyState( VK_SHIFT ) < 0;
		return bShift; }

	static BOOL MetaKeyState() {
		BOOL bMeta = GetKeyState( VK_LWIN ) < 0 || GetKeyState( VK_RWIN ) < 0;
		return bMeta; }

	static void Init4KeyStatus()
	{
		if( NULL == ms_hKeyHook )
		{
			_mControl = CtrlKeyState();
			_mShift   = ShiftKeyState();
			_mAlt     = AltKeyState();
			_mMeta    = MetaKeyState();
		}
	}

public:
	class CKeyEventListener
	{
	public:
		CKeyEventListener();
		INT HandleEvent();

	public:
		UINT						m_nChar;
		BOOL						m_bKeyDown;
		SKbdUIState::PFNKeyEventCB	m_pfnCB;
		void*						m_pUserData;
	};

public:
	static HHOOK		ms_hKeyHook;
	static CPtrArray	ms_arpKeyEventListener;
};

HHOOK		SKbdUIStatePriv::ms_hKeyHook = NULL;
CPtrArray	SKbdUIStatePriv::ms_arpKeyEventListener;

///////////////////////////////////////////////////////////////////////////////////////////////////
SKbdUIStatePriv::CKeyEventListener::CKeyEventListener()
{
	m_nChar = 0;
	m_bKeyDown = TRUE;
	m_pfnCB = NULL;
	m_pUserData = NULL;
}

INT SKbdUIStatePriv::CKeyEventListener::HandleEvent()
{
	if( m_pfnCB )
		(*m_pfnCB)( m_nChar, m_bKeyDown, m_pUserData );

	return 0;
}

void SKbdUIState::ResetKeyState()
{
	/*_mLButton = FALSE;
	_mRButton = FALSE;
	_mMButton = FALSE;*/
	
	_mNumLock = FALSE;
	_mScrollLock = FALSE;
	_mCapsLock = FALSE;
	
	_mShift = FALSE;
	_mControl = FALSE;
	_mAlt = FALSE;
	_mMeta = FALSE;
	_mApps = FALSE;

	_mLShift = FALSE;
	_mLControl = FALSE;
	_mLAlt = FALSE;
	_mLMeta = FALSE;

	_mRShift = FALSE;
	_mRControl = FALSE;
	_mRAlt = FALSE;
	_mRMeta = FALSE;
}

/// Checks CONTROL, SHIFT, ALT are not pressed
BOOL SKbdUIState::IsNoShift()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return !Control && !Shift && !Alt;
}

/// Checks CONTROL, SHIFT, ALT are pressed
BOOL SKbdUIState::IsAllShift()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Control && Shift && Alt;
}

/// Checks CONTROL Key alone is pressed
BOOL SKbdUIState::IsCtrl()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Control && !Shift && !Alt;
}

/// Checks CONTROL Key is pressed. The other shift keys can be pressed or not
BOOL SKbdUIState::IsCtrl_()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Control;
}

/// Checks CONTROL Key is pressed, SHIFT is not pressed and ALT is pressed or not
BOOL SKbdUIState::IsCtrl_S()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Control && !Shift;
}

/// Checks CONTROL Key is pressed, ALT are not pressed and SHIFT is pressed or not
BOOL SKbdUIState::IsCtrl_A()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Control && !Alt;
}

/// Checks CONTROL, SHIFT Key is pressed, and ALT is pressed
BOOL SKbdUIState::IsCtrlS()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Control && Shift && !Alt;
}

/// Checks CONTROL, SHIFT Key is pressed, and ALT is pressed or not pressed
BOOL SKbdUIState::IsCtrlS_()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Control && Shift;
}

/// Checks CONTROL, ALT Key is pressed, and SHIFT is pressed
BOOL SKbdUIState::IsCtrlA()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Control && Alt && !Shift;
}

/// Checks CONTROL, ALT Key is pressed, and SHIFT is pressed or not pressed
BOOL SKbdUIState::IsCtrlA_()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Control && Alt;
}

/// Checks SHIFT Key alone is pressed
BOOL SKbdUIState::IsShift()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Shift && !Control && !Alt;
}

/// Checks SHIFT Key is pressed. The other shift keys can be pressed or not
BOOL SKbdUIState::IsShift_()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Shift;
}

/// Checks SHIFT Key is pressed, CONTROL is not pressed and ALT is pressed or not
BOOL SKbdUIState::IsShift_C()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Shift && !Control;
}

/// Checks SHIFT Key is pressed, ALT are not pressed and CONTROL is pressed or not
BOOL SKbdUIState::IsShift_A()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Shift && !Alt;
}

/// Checks SHIFT, CONTROL Key is pressed, and ALT is pressed
BOOL SKbdUIState::IsShiftC()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Shift && Control && !Alt;
}

/// Checks SHIFT, CONTROL Key is pressed, and ALT is pressed or not pressed
BOOL SKbdUIState::IsShiftC_()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Shift && Control;
}

/// Checks SHIFT, ALT Key is pressed, and CONTROL is pressed
BOOL SKbdUIState::IsShiftA()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Shift && Alt && !Control;
}

/// Checks SHIFT, ALT Key is pressed, and CONTROL is pressed or not pressed
BOOL SKbdUIState::IsShiftA_()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Shift && Alt;
}

/// Checks ALT Key alone is pressed
BOOL SKbdUIState::IsAlt()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Alt && !Control && !Shift;
}

/// Checks ALT Key is pressed. The other shift keys can be pressed or not
BOOL SKbdUIState::IsAlt_()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Alt;
}

/// Checks ALT Key is pressed, CONTROL is not pressed and SHIFT is pressed or not
BOOL SKbdUIState::IsAlt_C()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Alt && !Control;
}

/// Checks ALT Key is pressed, SHIFT are not pressed and CONTROL is pressed or not
BOOL SKbdUIState::IsAlt_S()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Alt && !Shift;
}

/// Checks ALT, SHIFT Key is pressed, and CONTROL is pressed
BOOL SKbdUIState::IsAltS()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Alt && !Control && Shift;
}

/// Checks ALT, SHIFT Key is pressed, and CONTROL is pressed or not pressed
BOOL SKbdUIState::IsAltS_()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Alt && Shift;
}

/// Checks ALT, CONTROL Key is pressed, and SHIFT is pressed
BOOL SKbdUIState::IsAltC()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Alt && Control && !Shift;
}

/// Checks ALT, CONTROL Key is pressed, and SHIFT is pressed or not pressed
BOOL SKbdUIState::IsAltC_()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Alt && Control;
}

/// Checks Meta is pressed
BOOL SKbdUIState::IsMeta()
{
	SKbdUIStatePriv::Init4KeyStatus();
	return Meta;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL SKbdUIState::StartKeyboardHook( HINSTANCE hInst )
{
	if( SKbdUIStatePriv::ms_hKeyHook )
		return FALSE;

	ResetKeyState();
	_mControl = SKbdUIStatePriv::CtrlKeyState();
	_mShift   = SKbdUIStatePriv::ShiftKeyState();
	_mAlt     = SKbdUIStatePriv::AltKeyState();

	SKbdUIStatePriv::ms_hKeyHook = SetWindowsHookEx( WH_KEYBOARD, 
													 (HOOKPROC)SKbdUIStatePriv::KeyboardHookProc, 
													  hInst, GetCurrentThreadId() );
	if( NULL == SKbdUIStatePriv::ms_hKeyHook )
		return FALSE;

	return TRUE;
}

BOOL SKbdUIState::StopKeyboardHook()
{
	if( NULL == SKbdUIStatePriv::ms_hKeyHook )
		return FALSE;

	UnhookWindowsHookEx( SKbdUIStatePriv::ms_hKeyHook );
	SKbdUIStatePriv::ms_hKeyHook =  NULL;

	return TRUE;
}

BOOL SKbdUIState::AddKeyEventListener( UINT nChar, BOOL bKeyDown, PFNKeyEventCB pfnCB, void* pUserData )
{
	INT nIndex = SKbdUIStatePriv::FindKeyEventListener( nChar, bKeyDown, pfnCB, pUserData );
	if( -1 != nIndex )
		return FALSE;	/// Already there

	SKbdUIStatePriv::CKeyEventListener* pListener = new SKbdUIStatePriv::CKeyEventListener;
	ASSERT( pListener );
	pListener->m_nChar = nChar;
	pListener->m_pfnCB = pfnCB;
	pListener->m_pUserData = pUserData;
	pListener->m_bKeyDown = bKeyDown;
	SKbdUIStatePriv::ms_arpKeyEventListener.Add( pListener );

	return TRUE;
}

BOOL SKbdUIState::RemoveKeyEventListener( UINT nChar, BOOL bKeyDown, PFNKeyEventCB pfnCB, void* pUserData )
{
	INT nIndex = SKbdUIStatePriv::FindKeyEventListener( nChar, bKeyDown, pfnCB, pUserData );
	if( -1 == nIndex )
		return FALSE;	/// Not there

	SKbdUIStatePriv::CKeyEventListener* pListener = (SKbdUIStatePriv::CKeyEventListener*)SKbdUIStatePriv::ms_arpKeyEventListener.GetAt( nIndex );
	delete pListener;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
INT SKbdUIStatePriv::FindKeyEventListener( UINT nChar, BOOL bKeyDown, PFNKeyEventCB pfnCB, void* pUserData )
{
	INT nCount = SKbdUIStatePriv::ms_arpKeyEventListener.GetSize();
	CKeyEventListener** ppListener = (CKeyEventListener**)SKbdUIStatePriv::ms_arpKeyEventListener.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppListener[i]->m_nChar == nChar && ppListener[i]->m_bKeyDown == bKeyDown 
		 && ppListener[i]->m_pUserData == pUserData && ppListener[i]->m_pfnCB == pfnCB )
			return i;
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void SKbdUIStatePriv::OnKeyDown( UINT nChar, UINT nFlags )
{
	INT nCount = SKbdUIStatePriv::ms_arpKeyEventListener.GetSize();
	CKeyEventListener** ppListener = (CKeyEventListener**)SKbdUIStatePriv::ms_arpKeyEventListener.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppListener[i]->m_nChar == nChar && TRUE == ppListener[i]->m_bKeyDown )
			ppListener[i]->HandleEvent();
	}
	
	switch( nChar )
	{
	case VK_LWIN:
		_mMeta = TRUE;
		_mLMeta = TRUE;
		break;

	case VK_RWIN:
		_mMeta = TRUE;
		_mRMeta = TRUE;
		break;

	case VK_APPS:
		_mApps = TRUE;
		break;

	case VK_SHIFT:
		_mShift = TRUE;
		break;

	case VK_CONTROL:
		_mControl = TRUE;
		break;

	case VK_MENU:
		_mAlt = TRUE;
		break;

	case VK_SCROLL:
		_mScrollLock = TRUE;
		break;

	case VK_NUMLOCK:
		_mNumLock = TRUE;
		break;

	case VK_CAPITAL:
		_mCapsLock = TRUE;
		break;

/*	case VK_LBUTTON:
		_mLButton = TRUE;
		break;

	case VK_RBUTTON:
		_mRButton = TRUE;
		break;

	case VK_MBUTTON:
		_mMButton = TRUE;
		break;*/
	}
}

void SKbdUIStatePriv::OnKeyUp( UINT nChar, UINT nFlags )
{
	INT nCount = SKbdUIStatePriv::ms_arpKeyEventListener.GetSize();
	CKeyEventListener** ppListener = (CKeyEventListener**)SKbdUIStatePriv::ms_arpKeyEventListener.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppListener[i]->m_nChar == nChar && FALSE == ppListener[i]->m_bKeyDown )
			ppListener[i]->HandleEvent();
	}

	switch( nChar )
	{
	case VK_LWIN:
		_mMeta = FALSE;
		_mLMeta = FALSE;
		break;

	case VK_RWIN:
		_mMeta = FALSE;
		_mRMeta = FALSE;
		break;

	case VK_APPS:
		_mApps = FALSE;
		break;

	case VK_SHIFT:
		_mShift = FALSE;
		break;

	case VK_CONTROL:
		_mControl = FALSE;
		break;

	case VK_MENU:
		_mAlt = FALSE;
		break;

	case VK_SCROLL:
		_mScrollLock = FALSE;
		break;

	case VK_NUMLOCK:
		_mNumLock = FALSE;
		break;

	case VK_CAPITAL:
		_mCapsLock = FALSE;
		break;

/*	case VK_LBUTTON:
		_mLButton = FALSE;
		break;

	case VK_RBUTTON:
		_mRButton = FALSE;
		break;

	case VK_MBUTTON:
		_mMButton = FALSE;
		break;*/
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void SKbdUIStatePriv::OnKeyRepeat( UINT nChar, UINT nFlags )
{}

LRESULT CALLBACK SKbdUIStatePriv::KeyboardHookProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	LPARAM lTransStateFlag = lParam, // Transition state of key
		   lPrevStateFlag  = lParam; // Prev state of key
	
	if ( (nCode<0) || (HC_NOREMOVE == nCode) )
		return CallNextHookEx( ms_hKeyHook, nCode, wParam, lParam );
	
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
	
	return CallNextHookEx( ms_hKeyHook, nCode, wParam, lParam );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
NUIState::SPOINT	SMouseUIState::Cursor;
NUIState::SBOOL		SMouseUIState::LButton;
NUIState::SBOOL		SMouseUIState::RButton;
NUIState::SBOOL		SMouseUIState::MButton;

#define _mCursor	 *((SPOINTPriv*)&Cursor)

#define _mLButton	 *((SBOOLPriv*)&LButton)
#define _mRButton	 *((SBOOLPriv*)&RButton)
#define _mMButton	 *((SBOOLPriv*)&MButton)

#define _mMeta		 *((SBOOLPriv*)&Meta)
#define _mLMeta		 *((SBOOLPriv*)&LMeta)
#define _mRMeta		 *((SBOOLPriv*)&RMeta)

///////////////////////////////////////////////////////////////////////////////////////////////////
struct SMouseUIStatePriv : public SMouseUIState
{
public:
	////////////////////////////./////////////////////.//////////////////////////.//////////////////////////
	static LRESULT CALLBACK MouseHookProc( int nCode, WPARAM wParam, LPARAM lParam );

	static BOOL LButtonKeyState() {
		BOOL bLButton = GetKeyState( VK_LBUTTON ) < 0;
		return bLButton; }

	static BOOL RButtonKeyState() {
		BOOL bRButton = GetKeyState( VK_RBUTTON ) < 0;
		return bRButton; }

	static BOOL MButtonKeyState() {
		BOOL bMButton = GetKeyState( VK_MBUTTON ) < 0;
		return bMButton; }

	static void InitMouse3BtnStatus()
	{
		if( NULL == ms_hMouseHook )
		{
			_mLButton = LButtonKeyState();
			_mRButton = RButtonKeyState();
			_mMButton = MButtonKeyState();
		}
	}

public:
	static HHOOK ms_hMouseHook;
};

HHOOK SMouseUIStatePriv::ms_hMouseHook = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks LBUTTON Key is pressed. The other shift keys can be pressed or not
BOOL SMouseUIState::IsLButton_()
{
	SMouseUIStatePriv::InitMouse3BtnStatus();
	return LButton;
}

/// Checks RBUTTON Key is pressed. The other shift keys can be pressed or not
BOOL SMouseUIState::IsRButton_()
{
	SMouseUIStatePriv::InitMouse3BtnStatus();
	return RButton;
}

/// Checks MBUTTON Key is pressed. The other shift keys can be pressed or not
BOOL SMouseUIState::IsMButton_()
{
	SMouseUIStatePriv::InitMouse3BtnStatus();
	return MButton;
}

BOOL SMouseUIState::StartMouseHook( HINSTANCE hInst )
{
	if( SMouseUIStatePriv::ms_hMouseHook )
		return FALSE;

	_mLButton = SMouseUIStatePriv::LButtonKeyState();
	_mRButton = SMouseUIStatePriv::RButtonKeyState();
	_mMButton = SMouseUIStatePriv::MButtonKeyState();

	SMouseUIStatePriv::ms_hMouseHook = SetWindowsHookEx( WH_MOUSE, 
														 (HOOKPROC)SMouseUIStatePriv::MouseHookProc, 
														 hInst, GetCurrentThreadId() );
	if( NULL == SMouseUIStatePriv::ms_hMouseHook )
		return FALSE;

	return TRUE;
}

BOOL SMouseUIState::StopMouseHook()
{
	if( NULL == SMouseUIStatePriv::ms_hMouseHook )
		return FALSE;

	UnhookWindowsHookEx( SMouseUIStatePriv::ms_hMouseHook );
	SMouseUIStatePriv::ms_hMouseHook =  NULL;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK SMouseUIStatePriv::MouseHookProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( (nCode<0) || (HC_NOREMOVE == nCode) )
		return CallNextHookEx( ms_hMouseHook, nCode, wParam, lParam );

	
	if ( HC_ACTION == nCode )
	{
		switch( wParam )
		{
		case WM_LBUTTONDOWN:
			_mLButton = TRUE;
			break;

		case WM_LBUTTONUP:
			_mLButton = FALSE;
			break;

		case WM_RBUTTONDOWN:
			_mRButton = TRUE;
			break;

		case WM_RBUTTONUP:
			_mRButton = FALSE;
			break;

		case WM_MBUTTONDOWN:
			_mMButton = TRUE;
			break;

		case WM_MBUTTONUP:
			_mMButton = FALSE;
			break;
		}

		MOUSEHOOKSTRUCT* psMs = (MOUSEHOOKSTRUCT*)lParam;
		_mCursor = psMs->pt;
	}
	
	return CallNextHookEx( ms_hMouseHook, nCode, wParam, lParam );
}