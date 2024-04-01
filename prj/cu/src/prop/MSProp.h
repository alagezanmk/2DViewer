#ifndef ___MULTI_SEL_PROP__PH___
#define ___MULTI_SEL_PROP__PH___

#include "Prop.h"

class CPropBox;
class CMultiSelProp : public CProp
{
public:
	CMultiSelProp( CPropBox& rPropCtrl );
	virtual ~CMultiSelProp();

public:
	// Handler functions
	virtual void SetCurItem( SPropItem* psItem );

	virtual BOOL GetLabel( SPropItem* psItem, CString& rcszName );
	virtual BOOL GetDesc( SPropItem* psItem, CString& rcszDesc );
	virtual BOOL GetText( SPropItem* psItem, CString& rcszText, BOOL* pbMultiple = NULL );
	virtual void UpdateText();
	virtual void UpdateText( INT nID );

	virtual BOOL EditChange( SPropItem* psItem );
	virtual BOOL UpdateItem( SPropItem* psItem );

	virtual BOOL BtnClick( SPropItem* psItem );

	virtual BOOL FillCombo( SPropItem* psItem );
	virtual BOOL UpdateCombo( SPropItem* psItem );
	virtual BOOL ComboSelChange( SPropItem* psItem, CMSComboBox::NMSELCHANGE* pNotifyStruct, LRESULT* plResult );
	virtual BOOL SetComboSel( SPropItem* psItem );
	virtual BOOL ComboCancel( SPropItem* psItem );

	CProp* CreateProp( SPropHandler* psHandler, BOOL bAdd = TRUE );
	void DeleteProp( CProp* pProp );
	void DeleteAllProp();
	void RemoveAllProp();
	void AddProp( CProp* pProp );
	BOOL RemoveProp( CProp* pProp );

	void CreateCommonItemList();

public:
	CPtrArray		m_arpProp;
	CPropBox&		m_rPropCtrl;
};

#endif //!___MULTI_SEL_PROP__PH___
