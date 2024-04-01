#include "stdafx.h"
#include <gl\Gdip.h>

CU_EXT_API Region* CreateRegion( GraphicsPath* pgPath )  {
	return new Region( pgPath );  }

CU_EXT_API void DeleteRegion( Region* pgRgn )  {
	delete pgRgn; }

CU_EXT_API Brush* CreateGdipSolidBrush( const Color& color ) {
	return new SolidBrush( color ); }

CU_EXT_API Brush* CreateGdipHatchBrush( INT nHatchStyle, const Color& color, const Color& backColor /*= Color()*/ ) {
	return new HatchBrush( (HatchStyle)nHatchStyle, color, backColor ); }

CU_EXT_API Pen* CreateGdipPen( const Color& color, FLOAT fThickness /*= 1.0f*/ ) {
	return new Pen( color, fThickness ); }

CU_EXT_API void DeleteGdipBrush( Brush* pBrush )
{
	ASSERT( pBrush );
	delete pBrush;
}

CU_EXT_API void DeleteGdipPen( Pen* pPen )
{
	ASSERT( pPen );
	delete pPen;
}

CU_EXT_API Graphics* CreateGraphics( const HDC& rhDC ) 
{
	Graphics* pGdip = new Graphics( rhDC ); 
	return pGdip;
}

CU_EXT_API Graphics* CreateGraphics( Bitmap* pgbmp )
{
	Graphics* pGdip = new Graphics( pgbmp ); 
	return pGdip;
}

CU_EXT_API void DeleteGraphics( Graphics* pGdip ) {
	delete pGdip; }

CU_EXT_API void DeleteGdipImage( Image* pImage ) {
	delete pImage; }

CU_EXT_API Matrix* CreateMatrix() {
	return new Matrix; }

CU_EXT_API void	DeleteMatrix( Matrix* pMtx )
{
	if( pMtx )
		delete pMtx;
}

CU_EXT_API Bitmap* CreateBitmap( IN INT width,
				   IN INT height,
				   IN INT stride, PixelFormat format,
				   IN BYTE* scan0 )
{
	return new Bitmap( width, height, stride, format, scan0 );
}

CU_EXT_API Bitmap* CreateBitmap( IN INT width,
				   IN INT height,
				   IN PixelFormat format /*= PixelFormat32bppARGB*/ )
{
	return new Bitmap( width, height, format );
}

CU_EXT_API Bitmap* CreateBitmap( IN INT width,
				   IN INT height,
				   IN  Graphics* target )
{
	return new Bitmap( width, height, target );
}

