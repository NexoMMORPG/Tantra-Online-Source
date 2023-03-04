

#ifndef __HTMAINCHARACTER_H__
#define __HTMAINCHARACTER_H__

#define NEWATTACK_SYSTEM

#include "HTMainCharacterMove.h"

class HTMainCharacter
{
public:
	HTMainCharacter();
	~HTMainCharacter();

	//	ĳ���� ����
	HTvoid						HT_vMainChar_CleanUp();
	//	ĳ���� ����
    HTvoid						HT_vMainChar_Create();
	//	���� ��ȯ�� ���� ĳ���� ����/����
    HTvoid						HT_vMainChar_ChangeSexDelCre( HTshort snTribe, HTbyte byHeadType, HTbyte byFaceType );
	//	�⺻ ����Ÿ ����_����, �̵�, ĳ����
	HTvoid						HT_vMainChar_BasicInfoSetting();
	//	������ ������� �ʴ� ����Ÿ �ʱ�ȭ
	HTRESULT					HT_hrMainCharInitVariable();
	//	�������� �ʱ�ȭ �޾Ƽ� ó���ϱ�
	HTRESULT					HT_hrMainCharInit( HTint iKeyID, HTint iX, HTint iZ, DWORD dwGameTime, HTbyte byClan, HTdword dwTimeStamp[MAX_TIMEITEM]);
	//	���� �ѹ��� ������Ʈ
	HTvoid						HT_vMainChar_OneTimeUpdate();
	//	����ĳ���� �����췯
	HTvoid						HT_vMainChar_Control( HTfloat fElapsedTime );
	//	MouseLbuttonUp���� ������ ��
	HTvoid						HT_vMainChar_MouseLButtonUpCheck( HT_CELL_COORD, HTbool bTargetEffectSw );
	//	�� �ڽ��� Ŭ���ߴ��� �Ǵ�
	HTRESULT					HT_vMainCharMyselfClick();
	//	�� �ڽ��� Ŭ�� ����
	HTvoid						HT_vMainCharMyselfUndoClick();
	//	�ִϸ��̼� ����
	HTvoid						HT_vMainChar_SetChangeAni( BYTE byAniTable, HTint loop, HTfloat fTime, DWORD dwSkillIndex, HTint iAttackAniCount );
	//	�ִϸ��̼� ��_�ִϸ��̼� ����Ʈ üũ
	HTvoid						m_vMainChar_AnmPointCheck();

	//----------ĳ���� ���� ����----------//
	//----------���� ���� ----------//
	HTvoid						HT_vMainChar_SetAttackStatus( DWORD dwTargetKeyID, HTint iModelID, HTbool bForAttack );
	HTvoid						HT_vMainChar_SetAttackCancel( HTint iDebugIndex );
	HTvoid						HT_vMainChar_SetCastCancel();
	//----------���� ��Ʈ��----------//
	HTvoid						HT_vMainChar_AttackControl();
	//	���� ���� �Ϲݰ������� ��ų�������� �Ǵ�, ĳ���� �ð��� �ľ�
	HTvoid						HT_vMainChar_AttackTypeAndCastTimeCheck();
    //----------������ ���� �����̱�----------//
	HTvoid						HT_vMainChar_AttackMove();
	//	��� ��ǥ ����
	HTvoid						HT_vMainChar_TargetPosCheck();
	//	�����Ÿ� ����
    HTvoid						HT_vMainChar_SetAttackRange();
	//	�����Ÿ� üũ
    HTvoid						HT_vMainChar_AttackRangeCheck();
	//	��ġ�⸦ �������� �߰��� ��ֹ��� �ִ��� �˻�
	HTRESULT					HT_hrMainChar_ObstacleCenterCheck( HTvector3 vecTargetPos, HTvector3 vecSourcePos );
	//	���� ���ݽÿ� ���ٰ͵�
	HTvoid						HT_vMainChar_RealAttackControl();
	//	���� ���ø� �������� ������ �ؾ����� ����
	HTvoid						HT_vMainChar_CheckAttackEnd();
	//----------�ִϸ��̼� ���� ����Ʈ���� �ϴ���----------//
	HTvoid						HT_vMainChar_AttackAnmAttackPoint();

