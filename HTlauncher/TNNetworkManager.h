//----------------------------------------------------------------------------//
//	파일 이름	: TNNetworkManager.h
//
//	파일 설명 	: 
//		- 게임에서 사용하게 될 네트워크들을 다루는 클레스.
//
//	작성자		:
//		- 2002/08/01, Created by Youn woo Kyoung
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//

#if !defined(AFX_TNNETWORKMANAGER_H__8E94DA55_857C_4C11_A829_C9759F895F3B__INCLUDED_)
#define AFX_TNNETWORKMANAGER_H__8E94DA55_857C_4C11_A829_C9759F895F3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef  BYTE*	PPACKET;
#define  PTOBYTE(address)	*(BYTE*)(address);
#define  PTOint(address)	*(int*)(address);

#include "Basedef.h"

class TNNetworkManager//: public TNINetCallback // Interface 상속
{
public:
	// Construction/Destruction
	TNNetworkManager();
	~TNNetworkManager();

	//	**	로그인 그룹  **  ////////////////////////////////////////////////////////		

	//	월드 대표 존서버에 접속을 요청함.
	HTRESULT RequestReqMoveZoneServer(PS_CSP_REQ_MOVE_ZONE_SERVER pData);

	//	케릭터의 리스트를 요청함.
	HTRESULT RequestCharList();

	//	케릭터 생성을 요청함.
	HTRESULT RequestCharCreation(PS_CSP_REQ_CHAR_CREATE pData);

	//	케릭터 삭제를 요청함.
	HTRESULT RequestCharDeletion(PS_CSP_REQ_CHAR_REMOVE pData);

	//	케릭터 접속을 요청함.	
	HTRESULT RequestReqCharSelect(PS_CSP_REQ_CHAR_SELECT pData);

	//	**  Initialize 그룹	 **  ////////////////////////////////////////////////////
	//	케릭터 초기 데이터를 요청.
	HTRESULT RequestInitChar(PS_CSP_REQ_CHAR_INIT pData);

	//	다른오브젝트의 이닛을 요청함
	HTRESULT RequestInitMobByID( MSG_REQMobByID* pData );


	//	캐릭터 죽고, Regen 초기화 요청
	HTRESULT RequestReqInitRegenChar(PS_CSP_REQ_INIT_REGEN_CHAR pData);

	//	**	Moving, Packing/UnPacking, Using **  ////////////////////////////////////

	//	캐릭터가 앉을때와 설때 서버에 보냄
	HTRESULT RequestCharAct(PS_CSP_REQ_CHAR_ACT pData);

	//	아이템 이동결과
	HTRESULT RequestItemMove(PS_CSP_REQ_ITEM_MOVE pData);

	// 맵 위에 아이템 떨어뜨리기
	HTRESULT RequestItemDrop(_S_CSP_REQ_ITEM_DROP* pData);

	// 맵위의 아이템 줍기
	HTRESULT RequestItemGet(_S_CSP_REQ_ITEM_GET* pData);

	//	아이템 패킹을 요청함.
	//HTRESULT RequestItemPacking(PS_CSP_REQ_ITEM_PACKING pData);
	HTRESULT RequestItemPacking( MSG_Packing* pData );

	//	아이템 사용을 요청함.
	HTRESULT RequestItemUse(MSG_ITEM* pData);

	//	루피아의 이동을 요청함.
	HTRESULT RequestMoneyMove( MSG_Money_Move* pData );

	//	케릭터의 이동을 요청함.
	HTRESULT RequestCharMoveBroadcast( PS_CSP_REQ_CHAR_MOVE_BROADCAST pData );

	//	케릭터의 이동을 요청함2.
	HTRESULT RequestMSG_Action( MSG_Action* pData );

	//	공격을 요청함
	HTRESULT RequestMSG_Attack( MSG_Attack* pData, HTint iMsgSize );

	//	포탈이동을 요청함.
	HTRESULT RequestReqMovePortal(PS_CSP_REQ_MOVE_PORTAL pData);

	//	칼라코어 등록을 요청함
	HTRESULT RequestReqRegisterKalaCore(MSG_REGISTER_KALA_CORE* pData);

    //  **  Normal Combat  **  //////////////////////////////////////////////////////
	//	PK버튼 토글 메시지
	HTRESULT RequestPKToggleButton(MSG_TOGGLE_BUTTON* pData);

	//	**  Chatting  **  ///////////////////////////////////////////////////////////
	//	일반 채팅 처리를 알림.
	HTRESULT RequestReqNormalChat(PS_CSP_REQ_CHAT pData);

	//	귓속말 채팅 처리를 알림.
	HTRESULT RequestReqWhisperChat(PS_CSP_REQ_WHISPER_CHAT pData);

