#include "stdafx.h"
#include <g\tools\eTool.h>
#include <g\type\idom\giDocument.h>
#include <g\tools\sTool.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPL_GTPYECLASS_DYNCREATE( CGIElementTool, CGIElementUITool, _T("ElementTool") )
CGIElementTool::CGIElementTool()
{
	m_pgInstanceType = &GetClassType();

	m_pNewElementParent = NULL;
	m_pSelTool = NULL;
	m_bSelection = NULL;

	SetHandleSize( 6 );

	m_cHandle = Color::White;
	m_cSelectedHandle = Color::Red;

	m_nToolMode = TMC_NONE;
	m_nToolModeCaps = TMC_NONE;

	m_nDragOrient = NONE_DRAG_ORIENT;

	m_bNewElementActive = FALSE;
	m_nTrackerDrawType = TDT_NONE;
}

CGIElementTool::~CGIElementTool()
{}

BOOL CGIElementTool::IsToolModeCaps( INT nIndex ) const {
	return 0 != (m_nToolModeCaps & nIndex); }

BOOL CGIElementTool::IsToolModeActive( INT nIndex ) const {
	return 0 != (m_nToolMode & nIndex); }

BOOL CGIElementTool::SetToolMode( INT nIndex, BOOL bSet /*= TRUE*/ )
{
	BOOL bOldMode = IsToolModeActive( nIndex );
	if( bSet )
		m_nToolMode |= nIndex;
	else
		m_nToolMode &= ~nIndex;

	return bOldMode;
}

void CGIElementTool::SetHandleSize( INT nSize ) 
{
	m_nHandleSize = nSize;
	m_nHalfHandleSize = m_nHandleSize / 2;
}

void CGIElementTool::SetHandleColor( const Color& rColor, BOOL bSelected /*= FALSE*/ ) 
{
	if( bSelected )
		m_cHandle = rColor; 
	else
		m_cSelectedHandle = rColor;
}

void CGIElementTool::DrawHandleRect( CDC& rDC, RECT& rRect, const PointF* pptf, INT nCount, BOOL bSelected /*= FALSE*/ )
{
	Graphics gdip( rDC.m_hDC );

	// Draw eight set of handle rectangles
	SolidBrush gbrush( bSelected ?m_cSelectedHandle :m_cHandle );
	Pen gpen( Color::Black );
	RectF grcf( 0, 0, (FLOAT)m_nHandleSize, (FLOAT)m_nHandleSize );

	for( INT i = 0; i < nCount; i++ )
	{
		grcf.X = pptf[i].X - m_nHalfHandleSize; 
		grcf.Y = pptf[i].Y - m_nHalfHandleSize;
		gdip.FillRectangle( &gbrush, grcf );
		gdip.DrawRectangle( &gpen, grcf );
	}
}

BOOL CGIElementTool::SetNewElementMode( BOOL bSet, CGIGroup* pParent /*= NULL*/ )
{
	if( bSet )
	{
		if( NULL == pParent )
			return FALSE;

		m_pNewElementParent = pParent;
	}
	else
		m_pNewElementParent = NULL;

	return TRUE;
}

INT CGIElementTool::GetDrawType() const 
{
	if( m_nDefUIMode != m_nUIMode )
		return CGIElementUITool::GetDrawType();

	return UPPER_DRAW_TYPE;
}

void CGIElementTool::InvalidateRect( RectF* pRect ) const
{
	CRect rect( (INT)floor( pRect->X ),
				(INT)floor( pRect->Y ), 
				(INT)ceil( pRect->X + pRect->Width ), 
				(INT)ceil( pRect->Y + pRect->Height ) );
	InvalidateRect( &rect );
}

void CGIElementTool::InvalidateRect( RECT* pRect ) const
{
	if( m_pwndView )
		m_pwndView->InvalidateRect( pRect, FALSE );
}

void CGIElementTool::InvalidateRect( BOOL bHandle /*= FALSE*/ ) const
{}

void CGIElementTool::UpdateWindow() const
{
	if( m_pwndView )
		m_pwndView->UpdateWindow();
}

