#ifndef ___G_POINT_F_ATTR_LINK__PH___
#define ___G_POINT_F_ATTR_LINK__PH___

#include "gAttrLink.h"
#include "gPointFAttr.h"

class GDOM_EXT_CLASS CGSAPointFLink : public CGIAttrLink
{
public:
	CGSAPointFLink( LPCTSTR pctszName );

public:
	BOOL operator=( const CString& rcszValue );
	BOOL operator=( const GPointF& rgptfValue );
	operator const GPointF&() const;

	virtual void Get( FLOAT& rfX, FLOAT& rfY ) const;
	virtual BOOL Set( FLOAT fX, FLOAT fY );
};

#endif //!___G_POINT_F_ATTR_LINK__PH___
