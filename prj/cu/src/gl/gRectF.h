#ifndef ___G_RECT_F__PH___
#define ___G_RECT_F__PH___

struct GPointF;
struct GSizeF;
#ifdef _GDIPLUS_H

/// To avoid conflict between CGRectF::Size function and Gdi+ Size class 
/// class Size is type defined as GPSize
typedef Size GPSize;
#endif //_GDIPLUS_H

struct GRectF
{
	FLOAT left;
	FLOAT top;
	FLOAT right;
	FLOAT bottom;
};

class CGSizeF;
class CGRectF;
class CGPointF;

class CGRectF : public GRectF
{
public:
	CGRectF() 
	{}	/// Uninitialized

	CGRectF( INT _left, INT _top, INT _right, INT _bottom );
	CGRectF( FLOAT _left, FLOAT _top, FLOAT _right, FLOAT _bottom );
	CGRectF( const RECT& rRect );
	CGRectF( const GRectF& rRect );
	CGRectF( const POINT& rPoint, const SIZE& rSize );
	CGRectF( const POINT& rTopLeft, const POINT& rBottomRight );
	CGRectF( const GPointF& rPoint, const GSizeF& rSize );
	CGRectF( const GPointF& rTopLeft, const GPointF& rBottomRight );

	FLOAT Width() const;
	FLOAT Height() const;

	GSizeF Size() const;
	void Size( GSizeF& rSize ) const;

	void Size( FLOAT& rfWidth, FLOAT& rfHeight ) const;

	GPointF TopLeft() const;
	void TopLeft( GPointF& rPoint ) const;
	void TopLeft( FLOAT& rx, FLOAT& ry ) const;

	GPointF BottomRight() const;
	void BottomRight( GPointF& rPoint ) const;
	void BottomRight( FLOAT& rx, FLOAT& ry ) const;

	GPointF CenterPoint() const;
	void CenterPoint( GPointF& rPoint ) const;
	void CenterPoint( FLOAT& rx, FLOAT& ry ) const;
	
	void SwapLeftRight();
	void SwapTopBottom();

	operator GRectF*();
	operator const GRectF*() const;

	void SetRectEmpty();
	BOOL IsRectEmpty() const;
	BOOL IsRectNull() const;

	BOOL PtInRect( INT x, INT y ) const;
	BOOL PtInRect( FLOAT x, FLOAT y ) const;

	BOOL PtInRect( const POINT& rPoint ) const;

	void SetRect( INT _left, INT _top, INT _right, INT _bottom );
	void SetRect( FLOAT _left, FLOAT _top, FLOAT _right, FLOAT _bottom );

	void SetRect( const RECT& rRect );
	void SetRect( const GRectF& rRect );

	void SetRect( const POINT& rPoint, const SIZE& rSize );
	void SetRect( const POINT& rTopLeft, const POINT& rBottomRight );

	void SetRect( const GPointF& rPoint, const GSizeF& rSize );
	void SetRect( const GPointF& rTopLeft, const GPointF& rBottomRight );

	void CopyRect( FLOAT& rfLeft, FLOAT& rfTop, FLOAT& rfRight, FLOAT& rfBottom ) const;
	void CopyRect( GRectF& rRect ) const;
	void CopyRect( GPointF& rPoint, GSizeF& rSize ) const;
	void CopyRect( GPointF& rTopLeft, GPointF& rBottomRight ) const;

	BOOL EqualRect( const GRectF& rRect ) const;

	void InflateRect( INT x, INT y );
	void InflateRect( FLOAT x, FLOAT y );
	void InflateRect( const SIZE& rSize );
	void InflateRect( const GSizeF& rSize );
	void InflateRect( const RECT& rRect );
	void InflateRect( const GRectF& rRect );
	void InflateRect( INT l, INT t, INT r, INT b );
	void InflateRect( FLOAT l, FLOAT t, FLOAT  r, FLOAT  b  );

	void DeflateRect( INT x, INT y );
	void DeflateRect( FLOAT x, FLOAT y );
	void DeflateRect( const SIZE& rSize );
	void DeflateRect( const GSizeF& rSize );
	void DeflateRect( const RECT& rRect );
	void DeflateRect( const GRectF& rRect );
	void DeflateRect( INT l, INT t, INT r, INT b );
	void DeflateRect( FLOAT l, FLOAT t, FLOAT  r, FLOAT  b  );

