#ifndef ___PROP_BOX_BAR__PH___
#define ___PROP_BOX_BAR__PH___

#include "PropBox.h"
#include <ctrl\SizeCBar.h>

class CU_EXT_CLASS CPropBoxBar : public CSizingControlBar
{
public:
	CPropBoxBar();
	virtual ~CPropBoxBar();

	//{{AFX_VIRTUAL(CPropBox)
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPropBox)
	afx_msg INT OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, INT cx, INT cy );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual CPropBox* CreatePropBox() const;

public:
	CPropBox*	m_pPropBox;
};

inline CPropBox* CPropBoxBar::CreatePropBox() const {
	return new CPropBox; }

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif//___PROP_BOX_BAR__PH___
