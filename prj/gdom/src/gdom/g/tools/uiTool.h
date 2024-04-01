#ifndef ___G_UI_TOOL__PH___
#define ___G_UI_TOOL__PH___

#include <cu\ui.h>
#include <g\type\idom\gUI.h>
#include <gbase\gObject.h>
#include <g\type\idom\giNode.h>
#include <g\type\idom\giView.h>

#include <g\wnd\gViewWndBase.h>
class GDOM_EXT_CLASS CGIUITool : public CGObject, public CUI
{
	DECL_BASE_GTPYECLASS_DYNCREATE( CGIUITool )
public:
	enum UI_MODE { 
		NONE_UI_MODE = 0,
	};

	enum UI_STATE { 
		NONE_UI_STATE = 0, 
	};

	enum DRAW_TYPE { 
		LOWER_DRAW_TYPE = 0, 
		UPPER_DRAW_TYPE = 1, 
	};

	struct SSubUIMode {
		INT	nMode;
		INT	nState;
	};

public:
	CGIUITool();

protected:
	virtual ~CGIUITool();

public:
	virtual INT GetDrawType() const;

	void SetUIState( INT nState );
	INT GetUIState() const;

	void SetUIMode( INT nMode );
	INT GetUIMode() const;

	void SetDefaultUIMode( INT nMode );
	INT GetDefaultUIMode() const;

	BOOL IsSubUIModeActive( INT nMode, INT nState ) const;
	void GetLastSubUIMode( INT& rnMode, INT& rnState ) const;
	BOOL RemoveSubUIMode( INT nMode, INT nState );
	BOOL PushSubUIMode( INT nMode, INT nState );
	void PopSubUIMode( INT& rnMode, INT& rnState );
	void RemoveAllSubUIMode();

	virtual BOOL IsUIModeKey( INT nMode, UINT nChar );
	virtual UINT GetUIModeKey( INT nMode );

	virtual BOOL IsUIStateKey( INT nMode, INT nState, UINT nChar );
	virtual UINT GetUIStateKey( INT nMode, INT nState );

	virtual BOOL AddListenKeyState( UINT nChar, BOOL bKeyDown = FALSE );
	virtual BOOL AddListenUIModeKey( INT nMode, BOOL bKeyDown = FALSE );
	virtual BOOL AddListenUIStateKey( INT nMode, INT nState, BOOL bKeyDown = FALSE );

	virtual BOOL RemoveListenKeyState( UINT nChar, BOOL bKeyDown = FALSE );
	virtual BOOL RemoveListenUIModeKey( INT nMode, BOOL bKeyDown = FALSE );
	virtual BOOL RemoveListenUIStateKey( INT nMode, INT nState, BOOL bKeyDown = FALSE );

	static INT KeyListenerCB( UINT nChar, BOOL bKeyDown, void* pUserData );
	INT KeyListener( UINT nChar, BOOL bKeyDown, void* pUserData );

	CGIViewWnd* GetViewWindow();
	const CGIViewWnd* GetViewWindow() const;
	virtual void SetViewWindow( CGIViewWnd* pWin );

	CGIView* GetView();
	const CGIView* GetView() const;
	virtual void SetView( CGIView* pView );

	///{{ Reimplemented
	virtual BOOL Draw( CDC& rDC, RECT& rRect );
	///}} Reimplemented

protected:
	CGIViewWnd*		m_pwndView;
	CGIView*		m_pView;

	INT				m_nHitTest;
	INT				m_nUIMode;
	INT				m_nUIState;

	INT				m_nDefUIMode;
	CArray<SSubUIMode, SSubUIMode&> m_aarSubMode;
};

inline INT CGIUITool::GetUIState() const {
	return m_nUIState; }

inline INT CGIUITool::GetUIMode() const {
	return m_nUIMode; }

inline INT CGIUITool::GetDefaultUIMode() const {
	return m_nDefUIMode; }


inline CGIView* CGIUITool::GetView() {
	return m_pView; }

inline const CGIView* CGIUITool::GetView() const {
	return m_pView; }

inline CGIViewWnd* CGIUITool::GetViewWindow() {
	return m_pwndView; }

inline const CGIViewWnd* CGIUITool::GetViewWindow() const {
	return m_pwndView; }

#endif //!___G_UI_TOOL__PH___
