//----------------------------------------------------------------------------//
//	���� �̸�	: TNNetworkManager.h
//
//	���� ���� 	: 
//		- ���ӿ��� ����ϰ� �� ��Ʈ��ũ���� �ٷ�� Ŭ����.
//
//	�ۼ���		:
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

class TNNetworkManager//: public TNINetCallback // Interface ���
{
public:
	// Construction/Destruction
	TNNetworkManager();
	~TNNetworkManager();

	//	**	�α��� �׷�  **  ////////////////////////////////////////////////////////		

	//	���� ��ǥ �������� ������ ��û��.
	HTRESULT RequestReqMoveZoneServer(PS_CSP_REQ_MOVE_ZONE_SERVER pData);

	//	�ɸ����� ����Ʈ�� ��û��.
	HTRESULT RequestCharList();

	//	�ɸ��� ������ ��û��.
	HTRESULT RequestCharCreation(PS_CSP_REQ_CHAR_CREATE pData);

	//	�ɸ��� ������ ��û��.
	HTRESULT RequestCharDeletion(PS_CSP_REQ_CHAR_REMOVE pData);

	//	�ɸ��� ������ ��û��.	
	HTRESULT RequestReqCharSelect(PS_CSP_REQ_CHAR_SELECT pData);

	//	**  Initialize �׷�	 **  ////////////////////////////////////////////////////
	//	�ɸ��� �ʱ� �����͸� ��û.
	HTRESULT RequestInitChar(PS_CSP_REQ_CHAR_INIT pData);

	//	�ٸ�������Ʈ�� �̴��� ��û��
	HTRESULT RequestInitMobByID( MSG_REQMobByID* pData );


	//	ĳ���� �װ�, Regen �ʱ�ȭ ��û
	HTRESULT RequestReqInitRegenChar(PS_CSP_REQ_INIT_REGEN_CHAR pData);

	//	**	Moving, Packing/UnPacking, Using **  ////////////////////////////////////

	//	ĳ���Ͱ� �������� ���� ������ ����
	HTRESULT RequestCharAct(PS_CSP_REQ_CHAR_ACT pData);

	//	������ �̵����
	HTRESULT RequestItemMove(PS_CSP_REQ_ITEM_MOVE pData);

	// �� ���� ������ ����߸���
	HTRESULT RequestItemDrop(_S_CSP_REQ_ITEM_DROP* pData);

	// ������ ������ �ݱ�
	HTRESULT RequestItemGet(_S_CSP_REQ_ITEM_GET* pData);

	//	������ ��ŷ�� ��û��.
	//HTRESULT RequestItemPacking(PS_CSP_REQ_ITEM_PACKING pData);
	HTRESULT RequestItemPacking( MSG_Packing* pData );

	//	������ ����� ��û��.
	HTRESULT RequestItemUse(MSG_ITEM* pData);

	//	���Ǿ��� �̵��� ��û��.
	HTRESULT RequestMoneyMove( MSG_Money_Move* pData );

	//	�ɸ����� �̵��� ��û��.
	HTRESULT RequestCharMoveBroadcast( PS_CSP_REQ_CHAR_MOVE_BROADCAST pData );

	//	�ɸ����� �̵��� ��û��2.
	HTRESULT RequestMSG_Action( MSG_Action* pData );

	//	������ ��û��
	HTRESULT RequestMSG_Attack( MSG_Attack* pData, HTint iMsgSize );

	//	��Ż�̵��� ��û��.
	HTRESULT RequestReqMovePortal(PS_CSP_REQ_MOVE_PORTAL pData);

	//	Į���ھ� ����� ��û��
	HTRESULT RequestReqRegisterKalaCore(MSG_REGISTER_KALA_CORE* pData);

    //  **  Normal Combat  **  //////////////////////////////////////////////////////
	//	PK��ư ��� �޽���
	HTRESULT RequestPKToggleButton(MSG_TOGGLE_BUTTON* pData);

	//	**  Chatting  **  ///////////////////////////////////////////////////////////
	//	�Ϲ� ä�� ó���� �˸�.
	HTRESULT RequestReqNormalChat(PS_CSP_REQ_CHAT pData);

	//	�ӼӸ� ä�� ó���� �˸�.
	HTRESULT RequestReqWhisperChat(PS_CSP_REQ_WHISPER_CHAT pData);

	//	��Ƽ ä���� �˸�.
	HTRESULT RequestGroupChat(MSG_Chat* pData);

	//	���峻 ���� ä���� �˸�.
	HTRESULT ReqNotifyMessage(MSG_Broadcast* pData);

	//	**  Party/Guild/Address Book  **  ///////////////////////////////////////////
	//	��Ƽ ����/������ ��û��
	HTRESULT RequestReqCreateJoinParty(MSG_REQParty* pData);
	
	//	��Ƽ ���Կ�û�� ���� ����
	HTRESULT RequestReqCNFParty(MSG_CNFParty* pData);

	//	��Ƽ Ż��/��ü ��û
	HTRESULT RequestReqRemoveParty(MSG_RemoveParty* pData);

