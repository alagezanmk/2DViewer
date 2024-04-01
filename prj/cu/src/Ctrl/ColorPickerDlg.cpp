#include "stdafx.h"
#include <cu\MemDC.h>
#include "ColorPickerDlg.h"
//#include "PsRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Coordinates
// ^
// |
// |	R   G	B	-> Current Radio Button
// R	z	y	y
// G	y	z	x
// B	x	x	z

// Coordinates
// ^
// |
// |	H   S	V	-> Current Radio Button
// R H	z	x	x
// G S	x	z	y
// B V	y	y	z

void HSVtoRGB( INT h, INT s, INT v, INT *r, INT *g, INT *b );
void RGBtoHSV( INT r, INT g, INT b, INT *h, INT *s, INT *v );

FLOAT Min(FLOAT a, FLOAT b, FLOAT c);
FLOAT Max( FLOAT a, FLOAT b, FLOAT c );

const INT g_cnMrnX = 10;
const INT g_cnMrnY = 10;

const INT g_cnColorPanelW = 256;
const INT g_cnColorPanelH = 256;

const INT g_cnColorBarX = g_cnMrnX + g_cnColorPanelW + 2 + g_cnMrnX + 6;
const INT g_cnColorBarY = g_cnMrnY;

const INT g_cnColorBarW = 20;
const INT g_cnColorBarH = 256;

const INT g_cnCurColorX = g_cnColorBarX + g_cnColorBarW + 30;
const INT g_cnCurColorY = g_cnMrnY;

const INT g_cnCurColorW = 78;
const INT g_cnCurColorH = 85;

const INT g_cnArrX = 4;
const INT g_cnArrY = 4;

FLOAT Min(FLOAT a, FLOAT b, FLOAT c)
{
	if( ( a < b ) && ( a < c ) ) return a;
	else if ( b < c ) return b;
	else return c;
}

FLOAT Max( FLOAT a, FLOAT b, FLOAT c )
{
	if( ( a > b ) && ( a > c ) ) return a;
	else if ( b > c )return b;
	else return c;
}

void RGBtoHSV( INT nR, INT nG, INT nB, PINT pnH, PINT pnS, PINT pnV )
{
	FLOAT fMin, fMax, fDelta;
	FLOAT fR, fG, fB;
	
	fR = (FLOAT)nR / 256.0f;
	fG = (FLOAT)nG / 256.0f;
	fB = (FLOAT)nB / 256.0f;

	fMin = Min( fR, fG, fB );
	fMax = Max( fR, fG, fB );

	*pnV = (INT)(fMax * 100.0f);

	fDelta = fMax - fMin;
	if( 0 != fMax )
		*pnS = (INT)(fDelta * 100.0 / fMax);
	else 
	{
		*pnS = 0;
		*pnH = 0;
		return;
	}

	if( fR == fMax )
		*pnH = (INT)((fG - fB) / fDelta);
	else if( fG == fMax )
		*pnH = (INT)(2 + (fB - fR) / fDelta);
	else
		*pnH = (INT)(4 + (fR - fB) / fDelta);

	*pnH *= 60;	
	if( *pnH < 0 )
		*pnH += 360;
}

void HSVtoRGB( INT nH, INT nS, INT nV, PINT pnR, PINT pnG, PINT pnB )
{
	INT i;
	
	FLOAT f, p, q, t;
	FLOAT fH, fS, fV;

	if( nS == 0 )
	{
		// achromatic (grey)
		*pnR = *pnG = *pnB = nV;
		return;
	}

	fV = (FLOAT)nV / 100.0f;
	fS = (FLOAT)nS / 100.0f;

	fH = (FLOAT)nH / (60.0f * 360.0f);					// sector 0 to 5
	i = (INT)floor( fH );
	f = fH - i;										// factorial part of h
	p = fV * (1 - fS);
	q = fV * (1 - fS * f);
	t = fV * (1 - fS * (1 - f) );

	switch( i ) 
	{
	case 2:
		*pnR = nV;
		*pnG = (INT)(t * 256.0f);
		*pnB = (INT)(p * 256.0f);
		break;

	case 3:
		*pnR = (INT)(q * 256.0f);
		*pnG = nV;
		*pnB = (INT)(p * 256.0f);
		break;

	case 4:
		*pnR = (INT)(p * 256.0f);
		*pnG = nV;
		*pnB = (INT)(t * 256.0f);
		break;

	case 5:
		*pnR = (INT)(p * 256.0f);
		*pnG = (INT)(q * 256.0f);
		*pnB = nV;
		break;

	case 0:
		*pnR = (255 - (INT)(t * 256.0f));
		*pnG = (255 - (INT)(p * 256.0f));
		*pnB = (225 - nV);
		break;

	case 1:
		*pnR = nV;
		*pnG = (INT)(p * 256.0f);
		*pnB = (INT)(q * 256.0f);
		break;
	}
}

CColorPickerDlg::CColorPickerDlg( CWnd* pParent /*=NULL*/ ) :
	CDialog( IDD_COLOR_PICKER_DLG, pParent )
{
	//{{AFX_DATA_INIT(CColorPickerDlg)
	//}}AFX_DATA_INIT

	m_enInternalUpdate = enNone;
	m_enColorMode = enHue;
	m_crfPrev = RGB(255, 0, 0);
	m_crfCur = RGB(255, 0, 0);

	m_nDrag  = 0;
	m_nRed   = 255;
	m_nGreen = 0;
	m_nBlue  = 0;

	m_bColorPanelModified = TRUE;
	m_bColorBarModified   = TRUE;
	m_pbyColorPanel = NULL;
	m_pbyColorBar   = NULL;
}

CColorPickerDlg::~CColorPickerDlg()
{
	if( m_pbyColorPanel )
		delete m_pbyColorPanel;

	if( m_pbyColorBar )
		delete m_pbyColorBar;
}

void CColorPickerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorPickerDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColorPickerDlg, CDialog)
	//{{AFX_MSG_MAP(CColorPickerDlg)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_H_RDO, OnHueRdo)
	ON_BN_CLICKED(IDC_S_RDO, OnSaturationRdo)
	ON_BN_CLICKED(IDC_BRIGHT_RDO, OnBrightnessRdo)
	ON_BN_CLICKED(IDC_R_RDO, OnRedRdo)
	ON_BN_CLICKED(IDC_G_RDO, OnGreenRdo)
	ON_BN_CLICKED(IDC_B_RDO, OnBlueRdo)
	ON_EN_CHANGE(IDC_EDIT_BLUE, OnChangeEditBlue)
	ON_EN_CHANGE(IDC_EDIT_GREEN, OnChangeEditGreen)
	ON_EN_CHANGE(IDC_EDIT_RED, OnChangeEditRed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define REG_COLOR_PICKER (REG_TOOL_SAVE_SETTING _T("\\ColorPicker" ) )
BOOL CColorPickerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//m_enColorMode = (EColorMode)g_pApp->GetProfileInt( REG_COLOR_PICKER, _T("Mode"), 1 );
	m_enColorMode = enSaturation;
	CButton *pBtn;
	switch( m_enColorMode )
	{
	case enSaturation:
		pBtn = (CButton *)GetDlgItem( IDC_S_RDO );
		break;

	case enBrightness:
		pBtn = (CButton *)GetDlgItem( IDC_BRIGHT_RDO );
		break;

	case enBlue:
		pBtn = (CButton *)GetDlgItem( IDC_B_RDO );
		break;

	case enGreen:
		pBtn = (CButton *)GetDlgItem( IDC_G_RDO );
		break;

	case enRed:
		pBtn = (CButton *)GetDlgItem( IDC_R_RDO );
		break;

	default:
		m_enColorMode = enHue;

	case enHue:
		pBtn = (CButton *)GetDlgItem( IDC_H_RDO );
		break;
	}
	pBtn->SetCheck( 1 );

    RGBtoHSV( m_nRed, m_nGreen, m_nBlue, &m_nHue, &m_nSaturation, &m_nBrightness );
	CalcXYZ();
	UpdateEdit();
	
	return TRUE;
}

VOID CColorPickerDlg::SetColor( COLORREF crfColor )
{
	m_crfPrev = crfColor;
	m_crfCur = crfColor;
	m_nRed = GetRValue( crfColor ); 
	m_nGreen = GetGValue( crfColor );
	m_nBlue = GetBValue( crfColor );
	CalcXYZ();
	CalcColor();
	if( m_hWnd )
		UpdateEdit();
}

COLORREF CColorPickerDlg::GetColor()
{
	return m_crfCur;
}

COLORREF CColorPickerDlg::GetCurrentColor()
{
	return m_crfCur;
}

COLORREF CColorPickerDlg::GetPreviousColor()
{
	return m_crfCur;
}

VOID CColorPickerDlg::SetColorMode( EColorMode enMode )
{
	m_enInternalUpdate = m_enColorMode = enMode;
	m_bColorPanelModified = TRUE;
	m_bColorBarModified = TRUE;
	CalcXYZ();
	UpdateEdit();
	m_enInternalUpdate = enNone;
	InvalidateRect( NULL, FALSE );
}

void CColorPickerDlg::OnHueRdo() 
{
	SetColorMode( enHue );
}

void CColorPickerDlg::OnSaturationRdo() 
{
	SetColorMode( enSaturation );
}

void CColorPickerDlg::OnBrightnessRdo()
{
	SetColorMode( enBrightness );
}

void CColorPickerDlg::OnRedRdo() 
{
	SetColorMode( enRed );
}

void CColorPickerDlg::OnGreenRdo() 
{
	SetColorMode( enGreen );
}

void CColorPickerDlg::OnBlueRdo() 
{
	SetColorMode( enBlue );
}

void CColorPickerDlg::OnChangeEditBlue() 
{
	EColorMode	enOld;
	CString csz;
	if( m_enInternalUpdate )
		return;

	((CEdit *)GetDlgItem(IDC_EDIT_BLUE))->GetWindowText( csz );

	enOld = m_enInternalUpdate;
	m_enInternalUpdate = enGreen;
	
	m_nBlue = atoi( csz );
	CalcXYZ();
	CalcColor();
	UpdateEdit();
	InvalidateRect( NULL, FALSE );
	m_enInternalUpdate = enOld;
}

void CColorPickerDlg::OnChangeEditGreen() 
{
	EColorMode	enOld;
	CString csz;
	if( m_enInternalUpdate )
		return;

	((CEdit *)GetDlgItem(IDC_EDIT_GREEN))->GetWindowText( csz );
	
	enOld = m_enInternalUpdate;
	m_enInternalUpdate = enGreen;

	m_nGreen = atoi( csz );
	CalcXYZ();
	CalcColor();
	UpdateEdit();
	InvalidateRect( NULL, FALSE );
	m_enInternalUpdate = enOld;
}

void CColorPickerDlg::OnChangeEditRed() 
{
	EColorMode	enOld;
	CString csz;
	if( m_enInternalUpdate )
		return;

	((CEdit *)GetDlgItem(IDC_EDIT_RED))->GetWindowText( csz );

	enOld = m_enInternalUpdate;
	m_enInternalUpdate = enGreen;

	m_nRed = atoi( csz );
	CalcXYZ();
	CalcColor();
	UpdateEdit();
	InvalidateRect( NULL, FALSE );
	m_enInternalUpdate = enOld;
}

VOID CColorPickerDlg::CalcColor()
{
	switch( m_enColorMode )
	{
	case enRed:
		m_nRed    = m_z;
		m_nGreen  = m_y;
		m_nBlue   = m_x;
		
		RGBtoHSV( m_nRed, m_nGreen, m_nBlue, &m_nHue, &m_nSaturation, &m_nBrightness );
		break;

	case enGreen:
		m_nRed    = m_y;
		m_nGreen  = m_z;
		m_nBlue   = m_x;

		RGBtoHSV( m_nRed, m_nGreen, m_nBlue, &m_nHue, &m_nSaturation, &m_nBrightness );
		break;

	case enBlue:
		m_nRed    = m_y;
		m_nGreen  = m_x;
		m_nBlue   = m_z;

		RGBtoHSV( m_nRed, m_nGreen, m_nBlue, &m_nHue, &m_nSaturation, &m_nBrightness );
		break;

	case enHue:
		m_nHue		  = (INT)((m_z * 360.0f) / 256.0f);
		m_nSaturation = (INT)((m_x * 100.0f) / 256.0f);
		m_nBrightness = (INT)((m_y * 100.0f) / 256.0f);

		HuetoRGB( m_x, m_y, m_nHue, &m_nRed, &m_nGreen, &m_nBlue );
		break;

	case enSaturation:
		m_nHue		  = (INT)((m_x * 360.0f) / 256.0f);
		m_nSaturation = (INT)((m_z * 100.0f) / 256.0f);
		m_nBrightness = (INT)((m_y * 100.0f) / 256.0f);

		SaturationtoRGB( m_x, m_y, m_nSaturation, &m_nRed, &m_nGreen, &m_nBlue );
		break;

	case enBrightness:
		m_nHue		  = (INT)((m_x * 360.0f) / 256.0f);
		m_nSaturation = (INT)((m_y * 100.0f) / 256.0f);
		m_nBrightness = (INT)((m_z * 100.0f) / 256.0f);

		BrightnesstoRGB( m_x, m_y, m_nBrightness, &m_nRed, &m_nGreen, &m_nBlue );
	}

	m_crfCur = RGB( m_nRed, m_nGreen, m_nBlue );
}

