#include "stdafx.h"
#include <gl\gCoordF.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
extern CU_EXT_DATA const PointF nullPointF(0.f, 0.f);
extern CU_EXT_DATA const SizeF nullSizeF(0.f, 0.f);
extern CU_EXT_DATA const RectF nullRectF(0.f, 0.f, 0.f, 0.f);

//extern CU_EXT_DATA const GPointF nullGPointF(0.f, 0.f);
//extern CU_EXT_DATA const GSizeF nullGSizeF(0.f, 0.f);
//extern CU_EXT_DATA const GRectF nullGRectF(0.f, 0.f, 0.f, 0.f);

////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void CopyRect( GRectF& rrcDst, const GRectF& rrcSrc )  {
	memcpy( &rrcDst, &rrcSrc, sizeof(GRectF) ); }

CU_EXT_API void CopyRect( GRectF& rrcDst, const RECT& rrcSrc ) 
{
	rrcDst.left = (FLOAT)rrcSrc.left;
	rrcDst.top = (FLOAT)rrcSrc.top;

	rrcDst.right = (FLOAT)rrcSrc.right;
	rrcDst.bottom = (FLOAT)rrcSrc.bottom;
}

CU_EXT_API void CopyRect( GRectF& rrcDst, const Rect& rrcSrc )
{
	rrcDst.left = (FLOAT)rrcSrc.X;
	rrcDst.top = (FLOAT)rrcSrc.Y;

	rrcDst.right = (FLOAT)rrcSrc.X + (FLOAT)rrcSrc.Width;
	rrcDst.bottom = (FLOAT)rrcSrc.Y + (FLOAT)rrcSrc.Height;
}

CU_EXT_API void CopyRect( GRectF& rrcDst, const RectF& rrcSrc )
{
	rrcDst.left = rrcSrc.X;
	rrcDst.top = rrcSrc.Y;

	rrcDst.right = rrcSrc.X + rrcSrc.Width;
	rrcDst.bottom = rrcSrc.Y + rrcSrc.Height;
}

/*CU_EXT_API void CopyRect( GRect& rrcDst, const RectF& rrcSrc ) 
{
	rrcDst.left = (INT)rrcSrc.X;
	rrcDst.top = (INT)rrcSrc.Y;
	rrcDst.right = (INT)rrcSrc.X + (INT)rrcSrc.Width;
	rrcDst.bottom = (INT)rrcSrc.Y + (INT)rrcSrc.Height;
}*/

////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL IsRectEmpty( const Rect& rRect )  {
	return 0 == rRect.Width || 0 == rRect.Height;  }

CU_EXT_API BOOL IsRectEmpty( const GRectF& rRect )  {
	return rRect.left == rRect.right || rRect.top == rRect.bottom;  }

CU_EXT_API BOOL IsRectEmpty( const RectF& rRect )  {
	return 0.f == rRect.Width || 0.f == rRect.Height;  }

////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void SetRect( GRectF& rRect, FLOAT l, FLOAT t, FLOAT r, FLOAT b ) 
{
	rRect.left = l;
	rRect.top = t;
	rRect.right = r;
	rRect.bottom = b; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*CU_EXT_API BOOL PtInRect( const GRectF& rRect, const GPoint& rpt ) 
{
	return (rRect.left <= rpt.x && rRect.right >= rpt.x &&
			rRect.top <= rpt.y && rRect.bottom >= rpt.y); 
}*/
	
CU_EXT_API BOOL PtInRect( const GRectF& rRect, const POINT& rpt ) 
{
	return (rRect.left <= rpt.x && rRect.right >= rpt.x &&
			rRect.top <= rpt.y && rRect.bottom >= rpt.y); 
}
	
CU_EXT_API BOOL PtInRect( const GRectF& rRect, const Point& rpt ) 
{
	return (rRect.left <= rpt.X && rRect.right >= rpt.X &&
			rRect.top <= rpt.Y && rRect.bottom >= rpt.Y); 
}
	
CU_EXT_API BOOL PtInRect( const GRectF& rRect, const PointF& rpt ) 
{
	return (rRect.left <= rpt.X && rRect.right >= rpt.X &&
			rRect.top <= rpt.Y && rRect.bottom >= rpt.Y); 
}
	
////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void SetRectEmpty( GRectF& rRect )  {
	memset( &rRect, 0, sizeof(GRectF) );  }

