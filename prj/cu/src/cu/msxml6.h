// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMImplementation wrapper class

class IXMLDOMImplementation : public COleDispatchDriver
{
public:
	IXMLDOMImplementation() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMImplementation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMImplementation(const IXMLDOMImplementation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL hasFeature(LPCTSTR feature, LPCTSTR version);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNode wrapper class

class IXMLDOMNode : public COleDispatchDriver
{
public:
	IXMLDOMNode() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMNode(const IXMLDOMNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNodeList wrapper class

class IXMLDOMNodeList : public COleDispatchDriver
{
public:
	IXMLDOMNodeList() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMNodeList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMNodeList(const IXMLDOMNodeList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetItem(long index);
	long GetLength();
	LPDISPATCH nextNode();
	void reset();
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNamedNodeMap wrapper class

class IXMLDOMNamedNodeMap : public COleDispatchDriver
{
public:
	IXMLDOMNamedNodeMap() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMNamedNodeMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMNamedNodeMap(const IXMLDOMNamedNodeMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH getNamedItem(LPCTSTR name);
	LPDISPATCH setNamedItem(LPDISPATCH newItem);
	LPDISPATCH removeNamedItem(LPCTSTR name);
	LPDISPATCH GetItem(long index);
	long GetLength();
	LPDISPATCH getQualifiedItem(LPCTSTR baseName, LPCTSTR namespaceURI);
	LPDISPATCH removeQualifiedItem(LPCTSTR baseName, LPCTSTR namespaceURI);
	LPDISPATCH nextNode();
	void reset();
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocument wrapper class

class IXMLDOMDocument : public COleDispatchDriver
{
public:
	IXMLDOMDocument() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMDocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMDocument(const IXMLDOMDocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	LPDISPATCH GetDoctype();
	LPDISPATCH GetImplementation();
	LPDISPATCH GetDocumentElement();
	void SetRefDocumentElement(LPDISPATCH newValue);
	LPDISPATCH createElement(LPCTSTR tagName);
	LPDISPATCH createDocumentFragment();
	LPDISPATCH createTextNode(LPCTSTR data);
	LPDISPATCH createComment(LPCTSTR data);
	LPDISPATCH createCDATASection(LPCTSTR data);
	LPDISPATCH createProcessingInstruction(LPCTSTR target, LPCTSTR data);
	LPDISPATCH createAttribute(LPCTSTR name);
	LPDISPATCH createEntityReference(LPCTSTR name);
	LPDISPATCH getElementsByTagName(LPCTSTR tagName);
	LPDISPATCH createNode(const VARIANT& type, LPCTSTR name, LPCTSTR namespaceURI);
	LPDISPATCH nodeFromID(LPCTSTR idString);
	BOOL load(const VARIANT& xmlSource);
	long GetReadyState();
	LPDISPATCH GetParseError();
	CString GetUrl();
	BOOL GetAsync();
	void SetAsync(BOOL bNewValue);
	void abort();
	BOOL loadXML(LPCTSTR bstrXML);
	void save(const VARIANT& destination);
	BOOL GetValidateOnParse();
	void SetValidateOnParse(BOOL bNewValue);
	BOOL GetResolveExternals();
	void SetResolveExternals(BOOL bNewValue);
	BOOL GetPreserveWhiteSpace();
	void SetPreserveWhiteSpace(BOOL bNewValue);
	void SetOnreadystatechange(const VARIANT& newValue);
	void SetOndataavailable(const VARIANT& newValue);
	void SetOntransformnode(const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocumentType wrapper class

class IXMLDOMDocumentType : public COleDispatchDriver
{
public:
	IXMLDOMDocumentType() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMDocumentType(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMDocumentType(const IXMLDOMDocumentType& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	CString GetName();
	LPDISPATCH GetEntities();
	LPDISPATCH GetNotations();
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMElement wrapper class

class IXMLDOMElement : public COleDispatchDriver
{
public:
	IXMLDOMElement() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMElement(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMElement(const IXMLDOMElement& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	CString GetTagName();
	VARIANT getAttribute(LPCTSTR name);
	void setAttribute(LPCTSTR name, const VARIANT& value);
	void removeAttribute(LPCTSTR name);
	LPDISPATCH getAttributeNode(LPCTSTR name);
	LPDISPATCH setAttributeNode(LPDISPATCH DOMAttribute);
	LPDISPATCH removeAttributeNode(LPDISPATCH DOMAttribute);
	LPDISPATCH getElementsByTagName(LPCTSTR tagName);
	void normalize();
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMAttribute wrapper class

class IXMLDOMAttribute : public COleDispatchDriver
{
public:
	IXMLDOMAttribute() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMAttribute(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMAttribute(const IXMLDOMAttribute& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	CString GetName();
	VARIANT GetValue();
	void SetValue(const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocumentFragment wrapper class

class IXMLDOMDocumentFragment : public COleDispatchDriver
{
public:
	IXMLDOMDocumentFragment() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMDocumentFragment(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMDocumentFragment(const IXMLDOMDocumentFragment& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMText wrapper class

class IXMLDOMText : public COleDispatchDriver
{
public:
	IXMLDOMText() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMText(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMText(const IXMLDOMText& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
	long GetLength();
	CString substringData(long offset, long count);
	void appendData(LPCTSTR data);
	void insertData(long offset, LPCTSTR data);
	void deleteData(long offset, long count);
	void replaceData(long offset, long count, LPCTSTR data);
	LPDISPATCH splitText(long offset);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMCharacterData wrapper class

class IXMLDOMCharacterData : public COleDispatchDriver
{
public:
	IXMLDOMCharacterData() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMCharacterData(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMCharacterData(const IXMLDOMCharacterData& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
	long GetLength();
	CString substringData(long offset, long count);
	void appendData(LPCTSTR data);
	void insertData(long offset, LPCTSTR data);
	void deleteData(long offset, long count);
	void replaceData(long offset, long count, LPCTSTR data);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMComment wrapper class

class IXMLDOMComment : public COleDispatchDriver
{
public:
	IXMLDOMComment() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMComment(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMComment(const IXMLDOMComment& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
	long GetLength();
	CString substringData(long offset, long count);
	void appendData(LPCTSTR data);
	void insertData(long offset, LPCTSTR data);
	void deleteData(long offset, long count);
	void replaceData(long offset, long count, LPCTSTR data);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMCDATASection wrapper class

class IXMLDOMCDATASection : public COleDispatchDriver
{
public:
	IXMLDOMCDATASection() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMCDATASection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMCDATASection(const IXMLDOMCDATASection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
	long GetLength();
	CString substringData(long offset, long count);
	void appendData(LPCTSTR data);
	void insertData(long offset, LPCTSTR data);
	void deleteData(long offset, long count);
	void replaceData(long offset, long count, LPCTSTR data);
	LPDISPATCH splitText(long offset);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMProcessingInstruction wrapper class

class IXMLDOMProcessingInstruction : public COleDispatchDriver
{
public:
	IXMLDOMProcessingInstruction() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMProcessingInstruction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMProcessingInstruction(const IXMLDOMProcessingInstruction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	CString GetTarget();
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMEntityReference wrapper class

class IXMLDOMEntityReference : public COleDispatchDriver
{
public:
	IXMLDOMEntityReference() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMEntityReference(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMEntityReference(const IXMLDOMEntityReference& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMParseError wrapper class

class IXMLDOMParseError : public COleDispatchDriver
{
public:
	IXMLDOMParseError() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMParseError(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMParseError(const IXMLDOMParseError& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetErrorCode();
	CString GetUrl();
	CString GetReason();
	CString GetSrcText();
	long GetLine();
	long GetLinepos();
	long GetFilepos();
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocument2 wrapper class

class IXMLDOMDocument2 : public COleDispatchDriver
{
public:
	IXMLDOMDocument2() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMDocument2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMDocument2(const IXMLDOMDocument2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	LPDISPATCH GetDoctype();
	LPDISPATCH GetImplementation();
	LPDISPATCH GetDocumentElement();
	void SetRefDocumentElement(LPDISPATCH newValue);
	LPDISPATCH createElement(LPCTSTR tagName);
	LPDISPATCH createDocumentFragment();
	LPDISPATCH createTextNode(LPCTSTR data);
	LPDISPATCH createComment(LPCTSTR data);
	LPDISPATCH createCDATASection(LPCTSTR data);
	LPDISPATCH createProcessingInstruction(LPCTSTR target, LPCTSTR data);
	LPDISPATCH createAttribute(LPCTSTR name);
	LPDISPATCH createEntityReference(LPCTSTR name);
	LPDISPATCH getElementsByTagName(LPCTSTR tagName);
	LPDISPATCH createNode(const VARIANT& type, LPCTSTR name, LPCTSTR namespaceURI);
	LPDISPATCH nodeFromID(LPCTSTR idString);
	BOOL load(const VARIANT& xmlSource);
	long GetReadyState();
	LPDISPATCH GetParseError();
	CString GetUrl();
	BOOL GetAsync();
	void SetAsync(BOOL bNewValue);
	void abort();
	BOOL loadXML(LPCTSTR bstrXML);
	void save(const VARIANT& destination);
	BOOL GetValidateOnParse();
	void SetValidateOnParse(BOOL bNewValue);
	BOOL GetResolveExternals();
	void SetResolveExternals(BOOL bNewValue);
	BOOL GetPreserveWhiteSpace();
	void SetPreserveWhiteSpace(BOOL bNewValue);
	void SetOnreadystatechange(const VARIANT& newValue);
	void SetOndataavailable(const VARIANT& newValue);
	void SetOntransformnode(const VARIANT& newValue);
	LPDISPATCH GetNamespaces();
	VARIANT GetSchemas();
	void SetRefSchemas(const VARIANT& newValue);
	LPDISPATCH validate();
	void setProperty(LPCTSTR name, const VARIANT& value);
	VARIANT getProperty(LPCTSTR name);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMSchemaCollection wrapper class

class IXMLDOMSchemaCollection : public COleDispatchDriver
{
public:
	IXMLDOMSchemaCollection() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMSchemaCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMSchemaCollection(const IXMLDOMSchemaCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void add(LPCTSTR namespaceURI, const VARIANT& var);
	LPDISPATCH get(LPCTSTR namespaceURI);
	void remove(LPCTSTR namespaceURI);
	long GetLength();
	CString GetNamespaceURI(long index);
	void addCollection(LPDISPATCH otherCollection);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocument3 wrapper class

class IXMLDOMDocument3 : public COleDispatchDriver
{
public:
	IXMLDOMDocument3() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMDocument3(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMDocument3(const IXMLDOMDocument3& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	LPDISPATCH GetDoctype();
	LPDISPATCH GetImplementation();
	LPDISPATCH GetDocumentElement();
	void SetRefDocumentElement(LPDISPATCH newValue);
	LPDISPATCH createElement(LPCTSTR tagName);
	LPDISPATCH createDocumentFragment();
	LPDISPATCH createTextNode(LPCTSTR data);
	LPDISPATCH createComment(LPCTSTR data);
	LPDISPATCH createCDATASection(LPCTSTR data);
	LPDISPATCH createProcessingInstruction(LPCTSTR target, LPCTSTR data);
	LPDISPATCH createAttribute(LPCTSTR name);
	LPDISPATCH createEntityReference(LPCTSTR name);
	LPDISPATCH getElementsByTagName(LPCTSTR tagName);
	LPDISPATCH createNode(const VARIANT& type, LPCTSTR name, LPCTSTR namespaceURI);
	LPDISPATCH nodeFromID(LPCTSTR idString);
	BOOL load(const VARIANT& xmlSource);
	long GetReadyState();
	LPDISPATCH GetParseError();
	CString GetUrl();
	BOOL GetAsync();
	void SetAsync(BOOL bNewValue);
	void abort();
	BOOL loadXML(LPCTSTR bstrXML);
	void save(const VARIANT& destination);
	BOOL GetValidateOnParse();
	void SetValidateOnParse(BOOL bNewValue);
	BOOL GetResolveExternals();
	void SetResolveExternals(BOOL bNewValue);
	BOOL GetPreserveWhiteSpace();
	void SetPreserveWhiteSpace(BOOL bNewValue);
	void SetOnreadystatechange(const VARIANT& newValue);
	void SetOndataavailable(const VARIANT& newValue);
	void SetOntransformnode(const VARIANT& newValue);
	LPDISPATCH GetNamespaces();
	VARIANT GetSchemas();
	void SetRefSchemas(const VARIANT& newValue);
	LPDISPATCH validate();
	void setProperty(LPCTSTR name, const VARIANT& value);
	VARIANT getProperty(LPCTSTR name);
	LPDISPATCH validateNode(LPDISPATCH node);
	LPDISPATCH importNode(LPDISPATCH node, BOOL deep);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNotation wrapper class

class IXMLDOMNotation : public COleDispatchDriver
{
public:
	IXMLDOMNotation() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMNotation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMNotation(const IXMLDOMNotation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	VARIANT GetPublicId();
	VARIANT GetSystemId();
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMEntity wrapper class

class IXMLDOMEntity : public COleDispatchDriver
{
public:
	IXMLDOMEntity() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMEntity(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMEntity(const IXMLDOMEntity& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	VARIANT GetPublicId();
	VARIANT GetSystemId();
	CString GetNotationName();
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMParseError2 wrapper class

class IXMLDOMParseError2 : public COleDispatchDriver
{
public:
	IXMLDOMParseError2() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMParseError2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMParseError2(const IXMLDOMParseError2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetErrorCode();
	CString GetUrl();
	CString GetReason();
	CString GetSrcText();
	long GetLine();
	long GetLinepos();
	long GetFilepos();
	CString GetErrorXPath();
	LPDISPATCH GetAllErrors();
	CString errorParameters(long index);
	long GetErrorParametersCount();
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMParseErrorCollection wrapper class

class IXMLDOMParseErrorCollection : public COleDispatchDriver
{
public:
	IXMLDOMParseErrorCollection() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMParseErrorCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMParseErrorCollection(const IXMLDOMParseErrorCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetItem(long index);
	long GetLength();
	LPDISPATCH GetNext();
	void reset();
};
/////////////////////////////////////////////////////////////////////////////
// IXTLRuntime wrapper class

class IXTLRuntime : public COleDispatchDriver
{
public:
	IXTLRuntime() {}		// Calls COleDispatchDriver default constructor
	IXTLRuntime(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXTLRuntime(const IXTLRuntime& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetNodeName();
	VARIANT GetNodeValue();
	void SetNodeValue(const VARIANT& newValue);
	long GetNodeType();
	LPDISPATCH GetParentNode();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetPreviousSibling();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetAttributes();
	LPDISPATCH insertBefore(LPDISPATCH newChild, const VARIANT& refChild);
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH removeChild(LPDISPATCH childNode);
	LPDISPATCH appendChild(LPDISPATCH newChild);
	BOOL hasChildNodes();
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetNodeTypeString();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetDefinition();
	VARIANT GetNodeTypedValue();
	void SetNodeTypedValue(const VARIANT& newValue);
	VARIANT GetDataType();
	void SetDataType(LPCTSTR lpszNewValue);
	CString GetXml();
	CString transformNode(LPDISPATCH stylesheet);
	LPDISPATCH selectNodes(LPCTSTR queryString);
	LPDISPATCH selectSingleNode(LPCTSTR queryString);
	BOOL GetParsed();
	CString GetNamespaceURI();
	CString GetPrefix();
	CString GetBaseName();
	void transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject);
	long uniqueID(LPDISPATCH pNode);
	long depth(LPDISPATCH pNode);
	long childNumber(LPDISPATCH pNode);
	long ancestorChildNumber(LPCTSTR bstrNodeName, LPDISPATCH pNode);
	long absoluteChildNumber(LPDISPATCH pNode);
	CString formatIndex(long lIndex, LPCTSTR bstrFormat);
	CString formatNumber(double dblNumber, LPCTSTR bstrFormat);
	CString formatDate(const VARIANT& varDate, LPCTSTR bstrFormat, const VARIANT& varDestLocale);
	CString formatTime(const VARIANT& varTime, LPCTSTR bstrFormat, const VARIANT& varDestLocale);
};
/////////////////////////////////////////////////////////////////////////////
// IXSLTemplate wrapper class

class IXSLTemplate : public COleDispatchDriver
{
public:
	IXSLTemplate() {}		// Calls COleDispatchDriver default constructor
	IXSLTemplate(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXSLTemplate(const IXSLTemplate& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SetRefStylesheet(LPDISPATCH newValue);
	LPDISPATCH GetStylesheet();
	LPDISPATCH createProcessor();
};
/////////////////////////////////////////////////////////////////////////////
// IXSLProcessor wrapper class

class IXSLProcessor : public COleDispatchDriver
{
public:
	IXSLProcessor() {}		// Calls COleDispatchDriver default constructor
	IXSLProcessor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXSLProcessor(const IXSLProcessor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SetInput(const VARIANT& newValue);
	VARIANT GetInput();
	LPDISPATCH GetOwnerTemplate();
	void setStartMode(LPCTSTR mode, LPCTSTR namespaceURI);
	CString GetStartMode();
	CString GetStartModeURI();
	void SetOutput(const VARIANT& newValue);
	VARIANT GetOutput();
	BOOL transform();
	void reset();
	long GetReadyState();
	void addParameter(LPCTSTR baseName, const VARIANT& parameter, LPCTSTR namespaceURI);
	void addObject(LPDISPATCH obj, LPCTSTR namespaceURI);
	LPDISPATCH GetStylesheet();
};
/////////////////////////////////////////////////////////////////////////////
// IVBSAXXMLReader wrapper class

class IVBSAXXMLReader : public COleDispatchDriver
{
public:
	IVBSAXXMLReader() {}		// Calls COleDispatchDriver default constructor
	IVBSAXXMLReader(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVBSAXXMLReader(const IVBSAXXMLReader& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL getFeature(LPCTSTR strName);
	void putFeature(LPCTSTR strName, BOOL fValue);
	VARIANT getProperty(LPCTSTR strName);
	void putProperty(LPCTSTR strName, const VARIANT& varValue);
	LPDISPATCH GetEntityResolver();
	void SetRefEntityResolver(LPDISPATCH newValue);
	LPDISPATCH GetContentHandler();
	void SetRefContentHandler(LPDISPATCH newValue);
	LPDISPATCH GetDtdHandler();
	void SetRefDtdHandler(LPDISPATCH newValue);
	LPDISPATCH GetErrorHandler();
	void SetRefErrorHandler(LPDISPATCH newValue);
	CString GetBaseURL();
	void SetBaseURL(LPCTSTR lpszNewValue);
	CString GetSecureBaseURL();
	void SetSecureBaseURL(LPCTSTR lpszNewValue);
	void parse(const VARIANT& varInput);
	void parseURL(LPCTSTR strURL);
};
/////////////////////////////////////////////////////////////////////////////
// IVBSAXEntityResolver wrapper class

class IVBSAXEntityResolver : public COleDispatchDriver
{
public:
	IVBSAXEntityResolver() {}		// Calls COleDispatchDriver default constructor
	IVBSAXEntityResolver(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVBSAXEntityResolver(const IVBSAXEntityResolver& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	VARIANT resolveEntity(BSTR* strPublicId, BSTR* strSystemId);
};
/////////////////////////////////////////////////////////////////////////////
// IVBSAXContentHandler wrapper class

class IVBSAXContentHandler : public COleDispatchDriver
{
public:
	IVBSAXContentHandler() {}		// Calls COleDispatchDriver default constructor
	IVBSAXContentHandler(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVBSAXContentHandler(const IVBSAXContentHandler& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SetRefDocumentLocator(LPDISPATCH newValue);
	void startDocument();
	void endDocument();
	void startPrefixMapping(BSTR* strPrefix, BSTR* strURI);
	void endPrefixMapping(BSTR* strPrefix);
	void startElement(BSTR* strNamespaceURI, BSTR* strLocalName, BSTR* strQName, LPDISPATCH oAttributes);
	void endElement(BSTR* strNamespaceURI, BSTR* strLocalName, BSTR* strQName);
	void characters(BSTR* strChars);
	void ignorableWhitespace(BSTR* strChars);
	void processingInstruction(BSTR* strTarget, BSTR* strData);
	void skippedEntity(BSTR* strName);
};
/////////////////////////////////////////////////////////////////////////////
// IVBSAXLocator wrapper class

class IVBSAXLocator : public COleDispatchDriver
{
public:
	IVBSAXLocator() {}		// Calls COleDispatchDriver default constructor
	IVBSAXLocator(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVBSAXLocator(const IVBSAXLocator& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetColumnNumber();
	long GetLineNumber();
	CString GetPublicId();
	CString GetSystemId();
};
/////////////////////////////////////////////////////////////////////////////
// IVBSAXAttributes wrapper class

class IVBSAXAttributes : public COleDispatchDriver
{
public:
	IVBSAXAttributes() {}		// Calls COleDispatchDriver default constructor
	IVBSAXAttributes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVBSAXAttributes(const IVBSAXAttributes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetLength();
	CString getURI(long nIndex);
	CString getLocalName(long nIndex);
	CString getQName(long nIndex);
	long getIndexFromName(LPCTSTR strURI, LPCTSTR strLocalName);
	long getIndexFromQName(LPCTSTR strQName);
	CString getType(long nIndex);
	CString getTypeFromName(LPCTSTR strURI, LPCTSTR strLocalName);
	CString getTypeFromQName(LPCTSTR strQName);
	CString getValue(long nIndex);
	CString getValueFromName(LPCTSTR strURI, LPCTSTR strLocalName);
	CString getValueFromQName(LPCTSTR strQName);
};
/////////////////////////////////////////////////////////////////////////////
// IVBSAXDTDHandler wrapper class

class IVBSAXDTDHandler : public COleDispatchDriver
{
public:
	IVBSAXDTDHandler() {}		// Calls COleDispatchDriver default constructor
	IVBSAXDTDHandler(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVBSAXDTDHandler(const IVBSAXDTDHandler& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void notationDecl(BSTR* strName, BSTR* strPublicId, BSTR* strSystemId);
	void unparsedEntityDecl(BSTR* strName, BSTR* strPublicId, BSTR* strSystemId, BSTR* strNotationName);
};
/////////////////////////////////////////////////////////////////////////////
// IVBSAXErrorHandler wrapper class

class IVBSAXErrorHandler : public COleDispatchDriver
{
public:
	IVBSAXErrorHandler() {}		// Calls COleDispatchDriver default constructor
	IVBSAXErrorHandler(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVBSAXErrorHandler(const IVBSAXErrorHandler& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void error(LPDISPATCH oLocator, BSTR* strErrorMessage, long nErrorCode);
	void fatalError(LPDISPATCH oLocator, BSTR* strErrorMessage, long nErrorCode);
	void ignorableWarning(LPDISPATCH oLocator, BSTR* strErrorMessage, long nErrorCode);
};
/////////////////////////////////////////////////////////////////////////////
// IVBSAXXMLFilter wrapper class

class IVBSAXXMLFilter : public COleDispatchDriver
{
public:
	IVBSAXXMLFilter() {}		// Calls COleDispatchDriver default constructor
	IVBSAXXMLFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVBSAXXMLFilter(const IVBSAXXMLFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParent();
	void SetRefParent(LPDISPATCH newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IVBSAXLexicalHandler wrapper class

class IVBSAXLexicalHandler : public COleDispatchDriver
{
public:
	IVBSAXLexicalHandler() {}		// Calls COleDispatchDriver default constructor
	IVBSAXLexicalHandler(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVBSAXLexicalHandler(const IVBSAXLexicalHandler& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void startDTD(BSTR* strName, BSTR* strPublicId, BSTR* strSystemId);
	void endDTD();
	void startEntity(BSTR* strName);
	void endEntity(BSTR* strName);
	void startCDATA();
	void endCDATA();
	void comment(BSTR* strChars);
};
/////////////////////////////////////////////////////////////////////////////
// IVBSAXDeclHandler wrapper class

class IVBSAXDeclHandler : public COleDispatchDriver
{
public:
	IVBSAXDeclHandler() {}		// Calls COleDispatchDriver default constructor
	IVBSAXDeclHandler(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVBSAXDeclHandler(const IVBSAXDeclHandler& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void elementDecl(BSTR* strName, BSTR* strModel);
	void attributeDecl(BSTR* strElementName, BSTR* strAttributeName, BSTR* strType, BSTR* strValueDefault, BSTR* strValue);
	void internalEntityDecl(BSTR* strName, BSTR* strValue);
	void externalEntityDecl(BSTR* strName, BSTR* strPublicId, BSTR* strSystemId);
};
/////////////////////////////////////////////////////////////////////////////
// IMXWriter wrapper class

class IMXWriter : public COleDispatchDriver
{
public:
	IMXWriter() {}		// Calls COleDispatchDriver default constructor
	IMXWriter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMXWriter(const IMXWriter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SetOutput(const VARIANT& newValue);
	VARIANT GetOutput();
	void SetEncoding(LPCTSTR lpszNewValue);
	CString GetEncoding();
	void SetByteOrderMark(BOOL bNewValue);
	BOOL GetByteOrderMark();
	void SetIndent(BOOL bNewValue);
	BOOL GetIndent();
	void SetStandalone(BOOL bNewValue);
	BOOL GetStandalone();
	void SetOmitXMLDeclaration(BOOL bNewValue);
	BOOL GetOmitXMLDeclaration();
	void SetVersion(LPCTSTR lpszNewValue);
	CString GetVersion();
	void SetDisableOutputEscaping(BOOL bNewValue);
	BOOL GetDisableOutputEscaping();
	void flush();
};
/////////////////////////////////////////////////////////////////////////////
// IMXAttributes wrapper class

class IMXAttributes : public COleDispatchDriver
{
public:
	IMXAttributes() {}		// Calls COleDispatchDriver default constructor
	IMXAttributes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMXAttributes(const IMXAttributes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void addAttribute(LPCTSTR strURI, LPCTSTR strLocalName, LPCTSTR strQName, LPCTSTR strType, LPCTSTR strValue);
	void addAttributeFromIndex(const VARIANT& varAtts, long nIndex);
	void clear();
	void removeAttribute(long nIndex);
	void setAttribute(long nIndex, LPCTSTR strURI, LPCTSTR strLocalName, LPCTSTR strQName, LPCTSTR strType, LPCTSTR strValue);
	void setAttributes(const VARIANT& varAtts);
	void setLocalName(long nIndex, LPCTSTR strLocalName);
	void setQName(long nIndex, LPCTSTR strQName);
	void setType(long nIndex, LPCTSTR strType);
	void setURI(long nIndex, LPCTSTR strURI);
	void setValue(long nIndex, LPCTSTR strValue);
};
/////////////////////////////////////////////////////////////////////////////
// IMXReaderControl wrapper class

class IMXReaderControl : public COleDispatchDriver
{
public:
	IMXReaderControl() {}		// Calls COleDispatchDriver default constructor
	IMXReaderControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMXReaderControl(const IMXReaderControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void abort();
	void resume();
	void suspend();
};
/////////////////////////////////////////////////////////////////////////////
// IMXSchemaDeclHandler wrapper class

class IMXSchemaDeclHandler : public COleDispatchDriver
{
public:
	IMXSchemaDeclHandler() {}		// Calls COleDispatchDriver default constructor
	IMXSchemaDeclHandler(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMXSchemaDeclHandler(const IMXSchemaDeclHandler& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void schemaElementDecl(LPDISPATCH oSchemaElement);
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaElement wrapper class

class ISchemaElement : public COleDispatchDriver
{
public:
	ISchemaElement() {}		// Calls COleDispatchDriver default constructor
	ISchemaElement(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaElement(const ISchemaElement& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
	VARIANT GetMinOccurs();
	VARIANT GetMaxOccurs();
	LPDISPATCH GetType();
	LPDISPATCH GetScope();
	CString GetDefaultValue();
	CString GetFixedValue();
	BOOL GetIsNillable();
	LPDISPATCH GetIdentityConstraints();
	LPDISPATCH GetSubstitutionGroup();
	long GetSubstitutionGroupExclusions();
	long GetDisallowedSubstitutions();
	BOOL GetIsAbstract();
	BOOL GetIsReference();
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaParticle wrapper class

class ISchemaParticle : public COleDispatchDriver
{
public:
	ISchemaParticle() {}		// Calls COleDispatchDriver default constructor
	ISchemaParticle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaParticle(const ISchemaParticle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
	VARIANT GetMinOccurs();
	VARIANT GetMaxOccurs();
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaItem wrapper class

class ISchemaItem : public COleDispatchDriver
{
public:
	ISchemaItem() {}		// Calls COleDispatchDriver default constructor
	ISchemaItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaItem(const ISchemaItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
};
/////////////////////////////////////////////////////////////////////////////
// ISchema wrapper class

class ISchema : public COleDispatchDriver
{
public:
	ISchema() {}		// Calls COleDispatchDriver default constructor
	ISchema(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchema(const ISchema& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
	CString GetTargetNamespace();
	CString GetVersion();
	LPDISPATCH GetTypes();
	LPDISPATCH GetElements();
	LPDISPATCH GetAttributes();
	LPDISPATCH GetAttributeGroups();
	LPDISPATCH GetModelGroups();
	LPDISPATCH GetNotations();
	LPDISPATCH GetSchemaLocations();
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaItemCollection wrapper class

class ISchemaItemCollection : public COleDispatchDriver
{
public:
	ISchemaItemCollection() {}		// Calls COleDispatchDriver default constructor
	ISchemaItemCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaItemCollection(const ISchemaItemCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetItem(long index);
	LPDISPATCH itemByName(LPCTSTR name);
	LPDISPATCH itemByQName(LPCTSTR name, LPCTSTR namespaceURI);
	long GetLength();
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaStringCollection wrapper class

class ISchemaStringCollection : public COleDispatchDriver
{
public:
	ISchemaStringCollection() {}		// Calls COleDispatchDriver default constructor
	ISchemaStringCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaStringCollection(const ISchemaStringCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetItem(long index);
	long GetLength();
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaType wrapper class

class ISchemaType : public COleDispatchDriver
{
public:
	ISchemaType() {}		// Calls COleDispatchDriver default constructor
	ISchemaType(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaType(const ISchemaType& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
	LPDISPATCH GetBaseTypes();
	long GetFinal();
	long GetVariety();
	long GetDerivedBy();
	BOOL isValid(LPCTSTR data);
	CString GetMinExclusive();
	CString GetMinInclusive();
	CString GetMaxExclusive();
	CString GetMaxInclusive();
	VARIANT GetTotalDigits();
	VARIANT GetFractionDigits();
	VARIANT GetLength();
	VARIANT GetMinLength();
	VARIANT GetMaxLength();
	LPDISPATCH GetEnumeration();
	long GetWhitespace();
	LPDISPATCH GetPatterns();
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaComplexType wrapper class

class ISchemaComplexType : public COleDispatchDriver
{
public:
	ISchemaComplexType() {}		// Calls COleDispatchDriver default constructor
	ISchemaComplexType(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaComplexType(const ISchemaComplexType& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
	LPDISPATCH GetBaseTypes();
	long GetFinal();
	long GetVariety();
	long GetDerivedBy();
	BOOL isValid(LPCTSTR data);
	CString GetMinExclusive();
	CString GetMinInclusive();
	CString GetMaxExclusive();
	CString GetMaxInclusive();
	VARIANT GetTotalDigits();
	VARIANT GetFractionDigits();
	VARIANT GetLength();
	VARIANT GetMinLength();
	VARIANT GetMaxLength();
	LPDISPATCH GetEnumeration();
	long GetWhitespace();
	LPDISPATCH GetPatterns();
	BOOL GetIsAbstract();
	LPDISPATCH GetAnyAttribute();
	LPDISPATCH GetAttributes();
	long GetContentType();
	LPDISPATCH GetContentModel();
	long GetProhibitedSubstitutions();
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaAny wrapper class

class ISchemaAny : public COleDispatchDriver
{
public:
	ISchemaAny() {}		// Calls COleDispatchDriver default constructor
	ISchemaAny(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaAny(const ISchemaAny& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
	VARIANT GetMinOccurs();
	VARIANT GetMaxOccurs();
	LPDISPATCH GetNamespaces();
	long GetProcessContents();
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaModelGroup wrapper class

class ISchemaModelGroup : public COleDispatchDriver
{
public:
	ISchemaModelGroup() {}		// Calls COleDispatchDriver default constructor
	ISchemaModelGroup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaModelGroup(const ISchemaModelGroup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
	VARIANT GetMinOccurs();
	VARIANT GetMaxOccurs();
	LPDISPATCH GetParticles();
};
/////////////////////////////////////////////////////////////////////////////
// IMXXMLFilter wrapper class

class IMXXMLFilter : public COleDispatchDriver
{
public:
	IMXXMLFilter() {}		// Calls COleDispatchDriver default constructor
	IMXXMLFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMXXMLFilter(const IMXXMLFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL getFeature(LPCTSTR strName);
	void putFeature(LPCTSTR strName, BOOL fValue);
	VARIANT getProperty(LPCTSTR strName);
	void putProperty(LPCTSTR strName, const VARIANT& varValue);
	LPUNKNOWN GetEntityResolver();
	void SetRefEntityResolver(LPUNKNOWN newValue);
	LPUNKNOWN GetContentHandler();
	void SetRefContentHandler(LPUNKNOWN newValue);
	LPUNKNOWN GetDtdHandler();
	void SetRefDtdHandler(LPUNKNOWN newValue);
	LPUNKNOWN GetErrorHandler();
	void SetRefErrorHandler(LPUNKNOWN newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMSchemaCollection2 wrapper class

class IXMLDOMSchemaCollection2 : public COleDispatchDriver
{
public:
	IXMLDOMSchemaCollection2() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMSchemaCollection2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMSchemaCollection2(const IXMLDOMSchemaCollection2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void add(LPCTSTR namespaceURI, const VARIANT& var);
	LPDISPATCH get(LPCTSTR namespaceURI);
	void remove(LPCTSTR namespaceURI);
	long GetLength();
	CString GetNamespaceURI(long index);
	void addCollection(LPDISPATCH otherCollection);
	void validate();
	void SetValidateOnLoad(BOOL bNewValue);
	BOOL GetValidateOnLoad();
	LPDISPATCH getSchema(LPCTSTR namespaceURI);
	LPDISPATCH getDeclaration(LPDISPATCH node);
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaAttribute wrapper class

class ISchemaAttribute : public COleDispatchDriver
{
public:
	ISchemaAttribute() {}		// Calls COleDispatchDriver default constructor
	ISchemaAttribute(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaAttribute(const ISchemaAttribute& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
	LPDISPATCH GetType();
	LPDISPATCH GetScope();
	CString GetDefaultValue();
	CString GetFixedValue();
	long GetUse();
	BOOL GetIsReference();
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaAttributeGroup wrapper class

class ISchemaAttributeGroup : public COleDispatchDriver
{
public:
	ISchemaAttributeGroup() {}		// Calls COleDispatchDriver default constructor
	ISchemaAttributeGroup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaAttributeGroup(const ISchemaAttributeGroup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
	LPDISPATCH GetAnyAttribute();
	LPDISPATCH GetAttributes();
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaIdentityConstraint wrapper class

class ISchemaIdentityConstraint : public COleDispatchDriver
{
public:
	ISchemaIdentityConstraint() {}		// Calls COleDispatchDriver default constructor
	ISchemaIdentityConstraint(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaIdentityConstraint(const ISchemaIdentityConstraint& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
	CString GetSelector();
	LPDISPATCH GetFields();
	LPDISPATCH GetReferencedKey();
};
/////////////////////////////////////////////////////////////////////////////
// ISchemaNotation wrapper class

class ISchemaNotation : public COleDispatchDriver
{
public:
	ISchemaNotation() {}		// Calls COleDispatchDriver default constructor
	ISchemaNotation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISchemaNotation(const ISchemaNotation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetNamespaceURI();
	LPDISPATCH GetSchema();
	CString GetId();
	long GetItemType();
	LPDISPATCH GetUnhandledAttributes();
	BOOL writeAnnotation(LPUNKNOWN annotationSink);
	CString GetSystemIdentifier();
	CString GetPublicIdentifier();
};
/////////////////////////////////////////////////////////////////////////////
// IXMLDOMSelection wrapper class

class IXMLDOMSelection : public COleDispatchDriver
{
public:
	IXMLDOMSelection() {}		// Calls COleDispatchDriver default constructor
	IXMLDOMSelection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLDOMSelection(const IXMLDOMSelection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetItem(long index);
	long GetLength();
	LPDISPATCH nextNode();
	void reset();
	CString GetExpr();
	void SetExpr(LPCTSTR lpszNewValue);
	LPDISPATCH GetContext();
	void SetRefContext(LPDISPATCH newValue);
	LPDISPATCH peekNode();
	LPDISPATCH matches(LPDISPATCH pNode);
	LPDISPATCH removeNext();
	void removeAll();
	LPDISPATCH clone();
	VARIANT getProperty(LPCTSTR name);
	void setProperty(LPCTSTR name, const VARIANT& value);
};
/////////////////////////////////////////////////////////////////////////////
// XMLDOMDocumentEvents wrapper class

class XMLDOMDocumentEvents : public COleDispatchDriver
{
public:
	XMLDOMDocumentEvents() {}		// Calls COleDispatchDriver default constructor
	XMLDOMDocumentEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	XMLDOMDocumentEvents(const XMLDOMDocumentEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	// method 'ondataavailable' not emitted because of invalid return type or parameter type
	// method 'onreadystatechange' not emitted because of invalid return type or parameter type
};
/////////////////////////////////////////////////////////////////////////////
// IDSOControl wrapper class

class IDSOControl : public COleDispatchDriver
{
public:
	IDSOControl() {}		// Calls COleDispatchDriver default constructor
	IDSOControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IDSOControl(const IDSOControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetXMLDocument();
	void SetXMLDocument(LPDISPATCH newValue);
	long GetJavaDSOCompatible();
	void SetJavaDSOCompatible(long nNewValue);
	long GetReadyState();
};
/////////////////////////////////////////////////////////////////////////////
// IXMLHTTPRequest wrapper class

class IXMLHTTPRequest : public COleDispatchDriver
{
public:
	IXMLHTTPRequest() {}		// Calls COleDispatchDriver default constructor
	IXMLHTTPRequest(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXMLHTTPRequest(const IXMLHTTPRequest& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void open(LPCTSTR bstrMethod, LPCTSTR bstrUrl, const VARIANT& varAsync, const VARIANT& bstrUser, const VARIANT& bstrPassword);
	void setRequestHeader(LPCTSTR bstrHeader, LPCTSTR bstrValue);
	CString getResponseHeader(LPCTSTR bstrHeader);
	CString getAllResponseHeaders();
	void send(const VARIANT& varBody);
	void abort();
	long GetStatus();
	CString GetStatusText();
	LPDISPATCH GetResponseXML();
	CString GetResponseText();
	VARIANT GetResponseBody();
	VARIANT GetResponseStream();
	long GetReadyState();
	void SetOnreadystatechange(LPDISPATCH newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IServerXMLHTTPRequest wrapper class

class IServerXMLHTTPRequest : public COleDispatchDriver
{
public:
	IServerXMLHTTPRequest() {}		// Calls COleDispatchDriver default constructor
	IServerXMLHTTPRequest(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IServerXMLHTTPRequest(const IServerXMLHTTPRequest& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void open(LPCTSTR bstrMethod, LPCTSTR bstrUrl, const VARIANT& varAsync, const VARIANT& bstrUser, const VARIANT& bstrPassword);
	void setRequestHeader(LPCTSTR bstrHeader, LPCTSTR bstrValue);
	CString getResponseHeader(LPCTSTR bstrHeader);
	CString getAllResponseHeaders();
	void send(const VARIANT& varBody);
	void abort();
	long GetStatus();
	CString GetStatusText();
	LPDISPATCH GetResponseXML();
	CString GetResponseText();
	VARIANT GetResponseBody();
	VARIANT GetResponseStream();
	long GetReadyState();
	void SetOnreadystatechange(LPDISPATCH newValue);
	void setTimeouts(long resolveTimeout, long connectTimeout, long sendTimeout, long receiveTimeout);
	BOOL waitForResponse(const VARIANT& timeoutInSeconds);
	VARIANT getOption(long option);
	void setOption(long option, const VARIANT& value);
};
/////////////////////////////////////////////////////////////////////////////
// IServerXMLHTTPRequest2 wrapper class

class IServerXMLHTTPRequest2 : public COleDispatchDriver
{
public:
	IServerXMLHTTPRequest2() {}		// Calls COleDispatchDriver default constructor
	IServerXMLHTTPRequest2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IServerXMLHTTPRequest2(const IServerXMLHTTPRequest2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void open(LPCTSTR bstrMethod, LPCTSTR bstrUrl, const VARIANT& varAsync, const VARIANT& bstrUser, const VARIANT& bstrPassword);
	void setRequestHeader(LPCTSTR bstrHeader, LPCTSTR bstrValue);
	CString getResponseHeader(LPCTSTR bstrHeader);
	CString getAllResponseHeaders();
	void send(const VARIANT& varBody);
	void abort();
	long GetStatus();
	CString GetStatusText();
	LPDISPATCH GetResponseXML();
	CString GetResponseText();
	VARIANT GetResponseBody();
	VARIANT GetResponseStream();
	long GetReadyState();
	void SetOnreadystatechange(LPDISPATCH newValue);
	void setTimeouts(long resolveTimeout, long connectTimeout, long sendTimeout, long receiveTimeout);
	BOOL waitForResponse(const VARIANT& timeoutInSeconds);
	VARIANT getOption(long option);
	void setOption(long option, const VARIANT& value);
	void setProxy(long proxySetting, const VARIANT& varProxyServer, const VARIANT& varBypassList);
	void setProxyCredentials(LPCTSTR bstrUserName, LPCTSTR bstrPassword);
};
/////////////////////////////////////////////////////////////////////////////
// IMXNamespacePrefixes wrapper class

class IMXNamespacePrefixes : public COleDispatchDriver
{
public:
	IMXNamespacePrefixes() {}		// Calls COleDispatchDriver default constructor
	IMXNamespacePrefixes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMXNamespacePrefixes(const IMXNamespacePrefixes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetItem(long index);
	long GetLength();
};
/////////////////////////////////////////////////////////////////////////////
// IVBMXNamespaceManager wrapper class

class IVBMXNamespaceManager : public COleDispatchDriver
{
public:
	IVBMXNamespaceManager() {}		// Calls COleDispatchDriver default constructor
	IVBMXNamespaceManager(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVBMXNamespaceManager(const IVBMXNamespaceManager& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SetAllowOverride(BOOL bNewValue);
	BOOL GetAllowOverride();
	void reset();
	void pushContext();
	void pushNodeContext(LPDISPATCH contextNode, BOOL fDeep);
	void popContext();
	void declarePrefix(LPCTSTR prefix, LPCTSTR namespaceURI);
	LPDISPATCH getDeclaredPrefixes();
	LPDISPATCH getPrefixes(LPCTSTR namespaceURI);
	VARIANT getURI(LPCTSTR prefix);
	VARIANT getURIFromNode(LPCTSTR strPrefix, LPDISPATCH contextNode);
};
