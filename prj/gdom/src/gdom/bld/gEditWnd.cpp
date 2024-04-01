#include "stdafx.h"
#include <bld\gEditWnd.h>

#include <g\tools\sTool.h>
#include <g\tools\eRectTool.h>
#include <g\tools\eLineTool.h>
#include <cu\reg.h>

#include <cu\msg.h>
#include <g\type\gElementPriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
LPCTSTR CGEditWndEvent::ActiveGroupChange = _T("ActiveGroupChange");
CGEditWndEvent::CGEditWndEvent()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGEditRulerWnd::CGEditRulerWnd() {
	m_pEditView = NULL; }

CGEditRulerWnd::~CGEditRulerWnd()
{
	SetView( NULL );
}

void CGEditRulerWnd::ShowSettingDlg() {
	CRulerWnd::ShowSettingDlg(); }

BOOL CGEditRulerWnd::OnInitialUpdate() {
	return TRUE; }

BOOL CGEditRulerWnd::SetView( CGIEditView* pView )
{
	if( m_pEditView )
	{
		m_pEditView->RemoveEventListener( CGZoomEvent::EVENT, *this, FALSE );
		m_pEditView->RemoveEventListener( CGScrollEvent::EVENT, *this, FALSE );
		m_pEditView->Release();
	}

	m_pEditView = pView;
	if( m_pEditView )
	{
		m_pEditView->AddRef();
		m_pEditView->AddEventListener( CGZoomEvent::EVENT, *this, FALSE );
		m_pEditView->AddEventListener( CGScrollEvent::EVENT, *this, FALSE );
	}

	return TRUE;
}

void CGEditRulerWnd::CalcCoord( GPointF& rpptf, INT nType ) const
{
	if( NULL == m_pEditView )
	{
		ASSERT( NULL );
		return;
	}

	Matrix mtx;
	m_pEditView->GetCTM( mtx );
	switch( nType )
	{
	case enRCC_PagePointF:
		mtx.Invert();
		mtx.TransformPoints( (PointF*)&rpptf );
		break;

	case enRCC_ViewPointF:
		mtx.TransformPoints( (PointF*)&rpptf );
		break;

	case enRCC_PageVectPointF:
		mtx.Invert();
		mtx.TransformVectors( (PointF*)&rpptf );
		break;

	case enRCC_ViewVectPointF:
		mtx.TransformVectors( (PointF*)&rpptf );
		break;

	default:
		ASSERT( FALSE );
	}
}

