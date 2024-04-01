#include "stdafx.h"
#include "gObject.h"

namespace NCGObject
{
struct SNewAllocData
{
	void*	pMem;
	INT		nMemSize;
	INT		nCount;
	CString cszFileInfo;
};

static CArray <SNewAllocData, SNewAllocData&> gs_arpMemAllocBlock;
static CCriticalSection	gs_MemAllocCriticalSection;

static void Lock() {
	gs_MemAllocCriticalSection.Lock(); }

static void Unlock() {
	gs_MemAllocCriticalSection.Unlock(); }

static void Add( SNewAllocData& rsData ) 
{
	Lock();
	gs_arpMemAllocBlock.Add( rsData );
	Unlock();
}

static void RemoveAt( INT nIndex ) 
{
	Lock();
	gs_arpMemAllocBlock.RemoveAt( nIndex );
	Unlock();
}
};

void* PASCAL CGObject::operator new( size_t nSize )
{
	NCGObject::SNewAllocData sNewAllocData;
	sNewAllocData.nMemSize = nSize;
	sNewAllocData.nCount = 1;
#ifdef _AFX_NO_DEBUG_CRT
	sNewAllocData.pMem = ::operator new( nSize );
#else
	sNewAllocData.pMem = ::operator new( nSize, _NORMAL_BLOCK, NULL, 0 );
#endif // _AFX_NO_DEBUG_CRT
	NCGObject::Add( sNewAllocData );
	return sNewAllocData.pMem;
}

void* PASCAL CGObject::operator new[]( size_t nSize ) 
{
	NCGObject::SNewAllocData sNewAllocData;
	sNewAllocData.nMemSize = nSize;
	sNewAllocData.nCount = -1;
#ifdef _AFX_NO_DEBUG_CRT
	sNewAllocData.pMem = ::operator new( nSize );
#else
	sNewAllocData.pMem = ::operator new( nSize, _NORMAL_BLOCK, NULL, 0 );
#endif // _AFX_NO_DEBUG_CRT
	NCGObject::Add( sNewAllocData );
	return sNewAllocData.pMem;
}

void* PASCAL CGObject::operator new( size_t, void* p ) 
{
	ASSERT( FALSE );
	return p; 
}

void* PASCAL CGObject::operator new[]( size_t, void* p ) 
{
	ASSERT( FALSE );
	return p; 
}

#ifdef _DEBUG
// _DEBUG new & delete

#ifndef _AFX_NO_DEBUG_CRT
void* PASCAL CGObject::operator new( size_t nSize, LPCSTR lpszFileName, int nLine )
{
	NCGObject::SNewAllocData sNewAllocData;
	sNewAllocData.nMemSize = nSize;
	sNewAllocData.nCount = 1;
	sNewAllocData.pMem = ::operator new( nSize, _NORMAL_BLOCK, lpszFileName, nLine );
	sNewAllocData.cszFileInfo.Format( _T("%s, LineNo: %d"), lpszFileName, nLine );

	NCGObject::Add( sNewAllocData );
	return sNewAllocData.pMem; 
}

void* PASCAL CGObject::operator new[]( size_t nSize, LPCSTR lpszFileName, int nLine ) 
{
	NCGObject::SNewAllocData sNewAllocData;
	sNewAllocData.nMemSize = nSize;
	sNewAllocData.nCount = -1;
	sNewAllocData.pMem = ::operator new( nSize, _NORMAL_BLOCK, lpszFileName, nLine );
	sNewAllocData.cszFileInfo.Format( _T("%s, LineNo: %d"), lpszFileName, nLine );

	NCGObject::Add( sNewAllocData );
	return sNewAllocData.pMem; 
}
#endif // !_AFX_NO_DEBUG_CRT

#if _MSC_VER >= 1200
void PASCAL CGObject::operator delete( void* p, void* ) 
{
	CGObject* pThis = (CGObject*)p;
	ASSERT( 0 == pThis->m_dwRefCnt );	// This CGBase derived object is
										// deleted without Release()ing properly

#ifdef _AFX_NO_DEBUG_CRT
	free( p );
#else
	_free_dbg( p, _NORMAL_BLOCK );
#endif
}

void PASCAL CGObject::operator delete[]( void* p, void* ) 
{
	CGObject* pThis = (CGObject*)p;
	ASSERT( 0 == pThis->m_dwRefCnt );	// This CGBase derived object is 
										// deleted without Release()ing properly

#ifdef _AFX_NO_DEBUG_CRT
	free( p );
#else
	_free_dbg( p, _NORMAL_BLOCK );
#endif
}
#endif //_MSC_VER >= 1200

