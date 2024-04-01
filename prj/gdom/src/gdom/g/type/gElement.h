#ifndef ___G_ELEMENT__PH___
#define ___G_ELEMENT__PH___

#include "idom\giElement.h"
class CAttr;

class CGElement : public CGNode
{
public:
    CGElement();
    CGElement( const CGElement& rElement );

private:
    CGElement( CGIElement* piElement );

public:
    CGElement& operator=( const CGElement& rElement );

public:
    ///{{ DOM ////////////////////////////////////////////////////////////////////
   // DOM read only attributes
    CString GetTagName() const;
	void GetTagName( CString& rcszTageName ) const;

    CString GetAttribute( LPCTSTR pctszName ) const;
	BOOL GetAttribute( CString& rcszValue, LPCTSTR pctszName ) const;

    BOOL SetAttribute( LPCTSTR pctszName, const CString& rcszValue );
	BOOL SetAttribute( LPCTSTR pctszName, LPCTSTR pctszValue );

    void RemoveAttribute( LPCTSTR pctszName );

    CGAttr GetAttributeNode( LPCTSTR pctszName );
    CGAttr SetAttributeNode( const CGAttr& rAttr );
    CGAttr RemoveAttributeNode( const CGAttr& rOldAttr );

    CGNodeList GetElementsByTagName( LPCTSTR pctsName ) const;

    CString GetttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszDefValue = NULL ) const;
	BOOL GetAttributeNS( CString& rcszValue, LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszDefValue = NULL ) const;

    BOOL SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, const CString& rcszValue );
	BOOL SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszValue );

    void RemoveAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName );

    CGAttr GetAttributeNodeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName );
    CGAttr SetAttributeNodeNS( const CGAttr& rAttr );
    CGAttr RemoveAttributeNodeNS( const CGAttr& rOldAttr );

    CGNodeList GetElementsByTagNameNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName ) const;

    BOOL HasAttribute( LPCTSTR pctszName ) const;
    BOOL HasAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName ) const;

	// Introduced in DOM Level 3:
	//readonly attribute TypeInfo schemaTypeInfo;

	// Introduced in DOM Level 3:
	void SetIdAttribute( LPCTSTR pctszName, BOOL bIsID );

	// Introduced in DOM Level 3:
	void SetIdAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, BOOL bIsID );

	// Introduced in DOM Level 3:
	void SetIdAttributeNode( CGIAttr& rAttr, BOOL bIsID );
	///}} DOM ////////////////////////////////////////////////////////////////////

	/// Reimplemented from CGNode
    CGNode::ENodeType GetNodeType() const;

	///{{ Customsized DOM ////////////////////////////////////////////////////////
    void SetAttribute( LPCTSTR pctszName, LONGLONG llValue );

    void SetAttribute( LPCTSTR pctszName, INT nValue );
	void SetAttribute( LPCTSTR pctszName, UINT unValue );

    void SetAttribute( LPCTSTR pctszName, FLOAT fValue );
	void SetAttribute( LPCTSTR pctszName, double dfValue );

    void SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LONGLONG llValue );

    void SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, INT nValue );
	void SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, UINT unValue );

    void SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, FLOAT fValue );
	void SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, double dfValue );
	///}} Customsized DOM ////////////////////////////////////////////////////////

    friend class CGDocument;
    friend class CGNode;
    friend class CGAttr;
};

inline CGNode::ENodeType CGElement::GetNodeType() const {
	return CGNode::ELEMENT_NODE; }

#endif //!___G_ELEMENT__PH___
