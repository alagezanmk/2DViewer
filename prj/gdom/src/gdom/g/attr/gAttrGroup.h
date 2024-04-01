#ifndef ___G_ATTR_GROUP__PH___
#define ___G_ATTR_GROUP__PH___

#include <g\type\idom\giNodeMap.h>
#include "gAttr.h"
#include "gAttrTypes.h"

class CGIElement;
class CGINamedAttrMap;

///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGIAttrGroup : public CGINode
{
	DECL_GTPYECLASS_DYNCREATE(CGIAttrGroup)
public:
	CGIAttrGroup();
	CGIAttrGroup( LPCTSTR pctszName );
	virtual ~CGIAttrGroup();

public:
	void SetName( LPCTSTR pctszName, INT nLength = 0 );

	CString GetGroupName() const;
	void GetGroupName( CString& rcsName ) const;

	virtual BOOL IsRootGroup() const;

	CGIAttrGroup* GetAttributeGroup( LPCTSTR pctszName );
	CGIAttrGroup* CreateAttributeGroup( LPCTSTR pctszName );

	///{{ Reimplemented
	overrided INT GetNodeType() const;
	virtual LPCTSTR GetName() const;
	virtual void InitializeAttributes();

protected:
	overrided void Attach( CGEventNode& rNode );
	overrided void Detach( CGEventNode& rNode );
	///}} Reimplemented

protected:
	CGIElement*			m_pElement;
	BOOL				m_bAttrInited;

	friend CGINamedAttrMap;
};

inline LPCTSTR CGIAttrGroup::GetName() const {
	return m_cszName; }

inline BOOL CGIAttrGroup::IsRootGroup() const {
	return FALSE; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGIRootAttrGroup : public CGIAttrGroup
{
public:
	overrided BOOL IsRootGroup() const;
};

inline BOOL CGIRootAttrGroup::IsRootGroup() const {
	return TRUE; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGINamedAttrMap : public CGINamedNodeMap
{
public:
	static const TCHAR GROUP_CHAR;

public:
	CGINamedAttrMap();
	virtual ~CGINamedAttrMap();

public:
	CGIElement* GetElement();
	const CGIElement* GetElement() const;

	/// Get an attribute node
	CGIAttr* GetAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL );
	const CGIAttr* GetAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL ) const;
	
	CGIAttr* operator[]( LPCTSTR pctszName );
	const CGIAttr* operator[]( LPCTSTR pctszName ) const;

	/// Add an attribute node
	CGIAttr* AddAttributeNode( CGIAttr& rAttr );
	CGIAttr* AddAttributeNode( CGIAttr& rAttr, LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL, BOOL bGroupedNaming = FALSE );

	/// Remove an attribute node
	CGIAttr* RemoveAttributeNode( CGIAttr& rAttr );
	CGIAttr* RemoveAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL );

	/// Get an attribute group
	CGIAttrGroup* GetAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL );
	const CGIAttrGroup* GetAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL ) const;

	/// Add an attribute group
	CGIAttrGroup* AddAttributeGroup( CGIAttrGroup& rAttrGroup );
	CGIAttrGroup* AddAttributeGroup( CGIAttrGroup& rAttrGroup, LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL );

	/// Remove an attribute group
	CGIAttrGroup* RemoveAttributeGroup( CGIAttrGroup& rAttrGroup );
	CGIAttrGroup* RemoveAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL );

	///{ Name space Support
	/// Get a NS attribute node
	CGIAttr* GetAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName = NULL );
	const CGIAttr* GetAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName = NULL ) const;

	/// Add a NS attribute node
	CGIAttr* AddAttributeNodeNS( CGIAttr& rAttr, LPCTSTR pctszGroupName = NULL, BOOL bGroupedNaming = FALSE );
	CGIAttr* AddAttributeNodeNS( CGIAttr& rAttr, LPCTSTR ptszNsURI, LPCTSTR pctszQualifiedName, LPCTSTR pctszGroupName = NULL, BOOL bGroupedNaming = FALSE );

	/// Remove a NS attribute node
	CGIAttr* RemoveAttributeNodeNS( CGIAttr& rAttr );
	CGIAttr* RemoveAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName = NULL );

	/// Get an attribute group
	CGIAttrGroup* GetAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName = NULL );
	const CGIAttrGroup* GetAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName = NULL ) const;

	/// Add a NS attribute group
	CGIAttrGroup* AddAttributeGroupNS( CGIAttrGroup& rAttrGroup, LPCTSTR pctszGroupName = NULL );
	CGIAttrGroup* AddAttributeGroupNS( CGIAttrGroup& rAttrGroup, LPCTSTR ptszNsURI, LPCTSTR pctszQualifiedName, LPCTSTR pctszGroupName = NULL );

	/// Remove a NS attribute group
	CGIAttrGroup* RemoveAttributeGroupNS( CGIAttrGroup& rAttrGroup );
	CGIAttrGroup* RemoveAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName = NULL );
	///} Name space Support

	BOOL IsAttributeNode( const CGIAttr& rAttr ) const;

	BOOL HasAttributes() const;
	BOOL HasAttribute( LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL ) const;
	BOOL HasAttributeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName = NULL ) const;

	BOOL HasAttributesGroup() const;
	BOOL HasAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL ) const;
	BOOL HasAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName = NULL ) const;

	void SetRootGroupName( LPCTSTR pctszName );
	LPCTSTR GetRootGroupName();

	CGIAttrGroup& GetRootGroup();
	const CGIAttrGroup& GetRootGroup() const;

	void RemoveAll();
	void RemoveAll( CGIAttrGroup& rGroup );

	virtual BOOL OnInitialUpdate();

public:
	CMapStringToPtr		m_mapNameToGroup;

protected:
	CGIElement*			m_pElement;
	CGIAttrGroup		m_aGeneral;
	CGIRootAttrGroup	m_aRoot;

	//CMapStringToPtr		m_mapNameToGroup;

	friend CGIElement;
};

inline CGIElement* CGINamedAttrMap::GetElement() {
	return m_pElement; }

inline const CGIElement* CGINamedAttrMap::GetElement() const {
	return m_pElement; }

inline CGIAttr* CGINamedAttrMap::operator[]( LPCTSTR pctszName ) {
	return GetAttributeNode( pctszName ); }

inline const CGIAttr* CGINamedAttrMap::operator[]( LPCTSTR pctszName ) const {
	return GetAttributeNode( pctszName ); }

inline BOOL CGINamedAttrMap::IsAttributeNode( const CGIAttr& rAttr ) const {
	return m_aRoot.IsChildNode( rAttr, TRUE ); }

inline BOOL CGINamedAttrMap::HasAttributes() const {
	return 0 != m_mapNameToNode.GetCount(); }

inline BOOL CGINamedAttrMap::HasAttributesGroup() const {
	return 0 != m_mapNameToGroup.GetCount(); }

inline const CGIAttr* CGINamedAttrMap::GetAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName /*= NULL*/ ) const {
	return (const CGIAttr*)((CGINamedAttrMap*)this)->GetAttributeNode( pctszName, pctszGroupName ); }

inline CGIAttrGroup& CGINamedAttrMap::GetRootGroup() {
	return m_aRoot; }

inline const CGIAttrGroup& CGINamedAttrMap::GetRootGroup() const {
	return m_aRoot; }

inline LPCTSTR CGINamedAttrMap::GetRootGroupName() {
	return m_aGeneral.GetName(); }

inline void CGINamedAttrMap::SetRootGroupName( LPCTSTR pctszName ) {
	m_aGeneral.SetName( pctszName ); }

#endif //!___G_ATTR_GROUP__PH___
