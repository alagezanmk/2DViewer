#include "stdafx.h"
#include "ObjLayerGrp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CObjLayerGrp::CObjLayerGrp()
{}

CObjLayerGrp::~CObjLayerGrp()
{
	DeleteStruct();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Obj Struct functions
BOOL CObjLayerGrp::InitStruct()
{
	if( FALSE == CObjLayer::InitStruct() )
		return FALSE;

	return TRUE;
}

void CObjLayerGrp::DeleteStruct()
{
	if( NULL == m_psObj || NULL == &sLayerGrp() )
		return;

	delete &sLayerGrp();
	sLayerGrp( NULL );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Track Struct functions
BOOL CObjLayerGrp::CreateTrackStruct( INT nMode )
{
	if( FALSE == CObj::CreateTrackStruct( nMode ) )
		return FALSE;

	if( NULL == &sLayerGrpTrk() )
		VERIFY( sLayerGrpTrk( new SObjTrackLayerGrp ) );

	return (NULL != &sLayerGrpTrk());
}

void CObjLayerGrp::DeleteTrackStruct( INT nMode )
{
	CObjLayer::DeleteTrackStruct( nMode );
}