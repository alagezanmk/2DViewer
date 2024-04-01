#include "stdafx.h"
#include "ToolBox.h"
#include <cu\MemDC.h>
#include <gl\gl.h>
#include <cu\Key.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/// \bug(1) Invalid value -1 is stored in m_nPressed for the following case
/// Status - Solved
///		1. Press hold the Group button to open the popup
///		2. Press Alt + Tab.
///		3. In the OnMouseMOve m_nPressed is not with -1
///		4. When the OnTimer uses m_nPressed, ASSERT will be shown.
///
/// Solution(1)
///		1. Code CToolBox::OnMouseMove function that starts Timer was masked

///////////////////////////////////////////////////////////////////////////////////////////////////
struct CToolBox::SItem
{
	void Copy( SItem* psItem );

	INT			nID;
	INT			nKey;

	CRect		rect;
	SImageList*	pImageList;
	CPtrArray	arpGroup;
	INT			nImageIndex;

	CString		cszCaption;
	DWORD		dwData;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
struct CToolBox::SImageList
{
	INT			nID;
	CImageList  ImageList;
	CSize		cbImage;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
const int g_cnx = 2;
const int g_cny = 2;
class CPopupWnd : CWnd
{
	CPopupWnd();
	virtual ~CPopupWnd();

	//{{AFX_VIRTUAL(CPopupWnd)
	public:
	virtual BOOL Create( CWnd* pParentWnd );
	int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPopupWnd)
	afx_msg LRESULT OnFloatStatusMsg( WPARAM wParam, LPARAM lParam );
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void SetCurSel( INT nIndex, BOOL bHilite = FALSE );
	INT GetItemAt( CPoint point, CToolBox::SItem** ppsItem = NULL );
	void DrawItem( CDC* pDC, INT nIndex, CRect rect, CToolBox::SItem* psItem );
	INT Track( CPoint point );

protected:
	CPtrArray*	m_parpGrp;
	CSize		m_cbItem;
	INT			m_nHilite;
	INT			m_nCurItem;
	INT			m_nSel;
	BOOL		m_bPressed;

