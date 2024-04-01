#ifndef ___I_GL__PH___
#define ___I_GL__PH___

#include <gl\gCoord.h>

#ifdef _WIN32
 typedef HDC			HGD;
 typedef HWND			HWIN;
#endif

///class CU_EXT_CLASS GColor
///{
///};
///
///class CU_EXT_CLASS GPalette
///{
///public:
///	GPalette();
///	virtual ~GPalette();
///	
///	GPalette* Clone();
///};
///
///class CU_EXT_CLASS GImageData
///{
///	GImageData();
///	virtual ~GImageData();
///
///	GImageData* Clone();
///
///	INT GetWidth();
///	INT GetHeight();
///	INT GetWidthBytes();
///	INT GetBitCount();
///
///protected:
///	INT		m_nWidth;
///	INT		m_nHeight;
///	INT		m_nWidthBytes;
///	INT		m_nBitCount;
///	void*	m_pBitData;
///};
///
///class CU_EXT_CLASS GImage
///{
///public:
///	enum { enImgTypeUnknown, enImgTypeBMP, enImgTypeJPG, enImgTypeGIF, enImgTypePNG };
///
///	enum { en1BitCount, en2BitCount, en4BitCount, en8BitCount,
///		   en16BitCount, en24BitCount, en32BitCount };
///
///public:
///	GImage();
///	GImage( const TCHAR* ptszFilename );
///	virtual ~GImage();
///
///	GImage* Clone();
///
///	BOOL Read( const TCHAR* ptszFilename );
///	BOOL Save( const TCHAR* ptszFilename, INT nType );
///
///	INT GetType();
///	INT GetBitCount();
///
///    INT GetWidth();
///    INT GetHeight();
///
///	INT	GetHorzDpi();
///	INT	GetVertDpi();
///
///	void GetDpi( INT& rnXDpi, INT& rnYDpi );
///	void SetDpi( INT nXDpi, INT nYDpi );
///
///	INT GetFrameCount();
///	INT SelectFrame( INT nIndex );
///
///	INT GetPaletteSize();
///	INT GetPalette( GPalette& rPalette, INT nSize );
///	INT SetPalette( GPalette& rPalette, INT nSize );
///
///	void GetPixel( INT x, INT y, GColor* pColor );
///	void SetPixel( INT x, INT y, const GColor& rColor );
///
///	INT GetRawDataSize();
///	INT SetRawData( void* pvData, INT nSize );
///
///	INT GetBits( const GRect& rRect, GImageData* pBitmapData );
///	INT SetBits( const GRect& rRect, GImageData* pBitmapData );
///
///	static GImage* FromBITMAPINFO( BITMAPINFO* pBitmapInfo, void* pvData );
///	static GImage* FromHBITMAP( HBITMAP hBitmap, HPALETTE hPalette );
///	static GImage* FromHICON( HICON hIcon );
///	static GImage* FromResource( HINSTANCE hInstance, const TCHAR* ptszBitmapName );
///
///protected:
///	CString		m_cszFilename;
///	INT			m_nWidth;
///	INT			m_nHeight;
///
///	INT			m_nXDpi;
///	INT			m_nYDpi;
///};

class CU_EXT_CLASS CGPen
{
};

class CU_EXT_CLASS CGBrush
{
};

class CU_EXT_CLASS CGC;
class CU_EXT_CLASS CGCCreator;
class CU_EXT_CLASS CGL
{
public:
	enum { enGCTypeUnknown, enGCTypePaint, enGCTypeClient, enGCTypeWindow };

public:
	CGL();
	CGL( CGCCreator* pCreator, HGD hGD );
	CGL( CGCCreator* pCreator, HWIN hWin, INT nGCType = enGCTypeClient );
	CGL( HGD hGD );
	CGL( HWIN hWin, INT nGCType = enGCTypeClient );
	CGL( CGC* pGC );
	virtual ~CGL();

	void Constructor();
	static BOOL SetDefaultGC( CGCCreator* pCreator );
	static void DeleteDefaultGC();

	void SetTransform( const Matrix& rMtx );

	BOOL MoveTo( INT x, INT y );
	BOOL MoveTo( FLOAT x, FLOAT y );

	BOOL LineTo( INT x, INT y );
	BOOL LineTo( FLOAT x, FLOAT y );

	BOOL MoveToRel( INT dx, INT dy );
	BOOL MoveToRel( FLOAT dx, FLOAT dy );

	BOOL LineToRel( INT dx, INT dy );
	BOOL LineToRel( FLOAT dx, FLOAT dy );

	BOOL Line( INT x1, INT y1, INT x2, INT y2 );
	BOOL Line( FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2 );

	BOOL Rectangle( INT x1, INT y1, INT x2, INT y2 );
	BOOL Rectangle( FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2 );

	BOOL Circle( INT cx, INT cy, INT nRadius );
	BOOL Circle( FLOAT cx, FLOAT cy, FLOAT nRadius );

protected:
	static CGCCreator*	m_pGCCreator;
	GPointF				m_arfPoint[30];
	GPointF				m_ptfCurPos;

public:
	CGC*				m_pGC;
};

class CU_EXT_CLASS CGC
{
public:
	CGC();
	CGC( HGD hGD );
	CGC( HWIN hWin, INT nGCType = CGL::enGCTypeClient );
	virtual ~CGC();

	virtual BOOL DrawPolygon( GPointF* pPoint, INT nCount );
	virtual BOOL FillPolygon( GPointF* pPoint, INT nCount );

	virtual BOOL DrawBezier( GPointF* pPoint, INT nCount );
	virtual BOOL FillBezier( GPointF* pPoint, INT nCount );

	virtual BOOL StartFigure();
	virtual BOOL CloseFigure();

public:
	INT		m_nGCType;
};

class CU_EXT_CLASS CGCCreator
{
public:
	virtual CGC* Create( HGD hGD );
	virtual CGC* Create( HWIN hWin, INT nGCType = CGL::enGCTypeClient );
};

#endif //!___I_GL__PH___