CU_EXT_API void DeleteBitmap( Bitmap* pBmp )
{
	delete pBmp;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CU_EXT_API void Draw3DRect( Graphics* pGdip, RectF* prcf, Color clrTopLeft, Color clrRightBottom)
{
	// Create pen
	Pen pen( clrTopLeft, 1 );
	pen.SetAlignment( PenAlignmentInset );

	FLOAT x1 = prcf->GetLeft() + 0.5f;
	FLOAT x2 = prcf->GetRight() - 0.5f;
	FLOAT y1 = prcf->GetTop() + 0.5f;
	FLOAT y2 = prcf->GetBottom() - 0.5f;

	PointF ptf[3];
	ptf[2].X = x1;
	ptf[2].Y = y2 - 0.5f;

	ptf[1].X = x1;
	ptf[1].Y = y1;

	ptf[0].X = x2 - 0.5f;
	ptf[0].Y = y1;

	xGraphicsPath path;
	path.AddPolyline( ptf, 3 );
	pGdip->DrawPath( &pen, &path );

	ptf[0].X = x2;
	ptf[0].Y = y1 + 0.5f;

	ptf[1].X = x2;
	ptf[1].Y = y2;

	ptf[2].X = x1 - 0.5f;
	ptf[2].Y = y2;
	pen.SetColor( clrRightBottom );
	path.Reset();
	path.AddPolyline( ptf, 3 );
	pGdip->DrawPath( &pen, &path );
}

CU_EXT_API void GetBtnShades( ARGB argb, ARGB* pargbShadow, ARGB* pargbHilite, INT nShadow /*= 150*/, INT nHilite /*= 80*/ )
{
	if( NULL == pargbShadow && NULL == pargbHilite )
		return;

 	INT R  = ARGB_RED  (argb);
	INT G  = ARGB_GREEN(argb);
	INT B  = ARGB_BLUE (argb);
	INT nA = ARGB_ALPHA(argb);

	INT nR = R - nShadow;
	INT nG = G - nShadow;
	INT nB = B - nShadow;
	if( pargbShadow )
	{
		if( nR < 0 ) nR = 0;
		if( nG < 0 ) nG = 0;
		if( nB < 0 ) nB = 0;
		*pargbShadow = MAKE_ARGB( nA, nR, nG, nB );
	}

	if( pargbHilite )
	{
		nR = R + nHilite;
		nG = G + nHilite;
		nB = B + nHilite;
		if( nR > 255 ) nR = 255;
		if( nG > 255 ) nG = 255;
		if( nB > 255 ) nB = 255;
		*pargbHilite = MAKE_ARGB( nA, nR, nG, nB );
	}
}

///CU_EXT_API void RoundRndToBezier( FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT x3, FLOAT y3, PointF* ppts )
///{
///    // MAGICAL CONSTANT to map ellipse to beziers	2/3*(sqrt(2)-1) 
///    const DOUBLE EToBConst = 0.2761423749154; 
///	
///	FLOAT nCx = x3 * 2;
///	FLOAT nCy = y3 * 2;
///
///    CSizeF  cbOffset( (FLOAT)(nCx * EToBConst), (FLOAT)(nCy * EToBConst) );
///
///	ppts[0].X  = x1;							// pt
///	ppts[0].Y  = y1 + y3;
///
///	ppts[1].X  = x1;							// Control pt
///	ppts[1].Y  = ppts[0].Y - cbOffset.cy;
///
///	ppts[2].X  = x1 + x3 - cbOffset.cx;			// Control pt
///	ppts[2].Y  = y1;
///
///	ppts[3].X  = x1 + x3;						// pt
///	ppts[3].Y  = y1;
///
///	ppts[4]    = ppts[3];						// Control pt
///
///	ppts[5].X  = x2 - x3;						// Control pt
///	ppts[5].Y  = y1;
///
///	ppts[6]    = ppts[5];						// pt
///
///	ppts[7].X  = ppts[6].X + cbOffset.cx;		// Control pt
///	ppts[7].Y  = y1;
///
///	ppts[8].X  = x2;							// Control pt
///	ppts[8].Y  = ppts[1].Y;
///
///	ppts[9].X  = x2;							// pt
///	ppts[9].Y  = ppts[0].Y;
///
///	ppts[10]   = ppts[9];						// Control pt
///
///	ppts[11].X = x2;							// Control pt
///	ppts[11].Y = y2 - y3;
///
///	ppts[12]   = ppts[11];						// pt
///
///	ppts[13].X = x2;							// Control pt
///	ppts[13].Y = y2 - y3 + cbOffset.cy;
///
///	ppts[14].X = ppts[7].X;						// Control pt
///	ppts[14].Y = y2;
///
///	ppts[15].X = ppts[6].X;						// pt
///	ppts[15].Y = y2;
///
///	ppts[16]   = ppts[15];						// Control pt
///
///	ppts[17].X = ppts[4].X;						// Control pt
///	ppts[17].Y = y2;
///
///	ppts[18]   = ppts[17];						// pt
///
///	ppts[19].X = ppts[2].X;						// Control pt
///	ppts[19].Y = y2;
///
///	ppts[20].X = x1;							// Control pt
///	ppts[20].Y = ppts[13].Y;
///
///	ppts[21].X = x1;							// pt
///	ppts[21].Y = ppts[12].Y;
///
///	ppts[22]   = ppts[21];						// Control pt
///
///	ppts[23].X = x1;							// Control pt
///	ppts[23].Y = ppts[10].Y;
///
///	ppts[24]   = ppts[0];						// pt
///}

CU_EXT_API int GetCodecClsid( const WCHAR* format, CLSID* pClsid )
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders( num, size, pImageCodecInfo );
   for( UINT j = 0; j < num; j++ )
   {
      if( wcscmp( pImageCodecInfo[j].MimeType, format ) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         return j;  // Success
      }    
   } // for

   return -1;  // Failure
}