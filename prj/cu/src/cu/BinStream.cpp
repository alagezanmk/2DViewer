#include "stdafx.h"
#pragma warning( disable : 4786 )
#include <cu\BinStream.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CBinStream::CBinStream( INT nMode )
{
	m_nMode = nMode;
	m_u32StreamPos = 0;				//the position in the CBinStream(how many bytes you have put in)
	m_u32BytePos = 8;				//the number of bits left to fill in the current byte
	m_u8CurrentByte = 0;			//the value of the current byte being created

	// start out at 1k to make faster - 
	// if it is a debug build, don't reserve, as we wish to stress the system
#ifndef DEBUG
	m_Stream.reserve( 1024 );
#endif

	m_Stream.push_back( 0 );
}

//	Adds 'size' bits from 'data' to the m_Stream CBinStream. Data is in the form of
//	a U32.  Size indicates how many of the 32 bits are significant and should 
//	be output.  It checks how many bits are available in the current output byte
//	and works by repeatedly stuffing it with the next bits from 'data' 
//	and then adding m_u8CurrentByte to the m_Stream until all "size" bits have been output.  
void CBinStream::WriteBits(U32 data, U32 size)	 //adds individual bits
{
	ASSERT( enStreamAppendMode == m_nMode || enStreamWriteMode == m_nMode );
	ASSERT( ( data <= (0x01<<size) - 1 ) || ( -(S32)(data) <= (0x01<<size) - 1 ) );
	while ( size != 0 )
	{
		if ( size > m_u32BytePos )
		{	
			//if more bits left to write than shift out what will fit 
			m_u8CurrentByte |= data << (32 - size) >> (32 - m_u32BytePos);

			// shift all the way left, then right to right
			// justify the data to be or'ed in
			m_Stream[m_u32StreamPos] = m_u8CurrentByte;
			m_u32StreamPos++;
			m_Stream.push_back( 0 );
			size -= m_u32BytePos;
			m_u8CurrentByte = 0;
			m_u32BytePos = 8;
		}
		else if ( size <= m_u32BytePos )
		{
			m_u8CurrentByte |= data << (32 - size) >> (32 - m_u32BytePos);
			m_u32BytePos -= size;
			size = 0;

			if ( !m_u32BytePos )
			{						  //if current byte is filled
				m_Stream[m_u32StreamPos] = m_u8CurrentByte;
				m_u32StreamPos++;
				m_Stream.push_back( 0 );
				m_u8CurrentByte = 0;
				m_u32BytePos = 8;
			}
		}
	}
}

//	For adding large data that is pointed to by a pointer.  The data is only
//	integrated into the m_Stream when it is actually written to disk. 
//	E. G. a large JPEG. This is to avoid storing it twice.  
//	Stores the current m_u32StreamPos, data pointer and size in the OutDataList.
void CBinStream::WriteData( PVOID pData, U32 size, BOOL bCopy /*= FALSE*/ )
{
	ASSERT( enStreamAppendMode == m_nMode || enStreamWriteMode == m_nMode );
	SLargeData large;

	large.position = m_u32StreamPos;
	large.size     = size;
	large.bcopy    = bCopy;
	if( bCopy )
	{
		VERIFY( large.data = new BYTE[size] );
		memcpy( large.data, pData, size );
	}
	else
		large.data = (PBYTE)pData;

	m_OutDataList.push_back( large );
}

//	Kick out the current partially filled byte to the m_Stream.
//	If there is a byte currently being built for addition to the m_Stream, then the end of that
//	byte is filled with zeroes and the byte is added to the m_Stream.
void CBinStream::FlushBits()
{
	ASSERT( enStreamAppendMode == m_nMode || enStreamWriteMode == m_nMode );
	if ( m_u32BytePos != 8 )
	{
		m_Stream[m_u32StreamPos] = m_u8CurrentByte;
		m_u32StreamPos++;
		m_Stream.push_back( 0 );
		m_u8CurrentByte = 0;
		m_u32BytePos = 8;
	}
}

