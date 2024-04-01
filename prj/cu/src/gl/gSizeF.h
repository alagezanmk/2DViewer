#ifndef ___G_SIZE_F__PH___
#define ___G_SIZE_F__PH___

struct GSizeF
{
	FLOAT cx;
	FLOAT cy;
};

struct GRectF;
struct GPointF;

class CGSizeF : public GSizeF
{
public:
	CGSizeF()
	{}	/// Uninitialized

	CGSizeF( INT cx, INT cy );
	CGSizeF( FLOAT cx, FLOAT cy );
	CGSizeF( DWORD dwSize );

	CGSizeF( const SIZE& rSize );
	CGSizeF( const GSizeF& rSize );

	CGSizeF( const POINT& rPoint );
	CGSizeF( const GPointF& rPoint );

	BOOL operator==( const SIZE& rSize ) const;
	BOOL operator==( const GSizeF& rSize ) const;

	BOOL operator!=( const SIZE& rSize ) const;
	BOOL operator!=( const GSizeF& rSize ) const;

	void operator+=( const SIZE& rSize );
	void operator+=( const GSizeF& rSize );

	void operator-=( const SIZE& rSize );
	void operator-=( const GSizeF& rSize );

	CGSizeF operator+( const SIZE& rSize ) const;
	CGSizeF operator+( const GSizeF& rSize ) const;

	CGSizeF operator-( const SIZE& rSize ) const;
	CGSizeF operator-( const GSizeF& rSize ) const;

	CGSizeF operator-() const;

	CGPointF operator+( const POINT& rPoint ) const;
	CGPointF operator+( const GPointF& rPoint ) const;

	CGPointF operator-( const POINT& rPoint ) const;
	CGPointF operator-( const GPointF& rPoint ) const;

	CGRectF operator+( const RECT& rRect ) const;
	CGRectF operator+( const GRectF& rRect ) const;

	CGRectF operator-( const RECT& rRect ) const;
	CGRectF operator-( const GRectF& rRect ) const;

#ifdef _GDIPLUS_H
	CGSizeF( const SizeF& rSize );
	CGSizeF( const Size& rSize );

	CGSizeF( const PointF& rPoint );
	CGSizeF( const Point& rPoint );

	BOOL operator==( const SizeF& rSize ) const;
	BOOL operator==( const Size& rSize ) const;

	BOOL operator!=( const SizeF& rSize ) const;
	BOOL operator!=( const Size& rSize ) const;

	void operator+=( const SizeF& rSize );
	void operator+=( const Size& rSize );

	void operator-=( const SizeF& rSize );
	void operator-=( const Size& rSize );

	CGSizeF operator+( const SizeF& rSize ) const;
	CGSizeF operator+( const Size& rSize ) const;

	CGSizeF operator-( const SizeF& rSize ) const;
	CGSizeF operator-( const Size& rSize ) const;

	CGPointF operator+( const PointF& rPoint ) const;
	CGPointF operator+( const Point& rPoint ) const;

	CGPointF operator-( const PointF& rPoint ) const;
	CGPointF operator-( const Point& rPoint ) const;

	CGRectF operator+( const RectF& rRect ) const;
	CGRectF operator+( const Rect& rRect ) const;

	CGRectF operator-( const RectF& rRect ) const;
	CGRectF operator-( const Rect& rRect ) const;
#endif //_GDIPLUS_H
};

extern CU_EXT_DATA const GSizeF nullGSizeF;

#endif //!___G_SIZE_F__PH___