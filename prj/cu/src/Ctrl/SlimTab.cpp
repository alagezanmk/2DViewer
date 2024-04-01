#include "stdafx.h"
#include "SlimTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const INT g_nTabSlant	= 13;				// Slant of Tab
const INT g_nTabMrgn	= 2;				// Margin For Text	
const INT g_nBtnW		= g_nTabSlant + 1;	// Button Width
const INT g_nBtnH		= g_nTabSlant + 1;	// Button Height
const INT g_nCPtr		= 4;				// Size for Btn Ptr
const INT gc_nSizeBar	= 5;
#define _TAB_FONT		_T("Arial")

const INT g_cnTabOffset[4][3][2] =
{
	{ {  g_nTabSlant,  g_nTabSlant }, { 1, 0 }, {  g_nTabSlant, -g_nTabSlant } },		// Bottom 
	{ {  g_nTabSlant, -g_nTabSlant }, { 1, 0 }, {  g_nTabSlant,  g_nTabSlant } },		// Top
	{ { -g_nTabSlant, -g_nTabSlant }, { 0, -1 }, {  g_nTabSlant, -g_nTabSlant } },		// Left
	{ {  g_nTabSlant, -g_nTabSlant }, { 0, -1 }, { -g_nTabSlant, -g_nTabSlant } }		// Right
};

BEGIN_MESSAGE_MAP(CSlimTab, CWnd)
	//{{AFX_MSG_MAP(CSlimTab)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_NCHITTEST()
	ON_WM_RBUTTONUP()
	ON_COMMAND( 100 + 4, OnRename )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSlimTab::CSlimTab()
{
	m_nTabSize = 30;
	m_nCurTab  = 0;
	m_nVisible = 0;
	m_hMsg   = NULL;
	m_nMouseOver = ST_MOUSENONE;
	m_bLeft	 = FALSE;
	m_bRight = FALSE;
	m_nTabStyle = ST_HORIZONTAL_TABDOWN;
	m_bScrollBtnSide = TRUE;

	m_nClicked = -1;
}

CSlimTab::~CSlimTab()
{}

BOOL CSlimTab::Create( CWnd *pParent, CRect *prctWnd, INT nID )
{
	return CWnd::Create( NULL, NULL, WS_CHILD, *prctWnd, pParent, nID, NULL );
}

