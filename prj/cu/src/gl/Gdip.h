#ifndef ___GDI_P__PH____
#define ___GDI_P__PH____

///////////////////////////////////////////////////////////////////////////////////////////////////
/// ARGB & COLORREF Macros
#define MAKE_ARGB(a,r,g,b) 				(((ARGB) (b) << 0)    | \
										((ARGB)  (g) << 8)    | \
										((ARGB)  (r) <<  16)  | \
										((ARGB)  (a) << 24))

#define MAKE_RGB(r,g,b)					(((ARGB) (b)  << 0)   | \
										((ARGB)  (g)  << 8)   | \
										((ARGB)  (r)  <<  16) | \
										((ARGB)  (255) << 24))

#define ARGB_ALPHA( Argb )				((INT)(BYTE)(Argb >> 24))
#define ARGB_RED( Argb )				((INT)(BYTE)(Argb >> 16))
#define ARGB_GREEN( Argb )				((INT)(BYTE)(Argb >> 8))
#define ARGB_BLUE( Argb )				((INT)(BYTE)(Argb))

#define CRF_2_ARGB( crf )				(ARGB)((crf & 0xFF000000)    | \
											  ((crf & 0xFF) << 16)   | \
											  ( crf & 0x0000FF00)     | \
									          ((crf & 0xFF0000) >> 16))
#define CRF_2_COLOR( crf )				((Color)CRF_2_ARGB(crf))

#define ARGB_2_CRF( argb )				((COLORREF)(CRF_2_ARGB(argb)))
//#define ARGB_2_CRF( argb )				((COLORREF)((argb << 8) | (argb >> 24) ))
#define COLOR_2_CRF( argb )				((COLORREF)ARGB_2_CRF(argb))

///////////////////////////////////////////////////////////////////////////////////////////////
/// Extension for GDI+ Graphics path
class CU_EXT_CLASS xGraphicsPath : public GraphicsPath
{
public:
	Status AddPolyline( PointF* pptf, int count ) {
		return SetStatus(DllExports::GdipAddPathLine2( nativePath, pptf, count ) ); }
};

CU_EXT_API Brush*	CreateGdipSolidBrush( const Color& color );
CU_EXT_API Brush*	CreateGdipHatchBrush( INT nHatchStyle, const Color& color, const Color& backColor = Color() );
CU_EXT_API void	DeleteGdipBrush( Brush* pBrush );

CU_EXT_API Pen* CreateGdipPen( const Color& color, FLOAT fThickness = 1.0f );
CU_EXT_API void DeleteGdipPen( Pen* pPen );
CU_EXT_API Graphics* CreateGraphics( const HDC& rhDC );
CU_EXT_API Graphics* CreateGraphics( Bitmap* pgbmp );
CU_EXT_API void DeleteGraphics( Graphics* pGdip );
CU_EXT_API void DeleteGdipImage( Image* pImage );

CU_EXT_API Region* CreateRegion( GraphicsPath* pgPath );
CU_EXT_API Matrix* CreateMatrix();
CU_EXT_API void	DeleteMatrix( Matrix* pMtx );
CU_EXT_API void	DeleteRegion( Region* pgRgn );

CU_EXT_API Bitmap* CreateBitmap( IN INT width,
							   IN INT height,
							   IN INT stride, PixelFormat format,
							   IN BYTE* scan0 );

CU_EXT_API Bitmap* CreateBitmap( IN INT width,
							   IN INT height,
							   IN PixelFormat format = PixelFormat32bppARGB );

CU_EXT_API Bitmap* CreateBitmap( IN INT width,
							   IN INT height,
							   IN  Graphics* target );
CU_EXT_API void DeleteBitmap( Bitmap* pBmp );

CU_EXT_API void Draw3DRect( Graphics* pGdip, RectF* prcf, 
				Color clrTopLeft, Color clrRightBottom );

CU_EXT_API void RoundRndToBezier( FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT x3, FLOAT y3, PointF* ppts );

CU_EXT_API void GetBtnShades( ARGB argb, ARGB* pargbShadow, ARGB* pargbHilite, INT nShadow = 150, INT nHilite = 80 );
CU_EXT_API int GetCodecClsid( const WCHAR* format, CLSID* pClsid );

#endif  ___GDI_P__PH____