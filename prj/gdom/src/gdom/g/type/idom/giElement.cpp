#include "stdafx.h"
#include <g\type\idom\giElement.h>
#include <g\type\idom\giTransformElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CGAttrSetPriv : public CGINamedAttrMap
{
public:
	void SetElement( CGIElement* pElement ) {
		m_pElement = pElement; }
};

CGSaveTransform::CGSaveTransform( Graphics& rGdip ) :
	m_rGdip( rGdip )
{
	Matrix mtx;
	rGdip.GetTransform( &mtx );
	mtx.GetElements( m_arfTransform );
};

CGSaveTransform::~CGSaveTransform()
{
	Matrix mtx;
	mtx.SetElements( m_arfTransform[0], m_arfTransform[1], m_arfTransform[2], m_arfTransform[3], m_arfTransform[4], m_arfTransform[5] );
	m_rGdip.SetTransform( &mtx );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CMapStringToPtr CGIElement::m_mapIDIndex;

IMPL_GTPYECLASS_DYNCREATE( CGIElement, CGINode, _T("element") )
LPCTSTR CGIElement::ELEMENT_TAGNAME = _T("element");
CGIElement::CGIElement() :
 m_aID( _T("id") )
{
	m_pgInstanceType = &GetClassType();
	m_pParent = NULL;
	m_pPrev = NULL;
	m_pNext = NULL;
	((CGAttrSetPriv*)&m_mapAttr)->SetElement( this );

	m_pRootElement = this;
	m_pViewPortElement = NULL;

	m_mapAttr.m_pElement = this;
}

CGIElement::~CGIElement()
{
	m_pRootElement = NULL;
	m_pViewPortElement = NULL;
}	

void CGIElement::OnFinalRelease()
{
	m_mapAttr.RemoveAll();
}	

INT CGIElement::GetNodeType() const {
	return CGNode::ELEMENT_NODE; }

BOOL CGIElement::OnInitialUpdate()
{
	CGINode::OnInitialUpdate();
	if( FALSE == m_mapAttr.OnInitialUpdate() )
	{
		ASSERT( FALSE );
		return FALSE;
	}

	AddEventListener( CGMutationEvent::DOMAttrModified, *this, FALSE );
	InitializeAttributes();
	return TRUE;
}

void CGIElement::InitializeAttributes() 
{
	AddAttributeNode( m_aID ); 
	CString cszTagName = GetTagName();

#ifdef _DEBUG
	INT nIndex = 0;
	void* pIndex = NULL;
	if( m_mapIDIndex.Lookup( cszTagName, pIndex ) )
		nIndex = (INT)pIndex;

	m_mapIDIndex.SetAt( cszTagName, (void*)++nIndex );

	CString cszID;
	cszID.Format( _T("%s_%d"), (LPCTSTR)cszTagName, nIndex );
	m_aID = cszID;
#else
	m_aID = cszTagName;
#endif //_DEBUG
}

BOOL CGIElement::GetAttribute( CString& rcszValue, LPCTSTR pctszName ) const
{
	rcszValue.Empty();
	const CGIAttr* pAttr = m_mapAttr.GetAttributeNode( pctszName );
	if( NULL == pAttr )
		return FALSE;

	pAttr->Get( rcszValue );
	return TRUE;
}

CString CGIElement::GetAttribute( LPCTSTR pctszName ) const
{
	CString csz;
	const CGIAttr* pAttr = m_mapAttr.GetAttributeNode( pctszName );
	if( NULL == pAttr )
		return csz;

	pAttr->Get( csz );
	return csz;
}

BOOL CGIElement::SetAttribute( LPCTSTR pctszName, LPCTSTR pctszValue )
{
	CGIAttr* pAttr = m_mapAttr.GetAttributeNode( pctszName );
	if( NULL == pAttr )
		return FALSE;

	return pAttr->Set( pctszValue );
}

BOOL CGIElement::SetAttribute( LPCTSTR pctszName, const CString& rcszValue )
{
	CGIAttr* pAttr = m_mapAttr.GetAttributeNode( pctszName );
	if( NULL == pAttr )
		return FALSE;

	return pAttr->Set( rcszValue );
}

CGIAttr* CGIElement::RemoveAttributeNode( LPCTSTR pctszName ) {
	return m_mapAttr.RemoveAttributeNode( pctszName ); }

CGIAttr* CGIElement::GetAttributeNode( LPCTSTR pctszName ) {
	return m_mapAttr.GetAttributeNode( pctszName ); }

const CGIAttr* CGIElement::GetAttributeNode( LPCTSTR pctszName ) const {
	return (const CGIAttr*)((CGIElement*)this)->GetAttributeNode( pctszName ); }

CGIAttr* CGIElement::SetAttributeNode( CGIAttr& rAttr ) {
	return AddAttributeNode( rAttr ); }

CGIAttr* CGIElement::RemoveAttributeNode( CGIAttr& rOldAttr ) {
	return m_mapAttr.RemoveAttributeNode( rOldAttr ); }

CGINodeList* CGIElement::GetElementsByTagName( LPCTSTR pctszName ) 
{
	///TODO
	ASSERT( FALSE );
	return NULL; 
}

BOOL CGIElement::GetAttributeNS( CString& rcszValue, LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszDefValue /*= NULL*/ ) const
{
	const CGIAttr* pAttr = m_mapAttr.GetAttributeNodeNS( pctszNsURI, pctszLocalName );
	if( NULL == pAttr )
		return FALSE;

	pAttr->Get( rcszValue );
	return TRUE;
}

CString CGIElement::GetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszDefValue /*= NULL*/ ) const
{
	CString csz;
	const CGIAttr* pAttr = m_mapAttr.GetAttributeNodeNS( pctszNsURI, pctszLocalName );
	if( NULL == pAttr )
		return csz;

	pAttr->Get( csz );
	return csz;
}

