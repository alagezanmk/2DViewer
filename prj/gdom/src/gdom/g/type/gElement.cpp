#include "stdafx.h"
#include <g\type\gElement.h>
#include <g\attr\gAttr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CGAttr : public CGNode
{
public:
	CGAttr();
	CGAttr( CGAttr& rAttr );
	CGAttr( CGIAttr* piAttr );

	friend CGElement;
};

CGAttr::CGAttr()
{}

CGAttr::CGAttr( CGAttr& rAttr )
{}

CGAttr::CGAttr( CGIAttr* piAttr )
{}

#define m__piNode ((CGIElement*)m_piNode)

CGElement::CGElement()
{}

CGElement::CGElement( const CGElement& rElement )
 : CGNode( rElement )
{}

CGElement::CGElement( CGIElement* piElement )
 : CGNode( piElement )
{}

CGElement& CGElement::operator=( const CGElement& rElement ) 
{
//	return (CGElement&)CGNode::::operator=( rElement ); 
	///TODO
	ASSERT( FALSE );
	static CGElement s;
	return s;
}

CString CGElement::GetTagName() const
{
	if( NULL == m_piNode )
		return CString();

	return m__piNode->GetTagName();
}

void CGElement::GetTagName( CString& rcszTageName ) const
{
	if( NULL == m_piNode )
	{
		rcszTageName.Empty();
		return;
	}

	m__piNode->GetTagName( rcszTageName );
}

CString CGElement::GetAttribute( LPCTSTR pctszName ) const 
{
	if( NULL == m_piNode )
		return CString();

	return m__piNode->GetAttribute( pctszName );
}

BOOL CGElement::GetAttribute( CString& rcszValue, LPCTSTR pctszName ) const
{
	if( NULL == m_piNode )
	{
		rcszValue.Empty();
		return FALSE;
	}

	return m__piNode->GetAttribute( rcszValue, pctszName );
}

BOOL CGElement::SetAttribute( LPCTSTR pctszName, const CString& rcszValue )
{
	if( NULL == m_piNode )
		return FALSE;

	return m__piNode->SetAttribute( pctszName, rcszValue );
}

BOOL CGElement::SetAttribute( LPCTSTR pctszName, LPCTSTR pctszValue )
{
	if( NULL == m_piNode )
		return FALSE;

	return m__piNode->SetAttribute( pctszName, pctszValue );
}

void CGElement::RemoveAttribute( LPCTSTR pctszName )
{
	if( NULL == m_piNode )
		return;

	m__piNode->RemoveAttributeNode( pctszName );
}

CGAttr CGElement::GetAttributeNode( LPCTSTR pctszName )
{
	if( NULL == m_piNode )
		return CGAttr();

	return CGAttr( m__piNode->GetAttributeNode( pctszName ) );
}

CGAttr CGElement::SetAttributeNode( const CGAttr& rAttr )
{
	if( NULL == m_piNode || NULL == rAttr.m_piNode )
		return FALSE;

	return CGAttr( m__piNode->AddAttributeNode( *((CGIAttr*)rAttr.m_piNode) ) );
}

CGAttr CGElement::RemoveAttributeNode( const CGAttr& rOldAttr )
{
	if( NULL == m_piNode || NULL == rOldAttr.m_piNode )
		return FALSE;

	return CGAttr( m__piNode->RemoveAttributeNode( *((CGIAttr*)rOldAttr.m_piNode) ) );
}

CGNodeList CGElement::GetElementsByTagName( LPCTSTR pctszName ) const
{
	if( NULL == m_piNode )
		return CGNodeList();

	return CGNodeList( m__piNode->GetElementsByTagName( pctszName ) );
}

CString CGElement::GetttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszDefValue /*= NULL*/ ) const
{
	if( NULL == m_piNode )
		return CString();

	return m__piNode->GetAttributeNS( pctszNsURI, pctszLocalName, pctszDefValue );
}

