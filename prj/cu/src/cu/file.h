#ifndef ___CU__FILE__PH___
#define ___CU__FILE__PH___

CU_EXT_API INT GetCurrentFoldername( CString& rcszFoldername );
CU_EXT_API INT MakeFullname( CString& rcszFullname, LPCTSTR ptszPathname, LPCTSTR ptszFilename, LPCTSTR ptszExt = NULL );
CU_EXT_API INT GetFileExtension( LPCTSTR ptszFilename );
CU_EXT_API INT GetFilename( CString& rcszFilename, LPCTSTR ptszFullname );
CU_EXT_API INT GetFoldername( CString& rcszFoldername, LPCTSTR ptszFullname );
CU_EXT_API void CorrectPathSlash( LPTSTR ptszPathname );

#endif ___CU__FILE__PH___