#ifndef ___G_POINT__PH___
#define ___G_POINT__PH___

/*class GSize;
class GRect;
class GPoint;

class CGRect;

class GPoint
{
public:
	// create an uninitialized gpt
	GPoint();

	// create from two integers
	GPoint( INT x, INT y );

	// create from another gpt
	GPoint( const GPoint& rpt );

	// create from a size
	GPoint( const GSize& rSize );

	// create from a dword: x = LOWORD(dw) y = HIWORD(dw)
	GPoint( DWORD dwPoint );

	// translate the gpt
	void Offset( INT dx, INT dy );
	void Offset( const GPoint& rpt );
	void Offset( const GSize& rSize);

	void operator=( const GPoint& rpt );

	BOOL operator==( const GPoint& rpt ) const;
	BOOL operator!=( const GPoint& rpt ) const;

	GPoint operator-() const;

	void operator+=( const GSize& rSize );
	void operator-=( const GSize& rSize );

	void operator+=( const GPoint& rpt );
	void operator-=( const GPoint& rpt );

	GPoint operator+( const GSize& rSize ) const;
	GPoint operator-( const GSize& rSize ) const;

	GPoint operator+( const GPoint& rpt ) const;
	GPoint operator-( const GPoint& rpt ) const;

	// Operators returning GRect values
	GRect operator+( const GRect& rRect ) const;
	GRect operator-( const GRect& rRect ) const;

public:
	INT		x;
	INT		y;
};

/// Can accept SIZE, Size, POINT, Point
/// Can return SIZE, Size, POINT, Point
class CGPoint : public GPoint
{
public:
	CGPoint();

	CGPoint( INT x, INT y );

	// create from another POINT
	CGPoint( const POINT& rpt );
	CGPoint( const Point& rpt );

	// create from a size
	CGPoint( const SIZE& rSize );
	CGPoint( const Size& rSize );

	// translate the gpt
	void Offset( const POINT& rpt );
	void Offset( const Point& rpt );
	void Offset( const SIZE& rSize );
	void Offset( const Size& rSize );

	void operator=( const GPoint& rpt );
	void operator=( const POINT& rpt );
	void operator=( const Point& rpt );

	void operator=( const SIZE& rSize );
	void operator=( const Size& rSize );

	BOOL operator==( const POINT& rpt ) const;
	BOOL operator==( const Point& rpt ) const;

	BOOL operator==( const SIZE& rSize ) const;
	BOOL operator==( const Size& rSize ) const;

	BOOL operator!=( const POINT& rpt ) const;
	BOOL operator!=( const Point& rpt ) const;

	BOOL operator!=( const SIZE& rpt ) const;
	BOOL operator!=( const Size& rpt ) const;

	void operator+=( const POINT& rpt );
	void operator+=( const Point& rpt );

	void operator-=( const POINT& rpt );
	void operator-=( const Point& rpt );

	void operator+=( const SIZE& rSize );
	void operator+=( const Size& rSize );

	void operator-=( const SIZE& rSize );
	void operator-=( const Size& rSize );

	// Operators returning GPoint values
	CGPoint operator+( const POINT& rpt ) const;
	CGPoint operator+( const Point& rpt ) const;

	CGPoint operator-( const POINT& rpt ) const;
	CGPoint operator-( const Point& rpt ) const;

	CGPoint operator+( const SIZE& rSize ) const;
	CGPoint operator+( const Size& rSize ) const;

	CGPoint operator-( const SIZE& rSize ) const;
	CGPoint operator-( const Size& rSize ) const;

	// Operators returning CRect/Rect values
	CGRect operator+( const RECT& rRect ) const;
	CGRect operator-( const RECT& rRect ) const;

	CGRect operator+( const Rect& rRect ) const;
	CGRect operator-( const Rect& rRect ) const;
};

extern CU_EXT_DATA const GPoint nullGPoint;*/

#endif //!___G_POINT__PH___