	//	파티 채팅을 알림.
	HTRESULT RequestGroupChat(MSG_Chat* pData);

	//	월드내 공지 채팅을 알림.
	HTRESULT ReqNotifyMessage(MSG_Broadcast* pData);

	//	**  Party/Guild/Address Book  **  ///////////////////////////////////////////
	//	파티 생성/가입을 요청함
	HTRESULT RequestReqCreateJoinParty(MSG_REQParty* pData);
	
	//	파티 가입요청에 대한 응답
	HTRESULT RequestReqCNFParty(MSG_CNFParty* pData);

	//	파티 탈퇴/해체 요청
	HTRESULT RequestReqRemoveParty(MSG_RemoveParty* pData);

	//	자동분배 모드 변경 요청
	HTRESULT RequestSetParty( MSG_SetParty* pData );
	
	//	주소록 등록을 요청함
	HTRESULT RequestJoinAddressBook(MSG_ReqMessenger* pData);

	//	주소록 첨부 요청에 대한 결과를 처리함
	HTRESULT RequestJoinAddressBookResult(MSG_CNFMessenger* pData);

	//	주소록에서 삭제를 요청함
	HTRESULT RequestReqAddressBookMemberDelete(MSG_RemoveMessenger* pData);
	

	//	**  Status  **  /////////////////////////////////////////////////////////////

	//	케릭터의 게임접속중임을 알린다.
	HTRESULT RequestCharPing();

	//	케릭터의 접속상태 및 위치를 확인한다.
	HTRESULT RequestReqCharLocation( S_GCSP_REQ_CHARACTER_SEARCH* pData );

	//	**  Parameter  **  /////////////////////////////////////////////////////////

	//	차크라 포인트 상승을 요청
	HTRESULT RequestIncreaseChakra(PS_CSP_REQ_INCREASE_CHAKRA pData);

	//	주신선택 요청
	HTRESULT RequestSelectTrimuriti( MSG_TrimuritySelect* pData, BYTE byType);
	
	//	주신포인트 확장 요청
	HTRESULT RequestBrahmanPointRising( );

	//	위치 저장을 요청한다.
	HTRESULT ReqSavePosition(int iNPCID = 0);

	// 전직을 요청한다.
	HTRESULT ReqChangeJob( MSG_CLASS* pData );

	//	**  Skill  **  /////////////////////////////////////////////////////////////
	//	스킬 초기화를 요청함
	HTRESULT RequestInitSkill( MSG_InitSkill* pData );

	//	캐릭터의 스킬 Level-Up을 전송.
	HTRESULT RequestSkillLevelUp( PS_CSP_REQ_SKILL_LEVEL_UP pData );

	//	캐릭터의 스킬 Learn을 전송.
	HTRESULT RequestSkillLearn( PS_CSP_REQ_LEARN_SKILL pData );

	//	캐릭터의 스킬 Cast Unit 전송.
	HTRESULT RequestSkillCastUnitSkill( PS_CSP_CAST_UNIT_SKILL pData );

	//	캐릭터의 스킬 Cast Area 전송.
	HTRESULT RequestSkillCastAreaSkill( PS_CSP_CAST_AREA_SKILL pData );

	//	**  Item & Economy  **  ///////////////////////////////////////////////////
	//  캐쉬 데이터 요청.
	HTRESULT RequestItemCash( Msg_Cash* pData );

	// 차크라/스킬 초기화 정보 요청 (2004. 8. 27)
	HTRESULT RequestCharacterInitialize(Msg_NPCCommand* pData );

	//	아이템 제작을 요청.
	HTRESULT RequestItemBuy( PS_CSP_REQ_ITEM_BUY pData );

	//	아이템 수리를 요청함.
	HTRESULT RequestItemRepair(PS_CSP_REQ_ITEM_REPAIR pData);

	//	아이템 해체를 요청.
	HTRESULT RequestItemSell( PS_CSP_REQ_ITEM_SELL pData );

	//	아이템 제련을 요청
	HTRESULT RequestItemRefining(PS_CSP_REQ_ITEM_REFINING pData);

	//	아이템 헌납 요청
	HTRESULT RequestItemOffering( MSG_ItemContribution* pData );

	//	헌납 게이지 수치 요청
	HTRESULT RequestRefineScale( );

	//	프라나 헌납을 요청.
	HTRESULT RequestPranaContribution(PS_CSP_REQ_PRANA_CONTRIBUTION pData);

	// 개인 상점 팔 목록 등록
	HTRESULT RequestStore( MSG_MobStore* pData );

