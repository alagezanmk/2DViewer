#ifndef ___G_SIZE_INL__PH___
#define ___G_SIZE_INL__PH___

#if 0
inline GSize::GSize() { 
	/* random filled */ }

inline GSize::GSize( INT _cx, INT _cy ) { 
	cx = _cx; cy = _cy; }

inline GSize::GSize( const GSize& rSize)
	{ *(GSize*)this = rSize; }

inline GSize::GSize( const GPoint& rpt ) { 
	*(GPoint*)this = rpt; }

inline GSize::GSize( DWORD dwSize ) {
		cx = (short)LOWORD(dwSize);
		cy = (short)HIWORD(dwSize); }

inline const GSize& GSize::operator=( const GSize& rSize ) {
	cx = rSize.cx; cy = rSize.cy; 
	return *this; }

inline BOOL GSize::operator==( const GSize& rSize ) const {
	return (cx == rSize.cx && cy == rSize.cy); }

inline BOOL GSize::operator!=( const GSize& rSize ) const {
	return (cx != rSize.cx || cy != rSize.cy); }

inline void GSize::operator+=( const GSize& rSize ) {
	cx += rSize.cx; cy += rSize.cy; }

inline void GSize::operator-=( const GSize& rSize) {
	cx -= rSize.cx; cy -= rSize.cy; }

inline GSize GSize::operator+( const GSize& rSize) const {
	return GSize(cx + rSize.cx, cy + rSize.cy); }

inline GSize GSize::operator-( const GSize& rSize) const {
	return GSize(cx - rSize.cx, cy - rSize.cy); }

inline GSize GSize::operator-() const {
	return GSize( -cx, -cy ); }

inline GPoint GSize::operator+( const GPoint& rpt ) const {
	return GPoint( cx + rpt.x, cy + rpt.y ); }

inline GPoint GSize::operator-( const GPoint& rpt ) const {
	return GPoint( cx - rpt.x, cy - rpt.y ); }

inline GRect GSize::operator+( const GRect& rRect ) const {
	return GRect( rRect ) + *this; }

inline GRect GSize::operator-( const GRect& rRect ) const {
	return GRect( rRect ) - *this; }

///////////////////////////////////////////////////////////////////////////////////////////////////
inline CGSize::CGSize() {
	/*random filled*/ }

inline CGSize::CGSize( INT _cx, INT _cy ) { 
	cx = _cx; cy = _cy; }

inline CGSize::CGSize( const POINT& rpt )	{ 
	*(POINT*)this = rpt; }

inline CGSize::CGSize( const Point& rpt ) { 
	*(Point*)this = rpt; }

inline CGSize::CGSize( const SIZE& rSize )	{ 
	*(SIZE*)this = rSize; }

inline CGSize::CGSize( const Size& rSize ) { 
	*(Size*)this = rSize; }

inline void CGSize::Offset( const POINT& rpt ) { 
	cx += rpt.x; cy += rpt.y; }

inline void CGSize::Offset( const Point& rpt ) { 
	cx += rpt.X; cy += rpt.Y; }

inline void CGSize::Offset( const SIZE& rSize ) { 
	cx += rSize.cx; cy += rSize.cy; }

inline void CGSize::Offset( const Size& rSize ) { 
	cx += rSize.Width; cy += rSize.Height; }

inline const CGSize& CGSize::operator=( const GSize& rSize ) {
	cx = rSize.cx; cy = rSize.cy; 
	return *this; }

inline void CGSize::operator=( const POINT& rpt ) {
	*(POINT*)this = rpt; }

inline void CGSize::operator=( const Point& rpt ) {
	*(Point*)this = rpt; }

inline void CGSize::operator=( const SIZE& rSize ) {
	*(SIZE*)this = rSize; }

inline void CGSize::operator=( const Size& rSize ) {
	*(Size*)this = rSize; }

inline BOOL CGSize::operator==( const POINT& rpt ) const {
	return (cx == rpt.x && cy == rpt.y); }

inline BOOL CGSize::operator==( const Point& rpt ) const {
	return (cx == rpt.X && cy == rpt.Y); }

inline BOOL CGSize::operator==( const SIZE& rSize ) const {
	return (cx == rSize.cx && cy == rSize.cy); }

inline BOOL CGSize::operator==( const Size& rSize ) const {
	return (cx == rSize.Width && cy == rSize.Height); }

inline BOOL CGSize::operator!=( const POINT& rpt ) const {
	return (cx != rpt.x && cy != rpt.y); }

inline BOOL CGSize::operator!=( const Point& rpt ) const {
	return (cx != rpt.X && cy != rpt.Y); }

inline BOOL CGSize::operator!=( const SIZE& rSize ) const {
	return (cx != rSize.cx && cy != rSize.cy); }

inline BOOL CGSize::operator!=( const Size& rSize ) const {
	return (cx != rSize.Width && cy != rSize.Height); }

inline void CGSize::operator+=( const POINT& rpt ) {
	cx += rpt.x; cy += rpt.y; } 

inline void CGSize::operator+=( const Point& rpt ) {
	cx += rpt.X; cy += rpt.Y; } 

inline void CGSize::operator+=( const SIZE& rSize ) {
	cx += rSize.cx; cy += rSize.cy; } 

inline void CGSize::operator+=( const Size& rSize ) {
	cx += rSize.Width; cy += rSize.Height; } 

inline void CGSize::operator-=( const POINT& rpt ) {
	cx -= rpt.x; cy -= rpt.y; } 

inline void CGSize::operator-=( const Point& rpt ) {
	cx -= rpt.X; cy += rpt.Y; } 

inline void CGSize::operator-=( const SIZE& rSize ) {
	cx -= rSize.cx; cy -= rSize.cy; } 

inline void CGSize::operator-=( const Size& rSize ) {
	cx -= rSize.Width; cy -= rSize.Height; } 

inline CGSize CGSize::operator+( const POINT& rpt ) const {
	return CGSize(cx + rpt.x, cy + rpt.y); } 

inline CGSize CGSize::operator+( const Point& rpt ) const {
	return CGSize(cx + rpt.X, cy + rpt.Y); } 

inline CGSize CGSize::operator+( const SIZE& rSize ) const {
	return CGSize(cx + rSize.cx, cy + rSize.cy); } 

inline CGSize CGSize::operator+( const Size& rSize ) const {
	return CGSize(cx + rSize.Width, cy + rSize.Height); } 

inline CGSize CGSize::operator-( const POINT& rpt ) const {
	return CGSize(cx - rpt.x, cy - rpt.y); } 

inline CGSize CGSize::operator-( const Point& rpt ) const {
	return CGSize(cx - rpt.X, cy + rpt.Y); } 

inline CGSize CGSize::operator-( const SIZE& rSize ) const {
	return CGSize(cx - rSize.cx, cy - rSize.cy); } 

inline CGSize CGSize::operator-( const Size& rSize ) const {
	return CGSize(cx - rSize.Width, cy - rSize.Height); } 

inline CGRect CGSize::operator+( const RECT& rRect ) const {
	CGRect rect( rRect );
	rect += *this;
	return rect; }

inline CGRect CGSize::operator+( const Rect& rRect ) const {
	CGRect rect( rRect );
	rect += *this;
	return rect; }
	
inline CGRect CGSize::operator-( const RECT& rRect ) const {
	CGRect rect( rRect );
	rect += *this;
	return rect; }

inline CGRect CGSize::operator-( const Rect& rRect ) const {
	CGRect rect( rRect );
	rect += *this;
	return rect; }
#endif //0

#endif //!___G_SIZE_INL__PH___