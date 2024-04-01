#ifndef ___G_PRIV__PH___
#define ___G_PRIV__PH___

inline CPtrArray* _Create( CPtrArray*& prarpArr )
{
	if( NULL == prarpArr )
		VERIFY( prarpArr = new CPtrArray );

	return prarpArr;
}

inline void _DeleteIfEmpty( CPtrArray*& prarpArr )
{
	if( NULL == prarpArr )
		return;

	if( 0 == prarpArr->GetSize() )
	{
		delete prarpArr;
		prarpArr = NULL;
	}
}

inline void _Delete( CPtrArray*& prarpArr )
{
	if( prarpArr )
	{
		delete prarpArr;
		prarpArr = NULL;
	}
}

#ifdef __CGNodeList
inline CGNodeList* _Create( CGNodeList*& prarpNodeList )
{
	if( NULL == prarpNodeList )
		VERIFY( prarpNodeList = new CGNodeList );

	return prarpNodeList;
}

inline void _DeleteIfEmpty( CGNodeList*& prarpNodeList )
{
	if( NULL == prarpNodeList )
		return;

	if( 0 == prarpNodeList->GetSize() )
	{
		delete prarpNodeList;
		prarpNodeList = NULL;
	}
}

inline void _Delete( CGNodeList*& prarpNodeList )
{
	if( prarpNodeList )
	{
		delete prarpNodeList;
		prarpNodeList = NULL;
	}
}
#endif //__CGNodeList

inline CMapStringToPtr* _Create( CMapStringToPtr*& prarpMapStrToPtr )
{
	if( NULL == prarpMapStrToPtr )
		VERIFY( prarpMapStrToPtr = new CMapStringToPtr );

	return prarpMapStrToPtr;
}

inline void _DeleteIfEmpty( CMapStringToPtr*& prarpMapStrToPtr )
{
	if( NULL == prarpMapStrToPtr )
		return;

	if( 0 == prarpMapStrToPtr->GetCount() )
	{
		delete prarpMapStrToPtr;
		prarpMapStrToPtr = NULL;
	}
}

inline void _Delete( CMapStringToPtr*& prarpMapStrToPtr )
{
	if( prarpMapStrToPtr )
	{
		delete prarpMapStrToPtr;
		prarpMapStrToPtr = NULL;
	}
}

#endif //!___G_PRIV__PH___