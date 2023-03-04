#include "StdAfx.h"
#include "htmessageMgr.h"

#include "..\..\engine\HTUtilLib\HTXMLParser.h"
#include "..\..\engine\HTUtilLib\HTFile.h"

HTMsgIDLevel::HTMsgIDLevel() { iID = 0; byteLevel = 0; }
HTMsgIDLevel::~HTMsgIDLevel() {}
HTMsgIDLevel::HTMsgIDLevel( const HTMsgIDLevel& oIDLevel ) { iID = oIDLevel.iID; byteLevel = oIDLevel.byteLevel; }

#define HT_LOADCELL( szCell, Value, DataType ) \
{ strCell = (szCell); pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp ); Value = (DataType)iTemp; }

CHTMessage::CHTMessage(void) : m_nItems(0)
{
}

CHTMessage::~CHTMessage(void)
{
	HTMessage_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

// Load & Save
bool
CHTMessage::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	return true;
}

bool
CHTMessage::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTMessage* pRecord = NULL;
	int iID;
	HTMessageSave message;
	char szDecodeMessage[HT_MESSAGE_MAX];
	for ( int i = 0; i < m_nItems; ++i )
	{
		pFile->HT_bRead( &iID );
		pFile->HT_bRead( &message, sizeof(HTMessageSave) );

		pRecord = new HTMessage;

		for ( HTint iString = 0; iString < HT_MESSAGE_MAX; ++iString )
		{
			szDecodeMessage[iString] = message.szMessage[iString] ^ 0xFF;
		}

		pRecord->szMessage = szDecodeMessage;
		pRecord->sParameter1 = message.sParameter1;
		pRecord->sParameter2 = message.sParameter2;
		pRecord->sParameter3 = message.sParameter3;

		m_mapTable.insert( HTMessage_Value( iID, pRecord ) );
	}

	return true;
}

bool
CHTMessage::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTMessage_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	HTMessageSave message;
	char szEncodedMessage[HT_MESSAGE_MAX];

	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;

		memset( &message, 0, sizeof(HTMessageSave) );
		CHTString::HT_hrStringCopy( message.szMessage, (itTable->second)->szMessage, HT_MESSAGE_MAX );

		for ( HTint iString = 0; iString < HT_MESSAGE_MAX; ++iString )
		{
			szEncodedMessage[iString] = message.szMessage[iString] ^ 0xFF;
		}

		CHTString::HT_hrStringCopy( message.szMessage, szEncodedMessage, HT_MESSAGE_MAX );
		message.sParameter1 = (itTable->second)->sParameter1;
		message.sParameter2 = (itTable->second)->sParameter2;
		message.sParameter3 = (itTable->second)->sParameter3;

		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( &message, sizeof(HTMessageSave) );

		itTable++;
	}

	return true;
}

bool
CHTMessage::HT_bGetAllID( std::vector<HTMsgIDLevel>* pvectorIDLevel )
{
	std::vector<HTMsgIDLevel>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTMessage_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTMsgIDLevel oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTMsgIDLevel>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool
CHTMessage::HT_bGetParameter( const int id, short* psParameter1, short* psParameter2, short* psParameter3 )
{
	HTMessage_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*psParameter1 = (itTable->second)->sParameter1;
			*psParameter2 = (itTable->second)->sParameter2;
			*psParameter3 = (itTable->second)->sParameter3;
			return true;
		}
	}
	return false;
}

