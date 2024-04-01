#ifndef ___G_COLOR_ATTR__PH___
#define ___G_COLOR_ATTR__PH___

#include "gAttr.h"

class GDOM_EXT_CLASS CGIColor
{
public:
	Color		m_argba;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGIPColor : public CGIAttr
{
public:
	CGIPColor();
	virtual ~CGIPColor();

public:
	const CGIColor& Get() const;
	BOOL Set( const CGIColor& rcValue );

protected:
	CGIColor		m_color;
};

class GDOM_EXT_CLASS CGIPArrColor: public CGIAttrArray
{
public:
	CGIPArrColor();
	virtual ~CGIPArrColor();

public:
	CGIColor* GetList();
	const CGIColor* GetList() const;
	const CGIColor& GetAt( INT nIndex ) const;
	BOOL SetAt( INT nIndex, const CGIColor& rcValue, INT nCount = 1 );
	BOOL InsertAt( INT nIndex, const CGIColor& rcValue, INT nCount = 1 );
	BOOL RemoveAt( INT nIndex, INT nCount = 1 );

protected:
	CArray<CGIColor, const CGIColor&> m_arrColor;
};

#endif //!___G_COLOR_ATTR__PH___
