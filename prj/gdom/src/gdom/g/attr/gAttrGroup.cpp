#include "stdafx.h"
#include <g\attr\gAttrGroup.h>
#include <g\type\gElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/// The CGIAttrPriv is a private class derived CGAttr which used by 
/// CGIAttrGroup to initialize the protected members m_paSet and m_pElement
/// of CGIAttr through SetName and SetElement functions
class CGIAttrPriv : public CGIAttr
{
protected:
	/// Function to initiailize the member m_cszName
	void SetName( LPCTSTR pctszName ) {
		m_cszName = pctszName; 	}

	/// Function to initiailize the member m_cszPrefix
	void SetPrefix( LPCTSTR pctszPrefix ) {
		m_cszPrefix = pctszPrefix; 	}

	/// Function to initiailize the member m_cszPrefix
	void SetPrefix( const CString& rcszPrefix ) {
		m_cszPrefix = rcszPrefix; 	}

	/// Function to initiailize the member m_cszNameSpaceURI
	void SetNameSpaceURI( LPCTSTR pctszNameSpaceURI ) {
		m_cszNamespaceURI = pctszNameSpaceURI; 	}

	/// Function to initiailize the member m_cszNameSpaceURI
	void SetNameSpaceURI( const CString& rcszNameSpaceURI ) {
		m_cszNamespaceURI = rcszNameSpaceURI; 	}

	/// Function to initiailize the member m_pOwnerElement
	void SetOwnerElement( CGIElement* pElement ) {
		m_pOwnerElement = pElement; }

	friend CGIAttrGroup;
	friend CGINamedAttrMap;
};

IMPL_GTPYECLASS_DYNCREATE( CGIAttrGroup, CGINode, _T("AttrGroup") )
CGIAttrGroup::CGIAttrGroup()
{
	m_pgInstanceType = &GetClassType();
	m_pElement = NULL;
	m_bAttrInited = FALSE;
}

CGIAttrGroup::CGIAttrGroup( LPCTSTR pctszName )
{
	m_cszName = pctszName;
	m_pgInstanceType = &GetClassType();
	m_pElement = NULL;
	m_bAttrInited = FALSE;
}

CGIAttrGroup::~CGIAttrGroup() 
{}

INT CGIAttrGroup::GetNodeType() const {
	return CGNode::ATTRIBUTE_GROUP_NODE; }

/// This function sets m_cszName, which species name of the CGIAttrGroup object.
/// This is returned by the function GetName. m_cszName is a protected member.
inline void CGIAttrGroup::SetName( LPCTSTR pctszName, INT nLength /*= 0*/ ) 
{
	if( nLength > 1 )
	{
		lstrcpyn( m_cszName.GetBuffer( nLength + 1 ), pctszName, nLength + 1 );
		m_cszName.ReleaseBuffer( nLength );
	}
	else
		m_cszName = pctszName; 
}

/// This is function reimplemented from CGINode. This is overrided here to initialize 
/// the members m_paSet and m_pElement while attaching a CGINode object to the CGIAttrGroup.
void CGIAttrGroup::Attach( CGEventNode& rNode )
{
	INT nNodeType = rNode.GetNodeType();
	switch( nNodeType )
	{
	case CGNode::ATTRIBUTE_GROUP_NODE: {
		CGIAttrGroup* pGroup = (CGIAttrGroup*)&rNode;
		pGroup->m_pElement = m_pElement;
		break;	}
		
	case CGNode::ATTRIBUTE_NODE: {
		CGIAttrPriv* pAttrPriv = (CGIAttrPriv*)&rNode;
		pAttrPriv->SetOwnerElement( m_pElement );
		break;	}
	}
	
	CGINode::Attach( rNode );
}

/// This is function reimplemented from CGINode. This is overrided here to cleanup 
/// the members m_paSet and m_pElement while detaching a CGINode object from the CGIAttrGroup.
void CGIAttrGroup::Detach( CGEventNode& rNode )
{
	CGINode::Detach( rNode );
	
	INT nNodeType = rNode.GetNodeType();
	switch( nNodeType )
	{
	case CGNode::ATTRIBUTE_GROUP_NODE: {
		CGIAttrGroup* pGroup = (CGIAttrGroup*)&rNode;
		pGroup->m_pElement = NULL;
		break; }
		
	case CGNode::ATTRIBUTE_NODE: {
		CGIAttrPriv* pAttrPriv = (CGIAttrPriv*)&rNode;
		pAttrPriv->SetOwnerElement( NULL );
		break; }
	}
}

void CGIAttrGroup::InitializeAttributes()
{}

