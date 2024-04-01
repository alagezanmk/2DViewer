#ifndef ___G_RECT_INL__PH___
#define ___G_RECT_INL__PH___

////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
CU_EXT_API void CopyRect( GRect& rrcDst, const GRect& rrcSrc );
CU_EXT_API void CopyRect( GRect& rrcDst, const RECT& rrcSrc );
CU_EXT_API void CopyRect( GRect& rrcDst, const Rect& rrcSrc );
CU_EXT_API void CopyRect( GRect& rrcDst, const RectF& rrcSrc );

CU_EXT_API BOOL IsRectEmpty( const GRect& rRect );
CU_EXT_API BOOL IsRectEmpty( const Rect& rRect );

CU_EXT_API void SetRect( GRect& rRect, INT l, INT t, INT r, INT b );

CU_EXT_API BOOL PtInRect( const GRect& rRect, const GPoint& rpt );
CU_EXT_API BOOL PtInRect( const GRect& rRect, const POINT& rpt );
CU_EXT_API BOOL PtInRect( const GRect& rRect, const Point& rpt );

CU_EXT_API void SetRectEmpty( GRect& rRect );

CU_EXT_API BOOL EqualRect( const GRect& rRect1, const GRect& rRect2 );
CU_EXT_API BOOL EqualRect( const GRect& rRect1, const RECT& rRect2 );
CU_EXT_API BOOL EqualRect( const GRect& rRect1, const Rect& rRect2 );

CU_EXT_API void InflateRect( GRect& rRect, INT dx, INT dy );
CU_EXT_API void InflateRect( GRect& rRect, INT l, INT t, INT r, INT b );
CU_EXT_API void OffsetRect( GRect& rRect, INT dx, INT dy );

CU_EXT_API BOOL IntersectRect( GRect& rRect, const GRect& rRect1, const GRect& rRect2 );
CU_EXT_API BOOL IntersectRect( GRect& rRect, const GRect& rRect1, const RECT& rRect2 );
CU_EXT_API BOOL IntersectRect( GRect& rRect, const GRect& rRect1, const Rect& rRect2 );
CU_EXT_API BOOL IntersectRect( GRect& rRect, const RECT& rRect1, const RECT& rRect2 );
CU_EXT_API BOOL IntersectRect( GRect& rRect, const Rect& rRect1, const Rect& rRect2 );

CU_EXT_API BOOL UnionRect( GRect& rRect, const GRect& rRect1, const GRect& rRect2 );
CU_EXT_API BOOL UnionRect( GRect& rRect, const GRect& rRect1, const RECT& rRect2 );
CU_EXT_API BOOL UnionRect( GRect& rRect, const GRect& rRect1, const Rect& rRect2 );
CU_EXT_API BOOL UnionRect( GRect& rRect, const RECT& rRect1, const RECT& rRect2 );
CU_EXT_API BOOL UnionRect( GRect& rRect, const Rect& rRect1, const Rect& rRect2 );

CU_EXT_API BOOL SubtractRect( GRect& rRect, const GRect& rRect1, const GRect& rRect2 );
CU_EXT_API BOOL SubtractRect( GRect& rRect, const GRect& rRect1, const RECT& rRect2 );
CU_EXT_API BOOL SubtractRect( GRect& rRect, const GRect& rRect1, const Rect& rRect2 );
CU_EXT_API BOOL SubtractRect( GRect& rRect, const RECT& rRect1, const RECT& rRect2 );
CU_EXT_API BOOL SubtractRect( GRect& rRect, const Rect& rRect1, const Rect& rRect2 );

////////////////////////////////////////////////////////////////////////////////////////////////////
inline GRect::GRect() {
	/* random filled */ }

inline GRect::GRect( int l, int t, int r, int b ) {
	left = l; top = t; right = r; bottom = b; }

inline GRect::GRect( const GRect& rRect) {
 ::CopyRect( *this, rRect ); }

inline GRect::GRect( const GPoint& rTopLeft, const GSize& rSize ) {
	right = (left = rTopLeft.x) + rSize.cx; bottom = (top = rTopLeft.y) + rSize.cy; }

inline GRect::GRect( const GPoint& rTopLeft, const GPoint& rBottomRight ) {
	left = rTopLeft.x; top = rTopLeft.y;
	right = rBottomRight.x; bottom = rBottomRight.y; }

inline int GRect::Width() const {
	return right - left; }

