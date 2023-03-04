#pragma once

#include "HTOtherObjectMove.h"

#define OTHERCHAR_STATE_DEATH					0
#define OTHERCHAR_STATE_LIVE					1
#define OTEHRCHAR_STATE_DEATHMOTION				2
#define OTEHRCHAR_STATE_SUMMONS					3

#define CHATMSGDELAYTIME				5000

class HTOtherObject
{
public:
	HTOtherObject(void);
	~HTOtherObject(void);

	//	Init Other Mob
	HTvoid						HT_vOtherObject_Create( PS_SCP_INIT_OTHER_MOB info, BOOL bObjectShow );
	//	Create Model
	HTvoid						HT_vOtherObject_CreateModel();
	//	Delete Model
	HTvoid						HT_vOtherObject_DeleteModel();
	//	Control
	HTvoid						HT_vOtherObject_Control( HTfloat fElapsedTime );
	//	Control Death Delay
	HTvoid						HT_vOtherObject_ControlDeathDelay();
	//	Control Active Skill Cast Time Check
	HTvoid						HT_vOtherObject_ControlActiveSkillCastTimeCheck();
	//	Control AttackPointCheck From Time -> 보이지 않은 몬스터는 애니매이션 포인트가 날아오지 않기 때문에 시간으로 체크해야한다.
	HTvoid						HT_vOtherObject_ControlAttackPointCheckFromTime();
	
	//	Animation Set Change Animation
	HTvoid						HT_vOtherObject_SetChangeAnimation( HTint loop, HTfloat fTime, DWORD dwSkillIndex );
	//	Animation Animation Check
	HTvoid						HT_vOtherObject_AnimationCheck();

	//	Move Control
	//	Move Go Control
	HTvoid						HT_vOtherObject_MoveControl( HTfloat fElapsedTime );
	//	Move Rotate Control
	HTvoid						HT_vOtherObject_RotateControl( HTfloat fElapsedTime );
	//	Move Stand Control
	HTvoid						HT_vOtherObject_StandControl( HTfloat fElapsedTime );

	//	Attack
	//	Attack Point
	HTvoid						HT_vOtherObject_AttackPoint();
	//	Atack Atk Message
	HTvoid						HT_vOtherObject_AttackMessage();

	//	Effect
	//	Effect When Invade From OtherObject
	HTvoid						HT_vOtherObject_EffectAttack( HTint iSkillID, HTint iItemID, HTint iInvadeModelID, HTint iInvadeKeyID );
	//	Effect Recive Active Skill Use From OtherObject
	HTvoid						HT_vOtherObject_EffectActiveSkillEffectOn( HTint iSkillIndex, HTbool bType, BYTE byLevel );
	//	Effect When OtherObject Death
	HTvoid						HT_vOtherObject_WhenDeathEffect();
	//	Effect EffectStunSleepHoldOn
	HTvoid						HT_vOtherObject_EffectFaintingstateOn();
	//	Effect EffectSetModelColor
	HTvoid						HT_vOtherObject_EffectSetModelColor( HTfloat r, HTfloat g, HTfloat b, HTfloat fTime );
    
