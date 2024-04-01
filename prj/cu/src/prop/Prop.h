#ifndef ___PROP__PH___
#define ___PROP__PH___

#include "PropDef.h"
#include "PropBtn.h"
#include "PropEdit.h"
#include "PropComboBox.h"
#include "PropMSComboBox.h"

class CPropBox;

#define ID_PROP_EDIT		100
#define ID_PROP_COMBO		101
#define ID_PROP_BTN			102

#define PBR_SETFOCUS		2

///////////////////////////////////////////////////////////////////////////////////////////////////
typedef CProp* (*PFNPropHandler)( INT nID );
struct SPropHandler
{
	PFNPropHandler		pfnPropHandler;
	INT					nID;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CProp : public CWnd
{
	DECLARE_MESSAGE_MAP()
	DECLARE_PB_PROP_MAP()

public:
	static CPropEdit*		m_pedtProp;
	static CPropComboBox*	m_pcmbProp;
	static CPropMSComboBox*	m_pcmbMSProp;
	static CPropBtn*		m_pbtnProp;
	static CWnd*			m_pwnddynProp;

public:
	CProp();
	virtual ~CProp();

	virtual void* GetObject();
	virtual void SetObject( void* pvObject );
	virtual BOOL IsAlphabeticalTab();
	virtual void CreateAlphabeticPropList();
	virtual void CreatePropList( INT nTab = -1 );

	virtual INT GetTabCount();
	virtual void GetTabText( INT nTab, CString& rcszText );
	virtual CDialog* GetTabDlg( INT nTab );

	// Prop functions
	virtual INT GetPropCount( INT nTab = -1 );
	virtual SProp* GetPropList( INT nTab = -1 );

	virtual INT FoldPropGroup( INT nID, BOOL bFold = TRUE );
	virtual INT GetItemIndex( INT nID, INT* pnPropIndex = NULL );

	// Item functions
	virtual INT CreateAllItemList();
	virtual INT CreateItemList();
	virtual void DeleteItemList();

	SPropItem** GetAllItemList();
	INT GetAllItemListCount();

	SPropItem** GetItemList();
	INT GetItemListCount();

	virtual SPropItem* GetItemAt( INT nIndex );
	virtual SPropItem* GetItem( INT nID, INT* pnIndex = NULL );
	virtual INT FoldItemGroup( INT nIndex, BOOL bFold = TRUE );

	// Handler functions
	SPropItem* GetCurItem();
	virtual void SetCurItem( SPropItem* psItem );
	CProp* GetDefProp();
	LONG SendPropMsg( UINT nMsg, UINT nCode = 0, UINT nID = 0, UINT nData = 0, UINT nData1 = 0, UINT nData2 = 0 );

	virtual void AddUserItem();
	virtual void DeleteUserItem();

	virtual CPropEdit* CreatePropEdit( SPropItem* psItem, DWORD dwStyle, CRect rct, CWnd* pParent, INT nID );
	virtual CPropBtn* CreatePropBtn( SPropItem* psItem, PTCHAR ptszCaption, DWORD dwStyle, CRect rct, CWnd* pParent, INT nID );
	virtual CPropMSComboBox* CreatePropCombo( SPropItem* psItem, INT nCtrlCy, DWORD dwStyle, CRect rct, CWnd* pParent, INT nID );

	virtual void CreateDynItemCtrl( SPropItem* psItem, CWnd* pParent, CRect rct );
	virtual void DeleteDynItemCtrl( SPropItem* psItem );

	virtual void CreateStaticCtrl( SPropItem* psItem, CWnd* pParent, CRect rct );
	virtual void DeleteStaticCtrl( SPropItem* psItem );
	virtual void ShowStaticCtrl( SPropItem* psItem, BOOL bShow = TRUE );
	virtual void MoveStaticCtrl( SPropItem* psItem, CRect rct );
	
	virtual void InitItemStruct();
	virtual void InitItemStruct( SPropItem* psItem, INT nFlag );
	virtual BOOL InitItemDataPtr( SPropItem* psItem, INT nFlag );

	virtual HINSTANCE GetResourceHandle();
	virtual BOOL GetResourceString( INT nID, CString& rcszString, BOOL bLocal = FALSE );
	virtual void ParseLabelString( CString& rcszString );
	virtual void ParseDescString( CString& rcszString );

	virtual BOOL GetLabel( SPropItem* psItem, CString& rcszName );
	virtual BOOL GetDesc( SPropItem* psItem, CString& rcszDesc );
	virtual BOOL GetText( SPropItem* psItem, CString& rcszText );
	virtual void UpdateText();
	virtual void UpdateText( INT nID );

	virtual BOOL EditChange( SPropItem* psItem );
	virtual BOOL UpdateItem( SPropItem* psItem );
	virtual BOOL UpdateTextItem( SPropItem* psItem, PTCHAR ptszText );
	virtual BOOL UpdateIntItem( SPropItem* psItem, INT nInt );
	virtual BOOL UpdateFloatItem( SPropItem* psItem, FLOAT fFloat );
	virtual BOOL UpdateDoubleItem( SPropItem* psItem, DOUBLE dfDouble );

	virtual BOOL BtnClick( SPropItem* psItem );
	
	virtual BOOL FillCombo( SPropItem* psItem );
	virtual BOOL SetComboSel( SPropItem* psItem );
	virtual BOOL ComboSelChange( SPropItem* psItem, CMSComboBox::NMSELCHANGE* pNotifyStruct, LRESULT* plResult );
	virtual BOOL UpdateCombo( SPropItem* psItem );
	virtual BOOL ComboCancel( SPropItem* psItem );

	const CPtrArray& GetAllItemArray();
	const CPtrArray& GetItemArray();

	INT GetError();

protected:
	void SetError( INT nError );

protected:
	INT			m_nError;
	INT			m_nPropListCnt;
	SProp*		m_psPropList;
	SPropItem*	m_parsItem;

public:
	CPtrArray	m_arpAllItem;
	CPtrArray	m_arpItem;

	SPropItem*	m_psCurItem;
	CPropBox*	m_pPropCtrl;
};

inline INT CProp::GetError() {
	return m_nError; }

inline void CProp::SetError( INT nError ) {
	m_nError = nError; }

inline SPropItem** CProp::GetAllItemList() {
	return (SPropItem**)m_arpAllItem.GetData(); }

inline INT CProp::GetAllItemListCount() {
	return m_arpAllItem.GetSize(); }

inline SPropItem** CProp::GetItemList() {
	return (SPropItem**)m_arpItem.GetData(); }

inline const CPtrArray& CProp::GetItemArray() {
	return m_arpItem; }

inline INT CProp::GetItemListCount() {
	return m_arpItem.GetSize(); }

inline const CPtrArray& CProp::GetAllItemArray() {
	return m_arpAllItem; }

inline SPropItem* CProp::GetCurItem() {
	return m_psCurItem; }

#endif //___PROP__PH___
