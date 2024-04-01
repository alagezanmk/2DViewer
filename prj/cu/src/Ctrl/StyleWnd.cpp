#include "stdafx.h"
#include <cu\msg.h>
#include "StyleWnd.h"
//#include "ColorPickerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*class CARGBPickerDlg : public CColorPickerDlg
{
public:
	void SetColor( const CStyle& rStyle ) {
		m_fOpacity = rStyle.m_fOpacity;
		CColorPickerDlg::SetColor( ARGB_2_CRF( rStyle.GetARGB() ) ); }

	const CStyle& GetColor() {
		m_style.SetColor( CRF_2_ARGB(CColorPickerDlg::GetColor()) );
		m_style.m_fOpacity = m_fOpacity;
		return m_style; }

	const CStyle& GetCurrentColor() {
		m_style.SetColor( CRF_2_ARGB(CColorPickerDlg::GetCurrentColor()) );
		m_style.m_fOpacity = m_fOpacity;
		return m_style; }

	const CStyle& GetPreviousColor() {
		m_style.SetColor( CRF_2_ARGB(CColorPickerDlg::GetPreviousColor()) );
		m_style.m_fOpacity = m_fOpacity;
		return m_style; }

	virtual void DrawStyle( CDC* pDC, const CRect& rct, const CRect& rctCur, const CRect& rctPrev );

	CStyle		m_style;
	FLOAT		m_fOpacity;
};

void CARGBPickerDlg::DrawStyle( CDC* pDC, const CRect& rct, const CRect& rctCur, const CRect& rctPrev )
{
	Graphics gdip( pDC->m_hDC );
	Rect grct( rct.left, rct.top, rct.Width(), rct.Height() );
	HatchBrush brushHatch( HatchStyleZigZag, Color(85,0,0,0), Color::White );
	SolidBrush brushWhite( Color::White );
	gdip.FillRectangle( &brushWhite, grct );
	gdip.FillRectangle( &brushHatch, grct );

	{
		grct.X = rctCur.left;
		grct.Y = rctCur.top;
		grct.Width = rctCur.Width();
		grct.Height = rctCur.Height();

		m_style.SetColor( CRF_2_ARGB( m_crfCur ), m_fOpacity );
		CStyleBrush brush( m_style );
		gdip.FillRectangle( brush, grct );
	}

	{
		grct.X = rctPrev.left;
		grct.Y = rctPrev.top;
		grct.Width = rctPrev.Width();
		grct.Height = rctPrev.Height();
		
		m_style.SetColor( CRF_2_ARGB( m_crfPrev ), m_fOpacity );
		CStyleBrush brush( m_style );
		gdip.FillRectangle( brush, grct );
	}
}*/

const INT g_cnCtrlx = 3;
const INT g_cnCtrly = 3;
const INT g_cnDefBoxCs = 7;
const INT g_cnDefBoxOffset = 3;
const INT g_cnExgSize = 8;
const INT g_cnArrSize = 2;

BEGIN_MESSAGE_MAP(CStyleWnd, CWnd)
	//{{AFX_MSG_MAP(CStyleWnd)
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CStyle CStyleWnd::ms_styleFore;
CStyle CStyleWnd::ms_styleBack;
INT CStyleWnd::ms_nActiveBox;
CPtrArray CStyleWnd::m_arpColorWnd;

CStyleWnd::CStyleWnd()
{
	ms_styleFore.SetColor( Color::Blue, 0.5f );
	ms_styleBack.SetColor( Color::Teal, 0.5f );
	m_nLeft		 = g_cnCtrlx;
	m_nTop		 = g_cnCtrly;
	ms_nActiveBox = 0;
	m_nBoxSize = 26;
	m_unStyle = CBS_DEFAULT | CBS_EXCHANGE | CBS_SHOWACTIVEBOX;
	m_bInternalUpdate = FALSE;

	CalcBoxSize();
}

CStyleWnd::~CStyleWnd()
{}

void CStyleWnd::SetStartPoint( INT x, INT y )
{
	m_nLeft = x;
	m_nTop = y;
	CalcBoxSize();
}

