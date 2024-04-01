#include "stdafx.h"
#include <bld\File\FileExport.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGIFileExport::CGIFileExport( CGINode& rNode )
{
	m_pRootNode = &rNode;
	m_pRootNode->AddRef();
}

CGIFileExport::CGIFileExport( CGINode& rNode, LPCTSTR pctszFileName )
{
	m_pRootNode = &rNode;
	m_pRootNode->AddRef();

	m_cszFileName = pctszFileName;
}

CGIFileExport::~CGIFileExport()
{
	if( m_pRootNode )
		m_pRootNode->Release();
}

BOOL CGIFileExport::Open() 
{
	if( m_cszFileName.IsEmpty() )
		return FALSE;
	
	return Open( m_cszFileName );
}

BOOL CGIFileExport::Open( LPCTSTR pctszFileName ) {
	return FALSE; }

BOOL CGIFileExport::Write() {
	return FALSE; }

BOOL CGIFileExport::Close() {
	return FALSE; }
