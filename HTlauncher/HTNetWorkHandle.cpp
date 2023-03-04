
#include "stdafx.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTWindowManager.h"
#include "HTNetWorkHandle.h"

// ĳ���� �α׾ƿ�
#define REPLY_REQ_CHAR_LOGOUT_SUCC				0x00	// ĳ���� �α׾ƿ� ����
#define REPLY_REQ_CHAR_LOGOUT_PORTAL			0x01	// ĳ���� �α׾ƿ� ����(��Ż)
#define REPLY_REQ_CHAR_LOGOUT_CALL				0x02	// ĳ���� �α׾ƿ� ����(��ȯ)
#define DISCONNECT_ALREADY_CONNECTED			0x03	// �̹� �������� ������ ���� �α׾ƿ�ó��
#define DISCONNECT_LACK_OR_HACK					0x04	// �ٻ���ڿ� ���� �α׾ƿ�ó��

// �ʱ�ȭ ��û�� ���� �ڵ�
#define INIT_CHAR_SUCCESS						0x00
#define INIT_CHAR_ERROR_FORTALID				0x01
#define INIT_CHAR_ERROR_POSITION				0x02
#define INIT_CHAR_ERROR_ARRANGE					0x03
#define INIT_CHAR_ERROR_HANDLE					0x04
#define INIT_CHAR_ERROR_GETID					0x05
#define INIT_CHAR_ERROR_GETNAME					0x06
#define INIT_CHAR_ERROR_CREATEAREA				0x07
#define INIT_CHAR_ERROR_GETDATA					0x08
#define INIT_CHAR_ERROR							0x09

CHTNetWorkHandle::CHTNetWorkHandle()
{
}

CHTNetWorkHandle::~CHTNetWorkHandle()
{
}

//----------��Ʈ�� ȯ�� �ʱ�ȭ�ϰ�, �ʱ� ���� �ٿ�ε�----------//
HTRESULT CHTNetWorkHandle::HT_vNetWorkInit()
{
	g_DebugingFont_Count = 0;
	for( HTint i=0 ;i<10 ; i++ )
		g_DebugingFont[i].HT_hrCleanUp();

	return HT_OK;
}

HTRESULT CHTNetWorkHandle::HT_vNetWorkControl()
{
	return HT_OK;
}