VOID CColorPickerDlg::CalcXYZ()
{
	switch( m_enColorMode )
	{
	case enRed:
		m_z = m_nRed;
		m_y = m_nGreen;
		m_x = m_nBlue;
		break;

	case enGreen:
		m_y = m_nRed;
		m_z = m_nGreen;
		m_x = m_nBlue;
		break;

	case enBlue:
		m_y = m_nRed;
		m_x = m_nGreen;
		m_z = m_nBlue;
		break;

	case enHue:
		m_z = (m_nHue * 256) / 360;
		m_x = (m_nSaturation * 256) / 360;
		m_y = (m_nBrightness * 256) / 360;
		break;

	case enSaturation:
		m_x = (m_nHue * 256) / 360;
		m_z = (m_nSaturation * 256) / 360;
		m_y = (m_nBrightness * 256) / 360;
		break;

	case enBrightness:
		m_x = (m_nHue * 256) / 360;
		m_y = (m_nSaturation * 256) / 360;
		m_z = (m_nBrightness * 256) / 360;
	}
}

VOID CColorPickerDlg::SetColor( INT nRed, INT nGreen, INT nBlue )
{
	if( nRed >= 0 )
		m_nRed = nRed;

	if( nGreen >= 0 )
		m_nGreen = nGreen;

	if( nBlue >= 0 )
		m_nBlue = nBlue;

	RGBtoHSV( m_nRed, m_nGreen, m_nBlue, &m_nHue, &m_nSaturation, &m_nBrightness );
}

VOID CColorPickerDlg::UpdateEdit()
{
	CString csz;

	if( enRed != m_enInternalUpdate )
	{
		csz.Format( _T("%d"), m_nRed );
		((CEdit *)GetDlgItem(IDC_EDIT_RED))->SetWindowText( csz );
	}

	if( enGreen != m_enInternalUpdate )
	{
		csz.Format( _T("%d"), m_nGreen );
		((CEdit *)GetDlgItem(IDC_EDIT_GREEN))->SetWindowText( csz );
	}

	if( enBlue != m_enInternalUpdate )
	{
		csz.Format( _T("%d"), m_nBlue );
		((CEdit *)GetDlgItem(IDC_EDIT_BLUE))->SetWindowText( csz );
	}
	
	if( enHue != m_enInternalUpdate )
	{
		csz.Format( _T("%d"), m_nHue );
		((CEdit *)GetDlgItem(IDC_EDIT_HUE))->SetWindowText( csz );
	}

	if( enSaturation != m_enInternalUpdate )
	{
		csz.Format( _T("%d"), m_nSaturation );
		((CEdit *)GetDlgItem(IDC_EDIT_SATURATION))->SetWindowText( csz );
	}

	if( enBrightness != m_enInternalUpdate )
	{
		csz.Format( _T("%d"), m_nBrightness );
		((CEdit *)GetDlgItem(IDC_EDIT_BRIGHTNESS))->SetWindowText( csz );
	}

	csz.Format( _T("%02X%02X%02X"), m_nRed, m_nGreen, m_nBlue );
	((CEdit *)GetDlgItem(IDC_EDIT_HEXVALUE))->SetWindowText( csz );
}

void CColorPickerDlg::DrawStyle( CDC* pDC, const CRect& rct, const CRect& rctCur, const CRect& rctPrev )
{
	CBrush brush;
	brush.CreateSolidBrush( m_crfCur );
	pDC->FillRect( &rctCur, &brush );
	brush.DeleteObject();

	brush.CreateSolidBrush( m_crfPrev );
	pDC->FillRect( &rctPrev, &brush );
}

