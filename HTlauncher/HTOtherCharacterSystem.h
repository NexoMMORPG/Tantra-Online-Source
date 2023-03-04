
#ifndef __HTOTHERCHARACTERSYSTEM_H__
#define __HTOTHERCHARACTERSYSTEM_H__

#include "HTOtherCharacter.h"


//----------몬스터 LL 구현을 위한 구조체----------//
typedef struct _HT_OTHERCHARACTER_NODE
{
	HTOtherCharacter					sOtherCharacter;
	struct _HT_OTHERCHARACTER_NODE		*next;

} HT_OTHERCHARACTER_NODE;


#define CHATMSGDELAYTIME				5000

//----------다른 캐릭터 전체 시스템과 LL을 실제 구현----------//
class HTOtherCharacterSystem
{
public:
	HTOtherCharacterSystem();
	~HTOtherCharacterSystem();
	HTvoid						HT_vOtherCharSystem_CleanUp();


	HTRESULT					HT_hOtherCharSystemInit();
	HTvoid						HT_vOtherCharSystemUpdate();
	
	HTvoid						HT_vOtherCharSystemControl( HTfloat fElapsedTime );			//	컨트롤
	HTvoid						HT_vOtherCharSystemImsiKeyInput();

	//----------전 OtherChar 삭제--------//
	HTvoid						HT_vecOtherCharSystem_TotalCharDelete();

	//----------OtherChar를 픽했을때---------//
	DWORD						HT_iOtherCharSystemComIDCheck( HTint iID );
	//----------OtherCharSystem 정보창 초기화---------//
	HTvoid						HT_vOtherCharacterSystem_HPWindowInit();

	//----------셀에 위치한 캐릭터가 있는가?---------//
	DWORD						HT_dOtherCharSystem_CheckMapCell( HTint iMapCellX, HTint iMapCellZ );
	//----------AOI 영역 체크----------//
	HTvoid						HT_vOtherCharSystem_AOI_Check( HT_OTHERCHARACTER_NODE *t );
	
	//----------셋팅하기---------//
	HTvoid						HT_vOtherCharSystem_SetShowName();
	//	채팅 메시지 보여주기
	HTvoid						HT_vOtherCharSystem_SetShowChatMsg();
	HTbool						HT_bOtherCharSystem_GetShowChatMsg()	{ return m_bOtherChar_ChatMsgShowSw;};
	
	//----------반환값---------//
	DWORD						HT_dOtherCharSystem_GetModelID( DWORD iKeyID );
	DWORD						HT_dOtherCharSystem_GetKeyID( HTint iImageID );
	HTbyte						HT_dOtherCharSystem_byGetLevel( HTint iKeyID );
	//----------키이이디로 이름을 얻어온다.---------//
	CHTString					HT_strOtherCharSytem_GetName( DWORD dwkeyID );
	//----------모델아이디로 이름을 얻어온다---------//
	CHTString					HT_strOtherCharSytem_GetNamebyModelID( DWORD dwModelID );

	HTPoint						HT_dOtherCharSystem_GetCellPos( DWORD dKeyID );
	HTPoint						HT_dOtherCharSystem_GetCellPosbyModelID( HTint iImageID );
	HTvector3					HT_vecOtherCharSystem_GetAtkTargetCheck( DWORD, HTint, DWORD );	//	내가 공격대상인지 파악
	HTvector3					HT_vecOtherCharSystem_GetCoordPos( DWORD );
	//	셀좌표로 캐릭터 키아디를 알아온다
	HTint						HT_iOtherCharSystem_GetKeyIDFromCell( short, short, HTvector3* );

	//----------모델아이디로 현재 위치 얻어온다--------//
	HTvector3					HT_vecOtherCharSystem_GetCoordPosbyModelID( DWORD dwModelID );

	//-----------픽된 상태인가 체크----------//
	HTRESULT					HT_hrOtherCharSystem_GetInfoStatus( HTint );

	//----------그려주기---------//
	HTvoid						HT_OtherCharSystem_Render();
	HTvoid						HT_vOtherCharSystem_RenderName( HT_OTHERCHARACTER_NODE* t );

    //---------공격 관련----------//
	//---------공격 받았을 때_맞는 액션 온----------//
	HTvoid						HT_vOtherCharSystem_SetDisAttackOn( DWORD, DWORD, BYTE, HTint iItemIndex );
	//----------아이템 사용 이펙트 셋팅----------//
	HTvoid						HT_vOtherCharSystem_SetItemUseEffect( DWORD );
	//---------HP 변경사항 체크, byReturnType:0x00:현재HP,0x01:맞은HP----------//
	HTint						HT_nOtherCharacterSystem_GetHPCheck( DWORD dwKeyID, HTint nHP, BYTE byReturnType );
	//---------액티브 이펙트를 받았을 때----------//
	HTvoid						HT_vOtherCharSystem_SetActiveEffectOn( DWORD dwKeyID, DWORD dwSkillIndex, HTbool bType, BYTE byLevel );

