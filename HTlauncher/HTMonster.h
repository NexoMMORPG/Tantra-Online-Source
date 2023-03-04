

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
	
	HTvoid						HT_vMonsterSet_physical_CellMove( HTfloat );	//	���� �������� ������ - ȭ��󿡼� ������ ��

	HTvoid						HT_vMonster_AnimationControl();			//	���� �ѹ��ϰ� �ߴ�
	HTvoid						HT_vMonster_AnimationControl_WlkRun();	//	�ȱ�/�ٱ� ��Ʈ��

	//---------������Ʈ----------//
	HTvoid						HT_vMonsterUpdate( HTfloat );
	//---------������Ʈ_������ ���Ͽ�----------//
	HTvoid						HT_vMonsterUpdate_Death();
	//---------���� �޾��� ��_�´� �׼� ��----------//
	HTbool						HT_vMonster_SetDisAttackOn( DWORD, BYTE, HTfloat, HTint );
	//---------HP ������� üũ----------//
	HTint						HT_vMonster_SetHPCheck( DWORD dwInvadeKeyID, HTint nCurHP, HTint nDamageHP, BYTE byInvadeType, HTvector3 vecInvadePos, HTint nInvadeModelID );
	//---------���� ���÷��� ����----------//
	HTvoid						HT_vMonster_SetInfoDisplay(HTbool bAttack);
	//---------���� ���÷��� �������----------//
	HTvoid						HT_vMonster_SetInfoCancel();
	
	//---------�ִϸ��̼� ����----------//
	HTvoid						HT_vMonster_SetAnimation( HTint );

	//---------����Ʈ_����Ʈ ����Ʈ Ʋ���ֱ�----------//
	HTvoid						m_vMonsterAttack_ImpactEffect( DWORD dwIndex, BYTE byLevel, HTint iItemIndex );
	//---------����Ʈ_���� �׾����� ���������͵�----------//
	HTvoid						m_vMonster_WhenDeathEffect();

	//-----������ ��Ʈ��ũ-----//
	HTvoid						HT_vMonsterSet_logical_CellEnd( MSG_Action* sInfo );		//	���� ������ ��
	//-----------�����Ѵ�----------//
	HTvoid						HT_vMonster_RotateAttack( HTvector3 );
	HTvoid						HT_vMonster_AttackPointCheck();			//	������ ��������Ʈ���� ����
	//-----------���Ͱ� �״´�----------//
	HTvoid						HT_vMonster_Network_Death();
	//-----------���Ͱ� �ڷ���Ʈ �Ѵ�----------//
	HTvoid						HT_vMonster_Network_Teleport();
	//	���ݹ޾����� ���� ������
	HTvoid						HT_vMonster_ScaleControl();

	//	���Ͱ� ������ ��
	HTvoid						HT_vMonster_Network_SCP_Msg_Attack( S_MSG_ATTACK_OTHERMOB info );

private:


public:
	CHTMoveMonSter*				m_cMoveMonster;

    DWORD						m_iMonsterKeyID;
	HTint						m_iMonsterModelID;						//	���� �� ID
	HTint						m_iMonsterIndex;						//	���͸� �����ϱ� ���ؼ�,
	HTint						m_nMonster_ResentAnm;					//	���� ������ �ִϸ��̼�
	CHTString					m_strName;
//	BYTE						m_byMaxAttackDistance;					//	�ִ� ���� �Ÿ�
	HTint						m_iMaxAttackDistance;
	BYTE						m_byMonster_Size;						//	������ ũ��
	
	//-----������ ���� HP���¸� üũ-----//
	HTint						m_nMonster_MAX_HP;
	HTint						m_nMonster_Resent_HP;

	//-----���ݰ� �����Ͽ�-----//
	HTbool						m_bMonster_AttackSw;
	HTbool						m_bMonster_DisAttackSw;
	HTint						m_nMonster_Live;
	BYTE						m_byMonster_InvadeType;				//	0x03:MainChar, 0x01:OtherChar
	HTint						m_nMonster_InvadeModelID;			//	���͸� ������ ĳ������ �� ���̵�
	DWORD						m_dwMonster_InvadeKeyID;
	BYTE						m_byMonster_AttackTarget;			//	0x01:OtherChar, 0x03:MainChar
	DWORD						m_dwMonster_TargetKeyID;			//	���ݹ��� ����� KeyID
	DWORD						m_dwMonster_Skill;					//	������ ���
	BYTE						m_byMonster_AttackType;				//	���� Ÿ��
	HTvector3					m_vecMonster_TargetPos;				//	���ݴ���� ��ġ
	BYTE						m_byMonster_CriticalHit;			//	Ŀ��Ƽ�� ��
	HTint						m_nMonster_AttackTargetModelID;		//	���ݴ���� �� ���̵�
	HTint						m_nMonster_TargetHP;				//	���ݹ��� ����� HP
	HTint						m_nMonster_DamageHP;

	BYTE						m_byMonster_ActonEffect;

	//-----���� ���÷���-----//
	HTbool						m_bMonster_InfoShow_Sw;
	
	//-----������ ���� ����Ʈ-----//
	HTbool						m_bMonster_Death_Sw;
	DWORD						m_bMonster_Death_Delay;

	//-----�¾����� �̵����̸� �̵����� ����-----//
	HTbool						m_bMOnster_HitMove_Sw;

	//-----���� ����/���� ����-----//
	HTint						m_nMonster_HitCount;

	//	���� �Ǿ����� �����ִ� ����Ʈ
	HTint						m_nTargettingEffectID;

	//-----���� ���̵� ������ ����-----//
	DWORD						m_nMonster_IdlDelay;

	//-----���� HP ǥ���ϱ����� ����ĳ���Ͱ� ����������-----//
	HTbool						m_bAttack_FromMainChar;

	HTint						m_iMonster_ScaleIndex;			//	������ �ε���
	HTfloat						m_fMonster_ScaleValue;			//	������ ��
	HTfloat						m_fMonster_ScaleValueTrans;		//	������ ��ȭ ��

	HTfloat						m_fMonsterModelHeight;

	P_ATTACK_FACTOR				m_sMonster_AttackFactor;

	//	�ӽ�
	short						m_snMonster_TargetX;
	short						m_snMonster_TargetZ;
};

#endif