void CColorPickerDlg::OnPaint() 
{
	CDC			MemDC;
	CBitmap		Bm, *pOldBm;

	CPaintDC	dc( this );
	COLORREF	crf3dHilite = GetSysColor( COLOR_3DHILIGHT );
	COLORREF	crf3dShadow = GetSysColor( COLOR_3DDKSHADOW );
	CBrush		brBackGrnd( GetSysColor( COLOR_3DFACE ) );
	CRect		rctClnt;

	BITMAPINFOHEADER*	pBmh;
	PBYTE				pbyDibs;
	
	do
	{
		GetClientRect( &rctClnt );
		rctClnt.right = g_cnColorBarX + g_cnColorBarW + g_cnArrX * 2;
		rctClnt.bottom = g_cnMrnY + g_cnColorPanelH + g_cnArrY;
		if( FALSE == MemDC.CreateCompatibleDC( &dc ) ||
			FALSE == Bm.CreateCompatibleBitmap( &dc, rctClnt.Width(), rctClnt.Height() ) )
			break;

		pOldBm = MemDC.SelectObject( &Bm );

		MemDC.FillRect( &rctClnt, &brBackGrnd );

		// Draw Color Panel
		MemDC.Draw3dRect( g_cnMrnX - 1, g_cnMrnY - 1, g_cnColorPanelW + 2, g_cnColorPanelH + 2, crf3dShadow, crf3dHilite );
		if( m_bColorPanelModified )
		{
			ASSERT( FillColorPanel() );
			m_bColorPanelModified = FALSE;
		}
		pBmh = (BITMAPINFOHEADER*)m_pbyColorPanel;
		ASSERT( pBmh );

		pbyDibs = (PBYTE)pBmh + 40;
		StretchDIBits( MemDC.m_hDC, g_cnMrnX, g_cnMrnY, 256, 256, 0, 0, 256, 256, 
					   pbyDibs, (BITMAPINFO*)pBmh, DIB_RGB_COLORS, SRCCOPY );
		
		// Draw Color Bar
		CRect rct(  g_cnColorBarX - g_cnArrX * 2, g_cnColorBarY - g_cnArrY,
					g_cnColorBarX + g_cnColorBarW + g_cnArrX * 2, 
					g_cnColorBarY + g_cnColorBarH + g_cnArrY );
		MemDC.FillRect( &rct, &brBackGrnd );
		MemDC.Draw3dRect( g_cnColorBarX - 1, g_cnColorBarY - 1, g_cnColorBarW + 2, g_cnColorBarH + 2, crf3dShadow, crf3dHilite );

		if( m_bColorBarModified )
		{
			ASSERT( FillColorBar() );
			m_bColorBarModified = FALSE;
			pBmh = (BITMAPINFOHEADER*)FillColorBar();
		}

		pBmh = (BITMAPINFOHEADER*)m_pbyColorBar;
		ASSERT( pBmh );
		pbyDibs = (PBYTE)pBmh + 40;
		StretchDIBits( MemDC.m_hDC, g_cnColorBarX, g_cnColorBarY, g_cnColorBarW, g_cnColorBarH, 
					   0, 0, g_cnColorBarW, g_cnColorBarH,
					   pbyDibs, (BITMAPINFO*)pBmh, DIB_RGB_COLORS, SRCCOPY );

		// Draw Color Bar arrow pointer
		DrawPointer( &MemDC );

		// Draw Color Panel circle pointer
		{
			INT nR = 5;
			CBrush* pBm;
			HRGN hrgnClip, hrgnOld;
			INT	 nRgn, nResult;
			
			hrgnClip = CreateRectRgn( g_cnMrnX, g_cnMrnY, g_cnMrnX + g_cnColorPanelW, g_cnMrnY + g_cnColorPanelH );
			hrgnOld = CreateRectRgn( 1, 1, 10, 10 );
			ASSERT( hrgnClip && hrgnOld );

			nRgn = GetClipRgn( MemDC.m_hDC, hrgnOld );
			nResult = SelectClipRgn( MemDC.m_hDC, hrgnClip );
			ASSERT( ERROR != nResult );

			INT nOldROP = MemDC.SetROP2( R2_NOT );
			pBm = (CBrush*)MemDC.SelectStockObject( NULL_BRUSH );
			MemDC.Ellipse( g_cnMrnX + m_x - nR, g_cnMrnY + (255 - m_y) - nR, g_cnMrnX + m_x + nR, g_cnMrnY + (255 - m_y) + nR );
			MemDC.SelectObject( pBm );
			MemDC.SetROP2( nOldROP );
			
			if( 0 == nRgn )
				nResult = SelectClipRgn( MemDC.m_hDC, NULL );
			else
				nResult = SelectClipRgn( MemDC.m_hDC, hrgnOld );

			DeleteObject( hrgnOld );
			DeleteObject( hrgnClip );
		}

		brBackGrnd.DeleteObject();

		// Draw Current & Previous color Box
		{
			rct.SetRect( 0, 0, g_cnCurColorW, g_cnCurColorH );

			CMemDC MemDC;
			VERIFY( MemDC.Create( &dc, g_cnCurColorW, g_cnCurColorH ) );
			MemDC.Draw3dRect( &rct, crf3dShadow, crf3dHilite );

			rct.DeflateRect( 1, 1 );
			CRect rctCur = rct;
			CRect rctPrev = rct;

			rctCur.bottom /= 2;
			rctPrev.top = rctCur.bottom;
			DrawStyle( &MemDC, rct, rctCur, rctPrev );
			MemDC.BitBltTo( &dc, g_cnCurColorX, g_cnCurColorY, g_cnCurColorW, g_cnCurColorH );
		}
		
		dc.BitBlt( 0, 0, rctClnt.Width(), rctClnt.Height(), &MemDC, 0, 0, SRCCOPY );
		MemDC.SelectObject( pOldBm );
	}while(0);
}

void CColorPickerDlg::OnOK() 
{
	//g_pApp->WriteProfileInt( REG_COLOR_PICKER, _T("Mode"), m_enColorMode );
	CDialog::OnOK();
}

void CColorPickerDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( (nFlags & MK_LBUTTON) )
	{
		CRect rct;
  		if( 1 == m_nDrag )
		{
			// Check Color Bar rect
			m_z = point.y - g_cnColorBarY;

			if( m_z < 0 )
				m_z = 0;
			else if( m_z > 255 )
				m_z = 255;

			m_bColorPanelModified = TRUE;
			CalcColor();
			m_enInternalUpdate = m_enColorMode;
			UpdateEdit();
			m_enInternalUpdate = enNone;

			InvalidateRect( NULL, FALSE );
		}
		else if( 2 == m_nDrag )
		{
			// Check Color Panel Rect
			m_x = point.x - g_cnMrnX;
			m_y = point.y - g_cnMrnY;

			if( m_x < 0 )
				m_x = 0;
			else if( m_x > 256 )
				m_x = 255;

			if( m_y < 0 )
				m_y = 0;
			else if( m_y > 256 )
				m_y = 255;
			m_y = 255 - m_y;

			m_bColorBarModified = TRUE;
			CalcColor();
			m_enInternalUpdate = m_enColorMode;
			UpdateEdit();
			m_enInternalUpdate = enNone;

			InvalidateRect( NULL, FALSE );
		}
	}
	else
	{
		m_nDrag = 0;
		ReleaseCapture();
	}
}

void CColorPickerDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rct;

	// Check Color Bar rect
	rct.SetRect( g_cnColorBarX - 20, g_cnColorBarY,
				  g_cnColorBarX + g_cnColorBarW + g_cnArrX + 20,
				  g_cnColorBarY + g_cnColorBarH );
	if( rct.PtInRect( point ) )
	{
		m_bColorPanelModified = TRUE;
		m_z = point.y - g_cnColorBarY;
		m_nDrag = 1;
	}
	else
	{
		// Check Color Panel Rect
		rct.SetRect( g_cnMrnX, g_cnMrnY, g_cnMrnX + g_cnColorPanelW + 2, g_cnMrnY + g_cnColorPanelH + 2 );
		if( rct.PtInRect( point ) )
		{
			m_bColorBarModified = TRUE;
			m_x = point.x - g_cnMrnX;
			m_y = point.y - g_cnMrnY;
			m_y = 255 - m_y;
			m_nDrag = 2;
		}
	}
	if( m_nDrag )
	{
		CalcColor();
		m_enInternalUpdate = m_enColorMode;
		UpdateEdit();
		m_enInternalUpdate = enNone;

		ValidateRect( NULL );
		InvalidateRect( NULL, FALSE );
		SetCapture();
	}
}

void CColorPickerDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( m_nDrag )
	{
		m_nDrag = 0;
		ReleaseCapture();
	}
}

