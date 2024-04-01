#ifndef ___G_VIEW_BOX__PH___
#define ___G_VIEW_BOX__PH___

#include <g\attr\gAttrGroup.h>
class GDOM_EXT_CLASS CGIViewBox : public CGIAttrGroup
{
public:
	enum EAspectRatioType { enARNone, enARMeet, enARSlice };
	enum EAlign			  { enANone, enAxMinYMin, enAxMidYMin, enAxMaxYMin,
									 enAxMinYMid, enAxMidYMid, enAxMaxYMid,
									 enAxMinYMax, enAxMidYMax, enAxMaxYMax };

public:
	CGIViewBox( LPCTSTR pctszName );
	virtual ~CGIViewBox();

public:
	void SetViewSize( FLOAT fWidth, FLOAT fHeight );

	void SetOrigin( FLOAT x, FLOAT y );
	void SetOrigin( const GPointF& rgptf );
	void SetSize( FLOAT fWidth, FLOAT fHeight );
	void Set( FLOAT x, FLOAT y, FLOAT fWidth, FLOAT fHeight );
	void Set( const GPointF& rgptf, FLOAT fWidth, FLOAT fHeight );

	void GetOrigin( FLOAT& rx, FLOAT& ry ) const;
	void GetOrigin( GPointF& rgptf ) const;
	void GetSize( FLOAT& rfWidth, FLOAT& rfHeight ) const;
	void Get( FLOAT& rx, FLOAT& ry, FLOAT& rfWidth, FLOAT& rfHeight ) const;
	void Get( GPointF& rgptf, FLOAT& rfWidth, FLOAT& rfHeight ) const;

	void SetAlign( EAlign enType );
	void SetAspectRatioType( EAspectRatioType enType );

	overrided void InitializeAttributes();

	overrided BOOL GetCTM( Matrix& rmtx ) const;
	overrided void UpdateCTM( Matrix& rMtx );

	overrided void Update();

public:
	CGSABoolLink		m_aEnable;
	CGSAFloatLink		m_aX;
	CGSAFloatLink		m_aY;
	CGSAFloatLink		m_aWidth;
	CGSAFloatLink		m_aHeight;

protected:
	Matrix*				m_pmtxViewBox;
	FLOAT				m_fViewWidth;
	FLOAT				m_fViewHeight;

	EAspectRatioType	m_enAspectRatioType;
	EAlign				m_enAlign;
};

#endif //!___G_VIEW_BOX__PH___