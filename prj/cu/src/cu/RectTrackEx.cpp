#include "stdafx.h"
#include <cu\RectTrackEx.h>
#include <cu\Msg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CRectTrackerEx::OnChangedRect( const CRect& rectOld )
{
	if( FALSE == m_bSetcursor )
	{
		m_bSetcursor = TRUE;
		AfsSendCall( m_pWnd, CM_UPDATE_CURSOR_POS );
	}

	CRectTracker::OnChangedRect( rectOld );
}

BOOL CRectTrackerEx::TrackRubberBand(CWnd* pWnd, CPoint point, BOOL bAllowInvert)
{
	// simply call helper function to track from bottom right handle
	m_bAllowInvert = bAllowInvert;
	m_rect.SetRect(point.x, point.y, point.x, point.y);
	return TrackHandle(hitBottomRight, pWnd, point, NULL);
}

void CRectTrackerEx::DrawTrackerRect( LPCRECT lpRect, CWnd* pWndClipTo, CDC* pDC, CWnd* pWnd )
{
	if( TRUE == m_bMinSize )
		if( abs( lpRect->right - lpRect->left ) >= m_szSize.cx && abs( lpRect->bottom - lpRect->top ) >= m_szSize.cy ) 
			m_bMinSize = -1;

	if( FALSE == m_bMinSize || -1 == m_bMinSize )
		CRectTracker::DrawTrackerRect( lpRect, pWndClipTo, pDC, pWnd );
}

BOOL CRectTrackerEx::TrackHandle(int nHandle, CWnd* pWnd, CPoint point,
	CWnd* pWndClipTo)
{
	ASSERT(nHandle >= 0);
	ASSERT(nHandle <= 8);   // handle 8 is inside the rect

	// don't handle if capture already set
	if (::GetCapture() != NULL)
		return FALSE;

	AfxLockTempMaps();  // protect maps while looping

	ASSERT(!m_bFinalErase);

	// save original width & height in pixels
	int nWidth = m_rect.Width();
	int nHeight = m_rect.Height();

	// set capture to the window which received this message
	pWnd->SetCapture();
	ASSERT(pWnd == CWnd::GetCapture());
	pWnd->UpdateWindow();
	if (pWndClipTo != NULL)
		pWndClipTo->UpdateWindow();
	CRect rectSave = m_rect;

	// find out what x/y coords we are supposed to modify
	int *px, *py;
	int xDiff, yDiff;
	GetModifyPointers(nHandle, &px, &py, &xDiff, &yDiff);
	xDiff = point.x - xDiff;
	yDiff = point.y - yDiff;

	// get DC for drawing
	CDC* pDrawDC;
	if (pWndClipTo != NULL)
	{
		// clip to arbitrary window by using adjusted Window DC
		pDrawDC = pWndClipTo->GetDCEx(NULL, DCX_CACHE);
	}
	else
	{
		// otherwise, just use normal DC
		pDrawDC = pWnd->GetDC();
	}

	ASSERT_VALID(pDrawDC);

	CRect rectOld;
	BOOL bMoved = FALSE;

	// get messages until capture lost or cancelled/accepted
	for (;;)
	{
//LBMsgFetch:;
		MSG msg;
		VERIFY(::GetMessage(&msg, NULL, 0, 0));

		if (CWnd::GetCapture() != pWnd)
		{
			rectOld = m_rect;
			m_bErase = TRUE;
			DrawTrackerRect(&rectOld, pWndClipTo, pDrawDC, pWnd);
			break;
		}

		switch (msg.message)
		{
		// handle movement/accept messages
		case WM_LBUTTONUP:
		case WM_MOUSEMOVE:{
			rectOld = m_rect;
			CPoint point;
			// handle resize cases (and part of move)
			if (px != NULL)
				point.x = *px = (int)(short)LOWORD(msg.lParam) - xDiff;
			if (py != NULL)
				point.y = *py = (int)(short)HIWORD(msg.lParam) - yDiff;

			//CZoomView::ms_ptScreen = point;
			}

			//m_pView->ClientToScreen( &CZoomView::ms_ptScreen );	
			AfsSendCallEx( m_pWnd, CM_UPDATE_CURSOR );

			// handle move case
			if (nHandle == hitMiddle)
			{
				m_rect.right = m_rect.left + nWidth;
				m_rect.bottom = m_rect.top + nHeight;
			}

			// allow caller to adjust the rectangle if necessary
			AdjustRect(nHandle, &m_rect);
			if( 0 )
			{
				POINT ptMove;
//				BOOL bMove = m_pView->AdjustView( g_point, &ptMove );
				BOOL bMove = FALSE;

				if( bMove )
				{
					m_rect.left += -ptMove.x;
					m_rect.top += -ptMove.y;
//					m_rect.OffsetRect( ptMove );
					rectOld = m_rect;
					m_bErase = FALSE;
					DrawTrackerRect(&m_rect, pWndClipTo, pDrawDC, pWnd);
				}
			}

			// only redraw and callback if the rect actually changed!
			m_bFinalErase = (msg.message == WM_LBUTTONUP);
			if (!rectOld.EqualRect(&m_rect) || m_bFinalErase)
			{
				if (bMoved)
				{
					m_bErase = TRUE;
					DrawTrackerRect(&rectOld, pWndClipTo, pDrawDC, pWnd);
				}
				OnChangedRect(rectOld);
				if (msg.message != WM_LBUTTONUP)
					bMoved = TRUE;
			}
			if (m_bFinalErase)
				goto ExitLoop;

			if (!rectOld.EqualRect(&m_rect))
			{
				m_bErase = FALSE;
				DrawTrackerRect(&m_rect, pWndClipTo, pDrawDC, pWnd);
			}
			break;

/*		case WM_KEYUP:
			if( m_pView->KeyBrdMouseUp( msg.wParam, LOWORD(msg.lParam), HIWORD(msg.lParam) ) )
				goto LBMsgFetch;
			break;*/

		// handle cancel messages
		case WM_KEYDOWN:
/*			if( m_pView->KeyBrdMouseDown( msg.wParam, LOWORD(msg.lParam), HIWORD(msg.lParam) ) )
				goto LBMsgFetch;*/

			if (msg.wParam != VK_ESCAPE)
				break;

		case WM_RBUTTONUP:
		case WM_RBUTTONDOWN:
			if (bMoved)
			{
				m_bErase = m_bFinalErase = TRUE;
				DrawTrackerRect(&m_rect, pWndClipTo, pDrawDC, pWnd);
			}
			m_rect = rectSave;
			goto ExitLoop;

		// just dispatch rest of the messages
		default:
			DispatchMessage(&msg);
			break;
		}
	}

ExitLoop:
	if (pWndClipTo != NULL)
		pWndClipTo->ReleaseDC(pDrawDC);
	else
		pWnd->ReleaseDC(pDrawDC);

	ReleaseCapture();

	AfxUnlockTempMaps(FALSE);

	// restore rect in case bMoved is still FALSE
	if (!bMoved)
		m_rect = rectSave;
	m_bFinalErase = FALSE;
	m_bErase = FALSE;

	// return TRUE only if rect has changed
	return !rectSave.EqualRect(&m_rect);
}

