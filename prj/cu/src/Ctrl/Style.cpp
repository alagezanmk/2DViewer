#include "stdafx.h"
#include "ObjStyle.h"
#include "IccColorStyle.h"
//#include "GradStyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// CStyle class
CStyle::CStyle()
{
	m_wType = enObjStyleColor;
	m_fOpacity = 1.0f;
	SetARGB( Color::White );
}

CStyle::~CStyle()
{
	Delete();
}

void CStyle::Delete()
{
	if( m_pData )
	{
		if( m_wType > enObjStyleIccColor )
			delete m_pData;
			
		m_pData = NULL;
	}

	m_wType = enObjStyleNone;
}

void CStyle::CopyStyle( const CStyle* pStyle )
{
	Copy( pStyle );
}

void CStyle::Copy( const CStyle* pStyle )
{
	ASSERT( pStyle );

	if( m_wType > enObjStyleIccColor )
		Delete();

	m_wType = pStyle->m_wType;
	m_fOpacity = pStyle->m_fOpacity;

	if( pStyle->m_wType <= enObjStyleIccColor )
		m_nIndex = pStyle->m_nIndex;
	else
		m_pData->Copy( *pStyle->m_pData );
}

void CStyle::Get( CStyle* pStyle ) {
	pStyle->Copy( this ); }

void CStyle::GetText( CString& cszText, BOOL bOpacity /*= TRUE*/ )
{
	if( enObjStyleNotSet == m_wType )
	{
		cszText = _T("[NotSet]");
		return;
	}

	if( IsNull() )
	{
		cszText = _T("[None]");
		return;
	}

	CStyleCreator* pCreator = CStyle::GetStyleCreator( m_wType );
	if( NULL == pCreator )
	{
		ASSERT( NULL );
		return;
	}

	pCreator->GetStyleText( *this, cszText );
	if( bOpacity )
	{
		CString cszOpacity;
		cszOpacity.Format( _T(":%d"), (INT)(m_fOpacity * 255.0f) );
		cszText += cszOpacity;
	}
}

void CStyle::SetByText( WORD wType, LPCTSTR ptszText, FLOAT fOpacity /*= -2.0f*/ )
{
	if( m_wType > enObjStyleIccColor )
		Delete();

	CStyleCreator* pCreator = CStyle::GetStyleCreator( wType );
	if( NULL == pCreator )
	{
		ASSERT( NULL );
		return;
	}

	pCreator->SetStyleByText( *this, ptszText );
	m_wType = wType;
	if( m_wType >= enObjStyleColor && m_wType <= enObjStyleIccColor )
	{
		if( -2.0f == fOpacity )
			m_fOpacity = pCreator->GetAlpha( *this );
		else if( fOpacity >= 0.0f && fOpacity <= 1.0f )
			m_fOpacity = fOpacity;
	}
}

void CStyle::SetColor( ARGB argb, FLOAT fOpacity /*= -2.0f*/ )
{
	if( m_wType > enObjStyleIccColor )
		Delete();

	m_wType = enObjStyleColor;
	SetARGB( argb );

	if( -2.0f == fOpacity )
		m_fOpacity = (FLOAT)ARGB_ALPHA( m_argb ) / 255.0f;
	else if( fOpacity >= 0.0f && fOpacity <= 1.0f )
		m_fOpacity = fOpacity;
}

