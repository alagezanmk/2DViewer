#include "stdafx.h"
#include "IccColorStyle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const SIccColor g_sIccColor[] =
{
	{ _T("aliceblue"),				MAKE_ARGB(255, 240, 248, 255) },
	{ _T("antiquewhite"),			MAKE_ARGB(255, 250, 235, 215) },
	{ _T("aqua"),					MAKE_ARGB(255, 0,   255, 255) },
	{ _T("aquamarine"),				MAKE_ARGB(255, 127, 255, 212) },
	{ _T("azure"),					MAKE_ARGB(255, 240, 255, 255) },
	{ _T("beige"),					MAKE_ARGB(255, 245, 245, 220) },
	{ _T("bisque"),					MAKE_ARGB(255, 255, 228, 196) },
	{ _T("black"),					MAKE_ARGB(255, 0,   0,	 0  ) },
	{ _T("blanchedalmond"),			MAKE_ARGB(255, 255, 235, 205) },
	{ _T("blue"),					MAKE_ARGB(255, 0,   0,	 255) },
	{ _T("blueviolet"),				MAKE_ARGB(255, 138, 43,  226) },
	{ _T("brown"),					MAKE_ARGB(255, 165, 42,  42 ) },
	{ _T("burlywood"),				MAKE_ARGB(255, 222, 184, 135) },
	{ _T("cadetblue"),				MAKE_ARGB(255, 95,  158, 160) },
	{ _T("chartreuse"),				MAKE_ARGB(255, 127, 255, 0  ) },
	{ _T("chocolate"),				MAKE_ARGB(255, 210, 105, 30 ) },
	{ _T("coral"),					MAKE_ARGB(255, 255, 127, 80 ) },
	{ _T("cornflowerblue"),			MAKE_ARGB(255, 100, 149, 237) },
	{ _T("cornsilk"),				MAKE_ARGB(255, 255, 248, 220) },
	{ _T("crimson"),				MAKE_ARGB(255, 220, 20,  60 ) },
	{ _T("cyan"),					MAKE_ARGB(255, 0,   255, 255) },
	{ _T("darkblue"),				MAKE_ARGB(255, 0,   0,   139) },
	{ _T("darkcyan"),				MAKE_ARGB(255, 0,   139, 139) },
	{ _T("darkgoldenrod"),			MAKE_ARGB(255, 184, 134, 11 ) },
	{ _T("darkgray"),				MAKE_ARGB(255, 169, 169, 169) },
	{ _T("darkgreen"),				MAKE_ARGB(255, 0,   100, 0  ) },
	{ _T("darkgrey"),				MAKE_ARGB(255, 169, 169, 169) },
	{ _T("darkkhaki"),				MAKE_ARGB(255, 189, 183, 107) },
	{ _T("darkmagenta"),			MAKE_ARGB(255, 139, 0,   139) },
	{ _T("darkolivegreen"),			MAKE_ARGB(255, 85,  107, 47 ) },
	{ _T("darkorange"),				MAKE_ARGB(255, 255, 140, 0  ) },
	{ _T("darkorchid"),				MAKE_ARGB(255, 153, 50,  204) },
	{ _T("darkred"),				MAKE_ARGB(255, 139, 0,   0  ) },
	{ _T("darksalmon"),				MAKE_ARGB(255, 233, 150, 122) },
	{ _T("darkseagreen"),			MAKE_ARGB(255, 143, 188, 143) },
	{ _T("darkslateblue"),			MAKE_ARGB(255, 72,  61,  139) },
	{ _T("darkslategray"),			MAKE_ARGB(255, 47,  79,  79 ) },
	{ _T("darkslategrey"),			MAKE_ARGB(255, 47,  79,  79 ) },
	{ _T("darkturquoise"),			MAKE_ARGB(255, 0,   206, 209) },
	{ _T("darkviolet"),				MAKE_ARGB(255, 148, 0,   211) },
	{ _T("deeppink"),				MAKE_ARGB(255, 255, 20,  147) },
	{ _T("deepskyblue"),			MAKE_ARGB(255, 0,   191, 255) },
	{ _T("dimgray"),				MAKE_ARGB(255, 105, 105, 105) },
	{ _T("dimgrey"),				MAKE_ARGB(255, 105, 105, 105) },
	{ _T("dodgerblue"),				MAKE_ARGB(255, 30,  144, 255) },
	{ _T("firebrick"),				MAKE_ARGB(255, 178, 34,  34 ) },
	{ _T("floralwhite"),			MAKE_ARGB(255, 255, 250, 240) },
	{ _T("forestgreen"),			MAKE_ARGB(255, 34,  139, 34 ) },
	{ _T("fuchsia"),				MAKE_ARGB(255, 255, 0,   255) },
	{ _T("gainsboro"),				MAKE_ARGB(255, 220, 220, 220) },
	{ _T("ghostwhite"),				MAKE_ARGB(255, 248, 248, 255) },
	{ _T("gold"),					MAKE_ARGB(255, 255, 215, 0  ) },
	{ _T("goldenrod"),				MAKE_ARGB(255, 218, 165, 32 ) },
	{ _T("gray"),					MAKE_ARGB(255, 128, 128, 128) },
	{ _T("grey"),					MAKE_ARGB(255, 128, 128, 128) },
	{ _T("green"),					MAKE_ARGB(255, 0,   128, 0  ) },
	{ _T("greenyellow"),			MAKE_ARGB(255, 173, 255, 47 ) },
	{ _T("honeydew"),				MAKE_ARGB(255, 240, 255, 240) },
	{ _T("hotpink"),				MAKE_ARGB(255, 255, 105, 180) },
	{ _T("indianred"),				MAKE_ARGB(255, 205, 92,  92 ) },
	{ _T("indigo"),					MAKE_ARGB(255, 75,  0,   130) },
	{ _T("ivory"),					MAKE_ARGB(255, 255, 255, 240) },
	{ _T("khaki"),					MAKE_ARGB(255, 240, 230, 140) },
	{ _T("lavender"),				MAKE_ARGB(255, 230, 230, 250) },
	{ _T("lavenderblush"),			MAKE_ARGB(255, 255, 240, 245) },
	{ _T("lawngreen"),				MAKE_ARGB(255, 124, 252, 0  ) },
	{ _T("lemonchiffon"),			MAKE_ARGB(255, 255, 250, 205) },
	{ _T("lightblue"),				MAKE_ARGB(255, 173, 216, 230) },
	{ _T("lightcoral"),				MAKE_ARGB(255, 240, 128, 128) },
	{ _T("lightcyan"),				MAKE_ARGB(255, 224, 255, 255) },
	{ _T("lightgoldenrodyellow"),	MAKE_ARGB(255, 250, 250, 210) },
	{ _T("lightgray"),				MAKE_ARGB(255, 211, 211, 211) },
	{ _T("lightgreen"),				MAKE_ARGB(255, 144, 238, 144) },
	{ _T("lightgrey"),				MAKE_ARGB(255, 211, 211, 211) },
	{ _T("lightpink"),				MAKE_ARGB(255, 255, 182, 193) },
	{ _T("lightsalmon"),			MAKE_ARGB(255, 255, 160, 122) },
	{ _T("lightseagreen"),			MAKE_ARGB(255, 32,  178, 170) },
	{ _T("lightskyblue"),			MAKE_ARGB(255, 135, 206, 250) },
	{ _T("lightslategray"),			MAKE_ARGB(255, 119, 136, 153) },
	{ _T("lightslategrey"),			MAKE_ARGB(255, 119, 136, 153) },
	{ _T("lightsteelblue"),			MAKE_ARGB(255, 176, 196, 222) },
	{ _T("lightyellow"),			MAKE_ARGB(255, 255, 255, 224) },
	{ _T("lime"),					MAKE_ARGB(255, 0,   255, 0  ) },
	{ _T("limegreen"),				MAKE_ARGB(255, 50,  205, 50 ) },
	{ _T("linen"),					MAKE_ARGB(255, 250, 240, 230) },
	{ _T("magenta"),				MAKE_ARGB(255, 255, 0,   255) },
	{ _T("maroon"),					MAKE_ARGB(255, 128, 0,   0  ) },
	{ _T("mediumaquamarine"),		MAKE_ARGB(255, 102, 205, 170) },
	{ _T("mediumblue"),				MAKE_ARGB(255, 0,	0,   205) },
	{ _T("mediumorchid"),			MAKE_ARGB(255, 186, 85,  211) },
	{ _T("mediumpurple"),			MAKE_ARGB(255, 147, 112, 219) },
	{ _T("mediumseagreen"),			MAKE_ARGB(255, 60,  179, 113) },
	{ _T("mediumslateblue"),		MAKE_ARGB(255, 123, 104, 238) },
	{ _T("mediumspringgreen"),		MAKE_ARGB(255, 0,   250, 154) },
	{ _T("mediumturquoise"),		MAKE_ARGB(255, 72,  209, 204) },
	{ _T("mediumvioletred"),		MAKE_ARGB(255, 199, 21,  133) },
	{ _T("midnightblue"),			MAKE_ARGB(255, 25,  25,  112) },
	{ _T("mintcream"),				MAKE_ARGB(255, 245, 255, 250) },
	{ _T("mistyrose"),				MAKE_ARGB(255, 255, 228, 225) },
	{ _T("moccasin"),				MAKE_ARGB(255, 255, 228, 181) },
	{ _T("navajowhite"),			MAKE_ARGB(255, 255, 222, 173) },
	{ _T("navy"),					MAKE_ARGB(255, 0,	0,   128) },
	{ _T("oldlace"),				MAKE_ARGB(255, 253, 245, 230) },
	{ _T("olive"),					MAKE_ARGB(255, 128, 128, 0  ) },
	{ _T("olivedrab"),				MAKE_ARGB(255, 107, 142, 35 ) },
	{ _T("orange"),					MAKE_ARGB(255, 255, 165, 0  ) },
	{ _T("orangered"),				MAKE_ARGB(255, 255, 69,  0  ) },
	{ _T("orchid"),					MAKE_ARGB(255, 218, 112, 214) },
	{ _T("palegoldenrod"),			MAKE_ARGB(255, 238, 232, 170) },
	{ _T("palegreen"),				MAKE_ARGB(255, 152, 251, 152) },
	{ _T("paleturquoise"),			MAKE_ARGB(255, 175, 238, 238) },
	{ _T("palevioletred"),			MAKE_ARGB(255, 219, 112, 147) },
	{ _T("papayawhip"),				MAKE_ARGB(255, 255, 239, 213) },
	{ _T("peachpuff"),				MAKE_ARGB(255, 255, 218, 185) },
	{ _T("peru"),					MAKE_ARGB(255, 205, 133, 63 ) },
	{ _T("pink"),					MAKE_ARGB(255, 255, 192, 203) },
	{ _T("plum"),					MAKE_ARGB(255, 221, 160, 221) },
	{ _T("powderblue"),				MAKE_ARGB(255, 176, 224, 230) },
	{ _T("purple"),					MAKE_ARGB(255, 128, 0,   128) },
	{ _T("red"),					MAKE_ARGB(255, 255, 0,	 0  ) },
	{ _T("rosybrown"),				MAKE_ARGB(255, 188, 143, 143) },
	{ _T("royalblue"),				MAKE_ARGB(255, 65,	105, 225) },
	{ _T("saddlebrown"),			MAKE_ARGB(255, 139, 69,	 19 ) },
	{ _T("salmon"),					MAKE_ARGB(255, 250, 128, 114) },
	{ _T("sandybrown"),				MAKE_ARGB(255, 244, 164, 96 ) },
	{ _T("seagreen"),				MAKE_ARGB(255, 46,	139, 87 ) },
	{ _T("seashell"),				MAKE_ARGB(255, 255, 245, 238) },
	{ _T("sienna"),					MAKE_ARGB(255, 160, 82,  45 ) },
	{ _T("silver"),					MAKE_ARGB(255, 192, 192, 192) },
	{ _T("skyblue"),				MAKE_ARGB(255, 135, 206, 235) },
	{ _T("slateblue"),				MAKE_ARGB(255, 106, 90,  205) },
	{ _T("slategray"),				MAKE_ARGB(255, 112, 128, 144) },
	{ _T("slategrey"),				MAKE_ARGB(255, 112, 128, 144) },
	{ _T("snow"),					MAKE_ARGB(255, 255, 250, 250) },
	{ _T("springgreen"),			MAKE_ARGB(255, 0,	255, 127) },
	{ _T("steelblue"),				MAKE_ARGB(255, 70,	130, 180) },
	{ _T("tan"),					MAKE_ARGB(255, 210, 180, 140) },
	{ _T("teal"),					MAKE_ARGB(255, 0,	128, 128) },
	{ _T("thistle"),				MAKE_ARGB(255, 216, 191, 216) },
	{ _T("tomato"),					MAKE_ARGB(255, 255, 99,  71 ) },
	{ _T("turquoise"),				MAKE_ARGB(255, 64,	224, 208) },
	{ _T("violet"),					MAKE_ARGB(255, 238, 130, 238) },
	{ _T("wheat"),					MAKE_ARGB(255, 245, 222, 179) },
	{ _T("white"),					MAKE_ARGB(255, 255, 255, 255) },
	{ _T("whitesmoke"),				MAKE_ARGB(255, 245, 245, 245) },
	{ _T("yellow"),					MAKE_ARGB(255, 255, 255, 0  ) },
	{ _T("yellowgreen"),			MAKE_ARGB(255, 154, 205, 50 ) },
	//nine more colors repeated
	{ _T("darkkhaki"),				MAKE_ARGB(255, 189, 183, 107) },
	{ _T("darkmagenta"),			MAKE_ARGB(255, 139, 0,   139) },
	{ _T("darkolivegreen"),			MAKE_ARGB(255, 85,	107, 47 ) },
	{ _T("darkorange"),				MAKE_ARGB(255, 255, 140, 0  ) },
	{ _T("darkorchid"),				MAKE_ARGB(255, 153, 50,  204) },
	{ _T("darkred"),				MAKE_ARGB(255, 139, 0,   0  ) },
	{ _T("darksalmon"),				MAKE_ARGB(255, 233, 150, 122) },
};

