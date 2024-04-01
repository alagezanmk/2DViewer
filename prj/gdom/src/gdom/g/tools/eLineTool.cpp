#include "stdafx.h"
#include <g\tools\eLineTool.h>
#include <g\type\idom\giLineElement.h>
#include <prop\PropRes.h>
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPL_GTPYECLASS_DYNCREATE( CGILineElementTool, CGIElementTool, _T("LineElementTool") )
CGILineElementTool::CGILineElementTool()
{
	m_pgInstanceType = &GetClassType();

	m_nDefUIMode = LINE_TOOL_UI_MODE;
	m_nUIMode = LINE_TOOL_UI_MODE;
}

void CGILineElementTool::DrawTracker( const PointF& rptfStart, 
									  const PointF& rptfEnd, 
									  CDC& rDC, RECT& rRect )
{
	if( NULL == m_piElement )
		return;

	const INT cnPointCount = 2;
	PointF arptf[cnPointCount];
	GetHandlePoints( rptfStart, rptfEnd, arptf );

	Matrix mtx;
	GetElementScreenCTM( mtx );
	mtx.TransformPoints( arptf, cnPointCount );

	CPoint arpt[cnPointCount];
	for( INT i = 0; i < cnPointCount; i++ )
	{
		arpt[i].x = (INT)arptf[i].X;
		arpt[i].y = (INT)arptf[i].Y;
	}

	rDC.Polyline( arpt, cnPointCount );
}

BOOL CGILineElementTool::DrawTracker( CDC& rDC, RECT& rRect )
{
	if( NONE_UI_STATE == m_nUIState || TDT_NONE == m_nTrackerDrawType )
		return FALSE;

	// Draw XORing track rectangle
	CPen pen( PS_SOLID, 1, RGB(0,100,100) );
	CPen* pOldPen = rDC.SelectObject( &pen );
	INT nOldRop = rDC.SetROP2( R2_NOTXORPEN );

	BOOL bResult = TDT_DRAWN == m_nTrackerDrawType;	// Return FALSE if Track have not drawn yet
	if( TDT_END == m_nTrackerDrawType || TDT_DRAWN == m_nTrackerDrawType )	// Erase previous rectangle
		DrawTracker( m_ptfTrackStart, m_ptfTrackEnd, rDC, rRect );

	if( TDT_END != m_nTrackerDrawType )
		DrawTracker( m_ptfLineStart, m_ptfLineEnd, rDC, rRect );

	// Update points for erase
	m_ptfTrackStart = m_ptfLineStart;
	m_ptfTrackEnd = m_ptfLineEnd;
	m_nTrackerDrawType = TDT_DRAWN;

	rDC.SetROP2( nOldRop );
	rDC.SelectObject( pOldPen );
	return bResult;
}

