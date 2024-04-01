#ifndef ___G_COORD_F__PH___
#define ___G_COORD_F__PH___

#ifndef _GDIPLUS_H
class PointF
{
public:
	INT X;
	INT Y;
};

class SizeF
{
public:
	FLOAT Width;
	FLOAT Height;
};

class RectF
{
public:
	FLOAT X;
	FLOAT Y;
	FLOAT Width;
	FLOAT Height;
};

#endif //_GDIPLUS_H

#include "gPointF.h"
#include "gRectF.h"
#include "gSizeF.h"

#include "gPointFInl.h"
#include "gRectFInl.h"
#include "gSizeFInl.h"

extern CU_EXT_DATA const PointF nullPointF;
extern CU_EXT_DATA const SizeF nullSizeF;
extern CU_EXT_DATA const RectF nullRectF;

extern CU_EXT_DATA const GPointF nullGPointF;
extern CU_EXT_DATA const GSizeF nullGSizeF;
extern CU_EXT_DATA const GRectF nullGRectF;

#endif //!___G_COORD_F__PH___
