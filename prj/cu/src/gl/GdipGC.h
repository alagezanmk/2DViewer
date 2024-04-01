#ifndef ___GDIP_GC__PH___
#define ___GDIP_GC__PH___

#include <gl\gl.h>
#include "WinGC.h"

class CGdipGCCreator : public CGCCreator
{
public:
	CGdipGCCreator();

public:
	virtual CGC* Create( HGD hGD );
	virtual CGC* Create( HWIN hWin, INT nGCType = CGL::enGCTypeClient );
};

class CGdipGC : public CGC
{
public:
	CGdipGC();
	CGdipGC( HGD hGD );
	CGdipGC( HWIN hWin, INT nGCType = CGL::enGCTypeClient );
	virtual ~CGdipGC();

public:
	virtual BOOL DrawPolygon( GPointF* pPoint, INT nCount );

public:
	HDC				m_hDC;
	HWND			m_hWnd;
	PAINTSTRUCT		m_ps;
	Graphics*		m_pG;
};

#endif //!___GDIP_GC__PH___