	// 개인 상점에서 살 목록 요청
	HTRESULT RequestStoreBuy( MSG_MobStore_Buy* pData );

	// 사용내역 스위칭 요청
	HTRESULT RequestTimeMode( Msg_TimeMode* pData );

	// 기능성 유료화 아이템 신청
	HTRESULT RequestChargeFunctionItem( Msg_Time* pData );

	//	**  Rental Stroe  **  /////////////////////////////////////////////////////////
	HTRESULT RequestMyRentalItemList( Msg_MyRentalItemList* pData );		// 나의 위탁 아이템 리스트를 요청
	HTRESULT RequestRentalItemList( Msg_RentalItemList* pData );			// 특정 위탁상점의 아이템리스트 요청
	HTRESULT RequestRentalItemAdd( Msg_RentalItemAdd* pData );				// 아이템을 위탁함
	HTRESULT RequestRentalItemCancel( Msg_RentalItemCancel* pData );		// 위탁한 아이템을 취소
	HTRESULT RequestRentalGetMoney( Msg_RentalGetMoney* pData );			// 저장된 나의 돈 찾기
	HTRESULT RequestRentalGetItem( Msg_RentalGetItem* pData );				// 저장된 내 물품 찾기 (기간 지난 아이템들)
	HTRESULT RequestRentalTex( Msg_SetRentalTex* pData );						// 위탁상점의 세율 정함
	HTRESULT RequestRentalStoreClose( Msg_RentalStoreClose* pData );		// 위탁상점 성주가 닫기
	HTRESULT RequestRentalItemBuy( Msg_RentalItemBuy* pData );				// 위탁상점에서 아이템 구입
	//HTRESULT RequestRentalStockItem( Msg_RentalStockItem* pData );		// 서버에 재고아이템리스트를 요청한다.
	HTRESULT RequestRentalStockItemList( Msg_RentalStockItemList* pData );		// 서버에 재고아이템리스트를 요청한다.

	//	**  Exchange  **  /////////////////////////////////////////////////////////
	// 교환요청/아이템 추가 요청/결과
	HTRESULT RequestExchange( PS_CSP_REQ_TRADE pData);

	// 교환 취소
	HTRESULT RequestTradeCancel( );

	// 새로운 "/탈출"
	HTRESULT RequestEscape();
	

	//	**  Quest  **  /////////////////////////////////////////////////////////

	//	클라이언트 화면에 NPC 대화를 표시한다.
	HTRESULT RequestQuestDialog(PS_CSP_QUEST_DIALOG pData);

	//	퀘스트 진행 상태를 알린다
	HTRESULT RequestQuestNotifyLevel(PS_CSP_QUEST_NOTIFY_LEVEL pData);

	// 테스크 퀘스트 실행 요청
	HTRESULT RequestTaskQuest( MSG_STANDARDPARM* pData );

	//	**  GM  **  ///////////////////////////////////////////////////////////////
	//	GM의 모드를 설정 또는 해제를 요청.
	HTRESULT RequestGMMode(MSG_GMMode* pData);

	//	특정위치로의 워프를 요청.(동일존내)
	HTRESULT RequestGMMovePosition(MSG_GMMovePosition* pData);

	//	특정케릭터 근처로의 워프를 요청.
	HTRESULT RequestGMMoveNearChar(MSG_GMMoveToPlayer* pData);

	//	특정케릭터를 GM 근처로 워프 요청한다
	HTRESULT RequesCharRecall(PS_CSP_REQ_CHAR_RECALL pData);

	//	채팅사용의 금지, 해제 요청.
	HTRESULT RuquestControlChat(PS_CSP_REQ_CONTROL_CHAT pData);

	//	특정케릭터의 동작멈춤을 요청한다.
	HTRESULT RuquestControlAction(PS_CSP_REQ_CONTROL_ACTION pData);

	//	특정케릭터의 정보를 요청한다.(기본정보, 장착정보, 스킬)
	HTRESULT RuquestCharacterInfo(PS_CSP_REQ_CHAR_INFO pData);

	//	특정케릭터의 접속종료를 요청한다.
	HTRESULT RuquestCloseCharacter(MSG_GMKickPlayer* pData);

	//	진정기능
	HTRESULT RuquestAppealChat(PS_CSP_REQ_APPEAL_CHAT pData);

	//	**  GUILD  **  ///////////////////////////////////////////////////////////////

	//	길드 생성을 요청한다.
	HTRESULT ReqestGuildCreateMsg(MSG_CreateGuild* pData);

	//	길드해체를 요청한다.
	HTRESULT ReqestGuildDisbandMsg(MSG_RemoveGuildMember* pData);

	//	길드원 참여를 요청한다.
	HTRESULT ReqestGuildJoinMsg( MSG_REQGuild* pData );