void CSlimTab::OnPaint() 
{
	CPaintDC	dc(this); // device context for painting
	CDC*		pDC = &dc;
	PSSlimTab	psTab;
	CRgn		rgnFill;
	CFont		fntTab, *pfntOld;
	INT			nFontAngle;
	INT			nFontSize;
	CRect		rctClient, rcText;
	INT			nCount;
	COLORREF	crfHilite = GetSysColor( COLOR_3DHILIGHT );
	COLORREF	crfShadow = GetSysColor( COLOR_3DSHADOW );
	crfHilite = crfShadow;
	
	GetClientRect( rctClient );
	INT nCCx = rctClient.Width();
	INT nCCy = rctClient.Height();

	CDC		MemDC;
	CBitmap MemBm;

	MemDC.CreateCompatibleDC( &dc );
	MemBm.CreateCompatibleBitmap( &dc, nCCx, nCCy );
	CBitmap* pMemOld = MemDC.SelectObject( &MemBm );
	pDC = &MemDC;

	nCCx -= gc_nSizeBar;

	HBRUSH hbrBtnFace = GetSysColorBrush( COLOR_BTNFACE );
	HBRUSH hbrBtn = GetSysColorBrush( COLOR_WINDOW );
	
	FillRect( pDC->m_hDC, rctClient, hbrBtnFace );
	pDC->SetBkMode( TRANSPARENT );
	switch( m_nTabStyle )
	{
	case ST_HORIZONTAL_TABDOWN:
	case ST_HORIZONTAL_TABUP:
		nFontAngle = 0;
		nFontSize = 14;
		break;

	case ST_VERTICAL_TABLEFT:
		nFontAngle = 90 * 10;
		nFontSize = 12;
		break;

	case ST_VERTICAL_TABRIGHT:
		nFontAngle = 270 * 10;
		nFontSize = 12;
		break;

	default:
		ASSERT( FALSE );
	}

	fntTab.CreateFont( nFontSize, 0, nFontAngle, nFontAngle, 0, 0, 0, 0, 0, 0, 0, 0, 0, _TAB_FONT );
	ASSERT( fntTab.m_hObject );
	pfntOld = pDC->SelectObject( &fntTab);
	
	// Draw Tabs
	nCount = m_arSlimTab.GetSize();
	if( nCount )
	{
		PINT pnOffset = (PINT)g_cnTabOffset[m_nTabStyle];
		psTab = (PSSlimTab)m_arSlimTab.GetData();
		for( int i = 0; i < nCount; i++ )
		{
			pDC->BeginPath();
			DrawTab( pDC, pnOffset, &psTab[i] );
			pDC->EndPath();

			rgnFill.CreateFromPath( pDC);
			FillRgn( pDC->m_hDC, (HRGN)rgnFill.m_hObject, hbrBtn );
			rgnFill.DeleteObject();

			DrawTab( pDC, pnOffset, &psTab[i] );
			pDC->DrawText( psTab[i].cszText, psTab[i].rctText, DT_CENTER | DT_TOP | DT_SINGLELINE | DT_END_ELLIPSIS );
		}

		// Draw Outline
		switch( m_nTabStyle )
		{
		case ST_HORIZONTAL_TABDOWN:
			rctClient.bottom = rctClient.top;
			pDC->Draw3dRect( rctClient, crfShadow, crfShadow );
			break;

		case ST_HORIZONTAL_TABUP:
			rctClient.top = rctClient.bottom;
			pDC->Draw3dRect( rctClient, crfHilite, crfHilite );
			break;

		case ST_VERTICAL_TABLEFT:
			rctClient.left = rctClient.right;
			pDC->Draw3dRect( rctClient, crfHilite, crfHilite );
			break;

		case ST_VERTICAL_TABRIGHT:
			rctClient.right = rctClient.left;
			pDC->Draw3dRect( rctClient, crfShadow, crfShadow );
			break;

		default:
			ASSERT( FALSE);
		}

		// Draw The Current Tab
		pDC->BeginPath();
		DrawTab( pDC, pnOffset, &psTab[m_nCurTab] );
		pDC->EndPath();

		rgnFill.CreateFromPath( pDC );
		FillRgn( pDC->m_hDC, (HRGN)rgnFill.m_hObject, hbrBtn );

		DrawTab( pDC, pnOffset, &psTab[m_nCurTab] );
		pDC->DrawText( psTab[m_nCurTab].cszText, psTab[m_nCurTab].rctText, DT_CENTER | DT_TOP | DT_SINGLELINE | DT_END_ELLIPSIS );
	}

	pDC->SelectObject( &pfntOld );

	// Draw Button
	CRect		rctL, rctR;
	COLORREF	crfEnable	= RGB( 0, 0, 0 );
	COLORREF	crfDisable = GetSysColor( COLOR_3DSHADOW );

	rctL = GetScrollBtnRect( ST_BTN_LEFT );
	rctR = GetScrollBtnRect( ST_BTN_RIGHT );
	FillRect( pDC->m_hDC, rctL, hbrBtnFace );
	FillRect( pDC->m_hDC, rctR, hbrBtnFace );
	if( m_bLeft )
	{
		if( ST_MOUSEON_LEFT == m_nMouseOver )
		{
			pDC->Draw3dRect( rctL, crfHilite, crfShadow );
			DrawScrollBtn( pDC, crfEnable, ST_BTN_LEFT );
		}
		else if( ST_MOUSECLICK_LEFT == m_nMouseOver )
		{
			pDC->Draw3dRect( rctL, crfShadow, crfHilite );
			DrawScrollBtn( pDC, crfDisable, ST_BTN_LEFT );
		}
		else
			DrawScrollBtn( pDC, crfEnable, ST_BTN_LEFT );
	}
	else
		DrawScrollBtn( pDC, crfDisable, ST_BTN_LEFT );

	if( m_bRight )
	{
		if( ST_MOUSEON_RIGHT == m_nMouseOver )
		{
			pDC->Draw3dRect( rctR, crfHilite, crfShadow );
			DrawScrollBtn( pDC, crfEnable, ST_BTN_RIGHT );
		}
		else if( ST_MOUSECLICK_RIGHT == m_nMouseOver )
		{
			pDC->Draw3dRect( rctR, crfShadow, crfHilite );
			DrawScrollBtn( pDC, crfDisable, ST_BTN_RIGHT );
		}
		else
			DrawScrollBtn( pDC, crfEnable, ST_BTN_RIGHT );
	}
	else
		DrawScrollBtn( pDC, crfDisable, ST_BTN_RIGHT );

	nCCx += gc_nSizeBar;
	rctClient.SetRect( 0, 0, nCCx, nCCy );
	rctClient.left = rctClient.right - gc_nSizeBar;
	crfHilite = GetSysColor( COLOR_3DHILIGHT );
	FillRect( pDC->m_hDC, rctClient, hbrBtnFace );
	pDC->Draw3dRect( rctClient, crfHilite, crfShadow );

	dc.BitBlt( 0, 0, nCCx, nCCy, &MemDC, 0, 0, SRCCOPY );
	MemDC.SelectObject( pMemOld );
}