const INT g_cnIccColorCnt = sizeof(g_sIccColor) / sizeof(SIccColor );

///////////////////////////////////////////////////////////////////////////////////////////////////
class CIccColorStyleCreator : public CStyleCreator
{
public:
	CIccColorStyleCreator();

	virtual Pen* CreatePen( CStylePen& rPen, const CStyle& rStyle, FLOAT fParentOpacity = 1.0f, const RectF& rrctF = nullRectF );
	virtual Brush* CreateBrush( CStyleBrush& rBrush, const CStyle& rStyle, FLOAT fParentOpacity = 1.0f, const RectF& rrctF = nullRectF );

	virtual FLOAT GetAlpha( const CStyle& rStyle );

	virtual void GetStyleText( const CStyle& rStyle, CString& rcszText );
	virtual BOOL SetStyleByText( CStyle& rStyle, LPCTSTR ptszText );
};

static CIccColorStyleCreator oneIccColorStyleCreator;
void AddIccColorStyleCreator()
{
	CStyle::AddStyleCreator( enObjStyleIccColor, &oneIccColorStyleCreator );
}

CIccColorStyleCreator::CIccColorStyleCreator()
{}

Pen* CIccColorStyleCreator::CreatePen( CStylePen& rPen, const CStyle& rStyle, FLOAT fParentOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	if( enObjStyleIccColor == rStyle.m_wType )
	{
		ASSERT( rStyle.m_nIndex >= 0 && rStyle.m_nIndex < g_cnIccColorCnt );
		VERIFY( rPen.m_pPen = CreateGdipPen( OBJ_COLOR(g_sIccColor[rStyle.m_nIndex].cColor, rStyle.m_fOpacity * fParentOpacity) ) );
		if( NULL == rPen.m_pPen )
			return NULL;

		return rPen.m_pPen;
	}

	// This is not creator of the m_wType
	ASSERT( NULL );
	return NULL;
}