VOID CColorPickerDlg::DrawPointer( CDC* pDC )
{
	INT x, y;

	x = g_cnColorBarX - 2;
	y = g_cnColorBarY + m_z;

	pDC->MoveTo( x, y );
	pDC->LineTo( x - g_cnArrX, y - g_cnArrY );
	pDC->LineTo( x - g_cnArrX, y + g_cnArrY );
	pDC->LineTo( x, y );

	x = g_cnColorBarX + g_cnColorBarW + 1;

	pDC->MoveTo( x, y );
	pDC->LineTo( x + g_cnArrX, y - g_cnArrY );
	pDC->LineTo( x + g_cnArrX, y + g_cnArrY );
	pDC->LineTo( x, y );
}

BOOL CColorPickerDlg::FillColorPanel()
{
	switch( m_enColorMode ) 
	{
	case enRed:
	case enGreen:
	case enBlue:
		return FillRGBColorPanel();

	case enHue:
		return FillHueColorPanel();

	case enSaturation:
		return FillSaturationColorPanel();

	case enBrightness:
		return FillBrightnessColorPanel();
	}

	return FALSE;
}

BOOL CColorPickerDlg::FillColorBar()
{
	switch( m_enColorMode ) 
	{
	case enRed:
	case enGreen:
	case enBlue:
		return FillRGBColorBar();

	case enHue:
		return FillHueColorBar();

	case enSaturation:
		return FillSaturationColorBar();

	case enBrightness:
		return FillBrightnessColorBar();
	}

	return FALSE;
}

BOOL CColorPickerDlg::FillRGBColorBar()
{
	BOOL				bResult = FALSE;
	PBYTE				pbyBm = NULL;
	BITMAPINFOHEADER*	pBmh;
	PBYTE				pbyDibs;
	PBYTE				pbyX, pbyY, pbyZ;
	INT					nWidthBytes;
	INT					x, z, nX, nY;

	do
	{
		nWidthBytes = ((g_cnColorBarW * 24 + 31) / 32) * 4;
		if( NULL == m_pbyColorBar )
		{
			m_pbyColorBar = pbyBm = new BYTE[40 + 256 * nWidthBytes];
			if( NULL == pbyBm )
				break;
		}
		else
			pbyBm = m_pbyColorBar;

		pBmh = (BITMAPINFOHEADER*)pbyBm;
		ZeroMemory( pBmh, 40 );
		pBmh->biSize = 40;
		pBmh->biPlanes = 1;
		pBmh->biBitCount = 24;
		pBmh->biHeight = 256;
		pBmh->biWidth = g_cnColorBarW;

		pbyDibs = pbyBm + 40;

		switch( m_enColorMode ) 
		{
		case enRed:
			nX  = m_nBlue;
			nY  = m_nGreen;

			pbyX = pbyDibs;
			pbyY = pbyDibs + 1;
			pbyZ = pbyDibs + 2;
			break;

		case enGreen:
			nX  = m_nBlue;
			nY  = m_nRed;

			pbyX = pbyDibs;
			pbyY = pbyDibs + 2;
			pbyZ = pbyDibs + 1;
			break;

		case enBlue:
			nX  = m_nGreen;
			nY  = m_nRed;

			pbyX = pbyDibs + 1;
			pbyY = pbyDibs + 2;
			pbyZ = pbyDibs;
			break;

		default:
			ASSERT( FALSE );
		}

		for( z = 0; z < 256; z++ )
				{
			for( x = 0; x < g_cnColorBarW; x++ )
			{
				pbyX[x * 3] = nX;
				pbyY[x * 3] = nY;
				pbyZ[x * 3] = z;
			}
			pbyX += nWidthBytes;
			pbyY += nWidthBytes;
			pbyZ += nWidthBytes;
		}

		bResult = TRUE;
	}while(0);

	return bResult;
}

BOOL CColorPickerDlg::FillHueColorBar()
{
	BOOL				bResult = FALSE;
	PBYTE				pbyBm = NULL;
	BITMAPINFOHEADER*	pBmh;
	PBYTE				pbyDibs;
	INT					nWidthBytes;

	do
	{
		nWidthBytes = ((g_cnColorBarW * 24 + 31) / 32) * 4;
		if( NULL == m_pbyColorBar )
		{
			m_pbyColorBar = pbyBm = new BYTE[40 + 256 * nWidthBytes];
			if( NULL == pbyBm )
				break;
		}
		else
			pbyBm = m_pbyColorBar;

		pBmh = (BITMAPINFOHEADER*)pbyBm;
		ZeroMemory( pBmh, 40 );
		pBmh->biSize = 40;
		pBmh->biPlanes = 1;
		pBmh->biBitCount = 24;
		pBmh->biHeight = 256;
		pBmh->biWidth = g_cnColorBarW;

		pbyDibs = pbyBm + 40;
		PBYTE p;
		FLOAT h, f;
		INT r, g, b;
		INT i;

		for( INT y = 0; y < 256; y++ )
		{
			p = pbyDibs;
			
			h = (FLOAT)y * 360.0f / 256.0f;
			h = 360 - h;
			
			if (h < 0)
				h = 0;
			if (h >= 360)
				h = 0;
			
			h /= 60;
			f = (h - (int) h) * 255;
			
			r = g = b = 0;
			
			switch ((int) h)
			{
			case 2:
				r = 255;
				g = (INT)f;
				b = 0;
				break;

			case 3:
				r = 255 - (INT)f;
				g = 255;
				b = 0;
				break;

			case 4:
				r = 0;
				g = 255;
				b = (INT)f;
				break;

			case 5:
				r = 0;
				g = 255 - (INT)f;
				b = 255;
				break;

			case 0:
				r = (INT)f;
				g = 0;
				b = 255;
				break;

			case 1:
				r = 255;
				g = 0;
				b = 255 - (INT)f;
				break;
			}
			
			for( i = 0; i < g_cnColorBarW; i++ )
			{
				*p++ = r;
				*p++ = g;
				*p++ = b;
			}
			pbyDibs += nWidthBytes;
		}

		bResult = TRUE;
	}while(0);

	return bResult;
}

