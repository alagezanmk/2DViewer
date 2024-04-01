#include "stdafx.h"
#include <g\type\gViewPort.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGViewPort::CGViewPort()
{
	m_cbWindowSize.cx = 1;
	m_cbWindowSize.cy = 1;

	m_cbViewSize.cx = 1;
	m_cbViewSize.cy = 1;

	m_cbDisplaySize.cx = 1;
	m_cbDisplaySize.cy = 1;

	m_fScale = 1.f;
	m_fAspectRatio = 1.f;
	m_ptDisplayOrigin.x = 0;
	m_ptDisplayOrigin.y = 0;
}

CGViewPort::~CGViewPort()
{}

void CGViewPort::SetWindowSize( INT nWidth, INT nHeight )
{
	m_cbWindowSize.cx = nWidth;
	m_cbWindowSize.cy = nHeight;
}

void CGViewPort::GetWindowSize( INT& rnWidth, INT& rnHeight )
{
	rnWidth = m_cbWindowSize.cx;
	rnHeight = m_cbWindowSize.cy;
}

void CGViewPort::SetWindowSize( const SIZE& rSize ) {
	m_cbWindowSize = rSize; }

const SIZE& CGViewPort::GetWindowSize() {
	return m_cbWindowSize; }
	
void CGViewPort::SetViewSize( INT nWidth, INT nHeight )
{
	m_cbViewSize.cx = nWidth;
	m_cbViewSize.cy = nHeight;
}

void CGViewPort::GetViewSize( INT& rnWidth, INT& rnHeight )
{
	rnWidth = m_cbViewSize.cx;
	rnHeight = m_cbViewSize.cy;
}

void CGViewPort::SetViewSize( const SIZE& rSize ) {
	m_cbViewSize = rSize; }

const SIZE& CGViewPort::GetViewSize() {
	return m_cbViewSize; }

void CGViewPort::SetScale( FLOAT fScale ) {
	m_fScale = fScale; }

FLOAT CGViewPort::GetScale() {
	return m_fScale; }

void CGViewPort::SetScale( FLOAT fxScale, FLOAT fyScale )  {
	m_fScale = fxScale;	 }

void CGViewPort::GetScale( FLOAT& rfxScale, FLOAT& rfyScale ) {
	rfxScale = m_fScale;
	rfyScale = m_fScale; }

void CGViewPort::SetAspectRatio( FLOAT fRatio ) {
	ASSERT( FALSE );
	m_fAspectRatio = fRatio; }

FLOAT CGViewPort::GetAspectRatio() {
	ASSERT( FALSE );
	return m_fAspectRatio; }

void CGViewPort::CalculateView()
{
	m_cbDisplaySize.cx = (INT)((FLOAT)m_cbViewSize.cx * m_fScale);
	m_cbDisplaySize.cy = (INT)((FLOAT)m_cbViewSize.cy * m_fScale);

	if( m_cbWindowSize.cx > m_cbDisplaySize.cx )
		m_ptDisplayOrigin.x = (m_cbWindowSize.cx - m_cbDisplaySize.cx) / 2;
//	else
//		m_ptDisplayOrigin.x = 0;

	if( m_cbWindowSize.cy > m_cbDisplaySize.cy )
		m_ptDisplayOrigin.y = (m_cbWindowSize.cy - m_cbDisplaySize.cy) / 2;
//	else
//		m_ptDisplayOrigin.y = 0;
}

void CGViewPort::GetDisplaySize( INT& rnWidth, INT& rnHeight )
{
	rnWidth = m_cbDisplaySize.cx;
	rnHeight = m_cbDisplaySize.cy;
}

void CGViewPort::GetDisplaySize( FLOAT& rfWidth, FLOAT& rfHeight )
{
	rfWidth = (FLOAT)m_cbDisplaySize.cx;
	rfHeight = (FLOAT)m_cbDisplaySize.cy;
}

const SIZE& CGViewPort::GetDisplaySize() {
	return m_cbDisplaySize; }

void CGViewPort::GetDisplayOrigin( FLOAT& rfx, FLOAT& rfy )
{
	rfx = (FLOAT)m_ptDisplayOrigin.x;
	rfy = (FLOAT)m_ptDisplayOrigin.y;
}

void CGViewPort::GetDisplayOrigin( INT& rnx, INT& rny )
{
	rnx = m_ptDisplayOrigin.x;
	rny = m_ptDisplayOrigin.y;
}

const POINT& CGViewPort::GetDisplayOrigin() {
	return m_ptDisplayOrigin; }

void CGViewPort::SetDisplayOrigin( FLOAT x, FLOAT y )
{
	m_ptDisplayOrigin.x = (INT)x;
	m_ptDisplayOrigin.y = (INT)y;
}

void CGViewPort::SetDisplayOrigin( INT x, INT y )
{
	m_ptDisplayOrigin.x = x;
	m_ptDisplayOrigin.y = y;
}

void CGViewPort::SetDisplayOrigin( const POINT& rgpt ) 
{
	m_ptDisplayOrigin.x = rgpt.x; 
	m_ptDisplayOrigin.y = rgpt.y;
}

