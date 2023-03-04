
#ifndef __HTOTHERCHARACTER_H__
#define __HTOTHERCHARACTER_H__

#include "HTOtherCharacterMove.h"

#define OTHERCHAR_STATE_DEATH					0
#define OTHERCHAR_STATE_LIVE					1
#define OTEHRCHAR_STATE_DEATHMOTION				2

class HTOtherCharacter
{
public:

	HTOtherCharacter();
	~HTOtherCharacter();

	HTvoid						HT_vOtherCharCreate( PS_SCP_INIT_OTHER_MOB );
	HTvoid						HT_vOtherCharDistroy();
	HTvoid						HT_vOtherCharControl( HTfloat fElapsedTime );
	HTvoid						HT_vOtherCharControl_SkillCastTimeCheck();

	//---------이펙트_임팩트 이펙트 틀어주기----------//
	HTvoid						m_vOtherCharAttack_ImpactEffect( DWORD dwSkillIndex, HTint iItemIndex );
	HTvoid						HT_vOtherChar_ActiveSkillEffectOn();
	HTvoid						HT_vOtherChar_ActiveSkillEffectOff();

	//	길드 마크 셋팅 하기
	HTvoid						HT_vOtherChar_SetGuildMarkID( HTint iGuildMarkID );
	//	길드 마크 표현 하기
	HTvoid						HT_vOtherChar_GuildEmblemOn();
	//	길드 마크 표현 안하기
	HTvoid						HT_vOtherChar_GuildEmblemOff();
	//	주신 셋팅 하기
	HTvoid						HT_vOtherChar_SetTrimuritiD( BYTE byTrimuritii );
	//	주신 마크 표현 하기
	HTvoid						HT_vOtherChar_TrimuritiMarkOn();
	//	주신 마크 표현 안하기
	HTvoid						HT_vOtherChar_TrimuritiMarkOff();

	HTvoid						HT_vOtherChar_MoveControl( HTfloat fElapsedTime );
	//---------아이템을 판별하여 셋팅해준다----------//
	HTvoid						HT_vOtherChar_SetItemType( BYTE byPart, STRUCT_ITEMVIEW info );

	//---------애니매이션----------//
	//	캐릭터 애니매이션 셋팅
	HTvoid						HT_vOtherChar_SetChangeAni( HTint loop, HTfloat fTime, DWORD dwSkillIndex );
	HTvoid						HT_vOtherChar_AnimationControl();

	//---------정보 디스플레이 ----------//	//2003.1.3 선미추가
	HTvoid						HT_vOtherChar_SetInfoDisplay();
	HTvoid						HT_vOtherChar_SetInfoCancel();

	//-----------픽된 상태인가 체크----------//
	HTRESULT					HT_hrOtherChar_GetInfoStatus();

	//	전체 공격 관련
	//-----------공격당한 순간 해야할일들----------//
	HTvoid						HT_vOtherChar_SetAttack( DWORD, BYTE byAttackType, HTint iItemIndex );
	//-----------공격포인트에서 해야할일들----------//
	HTvoid						HT_vOtherChar_AttackPointCheck();
	//---------HP 변경사항 체크----------//
	HTint						HT_nOtherChar_SetHPCheck( HTint nHP );
	HTvoid						HT_vOtherChar_RotateAttack( HTvector3 );		//	공격자를 향해 회전
	HTvoid						HT_vOtherChar_AttackPosCheck( HTint, HTint );	//	공격자의 위치 보정
	//-----------스킬 셋팅----------//
	HTvoid						HT_vOtherChar_SetActiveSkill( PS_SCP_RESP_SKILL_SELECT_BROADCAST info );
	//	액티브 스킬 상용을 받았을 때 Effect 틀기
	HTvoid						HT_vOtherChar_SetActiveSkillEffectOn( DWORD dwSkillIndex, HTbool bType, BYTE byLevel );
	//-----------파티원으로서 가입 및 탈퇴할때----------//
	HTvoid						HT_vOtherChar_SetPartyJoineDisband( BYTE );

	//----------서버와 통신하는 네트워크 함수---------//
	//	Other Character LevelUp 을 알림
	HTvoid						HT_vOtherChar_LevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info );
	//	GM의 투명모드를 설정 또는 해제를 요청한다를 알린다
	HTvoid						HT_vNetWork_SCP_TRANSPARENCY_MODE_NOTIFY( PS_SCP_TRANSPARENCY_MODE_NOTIFY );
	//	서버가 다른캐릭터의 이동을 알려왔을 때
	HTvoid						HT_vNetWork_OtherChar_Action( MSG_Action* info );
	//	스킬 시작을 알림
	HTvoid						HT_vOtherChar_Ready_Char_Broadcast( PS_SCP_SKILL_READY_CHAR_BROADCAST info );
	//	스킬 적용을 알림
	HTvoid						HT_vOtherChar_Network_Skill_Cast_Broadcast( S_MSG_ATTACK_OTHERMOB );
	//	OtherChar 죽음 처리
	HTvoid						HT_hrOtherChar_Death();
	//	OtherChar 죽음 처리 딜레이
	HTvoid						HT_hrOtherChar_DeathDelay();