BOOL CGIElement::SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszValue )
{
	CGIAttr* pAttr = m_mapAttr.GetAttributeNodeNS( pctszNsURI, pctszLocalName );
	if( NULL == pAttr )
		return FALSE;

	return pAttr->Set( pctszValue );
}

BOOL CGIElement::SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, const CString& rcszValue )
{
	CGIAttr* pAttr = m_mapAttr.GetAttributeNodeNS( pctszNsURI, pctszLocalName );
	if( NULL == pAttr )
		return FALSE;

	return pAttr->Set( rcszValue );
}

CGIAttr* CGIElement::RemoveAttributeNodeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName ) {
	return m_mapAttr.RemoveAttributeNodeNS( pctszNsURI, pctszLocalName ); }

CGIAttr* CGIElement::GetAttributeNodeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName ) {
	return m_mapAttr.GetAttributeNodeNS( pctszNsURI, pctszLocalName ); }

CGIAttr* CGIElement::SetAttributeNodeNS( CGIAttr& rAttr ) {
	return m_mapAttr.AddAttributeNodeNS( rAttr ); }

CGINodeList* CGIElement::GetElementsByTagNameNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName ) 
{
	//TODO
	ASSERT( FALSE );
	return NULL;
}

BOOL CGIElement::HasAttribute( LPCTSTR pctszName ) const {
	return m_mapAttr.HasAttribute( pctszName ); }

BOOL CGIElement::HasAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName ) const {
	return m_mapAttr.HasAttributeNS( pctszNsURI, pctszLocalName ); }

//readonly attribute TypeInfo schemaTypeInfo;

BOOL CGIElement::SetIdAttribute( LPCTSTR pctszName, BOOL bIsID ) 
{
	CGIAttr* pAttr = GetAttributeNode( pctszName );
	if( pAttr )
	{
		pAttr->SetAttrFlag( CGIAttr::IS_ID_ATTR_FLAG, bIsID );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIElement::SetIdAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, BOOL bIsID ) 
{
	CGIAttr* pAttr = GetAttributeNodeNS( pctszNsURI, pctszLocalName );
	if( pAttr )
	{
		pAttr->SetAttrFlag( CGIAttr::IS_ID_ATTR_FLAG, bIsID );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIElement::SetIdAttributeNode( CGIAttr& rAttr, BOOL bIsID )
{
	if( FALSE == m_mapAttr.IsAttributeNode( rAttr ) )
		return FALSE;
	
	rAttr.SetAttrFlag( CGIAttr::IS_ID_ATTR_FLAG, bIsID );
	return TRUE;
}

CGIAttr* CGIElement::GetAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName ) {
	return m_mapAttr.GetAttributeNode( pctszName, pctszGroupName ); }

const CGIAttr* CGIElement::GetAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName ) const{
	return (const CGIAttr*)((CGIElement*)this)->GetAttributeNode( pctszName, pctszGroupName ); }
	
CGIAttr* CGIElement::operator[]( LPCTSTR pctszName ) {
	return GetAttributeNode( pctszName ); }

const CGIAttr* CGIElement::operator[]( LPCTSTR pctszName ) const {
	return GetAttributeNode( pctszName ); }

CGIAttr* CGIElement::AddAttributeNode( CGIAttr& rAttr ) {
	return m_mapAttr.AddAttributeNode( rAttr ); }
	
CGIAttr* CGIElement::AddAttributeNode( CGIAttr& rAttr, LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/, BOOL bGroupedNaming /*= FALSE*/ ) {
	return m_mapAttr.AddAttributeNode( rAttr, pctszName, pctszGroupName, bGroupedNaming ); }
	
CGIAttr* CGIElement::RemoveAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName ) {
	return m_mapAttr.RemoveAttributeNode( pctszName, pctszGroupName ); }
	
