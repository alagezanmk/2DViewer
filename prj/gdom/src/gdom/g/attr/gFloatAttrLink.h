#ifndef ___G_FLOAT_ATTR_LINK__PH___
#define ___G_FLOAT_ATTR_LINK__PH___

#include "gAttrLink.h"
#include "gFloatAttr.h"

class GDOM_EXT_CLASS CGSAFloatLink : public CGIAttrLink
{
public:
	CGSAFloatLink( LPCTSTR pctszName );

public:
	BOOL operator=( const CString& rcszValue );
	operator FLOAT() const;
	BOOL operator=( FLOAT fValue );
};

#endif //!___G_FLOAT_ATTR_LINK__PH___