public:

	CHTString					m_iOtherCharName;					//	이름
    CHTString					m_strOtherChar_GuildName;			//	길드 이름
	BYTE						m_byOtherChar_Level;				//	다른캐릭터의 레벨
	
	BYTE						m_byOtherChar_SpecialName;			//	특수칭호
	DWORD						m_dwOtherCharKeyID;					//	서버의 분별을 위한 ID
	HTint						m_iOtherCharModelID;				//	다른캐릭터 ID
	BYTE						m_byOtherChar_TribeType;			//	종족 타입
	BYTE						m_byOtherChar_FaceType;				//	얼굴
	BYTE						m_byOtherChar_HairType;				//	머리
	CHTString					m_sOtherCharAnimation[3][10];		//	애니매이션 ID
	DWORD						m_dwEquipItem[16];					//	아이템 인덱스
	BYTE						m_byOtherChar_PartyMember;			//	0x01:파티멤버아님, 0x02:파티멤버
	DWORD						m_dwOtherChar_GuildEmblemID;		//	길드 마크
	
	HTint						m_iOtherCharCellSizeX;				//	다른캐릭터가 치지하는 셀X
	HTint						m_iOtherCharCellSizeZ;				//	다른캐릭터가 치지하는 셀Z

	CHTOtherCharMove*			m_cOtherCharMove;
	BYTE						m_bOtherCharMoveState;				//	캐릭터의 이동상태
	BYTE						m_bOtehrCharMoveDir;				//	현재방향

	//-----애니매이션 컨트롤 위해-----//
	HTint						m_nOtherChar_WeaponItemID;
	HTint						m_nOtherChar_WearItemID;
	HTint						m_nOtherChar_AniResentState;
	HTint						m_nOtherChar_AttackType;
	HTbool						m_bOtherChar_AttackSw;
	HTint						m_iOtherChar_AttackAniCount;
	HTbool						m_bOtherChar_ActiveSkillIngSw;

	//-----캐릭터의 현재 HP상태 / 정보를 체크-----//
	HTint						m_nOtherChar_MAX_HP;
	HTint						m_nOtherChar_Resent_HP;
	HTbool						m_bOtherChar_Info_Sw;
	DWORD						m_bOtherChar_HPShow_StartTime;
	
	//-----맞았는지 체크-----//
	HTbool						m_bOtherChar_HitSw;

	//-----이펙트 관련 인덱스-----//
	HTint						m_nEffect_ActiveSkillID;
	DWORD						m_dwActiveSkillIndex;
	BYTE						m_byActiveSkillLevel;

	//	공격 관련
	HTvector3					m_vecAttack_TargetPos;			//	공격 효과 위치
	HTint						m_nAttack_TargetModelID;		//	공격타겥의 모델 아이디
	BYTE						m_byOtherChar_AttackTarget;		//	0x01:MainChar,0x02:OtherChar,0x03:Monster
	DWORD						m_dwOtherChar_TargetKeyID;		//	공격받은 대상의 KeyID
	HTint						m_nOtherChar_TargetHP;			//	공격받은 대상의 HP
	HTint						m_nOtherChar_HitCount;			//	맞은 데미지
	HTbool						m_bOtherChar_CastSw;			//	캐스트 유무
	HTint						m_iOtherChar_CastEffectID;		//	캐스트 이펙트 ID
	BYTE						m_byOtherCharCriticalHit;		//	커리티컬 힛 판정 여부
	short						m_snOtherChar_Demage;
	BYTE						m_byOtherChar_Trimuriti;		//	주신

	//	스킬 관련 설정
	DWORD						m_dwOhterChar_SkillID;				//	OtherChar 스킬 ID
	DWORD						m_dwOhterChar_SkillLevel;			//	OtherChar 스킬 Level
	HTdword						m_dwOtherChar_SkillType;			//	스킬 Type
	HTint						m_iOtherChar_SkillCastTime;			//	캐스팅 시간
	HTbool						m_bOtherChar_SkillCastTimeSw;		//	캐스팅 체크 설정
	HTint						m_iOtherChar_SkillCastStartTime;	//	캐스팅 시작 시간
	HTint						m_iOtherChar_SkillEffectID;

	//	동작중에 다른 이벤트를 받을수 있는것과 없는것 구별
	HTbool						m_bOtherChar_AniEventCanSw;

	//-----아이들 동작을 위해-----//
	DWORD						m_dwOtherChar_IdlTime;

	//-----OtherChar 죽음 처리-----//
	HTint						m_nOtherChar_Death;
	DWORD						m_dwOtherChar_DeathDelay;

	HTfloat						m_fModelHeight;		//	몬스터 모델의 키

	//-----조교인지 아닌지 체크-----//
	HTbool						m_bAssistantSw;		//	InitOtherChar 일때, 장/탈착시에 체크

	//	채팅메시지
	BYTE						m_byOtherChar_ChattingType;
	CHTString					m_strOtherChar_ChattingMessage;
	DWORD						m_dwOtherChar_ChatMsgDelay;

	P_ATTACK_FACTOR				m_sOtherChar_AttackFactor;

	// 무기를 뒤로 찼는지에 대한 플래그
	HTbool						m_bIsWeaponArmed;
};

#endif