void CGEditRulerWnd::HandleEvent( CGEvent& rEvent )
{
	if( rEvent.GetType() == CGZoomEvent::EVENT
	 || rEvent.GetType() == CGScrollEvent::EVENT )
	{
		CGZoomEvent* pZoomEvent = (CGZoomEvent*)&rEvent;

		m_ptfDocOrg.x = 0.f;
		m_ptfDocOrg.y = 0.f;
		CalcCoord( m_ptfDocOrg, enRCC_ViewPointF );

		pZoomEvent->GetScale( m_fScaleX, m_fScaleY );
		Matrix mtxO2V;
		m_pEditView->GetCTM( mtxO2V );
		GPointF ptf;
		ptf.x = 100000.f;
		ptf.y = 0.f;
		mtxO2V.TransformVectors( (PointF*)&ptf );
		if( ptf.x < 0.f )
			ptf.x *= -1.f;

		m_fScaleX *= ptf.x / 100000.f;

		ptf.x = 0.f;
		ptf.y = 100000.f;
		mtxO2V.TransformVectors( (PointF*)&ptf );
		if( ptf.y < 0.f )
			ptf.y *= -1.f;

		m_fScaleY *= ptf.y / 100000.f;

		SetScale( m_fScaleX, m_fScaleY );

		if( m_pEditView && CGUnit::PERCENT_UNIT == m_pUnit->GetUnit() )
		{
			CRulerUnitPercent* pPercentUnit = (CRulerUnitPercent*)m_pUnit;
			m_pEditView->GetDocSize( pPercentUnit->m_fPageCx, pPercentUnit->m_fPageCy );
		}

		m_pUnit->Update();
		Invalidate( FALSE );
		UpdateWindow();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
IMPL_GTPYECLASS_DYNCREATE( CGEditViewWnd, CGViewWnd, _T("editViewWnd") )
BEGIN_MESSAGE_MAP(CGEditViewWnd, CGViewWnd)
	//{{AFX_MSG_MAP(CGEditViewWnd)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

SGridConf CGEditViewWnd::ms_sGridConf;
CGEditViewWnd::CGEditViewWnd()
{
	m_pgInstanceType = &GetClassType();
	m_pwndRuler = NULL;
	m_pwndEdit = NULL;
}

BOOL CGEditViewWnd::OnInitialUpdate()
{
	if( FALSE == CGViewWnd::OnInitialUpdate() )
		return FALSE;

	LoadGridSetting();
	*((SGridConf*)&m_sViewGrid) = ms_sGridConf;
	CalcGrid();
	return TRUE;
}

CGIUITool* CGEditViewWnd::CreateTool( const CGType& rType )
{
	CGIUITool* pTool = (CGIUITool*)CreateFactoryObject( rType.GetName(), (void*)&rType );
	if( pTool )
		return pTool;

	if( rType == CGISelectionTool::GetClassType() )
		return new CGISelectionTool;

	return CGViewWnd::CreateTool( rType );
}

#define _VIEW_REGK _T("EditorView Window")
#define _GRID_SETTING_REGK _VIEW_REGK _T("\\Grid")
#define _GRID_UNIT			_T("Unit")
#define _GRID_MAJOR_DIV		_T("Major")
#define _GRID_MINOR_DIV		_T("Minor")
#define _GRID_STYLE			_T("Style")
#define _GRID_VISIBLE		_T("Visible")
#define _GRID_SNAP			_T("Snap")
#define _GRID_COLOR			_T("Color")
void CGEditViewWnd::SaveGridSetting()
{
	WriteProfileInt( NULL, _GRID_SETTING_REGK, _GRID_UNIT, ms_sGridConf.enUnit );
	WriteProfileInt( NULL, _GRID_SETTING_REGK, _GRID_STYLE, ms_sGridConf.nStyle );
	WriteProfileInt( NULL, _GRID_SETTING_REGK, _GRID_MINOR_DIV, ms_sGridConf.nMinorDiv );
	WriteProfileFloat( NULL, _GRID_SETTING_REGK, _GRID_MAJOR_DIV, ms_sGridConf.fMajor );
	WriteProfileBool( NULL, _GRID_SETTING_REGK, _GRID_VISIBLE, ms_sGridConf.bVisible );
	WriteProfileBool( NULL, _GRID_SETTING_REGK, _GRID_SNAP, ms_sGridConf.bSnap );
}

void CGEditViewWnd::LoadGridSetting()
{
	ms_sGridConf.crf = RGB(255, 0, 0);

	ms_sGridConf.enUnit = (CGUnit::UNIT)GetProfileInt( NULL, _GRID_SETTING_REGK, _GRID_UNIT, CGUnit::INCH_UNIT, CGUnit::INCH_UNIT, CGUnit::MILS_UNIT );
	ms_sGridConf.nStyle = GetProfileInt( NULL, _GRID_SETTING_REGK, _GRID_STYLE, SGridConf::enGSLine, SGridConf::enGSDot, SGridConf::enGSLine );
	ms_sGridConf.nMinorDiv = GetProfileInt( NULL, _GRID_SETTING_REGK, _GRID_MINOR_DIV, 4, 1, 100 );
	ms_sGridConf.fMajor = GetProfileFloat( NULL, _GRID_SETTING_REGK, _GRID_MAJOR_DIV, 1.0f, 1.0f, 100.0f );
	ms_sGridConf.bVisible = GetProfileBool( NULL, _GRID_SETTING_REGK, _GRID_VISIBLE, 0 );
	ms_sGridConf.bSnap = GetProfileBool( NULL, _GRID_SETTING_REGK, _GRID_SNAP, 0 );
}

void CGEditViewWnd::CalcGrid()
{
	if( m_sViewGrid.fMajor <= 0.0f )
		return;

	FLOAT z_fxDpi = 96.0f;
	FLOAT z_fyDpi = 96.0f;

	FLOAT fDocCx, fDocCy;
	m_pView->GetSize( fDocCx, fDocCy );
	FLOAT z_cbPagecx = fDocCx;
	FLOAT z_cbPagecy = fDocCy;

	FLOAT fUnitConst = 1.0f;
	switch( m_sViewGrid.enUnit )
	{
	case CGUnit::PIXEL_UNIT:
		fUnitConst = 1.0f;
		break;

	case CGUnit::POINTS_UNIT:
		fUnitConst = 72.0f;
		break;

	case CGUnit::PERCENT_UNIT:
		fUnitConst = z_fxDpi / z_cbPagecx;
		break;

	case CGUnit::INCH_UNIT:
		fUnitConst = z_fxDpi;
		break;

	case CGUnit::CM_UNIT:
		fUnitConst = z_fxDpi / 2.54f;
		break;

	case CGUnit::MM_UNIT:
		fUnitConst = z_fxDpi / 25.4f;
		break;

	case CGUnit::MILS_UNIT:
		fUnitConst = z_fxDpi / 1000.0f;
		break;
	}

	FLOAT z_fxZoom, z_fyZoom;
	m_pView->GetScale( z_fxZoom, z_fyZoom );
	z_fxZoom *= 100.f;
	z_fyZoom *= 100.f;
	m_sViewGrid.v.fMajorDiv = m_sViewGrid.fMajor * fUnitConst;

	m_sViewGrid.v.fMajor = (m_sViewGrid.fMajor * fUnitConst * z_fxZoom) / 100.0f;
	while( m_sViewGrid.v.fMajor < 4.0f )
		m_sViewGrid.v.fMajor *= 2.0f;

	m_sViewGrid.v.fMinor = m_sViewGrid.v.fMajor / m_sViewGrid.nMinorDiv;
	m_sViewGrid.v.fMinorDiv = m_sViewGrid.v.fMajorDiv / m_sViewGrid.nMinorDiv;

	m_pView->Update();
	FLOAT fRenderCx, fRenderCy;
	m_pView->GetRenderSize( fRenderCx, fRenderCy );

	FLOAT z_cbPageZoomedcx = fRenderCx;
	FLOAT z_cbPageZoomedcy = fRenderCy;

	FLOAT z_rcViewleft = 0;
	FLOAT z_rcViewtop = 0;
	FLOAT z_rcViewright = fRenderCx;
	FLOAT z_rcViewbottom = fRenderCy;

	BOOL bHorzScrollable, bVertBarScrollable;
	m_pView->GetScrollable( bHorzScrollable, bVertBarScrollable );
	if( bHorzScrollable )
	{
		m_sViewGrid.v.fsx = ((INT)(((FLOAT)z_rcViewleft - m_sViewGrid.v.fMajor - 1) / m_sViewGrid.v.fMajor)) * m_sViewGrid.v.fMajor;
		if( m_sViewGrid.v.fsx < 0 ) 
			m_sViewGrid.v.fsx = 0;

		m_sViewGrid.v.fex = ((INT)(((FLOAT)z_rcViewright + m_sViewGrid.v.fMajor + 1) / m_sViewGrid.v.fMajor)) * m_sViewGrid.v.fMajor;
	}
	else
	{
		m_sViewGrid.v.fsx = 0;
		m_sViewGrid.v.fex = (FLOAT)z_cbPageZoomedcx;
	}

	if( bVertBarScrollable )
	{
		m_sViewGrid.v.fsy = ((INT)(((FLOAT)z_rcViewtop - m_sViewGrid.v.fMajor - 1) / m_sViewGrid.v.fMajor)) * m_sViewGrid.v.fMajor;
		if( m_sViewGrid.v.fsy < 0 ) 
			m_sViewGrid.v.fsy = 0;

		m_sViewGrid.v.fey = ((INT)(((FLOAT)z_rcViewbottom + m_sViewGrid.v.fMajor + 1) / m_sViewGrid.v.fMajor)) * m_sViewGrid.v.fMajor;
	}
	else
	{
		m_sViewGrid.v.fsy = 0;
		m_sViewGrid.v.fey = (FLOAT)z_cbPageZoomedcy;
	}	

	m_sViewGrid.bMinor = (m_sViewGrid.nMinorDiv > 1 && m_sViewGrid.v.fMinor > 4);
}

void CGEditViewWnd::DrawView( Graphics& rGdip, const CRect& rrcPaint, BOOL bPrint /*= FALSE*/ )
{
	CGViewWnd::DrawView( rGdip, rrcPaint, bPrint );

	if( FALSE == bPrint )
	{
		HDC hDC = rGdip.GetHDC();
		CDC dc;
		dc.Attach( hDC );
		CRect rct = rrcPaint;

		if( m_pActiveTool && CGIUITool::UPPER_DRAW_TYPE == m_pActiveTool->GetDrawType() )
			m_pActiveTool->Draw( dc, rct );

		if( m_pwndEdit )
		{
			CGISelectionTool* pSelTool = (CGISelectionTool*)m_pwndEdit->GetTool( CGISelectionTool::GetClassType() );
			if( pSelTool && m_pActiveTool && 
				pSelTool != m_pActiveTool )
				pSelTool->Draw( dc, rct );
		}

		if( 1 )
		{
			dc.Detach();
			rGdip.ReleaseHDC( hDC );
		}

		// Draw ruler 
		if( m_pwndRuler && m_pwndRuler->m_bVisible )
		{
			rGdip.ResetTransform();
			Matrix mtx;
			m_pView->GetCTM( mtx );
			rGdip.SetTransform( &mtx );
			m_pwndRuler->DrawGuides( rGdip );
		}

		if( 0 )
		{
			DrawGrid( &dc );

			dc.Detach();
			rGdip.ReleaseHDC( hDC );
		}
	}
}

void CGEditViewWnd::DrawGrid( CDC* pDC )
{
	//if( FALSE == m_sViewGrid.bVisible  )
		//return;

	if( SGridConf::enGSDot == m_sViewGrid.nStyle )
		DrawDotGrid( pDC );
	else
		DrawLineGrid( pDC );
}

void CGEditViewWnd::DrawLineGrid( CDC* pDC )
{
/*	FLOAT x, y, n;

	m_pView->Update();
	FLOAT fRenderCx, fRenderCy;
	m_pView->GetRenderSize( fRenderCx, fRenderCy );

	FLOAT z_cbPageZoomedcx = fRenderCx;
	FLOAT z_cbPageZoomedcy = fRenderCy;

	// Draw Minor division
	if( m_sViewGrid.bMinor )
	{
		FLOAT fex, fey;
		FLOAT fix, fiy;
		FLOAT fmx, fmy;
		for( x = m_sViewGrid.v.fsx, fmx = x + m_sViewGrid.v.fMajor; x < m_sViewGrid.v.fex; x = fmx, fmx = x + m_sViewGrid.v.fMajor )
            for( fix = x + m_sViewGrid.v.fMinor, n = (INT)fix, fex = fix + m_sViewGrid.v.fMajor; fix < fex && n < z_cbPageZoomedcx; fix += m_sViewGrid.v.fMinor, n = (INT)fix )
				if( fix != fmx )
					for( FLOAT fny = m_sViewGrid.v.fsy; fny < z_cbPageZoomedcy && fny < m_sViewGrid.v.fey; fny += 2.0f )
					{
						INT ny = (INT)fny;
						pDC->SetPixel( n, ny, m_sViewGrid.crf );
					}
		
		for( y = m_sViewGrid.v.fsy, fmy = y + m_sViewGrid.v.fMajor; y < m_sViewGrid.v.fey; y = fmy, fmy = y + m_sViewGrid.v.fMajor )
            for( fiy = y + m_sViewGrid.v.fMinor, n = (INT)fiy, fey = fiy + m_sViewGrid.v.fMajor; fiy < fey && n < z_cbPageZoomedcy; fiy += m_sViewGrid.v.fMinor, n = (INT)fiy )
				if( fiy != fmy )
					for( FLOAT fnx = m_sViewGrid.v.fsx; fnx < z_cbPageZoomedcx && fnx < m_sViewGrid.v.fex; fnx += 2 )
					{
						INT nx = (INT)fnx;
						pDC->SetPixel( nx, n, m_sViewGrid.crf );
					}
	}
		
	// Draw Major division
	{
		CPen pen, *pOldPen;
		pen.CreatePen( PS_SOLID, 1, m_sViewGrid.crf );
		pOldPen = pDC->SelectObject( &pen );

		for( x = m_sViewGrid.v.fsx; x < m_sViewGrid.v.fex; x += m_sViewGrid.v.fMajor )
		{
			n = (INT)x;
			pDC->MoveTo( n, 0 );
			pDC->LineTo( n, z_cbPageZoomedcy );
		}

		for( y = m_sViewGrid.v.fsy; y < m_sViewGrid.v.fey; y += m_sViewGrid.v.fMajor )
		{
			n = (INT)y;
			pDC->MoveTo( 0, n );
			pDC->LineTo( z_cbPageZoomedcx, n );
		}

		pDC->SelectObject( pOldPen );
	}*/
}

void CGEditViewWnd::DrawDotGrid( CDC* pDC )
{
	/*FLOAT x;
	FLOAT y;
	INT nx, ny;
	
	m_pView->Update();
	FLOAT fRenderCx, fRenderCy;
	m_pView->GetRenderSize( fRenderCx, fRenderCy );

	FLOAT z_cbPageZoomedcx = fRenderCx;
	FLOAT z_cbPageZoomedcy = fRenderCy;

	// Draw with Minor division
	if( m_sViewGrid.bMinor )
	{
		FLOAT ix, iy;
		FLOAT ex, ey;

		for( y = m_sViewGrid.v.fsy; y < m_sViewGrid.v.fey; y += m_sViewGrid.v.fMajor )
            for( iy = y + m_sViewGrid.v.fMinor, ny = (INT)iy, ey = iy + m_sViewGrid.v.fMajor; iy < ey && ny < z_cbPageZoomedcy; iy += m_sViewGrid.v.fMinor, ny = (INT)iy )
				for( x = m_sViewGrid.v.fsx; x < m_sViewGrid.v.fex; x += m_sViewGrid.v.fMajor )
					for( ix = x + m_sViewGrid.v.fMinor, nx = (INT)ix, ex = ix + m_sViewGrid.v.fMajor; ix < ex && nx < z_cbPageZoomedcx; ix += m_sViewGrid.v.fMinor, nx = (INT)ix )
						pDC->SetPixel( nx, ny, m_sViewGrid.crf );

	}
	else
	{
		for( y = m_sViewGrid.v.fsy, ny = (INT)y; y < m_sViewGrid.v.fey; y += m_sViewGrid.v.fMajor, ny = (INT)y )
			for( x = m_sViewGrid.v.fsx, nx = (INT)x; x < m_sViewGrid.v.fex; x += m_sViewGrid.v.fMajor, nx = (INT)x )
				pDC->SetPixel( nx, ny, m_sViewGrid.crf );
	}*/
}

BOOL CGEditViewWnd::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
	if( m_pwndRuler && m_pwndRuler->m_bVisible )
	{
		CPoint point;
		GetCursorPos( &point );
		m_pwndRuler->ScreenToClient( &point );

		UINT nHitTest = m_pwndRuler->HitTest( point );
		if( CRulerWnd::HT_NOTHING != nHitTest )
			nHitTest = nHitTest;

		if( m_pwndRuler->On_SetCursor( this, nHitTest, 0 ) )
			return TRUE;
	}

	return CGViewWnd::OnSetCursor( pWnd, nHitTest, message );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
IMPL_BASE_GTPYECLASS_DYNCREATE( CGEditWnd, _T("editWnd") )
BEGIN_MESSAGE_MAP(CGEditWnd, CGWin)
	//{{AFX_MSG_MAP(CGEditWnd)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENT_LINK( CGEditWnd, CGEventNode )
	ON_EVT_PHASE( CGViewWndEvent::DocumentChange, CGEvent::CAPTURING_PHASE, OnDocumentChangeEvent )
	
	ON_EVT_PHASE_NODE_LINK_CHANGE( CGMutationEvent::DOMNodeInserted, CGEvent::CAPTURING_PHASE, OnNodeInsertedEvent )
	ON_EVT_PHASE_NODE_LINK_CHANGE( CGMutationEvent::DOMNodeRemoved, CGEvent::CAPTURING_PHASE, OnNodeRemoveEvent )
END_EVENT_LINK()

CGEditWnd::CGEditWnd()
{
	m_pgInstanceType = &GetClassType();

	m_pwndRuler = NULL;
	m_pwndPlay = NULL;	
	m_pwndView = NULL;
	m_pView = NULL;
}

CGEditWnd::~CGEditWnd()
{
	DeleteAllTool();

	RemoveEventListener( CGViewWndEvent::DocumentChange, *this, TRUE );

	if( m_pwndPlay )
	{
		if( m_pwndRuler )
			m_pwndRuler->RemoveChild( *m_pwndPlay );

		delete m_pwndPlay;
	}

	if( m_pwndRuler )
	{
		RemoveChild( *m_pwndRuler );
		delete m_pwndRuler;
	}

	if( m_pView )
		m_pView->Release();
}

BOOL CGEditWnd::Create( CWnd* pParent, INT nID, RECT& rect /*= CRect(0,0,0,0)*/ )
{
	if( FALSE == CGWin::Create( NULL, NULL, WS_CHILD | WS_VISIBLE, rect, pParent, nID ) )
		return FALSE;

	return OnInitialUpdate();
}

BOOL CGEditWnd::SetPlayWindow( CGPlayWnd& rwndPlay ) 
{
	if( m_pwndPlay )
		return FALSE;

	m_pwndPlay = &rwndPlay;
	return TRUE;
}

const CGIView* CGEditWnd::GetView() const 
{

	const CGViewWnd* pwndView = GetViewWindow();
	if( NULL == pwndView )
		return NULL;

	return pwndView->GetView(); 
}
	
BOOL CGEditWnd::SetView( CGIView& rView )
{
	if( m_pView || NULL == &rView )
		return FALSE;

	m_pView = &rView;
	m_pView->AddRef();
	return TRUE;
}

const CGViewWnd* CGEditWnd::GetViewWindow() const 
{
	if( NULL == m_pwndPlay )
		return NULL;

	return m_pwndPlay->GetViewWindow(); 
}

BOOL CGEditWnd::SetViewWindow( CGViewWnd& rwndView ) 
{
	if( m_pwndView )
		return FALSE;

	m_pwndView = &rwndView;
	return TRUE;
}

void* CGEditWnd::CreateElementToolCB( LPCTSTR pClassName, void* pCookie )
{
	CGType* pType = (CGType*)pCookie;
	if( NULL == pType )
	{
		ASSERT( NULL );
		return NULL;
	}

	CGIElementUITool* pElementTool = NULL;
	if( *pType == CGIRectElement::GetClassType() )
		pElementTool = new CGIRectElementTool;
	else if( *pType == CGILineElement::GetClassType() )
		pElementTool = new CGILineElementTool;

	return pElementTool;
}

void* CGEditWnd::CreateFactoryObject( const CGType& rType )
{
	void* pObject = CGEventNode::CreateFactoryObject( rType );
	if( pObject )
		return pObject;

	if( rType == CGEditRulerWnd::GetClassType() )
		return new CGEditRulerWnd;
	else if( rType == CGPlayWnd::GetClassType() )
		return new CGPlayWnd;
	else if( rType == CGEditViewWnd::GetClassType() )
		return new CGEditViewWnd;
	else if( rType == CGIEditView::GetClassType() )
		return new CGIEditView;

	return NULL;
}

BOOL CGEditWnd::OnInitialUpdate()
{
	ModifyStyle( 0, WS_CLIPCHILDREN );

	AddEventListener( CGViewWndEvent::DocumentChange, *this, TRUE );
		
	// Create Ruler instance and initialize
	ASSERT( NULL == m_pwndRuler );
	VERIFY( m_pwndRuler = (CGEditRulerWnd*)CreateFactoryObject( CGEditRulerWnd::GetClassType() ) );
	if( NULL == m_pwndRuler )
		return FALSE;

	// Link ruler as child and create its window
	AppendChild( *m_pwndRuler );
	if( FALSE == m_pwndRuler->Create( NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, EID_RULER_WND ) )
		return FALSE;

	// Create Player instance if not there
	if( NULL == m_pwndPlay )
	{
		VERIFY( m_pwndPlay = (CGPlayWnd*)CreateFactoryObject( CGPlayWnd::GetClassType() ) );
		if( NULL == m_pwndPlay )
			return FALSE;
	}

	// Link player as child of ruler and create its window
	m_pwndRuler->AppendChild( *m_pwndPlay );
	if( m_pwndView )
	{
		if( FALSE == m_pwndView->IsDerivedFrom( CGEditViewWnd::GetClassType() ) )
		{
			delete m_pwndView;
			m_pwndView = NULL;
		}
	}

	// Create Edit View window instance if not there
	if( NULL == m_pwndView )
	{
		VERIFY( m_pwndView = (CGEditViewWnd*)CreateFactoryObject( CGEditViewWnd::GetClassType() ) );
		if( NULL == m_pwndView )
			return FALSE;
	}

	// Pass this to Player window
	m_pwndPlay->SetViewWindow( *m_pwndView );

	if( m_pView )
	{
		if( FALSE == m_pView->IsDerivedFrom( CGIEditView::GetClassType() ) )
		{
			m_pView->Release();
			m_pView = NULL;
		}
	}

	if( NULL == m_pView )
	{
		VERIFY( m_pView = (CGIEditView*)CreateFactoryObject( CGIEditView::GetClassType() ) );
		if( NULL == m_pView )
			return FALSE;

		m_pView->AddRef();
	}

	m_pwndPlay->SetView( *m_pView );

	if( FALSE == m_pwndPlay->Create( NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), m_pwndRuler, EID_PLAY_WND ) )
		return FALSE;

	m_pwndPlay->SetUIHook( this );
	if( FALSE == m_pwndPlay->OnInitialUpdate() )
		return FALSE;

	CGEditViewWnd* pwndView = (CGEditViewWnd*)m_pwndPlay->GetViewWindow();
	if( FALSE == pwndView->IsDerivedFrom( CGEditViewWnd::GetClassType() ) )
		return FALSE;

	CGIEditView* pView = (CGIEditView*)pwndView->GetView();
	if( FALSE == pView->IsDerivedFrom( CGIEditView::GetClassType() ) )
		return FALSE;
	
	pwndView->m_pwndRuler = m_pwndRuler;
	pwndView->m_pwndEdit = this;

	m_pwndRuler->m_pResizeWnd = m_pwndPlay;
	ASSERT( pwndView );
	m_pwndRuler->m_pViewWnd = pwndView;

	ASSERT( pView );
	m_pwndRuler->SetView( pView );

	if( FALSE == m_pwndRuler->OnInitialUpdate() )
		return FALSE;

	// Create a Zoom Tool if not there in View window
	CGIUITool* piTool = &pwndView->GetZoomTool();
	if( NULL == piTool )
		VERIFY( piTool = pwndView->CreateTool( CGIZoomTool::GetClassType() ) );
	
	if( piTool )
	{
		pwndView->SetActiveTool( piTool );
		AddTool( piTool, CGIZoomTool::GetClassType() );
	}

	VERIFY( piTool = pwndView->CreateTool( CGIPanTool::GetClassType() ) );
	if( piTool )
		AddTool( piTool, CGIPanTool::GetClassType() );

	// Create a Selection Tool and add to View window
	VERIFY( piTool = pwndView->CreateTool( CGISelectionTool::GetClassType() ) );
	if( piTool )
	{
		CGISelectionTool* pSTool = (CGISelectionTool*)piTool;
		CGClassFactory* pClassFactory = pSTool->GetClassFactory();
		ASSERT( pClassFactory );
		if( pClassFactory )
		{
			pClassFactory->AddCreator( CGIRectElement::ELEMENT_TAGNAME, CGEditWnd::CreateElementToolCB );
			pClassFactory->AddCreator( CGILineElement::ELEMENT_TAGNAME, CGEditWnd::CreateElementToolCB );
		}

		AddTool( piTool, CGISelectionTool::GetClassType() );
		pSTool->SetActiveGroup( pView );
	}

	// Create a Element Tool for Rectangle and Line and add to View window
	m_pRectTool = new CGIRectElementTool;
	ASSERT( m_pRectTool );
	if( m_pRectTool )
		AddTool( m_pRectTool, CGIRectElementTool::GetClassType() );

	m_pLineTool = new CGILineElementTool;
	ASSERT( m_pLineTool );
	if( m_pLineTool )
		AddTool( m_pLineTool, CGILineElementTool::GetClassType() );

	return TRUE;
}

void CGEditWnd::OnSize(UINT nType, int cx, int cy) 
{
	CGWin::OnSize(nType, cx, cy);
	if( m_pwndRuler && m_pwndRuler->m_hWnd )
		m_pwndRuler->MoveWindow( 0, 0, cx, cy );	
}

INT CGEditWnd::FindTool( CGIUITool* pTool ) const
{
	INT nCount = m_arrTool.GetSize();
	const SToolItem* pItem = m_arrTool.GetData();
	for( INT i = 0; i < nCount; i++ )
		if( pTool == pItem[i].pTool )
			return i;
	
	return -1;
}

CGIUITool* CGEditWnd::GetTool( const CGType& rType ) const
{
	INT nCount = m_arrTool.GetSize();
	const SToolItem* pItem = m_arrTool.GetData();
	for( INT i = 0; i < nCount; i++ )
		if( *pItem[i].pType == rType )
			return pItem[i].pTool;
	
	return NULL;
}

BOOL CGEditWnd::AddTool( CGIUITool* pTool, const CGType& rType )
{
	if( -1 != FindTool( pTool ) )
		return FALSE;

	pTool->AddRef();
	SToolItem sItem = { pTool, &rType };
	m_arrTool.Add( sItem );
	return TRUE;
}

BOOL CGEditWnd::RemoveTool( CGIUITool* pTool )
{
	INT nIndex = FindTool( pTool );
	if( -1 != nIndex )
		return FALSE;

	pTool->Release();
	m_arrTool.RemoveAt( nIndex );
	return TRUE;
}

void CGEditWnd::DeleteAllTool()
{
	INT nCount = m_arrTool.GetSize();
	SToolItem* pItem = m_arrTool.GetData();
	for( INT i = 0; i < nCount; i++ )
		pItem[i].pTool->Release();

	m_arrTool.RemoveAll();
}

const CGType& CGEditWnd::GetToolType( UINT nChar ) const 
{
	if( 'Z' == nChar )
		return CGIZoomTool::GetClassType();

	if( 'H' == nChar )
		return CGIPanTool::GetClassType();

	if( 'V' == nChar )
		return CGISelectionTool::GetClassType();

	if( 'R' == nChar )
		return CGIRectElementTool::GetClassType();

	if( 'L' == nChar )
		return CGILineElementTool::GetClassType();

	return CGType::GetNullType(); 
}

BOOL CGEditWnd::SelectTool( UINT nKey )
{
	// According to the key pressed, change Active Tool
	const CGType& rType = GetToolType( nKey );
	return SelectTool( rType );
}

BOOL CGEditWnd::SelectTool( const CGType& rType )
{
	if( rType == CGType::GetNullType() )
		return FALSE;
	
	CGIUITool* pTool = GetTool( rType );
	return SelectTool( *pTool );
}

BOOL CGEditWnd::SelectTool( CGIUITool& rTool )
{
	CGViewWnd* pwndView = GetViewWindow();
	ASSERT( pwndView );

	CGIUITool* pActiveTool = pwndView->GetActiveTool();
	if( &rTool == pActiveTool )
	{
		CGISelectionTool* pSelTool = GetSelectionTool();
		ASSERT( pSelTool );
		if( &rTool != pSelTool || NULL == pSelTool->GetDefaultElementTool() )
			return TRUE;
	}
	
	// Is Element Tool
	if( rTool.IsDerivedFrom( CGIElementTool::GetClassType() ) )
		SetElementTool( *((CGIElementTool*)&rTool) );
	else if( rTool.IsDerivedFrom( CGISelectionTool::GetClassType() ) )
		SetSelectionTool( *((CGISelectionTool*)&rTool) );
	else
	{
		pwndView->SetActiveTool( &rTool );
		pwndView->UpdateCursor();
	}
	
	return TRUE;
}

BOOL CGEditWnd::SetElementTool( CGIElementTool& rTool )
{
	// To select the Element Tool, the selection tool should be selected and 
	// then attach the Element Tool to selection tool
	CGISelectionTool* pSelTool = GetSelectionTool();
	ASSERT( pSelTool );
	if( NULL == pSelTool )
		return FALSE;

	// Initialize the Element Tool with View window and parent group to which new has to created.
	CGViewWnd* pwndView = GetViewWindow();
	ASSERT( pwndView );

	CGIView* pView = pwndView->GetView();
	ASSERT( pView );

	rTool.SetNewElementMode( TRUE, pSelTool->GetActiveGroup() );
	rTool.SetView( pView );
	rTool.SetViewWindow( pwndView );
	rTool.SetSelectionTool( pSelTool );

	pSelTool->SetDefaultElementTool( &rTool );
	pwndView->SetActiveTool( pSelTool );	// Instead of the Element tool, make the Selection Tool to be selected
	pwndView->UpdateCursor();
	return TRUE;
}

CGISelectionTool* CGEditWnd::GetSelectionTool() 
{
	CGISelectionTool* pSelTool = (CGISelectionTool*)GetTool( CGISelectionTool::GetClassType() );
	return pSelTool;
}

const CGISelectionTool* CGEditWnd::GetSelectionTool() const
{
	CGISelectionTool* pSelTool = (CGISelectionTool*)GetTool( CGISelectionTool::GetClassType() );
	return pSelTool;
}

BOOL CGEditWnd::SetSelectionTool( CGISelectionTool& rTool )
{
	// If the Selection Tool has attached with a Element tool, removed it
	CGIElementTool* pElementTool = (CGIElementTool*)rTool.GetDefaultElementTool();
	if( pElementTool )
	{
		pElementTool->SetNewElementMode( FALSE );
		rTool.SetDefaultElementTool( NULL );
	}

	CGViewWnd* pwndView = GetViewWindow();
	ASSERT( pwndView );
	pwndView->SetActiveTool( &rTool );
	pwndView->UpdateCursor();
	return TRUE;
}

CGIGroup* CGEditWnd::GetActiveGroup()
{
	CGISelectionTool* pSelTool = GetSelectionTool();
	ASSERT( pSelTool );
	if( NULL == pSelTool )
		return NULL;

	CGIGroup* pGroup = pSelTool->GetActiveGroup();
	return pGroup;
}

const CGIGroup* CGEditWnd::GetActiveGroup() const
{
	const CGISelectionTool* pSelTool = GetSelectionTool();
	ASSERT( pSelTool );
	if( NULL == pSelTool )
		return NULL;

	CGIGroup* pGroup = pSelTool->GetActiveGroup();
	return pGroup;
}

void CGEditWnd::SetActiveGroup( CGIGroup* pGroup )
{
	CGISelectionTool* pSelTool = GetSelectionTool();
	ASSERT( pSelTool );
	if( NULL == pSelTool )
		return;

	CGIGroup* pPrevGroup = pSelTool->GetActiveGroup();
	CGEditWndEvent event;
	event.InitEvent( CGEditWndEvent::ActiveGroupChange, TRUE, TRUE, NULL, 
					 pPrevGroup, pGroup, NULL, CGEditWndEvent::MODIFICATION );

	DispatchEvent( event );
	if( event.GetPreventDefault() )
		return;
	
	pSelTool->SetActiveGroup( pGroup );
}

void CGEditWnd::OnDocumentChangeEvent( CGEvent& rEvent )
{
	CGISelectionTool* pSelTool = GetSelectionTool();
	ASSERT( pSelTool );
	if( NULL == pSelTool )
		return;

	CGViewWndEvent& rViewEvent = *((CGViewWndEvent*)&rEvent);
	CGIDocument* pDocument = (CGIDocument*)rViewEvent.GetRelatedNode();
	INT nAttrChange = rViewEvent.GetAttrChange();
	if( CGViewWndEvent::REMOVAL == nAttrChange )
	{
		pSelTool->SetActiveGroup( NULL );

		pDocument->RemoveEventListener( CGMutationEvent::DOMNodeInserted, *this, TRUE );
		pDocument->RemoveEventListener( CGMutationEvent::DOMNodeRemoved, *this, TRUE );
	}
	else
	{
		CGINode* pRootNode = pDocument->GetFirst();
		if( pRootNode && pRootNode->IsDerivedFrom( CGIGroup::GetClassType() ) )
			pSelTool->SetActiveGroup( (CGIGroup*)pRootNode );
	
		pDocument->AddEventListener( CGMutationEvent::DOMNodeInserted, *this, TRUE );
		pDocument->AddEventListener( CGMutationEvent::DOMNodeRemoved, *this, TRUE );
	}
}

void CGEditWnd::OnNodeInsertedEvent( CGMutationEvent& rEvent )
{
	CGViewWnd* pwndView = GetViewWindow();
	if( NULL == pwndView )
		return;

	CGIDocument* pDocument = pwndView->GetDocument();
	CGINode* pRelatedNode = (CGINode*)rEvent.GetRelatedNode();
	CGINode* pTarget = (CGINode*)rEvent.GetTarget();
	if( pDocument == pRelatedNode 
		&& pDocument->GetFirst() == pTarget
		&& pTarget->IsDerivedFrom( CGIGroup::GetClassType() ) )
		SetActiveGroup( (CGIGroup*)pTarget );
}

void CGEditWnd::OnNodeRemoveEvent( CGMutationEvent& rEvent )
{
	CGViewWnd* pwndView = GetViewWindow();
	if( NULL == pwndView )
		return;

	CGIDocument* pDocument = pwndView->GetDocument();
	CGINode* pRelatedNode = (CGINode*)rEvent.GetRelatedNode();
	CGINode* pTarget = (CGINode*)rEvent.GetTarget();
	if( pDocument == pRelatedNode 
		&& pDocument->GetFirst() == pTarget
		&& pTarget->IsDerivedFrom( CGIGroup::GetClassType() ) )
	{
		CGIGroup* pNewActiveGroup = (CGIGroup*)pTarget;
		CGIGroup* pActiveGroup = GetActiveGroup();
		if( pActiveGroup == pNewActiveGroup )
			SetActiveGroup( NULL );
	}
}

BOOL CGEditWnd::OnMouseMove( const CMouseEvent& rEvent )
{
	UINT nFlags; 
	CPoint point;
	rEvent.GetWindowsParameter( nFlags, point );

	if( m_pwndRuler && m_pwndRuler->On_MouseMove( nFlags, point ) )
		return TRUE;

	return CGWin::OnMouseMove( rEvent );
}

BOOL CGEditWnd::OnLButtonDown( const CMouseEvent& rEvent )
{
	UINT nFlags; 
	CPoint point;
	rEvent.GetWindowsParameter( nFlags, point );

	if( m_pwndRuler && m_pwndRuler->On_LButtonDown( nFlags, point ) )
		return TRUE;

	return CGWin::OnLButtonDown( rEvent );
}

BOOL CGEditWnd::OnLButtonUp( const CMouseEvent& rEvent )
{
	UINT nFlags; 
	CPoint point;
	rEvent.GetWindowsParameter( nFlags, point );

	if( m_pwndRuler && m_pwndRuler->On_LButtonUp( nFlags, point ) )
		return TRUE;

	return CGWin::OnLButtonUp( rEvent );
}

BOOL CGEditWnd::OnLButtonDblClk( const CMouseEvent& rEvent )
{
	UINT nFlags; 
	CPoint point;
	rEvent.GetWindowsParameter( nFlags, point );

	if( m_pwndRuler && m_pwndRuler->On_LButtonDblClk( nFlags, point ) )
		return TRUE;

	return CGWin::OnLButtonDblClk( rEvent );
}

BOOL CGEditWnd::OnKeyDown( const CKbdEvent& rEvent )
{
	UINT nChar, nRepCnt, nFlags;
	rEvent.GetWindowsParameter( nChar, nRepCnt, nFlags );

	if( m_pwndRuler && m_pwndRuler->On_KeyDown( nChar, nRepCnt, nFlags ) )
		return TRUE;

	if( SelectTool( rEvent.m_nKey ) )
		return TRUE;

	return CGWin::OnKeyDown( rEvent );
}

BOOL CGEditWnd::OnKeyUp( const CKbdEvent& rEvent )
{
	UINT nChar, nRepCnt, nFlags;
	rEvent.GetWindowsParameter( nChar, nRepCnt, nFlags );

	if( m_pwndRuler && m_pwndRuler->On_KeyUp( nChar, nRepCnt, nFlags ) )
		return TRUE;

	return CGWin::OnKeyUp( rEvent );
}
