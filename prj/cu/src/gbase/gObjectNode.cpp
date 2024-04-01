#include "stdafx.h"
#include <gbase\gObjectNode.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
LPCTSTR CGObjectNode::NODE_TYPE = _T("CGClassNode");
CGObjectNode::CGObjectNode() 
{
	m_pParent = NULL;

	m_pPrev = NULL;
	m_pNext = NULL;

	m_pFirst = NULL;
	m_pLast = NULL;
}	

CGObjectNode::~CGObjectNode() {
	RemoveAllChild(); }

BOOL CGObjectNode::HasChildNodes() const {
	return NULL != m_pFirst; }

BOOL CGObjectNode::_IsDerivedFrom( LPCTSTR pctszNodeType ) const
{
	if( CGObjectNode::NODE_TYPE == pctszNodeType )
		return TRUE;

	return FALSE;
}

void CGObjectNode::RemoveAllChild()
{
	CLockCriticalSection cs( m_cSect ); 

	CGObjectNode* pNode = m_pLast;
	CGObjectNode* pPrev;
	while( pNode )
	{
		pPrev = pNode->m_pPrev;
		RemoveChild( *pNode );
		pNode = pPrev;
	}
}

void CGObjectNode::OnNodeListModified()
{}

CGObjectNode* CGObjectNode::InsertBefore( CGObjectNode& rNewChild, CGObjectNode& rRef ) 
{
	CLockCriticalSection cs( m_cSect ); 

	if( &rNewChild == &rRef )
		return NULL;

	if( FALSE == IsChildNode( rRef ) )
		return NULL;

	if( IsChildNode( rNewChild ) )
		return NULL;
	
	OnNodeListModified();

	CGObjectNode* pRefPrev = rRef.m_pPrev;
	rNewChild.m_pPrev = rRef.m_pPrev;
	rNewChild.m_pNext = &rRef;
	rRef.m_pPrev = &rNewChild;

	if( pRefPrev )
		pRefPrev->m_pNext = &rNewChild;

	if( m_pFirst == &rRef )
		m_pFirst = &rNewChild;

	AttachChild( rNewChild );

	return &rNewChild;
}

CGObjectNode* CGObjectNode::InsertAfter( CGObjectNode& rNewChild, CGObjectNode& rRef ) 
{
	CLockCriticalSection cs( m_cSect ); 

	if( &rNewChild == &rRef )
		return NULL;

	if( FALSE == IsChildNode( rRef ) )
		return NULL;
	
	if( IsChildNode( rNewChild ) )
		return NULL;

	OnNodeListModified();

	CGObjectNode* pRefNext = rRef.m_pNext;
	rNewChild.m_pPrev = &rRef;
	rNewChild.m_pNext = rRef.m_pNext;
	rRef.m_pNext = &rNewChild;

	if( pRefNext )
		pRefNext->m_pPrev = &rNewChild;

	if( m_pLast == &rRef )
		m_pLast = &rNewChild;

	AttachChild( rNewChild );

	return &rNewChild;
}

CGObjectNode* CGObjectNode::ReplaceChild( CGObjectNode& rNewChild, CGObjectNode& rOldNode )
{
	CLockCriticalSection cs( m_cSect ); 

	if( &rNewChild == &rOldNode )
		return NULL;

	if( FALSE == IsChildNode( rOldNode ) )
		return NULL;
	
	if( IsChildNode( rNewChild ) )
		return NULL;

	DetachChild( rOldNode );

	OnNodeListModified();

	rNewChild.m_pPrev = rOldNode.m_pPrev;
	rNewChild.m_pNext = rOldNode.m_pNext;
	rOldNode.ResetLink();

	if( m_pFirst == &rOldNode )
		m_pFirst = &rNewChild;

	if( m_pLast == &rOldNode )
		m_pLast = &rNewChild;
	
	AttachChild( rNewChild );

	return &rNewChild;
}

CGObjectNode* CGObjectNode::AppendChild( CGObjectNode& rNewChild )
{
	CLockCriticalSection cs( m_cSect ); 

	if( IsChildNode( rNewChild ) )
		return NULL;

	OnNodeListModified();

	if( m_pLast )
		m_pLast->m_pNext = &rNewChild;

	rNewChild.m_pPrev = m_pLast;
	rNewChild.m_pNext = NULL;
	
	m_pLast = &rNewChild;
	if( NULL == m_pFirst )
		m_pFirst = m_pLast;

	AttachChild( rNewChild );

	return &rNewChild;
}

CGObjectNode* CGObjectNode::RemoveChild( CGObjectNode& rChild )
{
	CLockCriticalSection cs( m_cSect ); 

	if( FALSE == IsChildNode( rChild ) )
		return NULL;

	DetachChild( rChild );

	OnNodeListModified();

	if( m_pFirst == &rChild )
	{
		if( m_pLast == &rChild )
		{
			m_pFirst = NULL;
			m_pLast = NULL;
		}
		else
			m_pFirst = m_pFirst->m_pNext;
	}
	else if( m_pLast == &rChild )
		m_pLast = m_pLast->m_pPrev;
	else
	{
		CGObjectNode* pPrev = rChild.m_pPrev;
		CGObjectNode* pNext = rChild.m_pNext;
		pNext->m_pPrev = pPrev;
		pPrev->m_pNext = pNext;
	}

	rChild.ResetLink();

	return &rChild;
}

BOOL CGObjectNode::IsChildNode( const CGObjectNode& rNode, BOOL bDeepSearch /*= FALSE*/ ) const
{
	CLockCriticalSection cs( m_cSect ); 

	CGObjectNode* piNode = m_pFirst;
	while( piNode )
	{
		if( piNode == &rNode )
			return TRUE;

		piNode = piNode->GetNextNode();
	}

	if( bDeepSearch )
	{
		piNode = m_pFirst;
		while( piNode )
		{
			if( piNode->IsChildNode( rNode, bDeepSearch ) )
				return TRUE;

			piNode = piNode->GetNextNode();
		}
	}

	return FALSE;
}

BOOL CGObjectNode::IsSibilingNode( const CGObjectNode& rNode ) const
{
	const CGObjectNode* piNode = this;
	CLockCriticalSection cs( m_cSect ); 
	while( piNode )
	{
		if( piNode == &rNode ) 
			return TRUE;

		piNode = piNode->GetNextNode();
	}

	return FALSE;
}

void CGObjectNode::AttachChild( CGObjectNode& rNode )
{
	rNode.m_pParent = this;
	Attach( rNode );
}

void CGObjectNode::Attach( CGObjectNode& rNode ) 
{
	CLockCriticalSection cs( m_cSect ); 
	CGObjectNode* piNode = rNode.m_pFirst;
	while( piNode )
	{
		rNode.Attach( *piNode );
		piNode = piNode->GetNextNode();
	}
}

void CGObjectNode::DetachChild( CGObjectNode& rNode )
{
	Detach( rNode );
	rNode.m_pParent = NULL;
}

void CGObjectNode::Detach( CGObjectNode& rNode )
{
	CLockCriticalSection cs( m_cSect ); 
	CGObjectNode* piNode = rNode.m_pFirst;
	while( piNode )
	{
		rNode.Detach( *piNode );
		piNode = piNode->GetNextNode();
	}
}

void CGObjectNode::ResetLink()
{
	m_pNext = NULL;
	m_pPrev = NULL;
}
