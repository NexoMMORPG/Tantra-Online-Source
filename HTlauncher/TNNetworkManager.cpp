//----------------------------------------------------------------------------//
//	���� �̸�	: TNNetworkManager.cpp
//
//	���� ���� 	: 
//		- ���ӿ��� ����ϰ� �� ��Ʈ��ũ���� �ٷ�� Ŭ����.
//
//	�ۼ���		:
//		- 2002/08/01, Created by Youn woo Kyoung
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//


#include "stdafx.h"
#include "TNNetworkManager.h"
#include "HTNetworkMsg.h"
#include "HTextern.h"

extern unsigned	short	g_pServerListPort[MAX_SERVERGROUP][MAX_SERVERNUMBER];

#define	TNMSG_HEADER_SIZE			(sizeof(HEADER))


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TNNetworkManager::TNNetworkManager()
{
}

TNNetworkManager::~TNNetworkManager()
{
}


///////////////////////////////////////////////////////////////
//	Network Initialize Function	_2002.07.31_y.w.k
///////////////////////////////////////////////////////////////
bool TNNetworkManager::InitNetworkManager(void)
{
	g_iWorldNum = 0;
	HTint s1,s2,s3,s4;
	for( HTint i=0 ; i<MAX_SERVERGROUP ; i++ )
	{
		if( g_pServerListPort[i][0] == 0 )
			break;
		for( HTint j=0 ; j<MAX_SERVER ; j++ )
		{
			sscanf( g_pServerList[i][j], "%d.%d.%d.%d %d", &s1, &s2, &s3, &s4 );
			if( g_pServerListPort[i][j] == 0 )
				break;

			sprintf(g_oWorldList[i][j].szWorldIP,"%d.%d.%d.%d",s1, s2, s3, s4);
			g_oWorldList[i][j].snWorldPort = g_pServerListPort[i][j];

			CHTString szString;
			if( g_gServerType == SERVERTYPE_MAIN )
			{
				if( g_pMessageMgr->HT_bGetMessage( eMsgCommonServerName1+i, &szString ) == true )
				{
					CHTString::HT_hrStringCopy( g_oWorldList[i][j].szWorldName, szString.HT_szGetString(), 26 );
				}
			}
			else
			{
				if( g_pMessageMgr->HT_bGetMessage( eMsgCommonServerName9+i, &szString ) == true )
				{
					CHTString::HT_hrStringCopy( g_oWorldList[i][j].szWorldName, szString.HT_szGetString(), 26 );
				}
			}
		}
		g_iWorldNum++;
	}

	//	��ŷ ���� ����
	for( HTint i=0 ; i<5 ; i++ )
	{
		m_dwUnitSkillPassTime[i] = i*2000;
		m_dwGetItemPassTime[i] = i*2000;
	}

	//	������ ������ �ڵ� �˾ƿͼ� �߱����� ���������� ���������
	//LANGID oSysLanguageID = GetSystemDefaultLangID();
	//LANGID oUserLanguageID = GetUserDefaultLangID();
	//LANGID oLanguageID = MAKELANGID( LANG_KOREAN, SUBLANG_KOREAN );
	/*
	LCID oSysLocaleID = GetSystemDefaultLCID();
	LCID oUserLocaleID = GetUserDefaultLCID();
	//LCID oLocaleID = MAKELCID( MAKELANGID( LANG_KOREAN, SUBLANG_KOREAN ), SORT_KOREAN_KSC );

	//	�����ڵ�
	g_iInationalCode = oSysLocaleID;

	if( !g_bDevelopingMode )
	{
		if( g_iInationalCode == 2052 )
		{
			CHTString strKoreaIP;
			//	�¼� üũ
			strKoreaIP = _T("211.43.194.55");
			if( strKoreaIP.HT_iStringCompare( g_oWorldList[0][0].szWorldIP ) == 0 )
			{	
				//MessageBox( NULL, "Can not play!! You must connect china server.", "Warning !", MB_OK | MB_ICONEXCLAMATION );
				PostQuitMessage( 0 );
			}
			//	���� üũ
			strKoreaIP = _T("211.233.70.91");
			if( strKoreaIP.HT_iStringCompare( g_oWorldList[0][0].szWorldIP ) == 0 )
			{
				//MessageBox( NULL, "Can not play!! You must connect china server.", "Warning !", MB_OK | MB_ICONEXCLAMATION );
				PostQuitMessage( 0 );
			}
		}
	}
*/
	return true;
}

///////////////////////////////////////////////////
//	Get latest connecting state	20030227Tenma
///////////////////////////////////////////////////
WORD TNNetworkManager::GetConnectingState()
{
	if( g_cCPSock.Sock != 0 )
		return STATUS_ALIVE;
	else
		return STATUS_DISCONNECT;
}


////////////////////////////////////////////////////////////////////////////////////////
//	Network Connect Function	_2002.07.31_y.w.k
////////////////////////////////////////////////////////////////////////////////////////
HTint TNNetworkManager::Connect( char *a_pstrServerIP, short a_nPortNum)
{
//	CHTString str;
//	str.HT_szFormat("Connect %s:%d",a_pstrServerIP, a_nPortNum);
//	MessageBox(NULL, str, "DEBUG", MB_OK);

	if( g_cCPSock.ConnectServer( a_pstrServerIP, a_nPortNum, INADDR_ANY, WSA_READ, g_hWnd ) == 0 )
		return 0;
	else
		return 1;
}


