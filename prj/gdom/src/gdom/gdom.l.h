#ifndef ___GDOM__L__PH___
#define ___GDOM__L__PH___

#ifndef GDOM_IMPORT
 #define GDOM_IMPORT				__declspec(dllimport)
#endif

#ifndef GDOM_EXPORT
 #define GDOM_EXPORT				__declspec(dllexport)
#endif

#ifndef DLL_IMPORT
 #define DLL_IMPORT				GDOM_IMPORT
#endif

#ifndef DLL_EXPORT
 #define DLL_EXPORT				GDOM_EXPORT
#endif

#ifndef CLASS_IMPORT
 #define CLASS_IMPORT			GDOM_IMPORT
#endif

#ifndef CLASS_EXPORT
 #define CLASS_EXPORT			GDOM_EXPORT
#endif

#ifdef _GDOM_LIB
 #define GDOM_EXT_API
 #define GDOM_EXT_DATA
 #define GDOM_EXT_CLASS
#else
 #ifdef _GDOM_EXT
  #define GDOM_EXT_API			GDOM_EXPORT
  #define GDOM_EXT_DATA			GDOM_EXPORT
  #define GDOM_EXT_CLASS			GDOM_EXPORT
 #else
  #define GDOM_EXT_API			GDOM_IMPORT
  #define GDOM_EXT_DATA			GDOM_IMPORT
  #define GDOM_EXT_CLASS			GDOM_IMPORT
  #ifdef _DEBUG
   #pragma comment (lib, "gdomD.lib" )
  #else
   #pragma comment (lib, "gdom.lib" )
  #endif
 #endif
#endif

#include <math.h>
#include <afxtempl.h>
#include <Shlwapi.h>

#include <cu\cu.l.h>
#include <gl\g.l.h>

#endif //!___GDOM__L__PH___