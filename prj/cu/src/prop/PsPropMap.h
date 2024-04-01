#ifndef ___PS_PROP_MAP__PH___
#define ___PS_PROP_MAP__PH___

enum AfsSig
{
	AfsSig_end = 0,     // [marks end of message map]

	AfsSig_bb,      // BOOL (BOOL)
	AfsSig_iwWw,    // int (UINT, CWnd*, UINT)
	AfsSig_iww,     // int (UINT, UINT)
	AfsSig_is,      // int (LPTSTR)
	AfsSig_lwl,     // LRESULT (WPARAM, LPARAM)
	AfsSig_lwwM,    // LRESULT (UINT, UINT, CMenu*)
	AfsSig_vv,      // void (void)

	AfsSig_vw,      // void (UINT)
	AfsSig_vww,     // void (UINT, UINT)
	AfsSig_vvii,    // void (int, int) // wParam is ignored
	AfsSig_vwww,    // void (UINT, UINT, UINT)
	AfsSig_vwii,    // void (UINT, int, int)
	AfsSig_vwl,     // void (UINT, LPARAM)

	AfsSig_vwwx,    // void (UINT, UINT)
	AfsSig_vs,      // void (LPTSTR)
	AfsSig_vOWNER,  // void (int, LPTSTR), force return TRUE
	AfsSig_iis,     // int (int, LPTSTR)
	AfsSig_wv,      // UINT (void)

	AfsSig_bPi_,	// BOOL (SPropItem*)
	AfsSig_bPi_S,	// BOOL (SPropItem*, LPTSTR)
	AfsSig_bPi_SI,	// BOOL (SPropItem*, LPTSTR, INT*)
	AfsSig_bPi_i,	// BOOL (SPropItem*, INT)
	AfsSig_bPi_f,	// BOOL (SPropItem*, FLOAT)
	AfsSig_bPi_d,	// BOOL (SPropItem*, DOUBLE)

	AfsSig_bPi_I,	// INT (SPropItem*, INT* )
	AfsSig_bPi_SL,	// BOOL (SPropItem*, STRUCT*, LRESULT*)

	AfsSig_bPi_Cs,	// BOOL (SPropItem*, CString* )
};

#define PBM_GETTEXT					1
#define PBM_GETLABEL				2
#define PBM_GETDESC					3

#define PBM_UPDATEITEM				4
#define PBM_UPDATEITEM_TEXT			5
#define PBM_UPDATEITEM_CSTR			6
#define PBM_UPDATEITEM_INT			7
#define PBM_UPDATEITEM_FLOAT		8
#define PBM_UPDATEITEM_DOUBLE		9

#define PBM_EDITCHANGE				10

#define PBM_BTNCLICK				11
#define PBM_DDT_BTNCLICK			12
#define PBM_DDT_CHECK				13

#define PBM_COMBO_FILL				14
#define PBM_COMBO_SELCHANGE			15
#define PBM_COMBO_UPDATE			16
#define PBM_COMBO_SETSEL			17
#define PBM_COMBO_CANCEL			18

union PropMapFunctions
{
	PS_PPROP pfn;   // generic member function pointer

	BOOL (CProp::*pfn_b_pSPropItem_pCStr)( SPropItem*, CString* );
	BOOL (CProp::*pfn_b_pSPropItem)( SPropItem* );

	BOOL (CProp::*pfn_b_pSPropItem_pTChar)( SPropItem*, PTCHAR );
	BOOL (CProp::*pfn_b_pSPropItem_pTChar_pInt)( SPropItem*, PTCHAR, INT* );
	BOOL (CProp::*pfn_b_pSPropItem_pInt)( SPropItem*, INT*);
	BOOL (CProp::*pfn_b_pSPropItem_pFlt)( SPropItem*, FLOAT*);
	BOOL (CProp::*pfn_b_pSPropItem_pDbl)( SPropItem*, DOUBLE*);

	BOOL (CProp::*pfn_pSPropItem_pNMMSCmb_pL)( SPropItem*, CMSComboBox::NMSELCHANGE*, LRESULT* );
};

#define ON_PBM_GETTEXT( nID, memberFxn ) \
	{ PBM_GETTEXT, 0, nID, nID, AfsSig_bPi_Cs, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },

#define ON_PBM_RANGE_GETTEXT( nID, nLastID, memberFxn ) \
	{ PBM_GETTEXT, 0, nID, nLastID, AfsSig_bPi_Cs, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },


#define ON_PBM_GETLABEL( nID, memberFxn ) \
	{ PBM_GETLABEL, 0, nID, nID, AfsSig_bPi_Cs, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },

#define ON_PBM_RANGE_GETLABEL( nID, nLastID, memberFxn ) \
	{ PBM_GETLABEL, 0, nID, nLastID, AfsSig_bPi_Cs, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },


#define ON_PBM_GETDESC( nID, memberFxn ) \
	{ PBM_GETDESC, 0, nID, nID, AfsSig_bPi_Cs, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },

#define ON_PBM_RANGE_GETDESC( nID, nLastID, memberFxn ) \
	{ PBM_GETDESC, 0, nID, nLastID, AfsSig_bPi_Cs, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },


#define ON_PBM_UPDATE_ITEM( nID, memberFxn ) \
	{ PBM_UPDATEITEM, 0, nID, nID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },

#define ON_PBM_UPDATE_RANGE_ITEM( nID, nLastID, memberFxn ) \
	{ PBM_UPDATEITEM, 0, nID, nLastID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },


#define ON_PBM_UPDATE_TEXT_ITEM( nID, memberFxn ) \
	{ PBM_UPDATEITEM_TEXT, 0, nID, nID, AfsSig_bPi_S \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*, PTCHAR))&memberFxn },

#define ON_PBM_UPDATE_RANGE_TEXT_ITEM( nID, nLastID, memberFxn ) \
	{ PBM_UPDATEITEM_TEXT, 0, nID, nLastID, AfsSig_bPi_S \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*, PTCHAR))&memberFxn },


#define ON_PBM_UPDATE_INT_ITEM( nID, memberFxn ) \
	{ PBM_UPDATEITEM_INT, 0, nID, nID, AfsSig_bPi_i, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*,INT))&memberFxn },

#define ON_PBM_UPDATE_RANGE_INT_ITEM( nID, nLastID, memberFxn ) \
	{ PBM_UPDATEITEM_INT, 0, nID, nLastID, AfsSig_bPi_i, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*,INT))&memberFxn },


#define ON_PBM_UPDATE_FLOAT_ITEM( nID, memberFxn ) \
	{ PBM_UPDATEITEM_FLOAT, 0, nID, nID, AfsSig_bPi_f, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*,FLOAT))&memberFxn },

#define ON_PBM_UPDATE_RANGE_FLOAT_ITEM( nID, nLastID, memberFxn ) \
	{ PBM_UPDATEITEM_FLOAT, 0, nID, nLastID, AfsSig_bPi_f, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*,FLOAT))&memberFxn },


#define ON_PBM_UPDATE_DOUBLE_ITEM( nID, memberFxn ) \
	{ PBM_UPDATEITEM_DOUBLE, 0, nID, nID, AfsSig_bPi_d, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*,DOUBLE))&memberFxn },

#define ON_PBM_UPDATE_RANGE_DOUBLE_ITEM( nID, nLastID, memberFxn ) \
	{ PBM_UPDATEITEM_DOUBLE, 0, nID, nLastID, AfsSig_bPi_d, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*,DOUBLE))&memberFxn },


#define ON_PBM_EDITCHANGE( nID, memberFxn ) \
	{ PBM_EDITCHANGE, 0, nID, nID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },

#define ON_PBM_RANGE_EDITCHANGE( nID, nLastID, memberFxn ) \
	{ PBM_EDITCHANGE, 0, nID, nLastID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },


#define ON_PBM_BTNCLICK( nID, memberFxn ) \
	{ PBM_BTNCLICK, 0, nID, nID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },

#define ON_PBM_RANGE_BTNCLICK( nID, nLastID, memberFxn ) \
	{ PBM_BTNCLICK, 0, nID, nLastID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },


#define ON_PBM_DDT_BTNCLICK( nID, nType, memberFxn ) \
	{ PBM_DDT_BTNCLICK, nType, nID, nID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },

#define ON_PBM_RANGE_DDT_BTNCLICK( nID, nLastID, nType, memberFxn ) \
	{ PBM_DDT_BTNCLICK, nType, nID, nLastID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },


#define ON_PBM_DDT_CHECK( nID, nType, memberFxn ) \
	{ PBM_DDT_CHECK, nType, nID, nID, AfsSig_bPi_SI, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*, PTCHAR, INT*))&memberFxn },

#define ON_PBM_RANGE_DDT_CHECK( nID, nLastID, nType, memberFxn ) \
	{ PBM_DDT_CHECK, nType, nID, nLastID, AfsSig_bPi_SI, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*, PTCHAR, INT*))&memberFxn },


#define ON_PBM_COMBO_FILL( nID, memberFxn ) \
	{ PBM_COMBO_FILL, 0, nID, nID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },

#define ON_PBM_RANGE_COMBO_FILL( nID, nLastID, memberFxn ) \
	{ PBM_COMBO_FILL, 0, nID, nLastID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },


#define ON_PBM_COMBO_SELCHANGE( nID, memberFxn ) \
	{ PBM_COMBO_SELCHANGE, 0, nID, nID, AfsSig_bPi_SL, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*, NMMSCmb*, LRESULT*))&memberFxn },

#define ON_PBM_RANGE_COMBO_SELCHANGE( nID, memberFxn ) \
	{ PBM_COMBO_SELCHANGE, 0, nID, nID, AfsSig_bPi_SL, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*, NMMSCmb*, LRESULT*))&memberFxn },


#define ON_PBM_COMBO_UPDATE( nID, memberFxn ) \
	{ PBM_COMBO_UPDATE, 0, nID, nID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },

#define ON_PBM_RANGE_COMBO_UPDATE( nID, nLastID, memberFxn ) \
	{ PBM_COMBO_UPDATE, 0, nID, nLastID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },


#define ON_PBM_COMBO_SETSEL( nID, memberFxn ) \
	{ PBM_COMBO_SETSEL, 0, nID, nID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },

#define ON_PBM_RANGE_COMBO_SETSEL( nID, nLastID, memberFxn ) \
	{ PBM_COMBO_SETSEL, 0, nID, nLastID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },


#define ON_PBM_COMBO_CANCEL( nID, memberFxn ) \
	{ PBM_COMBO_CANCEL, 0, nID, nID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },

#define ON_PBM_RANGE_COMBO_CANCEL( nID, nLastID, memberFxn ) \
	{ PBM_COMBO_CANCEL, 0, nID, nLastID, AfsSig_bPi_, \
		(PS_PPROP)(BOOL (CProp::*)(SPropItem*))&memberFxn },


#endif ___PS_PROP_MAP__PH___