	//----------ĳ���� �̵� ����_�ȱ�, �ٱ� ����----------//
	HTvoid						HT_vMainChar_SetMoveType();
	//	ĳ���� �̵� ����_�������Ͽ� Ÿ�� ����
	HTvoid						HT_vMainChar_SetTargetMovePosition( HT_CELL_COORD, HTbool bTargetEffectSw );
	//-----�� �˻�_�ʿ� ����Ʈ ���-----//
	HTvoid						HT_vDrawPickMapEffect( HTvector3 );
	//-----�� �˻�_�ʿ� ���� ����Ʈ üũ�ϱ�-----//
	HTvoid						HT_vInterface_Pick_Map_CheckEffect();
	//-----�� �˻�_�ʿ� ���� ����Ʈ �����ϱ�-----//
	HTvoid						HT_vInterface_Pick_Map_DeleteEffect();

	//----------Ű�� ������ ���� üũ----------//
    HTvoid						HT_vCharSetKeyDownCheck( HTbool );
	//----------Ű�� �������¿��� ������ ��� ����----------//
	HTvoid						HT_vCharSetMoveForward_Go( HTfloat fElapsedTime );
	//----------Ű�� �������¿��� ������ ȸ��----------//
	HTvoid						HT_vCharSetMoveForward_Right();
	//----------Ű�� �������¿��� ���� ȸ��----------//
	HTvoid						HT_vCharSetMoveForward_Left();
    //----------���콺 LButtonDown�϶� ----------//
	HTvoid						HT_vMainChar_SetLButtonDown( HTPoint );
	HTvoid						HT_vMainChar_SetLButtonUp( HTPoint );
	HTvoid						HT_vMainChar_SetLButtonMove( HTPoint );
	HTvoid						HT_vMainChar_LButtonDown_Move();
	//----------ȭ���� �߽����� ���콺 ����Ʈ�� ���� ���� ���ؿ�----------//
	HTfloat						HT_vMainChar_GetLButtonDown_Point();

	//----------ĳ���� �̵� ����_�ȱ�, �ٱ� ���� �ִϸ��̼� ����----------//
	HTvoid						HT_vMainChar_SetMoveAnme();
	//----------ĳ���� ������ ���¸� üũ�Ͽ� ���� �ִϸ��̼� ����----------//
	HTvoid						HT_vMainChar_StopMoveCheck();
	//----------ĳ���� ���� ����----------//
	HTvoid						HT_vMainChar_SetStopMove();
	//----------ĳ���� �ɱ� ����----------//
	HTvoid						HT_vMainChar_SetSit();
	HTbool						HT_bMainChar_GetSitStatus()			{	return m_bMainChar_SitSw;	};

	//----------�̵���� ����----------//
	HTvoid						HT_vMainChar_MovePathSaved();
	//----------�̵���� ��ȯ----------//
	HTvoid						HT_vMainChar_GetMovePath( HTPoint*,  HTint );
	
	//----------������ ��� ����Ʈ ����----------//
	HTvoid						HT_vMainChar_SetItemUseEffect();
	//----------��� �ִϸ��̼� ����----------//
	HTvoid						HT_vMainChar_SetDefence();

	//--------- ������ ���� �������� ���ÿ� ���� ����Ʈ ���� ----------//
	HTvoid						HT_vMainChar_AttachRefineEffect( );

	//	��ų ������ üũ
	HTRESULT					HT_bvMainChar_GetPCSkillAllowedTarget( HTint, BYTE );
	//	�׼� ��ų ����
	HTvoid						HT_vMainChar_SetActionSkill( DWORD dwSkillID );
	//	�׼� ��ų ����_����
	HTvoid						HT_vMainChar_SetActionSkillAffect();
	//	��Ƽ�� ��ų �����췯_StateEffect����
	HTvoid						HT_vMainChar_ControlActiveSkill_ActivateAndState();
	//	��Ƽ�� ��ų ����
	HTvoid						HT_vMainChar_SetActiveSkill( DWORD );
	//	��Ƽ�� ����Ʈ �Ѿ� �ɶ�_STATE_ONCE_TOME_PERATTACK, PERATTACKED
	HTvoid						HT_vMainChar_SetActiveSkillEffect();
	//	��Ƽ�� ��ų ����
	HTvoid						HT_vMainChar_StopActiveSkill();
	
	//----------���� ���ݴ������ �ľ�----------//
	HTvector3					HT_vecMainChar_GetAtkTargetCheck( DWORD );
	//----------���� �޾����� ����� �� �ϵ�----------//
	HTvoid						HT_vMainChar_SetDisAttackCheck( HTint iSkillID, HTint iItemID, HTint iInvadeModelID );
	
