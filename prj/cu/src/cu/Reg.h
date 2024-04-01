#ifndef ____REG__PH____
#define ____REG__PH____

CU_EXT_API INT GetProfileID2Value( INT nID, INT nStartID, INT nStartValue, INT nCount, INT nDefValue = 0 );
CU_EXT_API INT GetProfileValue2ID( INT nValue, INT nStartID, INT nStartValue, INT nCount, INT nDefID );

CU_EXT_API BOOL WriteProfileInt( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, INT nValue );
CU_EXT_API INT GetProfileInt( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, INT nDefault, INT nMin, INT nMax );

CU_EXT_API BOOL WriteProfileFloat( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, FLOAT fValue );
CU_EXT_API FLOAT GetProfileFloat( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, FLOAT fDefault, FLOAT fMin, FLOAT fMax );

CU_EXT_API BOOL WriteProfileBool( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, BOOL bValue );
CU_EXT_API BOOL GetProfileBool( CWinApp* pApp, LPCTSTR lpszSection, LPCTSTR lpszEntry, BOOL bDefault );

#endif //____REG__PH____