void CGIElementTool::UpdateDisplay() const
{
	if( m_pwndView )
	{
		InvalidateRect();
		m_pwndView->UpdateWindow();
	}
}

BOOL CGIElementTool::DrawTracker( CDC& rDC, RECT& rRect ) {
	return FALSE; }

void CGIElementTool::UpdateTrackerDisplay()
{
	if( m_pwndView )
	{
		CClientDC dc( m_pwndView );
		CRect rctClient;
		m_pwndView->GetClientRect( rctClient );
		DrawTracker( dc, rctClient );
	}
}

BOOL CGIElementTool::BeginNewElement( LPCTSTR pctszTagName )
{
	if( FALSE == IsNewElementMode() )
		return FALSE;

	CGIDocument* pDocument = m_pNewElementParent->GetOwnerDocument();
	CGIShapeElement* pNewElement = (CGIShapeElement*)pDocument->CreateElement( pctszTagName );
	if( NULL == pNewElement )
		return FALSE;

	m_nHitTest = HT_NOTHING;	// Since starting new element at a new place
	m_pNewElementParent->AppendChild( *pNewElement );
	
	m_piElement = pNewElement;
	m_pSelTool->ChangeSelection( *pNewElement );
	m_bNewElementActive = TRUE;
	return TRUE;
}

void CGIElementTool::EndNewElement() {
	m_bNewElementActive = FALSE;
	m_nHitTest = HT_NOTHING; }

void CGIElementTool::GetTrackerPath( GraphicsPath& rgpath, const Matrix* pmtx /*= (Matrix*)-1*/ )
{}

void CGIElementTool::StartElementPoints()
{
	m_ptfElementCenter.X = (m_ptfElementStart.X + m_ptfElementEnd.X) / 2;
	m_ptfElementCenter.Y = (m_ptfElementStart.Y + m_ptfElementEnd.Y) / 2;

	m_nToolMode = TMC_NONE;
	m_nDragOrient = NONE_DRAG_ORIENT;
}

void CGIElementTool::UpdateCenterToolMode()
{
	if( IsToolModeActive( TMC_CENTER ) )
	{
		PointF ptfRadius(
			m_ptfCurEnd.X - m_ptfElementCenter.X,
			m_ptfCurEnd.Y - m_ptfElementCenter.Y );

		m_ptfCurStart.X = m_ptfElementCenter.X - ptfRadius.X;
		m_ptfCurStart.Y = m_ptfElementCenter.Y - ptfRadius.Y;
	}
	else
		m_ptfCurStart = m_ptfElementStart;
}	

#define ABS(x) (x >0 ?x :-x)
void CGIElementTool::UpdateSymmetricToolMode()
{
	if( FALSE == IsToolModeActive( TMC_SYMMETRIC ) )
		return;

	FLOAT fx = m_ptfCurEnd.X - m_ptfElementStart.X;
	FLOAT fy = m_ptfCurEnd.Y - m_ptfElementStart.Y;

	if( m_bNewElementActive )
	{
		if( ABS( fx ) > ABS( fy ) )
			m_ptfCurEnd.Y = m_ptfElementStart.Y + fx;
		else
			m_ptfCurEnd.X = m_ptfElementStart.X + fy;
	}
	else
	{
		FLOAT fex = m_ptfElementEnd.X - m_ptfElementStart.X;
		FLOAT fey = m_ptfElementEnd.Y - m_ptfElementStart.Y;

		FLOAT fmx = fx >= 0 ?1.f :-1.f;
		FLOAT fmy = fy >= 0 ?1.f :-1.f;

		FLOAT fr;
		if( ABS( fx ) > ABS( fy ) )
		{
			fr = ABS( fx ) / fex;
			m_ptfCurEnd.Y = m_ptfCurStart.Y + fmy * fr * fey;
			m_ptfCurEnd.X = m_ptfCurStart.X + fmx * fr * fex;
		}
		else
		{
			fr = ABS( fy ) / fey;
			m_ptfCurEnd.X = m_ptfCurStart.X + fmx * fr * fex;
			m_ptfCurEnd.Y = m_ptfCurStart.Y + fmy * fr * fey;
		}
	}
}	

