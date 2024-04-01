#ifndef ___TEST_VIEW_VIEW__PH___
#define ___TEST_VIEW_VIEW__PH___

#include <g/type/idom/giView.h>
#include <g/wnd/gViewWnd.h>
#include <cu\ui.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
class CTestViewView : public CView, public CUI
{
	DECLARE_DYNCREATE( CTestViewView )
protected: 
	CTestViewView();
	virtual ~CTestViewView();

public:
	//{{AFX_VIRTUAL(CTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnDestroy();
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnSysKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual CTestViewDoc* GetDocument();

	overrided BOOL OnKeyDown( const CKbdEvent& rEvent );
	overrided BOOL OnKeyUp( const CKbdEvent& rEvent );

public:
	CGViewWnd*		m_pwndView;
	CGIView*		m_pgView;
};

#ifndef _DEBUG  // debug version in testView.cpp
inline CTestViewDoc* CTestViewView::GetDocument() {
	return ( CTestViewDoc * ) m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
#endif //!___TEST_VIEW_VIEW__PH___
