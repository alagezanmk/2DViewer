#include "stdafx.h"
#include <g\type\idom\giNodeList.h>
#include <g\type\idom\giNode.h>
#include <g\type\idom\giElement.h>
#include <g\type\gPriv.h>
#include <g\type\gEventPriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
LPCTSTR CGDomMutationEvent::DOMExtUpdateAttr = _T("DOMExtUpdateAttr");
LPCTSTR CGDomMutationEvent::DOMExtValidateAttr = _T("DOMExtValidateAttr");

CGDomMutationEvent::CGDomMutationEvent()
{}

CGDomMutationEvent::~CGDomMutationEvent()
{
	if( m_pRelatedNode && m_pRelatedNode->IsDerivedFrom( CGIAttr::GetClassType() ) )
	{
		CGIAttr* pRelatedNode = (CGIAttr*)m_pRelatedNode;
		if( m_pvPreviousValue )
			pRelatedNode->DeletePreviousValuePointer( m_pvPreviousValue );

		if( m_pvNewValue )
			pRelatedNode->DeleteNewValuePointer( m_pvNewValue );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGDomMutationEventPriv : public CGDomMutationEvent
{
public:
	CGDomMutationEventPriv( LPCTSTR pctszEventType, CGEventTarget* pTarget );
};

///////////////////////////////////////////////////////////////////////////////////////////////////
CGDomMutationEventPriv::CGDomMutationEventPriv( LPCTSTR pctszEventType, CGEventTarget* pTarget )
{
	m_pctszEventType = pctszEventType;
	m_pEventTarget = pTarget;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void CGINameSpaceString::SplitQualifiedName( CString& rcszPrefix, CString& rcszName, LPCTSTR pctszQualifiedName, 
											 BOOL bHasURI /*= FALSE*/ )
{
    LPTSTR ptszChar = (LPTSTR)_tcschr( pctszQualifiedName, _T(':') );
    if( NULL == ptszChar ) 
	{
		rcszPrefix.Empty();
        rcszName = pctszQualifiedName;
    } 
	else 
	{
		INT nLength = (ptszChar - pctszQualifiedName) / sizeof(TCHAR);
		lstrcpyn( rcszPrefix.GetBuffer( nLength ), pctszQualifiedName, nLength + 1 );
		rcszPrefix.ReleaseBuffer();

		rcszName = ptszChar + 1;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
IMPL_GTPYECLASS_DYNCREATE( CGINode, CGEventNode, _T("node") )
CGINode::CGINode() {
	Construct(); }	

CGINode::CGINode( CGIDocument* piDocument, CGINode* piParent /*= NULL*/ )
{
	Construct();
	m_pOwnerDocument = piDocument;
	m_pParent = piParent;
}

CGINode::CGINode( CGINode* piNode, BOOL bDeep /*= FALSE*/ )
{
	Construct();
	m_pOwnerDocument = piNode->GetOwnerDocument();
	m_pParent = piNode;

	piNode->GetNodeName( m_cszName );
	SetPrefix( piNode->GetPrefix() );
	SetNameSpaceURI( piNode->GetNameSpaceURI() );

	SetNodeValue( piNode->GetNodeValue() );

	if( FALSE == bDeep )
		return;

	CGINode* piItrNode = piNode->GetFirst();
	while( piItrNode )
	{
		AppendChild( *piItrNode->CloneNode( TRUE ) );
		piItrNode = piItrNode->GetNext();
	}
}

void CGINode::Construct()
{
	m_pgInstanceType = &GetClassType();
	m_pOwnerDocument = NULL;

	m_nNodeFlag = 0;
	m_pmapUserDataToKey = NULL;
}

CGINode::~CGINode()
{
	RemoveAllEventListener();
	RemoveAllPendingEvent();

	RemoveAllChild();

	if( m_pmapUserDataToKey )
		delete m_pmapUserDataToKey;
}

void CGINode::OnNodeListModified() {
	CGINodeList::m_lNodeListTime++; }

BOOL CGINode::OnInitialUpdate() {
	return TRUE; }

CString CGINode::GetNodeName() const 
{
	CString cszNodeName;
	GetNodeName( cszNodeName );
	return cszNodeName; 
}

void CGINode::GetNodeName( CString& rcszNodeName ) const 
{
	rcszNodeName.Empty();

	LPCTSTR ptszPrefix = GetPrefix();
	if( ptszPrefix && ptszPrefix[0] )
		rcszNodeName.Format( _T("%s:%s"), ptszPrefix, m_cszName );
	else
		rcszNodeName = m_cszName;
}

void CGINode::SetNodeName( LPCTSTR pctszName )
{
	if( _tcschr( pctszName, _T(':') ) )
	{
		CString cszPrefix, cszName;
		CGINameSpaceString::SplitQualifiedName( cszPrefix, cszName, pctszName, TRUE );
		m_cszName = cszName;
		SetPrefix( cszPrefix );
		return;
	}

	m_cszName = pctszName;
	SetPrefix( NULL );
}

BOOL CGINode::SetNodeValue( LPCTSTR pctszValue ) {
	return TRUE; }

BOOL CGINode::SetNodeValue( const CString& rcszValue ) {
	return TRUE; }

CGINodeList* CGINode::GetChildNodes()
{
	CGINodeList* piNodeList = new CGINodeList( this );
	if( NULL == piNodeList )
	{
		ASSERT( piNodeList );
	}

	return piNodeList;
}

CGINode* CGINode::CloneNode( BOOL bDeep ) const {
	return NULL; }

CGINode* CGINode::InsertBefore( CGINode& rNewChild, CGINode& rRef ) {
	return (CGINode*)CGEventNode::InsertBefore( rNewChild, rRef ); }

CGINode* CGINode::InsertAfter( CGINode& rNewChild, CGINode& rRef ) {
	return (CGINode*)CGEventNode::InsertAfter( rNewChild, rRef ); }

CGINode* CGINode::AppendChild( CGINode& rNewChild ) {
	return (CGINode*)CGEventNode::AppendChild( rNewChild ); }

CGINode* CGINode::ReplaceChild( CGINode& rNewChild, CGINode& rOldNode )
{
	CGINode* pNewChild = (CGINode*)CGEventNode::ReplaceChild( rNewChild, rOldNode );
	if( pNewChild )
		rOldNode.Release();

	return pNewChild;
}

CGINode* CGINode::RemoveChild( CGINode& rChild )
{
	CGINode* pOldNode = (CGINode*)CGEventNode::RemoveChild( rChild );
	if( pOldNode )
	{
		INT nRefCnt = rChild.m_dwRefCnt;
		rChild.Release();
		if( nRefCnt <= 1 )
			return NULL;
	}

	return pOldNode;
}

void CGINode::RemoveAllChild() 
{
	CGINode* pNode = GetLast();
	CGINode* pPrev;
	while( pNode )
	{
		pPrev = pNode->GetPrev();
		RemoveChild( *pNode );
		pNode = pPrev;
	}
}

void CGINode::Normalize() 
{}

BOOL CGINode::IsSupported( LPCTSTR pctszFeature,
						   LPCTSTR pctszVersion ) const 
{
	ASSERT( FALSE );
	//TODO
    //CGIImplementation impl;
    //return impl.HasFeature( pctszFeature, pctszVersion );
	return FALSE;
}

LPCTSTR CGINode::GetLocalName() const {
	return m_cszName; }

void CGINode::GetLocalName( CString& rcszLocalName ) const {
	rcszLocalName = m_cszName; }

void* CGINode::SetUserData( LPCTSTR pctszKey, 
						    void* pData /*= NULL*/,
					        CGUserDataHandler* pHandler /*= NULL*/ )
{
	void* pOldData = NULL;
	if( NULL == _Create( m_pmapUserDataToKey ) )
	{
		ASSERT( FALSE );
		return NULL;
	}

	m_pmapUserDataToKey->Lookup( pctszKey, pOldData );
	m_pmapUserDataToKey->SetAt( pctszKey, pData );

	return pOldData;
}

void* CGINode::GetUserData( LPCTSTR pctszKey ) const
{
	if( NULL == m_pmapUserDataToKey )
		return NULL;

	void* pOldData = NULL;
	m_pmapUserDataToKey->Lookup( pctszKey, pOldData );

	return pOldData;
}

void* CGINode::RemoveUserData( LPCTSTR pctszKey )
{
	if( NULL == m_pmapUserDataToKey )
		return NULL;

	void* pOldData = NULL;
	m_pmapUserDataToKey->Lookup( pctszKey, pOldData );
	m_pmapUserDataToKey->RemoveKey( pctszKey );
	_DeleteIfEmpty( m_pmapUserDataToKey );

	return pOldData;
}

CString CGINode::GetQualifiedName() const 
{
	CString cszQName;
	GetQualifiedName( cszQName );
	return cszQName; 
}

void CGINode::GetQualifiedName( CString& rcszQName ) const {
	GetNodeName( rcszQName ); }

/// Note: CGINode::DetachChild is not necessary to override for rNode.Release()
/// as AttachChild which is for AddRef. rNode.Release() is done in RemoveChild()
/// and ReplaceChild
void CGINode::AttachChild( CGEventNode& rNode ) 
{
	if( rNode.IsDerivedFrom( CGINode::GetClassType() ) )
		((CGINode*)&rNode)->AddRef();

	CGEventNode::AttachChild( rNode );
}

void CGINode::Attach( CGEventNode& rNode )
{
	if( rNode.IsDerivedFrom( CGINode::GetClassType() ) )
		((CGINode*)&rNode)->m_pOwnerDocument = m_pOwnerDocument;

	CGEventNode::Attach( rNode );
}

void CGINode::Detach( CGEventNode& rNode )
{
	CGEventNode::Detach( rNode );

	if( rNode.IsDerivedFrom( CGINode::GetClassType() ) )
		((CGINode*)&rNode)->m_pOwnerDocument = NULL;
}

INT CGINode::SetNodeFlag( INT nFlag, BOOL bSet /*= TRUE*/ )
{
	INT nOldFlag = m_nNodeFlag;
	if( bSet )
		m_nNodeFlag |= nFlag;
	else
		m_nNodeFlag &= ~nFlag;

	return nOldFlag;
}

#ifdef _DEBUG
void CGINode::OnFinalRelease()
{
	CGObject::OnFinalRelease();
	TRACE( _T("\tCGINode::%s\n"), m_cszName );
}

void CGINode::Dump( CDumpContext& dc ) const
{
	CGObject::Dump( dc );
	dc << "CGINode:\n";

	CLockCriticalSection cs( m_cSect ); 
	CGINode* piNode = (CGINode*)m_pFirst;
	while( piNode )
	{
		dc << "[Node:" << piNode << ", " << piNode->m_cszName << "]\n";
		piNode = (CGINode*)piNode->m_pNext;

	}
}
#endif

CGMutationEvent* CGINode::CreateAttrModifiedMutationEvent( LPCTSTR pctszEventType )
{
	if( CGMutationEvent::DOMAttrModified != pctszEventType )
		return CGEventNode::CreateAttrModifiedMutationEvent( pctszEventType );

	CGDomMutationEventPriv* pEvent = new CGDomMutationEventPriv( pctszEventType, this );
	ASSERT( pEvent );
	return pEvent;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGICharacterData::Setdata( LPCTSTR pctszData ) 
{
	m_cszData = pctszData;
	return TRUE;
}

void CGICharacterData::GetSubstringData( INT nOffset,
										INT nCount,
										CString& rcszData ) const {
	rcszData = m_cszData.Mid( nOffset, nCount ); }

void CGICharacterData::AppendData( LPCTSTR pctszArg ) {
	m_cszData += pctszArg; }

void CGICharacterData::InsertData( INT nOffset,
								  LPCTSTR pctszArg ) {
	m_cszData.Insert( nOffset, pctszArg ); }

void CGICharacterData::DeleteData( INT nOffset,
 								  INT nCount ) {
	m_cszData.Delete( nOffset, nCount ); }

void CGICharacterData::ReplaceData( INT nOffset,
								   INT nCount,
								   LPCTSTR pctszArg )
{
	ASSERT( FALSE );
	//m_cszData.Replace( nOffset, nCount, pctszArg );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CGIDocumentType::CGIDocumentType( CGIDocument* piDocument, CGINode* piParent /*= NULL*/ )
 : CGINode( piDocument, piParent )
{
	Construct();
}

CGIDocumentType::CGIDocumentType( CGIDocumentType* piDocumentType, BOOL bDeep )
: CGINode( piDocumentType, bDeep )
{
    Construct();

    // Refill the maps with our new children
    CGINode* piItrNode = GetFirst();
    while( piItrNode ) 
	{
        if( piItrNode->IsKindOf( CGNode::ENTITY_NODE ) )
            // Dont use normal insert function since we would create infinite recursion
            m_pimapEntities->m_mapNameToNode.SetAt( piItrNode->GetNodeName(), piItrNode );

        if( piItrNode->IsKindOf( CGNode::NOTATION_NODE ) )
            // Dont use normal insert function since we would create infinite recursion
			m_pimapNotations->m_mapNameToNode.SetAt( piItrNode->GetNodeName(), piItrNode );

		ASSERT( FALSE ); ///TODO: Check if next itertortion needed
		piItrNode = piItrNode->GetNext();
    }
}

void CGIDocumentType::Construct()
{
    VERIFY( m_pimapEntities = new CGINamedNodeMap( this ) );
	m_pimapEntities->AddRef();

    VERIFY( m_pimapNotations = new CGINamedNodeMap( this ) );
	m_pimapNotations->AddRef();

    m_pimapEntities->SetAppendToParent( TRUE );
    m_pimapNotations->SetAppendToParent( TRUE );
}

CGIDocumentType::~CGIDocumentType()
{
	if( m_pimapEntities )
		m_pimapEntities->Release();

	if( m_pimapNotations )
		m_pimapNotations->Release();
}

CGINode* CGIDocumentType::CloneNode( BOOL bDeep /*= TRUE*/ )
{
    CGINode* piNode = new CGIDocumentType( this, bDeep );
	ASSERT( piNode );

    return piNode;
}

CGINode* CGIDocumentType::InsertBefore( CGINode& rNewChild, CGINode& rRef )
{
    // Call the original implementation
    CGINode* piNode = CGINode::InsertBefore( rNewChild, rRef );
	if( piNode )
	{
		// Update the maps
		if( piNode->IsKindOf( CGNode::ENTITY_NODE ) )
			m_pimapEntities->m_mapNameToNode.SetAt( piNode->GetNodeName(), piNode );
		 else if( piNode->IsKindOf( CGNode::NOTATION_NODE ) )
			m_pimapNotations->m_mapNameToNode.SetAt( piNode->GetNodeName(), piNode );
	}

    return piNode;
}

CGINode* CGIDocumentType::InsertAfter( CGINode& rNewChild, CGINode& rRef )
{
    // Call the original implementation
    CGINode* piNode = CGINode::InsertAfter( rNewChild, rRef );
	if( piNode )
	{
		// Update the maps
		if( piNode->IsKindOf( CGNode::ENTITY_NODE ) )
			m_pimapEntities->m_mapNameToNode.SetAt( piNode->GetNodeName(), piNode );
		 else if( piNode->IsKindOf( CGNode::NOTATION_NODE ) )
			m_pimapNotations->m_mapNameToNode.SetAt( piNode->GetNodeName(), piNode );
	}

    return piNode;
}

CGINode* CGIDocumentType::ReplaceChild( CGINode& rNewChild, CGINode& rOldNode )
{
    // Call the original implementation
    CGINode* piNode = CGINode::ReplaceChild( rNewChild, rOldNode );
	if( piNode )
	{
		// Update the maps
		if( rOldNode.IsKindOf( CGNode::ENTITY_NODE ) )
			m_pimapEntities->m_mapNameToNode.RemoveKey( rOldNode.GetNodeName() );
		 else if( rOldNode.IsKindOf( CGNode::NOTATION_NODE ) )
			m_pimapNotations->m_mapNameToNode.RemoveKey( rOldNode.GetNodeName() );

		// Update the maps
		if( piNode->IsKindOf( CGNode::ENTITY_NODE ) )
			m_pimapEntities->m_mapNameToNode.SetAt( rOldNode.GetNodeName(), piNode );
		 else if( piNode->IsKindOf( CGNode::NOTATION_NODE ) )
			m_pimapNotations->m_mapNameToNode.SetAt( rOldNode.GetNodeName(), piNode );
	}

    return piNode;
}

CGINode* CGIDocumentType::AppendChild( CGINode& rNewChild )
{
    // Call the original implementation
    CGINode* piNode = CGINode::AppendChild( rNewChild );
	if( piNode )
	{
		// Update the maps
		if( piNode->IsKindOf( CGNode::ENTITY_NODE ) )
			m_pimapEntities->m_mapNameToNode.SetAt( piNode->GetNodeName(), piNode );
		 else if( piNode->IsKindOf( CGNode::NOTATION_NODE ) )
			m_pimapNotations->m_mapNameToNode.SetAt( piNode->GetNodeName(), piNode );
	}

	return piNode;
}

CGINode* CGIDocumentType::RemoveChild( CGINode& rChild )
{
    // Call the original implementation
    CGINode* piNode = CGINode::AppendChild( rChild );
	if( piNode )
	{
		// Update the maps
		if( rChild.IsKindOf( CGNode::ENTITY_NODE ) )
			m_pimapEntities->m_mapNameToNode.RemoveKey( rChild.GetNodeName() );
		 else if( rChild.IsKindOf( CGNode::NOTATION_NODE ) )
			m_pimapNotations->m_mapNameToNode.RemoveKey( rChild.GetNodeName() );
	}

	return piNode;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CGIImplementation::CGIImplementation()
{}

CGIImplementation* CGIImplementation::Clone()
{
	CGIImplementation* piImplementation = new CGIImplementation;
	ASSERT( piImplementation );

	return piImplementation;
}
