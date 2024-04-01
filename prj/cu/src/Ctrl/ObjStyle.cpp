#include "stdafx.h"
//#include "Obj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// CObjBrush class
CObjBrush::CObjBrush( const CObj* pObj )
 : CStyleBrush()
{
	ASSERT( pObj && pObj->m_psObj );
	FLOAT fOpactiy = pObj->GetOpacity();
	Create( pObj->m_psObj->FillStyle, fOpactiy, pObj->m_rbg );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// CObjPen class
CObjPen::CObjPen( const CObj* pObj )
 : CStylePen()
{
	ASSERT( pObj && pObj->m_psObj );
	FLOAT fOpactiy = pObj->GetOpacity();
	Create( pObj->m_psObj->StrokeStyle, fOpactiy, pObj->m_rbg );
}