void CStyleWnd::SetBoxSize( INT p_nBoxSize )
{
	m_nBoxSize = p_nBoxSize;
	CalcBoxSize();
}

void CStyleWnd::CalcBoxSize()
{
	m_rctBackBox.left	= m_nLeft + 15;
	m_rctBackBox.top	= m_nTop + 15;
	m_rctBackBox.right	= m_rctBackBox.left + m_nBoxSize;
	m_rctBackBox.bottom = m_rctBackBox.top + m_nBoxSize;
	
	m_rctForeBox = m_rctBackBox;
	OffsetRect( &m_rctForeBox, -m_nBoxSize / 2, -m_nBoxSize / 2 );
	
	m_rctDefBox.left	= m_rctForeBox.left;
	m_rctDefBox.right	= m_rctDefBox.left + g_cnDefBoxCs + g_cnDefBoxOffset;
	m_rctDefBox.bottom	= m_rctBackBox.bottom;
	m_rctDefBox.top		= m_rctDefBox.bottom - g_cnDefBoxCs - g_cnDefBoxOffset;
	
	m_rctExgBox.right	= m_rctBackBox.right;
	m_rctExgBox.left	= m_rctExgBox.right - g_cnExgSize ;
	m_rctExgBox.top		= m_rctForeBox.top;
	m_rctExgBox.bottom  = m_rctExgBox.top + g_cnExgSize;
	
	OffsetRect( &m_rctExgBox, -g_cnArrSize, g_cnArrSize );
}

void CStyleWnd::SetStyle( UINT unStyle )
{
	m_unStyle = unStyle;
}

BOOL CStyleWnd::Create( const RECT& rect, CWnd* pParentWnd, INT nID )
{
	LPCTSTR lptClass = AfxRegisterWndClass( 0, LoadCursor( NULL, MAKEINTRESOURCE(IDC_ARROW) ) );
	ASSERT( lptClass );

	return CreateEx(  0, lptClass, NULL, WS_VISIBLE | WS_CHILD, 
					  rect.left, rect.top, 
					  rect.right - rect.left,
					  rect.bottom - rect.top,
					  pParentWnd->m_hWnd, (HMENU)nID, NULL );
}

int  CStyleWnd::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( -1 == CWnd::OnCreate( lpCreateStruct ) )
		return -1;

	m_arpColorWnd.Add( this );
	
	return 0;
}

RectF GetRect( CRect& rRect )
{
	RectF rctf( (FLOAT)rRect.left, (FLOAT)rRect.top, (FLOAT)rRect.Width(), (FLOAT)rRect.Height() );
	return rctf;
}