// Draw single Tab 
void CSlimTab::DrawTab( CDC* pDC, PINT pnOffset, PSSlimTab psTab )
{
	INT			x, y;
	CPen		PnLight, PnShadow, *pPnOld;
	COLORREF	crfHilite = GetSysColor( COLOR_3DHILIGHT );
	COLORREF	crfShadow = GetSysColor( COLOR_3DSHADOW );
	crfHilite = crfShadow;
	crfShadow = 0;

	PnLight.CreatePen( PS_SOLID, 1, crfHilite );
	PnShadow.CreatePen( PS_SOLID, 1, crfShadow );
	ASSERT( PnLight.m_hObject && PnShadow.m_hObject );

	switch( m_nTabStyle )
	{
	case ST_HORIZONTAL_TABDOWN:
	case ST_HORIZONTAL_TABUP:
		pPnOld = pDC->SelectObject( &PnLight );
		break;

	case ST_VERTICAL_TABLEFT:
	case ST_VERTICAL_TABRIGHT:
		pPnOld = pDC->SelectObject( &PnShadow );
		break;
	default:
		ASSERT( FALSE);
	}

	x = psTab->x;
	y = psTab->y;
	pDC->MoveTo( x, y );
	x += pnOffset[0];
	y += pnOffset[1];
	pDC->LineTo( x, y );
	switch( m_nTabStyle )
	{
	case ST_HORIZONTAL_TABUP:
	case ST_VERTICAL_TABLEFT:
		pDC->SelectObject( &PnLight );
		break;

	case ST_HORIZONTAL_TABDOWN:
	case ST_VERTICAL_TABRIGHT:
		pDC->SelectObject( &PnShadow );
		break;

	default:
		ASSERT( FALSE);
	}

	x += pnOffset[2] * (g_nTabMrgn * 2 + psTab->nTabSize); 
	y += pnOffset[3] * (g_nTabMrgn * 2 + psTab->nTabSize);
	pDC->LineTo( x, y );
	switch( m_nTabStyle )
	{
	case ST_HORIZONTAL_TABDOWN:
	case ST_HORIZONTAL_TABUP:
		pDC->SelectObject( &PnShadow );
		break;

	case ST_VERTICAL_TABLEFT:
	case ST_VERTICAL_TABRIGHT:
		pDC->SelectObject( &PnLight );
		break;

	default:
		ASSERT( FALSE);
	}

	x += pnOffset[4]; 
	y += pnOffset[5];
	pDC->LineTo( x, y );
	pDC->SelectObject( pPnOld );
}

void CSlimTab::DrawScrollBtn( CDC* pDC, COLORREF crfPtr, INT nBtn )
{
	CRect	rctLeft, rctRight;
	CPen	PnPtr, *pPnOld;
	CBrush	brPtr, *brOld;

	PnPtr.CreatePen( PS_SOLID, 1, crfPtr );
	brPtr.CreateSolidBrush( crfPtr);
	rctLeft	 = GetScrollBtnRect( ST_BTN_LEFT );
	rctRight = GetScrollBtnRect( ST_BTN_RIGHT );
	pPnOld	 = pDC->SelectObject( &PnPtr );
	brOld	 = pDC->SelectObject( &brPtr );
	switch( m_nTabStyle )
	{
	case ST_HORIZONTAL_TABDOWN:
	case ST_HORIZONTAL_TABUP:
		if( ST_BTN_LEFT == nBtn )
		{
			pDC->BeginPath();
			pDC->MoveTo( rctLeft.left + g_nCPtr, rctLeft.top + rctLeft.Height()/2  );
			pDC->LineTo( rctLeft.right - g_nCPtr, rctLeft.top + g_nCPtr );
			pDC->LineTo( rctLeft.right - g_nCPtr, rctLeft.bottom - g_nCPtr );
			pDC->LineTo( rctLeft.left + g_nCPtr, rctLeft.top + rctLeft.Height()/2  );
			pDC->EndPath();
			pDC->StrokeAndFillPath();
		}
		else if( ST_BTN_RIGHT == nBtn )
		{
			pDC->BeginPath();
			pDC->MoveTo( rctRight.right - g_nCPtr, rctRight.top + rctRight.Height()/2  );
			pDC->LineTo( rctRight.left + g_nCPtr, rctRight.top + g_nCPtr );
			pDC->LineTo( rctRight.left + g_nCPtr, rctRight.bottom - g_nCPtr );
			pDC->LineTo( rctRight.right - g_nCPtr, rctRight.top + rctRight.Height()/2  );
			pDC->EndPath();
			pDC->StrokeAndFillPath();
		}		
		break;

	case ST_VERTICAL_TABLEFT:
	case ST_VERTICAL_TABRIGHT:
		if( ST_BTN_LEFT == nBtn )
		{
			pDC->BeginPath();
			pDC->MoveTo( rctLeft.left +  rctLeft.Width()/2 , rctLeft.bottom - g_nCPtr  );
			pDC->LineTo( rctLeft.left + g_nCPtr, rctLeft.top	+ g_nCPtr );
			pDC->LineTo( rctLeft.right - g_nCPtr, rctLeft.top	+ g_nCPtr );
			pDC->LineTo( rctLeft.left +  rctLeft.Width()/2 , rctLeft.bottom - g_nCPtr  );
			pDC->EndPath();
			pDC->StrokeAndFillPath();
		}
		else if( ST_BTN_RIGHT == nBtn )
		{
			pDC->BeginPath();
			pDC->MoveTo( rctLeft.left +  rctLeft.Width()/2, rctRight.top + g_nCPtr  );
			pDC->LineTo( rctRight.left + g_nCPtr, rctRight.bottom - g_nCPtr );
			pDC->LineTo( rctRight.right - g_nCPtr, rctRight.bottom - g_nCPtr );
			pDC->LineTo( rctLeft.left +  rctLeft.Width()/2, rctRight.top + g_nCPtr );
			pDC->EndPath();
			pDC->StrokeAndFillPath();
		}		
		break;

	default:
		ASSERT( FALSE);
	}

	pDC->SelectObject( pPnOld );
	pDC->SelectObject( brOld );
}

