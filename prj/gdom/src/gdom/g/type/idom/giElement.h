#ifndef ___G_I_ELEMENT__PH___
#define ___G_I_ELEMENT__PH___

#include <g\attr\gAttrGroup.h>
#include "giNode.h"
#include "gUI.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
class CGSaveTransform
{
public:
	CGSaveTransform( Graphics& rGdip );
	~CGSaveTransform();

protected:
	Graphics&	m_rGdip;
	FLOAT		m_arfTransform[6];
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGIElement : public CGINode, public CGUI
{
public:
	DECL_GTPYECLASS_DYNCREATE(CGIElement)

public:
	static LPCTSTR ELEMENT_TAGNAME;

public:
	CGIElement();

protected:
	virtual ~CGIElement();
	virtual void InitializeAttributes();

public:
	///{{ DOM Methods
	LPCTSTR GetTagName() const;
	void GetTagName( CString& rcszTagName ) const;

	BOOL GetAttribute( CString& rcszValue, LPCTSTR pctszName ) const;
	CString GetAttribute( LPCTSTR pctszName ) const;

	BOOL SetAttribute( LPCTSTR pctszName, LPCTSTR pctszValue );
	BOOL SetAttribute( LPCTSTR pctszName, const CString& rcszValue );

	CGIAttr* RemoveAttributeNode( LPCTSTR pctszName );

	CGIAttr* GetAttributeNode( LPCTSTR pctszName );
	const CGIAttr* GetAttributeNode( LPCTSTR pctszName ) const;

	CGIAttr* SetAttributeNode( CGIAttr& rAttr );
	CGIAttr* RemoveAttributeNode( CGIAttr& rOldAttr );

	CGINodeList* GetElementsByTagName( LPCTSTR pctszName );

	// Introduced in DOM Level 2:
	BOOL GetAttributeNS( CString& rcszValue, LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszDefValue = NULL ) const;
	CString GetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszDefValue = NULL ) const;

