#include "stdafx.h"
#include <g\type\idom\giNodeMap.h>
#include <g\type\idom\giNode.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGINamedNodeMap::CGINamedNodeMap( CGINode* piNode )
{
    m_bReadonly = FALSE;
    m_piParentNode = piNode;
    m_bAppendToParent = FALSE;
}

CGINamedNodeMap::~CGINamedNodeMap()
{
    ClearMap();
}

CGINamedNodeMap* CGINamedNodeMap::Clone( CGINode* piParentNode )
{
    CGINamedNodeMap* piNM = new CGINamedNodeMap( piParentNode );
    piNM->m_bReadonly = m_bReadonly;
    piNM->m_bAppendToParent = m_bAppendToParent;

	void* pNode;
	CString cszKey;
	CGINode* piNode, *piNewNode;
	POSITION pos = m_mapNameToNode.GetStartPosition();
	while( pos )
	{
		m_mapNameToNode.GetNextAssoc( pos, cszKey, pNode );
		piNode = (CGINode*)pNode;
		VERIFY( piNewNode = piNode->CloneNode( TRUE ) );
		piNewNode->SetParent( piParentNode );
		piNM->SetNamedItem( piNewNode );
	}

    return piNM;
}

void CGINamedNodeMap::ClearMap()
{
    // Dereference all of our children if we took references
    if( FALSE == m_bAppendToParent ) 
	{
		void* pNode;
		CString cszKey;
		CGINode* piNode;
		POSITION pos = m_mapNameToNode.GetStartPosition();
		while( pos )
		{
			m_mapNameToNode.GetNextAssoc( pos, cszKey, pNode );
			piNode = (CGINode*)pNode;
			if( piNode )
				piNode->Release();
		}
    }

    m_mapNameToNode.RemoveAll();
}

CGINode* CGINamedNodeMap::GetNamedItem( LPCTSTR ptszName ) const
{
	void* pNode = NULL;
	m_mapNameToNode.Lookup( ptszName, pNode );
	return (CGINode*)pNode;
}

CGINode* CGINamedNodeMap::GetNamedItemNS( const CMapStringToPtr& rmapStrToNode, LPCTSTR ptszNsURI, LPCTSTR ptszLocalName )
{
	void* pNode;
	CString cszKey;
	CGINode* piNode;
	POSITION pos = rmapStrToNode.GetStartPosition();
	while( pos )
	{
		rmapStrToNode.GetNextAssoc( pos, cszKey, pNode );
		piNode = (CGINode*)pNode;
		if( piNode->GetPrefix() )
		{
			if( 0 == lstrcmp( piNode->GetNameSpaceURI(), ptszNsURI ) 
				&& 0 == lstrcmp( piNode->GetName(), ptszLocalName ) )
				return piNode;
		}
	}

	return NULL;
}

CGINode* CGINamedNodeMap::GetNamedItemNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName ) const {
	return CGINamedNodeMap::GetNamedItemNS( m_mapNameToNode, ptszNsURI, ptszLocalName ); }

CGINode* CGINamedNodeMap::SetNamedItem( CGINode* piNode )
{
    if( m_bReadonly || NULL == piNode )
        return NULL;

    if( m_bAppendToParent )
        return m_piParentNode->AppendChild( *piNode );

    // We take a reference
	piNode->AddRef();
    m_mapNameToNode.SetAt( piNode->GetNodeName(), piNode );

    return piNode;
}

CGINode* CGINamedNodeMap::SetNamedItemNS( CGINode* piNode )
{
    if( m_bReadonly || NULL == piNode )
        return 0;

    if( m_bAppendToParent )
        return m_piParentNode->AppendChild( *piNode );

    if( piNode->GetPrefix() ) 
	{
        // node has a namespace
        CGINode* piPrevNode = GetNamedItemNS( piNode->GetNameSpaceURI(), piNode->GetName() );

        // We take a reference
        piNode->AddRef();
		m_mapNameToNode.SetAt( piNode->GetNodeName(), piNode );
        return piPrevNode;
    } 

	// ### check the following code if it is ok
    return SetNamedItem( piNode );
}

CGINode* CGINamedNodeMap::RemoveNamedItem( LPCTSTR ptszName )
{
    if (m_bReadonly)
        return 0;

    CGINode* piNode = GetNamedItem( ptszName );
    if( NULL == piNode )
        return NULL;

    if( m_bAppendToParent )
        return m_piParentNode->RemoveChild( *piNode );

    m_mapNameToNode.RemoveKey( piNode->GetNodeName() );

    // We took a reference, so we have to free one here
    piNode->Release();
    return piNode;
}

CGINode* CGINamedNodeMap::GetItem( INT nIndex ) const
{
    if( (UINT)nIndex >= GetLength() )
        return NULL;

	INT i = 0;
	void* pNode;
	CString cszKey;
	POSITION pos = m_mapNameToNode.GetStartPosition();
	while( pos )
	{
		m_mapNameToNode.GetNextAssoc( pos, cszKey, pNode );
		if( i == nIndex )
			return (CGINode*)pNode;

		i++;
	}

    return NULL;
}

UINT CGINamedNodeMap::GetLength() const
{
    return m_mapNameToNode.GetCount();
}

BOOL CGINamedNodeMap::FindItem( LPCTSTR ptszName ) const {
    return NULL != GetNamedItem( ptszName ); }

BOOL CGINamedNodeMap::FindItemNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName ) const {
    return NULL != GetNamedItemNS( ptszNsURI, ptszLocalName ); }
