#ifndef ___G_POINT_INL__PH___
#define ___G_POINT_INL__PH___

#if 0
inline GPoint::GPoint()	{ 
	/* random filled */ }

inline GPoint::GPoint( INT _x, INT _y )	{ 
	x = _x; y = _y; }

inline GPoint::GPoint( const GPoint& rpt )	{ 
	*(GPoint*)this = rpt; }

inline GPoint::GPoint( const GSize& rSize ) { 
	*(GSize*)this = rSize; }

inline GPoint::GPoint( DWORD dwPoint ) {
		x = (short)LOWORD(dwPoint);
		y = (short)HIWORD(dwPoint); }

inline void GPoint::Offset( INT dx, INT dy ) { 
	x += dx; y += dy; }

inline void GPoint::Offset( const GPoint& rpt ) { 
	x += rpt.x; y += rpt.y; }

inline void GPoint::Offset( const GSize& rSize ) { 
	x += rSize.cx; y += rSize.cy; }

inline void GPoint::operator=( const GPoint& rgpt ) {
	*(GPoint*)this = rgpt; }

inline BOOL GPoint::operator==( const GPoint& rpt ) const { 
	return (x == rpt.x && y == rpt.y); }

inline BOOL GPoint::operator!=( const GPoint& rpt) const { 
	return (x != rpt.x || y != rpt.y); }

inline GPoint GPoint::operator-() const {
	return GPoint(-x, -y); }

inline void GPoint::operator+=( const GSize& rSize ) {
	x += rSize.cx; y += rSize.cy; }

inline void GPoint::operator-=( const GSize& rSize ) {
	x -= rSize.cx; y -= rSize.cy; }

inline void GPoint::operator+=( const GPoint& rpt ) {
	x += rpt.x; y += rpt.y; }

inline void GPoint::operator-=( const GPoint& rpt ) {
	x -= rpt.x; y -= rpt.y; }

inline GPoint GPoint::operator+( const GSize& rSize ) const {
	return GPoint(x + rSize.cx, y + rSize.cy); }

inline GPoint GPoint::operator-( const GSize& rSize ) const {
	return GPoint(x - rSize.cx, y - rSize.cy); }

inline GPoint GPoint::operator+( const GPoint& rpt ) const {
	return GPoint(x + rpt.x, y + rpt.y); }

inline GPoint GPoint::operator-( const GPoint& rpt ) const {
	return GPoint(x - rpt.x, y - rpt.y); }

inline GRect GPoint::operator+( const GRect& rRect ) const {
	return GRect( rRect ) + *this; }

inline GRect GPoint::operator-( const GRect& rRect ) const {
	return GRect( rRect ) - *this; }

///////////////////////////////////////////////////////////////////////////////////////////////////
inline CGPoint::CGPoint() {
	/*random filled*/ }

inline CGPoint::CGPoint( INT _x, INT _y ) { 
	x = _x; y = _y; }

inline CGPoint::CGPoint( const POINT& rpt )	{ 
	*(POINT*)this = rpt; }

inline CGPoint::CGPoint( const Point& rpt ) { 
	*(Point*)this = rpt; }

inline CGPoint::CGPoint( const SIZE& rSize )	{ 
	*(SIZE*)this = rSize; }

inline CGPoint::CGPoint( const Size& rSize ) { 
	*(Size*)this = rSize; }

inline void CGPoint::Offset( const POINT& rpt ) { 
	x += rpt.x; y += rpt.y; }

inline void CGPoint::Offset( const Point& rpt ) { 
	x += rpt.X; y += rpt.Y; }

inline void CGPoint::Offset( const SIZE& rSize ) { 
	x += rSize.cx; y += rSize.cy; }

inline void CGPoint::Offset( const Size& rSize ) { 
	x += rSize.Width; y += rSize.Height; }

inline void CGPoint::operator=( const GPoint& rgpt ) {
	*(GPoint*)this = rgpt; }

inline void CGPoint::operator=( const POINT& rpt ) {
	*(POINT*)this = rpt; }

inline void CGPoint::operator=( const Point& rpt ) {
	*(Point*)this = rpt; }

