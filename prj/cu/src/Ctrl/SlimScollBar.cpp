#include "stdafx.h"
#include "SlimScollBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CSlimScollBar, CScrollBar)
	//{{AFX_MSG_MAP(CSlimScollBar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSlimScollBar::CSlimScollBar()
{
	m_bSlim = TRUE;
}

CSlimScollBar::~CSlimScollBar()
{}

void CSlimScollBar::OnPaint()
{
	if( FALSE == m_bSlim )
	{
		Default();
		return;
	}

	Default();
	//ValidateRect( NULL );
}