Brush* CIccColorStyleCreator::CreateBrush( CStyleBrush& rBrush, const CStyle& rStyle, FLOAT fParentOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	if( enObjStyleIccColor == rStyle.m_wType )
	{
		ASSERT( rStyle.m_nIndex >= 0 &&  rStyle.m_nIndex < g_cnIccColorCnt );
		VERIFY( rBrush.m_pBrush = CreateGdipSolidBrush( OBJ_COLOR(g_sIccColor[rStyle.m_nIndex].cColor, rStyle.m_fOpacity * fParentOpacity) ) );
		if( NULL == rBrush.m_pBrush )
			return NULL;

		return rBrush.m_pBrush;
	}

	// This is not a creator for this m_wType 
	ASSERT( NULL );
	return NULL;
}

FLOAT CIccColorStyleCreator::GetAlpha( const CStyle& rStyle ) {
	return ARGB_ALPHA(g_sIccColor[rStyle.m_nIndex].cColor) / 255.0f; }

void CIccColorStyleCreator::GetStyleText( const CStyle& rStyle, CString& rcszText )
{
	if( enObjStyleIccColor == rStyle.m_wType )
	{
		INT nIndex = rStyle.m_nIndex;
		ASSERT( nIndex >= 0 &&  nIndex < g_cnIccColorCnt );
		rcszText = g_sIccColor[nIndex].tszName;
		return;
	}

	// This is not a creator for this m_wType 
	ASSERT( FALSE );
}

BOOL CIccColorStyleCreator::SetStyleByText( CStyle& rStyle, LPCTSTR ptszText )
{
	INT nIndex = GetIccColorIndex( ptszText );
	if( nIndex >= 0 )
	{
		rStyle.m_nIndex = nIndex;
		return TRUE;
	}

	ASSERT( FALSE );
	return FALSE;
}

INT GetIccColorIndex( LPCTSTR ptszIccName )
{
	for( INT i = 0; i < g_cnIccColorCnt; i++ )
		if( 0 == lstrcmp( ptszIccName, g_sIccColor[i].tszName ) )
			return i;

	ASSERT( FALSE );
	return -1;
}