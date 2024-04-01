#ifndef ___BLD_VIEW__PH___
#define ___BLD_VIEW__PH___

#include <cu\ui.h>
#include <bld\gEditWnd.h>
#include <ctrl\ObjLayerCtrl.h>

class GDOM_EXT_CLASS CGEditView : public CView, public CUI, public CGEventNode
{
public:
	enum {
		EID_EDIT_WND = 1
	};

protected:
	DECLARE_DYNCREATE(CGEditView)

public:
	CGEditView();
	virtual ~CGEditView();

public:
	//{{AFX_VIRTUAL(CGEditView)
	public:
	virtual void OnDraw( CDC* pDC );
	protected:
	virtual BOOL OnPreparePrinting( CPrintInfo* pInfo );
	virtual void OnBeginPrinting( CDC* pDC, CPrintInfo* pInfo );
	virtual void OnEndPrinting( CDC* pDC, CPrintInfo* pInfo );
	virtual void OnPrint( CDC* pDC, CPrintInfo* );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CGEditView)
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnDestroy();
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnSysKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg LRESULT OnKeyDownMsg( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnKeyUpMsg( WPARAM wParam, LPARAM lParam );
	afx_msg void OnViewActivate( UINT nCmd );
	afx_msg void OnLayerCtrlCmd( UINT nID );
	afx_msg LRESULT OnLayerSelChange( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	virtual void OnDestroyView();
	virtual void OnDestroyLastView();
	virtual void OnGetFocusView();
	virtual void OnKillFocusView();
	void FillLayerBar();
	void ResetLayerBar();

public:
	overrided BOOL OnKeyDown( const CKbdEvent& rEvent );
	overrided BOOL OnKeyUp( const CKbdEvent& rEvent );

	CGIEditView* GetView();
	const CGIEditView* GetView() const;

	CGIDocument* GetDomDocument();
	const CGIDocument* GetDomDocument() const;

	CGViewWnd* GetViewWindow();
	const CGViewWnd* GetViewWindow() const;

	CGPlayWnd* GetPlayWindow();
	const CGPlayWnd* GetPlayWindow() const;

	CGEditWnd* GetEditWindow();
	const CGEditWnd* GetEditWindow() const;

protected:
	CGEditWnd*		m_pwndEdit;
	CObjLayerCtrl*	m_pLayerCtrl;
};

inline CGEditWnd* CGEditView::GetEditWindow() {
	return m_pwndEdit; }

inline const CGEditWnd* CGEditView::GetEditWindow() const {
	return m_pwndEdit; }

inline CGIEditView* CGEditView::GetView() {
	return (CGIEditView*)((const CGEditView*)this)->GetView(); }

inline CGIDocument* CGEditView::GetDomDocument() {
	return (CGIDocument*)((const CGEditView*)this)->GetDomDocument(); }

inline CGViewWnd* CGEditView::GetViewWindow() {
	return (CGViewWnd*)((const CGEditView*)this)->GetViewWindow(); }

inline CGPlayWnd* CGEditView::GetPlayWindow() {
	return (CGPlayWnd*)((const CGEditView*)this)->GetPlayWindow(); }

#endif //!___BLD_VIEW__PH___
