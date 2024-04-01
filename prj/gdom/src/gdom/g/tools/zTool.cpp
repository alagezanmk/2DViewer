#include "stdafx.h"
#include "resource.h"
#include <g\tools\zTool.h>
#include <prop\PropRes.h>
#include <cu\RectTrackEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_ZOOM_PERCENTAGE 0.01f
#define MAX_ZOOM_PERCENTAGE 100.f

IMPL_GTPYECLASS_DYNCREATE( CGIZoomTool, CGIPanTool, _T("ZoomTool") )
CGIZoomTool::CGIZoomTool()
{
	m_pgInstanceType = &GetClassType();
	m_fMinScale = MIN_ZOOM_PERCENTAGE;
	m_fMaxScale = MAX_ZOOM_PERCENTAGE;

	m_hPanBmp = NULL;
	m_nDefUIMode = ZOOM_UI_MODE;
	m_nUIMode = ZOOM_UI_MODE;

	m_bKeepViewPoint = TRUE;
	m_bZoomOutClicked = FALSE;
}

CGIZoomTool::~CGIZoomTool()
{}

UINT CGIZoomTool::HitTest( const CPoint& rpoint )
{
	if( ZOOM_UI_MODE != m_nUIMode )
		return CGIPanTool::HitTest( rpoint );

	UINT nCursorID = 0;
	switch( m_nUIState )
	{
	case NONE_UI_STATE:
		return HT_ZOOM_IN;

	case ZOOM_OUT_UI_STATE:
		return HT_ZOOM_OUT;
	}

	return HT_NOTHING;
}

