#ifndef ___G_RECT_F_INL__PH___
#define ___G_RECT_F_INL__PH___

inline CGRectF::CGRectF( INT _left, INT _top, INT _right, INT _bottom ) {
	left = (FLOAT)_left, top = (FLOAT)_top; 
	right = (FLOAT)_right; bottom = (FLOAT)_bottom; }

inline CGRectF::CGRectF( FLOAT _left, FLOAT _top, FLOAT _right, FLOAT _bottom ) {
	left = _left, top = _top; 
	right = _right; bottom = _bottom; }

inline CGRectF::CGRectF( const RECT& rRect ) {
	left = (FLOAT)rRect.left, top = (FLOAT)rRect.top; right = (FLOAT)rRect.right; bottom = (FLOAT)rRect.bottom; }

inline CGRectF::CGRectF( const GRectF& rRect ) {
	left = rRect.left, top = rRect.top; right = rRect.right; bottom = rRect.bottom; }

inline CGRectF::CGRectF( const POINT& rPoint, const SIZE& rSize ) {
	left = (FLOAT)rPoint.x, top = (FLOAT)rPoint.y; 
	right = (FLOAT)(rPoint.x + rSize.cx); bottom = (FLOAT)(rPoint.y + rSize.cy); }

inline CGRectF::CGRectF( const POINT& rTopLeft, const POINT& rBottomRight ) {
	left = (FLOAT)rTopLeft.x, top = (FLOAT)rTopLeft.y; 
	right = (FLOAT)rBottomRight.x; bottom = (FLOAT)rBottomRight.y; }

inline CGRectF::CGRectF( const GPointF& rPoint, const GSizeF& rSize ) {
	left = rPoint.x, top = rPoint.y; 
	right = rPoint.x + rSize.cx; bottom = rPoint.y + rSize.cy; }

inline CGRectF::CGRectF( const GPointF& rTopLeft, const GPointF& rBottomRight ){
	left = rTopLeft.x, top = rTopLeft.y; 
	right = rBottomRight.x; bottom = rBottomRight.y; }

inline FLOAT CGRectF::Width() const {
	return right - left; }
		
inline FLOAT CGRectF::Height() const {
	return bottom - top; }

inline GSizeF CGRectF::Size() const {
	GSizeF gfSizeF;
	Size( gfSizeF );
	return gfSizeF; }

inline void CGRectF::Size( GSizeF& rSize ) const {
	rSize.cx = right - left;
	rSize.cy = bottom - top; }

inline void CGRectF::Size( FLOAT& rfWidth, FLOAT& rfHeight ) const {
	rfWidth = right - left;
	rfHeight = bottom - top; }

inline GPointF CGRectF::TopLeft() const {
	GPointF gptf;
	TopLeft( gptf.x, gptf.y ); }

inline void CGRectF::TopLeft( GPointF& rPoint ) const {
	TopLeft( rPoint.x, rPoint.y ); }

inline void CGRectF::TopLeft( FLOAT& rx, FLOAT& ry ) const {
	rx = left; ry = top; }

inline GPointF CGRectF::BottomRight() const {
	GPointF gptf;
	BottomRight( gptf.x, gptf.y ); }

inline void CGRectF::BottomRight( GPointF& rPoint ) const {
	BottomRight( rPoint.x, rPoint.y ); }

inline void CGRectF::BottomRight( FLOAT& rx, FLOAT& ry ) const {
	rx = right; ry = bottom; }

inline GPointF CGRectF::CenterPoint() const {
	GPointF gptf;
	CenterPoint( gptf.x, gptf.y ); }

inline void CGRectF::CenterPoint( GPointF& rPoint ) const {
	CenterPoint( rPoint.x, rPoint.y ); }

inline void CGRectF::CenterPoint( FLOAT& rx, FLOAT& ry ) const {
	rx = (left + right) / 2; ry = (top + bottom) / 2; }

inline void CGRectF::SwapLeftRight() {
	FLOAT fTemp = left;
	left = right;
	right = fTemp; }

inline void CGRectF::SwapTopBottom() {
	FLOAT fTemp = top;
	top = bottom;
	bottom = fTemp; }

inline CGRectF::operator GRectF*() {
	return (GRectF*)this; }

inline CGRectF::operator const GRectF*() const {
	return (const GRectF*)this; }

CU_EXT_API BOOL IsRectEmpty( const GRectF& rRect );

CU_EXT_API void SetRectEmpty( GRectF& rRect );

inline void CGRectF::SetRectEmpty() {
	::SetRectEmpty( *this ); }

inline BOOL CGRectF::IsRectEmpty() const {
	return left == right && top == bottom; }

