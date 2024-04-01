#ifndef ___G_BOOL_ATTR_PH___
#define ___G_BOOL_ATTR_PH___

#include "gAttr.h"

class GDOM_EXT_CLASS CGSABool : public CGIAttr
{
public:
	CGSABool( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );
	BOOL operator=( const CString& rcszValue );
	virtual BOOL Set( LPCTSTR pctszValue );

	BOOL operator=( BOOL bValue );
	operator BOOL() const;

	virtual BOOL Set( BOOL bValue );
	virtual BOOL Get() const;
	virtual BOOL Validate( BOOL& rbValue ) const;
	virtual BOOL Update( BOOL bValue );

protected:
	BOOL m_b;
};

inline BOOL CGSABool::operator=( const CString& rcszValue ) {
	return Set( rcszValue ); }

inline BOOL CGSABool::operator=( BOOL bValue ) {
	return Set( bValue ); }

inline CGSABool::operator BOOL() const {
	return m_b; }

inline BOOL CGSABool::Get() const {
	return m_b; }

class GDOM_EXT_CLASS CGMABool : public CGIAttrArray
{
public:
	virtual ~CGMABool();

public:
	BOOL* GetList();
	const BOOL* GetList() const;
	BOOL GetAt( INT nIndex ) const;
	BOOL SetAt( INT nIndex, BOOL bValue, INT nCount = 1 );
	BOOL InsertAt( INT nIndex, BOOL bValue, INT nCount = 1 );
	BOOL RemoveAt( INT nIndex, INT nCount = 1 );

protected:
	CArray<BOOL, BOOL>	m_arrb;
};

#endif //!___G_BOOL_ATTR_PH___