CGIAttrGroup* CGIElement::GetAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ ) {
	return m_mapAttr.GetAttributeGroup( pctszName, pctszGroupName ); }
	
const CGIAttrGroup* CGIElement::GetAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ ) const {
	return m_mapAttr.GetAttributeGroup( pctszName, pctszGroupName ); }
	
CGIAttrGroup* CGIElement::AddAttributeGroup( CGIAttrGroup& rAttrGroup ) {
	return m_mapAttr.AddAttributeGroup( rAttrGroup ); }
	
CGIAttrGroup* CGIElement::AddAttributeGroup( CGIAttrGroup& rAttrGroup, LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ ) {
	return m_mapAttr.AddAttributeGroup( rAttrGroup, pctszName, pctszGroupName ); }
	
CGIAttrGroup* CGIElement::RemoveAttributeGroup( CGIAttrGroup& rAttrGroup ) {
	return m_mapAttr.RemoveAttributeGroup( rAttrGroup ); }
	
CGIAttrGroup* CGIElement::RemoveAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ ) {
	return m_mapAttr.RemoveAttributeGroup( pctszName, pctszGroupName ); }
	
CGIAttr* CGIElement::GetAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName ) {
	return m_mapAttr.GetAttributeNodeNS( ptszNsURI, ptszLocalName, pctszGroupName ); }
	
const CGIAttr* CGIElement::GetAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName ) const {
	return m_mapAttr.GetAttributeNodeNS( ptszNsURI, ptszLocalName, pctszGroupName ); }
	
CGIAttr* CGIElement::AddAttributeNodeNS( CGIAttr& rAttr ) {
	return m_mapAttr.AddAttributeNode( rAttr ); }
	
CGIAttr* CGIElement::AddAttributeNodeNS( CGIAttr& rAttr, LPCTSTR ptszNsURI, LPCTSTR pctszQualifiedName, LPCTSTR pctszGroupName /*= NULL*/, BOOL bGroupedNaming /*= FALSE*/ ) {
	return m_mapAttr.AddAttributeNodeNS( rAttr, ptszNsURI, pctszQualifiedName, pctszGroupName, bGroupedNaming ); }
	
CGIAttr* CGIElement::RemoveAttributeNodeNS( CGIAttr& rAttr ) {
	return m_mapAttr.RemoveAttributeNodeNS( rAttr ); }
	
CGIAttr* CGIElement::RemoveAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName ) {
	return m_mapAttr.RemoveAttributeNodeNS( ptszNsURI, ptszLocalName, pctszGroupName ); }
	
CGIAttrGroup* CGIElement::GetAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName /*= NULL*/ ) {
	return m_mapAttr.GetAttributeGroupNS( ptszNsURI, ptszLocalName, pctszGroupName ); }
	
const CGIAttrGroup* CGIElement::GetAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName /*= NULL*/ ) const {
	return m_mapAttr.GetAttributeGroupNS( ptszNsURI, ptszLocalName, pctszGroupName ); }
	
CGIAttrGroup* CGIElement::AddAttributeGroupNS( CGIAttrGroup& rAttrGroup, LPCTSTR pctszGroupName /*= NULL*/ ) {
	return m_mapAttr.AddAttributeGroupNS( rAttrGroup, pctszGroupName ); }
	
CGIAttrGroup* CGIElement::AddAttributeGroupNS( CGIAttrGroup& rAttrGroup, LPCTSTR ptszNsURI, LPCTSTR pctszQualifiedName, LPCTSTR pctszGroupName /*= NULL*/ ) {
	return m_mapAttr.AddAttributeGroupNS( rAttrGroup, ptszNsURI, pctszQualifiedName, pctszGroupName ); }
	
CGIAttrGroup* CGIElement::RemoveAttributeGroupNS( CGIAttrGroup& rAttrGroup ) {
	return m_mapAttr.RemoveAttributeGroupNS( rAttrGroup ); }
	
CGIAttrGroup* CGIElement::RemoveAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName /*= NULL*/ ) {
	return m_mapAttr.RemoveAttributeGroupNS( ptszNsURI, ptszLocalName, pctszGroupName ); }

