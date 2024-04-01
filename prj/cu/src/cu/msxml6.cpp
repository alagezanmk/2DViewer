// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "msxml6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IXMLDOMImplementation properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMImplementation operations

BOOL IXMLDOMImplementation::hasFeature(LPCTSTR feature, LPCTSTR version)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x91, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		feature, version);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNode properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNode operations

CString IXMLDOMNode::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMNode::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMNode::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMNode::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNode::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNode::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNode::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNode::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNode::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNode::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNode::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNode::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMNode::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMNode::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMNode::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMNode::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNode::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNode::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMNode::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMNode::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMNode::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMNode::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNode::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMNode::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMNode::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMNode::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMNode::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMNode::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMNode::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMNode::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMNode::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMNode::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMNode::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMNode::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMNode::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMNode::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNodeList properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNodeList operations

LPDISPATCH IXMLDOMNodeList::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long IXMLDOMNodeList::GetLength()
{
	long result;
	InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNodeList::nextNode()
{
	LPDISPATCH result;
	InvokeHelper(0x4c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXMLDOMNodeList::reset()
{
	InvokeHelper(0x4d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNamedNodeMap properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNamedNodeMap operations

LPDISPATCH IXMLDOMNamedNodeMap::getNamedItem(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x53, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH IXMLDOMNamedNodeMap::setNamedItem(LPDISPATCH newItem)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x54, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newItem);
	return result;
}

LPDISPATCH IXMLDOMNamedNodeMap::removeNamedItem(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x55, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH IXMLDOMNamedNodeMap::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long IXMLDOMNamedNodeMap::GetLength()
{
	long result;
	InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNamedNodeMap::getQualifiedItem(LPCTSTR baseName, LPCTSTR namespaceURI)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x57, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		baseName, namespaceURI);
	return result;
}

LPDISPATCH IXMLDOMNamedNodeMap::removeQualifiedItem(LPCTSTR baseName, LPCTSTR namespaceURI)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x58, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		baseName, namespaceURI);
	return result;
}

LPDISPATCH IXMLDOMNamedNodeMap::nextNode()
{
	LPDISPATCH result;
	InvokeHelper(0x59, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXMLDOMNamedNodeMap::reset()
{
	InvokeHelper(0x5a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocument properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocument operations

CString IXMLDOMDocument::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocument::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMDocument::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMDocument::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMDocument::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMDocument::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMDocument::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMDocument::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMDocument::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocument::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMDocument::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMDocument::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMDocument::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMDocument::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMDocument::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

LPDISPATCH IXMLDOMDocument::GetDoctype()
{
	LPDISPATCH result;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetImplementation()
{
	LPDISPATCH result;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetDocumentElement()
{
	LPDISPATCH result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument::SetRefDocumentElement(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x28, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IXMLDOMDocument::createElement(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

LPDISPATCH IXMLDOMDocument::createDocumentFragment()
{
	LPDISPATCH result;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::createTextNode(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH IXMLDOMDocument::createComment(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH IXMLDOMDocument::createCDATASection(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH IXMLDOMDocument::createProcessingInstruction(LPCTSTR target, LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		target, data);
	return result;
}

LPDISPATCH IXMLDOMDocument::createAttribute(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH IXMLDOMDocument::createEntityReference(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH IXMLDOMDocument::getElementsByTagName(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

LPDISPATCH IXMLDOMDocument::createNode(const VARIANT& type, LPCTSTR name, LPCTSTR namespaceURI)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_BSTR;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&type, name, namespaceURI);
	return result;
}

LPDISPATCH IXMLDOMDocument::nodeFromID(LPCTSTR idString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x38, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		idString);
	return result;
}

BOOL IXMLDOMDocument::load(const VARIANT& xmlSource)
{
	BOOL result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		&xmlSource);
	return result;
}

long IXMLDOMDocument::GetReadyState()
{
	long result;
	InvokeHelper(DISPID_READYSTATE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument::GetParseError()
{
	LPDISPATCH result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument::GetUrl()
{
	CString result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IXMLDOMDocument::GetAsync()
{
	BOOL result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument::SetAsync(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IXMLDOMDocument::abort()
{
	InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IXMLDOMDocument::loadXML(LPCTSTR bstrXML)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bstrXML);
	return result;
}

void IXMLDOMDocument::save(const VARIANT& destination)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &destination);
}

BOOL IXMLDOMDocument::GetValidateOnParse()
{
	BOOL result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument::SetValidateOnParse(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IXMLDOMDocument::GetResolveExternals()
{
	BOOL result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument::SetResolveExternals(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IXMLDOMDocument::GetPreserveWhiteSpace()
{
	BOOL result;
	InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument::SetPreserveWhiteSpace(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x43, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IXMLDOMDocument::SetOnreadystatechange(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x44, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IXMLDOMDocument::SetOndataavailable(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IXMLDOMDocument::SetOntransformnode(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocumentType properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocumentType operations

CString IXMLDOMDocumentType::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocumentType::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocumentType::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMDocumentType::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMDocumentType::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMDocumentType::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocumentType::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocumentType::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMDocumentType::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocumentType::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocumentType::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMDocumentType::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocumentType::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMDocumentType::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocumentType::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMDocumentType::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocumentType::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocumentType::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocumentType::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocumentType::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

CString IXMLDOMDocumentType::GetName()
{
	CString result;
	InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::GetEntities()
{
	LPDISPATCH result;
	InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentType::GetNotations()
{
	LPDISPATCH result;
	InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMElement properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMElement operations

CString IXMLDOMElement::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMElement::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMElement::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMElement::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMElement::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMElement::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMElement::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMElement::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMElement::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMElement::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMElement::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMElement::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMElement::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMElement::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMElement::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMElement::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMElement::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMElement::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMElement::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMElement::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMElement::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMElement::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMElement::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMElement::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMElement::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMElement::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMElement::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMElement::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMElement::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMElement::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMElement::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMElement::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMElement::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMElement::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMElement::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMElement::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

CString IXMLDOMElement::GetTagName()
{
	CString result;
	InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMElement::getAttribute(LPCTSTR name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x63, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		name);
	return result;
}

void IXMLDOMElement::setAttribute(LPCTSTR name, const VARIANT& value)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 name, &value);
}

void IXMLDOMElement::removeAttribute(LPCTSTR name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 name);
}

LPDISPATCH IXMLDOMElement::getAttributeNode(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH IXMLDOMElement::setAttributeNode(LPDISPATCH DOMAttribute)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x67, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DOMAttribute);
	return result;
}

LPDISPATCH IXMLDOMElement::removeAttributeNode(LPDISPATCH DOMAttribute)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DOMAttribute);
	return result;
}

LPDISPATCH IXMLDOMElement::getElementsByTagName(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

void IXMLDOMElement::normalize()
{
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMAttribute properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMAttribute operations

CString IXMLDOMAttribute::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMAttribute::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMAttribute::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMAttribute::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMAttribute::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMAttribute::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMAttribute::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMAttribute::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMAttribute::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMAttribute::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMAttribute::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMAttribute::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMAttribute::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMAttribute::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMAttribute::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMAttribute::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMAttribute::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMAttribute::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMAttribute::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMAttribute::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMAttribute::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMAttribute::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMAttribute::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMAttribute::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMAttribute::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMAttribute::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMAttribute::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMAttribute::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMAttribute::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMAttribute::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMAttribute::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMAttribute::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMAttribute::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMAttribute::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMAttribute::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMAttribute::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

CString IXMLDOMAttribute::GetName()
{
	CString result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMAttribute::GetValue()
{
	VARIANT result;
	InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMAttribute::SetValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x78, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocumentFragment properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocumentFragment operations

CString IXMLDOMDocumentFragment::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocumentFragment::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocumentFragment::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMDocumentFragment::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMDocumentFragment::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMDocumentFragment::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocumentFragment::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocumentFragment::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMDocumentFragment::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocumentFragment::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocumentFragment::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMDocumentFragment::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocumentFragment::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMDocumentFragment::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocumentFragment::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMDocumentFragment::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMDocumentFragment::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocumentFragment::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocumentFragment::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocumentFragment::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocumentFragment::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMText properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMText operations

CString IXMLDOMText::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMText::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMText::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMText::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMText::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMText::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMText::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMText::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMText::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMText::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMText::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMText::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMText::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMText::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMText::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMText::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMText::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMText::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMText::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMText::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMText::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMText::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMText::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMText::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMText::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMText::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMText::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMText::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMText::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMText::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMText::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMText::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMText::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMText::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMText::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMText::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

CString IXMLDOMText::GetData()
{
	CString result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMText::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IXMLDOMText::GetLength()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IXMLDOMText::substringData(long offset, long count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		offset, count);
	return result;
}

void IXMLDOMText::appendData(LPCTSTR data)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 data);
}

void IXMLDOMText::insertData(long offset, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, data);
}

void IXMLDOMText::deleteData(long offset, long count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x72, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count);
}

void IXMLDOMText::replaceData(long offset, long count, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count, data);
}

LPDISPATCH IXMLDOMText::splitText(long offset)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		offset);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMCharacterData properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMCharacterData operations

CString IXMLDOMCharacterData::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMCharacterData::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMCharacterData::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMCharacterData::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMCharacterData::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMCharacterData::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCharacterData::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMCharacterData::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMCharacterData::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMCharacterData::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMCharacterData::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMCharacterData::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMCharacterData::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMCharacterData::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCharacterData::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMCharacterData::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMCharacterData::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCharacterData::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCharacterData::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCharacterData::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMCharacterData::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

CString IXMLDOMCharacterData::GetData()
{
	CString result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMCharacterData::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IXMLDOMCharacterData::GetLength()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCharacterData::substringData(long offset, long count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		offset, count);
	return result;
}

void IXMLDOMCharacterData::appendData(LPCTSTR data)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 data);
}

void IXMLDOMCharacterData::insertData(long offset, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, data);
}

void IXMLDOMCharacterData::deleteData(long offset, long count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x72, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count);
}

void IXMLDOMCharacterData::replaceData(long offset, long count, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count, data);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMComment properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMComment operations

CString IXMLDOMComment::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMComment::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMComment::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMComment::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMComment::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMComment::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMComment::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMComment::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMComment::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMComment::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMComment::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMComment::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMComment::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMComment::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMComment::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMComment::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMComment::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMComment::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMComment::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMComment::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMComment::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMComment::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMComment::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMComment::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMComment::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMComment::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMComment::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMComment::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMComment::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMComment::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMComment::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMComment::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMComment::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMComment::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMComment::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMComment::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

CString IXMLDOMComment::GetData()
{
	CString result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMComment::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IXMLDOMComment::GetLength()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IXMLDOMComment::substringData(long offset, long count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		offset, count);
	return result;
}

void IXMLDOMComment::appendData(LPCTSTR data)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 data);
}

void IXMLDOMComment::insertData(long offset, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, data);
}

void IXMLDOMComment::deleteData(long offset, long count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x72, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count);
}

void IXMLDOMComment::replaceData(long offset, long count, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count, data);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMCDATASection properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMCDATASection operations

CString IXMLDOMCDATASection::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMCDATASection::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMCDATASection::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMCDATASection::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMCDATASection::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMCDATASection::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCDATASection::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMCDATASection::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMCDATASection::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMCDATASection::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMCDATASection::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMCDATASection::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMCDATASection::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMCDATASection::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCDATASection::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMCDATASection::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMCDATASection::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCDATASection::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCDATASection::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCDATASection::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMCDATASection::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

CString IXMLDOMCDATASection::GetData()
{
	CString result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMCDATASection::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IXMLDOMCDATASection::GetLength()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IXMLDOMCDATASection::substringData(long offset, long count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		offset, count);
	return result;
}

void IXMLDOMCDATASection::appendData(LPCTSTR data)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 data);
}

void IXMLDOMCDATASection::insertData(long offset, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, data);
}

void IXMLDOMCDATASection::deleteData(long offset, long count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x72, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count);
}

void IXMLDOMCDATASection::replaceData(long offset, long count, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count, data);
}

LPDISPATCH IXMLDOMCDATASection::splitText(long offset)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		offset);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMProcessingInstruction properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMProcessingInstruction operations

CString IXMLDOMProcessingInstruction::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMProcessingInstruction::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMProcessingInstruction::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMProcessingInstruction::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMProcessingInstruction::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMProcessingInstruction::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMProcessingInstruction::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMProcessingInstruction::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMProcessingInstruction::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMProcessingInstruction::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMProcessingInstruction::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMProcessingInstruction::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMProcessingInstruction::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMProcessingInstruction::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMProcessingInstruction::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMProcessingInstruction::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMProcessingInstruction::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMProcessingInstruction::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMProcessingInstruction::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMProcessingInstruction::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMProcessingInstruction::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

CString IXMLDOMProcessingInstruction::GetTarget()
{
	CString result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMProcessingInstruction::GetData()
{
	CString result;
	InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMProcessingInstruction::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMEntityReference properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMEntityReference operations

CString IXMLDOMEntityReference::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMEntityReference::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMEntityReference::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMEntityReference::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMEntityReference::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMEntityReference::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMEntityReference::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMEntityReference::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMEntityReference::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMEntityReference::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMEntityReference::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMEntityReference::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMEntityReference::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMEntityReference::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMEntityReference::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMEntityReference::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMEntityReference::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMEntityReference::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMEntityReference::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMEntityReference::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMEntityReference::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMParseError properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMParseError operations

long IXMLDOMParseError::GetErrorCode()
{
	long result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IXMLDOMParseError::GetUrl()
{
	CString result;
	InvokeHelper(0xb3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMParseError::GetReason()
{
	CString result;
	InvokeHelper(0xb4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMParseError::GetSrcText()
{
	CString result;
	InvokeHelper(0xb5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IXMLDOMParseError::GetLine()
{
	long result;
	InvokeHelper(0xb6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IXMLDOMParseError::GetLinepos()
{
	long result;
	InvokeHelper(0xb7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IXMLDOMParseError::GetFilepos()
{
	long result;
	InvokeHelper(0xb8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocument2 properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocument2 operations

CString IXMLDOMDocument2::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocument2::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMDocument2::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMDocument2::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMDocument2::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMDocument2::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMDocument2::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMDocument2::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument2::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMDocument2::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocument2::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMDocument2::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMDocument2::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument2::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMDocument2::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMDocument2::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMDocument2::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument2::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument2::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument2::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

LPDISPATCH IXMLDOMDocument2::GetDoctype()
{
	LPDISPATCH result;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetImplementation()
{
	LPDISPATCH result;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetDocumentElement()
{
	LPDISPATCH result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::SetRefDocumentElement(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x28, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IXMLDOMDocument2::createElement(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

LPDISPATCH IXMLDOMDocument2::createDocumentFragment()
{
	LPDISPATCH result;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::createTextNode(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH IXMLDOMDocument2::createComment(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH IXMLDOMDocument2::createCDATASection(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH IXMLDOMDocument2::createProcessingInstruction(LPCTSTR target, LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		target, data);
	return result;
}

LPDISPATCH IXMLDOMDocument2::createAttribute(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH IXMLDOMDocument2::createEntityReference(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH IXMLDOMDocument2::getElementsByTagName(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

LPDISPATCH IXMLDOMDocument2::createNode(const VARIANT& type, LPCTSTR name, LPCTSTR namespaceURI)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_BSTR;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&type, name, namespaceURI);
	return result;
}

LPDISPATCH IXMLDOMDocument2::nodeFromID(LPCTSTR idString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x38, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		idString);
	return result;
}

BOOL IXMLDOMDocument2::load(const VARIANT& xmlSource)
{
	BOOL result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		&xmlSource);
	return result;
}

long IXMLDOMDocument2::GetReadyState()
{
	long result;
	InvokeHelper(DISPID_READYSTATE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument2::GetParseError()
{
	LPDISPATCH result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument2::GetUrl()
{
	CString result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IXMLDOMDocument2::GetAsync()
{
	BOOL result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::SetAsync(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IXMLDOMDocument2::abort()
{
	InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IXMLDOMDocument2::loadXML(LPCTSTR bstrXML)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bstrXML);
	return result;
}

void IXMLDOMDocument2::save(const VARIANT& destination)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &destination);
}

BOOL IXMLDOMDocument2::GetValidateOnParse()
{
	BOOL result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::SetValidateOnParse(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IXMLDOMDocument2::GetResolveExternals()
{
	BOOL result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::SetResolveExternals(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IXMLDOMDocument2::GetPreserveWhiteSpace()
{
	BOOL result;
	InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::SetPreserveWhiteSpace(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x43, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IXMLDOMDocument2::SetOnreadystatechange(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x44, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IXMLDOMDocument2::SetOndataavailable(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IXMLDOMDocument2::SetOntransformnode(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH IXMLDOMDocument2::GetNamespaces()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocument2::GetSchemas()
{
	VARIANT result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::SetRefSchemas(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xca, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH IXMLDOMDocument2::validate()
{
	LPDISPATCH result;
	InvokeHelper(0xcb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument2::setProperty(LPCTSTR name, const VARIANT& value)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 name, &value);
}

VARIANT IXMLDOMDocument2::getProperty(LPCTSTR name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMSchemaCollection properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMSchemaCollection operations

void IXMLDOMSchemaCollection::add(LPCTSTR namespaceURI, const VARIANT& var)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 namespaceURI, &var);
}

LPDISPATCH IXMLDOMSchemaCollection::get(LPCTSTR namespaceURI)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceURI);
	return result;
}

void IXMLDOMSchemaCollection::remove(LPCTSTR namespaceURI)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 namespaceURI);
}

long IXMLDOMSchemaCollection::GetLength()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IXMLDOMSchemaCollection::GetNamespaceURI(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

void IXMLDOMSchemaCollection::addCollection(LPDISPATCH otherCollection)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 otherCollection);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocument3 properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMDocument3 operations

CString IXMLDOMDocument3::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocument3::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMDocument3::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMDocument3::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMDocument3::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMDocument3::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMDocument3::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMDocument3::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument3::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMDocument3::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocument3::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMDocument3::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMDocument3::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument3::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMDocument3::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMDocument3::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMDocument3::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument3::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument3::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument3::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

LPDISPATCH IXMLDOMDocument3::GetDoctype()
{
	LPDISPATCH result;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetImplementation()
{
	LPDISPATCH result;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetDocumentElement()
{
	LPDISPATCH result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::SetRefDocumentElement(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x28, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IXMLDOMDocument3::createElement(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

LPDISPATCH IXMLDOMDocument3::createDocumentFragment()
{
	LPDISPATCH result;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::createTextNode(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH IXMLDOMDocument3::createComment(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH IXMLDOMDocument3::createCDATASection(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH IXMLDOMDocument3::createProcessingInstruction(LPCTSTR target, LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		target, data);
	return result;
}

LPDISPATCH IXMLDOMDocument3::createAttribute(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH IXMLDOMDocument3::createEntityReference(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH IXMLDOMDocument3::getElementsByTagName(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

LPDISPATCH IXMLDOMDocument3::createNode(const VARIANT& type, LPCTSTR name, LPCTSTR namespaceURI)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_BSTR;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&type, name, namespaceURI);
	return result;
}

LPDISPATCH IXMLDOMDocument3::nodeFromID(LPCTSTR idString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x38, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		idString);
	return result;
}

BOOL IXMLDOMDocument3::load(const VARIANT& xmlSource)
{
	BOOL result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		&xmlSource);
	return result;
}

long IXMLDOMDocument3::GetReadyState()
{
	long result;
	InvokeHelper(DISPID_READYSTATE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMDocument3::GetParseError()
{
	LPDISPATCH result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IXMLDOMDocument3::GetUrl()
{
	CString result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IXMLDOMDocument3::GetAsync()
{
	BOOL result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::SetAsync(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IXMLDOMDocument3::abort()
{
	InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IXMLDOMDocument3::loadXML(LPCTSTR bstrXML)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bstrXML);
	return result;
}

void IXMLDOMDocument3::save(const VARIANT& destination)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &destination);
}

BOOL IXMLDOMDocument3::GetValidateOnParse()
{
	BOOL result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::SetValidateOnParse(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IXMLDOMDocument3::GetResolveExternals()
{
	BOOL result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::SetResolveExternals(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IXMLDOMDocument3::GetPreserveWhiteSpace()
{
	BOOL result;
	InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::SetPreserveWhiteSpace(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x43, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IXMLDOMDocument3::SetOnreadystatechange(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x44, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IXMLDOMDocument3::SetOndataavailable(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IXMLDOMDocument3::SetOntransformnode(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH IXMLDOMDocument3::GetNamespaces()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMDocument3::GetSchemas()
{
	VARIANT result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::SetRefSchemas(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xca, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH IXMLDOMDocument3::validate()
{
	LPDISPATCH result;
	InvokeHelper(0xcb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXMLDOMDocument3::setProperty(LPCTSTR name, const VARIANT& value)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 name, &value);
}

VARIANT IXMLDOMDocument3::getProperty(LPCTSTR name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH IXMLDOMDocument3::validateNode(LPDISPATCH node)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		node);
	return result;
}

LPDISPATCH IXMLDOMDocument3::importNode(LPDISPATCH node, BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0xd1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		node, deep);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNotation properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMNotation operations

CString IXMLDOMNotation::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMNotation::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMNotation::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMNotation::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNotation::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNotation::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNotation::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNotation::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNotation::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNotation::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNotation::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNotation::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMNotation::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMNotation::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMNotation::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMNotation::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNotation::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNotation::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMNotation::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMNotation::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMNotation::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMNotation::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMNotation::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMNotation::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMNotation::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMNotation::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMNotation::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMNotation::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMNotation::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMNotation::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMNotation::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMNotation::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMNotation::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMNotation::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMNotation::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMNotation::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

VARIANT IXMLDOMNotation::GetPublicId()
{
	VARIANT result;
	InvokeHelper(0x88, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMNotation::GetSystemId()
{
	VARIANT result;
	InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMEntity properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMEntity operations

CString IXMLDOMEntity::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMEntity::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMEntity::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXMLDOMEntity::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntity::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntity::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntity::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntity::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntity::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntity::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntity::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntity::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXMLDOMEntity::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXMLDOMEntity::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXMLDOMEntity::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXMLDOMEntity::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntity::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntity::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXMLDOMEntity::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMEntity::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMEntity::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXMLDOMEntity::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMEntity::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMEntity::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMEntity::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXMLDOMEntity::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXMLDOMEntity::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXMLDOMEntity::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMEntity::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXMLDOMEntity::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXMLDOMEntity::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXMLDOMEntity::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXMLDOMEntity::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMEntity::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMEntity::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMEntity::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

VARIANT IXMLDOMEntity::GetPublicId()
{
	VARIANT result;
	InvokeHelper(0x8c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMEntity::GetSystemId()
{
	VARIANT result;
	InvokeHelper(0x8d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

CString IXMLDOMEntity::GetNotationName()
{
	CString result;
	InvokeHelper(0x8e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMParseError2 properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMParseError2 operations

long IXMLDOMParseError2::GetErrorCode()
{
	long result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IXMLDOMParseError2::GetUrl()
{
	CString result;
	InvokeHelper(0xb3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMParseError2::GetReason()
{
	CString result;
	InvokeHelper(0xb4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXMLDOMParseError2::GetSrcText()
{
	CString result;
	InvokeHelper(0xb5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IXMLDOMParseError2::GetLine()
{
	long result;
	InvokeHelper(0xb6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IXMLDOMParseError2::GetLinepos()
{
	long result;
	InvokeHelper(0xb7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IXMLDOMParseError2::GetFilepos()
{
	long result;
	InvokeHelper(0xb8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IXMLDOMParseError2::GetErrorXPath()
{
	CString result;
	InvokeHelper(0xbe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMParseError2::GetAllErrors()
{
	LPDISPATCH result;
	InvokeHelper(0xbb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IXMLDOMParseError2::errorParameters(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xbc, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

long IXMLDOMParseError2::GetErrorParametersCount()
{
	long result;
	InvokeHelper(0xbd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMParseErrorCollection properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMParseErrorCollection operations

LPDISPATCH IXMLDOMParseErrorCollection::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long IXMLDOMParseErrorCollection::GetLength()
{
	long result;
	InvokeHelper(0xc1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMParseErrorCollection::GetNext()
{
	LPDISPATCH result;
	InvokeHelper(0xc2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXMLDOMParseErrorCollection::reset()
{
	InvokeHelper(0xc3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IXTLRuntime properties

/////////////////////////////////////////////////////////////////////////////
// IXTLRuntime operations

CString IXTLRuntime::GetNodeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXTLRuntime::GetNodeValue()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXTLRuntime::SetNodeValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IXTLRuntime::GetNodeType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXTLRuntime::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXTLRuntime::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXTLRuntime::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXTLRuntime::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXTLRuntime::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXTLRuntime::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXTLRuntime::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXTLRuntime::insertBefore(LPDISPATCH newChild, const VARIANT& refChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, &refChild);
	return result;
}

LPDISPATCH IXTLRuntime::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH IXTLRuntime::removeChild(LPDISPATCH childNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		childNode);
	return result;
}

LPDISPATCH IXTLRuntime::appendChild(LPDISPATCH newChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild);
	return result;
}

BOOL IXTLRuntime::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXTLRuntime::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXTLRuntime::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString IXTLRuntime::GetNodeTypeString()
{
	CString result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXTLRuntime::GetText()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXTLRuntime::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IXTLRuntime::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXTLRuntime::GetDefinition()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXTLRuntime::GetNodeTypedValue()
{
	VARIANT result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXTLRuntime::SetNodeTypedValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXTLRuntime::GetDataType()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IXTLRuntime::SetDataType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IXTLRuntime::GetXml()
{
	CString result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXTLRuntime::transformNode(LPDISPATCH stylesheet)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		stylesheet);
	return result;
}

LPDISPATCH IXTLRuntime::selectNodes(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

LPDISPATCH IXTLRuntime::selectSingleNode(LPCTSTR queryString)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		queryString);
	return result;
}

BOOL IXTLRuntime::GetParsed()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IXTLRuntime::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXTLRuntime::GetPrefix()
{
	CString result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXTLRuntime::GetBaseName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXTLRuntime::transformNodeToObject(LPDISPATCH stylesheet, const VARIANT& outputObject)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 stylesheet, &outputObject);
}

long IXTLRuntime::uniqueID(LPDISPATCH pNode)
{
	long result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xbb, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pNode);
	return result;
}

long IXTLRuntime::depth(LPDISPATCH pNode)
{
	long result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xbc, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pNode);
	return result;
}

long IXTLRuntime::childNumber(LPDISPATCH pNode)
{
	long result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xbd, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pNode);
	return result;
}

long IXTLRuntime::ancestorChildNumber(LPCTSTR bstrNodeName, LPDISPATCH pNode)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0xbe, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		bstrNodeName, pNode);
	return result;
}

long IXTLRuntime::absoluteChildNumber(LPDISPATCH pNode)
{
	long result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xbf, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pNode);
	return result;
}

CString IXTLRuntime::formatIndex(long lIndex, LPCTSTR bstrFormat)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0xc0, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		lIndex, bstrFormat);
	return result;
}

CString IXTLRuntime::formatNumber(double dblNumber, LPCTSTR bstrFormat)
{
	CString result;
	static BYTE parms[] =
		VTS_R8 VTS_BSTR;
	InvokeHelper(0xc1, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		dblNumber, bstrFormat);
	return result;
}

CString IXTLRuntime::formatDate(const VARIANT& varDate, LPCTSTR bstrFormat, const VARIANT& varDestLocale)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xc2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		&varDate, bstrFormat, &varDestLocale);
	return result;
}

CString IXTLRuntime::formatTime(const VARIANT& varTime, LPCTSTR bstrFormat, const VARIANT& varDestLocale)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xc3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		&varTime, bstrFormat, &varDestLocale);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXSLTemplate properties

/////////////////////////////////////////////////////////////////////////////
// IXSLTemplate operations

void IXSLTemplate::SetRefStylesheet(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IXSLTemplate::GetStylesheet()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXSLTemplate::createProcessor()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXSLProcessor properties

/////////////////////////////////////////////////////////////////////////////
// IXSLProcessor operations

void IXSLProcessor::SetInput(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXSLProcessor::GetInput()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXSLProcessor::GetOwnerTemplate()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXSLProcessor::setStartMode(LPCTSTR mode, LPCTSTR namespaceURI)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 mode, namespaceURI);
}

CString IXSLProcessor::GetStartMode()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IXSLProcessor::GetStartModeURI()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXSLProcessor::SetOutput(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IXSLProcessor::GetOutput()
{
	VARIANT result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL IXSLProcessor::transform()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IXSLProcessor::reset()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IXSLProcessor::GetReadyState()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IXSLProcessor::addParameter(LPCTSTR baseName, const VARIANT& parameter, LPCTSTR namespaceURI)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 baseName, &parameter, namespaceURI);
}

void IXSLProcessor::addObject(LPDISPATCH obj, LPCTSTR namespaceURI)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 obj, namespaceURI);
}

LPDISPATCH IXSLProcessor::GetStylesheet()
{
	LPDISPATCH result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IVBSAXXMLReader properties

/////////////////////////////////////////////////////////////////////////////
// IVBSAXXMLReader operations

BOOL IVBSAXXMLReader::getFeature(LPCTSTR strName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		strName);
	return result;
}

void IVBSAXXMLReader::putFeature(LPCTSTR strName, BOOL fValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x503, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName, fValue);
}

VARIANT IVBSAXXMLReader::getProperty(LPCTSTR strName)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x504, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		strName);
	return result;
}

void IVBSAXXMLReader::putProperty(LPCTSTR strName, const VARIANT& varValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName, &varValue);
}

LPDISPATCH IVBSAXXMLReader::GetEntityResolver()
{
	LPDISPATCH result;
	InvokeHelper(0x506, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IVBSAXXMLReader::SetRefEntityResolver(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x506, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IVBSAXXMLReader::GetContentHandler()
{
	LPDISPATCH result;
	InvokeHelper(0x507, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IVBSAXXMLReader::SetRefContentHandler(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x507, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IVBSAXXMLReader::GetDtdHandler()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IVBSAXXMLReader::SetRefDtdHandler(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x508, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IVBSAXXMLReader::GetErrorHandler()
{
	LPDISPATCH result;
	InvokeHelper(0x509, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IVBSAXXMLReader::SetRefErrorHandler(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x509, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IVBSAXXMLReader::GetBaseURL()
{
	CString result;
	InvokeHelper(0x50a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IVBSAXXMLReader::SetBaseURL(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x50a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IVBSAXXMLReader::GetSecureBaseURL()
{
	CString result;
	InvokeHelper(0x50b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IVBSAXXMLReader::SetSecureBaseURL(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x50b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IVBSAXXMLReader::parse(const VARIANT& varInput)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &varInput);
}

void IVBSAXXMLReader::parseURL(LPCTSTR strURL)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strURL);
}


/////////////////////////////////////////////////////////////////////////////
// IVBSAXEntityResolver properties

/////////////////////////////////////////////////////////////////////////////
// IVBSAXEntityResolver operations

VARIANT IVBSAXEntityResolver::resolveEntity(BSTR* strPublicId, BSTR* strSystemId)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x527, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		strPublicId, strSystemId);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IVBSAXContentHandler properties

/////////////////////////////////////////////////////////////////////////////
// IVBSAXContentHandler operations

void IVBSAXContentHandler::SetRefDocumentLocator(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x52a, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void IVBSAXContentHandler::startDocument()
{
	InvokeHelper(0x52b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IVBSAXContentHandler::endDocument()
{
	InvokeHelper(0x52c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IVBSAXContentHandler::startPrefixMapping(BSTR* strPrefix, BSTR* strURI)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x52d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strPrefix, strURI);
}

void IVBSAXContentHandler::endPrefixMapping(BSTR* strPrefix)
{
	static BYTE parms[] =
		VTS_PBSTR;
	InvokeHelper(0x52e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strPrefix);
}

void IVBSAXContentHandler::startElement(BSTR* strNamespaceURI, BSTR* strLocalName, BSTR* strQName, LPDISPATCH oAttributes)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_DISPATCH;
	InvokeHelper(0x52f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strNamespaceURI, strLocalName, strQName, oAttributes);
}

void IVBSAXContentHandler::endElement(BSTR* strNamespaceURI, BSTR* strLocalName, BSTR* strQName)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x530, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strNamespaceURI, strLocalName, strQName);
}

void IVBSAXContentHandler::characters(BSTR* strChars)
{
	static BYTE parms[] =
		VTS_PBSTR;
	InvokeHelper(0x531, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strChars);
}

void IVBSAXContentHandler::ignorableWhitespace(BSTR* strChars)
{
	static BYTE parms[] =
		VTS_PBSTR;
	InvokeHelper(0x532, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strChars);
}

void IVBSAXContentHandler::processingInstruction(BSTR* strTarget, BSTR* strData)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x533, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strTarget, strData);
}

void IVBSAXContentHandler::skippedEntity(BSTR* strName)
{
	static BYTE parms[] =
		VTS_PBSTR;
	InvokeHelper(0x534, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName);
}


/////////////////////////////////////////////////////////////////////////////
// IVBSAXLocator properties

/////////////////////////////////////////////////////////////////////////////
// IVBSAXLocator operations

long IVBSAXLocator::GetColumnNumber()
{
	long result;
	InvokeHelper(0x521, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IVBSAXLocator::GetLineNumber()
{
	long result;
	InvokeHelper(0x522, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IVBSAXLocator::GetPublicId()
{
	CString result;
	InvokeHelper(0x523, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IVBSAXLocator::GetSystemId()
{
	CString result;
	InvokeHelper(0x524, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IVBSAXAttributes properties

/////////////////////////////////////////////////////////////////////////////
// IVBSAXAttributes operations

long IVBSAXAttributes::GetLength()
{
	long result;
	InvokeHelper(0x540, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IVBSAXAttributes::getURI(long nIndex)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x541, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		nIndex);
	return result;
}

CString IVBSAXAttributes::getLocalName(long nIndex)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x542, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		nIndex);
	return result;
}

CString IVBSAXAttributes::getQName(long nIndex)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x543, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		nIndex);
	return result;
}

long IVBSAXAttributes::getIndexFromName(LPCTSTR strURI, LPCTSTR strLocalName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x544, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		strURI, strLocalName);
	return result;
}

long IVBSAXAttributes::getIndexFromQName(LPCTSTR strQName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x545, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		strQName);
	return result;
}

CString IVBSAXAttributes::getType(long nIndex)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x546, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		nIndex);
	return result;
}

CString IVBSAXAttributes::getTypeFromName(LPCTSTR strURI, LPCTSTR strLocalName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x547, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		strURI, strLocalName);
	return result;
}

CString IVBSAXAttributes::getTypeFromQName(LPCTSTR strQName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x548, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		strQName);
	return result;
}

CString IVBSAXAttributes::getValue(long nIndex)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x549, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		nIndex);
	return result;
}

CString IVBSAXAttributes::getValueFromName(LPCTSTR strURI, LPCTSTR strLocalName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x54a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		strURI, strLocalName);
	return result;
}

CString IVBSAXAttributes::getValueFromQName(LPCTSTR strQName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x54b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		strQName);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IVBSAXDTDHandler properties

/////////////////////////////////////////////////////////////////////////////
// IVBSAXDTDHandler operations

void IVBSAXDTDHandler::notationDecl(BSTR* strName, BSTR* strPublicId, BSTR* strSystemId)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x537, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName, strPublicId, strSystemId);
}

void IVBSAXDTDHandler::unparsedEntityDecl(BSTR* strName, BSTR* strPublicId, BSTR* strSystemId, BSTR* strNotationName)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x538, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName, strPublicId, strSystemId, strNotationName);
}


/////////////////////////////////////////////////////////////////////////////
// IVBSAXErrorHandler properties

/////////////////////////////////////////////////////////////////////////////
// IVBSAXErrorHandler operations

void IVBSAXErrorHandler::error(LPDISPATCH oLocator, BSTR* strErrorMessage, long nErrorCode)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBSTR VTS_I4;
	InvokeHelper(0x53b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 oLocator, strErrorMessage, nErrorCode);
}

void IVBSAXErrorHandler::fatalError(LPDISPATCH oLocator, BSTR* strErrorMessage, long nErrorCode)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBSTR VTS_I4;
	InvokeHelper(0x53c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 oLocator, strErrorMessage, nErrorCode);
}

void IVBSAXErrorHandler::ignorableWarning(LPDISPATCH oLocator, BSTR* strErrorMessage, long nErrorCode)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBSTR VTS_I4;
	InvokeHelper(0x53d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 oLocator, strErrorMessage, nErrorCode);
}


/////////////////////////////////////////////////////////////////////////////
// IVBSAXXMLFilter properties

/////////////////////////////////////////////////////////////////////////////
// IVBSAXXMLFilter operations

LPDISPATCH IVBSAXXMLFilter::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x51d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IVBSAXXMLFilter::SetRefParent(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x51d, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IVBSAXLexicalHandler properties

/////////////////////////////////////////////////////////////////////////////
// IVBSAXLexicalHandler operations

void IVBSAXLexicalHandler::startDTD(BSTR* strName, BSTR* strPublicId, BSTR* strSystemId)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x54e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName, strPublicId, strSystemId);
}

void IVBSAXLexicalHandler::endDTD()
{
	InvokeHelper(0x54f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IVBSAXLexicalHandler::startEntity(BSTR* strName)
{
	static BYTE parms[] =
		VTS_PBSTR;
	InvokeHelper(0x550, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName);
}

void IVBSAXLexicalHandler::endEntity(BSTR* strName)
{
	static BYTE parms[] =
		VTS_PBSTR;
	InvokeHelper(0x551, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName);
}

void IVBSAXLexicalHandler::startCDATA()
{
	InvokeHelper(0x552, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IVBSAXLexicalHandler::endCDATA()
{
	InvokeHelper(0x553, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IVBSAXLexicalHandler::comment(BSTR* strChars)
{
	static BYTE parms[] =
		VTS_PBSTR;
	InvokeHelper(0x554, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strChars);
}


/////////////////////////////////////////////////////////////////////////////
// IVBSAXDeclHandler properties

/////////////////////////////////////////////////////////////////////////////
// IVBSAXDeclHandler operations

void IVBSAXDeclHandler::elementDecl(BSTR* strName, BSTR* strModel)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x557, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName, strModel);
}

void IVBSAXDeclHandler::attributeDecl(BSTR* strElementName, BSTR* strAttributeName, BSTR* strType, BSTR* strValueDefault, BSTR* strValue)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x558, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strElementName, strAttributeName, strType, strValueDefault, strValue);
}

void IVBSAXDeclHandler::internalEntityDecl(BSTR* strName, BSTR* strValue)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x559, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName, strValue);
}

void IVBSAXDeclHandler::externalEntityDecl(BSTR* strName, BSTR* strPublicId, BSTR* strSystemId)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x55a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName, strPublicId, strSystemId);
}


/////////////////////////////////////////////////////////////////////////////
// IMXWriter properties

/////////////////////////////////////////////////////////////////////////////
// IMXWriter operations

void IMXWriter::SetOutput(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x569, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IMXWriter::GetOutput()
{
	VARIANT result;
	InvokeHelper(0x569, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IMXWriter::SetEncoding(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x56b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IMXWriter::GetEncoding()
{
	CString result;
	InvokeHelper(0x56b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IMXWriter::SetByteOrderMark(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x56c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IMXWriter::GetByteOrderMark()
{
	BOOL result;
	InvokeHelper(0x56c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IMXWriter::SetIndent(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x56d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IMXWriter::GetIndent()
{
	BOOL result;
	InvokeHelper(0x56d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IMXWriter::SetStandalone(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x56e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IMXWriter::GetStandalone()
{
	BOOL result;
	InvokeHelper(0x56e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IMXWriter::SetOmitXMLDeclaration(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x56f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IMXWriter::GetOmitXMLDeclaration()
{
	BOOL result;
	InvokeHelper(0x56f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IMXWriter::SetVersion(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x570, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IMXWriter::GetVersion()
{
	CString result;
	InvokeHelper(0x570, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IMXWriter::SetDisableOutputEscaping(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x571, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IMXWriter::GetDisableOutputEscaping()
{
	BOOL result;
	InvokeHelper(0x571, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IMXWriter::flush()
{
	InvokeHelper(0x572, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IMXAttributes properties

/////////////////////////////////////////////////////////////////////////////
// IMXAttributes operations

void IMXAttributes::addAttribute(LPCTSTR strURI, LPCTSTR strLocalName, LPCTSTR strQName, LPCTSTR strType, LPCTSTR strValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x55d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strURI, strLocalName, strQName, strType, strValue);
}

void IMXAttributes::addAttributeFromIndex(const VARIANT& varAtts, long nIndex)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4;
	InvokeHelper(0x567, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &varAtts, nIndex);
}

void IMXAttributes::clear()
{
	InvokeHelper(0x55e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IMXAttributes::removeAttribute(long nIndex)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x55f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nIndex);
}

void IMXAttributes::setAttribute(long nIndex, LPCTSTR strURI, LPCTSTR strLocalName, LPCTSTR strQName, LPCTSTR strType, LPCTSTR strValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x560, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nIndex, strURI, strLocalName, strQName, strType, strValue);
}

void IMXAttributes::setAttributes(const VARIANT& varAtts)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x561, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &varAtts);
}

void IMXAttributes::setLocalName(long nIndex, LPCTSTR strLocalName)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x562, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nIndex, strLocalName);
}

void IMXAttributes::setQName(long nIndex, LPCTSTR strQName)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x563, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nIndex, strQName);
}

void IMXAttributes::setType(long nIndex, LPCTSTR strType)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x564, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nIndex, strType);
}

void IMXAttributes::setURI(long nIndex, LPCTSTR strURI)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x565, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nIndex, strURI);
}

void IMXAttributes::setValue(long nIndex, LPCTSTR strValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x566, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nIndex, strValue);
}


/////////////////////////////////////////////////////////////////////////////
// IMXReaderControl properties

/////////////////////////////////////////////////////////////////////////////
// IMXReaderControl operations

void IMXReaderControl::abort()
{
	InvokeHelper(0x576, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IMXReaderControl::resume()
{
	InvokeHelper(0x577, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IMXReaderControl::suspend()
{
	InvokeHelper(0x578, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IMXSchemaDeclHandler properties

/////////////////////////////////////////////////////////////////////////////
// IMXSchemaDeclHandler operations

void IMXSchemaDeclHandler::schemaElementDecl(LPDISPATCH oSchemaElement)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x57b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 oSchemaElement);
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaElement properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaElement operations

CString ISchemaElement::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaElement::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaElement::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaElement::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaElement::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaElement::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaElement::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}

VARIANT ISchemaElement::GetMinOccurs()
{
	VARIANT result;
	InvokeHelper(0x5af, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaElement::GetMaxOccurs()
{
	VARIANT result;
	InvokeHelper(0x5ab, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaElement::GetType()
{
	LPDISPATCH result;
	InvokeHelper(0x5c4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaElement::GetScope()
{
	LPDISPATCH result;
	InvokeHelper(0x5bd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaElement::GetDefaultValue()
{
	CString result;
	InvokeHelper(0x597, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaElement::GetFixedValue()
{
	CString result;
	InvokeHelper(0x59e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL ISchemaElement::GetIsNillable()
{
	BOOL result;
	InvokeHelper(0x5a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaElement::GetIdentityConstraints()
{
	LPDISPATCH result;
	InvokeHelper(0x5a1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaElement::GetSubstitutionGroup()
{
	LPDISPATCH result;
	InvokeHelper(0x5bf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ISchemaElement::GetSubstitutionGroupExclusions()
{
	long result;
	InvokeHelper(0x5c0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ISchemaElement::GetDisallowedSubstitutions()
{
	long result;
	InvokeHelper(0x599, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ISchemaElement::GetIsAbstract()
{
	BOOL result;
	InvokeHelper(0x5a2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ISchemaElement::GetIsReference()
{
	BOOL result;
	InvokeHelper(0x5a4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaParticle properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaParticle operations

CString ISchemaParticle::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaParticle::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaParticle::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaParticle::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaParticle::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaParticle::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaParticle::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}

VARIANT ISchemaParticle::GetMinOccurs()
{
	VARIANT result;
	InvokeHelper(0x5af, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaParticle::GetMaxOccurs()
{
	VARIANT result;
	InvokeHelper(0x5ab, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaItem properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaItem operations

CString ISchemaItem::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaItem::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaItem::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaItem::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaItem::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaItem::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaItem::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchema properties

/////////////////////////////////////////////////////////////////////////////
// ISchema operations

CString ISchema::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchema::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchema::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchema::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchema::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchema::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchema::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}

CString ISchema::GetTargetNamespace()
{
	CString result;
	InvokeHelper(0x5c2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchema::GetVersion()
{
	CString result;
	InvokeHelper(0x5c9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchema::GetTypes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchema::GetElements()
{
	LPDISPATCH result;
	InvokeHelper(0x59a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchema::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x593, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchema::GetAttributeGroups()
{
	LPDISPATCH result;
	InvokeHelper(0x592, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchema::GetModelGroups()
{
	LPDISPATCH result;
	InvokeHelper(0x5b0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchema::GetNotations()
{
	LPDISPATCH result;
	InvokeHelper(0x5b4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchema::GetSchemaLocations()
{
	LPDISPATCH result;
	InvokeHelper(0x5bc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaItemCollection properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaItemCollection operations

LPDISPATCH ISchemaItemCollection::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH ISchemaItemCollection::itemByName(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x58f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH ISchemaItemCollection::itemByQName(LPCTSTR name, LPCTSTR namespaceURI)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x590, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name, namespaceURI);
	return result;
}

long ISchemaItemCollection::GetLength()
{
	long result;
	InvokeHelper(0x5a7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaStringCollection properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaStringCollection operations

CString ISchemaStringCollection::GetItem(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

long ISchemaStringCollection::GetLength()
{
	long result;
	InvokeHelper(0x5a7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaType properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaType operations

CString ISchemaType::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaType::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaType::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaType::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaType::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaType::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaType::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}

LPDISPATCH ISchemaType::GetBaseTypes()
{
	LPDISPATCH result;
	InvokeHelper(0x594, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ISchemaType::GetFinal()
{
	long result;
	InvokeHelper(0x59d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ISchemaType::GetVariety()
{
	long result;
	InvokeHelper(0x5c8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ISchemaType::GetDerivedBy()
{
	long result;
	InvokeHelper(0x598, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ISchemaType::isValid(LPCTSTR data)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5a5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		data);
	return result;
}

CString ISchemaType::GetMinExclusive()
{
	CString result;
	InvokeHelper(0x5ac, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaType::GetMinInclusive()
{
	CString result;
	InvokeHelper(0x5ad, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaType::GetMaxExclusive()
{
	CString result;
	InvokeHelper(0x5a8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaType::GetMaxInclusive()
{
	CString result;
	InvokeHelper(0x5a9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaType::GetTotalDigits()
{
	VARIANT result;
	InvokeHelper(0x5c3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaType::GetFractionDigits()
{
	VARIANT result;
	InvokeHelper(0x59f, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaType::GetLength()
{
	VARIANT result;
	InvokeHelper(0x5a7, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaType::GetMinLength()
{
	VARIANT result;
	InvokeHelper(0x5ae, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaType::GetMaxLength()
{
	VARIANT result;
	InvokeHelper(0x5aa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaType::GetEnumeration()
{
	LPDISPATCH result;
	InvokeHelper(0x59b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ISchemaType::GetWhitespace()
{
	long result;
	InvokeHelper(0x5ca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaType::GetPatterns()
{
	LPDISPATCH result;
	InvokeHelper(0x5b6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaComplexType properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaComplexType operations

CString ISchemaComplexType::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaComplexType::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaComplexType::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaComplexType::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaComplexType::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaComplexType::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaComplexType::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}

LPDISPATCH ISchemaComplexType::GetBaseTypes()
{
	LPDISPATCH result;
	InvokeHelper(0x594, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ISchemaComplexType::GetFinal()
{
	long result;
	InvokeHelper(0x59d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ISchemaComplexType::GetVariety()
{
	long result;
	InvokeHelper(0x5c8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ISchemaComplexType::GetDerivedBy()
{
	long result;
	InvokeHelper(0x598, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ISchemaComplexType::isValid(LPCTSTR data)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5a5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		data);
	return result;
}

CString ISchemaComplexType::GetMinExclusive()
{
	CString result;
	InvokeHelper(0x5ac, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaComplexType::GetMinInclusive()
{
	CString result;
	InvokeHelper(0x5ad, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaComplexType::GetMaxExclusive()
{
	CString result;
	InvokeHelper(0x5a8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaComplexType::GetMaxInclusive()
{
	CString result;
	InvokeHelper(0x5a9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaComplexType::GetTotalDigits()
{
	VARIANT result;
	InvokeHelper(0x5c3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaComplexType::GetFractionDigits()
{
	VARIANT result;
	InvokeHelper(0x59f, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaComplexType::GetLength()
{
	VARIANT result;
	InvokeHelper(0x5a7, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaComplexType::GetMinLength()
{
	VARIANT result;
	InvokeHelper(0x5ae, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaComplexType::GetMaxLength()
{
	VARIANT result;
	InvokeHelper(0x5aa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaComplexType::GetEnumeration()
{
	LPDISPATCH result;
	InvokeHelper(0x59b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ISchemaComplexType::GetWhitespace()
{
	long result;
	InvokeHelper(0x5ca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaComplexType::GetPatterns()
{
	LPDISPATCH result;
	InvokeHelper(0x5b6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaComplexType::GetIsAbstract()
{
	BOOL result;
	InvokeHelper(0x5a2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaComplexType::GetAnyAttribute()
{
	LPDISPATCH result;
	InvokeHelper(0x591, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaComplexType::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x593, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ISchemaComplexType::GetContentType()
{
	long result;
	InvokeHelper(0x596, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaComplexType::GetContentModel()
{
	LPDISPATCH result;
	InvokeHelper(0x595, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ISchemaComplexType::GetProhibitedSubstitutions()
{
	long result;
	InvokeHelper(0x5b8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaAny properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaAny operations

CString ISchemaAny::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaAny::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaAny::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaAny::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaAny::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaAny::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaAny::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}

VARIANT ISchemaAny::GetMinOccurs()
{
	VARIANT result;
	InvokeHelper(0x5af, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaAny::GetMaxOccurs()
{
	VARIANT result;
	InvokeHelper(0x5ab, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaAny::GetNamespaces()
{
	LPDISPATCH result;
	InvokeHelper(0x5b2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ISchemaAny::GetProcessContents()
{
	long result;
	InvokeHelper(0x5b7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaModelGroup properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaModelGroup operations

CString ISchemaModelGroup::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaModelGroup::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaModelGroup::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaModelGroup::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaModelGroup::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaModelGroup::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaModelGroup::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}

VARIANT ISchemaModelGroup::GetMinOccurs()
{
	VARIANT result;
	InvokeHelper(0x5af, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ISchemaModelGroup::GetMaxOccurs()
{
	VARIANT result;
	InvokeHelper(0x5ab, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaModelGroup::GetParticles()
{
	LPDISPATCH result;
	InvokeHelper(0x5b5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IMXXMLFilter properties

/////////////////////////////////////////////////////////////////////////////
// IMXXMLFilter operations

BOOL IMXXMLFilter::getFeature(LPCTSTR strName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x58f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		strName);
	return result;
}

void IMXXMLFilter::putFeature(LPCTSTR strName, BOOL fValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x591, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName, fValue);
}

VARIANT IMXXMLFilter::getProperty(LPCTSTR strName)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x590, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		strName);
	return result;
}

void IMXXMLFilter::putProperty(LPCTSTR strName, const VARIANT& varValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x592, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 strName, &varValue);
}

LPUNKNOWN IMXXMLFilter::GetEntityResolver()
{
	LPUNKNOWN result;
	InvokeHelper(0x58d, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void IMXXMLFilter::SetRefEntityResolver(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x58d, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPUNKNOWN IMXXMLFilter::GetContentHandler()
{
	LPUNKNOWN result;
	InvokeHelper(0x58b, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void IMXXMLFilter::SetRefContentHandler(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x58b, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPUNKNOWN IMXXMLFilter::GetDtdHandler()
{
	LPUNKNOWN result;
	InvokeHelper(0x58c, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void IMXXMLFilter::SetRefDtdHandler(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x58c, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPUNKNOWN IMXXMLFilter::GetErrorHandler()
{
	LPUNKNOWN result;
	InvokeHelper(0x58e, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void IMXXMLFilter::SetRefErrorHandler(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x58e, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMSchemaCollection2 properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMSchemaCollection2 operations

void IXMLDOMSchemaCollection2::add(LPCTSTR namespaceURI, const VARIANT& var)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 namespaceURI, &var);
}

LPDISPATCH IXMLDOMSchemaCollection2::get(LPCTSTR namespaceURI)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceURI);
	return result;
}

void IXMLDOMSchemaCollection2::remove(LPCTSTR namespaceURI)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 namespaceURI);
}

long IXMLDOMSchemaCollection2::GetLength()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IXMLDOMSchemaCollection2::GetNamespaceURI(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

void IXMLDOMSchemaCollection2::addCollection(LPDISPATCH otherCollection)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 otherCollection);
}

void IXMLDOMSchemaCollection2::validate()
{
	InvokeHelper(0x58b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IXMLDOMSchemaCollection2::SetValidateOnLoad(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x58c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IXMLDOMSchemaCollection2::GetValidateOnLoad()
{
	BOOL result;
	InvokeHelper(0x58c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMSchemaCollection2::getSchema(LPCTSTR namespaceURI)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x58d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceURI);
	return result;
}

LPDISPATCH IXMLDOMSchemaCollection2::getDeclaration(LPDISPATCH node)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x58e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		node);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaAttribute properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaAttribute operations

CString ISchemaAttribute::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaAttribute::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaAttribute::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaAttribute::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaAttribute::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaAttribute::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaAttribute::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}

LPDISPATCH ISchemaAttribute::GetType()
{
	LPDISPATCH result;
	InvokeHelper(0x5c4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaAttribute::GetScope()
{
	LPDISPATCH result;
	InvokeHelper(0x5bd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaAttribute::GetDefaultValue()
{
	CString result;
	InvokeHelper(0x597, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaAttribute::GetFixedValue()
{
	CString result;
	InvokeHelper(0x59e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaAttribute::GetUse()
{
	long result;
	InvokeHelper(0x5c7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ISchemaAttribute::GetIsReference()
{
	BOOL result;
	InvokeHelper(0x5a4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaAttributeGroup properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaAttributeGroup operations

CString ISchemaAttributeGroup::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaAttributeGroup::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaAttributeGroup::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaAttributeGroup::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaAttributeGroup::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaAttributeGroup::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaAttributeGroup::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}

LPDISPATCH ISchemaAttributeGroup::GetAnyAttribute()
{
	LPDISPATCH result;
	InvokeHelper(0x591, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaAttributeGroup::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x593, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaIdentityConstraint properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaIdentityConstraint operations

CString ISchemaIdentityConstraint::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaIdentityConstraint::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaIdentityConstraint::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaIdentityConstraint::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaIdentityConstraint::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaIdentityConstraint::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaIdentityConstraint::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}

CString ISchemaIdentityConstraint::GetSelector()
{
	CString result;
	InvokeHelper(0x5be, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaIdentityConstraint::GetFields()
{
	LPDISPATCH result;
	InvokeHelper(0x59c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaIdentityConstraint::GetReferencedKey()
{
	LPDISPATCH result;
	InvokeHelper(0x5ba, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ISchemaNotation properties

/////////////////////////////////////////////////////////////////////////////
// ISchemaNotation operations

CString ISchemaNotation::GetName()
{
	CString result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaNotation::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x5b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaNotation::GetSchema()
{
	LPDISPATCH result;
	InvokeHelper(0x5bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ISchemaNotation::GetId()
{
	CString result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ISchemaNotation::GetItemType()
{
	long result;
	InvokeHelper(0x5a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ISchemaNotation::GetUnhandledAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0x5c6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL ISchemaNotation::writeAnnotation(LPUNKNOWN annotationSink)
{
	BOOL result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x5cb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		annotationSink);
	return result;
}

CString ISchemaNotation::GetSystemIdentifier()
{
	CString result;
	InvokeHelper(0x5c1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ISchemaNotation::GetPublicIdentifier()
{
	CString result;
	InvokeHelper(0x5b9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLDOMSelection properties

/////////////////////////////////////////////////////////////////////////////
// IXMLDOMSelection operations

LPDISPATCH IXMLDOMSelection::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long IXMLDOMSelection::GetLength()
{
	long result;
	InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMSelection::nextNode()
{
	LPDISPATCH result;
	InvokeHelper(0x4c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXMLDOMSelection::reset()
{
	InvokeHelper(0x4d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString IXMLDOMSelection::GetExpr()
{
	CString result;
	InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLDOMSelection::SetExpr(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x51, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH IXMLDOMSelection::GetContext()
{
	LPDISPATCH result;
	InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXMLDOMSelection::SetRefContext(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x52, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IXMLDOMSelection::peekNode()
{
	LPDISPATCH result;
	InvokeHelper(0x53, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLDOMSelection::matches(LPDISPATCH pNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x54, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		pNode);
	return result;
}

LPDISPATCH IXMLDOMSelection::removeNext()
{
	LPDISPATCH result;
	InvokeHelper(0x55, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IXMLDOMSelection::removeAll()
{
	InvokeHelper(0x56, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IXMLDOMSelection::clone()
{
	LPDISPATCH result;
	InvokeHelper(0x57, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IXMLDOMSelection::getProperty(LPCTSTR name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x58, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		name);
	return result;
}

void IXMLDOMSelection::setProperty(LPCTSTR name, const VARIANT& value)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x59, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 name, &value);
}


/////////////////////////////////////////////////////////////////////////////
// XMLDOMDocumentEvents properties

/////////////////////////////////////////////////////////////////////////////
// XMLDOMDocumentEvents operations


/////////////////////////////////////////////////////////////////////////////
// IDSOControl properties

/////////////////////////////////////////////////////////////////////////////
// IDSOControl operations

LPDISPATCH IDSOControl::GetXMLDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x10001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IDSOControl::SetXMLDocument(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IDSOControl::GetJavaDSOCompatible()
{
	long result;
	InvokeHelper(0x10002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IDSOControl::SetJavaDSOCompatible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IDSOControl::GetReadyState()
{
	long result;
	InvokeHelper(DISPID_READYSTATE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IXMLHTTPRequest properties

/////////////////////////////////////////////////////////////////////////////
// IXMLHTTPRequest operations

void IXMLHTTPRequest::open(LPCTSTR bstrMethod, LPCTSTR bstrUrl, const VARIANT& varAsync, const VARIANT& bstrUser, const VARIANT& bstrPassword)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrMethod, bstrUrl, &varAsync, &bstrUser, &bstrPassword);
}

void IXMLHTTPRequest::setRequestHeader(LPCTSTR bstrHeader, LPCTSTR bstrValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrHeader, bstrValue);
}

CString IXMLHTTPRequest::getResponseHeader(LPCTSTR bstrHeader)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		bstrHeader);
	return result;
}

CString IXMLHTTPRequest::getAllResponseHeaders()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IXMLHTTPRequest::send(const VARIANT& varBody)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &varBody);
}

void IXMLHTTPRequest::abort()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IXMLHTTPRequest::GetStatus()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IXMLHTTPRequest::GetStatusText()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IXMLHTTPRequest::GetResponseXML()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IXMLHTTPRequest::GetResponseText()
{
	CString result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IXMLHTTPRequest::GetResponseBody()
{
	VARIANT result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IXMLHTTPRequest::GetResponseStream()
{
	VARIANT result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long IXMLHTTPRequest::GetReadyState()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IXMLHTTPRequest::SetOnreadystatechange(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IServerXMLHTTPRequest properties

/////////////////////////////////////////////////////////////////////////////
// IServerXMLHTTPRequest operations

void IServerXMLHTTPRequest::open(LPCTSTR bstrMethod, LPCTSTR bstrUrl, const VARIANT& varAsync, const VARIANT& bstrUser, const VARIANT& bstrPassword)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrMethod, bstrUrl, &varAsync, &bstrUser, &bstrPassword);
}

void IServerXMLHTTPRequest::setRequestHeader(LPCTSTR bstrHeader, LPCTSTR bstrValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrHeader, bstrValue);
}

CString IServerXMLHTTPRequest::getResponseHeader(LPCTSTR bstrHeader)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		bstrHeader);
	return result;
}

CString IServerXMLHTTPRequest::getAllResponseHeaders()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IServerXMLHTTPRequest::send(const VARIANT& varBody)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &varBody);
}

void IServerXMLHTTPRequest::abort()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IServerXMLHTTPRequest::GetStatus()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IServerXMLHTTPRequest::GetStatusText()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IServerXMLHTTPRequest::GetResponseXML()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IServerXMLHTTPRequest::GetResponseText()
{
	CString result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IServerXMLHTTPRequest::GetResponseBody()
{
	VARIANT result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IServerXMLHTTPRequest::GetResponseStream()
{
	VARIANT result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long IServerXMLHTTPRequest::GetReadyState()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IServerXMLHTTPRequest::SetOnreadystatechange(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void IServerXMLHTTPRequest::setTimeouts(long resolveTimeout, long connectTimeout, long sendTimeout, long receiveTimeout)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 resolveTimeout, connectTimeout, sendTimeout, receiveTimeout);
}

BOOL IServerXMLHTTPRequest::waitForResponse(const VARIANT& timeoutInSeconds)
{
	BOOL result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		&timeoutInSeconds);
	return result;
}

VARIANT IServerXMLHTTPRequest::getOption(long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		option);
	return result;
}

void IServerXMLHTTPRequest::setOption(long option, const VARIANT& value)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 option, &value);
}


/////////////////////////////////////////////////////////////////////////////
// IServerXMLHTTPRequest2 properties

/////////////////////////////////////////////////////////////////////////////
// IServerXMLHTTPRequest2 operations

void IServerXMLHTTPRequest2::open(LPCTSTR bstrMethod, LPCTSTR bstrUrl, const VARIANT& varAsync, const VARIANT& bstrUser, const VARIANT& bstrPassword)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrMethod, bstrUrl, &varAsync, &bstrUser, &bstrPassword);
}

void IServerXMLHTTPRequest2::setRequestHeader(LPCTSTR bstrHeader, LPCTSTR bstrValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrHeader, bstrValue);
}

CString IServerXMLHTTPRequest2::getResponseHeader(LPCTSTR bstrHeader)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		bstrHeader);
	return result;
}

CString IServerXMLHTTPRequest2::getAllResponseHeaders()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IServerXMLHTTPRequest2::send(const VARIANT& varBody)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &varBody);
}

void IServerXMLHTTPRequest2::abort()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IServerXMLHTTPRequest2::GetStatus()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IServerXMLHTTPRequest2::GetStatusText()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IServerXMLHTTPRequest2::GetResponseXML()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IServerXMLHTTPRequest2::GetResponseText()
{
	CString result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IServerXMLHTTPRequest2::GetResponseBody()
{
	VARIANT result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IServerXMLHTTPRequest2::GetResponseStream()
{
	VARIANT result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long IServerXMLHTTPRequest2::GetReadyState()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IServerXMLHTTPRequest2::SetOnreadystatechange(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void IServerXMLHTTPRequest2::setTimeouts(long resolveTimeout, long connectTimeout, long sendTimeout, long receiveTimeout)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 resolveTimeout, connectTimeout, sendTimeout, receiveTimeout);
}

BOOL IServerXMLHTTPRequest2::waitForResponse(const VARIANT& timeoutInSeconds)
{
	BOOL result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		&timeoutInSeconds);
	return result;
}

VARIANT IServerXMLHTTPRequest2::getOption(long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		option);
	return result;
}

void IServerXMLHTTPRequest2::setOption(long option, const VARIANT& value)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 option, &value);
}

void IServerXMLHTTPRequest2::setProxy(long proxySetting, const VARIANT& varProxyServer, const VARIANT& varBypassList)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 proxySetting, &varProxyServer, &varBypassList);
}

void IServerXMLHTTPRequest2::setProxyCredentials(LPCTSTR bstrUserName, LPCTSTR bstrPassword)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrUserName, bstrPassword);
}


/////////////////////////////////////////////////////////////////////////////
// IMXNamespacePrefixes properties

/////////////////////////////////////////////////////////////////////////////
// IMXNamespacePrefixes operations

CString IMXNamespacePrefixes::GetItem(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

long IMXNamespacePrefixes::GetLength()
{
	long result;
	InvokeHelper(0x588, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IVBMXNamespaceManager properties

/////////////////////////////////////////////////////////////////////////////
// IVBMXNamespaceManager operations

void IVBMXNamespaceManager::SetAllowOverride(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x57e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IVBMXNamespaceManager::GetAllowOverride()
{
	BOOL result;
	InvokeHelper(0x57e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IVBMXNamespaceManager::reset()
{
	InvokeHelper(0x57f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IVBMXNamespaceManager::pushContext()
{
	InvokeHelper(0x580, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IVBMXNamespaceManager::pushNodeContext(LPDISPATCH contextNode, BOOL fDeep)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x581, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 contextNode, fDeep);
}

void IVBMXNamespaceManager::popContext()
{
	InvokeHelper(0x582, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IVBMXNamespaceManager::declarePrefix(LPCTSTR prefix, LPCTSTR namespaceURI)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x583, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 prefix, namespaceURI);
}

LPDISPATCH IVBMXNamespaceManager::getDeclaredPrefixes()
{
	LPDISPATCH result;
	InvokeHelper(0x584, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IVBMXNamespaceManager::getPrefixes(LPCTSTR namespaceURI)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x585, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceURI);
	return result;
}

VARIANT IVBMXNamespaceManager::getURI(LPCTSTR prefix)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x586, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		prefix);
	return result;
}

VARIANT IVBMXNamespaceManager::getURIFromNode(LPCTSTR strPrefix, LPDISPATCH contextNode)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x587, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		strPrefix, contextNode);
	return result;
}
