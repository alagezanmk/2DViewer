#ifndef ___G__VIEW_PORT__PH___
#define ___G__VIEW_PORT__PH___

class CGViewPort
{
public:
	CGViewPort();
	virtual ~CGViewPort();

	void SetWindowSize( INT nWidth, INT nHeight );
	void GetWindowSize( INT& rnWidth, INT& rnHeight );

	void SetWindowSize( const SIZE& rSize );
	const SIZE& GetWindowSize();
		
	void SetViewSize( INT nWidth, INT nHeight );
	void GetViewSize( INT& rnWidth, INT& rnHeight );

	void SetViewSize( const SIZE& rSize );
	const SIZE& GetViewSize();

	void SetScale( FLOAT fScale );
	FLOAT GetScale();

	void SetScale( FLOAT fxScale, FLOAT fyScale );
	void GetScale( FLOAT& rfxScale, FLOAT& rfyScale );

	void CalculateView();

	void SetAspectRatio( FLOAT fRatio );
	FLOAT GetAspectRatio();

	void GetDisplaySize( FLOAT& rfWidth, FLOAT& rfHeight );
	void GetDisplaySize( INT& rnWidth, INT& rnHeight );
	const SIZE& GetDisplaySize();

	void SetDisplayOrigin( FLOAT x, FLOAT y );
	void GetDisplayOrigin( FLOAT& rfx, FLOAT& rfy );

	void SetDisplayOrigin( INT x, INT y );
	void GetDisplayOrigin( INT& rnx, INT& rny );

	void SetDisplayOrigin( const POINT& rgpt );
	const POINT& GetDisplayOrigin();

protected:
	CSize	m_cbWindowSize;
	CSize	m_cbViewSize;
	CSize	m_cbDisplaySize;

	CPoint	m_ptDisplayOrigin;
	CPoint	m_ptfSkew;
	FLOAT	m_fRotate;

	FLOAT	m_fScale;
	FLOAT	m_fAspectRatio;
};

#endif //!___G__VIEW_PORT__PH___