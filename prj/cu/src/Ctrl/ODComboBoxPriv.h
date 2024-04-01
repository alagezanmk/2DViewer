#ifndef ___COMBO_BOX_PRIV__H___
#define ___COMBO_BOX_PRIV__H___

typedef struct CODComboBox::SItem
{
	SItem();
	virtual ~SItem();
	
	CString			cszText;
	DWORD			dwItemData;
	CMapPtrToPtr	mapID_ItemData;
}SItem;

#endif //!___COMBO_BOX_PRIV__H___