inline BOOL CGRectF::IsRectNull() const {
	return 0 == left && 0 == top && 0 == right && 0 == bottom; }

inline BOOL CGRectF::PtInRect( INT x, INT y ) const {
	return left <= x && right > x && top <= y && bottom > y; }

inline BOOL CGRectF::PtInRect( FLOAT x, FLOAT y ) const {
	return left <= x && right > x && top <= y && bottom > y; }

inline BOOL CGRectF::PtInRect( const POINT& rPoint ) const {
	return left <= rPoint.x && right > rPoint.x && top <= rPoint.y && bottom > rPoint.y; }

inline void CGRectF::SetRect( INT _left, INT _top, INT _right, INT _bottom ) {
	left = (FLOAT)_left; top = (FLOAT)_top; 
	right = (FLOAT)_right; bottom = (FLOAT)_bottom; }

inline void CGRectF::SetRect( FLOAT _left, FLOAT _top, FLOAT _right, FLOAT _bottom ) {
	left = _left; top = _top; 
	right = _right; bottom = _bottom; }

inline void CGRectF::SetRect( const RECT& rRect ) {
	left = (FLOAT)rRect.left; top = (FLOAT)rRect.top; 
	right = (FLOAT)rRect.right; bottom = (FLOAT)rRect.bottom; }

inline void CGRectF::SetRect( const GRectF& rRect ) {
	left = rRect.left; top = rRect.top; 
	right = rRect.right; bottom = rRect.bottom; }

inline void CGRectF::SetRect( const POINT& rPoint, const SIZE& rSize ) {
	left = (FLOAT)rPoint.x, top = (FLOAT)rPoint.y; 
	right = (FLOAT)(rPoint.x + rSize.cx); bottom = (FLOAT)(rPoint.y + rSize.cy); }

inline void CGRectF::SetRect( const POINT& rTopLeft, const POINT& rBottomRight ) {
	left = (FLOAT)rTopLeft.x, top = (FLOAT)rTopLeft.y; 
	right = (FLOAT)rBottomRight.x; bottom = (FLOAT)rBottomRight.y; }

inline void CGRectF::SetRect( const GPointF& rPoint, const GSizeF& rSize ) {
	left = rPoint.x, top = rPoint.y; 
	right = rPoint.x + rSize.cx; bottom = rPoint.y + rSize.cy; }

inline void CGRectF::SetRect( const GPointF& rTopLeft, const GPointF& rBottomRight ) {
	left = rTopLeft.x, top = rTopLeft.y; 
	right = rBottomRight.x; bottom = rBottomRight.y; }

inline void CGRectF::CopyRect( FLOAT& rfLeft, FLOAT& rfTop, FLOAT& rfRight, FLOAT& rfBottom ) const {
	rfLeft = left; rfTop = top;
	rfRight = right; rfBottom = bottom; }

CU_EXT_API void CopyRect( GRectF& rRect, const GRectF& rgrctfSrc );

inline void CGRectF::CopyRect( GRectF& rRect ) const {
	::CopyRect( rRect, *this ); }

inline void CGRectF::CopyRect( GPointF& rPoint, GSizeF& rSize ) const {
	rPoint.x = left; rPoint.y = top;
	rSize.cx = right - left; rSize.cy = bottom - top; }

inline void CGRectF::CopyRect( GPointF& rTopLeft, GPointF& rBottomRight ) const {
	rTopLeft.x = left; rTopLeft.y = top;
	rBottomRight.x = right; rBottomRight.y = bottom; }

CU_EXT_API BOOL EqualRect( const GRectF& rgrctf1, const GRectF& rgrctf2 );
	
inline BOOL CGRectF::EqualRect( const GRectF& rRect ) const {
	return ::EqualRect( *this, rRect ); }

inline void CGRectF::InflateRect( INT x, INT y ) {
	left -= x; top -= y;
	right += x; bottom += y; }

inline void CGRectF::InflateRect( FLOAT x, FLOAT y ) {
	left -= x; top -= y;
	right += x; bottom += y; }

inline void CGRectF::InflateRect( const SIZE& rSize ) {
	left -= rSize.cx; top -= rSize.cy;
	right += rSize.cx; bottom += rSize.cy; }

inline void CGRectF::InflateRect( const GSizeF& rSize ) {
	left -= rSize.cx; top -= rSize.cy;
	right += rSize.cx; bottom += rSize.cy; }

inline void CGRectF::InflateRect( const RECT& rRect ) {
	left -= rRect.left; top -= rRect.top;
	right += rRect.right; bottom += rRect.bottom; }

