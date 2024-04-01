#ifndef ___OBJ_LAYER_BAR__PH___
#define ___OBJ_LAYER_BAR__PH___

#include "sizecbar.h"
#include "ObjLayerCtrl.h"
#include "ToolFrmWnd.h"

class CU_EXT_CLASS CObjLayerBar : public CToolFrmWnd
{
public:
	CObjLayerBar();
	virtual ~CObjLayerBar();

	//{{AFX_VIRTUAL(CObjLayerBar)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CObjLayerBar)
	afx_msg LRESULT OnFloatStatusMsg( WPARAM wParam, LPARAM lParam );
	afx_msg INT OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, INT cx, INT cy );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();

public:
	BOOL Create( LPCTSTR lpszWindowName, const RECT& rect, CWnd* pParentWnd );

	CObjLayerCtrl& GetLayerCtrl();
	const CObjLayerCtrl& GetLayerCtrl() const;
	
protected:
	CObjLayerCtrl*		m_pLayerCtrl;
};

inline CObjLayerCtrl& CObjLayerBar::GetLayerCtrl() {
	return *m_pLayerCtrl; }

inline const CObjLayerCtrl& CObjLayerBar::GetLayerCtrl() const {
	return *m_pLayerCtrl; }

//{{AFX_INSERT_LOCATION}}
#endif // !___OBJ_LAYER_BAR__PH___
