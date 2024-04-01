#include "stdafx.h"
#include <g\attr\gAttr.h>
#include <g\type\idom\giNode.h>
#include <g\type\idom\giElement.h>
#include <g\type\gEventPriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR CGIAttr::ATTR_NOT_SET_STR = _T("[Not Set]");;
////////////////////////////////////////////////////////////////////////////////////////////////////
IMPL_GTPYECLASS_DYNCREATE( CGIAttr, CGINode, _T("Attr") )
CGIAttr::CGIAttr( LPCTSTR pctszName ) 
{
	m_pgInstanceType = &GetClassType();
	m_cszName = pctszName;

	m_pOwnerElement = NULL;
	m_nAttrFlag = NONE_ATTR_FLAG;
	m_nAttrType = USER_DEFINED_ATTR_TYPE;
	m_bGroupedNaming = FALSE;
}

CString CGIAttr::GetGroupName() const
{
	CString cszGroupName;
	GetGroupName( cszGroupName );

	return cszGroupName;
}

void CGIAttr::GetGroupName( CString& rcsName ) const
{
	if( FALSE == m_bGroupedNaming )
		return;

	CGIAttrGroup* piGroup = (CGIAttrGroup*)GetParent();
	if( piGroup && CGNode::ATTRIBUTE_GROUP_NODE == piGroup->GetNodeType() )
	{
		rcsName = piGroup->GetNodeName();
		piGroup->GetGroupName( rcsName );
	}
}

INT CGIAttr::SetAttrType( INT nType, BOOL bSet /*= TRUE*/ ) 
{
	INT nOldType = m_nAttrType;
	if( bSet )
		m_nAttrType |= nType;
	else
		m_nAttrType &= ~nType;

	return nOldType;
}

INT CGIAttr::SetAttrFlag( INT nFlag, BOOL bSet /*= TRUE*/ )
{
	INT nOldFlag = m_nAttrFlag;
	if( bSet )
		m_nAttrFlag |= nFlag;
	else
		m_nAttrFlag &= ~nFlag;

	return nOldFlag;
}

void CGIAttr::NotSet( BOOL bSet /*= TRUE*/ )
{
	if( bSet )
		m_nAttrFlag |= NOT_SET_ATTR_FLAG;
	else
		m_nAttrFlag &= ~NOT_SET_ATTR_FLAG;

	Changed();
}

INT CGIAttr::GetValue( void* pValue ) const
{
	pValue = NULL;

	BOOL bNotSet = GetNotSet();
	if( FALSE == bNotSet )
		return ATTR_VALUE_TYPE;

	if( NULL == m_pOwnerElement )
		return UNDEFINED_VALUE_TYPE;

	BOOL bInheritable = IsInHeritable();
	if( FALSE == bInheritable )
	{
		if( m_pOwnerElement->GetDefaultAttributeValue( m_cszName, GetAttrType(), pValue ) )
			return DEF_VALUE_TYPE;

		return UNDEFINED_VALUE_TYPE;
	}

	INT nNodeType;
	INT nValueType;
	CGIAttr* pAttr;
	CGINode* pNode = m_pOwnerElement->GetParent();
	while( pNode )
	{
		nNodeType = pNode->GetNodeType();
		if( CGNode::ELEMENT_NODE == nNodeType )
		{
			pAttr = ((CGIElement*)pNode)->GetAttributeNode( m_cszName );
			if( pAttr )
			{
				bNotSet = pAttr->GetNotSet();
				if( FALSE == bNotSet )
				{
					nValueType = pAttr->GetValue( pValue );
					if( ATTR_VALUE_TYPE == nValueType || ANIM_VALUE_TYPE == nValueType )
						return INHERIT_VALUE_TYPE;

					return ATTR_VALUE_TYPE;
				}
			}
		}

		pNode = pNode->GetParent();
	}

	return UNDEFINED_VALUE_TYPE;
}

BOOL CGIAttr::Set( LPCTSTR pctszValue ) 
{
	CString cszValue = pctszValue;
	if( FALSE == Validate( cszValue ) )
		return FALSE;

	if( FALSE == Update( cszValue ) )
		return FALSE;

	Changed();
	return TRUE; 
}

void CGIAttr::Get( CString& rcszValue ) const
{
	if( GetNotSet() )
		rcszValue = ATTR_NOT_SET_STR;
	else
		rcszValue.Empty(); 
}

BOOL CGIAttr::Validate( CString& rcszValue ) const 
{
	if( m_pOwnerElement )
		return m_pOwnerElement->ValidateAttribute( *this, NULL );

	return TRUE; 
}

BOOL CGIAttr::Validate( void* pValue ) const
{
	if( m_pOwnerElement )
		return m_pOwnerElement->ValidateAttribute( *this, pValue );

	return TRUE; 
}