	friend class CToolBox;
};

BEGIN_MESSAGE_MAP(CPopupWnd, CWnd)
	//{{AFX_MSG_MAP(CToolBox)
	ON_MESSAGE( WM_FLOATSTATUS, OnFloatStatusMsg )
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPopupWnd::CPopupWnd()
{
	m_nSel = -2;
	m_nCurItem = -1;
	m_nHilite = -1;
	m_bPressed = FALSE;
}

CPopupWnd::~CPopupWnd()
{}

/// To syn float status, which keeps MainFrame always have active caption, 
/// even this control get activated
LRESULT CPopupWnd::OnFloatStatusMsg( WPARAM wParam, LPARAM lParam ) {
	return 1L; }

BOOL CPopupWnd::Create( CWnd* pParentWnd )  
{
	LPCTSTR lptClass = AfxRegisterWndClass( 0, LoadCursor( NULL, MAKEINTRESOURCE(IDC_ARROW) ), (HBRUSH)(COLOR_WINDOW + 1) );
	ASSERT( lptClass );

	CRect rectWnd(0,0,0,0);
	BOOL bResult = CreateEx( WS_EX_WINDOWEDGE, lptClass, NULL, 
						     WS_VISIBLE | WS_POPUP,
						     rectWnd, pParentWnd, 0 );
	if( bResult )
		EnableToolTips();

	return bResult;
}

BOOL CPopupWnd::OnEraseBkgnd(CDC* pDC)  {
	return TRUE; }

void CPopupWnd::OnPaint()
{
	CPaintDC dc( this );

	CMemDC MemDC;
	CRect rctClient;
	GetClientRect( rctClient );	

	MemDC.Create( &dc, rctClient.Width(), rctClient.Height() );
	HBRUSH hbrBkGnd = GetSysColorBrush( COLOR_BTNFACE );

	COLORREF crfHilite = GetSysColor( COLOR_BTNHIGHLIGHT );
	COLORREF crfLite = GetSysColor( COLOR_BTNSHADOW );
	FillRect( MemDC.m_hDC, rctClient, hbrBkGnd );
	MemDC.Draw3dRect( rctClient, crfHilite, crfLite );

	CRect rect( g_cnx, g_cny, m_cbItem.cx + g_cnx, m_cbItem.cy + g_cny );
	CToolBox::SItem** ppsItem = (CToolBox::SItem**)m_parpGrp->GetData();
	INT nCount = m_parpGrp->GetSize();
	for( INT i = 0; i < nCount; i++ )
	{
		DrawItem( &MemDC, i, rect, ppsItem[i] );
		rect.OffsetRect( m_cbItem.cx, 0 );
	}

	MemDC.BitBltTo( &dc );
}

void CPopupWnd::DrawItem( CDC* pDC, INT nIndex, CRect rect, CToolBox::SItem* psItem )
{
	if( m_nCurItem == nIndex )
	{
		COLORREF crfHilite = GetSysColor( COLOR_BTNHIGHLIGHT );
		COLORREF crfLite = GetSysColor( COLOR_3DDKSHADOW );
		pDC->Draw3dRect( rect, crfLite, crfHilite );

		if( m_nHilite == nIndex )
		{
			CRect rcHilite = rect;
			rcHilite.DeflateRect( 1, 1 );
			HBRUSH hbrHilite = GetSysColorBrush( COLOR_BTNHIGHLIGHT );
			FillRect( pDC->m_hDC, rcHilite, hbrHilite );
		}
	}
	else if( m_nHilite == nIndex )
	{
		COLORREF crfHilite = GetSysColor( COLOR_BTNHIGHLIGHT );
		COLORREF crfLite = GetSysColor( COLOR_3DDKSHADOW );
		if( m_bPressed )
		{
			crfHilite = crfLite;
			crfLite = GetSysColor( COLOR_BTNHIGHLIGHT );
		}

		pDC->Draw3dRect( rect, crfHilite, crfLite );
	}

	CToolBox::SImageList* psImageList = psItem->pImageList;

	POINT pt;
	pt.x = rect.TopLeft().x + (m_cbItem.cx - psImageList->cbImage.cx) / 2;
	pt.y = rect.TopLeft().y + (m_cbItem.cy - psImageList->cbImage.cy) / 2;

	psImageList->ImageList.Draw( pDC, psItem->nImageIndex, pt, ILD_NORMAL );
}

INT CPopupWnd::GetItemAt( CPoint point, CToolBox::SItem** ppsItm /*= NULL*/ )
{
	CRect rect( g_cnx, g_cny, m_cbItem.cx + g_cnx, m_cbItem.cy + g_cny );
	CToolBox::SItem** ppsItem = (CToolBox::SItem**)m_parpGrp->GetData();
	INT nCount = m_parpGrp->GetSize();

	for( INT i = 0; i < nCount; i++ )
	{
		if( rect.PtInRect( point ) )
		{
			if( ppsItm )
				*ppsItm = ppsItem[i];

			return i;
		}

		rect.OffsetRect( m_cbItem.cx, 0 );
	}

	return -1;
}

void CPopupWnd::SetCurSel( INT nIndex, BOOL bHilite /*= FALSE*/ )
{
	if( -1 == nIndex )
	{
		if( -1 != m_nHilite )
		{
			InvalidateRect( NULL, FALSE );
			m_nHilite = -1;
		}

		return;
	}

	if( bHilite )
		m_nHilite = nIndex;
	else
		m_nCurItem = nIndex;

	InvalidateRect( NULL, FALSE );
}

int CPopupWnd::OnToolHitTest( CPoint point, TOOLINFO* pTI ) const
{
	CPopupWnd* pToolBox = (CPopupWnd*)this;
	CToolBox::SItem* psItem;
	INT nTool = pToolBox->GetItemAt( point, &psItem );
	if( -1 != nTool )
	{
		SetRect( &pTI->rect, g_cnx, g_cny, m_cbItem.cx + g_cnx, m_cbItem.cy + g_cny );
		OffsetRect( &pTI->rect, m_cbItem.cx * nTool, 0 );

		pTI->hwnd = m_hWnd;
		pTI->uId = psItem->nID;

		pTI->lpszText = new TCHAR[psItem->cszCaption.GetLength() + 1];
		lstrcpy( pTI->lpszText,	(LPCTSTR)psItem->cszCaption );
	}

	return nTool;
}

void CPopupWnd::OnMouseMove( UINT nFlags, CPoint point ) 
{
	INT nItem = GetItemAt( point );
	SetCurSel( nItem, TRUE );
}

void CPopupWnd::OnLButtonUp( UINT nFlags, CPoint point ) 
{
	CToolBox::SItem* psItem;
	INT nItem = GetItemAt( point, &psItem );
	SetCurSel( nItem );
	if( -1 != nItem )
		m_nSel = nItem;
	else
		m_bPressed = FALSE;
}

void CPopupWnd::OnLButtonDown( UINT nFlags, CPoint point ) 
{
	CToolBox::SItem* psItem;
	INT nItem = GetItemAt( point, &psItem );
	if( -1 == nItem )
		m_nSel = -1;
	else
	{
		m_bPressed = TRUE;
		SetCurSel( nItem, TRUE );
	}
}

void CPopupWnd::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if( FALSE == IsKeyNoShift() )
		return;

