#include "stdafx.h"
#include <g\tools\eRectTool.h>
#include <g\type\idom\giRectElement.h>
#include <prop\PropRes.h>
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPL_GTPYECLASS_DYNCREATE( CGIRectElementTool, CGIElementTool, _T("RectElementTool") )
CGIRectElementTool::CGIRectElementTool()
{
	m_pgInstanceType = &GetClassType();

	m_nDefUIMode = RECT_TOOL_UI_MODE;
	m_nUIMode = RECT_TOOL_UI_MODE;
}

void CGIRectElementTool::DrawTracker( const PointF& rptfTopLeft, 
									  const PointF& rptfBottomRight, 
									  CDC& rDC, RECT& rRect )
{
	if( NULL == m_piElement )
		return;

	const INT cnPointCount = 4;
	PointF arptf[cnPointCount];
	GetHandlePoints( rptfTopLeft, rptfBottomRight, arptf, cnPointCount );

	Matrix mtx;
	GetElementScreenCTM( mtx );
	mtx.TransformPoints( arptf, cnPointCount );
	CPoint arpt[cnPointCount + 1];
	for( INT i = 0; i < cnPointCount; i++ )
	{
		arpt[i].x = (INT)arptf[i].X;
		arpt[i].y = (INT)arptf[i].Y;
	}

	arpt[cnPointCount] = arpt[0];
	rDC.Polyline( arpt, cnPointCount + 1 );
}

BOOL CGIRectElementTool::DrawTracker( CDC& rDC, RECT& rRect )
{
	if( NONE_UI_STATE == m_nUIState || TDT_NONE == m_nTrackerDrawType )
		return FALSE;

	// Draw XORing track rectangle
	CPen pen( PS_SOLID, 1, RGB(0,100,100) );
	CPen* pOldPen = rDC.SelectObject( &pen );
	INT nOldRop = rDC.SetROP2( R2_NOTXORPEN );

	BOOL bResult = TDT_DRAWN == m_nTrackerDrawType;	// Return FALSE if Track have not drawn yet
	if( TDT_END == m_nTrackerDrawType || TDT_DRAWN == m_nTrackerDrawType )	// Erase previous rectangle
		DrawTracker( m_ptfTrackTopLeft, m_ptfTrackBottomRight, rDC, rRect );

	if( TDT_END != m_nTrackerDrawType )
		DrawTracker( m_ptfTopLeft, m_ptfBottomRight, rDC, rRect );

	// Update points for erase
	m_ptfTrackTopLeft = m_ptfTopLeft;
	m_ptfTrackBottomRight = m_ptfBottomRight;
	m_nTrackerDrawType = TDT_DRAWN;

	rDC.SetROP2( nOldRop );
	rDC.SelectObject( pOldPen );
	return bResult;
}

BOOL CGIRectElementTool::Draw( CDC& rDC, RECT& rRect )
{
	if( NULL == m_piElement )
		return FALSE;

	// It can only be drawn for an Rectangle element 
	if( m_piElement->GetInstanceType() != CGIRectElement::GetClassType() )
		return FALSE;

	// For selection and UI state are none, there no is display
	if( NONE_UI_STATE == m_nUIState && FALSE == GetSelection() )
		return FALSE;

	if( NONE_UI_STATE == m_nUIState )
	{
		const INT cnPointCount = 8;
		PointF arptf[cnPointCount];
		GetHandlePoints( arptf, cnPointCount );

		Matrix mtx;
		GetElementScreenCTM( mtx );
		mtx.TransformPoints( arptf, cnPointCount );
		DrawHandleRect( rDC, rRect, arptf, cnPointCount );
	}
	else
	{
		DrawTracker( rDC, rRect );
		return TRUE;
	}

	return FALSE;
}