BOOL CGIAttr::Update( CString& rcszValue )
{
	if( m_pOwnerElement )
		return m_pOwnerElement->UpdateAttribute( *this, NULL );

	return TRUE;
}

BOOL CGIAttr::Update( void* pValue )
{
	if( FALSE == GetNotSet() )
		m_nAttrFlag &= ~NOT_SET_ATTR_FLAG;

	if( m_pOwnerElement )
		return m_pOwnerElement->UpdateAttribute( *this, pValue );

	return TRUE;
}

void CGIAttr::OnUpdate( void* pNewValue )
{
	if( m_pOwnerElement )
	{
		CGMutationEvent* pMutationEvent = CreateDOMUpdateAttrEvent( pNewValue );
		if( pMutationEvent )
			m_pOwnerElement->DispatchEvent( *pMutationEvent );

		m_pOwnerElement->LockEvent( CGMutationEvent::DOMAttrModified );
		pMutationEvent = CreateDOMAttrModifiedEvent();
		if( pMutationEvent )
			m_pOwnerElement->DispatchEvent( *pMutationEvent );
	}
}

void* CGIAttr::GetPreviousValuePointer() {
	return NULL; }

void CGIAttr::DeletePreviousValuePointer( void* pPointer )
{
	if( pPointer )
		delete pPointer;
}

void* CGIAttr::GetNewValuePointer() {
	return NULL; }

void CGIAttr::DeleteNewValuePointer( void* pPointer )
{
	if( pPointer )
		delete pPointer;
}

BOOL CGIAttr::CompareDOMAttrEvent( CGEvent* pEvent, void* pParam )
{
	if( NULL == pEvent || NULL == pParam )
		return FALSE;

	CGMutationEvent& rMutationEvent = *((CGMutationEvent*)pEvent);
	CGINode* pNode = (CGINode*)pParam;
	BOOL bResult = pNode  == rMutationEvent.GetRelatedNode();
	return bResult;
}

CGMutationEvent* CGIAttr::CreateDOMUpdateAttrEvent( void* pNewValue )
{
	if( NULL == m_pOwnerElement )
	{
		ASSERT( m_pOwnerElement );
		return NULL;
	}

	SCompareEventPending sCompare;
	sCompare.pfnCompare = CGIAttr::CompareDOMAttrEvent;
	sCompare.pParam = (void*)(CGINode*)this;

	BOOL bInitialize;
	CGMutationEvent* pEvent = m_pOwnerElement->CreateMutationEvent( CGDomMutationEvent::DOMExtUpdateAttr, 
																	bInitialize, NULL, &sCompare );
	ASSERT( pEvent );
	if( NULL == pEvent )
		return NULL;

	if( bInitialize )
		pEvent->InitEvent( CGDomMutationEvent::DOMExtUpdateAttr, TRUE, FALSE, this, 
						   GetPreviousValuePointer(),
						   pNewValue, 
						   m_cszName, CGMutationEvent::MODIFICATION );
	return pEvent;
}

CGMutationEvent* CGIAttr::CreateDOMAttrModifiedEvent()
{
	if( NULL == m_pOwnerElement )
	{
		ASSERT( m_pOwnerElement );
		return NULL;
	}

	SCompareEventPending sCompare;
	sCompare.pfnCompare = CGIAttr::CompareDOMAttrEvent;
	sCompare.pParam = (void*)(CGINode*)this;

	BOOL bInitialize;
	CGMutationEvent* pEvent = m_pOwnerElement->CreateMutationEvent( CGMutationEvent::DOMAttrModified, 
																	bInitialize, NULL, &sCompare );
	ASSERT( pEvent );
	if( NULL == pEvent )
		return NULL;

	if( bInitialize )
		pEvent->InitEvent( CGMutationEvent::DOMAttrModified, TRUE, FALSE, this, 
						   GetPreviousValuePointer(),
						   GetNewValuePointer(), 
						   m_cszName, CGMutationEvent::MODIFICATION );
	else
	{
		CGMutationEventPriv* pEventPriv = (CGMutationEventPriv*)pEvent;
		pEventPriv->SetNewValue( GetNewValuePointer() );
	}

	return pEvent;
}

void CGIAttr::Changed() 
{
	if( m_pOwnerElement )
	{
		m_pOwnerElement->UnlockEvent( CGMutationEvent::DOMAttrModified );
		CGMutationEvent* pMutationEvent = CreateDOMAttrModifiedEvent();
		if( pMutationEvent )
			m_pOwnerElement->DispatchEvent( *pMutationEvent );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGIAttrArray::CGIAttrArray( LPCTSTR pctszName )
 : CGIAttr( pctszName )
{}

CGIAttrArray::~CGIAttrArray()
{}
