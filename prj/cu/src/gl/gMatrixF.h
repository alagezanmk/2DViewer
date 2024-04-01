#ifndef ___G_DIM_MATRIX__PH___
#define ___G_DIM_MATRIX__PH___

class GMatrixF
{
public:
	// create an uninitialized mtx
	GMatrixF();

	// create from another mtx
	GMatrixF( const GMatrixF& rmtx );

	void operator=( const GMatrixF& rmtx );
	BOOL operator==( const GMatrixF& rmtx ) const;
	BOOL operator!=( const GMatrixF& rmtx ) const;

public:
	Matrix*	m_pMtx;	
};

#endif //!___G_DIM_MATRIX__PH___