static BOOL Snap( FLOAT& rpf, BOOL bEndPoint = FALSE )
{
	/*if( FALSE == IsSnap() )
		return FALSE;

	FLOAT f = rpf;
	FLOAT fDiv = m_sViewGrid.v.fMajorDiv;
	FLOAT fSnap = fDiv / 3.0f;
	if( m_sViewGrid.bMinor )
	{
		fDiv = m_sViewGrid.v.fMinorDiv;
		fSnap = fDiv / 3.0f;
	}

	if( ms_fViewSnapCs < fSnap )
		fSnap = ms_fViewSnapCs;

	FLOAT fMin = ((INT)(f / fDiv)) * fDiv;
	FLOAT fMax = ((INT)((f + fDiv - 0.9f) / fDiv)) * fDiv;

	FLOAT fdMin = f - fMin;
	FLOAT fdMax = fMax - f;

	BOOL bResult = FALSE;
	if( fdMin < fdMax )
	{
		if( fdMin < fSnap )
		{
			rpf = fMin;
			bResult = TRUE;
		}
	}
	else
	{
		if( fdMax < fSnap )
		{
			rpf = fMax;
			bResult = TRUE;
		}
	}

	if( bResult && bEndPoint )
	{
		f = rpf;
		FLOAT fPrev = ((INT)((f - fDiv + 0.9f) / fDiv)) * fDiv;
		fPrev += fDiv - 1.0f;
		//rpf = fPrev;
	}

	return bResult;*/
	return FALSE;
}

static BOOL SnapX( FLOAT& rpx, BOOL bEndPoint = FALSE )
{
	/*if( m_ruler.m_bGuideVisible && m_ruler.m_bGuideSnap )
	{
		FLOAT X = rpx;
		INT nCount = m_ruler.m_arfVGuide.GetSize();
		FLOAT* pfGuide = (FLOAT*)m_ruler.m_arfVGuide.GetData();
		for( INT i = 0; i < nCount; i++ )
		{
			FLOAT fDist = abs( X - pfGuide[i] );
			if( fDist < ms_fViewSnapCs )
			{
				rpx = pfGuide[i];
				return TRUE;
			}
		}
	}*/
				
	return Snap( rpx, bEndPoint );
}

static BOOL SnapY( FLOAT& rpy, BOOL bEndPoint = FALSE )
{
	/*if( m_ruler.m_bGuideVisible && m_ruler.m_bGuideSnap )
	{
		FLOAT Y = rpy;
		INT nCount = m_ruler.m_arfHGuide.GetSize();
		FLOAT* pfGuide = (FLOAT*)m_ruler.m_arfHGuide.GetData();
		for( INT i = 0; i < nCount; i++ )
		{
			FLOAT fDist = abs( Y - pfGuide[i] );
			if( fDist < ms_fViewSnapCs )
			{
				rpy = pfGuide[i];
				return TRUE;
			}
		}
	}*/

	return Snap( rpy, bEndPoint );
}

static BOOL Snap( PointF& rpptf, BOOL bEndPoint = FALSE )
{
	return FALSE;
	BOOL bResult  = SnapX( rpptf.X, bEndPoint );
		 bResult |= SnapY( rpptf.Y, bEndPoint );

	return bResult;
}

const DOUBLE c_dPI = 3.1415926535;
static BOOL SnapAlongAngle( PointF& rpptf, FLOAT fTheta, BOOL bEndPoint = FALSE )
{
	PointF ptfNew = rpptf;
	BOOL bResult = Snap( ptfNew, bEndPoint );	// Find snap point for given point rpptf
	if( bResult )
	{
		// Extend the given point rpptf in the direction fTheta upto nearest point ptfNew
		PointF ptfOffset = ptfNew - rpptf;
		FLOAT fRadian = (FLOAT)(fTheta * c_dPI) / 180.0f;
		FLOAT fCosTheta = (FLOAT)cos( fRadian );
		FLOAT fSinTheta = (FLOAT)sin( fRadian );

		if( ptfOffset.X < ptfOffset.Y )
			ptfOffset.Y = -ptfOffset.X * fSinTheta / fCosTheta;
		else
			ptfOffset.X = -ptfOffset.Y * fCosTheta / fSinTheta;

		rpptf.X += ptfOffset.X;
		rpptf.Y += ptfOffset.Y;
	}

	return bResult;
}

