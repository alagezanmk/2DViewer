#ifndef ___G_STRING_ATTR__PH___
#define ___G_STRING_ATTR__PH___

#include "gAttr.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSAString : public CGIAttr
{
	DECL_GTPYECLASS_DYNCREATE(CGSAString)
public:
	CGSAString( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;

	BOOL operator=( const CString& rcszValue );
	virtual BOOL Set( LPCTSTR pctszValue );
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	LPCTSTR Get() const;
	operator LPCTSTR() const;

protected:
	CString m_csz;
};

inline BOOL CGSAString::operator=( const CString& rcszValue ) {
	return Set( rcszValue ); }

inline CGSAString::operator LPCTSTR() const {
	return m_csz; }

inline LPCTSTR CGSAString::Get() const {
	return m_csz; }

////////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGMAString : public CGIAttrArray
{
protected:
	virtual ~CGMAString();

public:
	CString** GetList();
	const CString** GetList() const;
	LPCTSTR GetAt( INT nIndex ) const;
	BOOL SetAt( INT nIndex, LPCTSTR pctszValue, INT nCount = 1 );
	BOOL InsertAt( INT nIndex, LPCTSTR pctszValue, INT nCount = 1 );
	BOOL RemoveAt( INT nIndex, INT nCount = 1 );

protected:
	CStringArray	m_arrcsz;
};

#endif //!___G_STRING_ATTR__PH___