CString CGIAttrGroup::GetGroupName() const
{
	CString cszGroupName;
	GetGroupName( cszGroupName );
	return cszGroupName;
}

void CGIAttrGroup::GetGroupName( CString& rcsName ) const
{
	CString cszName;
	USHORT unNodeType;
	LPCTSTR pctszGroupName;
	CGIAttrGroup* piGroup = (CGIAttrGroup*)GetParent();
	while( piGroup && CGNode::ATTRIBUTE_GROUP_NODE == (unNodeType = piGroup->GetNodeType()) 
			&& FALSE == piGroup->IsRootGroup() )
	{
		unNodeType = piGroup->GetNodeType();
		if( CGNode::ATTRIBUTE_GROUP_NODE != unNodeType )
		{
			ASSERT( CGNode::ATTRIBUTE_GROUP_NODE == unNodeType );
			return;
		}
		
		pctszGroupName = piGroup->GetNodeName();
		if( rcsName.IsEmpty() )
			rcsName = pctszGroupName;
		else
		{
			cszName.Format( _T("%c%s"), CGINamedAttrMap::GROUP_CHAR, pctszGroupName );
			rcsName += cszName;
		}
		
		piGroup = (CGIAttrGroup*)piGroup->GetParent();
	}
}

CGIAttrGroup* CGIAttrGroup::GetAttributeGroup( LPCTSTR pctszName )
{
	if( lIsStrEmpty( pctszName ) )
		return NULL;

	INT nGroupNameLen = lstrlen( pctszName );
	TCHAR* ptszToken = (TCHAR*)_tcschr( pctszName, CGINamedAttrMap::GROUP_CHAR );
	if( ptszToken )
		nGroupNameLen = (ptszToken - pctszName) / sizeof(TCHAR);
	
	USHORT unNodeType;
	CString cszNodeName;
	CGIAttrGroup* piGroup = (CGIAttrGroup*)m_pFirst;
	while( piGroup )
	{
		unNodeType = piGroup->GetNodeType();
		if( CGNode::ATTRIBUTE_GROUP_NODE != unNodeType )
			continue;

		cszNodeName = piGroup->GetNodeName();
		if( 0 == lstrnicmp( cszNodeName, pctszName, nGroupNameLen ) )
		{
			if( NULL == ptszToken )
				return piGroup;

			return piGroup->GetAttributeGroup( ptszToken + 1 );
		}

		piGroup = (CGIAttrGroup*)piGroup->m_pNext;
	}

	return NULL;
}