static inline FLOAT CalcAngleSnapUpperQuad( FLOAT fCosTheta )
{
	FLOAT fTheta = 0;
	if( 0 == fCosTheta )	// Equal to 90
		fTheta = 90;
	else if( fCosTheta > 0 )	// Less than 90 deg
	{
		if( fCosTheta > 0.64278760 )	// Less than 50 deg
		{
			if( fCosTheta > 0.7660 )	// Less than 35 deg
			{
				if( fCosTheta > 0.939692620 )	// Less than 20 deg
				{
					if( fCosTheta >= 0.9961946980 ) // Less than 5 deg
						fTheta += 0;
					else // Greater than equal to 5 deg and less than 20
						fTheta += 15;
				}
				else // Greater than equal to 20 deg and less than 35
					fTheta += 30;
			}
			else // Greater than equal to 35 deg and less than 50
				fTheta += 45;
		}
		else // Greater than equal to 50 deg and less than 90
		{
			if( fCosTheta > 0.173648177666930 )	// Less than 80 deg
			{
				if( fCosTheta > 0.422618261740 )	// Less than 65 deg
				{
					if( fCosTheta >= 0.64278760 ) // Less than 50 deg
						fTheta += 45;
					else // Greater than equal to 50 deg and less than 65
						fTheta += 60;
				}
				else // Greater than equal to 65 deg and less than 80
					fTheta += 75;
			}
			else // Greater than equal to 80 deg and less than 90
				fTheta += 90;
		}
	}

	return fTheta;
}

static inline FLOAT CalcAngleSnap( FLOAT fCosTheta )
{
	FLOAT fTheta = 0;
	if( 0 == fCosTheta )	// Equal to 90
		fTheta = 90;
	else if( fCosTheta < 0 )	// Greater than 90
		fTheta = 180 - CalcAngleSnapUpperQuad( -fCosTheta );
	else 
		fTheta = CalcAngleSnapUpperQuad( fCosTheta );

	return fTheta;
}

static FLOAT CalcAngleSnap( const PointF& rptfStart, const PointF& rptfEnd, PointF& rptfNew )
{
	FLOAT fDistX = rptfEnd.X - rptfStart.X;
	FLOAT fDistY = rptfEnd.Y - rptfStart.Y;
	FLOAT fDist;
	FLOAT fCosTheta;
	FLOAT fSinTheta;
	FLOAT fTheta = 0;

	if( 0 == fDistY )	// delta Y dist is zero
	{
		if( fDistX > 0 )	// Angle is zero
		{
			fDist = fDistX;
			fTheta = 0;
		}
		else				// Angle is 180
		{
			fDist = -fDistX;
			fTheta = 180;
		}
	}
	else if( 0 == fDistX )	// delta X dist is zero
	{
		if( fDistY > 0 )	// Angle is 270
		{
			fDist = fDistY;
			fTheta = 270;
		}
		else				// Angle is 90
		{
			fDist = -fDistY;
			fTheta = 90;
		}
	}
	else				// delta X and Y are not zero
	{
		fDist = (FLOAT)sqrt( (DOUBLE)(fDistX * fDistX) + (DOUBLE)(fDistY * fDistY) );
		fCosTheta = fDistX / fDist;
		if( fDistY > 0 )
			fTheta = 360 - ::CalcAngleSnap( fCosTheta );
		else
			fTheta = ::CalcAngleSnap( fCosTheta );
	}

	rptfNew = rptfStart;

	if( 0.0f == fTheta || 360.0f == fTheta )
		rptfNew.X += fDist;
	else if( 90.0f == fTheta )
		rptfNew.Y += -fDist;
	else if( 180.0f == fTheta )
		rptfNew.X += -fDist;
	else if( 270.0f == fTheta )
		rptfNew.Y += fDist;
	else
	{
		FLOAT fRadian = (FLOAT)(fTheta * c_dPI) / 180.f;
		fCosTheta = (FLOAT)cos( fRadian );
		fSinTheta = (FLOAT)sin( fRadian );

		rptfNew.X += fCosTheta * fDist;
		rptfNew.Y -= fSinTheta * fDist;
	}

	return fTheta;
}

