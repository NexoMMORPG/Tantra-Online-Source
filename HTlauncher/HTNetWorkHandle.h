
#ifndef __HTNETWORKHANDLE_H__
#define __HTNETWORKHANDLE_H__

// 8 bit integer
//typedef __int8 char ;
typedef unsigned __int8 HSUBYTE ;


class CHTNetWorkHandle
{
public:
	CHTNetWorkHandle();
	~CHTNetWorkHandle();

	static HTRESULT			HT_vNetWorkInit();
	static HTRESULT			HT_vNetWorkControl();

	//----------�ʱ� ����Ÿ ��ȯ---------//
	static HTRESULT			HT_hrNetWorkInit_InitChar( BYTE byConnectType, WORD wPortalID, CHTString strMainCharName, CHTString stTargetCharName );

	//----------ť���ִ� ����Ÿ �����ͼ� ó���ϴ� �κ�---------//
	static HTRESULT			HT_hrWorkFunction(char* pData);

private:

	//	�������� �޴� �޽���
	static HTvoid				HT_vNetWork_MSG_MessagePanel( char* pData );
	
	//			0x00 Group - Login Server Cahnge
	static HTvoid				HT_vNetWork_SCP_CharacterList( char* pData );
	static HTvoid				HT_vNetWork_SCP_CharacterCreate( char* pData );
	static HTvoid				HT_vNetWork_SCP_CharacterRemove( char* pData );