inline int GRect::Height() const {
	return bottom - top; }

inline GSize GRect::GetSize() const {
	return GSize( right - left, bottom - top ); }

inline GPoint& GRect::TopLeft() {
	return *((GPoint*)this); }

inline GPoint& GRect::BottomRight() {
	return *((GPoint*)this + 1); }

inline const GPoint& GRect::TopLeft() const {
	return *((GPoint*)this); }

inline const GPoint& GRect::BottomRight() const {
	return *((GPoint*)this + 1); }

inline GPoint GRect::CenterPoint() const {
	return GPoint( (left + right) / 2, (top + bottom ) / 2); }

inline void GRect::SwapLeftRight() {
	SwapLeftRight( *((GRect*)this) ); }

inline void GRect::SwapLeftRight( GRect& rRect ) {
	LONG temp = rRect.left; rRect.left = rRect.right; rRect.right = temp; }

inline GRect::operator GRect*() {
	return this; }

inline GRect::operator const GRect*() const {
	return this; }

inline BOOL GRect::IsRectEmpty() const {
	return ::IsRectEmpty( *this ); }

inline BOOL GRect::IsRectNull() const {
	return ( left == 0 && right == 0 && top == 0 && bottom == 0 ); }

inline BOOL GRect::PtInRect( const GPoint& rpt ) const {
	return ::PtInRect( *this, rpt ); }

inline void GRect::SetRect( int x1, int y1, int x2, int y2 ) {
	::SetRect( *this, x1, y1, x2, y2 ); }

inline void GRect::SetRect( const GPoint& rTopLeft, const GPoint& rBottomRight ) {
	::SetRect( *this, rTopLeft.x, rTopLeft.y, rBottomRight.x, rBottomRight.y ); }

inline void GRect::SetRectEmpty() {
	::SetRectEmpty( *this ); }

inline void GRect::CopyRect( const GRect& rSrcRect ) {
	::CopyRect( *this, rSrcRect); }

inline BOOL GRect::EqualRect( const GRect& rRect ) const {
	return ::EqualRect( *this, rRect ); }

inline void GRect::InflateRect( int x, int y ) {
	::InflateRect( *this, x, y ); }

inline void GRect::InflateRect( INT l, INT t, INT r, INT b ) {
	left -= l; top -= t; right += r; bottom += b; }

inline void GRect::InflateRect( const GPoint& rpt ) {
	::InflateRect( *this, rpt.x, rpt.y ); }

inline void GRect::InflateRect( const GSize& rSize ) {
	::InflateRect( *this, rSize.cx, rSize.cy ); }

inline void GRect::InflateRect( const GRect& rRect ) {
	InflateRect( rRect.left, rRect.top, rRect.right, rRect.bottom ); }

inline void GRect::DeflateRect( int x, int y ) {
	::InflateRect( *this, -x, -y); }

inline void GRect::DeflateRect( const GSize& rSize ) {
	::InflateRect( *this, -rSize.cx, -rSize.cy ); }

inline void GRect::OffsetRect( int x, int y) {
	::OffsetRect( *this, x, y ); }

inline void GRect::OffsetRect( const GPoint& rpt ) {
	::OffsetRect( *this, rpt.x, rpt.y ); }

inline void GRect::OffsetRect( const GSize& rSize ) {
	::OffsetRect( *this, rSize.cx, rSize.cy ); }

inline BOOL GRect::IntersectRect( const GRect& rRect1, const GRect& rRect2 ) {
	return ::IntersectRect( *this, rRect1, rRect2 );}

inline BOOL GRect::UnionRect( const GRect& rRect1, const GRect& rRect2 ) {
	return ::UnionRect( *this, rRect1, rRect2 ); }

inline void GRect::operator=( const GRect& rsrcRect ) {
	::CopyRect( *this, rsrcRect ); }

inline BOOL GRect::operator==( const GRect& rRect ) const {
	return ::EqualRect( *this, rRect ); }

inline BOOL GRect::operator!=( const GRect& rRect ) const {
	return !::EqualRect( *this, rRect ); }

inline void GRect::operator+=( const GPoint& rpt ) {
	::OffsetRect( *this, rpt.x, rpt.y ); }

inline void GRect::operator+=( const GSize& rSize ) {
	::OffsetRect( *this, rSize.cx, rSize.cy ); }

inline void GRect::operator+=( const GRect& rRect ) {
	InflateRect( rRect ); }

