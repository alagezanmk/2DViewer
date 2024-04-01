#include "stdafx.h"
#include <gl\gCoord.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
extern CU_EXT_DATA const POINT nullPOINT = {0,0};
extern CU_EXT_DATA const SIZE nullSIZE = {0,0};
extern CU_EXT_DATA const RECT nullRECT = {0,0,0,0};

/*extern CU_EXT_DATA const Point nullPoint(0,0);
extern CU_EXT_DATA const Size nullSize(0,0);
extern CU_EXT_DATA const Rect nullRect(0,0,0,0);*/

//extern CU_EXT_DATA const GPoint nullGPoint(0,0);
//extern CU_EXT_DATA const GSize nullGSize(0,0);
//extern CU_EXT_DATA const GRect nullGRect(0,0,0,0);

extern CU_EXT_DATA const POINT nullPoint = {0, 0};
extern CU_EXT_DATA const SIZE nullSize = {0, 0};
extern CU_EXT_DATA const RECT nullRect = {0, 0, 0, 0};

#if 0
///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void CopyRect( GRect& rrcDst, const GRect& rrcSrc ) {
	::CopyRect( (RECT*)&rrcDst, (const RECT*)&rrcSrc ); }

CU_EXT_API void CopyRect( GRect& rrcDst, const RECT& rrcSrc ) {
	::CopyRect( (RECT*)&rrcDst, &rrcSrc ); }

CU_EXT_API void CopyRect( GRect& rrcDst, const Rect& rrcSrc ) 
{
	rrcDst.left = rrcSrc.X;
	rrcDst.top = rrcSrc.Y;
	rrcDst.right = rrcSrc.X + rrcSrc.Width;
	rrcDst.bottom = rrcSrc.Y + rrcSrc.Height;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL IsRectEmpty( const GRect& rRect ) {
	return ::IsRectEmpty( (const RECT*)&rRect ); }

CU_EXT_API BOOL IsRectEmpty( const Rect& rRect ) {
	CGRect rect( rRect );
	return ::IsRectEmpty( (const RECT*)&rect ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void SetRect( GRect& rRect, INT l, INT t, INT r, INT b ) {
	SetRect( (RECT*)&rRect, l, t, r, b ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL PtInRect( const GRect& rRect, const GPoint& rpt ) {
	CPoint pt( rpt.x, rpt.y );
	return PtInRect( (const RECT*)&rRect, pt ); }

CU_EXT_API BOOL PtInRect( const GRect& rRect, const POINT& rpt ) {
	return PtInRect( (const RECT*)&rRect, rpt ); }

CU_EXT_API BOOL PtInRect( const GRect& rRect, const Point& rpt ) {
	CPoint pt( rpt.X, rpt.Y );
	return PtInRect( (const RECT*)&rRect, pt ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void SetRectEmpty( GRect& rRect ) {
	SetRectEmpty( (RECT*)&rRect ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL EqualRect( const GRect& rRect1, const GRect& rRect2 ) {
	return EqualRect( (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL EqualRect( const GRect& rRect1, const RECT& rRect2 ) {
	return EqualRect( (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL EqualRect( const GRect& rRect1, const Rect& rRect2 ) {
	BOOL bResult = (rRect1.left == rRect2.X
					&& rRect1.top == rRect2.Y
					&& rRect1.right == rRect2.X + rRect2.Width
					&& rRect1.bottom == rRect2.Y + rRect2.Height );
	return bResult; }

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void InflateRect( GRect& rRect, INT dx, INT dy ) {
	InflateRect( rRect, dx, dy ); }

CU_EXT_API void InflateRect( GRect& rRect, INT l, INT t, INT r, INT b ) 
{
	rRect.left -= l; 
	rRect.top -= t; 
	rRect.right += r; 
	rRect.bottom += b; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API void OffsetRect( GRect& rRect, INT dx, INT dy ) {
	OffsetRect( rRect, dx, dy ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL IntersectRect( GRect& rRect, const GRect& rRect1, const GRect& rRect2 ) {
	return IntersectRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL IntersectRect( GRect& rRect, const GRect& rRect1, const RECT& rRect2 ) {
	return IntersectRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL IntersectRect( GRect& rRect, const GRect& rRect1, const Rect& rRect2 ) {
	CGRect rect2( rRect2 );
	return IntersectRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rect2 ); }

CU_EXT_API BOOL IntersectRect( GRect& rRect, const RECT& rRect1, const RECT& rRect2 ) {
	return IntersectRect( (RECT*)&rRect, &rRect1, &rRect2 ); }

CU_EXT_API BOOL IntersectRect( GRect& rRect, const Rect& rRect1, const Rect& rRect2 ) {
	CGRect rect1( rRect1 );
	CGRect rect2( rRect2 );
	return IntersectRect( (RECT*)&rRect, (const RECT*)&rect1, (const RECT*)&rect2 ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL UnionRect( GRect& rRect, const GRect& rRect1, const GRect& rRect2 ) {
	return UnionRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL UnionRect( GRect& rRect, const GRect& rRect1, const RECT& rRect2 ) {
	return UnionRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL UnionRect( GRect& rRect, const GRect& rRect1, const Rect& rRect2 ) {
	CGRect rect2( rRect2 );
	return UnionRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rect2 ); }

CU_EXT_API BOOL UnionRect( GRect& rRect, const RECT& rRect1, const RECT& rRect2 ) {
	return UnionRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL UnionRect( GRect& rRect, const Rect& rRect1, const Rect& rRect2 ) {
	CGRect rect1( rRect1 );
	CGRect rect2( rRect2 );
	return UnionRect( (RECT*)&rRect, (const RECT*)&rect1, (const RECT*)&rect2 ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL SubtractRect( GRect& rRect, const GRect& rRect1, const GRect& rRect2 ) {
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL SubtractRect( GRect& rRect, const GRect& rRect1, const RECT& rRect2 ) {
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL SubtractRect( GRect& rRect, const GRect& rRect1, const Rect& rRect2 ) {
	CGRect rect2( rRect2 );
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rect2 ); }

CU_EXT_API BOOL SubtractRect( GRect& rRect, const RECT& rRect1, const RECT& rRect2 ) {
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rRect1, (const RECT*)&rRect2 ); }

CU_EXT_API BOOL SubtractRect( GRect& rRect, const Rect& rRect1, const Rect& rRect2 ) {
	CGRect rect1( rRect1 );
	CGRect rect2( rRect2 );
	return SubtractRect( (RECT*)&rRect, (const RECT*)&rect1, (const RECT*)&rect2 ); }

#endif //0