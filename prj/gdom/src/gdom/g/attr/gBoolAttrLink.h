#ifndef ___G_BOOL_ATTR_lstrnicmp__PH___
#define ___G_BOOL_ATTR_LINK__PH___

#include "gAttrLink.h"
#include "gBoolAttr.h"

class GDOM_EXT_CLASS CGSABoolLink : public CGIAttrLink
{
public:
	CGSABoolLink( LPCTSTR pctszName );

public:
	BOOL operator=( const CString& rcszValue );
	BOOL operator=( BOOL bValue );
	operator BOOL() const;
};

#endif //!___G_BOOL_ATTR_LINK__PH___
