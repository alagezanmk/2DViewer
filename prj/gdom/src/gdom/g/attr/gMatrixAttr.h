#ifndef ___G_MATRIX_ATTR__PH___
#define ___G_MATRIX_ATTR__PH___

#include "gAttr.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
class GDOM_EXT_CLASS CGSFMatrix : public CGIAttr
{
public:
	virtual ~CGSFMatrix();

public:
	const GMatrixF& Get() const;
	BOOL Set( const GMatrixF& rptfValue );

protected:
	GMatrixF	m_mtxf;
};

class GDOM_EXT_CLASS CGMFMatrix: public CGIAttrArray
{
public:
	virtual ~CGMFMatrix();

public:
	GMatrixF* GetList();
	const GMatrixF* GetList() const;
	const GMatrixF& GetAt( INT nIndex ) const;
	BOOL SetAt( INT nIndex, const GMatrixF& rptfValue, INT nCount = 1 );
	BOOL InsertAt( INT nIndex, const GMatrixF& rptfValue, INT nCount = 1 );
	BOOL RemoveAt( INT nIndex, INT nCount = 1 );

protected:
	CArray<GMatrixF, const GMatrixF&>	m_arrpmtxf;
};

#endif //!___G_MATRIX_ATTR__PH___