void CGIElementTool::UpdateAngleSnapToolMode()
{
	if( FALSE == IsToolModeActive( TMC_ANGLESNAP ) )
		return;

	FLOAT fTheta = ::CalcAngleSnap( m_ptfCurStart, m_ptfCursor, m_ptfCurEnd );
	//if( IsSnap() )
		//SnapAlongAngle( m_ptfCurEnd, fTheta );
}

void CGIElementTool::StartOrientToolMode()
{
	if( FALSE == IsToolModeCaps( TMC_ORIENT ) || NONE_DRAG_ORIENT != m_nDragOrient )
		return;

	FLOAT fX = m_ptfScreenStart.X - m_ptfScreenCursor.X;
	FLOAT fY = m_ptfScreenStart.Y - m_ptfScreenCursor.Y;
	if( fX != fY )
	{
		if( ABS( fX ) > ABS( fY ) )
			m_nDragOrient = HORZ_DRAG_ORIENT;
		else
			m_nDragOrient = VERT_DRAG_ORIENT;
	}
}

static FLOAT cs_fDragOrientBreakSize  = 30.f;
void CGIElementTool::UpdateOrientToolMode()
{
	if( TMC_NONE == m_nDragOrient || FALSE == IsToolModeActive( TMC_ORIENT ) )
		return;

	PointF ptfNewCursor = m_ptfScreenCursor;
	PointF ptfOffset( m_ptfScreenCursor.X - m_ptfScreenStart.X,
					  m_ptfScreenCursor.Y - m_ptfScreenStart.Y );

	switch( m_nDragOrient )
	{
	case HORZ_DRAG_ORIENT:
		if( ABS( ptfOffset.Y ) < cs_fDragOrientBreakSize )
			ptfNewCursor.Y = m_ptfScreenStart.Y;
		break;
	
	case VERT_DRAG_ORIENT:
		if( ABS( ptfOffset.X ) < cs_fDragOrientBreakSize )
			ptfNewCursor.X = m_ptfScreenStart.X;
		break;
	}

	// Convert point Screen to Element
	Matrix mtx;
	m_piElement->GetScreenCTM( mtx );
	mtx.Invert(); // Screen To Element
	mtx.TransformPoints( &ptfNewCursor );

	m_ptfCurEnd = ptfNewCursor;
}

BOOL CGIElementTool::UpdateMoveTrackerToolMode()
{
	if( FALSE == IsToolModeActive( TMC_MOVE_TRACKER ) )
		return FALSE;
	
	PointF ptfOffset( 
		m_ptfCursor.X - m_ptfCur.X,
		m_ptfCursor.Y - m_ptfCur.Y );

   	m_ptfCurStart.X += ptfOffset.X;
	m_ptfCurStart.Y += ptfOffset.Y;
	
	m_ptfCurEnd.X += ptfOffset.X;
	m_ptfCurEnd.Y += ptfOffset.Y;

	m_ptfElementStart.X += ptfOffset.X;
	m_ptfElementStart.Y += ptfOffset.Y;
	
	m_ptfElementEnd.X += ptfOffset.X;
	m_ptfElementEnd.Y += ptfOffset.Y;

	m_ptfElementCenter.X += ptfOffset.X;
	m_ptfElementCenter.Y += ptfOffset.Y;

	m_ptfStart.X += ptfOffset.X;
	m_ptfStart.Y += ptfOffset.Y;
	
  	MoveTracker( ptfOffset );
	return TRUE;
}

void CGIElementTool::MoveTracker( const PointF& rptfOffset )
{}

void CGIElementTool::UpdateTracker()
{}