void CStyleWnd::OnPaint() 
{
	INT	nCtrlX = 3;
	INT	nCtrlY = 3;
	CRect rect;
	
	INT	nCCx, nCCy;
	CRect rctClient;
	CPaintDC dc( this );

	CDC	MemDC;
	CBitmap	Bm;
	CBitmap* pOldBm;
	
	COLORREF crfHilite = GetSysColor( COLOR_3DHILIGHT );
	COLORREF crfShadow = GetSysColor( COLOR_3DSHADOW );
	CBrush brBlack( RGB( 0, 0, 0 ) );
	CBrush brWhite( RGB( 255, 255, 255 ) );
	CBrush brBackgrnd( GetSysColor( COLOR_BTNFACE ) );

	GetClientRect( &rctClient );

	dc.FillSolidRect( rctClient, 0 );
	//return;

	nCCx = rctClient.Width();
	nCCy = rctClient.Height();

	MemDC.CreateCompatibleDC( &dc );
	Bm.CreateCompatibleBitmap( &dc, nCCx, nCCy );
	pOldBm = MemDC.SelectObject( &Bm );

	// Draw Back ground
	rctClient.InflateRect( 1, 1 );
	MemDC.FillRect( &rctClient, &brBackgrnd );

	{
		Graphics gdip( MemDC.m_hDC );
		CStyleBrush brushBack( ms_styleBack );
		CStyleBrush brushFore( ms_styleFore );
		HatchBrush brushHatch( HatchStyleZigZag, Color(85,0,0,0), Color::White );
		SolidBrush brushWhite( Color::White );
	
		// Back Color Box
		RectF rcf = GetRect( m_rctBackBox );
		gdip.FillRectangle( &brushWhite, rcf );
		gdip.FillRectangle( &brushHatch, rcf );
		gdip.FillRectangle( brushFore, rcf );
		if( (CBS_SHOWACTIVEBOX & m_unStyle) && 1 == ms_nActiveBox )
		{
			CRect rctBorder = m_rctBackBox;
			MemDC.FrameRect( &m_rctBackBox, &brBlack );
			rctBorder.DeflateRect( 1, 1 );
			MemDC.FrameRect( &rctBorder, &brWhite );
		}
		else // Draw 3d border
			MemDC.Draw3dRect( &m_rctBackBox, crfShadow, crfHilite );
		
		// Fore Color Box
		rcf = GetRect( m_rctForeBox );
		gdip.FillRectangle( &brushWhite, rcf );
		gdip.FillRectangle( &brushHatch, rcf );
		gdip.FillRectangle( brushBack, rcf );
		if( (CBS_SHOWACTIVEBOX & m_unStyle) && 0 == ms_nActiveBox )
		{
			CRect rctBorder = m_rctForeBox;
			MemDC.FrameRect( &m_rctForeBox, &brBlack );
			rctBorder.DeflateRect( 1, 1 );
			MemDC.FrameRect( &rctBorder, &brWhite );
		}
		else // Draw 3d border
			MemDC.Draw3dRect( &m_rctForeBox, crfShadow, crfHilite );
	}
	
	if( CBS_DEFAULT & m_unStyle )
	{
		// Default Fore Color Box
		rect = m_rctDefBox;
		rect.DeflateRect( g_cnDefBoxOffset, g_cnDefBoxOffset, 0, 0 );
		MemDC.FillRect( &rect, &brWhite );
		MemDC.FrameRect(&rect, &brBlack );

		// Default Back Color Box
		rect= m_rctDefBox;
		rect.DeflateRect( 0, 0, g_cnDefBoxOffset, g_cnDefBoxOffset );
		MemDC.FillRect( &rect, &brBlack );
	}
	
	if( CBS_EXCHANGE & m_unStyle )
	{
		// Exchange Arc
		MemDC.MoveTo( m_rctExgBox.left + g_cnArrSize, m_rctExgBox.top - g_cnArrSize );
		MemDC.LineTo( m_rctExgBox.left, m_rctExgBox.top );
		MemDC.LineTo( m_rctExgBox.right - 2, m_rctExgBox.top );
		MemDC.LineTo( m_rctExgBox.right, m_rctExgBox.top + 2 );
		MemDC.LineTo( m_rctExgBox.right, m_rctExgBox.bottom );
		MemDC.LineTo( m_rctExgBox.right  + g_cnArrSize, m_rctExgBox.bottom - g_cnArrSize );
		
		MemDC.MoveTo( m_rctExgBox.left, m_rctExgBox.top );
		MemDC.LineTo( m_rctExgBox.left + g_cnArrSize, m_rctExgBox.top + g_cnArrSize + 1 );
		
		MemDC.MoveTo( m_rctExgBox.left + g_cnArrSize, m_rctExgBox.top + g_cnArrSize );
		MemDC.LineTo( m_rctExgBox.left + g_cnArrSize, m_rctExgBox.top - g_cnArrSize - 1 );
		
		MemDC.MoveTo( m_rctExgBox.right, m_rctExgBox.bottom );
		MemDC.LineTo( m_rctExgBox.right - g_cnArrSize, m_rctExgBox.bottom - g_cnArrSize );
		
		MemDC.MoveTo( m_rctExgBox.right - g_cnArrSize, m_rctExgBox.bottom - g_cnArrSize );
		MemDC.LineTo( m_rctExgBox.right + g_cnArrSize, m_rctExgBox.bottom - g_cnArrSize );
	}

	dc.BitBlt( 0, 0, nCCx, nCCy, &MemDC, 0, 0, SRCCOPY );
	MemDC.SelectObject( pOldBm );
}

