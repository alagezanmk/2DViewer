#include "stdafx.h"
#include "PaletteBar.h"
#include <cu\MemDC.h>
//#include <AfsCfg.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CPaletteBar, CToolFrmWnd)
	//{{AFX_MSG_MAP(CPaletteBar)
	ON_MESSAGE( WM_FLOATSTATUS, OnFloatStatusMsg )
	ON_WM_PAINT()
	ON_WM_CREATE()
 	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPaletteBar::CPaletteBar()
{
	m_pPalCtrl = NULL;
}

CPaletteBar::~CPaletteBar()
{}

/// To syn float status, which keeps MainFrame always have active caption, 
/// even this control get activated
LRESULT CPaletteBar::OnFloatStatusMsg( WPARAM wParam, LPARAM lParam ) {
	return 1L; }

BOOL CPaletteBar::Create( LPCTSTR lpszWindowName, const RECT& rect, CWnd* pParentWnd )
{
	LPCTSTR lptClass = AfxRegisterWndClass( 0, LoadCursor( NULL, MAKEINTRESOURCE(IDC_ARROW) ) );
	ASSERT( lptClass );

	CRect rctWnd( rect );
	BOOL bResult = CreateEx( WS_EX_TOOLWINDOW, lptClass, lpszWindowName, 
						     WS_VISIBLE | WS_POPUP | WS_CAPTION | 
							 WS_SYSMENU | WS_THICKFRAME,
						     rctWnd, pParentWnd, 0 );

	return bResult;
}

#define ID_COLOR_WND		1
#define ID_OPACITY_SLDR		2
#define ID_PALETTE_CMB		3
INT CPaletteBar::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( CToolFrmWnd::OnCreate(lpCreateStruct) == -1 )
		return -1;

	m_wndStyle.Create( CRect(0, 0, 46, 46), this, ID_COLOR_WND );

	VERIFY( m_sldrOpacity.Create( WS_CHILD | WS_VISIBLE | TBS_HORZ, CRect(50, 20, 175, 45), this, ID_OPACITY_SLDR ) );
	m_sldrOpacity.SetRange( 0, 100 );
	m_sldrOpacity.SetTicFreq( 20 );
	m_sldrOpacity.SetLineSize( 1 );
	m_sldrOpacity.SetPageSize( 20 );

	m_cmbStyle.Create( WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, CRect(5, 50, 165, 130), this, ID_PALETTE_CMB );

	//SetSliderOpacity( g_sFill.fOpacity );

	/*VERIFY( m_pLyrCtrl = new CObjLayerCtrl );
	if( FALSE == m_pLyrCtrl->Create( NULL, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 
									   nullRECT, this, NULL, 0, NULL ) )
		return -1;*/

	return 0;
}

void CPaletteBar::OnSize( UINT nType, INT cx, INT cy ) 
{
	CToolFrmWnd::OnSize( nType, cx, cy );
	/*if( m_pLyrCtrl && m_pLyrCtrl->m_hWnd )
		m_pLyrCtrl->SetWindowPos( NULL, 0, 0, cx, cy, SWP_NOZORDER );*/
}

const INT gc_nPalx = 10;
const INT gc_nPaly = 10;
const INT gc_nPalCs = 25;
const INT gc_nPalBx = 20;
void CPaletteBar::OnPaint()
{
	CPaintDC dc( this );

	CRect rctClient;
	GetClientRect( rctClient );
	INT nCx = rctClient.Width();
	INT nCy = rctClient.Height();

	CMemDC MemDC;
	MemDC.Create( &dc, nCx, nCy );
	FillRect( MemDC.m_hDC, rctClient, (HBRUSH)(COLOR_BTNFACE + 1) );
	MemDC.TextOut( 100, 4, _T("Opacity") );

///	{
///		Graphics gdip( MemDC.m_hDC );
///		HatchBrush brushHatch( HatchStyleZigZag, Color(85,0,0,0), Color::White );
///		SolidBrush brushWhite( Color::White );
///		Pen pen( Color::Black );
///
///		/// Initialize rectangle structure for fill and stroke style drawing
///		GRectF rcf;
///		rcf.X = gc_nPalx;
///		rcf.Y = gc_nPaly;
///		rcf.Width = gc_nPalCs;
///		rcf.Height = gc_nPalCs;
///
///		// Draw Fill style background and rectangle
///		gdip.FillRectangle( &brushWhite, rcf );
///		gdip.FillRectangle( &brushHatch, rcf );
///		{
///			g_Style.m_FillStyle.SetByText( enObjStyleIccColor, _T("blue") );
///			CObjStyleBrush brush( &g_Style.m_FillStyle, 0.3f, rcf );
///			gdip.FillRectangle( brush, rcf );
///		}
///
///		gdip.DrawRectangle( &pen, rcf );
///
///
///		// Draw Stroke style background and rectangle
///		rcf.X += gc_nPalCs + gc_nPalBx;
///		gdip.FillRectangle( &brushWhite, rcf );
///		gdip.FillRectangle( &brushHatch, rcf );
///		{
///			g_Style.m_StrokeStyle.SetByText( enObjStyleIccColor, _T("darkred") );
///			CObjStyleBrush brush( &g_Style.m_StrokeStyle, 0.4f, rcf );
///			gdip.FillRectangle( brush, rcf );
///		}
///		gdip.DrawRectangle( &pen, rcf );
///	}

	MemDC.BitBltTo( &dc );
}