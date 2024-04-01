#ifndef __FILE_EXPORT__PH___
#define __FILE_EXPORT__PH___

#include <g\type\idom\giNode.h>

class GDOM_EXT_CLASS CGIFileExport : public CGObject
{
public:
	CGIFileExport( CGINode& rNode );
	CGIFileExport( CGINode& rNode, LPCTSTR pctszFileName );
	virtual ~CGIFileExport();

public:
	virtual BOOL Open( LPCTSTR pctszFileName );
	virtual BOOL Open();
	virtual BOOL Write();
	virtual BOOL Close();

	CGINode* GetRootNode() const;

protected:
	CGINode*	m_pRootNode;
	CString		m_cszFileName;
};

inline CGINode* CGIFileExport::GetRootNode() const {
	return m_pRootNode; }

#endif //!___FILE_EXPORT__PH___