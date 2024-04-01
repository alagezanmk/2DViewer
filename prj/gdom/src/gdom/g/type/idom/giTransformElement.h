#ifndef ___G_TRANSFROM_ELEMENT__PH___
#define ___G_TRANSFROM_ELEMENT__PH___

#include "giElement.h"
class GDOM_EXT_CLASS CGITransformElement : public CGIElement
{
	DECL_GTPYECLASS_DYNCREATE(CGITransformElement)

public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGITransformElement();

protected:
	overrided ~CGITransformElement();

	overrided void DrawElement( Graphics& rGdip );
	overrided BOOL GetCTM( Matrix& rMtx ) const;
	overrided void InitializeAttributes();

protected:
	CGSAFloatLink m_aRotate;
};

#endif //!___G_TRANSFROM_ELEMENT__PH___
