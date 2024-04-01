#ifndef ___G_POINT_F_INL__PH___
#define ___G_POINT_F_INL__PH___

inline CGPointF::CGPointF( INT _x, INT _y ) {
	x = (FLOAT)_x; y = (FLOAT)_y; }
	
inline CGPointF::CGPointF( FLOAT _x, FLOAT _y ) {
	x = _x; y = _y; }

inline CGPointF::CGPointF( DWORD dwPoint ) {
	x = LOWORD(dwPoint); x = HIWORD(dwPoint); }

inline CGPointF::CGPointF( const POINT& rPoint ) {
	x = (FLOAT)rPoint.x; y = (FLOAT)rPoint.y; }

inline CGPointF::CGPointF( const GPointF& rPoint ) {
	x = rPoint.x; y = rPoint.y; }

inline CGPointF::CGPointF( const SIZE& rSize ) {
	x = (FLOAT)rSize.cx; y = (FLOAT)rSize.cy; }

inline CGPointF::CGPointF( const GSizeF& rSize ) {
	x = rSize.cx; y = rSize.cy; }

inline void CGPointF::Offset( INT dx, INT dy ) {
	x += dx; y += dy; }

inline void CGPointF::Offset( FLOAT dx, FLOAT dy ) {
	x += dx; y += dy; }

inline void CGPointF::Offset( const POINT& rPoint ) {
	x += rPoint.x; y += rPoint.y; }

inline void CGPointF::Offset( const GPointF& rPoint ) {
	x += rPoint.x; y += rPoint.y; }

inline void CGPointF::Offset( const SIZE& rSize ) {
	x += rSize.cx; y += rSize.cy; }

inline void CGPointF::Offset( const GSizeF& rSize ) {
	x += rSize.cx; y += rSize.cy; }

inline BOOL CGPointF::operator==( const POINT& rPoint ) const {
	return x == rPoint.x && y == rPoint.y; }

inline BOOL CGPointF::operator==( const GPointF& rPoint ) const {
	return x == rPoint.x && y == rPoint.y; }

inline BOOL CGPointF::operator!=( const POINT& rPoint ) const {
	return x != rPoint.x || y != rPoint.y; }

inline BOOL CGPointF::operator!=( const GPointF& rPoint ) const {
	return x != rPoint.x || y != rPoint.y; }

inline void CGPointF::operator+=( const SIZE& rSize ) {
	x += rSize.cx; y += rSize.cy; }

inline void CGPointF::operator+=( const GSizeF& rSize ) {
	x += rSize.cx; y += rSize.cy; }

inline void CGPointF::operator-=( const SIZE& rSize ) {
	x -= rSize.cx; y -= rSize.cy; }

inline void CGPointF::operator-=( const GSizeF& rSize ) {
	x -= rSize.cx; y -= rSize.cy; }

inline void CGPointF::operator+=( const POINT& rPoint ) {
	x += rPoint.x; y += rPoint.y; }

inline void CGPointF::operator+=( const GPointF& rPoint ) {
	x += rPoint.x; y += rPoint.y; }

inline void CGPointF::operator-=( const POINT& rPoint ) {
	x -= rPoint.x; y -= rPoint.y; }

inline void CGPointF::operator-=( const GPointF& rPoint ) {
	x -= rPoint.x; y -= rPoint.y; }

inline CGPointF CGPointF::operator+( const SIZE& rSize ) const {
	CGPointF point;
	point.x = x + rSize.cx;
	point.y = y + rSize.cy;
	return rSize; }

inline CGPointF CGPointF::operator+( const GSizeF& rSize ) const {
	CGPointF point;
	point.x = x + rSize.cx;
	point.y = y + rSize.cy;
	return rSize; }

inline CGPointF CGPointF::operator-( const SIZE& rSize ) const {
	CGPointF point;
	point.x = x - rSize.cx;
	point.y = y - rSize.cy;
	return rSize; }

inline CGPointF CGPointF::operator-( const GSizeF& rSize ) const {
	CGPointF point;
	point.x = x - rSize.cx;
	point.y = y - rSize.cy;
	return rSize; }

inline CGPointF CGPointF::operator-() const {
	CGPointF point( -x , -y );
	return point; }

inline CGSizeF CGPointF::operator+( const POINT& rPoint ) const {
	CGSizeF size;
	size.cx = x + rPoint.x;
	size.cy = y + rPoint.y;
	return size; }

inline CGSizeF CGPointF::operator+( const GPointF& rPoint ) const {
	CGSizeF size;
	size.cx = x + rPoint.x;
	size.cy = y + rPoint.y;
	return size; }

inline CGSizeF CGPointF::operator-( const POINT& rPoint ) const {
	CGSizeF size;
	size.cx = x - rPoint.x;
	size.cy = y - rPoint.y;
	return size; }

inline CGSizeF CGPointF::operator-( const GPointF& rPoint ) const {
	CGSizeF size;
	size.cx = x - rPoint.x;
	size.cy = y - rPoint.y;
	return size; }

inline CGRectF CGPointF::operator+( const RECT& rRect ) const {
	CGRectF rect( rRect );
	rect += *this;
	return rect; }

