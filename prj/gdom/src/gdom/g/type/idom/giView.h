#ifndef ___G_VIEW__PH___
#define ___G_VIEW__PH___

#include "giViewPort.h"
#include <g\type\gViewPort.h>
#include <g\attr\gViewBox.h>

class GDOM_EXT_CLASS CGIView : public CGIGroup
{
	DECL_GTPYECLASS_DYNCREATE(CGIView)
public:
	static LPCTSTR ELEMENT_TAGNAME;

	enum MTX_TYPE
	{
		MTX_RENDER	= 1,
		MTX_VIEWBOX	= 2,
	};

public:
	CGIView();

protected:
	overrided ~CGIView();
	overrided void InitializeAttributes();

public:
	void SetSize( FLOAT fWidth, FLOAT fHeight );
	void GetSize( FLOAT& rfWidth, FLOAT& rfHeight ) const;

	virtual void SetDocSize( FLOAT fWidth, FLOAT fHeight );
	virtual void GetDocSize( FLOAT& rfWidth, FLOAT& rfHeight ) const;

	virtual void GetScrollableSize( FLOAT& rfWidth, FLOAT& rfHeight ) const;
	virtual void GetScrollable( BOOL& rbHorzBar, BOOL& rbVertBar );
	virtual BOOL IsScrollable( INT nSBar );
	virtual void Scroll( FLOAT fx, FLOAT fy, BOOL bScaled = TRUE );

	virtual void SetOrigin( FLOAT x, FLOAT y, BOOL bScaled = TRUE );
	virtual void GetOrigin( FLOAT& rx, FLOAT& ry, BOOL bScaled = TRUE ) const;
	virtual const GPointF& GetOrigin() const;

	virtual void GetRenderSize( FLOAT& rfWidth, FLOAT& rfHeight ) const;
	virtual void GetRenderCTM( Matrix& rmtx );

	FLOAT GetScale() const;
	FLOAT GetScaleX() const;
	FLOAT GetScaleY() const;
	void GetScale( FLOAT& rfX, FLOAT& rfY ) const;
	void GetScale( CGPointF& rgptf ) const;

	void SetScale( FLOAT fScale );
	void SetScale( FLOAT fScaleX, FLOAT fScaleY );

	FLOAT GetAspectRatio() const;
	void SetAspectRatio( FLOAT fRatio );

	virtual void Zoom( const CPoint& rpt, FLOAT fScale, BOOL bZoomToWindowCenter = FALSE );

	CGZoomEvent* CreateZoomEvent();
	void DispatchZoomEvent( CGZoomEvent& rEvent );

	CGScrollEvent* CreateScrollEvent();
	void DispatchScrollEvent( CGScrollEvent& rEvent );

	virtual void DrawBkGnd( Graphics& rGdip );

	overrided void Draw( Graphics& rGdip );
	overrided void DrawOverlay( Graphics& rGdip );

	overrided BOOL GetCTM( Matrix& rMtx ) const;
	overrided BOOL GetCTM( Matrix& rMtx, INT nType ) const;
	overrided void UpdateCTM( Matrix& rMtx );

	overrided BOOL IsDisplayAttribute( const CGIAttr& rAttr ) const;
	overrided void AttributeChanged( const CGIAttr& rAttr );
	overrided LPCTSTR GetTagName() const;

	overrided void GetClipRect( RectF& rrcf ) const;
	overrided BOOL GetRect( GRectF& rBBox ) const;

protected:
	FLOAT			m_fOffsetToCenterX;
	FLOAT			m_fOffsetToCenterY;

public:
	Color			m_c;
	CGIViewBox		m_aViewBox;

	CGIAttrGroup	m_agView;
	CGSAFloatLink	m_aX;
	CGSAFloatLink	m_aY;
	CGSAFloatLink	m_aWidth;
	CGSAFloatLink	m_aHeight;
	CGSAPointFLink	m_aOrigin;
	CGSAFloatLink	m_aScale;
	CGSAFloatLink	m_aAspectRatio;

	CGIAttrGroup	m_agDoc;
	CGSAFloatLink	m_aDocWidth;
	CGSAFloatLink	m_aDocHeight;
	CGSABoolLink	m_aDocCenter;
};

inline FLOAT CGIView::GetAspectRatio() const {
	return m_aAspectRatio; }

inline LPCTSTR CGIView::GetTagName() const {
	return ELEMENT_TAGNAME; }

#endif //!___G_VIEW__PH___