inline void GRect::operator-=( const GPoint& rpt ) {
	::OffsetRect( *this, -rpt.x, -rpt.y ); }

inline void GRect::operator-=( const GSize& rSize ) {
	::OffsetRect( *this, -rSize.cx, -rSize.cy ); }

inline void GRect::operator-=( const GRect& rRect ) {
	DeflateRect( rRect ); }

inline void GRect::operator&=( const GRect& rRect ) {
	::IntersectRect( *this, *this, rRect ); }

inline void GRect::operator|=( const GRect& rRect ) {
	::UnionRect( *this, *this, rRect ); }

inline GRect GRect::operator+( const GPoint& pt ) const {
	GRect rect( *this ); 
	::OffsetRect( rect, pt.x, pt.y ); 
	return rect; }

inline GRect GRect::operator-( const GPoint& pt ) const {
	GRect rect( *this ); 
	::OffsetRect( rect, -pt.x, -pt.y ); 
	return rect; }

inline GRect GRect::operator+( const GSize& rSize ) const {
	GRect rect( *this ); 
	::OffsetRect( rect, rSize.cx, rSize.cy ); 
	return rect; }

inline GRect GRect::operator-( const GSize& rSize ) const {
	GRect rect(*this); 
	::OffsetRect( rect, -rSize.cx, -rSize.cy ); 
	return rect; }

inline GRect GRect::operator+( const GRect& rRect ) const {
	GRect rect( *this ); rect.InflateRect( rRect ); 
	return rect; }

inline GRect GRect::operator-( const GRect& rRect ) const {
	GRect rect( *this ); rect.DeflateRect( rRect ); 
	return rect; }

inline GRect GRect::operator&( const GRect& rRect ) const {
	GRect rect; ::IntersectRect( rect, *this, rRect );
	return rect; }

inline GRect GRect::operator|( const GRect& rRect ) const {
	GRect rect; ::UnionRect( rect, *this, rRect );
	return rect; }

inline BOOL GRect::SubtractRect( const GRect& rRectSrc1, const GRect& rRectSrc2 ) {
	return ::SubtractRect( *this, rRectSrc1, rRectSrc2 ); }

////////////////////////////////////////////////////////////////////////////////////////////////////
inline CGRect::CGRect() {
	/* random filled */ }

inline CGRect::CGRect( const RECT& rRect ) {
	::CopyRect( *this, rRect ); }

inline CGRect::CGRect( const Rect& rRect ) {
	::CopyRect( *this, rRect ); }

inline CGRect::CGRect( const POINT& rTopLeft, const SIZE& rSize ) {
	right = (left = rTopLeft.x) + rSize.cx; bottom = (top = rTopLeft.y) + rSize.cy; }

inline CGRect::CGRect( const POINT& rTopLeft, const Size& rSize ) {
	right = (left = rTopLeft.x) + rSize.Width; bottom = (top = rTopLeft.y) + rSize.Height; }

inline CGRect::CGRect( const Point& rTopLeft, const SIZE& rSize ) {
	right = (left = rTopLeft.X) + rSize.cx; bottom = (top = rTopLeft.Y) + rSize.cy; }

inline CGRect::CGRect( const Point& rTopLeft, const Size& rSize ) {
	right = (left = rTopLeft.X) + rSize.Width; bottom = (top = rTopLeft.Y) + rSize.Height; }

inline CGRect::CGRect( const POINT& rTopLeft, const POINT& rBottomRight ) {
	left = rTopLeft.x; top = rTopLeft.y;
	right = rBottomRight.x; bottom = rBottomRight.y; }

inline CGRect::CGRect( const Point& rTopLeft, const Point& rBottomRight ) {
	left = rTopLeft.X; top = rTopLeft.Y;
	right = rBottomRight.X; bottom = rBottomRight.Y; }

inline CGRect::operator RECT*() {
	return (RECT*)this; }

inline CGRect::operator const RECT*() const {
	return (const RECT*)this; }

inline BOOL CGRect::PtInRect( const POINT& rpt ) const {
	return ::PtInRect( *this, rpt ); }

inline BOOL CGRect::PtInRect( const Point& rpt ) const {
	return ::PtInRect( *this, rpt ); }

inline void CGRect::SetRect( const POINT& rTopLeft, const POINT& rBottomRight ) {
	::SetRect( *this, rTopLeft.x, rTopLeft.y, rBottomRight.x, rBottomRight.y ); }

