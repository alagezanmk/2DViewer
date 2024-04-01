#ifndef ___UI_STATE__PH___
#define ___UI_STATE__PH___

namespace NUIState
{
class SBOOL
{
public:
	operator BOOL() const {
		return m_b;	}

protected:
	BOOL m_b;
};

////////////////////////////./////////////////////.//////////////////////////.//////////////////////////
class SPOINT
{
public:
	operator POINT() const {
		return m_pt;	}

protected:
	POINT m_pt;
};

////////////////////////////./////////////////////.//////////////////////////.//////////////////////////
class SCOLORREF
{
public:
	operator COLORREF() const {
		return m_crf;	}

protected:
	COLORREF m_crf;
};

////////////////////////////./////////////////////.//////////////////////////.//////////////////////////
class SHBRUSH
{
public:
	operator HBRUSH() const {
		return m_hbr;	}

protected:
	HBRUSH m_hbr;
};

////////////////////////////./////////////////////.//////////////////////////.//////////////////////////
class SHINSTANCE
{
public:
	operator HINSTANCE() const {
		return m_hInst;	}

protected:
	HINSTANCE m_hInst;
};

////////////////////////////./////////////////////.//////////////////////////.//////////////////////////
class SCString
{
public:
	operator LPCTSTR() const {
		return m_csz;	}

protected:
	CString m_csz;
};

////////////////////////////./////////////////////.//////////////////////////.//////////////////////////
class SCWinApp 
{
public:
	operator CWinApp*() const {
		return m_pApp;	}

protected:
	CWinApp*	m_pApp;
};

////////////////////////////./////////////////////.//////////////////////////.//////////////////////////
class SCMDIFrameWnd
{
public:
	operator CMDIFrameWnd*() const {
		return m_pMainFrm;	}

protected:
	CMDIFrameWnd*	m_pMainFrm;
};
};

struct CU_EXT_CLASS SAppState
{
	static NUIState::SCString			cszAppFolder;
	static NUIState::SHINSTANCE			hAppInst;

	static NUIState::SCWinApp			pApp;
	static NUIState::SCMDIFrameWnd		pMainFrm;
};

struct CU_EXT_CLASS SUIState
{
public:
	////////////////////////////./////////////////////.//////////////////////////.//////////////////////////
	static NUIState::SCOLORREF		crfAppWks;
	static NUIState::SCOLORREF		crfWindow;

	static NUIState::SCOLORREF		crfBtnFace;

	static NUIState::SCOLORREF		crfHilite;
	static NUIState::SCOLORREF		crfShadow;

	static NUIState::SCOLORREF		crf3DHilite;
	static NUIState::SCOLORREF		crf3DShadow;

