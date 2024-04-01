#include "stdafx.h"
#include <g\type\gNode.h>
#include <g\type\idom\giDocument.h>
#include <g\type\gElement.h>
#include <g\type\idom\giNodeList.h>
#include <g\type\idom\giNodeMap.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
CGNodeList::CGNodeList()
{
    m_piNodeList = NULL;
}

CGNodeList::CGNodeList( CGINodeList* piNode )
{
    m_piNodeList = piNode;
}

CGNodeList::CGNodeList( const CGNodeList& rNodeList )
{
    m_piNodeList = rNodeList.m_piNodeList;
    if( m_piNodeList )
        m_piNodeList->AddRef();
}

CGNodeList& CGNodeList::operator=( const CGNodeList& rNodeList )
{
    CGINodeList* piNodeList = rNodeList.m_piNodeList;
    if( piNodeList )
        piNodeList->AddRef();

    if( m_piNodeList )
        piNodeList->Release();

	m_piNodeList = piNodeList;
    return *this;
}

BOOL CGNodeList::operator==( const CGNodeList& rNodeList ) const
{
    if( m_piNodeList == rNodeList.m_piNodeList )
        return TRUE;

    if( NULL == m_piNodeList || NULL == rNodeList.m_piNodeList )
        return FALSE;

    return (*m_piNodeList == *rNodeList.m_piNodeList);
}

BOOL CGNodeList::operator!=( const CGNodeList& rNodeList ) const
{
    return !operator==( rNodeList );
}

CGNodeList::~CGNodeList()
{
    if( m_piNodeList )
        m_piNodeList->Release();
}

CGNode CGNodeList::GetItem( INT nIndex ) const
{
    if( NULL == m_piNodeList )
        return CGNode();

    return CGNode( m_piNodeList->GetItem( nIndex ) );
}

UINT CGNodeList::GetLength() const
{
    if( NULL == m_piNodeList )
        return 0;

    return m_piNodeList->GetLength();
}

void CGNodeList::CreateList()
{
    if( NULL == m_piNodeList )
        return;

	m_piNodeList->CreateList();
}

#ifdef _DEBUG
void CGNodeList::Dump( CDumpContext& dc ) const
{
	dc << "[CGNodeList]: Begin\n";
	if( NULL == m_piNodeList )
	{
		dc << "Null node list\n";
		dc << "[CGNodeList]: End\n";
        return;
	}

	m_piNodeList->Dump( dc );

	dc << "[CGNodeList]: End\n";
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
CGNamedNodeMap::CGNamedNodeMap() {
    m_piNodeMap = 0; }

CGNamedNodeMap::CGNamedNodeMap( const CGNamedNodeMap& rNodeMap )
{
    m_piNodeMap = rNodeMap.m_piNodeMap;
    if( m_piNodeMap )
        m_piNodeMap->AddRef();
}

CGNamedNodeMap::CGNamedNodeMap( CGINamedNodeMap* piNodeMap )
{
    m_piNodeMap = piNodeMap;
    if( m_piNodeMap )
        m_piNodeMap->AddRef();
}

CGNamedNodeMap::~CGNamedNodeMap()
{
    if( m_piNodeMap )
        m_piNodeMap->Release();
}
 
CGNamedNodeMap& CGNamedNodeMap::operator=( const CGNamedNodeMap& rNodeMap )
{
    CGINamedNodeMap* piNodeMap = rNodeMap.m_piNodeMap;
    if( piNodeMap )
        piNodeMap->AddRef();

    if( m_piNodeMap )
        m_piNodeMap->Release();

	m_piNodeMap = piNodeMap;
    return *this;
}

BOOL CGNamedNodeMap::operator==( const CGNamedNodeMap& rNodeMap ) const {
    return (m_piNodeMap == rNodeMap.m_piNodeMap); }

BOOL CGNamedNodeMap::operator!=( const CGNamedNodeMap& rNodeMap ) const {
    return (m_piNodeMap != rNodeMap.m_piNodeMap); }


CGNode CGNamedNodeMap::GetNamedItem( LPCTSTR ptszName ) const
{
    if( NULL == m_piNodeMap )
        return CGNode();

    return CGNode( m_piNodeMap->GetNamedItem( ptszName ) );
}

CGNode CGNamedNodeMap::SetNamedItem( const CGNode& rNode )
{
    if( NULL == m_piNodeMap )
        return CGNode();

    return CGNode( m_piNodeMap->SetNamedItem( (CGINode*)rNode.m_piNode ) );
}

CGNode CGNamedNodeMap::RemoveNamedItem( LPCTSTR ptszName )
{
    if( NULL == m_piNodeMap )
        return CGNode();

    return CGNode( m_piNodeMap->RemoveNamedItem( ptszName ) );
}

CGNode CGNamedNodeMap::GetItem( INT nIndex ) const
{
    if( NULL == m_piNodeMap )
        return CGNode();

    return CGNode( m_piNodeMap->GetItem( nIndex ) );
}

CGNode CGNamedNodeMap::GetNamedItemNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName ) const
{
    if( NULL == m_piNodeMap )
        return CGNode();

    return CGNode( m_piNodeMap->GetNamedItemNS( ptszNsURI, ptszLocalName ) );
}

