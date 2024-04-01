#ifndef ___G_RECT__PH___
#define ___G_RECT__PH___

#if 0
class GSize;
class GRect;
class GPoint;

class GRect
{
public:
	// uninitialized rectangle
	GRect();

	// from left, top, right, and bottom
	GRect( INT l, INT t, INT r, INT b );

	// copy constructor
	GRect( const GRect& rRect );

	// from a point and size
	GRect( const GPoint& rTopLeft, const GSize& rSize );

	// from two points
	GRect( const GPoint& rTopLeft, const GPoint& rBottomRight );

	// retrieves the width
	INT Width() const;

	// returns the height
	INT Height() const;

	// returns the size
	GSize GetSize() const;

	// reference to the top-left point
	GPoint& TopLeft();

	// reference to the bottom-right point
	GPoint& BottomRight();

	// const reference to the top-left point
	const GPoint& TopLeft() const;

	// const reference to the bottom-right point
	const GPoint& BottomRight() const;

	// the geometric center point of the rectangle
	GPoint CenterPoint() const;

	// swap the left and right
	void SwapLeftRight();
	static void SwapLeftRight( GRect& rRect );

	// convert between GRect and GRect*/const GRect* (no need for &)
	operator GRect*();
	operator const GRect*() const;

	// returns TRUE if rectangle has no area
	BOOL IsRectEmpty() const;

	// returns TRUE if rectangle is at (0,0) and has no area
	BOOL IsRectNull() const;

	// returns TRUE if point is within rectangle
	BOOL PtInRect( const GPoint& rpt ) const;

	// set rectangle from left, top, right, and bottom
	void SetRect( INT l, INT t, INT r, INT b );
	void SetRect( const GPoint& rTopLeft, const GPoint& rBottomRight );

	// empty the rectangle
	void SetRectEmpty();

	// copy from another rectangle
	void CopyRect( const GRect& rRect );

	// TRUE if exactly the same as another rectangle
	BOOL EqualRect( const GRect& rRect ) const;

	// inflate rectangle's width and height without
	// moving its top or left
	void InflateRect( INT dx, INT dy );
	void InflateRect( INT l, INT t, INT r, INT b );
	void InflateRect( const GPoint& rptf );
	void InflateRect( const GSize& rSize );
	void InflateRect( const GRect& rRect );

	// deflate the rectangle's width and height without
	// moving its top or left
	void DeflateRect( INT dx, INT dy );
	void DeflateRect( INT l, INT t, INT r, INT b );
	void DeflateRect( const GPoint& rpt );
	void DeflateRect( const GSize& rSize );
	void DeflateRect( const GRect& rRect );

	// translate the rectangle by moving its top and left
	void OffsetRect( INT dx, INT dy );
	void OffsetRect( const GSize& rSize );
	void OffsetRect( const GPoint& rpt );
	void NormalizeRect();

	// set this rectangle to intersection of two others
	BOOL IntersectRect( const GRect& rgRect1, const GRect& rgRect2 );

	// set this rectangle to bounding union of two others
	BOOL UnionRect( const GRect& rgRect1, const GRect& rgRect2 );

	// set this rectangle to minimum of two others
	BOOL SubtractRect( const GRect& rgRect1, const GRect& rgRect2 );

	void operator= ( const GRect& rRect );
	BOOL operator==( const GRect& rRect ) const;
	BOOL operator!=( const GRect& rRect ) const;

	void operator+=( const GPoint& rpt );
	void operator+=( const GSize& rSize );
	void operator+=( const GRect& rRect );

	void operator-=( const GPoint& rpt );
	void operator-=( const GSize& rSize );
	void operator-=( const GRect& rRect );

	void operator&=( const GRect& rRect );
	void operator|=( const GRect& rRect );

	GRect operator+( const GPoint& rpt) const;
	GRect operator+( const GRect& rRect ) const;
	GRect operator+( const GSize& rSize ) const;

	GRect operator-( const GPoint& rpt ) const;
	GRect operator-( const GSize& rSize ) const;
	GRect operator-( const GRect& rRect ) const;

	GRect operator&( const GRect& rRect ) const;
	GRect operator|( const GRect& rRect ) const;
	GRect MulDiv( INT nMultiplier, INT nDivisor ) const;

public:
	INT		left;
	INT		top;
	INT		right;
	INT		bottom;
};

/// Can accept POINT, Point, SIZE, Size, RECT, Rect
/// Can return POINT, Point, SIZE, Size, RECT, Rect
class CGRect : public GRect
{
public:
	CGRect();