	HTvoid						HT_vMainChar_ControlAngle( HTfloat fElapsedTime );
	HTvoid						HT_vMainChar_ControlMove( HTfloat fElapsedTime );
	HTvoid						HT_vCharGetInfomation();
	
	HTvoid						HT_vCharSoundControl();


	//	���°� �ɷ�����
	//	����
	HTvoid						HT_vMainChar_SetTransparency( HTbyte byGMMode, __int64 iAffection );
	//	�������� ���ϰ� ����
	HTvoid						HT_vMainChar_SetCanNotMove( HTbool bEffectSw );
	//	�����̰� ����
	HTvoid						HT_vMainChar_SetCanMove();


	//------------------���� �� ��ȯ����-------------------//
    HTvoid			HT_vMainCHar_SCP_SetAffections( __int64 iAffections );
	HTvoid			HT_vMainChar_SetInitAffectionsEffect();
	__int64			HT_iMAinChar_GetAffections() { return m_iMain_Affections; }
	HTPoint			HT_ptMainChar_GetCellPosition();
	HTvoid			HT_vMainChar_SetCellPosition( HTshort, HTshort );
	HTvoid			HT_vMainChar_SetTotalPrana( HTint );
	DWORD			HT_dwMainChar_GetTotalPrana()		{	return m_iMainChar_TotalPrana;		};
	HTint			HT_vMainChar_GetModelID()			{	return m_iMainChar_ModelID;			};
	HTint			HT_iMainChar_GetKeyID()				{	return m_iMainChar_KeyID;	};
	CHTString		HT_strMainChar_GetTribe();
	HTint			HT_iMainChar_GetTribeServerCode();		//	1,2,4,8,16,32,128
	HTvector3		HT_vecGetPosition();
	HTbool			HT_bMainChar_GetSitDownState()		{	return m_bMainChar_SitSw;	};
	//	�Ϲݰ����̳� ��ų�����̳�
	HTint			HT_iMainChar_GetAttack_Type()		{	return m_nMainChar_Attack_Type;	};
	HTvoid			HT_bMainChar_SetShowName();
	HTvoid			HT_bMainChar_SetShowName( HTbool bTrue );
	HTint			HT_iMainChar_GetAttackTargetKeyID()	{	return m_iMainChar_Target_KeyID; };
	HTfloat			HT_fMainChar_GetShowAngle()			{	return m_fMainChar_ShowAngle; };
	//	Return Get AttackSw
	HTbool			HT_bMainChar_GetAttackSw()			{	return m_bMainChar_AttackSw;	};
	//	Set Return Clan Value
	HTvoid			HT_vMainChar_SetClanValue( HTbyte byClan )		{	m_byMainChar_Clan = byClan;	};
	HTbyte			HT_byMainChar_GetClanValue()					{	return m_byMainChar_Clan;	};
	//	Return Get Click Status
	HTint			HT_iMainChar_GetClickStatus()					{	return m_iMainChar_OneClickIndex;	};

	//	Set �нú� ��ų�� ���� ����Ƽ�� �Ǵ� �����Ÿ�
	HTvoid			HT_vMainChar_SetPassiveSkillRange( HTbyte byRange )	{ m_iMainChar_PassiveSkillRange = byRange; };
	//	Set ���� �����ۿ� ���� �������� �Ǵ� �����Ÿ�
	HTvoid			HT_vMainChar_SetTotemItemRange( HTbyte byRange )	{ m_iMainChar_TotemItemRange = byRange;	};

	HTint						HT_iMainChar_GetAttackPoint();
	HTint						HT_iMainChar_GetDefensePoint();
	
	HTint						HT_nMainChar_GetMAXHP();
	HTvoid						HT_nMainChar_SetMAXHP( HTint nMAXHP );
	HTint						HT_nMainChar_GetResentHP();
	HTvoid						HT_nMainChar_SetDemageHP( CHTString strName, HTint iDemageHP );
	HTvoid						HT_nMainChar_SetCurHP( HTint iCurHP );
	HTfloat						HT_fMainChar_GetDirectAngle();					//----------ĳ������ ���� ������ ��ȯ----------------//
	BYTE						HT_vMainChar_GetHeadType();

