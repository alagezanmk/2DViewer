#include "stdafx.h"

#include <prop\PropRes.h>
#include <prop\PropRes.h>
#include <bld\bmainFrm.h>
#include "bView.h"

#include <g\tools\sTool.h>
#include <g\tools\eRectTool.h>
#include <g\tools\eLineTool.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CBldMainFrm, CIMainFrm)
BEGIN_MESSAGE_MAP(CBldMainFrm, CIMainFrm)
	//{{AFX_MSG_MAP(CBldMainFrm)
	ON_WM_CREATE()
	ON_COMMAND_RANGE( IDM_OBJ_EDIT, IDM_OBJ_TEXT, OnBar )
	ON_UPDATE_COMMAND_UI_RANGE( IDM_OBJ_EDIT, IDM_OBJ_TEXT, OnBarUI )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CBldMainFrm::CBldMainFrm() 
{
	m_pToolBox = NULL; 
	m_pLayerBar = NULL;
}

CBldMainFrm::~CBldMainFrm()
{}	

int CBldMainFrm::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if( -1 == CIMainFrm::OnCreate(lpCreateStruct) )
		return -1;

	EnableDocking(CBRS_ALIGN_ANY);

	if( FALSE == CreatToolBox() )
		return FALSE;

	if( FALSE == CreatePropBox() )
		return FALSE;

	if( FALSE == CreateLayerBar() )
		return FALSE;

	//m_pToolBox->ShowWindow( SW_HIDE );
	m_pLayerBar->ShowWindow( SW_HIDE );
	
	return 0;
}

#define IDC_PROP_BOX	1000
BOOL CBldMainFrm::CreatePropBox()
{
	if( !m_PropBoxBar.Create( _T("Properties"), this, CSize(180,100), TRUE, IDC_PROP_BOX ) )
	{
		TRACE0("Failed to create Property Box\n");
		ASSERT( FALSE );
		return FALSE;
	}

	m_PropBoxBar.SetBarStyle( CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC );
	m_PropBoxBar.EnableDocking( CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT );
	DockControlBar( &m_PropBoxBar );

	return TRUE;
}

BOOL CBldMainFrm::CreatToolBox() 
{
	ASSERT( NULL == m_pToolBox );
	VERIFY( m_pToolBox = new CToolBox );
	BOOL bResult = m_pToolBox->Create( _T("Tools"), CRect(60, 60, 130, 600), this );

	m_pToolBox->LoadImage( IDR_TOOLSBAR, 16 );

	CToolBox::SItemInfo sIF;
	sIF.nImageID = IDR_TOOLSBAR;
	sIF.dwData = NULL;
	sIF.nCy = -1;

	sIF.nID = IDM_OBJ_SELECT;
	sIF.bObjTool = FALSE;
	sIF.cszCaption = "Select(V)";
	sIF.nKey = _T('V');
	sIF.nImageIndex = 0;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_EDIT;
	sIF.cszCaption = "Edit(Q)";
	sIF.nKey = _T('Q');
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_INK_FILLER;
	sIF.cszCaption = "Ink Filler(K)";
	sIF.nKey = _T('K');
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_FILL;
	sIF.cszCaption = "Fill(W)";
	sIF.nKey = _T('W');
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	///----------------------------
	sIF.nID = CToolBox::SEPARATOR_ITEM;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_LINE;
	sIF.bObjTool = TRUE;
	sIF.cszCaption = "Line(L)";
	sIF.nKey = _T('L');
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_RECT;
	sIF.nKey = _T('R');
	sIF.cszCaption = "Rect(R)";
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_ELLIPSE;
	sIF.nKey = _T('E');
	sIF.cszCaption = "Ellipse(E)";
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_POLYLINE;
	sIF.nKey = _T('P');
	sIF.cszCaption = "Polyline(P)";
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_POLYGON;
	sIF.nKey = _T('P');
	sIF.cszCaption = "Polygon(P)";
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_IMAGE;
	sIF.nKey = _T('I');
	sIF.cszCaption = "Image(I)";
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_SPLINE;
	sIF.nKey = _T('S');
	sIF.cszCaption = "Spline(S)";
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	///----------------------------
	sIF.nID = CToolBox::SEPARATOR_ITEM;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_PAN;
	sIF.bObjTool = FALSE;
	sIF.cszCaption = "Panning(H)";
	sIF.nKey = _T('H');
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	sIF.nID = IDM_OBJ_ZOOM;
	sIF.nKey = _T('Z');
	sIF.cszCaption = "Zooming(Z)";
	sIF.nImageIndex++;
	m_pToolBox->AddItem( &sIF, FALSE );

	///----------------------------
	sIF.nID = CToolBox::SEPARATOR_ITEM;
	m_pToolBox->AddItem( &sIF, FALSE );

	///---Color Wnd----------------
	m_wndStyle.Create( nullRECT, m_pToolBox, 1 );
	sIF.nID = CToolBox::CONTROL_ITEM;
	sIF.nKey = 0;
	sIF.nImageIndex = (INT)m_wndStyle.m_hWnd;
	sIF.nCy = 46;
	m_pToolBox->AddItem( &sIF );

	m_pToolBox->ShowWindow( SW_SHOW );
	return TRUE; 
}

void CBldMainFrm::OnBar( UINT nID )
{
	INT nToolID = nID;
	CFrameWnd* pActiveFrame = GetActiveFrame();
	if( pActiveFrame ) 
	{
		CGEditView* pEditView = (CGEditView*)pActiveFrame->GetActiveView();
		if( pEditView && pEditView->IsKindOf( RUNTIME_CLASS(CGEditView) ) )
		{
			CGEditWnd* pEditWnd = (CGEditWnd*)pEditView->GetEditWindow();
			const CGType* pType = NULL;
			switch( nToolID )
			{
			case IDM_OBJ_ZOOM:
				pType = &CGIZoomTool::GetClassType();
				break;

			case IDM_OBJ_PAN:
				pType = &CGIPanTool::GetClassType();
				break;
		
			case IDM_OBJ_SELECT:
				pType = &CGISelectionTool::GetClassType();
				break;

			case IDM_OBJ_RECT:
				pType = &CGIRectElementTool::GetClassType();
				break;

			case IDM_OBJ_LINE:
				pType = &CGILineElementTool::GetClassType();
				break;
			}

			if( pType )
				pEditWnd->SelectTool( *pType );
		}
	}
}

void CBldMainFrm::OnBarUI( CCmdUI* pCmdUI )
{
	pCmdUI->Enable();
	/*if( IDM_OBJECT != g_sobj.nTool )
		pCmdUI->SetCheck( g_sobj.nTool == (INT)pCmdUI->m_nID );
	else
		pCmdUI->SetCheck( g_sobj.nObjToolID == (INT)pCmdUI->m_nID );*/
}

#define IDC_LAYER_BAR 1001
BOOL CBldMainFrm::CreateLayerBar()
{
	VERIFY( m_pLayerBar = new CObjLayerBar );
	BOOL bResult = m_pLayerBar ->Create( _T("Layers"), CRect(600, 100, 600 + 180, 100 + 200), this );
	return bResult;
}