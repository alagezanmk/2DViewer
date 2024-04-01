#ifndef ___STYLE_WND__PH___
#define ___STYLE_WND__PH___

#define NM_UPDATE_BACK	1000
#define NM_UPDATE_FORE	1001

#define CBS_NONE					0
#define CBS_SHOWACTIVEBOX			1
#define CBS_DEFAULT					2
#define CBS_EXCHANGE				4
#define CBS_SHOWPICKER				8

typedef struct
{
	INT			nCtrlID;
	INT			nType;
	COLORREF	crfColor;
}SAppColor;

#include "Style.h"

class CU_EXT_CLASS CStyleWnd : public CWnd
{
public:
	CStyleWnd();
	virtual ~CStyleWnd();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStyleWnd)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CStyleWnd)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	VOID CalcBoxSize();

public:
	VOID SetID( INT nID );
	BOOL Create( const RECT& rect, CWnd* pParentWnd, INT nID );
	VOID SetMsgHandle( HWND hMsg );
	VOID SetDefaultColor();
	VOID ExchangeColor();
	VOID SetStartPoint( INT x, INT y );

	VOID SetColor( INT nBox, const CStyle& rStyle );
	VOID SetBackColor( const CStyle& rStyle );
	VOID SetForeColor( const CStyle& rStyle );
	VOID SetActiveColor( const CStyle& rStyle );
	
	const CStyle& GetActiveColor();
	const CStyle& GetBackColor();
	const CStyle& GetForeColor();

	VOID SetStyle( UINT unStyle );
	VOID SetBoxSize(INT nBoxSize );
	INT GetActiveBox();

private:
static CPtrArray		m_arpColorWnd;
	void InvalidateAllColorWnd();

public:
static CStyle		ms_styleFore;
static CStyle		ms_styleBack;
static INT			ms_nActiveBox;

protected:
	INT				m_nLeft;
	INT				m_nTop;
	
	RECT			m_rctDefBox;
	RECT			m_rctExgBox;
	CRect			m_rctForeBox;
	CRect			m_rctBackBox;

	INT				m_nBoxSize;
	UINT			m_unStyle;
	BOOL			m_bInternalUpdate;
};

inline const CStyle& CStyleWnd::GetForeColor() { 
	return ms_styleFore; }

inline const CStyle& CStyleWnd::GetBackColor() { 
	return ms_styleBack;}

inline  INT CStyleWnd::GetActiveBox() { 
	return ms_nActiveBox; }

inline const CStyle& CStyleWnd::GetActiveColor() { 
	return ms_nActiveBox ?ms_styleBack :ms_styleFore; }

inline VOID CStyleWnd::SetActiveColor( const CStyle& rStyle ) { 
	SetColor( ms_nActiveBox, rStyle ); }

#endif //!___STYLE_WND__PH___