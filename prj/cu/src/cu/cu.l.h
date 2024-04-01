#ifndef ___CU__L__PH___
#define ___CU__L__PH___

#ifndef CU_IMPORT
 #define CU_IMPORT				__declspec(dllimport)
#endif

#ifndef CU_EXPORT
 #define CU_EXPORT				__declspec(dllexport)
#endif

#ifdef _CU_LIB
 #define CU_EXT_API
 #define CU_EXT_DATA
 #define CU_EXT_CLASS
#else
 #ifdef _CU_EXT
  #define CU_EXT_API			CU_EXPORT
  #define CU_EXT_DATA			CU_EXPORT
  #define CU_EXT_CLASS			CU_EXPORT
 #else
  #define CU_EXT_API			CU_IMPORT
  #define CU_EXT_DATA			CU_IMPORT
  #define CU_EXT_CLASS			CU_IMPORT
  #ifdef _DEBUG
   #pragma comment (lib, "cuD.lib" )
  #else
   #pragma comment (lib, "cu.lib" )
  #endif
 #endif
#endif

#include <math.h>
#include <afxtempl.h>
#include <afxmt.h>
#include <Shlwapi.h>

#include "Unicode.h"

#define overrided	virtual
#define overloaded

#include "SyncObject.h"

#endif //!___CU__L__PH___