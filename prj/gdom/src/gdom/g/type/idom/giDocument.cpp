#include "stdafx.h"
#include <g\type\idom\giDocument.h>
#include <g\type\idom\giElement.h>
#include <g\type\idom\giRectElement.h>
#include <g\type\idom\giLineElement.h>
#include <g\type\idom\giView.h>
#include <g\type\gElementPriv.h>
#include <bld\page.h>
#include <bld\layer.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
IMPL_GTPYECLASS_DYNCREATE( CGIDocument, CGINode, _T("#document") )
CGIDocument::CGIDocument()
{
	VERIFY( m_pImplementation = new CGIImplementation );
	m_pImplementation->AddRef();

	VERIFY( m_pDocumentType = new CGIDocumentType( this, this ) );
	m_pDocumentType->AddRef();

	Construct();
}

CGIDocument::CGIDocument( LPCTSTR pctszName )
{
	VERIFY( m_pImplementation = new CGIImplementation );
	m_pImplementation->AddRef();

	VERIFY( m_pDocumentType = new CGIDocumentType( this, this ) );
	m_pDocumentType->AddRef();
	m_pDocumentType->m_cszName = pctszName;

	Construct();
}

CGIDocument::CGIDocument( CGIDocumentType* piDocumentType )
{
	VERIFY( m_pImplementation = new CGIImplementation );
	m_pImplementation->AddRef();

	if( piDocumentType )
	{
		m_pDocumentType = piDocumentType;
		m_pDocumentType->AddRef();
	}
	else
		VERIFY( m_pDocumentType = new CGIDocumentType( this, this ) );

	Construct();
}

CGIDocument::CGIDocument( CGIDocument* piDocument, BOOL bDeep )
 : CGINode( piDocument, bDeep )
{
    m_pImplementation = piDocument->m_pImplementation->Clone();
    m_pImplementation->AddRef();

    m_pDocumentType = (CGIDocumentType*)piDocument->m_pDocumentType->CloneNode( TRUE );
    m_pDocumentType->SetParent( this );
	m_pDocumentType->AddRef();

	Construct();
}

void CGIDocument::Construct() 
{
	m_cszName = _T("#document"); 
	m_pOwnerDocument = this; 
}

CGIDocument::~CGIDocument()
{
	if( m_pDocumentType )
		m_pDocumentType->Release();

	if( m_pImplementation )
		m_pImplementation->Release();
}

BOOL CGIDocument::OnInitialUpdae() {
	return TRUE; }

CGIElement* CGIDocument::GetElementById( LPCTSTR pctszElementId ) 
{
	CGINode* pFind = GetFirst();
	while( pFind )
	{
		if( pFind->IsDerivedFrom( CGIElement::GetClassType() ) )
		{
			CGIElement* pElement = (CGIElement*)pFind;
			pElement->AddRef();
			if( 0 == lstrcmpi( pElement->GetID(), pctszElementId ) )
				return pElement;

			pElement->Release();
		}

		pFind = pFind->GetNext();
	}

	return NULL; 
}

CGIElement* CGIDocument::CreateElement( LPCTSTR pctszTagName ) const 
{
	CGIElement* pElement = NULL;
	if( CGILayer::ELEMENT_TAGNAME == pctszTagName )
		pElement = new CGILayer;
	else if( CGIPage::ELEMENT_TAGNAME == pctszTagName )
		pElement = new CGIPage;
	else if( CGILineElement::ELEMENT_TAGNAME == pctszTagName )
		pElement = new CGILineElement;
	else if( CGIRectElement::ELEMENT_TAGNAME == pctszTagName )
		pElement = new CGIRectElement;
	else if( CGIView::ELEMENT_TAGNAME == pctszTagName )
		pElement = new CGIView;
	else if( CGIViewPort::ELEMENT_TAGNAME == pctszTagName )
		pElement = new CGIViewPort;

	ASSERT( pElement );
	if( pElement )
		pElement->OnInitialUpdate();

	return pElement; 
}