void CSlimTab::SetMsgHandle( HWND hWnd )
{
	m_hMsg = hWnd;
}

void CSlimTab::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( m_arSlimTab.GetSize() <= 0 )
		return;

	if( FALSE == OnLButtonDown_Button( nFlags, point) )
		if( FALSE == OnLButtonDown_Tab( nFlags, point) )
			if( GetActiveWindow() != GetParent() )
				GetParent()->SetActiveWindow();
}

BOOL CSlimTab::OnLButtonDown_Button( UINT nFlags, CPoint point )
{
	CRect	rctLeft, rctRight;
	rctLeft	 = GetScrollBtnRect( ST_BTN_LEFT );
	rctRight = GetScrollBtnRect( ST_BTN_RIGHT );
	if( m_bLeft && rctLeft.PtInRect( point ))
	{
		m_nMouseOver = ST_MOUSECLICK_LEFT;
		InvalidateRect( rctLeft );
		InvalidateRect( rctRight );
		return TRUE;
	}
	else if( m_bRight && rctRight.PtInRect( point ))
	{
		m_nMouseOver = ST_MOUSECLICK_RIGHT;
		InvalidateRect( rctLeft );
		InvalidateRect( rctRight );
		return TRUE;
	}

	return FALSE;
}

BOOL CSlimTab::OnLButtonDown_Tab( UINT nFlags, CPoint point )
{
	PSSlimTab	psTab = (PSSlimTab)m_arSlimTab.GetData();
	INT			nCount = m_arSlimTab.GetSize();

	m_nMouseDown = -1;
	for( int i = m_nVisible; i < nCount; i++ )
	{
		if( psTab[i].rctText.PtInRect( point) )
		{
			m_nMouseDown = i;
			m_ptDown = point;
			SetCapture();
			return TRUE;
		}
	}

	return FALSE;
}

void CSlimTab::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( m_arSlimTab.GetSize() <= 0 )
		return;

	if( this == GetCapture() )
		ReleaseCapture();

	CRect rctLeft  = GetScrollBtnRect( ST_BTN_LEFT );
	CRect rctRight = GetScrollBtnRect( ST_BTN_RIGHT );

	// Check point is over the scroll button
	if( rctRight.PtInRect( point ) || rctLeft.PtInRect( point ) )
		OnLButtonUp_Button( nFlags,  point);
	else
		OnLButtonUp_Tab( nFlags,  point);
}

BOOL CSlimTab::OnLButtonUp_Button(UINT nFlags, CPoint point)
{
	CRect		rctLeft,rctRight;

	rctLeft	 = GetScrollBtnRect( ST_BTN_LEFT );
	rctRight = GetScrollBtnRect( ST_BTN_RIGHT );
	if( m_bLeft || m_bRight )
	{
		if( rctLeft.PtInRect( point ))
		{
			m_nMouseOver = ST_MOUSEON_LEFT;
			InvalidateRect( rctLeft );
			InvalidateRect( rctRight );
			if( m_bLeft )
			{
				if( ST_HORIZONTAL_TABDOWN == m_nTabStyle || ST_HORIZONTAL_TABUP == m_nTabStyle )
				{
					m_nStartX += g_nTabSlant +  g_nTabMrgn * 2 + m_arSlimTab[m_nVisible - 1].nTabSize;
					CalcTabPostion();
					if( 0 != m_nVisible )
						m_nVisible--;
					Invalidate();
				}
				if( ST_VERTICAL_TABLEFT == m_nTabStyle || ST_VERTICAL_TABRIGHT == m_nTabStyle )
				{
					m_nStartY -= g_nTabSlant +  g_nTabMrgn * 2 + m_arSlimTab[m_nVisible - 1].nTabSize;
					CalcTabPostion();
					if( 0 != m_nVisible )
						m_nVisible--;
					Invalidate();
				}
			}
		}
		else if( rctRight.PtInRect( point ))
		{
			m_nMouseOver = ST_MOUSEON_RIGHT;
			InvalidateRect( rctLeft );
			InvalidateRect( rctRight );
			if( m_bRight )
			{
				if( ST_HORIZONTAL_TABDOWN == m_nTabStyle || ST_HORIZONTAL_TABUP == m_nTabStyle )
				{
					m_nStartX -= g_nTabSlant +  g_nTabMrgn * 2 + m_arSlimTab[m_nVisible].nTabSize;
					CalcTabPostion();
					m_nVisible++;
					Invalidate();
				}
				if( ST_VERTICAL_TABLEFT == m_nTabStyle || ST_VERTICAL_TABRIGHT == m_nTabStyle )
				{
					m_nStartY += g_nTabSlant +  g_nTabMrgn * 2 + m_arSlimTab[m_nVisible].nTabSize;
					CalcTabPostion();
					m_nVisible++;
					Invalidate();
				}
			}
		}
		else if( ST_MOUSENONE != m_nMouseOver )
		{
			m_nMouseOver = ST_MOUSENONE; 
			InvalidateRect( rctLeft );
			InvalidateRect( rctRight );
		}
	}

	return FALSE;
}

