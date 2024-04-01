#ifndef ___XML_WRITER__PH___
#define ___XML_WRITER__PH___

class IXmlWriter
{
public:
	/// Stream functions
	virtual BOOL Open( LPCTSTR ptszFilename ) = 0;
	virtual BOOL Open() = 0;
	virtual void Close() = 0;

	virtual INT GetSize() = 0;
	virtual const TCHAR* GetBuffer( INT* pnSize = NULL ) = 0;

	/// Tag functions
	virtual void StartTag( const TCHAR* pctszID ) = 0;
	virtual void Tag( const TCHAR* pctszID ) = 0;

	virtual void CloseStartTag( BOOL bEndTag = FALSE ) = 0;
	virtual void EndTag() = 0;

	/// Attribute functions
	virtual void Attribute( const TCHAR* pctszName, const TCHAR* pctszValue ) = 0;
	virtual void Text( const TCHAR* pctsz, INT nLen = -1 ) = 0;

	virtual void Comment( const TCHAR* pctszComment ) = 0;
	virtual void CDATA( const TCHAR* pctszData ) = 0;

protected:
	void*		m_pvStream;
};

/// The class CXmlWriter provides the functionality for writing XML file 
/// This has functions of 
///		#. Stream - File / String stream
///		#. Controlling Indentation,
///		#. Automatic newline character append
///		#. Basic data type - Char, String
///		#. XML Tag - Start tag, simple tag
///		#. XML Attribute
///     #. XML Text
///		#. XML CDATA
class CU_EXT_CLASS CXmlWriter : public IXmlWriter
{
public:
	enum {
		enNone,
		enTabIndent			= 1,
		enAttrIndent		= 2,
		enCDATAIndent		= 4,
		enCommentIndent		= 8,
		enNewLine			= 16,

		enInsertSpace		= 32,
		enBufferStream		= 64,
		enFileStream		= 128,

		enDefault			= enTabIndent | enAttrIndent | enCDATAIndent | enCommentIndent | enNewLine | enInsertSpace,
	};

	CXmlWriter( INT nFlags = enDefault );
	CXmlWriter( LPCTSTR ptszFilename, INT nFlags = enDefault );
	CXmlWriter( BOOL bBuffer, INT nFlags = enDefault );
	virtual ~CXmlWriter();

	void Construct( INT nFlags );

	/// Stream functions
	BOOL Open( LPCTSTR ptszFilename );
	BOOL Open();
	void Close();

	INT GetSize();
	const TCHAR* GetBuffer( INT* pnSize = NULL );
	void GetBuffer( CString& rcszBuffer );

	/// Controller functions
	void SetFlag( BOOL bEnable = TRUE, INT nType = enTabIndent );
	BOOL IsFlagSet( INT nType = enTabIndent );

	void SetLineSize( INT nSize = 80 );
	INT GetLineSize();

	void OffsetIndent( INT nIndent );
	void SetIndent( INT nIndent );
	INT GetIndent();

	void SetIndentSize( INT nSize = 4, INT nType = enTabIndent );
	INT GetIndentSize( INT nType = enTabIndent );

	/// Basic data functions
	void PutChar( TCHAR tch, INT nCount = 1 );
	void PutString( const TCHAR* pctsz, INT nLen = -1 );

	void Indent();
	void InsertIndent( INT nSize );
	void InsertTab();
	void InsertNewline();

	/// Tag functions
	void WriteXMLStartTag( LPCTSTR ptszVersion = _T("1.0"), BOOL bCloseStartTag = TRUE );
	void CloseXMLStartTag();
	void StartTag( const TCHAR* pctszID );
	void Tag( const TCHAR* pctszID );

	void CloseStartTag( BOOL bEndTag = FALSE );
	void EndTag();

	/// Attribute functions
	void Attribute( const TCHAR* pctszName, const TCHAR* pctszValue );
	void Text( const TCHAR* pctsz, INT nLen = -1 );

	void Comment( const TCHAR* pctszComment );
	void CDATA( const TCHAR* pctszData );

protected:
	INT			m_nFlags;

	INT			m_nLineSize;
	INT			m_nCDATAIndentSize;
	INT			m_nAttrIndentSize;
	INT			m_nCommentIndentSize;
	INT			m_nTabSize;

	INT			m_nIndentPos;
	INT			m_nLineCharPos;

	CUIntArray	m_arnTagPos;
	CStringList m_cszlTag;

	CString		m_cszFilename;
};

inline void CXmlWriter::SetLineSize( INT nSize /*= 80*/ ) {
	m_nLineSize = nSize; }

inline INT CXmlWriter::GetLineSize() {
	return m_nLineSize; }

inline void CXmlWriter::OffsetIndent( INT nIndent )  {
	m_nIndentPos += nIndent;  }

inline void CXmlWriter::SetIndent( INT nIndent ) {
	m_nIndentPos += nIndent; }

inline INT CXmlWriter::GetIndent() {
	return m_nIndentPos; }

#endif //!___XML_WRITER__PH___