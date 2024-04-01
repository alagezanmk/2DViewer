#ifndef ___G_COORD__PH___
#define ___G_COORD__PH___

#include "gUnit.h"

#ifndef _GDIPLUSTYPES_H
class Point
{
public:
	INT X;
	INT Y;
};

class Size
{
public:
	INT Width;
	INT Height;
};

class Rect
{
public:
	FLOAT X;
	FLOAT Y;
	FLOAT Width;
	FLOAT Height;
};

#endif 

#include "gPoint.h"
#include "gRect.h"
#include "gSize.h"

#include "gPointInl.h"
#include "gRectInl.h"
#include "gSizeInl.h"

#include "gCoordF.h"

extern CU_EXT_DATA const POINT nullPOINT;
extern CU_EXT_DATA const SIZE nullSIZE;
extern CU_EXT_DATA const RECT nullRECT;

/*extern CU_EXT_DATA const Point nullPoint;
extern CU_EXT_DATA const Size nullSize;
extern CU_EXT_DATA const Rect nullRect;*/

//extern CU_EXT_DATA const GPoint nullGPoint;
//extern CU_EXT_DATA const GSize nullGSize;
//extern CU_EXT_DATA const GRect nullGRect;

#endif //!___G_COORD__PH___