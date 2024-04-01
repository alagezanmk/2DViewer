#ifndef ___G_FLOAT_ATTR__PH___
#define ___G_FLOAT_ATTR__PH___

#include "gAttr.h"

class GDOM_EXT_CLASS CGSAFloat : public CGIAttr
{
	DECL_GTPYECLASS_DYNCREATE(CGSAFloat)

public:
	CGSAFloat( LPCTSTR pctszName );

public:
	virtual void Get( CString& rcszValue ) const;

	BOOL operator=( const CString& rcszValue );
	virtual BOOL Set( LPCTSTR pctszValue );
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	operator FLOAT() const;
	virtual FLOAT Get() const;

	BOOL operator=( FLOAT fValue );
	virtual BOOL Set( FLOAT fValue );
	virtual BOOL Validate( FLOAT& rfValue ) const;
	virtual BOOL Update( FLOAT fValue );

	virtual void* GetPreviousValuePointer();
	virtual void* GetNewValuePointer();
	virtual void DeleteNewValuePointer( void* pPointer );

protected:
	FLOAT	m_f;
};

inline BOOL CGSAFloat::operator=( const CString& rcszValue ) {
	return Set( rcszValue ); }

inline BOOL CGSAFloat::operator=( FLOAT fValue ) {
	return Set( fValue ); }

inline CGSAFloat::operator FLOAT() const {
	return Get(); }

class GDOM_EXT_CLASS CGMAFloat : public CGIAttrArray
{
public:
	virtual ~CGMAFloat();

public:
	FLOAT* GetList();
	const FLOAT* GetList() const;
	FLOAT GetAt( INT nIndex ) const;
	BOOL SetAt( INT nIndex, FLOAT fValue, INT nCount = 1 );
	BOOL InsertAt( INT nIndex, FLOAT fValue, INT nCount = 1 );
	BOOL RemoveAt( INT nIndex, INT nCount = 1 );

protected:
	CArray<FLOAT, FLOAT>	m_arrf;
};

#endif //!___G_FLOAT_ATTR__PH___
