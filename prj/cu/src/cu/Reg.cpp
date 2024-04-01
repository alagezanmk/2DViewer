#include "stdafx.h"
#include <cu\Unicode.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CU_EXT_API INT GetProfileID2Value( INT nID, INT nStartID, INT nStartValue, INT nCount, INT nDefValue /*= 0*/ )
{
	// Given ID is out of range
	if( nID < nStartID || nID > nStartID + nCount )
		return nDefValue;
	
	return (nID - nStartID) + nStartValue;
}

CU_EXT_API INT GetProfileValue2ID( INT nValue, INT nStartID, INT nStartValue, INT nCount, INT nDefID )
{
	// Give Value is out of range
	if( nValue < nStartValue && nValue > nStartValue + nCount )
		return nDefID;

	return (nValue - nStartValue) + nStartID;
}

CU_EXT_API BOOL WriteProfileInt( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, INT nValue ) 
{
	if( NULL == pApp )
		pApp = AfxGetApp();

	ASSERT( pApp );
	return pApp->WriteProfileInt( lpszSection, lpszEntry, nValue ); 
}

CU_EXT_API INT GetProfileInt( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, INT nDefault, INT nMin, INT nMax )
{
	if( NULL == pApp )
		pApp = AfxGetApp();

	ASSERT( pApp );
	INT nValue = pApp->GetProfileInt( lpszSection, lpszEntry, nDefault );
	if( nValue > nMax )
		nValue = nDefault;

	if( nValue < nMin )
		nValue = nDefault;

	return nValue;
}

CU_EXT_API BOOL WriteProfileBool( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, BOOL bValue ) 
{
	if( NULL == pApp )
		pApp = AfxGetApp();

	ASSERT( pApp );
	return pApp->WriteProfileInt( lpszSection, lpszEntry, 0 != bValue ); 
}

CU_EXT_API BOOL GetProfileBool( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, BOOL bDefault ) 
{
	if( NULL == pApp )
		pApp = AfxGetApp();

	ASSERT( pApp );
	return 0 != pApp->GetProfileInt( lpszSection, lpszEntry, 0 != bDefault ); 
}

CU_EXT_API BOOL WriteProfileFloat( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, FLOAT fValue )
{
	if( NULL == pApp )
		pApp = AfxGetApp();

	ASSERT( pApp );
	CString csz;
	csz.Format( _T("%g"), fValue );
	return pApp->WriteProfileString( lpszSection, lpszEntry, csz );
}

CU_EXT_API FLOAT GetProfileFloat( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, FLOAT fDefault, FLOAT fMin, FLOAT fMax )
{
	if( NULL == pApp )
		pApp = AfxGetApp();

	ASSERT( pApp );
	CString cszDef;
	cszDef.Format( _T("%g"), fDefault );
	CString csz = pApp->GetProfileString( lpszSection, lpszEntry, cszDef );
	FLOAT fValue = latof( csz );
	if( fValue > fMax )
		fValue = fDefault;

	if( fValue < fMin )
		fValue = fDefault;

	return fValue;
}
