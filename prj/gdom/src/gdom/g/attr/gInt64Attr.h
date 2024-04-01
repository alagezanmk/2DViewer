#ifndef ___G_INT_64_ATTR__PH___
#define ___G_INT_64_ATTR__PH___

#include "gAttr.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSAInt64 : public CGIAttr
{
public:
	CGSAInt64( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	operator INT64() const;
	BOOL operator=( INT64 n64Value );
	
	virtual BOOL Set( INT64 n64Value );
	virtual INT64 Get() const;
	virtual BOOL Validate( INT64& rn64Value ) const;
	virtual BOOL Update( INT64 n64Value );

protected:
	INT64	m_n64;
};

inline BOOL CGSAInt64::operator=( INT64 n64Value ) {
	return Set( n64Value ); }

inline CGSAInt64::operator INT64() const {
	return m_n64; }

inline INT64 CGSAInt64::Get() const {
	return m_n64; }

/////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSAUInt64 : public CGIAttr
{
public:
	CGSAUInt64( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	operator UINT64() const;
	BOOL operator=( UINT64 n64Value );
	
	virtual BOOL Set( UINT64 n64Value );
	virtual UINT64 Get() const;
	virtual BOOL Validate( UINT64& rn64Value ) const;
	virtual BOOL Update( UINT64 n64Value );

protected:
	UINT64	m_un64;
};

inline BOOL CGSAUInt64::operator=( UINT64 n64Value ) {
	return Set( n64Value ); }

inline CGSAUInt64::operator UINT64() const {
	return m_un64; }

inline UINT64 CGSAUInt64::Get() const {
	return m_un64; }

#endif //!___G_INT_64_ATTR__PH___
