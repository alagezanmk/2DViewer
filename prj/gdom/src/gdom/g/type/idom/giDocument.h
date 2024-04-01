#ifndef ___GI_DOCUMENT__PH___
#define ___GI_DOCUMENT__PH___

#include "giNode.h"

class CGIElement;
class CGIAttr;
///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGIDocument : public CGINode
{
public:
	DECL_GTPYECLASS_DYNCREATE(CGIDocument)

public:
	CGIDocument();
	CGIDocument( LPCTSTR ptszName );
    CGIDocument( CGIDocumentType* piDocumentType );
    CGIDocument( CGIDocument* piDocument, BOOL bDeep );

	void Construct();

protected:
	virtual ~CGIDocument();
	
public:
	virtual BOOL OnInitialUpdae();

	virtual CGIDocumentType* GetDoctype();
	virtual const CGIDocumentType* GetDoctype() const;

	CGIImplementation& GetImplementation();
	const CGIImplementation& GetImplementation() const;

	virtual CGIElement* GetRootElement();
	virtual const CGIElement* GetRootElement() const;

	virtual CGIElement* CreateElement( LPCTSTR pctszTagName ) const;
	virtual CGIDocumentFragment* CreateDocumentFragment() const;
	virtual CGIText* CreateTextNode( LPCTSTR pctszData ) const;
	virtual CGIComment* CreateComment( LPCTSTR pctszData ) const;
	virtual CGICDATASection* CeateCDATASection( LPCTSTR pctszData ) const;
	virtual CGIProcessingInstruction* CreateProcessingInstruction( LPCTSTR pctszTarget,
																   LPCTSTR pctszData ) const;
	virtual CGIAttr* CreateAttribute( LPCTSTR pctszName ) const;
	virtual CGIEntityReference* CreateEntityReference( LPCTSTR pctszName ) const;

	virtual CGNodeList* GetElementsByTagName( LPCTSTR pctszTagname, LPCTSTR pctszLocalName = NULL ) const;

	/// Introduced in DOM Level 2:
	virtual CGINode* ImportNode( const CGINode& rImportedNode,
								 BOOL bDeep ) const;

	virtual CGIElement* CreateElementNS( LPCTSTR pctszNamespaceURI,
										 LPCTSTR pctszQualifiedName ) const;
	virtual CGIAttr* CreateAttributeNS( LPCTSTR pctszNamespaceURI,
									    LPCTSTR pctszQualifiedName ) const;
	virtual CGNodeList* GetElementsByTagNameNS( LPCTSTR pctszNamespaceURI,
											    LPCTSTR pctszLocalName ) const;

	CGIElement* GetElementById( LPCTSTR pctszElementId );

protected:
	CGIImplementation*		m_pImplementation;
	CGIDocumentType*		m_pDocumentType;
};

inline CGIDocumentType* CGIDocument::GetDoctype() {
	return m_pDocumentType; }

inline const CGIDocumentType* CGIDocument::GetDoctype() const {
	return m_pDocumentType; }

inline CGIImplementation& CGIDocument::GetImplementation() {
	ASSERT( m_pImplementation );
	return *m_pImplementation; }

inline const CGIImplementation& CGIDocument::GetImplementation() const {
	ASSERT( m_pImplementation );
	return *m_pImplementation; }

inline CGIElement* CGIDocument::GetRootElement() {
	return (CGIElement*)GetFirst(); }

inline const CGIElement* CGIDocument::GetRootElement() const {
	return (CGIElement*)GetFirst(); }

inline CGIDocumentFragment* CGIDocument::CreateDocumentFragment() const {
		return NULL; }

inline CGIText* CGIDocument::CreateTextNode( LPCTSTR pctszData ) const {
	return NULL; }

inline CGIComment* CGIDocument::CreateComment( LPCTSTR pctszData ) const {
	return NULL; }

inline CGICDATASection* CGIDocument::CeateCDATASection( LPCTSTR pctszData ) const {
	return NULL; }

inline CGIProcessingInstruction* CGIDocument::CreateProcessingInstruction( LPCTSTR pctszTarget,
																		   LPCTSTR pctszData ) const {
	return NULL; }

inline CGIAttr* CGIDocument::CreateAttribute( LPCTSTR pctszName ) const {
	return NULL; };

inline CGIEntityReference* CGIDocument::CreateEntityReference( LPCTSTR pctszName ) const {
	return NULL; };

inline CGNodeList* CGIDocument::GetElementsByTagName( LPCTSTR pctszTagname, LPCTSTR pctszLocalName /*= NULL*/ ) const {
	return NULL; };

inline CGINode* CGIDocument::ImportNode( const CGINode& rImportedNode,
										 BOOL bDeep ) const {
	return NULL; }

inline CGIElement* CGIDocument::CreateElementNS( LPCTSTR pctszNamespaceURI,
												 LPCTSTR pctszQualifiedName ) const {
	return NULL; }

inline CGIAttr* CGIDocument::CreateAttributeNS( LPCTSTR pctszNamespaceURI,
												LPCTSTR pctszQualifiedName ) const {
	return NULL; }

inline CGNodeList* CGIDocument::GetElementsByTagNameNS( LPCTSTR pctszNamespaceURI,
													    LPCTSTR pctszLocalName ) const {
	return NULL; }

#endif //!___GI_DOCUMENT__PH___
