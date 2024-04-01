#ifndef ___G_RULER__PH___
#define ___G_RULER__PH___

#include <gl\gCoord.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
/// CRulerUnit is measure holding class used by CRulerWnd in 
/// the division calculation from values
///		Pixels per inch	(dpi)
///		Value per Unit division(vpu)	(1 for Inch, CM, MM, Pixel, Mils)
///										(72 for Points)
///										(vpu = dpi / Page size)
///		Pixel per unit of division(ppu)	(Usually it is same value of dpi)
///										(1 - for Pixel)
///										(ppu = dpi for Points)
///										(ppu = dpi for Percent)
///										(ppu = dpi for inch)
///										(ppu = dpi / 2.54 for CM)
///										(ppu = dpi / (2.54 * 10 for MM)
///										(ppu = dpi / (2.54 * 10 for MM)
///		Min pixel per unit(mpu)			For all unit type it is 31.
///										If pixels per unit division falls below mpu,
///										then ruler will try to find next
///										lesser division of the current.
///										For Ex. In the case Inch, 
///										If scale = 0.25
///										pixels per division = ppu * 0.25 = 18 pixels
///																		 = 4 unit division
///										Since 18 pixels < mpu, find next lesser division
///												...... to do
class CRulerUnit
{
public:
	CRulerUnit();
	virtual ~CRulerUnit();

public:
	virtual CGUnit::UNIT GetUnit() const;
	virtual void Update();

public:
	FLOAT			m_fdpiX;			///< X - Pixels per inch
	FLOAT			m_fvpuX;			///< X - Value per unit
	FLOAT			m_fppuX;			///< X - pixel per unit
	FLOAT			m_fmpuX;			///< X - min pixel per unit

	FLOAT			m_fdpiY;			///< Y - Pixels per inch
	FLOAT			m_fvpuY;			///< Y - Value per unit
	FLOAT			m_fppuY;			///< Y - pixel per unit
	FLOAT			m_fmpuY;			///< Y - min pixel per unit

	INT*			m_arpnDiv[21];
};

