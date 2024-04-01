#ifndef ___G_NODE__PH___
#define ___G_NODE__PH___

class CGINode;
class CGINodeList;

class CGNodeList;

class CGINamedNodeMap;
class CGNamedNodeMap;
class CGElement;

class CGDocument;
class CGIDocument;

class CGDocumentType;
class CGIDocumentType;

class CGDocumentFragment;
class CGText;
class CGComment;
class CGCDATASection;
class CGProcessingInstruction;
class CGEntityReference;
class CGAttr;
class CGImplementation;

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGNode
{
public:
	/// NodeType
	enum ENodeType {	
			_EVENT_NODE					= -1,
			_NODE						= 0,
			ELEMENT_NODE				= 1,
			ATTRIBUTE_NODE				= 2,
			TEXT_NODE					= 3,
			CDATA_SECTION_NODE			= 4,
			ENTITY_REFERENCE_NODE		= 5,
			ENTITY_NODE					= 6,
			PROCESSING_INSTRUCTION_NODE = 7,
			COMMENT_NODE				= 8,
			DOCUMENT_NODE				= 9,
			DOCUMENT_TYPE_NODE			= 10,
			DOCUMENT_FRAGMENT_NODE		= 11,
			NOTATION_NODE				= 12,
		
			ATTRIBUTE_GROUP_NODE		= 512,	
	};

public:
	CGNode();
	CGNode( const CGNode& rNode );
	CGNode( CGINode* piNode );
    ~CGNode();

    CGNode& operator=( const CGNode& rNode );
    BOOL operator==( const CGNode& rNode ) const;
    BOOL operator!=( const CGNode& rNode ) const;

public:
	///{{ DOM ////////////////////////////////////////////////////////////////////
	CString GetNodeName() const;
	void GetNodeName( CString& rNodeName  ) const;

	CString GetNodeValue() const;
	void GetNodeValue( CString& cszValue ) const;		
									
	BOOL SetNodeValue( LPCTSTR pctszValue );
	BOOL SetNodeValue( const CString& rcszValue );

	INT GetNodeType();

	CGNode GetParentNode() const;
	const CGNode GetParentNode();

	CGNodeList GetNodeList() const;
	const CGNodeList GetNodeList();

	CGNode GetFirstChild() const;
	const CGNode GetFirstChild();

	CGNode GetLastChild() const;
	const CGNode GetLastChild();

	CGNode GetPreviousSibling();
	const CGNode GetPreviousSibling() const;

	CGNode GetNextSibling();
	const CGNode GetNextSibling() const;

	CGNamedNodeMap GetAttributes() const;

	/// Modified in DOM Level 2:
	CGDocument GetOwnerDocument();
	const CGDocument GetOwnerDocument() const;

	CGNode InsertBefore( CGNode& rNewChild,
						 CGNode& refChild );				/// raises(IDOMException);
	CGNode InsertAfter( CGNode& rNewChild, 
						CGNode& rRef );						/// raises(IDOMException);
	CGNode ReplaceChild( CGNode& rNewChild,					
						CGNode& rOldChild );				/// raises(IDOMException);
	CGNode AppendChild( CGNode& rNewChild );				/// raises(IDOMException);
	CGNode RemoveChild( CGNode& rOldChild );				/// raises(IDOMException);
	
	BOOL HasChildNodes() const;
	CGNode CloneNode( BOOL bDeep ) const;

	void Normalize();
	BOOL IsSupported( LPCTSTR pctszFeature,
					  LPCTSTR pctszVersion ) const;

	CString GetNameSpaceURI() const;
	void GetNameSpaceURI( CString& rcszNameSpaceURI ) const;

	CString GetPrefix() const;								
	void GetPrefix( CString& rcszPrefix ) const;			/// raises(IDOMException) on setting
															///		INVALID_CHARACTER_ERR: Raised if the specified prefix
															///		contains an illegal character.
															///		
															///		NO_MODIFICATION_ALLOWED_ERR: Raised if this node is
															///		readonly.
															///		
															///		NAMESPACE_ERR: Raised if the specified prefix is
															///		malformed, if the namespaceURI of this node is null, if the
															///		specified prefix is "xml" and the namespaceURI of this node is
															///		different from "http://www.w3.org/XML/1998/namespace", if
															///		this node is an attribute and the specified prefix is "xmlns" and
															///		the namespaceURI of this node is different from
															///		"http://www.w3.org/2000/xmlns/", or if this node is an attribute
															///		and the qualifiedName of this node is "xmlns"
															///		[Namespaces].
	CString GetLocalName() const;
	void GetLocalName( CString& rcszLocalName ) const;

	BOOL HasAttributes() const;
	///}} DOM ////////////////////////////////////////////////////////////////////

protected:
	CGINode*	m_piNode;

	friend CGNamedNodeMap;
	friend CGDocument;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGNodeList
{
public:
    CGNodeList();
    CGNodeList( const CGNodeList& rNodeList );
    CGNodeList& operator=( const CGNodeList& rNodeList );
    ~CGNodeList();

protected:
    CGNodeList( CGINodeList* piNodeList );

public:
    BOOL operator==( const CGNodeList& rNodeList ) const;
    BOOL operator!=( const CGNodeList& rNodeList ) const;

    // DOM functions
    CGNode GetItem( INT nIndex ) const;

    // DOM read only attributes
    UINT GetLength() const;

	void CreateList();

#ifdef _DEBUG
	overrided void Dump( CDumpContext& dc ) const;
#endif

private:
    CGINodeList* m_piNodeList;

    friend CGNode;
    friend CGElement;
    friend CGDocument;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGNamedNodeMap
{
public:
    CGNamedNodeMap();
    CGNamedNodeMap( const CGNamedNodeMap& rNodeMap );
    ~CGNamedNodeMap();

private:
    CGNamedNodeMap( CGINamedNodeMap* piNodeMap );

public:
    CGNamedNodeMap& operator=( const CGNamedNodeMap& rNodeMap );
    BOOL operator==( const CGNamedNodeMap& rNodeMap ) const;
    BOOL operator!=( const CGNamedNodeMap& rNodeMap ) const;

    // DOM functions
    CGNode GetNamedItem( LPCTSTR ptszName ) const;
    CGNode SetNamedItem( const CGNode& rNode );
    CGNode RemoveNamedItem( LPCTSTR ptszName );
    CGNode GetItem( INT nIndex ) const;
    CGNode GetNamedItemNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName ) const;
    CGNode SetNamedItemNS( const CGNode& newNode );
    CGNode RemoveNamedItemNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName );

    // DOM read only attributes
    UINT GetLength() const;

	/// Helper function
	void CreateList();
    BOOL FindItem( LPCTSTR ptszName ) const;
	BOOL FindItemNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName ) const;

