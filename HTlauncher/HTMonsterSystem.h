
#ifndef __HTMONSTERSYSTEM_H__
#define __HTMONSTERSYSTEM_H__

#include "HTMonster.h"

//----------몬스터 LL 구현을 위한 구조체----------//
typedef struct _HT_MONSTER_NODE
{
	HTMonster						sMonster;
	struct _HT_MONSTER_NODE			*next;

} HT_MONSTER_NODE;




//----------몬스터 전체 시스템과 LL을 실제 구현----------//
class HTMonsterSystem
{
public:
	HTMonsterSystem();
	~HTMonsterSystem();
	HTvoid					HT_vMonsterSysytem_Clean();

	HTRESULT				HT_hMonsterSystemInit();
	HTvoid					HT_vMonsterSystemUpdate( HTfloat );
	HTvoid					HT_vMonsterSystemMonUpdate( HTfloat );

	//----------몬스터 지우기---------//
	HTvoid					HT_vMonsterSystem_Delete( PS_SCP_RESP_REMOVE_MOB info );
	//----------전체 몬스터 지우기---------//
	HTvoid					HT_vMonsterSystem_TotalMonsterDelete();

	//---------공격 관련----------//
	//---------공격 받았을 때_맞는 액션 온----------//
	HTbool					HT_vMonsterSystem_SetDisAttackOn( DWORD, DWORD, HTfloat, BYTE, HTint );
	//---------HP 변경사항 체크----------//
	HTint					HT_vMonsterSystem_SetHPCheck( DWORD, HTint, HTint, BYTE byInvadeType, HTvector3 vecInvadePos, HTint nInvadeModelID );
	

	HTvoid					HT_vMonsterSystemCreate( PS_SCP_INIT_OTHER_MOB info );

	DWORD					HT_bMonsterSystemComIDCheck( HTint iID );
	HTvector3				HT_vMonsterSystemGetCameraPoint();
	HTint					HT_bMonsterSystemCheckMapCell( HTint iMapCellX, HTint iMapCellZ ); //	셀에 위치한 몬스터가 있는가?

	HTvoid					HT_vMainCharacterCheck();			//	메인캐릭터와의 관계 /  메인캐릭터 셋팅
	HTvoid					HT_vMonster_AOI_Check( HT_MONSTER_NODE *t );		//	AOI 영역 체크

	//----------랜더---------//
	HTvoid					HT_vMonsterSystemRender();
	//----------랜더_이름----------//
	HTvoid					HT_vMonsterSystem_RenderName( HT_MONSTER_NODE* t );

	//----------반환값---------//
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
	//	셀좌표로 캐릭터 키아디를 알아온다
	HTint					HT_iMonsterSystem_GetKeyIDFromCell( short, short, HTvector3* );
	//----------몬스터 정보창 초기화---------//
	HTvoid					HT_vMonsterSystem_HPWindowInit();
	
	//---------- 네트위크----------//
	HTRESULT				HT_vMonsterSystemSet_logical_End( MSG_Action* sInfo );

	HTvoid					HT_vMonsterSystem_NewWork_SCP_MSG_Attack( PS_CSP_CAST_UNIT_SKILL data );
	HTvoid					HT_vMonsterSystem_Skill_Ready_Char_Broadcast( PS_SCP_SKILL_READY_CHAR_BROADCAST );
	HTvoid					HT_vMonsterSystem_Skill_AtkChar_Broadcast( PS_SCP_SKILL_ATK_CHAR_BROADCAST );
	//HTvoid					HT_vMonsterSystem_Skill_Affect_Broadcast( PS_SCP_AFFECT_SKILL_BROADCAST info );
	HTvoid					HT_vMonsterSystemSet_Death( PS_SCP_CHAR_MONSTER_DEATH_BROADCAST info );
	HTvoid					HT_vMonsterSystem_Monster_DisApper( PS_SCP_MONSTER_DISAPPEAR );

	//----------이닛브로드캐스트 받지못했을때 MonsterNPC를 보정해주기 위해---------//
	HTvoid					HT_vRequestInitMonsterNPC( DWORD );

	//----------공격 대상을 찿아내어 그의 위치를 얻어내----------//
	HTvector3				HT_vMonsterSystem_GetAttackPos( DWORD dwTargetKeyID, HTint iSkillID, BYTE* byTargetType );
	//---------현재 타겟창에 몬스터 정보가 보여지고 있는 몬스터의 모델 ID 반환-------------//
	DWORD					HT_dwMosterSystem_GetTargetModelID();
	//	범위공격 영역안에 들어간 몹들을 찿아옴
	HTvoid					HT_vMosterSystem_GetTerritoryArea( HTvector3 vecTargetPos, HTfloat fRange, HTint iSkillID, HTfloat fDirect, HTint *iElement );
	//	몹이 살았는지 죽었는지 알아오기
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

	//----------몬스터 정보 표시위해----------//
	HTbool					m_nMonster_HPIndo_Sw;
	

private:
	HT_MONSTER_NODE*		m_sMonsterHead;
	HT_MONSTER_NODE*		m_sMonsterTail;
	BYTE					m_sMonsterInitDirect;

	HTdword					m_dwMonOnjID;


};

#endif

