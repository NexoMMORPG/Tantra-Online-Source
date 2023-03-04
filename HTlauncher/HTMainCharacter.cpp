
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTMainCharacter.h"

#define _AREAINDICATE_TIME	2.0f
#define	_ACTIVESKILL_CONTINUETIMECONNECT	1000

#define ATTACK_NONECLICK		0
#define ATTACK_ONECLICK			1
#define ATTACK_DOUBLECLICK		2


HTMainCharacter::HTMainCharacter()
{
	m_iMainChar_ModelID = -1;
	m_bShowMapEffect = HT_TRUE;
	m_dwWeaponItemID = -1;
	m_nTrrainPick_ModelID = -1;
	m_sMainChar_AttackFactor = HT_NULL;
	m_iMain_ActionEffect = -1;
	// Area Indicate
	m_iPrevArea			= -1;
	m_iArea				= -1;
	m_strAreaName		= _T("");
	m_fIndicateTime		= 0.0f;
	m_bAreaIndicated	= HT_FALSE;
	m_bIsWeaponArmed	= HT_FALSE;
	//	��ų ��Ÿ�� ����ġ
	m_iMainChar_ActiveSkillIndex = 0;
	//	MoveSystem
	m_cMainCharMove = HT_NULL;
	//	Affections ���� FX
	m_iMain_FXAffections = -1;
	//	��Ƽ�� ����Ʈ �Ѿ� �ɶ�_STATE_ONCE_TOME_PERATTACK, PERATTACKED
	m_iMain_ActiveImpactFXID = -1;
	//	Time Check For Skill
	m_bMainChar_TimeCheckForSkillStart = HT_TRUE;
	//	Clan Value
	m_byMainChar_Clan = 0;
}

HTMainCharacter::~HTMainCharacter()
{
}

//	�� �����
HTvoid HTMainCharacter::HT_vMainChar_CleanUp()
{
	//	���� ���� ����
	HT_DELETE( m_sMainChar_AttackFactor );
	HT_DELETE( m_cMainCharMove );

	if ( m_nTrrainPick_ModelID > 0 )
	{
		g_pEngineHandler->HT_vDestroyObject( m_nTrrainPick_ModelID, 14 );
		m_nTrrainPick_ModelID = -1;
	}

	g_pEngineHandler->HT_vDestroyCharacter( m_iMainChar_ModelID, 9 );

	g_bMainCharacterInitialized = HT_FALSE;
}

//	ĳ���� Model ����
HTvoid HTMainCharacter::HT_vMainChar_Create()
{//fors_debug �ı��������͵ط�
	//	ĳ���� �� ����                                       //g_oMainCharacterInfo.snTribe
	m_iMainChar_ModelID = g_pEngineHandler->HT_iCreateCharacter(g_oMainCharacterInfo.snTribe , m_cMainCharMove->HT_vecGetPosition(), g_oMainCharacterInfo.byHeadType, g_oMainCharacterInfo.byFaceType );
	g_pEngineHandler->HT_hrSetMainChar( m_iMainChar_ModelID );
	//	g_pEngineHandler->HT_hrRotateObject( m_iMainChar_ModelID, HT_PI );
	
	//	�� ������
	m_fModelHeight = g_pEngineHandler->HT_fGetObjHeight( m_iMainChar_ModelID );

	//	ĳ���� ����,��ġ,�ִϸ��̼� ����
	g_pEngineHandler->HT_hrStartAnimation( m_iMainChar_ModelID, g_oMainCharacterInfo.snTribe, HT_ANISTATE_STD, -1 );

	//	���� �������� ��ġ ����ִ� ��
	m_nTrrainPick_ModelID	= g_pEngineHandler->HT_iCreateNullModel( HTvector3( 100, 100, 100 ) );
	m_bTrrainPick_LoopSw	= HT_FALSE;
	//	���� ��
	if( m_timeMainChar_TimeStamp[eTime_Store] < 0 )	m_iMainChar_ShopCharID	= g_pEngineHandler->HT_iCreateMonster( 2482, HTvector3( 100, 100, 100 ) );
	else											m_iMainChar_ShopCharID	= g_pEngineHandler->HT_iCreateMonster( 2483, HTvector3( 100, 100, 100 ) );

	//	Init Map
	g_pEngineHandler->HT_hrLoadMapObjsInitial( m_cMainCharMove->HT_vecGetPosition() );

	//	NPC ����
	g_sNPCSystem->HT_vNPCSystem_CreateNPC();
}

//	���� ��ȯ�� ���� ĳ���� ����/����
HTvoid HTMainCharacter::HT_vMainChar_ChangeSexDelCre( HTshort snTribe, HTbyte byHeadType, HTbyte byFaceType )
{
	//	�� ����
	g_pEngineHandler->HT_vDestroyCharacter( m_iMainChar_ModelID, 9 );
	g_pEngineHandler->HT_vDestroyCharacter( m_iMainChar_ShopCharID, 9 );
	//	ĳ���� �� ����
	m_iMainChar_ModelID = g_pEngineHandler->HT_iCreateCharacter( snTribe, m_cMainCharMove->HT_vecGetPosition(), byHeadType, byFaceType );
	g_pEngineHandler->HT_hrSetMainChar( m_iMainChar_ModelID );
	//	�� ������
	m_fModelHeight = g_pEngineHandler->HT_fGetObjHeight( m_iMainChar_ModelID );
}

//	�⺻ ����Ÿ ����_����, �̵�, ĳ����
HTvoid HTMainCharacter::HT_vMainChar_BasicInfoSetting()
{
	//	���� �ӵ�
	m_dwMainChar_AttackItemSpeed	= 0;
	m_dwMainChar_AttackItemSpeedUp	= 0;
	m_dwMainChar_AttackSkillActionSpeed	= 0;
	m_dwMainChar_AttackSkillActivateSpeed = 0;
	//	ĳ���� �ӵ�
	m_iMainChar_CastGaterTime = 0;
}

HTRESULT HTMainCharacter::HT_hrMainCharInitVariable()
{
	//	Char Cur HP
	m_iMainChar_MAX_HP = 0;
	m_iMainChar_Cur_HP = 0;

	//	���� �ʱ�ȭ
	m_iMainChar_TotalPrana			= 0;
	//	OneClick �������� üũ
	m_iMainChar_OneClickIndex		= ATTACK_NONECLICK;
	//	F1~F10�� ���� ��ų ���� ��ȣ�� ���Դ���?
	m_bMainChar_SetSkillAttackSw	= HT_FALSE;
	//	�Ϲݰ��� ���� ���� ��ų�θ� �ϴ� �����̳�?
	m_bMainChar_OnlySkillAttackSw	= HT_FALSE;
	//	�����Կ��� �Ѿ���� ��ų ��ȣ
	m_bMainChar_ActionSkillIndex	= 0;
	//	�нú� ��ų�� ����Ƽ�� �Ŵ� �����Ÿ�
	m_iMainChar_PassiveSkillRange	= 0;
	//	���� �����ۿ� ���� �������� �Ǵ� �����Ÿ�
	m_iMainChar_TotemItemRange = 0;
	//	ĳ���� �ð�
    m_dwMainChar_AttackSpeed = 0;
    
	m_bTrrainPick_LoopSw	= HT_FALSE;
	//	����ĳ���� �̵� Ŭ���� �ʱ�ȭ
	m_cMainCharMove = HT_NULL;
	m_cMainCharMove = new CHTMainCharMove;

	//	����ĳ������ ���ݺ����� �ʱ�ȭ---------//
	m_iMainChar_MemoryTargetKeyID	= 0;
	m_nMainChar_AttackAnm			= 1;
	m_bMainChar_AttackSw			= HT_FALSE;
	m_bMainChar_AttackMoveSw		= HT_FALSE;
	m_dwMainChar_AttackStartTime	= GetTickCount();
	m_iMainChar_CastEffectID		= -1;
	//	���� ���� �ε��� 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	m_iMainChar_RealAttackIndex		= 1;
	m_bMainChar_MapPickAttackSw		= HT_FALSE;

	//	�����Ÿ� ����
	m_byMainChar_AttackRange_Item			= 0;
	m_iMainChar_AttackRange_ActionSkill		= 0;
	m_byMainChar_AttackRange_ActivateSkill	= 0;

	//	���� ���� ����
	m_sMainChar_AttackFactor		= HT_NULL;
    m_sMainChar_AttackFactor		= new S_ATTACK_FACTOR;
	
	m_nMainChar_AniResentState		= CHARACTER_ANISTATE_STD;
	m_nMainChar_AnmAttackCount		= 0;

	HT_CELL_COORD crdCell;
	HTvector3 vecPos;
	crdCell.x = 1000;
	crdCell.y = 500;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( vecPos, crdCell );
	vecPos.y = g_pEngineHandler->HT_fGetTerrainHeight( vecPos.x, vecPos.z );
	m_cMainCharMove->HT_vSetPosition( vecPos );

	//----------ĳ���� �̵� ����----------//
	//-----ĳ���� �ȱ� �ٱ� ���� ����-----//
	m_bMainChar_WalkRun_Sw	= HT_TRUE;			//	HT_FALSE:�ȱ�, HT_TRUE:�ٱ�

	//----------ĳ���� �ɱ� ����----------//
	m_bMainChar_SitSw		= HT_FALSE;

	m_nMainChar_MoveStart			= 0;
	m_nMainChar_MoveResent			= 0;
	m_bMainChar_OneTimeRotate		= HT_FALSE;
	m_nMainChar_MovePathCount		= 0;

	//	�´� ������ �� �� �ִ� ��� üũ
	m_bMainChar_HitEventCanSw		= HT_FALSE;

	//-----���̵� ������ ����-----//
	m_dwMainChar_IdlTime			= 0;
    
	//-----ȭ���� �Ͼ�� ���ϴ� ������ ���� ����-----//
	m_bMainChar_WhiteError			= HT_FALSE;

	m_bMainChar_ShowNameSw = HT_TRUE;

	//	10�� ������ �Ÿ��� üũ�Ҷ�
	m_bMainChar_MoveTargetCheckSw = HT_FALSE;
	//	Item�� Ȱ �ϰ��
	m_bMainChar_ItemArrow = HT_FALSE;
	//	�������� FX
	m_iMain_FaintingstateFX = 0;
	//	��ǥ������ �ٰ�����:HT_TRUE, �־�����:HT_FALSE
	m_bMainChar_GoTargetIndex = 0;
	//	������ SIZE ���
	m_byMainCHer_TargetSize = 0;

	return HT_OK;
}

//---------�������� ĳ���� �ʱ������� �޴°�---------//
HTRESULT HTMainCharacter::HT_hrMainCharInit( HTint iKeyID, HTint iX, HTint iZ, DWORD dwGameTime, HTbyte byClan, HTdword dwTimeStamp[MAX_TIMEITEM] )
{
	m_bMainChar_Reviving = HT_FALSE;
	m_pMainChar_SaveMovePos.x = iX;
	m_pMainChar_SaveMovePos.y = iZ;
	//	Set Clan Value
	m_byMainChar_Clan = byClan;
	//	KeyID Setting
	m_iMainChar_KeyID = iKeyID;
	//	���� ��� ����
	m_iMainChar_Target_KeyID = m_iMainChar_KeyID;
	//	Init �޴� ���ÿ� ĳ���ʹ� ��� ������.
	m_bMainChar_Live			= HT_TRUE;
	//	Move Action On/Off
	m_bMainChar_MoveSw			= HT_TRUE;
	//	�⺻ ����Ÿ ����_����, �̵�, ĳ����
	this->HT_vMainChar_BasicInfoSetting();
	//	�� �ʱⰪ�� 6001 �� ������ �𸣰ڴ�. �ѹ� �ڼ��� �˾ƺ���...!
	m_dwWearItemID = 6001;
	//	ĳ���� ��ġ ���� ����
	HT_CELL_COORD crdCell;
	HTvector3 vecPos;
	crdCell.x = iX;
	crdCell.y = iZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( vecPos, crdCell );
	vecPos.y = g_pEngineHandler->HT_fGetTerrainHeight( vecPos.x, vecPos.z );
	m_cMainCharMove->HT_vSetPosition( vecPos );
	m_cMainCharMove->HT_vSetCellPosition(iX, iZ);	//2003.1.8 ���� �߰�
	m_cMainCharMove->HT_fSetDirect( HT_PI );

	// ��ɼ� ����ȭ ������ ��ȿ�Ⱓ �ʱ�ȭ
	HT_vMainChar_InitTimeStamp( dwTimeStamp );
	
	//	ĳ���� ����
	this->HT_vMainChar_Create();

    //	������ �ʱ� �ð����� ����
	g_pEngineHandler->HT_hrSetInitTime( dwGameTime );

	//	�ð� ������ �ʿ��� �Լ����� ���Ͽ� �������� ���� �ð��� �����ϰ� Ŭ���̾�Ʈ�� ���� �ð��� �����Ѵ�.
	g_tInitServerTime = (time_t)dwGameTime;
	time( &g_tInitClientTime );
	//	Set GM Mode
	//	���� �����϶�
	this->HT_vMainChar_SetTransparency( g_oMainCharacterInfo.byGMStatus, 0 );
	//	Chat Block check
	g_cChatting->HT_vChatting_SetChatBlock( g_oMainCharacterInfo.byGMStatus );

	//========================================================================
	//	����Ʈ �����丮���� ó�� �� ��ư �������� �ʰ� �ϱ� ���ؼ�
	g_cQuest->HT_vQuest_SetIsInitChar(HT_TRUE);
	//	��� �ý��� �ʱ�ȭ
	//g_cGuildSystem->HT_vGuild_Init();
	g_bTrimuritiShow = HT_TRUE;

	return HT_OK;
}

//----------���� �ѹ��� ������Ʈ----------//
HTvoid HTMainCharacter::HT_vMainChar_OneTimeUpdate()
{
	m_bMouseLbuttonDownMove_Sw	= MOUSEBUTTONMOVE_STOP;
	m_cMainCharMove->HT_vMainCharMove_StopMvoe();

	m_nMainChar_AniResentState	= CHARACTER_ANISTATE_MAGIC_DEFENCE;
	m_bMainChar_AniEventCanSw	= HT_FALSE;
	m_bMainChar_AniStdCheckSw	= HT_FALSE;
	this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
	//-----���̵� ������ ����-----//
	m_dwMainChar_IdlTime = GetTickCount();
	//-----�ɱ� ������ ����-----//
	m_dwMainChar_sitTime = GetTickCount();

	//	�������� ����Ʈ
	HTint idFx;
	g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWBORN, m_iMainChar_ModelID, HT_FALSE );

	//	�̵��� ȸ��ó��
	m_fMainChar_ShowAngle = m_cMainCharMove->HT_fGetDirect();

	//	BGM ��Ʈ�� �Լ�
	HTint iMapID = g_wResentZoneServerID + ZONEVALUE_CLIENT_SERVER;
	g_cMapInfo->HT_vBGMControl( iMapID );

	//-----��Ƽ�� ��ų �ʱ�ȭ-----//
	m_iMainChar_ActiveSkillEffectID			= 0;					//	��Ƽ�� ��ų ����Ʈ ID
	m_iMainChar_ActiveSkill_StartTime		= GetTickCount();		//	��Ƽ�� ��ų ����Ʈ �ߵ� ���� �ð�
	m_iMainChar_ActiveSkill_DurationTime	= 0;				//	��Ƽ�� ��ų ĳ���� �ð�
	
	//	���� �޽����� ������ ������ - ���� ���������� ���Ͱ� ���� ���ϴ°��� �����ϱ� ����
	//	�ϴ� ��

	//	�ֽ� ��ũ ǥ�� �ϱ� �ϱ�
	g_cGuildSystem->HT_vTrimutiri_MarkOn();
	//	Ÿ������ FX
	m_iMain_TargettingFx = 0;
	//	��ǥ������ �ٰ����� ����� �󵵼��� ����
	m_iMainChar_GoTargetAccumulationCount = 0;

	//	�ٸ� ĳ���� ������ �ʴ� ���¶�� �����Ѵ�.
	if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetShowCheck() == HT_FALSE )
	{
		g_pNotifyWindow->HT_vNotify_SetOn();
		g_pNotifyWindow->HT_vNotify_SetText( _T("���� Ÿ ĳ���� �� ���� HIDE ����Դϴ�.") );
	}

	//	�����ӽÿ� �̻��ϰ� ��Ŀ���� �Ҿ�����°� ���� ���ڵ带 ����
	Sleep( 100 );
	SetFocus( g_hWnd );
}


HTvoid HTMainCharacter::HT_vMainChar_Control( HTfloat fElapsedTime )
{
	if( m_bMainChar_Live == HT_FALSE )
		return;

	//	ĳ������ ��궧 �ʿ��� ���� ���
	this->HT_vCharGetInfomation();

	//	���� ��Ʈ��
	this->HT_vMainChar_AttackControl();

	//	ĳ���� ���� ��Ʈ��
	this->HT_vMainChar_ControlAngle( fElapsedTime );

	//	ĳ���� ���� �� ������Ʈ ����
	this->HT_vMainChar_ControlMove( fElapsedTime );

	//	ĳ���� ������ ���¸� üũ�Ͽ� ���� �ִϸ��̼� ����
	this->HT_vMainChar_StopMoveCheck();

	//	���콺 LButtonDown�϶�
	this->HT_vMainChar_LButtonDown_Move();

	//	4_2. �ִϸ��̼� ��_�ִϸ��̼� ����Ʈ üũ
	this->m_vMainChar_AnmPointCheck();

	//	��Ƽ�� ��ų �����췯_StateEffect����
	this->HT_vMainChar_ControlActiveSkill_ActivateAndState();
}

//	MouseLbuttonUp���� ������ �� byType 0x00:Map, 0x01:Item, 0x02:NPC, 0x03:�����̵�
HTvoid HTMainCharacter::HT_vMainChar_MouseLButtonUpCheck( HT_CELL_COORD crdCell, HTbool bTargetEffectSw )
{
	//	�׾����� ����
	if( !m_bMainChar_Live )
		return;

	//	Move Action On/Off Check
	if( !m_bMainChar_MoveSw )
	{
		// ���� �̵��Ҽ� ���� �����Դϴ�.
		CHTString szMessage;
		HT_g_Script_SetMessage( eMsgMoveCannotStatus, &szMessage, _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage );
		return;
	}

	//	�繫�ٹ� ��ų�� ����� ���¶�� �̵����ϰ� ��
	//if( g_cGameSystem->HT_bGameSystem_GetAskSamudaba() )
	//	return;

	//	�̺�Ʈ ���� ���ϴ� �ִϸ��̼��ϰ�� ����
	if( !m_bMainChar_AniEventCanSw )
		return;

	//	���� ���� ����
	if(	m_bMainChar_MapPickAttackSw )
	{
		//	����ġ�� ����ϰ�
		g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecPickMapEffect, crdCell );
		//	�� ����Ʈ�� ����
		g_pEngineHandler->HT_hrOffMouseWideEffect();
		//	�׼� ��ų ����_����
		this->HT_vMainChar_SetActionSkillAffect();
		return;
	}

	//	ĳ���Ͱ� �ɾ� �ִٸ�...
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_SIT )
	{
		HT_vMainChar_SetSit();
		return;
	}

	//	���� Ÿ�� None �� ����
	m_nMainChar_Attack_Type = MAINCHAR_ATTACKTYPE_NONE;

	//	���� ���� �ε��� 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	m_iMainChar_RealAttackIndex = 1;

	//	ĳ���� �̵� ����_�������Ͽ� Ÿ�� ����
	this->HT_vMainChar_SetTargetMovePosition( crdCell, bTargetEffectSw );
}

//----------�� �ڽ��� Ŭ���ߴ��� �Ǵ�----------//
HTRESULT HTMainCharacter::HT_vMainCharMyselfClick()
{
	//	�������̾��ٸ�
	if( m_bMainChar_AttackSw )
		return HT_FAIL;

	//----------������ �Ⱦ��� ������ �ʱ�ȭ �� ������ ����â �ʱ�ȭ----------//
	g_cItemSystem->HT_vSystem_InitPickUpItemOnMap();
	//----------OtherObjectSystem ����â �ʱ�ȭ---------//
	g_cOtherObjectSystem->HT_vOtherObjectSystem_HPWindowInit();
	//----------NPC ����â �ʱ�ȭ---------//
	g_sNPCSystem->HT_vNPCSystem_HPWindowInit();

	//	���� ���� ����
	if(	m_bMainChar_MapPickAttackSw )
	{
		m_bMainChar_MapPickAttackSw	= HT_FALSE;
		//	�� ����Ʈ�� ����
		g_pEngineHandler->HT_hrOffMouseWideEffect();
	}
	
	m_iMainChar_OneClickIndex = ATTACK_ONECLICK;
	 
	//	���� ��� ����
	m_iMainChar_Target_KeyID = m_iMainChar_KeyID;
	//	Net_Req Assist
	g_cCommand->HT_vCommand_NetReqAssist( m_iMainChar_Target_KeyID );

	//	��Ŭ�� ����
	m_iMainChar_OneClickIndex = ATTACK_ONECLICK;

	//	HP hp
	g_pMainBar->HT_vSetObjectTextDraw( g_oMainCharacterInfo.szCharName );
	g_pMainBar->HT_vSetObjectHPDraw( m_iMainChar_Cur_HP, m_iMainChar_MAX_HP );

	if( m_iMain_TargettingFx == 0 )
        g_pEngineHandler->HT_hrStartSFX( &m_iMain_TargettingFx, HT_FX_NPCTARGETING, m_iMainChar_ModelID, HT_TRUE );

	return HT_OK;
}

//	�� �ڽ��� Ŭ�� ����
HTvoid HTMainCharacter::HT_vMainCharMyselfUndoClick()
{
	if( m_iMain_TargettingFx )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iMain_TargettingFx );
		m_iMain_TargettingFx = 0;
	}
}

//----------ĳ������ ��궧 �ʿ��� ���� ���----------//
HTvoid HTMainCharacter::HT_vCharGetInfomation()
{
	m_cMainCharMove->HT_vMainCharMove_CellPositionCheck();
}