BOOL CGElement::GetAttributeNS( CString& rcszValue, LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszDefValue /*= NULL*/ ) const
{
	if( NULL == m_piNode )
	{
		rcszValue.Empty();
		return FALSE;
	}

	return m__piNode->GetAttributeNS( rcszValue, pctszNsURI, pctszLocalName );
}

BOOL CGElement::SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, const CString& rcszValue )
{
	if( NULL == m_piNode )
		return FALSE;

	return m__piNode->SetAttributeNS( pctszNsURI, pctszLocalName, rcszValue );
}

BOOL CGElement::SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszValue )
{
	if( NULL == m_piNode )
		return FALSE;

	return m__piNode->SetAttributeNS( pctszNsURI, pctszLocalName, pctszValue );
}

void CGElement::RemoveAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName ) 
{
	if( NULL == m_piNode )
		return;

	m__piNode->RemoveAttributeNodeNS( pctszNsURI, pctszLocalName );
}

CGAttr CGElement::GetAttributeNodeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName )
{
	if( NULL == m_piNode )
		return CGAttr();

	return CGAttr( m__piNode->GetAttributeNodeNS( pctszNsURI, pctszLocalName ) );
}

CGAttr CGElement::SetAttributeNodeNS( const CGAttr& rAttr ) 
{
	if( NULL == m_piNode )
		return CGAttr();

	return CGAttr( m__piNode->AddAttributeNodeNS( *((CGIAttr*)rAttr.m_piNode) ) );
}

CGAttr CGElement::RemoveAttributeNodeNS( const CGAttr& rOldAttr )
{
	if( NULL == m_piNode )
		return CGAttr();

	return CGAttr( m__piNode->RemoveAttributeNodeNS( *((CGIAttr*)rOldAttr.m_piNode) ) );
}

CGNodeList CGElement::GetElementsByTagNameNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName ) const
{
	if( NULL == m_piNode )
		return CGNodeList();

	return CGNodeList( m__piNode->GetElementsByTagNameNS( pctszNsURI, pctszLocalName ) );
}

BOOL CGElement::HasAttribute( LPCTSTR pctszName ) const 
{
	if( NULL == m_piNode )
		return FALSE;

	return m__piNode->HasAttribute( pctszName );
}

BOOL CGElement::HasAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName ) const
{
	if( NULL == m_piNode )
		return FALSE;

	return m__piNode->HasAttributeNS( pctszNsURI, pctszLocalName );
}

//readonly attribute TypeInfo schemaTypeInfo;

void CGElement::SetIdAttribute( LPCTSTR pctszName, BOOL bIsID )
{
	if( NULL == m_piNode )
		return;

	m__piNode->SetIdAttribute( pctszName, bIsID );
}

void CGElement::SetIdAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, BOOL bIsID )
{
	if( NULL == m_piNode )
		return;

	m__piNode->SetIdAttributeNS( pctszNsURI, pctszLocalName, bIsID );
}

void CGElement::SetIdAttributeNode( CGIAttr& rAttr, BOOL bIsID )
{
	if( NULL == m_piNode )
		return;

	ASSERT( FALSE );
	///TODO
	//m__piNode->SetIdAttribute( rAttr, bIsID );
}

void CGElement::SetAttribute( LPCTSTR pctszName, LONGLONG llValue )
{
	if( NULL == m_piNode )
		return;

	ASSERT( FALSE );
	///TODO
}

void CGElement::SetAttribute( LPCTSTR pctszName, INT nValue )
{
	if( NULL == m_piNode )
		return;

	ASSERT( FALSE );
	///TODO
}

void CGElement::SetAttribute( LPCTSTR pctszName, UINT unValue )
{
	if( NULL == m_piNode )
		return;

	ASSERT( FALSE );
	///TODO
}

void CGElement::SetAttribute( LPCTSTR pctszName, FLOAT fValue )
{
	if( NULL == m_piNode )
		return;

	ASSERT( FALSE );
	///TODO
}

void CGElement::SetAttribute( LPCTSTR pctszName, double dfValue )
{
	if( NULL == m_piNode )
		return;

	ASSERT( FALSE );
	///TODO
}
