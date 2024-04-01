#include "stdafx.h"
#include <cu\msg.h>
#include "PropEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CPropEdit, CEdit)
	//{{AFX_MSG_MAP(CPropEdit)
	ON_WM_KILLFOCUS()
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CPropEdit::CPropEdit()
{
	m_nDataType = OPIDT_TEXT;
	m_nMinLen = 0;
	m_nMaxLen = -1;
}

CPropEdit::~CPropEdit()
{
}

INT CPropEdit::GetInt()
{
#ifdef _UNICODE 
	return _wtoi( m_cszText );
#else
	return atoi( m_cszText );
#endif
}

FLOAT CPropEdit::GetFloat()
{
#ifdef _UNICODE 
	return (FLOAT)_wtof( m_cszText );
#else
	return (FLOAT)atof( m_cszText );
#endif
}

DOUBLE CPropEdit::GetDouble()
{
#ifdef _UNICODE 
	return _wtof( m_cszText );
#else
	return atof( m_cszText );
#endif
}

void CPropEdit::OnKillFocus( CWnd* pNewWnd )
{
	SendNotify( this, NM_KILLFOCUS );
	CEdit::OnKillFocus( pNewWnd );
}

UINT CPropEdit::OnGetDlgCode()
{
	UINT unReturn = CEdit::OnGetDlgCode();
	unReturn |= DLGC_WANTALLKEYS;
	return unReturn;
}

void CPropEdit::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	switch( nChar )
	{
	case VK_RETURN:
		if( SendNotify( this, NM_RETURN ) )
			return;
		break;

	case VK_ESCAPE:
		if( SendNotify( this, NM_CANCEL ) )
			return;
		break;
	}

	CEdit::OnKeyDown( nChar, nRepCnt, nFlags );
}

void CPropEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	UpdateText();
	INT nTextLen = m_cszText.GetLength();
	INT nStartChar, nEndChar;
	GetSel( nStartChar, nEndChar );
	INT nSelLen = nEndChar - nStartChar;

	if( VK_BACK == nChar )
		goto LBOk;

	if( m_nMaxLen > 0 )
		if( nTextLen - nSelLen >= m_nMaxLen )
			return;

	switch( m_nDataType )
	{
	case OPIDT_INT:
		if( _T('-') == nChar || _T('+') == nChar )
		{
			if( nStartChar > 0 )
				return;
		}
		else if( FALSE == (nChar >= _T('0') && nChar <= _T('9')) )
			return;
		break;

	case OPIDT_HEX:
		if( FALSE == ((nChar >= _T('0') && nChar <= _T('9')) ||
			(nChar >= _T('a') && nChar <= _T('f')) || 
			(nChar >= _T('A') && nChar <= _T('F')) ) )
			return;
		break;
	}

LBOk:;
	CEdit::OnChar( nChar, nRepCnt, nFlags );
}
