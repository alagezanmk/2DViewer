#ifndef ___G_DIM_MATRIX_INL__PH___
#define ___G_DIM_MATRIX_INL__PH___

inline GMatrixF::GMatrixF() {
	VERIFY( m_pMtx = CreateMatrix() ); }

inline GMatrixF::GMatrixF( const GMatrixF& rmtx ) {
	VERIFY( m_pMtx = CreateMatrix() );
	m_pMtx->Multiply( rmtx.m_pMtx );  }

inline void GMatrixF::operator=( const GMatrixF& rmtx ) {
	ASSERT( m_pMtx && rmtx.m_pMtx );
	m_pMtx->Reset();
	m_pMtx->Multiply( rmtx.m_pMtx ); }

inline BOOL GMatrixF::operator==( const GMatrixF& rmtx ) const { 
	ASSERT( m_pMtx && rmtx.m_pMtx );
	GMatrixF* pgMtxF = const_cast<GMatrixF*>(&rmtx);
	return m_pMtx->Equals( pgMtxF->m_pMtx ); }

inline BOOL GMatrixF::operator!=( const GMatrixF& rmtx ) const { 
	ASSERT( m_pMtx && rmtx.m_pMtx );
	GMatrixF* pgMtxF = const_cast<GMatrixF*>(&rmtx);
	return FALSE == m_pMtx->Equals( pgMtxF->m_pMtx ); }

#endif //!___G_DIM_MATRIX_INL__PH___
