#ifndef ___G_POINT_F__PH___
#define ___G_POINT_F__PH___

struct GPointF
{
	FLOAT x;
	FLOAT y;
};

struct GSizeF;
struct GRectF;

class CGSizeF;
class CGRectF;

class CGPointF : public GPointF
{
public:
	CGPointF()
	{}	/// Uninitialized

	CGPointF( INT x, INT y );
	CGPointF( FLOAT x, FLOAT y );
	CGPointF( DWORD dwPoint );

	CGPointF( const POINT& rPoint );
	CGPointF( const GPointF& rPoint );

	CGPointF( const SIZE& rSize );
	CGPointF( const GSizeF& rSize );
	
	void Offset( INT dx, INT dy );
	void Offset( FLOAT dx, FLOAT dy );

	void Offset( const POINT& rPoint );
	void Offset( const GPointF& rPoint );

	void Offset( const SIZE& rSize );
	void Offset( const GSizeF& rSize );

	BOOL operator==( const POINT& rPoint ) const;
	BOOL operator==( const GPointF& rPoint ) const;

	BOOL operator!=( const POINT& rPoint ) const;
	BOOL operator!=( const GPointF& rPoint ) const;

	void operator+=( const SIZE& rSize );
	void operator+=( const GSizeF& rSize );

	void operator-=( const SIZE& rSize );
	void operator-=( const GSizeF& rSize );

	void operator+=( const POINT& rPoint );
	void operator+=( const GPointF& rPoint );

	void operator-=( const POINT& rPoint );
	void operator-=( const GPointF& rPoint );

	CGPointF operator+( const SIZE& rSize ) const;
	CGPointF operator+( const GSizeF& rSize ) const;

	CGPointF operator-( const SIZE& rSize ) const;
	CGPointF operator-( const GSizeF& rSize ) const;

	CGPointF operator-() const;

	CGSizeF operator+( const POINT& rPoint ) const;
	CGSizeF operator+( const GPointF& rPoint ) const;

	CGSizeF operator-( const POINT& rPoint ) const;
	CGSizeF operator-( const GPointF& rPoint ) const;

	CGRectF operator+( const RECT& rRect ) const;
	CGRectF operator+( const GRectF& rRect ) const;

	CGRectF operator-( const RECT& rRect ) const;
	CGRectF operator-( const GRectF& rRect ) const;

#ifdef _GDIPLUS_H
	CGPointF( const PointF& rPoint );
	CGPointF( const Point& rPoint );

	CGPointF( const SizeF& rSize );
	CGPointF( const Size& rSize );
	
	void Offset( const PointF& rPoint );
	void Offset( const Point& rPoint );

	void Offset( const SizeF& rSize );
	void Offset( const Size& rSize );

	BOOL operator==( const PointF& rPoint ) const;
	BOOL operator==( const Point& rPoint ) const;

	BOOL operator!=( const PointF& rPoint ) const;
	BOOL operator!=( const Point& rPoint ) const;

	void operator+=( const SizeF& rSize );
	void operator+=( const Size& rSize );

	void operator-=( const SizeF& rSize );
	void operator-=( const Size& rSize );

	void operator+=( const PointF& rPoint );
	void operator+=( const Point& rPoint );

	void operator-=( const PointF& rPoint );
	void operator-=( const Point& rPoint );

	CGPointF operator+( const SizeF& rSize ) const;
	CGPointF operator+( const Size& rSize ) const;

	CGPointF operator-( const SizeF& rSize ) const;
	CGPointF operator-( const Size& rSize ) const;

	CGSizeF operator+( const PointF& rPoint ) const;
	CGSizeF operator+( const Point& rPoint ) const;

	CGSizeF operator-( const PointF& rPoint ) const;
	CGSizeF operator-( const Point& rPoint ) const;

	CGRectF operator+( const RectF& rRect ) const;
	CGRectF operator+( const Rect& rRect ) const;

	CGRectF operator-( const RectF& rRect ) const;
	CGRectF operator-( const Rect& rRect ) const;
#endif //_GDIPLUS_H
};

extern CU_EXT_DATA const GPointF nullGPointF;

#endif //!___G_POINT_F__PH___