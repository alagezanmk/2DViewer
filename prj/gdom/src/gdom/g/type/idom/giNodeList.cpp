#include "stdafx.h"
#include <g\type\idom\giNodeList.h>
#include <g\type\idom\giNode.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

long CGINodeList::m_lNodeListTime = -1;

CGINodeList::CGINodeList( CGINode* piNode )
{
	AddRef();
    m_piNode = piNode;
    if( m_piNode )
        m_piNode->AddRef();

    m_lTimeStamp = -1;
}

CGINodeList::CGINodeList( CGINode* piNode, LPCTSTR ptszTagName )
{
    AddRef();
    m_piNode = piNode;
    if( m_piNode )
        m_piNode->AddRef();

    m_cszTagname = ptszTagName;
    m_lTimeStamp = -1;
}

CGINodeList::CGINodeList( CGINode *piNode, LPCTSTR ptszNsURI, LPCTSTR ptszLocalName )
{
    AddRef();
    m_piNode = piNode;
    if (m_piNode)
        m_piNode->AddRef();

    m_cszTagname = ptszLocalName;
    m_cszNSURI = ptszNsURI;
    m_lTimeStamp = -1;
}

CGINodeList::~CGINodeList()
{
    if( m_piNode )
        m_piNode->Release();
}

BOOL CGINodeList::operator==( const CGINodeList& riNodeList ) const {
    return(m_piNode == riNodeList.m_piNode) && (m_cszTagname == riNodeList.m_cszTagname); }

BOOL CGINodeList::operator!=( const CGINodeList& riNodeList ) const {
    return (m_piNode != riNodeList.m_piNode) || (m_cszTagname != riNodeList.m_cszTagname); }

void CGINodeList::CreateList()
{
    if( NULL == m_piNode )
        return;
	
    m_lTimeStamp = CGINodeList::m_lNodeListTime;
    CGINode* p = m_piNode->GetFirst();
	
	m_arrList.RemoveAll();
    if( m_cszTagname.IsEmpty() ) 
	{
        while( p ) 
		{
            m_arrList.Add( p );
            p = p->GetNext();
        }
    } 
	else if( m_cszNSURI.IsEmpty() ) 
	{
        while( p && p != m_piNode ) 
		{
            if( p->IsKindOf( CGNode::ELEMENT_NODE ) && p->GetNodeName() == m_cszTagname )
                m_arrList.Add( p );

            if( p->GetFirst() )
                p = p->GetFirst();
            else if( p->GetNext() )
                p = p->GetNext();
            else 
			{
                p = p->GetParent();
                while( p && p != m_piNode && !p->GetNext() )
                    p = p->GetParent();

                if( p && p != m_piNode )
                    p = p->GetNext();
            }
        }
    } 
	else 
	{
        while( p && p != m_piNode )
		{
            if( p->IsKindOf( CGNode::ELEMENT_NODE ) && p->GetName() == m_cszTagname && 
				p->GetNameSpaceURI() == m_cszNSURI )
                m_arrList.Add( p );

            if( p->GetFirst() )
                p = p->GetFirst();
            else if( p->GetNext() )
                p = p->GetNext();
            else 
			{
                p = p->GetParent();
                while( p && p != m_piNode && NULL == p->GetNext() )
                    p = p->GetParent();
                if( p && p != m_piNode )
                    p = p->GetNext();
            }
        }
    }
}

CGINode* CGINodeList::GetItem( INT nIndex )
{
    if( NULL == m_piNode )
        return NULL;

    if( m_lTimeStamp != CGINodeList::m_lNodeListTime )
        CreateList();

    if( nIndex >= m_arrList.GetSize() )
        return NULL;

    return m_arrList.GetAt( nIndex );
}

CGINode** CGINodeList::GetList() 
{
    if( NULL == m_piNode )
        return NULL;
	
    if( m_lTimeStamp != CGINodeList::m_lNodeListTime )
        CreateList();
	
	return m_arrList.GetData(); 
}

UINT CGINodeList::GetLength() const
{
    if( NULL == m_piNode )
        return 0;

    if( m_lTimeStamp != CGINodeList::m_lNodeListTime ) 
	{
        CGINodeList* pThis = (CGINodeList*)this;
        pThis->CreateList();
    }

    return m_arrList.GetSize();
}

#ifdef _DEBUG
void CGINodeList::Dump( CDumpContext& dc ) const
{
	dc << "[CGINodeList]: Begin\n";
	CGObject::Dump( dc );

    if( NULL == m_piNode )
	{
		dc << "Null Node\n";
		dc << "[CGINodeList]: End\n";
        return;
	}

	INT nCount = m_arrList.GetSize();
	dc << "Total Node " << nCount << "\n";
	CGINode* const* ppiNode = m_arrList.GetData();
	for( INT i = 0; i < nCount; i++ )
		dc << "Node[" << i << "] at " << ppiNode[i] << ", Name: " << ppiNode[i]->GetName() << "\n";

	dc << "[CGINodeList]: End\n";
}
#endif //_DEBUG