CGIAttrGroup* CGIAttrGroup::CreateAttributeGroup( LPCTSTR pctszName )
{
	if( lIsStrEmpty( pctszName ) )
		return NULL;
	
	CString cszGroupNodeName;

	INT nGroupNameLen = lstrlen( pctszName );
	TCHAR* ptszToken = (TCHAR*)_tcschr( pctszName, CGINamedAttrMap::GROUP_CHAR );
	if( ptszToken )
		nGroupNameLen = (ptszToken - pctszName) / sizeof(TCHAR);

	USHORT unNodeType;
	CString cszNodeName;
	CGIAttrGroup* piGroup = (CGIAttrGroup*)m_pFirst;
	CGIAttrGroup* pNewGroup;
	while( piGroup )
	{
		unNodeType = piGroup->GetNodeType();
		if( CGNode::ATTRIBUTE_GROUP_NODE != unNodeType )
			continue;

		cszNodeName = piGroup->GetNodeName();
		if( 0 == lstrnicmp( cszNodeName, pctszName, nGroupNameLen ) )
		{
			if( NULL == ptszToken )
				return piGroup;

			pNewGroup = piGroup->CreateAttributeGroup( ptszToken + 1 );
			return pNewGroup;
		}

		piGroup = (CGIAttrGroup*)piGroup->m_pNext;
	}

	VERIFY( pNewGroup = new CGIAttrGroup );
	if( NULL == pNewGroup )
		return NULL;

	pNewGroup->SetNodeName( pctszName );
	VERIFY( AppendChild( *pNewGroup ) );

	if( ptszToken )
		return pNewGroup->CreateAttributeGroup( ptszToken + 1 );

	return pNewGroup;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const TCHAR CGINamedAttrMap::GROUP_CHAR = _T('#');
CGINamedAttrMap::CGINamedAttrMap()
	: CGINamedNodeMap( NULL )
{
	m_pElement = NULL;
	m_aRoot.SetName( _T("_ROOT") );
	m_aGeneral.SetName( _T("general") );
}

CGINamedAttrMap::~CGINamedAttrMap()
{
	RemoveAll();	
}

void CGINamedAttrMap::RemoveAll()
{
	RemoveAll( m_aRoot );
}

void CGINamedAttrMap::RemoveAll( CGIAttrGroup& rGroup )
{
	CGIAttr* piAttr;
	CGIAttrGroup* piGroup;
	CString cszGroupName, cszNodeName, cszLookupName;
	USHORT usnNodeType;

#ifdef _DEBUG
	cszGroupName = rGroup.GetNodeName();
	TRACE( _T("Remove Group %s \n"), cszGroupName );
#endif

	rGroup.LockObjectLink();

	CGINode* piNode = rGroup.GetLast();
	while( piNode )
	{
		usnNodeType = piNode->GetNodeType();
		if( CGNode::ATTRIBUTE_NODE == usnNodeType
			|| CGNode::ATTRIBUTE_GROUP_NODE == usnNodeType )
		{
			cszNodeName = piNode->GetNodeName();
			if( CGNode::ATTRIBUTE_NODE == usnNodeType )
			{
				piAttr = (CGIAttr*)piNode;
				if( piAttr->m_bGroupedNaming )
				{
					cszGroupName = piAttr->GetGroupName();
					cszLookupName.Format( _T("%s%c%s"), cszGroupName, CGINamedAttrMap::GROUP_CHAR, cszNodeName );
				}
				else
					cszLookupName = cszNodeName;

				VERIFY( m_mapNameToNode.RemoveKey( cszLookupName ) );
			}
			else
			{
				piGroup = (CGIAttrGroup*)piNode;
				cszGroupName = piGroup->GetGroupName();
				if( cszGroupName.IsEmpty() )
					cszLookupName = cszNodeName;
				else
					cszLookupName.Format( _T("%s%c%s"), cszGroupName, CGINamedAttrMap::GROUP_CHAR, cszNodeName );

				VERIFY( m_mapNameToGroup.RemoveKey( cszLookupName ) );
				RemoveAll( *piGroup );
			}

			piNode->Release();
		}

		piNode = piNode->GetPrev();
	}

	rGroup.LockObjectLink( FALSE );
	rGroup.RemoveAllChild();
}

BOOL CGINamedAttrMap::OnInitialUpdate()
{
	m_aRoot.m_pElement = m_pElement;
	AddAttributeGroup( m_aGeneral );

	return TRUE;
}

CGIAttr* CGINamedAttrMap::GetAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ )
{
	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( FALSE == lIsStrEmpty( pctszGroupName ) )
	{
		cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, pctszName );
		pctszLookupName = cszLookupName;	
	}
	else
		pctszLookupName = pctszName;

	void* pAttr = NULL;
	m_mapNameToNode.Lookup( pctszLookupName, pAttr );
	CDumpContext dc;
	dc.SetDepth( 1999 );
	m_mapNameToNode.Dump( dc );
	return (CGIAttr*)(CGINode*)pAttr;
}

CGIAttr* CGINamedAttrMap::AddAttributeNode( CGIAttr& rAttr ) {
	return AddAttributeNode( rAttr, rAttr.GetName() ); }

CGIAttr* CGINamedAttrMap::AddAttributeNode( CGIAttr& rAttr, LPCTSTR pctszName, 
										    LPCTSTR pctszGroupName /*= NULL*/, 
											BOOL bGroupedNaming /*= FALSE*/ )
{
	if( CGNode::ATTRIBUTE_NODE != rAttr.GetNodeType() )
		return NULL;	// Not attribute

	if( bGroupedNaming && lIsStrEmpty( pctszGroupName ) )
		return NULL; // Null Group name

	// Initialize name pointer from attribute node, if it was not given
	if( lIsStrEmpty( pctszName ) )
		pctszName = rAttr.GetNodeName();

	if( lIsStrEmpty( pctszName ) )
		return NULL;	// Null name 

	// If naming by group
	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( bGroupedNaming )
	{
		// Make Loopupname using Group name
		cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, pctszName );
		pctszLookupName = cszLookupName;
	}
	else 
		pctszLookupName = pctszName;

	// Find the attribute by its lookup name
	void* pAttr = NULL;
	if( m_mapNameToNode.Lookup( pctszLookupName, pAttr ) )
		return &rAttr;	

	// Initialize group name from default group node, if it was not given
	if( lIsStrEmpty( pctszGroupName ) )
		pctszGroupName = m_aGeneral.GetName();

	// Get group node pointer, an existing one or create new one
	CGIAttrGroup* piGroup = m_aRoot.CreateAttributeGroup( pctszGroupName );
	if( NULL == piGroup )
		return NULL;

	// Add the attribute to the group node
	if( &rAttr == piGroup->AppendChild( rAttr ) )
	{
		rAttr.m_bGroupedNaming = bGroupedNaming;
		((CGIAttrPriv*)&rAttr)->SetNodeName( pctszName );
		m_mapNameToNode.SetAt( pctszLookupName, (CGINode*)&rAttr );
		rAttr.AddRef();
	}

	return &rAttr;
}