void CStyleWnd::SetForeColor( const CStyle& rStyle )
{
	if( FALSE == m_bInternalUpdate )
	{
		m_bInternalUpdate = TRUE;
		ms_styleFore.Copy( &rStyle );
		InvalidateAllColorWnd();
		SendNotify( this, NM_UPDATE_FORE );
		m_bInternalUpdate = FALSE;
	}
}

void CStyleWnd::SetBackColor( const CStyle& rStyle )
{
	if( FALSE == m_bInternalUpdate )
	{
		m_bInternalUpdate = TRUE;
		ms_styleBack.Copy( &rStyle );
		InvalidateAllColorWnd();
		SendNotify( this, NM_UPDATE_BACK );
		m_bInternalUpdate = FALSE;
	}
}

void CStyleWnd::SetColor( INT nBox, const CStyle& rStyle )
{
	switch( nBox )
	{
	case 0:
		SetForeColor( rStyle );
		break;

	case 1:
		SetBackColor( rStyle );
		break;
	}
}

void CStyleWnd::InvalidateAllColorWnd()
{
	INT nCount = m_arpColorWnd.GetSize();
	CWnd** ppWnd = (CWnd**)m_arpColorWnd.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		ASSERT_VALID( ppWnd[i] );
		ASSERT( IsWindow( ppWnd[i]->m_hWnd ) );
		ppWnd[i]->InvalidateRect( NULL, FALSE );
	}

}
void CStyleWnd::ExchangeColor()
{
	CStyle style;
	style.Copy( &ms_styleFore );
	ms_styleFore.Copy( &ms_styleBack );
	ms_styleBack.Copy( &style );
	InvalidateAllColorWnd();
}

void CStyleWnd::SetDefaultColor()
{
	ms_styleFore.SetColor( Color::White, 0.5f );
	ms_styleBack.SetColor( Color::Black, 0.5f );
	InvalidateAllColorWnd();
}

void CStyleWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CColorDialog oColorDialog;
	INT	nClkBox = ms_nActiveBox;
	
	// Check Default box
	if( (CBS_DEFAULT & m_unStyle) && PtInRect( &m_rctDefBox, point ) )
	{
		SetDefaultColor();
		return;
	}
	
	// Check Exchange box
	if( (CBS_EXCHANGE & m_unStyle) && PtInRect( &m_rctExgBox, point ) )
	{
		ExchangeColor();
		return;
	}

	BOOL bClickedColorPicker = FALSE;

	// Check Fore Color box
	if( PtInRect( &m_rctForeBox, point ) )
	{
		bClickedColorPicker = TRUE;
		ms_nActiveBox = 0;
		if( 0 != nClkBox && CBS_SHOWACTIVEBOX & m_unStyle )
		{
			InvalidateAllColorWnd();
			//SetColor( 0, m_crfFore );
			return;
		}
	} // Check Back Color box
	else if( PtInRect( &m_rctBackBox, point ) ) 
	{
		bClickedColorPicker = TRUE;
		ms_nActiveBox = 1;
		if( 1 != nClkBox && CBS_SHOWACTIVEBOX & m_unStyle )
		{
			InvalidateAllColorWnd();
			//SetColor( 1, m_crfBack );
			return;
		}
	}

	if( bClickedColorPicker && (CBS_SHOWPICKER & m_unStyle) )
	{
		/*CStyle* pStyle;
		CARGBPickerDlg dlg;

		pStyle = (0 == ms_nActiveBox ?&ms_styleFore :&ms_styleBack);
		dlg.SetColor( *pStyle );
		if( IDOK == dlg.DoModal() )
		{
			const CStyle& rStyle = dlg.GetColor();
			SetColor( ms_nActiveBox, rStyle );
		}*/
	}
}