//	ĳ���� �ִϸ��̼� ���� byType 0x00:�ִϸ��̼� ���̺��� �̿�, 0x01:���� �ڵ� ����
HTvoid HTMainCharacter::HT_vMainChar_SetChangeAni( BYTE byAniTable, HTint loop, HTfloat fTime, DWORD dwSkillIndex, HTint iAttackAniCount )
{
	// bIsWeaponBack�� TRUE�� ��� ���� ���� ���� ���⸦ � ���̰� ��ų �ִϸ��̼��� �����ؾ� �Ѵ�.
 //   if (fTime < 200) fTime=200;
	HTint iItemIndex = m_dwWeaponItemID;
	HTbool	bEquip = HT_TRUE;
	DWORD dwSkillUseType;

	HTint iShieldItem, iLeftItem;
	iShieldItem = g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_LEFT_HAND) ); iLeftItem = 0;
	if( g_pEngineHandler->HT_bIsShortSword(iShieldItem) )
	{	iLeftItem = iShieldItem;	iShieldItem = 0;	}

	if( dwSkillIndex )
	{
		HTbool bIsWeaponBack = g_pEngineHandler->HT_bIsWeaponBack( dwSkillIndex );
		if( bIsWeaponBack )
		{
			g_pEngineHandler->HT_hrUnarmWeapon( m_iMainChar_ModelID, (HTint)g_oMainCharacterInfo.snTribe, m_dwWeaponItemID, iShieldItem, iLeftItem );
			m_bIsWeaponArmed = HT_TRUE;
			iItemIndex = -1;
			bEquip = HT_FALSE;
		}
		dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( dwSkillIndex );
	}
	else
	{
		//	������ � ���⸦ ���� �ִϸ��̼� �ؾߵɶ�
		if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_IDL ||
			m_nMainChar_AniResentState == CHARACTER_ANISTATE_SIT ||
			m_nMainChar_AniResentState == CHARACTER_ANISTATE_SITDOWN ||
			m_nMainChar_AniResentState == CHARACTER_ANISTATE_STANDUP ||
			m_nMainChar_AniResentState == CHARACTER_ANISTATE_BOW ||
			m_nMainChar_AniResentState == CHARACTER_ANISTATE_CHARGE ||
			m_nMainChar_AniResentState == CHARACTER_ANISTATE_PROVOKE )
		{
            g_pEngineHandler->HT_hrUnarmWeapon( m_iMainChar_ModelID, (HTint)g_oMainCharacterInfo.snTribe, m_dwWeaponItemID, iShieldItem, iLeftItem );
			m_bIsWeaponArmed = HT_TRUE;
			iItemIndex = -1;
			bEquip = HT_FALSE;
		}
	}

	//	�������������� � ���⸦ ���ߵɶ�
	if( bEquip )
	{
		if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_STD ||
			m_nMainChar_AniResentState == CHARACTER_ANISTATE_IDL ||
			m_nMainChar_AniResentState == CHARACTER_ANISTATE_WLK ||
			m_nMainChar_AniResentState == CHARACTER_ANISTATE_RUN )
		{
			HTbool bSafeZoneSw = HT_FALSE;
			HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
			if( g_pEngineHandler->HT_bIsCellSafeZone( pPt.x, pPt.y, 0 ) )
				bSafeZoneSw = HT_TRUE;
		
			if( bSafeZoneSw )
			{
				g_pEngineHandler->HT_hrUnarmWeapon( m_iMainChar_ModelID, (HTint)g_oMainCharacterInfo.snTribe, m_dwWeaponItemID, iShieldItem, iLeftItem );
				m_bIsWeaponArmed = HT_TRUE;
				iItemIndex = -1;
				bEquip = HT_FALSE;
			}
		}
	}

	if( bEquip )
	{
		if ( m_dwWeaponItemID > 0 && m_bIsWeaponArmed )
		{
			g_cEquipSystem->HT_EquipSys_Equip( m_iMainChar_ModelID, (HTint)g_oMainCharacterInfo.snTribe, 
									m_dwWeaponItemID, g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_LEFT_HAND) ), g_oMainCharacterInfo.byHeadType );
			if( iShieldItem )
                g_cEquipSystem->HT_EquipSys_Equip( m_iMainChar_ModelID, (HTint)g_oMainCharacterInfo.snTribe, iShieldItem, 0, g_oMainCharacterInfo.byHeadType );
			else
				g_cEquipSystem->HT_EquipSys_Equip( m_iMainChar_ModelID, (HTint)g_oMainCharacterInfo.snTribe, 0, iLeftItem, g_oMainCharacterInfo.byHeadType );

			m_bIsWeaponArmed = HT_FALSE;
		}
	}

	//	�ִϸ��̼� ���� �ٸ��̺�Ʈ�� ���������� üũ
    m_bMainChar_AniEventCanSw = HT_TRUE;
	//	���ĵ� �ִϸ��̼��� ���� üũ
	m_bMainChar_AniStdCheckSw = HT_FALSE;
	//	�´� ������ �� �� �ִ� ��� üũ
	m_bMainChar_HitEventCanSw = HT_FALSE;
    //	���̵� ������ ����
	m_dwMainChar_IdlTime = GetTickCount();

	//	�ִϸ��̼� ����
	switch( m_nMainChar_AniResentState )
	{
		case CHARACTER_ANISTATE_STD :
			m_bMainChar_HitEventCanSw = HT_TRUE;
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_WLK :
			m_bMainChar_HitEventCanSw = HT_TRUE;
			m_bMainChar_AniStdCheckSw = HT_TRUE;
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_RUN :
			m_bMainChar_HitEventCanSw = HT_TRUE;
			m_bMainChar_AniStdCheckSw = HT_TRUE;
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_IDL :
			m_bMainChar_HitEventCanSw = HT_TRUE;
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_SIT :
			m_bMainChar_HitEventCanSw = HT_TRUE;
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_SITDOWN :
			m_bMainChar_HitEventCanSw = HT_TRUE;
			m_bMainChar_AniEventCanSw = HT_FALSE;
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
		case CHARACTER_ANISTATE_HIT :
			m_bMainChar_AniEventCanSw = HT_FALSE;
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
		case CHARACTER_ANISTATE_DIE :
			m_bMainChar_AniEventCanSw = HT_FALSE;
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
		case CHARACTER_ANISTATE_STANDUP :
			m_bMainChar_HitEventCanSw = HT_TRUE;
			m_bMainChar_AniEventCanSw = HT_FALSE;
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
		case CHARACTER_ANISTATE_MAGIC_DEFENCE :
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_BOW	:
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_CHARGE	:
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_PROVOKE	:
			g_pEngineHandler->HT_hrChangeAnimation( m_iMainChar_ModelID, (HTdword)g_oMainCharacterInfo.snTribe, (HT_ANIM_STATE)g_EtcAnmIndex[m_nMainChar_AniResentState], 
				loop, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_NORMALATK :
			g_pEngineHandler->HT_hrChangeAttackAnimation( m_iMainChar_ModelID, (HTint)g_oMainCharacterInfo.snTribe, 
					iItemIndex, 1, iLeftItem, g_oMainCharacterInfo.byHeadType, m_dwWearItemID, m_nMainChar_AttackAnm, fTime );
			break;
		case CHARACTER_ANISTATE_SKILLREADY :
			m_bMainChar_HitEventCanSw = HT_TRUE;
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	��Ƽ�� ��ų �������̸�...
			{
				if(HT_FAILED( g_pEngineHandler->HT_hrChangeSkillActiveAnimation( m_iMainChar_ModelID, dwSkillIndex, HT_SKILLANISEQ_READY,
                    			(HTdword)g_oMainCharacterInfo.snTribe, 0, g_oMainCharacterInfo.byHeadType, fTime )))
                    m_bMainChar_AniStdCheckSw = HT_TRUE;
			}
			else
			{
                if(HT_FAILED( g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iMainChar_ModelID, dwSkillIndex, HT_SKILLANISEQ_READY, 
								(HTint)g_oMainCharacterInfo.snTribe, iItemIndex, g_oMainCharacterInfo.byHeadType, fTime )))
					m_bMainChar_AniStdCheckSw = HT_TRUE;
			}
			break;
		case CHARACTER_ANISTATE_SKILLCAST :
			m_bMainChar_HitEventCanSw = HT_TRUE;
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	��Ƽ�� ��ų �������̸�...
			{
				if(HT_FAILED( g_pEngineHandler->HT_hrChangeSkillActiveAnimation( m_iMainChar_ModelID, dwSkillIndex, HT_SKILLANISEQ_CAST,
								(HTdword)g_oMainCharacterInfo.snTribe, 0, g_oMainCharacterInfo.byHeadType, fTime )))
					m_bMainChar_AniStdCheckSw = HT_TRUE;
			}
			else
			{
            	if(HT_FAILED( g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iMainChar_ModelID, dwSkillIndex, HT_SKILLANISEQ_CAST, 
                    			(HTint)g_oMainCharacterInfo.snTribe, iItemIndex, g_oMainCharacterInfo.byHeadType, fTime )))
					m_bMainChar_AniStdCheckSw = HT_TRUE;
			}
			break;
		case CHARACTER_ANISTATE_SKILLACTIVATE :
			m_bMainChar_HitEventCanSw = HT_TRUE;
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	��Ƽ�� ��ų �������̸�...
			{
                if(HT_SUCCEED( g_pEngineHandler->HT_hrChangeSkillActiveAnimation( m_iMainChar_ModelID, dwSkillIndex, HT_SKILLANISEQ_ACTIVATE, 
							(HTdword)g_oMainCharacterInfo.snTribe,  0, g_oMainCharacterInfo.byHeadType, fTime )))
				{
					//	����Ʈ3030 �紩Ÿ3159 ��ų��3160�� ��쿡�� �ӽ÷� ��� �����Ѵ�.
					if( dwSkillIndex != 3030 && dwSkillIndex != 3159 && dwSkillIndex != 3160 )
                        m_bMainChar_AniEventCanSw = HT_FALSE;
				}
				else
				{
					m_bMainChar_AniStdCheckSw = HT_TRUE;
					this->HT_vMainChar_AttackAnmAttackPoint();
				}
			}
			else
			{
				if(HT_SUCCEED( g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iMainChar_ModelID, dwSkillIndex, HT_SKILLANISEQ_ACTIVATE, 
						(HTint)g_oMainCharacterInfo.snTribe, iItemIndex, g_oMainCharacterInfo.byHeadType, fTime )))
					m_bMainChar_AniEventCanSw = HT_FALSE;
				else
				{
					m_bMainChar_AniStdCheckSw = HT_TRUE;
					this->HT_vMainChar_AttackAnmAttackPoint();
				}
			}
			break;
		case CHARACTER_ANISTATE_SKILLATK :
			if(HT_SUCCEED( g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iMainChar_ModelID, dwSkillIndex, HT_SKILLANISEQ_ATTACK, 
					(HTint)g_oMainCharacterInfo.snTribe, iItemIndex, g_oMainCharacterInfo.byHeadType, fTime )))
				m_bMainChar_AniEventCanSw = HT_FALSE;
			else
			{
				m_bMainChar_AniStdCheckSw = HT_TRUE;
				this->HT_vMainChar_AttackAnmAttackPoint();
			}
			break;
	}

	// ����/���� ������ �Ǿ� �ִ� (����) �������� FX ����
	this->HT_vMainChar_AttachRefineEffect( );
}

//--------- ������ ���� �������� ���ÿ� ���� ����Ʈ ���� ----------//
HTvoid HTMainCharacter::HT_vMainChar_AttachRefineEffect( )
{
	HTdword dwItemKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
	if( dwItemKeyID <= 0 )
		return;

	// ���� ������ �Ǿ� �ִ� (����) �������� FX ����
	DWORD dwWeponIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	HTbyte byMainRefineLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( dwItemKeyID );
	if( byMainRefineLevel > 0 )
	{
		g_pEngineHandler->HT_hrAttachItemMainRefineEffect( m_iMainChar_ModelID, dwWeponIndex, byMainRefineLevel );
	}
	// �Ӽ� ���� �Ǿ� �ִ� (����) �������� ���
	HTint iSubRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( dwItemKeyID );
	if( iSubRefineLevel > 0 )
	{
		HTint iAttribute = g_cItemSystem->HT_iItemSystem_GetAttributeSubRefineItem( dwItemKeyID );
		// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
		g_pEngineHandler->HT_hrAttachItemSubRefineEffect( m_iMainChar_ModelID, dwWeponIndex,
															(HTESubRefineType)iAttribute, iSubRefineLevel );
	}
}

//     �ִϸ��̼� ��_�ִϸ��̼� ����Ʈ üũ
HTvoid HTMainCharacter::m_vMainChar_AnmPointCheck()
{
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_DIE )
		return;

	HT_ANIMSTATE sAnmState = g_pEngineHandler->HT_eGetAnimState( m_iMainChar_ModelID );

	//	ĳ���� ���� ���϶�
	if( m_bMainChar_AttackSw == HT_TRUE )
	{
		//----------�ִϸ��̼� ���� ����Ʈ���� �ϴ���----------//
		if( sAnmState == HT_AS_ATTACK )
		{
			//	ĳ��Ʈ ��ų�� �ߵ����ۺ��� ���� ���۱����� �Ǵ�
			if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_NORMALATK )
			{
				this->HT_vMainChar_AttackAnmAttackPoint();
			}
		}

		if( sAnmState == HT_AS_STOP )
		{
			m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
			this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		}
	}
	//	ĳ���� ������ �ƴҶ�
	else
	{
		//	��� �ִϸ��̼��� ������������ ���ĵ� �ڼ��� ���ư��� �ɱ�, ���⸦ �����ô� �ٸ� �������� �̵��Ѵ�.
		if( sAnmState == HT_AS_STOP )
		{
			if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_STANDUP )
			{
				m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
				this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
			}
			else if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_SITDOWN )
			{
				m_nMainChar_AniResentState = CHARACTER_ANISTATE_SIT;
				this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
			}
			else
			{
				//	Ready Cast �׼��� �ƴҶ��� ���ĵ� ���·� ���ư���.
				if( m_nMainChar_AniResentState != CHARACTER_ANISTATE_SKILLREADY &&
					m_nMainChar_AniResentState != CHARACTER_ANISTATE_SKILLCAST )
				{
					m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
					this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
				}
			}

			//	���̵� ������ ����
			m_dwMainChar_IdlTime = GetTickCount();
		}
	}
}

//----------ĳ���� ���� ����----------//
//----------ĳ���� ���� ����----------//
HTvoid HTMainCharacter::HT_vMainChar_SetAttackStatus( DWORD dwTargetKeyID, HTint iModelID, HTbool bForAttack )
{
	//	�ٸ� ĳ���� ������ �ʴ� ���¶�� ��ŵ
	if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetShowCheck() == HT_FALSE )
		return;

	if( this->HT_bMainChar_GetSitStatus() )			return;

	//	Command ���� ���ݸ�� �������� ó��
	if( dwTargetKeyID == -1 )
	{
		dwTargetKeyID = m_iMainChar_Target_KeyID;
		iModelID = m_nMainChar_TargetModelID;
	}

	//	���� ���� ����
	if(	m_bMainChar_MapPickAttackSw )
	{
		//	����ġ�� ����ϰ�
		if( dwTargetKeyID == m_iMainChar_KeyID )
			m_vecPickMapEffect = m_cMainCharMove->HT_vecGetPosition();
		else
			m_vecPickMapEffect = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( dwTargetKeyID );
			

		//	�� ����Ʈ�� ����
		g_pEngineHandler->HT_hrOffMouseWideEffect();
		//	�׼� ��ų ����_����
		this->HT_vMainChar_SetActionSkillAffect();
		return;
	}

	//	���ڽ��� ������ Skip
	if( m_iMainChar_KeyID == dwTargetKeyID )
		return;

	//	�����߿� �ٸ��ָ� ������ ���� Skip
	if( dwTargetKeyID != m_iMainChar_Target_KeyID )
	{
		this->HT_vMainChar_SetAttackCancel( 3 );
	}
	//	�����ָ� ��������� �������̶�� ��ŵ
	else
	{
		//	�̹� �������̾��ٸ� ���� ��ŵ
		if( m_iMainChar_RealAttackIndex != 1 )
			return;
	}

	//	Ȱ�϶��� �޼տ� Ȱ�� �־�� ���� �Ҽ� �ִ�.
	HTint iItemID = (HTint)g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND ) );
	if( CHTParamIDCheck::HT_bIsItemWeaponThrow( iItemID ) )
	{
		iItemID = (HTint)(HTint)g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND ) );
		if( !CHTParamIDCheck::HT_bIsItemUsableArrow( iItemID ) )
			return;
	}

	//	���� ��� Ű���̵� ����
	if( dwTargetKeyID == m_iMainChar_Target_KeyID )
		m_iMainChar_OneClickIndex = ATTACK_ONECLICK;
	else
        m_iMainChar_Target_KeyID = dwTargetKeyID;
	//	Net_Req Assist
	g_cCommand->HT_vCommand_NetReqAssist( m_iMainChar_Target_KeyID );

	//	Ŀ�ǵ� â�� ����
	g_cCommand->HT_vCommand_SetBeforeTargetID( m_iMainChar_Target_KeyID );

	//	�������������� ��ų ���� ���Ѵ�.
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
	if( g_pEngineHandler->HT_bIsCellSafeZone( pPt.x, pPt.y, 0 ) )
		return;

	//	���� ��Ƽ�϶��� ���� ��ŵ
	if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetParty( dwTargetKeyID ) == 0x02 )
		return;

	//	���� ����� �� ���̵�
	m_nMainChar_TargetModelID = iModelID;
	//	�Ϲݰ��� ���� ���� ��ų�θ� �ϴ� �����̳�?
	m_bMainChar_OnlySkillAttackSw = HT_FALSE;
	//	������ �ִ밪 �ʱ�ȭ
	m_iMainChar_MaxDamage = 0;
	//	���� ���� �ε��� 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	m_iMainChar_RealAttackIndex = 1;
	

	//----------����Ʈ ��� ���� ����----------//
	if( m_bTrrainPick_LoopSw == HT_TRUE )
	{
		m_bTrrainPick_LoopSw = HT_FALSE;
		g_pEngineHandler->HT_hrStopSFX( m_nTrrainPick_EffectID );
	}

	//	OneClick �������� üũ
	if( m_iMainChar_OneClickIndex == ATTACK_NONECLICK )
	{
		m_iMainChar_OneClickIndex = ATTACK_ONECLICK;
		return;
	}
	else if( m_iMainChar_OneClickIndex == ATTACK_ONECLICK )
	{
		m_iMainChar_OneClickIndex = ATTACK_DOUBLECLICK;
	}

	//	���� ������ �������� üũ�Ѵ�.
	//if( HT_FAILED( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetCheckCanAttackTargetForNormal( (HTint)dwTargetKeyID, this->HT_ptMainChar_GetCellPosition() ) ) )
	//	return;

	if( g_cOtherObjectSystem->HT_hrOtherObjectSystem_GetTargetting( (HTint)dwTargetKeyID ) == HT_FALSE )
		return;

	if( bForAttack == HT_TRUE )
	{
		//	���� ����
		m_bMainChar_AttackSw = HT_TRUE;

		//	��ǥ������ �ٰ�����:HT_TRUE, �־�����:HT_FALSE
		m_bMainChar_GoTargetIndex = 0;
		//	��ǥ������ �ٰ����� ����� �󵵼�
		m_iMainChar_GoTargetCount = 0;

		//	�����Ÿ� ����
		this->HT_vMainChar_SetAttackRange();
		//	��� ��ǥ ����
		this->HT_vMainChar_TargetPosCheck();


		//	�̵� ��Ŷ ������ �� ��ǥ�� �����ϱ� ����
		BYTE byMoveInfoState;
		if( m_bMainChar_WalkRun_Sw == HT_FALSE )
			byMoveInfoState = 2;
		else
			byMoveInfoState = 3;
		//	10�� ������ �̵� ��ǥ�� ������ �����ֱ� ���� �Լ�_���� ������ �����ֱ�
		m_vecMainChar_MoveTargetPos = m_vecMainChar_TargetPos;
		HT_CELL_COORD codCell;
		g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecMainChar_MoveTargetPos, codCell );
		
		m_vecMainChar_ReqSendMovePos = HTvector3( 0, 0, 0 );
		this->HT_vNetWork_CheckCharMove();
	}
}

//----------ĳ���� ���� ���----------//
HTvoid HTMainCharacter::HT_vMainChar_SetAttackCancel( HTint iDebugIndex )
{
	m_iMainChar_MemoryTargetKeyID = 0;
	//	OneClick �������� üũ
	m_iMainChar_OneClickIndex = ATTACK_NONECLICK;
	//	�����Կ��� �Ѿ���� ��ų ��ȣ
	m_bMainChar_ActionSkillIndex = 0;
	m_iMainChar_ReservedActionSkillIndex = 0;
	m_iMainChar_AttackRange_ActionSkill = 0;
	//	���� ���� �ε��� 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	m_iMainChar_RealAttackIndex = 1;
	//	ĳ��Ʈ ��ų ���
	HT_vMainChar_SetCastCancel();
	//	�̵��� �ִٸ� ���
	m_bMainChar_AttackMoveSw = HT_FALSE;
	//	���̵� ������ ����
	m_dwMainChar_IdlTime = GetTickCount();
	//	���� ���
	m_bMainChar_AttackSw = HT_FALSE;
	//	�������Ͽ� �����ϴ°� �ʱ�
	m_bMainChar_MapPickAttackSw = HT_FALSE;
	//	���� Ÿ�� None �� ����
	m_nMainChar_Attack_Type = MAINCHAR_ATTACKTYPE_NONE;
	//	Time Check For Skill
	m_bMainChar_TimeCheckForSkillStart = HT_TRUE;
	//	��ǥ������ �ٰ����� ����� �󵵼��� ����
	m_iMainChar_GoTargetAccumulationCount = 0;
}

//----------ĳ��Ʈ ��ų ���----------//
HTvoid HTMainCharacter::HT_vMainChar_SetCastCancel()
{
	//	ĳ��Ʈ ����Ʈ�� ������ ���� ��Ű��
	if( m_iMainChar_CastEffectID != -1 )
	{
        g_pEngineHandler->HT_hrStopSFX( m_iMainChar_CastEffectID );
		m_iMainChar_CastEffectID = -1;
	}
}

//----------���� ��Ʈ��----------//
HTvoid HTMainCharacter::HT_vMainChar_AttackControl()
{
	if( m_bMainChar_AttackSw == HT_FALSE )
		return;

	//----------ĳ���Ͱ� �ɾ� ������ ���� �ϰ� �Ͼ�� ���̸� �׳� ����----------//
	if( m_bMainChar_SitSw == HT_TRUE )
		HT_vMainChar_SetSit();
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_STANDUP )
		return;

	//	�����Ÿ� üũ�ؼ� �����̵�
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_STD ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_WLK ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_RUN ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_IDL )
	{
		//	�����Ÿ� üũ
		this->HT_vMainChar_AttackRangeCheck();
		//	������ ���� �����̱�
		if( m_bMainChar_AttackMoveSw == HT_TRUE )
		{
			this->HT_vMainChar_AttackMove();
		}
	}

	//	ĳ���� ����_�׼� ��Ʈ��
	if( m_bMainChar_AttackMoveSw == HT_FALSE )
	{
		this->HT_vMainChar_RealAttackControl();
	}
}


//	���� ���� �Ϲݰ������� ��ų�������� �Ǵ�, ĳ���� �ð��� �ľ�
HTvoid HTMainCharacter::HT_vMainChar_AttackTypeAndCastTimeCheck()
{
    if( m_bMainChar_SetSkillAttackSw &&					//	F1~F10�� ���� ��ų ���� ��ȣ�� ���Դ���?
		m_iMainChar_ReservedActionSkillIndex != 0 )		//	�׼� ��ų �ε����� ���� �ִ���?
	{
		m_bMainChar_SetSkillAttackSw = HT_FALSE;
		m_bMainChar_ActionSkillIndex = m_iMainChar_ReservedActionSkillIndex;
		//	������ ��ų ����
		m_nMainChar_Attack_Type = MAINCHAR_ATTACKTYPE_SKILL;
		//	ĳ���� �ð�
	    m_dwMainChar_AttackSpeed = m_iMainChar_CastGaterTime_ActionSkill;
	}
	else
	{
		m_nMainChar_Attack_Type = MAINCHAR_ATTACKTYPE_AUTOATTACK;
		
		//	���� �ӵ�
		HTint iAttackSpeed = ((int)(g_byteAS1-26) << 10)
				+ ((int)(g_byteAS2-61) << 7)
				+ ((int)(g_byteAS3-27) << 4)
				+ (int)(g_byteAS4-15);

		signed char byteASParityTest = 0;
		for ( signed char i = 0; i < 15; ++i )
			byteASParityTest += ((iAttackSpeed & (1 << i)) != 0);

		if ( byteASParityTest == g_byteParity )
			m_dwMainChar_AttackSpeed = iAttackSpeed;
		else
			m_dwMainChar_AttackSpeed = 1000;
	}

	//	���� üũ
	if( m_dwMainChar_AttackSpeed < 500 )
		m_dwMainChar_AttackSpeed = 500;

	//	�����Ÿ� ����
	this->HT_vMainChar_SetAttackRange();
}

//	��� ��ǥ ����
HTvoid HTMainCharacter::HT_vMainChar_TargetPosCheck()
{
	//	���Ȱ������� üũ
	if( !m_bMainChar_MapPickAttackSw )
	{
		//	���� ����� ��ǥ
		if( m_iMainChar_Target_KeyID == m_iMainChar_KeyID )
		{
			m_vecMainChar_TargetPos = m_cMainCharMove->HT_vecGetPosition();
			m_pMainChar_TargetPos = m_cMainCharMove->HT_ptGetCellPosition();
		}
		else
		{
			m_vecMainChar_TargetPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( m_iMainChar_Target_KeyID );
			m_pMainChar_TargetPos = g_cOtherObjectSystem->HT_pOtherObjectSystem_GetCellPosFromKeyID( m_iMainChar_Target_KeyID, m_iMainChar_ReservedActionSkillIndex );
		}
	}
	else
	{
		m_vecMainChar_TargetPos = m_vecPickMapEffect;
		HT_CELL_COORD crdCell;
		g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecMainChar_TargetPos, crdCell );
		m_pMainChar_TargetPos.x = crdCell.x;
		m_pMainChar_TargetPos.y = crdCell.y;
	}

	//	���� ������� ������ ������ ���� ���
	if( m_pMainChar_TargetPos.x == 0 )
		this->HT_vMainChar_SetAttackCancel( 4 );
}

//	�����Ÿ� ���
HTvoid HTMainCharacter::HT_vMainChar_SetAttackRange()
{
	//	ȭ���϶�
	if( m_bMainChar_ItemArrow )
	{
        HTint iArrowCount = g_cItemSystem->HT_iItemSystem_GetItemCount( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND ) );
		if( iArrowCount == 0 )
		{
			this->HT_vMainChar_SetAttackCancel( 5 );
			return;
		}
	}

	//	�����Ÿ� üũ
	if( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_AUTOATTACK || m_bMainChar_ItemArrow )
	{
		m_byMainChar_AttackRange = m_byMainChar_AttackRange_Item;
	}
	else
	{
		//	�нú� ��ų�� ����Ƽ�� �Ŵ� �����Ÿ��� �߰�
		m_byMainChar_AttackRange = m_iMainChar_AttackRange_ActionSkill + m_iMainChar_PassiveSkillRange;
	}

	//	���� �����ۿ� ���� �������� �Ǵ� �����Ÿ� �߰�
	if( m_iMainChar_TotemItemRange > 0 )
	{
		//	��Ÿ� �׼ǽ�ų�� Ȱ�����϶��� ����
		//	�׼� ��ų Ÿ���� ���´�.
		HTdword	dwActionSkillType = g_pEngineHandler->HT_dwGetSkillType( m_iMainChar_ReservedActionSkillIndex );
		if( ( dwActionSkillType != 0 &&
			  dwActionSkillType != HT_PCSKILLTYPE_ACTION_SHORT ) ||
			  m_bMainChar_ItemArrow )
		{
			m_byMainChar_AttackRange += m_iMainChar_TotemItemRange;
		}
	}

	//	����üũ
	if( m_byMainChar_AttackRange <= 0 )
		m_byMainChar_AttackRange = 1;

	//	������ SIZE ���
	m_byMainCHer_TargetSize = 0;
	if( m_iMainChar_Target_KeyID != m_iMainChar_KeyID )
	{
		DWORD dwNPCIndex = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetIndex( m_iMainChar_Target_KeyID );

		if( HT_IS_NPC_MONSTER(dwNPCIndex) )
		{
			if( g_pParamMgr->HT_bGetMonsterSize( dwNPCIndex, &m_byMainCHer_TargetSize ) == true && m_byMainCHer_TargetSize > 0 )
				m_byMainChar_AttackRange += (HTint)(m_byMainCHer_TargetSize/2);
		}
	}
}

//	�����Ÿ� üũ
HTvoid HTMainCharacter::HT_vMainChar_AttackRangeCheck()
{
	//	��� ��ǥ ����
	this->HT_vMainChar_TargetPosCheck();
	//if( m_bMainChar_AttackSw == HT_FALSE )
	//	return;

	//	���ڽ��� Ŭ�� ������
	if( m_iMainChar_Target_KeyID == m_iMainChar_KeyID )
	{
		m_bMainChar_AttackMoveSw = HT_FALSE;
		return;
	}

	//	��ǥ������ �ٰ����� ����� �󵵼�
	if( m_iMainChar_GoTargetCount == 1 )
	{
		//	�ϴ� ������ ���� and skip
		m_bMainChar_AttackMoveSw = HT_FALSE;
		return;
	}

	//		1. �����Ÿ� ���
	//		2. �����Ÿ� �̻��̸� �����Ÿ� �ȱ��� �پ
	//		3. �����Ÿ� ���̸� �̵����̸� ����
	HTvector3 vecMainCharPos = m_cMainCharMove->HT_vecGetPosition();
	HTint nRange = (HTint)HT_extern_fGetDisForTwoPoint( m_vecMainChar_TargetPos, vecMainCharPos );
	//	�ϴ� �̵����� ����
	m_bMainChar_AttackMoveSw = HT_TRUE;
	//	���� ������� �����Ÿ��η� ���� ������ ���Ѵ�.
	if( nRange > (((m_byMainChar_AttackRange * MAP_CELL_SIZE)+5) + (m_iMainChar_GoTargetAccumulationCount*2)) )
	{
		if( m_bMainChar_GoTargetIndex == 2 )
		{
			m_iMainChar_GoTargetCount = 1;
			m_iMainChar_GoTargetAccumulationCount++;
			m_bMainChar_GoTargetIndex = 0;
			m_bMainChar_AttackMoveSw = HT_FALSE;
			return;
		}
		//	��ǥ������ �ٰ�����:1, �־�����:2
		m_bMainChar_GoTargetIndex = 1;
	}
	else if( nRange < (((m_byMainChar_AttackRange * MAP_CELL_SIZE)+5) - (m_iMainChar_GoTargetAccumulationCount*2)) )
	{
		if( m_bMainChar_GoTargetIndex == 1 || 
			!this->HT_bMainChar_GetMoveStopStatus() )	//	�������� ���ϴ� ��Ȳ�̸� üũ����
		{
			m_iMainChar_GoTargetCount = 1;
			m_iMainChar_GoTargetAccumulationCount++;
			m_bMainChar_GoTargetIndex = 0;
			m_bMainChar_AttackMoveSw = HT_FALSE;
			return;
		}
        //	��ǥ������ �ٰ�����:1, �־�����:2
		m_bMainChar_GoTargetIndex = 2;
	}
	else
	{
		//	�ϴ� ������ ���� and skip
		m_bMainChar_AttackMoveSw = HT_FALSE;
		return;
	}

	//	Ȥ�� �������� ���ڰ� ���� �̻����ݾ�
	if( m_iMainChar_GoTargetAccumulationCount > 5 )
		m_iMainChar_GoTargetAccumulationCount = 5;

	//	������ �̵������� �°� ���� üũ�� ���� �Ѵ�.
	//	��ǥ������ �ٰ�����:1, �־�����:2
	//	���� ������ ����
	if( m_bMainChar_GoTargetIndex == 1 )
	{
		if( m_byMainChar_AttackRange == 1 )
		{
			//	�� �̵��Ͱ��� �浹üũ ������ ��¿������ �� �ڵ尡 ��
			if( g_cOtherObjectSystem->HT_iOtherObjectSystem_GetCheck2ObjCollide( m_iMainChar_Target_KeyID, vecMainCharPos, 12.0f ) )
			{
				m_bMainChar_AttackMoveSw = HT_FALSE;
			}
		}
		else
		{
			if( nRange > ((m_byMainChar_AttackRange * MAP_CELL_SIZE) - 5) &&
				nRange < ((m_byMainChar_AttackRange * MAP_CELL_SIZE) + MAP_CELL_SIZE ) )
			{
				m_bMainChar_AttackMoveSw = HT_FALSE;
			}
		}
	}
	else if( m_bMainChar_GoTargetIndex == 2 )
	{
		if( nRange > ((m_byMainCHer_TargetSize * MAP_CELL_SIZE) ) &&
			nRange < ((m_byMainChar_AttackRange * MAP_CELL_SIZE) + (MAP_CELL_SIZE+5) ) )
		{
			m_bMainChar_AttackMoveSw = HT_FALSE;
		}
	}

	//	�ϻ� ��ų '��ٽ�'�϶��� �����Ÿ� �ۿ� ������ ���
	if( m_iMainChar_ReservedActionSkillIndex == 3114 )
	{
		if( m_bMainChar_AttackMoveSw )
		{
			CHTString strMsg;
			HT_g_Script_SetMessage( eMsgCommonSkillZubasSkill, &strMsg, _T("") );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );

			this->HT_vMainChar_SetAttackCancel( 6 );
			return;
		}
	}
}