CGIAttr* CGINamedAttrMap::RemoveAttributeNode( CGIAttr& rAttr )
{
	// Can't remove Non-Userdefined attribute
	INT nAttrType = rAttr.GetAttrType();
	if( 0 == (CGIAttr::USER_DEFINED_ATTR_TYPE & nAttrType) )
		return &rAttr;

	if( CGNode::ATTRIBUTE_NODE != rAttr.GetNodeType() )
		return NULL;	// Not attribute

	CGIAttrGroup* piGroup = (CGIAttrGroup*)rAttr.GetParent();
	if( NULL == piGroup )
		return NULL;	// Cannot remove root or attribute without parent

	CString cszGroupName = rAttr.GetGroupName();
	return RemoveAttributeNode( rAttr.GetNodeName(), cszGroupName );
}

CGIAttr* CGINamedAttrMap::RemoveAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ )
{
	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( lIsStrEmpty( pctszGroupName ) )
		pctszLookupName = pctszName;
	else
	{
		cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, pctszName );
		pctszLookupName = cszLookupName;	
	}

	void* pAttr = NULL;
	if( FALSE == m_mapNameToNode.Lookup( pctszLookupName, pAttr ) )
		return NULL;	// Not there

	CGIAttr* piAttr = (CGIAttr*)(CGINode*)pAttr;
	if( CGNode::ATTRIBUTE_NODE != piAttr->GetNodeType() )
		return NULL;

	// Can't remove Non-Userdefined attribute
	INT nAttrType = piAttr->GetAttrType();
	if( 0 == (CGIAttr::USER_DEFINED_ATTR_TYPE & nAttrType) )
		return piAttr;

	// If parent is not group, something is wrong
	CGIAttrGroup* piGroup = (CGIAttrGroup*)piAttr->GetParent();
	if( NULL == piGroup || CGNode::ATTRIBUTE_GROUP_NODE != piGroup->GetNodeType() )
	{
		ASSERT( piGroup && CGNode::ATTRIBUTE_GROUP_NODE == piGroup->GetNodeType() );
		return FALSE;
	}

	m_mapNameToNode.RemoveKey( pctszLookupName );

	piGroup->RemoveChild( *piAttr );
	piAttr->Release();

	return piAttr;
}

CGIAttrGroup* CGINamedAttrMap::GetAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ )
{
	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( FALSE == lIsStrEmpty( pctszGroupName ) )
	{
		cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, pctszName );
		pctszLookupName = cszLookupName;	
	}
	else
		pctszLookupName = pctszName;

	void* pAttrGroup = NULL;
	m_mapNameToGroup.Lookup( pctszLookupName, pAttrGroup );
	return (CGIAttrGroup*)(CGINode*)pAttrGroup;
}

const CGIAttrGroup* CGINamedAttrMap::GetAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ ) const {
	return (const CGIAttrGroup*)((CGINamedAttrMap*)this)->GetAttributeGroup( pctszName, pctszGroupName ); }

CGIAttrGroup* CGINamedAttrMap::AddAttributeGroup( CGIAttrGroup& rAttrGroup ) {
	return AddAttributeGroup( rAttrGroup, rAttrGroup.GetName() ); }

