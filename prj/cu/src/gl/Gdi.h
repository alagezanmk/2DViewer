#ifndef ___GDI__PH___
#define ___GDI__PH___

#define BGR(r, g, b)					((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))|(((DWORD)(BYTE)(255))<<24))
#define ABGR(a, r, g, b)				((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))|(((DWORD)(BYTE)(a))<<24))
#define CrfRed( crf )					DWORD(crf & 0xFF)
#define CrfGreen( crf )					DWORD((crf >> 8) & 0xFF)
#define CrfBlue( crf )					DWORD((crf >> 16) & 0xFF)
#define CrfAlpha( crf )					DWORD((crf >> 24) & 0xFF)

CU_EXT_API void GetCrfBtnShades( COLORREF crf, COLORREF* pcrfShadow, COLORREF* pcrfHilite, INT nShadow = 150, INT nHilite = 80 );

extern CU_EXT_DATA CRect nullCRect;
#endif //___GDI__PH___