UINT CGIRectElementTool::HitTest( const CPoint& rpoint )
{
	switch( m_nUIState )
	{
	case NEW_UI_STATE:
	case MOVE_UI_STATE:
	case ROTATE_UI_STATE:
		return m_nHitTest;
	}

	if( NULL == m_piElement )
		return HT_NOTHING;

	CGIRectElement* piRectElement = (CGIRectElement*)m_piElement;

	const INT cnPointCount = 8;
	PointF arptf[cnPointCount];
	GetHandlePoints( arptf, cnPointCount );

	Matrix mtx;
	GetElementScreenCTM( mtx );
	mtx.TransformPoints( arptf, cnPointCount );

	PointF ptfScreen( (FLOAT)rpoint.x, (FLOAT)rpoint.y );

	RectF rctf( 0, 0, (FLOAT)m_nHandleSize, (FLOAT)m_nHandleSize );
	for( INT i = 0; i < cnPointCount; i++ )
	{
		rctf.X = arptf[i].X - (FLOAT)m_nHalfHandleSize;
		rctf.Y = arptf[i].Y - (FLOAT)m_nHalfHandleSize;

		if( rctf.Contains( ptfScreen ) )
			return i;
	}

	FLOAT w = piRectElement->m_aWidth;
	FLOAT h = piRectElement->m_aHeight;
	if( w || h )
	{
		PointF ptfElement = ptfScreen;
		mtx.Invert();	// Screen To Element
		mtx.TransformPoints( &ptfElement );

		RectF rctf( piRectElement->m_aX, piRectElement->m_aY, w, h );
		if( rctf.Contains( ptfElement ) )
			return HT_MIDDLE;
	}

	return HT_NOTHING; 
}

UINT CGIRectElementTool::HitTest( const Region& rrgn )
{
	switch( m_nUIState )
	{
	case NEW_UI_STATE:
	case MOVE_UI_STATE:
	case ROTATE_UI_STATE:
		return m_nHitTest;
	}

	if( NULL == m_piElement )
		return HT_NOTHING;

	CGIRectElement* piRectElement = (CGIRectElement*)m_piElement;
	RectF rctf( piRectElement->m_aX, piRectElement->m_aY, piRectElement->m_aWidth, piRectElement->m_aHeight );
	Region rgn( rctf );
	rgn.Intersect( &rrgn );

	HWND hWnd = GetDesktopWindow();
	Graphics gdip( hWnd );
	if( FALSE == rgn.IsEmpty( &gdip ) )
		return HT_ELEMENT;

	return HT_NOTHING; 
}