CGIAttrGroup* CGINamedAttrMap::AddAttributeGroup( CGIAttrGroup& rAttrGroup, LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ )
{
	if( CGNode::ATTRIBUTE_GROUP_NODE != rAttrGroup.GetNodeType() )
		return NULL; // Not Group type

	if( lIsStrEmpty( pctszName ) )
		pctszName = rAttrGroup.GetName();

	if( lIsStrEmpty( pctszName ) )
		return NULL;	// Null name 

	CGIAttrGroup* piGroup = NULL;
	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( lIsStrEmpty( pctszGroupName ) )
	{
		piGroup = &m_aRoot;
		pctszLookupName = pctszName;
	}
	else
	{
		cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, pctszName );
		pctszLookupName = cszLookupName;
	}

	// Find the attribute group by its lookup name
	void* pvGroup = NULL;
	if( m_mapNameToGroup.Lookup( pctszLookupName, pvGroup ) )
		return NULL;	

	if( NULL == piGroup )
	{
		piGroup = m_aRoot.CreateAttributeGroup( pctszGroupName );
		if( NULL == piGroup )
			return NULL;
	}

	piGroup->AppendChild( rAttrGroup );
	rAttrGroup.SetNodeName( pctszName );

	pctszGroupName = pctszName;	// Get full group name
	m_mapNameToGroup.SetAt( pctszLookupName, (CGINode*)&rAttrGroup );
	rAttrGroup.AddRef();

	rAttrGroup.InitializeAttributes();
	rAttrGroup.LockObjectLink();

	USHORT usnNodeType;
	void* pvNode;
	CGIAttr* pAttr;
	CGINode* pNode = rAttrGroup.GetFirst();
	while( pNode )
	{
		usnNodeType = pNode->GetNodeType();
		if( CGNode::ATTRIBUTE_NODE == usnNodeType || 
			CGNode::ATTRIBUTE_GROUP_NODE == usnNodeType )
		{
			pctszName = pNode->GetNodeName();
			cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, pctszName );

			if( CGNode::ATTRIBUTE_NODE == usnNodeType )
			{
				pAttr = (CGIAttr*)pNode;
				if( FALSE == m_mapNameToNode.Lookup( cszLookupName, pvNode ) )
					VERIFY( AddAttributeNode( *pAttr, pctszName, pctszGroupName, pAttr->m_bGroupedNaming ) );
			}
			else
			{
				if( FALSE == m_mapNameToGroup.Lookup( cszLookupName, pvNode ) )
					VERIFY( AddAttributeGroup( *((CGIAttrGroup*)pNode), pctszName, pctszGroupName ) );
			}
		}

		pNode = pNode->GetNext();
	}

	rAttrGroup.LockObjectLink( FALSE );
	return &rAttrGroup;
}

CGIAttrGroup* CGINamedAttrMap::RemoveAttributeGroup( CGIAttrGroup& rAttrGroup )
{
	if( CGNode::ATTRIBUTE_GROUP_NODE != rAttrGroup.GetNodeType() )
		return NULL; // Not Group type

	CGIAttrGroup* piGroup = (CGIAttrGroup*)rAttrGroup.GetParent();
	if( NULL == piGroup )
		return NULL;	// Cannot remove root or attribute without parent

	CString cszGroupName = piGroup->GetGroupName();
	return RemoveAttributeGroup( rAttrGroup.GetNodeName(), cszGroupName );
}

CGIAttrGroup* CGINamedAttrMap::RemoveAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ )
{
	if( lIsStrEmpty( pctszName ) )
		return NULL;

	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( lIsStrEmpty( pctszGroupName ) )
		pctszLookupName = pctszName;
	else
	{
		cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, pctszName );
		pctszLookupName = cszLookupName;	
	}

	void* pvGroup = NULL;
	if( FALSE == m_mapNameToGroup.Lookup( pctszLookupName, pvGroup ) )
		return NULL;	// Not there

	CGINode* piGroup = (CGINode*)pvGroup;
	if( CGNode::ATTRIBUTE_GROUP_NODE != piGroup->GetNodeType() )
		return NULL;

	// If parent is not group, something is wrong
	CGIAttrGroup* piParent = (CGIAttrGroup*)piGroup->GetParent();
	if( NULL == piParent || CGNode::ATTRIBUTE_GROUP_NODE != piParent->GetNodeType() )
	{
		ASSERT( piParent && CGNode::ATTRIBUTE_GROUP_NODE == piParent->GetNodeType() );
		return FALSE;
	}

	m_mapNameToGroup.RemoveKey( pctszLookupName );
	piParent->RemoveChild( *piGroup );
	piGroup->Release();

	return (CGIAttrGroup*)piGroup;
}

CGIAttr* CGINamedAttrMap::GetAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName /*= NULL*/ )
{
	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( FALSE == lIsStrEmpty( pctszGroupName ) )
	{
		cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, ptszLocalName );
		pctszLookupName = cszLookupName;	
	}
	else
		pctszLookupName = ptszLocalName;

	CGINode* piNode = CGINamedNodeMap::GetNamedItemNS( m_mapNameToNode, ptszNsURI, pctszLookupName );
	return (CGIAttr*)piNode;
}

const CGIAttr* CGINamedAttrMap::GetAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName /*= NULL*/ ) const {
	return (const CGIAttr*)((CGINamedAttrMap*)this)->GetAttributeNodeNS( ptszNsURI, ptszLocalName, pctszGroupName ); }