BOOL CSlimTab::OnLButtonUp_Tab(UINT nFlags, CPoint point)
{
	PSSlimTab	psTab = (PSSlimTab)m_arSlimTab.GetData();
	INT			nCount = m_arSlimTab.GetSize();
	if( m_nMouseDown < 0 || m_nMouseDown >= nCount )
		return FALSE;

	for( int i = m_nVisible; i < nCount; i++ )
	{
		if( psTab[i].rctText.PtInRect( point) && m_nMouseDown == i )
		{
			m_nCurTab = i;
			if( m_hMsg )
				::SendMessage( m_hMsg, WM_USER + 1, i, 0 );

			Invalidate();
		}
	}
	return FALSE;
}

void CSlimTab::OnMouseMove( UINT nFlags, CPoint point ) 
{
	if( m_arSlimTab.GetSize() )
	{
		if( MK_LBUTTON & nFlags )
		{
			const INT gc_nDx = 8;
			const INT gc_nDy = 8;
			INT nDx = point.x - m_ptDown.x;
			INT nDy = point.y - m_ptDown.y;

			if( abs(nDx) > gc_nDx || abs(nDy) > gc_nDy )
				OnMouseMove_Tab( nFlags, point );
		}

		OnMouseMove_Button( nFlags, point );
	}
}

void CSlimTab::OnMouseMove_Button(UINT nFlags, CPoint point)
{
	CRect	rctLeft, rctRight;

	rctLeft	 = GetScrollBtnRect( ST_BTN_LEFT );
	rctRight = GetScrollBtnRect( ST_BTN_RIGHT );
	if( m_bLeft || m_bRight )
	{
		if( rctLeft.PtInRect( point ))
		{
			m_nMouseOver = ST_MOUSEON_LEFT;
			InvalidateRect( rctLeft, FALSE );
			InvalidateRect( rctRight, FALSE );
		}
		else if( rctRight.PtInRect( point ))
		{
			m_nMouseOver = ST_MOUSEON_RIGHT;
			InvalidateRect( rctLeft, FALSE );
			InvalidateRect( rctRight, FALSE );
		}
		else if( ST_MOUSENONE != m_nMouseOver )
		{
			m_nMouseOver = ST_MOUSENONE; 
			InvalidateRect( rctLeft, FALSE );
			InvalidateRect( rctRight, FALSE );
		}
	}
}

void CSlimTab::OnMouseMove_Tab( UINT nFlags, CPoint point )
{
	BOOL bDelete;
	if( m_nMouseDown < 0 || m_nMouseDown >= m_arSlimTab.GetSize() )
		return;

	LPARAM lParam = (LPARAM)(*(PINT)&m_ptDown);
	if( m_hMsg )
	{
		bDelete = ::SendMessage( m_hMsg, WM_USER + 2, m_nMouseDown, lParam );
		if( bDelete )
		{
			HWND hMainWnd = ::GetParent( m_hMsg );
			//?::PostMessage( hMainWnd, TCM_DELETE_FLOAT_TAB, 0, (LPARAM)m_hMsg );
		}
	}
}

int CSlimTab::OnCreate( LPCREATESTRUCT lpCreateStruct ) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitTab();
	CalcTabPostion();
	EnableToolTips();

	return 0;
}

