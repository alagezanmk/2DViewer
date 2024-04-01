#include "stdafx.h"
#include <afxdllx.h>
#include <cu\key.win.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment( lib, "shlwapi.lib" )
static AFX_EXTENSION_MODULE CuDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
#ifdef _DEBUG
		TRACE0("cuD.DLL Initializing!\n");
#else
		TRACE0("cu.DLL Initializing!\n");
#endif //_DEBUG
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(CuDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		SetKbStatusHook( hInstance );
		SetMsStatusHook( hInstance );
		new CDynLinkLibrary(CuDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		ReleaseKbStatusHook();
		ReleaseMsStatusHook();

#ifdef _DEBUG
		TRACE0("cuD.DLL Terminating!\n");
#else
		TRACE0("cu.DLL Terminating!\n");
#endif //_DEBUG
		// Terminate the library before destructors are called
		AfxTermExtensionModule(CuDLL);
	}
	return 1;   // ok
}
