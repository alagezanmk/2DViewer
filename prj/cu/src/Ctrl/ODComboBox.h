#ifndef ___COMBO_BOX__H___
#define ___COMBO_BOX__H___

// Owner draw Combobox 
class CU_EXT_CLASS CODComboBox : public CComboBox
{
public:
	struct SItem;

public:
	enum NOTIFY_CODE
	{
		NMODCB_GET_BORDER_COLOR	= 1000,
	};

	// ODCBBS_ - Owner draw Combobox Border style
	enum BORDER_STYLE
	{
		BS_WINDOWS	= 0,
		BS_USER		= 1,
		BS_NONE		= 2,
		BS_ALL		= 3,
	};

	struct NMBorderColor : public NMHDR
	{
		COLORREF crfOTop;
		COLORREF crfOLeft;
		COLORREF crfiTop;
		COLORREF crfiLeft;
		
		COLORREF crfOBottom;
		COLORREF crfORight;
		COLORREF crfiBottom;
		COLORREF crfiRight;
	};

public:
	CODComboBox();
	virtual ~CODComboBox();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODComboBox)
	virtual void MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItem );
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItem );
	virtual int CompareItem( LPCOMPAREITEMSTRUCT lpCompareItem );
	virtual void DeleteItem( LPDELETEITEMSTRUCT lpDeleteItem );
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CODComboBox)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void CustomPaint( CDC& rDC );
	void OnDestroyCtrl();
	virtual INT InsertItem( INT nIndex, LPCTSTR lpszString );
	SItem* GetItem( INT nIndex ) const;

public:
	void SetControlHeight( INT nHeight );
	INT GetControlHeight();

	void GetDropDownBtnRect( CRect& rrct );

	void SetBorderStyle( INT nBorderStyle );
	INT GetBorderStyle();

	void SetTextOffset( INT x, INT y );
	void SetTextOffset( POINT point );
	POINT GetTextOffset();

	INT AddString( LPCTSTR lpszString );
	INT InsertString( INT nIndex, LPCTSTR lpszString );

	INT GetLBText( INT nIndex, LPTSTR lpszText ) const;
	void GetLBText( INT nIndex, CString& rString ) const;
	INT GetLBTextLen( INT nIndex ) const;

	DWORD GetItemData( INT nIndex ) const;
	INT SetItemData( INT nIndex, DWORD dwItemData );

	DWORD GetItemData( INT nIndex, INT nID ) const;
	INT SetItemData( INT nIndex, INT nID, DWORD dwItemData );

protected:
	INT			m_nStyle;
	INT			m_nCtrlHeight;

public:
	POINT		m_ptTextOffset;
};

inline void CODComboBox::SetTextOffset( INT x, INT y ) {
	m_ptTextOffset.x = x; m_ptTextOffset.y = y; }

inline void CODComboBox::SetTextOffset( POINT point ) {
	m_ptTextOffset = point; }

inline POINT CODComboBox::GetTextOffset() {
	return m_ptTextOffset; }

inline void CODComboBox::SetBorderStyle( INT nStyle ) {
	m_nStyle = (m_nStyle & ~BS_ALL) | nStyle; }

inline INT CODComboBox::GetBorderStyle() {
	return m_nStyle & BS_ALL; }

inline void CODComboBox::SetControlHeight( INT nHeight ) {
	m_nCtrlHeight = nHeight; }

inline INT CODComboBox::GetControlHeight() {
	return m_nCtrlHeight; }

#endif //!___COMBO_BOX__H___
