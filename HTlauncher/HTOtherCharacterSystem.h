
#ifndef __HTOTHERCHARACTERSYSTEM_H__
#define __HTOTHERCHARACTERSYSTEM_H__

#include "HTOtherCharacter.h"


//----------���� LL ������ ���� ����ü----------//
typedef struct _HT_OTHERCHARACTER_NODE
{
	HTOtherCharacter					sOtherCharacter;
	struct _HT_OTHERCHARACTER_NODE		*next;

} HT_OTHERCHARACTER_NODE;


#define CHATMSGDELAYTIME				5000

//----------�ٸ� ĳ���� ��ü �ý��۰� LL�� ���� ����----------//
class HTOtherCharacterSystem
{
public:
	HTOtherCharacterSystem();
	~HTOtherCharacterSystem();
	HTvoid						HT_vOtherCharSystem_CleanUp();


	HTRESULT					HT_hOtherCharSystemInit();
	HTvoid						HT_vOtherCharSystemUpdate();
	
	HTvoid						HT_vOtherCharSystemControl( HTfloat fElapsedTime );			//	��Ʈ��
	HTvoid						HT_vOtherCharSystemImsiKeyInput();

	//----------�� OtherChar ����--------//
	HTvoid						HT_vecOtherCharSystem_TotalCharDelete();

	//----------OtherChar�� ��������---------//
	DWORD						HT_iOtherCharSystemComIDCheck( HTint iID );
	//----------OtherCharSystem ����â �ʱ�ȭ---------//
	HTvoid						HT_vOtherCharacterSystem_HPWindowInit();

	//----------���� ��ġ�� ĳ���Ͱ� �ִ°�?---------//
	DWORD						HT_dOtherCharSystem_CheckMapCell( HTint iMapCellX, HTint iMapCellZ );
	//----------AOI ���� üũ----------//
	HTvoid						HT_vOtherCharSystem_AOI_Check( HT_OTHERCHARACTER_NODE *t );
	
	//----------�����ϱ�---------//
	HTvoid						HT_vOtherCharSystem_SetShowName();
	//	ä�� �޽��� �����ֱ�
	HTvoid						HT_vOtherCharSystem_SetShowChatMsg();
	HTbool						HT_bOtherCharSystem_GetShowChatMsg()	{ return m_bOtherChar_ChatMsgShowSw;};
	
	//----------��ȯ��---------//
	DWORD						HT_dOtherCharSystem_GetModelID( DWORD iKeyID );
	DWORD						HT_dOtherCharSystem_GetKeyID( HTint iImageID );
	HTbyte						HT_dOtherCharSystem_byGetLevel( HTint iKeyID );
	//----------Ű���̵�� �̸��� ���´�.---------//
	CHTString					HT_strOtherCharSytem_GetName( DWORD dwkeyID );
	//----------�𵨾��̵�� �̸��� ���´�---------//
	CHTString					HT_strOtherCharSytem_GetNamebyModelID( DWORD dwModelID );

	HTPoint						HT_dOtherCharSystem_GetCellPos( DWORD dKeyID );
	HTPoint						HT_dOtherCharSystem_GetCellPosbyModelID( HTint iImageID );
	HTvector3					HT_vecOtherCharSystem_GetAtkTargetCheck( DWORD, HTint, DWORD );	//	���� ���ݴ������ �ľ�
	HTvector3					HT_vecOtherCharSystem_GetCoordPos( DWORD );
	//	����ǥ�� ĳ���� Ű�Ƶ� �˾ƿ´�
	HTint						HT_iOtherCharSystem_GetKeyIDFromCell( short, short, HTvector3* );

	//----------�𵨾��̵�� ���� ��ġ ���´�--------//
	HTvector3					HT_vecOtherCharSystem_GetCoordPosbyModelID( DWORD dwModelID );

	//-----------�ȵ� �����ΰ� üũ----------//
	HTRESULT					HT_hrOtherCharSystem_GetInfoStatus( HTint );

	//----------�׷��ֱ�---------//
	HTvoid						HT_OtherCharSystem_Render();
	HTvoid						HT_vOtherCharSystem_RenderName( HT_OTHERCHARACTER_NODE* t );

    //---------���� ����----------//
	//---------���� �޾��� ��_�´� �׼� ��----------//
	HTvoid						HT_vOtherCharSystem_SetDisAttackOn( DWORD, DWORD, BYTE, HTint iItemIndex );
	//----------������ ��� ����Ʈ ����----------//
	HTvoid						HT_vOtherCharSystem_SetItemUseEffect( DWORD );
	//---------HP ������� üũ, byReturnType:0x00:����HP,0x01:����HP----------//
	HTint						HT_nOtherCharacterSystem_GetHPCheck( DWORD dwKeyID, HTint nHP, BYTE byReturnType );
	//---------��Ƽ�� ����Ʈ�� �޾��� ��----------//
	HTvoid						HT_vOtherCharSystem_SetActiveEffectOn( DWORD dwKeyID, DWORD dwSkillIndex, HTbool bType, BYTE byLevel );