	switch( nChar )
	{
	case VK_ESCAPE:
		m_nSel = -1;
		break;

	case VK_RETURN:
		m_nSel = m_nHilite;
		break;

	case VK_LEFT:
		if( m_parpGrp->GetSize() <= 1 )
			return;

		if( m_nHilite - 1 >= 0 )
			m_nHilite--;
		else
			m_nHilite = m_parpGrp->GetSize() - 1;

		InvalidateRect( NULL, FALSE );
		break;

	case VK_RIGHT:
		if( m_parpGrp->GetSize() <= 1 )
			return;

		if( m_nHilite + 1 < m_parpGrp->GetSize() )
			m_nHilite++;
		else
			m_nHilite = 0;

		InvalidateRect( NULL, FALSE );
		break;
	}
}

INT CPopupWnd::Track( CPoint point )
{
	INT nCount = m_parpGrp->GetSize();
	CToolBox::SItem** ppsItem = (CToolBox::SItem**)m_parpGrp->GetData();
	
	CRect rect( point.x, point.y, point.x + m_cbItem.cx * nCount + 4, point.y + m_cbItem.cx + 4 );
	MoveWindow( rect );

	SetFocus();
	SetCapture();
	while( -2 == m_nSel && this == GetCapture() )
		AfxGetApp()->PumpMessage();

	if( this == GetCapture() )
		ReleaseCapture();

	if( -2 == m_nSel )
		m_nSel = -1;
		 
	return m_nSel;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CToolBox, CToolFrmWnd)
	//{{AFX_MSG_MAP(CToolBox)
	ON_MESSAGE( WM_FLOATSTATUS, OnFloatStatusMsg )
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

const int gc_x = 2;
const int gc_y = 2;
const int gc_bx = 2;
const int gc_by = 2;
const int gc_cy = 2;

const int gc_nPopupTimerID = 10;
const int gc_nPopupTimerDur = 500;

CToolBox::CToolBox()
{
	m_cbItem.cx = 24;
	m_cbItem.cy = 24;

	m_cszCtrlName = _T("Tool Box");

	ResetContent();
}

CToolBox::~CToolBox()
{
	ResetContent();
}

BOOL CToolBox::Create( LPCTSTR lpszWindowName, const RECT& rect, CWnd* pParentWnd )  
{
	LPCTSTR lptClass = AfxRegisterWndClass( 0, LoadCursor( NULL, MAKEINTRESOURCE(IDC_ARROW) ) );
	ASSERT( lptClass );

	CRect rectWnd( rect );
	rectWnd.right = rectWnd.left + (m_cbItem.cx + gc_bx) * 2 + gc_x * 3;
	rectWnd.bottom = rectWnd.top + m_cbItem.cy + 172;
	rectWnd.bottom = 1;//rectWnd.top + m_cbItem.cy + 172;
	BOOL bResult = CreateEx( WS_EX_TOOLWINDOW, lptClass, lpszWindowName, 
						     WS_VISIBLE | WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN,
						     rectWnd, pParentWnd, 0 );
	if( bResult )
		EnableToolTips();

	return bResult;
}

void CToolBox::OnClose()
{
	if( IsWindowVisible() )
		ShowWindow( SW_HIDE );
}

/// To syn float status, which keeps MainFrame always have active caption, 
/// even this control get activated
LRESULT CToolBox::OnFloatStatusMsg( WPARAM wParam, LPARAM lParam ) {
	return 1L; }

BOOL CToolBox::OnEraseBkgnd(CDC* pDC)  {
	return TRUE; }

void CToolBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CMemDC MemDC;
	CRect rctClient;
	GetClientRect( rctClient );	

	MemDC.Create( &dc, rctClient.Width(), rctClient.Height() );
	HBRUSH hbrBkGnd = GetSysColorBrush( COLOR_BTNFACE );
	FillRect( MemDC.m_hDC, rctClient, hbrBkGnd );

	{
		COLORREF crfHilite = GetSysColor( COLOR_BTNHIGHLIGHT );
		COLORREF crfLite = GetSysColor( COLOR_BTNSHADOW );

		SItem** ppsItem = (SItem**)m_arpItem.GetData();
		INT nCount = m_arpItem.GetSize();
		for( INT i = 0; i < nCount; i++ )
		{
			if( SEPARATOR_ITEM == ppsItem[i]->nID )
				MemDC.Draw3dRect( ppsItem[i]->rect, crfLite, crfHilite );
			else if( CONTROL_ITEM != ppsItem[i]->nID )
				DrawItem( &MemDC, i, ppsItem[i]->rect, ppsItem[i] );
		}
	}

	MemDC.BitBltTo( &dc );
}

void CToolBox::DrawItem( CDC* pDC, INT nIndex, CRect rect, SItem* psItem )
{
	if( m_nCurItem == nIndex )
	{
		COLORREF crfHilite = GetSysColor( COLOR_BTNHIGHLIGHT );
		COLORREF crfLite = GetSysColor( COLOR_3DDKSHADOW );
		pDC->Draw3dRect( rect, crfLite, crfHilite );

		if( m_nHilite == nIndex )
		{
			CRect rcHilite = rect;
			rcHilite.DeflateRect( 1, 1 );
			HBRUSH hbrHilite = GetSysColorBrush( COLOR_BTNHIGHLIGHT );
			FillRect( pDC->m_hDC, rcHilite, hbrHilite );
		}
	}
	else if( m_nHilite == nIndex )
	{
		COLORREF crfHilite = GetSysColor( COLOR_BTNHIGHLIGHT );
		COLORREF crfLite = GetSysColor( COLOR_3DDKSHADOW );
		if( m_bPressed )
		{
			crfHilite = crfLite;
			crfLite = GetSysColor( COLOR_BTNHIGHLIGHT );
		}

		pDC->Draw3dRect( rect, crfHilite, crfLite );
	}

	CToolBox::SImageList* psImageList = psItem->pImageList;

	POINT pt;
	pt.x = rect.TopLeft().x + (m_cbItem.cx - psImageList->cbImage.cx) / 2;
	pt.y = rect.TopLeft().y + (m_cbItem.cy - psImageList->cbImage.cy) / 2;

	psImageList->ImageList.Draw( pDC, psItem->nImageIndex, pt, ILD_NORMAL );

	if( psItem->arpGroup.GetSize() )
	{
		const int c_Cs = 1;
		INT x = rect.right - 2;
		INT y = rect.bottom - 2;

		pDC->MoveTo( x, y );
		pDC->LineTo( x - c_Cs, y );
		pDC->LineTo( x, y - c_Cs );
		pDC->LineTo( x, y );
	}
}

BOOL CToolBox::AddItem( SItemInfo* psItemInfo, BOOL bUpdateFrame /*= TRUE*/ )
{
	SItem* psItem = new SItem;
	if( NULL == psItem )
	{
		ASSERT( psItem );
		return FALSE;
	}

	psItem->pImageList = NULL;

	SItem* psGroup = NULL;
	if( SEPARATOR_ITEM == (INT)psItemInfo || SEPARATOR_ITEM == psItemInfo->nID )
	{
		psItem->nID	= SEPARATOR_ITEM;
	}
	else if( CONTROL_ITEM == psItemInfo->nID )
	{
		psItem->nID = CONTROL_ITEM;
		psItem->nKey = psItemInfo->nKey;
		psItem->rect.top = 0;
		psItem->rect.bottom = 0;
		psItem->nImageIndex = psItemInfo->nImageIndex;
		psItem->dwData = psItemInfo->dwData;

		if( psItemInfo->nCy > 0 )
			psItem->rect.bottom = psItemInfo->nCy;
	}
	else
	{
		psItem->pImageList = GetImageList( psItemInfo->nImageID );
		if( NULL == psItem->pImageList )
		{
			delete psItem;
			return FALSE;
		}

		psItem->nID = psItemInfo->nID;
		psItem->nKey = psItemInfo->nKey;
		psItem->nImageIndex	= psItemInfo->nImageIndex;
		psItem->cszCaption = psItemInfo->cszCaption;
		psItem->dwData = psItemInfo->dwData;

		if( psItem->nKey )
			psGroup	= GetItemGroup( psItem->nKey );
	}

	if( psGroup )
	{
		// if no items was added yet, add this psGroup also into Group
		if( 0 == psGroup->arpGroup.GetSize() )
			psGroup->arpGroup.Add( psGroup );

		psGroup->arpGroup.Add( psItem );
	}
	else
		m_arpItem.Add( psItem );

	INT nCy = ReCalcLayout();
	if( bUpdateFrame )
	{
		CRect rectBorder;
		rectBorder.SetRectEmpty();
		INT nStyle = GetWindowLong( m_hWnd, GWL_STYLE );
		INT nExStyle = GetWindowLong( m_hWnd, GWL_EXSTYLE );
		AdjustWindowRect( rectBorder, nStyle, nExStyle );

		CRect rect;
		GetWindowRect( rect );
		rect.right = rect.left + (m_cbItem.cx + gc_bx) * 2 - rectBorder.left + rectBorder.right;
		rect.bottom = rect.top + nCy - rectBorder.top - rectBorder.bottom - 17;
		MoveWindow( rect );
	}

	InvalidateRect( NULL, FALSE );
	return TRUE;
}