bool
CHTMessage::HT_bGetMessage( const int id, CHTString* pstrMessage)
{
	HTMessage_It itTable = m_mapTable.find( id );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*pstrMessage = (itTable->second)->szMessage;
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////
CHTMessageMgr::CHTMessageMgr()
{
	for( int i = 0 ; i < HT_MESSAGETYPE_END ; ++i )
		m_arrTable[i] = 0;
}

CHTMessageMgr::~CHTMessageMgr()
{
	for( int i = 0 ; i < HT_MESSAGETYPE_END ; ++i )
		delete m_arrTable[i];
}

bool
CHTMessageMgr::HT_bLoadXML( CHTString& strFile )
{
	bool bReturn = true;
	CHTString strTable;
	CHTXMLParser oXML;

	if ( HT_FAILED( oXML.HT_hrOpen( strFile ) ) ) return false;

	strTable = _T("Common");
	m_arrTable[HT_MESSAGETYPE_COMMON] = new CHTMessage;
	if ( m_arrTable[HT_MESSAGETYPE_COMMON]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("Character");
	m_arrTable[HT_MESSAGETYPE_CHARACTER] = new CHTMessage;
	if ( m_arrTable[HT_MESSAGETYPE_CHARACTER]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("Item");
	m_arrTable[HT_MESSAGETYPE_ITEM] = new CHTMessage;
	if ( m_arrTable[HT_MESSAGETYPE_ITEM]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("QuestMessage");
	m_arrTable[HT_MESSAGETYPE_QUESTMSG] = new CHTMessage;
	if ( m_arrTable[HT_MESSAGETYPE_QUESTMSG]->HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	oXML.HT_hrClose();

	return bReturn;
}

bool
CHTMessageMgr::HT_bLoad( CHTString& strFile )
{
	CHTFile oLoadFile;
	if ( !oLoadFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) ) return false;

	for( HTint i = 1; i < HT_MESSAGETYPE_END ; ++i )
		m_arrTable[i]		= new CHTMessage;

	bool bReturn = true;

	CHTString strTable;

	for( i = 1; i < HT_MESSAGETYPE_END ; ++i )
		bReturn &= m_arrTable[i]->HT_bLoad( &oLoadFile );

	oLoadFile.HT_vClose();

	return bReturn;
}

bool
CHTMessageMgr::HT_bSave( CHTString& strFile )
{
	CHTFile oSaveFile;
	if ( !oSaveFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_WRITEONLY ) )
		return false;

	bool bReturn = true;

	for( HTint i = 1; i < HT_MESSAGETYPE_END ; ++i )
		bReturn &= m_arrTable[i]->HT_bSave( &oSaveFile );

	oSaveFile.HT_vClose();

	return bReturn;
}

bool
CHTMessageMgr::HT_bTestMessage( CHTString& strFile )
{
	short sOut, sOut2, sOut3;
	CHTString str;

	FILE* pFile;
	if ( pFile = fopen( (HTtchar*)strFile, "wt" ) )
	{
		int id;

		std::vector<HTMsgIDLevel> vectorIDLevel;
		vector<HTMsgIDLevel>::iterator vec_It;

		for( int i = 1 ; i < HT_MESSAGETYPE_END ; ++i )
		{
			fprintf( pFile, "---------------------------------------");
			switch ( i )
			{
			case HT_MESSAGETYPE_COMMON:
				fprintf( pFile, "\nCommon" );
				break;
			case HT_MESSAGETYPE_CHARACTER:
				fprintf( pFile, "\nCharacter" );
				break;

			case HT_MESSAGETYPE_ITEM:
				fprintf( pFile, "\nItem" );
				break;

			case HT_MESSAGETYPE_QUESTMSG:
				fprintf( pFile, "\nQuestMessage" );
				break;

			default:
				fprintf( pFile, "\n");
				break;
			} 
			fprintf( pFile, "\n---------------------------------------");

			if( m_arrTable[i] != 0 && m_arrTable[i]->HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
			{
				vec_It = vectorIDLevel.begin();
				while ( vec_It != vectorIDLevel.end() )
				{
					id = vec_It->iID;
					fprintf( pFile, "\n    : ID(%d)", id );

					if ( m_arrTable[i]->HT_bGetParameter( id, &sOut, &sOut2, &sOut3 ) ) 
					{
						if( i == HT_MESSAGETYPE_QUESTMSG ) // 퀘스트 메세지
							fprintf( pFile, "\nHT_bGetParameter : index(%d) maxStep(%d) subIndex(%d)", sOut, sOut2, sOut3 );
						else
							fprintf( pFile, "\nHT_bGetParameter : %d %d %d", sOut, sOut2, sOut3 );
					}
					if ( m_arrTable[i]->HT_bGetMessage( id, &str ) ) 
						fprintf( pFile, "\nHT_bGetMessage : %s", str.HT_szGetString() );

					fprintf( pFile, "\n");
					fflush( pFile );

					++vec_It;
				}	//end of while
			}	// end of if( HT_bGetAllID( pvecIDLevel) )

			fprintf( pFile, "\n");
		}

		fclose( pFile );

		return true;
	}
	else
	{
		return false;
	}
}

bool
CHTMessageMgr::HT_bGetParameter( const int id, short* psParameter1, short* psParameter2, short* psParameter3 )
{
	CHTMessage* pTable = this->HT_pGetTable( id );
	if ( pTable ) return pTable->HT_bGetParameter( id, psParameter1, psParameter2, psParameter3 );
	else return false;
}

bool
CHTMessageMgr::HT_bGetMessage( const int id, CHTString* pstrMessage )
{
	CHTMessage* pTable = this->HT_pGetTable( id );
	if ( pTable ) return pTable->HT_bGetMessage( id, pstrMessage );
	else return false;
}

CHTMessage*
CHTMessageMgr::HT_pGetTable( int id )
{
	if ( HT_MESSAGETYPE_COMMON_START <= id && id <= HT_MESSAGETYPE_COMMON_END )
	{
		return m_arrTable[ HT_MESSAGETYPE_COMMON ];
	}
	else if ( HT_MESSAGETYPE_CHARACTER_START <= id && id <= HT_MESSAGETYPE_CHARACTER_END )
	{
		return m_arrTable[ HT_MESSAGETYPE_CHARACTER ];
	}
	else if ( HT_MESSAGETYPE_ITEM_START <= id && id <= HT_MESSAGETYPE_ITEM_END )
	{
		return m_arrTable[ HT_MESSAGETYPE_ITEM ];
	}
	else if ( HT_MESSAGETYPE_QUESTMSG_START <= id && id <= HT_MESSAGETYPE_QUESTMSG_END )
	{
		return m_arrTable[ HT_MESSAGETYPE_QUESTMSG ];
	}
	else
	{
		return 0;
	}
}

bool
CHTMessageMgr::HT_bIsStringParam( const short idParam )
{
	if ( ( HT_MSG_PARAM_STRING_START <= idParam ) && ( idParam <= HT_MSG_PARAM_STRING_END ) ) return true;
	else return false;
}

bool
CHTMessageMgr::HT_bIsNumberParam( const short idParam )
{
	if ( ( HT_MSG_PARAM_NUMBER_START <= idParam ) && ( idParam <= HT_MSG_PARAM_NUMBER_END ) ) return true;
	else return false;
}