//  Writes a 32 bit m_Stream of data to given CBinStream in the proper form (reversed byte order),
//  so B1B2B3B4 is written as B4B3B2B1. The function does this by sending a byte at a time 
//  of the data to the CBinStream in the appropriate order.
void CBinStream::WriteDWord(U32 data)
{
	ASSERT( enStreamAppendMode == m_nMode || enStreamWriteMode == m_nMode );
	//declare variable used to output the bytes
	U32 v;
	
	//output the rightmost byte
	v = data << 24 >> 24;
	WriteBits(v, 8);
	
	//output the center right byte
	v = data << 16 >> 24;
	WriteBits(v, 8);
	
	//output the center left byte
	v = data << 8 >> 24;
	WriteBits(v, 8);
	
	//output the leftmost byte
	v = data >> 24;
	WriteBits(v, 8);
}

//  Writes a 16 bit m_Stream of data to the CBinStream in the proper form, so B1B2 is written as
//  B2B1.  
void CBinStream::WriteWord(U32 data )
{
	ASSERT( enStreamAppendMode == m_nMode || enStreamWriteMode == m_nMode );
	//declare the variable used to output the bytes
	U32 v;

	//output the rightmost byte
	v = data << 24 >> 24;
	WriteBits(v, 8);

	//output the leftmost byte
	v = data << 16 >> 24;
	WriteBits(v, 8);
}

//  Writes an 8 bit m_Stream of data to the CBinStream.  There is no bit swapping!! A byte is 
//  written as a byte.
void CBinStream::WriteByte(U32 data )
{
	ASSERT( enStreamAppendMode == m_nMode || enStreamWriteMode == m_nMode );
	//declare the variable used to output the byte
	U32 v = 0;

	//output the byte
	v = data << 24 >> 24;
	WriteBits(v, 8);
}

//	Returns the size of the CBinStream.  For purposes of denoting size in tags and headers.
U32 CBinStream::GetSize(void)
{
	ASSERT( enStreamAppendMode == m_nMode || enStreamWriteMode == m_nMode );
	INT size = m_u32StreamPos;
	std::list<SLargeData>::iterator it;

	for ( it = m_OutDataList.begin(); it != m_OutDataList.end(); it++ )
	{
		SLargeData& data = (*it);
		size += data.size;
	}
	return size;
}

//	Appends the m_Stream CBinStream to this.  Doesn't actually write the bitmaps, 
//  jpegs ...  Instead it just writes their file name with a note that the actual file 
//  should go there.
void CBinStream::Append(CBinStream *add)
{
	ASSERT( enStreamAppendMode == m_nMode || enStreamWriteMode == m_nMode );
	INT addStreamPos = 0;		// this functions position in the "add" m_Stream,
								// remembering that add->m_u32StreamPos is the END 
								// of the "add" m_Stream.

	// remove all the large data from the other m_Stream
	while( add->m_OutDataList.size() )
	{
		SLargeData data = add->m_OutDataList.front();
		add->m_OutDataList.pop_front();

		for ( ;addStreamPos < data.position; addStreamPos++ )
		{
			WriteBits( add->m_Stream[addStreamPos], 8 );
		}
		//addStreamPos should now equal data.position
		WriteData( data.data, data.size );
	}

	// Write the remainder of the m_Stream data, after the last outData.
	for ( ;addStreamPos < add->m_u32StreamPos; addStreamPos++ )
	{
		WriteBits( add->m_Stream[addStreamPos], 8);
	}
}

