#ifndef ___G_ENUM_ATTR__PH___
#define ___G_ENUM_ATTR__PH___

#include "gAttr.h"

typedef INT ENUM;
/////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSAEnum : public CGIAttr
{
public:
	CGSAEnum( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	BOOL operator=( ENUM enValue );
	operator ENUM() const;
	
	virtual BOOL Set( ENUM enValue );
	virtual ENUM Get() const;
	virtual BOOL Validate( ENUM& renValue ) const;
	virtual BOOL Update( ENUM enValue );

protected:
	ENUM	m_en;
};

inline BOOL CGSAEnum::operator=( ENUM enValue ) {
	return Set( enValue ); }

inline CGSAEnum::operator ENUM() const {
	return m_en; }

inline ENUM CGSAEnum::Get() const {
	return m_en; }

class GDOM_EXT_CLASS CGMAEnum: public CGIAttrArray
{
public:
	CGMAEnum();
	virtual ~CGMAEnum();

public:
	INT* GetList();
	const INT* GetList() const;
	const INT GetAt( INT nIndex ) const;
	BOOL SetAt( INT nIndex, INT enValue, INT nCount = 1 );
	BOOL InsertAt( INT nIndex, INT enValue, INT nCount = 1 );
	BOOL RemoveAt( INT nIndex, INT nCount = 1 );

protected:
	CArray<INT, INT>	m_arren;
};

#endif //!___G_ENUM_ATTR__PH___
