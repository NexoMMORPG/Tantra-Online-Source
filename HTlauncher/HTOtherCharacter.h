
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

	//---------����Ʈ_����Ʈ ����Ʈ Ʋ���ֱ�----------//
	HTvoid						m_vOtherCharAttack_ImpactEffect( DWORD dwSkillIndex, HTint iItemIndex );
	HTvoid						HT_vOtherChar_ActiveSkillEffectOn();
	HTvoid						HT_vOtherChar_ActiveSkillEffectOff();

	//	��� ��ũ ���� �ϱ�
	HTvoid						HT_vOtherChar_SetGuildMarkID( HTint iGuildMarkID );
	//	��� ��ũ ǥ�� �ϱ�
	HTvoid						HT_vOtherChar_GuildEmblemOn();
	//	��� ��ũ ǥ�� ���ϱ�
	HTvoid						HT_vOtherChar_GuildEmblemOff();
	//	�ֽ� ���� �ϱ�
	HTvoid						HT_vOtherChar_SetTrimuritiD( BYTE byTrimuritii );
	//	�ֽ� ��ũ ǥ�� �ϱ�
	HTvoid						HT_vOtherChar_TrimuritiMarkOn();
	//	�ֽ� ��ũ ǥ�� ���ϱ�
	HTvoid						HT_vOtherChar_TrimuritiMarkOff();

	HTvoid						HT_vOtherChar_MoveControl( HTfloat fElapsedTime );
	//---------�������� �Ǻ��Ͽ� �������ش�----------//
	HTvoid						HT_vOtherChar_SetItemType( BYTE byPart, STRUCT_ITEMVIEW info );

	//---------�ִϸ��̼�----------//
	//	ĳ���� �ִϸ��̼� ����
	HTvoid						HT_vOtherChar_SetChangeAni( HTint loop, HTfloat fTime, DWORD dwSkillIndex );
	HTvoid						HT_vOtherChar_AnimationControl();

	//---------���� ���÷��� ----------//	//2003.1.3 �����߰�
	HTvoid						HT_vOtherChar_SetInfoDisplay();
	HTvoid						HT_vOtherChar_SetInfoCancel();

	//-----------�ȵ� �����ΰ� üũ----------//
	HTRESULT					HT_hrOtherChar_GetInfoStatus();

	//	��ü ���� ����
	//-----------���ݴ��� ���� �ؾ����ϵ�----------//
	HTvoid						HT_vOtherChar_SetAttack( DWORD, BYTE byAttackType, HTint iItemIndex );
	//-----------��������Ʈ���� �ؾ����ϵ�----------//
	HTvoid						HT_vOtherChar_AttackPointCheck();
	//---------HP ������� üũ----------//
	HTint						HT_nOtherChar_SetHPCheck( HTint nHP );
	HTvoid						HT_vOtherChar_RotateAttack( HTvector3 );		//	�����ڸ� ���� ȸ��
	HTvoid						HT_vOtherChar_AttackPosCheck( HTint, HTint );	//	�������� ��ġ ����
	//-----------��ų ����----------//
	HTvoid						HT_vOtherChar_SetActiveSkill( PS_SCP_RESP_SKILL_SELECT_BROADCAST info );
	//	��Ƽ�� ��ų ����� �޾��� �� Effect Ʋ��
	HTvoid						HT_vOtherChar_SetActiveSkillEffectOn( DWORD dwSkillIndex, HTbool bType, BYTE byLevel );
	//-----------��Ƽ�����μ� ���� �� Ż���Ҷ�----------//
	HTvoid						HT_vOtherChar_SetPartyJoineDisband( BYTE );

	//----------������ ����ϴ� ��Ʈ��ũ �Լ�---------//
	//	Other Character LevelUp �� �˸�
	HTvoid						HT_vOtherChar_LevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info );
	//	GM�� �����带 ���� �Ǵ� ������ ��û�Ѵٸ� �˸���
	HTvoid						HT_vNetWork_SCP_TRANSPARENCY_MODE_NOTIFY( PS_SCP_TRANSPARENCY_MODE_NOTIFY );
	//	������ �ٸ�ĳ������ �̵��� �˷����� ��
	HTvoid						HT_vNetWork_OtherChar_Action( MSG_Action* info );
	//	��ų ������ �˸�
	HTvoid						HT_vOtherChar_Ready_Char_Broadcast( PS_SCP_SKILL_READY_CHAR_BROADCAST info );
	//	��ų ������ �˸�
	HTvoid						HT_vOtherChar_Network_Skill_Cast_Broadcast( S_MSG_ATTACK_OTHERMOB );
	//	OtherChar ���� ó��
	HTvoid						HT_hrOtherChar_Death();
	//	OtherChar ���� ó�� ������
	HTvoid						HT_hrOtherChar_DeathDelay();