inline CGUnit::UNIT CRulerUnit::GetUnit() const { 
	return CGUnit::UNKNOWN_UNIT; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CRulerUnitPixel : public CRulerUnit
{
public:
	CRulerUnitPixel();
	virtual CGUnit::UNIT GetUnit() const;
};

inline CGUnit::UNIT CRulerUnitPixel::GetUnit() const { 
	return CGUnit::PIXEL_UNIT; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CRulerUnitPoints : public CRulerUnit
{
public:
	CRulerUnitPoints();
	virtual CGUnit::UNIT GetUnit() const;
	virtual void Update();
};

inline CGUnit::UNIT CRulerUnitPoints::GetUnit() const { 
	return CGUnit::POINTS_UNIT; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CRulerUnitPercent : public CRulerUnit
{
public:
	CRulerUnitPercent();
	virtual CGUnit::UNIT GetUnit() const;
	virtual void Update();

public:
	FLOAT m_fPageCx;
	FLOAT m_fPageCy;
};

inline CGUnit::UNIT CRulerUnitPercent::GetUnit() const { 
	return CGUnit::PERCENT_UNIT; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CRulerUnitInch : public CRulerUnit
{
public:
	CRulerUnitInch();
	virtual CGUnit::UNIT GetUnit() const;
	virtual void Update();
};

inline CGUnit::UNIT CRulerUnitInch::GetUnit() const { 
	return CGUnit::INCH_UNIT; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CRulerUnitCM : public CRulerUnit
{
public:
	CRulerUnitCM();
	virtual CGUnit::UNIT GetUnit() const;
	virtual void Update();
};

inline CGUnit::UNIT CRulerUnitCM::GetUnit() const { 
	return CGUnit::CM_UNIT; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CRulerUnitMM : public CRulerUnit
{
public:
	CRulerUnitMM();
	virtual CGUnit::UNIT GetUnit() const;
	virtual void Update();
};

inline CGUnit::UNIT CRulerUnitMM::GetUnit() const { 
	return CGUnit::MM_UNIT; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CRulerUnitMils : public CRulerUnit
{
public:
	CRulerUnitMils();
	virtual CGUnit::UNIT GetUnit() const;
	virtual void Update();
};

inline CGUnit::UNIT CRulerUnitMils::GetUnit() const { 
	return CGUnit::MILS_UNIT; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CRulerWnd : public CWnd
{
public:
	enum {
		HT_NOTHING		= 0xFFFFFFFF,
		HT_HORZ_GUIDE	= 0, 
		HT_VERT_GUIDE	= 1,
		HT_BOTH_GUIDE	= 2,

		HT_ZERO_TRACK	= 3,
		HT_RULER		= 4,
	};

protected:
	struct SRulerDiv
	{
		FLOAT			fDiv;			/// Sub division value
		FLOAT			fMult;			/// Sub division multiple
		INT*			parnSubDiv;		/// Sub dividor
		INT				nFirstCs;		/// First Sub division size
	};

public:
	/// RGS_ Ruler Guide Style
	enum {  enRGS_Dot, enRGS_DashDot, enRGS_Line };

	/// RCC_ Ruler Coord Conversion type
	enum {	enRCC_PagePointF		= 1,
			enRCC_PageRectF			= 2,

			enRCC_ViewPointF		= 32,
			enRCC_ViewRectF			= 33,

			enRCC_PageVectPointF	= 64,
			enRCC_PageVectRectF		= 65,

			enRCC_ViewVectPointF	= 128,
			enRCC_ViewVectRectF		= 129 };

public:
	CRulerWnd();

protected:
	virtual ~CRulerWnd();

	//{{AFX_VIRTUAL(CRulerWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CRulerWnd)
	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage );
	afx_msg void OnWindowPosChanged( WINDOWPOS* lpwndpos );
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg LRESULT OnKeyDownMsg( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnKeyUpMsg( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void LoadSetting();
	void SaveSetting();
	virtual void ShowSettingDlg();
	virtual void CalcCoord( GPointF& rpptf, INT nType ) const;
	virtual BOOL GetCursor( UINT nHitTest, UINT& runCursorID, HINSTANCE& rhInst ) const;
	virtual void FormatRulerNo( FLOAT fValue, CString& rcsz );

	UINT HitTest( const CPoint& rpoint, UINT& rnIndex ) const;
	UINT HitTest( const CPoint& rpoint ) const;
	BOOL On_SetCursor( CWnd* pWnd, UINT nHitTest, UINT nMessage );

	virtual BOOL On_MouseMove( UINT nFlags, CPoint point );

	virtual BOOL On_LButtonDown( UINT nFlags, CPoint point );
	virtual BOOL On_LButtonUp( UINT nFlags, CPoint point );
	virtual BOOL On_LButtonDblClk( UINT nFlags, CPoint point );

	virtual BOOL On_KeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual BOOL On_KeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

	void Draw( CDC& rDC, CRect rcPaint );
	void DrawCursor( CPoint point, BOOL bEraseOnly = FALSE );
	void DrawCursor( CDC& rDC, CPoint point, BOOL bEraseOnly = FALSE );
	void EraseCursor();
	void DrawGuides( Graphics& rGdip );
	void DrawRuler();
	void DrawRulerSubDivision( CDC& rDC, FLOAT fOrg, FLOAT fLength, FLOAT fDiv, const INT* parnDiv, INT nHeight, BOOL bHorz = TRUE );
	void DrawRulerDivision( CDC& rDC, FLOAT fZoom, FLOAT fOrg, FLOAT fLength, const SRulerDiv& rsDiv, BOOL bHorz = TRUE );
	void CalcRulerSubDivsion( SRulerDiv& rsDiv, FLOAT fScale, FLOAT fppu, FLOAT fmpu );
	
	void SetRulerUnit( CGUnit::UNIT enUnit );
	void SetGuideStyle( Pen& rPen );
	BOOL AddOptionPage( CPropertySheet* pPropSheet );

	void ResetOrigin();
	void ZeroTrack( CPoint point );
	void GuideTrack( UINT nHitTest, CPoint point, INT nPos = -1 );
	void BothGuideTrack( CPoint point );
	void InvalidateGuideAt( GPointF ptf );

	void SetScale( FLOAT fScaleX, FLOAT fScaleY );

public:
	CWnd*			m_pResizeWnd;
	CWnd*			m_pViewWnd;

public:
	INT				m_nState;			/// Class State
	CRulerUnit*		m_pUnit;			/// Current Ruler unit
	CGUnit::UNIT	m_enUnit;			/// Current Ruler unit ID
	INT				m_nSize;			/// Ruler Size - Vertically as well as Horzontally
	INT				m_nHTMargin;		/// HitTest margin value

	BOOL			m_bVisible;			/// Ruler visibility
	CPoint			m_ptPrevHairLine;	/// Ruler Previous Hair line position
	GPointF			m_ptfDocOrg;		/// Document Top left position (Origin)
	GPointF			m_ptfRulerOrg;		/// Ruler Top left position (Origin)
	CPoint			m_ptOrg;			/// Ruler Top left position (Drawing Origin)

	FLOAT			m_fScaleY;			/// Current x-axis Scale
	FLOAT			m_fScaleX;			/// Current y-axis Scale
	SRulerDiv		m_sxDiv;			/// X-Axis Sub division value
	SRulerDiv		m_syDiv;			/// Y-Axis Sub division value

	BOOL			m_bGuideVisible;	/// Guide visibility
	INT				m_nGuideStyle;		/// Guide Style Dot, DashDot or Line
	BOOL			m_bGuideSnap;		/// Snapped to Guide or not

	CUIntArray		m_arfHorzGuide;		/// Horizontal Guide position values
	CUIntArray		m_arfVertGuide;		/// Vertical Guide position values

	COLORREF		m_crfGuide;			/// Guide color
};

//{{AFX_INSERT_LOCATION}}
#endif //!___G_RULER__PH___
