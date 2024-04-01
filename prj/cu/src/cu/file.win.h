#ifndef ___FILE__WIN_CU__PH___
#define ___FILE__WIN_CU__PH___

enum ESYSTEM_PATH_TYPE
{
	ESPT_DESKTOP,
	ESPT_SYSTEM,
	ESPT_WINDOWS,
	ESPT_TEMP,
	ESPT_CUURENT,
};

CU_EXT_API INT PrependSystemPathname( CString& rcszFullname, LPCTSTR ptszFilename, ESYSTEM_PATH_TYPE enType = ESPT_DESKTOP );
CU_EXT_API INT GetDesktopFoldername( CString& rcszFoldername );
CU_EXT_API INT GetSystemFoldername( CString& rcszFoldername );
CU_EXT_API INT GetWindowsFoldername( CString& rcszFoldername );
CU_EXT_API INT GetTempFoldername( CString& rcszFoldername );

#endif ___FILE__WIN_CU__PH___