CGNode CGNamedNodeMap::SetNamedItemNS( const CGNode& rNode )
{
    if( NULL == m_piNodeMap )
        return CGNode();

    return CGNode( m_piNodeMap->SetNamedItemNS( (CGINode*)rNode.m_piNode ) );
}

CGNode CGNamedNodeMap::RemoveNamedItemNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName )
{
    if( NULL == m_piNodeMap )
        return CGNode();

    CGINode* piNode = m_piNodeMap->GetNamedItemNS( ptszNsURI, ptszLocalName );
    if( NULL == piNode )
        return CGNode();
	 
    return CGNode( m_piNodeMap->RemoveNamedItem( piNode->GetName() ) );
}

UINT CGNamedNodeMap::GetLength() const
{
    if( NULL == m_piNodeMap )
        return 0;

    return m_piNodeMap->GetLength();
}

BOOL CGNamedNodeMap::FindItem( LPCTSTR  ptszName ) const
{
    if( NULL == m_piNodeMap )
        return FALSE;

    return m_piNodeMap->FindItem( ptszName );
}

BOOL CGNamedNodeMap::FindItemNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName ) const
{
    if( NULL == m_piNodeMap )
        return FALSE;

    return m_piNodeMap->FindItemNS( ptszNsURI, ptszLocalName );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CGNode::CGNode()
{
	m_piNode = NULL;
}

CGNode::CGNode( const CGNode& rNode )
{
	m_piNode = rNode.m_piNode;
    if( m_piNode )
        m_piNode->AddRef();
}

CGNode::CGNode( CGINode* piNode )
{
    m_piNode = piNode;
    if( m_piNode )
        m_piNode->AddRef();
}

CGNode::~CGNode()
{
	if( m_piNode )
		m_piNode->Release();
}

CGNode& CGNode::operator=( const CGNode& rNode )
{
    CGINode* piNode = rNode.m_piNode;
    if( piNode )
        piNode->AddRef();

	if( m_piNode )
		m_piNode->Release();

	m_piNode = piNode;
    return *this;
}

BOOL CGNode::operator==( const CGNode& rNode ) const {
    return (m_piNode == rNode.m_piNode); }

BOOL CGNode::operator!=( const CGNode& rNode ) const {
    return (m_piNode != rNode.m_piNode); }

CString CGNode::GetNodeName() const
{
	CString csz;
	if( NULL == m_piNode )
		return csz;

	csz = m_piNode->GetNodeName();
	return csz;
}

void CGNode::GetNodeName( CString& rNodeName ) const
{
	if( NULL == m_piNode )
	{
		rNodeName.Empty();
		return;
	}

	m_piNode->GetNodeName( rNodeName );
}


/// raises(IDOMException) on retrieval
///		DOMSTRING_SIZE_ERR: Raised when it would return more
///		characters than fit in a DOMString [p.17] variable on the
CString CGNode::GetNodeValue() const
{
	CString csz;
	GetNodeValue( csz );

	return csz;
}

/// raises(IDOMException) on retrieval
///		DOMSTRING_SIZE_ERR: Raised when it would return more
///		characters than fit in a DOMString [p.17] variable on the
void CGNode::GetNodeValue( CString& cszValue ) const
{
	if( NULL == m_piNode )
	{
		cszValue.Empty();
		return;
	}

	m_piNode->GetNodeValue( cszValue );
}

BOOL CGNode::SetNodeValue( LPCTSTR pctszValue )
{
	if( NULL == m_piNode )
		return FALSE;

	return m_piNode->SetNodeValue( pctszValue );
}

BOOL CGNode::SetNodeValue( const CString& rcszValue )
{
	if( NULL == m_piNode )
		return FALSE;

	return m_piNode->SetNodeValue( rcszValue );
}

INT CGNode::GetNodeType()
{
	if( NULL == m_piNode )
		return _NODE;

	return m_piNode->GetNodeType();
}

CGNodeList CGNode::GetNodeList() const
{
	if( NULL == m_piNode )
		return CGNodeList();

	return CGNodeList( new CGINodeList( m_piNode ) );
}

const CGNodeList CGNode::GetNodeList()
{
	if( NULL == m_piNode )
		return CGNodeList();

	return CGNodeList( new CGINodeList( m_piNode ) );
}

CGNode CGNode::GetParentNode() const
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->GetParent() );
}

