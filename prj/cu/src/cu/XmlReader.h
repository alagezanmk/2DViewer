#ifndef ___XML_READER__PH___
#define ___XML_READER__PH___

#import "msxml.dll" named_guids raw_interfaces_only

#define TESTHR(x) { hr = x; if( FAILED(hr) ) goto LBCleanUp; }
#define SAFERELEASE(p) { if( p ) { (p)->Release(); p = NULL; } }

class CU_EXT_CLASS CXmlReader
{
public:
	CXmlReader();
	CXmlReader( BSTR bszXml );
	CXmlReader( LPCTSTR pctszFilename );
	virtual ~CXmlReader();
	void Construct();

	BOOL InitMSXMLDoc();
	MSXML::IXMLDOMNode* GetCurrentNode();
	void SetCurrentNode( MSXML::IXMLDOMNode* pNode );

	BOOL OpenXML( LPCTSTR bszXml );
	BOOL Open( LPCTSTR pctszFilename );
	void Close();
	BOOL IsOpen() const;

	BOOL SetFirstChild();
	BOOL Next();

	INT GetDomNodeType() const;
	void GetNodeName( CString& rcszName ) const;
	CString GetAttribute( const TCHAR* pctszAttrName );
	INT GetAttributes( CMapStringToString& rcszmapAttr );
	BOOL GetText( CString& rcszText );

protected:
	MSXML::IXMLDOMDocument*		m_pDomDoc;
	MSXML::IXMLDOMNode*			m_pDomNode;
	MSXML::IXMLDOMNode*			m_pCurDomNode;
	MSXML::IXMLDOMParseError*	m_pDomParseErr;

	BOOL						m_bTmpFileName;
    CString						m_cszTmpFileName;
	CString						m_cszFileName;
};

inline BOOL CXmlReader::IsOpen() const {
	return NULL != m_pDomDoc; }

#endif //!___XML_READER__PH___