BOOL CColorPickerDlg::FillSaturationColorBar()
{
	BOOL				bResult = FALSE;
	PBYTE				pbyBm = NULL;
	BITMAPINFOHEADER*	pBmh;
	PBYTE				pbyDibs;
	INT					nWidthBytes;

	do
	{
		nWidthBytes = ((g_cnColorBarW * 24 + 31) / 32) * 4;
		if( NULL == m_pbyColorBar )
		{
			m_pbyColorBar = pbyBm = new BYTE[40 + 256 * nWidthBytes];
			if( NULL == pbyBm )
				break;
		}
		else
			pbyBm = m_pbyColorBar;

		pBmh = (BITMAPINFOHEADER*)pbyBm;
		ZeroMemory( pBmh, 40 );
		pBmh->biSize = 40;
		pBmh->biPlanes = 1;
		pBmh->biBitCount = 24;
		pBmh->biHeight = 256;
		pBmh->biWidth = g_cnColorBarW;

		pbyDibs = pbyBm + 40;

		PBYTE p = pbyDibs;
		FLOAT f, h, v, s, ds;
		INT	  i, nV;
			
		h = 360.0f - ((FLOAT)m_x * 360.0f / 256.0f);
		if (h < 0)
			h = 0;
		if (h > 359)
			h = 359;
		
		h /= 60;
		f = (h - (int) h) * 255.0f;

		v = (FLOAT)m_nBrightness / 100.0f;
		nV = (INT)(v * 256.0f);

		ds = 1.0 / 256;
		s = 0;
		for( INT y = 0; y < 256; y++ )
		{
			for( i = 0; i < g_cnColorBarW; i++ )
			{
				switch ((int) h)
				{
				case 2:
					*p++ = nV;
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					*p++ = (BYTE)(nV * (1 - s));
					break;
				
				case 3:
					*p++ = (BYTE)(v * (255 - s * f));
					*p++ = nV;
					*p++ = (BYTE)(nV * (1 - s));
					break;

				case 4:
					*p++ = (BYTE)(nV * (1 - s));
					*p++ = nV;
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					break;

				case 5:
					*p++ = (BYTE)(nV * (1 - s));
					*p++ = (BYTE)(v * (255 - s * f));
					*p++ = nV;
					break;

				case 0:
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					*p++ = (BYTE)(nV * (1 - s));
					*p++ = nV;
					break;

				case 1:
					*p++ = nV;
					*p++ = (BYTE)(nV * (1 - s));
					*p++ = (BYTE)(v * (255 - s * f));
					break;
				}
			}		
			s += ds;
		}

		bResult = TRUE;
	}while(0);

	return bResult;
}

BOOL CColorPickerDlg::FillBrightnessColorBar()
{
	BOOL				bResult = FALSE;
	PBYTE				pbyBm = NULL;
	BITMAPINFOHEADER*	pBmh;
	PBYTE				pbyDibs;
	INT					nWidthBytes;

	do
	{
		nWidthBytes = ((g_cnColorBarW * 24 + 31) / 32) * 4;
		if( NULL == m_pbyColorBar )
		{
			m_pbyColorBar = pbyBm = new BYTE[40 + 256 * nWidthBytes];
			if( NULL == pbyBm )
				break;
		}
		else
			pbyBm = m_pbyColorBar;

		pBmh = (BITMAPINFOHEADER*)pbyBm;
		ZeroMemory( pBmh, 40 );
		pBmh->biSize = 40;
		pBmh->biPlanes = 1;
		pBmh->biBitCount = 24;
		pBmh->biHeight = 256;
		pBmh->biWidth = g_cnColorBarW;

		pbyDibs = pbyBm + 40;

		PBYTE p;
		FLOAT f, h, v, dv, s;
		INT i;

		h = 360.0f - ((FLOAT)m_x * 360.0f / 256.0f);

		if (h < 0)
			h = 0;
		if (h > 359)
			h = 359;
		
		h /= 60;
		f = (h - (INT) h) * 255;
		
		p = pbyDibs;
		s = (FLOAT)m_nSaturation / 100.0f;
		dv = 1.0 / 256.0;
		v = 0;
		for( INT y = 0; y < 256; y++ )
		{
			for( i = 0; i < g_cnColorBarW; i++ )
			{
				switch ((int) h)
				{
				case 2:
					*p++ = y;
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					*p++ = (BYTE)(y * (1 - s));
					break;

				case 3:
					*p++ = (BYTE)(v * (255 - s * f));
					*p++ = y;
					*p++ = (BYTE)(y * (1 - s));
					break;

				case 4:
					*p++ = (BYTE)(y * (1 - s));
					*p++ = y;
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					break;

				case 5:
					*p++ = (BYTE)(y * (1 - s));
					*p++ = (BYTE)(v * (255 - s * f));
					*p++ = y;
					break;

				case 0:
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					*p++ = (BYTE)(y * (1 - s));
					*p++ = y;
					break;

				case 1:
					*p++ = y;
					*p++ = (BYTE)(y * (1 - s));
					*p++ = (BYTE)(v * (255 - s * f));
					break;
				}
				
			}
			v += dv;
		}

		bResult = TRUE;
	}while(0);

	return bResult;
}

BOOL CColorPickerDlg::FillRGBColorPanel()
{
	BOOL				bResult = FALSE;
	PBYTE				pbyBm;
	BITMAPINFOHEADER*	pBmh;
	PBYTE				pbyDibs;
	PBYTE				pbyX, pbyY;
	INT					nWidthBytes;
	INT					x, y, nValue;

	do
	{
		nWidthBytes = ((256 * 24 + 31) / 32) * 4;
		if( NULL == m_pbyColorPanel )
		{
			m_pbyColorPanel = pbyBm = new BYTE[40 + 256 * nWidthBytes];
			if( NULL == pbyBm )
				break;
		}
		else
			pbyBm = m_pbyColorPanel;

		pBmh = (BITMAPINFOHEADER*)pbyBm;
		ZeroMemory( pBmh, 40 );
		pBmh->biSize = 40;
		pBmh->biPlanes = 1;
		pBmh->biBitCount = 24;
		pBmh->biHeight = 256;
		pBmh->biWidth = 256;

		pbyDibs = pbyBm + 40;
		switch( m_enColorMode ) 
		{
		case enRed:
			pbyX = pbyDibs;
			pbyY = pbyDibs + 1;
			nValue = m_nRed;
			break;

		case enGreen:
			pbyX = pbyDibs;
			pbyY = pbyDibs + 2;
			nValue = m_nGreen;
			break;

		case enBlue:
			pbyX = pbyDibs + 1;
			pbyY = pbyDibs + 2;
			nValue = m_nBlue;
			break;

		default:
			ASSERT( FALSE );
		}

		memset( pbyDibs, nValue, 256 * nWidthBytes );
		for( y = 0; y < 256; y++ )
		{
			for( x = 0; x < 256; x++ )
			{
				pbyX[x * 3] = x;
				pbyY[x * 3] = y;
			}
			pbyX += nWidthBytes;
			pbyY += nWidthBytes;
		}

		bResult = TRUE;
	}while(0);

	return bResult;
}