BOOL CGIRectElementTool::On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage )
{
	if( NONE_UI_STATE != m_nUIState )
		return TRUE;

	HINSTANCE hResInst = NULL;
	LPCTSTR pctszCursorID = NULL;
	if( HT_ROTATE == nHitTest || (nHitTest >= HT_TOPLEFT && nHitTest <= HT_MIDDLE) )
	{
		if( HT_ROTATE == nHitTest )
			pctszCursorID = IDC_UPARROW;
		else if( HT_MIDDLE == nHitTest )
			pctszCursorID = IDC_SIZEALL;
		else
			pctszCursorID = IDC_SIZEWE;
	}

	if( NULL == pctszCursorID && IsNewElementMode() )
	{
		pctszCursorID = MAKEINTRESOURCE(IDC_HAIR_CUR);
		hResInst = AfxFindResourceHandle( pctszCursorID, RT_GROUP_CURSOR );
	}

	if( pctszCursorID )
	{
		SetCursor( ::LoadCursor( hResInst, pctszCursorID ) );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIRectElementTool::OnMouseWheel( const CMouseEvent& rEvent )
{
	if( FALSE == GetSelection() )
		return FALSE;

	PointF ptf1( (FLOAT)rEvent.m_ptClient.x, (FLOAT)rEvent.m_ptClient.y );
	PointF ptf2 = ptf1;

	ptf2.Y += rEvent.m_zDelta;

	Matrix mtx;
	GetElementScreenCTM( mtx );
	mtx.TransformPoints( &ptf1 );
	mtx.TransformPoints( &ptf2 );

	PointF ptfOffset( ptf2.X - ptf1.X, ptf2.Y - ptf1.Y );

	CGIRectElement* piRectElement = (CGIRectElement*)m_piElement;
	piRectElement->m_aX = piRectElement->m_aX + ptfOffset.X;
	piRectElement->m_aY = piRectElement->m_aY + ptfOffset.Y;

	return TRUE;
}

BOOL CGIRectElementTool::OnLButtonDown( const CMouseEvent& rEvent )
{
	if( HT_NOTHING == m_nHitTest && IsNewElementMode() )
	{
		if( FALSE == BeginNewElement( CGIRectElement::ELEMENT_TAGNAME ) )
			return FALSE;
	}

	if( NULL == m_piElement )
		return FALSE;

	CGIRectElement* piRectElement = (CGIRectElement*)m_piElement;
	PointF ptf( (FLOAT)rEvent.m_ptClient.x, (FLOAT)rEvent.m_ptClient.y );

	Matrix mtx;
	GetElementScreenCTM( mtx );

	if( m_nHitTest >= HT_TOPLEFT && m_nHitTest <= HT_LEFT )
	{
		const INT cnPointCount = 8;
		PointF arptfRect[cnPointCount];
		GetHandlePoints( arptfRect, cnPointCount );

		INT arnIndex[cnPointCount][4] = {
			// BottomRight,	LeftTop		Chg-W,	Chg-H	Hit Point
			{  2,			0,			1,		1	},	// Top Left
			{  3,			1,			1,		1   },	// Top Right
			{  0,			2,			1,		1,	},	// Bottom Right
			{  1,			3,			1,		1	},	// Bottom Left
			{  2,			0,			0,		1   },	// Top
			{  0,			2,			1,		0	},	// Right
			{  0,			2,			0,		1   },	// Bottom
			{  2,			0,			1,		0   },	// Left
		};

		ptf = arptfRect[arnIndex[m_nHitTest][0]];
		m_ptfElementEnd = arptfRect[arnIndex[m_nHitTest][1]];
		m_ptfCurEnd = m_ptfBottomRight = m_ptfTrackBottomRight = m_ptfElementEnd;

		m_bChangeWidth = arnIndex[m_nHitTest][2];
		m_bChangeHeight = arnIndex[m_nHitTest][3];

		// Invalidate, SetCursor before update m_nUIState to erase Handles rect drawing
		InvalidateRect();	
		On_SetCursor( m_pwndView, HT_NOTHING, 0 ); 

		m_nToolModeCaps = TMC_CENTER | TMC_MOVE_TRACKER;
		switch( m_nHitTest )
		{
		case HT_TOPLEFT:
		case HT_TOPRIGHT:
		case HT_BOTTOMLEFT:
		case HT_BOTTOMRIGHT:
			m_nToolModeCaps |= TMC_SYMMETRIC;
		}
		
		goto LBNewRect;
	}
	else if( HT_MIDDLE == m_nHitTest )
	{
		m_ptfElementStart.X = piRectElement->m_aX;
		m_ptfElementStart.Y = piRectElement->m_aY;
		m_ptfTopLeft = m_ptfTrackTopLeft = m_ptfCurStart = m_ptfElementStart;

		m_ptfElementEnd.X = m_ptfElementStart.X + piRectElement->m_aWidth;
		m_ptfElementEnd.Y = m_ptfElementStart.Y + piRectElement->m_aHeight;
		m_ptfBottomRight = m_ptfTrackBottomRight = m_ptfCurEnd = m_ptfElementEnd;

		m_ptfStart.X = (FLOAT)rEvent.m_ptClient.x;
		m_ptfStart.Y = (FLOAT)rEvent.m_ptClient.y;

		mtx.Invert(); // Screen To Element
		mtx.TransformPoints( &m_ptfStart );

		// Invalidate, SetCursor before update m_nUIState to erase Handles rect drawing
		InvalidateRect(); 
		On_SetCursor( m_pwndView, HT_NOTHING, 0 ); 

		m_nUIState = MOVE_UI_STATE;
		m_nToolModeCaps = TMC_ANGLESNAP | TMC_MOVE_TRACKER;
		m_nHitTest= HT_MIDDLE;
		goto LBStartState;
	}
	
	mtx.Invert(); // Screen To Element
	mtx.TransformPoints( &ptf );
	m_ptfBottomRight = m_ptfTrackBottomRight = m_ptfCurStart = m_ptfElementEnd = ptf;

	m_bChangeWidth = TRUE;
	m_bChangeHeight = TRUE;
	m_nHitTest= HT_BOTTOMRIGHT;
	m_nToolModeCaps = TMC_SYMMETRIC | TMC_CENTER | TMC_MOVE_TRACKER;

LBNewRect:;
	m_nUIState = NEW_UI_STATE;
	m_ptfTopLeft = m_ptfTrackTopLeft = m_ptfCurStart = m_ptfElementStart = m_ptfCur = ptf;

LBStartState:;
	StartTracker();
	return TRUE;
}

BOOL CGIRectElementTool::OnMouseMove( const CMouseEvent& rEvent ) 
{
	if( NONE_UI_STATE == m_nUIState )
		return FALSE;

	if( NULL == m_piElement )
		return FALSE;

	PointF ptf( (FLOAT)rEvent.m_ptClient.x, (FLOAT)rEvent.m_ptClient.y );

	Matrix mtx;
	GetElementScreenCTM( mtx );
	mtx.Invert(); // Screen To Element
	mtx.TransformPoints( &ptf );

	m_ptfCursor = ptf;
	UpdateTracker();
	m_ptfCur = ptf;

	return TRUE;
}

BOOL CGIRectElementTool::OnLButtonUp( const CMouseEvent& rEvent )
{
	if( NONE_UI_STATE == m_nUIState )
		return FALSE;

	if( NULL == m_piElement )
		return FALSE;

	CGIRectElement* piRectElement = (CGIRectElement*)m_piElement;
	switch( m_nUIState )
	{
	case NEW_UI_STATE:{
		CGRectF grctf( m_ptfTopLeft, m_ptfBottomRight );
		grctf.NormalizeRect();
		piRectElement->m_aX = grctf.left;
		piRectElement->m_aY = grctf.top;

		piRectElement->m_aWidth = grctf.Width();
		piRectElement->m_aHeight = grctf.Height();
		}break;

	case MOVE_UI_STATE:
		piRectElement->m_aX = m_ptfTopLeft.X;
		piRectElement->m_aY = m_ptfTopLeft.Y;
		break;
	}

	EndTracker();
	return FALSE;
}

void CGIRectElementTool::UpdateTracker()
{
	if( NONE_UI_STATE == m_nUIState )
		return;

	if( NULL == m_piElement )
		return;

	m_ptfCurEnd = m_ptfCursor;

	UpdateMoveTrackerToolMode();
	UpdateAngleSnapToolMode();
	UpdateSymmetricToolMode();
	UpdateCenterToolMode();

	if( NEW_UI_STATE == m_nUIState )
	{
		m_ptfTopLeft = m_ptfElementStart;
		m_ptfBottomRight = m_ptfElementEnd;

		if( m_bChangeWidth )
		{
			m_ptfTopLeft.X = m_ptfCurStart.X;
			m_ptfBottomRight.X = m_ptfCurEnd.X;
		}

		if( m_bChangeHeight )
		{
			m_ptfTopLeft.Y = m_ptfCurStart.Y;
			m_ptfBottomRight.Y = m_ptfCurEnd.Y;
		}
	}
	else if( MOVE_UI_STATE == m_nUIState )
	{
		PointF ptfOffset( m_ptfCurEnd.X - m_ptfStart.X, m_ptfCurEnd.Y - m_ptfStart.Y );

		m_ptfTopLeft.X = m_ptfElementStart.X + ptfOffset.X;
		m_ptfTopLeft.Y = m_ptfElementStart.Y + ptfOffset.Y;

		m_ptfBottomRight.X = m_ptfElementEnd.X + ptfOffset.X;
		m_ptfBottomRight.Y = m_ptfElementEnd.Y + ptfOffset.Y;
	}

	UpdateTrackerDisplay();
}

void CGIRectElementTool::InvalidateRect( BOOL bHandle /*= FALSE*/ ) const
{
	if( NULL == m_piElement || NULL == m_pwndView )
		return;

	if( NONE_UI_STATE == m_nUIState && FALSE == GetSelection() )
		return;

	const INT cnPointCount = 4;
	PointF arptf[cnPointCount];
	Matrix mtx;
	GetElementScreenCTM( mtx );

	FLOAT fWidenPixelSize = 1;
	GraphicsPath gpath;
	if( bHandle || NONE_UI_STATE == m_nUIState )
	{
		if( bHandle )
			GetHandlePoints( m_ptfElementStart, m_ptfElementEnd, arptf, cnPointCount );
		else
			GetHandlePoints( arptf, cnPointCount );

		mtx.TransformPoints( arptf, cnPointCount );
		RectF grcf( 0, 0, (FLOAT)m_nHandleSize, (FLOAT)m_nHandleSize );
		for( INT i = 0; i < cnPointCount; i++ )
		{
			grcf.X = arptf[i].X - m_nHalfHandleSize; 
			grcf.Y = arptf[i].Y - m_nHalfHandleSize;
			gpath.AddRectangle( grcf );
		}
	}
	else
	{
		const INT cnPointCount = 4;
		const INT cnTrackCount = 2;
		const INT cnTrackPointCount = 2;
		const PointF* pparptf[cnTrackCount][cnTrackPointCount] = { 
			{ &m_ptfTrackTopLeft, &m_ptfTrackBottomRight },
			{ &m_ptfTopLeft, &m_ptfBottomRight },
		};

		for( INT i = 0; i < cnTrackCount; i++ )
		{
			GetHandlePoints( *pparptf[i][0], *pparptf[i][1], arptf, cnPointCount );
			mtx.TransformPoints( arptf, cnPointCount );

			gpath.AddLines( arptf, cnPointCount );
		}
	}

	if( fWidenPixelSize )
	{
		Pen gpen( Color::Black, fWidenPixelSize );
		gpath.Widen( &gpen, NULL );
	}

	RectF rctf;
	gpath.GetBounds( &rctf );
	CGIElementTool::InvalidateRect( &rctf );

	if( m_pwndView )
	{
		CClientDC dc( m_pwndView );
		Graphics gdip( dc.m_hDC );

		Pen gpen( Color::Red );
		if( 0 && bHandle )
		{
			gdip.DrawRectangle( &gpen, rctf );
			Sleep( 1000 );
		}
	}
}

void CGIRectElementTool::GetHandlePoints( PointF* pptf, INT nCount /*= 4*/ ) const 
{
	if( NONE_UI_STATE == m_nUIState )
	{
		if( NULL == m_piElement )
		{
			ASSERT( NULL );
			return;
		}

		CGIRectElement* piRectElement = (CGIRectElement*)m_piElement;
		FLOAT x = piRectElement->m_aX;
		FLOAT y = piRectElement->m_aY;

		FLOAT w = piRectElement->m_aWidth;
		FLOAT h = piRectElement->m_aHeight;

		PointF ptfTopLeft( x, y );
		PointF ptfBottomRight( x + w, y + h );
		GetHandlePoints( ptfTopLeft, ptfBottomRight, pptf, nCount );
	}
	else
		GetHandlePoints( m_ptfTopLeft, m_ptfBottomRight, pptf, nCount );
}

void CGIRectElementTool::GetHandlePoints( const PointF& rptfTopLeft, 
										  const PointF& rptfBottomRight, 
										  PointF* pptf, INT nCount /*= 4*/ ) const 
{
	if( nCount >= 4 )
	{
		pptf[0] = rptfTopLeft;			// topleft
																
		pptf[1].X = rptfBottomRight.X;	// topright.x
		pptf[1].Y = rptfTopLeft.Y;		// topright.y
													
		pptf[2] = rptfBottomRight;		// bottomright
													
		pptf[3].X = rptfTopLeft.X;		// bottomleft.x
		pptf[3].Y = rptfBottomRight.Y;	// bottomleft.y
	}

	if( nCount >= 8 )
	{
		pptf[4].X = (pptf[0].X + pptf[1].X) / 2;	// Left to Right - top middle
		pptf[4].Y = pptf[0].Y;

		pptf[5].X = pptf[1].X;						// Top to Bottom - right middle
		pptf[5].Y = (pptf[1].Y + pptf[2].Y) / 2;

		pptf[6].X = pptf[4].X;						// Left to Right - bottom middle
		pptf[6].Y = pptf[2].Y;

		pptf[7].X = pptf[0].X;						// Top to Bottom - left middle
		pptf[7].Y = pptf[5].Y;
	}
}

void CGIRectElementTool::GetTrackerPath( GraphicsPath& rgpath, const Matrix* pmtx /*= (Matrix*)-1*/ ) const
{
	if( NULL == m_piElement )
		return;

	Matrix mtx;
	if( (Matrix*)-1 == pmtx )
	{
		GetElementScreenCTM( mtx );
		pmtx = &mtx;
	}

	const INT cnPointCount = 4;
	PointF arptf[cnPointCount];
	GetHandlePoints( arptf, cnPointCount );
	if( pmtx )
		pmtx->TransformPoints( arptf, cnPointCount );
}