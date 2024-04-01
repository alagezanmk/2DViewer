#ifndef ___G_SHAPE_ELEMENT__PH___
#define ___G_SHAPE_ELEMENT__PH___

#include "giElement.h"

class GDOM_EXT_CLASS CGIShapeElement : public CGIElement
{
	DECL_GTPYECLASS_DYNCREATE(CGIShapeElement)

public:
	enum UI_MODE { 
		NONE_UI_MODE = 0,
	};

	enum UI_STATE { 
		NONE_UI_STATE = 0, 
	};

	enum {       
		HT_ELEMENT = 0xFFFFFFFE,
	};

public:
	CGIShapeElement();

protected:
	overrided ~CGIShapeElement();

public:
	virtual void UpdateCTM( Matrix& rMtx );

	overrided  void Update();
	overrided BOOL GetCTM( Matrix& rMtx ) const;
	overrided BOOL GetDrawBBox( GRectF& rBBox, Matrix* pmtx = NULL ) const;

protected:
	mutable CGRectF		m_grctfDrawBBox;
	Matrix				m_mtx;

	INT					m_nUIState;			/// Current UI Mode's state
	UINT				m_nHitTest;
};

#endif //!___G_SHAPE_ELEMENT__PH___
