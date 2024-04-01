#include "stdafx.h"
#include <cu\XmlReader.h>
#include <atlbase.h>
//#include "msxml.tlh"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CXmlReader::CXmlReader()
{
	Construct();
}

void CXmlReader::Construct()
{
	m_pDomDoc = NULL;
	m_pDomNode = NULL;
	m_pCurDomNode = NULL;
	m_pDomParseErr = NULL;

	m_bTmpFileName = FALSE;
}

CXmlReader::CXmlReader( LPCTSTR pctszFilename )
{
	Construct();
	if( Open( pctszFilename ) )
		throw _T("Xml file open error");
}

CXmlReader::CXmlReader( BSTR bszXML )
{
	Construct();
//	if( Open( bszXML ) )
//		throw _T("Xml buffer init error");
}

CXmlReader::~CXmlReader()
{}

BOOL CXmlReader::InitMSXMLDoc()
{
	ASSERT( NULL == m_pCurDomNode );
	HRESULT hResult;
	hResult = CoInitialize( NULL );
	if( FAILED( hResult ) ) 
		return FALSE;
	
	hResult = CoCreateInstance( MSXML::CLSID_DOMDocument, 
								NULL, CLSCTX_INPROC_SERVER,
								MSXML::IID_IXMLDOMDocument, (void**)&m_pDomDoc );
	if( FAILED( hResult ) )
	{
		CoUninitialize();
		return FALSE;
	}
	
	m_pDomDoc->put_resolveExternals( true );
	m_pDomDoc->put_validateOnParse( true );  //! this enables to read XML files with DOC TYPE
	
	return TRUE;
}

BOOL CXmlReader::Open( LPCTSTR pctszFilename )
{
	if( FALSE == InitMSXMLDoc() )
		return FALSE;
	
	VARIANT_BOOL vbRet;
	_variant_t vXMLFilename( pctszFilename );
	m_pDomDoc->load( vXMLFilename, &vbRet );
	
	m_pDomDoc->QueryInterface( MSXML::IID_IXMLDOMNode, (void**)&m_pDomNode );
	m_pCurDomNode = m_pDomNode;
	m_cszFileName = pctszFilename;
	return TRUE;
}

BOOL CXmlReader::OpenXML( LPCTSTR bszXML )
{
	INT nLen = lstrlen( bszXML );
	if( 0 == nLen )
		return FALSE;
	
	// Get Windows Temp Path
	CString cszTempPath;
	const INT cnPathMax = 256;
	LPTSTR ptszTempPath = cszTempPath.GetBuffer( cnPathMax );
	GetTempPath( cnPathMax, ptszTempPath );
	
	// Get a Temp File Name
	CString cszTempFileName;
	LPTSTR ptszTempFileName = cszTempFileName.GetBuffer( cnPathMax );
	GetTempFileName( ptszTempPath, _T("~XmlText"), 0, ptszTempFileName );
	
	// Open a File with Temp File Name and write the given buffer to the File
	CFile file;
	if( FALSE == file.Open( cszTempFileName, CFile::modeCreate | CFile::modeWrite ) )
		return FALSE;
	
	m_bTmpFileName = TRUE;
    m_cszTmpFileName = cszTempFileName;
	file.Write( bszXML, nLen );
	file.Close();
	return Open( cszTempFileName );
}

void CXmlReader::Close()
{
	ASSERT( m_pDomDoc );
	if( NULL == m_pDomDoc )
		return;
	
	m_pDomDoc->Release();
	m_pDomDoc		= NULL;
	m_pDomNode		= NULL;
	m_pCurDomNode	= NULL;
	m_pDomParseErr	= NULL;
	m_cszFileName.Empty();
	
	if( m_bTmpFileName )
    {
		_tunlink( m_cszTmpFileName );
        m_bTmpFileName = FALSE;
    }
}