BOOL CGILineElementTool::Draw( CDC& rDC, RECT& rRect )
{
	if( NULL == m_piElement )
		return FALSE;

	// It can only be drawn for an Line element 
	if( m_piElement->GetInstanceType() != CGILineElement::GetClassType() )
		return FALSE;

	// For selection and UI state are none, there no is display
	if( NONE_UI_STATE == m_nUIState && FALSE == GetSelection() )
		return FALSE;

	if( NONE_UI_STATE == m_nUIState )
	{
		const INT cnPointCount = 2;
		PointF arptf[cnPointCount];
		GetHandlePoints( arptf );

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

UINT CGILineElementTool::HitTest( const CPoint& rpoint )
{
	switch( m_nUIState )
	{
	case FIRST_POINT_DRAG_UI_STATE:
	case SECOND_POINT_DRAG_UI_STATE:
	case MOVE_UI_STATE:
		return m_nHitTest;
	}

	if( NULL == m_piElement )
		return HT_NOTHING;

	CGILineElement* pLineElement = (CGILineElement*)m_piElement;

	const INT cnPointCount = 2;
	PointF arptf[cnPointCount];
	GetHandlePoints( arptf );

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
			return HT_FIRSTPOINT + i;
	}

	GraphicsPath gpath;
	gpath.AddLines( arptf, cnPointCount );

	Pen gpen( Color::Black, 2.f );
	gpath.Widen( &gpen );

	if( gpath.IsVisible( ptfScreen ) )
		return HT_LINE;

	return HT_NOTHING; 
}

UINT CGILineElementTool::HitTest( const Region& rrgn )
{
	switch( m_nUIState )
	{
	case FIRST_POINT_DRAG_UI_STATE:
	case SECOND_POINT_DRAG_UI_STATE:
	case MOVE_UI_STATE:
		return m_nHitTest;
	}

	if( NULL == m_piElement )
		return HT_NOTHING;

	const INT cnPointCount = 2;
	PointF arptf[cnPointCount];
	GetHandlePoints( arptf );

	GraphicsPath gpath;
	gpath.AddLines( arptf, cnPointCount );
	Pen gpen( Color::Black, 6.f );
	gpath.Widen( &gpen );

	Region rgn;
	rgn.Union( &rrgn );
	rgn.Intersect( &gpath );

	HWND hWnd = GetDesktopWindow();
	Graphics gdip( hWnd );
	if( FALSE == rgn.IsEmpty( &gdip ) )
		return HT_LINE;

	return HT_NOTHING; 
}

BOOL CGILineElementTool::On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage )
{
	if( NONE_UI_STATE != m_nUIState )
		return TRUE;

	HINSTANCE hResInst = NULL;
	LPCTSTR pctszCursorID = NULL;
	if( nHitTest >= HT_LINE && nHitTest <= HT_SECONDPOINT )
	{
		if( HT_LINE == nHitTest )
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

BOOL CGILineElementTool::OnLButtonDown( const CMouseEvent& rEvent )
{
	if( HT_NOTHING == m_nHitTest && IsNewElementMode() )
	{
		if( FALSE == BeginNewElement( CGILineElement::ELEMENT_TAGNAME ) )
			return FALSE;
	}

	if( NULL == m_piElement )
		return FALSE;

	CGILineElement* pLineElement = (CGILineElement*)m_piElement;

	Matrix mtx;
	GetElementScreenCTM( mtx );

	PointF ptf( (FLOAT)rEvent.m_ptClient.x, (FLOAT)rEvent.m_ptClient.y );
	mtx.Invert(); // Screen To Element
	mtx.TransformPoints( &ptf );
	m_ptfCur = ptf;

	if( m_nHitTest >= HT_LINE && m_nHitTest <= HT_SECONDPOINT )
	{
		
		m_ptfElementStart.X = pLineElement->m_aX1;
		m_ptfElementStart.Y = pLineElement->m_aY1;
		m_ptfCurStart = m_ptfLineStart = m_ptfTrackStart = m_ptfElementStart;

		m_ptfElementEnd.X = pLineElement->m_aX2;
		m_ptfElementEnd.Y = pLineElement->m_aY2;
		m_ptfCurEnd = m_ptfLineEnd = m_ptfTrackEnd = m_ptfElementEnd;

		// Invalidate, SetCursor before update m_nUIState to erase Handles rect drawing
		InvalidateRect();	
		On_SetCursor( m_pwndView, HT_NOTHING, 0 ); 

		switch( m_nHitTest )
		{
		case HT_LINE:
			m_nUIState = MOVE_UI_STATE;
			m_ptfScreenStart.X = (FLOAT)rEvent.m_ptClient.x;
			m_ptfScreenStart.Y = (FLOAT)rEvent.m_ptClient.y;
			m_ptfScreenCursor = m_ptfScreenStart;
			m_ptfStart = ptf;
			break;

		case HT_FIRSTPOINT:{
			PointF ptfTemp = m_ptfElementStart;
			m_ptfElementStart = m_ptfElementEnd;
			m_ptfElementEnd = ptfTemp;
			m_ptfCurStart = m_ptfLineStart = m_ptfTrackStart = m_ptfElementStart;
			m_ptfCurEnd = m_ptfLineEnd = m_ptfTrackEnd = m_ptfElementEnd;
			m_nUIState = FIRST_POINT_DRAG_UI_STATE;
			}break;

		case HT_SECONDPOINT:
			m_nUIState = SECOND_POINT_DRAG_UI_STATE;
			break;
		}

		if( HT_LINE == m_nHitTest )
			m_nToolModeCaps = TMC_ORIENT; 
		else
			m_nToolModeCaps = TMC_CENTER | TMC_ANGLESNAP | TMC_MOVE_TRACKER;

		goto LBStartState;
	}

	m_ptfCurStart = m_ptfLineStart = m_ptfTrackStart = m_ptfElementStart = ptf;
	m_ptfCurEnd = m_ptfLineEnd = m_ptfTrackEnd = m_ptfElementEnd = ptf;
	
	m_nHitTest= HT_SECONDPOINT;
	m_nUIState = SECOND_POINT_DRAG_UI_STATE;
	m_nToolModeCaps = TMC_CENTER | TMC_ANGLESNAP | TMC_MOVE_TRACKER;

LBStartState:;
	StartTracker();
	return TRUE;
}

BOOL CGILineElementTool::OnMouseMove( const CMouseEvent& rEvent ) 
{
	if( NONE_UI_STATE == m_nUIState )
		return FALSE;

	if( NULL == m_piElement )
		return FALSE;

	PointF ptf( (FLOAT)rEvent.m_ptClient.x, (FLOAT)rEvent.m_ptClient.y );
	m_ptfScreenCursor = m_ptfScreenCursor = ptf;
	if( m_ptfScreenStart.X - m_ptfScreenCursor.X )
		m_ptfScreenStart.X = m_ptfScreenStart.X;

	Matrix mtx;
	GetElementScreenCTM( mtx );
	mtx.Invert(); // Screen To Element
	mtx.TransformPoints( &ptf );

	m_ptfCursor = ptf;
	if( IsToolModeCaps( TMC_ORIENT ) )
		StartOrientToolMode();

	UpdateTracker();
	m_ptfCur = ptf;

	return TRUE;
}

BOOL CGILineElementTool::OnLButtonUp( const CMouseEvent& rEvent )
{
	if( NONE_UI_STATE == m_nUIState )
		return FALSE;

	if( NULL == m_piElement )
		return FALSE;

	CGILineElement* pLineElement = (CGILineElement*)m_piElement;
	pLineElement->m_aX1 = m_ptfLineStart.X;
	pLineElement->m_aY1 = m_ptfLineStart.Y;
	pLineElement->m_aX2 = m_ptfLineEnd.X;
	pLineElement->m_aY2 = m_ptfLineEnd.Y;

	EndTracker();
	return FALSE;
}

void CGILineElementTool::UpdateTracker()
{
	if( NONE_UI_STATE == m_nUIState )
		return;

	if( NULL == m_piElement )
		return;

	m_ptfCurEnd = m_ptfCursor;

	UpdateMoveTrackerToolMode();
	UpdateOrientToolMode();
	UpdateAngleSnapToolMode();
	UpdateSymmetricToolMode();
	UpdateCenterToolMode();

	if( FIRST_POINT_DRAG_UI_STATE == m_nUIState )
	{
		m_ptfLineStart = m_ptfCurEnd;
		m_ptfLineEnd = m_ptfCurStart;
	}
	else if( SECOND_POINT_DRAG_UI_STATE == m_nUIState )
	{
		m_ptfLineStart = m_ptfCurStart;
		m_ptfLineEnd = m_ptfCurEnd;
	}
	else if( MOVE_UI_STATE == m_nUIState )
	{
		PointF ptfOffset( m_ptfCurEnd.X - m_ptfStart.X, m_ptfCurEnd.Y - m_ptfStart.Y );

		m_ptfLineStart.X = m_ptfElementStart.X + ptfOffset.X;
		m_ptfLineStart.Y = m_ptfElementStart.Y + ptfOffset.Y;

		m_ptfLineEnd.X = m_ptfElementEnd.X + ptfOffset.X;
		m_ptfLineEnd.Y = m_ptfElementEnd.Y + ptfOffset.Y;
	}

	UpdateTrackerDisplay();
}

void CGILineElementTool::MoveTracker( const PointF& rptfOffset )
{}

void CGILineElementTool::InvalidateRect( BOOL bHandle /*= FALSE*/ ) const
{
	if( NULL == m_piElement || NULL == m_pwndView )
		return;

	if( NONE_UI_STATE == m_nUIState && FALSE == GetSelection() )
		return;

	const INT cnPointCount = 2;
	PointF arptf[cnPointCount];
	Matrix mtx;
	GetElementScreenCTM( mtx );

	FLOAT fWidenPixelSize = 2;
	GraphicsPath gpath;
	if( bHandle || NONE_UI_STATE == m_nUIState )
	{
		if( bHandle )
			GetHandlePoints( m_ptfElementStart, m_ptfElementEnd, arptf );
		else
			GetHandlePoints( arptf );

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
		const INT cnTrackCount = 2;
		const INT cnTrackPointCount = 2;
		const PointF* pparptf[cnTrackCount][cnTrackPointCount] = { 
			{ &m_ptfTrackStart, &m_ptfTrackEnd },
			{ &m_ptfLineStart, &m_ptfLineEnd },
		};

		for( INT i = 0; i < cnTrackCount; i++ )
		{
			GetHandlePoints( *pparptf[i][0], *pparptf[i][1], arptf );
			mtx.TransformPoints( arptf, cnPointCount );

			gpath.AddLines( arptf, cnPointCount );
		}
	}

	Pen gpen( Color::Black, fWidenPixelSize );
	gpath.Widen( &gpen, NULL );

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

void CGILineElementTool::GetHandlePoints( PointF* pptf ) const 
{
	if( NONE_UI_STATE == m_nUIState )
	{
		if( NULL == m_piElement )
		{
			ASSERT( NULL );
			return;
		}

		CGILineElement* pLineElement = (CGILineElement*)m_piElement;
		pptf[0].X = pLineElement->m_aX1;
		pptf[0].Y = pLineElement->m_aY1;

		pptf[1].X = pLineElement->m_aX2;
		pptf[1].Y = pLineElement->m_aY2;
	}
	else
		GetHandlePoints( m_ptfLineStart, m_ptfLineEnd, pptf );
}

void CGILineElementTool::GetHandlePoints( const PointF& rptfStart, 
										  const PointF& rptfEnd, 
										  PointF* pptf ) const 
{
	pptf[0] = rptfStart;
	pptf[1] = rptfEnd;
}

void CGILineElementTool::GetTrackerPath( GraphicsPath& rgpath, const Matrix* pmtx /*= (Matrix*)-1*/ ) const
{
	if( NULL == m_piElement )
		return;

	Matrix mtx;
	if( (Matrix*)-1 == pmtx )
	{
		GetElementScreenCTM( mtx );
		pmtx = &mtx;
	}

	const INT cnPointCount = 2;
	PointF arptf[cnPointCount];
	GetHandlePoints( arptf );
	if( pmtx )
		pmtx->TransformPoints( arptf, cnPointCount );
}
