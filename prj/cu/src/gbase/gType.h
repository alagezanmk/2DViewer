#ifndef ___G_TYPE__PH___
#define ___G_TYPE__PH___

///{{
#define DECL_GTPYECLASS_DYNCREATE( className )								\
public:																		\
	static const CGType& GetClassType();									\
protected:																	\
	static const CGType	m_g##className##ClassType;
																
///{{
#define DECL_BASE_GTPYECLASS_DYNCREATE( className )							\
public:																		\
	BOOL IsDerivedFrom( const CGType& rType ) const;						\
	virtual const CGType& GetInstanceType() const;							\
	static const CGType& GetClassType();									\
protected:																	\
	static const CGType	m_g##className##ClassType;							\
	const CGType*	m_pgInstanceType;
///}}

///{{
#define IMPL_GTPYECLASS_DYNCREATE( className, classParentName, pctszName )	\
	const CGType& className::GetClassType() {								\
			return m_g##className##ClassType; }								\
																			\
	const CGType className::m_g##className##ClassType(						\
							&classParentName::GetClassType(),				\
							pctszName );										
///}}

///{{
#define IMPL_BASE_GTPYECLASS_DYNCREATE( className, pctszName )				\
	BOOL className::IsDerivedFrom( const CGType& rType ) const {			\
		ASSERT( m_pgInstanceType );											\
		if( m_pgInstanceType )												\
			return m_pgInstanceType->IsDerivedFrom( rType );				\
		return FALSE; }														\
	const CGType& className::GetInstanceType() const {						\
		ASSERT( m_pgInstanceType );											\
		return *m_pgInstanceType; }											\
																			\
	const CGType& className::GetClassType() {								\
			return m_g##className##ClassType; }								\
																			\
	const CGType className::m_g##className##ClassType(						\
							NULL,											\
							pctszName );
///}}

class CGTypeData;
class CU_EXT_CLASS CGType
{
public:
	CGType();
	CGType( CGTypeData* pTypeData );
	CGType( const CGType* pParentType, LPCTSTR pctszName );
	virtual ~CGType();

public:
	void operator=( const CGType& rType );
	BOOL operator==( const CGType& rType ) const;
	BOOL operator!=( const CGType& rType ) const;

	static const CGType& GetNullType();
	static const CGType& GetType( LPCTSTR pctszName );
	LPCTSTR GetName() const;
	BOOL IsDerivedFrom( const CGType& rType ) const;
	BOOL InitType( const CGType* pParentType, LPCTSTR pctszName );

protected:
	CGTypeData*			m_pTypeData;
};

#endif //!___G_TYPE__PH___
