#ifndef ___G_EDITOR__PH___
#define ___G_EDITOR__PH___

#include <cu\RulerWnd.h>
#include <g\wnd\gPlayWnd.h>
#include <g\wnd\gViewWnd.h>
#include <g\type\idom\gUI.h>
#include "gEditView.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGEditWndEvent : public CGMutationEvent
{
public:
	static LPCTSTR ActiveGroupChange;

public:
	CGEditWndEvent();
};

class CGEditWnd;
///////////////////////////////////////////////////////////////////////////////////////////////////
class CGEditRulerWnd : public CRulerWnd, public CGEventNode
{
public:
	CGEditRulerWnd();
	virtual ~CGEditRulerWnd();

public:
	virtual BOOL OnInitialUpdate();

	virtual void ShowSettingDlg();
	virtual void CalcCoord( GPointF& rpptf, INT nType ) const;
	BOOL SetView( CGIEditView* pEditView );

	///{{ Reimplemented
	overrided void HandleEvent( CGEvent& rEvent );
	///}} Reimplemented

protected:
	CGIEditView* m_pEditView;

	friend CGEditWnd;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
struct SGridConf
{
	/// enGS - Grid Style
	enum 
	{ 
		enGSDot, enGSLine 
	};

	CGUnit::UNIT	enUnit;
	FLOAT			fMajor;
	INT				nMinorDiv;

	BOOL			bVisible;
	BOOL			bSnap;
	INT				nStyle;
	COLORREF crf;
};

struct SViewGrid : public SGridConf
{
	struct SView
	{
		FLOAT		fsx, fsy;
		FLOAT		fex, fey;			

		FLOAT		fMajor,	   fMinor;		
		FLOAT		fMajorDiv, fMinorDiv;
	};
	struct SView v;
	BOOL		bMajor, bMinor;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGEditViewWnd : public CGViewWnd
{
	DECL_GTPYECLASS_DYNCREATE(CGEditViewWnd);

public:
	CGEditViewWnd();
	
	//{{AFX_VIRTUAL(CGEditViewWnd)
	virtual BOOL OnInitialUpdate();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGEditViewWnd)
	BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void DrawGrid( CDC* pDC );
	void DrawLineGrid( CDC* pDC );
	void DrawDotGrid( CDC* pDC );

	void CalcGrid();
	void SaveGridSetting();
	void LoadGridSetting();

	///{{ Reimplemented
	virtual void DrawView( Graphics& rGdip, const CRect& rrcPaint, BOOL bPrint = FALSE );
	virtual CGIUITool* CreateTool( const CGType& rType );
	///}} Reimplemented

public:
	static 
	 SGridConf			ms_sGridConf;
	SViewGrid			m_sViewGrid;
	CGEditRulerWnd*		m_pwndRuler;
	CGEditWnd*			m_pwndEdit;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGIRectElementTool;
class CGILineElementTool;
class CGIElementTool;
class CGISelectionTool;

class GDOM_EXT_CLASS CGEditWnd : public CGWin, public CGEventNode
{
	DECL_BASE_GTPYECLASS_DYNCREATE( CGEditWnd )

public:
	enum {
		EID_RULER_WND	= 1,
		EID_PLAY_WND	= 2,
	};

	struct SToolItem {
		CGIUITool*		pTool;
		const CGType*	pType;	
	};

public:
	CGEditWnd();
	virtual ~CGEditWnd();

	//{{AFX_VIRTUAL(CGEditWnd)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGEditWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//{{AFX_Event_Link
	void OnDocumentChangeEvent( CGEvent& rEvent );
	void OnNodeInsertedEvent( CGMutationEvent& rEvent );
	void OnNodeRemoveEvent( CGMutationEvent& rEvent );
	//}}AFX_Event_Link
	DECLARE_EVENT_LINK()

public:
	virtual BOOL OnInitialUpdate();

	CGViewWnd* GetViewWindow();
	const CGViewWnd* GetViewWindow() const;
	BOOL SetViewWindow( CGViewWnd& rwndView );

	CGIView* GetView();
	const CGIView* GetView() const;
	BOOL SetView( CGIView& rView );

	CGPlayWnd* GetPlayWindow();
	const CGPlayWnd* GetPlayWindow() const;
	BOOL SetPlayWindow( CGPlayWnd& rwndPlay );
	
	virtual INT FindTool( CGIUITool* pTool ) const;
	virtual CGIUITool* GetTool( const CGType& rType ) const;
	virtual const CGType& GetToolType( UINT nChar ) const;

	virtual BOOL AddTool( CGIUITool* pTool, const CGType& rType );
	virtual BOOL RemoveTool( CGIUITool* pTool );
	virtual void DeleteAllTool();

	BOOL SelectTool( UINT nKey );
	BOOL SelectTool( const CGType& rType );
	BOOL SelectTool( CGIUITool& rTool );
	BOOL SetElementTool( CGIElementTool& rTool );
	BOOL SetSelectionTool( CGISelectionTool& rTool );
	CGISelectionTool* GetSelectionTool();
	const CGISelectionTool* GetSelectionTool() const;

	void SetActiveGroup( CGIGroup* pGroup );
	CGIGroup* GetActiveGroup();
	const CGIGroup* GetActiveGroup() const;

	static void* CreateElementToolCB( LPCTSTR pClassName, void* pCookie );
	overrided void* CreateFactoryObject( const CGType& rType );

	BOOL Create( CWnd* pParent, INT nID, RECT& rect = CRect(0,0,0,0) );

	overrided BOOL OnMouseMove( const CMouseEvent& rEvent );

	overrided BOOL OnLButtonDown( const CMouseEvent& rEvent );
	overrided BOOL OnLButtonUp( const CMouseEvent& rEvent );
	overrided BOOL OnLButtonDblClk( const CMouseEvent& rEvent );

	overrided BOOL OnKeyDown( const CKbdEvent& rEvent );
	overrided BOOL OnKeyUp( const CKbdEvent& rEvent );
	
protected:
	CGEditRulerWnd*					m_pwndRuler;
	CGPlayWnd*						m_pwndPlay;

	CGViewWnd*						m_pwndView;	/// Temp holder used 
	CGIView*						m_pView;	/// while creating Play window

	CArray<SToolItem, SToolItem&>	m_arrTool;
	CGIRectElementTool*				m_pRectTool;
	CGILineElementTool*				m_pLineTool;
};

inline CGPlayWnd* CGEditWnd::GetPlayWindow() {
	return m_pwndPlay; }

inline const CGPlayWnd* CGEditWnd::GetPlayWindow() const {
	return (const CGPlayWnd*)((CGEditWnd*)this)->GetPlayWindow(); }

inline CGIView* CGEditWnd::GetView() {
	return (CGIView*)((const CGEditWnd*)this)->GetView(); }

inline CGViewWnd* CGEditWnd::GetViewWindow() {
	return (CGViewWnd*)((const CGEditWnd*)this)->GetViewWindow(); }

//{{AFX_INSERT_LOCATION}}
#endif //!___G_EDITOR__PH___