BOOL CGIZoomTool::On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage )
{
	if( ZOOM_UI_MODE != m_nUIMode )
		return CGIPanTool::On_SetCursor( pWnd, nHitTest, nMessage );

	UINT nCursorID = 0;
	switch( nHitTest )
	{
	case HT_ZOOM_IN:
		nCursorID = IDC_ZOOM_IN_CUR;
		break;

	case HT_ZOOM_OUT:
		nCursorID = IDC_ZOOM_OUT_CUR;
		break;
	}

	if( nCursorID )
	{
		LPCTSTR pctszCursorID = MAKEINTRESOURCE(nCursorID);
		HINSTANCE hResInst = AfxFindResourceHandle( pctszCursorID, RT_GROUP_CURSOR );
		HCURSOR hCursor = ::LoadCursor( hResInst, pctszCursorID );
		::SetCursor( hCursor );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomTool::OnLButtonDown( const CMouseEvent& rEvent )
{
	if( ZOOM_UI_MODE != m_nUIMode )
		return CGIPanTool::OnLButtonDown( rEvent );

	if( NULL == m_pwndView )
		return FALSE;

	if( ZOOM_OUT_UI_STATE == m_nUIState )
		m_bZoomOutClicked = TRUE;

	CRectTrackerEx rctTracker;
	rctTracker.m_bMinSize = TRUE;
	rctTracker.m_szSize.cx = 7;
	rctTracker.m_szSize.cy = 7;
	rctTracker.m_pWnd = m_pwndView;
	rctTracker.m_sizeMin.cx = 1;
	rctTracker.m_sizeMin.cy = 1;
	rctTracker.m_nStyle = CRectTracker::dottedLine;
	rctTracker.m_rect.SetRect( rEvent.m_ptClient, rEvent.m_ptClient );

	if( rctTracker.TrackRubberBand( m_pwndView, rEvent.m_ptClient, TRUE ) )
	{
		if( TRUE == rctTracker.m_bMinSize )
			goto LBPointZoom;

		rctTracker.m_rect.NormalizeRect();
		Zoom( rctTracker.m_rect, ZOOM_OUT_UI_STATE != m_nUIState );
	}
	else
	{
LBPointZoom:;
		FLOAT fScale = m_pView->GetScale(); 
		if( ZOOM_OUT_UI_STATE != m_nUIState )
			fScale *= 2.f;
		else
			fScale /= 2.f;

		CPoint point = rctTracker.m_rect.CenterPoint();
		Zoom( point, fScale );
	}

	return TRUE;
}

void CGIZoomTool::Zoom( CRect& rRect, BOOL bZoomIn )
{
	FLOAT fZoomCx = (FLOAT)rRect.Width();
	FLOAT fZoomCy = (FLOAT)rRect.Height();

	CRect rcClient;
	m_pwndView->GetClientRect( rcClient );
	
	FLOAT fViewCx, fViewCy;
	m_pView->GetRenderSize( fViewCx, fViewCy );
	
	FLOAT fRatio;
	if( bZoomIn )
	{
		FLOAT fRatioX = fViewCx / fZoomCx;
		FLOAT fRatioY = fViewCy / fZoomCy;
				
		if( fRatioX > fRatioY )
			fRatio = fRatioX;
		else
			fRatio = fRatioY;
	}
	else
		fRatio = fViewCx / fZoomCx;

	FLOAT fCurScale = m_pView->GetScale();
	Zoom( rRect.CenterPoint(), fRatio * fCurScale, TRUE );
}

void CGIZoomTool::Zoom( const CPoint& rpt, FLOAT fScale, BOOL bZoomToWindowCenter /*= FALSE*/ )
{
	if( fScale < m_fMinScale )
		fScale = m_fMinScale;
	else if( fScale > m_fMaxScale )
		fScale = m_fMaxScale;

	m_pView->Zoom( rpt, fScale, bZoomToWindowCenter );
}

BOOL CGIZoomTool::IsUIModeKey( INT nMode, UINT nChar )
{
	switch( nMode )
	{
	case PAN_UI_MODE:
		return VK_SPACE == nChar;
	}

	return CGIPanTool::IsUIModeKey( nMode, nChar );
}

UINT CGIZoomTool::GetUIModeKey( INT nMode )
{
	switch( nMode )
	{
	case PAN_UI_MODE:
		return VK_SPACE;
	}

	return CGIPanTool::GetUIModeKey( nMode );;
}

BOOL CGIZoomTool::IsUIStateKey( INT nMode, INT nState, UINT nChar )
{
	if( ZOOM_UI_MODE == nMode )
	{
		switch( nState )
		{
		case ZOOM_OUT_UI_STATE:
			return VK_MENU == nChar;
		}
	}

	return CGIPanTool::IsUIStateKey( nMode, nState, nChar );
}

UINT CGIZoomTool::GetUIStateKey( INT nMode, INT nState )
{
	if( ZOOM_UI_MODE == nMode )
	{
		switch( nState )
		{
		case ZOOM_OUT_UI_STATE:
			return VK_MENU;
		}
	}

	return CGIPanTool::GetUIStateKey( nMode, nState );
}

BOOL CGIZoomTool::OnKeyDown( const CKbdEvent& rEvent )
{
	if( ZOOM_UI_MODE != m_nDefUIMode )
		return CGIPanTool::OnKeyDown( rEvent );

	if( ZOOM_UI_MODE == m_nUIMode )
	{
		if( ZOOM_OUT_UI_STATE != m_nUIState && PAN_UI_MODE != m_nUIMode 
			&& IsUIModeKey( PAN_UI_MODE, rEvent.m_nKey ) )
		{
			m_nUIMode = PAN_UI_MODE;

			VERIFY( AddListenUIModeKey( PAN_UI_MODE ) );
			if( m_pwndView )
				m_pwndView->UpdateCursor();

			return TRUE;
		}
 		else if( IsUIStateKey( ZOOM_UI_MODE, ZOOM_OUT_UI_STATE, rEvent.m_nKey ) )
		{
			m_nUIState = ZOOM_OUT_UI_STATE;

			VERIFY( AddListenUIStateKey( ZOOM_UI_MODE, ZOOM_OUT_UI_STATE ) );
			if( m_pwndView )
				m_pwndView->UpdateCursor();

			return TRUE;
		}
	}

	return FALSE;
}

BOOL CGIZoomTool::OnKeyUp( const CKbdEvent& rEvent )
{
	if( ZOOM_UI_MODE != m_nDefUIMode )
		return CGIPanTool::OnKeyUp( rEvent );

	if( ZOOM_UI_MODE == m_nUIMode && ZOOM_OUT_UI_STATE == m_nUIState &&
		IsUIStateKey( ZOOM_UI_MODE, ZOOM_OUT_UI_STATE, rEvent.m_nKey ) )
	{
		BOOL bKeyProcessed = TRUE;
		bKeyProcessed = m_bZoomOutClicked;
		m_bZoomOutClicked = FALSE;

		m_nUIState = NONE_UI_STATE;
		VERIFY( RemoveListenUIStateKey( ZOOM_UI_MODE, ZOOM_OUT_UI_STATE ) );
		if( m_pwndView )
			m_pwndView->UpdateCursor();

		return bKeyProcessed;
	}

	if( PAN_UI_MODE == m_nUIMode && IsUIModeKey( PAN_UI_MODE, rEvent.m_nKey ) )
	{
		if( PANNING_UI_STATE == m_nUIState )
			EndPan();

		m_nUIMode = ZOOM_UI_MODE;
		VERIFY( RemoveListenUIModeKey( PAN_UI_MODE ) );
		if( m_pwndView )
			m_pwndView->UpdateCursor();
		
		return TRUE;
	}

	return FALSE;
}