inline void CGRectF::InflateRect( const GRectF& rRect ) {
	left -= rRect.left; top -= rRect.top;
	right += rRect.right; bottom += rRect.bottom; }

inline void CGRectF::InflateRect( INT l, INT t, INT r, INT b ) {
	left -= l; top -= t;
	right += r; bottom += b; }

inline void CGRectF::InflateRect( FLOAT l, FLOAT t, FLOAT r, FLOAT b  ) {
	left -= l; top -= t;
	right += r; bottom += b; }

inline void CGRectF::DeflateRect( INT x, INT y ) {
	left += x; top += y;
	right -= x; bottom -= y; }

inline void CGRectF::DeflateRect( FLOAT x, FLOAT y ) {
	left += x; top += y;
	right -= x; bottom -= y; }

inline void CGRectF::DeflateRect( const SIZE& rSize ) {
	left += rSize.cx; top += rSize.cy;
	right -= rSize.cx; bottom -= rSize.cy; }

inline void CGRectF::DeflateRect( const GSizeF& rSize ) {
	left += rSize.cx; top += rSize.cy;
	right -= rSize.cx; bottom -= rSize.cy; }

inline void CGRectF::DeflateRect( const RECT& rRect ) {
	left += rRect.left; top += rRect.top;
	right -= rRect.right; bottom -= rRect.bottom; }

inline void CGRectF::DeflateRect( const GRectF& rRect ) {
	left += rRect.left; top += rRect.top;
	right -= rRect.right; bottom -= rRect.bottom; }

inline void CGRectF::DeflateRect( INT l, INT t, INT r, INT b ) {
	left += l; top += t;
	right -= r; bottom -= b; }

inline void CGRectF::DeflateRect( FLOAT l, FLOAT t, FLOAT r, FLOAT b  ) {
	left += l; top += t;
	right -= r; bottom -= b; }

inline void CGRectF::OffsetRect( INT x, INT y ) {
	left += x; top += y;
	right += x; bottom += y; }

inline void CGRectF::OffsetRect( FLOAT x, FLOAT y ) {
	left += x; top += y;
	right += x; bottom += y; }

inline void CGRectF::OffsetRect( const POINT& rPoint ) {
	left += rPoint.x; top += rPoint.y;
	right += rPoint.x; bottom += rPoint.y; }

inline void CGRectF::OffsetRect( const GPointF& rPoint ) {
	left += rPoint.x; top += rPoint.y;
	right += rPoint.x; bottom += rPoint.y; }

inline void CGRectF::OffsetRect( const SIZE& rSize ) {
	left += rSize.cx; top += rSize.cy;
	right += rSize.cx; bottom += rSize.cy; }

inline void CGRectF::OffsetRect( const GSizeF& rSize ) {
	left += rSize.cx; top += rSize.cy;
	right += rSize.cx; bottom += rSize.cy; }

inline void CGRectF::OffsetRect( const RECT& rRect ) {
	left += rRect.left; top += rRect.top;
	right += rRect.right; bottom += rRect.bottom; }

inline void CGRectF::OffsetRect( const GRectF& rRect ) {
	left += rRect.left; top += rRect.top;
	right += rRect.right; bottom += rRect.bottom; }

inline void CGRectF::OffsetRect( INT l, INT t, INT r, INT b ) {
	left += l; top += t;
	right += r; bottom += b; }

inline void CGRectF::OffsetRect( FLOAT l, FLOAT t, FLOAT r, FLOAT b  ) {
	left += l; top += t;
	right += r; bottom += b; }

CU_EXT_API void NormalizeRect( GRectF& rRect );

inline void CGRectF::NormalizeRect() {
	::NormalizeRect( *this ); }

CU_EXT_API BOOL IntersectRect( GRectF& rRect, const GRectF& rgrctf1, const GRectF& rgrctf2 );

inline BOOL CGRectF::IntersectRect( const GRectF& rgrctf1, const GRectF& rgrctf2 ) {
	return ::IntersectRect( *this, rgrctf1, rgrctf2 ); }

inline BOOL CGRectF::IntersectRect( const RECT& rRect1, const RECT& rrct2 )
{
	CRect rect;
	rect.IntersectRect( &rRect1, &rrct2 );

	right = (FLOAT)rect.right;
	bottom = (FLOAT)rect.bottom;
	left = (FLOAT)rect.left;
	top = (FLOAT)rect.top;

	return rect.IsRectEmpty();
}

CU_EXT_API BOOL UnionRect( GRectF& rRect, const GRectF& rgrctf1, const GRectF& rgrctf2 );

inline BOOL CGRectF::UnionRect( const GRectF& rgrctf1, const GRectF& rgrctf2 ) {
	return ::UnionRect( *this, rgrctf1, rgrctf2 ); }

