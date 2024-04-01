#ifndef ___G_SELECTION_TOOL__PH___
#define ___G_SELECTION_TOOL__PH___

#include "zpTool.h"
#include "eTool.h"
#include "eGroupTool.h"
#include <gbase\gClassFactory.h>

//////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSelectionEvent : public CGEvent
{
public:
	static LPCTSTR	EVENT;

	/// Selection Change
	enum SELECTION_CHANGE{
		UNKNOWN				= 0x00,
		START_SELECTION		= 0x01,
		SELECT				= 0x02,
		DESELECT			= 0x03,
		SELECTION_PICK		= 0x04,
		END_SELECTION		= 0x05,
	};

public:
	CGSelectionEvent();
	virtual ~CGSelectionEvent();

	INT GetSelectionChange() const;
	CPtrArray& GetShapeElementArray();

	void InitEvent( INT	nSelectionChange, CGIElement& rElement, 
				    const GPointF* pptf = NULL );
	void InitEvent( INT	nSelectionChange, const CPtrArray* parpElements = NULL, 
					const GRectF* prctf = NULL );

protected:
	INT					m_nSelectionChange;		/// See SELECTION_CHANGE
	CPtrArray			m_arpElements;			/// List of elements for 
												/// selection /de-selection
	CGPointF			m_ptfHit;				/// Point at which selection was done
	CGRectF				m_rctf;					/// Rectangle at which selection was done
};

inline INT CGSelectionEvent::GetSelectionChange() const {
	return m_nSelectionChange; }

inline CPtrArray& CGSelectionEvent::GetShapeElementArray() {
	return m_arpElements; }

//////////////////////////////////////////////////////////////////////////////////////////
/// >>> TODO <<<
/// This class is written temporarily to act for Editor supporting Selection Tool. 
/// and it has to be reimplemented to have support for Player window.
/// 1 Jan 2007 - Alagesan

/// >>> TODO <<<
/// Make this class similar to the selection tool done in QProbe 1.4
/// Need to be done are
///		1. 

class GDOM_EXT_CLASS CGISelectionTool : public CGIZoomPanTool, 
										public CGFactoryObject
{
protected:
	DECL_GTPYECLASS_DYNCREATE(CGISelectionTool)

public:
	enum ESelectionFlag {
		ESF_NONE				= 0,
		ESF_MULTIPLE_SELECTION	= 1,
		ESF_MAKE_ACTIVE			= 2,
		ESF_NO_UPDATE_SELECTION	= 4,
		ESF_NO_START_SELECTION	= 8,
		ESF_NO_END_SELECTION	= 16,
	};

	enum UI_MODE { 
		SELECTION_UI_MODE		= 256,
	};

	enum UI_STATE { 
		MULTIPLE_SELECTION_UI_STATE	= 256,
		MAKE_ACTIVE_UI_STATE		= 257,
	};

public:
	CGISelectionTool();

protected:
	virtual ~CGISelectionTool();

public:
	void SetActiveGroup( CGIGroup* piGroup );
	CGIGroup* GetActiveGroup() const;
	
	INT SelectAll();
	BOOL DeselectAll();

	BOOL AddSelection( CGIElement& rElement, BOOL bUpdate = TRUE );
	BOOL RemoveSelection( CGIElement& rElement, BOOL bUpdate = TRUE );

	BOOL ChangeSelection( CGIElement& rElement, INT nFlags = ESF_NONE );
	void UpdateSelection();

	/// Select a shape element manually at the spectified point 'rpoint'. 
	/// The point 'rptf' value is in Device coordinate
	INT Select( const CPoint& rpoint, INT nFlags = ESF_NO_START_SELECTION 
												 | ESF_NO_END_SELECTION );

	/// Select a shape elements manually lie within the specified rectangle rrct'. 
	/// The rectangle 'rctf' value is in Device coordinate
	BOOL Select( const CRect& rrct, INT nFlags = ESF_NO_START_SELECTION 
		                                       | ESF_NO_END_SELECTION );

	/// Deselect a shape element manually at the specified point 'rptf'. 
	/// The point 'rptf' value is in Device coordinate
	BOOL Deselect( const CPoint& rpoint );

	/// Deselect a shape elements manually lie within the specified rectangle rrct'. 
	/// The rectangle 'rctf' value is in Device coordinate
	BOOL Deselect( const CRect& rrct );

	/// Returns number Tools of selected elements
	INT GetSelectedCount() const;

	/// Returns array pointers pointing to the Tools of selected elements
	CGIElementUITool** GetSelectedTools();
	const CGIElementUITool** GetSelectedTools() const;

	BOOL GetLock() const;
	void SetLock( BOOL bSet = TRUE );

	void SetDefaultElementTool( CGIElementUITool* pTool );
	CGIElementUITool* GetDefaultElementTool() const;

	void SetDefaultTool( CGIUITool* pTool );
	CGIUITool* GetDefaultTool() const;

	CGIElementUITool* GetActiveTool() const;
	CGIElementUITool* GetFocusTool() const;

	///{{ Reimplemented
	virtual INT GetDrawType() const;
	virtual BOOL Draw( CDC& rDC, RECT& rRect );
	overrided UINT HitTest( const CPoint& rpoint );
	overrided BOOL On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage );
	
	overrided BOOL OnMouseWheel( const CMouseEvent& rEvent );
	overrided BOOL OnMouseMove( const CMouseEvent& rEvent );
	overrided BOOL OnLButtonDown( const CMouseEvent& rEvent );
	overrided BOOL OnLButtonUp( const CMouseEvent& rEvent );

	overrided BOOL OnKeyDown( const CKbdEvent& rEvent );
	overrided BOOL OnKeyUp( const CKbdEvent& rEvent );

	virtual BOOL IsUIStateKey( INT nMode, INT nState, UINT nChar );
	virtual UINT GetUIStateKey( INT nMode, INT nState );

	overrided void LockObjectLink( BOOL bLock = TRUE );
	overrided CGFactoryObject* GetFactoryObjectParent();

	overrided CGClassFactory* GetClassFactory();
	overrided void* CreateFactoryObject( LPCTSTR pctszClassName, void* pCookie = NULL ) const;

	virtual void SetView( CGIView* pView );
	///}} Reimplemented