////////////////////////////////////////////////////////////////////////////////////////
//	Network DisConnect Function	_2002.07.31_y.w.k
////////////////////////////////////////////////////////////////////////////////////////
HTint TNNetworkManager::DisConnect()
{
	g_cCPSock.CloseSocket();

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////
//	**	�α��� �׷�  **  ////////////////////////////////////////////////////////	
/////////////////////////////////////////////////////////////////////////////////
//	���� ��ǥ �������� ������ ��û��.
HTRESULT TNNetworkManager::RequestReqMoveZoneServer(PS_CSP_REQ_MOVE_ZONE_SERVER pData)
{
	if( pData == NULL )
		return HT_FAIL;

//	HSTRACE(eGame, "RequestReqMoveZoneServer \n");

	//	SendData
	short	iTotalSize = sizeof( S_CSP_REQ_MOVE_ZONE_SERVER );
	pData->wType	= CSP_REQ_MOVE_ZONE_SERVER;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ɸ����� ����Ʈ�� ��û��.
HTRESULT TNNetworkManager::RequestCharList()
{
//	HSTRACE(eGame, "RequestCharList \n");

	_S_CSP_REQ_CHAR_LIST* pData = NULL;
	pData = new _S_CSP_REQ_CHAR_LIST;
	
	pData->wType	= CSP_REQ_CHAR_LIST;
	pData->wSeq	= 0;		
	pData->wPDULength	= sizeof( _S_CSP_REQ_CHAR_LIST ) - TNMSG_HEADER_SIZE;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, sizeof( _S_CSP_REQ_CHAR_LIST ) );

	if( pData != NULL )
		delete pData;

	return HT_OK;
}

//	�ɸ��� ������ ��û��.
HTRESULT TNNetworkManager::RequestCharCreation(_S_CSP_REQ_CHAR_CREATE* pData)
{
//	HSTRACE(eGame, "RequestCharCreation \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_CHAR_CREATE );
	pData->wType	= CSP_REQ_CHAR_CREATE;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ɸ��� ������ ��û��.
HTRESULT TNNetworkManager::RequestCharDeletion(_S_CSP_REQ_CHAR_REMOVE* pData)
{
//	HSTRACE(eGame, "RequestCharDeletion \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_CHAR_REMOVE );
	pData->wType	= CSP_REQ_CHAR_REMOVE;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

			//if( pPacket != NULL )
			//	free( pPacket );

	return HT_OK;
}

//	�ɸ��� ������ ��û��.	
HTRESULT TNNetworkManager::RequestReqCharSelect(_S_CSP_REQ_CHAR_SELECT* pData)
{
//	HSTRACE(eGame, "RequestReqCharSelect \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_CHAR_SELECT );
	pData->wType	= CSP_REQ_CHAR_CREATE;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

			//if( pPacket != NULL )
			//	free( pPacket );

	return HT_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//	**  Initialize �׷�	 **  ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//	�ɸ��� �ʱ� �����͸� ��û.
HTRESULT TNNetworkManager::RequestInitChar(PS_CSP_REQ_CHAR_INIT pData)
{
//	HSTRACE(eGame, "RequestInitChar \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_CHAR_INIT );
	pData->wType	= CSP_REQ_CHAR_INIT;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ٸ�������Ʈ�� �̴��� ��û��
HTRESULT TNNetworkManager::RequestInitMobByID( MSG_REQMobByID* pData )
{
//	HSTRACE(eGame, "ReqMobByID \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_REQMobByID );
	pData->wType	= _MSG_REQMobByID;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	ĳ���� �װ�, Regen �ʱ�ȭ ��û
HTRESULT TNNetworkManager::RequestReqInitRegenChar(PS_CSP_REQ_INIT_REGEN_CHAR pData)
{
//	HSTRACE(eGame, "RequestReqInitRegenChar \n");

	short	iTotalSize = sizeof( S_CSP_REQ_INIT_REGEN_CHAR );
	pData->wType	= CSP_REQ_INIT_REGEN_CHAR;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//	**	Moving, Packing/UnPacking, Using **  ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//	ĳ���Ͱ� �������� ���� ������ ����
HTRESULT TNNetworkManager::RequestCharAct(PS_CSP_REQ_CHAR_ACT pData)
{
//	HSTRACE(eGame, "RequestCharAct \n");

	short	iTotalSize = sizeof( S_CSP_REQ_CHAR_ACT );
	pData->wType	= CSP_REQ_CHAR_ACT;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	������ �̵����
HTRESULT TNNetworkManager::RequestItemMove(_S_CSP_REQ_ITEM_MOVE* pData)
{
//	HSTRACE(eGame, "RequestItemMove \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_ITEM_MOVE );
			//BYTE*		pTempPacket = NULL , *pPacket = NULL;

			//pTempPacket = pPacket = GetMsgResouce( sizeof( S_CSP_REQ_ITEM_MOVE ), &iTotalSize );
			//m_ClientMsgComposer.MakeItemMoveMsg( pTempPacket, PData );

	pData->wType	= CSP_REQ_ITEM_MOVE;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

			//if( pPacket != NULL )
			//	free( pPacket );

	return HT_OK;
}

// �� ���� ������ ����߸���
HTRESULT TNNetworkManager::RequestItemDrop(_S_CSP_REQ_ITEM_DROP* pData)
{
//	HSTRACE(eGame, "RequestItemDrop \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_ITEM_DROP );

	pData->wType	= CSP_REQ_ITEM_DROP;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

// ������ ������ �ݱ�
HTRESULT TNNetworkManager::RequestItemGet(_S_CSP_REQ_ITEM_GET* pData)
{
//	HSTRACE(eGame, "RequestItemGet \n");
	if( pData == NULL )
		return HT_FAIL;

	////	�Լ� �� ��ŷ üũ
	//for( HTint i=0 ; i<4 ; i++ )
	//{
	//	m_dwGetItemPassTime[i] = m_dwGetItemPassTime[i+1];
	//}
	//m_dwGetItemPassTime[4] = timeGetTime();

	//if( abs(m_dwGetItemPassTime[4]-m_dwGetItemPassTime[0] ) < 500 )
	//{
	//	this->DisConnect();
	//}
	//else
	{
		short	iTotalSize = sizeof( S_CSP_REQ_ITEM_GET );
		pData->wType	= CSP_REQ_ITEM_GET;
		pData->wSeq	= 0;		
		pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
		pData->wDummy = 0;
		pData->dwClientTick  = timeGetTime();

		g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );
	}

	return HT_OK;
}

//	������ ��ŷ�� ��û��.
HTRESULT TNNetworkManager::RequestItemPacking( MSG_Packing* pData )
{
//	HSTRACE(eGame, "RequestItemPacking \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_Packing );

	pData->wType	= _MSG_Packing;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	������ ����� ��û��.
HTRESULT TNNetworkManager::RequestItemUse( MSG_ITEM* pData )
{
//	HSTRACE(eGame, "RequestItemUse \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_ITEM );

	pData->wType	= MSG_ITEM_ID;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	���Ǿ��� �̵��� ��û��.
HTRESULT TNNetworkManager::RequestMoneyMove( MSG_Money_Move* pData )
{
//	HSTRACE(eGame, "RequestMoneyMove \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_Money_Move );

	pData->wType	= _MSG_Money_Move;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ɸ����� �̵��� ��û��.
HTRESULT TNNetworkManager::RequestCharMoveBroadcast( PS_CSP_REQ_CHAR_MOVE_BROADCAST pData )
{
	//HSTRACE(eGame, "RequestCharMoveBroadcast \n");

	//short	iTotalSize;
	//BYTE*		pTempPacket = NULL , *pPacket = NULL;

	//pTempPacket = pPacket = GetMsgResouce( sizeof( S_CSP_REQ_CHAR_MOVE_BROADCAST ), &iTotalSize );

	//m_ClientMsgComposer.MakeReqCharMoveBroadcastMsg( pTempPacket, pData );

	//g_cCPSock.SendOneMessage( ( char * )pPacket, iTotalSize );

	//if( pPacket != NULL )
	//	free( pPacket );

	return HT_OK;
}

//	�ɸ����� �̵��� ��û��2.
HTRESULT TNNetworkManager::RequestMSG_Action( MSG_Action* pData )
{
//	HSTRACE(eGame, "RequestMSG_Action \n");

	short	iTotalSize = sizeof( MSG_Action );
	pData->wType	= _MSG_Action;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	������ ��û��
HTRESULT TNNetworkManager::RequestMSG_Attack( MSG_Attack* pData, HTint iMsgSize )
{
//	HSTRACE(eGame, "RequestMSG_Attack \n");

	short	iTotalSize;
	if( iMsgSize == 0 )
	{
		iTotalSize = sizeof( MSG_Attack );
        pData->wType	= _MSG_Attack;
	}
	else if( iMsgSize == 1 )
	{
		iTotalSize = sizeof( MSG_AttackOne );
        pData->wType	= _MSG_AttackOne;
	}
	else if( iMsgSize == 2 )
	{
		iTotalSize = sizeof( MSG_AttackTwo );
        pData->wType	= _MSG_AttackTwo;
	}

	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	��Ż�̵��� ��û��.
HTRESULT TNNetworkManager::RequestReqMovePortal(PS_CSP_REQ_MOVE_PORTAL pData)
{
//	HSTRACE(eGame, "RequestReqMovePortal \n");

	short	iTotalSize = sizeof( S_CSP_REQ_MOVE_PORTAL );
	pData->wType	= CSP_REQ_MOVE_PORTAL;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Į���ھ� ����� ��û��
HTRESULT TNNetworkManager::RequestReqRegisterKalaCore(MSG_REGISTER_KALA_CORE* pData)
{
//	HSTRACE(eGame, "RequestReqRegisterKalaCore \n");

	short	iTotalSize = sizeof( MSG_REGISTER_KALA_CORE );
	pData->wType	= REGISTER_KALA_CORE;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}


/////////////////////////////////////////////////////////////////////////////////
//  **  Normal Combat  **  //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//	PK��ư ��� �޽���
HTRESULT TNNetworkManager::RequestPKToggleButton(MSG_TOGGLE_BUTTON* pData)
{
//	HSTRACE(eGame, "RequestReq_Msg_Toggle_Button \n");

	short	iTotalSize = sizeof( MSG_TOGGLE_BUTTON );
	pData->wType	= _MSG_TOGGLE_BUTTON;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//	**  Chatting  **  ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//	�Ϲ� ä�� ó���� �˸�.
HTRESULT TNNetworkManager::RequestReqNormalChat(PS_CSP_REQ_CHAT pData)
{
//	HSTRACE(eGame, "RequestReqNormalChat \n");

	short	iTotalSize = sizeof( S_CSP_REQ_CHAT );
	pData->wType	= CSP_REQ_CHAT;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ӼӸ� ä�� ó���� �˸�.
HTRESULT TNNetworkManager::RequestReqWhisperChat(PS_CSP_REQ_WHISPER_CHAT pData)
{
//	HSTRACE(eGame, "RequestReqWhisperChat \n");

	short	iTotalSize = sizeof( S_CSP_REQ_WHISPER_CHAT );
	pData->wType	= CSP_REQ_WHISPER_CHAT;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	��Ƽ ä���� �˸�.
//	��Ƽ ä���� �˸�.
HTRESULT TNNetworkManager::RequestGroupChat(MSG_Chat* pData)
{
//	HSTRACE(eGame, "ReqMSG_Chat \n");

	short	iTotalSize = sizeof( MSG_Chat );
	pData->wType	= _MSG_Chat;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	���峻 ���� ä���� �˸�.
HTRESULT TNNetworkManager::ReqNotifyMessage(MSG_Broadcast* pData)
{
//	HSTRACE(eGame, "ReqNotifyMessage \n");

	short	iTotalSize = sizeof( MSG_Broadcast );
	pData->wType	= _MSG_Broadcast;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//	**  Party/Guild/Address Book  **  ///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//	��Ƽ ����/������ ��û��
HTRESULT TNNetworkManager::RequestReqCreateJoinParty(MSG_REQParty* pData)
{
//	HSTRACE(eGame, "RequestReqCreateJoinParty \n");

	short	iTotalSize = sizeof( MSG_REQParty );
	pData->wType	= _MSG_REQParty;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	��Ƽ ���Կ�û�� ���� ����
HTRESULT TNNetworkManager::RequestReqCNFParty(MSG_CNFParty* pData)
{
//	HSTRACE(eGame, "RequestReqCNFParty \n");

	short	iTotalSize = sizeof( MSG_CNFParty );
	pData->wType	= _MSG_CNFParty;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	��Ƽ Ż��/��ü ��û
HTRESULT TNNetworkManager::RequestReqRemoveParty(MSG_RemoveParty* pData)
{
//	HSTRACE(eGame, "RequestReqRemoveParty \n");

	short	iTotalSize = sizeof( MSG_RemoveParty );
	pData->wType	= _MSG_RemoveParty;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ڵ��й� ��� ���� ��û
HTRESULT TNNetworkManager::RequestSetParty(MSG_SetParty* pData)
{
//	HSTRACE(eGame, "RequestSetParty \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_SetParty );
	pData->wType	= _MSG_SetParty;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ּҷ� ����� ��û��
HTRESULT TNNetworkManager::RequestJoinAddressBook(MSG_ReqMessenger* pData)
{
//	HSTRACE(eGame, "MSG_ReqMessenger \n");

	short	iTotalSize = sizeof( MSG_ReqMessenger );
	pData->wType	= _MSG_ReqMessenger;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ּҷ� �߰� ��û�� ���� ����� ó����
HTRESULT TNNetworkManager::RequestJoinAddressBookResult(MSG_CNFMessenger* pData)
{
//	HSTRACE(eGame, "MSG_CNFMessenger \n");

	short	iTotalSize = sizeof( MSG_CNFMessenger );
	pData->wType	= _MSG_CNFMessenger;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ּҷϿ��� ������ ��û��
HTRESULT TNNetworkManager::RequestReqAddressBookMemberDelete(MSG_RemoveMessenger* pData)
{
//	HSTRACE(eGame, "MSG_RemoveMessenger \n");

	short	iTotalSize = sizeof( MSG_RemoveMessenger );
	pData->wType	= _MSG_RemoveMessenger;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//	**  Status  **  /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//	�ɸ����� �������������� �˸���.
HTRESULT TNNetworkManager::RequestCharPing()
{
	PS_CSP_CHAR_PING pData = HT_NULL;
	pData = new S_CSP_CHAR_PING;

//	HSTRACE(eGame, "RequestCharPing \n");

	short	iTotalSize = sizeof( S_CSP_CHAR_PING );
	pData->wType	= CSP_CHAR_PING;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	HT_DELETE( pData );

	return HT_OK;
}

//	�ɸ����� ���ӻ��� �� ��ġ�� Ȯ���Ѵ�.
HTRESULT TNNetworkManager::RequestReqCharLocation( S_GCSP_REQ_CHARACTER_SEARCH* pData )
{
//	HSTRACE(eGame, "RequestReqCharacterSearch\n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_GCSP_REQ_CHARACTER_SEARCH );
	pData->wType	= GCSP_REQ_CHARACTER_SEARCH;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//	**  Status  **  /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//	��ų �ʱ�ȭ�� ��û��
HTRESULT TNNetworkManager::RequestInitSkill( MSG_InitSkill* pData )
{
	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_InitSkill );
	pData->wType	= _MSG_InitSkill;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	ĳ������ ��ų Level-Up�� ����.
HTRESULT TNNetworkManager::RequestSkillLevelUp( PS_CSP_REQ_SKILL_LEVEL_UP pData )
{
	//HSTRACE(eGame, "RequestSkillLevelUp \n");

	//short	iTotalSize;
	//BYTE*		pTempPacket = NULL , *pPacket = NULL;

	//pTempPacket = pPacket = GetMsgResouce( sizeof( S_CSP_REQ_SKILL_LEVEL_UP ), &iTotalSize );

	//m_ClientMsgComposer.MakeSkillLevelupMsg( pTempPacket, pData );

	//g_cCPSock.SendOneMessage( ( char * )pPacket, iTotalSize );

	//if( pPacket != NULL )
	//	free( pPacket );

	return HT_OK;
}

//	ĳ������ ��ų Learn�� ����.
HTRESULT TNNetworkManager::RequestSkillLearn( PS_CSP_REQ_LEARN_SKILL pData )
{
//	HSTRACE(eGame, "RequestSkillLearn \n");

	short	iTotalSize = sizeof( S_CSP_REQ_LEARN_SKILL );
	pData->wType	= CSP_REQ_LEARN_SKILL;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	ĳ������ ��ų Cast ����.
HTRESULT TNNetworkManager::RequestSkillCastUnitSkill( PS_CSP_CAST_UNIT_SKILL pData )
{
//	HSTRACE(eGame, "RequestSkillUnitSkill \n");
	//	�Լ� �� ��ŷ üũ
	//if( pData->snRes != -1 )
	//{
	//	for( HTint i=0 ; i<4 ; i++ )
	//	{
	//		m_dwUnitSkillPassTime[i] = m_dwUnitSkillPassTime[i+1];
	//	}
	//	m_dwUnitSkillPassTime[4] = timeGetTime();
	//}
	//if( abs(m_dwUnitSkillPassTime[4]-m_dwUnitSkillPassTime[0] ) < 1000 )
	//{
	//	this->DisConnect();
	//}
	//else
	{
		short	iTotalSize = sizeof( S_CSP_CAST_UNIT_SKILL );
		pData->wType	= CSP_CAST_UNIT_SKILL;
		pData->wSeq	= 0;		
		pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
		pData->wDummy = 0;
		pData->dwClientTick  = timeGetTime();

		g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );
	}

	return HT_OK;
}

//	ĳ������ ��ų Cast Area ����.
HTRESULT TNNetworkManager::RequestSkillCastAreaSkill( PS_CSP_CAST_AREA_SKILL pData )
{
	//	�Լ� �� ��ŷ üũ
	//if( pData->snRes != -1 )
	//{
	//	for( HTint i=0 ; i<4 ; i++ )
	//	{
	//		m_dwUnitSkillPassTime[i] = m_dwUnitSkillPassTime[i+1];
	//	}
	//	m_dwUnitSkillPassTime[4] = timeGetTime();
	//}
	//if( abs(m_dwUnitSkillPassTime[4]-m_dwUnitSkillPassTime[0] ) < 1000 )
	//{
	//	this->DisConnect();
	//} 
	//else
	{
		short	iTotalSize = sizeof( S_CSP_CAST_AREA_SKILL );
		pData->wType	= CSP_CAST_AREA_SKILL;
		pData->wSeq	= 0;		
		pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
		pData->wDummy = 0;
		pData->dwClientTick  = timeGetTime();

		g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );
	}

	return HT_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//	**  Item & Economy  **  /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
HTRESULT TNNetworkManager::RequestItemCash( Msg_Cash* pData )
{
//	HSTRACE(eGame, "RequestItemCash \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( Msg_Cash );

	pData->wType	= _Msg_Cash;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}


HTRESULT TNNetworkManager::RequestCharacterInitialize( Msg_NPCCommand* pData )
{
//	HSTRACE(eGame, "RequestCharInitialize \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( Msg_NPCCommand );

	pData->wType	= _Msg_NPCCommand;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

// ��ɼ� ����ȭ ������ ��û
HTRESULT TNNetworkManager::RequestChargeFunctionItem( Msg_Time* pData )
{
//	HSTRACE(eGame, "RequestChargeFunctionItem\n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( Msg_Time );

	pData->wType	= _Msg_Time;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

HTRESULT TNNetworkManager::RequestItemBuy( PS_CSP_REQ_ITEM_BUY pData )
{
//	HSTRACE(eGame, "RequestItemBuy \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_ITEM_BUY );

	pData->wType	= CSP_REQ_ITEM_BUY;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	������ ������ ��û��.
HTRESULT TNNetworkManager::RequestItemRepair( PS_CSP_REQ_ITEM_REPAIR pData )
{
//	HSTRACE(eGame, "RequestItemRepair \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_ITEM_REPAIR );

	pData->wType	= CSP_REQ_ITEM_REPAIR;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}


HTRESULT TNNetworkManager::RequestItemSell( PS_CSP_REQ_ITEM_SELL pData )
{
//	HSTRACE(eGame, "RequestItemSell \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_ITEM_SELL );

	pData->wType	= CSP_REQ_ITEM_SELL;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	������ ������ ��û
HTRESULT TNNetworkManager::RequestItemRefining(PS_CSP_REQ_ITEM_REFINING pData)
{
//	HSTRACE(eGame, "RequestItemRefining \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_ITEM_REFINING );
	pData->wType	= CSP_REQ_ITEM_REFINING;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	������ �峳�� ��û
HTRESULT TNNetworkManager::RequestItemOffering( MSG_ItemContribution* pData )
{
//	HSTRACE(eGame, "RequestItemOffering \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_ItemContribution );
	pData->wType	= _MSG_ItemContribution;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�峳 ������ ��ġ ��û
HTRESULT TNNetworkManager::RequestRefineScale( )
{
//	HSTRACE(eGame, "RequestRefineScale\n");

	short	iTotalSize = sizeof( MSG_RefineScale );

	MSG_RefineScale* pData = NULL;
	pData = new MSG_RefineScale;
	
	pData->wType	= _MSG_RefineScale;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	if( pData != NULL )
		delete pData;

	return HT_OK;
}

//	���� �峳�� ��û.
HTRESULT TNNetworkManager::RequestPranaContribution(PS_CSP_REQ_PRANA_CONTRIBUTION pData)
{
	//HSTRACE(eGame, "RequestPranaContribution \n");

	//short	iTotalSize;
	//BYTE*		pTempPacket = NULL , *pPacket = NULL;

	//pTempPacket = pPacket = GetMsgResouce( sizeof( S_CSP_REQ_PRANA_CONTRIBUTION ), &iTotalSize );

	//m_ClientMsgComposer.MakePranaContributionMsg( pTempPacket, pData );

	//g_cCPSock.SendOneMessage( ( char * )pPacket, iTotalSize );

	//if( pPacket != NULL )
	//	free( pPacket );

	return HT_OK;
}
// ���� �������� �� ��� ���
HTRESULT TNNetworkManager::RequestStore( MSG_MobStore* pData )
{
//	HSTRACE(eGame, "RequestStore \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_MobStore );
	pData->wType	= _MSG_MobStore;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

// ���� �������� �� ��� ��û
HTRESULT TNNetworkManager::RequestStoreBuy( MSG_MobStore_Buy* pData )
{
//	HSTRACE(eGame, "RequestStoreBuy \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_MobStore_Buy );
	pData->wType	= _MSG_MobStore_Buy;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

// ��� ���� ����Ī ��û
HTRESULT TNNetworkManager::RequestTimeMode( Msg_TimeMode* pData )
{
//	HSTRACE(eGame, "RequestTimeMode \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( Msg_TimeMode );
	pData->wType	= _Msg_TimeMode;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

// ============================
//
//			��Ź ���� 
//
// ============================
#define SendPacket(pData, oType)	{if( pData == NULL ) return HT_FAIL; short	iTotalSize = sizeof( oType ); pData->wType	= _##oType; pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ; pData->wDummy = 0; pData->dwClientTick  = timeGetTime(); g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize ); }


// ���� ��Ź ������ ����Ʈ�� ��û
HTRESULT TNNetworkManager::RequestMyRentalItemList( Msg_MyRentalItemList* pData )
{
	SendPacket(pData, Msg_MyRentalItemList);
	return HT_OK;
}

// Ư�� ��Ź������ �����۸���Ʈ ��û
HTRESULT TNNetworkManager::RequestRentalItemList( Msg_RentalItemList* pData )
{
	SendPacket(pData, Msg_RentalItemList);
	return HT_OK;
}

// �������� ��Ź��
HTRESULT TNNetworkManager::RequestRentalItemAdd( Msg_RentalItemAdd* pData )
{
	SendPacket(pData, Msg_RentalItemAdd);
	return HT_OK;
}

// ��Ź�� �������� ���
HTRESULT TNNetworkManager::RequestRentalItemCancel( Msg_RentalItemCancel* pData )
{
	SendPacket(pData, Msg_RentalItemCancel);
	return HT_OK;
}

// ����� ���� �� ã��
HTRESULT TNNetworkManager::RequestRentalGetMoney( Msg_RentalGetMoney* pData )
{
	SendPacket(pData, Msg_RentalGetMoney);
	return HT_OK;
}

// ����� �� ��ǰ ã�� (�Ⱓ ���� �����۵�)
HTRESULT TNNetworkManager::RequestRentalGetItem( Msg_RentalGetItem* pData )
{
	SendPacket(pData, Msg_RentalGetItem);
	return HT_OK;
}

// ��Ź������ ���� ����
HTRESULT TNNetworkManager::RequestRentalTex( Msg_SetRentalTex* pData )
{
	SendPacket(pData, Msg_SetRentalTex);
	return HT_OK;
}

// ��Ź���� ���ְ� �ݱ�
HTRESULT TNNetworkManager::RequestRentalStoreClose( Msg_RentalStoreClose* pData )
{
	SendPacket(pData, Msg_RentalStoreClose);
	return HT_OK;
}

// ��Ź�������� ������ ����
HTRESULT TNNetworkManager::RequestRentalItemBuy( Msg_RentalItemBuy* pData )
{
	SendPacket(pData, Msg_RentalItemBuy);
	return HT_OK;
}

// ������ �������۸���Ʈ�� ��û�Ѵ�.
HTRESULT TNNetworkManager::RequestRentalStockItemList( Msg_RentalStockItemList* pData )
{
	SendPacket(pData, Msg_RentalStockItemList);
	return HT_OK;
}
/*
// ������ ���������� ��û�Ѵ�.
HTRESULT TNNetworkManager::RequestRentalStockItem( Msg_RentalStockItem* pData )
{
	SendPacket(pData, Msg_RentalStockItem);
	return HT_OK;
}
*/


/////////////////////////////////////////////////////////////////////////////////
//	**  Parameter  **  //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//	��ũ�� ����Ʈ ����� ��û
HTRESULT TNNetworkManager::RequestIncreaseChakra(PS_CSP_REQ_INCREASE_CHAKRA pData)
{
//	HSTRACE(eGame, "ReqIncreaseChakra\n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_INCREASE_CHAKRA );

	pData->wType	= CSP_REQ_INCREASE_CHAKRA;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ֽż��� ��û
HTRESULT TNNetworkManager::RequestSelectTrimuriti( MSG_TrimuritySelect* pData, BYTE byType )
{
//	HSTRACE(eGame, "ReqSelectTrimuriti\n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_TrimuritySelect );

	pData->wType	= _MSG_TrimuritySelect;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ֽ�����Ʈ Ȯ�� ��û
HTRESULT TNNetworkManager::RequestBrahmanPointRising( )
{
//	HSTRACE(eGame, "ReqRisingBrahmanPoint\n");

	short	iTotalSize = sizeof( MSG_TrimurityPoint );

	MSG_TrimurityPoint* pData = NULL;
	pData = new MSG_TrimurityPoint;
	
	pData->wType	= _MSG_TrimurityPoint;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	if( pData != NULL )
		delete pData;

	return HT_OK;
}

// ��ġ ���� ��û
HTRESULT TNNetworkManager::ReqSavePosition(int iNPCID )
{
//	HSTRACE(eGame, "ReqSavePosition\n");

	short	iTotalSize = sizeof( S_REQUEST );

	PS_REQUEST pData = NULL;
	pData = new S_REQUEST;
	
	pData->wType	= CSP_REQ_SAVE_POSITION;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE;
	pData->wDummy = iNPCID;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	if( pData != NULL )
		delete pData;

	return HT_OK;
}

// ���� ��û
HTRESULT TNNetworkManager::ReqChangeJob( MSG_CLASS* pData )
{
//	HSTRACE(eGame, "ReqChangeJob\n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_CLASS );

	pData->wType	= _MSG_CLASS;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//	**  Exchange  **  ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
// ��ȯ��û/������ �߰� ��û/���
HTRESULT TNNetworkManager::RequestExchange( PS_CSP_REQ_TRADE pData)
{
//	HSTRACE(eGame, "RequestExchange \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_TRADE );

	pData->wType	= CSP_REQ_TRADE;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

// ��ȯ ���
HTRESULT TNNetworkManager::RequestTradeCancel( )
{
//	HSTRACE(eGame, "RequestTradeCancel \n");

	PS_REQUEST pData = NULL;
	pData = new S_REQUEST;
	
	pData->wType	= CSP_REQ_TRADE_CANCEL;
	pData->wSeq	= 0;		
	pData->wPDULength	= sizeof( S_REQUEST ) - TNMSG_HEADER_SIZE;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, sizeof( S_REQUEST ) );

	if( pData != NULL )
		delete pData;

	return HT_OK;
}

// ���ο� "/Ż��"
HTRESULT
TNNetworkManager::RequestEscape()
{
	static S_REQUEST oRequest;
	oRequest.wType = _Msg_Escape;
	oRequest.wSeq	= 0;		
	oRequest.wPDULength	= sizeof( S_REQUEST ) - TNMSG_HEADER_SIZE;
	oRequest.wDummy = 0;
	oRequest.dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( (char*)(&oRequest), sizeof( S_REQUEST ) );
	return HT_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//	**  Quest  **  //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//	Ŭ���̾�Ʈ ȭ�鿡 NPC ��ȭ�� ǥ���Ѵ�.
HTRESULT TNNetworkManager::RequestQuestDialog( PS_CSP_QUEST_DIALOG pData)
{
//	HSTRACE(eGame, "RequestQuestDialog \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_QUEST_DIALOG );

	pData->wType	= CSP_QUEST_DIALOG;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	����Ʈ ���� ���¸� �˸���
HTRESULT TNNetworkManager::RequestQuestNotifyLevel( PS_CSP_QUEST_NOTIFY_LEVEL pData )
{
//	HSTRACE(eGame, "RequestQuestNotifyLevel \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_QUEST_NOTIFY_LEVEL );

	pData->wType	= CSP_QUEST_NOTIFY_LEVEL;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

// �׽�ũ ����Ʈ ���� ��û
HTRESULT TNNetworkManager::RequestTaskQuest( MSG_STANDARDPARM* pData )
{
//	HSTRACE(eGame, "RequestTaskQuest \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_STANDARDPARM );

	pData->wType	= _MSG_Quest;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//	**  GM  **  /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//	GM�� �����带 ���� �Ǵ� ������ ��û.
HTRESULT TNNetworkManager::RequestGMMode(MSG_GMMode* pData)
{
//	HSTRACE(eGame, "RequestGMMode \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_GMMode );

	pData->wType	= _MSG_GMMode;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Ư����ġ���� ������ ��û.(��������)
HTRESULT TNNetworkManager::RequestGMMovePosition(MSG_GMMovePosition* pData)
{
//	HSTRACE(eGame, "RequestGMMovePosition \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_GMMovePosition );

	pData->wType	= _MSG_GMMovePosition;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Ư���ɸ��� ��ó���� ������ ��û.
HTRESULT TNNetworkManager::RequestGMMoveNearChar(MSG_GMMoveToPlayer* pData)
{
//	HSTRACE(eGame, "RequestGMMoveToPlayer \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_GMMoveToPlayer );

	pData->wType	= _MSG_GMMoveToPlayer;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Ư���ɸ��͸� GM ��ó�� ���� ��û�Ѵ�
HTRESULT TNNetworkManager::RequesCharRecall(PS_CSP_REQ_CHAR_RECALL pData)
{
	//HSTRACE(eGame, "RequesCharRecall \n");

	//short	iTotalSize;
	//BYTE*		pTempPacket = NULL , *pPacket = NULL;

	//pTempPacket = pPacket = GetMsgResouce( sizeof(S_CSP_REQ_CHAR_RECALL), &iTotalSize );

	//m_ClientMsgComposer.MakeCharRecallMsg( pTempPacket, pData );

	//g_cCPSock.SendOneMessage( ( char * )pPacket, iTotalSize );

	//if( pPacket != NULL )
	//	free( pPacket );

	return HT_OK;
}

//	ä�û���� ����, ���� ��û.
HTRESULT TNNetworkManager::RuquestControlChat(PS_CSP_REQ_CONTROL_CHAT pData)
{
	//HSTRACE(eGame, "RuquestControlChat \n");

	//short	iTotalSize;
	//BYTE*		pTempPacket = NULL , *pPacket = NULL;

	//pTempPacket = pPacket = GetMsgResouce( sizeof(S_CSP_REQ_CONTROL_CHAT), &iTotalSize );

	//m_ClientMsgComposer.MakeControlChatMsg( pTempPacket, pData );

	//g_cCPSock.SendOneMessage( ( char * )pPacket, iTotalSize );

	//if( pPacket != NULL )
	//	free( pPacket );

	return HT_OK;
}

//	Ư���ɸ����� ���۸����� ��û�Ѵ�.
HTRESULT TNNetworkManager::RuquestControlAction(PS_CSP_REQ_CONTROL_ACTION pData)
{
	//HSTRACE(eGame, "RuquestControlAction \n");

	//short	iTotalSize;
	//BYTE*		pTempPacket = NULL , *pPacket = NULL;

	//pTempPacket = pPacket = GetMsgResouce( sizeof(S_CSP_REQ_CONTROL_ACTION), &iTotalSize );

	//m_ClientMsgComposer.MakeControlActionMsg( pTempPacket, pData );

	//g_cCPSock.SendOneMessage( ( char * )pPacket, iTotalSize );

	//if( pPacket != NULL )
	//	free( pPacket );

	return HT_OK;
}

//	Ư���ɸ����� ������ ��û�Ѵ�.(�⺻����, ��������, ��ų)
HTRESULT TNNetworkManager::RuquestCharacterInfo(PS_CSP_REQ_CHAR_INFO pData)
{
	//HSTRACE(eGame, "RuquestCharacterInfo \n");

	//short	iTotalSize;
	//BYTE*		pTempPacket = NULL , *pPacket = NULL;

	//pTempPacket = pPacket = GetMsgResouce( sizeof(S_CSP_REQ_CHAR_INFO), &iTotalSize );

	//m_ClientMsgComposer.MakeCharacterInfoMsg( pTempPacket, pData );

	//g_cCPSock.SendOneMessage( ( char * )pPacket, iTotalSize );

	//if( pPacket != NULL )
	//	free( pPacket );

	return HT_OK;
}

//	Ư���ɸ����� �������Ḧ ��û�Ѵ�.
HTRESULT TNNetworkManager::RuquestCloseCharacter(MSG_GMKickPlayer* pData)
{
	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_GMKickPlayer );

	pData->wType	= _MSG_GMKickPlayer;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�������
HTRESULT TNNetworkManager::RuquestAppealChat(PS_CSP_REQ_APPEAL_CHAT pData)
{
//	HSTRACE(eGame, "ReqestAppealChat \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( S_CSP_REQ_APPEAL_CHAT );

	pData->wType	= CSP_REQ_APPEAL_CHAT;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}


/////////////////////////////////////////////////////////////////////////////////
// Clear queued data
/////////////////////////////////////////////////////////////////////////////////
bool TNNetworkManager::ClearQueue(void)
{
	for(int i=0; i<g_pNetMsg->GetCount(); ++i)
	{
		BYTE* pData = (BYTE*)g_pNetMsg->GetData();
		HeapFree(GetProcessHeap(), 0, pData);
		g_pNetMsg->DelData();
	}

	return false;
}

// Guild
HTRESULT TNNetworkManager::ReqestGuildCreateMsg(MSG_CreateGuild* pData)
{
//	HSTRACE(eGame, "ReqestGuildCreateMsg \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_CreateGuild );

	pData->wType	= _MSG_CreateGuild;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

HTRESULT TNNetworkManager::ReqestGuildDisbandMsg(MSG_RemoveGuildMember* pData)
{
//	HSTRACE(eGame, "ReqestGuildDisbandMsg \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_RemoveGuildMember );

	pData->wType	= _MSG_RemoveGuildMember;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

HTRESULT TNNetworkManager::ReqestGuildJoinMsg( MSG_REQGuild* pData )
{
//	HSTRACE(eGame, "RequestGuildJoinMsg \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_REQGuild );

	pData->wType	= _MSG_REQGuild;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );
	
	return HT_OK;
}

HTRESULT TNNetworkManager::ReqestGuildCNFGuild( MSG_CNFGuild* pData )
{
//	HSTRACE(eGame, "RequestGuildCNFGuild \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_CNFGuild );

	pData->wType	= _MSG_CNFGuild;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	��帶ũ ������ ��û
HTRESULT TNNetworkManager::ReqestGuildMarkCreateMsg( MSG_GuildUpdateMark* pData )
{
//	HSTRACE(eGame, "MSG_GuildUpdateMark \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_GuildUpdateMark );

	pData->wType	= _MSG_GuildUpdateMark;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�����������
HTRESULT TNNetworkManager::ReqestGuildUpdateMsg( MSG_GuildUpdate* pData )
{
//	HSTRACE(eGame, "MSG_GuildUpdate \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_GuildUpdate );

	pData->wType	= _MSG_GuildUpdate;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	��� ���� ����
HTRESULT TNNetworkManager::ReqestGuildSetRanking( MSG_GuildSetRanking* pData )
{
//	HSTRACE(eGame, "MSG_GuildSetRanking \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_GuildSetRanking );

	pData->wType	= _MSG_GuildSetRanking;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	���� �ֽ� NPC�� Ŭ��������
HTRESULT TNNetworkManager::ReqestMsgContactNpc( MSG_CONTACT_NPC* pData )
{
//	HSTRACE(eGame, "MSG_Contact_NPC \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_CONTACT_NPC );

	pData->wType	= CONTACT_NPC;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�̿��
HTRESULT TNNetworkManager::RequestMsgBeauty( MSG_Beauty* pData )
{
//	HSTRACE(eGame, "MSG_Beauty \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_Beauty );

	pData->wType	= _MSG_Beauty;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Challenger
HTRESULT TNNetworkManager::RequestMsgChallenger( Msg_Challenger* pData )
{
//	HSTRACE(eGame, "MSG_Challenger \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( Msg_Challenger );

	pData->wType	= _Msg_Challenger;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	�ƽ�������
HTRESULT TNNetworkManager::RequestMsgAshuramGuild( Msg_GuildAlliance* pData )
{
//	HSTRACE(eGame, "MSG_Challenger \n");

	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( Msg_GuildAlliance );

	pData->wType	= _Msg_GuildAlliance;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Assist Change Target
HTRESULT TNNetworkManager::RequestMsgChangeTarget( MSG_CHANGE_TARGET* pData )
{
	if( pData == NULL )
		return HT_FAIL;

	short	iTotalSize = sizeof( MSG_CHANGE_TARGET );

	pData->wType	= _MSG_CHANGE_TARGET;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Coupon Event
HTRESULT TNNetworkManager::RequestMsgCouponEvent(Msg_GameEvent* pData)
{
//	HSTRACE(eGame, "ReqNotifyMessage \n");

	short	iTotalSize = sizeof( Msg_GameEvent );
	pData->wType	= _Msg_GameEvent;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Echo
HTRESULT TNNetworkManager::RequestMsgEcho( Msg_Echo* pData )
{
	short	iTotalSize = sizeof( Msg_Echo );
	pData->wType	= _Msg_Echo;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Pat Command
HTRESULT TNNetworkManager::RequestMsgPatCommand( MSG_PET_COMMAND* pData )
{
	short	iTotalSize = sizeof( MSG_PET_COMMAND );
	pData->wType	= MSG_PET_COMMAND_ID;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Msg_YutMyMoney
HTRESULT TNNetworkManager::RequestMsgYutMyMoney( Msg_YutMyMoney* pData )
{
	short	iTotalSize = sizeof( Msg_YutMyMoney );
	pData->wType	= _Msg_YutMyMoney;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Msg_YutStatus
HTRESULT TNNetworkManager::RequestMsgYutStatus( Msg_YutStatus* pData )
{
	short	iTotalSize = sizeof( Msg_YutStatus );
	pData->wType	= _Msg_YutStatus;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Msg_YutBet
HTRESULT TNNetworkManager::RequestMsgYutBet( Msg_YutBet* pData )
{
	short	iTotalSize = sizeof( Msg_YutBet );
	pData->wType	= _Msg_YutBet;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Msg_YutMoney
HTRESULT TNNetworkManager::RequestMsgYutGetMoney( Msg_YutGetMoney* pData )
{
	short	iTotalSize = sizeof( Msg_YutGetMoney );

	pData->wType	= _Msg_YutGetMoney;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Siege
//	State_of_the_siege
HTRESULT TNNetworkManager::RequestMsgStateOfSiege( MSG_STATE_OF_THE_SIEGE* pData )
{
	short	iTotalSize = sizeof( MSG_STATE_OF_THE_SIEGE );

	pData->wType	= MSG_STATE_OF_THE_SIEGE_ID;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}
//	State_Apply_Siege
HTRESULT TNNetworkManager::RequestMsgApplySiege( MSG_APPLY_SIEGE* pData )
{
	short	iTotalSize = sizeof( MSG_APPLY_SIEGE );

	pData->wType	= MSG_APPLY_SIEGE_ID;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}
//	Check Siege Entry
HTRESULT TNNetworkManager::RequestMsgCheckSiegeEntry( MSG_CHECK_SIEGE_ENTRY* pData )
{
	short	iTotalSize = sizeof( MSG_CHECK_SIEGE_ENTRY );

	pData->wType	= MSG_CHECK_SIEGE_ENTRY_ID;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}
//	Check Siege Entry
HTRESULT TNNetworkManager::RequestMsgStateOfTheSiege( MSG_STATE_OF_THE_SIEGE* pData )
{
	short	iTotalSize = sizeof( MSG_STATE_OF_THE_SIEGE );

	pData->wType	= MSG_STATE_OF_THE_SIEGE_ID;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}
//	MSG_FIX_DATE_OF_SIEGE 
HTRESULT TNNetworkManager::RequestMsgFixDataOfSiege( MSG_FIX_DATE_OF_SIEGE* pData )
{
	short	iTotalSize = sizeof( MSG_FIX_DATE_OF_SIEGE );

	pData->wType	= MSG_FIX_DATE_OF_SIEGE_ID;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}
//	Msg_SetSalesRate
HTRESULT TNNetworkManager::RequestMsgSetSalesRate( Msg_SetSalesRate* pData )
{
	short	iTotalSize = sizeof( Msg_SetSalesRate );

	pData->wType	= _Msg_SetSalesRate;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

    return HT_OK;
}
//	Msg_GetMoney
HTRESULT TNNetworkManager::RequestMsgGetMoney( Msg_GetMoney* pData )
{
	short	iTotalSize = sizeof( Msg_GetMoney );

	pData->wType	= _Msg_GetMoney;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}

//	Ashram Cargo
//	Msg_GuildCargoUsingLevel
HTRESULT TNNetworkManager::RequestGuildCargoUsingLevel( Msg_GuildCargoUsingLevel* pData )
{
	short	iTotalSize = sizeof( Msg_GuildCargoUsingLevel );

	pData->wType	= _Msg_GuildCargoUsingLevel;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}
//	Msg_GuildCargoTimeExtension
HTRESULT TNNetworkManager::RequestGuildCargoTimeExtension( Msg_GuildCargoTimeExtension* pData )
{
	short	iTotalSize = sizeof( Msg_GuildCargoTimeExtension );

	pData->wType	= _Msg_GuildCargoTimeExtension;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}
//	Msg_GuildItem
HTRESULT TNNetworkManager::RequestGuildItem( Msg_GuildItem* pData )
{
	short	iTotalSize = sizeof( Msg_GuildItem );

	pData->wType	= _Msg_GuildItem;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}
// Who are you? - BOT check.
HTRESULT TNNetworkManager::RequestWhoMessage( Msg_Who *pData )
{
	short	iTotalSize = sizeof( Msg_Who );
	pData->wType = _Msg_Who;
	pData->wSeq = 0;
	pData->wPDULength = iTotalSize - TNMSG_HEADER_SIZE;
	pData->wDummy = 0;
	pData->dwClientTick = timeGetTime();
	//pData->
	//pData->byteLevel=0;
	//pData->skillid=0;
	memcpy( pData->pszPassword, g_cCPSock.m_pszWho, 128 );

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );
	ZeroMemory( g_cCPSock.m_pszWho, sizeof(g_cCPSock.m_pszWho) );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send Who Message" );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	

	return HT_OK;
}
//	Reply Quiz
HTRESULT TNNetworkManager::ReplyQuiz( Msg_QuizResponse* pData )
{
	short	iTotalSize = sizeof( Msg_QuizResponse );

	pData->wType	= _Msg_QuizResponse;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	return HT_OK;
}