	HTvoid						HT_vMainChar_SetWearItem( DWORD );
	HTvoid						HT_vMainChar_SetArmsType( DWORD );// ������ �ε���
	HTvoid						HT_vMainChar_SetWeaponItem( DWORD );
	// ĳ������ ��ɼ� ������ ��ȿ�Ⱓ
	HTvoid						HT_vMainChar_InitTimeStamp( HTdword dwTimeStamp[MAX_TIMEITEM] );
	HTvoid						HT_vMainChar_SetTimeStamp( HTbyte byTimeArrIndex, HTdword dwTime );
	HTvoid						HT_vMainChar_GetTimeStamp( HTbyte byTimeArrIndex, CHTString& szTime );
	HTbool						HT_bMainChar_GetTimeStamp( HTbyte byTimeArrIndex, time_t& timeTime );

	//	Return Get Animation Status
	HTint						HT_iMainChar_GetAnimationStatus()	{	return m_nMainChar_AniResentState;	};
	//	Return Get MoveStop Stauts
	HTbool						HT_bMainChar_GetMoveStopStatus();
	//	Return Get AttackStop Stauts
	HTbool						HT_bMainChar_GetAttackStopStatus();

    //-------------------------------//
	//----------����----------//
	//-------------------------------//
	HTvoid						HT_vCharRender();
	HTvoid						HT_vCharRenderText();

	//	ĳ���� ���� ��ȭ�ֱ�
	HTvoid			HT_vMainChar_SetModelColor( HTfloat r, HTfloat g, HTfloat b, HTfloat fTime );

	//-------------------------------//
	//----------������ ���----------//
	//-------------------------------//
	//----------��Ʈ���� �����Ͽ�----------//
	HTvoid				HT_vNetWork_CharSitAndStand();			//----------Move_�ɱ�, ���� ������ ������----------//
	HTvoid				HT_vMainChar_NetWorkMoveFaild( PS_SCP_RESP_CHAR_MOVE );	//	�������� �̵� ���� �����ޱ�

	HTvoid				HT_vNetWork_CheckCharMove();

	HTvoid				HT_vNetWork_Send_MSGAction( BYTE byDir, HTint iEndX, HTint iEndZ );
	HTvoid				HT_vNetWork_Recive_MSGAction( MSG_Action *info );

	HTvoid				HT_vMainChar_SetBrahman_Rising( PS_SCP_RESP_BRAHMAN_RISING info );
	HTvoid				HT_vMainChar_NetWork_ChattingMessage( BYTE byType, CHTString strMessage );

	//	ĳ���� �״°� ó��
	HTvoid						HT_vMainChar_NetWorkDieMotion();
	HTbool						HT_vMainChar_GetCharLive() { return m_bMainChar_Live; };
	//----------�������� ��Ŷ �����ޱ�-ĳ���� ����� �̴� ������û ���----------//
	HTvoid						HT_vMainChar_SCP_INIT_REGEN_CHAR( HTint nX, HTint nZ );
	
	//----------ĳ������ �����̳� ��Ż �̵������� �ٲ� ĳ������ ��ġ ����----------//
	HTvoid						HT_vMainChar_SetCharacterPosition( HTint nX, HTint nZ, HTint iPosType );

	//	ĳ���Ͱ� �ʿ� �������� ����������
	HTvoid						HT_vMainChar_EscapeCharacterFromNotMoveZone();

	//--------------------------------------//

	//			0x13 Group ? Combat
	HTvoid				HT_vMainChar_CSP_UnitSkill_Start( DWORD dwSkillID, DWORD dwTargetKeyID, HTvector3 vecTargetPos, BYTE bySkillType );
	HTvoid				HT_vMainChar_CSP_AreaSkill_Start( DWORD dwSkillID, DWORD dwTargetKeyID, HTvector3 vecTargetPos, BYTE bySkillType );
	HTvoid				HT_vMainChar_CSP_Cast_Unit_Cast();
	HTvoid				HT_vMainChar_CSP_Cast_Area_Cast();
	HTvoid				HT_vMainChar_SCP_Skill_CastSkill_Broadcast( PS_CSP_CAST_UNIT_SKILL info );
	HTvoid				HT_vMainChar_SCP_Skill_CastSkill_Broadcast( PS_CSP_CAST_AREA_SKILL info );		//	�������� ĳ��Ʈ��ų(����) ������ �˷���

	//	Network_�Ҳɳ���
	HTvoid				HT_vMainChar_SCP_FireFxBroadcast( PS_SCP_FIRE_FX_BROADCAST info );
	//	Set Item Effect
	HTvoid				HT_vMainChar_SCP_SetItemEffect( HTint iItemID );
	
private:
	HTvoid				HT_vShowArea();
	HTvoid				HT_vUpdateAreaIndicate(HTfloat fElapsedTime);
	//--------------------------------------------------------------
	// �޼��� ���
	//--------------------------------------------------------------
	HTvoid				HT_vMainChar_SetMessage( HTint idMessage, CHTString* pszMessage );
	HTvoid				HT_vMainChar_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

private:

	//	��ü ����
	HTint						m_iMainChar_TotalPrana;
	DWORD						m_dwWearItemID;

	// �޼��� ����� ���� ����
	CHTString					m_szEnemyName;	// ���� ���
	HTint						m_iMessageVal;	// ������

	//	ĳ������ ���� ���¸� üũ
	HTint						m_iMainChar_MAX_HP;
	HTint						m_iMainChar_Cur_HP;

	//-----�ִϸ��̼� ��Ʈ�� ����-----//	
	HTint						m_nMainChar_AnmAttackCount;

	//----------ĳ���� �̵� ����----------//
	//-----ĳ���� �ȱ� �ٱ� ���� ����-----//
	HTbool						m_bMainChar_WalkRun_Sw;			// HT_FALSE:�ȱ�, HT_TRUE:�ٱ�

	HTbool						m_bTrrainPick_LoopSw;
	HTint						m_nTrrainPick_ModelID;			// ���� �������� ��ġ ����ִ� ��
	HTint						m_nTrrainPick_EffectID;			// ���� �������� �������� ȿ��
	
	//	�̵��� ȸ��ó��
	HTfloat						m_fMainChar_ShowAngle;
	HTint						m_iMainChar_ProgressAngle;

	// �� ����Ʈ�� ������ ��ġ�� ����
	HTvector3					m_vecPickMapEffect;
	HTbool						m_bShowMapEffect;
	//	ĳ���� �ɱ� ����
	HTbool						m_bMainChar_SitSw;
	//	Target Position
	HTvector3					m_vecTargetPosition;
	//	Model Hight
	HTfloat						m_fModelHeight;

	//	Time Check For Skill
	HTbool						m_bMainChar_TimeCheckForSkillStart;

	//	For �׼ǽ�ų
	HTint						m_iMainChar_OneClickIndex;				//	OneClick �������� üũ
	DWORD						m_bMainChar_ActionSkillIndex;			//	�����Կ��� �Ѿ���� ��ų ��ȣ
	HTint 						m_iMainChar_ReservedActionSkillIndex;	//	�����Կ��� �Ѿ���� ��ų�� ����
	HTbool						m_bMainChar_SetSkillAttackSw;			//	������ F1~F10�� ���� ��ų ���� ��ȣ�� ���Դ���?
	HTbool						m_bMainChar_OnlySkillAttackSw;			//	�Ϲݰ��� ���� ���� ��ų�θ� �ϴ� �����̳�?
	HTbool						m_bMainChar_MapPickAttackSw;			//	�����Ѱ��� �����ϴ� ��ų�̳�?

	//	For ��Ƽ�� ��ų
	HTint						m_iMainChar_ActiveSkillIndex;				//	��Ƽ�� ��ų ���� �ε���
	DWORD						m_dwMainChar_ActiveSkillCurIndex;			//	���� �ߵ��Ǵ� ��Ƽ�� ��ų INDEX
	BYTE						m_byMainChar_ActiveSkillCurLevel;			//	���� �ߵ��Ǵ� ��Ƽ�� ��ų ����
	HTint						m_iMainChar_ActiveSkillEffectID;			//	��Ƽ�� ��ų ����Ʈ ID
	HTint						m_iMainChar_ActiveSkill_StartTime;			//	��Ƽ�� ��ų ����Ʈ �ߵ� ���� �ð�
	HTint						m_iMainChar_ActiveSkill_DurationTime;		//	��Ƽ�� ��ų ���� �ð�
	HTdword						m_dwMainChar_ActiveSkillType;				//	��Ƽ�� ��ų�� ���� �÷���

