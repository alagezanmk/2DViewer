#ifndef ___G_LINE_ELEMENT__PH___
#define ___G_LINE_ELEMENT__PH___

#include "giShapeElement.h"
#include <g\attr\gFloatAttrLink.h>

//////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGILineElement : public  CGIShapeElement
{
	DECL_GTPYECLASS_DYNCREATE(CGILineElement)

public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGILineElement();

protected:
	virtual ~CGILineElement();
	overrided void InitializeAttributes();

public:
	virtual void DrawElement( Graphics& rGdip );
	overrided LPCTSTR GetTagName() const;

	overrided UINT HitTest( const PointF& rptf );
	virtual UINT HitTest( const Region& rrgn );

	overrided BOOL GetRect( GRectF& rBBox ) const;

public:
	CGSAFloatLink	m_aX1;
	CGSAFloatLink	m_aY1;
	CGSAFloatLink	m_aX2;
	CGSAFloatLink	m_aY2;
};

inline LPCTSTR CGILineElement::GetTagName() const {
	return ELEMENT_TAGNAME; }

#endif //!___G_LINE_ELEMENT__PH___