//----------�ʱ� ĳ���� ���� ��û---------//
HTRESULT CHTNetWorkHandle::HT_hrNetWorkInit_InitChar( BYTE byConnectType, WORD wPortalID, CHTString strMainCharName, CHTString stTargetCharName )
{
	//  initChar�� �ι� ���� �� �ִ� ��츦 �����ϱ� ����
	g_iInitCharSW = HT_TRUE;

	static S_CSP_REQ_CHAR_INIT info;

	info.byConnType	= byConnectType;			// ���� ���¸� ���� ( 0x01: �ʱ� ����, 0x02: ��Ż �̵�, 0x03:���� );
	info.byConnPos		= 0;						// �ʱ� ������ ��� ���� ��ġ ( 0x01: �ֽ� ����, 0x02: ���� ���� ��ġ )
	info.wPortalID		= wPortalID;				// ��Ż �̵��� ��� ��Ż ID
	CHTString::HT_hrStringCopy( info.szCharName, strMainCharName, SZNAME_LENGTH );
	CHTString::HT_hrStringCopy( info.szTargetName, stTargetCharName, SZNAME_LENGTH );
    	
	if ( g_pNetWorkMgr ) g_pNetWorkMgr->RequestInitChar( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Req_InitChar Name:%s", info.szCharName );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	//	���ΰ��� ���� �ѹ��� ������Ʈ
	g_bOneTimeUpdate				= GAMESEQUNCE_MAINGAME_NONE;

	HT_g_vLogFile("InitRequestChar! \n");
	
	return HT_OK;
}

//----------ť���ִ� ����Ÿ �����ͼ� ó���ϴ� �κ�---------//
HTRESULT CHTNetWorkHandle::HT_hrWorkFunction(char* pData)
{
	HTRESULT hr = HT_OK;


#ifdef HT_DEBUG_NETWORK
//	HSTRACE(eNet, "Execute Receive Data Type:%x	DataLength:%d\n", usType, usLength);
#endif

	MSG_STANDARD *pMsg = (MSG_STANDARD*)pData;

	if (!pMsg) return HT_FAIL;

	//CHTString strTmp;
	//strTmp.HT_szFormat( "#%x#", pMsg->wType );
	//HT_g_vLogFile( (HTtchar*)strTmp );

	switch(pMsg->wType)
	{
		case _MSG_MessagePanel :
			HT_vNetWork_MSG_MessagePanel( pData );
			break;
		//----------------------------------------------------------------------
		// Intro part
		//----------------------------------------------------------------------
		case SCP_RESP_CHAR_LIST:
			HT_vNetWork_SCP_CharacterList( pData );
			break;
		case SCP_RESP_CHAR_CREATE:
			HT_vNetWork_SCP_CharacterCreate( pData );
			break;
		case SCP_RESP_CHAR_REMOVE:
			HT_vNetWork_SCP_CharacterRemove( pData );
			break;
		case SCP_RESP_MOVE_ZONE_SERVER:
			HT_vNetWork_SCP_ZoneMove( pData );
			break;
		case _MSG_MoveOtherZone :
			HT_vNetWork_SCP_MSG_MoveOtherZone( pData );
			break;
		//----------------------------------------------------------------------
		// Main part
		//----------------------------------------------------------------------
		case SCP_RESP_CHAR_INIT:
			HT_vNetWork_SCP_InitChar( pData );
			break;
		case SCP_RESP_INIT_REGEN_CHAR :
			HT_vNetWork_SCP_Init_Regen_Char( pData );
			break;
		case SCP_INIT_OTHER_MOB:
			HT_vNetWork_SCP_InitOtherChar( pData );
			break;
		case _MSG_GuildInfo :
            HT_vNetWork_SCP_Init_Guild( pData );
			break;
		case _Msg_StrongHoldInit :
			HT_vNetWork_SCP_StrongGuildInit( pData );
			break;
		case _Msg_StrongHoldUpdate :
			HT_vNetWork_SCP_StrongGuildUdate( pData );
			break;
		//			0x15 Group - Chatting
		case SCP_NOTIFY_CHAT:
			HT_vNetWork_SCP_NormalChatting( pData );
			break;
		case SCP_NOTIFY_WHISPER_CHAT:
			HT_vNetWork_SCP_WhisperChatting( pData );
			break;
		case _MSG_Chat:
			HT_vNetWork_SCP_GroupChatting( pData );
			break;
		case _MSG_Broadcast:
			HT_vNetWork_SCP_NotifyMessage( pData );
			break;
		case SCP_RESP_WHISPER_CHAT:
			HT_vNetWork_SCP_RESP_WhisperChatting( pData );
			break;
		case SCP_RESP_REMOVE_MOB:
			HT_vNetWork_SCP_RESP_Remove_Mob( pData );
			break;
		case SCP_RESP_EQUIP_SET :
			HT_vNetWork_SCP_Item_Equipment_Broadcast( pData );
			break;
		case SCP_ITEM_ABRASION:
			HT_vNetWork_SCP_Item_Abrasion(pData );
			break;

		case SCP_ITEM_ABRASION_BROADCAST:
			HT_vNetWork_SCP_Item_Abrasion_Broadcast(pData );
			break;

		//			0x12 Group ? Moving, Packing/UnPacking, Using
		case SCP_RESP_ITEM_MOVE :
			HT_vNetWork_SCP_RESP_Item_Move( pData );
			break;
		case SCP_MAP_ITEM_APPEAR :
			HT_vNetWork_SCP_RESP_Map_Item_Appear( pData );
			break;
		case SCP_MAP_ITEM_DISAPPEAR :
			HT_vNetWork_SCP_RESP_Map_Item_DisAppear( pData );
			break;
		case SCP_RESP_ITEM_DROP :
			HT_vNetWork_SCP_RESP_Item_Drop( pData );
			break;
		case SCP_RESP_ITEM_GET :
			HT_vNetWork_SCP_RESP_Item_Get( pData );
			break;
		case SCP_RESP_ITEM_SET :
			HT_vNetWork_SCP_RESP_Item_Set( pData );
			break;
		case _MSG_Packing :
			HT_vNetWork_SCP_RESP_Item_Packing( pData );
			break;
		case _MSG_TrimuritySelect:	// �ֽ� ����/��ȸ ��Ŷ
			HT_vNetWork_SCP_RESP_Select_Trimuriti( pData );
			break;
		case SCP_RESP_SAVE_POSITION:
			HT_vNetWork_SCP_RESP_Save_Position( pData );
			break;
		case _MSG_CLASS:
			HT_vNetWork_SCP_Resp_Change_Job( pData );
			break;
		case MSG_ITEM_ID:
			HT_vNetWork_SCP_RESP_Itme_UseOrInfo( pData );
			break;
		case SCP_RESP_CHAR_MOVE_BROADCAST :
			HT_vNetWork_SCP_RESP_Char_Move_Broadcast( pData );
			break;
		case _MSG_Action :
			HT_vNetWork_SCP_RESP_MSG_Action( pData );
			break;
		case SCP_RESP_MOVE_PORTAL :
			HT_vNetWork_SCP_RESP_Move_Portal( pData );
			break;
		//			0x19 Group - Parameter
		case SCP_LEVEL_UP_BROADCAST:
			HT_vNetWork_SCP_RESP_LevelUp_Broadcast( pData );
			break;
		case _MSG_TrimurityPoint :
			HT_vNetWork_SCP_Brahman_Rising( pData );
			break;
		case SCP_RESP_UPDATE_UI :
			HT_vNetWork_SCP_RESP_UpdateUI( pData );
			break;
		case SCP_RESP_UPDATE_STATUS:
			HT_vNetWork_SCP_RESP_Update_Status( pData );
			break;
		//			0x20 Group ? Skill
		case _MSG_InitSkill:
			HT_vNetWork_SCP_Skill_InitData( pData );
			break;
		case SCP_RESP_SKILL_LEVEL_UP :
			HT_vNetWork_SCP_Skill_LevelUP( pData );
			break;
		case SCP_RESP_LEARN_SKILL :
			HT_vNetWork_SCP_Skill_LearnSkill( pData );
			break;
		case CSP_CAST_UNIT_SKILL :
			HT_vNetWork_SCP_Skill_CastUnitSkill( pData );
			break;
		case CSP_CAST_AREA_SKILL :
			HT_vNetWork_SCP_Skill_CastAreaSkill( pData );
			break;
		case SKILL_UP_EFFECT :
			HT_vNetWork_SCP_SKILL_Up_Effect( pData );
			break;
		//			0x21 Group ? Item & Economy
		case SCP_RESP_ITEM_BUY :
			HT_vNetWork_SCP_RESP_ITEM_BUY( pData );
			break;
		case SCP_RESP_ITEM_REPAIR :
			HT_vNetWork_SCP_RESP_ITEM_REPAIR( pData );
			break;
		case SCP_RESP_ITEM_SELL :
			HT_vNetWork_SCP_RESP_ITEM_SELL( pData );
			break;
		case _Msg_Cash :
			HT_vNetWork_SCP_RESP_ITEM_CASH( pData );
			break;
		case _Msg_NPCCommand :
			HT_vNetWork_SCP_Resp_Item_CharacterInitialize( pData );
			break;
		case _Msg_Time :
			HT_vNetWork_SCP_RESP_Charge_Function_Item( pData );
			break;
		case _MSG_MobStore :
			HT_vNetWork_SCP_Resp_Store( pData );
			break;
		case _MSG_MobStore_Buy :
			HT_vNetWork_SCP_Resp_Store_Buy( pData );
			break;
		case _MSG_MobStatus :
			HT_vNetWork_SCP_Resp_MobStatus( pData );
			break;
		case SCP_RESP_ITEM_REFINING:
			HT_vNetWork_SCP_RESP_ITEM_REFINING( pData );
			break;
		case _MSG_ItemContribution:
			HT_vNetWork_SCP_RESP_ItemContribution( pData );
			break;
		case _MSG_RefineScale:
			HT_vNetWork_SCP_RESP_RefineScale( pData );
			break;
		case SCP_RESP_PRANA_CONTRIBUTION :
			HT_vNetWork_SCP_RESP_PRANA_CONTRIBUTION( pData );
			break;
		case SCP_ITEM_REMOVE:
			HT_vNetWork_SCP_ITEM_REMOVE( pData );
			break;
		case _MSG_Money_Move:
			HT_vNetWork_SCP_RESP_MONEY_MOVE( pData );
			break;

		//			0x22 Group - Exchange
		case CSP_REQ_TRADE:
			HT_vNetWork_SCP_RESP_TRADE( pData );
			break;
		case SCP_RESP_TRADE_CANCEL:
			HT_vNetWork_SCP_RESP_TRADE_CANCEL( pData );
			break;

		//			0x16 Group ? Party/Guild/Address Book
		case _MSG_REQParty:
			HT_vNetWork_SCP_CREATEJOIN_PARTY( pData );
			break;
		case _MSG_AddParty:
			HT_vNetWork_SCP_MSG_ADDPARTY( pData );
			break;
		case SCP_RESP_UPDATE_PARTY:
			HT_vNetWork_SCP_MSG_UPDATEPARTY( pData );
			break;
		case _MSG_RemoveParty:
			HT_vNetWork_SCP_MSG_REMOVEPARTY( pData );
			break;
		case _MSG_SetParty:
			HT_vNetWork_SCP_Resp_Set_Party( pData );
			break;

		case _MSG_RemoveGuildMember :
			HT_vNetWork_SCP_RemoveGuildMember( pData );
			break;
		case _MSG_REQGuild :
			HT_vNetWork_SCP_REQGuild( pData );
			break;
		case _MSG_GuildMemberin	:
			HT_vNetWork_SCP_GuildMemberin( pData );
			break;
		case _MSG_GuildMemberout :
			HT_vNetWork_SCP_GuildMemberout( pData );
			break;
		case _MSG_AddGuildMember :
			HT_vNetWork_SCP_AddGuildMember( pData );
			break;
		case _MSG_GuildUpdateMark :
			HT_vNewWork_SCP_MSG_GuildUpdateMark( pData );
			break;
		case _MSG_GuildUpdate :
			HT_vNewWork_SCP_MSG_GuildUpdate( pData );
			break;
		case _MSG_GuildUpdateMember :
			HT_vNewWork_SCP_MSG_GuildUpdateMember( pData );
			break;
		case _MSG_GuildNotify :
			HT_vNewWork_SCP_MSG_GuildNotify( pData );
			break;
		case _MSG_GuildSetRanking :
			HT_vNewWork_SCP_MSG_GuildSetRanking( pData );
			break;

		case _MSG_UpdateMessengerList:
			HT_vNetWork_SCP_INIT_ADDRESS_BOOK( pData );
			break;
		case _MSG_UpdateMessengerItem:
			HT_vNetWork_SCP_INIT_REAL_ADDRESS_BOOK( pData );
			break;
		case _MSG_MessengerLogin:
			HT_vNetWork_SCP_MSG_MessengerLogin( pData );
			break;
		case _MSG_MessengerLogout:
			HT_vNetWork_SCP_MSG_MessengerLogout( pData );
			break;
		case _MSG_ReqMessenger:
			HT_vNetWork_SCP_JOIN_ADDRESS_BOOK( pData );
			break;
		//	0x17 Group - Quest
		case SCP_RESP_QUEST_HISTORY:
			HT_vNetWork_SCP_RESP_QUEST_HISTORY( pData );
			break;
		case SCP_QUEST_DIALOG:
			HT_vNetWork_SCP_QUEST_DIALOG( pData );
			break;
		case SCP_QUEST_NOTIFY_LEVEL:
			HT_vNetWork_SCP_RESP_QUEST_NOTIFY_LEVEL( pData );
			break;
		case _MSG_Quest :
			HT_vNetWork_SCP_RESP_TaskQuest( pData );
			break;
		//	0x17 Group - GM
		case _MSG_GMMode :
			HT_vNetWork_SCP_RESP_GMMode( pData );
			break;
		case _MSG_GMMode_Notify :
			HT_vNetWork_SCP_GMmode_NOTIFY( pData );
			break;
		case _MSG_GMMovePosition :
			HT_vNetWork_SCP_RESP_GMMOVE_POSITION( pData );
			break;
		case _MSG_GMMoveToPlayer :
			HT_vNetWork_SCP_RESP_GMMOVE_NEAR_CHAR( pData );
			break;
		case SCP_RESP_TROUBLE_REPORT :
			HT_vNetWork_SCP_RESP_TROUBLE_REPORT( pData );
			break;
		case SCP_RESP_TROUBLE_REPORT_LIST :
			HT_vNetWork_SCP_RESP_TROUBLE_REPORT_LIST( pData );
			break;
		case SCP_RESP_TROUBLE_REPORT_SET :
			HT_vNetWork_SCP_RESP_TROUBLE_REPORT_SET( pData );
			break;
		case SCP_RESP_CHAR_INFO :
			HT_vNetWork_SCP_RESP_CHAR_INFO( pData );
			break;
		case SCP_RESP_CHAR_SKILL :
			HT_vNetWork_SCP_RESP_CHAR_SKILL( pData );
			break;
		case SCP_RESP_CLOSE_CHAR :
			HT_vNetWork_SCP_RESP_CLOSE_CHAR( pData );
			break;
		case SCP_FIRE_FX_BROADCAST :
			HT_vNetWork_SCP_FireFxBroadcast( pData );
			break;
		case _MSG_Beauty :
			HT_vNetWork_SCP_Beauty( pData );
			break;
		case _Msg_Challenger :
			HT_vNetWork_SCP_Challenger( pData );
			break;
		case _Msg_GuildAlliance :
			HT_vNetWork_SCP_AshuramGuild( pData );
			break;
		case _MSG_CHANGE_TARGET :
			HT_vNetWork_SCP_ChangeTarget( pData );
			break;
		case _Msg_VersionCheck :
			HT_vNetWork_SCP_VersionCheck( pData );
			break;
		case _Msg_BillStatus :
			HT_vNetWork_SCP_BillingStatus( pData );
			break;
		case _Msg_GameEvent :
			HT_vNetWork_SCP_GameEvent( pData );
			break;
		case _MSG_Warp :
			HT_vNetWork_SCP_Warp( pData );
			break;
		case _Msg_Echo :
			HT_vNetWork_SCP_Echo( pData );
			break;
		case _Msg_YutMove :
			HT_vNetWork_SCP_YutMove( pData );
			break;
		case _Msg_YutMyMoney :		// �׺��� �ڽ��� �� ���� ���¸� �޾ƿɴϴ�. (ó�� ������ �˾��ø� ��û�Ͽ� ����)
			HT_vNetWork_SCP_YutMyMoney( pData );
			break;
		case _Msg_YutStatus :		// �׺��� ��ü�� �� ���� ���¸� �޾ƿɴϴ�. (���ΰ�ħ�� ��û�Ͽ� ����)
			HT_vNetWork_SCP_YutStatus( pData );
			break;
		case _Msg_YutBet :			// �׺��� ������ �õ��Ͽ� ����� �޽��ϴ�.
			HT_vNetWork_SCP_YutBet( pData );
			break;
		case _Msg_YutGetMoney :		// ��÷�� ������ ��û�մϴ�.
			HT_vNetWork_SCP_YutGetMoney( pData );
			break;
		case MSG_SET_ZONE_SETTINGS_ID :
			HT_vNetWork_SCP_ZoneSetting( pData );
			break;
		case MSG_CHANGE_TRIMURITI_ID :
			HT_vNetWork_SCP_ChangeTrimuritiID( pData );
			break;
		case MSG_STATE_OF_THE_SIEGE_ID :
			HT_vNetWork_SCP_StateOfSiege( pData );
			break;
		case MSG_SIEGE_ENTRY_ID :
			HT_vNetWork_SCP_SiegeEntry( pData );
			break;
		case MSG_FIX_DATE_OF_SIEGE_ID :
			HT_vNetWork_SCP_FixDataOfSiege( pData );
			break;
		case _Msg_SetSalesRate :
			HT_vNetWork_SCP_SetSalesRate( pData );
			break;
		case _Msg_GetMoney :
			HT_vNetWork_SCP_GetMoney( pData );
			break;
		case MSG_CHANGE_CLAN_ID :
			HT_vNetWork_SCP_ChangeClanID( pData );
			break;
		case MSG_APPLY_SIEGE_ID :
			HT_vNetWork_SCP_Apply_Siege_ID( pData );
			break;
		case _Msg_CastleInit :
			HT_vNetWork_SCP_CastleInit( pData );
			break;
		case _Msg_CastleUpdate :
            HT_vNetWork_SCP_CastleUpdate( pData );
			break;
		case _Msg_GuildCargoUsingLevel :
			HT_vNetWork_SCP_GuildCargoUsingLevel( pData );
			break;
		case _Msg_GuildCargoTimeExtension :
			HT_vNetWork_SCP_GuildCargoTimeExtension( pData );
			break;
		case _Msg_GuildCargoTime :
			HT_vNetWork_SCP_GuildCargoTime( pData );
			break;
		case _Msg_GuildItem :
			HT_vNetWork_SCP_GuildItem( pData );
			break;
		case _Msg_GuildItemUpdate :
			HT_vNetWork_SCP_GuildItemUpdate( pData );
			break;
		//===========================================
		//				��Ź���� ��Ŷ��
		//===========================================	
		case _Msg_MyRentalItemList :		// ���� ��Ź ������ ����Ʈ�� ��û ����
			HT_vNetWork_SCP_MyRentalItemList( pData );
			break;
		case _Msg_RentalItemList :			// Ư�� ��Ź������ �����۸���Ʈ ��û ����
			HT_vNetWork_SCP_RentalItemList( pData );
			break;
		case _Msg_RentalItemAdd :			// �������� ��Ź�� ����
			HT_vNetWork_SCP_RentalItemAdd( pData );
			break;
		case _Msg_RentalItemCancel :		// ��Ź�� �������� ��� ����
			HT_vNetWork_SCP_RentalItemCancel( pData );
			break;
		case _Msg_RentalGetMoney :			// ����� ���� �� ã�� ����
			HT_vNetWork_SCP_RentalGetMoney( pData );
			break;
		case _Msg_RentalGetItem :			// ����� �� ��ǰ ã�� (�Ⱓ ���� �����۵�) ����
			HT_vNetWork_SCP_RentalGetItem( pData );
			break;
		case _Msg_SetRentalTex :				// ��Ź������ ���� ���� ����
			HT_vNetWork_SCP_RentalTex( pData );
			break;
		case _Msg_RentalStoreClose :		// ��Ź���� ���ְ� �ݱ� ����
			HT_vNetWork_SCP_RentalStoreClose( pData );
			break;
		case _Msg_RentalItemBuy :			// ��Ź�������� ������ ���� ����
			HT_vNetWork_SCP_RentalItemBuy( pData );
			break;
//		case _Msg_RentalStockItem :			// ������ ���������� ��û�Ѵ�. ����
//			HT_vNetWork_SCP_RentalStockItem( pData );
//			break;
		case _Msg_RentalStockItemList :			// ������ �������۸���Ʈ�� ��û�Ѵ�. ����
			HT_vNetWork_SCP_RentalStockItemList( pData );
			break;
		case _Msg_Who:						// Bot ������ ��ȣ ���� ��Ŷ ����
			HT_vNetwork_SCP_Who( pData );
			break;
		case _Msg_Quiz:
			HT_vNetwork_SCP_Quiz( pData );	//	�׾߸��� ����
			break;
		// etc
		case TNNETWORKERROR:
			break;
		case TNNETWORKCONNECT:
		//	HSTRACE(eGame, "Network(Region) Connected!!!\n");
			break;
		case TNNETWORKDISCONNECT:
			if( g_iGameSequnce == 1 )
			{
				if (g_cIntroManager)
				{
					CHTString szMessage;
					// �˼��մϴ�. ������ ������ ���������ϴ�. �ٽ� �������ֽʽÿ�.
					if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
						g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
				}
			}
			else
			{
				if( !g_bZoneServerSwitching )
				{
					// ���� �� ������ ������ ������ �����̸� ���α׷��� ����
					if (g_pNetWorkMgr)
					{
						if( g_pNetWorkMgr->GetConnectingState() == STATUS_DISCONNECT )
						{
							CHTString szMessage;
							// �˼��մϴ�. ������ ������ ���������ϴ�. �ٽ� �������ֽʽÿ�.
							if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
								g_cGameSystem->HT_vGameSystem_ServerDisConnect_SetDlg( szMessage );
						}
					}
				}
			}
			break;
		default:
			if( g_bDevelopingMode )
			{
				CHTString strTmp;
				strTmp.HT_szFormat( "UnKnow Message#%x#", pMsg->wType );
				HT_g_vLogFile( (HTtchar*)strTmp );
				MessageBox( NULL, strTmp, "Debug", MB_OK );
			}
			break;
	}

	return hr;
}

//	�������� �޴� �޽���
HTvoid CHTNetWorkHandle::HT_vNetWork_MSG_MessagePanel( char* pData )
{
	static MSG_MessagePanel info;
	memcpy( &info, pData, sizeof(MSG_MessagePanel) );

	if( g_iGameSequnce == 1 )
	{
		if (g_cIntroManager) g_cIntroManager->HT_vIntro_SetShowMessage( info.String, 5000 );
		return;
	}
	else
	{
        if (g_BasicLoadingInfo) g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, info.String );
	}

	// for debugging
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Recive Panel Message : %s", info.String );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

// Recive char list
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_CharacterList( char* pData )
{
	if (g_cIntroManager) g_cIntroManager->HT_vSCP_RESP_CHAR_LIST( pData+TNMSG_HEADER_SIZE );
	// for debugging
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_CharacterList : OK");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

// Get response about create character
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_CharacterCreate( char* pData )
{
	static S_SCP_RESP_CHAR_CREATE info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_CHAR_CREATE) );
	
	if (g_cIntroManager) g_cIntroManager->HT_vCSP_RESP_CHAR_CREATE( &info );
	// for debugging
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_CharacterCreate : %x", info.byResult);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

// Get response about remove character
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_CharacterRemove( char* pData )
{
	static S_SCP_RESP_CHAR_REMOVE info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_CHAR_REMOVE) );

	if (g_cIntroManager) g_cIntroManager->HT_vCSP_RESP_CHAR_REMOVE( &info );
	// for debugging
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_CharacterRemove : %x", info.byResult);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//			0x00 Group - Login Server Cahnge
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_ZoneMove( char* pData )
{
	static S_SCP_RESP_MOVE_ZONE_SERVER info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_MOVE_ZONE_SERVER) );

	//CHTString strDebug;
	//strDebug.HT_szFormat( "Recive Move Zone Server %d, %d, %d", info.nResult, g_byInitConnectType, g_wPotalID );
	//MessageBox( HT_NULL, strDebug, _T("Debug"), MB_OK );

	if( g_iGameSequnce == 1 )
	{
        if (g_cIntroManager) g_cIntroManager->HT_vSCP_RESP_MOVE_ZONE_SERVER( &info );
	}
	else
	{
		if( info.nResult == 0 )
		{
			//	Request Move Zone Server
            //g_cGameSystem->HT_vSetRequestMoveZoneServer( HT_FALSE );

			//	ĳ���� ���ʺ��� �ʱ�ȭ
			if (g_cMainCharacter) g_cMainCharacter->HT_hrMainCharInitVariable();
			//	���� �õ� �ð� ����
			g_cInitConntion_StartTime = GetTickCount();

			// INIT_CHAR�� �����Ѵ�.
			if( g_byInitConnectType == CONNECT_TYPE_PORTAL ||
				g_byInitConnectType == CONNECT_TYPE_PUSTICA )
			{
				HT_hrNetWorkInit_InitChar( g_byInitConnectType, g_wPotalID, g_oMainCharacterInfo.szCharName, _T("") );
			}
			else if( g_byInitConnectType == CONNECT_TYPE_WARP )
			{
				if ( g_cGMSystem ) 
					HT_hrNetWorkInit_InitChar( g_byInitConnectType, 0, g_oMainCharacterInfo.szCharName, g_cGMSystem->HT_strGM_GetNearCharName() );
			}
			else if( g_byInitConnectType == CONNECT_TYPE_DIE ||
					 g_byInitConnectType == CONNECT_TYPE_FIRST ||
					 g_byInitConnectType == CONNECT_TYPE_GMRECALL )
			{
				HT_hrNetWorkInit_InitChar( g_byInitConnectType, 0, g_oMainCharacterInfo.szCharName, _T("") );
			}
		}
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_RespMoveZoneServer : %x", info.nResult);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_MSG_MoveOtherZone( char* pData )
{
	static MSG_MoveOtherZone info;
	memcpy( &info, pData, sizeof(MSG_MoveOtherZone) );

	g_cPortal->HT_vPortal_NetWork_SCP_MSG_MoveOtherZone( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_MSG_MoveOtherZone");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//			0x10 Group - Login & Character
//----------�ٸ� ĳ���ͳ� ������ AOI���� ����� ��---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Remove_Mob( char* pData )
{
	if( g_iGameSequnce == 1 )
	{
		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Rmove_Mob:" );
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
		return;
	}

	static S_SCP_RESP_REMOVE_MOB info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_REMOVE_MOB) );

	if ( g_cMainCharacter )
	{
		if( info.nID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
		{
			if( info.byResult == 1 )
			{
				g_cGameSystem->HT_vGameSystem_NetWorkDeath( info.snTribe, info.szName );
				//-----����� �׽�Ʈ�� ���Ͽ�-----//
				//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MainChar_DeathMessage" );
				//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
			}
		}
		else
		{
			if ( g_cOtherObjectSystem ) g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkObjectRemoveMob( &info );
		}

		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		////g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Rmove_Mob:" );
		////if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}
}

//			0x11 Group ? Initialize
//----------ĳ���� ���ӽ� �ʱ�ȭ ����---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_InitChar( char* pData )
{
	HT_g_vLogFile("-InitReciveChar \n"); 

	//  initChar�� �ι� ���� �� �ִ� ��츦 �����ϱ� ����
	if( !g_iInitCharSW )
		return;
	g_iInitCharSW = HT_FALSE;
	
	static S_SCP_RESP_CHAR_INIT info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_CHAR_INIT) );

	g_wPotalID = 0x00;
	g_wWalf = 0x00;
	g_byIsDeadInit = info.byIsDead;

	//	ĳ���� �⺻ ���� ���� �ѱ��
	if ( g_cMainCharacter )
	{
		// MainCharacter�� Guild Serial �� �����Ͽ� ���� �ƽ��� ��α׿� ������ �� ����Ѵ�.
		g_cMainCharacter->m_iGuildSerial = info.nGuildID;
		g_cMainCharacter->HT_hrMainCharInit( info.dwKeyID, info.snX, info.snZ, info.dwGameTime, info.byClan, info.dwTimeStamp );
	}
	
	if ( g_cItemSystem )
	{
		//	PC �κ��丮 �ʱ�ȭ
		g_cEquipInventory->HT_vInitBagStatus( );
		g_cItemSystem->HT_LL_vInsertAfter_ItemCreateInven( info.Inven );
		//	���� ������ �ʱ�ȭ
		g_cItemSystem->HT_LL_vInsertAfter_ItemCreateEquip( info.Equip );
	}

	if (g_cSkillSystem)
	{
		//	Skill ���� �ѱ��
		g_cSkillSystem->HT_vSkillSystem_Init_SkillBook( info.bySkill );
	}
 
	if ( g_cItemSystem )
	{
		// NPC �κ��丮 �ʱ�ȭ
		g_cItemSystem->HT_LL_vInsertAfter_ItemCreateNPCInven( info.Cargo );
	}

	if (g_cEquipInventory)
	{
		g_cEquipInventory->HT_vEquipInventory_SetNPCMoney( info.nCargoMoney );
	}

	if (g_cQuest)
	{
		// ����Ʈ �ʱ�ȭ
		g_cQuest->HT_vNetWork_SCP_RESP_Quest_History( info.byQuest );
	}

	if (g_cIndividualStore)	// �� �̵���, �����̾� ���� ��볻�� ������ �ʱ�ȭ ���� �ʱ� ���� ������ ������ �����ش�.
	{
		//������ ��Ŷ�� ������.
		g_cIndividualStore->HT_vNetWork_CSP_Req_TimeMode( g_cIndividualStore->PrimiumService_UseList() );
	}

	if( info.dwEvent > 0 )
        g_pEventWindow->HT_vEventWnd_ReqCheckGameEvent( info.dwEvent );

	//----------���� ������Ʈ ����----------//
	g_bOneTimeUpdate = GAMESEQUNCE_MAINGAME_RECEIVEINITCHAR;
	//----------���� ������Ʈ ����----------//
	g_bMainCharacterInitialized = HT_TRUE;

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_InitChar : %d", info.dwKeyID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------ĳ���� ���� ��û ���---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Init_Regen_Char( char* pData )
{
	static S_SCP_RESP_INIT_REGEN_CHAR info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_INIT_REGEN_CHAR) );
	
	if (g_cGameSystem) g_cGameSystem->HT_vGameSystem_SCP_INIT_REGEN_CHAR( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_INIT_REGEN_CHAR : OK");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------��� ���� �ʱⰪ---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_StrongGuildInit( char* pData )
{
	static Msg_StrongHoldInit info;
	memcpy( &info, pData, sizeof(Msg_StrongHoldInit) );

	if( g_cGuildSystem ) g_cGuildSystem->HT_vGuildNet_SCP_StrongGuildInit( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_StrongHoldInit");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------��� ���� ������Ʈ��---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_StrongGuildUdate( char* pData )
{
	static Msg_StrongHoldUpdate info;
	memcpy( &info, pData, sizeof(Msg_StrongHoldUpdate) );

	if( g_cGuildSystem ) g_cGuildSystem->HT_vGuildNet_SCP_StrongGuildUpdate( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_StrongHoldInit");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�ֺ� �ٸ� ĳ���͵��� ������ ����---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_InitOtherChar( char* pData )
{
	static S_SCP_INIT_OTHER_MOB info;
	memcpy( &info, pData, sizeof(S_SCP_INIT_OTHER_MOB) );

	if( g_iGameSequnce == 1 )
	{
		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Init_Other_MOB:" );
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
		return;
	}

	//	���� NPC�� ���� ���� - ����
    if( g_iInationalType != INATIONALTYPE_KOREA )
	{
		if( info.snTribe == 2945 ||
			info.snTribe == 2939 ||
			info.snTribe == 2940 ||
			info.snTribe == 2941 ||
			info.snTribe == 2942 ||
			info.snTribe == 2943 ||
			info.snTribe == 2944 )
			return;
	}
	
	if( g_cOtherObjectSystem )
        g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkObjectInsert( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	////g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_InitOtherChar : ID:%d, Tribe:%d, x:%d,z:%d", info.nID, info.snTribe, info.snTargetX, info.snTargetZ );
	////if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------��� �ʱ�ȭ----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Init_Guild( char* pData )
{
	MSG_GuildInfo info;
	memcpy( &info, pData, sizeof(MSG_GuildInfo) );

	if (g_cGuildSystem) g_cGuildSystem->HT_vNetWork_SCP_INIT_GUILD( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_InitGuild");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//			0x12 Group ? Moving, Packing/UnPacking, Using
//----------������ �̵� ���� ����---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Item_Move( char* pData )
{
	static S_SCP_RESP_ITEM_MOVE info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_ITEM_MOVE) );
	if (g_cItemControl) g_cItemControl->HT_vItemControl_Network_ReqMove_Result( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Move : %x(%d:%d)->(%d:%d)", info.nResult, 
	//									info.byFromPlace, info.snFromIndex, info.byToPlace, info.snToIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Item_Drop( char* pData )
{
	static S_SCP_RESP_ITEM_DROP info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_ITEM_DROP) );
	if (g_cItemControl) g_cItemControl->HT_vItemControl_Network_ReqDrop_Result( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Drop : type(%d-%d)(%d:%d)(��%d)", 
	//										info.byType, info.snResult, info.byPlace, info.byIndex, info.dwMoney );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Item_Get( char* pData )
{
	static S_SCP_RESP_ITEM_GET info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_ITEM_GET) );
	if (g_cItemControl) g_cItemControl->HT_vItemControl_Network_ReqGet_Result( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Get : %d-%d", info.nResult, info.snIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Item_Set( char* pData )
{
	static S_SCP_RESP_ITEM_SET info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_ITEM_SET) );
	
	if (g_cItemSystem) g_cItemSystem->HT_vItemSystem_ItemSet( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Set : %d-%d:%d", info.byType, info.byPlace, info.byIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�������� ������ ��Ÿ����---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Map_Item_Appear( char* pData )
{
	//	������ �Կ��� ���� ������ �������� ������ �ʾƾ� �Ѵ�.
	if( g_bGamePlayMovieForGlobal )
		return;

	static S_SCP_MAP_ITEM_APPEAR info;
	memcpy( &info, pData, sizeof(S_SCP_MAP_ITEM_APPEAR) );
	if (g_cItemSystem) g_cItemSystem->HT_vItemSystem_Appear( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Apper : %x:%d(%d,%d)", 
	//																info.nItemID, info.dwIndex, info.snX, info.snZ );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�������� �ʿ��� �������---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Map_Item_DisAppear( char* pData )
{
	static S_SCP_MAP_ITEM_DISAPPEAR info;
	memcpy( &info, pData, sizeof(S_SCP_MAP_ITEM_DISAPPEAR) );
	if (g_cItemSystem) g_cItemSystem->HT_vItemSystem_DisAppear( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_DisAppear : %d", info.nItemID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Item_Packing( char* pData )
{
	//PS_SCP_RESP_ITEM_PACKING info = HT_NULL;
	//info = new S_SCP_RESP_ITEM_PACKING;
	//memcpy( info, pData, sizeof(S_SCP_RESP_ITEM_PACKING) );
	static MSG_Packing info;
	memcpy( &info, pData, sizeof(MSG_Packing) );

	if ( g_cItemSystem ) g_cItemControl->HT_vItemControl_Network_Resp_ItemPacking( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Packing: %d:type(%d)-Sou(%d,%d:%d)Des(%d,%d:%d)", info.byResult, 
	//	info.byType, info.byFromPlace, info.byFromIndex, info.byFromCount, info.byToPlace, info.byToIndex, info.byToCount );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Select_Trimuriti( char* pData )
{
	static MSG_TrimuritySelect info;
	memcpy( &info, pData, sizeof(MSG_TrimuritySelect) );

	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_Resp_Select_Trimuriti( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SelectTrimuriti : %s-%d(type = %d)[%d:%d:%d]", info.CharName, info.byTrimuriti, info.byType, info.nBrahmaCount, info.nVishnuCount, info.nSivaCount);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

// ��ġ ����
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Save_Position( char* pData )
{
	static S_RESULT info;
	memcpy( &info, pData, sizeof(S_RESULT) );

	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_Resp_SavePosition( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Save_Position");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Itme_UseOrInfo( char* pData )
{
	static MSG_ITEM info;
	memcpy( &info, pData, sizeof(MSG_ITEM) );

	/*if (info.kItem.snDurability < 0 )
	{
		int a = info.kItem.snDurability;
	}*/

	if (g_cItemControl)
	{
		if( info.byType == HT_MSG_ITEM_USE )
		{
			g_cItemControl->HT_vNetWork_SCP_RESP_Item_Use_Result( &info );
		}
		else if ( info.byType == eItem_Brd )
		{	//	Ư�� �����ۿ� ���Ͽ� ����Ʈ Ʋ���ֱ� ����
			if( info.snUserKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
			{	// ������ Ŭ�� ����ϴ� ������ �ε����� �ణ �ٸ��� ^^;
				HTint idItem = info.kItem.snIndex + HT_PARAMTYPE_ITEM_START - 1;
				g_cMainCharacter->HT_vMainChar_SCP_SetItemEffect( idItem );
				g_cItemControl->HT_vNetWork_SCP_RESP_Item_Use_Result( &info );
			}
			else
			{
				HTint idItem = info.kItem.snIndex + HT_PARAMTYPE_ITEM_START - 1;
				g_cOtherObjectSystem->HT_vOtherObjectSystem_SetItemEffect( info.snUserKeyID, idItem );
			}
		}
		else
		{	// info.byType == HT_MSG_ITEM_INFO
			g_cItemSystem->HT_vItemSystem_vNetWork_SCP_Item_Durability_Decrease( &info );
		}			
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_UseOrInfo : type-%d", info.byType);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Char_Move_Broadcast( char* pData )
{
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Char_Move_Broadcast : OK");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_MSG_Action( char* pData )
{
	if( g_iGameSequnce == 1 )
	{
		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Char_MSG_Action" );
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
		return;
	}

	if( !g_cMainCharacter || !g_cOtherObjectSystem )
		return;

	static MSG_Action info;
	memcpy( &info, pData, sizeof(MSG_Action) );

	if( info.dwKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		g_cMainCharacter->HT_vNetWork_Recive_MSGAction( &info );
	}
	else
	{
		g_cOtherObjectSystem->HT_hrOtherObjectSystem_Network_MsgAction( &info );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	////g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Char_MSG_Action : ID:%d, x:%d, z:%d", info.dwKeyID, info.TargetX, info.TargetY );
	////if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------���� �̵� ��û ���----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Move_Portal( char* pData )
{
	static S_SCP_RESP_MOVE_PORTAL info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_MOVE_PORTAL) );

	if ( g_cPortal ) g_cPortal->HT_vPortal_Network_SCP_Resp_Portal( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Move_Portal :%d ", info.byResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//			0x14 Group - Equipment
//----------������ ������ ������ �˸�---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Item_Equipment_Broadcast( char* pData )
{
	static S_SCP_RESP_EQUIP_SET info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_EQUIP_SET) );

	if ( g_cOtherObjectSystem ) g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkEquip( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_RESP_Item_EquipBroadcast : OK");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//-----------������ ������ �Ҹ�(�����)--------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Item_Abrasion( char* pData )
{
	static S_SCP_ITEM_ABRASION info;
	memcpy( &info, pData, sizeof(S_SCP_ITEM_ABRASION) );
	if ( g_cItemSystem ) g_cItemSystem->HT_hrItemSystem_vNetWork_SCP_Item_Abrasion( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Abrasion : OK");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//-----------������ ������ �Ҹ�(�����)�� �ֺ� ĳ���͵鿡�� ����------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Item_Abrasion_Broadcast( char* pData )
{
	static S_SCP_ITEM_ABRASION_BROADCAST info;
	memcpy( &info, pData, sizeof(S_SCP_ITEM_ABRASION_BROADCAST) );
	if ( g_cOtherObjectSystem ) g_cOtherObjectSystem->HT_vOtherObjectSystem_NewworkItemAbrasion( &info );//

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Abrasion_Broadcast : KeyID(%d)", info.dwKeyID);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//			0x15 Group - Chatting
//----------�븻 ä�� ����---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_NormalChatting( char* pData )
{
	static S_SCP_NOTIFY_CHAT info;
	memcpy( &info, pData, sizeof(S_SCP_NOTIFY_CHAT) );
	if ( g_cChatting ) g_cChatting->HT_vReceiveData_Normal( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	////g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_NormalChatting : OK");
	////if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�ӼӸ� ä�� ����---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_WhisperChatting( char* pData )
{
	static S_SCP_NOTIFY_WHISPER_CHAT info;
	memcpy( &info, pData, sizeof(S_SCP_NOTIFY_WHISPER_CHAT) );
	if ( g_cChatting ) g_cChatting->HT_vReceiveData_Whisper( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	////g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Notify_WhisperChatting : %s", info.szName);
	////if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}


//----------�׷� �޽��� ����---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_GroupChatting( char* pData )
{
	static MSG_Chat info;
	memcpy( &info, pData, sizeof(MSG_Chat) );
	if ( g_cChatting ) g_cChatting->HT_vReceiveData_Group( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	////g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_Chat : OK");
	////if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�������� ����---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_NotifyMessage( char* pData )
{
	static MSG_Broadcast info;
	memcpy( &info, pData, sizeof(MSG_Broadcast) );
	if ( g_cChatting ) g_cChatting->HT_vReceiveData_Notify( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_NotifyMessage : OK");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�ӼӸ� ä�� �۽� ���---------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_WhisperChatting( char* pData )
{
	//	�ӼӸ� ä�� �۽� ��� ó�� 
	static S_SCP_RESP_WHISPER_CHAT info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_WHISPER_CHAT) );
	if ( g_cChatting ) g_cChatting->HT_vReceiveDataResult_Whisper( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_WhisperChatting_Result : %d-%s", info.byResult, info.szName);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//			0x16 Group ? Party/Guild/Address Book
//	PS_SCP_RESP_ADDRESS_BOOK_DELETE;
//	PS_CSP_REQ_ADDRESS_BOOK_LIST;
//	PS_SCP_RESP_ADDRESS_BOOK_LIST;
//----------��Ƽ ����----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_CREATEJOIN_PARTY( char* pData )
{
	static MSG_REQParty info;
	memcpy( &info, pData, sizeof(MSG_REQParty) );
	if ( g_cParty ) g_cParty->HT_vNetWork_SCP_CREATEJOIN_PARTY( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_PartyCreate_Result : Leader:%d", info.Leader.nID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_MSG_ADDPARTY( char* pData )
{
	static MSG_AddParty info;
	memcpy( &info, pData, sizeof(MSG_AddParty) );

	if ( g_cParty ) g_cParty->HT_vNetWork_SCP_MSG_AddParty( &info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_AddParty:%d", info.Party.nID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_MSG_UPDATEPARTY( char* pData )
{
	if( g_iGameSequnce == 1 )
		return;

	static S_SCP_RESP_UPDATE_PARTY info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_UPDATE_PARTY) );

	if ( g_cParty ) g_cParty->HT_vNetWork_SCP_MSG_UpdateParty( &info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_UpdateParty" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_MSG_REMOVEPARTY( char* pData )
{
	static MSG_RemoveParty info;
	memcpy( &info, pData, sizeof(MSG_RemoveParty) );

	if ( g_cParty ) g_cParty->HT_vNetWork_SCP_MSG_RemoveParty( &info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_RemoveParty" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	��� ��ü�� ��û�Ѵ�.
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RemoveGuildMember( char* pData )
{
	static MSG_RemoveGuildMember info;
	memcpy( &info, pData, sizeof(MSG_RemoveGuildMember) );
	if ( g_cGuildSystem ) g_cGuildSystem->HT_vNetWork_SCP_RemoveGuildMember( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_S_SCP_Disband_Guild : OK" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	��� ������ ��û�Ѵ�.
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_REQGuild( char* pData )
{
	static MSG_REQGuild info;
	memcpy( &info, pData, sizeof(MSG_REQGuild) );
	if ( g_cGuildSystem )g_cGuildSystem->HT_vNetWork_SCP_REQGuild( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_S_SCP_ReqGuild" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//	������ ������
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_GuildMemberin( char* pData )
{
	static MSG_GuildMemberin info;
	memcpy( &info, pData, sizeof(MSG_GuildMemberin) );
	if ( g_cGuildSystem ) g_cGuildSystem->HT_vNetWork_SCP_GuildMemberin( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_S_SCP_GuildMemberIn" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//	������ ������ ����
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_GuildMemberout( char* pData )
{
	static MSG_GuildMemberout info;
	memcpy( &info, pData, sizeof(MSG_GuildMemberout) );
	if ( g_cGuildSystem ) g_cGuildSystem->HT_vNetWork_SCP_GuildMemberout( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_S_SCP_GuildMemberOut" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	�ű� ������ ������ �����鿡�� �����Ѵ�.
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_AddGuildMember( char* pData )
{
	static MSG_AddGuildMember info;
	memcpy( &info, pData, sizeof(MSG_AddGuildMember) );
	if ( g_cGuildSystem ) g_cGuildSystem->HT_vNetWork_SCP_AddGuildMember( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SCP_AddGuildMember : OK" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	��帶ũ ���ۿ� ���� ����
HTvoid CHTNetWorkHandle::HT_vNewWork_SCP_MSG_GuildUpdateMark( char* pData )
{
	static MSG_GuildUpdateMark info;
	memcpy( &info, pData, sizeof(MSG_GuildUpdateMark) );
	if ( g_cGuildSystem ) g_cGuildSystem->HT_vNetWork_SCP_MSG_GuildUpdateMark( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SCP_MSG_GuildUpdateMark : ID-%d,Mark-%d, CostType %d", 
	//	info.GuildID, info.Mark, info.byCostType );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	��� ������Ʈ
HTvoid CHTNetWorkHandle::HT_vNewWork_SCP_MSG_GuildUpdate( char* pData )
{
	static MSG_GuildUpdate info;
	memcpy( &info, pData, sizeof(MSG_GuildUpdate) );
	if ( g_cGuildSystem ) g_cGuildSystem->HT_vNetWork_SCP_MSG_GuildUpdate( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_GuildUpdate : OK (%s, %s, %s, %s)",info.AlliedGuildName1, info.AlliedGuildName2, info.EnemyGuildName1, info.EnemyGuildName2 );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	��� ��� ������Ʈ
HTvoid CHTNetWorkHandle::HT_vNewWork_SCP_MSG_GuildUpdateMember( char* pData )
{
	static MSG_GuildUpdateMember info;
	memcpy( &info, pData, sizeof(MSG_GuildUpdateMember) );
	if ( g_cGuildSystem ) g_cGuildSystem->HT_vNetWork_SCP_MSG_GuildUpdateMember( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_GuildUpdateMember : OK" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	��� â���� ������ ������
HTvoid CHTNetWorkHandle::HT_vNewWork_SCP_MSG_GuildNotify( char* pData )
{
	static MSG_GuildNotify info;
	memcpy( &info, pData, sizeof(MSG_GuildNotify) );
	if ( g_cOtherObjectSystem ) g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkGuildNotify( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_GuildNotify : ID-%d, Name-%s, Mark-%d",
	//																info.nID, info.GuildName, info.nMark );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	��� ��ŷ ������Ʈ
HTvoid CHTNetWorkHandle::HT_vNewWork_SCP_MSG_GuildSetRanking( char* pData )
{
	static MSG_GuildSetRanking info;
	memcpy( &info, pData, sizeof(MSG_GuildSetRanking) );
	if ( g_cGuildSystem ) g_cGuildSystem->HT_vNetWork_SCP_MSG_GuildSetRanking( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_GuildSetRanking : OK" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�ּҷ��� �����͸� �ʱ�ȭ (�޴´�)----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_INIT_ADDRESS_BOOK( char* pData )
{
	static MSG_UpdateMessengerList info;
	memcpy( &info, pData, sizeof(MSG_UpdateMessengerList) );

	if ( g_cAddress ) g_cAddress->HT_vSCP_InitAddressBook( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_UpdateMessengerList");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�ּҷ��� ������ ��ȭ�� �޴´�.----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_INIT_REAL_ADDRESS_BOOK( char* pData )
{
	static MSG_UpdateMessengerItem info;
	memcpy( &info, pData, sizeof(MSG_UpdateMessengerItem) );

	if ( g_cAddress ) g_cAddress->HT_vSCP_UpdateDataAddressBook( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_UpdateMessengerItem");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_MSG_MessengerLogin( char* pData )
{
	static MSG_MessengerLogin info;
	memcpy( &info, pData, sizeof(MSG_MessengerLogin) );

	if ( g_cAddress ) g_cAddress->HT_vSCP_MSG_MessengerLogin( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_MessengerLogin");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_MSG_MessengerLogout( char* pData )
{
	static MSG_MessengerLogout info;
	memcpy( &info, pData, sizeof(MSG_MessengerLogout) );

	if ( g_cAddress ) g_cAddress->HT_vSCP_MSG_MessengerLogout( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_MessengerLogout");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�ּҷϿ� ĳ���� �߰��� ��û�Ѵ�----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_JOIN_ADDRESS_BOOK( char* pData )
{
	static MSG_ReqMessenger info;
	memcpy( &info, pData, sizeof(MSG_ReqMessenger) );

	if ( g_cAddress ) g_cAddress->HT_vSCP_JoinAddressBook( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_ReqMessenger" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//			0x19 Group - Parameter
//----------LevelUp �� �˸�----------//
HTvoid  CHTNetWorkHandle::HT_vNetWork_SCP_RESP_LevelUp_Broadcast( char* pData )
{
	static S_SCP_LEVEL_UP_BROADCAST info;
	memcpy( &info, pData, sizeof(S_SCP_LEVEL_UP_BROADCAST) );

	//	MainChar	LevelUp Brodcast
	if( info.dwKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		g_cStatus->HT_vStatus_NetworkLevelUpBrodcast( &info );
		//g_cUIManager->HT_HideWindow(_DIALOG_SKILL);
		g_cUISkillWindow->HT_vSkillWindow_WindowPopup();
	}
	//	Other Character LevelUp �� �˸�
	else
	{	
		if( g_cOtherObjectSystem ) g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkLevelUpBrodcast( &info );
	}
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_LevelUp_Broadcast: %d Lvl %d", info.dwKeyID, info.byLevel );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------����常 ��� ���----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Brahman_Rising( char* pData )
{
	static MSG_TrimurityPoint info;
	memcpy( &info, pData, sizeof(MSG_TrimurityPoint) );
	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_Resp_Rising_Brahman( &info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Brahman_Rising : %d-money%d", info.nBramanPoint, info.dwMoney );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------ĳ���� �⺻ ����Ÿ ����ÿ� �������� ������----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_UpdateUI( char* pData )
{
	static S_SCP_RESP_UPDATE_UI info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_UPDATE_UI) );

	//	ToDo
	if ( g_cGameSystem ) g_cGameSystem->HT_vGameSystem_UpDateUI( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	////g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SCP_RESP_UpdateUI AtkSpeed:%d, MoveSpeed:%d", info.iAttackSpeed, info.iMoveSpeed );
	////if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Update_Status( char* pData )
{
	static S_SCP_RESP_UPDATE_STATUS info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_UPDATE_STATUS) );

	//	ToDo
	if ( g_cGameSystem ) g_cGameSystem->HT_vGameSystem_UpDate_Status( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	////g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SCP_RESP_UpdateUI_Status:HP:%d, Prana:%d, Affections:%x", info.iHP, info.iPrana, info.iAffections );
	////if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//-----���������� ������-----//

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Monster_Params( char* pData )
{
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Monster_Params_Change( char* pData )
{
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Item_Params_Change( char* pData )
{
}

//			0x20 Group ? Skill
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Skill_InitData( char* pData )
{
	static MSG_InitSkill info;
	memcpy( &info, pData, sizeof(MSG_InitSkill) );

	if (g_cSkillSystem)
	{
		//	Skill ���� �ѱ��
		g_cSkillSystem->HT_vSkillSystem_Init_SkillBook( info.bySkill );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MsgSkillInit");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------���� ��----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Skill_LevelUP( char* pData )
{
	static S_SCP_RESP_SKILL_LEVEL_UP info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_SKILL_LEVEL_UP) );
	if (g_cSkillInventory) g_cSkillInventory->HT_vNetWork_SCP_Skill_LevelUp( &info );
    
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SkillLevelUp : %d(%dLvl) ", info.byResult, info.byLevel);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------��ų ����----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Skill_LearnSkill( char* pData )
{
	static S_SCP_RESP_LEARN_SKILL info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_LEARN_SKILL) );
	if (g_cSkillInventory) g_cSkillInventory->HT_vNetWork_SCP_Skill_LearnSkill( &info );
    
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SkillLearnSkill OK");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------��ų ĳ��Ʈ �˸�----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Skill_CastUnitSkill( char* pData )
{
	static S_CSP_CAST_UNIT_SKILL info;
	memcpy( &info, pData, sizeof(S_CSP_CAST_UNIT_SKILL) );

	if( !g_cMainCharacter || !g_cOtherObjectSystem ) return;

	if( info.snCasterKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		g_cMainCharacter->HT_vMainChar_SCP_Skill_CastSkill_Broadcast( &info );
	}
	else
	{
		g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkUnitSkill( &info );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Unit_Skill ID:%d, snRes:%d, snKTargetRes:%d, CurHP:%d, Damage:%d, CasterTP:%d, SkillIndex:%d", 
		info.snCasterKeyID, info.snRes, info.kTarget.byRes, info.kTarget.iHP, info.kTarget.iDamage, info.iCasterTP, info.snSkillID );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------���� ��ų �˸�----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Skill_CastAreaSkill( char* pData )
{
	static S_CSP_CAST_AREA_SKILL info;
	memcpy( &info, pData, sizeof(S_CSP_CAST_AREA_SKILL) );
	
	if( info.snCasterKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		if ( g_cMainCharacter ) g_cMainCharacter->HT_vMainChar_SCP_Skill_CastSkill_Broadcast( &info );
	}			
	else
	{
		if ( g_cOtherObjectSystem ) g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkAreaSkill( &info );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//if( info.snRes == -1 )
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Cast_Area_Ready_Skill");
	//else
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Cast_Area_Attack_Skill");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------Ư���� �����ۿ� ���� ��ų ���� ��----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_SKILL_Up_Effect( char* pData )
{
	static MSG_SKILL_UP_EFFECT info;
	memcpy( &info, pData, sizeof(MSG_SKILL_UP_EFFECT) );

	g_cSkillInventory->HT_vNetWork_SCP_Skill_Up_Effect( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Skill_Up_Efect : ID:%d,CurLv:%d,UpLv:%d", info.snID, info.byLevel, info.byLevelPlus );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//			0x21 Group ? Item & Economy
//----------������ ������ ��û���----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_ITEM_BUY( char* pData )
{
	static S_SCP_RESP_ITEM_BUY info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_ITEM_BUY) );

	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_Resp_Item_Buy( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Buy : %d(%d:%d���Ǿ�)", 
	//												info.byResult, info.snItemIndex, info.nMoney );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------������ ������ ��û_���----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_ITEM_REPAIR( char* pData )
{
	static S_SCP_RESP_ITEM_REPAIR info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_ITEM_REPAIR) );
	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_RESP_ITEM_REPAIR( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Repair : %d(%d:%d-%d)", 
	//												info.byResult, info.byPlace, info.byIndex, info.nMoney);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------������ ��ü�� ��û_���----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_ITEM_SELL( char* pData )
{
	static S_SCP_RESP_ITEM_SELL info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_ITEM_SELL) );
	
	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_Resp_Item_Sell( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Sell : %d(%d:%d)", 
	//														info.byResult, info.byPlace, info.byIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------������ ĳ�� ��û_���----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_ITEM_CASH( char* pData )
{
	static Msg_Cash info;
	memcpy( &info, pData, sizeof(Msg_Cash) );

	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_Resp_Item_Cash( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Item_Cash : %d", info.nCash );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}


//----------��ũ��/��ų �ʱ�ȭ ���� ��û_���----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Resp_Item_CharacterInitialize( char* pData )
{
	static Msg_NPCCommand info;
	memcpy( &info, pData, sizeof(Msg_NPCCommand) );

	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_Resp_Item_CharacterInitialize( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Msg_NPCCommand %d", info.byResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------- ��ɼ� ����ȭ ������ ��û ��� -------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_Charge_Function_Item( char* pData)
{
	static Msg_Time info;
	memcpy( &info, pData, sizeof(Msg_Time) );

	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_Resp_Charge_Function_Item( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Charge_Function_Item: %d-Time%d",
	//													info.byResult, info.dwTime );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------���λ����� ��û_���----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Resp_Store( char* pData )
{
	static MSG_MobStore info;
	memcpy( &info, pData, sizeof(MSG_MobStore) );
	
	if ( g_cIndividualStore ) g_cIndividualStore->HT_vNetWork_SCP_Resp_Store( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Store : ");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------���λ��� ��ǰ ���� ��û_���----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Resp_Store_Buy( char* pData )
{
	static MSG_MobStore_Buy info;
	memcpy( &info, pData, sizeof(MSG_MobStore_Buy) );
	
	if ( g_cIndividualStore ) g_cIndividualStore->HT_vNetWork_SCP_Resp_Store_Buy( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Store_Buy : ");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�ٸ� ĳ������ ���λ��� ����/�� �κ� ���Ǿ� ����----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Resp_MobStatus( char* pData )
{
	static MSG_MobStatus info;
	memcpy( &info, pData, sizeof(MSG_MobStatus) );
	
	HTint iKeyID = 0;
	if( g_cMainCharacter ) iKeyID = g_cMainCharacter->HT_iMainChar_GetKeyID();
	if( info.nID == iKeyID )
	{
		if ( g_cEquipInventory ) g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info.nRupia );
	}
	else // �ٸ� ĳ������ ���� ���� 
	{
		if ( g_cIndividualStore ) g_cIndividualStore->HT_vNetWork_SCP_Resp_Status( &info );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Status : ID %d ", info.nID);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------NPC���� ������ ������ ��û_���----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_ITEM_CONTRIBUTION( char* pData )
{
	
}

//----------�ſ��� ���� �峳�� ��û_���----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_PRANA_CONTRIBUTION( char* pData )
{
	static S_SCP_RESP_PRANA_CONTRIBUTION info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_PRANA_CONTRIBUTION) );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Prana_Contribution : OK");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- �κ��丮���� ������ ����� -----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_ITEM_REMOVE( char* pData )
{
	static S_SCP_ITEM_REMOVE info;
	memcpy( &info, pData, sizeof(S_SCP_ITEM_REMOVE) );

	// ������ ����
	if ( g_cItemSystem ) g_cItemSystem->HT_vItemSystem_DeleteItem(info.dwKeyID);

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Scp_Item_Remove : %d", info.dwKeyID);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- ���Ǿ� �̵� -----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_MONEY_MOVE( char* pData )
{
	static MSG_Money_Move info;
	memcpy( &info, pData, sizeof(MSG_Money_Move) );

	// ������ ����
	if ( g_cEquipInventory ) g_cEquipInventory->HT_vNetwork_SCP_Resp_Money_Move( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Scp_Money_Move : From:%d,%d To:%d,%d)", 
	//												info.byFromPlace, info.dwFromMoney, info.byToPlace, info.dwToMoney );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//------------������ ����------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_ITEM_REFINING( char* pData )
{
	static S_SCP_RESP_ITEM_REFINING info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_ITEM_REFINING) );
	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_RESP_ITEM_REFINING( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_ItemRefining : %d-%d:%d(�������%d:%d),��:%d", 
	//				info.byResult, info.byPlace, info.byIndex, info.bySubPlace, info.bySubIndex, info.nMoney);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

// ������ �峳 ��û ���
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_ItemContribution( char* pData )
{
	static MSG_ItemContribution info;
	memcpy( &info, pData, sizeof(MSG_ItemContribution) );
	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_Resp_ItemOffering( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_ItemOffering : %d-scale%d,money-%d", 
	//											info.byResult, info.snRefineScale, info.dwRupia );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
// �峳 ������ ��û ���
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_RefineScale( char* pData )
{
	static MSG_RefineScale info;
	memcpy( &info, pData, sizeof(MSG_RefineScale) );
	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_Resp_RefineScale( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_RefineScale : %d", info.snRefineScale );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//			0x22 Group - Exchange
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_TRADE( char* pData )
{
	static S_CSP_REQ_TRADE info;
	memcpy( &info, pData, sizeof(S_CSP_REQ_TRADE) );
	if ( g_cExchangeSystem ) 
	{
		// ��ȯ��û�� �޾��� ��� info.szCharName�� ���� �̸��� �ִ�.
		if ( info.szCharName[0] && g_cExchangeSystem->HT_bExchange_IsExchanging( ) == HT_FALSE ) 
		{
			// ��ȯ�� ��û�� ĳ������ ������ Client ���� ������ ��ġ�ϴ��� �˻�
			if ( g_cOtherObjectSystem && g_cOtherObjectSystem->HT_bOtherObjectSystem_CheckOtherMobForTrade( &info ) )
			{
				g_cExchangeSystem->HT_vNetWork_SCP_Resp_Trade( &info );
			}
		}
		else
			g_cExchangeSystem->HT_vNetWork_SCP_Resp_Trade( &info );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Exchange : ���ID %d", info.OpponentID);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_TRADE_CANCEL( char* pData )
{
	static S_RESULT info;
	memcpy( &info, pData, sizeof(S_RESULT) );
	if ( g_cExchangeSystem ) g_cExchangeSystem->HT_vNetWork_SCP_Resp_Trade_Cancel( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Trade_Cancel : %d", info.nResult);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//---------- ĳ������ ����Ʈ ��� ���� -------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_QUEST_HISTORY( char* pData )
{
	static S_SCP_RESP_QUEST_HISTORY info;
	memcpy( &info, pData, sizeof( S_SCP_RESP_QUEST_HISTORY ) );
	
	if ( g_cQuest ) g_cQuest->HT_vNetWork_SCP_RESP_Quest_History( info.byQuest );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Quest_History ");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------����Ʈ ���� ���� ����-----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_QUEST_DIALOG( char* pData )
{
	static S_SCP_QUEST_DIALOG info;
	memcpy( &info, pData, sizeof(S_SCP_QUEST_DIALOG) );

	if ( g_cQuest ) g_cQuest->HT_vNetWork_SCP_RESP_Quest_Dialog( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Quest_Dialog : %d", info.wIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- ĳ������ ������ ����Ʈ ���� ���� ���� -------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_QUEST_NOTIFY_LEVEL( char* pData )
{
	static S_SCP_QUEST_NOTIFY_LEVEL info;
	memcpy( &info, pData, sizeof(S_SCP_QUEST_NOTIFY_LEVEL) );

	if ( g_sNPCSystem ) g_sNPCSystem->HT_vNetWork_SCP_RESP_Quest_Notify_Level( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Quest_Notify_Level : NPC(%d) %d��(%d lv)", 
																info.snNPCIndex, info.byIndex, info.byLevel );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

// �׽�ũ ����Ʈ ��û ���
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_TaskQuest( char* pData )
{
	static MSG_STANDARDPARM info;
	memcpy( &info, pData, sizeof(MSG_STANDARDPARM) );

	if ( g_cNPCControl ) g_cNPCControl->HT_vNetWork_SCP_Resp_TaskQuest( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_TaskQuest : %d:NPC(%d)", info.Parm, info.nID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//			0x25 Group(GM)
//---------- GM ��带 ���� �Ǵ� ������ ��û�Ѵ�_���-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_GMMode( char* pData )
{
	static MSG_GMMode info;
	memcpy( &info, pData, sizeof(MSG_GMMode) );
    
	if ( g_cGMSystem ) g_cGMSystem->HT_vNetWork_SCP_Resp_GMMode( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_GMMode %d, %x", info.byResult, info.byGMMode);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- GM�� �����带 ���� �Ǵ� ������ ��û�Ѵٸ� �˸���-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_GMmode_NOTIFY( char* pData )
{
	static MSG_GMMode_Notify info;
	memcpy( &info, pData, sizeof(MSG_GMMode_Notify) );

	if( info.nID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		g_oMainCharacterInfo.byGMStatus = info.byGMMode;
		//	���� �����϶�
		if( g_cMainCharacter )	g_cMainCharacter->HT_vMainChar_SetTransparency( g_oMainCharacterInfo.byGMStatus, 0 );
		//	Chat Block check
		if( g_cChatting )		g_cChatting->HT_vChatting_SetChatBlock( g_oMainCharacterInfo.byGMStatus );
	}
	else
	{
		if ( g_cOtherObjectSystem ) g_cOtherObjectSystem->HT_vOtherObjectSystem_GMMode_Notify( info.nID, info.byGMMode );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_GMMode_Notify : %d(ID) %d(GMMode)", info.nID, info.byGMMode );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- Ư����ġ���� ������ ��û�Ѵ�.(��������)_���-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_GMMOVE_POSITION( char* pData )
{
	static MSG_GMMovePosition info;
	memcpy( &info, pData, sizeof(MSG_GMMovePosition) );

	if ( g_cGMSystem ) g_cGMSystem->HT_vNetWork_SCP_Resp_GMMOVE_POSITION( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_GMmove_Position");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- Ư���ɸ��� ��ó���� ������ ��û�Ѵ�_���-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_GMMOVE_NEAR_CHAR( char* pData )
{
	static MSG_GMMoveToPlayer info;
	memcpy( &info, pData, sizeof(MSG_GMMoveToPlayer) );

	//	������ �̵��϶�
	if( info.byZone != g_wResentZoneServerID )
	{
		g_cGMSystem->HT_vNetWork_SCP_Resp_GMMOVE_NEAR_CHAR( &info );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_GMMove_Near_Char");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_APPEAL_CHAT( char* pData )
{
	static S_SCP_RESP_APPEAL_CHAT info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_APPEAL_CHAT) );

	if ( g_cGMSystem ) g_cGMSystem->HT_vNewWork_SCP_RESP_Appeal_Chat( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Appeal_Chat");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- Ư���ɸ��͸� GM ��ó�� ���� ��û�Ѵ�_���-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_CHAR_RECALL( char* pData )
{
	static S_SCP_RESP_CHAR_RECALL info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_CHAR_RECALL) );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Char_Recall");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- Ư����ġ���� ���� ��û�� �˸���-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_CHAR_RECALL_NOTIFY( char* pData )
{
	static S_SCP_CHAR_RECALL_NOTIFY info;
	memcpy( &info, pData, sizeof(S_SCP_CHAR_RECALL_NOTIFY) );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Char_Recall_Notify");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- ä�û���� ����, ���� ��û�Ѵ�_���-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_CONTROL_CHAT( char* pData )
{
	static S_SCP_RESP_CONTROL_CHAT info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_CONTROL_CHAT) );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Control_Chat");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- ä�û���� ����, ������ �˸���.-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_CONTROL_CHAT_NOTIFY( char* pData )
{
	static S_CSP_CONTROL_CHAT_NOTIFY info;
	memcpy( &info, pData, sizeof(S_CSP_CONTROL_CHAT_NOTIFY) );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Control_Char_Notify");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- Ư���ɸ����� ���۸����� ��û�Ѵ�_���-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_CONTROL_ACTION( char* pData )
{
	static S_SCP_RESP_CONTROL_ACTION info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_CONTROL_ACTION) );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Control_Action");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- GM�ɸ��Ϳ����� ���۸����� �˸���_���-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_CONTROL_ACTION_NOTIFY( char* pData )
{
	static S_SCP_CONTROL_ACTION_NOTIFY info;
	memcpy( &info, pData, sizeof(S_SCP_CONTROL_ACTION_NOTIFY) );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Control_Action_Notify");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------������ �Ű����� �����Ѵ�.-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_TROUBLE_REPORT( char* pData )
{
	static S_SCP_RESP_TROUBLE_REPORT info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_TROUBLE_REPORT) );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Trouble_Report");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�ڽ��� �Ű��� �Ű����� ����Ʈ�� �޴´�.-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_TROUBLE_REPORT_LIST( char* pData )
{
	static S_SCP_RESP_TROUBLE_REPORT_LIST info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_TROUBLE_REPORT_LIST) );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Trouble_Report_List");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�ڽ��� �Ű��� �Ű����� ����Ʈ�� �޴´�.-------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_TROUBLE_REPORT_SET( char* pData )
{
	static S_SCP_RESP_TROUBLE_REPORT_SET info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_TROUBLE_REPORT_SET) );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Trouble_Report_Set");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�ٸ�ĳ������ ������ �޴´�.----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_CHAR_INFO( char* pData )
{
	static S_SCP_RESP_CHAR_INFO info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_CHAR_INFO) );

	if ( g_cGMSystem ) g_cGMSystem->HT_vNetWork_SCP_RESP_CHAR_INFO( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Char_Info");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------�ٸ�ĳ������ ��ų������ �޴´�.----------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_CHAR_SKILL( char* pData )
{
	static S_SCP_RESP_CHAR_SKILL info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_CHAR_SKILL) );

	if ( g_cGMSystem ) g_cGMSystem->HT_vNetWork_SCP_RESP_CHAR_SKILL( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Char_Skill");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RESP_CLOSE_CHAR( char* pData )
{
	static S_SCP_RESP_CLOSE_CHAR info;
	memcpy( &info, pData, sizeof(S_SCP_RESP_CLOSE_CHAR) );

	if ( g_cGMSystem ) g_cGMSystem->HT_vNetWork_SCP_RESP_CLOSE_CHAR( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Close_Char");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------- ���� ��û�� ���--------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Resp_Change_Job( char* pData )
{
	static MSG_CLASS info;
	memcpy( &info, pData, sizeof(MSG_CLASS) );

	if ( g_cNPCControl ) g_cNPCControl->HT_vNetwork_SCP_Resp_Change_Job( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Change_Job: %d-%d, %d", 
	//														info.nID, info.byClass1, info.byClass2 );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------- ��Ƽ �й��� ���� --------------//
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Resp_Set_Party( char* pData )
{
	static MSG_SetParty info;
	memcpy( &info, pData, sizeof(MSG_SetParty) );

	if ( g_cParty ) g_cParty->HT_vNetWork_SCP_Resp_Set_Party( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Set_Party: %d-%d", info.byResult, info.byRootingMode );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Event
//	Fire Fx Broadcast
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_FireFxBroadcast( char* pData )
{
	static S_SCP_FIRE_FX_BROADCAST info;
	memcpy( &info, pData, sizeof(S_SCP_FIRE_FX_BROADCAST) );

	if( info.dwKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		g_cMainCharacter->HT_vMainChar_SCP_FireFxBroadcast( &info );
	}
	else
	{
		g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkFireFxBroadcast( &info );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_SCP_FireFxBroadcast" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Beauty( char* pData )
{
	static MSG_Beauty info;
	memcpy( &info, pData, sizeof(MSG_Beauty) );

	if ( g_cStatus ) g_cStatus->HT_vStatus_NetworkReciveBeauty( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Beauty: %d", info.byResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Duel System
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Challenger( char* pData )
{
	static Msg_Challenger info;
	memcpy( &info, pData, sizeof(Msg_Challenger) );

	if ( g_pDuelSystem ) g_pDuelSystem->HT_vDuelNet_SCP_Challenger( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_Duel: %d", info.byMode );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	�ƽ�������
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_AshuramGuild( char* pData )
{
	static Msg_GuildAlliance info;
	memcpy( &info, pData, sizeof(Msg_GuildAlliance) );

	if ( g_cGuildSystem ) g_cGuildSystem->HT_vGuildNet_SCP_AshuramGuild( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Resp_AshuramGuild: Result = %d, Type = %d, Act = %d, Result = %d", info.byResult, info.byType, info.byAct, info.byResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Assist Change Target
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_ChangeTarget( char* pData )
{
	static MSG_CHANGE_TARGET info;
	memcpy( &info, pData, sizeof(MSG_CHANGE_TARGET) );

	g_cCommand->HT_vCommand_NetReciveAssist( info.snTarget );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Target: %d", info.snTarget );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Version Check
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_VersionCheck( char* pData )
{
	static MSG_STANDARD info;
	memcpy( &info, pData, sizeof(MSG_STANDARD) );

	if( info.nID != 0 )
	{
		CHTString szMessage;
		// ������ ������ ���������ϴ�. ����� �ٽ� ������ �ֽʽÿ�!
		if( g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
		{
			if( g_iGameSequnce == 1 )
				g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
			else
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		}
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Satndard: %d", info.nID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Billing Status
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_BillingStatus( char* pData )
{
	static Msg_BillStatus info;
	memcpy( &info, pData, sizeof(Msg_BillStatus) );

	//	����� ������ �Ⱓ�� ����Ǿ����ϴ�.
	if( info.nCommand == 1 )
	{
		//	���� ������ ���� ����
		g_pNetWorkMgr->DisConnect();
		//  ���� ���� ���� ���
		g_bReciveBillingServer = HT_FALSE;

		CHTString szMessage;
		if( g_iGameSequnce == 1 )
		{
			if (g_cIntroManager)
			{
				if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgCommonNoGameTime, &szMessage ) == true )
					g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
			}
		}
		else
		{
			if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgCommonNoGameTime, &szMessage ) == true )
				g_cGameSystem->HT_vGameSystem_ServerDisConnect_SetDlg( szMessage );
		}
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_BillStatus: %d", info.nCommand );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_GameEvent( char* pData )
{
	static Msg_GameEvent info;
	memcpy( &info, pData, sizeof(Msg_GameEvent) );

//	i.	��÷ �޼��� (info.byResult)
//	0.	�˼��մϴ�. 7���̸� ��ǰ�� �����ϴ�. ���� ��ȸ�� �̿����ּ���
//	1.	��COMRADE(�ĸ���) GeForce 6600 3.3ns�׷��� ī�� �� 1� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.
//	2.	��Ÿ�Ͼ� �� 2� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.
//	3.	��Ÿ�� �� 3� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.
//	4.	���� �� 4� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.
//	5.	����� �� 5� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.
//	6.	���Ʊ�� �� 6� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.

	g_pEventWindow->HT_vEventWnd_ReciveMsgGameEvent( &info );

	//CHTString strString;
	//
	//switch(info.byResult)
	//{
	//case 0:
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "�˼��մϴ�. 7���̸� ��ǰ�� �����ϴ�. ���� ��ȸ�� �̿����ּ���");
	//	break;
	//case 1:
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "��COMRADE(�ĸ���) GeForce 6600 3.3ns�׷��� ī�� �� 1� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.");
	//	break;
	//case 2:
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "��Ÿ�Ͼ� �� 2� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.");
	//	break;
	//case 3:
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "��Ÿ�� �� 3� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.");
	//	break;
	//case 4:
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "���� �� 4� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.");
	//	break;
	//case 5:
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "����� �� 5� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.");
	//	break;
	//case 6:
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "���Ʊ�� �� 6� ��÷�Ǽ̽��ϴ�. �������� ���� �帳�ϴ�. źƮ�� Ȩ������ �̺�Ʈ ������ �������ֽñ� �ٶ��ϴ�.");
	//	break;
	//default:
	//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "�˼��մϴ�. 7���̸� ��ǰ�� �����ϴ�. ���� ��ȸ�� �̿����ּ���");
	//	break;
	//}
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_GameEvent: result = %d", info.byResult);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Msg Alarm
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Alarm( char* pData )
{
	static Msg_Alarm info;
	memcpy( &info, pData, sizeof(Msg_Alarm) );

	if( info.dwClientTick == 1 )
	{
		// �Ҹ� ����
		g_pEngineHandler->HT_hrPlaySound( 33529, 3 );
	}
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MsgAlarm : %d", info.unType );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Warp
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Warp( char* pData )
{
	static MSG_Warp info;
	memcpy( &info, pData, sizeof(MSG_Warp) );

	g_cPortal->HT_vPortal_NetWork_SCP_Msg_Warp( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_Warp : %d", info.dwPlace );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Echo
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Echo( char* pData )
{
	static Msg_Echo info;
	memcpy( &info, pData, sizeof(Msg_Echo) );

	g_cGameSystem->HT_vGameSystem_ReciveAnswerUseSamudaba( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_MSG_Echo : %d", info.iEchoID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	YutMove
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_YutMove( char* pData )
{
	static Msg_YutMove info;
	memcpy( &info, pData, sizeof(Msg_YutMove) );


	g_cOtherObjectSystem->HT_vOtherObjectSystem_NetWorkYutMove( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Msg_YutMove : %d", info.wToIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

// YutMyMoney
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_YutMyMoney( char* pData )
{
	static Msg_YutMyMoney info;
	memcpy( &info, pData, sizeof(Msg_YutMyMoney) );

	if (g_cGamble)
	g_cGamble->HT_vGamble_NetWorkYutMyMoney( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Msg_YutMyMoney" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

// YutStatus
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_YutStatus( char* pData )
{
	static Msg_YutStatus info;
	memcpy( &info, pData, sizeof(Msg_YutStatus) );
	
	if (g_cGamble)
	g_cGamble->HT_vGamble_NetWorkYutStatus( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Msg_YutStatus ");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

// YutBet
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_YutBet( char* pData )
{
	static Msg_YutBet info;
	memcpy( &info, pData, sizeof(Msg_YutBet) );

	if (g_cGamble)
	g_cGamble->HT_vGamble_NetWorkYutBet( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Msg_YutBet : Result = %d", info.byResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

// YutGetMoney
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_YutGetMoney( char* pData )
{
	static Msg_YutGetMoney info;
	memcpy( &info, pData, sizeof(Msg_YutGetMoney) );

	if (g_cGamble)
		g_cGamble->HT_vGamble_NetWorkYutGetMoney( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Msg_YutGetMoney : Result = %d", info.byResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Zone Setting
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_ZoneSetting( char* pData )
{
	static MSG_SET_ZONE_SETTINGS info;
	memcpy( &info, pData, sizeof(MSG_SET_ZONE_SETTINGS) );

	g_snResentZoneSiege = info.snSiege;
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Msg_ZoneSiege : %d", info.snSiege );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Change Trimuriti ID
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_ChangeTrimuritiID( char* pData )
{
	static MSG_CHANGE_TRIMURITI info;
	memcpy( &info, pData, sizeof(MSG_CHANGE_TRIMURITI) );

	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTrimuritiD( info.snKeyID, info.byTrimuriti );
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting( info.snKeyID );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Msg_ChangeTrimuritiID : ID:%d, Tri:%d", info.snKeyID, info.byTrimuriti );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	State_of_the_siege
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_StateOfSiege( char* pData )
{
	static MSG_STATE_OF_THE_SIEGE info;
	memcpy( &info, pData, sizeof(MSG_STATE_OF_THE_SIEGE) );

	g_pSiege->HT_vSiege_NetworkSCPStateOfTheSiege( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Msg_StateOfSiege Mark:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
	//	info.irgClan[0],info.irgClan[1],info.irgClan[2],info.irgClan[3],info.irgClan[4],info.irgClan[5],
	//	info.irgClan[6],info.irgClan[7],info.irgClan[8],info.irgClan[9],info.irgClan[10]);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	State_Siege Entry
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_SiegeEntry( char* pData )
{
	static MSG_SIEGE_ENTRY info;
	memcpy( &info, pData, sizeof(MSG_SIEGE_ENTRY) );

	g_pSiege->HT_vSiege_NetworkSiegeEntry( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Msg_SiegeEntry" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	MSG_FIX_DATE_OF_SIEGE 
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_FixDataOfSiege( char* pData )
{
	static MSG_FIX_DATE_OF_SIEGE info;
	memcpy( &info, pData, sizeof(MSG_FIX_DATE_OF_SIEGE) );

	g_pSiege->HT_vSiege_NetworkSCP_FixDataOfSiege( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Msg_FixDataOfSiege" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Msg_SetSalesRate
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_SetSalesRate( char* pData )
{
	static Msg_SetSalesRate info;
	memcpy( &info, pData, sizeof(Msg_SetSalesRate) );

	g_pSiege->HT_vSiege_NetworkSCP_SetSalesRate( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Msg_SetSalesRate" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//	Msg_GetMoney
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_GetMoney( char* pData )
{
	static Msg_GetMoney info;
	memcpy( &info, pData, sizeof(Msg_GetMoney) );

	g_pSiege->HT_vSiege_NetworkSCP_GetMoney( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Msg_GetMoney" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//	MSG_ChangeClanID
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_ChangeClanID( char* pData )
{
	static MSG_CHANGE_CLAN info;
	memcpy( &info, pData, sizeof(MSG_CHANGE_CLAN) );

	g_cMainCharacter->HT_vMainChar_SetClanValue( info.byClan );
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Change Clan IDe : byClan:%d", info.byClan );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//	MSG__APPLY_SIEGE_ID
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_Apply_Siege_ID( char* pData )
{
	static MSG_APPLY_SIEGE info;
	memcpy( &info, pData, sizeof(MSG_APPLY_SIEGE) );

	g_pSiege->HT_vSiege_NetworkSCP_ApplySiege( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Msg_Apply_Siege : byClanSlot:%d, byExpandSlot:%d, snResult:", info.byClanSlot, info.byExpandSlot, info.snResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//	Msg Castle Init
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_CastleInit( char* pData )
{
	static Msg_CastleInit info;
	memcpy( &info, pData, sizeof(Msg_CastleInit) );

	g_pSiege->HT_vSiege_NetworkSCP_SetCastle( info.iCastleOwner );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Msg_CastleInit : Owner:", info.iCastleOwner );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//	Msg Castle Update
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_CastleUpdate( char* pData )
{
	static Msg_CastleUpdate info;
	memcpy( &info, pData, sizeof(Msg_CastleUpdate) );

	g_pSiege->HT_vSiege_NetworkSCP_SetCastle( info.iCastleOwner );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Msg_CastleInit : Owner:", info.iCastleOwner );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	Ahsram Cargo
//	Msg_GuildCargoUsingLevel
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_GuildCargoUsingLevel( char* pData )
{
	static Msg_GuildCargoUsingLevel info;
	memcpy( &info, pData, sizeof(Msg_GuildCargoUsingLevel) );

	g_cGuildSystem->HT_vAshram_SCPSetLevelAshramCargo( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive Msg_GuildCargoUsingLevel %d, %d, %d", info.byCargoLevel[0], info.byCargoLevel[1], info.byCargoLevel[2] );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//	Msg_GuildCargoTimeExtension
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_GuildCargoTimeExtension( char* pData )
{
	static Msg_GuildCargoTimeExtension info;
	memcpy( &info, pData, sizeof(Msg_GuildCargoTimeExtension) );

	g_cGuildSystem->HT_vAshram_SCPGuildCargoTimeExtension( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Msg_GuildCargoTimeExtension : %d", info.byResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//	Msg_GuildCargoTime
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_GuildCargoTime( char* pData )
{
	static Msg_GuildCargoTime info;
	memcpy( &info, pData, sizeof(Msg_GuildCargoTime) );

	g_cGuildSystem->HT_vAshram_SCPGuildCargoTime( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive Guild Cargo Time" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//	Msg_GuildItem
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_GuildItem( char* pData )
{
	static Msg_GuildItem info;
	memcpy( &info, pData, sizeof(Msg_GuildItem) );

	g_cGuildSystem->HT_vAshram_SCPAshramItem( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive Guild Item" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
//	Msg_GuildItemUpdate
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_GuildItemUpdate( char* pData )
{
	static Msg_GuildItemUpdate info;
	memcpy( &info, pData, sizeof(Msg_GuildItemUpdate) );

	g_cGuildSystem->HT_vAshram_SCPGuildItemUpdate( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive Guild Item Update : From%d, To:%d", info.nFromIndex, info.nToIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	
}


//
// ��Ź ���� ��Ŷ
//
//	**  Rental Stroe  **  /////////////////////////////////////////////////////////

// Msg_MyRentalItemList :		
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_MyRentalItemList( char* pData )		// ���� ��Ź ������ ����Ʈ�� ��û ����
{
	static Msg_MyRentalItemList info;
	memcpy( &info, pData, sizeof(Msg_MyRentalItemList) );

	g_cRentalStore->HT_vRentalStore_SCP_MyRentalItemList( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive RentalStore MyRentalItemList");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	
}

// Msg_RentalItemList :			
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RentalItemList( char* pData )			// Ư�� ��Ź������ �����۸���Ʈ ��û ����
{
	static Msg_RentalItemList info;
	memcpy( &info, pData, sizeof(Msg_RentalItemList) );

	g_cRentalStore->HT_vRentalStore_SCP_RentalItemList( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive RentalStore RentalItemList : Store ID:%d", info.dwStoreIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	
}

// Msg_RentalItemAdd :			
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RentalItemAdd( char* pData )			// �������� ��Ź�� ����
{
	static Msg_RentalItemAdd info;
	memcpy( &info, pData, sizeof(Msg_RentalItemAdd) );

	g_cRentalStore->HT_vRentalStore_SCP_RentalItemAdd( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive RentalStore RentalItemAdd : Result:%d, StoreID:%d, Hour:%d, InvenID:%d, Money:%d ", info.byResult, info.dwStoreIndex, info.byHour, info.dwIndex, info.dwMoney );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	
}

// Msg_RentalItemCancel :		
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RentalItemCancel( char* pData )		// ��Ź�� �������� ��� ����
{
	static Msg_RentalItemCancel info;
	memcpy( &info, pData, sizeof(Msg_RentalItemCancel) );

	g_cRentalStore->HT_vRentalStore_SCP_RentalItemCancel( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive RentalStore RentalItemCancel : Result:%d, StoreID:%d, SInvenID:%d", info.byResult, info.dwStoreIndex, info.dwIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	
}

// Msg_RentalGetMoney :			
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RentalGetMoney( char* pData )			// ����� ���� �� ã�� ����
{
	static Msg_RentalGetMoney info;
	memcpy( &info, pData, sizeof(Msg_RentalGetMoney) );

	g_cRentalStore->HT_vRentalStore_SCP_RentalGetMoney( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive RentalStore RentalGetMoney : Type:%d, Money:%d", info.byType, info.dwMoney );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	
}

// Msg_RentalGetItem :			
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RentalGetItem( char* pData )			// ����� �� ��ǰ ã�� (�Ⱓ ���� �����۵�) ����
{
	static Msg_RentalGetItem info;
	memcpy( &info, pData, sizeof(Msg_RentalGetItem) );

	g_cRentalStore->HT_vRentalStore_SCP_RentalGetItem( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive RentalStore RentalGetItem ");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	
}

// Msg_RentalTex :				
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RentalTex( char* pData )				// ��Ź������ ���� ���� ����
{
	static Msg_SetRentalTex info;
	memcpy( &info, pData, sizeof(Msg_SetRentalTex) );

	g_cRentalStore->HT_vRentalStore_SCP_RentalTex( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive RentalStore RentalTex : Tex:%d", info.byTex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	
}

// Msg_RentalStoreClose :		
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RentalStoreClose( char* pData )		// ��Ź���� ���ְ� �ݱ� ����
{
	static Msg_RentalStoreClose info;
	memcpy( &info, pData, sizeof(Msg_RentalStoreClose) );

	g_cRentalStore->HT_vRentalStore_SCP_RentalStoreClose( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive RentalStore RentalStoreClose : Result:%d, StoreID:%d", info.byResult, info.dwStore );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	
}

// Msg_RentalItemBuy :			
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RentalItemBuy( char* pData )			// ��Ź�������� ������ ���� ����
{
	static Msg_RentalItemBuy info;
	memcpy( &info, pData, sizeof(Msg_RentalItemBuy) );

	g_cRentalStore->HT_vRentalStore_SCP_RentalItemBuy( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive RentalStore RentalItemBuy : Result:%d, StoreID:%d, SInvenID:%d, InvenMoney:%d", info.byResult, info.dwStoreIndex, info.dwIndex, info.dwMoney);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

/*
// Msg_RentalStockItem :		
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RentalStockItem( char* pData )		// ������ �������۸���Ʈ�� ��û�Ѵ�. ����
{
	static Msg_RentalStockItem info;
	memcpy( &info, pData, sizeof(Msg_RentalStockItem) );

	g_cRentalStore->HT_vRentalStore_SCP_RentalStockItem( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive RentalStore RentalStockItem" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	
}
*/

// Msg_RentalStockItemList :		
HTvoid CHTNetWorkHandle::HT_vNetWork_SCP_RentalStockItemList( char* pData )		// ������ �������۸���Ʈ�� ��û�Ѵ�. ����
{
	static Msg_RentalStockItemList info;
	memcpy( &info, pData, sizeof(Msg_RentalStockItemList) );

	g_cRentalStore->HT_vRentalStore_SCP_RentalStockItemList( &info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive RentalStore RentalStockItemList" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;	
}

HTvoid CHTNetWorkHandle::HT_vNetwork_SCP_Who( char *pData ) // Bot ������ ��ȣ ���� ��Ŷ ����
{
	static Msg_Who info;
	memcpy( &info, pData, sizeof(Msg_Who) );
    g_cCPSock.m_byWhoCount = 20;
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive Who Message" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
HTvoid CHTNetWorkHandle::HT_vNetwork_SCP_Quiz( char *pData )	//	�׾߸��� ����
{
	static Msg_Quiz info;
	memcpy( &info, pData, sizeof(Msg_Quiz) );

	g_cGameSystem->HT_vGameSystem_SCP_Quiz( &info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive Quiz Answer:%s,1:%s,2:%s,3:%s,4:%s", info.pszQuiz, info.pszQuizSelect1[0], info.pszQuizSelect1[1], info.pszQuizSelect1[2], info.pszQuizSelect1[3] );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}
