#include "stdafx.h"
#include <cu\RulerWnd.h>
#include <cu\MemDC.h>
#include <gl\Gdip.h>
#include <cu\key.h>
#include <cu\reg.h>
#include <Windowsx.h> // for GET_X/Y_LPARAM
#include <cu\msg.h>
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/// This union is used to add float value into CUIntArray as interger
union _I2F
{
	FLOAT f;
	INT   i;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
CRulerUnit::CRulerUnit()
{
	m_fdpiX = 96.0f;
	m_fvpuX = 1.0f;
	m_fmpuX = 31.0f;

	m_fdpiY = 96.0f;
	m_fvpuY = 1.0f;
	m_fmpuY = 31.0f;
	Update();

	memset( m_arpnDiv, 0, sizeof(m_arpnDiv) );
	static INT s_arnDiv12[] = { 2, 5, 0 };
	static INT s_arnDiv5_10_20[] = { 2, 2, 2, 2, 0 };
	m_arpnDiv[1] = s_arnDiv12;
	m_arpnDiv[2] = s_arnDiv12;
	m_arpnDiv[5] = s_arnDiv5_10_20;
	m_arpnDiv[10] = s_arnDiv5_10_20;
	m_arpnDiv[20] = s_arnDiv5_10_20;
}

void CRulerUnit::Update()
{
	m_fppuX = m_fdpiX;
	m_fppuY = m_fdpiY;
}

CRulerUnit::~CRulerUnit()
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
CRulerUnitPixel::CRulerUnitPixel()
{
	m_fppuX = 1.0f;
	m_fppuY = 1.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CRulerUnitPoints::CRulerUnitPoints()
{
	m_fvpuX = 72.0f;
	m_fvpuY = 72.0f;
	Update();
}

void CRulerUnitPoints::Update()
{
	m_fppuX = m_fdpiX;
	m_fppuY = m_fdpiY;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CRulerUnitPercent::CRulerUnitPercent()
{
	m_fvpuX = 72.0f;
	m_fvpuY = 72.0f;

	m_fPageCx = 1024;
	m_fPageCy = 768;
	Update();
}

void CRulerUnitPercent::Update()
{
	m_fppuX = m_fdpiX;
	m_fppuY = m_fdpiY;

	m_fvpuX = (m_fdpiX / m_fPageCx) * 100.0f;
	m_fvpuY = (m_fdpiY / m_fPageCy) * 100.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CRulerUnitInch::CRulerUnitInch()
{
	Update();

	static INT s_arnDiv12[] = { 2, 5, 0 };
	static INT s_arnDiv5_10_20[] = { 2, 2, 2, 2, 0 };
	m_arpnDiv[1] = s_arnDiv12;
	m_arpnDiv[2] = s_arnDiv12;
	m_arpnDiv[5] = s_arnDiv5_10_20;
	m_arpnDiv[10] = s_arnDiv5_10_20;
	m_arpnDiv[20] = s_arnDiv5_10_20;
}

void CRulerUnitInch::Update()
{
	m_fppuX = m_fdpiX;
	m_fppuY = m_fdpiY;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CRulerUnitCM::CRulerUnitCM()
{
	Update();
}

void CRulerUnitCM::Update()
{
	m_fppuX = m_fdpiX / 2.54f;
	m_fppuY = m_fdpiY / 2.54f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CRulerUnitMM::CRulerUnitMM()
{
	Update();
}

void CRulerUnitMM::Update()
{
	m_fppuX = m_fdpiX / (2.54f * 10.0f);
	m_fppuY = m_fdpiY / (2.54f * 10.0f);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CRulerUnitMils::CRulerUnitMils()
{
	Update();
	static INT s_arnDiv10[] = { 10, 0, 0 };
	m_arpnDiv[10] = s_arnDiv10;
}

void CRulerUnitMils::Update()
{
	m_fppuX = m_fdpiX / 10.0f;
	m_fppuY = m_fdpiY / 10.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#define _CS_ZERO_TRACKING			1
#define _CS_HGUIDE_TRACKING			2
#define _CS_VGUIDE_TRACKING			2
#define _Is_ZeroTracking()			(0 != (m_nState & _CS_ZERO_TRACKING))
#define _Set_ZeroTracking()			(m_nState |= _CS_ZERO_TRACKING)
#define _Reset_ZeroTracking()		(m_nState &= ~_CS_ZERO_TRACKING)

#define _Is_HGuideTracking()		(0 != (m_nState & _CS_HGUIDE_TRACKING))
#define _Set_HGuideTracking()		(m_nState |= _CS_HGUIDE_TRACKING)
#define _Reset_HGuideTracking()		(m_nState &= ~_CS_HGUIDE_TRACKING)

#define _Is_VGuideTracking()		(0 != (m_nState & _CS_VGUIDE_TRACKING))
#define _Set_VGuideTracking()		(m_nState |= _CS_VGUIDE_TRACKING)
#define _Reset_VGuideTracking()		(m_nState &= ~_CS_VGUIDE_TRACKING)

#define _RULER_REGK			_T("Ruler")
#define _RULER_UNIT			_T("Unit")
#define _RULER_VISIBLE		_T("Visible")

#define _GUIDE_REGK			_RULER_REGK _T("\\Guide")
#define _GUIDE_VISIBLE		_T("Visible")
#define _GUIDE_SNAP			_T("Snap")
#define _GUIDE_STYLE		_T("Style")

BEGIN_MESSAGE_MAP(CRulerWnd, CWnd)
	//{{AFX_MSG_MAP(CRulerWnd)
	ON_WM_SETCURSOR()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ONC_MSG( CM_KEY_DOWN, OnKeyDownMsg )
	ONC_MSG( CM_KEY_UP, OnKeyUpMsg )
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CRulerWnd::CRulerWnd()
{
	m_pViewWnd = NULL;

	m_enUnit = CGUnit::INCH_UNIT;
	m_pUnit = NULL;

	m_nSize = 17;
	m_nState = 0;
	m_ptPrevHairLine.x = -1;	// No initial drawing
	m_ptfRulerOrg.x = 0;
	m_ptfRulerOrg.y = 0;

	m_ptfDocOrg.x = 0;
	m_ptfDocOrg.y = 0;
	m_ptOrg.x = 0;
	m_ptOrg.y = 0;
	m_fScaleX = 100.0f;
	m_fScaleY = 100.0f;
	m_crfGuide = RGB(0,0,255);

	m_nHTMargin = 5;	
 
	LoadSetting();
}

CRulerWnd::~CRulerWnd()
{
	CWinApp* pApp = AfxGetApp();
	WriteProfileBool( pApp, _RULER_REGK, _RULER_VISIBLE, m_bVisible );
	if( m_pUnit )
		delete m_pUnit;
}

BOOL CRulerWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_CLIPCHILDREN;	
	return CWnd::PreCreateWindow(cs);
}

void CRulerWnd::OnWindowPosChanged( WINDOWPOS* lpwndpos )
{
	CWnd::OnWindowPosChanged( lpwndpos );

	if( m_pViewWnd	)
	{
		INT nSize = m_nSize + 1;
		m_pResizeWnd->MoveWindow( nSize, nSize, lpwndpos->cx - nSize, lpwndpos->cy - nSize );
	}
}

void CRulerWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect;	
	GetClientRect( rect );

	HBRUSH hbrWindow = GetSysColorBrush( COLOR_WINDOW );
	FillRect( dc.m_hDC, rect, hbrWindow );

	// Draw Horz Ruler Border
	dc.MoveTo( 0, m_nSize );
	dc.LineTo( rect.right, m_nSize );

	// Draw Vert Ruler Border
	dc.MoveTo( m_nSize, 0 );
	dc.LineTo( m_nSize, rect.bottom );

	// Draw Origin Symbol
	INT nSize = m_nSize - 5;
	dc.MoveTo( nSize, 0 );
	dc.LineTo( nSize, m_nSize );

	dc.MoveTo( 0, nSize );
	dc.LineTo( m_nSize, nSize );

	DrawRuler();
}

BOOL CRulerWnd::OnEraseBkgnd( CDC* pDC ) {
	return TRUE; }

void CRulerWnd::LoadSetting()
{
	CWinApp* pApp = AfxGetApp();
	m_bVisible = GetProfileBool( pApp, _RULER_REGK, _RULER_VISIBLE, TRUE );

	m_bGuideVisible = GetProfileBool( pApp, _GUIDE_REGK, _GUIDE_VISIBLE, TRUE );
	m_bGuideSnap = GetProfileBool( pApp, _GUIDE_REGK, _GUIDE_SNAP, TRUE );
	m_nGuideStyle = GetProfileInt( pApp, _GUIDE_REGK, _GUIDE_STYLE, enRGS_Dot, enRGS_Dot, enRGS_Line );

	m_nGuideStyle = enRGS_DashDot;
	//m_nGuideStyle = enRGS_Line;
	m_enUnit = (CGUnit::UNIT)GetProfileInt( pApp, _RULER_REGK, _RULER_UNIT, CGUnit::INCH_UNIT, CGUnit::INCH_UNIT, CGUnit::MILS_UNIT );
	m_pUnit = NULL;
	SetRulerUnit( m_enUnit );
	SetRulerUnit( CGUnit::PIXEL_UNIT );
	ASSERT( m_pUnit );
}

void CRulerWnd::SaveSetting()
{
	CWinApp* pApp = AfxGetApp();

	WriteProfileInt( pApp, _RULER_REGK, _RULER_UNIT, m_enUnit );
	WriteProfileBool( pApp, _RULER_REGK, _RULER_VISIBLE, m_bVisible );
	WriteProfileBool( pApp, _GUIDE_REGK, _GUIDE_VISIBLE, m_bGuideVisible );
	WriteProfileBool( pApp, _GUIDE_REGK, _GUIDE_SNAP, m_bGuideSnap );
	WriteProfileInt( pApp, _GUIDE_REGK, _GUIDE_STYLE, m_nGuideStyle );
}

void CRulerWnd::ShowSettingDlg()
{
///	AfsSendCall( this, CM_ZMV_SHOW_TOOL_OPT );
}

void CRulerWnd::CalcCoord( GPointF& rpptf, INT nType ) const
{
	// Override this function
	ASSERT( NULL );
}

static void _CalcRulerDivision( FLOAT fScale, FLOAT* pfDiv, FLOAT* pfMul, FLOAT fppu, FLOAT fmpu )
{
	FLOAT fMul = 1.0f;
	FLOAT f = fppu * fMul * fScale;
	*pfMul = fMul;

	// Loop til a suitable multiple value such that f * multiple < min pixel per division
	while( f * fMul < fmpu )		
	{
		*pfMul = fMul;
		fMul *= 10.0f;
	}

	// Value = pixel per division
	f *= (*pfMul);

	// Value = Division no
	*pfDiv = 20.0f;
	if( f * 10.0f > fmpu )
		*pfDiv = 10.0f;

	if( f * 5.0f > fmpu )
		*pfDiv = 5.0f;

	if( f * 2.0f > fmpu )
		*pfDiv = 2.0f;

	if( f * 1.0f > fmpu )
		*pfDiv = 1.0f;
}

const INT cnSubDivMinGap = 2;
const INT cnSubDivInc = 2;
void CRulerWnd::CalcRulerSubDivsion( SRulerDiv& rsDiv, FLOAT fScale, FLOAT fppu, FLOAT fmpu )
{
	FLOAT fDiv, fMul;
	_CalcRulerDivision( fScale, &fDiv, &fMul, fppu, fmpu );
	INT nDivIndex = (INT)fDiv;

	rsDiv.parnSubDiv = NULL;
	if( nDivIndex < 21 )
		rsDiv.parnSubDiv = m_pUnit->m_arpnDiv[nDivIndex];

	if( NULL == rsDiv.parnSubDiv && nDivIndex > 0 && m_pUnit->m_arpnDiv[0] )
		rsDiv.parnSubDiv = m_pUnit->m_arpnDiv[0];

	rsDiv.fMult = fDiv * fMul;
	rsDiv.fDiv = fppu * fDiv * fMul * fScale;

	if( rsDiv.parnSubDiv )
	{
		INT nLevel = 0;
		INT* parnSubDiv = rsDiv.parnSubDiv;
		FLOAT fSubDiv, fDiv = rsDiv.fDiv;
		while( *parnSubDiv )
		{
			fSubDiv = fDiv / *parnSubDiv;
			if( fSubDiv <= cnSubDivMinGap )
				break;

			nLevel++;
			parnSubDiv++;
			fDiv = fSubDiv;
		}

		rsDiv.nFirstCs = 3 + nLevel * cnSubDivInc;
	}
}

void CRulerWnd::SetScale( FLOAT fScaleX, FLOAT fScaleY )
{
	// X - value
	m_fScaleX = fScaleX;
	CalcRulerSubDivsion( m_sxDiv, fScaleX, m_pUnit->m_fppuX, m_pUnit->m_fmpuX );

	// Y - value
	m_fScaleY = fScaleY;
	CalcRulerSubDivsion( m_syDiv, fScaleY, m_pUnit->m_fppuY, m_pUnit->m_fmpuY );
}

void CRulerWnd::EraseCursor()
{
	if( FALSE == m_bVisible )
		return;

	CPoint point( 0, 0 );
	CClientDC dc( this );
	DrawCursor( dc, point, TRUE );
}

void CRulerWnd::SetRulerUnit( CGUnit::UNIT enUnit )
{
	CRulerUnit* pUnit = NULL;
	switch( enUnit )
	{
	case CGUnit::PIXEL_UNIT:
		pUnit = new CRulerUnitPixel;
		break;

	case CGUnit::POINTS_UNIT:
		pUnit = new CRulerUnitPoints;
		break;

	case CGUnit::PERCENT_UNIT:
		pUnit = new CRulerUnitPercent;
		break;

	case CGUnit::INCH_UNIT:
		pUnit = new CRulerUnitInch;
		break;

	case CGUnit::CM_UNIT:
		pUnit = new CRulerUnitCM;
		break;

	case CGUnit::MM_UNIT:
		pUnit = new CRulerUnitMM;
		break;

	case CGUnit::MILS_UNIT:
		pUnit = new CRulerUnitMils;
		break;
	}

	if( pUnit )
	{
		if( m_pUnit )
			delete m_pUnit;

		m_pUnit = pUnit;
		SetScale( m_fScaleX, m_fScaleY );
	}
}

void CRulerWnd::DrawRuler()
{
	CClientDC dc( this );
	CRect rect;
	GetClientRect( rect );

	Draw( dc, rect );
}

void CRulerWnd::Draw( CDC& rDC, CRect rcPaint )
{
	GPointF ptfOrg = m_ptfRulerOrg;
	CalcCoord( ptfOrg, enRCC_ViewVectPointF );
	ptfOrg.x += m_ptfDocOrg.x + m_nSize; 
	ptfOrg.y += m_ptfDocOrg.y + m_nSize;
	m_ptPrevHairLine.x = -1;

	// Get System Window Color
	HBRUSH hbrWindow = GetSysColorBrush( COLOR_WINDOW );

	CRect rctBorder, rctDraw;
	{
		// Draw Ruler Left
		rctDraw.SetRect( 0, 0, m_nSize, rcPaint.Height() );

		CMemDC	MemDC;
		// TODO - if rctDraw.Height() <= m_nSize case, 'rctDraw.Height() - m_nSize' 
		// gives negative value and MemDC.create fails.
		if( MemDC.Create( &rDC, m_nSize, rctDraw.Height() - m_nSize ) )
		{
			MemDC.SetViewportOrg( 0, -m_nSize );
			FillRect( MemDC.m_hDC, rctDraw, hbrWindow );

//			MemDC.MoveTo( m_nSize - 1, 0 );
//			MemDC.LineTo( m_nSize - 1, rctDraw.bottom );

			DrawRulerDivision( MemDC, m_fScaleX, ptfOrg.y, (FLOAT)rcPaint.Height(), m_sxDiv, FALSE );
		}

		MemDC.SetViewportOrg( 0, 0 );
		rDC.BitBlt( rcPaint.left, rcPaint.top + m_nSize, m_nSize, rctDraw.Height() - m_nSize, &MemDC, 0, 0, SRCCOPY );
	}

	{
		// Draw Ruler Top
		rctDraw = rcPaint;
		rctDraw.bottom = rctDraw.top + m_nSize;
		rctDraw.SetRect( 0, 0, rcPaint.Width(), m_nSize );

		CMemDC	MemDC;
		if( MemDC.Create( &rDC, rctDraw.right, m_nSize ) )
		{
			FillRect( MemDC.m_hDC, rctDraw, hbrWindow );

			MemDC.MoveTo( m_nSize - 1, 0 );
			MemDC.LineTo( m_nSize - 1, m_nSize );

			MemDC.MoveTo( m_nSize / 2 + 2, 0 );
			MemDC.LineTo( m_nSize / 2 + 2, m_nSize );

			MemDC.MoveTo( 0, m_nSize / 2 + 2 );
			MemDC.LineTo( m_nSize, m_nSize / 2 + 2 );

			MemDC.MoveTo( 0, m_nSize - 1 );
			MemDC.LineTo( m_nSize, m_nSize - 1 );

			DrawRulerDivision( MemDC, m_fScaleY, ptfOrg.x, (FLOAT)rcPaint.Width(), m_syDiv );
		}

		rDC.BitBlt( rcPaint.left, rcPaint.top, rctDraw.Width(), m_nSize, &MemDC, 0, 0, SRCCOPY );
	}
}

void CRulerWnd::DrawCursor( CPoint point, BOOL bEraseOnly /*= FALSE*/ )
{
	CClientDC dc( this );
	DrawCursor( dc, point, bEraseOnly );
}

void CRulerWnd::DrawCursor( CDC& rDC, CPoint point, BOOL bEraseOnly /*= FALSE*/ )
{
	HPEN hPen;
	OSVERSIONINFO osv;
	osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx( &osv );

	if( VER_PLATFORM_WIN32_NT == osv.dwPlatformId )
	{
		LOGBRUSH lb;
		lb.lbColor = RGB(255,255,255);
		lb.lbStyle = BS_SOLID;
		hPen = ExtCreatePen( PS_COSMETIC | PS_ALTERNATE, 1, &lb, 0, 0 );
	}
	else
		hPen = CreatePen( PS_DOT, 1, RGB(0,0,0) );

	HPEN hOldPen = (HPEN)SelectObject( rDC.m_hDC, hPen );
	INT nOldRop = rDC.SetROP2( R2_XORPEN );

	point.x += m_ptOrg.x;
	point.y += m_ptOrg.y;
	if( m_ptPrevHairLine.x > 0 && m_ptPrevHairLine.y > 0 )
	{
		rDC.MoveTo( m_ptPrevHairLine.x, 0 );
		rDC.LineTo( m_ptPrevHairLine.x, m_nSize );

		rDC.MoveTo( 0, m_ptPrevHairLine.y );
		rDC.LineTo( m_nSize, m_ptPrevHairLine.y );
	}

	if( FALSE == bEraseOnly )
	{
		rDC.MoveTo( point.x, 0 );
		rDC.LineTo( point.x, m_nSize );

		rDC.MoveTo( 0, point.y );
		rDC.LineTo( m_nSize, point.y );
		m_ptPrevHairLine = point;
	}
	else
	{
		m_ptPrevHairLine.x = -1;
	}

	rDC.SetROP2( nOldRop );
	SelectObject( rDC.m_hDC, hOldPen );

	DeleteObject( hPen );
}

void CRulerWnd::DrawRulerSubDivision( CDC& rDC, 
									  FLOAT fOrg, FLOAT fLength, FLOAT fDiv, 
									  const INT* parnDiv, INT nHeight,
									  BOOL bHorz /*= TRUE*/ )
{
	ASSERT( parnDiv );
	FLOAT fSubDiv, fEnd = fOrg + fLength - 1;
	if( bHorz )
	{
		for( FLOAT fx = fOrg; fx < fEnd; fx += fDiv )
		{
			if( *parnDiv )
			{
				fSubDiv = fDiv / *parnDiv;
				if( fSubDiv > cnSubDivMinGap )
					DrawRulerSubDivision( rDC, fx, fDiv, fSubDiv, &parnDiv[1], nHeight - cnSubDivInc, bHorz );
			}

			if( fx <= m_nSize )
				continue;

			rDC.MoveTo( (INT)fx, m_nSize - nHeight );
			rDC.LineTo( (INT)fx, m_nSize );
		}
	}
	else
	{
		for( FLOAT fy = fOrg; fy < fEnd; fy += fDiv )
		{
			if( *parnDiv )
			{
				fSubDiv = fDiv / *parnDiv;
				if( fSubDiv > 1 )
					DrawRulerSubDivision( rDC, fy, fDiv, fSubDiv, &parnDiv[1], nHeight - cnSubDivInc, bHorz );
			}

			if( fy <= m_nSize )
				continue;

			rDC.MoveTo( m_nSize - nHeight, (INT)fy );
			rDC.LineTo( m_nSize, (INT)fy );
		}
	}
}

void CRulerWnd::FormatRulerNo( FLOAT fValue, CString& rcsz )
{
	LPCTSTR cptszNumFormat = _T("%.4g");

	if( fValue > 1000.f )
		rcsz.Format( _T("%d"), (INT)floor( fValue ) );
	else
		rcsz.Format( cptszNumFormat, fValue );
}

void CRulerWnd::DrawRulerDivision( CDC& rDC, FLOAT fScale, FLOAT fOrg, FLOAT fLength, const SRulerDiv& rsDiv, BOOL bHorz /*= TRUE*/ )
{
	INT nOldBkMode = rDC.GetBkMode();
	rDC.SetBkMode( TRANSPARENT );

	NONCLIENTMETRICS info; 
	info.cbSize = sizeof(info);
	::SystemParametersInfo( SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0 );
	CFont font, *pOldFont;

	if( info.lfMenuFont.lfHeight < 0 )
		info.lfMenuFont.lfHeight += 2;
	else
		info.lfMenuFont.lfHeight -= 2;

	VERIFY( font.CreateFontIndirect( &info.lfMenuFont ) );
	pOldFont = rDC.SelectObject( &font );

	TEXTMETRIC tm;
	GetTextMetrics( rDC.m_hDC, &tm );

	LPCTSTR cptszNumFormat = _T("%.4g");
	const INT cnLabelCy = 0;
	FLOAT f, fSubDiv;
	CString csz;
	LPTSTR ptsz;
	INT* parnSubDiv = rsDiv.parnSubDiv;
	if( bHorz )
	{
		FLOAT fx;
		for( fx = fOrg; fx < fLength; fx += rsDiv.fDiv )
		{
			if( parnSubDiv )
			{
				fSubDiv = rsDiv.fDiv / parnSubDiv[0];
				if( fSubDiv > cnSubDivMinGap )
					DrawRulerSubDivision( rDC, fx, rsDiv.fDiv, fSubDiv, &parnSubDiv[1], rsDiv.nFirstCs, bHorz );
			}

			if( fx <= m_nSize )
				continue;

			rDC.MoveTo( (INT)fx, 0 );
			rDC.LineTo( (INT)fx, m_nSize );

			f = m_pUnit->m_fvpuX * (fx - fOrg) / rsDiv.fDiv * rsDiv.fMult;
			if( f < 0.0f ) 
				f = -f;

			FormatRulerNo( f, csz );
			rDC.TextOut( (INT)fx + 2, -cnLabelCy, csz );
		}

		for( fx = fOrg - rsDiv.fDiv; ; fx -= rsDiv.fDiv )
		{
			if( parnSubDiv )
			{
				fSubDiv = rsDiv.fDiv / parnSubDiv[0];
				if( fSubDiv > cnSubDivMinGap )
					DrawRulerSubDivision( rDC, fx, rsDiv.fDiv, fSubDiv, &parnSubDiv[1], rsDiv.nFirstCs, bHorz );
			}

			if( fx < 0 )
				break;

			if( fx <= m_nSize )
				continue;

			rDC.MoveTo( (INT)fx, 0 );
			rDC.LineTo( (INT)fx, m_nSize );

			f = m_pUnit->m_fvpuX * (fx - fOrg) / rsDiv.fDiv * rsDiv.fMult;
			if( f < 0.0f ) 
				f = -f;

			FormatRulerNo( f, csz );
			rDC.TextOut( (INT)fx + 2, -cnLabelCy, csz );
		}
	}
	else
	{
		tm.tmHeight -= tm.tmInternalLeading;
		INT y;
		FLOAT fy;
		for( fy = fOrg; fy < fLength; fy += rsDiv.fDiv )
		{
			if( parnSubDiv )
			{
				fSubDiv = rsDiv.fDiv / parnSubDiv[0];
				if( fSubDiv > cnSubDivMinGap )
					DrawRulerSubDivision( rDC, fy, rsDiv.fDiv, fSubDiv, &parnSubDiv[1], rsDiv.nFirstCs, bHorz );
			}

			if( fy <= m_nSize )
				continue;

			rDC.MoveTo( 0, (INT)fy );
			rDC.LineTo( m_nSize, (INT)fy );

			f = m_pUnit->m_fvpuY * (fy - fOrg) / rsDiv.fDiv * rsDiv.fMult;
			if( f < 0.0f ) 
				f = -f;

			FormatRulerNo( f, csz );
			INT nLen = csz.GetLength();
			ptsz = (LPTSTR)(LPCTSTR)csz;
			y = (INT)fy + 2;
			for( INT i = 0; i < nLen; i++, y += tm.tmHeight )
				rDC.TextOut( 2, y, ptsz++, 1 );
		}

		for( fy = fOrg - rsDiv.fDiv; ; fy -= rsDiv.fDiv )
		{
			if( parnSubDiv )
			{
				fSubDiv = rsDiv.fDiv / parnSubDiv[0];
				if( fSubDiv > cnSubDivMinGap )
					DrawRulerSubDivision( rDC, fy, rsDiv.fDiv, fSubDiv, &parnSubDiv[1], rsDiv.nFirstCs, bHorz );
			}

			if( fy < 0 )
				break;

			if( fy <= m_nSize )
				continue;

			rDC.MoveTo( 0, (INT)fy );
			rDC.LineTo( m_nSize, (INT)fy );

			f = m_pUnit->m_fvpuY * (fy - fOrg) / rsDiv.fDiv * rsDiv.fMult;
			if( f < 0.0f ) 
				f = -f;

			FormatRulerNo( f, csz );
			INT nLen = csz.GetLength();
			ptsz = (LPTSTR)(LPCTSTR)csz;
			y = (INT)fy + 2;
			for( INT i = 0; i < nLen; i++, y += tm.tmHeight )
				rDC.TextOut( 2, y, ptsz++, 1 );
		}
	}

	rDC.SelectObject( pOldFont );
	rDC.SetBkMode( nOldBkMode );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Guide
void CRulerWnd::SetGuideStyle( Pen& rPen )
{
	switch( m_nGuideStyle )
	{
	case enRGS_Dot:
		rPen.SetDashStyle( DashStyleDot );
		break;

	case enRGS_DashDot: 
		rPen.SetDashStyle( DashStyleDash );
		break;
	}
}

void CRulerWnd::DrawGuides( Graphics& rGdip )
{
	if( 0 == m_arfHorzGuide.GetSize() && 0 == m_arfVertGuide.GetSize() )
		return;

	SmoothingMode enOldSmoothMode = rGdip.GetSmoothingMode();
	rGdip.SetSmoothingMode( SmoothingModeNone );

	Matrix mtx;
	rGdip.GetTransform( &mtx );
	rGdip.ResetTransform();

	CRect rcClient;
	GetClientRect( rcClient );

	GPointF ptf;
	FLOAT fCCx = (FLOAT)rcClient.right;
	FLOAT fCCy = (FLOAT)rcClient.bottom;

	Pen pen( CRF_2_COLOR( m_crfGuide | 0xFF000000 ) );
	pen.SetColor( Color::Blue );
	SetGuideStyle( pen );

	INT nCount = m_arfHorzGuide.GetSize();
	FLOAT* pfGuide = (FLOAT*)m_arfHorzGuide.GetData();
	INT i;
	for( i = 0; i < nCount; i++ )
	{
		ptf.x = 0.0f;
		ptf.y = pfGuide[i];
		mtx.TransformPoints( (PointF*)&ptf );
		rGdip.DrawLine( &pen, 0.0f, ptf.y, fCCx, ptf.y );
	}

	nCount = m_arfVertGuide.GetSize();
	pfGuide = (FLOAT*)m_arfVertGuide.GetData();
	for( i = 0; i < nCount; i++ )
	{
		ptf.x = pfGuide[i];
		ptf.y = 0.0f;
		mtx.TransformPoints( (PointF*)&ptf );
		rGdip.DrawLine( &pen, ptf.x, 0.0f, ptf.x, fCCy );
	}

	rGdip.SetTransform( &mtx );
	rGdip.SetSmoothingMode( enOldSmoothMode );
}

/// Parameter: 
///	rnIndex - Reference to a INT that receives index value of a 
/// horzontal or vertical guide if hittest matches one of it, otherwise -1.
UINT CRulerWnd::HitTest( const CPoint& rpoint, UINT& rnIndex ) const
{
	rnIndex = -1;

	// If point on Ruler drawing area
	if( rpoint.x < m_nSize && rpoint.y < m_nSize )
		return HT_NOTHING;

	if( rpoint.x < m_nSize || rpoint.y < m_nSize )
		return HT_RULER;

	CPoint point = rpoint;
	if( m_bVisible )
	{
		point.x -= m_nSize;
		point.y -= m_nSize;
	}

	GPointF ptf;
	INT nCount = m_arfHorzGuide.GetSize();
	FLOAT* pfGuide = (FLOAT*)m_arfHorzGuide.GetData();
	INT i;
	for( i = 0; i < nCount; i++ )
	{
		ptf.x = 0.0f;
		ptf.y = pfGuide[i];
		CalcCoord( ptf, enRCC_ViewPointF );
		if( ptf.y >= point.y - m_nHTMargin && ptf.y <= point.y + m_nHTMargin )
		{
			rnIndex = i;
			return HT_HORZ_GUIDE;
		}
	}

	nCount = m_arfVertGuide.GetSize();
	pfGuide = (FLOAT*)m_arfVertGuide.GetData();
	for( i = 0; i < nCount; i++ )
	{
		ptf.x = pfGuide[i];
		ptf.y = 0.0f;
		CalcCoord( ptf, enRCC_ViewPointF );
		if( ptf.x >= point.x - m_nHTMargin && ptf.x <= point.x + m_nHTMargin )
		{
			rnIndex = i;
			return HT_VERT_GUIDE;
		}
	}

	return HT_NOTHING;
}

UINT CRulerWnd::HitTest( const CPoint& rpoint ) const 
{
	UINT nIndex;
	return HitTest( rpoint, nIndex );
}

BOOL CRulerWnd::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage )
{
	{
		CPoint point;
		GetCursorPos( &point );
		ScreenToClient( &point );

		UINT nHitTest = HitTest( point );
		if( On_SetCursor( pWnd, nHitTest, nMessage ) )
			return TRUE;
	}

	return CWnd::OnSetCursor( pWnd, nHitTest, nMessage );
}

/// Parameter:
///	nMessage - Specifies the index of a guide line if the value of nHitTest is HT_HORZ or HT_VERT.
///			   If the value of nHitTest is HT_NOTHING, the value of nMessage is ignored.
BOOL CRulerWnd::On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage ) 
{
	if( HT_NOTHING == nHitTest || (HT_HORZ_GUIDE != nHitTest 
								&& HT_VERT_GUIDE != nHitTest
								&& HT_BOTH_GUIDE != nHitTest
								&& HT_ZERO_TRACK != nHitTest
								&& HT_RULER      != nHitTest) )
		return FALSE;

	UINT unCursorID = 0;
	HINSTANCE hInst = NULL;
	if( GetCursor( nHitTest, unCursorID, hInst ) )
		return TRUE;

	if( unCursorID )
		::SetCursor( LoadCursor( hInst, (LPCTSTR)unCursorID ) );

	return TRUE; 
}

BOOL CRulerWnd::GetCursor( UINT nHitTest, UINT& runCursorID, HINSTANCE& rhInst ) const
{
	switch( nHitTest )
	{
	case HT_RULER:
		runCursorID = (UINT)IDC_ARROW;
		return FALSE;

	case HT_BOTH_GUIDE:
	case HT_ZERO_TRACK:
		runCursorID = (UINT)IDC_HAIR_CUR;
		rhInst = AfxFindResourceHandle( MAKEINTRESOURCE(runCursorID), RT_GROUP_CURSOR );
		return FALSE;
		
	case HT_HORZ_GUIDE:
		runCursorID = AFX_IDC_VSPLITBAR;
		break;

	case HT_VERT_GUIDE:
		runCursorID = AFX_IDC_HSPLITBAR;
		break;
	}

	if( runCursorID )
		rhInst = AfxFindResourceHandle( MAKEINTRESOURCE(AFX_IDC_TRACK4WAY), RT_GROUP_CURSOR );

	return FALSE;
}

void CRulerWnd::OnLButtonDown( UINT nFlags, CPoint point )
{
	On_LButtonDown( nFlags, point );
}

BOOL CRulerWnd::On_LButtonDown( UINT nFlags, CPoint point )
{
	if( point.x < m_nSize )
	{
		if( point.y < m_nSize )
		{
			if( IsKeyCtrl_() )
				BothGuideTrack( point );
			else
				ZeroTrack( point );
			return TRUE;
		}

		GuideTrack( HT_VERT_GUIDE, point );
		return TRUE;
	}

	if( point.y < m_nSize )
	{
		GuideTrack( HT_HORZ_GUIDE, point );
		return TRUE;
	}

	UINT nGuideIndex;
	UINT nHitTest = HitTest( point, nGuideIndex );
	if( HT_NOTHING == nHitTest )
		return FALSE;

	GPointF ptf;
	FLOAT* pfGuide;
	
	if( HT_HORZ_GUIDE == nHitTest )
	{
		pfGuide = (FLOAT*)m_arfHorzGuide.GetData();
		ptf.x = 0.0f;
		ptf.y = pfGuide[nGuideIndex];
		CalcCoord( ptf, enRCC_ViewPointF );
		point.y = (INT)ptf.y + m_nSize;

		GuideTrack( HT_HORZ_GUIDE, point, nGuideIndex );
	}
	else
	{
		ASSERT( HT_VERT_GUIDE == nHitTest );
		pfGuide = (FLOAT*)m_arfVertGuide.GetData();
		ptf.x = pfGuide[nGuideIndex];
		ptf.y = 0.0f;
		CalcCoord( ptf, enRCC_ViewPointF );
		point.x = (INT)ptf.x + m_nSize;

		GuideTrack( HT_VERT_GUIDE, point, nGuideIndex );
	}

	return TRUE;
}

BOOL CRulerWnd::On_LButtonUp( UINT nFlags, CPoint point ) {
	return FALSE; }

void CRulerWnd::OnLButtonDblClk( UINT nFlags, CPoint point ) {
	On_LButtonDblClk( nFlags, point ); }

BOOL CRulerWnd::On_LButtonDblClk( UINT nFlags, CPoint point )
{
	if( point.x < m_nSize && point.y < m_nSize )
	{
		ResetOrigin();
		return TRUE;
	}

	if( point.x < m_nSize || point.y < m_nSize )
	{
		ShowSettingDlg();
		return TRUE;
	}

	return FALSE;
}

void CRulerWnd::ResetOrigin()
{
	m_ptfRulerOrg.x = 0.0f;
	m_ptfRulerOrg.y = 0.0f;
	DrawRuler();
}

void CRulerWnd::ZeroTrack( CPoint point )
{
	SetCapture();
	if( this != GetCapture() )
		return;

	On_SetCursor( this, HT_ZERO_TRACK, 0 );

	CRect rcClient;
	m_pViewWnd->GetClientRect( rcClient );
	INT nCCx = rcClient.right;
	INT nCCy = rcClient.bottom;

	CClientDC dc( m_pViewWnd );
	dc.SetROP2( R2_XORPEN );
	CPen pen( PS_SOLID, 1, RGB(127, 127, 127) );
	CPen* pOldPen = dc.SelectObject( &pen );

	point.x -= m_nSize;
	point.y -= m_nSize;
	dc.MoveTo( point.x, 0 );
	dc.LineTo( point.x, nCCy );

	dc.MoveTo( 0, point.y );
	dc.LineTo( nCCx, point.y );

	MSG msg;

	CPoint ptPrev = point;
	BOOL bOnRuler;
	BOOL bEnd = FALSE;
	BOOL bDraw = FALSE;
	BOOL bHorzErase = TRUE;
	BOOL bVertErase = TRUE;

	while( FALSE == bEnd && this == GetCapture() )
	{
		GetMessage( &msg, NULL, 0, 0 );
		if( msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSEFIRST )
		{
			point.x = GET_X_LPARAM(msg.lParam) - m_nSize;
			point.y = GET_Y_LPARAM(msg.lParam) - m_nSize;
		}

		switch( msg.message )
		{
		case WM_MOUSEMOVE:
			if( point != ptPrev )
			{
				bDraw = TRUE;
				bOnRuler = point.x < 0 || point.y < 0;
				if( bOnRuler )
					EraseCursor();
				else if( m_bVisible )
				{
					CPoint ptCursor = point;
					point.x--;
					point.y--;
					ptCursor.x += m_nSize;
					ptCursor.y += m_nSize;
					DrawCursor( ptCursor );
				}
			}
			break;

		case WM_LBUTTONUP:
			bEnd = TRUE;
			break;

		case WM_KEYDOWN:
			switch( msg.wParam )
			{
			case VK_ESCAPE:
				point.x = -1;
				point.y = -1;
				bEnd = TRUE;
				break;
			}
			break;

		default:
			DispatchMessage( &msg );
		}

		if( bDraw )
		{
			bDraw = FALSE;

			if( bHorzErase )
			{
				bHorzErase = FALSE;
				dc.MoveTo( 0, ptPrev.y );
				dc.LineTo( nCCx, ptPrev.y );
			}

			if( bVertErase )
			{
				bVertErase = FALSE;
				dc.MoveTo( ptPrev.x, 0 );
				dc.LineTo( ptPrev.x, nCCy );
			}

			if( point.x < nCCx )
			{
				bVertErase = TRUE;
				dc.MoveTo( point.x, 0 );
				dc.LineTo( point.x, nCCy );
			}

			if( point.y < nCCy )
			{
				bHorzErase = TRUE;
				dc.MoveTo( 0, point.y );
				dc.LineTo( nCCx, point.y );
			}

			ptPrev = point;
		}
	}

	dc.SelectObject( pOldPen );

	if( this == GetCapture() )
		ReleaseCapture();

	if( point.x >= 0 && point.y >= 0 )
	{
		m_ptfRulerOrg.x = (FLOAT)point.x + 2;
		m_ptfRulerOrg.y = (FLOAT)point.y + 1;
		m_ptfRulerOrg.x = m_ptfRulerOrg.x - m_ptfDocOrg.x;
		m_ptfRulerOrg.y = m_ptfRulerOrg.y - m_ptfDocOrg.y;
		CalcCoord( m_ptfRulerOrg, enRCC_PageVectPointF );
		DrawRuler();
	}

	CRect rect;
	rect.SetRect( 0, point.y, nCCx, point.y + 1 );
	m_pViewWnd->InvalidateRect( rect, FALSE );

	rect.SetRect( point.x, 0, point.x + 1, nCCy );	
	m_pViewWnd->InvalidateRect( rect, FALSE );
}

void CRulerWnd::GuideTrack( UINT nHitTest, CPoint point, INT nPos /*= -1*/ )
{
	SetCapture();
	if( this != GetCapture() )
		return;

	m_pViewWnd->UpdateWindow();

	CRect rcClient;
	m_pViewWnd->GetClientRect( rcClient );
	INT nCCx = rcClient.right;
	INT nCCy = rcClient.bottom;

	if( HT_HORZ_GUIDE == nHitTest )
		point.y -= m_nSize - 1;
	else
		point.x -= m_nSize - 1;

	if( -1 != nPos )
	{
		CRect rect;
		if( HT_HORZ_GUIDE == nHitTest )
			rect.SetRect( 0, point.y, nCCx, point.y + 1 );
		else
			rect.SetRect( point.x, 0, point.x + 1, nCCy );	

		m_pViewWnd->InvalidateRect( rect, FALSE );
	}

	CClientDC dc( m_pViewWnd );
	dc.SetROP2( R2_XORPEN );
	CPen pen( PS_SOLID, 1, RGB(127, 127, 127) );
	CPen* pOldPen = dc.SelectObject( &pen );

	if( HT_HORZ_GUIDE == nHitTest )
	{
		dc.MoveTo( 0, point.y );
		dc.LineTo( nCCx, point.y );
	}
	else
	{
		dc.MoveTo( point.x, 0 );
		dc.LineTo( point.x, nCCy );
	}

	MSG msg;
	CPoint ptPrev = point;

	INT nOldHitTest;
	BOOL bEnd = FALSE;
	BOOL bDraw = FALSE;
	BOOL bErase = TRUE;
	BOOL bReversed = FALSE;
	BOOL bReverse = FALSE;
	BOOL bAltDown = FALSE;
	BOOL bOnRuler;

	bOnRuler = HT_HORZ_GUIDE == nHitTest ?point.y < 0 
										 :point.x < 0;
	On_SetCursor( this, bOnRuler ?HT_RULER :nHitTest, 0 );

	CWnd* pPrevFocus = GetFocus();
	SetFocus();
	while( FALSE == bEnd && this == GetCapture() )
	{
		GetMessage( &msg, NULL, 0, 0 );
		if( msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSEFIRST )
		{
			point.x = GET_X_LPARAM(msg.lParam) - m_nSize - 1;
			point.y = GET_Y_LPARAM(msg.lParam) - m_nSize - 1;
		}

		switch( msg.message )
		{
		case WM_PAINT:
			DispatchMessage( &msg );
			bDraw = TRUE;
			break;

		case WM_MOUSEMOVE:
			if( point != ptPrev )
			{
				if( (HT_HORZ_GUIDE == nHitTest && point.y >= nCCy)
				 || (HT_VERT_GUIDE == nHitTest && point.x >= nCCx) )
					bDraw = FALSE;
				else
					bDraw = TRUE;

				On_SetCursor( this, FALSE == bDraw || bOnRuler ?HT_RULER :nHitTest, 0 );

				bOnRuler = point.x < 0 || point.y < 0;
				if( FALSE == bDraw || bOnRuler )
					EraseCursor();
				else if( m_bVisible )
				{
					CPoint ptCursor = point;
					ptCursor.x += m_nSize + 1;
					ptCursor.y += m_nSize + 1;
					DrawCursor( ptCursor );
				}
			}
			break;

		case WM_LBUTTONUP:
			bEnd = TRUE;
			break;

		case WM_SYSKEYDOWN:
			if( FALSE == bAltDown && VK_MENU == msg.wParam )
			{
				bAltDown = TRUE;
				bReversed = TRUE;
				bReverse = TRUE;
				bDraw = TRUE;
			}
			break;

		case WM_SYSKEYUP:
			if( bAltDown && VK_MENU == msg.wParam )
			{
				bAltDown = FALSE;
				bReversed = FALSE;
				bReverse = TRUE;
				bDraw = TRUE;
			}
			break;

		case WM_KEYDOWN:
			switch( msg.wParam )
			{
			case VK_ESCAPE:
				nPos = -1;
			case VK_DELETE:
				if( HT_HORZ_GUIDE == nHitTest )
					point.y = -1;
				else
					point.x = -1;
				bEnd = TRUE;
				break;
			}
		}

		nOldHitTest = nHitTest;
		if( bReverse )
		{
			bReverse = FALSE;
			nHitTest = HT_HORZ_GUIDE == nHitTest ?HT_VERT_GUIDE :HT_HORZ_GUIDE;
			On_SetCursor( this, bOnRuler ?HT_RULER :nHitTest, 0 );
		}

		if( bDraw )
		{
			bDraw = FALSE;

			if( bErase )
			{
				bErase = TRUE;

				if( HT_HORZ_GUIDE == nOldHitTest )
				{
					dc.MoveTo( 0, ptPrev.y );
					dc.LineTo( nCCx, ptPrev.y);
				}
				else
				{
					dc.MoveTo( ptPrev.x, 0 );
					dc.LineTo( ptPrev.x, nCCy );
				}
			}
			
			if( HT_HORZ_GUIDE == nHitTest )
			{
				dc.MoveTo( 0, point.y );
				dc.LineTo( nCCx, point.y);
			}
			else
			{
				dc.MoveTo( point.x, 0 );
				dc.LineTo( point.x, nCCy );
			}

			ptPrev = point;
		}
	}

	dc.SelectObject( pOldPen );
	pen.DeleteObject();

	if( this == GetCapture() )
		ReleaseCapture();

	if( bReversed && -1 != nPos )
	{
		if( HT_HORZ_GUIDE == nHitTest )
			m_arfVertGuide.RemoveAt( nPos );
		else
			m_arfHorzGuide.RemoveAt( nPos );

		nPos = -1;
	}

	if( HT_HORZ_GUIDE == nHitTest )
	{
		if( point.y >= 0 && point.y < nCCy )
		{
			_I2F i2f;
			GPointF ptf;
			ptf.y = (FLOAT)point.y; 
			ptf.x = 0.0f;
			CalcCoord( ptf, enRCC_PagePointF );
			i2f.f = ptf.y;

			if( -1 != nPos )
			{
				FLOAT* pfGuide = (FLOAT*)m_arfHorzGuide.GetData();
				pfGuide[nPos] = ptf.y - 1;
			}
			else
			{
				m_arfHorzGuide.Add( i2f.i );
				if( FALSE == m_bGuideVisible )
				{
					m_bGuideVisible = TRUE;
					m_pViewWnd->InvalidateRect( NULL, FALSE );
				}
			}

			{
				Graphics gdip( dc.m_hDC );

				Pen pen( CRF_2_COLOR( m_crfGuide | 0xFF000000 ) );
				pen.SetColor( Color::Blue );
				SetGuideStyle( pen );
				gdip.DrawLine( &pen, 0.0f, (FLOAT)point.y, (FLOAT)nCCx, (FLOAT)point.y );
			}
		}
		else if( -1 != nPos )
			m_arfHorzGuide.RemoveAt( nPos );
	}
	else
	{
 		if( point.x >= 0&& point.x < nCCx )
		{
			_I2F i2f;
			GPointF ptf;
			ptf.x = (FLOAT)point.x; 
			ptf.y = 0.0f; 
			CalcCoord( ptf, enRCC_PagePointF );
			i2f.f = ptf.x;
			
			if( -1 != nPos )
			{
				FLOAT* pfGuide = (FLOAT*)m_arfVertGuide.GetData();
				pfGuide[nPos] = ptf.x - 1;
			}
			else
			{
				m_arfVertGuide.Add( i2f.i );
				if( FALSE == m_bGuideVisible )
				{
					m_bGuideVisible = TRUE;
					m_pViewWnd->InvalidateRect( NULL, FALSE );
				}
			}

			{
				Graphics gdip( dc.m_hDC );

				Pen pen( CRF_2_COLOR( m_crfGuide | 0xFF000000 ) );
				pen.SetColor( Color::Blue );
				SetGuideStyle( pen );
				gdip.DrawLine( &pen, (FLOAT)point.x, 0.0f, (FLOAT)point.x, (FLOAT)nCCy );
			}
		}
		else if( -1 != nPos )
			m_arfVertGuide.RemoveAt( nPos );
	}

	m_pViewWnd->UpdateWindow();
	pPrevFocus->SetFocus();
}

void CRulerWnd::BothGuideTrack( CPoint point )
{
	SetCapture();
	if( this != GetCapture() )
		return;

	CRect rcClient;
	m_pViewWnd->GetClientRect( rcClient );
	INT nCCx = rcClient.right  - m_nSize;
	INT nCCy = rcClient.bottom - m_nSize;

	if( m_bVisible )
		EraseCursor();

	CClientDC dc( m_pViewWnd );
	dc.SetROP2( R2_XORPEN );
	CPen pen( PS_SOLID, 1, RGB(127, 127, 127) );
	CPen* pOldPen = dc.SelectObject( &pen );

	point.x -= m_nSize;
	point.y -= m_nSize;
	dc.MoveTo( point.x, 0 );
	dc.LineTo( point.x, nCCy );

	dc.MoveTo( 0, point.y );
	dc.LineTo( nCCx, point.y);

	MSG msg;

	CPoint ptPrev = point;

	BOOL bOnRuler;
	BOOL bEnd = FALSE;
	BOOL bDraw = FALSE;
	BOOL bHorzErase = TRUE;
	BOOL bVertErase = TRUE;

	On_SetCursor( this, HT_BOTH_GUIDE, 0 );

	while( FALSE == bEnd && this == GetCapture() )
	{
		GetMessage( &msg, NULL, 0, 0 );
		if( msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSEFIRST )
		{
			point.x = GET_X_LPARAM(msg.lParam) - m_nSize;
			point.y = GET_Y_LPARAM(msg.lParam) - m_nSize;
		}

		switch( msg.message )
		{
		case WM_MOUSEMOVE:
			if( point != ptPrev )
			{
				bDraw = TRUE;

				bOnRuler = point.x < 0 || point.y < 0;
				if( FALSE == bDraw || bOnRuler )
					EraseCursor();
				else if( m_bVisible )
				{
					CPoint ptCursor = point;
					ptCursor.x += m_nSize + 1;
					ptCursor.y += m_nSize + 1;
					DrawCursor( ptCursor );
				}
			}
			break;

		case WM_LBUTTONUP:
			bEnd = TRUE;
			break;

		case WM_KEYDOWN:
			switch( msg.wParam )
			{
			case VK_ESCAPE:
				point.x = -1;
				point.y = -1;
				bEnd = TRUE;
				break;
			}
		}

		if( bDraw )
		{
			bDraw = FALSE;

			if( bHorzErase )
			{
				bHorzErase = FALSE;
				dc.MoveTo( 0, ptPrev.y );
				dc.LineTo( nCCx, ptPrev.y);
			}

			if( bVertErase )
			{
				bVertErase = FALSE;
				dc.MoveTo( ptPrev.x, 0 );
				dc.LineTo( ptPrev.x, nCCy );
			}

			if( point.x < nCCx )
			{
				bVertErase = TRUE;
				dc.MoveTo( point.x, 0 );
				dc.LineTo( point.x, nCCy );
			}

			if( point.y < nCCy )
			{
				bHorzErase = TRUE;
				dc.MoveTo( 0, point.y );
				dc.LineTo( nCCx, point.y);
			}

			ptPrev = point;
		}
	}

	dc.SelectObject( pOldPen );
	pen.DeleteObject();

	if( this == GetCapture() )
		ReleaseCapture();

	if( point.x >= 0 && point.x < nCCx )
	{
		_I2F i2f;
		GPointF ptf;
		ptf.x = (FLOAT)point.x; 
		ptf.y = 0.0f; 
		CalcCoord( ptf, enRCC_PagePointF );
		i2f.f = ptf.x;
		
		m_arfVertGuide.Add( i2f.i );
		if( FALSE == m_bGuideVisible )
		{
			m_bGuideVisible = TRUE;
			m_pViewWnd->InvalidateRect( NULL, FALSE );
		}

		{
			Graphics gdip( dc.m_hDC );

			Pen pen( CRF_2_COLOR( m_crfGuide | 0xFF000000 ) );
			pen.SetColor( Color::Blue );
			SetGuideStyle( pen );
			gdip.DrawLine( &pen, (FLOAT)point.x, 0.0f, (FLOAT)point.x, (FLOAT)nCCy );
		}
	}

	if( point.y >= 0 && point.y < nCCy )
	{
		_I2F i2f;
		GPointF ptf;
		ptf.y = (FLOAT)point.y; 
		ptf.x = 0.0f;
		CalcCoord( ptf, enRCC_PagePointF );
		i2f.f = ptf.y;

		m_arfHorzGuide.Add( i2f.i );
		if( FALSE == m_bGuideVisible )
		{
			m_bGuideVisible = TRUE;
			m_pViewWnd->InvalidateRect( NULL, FALSE );
		}

		{
			Graphics gdip( dc.m_hDC );

			Pen pen( CRF_2_COLOR( m_crfGuide | 0xFF000000 ) );
			pen.SetColor( Color::Blue );
			SetGuideStyle( pen );
			gdip.DrawLine( &pen, 0.0f, (FLOAT)point.y, (FLOAT)nCCx, (FLOAT)point.y );
		}
	}
}

void CRulerWnd::InvalidateGuideAt( GPointF ptf )
{
	CalcCoord( ptf, enRCC_ViewPointF );
	CRect rcClient;
	GetClientRect( rcClient );

	if( ptf.x )
	{
		rcClient.left  = (INT)(ptf.x - 1);
		rcClient.right = (INT)(ptf.x + 1);
	}

	if( ptf.y )
	{
		rcClient.top  = (INT)(ptf.y - 1);
		rcClient.bottom = (INT)(ptf.y + 1);
	}

	m_pViewWnd->InvalidateRect( rcClient, FALSE );
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CRulerWnd::AddOptionPage( CPropertySheet* pPropSheet )
{
///	CRulerSettingPSDlg* pdlgRulerSetting = new CRulerSettingPSDlg;
///
///	pdlgRulerSetting->m_pRuler = this;
///	pPropSheet->AddPage( pdlgRulerSetting );
///
	return TRUE;
}

BOOL CRulerWnd::On_MouseMove( UINT nFlags, CPoint point ) 
{
	if( point.x < m_nSize || point.y < m_nSize )
		EraseCursor();
	else
		DrawCursor( point );

	return FALSE; 
}

void CRulerWnd::OnMouseMove( UINT nFlags, CPoint point ) {
	On_MouseMove( nFlags, point ); }

///{ Pass Key message to parent, it will be passed again to this window 
/// by parent if it does not want to process the key
LRESULT CRulerWnd::OnKeyDownMsg( WPARAM wParam, LPARAM lParam ) {
	return AfsSendMsg( GetParent(), CM_KEY_DOWN, wParam, lParam ); }

LRESULT CRulerWnd::OnKeyUpMsg( WPARAM wParam, LPARAM lParam ) {
	return AfsSendMsg( GetParent(), CM_KEY_UP, wParam, lParam ); }

void CRulerWnd::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	AfsSendMsg( GetParent(), CM_KEY_DOWN, nChar, MAKELPARAM( nRepCnt, nFlags ) ); }

void CRulerWnd::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	AfsSendMsg( GetParent(), CM_KEY_UP, nChar, MAKELPARAM( nRepCnt, nFlags ) ); }
///}

BOOL CRulerWnd::On_KeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	return FALSE; }

BOOL CRulerWnd::On_KeyUp( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	return FALSE; }