BOOL CSlimTab::PreCreateWindow(CREATESTRUCT& cs) 
{
	if( !CWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style |= WS_CLIPSIBLINGS; 
	return TRUE;
}

int CSlimTab::OnToolHitTest( CPoint point, TOOLINFO* pTI ) const
{
	CSlimTab* pTab = (CSlimTab*)this;
	PSSlimTab psTab = (PSSlimTab)m_arSlimTab.GetData();
	INT nTab = pTab->GetTabAt( point );
	if( -1 != nTab && psTab[nTab].nCaptionSize < psTab[nTab].nTabSize )
		nTab = -1;

	if( -1 != nTab )
	{
		pTI->hwnd = m_hWnd;
		pTI->rect = psTab[nTab].rctText;
		pTI->uId = nTab;

		pTI->lpszText = new TCHAR[psTab[nTab].cszText.GetLength() + 1];
		lstrcpy( pTI->lpszText,	(LPCTSTR)psTab[nTab].cszText );
	}

	return nTab;
}

void CSlimTab::AddTab( PTCHAR pszTabName )
{
	SSlimTab	sTab;
	SIZE		cbSize;
	HFONT		hFont, hOldFont;
	HDC	hdc	= ::GetDC( ::GetDesktopWindow() );

	sTab.cszText = pszTabName;

	hFont	= CreateFont( 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _TAB_FONT );
	ASSERT( hFont );
	hOldFont = (HFONT)SelectObject( hdc, hFont );
	GetTextExtentPoint32( hdc, pszTabName, sTab.cszText.GetLength(), &cbSize );
	sTab.nTabSize = cbSize.cx;
	sTab.nCaptionSize = cbSize.cx;
	SelectObject( hdc, hOldFont );
	if( m_nTabSize )
	{
		sTab.nTabSize = m_nTabSize;
		//sTab.nCaptionSize = m_nTabSize;
	}

	m_arSlimTab.Add( sTab );
	::ReleaseDC( ::GetDesktopWindow(), hdc );
	CalcTabPostion();
	Invalidate();
}


void CSlimTab::RemoveAll()
{
	m_arSlimTab.RemoveAll();
	m_nMouseDown = 0;
	m_nMouseOver = 0;
	m_nStartX = 0;
	m_nStartY = 0;
	m_nCurTab = 0;
	m_bRight = FALSE;
	m_bLeft = FALSE;
	InvalidateRect( NULL, FALSE );
	InitTab();
}

void CSlimTab::RemoveTab( INT nTab )
{
	INT nCount = m_arSlimTab.GetSize();
	if( nTab < nCount )
	{
		m_arSlimTab.RemoveAt( nTab );
		nCount--;
		if( m_nCurTab > 0 )
			m_nCurTab--;

		if( nCount )
			::SendMessage( m_hMsg, WM_USER + 1, m_nCurTab, 0 );

		InitTab();
		CalcTabPostion();
		InvalidateRect( NULL, FALSE );
	}
}

void CSlimTab::CalcTabPostion()
{
	INT		  nVisible;
	INT		  nCount;
	CRect	  rctClient;
	PSSlimTab psTab;
	INT		  x, y, nTabMrgn;

	GetClientRect( rctClient );

	// Calc initial x, y of first tab
	switch( m_nTabStyle )
	{
	case ST_HORIZONTAL_TABDOWN:
		x = m_nStartX;
		y = rctClient.top;
		break;

	case ST_HORIZONTAL_TABUP:
		x = m_nStartX;
		y = rctClient.bottom;
		break;

	case ST_VERTICAL_TABLEFT:
		x = rctClient.right;
		y = m_nStartY;
		break;

	case ST_VERTICAL_TABRIGHT:
		x = 0;
		y = m_nStartY;
		break;

	default:
		ASSERT( FALSE);
	}

	// Calc position of each tab
	nCount  = m_arSlimTab.GetSize();
	psTab = (PSSlimTab)m_arSlimTab.GetData();
	nTabMrgn = g_nTabSlant + g_nTabMrgn * 2;
	if( ST_HORIZONTAL_TABDOWN == m_nTabStyle || ST_HORIZONTAL_TABUP == m_nTabStyle )
	{
		// Calc position of each tab
		for( int i = 0; i < nCount; i++ )
		{
			psTab[i].x = x;
			psTab[i].y = y;

			psTab[i].rctText.left = x + g_nTabSlant;
			psTab[i].rctText.top = y;
			psTab[i].rctText.right = psTab[i].rctText.left + psTab[i].nTabSize;
			psTab[i].rctText.bottom = psTab[i].rctText.top + rctClient.Height();
			x = psTab[i].nTabCx = x + nTabMrgn + psTab[i].nTabSize;
		}

		m_bLeft = m_bScrollBtnSide 
					?(m_nStartX < (rctClient.left + 2 * g_nBtnH))
					:(m_nStartX < rctClient.left);

		if( nCount )
			nVisible = m_bScrollBtnSide
							?psTab[nCount - 1].nTabCx
							:psTab[nCount - 1].nTabCx + g_nBtnW;
		m_bRight = (nVisible > rctClient.right);
	}

	if( ST_VERTICAL_TABLEFT == m_nTabStyle || ST_VERTICAL_TABRIGHT == m_nTabStyle )
	{
		// Calc position of each tab
		for( int i = 0; i < nCount; i++ )
		{
			psTab[i].x = x; 
			psTab[i].y = y;

			ASSERT( FALSE );
			psTab[i].rctText.left = x + g_nTabSlant;
			psTab[i].rctText.top = y;
			psTab[i].rctText.right = psTab[i].rctText.left + psTab[i].nTabSize;
			psTab[i].rctText.bottom = psTab[i].rctText.top + rctClient.Height();


			y = psTab[i].nTabCx = y - (nTabMrgn + psTab[i].nTabSize);
		}

		m_bLeft = m_bScrollBtnSide 
					?(m_nStartY > (rctClient.bottom - (2 * g_nBtnH)))
					:(m_nStartY > (rctClient.bottom));

		if( nCount )
			nVisible = m_bScrollBtnSide 
							?psTab[nCount - 1].nTabCx
							:nVisible = psTab[nCount - 1].nTabCx - g_nBtnH;

		m_bRight = (nVisible < rctClient.top);
	}
}

void CSlimTab::SetTabStyle( INT nStyle )
{
	ASSERT( nStyle >= ST_HORIZONTAL_TABDOWN && nStyle <= ST_VERTICAL_TABRIGHT );
	m_nTabStyle = nStyle;
}

void CSlimTab::OnSize( UINT nType, int cx, int cy ) 
{
	CWnd::OnSize( nType, cx, cy );
	CWnd* pNextWnd = GetNextWindow();
	if( pNextWnd )
	{
		CWnd* pParent = GetParent();
		ASSERT( pParent );

		CRect rcNext;
		pNextWnd->GetClientRect( rcNext );
		pParent->ClientToScreen( rcNext );

		CRect rct;
		GetClientRect( rct );
		pParent->ClientToScreen( rct );

		rcNext.left = rct.right + 1;
		pParent->ScreenToClient( rcNext );

		pNextWnd->MoveWindow( rcNext );
	}

	CalcTabPostion();
}

void CSlimTab::SetCurrentTab( INT nActive )
{
#ifdef _DEBUG
	INT nCount = m_arSlimTab.GetSize();
	ASSERT( nActive >= 0 && nActive < nCount );
#endif
	m_nCurTab = nActive;
	InvalidateRect( NULL, FALSE );
}

void CSlimTab::SetOppositeButton()
{
	m_bScrollBtnSide = (m_bScrollBtnSide == TRUE ?FALSE :TRUE);
	InitTab();
	CalcTabPostion();
	Invalidate();
}

CRect CSlimTab::GetScrollBtnRect( INT nBtn )
{
	CRect rctLeft, rctRight, rctClient;

	GetClientRect( rctClient );
	switch( m_nTabStyle )
	{
	case ST_HORIZONTAL_TABDOWN:
	case ST_HORIZONTAL_TABUP:
		rctLeft.top = (ST_HORIZONTAL_TABDOWN == m_nTabStyle ?rctClient.top + 1 :rctClient.bottom - g_nBtnH - 1);
		rctLeft.left = (m_bScrollBtnSide == TRUE ?rctClient.left :rctClient.right - 2 * g_nBtnW);
		rctLeft.right = rctLeft.left + g_nBtnW;
		rctLeft.bottom = rctLeft.top + g_nBtnH;
		rctRight = rctLeft;
		rctRight.OffsetRect( g_nBtnW, 0 );
		break;

	case ST_VERTICAL_TABLEFT:
	case ST_VERTICAL_TABRIGHT:
		rctLeft.top = (m_bScrollBtnSide == TRUE ?rctClient.bottom - g_nBtnH :rctClient.top + g_nBtnH);
		rctLeft.left = (ST_VERTICAL_TABLEFT == m_nTabStyle ?rctClient.right - g_nBtnW - 1 :rctClient.left + 1);
		rctLeft.right = rctLeft.left + g_nBtnW;
		rctLeft.bottom = rctLeft.top + g_nBtnH;
		rctRight = rctLeft;
		rctRight.OffsetRect( 0, -g_nBtnH );
		break;

	default:
		ASSERT( FALSE);
	}

	if( ST_BTN_LEFT == nBtn )
		return rctLeft; 
	else if( ST_BTN_RIGHT == nBtn )
		return rctRight;

	return NULL;
}

INT CSlimTab::GetCurrentTab()
{
	return m_nCurTab;
}

void CSlimTab::InitTab()
{
	CRect rctClient;

	m_nStartX  = 0;
	m_nStartY  = 0;

	GetClientRect( rctClient );
	switch( m_nTabStyle )
	{
	case ST_HORIZONTAL_TABDOWN:
	case ST_HORIZONTAL_TABUP:
		if( m_bScrollBtnSide == TRUE )
			m_nStartX = rctClient.left + 2 * g_nBtnW;
		else
			m_nStartX = rctClient.left;
		break;

	case ST_VERTICAL_TABLEFT:
	case ST_VERTICAL_TABRIGHT:
		if( m_bScrollBtnSide == TRUE )
			m_nStartY = rctClient.bottom - 2 * g_nBtnH;
		else
			m_nStartY = rctClient.bottom;
		break;

	default:
		ASSERT( FALSE ); 
	}
}

PTCHAR CSlimTab::GetTabText( INT nTab )
{
	ASSERT( nTab >= 0 && nTab < m_arSlimTab.GetSize() );
	return (PTCHAR)(LPCTSTR)m_arSlimTab[nTab].cszText;
}

LRESULT CSlimTab::OnNcHitTest(CPoint point) 
{
	CRect rct;
	GetClientRect( rct );	

	rct.left = rct.right - gc_nSizeBar;
	ClientToScreen( rct );
	if( rct.PtInRect( point ) )
		return HTRIGHT;

	return CWnd::OnNcHitTest(point);
}

INT CSlimTab::GetTabAt( CPoint point )
{
	INT nCount = m_arSlimTab.GetSize();
	PSSlimTab psTab = (PSSlimTab)m_arSlimTab.GetData();

	for( INT i = m_nVisible; i < nCount; i++ )
	{
		if( psTab[i].rctText.PtInRect( point ) )
			return i;
	}

	return -1;
}

class CRenameWnd : public CWnd
{
public:
	CRenameWnd();
	virtual ~CRenameWnd();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRenameWnd)
	public:
	virtual BOOL Create( CWnd* pParentWnd );
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CRenameWnd)
	afx_msg LRESULT OnFloatStatusMsg( WPARAM wParam, LPARAM lParam );
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
//	afx_msg void OnTimer(UINT nIDEvent);*/
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CRenameWnd, CWnd)
	//{{AFX_MSG_MAP(CToolBox)
	ON_MESSAGE( WM_FLOATSTATUS, OnFloatStatusMsg )