const CGNode CGNode::GetParentNode()
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->GetParent() );
}

CGNode CGNode::GetFirstChild() const 
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->GetFirst() );
}

const CGNode CGNode::GetFirstChild()
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->GetFirst() );
}

CGNode CGNode::GetLastChild() const
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->GetLast() );
}

const CGNode CGNode::GetLastChild()
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->GetLast() );
}

CGNode CGNode::GetPreviousSibling()
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->GetPrev() );
}

const CGNode CGNode::GetPreviousSibling() const
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->GetPrev() );
}

CGNode CGNode::GetNextSibling()
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->GetNext() );
}

const CGNode CGNode::GetNextSibling() const
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->GetNext() );
}

CGNamedNodeMap CGNode::GetAttributes() const
{
    if( NULL == m_piNode || m_piNode->IsKindOf( CGNode::ELEMENT_NODE ) )
        return CGNamedNodeMap();

    return CGNamedNodeMap( static_cast<CGIElement*>(m_piNode)->GetAttributes() );
}

CGDocument CGNode::GetOwnerDocument() 
{
	if( NULL == m_piNode )
		return CGDocument();

	return CGDocument( m_piNode->GetOwnerDocument() );
}

const CGDocument CGNode::GetOwnerDocument() const 
{
	if( NULL == m_piNode )
		return CGDocument();

	return CGDocument( m_piNode->GetOwnerDocument() );
}

CGNode CGNode::InsertBefore( CGNode& rNewChild, CGNode& rRef )
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->InsertBefore( *rNewChild.m_piNode, *rRef.m_piNode ) );
}

CGNode CGNode::InsertAfter( CGNode& rNewChild, CGNode& rRef )
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->InsertAfter( *rNewChild.m_piNode, *rRef.m_piNode ) );
}

CGNode CGNode::ReplaceChild( CGNode& rNewChild,	CGNode& rOldChild )
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->ReplaceChild( *rNewChild.m_piNode, *rOldChild.m_piNode ) );
}

CGNode CGNode::AppendChild( CGNode& rNewChild )
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->AppendChild( *rNewChild.m_piNode ) );
}

CGNode CGNode::RemoveChild( CGNode& rOldChild )
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->AppendChild( *rOldChild.m_piNode ) );
}

BOOL CGNode::HasChildNodes() const
{
	if( NULL == m_piNode )
		return FALSE;

	return m_piNode->HasChildNodes();
}

CGNode CGNode::CloneNode( BOOL bDeep ) const
{
	if( NULL == m_piNode )
		return CGNode();

	return CGNode( m_piNode->CloneNode( bDeep ) );
}

void CGNode::Normalize()
{
	if( NULL == m_piNode )
		return;

	m_piNode->Normalize();
}

