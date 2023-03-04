//////////////////////////////////////////////////////////////////////////////////////////
// 설명 : 게임 내에서 출력할 에러메세지, 네트워크 메세지 등으로 사용되는 스트링 모음
// 
// 작성자 : 김선미
// 2004.01.09
//
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HTMessage_H_
#define _HTMessage_H_

#include "HTMessageDef.h"

#define HT_MESSAGE_MAX	500

#define HT_MESSAGETYPE_COMMON			1
#define HT_MESSAGETYPE_COMMON_START			1
#define HT_MESSAGETYPE_COMMON_END			1000

#define HT_MESSAGETYPE_CHARACTER		2
#define HT_MESSAGETYPE_CHARACTER_START		1001
#define HT_MESSAGETYPE_CHARACTER_END		2000

#define HT_MESSAGETYPE_ITEM				3
#define HT_MESSAGETYPE_ITEM_START			2001
#define HT_MESSAGETYPE_ITEM_END				10000

#define HT_MESSAGETYPE_QUESTMSG			4
#define HT_MESSAGETYPE_QUESTMSG_START		50001
#define HT_MESSAGETYPE_QUESTMSG_END			60000

#define	HT_MESSAGETYPE_END				5

struct HTMsgIDLevel
{
	HTMsgIDLevel();
	~HTMsgIDLevel();
	HTMsgIDLevel( const HTMsgIDLevel& oIDLevel );
	int		iID;
	byte	byteLevel;
};

class CHTXMLParser;

class CHTMessage
{
public:
	CHTMessage(void);
	~CHTMessage(void);

	bool		HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	bool		HT_bLoad( CHTFile* pFile );
	bool		HT_bSave( CHTFile* pFile );

	bool		HT_bGetAllID( std::vector<HTMsgIDLevel>* pvectorIDLevel );

	bool		HT_bGetParameter( const int id, short* psParameter1, short* psParameter2, short* psParameter3 );
	bool		HT_bGetMessage( const int id, CHTString* pstrMessage );

private:
	struct HTMessageSave
	{
		char			szMessage[HT_MESSAGE_MAX];

		short			sParameter1;
		short			sParameter2;
		short			sParameter3;
	};

	struct HTMessage
	{
		CHT_DATA_STR	szMessage;

		short			sParameter1;
		short			sParameter2;
		short			sParameter3;
	};

	typedef std::map<int,HTMessage*>				HTMessage_Map;
	typedef std::map<int,HTMessage*>::value_type	HTMessage_Value;
	typedef std::map<int,HTMessage*>::iterator		HTMessage_It;

	HTMessage_Map	m_mapTable;

	HTint			m_nItems;
};

class CHTMessageMgr
{
public:
	CHTMessageMgr(void);
	~CHTMessageMgr(void);

	CHTMessage*	HT_pGetTable( int id );

	bool		HT_bTestMessage( CHTString& strFile );

	bool		HT_bIsStringParam( const short idParam );
	bool		HT_bIsNumberParam( const short idParam );

	// 언어 설정
	void		HT_vSetLanguage( CHTString szLanguage ) { m_szLanguage = szLanguage; }

	bool		HT_bLoad( CHTString& strFile );
	bool		HT_bLoadXML( CHTString& strFile );
	bool		HT_bSave( CHTString& strFile );

	bool		HT_bGetParameter( const int id, short* psParameter1, short* psParameter2, short* psParameter3 );
	bool		HT_bGetMessage( const int id, CHTString* pstrMessage );

private:
	CHTMessage*		m_arrTable[HT_MESSAGETYPE_END];
	CHTString		m_szLanguage;
};

#endif