#ifndef ___G_BJECT_NODE__PH___
#define ___G_BJECT_NODE__PH___

#include <gbase\gClassFactory.h>

class CU_EXT_CLASS CGObjectNode
{
public:
	static LPCTSTR NODE_TYPE;

public:
	CGObjectNode();

protected:
	virtual ~CGObjectNode();

public:
	/// readonly attribute Node parentNode;
	CGObjectNode* GetParentNode();
	const CGObjectNode* GetParentNode() const;

	/// readonly attribute Node firstChild;
	CGObjectNode* GetFirstNode();
	const CGObjectNode* GetFirstNode() const;

	/// readonly attribute Node lastChild;
	CGObjectNode* GetLastNode();
	const CGObjectNode* GetLastNode() const;

	/// readonly attribute Node previousSibling;
	CGObjectNode* GetPrevNode();
	const CGObjectNode* GetPrevNode() const;

	/// readonly attribute Node nextSibling;
	CGObjectNode* GetNextNode();
	const CGObjectNode* GetNextNode() const;

	/// Modified in DOM Level 3:
	virtual CGObjectNode* InsertBefore( CGObjectNode& rNewChild, CGObjectNode& rRef );

	///<< Customized DOM
	virtual CGObjectNode* InsertAfter( CGObjectNode& rNewChild, CGObjectNode& rRef );
	///>> Customized DOM

	/// Introduced in DOM Level 3:
	virtual CGObjectNode* ReplaceChild( CGObjectNode& rNewChild, CGObjectNode& rOldNode );

	/// Introduced in DOM Level 3:
	virtual CGObjectNode* AppendChild( CGObjectNode& rNewChild );

	/// Introduced in DOM Level 3:
	virtual CGObjectNode* RemoveChild( CGObjectNode& rChild );

	virtual void RemoveAllChild();
	virtual BOOL HasChildNodes() const;

	void SetParent( CGObjectNode* pParent );
	BOOL IsChildNode( const CGObjectNode& rNode, BOOL bDeepSearch = FALSE ) const;
	BOOL IsSibilingNode( const CGObjectNode& rNode ) const;

	virtual LPCTSTR _GetNodeType() const;
	BOOL _IsKindOf( LPCTSTR ptszNodeType ) const;
	virtual BOOL _IsDerivedFrom( LPCTSTR ptszNodeType ) const;
	virtual void OnNodeListModified();

protected:
	virtual void AttachChild( CGObjectNode& rNode );
	virtual void Attach( CGObjectNode& rNode );

	virtual void DetachChild( CGObjectNode& rNode );
	virtual void Detach( CGObjectNode& rNode );
	virtual void ResetLink();

protected:
mutable 
	CCriticalSection	m_cSect;
	CGObjectNode*		m_pParent;

	CGObjectNode*		m_pPrev;
	CGObjectNode*		m_pNext;

	CGObjectNode*		m_pFirst;
	CGObjectNode*		m_pLast;
};

inline CGObjectNode* CGObjectNode::GetParentNode() {
	return m_pParent; }

inline const CGObjectNode* CGObjectNode::GetParentNode() const {
	return m_pParent; }

inline CGObjectNode* CGObjectNode::GetNextNode() {
	return m_pNext; }

inline const CGObjectNode* CGObjectNode::GetNextNode() const {
	return m_pNext; }

inline CGObjectNode* CGObjectNode::GetPrevNode() {
	return m_pPrev; }

inline const CGObjectNode* CGObjectNode::GetPrevNode() const {
	return m_pPrev; }

inline CGObjectNode* CGObjectNode::GetFirstNode() {
	return m_pFirst; }

inline const CGObjectNode* CGObjectNode::GetFirstNode() const {
	return m_pFirst; }

inline CGObjectNode* CGObjectNode::GetLastNode() {
	return m_pLast; }

inline const CGObjectNode* CGObjectNode::GetLastNode() const {
	return m_pLast; }

inline void CGObjectNode::SetParent( CGObjectNode* pParent ) {
	m_pParent = pParent; }

inline LPCTSTR CGObjectNode::_GetNodeType() const {
	return NODE_TYPE; }

inline BOOL CGObjectNode::_IsKindOf( LPCTSTR ptszNodeType ) const {
	return _GetNodeType() == ptszNodeType; }

#endif //!___G_BJECT_NODE__PH___
