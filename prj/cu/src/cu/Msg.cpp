#include "stdafx.h"
#include <cu\msg.h>
#include <..\src\mfc\AfxImpl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CMapWordToPtr gs_mapCtrlList;

CU_EXT_API BOOL AfsAddCtrlWnd( UINT nID, CWnd* pWnd )
{
	CWnd* pwndLockUp;
	if( gs_mapCtrlList.Lookup( nID, (void*&)pwndLockUp ) )
		return FALSE;

	gs_mapCtrlList.SetAt( nID, pWnd );
	return TRUE;
}

CU_EXT_API void AfsSetCtrlWnd( UINT nID, CWnd* pWnd ) {
	gs_mapCtrlList.SetAt( nID, pWnd ); }

CU_EXT_API BOOL AfsRemoveCtrlWnd( UINT nID, CWnd* pWnd ) {
	return gs_mapCtrlList.RemoveKey( nID ); }

CU_EXT_API CWnd* AfsGetCtrlWnd( UINT nID )
{
	CWnd* pWnd;
	if( gs_mapCtrlList.Lookup( nID, (void*&)pWnd ) )
		return pWnd;

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API LRESULT SendNotify( CWnd* pWnd, INT nCode, NMHDR* pnm /*= NULL*/ )
{
	NMHDR nm;
	if( NULL == pnm )
		pnm = &nm;

	pnm->code = nCode;
	pnm->hwndFrom = pWnd->m_hWnd;
	pnm->idFrom = pWnd->GetDlgCtrlID();

	CWnd* pParent = pWnd->GetParent();
	return pParent->SendMessage( WM_NOTIFY, pnm->idFrom, (LPARAM)pnm );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
class _CWnd : public CWnd
{
	friend CU_EXT_API LRESULT AfsSend( UINT nCode, CWnd* pWnd, UINT id, WPARAM wParam, LPARAM lParam );
};

CU_EXT_API LRESULT AfsSend( UINT nCode, UINT nCtrlID, UINT id, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/ )
{
	CWnd* pWnd = AfsGetCtrlWnd( nCtrlID );
	if( NULL == pWnd )
		return 0;

	return AfsSend( nCode, pWnd, id, wParam, lParam );
}

CU_EXT_API LRESULT AfsSend( UINT nCode, HWND hWnd, UINT id, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/ )
{
	CWnd* pWnd = CWnd::FromHandlePermanent( hWnd );
	if( NULL == pWnd )
		return 0;

	return AfsSend( nCode, pWnd, id, wParam, lParam );
}

CU_EXT_API LRESULT AfsSend( UINT nCode, CWnd* pWnd, UINT id, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/ )
{
	LRESULT lResult = 0;
	if( NULL == pWnd )
		return 0;

	_CWnd* _pWnd = (_CWnd*)pWnd;
	const AFX_MSGMAP* pMessageMap; pMessageMap = _pWnd->GetMessageMap();
	const AFX_MSGMAP_ENTRY* lpEntry;

#ifdef _AFXDLL
	for (/* pMessageMap already init'ed */; pMessageMap->pfnGetBaseMap != NULL;
		pMessageMap = (*pMessageMap->pfnGetBaseMap)())
#else
	for (/* pMessageMap already init'ed */; pMessageMap->pBaseMap != NULL;
		pMessageMap = pMessageMap->pBaseMap)
#endif
	{
		// Note: catch not so common but fatal mistake!!
		//      BEGIN_MESSAGE_MAP(CMyWnd, CMyWnd)
#ifdef _AFXDLL
		ASSERT(pMessageMap != (*pMessageMap->pfnGetBaseMap)());
#else
		ASSERT(pMessageMap != pMessageMap->pBaseMap);
#endif
		lpEntry = pMessageMap->lpEntries;
		if( (lpEntry = AfxFindMessageEntry( lpEntry, WIN_MSG, nCode, id )) != NULL )
			goto LDispatch;
	}

	return 0;

LDispatch:;
	union MessageMapFunctions mmf;
	mmf.pfn = lpEntry->pfn;

	int nSig = lpEntry->nSig;
	switch( nSig )
	{
	default:
		return 0;

	case AfxSig_vv:
		(pWnd->*mmf.pfn_v_v)();
		return 1;	// dispatched

	case AfxSig_bv:
		lResult = (pWnd->*mmf.pfnCmd_b_v)();
		if( WMC_CMDROUTE == nCode )
			return AfsSend( nCode, pWnd->GetParent(), id, wParam, lParam );
		return lResult;

	case AfxSig_vw: // AfxSig_vb, AfxSig_vh
		if( WMC_CMD == nCode )
			(pWnd->*mmf.pfn_v_u)( wParam );
		else
			(pWnd->*mmf.pfn_v_u)( id );
		return 1;	// dispatched

	case AfxSig_bw:
		if( WMC_CMD == nCode )
			lResult = (pWnd->*mmf.pfnCmd_b_u)( wParam );
		else
			lResult = (pWnd->*mmf.pfnCmd_b_u)( id );

		if( WMC_CMDROUTE == nCode )
			return AfsSend( nCode, pWnd->GetParent(), id, wParam, lParam );
		return lResult;	// dispatched

	case AfxSig_lwl:
		if( lpEntry->nID != lpEntry->nLastID )
			lResult = (pWnd->*mmf.pfn_l_w_l)( id, lParam );
		else
			lResult = (pWnd->*mmf.pfn_l_w_l)( wParam, lParam );
		break;
	}

	return lResult;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL LoadWindowPlacement( LPCTSTR ptszRegKey, WINDOWPLACEMENT& wndPlace )
{
	int			nReturn;
	HKEY		hKey;
	ULONG		ulType;
	
	do
	{
		char strWinPlace[50];
		unsigned long ulSize = 50;

		nReturn = RegOpenKeyEx( HKEY_CURRENT_USER, ptszRegKey, 0, KEY_QUERY_VALUE,&hKey );
		
		if (nReturn != ERROR_SUCCESS)
			break;
		
		nReturn = RegQueryValueEx( hKey,_T("MainWnd"),NULL, &ulType,
								   (BYTE*)strWinPlace, &ulSize );

		if( nReturn != ERROR_SUCCESS )
			break;

		if( strlen( strWinPlace ) < 44 )
		{
			nReturn = -1;
			break;
		}
			
#ifdef _UNICODE
		sscanf( (const char*)strWinPlace, "%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d",
				&wndPlace.flags,
				&wndPlace.length,
				&wndPlace.ptMaxPosition.x,
				&wndPlace.ptMaxPosition.y,
				&wndPlace.ptMinPosition.x,
				&wndPlace.ptMinPosition.y,
				&wndPlace.rcNormalPosition.left,
				&wndPlace.rcNormalPosition.top,
				&wndPlace.rcNormalPosition.right,
				&wndPlace.rcNormalPosition.bottom,
				&wndPlace.showCmd );
#else
		sscanf( (const char*)strWinPlace, _T("%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d"), 
				&wndPlace.flags,
				&wndPlace.length,
				&wndPlace.ptMaxPosition.x,
				&wndPlace.ptMaxPosition.y,
				&wndPlace.ptMinPosition.x,
				&wndPlace.ptMinPosition.y,
				&wndPlace.rcNormalPosition.left,
				&wndPlace.rcNormalPosition.top,
				&wndPlace.rcNormalPosition.right,
				&wndPlace.rcNormalPosition.bottom,
				&wndPlace.showCmd );
#endif // _UNICODE
			
		HWND hDesktopWnd =  GetDesktopWindow();
		CRect rctDesktop, rctIntersect;
		GetWindowRect( hDesktopWnd, rctDesktop );
		CRect rctWnd = wndPlace.rcNormalPosition;
		rctWnd.NormalizeRect();
		if( FALSE == rctIntersect.IntersectRect( rctDesktop, &rctWnd ) )
		{
			wndPlace.rcNormalPosition = rctDesktop;
			//return FALSE;
		}
		else if( rctDesktop.bottom - 24 <= rctWnd.top )
		{
			wndPlace.rcNormalPosition = rctDesktop;
			//return FALSE;
		}
	}while(0);

	if(nReturn != ERROR_SUCCESS)
	{
		RegCloseKey( hKey );
		return FALSE;
	}

	return (ERROR_SUCCESS == RegCloseKey( hKey));
}

CU_EXT_API BOOL SaveWindowPlacement( LPCTSTR ptszRegKey, WINDOWPLACEMENT& wndPlace )
{
	if(wndPlace.showCmd == SW_SHOWMINIMIZED)
		return FALSE;

	CString csWinPlace;
	csWinPlace.Format( _T("%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d"),
		wndPlace.flags,wndPlace.length, 
		wndPlace.ptMaxPosition.x, wndPlace.ptMaxPosition.y,
		wndPlace.ptMinPosition.x,	wndPlace.ptMinPosition.y,
		wndPlace.rcNormalPosition.left, wndPlace.rcNormalPosition.top,
		wndPlace.rcNormalPosition.right,wndPlace.rcNormalPosition.bottom,
		wndPlace.showCmd );

	int  nReturn;
	HKEY hKey;

	do
	{
		nReturn = RegCreateKeyEx( HKEY_CURRENT_USER,
							ptszRegKey, 0, NULL,
							REG_OPTION_NON_VOLATILE,
							KEY_ALL_ACCESS, NULL,
							&hKey, NULL );
		if (nReturn != ERROR_SUCCESS)
			break;
		
		nReturn = RegSetValueEx( hKey,_T("MainWnd"),NULL,REG_SZ,
			(const BYTE *)LPCTSTR(csWinPlace), 50 );

	}while(0);
	
	if(nReturn != ERROR_SUCCESS)
	{
		RegCloseKey( hKey );
		return FALSE;
	}

	return (ERROR_SUCCESS == RegCloseKey( hKey));
}