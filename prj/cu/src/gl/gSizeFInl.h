#ifndef ___G_SIZE_F_INL__PH___
#define ___G_SIZE_F_INL__PH___

inline CGSizeF::CGSizeF( INT _cx, INT _cy ) {
	cx = (FLOAT)_cx; cy = (FLOAT)_cy; }

inline CGSizeF::CGSizeF( FLOAT _cx, FLOAT _cy ) {
	cx = _cx; cy = _cy; }

inline CGSizeF::CGSizeF( DWORD dwSize ) {
	cx = LOWORD(dwSize); cy = HIWORD(dwSize); }

inline CGSizeF::CGSizeF( const SIZE& rSize ) {
	cx = (FLOAT)rSize.cx; cy = (FLOAT)rSize.cy; }

inline CGSizeF::CGSizeF( const GSizeF& rSize ) {
	cx = rSize.cx; cy = rSize.cy; }

inline CGSizeF::CGSizeF( const POINT& rPoint ) {
	cx = (FLOAT)rPoint.x; cy = (FLOAT)rPoint.y; }

inline CGSizeF::CGSizeF( const GPointF& rPoint ) {
	cx = rPoint.x; cy = rPoint.y; }

inline BOOL CGSizeF::operator==( const SIZE& rSize ) const {
	return cx == rSize.cx && cy == rSize.cy; }

inline BOOL CGSizeF::operator==( const GSizeF& rSize ) const {
	return cx == rSize.cx && cy == rSize.cy; }

inline BOOL CGSizeF::operator!=( const SIZE& rSize ) const {
	return cx != rSize.cx || cy != rSize.cy; }

inline BOOL CGSizeF::operator!=( const GSizeF& rSize ) const {
	return cx != rSize.cx || cy != rSize.cy; }

inline void CGSizeF::operator+=( const SizeF& rSize ) {
	cx += rSize.Width; cy += rSize.Height; }

inline void CGSizeF::operator+=( const Size& rSize ) {
	cx += rSize.Width; cy += rSize.Height; }

inline void CGSizeF::operator-=( const SizeF& rSize ) {
	cx -= rSize.Width; cy -= rSize.Height; }

inline void CGSizeF::operator-=( const Size& rSize ) {
	cx -= rSize.Width; cy -= rSize.Height; }

inline CGSizeF CGSizeF::operator+( const SizeF& rSize ) const {
	CGSizeF size( rSize );
	size += *this;
	return size; }

inline CGSizeF CGSizeF::operator+( const Size& rSize ) const {
	CGSizeF size( rSize );
	size += *this;
	return size; }

inline CGSizeF CGSizeF::operator-( const SizeF& rSize ) const {
	CGSizeF size( rSize );
	size -= *this;
	return size; }

inline CGSizeF CGSizeF::operator-( const Size& rSize ) const {
	CGSizeF size( rSize );
	size -= *this;
	return size; }

inline CGPointF CGSizeF::operator+( const PointF& rPoint ) const {
	CGSizeF size( rPoint );
	size += *this;
	return size; }

inline CGPointF CGSizeF::operator+( const Point& rPoint ) const {
	CGSizeF size( rPoint );
	size += *this;
	return size; }

inline CGPointF CGSizeF::operator-( const PointF& rPoint ) const {
	CGSizeF size( rPoint );
	size -= *this;
	return size; }

inline CGPointF CGSizeF::operator-( const Point& rPoint ) const {
	CGSizeF size( rPoint );
	size -= *this;
	return size; }

inline CGRectF CGSizeF::operator+( const RectF& rRect ) const {
	CGRectF rect( rRect );
	rect += *this;
	return rect; }

inline CGRectF CGSizeF::operator+( const Rect& rRect ) const {
	CGRectF rect( rRect );
	rect += *this;
	return rect; }

inline CGRectF CGSizeF::operator-( const RectF& rRect ) const {
	CGRectF rect( rRect );
	rect -= *this;
	return rect; }

inline CGRectF CGSizeF::operator-( const Rect& rRect ) const {
	CGRectF rect( rRect );
	rect -= *this;
	return rect; }

#endif //!___G_SIZE_F_INL__PH___