inline void CGPoint::operator=( const SIZE& rSize ) {
	*(SIZE*)this = rSize; }

inline void CGPoint::operator=( const Size& rSize ) {
	*(Size*)this = rSize; }

inline BOOL CGPoint::operator==( const POINT& rpt ) const {
	return (x == rpt.x && y == rpt.y); }

inline BOOL CGPoint::operator==( const Point& rpt ) const {
	return (x == rpt.X && y == rpt.Y); }

inline BOOL CGPoint::operator==( const SIZE& rSize ) const {
	return (x == rSize.cx && y == rSize.cy); }

inline BOOL CGPoint::operator==( const Size& rSize ) const {
	return (x == rSize.Width && y == rSize.Height); }

inline BOOL CGPoint::operator!=( const POINT& rpt ) const {
	return (x != rpt.x && y != rpt.y); }

inline BOOL CGPoint::operator!=( const Point& rpt ) const {
	return (x != rpt.X && y != rpt.Y); }

inline BOOL CGPoint::operator!=( const SIZE& rSize ) const {
	return (x != rSize.cx && y != rSize.cy); }

inline BOOL CGPoint::operator!=( const Size& rSize ) const {
	return (x != rSize.Width && y != rSize.Height); }

inline void CGPoint::operator+=( const POINT& rpt ) {
	x += rpt.x; y += rpt.y; } 

inline void CGPoint::operator+=( const Point& rpt ) {
	x += rpt.X; y += rpt.Y; } 

inline void CGPoint::operator+=( const SIZE& rSize ) {
	x += rSize.cx; y += rSize.cy; } 

inline void CGPoint::operator+=( const Size& rSize ) {
	x += rSize.Width; y += rSize.Height; } 

inline void CGPoint::operator-=( const POINT& rpt ) {
	x -= rpt.x; y -= rpt.y; } 

inline void CGPoint::operator-=( const Point& rpt ) {
	x -= rpt.X; y += rpt.Y; } 

inline void CGPoint::operator-=( const SIZE& rSize ) {
	x -= rSize.cx; y -= rSize.cy; } 

inline void CGPoint::operator-=( const Size& rSize ) {
	x -= rSize.Width; y -= rSize.Height; } 

inline CGPoint CGPoint::operator+( const POINT& rpt ) const {
	return CGPoint(x + rpt.x, y + rpt.y); } 

inline CGPoint CGPoint::operator+( const Point& rpt ) const {
	return CGPoint(x + rpt.X, y + rpt.Y); } 

inline CGPoint CGPoint::operator+( const SIZE& rSize ) const {
	return CGPoint(x + rSize.cx, y + rSize.cy); } 

inline CGPoint CGPoint::operator+( const Size& rSize ) const {
	return CGPoint(x + rSize.Width, y + rSize.Height); } 

inline CGPoint CGPoint::operator-( const POINT& rpt ) const {
	return CGPoint(x - rpt.x, y - rpt.y); } 

inline CGPoint CGPoint::operator-( const Point& rpt ) const {
	return CGPoint(x - rpt.X, y + rpt.Y); } 

inline CGPoint CGPoint::operator-( const SIZE& rSize ) const {
	return CGPoint(x - rSize.cx, y - rSize.cy); } 

inline CGPoint CGPoint::operator-( const Size& rSize ) const {
	return CGPoint(x - rSize.Width, y - rSize.Height); } 

inline CGRect CGPoint::operator+( const RECT& rRect ) const {
	CGRect rect( rRect );
	rect += *this;
	return rect; }

inline CGRect CGPoint::operator+( const Rect& rRect ) const {
	CGRect rect( rRect );
	rect += *this;
	return rect; }
	
inline CGRect CGPoint::operator-( const RECT& rRect ) const {
	CGRect rect( rRect );
	rect -= *this;
	return rect; }

inline CGRect CGPoint::operator-( const Rect& rRect ) const {
	CGRect rect( rRect );
	rect -= *this;
	return rect; }
#endif //0

#endif //!___G_POINT_INL__PH___
