#include "stdafx.h"
#include "DefProp.h"
#include "PsPropMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static const PS_PROPMAP_ENTRY* _AfsPbFindPropMapEntry( const PS_PROPMAP_ENTRY* pEntries, UINT nMsg, UINT nCode, UINT nID )
{
	while( pEntries )
	{
		if( AfsSig_end == pEntries->nSig )
			break;

		if( pEntries->nMsg == nMsg && pEntries->nCode == nCode )
			if( nID >= pEntries->nID && nID <= pEntries->nLastID )
				return pEntries;

		pEntries++;
	}

	return NULL;
}

CProp* CProp::GetDefProp()
{
	static CDefaultProp s_DefProp;
	return &s_DefProp;
}

LONG CProp::SendPropMsg( UINT nMsg, UINT nCode /*= 0*/, UINT nID /*= 0*/, UINT nData /*= 0*/, UINT nData1 /*= 0*/, UINT nData2 /*= 0*/ )
{
	CProp* pProp = this;

LBStart:;
	const PS_PROPMAP* psMap;
	const PS_PROPMAP_ENTRY* psMapEntry;

	psMap = pProp->GetPropMap();
	while( psMap )
	{
		psMapEntry = _AfsPbFindPropMapEntry( psMap->lpEntries, nMsg, nCode, nID );
		if( psMapEntry )
			break;

		if( psMap != psMap->pfnGetBaseMap() )
			psMap = psMap->pfnGetBaseMap();
		else
			psMap = NULL;
	}
	
	if( NULL == psMapEntry )
	{
		if( pProp == this )
		{
			pProp = GetDefProp();
			((CDefaultProp*)pProp)->m_pProp = this;
			goto LBStart;
		}

		return 0;
	}

	union PropMapFunctions pmf;
	pmf.pfn = psMapEntry->pfn;
	switch( psMapEntry->nSig )
	{
	case AfsSig_bPi_Cs:
		return (pProp->*pmf.pfn_b_pSPropItem_pCStr)( (SPropItem*)nData, (CString*)nData1 );

	case AfsSig_bPi_:
		return (pProp->*pmf.pfn_b_pSPropItem)( (SPropItem*)nData );

	case AfsSig_bPi_S:
		return (pProp->*pmf.pfn_b_pSPropItem_pTChar)( (SPropItem*)nData, (PTCHAR)nData1 );

	case AfsSig_bPi_SI:
		return (pProp->*pmf.pfn_b_pSPropItem_pTChar_pInt)( (SPropItem*)nData, (PTCHAR)nData1, (INT*)nData2 );

	case AfsSig_bPi_i:
		return (pProp->*pmf.pfn_b_pSPropItem_pInt)( (SPropItem*)nData, (PINT)nData1 );

	case AfsSig_bPi_f:
		return (pProp->*pmf.pfn_b_pSPropItem_pFlt)( (SPropItem*)nData, (FLOAT*)nData1 );

	case AfsSig_bPi_d:
		return (pProp->*pmf.pfn_b_pSPropItem_pDbl)( (SPropItem*)nData, (DOUBLE*)nData1 );

	case AfsSig_bPi_SL:
		return (pProp->*pmf.pfn_pSPropItem_pNMMSCmb_pL)( (SPropItem*)nData, (CMSComboBox::NMSELCHANGE*)nData1, (LRESULT*)nData2 );
	}

	return 0;
}
