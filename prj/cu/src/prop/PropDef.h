#ifndef ___PROP_DEF__PH___
#define ___PROP_DEF__PH___

struct SPropDataInfo
{};

struct SPropDataLen : public SPropDataInfo
{	
	SPropDataLen( 
		INT					nDataMinLen = 0,
		INT					nDataMaxLen = 0,

		INT					nDataMin = 0,
		FLOAT				fDataMin = 0.0f,
							
		INT					nDataMax = 0,
		FLOAT				fDataMax = 0.0f
	);
	
	INT					nDataMinLen;
	INT					nDataMaxLen;

	INT					nDataMin;
	FLOAT				fDataMin;
						
	INT					nDataMax;
	FLOAT				fDataMax;
};

class CProp;
struct CU_EXT_CLASS SProp
{
public:
	void Set( INT nID, PTCHAR ptszLabel, INT nType, INT nFlag, INT nCtrlType, 
			  INT nCtrlFlag = 0, INT nDataType = 0, INT nDataFlag = 0, 
			  DWORD dwItemData = 0, SPropDataInfo* psDataInfo = NULL );

public:
	INT					nID;
	PTCHAR				ptszLabel;

	INT					nType;
	INT					nFlag;

	INT					nCtrlType;
	INT					nCtrlFlag;
							
	INT					nDataType;
	INT					nDataFlag;
	DWORD				dwItemData;
	SPropDataInfo*		psDataInfo;
};

/// OPST_ Obj Prop Struct Type - nType
#define OPST_TAB					0
#define OPST_GROUP					1
#define OPST_ITEM					2

/// OPSF_ Obj Prop Struct Flag - nFlag
#define OPSF_USER_ITEM				0x00000001
#define OPSF_DISABLE				0x00000002
#define OPSF_FOLD					0x00000004
#define OPSF_LABEL_ID				0x00000008
#define OPSF_LABEL_IDLOCAL			0x00000010

// OPCT_ Obj Prop Crtl Type	- nCtlrType
#define	OPCT_EDIT					1
#define	OPCT_BTN					2
#define	OPCT_COMBO					4
#define	OPCT_USER					0x100
#define	OPCT_STATIC					0x200

/// Derived data type
#define	OPIDT_D_FIRST				0x10000
#define	OPIDT_D_FILENAME			0x10000
#define	OPIDT_D_COLORREF			0x20000
#define	OPIDT_D_LAST				0xFF000

// OPCT_ Obj Prop Crtl Flag	- nCtrlFlag
#define	OPCF_USER_FROM_LABEL		1
#define	OPCF_USER_FROM_LEFT			2

/// For Obj Prop Item Data Type - nDataType see PropEdit.h

/// OPIDF_ - Obj Prop Item Data Flag - nDataFlag
#define OPIDF_MIN					1
#define OPIDF_MAX					2
#define OPIDF_LEN					4
#define OPIDF_DATAPTR				8
#define OPIDF_CTRLPTR				16

struct SPropItem
{
	SPropItem();
	virtual ~SPropItem();

	SPropItem*			pParent;
	SPropItem*			pPrev;
	SPropItem*			pNext;

	INT					nFlag;
	INT					nChildCount;
	INT					nCy;
	SPropItem*			psGroup;
	SProp*				psProp;

	PVOID				pData;
	PVOID				pCtrlData;

	BOOL				bText;
	CString*			pcszText;
};

/// OPIS_ Obj Prop Item Flag - nFlag
#define OPIF_USER_ITEM				1
#define OPIF_DISABLE				2
#define OPIF_FOLD					4
#define OPIF_HIDDEN					8

///////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (CProp::*PS_PPROP)(void);

struct PS_PROPMAP_ENTRY
{
	UINT nMsg;		 // message no
	UINT nCode;      // control code or WM_NOTIFY code
	UINT nID;        // control ID (or 0 for windows messages)
	UINT nLastID;    // used for entries specifying a range of control id's
	UINT nSig;       // signature type (action) or pointer to message #
	PS_PPROP pfn;    // routine to call (or special value)
};

struct PS_PROPMAP
{
	const PS_PROPMAP* (*pfnGetBaseMap)();
	const PS_PROPMAP_ENTRY* lpEntries;
};

#define DECLARE_PB_PROP_MAP() \
private: \
	static const PS_PROPMAP_ENTRY _propEntries[]; \
