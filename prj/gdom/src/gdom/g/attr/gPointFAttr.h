#ifndef ___G_POINT_F_ATTR__PH___
#define ___G_POINT_F_ATTR__PH___

#include "gAttr.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSAPointF : public CGIAttr
{
public:
	CGSAPointF( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;
	virtual BOOL Set( LPCTSTR pctszValue );
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	BOOL operator=( const GPointF& rgptfValue );
	operator const GPointF&() const;

	virtual BOOL Set( const GPointF& rgptfValue );
	virtual BOOL Set( FLOAT fX, FLOAT fY );
	virtual const GPointF& Get() const;
	virtual void Get( FLOAT& rfX, FLOAT& rfY ) const;

	virtual BOOL Validate( GPointF& rgptfValue ) const;
	virtual BOOL Validate( FLOAT& rfX, FLOAT& rfY ) const;
	virtual BOOL Update( const GPointF& rgptfValue );
	virtual BOOL Update( FLOAT fX, FLOAT fY );

protected:
	CGPointF m_gptf;
};

inline BOOL CGSAPointF::operator=( const GPointF& rgptfValue ) {
	return Set( rgptfValue ); }

inline CGSAPointF::operator const GPointF&() const {
	return Get(); }

inline const GPointF& CGSAPointF::Get() const {
	return m_gptf; }

inline void CGSAPointF::Get( FLOAT& rfX, FLOAT& rfY ) const {
	rfX = m_gptf.x; rfY = m_gptf.y; }

class GDOM_EXT_CLASS CGMAPointF: public CGIAttrArray
{
public:
	virtual ~CGMAPointF();

public:
	GPointF* GetList();
	const GPointF* GetList() const;
	const GPointF& GetAt( INT nIndex ) const;
	BOOL SetAt( INT nIndex, const GPointF& rgptValue, INT nCount = 1 );
	BOOL InsertAt( INT nIndex, const GPointF& rgptValue, INT nCount = 1 );
	BOOL RemoveAt( INT nIndex, INT nCount = 1 );

protected:
	CArray<GPointF, const GPointF&>	m_arrgpt;
};

#endif //!___G_POINT_F_ATTR__PH___
