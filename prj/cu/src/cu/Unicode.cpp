#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CU_EXT_API BOOL lIsStrEmpty( const TCHAR* pctsz )
{
	if( NULL == pctsz || 0 == pctsz[0] )
		return TRUE;
	
	return FALSE;
}