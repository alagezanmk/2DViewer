#ifndef ___G_EVENT_NODE__PH___
#define ___G_EVENT_NODE__PH___

#include <gbase\gEvent.h>
#include <gbase\gObjectNode.h>

class CU_EXT_CLASS CGEventNode : public CGObjectNode, public CGFactoryObject, public CGEventTarget
{
public:
	DECL_GTPYECLASS_DYNCREATE( CGEventNode )
	static LPCTSTR NODE_TYPE;

public:
	CGEventNode();

protected:
	overrided ~CGEventNode();

public:
	/// readonly attribute unsigned short nodeType;
	virtual INT GetNodeType() const;

	overrided LPCTSTR _GetNodeType() const;
	overrided BOOL _IsDerivedFrom( LPCTSTR ptszNodeType ) const;

	overrided void LockObjectLink( BOOL bLock = TRUE );
	overrided CGFactoryObject* GetFactoryObjectParent();

	using CGFactoryObject::CreateFactoryObject;
	virtual void* CreateFactoryObject( const CGType& rType );

public:
	/// For Event class
	overrided INT GetDispatchPath( CPtrArray& arpPath );
	virtual CGMutationEvent* CreateAttrModifiedMutationEvent( LPCTSTR pctszEventType );
	virtual CGMutationEvent* CreateMutationEvent( LPCTSTR pctszEventType, BOOL& rbInitialize, 
												  CGEventNode* pLockCheckParent = NULL,
												  SCompareEventPending* pCompare = NULL );
	virtual CGMutationEvent* CreateNodeTreeModifiedEvent( LPCTSTR pctszEventType, 
														  CGEventNode* pRelatedNode, 
														  INT nAttrChange,
														  CGEventNode* pLockCheckParent = NULL );

	virtual void DispatchNodeTreeModifiedEvent( LPCTSTR pctszEventType, CGEventNode* pTarget, 
											    CGEventNode* pRelatedNode, INT nAttrChange );
	virtual void DispatchNodeInsertedIntoDocumentEvent( CGEventNode& rTarget );
	virtual void DispatchNodeRemovedFromDocumentEvent( CGEventNode& rTarget );
	
protected:
	overrided void AttachChild( CGObjectNode& rNode );
	overrided void DetachChild( CGObjectNode& rNode );

	overrided void Attach( CGObjectNode& rNode );
	overrided void Detach( CGObjectNode& rNode );

	virtual void AttachChild( CGEventNode& rNode );
	virtual void DetachChild( CGEventNode& rNode );

	virtual void Attach( CGEventNode& rNode );
	virtual void Detach( CGEventNode& rNode );
};

inline INT CGEventNode::GetNodeType() const {
	return -1; }

inline LPCTSTR CGEventNode::_GetNodeType() const {
	return NODE_TYPE; }

#endif //!___G_EVENT_NODE__PH___