	//	�нú� ��ų �����Ÿ�
	HTint						m_iMainChar_PassiveSkillRange;				//	�нú� ��ų�� ����Ƽ�� �Ŵ� �����Ÿ�
	//	���� ������ �����Ÿ�
	HTint						m_iMainChar_TotemItemRange;					//	���� ���������� ����Ƽ�� �Ŵ� �����Ÿ�

	//-----������ ���� ����-----//
	HTbool						m_bMainChar_AttackSw;
	HTbool						m_bMainChar_AttackMoveSw;
    HTint						m_iMainChar_Target_KeyID;
	HTint						m_iMainChar_MemoryTargetKeyID;
	HTvector3					m_vecMainChar_TargetPos;				//	���� ����� 3D ��ǥ
	HTPoint						m_pMainChar_TargetPos;					//	���� ����� �� ��ǥ
	HTint						m_nMainChar_Attack_Type;				//	�Ϲݰ����̳� ��ų�����̳�
	HTint						m_nMainChar_AttackAnm;					//	���� �ִϸ��̼� ���� �ε���
	HTint						m_nMainChar_TargetModelID;				//	���� ����� �� ���̵�
	DWORD						m_dwMainChar_AttackStartTime;
	DWORD						m_dwMainChar_AttackSendNetworkTime;		//	������ ���� �޽��� ����
	DWORD						m_dwMainChar_AttackSpeed;
	DWORD						m_dwMainChar_AttackItemSpeed;			//	������ �⺻ ���� �ӵ�
	DWORD						m_dwMainChar_AttackItemSpeedUp;			//	���� ��ῡ ���� �ӵ�
	DWORD						m_dwMainChar_AttackSkillActionSpeed;
	DWORD						m_dwMainChar_AttackSkillActivateSpeed;
	HTint						m_byMainChar_AttackRange;				//	�����Ÿ�
	BYTE						m_byMainChar_AttackRange_Item;			//	�����Ÿ�_������
	HTint						m_iMainChar_AttackRange_ActionSkill;	//	�����Ÿ�_��ų
	BYTE						m_byMainChar_AttackRange_ActivateSkill;	//	�����Ÿ�_��ų
	P_ATTACK_FACTOR				m_sMainChar_AttackFactor;
	HTint						m_iMainChar_RealAttackIndex;			//	���� ���� �ε��� 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	HTint						m_iMainChar_CastEffectID;
	HTint						m_iMainChar_ReadyStartTime;				//	Ready ���� �ð�
	HTint						m_iMainChar_ReadyGaterTime;				//	Ready �ð�
	HTint						m_iMainChar_CastStartTime;				//	Cast  ���� �ð�
	HTint						m_iMainChar_CastGaterTime;				//	Cast  �ð�
	HTint						m_iMainChar_ApplyStartTime;				//	Apply ���� �ð�
	HTint						m_iMainChar_ApplyGaterTime;				//	Apply �ð�

	HTint						m_iMainChar_CastGaterTime_Item;			//	ĳ��Ʈ ���ƾ� �� �ð�_������
	HTint						m_iMainChar_CastGaterTime_ActionSkill;	//	ĳ��Ʈ ���ƾ� �� �ð�_��ų
	DWORD						m_dwMainChar_CastGaterTime_ActivateSkill;//	ĳ��Ʈ ���ƾ� �� �ð�_��ų
	BYTE						m_byMainChar_CriticalHit;
	HTint						m_iMainChar_MaxDamage;
	//	��ǥ������ �ٰ�����:1, �־�����:2
	HTint						m_bMainChar_GoTargetIndex;
	//	��ǥ������ �ٰ����� ����� �󵵼�
	HTint						m_iMainChar_GoTargetCount;
	//	��ǥ������ �ٰ����� ����� �󵵼��� ����
	HTint						m_iMainChar_GoTargetAccumulationCount;
	//	���ݴ���� Size
	HTbyte						m_byMainCHer_TargetSize;
	//	Attack Point ���� ����
	HTbool						m_bMainChar_AttackPointSw;

	//	10�� ������ �̵� ��ǥ�� ������ �����ֱ� ���� ����
	HTvector3					m_vecMainChar_MoveTargetPos;
	HTvector3					m_vecMainChar_MoveResentPos;
	HTbool						m_bMainChar_MoveTargetCheckSw;

	HTvector3					m_vecMainChar_ReqSendMovePos;