inline CGRectF CGPointF::operator+( const GRectF& rRect ) const {
	CGRectF rect( rRect );
	rect += *this;
	return rect; }

inline CGRectF CGPointF::operator-( const RECT& rRect ) const {
	CGRectF rect( rRect );
	rect -= *this;
	return rect; }

inline CGRectF CGPointF::operator-( const GRectF& rRect ) const {
	CGRectF rect( rRect );
	rect -= *this;
	return rect; }

#ifdef _GDIPLUS_H
inline CGPointF::CGPointF( const PointF& rPoint ) {
	x = rPoint.X; y = rPoint.Y; }

inline CGPointF::CGPointF( const Point& rPoint ) {
	x = (FLOAT)rPoint.X; y = (FLOAT)rPoint.Y; }

inline CGPointF::CGPointF( const SizeF& rSize ) {
	x = rSize.Width; y = rSize.Height; }

inline CGPointF::CGPointF( const Size& rSize ) {
	x = (FLOAT)rSize.Width; y = (FLOAT)rSize.Height; }

inline void CGPointF::Offset( const PointF& rPoint ) {
	x += rPoint.X; y += rPoint.Y; }

inline void CGPointF::Offset( const Point& rPoint ) {
	x += rPoint.X; y += rPoint.Y; }

inline void CGPointF::Offset( const SizeF& rSize ) {
	x += rSize.Width; y += rSize.Height; }

inline void CGPointF::Offset( const Size& rSize ) {
	x += rSize.Width; y += rSize.Height; }

inline BOOL CGPointF::operator==( const PointF& rPoint ) const {
	return x == rPoint.X && y == rPoint.Y; }

inline BOOL CGPointF::operator==( const Point& rPoint ) const {
	return x == rPoint.X && y == rPoint.Y; }

inline BOOL CGPointF::operator!=( const PointF& rPoint ) const {
	return x != rPoint.X || y != rPoint.Y; }

inline BOOL CGPointF::operator!=( const Point& rPoint ) const {
	return x != rPoint.X || y != rPoint.Y; }

inline void CGPointF::operator+=( const SizeF& rSize ) {
	x += rSize.Width; y += rSize.Height; }

inline void CGPointF::operator+=( const Size& rSize ) {
	x += rSize.Width; y += rSize.Height; }

inline void CGPointF::operator-=( const SizeF& rSize ) {
	x -= rSize.Width; y -= rSize.Height; }

inline void CGPointF::operator-=( const Size& rSize ) {
	x -= rSize.Width; y -= rSize.Height; }

inline void CGPointF::operator+=( const PointF& rPoint ) {
	x += rPoint.X; y += rPoint.Y; }

inline void CGPointF::operator+=( const Point& rPoint ) {
	x += rPoint.X; y += rPoint.Y; }

inline void CGPointF::operator-=( const PointF& rPoint ) {
	x -= rPoint.X; y -= rPoint.Y; }

inline void CGPointF::operator-=( const Point& rPoint ) {
	x -= rPoint.X; y -= rPoint.Y; }

inline CGPointF CGPointF::operator+( const SizeF& rSize ) const {
	CGPointF point;
	point.x = x + rSize.Width;
	point.y = y + rSize.Height;
	return rSize; }

inline CGPointF CGPointF::operator+( const Size& rSize ) const {
	CGPointF point;
	point.x = x + rSize.Width;
	point.y = y + rSize.Height;
	return rSize; }

inline CGPointF CGPointF::operator-( const SizeF& rSize ) const {
	CGPointF point;
	point.x = x - rSize.Width;
	point.y = y - rSize.Height;
	return rSize; }

inline CGPointF CGPointF::operator-( const Size& rSize ) const {
	CGPointF point;
	point.x = x - rSize.Width;
	point.y = y - rSize.Height;
	return rSize; }

inline CGSizeF CGPointF::operator+( const PointF& rPoint ) const {
	CGSizeF size;
	size.cx = x + rPoint.X;
	size.cy = y + rPoint.Y;
	return size; }

inline CGSizeF CGPointF::operator+( const Point& rPoint ) const {
	CGSizeF size;
	size.cx = x + rPoint.X;
	size.cy = y + rPoint.Y;
	return size; }

inline CGSizeF CGPointF::operator-( const PointF& rPoint ) const {
	CGSizeF size;
	size.cx = x - rPoint.X;
	size.cy = y - rPoint.Y;
	return size; }

inline CGSizeF CGPointF::operator-( const Point& rPoint ) const {
	CGSizeF size;
	size.cx = x - rPoint.X;
	size.cy = y - rPoint.Y;
	return size; }

inline CGRectF CGPointF::operator+( const RectF& rRect ) const {
	CGRectF rect( rRect );
	rect += *this;
	return rect; }

inline CGRectF CGPointF::operator+( const Rect& rRect ) const {
	CGRectF rect( rRect );
	rect += *this;
	return rect; }

inline CGRectF CGPointF::operator-( const RectF& rRect ) const {
	CGRectF rect( rRect );
	rect -= *this;
	return rect; }

inline CGRectF CGPointF::operator-( const Rect& rRect ) const {
	CGRectF rect( rRect );
	rect -= *this;
	return rect; }
#endif //_GDIPLUS_H

#endif //!___G_POINT_F_INL__PH___