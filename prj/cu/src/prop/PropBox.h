#ifndef ___PROP_BOX__PH___
#define ___PROP_BOX__PH___

#include "PropObjectSelComboBox.h"
#include "MsProp.h"
#include "PropItemListCtrl.h"

class CPropDesc : public CWnd
{
public:
	CPropDesc();
	virtual ~CPropDesc();

	//{{AFX_VIRTUAL(CPropDesc)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPropDesc)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetEmpty();
	void SetString( CString& rcszDesc );
	void SetString( LPCTSTR pszDesc );

protected:
	CString		m_cszDesc;
	CEdit		m_edtDesc;
};

inline void CPropDesc::SetEmpty() {
	m_cszDesc.Empty(); InvalidateRect( NULL, FALSE ); }

inline void CPropDesc::SetString( CString& rcszDesc ) {
	SetString( (LPCTSTR)rcszDesc ); }

inline void CPropDesc::SetString( LPCTSTR pszDesc ) {
	m_cszDesc = pszDesc; InvalidateRect( NULL, FALSE ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
/// RO - Relate Object
#define PROP_RO_ROOT		((void*)0xFFFFFFFF)
#define PROP_RO_FIRST		((void*)0xFFFFFFFE)
#define PROP_RO_LAST		((void*)0xFFFFFFFD)

class CU_EXT_CLASS CPropBox : public CFrameWnd
{
public:
	struct SObj;
	typedef void (*PFNOnNotify)( NMHDR* pNMHDR, LRESULT* plResult, void* pParam );
	enum NOTIFY_HOOK_TYPE
	{
		SEL_NOTIFY_HOOK = 0,
	};

public:
	CPropBox();
	virtual ~CPropBox();

protected:
	//{{AFX_VIRTUAL(CPropCtrl)
	protected:
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPropCtrl)
	afx_msg INT OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, INT cx, INT cy );
	afx_msg void OnTabSelChange( NMHDR* pNMHDR, LRESULT* plResult );
	afx_msg void OnPropBtn( UINT nID );
	afx_msg void OnPropBtnUI( CCmdUI* pCmdUI );
	afx_msg void OnObjectSelChange( NMHDR* pNMHDR, LRESULT* plResult );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	static void AddPropHandler( SPropHandler* psHandler );
	SPropHandler* GetPropHandler( INT nID );

	void SetNotifyHook( NOTIFY_HOOK_TYPE enType, PFNOnNotify pfnOnNotify, void* pvParam = NULL );

	void ResetContent();
	BOOL DeleteObject( void* pvObject );
	BOOL InsertObject( void* pvObject, LPCTSTR ptszName, INT nID,
					   void* pvParent = TVI_ROOT, void* pvInsertAfter = TVI_LAST );

	void* GetCurObject();
	BOOL SetCurObject( void* pvObject );
	BOOL SelectObject( void* pvObject, BOOL bSelect = TRUE );
	BOOL SetActiveObject( void* pvObject );
	
	INT GetCurPropItemID();
	SPropItem* GetCurPropItem();
	CProp* GetCurProp();
	BOOL SetCurPropItem( INT nID );
	BOOL SetCurPropItemByIndex( INT nIndex );
	BOOL UpdatePropItem();
	BOOL ExpandPropGroup( INT nIndex, BOOL bExpand = TRUE );

	virtual void OnItemSelChange();
	virtual void OnItemSelChanging();

	HTREEITEM ObjectToHTREEITEM( void* pvObject );
	void* HTREEITEMToObject( HTREEITEM hItem );

protected:
	virtual void UpdateObjectSelection();
	virtual void UpdatePropList();
	virtual void ResetPropList( BOOL bDeleteProp = TRUE );

protected:
	static CPtrArray		ms_arpHandler;
	CPropObjectSelComboBox	m_cmbObjectSel;
	CToolBar				m_ToolBar;
	CTabCtrl				m_TabCtrl;
	CPropDesc				m_PropDesc;
	CPropItemListCtrl*		m_pPropItemListCtrl;

	INT						m_nCurPropID;
	INT						m_nCurItemIndex;
						
	void*					m_pvObject;
	CProp*					m_pProp;
	INT						m_nPropID;
	CMultiSelProp			m_msProp;
	PFNOnNotify				m_pfnOnSelNotify;
	void*					m_pvOnSelNotifyParam;

	CMapPtrToPtr			m_mapObjectItem;
	
	friend class CMultiSelProp;
	friend class CPropItemList;
	friend class CPropItemListCtrl;
};

inline void* CPropBox::GetCurObject() {
	return m_pvObject; }

inline CProp* CPropBox::GetCurProp() {
	return m_pProp; }

inline SPropItem* CPropBox::GetCurPropItem() {
	if( m_pProp )
		return m_pProp->GetCurItem(); 
	return NULL; }

inline INT CPropBox::GetCurPropItemID() {
	return m_nCurPropID; }

#endif //___PROP_BOX__PH___