	//----------���� ����Ÿ üũ�Ͽ� ó��---------//
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
    //-----------��ų ����----------//
	HTvoid						HT_vOtherCharSystem_SetActiveSkill( PS_SCP_RESP_SKILL_SELECT_BROADCAST info );
	HTvoid						HT_vOtherCharSystem_ActiveSkillEffectOn();
	HTvoid						HT_vOtherCharSystem_ActiveSkillEffectOff();
	//	��� ��ũ ���� �ϱ�
	HTvoid						HT_vOtherCharSystem_SetGuildMarkID( CHTString strName, HTint iGuildMark );
	//	��� ��ũ ǥ�� �ϱ�/���ϱ�
	HTvoid						HT_vOtherCharSystem_GuildEmblemOn();
	HTvoid						HT_vOtherCharSystem_GuildEmblemOff();
	//	�ֽ� ���� �ϱ�
	HTvoid						HT_vOtherCharSystem_SetTrimuritiD( CHTString strName, BYTE byTrimuritii );
	//	�ֽ� ��ũ ǥ�� �ϱ�
	HTvoid						HT_vOtherCharSystem_TrimuritiMarkOn();
	//	�ֽ� ��ũ ǥ�� ���ϱ�
	HTvoid						HT_vOtherCharSystem_TrimuritiMarkOff();


	//-----------��Ƽ�����μ� ���� �� Ż���Ҷ�----------//
	HTvoid						HT_vOtherChar_SetPartyJoineDisband( CHTString, BYTE );
	//-----------������ �Ҹ�� �����-------------//
	HTvoid						HT_vOtherCharSystem_NetWork_ItemAbrasionBroadcast(PS_SCP_ITEM_ABRASION_BROADCAST info);

	//----------�̴ֺ�ε�ĳ��Ʈ ������������ OtherChar�� �������ֱ� ����---------//
	HTvoid						HT_vOtherCharSystem_NetWork_RequestInitOtherChar( DWORD dwKeyID );

	//---------- GM�� �����带 ���� �Ǵ� ������ ��û�Ѵٸ� �˸���-------------//
	HTvoid						HT_vOtherCharSystem_NetWork_SCP_TRANSPARENCY_MODE_NOTIFY( PS_SCP_TRANSPARENCY_MODE_NOTIFY info );

	HTvector3					HT_vOtherCharSystem_GetAttackPos( DWORD dwTargetKeyID, DWORD dwSkillIndex, BYTE* byTargetType, HTint* iTargetModelID );

	//---------���� Ÿ��â�� ������ �������� �ִ� ĳ������ �� ID ��ȯ-------------//
	DWORD						HT_dwOtherCharacterSystem_GetTargetModelID();
	//-----------��Ƽ ����/Ż�� ����-------------//
	HTvoid						HT_vOtherCharSystem_SetPartyJoin( CHTString, HTbool );
	HTRESULT					HT_hrOtherCharSystem_CompareGuild( HTint iKeyID, HTint iGuildMark );
	//	PS_SCP_RESP_UPDATE_STATUS Setting
	HTvoid						HT_vOtherCharSystem_SCPRespUpdateStatus( PS_SCP_RESP_UPDATE_STATUS info );
	//	���� ���߱�
	HTvoid						HT_vOtherCharSystem_SetStop( HTint );
	

private:
	HTvoid						HT_LL_vInitList();
	HTRESULT					HT_LL_hrDeleteNode( int );
	HTRESULT					HT_LL_hrInsertAfter( PS_SCP_INIT_OTHER_MOB info );
	HTvoid						HT_LL_hrDeleteAll();


public:
	HTint						m_iOtherChar_IndexCount;

	PS_SCP_OTHER_CHAR_MOVE		m_SCP_OTHER_CHAR_MOVE;

	//----------OtherChar ���� ǥ������----------//
	HTbool						m_nOtherChar_HPInfo_Sw;

	
private:
	HT_OTHERCHARACTER_NODE*		m_sOtherCharHead;
	HT_OTHERCHARACTER_NODE*		m_sOtherCharTail;

	//	�̸� �����ֱ�
	HTbool						m_bOtherChar_NameShowSw;
	//	ä�� �޽��� �����ֱ�
	HTbool						m_bOtherChar_ChatMsgShowSw;

};

#endif

