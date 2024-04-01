#ifndef __FILE_IMPORT__PH___
#define __FILE_IMPORT__PH___

#include <g\type\idom\giNode.h>

class GDOM_EXT_CLASS CGIFileImport : public CGObject
{
public:
	CGIFileImport();
	CGIFileImport( LPCTSTR pctszFileName );
	virtual ~CGIFileImport();

public:
	virtual BOOL Open( LPCTSTR pctszFileName );
	virtual BOOL Open();
	virtual BOOL Read();
	virtual BOOL Close();

	CGINode* GetRootNode() const;

protected:
	CGINode*	m_pRootNode;
	CString		m_cszFileName;
};

inline CGINode* CGIFileImport::GetRootNode() const {
	return m_pRootNode; }

#endif //!___FILE_IMPORT__PH___