	//	Setting
	//	Setting Set Item 
	HTvoid						HT_vOtherObject_SetItemType( BYTE byPart, STRUCT_ITEMVIEW info );
	//	Setting Set Guild Mark ID
	HTvoid						HT_vOtherObject_SetGuildMarkID( HTint iGuildMarkID );
	//	Setting Show Guild Mark
	HTvoid						HT_vOtherObject_SetGuildMarkOn();
	//	Setting Hide Guild Mark
	HTvoid						HT_vOtherObject_SetGuildMarkOff();
	//	Setting Set Trimuriti ID
	HTvoid						HT_vOtherObject_SetSetTrimuritiID( BYTE TrimuritiID );
	//	Setting Show Trimuriti Mark
	HTvoid						HT_vOtherObject_SetTrimuritiMarkOn();
	//	Setting Hide Trimuriti Mark
	HTvoid						HT_vOtherObject_SetTrimuritiMarkOff();
	//	Setting HP
	HTvoid						HT_iOtherObject_SetHPCheck( HTint iHP );
	//	Setting Show Infomation
	HTvoid						HT_vOtherObject_SetShowInfomation( HTbool );
	//	Setting Hide Infomation
	HTvoid						HT_vOtherObject_SetHideInfomation();
	//	Setting Party Join and Disband
	HTvoid						HT_vOtherObject_SetPartyJoineDisband( BYTE );
	//	Setting Model Hide
	HTvoid						HT_vOtherObject_SetModelHide( HTbool );
	//	Setting Affections
	HTvoid						HT_vOtherObject_SetAffections( __int64 );
	//	Setting TradeMode
	HTvoid						HT_vOtherObject_SetTradeMode( MSG_MobStatus* info );
	//	Setting MyGuildName
	HTvoid						HT_vOtherObject_SetMyGuildCheck( CHTString strGuildName );
	//	Setting MainCharWizardEyesSw
	HTvoid						HT_vOtherObject_SetMainCharWizardEyes( HTbool bTrue );
	//	Setting 장착한 무기 아이템의 제련에 따른 이펙트 설정
	HTvoid						HT_vOtherObject_SetAttachRefineEffect();
	//	Setting Targetting
	HTvoid						HT_vOtherObject_SetTargetting();
	//	Setting Collison
	HTvoid						HT_vOtherObject_SetCollison();

	//	Network
	//	Network	LevelUp Brodcast
	HTvoid						HT_vOtherObject_NetworkLevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info );
	//	Network	GM의 투명모드를 설정 또는 해제를 요청한다를 알린다
	HTvoid						HT_vOtherObject_NetworkGMMode_Notify( BYTE byGMMode );
	//	Network	Recive OtherObjct Move Message
	HTvoid						HT_vOtherObject_NetworkAction( MSG_Action* info );
	//	Network Apply Skill Brodcast
	HTvoid						HT_vOtherObject_NetworkApplySkillBroadcast( S_MSG_ATTACK_OTHERMOB );
	//	Network Recive Death Message
	HTvoid						HT_vOtherObject_Death();
	//	Network Recive Summons Message 
	HTvoid						HT_vOtherObject_NetworkSummons();
	//	Network Teleport
	HTvoid						HT_vOtherObject_NetworkTeleport();
	//	Network YutMove
	HTvoid						HT_vOtherObject_NetworkYutMove( Msg_YutMove* info );