	//			0x10 Group - Login & Character
	static HTvoid				HT_vNetWork_SCP_ZoneMove( char* pData );
	static HTvoid				HT_vNetWork_SCP_MSG_MoveOtherZone( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Remove_Mob( char* pData );

	//			0x11 Group ? Initialize
	static HTvoid				HT_vNetWork_SCP_InitChar( char* pData );
	static HTvoid				HT_vNetWork_SCP_InitOtherChar( char* pData );
	static HTvoid				HT_vNetWork_SCP_Init_Guild( char* pData );
	static HTvoid				HT_vNetWork_SCP_Init_Regen_Char( char* pData );
	static HTvoid				HT_vNetWork_SCP_StrongGuildInit( char* pData );
	static HTvoid				HT_vNetWork_SCP_StrongGuildUdate( char* pData );
		
	//			0x12 Group ? Moving, Packing/UnPacking, Using
	static HTvoid				HT_vNetWork_SCP_RESP_Item_Move( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Map_Item_Appear( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Map_Item_DisAppear( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Item_Drop( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Item_Get( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Item_Set( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Item_Packing( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Select_Trimuriti( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Save_Position( char* pData );
	static HTvoid				HT_vNetWork_SCP_Resp_Change_Job( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Itme_UseOrInfo( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Char_Move_Broadcast( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_MSG_Action( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Move_Portal( char* pData );

	//			0x14 Group - Equipment
	static HTvoid				HT_vNetWork_SCP_Item_Equipment_Broadcast( char* pData );
	static HTvoid				HT_vNetWork_SCP_Item_Abrasion( char* pData );
	//-----���������� ������-----//
	static HTvoid				HT_vNetWork_SCP_Item_Abrasion_Broadcast( char* pData );
	
	//			0x15 Group - Chatting
	static HTvoid				HT_vNetWork_SCP_NormalChatting( char* pData );
	static HTvoid				HT_vNetWork_SCP_WhisperChatting( char* pData );
	static HTvoid				HT_vNetWork_SCP_GroupChatting( char* pData );
	static HTvoid				HT_vNetWork_SCP_NotifyMessage( char* pData );

	static HTvoid				HT_vNetWork_SCP_RESP_WhisperChatting( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_PartyChatting( char* pData );

	//			0x16 Group(Party/Guild/�ּҷ�)	101
	static HTvoid				HT_vNetWork_SCP_CREATEJOIN_PARTY( char* pData );
	static HTvoid				HT_vNetWork_SCP_MSG_ADDPARTY( char* pData );
	static HTvoid				HT_vNetWork_SCP_MSG_UPDATEPARTY( char* pData );
	static HTvoid				HT_vNetWork_SCP_MSG_REMOVEPARTY( char* pData );
	static HTvoid				HT_vNetWork_SCP_Resp_Set_Party( char* pData );

	static HTvoid				HT_vNetWork_SCP_RemoveGuildMember( char* pData );
	static HTvoid				HT_vNetWork_SCP_REQGuild( char* pData );
	static HTvoid				HT_vNetWork_SCP_GuildMemberin( char* pData );
	static HTvoid				HT_vNetWork_SCP_GuildMemberout( char* pData );
	static HTvoid				HT_vNetWork_SCP_AddGuildMember( char* pData );
	static HTvoid				HT_vNewWork_SCP_MSG_GuildUpdateMark( char* pData );
	static HTvoid				HT_vNewWork_SCP_MSG_GuildUpdate( char* pData );
	static HTvoid				HT_vNewWork_SCP_MSG_GuildUpdateMember( char* pData );
	static HTvoid				HT_vNewWork_SCP_MSG_GuildNotify( char* pData );
	static HTvoid				HT_vNewWork_SCP_MSG_GuildSetRanking( char* pData );

	static HTvoid				HT_vNetWork_SCP_INIT_ADDRESS_BOOK( char* pData );
	static HTvoid				HT_vNetWork_SCP_INIT_REAL_ADDRESS_BOOK( char* pData );
	static HTvoid				HT_vNetWork_SCP_MSG_MessengerLogin( char* pData );
	static HTvoid				HT_vNetWork_SCP_MSG_MessengerLogout( char* pData );
	static HTvoid				HT_vNetWork_SCP_JOIN_ADDRESS_BOOK( char* pData );


	//			0x17 Group - Quest
	//---------- ĳ������ ����Ʈ ��� ���� -------------//
	static HTvoid				HT_vNetWork_SCP_RESP_QUEST_HISTORY( char* pData );
	//---------����Ʈ ���� ���� ����-----------//
	static HTvoid				HT_vNetWork_SCP_QUEST_DIALOG( char* pData );
	//---------- ĳ������ ������ ����Ʈ ���� ���� ���� -------------//
	static HTvoid				HT_vNetWork_SCP_RESP_QUEST_NOTIFY_LEVEL( char* pData );
	// �׽�ũ ����Ʈ ��û ���
	static HTvoid				HT_vNetWork_SCP_RESP_TaskQuest( char* pData );

	//			0x19 Group - Parameter
	static HTvoid				HT_vNetWork_SCP_Brahman_Rising( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_UpdateUI( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Update_Status( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_LevelUp_Broadcast( char* pData );

	//-----���������� ������-----//	
	static HTvoid				HT_vNetWork_SCP_RESP_Monster_Params( char* pData );
	static HTvoid				HT_vNetWork_SCP_Monster_Params_Change( char* pData );
	static HTvoid				HT_vNetWork_SCP_Item_Params_Change( char* pData );

	//			0x20 Group ? Skill
	static HTvoid				HT_vNetWork_SCP_Skill_InitData( char* pData );
	static HTvoid				HT_vNetWork_SCP_Skill_LevelUP( char* pData );
	static HTvoid				HT_vNetWork_SCP_Skill_LearnSkill( char* pData );
	static HTvoid				HT_vNetWork_SCP_Skill_CastUnitSkill( char* pData );
	static HTvoid				HT_vNetWork_SCP_Skill_CastAreaSkill( char* pData );
	static HTvoid				HT_vNetWork_SCP_SKILL_Up_Effect( char* pData );
	static HTvoid				HT_vNetWork_SCP_Resp_Item_CharacterInitialize( char* pData );	// �߰� (��ų/��ũ�� �ʱ�ȭ���� ��û) 2004. 8. 27

	//			0x21 Group ? Item & Economy
	static HTvoid				HT_vNetWork_SCP_RESP_ITEM_BUY( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_ITEM_SELL( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_ITEM_CASH( char* pData );		// �߰� (������ ĳ��) 2004. 8. 19
	static HTvoid				HT_vNetWork_SCP_RESP_ITEM_REPAIR( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_ITEM_REFINING( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_Charge_Function_Item( char* pData);

	static HTvoid				HT_vNetWork_SCP_RESP_ItemContribution( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_RefineScale( char* pData );

	static HTvoid				HT_vNetWork_SCP_RESP_ITEM_CONTRIBUTION( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_PRANA_CONTRIBUTION( char* pData );
	static HTvoid				HT_vNetWork_SCP_ITEM_REMOVE( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_MONEY_MOVE( char* pData );	//���Ǿ� �̵�
	
	static HTvoid				HT_vNetWork_SCP_Resp_Store( char* pData );
	static HTvoid				HT_vNetWork_SCP_Resp_Store_Buy( char* pData );
	static HTvoid				HT_vNetWork_SCP_Resp_MobStatus( char* pData );

	//			0x22 Group - Exchange
	static HTvoid				HT_vNetWork_SCP_RESP_TRADE( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_TRADE_CANCEL( char* pData );
	
    //			0x25 Group(GM)	212
	static HTvoid				HT_vNetWork_SCP_RESP_GMMode( char* pData );
	static HTvoid				HT_vNetWork_SCP_GMmode_NOTIFY( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_GMMOVE_POSITION( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_GMMOVE_NEAR_CHAR( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_APPEAL_CHAT( char* pData );

	static HTvoid				HT_vNetWork_SCP_RESP_CHAR_RECALL( char* pData );
	static HTvoid				HT_vNetWork_SCP_CHAR_RECALL_NOTIFY( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_CONTROL_CHAT( char* pData );
	static HTvoid				HT_vNetWork_SCP_CONTROL_CHAT_NOTIFY( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_CONTROL_ACTION( char* pData );
	static HTvoid				HT_vNetWork_SCP_CONTROL_ACTION_NOTIFY( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_TROUBLE_REPORT( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_TROUBLE_REPORT_LIST( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_TROUBLE_REPORT_SET( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_CHAR_INFO( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_CHAR_SKILL( char* pData );
	static HTvoid				HT_vNetWork_SCP_RESP_CLOSE_CHAR( char* pData );

	//	Event
	//	Fire Fx Broadcast
	static HTvoid				HT_vNetWork_SCP_FireFxBroadcast( char* pData );
	//	Beauty
	static HTvoid				HT_vNetWork_SCP_Beauty( char* pData );
	//	Duel System
	static HTvoid				HT_vNetWork_SCP_Challenger( char* pData );
	// �ƽ�������
	static HTvoid				HT_vNetWork_SCP_AshuramGuild( char* pData );
	//	Assist Change Target
	static HTvoid				HT_vNetWork_SCP_ChangeTarget( char* pData );
	//	Version Check
	static HTvoid				HT_vNetWork_SCP_VersionCheck( char* pData );
	//	Billing Status
	static HTvoid				HT_vNetWork_SCP_BillingStatus( char* pData );
	//	Coupon Event
	static HTvoid				HT_vNetWork_SCP_GameEvent( char* pData );
	//	Msg Alarm
	static HTvoid				HT_vNetWork_SCP_Alarm( char* pData );
	//	Warp
	static HTvoid				HT_vNetWork_SCP_Warp( char* pData );
	//	Echo
	static HTvoid				HT_vNetWork_SCP_Echo( char* pData );
	//	YutMove
	static HTvoid				HT_vNetWork_SCP_YutMove( char* pData );
	//	YutMyMoney
	static HTvoid				HT_vNetWork_SCP_YutMyMoney( char* pData );
	//	YutStatus
	static HTvoid				HT_vNetWork_SCP_YutStatus( char* pData );
	//	YutBet
	static HTvoid				HT_vNetWork_SCP_YutBet( char* pData );
	//	YutGetMoney
	static HTvoid				HT_vNetWork_SCP_YutGetMoney( char* pData );

	//	Zone Setting
	static HTvoid				HT_vNetWork_SCP_ZoneSetting( char* pData );
	//	Change Trimuriti ID
	static HTvoid				HT_vNetWork_SCP_ChangeTrimuritiID( char* pData );

	//	State_of_the_siege
	static HTvoid				HT_vNetWork_SCP_StateOfSiege( char* pData );
	//	State_Siege Entry
	static HTvoid				HT_vNetWork_SCP_SiegeEntry( char* pData );
	//	MSG_FIX_DATE_OF_SIEGE 
	static HTvoid				HT_vNetWork_SCP_FixDataOfSiege( char* pData );
	//	Msg_SetSalesRate
	static HTvoid				HT_vNetWork_SCP_SetSalesRate( char* pData );
	//	Msg_GetMoney
	static HTvoid				HT_vNetWork_SCP_GetMoney( char* pData );
	//	MSG_ChangeClanID
	static HTvoid				HT_vNetWork_SCP_ChangeClanID( char* pData );
	//	MSG_APPLY_SIEGE_ID
	static HTvoid				HT_vNetWork_SCP_Apply_Siege_ID( char* pData );
	//	Msg Castle Init
	static HTvoid				HT_vNetWork_SCP_CastleInit( char* pData );
	//	Msg Castle Update
	static HTvoid				HT_vNetWork_SCP_CastleUpdate( char* pData );

	//	Ahsram Cargo
	//	Msg_GuildCargoUsingLevel
	static HTvoid				HT_vNetWork_SCP_GuildCargoUsingLevel( char* pData );
	//	Msg_GuildCargoTimeExtension
	static HTvoid				HT_vNetWork_SCP_GuildCargoTimeExtension( char* pData );
	//	Msg_GuildCargoTime
	static HTvoid				HT_vNetWork_SCP_GuildCargoTime( char* pData );
	//	Msg_GuildItem
	static HTvoid				HT_vNetWork_SCP_GuildItem( char* pData );
	//	Msg_GuildItemUpdate
	static HTvoid				HT_vNetWork_SCP_GuildItemUpdate( char* pData );

	// Rental Store
	// Msg_MyRentalItemList :		
	static HTvoid				HT_vNetWork_SCP_MyRentalItemList( char* pData );		// ���� ��Ź ������ ����Ʈ�� ��û ����
	// Msg_RentalItemList :			
	static HTvoid				HT_vNetWork_SCP_RentalItemList( char* pData );		// Ư�� ��Ź������ �����۸���Ʈ ��û ����
	// Msg_RentalItemAdd :			
	static HTvoid				HT_vNetWork_SCP_RentalItemAdd( char* pData );			// �������� ��Ź�� ����
	// Msg_RentalItemCancel :		
	static HTvoid				HT_vNetWork_SCP_RentalItemCancel( char* pData );		// ��Ź�� �������� ��� ����
	// Msg_RentalGetMoney :			
	static HTvoid				HT_vNetWork_SCP_RentalGetMoney( char* pData );		// ����� ���� �� ã�� ����
	// Msg_RentalGetItem :			
	static HTvoid				HT_vNetWork_SCP_RentalGetItem( char* pData );			// ����� �� ��ǰ ã�� (�Ⱓ ���� �����۵�) ����
	// Msg_RentalTex :				
	static HTvoid				HT_vNetWork_SCP_RentalTex( char* pData );				// ��Ź������ ���� ���� ����
	// Msg_RentalStoreClose :		
	static HTvoid				HT_vNetWork_SCP_RentalStoreClose( char* pData );		// ��Ź���� ���ְ� �ݱ� ����
	// Msg_RentalItemBuy :			
	static HTvoid				HT_vNetWork_SCP_RentalItemBuy( char* pData );			// ��Ź�������� ������ ���� ����
	// Msg_RentalStockItem :		
	//static HTvoid				HT_vNetWork_SCP_RentalStockItem( char* pData );	// ������ ���������� ��û�Ѵ�. ����
	// Msg_RentalStockItemList :		
	static HTvoid				HT_vNetWork_SCP_RentalStockItemList( char* pData );	// ������ �������۸���Ʈ�� ��û�Ѵ�. ����

	//	For Bot
	// Msg_Who :
	static HTvoid				HT_vNetwork_SCP_Who( char *pData );	// Bot ������ ��ȣ ���� ��Ŷ ����
	static HTvoid				HT_vNetwork_SCP_Quiz( char *pData );	//	�׾߸��� ����
};

#endif