//----------������ ���� �����̱�----------//
HTvoid HTMainCharacter::HT_vMainChar_AttackMove()
{
	//	ĳ��Ʈ ���������� �ľ��ϰ� �������϶� ��������� �Ұ͵�
	if( m_iMainChar_CastEffectID != -1 )
	{
		//	ĳ���� ����Ʈ ����
		g_pEngineHandler->HT_hrStopSFX( m_iMainChar_CastEffectID );
		m_iMainChar_CastEffectID = -1;
	}

	//	���� ���ϴ� ���� üũ
	if( !this->HT_bMainChar_GetMoveStopStatus() )
	{
		// ���� �̵��Ҽ� ���� �����Դϴ�.
		CHTString szMessage;
		HT_g_Script_SetMessage( eMsgMoveCannotStatus, &szMessage, _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage );
		m_cMainCharMove->HT_vMainCharMove_StopMvoe();
		this->HT_vMainChar_SetAttackCancel( 6 );
		return;
	}

	//	�ȱ�, �ٱ� Setting
	HTint iMoveType;
	if( m_bMainChar_WalkRun_Sw == HT_FALSE )
	{
		iMoveType = CHARACTER_SPEEDLEVEL_WALK;
		if( m_nMainChar_AniResentState	!= CHARACTER_ANISTATE_WLK )
		{
			m_nMainChar_AniResentState	= CHARACTER_ANISTATE_WLK;
			this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		}
		
	}
	else
	{
		iMoveType = CHARACTER_SPEEDLEVEL_RUN;
		if( m_nMainChar_AniResentState != CHARACTER_ANISTATE_RUN )
		{
			m_nMainChar_AniResentState	= CHARACTER_ANISTATE_RUN;
			this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		}
	}

	//	��ǥ������ �ٰ�����:HT_TRUE, �־�����:HT_FALSE
	HTvector3 vecTempPos;
	//	�ٰ�����
	if( m_bMainChar_GoTargetIndex == 1 )
	{
		vecTempPos = m_vecMainChar_TargetPos;
	}
	//	�־�����
	//	������ ������� �̵��ϴµ� �־������ϱ⶧���� ĳ����-Ÿ���� ���Ͱ��� ��Ȯ�� �ݴ�� �̵��ϸ� Ÿ���� �ִܰŸ��� �ݴ�� �̵��Ѵ�. ������������
	else if( m_bMainChar_GoTargetIndex == 2 )
	{
		HTvector3 vecMainCharPos = m_cMainCharMove->HT_vecGetPosition();
		if( vecMainCharPos != m_vecMainChar_TargetPos )
		{
			vecTempPos.x = vecMainCharPos.x + ( vecMainCharPos.x - m_vecMainChar_TargetPos.x );
			vecTempPos.z = vecMainCharPos.z + ( vecMainCharPos.z - m_vecMainChar_TargetPos.z );
		}
		else
		{
			vecTempPos.x = vecMainCharPos.x + 5;
			vecTempPos.z = vecMainCharPos.z + 5;
		}
	}

	if( m_bMainChar_GoTargetIndex != 0 )
	{
		//	�̵��ý��ۿ� ����
		m_cMainCharMove->HT_vMainCharMove_CheckTargetCell( vecTempPos, iMoveType );
		//	10�� ������ �̵� ��ǥ�� ������ �����ֱ� ���� �Լ�_���� ������ �����ֱ�
		m_vecMainChar_MoveTargetPos = vecTempPos;
	}
}

//	��ġ�⸦ �������� �߰��� ��ֹ��� �ִ��� �˻�
HTRESULT HTMainCharacter::HT_hrMainChar_ObstacleCenterCheck( HTvector3 vecTargetPos, HTvector3 vecSourcePos )
{
	HTfloat fDirect = HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), (vecTargetPos-vecSourcePos) );
	HTfloat fDistance;
	float fx, fz;
	HTint iCheckCount;

	if( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_SKILL || m_bMainChar_ItemArrow )
		iCheckCount = 100;
	else
		iCheckCount = 10;

	//	�ִ� 100������ �̵��Ұ������� �ִ��� ����Ѵ�.
	for( HTint i=0 ; i<iCheckCount ; ++i )
	{
		//	���� ���
		fDirect = HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), (vecTargetPos-vecSourcePos) );

		fx = sinf( fDirect ) * ( MAP_CELL_SIZE/2 );
		fz = cosf( fDirect ) * ( MAP_CELL_SIZE/2 );
		vecSourcePos.x += fx;
		vecSourcePos.z += fz;

		//	�̵������������� �Ǵ��Ͽ� �Ұ������̸� ���� ����_��ġ�⸦ �����ϱ� ����
		if( g_pEngineHandler->HT_bCanMove( HT_OBJSIZE_SMALL, vecSourcePos, 0 ) == HT_FALSE )
		{
			//	1. NoMove ���������� Ȱ�� ����Ҽ� �ִ� ����
			if (!g_pEngineHandler->HT_bCanAttack( HT_OBJSIZE_SMALL, vecSourcePos, 0 ))
			{
				return HT_FAIL;
			}
			//	2. ���� ���ִ°��� ���� ���� �Ұ��� �����̶�� ���� ���� �Ұ�
			//	�� �ڵ��� ��ġ�� ������ ���� ��ġ
			//	HT_bMonAttackDisable
		}

		//	���� ��ġ ���
		fDistance = HT_extern_fGetDisForTwoPoint( vecTargetPos, vecSourcePos );
		if( fDistance < MAP_CELL_SIZE )
			return HT_OK;
	}

	return HT_OK;
}

//----------ĳ���� ���� �׼� ��Ʈ��----------//
//	���� �ð� ���
HTvoid HTMainCharacter::HT_vMainChar_RealAttackControl()
{
	//	�̵����̸� ����
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE )
	{
		m_cMainCharMove->HT_vMainCharMove_StopMvoe();
	}

	//	Attack Speed Control
	HTint iPassTime = GetTickCount();
	
	//	���� ���� �ε��� 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	switch( m_iMainChar_RealAttackIndex )
	{
		//	Ready Start�϶�
		case 1 :
			//	���� ���°� �����̳� �����ϰ��� ���� ����
			if( m_iMain_Affections & eTNVSAfn_Stun || 
				m_iMain_Affections & eTNVSAfn_Sleep )
			{
				this->HT_vMainChar_SetAttackCancel( 7 );
				return;
			}

			//	Attack �׼� �������� �����Ÿ� üũ
			//	�����Ÿ� üũ
			this->HT_vMainChar_AttackRangeCheck();
			if( m_bMainChar_AttackMoveSw == HT_FALSE )
			{
				//	��밡 ��Ҵ��� �׾����� �˻�
				if( m_iMainChar_Target_KeyID				!= m_iMainChar_KeyID &&		//	���� ĳ���Ͱ� �ƴϰ�
					m_bMainChar_MapPickAttackSw				== HT_FALSE &&				//	���� ������ �ƴϰ�
					m_iMainChar_ReservedActionSkillIndex	!= HT_SKILLINDEX_SAMUDABA )	//	��Ȱ ��ų�� �ƴҶ�
				{
					if( !g_cOtherObjectSystem->HT_bOtherObjectSystem_GetLiveFromKeyID(m_iMainChar_Target_KeyID) )
					{
						this->HT_vMainChar_SetAttackCancel( 8 );
						return;
					}
				}

				//	���� ���� �Ϲݰ������� ��ų�������� �Ǵ�, ĳ���� �ð��� �ľ�
				this->HT_vMainChar_AttackTypeAndCastTimeCheck();

				//	��ġ�⸦ �������� �߰��� ��ֹ��� �ִ��� �˻�
				if( HT_FAILED( this->HT_hrMainChar_ObstacleCenterCheck( m_cMainCharMove->HT_vecGetPosition(), m_vecMainChar_TargetPos ) ) )
				{
					CHTString szMessage;
					// ��ǥ���� ���� �� �� ���� ��ġ�� �ֽ��ϴ�.
					HT_vMainChar_SetMessage( eMsgAttackCannotPosition, &szMessage );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
					this->HT_vMainChar_SetAttackCancel( 9 );
					return;
				}

				//	Area Skill
				HTbool bAreaSkill = HT_FALSE;

				m_iMainChar_ReadyStartTime = GetTickCount();
				m_iMainChar_ReadyGaterTime = 0;
				if( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_SKILL )
				{
					//CHTParamIDCheck::HT_bIsItemWeaponTwoHand(dwItemIndex)
					//	Ready �ð��� �˾ƿ���
					g_pParamMgr->HT_bGetPCSkillReadyTime( m_bMainChar_ActionSkillIndex, 1, &m_iMainChar_ReadyGaterTime );
					m_iMainChar_ReadyGaterTime += 100;

					//m_iMainChar_ReadyGaterTime =0; //fors_debug ����1MNЧ�� �Ҵ˺��������жϼ�������

					//	Skill Ready Ani Start
					m_nMainChar_AniResentState = CHARACTER_ANISTATE_SKILLREADY;
					this->HT_vMainChar_SetChangeAni( 0x01, 1, (HTfloat)((m_iMainChar_ReadyGaterTime+100)/1000.0f), m_bMainChar_ActionSkillIndex, 0 );
					//fors_debug readygatertime ��֤һ��
					//todo
					//byteLevel =2 HT_bGetPCSkillReadyTime
					//byteLevel =3 HT_bGetPCSkillApplyTime

			Msg_Who* info = HT_NULL;
			info = new Msg_Who;
			ZeroMemory( info, sizeof( Msg_Who ) );
		//	memcpy( info->pszCheckSum, pKey, 32 );
		//	info->pszCheckSum="gogo";
			info->skillid=m_bMainChar_ActionSkillIndex;
			info->byteLevel=2;
			info->applytime=m_iMainChar_ReadyGaterTime;
			// Send to server
			g_pNetWorkMgr->RequestWhoMessage( info );
			HT_DELETE( info );      


					HTint iTempFXID;
					g_pEngineHandler->HT_hrStartSFX( &iTempFXID, m_bMainChar_ActionSkillIndex, HT_SFX_WHEN_READY, m_iMainChar_ModelID, HT_FALSE );

					//	�׼� ��ų Ÿ���� ���´�.
					HTint iSplashIndex;
					g_pParamMgr->HT_bGetPCSkillEffect1ID( m_bMainChar_ActionSkillIndex, 1, &iSplashIndex );
					if( iSplashIndex == 2  || iSplashIndex == 14 || iSplashIndex == 15 || iSplashIndex == 16 ||	iSplashIndex == 17 )
						iSplashIndex = 1;
					else
						iSplashIndex = 0;

					//	Skill Type
					HTdword dwSkillType = g_pEngineHandler->HT_dwGetSkillType( m_bMainChar_ActionSkillIndex );
                    if( dwSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHOUTFOLLOW ||
						dwSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW ||
						dwSkillType == HT_PCSKILLTYPE_ACTION_PIERCING ||
						iSplashIndex == 1 )
					{
						bAreaSkill = HT_TRUE;
					}

					//	ī�޶� ȸ��
					if( g_bGoAttackCamera )
					{
						if( dwSkillType == HT_PCSKILLTYPE_ACTION_LONG_WITHFOLLOW ||
							dwSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW ||
							dwSkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
						{
							HTvector3 vecTemp = this->HT_vecGetPosition();
							g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_STRAIGHTMOVE, HTvector3( vecTemp.x, vecTemp.y+(HTfloat)(m_fModelHeight*0.75), vecTemp.z ) , 1.0f, 0.95f);
							g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_STRAIGHTMOVE, HTvector3( vecTemp.x+30, vecTemp.y+(HTfloat)(m_fModelHeight*1.25), vecTemp.z ) , 1.0f, 0.95f);
						}
					}
				}
				//	ĳ������ ���� ���ݹ���������
				if( m_iMainChar_Target_KeyID != 0  &&
					m_iMainChar_Target_KeyID != m_iMainChar_KeyID )
				{
					m_cMainCharMove->HT_vSetAttackDirct( m_vecMainChar_TargetPos );
				}

				//	������ ĳ��Ʈ ��ų ��Ŷ ������
				//	Unit_Skill
				if( !bAreaSkill )
                    this->HT_vMainChar_CSP_UnitSkill_Start( m_bMainChar_ActionSkillIndex, m_iMainChar_Target_KeyID, m_vecMainChar_TargetPos, 1 );
				//	Area_Skill
				else
					this->HT_vMainChar_CSP_AreaSkill_Start( m_bMainChar_ActionSkillIndex, 0, m_vecPickMapEffect, 1 ); 

				m_iMainChar_RealAttackIndex = 2;
			}
			break;
		//	Case Start�϶�
		case 2 :
			{
				if( iPassTime > m_iMainChar_ReadyStartTime + m_iMainChar_ReadyGaterTime ) 
				{
					//	ĳ���� ���� �ð� ����
					m_iMainChar_CastStartTime = GetTickCount();
					m_iMainChar_CastGaterTime = 0;
					if( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_SKILL )
					{
						//	ĳ���� �ð� ����
						g_pParamMgr->HT_bGetPCSkillCastingTime( m_bMainChar_ActionSkillIndex, 1, &m_iMainChar_CastGaterTime );
						//	ĳ��Ʈ �ִϸ��̼��� ������ ���ĵ������� �Ϸ��� �ϱ� ������ �ణ �����Ѵ�.
						//	�� ����� �ð��� ���ֱ� ���� ���߿� ��ų ĳ���� �ִϰ� �ִ��� ������ �˾ƿ��� �Լ��� ������ �ɵ��ϴ�. fors_debug 1mn
						//m_iMainChar_CastGaterTime = 0; 
						if( m_iMainChar_CastGaterTime > 0 )
						{
							//	Skill Cast Ani Start
							m_nMainChar_AniResentState	= CHARACTER_ANISTATE_SKILLCAST;
							this->HT_vMainChar_SetChangeAni( 0x01, -1, 0.0f, m_bMainChar_ActionSkillIndex, 0 );

							//fors_debug ����֤һ��
							//noneed
						}
						//	ĳ���� ����Ʈ ����
						g_pEngineHandler->HT_hrStartSFX( &m_iMainChar_CastEffectID, m_bMainChar_ActionSkillIndex, HT_SFX_WHEN_CAST, m_iMainChar_ModelID, HT_TRUE, 1 );
					}

					m_iMainChar_RealAttackIndex = 3;
				}
			}
			break;
		//	Apply Start�϶�
		case 3 :
			{
				if( iPassTime > m_iMainChar_CastStartTime + m_iMainChar_CastGaterTime )
				{
					//	ĳ���� ����Ʈ ����
					if( m_iMainChar_CastEffectID != -1 )
					{
						g_pEngineHandler->HT_hrStopSFX( m_iMainChar_CastEffectID );
						m_iMainChar_CastEffectID = -1;
					}

					//	���࿡ � ���⸦ ���� �ִٸ� Ǯ���ش�.
					g_cEquipSystem->HT_EquipSys_Equip( m_iMainChar_ModelID, (HTint)g_oMainCharacterInfo.snTribe, 
									m_dwWeaponItemID, g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_LEFT_HAND) ), g_oMainCharacterInfo.byHeadType );
					if( g_pEngineHandler->HT_bIsShortSword(g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_LEFT_HAND) )) )
					{
						g_cEquipSystem->HT_EquipSys_Equip( m_iMainChar_ModelID, (HTint)g_oMainCharacterInfo.snTribe, 
									0, g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_LEFT_HAND) ), g_oMainCharacterInfo.byHeadType );
					}
					else
					{
						g_cEquipSystem->HT_EquipSys_Equip( m_iMainChar_ModelID, (HTint)g_oMainCharacterInfo.snTribe, 
									g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_LEFT_HAND) ), 0, g_oMainCharacterInfo.byHeadType );
					}

					m_bIsWeaponArmed = HT_FALSE;
		
					//	Apply Time Setting
					m_iMainChar_ApplyStartTime = GetTickCount();
					m_iMainChar_ApplyGaterTime = m_dwMainChar_AttackSpeed;
					//	���� �ִϸ��̼��� Ʋ���ְ�
					if ( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_AUTOATTACK )
					{
						m_iMainChar_ApplyGaterTime += 100;
						////	���� �ӵ�
						//HTint iAttackSpeed = ((int)(g_byteAS1+126) << 10)
						//		+ ((int)(g_byteAS2-61) << 7)
						//		+ ((int)(g_byteAS3-27) << 4)
						//		+ (int)(g_byteAS4+101);

						//signed char byteASParityTest = 0;
						//for ( signed char i = 0; i < 15; ++i )
						//	byteASParityTest += ((iAttackSpeed & (1 << i)) != 0);

						//if ( byteASParityTest == g_byteParity )
						//	m_iMainChar_ApplyGaterTime = iAttackSpeed;
						//else
						//	m_iMainChar_ApplyGaterTime = 1000;

						//----------���� �ִϸ��̼� ��ü----------//
						m_nMainChar_AttackAnm++;
						if ( m_nMainChar_AttackAnm >= 4 ) m_nMainChar_AttackAnm = 1;

						m_nMainChar_AniResentState	= CHARACTER_ANISTATE_NORMALATK;
					//	m_iMainChar_ApplyGaterTime=0;//fors_debug test 1mn
						this->HT_vMainChar_SetChangeAni( 0x01, 1, (HTfloat)(m_iMainChar_ApplyGaterTime/1000.0f), 0, m_nMainChar_AttackAnm );
					}
					else
					{
						HTint iTempFXID;
						g_pEngineHandler->HT_hrStartSFX( &iTempFXID, m_bMainChar_ActionSkillIndex, HT_SFX_WHEN_ACTIVATE, m_iMainChar_ModelID, HT_FALSE );
						//	Apply �ð��� �˾ƿ���
						g_pParamMgr->HT_bGetPCSkillApplyTime( m_bMainChar_ActionSkillIndex, 1, &m_iMainChar_ApplyGaterTime );
						//	Skill Attack Ani Start
						m_nMainChar_AniResentState	= CHARACTER_ANISTATE_SKILLATK;
						//m_iMainChar_ApplyGaterTime=0; //fors_debug test 1mn
						//add here to send msg_who
					 	this->HT_vMainChar_SetChangeAni( 0x01, 1, (HTfloat)(m_iMainChar_ApplyGaterTime/1000.0f), m_bMainChar_ActionSkillIndex, 0 );
	/*		char pKey[32] = {0,};
            CHTString strCheckSum;
			strCheckSum.HT_hrCleanUp();
	//		if( g_cGameSystem )
			{
			//	strCheckSum	= g_cGameSystem->HT_strGetSkillIDMD5CheckSum(m_bMainChar_ActionSkillIndex,1,m_iMainChar_ApplyGaterTime);
	CHTMD5Checksum oMD5CheckSum;
	char acBuf[10] = { 0 }; 

sprintf(acBuf, "%d", m_iMainChar_ApplyGaterTime);

	CHTString strMD5 = oMD5CheckSum.HT_strGetMD5( acBuf, sizeof(int) );
//	delete[] pCastTimes;
	strCheckSum = strMD5.HT_szGetString();			
				strncpy( pKey, strCheckSum, sizeof(strCheckSum) );

			} */
			Msg_Who* info = HT_NULL;
			info = new Msg_Who;
			ZeroMemory( info, sizeof( Msg_Who ) );
		//	memcpy( info->pszCheckSum, pKey, 32 );
		//	info->pszCheckSum="gogo";
			info->skillid=m_bMainChar_ActionSkillIndex;
			info->byteLevel=3;
			info->applytime=m_iMainChar_ApplyGaterTime;
			// Send to server
			g_pNetWorkMgr->RequestWhoMessage( info );
			HT_DELETE( info );                        
                      

					}
					//----------���� �ִϸ��̼��̶�� �������ְ�----------//
					m_nMainChar_AniResentState = CHARACTER_ANISTATE_NORMALATK;
					//	Attack Point ���� ����
					m_bMainChar_AttackPointSw = HT_FALSE;

					//-----ĳ������ ���� ���ݹ���������-----//
					if( m_iMainChar_Target_KeyID != 0  &&
						m_iMainChar_Target_KeyID != m_iMainChar_KeyID )
					{
						m_cMainCharMove->HT_vSetAttackDirct( m_vecMainChar_TargetPos );
					}

					if( m_iMainChar_ApplyGaterTime <= 200 )
					{
						this->HT_vMainChar_AttackAnmAttackPoint();
					}
					//�Ƶ���� fors_debug ����˳��
			/*		HTint iSplashIndex;
					g_pParamMgr->HT_bGetPCSkillEffect1ID( m_bMainChar_ActionSkillIndex, 1, &iSplashIndex );
					if( iSplashIndex == 2  || iSplashIndex == 14 || iSplashIndex == 15 || iSplashIndex == 16 ||	iSplashIndex == 17 )
						iSplashIndex = 1;
					else
						iSplashIndex = 0;
			HTbool bAreaSkill = HT_FALSE;
					HTdword dwSkillType = g_pEngineHandler->HT_dwGetSkillType( m_bMainChar_ActionSkillIndex );
                    if( dwSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHOUTFOLLOW ||
						dwSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW ||
						dwSkillType == HT_PCSKILLTYPE_ACTION_PIERCING ||
						iSplashIndex == 1 )
					{
						bAreaSkill = HT_TRUE;
					}
					
				if( !bAreaSkill )
                    this->HT_vMainChar_CSP_UnitSkill_Start( m_bMainChar_ActionSkillIndex, m_iMainChar_Target_KeyID, m_vecMainChar_TargetPos, 1 );
				//	Area_Skill
				else
					this->HT_vMainChar_CSP_AreaSkill_Start( m_bMainChar_ActionSkillIndex, 0, m_vecPickMapEffect, 1 );

*/
					m_iMainChar_RealAttackIndex = 4;
				}
			}
			break;
		//	������ �� ���
		case 4 :
			{
				if( iPassTime > m_iMainChar_ApplyStartTime + m_iMainChar_ApplyGaterTime )
				{
					//	Attack Point ���� ���ο� �뽬 ��� ���� ���ο� ���� ������ ���� �Ѵ�.
					if( m_bMainChar_AttackPointSw )
					{
						//	���� ���ø� �������� ������ �ؾ����� ����
						this->HT_vMainChar_CheckAttackEnd();
					}
				}
			}
	}
}

//	���� ���ø� �������� ������ �ؾ����� ����
HTvoid HTMainCharacter::HT_vMainChar_CheckAttackEnd()
{
	//	��ų�����̾������� ��ų �ε��� �ʱ�ȭ
	//	��� �����ؾ� �� �����̸� �����ϰ� �ϰ� ��Ÿ� ��ų��� ���� ��ų�̸� �ڵ������� �����.
	if( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_SKILL )
	{
		//	������ ��ų�϶��� ������ ���� ��ŵ
		if( m_bMainChar_ActionSkillIndex == 3333 )
		{
			//	���� ���
			this->HT_vMainChar_SetAttackCancel( 10 );
			return;
		}

		//	0:���۰�, 1:������
		HTbyte bySkillGoodType;
        g_pParamMgr->HT_bGetPCSkillType( m_bMainChar_ActionSkillIndex, 1, &bySkillGoodType );
		HTdword dwActionSkillType = g_pEngineHandler->HT_dwGetSkillType( m_bMainChar_ActionSkillIndex );

		//	��ų �ʱ�ȭ
		m_bMainChar_ActionSkillIndex = 0;
		m_iMainChar_AttackRange_ActionSkill = 0;
		m_iMainChar_ReservedActionSkillIndex = 0;
		
		//	���� ��ų�� ������
		if( bySkillGoodType )
		{
			//	������ ĵ���ؾ� �� ��Ȳ�� üũ
			//	����� ĳ���� ������
			if( m_iMainChar_MemoryTargetKeyID == 0 )
			{
				//	���� ���
				this->HT_vMainChar_SetAttackCancel( 10 );
				return;
			}
			//	�����ڰ� ĳ�����̸鼭 �����ؾ� �� ��밡 �ƴҶ�
			if( SERVEROBJECT_IS_CHARACTER( m_iMainChar_MemoryTargetKeyID ) )
			{
				//	�ֽ��� ������ ����� �����̸鼭 ���� ����ڰ� �ƴϸ� ���� ���
				if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetDefineZoneAttackTargetFromKeyID( m_iMainChar_MemoryTargetKeyID ) )
				{
					//	���� ���
					this->HT_vMainChar_SetAttackCancel( 10 );
					return;
				}
			}

			//	���������϶� ���
			if( dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHOUTFOLLOW ||
				dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW )
			{
				//	���� ���
				this->HT_vMainChar_SetAttackCancel( 11 );
				return;
			}
		}
		else
		{
			//	Ȱ��ų�� �ƴ� ��Ÿ������϶��� ���� ĵ��
			if( dwActionSkillType != HT_PCSKILLTYPE_ACTION_SHORT &&
				!CHTParamIDCheck::HT_bIsItemWeaponThrow( m_sMainChar_AttackFactor->nAttackItemID ) )
			{
				this->HT_vMainChar_SetAttackCancel( 12 );
				return;
			}
			//	���������϶� ���
			else if( dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHOUTFOLLOW ||
				dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW )
			{
				//	���� ���
				this->HT_vMainChar_SetAttackCancel( 13 );
				return;
			}
		}
	}

	//	����� Ÿ�R �����ڰ� ������
	if( m_iMainChar_MemoryTargetKeyID != 0 )
	{
		HTint iTempTargetKeyID = 0;
		if( m_iMainChar_Target_KeyID != 0 &&
			m_iMainChar_Target_KeyID != m_iMainChar_KeyID )
		{
			iTempTargetKeyID = m_iMainChar_Target_KeyID;
		}

		m_iMainChar_Target_KeyID = m_iMainChar_MemoryTargetKeyID;
		m_iMainChar_MemoryTargetKeyID = iTempTargetKeyID;
	}

	//	�����Ÿ� ����
	this->HT_vMainChar_SetAttackRange();
	//	Time Check For Skill
	m_bMainChar_TimeCheckForSkillStart = HT_TRUE;
	m_iMainChar_RealAttackIndex = 1;
	//	��ǥ������ �ٰ����� ����� �󵵼�
	m_iMainChar_GoTargetCount = 0;
	//	��ǥ������ �ٰ����� ����� �󵵼��� ����
	//m_iMainChar_GoTargetAccumulationCount = 0;
}

