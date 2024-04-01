#ifndef __ALX__PH___
#define __ALX__PH___

struct CU_EXT_CLASS SALX
{
	CString			cszAppDir;
	HINSTANCE		hAppInst;
	CWinApp*		pApp;

	CMDIFrameWnd*	pMainFrm;

	COLORREF		crfAppWks;
	COLORREF		crfWindow;

	COLORREF		crfBtnFace;

	COLORREF		crfHilite;
	COLORREF		crfShadow;

	COLORREF		crf3DHilite;
	COLORREF		crf3DShadow;

	HBRUSH			hbrAppWks;
	HBRUSH			hbrWindow;
	HBRUSH			hbrBtnFace;
	HBRUSH			hbr3DShadow;
	HBRUSH			hbr3DHilight;
	HBRUSH			hbr3DDkShadow;
	HBRUSH			hbr3DDkHilight;
};

extern CU_EXT_DATA SALX	g_alx;

#endif  __ALX__PH___
