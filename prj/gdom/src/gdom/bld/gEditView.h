#ifndef ___G_EDITOR_VIEW__PH___
#define ___G_EDITOR_VIEW__PH___

#include <g\type\idom\giView.h>

class GDOM_EXT_CLASS CGIEditView : public CGIView
{
	DECL_GTPYECLASS_DYNCREATE(CGIEditView)

public:
	enum MTX_TYPE
	{
		MTX_RENDER_TO_DOCUMENT	= 3,
		MTX_DOCUMENT			= 4,
	};

public:
	CGIEditView();

protected:
	virtual ~CGIEditView();

public:
	FLOAT GetDocumentScale() const;
	FLOAT GetDocumentScaleX() const;
	FLOAT GetDocumentScaleY() const;
	void GetDocumentScale( FLOAT& rfX, FLOAT& rfY ) const;
	void GetDocumentScale( CGPointF& rgptf ) const;

	void SetDocumentScale( FLOAT fScale );
	void SetDocumentScale( FLOAT fScaleX, FLOAT fScaleY );

	FLOAT GetDocumentAspectRatio() const;
	void SetDocumentAspectRatio( FLOAT fRatio );

	virtual void GetRenderSize( FLOAT& rfWidth, FLOAT& rfHeight, Matrix* pmtx, BOOL bScaled = TRUE ) const;

	overrided void GetRenderSize( FLOAT& rfWidth, FLOAT& rfHeight ) const;
	overrided void GetRenderCTM( Matrix& rmtx );
	
	overrided BOOL GetCTM( Matrix& rMtx ) const;
	overrided BOOL GetCTM( Matrix& rMtx, INT nType ) const;
	overrided void UpdateCTM( Matrix& rMtx );

	overrided void InitializeAttributes();
	overrided BOOL GetDrawBBox( GRectF& rBBox, Matrix* pmtx = NULL ) const;

	overrided void GetClipRect( RectF& rrcf ) const;

	overrided void Draw( Graphics& rGdip );
	overrided void DrawBkGnd( Graphics& rGdip );
	overrided void DrawOverlay( Graphics& rGdip );

public:
	CGSAFloatLink	m_aDocSkewX;
	CGSAFloatLink	m_aDocSkewY;
	CGSAFloatLink	m_aDocScale;
	CGSAFloatLink	m_aDocRotate;
	CGSAFloatLink	m_aDocAspectRatio;

	CGSAFloatLink	m_aWrkSpaceTop;
	CGSAFloatLink	m_aWrkSpaceLeft;
	CGSAFloatLink	m_aWrkSpaceBottom;
	CGSAFloatLink	m_aWrkSpaceRight;
};

inline FLOAT CGIEditView::GetDocumentAspectRatio() const {
	return m_aDocAspectRatio; }

#endif //!___G_VIEW__PH___