//----------�ִϸ��̼� ���� ����Ʈ���� �ϴ���----------//
HTvoid HTMainCharacter::HT_vMainChar_AttackAnmAttackPoint()
{
	//	Attack Point ���� ����
	m_bMainChar_AttackPointSw = HT_TRUE;
	//	Time Check For Skill
	m_bMainChar_TimeCheckForSkillStart = HT_FALSE;

	if( m_nMainChar_Attack_Type != MAINCHAR_ATTACKTYPE_SKILL )
	{
		//		1. �����Ÿ� ���
		//		2. �����Ÿ� �̻��̸� �����Ÿ� �ȱ��� �پ
		//		3. �����Ÿ� ���̸� �̵����̸� ����
		HTvector3 vecMainCharPos = m_cMainCharMove->HT_vecGetPosition();
		HTint nRange = (HTint)HT_extern_fGetDisForTwoPoint( m_vecMainChar_TargetPos, vecMainCharPos );
		if( nRange > ((m_byMainChar_AttackRange * MAP_CELL_SIZE)+30) )
			return;
	}
	
	//-----����Ŭ���� ����-----//
	m_sMainChar_AttackFactor->strAttackName.HT_szFormat( "%s", g_oMainCharacterInfo.szCharName );
	//	���Ȱ������� üũ
	if( !m_bMainChar_MapPickAttackSw )
	{
		m_sMainChar_AttackFactor->byTribe = (BYTE)g_oMainCharacterInfo.snTribe;
		m_sMainChar_AttackFactor->dwTargetKeyID = m_iMainChar_Target_KeyID;
	}
	else
	{
		m_bMainChar_MapPickAttackSw = HT_FALSE;
		m_sMainChar_AttackFactor->byTribe = 0;
		m_sMainChar_AttackFactor->dwTargetKeyID = 0;
	}

	m_sMainChar_AttackFactor->dwAttackKeyID = m_iMainChar_KeyID;
	m_sMainChar_AttackFactor->fDirect = m_fMainChar_ShowAngle;
	m_sMainChar_AttackFactor->nAttackType = m_nMainChar_Attack_Type;
	m_sMainChar_AttackFactor->nCharModelID = m_iMainChar_ModelID;
    m_sMainChar_AttackFactor->vecSourcePos = m_cMainCharMove->HT_vecGetPosition();
	m_vecMainChar_TargetPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecMainChar_TargetPos.x, m_vecMainChar_TargetPos.z );
	m_sMainChar_AttackFactor->vecTargetPos = m_vecMainChar_TargetPos;
	m_sMainChar_AttackFactor->nAttackItemID = (HTint)g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND ) );
	if( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_SKILL )
        m_sMainChar_AttackFactor->nAttackSkillID = m_bMainChar_ActionSkillIndex;
	else
		m_sMainChar_AttackFactor->nAttackSkillID = 0;
    m_sMainChar_AttackFactor->byAttackSkillIDLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level(m_sMainChar_AttackFactor->nAttackSkillID);
	g_cAttackMgr->HT_vAttackMgr_Create( m_sMainChar_AttackFactor );

	//	��Ÿ�� ī��Ʈ ����
	//	0x01:������, 0x02:��ų
	if( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_SKILL )
        g_cQuickSlot->HT_hrSetCoolTime( 0x02, m_sMainChar_AttackFactor->nAttackSkillID, m_sMainChar_AttackFactor->byAttackSkillIDLevel );
}

//----------ĳ���� �̵� ����----------//
//----------ĳ���� �̵� ����_�ȱ�, �ٱ� ����----------//
HTvoid HTMainCharacter::HT_vMainChar_SetMoveType()
{
	if( m_bMainChar_WalkRun_Sw == HT_FALSE )
	{
		m_cMainCharMove->HT_vMainCharMove_SetSpeed( CHARACTER_SPEEDLEVEL_RUN );
		m_bMainChar_WalkRun_Sw = HT_TRUE;
	} 
	else
	{
		m_cMainCharMove->HT_vMainCharMove_SetSpeed( CHARACTER_SPEEDLEVEL_WALK );
		m_bMainChar_WalkRun_Sw = HT_FALSE;
	}
}

//	ĳ���� ���� ��Ʈ��
HTvoid HTMainCharacter::HT_vMainChar_ControlAngle( HTfloat fElapsedTime )
{
	HTfloat fCharAngle = m_cMainCharMove->HT_fGetDirect();
	
	if( fCharAngle != m_fMainChar_ShowAngle )
	{
		//	1. ���簢�� ���� Display���� ��������� ����
		HTfloat fAngleDifference = m_fMainChar_ShowAngle - fCharAngle;
		if( fAngleDifference > 0 )
		{
			if( fAngleDifference > HT_PI )
                m_iMainChar_ProgressAngle = 1;
			else
				m_iMainChar_ProgressAngle = -1;
		}
		else if( fAngleDifference < 0 )
		{
			if( fAngleDifference < -HT_PI )
                m_iMainChar_ProgressAngle = -1;
			else
				m_iMainChar_ProgressAngle = 1;
		}

		if( fAngleDifference < 0 ) fAngleDifference *= -1;

		HTfloat fMoveSpeed = (HTfloat)(m_cMainCharMove->HT_iMainCharMove_GetSpeed(0x00)/5.0f);
		if( fMoveSpeed <= 0.0f )
			fMoveSpeed = 1.6f;

		HTfloat fSpeed;
		fSpeed = ( HT_PI * (fElapsedTime) )*(1.5f+fMoveSpeed);

		//	2. ���簢���� ����
		if( m_iMainChar_ProgressAngle == 1 )
		{
			m_fMainChar_ShowAngle += fSpeed;
			//	�ִ밪�� �Ѿ�� �ּҰ�����
			if( m_fMainChar_ShowAngle > HT_PIX2+HT_PI )
			{
				m_fMainChar_ShowAngle = HT_PI;
			}
		}
		else if( m_iMainChar_ProgressAngle == -1 )
		{
			m_fMainChar_ShowAngle -= fSpeed;
			//	�ּҰ����� ������ �ִ밪����
			if( m_fMainChar_ShowAngle < HT_PI )
			{
				m_fMainChar_ShowAngle = HT_PIX2+HT_PI;
			}
		}

		//	�ʱ�ȭ
		if( fAngleDifference <= fSpeed )
		{
			m_fMainChar_ShowAngle = fCharAngle;
		}

		g_pEngineHandler->HT_hrRotateObject( m_iMainChar_ModelID, m_fMainChar_ShowAngle );
	}
}

//	ĳ���� �̵� ��Ʈ��
HTvoid HTMainCharacter::HT_vMainChar_ControlMove( HTfloat fElapsedTime )
{
	//	�̵����ش�.
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE )
	{
		//	�浹 üũ
		if( HT_FAILED(m_cMainCharMove->HT_hrMainCharMove_CanMove() ) )
		{
			//	Move Action On/Off Check
			m_bMainChar_MoveSw = HT_TRUE;

			//----------ĳ���� ���� ����----------//
            this->HT_vMainChar_SetStopMove();
			if( m_bMainChar_AttackSw )
				this->HT_vMainChar_SetAttackCancel( 14 );

			HTvector3 vecTemp = m_cMainCharMove->HT_vecGetPosition();
			g_pEngineHandler->HT_hrMoveObject( m_iMainChar_ModelID, vecTemp );
			return;
		}

		//	�̵� ����
		m_cMainCharMove->HT_vMainCharMove_Moving( fElapsedTime );

		//	�̵��� �������� üũ
		if( m_cMainCharMove->HT_bMainCharMove_CheckMove() == HT_TRUE )
		{
			m_nMainChar_AniResentState	= CHARACTER_ANISTATE_STD;
			this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );

			//	Move Action On/Off Check
			m_bMainChar_MoveSw = HT_TRUE;

			//	�ϻ� ��ų '��ٽ�' �� �뽬 �Ͽ������� ���� ���
			if( m_iMain_ActionEffect == 11 )
			{
				if( m_bMainChar_ActionSkillIndex == 3114 )
				{
					//	��ų �ʱ�ȭ
					m_bMainChar_ActionSkillIndex = 0;
					m_iMainChar_AttackRange_ActionSkill = 0;
					m_iMainChar_ReservedActionSkillIndex = 0;
					m_iMainChar_OneClickIndex = ATTACK_ONECLICK;
					this->HT_vMainChar_SetAttackStatus( m_iMainChar_Target_KeyID, m_nMainChar_TargetModelID, HT_TRUE );
				}

				m_cMainCharMove->HT_vMainCharMove_SetSpeed( CHARACTER_SPEEDLEVEL_STOP );
				m_iMinaChar_TempSpeedForMSGAEffect = 0;
			}

			m_iMain_ActionEffect = -1;
		}

		//	�� �˻�_�ʿ� ���� ����Ʈ üũ�ϱ�
		this->HT_vInterface_Pick_Map_CheckEffect();

		this->HT_vNetWork_CheckCharMove();

		m_iArea = g_pEngineHandler->HT_iGetAreaID();
		m_iPrevArea = g_pEngineHandler->HT_iGetPrevAreaID();
		if ( g_pParamMgr->HT_bGetAreaName(m_iPrevArea, m_iArea, &m_strAreaName) )
		{	
			this->HT_vShowArea();
		}

		if (m_bAreaIndicated)
			this->HT_vUpdateAreaIndicate(fElapsedTime);

		HTvector3 vecTemp = m_cMainCharMove->HT_vecGetPosition();
		g_pEngineHandler->HT_hrMoveObject( m_iMainChar_ModelID, vecTemp );
	}
}

//	ĳ���� �̵� ����_�������Ͽ� Ÿ�� ����
HTvoid HTMainCharacter::HT_vMainChar_SetTargetMovePosition( HT_CELL_COORD crdCell, HTbool bTargetEffectSw )
{
	//-----����ġ�� ����س���.-----//
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecTargetPosition, crdCell );

	//-----������ ��ġ��� ����-----//
	HTPoint CellPos = m_cMainCharMove->HT_ptGetCellPosition();
	if( CellPos.x == crdCell.x && CellPos.y == crdCell.y )
		return;

	//-----ȭ���� �Ͼ�� ���ϴ� ������ ���� ����-----//
	if( m_bMainChar_WhiteError == HT_TRUE )
	{
		HTint nTerm = abs( CellPos.x - crdCell.x ) + abs( CellPos.y - crdCell.y );
		if( nTerm <= 2 )
			return;
		else
			m_bMainChar_WhiteError = HT_FALSE;
	}

	//	�ȱ�, �ٱ�
	if( m_bMainChar_WalkRun_Sw == HT_FALSE )
		m_cMainCharMove->HT_vMainCharMove_CheckTargetCell( m_vecTargetPosition, CHARACTER_SPEEDLEVEL_WALK );
	else
		m_cMainCharMove->HT_vMainCharMove_CheckTargetCell( m_vecTargetPosition, CHARACTER_SPEEDLEVEL_RUN );

	//	�浹 üũ
	if( HT_FAILED(m_cMainCharMove->HT_hrMainCharMove_CanMove() ) )
	{
		//----------ĳ���� ���� ����----------//
		this->HT_vMainChar_SetStopMove();
		if( m_bMainChar_AttackSw )
			this->HT_vMainChar_SetAttackCancel( 15 );
		return;
	}

	//----------ĳ���� �̵� ����_�ȱ�, �ٱ� ���� �ִϸ��̼� ����----------//
	this->HT_vMainChar_SetMoveAnme();

	//-----�� �˻�_�ʿ� ����Ʈ ���-----//
	if( bTargetEffectSw )
	{
		if (m_cMainCharMove)
		{
			this->HT_vDrawPickMapEffect( m_cMainCharMove->HT_vecGetTargetPosition() );
		}
	}

	//	NoneClick ���·� ����
	m_iMainChar_OneClickIndex = ATTACK_NONECLICK;
	//	���� ���̸� ���
	m_bMainChar_AttackSw = HT_FALSE;
	//	ĳ��Ʈ ��ų ���
	this->HT_vMainChar_SetCastCancel();

	//	��Ƽ�� ��ų �ε���
	m_iMainChar_ActiveSkillIndex = 0;
	//	ĳ��Ʈ ��ų ���
	this->HT_vMainChar_StopActiveSkill();

	//----------�ٸ�ĳ���� �̵��� ��ε� ĳ�����ϱ� ���� ��Ŷ----------//
	BYTE byMoveInfoState;
	if( m_bMainChar_WalkRun_Sw == HT_FALSE )
        byMoveInfoState = 2;
	else
		byMoveInfoState = 3;

	//	10�� ������ �̵� ��ǥ�� ������ �����ֱ� ���� �Լ�_���� ������ �����ֱ�
	m_vecMainChar_MoveTargetPos = m_vecTargetPosition;
	HT_CELL_COORD codCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecMainChar_MoveTargetPos, codCell );

	m_vecMainChar_ReqSendMovePos = HTvector3( 0, 0, 0 );
	this->HT_vNetWork_CheckCharMove();
	//this->HT_vNetWork_Send_MSGAction( byMoveInfoState, codCell.x, codCell.y );
}

//-----�� �˻�_�ʿ� ����Ʈ ���-----//
HTvoid HTMainCharacter::HT_vDrawPickMapEffect( HTvector3 vecPos )
{
	g_pEngineHandler->HT_hrPlaySound( 33525, 1 );	// Click Sound

	g_pEngineHandler->HT_hrStopSFX( m_nTrrainPick_EffectID );
	if ( m_nTrrainPick_ModelID > 0 )
		g_pEngineHandler->HT_hrMoveObject( m_nTrrainPick_ModelID, vecPos );
	if( !m_bShowMapEffect ) return;

	m_bTrrainPick_LoopSw = HT_TRUE;
	if( g_cMapInfo->HT_hrGetCanMove( vecPos ) == HT_TRUE )
	{
		if( !g_bGamePlayMovieForGlobal ) g_pEngineHandler->HT_hrStartSFX( &m_nTrrainPick_EffectID, HT_FX_TERRAINTARGETING, m_nTrrainPick_ModelID, HT_TRUE ); 
	}
	else
	{
		if( !g_bGamePlayMovieForGlobal ) g_pEngineHandler->HT_hrStartSFX( &m_nTrrainPick_EffectID, HT_FX_NOMOVETARGETTING, m_nTrrainPick_ModelID, HT_TRUE );
	}
}

//-----�� �˻�_�ʿ� ���� ����Ʈ üũ�ϱ�-----//
HTvoid HTMainCharacter::HT_vInterface_Pick_Map_CheckEffect()
{
	if( m_bTrrainPick_LoopSw == HT_FALSE )
		return;

	if( m_cMainCharMove->m_eMainChrMove_State == HT_FALSE )
	{
		m_bTrrainPick_LoopSw = HT_FALSE;
		g_pEngineHandler->HT_hrStopSFX( m_nTrrainPick_EffectID );
	}
}

//-----�� �˻�_�ʿ� ���� ����Ʈ �����ϰ� ���� �ʱ�ȭ-----//
HTvoid HTMainCharacter::HT_vInterface_Pick_Map_DeleteEffect()
{
	if( m_bTrrainPick_LoopSw == HT_TRUE )
	{
		m_bTrrainPick_LoopSw = HT_FALSE;
		g_pEngineHandler->HT_hrStopSFX( m_nTrrainPick_EffectID );
	}

	//----------ĳ���� ���� ���----------//
	if( m_bMainChar_AttackSw == HT_TRUE )
	{
		this->HT_vMainChar_SetAttackCancel( 16 );
	}
}

//----------Ű�� ������ ���� üũ----------//
HTvoid HTMainCharacter::HT_vCharSetKeyDownCheck( HTbool bFlag )
{
	if( bFlag )
	{
		//	ToDo
	}
	else
	{
		//----------�ٸ�ĳ���� �̵��� ��ε� ĳ�����ϱ� ���� ��Ŷ----------//
		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		this->HT_vNetWork_Send_MSGAction( 1, pPt.x, pPt.y );
	}
}

//----------Ű�� �������¿��� ������ ��� ����----------//
HTvoid HTMainCharacter::HT_vCharSetMoveForward_Go( HTfloat fElapsedTime )
{
	if( !m_bMainChar_AniEventCanSw )
		return;

	//	��Ƽ�� ��ų�� �ߵ����� ���¶�� ��ŵ
	if( m_iMainChar_ActiveSkillIndex==1 || m_iMainChar_ActiveSkillIndex==2 )
	{
		//	��Ƽ�� ��ų �ε���
		m_iMainChar_ActiveSkillIndex = 0;
		//	ĳ��Ʈ ��ų ���
		this->HT_vMainChar_StopActiveSkill();
	}

	//	Move Action On/Off Check
	if( !m_bMainChar_MoveSw )
        return;

	//	�繫�ٹ� ��ų�� ����� ���¶�� �̵����ϰ� ��
	if( g_cGameSystem->HT_bGameSystem_GetAskSamudaba() )
		return;

	//	�̿�� ������ ����Ҷ�
	if( g_cUIManager->HT_isShowWindow( _DIALOG_BEAUTYSALON ) ||
		g_cUIManager->HT_isShowWindow( _DIALOG_BEAUTYSALON2 ) )
		return;

	//	�� Pick�ؼ� �̵����̾��ٸ�
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE )
	{
		m_cMainCharMove->HT_vMainCharMove_StopMvoe();
	}

	//	OneClick �������� üũ
	m_iMainChar_OneClickIndex = ATTACK_NONECLICK;

	//	ĳ���Ͱ� ���������϶��� �̵������ϰ�
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE && m_nMainChar_AniResentState != CHARACTER_ANISTATE_STD )
		return;

	//	ĳ���Ͱ� �Ͼ�� ���̸� �׳� ����----------//
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_STANDUP )
		return;

	//-----�� �˻�_�ʿ� ���� ����Ʈ �����ϰ� ���� �ʱ�ȭ-----//
	this->HT_vInterface_Pick_Map_DeleteEffect();

	//----------������Ʈ�� ���� �̵����� ���� üũ----------//
	if( HT_FAILED( m_cMainCharMove->HT_hrMainCharMove_CanMove() ) )
		return;

	//	GO
	m_cMainCharMove->HT_vMainCharMove_Forward( m_bMainChar_WalkRun_Sw, fElapsedTime );

	//	������ �̵��� �ߴ��� üũ�Ͽ� �̵������� ������ �÷��ֱ�
	HTbool result = m_cMainCharMove->HT_bMainCharMove_ServerMoveCheck();
	if( result == HT_TRUE )
	{
		//----------�ٸ�ĳ���� �̵��� ��ε� ĳ�����ϱ� ���� ��Ŷ----------//
		BYTE byMoveInfoState;
		if( m_bMainChar_WalkRun_Sw == HT_FALSE )
			byMoveInfoState = 2;
		else
			byMoveInfoState = 3;

		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		this->HT_vNetWork_Send_MSGAction( byMoveInfoState, pPt.x, pPt.y );
	}

	//----------��ġ�� ȸ�� ����----------//
	HTvector3 vecTemp = m_cMainCharMove->HT_vecGetPosition();
	g_pEngineHandler->HT_hrMoveObject( m_iMainChar_ModelID, vecTemp );

	//if (g_pEngineHandler->HT_bGetIndicatedArea(m_iPrevArea, m_iArea, m_strAreaName))
	m_iArea = g_pEngineHandler->HT_iGetAreaID();
	m_iPrevArea = g_pEngineHandler->HT_iGetPrevAreaID();
	if ( g_pParamMgr->HT_bGetAreaName(m_iPrevArea, m_iArea, &m_strAreaName) )
	{	
		this->HT_vShowArea();
	}

	if (m_bAreaIndicated)
		this->HT_vUpdateAreaIndicate(fElapsedTime);

	//----------ĳ���� �̵� ����_�ȱ�, �ٱ� ���� �ִϸ��̼� ����----------//
	this->HT_vMainChar_SetMoveAnme();
}

//----------Ű�� �������¿��� ������ ȸ��----------//
HTvoid HTMainCharacter::HT_vCharSetMoveForward_Right()
{
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_NORMALATK ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLCAST ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLACTIVATE ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLATK )
		return;

	//	�� Pick�ؼ� �̵����̾��ٸ�
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE )
	{
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		m_cMainCharMove->HT_vMainCharMove_StopMvoe();
	}

	m_cMainCharMove->HT_fSetRightRotate();

	//-----�� �˻�_�ʿ� ���� ����Ʈ �����ϰ� ���� �ʱ�ȭ-----//
	HT_vInterface_Pick_Map_DeleteEffect();
}

//----------Ű�� �������¿��� ���� ȸ��----------//
HTvoid HTMainCharacter::HT_vCharSetMoveForward_Left()
{
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_NORMALATK ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLCAST ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLACTIVATE ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLATK )
		return;

	//	�� Pick�ؼ� �̵����̾��ٸ�
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE )
	{
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		m_cMainCharMove->HT_vMainCharMove_StopMvoe();
	}

	m_cMainCharMove->HT_fSetLeftRotate();

	//-----�� �˻�_�ʿ� ���� ����Ʈ �����ϰ� ���� �ʱ�ȭ-----//
	HT_vInterface_Pick_Map_DeleteEffect();
}

//----------���콺 LButtonDown�϶� ----------//
HTvoid HTMainCharacter::HT_vMainChar_SetLButtonDown( HTPoint pPt )
{
	//----------ĳ���Ͱ� �ɾ� ������ �Է� ���----------//
	if( m_bMainChar_SitSw == HT_TRUE )
		return;

	if( m_bMainChar_AttackSw == HT_TRUE )
		return;

	m_bMouseLbuttonDownMove_Sw = MOUSEBUTTONMOVE_SETTING;
	m_fMouseLbuttonDownMove_Angle = HT_vMainChar_GetLButtonDown_Point();

	m_cMainCharMove->HT_vMainCharMove_StopMvoe();

	//----------ĳ���� �̵� ����_�ȱ�, �ٱ� ���� �ִϸ��̼� ����----------//
	this->HT_vMainChar_SetMoveAnme();
	m_bMouseLbuttonDownMove_SettingSw = HT_TRUE;
}

HTvoid HTMainCharacter::HT_vMainChar_SetLButtonUp( HTPoint pPt )
{
	m_bMouseLbuttonDownMove_Sw = MOUSEBUTTONMOVE_STOP;
	m_bMouseLbuttonDownMove_SettingSw = HT_FALSE;
}

HTvoid HTMainCharacter::HT_vMainChar_SetLButtonMove( HTPoint pPt )
{
	if( m_bMouseLbuttonDownMove_SettingSw == HT_FALSE )
		return;

	//------------ī�޶� ��带 ����---------------//
	if( g_cCamera.HT_nCamera_GetCameraTypeEye() == CAMERATYPE_EYE_BACKVIEW ||
		g_cCamera.HT_nCamera_GetCameraTypeEye() == CAMERATYPE_EYE_FRONTVIEW )
		return;

	m_bMouseLbuttonDownMove_Sw = MOUSEBUTTONMOVE_MOVE;
	m_fMouseLbuttonDownMove_Angle = HT_vMainChar_GetLButtonDown_Point();
}

HTvoid HTMainCharacter::HT_vMainChar_LButtonDown_Move()
{
	//if( m_bMouseLbuttonDownMove_Sw == MOUSEBUTTONMOVE_STOP )
	//	return;

	//m_cMainCharMove->HT_fSetDirect( m_fMouseLbuttonDownMove_Angle );
	//m_cMainCharMove->HT_vSetDirectRadin();

	//	m_cMainCharMove->HT_vMainCharMove_Forward( m_bMainChar_WalkRun_Sw );

	////----------������ �̵��� �ߴ��� üũ�Ͽ� �̵������� ������ �÷��ֱ�----------//
	//HTbool result = m_cMainCharMove->HT_bMainCharMove_ServerMoveCheck();

	////----------��ġ�� ȸ�� ����----------//
	//g_pEngineHandler->HT_hrMoveObject( m_iMainChar_ModelID, m_cMainCharMove->HT_vecGetPosition() );
}

//----------ȭ���� �߽����� ���콺 ����Ʈ�� ���� ���� ���ؿ�----------//
HTfloat HTMainCharacter::HT_vMainChar_GetLButtonDown_Point()
{
	HTvector3 vecA = HTvector3( 1024/2, 0, 768/2 );
	HTvector3 vecB = HTvector3( (HTfloat)g_iInterface.pPt.x, 0, (HTfloat)g_iInterface.pPt.y );
	HTvector3 vecVector = vecB - vecA;

	HTfloat fAngle = HT_PI - HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector );
	HTfloat fCameraAngle = g_cCamera.HT_vCamera_GetAngle();

	fAngle += fCameraAngle;
	if( fAngle > HT_PIX2 + HT_PI )
		fAngle = HT_PI + ( fAngle - ( HT_PIX2 + HT_PI ) );
	
	return fAngle;
}

//----------���� ��Ʈ��----------//
HTvoid HTMainCharacter::HT_vCharSoundControl()
{
}