	//----------���콺 LButtonDown�϶� ----------//
	BYTE						m_bMouseLbuttonDownMove_Sw;
	HTfloat						m_fMouseLbuttonDownMove_Angle;
	HTbool						m_bMouseLbuttonDownMove_SettingSw;

	//-----�̵���� ����-----//	
	HTPoint						m_pMainChar_MovePath[1000];
	HTint						m_nMainChar_MoveStart;
	HTint						m_nMainChar_MoveResent;
	HTbool						m_bMainChar_OneTimeRotate;
	HTint						m_nMainChar_MovePathCount;

	//-----���� �޾��� ���� HP ���� üũ-----//	
	HTbool						m_bMinaChar_HitDamage;

	//-----���̵� ������ ����-----//
	DWORD						m_dwMainChar_IdlTime;

	//-----�ɱ� ���� �����̸� ����-----//
	DWORD						m_dwMainChar_sitTime;

	//-----ȭ���� �Ͼ�� ���ϴ� ������ ���� ����-----//
	HTbool						m_bMainChar_WhiteError;

	//-----�ɾ� ������ �����ϸ� ������ġ ����-----//
	HT_CELL_COORD				m_crdSitCell;

	//-----����ģ ä�� �޽���-----//
	CHTString					m_strMainChar_ChatMsg;
	DWORD						m_dwMainChar_ChatMsgDelayTime;

	//-----����ģ ä�� �޽���-----//
	HTbool						m_bMainChar_ShowNameSw;

		// Area Indicate
	HTint						m_iPrevArea;
	HTint						m_iArea;
	CHTString					m_strAreaName;
	HTfloat						m_fIndicateTime;
	HTbool						m_bAreaIndicated;

	// ���⸦ �ڷ� á������ ���� �÷���
	HTbool						m_bIsWeaponArmed;

	//	�´� ������ �� �� �ִ� ��� üũ
	HTbool						m_bMainChar_HitEventCanSw;
	//	����, �ȱ�, �ٱ�, ����, �±�, �ױ�, �ɱ�, ��������, ����, �ı��, ��ų�غ�, ��ų������, ��ų����
	HTint						m_nMainChar_AniResentState;
	//	�����߿� �ٸ� �̺�Ʈ�� ������ �ִ°Ͱ� ���°� ����
	HTbool						m_bMainChar_AniEventCanSw;
	//	���� �ִϸ��̼��� üũ �ؾߵ� �ִ��ϰ��
	HTbool						m_bMainChar_AniStdCheckSw;
	//	�̵� �޽��� ������ �ø��� �׶��� ��ġ ����
	HTPoint						m_pMainChar_SaveMovePos;

	//	Item�� Ȱ �ϰ��
	HTbool						m_bMainChar_ItemArrow;

	HTint						m_iFootSound;
    HSAMPLE						m_hFoootSound;
	//	�������� FX
	HTint						m_iMain_FaintingstateFX;
	//	Ÿ������ FX
	HTint						m_iMain_TargettingFx;
	//	�������� �������� ĳ���� ����
	__int64						m_iMain_Affections;
	//	Affections ���� FX
	HTint						m_iMain_FXAffections;
	//	��Ƽ�� ����Ʈ �Ѿ� �ɶ�_STATE_ONCE_TOME_PERATTACK, PERATTACKED
	HTint						m_iMain_ActiveImpactFXID;
	//	Effect of MSG_Action
	HTint						m_iMain_ActionEffect;
	//	Move Action On/Off
	HTbool						m_bMainChar_MoveSw;
	//	Temp Speed for MSGAction Effect
	HTint						m_iMinaChar_TempSpeedForMSGAEffect;
	//	Clan Value
	HTbyte						m_byMainChar_Clan;

public:

	//-----�̵� Ŭ����-----//	
	CHTMainCharMove*			m_cMainCharMove;
	HTint						m_byTimeArrIndex;
	//	����ĳ���� ����
	HTint						m_iMainChar_KeyID;
	DWORD						m_dwWeaponItemID;
	HTint						m_iMainChar_ModelID;
	HTbool						m_bMainChar_Live;
	HTbool						m_bMainChar_Reviving;
	time_t						m_timeMainChar_TimeStamp[MAX_TIMEITEM];
	HTint						m_iGuildSerial;
	//	���� ĳ����
	HTint						m_iMainChar_ShopCharID;
};

#endif
