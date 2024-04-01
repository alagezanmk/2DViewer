#include "stdafx.h"
#include "cu\file.h"
#include "shlwapi.h"

#pragma comment(lib, "shlwapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CU_EXT_API INT MakeFullname( CString& rcszFullname, LPCTSTR ptszPathname, LPCTSTR ptszFilename, LPCTSTR ptszExt /*= NULL*/ )
{
	if( (LPCTSTR)rcszFullname != ptszPathname )
		rcszFullname = ptszPathname;

	PathRemoveBackslash( (LPTSTR)(LPCTSTR)rcszFullname );
	rcszFullname.ReleaseBuffer();
	rcszFullname += _T("\\");
	rcszFullname += ptszFilename;

	if( ptszExt )
	{
		if( _T('.') == ptszExt[0] )
			ptszExt++;

		rcszFullname += ptszExt;
	}

	return rcszFullname.GetLength();
}

CU_EXT_API INT GetFileExtension( LPCTSTR ptszFilename )
{
	static TCHAR tszExtension[100];
	LPCTSTR ptszExt = PathFindExtension( ptszFilename );
	if( NULL == ptszExt )
		return 0;

	lstrcpyn( tszExtension, ptszExt + 1, 100 ); 
	return lstrlen( tszExtension );
}

CU_EXT_API INT GetFilename( CString& rcszFilename, LPCTSTR ptszFullname )
{
	CString cszDrive;
	CString cszFoldername;
	CString cszExt;
	
#ifdef _UNICODE
	_wsplitpath( 
#else //_UNICODE
	_splitpath( 
#endif //_UNICODE
		ptszFullname, cszDrive.GetBuffer( 10 ),
					  cszFoldername.GetBuffer( 1000 ),
					  rcszFilename.GetBuffer( 1000 ),
					  cszExt.GetBuffer( 100 )
			   );

	rcszFilename.ReleaseBuffer();
	return rcszFilename.GetLength();
}

CU_EXT_API INT GetFoldername( CString& rcszFoldername, LPCTSTR ptszFullname )
{
	CString cszDrive;
	CString cszFilename;
	CString cszExt;
	
#ifdef _UNICODE
	_wsplitpath( 
#else //_UNICODE
	_splitpath( 
#endif //_UNICODE
		ptszFullname, cszDrive.GetBuffer( 10 ),
					  rcszFoldername.GetBuffer( 1000 ),
					  cszFilename.GetBuffer( 1000 ),
					  cszExt.GetBuffer( 100 )
			   );

	PathRemoveBackslash( (LPTSTR)(LPCTSTR)rcszFoldername );
	rcszFoldername.ReleaseBuffer();
	cszDrive.ReleaseBuffer();

	CString cszPathName = cszDrive + rcszFoldername;
	rcszFoldername = cszPathName;
	return rcszFoldername.GetLength();
}

CU_EXT_API void CorrectPathSlash( LPTSTR ptszPathname )
{
	INT nLen = lstrlen( ptszPathname );
	for( INT i = 0; i < nLen; i++ )
		if( _T('/') == ptszPathname[i] )
			ptszPathname[i] = _T('\\');
}