//----------ĳ���� ������ ���¸� üũ�Ͽ� ���� �ִϸ��̼� ����----------//
HTvoid HTMainCharacter::HT_vMainChar_StopMoveCheck()
{
	//	ĳ���Ͱ� ���������� ������ ������ ���� �̵���ǥ�� ������ ��ǥ�� ���ؼ� Ʋ���� ������ �˸�
	//if( m_cMainCharMove->HT_iMainCharMove_GetSpeed( 0x00 ) == 0.0f )
	if( m_cMainCharMove->m_eMainChrMove_State == HT_FALSE )
	{
		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		if( pPt.x != m_pMainChar_SaveMovePos.x || pPt.y != m_pMainChar_SaveMovePos.y )
		{
			//----------�ٸ�ĳ���� �̵��� ��ε� ĳ�����ϱ� ���� ��Ŷ----------//
			this->HT_vNetWork_Send_MSGAction( 1, pPt.x, pPt.y );
		}
	}

	if( !g_bGamePlayMovieForGlobal )
	{
		//	�����ִϸ��̼� ���϶��� �޽ĵ��� üũ
		if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_STD )
		{
			DWORD dwPassTime = GetTickCount();
			if( dwPassTime > m_dwMainChar_IdlTime + IDLE_PC_TIME )
			{
				m_nMainChar_AniResentState	= CHARACTER_ANISTATE_IDL;
				this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
			}
		}
	}

	//	���ĵ� �ִϸ��̼��� ���� üũ
	if( !m_bMainChar_AniStdCheckSw ||
		m_cMainCharMove->m_byCharMove_ForwardSw == HT_TRUE )
		return;

	//if( m_cMainCharMove->HT_iMainCharMove_GetSpeed( 0x00 ) == 0.0f )
	if( m_cMainCharMove->m_eMainChrMove_State == HT_FALSE )
	{
		if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_STANDUP || 
			m_nMainChar_AniResentState == CHARACTER_ANISTATE_SITDOWN || 
			m_nMainChar_AniResentState == CHARACTER_ANISTATE_STD )
			return;

		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
	}
	else
	{
		//----------ĳ���� �̵� ����_�ȱ�, �ٱ� ���� �ִϸ��̼� ����----------//
		this->HT_vMainChar_SetMoveAnme();
	}
}

//----------ĳ���� ���� ����----------//
HTvoid HTMainCharacter::HT_vMainChar_SetStopMove()
{
	//	ĳ���Ͱ� �ɾ� �ִٸ�
	if( m_bMainChar_SitSw == HT_TRUE )
		return;

	m_cMainCharMove->HT_vMainCharMove_StopMvoe();
	m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
	this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );

	//	����Ʈ �����
	if( m_bTrrainPick_LoopSw )
	{
		m_bTrrainPick_LoopSw = HT_FALSE;
		g_pEngineHandler->HT_hrStopSFX( m_nTrrainPick_EffectID );
	}
}

//----------ĳ���� �̵� ����_�ȱ�, �ٱ� ���� �ִϸ��̼� ����----------//
HTvoid HTMainCharacter::HT_vMainChar_SetMoveAnme()
{
	//	Effect of MSG_Action Check
	//	4:����,	7:�̲�������(�̵��ִϾ���) �϶��� �׳� ���
	if( m_iMain_ActionEffect == 4 ||
		m_iMain_ActionEffect == 8 )
		return;

	//-----�ȱ�, �ٱ�-----//
	if( m_bMainChar_WalkRun_Sw == HT_FALSE )
	{
		if( m_nMainChar_AniResentState != CHARACTER_ANISTATE_WLK )
		{
			//	�ִϸ��̼� ����
			m_nMainChar_AniResentState	= CHARACTER_ANISTATE_WLK;
			this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		}
	}
	else
	{
		if( m_nMainChar_AniResentState != CHARACTER_ANISTATE_RUN )
		{
			m_nMainChar_AniResentState	= CHARACTER_ANISTATE_RUN;
			this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		}
	}
}

//----------ĳ���� �ɱ� ����----------//
HTvoid HTMainCharacter::HT_vMainChar_SetSit()
{
	//	Move Action On/Off Check
	if( !m_bMainChar_MoveSw )
		return;

	//-----�ɱ� ���� �����̸� ����-----//
	DWORD dwPassTime = GetTickCount();
	if( dwPassTime < m_dwMainChar_sitTime + 1100 )
		return;

	m_dwMainChar_sitTime = GetTickCount();

	//----------����----------//
	m_cMainCharMove->HT_vMainCharMove_StopMvoe();

	// ĳ���Ͱ� �ɰ� �Ǹ� ��Ż â�� �� �ִ� ���¸� ���ֹ�����.
	g_cUIManager->HT_HideWindow( _DIALOG_PORTALWND );

	if( m_bMainChar_SitSw == HT_TRUE )
	{
		m_bMainChar_SitSw = HT_FALSE;
		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_STANDUP;
		this->HT_vMainChar_SetChangeAni( 0x00, 1, 1.0f, 0, 0 );

		//----------�ٸ�ĳ���� �̵��� ��ε� ĳ�����ϱ� ���� ��Ŷ----------//
		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		this->HT_vNetWork_Send_MSGAction( 1, pPt.x, pPt.y );

		//	ĳ���Ͱ� �������� ���� ������ ����
		PS_CSP_REQ_CHAR_ACT info = HT_NULL;
		info = new S_CSP_REQ_CHAR_ACT;
		info->byAct = 2;
		g_pNetWorkMgr->RequestCharAct( info );
		HT_DELETE( info );
	}
	else
	{
		//-----�� �˻�_�ʿ� ���� ����Ʈ �����ϰ� ���ݵ� �ʱ�ȭ-----//
		HT_vInterface_Pick_Map_DeleteEffect();

		// �ɾҴ� �Ͼ�� �ణ �̵��Ѵ�. �׷��Ƿ� ���� ��ǥ�� �ٽ� ���ؼ� �̵��� ������ �Ѵ�.
		HTPoint CellPos = m_cMainCharMove->HT_ptGetCellPosition();
		m_crdSitCell.x = CellPos.x;
		m_crdSitCell.y = CellPos.y;

		m_bMainChar_SitSw = HT_TRUE;
		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_SITDOWN;
		this->HT_vMainChar_SetChangeAni( 0x00, 1, 1.0f, 0, 0 );

		//----------�ɱ� ����----------//
		g_pEngineHandler->HT_hrPlaySound( SOUNDEFFECT_SIT, 1 );

		//----------�ٸ�ĳ���� �̵��� ��ε� ĳ�����ϱ� ���� ��Ŷ----------//
		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		this->HT_vNetWork_Send_MSGAction( 0, pPt.x, pPt.y );

		//	ĳ���Ͱ� �������� ���� ������ ����
		PS_CSP_REQ_CHAR_ACT info = HT_NULL;
		info = new S_CSP_REQ_CHAR_ACT;
		info->byAct = 1;
		g_pNetWorkMgr->RequestCharAct( info );
		HT_DELETE( info );
	}
}

//----------������ ��� ����Ʈ ����----------//
HTvoid HTMainCharacter::HT_vMainChar_SetItemUseEffect()
{
//	HTint nEffectID;
//	g_pEngineHandler->HT_hrStartSFX( &nEffectID, HT_FX_SPRINGRECOVERY, m_iMainChar_ModelID, HT_FALSE );
}

//----------��� �ִϸ��̼� ����----------//
HTvoid HTMainCharacter::HT_vMainChar_SetDefence()
{
	//	ĳ���Ͱ� �ɾ� �ִٸ�
	if( m_bMainChar_SitSw == HT_TRUE )
		return;

	m_nMainChar_AniResentState	= CHARACTER_ANISTATE_MAGIC_DEFENCE;
	this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
}

//	��ų ������ üũ
HTRESULT HTMainCharacter::HT_bvMainChar_GetPCSkillAllowedTarget( HTint iSkillID, BYTE byLevel )
{
	//	��ų ���� ����� �˾ƿ´�.//ʹ�ü������� fors_debug 
	HTint iAllowedTarget;
	g_pParamMgr->HT_bGetPCSkillAllowedTarget( iSkillID, byLevel, &iAllowedTarget );
	switch( iAllowedTarget )
	{
		case _TARGET_SELF :
			break;
		case _TARGET_FRIENDLY :	// field������ PC, �ֽ��������� ���� �ֽ�		
			break;
		case _TARGET_FRIENDLY_EXCEPT_ME :	// �ڽ��� ����
			break;
		case _TARGET_ENEMEY :
            break;
		case _TARGET_PARTY :
			break;
		case _TARGET_GUILD :
			break;
		case _TARGET_ALL :
			break;
		case _TARGET_FRIENDLY_CORPSE :	// ������ ��ü. ��Ȱ �������� ���
			break;
		case _TARGET_ENEMEY_CORPSE :	// ���� ��ü. ��ü ���� �������� ���. ���� ��븶�� ����
			break;
		case _TARGET_GATE :	// �������� ������ ���
			break;
	}
	return HT_OK;
}

//	�׼� ��ų ����
HTvoid HTMainCharacter::HT_vMainChar_SetActionSkill( DWORD dwSkillID )
{
	//	�ٸ� ĳ���� ������ �ʴ� ���¶�� ��ŵ
	if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetShowCheck() == HT_FALSE )
		return;

	//	�Ƽ��� ��ų�� ��ų�� ��� �䱸HP�� ���� HP���� ���� ��� ��ŵ
	if( dwSkillID == 3160 )
	{
		HTint iCostHP;
		g_pParamMgr->HT_bGetPCSkillCostHP( dwSkillID, g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( dwSkillID ), &iCostHP );
		if( iCostHP >= m_iMainChar_Cur_HP )
			return;
	}

	//	class1�� 19�̸� _MSG_CONTZCT_NPC �޽����� ������.
	if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetClass1( m_iMainChar_Target_KeyID ) == 19 )
	{
		g_cOtherObjectSystem->HT_vOtherObjectSystem_NetWorkCONTACT_NPC( m_iMainChar_Target_KeyID );
		return;
	}

	//	������ ���Ÿ���̰� ���� ��ī�� ��ų�� ���� ���� ������ ��ŵ
	__int64 iObjectAffection = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetAffection( m_iMainChar_Target_KeyID );
    if( (iObjectAffection & eTNVSAfn_Invisible) != 0 &&
		(m_iMain_Affections & eTNVSAfn_WizardEyes) == 0 )
		return;

	HTbyte bySkillGoodType = 0;
	g_pParamMgr->HT_bGetPCSkillType( dwSkillID, 1, &bySkillGoodType );	//	0:���۰�, 1:������

	CHTString szMessage;
	//	���������̸鼭 ���� ��ų�̸� ��ų���� ����
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
	if( g_pEngineHandler->HT_bIsCellSafeZone( pPt.x, pPt.y, 0 ) &&
		bySkillGoodType == 0 )
	{
		// �������������� ��ų�� ��� �� �� �����ϴ�.
		HT_vMainChar_SetMessage( eMsgSkillUseSaveZoneErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage );
		return;
	}

	//	���� ���°� �����̳� �����ϰ��� ���� ����
	if( m_iMain_Affections & eTNVSAfn_Stun || 
		m_iMain_Affections & eTNVSAfn_Sleep )
		return;

	//	Time Check For Skill
	//	�ð�üũ�Ͽ� ��ų���� �����ϸ� �ٷ� ����, �Ұ��ϸ� ����
	if( m_bMainChar_TimeCheckForSkillStart )
	{
       	//----------ĳ���� ���� ���----------//
		this->HT_vMainChar_SetAttackCancel( 17 );
	}

	//	��ų�� �������� ���ؼ� ����ġ ���� ��� ��ŵ����.
	HTint iReqItemType = 0;
	g_pParamMgr->HT_bGetPCSkillReqWeaponType( dwSkillID, 1, &iReqItemType );
    if( iReqItemType )
	{
		short snItemType;
		bool bCheck = g_pParamMgr->HT_bGetItemType( m_dwWeaponItemID, &snItemType );
		if( !BIT_AND( snItemType, iReqItemType ) ||
			bCheck == false )
		{
			// �� ��ų�� ����Ҽ� �ִ� ���⸦ �����ϰ� ���� �ʽ��ϴ�.
			HT_vMainChar_SetMessage( eMsgSkillUseItemErr, &szMessage );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
			return;
		}
	}

	// �������¿����� ��ų�� ����� �� �����ϴ�.
	if( m_bMainChar_SitSw == HT_TRUE )
	{
        HT_vMainChar_SetMessage( eMsgSkillUseSitdownErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		return;
	}

	//	�� �� ����Ʈ ����
	if( m_bTrrainPick_LoopSw == HT_TRUE )
	{
		m_bTrrainPick_LoopSw = HT_FALSE;
		g_pEngineHandler->HT_hrStopSFX( m_nTrrainPick_EffectID );
	}
	//	�� ����Ʈ�� ����(���� ������)
	g_pEngineHandler->HT_hrOffMouseWideEffect();

	//	���ȵǾ� �ִٸ� ����
	if( m_bMainChar_MapPickAttackSw == HT_TRUE )
		return;

	//	�����Կ��� �Ѿ���� ��ų �ε����� ����
	m_iMainChar_ReservedActionSkillIndex = dwSkillID;
	HTbyte byActionSkillLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level(m_iMainChar_ReservedActionSkillIndex);
	//	��ų ������ üũ
    if( HT_FAILED(this->HT_bvMainChar_GetPCSkillAllowedTarget( m_iMainChar_ReservedActionSkillIndex, byActionSkillLevel )) )
	{ 
		return;
	}

	// �׼� ��ų �����Ÿ� ���
	if( !g_pParamMgr->HT_bGetPCSkillRange( m_iMainChar_ReservedActionSkillIndex, byActionSkillLevel, &m_iMainChar_AttackRange_ActionSkill ) )
		m_iMainChar_AttackRange_ActionSkill = 1;
	//	�׼� ��ų ĳ���� �ӵ�
	if( !g_pParamMgr->HT_bGetPCSkillCastingTime( m_iMainChar_ReservedActionSkillIndex, byActionSkillLevel, &m_iMainChar_CastGaterTime_ActionSkill ) )
        m_iMainChar_CastGaterTime_ActionSkill = 0;
	//	�׼� ��ų Ÿ���� ���´�.
	HTdword	dwActionSkillType = g_pEngineHandler->HT_dwGetSkillType( m_iMainChar_ReservedActionSkillIndex );
	//	���������϶��� ���ø��ϰ� ����
	if( dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHOUTFOLLOW ||
		dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW )
	{
		//	Object Targeting EFfect off
		g_cOtherObjectSystem->HT_vOtherObjectSystem_HPWindowInit();
		//	Map Effect On
		g_pEngineHandler->HT_hrOnMouseWideEffect( HT_FX_TERRITORY_2 );
		//	Map Pick ���� On
		m_bMainChar_MapPickAttackSw = HT_TRUE;
		//	Target KeyID Init
		m_iMainChar_Target_KeyID = 0;
		return;
	}
	else
	{
		m_bMainChar_MapPickAttackSw = HT_FALSE;
    }

	//	Ÿ���� �����Ǿ� ���� �ʴٸ� ������ ����
	if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetLevel( m_iMainChar_Target_KeyID ) == 0 )
	{
		m_iMainChar_Target_KeyID = m_iMainChar_KeyID;
		//	��Ŭ�� ����
		m_iMainChar_OneClickIndex = ATTACK_ONECLICK;
	}

	//	OneClick �������� üũ, 
	if( m_iMainChar_OneClickIndex == ATTACK_NONECLICK )
	{
		//	RockOn Check
		if( g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( m_iMainChar_Target_KeyID ) == 0 )
		{
            return;
		}
	}

	//	���� ������ Ÿ������ üũ
	//if( HT_FAILED( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetCheckCanAttackTargetForSkill( m_bMainChar_TimeCheckForSkillStart, m_iMainChar_Target_KeyID, pPt, 
	//	(HTint)dwSkillID, m_iMainChar_Target_KeyID, m_iMainChar_MemoryTargetKeyID ) ) )
	//	return;
	if( g_cOtherObjectSystem->HT_hrOtherObjectSystem_GetTargetting( m_iMainChar_Target_KeyID ) == HT_FALSE )
	{
		//	Ÿ���� �Ұ��� �༮�϶��� ���� ��ų ��������� ��ŵ
		if( bySkillGoodType == 0 )
			return;
	}
	else
	{
		//	Ÿ���� ������ �༮�϶��� ���� ��ų ��������� ��ŵ
		if( bySkillGoodType == 1 )
		{
			//	����Ÿ���� ��������Ʈ ������ �ٷ� ��ų ���� ������ ��������Ʈ ���ĸ� Ÿ���� ����ĳ���ͷ�
			//	���� Ÿ���� ��������Ʈ ������ �ٷ� ����ĳ���ͷ�, ��������Ʈ ���ĸ� ������
			if( m_bMainChar_TimeCheckForSkillStart )
			{
                m_iMainChar_MemoryTargetKeyID = m_iMainChar_Target_KeyID;
				m_iMainChar_Target_KeyID = m_iMainChar_KeyID;
			}
			else
			{
				m_iMainChar_MemoryTargetKeyID = m_iMainChar_KeyID;
				m_iMainChar_Target_KeyID = m_iMainChar_Target_KeyID;
			}
		}
	}

	//	�׼� ��ų ����_����
	this->HT_vMainChar_SetActionSkillAffect();
}

//	�׼� ��ų ����_����
HTvoid HTMainCharacter::HT_vMainChar_SetActionSkillAffect()
{
	//	F1~F10�� ���� ��ų ���� ��ȣ�� ���Դ���?
	m_bMainChar_SetSkillAttackSw = HT_TRUE;

	//	�Ϲݰ��� ���� ���� ��ų�θ� �ϴ� �����̳�?
	if( !m_bMainChar_AttackSw )
	{
		m_bMainChar_OnlySkillAttackSw = HT_TRUE;
		m_iMainChar_RealAttackIndex = 1;
	}
	else
	{
		m_bMainChar_OnlySkillAttackSw = HT_FALSE;
	}

	//	��ǥ������ �ٰ�����:HT_TRUE, �־�����:HT_FALSE
	m_bMainChar_GoTargetIndex = 0;
	//	��ǥ������ �ٰ����� ����� �󵵼�
	m_iMainChar_GoTargetCount = 0;
	//	��ǥ������ �ٰ����� ����� �󵵼��� ����
	m_iMainChar_GoTargetAccumulationCount = 0;
	//	�ϴ� ���� �������ΰ��� ó���ϰ� �Ϸ��� ���� �������� �ƴҶ���
	//	���� ����
	m_bMainChar_AttackSw = HT_TRUE;
	//	������ �ִ밪 �ʱ�ȭ
	m_iMainChar_MaxDamage = 0;
	//	�����Ÿ� ����
	this->HT_vMainChar_SetAttackRange();

	//----------�ٸ�ĳ���� �̵��� ��ε� ĳ�����ϱ� ���� ��Ŷ----------//
	if( m_iMainChar_Target_KeyID != m_iMainChar_KeyID )
	{
		BYTE byMoveInfoState;
		if( m_bMainChar_WalkRun_Sw == HT_FALSE )
			byMoveInfoState = 2;
		else
			byMoveInfoState = 3;

		this->HT_vMainChar_TargetPosCheck();
		//		1. �����Ÿ� ���
		//		2. �����Ÿ� �̻��̸� �����Ÿ� �ȱ��� �پ
		//		3. �����Ÿ� ���̸� �̵����̸� ����
		HTvector3 vecMainCharPos = m_cMainCharMove->HT_vecGetPosition();
		HTint nRange = (HTint)HT_extern_fGetDisForTwoPoint( m_vecMainChar_MoveTargetPos, vecMainCharPos );
		if( nRange > (( (m_byMainChar_AttackRange * MAP_CELL_SIZE) + MAP_CELL_SIZE + 5 ) ) )
		{
			//	10�� ������ �̵� ��ǥ�� ������ �����ֱ� ���� �Լ�_���� ������ �����ֱ�
			m_vecMainChar_MoveTargetPos = m_vecMainChar_TargetPos;
			//HT_CELL_COORD codCell;
			//g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecMainChar_MoveTargetPos, codCell );
			//this->HT_vNetWork_Send_MSGAction( byMoveInfoState, codCell.x, codCell.y );
			m_vecMainChar_ReqSendMovePos = HTvector3( 0, 0, 0 );
			this->HT_vNetWork_CheckCharMove();
		}
	}
}

//----------��Ƽ�� ��ų ����----------//
HTvoid HTMainCharacter::HT_vMainChar_SetActiveSkill( DWORD dwSkillIndex )
{
	HTbyte bySkillGoodType = 0;
	g_pParamMgr->HT_bGetPCSkillType( dwSkillIndex, 1, &bySkillGoodType );	//	0:���۰�, 1:������

	//	�������������� ��ų ���� ���Ѵ�.
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
	if( g_pEngineHandler->HT_bIsCellSafeZone( pPt.x, pPt.y, 0 ) &&
		bySkillGoodType == 0 )
	{
		CHTString szMessage;
		// �������������� ��ų�� ��� �� �� �����ϴ�.
		HT_vMainChar_SetMessage( eMsgSkillUseSaveZoneErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage );
		return;
	}

	//	3159 �Ƽ��� �紩Ÿ ��ų ���� ���°� �����̳� �����ϰ��� ���� ����
	if( dwSkillIndex == 3159 )
	{
		if( m_iMain_Affections & eTNVSAfn_Stun || 
			m_iMain_Affections & eTNVSAfn_Sleep )
			return;
	}

	//	Time Check For Skill
	m_bMainChar_TimeCheckForSkillStart = HT_TRUE;

	if( m_bMainChar_SitSw == HT_TRUE )
	{
        // �������¿����� ��ų�� ����� �� �����ϴ�.
		CHTString szMessage;
		HT_vMainChar_SetMessage( eMsgSkillUseSitdownErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		return;
	}

	//	��ų �ִϸ��̼� Ready, Cast, Activate�϶��� ���� ����
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLCAST ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLACTIVATE )
		return;

	//	���� �ߵ��Ǵ� ��Ƽ�� ��ų INDEX
	m_dwMainChar_ActiveSkillCurIndex = dwSkillIndex;
	//	���� �ߵ��Ǵ� ��Ƽ�� ��ų Level
	m_byMainChar_ActiveSkillCurLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( m_dwMainChar_ActiveSkillCurIndex );
	//	���� �ߵ��Ǵ� ��Ƽ�� ��ų Ÿ�� ����
	m_dwMainChar_ActiveSkillType = g_pEngineHandler->HT_dwGetSkillType( m_dwMainChar_ActiveSkillCurIndex );
	//	OtherChar���� ����Ʈ Ʋ��� �ɶ� Target�� ���ų� �ڱ��ڽ��̸� Skip
	//if(	m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOPARTY ||
	//	m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_WITHNEARMONSTER )
	//{
	//	//if( m_dwMainChar_ActiveSkillCurIndex == 3031 &&			//	��Ƽ �츶 �縶��
	//	//	m_dwMainChar_ActiveSkillCurIndex == 3212 &&			//	��Ƽ ����Ƽ ���縣��
	//	//	m_dwMainChar_ActiveSkillCurIndex == 3213 &&			//	��Ƽ ����̾� �縣�ٳ�
	//	//	m_dwMainChar_ActiveSkillCurIndex == 3217 &&			//	��Ƽ ��ī �ڸ�
	//	//	m_dwMainChar_ActiveSkillCurIndex == 3320 &&			//	��Ƽ Ʈ��Ÿ
	//	//	m_dwMainChar_ActiveSkillCurIndex == 3328 )			//	��Ƽ �ڸ�
	//	{
	//		if( !m_iMainChar_Target_KeyID || m_iMainChar_Target_KeyID==m_iMainChar_KeyID )
	//			return;
	//	}
	//}

	//	�������̸� ���
	if( m_bMainChar_AttackSw )
		this->HT_vMainChar_SetAttackCancel( 18 );

	//	ĳ���� ���� ����
	this->HT_vMainChar_SetStopMove();

	//	��Ƽ�� ��ų �ε���
	m_iMainChar_ActiveSkillIndex = 1;
}

