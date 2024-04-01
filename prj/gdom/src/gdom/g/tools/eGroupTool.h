#ifndef ___G_ELEMENT_GROUP_TOOL__PH___
#define ___G_ELEMENT_GROUP_TOOL__PH___

#include "eTool.h"

class CGIGroupElementTool : public CGIElementTool
{
public:
	enum UI_MODE { 
		GROUP_TOOL_UI_MODE = 256,
	};

public:
	CGIGroupElementTool();
	virtual ~CGIGroupElementTool();

public:
	CGIElementUITool* GetElementTool( CGIElement& rElement );
	BOOL AddTool( CGIElementUITool& rTool );
	BOOL RemoveTool( CGIElementUITool& rTool );

	///{{ Reimplemented
	virtual INT GetDrawType() const;
	virtual BOOL Draw( CDC& rDC, RECT& rRect );
	overrided UINT HitTest( const CPoint& rpoint );
	virtual void GetBBox( GRectF& rrctf ) const;
	virtual const GRectF& GetBBox() const;

	overrided void InvalidateRect( BOOL bTracker = FALSE ) const;
	///}} Reimplemented

public:
	CPtrArray		m_arpTool;
};

#endif //!___G_ELEMENT_GROUP_TOOL__PH___