	//	길드참여요청에 대한 응답메세지를 전송한다.
	HTRESULT ReqestGuildCNFGuild( MSG_CNFGuild* pData );

	//	길드마크 생성을 요청
	HTRESULT ReqestGuildMarkCreateMsg( MSG_GuildUpdateMark* );

	//	길드 업데이트 요청
	HTRESULT ReqestGuildUpdateMsg( MSG_GuildUpdate* );

	//	길드 직위 변경
	HTRESULT ReqestGuildSetRanking( MSG_GuildSetRanking* pData );

	// 아쉬람 연합
	HTRESULT RequestMsgAshuramGuild( Msg_GuildAlliance* pData );

	///////////////////////////////////////////////////////////////////////////////

	//	같은 주신 NPC를 클릭했을때
	HTRESULT ReqestMsgContactNpc( MSG_CONTACT_NPC* pData );

	//	미용실
	HTRESULT RequestMsgBeauty( MSG_Beauty* pData );

	//	Challenger
	HTRESULT RequestMsgChallenger( Msg_Challenger* pData );

	//	Assist Change Target
	HTRESULT RequestMsgChangeTarget( MSG_CHANGE_TARGET* pData );

	//	Coupon Event
	HTRESULT RequestMsgCouponEvent(Msg_GameEvent* pData);

	//	Echo
	HTRESULT RequestMsgEcho( Msg_Echo* pData );

	//	Pat Command
	HTRESULT RequestMsgPatCommand( MSG_PET_COMMAND* pData );

	//	Yut
	HTRESULT RequestMsgYutMyMoney( Msg_YutMyMoney* pData );
	HTRESULT RequestMsgYutStatus( Msg_YutStatus* pData );
	HTRESULT RequestMsgYutBet( Msg_YutBet* pData );
	HTRESULT RequestMsgYutGetMoney( Msg_YutGetMoney* pData );

	//	Siege
	//	State_of_the_siege
	HTRESULT RequestMsgStateOfSiege( MSG_STATE_OF_THE_SIEGE* pData );
	//	State_Apply_Siege
	HTRESULT RequestMsgApplySiege( MSG_APPLY_SIEGE* pData );
	//	Check Siege Entry
	HTRESULT RequestMsgCheckSiegeEntry( MSG_CHECK_SIEGE_ENTRY* pData );
	//	Check Siege Entry
	HTRESULT RequestMsgStateOfTheSiege( MSG_STATE_OF_THE_SIEGE* pData );
	//	MSG_FIX_DATE_OF_SIEGE 
	HTRESULT RequestMsgFixDataOfSiege( MSG_FIX_DATE_OF_SIEGE* pData );
	//	Msg_SetSalesRate
	HTRESULT RequestMsgSetSalesRate( Msg_SetSalesRate* pData );
	//	Msg_GetMoney
	HTRESULT RequestMsgGetMoney( Msg_GetMoney* pData );

	//	Ashram Cargo
	//	Msg_GuildCargoUsingLevel
	HTRESULT RequestGuildCargoUsingLevel( Msg_GuildCargoUsingLevel* pData );
	//	Msg_GuildCargoTimeExtension
	HTRESULT RequestGuildCargoTimeExtension( Msg_GuildCargoTimeExtension* pData );
	//	Msg_GuildItem
	HTRESULT RequestGuildItem( Msg_GuildItem* pData );

	// Who are you? - BOT check.
	HTRESULT RequestWhoMessage( Msg_Who *pData );

	//	Reply Quiz
	HTRESULT ReplyQuiz( Msg_QuizResponse* pData );


	///////////////////////////////////////////////////////////////////////////////
	bool InitNetworkManager(void);
	HTint DisConnect(void);													//	Network Disconnect Function
	HTint Connect(char *a_pstrServerIP, short a_nPortNum);					//	Network Connect Function
	WORD GetConnectingState();												//  Get State of the connecting server


private:
	CHTString			m_cstrLogIP;				//	Login Server's IP
	short				m_nLogPort;					//	Login Server's Port
	HWND				m_hWnd;						//	Parent's Window Handle
	CHTString			m_cstrID;					//	Player's ID

	char				m_pstrLogIP[20];			//	Login Server IP
	short				m_usLogPort;				//	Login Server Port

	//	About Hack
	DWORD				m_dwUnitSkillPassTime[5];
	DWORD				m_dwGetItemPassTime[5];

public:
	// Clear queued data
	bool ClearQueue(void);
};

#endif // !defined(AFX_TNNETWORKMANAGER_H__8E94DA55_857C_4C11_A829_C9759F895F3B__INCLUDED_)