CGIAttr* CGINamedAttrMap::AddAttributeNodeNS( CGIAttr& rAttr, LPCTSTR pctszGroupName /*= NULL*/, BOOL bGroupedNaming /*= FALSE*/ )
{
	if( CGNode::ATTRIBUTE_NODE != rAttr.GetNodeType() )
		return NULL; // Not attribute type

	LPCTSTR ptszNsURI = rAttr.GetNameSpaceURI();
	LPCTSTR pctszQualifiedName = rAttr.GetQualifiedName();

	return AddAttributeNodeNS( rAttr, ptszNsURI, pctszQualifiedName, pctszGroupName, bGroupedNaming );
}

CGIAttr* CGINamedAttrMap::AddAttributeNodeNS( CGIAttr& rAttr, LPCTSTR ptszNsURI, LPCTSTR pctszQualifiedName, LPCTSTR pctszGroupName /*= NULL*/, BOOL bGroupedNaming /*= FALSE*/ )
{
	if( CGNode::ATTRIBUTE_NODE != rAttr.GetNodeType() )
		return NULL; // Not attribute type

	if( bGroupedNaming && lIsStrEmpty( pctszGroupName ) )
		return NULL; // Null Group name

	// Initialize name pointer from attribute node, if it was not given
	CString cszQualifiedName;
	if( lIsStrEmpty( pctszQualifiedName ) )
	{
		rAttr.GetQualifiedName( cszQualifiedName );
		pctszQualifiedName = cszQualifiedName;
	}

	if( lIsStrEmpty( pctszQualifiedName ) )
		return NULL;	// Null Qualified name 

	if( lIsStrEmpty( ptszNsURI ) )
		ptszNsURI = rAttr.GetNameSpaceURI();

	CString cszPrefix, cszName;
	CGINameSpaceString::SplitQualifiedName( cszPrefix, cszName, pctszQualifiedName, TRUE );

	CString cszNodeName;
	cszNodeName.Format( _T("%s:%s"), cszPrefix, cszName );

	if( cszNodeName.IsEmpty() )
		return NULL; // Null name

	// If naming by group
	LPCTSTR pctszName = cszNodeName;
	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( lIsStrEmpty( pctszGroupName ) )
		pctszLookupName = pctszName;
	else 
	{
		// Make Loopupname using Group name
		cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, pctszName );
		pctszLookupName = cszLookupName;	
	}

	// Find the attribute by its lookup name
	void* pAttr = NULL;
	if( m_mapNameToNode.Lookup( pctszLookupName, pAttr ) )
		return NULL;	

	// Initialize group name from default group node, if it was not given
	if( lIsStrEmpty( pctszGroupName ) )
		pctszGroupName = m_aGeneral.GetNodeName();

	// Get group node pointer, an existing one or create new one
	CGIAttrGroup* piGroup = m_aRoot.CreateAttributeGroup( pctszGroupName );
	if( NULL == piGroup )
		return NULL;

	// Add the attribute to the group node
	if( &rAttr == piGroup->AppendChild( rAttr ) )
	{
		rAttr.m_bGroupedNaming = bGroupedNaming;
		rAttr.SetNodeName( pctszName );
		((CGIAttrPriv*)&rAttr)->SetNameSpaceURI( ptszNsURI );

		m_mapNameToNode.SetAt( pctszLookupName, (CGINode*)&rAttr );
		rAttr.AddRef();
	}

	return &rAttr;
}

CGIAttr* CGINamedAttrMap::RemoveAttributeNodeNS( CGIAttr& rAttr )
{
	if( CGNode::ATTRIBUTE_NODE != rAttr.GetNodeType() )
		return NULL; // Not attribute type

	CGIAttrGroup* piGroup = (CGIAttrGroup*)rAttr.GetParent();
	if( NULL == piGroup )
		return FALSE;	// Cannot remove root or attribute without parent

	CString cszGroupName = rAttr.GetGroupName();
	LPCTSTR pctszNamespaceURI = rAttr.GetNameSpaceURI();
	if( FALSE == lIsStrEmpty( pctszNamespaceURI ) )
		return RemoveAttributeNodeNS( pctszNamespaceURI, rAttr.GetName(), cszGroupName );

	return NULL;
}