	//----------서버 데이타 체크하여 처리---------//
	HTRESULT					HT_hrOtherCharSystem_Insert( PS_SCP_INIT_OTHER_MOB info );
	HTvoid						HT_vOtherCharSystem_NetWork_Action_Brodcast( MSG_Action* info );
	HTvoid						HT_vOtherCharSystem_NewWork_RemoveMob( PS_SCP_RESP_REMOVE_MOB info );
	HTvoid						HT_vOtherCharSystem_ItemEquipmentBrodcast( PS_SCP_RESP_EQUIP_SET );
	HTvoid						HT_vOtherCharSystem_LevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST );

	HTvoid						HT_vOtherCharSystem_NetWork_Skill_Ready_Char_Broadcast( PS_SCP_SKILL_READY_CHAR_BROADCAST );
	HTvoid						HT_vOtherCharSystem_NetWork_Death( PS_SCP_CHAR_MONSTER_DEATH_BROADCAST info );
	HTvoid						HT_vOtherCharSystem_NetWork_ChattingMessage( DWORD dwKeyID, BYTE byType, CHTString strMessage );
	HTvoid						HT_vOtherCharSystem_Network_Skill_Unit_Skill_Broadcast( PS_CSP_CAST_UNIT_SKILL info );
	HTvoid						HT_vOtherCharSystem_Network_Skill_Area_Skill_Broadcast( PS_CSP_CAST_AREA_SKILL info );
    //-----------스킬 셋팅----------//
	HTvoid						HT_vOtherCharSystem_SetActiveSkill( PS_SCP_RESP_SKILL_SELECT_BROADCAST info );
	HTvoid						HT_vOtherCharSystem_ActiveSkillEffectOn();
	HTvoid						HT_vOtherCharSystem_ActiveSkillEffectOff();
	//	길드 마크 셋팅 하기
	HTvoid						HT_vOtherCharSystem_SetGuildMarkID( CHTString strName, HTint iGuildMark );
	//	길드 마크 표현 하기/안하기
	HTvoid						HT_vOtherCharSystem_GuildEmblemOn();
	HTvoid						HT_vOtherCharSystem_GuildEmblemOff();
	//	주신 셋팅 하기
	HTvoid						HT_vOtherCharSystem_SetTrimuritiD( CHTString strName, BYTE byTrimuritii );
	//	주신 마크 표현 하기
	HTvoid						HT_vOtherCharSystem_TrimuritiMarkOn();
	//	주신 마크 표현 안하기
	HTvoid						HT_vOtherCharSystem_TrimuritiMarkOff();


	//-----------파티원으로서 가입 및 탈퇴할때----------//
	HTvoid						HT_vOtherChar_SetPartyJoineDisband( CHTString, BYTE );
	//-----------아이템 소모로 사라짐-------------//
	HTvoid						HT_vOtherCharSystem_NetWork_ItemAbrasionBroadcast(PS_SCP_ITEM_ABRASION_BROADCAST info);

	//----------이닛브로드캐스트 받지못했을때 OtherChar를 보정해주기 위해---------//
	HTvoid						HT_vOtherCharSystem_NetWork_RequestInitOtherChar( DWORD dwKeyID );

	//---------- GM의 투명모드를 설정 또는 해제를 요청한다를 알린다-------------//
	HTvoid						HT_vOtherCharSystem_NetWork_SCP_TRANSPARENCY_MODE_NOTIFY( PS_SCP_TRANSPARENCY_MODE_NOTIFY info );

	HTvector3					HT_vOtherCharSystem_GetAttackPos( DWORD dwTargetKeyID, DWORD dwSkillIndex, BYTE* byTargetType, HTint* iTargetModelID );

	//---------현재 타겟창에 정보가 보여지고 있는 캐릭터의 모델 ID 반환-------------//
	DWORD						HT_dwOtherCharacterSystem_GetTargetModelID();
	//-----------파티 가입/탈퇴를 셋팅-------------//
	HTvoid						HT_vOtherCharSystem_SetPartyJoin( CHTString, HTbool );
	HTRESULT					HT_hrOtherCharSystem_CompareGuild( HTint iKeyID, HTint iGuildMark );
	//	PS_SCP_RESP_UPDATE_STATUS Setting
	HTvoid						HT_vOtherCharSystem_SCPRespUpdateStatus( PS_SCP_RESP_UPDATE_STATUS info );
	//	동작 멈추기
	HTvoid						HT_vOtherCharSystem_SetStop( HTint );
	

private:
	HTvoid						HT_LL_vInitList();
	HTRESULT					HT_LL_hrDeleteNode( int );
	HTRESULT					HT_LL_hrInsertAfter( PS_SCP_INIT_OTHER_MOB info );
	HTvoid						HT_LL_hrDeleteAll();


public:
	HTint						m_iOtherChar_IndexCount;

	PS_SCP_OTHER_CHAR_MOVE		m_SCP_OTHER_CHAR_MOVE;

	//----------OtherChar 정보 표시위해----------//
	HTbool						m_nOtherChar_HPInfo_Sw;

	
private:
	HT_OTHERCHARACTER_NODE*		m_sOtherCharHead;
	HT_OTHERCHARACTER_NODE*		m_sOtherCharTail;

	//	이름 보여주기
	HTbool						m_bOtherChar_NameShowSw;
	//	채팅 메시지 보여주기
	HTbool						m_bOtherChar_ChatMsgShowSw;

};

#endif

