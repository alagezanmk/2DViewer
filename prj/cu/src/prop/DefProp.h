#ifndef ___DEF_PROP__PH____
#define ___DEF_PROP__PH____

#include "Prop.h"

class CDefaultProp : public CProp
{
	DECLARE_PB_PROP_MAP()

public:
	CDefaultProp();
	virtual ~CDefaultProp();

	BOOL OnFileNameBtnClick( SPropItem* psItem );
	BOOL OnFileNameCheck( SPropItem* psItem, PTCHAR ptszName, INT* pnType );

	BOOL OnColorRefBtnClick( SPropItem* psItem );
	BOOL OnColorRefCheck( SPropItem* psItem, PTCHAR ptszName, INT* pnType );
	COLORREF ParseColorRef( SPropItem* psItem, PTCHAR ptszCrf );

public:
	CProp* m_pProp;
};

#endif //!___DEF_PROP__PH____