BOOL CToolBox::InsertItem( INT nIndex, SItemInfo* psItemInfo )
{
	SItem* psGroup = NULL;
	if( psItemInfo->nID )
		psGroup	= GetItemGroup( psItemInfo->nKey );

	// Check nIndex whether valid or not
	if( psGroup )
	{
		if( nIndex > psGroup->arpGroup.GetSize() )
			return FALSE;
	}
	else if( nIndex > m_arpItem.GetSize() )
		return FALSE;

	SItem* psItem = new SItem;
	if( NULL == psItem )
	{
		ASSERT( psItem );
		return FALSE;
	}

	psItem->pImageList	= GetImageList( psItemInfo->nImageID );
	if( NULL == psItem->pImageList )
	{
		delete psItem;
		return FALSE;
	}

	psItem->nID			= psItemInfo->nID;
	psItem->nKey		= psItemInfo->nKey;
	psItem->nImageIndex	= psItemInfo->nImageIndex;
	psItem->cszCaption	= psItemInfo->cszCaption;
	psItem->dwData		= psItemInfo->dwData;
	ASSERT( psItem->pImageList );

	if( psGroup )
	{
		// if no items was added yet, add this psGroup also into Group
		if( 0 == psGroup->arpGroup.GetSize() )
			psGroup->arpGroup.Add( psGroup );

		psGroup->arpGroup.InsertAt( nIndex, psItem );
	}
	else
		m_arpItem.InsertAt( nIndex, psItem );

	ReCalcLayout();
	InvalidateRect( NULL, FALSE );
	return TRUE;
}

CToolBox::SImageList* CToolBox::GetImageList( INT nID )
{
	CToolBox::SImageList** ppImageList = (CToolBox::SImageList**)m_arpImageList.GetData();
	INT nCount = m_arpImageList.GetSize();
	for( INT i = 0; i < nCount; i++ )
		if( ppImageList[i]->nID == nID )
			return ppImageList[i];

	return NULL;
}

BOOL CToolBox::AddImageList( CImageList* pList, INT nID, INT cx )
{
	if( GetImageList( nID ) )
		return FALSE;

	CToolBox::SImageList* pImageList = new CToolBox::SImageList;
	if( NULL == pImageList )
	{
		ASSERT( pImageList );
		return FALSE;
	}

	if( FALSE == pImageList->ImageList.Create( pList ) )
	{
		delete pImageList;
		return FALSE;
	}

	pImageList->nID = nID;
	pImageList->cbImage.cx = cx;
	pImageList->cbImage.cy = 12;
	m_arpImageList.Add( pImageList );
	return TRUE;
}

BOOL CToolBox::LoadImage( INT nID, INT cx )
{
	if( GetImageList( nID ) )
		return FALSE;

	CToolBox::SImageList* pImageList = new CToolBox::SImageList;
	ASSERT( pImageList );
	if( NULL == pImageList )
	{
		ASSERT( pImageList );
		return FALSE;
	}

	if( FALSE == pImageList->ImageList.Create( nID, cx, 12, RGB(255,255,255) ) )
	{
		delete pImageList;
		return FALSE;
	}

	pImageList->nID = nID;
	pImageList->cbImage.cx = cx;
	pImageList->cbImage.cy = 12;
	m_arpImageList.Add( pImageList );
	return TRUE;
}