//	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CRenameWnd::CRenameWnd()
{
}

CRenameWnd::~CRenameWnd()
{}

BOOL CRenameWnd::Create( CWnd* pParentWnd )
{
	LPCTSTR lptClass = AfxRegisterWndClass( 0, LoadCursor( NULL, MAKEINTRESOURCE(IDC_ARROW) ), (HBRUSH)(COLOR_WINDOW + 1) );
	ASSERT( lptClass );

	CRect rctWnd(0,0,0,0);
	BOOL bResult = CreateEx( WS_EX_WINDOWEDGE, lptClass, NULL, 
						     WS_VISIBLE | WS_POPUP,
						     rctWnd, pParentWnd, 0 );

	return bResult;
}

// To syn float status, which keeps MainFrame always have active caption, 
// even this control get activated
LRESULT CRenameWnd::OnFloatStatusMsg( WPARAM wParam, LPARAM lParam ) {
	return 1L; }

static CPoint gs_ptMenu;
void CSlimTab::OnRButtonUp(UINT nFlags, CPoint point) 
{
	INT nTab = GetTabAt( point );
	if( -1 == nTab )
		return;

	if( m_nCurTab != nTab )
	{
		SetCurrentTab( nTab );
		UpdateWindow();
	}

	CMenu menu;
	menu.CreatePopupMenu();

	menu.AppendMenu( MF_STRING, 100 + 1, _T("Cut") );
	menu.AppendMenu( MF_STRING, 100 + 2, _T("Copy") );
	menu.AppendMenu( MF_STRING, 100 + 3, _T("Paste") );
	menu.AppendMenu( MFT_SEPARATOR, 100 + 0, _T("Sep") );
	menu.AppendMenu( MF_STRING, 100 + 4, _T("Rename") );

	ClientToScreen( &point );
	gs_ptMenu = point;
	int nCmd = menu.TrackPopupMenu( 0, point.x, point.y, this );
	
	if( nCmd )
		SendMessage( WM_COMMAND, nCmd );
}

