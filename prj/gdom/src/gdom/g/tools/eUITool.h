#ifndef ___G_ELEMENT_UI_TOOL__PH___
#define ___G_ELEMENT_UI_TOOL__PH___

#include "uiTool.h"

class GDOM_EXT_CLASS CGIElementUITool : public CGIUITool
{
	DECL_GTPYECLASS_DYNCREATE(CGIElementUITool)

public:
	CGIElementUITool();
	virtual ~CGIElementUITool();

public:
	virtual void InvalidateRect( BOOL bTracker = FALSE ) const;

	virtual BOOL GetSelection() const;
	virtual void SetSelection( BOOL bSet = TRUE );

	virtual INT GetHitTest() const;
	virtual void SetHitTest( INT nHitTest );

	virtual BOOL GetElementScreenCTM( Matrix& rMtx ) const;

	overrided BOOL OnKeyDown( const CKbdEvent& rEvent );
	overrided BOOL OnKeyUp( const CKbdEvent& rEvent );
	
public:
	CGIElement*	m_piElement;
};

#endif //!___G_ELEMENT_UI_TOOL__PH___
