//----------------------------------------------------------------------------//
//	파일 이름	: TNChatNetworkManager.h
//
//	파일 설명 	: 
//		- 채팅 서버와의 연결을 위한 클래스
//
//	작성자		:
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

	//	**	로그인 그룹  **  ////////////////////////////////////////////////////////		

	HTRESULT RequestMsgChat( MSG_Chat* pData );										// 채팅 메시지
	HTRESULT RequestMsgAccountLogin( Msg_AccountLogin* pData );						// 채팅방 로그인 함수
	HTRESULT RequestMsgChatRoomListRequest( );										// 채팅방리스트 요청 함수
	HTRESULT RequestMsgChatRoomCreate( Msg_ChatRoomCreate* pData );					// 채팅방 생성 요청
	HTRESULT RequestMsgChatRoomJoin( Msg_ChatRoomJoin* pData );						// 해당 채팅방 참여 요청
	HTRESULT RequestMsgChatRoomGoout( Msg_ChatRoomGoout* pData );					// 참여한 채팅방으로 부터 나감
	HTRESULT RequestMsgChatWaitingListRequest( Msg_ChatWaitingListRequest* pData);	// 채팅방 대기자 요청
	HTRESULT RequestMsgChatRoomInvite( Msg_ChatRoomInvite* pData);					// 채팅방 초대 요청
	HTRESULT RequestMsgChatRoomUpdate( Msg_ChatRoomUpdate* pData);					// 채팅방 변경 요청
	HTRESULT RequestMsgChatRoomOrder( Msg_ChatRoomOrder* pData);					// 채팅방 강퇴 요청

	bool InitNetworkManager(void);
	HTint DisConnect(void);													//	Network Disconnect Function
	HTint Connect(char *a_pstrServerIP, short a_nPortNum);					//	Network Connect Function
	WORD GetConnectingState();												//  Get State of the connecting server
};

#endif // __TNCHATNETWORKMANAGER_H_INCLUDE__