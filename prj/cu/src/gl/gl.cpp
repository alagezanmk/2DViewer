#include "stdafx.h"
#include <gl\gl.h>
#include <gl\GdipGC.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
CGCCreator*	CGL::m_pGCCreator;
void CGL::Constructor()
{
	m_pGC = NULL;
	m_ptfCurPos.x = 0;
	m_ptfCurPos.y = 0;
}

CGL::CGL( CGCCreator* pCreator, HGD hGD )
{
	Constructor();
	ASSERT( hGD );
	ASSERT( pCreator );

	m_pGC = pCreator->Create( hGD );
	if( NULL == m_pGC )
		throw _T("CGC creation failed");
}

CGL::CGL( CGCCreator* pCreator, HWIN hWin, INT nGCType /*= enGCTypeClient*/ )
{
	Constructor();
	ASSERT( hWin );
	ASSERT( pCreator );

	m_pGC = pCreator->Create( hWin, nGCType );
	if( NULL == m_pGC )
		throw _T("CGC creation failed");
}

CGL::CGL( HGD hGD )
{
	Constructor();
	ASSERT( hGD );
	ASSERT( m_pGCCreator );
	if( NULL == m_pGCCreator )
	{
		throw _T("Creator was not set");
		return;
	}

	m_pGC = m_pGCCreator->Create( hGD );
	if( NULL == m_pGC )
		throw _T("CGC creation failed");

}

CGL::CGL( HWIN hWin, INT nGCType /*= enGCTypeClient*/ )
{
	Constructor();
	ASSERT( hWin );
	ASSERT( m_pGCCreator );
	if( NULL == m_pGCCreator )
	{
		throw _T("Creator was not set");
		return;
	}

	m_pGC = m_pGCCreator->Create( hWin, nGCType );
	if( NULL == m_pGC )
		throw _T("CGC creation failed");
}

CGL::CGL( CGC* pGC )
{
	Constructor();
	ASSERT( pGC );
	m_pGC = pGC;
}

CGL::~CGL()
{
	if( m_pGC )
	{
		delete m_pGC;
		m_pGC = NULL;
	}
}

BOOL CGL::SetDefaultGC( CGCCreator* pCreator )
{
	if( NULL == pCreator )
	{
		ASSERT( pCreator );
		return FALSE;
	}

	m_pGCCreator = pCreator;
	return TRUE;
}

void CGL::DeleteDefaultGC()
{
	if( m_pGCCreator )
	{
		delete m_pGCCreator;
		m_pGCCreator = NULL;
	}
}

void CGL::SetTransform( const Matrix& rMtx ) 
{
	CGdipGC* pGdipGC = (CGdipGC*)m_pGC;
	pGdipGC->m_pG->SetTransform( &rMtx );
}

BOOL CGL::MoveTo( INT x, INT y ) {
	m_pGC->StartFigure();
	return MoveTo( (FLOAT)x, (FLOAT)y ); }

BOOL CGL::MoveTo( FLOAT x, FLOAT y )
{
	m_ptfCurPos.x = x;
	m_ptfCurPos.y = y;
	return TRUE;
}

BOOL CGL::LineTo( INT x, INT y ) {
	return LineTo( (FLOAT)x, (FLOAT)y ); }

BOOL CGL::LineTo( FLOAT x, FLOAT y )
{
	if( NULL == m_pGC )
	{
		ASSERT( m_pGC );
		return FALSE;
	}

	m_arfPoint[0] = m_ptfCurPos;
	m_arfPoint[1].x = x;
	m_arfPoint[1].y = y;
	m_ptfCurPos = m_arfPoint[1];
	return m_pGC->DrawPolygon( m_arfPoint, 2 );
}

BOOL CGL::MoveToRel( INT dx, INT dy ) {
	return MoveToRel( (FLOAT)dx, (FLOAT)dy ); }