	//	�ڵ��й� ��� ���� ��û
	HTRESULT RequestSetParty( MSG_SetParty* pData );
	
	//	�ּҷ� ����� ��û��
	HTRESULT RequestJoinAddressBook(MSG_ReqMessenger* pData);

	//	�ּҷ� ÷�� ��û�� ���� ����� ó����
	HTRESULT RequestJoinAddressBookResult(MSG_CNFMessenger* pData);

	//	�ּҷϿ��� ������ ��û��
	HTRESULT RequestReqAddressBookMemberDelete(MSG_RemoveMessenger* pData);
	

	//	**  Status  **  /////////////////////////////////////////////////////////////

	//	�ɸ����� �������������� �˸���.
	HTRESULT RequestCharPing();

	//	�ɸ����� ���ӻ��� �� ��ġ�� Ȯ���Ѵ�.
	HTRESULT RequestReqCharLocation( S_GCSP_REQ_CHARACTER_SEARCH* pData );

	//	**  Parameter  **  /////////////////////////////////////////////////////////

	//	��ũ�� ����Ʈ ����� ��û
	HTRESULT RequestIncreaseChakra(PS_CSP_REQ_INCREASE_CHAKRA pData);

	//	�ֽż��� ��û
	HTRESULT RequestSelectTrimuriti( MSG_TrimuritySelect* pData, BYTE byType);
	
	//	�ֽ�����Ʈ Ȯ�� ��û
	HTRESULT RequestBrahmanPointRising( );

	//	��ġ ������ ��û�Ѵ�.
	HTRESULT ReqSavePosition(int iNPCID = 0);

	// ������ ��û�Ѵ�.
	HTRESULT ReqChangeJob( MSG_CLASS* pData );

	//	**  Skill  **  /////////////////////////////////////////////////////////////
	//	��ų �ʱ�ȭ�� ��û��
	HTRESULT RequestInitSkill( MSG_InitSkill* pData );

	//	ĳ������ ��ų Level-Up�� ����.
	HTRESULT RequestSkillLevelUp( PS_CSP_REQ_SKILL_LEVEL_UP pData );

	//	ĳ������ ��ų Learn�� ����.
	HTRESULT RequestSkillLearn( PS_CSP_REQ_LEARN_SKILL pData );

	//	ĳ������ ��ų Cast Unit ����.
	HTRESULT RequestSkillCastUnitSkill( PS_CSP_CAST_UNIT_SKILL pData );

	//	ĳ������ ��ų Cast Area ����.
	HTRESULT RequestSkillCastAreaSkill( PS_CSP_CAST_AREA_SKILL pData );

	//	**  Item & Economy  **  ///////////////////////////////////////////////////
	//  ĳ�� ������ ��û.
	HTRESULT RequestItemCash( Msg_Cash* pData );

	// ��ũ��/��ų �ʱ�ȭ ���� ��û (2004. 8. 27)
	HTRESULT RequestCharacterInitialize(Msg_NPCCommand* pData );

	//	������ ������ ��û.
	HTRESULT RequestItemBuy( PS_CSP_REQ_ITEM_BUY pData );

	//	������ ������ ��û��.
	HTRESULT RequestItemRepair(PS_CSP_REQ_ITEM_REPAIR pData);

	//	������ ��ü�� ��û.
	HTRESULT RequestItemSell( PS_CSP_REQ_ITEM_SELL pData );

	//	������ ������ ��û
	HTRESULT RequestItemRefining(PS_CSP_REQ_ITEM_REFINING pData);

	//	������ �峳 ��û
	HTRESULT RequestItemOffering( MSG_ItemContribution* pData );

	//	�峳 ������ ��ġ ��û
	HTRESULT RequestRefineScale( );

	//	���� �峳�� ��û.
	HTRESULT RequestPranaContribution(PS_CSP_REQ_PRANA_CONTRIBUTION pData);

	// ���� ���� �� ��� ���
	HTRESULT RequestStore( MSG_MobStore* pData );

	// ���� �������� �� ��� ��û
	HTRESULT RequestStoreBuy( MSG_MobStore_Buy* pData );

	// ��볻�� ����Ī ��û
	HTRESULT RequestTimeMode( Msg_TimeMode* pData );

	// ��ɼ� ����ȭ ������ ��û
	HTRESULT RequestChargeFunctionItem( Msg_Time* pData );