VOID CColorPickerDlg::HuetoRGB( INT x, INT y, INT nHue, PINT pnR, PINT pnG, PINT pnB )
{
	FLOAT	h, v, dv, s;
	FLOAT	f;

	h = (FLOAT)nHue;
	if (h >= 360)
		h -= 360;
	h /= 60;
	f = (h - (INT)h) * 255.0f;

	dv = 1.0f / 256.0f;
	v = y * dv;
	s = x * dv;
	switch( nHue / 60 )
	{
	case 2:
		*pnB = y;
		*pnG = (BYTE)(v * (255 - (s * (255.0f - f))));
		*pnR = (BYTE)(y * (1 - s));
		break;

	case 3:
		*pnB = (BYTE)(v * (255.0f - s * f));
		*pnG = y;
		*pnR = (BYTE)(y * (1 - s));
		break;

	case 4:
		*pnB = (BYTE)(y * (1 - s));
		*pnG = y;
		*pnR = (BYTE)(v * (255 - (s * (255 - f))));		
		break;

	case 5:
		*pnB = (BYTE)(y * (1 - s));
		*pnG = (BYTE)(v * (255 - s * f));
		*pnR = y;
		break;

	case 0:
		*pnB = (BYTE)(v * (255 - (s * (255 - f))));
		*pnG = (BYTE)(y * (1 - s));
		*pnR = y;
		break;

	case 1:
		*pnB = y;
		*pnG = (BYTE)(y * (1 - s));
		*pnR = (BYTE)(v * (255 - s * f));
		break;
	}
}

BOOL CColorPickerDlg::FillHueColorPanel()
{
	BOOL				bResult = FALSE;
	PBYTE				pbyBm;
	BITMAPINFOHEADER*	pBmh;
	PBYTE				pbyDibs;
	INT					nWidthBytes;
	INT					y;
	
	do
	{
		nWidthBytes = 256 * 3;
		if( NULL == m_pbyColorPanel )
		{
			m_pbyColorPanel = pbyBm = new BYTE[40 + 256 * nWidthBytes];
			if( NULL == pbyBm )
				break;
		}
		else
			pbyBm = m_pbyColorPanel;
		
		pBmh = (BITMAPINFOHEADER*)pbyBm;
		ZeroMemory( pBmh, 40 );
		pBmh->biSize = 40;
		pBmh->biPlanes = 1;
		pBmh->biBitCount = 24;
		pBmh->biHeight = 256;
		pBmh->biWidth = 256;
		
		pbyDibs = pbyBm + 40;
		
		PBYTE	p = pbyDibs;
		FLOAT	h, v, dv, s;
		FLOAT	f;
		INT		i;

		h = (FLOAT)m_nHue;
		if (h >= 360)
			h -= 360;
		h /= 60;
		f = (h - (INT)h) * 255.0f;

		dv = 1.0 / 256;
		v = 0;
		switch( m_nHue/60 )
		{
		case 2:
			for( y = 0; y < 256; y++, v += dv )
			{
				s = 0;
				for ( i = 0; i < 256; i++ )
				{
					*p++ = y;
					*p++ = (BYTE)(v * (255 - (s * (255.0f - f))));
					*p++ = (BYTE)(y * (1 - s));
					s += dv;
				}
			}
			break;

		case 3:
			for( y = 0; y < 256; y++, v += dv )
			{
				s = 0;
				for( i = 0; i < 256; i++ )
				{
					*p++ = (BYTE)(v * (255.0f - s * f));
					*p++ = y;
					*p++ = (BYTE)(y * (1 - s));
					s += dv;
				}
			}
			break;

		case 4:
			for( y = 0; y < 256; y++, v += dv )
			{
				s = 0;
				for( i = 0; i < 256; i++ )
				{
					*p++ = (BYTE)(y * (1 - s));
					*p++ = y;
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));		
					s += dv;
				}
			}
			break;

		case 5:
			for( y = 0; y < 256; y++, v += dv )
			{
				s = 0;
				for( i = 0; i < 256; i++ )
				{
					*p++ = (BYTE)(y * (1 - s));
					*p++ = (BYTE)(v * (255 - s * f));
					*p++ = y;
					s += dv;
				}
			}
			break;

		case 0:
			for( y = 0; y < 256; y++, v += dv )
			{
				s = 0;
				for( i = 0; i < 256; i++ )
				{
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					*p++ = (BYTE)(y * (1 - s));
					*p++ = y;
					s += dv;
				}
			}
			break;

		case 1:
			for( INT y = 0; y < 256; y++, v += dv )
			{
				s = 0;
				for( i = 0; i < 256; i++ )
				{
					*p++ = y;
					*p++ = (BYTE)(y * (1 - s));
					*p++ = (BYTE)(v * (255 - s * f));
					s += dv;
				}
			}
			break;
		}

		bResult = TRUE;
	}while(0);

	return bResult;
}

VOID CColorPickerDlg::SaturationtoRGB( INT x, INT y, INT nSaturation, PINT pnR, PINT pnG, PINT pnB )
{
	FLOAT f, h, v, dv, s;
	
	s = (FLOAT)nSaturation / 100.0f;
	dv = 1.0 / 256.0;
	v = y * dv;

	h = 360.0f - ((FLOAT)x * 360.0f / 256.0f);
	if (h < 0)
		h = 0;
	if (h > 359)
		h = 359;
	
	h /= 60;
	f = (h - (INT) h) * 255;

	switch ((int) h)
	{
	case 2:
		*pnB = y;
		*pnG = (BYTE)(v * (255 - (s * (255 - f))));
		*pnR = (BYTE)(y * (1 - s));
		break;

	case 3:
		*pnB = (BYTE)(v * (255 - s * f));
		*pnG = y;
		*pnR = (BYTE)(y * (1 - s));
		break;

	case 4:
		*pnB = (BYTE)(y * (1 - s));
		*pnG = y;
		*pnR = (BYTE)(v * (255 - (s * (255 - f))));
		break;

	case 5:
		*pnB = (BYTE)(y * (1 - s));
		*pnG = (BYTE)(v * (255 - s * f));
		*pnR = y;
		break;

	case 0:
		*pnB = (BYTE)(v * (255 - (s * (255 - f))));
		*pnG = (BYTE)(y * (1 - s));
		*pnR = y;
		break;

	case 1:
		*pnB = y;
		*pnG = (BYTE)(y * (1 - s));
		*pnR = (BYTE)(v * (255 - s * f));
		break;
	}
}