BOOL CGIElement::GetDefaultAttributeValue( LPCTSTR pctszName, INT nAttrType, void* pValue ) const {
	return FALSE; }

BOOL CGIElement::ValidateAttribute( const CGIAttr& rAttr, void* pValue ) const {
	return TRUE; }

BOOL CGIElement::UpdateAttribute( const CGIAttr& rAttr, void* pValue ) {
	return TRUE; }

void CGIElement::AttributeChanged( const CGIAttr& rAttr ) {
	SetModified(); }

BOOL CGIElement::IsDisplayAttribute( const CGIAttr& rAttr )  const {
	return FALSE; }

void CGIElement::HandleEvent( CGEvent& rEvent )
{
	if( CGMutationEvent::DOMAttrModified == rEvent.GetType() 
		&& CGEvent::AT_TARGET == rEvent.GetEventPhase() )
	{
		CGMutationEvent* pMutationEvent = (CGMutationEvent*)&rEvent;
		AttributeChanged( *((CGIAttr*)pMutationEvent->GetRelatedNode()) );
	}
}
	
void CGIElement::Draw( Graphics& rGdip )
{
	DrawElement( rGdip );
	DrawChild( rGdip );
	DrawOverlay( rGdip );
}

void CGIElement::DrawElement( Graphics& rGdip )
{}

void CGIElement::DrawChild( Graphics& rGdip )
{
	CGIElement* pElement = (CGIElement*)m_pFirst;
	while( pElement )
	{
		pElement->Draw( rGdip );
		pElement = (CGIElement*)pElement->m_pNext;
	}
}

void CGIElement::DrawOverlay( Graphics& rGdip )
{}

void CGIElement::Attach( CGEventNode& rNode )
{
	if( rNode.IsDerivedFrom( CGIElement::GetClassType() ) )
	{
		CGIElement* pElement = (CGIElement*)&rNode;
		pElement->m_pRootElement = m_pRootElement;
		pElement->m_pViewPortElement = m_pViewPortElement;
	}

	CGINode::Attach( rNode );
}

void CGIElement::Detach( CGEventNode& rNode )
{
	CGINode::Detach( rNode );

	if( rNode.IsDerivedFrom( CGIElement::GetClassType() ) )
	{
		CGIElement* pElement = (CGIElement*)&rNode;
		pElement->m_pRootElement = NULL;
		pElement->m_pViewPortElement = NULL;
	}
}

LPCTSTR CGIElement::GetId() const
{
	const CGIAttr* pAttr = m_mapAttr.GetAttributeNode( _T("id") );
	if( NULL == pAttr )
		return NULL;

	if( pAttr->GetInstanceType() != CGSAString::GetClassType() )
		return NULL;

	CGSAString* pStrAttr = (CGSAString*)pAttr;
	return pStrAttr->Get();
}

BOOL CGIElement::SetId( LPCTSTR pctszId )
{
	const CGIAttr* pAttr = m_mapAttr.GetAttributeNode( _T("id") );
	if( NULL == pAttr )
		return FALSE;

	if( pAttr->GetInstanceType() != CGSAString::GetClassType() )
		return FALSE;

	CGSAString* pStrAttr = (CGSAString*)pAttr;
	return pStrAttr->Set( pctszId );
}

LPCTSTR CGIElement::GetXmlbase()  const 
{
	ASSERT( FALSE );
	return NULL;
}

BOOL CGIElement::SetXmlbase( LPCTSTR pctszBase )
{
	ASSERT( FALSE );
	return FALSE;
}

BOOL CGIElement::GetRect( GRectF& rBBox ) const {
	return TRUE; }

BOOL CGIElement::GetDrawBBox( GRectF& rBBox, Matrix* pmtx /*= NULL*/ ) const {
	return TRUE; }

BOOL CGIElement::GetCTM( Matrix& rMtx ) const {
	return FALSE; }

BOOL CGIElement::GetCTM( Matrix& rMtx, INT nTYpe ) const {
	return FALSE; }

BOOL CGIElement::GetScreenCTM( Matrix& rMtx ) const {
	return GetCTMToElement( rMtx, *m_pRootElement ); }

BOOL CGIElement::GetCTMToElement( Matrix& rMtx, const CGIElement& rRef ) const 
{
	CGIElement* piElement = (CGIElement*)this;
	CGIElement* piPrev;
	
	do
	{
		if( piElement->IsDerivedFrom( CGIElement::GetClassType() ) )
			piElement->GetCTM( rMtx );

		if( &rRef == piElement )
			break;

		if( 0 )
		{
			piPrev = (CGIElement*)piElement->GetPrev();
			while( piPrev )
			{
				if( piPrev->IsDerivedFrom( CGITransformElement::GetClassType() ) )
					piPrev->GetCTM( rMtx );
				
				piPrev = (CGIElement*)piPrev->GetPrev();
			}
		}

		piElement = (CGIElement*)piElement->GetParent();
	}while( piElement );

	return FALSE == rMtx.IsIdentity();
}

