#ifndef ___G_WIN__PH___
#define ___G_WIN__PH___

#include <cu\Win.h>
#include <cu\UI.h>

class GDOM_EXT_CLASS CGWin : public CWin
{
public:
	CGWin();

public:
	void SetUIHook( CGWin* pUIHook );
	CGWin* GetUIHook() const;

	/// To forward to parent
	overrided BOOL OnMouseWheel( const CMouseEvent& rEvent );
	overrided BOOL OnMouseMove( const CMouseEvent& rEvent );

	overrided BOOL OnLButtonDown( const CMouseEvent& rEvent );
	overrided BOOL OnLButtonUp( const CMouseEvent& rEvent );
	overrided BOOL OnLButtonDblClk( const CMouseEvent& rEvent );

	overrided BOOL OnRButtonDown( const CMouseEvent& rEvent );
	overrided BOOL OnRButtonUp( const CMouseEvent& rEvent );
	overrided BOOL OnRButtonDblClk( const CMouseEvent& rEvent );

	overrided BOOL OnMButtonDown( const CMouseEvent& rEvent );
	overrided BOOL OnMButtonUp( const CMouseEvent& rEvent );
	overrided BOOL OnMButtonDblClk( const CMouseEvent& rEvent );

	overrided BOOL OnKeyDown( const CKbdEvent& rEvent );
	overrided BOOL OnKeyUp( const CKbdEvent& rEvent );

protected:
	BOOL SendToUIHook( const CMouseEvent& rEvent );

protected:
	CGWin* m_pUIHook;
};

inline CGWin* CGWin::GetUIHook() const {
	return m_pUIHook; }

#endif //!___G_WIN__PH___