#ifndef ___TEST_BLD_VIEW__PH___
#define ___TEST_BLD_VIEW__PH___

#include <bld\bView.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
class CTestBldView : public CGEditView
{
	DECLARE_DYNCREATE( CTestBldView )
protected: 
	CTestBldView();
	virtual ~CTestBldView();

public:
	//{{AFX_VIRTUAL(CTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnInitialUpdate();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnTimer( UINT nIDEvent );
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CTreeCtrl* GetTreeCtrl();
	const CTreeCtrl* GetTreeCtrl() const;

	HTREEITEM AddChild( CGINode* pgiNode, HTREEITEM hParent, BOOL bAddChilds = FALSE );
	BOOL RemoveChild( CGINode* pgiNode, HTREEITEM hParent );

	void SelectElement( CGIShapeElement* pElement );
	void DeselectElement( CGIShapeElement* pElement );

	//{{AFX_Event_Link
	void OnDocumentChangeEvent( CGEvent& rEvent );
	void OnSelectionEvent( CGEvent& rEvent );
	void OnNodeLinkChangeEvent( CGMutationEvent& rEvent );
	//}}AFX_Event_Link
	DECLARE_EVENT_LINK()

	static void OnPropObjectSelChange( NMHDR* pNMHDR, LRESULT* plResult, void* pvParam );

public:
	CTestBldDoc* GetDocument();
};

#ifndef _DEBUG  // debug version in testView.cpp
inline CTestBldDoc* CTestBldView::GetDocument() {
	return ( CTestBldDoc * ) m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
#endif //!___TEST_BLD_VIEW__PH___
