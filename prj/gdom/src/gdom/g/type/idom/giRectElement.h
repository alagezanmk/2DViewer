#ifndef ___G_RECT_ELEMENT__PH___
#define ___G_RECT_ELEMENT__PH___

#include "giShapeElement.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGIRectElement : public  CGIShapeElement
{
	DECL_GTPYECLASS_DYNCREATE(CGIRectElement)

public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGIRectElement();

protected:
	virtual ~CGIRectElement();
	overrided void InitializeAttributes();

public:
	virtual void DrawElement( Graphics& rGdip );
	overrided LPCTSTR GetTagName() const;

	overrided UINT HitTest( const PointF& rptf );
	virtual UINT HitTest( const Region& rrgn );

	overrided BOOL GetRect( GRectF& rBBox ) const;

public:
	CGSAFloatLink	m_aX;
	CGSAFloatLink	m_aY;
	CGSAFloatLink	m_aWidth;
	CGSAFloatLink	m_aHeight;
};

inline LPCTSTR CGIRectElement::GetTagName() const {
	return ELEMENT_TAGNAME; }

#endif //!___G_RECT_ELEMENT__PH___