	void OffsetRect( INT x, INT y );
	void OffsetRect( FLOAT x, FLOAT y );
	void OffsetRect( const POINT& rPoint );
	void OffsetRect( const GPointF& rPoint );
	void OffsetRect( const SIZE& rSize );
	void OffsetRect( const GSizeF& rSize );
	void OffsetRect( const RECT& rRect );
	void OffsetRect( const GRectF& rRect );
	void OffsetRect( INT l, INT t, INT r, INT b );
	void OffsetRect( FLOAT l, FLOAT t, FLOAT  r, FLOAT  b  );
	void NormalizeRect();

	BOOL IntersectRect( const GRectF& rgrctf1, const GRectF& rgrctf2 );
	BOOL IntersectRect( const RECT& rRect1, const RECT& rrct2 );

	BOOL UnionRect( const GRectF& rgrctf1, const GRectF& rgrctf2 );
	BOOL UnionRect( const RECT& rRect1, const RECT& rrct2 );

	BOOL SubtractRect( const GRectF& rgrctf1, const GRectF& rgrctf2 );
	BOOL SubtractRect( const RECT& rRect1, const RECT& rrct2 );

	void operator=( const RECT& rRect );
	void operator=( const GRectF& rRect );

	BOOL operator==( const RECT& rRect ) const;
	BOOL operator==( const GRectF& rRect ) const;

	BOOL operator!=( const RECT& rRect ) const;
	BOOL operator!=( const GRectF& rRect ) const;

	void operator+=( const RECT& rRect );
	void operator+=( const GRectF& rRect );

	void operator+=( const POINT& rPoint );
	void operator+=( const GPointF& rPoint );

	void operator+=( const SIZE& rSize );
	void operator+=( const GSizeF& rSize );

	void operator-=( const RECT& rRect );
	void operator-=( const GRectF& rRect );

	void operator-=( const POINT& rPoint );
	void operator-=( const GPointF& rPoint );

	void operator-=( const SIZE& rSize );
	void operator-=( const GSizeF& rSize );

	void operator&=( const RECT& rRect );
	void operator&=( const GRectF& rRect );

	void operator|=( const RECT& rRect );
	void operator|=( const GRectF& rRect );

	CGRectF operator+( const POINT& rPoint ) const;
	CGRectF operator+( const GPointF& rPoint ) const;

	CGRectF operator-( const POINT& rPoint ) const;
	CGRectF operator-( const GPointF& rPoint ) const;

	CGRectF operator+( const RECT& rRect ) const;
	CGRectF operator+( const GRectF& rRect ) const;

	CGRectF operator-( const RECT& rRect ) const;
	CGRectF operator-( const GRectF& rRect ) const;

	CGRectF operator+( const SIZE& rSize ) const;
	CGRectF operator+( const GSizeF& rgSizef ) const;

	CGRectF operator-( const SIZE& rSize ) const;
	CGRectF operator-( const GSizeF& rgSizef ) const;

	CGRectF operator&( const RECT& rRect ) const;
	CGRectF operator&( const GRectF& rRect ) const;

	CGRectF operator|( const RECT& rRect ) const;
	CGRectF operator|( const GRectF& rRect ) const;

#ifdef _GDIPLUS_H
	CGRectF( const RectF& rRect );
	CGRectF( const Rect& rRect );
	CGRectF( const PointF& rPoint, const SizeF& rsizef );
	CGRectF( const Point& rPoint, const GPSize& rsizef );
	CGRectF( const PointF& rTopLeft, const PointF& rBottomRight );
	CGRectF( const Point& rTopLeft, const Point& rBottomRight );

	void Size( SizeF& rSize ) const;
	void TopLeft( PointF& rPoint ) const;
	void BottomRight( PointF& rPoint ) const;
	void CenterPoint( PointF& rPoint ) const;

	BOOL PtInRect( const PointF& rPoint ) const;
	BOOL PtInRect( const Point& rPoint ) const;

