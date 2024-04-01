#ifndef ___OBJ_LAYER_GRP_OBJ__PH___
#define ___OBJ_LAYER_GRP_OBJ__PH___

//#include "ObjLayer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// SObjLayerGrp struct
struct SObjLayerGrp : public SObjLayer
{};

///////////////////////////////////////////////////////////////////////////////////////////////
// SObjTrackLayerGrp struct
struct SObjTrackLayerGrp : public SObjTrackLayer
{};

///////////////////////////////////////////////////////////////////////////////////////////////
inline SObjLayerGrp* sLayerGrp( SObj* psObj ) {
	return (SObjLayerGrp*)psObj; }

inline SObjLayerGrp* sLayerGrp( CObj* pObj ) {
	return (SObjLayerGrp*)pObj->m_psObj->psDat; }

class CObjLayerGrp : public CObjLayer
{
public:
	enum { enObjTypeLayerGrp = 258 };
	CObjLayerGrp();
	virtual ~CObjLayerGrp();

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Info functions
	virtual INT GetType();

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Data functions
	virtual PVOID CreateObjStruct();
	virtual BOOL InitStruct();
	virtual void DeleteStruct();

	SObjLayerGrp& sLayerGrp();
	SObjLayerGrp* sLayerGrp( SObjLayerGrp* psObj );

	SObjTrackLayerGrp& sLayerGrpTrk();
	SObjTrackLayerGrp* sLayerGrpTrk( SObjTrackLayerGrp* psTrk );

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Track Struct functions
	virtual BOOL CreateTrackStruct( INT nMode );
	virtual void DeleteTrackStruct( INT nMode );
};

inline SObjLayerGrp& CObjLayerGrp::sLayerGrp() {
	return *((SObjLayerGrp*)m_psObj->psDat); }

inline SObjLayerGrp* CObjLayerGrp::sLayerGrp( SObjLayerGrp* psObj ) {
	m_psObj->psDat = psObj;
	return psObj; }

inline SObjTrackLayerGrp& CObjLayerGrp::sLayerGrpTrk() {
	return *((SObjTrackLayerGrp*)m_pstrk); }

inline SObjTrackLayerGrp* CObjLayerGrp::sLayerGrpTrk( SObjTrackLayerGrp* pstrk ) {
	m_pstrk = pstrk;
	return pstrk; }

inline INT CObjLayerGrp::GetType() {
	return enObjTypeLayerGrp; }

inline PVOID CObjLayerGrp::CreateObjStruct() {
	return new SObjLayerGrp; }

#endif // !___OBJ_LAYER_GRP_OBJ__PH___
