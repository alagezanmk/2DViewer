#ifndef ___G_ATTR_LINK__PH___
#define ___G_ATTR_LINK__PH___

#include "gAttr.h"
class GDOM_EXT_CLASS CGIAttrLink
{
public:
	CGIAttrLink();
	virtual ~CGIAttrLink();

public:
	LPCTSTR GetName() const;
	void ConstructAttribute();
	void RemoveAttribute();

	operator CGIAttr*();
	operator const CGIAttr*() const;

	operator CGIAttr&();
	operator const CGIAttr&() const;

	virtual void NotSet( BOOL bSet = TRUE );
	BOOL GetNotSet() const;

	BOOL IsInHeritable() const;

	BOOL IsAttrTypeSet( INT nType ) const;
	INT GetAttrType() const;
	void SetAttrType( INT nType );

	INT IsAttrFlagSet( INT nFlag ) const;
	INT GetAttrFlag() const;
	INT SetAttrFlag( INT nFlag, BOOL bSet = TRUE );

protected:
	CGIAttr*	m_pAttr;
};

inline CGIAttrLink::operator CGIAttr&() {
	return *m_pAttr; }

inline CGIAttrLink::operator const CGIAttr&() const {
	return *m_pAttr; }

inline CGIAttrLink::operator CGIAttr*() {
	return m_pAttr; }

inline CGIAttrLink::operator const CGIAttr*() const {
	return m_pAttr; }

#endif //!___G_ATTR_LINK__PH___