private:
    CGINamedNodeMap*	m_piNodeMap;

    friend CGNode;
    friend CGDocumentType;
    friend CGElement;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGDocument : public CGNode
{
public:
    CGDocument();
    explicit CGDocument( LPCTSTR pctszName );
	explicit CGDocument( const CGDocumentType& rDoctype );
    CGDocument( const CGDocument& rDocument );

public:
    virtual ~CGDocument();
    CGDocument& operator=( const CGDocument& rDocument );

    // DOM functions
    CGElement CreateElement( LPCTSTR pctszTagName );
    CGDocumentFragment CreateDocumentFragment();
    CGText CreateTextNode( LPCTSTR pctszData );
    CGComment CreateComment( LPCTSTR pctszData );
    CGCDATASection CreateCDATASection( LPCTSTR pctszData );
    CGProcessingInstruction CreateProcessingInstruction( LPCTSTR pctszTarget, LPCTSTR pctszData );
    CGAttr CreateAttribute( LPCTSTR pctszName );
    CGEntityReference CreateEntityReference( LPCTSTR pctszName );
    CGNodeList ElementsByTagName( LPCTSTR pctszTagName ) const;
    CGNode ImportNode(const CGNode& rImportedNode, BOOL bDeep );
    CGElement CreateElementNS( LPCTSTR pctszNsURI, LPCTSTR pctszQualifiedName );
    CGAttr CreateAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszQualifiedName );
    CGNodeList ElementsByTagNameNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName );
    CGElement ElementById( LPCTSTR pctszElementId );

    // DOM read only attributes
    CGDocumentType Doctype() const;
    CGImplementation Implementation() const;
    CGElement DocumentElement() const;

    // Overridden from CGNode
    CGNode::ENodeType GetNodeType() const;

    // Qt extensions
    /*bool setContent(const QByteArray& text, bool namespaceProcessing, QString *errorMsg=0, int *errorLine=0, int *errorColumn=0 );
    bool setContent(LPCTSTR text, bool namespaceProcessing, QString *errorMsg=0, int *errorLine=0, int *errorColumn=0 );
    bool setContent(QIODevice* dev, bool namespaceProcessing, QString *errorMsg=0, int *errorLine=0, int *errorColumn=0 );
    bool setContent(const QByteArray& text, QString *errorMsg=0, int *errorLine=0, int *errorColumn=0 );
    bool setContent(LPCTSTR text, QString *errorMsg=0, int *errorLine=0, int *errorColumn=0 );
    bool setContent(QIODevice* dev, QString *errorMsg=0, int *errorLine=0, int *errorColumn=0 );
    bool setContent(QXmlInputSource *source, QXmlReader *reader, QString *errorMsg=0, int *errorLine=0, int *errorColumn=0 );

    // Qt extensions
    QString toString(int = 1) const;
    QByteArray toByteArray(int = 1) const;*/

private:
    CGDocument( CGIDocument* piDocument );

protected:
    friend class CGNode;
};

inline CGNode::ENodeType CGDocument::GetNodeType() const { 
	return CGNode::DOCUMENT_NODE; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGDocumentType : public CGNode
{
public:
    CGDocumentType();
    CGDocumentType( const CGDocumentType& rDocumentType );
    CGDocumentType& operator=( const CGDocumentType& rDocumentType );

public:
    // DOM read only attributes
    CString GetName() const;

    CGNamedNodeMap GetEntities() const;
    CGNamedNodeMap GetNotations() const;
    CString GetPublicId() const;
    CString GetSystemId() const;
    CString GetInternalSubset() const;

    // Overridden from CGNode
    virtual INT GetNodeType() const;

private:
    CGDocumentType( CGIDocumentType* piDocumentType );

    friend class CGImplementation;
    friend class CGDocument;
    friend class CGNode;
};

inline INT CGDocumentType::GetNodeType() const {
	return CGNode::DOCUMENT_TYPE_NODE; } 

#endif //!___G_NODE__PH___