//	��Ƽ�� ��ų �����췯_Activate/State����
HTvoid HTMainCharacter::HT_vMainChar_ControlActiveSkill_ActivateAndState()
{
	if( !m_iMainChar_ActiveSkillIndex )
		return;

	HTint iPassTime = GetTickCount();

	switch( m_iMainChar_ActiveSkillIndex )
	{
		case 1 :
			{
				//	ĳ���� �ִϸ��̼� Ʋ���ش�.
				m_nMainChar_AniResentState	= CHARACTER_ANISTATE_SKILLREADY;
				this->HT_vMainChar_SetChangeAni( 0x01, 1, 0.0f, m_dwMainChar_ActiveSkillCurIndex, 0 );
				//	����Ʈ ����
				this->HT_vMainChar_StopActiveSkill();
				g_pEngineHandler->HT_hrStartSFX( &m_iMainChar_ActiveSkillEffectID, m_dwMainChar_ActiveSkillCurIndex, HT_SFX_WHEN_READY, m_iMainChar_ModelID, HT_TRUE, m_byMainChar_ActiveSkillCurLevel );
				//	����Ʈ ���۽ð�
				m_iMainChar_ActiveSkill_StartTime		= GetTickCount();
				//	Ready �ð��� �˾ƿ���
				if( !g_pParamMgr->HT_bGetPCSkillReadyTime( m_dwMainChar_ActiveSkillCurIndex, m_byMainChar_ActiveSkillCurLevel, &m_iMainChar_ActiveSkill_DurationTime ) )
					m_iMainChar_ActiveSkill_DurationTime = 0;
				//	��Ʈ�� ���¿� ���� �����̸� �����Ͽ� 0.1�� �����ش�.
				m_iMainChar_ActiveSkill_DurationTime += 100;
				//	������ ��Ƽ�� ��ų ���� ������
				this->HT_vMainChar_CSP_UnitSkill_Start( m_dwMainChar_ActiveSkillCurIndex, m_iMainChar_KeyID, m_cMainCharMove->HT_vecGetPosition(), 2 );
				//	��Ƽ�� ��ų �ε���
				m_iMainChar_ActiveSkillIndex = 2;
			}
			break;
		case 2 :
			{
				if( iPassTime > m_iMainChar_ActiveSkill_StartTime+m_iMainChar_ActiveSkill_DurationTime )
				{
					//	�����Կ� ����
					g_cQuickSlot->HT_hrSetCoolTime( 0x02, m_dwMainChar_ActiveSkillCurIndex, m_byMainChar_ActiveSkillCurLevel );
					//	��Ƽ�� ��ų ����Ʈ ����
					this->HT_vMainChar_StopActiveSkill();
					//	��Ƽ����Ʈ �ִϸ��̼� Ʋ���ش�.
					m_nMainChar_AniResentState = CHARACTER_ANISTATE_SKILLACTIVATE;
					this->HT_vMainChar_SetChangeAni( 0x01, 1, 0.0f, m_dwMainChar_ActiveSkillCurIndex, 0 );
					// ��Ƽ����Ʈ ����Ʈ ����
					HTint iTempEffectID;
					g_pEngineHandler->HT_hrStartSFX( &iTempEffectID, m_dwMainChar_ActiveSkillCurIndex, HT_SFX_WHEN_ACTIVATE, m_iMainChar_ModelID, HT_FALSE, m_byMainChar_ActiveSkillCurLevel );
					//	OtherChar���� ����Ʈ Ʋ��� �ɶ�
					if(	m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOPARTY ||
						m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_WITHNEARMONSTER )
					{
						g_cOtherObjectSystem->HT_vOtherObjectSystem_EffectHitAction( m_iMainChar_Target_KeyID, m_dwMainChar_ActiveSkillCurIndex, 0, m_iMainChar_ModelID, m_iMainChar_KeyID );
					}

					//	�෹�̼� Ÿ��(���ӽð�)�� ����
					if( !g_pParamMgr->HT_bGetPCSkillDuration( m_dwMainChar_ActiveSkillCurIndex, m_byMainChar_ActiveSkillCurLevel, &m_iMainChar_ActiveSkill_DurationTime ) )
						m_iMainChar_ActiveSkill_DurationTime = 0;
					//	����Ʈ ���۽ð�
					m_iMainChar_ActiveSkill_StartTime = GetTickCount();
					
					//	�ڽ������� ������ �ִ½�ų���� �ľ��ؼ� ���� ��ų�� ������ ������ �׷��� �������� �Ϲ� ��ų�� ������ ����
					HTbool	bExceptionForFX;
					if( m_dwMainChar_ActiveSkillCurIndex == 3028 ||			//	���ν��Ƴ� ��Ƽ��
						m_dwMainChar_ActiveSkillCurIndex == 3029 ||			//	����ī
						m_dwMainChar_ActiveSkillCurIndex == 3043 ||			//	����Ƽ
						m_dwMainChar_ActiveSkillCurIndex == 3061 ||			//	����ī
						m_dwMainChar_ActiveSkillCurIndex == 3017 ||
						m_dwMainChar_ActiveSkillCurIndex == 3361 ||			//	���Ƽ ��Ƽ��
						m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOPARTY )
					{
						bExceptionForFX = HT_TRUE;
						this->HT_vMainChar_CSP_Cast_Area_Cast();
					}
					else
					{
						bExceptionForFX = HT_FALSE;
						this->HT_vMainChar_CSP_Cast_Unit_Cast();
					}

					//	�������� ������ ��ų�̸� ����Ʈ Ʋ�� �ʴ´�.
					if( m_dwMainChar_ActiveSkillType != HT_PCSKILLTYPE_ACTIVE_STATE_LOOP_TOME_WITHENERGY )
					{
						//	�෹�̼� Ÿ���� ������ ���� ������ �ѹ� ��ų�� ǥ���Ѵ�.
						if( m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME ||
							m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_PERATTACK ||
							m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_PERATTACKED ||
							m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOPARTY ||
							bExceptionForFX == HT_TRUE )
							g_pEngineHandler->HT_hrStartSFX( &m_iMainChar_ActiveSkillEffectID, m_dwMainChar_ActiveSkillCurIndex, HT_SFX_WHEN_STATE, m_iMainChar_ModelID, HT_FALSE, m_byMainChar_ActiveSkillCurLevel );
						else
							g_pEngineHandler->HT_hrStartSFX( &m_iMainChar_ActiveSkillEffectID, m_dwMainChar_ActiveSkillCurIndex, HT_SFX_WHEN_STATE, m_iMainChar_ModelID, HT_TRUE, m_byMainChar_ActiveSkillCurLevel );
					}

					//	��Ƽ�� ��ų �ε���
					m_iMainChar_ActiveSkillIndex = 3;
				}
			}
			break;
		case 3 :
			{
				if( iPassTime > m_iMainChar_ActiveSkill_StartTime+(m_iMainChar_ActiveSkill_DurationTime) )
				{
					m_iMainChar_ActiveSkill_DurationTime = 0;
					m_dwMainChar_ActiveSkillCurIndex = 0;
					m_byMainChar_ActiveSkillCurLevel = 0;
					m_dwMainChar_ActiveSkillType = 0;

					//	��Ƽ�� ��ų ����
					this->HT_vMainChar_StopActiveSkill();
					//	��Ƽ�� ��ų �ε���
					m_iMainChar_ActiveSkillIndex = 0;
				}
			}
			break;
	}
}

//	��Ƽ�� ����Ʈ �Ѿ� �ɶ�_STATE_ONCE_TOME_PERATTACK, PERATTACKED
HTvoid HTMainCharacter::HT_vMainChar_SetActiveSkillEffect()
{
	if(( m_iMain_Affections & eTNVSAfn_MagicShield ))
	{
		g_pEngineHandler->HT_hrStopSFX( m_iMain_ActiveImpactFXID );
		g_pEngineHandler->HT_hrStartSFX( &m_iMain_ActiveImpactFXID, 3102, HT_SFX_WHEN_STATE, m_iMainChar_ModelID, HT_FALSE, 1 );
	}
	if( ( m_iMain_Affections & eTNVSAfn_EnhancedMagicShield ) )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iMain_ActiveImpactFXID );
		g_pEngineHandler->HT_hrStartSFX( &m_iMain_ActiveImpactFXID, 3145, HT_SFX_WHEN_STATE, m_iMainChar_ModelID, HT_FALSE, 1 );
	}
	
}

//	��Ƽ�� ��ų ����
HTvoid HTMainCharacter::HT_vMainChar_StopActiveSkill()
{
	if( m_iMainChar_ActiveSkillEffectID != 0 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iMainChar_ActiveSkillEffectID );
		m_iMainChar_ActiveSkillEffectID = 0;
	}
}

//----------���� ���ݴ������ �ľ�----------------//
HTvector3 HTMainCharacter::HT_vecMainChar_GetAtkTargetCheck( DWORD dwTargetKeyID )
{
	if( dwTargetKeyID == m_iMainChar_KeyID )
	{
		HTvector3 vecPos = m_cMainCharMove->HT_vecGetPosition();
		vecPos.y = (HTfloat)m_iMainChar_ModelID;
		return vecPos;
	}
	else
		return HTvector3( 0, 0, 0 );
}

//----------���� �޾����� ����� �� �ϵ�----------//
HTvoid HTMainCharacter::HT_vMainChar_SetDisAttackCheck( HTint iSkillID, HTint iItemID, HTint iInvadeModelID )
{
	if( m_nMainChar_AniResentState	== CHARACTER_ANISTATE_DIE )
		return;

	//	���� ��Ƽ�� ��ų �ߵ����϶� ����Ʈ Ʋ�� ����_��ų��
	this->HT_vMainChar_SetActiveSkillEffect();

	//	Impact Effect
	if( iSkillID == 0 )
	{
		g_pEngineHandler->HT_hrStartSFX( iItemID, iInvadeModelID, m_iMainChar_ModelID );
	}
	else
	{
		g_pEngineHandler->HT_hrStartSFX( iSkillID, iInvadeModelID, m_iMainChar_ModelID );
	}

	//	���� ��������� ���⼭ ��ŵ
	if( g_cIndividualStore->HT_bIndividualStore_IsStoreMode() )
		return;

	//	�ڸ���� ����� �����Ѵ�.
	if( g_pDuelSystem->HT_bDuel_GetWaitMode() == HT_TRUE )
        g_pDuelSystem->HT_vDuel_SetWaitModeCancelFromKeyInput();

	//----------�ɾ� �־��ٸ� Ǯ��----------//
	if( m_bMainChar_SitSw == HT_TRUE )
	{
		m_bMainChar_SitSw = HT_FALSE;
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		//----------�ٸ�ĳ���� �̵��� ��ε� ĳ�����ϱ� ���� ��Ŷ----------//
		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		this->HT_vNetWork_Send_MSGAction( 1, pPt.x, pPt.y );
	}

	//	ĳ���� ���� ��ȭ�ֱ�
	// ���� ȭ�� �ñ� ���� �� ���� �ƴҶ���
	if( !(m_iMain_Affections&eTNVSAfn_Damage) &&
		!(m_iMain_Affections & eTNVSAfn_Fire) &&
		!(m_iMain_Affections & eTNVSAfn_Cold) &&
		!(m_iMain_Affections & eTNVSAfn_Lightning) &&
        !(m_iMain_Affections & eTNVSAfn_Poison) &&
		!(m_iMain_Affections & eTNVSAfn_ProtectFromPK) )
        this->HT_vMainChar_SetModelColor( 1.0f, 0.1f, 0.0f, 0.4f );

	if( !m_bMainChar_HitEventCanSw )
		return;

	//	�ܰŸ� �����̾��ٸ� Skip
	//if( m_iMainChar_AttackRange_ActionSkill <= 1 )
        //return;

	//	0:���۰�, 1:������
	HTbyte bySkillType = 0;
	if( iSkillID )
        g_pParamMgr->HT_bGetPCSkillType( iSkillID, 1, &bySkillType );

	if( bySkillType == 0 )
	{
		//	�ø�Ŀ
		g_pEngineHandler->HT_hrFlickerObject( m_iMainChar_ModelID, HT_COLOR( 1.00f, 0.20f, 0.10f, 1.0f ), 0.4f );

        if( m_nMainChar_AniResentState != CHARACTER_ANISTATE_WLK && 
			m_nMainChar_AniResentState != CHARACTER_ANISTATE_RUN )
		{
			//	���� ���̾��ٸ�
			if( m_bMainChar_AttackSw )
			{
				//	Ȱ�϶� ��ŵ
				if( m_bMainChar_ItemArrow == HT_TRUE )
					return;

				//	��ų�϶�
				if( m_bMainChar_ActionSkillIndex )
				{
					//	��Ÿ� ��ų�϶��� ���
					if( m_byMainChar_AttackRange > 2 )
						this->HT_vMainChar_SetAttackCancel( 19 );
					else
					{
						if( m_iMainChar_RealAttackIndex != 4 )
							return;
					}
				}
			}

			m_nMainChar_AniResentState = CHARACTER_ANISTATE_HIT;
			this->HT_vMainChar_SetChangeAni( 0x01, 1, 0.0f, 0, 0 );
			//	ĳ���� ����
			m_cMainCharMove->HT_vMainCharMove_StopMvoe();
		}
	}
	//else
	//{
	//	m_nMainChar_AniResentState = CHARACTER_ANISTATE_MAGIC_DEFENCE;
	//	this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
	//}
}

//	����
HTvoid HTMainCharacter::HT_vMainChar_SetTransparency( HTbyte byGMMode, __int64 iAffection )
{
	//	���� ��� ����
	if( ( byGMMode & 0x02 ) != 0x00 ||
		iAffection != 0 ||
		g_bTransparencyMode )
	{
		g_pEngineHandler->HT_hrShowObject( m_iMainChar_ModelID, HT_FALSE );
	}
	//	���� ��� �� ����
	else
	{
		////	����Ʈ�� ������ ����
		//if( m_iMain_FXAffections != -1 )
		//	g_pEngineHandler->HT_hrStopSFX( m_iMain_FXAffections );

		g_pEngineHandler->HT_hrShowObject( m_iMainChar_ModelID, HT_TRUE );
		//	���ǽ�ų ���ϴ� �༮�� Delete ��ī��...��.��
		g_pMainBar->HT_vMainBar_MySkillSetDelete( 3103 );
	}
}

//----------������ �������ų� ��Ż �̵� ��û���� ��----------//
HTvoid HTMainCharacter::HT_vMainChar_SetCanNotMove( HTbool bEffectSw )
{
	//	Move Action On/Off Check
	m_bMainChar_MoveSw = HT_FALSE;

// Affection �� �̿��� FX�� ��ü �ȴ�.
//	if( bEffectSw &&
//		m_iMain_FaintingstateFX == 0 )
//	{	
//		g_pEngineHandler->HT_hrStartSFX( &m_iMain_FaintingstateFX, HT_FX_FAINTINGSTATE, m_iMainChar_ModelID, HT_TRUE );
//	}

	//----------ĳ���� ���� ����----------//
	//	Ȧ���϶��� �������� �ƴҶ��� ����
	if( m_iMain_Affections&eTNVSAfn_Hold ||
		m_iMain_Affections&eTNVSAfn_Hold2 )
	{
		if( m_nMainChar_AniResentState != CHARACTER_ANISTATE_NORMALATK &&
			m_nMainChar_AniResentState != CHARACTER_ANISTATE_SKILLREADY &&
			m_nMainChar_AniResentState != CHARACTER_ANISTATE_SKILLCAST &&
			m_nMainChar_AniResentState != CHARACTER_ANISTATE_SKILLACTIVATE &&
			m_nMainChar_AniResentState != CHARACTER_ANISTATE_SKILLATK )
			this->HT_vMainChar_SetStopMove();
	}
	else
	{
		this->HT_vMainChar_SetStopMove();
	}
}

//----------��Ż�̵�----------//
HTvoid HTMainCharacter::HT_vMainChar_SetCanMove()
{
	//	Move Action On/Off Check
	m_bMainChar_MoveSw = HT_TRUE;

	if( m_iMain_FaintingstateFX )
	{
        g_pEngineHandler->HT_hrStopSFX( m_iMain_FaintingstateFX );
		m_iMain_FaintingstateFX = 0;
	}
}

//---------------------------------------------//
//------------------��ȯ����-------------------//
//---------------------------------------------//
//	�������� �������� ĳ������ ���� ����
HTvoid HTMainCharacter::HT_vMainCHar_SCP_SetAffections( __int64 iAffections )
{
	//	�����Ͼ����� Ǯ���ֱ� ���� ���� �ε��� 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	if( m_iMain_Affections & eTNVSAfn_Stun || 
		m_iMain_Affections & eTNVSAfn_Sleep )
        m_iMainChar_RealAttackIndex = 1;

	//	Affections Fx On/Off
	HTdword dwFXID = g_pEngineHandler->HT_dwGetAffectionFXID( iAffections, m_iMain_Affections );
    //if ( iAffections == eTNVSAfn_MoveSpeed140R ) dwFXID = 1010090;//fors_debug ֱ�Ӹ�ֵ �³��
	if( dwFXID == 0 )
	{
		if( m_iMain_FXAffections != -1 )
		{
			g_pEngineHandler->HT_hrStopSFX( m_iMain_FXAffections );
			m_iMain_FXAffections = -1;
		}
	}
	else
	{
		if( ( m_iMain_FXAffections != -1 ) ) 
			g_pEngineHandler->HT_hrStopSFX( m_iMain_FXAffections );

		if( g_iInationalType == INATIONALTYPE_JAPEN )
		{
			g_pEngineHandler->HT_hrStartSFX( &m_iMain_FXAffections, dwFXID, m_iMainChar_ModelID, HT_TRUE );
		}
		else
		{
			if( !(iAffections&eTNVSAfn_WizardEyes) )
			{
				g_pEngineHandler->HT_hrStartSFX( &m_iMain_FXAffections, dwFXID, m_iMainChar_ModelID, HT_TRUE );
			}
		}
	}

	//	�����
	if( (iAffections & eTNVSAfn_Blind) &&
		!(m_iMain_Affections & eTNVSAfn_Blind) )
	{
		g_pEngineHandler->HT_vSetBlind();
	}
	else if( !(iAffections & eTNVSAfn_Blind) &&
		(m_iMain_Affections & eTNVSAfn_Blind ) )
	{
		g_pEngineHandler->HT_vSetUnBlind();
	}

	//	������ Affections ����
	m_iMain_Affections = iAffections;

	//	���� üũ
	//if( iAffections & eTNVSAfn_Invisible ) //fors_debug ��
	this->HT_vMainChar_SetTransparency( 0x00, m_iMain_Affections & eTNVSAfn_Invisible );

	//	���� üũ, ���� üũ, Ȧ�� üũ
	if( m_iMain_Affections & eTNVSAfn_Stun || 
		m_iMain_Affections & eTNVSAfn_Sleep ||
		m_iMain_Affections & eTNVSAfn_Hold ||
		m_iMain_Affections & eTNVSAfn_Hold2 )	g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_TRUE );
	else										g_cMainCharacter->HT_vMainChar_SetCanMove();

	//	������ ��
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetWizardEyes( m_iMain_Affections & eTNVSAfn_WizardEyes );

	//	ĳ���� �� ����
	//	���� ��������
	CHTString strMsg, szMessage;
	strMsg.HT_hrCleanUp();
	if( m_iMain_Affections & eTNVSAfn_Damage ) // ����
	{
		this->HT_vMainChar_SetModelColor( 1.0f, 0.0f, 0.0f, 1.0f );	//	����
		HT_vMainChar_SetMessage( eMsgCommonSkillPhysics, &strMsg );
	}
    if( m_iMain_Affections & eTNVSAfn_Fire ) // ȭ��
	{
		this->HT_vMainChar_SetModelColor( 1.0f, 1.0f, 0.0f, 1.0f );	//	���
		if( strMsg.HT_bIsEmpty() )
			HT_vMainChar_SetMessage( eMsgCommonSkillBlaze, &strMsg);
		else
		{
			HT_vMainChar_SetMessage( eMsgCommonSkillBlaze, &szMessage);
			strMsg = strMsg + _T(", ") + szMessage;
		}
	}
	if( m_iMain_Affections & eTNVSAfn_Cold ) // �ñ�
	{
		this->HT_vMainChar_SetModelColor( 0.0f, 1.0f, 1.0f, 1.0f );	//	û��
		if( strMsg.HT_bIsEmpty() )
			HT_vMainChar_SetMessage( eMsgCommonSkillCold, &strMsg);
		else
		{
			HT_vMainChar_SetMessage( eMsgCommonSkillCold, &szMessage);
			strMsg = strMsg + _T(", ") + szMessage;
		}
	}
	if( m_iMain_Affections & eTNVSAfn_Lightning ) // ����
	{
		this->HT_vMainChar_SetModelColor( 0.9f, 0.5f, 0.0f, 1.0f );	//	���� û��
		if( strMsg.HT_bIsEmpty() )
			HT_vMainChar_SetMessage( eMsgCommonSkillLightning, &strMsg);
		else
		{
			HT_vMainChar_SetMessage( eMsgCommonSkillLightning, &szMessage);
			strMsg = strMsg + _T(", ") + szMessage;
		}
	}
	if( m_iMain_Affections & eTNVSAfn_Poison ) // ��
	{
		this->HT_vMainChar_SetModelColor( 0.0f, 1.0f, 0.0f, 1.0f );	//	���
		if( strMsg.HT_bIsEmpty() )
			HT_vMainChar_SetMessage( eMsgCommonSkillPoison, &strMsg);
		else
		{
			HT_vMainChar_SetMessage( eMsgCommonSkillPoison, &szMessage);
			strMsg = strMsg + _T(", ") + szMessage;
		}
	}
	if( !strMsg.HT_bIsEmpty() )
	{
		// ���� �������� �ް� �ֽ��ϴ�.
		HT_vMainChar_SetMessage( eMsgCharacterContinuousDamage, &szMessage);
		strMsg = strMsg + _T(" ") + szMessage;

		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
	}

	//	���� ����
	if( m_iMain_Affections & eTNVSAfn_ProtectFromPK )
	{
		this->HT_vMainChar_SetModelColor( 0.247f, 0.148f, 0.29f, 2.0f );	//	��Ȳ
	}
/*
	if(iAffections & eTNVSAfn_Invisible )
	{
		//	WizardEyesSw Check
		if( !(iAffections&eTNVSAfn_WizardEyes) )
		{
			//	���Ž�ų�� �����ٸ� ���õǾ����� ���� Ǯ���ش�.
			//this->HT_vOtherObject_SetHideInfomation();
			g_pMainBar->HT_vSetObjectHPOut();
			g_pMainBar->HT_vSetObjectNameOut();
			//	���� ����ĳ���Ͱ� �����ϴ� ĳ���Ͱ� �ڽ��̸� �������
			//if( g_cMainCharacter->HT_iMainChar_GetAttackTargetKeyID() == m_pObjectInfo->nID )
                g_cMainCharacter->HT_vMainChar_SetAttackCancel( 25 );
		//	this->HT_vOtherObject_SetModelHide( HT_FALSE );
			//	���Ÿ� Ȱ��ȭ�ǰ� �ٸ����͵��� ������� ó��
//			m_pObjectInfo->iAffections = eTNVSAfn_Invisible;
		}
	}
*/
}
HTvoid HTMainCharacter::HT_vMainChar_SetInitAffectionsEffect()
{
	if( m_iMain_FXAffections != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iMain_FXAffections );
		m_iMain_FXAffections = -1;
	}
}
//	���� ����ǥ�� ��ȯ
HTPoint HTMainCharacter::HT_ptMainChar_GetCellPosition()
{
	return m_cMainCharMove->HT_ptGetCellPosition();
}

HTvoid HTMainCharacter::HT_vMainChar_SetCellPosition( HTshort snX, HTshort snZ )
{
	m_cMainCharMove->HT_vSetCellPosition( snX, snZ );
}

CHTString HTMainCharacter::HT_strMainChar_GetTribe()
{
	CHTString strTribe;

	switch( g_oMainCharacterInfo.snTribe )
	{
		case HT_ID_CHARACTER_NAGA:		// ����
			HT_vMainChar_SetMessage( eMsgCommonTribeNaga, &strTribe); break;
		case HT_ID_CHARACTER_ASURA:		// �Ƽ���
			HT_vMainChar_SetMessage( eMsgCommonTribeAsura, &strTribe); break;
		case HT_ID_CHARACTER_YAKSA:		// ��ũ��
			HT_vMainChar_SetMessage( eMsgCommonTribeYaksha, &strTribe); break;
		case HT_ID_CHARACTER_DEVA:		// ����
			HT_vMainChar_SetMessage( eMsgCommonTribeDeva, &strTribe); break;
		case HT_ID_CHARACTER_KIMNARA:	// Ų����
			HT_vMainChar_SetMessage( eMsgCommonTribeKimnara, &strTribe); break;
		case HT_ID_CHARACTER_RAKSHASA:	// ������
			HT_vMainChar_SetMessage( eMsgCommonTribeRakshasa, &strTribe); break;
		case HT_ID_CHARACTER_GANDHARVA: // ���ٸ���
			HT_vMainChar_SetMessage( eMsgCommonTribeGandharva, &strTribe); break;
		case HT_ID_CHARACTER_GARUDA:	// �����
			HT_vMainChar_SetMessage( eMsgCommonTribeGaruda, &strTribe); break;
		case HT_ID_CHARACTER_GM :		// GM
			HT_vMainChar_SetMessage( eMsgCommonTribeGM, &strTribe); break;
		default:						// ���
			HT_vMainChar_SetMessage( eMsgCommonTribeAdministrator, &strTribe); break;
	}

	return strTribe; 
}

HTint HTMainCharacter::HT_iMainChar_GetTribeServerCode()
{
	switch( g_oMainCharacterInfo.snTribe )
	{
		case HT_ID_CHARACTER_NAGA :			return TRIBE_NAGA;
		case HT_ID_CHARACTER_ASURA :		return TRIBE_ASURA;
		case HT_ID_CHARACTER_YAKSA :		return TRIBE_YAKSA;	
		case HT_ID_CHARACTER_DEVA :			return TRIBE_DEVA;
		case HT_ID_CHARACTER_KIMNARA :		return TRIBE_KINNARA;
		case HT_ID_CHARACTER_RAKSHASA :		return TRIBE_RAKSHASA;
		case HT_ID_CHARACTER_GANDHARVA :	return TRIBE_GANDHARVA;
		case HT_ID_CHARACTER_GARUDA :		return TRIBE_GARUDA;
		//case HT_ID_CHARACTER_GM :			return TRIBE_NONE;
		default:							return 0;
	}
}

HTvector3 HTMainCharacter::HT_vecGetPosition()
{
	HTvector3 vecPos = m_cMainCharMove->HT_vecGetPosition();
	return vecPos;
};

HTint HTMainCharacter::HT_iMainChar_GetAttackPoint()
{
	return 0;
}

HTint HTMainCharacter::HT_iMainChar_GetDefensePoint()
{
	return 0;
}

HTint HTMainCharacter::HT_nMainChar_GetMAXHP()
{
	return m_iMainChar_MAX_HP;
}

HTvoid HTMainCharacter::HT_nMainChar_SetMAXHP( HTint nMAXHP )
{
	m_iMainChar_MAX_HP = nMAXHP;
	// �ִ� HP�پ��� ��� ���� HP �� ����
	if( m_iMainChar_Cur_HP > m_iMainChar_MAX_HP )
	{
		m_iMainChar_Cur_HP = m_iMainChar_MAX_HP;
	}
	g_pMainBar->HT_vHPUpdate( this->HT_nMainChar_GetResentHP(), this->HT_nMainChar_GetMAXHP() );
}
HTint HTMainCharacter::HT_nMainChar_GetResentHP()
{
	return m_iMainChar_Cur_HP;
}

HTvoid HTMainCharacter::HT_bMainChar_SetShowName()
{
	if( m_bMainChar_ShowNameSw == HT_TRUE )
		m_bMainChar_ShowNameSw = HT_FALSE;
	else
		m_bMainChar_ShowNameSw = HT_TRUE;
}

HTvoid HTMainCharacter::HT_bMainChar_SetShowName( HTbool bTrue )
{
	m_bMainChar_ShowNameSw = bTrue;
}

//	������ �޴°�->�������� �޾Ƽ� ó��
HTvoid HTMainCharacter::HT_nMainChar_SetDemageHP( CHTString strName, HTint iDamageHP )
{
	m_iMainChar_Cur_HP -= iDamageHP;
	if( m_iMainChar_Cur_HP < 0 )
		m_iMainChar_Cur_HP = 0;

	g_pMainBar->HT_vHPUpdate( m_iMainChar_Cur_HP, this->HT_nMainChar_GetMAXHP() );

	//	�޽��� �ٿ�
	CHTString strMessage;
	strMessage.HT_hrCleanUp();
	//char chName[SZNAME_LENGTH];
	//CHTString::HT_hrStringCopy( chName, strName, SZNAME_LENGTH );
	//strMessage.HT_szFormat( "%s�� ���� ������ %d��(��) �޾ҽ��ϴ�.", chName, iDamageHP );
	m_iMessageVal = iDamageHP;
	m_szEnemyName = strName;
	HT_vMainChar_SetMessage( eMsgAttackReceiveDamage, &strMessage );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ATTACKED, strMessage );
}

HTvoid HTMainCharacter::HT_nMainChar_SetCurHP( HTint iCurHP )
{
	m_iMainChar_Cur_HP = iCurHP;
	if( m_iMainChar_Cur_HP <= 0 )
	{
		m_iMainChar_Cur_HP = 0;
	}

	//	statusâ HP �� ����
	g_pMainBar->HT_vHPUpdate( m_iMainChar_Cur_HP, this->HT_nMainChar_GetMAXHP() );
}

HTvoid HTMainCharacter::HT_vMainChar_SetTotalPrana( HTint iPrana )
{
	// ���� ȹ�淮 �ý���â�� ǥ��
	if( iPrana > m_iMainChar_TotalPrana )
	{
		// �ý��� â�� ǥ��
		HTint iRevPrana = iPrana - m_iMainChar_TotalPrana;
		if( iRevPrana < 0 )
			iRevPrana = 0;
	}
	m_iMainChar_TotalPrana = iPrana;
	//	���� ����_UI�� ����
	g_pMainBar->HT_vPranaUpdate( m_iMainChar_TotalPrana );
}