	void SetRect( const RectF& rRect );
	void SetRect( const Rect& rRect );
	void SetRect( const PointF& rPoint, const SizeF& rsizef );
	///void SetRect( const Point& rPoint, const GPSize& rsizef );
	void SetRect( const PointF& rTopLeft, const PointF& rBottomRight );
	void SetRect( const Point& rTopLeft, const Point& rBottomRight );

	void CopyRect( RectF& rRect ) const;
	void CopyRect( PointF& rPoint, SizeF& rsizef ) const;
	void CopyRect( PointF& rTopLeft, PointF& rBottomRight ) const;

	BOOL EqualRect( const RectF& rRect ) const;

	void InflateRect( const PointF& rPoint );
	void InflateRect( const Point& rPoint );
	void InflateRect( const SizeF& rSize );
	void InflateRect( const GPSize& rSize );
	void InflateRect( const RectF& rRect );
	void InflateRect( const Rect& rRect );

	void DeflateRect( const PointF& rPoint );
	void DeflateRect( const Point& rPoint );
	void DeflateRect( const SizeF& rSize );
	void DeflateRect( const GPSize& rSize );
	void DeflateRect( const RectF& rRect );
	void DeflateRect( const Rect& rRect );

	void OffsetRect( const PointF& rPoint );
	void OffsetRect( const Point& rPoint );
	void OffsetRect( const SizeF& rSize );
	void OffsetRect( const GPSize& rSize );
	void OffsetRect( const RectF& rRect );
	void OffsetRect( const Rect& rRect );

	BOOL IntersectRect( const RectF& rRect1, const RectF& rRect2 );
	BOOL IntersectRect( const Rect& rRect1, const Rect& rRect2 );

	BOOL UnionRect( const RectF& rRect1, const RectF& rRect2 );
	BOOL UnionRect( const Rect& rRect1, const Rect& rRect2 );

	BOOL SubtractRect( const RectF& rRect1, const RectF& rRect2 );
	BOOL SubtractRect( const Rect& rRect1, const Rect& rRect2 );

	void operator=( const RectF& rRect );
	void operator=( const Rect& rRect );

	BOOL operator==( const RectF& rRect ) const;
	BOOL operator==( const Rect& rRect ) const;

	BOOL operator!=( const RectF& rRect ) const;
	BOOL operator!=( const Rect& rRect ) const;

	void operator+=( const RectF& rRect );
	void operator+=( const Rect& rRect );

	void operator+=( const PointF& rPoint );
	void operator+=( const Point& rPoint );

	void operator+=( const SizeF& rSize );
	void operator+=( const GPSize& rSize );

	void operator-=( const RectF& rRect );
	void operator-=( const Rect& rRect );

	void operator-=( const PointF& rPoint );
	void operator-=( const Point& rPoint );

	void operator-=( const SizeF& rSize );
	void operator-=( const GPSize& rSize );

	void operator&=( const RectF& rRect );
	void operator&=( const Rect& rRect );

	void operator|=( const RectF& rRect );
	void operator|=( const Rect& rRect );

	CGRectF operator+( const PointF& rPoint ) const;
	CGRectF operator+( const Point& rPoint ) const;

	CGRectF operator-( const PointF& rPoint ) const;
	CGRectF operator-( const Point& rPoint ) const;

	CGRectF operator+( const RectF& rRect ) const;
	CGRectF operator+( const Rect& rRect ) const;

	CGRectF operator-( const RectF& rRect ) const;
	CGRectF operator-( const Rect& rRect ) const;

	CGRectF operator+( const SizeF& rSize ) const;
	CGRectF operator+( const GPSize& rSize ) const;

	CGRectF operator-( const SizeF& rSize ) const;
	CGRectF operator-( const GPSize& rSize ) const;

	CGRectF operator&( const RectF& rRect ) const;
	CGRectF operator&( const Rect& rRect ) const;

	CGRectF operator|( const RectF& rRect ) const;
	CGRectF operator|( const Rect& rRect ) const;
#endif //_GDIPLUS_H
};

extern CU_EXT_DATA const GRectF nullGRectF;

#endif //!___G_RECT_F__PH___