#include "stdafx.h"
#include <g\tools\uiTool.h>
#include <g\wnd\gViewWnd.h>
#include <cu\Key.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPL_BASE_GTPYECLASS_DYNCREATE( CGIUITool, _T("UITool") )
CGIUITool::CGIUITool()
{
	m_pgInstanceType = &GetClassType();
	m_pwndView = NULL;
	m_pView = NULL;

	m_nUIState = NONE_UI_STATE;
	m_nUIMode = NONE_UI_MODE;
	m_nDefUIMode = NONE_UI_MODE;
	m_nHitTest = HT_NOTHING;
}

CGIUITool::~CGIUITool()
{}

BOOL CGIUITool::Draw( CDC& rDC, RECT& rRect ) {
	return FALSE; }

INT CGIUITool::GetDrawType() const {
	return LOWER_DRAW_TYPE; }

void CGIUITool::SetViewWindow( CGIViewWnd* pWin ) {
	m_pwndView = pWin; }

void CGIUITool::SetView( CGIView* pView ) {
	m_pView = pView; }

void CGIUITool::SetUIState( INT nState ) {
	m_nUIState = nState; }

void CGIUITool::SetUIMode( INT nMode ) {
	m_nUIMode = nMode; }

void CGIUITool::SetDefaultUIMode( INT nMode ) {
	m_nDefUIMode = nMode; }

BOOL CGIUITool::IsSubUIModeActive( INT nMode, INT nState ) const 
{
	INT nCount = m_aarSubMode.GetSize();
	const SSubUIMode* psSubUIMode = m_aarSubMode.GetData();
	for( INT i = 0; i < nCount; i++ )
		if( nMode == psSubUIMode[i].nMode 
			&& nState == psSubUIMode[i].nState )
			return TRUE;

	return FALSE;
}

void CGIUITool::RemoveAllSubUIMode() {
	m_aarSubMode.RemoveAll(); }

void CGIUITool::PopSubUIMode( INT& rnMode, INT& rnState )
{
	INT nCount = m_aarSubMode.GetSize();
	if( nCount )
		m_aarSubMode.SetSize( nCount - 1 );

	GetLastSubUIMode( rnMode, rnState );
}

void CGIUITool::GetLastSubUIMode( INT& rnMode, INT& rnState ) const 
{
	INT nCount = m_aarSubMode.GetSize();
	if( nCount )
	{
		const SSubUIMode& rsSubUIMode = m_aarSubMode.GetAt( nCount - 1 );
		rnMode = rsSubUIMode.nMode;
		rnState = rsSubUIMode.nState;
		return;
	}

	rnMode = m_nDefUIMode;
	rnState = NONE_UI_STATE;
}

BOOL CGIUITool::PushSubUIMode( INT nMode, INT nState )
{
	if( IsSubUIModeActive( nMode, nState ) )
		return FALSE;

	SSubUIMode sSubMode = { nMode, nState };
	m_aarSubMode.Add( sSubMode );
	return TRUE;
}

BOOL CGIUITool::RemoveSubUIMode( INT nMode, INT nState )
{
	INT nCount = m_aarSubMode.GetSize();
	SSubUIMode* psSubUIMode = m_aarSubMode.GetData();
	for( INT i = 0; i < nCount; i++ )
		if( nMode == psSubUIMode[i].nMode 
			&& nState == psSubUIMode[i].nState )
		{
			m_aarSubMode.RemoveAt( i );
			return TRUE;
		}

	return FALSE;
}

/// Find the use of the bStart 
BOOL CGIUITool::IsUIModeKey( INT nMode, UINT nChar ) {
	return FALSE; }

UINT CGIUITool::GetUIModeKey( INT nMode ) {
	return 0; }

BOOL CGIUITool::IsUIStateKey( INT nMode, INT nState, UINT nChar ) {
	return FALSE; }

UINT CGIUITool::GetUIStateKey( INT nMode, INT nState ) {
	return 0; }

BOOL CGIUITool::AddListenKeyState( UINT nChar, BOOL bKeyDown /*= FALSE*/ ) {
	return AddKeyEventListener( nChar, bKeyDown, CGIUITool::KeyListenerCB, this ); }

BOOL CGIUITool::AddListenUIModeKey( INT nMode, BOOL bKeyDown /*= FALSE*/ ) 
{
	UINT nKey = GetUIModeKey( nMode );
	return AddListenKeyState( nKey, bKeyDown );
}

BOOL CGIUITool::AddListenUIStateKey( INT nMode, INT nState, BOOL bKeyDown /*= FALSE*/ )
{
	UINT nKey = GetUIStateKey( nMode, nState );
	return AddListenKeyState( nKey, bKeyDown );
}

BOOL CGIUITool::RemoveListenKeyState( UINT nChar, BOOL bKeyDown /*= FALSE*/ ) {
	return RemoveKeyEventListener( nChar, bKeyDown, CGIUITool::KeyListenerCB, this ); }

BOOL CGIUITool::RemoveListenUIModeKey( INT nMode, BOOL bKeyDown /*= FALSE*/ ) 
{
	UINT nKey = GetUIModeKey( nMode );
	return RemoveListenKeyState( nKey, bKeyDown );
}

BOOL CGIUITool::RemoveListenUIStateKey( INT nMode, INT nState, BOOL bKeyDown /*= FALSE*/ )
{
	UINT nKey = GetUIStateKey( nMode, nState );
	return RemoveListenKeyState( nKey, bKeyDown );
}

INT CGIUITool::KeyListenerCB( UINT nChar, BOOL bKeyDown, void* pUserData )
{
	CGIUITool* pThis = (CGIUITool*)pUserData;
	return pThis->KeyListener( nChar, bKeyDown, pUserData );
}

INT CGIUITool::KeyListener( UINT nChar, BOOL bKeyDown, void* pUserData )
{
	if( bKeyDown )
		return On_KeyDown( nChar, 0, 0 );

	return On_KeyUp( nChar, 0, 0 );
}