	// Introduced in DOM Level 2:
	BOOL SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, LPCTSTR pctszValue );
	BOOL SetAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, const CString& rcszValue );

	// Introduced in DOM Level 2:
	CGIAttr* RemoveAttributeNodeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName );

	// Introduced in DOM Level 2:
	CGIAttr* GetAttributeNodeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName );

	// Introduced in DOM Level 2:
	CGIAttr* SetAttributeNodeNS( CGIAttr& rAttr );

	// Introduced in DOM Level 2:
	CGINodeList* GetElementsByTagNameNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName );

	// Introduced in DOM Level 2:
	BOOL HasAttribute( LPCTSTR pctszName ) const;

	// Introduced in DOM Level 2:
	BOOL HasAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName ) const;

	// Introduced in DOM Level 3:
	//readonly attribute TypeInfo schemaTypeInfo;

	// Introduced in DOM Level 3:
	BOOL SetIdAttribute( LPCTSTR pctszName, BOOL bIsID );

	// Introduced in DOM Level 3:
	BOOL SetIdAttributeNS( LPCTSTR pctszNsURI, LPCTSTR pctszLocalName, BOOL bIsID );

	// Introduced in DOM Level 3:
	BOOL SetIdAttributeNode( CGIAttr& rAttr, BOOL bIsID );
	///}} DOM Methods

	///{{ Reimplemented
	virtual BOOL OnInitialUpdate();
	overrided void HandleEvent( CGEvent& rEvent );

	overrided INT GetNodeType() const;

	CGINamedNodeMap* GetAttributes();

	virtual LPCTSTR GetNameSpaceURI() const;
	virtual void GetNameSpaceURI( CString& rcszameSpaceURI ) const;

	// Introduced in DOM Level 2:
	virtual LPCTSTR GetPrefix() const;
	virtual void GetPrefix( CString& rcszPrefix ) const;

	virtual BOOL HasAttributes() const;
	///}} Reimplemented

	///{{ Customized DOM attribute functions
	/// Get an attribute node
	CGIAttr* GetAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName );
	const CGIAttr* GetAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName ) const;
	
	CGIAttr* operator[]( LPCTSTR pctszName );
	const CGIAttr* operator[]( LPCTSTR pctszName ) const;

	/// Add an attribute node
	CGIAttr* AddAttributeNode( CGIAttr& rAttr );
	CGIAttr* AddAttributeNode( CGIAttr& rAttr, LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL, BOOL bGroupedNaming = FALSE );

	/// Remove an attribute node
	CGIAttr* RemoveAttributeNode( LPCTSTR pctszName, LPCTSTR pctszGroupName );

	/// Get an attribute group
	CGIAttrGroup* GetAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL );
	const CGIAttrGroup* GetAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL ) const;

	/// Add an attribute group
	CGIAttrGroup* AddAttributeGroup( CGIAttrGroup& rAttrGroup );
	CGIAttrGroup* AddAttributeGroup( CGIAttrGroup& rAttrGroup, LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL );

	/// Remove an attribute group
	CGIAttrGroup* RemoveAttributeGroup( CGIAttrGroup& rAttrGroup );
	CGIAttrGroup* RemoveAttributeGroup( LPCTSTR pctszName, LPCTSTR pctszGroupName = NULL );

	/// Get a NS attribute node
	CGIAttr* GetAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName );
	const CGIAttr* GetAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName ) const;

	/// Add a NS attribute node
	CGIAttr* AddAttributeNodeNS( CGIAttr& rAttr );
	CGIAttr* AddAttributeNodeNS( CGIAttr& rAttr, LPCTSTR ptszNsURI, LPCTSTR pctszQualifiedName, LPCTSTR pctszGroupName = NULL, BOOL bGroupedNaming = FALSE );

	/// Remove a NS attribute node
	CGIAttr* RemoveAttributeNodeNS( CGIAttr& rAttr );
	CGIAttr* RemoveAttributeNodeNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName );

	/// Get an attribute group
	CGIAttrGroup* GetAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName = NULL );
	const CGIAttrGroup* GetAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName = NULL ) const;

	/// Add a NS attribute group
	CGIAttrGroup* AddAttributeGroupNS( CGIAttrGroup& rAttrGroup, LPCTSTR pctszGroupName = NULL );
	CGIAttrGroup* AddAttributeGroupNS( CGIAttrGroup& rAttrGroup, LPCTSTR ptszNsURI, LPCTSTR pctszQualifiedName, LPCTSTR pctszGroupName = NULL );

	/// Remove a NS attribute group
	CGIAttrGroup* RemoveAttributeGroupNS( CGIAttrGroup& rAttrGroup );
	CGIAttrGroup* RemoveAttributeGroupNS( LPCTSTR ptszNsURI, LPCTSTR ptszLocalName, LPCTSTR pctszGroupName = NULL );
	///}} Customized DOM attribute functions
	
	/// Attribute functions
	virtual BOOL GetDefaultAttributeValue( LPCTSTR pctszName, INT nAttrType, void* pValue ) const;
	virtual BOOL ValidateAttribute( const CGIAttr& rAttr, void* pValue ) const;
	virtual BOOL UpdateAttribute( const CGIAttr& rAttr, void* pValue );
	virtual void AttributeChanged( const CGIAttr& rAttr );

	virtual BOOL IsDisplayAttribute( const CGIAttr& rAttr ) const;

	/// Frame work functions
	virtual void Draw( Graphics& rGdip );
	virtual void DrawElement( Graphics& rGdip );
	virtual void DrawChild( Graphics& rGdip );
	virtual void DrawOverlay( Graphics& rGdip );

	LPCTSTR GetId() const;
	virtual LPCTSTR GetID() const;
	BOOL SetId( LPCTSTR pctszId );

	LPCTSTR GetXmlbase()  const;
	BOOL SetXmlbase( LPCTSTR pctszBase );
	
	CGIElement* GetRootElement();
	const CGIElement* GetRootElement() const;

	CGIElement* GetViewportElement();
	const CGIElement* GetViewportElement() const;

	virtual BOOL GetRect( GRectF& rBBox ) const;
	virtual BOOL GetDrawBBox( GRectF& rBBox, Matrix* pmtx = NULL ) const;

	virtual BOOL GetScreenCTM( Matrix& rMtx ) const;
	virtual BOOL GetCTM( Matrix& rMtx ) const;
	virtual BOOL GetCTM( Matrix& rMtx, INT nTYpe ) const;
	virtual BOOL GetCTMToElement( Matrix& rMtx, const CGIElement& rRef ) const;

	///{{ Reimplemented
	virtual UINT HitTest( const CPoint& rpoint, Matrix* pmtx = NULL );
	overrided UINT HitTest( const PointF& rptf );

	virtual UINT HitTest( const CRect& rrct, Matrix* pmtx = NULL );
	virtual UINT HitTest( const Region& rrgn );
	///}} Reimplemented

	virtual void Update();
	void AddAttributes( CGIAttrLink* pAttrProxy, ... );

	void AddGroupedAttributesV( LPCTSTR pctszName, LPCTSTR pctszGroupName, BOOL bGroupedNaming, 
							   va_list argList );
	void AddGroupedAttributes( LPCTSTR pctszName, LPCTSTR pctszGroupName, BOOL bGroupedNaming, 
							   CGIAttrLink* pAttrProxy, ... );
	void AddGroupedAttributes( LPCTSTR pctszName, CGIAttrGroup& rAttrGroup, BOOL bGroupedNaming, 
							   CGIAttrLink* pAttrProxy, ... );

	static void RemoveAttributes( CGIAttrLink* pAttrProxy, ... );
	static void SetAttrType( INT nType, ... );
	static void SetAttrFlag( INT nFlag, BOOL bSet, ... );