inline BOOL CGRectF::UnionRect( const RECT& rRect1, const RECT& rrct2 )
{
	CRect rect;
	rect.UnionRect( &rRect1, &rrct2 );

	right = (FLOAT)rect.right;
	bottom = (FLOAT)rect.bottom;
	left = (FLOAT)rect.left;
	top = (FLOAT)rect.top;

	return rect.IsRectEmpty();
}

/// ToDo: Implement as said in help of CRect::SetRect
inline BOOL CGRectF::SubtractRect( const GRectF& rgrctf1, const GRectF& rgrctf2 ) {
	ASSERT( FALSE );
	return FALSE; }

inline BOOL CGRectF::SubtractRect( const RECT& rRect1, const RECT& rrct2 ) {
	ASSERT( FALSE ); 
	return FALSE; }

inline void CGRectF::operator=( const RECT& rRect ) {
	SetRect( rRect ); }

inline void CGRectF::operator=( const GRectF& rRect ) {
	SetRect( rRect ); }

CU_EXT_API BOOL IsEqualRect( const GRectF& rRect1, const GRectF& rRect2 );

inline BOOL CGRectF::operator==( const RECT& rRect ) const {
	return left == rRect.left && top == rRect.top &&
		   right == rRect.right && bottom == rRect.bottom; }
	
inline BOOL CGRectF::operator==( const GRectF& rRect ) const {
	return ::EqualRect( *this, rRect ); }

inline BOOL CGRectF::operator!=( const RECT& rRect ) const {
	return left != rRect.left || top != rRect.top ||
		   right != rRect.right || bottom != rRect.bottom; }

inline BOOL CGRectF::operator!=( const GRectF& rRect ) const {
	return FALSE == ::EqualRect( *this, rRect ); }

inline void CGRectF::operator+=( const RECT& rRect ) {
	left += rRect.left; top += rRect.top; 
	right += rRect.right; bottom += rRect.bottom; }
	
inline void CGRectF::operator+=( const GRectF& rRect ) {
	left += rRect.left; top += rRect.top; 
	right += rRect.right; bottom += rRect.bottom; }

inline void CGRectF::operator+=( const POINT& rPoint ) {
	left += rPoint.x; top += rPoint.y; 
	right += rPoint.x; bottom += rPoint.y; }

inline void CGRectF::operator+=( const GPointF& rPoint ) {
	left += rPoint.x; top += rPoint.y; 
	right += rPoint.x; bottom += rPoint.y; }

inline void CGRectF::operator+=( const SIZE& rSize ) {
	left += rSize.cx; top += rSize.cy; 
	right += rSize.cx; bottom += rSize.cy; }

inline void CGRectF::operator+=( const GSizeF& rSize ) {
	left += rSize.cx; top += rSize.cy; 
	right += rSize.cx; bottom += rSize.cy; }

inline void CGRectF::operator-=( const RECT& rRect ) {
	left -= rRect.left; top -= rRect.top; 
	right -= rRect.right; bottom -= rRect.bottom; }
	
inline void CGRectF::operator-=( const GRectF& rRect ) {
	left -= rRect.left; top -= rRect.top; 
	right -= rRect.right; bottom -= rRect.bottom; }

inline void CGRectF::operator-=( const POINT& rPoint ) {
	left -= rPoint.x; top -= rPoint.y; 
	right -= rPoint.x; bottom -= rPoint.y; }

inline void CGRectF::operator-=( const GPointF& rPoint ) {
	left -= rPoint.x; top -= rPoint.y; 
	right -= rPoint.x; bottom -= rPoint.y; }

inline void CGRectF::operator-=( const SIZE& rSize ) {
	left -= rSize.cx; top -= rSize.cy; 
	right -= rSize.cx; bottom -= rSize.cy; }

inline void CGRectF::operator-=( const GSizeF& rSize ) {
	left -= rSize.cx; top -= rSize.cy; 
	right -= rSize.cx; bottom -= rSize.cy; }

inline void CGRectF::operator&=( const RECT& rRect ) {
	CGRectF rctf( rRect ); 
	IntersectRect( *this, rctf ); }

inline void CGRectF::operator&=( const GRectF& rRect ) {
	IntersectRect( *this, rRect ); }

inline void CGRectF::operator|=( const RECT& rRect ) {
	CGRectF rctf( rRect ); 
	UnionRect( *this, rctf ); }

inline void CGRectF::operator|=( const GRectF& rRect ) {
	UnionRect( *this, rRect ); }

inline CGRectF CGRectF::operator+( const POINT& rPoint ) const {
	CGRectF rctf;
	rctf += rPoint; 
	return rctf; }
	
