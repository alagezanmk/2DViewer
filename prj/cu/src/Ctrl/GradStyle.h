#ifndef ___GRAD_STYLE__PH___
#define ___GRAD_STYLE__PH___

#include "ObjTfx.h"
#include "Style.h"
#include "ObjDataType.h"

class CGradientStyle : public CStyle
{
	class CData1 : public CStyle::CData
	{
		int ninde;
	};

	enum EnGradientType
	{
		enLinear,
		enRadial
	};

	enum EnGradientUnits
	{
		enUserSpace,
		enBoundObject
	};

	enum EnSpreadMethod
	{
		enRepeat,
		enReflect,
		enPad
	};

public:
	CGradientStyle();
	CGradientStyle( const CGradientStyle& sGrad );
	CGradientStyle& operator=( const CGradientStyle& sGrad );
	BOOL operator==( CGradientStyle& sGrad );
	Brush* CreateBrush( RectF bound, float fOpacity, float fCanWd, float fCanHt );

	ARGB GetColor( CString cszCol );
	float GetStop( CString cszPer );
	//int GetColor( CString cszSvgCol );

public:
	EnGradientType			m_enType;
	EnGradientUnits			m_enUnits;
	CArrPSObjTfx			m_carpTfx;
	EnSpreadMethod			m_enSpreadMethod;
	CArrColor				m_arcColor;
	CArrFLOAT				m_arfStop;

	union
	{
		struct
		{
			float	x1;
			float	y1;
			float	x2;
			float	y2;
		};

		struct 
		{
			float	cx;
			float	cy;
			float	fx;
			float	fy;
			float	r;
		};
	};
};

#endif //!___GRAD_STYLE__PH___