	static NUIState::SHBRUSH		hbrAppWks;
	static NUIState::SHBRUSH		hbrWindow;
	static NUIState::SHBRUSH		hbrBtnFace;
	static NUIState::SHBRUSH		hbr3DShadow;
	static NUIState::SHBRUSH		hbr3DHilight;
	static NUIState::SHBRUSH		hbr3DDkShadow;
	static NUIState::SHBRUSH		hbr3DDkHilight;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CU_EXT_CLASS SKbdUIState
{
public:
	static BOOL StartKeyboardHook( HINSTANCE hInst );
	static BOOL StopKeyboardHook();
	
	static BOOL IsNoShift();	/// Checks CONTROL, SHIFT, ALT are notpressed
	static BOOL IsAllShift();	/// Checks CONTROL, SHIFT, ALT are pressed
	static BOOL IsCtrl();		/// Checks CONTROL Key alone is pressed
	static BOOL IsCtrl_();		/// Checks CONTROL Key is pressed. The other shift keys can be pressed or not
	static BOOL IsCtrlS();		/// Checks CONTROL, SHIFT Key is pressed, and ALT is pressed
	static BOOL IsCtrlS_();		/// Checks CONTROL, SHIFT Key is pressed, and ALT is pressed or not pressed
	static BOOL IsCtrlA();		/// Checks CONTROL, ALT Key is pressed, and SHIFT is pressed
	static BOOL IsCtrlA_();		/// Checks CONTROL, ALT Key is pressed, and SHIFT is pressed or not pressed
	static BOOL IsCtrl_S();		/// Checks CONTROL Key is pressed, SHIFT is not pressed and ALT is pressed or not
	static BOOL IsCtrl_A();		/// Checks CONTROL Key is pressed, ALT are not pressed and SHIFT is pressed or not
	static BOOL IsShift();		/// Checks SHIFT Key alone is pressed
	static BOOL IsShift_();		/// Checks SHIFT Key is pressed. The other shift keys can be pressed or not
	static BOOL IsShift_C();	/// Checks SHIFT Key is pressed, CONTROL is not pressed and ALT is pressed or not
	static BOOL IsShift_A();	/// Checks SHIFT Key is pressed, ALT are not pressed and CONTROL is pressed or not
	static BOOL IsShiftC();		/// Checks SHIFT, CONTROL Key is pressed, and ALT is pressed
	static BOOL IsShiftC_();	/// Checks SHIFT, CONTROL Key is pressed, and ALT is pressed or not pressed
	static BOOL IsShiftA();		/// Checks SHIFT, ALT Key is pressed, and CONTROL is pressed
	static BOOL IsShiftA_();	/// Checks SHIFT, ALT Key is pressed, and CONTROL is pressed or not pressed
	static BOOL IsAlt();		/// Checks ALT Key alone is pressed
	static BOOL IsAlt_();		/// Checks ALT Key is pressed. The other shift keys can be pressed or not
	static BOOL IsAlt_C();		/// Checks ALT Key is pressed, CONTROL is not pressed and SHIFT is pressed or not
	static BOOL IsAlt_S();		/// Checks ALT Key is pressed, SHIFT are not pressed and CONTROL is pressed or not
	static BOOL IsAltS();		/// Checks ALT, SHIFT Key is pressed, and CONTROL is pressed
	static BOOL IsAltS_();		/// Checks ALT, SHIFT Key is pressed, and CONTROL is pressed or not pressed
	static BOOL IsAltC();		/// Checks ALT, CONTROL Key is pressed, and SHIFT is pressed
	static BOOL IsAltC_();		/// Checks ALT, CONTROL Key is pressed, and SHIFT is pressed or not pressed
	static BOOL IsMeta();		/// Checks Meta is pressed

	typedef INT (*PFNKeyEventCB)( UINT nChar, BOOL bKeyDown, void* pUserData );
	static BOOL AddKeyEventListener( UINT nChar, BOOL bKeyDown, PFNKeyEventCB pfnCB, void* pUserData );
	static BOOL RemoveKeyEventListener( UINT nChar, BOOL bKeyDown, PFNKeyEventCB pfnCB, void* pUserData );

protected:
	static void ResetKeyState(); 

public:
	static NUIState::SBOOL		Shift;
	static NUIState::SBOOL		Control;
	static NUIState::SBOOL		Alt;
	static NUIState::SBOOL		Apps;
	static NUIState::SBOOL		Meta;

	static NUIState::SBOOL		NumLock;
	static NUIState::SBOOL		ScrollLock;
	static NUIState::SBOOL		CapsLock;

	static NUIState::SBOOL		LMeta;
	static NUIState::SBOOL		RMeta;

protected:
	static NUIState::SBOOL		LShift;
	static NUIState::SBOOL		LControl;
	static NUIState::SBOOL		LAlt;

	static NUIState::SBOOL		RShift;
	static NUIState::SBOOL		RControl;
	static NUIState::SBOOL		RAlt;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CU_EXT_CLASS SMouseUIState
{
public:
	static BOOL StartMouseHook( HINSTANCE hInst );
	static BOOL StopMouseHook();
	
	static BOOL IsLButton_();		/// Checks LBUTTON Key is pressed. The other shift keys can be pressed or not
	static BOOL IsRButton_();		/// Checks RBUTTON Key is pressed. The other shift keys can be pressed or not
	static BOOL IsMButton_();		/// Checks MBUTTON Key is pressed. The other shift keys can be pressed or not

public:
	static NUIState::SPOINT		Cursor;
	static NUIState::SBOOL		LButton;
	static NUIState::SBOOL		RButton;
	static NUIState::SBOOL		MButton;
};

#endif  ___UI_STATE__PH___