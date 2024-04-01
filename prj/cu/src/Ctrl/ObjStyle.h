#ifndef ___OBJ_STYLE__PH___
#define ___OBJ_STYLE__PH___

#include "Style.h"
class CObj;
class CObjBrush : public CStyleBrush
{
private:
	CObjBrush(); ///< Should not used without object pointer

public:
	CObjBrush( const CObj* pObj );
};

class CObjPen : public CStylePen
{
private:
	CObjPen(); ///< Should not used without object pointer

public:
	CObjPen( const CObj* pObj );
};

#endif  ___OBJ_STYLE__PH___
