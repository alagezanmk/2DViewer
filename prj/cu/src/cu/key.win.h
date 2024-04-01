#ifndef ___KEY__WIN__PH___
#define ___KEY__WIN__PH___

struct SAlxKeyState
{ 
	POINT ptCursor;
	BOOL bLButton;
	BOOL bRButton;
	BOOL bMButton;

	BOOL bNumLock;
	BOOL bScrollLock;
	BOOL bCapsLock;

	BOOL bShift;
	BOOL bControl;
	BOOL bAlt;
	BOOL bWin;
	BOOL bApps;

///	BOOL bLShift;
///	BOOL bLControl;
///	BOOL bLAlt;
	BOOL bLWin;

///	BOOL bRShift;
///	BOOL bRControl;
///	BOOL bRAlt;
	BOOL bRWin;
};

extern CU_EXT_DATA SAlxKeyState g_alxKeyState;
CU_EXT_API BOOL SetKbStatusHook( HINSTANCE hInst );
CU_EXT_API BOOL ReleaseKbStatusHook();

CU_EXT_API BOOL SetMsStatusHook( HINSTANCE hInst );
CU_EXT_API BOOL ReleaseMsStatusHook();

typedef INT (*PFNKeyEventCB)( UINT nChar, BOOL bKeyDown, void* pUserData );
CU_EXT_API BOOL AddKeyEventListener( UINT nChar, BOOL bKeyDown, PFNKeyEventCB pfnCB, void* pUserData );
CU_EXT_API BOOL RemoveKeyEventListener( UINT nChar, BOOL bKeyDown, PFNKeyEventCB pfnCB, void* pUserData );

#endif  //!___KEY__WIN__PH___