#ifndef ___BLD_MAIN_FRM__PH___
#define ___BLD_MAIN_FRM__PH___

#include <cu\MainFrmi.h>
#include <prop\PropBoxBar.h>
#include <ctrl\ToolBox.h>
#include <ctrl\PaletteBar.h>
#include <ctrl\ObjLayerBar.h>

class CToolBoxStyleWnd : public CStyleWnd
{
public:
	CToolBoxStyleWnd()
	{
		m_unStyle &= ~CBS_SHOWACTIVEBOX;
		m_unStyle |= CBS_SHOWPICKER;
	}
};

class GDOM_EXT_CLASS CBldMainFrm : public CIMainFrm
{
	DECLARE_DYNCREATE(CBldMainFrm)
public:
	CBldMainFrm();
	virtual ~CBldMainFrm();

	//{{AFX_VIRTUAL(CBldMainFrm)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CBldMainFrm)
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnBar( UINT nID );
	afx_msg void OnBarUI( CCmdUI* pCmdUI );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CObjLayerBar* GetLayerBar();
	const CObjLayerBar* GetLayerBar() const;

	CPropBox* GetPropBox();
	const CPropBox* GetPropBox() const;

protected:
	BOOL CreatePropBox();
	BOOL CreatToolBox();
	BOOL CreateLayerBar();

protected:
	CPropBoxBar			m_PropBoxBar;
	CToolBox*			m_pToolBox;
	CToolBoxStyleWnd	m_wndStyle;
	CObjLayerBar*		m_pLayerBar;
};

inline CPropBox* CBldMainFrm::GetPropBox() {
	return m_PropBoxBar.m_pPropBox; }

inline const CPropBox* CBldMainFrm::GetPropBox() const {
	return m_PropBoxBar.m_pPropBox; }

inline CObjLayerBar* CBldMainFrm::GetLayerBar() {
	return m_pLayerBar; }

inline const CObjLayerBar* CBldMainFrm::GetLayerBar() const {
	return m_pLayerBar; }

//{{AFX_INSERT_LOCATION}}
#endif //!___BLD_MAIN_FRM__PH___