inline CGRectF CGRectF::operator+( const GPointF& rPoint ) const {
	CGRectF rctf;
	rctf += rPoint; 
	return rctf; }

inline CGRectF CGRectF::operator-( const POINT& rPoint ) const {
	CGRectF rctf;
	rctf -= rPoint; 
	return rctf; }

inline CGRectF CGRectF::operator-( const GPointF& rPoint ) const {
	CGRectF rctf;
	rctf -= rPoint; 
	return rctf; }

inline CGRectF CGRectF::operator+( const RECT& rRect ) const {
	CGRectF rctf;
	rctf += rRect; 
	return rctf; }

inline CGRectF CGRectF::operator+( const GRectF& rRect ) const {
	CGRectF rctf;
	rctf += rRect;
	return rctf; }

inline CGRectF CGRectF::operator-( const RECT& rRect ) const {
	CGRectF rctf;
	rctf -= rRect;
	return rctf; }

inline CGRectF CGRectF::operator-( const GRectF& rRect ) const {
	CGRectF rctf;
	rctf -= rRect;
	return rctf; }

inline CGRectF CGRectF::operator+( const SIZE& rSize ) const {
	CGRectF rctf;
	rctf += rSize;
	return rctf; }

inline CGRectF CGRectF::operator+( const GSizeF& rgSizef ) const {
	CGRectF rctf;
	rctf += rgSizef;
	return rctf; }

inline CGRectF CGRectF::operator-( const SIZE& rSize ) const {
	CGRectF rctf;
	rctf -= rSize;
	return rctf; }

inline CGRectF CGRectF::operator-( const GSizeF& rgSizef ) const {
	CGRectF rctf;
	rctf -= rgSizef;
	return rctf; }

inline CGRectF CGRectF::operator&( const RECT& rRect ) const {
	CGRectF rctf;
	rctf &= rRect;
	return rctf; }

inline CGRectF CGRectF::operator&( const GRectF& rRect ) const {
	CGRectF rctf;
	rctf &= rRect;
	return rctf; }

inline CGRectF CGRectF::operator|( const RECT& rRect ) const {
	CGRectF rctf;
	rctf |= rRect;
	return rctf; }

inline CGRectF CGRectF::operator|( const GRectF& rRect ) const {
	CGRectF rctf;
	rctf |= rRect;
	return rctf; }

#ifdef _GDIPLUS_H
inline CGRectF::CGRectF( const RectF& rRect ) {
	left = rRect.X, top = rRect.Y; 
	right = rRect.X + rRect.Width; bottom = rRect.Y + rRect.Height; }

inline CGRectF::CGRectF( const Rect& rRect ) {
	left = (FLOAT)rRect.X, top = (FLOAT)rRect.Y; 
	right = (FLOAT)(rRect.X + rRect.Width); bottom = (FLOAT)(rRect.Y + rRect.Height); }

inline CGRectF::CGRectF( const PointF& rPoint, const SizeF& rsizef ) {
	left = rPoint.X, top = rPoint.Y; 
	right = rPoint.X + rsizef.Width; bottom = rPoint.Y + rsizef.Height; }

inline CGRectF::CGRectF( const Point& rPoint, const GPSize& rsizef ) {
	left = (FLOAT)rPoint.X, top = (FLOAT)rPoint.Y; 
	right = (FLOAT)(rPoint.X + rsizef.Width); bottom = (FLOAT)(rPoint.Y + rsizef.Height); }

inline CGRectF::CGRectF( const PointF& rTopLeft, const PointF& rBottomRight ) {
	left = rTopLeft.X, top = rTopLeft.Y; 
	right = rBottomRight.X; bottom = rBottomRight.Y; }

inline CGRectF::CGRectF( const Point& rTopLeft, const Point& rBottomRight ) {
	left = (FLOAT)rTopLeft.X, top = (FLOAT)rTopLeft.Y; 
	right = (FLOAT)rBottomRight.X; bottom = (FLOAT)rBottomRight.Y; }

inline void CGRectF::Size( SizeF& rSize ) const {
	Size( rSize.Width, rSize.Height ); }

inline void CGRectF::CenterPoint( PointF& rPoint ) const {
	rPoint.X = (left + right) / 2;
	rPoint.Y = (top + bottom) / 2; }

inline BOOL CGRectF::PtInRect( const PointF& rPoint ) const {
	return PtInRect( rPoint.X, rPoint.Y ); }

inline BOOL CGRectF::PtInRect( const Point& rPoint ) const {
	return PtInRect( rPoint.X, rPoint.Y ); }

