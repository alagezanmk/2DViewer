#ifndef ___G_INT_16_ATTR__PH___
#define ___G_INT_16_ATTR__PH___

#include "gAttr.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSAInt16 : public CGIAttr
{
public:
	CGSAInt16( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	operator INT16() const;
	BOOL operator=( INT16 n16Value );
	
	virtual BOOL Set( INT16 n16Value );
	virtual INT16 Get() const;
	virtual BOOL Validate( INT16& rn16Value ) const;
	virtual BOOL Update( INT16 n16Value );

protected:
	INT16	m_n16;
};

inline BOOL CGSAInt16::operator=( INT16 n16Value ) {
	return Set( n16Value ); }

inline CGSAInt16::operator INT16() const {
	return m_n16; }

inline INT16 CGSAInt16::Get() const {
	return m_n16; }

/////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSAUInt16 : public CGIAttr
{
public:
	CGSAUInt16( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	operator UINT16() const;
	BOOL operator=( UINT16 n16Value );
	
	virtual BOOL Set( UINT16 n16Value );
	virtual UINT16 Get() const;
	virtual BOOL Validate( UINT16& rn16Value ) const;
	virtual BOOL Update( UINT16 n16Value );

protected:
	UINT16	m_un16;
};

inline BOOL CGSAUInt16::operator=( UINT16 n16Value ) {
	return Set( n16Value ); }

inline CGSAUInt16::operator UINT16() const {
	return m_un16; }

inline UINT16 CGSAUInt16::Get() const {
	return m_un16; }

#endif //!___G_INT_16_ATTR__PH___
