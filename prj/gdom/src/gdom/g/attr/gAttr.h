#ifndef ___G_ATTR__PH___
#define ___G_ATTR__PH___

#include <g\type\idom\giNode.h>

class CGIAttrGroup;
class CGINamedAttrMap;
class CGIElement;

///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGIAttr : public CGINode
{
	DECL_GTPYECLASS_DYNCREATE(CGIAttr)
public:
	static LPCTSTR ATTR_NOT_SET_STR;

	enum VALUE_TYPE {
		UNDEFINED_VALUE_TYPE	= -1,
		ATTR_VALUE_TYPE			= 0,
		DEF_VALUE_TYPE			= 1,
		INHERIT_VALUE_TYPE		= 2,
		ANIM_VALUE_TYPE			= 3,
	};

	enum ATTR_TYPE {
		USER_DEFINED_ATTR_TYPE	= 256,
		SYSTEM_ATTR_TYPE		= 512,

		DISPLAY_ATTR_TYPE		= 1,
		DRAW_BBOX_ATTR_TYPE		= 2,
		CTM_ATTR_TYPE			= 4,
	};

	enum ATTR_FLAG {
		NONE_ATTR_FLAG			= 0,
		SPECIFIED_ATTR_FLAG		= 1,
		IS_ID_ATTR_FLAG			= 2,
		NOT_SET_ATTR_FLAG		= 4,
		INHERITABLE_ATTR_FLAG	= 8,
	};

public:
	CGIAttr( LPCTSTR pctszName );

public:
	///{{ DOM Methods
	virtual void GetValue( CString& rcszValue ) const;
	BOOL GetSpecified() const;
	CGIElement* GetOwnerElement() const;
	///GetSchemaTypeInfo()
	BOOL IsId() const;
	///}} DOM Methods

	///{{ Reimplemented
	overrided INT GetNodeType() const;

	virtual LPCTSTR GetNameSpaceURI() const;
	virtual void GetNameSpaceURI( CString& rcszameSpaceURI ) const;

	virtual LPCTSTR GetPrefix() const;
	virtual void GetPrefix( CString& rcszPrefix ) const;
	///}} Reimplemented

	///{{ Functions to reimplemented in Derived attribute classes
	virtual BOOL Set( LPCTSTR pctszValue );
	virtual void Get( CString& rcszValue ) const;
	virtual BOOL Validate( CString& rcszValue ) const;
	virtual BOOL Update( CString& rcszValue );

	virtual void* GetPreviousValuePointer();
	virtual void* GetNewValuePointer();

	/// Optional overridables if pPointer buffer is basic data type(INT, FLOAT)
	virtual void DeleteNewValuePointer( void* pPointer );
	virtual void DeletePreviousValuePointer( void* pPointer );
	///}} Functions to reimplemented in Derived attribute classes

	virtual BOOL Validate( void* pValue ) const;
	virtual BOOL Update( void* pValue );
	virtual void Changed();
	INT GetValue( void* pValue ) const;

	void OnUpdate( void* pNewValue );

	virtual void NotSet( BOOL bSet = TRUE );
	BOOL GetNotSet() const;

	BOOL IsInHeritable() const;

	BOOL IsAttrTypeSet( INT nType ) const;
	INT GetAttrType() const;
	INT SetAttrType( INT nType, BOOL bSet = TRUE );

	INT IsAttrFlagSet( INT nFlag ) const;
	INT GetAttrFlag() const;
	INT SetAttrFlag( INT nFlag, BOOL bSet = TRUE );

	CString GetGroupName() const;
	void GetGroupName( CString& rcsName ) const;

	static BOOL CompareDOMAttrEvent( CGEvent* pEvent, void* pParam );
	CGMutationEvent* CreateDOMUpdateAttrEvent( void* pNewValue );
	CGMutationEvent* CreateDOMAttrModifiedEvent();

protected:
	CGIElement*			m_pOwnerElement;
	INT					m_nAttrFlag;
	INT					m_nAttrType;
	BOOL				m_bGroupedNaming;

    CString				m_cszPrefix;		// Set this only for ElementNode and AttributeNode
    CString				m_cszNamespaceURI;	// Set this only for ElementNode and AttributeNode

	friend CGIAttrGroup;
	friend CGINamedAttrMap;
};

inline void CGIAttr::GetValue( CString& rcszValue ) const {
	rcszValue.Empty(); }

inline BOOL CGIAttr::GetSpecified() const {
	return 0 != (m_nAttrFlag & SPECIFIED_ATTR_FLAG); }

inline CGIElement* CGIAttr::GetOwnerElement() const {
	return m_pOwnerElement; }

inline BOOL CGIAttr::IsId() const {
	return 0 != (m_nAttrFlag & IS_ID_ATTR_FLAG); }

inline INT CGIAttr::GetNodeType() const {
	return CGNode::ATTRIBUTE_NODE; }

inline LPCTSTR CGIAttr::GetNameSpaceURI() const {
	return m_cszNamespaceURI; }

inline void CGIAttr::GetNameSpaceURI( CString& rcszNameSpaceURI ) const {
	rcszNameSpaceURI = m_cszNamespaceURI; }

inline LPCTSTR CGIAttr::GetPrefix() const {
	return m_cszPrefix; }

inline void CGIAttr::GetPrefix( CString& rcszPrefix ) const {
	rcszPrefix = m_cszPrefix; }

inline BOOL CGIAttr::GetNotSet() const {
	return 0 != (m_nAttrFlag & NOT_SET_ATTR_FLAG); }

inline BOOL CGIAttr::IsInHeritable() const {
	return 0 != (m_nAttrFlag & INHERITABLE_ATTR_FLAG); }

inline BOOL CGIAttr::IsAttrTypeSet( INT nType ) const {
	return 0 != (m_nAttrType & nType); }

inline INT CGIAttr::GetAttrType() const {
	return m_nAttrType; }

inline INT CGIAttr::IsAttrFlagSet( INT nFlag ) const {
	return nFlag == (m_nAttrFlag & nFlag); }

inline INT CGIAttr::GetAttrFlag() const {
	return m_nAttrFlag; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGIAttrArray : public CGIAttr
{
public:
	CGIAttrArray( LPCTSTR pctszName );
	virtual ~CGIAttrArray();

public:
};

#endif //!___G_ATTR__PH___