////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL EqualRect( const GRectF& rRect1, const GRectF& rRect2 ) {
	return rRect1.left == rRect2.left   && rRect1.top == rRect2.top && 
		   rRect1.right == rRect2.right && rRect1.bottom == rRect2.bottom; }

CU_EXT_API BOOL EqualRect( const GRectF& rRect1, const RECT& rRect2 ) {
	BOOL bResult = (rRect1.left == rRect2.left 
					&& rRect1.top == rRect2.top
					&& rRect1.right == rRect2.right
					&& rRect1.bottom == rRect2.bottom );
	return bResult; }

CU_EXT_API BOOL EqualRect( const GRectF& rRect1, const Rect& rRect2 ) {
	BOOL bResult = (rRect1.left == rRect2.X 
					&& rRect1.top == rRect2.Y
					&& rRect1.right == rRect2.X + rRect2.Width
					&& rRect1.bottom == rRect2.Y + rRect2.Height );
	return bResult; }

CU_EXT_API BOOL EqualRect( const GRectF& rRect1, const RectF& rRect2 ) {
	BOOL bResult = (rRect1.left == rRect2.X 
					&& rRect1.top == rRect2.Y
					&& rRect1.right == rRect2.X + rRect2.Width
					&& rRect1.bottom == rRect2.Y + rRect2.Height );
	return bResult; }

////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void InflateRect( GRectF& rRect, INT dx, INT dy ) 
{
	rRect.left -= dx; 
	rRect.top -= dy; 
	rRect.right += dy; 
	rRect.bottom += dy;
}

