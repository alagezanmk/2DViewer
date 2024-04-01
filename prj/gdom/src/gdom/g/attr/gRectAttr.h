#ifndef ___G_RECT_F_ATTR__PH___
#define ___G_RECT_F_ATTR__PH___

#include "gAttr.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSARectF : public CGIAttr
{
public:
	CGSARectF( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	BOOL operator=( const GRectF& rgrcValue );
	operator const GRectF&() const;

	virtual const GRectF& Get() const;
	virtual void Get( FLOAT& rfLeft, FLOAT& rfTop, FLOAT& rfRight, FLOAT& rfBottom ) const;
	virtual BOOL Set( const GRectF& rgrcValue );
	virtual BOOL Set( FLOAT fLeft, FLOAT fTop, FLOAT fRight, FLOAT fBottom );

	virtual BOOL Validate( GRectF& rgrcValue ) const;
	virtual BOOL Validate( FLOAT& rfLeft, FLOAT& rfTop, FLOAT& rfRight, FLOAT& rfBottom ) const;
	virtual BOOL Update( const GRectF& rgrcValue );
	virtual BOOL Update( FLOAT fLeft, FLOAT fTop, FLOAT fRight, FLOAT fBottom );

protected:
	GRectF	m_grc;
};

inline BOOL CGSARectF::operator=( const GRectF& rgrcValue ) {
	return Set( rgrcValue ); }

inline CGSARectF::operator const GRectF&() const {
	return Get(); }

inline const GRectF& CGSARectF::Get() const {
	return m_grc;  }

inline void CGSARectF::Get( FLOAT& rfLeft, FLOAT& rfTop, FLOAT& rfRight, FLOAT& rfBottom ) const {
	rfLeft = m_grc.left, rfTop = m_grc.top, rfRight = m_grc.right, rfBottom = m_grc.bottom; } 

////////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGMARectF: public CGIAttrArray
{
public:
	virtual ~CGMARectF();

public:
	GRectF* GetList();
	const GRectF* GetList() const;
	const GRectF& GetAt( INT nIndex ) const;
	BOOL SetAt( INT nIndex, const GRectF& rgrcValue, INT nCount = 1 );
	BOOL InsertAt( INT nIndex, const GRectF& rgrcValue, INT nCount = 1 );
	BOOL RemoveAt( INT nIndex, INT nCount = 1 );

protected:
	CArray<GRectF, const GRectF&>	m_arrgrc;
};

#endif //!___G_RECT_F_ATTR__PH___
