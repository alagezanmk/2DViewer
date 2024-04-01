#ifndef ___STYLE__PH___
#define ___STYLE__PH___

#include <gl\gl.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Style Type enum
typedef enum
{
	enObjStyleNotSet = -1,
	enObjStyleNone,
	enObjStyleColor,
	enObjStyleIccColor,
	enObjStyleRadialGradient,
	enObjStyleLinearGradient,
	enObjStylePattern,
}EObjStyle;

///////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	enObjStrokeNone = -1,
	enObjStrokeSolid,
	enObjStrokeDash,
	enObjStrokeDot,
	enObjStrokeDashDot,
	enObjStrokeDashDotDot,
	enObjStrokeCustom,
}EObjStrokeStyle;

class CStyleCreator;

///////////////////////////////////////////////////////////////////////////////////////////////////
/// CStyle class
class CStyle
{
public:
	class CData
	{
	public:
		virtual ~CData() = 0 {}
		virtual CData* Clone() = 0;
		virtual void Copy( const CData& rData ) = 0;
		virtual void GetText( CString& cszText ) = 0;
	};

	CStyle();
	virtual ~CStyle();

	void Delete();

	void SetNull();
	BOOL IsNull();
	BOOL IsNull() const;

	FLOAT GetOpacity();
	void SetOpacity( FLOAT fOpacity );

	ARGB GetARGB();
	ARGB GetARGB() const;
	void SetARGB( ARGB argb );

	virtual void CopyStyle( const CStyle* pStyle );
	virtual void Copy( const CStyle* pStyle );
	virtual void Get( CStyle* pStyle );

	virtual void GetText( CString& cszText, BOOL bOpacity = TRUE );
	virtual void SetByText( WORD wType, LPCTSTR ptszText, FLOAT fOpacity = -2.0f );

	virtual void SetColor( ARGB argb, FLOAT fOpacity = -2.0f );
	virtual void SetIccColor( LPCTSTR ptszIccName, FLOAT fOpacity = -2.0f );

public:
	static BOOL AddStyleCreator( WORD wType, CStyleCreator* pCreator );
	static CStyleCreator* GetStyleCreator( WORD wType );
	static BOOL RemoveStyleCreator( WORD wType );

public:
	WORD		m_wType;
	FLOAT		m_fOpacity;

	union {
		ARGB		m_argb;
		INT			m_nIndex;
		CData*		m_pData;
	};
};

inline void CStyle::SetNull() {
	m_wType = enObjStyleNone; }

inline BOOL CStyle::IsNull() {
	return enObjStyleNone == m_wType; }

inline BOOL CStyle::IsNull() const {
	return enObjStyleNone == m_wType; }

inline FLOAT CStyle::GetOpacity() {
	return m_fOpacity; }

inline void CStyle::SetOpacity( FLOAT fOpacity ) {
	m_fOpacity = fOpacity; }

#define OBJ_COLOR(cColor, fOpacity)	((cColor & 0xFFFFFF) | ((INT)(fOpacity * 255.0f) << 24))

inline ARGB CStyle::GetARGB() const {
	return OBJ_COLOR(m_argb, m_fOpacity); }

inline ARGB CStyle::GetARGB() {
	return OBJ_COLOR(m_argb, m_fOpacity); }

inline void CStyle::SetARGB( ARGB argb ) {
	m_argb = argb; }

///////////////////////////////////////////////////////////////////////////////////////////////////
/// CFillStyle class
class CU_EXT_CLASS CFillStyle : public CStyle
{
public:
	CFillStyle();
	virtual ~CFillStyle();

	virtual void Copy( const CFillStyle* pStyle );
	virtual void Get( CFillStyle* pStyle ) const;

	virtual void SetBrushStyle( Brush& rBrush ) const;

public:
	INT			m_nFillRule;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
/// CStrokeStyle class
class CU_EXT_CLASS CStrokeStyle : public CStyle
{
public:
	CStrokeStyle();
	virtual ~CStrokeStyle();

	void Copy( const CStrokeStyle* pStyle );
	void Get( CStrokeStyle* pStyle ) const;

	virtual void SetPenStyle( Pen& rPen ) const;

public:
	INT			m_nDashStyle;

	INT			m_nLineCapStyle;
	INT			m_nJoinStyle;
	FLOAT		m_fThickness;
};

///////////////////////////////////////////////////////////////////////////////////////////////
/// CStylePen class
class CStylePen
{
public:
	class CData
	{
	public:
		virtual ~CData() = 0 {}
	};

	CStylePen();
	CStylePen( const CStyle& rStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF );
	CStylePen( const CStrokeStyle& rStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF );
	virtual ~CStylePen();

	operator Pen*() const;
	Pen* Create( const CStyle& rStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF );
	Pen* Create( const CStrokeStyle& rStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF );
	void Delete();

public:
	Pen*	m_pPen;
	CData*	m_pData;
};

inline CStylePen::operator Pen*() const { 
	return m_pPen; }

///////////////////////////////////////////////////////////////////////////////////////////////
/// CStyleBrush class
class CStyleBrush
{
public:
	class CData
	{
	public:
		virtual ~CData() = 0 {}
	};

	CStyleBrush();
	CStyleBrush( const CStyle& psStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF );
	CStyleBrush( const CFillStyle& psStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF );
	virtual ~CStyleBrush();

	operator Brush*() const;

	virtual void Delete();
	virtual Brush* Create( const CStyle& psStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF );
	virtual Brush* Create( const CFillStyle& psStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF );

public:
	Brush*	m_pBrush;
	CData*	m_pData;
};

inline CStyleBrush::operator Brush*() const { 
	return m_pBrush; }

///////////////////////////////////////////////////////////////////////////////////////////////
/// CStyleCreator class
class CStyleCreator
{
public:
	virtual Pen* CreatePen( CStylePen& rPen, const CStyle& rStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF ) = 0;
	virtual Brush* CreateBrush( CStyleBrush& rBrush, const CStyle& rStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF ) = 0;

	virtual FLOAT GetAlpha( const CStyle& rStyle ) = 0;
	
	virtual void GetStyleText( const CStyle& rStyle, CString& rcszText ) = 0;
	virtual BOOL SetStyleByText( CStyle& rStyle, LPCTSTR ptszText ) = 0;
};

#endif //!___STYLE__PH___