//	Writes the m_Stream CBinStream to the given file. 
INT CBinStream::WriteToFile( CFile* pFile )
{
	ASSERT( enStreamAppendMode == m_nMode || enStreamWriteMode == m_nMode );
	U32 currentStreamPos = 0;	//the current position in the CBinStream for writing
	const U8* currentData;
	U32 currentDataSize;
	U32 currentDataPosition;
	U32 outDataListSize = m_OutDataList.size();

	INT nWrote = 0;

	if( outDataListSize )
	{
		for( U32 i=0; i<outDataListSize; i++ )
		{
			currentDataPosition = m_OutDataList.front().position;
			currentData			= m_OutDataList.front().data;
			currentDataSize		= m_OutDataList.front().size;

			ASSERT( currentDataPosition >= currentStreamPos );

			if( currentDataPosition - currentStreamPos > 0 )
				pFile->Write( &m_Stream[currentStreamPos], (currentDataPosition - currentStreamPos) );

			nWrote += currentDataPosition - currentStreamPos;
			currentStreamPos = currentDataPosition;

			//currentStreamPos should now equal currentDataPosition
			ASSERT( currentDataSize > 0 );

			pFile->Write( currentData, currentDataSize );
			nWrote += currentDataSize;
			if( m_OutDataList.front().bcopy )
				delete (VOID*)currentData;

			m_OutDataList.pop_front();
		}
	}

	if ( m_u32StreamPos > currentStreamPos )
		pFile->Write( &m_Stream[currentStreamPos], m_u32StreamPos - currentStreamPos );

	nWrote += m_u32StreamPos - currentStreamPos;
	return nWrote;
}

INT CBinStream::WriteToMemory( U8* memory )
{
	ASSERT( enStreamAppendMode == m_nMode || enStreamWriteMode == m_nMode );
	U32 currentStreamPos = 0;	//the current position in the CBinStream for writing
	const U8* currentData;
	U32 currentDataSize;
	U32 currentDataPosition;
	U32 outDataListSize = m_OutDataList.size();

	INT nWrote = 0;

	if ( outDataListSize )
	{

		for ( U32 i=0; i<outDataListSize; i++ )
		{
			currentDataPosition = m_OutDataList.front().position;
			currentData			= m_OutDataList.front().data;
			currentDataSize		= m_OutDataList.front().size;
			m_OutDataList.pop_front();

			ASSERT( currentDataPosition >= currentStreamPos );

			if ( currentDataPosition - currentStreamPos > 0 )
			{
				memcpy( memory, &m_Stream[currentStreamPos], ( currentDataPosition - currentStreamPos ) );
				memory += currentDataPosition - currentStreamPos;
			}
			nWrote += currentDataPosition - currentStreamPos;
			currentStreamPos = currentDataPosition;

			//currentStreamPos should now equal currentDataPosition
			ASSERT( currentDataSize > 0 );

			memcpy( memory, currentData, currentDataSize );
			memory += currentDataSize;
			nWrote += currentDataSize;
		}
	}

	if ( m_u32StreamPos > currentStreamPos )
	{
		memcpy( memory, &m_Stream[currentStreamPos], m_u32StreamPos - currentStreamPos );
		memory += m_u32StreamPos - currentStreamPos;
	}
	nWrote += m_u32StreamPos - currentStreamPos;
	return nWrote;
}

//  Calculates the minimum number of bits necessary to represent the given number.  The
//	number should be given in its unsigned form with the flag sign equal to 1 if it is 
//	signed.  Repeatedly compares number to another unsigned INT called x.  
//	x is initialized to 1.  The value of x is shifted left i times until x is greater 
//	than number.  Now i is equal to the number of bits the UNSIGNED value of number needs.
//	The signed value will need one more bit for the sign so i+1 is returned if the number
//	is signed, and i is returned if the number is unsigned.
U32 CBinStream::MinBits(U32 number, U16 sign)
{
	//If the number == 0, then 0 bits are necessary for unsigned, and 1 for signed.
	//Sign should either have a value of 0 or 1.
	if ( number == 0 )
	{
		return sign;
	}

	//declare and initialize the variable for comparison
	U32 x = 1;
	U32 i;

	//keep increasing the value of x and i until s is greater than the given number
	for(i = 1; i<33; i++){
		x <<= 1;
		if (x > number){                  
			break;
		}
	}

	ASSERT( sign + i <= 32 );
	
	//return the calculated value and account for the number being signed or not
	return i + sign; 
}

