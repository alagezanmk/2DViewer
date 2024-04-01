#include "stdafx.h"
#include <g\attr\gViewBox.h>
#include <g\type\idom\giElement.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGIViewBox::CGIViewBox( LPCTSTR pctszName )
 : m_aEnable( _T("view-box-enable") ),
   m_aX( _T("view-box-x") ),
   m_aY( _T("view-box-y") ),
   m_aWidth( _T("view-box-width") ),
   m_aHeight( _T("view-box-height") )
{
	m_cszName = pctszName;
	m_fViewWidth = 1.f;
	m_fViewHeight = 1.f;

	m_enAlign = enANone;
	m_enAspectRatioType = enARMeet;
	VERIFY( m_pmtxViewBox = CreateMatrix() );
	SetNodeFlag( DATA_CTM_MODIFIED_NODE_FLAG );
}

CGIViewBox::~CGIViewBox()
{
	if( m_pmtxViewBox )
		DeleteMatrix( m_pmtxViewBox );
}

void CGIViewBox::InitializeAttributes()
{
	ASSERT( m_pElement );
	if( NULL == m_pElement )
		return;

	if( m_bAttrInited )
		return;

	LPCTSTR pctszViewBoxName = GetName();
	m_pElement->AddGroupedAttributes( NULL, pctszViewBoxName, FALSE, 
									  &m_aEnable,
									  &m_aX,
									  &m_aY,
									  &m_aWidth, 
									  &m_aHeight, NULL );

	m_pElement->SetAttrType( CGIAttr::DISPLAY_ATTR_TYPE | CGIAttr::DRAW_BBOX_ATTR_TYPE | CGIAttr::CTM_ATTR_TYPE, 
							 (CGIAttr*)m_aEnable,
							 (CGIAttr*)m_aX,
							 (CGIAttr*)m_aY,
							 (CGIAttr*)m_aWidth,
							 (CGIAttr*)m_aHeight,
							 NULL );
	m_bAttrInited = TRUE;
}

void CGIViewBox::SetViewSize( FLOAT fWidth, FLOAT fHeight )
{
	m_fViewWidth = fWidth;
	m_fViewHeight = fHeight;
}

void CGIViewBox::SetOrigin( FLOAT x, FLOAT y )
{
	m_aX = x;
	m_aY = y;
}

void CGIViewBox::SetOrigin( const GPointF& rgptf )
{
	m_aX = rgptf.x;
	m_aY = rgptf.y;
}

void CGIViewBox::SetSize( FLOAT fWidth, FLOAT fHeight )
{
	m_aWidth = fWidth;
	m_aHeight = fHeight;
}

void CGIViewBox::Set( FLOAT x, FLOAT y, FLOAT fWidth, FLOAT fHeight )
{
	m_aX = x;
	m_aY = y;
	m_aWidth = fWidth;
	m_aHeight = fHeight;
}

void CGIViewBox::Set( const GPointF& rgptf, FLOAT fWidth, FLOAT fHeight )
{
	m_aX = rgptf.x;
	m_aY = rgptf.y;
	m_aWidth = fWidth;
	m_aHeight = fHeight;
}

void CGIViewBox::GetOrigin( FLOAT& rx, FLOAT& ry ) const
{
	rx = m_aX;
	ry = m_aY;
}

void CGIViewBox::GetOrigin( GPointF& rgptf ) const 
{
	rgptf.x = m_aX;
	rgptf.y = m_aY;
}

void CGIViewBox::GetSize( FLOAT& rfWidth, FLOAT& rfHeight ) const
{
	rfWidth  = m_aWidth;
	rfHeight = m_aHeight;
}

void CGIViewBox::Get( FLOAT& rx, FLOAT& ry, FLOAT& rfWidth, FLOAT& rfHeight ) const
{
	rx = m_aX;
	ry = m_aY;

	rfWidth  = m_aWidth;
	rfHeight = m_aHeight;
}

void CGIViewBox::Get( GPointF& rgptf, FLOAT& rfWidth, FLOAT& rfHeight ) const
{
	rgptf.x = m_aX;
	rgptf.y = m_aY;

	rfWidth  = m_aWidth;
	rfHeight = m_aHeight;
}

void CGIViewBox::SetAlign( EAlign enType ) {
	m_enAlign = enType; }

void CGIViewBox::SetAspectRatioType( EAspectRatioType enType ) {
	m_enAspectRatioType = enType; }

void CGIViewBox::UpdateCTM( Matrix& rMtx ) {
	GetCTM( *m_pmtxViewBox ); }

void CGIViewBox::Update()
{
	//if( IsFlagSet( DATA_CTM_MODIFIED_FLAG ) )
	{
		m_pmtxViewBox->Reset();
		UpdateCTM( *m_pmtxViewBox );
		SetNodeFlag( DATA_CTM_MODIFIED_NODE_FLAG, FALSE );
	}
}

