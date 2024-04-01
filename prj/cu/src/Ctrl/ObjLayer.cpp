#include "stdafx.h"
#include "ObjLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CObjLayer::CObjLayer()
{}

CObjLayer::~CObjLayer()
{
	DeleteStruct();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Obj Struct functions
BOOL CObjLayer::InitStruct()
{
	if( FALSE == CObjContainer::InitStruct() )
		return FALSE;

	return TRUE;
}

void CObjLayer::DeleteStruct()
{
	if( NULL == m_psObj || NULL == &sLayer() )
		return;

	delete &sLayer();
	sLayer( NULL );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Track Struct functions
BOOL CObjLayer::CreateTrackStruct( INT nMode )
{
	if( FALSE == CObj::CreateTrackStruct( nMode ) )
		return FALSE;

	if( NULL == &sLayerTrk() )
		VERIFY( sLayerTrk( new SObjTrackLayer ) );

	return (NULL != &sLayerTrk());
}

void CObjLayer::DeleteTrackStruct( INT nMode )
{
	CObjContainer::DeleteTrackStruct( nMode );
}