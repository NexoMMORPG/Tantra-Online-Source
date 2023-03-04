//
// ä�ù� �ý���
//
// 2005. 12. 21 : ������ (grecia79@hanbitsoft.co.kr)
//

#include "stdafx.h"
#include "TNChatNetworkManager.h"
#include "HTextern.h"

#define SendPacket(pData, oType)	{if( pData == NULL ) return HT_FAIL; short	iTotalSize = sizeof( oType ); pData->wType	= _##oType; pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE ; pData->wDummy = 0; pData->dwClientTick  = timeGetTime(); g_cChatCPSock.SendOneMessage( ( char * )pData, iTotalSize ); }

TNChatNetworkManager::TNChatNetworkManager()
{
}

TNChatNetworkManager::~TNChatNetworkManager()
{
}

bool TNChatNetworkManager::InitNetworkManager(void)
{
	return true;
}

WORD TNChatNetworkManager::GetConnectingState()
{
	if( g_cChatCPSock.Sock != 0 )
		return STATUS_ALIVE;
	else
		return STATUS_DISCONNECT;
}

////////////////////////////////////////////////////////////////////////////////////////
//	Network Connect Function	_2005. 12. 21
////////////////////////////////////////////////////////////////////////////////////////
HTint TNChatNetworkManager::Connect( char *a_pstrServerIP, short a_nPortNum)
{
	//	CHTString str;
	//	str.HT_szFormat("Connect %s:%d",a_pstrServerIP, a_nPortNum);
	//	MessageBox(NULL, str, "DEBUG", MB_OK);

	if( g_cChatCPSock.ConnectServer( a_pstrServerIP, a_nPortNum, INADDR_ANY, WSA_READ + 1, g_hWnd ) == 0 )
		return 0;
	else
		return 1;
}


////////////////////////////////////////////////////////////////////////////////////////
//	Network DisConnect Function	_2005. 12. 21
////////////////////////////////////////////////////////////////////////////////////////
HTint TNChatNetworkManager::DisConnect()
{
	g_cChatCPSock.CloseSocket();

	return 0;
}

/////////////////////////////////
//
//	ä�ù� �ý��� 2005. 12. 21 //
//
/////////////////////////////////

// �α��� ��û
HTRESULT TNChatNetworkManager::RequestMsgChat( MSG_Chat* pData )
{
	SendPacket(pData, MSG_Chat);
	return HT_OK;
}

// �α��� ��û
HTRESULT TNChatNetworkManager::RequestMsgAccountLogin( Msg_AccountLogin* pData )
{
	SendPacket(pData, Msg_AccountLogin);
	return HT_OK;
}

// ä�ù渮��Ʈ ��û
HTRESULT TNChatNetworkManager::RequestMsgChatRoomListRequest( )
{
	short	iTotalSize = sizeof( S_REQUEST );

	PS_REQUEST pData = NULL;
	pData = new S_REQUEST;
	
	pData->wType	= _Msg_ChatRoomListRequest;
	pData->wSeq	= 0;		
	pData->wPDULength	= iTotalSize - TNMSG_HEADER_SIZE;
	pData->wDummy = 0;
	pData->dwClientTick  = timeGetTime();

	g_cChatCPSock.SendOneMessage( ( char * )pData, iTotalSize );

	if( pData != NULL ) delete pData;

	return HT_OK;
}

// ä�ù� ���� ��û
HTRESULT TNChatNetworkManager::RequestMsgChatRoomCreate( Msg_ChatRoomCreate* pData)
{
	SendPacket(pData, Msg_ChatRoomCreate);
	return HT_OK;
}

// �ش� ä�ù� ���� ��û
HTRESULT TNChatNetworkManager::RequestMsgChatRoomJoin( Msg_ChatRoomJoin* pData )
{
	SendPacket(pData, Msg_ChatRoomJoin);
	return HT_OK;
}

// ������ ä�ù����� ���� ����
HTRESULT TNChatNetworkManager::RequestMsgChatRoomGoout( Msg_ChatRoomGoout* pData )
{
	SendPacket(pData, Msg_ChatRoomGoout);
	return HT_OK;
}

// ä�ù� ����� ��û
HTRESULT TNChatNetworkManager::RequestMsgChatWaitingListRequest( Msg_ChatWaitingListRequest *pData )
{
	SendPacket(pData, Msg_ChatWaitingListRequest);
	return HT_OK;
}

// ä�ù� �ʴ� ��û
HTRESULT TNChatNetworkManager::RequestMsgChatRoomInvite( Msg_ChatRoomInvite* pData)
{
	SendPacket(pData, Msg_ChatRoomInvite);
	return HT_OK;
}

// ä�ù� ���� ��û
HTRESULT TNChatNetworkManager::RequestMsgChatRoomUpdate( Msg_ChatRoomUpdate* pData)
{
	SendPacket(pData, Msg_ChatRoomUpdate);
	return HT_OK;
}

// ä�ù� ���� ��û
HTRESULT TNChatNetworkManager::RequestMsgChatRoomOrder( Msg_ChatRoomOrder* pData)
{
	SendPacket(pData, Msg_ChatRoomOrder);
	return HT_OK;
}