public:

	//	Object Factor
	PS_SCP_INIT_OTHER_MOB		m_pObjectInfo;
	//	ModelID
	HTint						m_iOtherModelID;
	//	Model Hight
	HTfloat						m_fOther_ModelHeight;
	//	보정된 종족코드
	HTint						m_iOther_TribeCode;
	//	MoveSystem
	HTOtherObjectMove*			m_pOther_MoveSystem;
	//	AttackSystem
    P_ATTACK_FACTOR				m_oOther_AttackFactor;
	//	Animation State
	HTint						m_iOther_AniResentState;
	//	Atk Animation Count
	HTint						m_iOther_AttackAniCount;
	//	아이템 인덱스
	HTint						m_iOther_EquipItem[16];
	//	아이템 속성에 따른 비트셋이 필요함.
	HTbyte						m_byOther_MainRef[16];
	//	아이템 제련레벨
	HTbyte						m_byOther_RefineLevel[16];
	//	무기를 들고 있는가?
	HTbool						m_bOther_IsWeaponArmed;
	//	옷
	HTint						m_iOther_WearItemID;
	//	무기
	HTint						m_iOther_WeaponItemID;
	//	조교냐?
	HTbool						m_bOther_AssistantSw;
	//	Info Display
	HTbool						m_bOther_InfoSw;
	//	Live
	HTint						m_iOther_LiveIndex;
	//	Live DelayTime
	HTint						m_iOther_LiveDelayTime;
	//	Idle
	HTint						m_iOther_IdlTime;
	//	이동시 회전처리_각도
	HTfloat						m_fOther_ShowAngle;
	//	이동시 회전처리_순서
	HTint						m_iOther_ProgressAngle;
	//	Apply Skill Index
	HTint						m_iOther_ApplySkillIndex;
	//	Apply Skill Type
	HTint						m_iOther_ApplySkillType;
	//	Apply Skill Effect ID
	HTint						m_iOther_ApplySkillEffectID;
	//	Apply Skill Duration ID
	HTint						m_iOther_DurationSkillEffectID;
	//	Apply Skill Effect StartTime
	HTint						m_iOther_ApplySkillStartTime;
	//	Apply Skill Effect ContinueTime
	HTint						m_iOther_ApplySkillContinueTime;
	//	Party Member Check
	HTbyte						m_byOther_PartyMember;
	//	Attack Type
	HTint						m_iOther_AttackType;
	//	Attack Target KeyID
	HTint						m_iOther_TargetKeyID[TN_MAX_TARGET_COUNT];
	//	Attack Target Pos
	HTvector3					m_vecOther_AttackTargetPos;
	//	Attack Target Pos
	HTvector3					m_vecOther_AttackSourcePos;
	//	Invade Type
	HTint						m_iOther_InvadeKeyID;
	//	Chat Msg
	CHTString					m_strOther_ChatgMeg;
	//	Chat Msg Show Start Time
	HTint						m_iOther_ChatMsgStartTime;
	//	OtherObject
	HTint						m_iTargettingEffectID;
	//	공격 받는것에 의해 Object가 멈춘다.
	HTbool						m_bStopWhenInvadeSw;
	//	공격 받았을때 이동해서 때리는것 셋팅
	HTbool						m_bOther_AttackMoveSw;
	//	공격 대상의 Demage Count
	HTint						m_iOther_TargetDamageHP[TN_MAX_TARGET_COUNT];
	//	공격 대상의 HP
	HTint						m_iOther_TargetHP[TN_MAX_TARGET_COUNT];
	//	커리티컬 힛
	HTbyte						m_byOther_TargetRes[TN_MAX_TARGET_COUNT];
	//	Effect of MSG_Action
	HTint						m_iOther_ActionEffect;
	//	몬스트의 사이즈
	HTbyte						m_byOther_Size;
	//	상대방의 스킬적용 속성
	__int64						m_iOther_TargetAffaction;
	//	보이지 않은 몬스터는 애니매이션 포인트가 날아오지 않기 때문에 시간으로 체크해야한다.
	HTbool						m_bOther_AtkPtFromTimeSw;
	HTint						m_iOther_AtkptFromTimeDelay;
	HTint						m_iOther_AtkptFromTimeStartTime;
	//	어택 포인트 체크
	HTbool						m_bOther_AtkptCheck;
	//	Down Earth
	HTbool						m_bOther_DownEarthSw;
	//	Object Name
	CHTString					m_strOther_Name;
	//	Affections 상태 FX
	HTint						m_iOther_FXAffections;
	//	My Guild Member
	HTbool						m_bOther_MyGuildMemberSw;
	//	WizardEyesSw
	HTbool						m_bOther_MainCharWizardEyesSw;
	//	Cast Name
	CHTString					m_strOther_CastName;
	//	공격가능한 상대인지 체크
	HTbool						m_bOther_DefinZoneAttackTarget;
	//	Turn Point For Yut Move
	int							m_iOther_EndPoint;
	//	End Point For Yut Move
	HTPoint						m_pOther_EndPoint;
	//	현재의 Object가 타겥 가능한 Object인지 구분
	HTbool						m_bOhter_Targetting;
	//	충돌체크 돼야 하는경우
	HTbool						m_bOther_CollisonCheck;
	//	오브젝트 모델 출력여부
	HTbool						m_bOther_ShowObject;
};