CToolBox::SItem* CToolBox::GetItemGroup( INT nKey )
{
	SItem** ppsItem = (SItem**)m_arpItem.GetData();
	INT nCount = m_arpItem.GetSize();
	for( INT i = 0; i < nCount; i++ )
		if( ppsItem[i]->nKey == nKey )
			return ppsItem[i];

	return NULL;
}

INT CToolBox::GetItemAt( CPoint point, SItem** ppsItm /*= NULL*/ )
{
	SItem** ppsItem = (SItem**)m_arpItem.GetData();
	INT nCount = m_arpItem.GetSize();
	INT i;
	for( i = 0; i < nCount; i++ )
	{
		if( ppsItem[i]->nID )
			if( ppsItem[i]->rect.PtInRect( point ) )
				break;
	}

	if( i != nCount )
	{
		if( ppsItm )
			*ppsItm = ppsItem[i];

		return i;
	}

	return -1;
}

INT CToolBox::ReCalcLayout()
{
	INT y = 0;
	INT nCol = 0;
	INT nCount = m_arpItem.GetSize();
	SItem** ppsItem = (SItem**)m_arpItem.GetData();
	for( INT i = 0; i < nCount; i++ )
	{
		if( SEPARATOR_ITEM == ppsItem[i]->nID )
		{
			if( 1 == nCol )
			{
				nCol = 0;
				y += m_cbItem.cy;
			}

			y += 1;
			ppsItem[i]->rect.SetRect( gc_x + nCol * (m_cbItem.cx) - 1, gc_y + y, m_cbItem.cx * 2 + 4, gc_cy );
			ppsItem[i]->rect.right += ppsItem[i]->rect.left;
			ppsItem[i]->rect.bottom += ppsItem[i]->rect.top;

			y += gc_cy + 1;
		}
		else if( CONTROL_ITEM == ppsItem[i]->nID )
		{
			if( 1 == nCol )
			{
				nCol = 0;
				y += m_cbItem.cy;
			}

			INT nCy = ppsItem[i]->rect.Height();
			ppsItem[i]->rect.SetRect( gc_x, gc_y + y, m_cbItem.cx * 2 + gc_x, nCy );
			ppsItem[i]->rect.bottom += ppsItem[i]->rect.top;
			HWND hWnd = (HWND)ppsItem[i]->nImageIndex;
			if( IsWindow( hWnd ) )
			{
				::SetParent( hWnd, m_hWnd );

				INT nCx = ppsItem[i]->rect.right - ppsItem[i]->rect.left;
				::MoveWindow( hWnd, ppsItem[i]->rect.left,
							ppsItem[i]->rect.top,
							nCx, nCy, TRUE );
			}

			y += nCy;
		}
		else // Button Type
		{
			ppsItem[i]->rect.SetRect( gc_x + nCol * (m_cbItem.cx), gc_y + y, m_cbItem.cx, m_cbItem.cy );
			ppsItem[i]->rect.right += ppsItem[i]->rect.left;
			ppsItem[i]->rect.bottom += ppsItem[i]->rect.top;
			if( 0 == nCol )
				nCol = 1;
			else
			{
				nCol = 0;
				y += m_cbItem.cy;
			}
		}
	}

	return y;
}

void CToolBox::GetItemRect( INT nIndex, RECT* pRect )
{
	SItem** ppsItem = (SItem**)m_arpItem.GetData();
	*pRect = ppsItem[nIndex]->rect;
	return;
}

void CToolBox::SetItem( INT nIndex, SItem* psItem, BOOL bHilite /*= FALSE*/ )
{
	if( -1 == nIndex )
	{
		if( -1 != m_nHilite )
		{
			if( FALSE == m_bPressed /*&& this != GetCapture())*/ )
				ReleaseCapture();
			else
				m_bPressed = FALSE;

			InvalidateRect( NULL, FALSE );
			m_nHilite = -1;
		}

		return;
	}

	if( bHilite )
	{
		if( -1 == m_nHilite && this != GetCapture() && FALSE == m_bPressed )
			SetCapture();

		m_nHilite = nIndex;
	}
	else
	{
		m_nCurItem = nIndex;
		if( psItem )
			OnSelectItem( psItem );
	}

	InvalidateRect( NULL, FALSE );
}

