#ifndef ___G_SIZE__PH___
#define ___G_SIZE__PH___

#if 0
class GSize;
class GRect;
class GPoint;

class GSize : public SIZE
{
};

class GSize
{
public:
	// construct an uninitialized size
	GSize();

	// create from two integers
	GSize( INT cx, INT cy );

	// create from another size
	GSize( const GSize& rSize );

	// create from a point
	GSize( const GPoint& rpt );

	// create from a DWORD: cx = LOWORD(dw) cy = HIWORD(dw)
	GSize( DWORD dwSize );

	const GSize& operator=( const GSize& rSize );

	// Operations
	BOOL operator==( const GSize& rSize ) const;
	BOOL operator!=( const GSize& rSize ) const;
	GSize operator-() const;

	void operator+=( const GSize& rSize );
	void operator-=( const GSize& rSize );

	// Operators returning GSize values
	GSize operator+( const GSize& rSize ) const;
	GSize operator-( const GSize& rSize ) const;

	// Operators returning GPoint values
	GPoint operator+( const GPoint& rpt ) const;
	GPoint operator-( const GPoint& rpt ) const;

	// Operators returning GRect values
	GRect operator+( const GRect& rRect ) const;
	GRect operator-( const GRect& rRect ) const;

public:
	INT		cx;
	INT		cy;
};

extern CU_EXT_DATA const GSize nullGSize;

/// Can accept SIZE, Size, POINT, Point
/// Can return SIZE, Size, POINT, Point
class CGSize : public GSize
{
public:
	CGSize();

	// create from two integers
	CGSize( INT cx, INT cy );

	// create from another size
	CGSize( const SIZE& rSize );
	CGSize( const Size& rSize );

	// create from a point
	CGSize( const POINT& rpt );
	CGSize( const Point& rpt );

	// translate the gpt
	void Offset( const POINT& rpt );
	void Offset( const Point& rpt );
	void Offset( const SIZE& rSize );
	void Offset( const Size& rSize );

	// Operations
	const CGSize& operator=( const GSize& rSize );

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
	CGSize operator+( const POINT& rpt ) const;
	CGSize operator+( const Point& rpt ) const;

	CGSize operator-( const POINT& rpt ) const;
	CGSize operator-( const Point& rpt ) const;

	CGSize operator+( const SIZE& rSize ) const;
	CGSize operator+( const Size& rSize ) const;

	CGSize operator-( const SIZE& rSize ) const;
	CGSize operator-( const Size& rSize ) const;

	// Operators returning CRect/Rect values
	CGRect operator+( const RECT& rRect ) const;
	CGRect operator-( const RECT& rRect ) const;

	CGRect operator+( const Rect& rRect ) const;
	CGRect operator-( const Rect& rRect ) const;
};
#endif //0

extern CU_EXT_DATA const SIZE nullSize;

#endif //!___G_SIZE__PH___