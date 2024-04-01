#ifndef ___G_INT_32_ATTR__PH___
#define ___G_INT_32_ATTR__PH___

#include "gAttr.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSAInt32 : public CGIAttr
{
public:
	CGSAInt32( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	operator INT32() const;
	BOOL operator=( INT32 n32Value );
	
	virtual BOOL Set( INT32 n32Value );
	virtual INT32 Get() const;
	virtual BOOL Validate( INT32& rn32Value ) const;
	virtual BOOL Update( INT32 n32Value );

protected:
	INT32	m_n32;
};

inline BOOL CGSAInt32::operator=( INT32 n32Value ) {
	return Set( n32Value ); }

inline CGSAInt32::operator INT32() const {
	return m_n32; }

inline INT32 CGSAInt32::Get() const {
	return m_n32; }

/////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSAUInt32 : public CGIAttr
{
public:
	CGSAUInt32( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	operator UINT32() const;
	BOOL operator=( UINT32 n32Value );
	
	virtual BOOL Set( UINT32 n32Value );
	virtual UINT32 Get() const;
	virtual BOOL Validate( UINT32& rn32Value ) const;
	virtual BOOL Update( UINT32 n32Value );

protected:
	UINT32	m_un32;
};

inline BOOL CGSAUInt32::operator=( UINT32 n32Value ) {
	return Set( n32Value ); }

inline CGSAUInt32::operator UINT32() const {
	return m_un32; }

inline UINT32 CGSAUInt32::Get() const {
	return m_un32; }

#endif //!___G_INT_32_ATTR__PH___
