#ifndef ___PROP_EDIT__PH___
#define ___PROP_EDIT__PH___

#include "PropItemCtrl.h"

/// OPIDT_ - Obj Prop Item Data Type - nDataType
#define OPIDT_TEXT					1
#define OPIDT_HEX					2
#define OPIDT_SHORT					3
#define OPIDT_USHORT				4
#define OPIDT_INT					5
#define OPIDT_UINT					6
#define OPIDT_FLOAT					7
#define OPIDT_DOUBLE				8

class CU_EXT_CLASS CPropEdit : public CEdit
{
public:
	CPropEdit();
	virtual ~CPropEdit();
	DECLARE_MESSAGE_MAP()

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropEdit)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPropEdit)
	afx_msg void OnKillFocus( CWnd* pNewWnd );
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnChar( UINT nChar, UINT nRepCnt, UINT nFlags );
	//}}AFX_MSG

public:
	CString& GetText();
	void  UpdateText();
	INT GetInt();
	FLOAT GetFloat();
	DOUBLE GetDouble();

	void SetDataType( INT nType );
	void SetMinLength( INT nLen );
	void SetMaxLength( INT nLen );

protected:
	CString		m_cszText;
	INT			m_nMinLen;
	INT			m_nMaxLen;
	INT			m_nDataType;
};

inline void CPropEdit::SetDataType( INT nType ) {
	m_nDataType = nType; }

inline void CPropEdit::SetMinLength( INT nLen ) {
	if( nLen > 0 )
		m_nMinLen = nLen; }

inline void CPropEdit::SetMaxLength( INT nLen ) {
	if( nLen > 0 )
		m_nMaxLen = nLen; }

inline CString& CPropEdit::GetText() {
	return m_cszText; }

inline void CPropEdit::UpdateText() {
	ASSERT( IsWindow( m_hWnd ) ); 
	GetWindowText( m_cszText ); }

//{{AFX_INSERT_LOCATION}}
#endif //!___PROP_EDIT__PH___
