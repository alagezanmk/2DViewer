#ifndef ___G_I_NODE__PH___
#define ___G_I_NODE__PH___

#include <gbase\gEventNode.h>
#include <g\type\gNode.h>
#include "giNodeList.h"

class GDOM_EXT_CLASS CGDomMutationEvent : public CGMutationEvent
{
public:
	static LPCTSTR	DOMExtUpdateAttr;
	static LPCTSTR	DOMExtValidateAttr;

public:
	CGDomMutationEvent();

protected:
	virtual ~CGDomMutationEvent();
};

class CGINode;

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGINameSpaceString
{
public:
	static void SplitQualifiedName( CString& rcszPrefix, CString& rcszName, LPCTSTR pctszQualifiedName, BOOL bHasURI = FALSE );
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGUserDataHandler
{
public:
	// OperationType
	enum {	NODE_CLONED		= 1,
			NODE_IMPORTED   = 2,
			NODE_DELETED    = 3,
			NODE_RENAMED    = 4,
			NODE_ADOPTED    = 5, };

	virtual void Handle( unsigned short usnOperation,
						 LPCTSTR pctszKey, 
                         void* pUserData, 
                         CGINode& rSrc, 
                         CGINode& rDsc ) 
	{}
};

class CGIObject : public CGObject
{};

///////////////////////////////////////////////////////////////////////////////////////////////////

class CGIDocument;
class CGNodeArray;
///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGINode : public CGObject, public CGEventNode
{
public:
	DECL_GTPYECLASS_DYNCREATE(CGINode)

public:
	// DocumentPosition
	enum DOCUMENT_POSITION {	
			DOCUMENT_POSITION_UNKNOWN	   = 0x0,
			DOCUMENT_POSITION_DISCONNECTED = 0x01,
			DOCUMENT_POSITION_PRECEDING    = 0x02,
			DOCUMENT_POSITION_FOLLOWING    = 0x04,
			DOCUMENT_POSITION_CONTAINS     = 0x08,
			DOCUMENT_POSITION_CONTAINED_BY = 0x10,
			DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC = 0x20, };

	enum NODE_FLAG {	
			DATA_MODIFIED_NODE_FLAG				= 1,
			DATA_DISPLAY_MODIFIED_NODE_FLAG		= 2,
			DATA_CTM_MODIFIED_NODE_FLAG			= 4,
	};

public:
	CGINode();
	CGINode( CGIDocument* piDocument, CGINode* piParent = NULL );
	CGINode( CGINode* piNode, BOOL bDeep = FALSE );
	void Construct(); 

protected:
	virtual ~CGINode();

public:
	///{{ DOM Methods
	// readonly attribute DOMString nodeName;
	virtual CString GetNodeName() const;
	virtual void GetNodeName( CString& rcszName ) const;

	virtual void SetNodeName( LPCTSTR pctszName );

	/// attribute DOMString nodeValue;
	virtual CString GetNodeValue() const;
	virtual void GetNodeValue( CString& rcszValue ) const;

	virtual BOOL SetNodeValue( LPCTSTR pctszValue );
	virtual BOOL SetNodeValue( const CString& rcszValue );

	/// readonly attribute unsigned short nodeType;
	overrided INT GetNodeType() const;

	/// readonly attribute Node parentNode;
	CGINode* GetParent();
	const CGINode* GetParent() const;

	/// readonly attribute Node childNodes;
	CGINodeList* GetChildNodes();

	/// readonly attribute Node firstChild;
	CGINode* GetFirst();
	const CGINode* GetFirst() const;

	/// readonly attribute Node lastChild;
	CGINode* GetLast();
	const CGINode* GetLast() const;

	/// readonly attribute Node previousSibling;
	CGINode* GetPrev();
	const CGINode* GetPrev() const;

	/// readonly attribute Node nextSibling;
	CGINode* GetNext();
	const CGINode* GetNext() const;

	/// readonly attribute NamedNodeMap attributes;
	CGINamedNodeMap* GetAttributes() const;

	/// Modified in DOM Level 2:
	/// readonly attribute Document ownerDocument;
	CGIDocument* GetOwnerDocument();
	const CGIDocument* GetOwnerDocument() const;

	/// Modified in DOM Level 3:
	virtual CGINode* InsertBefore( CGINode& rNewChild, CGINode& rRef );

	/// Introduced in DOM Level 3:
	virtual CGINode* ReplaceChild( CGINode& rNewChild, CGINode& rOldNode );

	/// Introduced in DOM Level 3:
	virtual CGINode* AppendChild( CGINode& rNewChild );

	/// Introduced in DOM Level 3:
	virtual CGINode* RemoveChild( CGINode& rChild );

	overrided BOOL HasChildNodes() const;

	/// Introduced in DOM Level 2:
	virtual CGINode* CloneNode( BOOL bDeep ) const;

	/// Modified in DOM Level 3:
	virtual void Normalize();

	/// Introduced in DOM Level 2:
	virtual BOOL IsSupported( LPCTSTR pctszFeature,
							  LPCTSTR pctszVersion ) const;

	/// Introduced in DOM Level 2:
	/// readonly attribute DOMString namespaceURI;
	virtual LPCTSTR GetNameSpaceURI() const;
	virtual void GetNameSpaceURI( CString& rcszameSpaceURI ) const;

	/// Introduced in DOM Level 2:
	/// attribute DOMString prefix;
	virtual LPCTSTR GetPrefix() const;
	virtual void GetPrefix( CString& rcszPrefix ) const;

	/// Introduced in DOM Level 2:
	/// readonly attribute DOMString localName;
	virtual LPCTSTR GetLocalName() const;
	virtual void GetLocalName( CString& rcszLocalName ) const;

	/// Introduced in DOM Level 2:
	virtual BOOL HasAttributes() const;

	/// Introduced in DOM Level 2:
	virtual LPCTSTR GetBaseURI() const;

	/// Introduced in DOM Level 3:
    virtual unsigned short CompareDocumentPosition( CGINode& rOther ) const;

    /// Introduced in DOM Level 3:
	/// attribute DOMString textContent;
    virtual LPCTSTR GetTextContent() const;
	virtual BOOL SetTextContent( LPCTSTR pctszText );
	virtual BOOL SetTextContent( const CString& rcszText );

	 /// Introduced in DOM Level 3:
    virtual BOOL IsSameNode( const CGINode& rOther ) const;

    /// Introduced in DOM Level 3:
    virtual LPCTSTR LookupPrefix( LPCTSTR pctszNamespaceURI ) const;

    /// Introduced in DOM Level 3:
    virtual BOOL IsDefaultNamespace( LPCTSTR pctszNamespaceURI ) const;

    /// Introduced in DOM Level 3:
    virtual LPCTSTR LookupNamespaceURI( LPCTSTR pctszPrefix ) const;

    /// Introduced in DOM Level 3:
    virtual BOOL IsEqualNode( const CGINode& rNode ) const;

    /// Introduced in DOM Level 3:
    virtual CGIObject* GetFeature( LPCTSTR pctszFeature, LPCTSTR pctszVersion );
    virtual const CGIObject* GetFeature( LPCTSTR pctszFeature, LPCTSTR pctszVersion ) const;

    /// Introduced in DOM Level 3:
    void* SetUserData( LPCTSTR pctszKey, void* pData = NULL,
					   CGUserDataHandler* pHandler = NULL );

    /// Introduced in DOM Level 3:
    void* GetUserData( LPCTSTR pctszKey ) const;
	///}} DOM Methods

	///{{ Customized DOM
	virtual CGINode* InsertAfter( CGINode& rNewChild, CGINode& rRef );
	overrided void RemoveAllChild();	
	void* RemoveUserData( LPCTSTR pctszKey );
	///}} Customized DOM

	overrided void OnNodeListModified();

public:
#ifdef _DEBUG
	overrided void OnFinalRelease();
	overrided void Dump( CDumpContext& dc ) const;
#endif

	/// Helper function for Attribues and Element
	virtual CString GetQualifiedName() const;
	virtual void GetQualifiedName( CString& rcszQName ) const;

	/// CGINode derived class overridable function
	BOOL IsKindOf( INT nType ) const;
	virtual LPCTSTR GetName() const;

	/// Initialization function
	virtual BOOL OnInitialUpdate();

	INT SetNodeFlag( INT nFlag, BOOL bSet = TRUE );
	INT IsNodeFlagSet( INT nFlag ) const;
	INT GetNodeFlag() const;

	BOOL SetModified( BOOL bModified = TRUE );
	BOOL GetModified() const;

protected:
	overrided void AttachChild( CGEventNode& rNode );
	overrided void Attach( CGEventNode& rNode );
	overrided void Detach( CGEventNode& rNode );

	virtual void SetPrefix( LPCTSTR pctszPrefix );
	virtual void SetPrefix( const CString& rcszPrefix );

	virtual void SetNameSpaceURI( LPCTSTR pctszNameSpaceURI );
	virtual void SetNameSpaceURI( CString& rcszNameSpaceURI );
	overrided CGMutationEvent* CreateAttrModifiedMutationEvent( LPCTSTR pctszEventType );

protected:
	CGIDocument*			m_pOwnerDocument;

    CString					m_cszName;			// This is the local name if prefix != null
	INT						m_nNodeFlag;

	CMapStringToPtr*		m_pmapUserDataToKey;

	friend CGIDocument;
	friend CGNodeArray;
};

inline CString CGINode::GetNodeValue() const {
	return CString(); }

inline void CGINode::GetNodeValue( CString& rcsValue ) const {
	rcsValue.Empty(); }

inline INT CGINode::GetNodeType() const {
	return CGNode::_NODE; }

inline CGINode* CGINode::GetParent() {
	return (CGINode*)m_pParent; }

inline const CGINode* CGINode::GetParent() const {
	return (CGINode*)m_pParent; }

inline CGINode* CGINode::GetNext() {
	return (CGINode*)m_pNext; }

inline const CGINode* CGINode::GetNext() const {
	return (CGINode*)m_pNext; }

inline CGINode* CGINode::GetPrev() {
	return (CGINode*)m_pPrev; }

inline const CGINode* CGINode::GetPrev() const {
	return (CGINode*)m_pPrev; }

inline CGINode* CGINode::GetFirst() {
	return (CGINode*)m_pFirst; }

inline const CGINode* CGINode::GetFirst() const {
	return (CGINode*)m_pFirst; }

inline CGINode* CGINode::GetLast() {
	return (CGINode*)m_pLast; }

inline const CGINode* CGINode::GetLast() const {
	return (CGINode*)m_pLast; }

inline CGINamedNodeMap* CGINode::GetAttributes() const {
	return NULL; }

inline CGIDocument* CGINode::GetOwnerDocument() {
	return m_pOwnerDocument; }

inline const CGIDocument* CGINode::GetOwnerDocument() const {
	return m_pOwnerDocument; }

inline LPCTSTR CGINode::GetNameSpaceURI() const {
	return NULL; }

inline void CGINode::GetNameSpaceURI( CString& rcszNameSpaceURI ) const {
	rcszNameSpaceURI.Empty(); }
	
inline LPCTSTR CGINode::GetPrefix() const {
	return NULL; }

inline void CGINode::GetPrefix( CString& rcszPrefix ) const {
	rcszPrefix.Empty(); }

inline void CGINode::SetPrefix( LPCTSTR pctszPrefix ) 
{}

inline void CGINode::SetPrefix( const CString& rcszPrefix )
{}

inline void CGINode::SetNameSpaceURI( LPCTSTR pctszNameSpaceURI )
{}

inline void CGINode::SetNameSpaceURI( CString& rcszNameSpaceURI )
{}

inline LPCTSTR CGINode::GetName() const {
	return m_cszName; }

inline BOOL CGINode::HasAttributes() const {
	return FALSE; }

inline LPCTSTR CGINode::GetBaseURI() const {
	return NULL; }

inline unsigned short CGINode::CompareDocumentPosition( CGINode& rOther ) const {
	ASSERT( FALSE );
	return DOCUMENT_POSITION_UNKNOWN; }

inline LPCTSTR CGINode::GetTextContent() const {
	return NULL; }

inline BOOL CGINode::SetTextContent( LPCTSTR pctszText ) {
	return TRUE; }

inline BOOL CGINode::SetTextContent( const CString& rcszText ) {
	return TRUE; }

inline BOOL CGINode::IsSameNode( const CGINode& rOther ) const {
	return FALSE; }

inline LPCTSTR CGINode::LookupPrefix( LPCTSTR pctszNamespaceURI ) const {
	return NULL; }

inline BOOL CGINode::IsDefaultNamespace( LPCTSTR pctszNamespaceURI ) const {
	return FALSE; }

inline LPCTSTR CGINode::LookupNamespaceURI( LPCTSTR pctszPrefix ) const {
	return NULL; }

inline BOOL CGINode::IsEqualNode( const CGINode& rNode ) const {
	return FALSE; }

inline CGIObject* CGINode::GetFeature( LPCTSTR pctszFeature, LPCTSTR pctszVersion ) {
	return NULL; }

inline const CGIObject* CGINode::GetFeature( LPCTSTR pctszFeature, LPCTSTR pctszVersion ) const {
	return NULL; }

inline BOOL CGINode::IsKindOf( INT nType ) const {
	return GetNodeType() == nType; }

inline BOOL CGINode::HasChildNodes() const {
	return CGEventNode::HasChildNodes(); }

inline INT CGINode::IsNodeFlagSet( INT nFlag ) const {
	return nFlag == (m_nNodeFlag & nFlag); }

inline INT CGINode::GetNodeFlag() const {
	return m_nNodeFlag; }

inline BOOL CGINode::SetModified( BOOL bModified /*= TRUE*/ ) 
{
	BOOL bOldModified = IsNodeFlagSet( DATA_MODIFIED_NODE_FLAG );
	SetNodeFlag( DATA_MODIFIED_NODE_FLAG, bModified );
	return bOldModified;
}

inline BOOL CGINode::GetModified() const
{
	BOOL bModified = IsNodeFlagSet( DATA_MODIFIED_NODE_FLAG );
	return bModified;
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////
class CGICharacterData : public CGINode
{
	virtual LPCTSTR Getdata() const;
	virtual BOOL Setdata( LPCTSTR pctszData );
															
	virtual INT GetLength() const;
	virtual void GetSubstringData( INT nOffset,
								   INT nCount,
								    CString& rcszData ) const;
	virtual void AppendData( LPCTSTR pctszArg );
	virtual void InsertData( INT nOffset,
					 LPCTSTR pctszArg );					
	virtual void DeleteData( INT nOffset,
							 INT nCount );
	virtual void ReplaceData( INT nOffset,
							  INT nCount,
							  LPCTSTR pctszArg );

protected:
	CString m_cszData;
};

inline LPCTSTR CGICharacterData::Getdata() const {
	return m_cszData; }

inline INT CGICharacterData::GetLength() const {
	return m_cszData.GetLength(); }
	
///////////////////////////////////////////////////////////////////////////////////////////////////
class CGIComment : public CGICharacterData
{};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGIText : public CGICharacterData
{};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGICDATASection : public CGIText
{};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGIProcessingInstruction : public CGINode
{};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGIEntityReference : public CGINode
{};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGIDocumentType : public CGINode
{
public:
    CGIDocumentType( CGIDocument* piDocument, CGINode* piParent = NULL );
    CGIDocumentType( CGIDocumentType* piDocumentType, BOOL bDeep );
	void Construct();

    virtual ~CGIDocumentType();

public:
    // Reimplemented from CGINode
    virtual CGINode* CloneNode( BOOL bDeep );

	// Introduced in DOM Level 3:
	virtual CGINode* InsertBefore( CGINode& rNewChild, CGINode& rRef );

	// Customized DOM
	virtual CGINode* InsertAfter( CGINode& rNewChild, CGINode& rRef );

	// Introduced in DOM Level 3:
	virtual CGINode* ReplaceChild( CGINode& rNewChild, CGINode& rOldNode );

	// Introduced in DOM Level 3:
	virtual CGINode* AppendChild( CGINode& rNewChild );

	// Introduced in DOM Level 3:
	virtual CGINode* RemoveChild( CGINode& rChild );

    CGINamedNodeMap* GetEntities() const;
    CGINamedNodeMap* GetNotations() const;
    CString GetPublicId() const;
    CString GetSystemId() const;
    CString GetInternalSubset() const;

    overrided INT GetNodeType() const;

public:
    CGINamedNodeMap*	m_pimapEntities;
    CGINamedNodeMap*	m_pimapNotations;
    CString				m_cszPublicId;
    CString				m_cszSystemId;
    CString				m_cszInternalSubset;
};

inline CGINamedNodeMap* CGIDocumentType::GetEntities() const {
	return m_pimapEntities; }

inline CGINamedNodeMap* CGIDocumentType::GetNotations() const {
	return m_pimapNotations; }

inline CString CGIDocumentType::GetPublicId() const {
	return m_cszPublicId; }

inline CString CGIDocumentType::GetSystemId() const {
	return m_cszSystemId; }

inline CString CGIDocumentType::GetInternalSubset() const {
	return m_cszInternalSubset; }

inline INT CGIDocumentType::GetNodeType() const {
	return CGNode::DOCUMENT_TYPE_NODE; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGIImplementation : public CGObject
{
public:
    CGIImplementation();
    CGIImplementation* Clone();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGIDocumentFragment : public CGINode
{};

#endif //!___G_I_NODE__PH___
