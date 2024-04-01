#ifndef ___G_CONTAINER__PH___
#define ___G_CONTAINER__PH___

#include "giGroup.h"

class GDOM_EXT_CLASS CGIViewPort : public CGIGroup
{
	DECL_GTPYECLASS_DYNCREATE(CGIViewPort)

public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGIViewPort();

protected:
	virtual ~CGIViewPort();

public:
	virtual void Draw( Graphics& rGdip );
	virtual void DrawContainer( Graphics& rGdip );
	overrided void UpdateCTM( Matrix& rMtx );

	virtual void GetClipRect( RectF& rrcf ) const;
	overrided BOOL GetRect( GRectF& rBBox ) const;

protected:
	overrided void InitializeAttributes();

public:
	CGSAFloatLink	m_aX;
	CGSAFloatLink	m_aY;
	CGSAFloatLink	m_aWidth;
	CGSAFloatLink	m_aHeight;
	CGSABoolLink	m_aEnableClip;
};

#endif //!___G_CONTAINER__PH___