inline void CGRectF::SetRect( const RectF& rRect ) {
	SetRect( rRect.X, rRect.Y, rRect.X + rRect.Width, rRect.Y + rRect.Height ); }

inline void CGRectF::SetRect( const Rect& rRect ) {
	SetRect( rRect.X, rRect.Y, rRect.X + rRect.Width, rRect.Y + rRect.Height ); }

inline void CGRectF::SetRect( const PointF& rPoint, const SizeF& rsizef ) {
	SetRect( rPoint.X, rPoint.Y, rPoint.X + rsizef.Width, rPoint.Y + rsizef.Height ); }

//inline void CGRectF::SetRect( const Point& rPoint, const GPSize& rSize ) {
//	SetRect( rPoint.X, rPoint.Y, rPoint.X + rSize.Width, rPoint.Y + rSize.Height ); }

inline void CGRectF::SetRect( const PointF& rTopLeft, const PointF& rbottomRight ) {
	SetRect( rTopLeft.X, rTopLeft.Y, rbottomRight.X, rbottomRight.Y ); }

inline void CGRectF::SetRect( const Point& rTopLeft, const Point& rbottomRight ) {
	SetRect( rTopLeft.X, rTopLeft.Y, rbottomRight.X, rbottomRight.Y ); }

inline void CGRectF::CopyRect( RectF& rRect ) const {
	rRect.X = left, rRect.Y = top;
	rRect.Width = right - left;
	rRect.Height = bottom - top; }

inline void CGRectF::CopyRect( PointF& rPoint, SizeF& rsizef ) const {
	rPoint.X = left, rPoint.Y = top;
	rsizef.Width = right - left;
	rsizef.Height = bottom - top; }

inline void CGRectF::CopyRect( PointF& rTopLeft, PointF& rbottomRight ) const {
	rTopLeft.X = left, rTopLeft.Y = top;
	rbottomRight.X = top, rbottomRight.Y = bottom; }

inline BOOL CGRectF::EqualRect( const RectF& rRect ) const {
	return left == rRect.X && top == rRect.Y &&
		   right == rRect.X + rRect.Width && bottom == rRect.Y + rRect.Height; }

inline void CGRectF::InflateRect( const PointF& rPoint ) {
	InflateRect( rPoint.X, rPoint.Y ); }

inline void CGRectF::InflateRect( const Point& rPoint ) {
	InflateRect( rPoint.X, rPoint.Y ); }

inline void CGRectF::InflateRect( const SizeF& rSize ) {
	InflateRect( rSize.Width, rSize.Height ); }

inline void CGRectF::InflateRect( const GPSize& rSize ) {
	InflateRect( rSize.Width, rSize.Height ); }

inline void CGRectF::InflateRect( const RectF& rRect ) {
	InflateRect( rRect.X, rRect.Y, 
		rRect.X + rRect.Width, rRect.Y + rRect.Height ); }

inline void CGRectF::InflateRect( const Rect& rRect ) {
	InflateRect( rRect.X, rRect.Y, rRect.X + rRect.Width, rRect.Y + rRect.Height ); }

inline void CGRectF::DeflateRect( const PointF& rPoint ) {
	DeflateRect( rPoint.X, rPoint.Y ); }

inline void CGRectF::DeflateRect( const Point& rPoint ) {
	DeflateRect( rPoint.X, rPoint.Y ); }

inline void CGRectF::DeflateRect( const SizeF& rSize ) {
	DeflateRect( rSize.Width, rSize.Height ); }

inline void CGRectF::DeflateRect( const GPSize& rSize ) {
	DeflateRect( rSize.Width, rSize.Height ); }

inline void CGRectF::DeflateRect( const RectF& rRect ) {
	DeflateRect( rRect.X, rRect.Y, rRect.X + rRect.Width, rRect.Y + rRect.Height ); }

inline void CGRectF::DeflateRect( const Rect& rRect ) {
	DeflateRect( rRect.X, rRect.Y, rRect.X + rRect.Width, rRect.Y + rRect.Height ); }

inline void CGRectF::OffsetRect( const PointF& rPoint ) {
	OffsetRect( rPoint.X, rPoint.Y ); }

inline void CGRectF::OffsetRect( const Point& rPoint ) {
	OffsetRect( rPoint.X, rPoint.Y ); }

inline void CGRectF::OffsetRect( const SizeF& rSize ) {
	OffsetRect( rSize.Width, rSize.Height ); }

inline void CGRectF::OffsetRect( const GPSize& rSize ) {
	OffsetRect( rSize.Width, rSize.Height ); }

inline void CGRectF::OffsetRect( const RectF& rRect ) {
	OffsetRect( rRect.X, rRect.Y, rRect.X + rRect.Width, rRect.Y + rRect.Height ); }