HTvoid HTMainCharacter::HT_vMainChar_SetBrahman_Rising( PS_SCP_RESP_BRAHMAN_RISING info )
{
	g_oMainCharacterInfo.nBrahmanPoint	=  info->nRisingBrahman;

	// ���� ȹ�淮 �ý���â�� ǥ��
	if( info->nPrana > m_iMainChar_TotalPrana )
	{
		// �ý��� â�� ǥ��
		//HTint nRevPrana = info->nPrana - m_iMainChar_TotalPrana;
		//if( nRevPrana < 0 )
		//	nRevPrana = 0;
		m_iMessageVal = info->nPrana - m_iMainChar_TotalPrana;
		if( m_iMessageVal < 0 )
			m_iMessageVal = 0;

		CHTString szMessage;
		//szMessage.HT_szFormat("���� %d��(��) ȹ���߽��ϴ�.", nRevPrana);
		HT_vMainChar_SetMessage( eMsgAttackReceivePrana, &szMessage);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	}
	m_iMainChar_TotalPrana = info->nPrana;

	//---------���� ����----------//
	g_pMainBar->HT_vHPUpdate(this->HT_nMainChar_GetResentHP(), this->HT_nMainChar_GetMAXHP() );
}

HTvoid HTMainCharacter::HT_vMainChar_NetWork_ChattingMessage( BYTE byType, CHTString strMessage )
{
	//	ä�ø޽���
	if( strMessage.HT_nGetSize() < 60 )
        m_strMainChar_ChatMsg = strMessage;
	else
	{
		m_strMainChar_ChatMsg.HT_hrCleanUp();
		CHTString::HT_hrStringCopy( m_strMainChar_ChatMsg, strMessage, 55 );
		m_strMainChar_ChatMsg += _T("...");		
	}
	m_dwMainChar_ChatMsgDelayTime = GetTickCount();
}

HTvoid HTMainCharacter::HT_vMainChar_SetArmsType( DWORD dwItemIndex )
{
	//	�������� ĳ���� �ӵ��� ����
	//	�������� ���ݼӵ��� ����
	HTint iTempValue;
	if( !g_pParamMgr->HT_bGetItemCoolDownTime( dwItemIndex, &iTempValue ) )
		iTempValue = 0;
	m_dwMainChar_AttackItemSpeed = iTempValue;
	//	�������� �����Ÿ� ����
	if( !g_pParamMgr->HT_bGetItemRange( dwItemIndex, &m_byMainChar_AttackRange_Item ) )
		m_byMainChar_AttackRange_Item = 0;
	//	Ư���� �����ۿ� ���� �����Ÿ� ������ �ִ��� üũ�Ѵ�.
	HTint iSpecialRange;
	g_pParamMgr->HT_bGetItemEffect5ID( dwItemIndex, &iSpecialRange );
	if( iSpecialRange == 3160 )		//	Effect No 3160�̸� �����Ÿ� ��������.
	{
		if( g_pParamMgr->HT_bGetItemEffect5Param1( dwItemIndex, &iSpecialRange ) )
			m_byMainChar_AttackRange_Item += iSpecialRange;
	}
    //	�������� ���ݼӵ� üũ
	if( !g_pParamMgr->HT_bGetItemCoolDownTime( dwItemIndex, &m_iMainChar_CastGaterTime_Item ) )
		m_iMainChar_CastGaterTime_Item = 0;

	if( dwItemIndex != 0 )
	{
		if ( HT_IS_ITEM_WEAR( dwItemIndex ) )
		{
			m_dwWearItemID	= dwItemIndex;
		}
		else if ( HT_IS_ITEM_WEAPON( dwItemIndex ) )
		{
			m_dwWeaponItemID = dwItemIndex;
		}
	}
	else
	{
		m_dwWeaponItemID = 0;
	}

	//	Ȱ�϶��� �޼տ� Ȱ�� �־�� ���� �Ҽ� �ִ�.
	if( CHTParamIDCheck::HT_bIsItemWeaponThrow( dwItemIndex ) )
		m_bMainChar_ItemArrow = HT_TRUE;
	else
		m_bMainChar_ItemArrow = HT_FALSE;

	//	���⿡ �´� �ִϸ��̼� ����
	this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
}

//----------�Դ¿� ������ ���̵� ����----------------//
HTvoid HTMainCharacter::HT_vMainChar_SetWearItem( DWORD dwItem )
{
	m_dwWearItemID	= dwItem;
}

HTvoid HTMainCharacter::HT_vMainChar_SetWeaponItem( DWORD dwItem )
{
	m_dwWeaponItemID = dwItem;
}

// ĳ������ ��ɼ� ������ ��ȿ�Ⱓ �ʱ�ȭ
HTvoid HTMainCharacter::HT_vMainChar_InitTimeStamp( HTdword dwTimeStamp[MAX_TIMEITEM] )
{
	time_t svTime;
	tm* psTmTime = HT_NULL;
	for( HTint i = 0 ; i < MAX_TIMEITEM ; ++i )
	{
		ZeroMemory( &m_timeMainChar_TimeStamp[i], sizeof(time_t) );
		if( dwTimeStamp[i] > 0 )
		{
			svTime = (time_t)dwTimeStamp[i];
			m_timeMainChar_TimeStamp[i] = svTime;
		}
	}
}
// ĳ������ ��ɼ� �������� ��ȿ�Ⱓ
HTvoid HTMainCharacter::HT_vMainChar_SetTimeStamp( HTbyte byTimeArrIndex, HTdword dwTime )
{
	if( byTimeArrIndex < 0 || byTimeArrIndex >= MAX_TIMEITEM )
		return;
	
	m_timeMainChar_TimeStamp[byTimeArrIndex] = (time_t)dwTime;
}

HTvoid HTMainCharacter::HT_vMainChar_GetTimeStamp( HTbyte byTimeArrIndex, CHTString& szTime )
{
	if( byTimeArrIndex < 0 || byTimeArrIndex >= MAX_TIMEITEM )
	{
		if (byTimeArrIndex < 254)
		{
			szTime.HT_hrCleanUp(); return;
		}
	}

	if (byTimeArrIndex < 254)
		m_byTimeArrIndex = byTimeArrIndex;
	else
		m_byTimeArrIndex = byTimeArrIndex - 254;

	switch( byTimeArrIndex )
	{
		case 254 :
			HT_vMainChar_SetMessage( eMsgItemEquipExpandDate, &szTime );
			break;
		case 255 :
			HT_vMainChar_SetMessage( eMsgShopExpandDate, &szTime );
			break;
		case eTime_Inven :
		case eTime_Store :
		case eTime_AMoneyRoot :
		case eTime_Atman :
		case eTime_Anubaba :
		case eTime_15Chakra :
			HT_vMainChar_SetMessage( eMsgShopAdeptDate, &szTime );
			break;
		default :
			szTime.HT_hrCleanUp(); break;
	}
}

HTbool HTMainCharacter::HT_bMainChar_GetTimeStamp( HTbyte byTimeArrIndex, time_t& timeTime )
{
	if( byTimeArrIndex < 0 || byTimeArrIndex >= MAX_TIMEITEM )
		return HT_FALSE;

	timeTime = m_timeMainChar_TimeStamp[byTimeArrIndex];
	return HT_TRUE;
}

//	Return Get MoveStop Stauts
HTbool HTMainCharacter::HT_bMainChar_GetMoveStopStatus()
{
	if( m_iMain_Affections & eTNVSAfn_Stun || 
		m_iMain_Affections & eTNVSAfn_Sleep ||
		m_iMain_Affections & eTNVSAfn_Hold ||
		m_iMain_Affections & eTNVSAfn_Hold2 )
		return HT_FALSE;
	else
		return HT_TRUE;
}

//	Return Get AttackStop Stauts
HTbool HTMainCharacter::HT_bMainChar_GetAttackStopStatus()
{
	if( m_iMain_Affections & eTNVSAfn_Stun || 
		m_iMain_Affections & eTNVSAfn_Sleep )
		return HT_FALSE;
	else
		return HT_TRUE;
}

//----------ĳ������ ���� ������ ��ȯ----------------//
HTfloat HTMainCharacter::HT_fMainChar_GetDirectAngle()
{
	return m_cMainCharMove->HT_fGetDirect();
}

//----------���� �κ�----------//
HTvoid HTMainCharacter::HT_vCharRender()
{
	//----------�ؽ�Ʈ ���� ó��----------//
	if( !g_bGamePlayMovieForGlobal )
        HT_vCharRenderText();
}

//----------�ؽ�Ʈ ���� ó��----------//
HTvoid HTMainCharacter::HT_vCharRenderText()
{
	HTvector3 vTextPos = m_cMainCharMove->HT_vecGetPosition();
	vTextPos.y += m_fModelHeight + 3.0f;
	//    -> ���� ����
	HTint iColor = 15;
	HT_COLOR cFontColor = HT_COLOR( 0.0f,0.0f,0.0f,0.0f );;
	
	if( m_bMainChar_ShowNameSw ==HT_TRUE &&
		(m_iMain_Affections & eTNVSAfn_Invisible) == 0 )
	{
		//	����� �����϶�
		if( HT_SUCCEED( HT_IS_BIRYUCASTLE( g_wResentZoneServerID ) ) &&
			m_byMainChar_Clan >= 19 )
		{
			//	����
			if( m_byMainChar_Clan == 19 )		cFontColor = HT_COLOR( 0.59f, 0.86f, 0.59f, 1.0f );
			//	����1
			else if( m_byMainChar_Clan == 20 )	cFontColor = HT_COLOR( 0.99f, 0.54f, 0.57f, 1.0f );
			//	����2
			else if( m_byMainChar_Clan == 21 )	cFontColor = HT_COLOR( 0.99f, 0.74f, 1.00f, 1.0f );
			//	����3
			else if( m_byMainChar_Clan == 22 )	cFontColor = HT_COLOR( 0.73f, 0.71f, 0.97f, 1.0f );
			//	���Ҽ�
			else if( m_byMainChar_Clan == 23 )	cFontColor = HT_COLOR( 0.67f, 0.67f, 0.66f, 1.0f );
		}
		//       -> ī����? 		-> ����
		else if( g_oMainCharacterInfo.snKarma > 0 )			iColor = 11;
		//       -> �����̳�? 	-> ����
		else if(m_iMain_Affections & eTNVSAfn_PKAttacker )	iColor = 10;
		//       -> �Ϲ�			-> ���
		else												iColor = 15;
		//	Set Color
		if( cFontColor.a == 0.0f )
            cFontColor = g_ColorTable[iColor];

		/*
		//	PC�� �̺�Ʈ
		if( g_dwMyEvent & 0x00000001 &&
			g_cStatus->HT_byGetLevel() < 60 )
		{
			cFontColor.r -= 0.2f; if(cFontColor.r<0.0f)	cFontColor.r = 0.0f;
			cFontColor.g -= 0.2f; if(cFontColor.g<0.0f)	cFontColor.g = 0.0f;
			cFontColor.b -= 0.2f; if(cFontColor.b<0.0f)	cFontColor.b = 0.0f;
		}
*/
		CHTString strTemp = g_cGuildSystem->HT_strGuild_GetGuildName();

		if( strTemp.HT_nGetSize() > 0 )
		{
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, strTemp.HT_szGetString(), vTextPos, cFontColor );
			vTextPos.y += 2.0f;
		}

		if( !g_bDevelopingMode )
		{
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, g_oMainCharacterInfo.szCharName, vTextPos, cFontColor );
		}
		else
		{
			HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
			CHTString strTemp;
			strTemp.HT_szFormat( "%s,ID:%d,x:%d,z:%d,Clan:%d,Af:%I64x", g_oMainCharacterInfo.szCharName, m_iMainChar_KeyID, pPt.x, pPt.y, m_byMainChar_Clan, m_iMain_Affections );
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, strTemp, vTextPos, cFontColor );
		}
		vTextPos.y += 2.0f;
	}

	if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetShowChatMsg() )
	{
		if( !m_strMainChar_ChatMsg.HT_bIsEmpty() )
		{
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, m_strMainChar_ChatMsg, vTextPos, g_ColorTable[15], HT_COLOR( 0.1f, 0.1f, 0.1f, 0.7f ), 3.0f );
			vTextPos.y += 2.0f;

			DWORD dwPassTime = GetTickCount();
			if( dwPassTime > m_dwMainChar_ChatMsgDelayTime + CHATMSGDELAYTIME )
				m_strMainChar_ChatMsg.HT_hrCleanUp();
		}
	}

	//	�������
	if ( g_cIndividualStore )
	{
		if( g_cIndividualStore->HT_bIndividualStore_IsStoreMode() )
		{
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, g_cIndividualStore->HT_szIndividualStore_StoreMessage(), vTextPos, HT_COLOR( 0.22f, 0.71f, 0.29f, 1.0f ) );
			vTextPos.y += 2.0f;
		}
	}
}

BYTE HTMainCharacter::HT_vMainChar_GetHeadType()
{
	return g_oMainCharacterInfo.byHeadType;
}

//	ĳ���� ���� ��ȭ�ֱ�
HTvoid HTMainCharacter::HT_vMainChar_SetModelColor( HTfloat r, HTfloat g, HTfloat b, HTfloat fTime )
{
	//	�ø�Ŀ
    g_pEngineHandler->HT_hrFlickerObject( m_iMainChar_ModelID, HT_COLOR( r, g, b, 1.0f ), fTime );
}

//----------�̵���� ����----------//
HTvoid HTMainCharacter::HT_vMainChar_MovePathSaved()
{
	m_pMainChar_MovePath[m_nMainChar_MoveResent] = m_cMainCharMove->HT_ptGetCellPosition();

	m_nMainChar_MoveResent++;
	if( m_nMainChar_MoveResent >= 1000 )
	{
		m_bMainChar_OneTimeRotate = HT_TRUE;
		m_nMainChar_MoveResent = 0;
	}

	if( m_bMainChar_OneTimeRotate == HT_TRUE )
	{
		m_nMainChar_MoveStart = m_nMainChar_MoveResent+1;
		if( m_nMainChar_MoveStart == 1000 )
			m_nMainChar_MoveStart = 0;
	}

	m_nMainChar_MovePathCount++;
	if( m_nMainChar_MovePathCount >= 1000 )
		m_nMainChar_MovePathCount = 1000;
}

//----------�̵���� ��ȯ----------//
HTvoid HTMainCharacter::HT_vMainChar_GetMovePath( HTPoint* pCell,  HTint nCount )
{
	HTint nTempCount = m_nMainChar_MoveStart + nCount;
	if( nTempCount >= 1000 )
		nTempCount = 1000 - nTempCount;

	if( nTempCount == m_nMainChar_MoveStart || nCount > m_nMainChar_MovePathCount )
	{
		pCell->x = 0;
		pCell->y = 0;
	}
	else
	{
		pCell->x = m_pMainChar_MovePath[nTempCount].x;
		pCell->y = m_pMainChar_MovePath[nTempCount].y;
	}
}

//---------------------------------------------//
// ��Ʈ��ũ�� �����Ͽ�
//---------------------------------------------//
//----------�������� ��Ŷ �����ޱ�-�̵� ����----------//
HTvoid HTMainCharacter::HT_vMainChar_NetWorkMoveFaild( PS_SCP_RESP_CHAR_MOVE info )
{
	m_cMainCharMove->HT_vMainCharMove_NetWorkMoveFaild( info->snX, info->snZ );

	//----------��ġ�� ȸ�� ����----------//
	HTvector3 vecTemp = m_cMainCharMove->HT_vecGetPosition();
	g_pEngineHandler->HT_hrMoveObject( m_iMainChar_ModelID, vecTemp );

	//-----ȭ���� �Ͼ�� ���ϴ� ������ ���� ����-----//
	m_bMainChar_WhiteError			= HT_TRUE;
}

HTvoid HTMainCharacter::HT_vNetWork_CheckCharMove()
{
	HT_CELL_COORD codCell;
	float fx, fz;
	HTint iMoveTerm;

	HTvector3 vecTempPos = m_cMainCharMove->HT_vecGetPosition();

	//	�̵��� ���� ����
	if( m_bMainChar_AttackSw )
	{
		HTint nRange = (HTint)HT_extern_fGetDisForTwoPoint( m_vecMainChar_TargetPos, vecTempPos );
		if( nRange > 3 ) 	iMoveTerm = 3;
		else	            iMoveTerm = 1;
	}
	else
	{
		iMoveTerm = 5;
	}

	//	������ ���� ��ǥ�� ���ؼ� ���� �̵������� ������ �ʴ´�.
	fx = (float)sqrt( double( (vecTempPos.x - m_vecMainChar_ReqSendMovePos.x) * (vecTempPos.x - m_vecMainChar_ReqSendMovePos.x) ) );
	fz = (float)sqrt( double( (vecTempPos.z - m_vecMainChar_ReqSendMovePos.z) * (vecTempPos.z - m_vecMainChar_ReqSendMovePos.z) ) );
	if( fx+fz <  MAP_CELL_SIZE*iMoveTerm )
		return;

	//	Ÿ�� ��ǥ�� ���Ͽ� Ÿ������ ũ�� ������ ����ؼ� �����ְ� ������ Ÿ�a���� �̵���Ų��.
	fx = (float)sqrt( double( (vecTempPos.x - m_vecMainChar_MoveTargetPos.x) * (vecTempPos.x - m_vecMainChar_MoveTargetPos.x) ) );
	fz = (float)sqrt( double( (vecTempPos.z - m_vecMainChar_MoveTargetPos.z) * (vecTempPos.z - m_vecMainChar_MoveTargetPos.z) ) );
	if( fx+fz > MAP_CELL_SIZE*iMoveTerm )
	{
		m_bMainChar_MoveTargetCheckSw = HT_TRUE;
		fx = sinf( m_cMainCharMove->HT_fGetDirect() ) * ( MAP_CELL_SIZE*iMoveTerm );
		fz = cosf( m_cMainCharMove->HT_fGetDirect() ) * ( MAP_CELL_SIZE*iMoveTerm );
		HTvector3 vecSendTempPos;
		vecSendTempPos.x = vecTempPos.x+fx;
		vecSendTempPos.z = vecTempPos.z+fz;
		g_pEngineHandler->HT_3DCOORD_TO_CELL( vecSendTempPos, codCell );
	}
	else
	{
		m_bMainChar_MoveTargetCheckSw = HT_FALSE;
		g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecMainChar_MoveTargetPos, codCell );
	}

	//	������ ���� ��ǥ�� ������ �д�.
	if( m_bMainChar_WalkRun_Sw == HT_FALSE )
		this->HT_vNetWork_Send_MSGAction( 2, codCell.x, codCell.y );
	else
		this->HT_vNetWork_Send_MSGAction( 3, codCell.x, codCell.y );
	m_vecMainChar_ReqSendMovePos = vecTempPos;
}

//----------ĳ���� �̵��� ��ε� ĳ�����ϱ� ���� ��Ŷ_Send----------//
HTvoid HTMainCharacter::HT_vNetWork_Send_MSGAction( BYTE byEffect, HTint iEndX, HTint iEndZ )
{
	//	Effect of MSG_Action
	if( m_iMain_ActionEffect == 7 )
		return;

	//	����
	if( byEffect == 8 )
	{
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_PROVOKE;
		this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
	}
	//	�λ�
	else if( byEffect == 9 )
	{
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_BOW;
		this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
	}
	//	����
	else if( byEffect == 10 )
	{
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_CHARGE;
		this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
	}

	//	�̵� �޽��� ������ �ø��� �׶��� ��ġ ����
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
	m_pMainChar_SaveMovePos.x = iEndX;
	m_pMainChar_SaveMovePos.y = iEndZ;
	
	MSG_Action *info = HT_NULL;
	info = new MSG_Action;
	info->Direction		= (short)(m_cMainCharMove->HT_fGetDirect()*100);
	info->dwKeyID		= m_iMainChar_KeyID;
	info->Effect		= byEffect;
	info->PosX			= pPt.x;
	info->PosY			= pPt.y;
	info->TargetX		= iEndX;
	info->TargetY		= iEndZ;
	info->Speed			= m_cMainCharMove->HT_iMainCharMove_GetSpeed( 0x00 );
	g_pNetWorkMgr->RequestMSG_Action( info );
	////-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MsgAction : x:%d,z:%d-x:%d,z:%d", info->PosX, info->PosY, info->TargetX, info->TargetY );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}

//----------ĳ���� �̵��� ��ε� ĳ�����ϱ� ���� ��Ŷ_Recive----------//
HTvoid HTMainCharacter::HT_vNetWork_Recive_MSGAction( MSG_Action *info )
{
	//	ĳ���� Ȱ��ȭ ����....
	if( m_iMainChar_Cur_HP != 0 )
        m_bMainChar_Live = HT_TRUE;

	//	�켱 Cell ��ǥ�� Coord ��ǥ�� ���Ѵ�.
	HTvector3 vecTempPos;
	HT_CELL_COORD crdCell;
	crdCell.x = info->TargetX;
	crdCell.y = info->TargetY;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( vecTempPos, crdCell );

	//	������ ���� ��ǥ
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();

	//	Effect of MSG_Action
	m_iMain_ActionEffect = info->Effect;

	////	0:�ɱ�
	//if( info->Effect == 0 )
	//{
	//	//	Move Action On/Off Check
	//	m_bMainChar_MoveSw = HT_TRUE;
	//	//	���� ������� ��ȯ���ְ�,
	//	m_bMainChar_SitSw = HT_FALSE;
	//	//	�ɱ� ����
	//	this->HT_vMainChar_SetSit();
	//}
	////	1:����
	//else if( info->Effect == 1 )
	//{
	//	//	Move Action On/Off Check
	//	m_bMainChar_MoveSw = HT_TRUE;
	//	//	���� ������� ��ȯ���ְ�,
	//	m_bMainChar_SitSw = HT_TRUE;
	//	//	�ɱ� ����
	//	this->HT_vMainChar_SetSit();
	//}
	////	2:�ȱ�
	//else if( info->Effect == 2 )
	//{
	//	if( pPt.x != crdCell.x || pPt.y != crdCell.y )
	//	{
	//		m_bMainChar_WalkRun_Sw = HT_TRUE;
	//		this->HT_vMainChar_SetMoveType();
	//		//	Move Action On/Off Check
	//		m_bMainChar_MoveSw = HT_FALSE;
	//		//	ĳ���� �̵� ����_�������Ͽ� Ÿ�� ����
	//		this->HT_vMainChar_SetTargetMovePosition( crdCell, HT_TRUE );
	//	}
	//}
	////	3:�ٱ�
	//else if( info->Effect == 3 )
	//{
	//	if( pPt.x != crdCell.x || pPt.y != crdCell.y )
	//	{
	//		m_bMainChar_WalkRun_Sw = HT_FALSE;
	//		this->HT_vMainChar_SetMoveType();
	//		//	Move Action On/Off Check
	//		m_bMainChar_MoveSw = HT_FALSE;
	//		//	ĳ���� �̵� ����_�������Ͽ� Ÿ�� ����
	//		this->HT_vMainChar_SetTargetMovePosition( crdCell, HT_TRUE );
	//	}
	//}
	//	4:����
	if( info->Effect == 4 )
	{
		//	hmm.....�ӽ÷� �ٱ���� ����
		m_bMainChar_WalkRun_Sw = HT_FALSE;
		this->HT_vMainChar_SetMoveType();
		//	Move Action On/Off Check
		m_bMainChar_MoveSw = HT_FALSE;
		//	ĳ���� �̵� ����_�������Ͽ� Ÿ�� ����
		this->HT_vMainChar_SetTargetMovePosition( crdCell, HT_TRUE );
		//	Ani Setting
		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
	}
	//	5:�ڷ���Ʈ
	else if( info->Effect == 5 )
	{
		//	Setting	Targetting
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();
		//	Move Action On/Off Check
		m_bMainChar_MoveSw = HT_TRUE;
		m_cMainCharMove->HT_vMainCharMove_NetWorkMoveFaild( info->TargetX, info->TargetY );
		//	��ġ�� ȸ�� ����
		this->HT_vMainChar_SetCharacterPosition( info->TargetX, info->TargetY, 1 );
		m_bMainChar_SitSw = HT_FALSE;
	}
	//	6:�и���(knock-back)
	else if( info->Effect == 6 )
	{
		//	�������̸� ���
		if( m_bMainChar_AttackSw )
			this->HT_vMainChar_SetAttackCancel( 20 );

		//	Move Action On/Off Check
		m_bMainChar_MoveSw = HT_FALSE;
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_HIT;
		this->HT_vMainChar_SetChangeAni( 0x01, 1, 0.0f, 0, 0 );
		m_cMainCharMove->HT_vMainCharMove_CheckTargetCell( vecTempPos, CHARACTER_SPEEDLEVEL_KNOCKBACK );

		//	������ ������ �ݴ�� �����ش�.
		HTfloat fCharAngle = m_cMainCharMove->HT_fGetDirect();
		if( fCharAngle > HT_PIX2 )
			fCharAngle -= HT_PI;
		else
			fCharAngle += HT_PI;
		m_cMainCharMove->HT_fSetDirect( fCharAngle );
	}
	//	7:�̲�������(�̵��ִϾ���)
	else if( info->Effect == 7 )
	{
		m_bMainChar_WalkRun_Sw = HT_FALSE;
		this->HT_vMainChar_SetMoveType();
		//	Move Action On/Off Check
		m_bMainChar_MoveSw = HT_FALSE;
		//	ĳ���� �̵� ����_�������Ͽ� Ÿ�� ����
		this->HT_vMainChar_SetTargetMovePosition( crdCell, HT_TRUE );
		//	Ani Setting
		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
	}
	//	8:����
	else if( info->Effect == 8 )
	{
		g_cCommand->HT_vCommand_Provoke();
	}
	//	9:�λ�
	else if( info->Effect == 9 )
	{
		g_cCommand->HT_vCommand_Greet();
	}
	//	10:����
	else if( info->Effect == 10 )
	{
		g_cCommand->HT_vCommand_Rush();
	}
	//	11:���ӵ� ����
	else if( info->Effect == 11 )
	{
		///	���� ���� �ε��� 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
		m_iMainChar_RealAttackIndex = 1;
		m_bMainChar_AttackSw = HT_FALSE;
		//	Move Action On/Off Check
		m_bMainChar_MoveSw = HT_FALSE;
		m_bMainChar_WalkRun_Sw = HT_FALSE;
		this->HT_vMainChar_SetMoveType();
		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_RUN;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		m_cMainCharMove->HT_vMainCharMove_CheckTargetCell( vecTempPos, CHARACTER_SPEEDLEVEL_ZUBAS );


		////	���� ���� �ε��� 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
		//m_iMainChar_RealAttackIndex = 1;
		////	�����ӵ��� �����ϰ� ���� �ӵ��� �Է��Ѵ�.
		//m_iMinaChar_TempSpeedForMSGAEffect = m_cMainCharMove->HT_iMainCharMove_GetSpeed( 0x02 );
		//m_cMainCharMove->HT_vSetMiddleMoveSpeed( 40 );

		//m_bMainChar_WalkRun_Sw = HT_FALSE;
		//this->HT_vMainChar_SetMoveType();
		////	Move Action On/Off Check
		//m_bMainChar_MoveSw = HT_FALSE;
		////	ĳ���� �̵� ����_�������Ͽ� Ÿ�� ����
		//this->HT_vMainChar_SetTargetMovePosition( crdCell, HT_TRUE );
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Char_MSG_Action MainChar Effect:%d", info->Effect );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid HTMainCharacter::HT_vMainChar_NetWorkDieMotion()
{
	//	����Ʈ ���ֱ�
	if( m_iMain_FaintingstateFX )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iMain_FaintingstateFX );
		m_iMain_FaintingstateFX = 0;
	}

	//	�� ����Ʈ�� ����
	g_pEngineHandler->HT_hrOffMouseWideEffect();

	m_bMainChar_AttackSw = HT_FALSE;
	m_bMainChar_Live = HT_FALSE;
	m_nMainChar_AniResentState	= CHARACTER_ANISTATE_DIE;
	this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );

	HTvector3 vecPos = HT_vecGetPosition();
	g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_DEATH, vecPos, 1, 0.9f);
	vecPos.x += 10;
	vecPos.y += 50;
	vecPos.z += 10;
	g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_DEATH, vecPos, 1, 0.9f);
}

