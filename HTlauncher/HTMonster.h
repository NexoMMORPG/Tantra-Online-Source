

#ifndef __HTMONSTER_H__
#define __HTMONSTER_H__

#include "HTMoveMonster.h"

#define MONSTER_STATE_DEATH					0
#define MONSTER_STATE_LIVE					1
#define MONSTER_STATE_DEATHMOTION			2

class HTMonster
{
public:

	HTMonster();
	~HTMonster();

	HTRESULT					HT_hMonsterInit();

	HTvoid						HT_vMonsterCreate( PS_SCP_INIT_OTHER_MOB, BYTE );
	
	HTvoid						HT_vMonsterSet_physical_CellMove( HTfloat );	//	몬스터 물리적인 셀무브 - 화면상에서 움직일 때

	HTvoid						HT_vMonster_AnimationControl();			//	공격 한번하고 중단
	HTvoid						HT_vMonster_AnimationControl_WlkRun();	//	걷기/뛰기 컨트롤

	//---------업데이트----------//
	HTvoid						HT_vMonsterUpdate( HTfloat );
	//---------업데이트_죽음에 관하여----------//
	HTvoid						HT_vMonsterUpdate_Death();
	//---------공격 받았을 때_맞는 액션 온----------//
	HTbool						HT_vMonster_SetDisAttackOn( DWORD, BYTE, HTfloat, HTint );
	//---------HP 변경사항 체크----------//
	HTint						HT_vMonster_SetHPCheck( DWORD dwInvadeKeyID, HTint nCurHP, HTint nDamageHP, BYTE byInvadeType, HTvector3 vecInvadePos, HTint nInvadeModelID );
	//---------정보 디스플레이 셋팅----------//
	HTvoid						HT_vMonster_SetInfoDisplay(HTbool bAttack);
	//---------정보 디스플레이 셋팅취소----------//
	HTvoid						HT_vMonster_SetInfoCancel();
	
	//---------애니매이션 셋팅----------//
	HTvoid						HT_vMonster_SetAnimation( HTint );

	//---------이펙트_임팩트 이펙트 틀어주기----------//
	HTvoid						m_vMonsterAttack_ImpactEffect( DWORD dwIndex, BYTE byLevel, HTint iItemIndex );
	//---------이펙트_몬스터 죽었을때 여러가지것들----------//
	HTvoid						m_vMonster_WhenDeathEffect();

	//-----서버쪽 네트위크-----//
	HTvoid						HT_vMonsterSet_logical_CellEnd( MSG_Action* sInfo );		//	몬스터 논리적인 끝
	//-----------공격한다----------//
	HTvoid						HT_vMonster_RotateAttack( HTvector3 );
	HTvoid						HT_vMonster_AttackPointCheck();			//	몬스터의 공격포인트에서 할일
	//-----------몬스터가 죽는다----------//
	HTvoid						HT_vMonster_Network_Death();
	//-----------몬스터가 텔레포트 한다----------//
	HTvoid						HT_vMonster_Network_Teleport();
	//	공격받았을때 몬스터 스케일
	HTvoid						HT_vMonster_ScaleControl();

	//	몬스터가 공격을 함
	HTvoid						HT_vMonster_Network_SCP_Msg_Attack( S_MSG_ATTACK_OTHERMOB info );

private:


public:
	CHTMoveMonSter*				m_cMoveMonster;

    DWORD						m_iMonsterKeyID;
	HTint						m_iMonsterModelID;						//	몬스터 모델 ID
	HTint						m_iMonsterIndex;						//	몬스터를 구별하기 위해서,
	HTint						m_nMonster_ResentAnm;					//	몬스터 현재의 애니매이션
	CHTString					m_strName;
//	BYTE						m_byMaxAttackDistance;					//	최대 공격 거리
	HTint						m_iMaxAttackDistance;
	BYTE						m_byMonster_Size;						//	몬스터의 크기
	
	//-----몬스터의 현재 HP상태를 체크-----//
	HTint						m_nMonster_MAX_HP;
	HTint						m_nMonster_Resent_HP;

	//-----공격과 관련하여-----//
	HTbool						m_bMonster_AttackSw;
	HTbool						m_bMonster_DisAttackSw;
	HTint						m_nMonster_Live;
	BYTE						m_byMonster_InvadeType;				//	0x03:MainChar, 0x01:OtherChar
	HTint						m_nMonster_InvadeModelID;			//	몬스터를 공격한 캐릭터의 모델 아이디
	DWORD						m_dwMonster_InvadeKeyID;
	BYTE						m_byMonster_AttackTarget;			//	0x01:OtherChar, 0x03:MainChar
	DWORD						m_dwMonster_TargetKeyID;			//	공격받은 대상의 KeyID
	DWORD						m_dwMonster_Skill;					//	몬스터의 기술
	BYTE						m_byMonster_AttackType;				//	공격 타입
	HTvector3					m_vecMonster_TargetPos;				//	공격대상의 위치
	BYTE						m_byMonster_CriticalHit;			//	커리티컬 힛
	HTint						m_nMonster_AttackTargetModelID;		//	공격대상의 모델 아이디
	HTint						m_nMonster_TargetHP;				//	공격받은 대상의 HP
	HTint						m_nMonster_DamageHP;

	BYTE						m_byMonster_ActonEffect;

	//-----정보 디스플레이-----//
	HTbool						m_bMonster_InfoShow_Sw;
	
	//-----죽음에 관한 리포트-----//
	HTbool						m_bMonster_Death_Sw;
	DWORD						m_bMonster_Death_Delay;

	//-----맞았을때 이동중이면 이동정보 저장-----//
	HTbool						m_bMOnster_HitMove_Sw;

	//-----공격 성공/실패 판정-----//
	HTint						m_nMonster_HitCount;

	//	지정 되었음을 보여주는 이펙트
	HTint						m_nTargettingEffectID;

	//-----몬스터 아이들 동작을 위해-----//
	DWORD						m_nMonster_IdlDelay;

	//-----몬스터 HP 표현하기위해 메인캐릭터가 때렸을때만-----//
	HTbool						m_bAttack_FromMainChar;

	HTint						m_iMonster_ScaleIndex;			//	스케일 인덱스
	HTfloat						m_fMonster_ScaleValue;			//	스케일 값
	HTfloat						m_fMonster_ScaleValueTrans;		//	스케일 변화 값

	HTfloat						m_fMonsterModelHeight;

	P_ATTACK_FACTOR				m_sMonster_AttackFactor;

	//	임시
	short						m_snMonster_TargetX;
	short						m_snMonster_TargetZ;
};

#endif