void CGIElementTool::StartTracker()
{
	StartElementPoints();
	UpdateDisplay();
	
	m_nTrackerDrawType = TDT_START;
	UpdateTrackerDisplay();
	
	if( m_pwndView )
		m_pwndView->SetCapture();
}

void CGIElementTool::EndTracker()
{
	UINT nKey;
	INT arnMode[] = {
		TMC_MOVE_TRACKER,
		TMC_ORIENT,
		TMC_ANGLESNAP,
		TMC_SYMMETRIC,
		TMC_CENTER
	};	

	INT nMode, nModeCount = sizeof(arnMode) / sizeof(INT);
	for( INT i = 0; i < nModeCount; i++ )
	{
		nMode = arnMode[i];
		if( IsToolModeActive( nMode ) )
		{
			nKey = GetToolModeKey( nMode );
			SetToolMode( nMode, FALSE );
            VERIFY( RemoveListenKeyState( nKey, FALSE ) );
		}
	}

	if( IsNewElementMode() )
		EndNewElement();
	
	InvalidateRect( TRUE );			// Handle Rect
	
	m_nTrackerDrawType = TDT_END;	// Erase Tracker
	UpdateTrackerDisplay();
	m_nTrackerDrawType = TDT_NONE;	// Tracking completed
	
	m_nUIState = NONE_UI_STATE;
	InvalidateRect();				// Handles Rect
	
	if( m_pwndView && m_pwndView == m_pwndView->GetCapture() )
		ReleaseCapture();
}

BOOL CGIElementTool::IsToolModeKey( INT nMode, UINT nChar ) 
{
	UINT nToolModeKey = GetToolModeKey( nMode );
	if( nToolModeKey && nToolModeKey == nChar )
		return TRUE;

	return FALSE; 
}

UINT CGIElementTool::GetToolModeKey( INT nMode )
{
	switch( nMode )
	{
	case TMC_MOVE_TRACKER:
		return VK_SPACE;

	case TMC_ORIENT:
		return VK_SHIFT;

	case TMC_ANGLESNAP:
		return VK_SHIFT;

	case TMC_SYMMETRIC:
		return VK_SHIFT;

	case TMC_CENTER:
		return VK_MENU;
	}

	return 0;
}

BOOL CGIElementTool::OnKeyDown( const CKbdEvent& rEvent )
{
	if( NONE_UI_STATE == m_nUIState )
		return FALSE;

	INT arnMode[] = {
		TMC_MOVE_TRACKER,
		TMC_ORIENT,
		TMC_ANGLESNAP,
		TMC_SYMMETRIC,
		TMC_CENTER
	};	

	INT nMode, nModeCount = sizeof(arnMode) / sizeof(INT);
	for( INT i = 0; i < nModeCount; i++ )
	{
		nMode = arnMode[i];
		if( IsToolModeCaps( nMode )
			&& IsToolModeKey( nMode, rEvent.m_nKey )
			&& FALSE == IsToolModeActive( nMode ) )
		{
 			SetToolMode( nMode );
			UpdateTracker();
			VERIFY( AddListenKeyState( rEvent.m_nKey, FALSE ) );
			return TRUE;
		}
	}

	return TRUE;
}

BOOL CGIElementTool::OnKeyUp( const CKbdEvent& rEvent )
{
	if( NONE_UI_STATE == m_nUIState )
		return FALSE;

	INT arnMode[] = {
		TMC_MOVE_TRACKER,
		TMC_ORIENT,
		TMC_ANGLESNAP,
		TMC_SYMMETRIC,
		TMC_CENTER
	};	

	INT nMode, nModeCount = sizeof(arnMode) / sizeof(INT);
	for( INT i = 0; i < nModeCount; i++ )
	{
		nMode = arnMode[i];
		if( IsToolModeActive( nMode )
		 && IsToolModeKey( nMode, rEvent.m_nKey ) )
		{
			SetToolMode( nMode, FALSE );
			UpdateTracker();
			VERIFY( RemoveListenKeyState( rEvent.m_nKey, FALSE ) );
			return TRUE;
		}
	}

	return TRUE;
}

