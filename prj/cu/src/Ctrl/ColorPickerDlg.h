#ifndef ___COLOR_PCIKER_DLG__PH___
#define ___COLOR_PCIKER_DLG__PH___

class CU_EXT_CLASS CColorPickerDlg : public CDialog
{
public:
	CColorPickerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CColorPickerDlg();

	enum EColorMode
	{
		enNone,
		enHue,
		enSaturation,
		enBrightness,
		enBlue,
		enGreen,
		enRed,
	};

	void SetColor( COLORREF crf );
	COLORREF GetColor();
	COLORREF GetCurrentColor();
	COLORREF GetPreviousColor();

	virtual void DrawStyle( CDC* pDC, const CRect& rct, const CRect& rctCur, const CRect& rctPrev );

	VOID CalcXYZ();
	VOID CalcColor();
	VOID SetColor( INT nRed, INT nGreen, INT nBlue );
	VOID UpdateEdit();
	VOID ExchangeColor( INT nNewMode );

	VOID HuetoRGB( INT x, INT y, INT nHue, PINT pnR, PINT pnG, PINT pnB );
	VOID SaturationtoRGB( INT x, INT y, INT nSaturation, PINT pnR, PINT pnG, PINT pnB );
	VOID BrightnesstoRGB( INT x, INT y, INT nBrightness, PINT pnR, PINT pnG, PINT pnB );

	VOID SetColorMode( EColorMode enMode );
	VOID DrawPointer( CDC* pDC );
	BOOL FillColorPanel();
	BOOL FillRGBColorPanel();
	BOOL FillHueColorPanel();
	BOOL FillSaturationColorPanel();
	BOOL FillBrightnessColorPanel();

	BOOL FillColorBar();
	BOOL FillRGBColorBar();
	BOOL FillHueColorBar();
	BOOL FillSaturationColorBar();
	BOOL FillBrightnessColorBar();

	//{{AFX_DATA(CColorPickerDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CColorPickerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CColorPickerDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRedRdo();
	afx_msg void OnGreenRdo();
	afx_msg void OnBlueRdo();
	afx_msg void OnHueRdo();
	afx_msg void OnBrightnessRdo();
	afx_msg void OnSaturationRdo();
	afx_msg void OnChangeEditBlue();
	afx_msg void OnChangeEditGreen();
	afx_msg void OnChangeEditRed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	COLORREF	m_crfCur;
	COLORREF	m_crfPrev;

private:
	INT			m_nRed;
	INT			m_nGreen;
	INT			m_nBlue;
	INT			m_nHue;
	INT			m_nSaturation;
	INT			m_nBrightness;
	INT			m_x, m_y, m_z;

	BOOL		m_bColorPanelModified;
	BOOL		m_bColorBarModified;

	PBYTE		m_pbyColorPanel;
	PBYTE		m_pbyColorBar;

	INT			m_nDrag;
	EColorMode	m_enInternalUpdate;
	EColorMode	m_enColorMode;
};	

//{{AFX_INSERT_LOCATION}}
#endif //!___COLOR_PCIKER_DLG__PH___
