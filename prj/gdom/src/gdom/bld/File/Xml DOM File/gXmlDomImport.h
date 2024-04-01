#ifndef __G_DOM_XML_IMPORT__PH___
#define __G_DOM_XML_IMPORT__PH___

#include <bld\File\FileImport.h>
#include <cu\XmlReader.h>

class CGIDomNodeImport;
class GDOM_EXT_CLASS CGIXmlDomImport : public CGIFileImport, public CGFactoryObject
{
public:
	CGIXmlDomImport();
	CGIXmlDomImport( LPCTSTR pctszFileName );
	virtual ~CGIXmlDomImport();

public:
	virtual BOOL Open( LPCTSTR pctszFileName );
	virtual BOOL Open();
	virtual BOOL Read();
	virtual BOOL Close();

	CXmlReader* GetXmlReader();
	CGIDomNodeImport* CreateNodeImport( const CString& rcszTagName );
	CGINode* CreateNode( const CString& rcszTagName );

	virtual BOOL ReadNode( CGINode& rParentNode );
	virtual BOOL ReadChildren( CGINode& rParentNode );

	overrided void LockObjectLink( BOOL bLock = TRUE );
	overrided CGFactoryObject* GetFactoryObjectParent();

protected:
	CXmlReader	m_xmlReader;
};

inline CXmlReader* CGIXmlDomImport::GetXmlReader() {
	return &m_xmlReader; }

inline void CGIXmlDomImport::LockObjectLink( BOOL bLock /*= TRUE*/ ) 
{}

inline CGFactoryObject* CGIXmlDomImport::GetFactoryObjectParent() {
	return NULL; }

#endif //!___G_DOM_XML_IMPORT__PH___