//  Compares the absolute values of 4 signed integers and returns the unsigned magnitude of 
//  the number with the greatest absolute value.
U32 CBinStream::MaxNum(S32 a, S32 b, S32 c, S32 d)
{
	//take the absolute values of the given numbers
	INT aAbs = abs(a);
	INT bAbs = abs(b);
	INT cAbs = abs(c);
	INT dAbs = abs(d);

	//compare the numbers and return the unsigned value of the one with the greatest magnitude
	if (aAbs>bAbs){
		if (aAbs>cAbs){
			if (aAbs>dAbs){
				return (U32) aAbs;
			} else {
				return (U32) dAbs;
			}
		} else 
			if (cAbs>dAbs){
				return (U32) cAbs;
			} else {
				return (U32) dAbs;
			}
	} else {
		if (bAbs>cAbs){
			if (bAbs>dAbs){
				return (U32) bAbs;
			} else {
				return (U32) dAbs;
			}
		} else 
			if (cAbs>dAbs){
				return (U32) cAbs;
			} else {
				return (U32) dAbs;
			}
	}
}

void CBinStream::SetAppendBuffer( PVOID pData, INT nSize )
{
	WriteData( pData, nSize );
}

void CBinStream::SetReadBuffer( PVOID pData, INT nSize )
{
	m_nSize = nSize;
	m_pbyBuf = (PBYTE)pData;
	m_u32StreamPos = 0;
}

INT CBinStream::ReadData( PVOID pData, INT nSize )
{
	ASSERT( enStreamReadMode == m_nMode );
	ASSERT( nSize > 0 );
	if( m_u32StreamPos + nSize > m_nSize )
		nSize = m_nSize - m_u32StreamPos;

	if( pData )
		memcpy( pData, m_pbyBuf + m_u32StreamPos, nSize );
	m_u32StreamPos += nSize;
	return nSize;
}

U32 CBinStream::ReadU32()
{
	ASSERT( enStreamReadMode == m_nMode );
	if( m_u32StreamPos + 4 <= m_nSize )
	{
		m_u32StreamPos += 4;
		return *((U32*)(m_pbyBuf + m_u32StreamPos - 4));
	}

	ASSERT( FALSE );
	return -1;
}

U16 CBinStream::ReadU16()
{
	ASSERT( enStreamReadMode == m_nMode );
	if( m_u32StreamPos + 2 <= m_nSize )
	{
		m_u32StreamPos += 2;
		return *((U16*)(m_pbyBuf + m_u32StreamPos - 2));
	}

	ASSERT( FALSE );
	return -1;
}

U8 CBinStream::ReadU8()
{
	ASSERT( enStreamReadMode == m_nMode );
	if( m_u32StreamPos + 1 <= m_nSize )
	{
		m_u32StreamPos += 1;
		return *((U8*)(m_pbyBuf + m_u32StreamPos - 1));
	}

	ASSERT( FALSE );
	return -1;
}

S32 CBinStream::ReadS32()
{
	ASSERT( enStreamReadMode == m_nMode );
	if( m_u32StreamPos + 4 <= m_nSize )
	{
		m_u32StreamPos += 4;
		return *((S32*)(m_pbyBuf + m_u32StreamPos - 4));
	}

	ASSERT( FALSE );
	return -1;
}

S16 CBinStream::ReadS16()
{
	ASSERT( enStreamReadMode == m_nMode );
	if( m_u32StreamPos + 2 <= m_nSize )
	{
		m_u32StreamPos += 2;
		return *((S16*)(m_pbyBuf + m_u32StreamPos - 2));
	}

	ASSERT( FALSE );
	return -1;
}

S8 CBinStream::ReadS8()
{
	ASSERT( enStreamReadMode == m_nMode );
	if( m_u32StreamPos + 1 <= m_nSize )
	{
		m_u32StreamPos += 1;
		return *((S8*)(m_pbyBuf + m_u32StreamPos - 1));
	}

	ASSERT( FALSE );
	return -1;
}