CU_EXT_API void InflateRect( GRectF& rRect, FLOAT l, FLOAT t, FLOAT r, FLOAT b ) 
{
	rRect.left -= l; 
	rRect.top -= t; 
	rRect.right += r; 
	rRect.bottom += b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void OffsetRect( GRectF& rRect, INT dx, INT dy ) 
{
	rRect.left += dx; 
	rRect.right += dx;
	rRect.top += dy; 
	rRect.bottom += dy;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void NormalizeRect( GRectF& rRect )
{
	FLOAT f;
	if( rRect.left > rRect.right )
	{
		f = rRect.left;
		rRect.left = rRect.right;
		rRect.right = f;
	}

	if( rRect.top > rRect.bottom )
	{
		f = rRect.top;
		rRect.top = rRect.bottom;
		rRect.bottom = f;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL IntersectRect( GRectF& rRect, const GRectF& rRect1, const GRectF& rRect2 );

CU_EXT_API BOOL IntersectRect( GRectF& rRect, const RECT& rRect1, const RECT& rRect2 ) 
{
	if( IsRectEmpty( &rRect1 ) || IsRectEmpty( &rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	rRect.right = (FLOAT)min( rRect1.right, rRect2.right );
	rRect.bottom = (FLOAT)min( rRect1.bottom, rRect2.bottom );
	rRect.left = (FLOAT)max( rRect1.left, rRect2.left );
	rRect.top = (FLOAT)max( rRect1.top, rRect2.top );
	return !IsRectEmpty( rRect ); 
}

CU_EXT_API BOOL IntersectRect( GRectF& rRect, const GRectF& rRect1, const RECT& rRect2 ) 
{
	if( IsRectEmpty( rRect1 ) || IsRectEmpty( &rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	rRect.right = min( rRect1.right, (FLOAT)rRect2.right );
	rRect.bottom = min( rRect1.bottom, (FLOAT)rRect2.bottom );
	rRect.left = max( rRect1.left, (FLOAT)rRect2.left );
	rRect.top = max( rRect1.top, (FLOAT)rRect2.top );
	return !IsRectEmpty( rRect ); 
}

CU_EXT_API BOOL IntersectRect( GRectF& rRect, const Rect& rRect1, const Rect& rRect2 ) 
{
	if( IsRectEmpty( rRect1 ) || IsRectEmpty( rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	rRect.right = (FLOAT)min( rRect1.X + rRect1.Width, rRect2.X + rRect2.Width );
	rRect.bottom = (FLOAT)min( rRect1.Y + rRect1.Height, rRect2.Y + rRect2.Height );
	rRect.left = (FLOAT)max( rRect1.X, rRect2.X );
	rRect.top = (FLOAT)max( rRect1.Y, rRect2.Y );
	return !IsRectEmpty( rRect ); 
}

/*CU_EXT_API BOOL IntersectRect( GRectF& rRect, const GRect& rRect1, const Rect& rRect2 ) 
{
	if( IsRectEmpty( rRect1 ) || IsRectEmpty( rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	rRect.right = min( rRect1.right, (FLOAT)(rRect2.X + rRect2.Width) );
	rRect.bottom = min( rRect1.bottom, (FLOAT)(rRect2.Y + rRect2.Height) );
	rRect.left = max( rRect1.left, (FLOAT)rRect2.X );
	rRect.top = max( rRect1.top, (FLOAT)rRect2.Y );
	return !IsRectEmpty( rRect ); 
}*/

/*CU_EXT_API BOOL IntersectRect( GRectF& rRect, const GRect& rRect1, const RectF& rRect2 ) 
{
	if( IsRectEmpty( rRect1 ) || IsRectEmpty( rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	rRect.right = min( rRect1.right, rRect2.X + rRect2.Width );
	rRect.bottom = min( rRect1.bottom, rRect2.Y + rRect2.Height );
	rRect.left = max( rRect1.left, rRect2.X );
	rRect.top = max( rRect1.top, rRect2.Y );
	return !IsRectEmpty( rRect ); 
}*/

CU_EXT_API BOOL IntersectRect( GRectF& rRect, const RectF& rRect1, const RectF& rRect2 ) 
{
	if( IsRectEmpty( rRect1 ) || IsRectEmpty( rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	rRect.right = min( rRect1.X + rRect1.Width, rRect2.X + rRect2.Width );
	rRect.bottom = min( rRect1.Y + rRect1.Height, rRect2.Y + rRect2.Height );
	rRect.left = max( rRect1.X, rRect2.X );
	rRect.top = max( rRect1.Y, rRect2.Y );
	return !IsRectEmpty( rRect ); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL IsEqualRect( const GRectF& rRect1, const GRectF& rRect2 )
{
	return rRect1.left == rRect2.left && rRect1.top == rRect2.top &&
		   rRect1.right == rRect2.right && rRect1.bottom == rRect2.bottom;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL UnionRect( GRectF& rRect, const GRectF& rRect1, const GRectF& rRect2 ) 
{
	ASSERT( rRect1.right  >= rRect1.left );
	ASSERT( rRect1.bottom >= rRect1.top );
	ASSERT( rRect2.right  >= rRect2.left );
	ASSERT( rRect2.bottom >= rRect2.top );

	if( IsRectEmpty( rRect1 ) && IsRectEmpty( rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	if( IsRectEmpty( rRect1 ) )
	{
		if( &rRect != (void*)&rRect2 )
			CopyRect( rRect, rRect2 );

		return TRUE;
	}

	if( IsRectEmpty( rRect2 ) )
	{
		if( &rRect != (void*)&rRect1 )
			CopyRect( rRect, rRect1 );

		return TRUE;
	}
	else
	{
		rRect.right  = max( rRect1.right,  rRect2.right );
		rRect.bottom = max( rRect1.bottom, rRect2.bottom );
		rRect.left   = min( rRect1.left,   rRect2.left );
		rRect.top    = min( rRect1.top,    rRect2.top );
	}

	return !IsRectEmpty( rRect ); 
}

CU_EXT_API BOOL UnionRect( GRectF& rRect, const RECT& rRect1, const RECT& rRect2 ) 
{
	ASSERT( rRect1.right  >= rRect1.left );
	ASSERT( rRect1.bottom >= rRect1.top );
	ASSERT( rRect2.right  >= rRect2.left );
	ASSERT( rRect2.bottom >= rRect2.top );

	if( IsRectEmpty( &rRect1 ) && IsRectEmpty( &rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	if( IsRectEmpty( &rRect1 ) )
	{
		if( &rRect != (void*)&rRect2 )
			CopyRect( rRect, rRect2 );

		return TRUE;
	}

	if( IsRectEmpty( &rRect2 ) )
	{
		if( &rRect != (void*)&rRect1 )
			CopyRect( rRect, rRect1 );

		return TRUE;
	}
	else
	{
		rRect.right  = (FLOAT)max( rRect1.right,  rRect2.right );
		rRect.bottom = (FLOAT)max( rRect1.bottom, rRect2.bottom );
		rRect.left   = (FLOAT)min( rRect1.left,   rRect2.left );
		rRect.top    = (FLOAT)min( rRect1.top,    rRect2.top );
	}

	return !IsRectEmpty( rRect ); 
}

CU_EXT_API BOOL UnionRect( GRectF& rRect, const GRectF& rRect1, const RECT& rRect2 ) 
{
	ASSERT( rRect1.right  >= rRect1.left );
	ASSERT( rRect1.bottom >= rRect1.top );
	ASSERT( rRect2.right  >= rRect2.left );
	ASSERT( rRect2.bottom >= rRect2.top );

	if( IsRectEmpty( rRect1 ) && IsRectEmpty( &rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	if( IsRectEmpty( rRect1 ) )
	{
		if( &rRect != (void*)&rRect2 )
			CopyRect( rRect, rRect2 );

		return TRUE;
	}

	if( IsRectEmpty( &rRect2 ) )
	{
		if( &rRect != (void*)&rRect1 )
			CopyRect( rRect, rRect1 );

		return TRUE;
	}
	else
	{
		rRect.right  = (FLOAT)max( rRect1.right,  rRect2.right );
		rRect.bottom = (FLOAT)max( rRect1.bottom, rRect2.bottom );
		rRect.left   = (FLOAT)min( rRect1.left,   rRect2.left );
		rRect.top    = (FLOAT)min( rRect1.top,    rRect2.top );
	}

	return !IsRectEmpty( rRect ); 
}

CU_EXT_API BOOL UnionRect( GRectF& rRect, const GRectF& rRect1, const Rect& rRect2 ) 
{
	ASSERT( rRect1.right  >= rRect1.left );
	ASSERT( rRect1.bottom >= rRect1.top );
	ASSERT( rRect2.X + rRect2.Width >= rRect2.X );
	ASSERT( rRect2.Y + rRect2.Height >= rRect2.Y );

	if( IsRectEmpty( rRect1 ) && IsRectEmpty( rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	if( IsRectEmpty( rRect1 ) )
	{
		if( &rRect != (void*)&rRect2 )
			CopyRect( rRect, rRect2 );

		return TRUE;
	}

	if( IsRectEmpty( rRect2 ) )
	{
		if( &rRect != (void*)&rRect1 )
			CopyRect( rRect, rRect1 );

		return TRUE;
	}
	else
	{
		rRect.right  = (FLOAT)max( rRect1.right,  rRect2.X + rRect2.Width );
		rRect.bottom = (FLOAT)max( rRect1.bottom, rRect2.Y + rRect2.Height );
		rRect.left   = (FLOAT)min( rRect1.left,   rRect2.X );
		rRect.top    = (FLOAT)min( rRect1.top,    rRect2.Y );
	}

	return !IsRectEmpty( rRect ); 
}

CU_EXT_API BOOL UnionRect( GRectF& rRect, const Rect& rRect1, const Rect& rRect2 ) 
{
	ASSERT( rRect1.X + rRect1.Width  >= rRect1.X );
	ASSERT( rRect1.Y + rRect1.Height >= rRect1.Y );
	ASSERT( rRect2.X + rRect2.Width >= rRect2.X );
	ASSERT( rRect2.Y + rRect2.Height >= rRect2.Y );

	if( IsRectEmpty( rRect1 ) && IsRectEmpty( rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	if( IsRectEmpty( rRect1 ) )
	{
		if( &rRect != (void*)&rRect2 )
			CopyRect( rRect, rRect2 );

		return TRUE;
	}

	if( IsRectEmpty( rRect2 ) )
	{
		if( &rRect != (void*)&rRect1 )
			CopyRect( rRect, rRect1 );

		return TRUE;
	}
	else
	{
		rRect.right  = (FLOAT)max( rRect1.X + rRect1.Width,  rRect2.X + rRect2.Width );
		rRect.bottom = (FLOAT)max( rRect1.Y + rRect1.Height, rRect2.Y + rRect2.Height );
		rRect.left   = (FLOAT)min( rRect1.X, rRect2.X );
		rRect.top    = (FLOAT)min( rRect1.Y, rRect2.Y );
	}

	return !IsRectEmpty( rRect ); 
}

CU_EXT_API BOOL UnionRect( GRectF& rRect, const Rect& rRect1, const RectF& rRect2 ) 
{
	ASSERT( rRect1.X + rRect1.Width  >= rRect1.X );
	ASSERT( rRect1.Y + rRect1.Height >= rRect1.Y );
	ASSERT( rRect2.X + rRect2.Width >= rRect2.X );
	ASSERT( rRect2.Y + rRect2.Height >= rRect2.Y );

	if( IsRectEmpty( rRect1 ) && IsRectEmpty( rRect2 ) )
	{
		if( *((CGRectF*)&rRect) != rRect2 )
			SetRectEmpty( rRect ); 

		return FALSE;
	}

	if( IsRectEmpty( rRect1 ) )
	{
		if( *((CGRectF*)&rRect) != rRect2 )
			CopyRect( rRect, rRect2 );

		return TRUE;
	}

	if( IsRectEmpty( rRect2 ) )
	{
		if( *((CGRectF*)&rRect) != rRect1 )
			CopyRect( rRect, rRect1 );

		return TRUE;
	}
	else
	{
		rRect.right  = max( rRect1.X + rRect1.Width,  rRect2.X + rRect2.Width );
		rRect.bottom = max( rRect1.Y + rRect1.Height, rRect2.Y + rRect2.Height );
		rRect.left   = min( rRect1.X, rRect2.X );
		rRect.top    = min( rRect1.Y, rRect2.Y );
	}

	return !IsRectEmpty( rRect ); 
}

CU_EXT_API BOOL UnionRect( GRectF& rRect, const RectF& rRect1, const RectF& rRect2 ) 
{
	ASSERT( rRect1.X + rRect1.Width  >= rRect1.X );
	ASSERT( rRect1.Y + rRect1.Height >= rRect1.Y );
	ASSERT( rRect2.X + rRect2.Width >= rRect2.X );
	ASSERT( rRect2.Y + rRect2.Height >= rRect2.Y );

	if( IsRectEmpty( rRect1 ) && IsRectEmpty( rRect2 ) )
	{
		SetRectEmpty( rRect ); 
		return FALSE;
	}

	if( IsRectEmpty( rRect1 ) )
	{
		if( &rRect != (void*)&rRect2 )
			CopyRect( rRect, rRect2 );

		return TRUE;
	}

	if( IsRectEmpty( rRect2 ) )
	{
		if( &rRect != (void*)&rRect1 )
			CopyRect( rRect, rRect1 );

		return TRUE;
	}
	else
	{
		rRect.right  = max( rRect1.X + rRect1.Width,  rRect2.X + rRect2.Width );
		rRect.bottom = max( rRect1.Y + rRect1.Height, rRect2.Y + rRect2.Height );
		rRect.left   = min( rRect1.X, rRect2.X );
		rRect.top    = min( rRect1.Y, rRect2.Y );
	}

	return !IsRectEmpty( rRect ); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL SubtractRect( GRectF& rRect, const GRectF& rRect1, const GRectF& rRect2 ) {
	ASSERT( FALSE );
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL SubtractRect( GRectF& rRect, const RECT& rRect1, const RECT& rRect2 ) {
	ASSERT( FALSE );
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL SubtractRect( GRectF& rRect, const GRectF& rRect1, const RECT& rRect2 ) {
	ASSERT( FALSE );
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL SubtractRect( GRectF& rRect, const GRectF& rRect1, const Rect& rRect2 ) {
	ASSERT( FALSE );
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL SubtractRect( GRectF& rRect, const Rect& rRect1, const Rect& rRect2 ) {
	ASSERT( FALSE );
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL SubtractRect( GRectF& rRect, const Rect& rRect1, const RectF& rRect2 ) {
	ASSERT( FALSE );
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL SubtractRect( GRectF& rRect, const RectF& rRect1, const RectF& rRect2 ) {
	ASSERT( FALSE );
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

