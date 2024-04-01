#include "stdafx.h"
#include <Afxtempl.h>

#include "XmlWriter.h"

/// _open, _close, ...
#include <io.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>

// class strstream
#include <atlbase.h>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CXmlWriter::CXmlWriter( INT nFlags /*= enDefault*/ )
{
	Construct( nFlags );
}

void CXmlWriter::Construct( INT nFlags )
{
	m_nLineCharPos = 0;
	m_nIndentPos = 0;

	m_nFlags = nFlags;
	m_nLineSize = 80;
	m_nTabSize = 4;
	m_nAttrIndentSize = 3;
	m_nCommentIndentSize = 3;
	m_nCDATAIndentSize = 2;

	m_pvStream = NULL;
	m_cszFilename.Empty();
}

CXmlWriter::CXmlWriter( LPCTSTR ptszFilename, INT nFlags /*= enDefault*/ )
{
	Construct( nFlags );
	if( FALSE == Open( ptszFilename ) )
		throw _T("Xml file create error");
}

CXmlWriter::CXmlWriter( BOOL bBuffer, INT nFlags /*= enDefault*/ )
{
	Construct( nFlags );
	if( bBuffer && FALSE == Open() )
		throw _T("Xml buffer create error");
}

CXmlWriter::~CXmlWriter()
{
	if( m_pvStream )	
		Close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlWriter::SetFlag( BOOL bEnable /*= TRUE*/, INT nType /*= enTabIndent*/ )
{
	INT nFlags = 0;
	switch( nType )
	{
	case enTabIndent:
		nFlags = enTabIndent;
		break;

	case enAttrIndent:
		nFlags = enAttrIndent;
		break;

	case enCDATAIndent:
		nFlags = enCDATAIndent;
		break;

	case enCommentIndent:
		nFlags = enCommentIndent;
		break;

	case enBufferStream:
		nFlags = enBufferStream;
		break;

	case enFileStream:
		nFlags = enFileStream;
		break;

	default:
		ASSERT( FALSE );
		return;
	}

	if( bEnable )
		m_nFlags |= nFlags;
	else
		m_nFlags &= ~nFlags;
}

BOOL CXmlWriter::IsFlagSet( INT nType /*= enTabIndent*/ )
{
	INT nFlags = 0;
	switch( nType )
	{
	case enTabIndent:
		nFlags = enTabIndent;
		break;

	case enAttrIndent:
		nFlags = enAttrIndent;
		break;

	case enCDATAIndent:
		nFlags = enCDATAIndent;
		break;

	case enCommentIndent:
		nFlags = enCommentIndent;
		break;

	case enBufferStream:
		nFlags = enBufferStream;
		break;

	case enFileStream:
		nFlags = enFileStream;
		break;

	default:
		ASSERT( FALSE );
		return FALSE;
	}

	return 0 != (m_nFlags & nFlags);
}

void CXmlWriter::SetIndentSize( INT nSize /*= 4*/, INT nType /*= enTabIndent*/ ) 
{
	switch( nType )
	{
	case enTabIndent:
		m_nTabSize = nSize; 
		break;

	case enAttrIndent:
		m_nAttrIndentSize = nSize; 
		break;

	case enCDATAIndent:
		m_nCDATAIndentSize = nSize; 
		break;

	case enCommentIndent:
		m_nCommentIndentSize = nSize;
		break;

	default:
		ASSERT( FALSE );
	}
}

INT CXmlWriter::GetIndentSize( INT nType /*= enTabIndent*/ )
{
	switch( nType )
	{
	case enTabIndent:
		return m_nTabSize;

	case enAttrIndent:
		return m_nAttrIndentSize;

	case enCDATAIndent:
		return m_nCDATAIndentSize;

	case enCommentIndent:
		return m_nCommentIndentSize;
	}

	ASSERT( FALSE );
	return -1; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Stream functions
static void _UnicodeToAnsi( CString& rcszString, char*& rpszCharArray )
{
	BSTR unicodestr = 0;

	unicodestr = rcszString.AllocSysString();
	int nLenW = ::SysStringLen( unicodestr );
	int nLenA = ::WideCharToMultiByte( CP_ACP, 0, unicodestr, nLenW, 0, 0, NULL, NULL );
	if( nLenA > 0 )
	{
		rpszCharArray = new char[nLenA + 1]; // Allocate a final null terminator as well
		::WideCharToMultiByte( CP_ACP, 0, unicodestr, nLenW, rpszCharArray, nLenA, NULL, NULL );
		rpszCharArray[nLenA] = 0; // Set the null terminator yourself
	}
	else
	{
		// Handle the error
	}

	::SysFreeString( unicodestr );
}

BOOL CXmlWriter::Open( LPCTSTR ptszFilename )
{
	m_cszFilename = ptszFilename;

	/// Should not be created
	ASSERT( NULL == m_pvStream );

	char* pszFileName = NULL;
	_UnicodeToAnsi( m_cszFilename, pszFileName );
	ASSERT( pszFileName );

	VERIFY( m_pvStream = new std::wofstream( pszFileName ) );
	delete pszFileName;

	if( NULL == m_pvStream )
		return FALSE;

	SetFlag( TRUE, enFileStream );

	return TRUE;
}

BOOL CXmlWriter::Open()
{
	/// Should not be created
	ASSERT( NULL == m_pvStream );

#ifdef UNICODE
	VERIFY( m_pvStream = new std::wstringstream );
#else // UNICODE
	VERIFY( m_pvStream = new std::stringstream );
#endif // UNICODE

	if( NULL == m_pvStream )
		return FALSE;

	SetFlag( TRUE, enBufferStream );
	return TRUE;
}

void CXmlWriter::Close()
{
	if( m_pvStream )
	{
		if( IsFlagSet( enFileStream ) )
		{
			std::wofstream* pwofStream = (std::wofstream*)m_pvStream;
			pwofStream->flush();
			pwofStream->close();
			SetFlag( FALSE, enFileStream );
		}
		else if( IsFlagSet( enBufferStream ) )
		{
#ifdef UNICODE
			std::wstringstream* pwstrStream = (std::wstringstream*)m_pvStream;
			pwstrStream->flush();
#else // UNICODE
			std::stringstream* pstrStream = (std::stringstream*)m_pvStream;
			pstrStream->flush();
#endif // UNICODE
			SetFlag( FALSE, enBufferStream );
		}
		else
		{
			ASSERT( FALSE ); // Unsupported stream
		}
	}
}

INT CXmlWriter::GetSize()
{
	if( NULL == m_pvStream )
	{
		ASSERT( FALSE );
		return -1;
	}

	if( IsFlagSet( enFileStream ) )
	{
		std::wofstream* pwofStream = (std::wofstream*)m_pvStream;
		return pwofStream->tellp();
	}

	ASSERT( IsFlagSet( enBufferStream ) );
#ifdef UNICODE
	std::wstringstream* pwstrStream = (std::wstringstream*)m_pvStream;
	return pwstrStream->tellg();
#else // UNICODE
	std::stringstream* pstrStream = (std::stringstream*)m_pvStream;
	return pstrStream->tellg();
#endif // UNICODE
}

const TCHAR* CXmlWriter::GetBuffer( INT* pnSize /*= NULL*/ )
{
	if( pnSize )
		*pnSize = -1;

	if( NULL == m_pvStream )
	{
		ASSERT( FALSE );
		return NULL;
	}

	// Valid only for string stream
	if( IsFlagSet( enFileStream ) )
	{
		ASSERT( FALSE );
		return NULL;
	}

	ASSERT( IsFlagSet( enBufferStream ) );
#ifdef UNICODE
	std::wstringstream* pwstrStream = (std::wstringstream*)m_pvStream;
	if( pnSize )
		*pnSize = pwstrStream->str().length();

	ASSERT( FALSE );	// Not Working
	return pwstrStream->str().c_str();
#else // UNICODE
	std::stringstream* pstrStream = (std::stringstream*)m_pvStream;
	if( pnSize )
		*pnSize = pstrStream->str().length();

	ASSERT( FALSE );	// Not Working
	return pstrStream->str().c_str();
#endif // UNICODE
}

void CXmlWriter::GetBuffer( CString& rcszBuffer )
{
	std::wstringstream* pStream = (std::wstringstream*)m_pvStream;
	rcszBuffer = (LPTSTR)pStream->str().c_str();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Basic data functions
void CXmlWriter::PutChar( TCHAR tch, INT nCount /*= 1*/ )
{
	ASSERT( m_pvStream );
	if( IsFlagSet( enFileStream ) )
	{
		std::wofstream* pwofStream = (std::wofstream*)m_pvStream;
		if( nCount > 1 )
		{
			for( INT i = 0; i < nCount; i++ )
				*pwofStream << tch;
		}
		else
			*pwofStream << tch;
	}

	ASSERT( IsFlagSet( enBufferStream ) );
#ifdef UNICODE
	std::wstringstream* pwstrStream = (std::wstringstream*)m_pvStream;
	if( nCount > 1 )
	{
		for( INT i = 0; i < nCount; i++ )
			*pwstrStream << tch;
	}
	else
		*pwstrStream << tch;
#else // UNICODE
	std::stringstream* pstrStream = (std::stringstream*)m_pvStream;
	if( nCount > 1 )
	{
		for( INT i = 0; i < nCount; i++ )
			*pstrStream << tch;
	}
	else
		*pstrStream << tch;
#endif // UNICODE
}

//void CXmlWriter::PutString( const TCHAR* pctsz, INT nLen /*= -1*/ )
/*{
if( -1 == nLen )
nLen = lstrlen( pctsz );

if( 0 == nLen )
return;

char* pszCharArray;
CString cszText = pctsz;

_UnicodeToAnsi( cszText, pszCharArray );

ASSERT( pszCharArray );
m_pStream->write( pszCharArray, nLen );
m_nLineCharPos += nLen;

delete pszCharArray;
}*/

void CXmlWriter::PutString( const TCHAR* pctsz, INT nLen /*= -1*/ )
{
	if( -1 == nLen )
		nLen = lstrlen( pctsz );

	if( 0 == nLen )
		return;

	for( INT i = 0; i < nLen; ++i )
	{
		PutChar( pctsz[i] );
	}

	m_nLineCharPos += nLen;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
#define _m_bIndent()			(enTabIndent == (enTabIndent & m_nFlags))
#define _m_bCDATAIndent()		(enCDATAIndent == (enCDATAIndent & m_nFlags))
#define _m_bCommentIndent()		(enCommentIndent == (enCommentIndent & m_nFlags))
#define _m_bAttrIndent()		(enAttrIndent == (enAttrIndent & m_nFlags))
#define _m_bNewline()			(enNewLine == (enNewLine & m_nFlags))
#define __m_bInsertSpace()		(enInsertSpace == (enInsertSpace & m_nFlags))
void CXmlWriter::Indent()
{
	if( FALSE == _m_bIndent() || FALSE == _m_bNewline() )
		return;

	INT nIndent = m_nIndentPos / m_nTabSize;
	for( INT i = 0; i < nIndent; i++ )
		InsertTab();

	nIndent = m_nIndentPos - nIndent * m_nTabSize;
	if( nIndent )
	{
		CString cszFormat;
		cszFormat.Format( _T("%%%ds"), nIndent, _T(" ") );
		CString cszIndent;
		cszIndent.Format( cszFormat, _T(" ") );
		PutString( cszIndent );
		m_nLineCharPos += nIndent;
	}
}

void CXmlWriter::InsertTab()
{
	if( __m_bInsertSpace() )
		PutChar( _T(' '), m_nTabSize );
	else
		PutChar( _T('\t') );

	m_nLineCharPos += m_nTabSize;
}

void CXmlWriter::InsertNewline() 
{
	m_nLineCharPos = 0;
	PutString( _T("\r\n") );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlWriter::WriteXMLStartTag( LPCTSTR ptszVersion /*= _T("1.0")*/, BOOL bCloseStartTag /*= TRUE*/ )
{
	PutString( _T("<?xml") );
	if( 0 != lstrcmp( _T("[NO]"), ptszVersion ) )
	{
		PutString( _T(" version = \"") );
		PutString( ptszVersion );
		PutString( _T("\"") );
	}

	if( bCloseStartTag )
		CloseXMLStartTag();
}

void CXmlWriter::CloseXMLStartTag() {
	PutString( _T("?>\n") ); }

void CXmlWriter::StartTag( const TCHAR* pctszID )
{
	if( _m_bIndent() )
		Indent();

	PutString( _T("<") );
	PutString( pctszID );

	/// Store tag ID for closing latter by EndStartTag()
	m_cszlTag.AddHead( pctszID );
	m_arnTagPos.Add( m_nIndentPos );
}

void CXmlWriter::Tag( const TCHAR* pctszID )
{
	if( _m_bIndent() )
	{
		Indent();
		m_arnTagPos.Add( m_nIndentPos );
		m_nIndentPos = ((m_nIndentPos + m_nTabSize) / m_nTabSize) * m_nTabSize;
	}

	PutString( _T("<") );
	PutString( pctszID );
	PutString( _T(">") );

	/// Store tag ID for closing latter by EndStartTag()
	m_cszlTag.AddHead( pctszID );

	if( _m_bNewline() )
		InsertNewline();
}

void CXmlWriter::CloseStartTag( BOOL bEndTag /*= FALSE*/ )
{
	if( bEndTag )
	{
		m_arnTagPos.RemoveAt( m_arnTagPos.GetSize() - 1 );
		m_cszlTag.RemoveHead();
		PutString( _T("/>") );
	}
	else
		PutString( _T(">") );

	if( _m_bNewline() )
		InsertNewline();

	if( FALSE == bEndTag && _m_bIndent() )
		m_nIndentPos = ((m_nIndentPos + m_nTabSize) / m_nTabSize) * m_nTabSize;
}

void CXmlWriter::EndTag()
{
	if( 0 == m_cszlTag.GetCount() )
	{
		/// No Tag
		ASSERT( FALSE );
		return;
	}

	INT nIndentIndex = m_arnTagPos.GetSize() - 1;
	if( _m_bIndent() )
	{
		m_nIndentPos = m_arnTagPos.GetAt( nIndentIndex );
		Indent();
	}

	CString& cszTag = m_cszlTag.GetHead();
	PutString( _T("</") );
	PutString( (LPCTSTR)cszTag, cszTag.GetLength() );
	PutString( _T(">") );
	m_cszlTag.RemoveHead();
	m_arnTagPos.RemoveAt( nIndentIndex );

	if( _m_bNewline() )
		InsertNewline();
}

void CXmlWriter::InsertIndent( INT nSize )
{
	INT nOldIndent = m_nIndentPos;
	m_nIndentPos += nSize;
	Indent();
	m_nIndentPos = nOldIndent;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlWriter::Attribute( const TCHAR* pctszName, const TCHAR* pctszValue )
{
	if( NULL == pctszName || NULL == pctszValue )
		return;

	if( _m_bAttrIndent() && _m_bIndent() && m_nLineCharPos >= m_nLineSize )
	{
		InsertNewline();
		InsertIndent( m_nAttrIndentSize );
	}
	else
		PutString( _T(" ") );

	PutString( pctszName );
	PutString( _T("=\"") );

	CString csz;
	for( ;*pctszValue; pctszValue++ ) 
	{
		switch( *pctszValue )
		{
		case _T('<'):
			csz += _T("&lt;");
			break;

		case _T('>'):
			csz += _T("&gt;");
			break;

		case _T('&'):
			csz += _T("&amp;");
			break;

		case _T('"'):
			csz += _T("&quot;");
			break;

		case _T('\''):
			csz += _T("&apos;");
			break;

		default:
			csz += *pctszValue;
		}
	}

	PutString( csz, csz.GetLength() );
	PutString( _T("\"") );
}

void CXmlWriter::Text( const TCHAR* pctsz, INT nLen /*= -1*/ )
{
	if( _m_bIndent() )
		Indent();

	CString csz;
	for( ;*pctsz && nLen; pctsz++, nLen-- )
	{
		switch( *pctsz )
		{
		case  _T('<'): csz += _T("&lt;");		break;
		case  _T('&'): csz += _T("&amp;");		break;
		case  _T('>'): csz += _T("&gt;");		break;
		case _T('\''): csz += _T("&apos;");		break;
		case  _T('"'): csz += _T("&quot;");		break;
		case  _T('®'): csz += _T("&#xAE;");		break;
		case  _T('£'): csz += _T("&#xA3;");		break;
		case  _T('™'): csz += _T("&#x2122;");	break;
		case  _T('€'): csz += _T("&#x20AC;");	break;
		case  _T('´'): csz += _T("&#xB4;");		break;

		case  _T('¢'): csz += _T("&#xA2;");		break;
		case  _T('©'): csz += _T("&#xA9;");		break;
		case  _T('°'): csz += _T("&#xB0;");		break;
		case  _T('·'): csz += _T("&#xB7;");		break;
		case  _T('¾'): csz += _T("&#xBE;");		break;
		case  _T('Å'): csz += _T("&#xC5;");		break;
		case  _T('Ì'): csz += _T("&#xCC;");		break;
		case  _T('Ó'): csz += _T("&#xD3;");		break;
		case  _T('Ú'): csz += _T("&#xDA;");		break;
		case  _T('á'): csz += _T("&#xE1;");		break;
		case  _T('è'): csz += _T("&#xE8;");		break;
		case  _T('ï'): csz += _T("&#xEF;");		break;
			///		case  _T(' '): csz += _T("&#x20;");		break;
			///		case  _T('^'): csz += _T("&#x5E;");		break;
			///		case  _T('™'): csz += _T("&#x80;");		break;
			///		case  _T('™'): csz += _T("&#x87;");		break;
			///		case  _T('™'): csz += _T("&#x8E;");		break;
			///		case  _T('™'): csz += _T("&#x95;");		break;
			///		case  _T('™'): csz += _T("&#x9C;");		break;
		case  _T('ª'): csz += _T("&#xAA;");		break;
		case  _T('±'): csz += _T("&#xB1;");		break;
		case  _T('¸'): csz += _T("&#xB8;");		break;
		case  _T('¿'): csz += _T("&#xBF;");		break;
		case  _T('Æ'): csz += _T("&#xC6;");		break;
		case  _T('Í'): csz += _T("&#xCD;");		break;
		case  _T('Ô'): csz += _T("&#xD4;");		break;
		case  _T('Û'): csz += _T("&#xDB;");		break;
		case  _T('â'): csz += _T("&#xE2;");		break;
		case  _T('é'): csz += _T("&#xE9;");		break;
		case  _T('ð'): csz += _T("&#xF0;");		break;
			///		case  _T('#'): csz += _T("&#x23;");		break;
		case  _T('`'): csz += _T("&#x60;");		break;
			///		case  _T('™'): csz += _T("&#x81;");		break;
			///		case  _T('™'): csz += _T("&#x88;");		break;
			///		case  _T('™'): csz += _T("&#x8F;");		break;
			///		case  _T('™'): csz += _T("&#x96;");		break;
			///		case  _T('™'): csz += _T("&#x9D;");		break;
		case  _T('¤'): csz += _T("&#xA4;");		break;
		case  _T('«'): csz += _T("&#xAB;");		break;
		case  _T('²'): csz += _T("&#xB2;");		break;
		case  _T('¹'): csz += _T("&#xB9;");		break;
		case  _T('À'): csz += _T("&#xC0;");		break;
		case  _T('Ç'): csz += _T("&#xC7;");		break;
		case  _T('Î'): csz += _T("&#xCE;");		break;
		case  _T('Õ'): csz += _T("&#xD5;");		break;
		case  _T('Ü'): csz += _T("&#xDC;");		break;
		case  _T('ã'): csz += _T("&#xE3;");		break;
		case  _T('ê'): csz += _T("&#xEA;");		break;
		case  _T('ñ'): csz += _T("&#xF1;");		break;
			///		case  _T('$'): csz += _T("&#x24;");		break;
			///		case  _T('{'): csz += _T("&#x7B;");		break;
			///		case  _T('™'): csz += _T("&#x82;");		break;
			///		case  _T('™'): csz += _T("&#x89;");		break;
			///		case  _T('™'): csz += _T("&#x90;");		break;
			///		case  _T('™'): csz += _T("&#x97;");		break;
			///		case  _T('™'): csz += _T("&#x9E;");		break;
		case  _T('¥'): csz += _T("&#xA5;");		break;
		case  _T('¬'): csz += _T("&#xAC;");		break;
		case  _T('³'): csz += _T("&#xB3;");		break;
		case  _T('º'): csz += _T("&#xBA;");		break;
		case  _T('Á'): csz += _T("&#xC1;");		break;
		case  _T('È'): csz += _T("&#xC8;");		break;
		case  _T('Ï'): csz += _T("&#xCF;");		break;
		case  _T('Ö'): csz += _T("&#xD6;");		break;
		case  _T('Ý'): csz += _T("&#xDD;");		break;
		case  _T('ä'): csz += _T("&#xE4;");		break;
		case  _T('ë'): csz += _T("&#xEB;");		break;
		case  _T('ò'): csz += _T("&#xF5;");		break;

		case  _T('ó'): csz += _T("&#xF3;");		break;
		case  _T('ú'): csz += _T("&#xFA;");		break;
		case  _T('ô'): csz += _T("&#xF4;");		break;
		case  _T('û'): csz += _T("&#xFB;");		break;
		case  _T('õ'): csz += _T("&#xF5;");		break;
		case  _T('ü'): csz += _T("&#xFC;");		break;
		case  _T('ù'): csz += _T("&#xF9;");		break;
		case  _T('ö'): csz += _T("&#xF6;");		break;
		case  _T('ý'): csz += _T("&#xFD;");		break;
		case  _T('÷'): csz += _T("&#xF7;");		break;
		case  _T('þ'): csz += _T("&#xFE;");		break;
		case  _T('ø'): csz += _T("&#xF8;");		break;
		case  _T('ÿ'): csz += _T("&#xFF;");		break;
		default:	   csz += *pctsz;
		}
	}

	PutString( csz, csz.GetLength() );

	if( _m_bNewline() )
		InsertNewline();
}

void CXmlWriter::Comment( const TCHAR* pctszComment )
{
	ASSERT( pctszComment );
	if( _m_bIndent() )
		Indent();

	PutString( _T("<!-- ") );

	if( _m_bCommentIndent() && _m_bIndent() )
	{
		BOOL bFirstLine = TRUE;

		TCHAR* pctsz = const_cast<TCHAR*>(pctszComment);
		INT nLineCharPos = m_nLineCharPos;
		INT nLen;
		for( nLen = 0; *pctszComment; pctszComment++, nLen++, nLineCharPos++ )
		{
			if( nLineCharPos >= m_nLineSize )
			{
				switch( *pctszComment )
				{
				case _T('\r'):
					if( *(pctszComment + 1) && _T('\n') == *(pctszComment + 1) )
						pctszComment++;
				case _T('\n'):
				case _T(' '):
					if( FALSE == bFirstLine )
						InsertIndent( m_nCommentIndentSize );

					PutString( pctsz, nLen );
					InsertNewline();

					pctsz = const_cast<TCHAR*>(pctszComment + 1);
					nLen = -1;
					nLineCharPos = m_nLineCharPos + m_nCommentIndentSize;
					bFirstLine = FALSE;
					break;
				}
			}
		}

		if( nLen )
		{
			if( FALSE == bFirstLine )
				InsertIndent( m_nCommentIndentSize );

			PutString( pctsz, nLen );
		}
	}
	else
		PutString( pctszComment );

	//PutString( pctszComment );
	PutString( _T(" --> ") );
	InsertNewline();
}

void CXmlWriter::CDATA( const TCHAR* pctszData )
{
	ASSERT( pctszData );

	if( _m_bCDATAIndent() && _m_bIndent() )
		Indent();

	PutString( _T("<![CDATA[") );
	InsertNewline();

	if( _m_bCDATAIndent() && _m_bIndent() )
	{
		TCHAR* pctsz = const_cast<TCHAR*>(pctszData);
		INT nLen;
		for( nLen = 0; *pctszData; pctszData++, nLen++ )
		{
			if( _T('\r') == *pctszData )
			{
				if( *(pctszData + 1) && _T('\n') == *(pctszData + 1) )
					pctszData++;
			}
			else if( _T('\n') != *pctszData )
				continue;

			InsertIndent( m_nCDATAIndentSize );
			PutString( pctsz, nLen );
			InsertNewline();
			pctsz = const_cast<TCHAR*>(pctszData + 1);
			nLen = -1;
		}

		if( nLen )
		{
			InsertIndent( m_nCDATAIndentSize );
			PutString( pctsz, nLen );
		}
	}
	else
		PutString( pctszData );

	InsertNewline();
	if( _m_bCDATAIndent() && _m_bIndent() )
		Indent();

	PutString( _T("]]>") );
	InsertNewline();
}
