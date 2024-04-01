#ifndef ___G_PLAY_WND_PH___
#define ___G_PLAY_WND_PH___

#include "gViewWnd.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGPlayWnd : public CGWin, public CGEventNode
{
	DECL_BASE_GTPYECLASS_DYNCREATE( CGPlayWnd )

public:
	enum {
		EID_VIEW_WND = 1,
	};

public:
	CGPlayWnd();
	virtual ~CGPlayWnd();

	//{{AFX_VIRTUAL(CGPlayWnd)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGPlayWnd)
	afx_msg void OnSize( UINT nType, int cx, int cy );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitialUpdate();

	CGViewWnd* GetViewWindow();
	const CGViewWnd* GetViewWindow() const;
	BOOL SetViewWindow( CGViewWnd& rwndView );

	CGIView* GetView();
	const CGIView* GetView() const;
	BOOL SetView( CGIView& rView );

	///{{ Reimplemented
	///}} Reimplemented

protected:
	CGViewWnd*	m_pwndView;
	CGIView*	m_pView;
};

inline CGViewWnd* CGPlayWnd::GetViewWindow() {
	return m_pwndView; }

inline const CGViewWnd* CGPlayWnd::GetViewWindow() const {
	return m_pwndView; }

inline CGIView* CGPlayWnd::GetView() {
	return m_pView; }

inline const CGIView* CGPlayWnd::GetView() const {
	return m_pView; }

#endif //!___G_PLAY_WND_PH___