BOOL CGIViewBox::GetCTM( Matrix& rMtx ) const 
{
	CGPointF gptfTranslate( 0, 0 );
	FLOAT fScale = 1;
	FLOAT fAspectRatio = 1;

	if( m_aEnable )
	{
		gptfTranslate.x = -m_aX;
		gptfTranslate.y = -m_aY;

		FLOAT fWidth, fHeight;
		switch( m_enAlign )
		{
		case enANone: 
			{
				FLOAT fScaleX = m_fViewWidth / m_aWidth;
				FLOAT fScaleY = m_fViewHeight / m_aHeight;
				fScale = fScaleX;
				fAspectRatio = fScaleY / fScaleX;
			}
			
			break;

		case enAxMinYMin:
			if( CGIViewBox::enARMeet == m_enAspectRatioType )
			{
				if( m_fViewHeight > m_fViewWidth )
					fScale = m_fViewWidth / m_aWidth;
				else
					fScale = m_fViewHeight / m_aHeight;
			}
			else
			{
				if( m_fViewHeight > m_fViewWidth )
					fScale = m_fViewHeight / m_aHeight;
				else
					fScale = m_fViewWidth / m_aWidth; 
			}

			break;

		case enAxMidYMin:
			if( CGIViewBox::enARMeet == m_enAspectRatioType )
			{
				if( m_fViewHeight > m_fViewWidth )
					fScale = m_fViewWidth / m_aWidth;
				else
				{
					fScale = m_fViewHeight / m_aHeight; 

					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += (fWidth - m_aWidth) / 2.f;
				}
			}
			else
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewHeight / m_aHeight; 

					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += (fWidth - m_aWidth) / 2.f;
				}
				else
					fScale = m_fViewWidth / m_aWidth;
			}

			break;

		case enAxMaxYMin:
			if( CGIViewBox::enARMeet == m_enAspectRatioType )
			{
				if( m_fViewHeight > m_fViewWidth )
					fScale = m_fViewWidth / m_aWidth;
				else
				{
					fScale = m_fViewHeight / m_aHeight; 

					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += fWidth - m_aWidth;
				}
			}
			else
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewHeight / m_aHeight; 

					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += fWidth - m_aWidth;
				}
				else
					fScale = m_fViewWidth / m_aWidth;
			}	

			break;

		case enAxMinYMid:
			if( CGIViewBox::enARMeet == m_enAspectRatioType )
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewWidth / m_aWidth; 

					float fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += (fHeight - m_aHeight) / 2.f;
				}
				else
					fScale = m_fViewHeight / m_aHeight; 
			}
			else
			{
				if( m_fViewHeight > m_fViewWidth )
					fScale = m_fViewHeight / m_aHeight; 
				else
				{
					fScale = m_fViewWidth / m_aWidth; 

					fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += (fHeight - m_aHeight) / 2.f;
				}
			}

			break;

		case enAxMidYMid:
			if( CGIViewBox::enARMeet == m_enAspectRatioType )
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewWidth / m_aWidth; 

					fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += (fHeight - m_aHeight) / 2.f;
				}
				else
				{
					fScale = m_fViewHeight / m_aHeight; 

					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += (fWidth - m_aWidth) / 2.f;
				}
			}
			else
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewHeight / m_aHeight; 

					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += (fWidth - m_aWidth) / 2.f;
				}
				else
				{
					fScale = m_fViewWidth / m_aWidth;

					fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += (fHeight - m_aHeight) / 2.f;
				}
			}

			break;

		case enAxMaxYMid:
			if( CGIViewBox::enARMeet == m_enAspectRatioType )
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewWidth / m_aWidth; 

					fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += (fHeight - m_aHeight) / 2.f;
				}
				else
				{
					fScale = m_fViewHeight / m_aHeight; 

					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += fWidth - m_aWidth;
				}
			}
			else
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewHeight / m_aHeight; 

					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += fWidth - m_aWidth;
				}
				else
				{
					fScale = m_fViewWidth / m_aWidth;

					fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += (fHeight - m_aHeight) / 2.f;
				}
			}

			break;

		case enAxMinYMax:
			if( CGIViewBox::enARMeet == m_enAspectRatioType )
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewWidth / m_aWidth; 

					fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += fHeight - m_aHeight;
				}
				else
					fScale = m_fViewHeight / m_aHeight; 
			}
			else
			{
				if( m_fViewHeight > m_fViewWidth )
					fScale = m_fViewHeight / m_aHeight; 
				else
				{
					fScale = m_fViewWidth / m_aWidth; 

					fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += fHeight - m_aHeight;
				}
			}

			break;

		case enAxMidYMax:
			if( CGIViewBox::enARMeet == m_enAspectRatioType )
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewWidth / m_aWidth;

					fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += fHeight - m_aHeight;
				}
				else
				{
					fScale = m_fViewHeight / m_aHeight; 

					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += (fWidth - m_aWidth) / 2.f;
				}
			}
			else
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewHeight / m_aHeight; 
					
					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += (fWidth - m_aWidth) / 2.f;
				}
				else
				{
					fScale = m_fViewWidth / m_aWidth;

					fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += fHeight - m_aHeight;
				}
			}

			break;

		case enAxMaxYMax:
			if( CGIViewBox::enARMeet == m_enAspectRatioType )
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewWidth / m_aWidth;

					fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += fHeight - m_aHeight;
				}
				else
				{
					fScale = m_fViewHeight / m_aHeight; 

					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += fWidth - m_aWidth;
				}
			}
			else
			{
				if( m_fViewHeight > m_fViewWidth )
				{
					fScale = m_fViewHeight / m_aHeight; 
					
					fWidth = m_fViewWidth / fScale;
					gptfTranslate.x += fWidth - m_aWidth;
				}
				else
				{
					fScale = m_fViewWidth / m_aWidth;

					fHeight = m_fViewHeight / fScale;
					gptfTranslate.y += fHeight - m_aHeight;
				}
			}

			break;
		}
	}
	else
	{
		gptfTranslate.x = m_aX;
		gptfTranslate.y = m_aY;
	}

	rMtx.Scale( fScale, fScale * fAspectRatio );
	rMtx.Translate( gptfTranslate.x, gptfTranslate.y );
	return FALSE == rMtx.IsIdentity();
}