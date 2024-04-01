#ifndef ___G__UNIT__PH___
#define ___G__UNIT__PH___

class CGUnit
{
public:
	enum UNIT
	{
		UNKNOWN_UNIT	= -1,
		DEF_UNIT		= 0,
		PIXEL_UNIT		= 1,
		POINTS_UNIT		= 2,
		PERCENT_UNIT	= 3,
		INCH_UNIT		= 4,
		CM_UNIT			= 5,
		MM_UNIT			= 6,
		MILS_UNIT		= 7,
	};

public:
	virtual FLOAT PixelValue( FLOAT fValue, FLOAT fAspectRatio = 1.f ) = 0;
	virtual FLOAT UnitValue( FLOAT fValue, FLOAT fAspectRatio = 1.f ) = 0;

public:
	INT	m_nUnit;
};

#endif //!___G__UNIT__PH___