inline void CGRect::SetRect( const Point& rTopLeft, const Point& rBottomRight ) {
	::SetRect( *this, rTopLeft.X, rTopLeft.Y, rBottomRight.X, rBottomRight.Y ); }

inline void CGRect::CopyRect( const RECT& rSrcRect ) {
	::CopyRect( *this, rSrcRect); }

inline void CGRect::CopyRect( const Rect& rSrcRect ) {
	::CopyRect( *this, rSrcRect); }

inline BOOL CGRect::EqualRect( const RECT& rRect ) const {
	return ::EqualRect( *this, rRect ); }

inline BOOL CGRect::EqualRect( const Rect& rRect ) const {
	return ::EqualRect( *this, rRect ); }

inline void CGRect::InflateRect( const POINT& rpt ) {
	::InflateRect( *this, rpt.x, rpt.y ); }

inline void CGRect::InflateRect( const Point& rpt ) {
	::InflateRect( *this, rpt.X, rpt.Y ); }

inline void CGRect::InflateRect( const SIZE& rSize ) {
	::InflateRect( *this, rSize.cx, rSize.cy ); }

inline void CGRect::InflateRect( const Size& rSize ) {
	::InflateRect( *this, rSize.Height, rSize.Height ); }

inline void CGRect::InflateRect( const RECT& rRect ) {
	::InflateRect( *this, rRect.left, rRect.top, rRect.right, rRect.bottom ); }

inline void CGRect::DeflateRect( const POINT& rpt ) {
	::InflateRect( *this, -rpt.x, -rpt.y ); }

inline void CGRect::DeflateRect( const Point& rpt ) {
	::InflateRect( *this, -rpt.X, -rpt.Y ); }

inline void CGRect::DeflateRect( const SIZE& rSize ) {
	::InflateRect( *this, -rSize.cx, -rSize.cy ); }

inline void CGRect::DeflateRect( const Size& rSize ) {
	::InflateRect( *this, -rSize.Height, -rSize.Height ); }

inline void CGRect::DeflateRect( const RECT& rRect ) {
	::InflateRect( *this, -rRect.left, -rRect.top, -rRect.right, -rRect.bottom ); }

inline void CGRect::OffsetRect( const POINT& rpt ) {
	::OffsetRect( *this, rpt.x, rpt.y ); }

inline void CGRect::OffsetRect( const Point& rpt ) {
	::OffsetRect( *this, rpt.X, rpt.Y ); }

inline void CGRect::OffsetRect( const SIZE& rSize ) {
	::OffsetRect( *this, rSize.cx, rSize.cy ); }

inline void CGRect::OffsetRect( const Size& rSize ) {
	::OffsetRect( *this, rSize.Width, rSize.Height ); }

inline BOOL CGRect::IntersectRect( const RECT& rRect1, const RECT& rRect2 ) {
	return ::IntersectRect( *this, rRect1, rRect2 );}

inline BOOL CGRect::IntersectRect( const Rect& rRect1, const Rect& rRect2 ) {
	return ::IntersectRect( *this, rRect1, rRect2 );}

inline BOOL CGRect::UnionRect( const RECT& rRect1, const RECT& rRect2 ) {
	return ::UnionRect( *this, rRect1, rRect2 );}

inline BOOL CGRect::UnionRect( const Rect& rRect1, const Rect& rRect2 ) {
	return ::UnionRect( *this, rRect1, rRect2 );}

inline BOOL CGRect::SubtractRect( const RECT& rRect1, const RECT& rRect2 ) {
	return ::SubtractRect( *this, rRect1, rRect2 );}

inline BOOL CGRect::SubtractRect( const Rect& rRect1, const Rect& rRect2 ) {
	return ::SubtractRect( *this, rRect1, rRect2 );}

inline void CGRect::operator=( const RECT& rsrcRect ) {
	::CopyRect( *this, rsrcRect ); }

inline void CGRect::operator=( const Rect& rsrcRect ) {
	::CopyRect( *this, rsrcRect ); }

inline BOOL CGRect::operator==( const RECT& rRect ) const {
	return ::EqualRect( *this, rRect ); }

inline BOOL CGRect::operator==( const Rect& rRect ) const {
	return ::EqualRect( *this, rRect ); }

inline BOOL CGRect::operator!=( const RECT& rRect ) const {
	return !::EqualRect( *this, rRect ); }