inline void CGRectF::OffsetRect( const Rect& rRect ) {
	OffsetRect( rRect.X, rRect.Y, rRect.X + rRect.Width, rRect.Y + rRect.Height ); }

inline BOOL CGRectF::IntersectRect( const RectF& rRect1, const RectF& rRect2 ) 
{
	RectF rect;
	BOOL bIsEmpty = RectF::Intersect( rect, rRect1, rRect2 );
	left = rect.X;
	top = rect.Y;
	right = rect.X + rect.Width;
	bottom = rect.Y + rect.Height;
	return bIsEmpty;
}

inline BOOL CGRectF::IntersectRect( const Rect& rRect1, const Rect& rRect2 )
{
	Rect rect;
	BOOL bIsEmpty = Rect::Intersect( rect, rRect1, rRect2 );
	left = (FLOAT)rect.X;
	top = (FLOAT)rect.Y;
	right = (FLOAT)(rect.X + rect.Width);
	bottom = (FLOAT)(rect.Y + rect.Height);
	return bIsEmpty;
}

inline BOOL CGRectF::UnionRect( const RectF& rRect1, const RectF& rRect2 ) 
{
	RectF rect;
	BOOL bIsEmpty = RectF::Union( rect, rRect1, rRect2 );
	left = rect.X;
	top = rect.Y;
	right = rect.X + rect.Width;
	bottom = rect.Y + rect.Height;
	return bIsEmpty;
}

inline BOOL CGRectF::UnionRect( const Rect& rRect1, const Rect& rRect2 )
{
	Rect rect;
	BOOL bIsEmpty = Rect::Union( rect, rRect1, rRect2 );
	left = (FLOAT)rect.X;
	top = (FLOAT)rect.Y;
	right = (FLOAT)(rect.X + rect.Width);
	bottom = (FLOAT)(rect.Y + rect.Height);
	return bIsEmpty;
}

/// ToDo: Complete this as in CRect::SubtraactRect
inline BOOL CGRectF::SubtractRect( const RectF& rRect1, const RectF& rRect2 ) 
{
	ASSERT( FALSE );
	return FALSE;
}

/// ToDo: Complete this as in CRect::SubtraactRect
inline BOOL CGRectF::SubtractRect( const Rect& rRect1, const Rect& rRect2 )
{
	ASSERT( FALSE );
	return FALSE;
}

inline void CGRectF::operator=( const RectF& rRect )
{
	left = rRect.X;
	top = rRect.Y;
	right = rRect.X + rRect.Width;
	bottom = rRect.Y + rRect.Height;
}

inline void CGRectF::operator=( const Rect& rRect )
{
	left = (FLOAT)rRect.X;
	top = (FLOAT)rRect.Y;
	right = (FLOAT)(rRect.X + rRect.Width);
	bottom = (FLOAT)(rRect.Y + rRect.Height);
}

inline BOOL CGRectF::operator==( const RectF& rRect ) const {
	return left == rRect.X && top == rRect.Y &&
		   right == rRect.X + rRect.Width && 
		   bottom == rRect.X + rRect.Height; }

inline BOOL CGRectF::operator==( const Rect& rRect ) const {
	return left == rRect.X && top == rRect.Y &&
		   right == rRect.X + rRect.Width && 
		   bottom == rRect.X + rRect.Height; }

inline BOOL CGRectF::operator!=( const RectF& rRect ) const {
	return left != rRect.X || top != rRect.Y ||
		   right != rRect.X + rRect.Width || 
		   bottom != rRect.X + rRect.Height; }

inline BOOL CGRectF::operator!=( const Rect& rRect ) const {
	return left != rRect.X || top != rRect.Y ||
		   right != rRect.X + rRect.Width || 
		   bottom != rRect.X + rRect.Height; }

inline void CGRectF::operator+=( const RectF& rRect ) {
	left += rRect.X; top += rRect.Y;
	right += rRect.X + rRect.Width; 
	bottom += rRect.Y + rRect.Height; }

inline void CGRectF::operator+=( const Rect& rRect ) {
	left += rRect.X; top += rRect.Y;
	right += rRect.X + rRect.Width; 
	bottom += rRect.Y + rRect.Height; }

inline void CGRectF::operator+=( const PointF& rPoint ) {
	left += rPoint.X; top += rPoint.Y;
	right += rPoint.X; bottom += rPoint.Y; }

inline void CGRectF::operator+=( const Point& rPoint ) {
	left += rPoint.X; top += rPoint.Y;
	right += rPoint.X; bottom += rPoint.Y; }

