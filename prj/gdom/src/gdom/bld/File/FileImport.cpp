#include "stdafx.h"
#include <bld\File\FileImport.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGIFileImport::CGIFileImport() {
	m_pRootNode = NULL; }

CGIFileImport::CGIFileImport( LPCTSTR pctszFileName )
{
	m_pRootNode = NULL;
	m_cszFileName = pctszFileName;
}

CGIFileImport::~CGIFileImport()
{
	if( m_pRootNode )
		m_pRootNode->Release();
}

BOOL CGIFileImport::Open() {
	return FALSE; }

BOOL CGIFileImport::Open( LPCTSTR pctszFileName ) {
	return FALSE; }

BOOL CGIFileImport::Read() {
	return FALSE; }

BOOL CGIFileImport::Close() {
	return FALSE; }
