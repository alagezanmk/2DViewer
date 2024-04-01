#include "stdafx.h"
#include <cu\file.h>
#include <cu\file.win.h>
#include "shlwapi.h"

#pragma comment(lib, "shlwapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CU_EXT_API INT GetDesktopFoldername( CString& rcszFoldername )
{
	rcszFoldername = _T("C:\\Documents and Settings\\sukesh\\Desktop");
	return rcszFoldername.GetLength();
}

CU_EXT_API INT GetSystemFoldername( CString& rcszFoldername )
{
	const INT cnMaxLen = 1024;
	UINT nLen = GetSystemDirectory( rcszFoldername.GetBuffer( cnMaxLen ), cnMaxLen );
	rcszFoldername.ReleaseBuffer();

	return (INT)nLen;
}

CU_EXT_API INT GetWindowsFoldername( CString& rcszFoldername )
{
	const INT cnMaxLen = 1024;
	UINT nLen = GetWindowsDirectory( rcszFoldername.GetBuffer( cnMaxLen ), cnMaxLen );
	rcszFoldername.ReleaseBuffer();

	return (INT)nLen;
}

CU_EXT_API INT GetTempFoldername( CString& rcszFoldername )
{
	const INT cnMaxLen = 1024;
	UINT nLen = GetTempPath( cnMaxLen, rcszFoldername.GetBuffer( cnMaxLen ) );
	rcszFoldername.ReleaseBuffer();

	return (INT)nLen;
}

CU_EXT_API INT GetCurrentFoldername( CString& rcszFoldername )
{
	const INT cnMaxLen = 1024;
	UINT nLen = GetCurrentDirectory( cnMaxLen, rcszFoldername.GetBuffer( cnMaxLen ) );
	rcszFoldername.ReleaseBuffer();

	return (INT)nLen;
}

CU_EXT_API INT PrependSystemPathname( CString& rcszFullname, LPCTSTR ptszFilename, INT nType /*= _EPSP_DESKTOP*/ )
{
	CString cszPathname;
	switch( nType )
	{
	case ESPT_DESKTOP:
		GetDesktopFoldername( cszPathname );
		break;

	case ESPT_SYSTEM:
		GetSystemFoldername( cszPathname );
		break;

	case ESPT_WINDOWS:
		GetWindowsFoldername( cszPathname );
		break;

	case ESPT_TEMP:
		GetTempFoldername( cszPathname );
		break;

	case ESPT_CUURENT:
		GetCurrentFoldername( cszPathname );
		break;
	}

	return MakeFullname( rcszFullname, cszPathname, ptszFilename );
}