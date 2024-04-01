#include "stdafx.h"
#include "PropDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

SPropDataLen::SPropDataLen( 
		INT					_nDataMinLen /*= 0*/,
		INT					_nDataMaxLen /*= 0*/,

		INT					_nDataMin /*= 0*/,
		FLOAT				_fDataMin /*= 0.0f*/,
							
		INT					_nDataMax /*= 0*/,
		FLOAT				_fDataMax /*= 0.0f*/
	)
{
	nDataMinLen = _nDataMinLen;
	nDataMaxLen = _nDataMaxLen;

	nDataMin = _nDataMin;
	fDataMin = _fDataMin;
	
	nDataMax = _nDataMax;
	fDataMax = _fDataMax;
}

void SProp::Set( INT _nID, PTCHAR _ptszLabel, INT _nType, INT _nFlag, INT _nCtrlType, 
				 INT _nCtrlFlag /*= 0*/, INT _nDataType /*= 0*/, INT _nDataFlag /*= 0*/, 
				 DWORD _dwItemData /*= 0*/, SPropDataInfo* _psDataInfo /*= NULL*/ )
{
	nID	= _nID;
	ptszLabel = _ptszLabel;

	nType = _nType;
	nFlag = _nFlag;

	nCtrlType = _nCtrlType;
	nCtrlFlag = _nCtrlFlag;
		
	nDataType = _nDataType;
	nDataFlag = _nDataFlag;
	dwItemData = _dwItemData;
	psDataInfo = _psDataInfo;
}

SPropItem::SPropItem()
{
	pParent = NULL;
	pPrev = NULL;
	pNext = NULL;

	nFlag = 0;
	nChildCount = 0;
	nCy = 0;
	psGroup = 0;
	psProp = 0;

	pData = NULL;
	pCtrlData = NULL;

	bText = FALSE;
	pcszText = NULL;

	VERIFY( pcszText = new CString() );
}

SPropItem::~SPropItem()
{
	if( pcszText )
		delete pcszText;
}