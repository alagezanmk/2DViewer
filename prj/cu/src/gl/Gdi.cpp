#include "stdafx.h"
#include <gl\Gdi.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CU_EXT_DATA CRect nullCRect( 0, 0, 0, 0 );

CU_EXT_API void GetCrfBtnShades( COLORREF crf, COLORREF* pcrfShadow, COLORREF* pcrfHilite, INT nShadow /*= 150*/, INT nHilite /*= 80*/ )
{
	if( NULL == pcrfShadow && NULL == pcrfHilite )
		return;

 	INT R  = CrfRed  (crf);
	INT G  = CrfGreen(crf);
	INT B  = CrfBlue (crf);
	INT nA = CrfAlpha(crf);

	INT nR = R - nShadow;
	INT nG = G - nShadow;
	INT nB = B - nShadow;
	if( pcrfShadow )
	{
		if( nR < 0 ) nR = 0;
		if( nG < 0 ) nG = 0;
		if( nB < 0 ) nB = 0;
		*pcrfShadow = ABGR( nA, nR, nG, nB );
	}

	if( pcrfHilite )
	{
		nR = R + nHilite;
		nG = G + nHilite;
		nB = B + nHilite;
		if( nR > 255 ) nR = 255;
		if( nG > 255 ) nG = 255;
		if( nB > 255 ) nB = 255;
		*pcrfHilite = ABGR( nA, nR, nG, nB );
	}
}
