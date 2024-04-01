#ifndef ___G_I_NODE_MAP_PH___
#define ___G_I_NODE_MAP_PH___

#include <gbase\gObject.h>
class CGINode;
class CGIDocumentType;

class GDOM_EXT_CLASS CGINamedNodeMap : public CGObject
{
public:
    CGINamedNodeMap( CGINode* piNode );
    ~CGINamedNodeMap();

public:
    CGINode* GetNamedItem( LPCTSTR ptszName ) const;
    CGINode* GetNamedItemNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName ) const;
	static CGINode* GetNamedItemNS( const CMapStringToPtr& rmapStrToNode, LPCTSTR ptszNsURI, LPCTSTR ptszLocalName );

    CGINode* SetNamedItem( CGINode* piNode );
    CGINode* SetNamedItemNS( CGINode* piNode );

    CGINode* RemoveNamedItem( LPCTSTR ptszName );

    CGINode* GetItem( INT nIndex ) const;
    UINT GetLength() const;
    BOOL FindItem( LPCTSTR ptszName ) const;
    BOOL FindItemNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName ) const;

    void ClearMap();
    BOOL IsReadOnly();
    void SetReadOnly( BOOL bReadonly );
    BOOL IsAppendToParent();

    /// If true, then the node will redirect insert/remove calls
    /// to its m_piParentNode by calling CGINode::appendChild or removeChild.
    /// In addition the map wont increase or decrease the reference count
    /// of the nodes it contains.
    ///
	/// By default this value is FALSE and the map will handle reference counting
    /// by itself.
    void SetAppendToParent( BOOL bAppend );

    /// Creates a copy of the map. It is a deep copy
    /// that means that all children are cloned.
    CGINamedNodeMap* Clone( CGINode* piParentNode );

public:
	CMapStringToPtr				m_mapNameToNode;

protected:
	//CMapStringToPtr				m_mapNameToNode;
    CGINode*					m_piParentNode;
    BOOL						m_bReadonly;
    BOOL						m_bAppendToParent;

	friend CGIDocumentType;
};

inline BOOL CGINamedNodeMap::IsReadOnly() { 
	return m_bReadonly; }

inline void CGINamedNodeMap::SetReadOnly( BOOL bReadonly ) { 
	m_bReadonly = bReadonly; }

inline BOOL CGINamedNodeMap::IsAppendToParent() { 
	return m_bAppendToParent; }

inline void CGINamedNodeMap::SetAppendToParent( BOOL bAppend ) { 
	m_bAppendToParent = bAppend; }

#endif //!___G_I_NODE_MAP_PH___
