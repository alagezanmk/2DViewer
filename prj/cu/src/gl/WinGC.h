#ifndef ___WIN_GC__PH___
#define ___WIN_GC__PH___

#include <gl\gl.h>

CU_EXT_API void InitGC();
CU_EXT_API void ReleaseGC();

class CWinGC;
class CWinGCCreator : public CGCCreator
{
public:
	CWinGCCreator();

public:
	virtual CGC* Create( HGD hGD );
	virtual CGC* Create( HWIN hWin, INT nGCType = CGL::enGCTypeClient );
};

class CWinGC : public CGC
{
public:
	CWinGC();
	CWinGC( HGD hGD );
	CWinGC( HWIN hWin, INT nGCType = CGL::enGCTypeClient );
	virtual ~CWinGC();

public:
	virtual BOOL DrawPolygon( GPointF* pPoint, INT nCount );

public:
	HDC				m_hDC;
	HWND			m_hWnd;
	PAINTSTRUCT		m_ps;
};

#endif //!___WIN_GC__PH___