void CToolBox::OnSelectItem( SItem* psItem )
{
	if( psItem )
		AfxGetMainWnd()->PostMessage( WM_COMMAND, psItem->nID );
}

BOOL CToolBox::SetCurItem( INT nID )
{
	SItem** ppsItem = (SItem**)m_arpItem.GetData();
	INT nCount = m_arpItem.GetSize();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppsItem[i]->nID == nID )
		{
			SetItem( i, ppsItem[i] );
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CToolBox::OnChar( INT nChar )
{
	if( FALSE == IsKeyAlt_() )
	{
		SItem** ppsItem = (SItem**)m_arpItem.GetData();
		INT nCount = m_arpItem.GetSize();
		for( INT i = 0; i < nCount; i++ )
		{
			if( ppsItem[i]->nKey == nChar )
			{
				if( 0 == ppsItem[i]->arpGroup.GetSize() && IsKeyNoShift() )
					SetItem( i, ppsItem[i] );
				else
				{
					if( IsKeyShiftC() )
						ShowPopup( i );
					else if( IsKeyNoShift() )
					{
						if( m_nCurItem != i )
						{
							SetItem( i, ppsItem[i] );
							return TRUE;
						}

						nCount = ppsItem[i]->arpGroup.GetSize();
						SItem** ppsGrpItem = (SItem**)ppsItem[i]->arpGroup.GetData();
						INT nSel;
						for( nSel = 0; nSel < nCount; nSel++ )
							if( ppsGrpItem[nSel] == ppsItem[i] )
								break;

						if( nSel == nCount )
							return FALSE;

						nSel++;
						if( nSel == nCount )
							nSel = 0;

						SwapItem( i, nSel );
						SetItem( i, (SItem*)ppsItem[i]->arpGroup.GetAt( nSel ) );
					}
					else
						return FALSE;
				}

				return TRUE;
			}
		}
	}

	return FALSE;
}

static void DeleteItems( CPtrArray& rarpItem )
{
	CToolBox::SItem** ppsItem = (CToolBox::SItem**)rarpItem.GetData();
	INT nCount = rarpItem.GetSize();
	for( INT i = 0; i < nCount; i++ )
	{
		if( ppsItem[i]->arpGroup.GetSize() )
		{
			CPtrArray arpCopy;
			arpCopy.Copy( ppsItem[i]->arpGroup );
			ppsItem[i]->arpGroup.RemoveAll();
			DeleteItems( arpCopy );
		}
		else
			delete ppsItem[i];
	}

	rarpItem.RemoveAll();
}

void CToolBox::ResetContent()
{
	DeleteItems( m_arpItem );

	CToolBox::SImageList** ppImageList = (CToolBox::SImageList**)m_arpImageList.GetData();
	INT nCount = m_arpImageList.GetSize();
	for( INT i = 0; i < nCount; i++ )
		delete ppImageList[i];

	m_arpImageList.RemoveAll();

	m_nPressed = -1;
	m_nHilite = -1;
	m_bPressed = FALSE;
	m_nCurItem = 0;
}

int CToolBox::OnToolHitTest( CPoint point, TOOLINFO* pTI ) const
{
	CToolBox* pToolBox = (CToolBox*)this;
	SItem* psItem;
	INT nItem = pToolBox->GetItemAt( point, &psItem );
	if( -1 != nItem )
	{
		pTI->hwnd = m_hWnd;
		pTI->rect = psItem->rect;
		pTI->uId = psItem->nID;

		pTI->lpszText = new TCHAR[psItem->cszCaption.GetLength() + 1];
		lstrcpy( pTI->lpszText,	(LPCTSTR)psItem->cszCaption );
	}

	return nItem;
}

void CToolBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( OnChar( nChar ) )
		return;

	if( VK_ESCAPE == nChar && IsKeyShift() )
	{
		ShowWindow( SW_HIDE );
		return;
	}

	if( FALSE == IsKeyNoShift() )
		return;

	if( VK_ESCAPE == nChar )
	{
			if( -1 != m_nHilite )
			SetItem( -1, NULL );
		else if( GetFocus() == this )
			AfxGetMainWnd()->SetFocus();

		return;
	}

	switch( nChar )
	{
	case VK_UP:
	case VK_LEFT:
		if( m_arpItem.GetSize() <= 1 )
			return;

		if( -1 == m_nHilite )
			m_nHilite = m_nCurItem;

		do
		{
			if( m_nHilite - 1 >= 0 )
				m_nHilite--;
			else
				m_nHilite = m_arpItem.GetSize() - 1;
		}while( SEPARATOR_ITEM == ((SItem*)m_arpItem.GetAt( m_nHilite ))->nID );

		InvalidateRect( NULL, FALSE );
		break;

	case VK_DOWN:
	case VK_RIGHT:
		if( m_arpItem.GetSize() <= 1 )
			return;

		if( -1 == m_nHilite )
			m_nHilite = m_nCurItem;

		do
		{
			if( m_nHilite + 1 < m_arpItem.GetSize() )
				m_nHilite++;
			else
				m_nHilite = 0;
		}while( SEPARATOR_ITEM == ((SItem*)m_arpItem.GetAt( m_nHilite ))->nID );

		InvalidateRect( NULL, FALSE );
		break;

	case VK_RETURN:
		if( -1 != m_nHilite )
			SetItem( m_nHilite, ((SItem*)m_arpItem.GetAt( m_nHilite )) );

		break;
	}
}

