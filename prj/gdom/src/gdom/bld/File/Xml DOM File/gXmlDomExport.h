#ifndef __G_DOM_XML_EXPORT__PH___
#define __G_DOM_XML_EXPORT__PH___

#include <bld\File\FileExport.h>
#include <cu\XmlWriter.h>

class CGIDomNodeImport;
class GDOM_EXT_CLASS CGIXmlDomExport : public CGIFileExport
{
public:
	CGIXmlDomExport( CGINode& rNode );
	CGIXmlDomExport( CGINode& rNode, LPCTSTR pctszFileName );
	overrided ~CGIXmlDomExport();

public:
	using CGIFileExport::Open;
	overrided BOOL Open( LPCTSTR pctszFileName );
	overrided BOOL Write();
	overrided BOOL Close();

	CXmlWriter* GetXmlWriter();

	void WriteNodeAttriute( CGINode& rNode );
	void WriteNode( CGINode& rNode );

protected:
	CXmlWriter	m_xmlWriter;
};

inline CXmlWriter* CGIXmlDomExport::GetXmlWriter() {
	return &m_xmlWriter; }

#endif //!___G_DOM_XML_EXPORT__PH___