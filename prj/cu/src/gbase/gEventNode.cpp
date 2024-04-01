#include "stdafx.h"
#include <gbase\gEventNode.h>
#include <g\type\gEventPriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
LPCTSTR CGEventNode::NODE_TYPE = _T("CGEventNode");
IMPL_GTPYECLASS_DYNCREATE( CGEventNode, CGEventTarget, _T("eventNode") )
CGEventNode::CGEventNode() 
{
	m_pgInstanceType = &GetClassType();
}	

CGEventNode::~CGEventNode() 
{}

INT CGEventNode::GetDispatchPath( CPtrArray& rarpPath )
{
	CGObjectNode* pNode = this;
	while( pNode  )
	{
		rarpPath.Add( (CGEventTarget*)(CGEventNode*)pNode );
		pNode = pNode->GetParentNode();

		// Not add if the node is not Event Node type
		if( pNode && FALSE == pNode->_IsDerivedFrom( CGEventNode::NODE_TYPE ) )
			pNode = NULL;
	}

	return rarpPath.GetSize();
}

CGMutationEvent* CGEventNode::CreateAttrModifiedMutationEvent( LPCTSTR pctszEventType )
{
	CGMutationEventPriv* pEvent = new CGMutationEventPriv( pctszEventType, this );
	return pEvent;
}

CGMutationEvent* CGEventNode::CreateMutationEvent( LPCTSTR pctszEventType, BOOL& rbInitialize, 
												   CGEventNode* pLockCheckParent /*= NULL*/,
												   SCompareEventPending* pCompare /*= NULL*/ )
{
	rbInitialize = FALSE;

	if( NULL == pLockCheckParent )
		pLockCheckParent = this;

	CGMutationEvent* pPendingEvent = (CGMutationEvent*)pLockCheckParent->GetPendingEvent( pctszEventType, this, pCompare );
	if( pPendingEvent )
		return pPendingEvent;

	CGMutationEvent* pEvent = CreateAttrModifiedMutationEvent( pctszEventType );
	ASSERT( pEvent );
	if( pEvent )
		rbInitialize = TRUE;

	return pEvent;
}

CGMutationEvent* CGEventNode::CreateNodeTreeModifiedEvent( LPCTSTR pctszEventType,  
													       CGEventNode* pRelatedNode, 
													       INT nAttrChange,
														   CGEventNode* pLockCheckParent /*= NULL*/ )
{
	BOOL bInitialize;
	CGMutationEvent* pEvent = CreateMutationEvent( pctszEventType, bInitialize, pLockCheckParent );
	ASSERT( pEvent );
	if( NULL == pEvent )
		return NULL;

	if( bInitialize )
	{
		BOOL bCanBubble = TRUE;
		if( CGMutationEvent::DOMNodeInsertedIntoDocument == pctszEventType
			|| CGMutationEvent::DOMNodeRemovedFromDocument == pctszEventType )
			bCanBubble = FALSE;

		pEvent->InitEvent( pctszEventType, bCanBubble, FALSE, pRelatedNode,
						   NULL, NULL, NULL, nAttrChange );
	}

	return pEvent;
}

void CGEventNode::DispatchNodeTreeModifiedEvent( LPCTSTR pctszEventType, CGEventNode* pTarget, 
											     CGEventNode* pRelatedNode, INT nAttrChange )
{
	if( CGMutationEvent::DOMSubTreeModified != pctszEventType
		&& CGMutationEvent::DOMNodeInserted != pctszEventType 
		&& CGMutationEvent::DOMNodeRemoved != pctszEventType
		&& CGMutationEvent::DOMNodeInsertedIntoDocument != pctszEventType
		&& CGMutationEvent::DOMNodeRemovedFromDocument != pctszEventType )
	{
		ASSERT( FALSE );
		return;
	}

	CGMutationEvent* pEvent = pTarget->CreateNodeTreeModifiedEvent( pctszEventType, 
																	pRelatedNode, 
																	nAttrChange,
																	this );
	if( pEvent )
		pTarget->DispatchEvent( *pEvent );
}

