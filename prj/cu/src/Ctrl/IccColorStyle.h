#ifndef ___ICC_COLOR_STYLE__PH___
#define ___ICC_COLOR_STYLE__PH___

#include "ObjStyle.h"

struct SIccColor
{
	TCHAR	tszName[30];
	ARGB	cColor;
};

extern const SIccColor g_sIccColor[];
extern const INT g_cnIccColorCnt;

INT GetIccColorIndex( LPCTSTR ptszIccName );

#endif //!___ICC_COLOR_STYLE__PH___