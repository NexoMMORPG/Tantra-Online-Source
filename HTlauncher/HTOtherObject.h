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
	//	Control AttackPointCheck From Time -> ������ ���� ���ʹ� �ִϸ��̼� ����Ʈ�� ���ƿ��� �ʱ� ������ �ð����� üũ�ؾ��Ѵ�.
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
	//	Setting ������ ���� �������� ���ÿ� ���� ����Ʈ ����
	HTvoid						HT_vOtherObject_SetAttachRefineEffect();
	//	Setting Targetting
	HTvoid						HT_vOtherObject_SetTargetting();
	//	Setting Collison
	HTvoid						HT_vOtherObject_SetCollison();

	//	Network
	//	Network	LevelUp Brodcast
	HTvoid						HT_vOtherObject_NetworkLevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info );
	//	Network	GM�� �����带 ���� �Ǵ� ������ ��û�Ѵٸ� �˸���
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
	//	������ �����ڵ�
	HTint						m_iOther_TribeCode;
	//	MoveSystem
	HTOtherObjectMove*			m_pOther_MoveSystem;
	//	AttackSystem
    P_ATTACK_FACTOR				m_oOther_AttackFactor;
	//	Animation State
	HTint						m_iOther_AniResentState;
	//	Atk Animation Count
	HTint						m_iOther_AttackAniCount;
	//	������ �ε���
	HTint						m_iOther_EquipItem[16];
	//	������ �Ӽ��� ���� ��Ʈ���� �ʿ���.
	HTbyte						m_byOther_MainRef[16];
	//	������ ���÷���
	HTbyte						m_byOther_RefineLevel[16];
	//	���⸦ ��� �ִ°�?
	HTbool						m_bOther_IsWeaponArmed;
	//	��
	HTint						m_iOther_WearItemID;
	//	����
	HTint						m_iOther_WeaponItemID;
	//	������?
	HTbool						m_bOther_AssistantSw;
	//	Info Display
	HTbool						m_bOther_InfoSw;
	//	Live
	HTint						m_iOther_LiveIndex;
	//	Live DelayTime
	HTint						m_iOther_LiveDelayTime;
	//	Idle
	HTint						m_iOther_IdlTime;
	//	�̵��� ȸ��ó��_����
	HTfloat						m_fOther_ShowAngle;
	//	�̵��� ȸ��ó��_����
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
	//	���� �޴°Ϳ� ���� Object�� �����.
	HTbool						m_bStopWhenInvadeSw;
	//	���� �޾����� �̵��ؼ� �����°� ����
	HTbool						m_bOther_AttackMoveSw;
	//	���� ����� Demage Count
	HTint						m_iOther_TargetDamageHP[TN_MAX_TARGET_COUNT];
	//	���� ����� HP
	HTint						m_iOther_TargetHP[TN_MAX_TARGET_COUNT];
	//	Ŀ��Ƽ�� ��
	HTbyte						m_byOther_TargetRes[TN_MAX_TARGET_COUNT];
	//	Effect of MSG_Action
	HTint						m_iOther_ActionEffect;
	//	��Ʈ�� ������
	HTbyte						m_byOther_Size;
	//	������ ��ų���� �Ӽ�
	__int64						m_iOther_TargetAffaction;
	//	������ ���� ���ʹ� �ִϸ��̼� ����Ʈ�� ���ƿ��� �ʱ� ������ �ð����� üũ�ؾ��Ѵ�.
	HTbool						m_bOther_AtkPtFromTimeSw;
	HTint						m_iOther_AtkptFromTimeDelay;
	HTint						m_iOther_AtkptFromTimeStartTime;
	//	���� ����Ʈ üũ
	HTbool						m_bOther_AtkptCheck;
	//	Down Earth
	HTbool						m_bOther_DownEarthSw;
	//	Object Name
	CHTString					m_strOther_Name;
	//	Affections ���� FX
	HTint						m_iOther_FXAffections;
	//	My Guild Member
	HTbool						m_bOther_MyGuildMemberSw;
	//	WizardEyesSw
	HTbool						m_bOther_MainCharWizardEyesSw;
	//	Cast Name
	CHTString					m_strOther_CastName;
	//	���ݰ����� ������� üũ
	HTbool						m_bOther_DefinZoneAttackTarget;
	//	Turn Point For Yut Move
	int							m_iOther_EndPoint;
	//	End Point For Yut Move
	HTPoint						m_pOther_EndPoint;
	//	������ Object�� Ÿ�� ������ Object���� ����
	HTbool						m_bOhter_Targetting;
	//	�浹üũ �ž� �ϴ°��
	HTbool						m_bOther_CollisonCheck;
	//	������Ʈ �� ��¿���
	HTbool						m_bOther_ShowObject;
};

