#ifndef ___G_I_NODE_LIST_PH___
#define ___G_I_NODE_LIST_PH___

#include <gbase\gObject.h>

class CGINode;

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGINodeList : public CGObject
{
public:
    CGINodeList( CGINode* piNode );
    CGINodeList( CGINode* piNode, LPCTSTR ptszTagName );
    CGINodeList( CGINode* piNode, LPCTSTR ptszNsURI, LPCTSTR ptszLocalName );
    ~CGINodeList();

public:
    BOOL operator==( const CGINodeList& ) const;
    BOOL operator!=( const CGINodeList& ) const;

    void CreateList();
    CGINode* GetItem( INT nIndex );
    UINT GetLength() const;
	const CGINode** GetList() const;
	CGINode** GetList();

#ifdef _DEBUG
	overrided void Dump( CDumpContext& dc ) const;
#endif

public:
    CGINode*					m_piNode;
    CString						m_cszTagname;
    CString						m_cszNSURI;
	CArray<CGINode*, CGINode*>	m_arrList;
    LONG						m_lTimeStamp;

public:
	static long					m_lNodeListTime;
};

inline const CGINode** CGINodeList::GetList() const {
	return (const CGINode**)((CGINodeList*)this)->GetList(); }

#endif //!___G_I_NODE_LIST_PH___
