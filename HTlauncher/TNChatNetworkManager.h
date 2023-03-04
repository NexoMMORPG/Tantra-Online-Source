//----------------------------------------------------------------------------//
//	���� �̸�	: TNChatNetworkManager.h
//
//	���� ���� 	: 
//		- ä�� �������� ������ ���� Ŭ����
//
//	�ۼ���		:
//		- 2005/12/19, Created by Ahn sung hoi
//
//  Copyright (c) 2000-2005 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//

#ifndef __TNCHATNETWORKMANAGER_H_INCLUDE__
#define __TNCHATNETWORKMANAGER_H_INCLUDE__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseDef.h"

class TNChatNetworkManager
{
public:
	TNChatNetworkManager();
	~TNChatNetworkManager();

	//	**	�α��� �׷�  **  ////////////////////////////////////////////////////////		

	HTRESULT RequestMsgChat( MSG_Chat* pData );										// ä�� �޽���
	HTRESULT RequestMsgAccountLogin( Msg_AccountLogin* pData );						// ä�ù� �α��� �Լ�
	HTRESULT RequestMsgChatRoomListRequest( );										// ä�ù渮��Ʈ ��û �Լ�
	HTRESULT RequestMsgChatRoomCreate( Msg_ChatRoomCreate* pData );					// ä�ù� ���� ��û
	HTRESULT RequestMsgChatRoomJoin( Msg_ChatRoomJoin* pData );						// �ش� ä�ù� ���� ��û
	HTRESULT RequestMsgChatRoomGoout( Msg_ChatRoomGoout* pData );					// ������ ä�ù����� ���� ����
	HTRESULT RequestMsgChatWaitingListRequest( Msg_ChatWaitingListRequest* pData);	// ä�ù� ����� ��û
	HTRESULT RequestMsgChatRoomInvite( Msg_ChatRoomInvite* pData);					// ä�ù� �ʴ� ��û
	HTRESULT RequestMsgChatRoomUpdate( Msg_ChatRoomUpdate* pData);					// ä�ù� ���� ��û
	HTRESULT RequestMsgChatRoomOrder( Msg_ChatRoomOrder* pData);					// ä�ù� ���� ��û

	bool InitNetworkManager(void);
	HTint DisConnect(void);													//	Network Disconnect Function
	HTint Connect(char *a_pstrServerIP, short a_nPortNum);					//	Network Connect Function
	WORD GetConnectingState();												//  Get State of the connecting server
};

#endif // __TNCHATNETWORKMANAGER_H_INCLUDE__