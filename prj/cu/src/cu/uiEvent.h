#ifndef ___UI_EVENT__PH___
#define ___UI_EVENT__PH___

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CUIEvent
{
public:
	CUIEvent();

	void InitEvent( LPCTSTR	pctszEventType );

	static LPCTSTR GetEventType( UINT nMessage );

public:
	LPCTSTR	m_pctszEventType;
	MSG		m_sMsg;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CMouseEvent : public CUIEvent
{
public:
	static LPCTSTR mousewheel;
	static LPCTSTR mousemove;

	static LPCTSTR lbuttondown;
	static LPCTSTR lbuttonup;
	static LPCTSTR lbuttondblclk;

	static LPCTSTR rbuttondown;
	static LPCTSTR rbuttonup;
	static LPCTSTR rbuttondblclk;

	static LPCTSTR mbuttondown;
	static LPCTSTR mbuttonup;
	static LPCTSTR mbuttondblclk;

public:
	CMouseEvent();

	void InitEvent( HWND hWnd, UINT nMessage );
	void InitEvent( HWND hWnd, UINT nMessage, const POINT& rptClient, INT nFlags = 0, short zDelta = 0 );

	void InitEvent( const MSG& rsMsg );
	void InitEvent( HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam );

	static LPCTSTR GetEventType( UINT nMessage );

	void GetWindowsParameter( UINT& rnFlags, CPoint& rpoint, short* pzDelta = NULL ) const;

public:
	CPoint	m_ptClient;
	CPoint	m_ptScreen;
	INT		m_zDelta;

	BOOL	m_bCtrlKey;
	BOOL	m_bShiftKey;
	BOOL	m_bAltKey;
	BOOL	m_bMetaKey;

	BOOL	m_bLButton;
	BOOL	m_bRButton;
	BOOL	m_bMButton;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CKbdEvent : public CUIEvent
{
public:
	static LPCTSTR keydown;
	static LPCTSTR keyup;

public:
	CKbdEvent();

	void InitEvent( HWND hWnd, UINT nMessage, UINT nChar );
	void InitEvent( HWND hWnd, UINT nMessage, UINT nChar, UINT nRepCnt, UINT nFlags );

	void InitEvent( const MSG& rsMsg );
	void InitEvent( HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam );

	static LPCTSTR GetEventType( UINT nMessage );

	void GetWindowsParameter( UINT& rnChar, UINT& rnRepCnt, UINT& rnFlags ) const;

public:
	INT		m_nKey;
	INT		m_nRepCnt;

	BOOL	m_bCtrlKey;
	BOOL	m_bShiftKey;
	BOOL	m_bAltKey;
	BOOL	m_bMetaKey;
};

#endif //!___UI_EVENT__PH___
