#include "stdafx.h"
#include <g\tools\eUITool.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPL_GTPYECLASS_DYNCREATE( CGIElementUITool, CGIUITool, _T("ElementUITool") )
CGIElementUITool::CGIElementUITool()
{
	m_pgInstanceType = &GetClassType();

	m_piElement = NULL;
}

CGIElementUITool::~CGIElementUITool()
{}

BOOL CGIElementUITool::OnKeyDown( const CKbdEvent& rEvent )
{
	if( m_piElement )
	{
		CGKeyboardEvent rgEvent;
		m_piElement->InitKeyboardEvent( rgEvent, rEvent, m_pwndView );
		return m_piElement->KeyDown( rgEvent );
	}

	return FALSE;
}

BOOL CGIElementUITool::OnKeyUp( const CKbdEvent& rEvent )
{
	if( m_piElement )
	{
		CGKeyboardEvent rgEvent;
		m_piElement->InitKeyboardEvent( rgEvent, rEvent, m_pwndView );
		return m_piElement->KeyUp( rgEvent );
	}

	return FALSE;
}

BOOL CGIElementUITool::GetElementScreenCTM( Matrix& rMtx ) const
{
	if( m_pView )
		m_pView->GetScreenCTM( rMtx );

	if( m_piElement )
		m_piElement->GetScreenCTM( rMtx );

	return FALSE == rMtx.IsIdentity();
}

INT CGIElementUITool::GetHitTest() const {
	return HT_NOTHING; }

void CGIElementUITool::SetHitTest( INT nHitTest ) 
{}

BOOL CGIElementUITool::GetSelection() const {
	return FALSE; }

void CGIElementUITool::SetSelection( BOOL bSet /*= TRUE*/ ) 
{}

void CGIElementUITool::InvalidateRect( BOOL bHandle /*= FALSE*/ ) const 
{}
