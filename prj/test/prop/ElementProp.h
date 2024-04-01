#ifndef ___ELEMENT_PROP__PH___
#define ___ELEMENT_PROP__PH___

#include <prop\Prop.h>
#include <g\type\idom\giElement.h>

class CElementProp : public CProp, public CGEventTarget
{
public:
	CElementProp();
	virtual ~CElementProp();

	///virtual BOOL GetCursor( INT nMode, UINT& unCursorID, HINSTANCE& hInst );

	SProp* GetElementPropList();
	void AddAttribute( CGIAttrGroup& rGroup );

	//{{AFX_Event_Link
	void OnAttrModifiedEvent( CGMutationEvent& rEvent );
	//}}AFX_Event_Link
	DECLARE_EVENT_LINK()

	///{{ Reimplemented
	virtual void* GetObject();
	virtual void SetObject( void* pvObject );

	virtual INT GetPropCount( INT nTab = -1 );
	virtual SProp* GetPropList( INT nTab = -1 );
	virtual BOOL IsAlphabeticalTab();
	virtual INT GetTabCount();
	virtual BOOL GetDesc( SPropItem* psItem, CString& rcszDesc );
	virtual BOOL GetLabel( SPropItem* psItem, CString& rcszName );
	virtual BOOL GetText( SPropItem* psItem, CString& rcszText );
	virtual BOOL UpdateTextItem( SPropItem* psItem, PTCHAR ptszText );
	/*virtual BOOL InitItemDataPtr( SPropItem* psItem, INT nFlag );

	virtual BOOL UpdateItem( SPropItem* psItem );
	virtual BOOL UpdateIntItem( SPropItem* psItem, INT nInt );
	virtual BOOL UpdateFloatItem( SPropItem* psItem, FLOAT fFloat );*/
	///}} Reimplemented

public:
	CGIElement*				m_pElement;
	CArray<SProp, SProp&>	m_arrsProp;
};

#endif //___ELEMENT_PROP__PH___