BOOL CGL::MoveToRel( FLOAT dx, FLOAT dy )
{
	m_ptfCurPos.x += dx;
	m_ptfCurPos.y += dy;
	return TRUE;
}

BOOL CGL::LineToRel( INT dx, INT dy ) {
	return LineToRel( (FLOAT)dx, (FLOAT)dy ); }

BOOL CGL::LineToRel( FLOAT dx, FLOAT dy )
{
	if( NULL == m_pGC )
	{
		ASSERT( m_pGC );
		return FALSE;
	}

	m_arfPoint[0] = m_ptfCurPos;
	m_arfPoint[1].x = m_ptfCurPos.x + dx;
	m_arfPoint[1].y = m_ptfCurPos.x + dy;
	m_ptfCurPos = m_arfPoint[1];
	return m_pGC->DrawPolygon( m_arfPoint, 2 );
}

BOOL CGL::Line( INT x1, INT y1, INT x2, INT y2 ) {
	return Line( (FLOAT)x1, (FLOAT)y1, (FLOAT)x2, (FLOAT)y2 ); }

BOOL CGL::Line( FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2 )
{
	if( NULL == m_pGC )
	{
		ASSERT( m_pGC );
		return FALSE;
	}

	m_pGC->StartFigure();
	m_arfPoint[0].x = x1;
	m_arfPoint[0].y = y1;
	m_arfPoint[1].x = x2;
	m_arfPoint[1].y = y2;
	m_ptfCurPos = m_arfPoint[1];
	return m_pGC->DrawPolygon( m_arfPoint, 2 );
}

BOOL CGL::Rectangle( INT x1, INT y1, INT x2, INT y2 ) {
	return Rectangle( (FLOAT)x1, (FLOAT)y1, (FLOAT)x2, (FLOAT)y2 ); }

BOOL CGL::Rectangle( FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2 )
{
	if( NULL == m_pGC )
	{
		ASSERT( m_pGC );
		return FALSE;
	}

	m_pGC->StartFigure();

	m_arfPoint[0].x = x1;
	m_arfPoint[0].y = y1;

	m_arfPoint[1].x = x2;
	m_arfPoint[1].y = y1;

	m_arfPoint[2].x = x2;
	m_arfPoint[2].y = y2;

	m_arfPoint[3].x = x1;
	m_arfPoint[3].y = y2;

	if( FALSE == m_pGC->DrawPolygon( m_arfPoint, 4 ) )
		return TRUE;

	return m_pGC->CloseFigure();
}

BOOL CGL::Circle( INT cx, INT cy, INT nRadius ) {
	return Circle( (FLOAT)cx, (FLOAT)cy, (FLOAT)nRadius ); }

BOOL CGL::Circle( FLOAT cx, FLOAT cy, FLOAT nRadius )
{
	ASSERT( FALSE );
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CGC::CGC()
{
	m_nGCType = CGL::enGCTypeUnknown;
}

CGC::CGC( HGD hGD )
{}

CGC::CGC( HWIN hWin, INT nGCType /*= CGL::enGCTypeClient*/ )
{}

CGC::~CGC()
{}

BOOL CGC::DrawPolygon( GPointF* pPoint, INT nCount ) {
	return FALSE; }

BOOL CGC::FillPolygon( GPointF* pPoint, INT nCount ) {
	return FALSE; }

BOOL CGC::DrawBezier( GPointF* pPoint, INT nCount ) {
	return FALSE; }

BOOL CGC::FillBezier( GPointF* pPoint, INT nCount ) {
	return FALSE; }

BOOL CGC::StartFigure() {
	return TRUE; }

BOOL CGC::CloseFigure() {
	return TRUE; }

////////////////////////////////////////////////////////////////////////////////////////////////////
CGC* CGCCreator::Create( HGD hGD ) {
	return NULL; }

CGC* CGCCreator::Create( HWIN hWin, INT nGCType /*= CGL::enGCTypeClient*/ ) {
	return NULL; }
