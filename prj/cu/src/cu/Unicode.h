#ifndef ___UNICODE__PH___
#define ___UNICODE__PH___

inline INT latoi( const TCHAR * c)
{
#ifndef _UNICODE
	return atoi( c);
#else
	return _wtoi( c );
#endif
}

inline INT latoi( TCHAR* ptchStr )
{
#ifndef _UNICODE
	return atoi( ptchStr );
#else
	return _wtoi( ptchStr );
#endif
}

inline INT litoa( INT value, TCHAR* ptchStr, INT radix )
{
	return *_itot( value, ptchStr, radix );
}

inline double latodf( const TCHAR * c)
{
#ifndef _UNICODE
	return atof( c);
#else
	double f;
	swscanf( c, _T("%lf"), &f );
	return f;
#endif
}

inline float latof( const TCHAR * c)
{
#ifndef _UNICODE
	return (float)atof( c);
#else
	float f;
	swscanf( c, _T("%f"), &f );
	return f;
#endif
}

#ifndef _UNICODE
#define	lstrtok strtok
#else
#define	lstrtok wcstok
#endif

#ifndef _UNICODE
#define	lstrtod strtod
#else
#define	lstrtod wcstod
#endif

#ifndef _UNICODE
#define	lstrchr strchr
#else
#define	lstrchr wcschr
#endif

#ifdef _UNICODE
#define lstrtod wcstod
#else
#define lstrtod strtod
#endif

#ifdef _UNICODE
#define lsscanf swscanf
#else
#define lsscanf sscanf
#endif

#ifdef _UNICODE
#define lunlink _wunlink
#else
#define lunlink _unlink
#endif

INT GetStringNo( TCHAR *ptchBuf, INT nLen );

#ifdef _UNICODE
#define lisalnum isalnum
#else
#define lisalnum iswalnum
#endif

#ifndef _UNICODE		
#define lisalpha isalpha
#else
#define lisalpha iswalpha
#endif

#ifndef _UNICODE		
#define lisspace isspace
#else
#define lisspace iswspace
#endif

#ifndef _UNICODE
#define lstrnicmp _strnicmp
#else
#define lstrnicmp _wcsnicmp
#endif

#ifndef _UNICODE
#define lstrncat strncat( ptchSrc, ptchTarget, nLen );
#else
#define lstrncat wcsncat( ptchSrc, ptchTarget, nLen );
#endif

CU_EXT_API BOOL lIsStrEmpty( const TCHAR* pctsz );

#endif //!___UNICODE__PH___