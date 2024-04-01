#ifndef ___G_ELEMENT_TOOL__PH___
#define ___G_ELEMENT_TOOL__PH___

#include "eUITool.h"

class CGISelectionTool;
class GDOM_EXT_CLASS CGIElementTool : public CGIElementUITool
{
	DECL_GTPYECLASS_DYNCREATE(CGIElementTool)
public:
	enum HITTEST {
		HT_ELEMENT  = 0xFFFFFFFE,
		HT_POINT    = 0x200,	///(512)
	};

	enum TOOL_MODE_CAPS {
		TMC_NONE			= 0,

		TMC_MOVE_TRACKER	= 0x001,

		TMC_ORIENT			= 0x002,
		TMC_ANGLESNAP		= 0x004,
		TMC_SYMMETRIC		= 0x008,
		TMC_CENTER			= 0x010,
	};

	enum DRAG_ORIENT_TYPE {
		NONE_DRAG_ORIENT		= 1,
		HORZ_DRAG_ORIENT		= 2,
		VERT_DRAG_ORIENT		= 3,
	};

	enum TRACKER_DRAW_TYPE { 
		TDT_NONE	= 0,
		TDT_START	= 1,
		TDT_DRAWN	= 2,
		TDT_END		= 3,
	};

public:
	CGIElementTool();
	virtual ~CGIElementTool();

public:
	virtual UINT GetToolModeCaps() const;
	virtual BOOL IsToolModeCaps( INT nIndex ) const;

	virtual UINT GetToolMode() const;
	virtual BOOL IsToolModeActive( INT nIndex ) const;
	virtual BOOL SetToolMode( INT nIndex, BOOL bSet = TRUE );

	virtual BOOL IsToolModeKey( INT nMode, UINT nChar );
	virtual UINT GetToolModeKey( INT nMode );

	BOOL IsNewElementMode() const;
	virtual BOOL BeginNewElement( LPCTSTR pctszTagName );
	virtual void EndNewElement();

	BOOL SetNewElementMode( BOOL bSet, CGIGroup* pParent = NULL );
	CGINode* GetNewElementParent() const;

	INT GetHandleSize() const;
	void SetHandleSize( INT nSize );

	void SetHandleColor( const Color& rColor, BOOL bSelected = FALSE );
	const Color& GetHandleColor( BOOL bSelected = FALSE ) const;
	virtual void DrawHandleRect( CDC& rDC, RECT& rRect, const PointF* pptf, INT nCount, BOOL bSelected = FALSE );

	CGISelectionTool* GetSelectionTool() const;
	void SetSelectionTool( CGISelectionTool* pTool );

	virtual void UpdateTrackerDisplay();
	virtual void UpdateTracker();
	virtual BOOL DrawTracker( CDC& rDC, RECT& rRect );

	virtual void GetTrackerPath( GraphicsPath& rgpath, const Matrix* pmtx = (Matrix*)-1 );
	virtual void MoveTracker( const PointF& rptfOffset );
	virtual void StartTracker();
	virtual void EndTracker();

	virtual void UpdateWindow() const;
	virtual void UpdateDisplay() const;
	virtual void InvalidateRect( RectF* pRect ) const;
	virtual void InvalidateRect( RECT* pRect ) const;
	overrided void InvalidateRect( BOOL bTracker = FALSE ) const;
	
	virtual void StartElementPoints();
	virtual void StartOrientToolMode();

	virtual void UpdateOrientToolMode();
	virtual void UpdateAngleSnapToolMode();
	virtual void UpdateSymmetricToolMode();
	virtual void UpdateCenterToolMode();
	virtual BOOL UpdateMoveTrackerToolMode();

	overrided BOOL GetSelection() const;
	overrided void SetSelection( BOOL bSet = TRUE );

	overrided INT GetHitTest() const;
	overrided void SetHitTest( INT nHitTest );

	overrided INT GetDrawType() const;
	overrided BOOL OnKeyDown( const CKbdEvent& rEvent );
	overrided BOOL OnKeyUp( const CKbdEvent& rEvent );
	
public:
	BOOL				m_bNewElementActive;
	CGIGroup*			m_pNewElementParent;
	CGISelectionTool*	m_pSelTool;
	BOOL				m_bSelection;

	INT					m_nHandleSize;
	INT					m_nHalfHandleSize;

	Color				m_cSelectedHandle;		/// Selected Handle Rect Color
	Color				m_cHandle;				/// Handle Rect Color

	INT					m_nTrackerDrawType;
	mutable CGRectF		m_grctfDrawBBox;

	INT					m_nDragOrient;

	PointF				m_ptfElementStart;
	PointF				m_ptfElementEnd;
	PointF				m_ptfElementCenter;

	PointF				m_ptfCurStart;
	PointF				m_ptfCurEnd;
	PointF				m_ptfCur;

	PointF				m_ptfStart;
	PointF				m_ptfCursor;

	PointF				m_ptfScreenStart;
	PointF				m_ptfScreenCursor;

	UINT				m_nToolMode;
	UINT				m_nToolModeCaps;
};

inline UINT CGIElementTool::GetToolModeCaps() const {
	return m_nToolModeCaps; }

inline UINT CGIElementTool::GetToolMode() const {
	return m_nToolMode; }

inline BOOL CGIElementTool::IsNewElementMode() const {
	return m_pSelTool && m_pNewElementParent; }

inline CGINode* CGIElementTool::GetNewElementParent() const {
	return m_pNewElementParent; }

inline INT CGIElementTool::GetHandleSize() const {
	return m_nHandleSize; }

inline const Color& CGIElementTool::GetHandleColor( BOOL bSelected /*= FALSE*/ ) const {
	if( bSelected )
		return m_cSelectedHandle;

	return m_cHandle; }

inline CGISelectionTool* CGIElementTool::GetSelectionTool( ) const {
	return m_pSelTool; }

inline void CGIElementTool::SetSelectionTool( CGISelectionTool* pTool ) {
	m_pSelTool = pTool; }

inline INT CGIElementTool::GetHitTest() const {
	return m_nHitTest; }

inline void CGIElementTool::SetHitTest( INT nHitTest ) {
	m_nHitTest = nHitTest; }

inline BOOL CGIElementTool::GetSelection() const {
	return m_bSelection; }

inline void CGIElementTool::SetSelection( BOOL bSet /*= TRUE*/ ) {
	CGIElementUITool::SetSelection( bSet );
	m_bSelection = bSet; }

#endif //!___G_ELEMENT_TOOL__PH___
