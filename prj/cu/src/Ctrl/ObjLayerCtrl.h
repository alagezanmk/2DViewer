#ifndef ___OBJ_LAYER_CTRL__PH___
#define ___OBJ_LAYER_CTRL__PH___

#include "ObjLayerListView.h"

class CU_EXT_CLASS CObjLayerCtrl : public CFrameWnd
{
public:
	enum {
		NEW_LAYER		= 0,
		NEW_LAYER_GROUP	= 1,
		DELETE_LAYER	= 2,
	};

public:
	CObjLayerCtrl();
	virtual ~CObjLayerCtrl();

	//{{AFX_VIRTUAL(CObjLayerCtrl)
	protected:
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CObjLayerCtrl)
	afx_msg INT OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, INT cx, INT cy );
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnPaint();
	afx_msg void OnLockBarUI( CCmdUI* pCmdUI );
	afx_msg void OnBottomBarUI( CCmdUI* pCmdUI );
	afx_msg void OnBottomBar( UINT nID );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();

public:
	void Connect( HWND hWnd );
	INT Find( LPLayer pLayer );
	LPLayer GetAt( INT nIndex );
	BOOL Add( LPLayer pLayer, LPCTSTR pctszName );
	BOOL Remove( LPLayer pLayer );
	BOOL RemoveAt( INT nIndex );
	void ResetContent();

	void SetCurSel( LPLayer pLayer );
	void SetCurSel( INT nIndex );
	INT GetCurSel();

protected:
	HWND					m_hMsg;
	CToolBar				m_wndToolBar;
	CToolBar				m_wndBottomBar;
	CObjLayerListView*		m_plstviewLayer;
};

//{{AFX_INSERT_LOCATION}}
#endif // !___OBJ_LAYER_CTRL__H___