protected: \
	static const PS_PROPMAP propMap; \
	static const PS_PROPMAP* _GetBasePropMap(); \
	virtual const PS_PROPMAP* GetPropMap() const; \

#define BEGIN_PB_PROP_MAP(theClass, baseClass) \
	const PS_PROPMAP* theClass::_GetBasePropMap() \
		{ return &baseClass::propMap; } \
	const PS_PROPMAP* theClass::GetPropMap() const \
		{ return &theClass::propMap; } \
	const PS_PROPMAP theClass::propMap = \
	{ &theClass::_GetBasePropMap, &theClass::_propEntries[0] }; \
	const PS_PROPMAP_ENTRY theClass::_propEntries[] = \
	{ \

#define END_PB_PROP_MAP() \
		{0, 0, 0, 0, AfsSig_end, (PS_PPROP)0 } \
	}; \

///////////////////////////////////////////////////////////////////////////////////////////////////
#define IDOPST_PROPERTY			100
#define IDOPST_ALPHABETIC		101

/// Tab Entries
#define	OPST_PROPERTY		{ IDOPST_PROPERTY,   NULL, OPST_TAB }
#define	OPST_ALPHABETIC		{ IDOPST_ALPHABETIC, NULL, OPST_TAB }

#define IDOPSG_GENERAL			200
#define IDOPSG_MORE				201
#define IDOPSG_FILL_STYLE		202
#define IDOPSG_STYLE_STYLE		203

/// Group Entries
#define	OPSG_GENERAL		{ IDOPSG_GENERAL,		_T("General"), OPST_GROUP }
#define	OPSG_MORE			{ IDOPSG_MORE,			NULL, OPST_GROUP }
#define	OPSG_FILL_STYLE		{ IDOPSG_FILL_STYLE,	NULL, OPST_GROUP }
#define	OPSG_STROKE_STYLE	{ IDOPSG_STROKE_STYLE,	NULL, OPST_GROUP }

#define IDOPSI_NAME				300

#define IDOPSI_FILL_STYLE		301
#define IDOPSI_FILL_OPACITY		302

#define IDOPSI_STYLE_STYLE		303
#define IDOPSI_STYLE_OPACITY	304

#define IDOPSI_X1				305
#define IDOPSI_Y1				306
#define IDOPSI_X2				307
#define IDOPSI_Y2				308

#define IDOPSI_LEFT				309
#define IDOPSI_TOP				310
#define IDOPSI_WIDTH			311
#define IDOPSI_HEIGHT			312

#define IDOPSI_RNDX				313
#define IDOPSI_RNDY				314
#define IDOPSI_CENTERX			315
#define IDOPSI_CENTERY			316
#define IDOPSI_RADIUS			317
#define IDOPSI_RADIUSX			318
#define IDOPSI_RADIUSY			319

/// Item Entries
#define	OPSI_NAME			{ IDOPSI_NAME,   NULL, OPST_ITEM, 0, OPCT_EDIT, 0, OPIDT_TEXT }

#define	OPSI_LEFT			{ IDOPSI_LEFT,	 NULL, OPST_ITEM, 0, OPCT_EDIT, 0, OPIDT_FLOAT }
#define	OPSI_TOP			{ IDOPSI_TOP,	 NULL, OPST_ITEM, 0, OPCT_EDIT, 0, OPIDT_FLOAT }
#define	OPSI_WIDTH			{ IDOPSI_WIDTH,	 NULL, OPST_ITEM, 0, OPCT_EDIT, 0, OPIDT_FLOAT }
#define	OPSI_HEIGHT			{ IDOPSI_HEIGHT, NULL, OPST_ITEM, 0, OPCT_EDIT, 0, OPIDT_FLOAT }

#define	OPSI_X1				{ IDOPSI_X1,	 NULL, OPST_ITEM, 0, OPCT_EDIT, 0, OPIDT_FLOAT }
#define	OPSI_Y1				{ IDOPSI_Y1,	 NULL, OPST_ITEM, 0, OPCT_EDIT, 0, OPIDT_FLOAT }
#define	OPSI_X2				{ IDOPSI_X2,	 NULL, OPST_ITEM, 0, OPCT_EDIT, 0, OPIDT_FLOAT }
#define	OPSI_Y2				{ IDOPSI_Y2,	 NULL, OPST_ITEM, 0, OPCT_EDIT, 0, OPIDT_FLOAT }

#endif //___PROP_DEF__PH___