BOOL CColorPickerDlg::FillSaturationColorPanel()
{
	BOOL				bResult = FALSE;
	PBYTE				pbyBm = NULL;
	BITMAPINFOHEADER*	pBmh;
	PBYTE				pbyDibs;
	INT					nWidthBytes;
	
	do
	{
		nWidthBytes = 256 * 3;
		if( NULL == m_pbyColorPanel )
		{
			m_pbyColorPanel = pbyBm = new BYTE[40 + 256 * nWidthBytes];
			if( NULL == pbyBm )
				break;
		}
		else
			pbyBm = m_pbyColorPanel;
		
		pBmh = (BITMAPINFOHEADER*)pbyBm;
		ZeroMemory( pBmh, 40 );
		pBmh->biSize = 40;
		pBmh->biPlanes = 1;
		pBmh->biBitCount = 24;
		pBmh->biHeight = 256;
		pBmh->biWidth = 256;
		
		pbyDibs = pbyBm + 40;
		
		PBYTE p;
		FLOAT f, h, v, dv, s;
		INT i;
		
		p = pbyDibs;
		s = (FLOAT)m_nSaturation / 100.0f;
		dv = 1.0 / 256.0;
		v = 0;
		for( INT y = 0; y < 256; y++ )
		{
			for( i = 0; i < 256; i++ )
			{
				h = 360.0f - ((FLOAT)i * 360.0f / 256.0f);

				if (h < 0)
					h = 0;
				if (h > 359)
					h = 359;
				
				h /= 60;
				f = (h - (INT) h) * 255;

				switch ((int) h)
				{
				case 2:
					*p++ = y;
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					*p++ = (BYTE)(y * (1 - s));
					break;

				case 3:
					*p++ = (BYTE)(v * (255 - s * f));
					*p++ = y;
					*p++ = (BYTE)(y * (1 - s));
					break;

				case 4:
					*p++ = (BYTE)(y * (1 - s));
					*p++ = y;
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					break;

				case 5:
					*p++ = (BYTE)(y * (1 - s));
					*p++ = (BYTE)(v * (255 - s * f));
					*p++ = y;
					break;

				case 0:
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					*p++ = (BYTE)(y * (1 - s));
					*p++ = y;
					break;

				case 1:
					*p++ = y;
					*p++ = (BYTE)(y * (1 - s));
					*p++ = (BYTE)(v * (255 - s * f));
					break;
				}
				
			}
			v += dv;
		}
		
		bResult = TRUE;
	}while(0);

	return bResult;
}

VOID CColorPickerDlg::BrightnesstoRGB( INT x, INT y, INT nBrightness, PINT pnR, PINT pnG, PINT pnB )
{
	FLOAT f, h, v, s, ds;
	INT	  nV;
		
	v = (FLOAT)nBrightness / 100.0f;
	nV = (INT)(v * 256.0f);

	ds = 1.0 / 256;
	s = y * ds;

	h = 360.0f - ((FLOAT)x * 360.0f / 256.0f);
	if (h < 0)
		h = 0;
	if (h > 359)
		h = 359;
	
	h /= 60;
	f = (h - (int) h) * 255.0f;

	switch ((int) h)
	{
	case 2:
		*pnB = nV;
		*pnG = (BYTE)(v * (255 - (s * (255 - f))));
		*pnR = (BYTE)(nV * (1 - s));
		break;
	
	case 3:
		*pnB = (BYTE)(v * (255 - s * f));
		*pnG = nV;
		*pnR = (BYTE)(nV * (1 - s));
		break;

	case 4:
		*pnB = (BYTE)(nV * (1 - s));
		*pnG = nV;
		*pnR = (BYTE)(v * (255 - (s * (255 - f))));
		break;

	case 5:
		*pnB = (BYTE)(nV * (1 - s));
		*pnG = (BYTE)(v * (255 - s * f));
		*pnR = nV;
		break;

	case 0:
		*pnB = (BYTE)(v * (255 - (s * (255 - f))));
		*pnG = (BYTE)(nV * (1 - s));
		*pnR = nV;
		break;

	case 1:
		*pnB = nV;
		*pnG = (BYTE)(nV * (1 - s));
		*pnR = (BYTE)(v * (255 - s * f));
		break;
	}
}

BOOL CColorPickerDlg::FillBrightnessColorPanel()
{
	BOOL				bResult = FALSE;
	PBYTE				pbyBm = NULL;
	BITMAPINFOHEADER*	pBmh;
	PBYTE				pbyDibs;
	INT					nWidthBytes;
	
	do
	{
		nWidthBytes = 256 * 3;
		if( NULL == m_pbyColorPanel )
		{
			m_pbyColorPanel = pbyBm = new BYTE[40 + 256 * nWidthBytes];
			if( NULL == pbyBm )
				break;
		}
		else
			pbyBm = m_pbyColorPanel;
		
		pBmh = (BITMAPINFOHEADER*)pbyBm;
		ZeroMemory( pBmh, 40 );
		pBmh->biSize = 40;
		pBmh->biPlanes = 1;
		pBmh->biBitCount = 24;
		pBmh->biHeight = 256;
		pBmh->biWidth = 256;
		
		pbyDibs = pbyBm + 40;
		
		PBYTE p = pbyDibs;
		FLOAT f, h, v, s, ds;
		INT	  i, nV;
			
		v = (FLOAT)m_nBrightness / 100.0f;
		nV = (INT)(v * 256.0f);

		ds = 1.0 / 256;
		s = 0;
		for( INT y = 0; y < 256; y++ )
		{
			for( i = 0; i < 256; i++ )
			{
				h = 360.0f - ((FLOAT)i * 360.0f / 256.0f);
				
				if (h < 0)
					h = 0;
				if (h > 359)
					h = 359;
				
				h /= 60;
				f = (h - (int) h) * 255.0f;

				switch ((int) h)
				{
				case 2:
					*p++ = nV;
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					*p++ = (BYTE)(nV * (1 - s));
					break;
				
				case 3:
					*p++ = (BYTE)(v * (255 - s * f));
					*p++ = nV;
					*p++ = (BYTE)(nV * (1 - s));
					break;

				case 4:
					*p++ = (BYTE)(nV * (1 - s));
					*p++ = nV;
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					break;

				case 5:
					*p++ = (BYTE)(nV * (1 - s));
					*p++ = (BYTE)(v * (255 - s * f));
					*p++ = nV;
					break;

				case 0:
					*p++ = (BYTE)(v * (255 - (s * (255 - f))));
					*p++ = (BYTE)(nV * (1 - s));
					*p++ = nV;
					break;

				case 1:
					*p++ = nV;
					*p++ = (BYTE)(nV * (1 - s));
					*p++ = (BYTE)(v * (255 - s * f));
					break;
				}
			}		
			s += ds;
		}

		bResult = TRUE;
	}while(0);

	return bResult;
}