	//	**  Rental Stroe  **  /////////////////////////////////////////////////////////
	HTRESULT RequestMyRentalItemList( Msg_MyRentalItemList* pData );		// ���� ��Ź ������ ����Ʈ�� ��û
	HTRESULT RequestRentalItemList( Msg_RentalItemList* pData );			// Ư�� ��Ź������ �����۸���Ʈ ��û
	HTRESULT RequestRentalItemAdd( Msg_RentalItemAdd* pData );				// �������� ��Ź��
	HTRESULT RequestRentalItemCancel( Msg_RentalItemCancel* pData );		// ��Ź�� �������� ���
	HTRESULT RequestRentalGetMoney( Msg_RentalGetMoney* pData );			// ����� ���� �� ã��
	HTRESULT RequestRentalGetItem( Msg_RentalGetItem* pData );				// ����� �� ��ǰ ã�� (�Ⱓ ���� �����۵�)
	HTRESULT RequestRentalTex( Msg_SetRentalTex* pData );						// ��Ź������ ���� ����
	HTRESULT RequestRentalStoreClose( Msg_RentalStoreClose* pData );		// ��Ź���� ���ְ� �ݱ�
	HTRESULT RequestRentalItemBuy( Msg_RentalItemBuy* pData );				// ��Ź�������� ������ ����
	//HTRESULT RequestRentalStockItem( Msg_RentalStockItem* pData );		// ������ �������۸���Ʈ�� ��û�Ѵ�.
	HTRESULT RequestRentalStockItemList( Msg_RentalStockItemList* pData );		// ������ �������۸���Ʈ�� ��û�Ѵ�.

	//	**  Exchange  **  /////////////////////////////////////////////////////////
	// ��ȯ��û/������ �߰� ��û/���
	HTRESULT RequestExchange( PS_CSP_REQ_TRADE pData);

	// ��ȯ ���
	HTRESULT RequestTradeCancel( );

	// ���ο� "/Ż��"
	HTRESULT RequestEscape();
	

	//	**  Quest  **  /////////////////////////////////////////////////////////

	//	Ŭ���̾�Ʈ ȭ�鿡 NPC ��ȭ�� ǥ���Ѵ�.
	HTRESULT RequestQuestDialog(PS_CSP_QUEST_DIALOG pData);

	//	����Ʈ ���� ���¸� �˸���
	HTRESULT RequestQuestNotifyLevel(PS_CSP_QUEST_NOTIFY_LEVEL pData);

	// �׽�ũ ����Ʈ ���� ��û
	HTRESULT RequestTaskQuest( MSG_STANDARDPARM* pData );

	//	**  GM  **  ///////////////////////////////////////////////////////////////
	//	GM�� ��带 ���� �Ǵ� ������ ��û.
	HTRESULT RequestGMMode(MSG_GMMode* pData);

	//	Ư����ġ���� ������ ��û.(��������)
	HTRESULT RequestGMMovePosition(MSG_GMMovePosition* pData);

	//	Ư���ɸ��� ��ó���� ������ ��û.
	HTRESULT RequestGMMoveNearChar(MSG_GMMoveToPlayer* pData);

	//	Ư���ɸ��͸� GM ��ó�� ���� ��û�Ѵ�
	HTRESULT RequesCharRecall(PS_CSP_REQ_CHAR_RECALL pData);

	//	ä�û���� ����, ���� ��û.
	HTRESULT RuquestControlChat(PS_CSP_REQ_CONTROL_CHAT pData);

	//	Ư���ɸ����� ���۸����� ��û�Ѵ�.
	HTRESULT RuquestControlAction(PS_CSP_REQ_CONTROL_ACTION pData);

	//	Ư���ɸ����� ������ ��û�Ѵ�.(�⺻����, ��������, ��ų)
	HTRESULT RuquestCharacterInfo(PS_CSP_REQ_CHAR_INFO pData);

	//	Ư���ɸ����� �������Ḧ ��û�Ѵ�.
	HTRESULT RuquestCloseCharacter(MSG_GMKickPlayer* pData);

	//	�������
	HTRESULT RuquestAppealChat(PS_CSP_REQ_APPEAL_CHAT pData);

	//	**  GUILD  **  ///////////////////////////////////////////////////////////////

	//	��� ������ ��û�Ѵ�.
	HTRESULT ReqestGuildCreateMsg(MSG_CreateGuild* pData);

	//	�����ü�� ��û�Ѵ�.
	HTRESULT ReqestGuildDisbandMsg(MSG_RemoveGuildMember* pData);

	//	���� ������ ��û�Ѵ�.
	HTRESULT ReqestGuildJoinMsg( MSG_REQGuild* pData );

	//	���������û�� ���� ����޼����� �����Ѵ�.
	HTRESULT ReqestGuildCNFGuild( MSG_CNFGuild* pData );

	//	��帶ũ ������ ��û
	HTRESULT ReqestGuildMarkCreateMsg( MSG_GuildUpdateMark* );

	//	��� ������Ʈ ��û
	HTRESULT ReqestGuildUpdateMsg( MSG_GuildUpdate* );

	//	��� ���� ����
	HTRESULT ReqestGuildSetRanking( MSG_GuildSetRanking* pData );

	// �ƽ��� ����
	HTRESULT RequestMsgAshuramGuild( Msg_GuildAlliance* pData );

	///////////////////////////////////////////////////////////////////////////////

	//	���� �ֽ� NPC�� Ŭ��������
	HTRESULT ReqestMsgContactNpc( MSG_CONTACT_NPC* pData );

	//	�̿��
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