BOOL CXmlReader::SetFirstChild()
{
	if( NULL == m_pCurDomNode )
		return FALSE;
	
	MSXML::IXMLDOMNode* pChildNode;
	m_pCurDomNode->get_firstChild( &pChildNode );
	if( NULL == pChildNode )
		return FALSE;
	
	m_pCurDomNode = pChildNode;
	return TRUE;
}

BOOL CXmlReader::Next()
{
	if( NULL == m_pCurDomNode )
		return FALSE;
	
	MSXML::IXMLDOMNode *pChildNode;
	INT nType = GetDomNodeType();
	m_pCurDomNode->get_nextSibling( &pChildNode );
	if( NULL == pChildNode )
	{
		m_pCurDomNode->get_parentNode( &m_pCurDomNode );
		return FALSE;
	}
	
	m_pCurDomNode = pChildNode;
	return TRUE;
}

INT CXmlReader::GetDomNodeType() const
{
	INT nNodeType;
	m_pCurDomNode->get_nodeType( (MSXML::tagDOMNodeType *)&nNodeType );
	return nNodeType;
}

void CXmlReader::GetNodeName( CString& rcszName ) const
{ 
	if( NULL == m_pCurDomNode ) 
		return;
	
	BSTR bszName;
	m_pCurDomNode->get_nodeName( &bszName ); 
	if( bszName )
	{
		rcszName = bszName;
		SysFreeString( bszName );
	}
}

CString CXmlReader::GetAttribute( const TCHAR* pctszAttrName )
{
	ASSERT( pctszAttrName );
	if( NULL == pctszAttrName )
		return CString();
	
	MSXML::IXMLDOMNamedNodeMap *pAttrMap;
	MSXML::IXMLDOMNode *pChildNode;
	HRESULT hResult;
	
	if( FAILED( m_pCurDomNode->get_attributes( &pAttrMap ) ) )
		return CString();
	
	_variant_t vrValue;
	CComBSTR bszAttrName = pctszAttrName;
	hResult = pAttrMap->getNamedItem( bszAttrName, &pChildNode );
	if( FAILED(hResult) || NULL == pChildNode )
		return CString();
	
	hResult = pChildNode->get_nodeValue( &vrValue );
	if( FAILED( hResult ) )
		return CString();
	
	CString csz = vrValue.bstrVal;
	return csz;
}

INT CXmlReader::GetAttributes( CMapStringToString& rcszmapAttr )
{
	HRESULT hResult;
	MSXML::IXMLDOMNamedNodeMap *pAttrMap;
	hResult = m_pCurDomNode->get_attributes( &pAttrMap );
	if( FAILED( hResult ) ) 
		return -1;
	
	if( NULL == pAttrMap )
		return 0;
	
	long lCnt;
	hResult = pAttrMap->get_length( &lCnt );
	if( FAILED( hResult ) ) 
		return -1;
	
	_variant_t vrValue;
	BSTR bszName;
	CString cszName, cszValue;
	MSXML::IXMLDOMNode *pChildNode;
	
	for( INT i = 0; i < lCnt; i++ )
	{
		hResult = pAttrMap->get_item( i, &pChildNode );
		if( FAILED( hResult ) ) 
		{
			rcszmapAttr.RemoveAll();
			return -1;
		}
		
		pChildNode->get_nodeValue( &vrValue );
		pChildNode->get_nodeName( &bszName );
		
		cszName = bszName;
		cszValue = vrValue.bstrVal;
		rcszmapAttr.SetAt( cszName, cszValue );
	}
	
	return lCnt;
}

BOOL CXmlReader::GetText( CString& rcszText )
{
	BSTR bszText;
	if( m_pCurDomNode ) 
	{
		m_pCurDomNode->get_text( &bszText ); 
		rcszText = bszText;
		SysFreeString( bszText );
		return TRUE;
	}
	
	return FALSE;
}

MSXML::IXMLDOMNode* CXmlReader::GetCurrentNode()  {
	return m_pCurDomNode; }

void CXmlReader::SetCurrentNode( MSXML::IXMLDOMNode* pNode ) {
	m_pCurDomNode = pNode;  }
