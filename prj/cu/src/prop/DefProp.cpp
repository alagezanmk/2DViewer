#include "stdafx.h"
#include <cu\msg.h>
#include "DefProp.h"
#include "PsPropMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BEGIN_PB_PROP_MAP(CDefaultProp,CProp)
	ON_PBM_RANGE_DDT_BTNCLICK( 0, UINT_MAX, OPIDT_D_FILENAME, OnFileNameBtnClick )
	ON_PBM_RANGE_DDT_CHECK( 0, UINT_MAX, OPIDT_D_FILENAME, OnFileNameCheck )
	ON_PBM_RANGE_DDT_BTNCLICK( 0, UINT_MAX, OPIDT_D_COLORREF, OnColorRefBtnClick )
	ON_PBM_RANGE_DDT_CHECK( 0, UINT_MAX, OPIDT_D_COLORREF, OnColorRefCheck )
END_PB_PROP_MAP()

CDefaultProp::CDefaultProp()
{
	m_pProp = NULL;
}

CDefaultProp::~CDefaultProp()
{}

BOOL CDefaultProp::OnFileNameBtnClick( SPropItem* psItem )
{
static INT s_nFilterIndex;
	CString cszFileName;
	GetText( psItem, cszFileName );
	CFileDialog dlg( TRUE, _T("bmp"), (LPCTSTR)cszFileName, 
					 OFN_HIDEREADONLY, (LPCTSTR)psItem->psProp->dwItemData, NULL );

	dlg.m_ofn.nFilterIndex = s_nFilterIndex;

	if( IDOK != dlg.DoModal() )
		return TRUE;

	s_nFilterIndex = dlg.m_ofn.nFilterIndex;
	cszFileName = dlg.GetPathName();
	
	CProp::m_pedtProp->SetWindowText( cszFileName );
	CProp::m_pedtProp->SetModify();
	return SendNotify( CProp::m_pedtProp, NM_UPDATE );
}

BOOL CDefaultProp::OnFileNameCheck( SPropItem* psItem, PTCHAR ptszName, INT* pnType )
{
	if( ptszName && 0 != ptszName[0] && FALSE == PathFileExists( ptszName ) )
	{
		CString cszMsg;
		cszMsg.Format( _T("File '%s' does not exit. Enter valid name"), ptszName );
		AfxMessageBox( cszMsg );

		// Invalid file name don't pass
		return PBR_SETFOCUS;
	}

	*pnType = OPIDT_TEXT;
	return TRUE;
}

COLORREF CDefaultProp::ParseColorRef( SPropItem* psItem, PTCHAR ptszCrf )
{
	return 0;
}

BOOL CDefaultProp::OnColorRefBtnClick( SPropItem* psItem )
{
static INT s_nFilterIndex;
	CString cszText;
	
	COLORREF crf;
	BOOL bDataPtr = 0 != (psItem->psProp->nDataFlag & OPIDF_DATAPTR);
	if( bDataPtr )
		crf = *((COLORREF*)psItem->pData);
	else
	{
		GetText( psItem, cszText );
		crf = ParseColorRef( psItem, (PTCHAR)(LPCTSTR)cszText );
	}

	CColorDialog dlg( crf );
	dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	if( IDOK != dlg.DoModal() )
		return TRUE;

	crf = dlg.m_cc.rgbResult;
	
	CProp::m_pedtProp->SetWindowText( cszText );
	CProp::m_pedtProp->SetModify();
	CWnd* pWnd = GetParent();
	return SendNotify( CProp::m_pedtProp, NM_UPDATE );
}

BOOL CDefaultProp::OnColorRefCheck( SPropItem* psItem, PTCHAR ptszName, INT* pnType )
{
	if( ptszName && 0 != ptszName[0] && FALSE == PathFileExists( ptszName ) )
	{
		CString cszMsg;
		cszMsg.Format( _T("File '%s' does not exit. Enter valid name"), ptszName );
		AfxMessageBox( cszMsg );
		m_pedtProp->SetFocus();

		// Invalid file name don't pass
		return PBR_SETFOCUS;
	}

	*pnType = OPIDT_UINT;
	return TRUE;
}
