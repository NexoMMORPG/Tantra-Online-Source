
#ifndef __HTMONSTERSYSTEM_H__
#define __HTMONSTERSYSTEM_H__

#include "HTMonster.h"

//----------���� LL ������ ���� ����ü----------//
typedef struct _HT_MONSTER_NODE
{
	HTMonster						sMonster;
	struct _HT_MONSTER_NODE			*next;

} HT_MONSTER_NODE;




//----------���� ��ü �ý��۰� LL�� ���� ����----------//
class HTMonsterSystem
{
public:
	HTMonsterSystem();
	~HTMonsterSystem();
	HTvoid					HT_vMonsterSysytem_Clean();

	HTRESULT				HT_hMonsterSystemInit();
	HTvoid					HT_vMonsterSystemUpdate( HTfloat );
	HTvoid					HT_vMonsterSystemMonUpdate( HTfloat );

	//----------���� �����---------//
	HTvoid					HT_vMonsterSystem_Delete( PS_SCP_RESP_REMOVE_MOB info );
	//----------��ü ���� �����---------//
	HTvoid					HT_vMonsterSystem_TotalMonsterDelete();

	//---------���� ����----------//
	//---------���� �޾��� ��_�´� �׼� ��----------//
	HTbool					HT_vMonsterSystem_SetDisAttackOn( DWORD, DWORD, HTfloat, BYTE, HTint );
	//---------HP ������� üũ----------//
	HTint					HT_vMonsterSystem_SetHPCheck( DWORD, HTint, HTint, BYTE byInvadeType, HTvector3 vecInvadePos, HTint nInvadeModelID );
	

	HTvoid					HT_vMonsterSystemCreate( PS_SCP_INIT_OTHER_MOB info );

	DWORD					HT_bMonsterSystemComIDCheck( HTint iID );
	HTvector3				HT_vMonsterSystemGetCameraPoint();
	HTint					HT_bMonsterSystemCheckMapCell( HTint iMapCellX, HTint iMapCellZ ); //	���� ��ġ�� ���Ͱ� �ִ°�?

	HTvoid					HT_vMainCharacterCheck();			//	����ĳ���Ϳ��� ���� /  ����ĳ���� ����
	HTvoid					HT_vMonster_AOI_Check( HT_MONSTER_NODE *t );		//	AOI ���� üũ

	//----------����---------//
	HTvoid					HT_vMonsterSystemRender();
	//----------����_�̸�----------//
	HTvoid					HT_vMonsterSystem_RenderName( HT_MONSTER_NODE* t );

	//----------��ȯ��---------//
	DWORD					HT_MonsterSystem_GetKeyID( HTint iImageID );
	DWORD					HT_dwMonsterSystem_GetIndex( DWORD KeyID );
	HTPoint					HT_MonsterSystem_GetCellPos( DWORD );
	HTvector3				HT_MonsterSystem_GetCoordFromModelID( HTint );
	HTvector3				HT_MonsterSystem_GetCoordFromKeyID( DWORD );
	HTvector3				HT_MonsterSystem_GetAttackPos( DWORD dwKeyID, HTint nCurHP, DWORD );
	CHTString				HT_strMonsterSystem_GetName( DWORD dwkeyID );
	CHTString				HT_strMonsterSystem_GetNamebyModelID( DWORD dwModelID );
	HTint					HT_strMonsterSystem_GetModelIDbyKeyID( DWORD dwKeyID );
	BYTE					HT_byMonsterSystem_GetMonsterSize( DWORD dwKeyID );
	//	����ǥ�� ĳ���� Ű�Ƶ� �˾ƿ´�
	HTint					HT_iMonsterSystem_GetKeyIDFromCell( short, short, HTvector3* );
	//----------���� ����â �ʱ�ȭ---------//
	HTvoid					HT_vMonsterSystem_HPWindowInit();
	
	//---------- ��Ʈ��ũ----------//
	HTRESULT				HT_vMonsterSystemSet_logical_End( MSG_Action* sInfo );

	HTvoid					HT_vMonsterSystem_NewWork_SCP_MSG_Attack( PS_CSP_CAST_UNIT_SKILL data );
	HTvoid					HT_vMonsterSystem_Skill_Ready_Char_Broadcast( PS_SCP_SKILL_READY_CHAR_BROADCAST );
	HTvoid					HT_vMonsterSystem_Skill_AtkChar_Broadcast( PS_SCP_SKILL_ATK_CHAR_BROADCAST );
	//HTvoid					HT_vMonsterSystem_Skill_Affect_Broadcast( PS_SCP_AFFECT_SKILL_BROADCAST info );
	HTvoid					HT_vMonsterSystemSet_Death( PS_SCP_CHAR_MONSTER_DEATH_BROADCAST info );
	HTvoid					HT_vMonsterSystem_Monster_DisApper( PS_SCP_MONSTER_DISAPPEAR );

	//----------�̴ֺ�ε�ĳ��Ʈ ������������ MonsterNPC�� �������ֱ� ����---------//
	HTvoid					HT_vRequestInitMonsterNPC( DWORD );

	//----------���� ����� �O�Ƴ��� ���� ��ġ�� ��----------//
	HTvector3				HT_vMonsterSystem_GetAttackPos( DWORD dwTargetKeyID, HTint iSkillID, BYTE* byTargetType );
	//---------���� Ÿ��â�� ���� ������ �������� �ִ� ������ �� ID ��ȯ-------------//
	DWORD					HT_dwMosterSystem_GetTargetModelID();
	//	�������� �����ȿ� �� ������ �O�ƿ�
	HTvoid					HT_vMosterSystem_GetTerritoryArea( HTvector3 vecTargetPos, HTfloat fRange, HTint iSkillID, HTfloat fDirect, HTint *iElement );
	//	���� ��Ҵ��� �׾����� �˾ƿ���
	HTbool					HT_bMonsterSystem_GetMobLive( HTint iKeyID );
	//	PS_SCP_RESP_UPDATE_STATUS Setting
	HTvoid					HT_vMonsterSystem_SCPRespUpdateStatus( PS_SCP_RESP_UPDATE_STATUS info );
	//	Set Stop
	HTvoid					HT_vMonsterSystem_SetStop( HTint iKeyID );

private:
	HTvoid					HT_LL_vInitList();
	HTRESULT				HT_LL_hrDeleteNode( DWORD iMonsterKeyID );
	HTRESULT				HT_LL_hrInsertAfter( PS_SCP_INIT_OTHER_MOB info );
	HTvoid					HT_LL_hrDeleteAll();


public:
	HTint					m_iMonster_IndexCount;

	//----------���� ���� ǥ������----------//
	HTbool					m_nMonster_HPIndo_Sw;
	

private:
	HT_MONSTER_NODE*		m_sMonsterHead;
	HT_MONSTER_NODE*		m_sMonsterTail;
	BYTE					m_sMonsterInitDirect;

	HTdword					m_dwMonOnjID;


};

#endif