public:

	CHTString					m_iOtherCharName;					//	�̸�
    CHTString					m_strOtherChar_GuildName;			//	��� �̸�
	BYTE						m_byOtherChar_Level;				//	�ٸ�ĳ������ ����
	
	BYTE						m_byOtherChar_SpecialName;			//	Ư��Īȣ
	DWORD						m_dwOtherCharKeyID;					//	������ �к��� ���� ID
	HTint						m_iOtherCharModelID;				//	�ٸ�ĳ���� ID
	BYTE						m_byOtherChar_TribeType;			//	���� Ÿ��
	BYTE						m_byOtherChar_FaceType;				//	��
	BYTE						m_byOtherChar_HairType;				//	�Ӹ�
	CHTString					m_sOtherCharAnimation[3][10];		//	�ִϸ��̼� ID
	DWORD						m_dwEquipItem[16];					//	������ �ε���
	BYTE						m_byOtherChar_PartyMember;			//	0x01:��Ƽ����ƴ�, 0x02:��Ƽ���
	DWORD						m_dwOtherChar_GuildEmblemID;		//	��� ��ũ
	
	HTint						m_iOtherCharCellSizeX;				//	�ٸ�ĳ���Ͱ� ġ���ϴ� ��X
	HTint						m_iOtherCharCellSizeZ;				//	�ٸ�ĳ���Ͱ� ġ���ϴ� ��Z

	CHTOtherCharMove*			m_cOtherCharMove;
	BYTE						m_bOtherCharMoveState;				//	ĳ������ �̵�����
	BYTE						m_bOtehrCharMoveDir;				//	�������

	//-----�ִϸ��̼� ��Ʈ�� ����-----//
	HTint						m_nOtherChar_WeaponItemID;
	HTint						m_nOtherChar_WearItemID;
	HTint						m_nOtherChar_AniResentState;
	HTint						m_nOtherChar_AttackType;
	HTbool						m_bOtherChar_AttackSw;
	HTint						m_iOtherChar_AttackAniCount;
	HTbool						m_bOtherChar_ActiveSkillIngSw;

	//-----ĳ������ ���� HP���� / ������ üũ-----//
	HTint						m_nOtherChar_MAX_HP;
	HTint						m_nOtherChar_Resent_HP;
	HTbool						m_bOtherChar_Info_Sw;
	DWORD						m_bOtherChar_HPShow_StartTime;
	
	//-----�¾Ҵ��� üũ-----//
	HTbool						m_bOtherChar_HitSw;

	//-----����Ʈ ���� �ε���-----//
	HTint						m_nEffect_ActiveSkillID;
	DWORD						m_dwActiveSkillIndex;
	BYTE						m_byActiveSkillLevel;

	//	���� ����
	HTvector3					m_vecAttack_TargetPos;			//	���� ȿ�� ��ġ
	HTint						m_nAttack_TargetModelID;		//	����Ÿ���� �� ���̵�
	BYTE						m_byOtherChar_AttackTarget;		//	0x01:MainChar,0x02:OtherChar,0x03:Monster
	DWORD						m_dwOtherChar_TargetKeyID;		//	���ݹ��� ����� KeyID
	HTint						m_nOtherChar_TargetHP;			//	���ݹ��� ����� HP
	HTint						m_nOtherChar_HitCount;			//	���� ������
	HTbool						m_bOtherChar_CastSw;			//	ĳ��Ʈ ����
	HTint						m_iOtherChar_CastEffectID;		//	ĳ��Ʈ ����Ʈ ID
	BYTE						m_byOtherCharCriticalHit;		//	Ŀ��Ƽ�� �� ���� ����
	short						m_snOtherChar_Demage;
	BYTE						m_byOtherChar_Trimuriti;		//	�ֽ�

	//	��ų ���� ����
	DWORD						m_dwOhterChar_SkillID;				//	OtherChar ��ų ID
	DWORD						m_dwOhterChar_SkillLevel;			//	OtherChar ��ų Level
	HTdword						m_dwOtherChar_SkillType;			//	��ų Type
	HTint						m_iOtherChar_SkillCastTime;			//	ĳ���� �ð�
	HTbool						m_bOtherChar_SkillCastTimeSw;		//	ĳ���� üũ ����
	HTint						m_iOtherChar_SkillCastStartTime;	//	ĳ���� ���� �ð�
	HTint						m_iOtherChar_SkillEffectID;

	//	�����߿� �ٸ� �̺�Ʈ�� ������ �ִ°Ͱ� ���°� ����
	HTbool						m_bOtherChar_AniEventCanSw;

	//-----���̵� ������ ����-----//
	DWORD						m_dwOtherChar_IdlTime;

	//-----OtherChar ���� ó��-----//
	HTint						m_nOtherChar_Death;
	DWORD						m_dwOtherChar_DeathDelay;

	HTfloat						m_fModelHeight;		//	���� ���� Ű

	//-----�������� �ƴ��� üũ-----//
	HTbool						m_bAssistantSw;		//	InitOtherChar �϶�, ��/Ż���ÿ� üũ

	//	ä�ø޽���
	BYTE						m_byOtherChar_ChattingType;
	CHTString					m_strOtherChar_ChattingMessage;
	DWORD						m_dwOtherChar_ChatMsgDelay;

	P_ATTACK_FACTOR				m_sOtherChar_AttackFactor;

	// ���⸦ �ڷ� á������ ���� �÷���
	HTbool						m_bIsWeaponArmed;
};

#endif



