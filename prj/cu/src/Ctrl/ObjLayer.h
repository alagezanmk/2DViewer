#ifndef ___OBJ_LAYER__PH___
#define ___OBJ_LAYER__PH___

#include <ObjContainer.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
/// SObjLayer struct
struct SObjLayer : public SObjContainer
{};

///////////////////////////////////////////////////////////////////////////////////////////////
/// SObjTrackLayer struct
struct SObjTrackLayer : public SObjTrackContainer
{};

///////////////////////////////////////////////////////////////////////////////////////////////
inline SObjLayer* sLayer( SObj* psObj ) {
	return (SObjLayer*)psObj; }

inline SObjLayer* sLayer( CObj* pObj ) {
	return (SObjLayer*)pObj->m_psObj->psDat; }

class CObjLayer : public CObjContainer
{
public:
	enum { enObjTypeLayer = 257 };
	CObjLayer();
	virtual ~CObjLayer();

	///////////////////////////////////////////////////////////////////////////////////////////////
	/// Info functions
	virtual INT GetType();

	///////////////////////////////////////////////////////////////////////////////////////////////
	/// Data functions
	virtual PVOID CreateObjStruct();
	virtual BOOL InitStruct();
	virtual void DeleteStruct();

	SObjLayer& sLayer();
	SObjLayer* sLayer( SObjLayer* psObj );

	SObjTrackLayer& sLayerTrk();
	SObjTrackLayer* sLayerTrk( SObjTrackLayer* psTrk );

	///////////////////////////////////////////////////////////////////////////////////////////////
	/// Track Struct functions
	virtual BOOL CreateTrackStruct( INT nMode );
	virtual void DeleteTrackStruct( INT nMode );
};

inline SObjLayer& CObjLayer::sLayer() {
	return *((SObjLayer*)m_psObj->psDat); }

inline SObjLayer* CObjLayer::sLayer( SObjLayer* psObj ) {
	m_psObj->psDat = psObj;
	return psObj; }

inline SObjTrackLayer& CObjLayer::sLayerTrk() {
	return *((SObjTrackLayer*)m_pstrk); }

inline SObjTrackLayer* CObjLayer::sLayerTrk( SObjTrackLayer* pstrk ) {
	m_pstrk = pstrk;
	return pstrk; }

inline INT CObjLayer::GetType() {
	return enObjTypeLayer; }

inline PVOID CObjLayer::CreateObjStruct() {
	return new SObjLayer; }

#endif // !___OBJ_LAYER__PH___