BOOL CGNode::IsSupported( LPCTSTR pctszFeature, LPCTSTR pctszVersion ) const
{
	if( NULL == m_piNode )
		return FALSE;

	return m_piNode->IsSupported( pctszFeature, pctszVersion );
}

CString CGNode::GetNameSpaceURI() const
{
	if( NULL == m_piNode )
		return CString();

	return m_piNode->GetNameSpaceURI();
}

void CGNode::GetNameSpaceURI( CString& rcszNameSpaceURI ) const
{
	if( NULL == m_piNode )
	{
		rcszNameSpaceURI.Empty();
		return;
	}

	m_piNode->GetNameSpaceURI( rcszNameSpaceURI );
}

CString CGNode::GetPrefix() const
{
	if( NULL == m_piNode )
		return CString();

	return m_piNode->GetPrefix();
}

void CGNode::GetPrefix( CString& rcszPrefix ) const
{
	if( NULL == m_piNode )
	{
		rcszPrefix.Empty();
		return;
	}

	m_piNode->GetPrefix( rcszPrefix );
}

CString CGNode::GetLocalName() const
{
	if( NULL == m_piNode )
		return CString();

	return m_piNode->GetLocalName();
}

void CGNode::GetLocalName( CString& rcszLocalName ) const
{
	if( NULL == m_piNode )
	{
		rcszLocalName.Empty();
		return;
	}

	m_piNode->GetLocalName( rcszLocalName );
}

BOOL CGNode::HasAttributes() const
{
	if( NULL == m_piNode )
		return FALSE;

	return m_piNode->HasAttributes();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
CGDocument::CGDocument() 
{}

CGDocument::CGDocument( LPCTSTR pctszName )
{
	m_piNode = new CGIDocument( pctszName );
}

CGDocument::CGDocument( const CGDocumentType& rDoctype )
{
	m_piNode = new CGIDocument( (CGIDocumentType*)(rDoctype.m_piNode) );
}

CGDocument::CGDocument( const CGDocument& rDocument )
 : CGNode( rDocument )
{}

CGDocument::CGDocument( CGIDocument* piDocument )
: CGNode( piDocument )
{}

CGDocument::~CGDocument()
{}

CGDocument& CGDocument::operator=( const CGDocument& rDocument ) {
	return (CGDocument&) CGNode::operator=( rDocument ); }

CGDocumentType CGDocument::Doctype() const
{
	if( NULL == m_piNode )
		return CGDocumentType();

	return CGDocumentType( ((CGIDocument*)m_piNode)->GetDoctype() );
}


///////////////////////////////////////////////////////////////////////////////////////////////////
#define m__piNode ((CGIDocumentType*)m_piNode)

CGDocumentType::CGDocumentType()
{}

CGDocumentType::CGDocumentType( const CGDocumentType& rDocumentType )
 : CGNode( rDocumentType )
{}

CGDocumentType::CGDocumentType( CGIDocumentType* piDocumentType )
 : CGNode( piDocumentType )
{}

CGDocumentType& CGDocumentType::operator=( const CGDocumentType& rDocumentType ) {
	return (CGDocumentType&) CGNode::operator=( rDocumentType ); }

CString CGDocumentType::GetName() const
{
	CString csz;
	if( NULL == m_piNode )
		return csz;

	m_piNode->GetNodeName( csz );
	return csz;
}

CGNamedNodeMap CGDocumentType::GetEntities() const
{
	if( NULL == m_piNode )
		return CGNamedNodeMap();

	return CGNamedNodeMap( m__piNode->GetEntities() );
}

CGNamedNodeMap CGDocumentType::GetNotations() const
{
	if( NULL == m_piNode )
		return CGNamedNodeMap();

	return CGNamedNodeMap( m__piNode->GetNotations() );
}

CString CGDocumentType::GetPublicId() const
{
	if( NULL == m_piNode )
		return CString();

	return m__piNode->GetPublicId();
}

CString CGDocumentType::GetSystemId() const
{
	if( NULL == m_piNode )
		return CString();

	return m__piNode->GetSystemId();
}

CString CGDocumentType::GetInternalSubset() const
{
	if( NULL == m_piNode )
		return CString();

	return m__piNode->GetSystemId();
}

#undef m__piNode