protected:
	overrided void Attach( CGEventNode& rNode );
	overrided void Detach( CGEventNode& rNode );
	overrided void OnFinalRelease();

protected:
	CGIElement*			m_pRootElement;
	CGIElement*			m_pViewPortElement;

    CString				m_cszPrefix;		// Set this only for ElementNode and AttributeNode
    CString				m_cszNamespaceURI;	// Set this only for ElementNode and AttributeNode

#ifdef _DEBUG
	static CMapStringToPtr		m_mapIDIndex;
#endif //_DEBUG

public:
	CGINamedAttrMap		m_mapAttr;
	CGSAString			m_aID;

	class CGElement;
};

inline void CGIElement::GetTagName( CString& rcszTagName ) const {
	GetNodeName( rcszTagName ); }

inline LPCTSTR CGIElement::GetTagName() const {
	return GetNodeName(); }

inline CGINamedNodeMap* CGIElement::GetAttributes() {
	return &m_mapAttr; }

inline LPCTSTR CGIElement::GetNameSpaceURI() const {
	return m_cszNamespaceURI; }

inline void CGIElement::GetNameSpaceURI( CString& rcszNameSpaceURI ) const {
	rcszNameSpaceURI = m_cszNamespaceURI; }

inline LPCTSTR CGIElement::GetPrefix() const {
	return m_cszPrefix; }

inline void CGIElement::GetPrefix( CString& rcszPrefix ) const {
	rcszPrefix = m_cszPrefix; }

inline BOOL CGIElement::HasAttributes() const {
	return m_mapAttr.HasAttributes(); }

inline LPCTSTR CGIElement::GetID() const {
		return NULL; }

inline CGIElement* CGIElement::GetRootElement() {
	return m_pRootElement; }

inline const CGIElement* CGIElement::GetRootElement() const {
	return m_pRootElement; }

inline CGIElement* CGIElement::GetViewportElement() {
	return m_pViewPortElement; }

inline const CGIElement* CGIElement::GetViewportElement() const {
	return m_pViewPortElement; }

#endif //!___G_I_ELEMENT__PH___
