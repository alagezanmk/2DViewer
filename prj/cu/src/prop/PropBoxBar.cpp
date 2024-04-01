#include "stdafx.h"
#include "PropBoxBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropBox class
BEGIN_MESSAGE_MAP( CPropBoxBar, CSizingControlBar )
	//{{AFX_MSG_MAP(CPropBox)
	ON_WM_CREATE()
 	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPropBoxBar::CPropBoxBar()
{
	m_pPropBox = NULL;
	m_szMin.cx = 100;
	m_szMin.cy = 150;
}

CPropBoxBar::~CPropBoxBar()
{}

BOOL CPropBoxBar::PreCreateWindow( CREATESTRUCT& cs )
{
	if( FALSE == CSizingControlBar::PreCreateWindow( cs ) )
		return FALSE;

	cs.style |= WS_CLIPCHILDREN;
	return TRUE;
}

INT CPropBoxBar::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( -1 == CSizingControlBar::OnCreate( lpCreateStruct ) )
		return -1;

	if( NULL == m_pPropBox )
	{
		m_pPropBox = CreatePropBox();
		if( NULL == m_pPropBox )
		{
			TRACE( _T("CPropBoxBar::OnCreate: Property Box object create failed\n") );
			ASSERT( m_pPropBox );
			return -1;
		}
	}
	
	if( m_pPropBox->m_hWnd )
	{
		if( IsWindow( m_pPropBox->m_hWnd ) )
		{
			TRACE( _T("CPropBoxBar::OnCreate: Invalid Property Box Window\n") );
			ASSERT( m_pPropBox );
			return -1;
		}

		// Change parent
		m_pPropBox->SetParent( this );
	}
	else
	{
		if( FALSE == m_pPropBox->Create( NULL, NULL, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
										 nullRECT, this, 
										 NULL, 0, NULL ) )
		{
			TRACE( _T("CPropBoxBar::OnCreate: Property Box window create failed\n") );
			ASSERT( FALSE );
			return FALSE;
		}
	}

	return 0;
}

void CPropBoxBar::OnSize(UINT nType, INT cx, INT cy) 
{
	CSizingControlBar::OnSize( nType, cx, cy );
	if( m_pPropBox && m_pPropBox->m_hWnd )
		m_pPropBox->SetWindowPos( NULL, 0, 0, cx, cy, SWP_NOZORDER );
}