//----------�������� ��Ŷ �����ޱ�-ĳ���� ����� �̴� ������û ���----------//
HTvoid HTMainCharacter::HT_vMainChar_SCP_INIT_REGEN_CHAR( HTint nX, HTint nZ )
{
	m_bMainChar_Live = HT_TRUE;
	m_bMainChar_SitSw = HT_FALSE;
	m_bMainChar_Reviving = HT_FALSE;	// �繫�ٹ� ��Ȱ��ų �������� ESCŰ�� ���� Ȯ��â�� �ߴ°� ���� ���� ����� �ɹ�����
	
	//----------ĳ������ �����̳� ��Ż �̵������� �ٲ� ĳ������ ��ġ ����----------//
	HT_vMainChar_SetCharacterPosition( nX, nZ, 0 );
}

//----------ĳ������ �����̳� ��Ż �̵������� �ٲ� ĳ������ ��ġ ����----------//
HTvoid HTMainCharacter::HT_vMainChar_SetCharacterPosition( HTint nX, HTint nZ, HTint iPosType )
{
	//---------ĳ���� ��ġ ����---------//
	HT_CELL_COORD crdCell;
	HTvector3 vecPos;
	crdCell.x = nX;
	crdCell.y = nZ; 
	g_pEngineHandler->HT_CELL_TO_3DCOORD( vecPos, crdCell );
	m_cMainCharMove->HT_vSetPosition( vecPos );
	m_cMainCharMove->HT_vSetCellPosition( nX, nZ );
	m_cMainCharMove->HT_vMainCharMove_StopMvoe();
	vecPos.y = g_pEngineHandler->HT_fGetTerrainHeight( vecPos.x, vecPos.z );
	g_pEngineHandler->HT_hrLoadMapObjsInitial( vecPos );
	
	HTvector3 vecTemp = m_cMainCharMove->HT_vecGetPosition();
	g_pEngineHandler->HT_hrMoveObject( m_iMainChar_ModelID, vecTemp );

	//if (g_pEngineHandler->HT_bGetIndicatedArea(m_iPrevArea, m_iArea, m_strAreaName))
	m_iArea = g_pEngineHandler->HT_iGetAreaID();
	m_iPrevArea = g_pEngineHandler->HT_iGetPrevAreaID();
	if ( g_pParamMgr->HT_bGetAreaName(m_iPrevArea, m_iArea, &m_strAreaName) )
	{	
		this->HT_vShowArea();
	}

	if (m_bAreaIndicated)
		this->HT_vUpdateAreaIndicate(0.0f);

	if( this->HT_nMainChar_GetResentHP() > 0 ||
		iPosType == 0 )
	{
		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );

		//	�������� ����Ʈ
		HTint idFx;
		g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWBORN, m_iMainChar_ModelID, HT_FALSE );
	}

	vecPos = HT_vecGetPosition();
	g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_CENTERCHARACTER, vecPos, 0, 0.0f );
	g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_CENTERCHARACTER, vecPos, 0, 0.0f );

	//	BGM ��Ʈ�� �Լ�
	HTint iMapID = g_wResentZoneServerID + ZONEVALUE_CLIENT_SERVER;
	g_cMapInfo->HT_vBGMControl( iMapID );
}

//	ĳ���Ͱ� �ʿ� �������� ����������
HTvoid HTMainCharacter::HT_vMainChar_EscapeCharacterFromNotMoveZone()
{
	if( g_iInationalType == INATIONALTYPE_JAPEN )
		return;

	//	���ݾ�!
    if( m_iMain_Affections & eTNVSAfn_Stun || 
		m_iMain_Affections & eTNVSAfn_Sleep ||
		m_iMain_Affections & eTNVSAfn_Hold )
		return;

	HTvector3 vecPos = m_cMainCharMove->HT_vecGetPosition();

	HTint iCount = 0;

	while(1)
	{
		//	��üũ
		if( HT_SUCCEED( m_cMainCharMove->HT_hrMainCharMove_CanPos( HTvector3( vecPos.x+(iCount*MAP_CELL_SIZE), vecPos.y, vecPos.z ) ) ) )
		{
			iCount++;
			vecPos.x += (iCount*MAP_CELL_SIZE);
			break;
		}
		//	��üũ
		if( HT_SUCCEED( m_cMainCharMove->HT_hrMainCharMove_CanPos( HTvector3( vecPos.x-(iCount*MAP_CELL_SIZE), vecPos.y, vecPos.z ) ) ) )
		{
			iCount++;
			vecPos.x -= (iCount*MAP_CELL_SIZE);
			break;
		}
		//	��üũ
		if( HT_SUCCEED( m_cMainCharMove->HT_hrMainCharMove_CanPos( HTvector3( vecPos.x, vecPos.y, vecPos.z+(iCount*MAP_CELL_SIZE) ) ) ) )
		{
			iCount++;
			vecPos.z += (iCount*MAP_CELL_SIZE);
			break;
		}
		//	��üũ
		if( HT_SUCCEED( m_cMainCharMove->HT_hrMainCharMove_CanPos( HTvector3( vecPos.x, vecPos.y, vecPos.z-(iCount*MAP_CELL_SIZE) ) ) ) )
		{
			iCount++;
			vecPos.z -= (iCount*MAP_CELL_SIZE);
			break;
		}
		iCount++;
	}

	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( vecPos, crdCell );
	MSG_GMMovePosition* info = HT_NULL;
	info = new MSG_GMMovePosition;
	info->snX = crdCell.x;
	info->snZ = crdCell.y;
	g_pNetWorkMgr->RequestGMMovePosition( info );
	HT_DELETE( info );
}

//	0x20 Group ? Skill
//	Unit Skill Start Brodcast
HTvoid HTMainCharacter::HT_vMainChar_CSP_UnitSkill_Start( DWORD dwSkillID, DWORD dwTargetKeyID, HTvector3 vecTargetPos, BYTE bySkillType )
{
	//	�� ��ġ
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( vecTargetPos, crdCell );
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();

	PS_CSP_CAST_UNIT_SKILL info = HT_NULL;
	info = new S_CSP_CAST_UNIT_SKILL;
    info->snRes = -1;
	info->snSkillID = (short)dwSkillID;
	info->snCasterKeyID = m_iMainChar_KeyID;
	info->kTarget.snKeyID = (short)dwTargetKeyID;
	info->snCasterX = (short)pPt.x;
	info->snCasterZ = (short)pPt.y;
	info->snMapX = crdCell.x;
	info->snMapZ = crdCell.y;

	g_pNetWorkMgr->RequestSkillCastUnitSkill( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Skill_Ready_Start" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );
}

//	Area Skill Start Brodcast
HTvoid HTMainCharacter::HT_vMainChar_CSP_AreaSkill_Start( DWORD dwSkillID, DWORD dwTargetKeyID, HTvector3 vecTargetPos, BYTE bySkillType )
{
	//	�� ��ġ
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( vecTargetPos, crdCell );
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();

	PS_CSP_CAST_AREA_SKILL info = HT_NULL;
	info = new S_CSP_CAST_AREA_SKILL;
	ZeroMemory( info, sizeof(S_CSP_CAST_AREA_SKILL) );
    info->snRes = -1;
	info->snSkillID = (short)dwSkillID;
	info->snCasterKeyID = m_iMainChar_KeyID;
	info->krgTarget[0].snKeyID = (short)dwTargetKeyID;
	info->snCasterX = (short)pPt.x;
	info->snCasterZ = (short)pPt.y;
	info->snMapX = crdCell.x;
	info->snMapZ = crdCell.y;

	g_pNetWorkMgr->RequestSkillCastAreaSkill( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Skill_Ready_Start" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );
}

//	������ ��Ƽ�� ��ų(�ܼ�) ���� ��û
HTvoid HTMainCharacter::HT_vMainChar_CSP_Cast_Unit_Cast()
{
	//	�� ��ġ
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();

	PS_CSP_CAST_UNIT_SKILL info = HT_NULL;
    info = new S_CSP_CAST_UNIT_SKILL;
	memset( info, 0, sizeof(PS_CSP_CAST_UNIT_SKILL) );

	info->snRes = 0;
	info->snSkillID			= (short)m_dwMainChar_ActiveSkillCurIndex;		// cast�� skill ID		
	info->snCasterKeyID		= m_iMainChar_KeyID;					// Caster handle
	info->kTarget.snKeyID	= m_iMainChar_KeyID;					// Target handle
	info->snCasterX			= pPt.x;
	info->snCasterZ			= pPt.y;
	info->snMapX			= pPt.x;
	info->snMapZ			= pPt.y;
	info->snPackCount		= -1;
	g_pNetWorkMgr->RequestSkillCastUnitSkill( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Skill_Cast_Unit_Skill" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	������ ��Ƽ�� ��ų(����) ���� ��û
HTvoid HTMainCharacter::HT_vMainChar_CSP_Cast_Area_Cast()
{
	//	�� ��ġ
    HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
	HTint	iElement[TN_MAX_TARGET_COUNT];
	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
		iElement[i] = 0;

	//	������ ���ؿ���
	HTint iAOE;
	g_pParamMgr->HT_bGetPCSkillAreaOfEffect( m_dwMainChar_ActiveSkillCurIndex, m_byMainChar_ActiveSkillCurLevel, &iAOE );

	//	��Ƽ ��ų�϶��� ��Ƽ�� ���̵� �־��ش�.
	if( m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOPARTY )
	{
		g_cParty->HT_vParty_GetPartyMemberKeyID( iElement, (HTfloat)(iAOE*MAP_CELL_SIZE) );
	}
	//	�Ϲ� �����϶��� �������� ������Ʈ�� ���̵� �־��ش�.
	else
	{
		//	�ش� OtherObject���� ���ؿ���
		HTbyte byGoodType;
		g_pParamMgr->HT_bGetPCSkillType( m_dwMainChar_ActiveSkillCurIndex, 1, &byGoodType );
		g_cOtherObjectSystem->HT_vOtherObjectSystem_GetTerritoryArea( m_cMainCharMove->HT_vecGetPosition(), (HTfloat)(iAOE*MAP_CELL_SIZE), m_dwMainChar_ActiveSkillCurIndex, m_iMainChar_ModelID, m_iMainChar_KeyID, byGoodType, iElement );
	}

	PS_CSP_CAST_AREA_SKILL info = HT_NULL;
    info = new S_CSP_CAST_AREA_SKILL;

    memset( info, 0, sizeof(S_CSP_CAST_AREA_SKILL) );

	info->snRes = 0;
	info->snSkillID			= (short)m_dwMainChar_ActiveSkillCurIndex;		// cast�� skill ID		
	info->snCasterKeyID		= m_iMainChar_KeyID;					// Caster handle
	info->snCasterX			= pPt.x;								// Caster�� ���� x ��ǥ
	info->snCasterZ			= pPt.y;								// Caster�� ���� y ��ǥ
	info->snMapX			= pPt.x;								// Map�� ���� x ��ǥ
	info->snMapZ			= pPt.y;								// Map�� ���� y ��ǥ

	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
	{
        info->krgTarget[i].snKeyID = iElement[i];
	}

	g_pNetWorkMgr->RequestSkillCastAreaSkill( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Skill_Cast_Area_Skill:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
	//	info->krgTarget[0].snKeyID, info->krgTarget[1].snKeyID, info->krgTarget[2].snKeyID, info->krgTarget[3].snKeyID, info->krgTarget[4].snKeyID,
	//	info->krgTarget[5].snKeyID, info->krgTarget[6].snKeyID, info->krgTarget[7].snKeyID, info->krgTarget[8].snKeyID, info->krgTarget[9].snKeyID,
	//	info->krgTarget[10].snKeyID, info->krgTarget[11].snKeyID, info->krgTarget[12].snKeyID, info->krgTarget[13].snKeyID, info->krgTarget[14].snKeyID,
	//	info->krgTarget[15].snKeyID );
	//HT_g_vLogFile( g_DebugingFont[g_DebugingFont_Count-1] );
	//HT_g_vLogFile( "\n" );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	�������� ĳ��Ʈ��ų(�ܼ�) ������ �˷���
HTvoid HTMainCharacter::HT_vMainChar_SCP_Skill_CastSkill_Broadcast( PS_CSP_CAST_UNIT_SKILL info )
{
	if( info->snRes != 0 )
		return;

	HTvector3 vecTargetPos;
	vecTargetPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( info->kTarget.snKeyID );

	//	Ŀ��Ƽ�����϶� ����Ʈ
	if( info->kTarget.byRes == 1 )
	{
		HTint iTargetModelID = 0;
		iTargetModelID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( info->kTarget.snKeyID );
		HTint idFx;
		g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_CRITICALIMPACT, iTargetModelID, HT_FALSE );
	}
	//	��Ƽ�� ���н� �޽��� ����� ����
	else if( info->kTarget.byRes == 102 )
	{
		//	���̾� �޽��� �߰���.
		CHTString strMsg;
		strMsg = _T("��Ÿ�� ���ѿ� ���� ���� �����߽��ϴ�.");
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
		return;
	}

	//	0:���۰�, 1:������
	HTbyte bySkillType = 0;
	if( info->snSkillID )
	{
		g_pParamMgr->HT_bGetPCSkillType( info->snSkillID, 1, &bySkillType );

		//	���ǽ�ų ����
        if( info->dwDurationTime && 
			bySkillType == 1 && 
			m_iMainChar_KeyID == info->kTarget.snKeyID )
		{
			g_pMainBar->HT_vMainBar_SetMySkill( info->snSkillID, 1, info->bySkillLevel );
		}
	}

	if( !g_bGamePlayMovieForGlobal )
	{
		if( bySkillType == 0 )
		{
            g_cHitCountMgr->HT_vHitCountMgr_Create( 0, info->kTarget.byRes, info->kTarget.iDamage, vecTargetPos, 0, HT_FALSE );
		}
	}

	//	���� / �޽��� ����
	if( info->kTarget.snKeyID != m_iMainChar_KeyID &&
		bySkillType == 0 )
	{
		//	Hit Message Set
		CHTString strMsg;
		if( info->kTarget.byRes == 0 ||
			info->kTarget.byRes == 1 )
		{
			//char* szName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->kTarget.snKeyID );
            // %s���� ������ %d�� �������ϴ�.", szName,  info->kTarget.iDamage
			m_iMessageVal = info->kTarget.iDamage;
			m_szEnemyName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->kTarget.snKeyID );
			HT_vMainChar_SetMessage( eMsgAttackSendDamage, &strMsg );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strMsg );
		}
		//	ȸ�� �޽���
		else if( info->kTarget.byRes == 2 )
		{
			//char* szName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->kTarget.snKeyID );
			m_szEnemyName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->kTarget.snKeyID );
			// %s�� ������ ���߽��ϴ�.", szName 
			HT_vMainChar_SetMessage( eMsgAttackEnemyDodge, &strMsg );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
		}
	}
	
	//	ȭ���϶� �ټ� ī�������ֱ� - 0�̸� �������
	if( info->snPackCount != -1 )
	{
		if( m_bMainChar_ItemArrow )
		{
			HTdword dwItemKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND );
			g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( dwItemKeyID, (HTbyte)info->snPackCount );
			if( info->snPackCount == 0 )
			{
				// ������ �ε����� ���� �������� ����� ���� ���Ѵ�.
				HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
				// ��� ����� ȭ�� ������ �����
				g_cItemSystem->HT_vItemSystem_DeleteItem( dwItemKeyID );

				// ȭ�� �ڵ� ä���
				if( g_cItemControl->HT_bItemControl_RefillArrow( dwItemKeyID, dwItemIndex ) == HT_FALSE )
				{
					this->HT_vMainChar_SetAttackCancel( 21 ); // ���ݻ��� ���
					// ���ʿ� ��վ����� ��Ʈ�� �׸���
					g_cEquipInventory->HT_vEquipInventory_SetLeftItem( 0 );

					DWORD dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
					if( dwKeyID > 0 )
					{
						DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
						if( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( dwIndex )	|| CHTParamIDCheck::HT_bIsItemWeaponThrow( dwIndex ) )
						{
							// �̹��� �׸���
							// ����� �׸���
						}
					} // end of if( dwKeyID > 0 )
				}
			}
		}
	}

	if( info->kTarget.iHP <= 0 )
	{
		this->HT_vMainChar_SetAttackCancel( 23 );
		//	Ÿ�R�� �ʱ�ȭ
		m_iMainChar_Target_KeyID = 0;
		//	�ֽ����������� ������� ������ ���Ͽ� "XX�� XX���� �¸��Ͽ����ϴ�."
		if( SERVEROBJECT_IS_CHARACTER( info->kTarget.snKeyID ) )
		{
			if( HT_FAILED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) &&
				HT_FAILED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
			{
				if( g_cStatus->HT_iGetKarmaPoint() == 0 &&
					g_pDuelSystem->HT_byDuel_GetDuelMode() != eChallenge_Combat )
				{
					// ī���� ����Ʈ�� ���ַ��� �ڽź��� ���� ���͸� ����ؾ� �մϴ�.
					if (g_iInationalType != INATIONALTYPE_KOREA)
					{
						//	����â ��
						g_pNotifyWindow->HT_vNotify_SetOn();
						CHTString strMessage;

						HT_vMainChar_SetMessage( eMsgCharacterCarmaUp, &strMessage );
						g_pNotifyWindow->HT_vNotify_SetText( strMessage.HT_szGetString() );
					}
					else
					{
						//_DIALOG_PK_NOTICE PK �ȳ�
					}
				}
			}
		}
	}

	//	Cur TP������ �ֱ�
	g_pMainBar->HT_vMainBar_SetCurTP( info->iCasterTP, 0 );

	//	Ÿ�������ش�.
	 g_cOtherObjectSystem->HT_vOtherObjectSystem_SetAttackTargetting( info->kTarget.snKeyID );

	//	���� ����Ÿ�� �������ش�.
	// ���� info->iCasterAffection �߰� ����
	this->HT_nMainChar_SetCurHP( info->iCasterHP );
	g_pMainBar->HT_vMainBar_SetCurTP( info->iCasterTP, 0 );

	//	Ÿ���� ����Ÿ�� �������ش�.
	PS_SCP_RESP_UPDATE_STATUS pData = NULL;
	pData = new S_SCP_RESP_UPDATE_STATUS;
	pData->snKeyID = info->kTarget.snKeyID;
	pData->iHP = info->kTarget.iHP;
	pData->iAffections = info->kTarget.iAffection;
	pData->snKarma = g_cOtherObjectSystem->HT_vOtherObjectSystem_GetKarma( pData->snKeyID );
	if( pData->snKarma < 0 )	pData->snKarma = 0;
	g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkUpdateStatus( pData );
	HT_DELETE( pData );

	//	�о�� ��ų�̾�����쿡 ĳ���� �����ϱ�
	if( info->snSkillID == 3041 )
		this->HT_vMainChar_SetAttackCancel( 24 );
}

//	�������� ĳ��Ʈ��ų(����) ������ �˷���
HTvoid HTMainCharacter::HT_vMainChar_SCP_Skill_CastSkill_Broadcast( PS_CSP_CAST_AREA_SKILL info )
{
	if( info->snRes != 0 )
		return;
    
	//	Cur TP������ �ֱ�
	g_pMainBar->HT_vMainBar_SetCurTP( info->iCasterTP, 0 );

    HTvector3 vecTargetPos;
	PS_SCP_RESP_UPDATE_STATUS pData = NULL;
	pData = new S_SCP_RESP_UPDATE_STATUS;
	//	������ ��ǥ ���ͼ� HitCount �����ϱ�
	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; ++i )
	{
		CHTString strTemp;
		strTemp.HT_szFormat( "%d:%d:%d:%d,",i,info->krgTarget[i], info->krgTarget[i].byRes, info->krgTarget[i].iDamage );
		HT_g_vLogFile( strTemp.HT_szGetString() );

		//	������ �����ϰ� �������� �������� ����.
		//	����Ÿ�� �������ش�.
		if( info->krgTarget[i].snKeyID == m_iMainChar_KeyID )
		{
            this->HT_vMainCHar_SCP_SetAffections( info->krgTarget[i].iAffection );
			//	���ǽ�ų ����
			if( info->snSkillID )
			{
				//	0:���۰�, 1:������
				HTbyte bySkillType = 0;
				g_pParamMgr->HT_bGetPCSkillType( info->snSkillID, 1, &bySkillType );
				if( info->dwDurationTime && 
					bySkillType == 1 )
				{
					g_pMainBar->HT_vMainBar_SetMySkill( info->snSkillID, 1, info->bySkillLevel );
				}
			}
		}
		else if( info->krgTarget[i].snKeyID > 0 )
		{
			//if( info->krgTarget[i].snDamage > 0 )
			{
				//	Get OtherObject Pos
				vecTargetPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( info->krgTarget[i].snKeyID );
				if( !g_bGamePlayMovieForGlobal )
				{
					//	Set Hit Count
					if( info->krgTarget[0].snKeyID == info->krgTarget[i].snKeyID )
					{
						g_cHitCountMgr->HT_vHitCountMgr_Create( 0, info->krgTarget[i].byRes, info->krgTarget[i].iDamage, vecTargetPos, i, HT_TRUE );
					}
					else
					{
						g_cHitCountMgr->HT_vHitCountMgr_Create( 0, info->krgTarget[i].byRes, info->krgTarget[i].iDamage, vecTargetPos, 0, HT_FALSE );
					}
				}
				//	Set OtherObject Data
				if( !g_bGamePlayMovieForGlobal )
				{
					pData->snKeyID = info->krgTarget[i].snKeyID;
					pData->iHP = info->krgTarget[i].iHP;
					pData->iAffections = info->krgTarget[i].iAffection;
					pData->snKarma = g_cOtherObjectSystem->HT_vOtherObjectSystem_GetKarma( pData->snKeyID );
					if( pData->snKarma < 0 )		pData->snKarma = 0;
					g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkUpdateStatus( pData );
				}
			}
		}
	}
	HT_g_vLogFile( "\n" );
	HT_DELETE( pData );
}

//	Network_�Ҳɳ���
HTvoid HTMainCharacter::HT_vMainChar_SCP_FireFxBroadcast( PS_SCP_FIRE_FX_BROADCAST info )
{
	//	�Ҳɳ��� ����Ʈ
	HTint idFx;
	g_pEngineHandler->HT_hrStartSFX( &idFx, info->iFX, m_iMainChar_ModelID, HT_FALSE );
}

//	Set Item Effect
HTvoid HTMainCharacter::HT_vMainChar_SCP_SetItemEffect( HTint iItemID )
{
//	HTint idFX;
	//g_pParamMgr->HT_bGetItemFXEffectID( iItemID, &idFX );

//	HTint id;
//	if ( idFX ) g_pEngineHandler->HT_hrStartSFX( &id, idFX, m_iMainChar_ModelID, HT_FALSE );
}

//	����
//	1.�ɾ� �ִ� ���¿��� ��ų�� �����ϸ� �����ִϸ��̼��� ������ ������ �ٽ� �̵� ����� ������ ���� ����� ���´�.
HTvoid
HTMainCharacter::HT_vShowArea()
{
	m_bAreaIndicated = HT_TRUE;
	m_fIndicateTime = 0.0f;
}


HTvoid
HTMainCharacter::HT_vUpdateAreaIndicate(HTfloat fElapsedTime)
{
	if (m_fIndicateTime<_AREAINDICATE_TIME)	m_fIndicateTime += fElapsedTime;
	else
	{
		// ����ǥ��
		m_fIndicateTime = 0.0f;
		m_bAreaIndicated = HT_FALSE;
	}
}

//------- �޼��� ��� ----------//
HTvoid HTMainCharacter::HT_vMainChar_SetMessage( HTint idMessage, CHTString* pszMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	
	// ������ 3�� �� ��
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vMainChar_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vMainChar_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vMainChar_SetParamTextForMessage( sParam3, &szOut3 );

		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vMainChar_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vMainChar_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vMainChar_SetParamTextForMessage( sParam1, &szOut1 );
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pszMessage = szString;
}

HTvoid HTMainCharacter::HT_vMainChar_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		case eMsgParamMyName			: // �� �̸�
			*pszParam = g_oMainCharacterInfo.szCharName; 
			break;
		
		// ���� ��� �̸�
		case eMsgParamTargetEnemyName	:
		// ���� ������ ��� �̸�
		case eMsgParamEnemyName			: 
			*pszParam = m_szEnemyName; 
			break;

		// ���濡�� �� ������
		case eMsgParamSpendingDamage	:
		// ���� ���� ������
		case eMsgParamReceivedDamage	:
		// ���� ����
		case eMsgParamRecoveryPrana		: 
			pszParam->HT_szFormat("%d", m_iMessageVal ); 
			break;
		
			// �κ�Ȯ�� ����
		case eMsgParamLimitInvenDate	:
		{
			tm* psTmTime = localtime( &m_timeMainChar_TimeStamp[eTime_Inven] );
			pszParam->HT_szFormat("%d.%d.%d", psTmTime->tm_year+1900, psTmTime->tm_mon+1, psTmTime->tm_mday );
		}
			break;
		// ���λ��� ����
		case eMsgParamLimitPrivateShopDate :
		{
			tm* psTmTime = localtime( &m_timeMainChar_TimeStamp[eTime_Store] );
			pszParam->HT_szFormat("%d.%d.%d", psTmTime->tm_year+1900, psTmTime->tm_mon+1, psTmTime->tm_mday );
		}
			break;
		case eMsgParamUseShopDate : // ������
		{
			tm* psTmTime = localtime( &m_timeMainChar_TimeStamp[m_byTimeArrIndex] );
			
			pszParam->HT_szFormat("%4d.%2d.%2d / %2d:%02d", psTmTime->tm_year+1900, psTmTime->tm_mon+1, psTmTime->tm_mday, psTmTime->tm_hour, psTmTime->tm_min );
		}
		default:
			break;
	}
}