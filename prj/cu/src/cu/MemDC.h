#ifndef ___MEM_DC__PH___
#define ___MEM_DC__PH___

/// The class CMemDC is derived from CDC. It can be used as Memory Device Context(DC). 
/// It encapsulates the functions of creating DC and Bitmap which is need for Memory DC.
class CU_EXT_CLASS CMemDC : public CDC
{
public:
	CMemDC();
	virtual ~CMemDC();

	/// Creates Memory DC for given width and height
	BOOL Create( CDC* pDC, INT nWidth, INT nHeight );

	///////////////////////////////////////////////////////////////////////////////////////////////
	/// Bit Blt Paint function
	/// Copy image from the given DC - pDC to this DC
	void BitBlt( CDC* pDC );

	/// Copy image from the given DC - pDC to this DC with the specified dimension
	void BitBlt( INT x, INT y, INT nWidth, INT nHeight, 
				 CDC* pDC, INT nSrcX = 0, INT nSrcY = 0, INT nROP = SRCCOPY );

	/// Copy image from this DC to the given DC - pDC
	void BitBltTo( CDC* pDC );

	/// Copy image from this DC to the given DC - pDC with the specified dimension
	void BitBltTo( CDC* pDC, INT x, INT y, INT nWidth, INT nHeight, 
				   INT nSrcX = 0, INT nSrcY = 0, INT nROP = SRCCOPY );

protected:
	HBITMAP		m_hBmp;
	HBITMAP		m_hOldBmp;
};

inline void CMemDC::BitBlt( CDC* pDC ) {
	BITMAP sBmp;
	GetObject( m_hBmp, sizeof(sBmp), &sBmp );
	BitBlt( 0, 0, sBmp.bmWidth, sBmp.bmHeight, pDC, 0, 0, SRCCOPY ); }

inline void CMemDC::BitBlt( INT x, INT y, INT nWidth, INT nHeight, CDC* pDC, INT nSrcX /*= 0*/, INT nSrcY /*= 0*/, INT nROP /*= SRCCOPY*/ ) {
	CDC::BitBlt( x, y, nWidth, nHeight, pDC, nSrcX, nSrcY, nROP ); }

inline void CMemDC::BitBltTo( CDC* pDC ) {
	BITMAP sBmp;
	GetObject( m_hBmp, sizeof(sBmp), &sBmp );
	pDC->BitBlt( 0, 0, sBmp.bmWidth, sBmp.bmHeight, this, 0, 0, SRCCOPY ); }

inline void CMemDC::BitBltTo( CDC* pDC, INT x, INT y, INT nWidth, INT nHeight, INT nSrcX /*= 0*/, INT nSrcY /*= 0*/, INT nROP /*= SRCCOPY*/ ) {
	pDC->BitBlt( x, y, nWidth, nHeight, this, nSrcX, nSrcY, nROP ); }

#endif  ___MEM_DC__PH___
