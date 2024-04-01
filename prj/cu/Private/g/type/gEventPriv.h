#ifndef ___G_EVENT_PRIV__PH___
#define ___G_EVENT_PRIV__PH___

#include <gbase\gEvent.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGZoomEventPriv : public CGZoomEvent
{
public:
	CGZoomEventPriv( CGEventTarget* pTarget );

	void SetZoomRectScreen( const GRectF& rgrcf );

	void SetPreviousAspectRatio( float fRatio );
	void SetAspectRatio( float fRatio );

	void SetPreviousScale( float fScale );
	void SetScale( float fScale );

	void SetPreviousTranslate( const GPointF& rgptf );
	void SetTranslate( const GPointF& rgptf );
};

inline void CGZoomEventPriv::SetZoomRectScreen( const GRectF& rgrcf ) {
	//m_grctfZoom = rgrcf; 
}

inline void CGZoomEventPriv::SetPreviousAspectRatio( float fRatio ) {
	m_fPrevAspectRatio = fRatio; }

inline void CGZoomEventPriv::SetAspectRatio( float fRatio ) {
	m_fAspectRatio = fRatio; }

inline void CGZoomEventPriv::SetPreviousScale( float fScale ) {
	m_fPrevScale = fScale; }

inline void CGZoomEventPriv::SetScale( float fScale ) {
	m_fScale = fScale; }

inline void CGZoomEventPriv::SetPreviousTranslate( const GPointF& rgptf ) {
	m_gptfPrevTranslate = rgptf; }

inline void CGZoomEventPriv::SetTranslate( const GPointF& rgptf ) {
	m_gptfTranslate = rgptf; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGScrollEventPriv : public CGScrollEvent
{
public:
	CGScrollEventPriv( CGEventTarget* pTarget );

	void SetZoomRectScreen( const GRectF& rgrcf );

	void SetPreviousAspectRatio( float fRatio );
	void SetAspectRatio( float fRatio );

	void SetPreviousScale( float fScale );
	void SetScale( float fScale );

	void SetPreviousTranslate( const GPointF& rgptf );
	void SetTranslate( const GPointF& rgptf );
};

inline void CGScrollEventPriv::SetZoomRectScreen( const GRectF& rgrcf ) {
	//m_grctfZoom = rgrcf; 
}

inline void CGScrollEventPriv::SetPreviousAspectRatio( float fRatio ) {
	m_fPrevAspectRatio = fRatio; }

inline void CGScrollEventPriv::SetAspectRatio( float fRatio ) {
	m_fAspectRatio = fRatio; }

inline void CGScrollEventPriv::SetPreviousScale( float fScale ) {
	m_fPrevScale = fScale; }

inline void CGScrollEventPriv::SetScale( float fScale ) {
	m_fScale = fScale; }

inline void CGScrollEventPriv::SetPreviousTranslate( const GPointF& rgptf ) {
	m_gptfPrevTranslate = rgptf; }

inline void CGScrollEventPriv::SetTranslate( const GPointF& rgptf ) {
	m_gptfTranslate = rgptf; }

///////////////////////////////////////////////////////////////////////////////////////////////////
class CU_EXT_CLASS CGMutationEventPriv : public CGMutationEvent
{
public:
	CGMutationEventPriv( LPCTSTR pctszEventType, CGEventTarget* pTarget );
	void SetNewValue( void* pNewValue );
};

#endif //!___G_EVENT_PRIV__PH___