void CGIElement::Update()
{}

void CGIElement::AddAttributes( CGIAttrLink* pAttrProxy, ... )
{
	va_list argList;
	va_start( argList, pAttrProxy );

	while( pAttrProxy )
	{
		AddAttributeNode( *pAttrProxy );
		pAttrProxy = va_arg(argList, CGIAttrLink*);
	}

	va_end( argList );
}

void CGIElement::AddGroupedAttributesV( LPCTSTR pctszName, LPCTSTR pctszGroupName, BOOL bGroupedNaming, 
									   va_list argList )
{
	CGIAttrLink* pAttrProxy = va_arg(argList, CGIAttrLink*);
	while( pAttrProxy )
	{
		AddAttributeNode( *pAttrProxy, pctszName, pctszGroupName, bGroupedNaming );
		pAttrProxy = va_arg(argList, CGIAttrLink*);
	}
}

void CGIElement::AddGroupedAttributes( LPCTSTR pctszName, LPCTSTR pctszGroupName, BOOL bGroupedNaming, 
									   CGIAttrLink* pAttrProxy, ... )
{
	va_list argList;
	va_start( argList, bGroupedNaming );
	AddGroupedAttributesV( pctszName, pctszGroupName, bGroupedNaming, argList );
	va_end( argList );
}

void CGIElement::AddGroupedAttributes( LPCTSTR pctszName, CGIAttrGroup& rAttrGroup, BOOL bGroupedNaming, 
									   CGIAttrLink* pAttrProxy, ... )
{
	LPCTSTR pctszGroupName = rAttrGroup.GetNodeName();
	if( lIsStrEmpty( pctszGroupName ) )
	{
		ASSERT( FALSE== lIsStrEmpty( pctszGroupName ) );
		return;
	}

	va_list argList;
	va_start( argList, bGroupedNaming );
	AddGroupedAttributesV( pctszName, pctszGroupName, bGroupedNaming, argList );
	va_end( argList );
}

void CGIElement::RemoveAttributes( CGIAttrLink* pAttrProxy, ... )
{
	va_list argList;
	va_start( argList, pAttrProxy );

	while( pAttrProxy )
	{
		pAttrProxy->RemoveAttribute();
		pAttrProxy = va_arg(argList, CGIAttrLink*);
	}

	va_end( argList );
}

void CGIElement::SetAttrType( INT nType, ... )
{
	va_list argList;
	va_start( argList, nType );

	CGIAttr* piAttr;
	do
	{
		piAttr = va_arg(argList, CGIAttr*);
		if( piAttr )
			piAttr->SetAttrType( nType );

	}while( piAttr );

	va_end( argList );
}

void CGIElement::SetAttrFlag( INT nFlag, BOOL bSet, ... )
{
	va_list argList;
	va_start( argList, bSet );

	CGIAttr* piAttr;
	do
	{
		piAttr = va_arg(argList, CGIAttr*);
		if( piAttr )
			piAttr->SetAttrFlag( nFlag, bSet );

	}while( piAttr );

	va_end( argList );
}

UINT CGIElement::HitTest( const CPoint& rpoint, Matrix* pmtx /*= NULL*/ )
{
	PointF ptf( (FLOAT)rpoint.x, (FLOAT)rpoint.y );

	Matrix mtx;
	GetScreenCTM( mtx );
	if( pmtx )
		mtx.Multiply( pmtx, MatrixOrderAppend );

	mtx.Invert();	// Screen To Element
	mtx.TransformPoints( &ptf );

	return HitTest( ptf );
}

UINT CGIElement::HitTest( const PointF& rptf ) {
	return HT_NOTHING; }

UINT CGIElement::HitTest( const CRect& rrct, Matrix* pmtx /*= NULL*/ )
{
	Rect rct( rrct.left, rrct.top, rrct.Width(), rrct.Height() );
	Region grgn( rct );
	
	Matrix mtx;
	GetScreenCTM( mtx );
	if( pmtx )
		mtx.Multiply( pmtx, MatrixOrderAppend );

	mtx.Invert();	// Screen To Element
	grgn.Transform( &mtx );

	return HitTest( grgn );
}

UINT CGIElement::HitTest( const Region& rrgn ) {
	return HT_NOTHING; }