void CSlimTab::OnRename()
{
	/*CRenameWnd* pRenameWnd = new CRenameWnd;
	pRenameWnd->Create( this );
	pRenameWnd->MoveWindow( gs_ptMenu.x, gs_ptMenu.y, 100, 16 );*/

	//RenameTab( m_nCurTab, "sdf" );
}

void CSlimTab::RenameTab( INT nIndex, PTCHAR pszTabName )
{
	INT nCount = m_arSlimTab.GetSize();
	if( nIndex < 0 || nIndex >= nCount )
		return;

	PSSlimTab psTab = &m_arSlimTab.GetAt( nIndex );
	SIZE		cbSize;
	HFONT		hFont, hOldFont;
	HDC	hdc	= ::GetDC( ::GetDesktopWindow() );

	psTab->cszText = pszTabName;

	hFont	= CreateFont( 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _TAB_FONT );
	ASSERT( hFont );
	hOldFont = (HFONT)SelectObject( hdc, hFont );
	GetTextExtentPoint32( hdc, pszTabName, psTab->cszText.GetLength(), &cbSize );
	psTab->nTabSize = cbSize.cx;
	psTab->nCaptionSize = cbSize.cx;
	SelectObject( hdc, hOldFont );
	if( m_nTabSize )
	{
		psTab->nTabSize = m_nTabSize;
		//psTab->nCaptionSize = m_nTabSize;
	}

	::ReleaseDC( ::GetDesktopWindow(), hdc );
	CalcTabPostion();
	Invalidate();
}
