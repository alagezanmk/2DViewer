#ifndef ___BIN_STREAM__PH___
#define ___BIN_STREAM__PH___

#pragma warning( disable : 4786 )
#include <list>
#include <vector>

typedef UINT U32;
typedef WORD U16;
typedef BYTE U8;

typedef INT S32;
typedef SHORT S16;
typedef CHAR S8;

class CU_EXT_CLASS CBinStream
{
public:
	enum {
		enStreamReadMode,
		enStreamWriteMode,
		enStreamAppendMode,
	};

	CBinStream( INT nMode );
	INT GetMode();

	U32 GetSize();
	U8* Memory();

	void SetAppendBuffer( PVOID pData, INT nSize );
	void SetReadBuffer( PVOID pData, INT nSize );
	INT ReadData( PVOID pData, INT nSize );
	U32 ReadU32();
	U16 ReadU16();
	U8 ReadU8();

	S32 ReadS32();
	S16 ReadS16();
	S8 ReadS8();

	void WriteBits( U32 data, U32 size );			
	void WriteData( PVOID pData, U32 size, BOOL bCopy = FALSE );
	void WriteDWord( U32 data );
	void WriteWord(  U32 data );
	void WriteByte(  U32 data );

	void FlushBits();					
 	void Append( CBinStream* _SWFStream );			

	INT WriteToFile( CFile* pFile );
	INT WriteToMemory( U8* memory );	
		
	static U32 MinBits(U32 number, U16 sign);
	static U32 MaxNum(S32 a, S32 b, S32 c, S32 d);

private:
	struct SLargeData
	{
		BOOL bcopy;
		U32  position;
		U8*  data;
		U32  size;
	};

	std::vector<U8>			m_Stream;
	U32						m_u32StreamPos;
	U32						m_u32BytePos;
	U8						m_u8CurrentByte;

	PBYTE					m_pbyBuf;
	INT						m_nSize;

	std::list<SLargeData>	m_OutDataList;		// stores pointer data - the overhead is not as bad as it seems
	INT						m_nMode;
};

inline U8* CBinStream::Memory() { 
	return &m_Stream[0]; }

inline INT CBinStream::GetMode() {
	return m_nMode; }

#endif//!___BIN_STREAM__PH___