inline void CGRectF::operator+=( const SizeF& rSize ) {
	left += rSize.Width; top += rSize.Height;
	right += rSize.Width; bottom += rSize.Height; }

inline void CGRectF::operator+=( const GPSize& rSize ) {
	left += rSize.Width; top += rSize.Height;
	right += rSize.Width; bottom += rSize.Height; }

inline void CGRectF::operator-=( const RectF& rRect ) {
	left -= rRect.X; top -= rRect.Y;
	right -= rRect.X + rRect.Width; 
	bottom -= rRect.Y + rRect.Height; }

inline void CGRectF::operator-=( const Rect& rRect ) {
	left -= rRect.X; top -= rRect.Y;
	right -= rRect.X + rRect.Width; 
	bottom -= rRect.Y + rRect.Height; }

inline void CGRectF::operator-=( const PointF& rPoint ) {
	left -= rPoint.X; top -= rPoint.Y;
	right -= rPoint.X; bottom -= rPoint.Y; }

inline void CGRectF::operator-=( const Point& rPoint ) {
	left -= rPoint.X; top -= rPoint.Y;
	right -= rPoint.X; bottom -= rPoint.Y; }

inline void CGRectF::operator-=( const SizeF& rSize ) {
	left -= rSize.Width; top -= rSize.Height;
	right -= rSize.Width; bottom -= rSize.Height; }

inline void CGRectF::operator-=( const GPSize& rSize ) {
	left -= rSize.Width; top -= rSize.Height;
	right -= rSize.Width; bottom -= rSize.Height; }

inline void CGRectF::operator&=( const RectF& rRect ) {
	CGRectF rect( rRect );
	*this &= rect; }

inline void CGRectF::operator&=( const Rect& rRect ) {
	CGRectF rect( rRect );
	*this &= rect; }

inline void CGRectF::operator|=( const RectF& rRect ) {
	CGRectF rect( rRect );
	*this |= rect; }

inline void CGRectF::operator|=( const Rect& rRect ) {
	CGRectF rect( rRect );
	*this |= rect; }

inline CGRectF CGRectF::operator+( const PointF& rPoint ) const {
	CGRectF rect( *this );
	rect += *((GPointF*)&rPoint); 
	return rect; }

inline CGRectF CGRectF::operator+( const Point& rPoint ) const {
	CGRectF rect( *this );
	rect += *((POINT*)&rPoint); 
	return rect; }

inline CGRectF CGRectF::operator-( const PointF& rPoint ) const {
	CGRectF rect( *this );
	rect -= *((GPointF*)&rPoint); 
	return rect; }

inline CGRectF CGRectF::operator-( const Point& rPoint ) const {
	CGRectF rect( *this );
	rect -= *((POINT*)&rPoint); 
	return rect; }

inline CGRectF CGRectF::operator+( const RectF& rRect ) const {
	CGRectF rect( *this );
	rect += rRect;
	return rect; }

inline CGRectF CGRectF::operator+( const Rect& rRect ) const {
	CGRectF rect( *this );
	rect += rRect;
	return rect; }

inline CGRectF CGRectF::operator-( const RectF& rRect ) const {
	CGRectF rect( *this );
	rect -= rRect;
	return rect; }

inline CGRectF CGRectF::operator-( const Rect& rRect ) const {
	CGRectF rect( *this );
	rect -= rRect;
	return rect; }

inline CGRectF CGRectF::operator+( const SizeF& rSize ) const {
	CGRectF rect( *this );
	rect += rSize;
	return rect; }

inline CGRectF CGRectF::operator+( const GPSize& rSize ) const {
	CGRectF rect( *this );
	rect += rSize;
	return rect; }

inline CGRectF CGRectF::operator-( const SizeF& rSize ) const {
	CGRectF rect( *this );
	rect -= rSize;
	return rect; }

inline CGRectF CGRectF::operator-( const GPSize& rSize ) const {
	CGRectF rect( *this );
	rect -= rSize;
	return rect; }

inline CGRectF CGRectF::operator&( const RectF& rRect ) const {
	CGRectF rect( *this );
	rect &= rRect;
	return rect; }

inline CGRectF CGRectF::operator&( const Rect& rRect ) const {
	CGRectF rect( *this );
	rect &= rRect;
	return rect; }

inline CGRectF CGRectF::operator|( const RectF& rRect ) const {
	CGRectF rect( *this );
	rect |= rRect;
	return rect; }

inline CGRectF CGRectF::operator|( const Rect& rRect ) const {
	CGRectF rect( *this );
	rect |= rRect;
	return rect; }
#endif //_GDIPLUS_H

#endif //!___G_RECT_F_INL__PH___