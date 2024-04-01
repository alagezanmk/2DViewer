#ifndef ___G_OBJECT__PH___
#define ___G_OBJECT__PH___

class CU_EXT_CLASS CGObject
{
public:
	enum RELEASE_MODE
	{
		LOCKED_RELEASE	= 0,
		AUTO_RELEASE	= 1,
		NEVER_RELEASE	= 2,
	};

public:
	CGObject();

protected:
	virtual ~CGObject();

public:
	virtual INT AddRef();
	virtual void Release( BOOL bNoDelete = FALSE );
	virtual void OnFinalRelease();

	void* PASCAL operator new( size_t nSize );
	void* PASCAL operator new[]( size_t nSize );

	void* PASCAL operator new( size_t, void* p );
	void* PASCAL operator new[]( size_t, void* p );

#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
	void* PASCAL operator new( size_t nSize, LPCSTR lpszFileName, int nLine );
	void* PASCAL operator new[]( size_t nSize, LPCSTR lpszFileName, int nLine );
#endif

	void PASCAL operator delete( void* p );
	void PASCAL operator delete[]( void* p );

#if _MSC_VER >= 1200
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
	void PASCAL operator delete( void* p, void* pPlace );
	void PASCAL operator delete[]( void* p, void* pPlace );

	void PASCAL operator delete( void *p, LPCSTR lpszFileName, int nLine );
	void PASCAL operator delete[]( void *p, LPCSTR lpszFileName, int nLine );
#endif
#endif

#ifdef _DEBUG
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:
	INT		m_nFlag;
	DWORD	m_dwRefCnt;

#ifdef _DEBUG
	CString m_cszFileName;
#endif
};

#endif //!___G_OBJECT__PH___

