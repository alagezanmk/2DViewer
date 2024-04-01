#include "stdafx.h"
#include <g\attr\gAttrLink.h>
#include <g\type\idom\giElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CGIAttrPriv : public CGIAttr
{
public:
	// Function to initialize the member m_cszName
	void SetAutoDelete( RELEASE_MODE enMode ) {
		m_nFlag = enMode; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
CGIAttrLink::CGIAttrLink() {
	m_pAttr = NULL; }

CGIAttrLink::~CGIAttrLink()
{
	if( m_pAttr )
	{
		((CGIAttrPriv*)m_pAttr)->SetAutoDelete( CGObject::AUTO_RELEASE );
		m_pAttr->Release();
	}
}

LPCTSTR CGIAttrLink::GetName() const 
{
	if( NULL == m_pAttr )
		return NULL;

	return m_pAttr->GetName();
}

void CGIAttrLink::ConstructAttribute()
{
	if( NULL == m_pAttr )
		return;

	m_pAttr->AddRef();
	m_pAttr->SetAttrType( CGIAttr::USER_DEFINED_ATTR_TYPE, FALSE );
	((CGIAttrPriv*)m_pAttr)->SetAutoDelete( CGObject::NEVER_RELEASE );
}

void CGIAttrLink::RemoveAttribute()
{
	if( NULL == m_pAttr )
		return;

	m_pAttr->SetAttrType( CGIAttr::USER_DEFINED_ATTR_TYPE );
	CGIElement* pElement = m_pAttr->GetOwnerElement();
	pElement->RemoveAttributeNode( *m_pAttr );
}

void CGIAttrLink::NotSet( BOOL bSet /*= TRUE*/ )
{
	if( NULL == m_pAttr )
		return;
	
	m_pAttr->NotSet( bSet ); 
}

BOOL CGIAttrLink::GetNotSet() const 
{
	if( NULL == m_pAttr )
		return FALSE;
	
	return m_pAttr->GetNotSet(); 
}

BOOL CGIAttrLink::IsInHeritable() const 
{
	if( NULL == m_pAttr )
		return FALSE;
	
	return m_pAttr->IsInHeritable(); 
}

BOOL CGIAttrLink::IsAttrTypeSet( INT nType ) const 
{
	if( NULL == m_pAttr )
		return FALSE;
	
	return m_pAttr->IsAttrTypeSet( nType ); 
}

void CGIAttrLink::SetAttrType( INT nType ) 
{
	if( NULL == m_pAttr )
		return;
	
	m_pAttr->SetAttrType( nType ); 
}

INT CGIAttrLink::GetAttrType() const 
{
	if( NULL == m_pAttr )
		return 0;
	
	return m_pAttr->GetAttrType(); 
}

INT CGIAttrLink::IsAttrFlagSet( INT nFlag ) const 
{
	if( NULL == m_pAttr )
		return FALSE;
	
	return m_pAttr->IsAttrFlagSet( nFlag ); 
}

INT CGIAttrLink::GetAttrFlag() const 
{
	if( NULL == m_pAttr )
		return 0;
	
	return m_pAttr->GetAttrFlag(); 
}

