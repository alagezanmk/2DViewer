#include "stdafx.h"
#include <g\tools\zpTool.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPL_GTPYECLASS_DYNCREATE( CGIZoomPanTool, CGIZoomTool, _T("ZoomPanTool") )
CGIZoomPanTool::CGIZoomPanTool() {
	m_pgInstanceType = &GetClassType(); }

CGIZoomPanTool::~CGIZoomPanTool()
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGIZoomPanTool::Draw( CDC& rDC, RECT& rRect, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
		if( CGIZoomTool::Draw( rDC, rRect ) )
		{
			rbResult = TRUE;
			return TRUE;
		}

	return FALSE;
}

UINT CGIZoomPanTool::HitTest( const CPoint& rpoint, BOOL& rbResult )
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::HitTest( rpoint );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::On_SetCursor( pWnd, nHitTest, nMessage );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnMouseWheel( const CMouseEvent& rEvent, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnMouseWheel( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnMouseMove( const CMouseEvent& rEvent, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnMouseMove( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnLButtonDown( const CMouseEvent& rEvent, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnLButtonDown( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnLButtonUp( const CMouseEvent& rEvent, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnLButtonUp( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnLButtonDblClk( const CMouseEvent& rEvent, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnLButtonDblClk( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnRButtonDown( const CMouseEvent& rEvent, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnRButtonDown( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnRButtonUp( const CMouseEvent& rEvent, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnRButtonUp( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnRButtonDblClk( const CMouseEvent& rEvent, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnRButtonDblClk( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnMButtonDown( const CMouseEvent& rEvent, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnMButtonDown( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnMButtonUp( const CMouseEvent& rEvent, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnMButtonUp( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnMButtonDblClk( const CMouseEvent& rEvent, BOOL& rbResult ) 
{
	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnMButtonDblClk( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::IsUIModeKey( INT nMode, UINT nChar )
{
	switch( nMode )
	{
	case ZOOM_IN_UI_MODE:
		return VK_CONTROL == nChar;

	case ZOOM_OUT_UI_MODE:
		return VK_MENU == nChar;

	case PAN_UI_MODE:
		return VK_SPACE == nChar;
	}

	return CGIZoomTool::IsUIModeKey( nMode, nChar );
}

UINT CGIZoomPanTool::GetUIModeKey( INT nMode )
{
	switch( nMode )
	{
	case ZOOM_IN_UI_MODE:
		return VK_CONTROL;

	case ZOOM_OUT_UI_MODE:
		return VK_MENU;

	case PAN_UI_MODE:
		return VK_SPACE;
	}

	return CGIZoomTool::GetUIModeKey( nMode );;
}

BOOL CGIZoomPanTool::OnKeyDown( const CKbdEvent& rEvent, BOOL& rbResult )
{
	BOOL bPanningMode = PAN_UI_MODE == m_nUIMode && PANNING_UI_STATE == m_nUIState;
	if( FALSE == bPanningMode )	// If Panning is active, zoom in and out can not be activated
	{
		// If Pan mode, Zoom in or Zoom out mode can be activated, 
		// if Zoom in mode , Zoom out mode can be activated, 
		// if Zoom out mode Zoom in mode can be activated, 
		if( PAN_UI_MODE == m_nUIMode || ZOOM_UI_MODE == m_nUIMode )
		{
			// If Zoom out mode not active and key is Zoom out mode
			BOOL bZoomOutMode = ZOOM_UI_MODE == m_nUIMode && ZOOM_OUT_UI_STATE == m_nUIState;
 			if( FALSE == bZoomOutMode && IsUIModeKey( ZOOM_OUT_UI_MODE, rEvent.m_nKey ) )
			{
				m_nUIMode = ZOOM_UI_MODE;
				m_nUIState = ZOOM_OUT_UI_STATE;
				VERIFY( PushSubUIMode( m_nUIMode, m_nUIState ) );
				VERIFY( AddListenUIModeKey( ZOOM_OUT_UI_MODE ) );
				if( m_pwndView )
					m_pwndView->UpdateCursor();

				return TRUE;
			}

			// If Zoom in mode not active and key is Zoom in mode
			BOOL bZoomInMode = ZOOM_UI_MODE == m_nUIMode && NONE_UI_STATE == m_nUIState;
			if( FALSE == bZoomInMode && IsUIModeKey( ZOOM_IN_UI_MODE, rEvent.m_nKey ) )
			{
				m_nUIMode = ZOOM_UI_MODE;
				m_nUIState = NONE_UI_STATE;
				VERIFY( PushSubUIMode( m_nUIMode, m_nUIState ) );
				VERIFY( AddListenUIModeKey( ZOOM_IN_UI_MODE ) );
				if( m_pwndView )
					m_pwndView->UpdateCursor();

				return TRUE;
			}
		}
		else
		{
			// If Zoom mode or Pan mode are not active, Pan can be activated
			if( IsUIModeKey( PAN_UI_MODE, rEvent.m_nKey ) )
			{
				m_nUIMode = PAN_UI_MODE;
				m_nUIState = NONE_UI_STATE;
				VERIFY( PushSubUIMode( m_nUIMode, m_nUIState ) );
				VERIFY( AddListenUIModeKey( PAN_UI_MODE ) );
				if( m_pwndView )
					m_pwndView->UpdateCursor();

				return TRUE;
			}
		}
	}

	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnKeyDown( rEvent );
		return TRUE;
	}

	return FALSE;
}

BOOL CGIZoomPanTool::OnKeyUp( const CKbdEvent& rEvent, BOOL& rbResult )
{
	if( ZOOM_UI_MODE == m_nUIMode									// Zoom Mode or
	|| (PAN_UI_MODE == m_nUIMode && PAN_UI_MODE != m_nDefUIMode) )	// (Pan mode and Def Mode not Pan mode)
	{
		// Pan mode key, stop Pan mode
		if( IsUIModeKey( PAN_UI_MODE, rEvent.m_nKey ) )
		{
			// If Panning, stop Panning
			if( PANNING_UI_STATE == m_nUIState )
				EndPan();

			// Remove all sub ui mode, key listener
			INT nMode;
			INT nCount = m_aarSubMode.GetSize();
			SSubUIMode* psSubUIMode = m_aarSubMode.GetData();
			for( INT i = 0; i < nCount; i++ )
			{
				nMode = psSubUIMode[i].nMode;
				if( ZOOM_UI_MODE == nMode && ZOOM_OUT_UI_STATE == psSubUIMode[i].nState )
					nMode = ZOOM_OUT_UI_MODE;

				VERIFY( RemoveListenUIModeKey( nMode ) );
			}

			// Restore to def mode
			RemoveAllSubUIMode();
			m_nUIMode = m_nDefUIMode;
			m_nUIState = NONE_UI_STATE;
			if( m_pwndView )
				m_pwndView->UpdateCursor();
			
			return TRUE;
		}

		// If Zoom in mode, stop Zoom in
		if( IsSubUIModeActive( ZOOM_UI_MODE, NONE_UI_STATE ) 
		 && IsUIModeKey( ZOOM_IN_UI_MODE, rEvent.m_nKey ) )
		{
			VERIFY( RemoveSubUIMode( ZOOM_UI_MODE, NONE_UI_STATE ) );
			GetLastSubUIMode( m_nUIMode, m_nUIState );
			VERIFY( RemoveListenUIModeKey( ZOOM_IN_UI_MODE ) );
			if( m_pwndView )
				m_pwndView->UpdateCursor();

			return TRUE;
		}

		// If Zoom out mode, stop Zoom out
		if( IsSubUIModeActive( ZOOM_UI_MODE, ZOOM_OUT_UI_STATE ) 
		 && IsUIModeKey( ZOOM_OUT_UI_MODE, rEvent.m_nKey ) )
		{
			VERIFY( RemoveSubUIMode( ZOOM_UI_MODE, ZOOM_OUT_UI_STATE ) );
			GetLastSubUIMode( m_nUIMode, m_nUIState );
			VERIFY( RemoveListenUIModeKey( ZOOM_OUT_UI_MODE ) );
			if( m_pwndView )
				m_pwndView->UpdateCursor();

			return TRUE;
		}
	}

	if( m_nDefUIMode != m_nUIMode )
	{
		rbResult = CGIZoomTool::OnKeyUp( rEvent );
		return TRUE;
	}

	return FALSE;
}