void CToolBox::OnMouseMove( UINT nFlags, CPoint point )
{
	INT nItem = GetItemAt( point );
	SetItem( nItem, NULL, TRUE );

	//{{ bug(1) :Solution(1)
	// Timer on
	/*if( -1 != m_nPressed )
	{
		m_nPressed = -1;
		KillTimer( gc_nPopupTimerID );
		if( -1 != m_nHilite && ((SItem*)m_arpItem.GetAt( m_nHilite ))->arpGroup.GetSize() )
		{
			// Restart timer
			SetTimer( gc_nPopupTimerID, gc_nPopupTimerDur, NULL );
			m_nPressed = m_nHilite;
			SetCapture();
		}
	}*/
	//}} bug(1) :Solution(1)
}

void CToolBox::OnLButtonUp( UINT nFlags, CPoint point ) 
{
	SItem* psItem;
	INT nItem = GetItemAt( point, &psItem );
	SetItem( nItem, psItem );
	m_bPressed = FALSE;
}

void CToolBox::OnLButtonDown( UINT nFlags, CPoint point ) 
{
	SItem* psItem;
	INT nItem = GetItemAt( point, &psItem );
	if( -1 != nItem )
	{
		if( psItem->arpGroup.GetSize() )
		{
			SetTimer( gc_nPopupTimerID, gc_nPopupTimerDur, NULL );
			m_nPressed = nItem;
		}

		SetCapture();
		m_bPressed = TRUE;
	}
}

void CToolBox::OnTimer( UINT nIDEvent ) 
{
	if( gc_nPopupTimerID == nIDEvent )
	{
		KillTimer( nIDEvent );
		SetItem( m_nPressed, (SItem*)m_arpItem.GetAt( m_nPressed ) );
		ReleaseCapture();
		m_bPressed = FALSE;
		ShowPopup( m_nPressed );
		m_nPressed = -1;
	}

	CToolFrmWnd::OnTimer( nIDEvent );
}

void CToolBox::ShowPopup( INT nIndex )
{
	SItem* psItem = (SItem*)m_arpItem.GetAt( nIndex );
	INT nCount = psItem->arpGroup.GetSize();
	if( 0 == nCount )
		return;

	CPopupWnd* pPopupWnd = new CPopupWnd;
	pPopupWnd->Create( this );

	pPopupWnd->m_parpGrp = &psItem->arpGroup;
	pPopupWnd->m_cbItem = m_cbItem;

	CPoint pt( psItem->rect.right, psItem->rect.bottom );
	ClientToScreen( &pt );
	INT nSel = pPopupWnd->Track( pt );

	delete pPopupWnd;

	if( -1 != nSel )
	{
		SItem* psSelItem = (SItem*)psItem->arpGroup.GetAt( nSel );

		// Selected same item
		if( psSelItem == psItem )
			return;

		SwapItem( nIndex, nSel );
		SetItem( nIndex, psSelItem );
	}
}

void CToolBox::SwapItem( INT nIndex, INT nSel )
{
	SItem* psItem = (SItem*)m_arpItem.GetAt( nIndex );
	SItem* psSelItem = (SItem*)psItem->arpGroup.GetAt( nSel );

	psSelItem->arpGroup.Copy( psItem->arpGroup );
	psItem->arpGroup.RemoveAll();

	m_arpItem.SetAt( nIndex, psSelItem );
	psSelItem->rect = psItem->rect;
}