CGIAttr* CGINamedAttrMap::RemoveAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName /*= NULL*/ )
{
	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( lIsStrEmpty( pctszGroupName ) )
		pctszLookupName = ptszLocalName;
	else
	{
		cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, ptszLocalName );
		pctszLookupName = cszLookupName;	
	}

	CGINode* piNode = CGINamedNodeMap::GetNamedItemNS( m_mapNameToNode, ptszNsURI, pctszLookupName );
	if( NULL == piNode )
		return NULL;	// Not there

	if( CGNode::ATTRIBUTE_NODE != piNode->GetNodeType() )
		return NULL; // Not attribute type

	// If parent is not group, something is wrong
	CGIAttrGroup* piGroup = (CGIAttrGroup*)piNode->GetParent();
	ASSERT( piGroup && CGNode::ATTRIBUTE_GROUP_NODE == piGroup->GetNodeType() );
	if( NULL == piGroup )
		return NULL;

	m_mapNameToNode.RemoveKey( pctszLookupName );
	piGroup->RemoveChild( *piNode );
	piNode->Release();

	return (CGIAttr*)piNode;
}

CGIAttrGroup* CGINamedAttrMap::GetAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName /*= NULL*/ )
{
	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( lIsStrEmpty( pctszGroupName ) )
		pctszLookupName = ptszLocalName;
	else
	{
		cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, ptszLocalName );
		pctszLookupName = cszLookupName;	
	}

	CGINode* piNode = CGINamedNodeMap::GetNamedItemNS( m_mapNameToGroup, ptszNsURI, pctszLookupName );
	return (CGIAttrGroup*)piNode;
}

const CGIAttrGroup* CGINamedAttrMap::GetAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName /*= NULL*/ ) const {
	return (const CGIAttrGroup*)((CGINamedAttrMap*)this)->GetAttributeGroupNS( ptszNsURI, ptszLocalName, pctszGroupName ); }

CGIAttrGroup* CGINamedAttrMap::AddAttributeGroupNS( CGIAttrGroup& rAttrGroup, LPCTSTR pctszGroupName /*= NULL*/ )
{
	if( CGNode::ATTRIBUTE_GROUP_NODE != rAttrGroup.GetNodeType() )
		return NULL; // Not group type

	LPCTSTR ptszNsURI = rAttrGroup.GetNameSpaceURI();
	LPCTSTR pctszQualifiedName = rAttrGroup.GetQualifiedName();

	return AddAttributeGroupNS( rAttrGroup, ptszNsURI, pctszQualifiedName, pctszGroupName );
}

CGIAttrGroup* CGINamedAttrMap::AddAttributeGroupNS( CGIAttrGroup& rAttrGroup, LPCTSTR ptszNsURI, LPCTSTR pctszQualifiedName, LPCTSTR pctszGroupName /*= NULL*/ )
{
	ASSERT( FALSE ); // Need logic review
	if( CGNode::ATTRIBUTE_GROUP_NODE != rAttrGroup.GetNodeType() )
		return NULL; // Not Group type

	if( lIsStrEmpty( pctszGroupName ) )
		return NULL; // Null Group name

	// Initialize name pointer from attribute node, if it was not given
	CString cszQualifiedName;
	if( lIsStrEmpty( pctszQualifiedName ) )
	{
		rAttrGroup.GetQualifiedName( cszQualifiedName );
		pctszQualifiedName = cszQualifiedName;
	}
	
	if( lIsStrEmpty( pctszQualifiedName ) )
		return NULL;	// Null Qualified name 

	if( lIsStrEmpty( ptszNsURI ) )
		ptszNsURI = rAttrGroup.GetNameSpaceURI();

	CString cszPrefix, cszName;
	CGINameSpaceString::SplitQualifiedName( cszPrefix, cszName, pctszQualifiedName, TRUE );

	CString cszNodeName;
	cszNodeName.Format( _T("%s:%s"), cszPrefix, cszName );
	
	if( cszNodeName.IsEmpty() )
		return NULL; // Null name

	CGIAttrGroup* piGroup = NULL;
	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( lIsStrEmpty( pctszGroupName ) )
	{
		piGroup = &m_aRoot;
		pctszLookupName = pctszQualifiedName;
	}
	else
	{
		cszLookupName.Format( _T("%s:%s%c%s"), (LPCTSTR)cszPrefix, pctszGroupName, CGINamedAttrMap::GROUP_CHAR, (LPCTSTR)cszName );
		pctszLookupName = cszLookupName;	
	}

	// Find the attribute group by its lookup name
	void* pvAttr = NULL;
	if( m_mapNameToGroup.Lookup( pctszLookupName, pvAttr ) )
		return NULL;	

	if( NULL == piGroup )
	{
		piGroup = m_aRoot.CreateAttributeGroup( pctszGroupName );
		if( NULL == piGroup )
			return NULL;
	}

	piGroup->AppendChild( rAttrGroup );
	rAttrGroup.SetName( cszName );

	pctszGroupName = rAttrGroup.GetName();	// Get full group name
	m_mapNameToGroup.SetAt( pctszLookupName, (CGINode*)&rAttrGroup );
	rAttrGroup.AddRef();

	rAttrGroup.InitializeAttributes();
	rAttrGroup.LockObjectLink();

	LPCTSTR pctszName;
	USHORT usnNodeType;
	void* pvNode;
	CGIAttr* piAttr;
	CGINode* pNode = rAttrGroup.GetFirst();
	while( pNode )
	{
		usnNodeType = pNode->GetNodeType();
		if( CGNode::ATTRIBUTE_NODE == usnNodeType || 
			CGNode::ATTRIBUTE_GROUP_NODE == usnNodeType )
		{
			pctszName = pNode->GetNodeName();
			cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, pctszName );

			if( CGNode::ATTRIBUTE_NODE == usnNodeType )
			{
				piAttr = (CGIAttr*)pNode;
				if( FALSE == m_mapNameToNode.Lookup( cszLookupName, pvNode ) )
					VERIFY( AddAttributeNode( *piAttr, pctszName, pctszGroupName, piAttr->m_bGroupedNaming ) );
			}
			else
			{
				if( FALSE == m_mapNameToGroup.Lookup( cszLookupName, pvNode ) )
					VERIFY( AddAttributeGroup( *((CGIAttrGroup*)pNode), pctszName, pctszGroupName ) );
			}
		}

		pNode = pNode->GetNext();
	}

	rAttrGroup.LockObjectLink( FALSE );
	return &rAttrGroup;
}