void CGEventNode::DispatchNodeInsertedIntoDocumentEvent( CGEventNode& rTarget )
{
	DispatchNodeTreeModifiedEvent( CGMutationEvent::DOMNodeInsertedIntoDocument, &rTarget, NULL, CGMutationEvent::ADDITION );

	CGObjectNode* pNode = rTarget.m_pFirst;
	while( pNode )
	{
		if( FALSE == pNode->_IsDerivedFrom( CGEventNode::NODE_TYPE ) )
			break;

		DispatchNodeInsertedIntoDocumentEvent( *((CGEventNode*)pNode) );
		pNode = pNode->GetNextNode();
	}
}

void CGEventNode::DispatchNodeRemovedFromDocumentEvent( CGEventNode& rTarget )
{
	CGObjectNode* pNode = rTarget.m_pFirst;
	while( pNode )
	{
		if( FALSE == pNode->_IsDerivedFrom( CGEventNode::NODE_TYPE ) )
			break;

		DispatchNodeRemovedFromDocumentEvent( *((CGEventNode*)pNode) );
		pNode = pNode->GetNextNode();
	}

	DispatchNodeTreeModifiedEvent( CGMutationEvent::DOMNodeRemovedFromDocument, &rTarget, NULL, CGMutationEvent::REMOVAL );
}

void CGEventNode::AttachChild( CGObjectNode& rNode )
{
	CGObjectNode::AttachChild( rNode );

	if( rNode._IsDerivedFrom( CGEventNode::NODE_TYPE ) )
	{
		CGEventNode* pNode = (CGEventNode*)&rNode;
		AttachChild( *pNode );
	}
}

void CGEventNode::AttachChild( CGEventNode& rNode )
{
	DispatchNodeTreeModifiedEvent( CGMutationEvent::DOMNodeInserted, &rNode, this, CGMutationEvent::ADDITION );
	DispatchNodeInsertedIntoDocumentEvent( rNode );
}

void CGEventNode::DetachChild( CGObjectNode& rNode )
{
	if( rNode._IsDerivedFrom( CGEventNode::NODE_TYPE ) )
	{
		CGEventNode* pNode = (CGEventNode*)&rNode;
		DetachChild( *pNode );
	}

	CGObjectNode::DetachChild( rNode );
}

void CGEventNode::DetachChild( CGEventNode& rNode )
{
	DispatchNodeTreeModifiedEvent( CGMutationEvent::DOMNodeRemoved, &rNode, this, CGMutationEvent::REMOVAL );
	DispatchNodeRemovedFromDocumentEvent( rNode );
}

void CGEventNode::Attach( CGEventNode& rNode )
{}

void CGEventNode::Detach( CGEventNode& rNode )
{}

void CGEventNode::Attach( CGObjectNode& rNode ) 
{
	CGObjectNode::Attach( rNode ); 
	if( rNode._IsDerivedFrom( CGEventNode::NODE_TYPE ) )
		Attach( *((CGEventNode*)&rNode) ); 
}

void CGEventNode::Detach( CGObjectNode& rNode ) 
{
	if( rNode._IsDerivedFrom( CGEventNode::NODE_TYPE ) )
		Detach( *((CGEventNode*)&rNode) ); 

	CGObjectNode::Detach( rNode ); 
}

BOOL CGEventNode::_IsDerivedFrom( LPCTSTR pctszNodeType ) const
{
	if( CGEventNode::NODE_TYPE == pctszNodeType )
		return TRUE;

	return CGObjectNode::_IsDerivedFrom( pctszNodeType );
}

CGFactoryObject* CGEventNode::GetFactoryObjectParent() {
	return (CGFactoryObject*)(CGEventNode*)GetParentNode(); }

void CGEventNode::LockObjectLink( BOOL bLock /*= TRUE*/ )
{
	if( bLock )
		m_cSect.Lock();
	else
		m_cSect.Unlock();
}

void* CGEventNode::CreateFactoryObject( const CGType& rType ) {
	return CGFactoryObject::CreateFactoryObject( rType.GetName(), (void*)&rType ); }