inline BOOL CGRect::operator!=( const Rect& rRect ) const {
	return !::EqualRect( *this, rRect ); }

inline void CGRect::operator+=( const POINT& rpt ) {
	::OffsetRect( *this, rpt.x, rpt.y ); }

inline void CGRect::operator+=( const Point& rpt ) {
	::OffsetRect( *this, rpt.X, rpt.Y ); }

inline void CGRect::operator+=( const SIZE& rSize ) {
	::OffsetRect( *this, rSize.cx, rSize.cy ); }

inline void CGRect::operator+=( const Size& rSize ) {
	::OffsetRect( *this, rSize.Width, rSize.Height ); }

inline void CGRect::operator+=( const RECT& rRect ) {
	InflateRect( rRect ); }

inline void CGRect::operator-=( const POINT& rpt ) {
	::OffsetRect( *this, -rpt.x, -rpt.y ); }

inline void CGRect::operator-=( const Point& rpt ) {
	::OffsetRect( *this, -rpt.X, -rpt.Y ); }

inline void CGRect::operator-=( const SIZE& rSize ) {
	::OffsetRect( *this, -rSize.cx, -rSize.cy ); }

inline void CGRect::operator-=( const Size& rSize ) {
	::OffsetRect( *this, -rSize.Width, -rSize.Height ); }

inline void CGRect::operator-=( const RECT& rRect ) {
	DeflateRect( rRect ); }

inline void CGRect::operator&=( const RECT& rRect ) {
	::IntersectRect( *this, *this, rRect ); }

inline void CGRect::operator&=( const Rect& rRect ) {
	::IntersectRect( *this, *this, rRect ); }

inline void CGRect::operator|=( const RECT& rRect ) {
	::UnionRect( *this, *this, rRect ); }

inline void CGRect::operator|=( const Rect& rRect ) {
	::UnionRect( *this, *this, rRect ); }

inline CGRect CGRect::operator+( const POINT& pt ) const {
	CGRect rect( *this ); 
	::OffsetRect( rect, pt.x, pt.y ); 
	return rect; }

inline CGRect CGRect::operator+( const Point& pt ) const {
	CGRect rect( *this ); 
	::OffsetRect( rect, pt.X, pt.Y ); 
	return rect; }

inline CGRect CGRect::operator+( const SIZE& rSize ) const {
	CGRect rect( *this ); 
	::OffsetRect( rect, rSize.cx, rSize.cy ); 
	return rect; }

inline CGRect CGRect::operator+( const Size& rSize ) const {
	CGRect rect( *this ); 
	::OffsetRect( rect, rSize.Width, rSize.Height ); 
	return rect; }

inline CGRect CGRect::operator+( const RECT& rRect ) const {
	CGRect rect( *this ); rect.InflateRect( rRect ); 
	return rect; }

inline CGRect CGRect::operator-( const POINT& pt ) const {
	CGRect rect( *this ); 
	::OffsetRect( rect, pt.x, pt.y ); 
	return rect; }

inline CGRect CGRect::operator-( const Point& pt ) const {
	CGRect rect( *this ); 
	::OffsetRect( rect, -pt.X, -pt.Y ); 
	return rect; }

inline CGRect CGRect::operator-( const SIZE& rSize ) const {
	CGRect rect( *this ); 
	::OffsetRect( rect, -rSize.cx, -rSize.cy ); 
	return rect; }

inline CGRect CGRect::operator-( const Size& rSize ) const {
	CGRect rect( *this ); 
	::OffsetRect( rect, -rSize.Width, -rSize.Height ); 
	return rect; }

inline CGRect CGRect::operator-( const RECT& rRect ) const {
	CGRect rect( *this ); rect.DeflateRect( rRect ); 
	return rect; }

inline CGRect CGRect::operator&( const RECT& rRect ) const {
	CGRect rect; ::IntersectRect( rect, *this, rRect );
	return rect; }

inline CGRect CGRect::operator&( const Rect& rRect ) const {
	CGRect rect; ::IntersectRect( rect, *this, rRect );
	return rect; }

inline CGRect CGRect::operator|( const RECT& rRect ) const {
	CGRect rect; ::UnionRect( rect, *this, rRect );
	return rect; }

inline CGRect CGRect::operator|( const Rect& rRect ) const {
	CGRect rect; ::UnionRect( rect, *this, rRect );
	return rect; }
#endif //0

#endif //!___G_RECT_INL__PH___