protected:
	/// Trigger a CGSelectionEvent' START_SELECTION event
	void StartSelection();

	/// Trigger a CGSelectionEvent' END_SELECTION event
	void EndSelection();

	/// Pick one or more Shape element for selection and 
	/// trigger a CGSelectionEvent' SELECTION_PICK event
	BOOL SelectionPick( CPtrArray& rarShapeElement, const GRectF& rrctf, 
		                INT nFlags = ESF_NONE );

	virtual CGIElementUITool* CreateElementTool( CGIElement& rElement );

	CGIElementUITool* HitTestTools( const CPoint& rpoint, UINT& rnHitTest ) const;
	CGIElement* HitTestGroupElements( const CPoint& rpoint, UINT& rnHitTest ) const;

	INT HitTestGroupElements( const CRect& rrct, CPtrArray& rarpElement );

protected:
	CGIElementUITool*		m_pDefaultElementTool;
	CGIUITool*				m_pDefaultTool;

	CGIGroupElementTool		m_GroupTool;
	CGIElementUITool*		m_pActiveTool;	/// The Active Tool is having unique selection 
											/// marking in case of multiple element 
											/// selection. In single element selection, 
											/// the Active Tool is same as the Focus Tool.

	CGIElementUITool*		m_pFocusTool;	/// The Focus Tool is the UI responding Tool 
											/// in multiple element selection and the Tool
											/// will be the type CGIGroupElementTool. 
											/// In single element selection, the Focus 
											/// Tool is same as the Active Tool

	CGIGroup*				m_piActiveGroup;/// The Active Group is specifies a pointer 
											/// of Group which is used to select or 
											/// de-select the Group child elements 
											/// during selection using mouse and used to 
											/// check selecting or deselecting one or 
											///	more element by manual selection

	CPoint					m_ptClick;
	UINT					m_nHitTest;
	mutable 
		CGIElement*			m_piHitObject;
	mutable 
		CGIElementUITool*	m_piHitTool;
	
	BOOL					m_bLock;
	BOOL					m_bMultipleSelect;
	BOOL					m_bChangeActive;
	BOOL					m_bUIToActiveObject;
	BOOL					m_bFirstMouseMove;
	BOOL					m_bStartSelectionCalled;
};

inline INT CGISelectionTool::GetSelectedCount() const {
	return m_GroupTool.m_arpTool.GetSize(); }

inline CGIElementUITool** CGISelectionTool::GetSelectedTools() {
	return (CGIElementUITool**)m_GroupTool.m_arpTool.GetData(); }

inline const CGIElementUITool** CGISelectionTool::GetSelectedTools() const {
	return (const CGIElementUITool**)m_GroupTool.m_arpTool.GetData(); }

inline BOOL CGISelectionTool::GetLock() const {
	return m_bLock; }

inline CGIGroup* CGISelectionTool::GetActiveGroup() const {
	return m_piActiveGroup; }

inline CGIUITool* CGISelectionTool::GetDefaultTool() const {
	return m_pDefaultTool; }

inline CGIElementUITool* CGISelectionTool::GetDefaultElementTool() const {
	return m_pDefaultElementTool; }

inline CGIElementUITool* CGISelectionTool::GetActiveTool() const {
	return m_pActiveTool; }

inline CGIElementUITool* CGISelectionTool::GetFocusTool() const {
	return m_pFocusTool; }

inline void CGISelectionTool::LockObjectLink( BOOL bLock /*= TRUE*/ ) 
{}

inline CGFactoryObject* CGISelectionTool::GetFactoryObjectParent() {
	return NULL; }

#endif //!___G_SELECTION_TOOL__PH___