CGIAttrGroup* CGINamedAttrMap::RemoveAttributeGroupNS( CGIAttrGroup& rAttrGroup )
{
	if( CGNode::ATTRIBUTE_GROUP_NODE != rAttrGroup.GetNodeType() )
		return NULL; // Not Group type

	CGIAttrGroup* piGroup = (CGIAttrGroup*)rAttrGroup.GetParent();
	if( NULL == piGroup )
		return NULL;	// Cannot remove root or attribute without parent

	CString cszGroupName = rAttrGroup.GetGroupName();
	LPCTSTR pctszNamespaceURI = rAttrGroup.GetNameSpaceURI();
	if( FALSE == lIsStrEmpty( pctszNamespaceURI ) )
		return RemoveAttributeGroupNS( pctszNamespaceURI, rAttrGroup.GetName(), cszGroupName );

	return NULL;
}

CGIAttrGroup* CGINamedAttrMap::RemoveAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName /*= NULL*/ )
{
	CString cszLookupName;
	LPCTSTR pctszLookupName;
	if( FALSE == lIsStrEmpty( pctszGroupName ) )
	{
		cszLookupName.Format( _T("%s%c%s"), pctszGroupName, CGINamedAttrMap::GROUP_CHAR, ptszLocalName );
		pctszLookupName = cszLookupName;	
	}
	else
		pctszLookupName = ptszLocalName;

	CGINode* piNode = CGINamedNodeMap::GetNamedItemNS( m_mapNameToGroup, ptszNsURI, pctszLookupName );
	if( NULL == piNode )
		return NULL;	// Not there

	if( CGNode::ATTRIBUTE_GROUP_NODE != piNode->GetNodeType() )
		return NULL;	// Not group type

	// If parent is not group, something is wrong
	CGIAttrGroup* piGroup = (CGIAttrGroup*)piNode->GetParent();
	ASSERT( piGroup && CGNode::ATTRIBUTE_GROUP_NODE == piGroup->GetNodeType() );
	if( NULL == piGroup )
		return NULL;

	m_mapNameToGroup.RemoveKey( pctszLookupName );
	piGroup->RemoveChild( *piNode );
	piNode->Release();

	return (CGIAttrGroup*)piNode;
}

BOOL CGINamedAttrMap::HasAttribute( LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ ) const
{
	const CGIAttr* piAttr = GetAttributeNode( pctszName, pctszGroupName );
	return NULL != piAttr;
}

BOOL CGINamedAttrMap::HasAttributeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName /*= NULL*/ ) const
{
	const CGIAttr* piAttr = GetAttributeNodeNS( ptszNsURI, ptszLocalName, pctszGroupName ); 
	return NULL != piAttr;
}

BOOL CGINamedAttrMap::HasAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ ) const
{
	const CGIAttrGroup* piAttrGroup = GetAttributeGroup( pctszName, pctszGroupName ); 
	return NULL != piAttrGroup;
}

BOOL CGINamedAttrMap::HasAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName /*= NULL*/ ) const
{
	const CGIAttrGroup* piAttrGroup = GetAttributeGroupNS( ptszNsURI, ptszLocalName, pctszGroupName ); 
	return NULL != piAttrGroup;
}