	CGRect( const RECT& rRect );
	CGRect( const Rect& rRect );

	// from a point and size
	CGRect( const POINT& rTopLeft, const SIZE& rSize );
	CGRect( const POINT& rTopLeft, const Size& rSize );

	CGRect( const Point& rTopLeft, const SIZE& rSize );
	CGRect( const Point& rTopLeft, const Size& rSize );

	// from two points
	CGRect( const POINT& rTopLeft, const POINT& rBottomRight );
	CGRect( const Point& rTopLeft, const Point& rBottomRight );

	operator RECT*();
	operator const RECT*() const;

	// returns TRUE if point is within rectangle
	BOOL PtInRect( const POINT& rpt ) const;
	BOOL PtInRect( const Point& rpt ) const;

	// set rectangle from left, top, right, and bottom
	void SetRect( const POINT& rTopLeft, const POINT& rBottomRight );
	void SetRect( const Point& rTopLeft, const Point& rBottomRight );

	// copy from another rectangle
	void CopyRect( const RECT& rRect );
	void CopyRect( const Rect& rRect );

	// TRUE if exactly the same as another rectangle
	BOOL EqualRect( const RECT& rRect ) const;
	BOOL EqualRect( const Rect& rRect ) const;

	// inflate rectangle's width and height without
	// moving its top or left
	void InflateRect( const POINT& rptf );
	void InflateRect( const Point& rptf );

	void InflateRect( const SIZE& rSize );
	void InflateRect( const Size& rSize );

	void InflateRect( const RECT& rRect );

	// deflate the rectangle's width and height without
	// moving its top or left
	void DeflateRect( const POINT& rptf );
	void DeflateRect( const Point& rptf );

	void DeflateRect( const SIZE& rSize );
	void DeflateRect( const Size& rSize );

	void DeflateRect( const RECT& rRect );

	// translate the rectangle by moving its top and left
	void OffsetRect( const POINT& rpt );
	void OffsetRect( const Point& rpt );

	void OffsetRect( const SIZE& rSize );
	void OffsetRect( const Size& rSize );

	// set this rectangle to intersection of two others
	BOOL IntersectRect( const RECT& rgRect1, const RECT& rgRect2 );
	BOOL IntersectRect( const Rect& rgRect1, const Rect& rgRect2 );

	// set this rectangle to bounding union of two others
	BOOL UnionRect( const RECT& rgRect1, const RECT& rgRect2 );
	BOOL UnionRect( const Rect& rgRect1, const Rect& rgRect2 );

	// set this rectangle to minimum of two others
	BOOL SubtractRect( const RECT& rgRect1, const RECT& rgRect2 );
	BOOL SubtractRect( const Rect& rgRect1, const Rect& rgRect2 );

	void operator=( const RECT& rRect );
	void operator=( const Rect& rRect );

	BOOL operator==( const RECT& rRect ) const;
	BOOL operator==( const Rect& rRect ) const;
	
	BOOL operator!=( const RECT& rRect ) const;
	BOOL operator!=( const Rect& rRect ) const;

	using GRect::operator+=;
	using GRect::operator-=;

	void operator+=( const POINT& rpt );
	void operator+=( const Point& rpt );

	void operator+=( const SIZE& rSize );
	void operator+=( const Size& rSize );

	void operator+=( const RECT& rRect );

	void operator-=( const POINT& rpt );
	void operator-=( const Point& rpt );

	void operator-=( const SIZE& rSize );
	void operator-=( const Size& rSize );

	void operator-=( const RECT& rRect );

	void operator&=( const RECT& rRect );
	void operator&=( const Rect& rRect );

	void operator|=( const RECT& rRect );
	void operator|=( const Rect& rRect );

	CGRect operator+( const POINT& rpt) const;
	CGRect operator+( const Point& rpt) const;

	CGRect operator+( const SIZE& rSize ) const;
	CGRect operator+( const Size& rSize ) const;

	CGRect operator+( const RECT& rRect ) const;

	CGRect operator-( const POINT& rpt ) const;
	CGRect operator-( const Point& rpt ) const;

	CGRect operator-( const SIZE& rSize ) const;
	CGRect operator-( const Size& rSize ) const;

	CGRect operator-( const RECT& rRect ) const;

	CGRect operator&( const RECT& rRect ) const;
	CGRect operator&( const Rect& rRect ) const;

	CGRect operator|( const RECT& rRect ) const;
	CGRect operator|( const Rect& rRect ) const;
};
#endif //0

#endif //!___G_RECT__PH___