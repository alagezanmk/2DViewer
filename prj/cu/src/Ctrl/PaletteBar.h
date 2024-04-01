#ifndef ___PALETTE_BAR__PH___
#define ___PALETTE_BAR__PH___

#include "ToolFrmWnd.h"
#include "PaletteCtrl.h"
#include "StyleWnd.h"

class CU_EXT_CLASS CPaletteBar : public CToolFrmWnd
{
public:
	CPaletteBar();
	virtual ~CPaletteBar();

	//{{AFX_VIRTUAL(CPaletteBar)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPaletteBar)
	afx_msg LRESULT OnFloatStatusMsg( WPARAM wParam, LPARAM lParam );
	afx_msg void OnPaint();
	afx_msg INT OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, INT cx, INT cy );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();

public:
	BOOL Create( LPCTSTR lpszWindowName, const RECT& rect, CWnd* pParentWnd );
	CPaletteCtrl& GetPalettetrl();
	
protected:
	CStyleWnd			m_wndStyle;
	CPaletteCtrl*		m_pPalCtrl;
	CSliderCtrl			m_sldrOpacity;
	CComboBox			m_cmbStyle;
};

#endif //!___PALETTE_BAR__PH___