#if _MSC_VER >= 1200
void PASCAL CGObject::operator delete( void *pObject, 
									   LPCSTR /* lpszFileName */,
									   int /* nLine */)
{
	CGObject* pThis = (CGObject*)pObject;
	ASSERT( 0 == pThis->m_dwRefCnt );	// This CGBase derived object is 
										// deleted without Release()ing properly

#ifdef _AFX_NO_DEBUG_CRT
	free( pObject );
#else
	_free_dbg( pObject, _NORMAL_BLOCK );
#endif
}

void PASCAL CGObject::operator delete[]( void *pObject, 
								         LPCSTR /* lpszFileName */, 
								 	     int /* nLine */)
{
	CGObject* pThis = (CGObject*)pObject;
	ASSERT( 0 == pThis->m_dwRefCnt );	// This CGBase derived object is
										// deleted without Release()ing properly

#ifdef _AFX_NO_DEBUG_CRT
	free( pObject );
#else
	_free_dbg( pObject, _NORMAL_BLOCK );
#endif
}

#endif //_MSC_VER >= 1200
#endif //_DEBUG

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// \brief Constructs a CGBase object. 
// The default version is automatically called by the constructor 
// of your derived class. 
CGObject::CGObject()
{
	m_dwRefCnt = 0;

	NCGObject::Lock();
	INT nCount = NCGObject::gs_arpMemAllocBlock.GetSize();
	NCGObject::SNewAllocData* psNewAllData = NCGObject::gs_arpMemAllocBlock.GetData();
	INT i;
	for( i = 0; i < nCount; i++ )
	{
		if( (INT)this >= (INT)psNewAllData[i].pMem &&  (INT)this < (INT)psNewAllData[i].pMem + psNewAllData[i].nMemSize )
			break;
	}

	if( i == nCount )	// Not found in New memory Track List
	{
		m_nFlag = FALSE;
		m_nFlag = LOCKED_RELEASE;
	}
	else
	{

		if( -1 == psNewAllData[i].nCount )
		{
			// Memory array using new[]
			psNewAllData[i].nCount = *((INT*)psNewAllData[i].pMem);
		}

#ifdef _DEBUG
		m_cszFileName = psNewAllData[i].cszFileInfo;
#endif
		psNewAllData[i].nCount--;
		if( 0 == psNewAllData[i].nCount )
			NCGObject::RemoveAt( i );

		m_nFlag = TRUE;
		m_nFlag = AUTO_RELEASE;
	}
	NCGObject::Lock();
}


CGObject::~CGObject()
{}


INT CGObject::AddRef()
{
	ASSERT( m_dwRefCnt >= 0 );
	return ++m_dwRefCnt;
}

void CGObject::Release( BOOL bNoDelete /*= FALSE*/ )
{
	ASSERT( m_dwRefCnt > 0 );
	if( NEVER_RELEASE == m_nFlag && m_dwRefCnt <= 0 )
	{
		m_dwRefCnt = 1;
		return;
	}

	--m_dwRefCnt;
	if( m_dwRefCnt <= 0 && FALSE == bNoDelete )
	{
		if( AUTO_RELEASE == m_nFlag )
		{
			OnFinalRelease();
			delete this;
			return;
		}

		m_dwRefCnt = 0;
	}

	if( NEVER_RELEASE == m_nFlag && m_dwRefCnt <= 0 )
		m_dwRefCnt = 1;
}

void CGObject::OnFinalRelease()
{
#ifdef _DEBUG
	TRACE( _T("CGObject::OnFinalRelease: %s\n"), m_cszFileName );
#endif //_DEBUG
}

#ifdef _DEBUG
void CGObject::Dump( CDumpContext& dc ) const
{
	dc << "[CGBase at " << this << " ]\n";
	dc << "\t AutoDelete[" << m_nFlag << "]\n";
	dc << "\t Ref count[" << m_dwRefCnt << "]\n";
}

#endif //_DEBUG

void PASCAL CGObject::operator delete( void* p ) 
{
	CGObject* pThis = (CGObject*)p;
	ASSERT( 0 == pThis->m_dwRefCnt );	// This CGBase derived object is 
										// deleted without Release()ing properly

#ifdef _AFX_NO_DEBUG_CRT
	free( p );
#else
	_free_dbg( p, _NORMAL_BLOCK );
#endif
}

void PASCAL CGObject::operator delete[]( void* p ) 
{
	CGObject* pThis = (CGObject*)p;
	ASSERT( 0 == pThis->m_dwRefCnt );	// This CGBase derived object is 
										// deleted without Release()ing properly

#ifdef _AFX_NO_DEBUG_CRT
	free( p );
#else
	_free_dbg( p, _NORMAL_BLOCK );
#endif
}