void CStyle::SetIccColor( LPCTSTR ptszIccName, FLOAT fOpacity /*= -2.0f*/ )
{
	if( m_wType > enObjStyleIccColor )
		Delete();

	INT nIndex = GetIccColorIndex( ptszIccName );
	if( nIndex >= 0 )
	{
		m_wType = enObjStyleIccColor;
		m_nIndex = nIndex;

		if( -2.0f == fOpacity )
			m_fOpacity = (FLOAT)ARGB_ALPHA( m_argb ) / 255.0f;
		else if( fOpacity >= 0.0f && fOpacity <= 1.0f )
			m_fOpacity = fOpacity;
		return;
	}

	ASSERT( FALSE );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// CStyleCreator
CMapWordToPtr gs_mapCreator;
BOOL CStyle::AddStyleCreator( WORD m_wType, CStyleCreator* pCreator )
{
	if( GetStyleCreator( m_wType ) )
		return FALSE;

	gs_mapCreator.SetAt( m_wType, (VOID*&)pCreator );
	return TRUE;
}

CStyleCreator* CStyle::GetStyleCreator( WORD m_wType )
{
	CStyleCreator* pCreator;
	if( gs_mapCreator.Lookup( m_wType, (VOID*&)pCreator ) )
		return pCreator;	

	return NULL;
}

BOOL CStyle::RemoveStyleCreator( WORD m_wType )
{
	if( gs_mapCreator.RemoveKey( m_wType ) )
		return TRUE;

	ASSERT( FALSE );
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// CFillStyle class
CFillStyle::CFillStyle()
{
	SetARGB( MAKE_RGB(0, 0, 255) );
	m_nFillRule = 0;
}

CFillStyle::~CFillStyle()
{}

void CFillStyle::Copy( const CFillStyle* pStyle )
{
	ASSERT( pStyle );
	CStyle::Copy( pStyle );
	m_nFillRule = pStyle->m_nFillRule;
}

void CFillStyle::Get( CFillStyle* pStyle ) const
{
	pStyle->Copy( this );
	pStyle->m_nFillRule = m_nFillRule;
}

void CFillStyle::SetBrushStyle( Brush& rBrush ) const
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
// CStrokeStyle class
CStrokeStyle::CStrokeStyle()
{
	SetARGB( MAKE_RGB(0, 0, 0) );
	m_nLineCapStyle = 0;
	m_nJoinStyle = 0;
}

CStrokeStyle::~CStrokeStyle()
{}

void CStrokeStyle::Copy( const CStrokeStyle* pStyle )
{
	CStyle::Copy( pStyle );

	m_nDashStyle = pStyle->m_nDashStyle;
	m_nLineCapStyle = pStyle->m_nLineCapStyle;
	m_nJoinStyle = pStyle->m_nJoinStyle;
	m_fThickness = pStyle->m_fThickness;
}

void CStrokeStyle::Get( CStrokeStyle* pStyle ) const
{
	pStyle->Copy( this );

	pStyle->m_nDashStyle = m_nDashStyle;
	pStyle->m_nLineCapStyle = m_nLineCapStyle;
	pStyle->m_nJoinStyle = m_nJoinStyle;
	pStyle->m_fThickness = m_fThickness;
}

void CStrokeStyle::SetPenStyle( Pen& rPen ) const
{
	if( enObjStrokeNone != m_nDashStyle )
		rPen.SetDashStyle( (DashStyle)m_nDashStyle ); 

	rPen.SetAlignment( PenAlignmentInset );
	rPen.SetLineCap( (LineCap)m_nLineCapStyle, 
					 (LineCap)m_nLineCapStyle,
					 (DashCap)m_nLineCapStyle );
}

///////////////////////////////////////////////////////////////////////////////////////////////
// CStyleBrush
CStyleBrush::CStyleBrush()
{
	m_pBrush = NULL;
	m_pData = NULL;
}

CStyleBrush::~CStyleBrush()
{
	Delete();
}

CStyleBrush::CStyleBrush( const CStyle& rStyle, FLOAT fOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	m_pBrush = NULL;
	m_pData = NULL;
	if( NULL == Create( rStyle, fOpacity, rrctF ) )
	{
		//CSimpleException e;
		//THROW( &e );
	}
}

CStyleBrush::CStyleBrush( const CFillStyle& rStyle, FLOAT fOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	m_pBrush = NULL;
	m_pData = NULL;
	if( NULL == Create( rStyle, fOpacity, rrctF ) )
	{
		//CException e;
		//THROW( &e );
	}
}

Brush* CStyleBrush::Create( const CStyle& rStyle, FLOAT fOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	ASSERT( NULL == m_pBrush );

	if( rStyle.IsNull() )
		return NULL;

	CStyleCreator* pCreator = CStyle::GetStyleCreator( rStyle.m_wType );
	if( NULL == pCreator )
	{
		// No Creator handler for this type
		ASSERT( NULL );
		return NULL;
	}

	if( pCreator->CreateBrush( *this, rStyle, fOpacity, rrctF ) )
		return m_pBrush;

	ASSERT( NULL );
	return NULL;
}

Brush* CStyleBrush::Create( const CFillStyle& rStyle, FLOAT fOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	ASSERT( NULL == m_pBrush );
	if( rStyle.IsNull() )
		return NULL;

	if( Create( (const CStyle&)rStyle, fOpacity, rrctF ) )
	{
		rStyle.SetBrushStyle( *m_pBrush );
		return m_pBrush;
	}

	return NULL;
}

void CStyleBrush::Delete()
{
	if( m_pBrush )
	{
		DeleteGdipBrush( m_pBrush );
		m_pBrush = NULL;

		if( m_pData )
		{
			delete m_pData;
			m_pData = NULL;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// CStylePen class
CStylePen::CStylePen()
{
	m_pPen = NULL;
	m_pData = NULL;
}

CStylePen::CStylePen( const CStyle& rStyle, FLOAT fOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	m_pPen = NULL;
	m_pData = NULL;
	if( NULL == Create( rStyle, fOpacity, rrctF ) )
	{
		//CException e;
		//THROW( &e );
	}
}

CStylePen::CStylePen( const CStrokeStyle& rStyle, FLOAT fOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	m_pPen = NULL;
	m_pData = NULL;
	if( NULL == Create( rStyle, fOpacity, rrctF ) )
	{
		//CException e;
		//THROW( &e );
	}
}

CStylePen::~CStylePen()
{
	Delete();
}

Pen* CStylePen::Create( const CStyle& rStyle, FLOAT fOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	ASSERT( NULL == m_pPen );

	if( rStyle.IsNull() )
		return NULL;

	CStyleCreator* pCreator = CStyle::GetStyleCreator( rStyle.m_wType );
	if( NULL == pCreator )
	{
		// No creator for the type
		ASSERT( NULL );
		return NULL;
	}

	if( pCreator->CreatePen( *this, rStyle, fOpacity, rrctF ) )
		return m_pPen;

	ASSERT( NULL );
	return NULL;
}

Pen* CStylePen::Create( const CStrokeStyle& rStyle, FLOAT fOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	ASSERT( NULL == m_pPen );

	if( rStyle.IsNull() || 0.0f == rStyle.m_fThickness )
		return NULL;

	if( Create( (const CStyle&)rStyle, fOpacity, rrctF ) )
	{
		rStyle.SetPenStyle( *m_pPen );
		return m_pPen;
	}

	ASSERT( NULL );
	return NULL;
}

void CStylePen::Delete()
{
	if( m_pPen )
	{
		DeleteGdipPen( m_pPen );
		m_pPen = NULL;

		if( m_pData )
		{
			delete m_pData;
			m_pData = NULL;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
class CColorStyleCreator : public CStyleCreator
{
public:
	CColorStyleCreator();

	virtual Pen* CreatePen( CStylePen& rPen, const CStyle& rStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF );
	virtual Brush* CreateBrush( CStyleBrush& rBrush, const CStyle& rStyle, FLOAT fOpacity = 1.0f, const RectF& rrctF = nullRectF );

	virtual FLOAT GetAlpha( const CStyle& rStyle );

	virtual void GetStyleText( const CStyle& rStyle, CString& rcszText );
	virtual BOOL SetStyleByText( CStyle& rStyle, LPCTSTR ptszText );
};

static CColorStyleCreator oneColorStyleCreator;
void AddColorStyleCreator()
{
	CStyle::AddStyleCreator( enObjStyleColor, &oneColorStyleCreator );
}

CColorStyleCreator::CColorStyleCreator()
{
	AddColorStyleCreator();
}

Pen* CColorStyleCreator::CreatePen( CStylePen& rPen, const CStyle& rStyle, FLOAT fOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	if( enObjStyleColor == rStyle.m_wType )
	{
		VERIFY( rPen.m_pPen = CreateGdipPen( OBJ_COLOR(rStyle.GetARGB(), rStyle.m_fOpacity * fOpacity) ) );
		if( NULL == rPen.m_pPen )
			return NULL;

		return rPen.m_pPen;
	}

	// This is not creator of the m_wType
	ASSERT( NULL );
	return NULL;
}

Brush* CColorStyleCreator::CreateBrush( CStyleBrush& rBrush, const CStyle& rStyle, FLOAT fOpacity /*= 1.0f*/, const RectF& rrctF /*= nullRectF*/ )
{
	if( enObjStyleColor == rStyle.m_wType )
	{
		VERIFY( rBrush.m_pBrush = CreateGdipSolidBrush( OBJ_COLOR(rStyle.GetARGB(), rStyle.m_fOpacity * fOpacity) ) );
		if( NULL == rBrush.m_pBrush )
			return NULL;

		return rBrush.m_pBrush;
	}

	// This is not a creator for this m_wType 
	ASSERT( NULL );
	return NULL;
}

FLOAT CColorStyleCreator::GetAlpha( const CStyle& rStyle ) {
	return ARGB_ALPHA(rStyle.m_argb) / 255.0f; }

void CColorStyleCreator::GetStyleText( const CStyle& rStyle, CString& rcszText )
{
	if( enObjStyleColor == rStyle.m_wType )
	{
		rcszText.Format( _T("RGB(%d,%d,%d)"), 
							 ARGB_RED( rStyle.GetARGB() ),
							 ARGB_GREEN( rStyle.GetARGB() ),
							 ARGB_BLUE( rStyle.GetARGB() ) );
		return;
	}

	// This is not a creator for this m_wType 
	ASSERT( FALSE );
}

BOOL CColorStyleCreator::SetStyleByText( CStyle& rStyle, LPCTSTR ptszText )
{
	ASSERT( FALSE );
	return FALSE;
}