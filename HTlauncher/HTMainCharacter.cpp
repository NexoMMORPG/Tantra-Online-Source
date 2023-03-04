
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
	//	스킬 쿨타입 스위치
	m_iMainChar_ActiveSkillIndex = 0;
	//	MoveSystem
	m_cMainCharMove = HT_NULL;
	//	Affections 상태 FX
	m_iMain_FXAffections = -1;
	//	액티브 이펙트 켜야 될때_STATE_ONCE_TOME_PERATTACK, PERATTACKED
	m_iMain_ActiveImpactFXID = -1;
	//	Time Check For Skill
	m_bMainChar_TimeCheckForSkillStart = HT_TRUE;
	//	Clan Value
	m_byMainChar_Clan = 0;
}

HTMainCharacter::~HTMainCharacter()
{
}

//	모델 지우기
HTvoid HTMainCharacter::HT_vMainChar_CleanUp()
{
	//	공격 인자 생성
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

//	캐릭터 Model 생성
HTvoid HTMainCharacter::HT_vMainChar_Create()
{//fors_debug 맣긴훙膠芚謹뒈렘
	//	캐릭터 모델 생성                                       //g_oMainCharacterInfo.snTribe
	m_iMainChar_ModelID = g_pEngineHandler->HT_iCreateCharacter(g_oMainCharacterInfo.snTribe , m_cMainCharMove->HT_vecGetPosition(), g_oMainCharacterInfo.byHeadType, g_oMainCharacterInfo.byFaceType );
	g_pEngineHandler->HT_hrSetMainChar( m_iMainChar_ModelID );
	//	g_pEngineHandler->HT_hrRotateObject( m_iMainChar_ModelID, HT_PI );
	
	//	모델 사이즈
	m_fModelHeight = g_pEngineHandler->HT_fGetObjHeight( m_iMainChar_ModelID );

	//	캐릭터 방향,위치,애니매이션 셋팅
	g_pEngineHandler->HT_hrStartAnimation( m_iMainChar_ModelID, g_oMainCharacterInfo.snTribe, HT_ANISTATE_STD, -1 );

	//	지형 픽했을때 위치 잡아주는 모델
	m_nTrrainPick_ModelID	= g_pEngineHandler->HT_iCreateNullModel( HTvector3( 100, 100, 100 ) );
	m_bTrrainPick_LoopSw	= HT_FALSE;
	//	상점 모델
	if( m_timeMainChar_TimeStamp[eTime_Store] < 0 )	m_iMainChar_ShopCharID	= g_pEngineHandler->HT_iCreateMonster( 2482, HTvector3( 100, 100, 100 ) );
	else											m_iMainChar_ShopCharID	= g_pEngineHandler->HT_iCreateMonster( 2483, HTvector3( 100, 100, 100 ) );

	//	Init Map
	g_pEngineHandler->HT_hrLoadMapObjsInitial( m_cMainCharMove->HT_vecGetPosition() );

	//	NPC 생성
	g_sNPCSystem->HT_vNPCSystem_CreateNPC();
}

//	성별 변환을 위한 캐릭터 삭제/생성
HTvoid HTMainCharacter::HT_vMainChar_ChangeSexDelCre( HTshort snTribe, HTbyte byHeadType, HTbyte byFaceType )
{
	//	모델 섹제
	g_pEngineHandler->HT_vDestroyCharacter( m_iMainChar_ModelID, 9 );
	g_pEngineHandler->HT_vDestroyCharacter( m_iMainChar_ShopCharID, 9 );
	//	캐릭터 모델 생성
	m_iMainChar_ModelID = g_pEngineHandler->HT_iCreateCharacter( snTribe, m_cMainCharMove->HT_vecGetPosition(), byHeadType, byFaceType );
	g_pEngineHandler->HT_hrSetMainChar( m_iMainChar_ModelID );
	//	모델 사이즈
	m_fModelHeight = g_pEngineHandler->HT_fGetObjHeight( m_iMainChar_ModelID );
}

//	기본 데이타 셋팅_공격, 이동, 캐스팅
HTvoid HTMainCharacter::HT_vMainChar_BasicInfoSetting()
{
	//	공격 속도
	m_dwMainChar_AttackItemSpeed	= 0;
	m_dwMainChar_AttackItemSpeedUp	= 0;
	m_dwMainChar_AttackSkillActionSpeed	= 0;
	m_dwMainChar_AttackSkillActivateSpeed = 0;
	//	캐스팅 속도
	m_iMainChar_CastGaterTime = 0;
}

HTRESULT HTMainCharacter::HT_hrMainCharInitVariable()
{
	//	Char Cur HP
	m_iMainChar_MAX_HP = 0;
	m_iMainChar_Cur_HP = 0;

	//	프라나 초기화
	m_iMainChar_TotalPrana			= 0;
	//	OneClick 상태인지 체크
	m_iMainChar_OneClickIndex		= ATTACK_NONECLICK;
	//	F1~F10에 의한 스킬 공격 신호가 들어왔느냐?
	m_bMainChar_SetSkillAttackSw	= HT_FALSE;
	//	일반공격 없이 오직 스킬로만 하는 공격이냐?
	m_bMainChar_OnlySkillAttackSw	= HT_FALSE;
	//	퀵슬롯에서 넘어오는 스킬 번호
	m_bMainChar_ActionSkillIndex	= 0;
	//	패시브 시킬로 어드밴티지 돼는 사정거리
	m_iMainChar_PassiveSkillRange	= 0;
	//	토템 아이템에 의해 어드밴지지 되는 사정거리
	m_iMainChar_TotemItemRange = 0;
	//	캐스팅 시간
    m_dwMainChar_AttackSpeed = 0;
    
	m_bTrrainPick_LoopSw	= HT_FALSE;
	//	메인캐릭터 이동 클래스 초기화
	m_cMainCharMove = HT_NULL;
	m_cMainCharMove = new CHTMainCharMove;

	//	메인캐릭터의 공격변수들 초기화---------//
	m_iMainChar_MemoryTargetKeyID	= 0;
	m_nMainChar_AttackAnm			= 1;
	m_bMainChar_AttackSw			= HT_FALSE;
	m_bMainChar_AttackMoveSw		= HT_FALSE;
	m_dwMainChar_AttackStartTime	= GetTickCount();
	m_iMainChar_CastEffectID		= -1;
	//	실재 공격 인덱스 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	m_iMainChar_RealAttackIndex		= 1;
	m_bMainChar_MapPickAttackSw		= HT_FALSE;

	//	사정거리 셋팅
	m_byMainChar_AttackRange_Item			= 0;
	m_iMainChar_AttackRange_ActionSkill		= 0;
	m_byMainChar_AttackRange_ActivateSkill	= 0;

	//	공격 인자 생성
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

	//----------캐릭터 이동 관련----------//
	//-----캐릭터 걷기 뛰기 관련 셋팅-----//
	m_bMainChar_WalkRun_Sw	= HT_TRUE;			//	HT_FALSE:걷기, HT_TRUE:뛰기

	//----------캐릭터 앉기 관련----------//
	m_bMainChar_SitSw		= HT_FALSE;

	m_nMainChar_MoveStart			= 0;
	m_nMainChar_MoveResent			= 0;
	m_bMainChar_OneTimeRotate		= HT_FALSE;
	m_nMainChar_MovePathCount		= 0;

	//	맞는 동작을 할 수 있는 경우 체크
	m_bMainChar_HitEventCanSw		= HT_FALSE;

	//-----아이들 동작을 위해-----//
	m_dwMainChar_IdlTime			= 0;
    
	//-----화면이 하얗게 변하는 에러를 막는 변수-----//
	m_bMainChar_WhiteError			= HT_FALSE;

	m_bMainChar_ShowNameSw = HT_TRUE;

	//	10셀 이하의 거리를 체크할때
	m_bMainChar_MoveTargetCheckSw = HT_FALSE;
	//	Item이 활 일경우
	m_bMainChar_ItemArrow = HT_FALSE;
	//	기절상태 FX
	m_iMain_FaintingstateFX = 0;
	//	목표물에게 다가가기:HT_TRUE, 멀어지기:HT_FALSE
	m_bMainChar_GoTargetIndex = 0;
	//	몬스터의 SIZE 계산
	m_byMainCHer_TargetSize = 0;

	return HT_OK;
}

//---------서버에서 캐릭터 초기정보를 받는곳---------//
HTRESULT HTMainCharacter::HT_hrMainCharInit( HTint iKeyID, HTint iX, HTint iZ, DWORD dwGameTime, HTbyte byClan, HTdword dwTimeStamp[MAX_TIMEITEM] )
{
	m_bMainChar_Reviving = HT_FALSE;
	m_pMainChar_SaveMovePos.x = iX;
	m_pMainChar_SaveMovePos.y = iZ;
	//	Set Clan Value
	m_byMainChar_Clan = byClan;
	//	KeyID Setting
	m_iMainChar_KeyID = iKeyID;
	//	공격 대상 셋팅
	m_iMainChar_Target_KeyID = m_iMainChar_KeyID;
	//	Init 받는 동시에 캐릭터는 살아 숨쉰다.
	m_bMainChar_Live			= HT_TRUE;
	//	Move Action On/Off
	m_bMainChar_MoveSw			= HT_TRUE;
	//	기본 데이타 셋팅_공격, 이동, 캐스팅
	this->HT_vMainChar_BasicInfoSetting();
	//	왜 초기값이 6001 이 들어가는지 모르겠다. 한번 자세히 알아보자...!
	m_dwWearItemID = 6001;
	//	캐릭터 위치 방향 셋팅
	HT_CELL_COORD crdCell;
	HTvector3 vecPos;
	crdCell.x = iX;
	crdCell.y = iZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( vecPos, crdCell );
	vecPos.y = g_pEngineHandler->HT_fGetTerrainHeight( vecPos.x, vecPos.z );
	m_cMainCharMove->HT_vSetPosition( vecPos );
	m_cMainCharMove->HT_vSetCellPosition(iX, iZ);	//2003.1.8 선미 추가
	m_cMainCharMove->HT_fSetDirect( HT_PI );

	// 기능성 유료화 아이템 유효기간 초기화
	HT_vMainChar_InitTimeStamp( dwTimeStamp );
	
	//	캐릭터 생성
	this->HT_vMainChar_Create();

    //	엔진에 초기 시간설정 설정
	g_pEngineHandler->HT_hrSetInitTime( dwGameTime );

	//	시간 저장이 필요한 함수들을 위하여 서버에서 받은 시간을 저장하고 클라이언트의 현재 시간도 저장한다.
	g_tInitServerTime = (time_t)dwGameTime;
	time( &g_tInitClientTime );
	//	Set GM Mode
	//	투명 상태일때
	this->HT_vMainChar_SetTransparency( g_oMainCharacterInfo.byGMStatus, 0 );
	//	Chat Block check
	g_cChatting->HT_vChatting_SetChatBlock( g_oMainCharacterInfo.byGMStatus );

	//========================================================================
	//	퀘스트 히스토리정보 처리 시 버튼 깜박이지 않게 하기 위해서
	g_cQuest->HT_vQuest_SetIsInitChar(HT_TRUE);
	//	길드 시스템 초기화
	//g_cGuildSystem->HT_vGuild_Init();
	g_bTrimuritiShow = HT_TRUE;

	return HT_OK;
}

//----------최초 한번만 업데이트----------//
HTvoid HTMainCharacter::HT_vMainChar_OneTimeUpdate()
{
	m_bMouseLbuttonDownMove_Sw	= MOUSEBUTTONMOVE_STOP;
	m_cMainCharMove->HT_vMainCharMove_StopMvoe();

	m_nMainChar_AniResentState	= CHARACTER_ANISTATE_MAGIC_DEFENCE;
	m_bMainChar_AniEventCanSw	= HT_FALSE;
	m_bMainChar_AniStdCheckSw	= HT_FALSE;
	this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
	//-----아이들 동작을 위해-----//
	m_dwMainChar_IdlTime = GetTickCount();
	//-----앉기 동작을 위해-----//
	m_dwMainChar_sitTime = GetTickCount();

	//	생성시의 이펙트
	HTint idFx;
	g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWBORN, m_iMainChar_ModelID, HT_FALSE );

	//	이동시 회전처리
	m_fMainChar_ShowAngle = m_cMainCharMove->HT_fGetDirect();

	//	BGM 컨트롤 함수
	HTint iMapID = g_wResentZoneServerID + ZONEVALUE_CLIENT_SERVER;
	g_cMapInfo->HT_vBGMControl( iMapID );

	//-----액티브 스킬 초기화-----//
	m_iMainChar_ActiveSkillEffectID			= 0;					//	액티브 스킬 이펙트 ID
	m_iMainChar_ActiveSkill_StartTime		= GetTickCount();		//	액티브 스킬 이펙트 발동 시작 시간
	m_iMainChar_ActiveSkill_DurationTime	= 0;				//	액티브 스킬 캐스팅 시간
	
	//	서기 메시지를 서버에 보내기 - 최초 생성했을때 몬스터가 공격 안하는것을 방지하기 위해
	//	일단 뺌

	//	주신 마크 표현 하기 하기
	g_cGuildSystem->HT_vTrimutiri_MarkOn();
	//	타겥지정 FX
	m_iMain_TargettingFx = 0;
	//	목표물에게 다가가기 계산한 빈도수의 누적
	m_iMainChar_GoTargetAccumulationCount = 0;

	//	다른 캐릭이 보이지 않는 상태라면 공지한다.
	if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetShowCheck() == HT_FALSE )
	{
		g_pNotifyWindow->HT_vNotify_SetOn();
		g_pNotifyWindow->HT_vNotify_SetText( _T("현재 타 캐릭터 및 몬스터 HIDE 모드입니다.") );
	}

	//	재접속시에 이상하게 포커스를 잃어버리는것 같아 이코드를 삽입
	Sleep( 100 );
	SetFocus( g_hWnd );
}


HTvoid HTMainCharacter::HT_vMainChar_Control( HTfloat fElapsedTime )
{
	if( m_bMainChar_Live == HT_FALSE )
		return;

	//	캐릭터의 계산때 필요한 정보 계산
	this->HT_vCharGetInfomation();

	//	공격 컨트롤
	this->HT_vMainChar_AttackControl();

	//	캐릭터 각도 컨트롤
	this->HT_vMainChar_ControlAngle( fElapsedTime );

	//	캐릭터 무빙 및 업데이트 관련
	this->HT_vMainChar_ControlMove( fElapsedTime );

	//	캐릭터 정지한 상태를 체크하여 정지 애니매이션 셋팅
	this->HT_vMainChar_StopMoveCheck();

	//	마우스 LButtonDown일때
	this->HT_vMainChar_LButtonDown_Move();

	//	4_2. 애니매이션 온_애니매이션 포이트 체크
	this->m_vMainChar_AnmPointCheck();

	//	액티브 스킬 스케쥴러_StateEffect관리
	this->HT_vMainChar_ControlActiveSkill_ActivateAndState();
}

//	MouseLbuttonUp으로 들어오는 곳 byType 0x00:Map, 0x01:Item, 0x02:NPC, 0x03:공격이동
HTvoid HTMainCharacter::HT_vMainChar_MouseLButtonUpCheck( HT_CELL_COORD crdCell, HTbool bTargetEffectSw )
{
	//	죽었으면 리턴
	if( !m_bMainChar_Live )
		return;

	//	Move Action On/Off Check
	if( !m_bMainChar_MoveSw )
	{
		// 현재 이동할수 없는 상태입니다.
		CHTString szMessage;
		HT_g_Script_SetMessage( eMsgMoveCannotStatus, &szMessage, _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage );
		return;
	}

	//	사무다바 스킬을 사용한 상태라면 이동못하게 셋
	//if( g_cGameSystem->HT_bGameSystem_GetAskSamudaba() )
	//	return;

	//	이벤트 받지 못하는 애니매이션일경우 리턴
	if( !m_bMainChar_AniEventCanSw )
		return;

	//	범위 마법 설정
	if(	m_bMainChar_MapPickAttackSw )
	{
		//	픽위치를 계산하고
		g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecPickMapEffect, crdCell );
		//	맵 이펙트를 꺼고
		g_pEngineHandler->HT_hrOffMouseWideEffect();
		//	액션 스킬 셋팅_적용
		this->HT_vMainChar_SetActionSkillAffect();
		return;
	}

	//	캐릭터가 앉아 있다면...
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_SIT )
	{
		HT_vMainChar_SetSit();
		return;
	}

	//	공격 타입 None 로 셋팅
	m_nMainChar_Attack_Type = MAINCHAR_ATTACKTYPE_NONE;

	//	실재 공격 인덱스 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	m_iMainChar_RealAttackIndex = 1;

	//	캐릭터 이동 관련_맵픽을하여 타겥 지정
	this->HT_vMainChar_SetTargetMovePosition( crdCell, bTargetEffectSw );
}

//----------나 자신을 클릭했는지 판단----------//
HTRESULT HTMainCharacter::HT_vMainCharMyselfClick()
{
	//	공격중이었다면
	if( m_bMainChar_AttackSw )
		return HT_FAIL;

	//----------맵위의 픽업된 아이템 초기화 및 아이템 정보창 초기화----------//
	g_cItemSystem->HT_vSystem_InitPickUpItemOnMap();
	//----------OtherObjectSystem 정보창 초기화---------//
	g_cOtherObjectSystem->HT_vOtherObjectSystem_HPWindowInit();
	//----------NPC 정보창 초기화---------//
	g_sNPCSystem->HT_vNPCSystem_HPWindowInit();

	//	범위 마법 설정
	if(	m_bMainChar_MapPickAttackSw )
	{
		m_bMainChar_MapPickAttackSw	= HT_FALSE;
		//	맵 이펙트를 꺼고
		g_pEngineHandler->HT_hrOffMouseWideEffect();
	}
	
	m_iMainChar_OneClickIndex = ATTACK_ONECLICK;
	 
	//	공격 대상 셋팅
	m_iMainChar_Target_KeyID = m_iMainChar_KeyID;
	//	Net_Req Assist
	g_cCommand->HT_vCommand_NetReqAssist( m_iMainChar_Target_KeyID );

	//	원클릭 셋팅
	m_iMainChar_OneClickIndex = ATTACK_ONECLICK;

	//	HP hp
	g_pMainBar->HT_vSetObjectTextDraw( g_oMainCharacterInfo.szCharName );
	g_pMainBar->HT_vSetObjectHPDraw( m_iMainChar_Cur_HP, m_iMainChar_MAX_HP );

	if( m_iMain_TargettingFx == 0 )
        g_pEngineHandler->HT_hrStartSFX( &m_iMain_TargettingFx, HT_FX_NPCTARGETING, m_iMainChar_ModelID, HT_TRUE );

	return HT_OK;
}

//	나 자신의 클릭 해제
HTvoid HTMainCharacter::HT_vMainCharMyselfUndoClick()
{
	if( m_iMain_TargettingFx )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iMain_TargettingFx );
		m_iMain_TargettingFx = 0;
	}
}

//----------캐릭터의 계산때 필요한 정보 계산----------//
HTvoid HTMainCharacter::HT_vCharGetInfomation()
{
	m_cMainCharMove->HT_vMainCharMove_CellPositionCheck();
}

//	캐릭터 애니매이션 셋팅 byType 0x00:애니매이션 테이블을 이용, 0x01:실제 코드 삽입
HTvoid HTMainCharacter::HT_vMainChar_SetChangeAni( BYTE byAniTable, HTint loop, HTfloat fTime, DWORD dwSkillIndex, HTint iAttackAniCount )
{
	// bIsWeaponBack이 TRUE인 경우 현재 장착 중인 무기를 등에 붙이고 스킬 애니메이션을 시전해야 한다.
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
		//	무조건 등에 무기를 차고 애니매이션 해야될때
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

	//	안전지역에서만 등에 무기를 차야될때
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

	//	애니매이션 도중 다른이벤트를 받을것인지 체크
    m_bMainChar_AniEventCanSw = HT_TRUE;
	//	스탠딩 애니매이션을 위한 체크
	m_bMainChar_AniStdCheckSw = HT_FALSE;
	//	맞는 동작을 할 수 있는 경우 체크
	m_bMainChar_HitEventCanSw = HT_FALSE;
    //	아이들 동작을 위해
	m_dwMainChar_IdlTime = GetTickCount();

	//	애니매이션 셋팅
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
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	액티브 스킬 지전중이면...
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
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	액티브 스킬 지전중이면...
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
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	액티브 스킬 지전중이면...
			{
                if(HT_SUCCEED( g_pEngineHandler->HT_hrChangeSkillActiveAnimation( m_iMainChar_ModelID, dwSkillIndex, HT_SKILLANISEQ_ACTIVATE, 
							(HTdword)g_oMainCharacterInfo.snTribe,  0, g_oMainCharacterInfo.byHeadType, fTime )))
				{
					//	마야트3030 사누타3159 아킬라3160일 경우에는 임시로 잠시 제외한다.
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

	// 메인/서브 제련이 되어 있는 (무기) 아이템의 FX 설정
	this->HT_vMainChar_AttachRefineEffect( );
}

//--------- 장착한 무기 아이템의 제련에 따른 이펙트 설정 ----------//
HTvoid HTMainCharacter::HT_vMainChar_AttachRefineEffect( )
{
	HTdword dwItemKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
	if( dwItemKeyID <= 0 )
		return;

	// 메인 제련이 되어 있는 (무기) 아이템의 FX 설정
	DWORD dwWeponIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	HTbyte byMainRefineLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( dwItemKeyID );
	if( byMainRefineLevel > 0 )
	{
		g_pEngineHandler->HT_hrAttachItemMainRefineEffect( m_iMainChar_ModelID, dwWeponIndex, byMainRefineLevel );
	}
	// 속성 제련 되어 있는 (무기) 아이템의 경우
	HTint iSubRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( dwItemKeyID );
	if( iSubRefineLevel > 0 )
	{
		HTint iAttribute = g_cItemSystem->HT_iItemSystem_GetAttributeSubRefineItem( dwItemKeyID );
		// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
		g_pEngineHandler->HT_hrAttachItemSubRefineEffect( m_iMainChar_ModelID, dwWeponIndex,
															(HTESubRefineType)iAttribute, iSubRefineLevel );
	}
}

//     애니매이션 온_애니매이션 포이트 체크
HTvoid HTMainCharacter::m_vMainChar_AnmPointCheck()
{
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_DIE )
		return;

	HT_ANIMSTATE sAnmState = g_pEngineHandler->HT_eGetAnimState( m_iMainChar_ModelID );

	//	캐릭터 전투 중일때
	if( m_bMainChar_AttackSw == HT_TRUE )
	{
		//----------애니매이션 공격 포인트에서 하는일----------//
		if( sAnmState == HT_AS_ATTACK )
		{
			//	캐스트 스킬이 발동시작부터 공격 시작까지를 판단
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
	//	캐릭터 전투중 아닐때
	else
	{
		//	모든 애니매이션이 정지했을때는 스탠딩 자세로 돌아가되 앉기, 서기를 했을시는 다른 로직으로 이동한다.
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
				//	Ready Cast 액션이 아닐때만 스탠딩 상태로 돌아간다.
				if( m_nMainChar_AniResentState != CHARACTER_ANISTATE_SKILLREADY &&
					m_nMainChar_AniResentState != CHARACTER_ANISTATE_SKILLCAST )
				{
					m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
					this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
				}
			}

			//	아이들 동작을 위해
			m_dwMainChar_IdlTime = GetTickCount();
		}
	}
}

//----------캐릭터 공격 관련----------//
//----------캐릭터 공격 셋팅----------//
HTvoid HTMainCharacter::HT_vMainChar_SetAttackStatus( DWORD dwTargetKeyID, HTint iModelID, HTbool bForAttack )
{
	//	다른 캐릭이 보이지 않는 상태라면 스킵
	if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetShowCheck() == HT_FALSE )
		return;

	if( this->HT_bMainChar_GetSitStatus() )			return;

	//	Command 에서 공격명령 들어왔을때 처리
	if( dwTargetKeyID == -1 )
	{
		dwTargetKeyID = m_iMainChar_Target_KeyID;
		iModelID = m_nMainChar_TargetModelID;
	}

	//	범위 마법 설정
	if(	m_bMainChar_MapPickAttackSw )
	{
		//	픽위치를 계산하고
		if( dwTargetKeyID == m_iMainChar_KeyID )
			m_vecPickMapEffect = m_cMainCharMove->HT_vecGetPosition();
		else
			m_vecPickMapEffect = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( dwTargetKeyID );
			

		//	맵 이펙트를 꺼고
		g_pEngineHandler->HT_hrOffMouseWideEffect();
		//	액션 스킬 셋팅_적용
		this->HT_vMainChar_SetActionSkillAffect();
		return;
	}

	//	나자신을 찍으면 Skip
	if( m_iMainChar_KeyID == dwTargetKeyID )
		return;

	//	공격중에 다른애를 찍으면 공격 Skip
	if( dwTargetKeyID != m_iMainChar_Target_KeyID )
	{
		this->HT_vMainChar_SetAttackCancel( 3 );
	}
	//	같은애를 찍었을때는 공격중이라면 스킵
	else
	{
		//	이미 전투중이었다면 공격 스킵
		if( m_iMainChar_RealAttackIndex != 1 )
			return;
	}

	//	활일때는 왼손에 활이 있어야 공격 할수 있다.
	HTint iItemID = (HTint)g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND ) );
	if( CHTParamIDCheck::HT_bIsItemWeaponThrow( iItemID ) )
	{
		iItemID = (HTint)(HTint)g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND ) );
		if( !CHTParamIDCheck::HT_bIsItemUsableArrow( iItemID ) )
			return;
	}

	//	공격 대상 키아이디 셋팅
	if( dwTargetKeyID == m_iMainChar_Target_KeyID )
		m_iMainChar_OneClickIndex = ATTACK_ONECLICK;
	else
        m_iMainChar_Target_KeyID = dwTargetKeyID;
	//	Net_Req Assist
	g_cCommand->HT_vCommand_NetReqAssist( m_iMainChar_Target_KeyID );

	//	커맨드 창에 셋팅
	g_cCommand->HT_vCommand_SetBeforeTargetID( m_iMainChar_Target_KeyID );

	//	안전지역에서는 스킬 시전 못한다.
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
	if( g_pEngineHandler->HT_bIsCellSafeZone( pPt.x, pPt.y, 0 ) )
		return;

	//	같은 파티일때도 공격 스킵
	if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetParty( dwTargetKeyID ) == 0x02 )
		return;

	//	공격 대상의 모델 아이디
	m_nMainChar_TargetModelID = iModelID;
	//	일반공격 없이 오직 스킬로만 하는 공격이냐?
	m_bMainChar_OnlySkillAttackSw = HT_FALSE;
	//	데미지 최대값 초기화
	m_iMainChar_MaxDamage = 0;
	//	실재 공격 인덱스 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	m_iMainChar_RealAttackIndex = 1;
	

	//----------이펙트 살아 있음 스톱----------//
	if( m_bTrrainPick_LoopSw == HT_TRUE )
	{
		m_bTrrainPick_LoopSw = HT_FALSE;
		g_pEngineHandler->HT_hrStopSFX( m_nTrrainPick_EffectID );
	}

	//	OneClick 상태인지 체크
	if( m_iMainChar_OneClickIndex == ATTACK_NONECLICK )
	{
		m_iMainChar_OneClickIndex = ATTACK_ONECLICK;
		return;
	}
	else if( m_iMainChar_OneClickIndex == ATTACK_ONECLICK )
	{
		m_iMainChar_OneClickIndex = ATTACK_DOUBLECLICK;
	}

	//	공격 가능한 상태인지 체크한다.
	//if( HT_FAILED( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetCheckCanAttackTargetForNormal( (HTint)dwTargetKeyID, this->HT_ptMainChar_GetCellPosition() ) ) )
	//	return;

	if( g_cOtherObjectSystem->HT_hrOtherObjectSystem_GetTargetting( (HTint)dwTargetKeyID ) == HT_FALSE )
		return;

	if( bForAttack == HT_TRUE )
	{
		//	공격 셋팅
		m_bMainChar_AttackSw = HT_TRUE;

		//	목표물에게 다가가기:HT_TRUE, 멀어지기:HT_FALSE
		m_bMainChar_GoTargetIndex = 0;
		//	목표물에게 다가가기 계산한 빈도수
		m_iMainChar_GoTargetCount = 0;

		//	사정거리 결정
		this->HT_vMainChar_SetAttackRange();
		//	상대 좌표 추적
		this->HT_vMainChar_TargetPosCheck();


		//	이동 패킷 보내기 내 좌표를 보정하기 위함
		BYTE byMoveInfoState;
		if( m_bMainChar_WalkRun_Sw == HT_FALSE )
			byMoveInfoState = 2;
		else
			byMoveInfoState = 3;
		//	10셀 단위로 이동 좌표를 서버에 보내주기 위한 함수_실제 서버에 보내주기
		m_vecMainChar_MoveTargetPos = m_vecMainChar_TargetPos;
		HT_CELL_COORD codCell;
		g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecMainChar_MoveTargetPos, codCell );
		
		m_vecMainChar_ReqSendMovePos = HTvector3( 0, 0, 0 );
		this->HT_vNetWork_CheckCharMove();
	}
}

//----------캐릭터 공격 취소----------//
HTvoid HTMainCharacter::HT_vMainChar_SetAttackCancel( HTint iDebugIndex )
{
	m_iMainChar_MemoryTargetKeyID = 0;
	//	OneClick 상태인지 체크
	m_iMainChar_OneClickIndex = ATTACK_NONECLICK;
	//	퀵슬롯에서 넘어오는 스킬 번호
	m_bMainChar_ActionSkillIndex = 0;
	m_iMainChar_ReservedActionSkillIndex = 0;
	m_iMainChar_AttackRange_ActionSkill = 0;
	//	실재 공격 인덱스 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	m_iMainChar_RealAttackIndex = 1;
	//	캐스트 스킬 취소
	HT_vMainChar_SetCastCancel();
	//	이동이 있다면 취소
	m_bMainChar_AttackMoveSw = HT_FALSE;
	//	아이들 동작을 위해
	m_dwMainChar_IdlTime = GetTickCount();
	//	전투 취소
	m_bMainChar_AttackSw = HT_FALSE;
	//	맵픽을하여 공격하는것 초기
	m_bMainChar_MapPickAttackSw = HT_FALSE;
	//	공격 타입 None 로 셋팅
	m_nMainChar_Attack_Type = MAINCHAR_ATTACKTYPE_NONE;
	//	Time Check For Skill
	m_bMainChar_TimeCheckForSkillStart = HT_TRUE;
	//	목표물에게 다가가기 계산한 빈도수의 누적
	m_iMainChar_GoTargetAccumulationCount = 0;
}

//----------캐스트 스킬 취소----------//
HTvoid HTMainCharacter::HT_vMainChar_SetCastCancel()
{
	//	캐스트 이펙트가 있으면 정지 시키고
	if( m_iMainChar_CastEffectID != -1 )
	{
        g_pEngineHandler->HT_hrStopSFX( m_iMainChar_CastEffectID );
		m_iMainChar_CastEffectID = -1;
	}
}

//----------공격 컨트롤----------//
HTvoid HTMainCharacter::HT_vMainChar_AttackControl()
{
	if( m_bMainChar_AttackSw == HT_FALSE )
		return;

	//----------캐릭터가 앉아 있으면 서게 하고 일어서는 중이면 그냥 리턴----------//
	if( m_bMainChar_SitSw == HT_TRUE )
		HT_vMainChar_SetSit();
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_STANDUP )
		return;

	//	사정거리 체크해서 공격이동
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_STD ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_WLK ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_RUN ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_IDL )
	{
		//	사정거리 체크
		this->HT_vMainChar_AttackRangeCheck();
		//	공격을 위해 움직이기
		if( m_bMainChar_AttackMoveSw == HT_TRUE )
		{
			this->HT_vMainChar_AttackMove();
		}
	}

	//	캐릭터 공격_액션 컨트롤
	if( m_bMainChar_AttackMoveSw == HT_FALSE )
	{
		this->HT_vMainChar_RealAttackControl();
	}
}


//	내가 지금 일반공격인지 스킬공격인지 판단, 캐스팅 시간도 파악
HTvoid HTMainCharacter::HT_vMainChar_AttackTypeAndCastTimeCheck()
{
    if( m_bMainChar_SetSkillAttackSw &&					//	F1~F10에 의한 스킬 공격 신호가 들어왔느냐?
		m_iMainChar_ReservedActionSkillIndex != 0 )		//	액션 스킬 인덱스에 값이 있느냐?
	{
		m_bMainChar_SetSkillAttackSw = HT_FALSE;
		m_bMainChar_ActionSkillIndex = m_iMainChar_ReservedActionSkillIndex;
		//	무조건 스킬 공격
		m_nMainChar_Attack_Type = MAINCHAR_ATTACKTYPE_SKILL;
		//	캐스팅 시간
	    m_dwMainChar_AttackSpeed = m_iMainChar_CastGaterTime_ActionSkill;
	}
	else
	{
		m_nMainChar_Attack_Type = MAINCHAR_ATTACKTYPE_AUTOATTACK;
		
		//	공격 속도
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

	//	에러 체크
	if( m_dwMainChar_AttackSpeed < 500 )
		m_dwMainChar_AttackSpeed = 500;

	//	사정거리 결정
	this->HT_vMainChar_SetAttackRange();
}

//	상대 좌표 추적
HTvoid HTMainCharacter::HT_vMainChar_TargetPosCheck()
{
	//	맵픽공격인지 체크
	if( !m_bMainChar_MapPickAttackSw )
	{
		//	공격 대상의 좌표
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

	//	값이 들오오지 않으면 들어오염 공격 취소
	if( m_pMainChar_TargetPos.x == 0 )
		this->HT_vMainChar_SetAttackCancel( 4 );
}

//	사정거리 계산
HTvoid HTMainCharacter::HT_vMainChar_SetAttackRange()
{
	//	화살일때
	if( m_bMainChar_ItemArrow )
	{
        HTint iArrowCount = g_cItemSystem->HT_iItemSystem_GetItemCount( g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND ) );
		if( iArrowCount == 0 )
		{
			this->HT_vMainChar_SetAttackCancel( 5 );
			return;
		}
	}

	//	사정거리 체크
	if( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_AUTOATTACK || m_bMainChar_ItemArrow )
	{
		m_byMainChar_AttackRange = m_byMainChar_AttackRange_Item;
	}
	else
	{
		//	패시브 시킬로 어드밴티지 돼는 사정거리도 추가
		m_byMainChar_AttackRange = m_iMainChar_AttackRange_ActionSkill + m_iMainChar_PassiveSkillRange;
	}

	//	토템 아이템에 의해 어드밴지지 되는 사정거리 추가
	if( m_iMainChar_TotemItemRange > 0 )
	{
		//	장거리 액션스킬과 활공격일때만 적용
		//	액션 스킬 타입을 얻어온다.
		HTdword	dwActionSkillType = g_pEngineHandler->HT_dwGetSkillType( m_iMainChar_ReservedActionSkillIndex );
		if( ( dwActionSkillType != 0 &&
			  dwActionSkillType != HT_PCSKILLTYPE_ACTION_SHORT ) ||
			  m_bMainChar_ItemArrow )
		{
			m_byMainChar_AttackRange += m_iMainChar_TotemItemRange;
		}
	}

	//	에러체크
	if( m_byMainChar_AttackRange <= 0 )
		m_byMainChar_AttackRange = 1;

	//	몬스터의 SIZE 계산
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

//	사정거리 체크
HTvoid HTMainCharacter::HT_vMainChar_AttackRangeCheck()
{
	//	상대 좌표 추적
	this->HT_vMainChar_TargetPosCheck();
	//if( m_bMainChar_AttackSw == HT_FALSE )
	//	return;

	//	나자신을 클릭 했을때
	if( m_iMainChar_Target_KeyID == m_iMainChar_KeyID )
	{
		m_bMainChar_AttackMoveSw = HT_FALSE;
		return;
	}

	//	목표물에게 다가가기 계산한 빈도수
	if( m_iMainChar_GoTargetCount == 1 )
	{
		//	일단 정지로 셋팅 and skip
		m_bMainChar_AttackMoveSw = HT_FALSE;
		return;
	}

	//		1. 사정거리 계산
	//		2. 사정거리 이상이면 사정거리 안까지 뛰어감
	//		3. 사정거리 안이면 이동중이면 스톱
	HTvector3 vecMainCharPos = m_cMainCharMove->HT_vecGetPosition();
	HTint nRange = (HTint)HT_extern_fGetDisForTwoPoint( m_vecMainChar_TargetPos, vecMainCharPos );
	//	일단 이동으로 셋팅
	m_bMainChar_AttackMoveSw = HT_TRUE;
	//	몬스터 사이즈와 사정거리로로 접근 유형을 정한다.
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
		//	목표물에게 다가가기:1, 멀어지기:2
		m_bMainChar_GoTargetIndex = 1;
	}
	else if( nRange < (((m_byMainChar_AttackRange * MAP_CELL_SIZE)+5) - (m_iMainChar_GoTargetAccumulationCount*2)) )
	{
		if( m_bMainChar_GoTargetIndex == 1 || 
			!this->HT_bMainChar_GetMoveStopStatus() )	//	움직이지 못하는 상황이면 체크안함
		{
			m_iMainChar_GoTargetCount = 1;
			m_iMainChar_GoTargetAccumulationCount++;
			m_bMainChar_GoTargetIndex = 0;
			m_bMainChar_AttackMoveSw = HT_FALSE;
			return;
		}
        //	목표물에게 다가가기:1, 멀어지기:2
		m_bMainChar_GoTargetIndex = 2;
	}
	else
	{
		//	일단 정지로 셋팅 and skip
		m_bMainChar_AttackMoveSw = HT_FALSE;
		return;
	}

	//	혹시 무한으로 숫자가 가면 이상하잖아
	if( m_iMainChar_GoTargetAccumulationCount > 5 )
		m_iMainChar_GoTargetAccumulationCount = 5;

	//	각각의 이동유형에 맞게 범위 체크를 따로 한다.
	//	목표물에게 다가가기:1, 멀어지기:2
	//	접근 유형에 따라서
	if( m_bMainChar_GoTargetIndex == 1 )
	{
		if( m_byMainChar_AttackRange == 1 )
		{
			//	문 이딴것과의 충돌체크 때문에 어쩔수없이 이 코드가 들어감
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

	//	암살 스킬 '쥬바스'일때는 사정거리 밖에 있으면 취소
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

//----------공격을 위해 움직이기----------//
HTvoid HTMainCharacter::HT_vMainChar_AttackMove()
{
	//	캐스트 진행중인지 파악하고 진행중일때 셋팅해줘야 할것들
	if( m_iMainChar_CastEffectID != -1 )
	{
		//	캐스팅 이펙트 정지
		g_pEngineHandler->HT_hrStopSFX( m_iMainChar_CastEffectID );
		m_iMainChar_CastEffectID = -1;
	}

	//	뛰지 못하는 상태 체크
	if( !this->HT_bMainChar_GetMoveStopStatus() )
	{
		// 현재 이동할수 없는 상태입니다.
		CHTString szMessage;
		HT_g_Script_SetMessage( eMsgMoveCannotStatus, &szMessage, _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage );
		m_cMainCharMove->HT_vMainCharMove_StopMvoe();
		this->HT_vMainChar_SetAttackCancel( 6 );
		return;
	}

	//	걷기, 뛰기 Setting
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

	//	목표물에게 다가가기:HT_TRUE, 멀어지기:HT_FALSE
	HTvector3 vecTempPos;
	//	다가가기
	if( m_bMainChar_GoTargetIndex == 1 )
	{
		vecTempPos = m_vecMainChar_TargetPos;
	}
	//	멀어지기
	//	문제는 여기부터 이동하는데 멀어져아하기때문에 캐릭터-타겥의 백터값의 정확히 반대로 이동하면 타겥과 최단거리로 반대로 이동한다. 으하하하하하
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
		//	이동시스템에 셋팅
		m_cMainCharMove->HT_vMainCharMove_CheckTargetCell( vecTempPos, iMoveType );
		//	10셀 단위로 이동 좌표를 서버에 보내주기 위한 함수_실제 서버에 보내주기
		m_vecMainChar_MoveTargetPos = vecTempPos;
	}
}

//	걸치기를 막기위해 중간에 장애물이 있는지 검색
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

	//	최대 100번까지 이동불가지역이 있는지 계산한다.
	for( HTint i=0 ; i<iCheckCount ; ++i )
	{
		//	각도 계산
		fDirect = HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), (vecTargetPos-vecSourcePos) );

		fx = sinf( fDirect ) * ( MAP_CELL_SIZE/2 );
		fz = cosf( fDirect ) * ( MAP_CELL_SIZE/2 );
		vecSourcePos.x += fx;
		vecSourcePos.z += fz;

		//	이동가능지역인지 판단하여 불가지역이면 공격 실패_걸치기를 방지하기 위해
		if( g_pEngineHandler->HT_bCanMove( HT_OBJSIZE_SMALL, vecSourcePos, 0 ) == HT_FALSE )
		{
			//	1. NoMove 지역이지만 활을 사용할수 있는 지역
			if (!g_pEngineHandler->HT_bCanAttack( HT_OBJSIZE_SMALL, vecSourcePos, 0 ))
			{
				return HT_FAIL;
			}
			//	2. 내가 서있는곳이 몬스터 어택 불가능 지역이라면 몬스터 공격 불가
			//	이 코드의 위치를 적당한 곳에 배치
			//	HT_bMonAttackDisable
		}

		//	현재 위치 계산
		fDistance = HT_extern_fGetDisForTwoPoint( vecTargetPos, vecSourcePos );
		if( fDistance < MAP_CELL_SIZE )
			return HT_OK;
	}

	return HT_OK;
}

//----------캐릭터 공격 액션 컨트롤----------//
//	공격 시간 계산
HTvoid HTMainCharacter::HT_vMainChar_RealAttackControl()
{
	//	이동중이면 정지
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE )
	{
		m_cMainCharMove->HT_vMainCharMove_StopMvoe();
	}

	//	Attack Speed Control
	HTint iPassTime = GetTickCount();
	
	//	실재 공격 인덱스 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	switch( m_iMainChar_RealAttackIndex )
	{
		//	Ready Start일때
		case 1 :
			//	나의 상태가 스턴이나 슬립일경우는 공격 못함
			if( m_iMain_Affections & eTNVSAfn_Stun || 
				m_iMain_Affections & eTNVSAfn_Sleep )
			{
				this->HT_vMainChar_SetAttackCancel( 7 );
				return;
			}

			//	Attack 액션 들어가기전에 사정거리 체크
			//	사정거리 체크
			this->HT_vMainChar_AttackRangeCheck();
			if( m_bMainChar_AttackMoveSw == HT_FALSE )
			{
				//	상대가 살았는지 죽었는지 검사
				if( m_iMainChar_Target_KeyID				!= m_iMainChar_KeyID &&		//	메인 캐릭터가 아니고
					m_bMainChar_MapPickAttackSw				== HT_FALSE &&				//	맵픽 공격이 아니고
					m_iMainChar_ReservedActionSkillIndex	!= HT_SKILLINDEX_SAMUDABA )	//	부활 스킬이 아닐때
				{
					if( !g_cOtherObjectSystem->HT_bOtherObjectSystem_GetLiveFromKeyID(m_iMainChar_Target_KeyID) )
					{
						this->HT_vMainChar_SetAttackCancel( 8 );
						return;
					}
				}

				//	내가 지금 일반공격인지 스킬공격인지 판단, 캐스팅 시간도 파악
				this->HT_vMainChar_AttackTypeAndCastTimeCheck();

				//	걸치기를 막기위해 중간에 장애물이 있는지 검색
				if( HT_FAILED( this->HT_hrMainChar_ObstacleCenterCheck( m_cMainCharMove->HT_vecGetPosition(), m_vecMainChar_TargetPos ) ) )
				{
					CHTString szMessage;
					// 목표물을 공격 할 수 없는 위치에 있습니다.
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
					//	Ready 시간을 알아오고
					g_pParamMgr->HT_bGetPCSkillReadyTime( m_bMainChar_ActionSkillIndex, 1, &m_iMainChar_ReadyGaterTime );
					m_iMainChar_ReadyGaterTime += 100;

					//m_iMainChar_ReadyGaterTime =0; //fors_debug 꿎桿1MN槻벎 할늪변鑒옵鹿털뙤세콘蘆잚

					//	Skill Ready Ani Start
					m_nMainChar_AniResentState = CHARACTER_ANISTATE_SKILLREADY;
					this->HT_vMainChar_SetChangeAni( 0x01, 1, (HTfloat)((m_iMainChar_ReadyGaterTime+100)/1000.0f), m_bMainChar_ActionSkillIndex, 0 );
					//fors_debug readygatertime 駱聯寧늴
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

					//	액션 스킬 타입을 얻어온다.
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

					//	카메라가 회전
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
				//	캐릭터의 방향 공격방향쪽으로
				if( m_iMainChar_Target_KeyID != 0  &&
					m_iMainChar_Target_KeyID != m_iMainChar_KeyID )
				{
					m_cMainCharMove->HT_vSetAttackDirct( m_vecMainChar_TargetPos );
				}

				//	서버에 캐스트 스킬 패킷 보내기
				//	Unit_Skill
				if( !bAreaSkill )
                    this->HT_vMainChar_CSP_UnitSkill_Start( m_bMainChar_ActionSkillIndex, m_iMainChar_Target_KeyID, m_vecMainChar_TargetPos, 1 );
				//	Area_Skill
				else
					this->HT_vMainChar_CSP_AreaSkill_Start( m_bMainChar_ActionSkillIndex, 0, m_vecPickMapEffect, 1 ); 

				m_iMainChar_RealAttackIndex = 2;
			}
			break;
		//	Case Start일때
		case 2 :
			{
				if( iPassTime > m_iMainChar_ReadyStartTime + m_iMainChar_ReadyGaterTime ) 
				{
					//	캐스팅 시작 시간 저장
					m_iMainChar_CastStartTime = GetTickCount();
					m_iMainChar_CastGaterTime = 0;
					if( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_SKILL )
					{
						//	캐스팅 시간 구함
						g_pParamMgr->HT_bGetPCSkillCastingTime( m_bMainChar_ActionSkillIndex, 1, &m_iMainChar_CastGaterTime );
						//	캐스트 애니매이션이 없으면 스탠딩동작을 하려고 하기 때문에 약간 움찔한다.
						//	그 어색한 시간을 없애기 위해 나중에 스킬 캐스팅 애니가 있는지 없는지 알아오는 함수가 있으면 될듯하다. fors_debug 1mn
						//m_iMainChar_CastGaterTime = 0; 
						if( m_iMainChar_CastGaterTime > 0 )
						{
							//	Skill Cast Ani Start
							m_nMainChar_AniResentState	= CHARACTER_ANISTATE_SKILLCAST;
							this->HT_vMainChar_SetChangeAni( 0x01, -1, 0.0f, m_bMainChar_ActionSkillIndex, 0 );

							//fors_debug 疼駱聯寧늴
							//noneed
						}
						//	캐스팅 이펙트 시작
						g_pEngineHandler->HT_hrStartSFX( &m_iMainChar_CastEffectID, m_bMainChar_ActionSkillIndex, HT_SFX_WHEN_CAST, m_iMainChar_ModelID, HT_TRUE, 1 );
					}

					m_iMainChar_RealAttackIndex = 3;
				}
			}
			break;
		//	Apply Start일때
		case 3 :
			{
				if( iPassTime > m_iMainChar_CastStartTime + m_iMainChar_CastGaterTime )
				{
					//	캐스팅 이펙트 정지
					if( m_iMainChar_CastEffectID != -1 )
					{
						g_pEngineHandler->HT_hrStopSFX( m_iMainChar_CastEffectID );
						m_iMainChar_CastEffectID = -1;
					}

					//	만약에 등에 무기를 차고 있다면 풀어준다.
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
					//	공격 애니매이션을 틀어주고
					if ( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_AUTOATTACK )
					{
						m_iMainChar_ApplyGaterTime += 100;
						////	공격 속도
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

						//----------공격 애니매이션 교체----------//
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
						//	Apply 시간을 알아오고
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
					//----------공격 애니매이션이라고 셋팅해주고----------//
					m_nMainChar_AniResentState = CHARACTER_ANISTATE_NORMALATK;
					//	Attack Point 수행 여부
					m_bMainChar_AttackPointSw = HT_FALSE;

					//-----캐릭터의 방향 공격방향쪽으로-----//
					if( m_iMainChar_Target_KeyID != 0  &&
						m_iMainChar_Target_KeyID != m_iMainChar_KeyID )
					{
						m_cMainCharMove->HT_vSetAttackDirct( m_vecMainChar_TargetPos );
					}

					if( m_iMainChar_ApplyGaterTime <= 200 )
					{
						this->HT_vMainChar_AttackAnmAttackPoint();
					}
					//盧돕侶긋 fors_debug 세콘糠埼
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
		//	공격의 끝 계산
		case 4 :
			{
				if( iPassTime > m_iMainChar_ApplyStartTime + m_iMainChar_ApplyGaterTime )
				{
					//	Attack Point 수행 여부와 대쉬 명령 수행 여부에 따라서 마지막 콜을 한다.
					if( m_bMainChar_AttackPointSw )
					{
						//	공격 마시막 시점에서 무엇을 해야할저 결정
						this->HT_vMainChar_CheckAttackEnd();
					}
				}
			}
	}
}

//	공격 마시막 시점에서 무엇을 해야할저 결정
HTvoid HTMainCharacter::HT_vMainChar_CheckAttackEnd()
{
	//	스킬공격이었을때는 스킬 인덱스 초기화
	//	계속 공격해야 할 사항이면 공격하게 하고 장거리 스킬등과 같은 스킬이면 자동공격을 멈춘다.
	if( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_SKILL )
	{
		//	수가마 스킬일때는 무조건 공격 스킵
		if( m_bMainChar_ActionSkillIndex == 3333 )
		{
			//	공격 취소
			this->HT_vMainChar_SetAttackCancel( 10 );
			return;
		}

		//	0:나쁜것, 1:좋은것
		HTbyte bySkillGoodType;
        g_pParamMgr->HT_bGetPCSkillType( m_bMainChar_ActionSkillIndex, 1, &bySkillGoodType );
		HTdword dwActionSkillType = g_pEngineHandler->HT_dwGetSkillType( m_bMainChar_ActionSkillIndex );

		//	스킬 초기화
		m_bMainChar_ActionSkillIndex = 0;
		m_iMainChar_AttackRange_ActionSkill = 0;
		m_iMainChar_ReservedActionSkillIndex = 0;
		
		//	좋은 스킬을 썼을때
		if( bySkillGoodType )
		{
			//	공격을 캔슬해야 될 상황을 체크
			//	예약된 캐릭이 없을때
			if( m_iMainChar_MemoryTargetKeyID == 0 )
			{
				//	공격 취소
				this->HT_vMainChar_SetAttackCancel( 10 );
				return;
			}
			//	예약자가 캐릭터이면서 공격해야 할 상대가 아닐때
			if( SERVEROBJECT_IS_CHARACTER( m_iMainChar_MemoryTargetKeyID ) )
			{
				//	주신전 지역과 요새전 지역이면서 공격 대상자가 아니면 공격 취소
				if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetDefineZoneAttackTargetFromKeyID( m_iMainChar_MemoryTargetKeyID ) )
				{
					//	공격 취소
					this->HT_vMainChar_SetAttackCancel( 10 );
					return;
				}
			}

			//	범위공격일때 취소
			if( dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHOUTFOLLOW ||
				dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW )
			{
				//	공격 취소
				this->HT_vMainChar_SetAttackCancel( 11 );
				return;
			}
		}
		else
		{
			//	활스킬이 아닌 장거리공격일때는 공격 캔슬
			if( dwActionSkillType != HT_PCSKILLTYPE_ACTION_SHORT &&
				!CHTParamIDCheck::HT_bIsItemWeaponThrow( m_sMainChar_AttackFactor->nAttackItemID ) )
			{
				this->HT_vMainChar_SetAttackCancel( 12 );
				return;
			}
			//	범위공격일때 취소
			else if( dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHOUTFOLLOW ||
				dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW )
			{
				//	공격 취소
				this->HT_vMainChar_SetAttackCancel( 13 );
				return;
			}
		}
	}

	//	예약된 타켙 지정자가 있으면
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

	//	사정거리 결정
	this->HT_vMainChar_SetAttackRange();
	//	Time Check For Skill
	m_bMainChar_TimeCheckForSkillStart = HT_TRUE;
	m_iMainChar_RealAttackIndex = 1;
	//	목표물에게 다가가기 계산한 빈도수
	m_iMainChar_GoTargetCount = 0;
	//	목표물에게 다가가기 계산한 빈도수의 누적
	//m_iMainChar_GoTargetAccumulationCount = 0;
}

//----------애니매이션 공격 포인트에서 하는일----------//
HTvoid HTMainCharacter::HT_vMainChar_AttackAnmAttackPoint()
{
	//	Attack Point 수행 여부
	m_bMainChar_AttackPointSw = HT_TRUE;
	//	Time Check For Skill
	m_bMainChar_TimeCheckForSkillStart = HT_FALSE;

	if( m_nMainChar_Attack_Type != MAINCHAR_ATTACKTYPE_SKILL )
	{
		//		1. 사정거리 계산
		//		2. 사정거리 이상이면 사정거리 안까지 뛰어감
		//		3. 사정거리 안이면 이동중이면 스톱
		HTvector3 vecMainCharPos = m_cMainCharMove->HT_vecGetPosition();
		HTint nRange = (HTint)HT_extern_fGetDisForTwoPoint( m_vecMainChar_TargetPos, vecMainCharPos );
		if( nRange > ((m_byMainChar_AttackRange * MAP_CELL_SIZE)+30) )
			return;
	}
	
	//-----공격클래스 생성-----//
	m_sMainChar_AttackFactor->strAttackName.HT_szFormat( "%s", g_oMainCharacterInfo.szCharName );
	//	맵픽공격인지 체크
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

	//	쿨타임 카운트 셋팅
	//	0x01:아이템, 0x02:스킬
	if( m_nMainChar_Attack_Type == MAINCHAR_ATTACKTYPE_SKILL )
        g_cQuickSlot->HT_hrSetCoolTime( 0x02, m_sMainChar_AttackFactor->nAttackSkillID, m_sMainChar_AttackFactor->byAttackSkillIDLevel );
}

//----------캐릭터 이동 관련----------//
//----------캐릭터 이동 관련_걷기, 뛰기 셋팅----------//
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

//	캐릭터 각도 컨트롤
HTvoid HTMainCharacter::HT_vMainChar_ControlAngle( HTfloat fElapsedTime )
{
	HTfloat fCharAngle = m_cMainCharMove->HT_fGetDirect();
	
	if( fCharAngle != m_fMainChar_ShowAngle )
	{
		//	1. 실재각을 향한 Display각의 진행방향을 구함
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

		//	2. 실재각으로 진행
		if( m_iMainChar_ProgressAngle == 1 )
		{
			m_fMainChar_ShowAngle += fSpeed;
			//	최대값을 넘어가면 최소값으로
			if( m_fMainChar_ShowAngle > HT_PIX2+HT_PI )
			{
				m_fMainChar_ShowAngle = HT_PI;
			}
		}
		else if( m_iMainChar_ProgressAngle == -1 )
		{
			m_fMainChar_ShowAngle -= fSpeed;
			//	최소값보다 작으면 최대값으로
			if( m_fMainChar_ShowAngle < HT_PI )
			{
				m_fMainChar_ShowAngle = HT_PIX2+HT_PI;
			}
		}

		//	초기화
		if( fAngleDifference <= fSpeed )
		{
			m_fMainChar_ShowAngle = fCharAngle;
		}

		g_pEngineHandler->HT_hrRotateObject( m_iMainChar_ModelID, m_fMainChar_ShowAngle );
	}
}

//	캐릭터 이동 컨트롤
HTvoid HTMainCharacter::HT_vMainChar_ControlMove( HTfloat fElapsedTime )
{
	//	이동해준다.
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE )
	{
		//	충돌 체크
		if( HT_FAILED(m_cMainCharMove->HT_hrMainCharMove_CanMove() ) )
		{
			//	Move Action On/Off Check
			m_bMainChar_MoveSw = HT_TRUE;

			//----------캐릭터 정지 셋팅----------//
            this->HT_vMainChar_SetStopMove();
			if( m_bMainChar_AttackSw )
				this->HT_vMainChar_SetAttackCancel( 14 );

			HTvector3 vecTemp = m_cMainCharMove->HT_vecGetPosition();
			g_pEngineHandler->HT_hrMoveObject( m_iMainChar_ModelID, vecTemp );
			return;
		}

		//	이동 진행
		m_cMainCharMove->HT_vMainCharMove_Moving( fElapsedTime );

		//	이동이 끝났는지 체크
		if( m_cMainCharMove->HT_bMainCharMove_CheckMove() == HT_TRUE )
		{
			m_nMainChar_AniResentState	= CHARACTER_ANISTATE_STD;
			this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );

			//	Move Action On/Off Check
			m_bMainChar_MoveSw = HT_TRUE;

			//	암살 스킬 '쥬바스' 로 대쉬 하였을때는 어택 명령
			if( m_iMain_ActionEffect == 11 )
			{
				if( m_bMainChar_ActionSkillIndex == 3114 )
				{
					//	스킬 초기화
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

		//	픽 검색_맵에 찍은 이펙트 체크하기
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

//	캐릭터 이동 관련_맵픽을하여 타겥 지정
HTvoid HTMainCharacter::HT_vMainChar_SetTargetMovePosition( HT_CELL_COORD crdCell, HTbool bTargetEffectSw )
{
	//-----셀위치를 계산해낸다.-----//
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecTargetPosition, crdCell );

	//-----현재의 위치라면 리턴-----//
	HTPoint CellPos = m_cMainCharMove->HT_ptGetCellPosition();
	if( CellPos.x == crdCell.x && CellPos.y == crdCell.y )
		return;

	//-----화면이 하얗게 변하는 에러를 막는 변수-----//
	if( m_bMainChar_WhiteError == HT_TRUE )
	{
		HTint nTerm = abs( CellPos.x - crdCell.x ) + abs( CellPos.y - crdCell.y );
		if( nTerm <= 2 )
			return;
		else
			m_bMainChar_WhiteError = HT_FALSE;
	}

	//	걷기, 뛰기
	if( m_bMainChar_WalkRun_Sw == HT_FALSE )
		m_cMainCharMove->HT_vMainCharMove_CheckTargetCell( m_vecTargetPosition, CHARACTER_SPEEDLEVEL_WALK );
	else
		m_cMainCharMove->HT_vMainCharMove_CheckTargetCell( m_vecTargetPosition, CHARACTER_SPEEDLEVEL_RUN );

	//	충돌 체크
	if( HT_FAILED(m_cMainCharMove->HT_hrMainCharMove_CanMove() ) )
	{
		//----------캐릭터 정지 셋팅----------//
		this->HT_vMainChar_SetStopMove();
		if( m_bMainChar_AttackSw )
			this->HT_vMainChar_SetAttackCancel( 15 );
		return;
	}

	//----------캐릭터 이동 관련_걷기, 뛰기 관련 애니매이션 셋팅----------//
	this->HT_vMainChar_SetMoveAnme();

	//-----픽 검색_맵에 이펙트 찍기-----//
	if( bTargetEffectSw )
	{
		if (m_cMainCharMove)
		{
			this->HT_vDrawPickMapEffect( m_cMainCharMove->HT_vecGetTargetPosition() );
		}
	}

	//	NoneClick 상태로 셋팅
	m_iMainChar_OneClickIndex = ATTACK_NONECLICK;
	//	공격 중이면 취소
	m_bMainChar_AttackSw = HT_FALSE;
	//	캐스트 스킬 취소
	this->HT_vMainChar_SetCastCancel();

	//	액티브 스킬 인덱스
	m_iMainChar_ActiveSkillIndex = 0;
	//	캐스트 스킬 취소
	this->HT_vMainChar_StopActiveSkill();

	//----------다른캐릭터 이동을 브로드 캐스팅하기 위한 패킷----------//
	BYTE byMoveInfoState;
	if( m_bMainChar_WalkRun_Sw == HT_FALSE )
        byMoveInfoState = 2;
	else
		byMoveInfoState = 3;

	//	10셀 단위로 이동 좌표를 서버에 보내주기 위한 함수_실제 서버에 보내주기
	m_vecMainChar_MoveTargetPos = m_vecTargetPosition;
	HT_CELL_COORD codCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecMainChar_MoveTargetPos, codCell );

	m_vecMainChar_ReqSendMovePos = HTvector3( 0, 0, 0 );
	this->HT_vNetWork_CheckCharMove();
	//this->HT_vNetWork_Send_MSGAction( byMoveInfoState, codCell.x, codCell.y );
}

//-----픽 검색_맵에 이펙트 찍기-----//
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

//-----픽 검색_맵에 찍은 이펙트 체크하기-----//
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

//-----픽 검색_맵에 찍은 이펙트 삭제하고 공격 초기화-----//
HTvoid HTMainCharacter::HT_vInterface_Pick_Map_DeleteEffect()
{
	if( m_bTrrainPick_LoopSw == HT_TRUE )
	{
		m_bTrrainPick_LoopSw = HT_FALSE;
		g_pEngineHandler->HT_hrStopSFX( m_nTrrainPick_EffectID );
	}

	//----------캐릭터 공격 취소----------//
	if( m_bMainChar_AttackSw == HT_TRUE )
	{
		this->HT_vMainChar_SetAttackCancel( 16 );
	}
}

//----------키가 눌러진 상태 체크----------//
HTvoid HTMainCharacter::HT_vCharSetKeyDownCheck( HTbool bFlag )
{
	if( bFlag )
	{
		//	ToDo
	}
	else
	{
		//----------다른캐릭터 이동을 브로드 캐스팅하기 위한 패킷----------//
		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		this->HT_vNetWork_Send_MSGAction( 1, pPt.x, pPt.y );
	}
}

//----------키를 누른상태에서 앞으로 계속 전진----------//
HTvoid HTMainCharacter::HT_vCharSetMoveForward_Go( HTfloat fElapsedTime )
{
	if( !m_bMainChar_AniEventCanSw )
		return;

	//	액티브 스킬이 발동중인 상태라면 스킵
	if( m_iMainChar_ActiveSkillIndex==1 || m_iMainChar_ActiveSkillIndex==2 )
	{
		//	액티브 스킬 인덱스
		m_iMainChar_ActiveSkillIndex = 0;
		//	캐스트 스킬 취소
		this->HT_vMainChar_StopActiveSkill();
	}

	//	Move Action On/Off Check
	if( !m_bMainChar_MoveSw )
        return;

	//	사무다바 스킬을 사용한 상태라면 이동못하게 셋
	if( g_cGameSystem->HT_bGameSystem_GetAskSamudaba() )
		return;

	//	미용실 아이템 사용할때
	if( g_cUIManager->HT_isShowWindow( _DIALOG_BEAUTYSALON ) ||
		g_cUIManager->HT_isShowWindow( _DIALOG_BEAUTYSALON2 ) )
		return;

	//	맵 Pick해서 이동중이었다면
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE )
	{
		m_cMainCharMove->HT_vMainCharMove_StopMvoe();
	}

	//	OneClick 상태인지 체크
	m_iMainChar_OneClickIndex = ATTACK_NONECLICK;

	//	캐릭터가 정지상태일때만 이동가능하게
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE && m_nMainChar_AniResentState != CHARACTER_ANISTATE_STD )
		return;

	//	캐릭터가 일어서는 중이면 그냥 리턴----------//
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_STANDUP )
		return;

	//-----픽 검색_맵에 찍은 이펙트 삭제하고 공격 초기화-----//
	this->HT_vInterface_Pick_Map_DeleteEffect();

	//----------오브젝트에 의한 이동가능 지역 체크----------//
	if( HT_FAILED( m_cMainCharMove->HT_hrMainCharMove_CanMove() ) )
		return;

	//	GO
	m_cMainCharMove->HT_vMainCharMove_Forward( m_bMainChar_WalkRun_Sw, fElapsedTime );

	//	셀단위 이동을 했는지 체크하여 이동했으면 서버에 올려주기
	HTbool result = m_cMainCharMove->HT_bMainCharMove_ServerMoveCheck();
	if( result == HT_TRUE )
	{
		//----------다른캐릭터 이동을 브로드 캐스팅하기 위한 패킷----------//
		BYTE byMoveInfoState;
		if( m_bMainChar_WalkRun_Sw == HT_FALSE )
			byMoveInfoState = 2;
		else
			byMoveInfoState = 3;

		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		this->HT_vNetWork_Send_MSGAction( byMoveInfoState, pPt.x, pPt.y );
	}

	//----------위치와 회전 셋팅----------//
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

	//----------캐릭터 이동 관련_걷기, 뛰기 관련 애니매이션 셋팅----------//
	this->HT_vMainChar_SetMoveAnme();
}

//----------키를 누른상태에서 오른쪽 회전----------//
HTvoid HTMainCharacter::HT_vCharSetMoveForward_Right()
{
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_NORMALATK ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLCAST ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLACTIVATE ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLATK )
		return;

	//	맵 Pick해서 이동중이었다면
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE )
	{
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		m_cMainCharMove->HT_vMainCharMove_StopMvoe();
	}

	m_cMainCharMove->HT_fSetRightRotate();

	//-----픽 검색_맵에 찍은 이펙트 삭제하고 공격 초기화-----//
	HT_vInterface_Pick_Map_DeleteEffect();
}

//----------키를 누른상태에서 왼쪽 회전----------//
HTvoid HTMainCharacter::HT_vCharSetMoveForward_Left()
{
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_NORMALATK ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLCAST ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLACTIVATE ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLATK )
		return;

	//	맵 Pick해서 이동중이었다면
	if( m_cMainCharMove->m_eMainChrMove_State == HT_TRUE )
	{
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		m_cMainCharMove->HT_vMainCharMove_StopMvoe();
	}

	m_cMainCharMove->HT_fSetLeftRotate();

	//-----픽 검색_맵에 찍은 이펙트 삭제하고 공격 초기화-----//
	HT_vInterface_Pick_Map_DeleteEffect();
}

//----------마우스 LButtonDown일때 ----------//
HTvoid HTMainCharacter::HT_vMainChar_SetLButtonDown( HTPoint pPt )
{
	//----------캐릭터가 앉아 있으면 입력 취소----------//
	if( m_bMainChar_SitSw == HT_TRUE )
		return;

	if( m_bMainChar_AttackSw == HT_TRUE )
		return;

	m_bMouseLbuttonDownMove_Sw = MOUSEBUTTONMOVE_SETTING;
	m_fMouseLbuttonDownMove_Angle = HT_vMainChar_GetLButtonDown_Point();

	m_cMainCharMove->HT_vMainCharMove_StopMvoe();

	//----------캐릭터 이동 관련_걷기, 뛰기 관련 애니매이션 셋팅----------//
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

	//------------카메라 모드를 리턴---------------//
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

	////----------셀단위 이동을 했는지 체크하여 이동했으면 서버에 올려주기----------//
	//HTbool result = m_cMainCharMove->HT_bMainCharMove_ServerMoveCheck();

	////----------위치와 회전 셋팅----------//
	//g_pEngineHandler->HT_hrMoveObject( m_iMainChar_ModelID, m_cMainCharMove->HT_vecGetPosition() );
}

//----------화면을 중심으로 마우스 포인트의 라디안 값을 구해옴----------//
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

//----------사운드 컨트롤----------//
HTvoid HTMainCharacter::HT_vCharSoundControl()
{
}

//----------캐릭터 정지한 상태를 체크하여 정지 애니매이션 셋팅----------//
HTvoid HTMainCharacter::HT_vMainChar_StopMoveCheck()
{
	//	캐릭터가 정지했을때 마지막 서버에 보낸 이동좌표와 현재의 좌표를 비교해서 틀리면 서버에 알림
	//if( m_cMainCharMove->HT_iMainCharMove_GetSpeed( 0x00 ) == 0.0f )
	if( m_cMainCharMove->m_eMainChrMove_State == HT_FALSE )
	{
		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		if( pPt.x != m_pMainChar_SaveMovePos.x || pPt.y != m_pMainChar_SaveMovePos.y )
		{
			//----------다른캐릭터 이동을 브로드 캐스팅하기 위한 패킷----------//
			this->HT_vNetWork_Send_MSGAction( 1, pPt.x, pPt.y );
		}
	}

	if( !g_bGamePlayMovieForGlobal )
	{
		//	정지애니매이션 중일때는 휴식동작 체크
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

	//	스탠딩 애니매이션을 위한 체크
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
		//----------캐릭터 이동 관련_걷기, 뛰기 관련 애니매이션 셋팅----------//
		this->HT_vMainChar_SetMoveAnme();
	}
}

//----------캐릭터 정지 셋팅----------//
HTvoid HTMainCharacter::HT_vMainChar_SetStopMove()
{
	//	캐릭터가 앉아 있다면
	if( m_bMainChar_SitSw == HT_TRUE )
		return;

	m_cMainCharMove->HT_vMainCharMove_StopMvoe();
	m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
	this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );

	//	이펙트 지우기
	if( m_bTrrainPick_LoopSw )
	{
		m_bTrrainPick_LoopSw = HT_FALSE;
		g_pEngineHandler->HT_hrStopSFX( m_nTrrainPick_EffectID );
	}
}

//----------캐릭터 이동 관련_걷기, 뛰기 관련 애니매이션 셋팅----------//
HTvoid HTMainCharacter::HT_vMainChar_SetMoveAnme()
{
	//	Effect of MSG_Action Check
	//	4:날기,	7:미끄러지기(이동애니없음) 일때는 그냥 통과
	if( m_iMain_ActionEffect == 4 ||
		m_iMain_ActionEffect == 8 )
		return;

	//-----걷기, 뛰기-----//
	if( m_bMainChar_WalkRun_Sw == HT_FALSE )
	{
		if( m_nMainChar_AniResentState != CHARACTER_ANISTATE_WLK )
		{
			//	애니매이션 셋팅
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

//----------캐릭터 앉기 관련----------//
HTvoid HTMainCharacter::HT_vMainChar_SetSit()
{
	//	Move Action On/Off Check
	if( !m_bMainChar_MoveSw )
		return;

	//-----앉기 동작 딜레이를 위해-----//
	DWORD dwPassTime = GetTickCount();
	if( dwPassTime < m_dwMainChar_sitTime + 1100 )
		return;

	m_dwMainChar_sitTime = GetTickCount();

	//----------정지----------//
	m_cMainCharMove->HT_vMainCharMove_StopMvoe();

	// 캐릭터가 앉게 되면 포탈 창이 떠 있는 상태를 없애버린다.
	g_cUIManager->HT_HideWindow( _DIALOG_PORTALWND );

	if( m_bMainChar_SitSw == HT_TRUE )
	{
		m_bMainChar_SitSw = HT_FALSE;
		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_STANDUP;
		this->HT_vMainChar_SetChangeAni( 0x00, 1, 1.0f, 0, 0 );

		//----------다른캐릭터 이동을 브로드 캐스팅하기 위한 패킷----------//
		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		this->HT_vNetWork_Send_MSGAction( 1, pPt.x, pPt.y );

		//	캐릭터가 앉을때와 설때 서버에 보냄
		PS_CSP_REQ_CHAR_ACT info = HT_NULL;
		info = new S_CSP_REQ_CHAR_ACT;
		info->byAct = 2;
		g_pNetWorkMgr->RequestCharAct( info );
		HT_DELETE( info );
	}
	else
	{
		//-----픽 검색_맵에 찍은 이펙트 삭제하고 공격도 초기화-----//
		HT_vInterface_Pick_Map_DeleteEffect();

		// 앉았다 일어나면 약간 이동한다. 그러므로 현재 좌표를 다시 구해서 이동이 없도록 한다.
		HTPoint CellPos = m_cMainCharMove->HT_ptGetCellPosition();
		m_crdSitCell.x = CellPos.x;
		m_crdSitCell.y = CellPos.y;

		m_bMainChar_SitSw = HT_TRUE;
		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_SITDOWN;
		this->HT_vMainChar_SetChangeAni( 0x00, 1, 1.0f, 0, 0 );

		//----------앉기 사운드----------//
		g_pEngineHandler->HT_hrPlaySound( SOUNDEFFECT_SIT, 1 );

		//----------다른캐릭터 이동을 브로드 캐스팅하기 위한 패킷----------//
		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		this->HT_vNetWork_Send_MSGAction( 0, pPt.x, pPt.y );

		//	캐릭터가 앉을때와 설때 서버에 보냄
		PS_CSP_REQ_CHAR_ACT info = HT_NULL;
		info = new S_CSP_REQ_CHAR_ACT;
		info->byAct = 1;
		g_pNetWorkMgr->RequestCharAct( info );
		HT_DELETE( info );
	}
}

//----------아이템 사용 이펙트 셋팅----------//
HTvoid HTMainCharacter::HT_vMainChar_SetItemUseEffect()
{
//	HTint nEffectID;
//	g_pEngineHandler->HT_hrStartSFX( &nEffectID, HT_FX_SPRINGRECOVERY, m_iMainChar_ModelID, HT_FALSE );
}

//----------방어 애니매이션 셋팅----------//
HTvoid HTMainCharacter::HT_vMainChar_SetDefence()
{
	//	캐릭터가 앉아 있다면
	if( m_bMainChar_SitSw == HT_TRUE )
		return;

	m_nMainChar_AniResentState	= CHARACTER_ANISTATE_MAGIC_DEFENCE;
	this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
}

//	스킬 적용대상 체크
HTRESULT HTMainCharacter::HT_bvMainChar_GetPCSkillAllowedTarget( HTint iSkillID, BYTE byLevel )
{
	//	스킬 적용 대상을 알아온다.//賈痰세콘蘆잚 fors_debug 
	HTint iAllowedTarget;
	g_pParamMgr->HT_bGetPCSkillAllowedTarget( iSkillID, byLevel, &iAllowedTarget );
	switch( iAllowedTarget )
	{
		case _TARGET_SELF :
			break;
		case _TARGET_FRIENDLY :	// field에서는 PC, 주신전에서는 같은 주신		
			break;
		case _TARGET_FRIENDLY_EXCEPT_ME :	// 자신을 제외
			break;
		case _TARGET_ENEMEY :
            break;
		case _TARGET_PARTY :
			break;
		case _TARGET_GUILD :
			break;
		case _TARGET_ALL :
			break;
		case _TARGET_FRIENDLY_CORPSE :	// 동료의 시체. 부활 마법에서 사용
			break;
		case _TARGET_ENEMEY_CORPSE :	// 적의 시체. 시체 폭파 마법에서 사용. 현재 사용마법 없음
			break;
		case _TARGET_GATE :	// 공성전시 성문에 사용
			break;
	}
	return HT_OK;
}

//	액션 스킬 셋팅
HTvoid HTMainCharacter::HT_vMainChar_SetActionSkill( DWORD dwSkillID )
{
	//	다른 캐릭이 보이지 않는 상태라면 스킵
	if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetShowCheck() == HT_FALSE )
		return;

	//	아수라 아킬라 스킬일 경우 요구HP가 현재 HP보다 높을 경우 스킵
	if( dwSkillID == 3160 )
	{
		HTint iCostHP;
		g_pParamMgr->HT_bGetPCSkillCostHP( dwSkillID, g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( dwSkillID ), &iCostHP );
		if( iCostHP >= m_iMainChar_Cur_HP )
			return;
	}

	//	class1이 19이면 _MSG_CONTZCT_NPC 메시지를 보낸다.
	if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetClass1( m_iMainChar_Target_KeyID ) == 19 )
	{
		g_cOtherObjectSystem->HT_vOtherObjectSystem_NetWorkCONTACT_NPC( m_iMainChar_Target_KeyID );
		return;
	}

	//	상대방이 은신모드이고 내가 로카나 스킬으 쓰고 있지 않으면 스킵
	__int64 iObjectAffection = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetAffection( m_iMainChar_Target_KeyID );
    if( (iObjectAffection & eTNVSAfn_Invisible) != 0 &&
		(m_iMain_Affections & eTNVSAfn_WizardEyes) == 0 )
		return;

	HTbyte bySkillGoodType = 0;
	g_pParamMgr->HT_bGetPCSkillType( dwSkillID, 1, &bySkillGoodType );	//	0:나쁜것, 1:좋은것

	CHTString szMessage;
	//	안전지역이면서 좋은 스킬이면 스킬시전 가능
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
	if( g_pEngineHandler->HT_bIsCellSafeZone( pPt.x, pPt.y, 0 ) &&
		bySkillGoodType == 0 )
	{
		// 안전지역에서는 스킬을 사용 할 수 없습니다.
		HT_vMainChar_SetMessage( eMsgSkillUseSaveZoneErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage );
		return;
	}

	//	나의 상태가 스턴이나 슬립일경우는 공격 못함
	if( m_iMain_Affections & eTNVSAfn_Stun || 
		m_iMain_Affections & eTNVSAfn_Sleep )
		return;

	//	Time Check For Skill
	//	시간체크하여 스킬시전 가능하면 바로 시전, 불가하면 예약
	if( m_bMainChar_TimeCheckForSkillStart )
	{
       	//----------캐릭터 공격 취소----------//
		this->HT_vMainChar_SetAttackCancel( 17 );
	}

	//	스킬과 아이템을 비교해서 적절치 못할 결우 스킵힌다.
	HTint iReqItemType = 0;
	g_pParamMgr->HT_bGetPCSkillReqWeaponType( dwSkillID, 1, &iReqItemType );
    if( iReqItemType )
	{
		short snItemType;
		bool bCheck = g_pParamMgr->HT_bGetItemType( m_dwWeaponItemID, &snItemType );
		if( !BIT_AND( snItemType, iReqItemType ) ||
			bCheck == false )
		{
			// 이 스킬을 사용할수 있는 무기를 착용하고 있지 않습니다.
			HT_vMainChar_SetMessage( eMsgSkillUseItemErr, &szMessage );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
			return;
		}
	}

	// 앉은상태에서는 스킬을 사용할 수 없습니다.
	if( m_bMainChar_SitSw == HT_TRUE )
	{
        HT_vMainChar_SetMessage( eMsgSkillUseSitdownErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		return;
	}

	//	맵 픽 이펙트 꺼고
	if( m_bTrrainPick_LoopSw == HT_TRUE )
	{
		m_bTrrainPick_LoopSw = HT_FALSE;
		g_pEngineHandler->HT_hrStopSFX( m_nTrrainPick_EffectID );
	}
	//	맵 이펙트를 꺼고(범위 마법용)
	g_pEngineHandler->HT_hrOffMouseWideEffect();

	//	맵픽되어 있다면 리턴
	if( m_bMainChar_MapPickAttackSw == HT_TRUE )
		return;

	//	퀵슬롯에서 넘어오는 스킬 인덱스와 레벨
	m_iMainChar_ReservedActionSkillIndex = dwSkillID;
	HTbyte byActionSkillLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level(m_iMainChar_ReservedActionSkillIndex);
	//	스킬 적용대상 체크
    if( HT_FAILED(this->HT_bvMainChar_GetPCSkillAllowedTarget( m_iMainChar_ReservedActionSkillIndex, byActionSkillLevel )) )
	{ 
		return;
	}

	// 액션 스킬 사정거리 계산
	if( !g_pParamMgr->HT_bGetPCSkillRange( m_iMainChar_ReservedActionSkillIndex, byActionSkillLevel, &m_iMainChar_AttackRange_ActionSkill ) )
		m_iMainChar_AttackRange_ActionSkill = 1;
	//	액션 스킬 캐스팅 속도
	if( !g_pParamMgr->HT_bGetPCSkillCastingTime( m_iMainChar_ReservedActionSkillIndex, byActionSkillLevel, &m_iMainChar_CastGaterTime_ActionSkill ) )
        m_iMainChar_CastGaterTime_ActionSkill = 0;
	//	액션 스킬 타입을 얻어온다.
	HTdword	dwActionSkillType = g_pEngineHandler->HT_dwGetSkillType( m_iMainChar_ReservedActionSkillIndex );
	//	범위공격일때는 셋팅만하고 리턴
	if( dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHOUTFOLLOW ||
		dwActionSkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW )
	{
		//	Object Targeting EFfect off
		g_cOtherObjectSystem->HT_vOtherObjectSystem_HPWindowInit();
		//	Map Effect On
		g_pEngineHandler->HT_hrOnMouseWideEffect( HT_FX_TERRITORY_2 );
		//	Map Pick 변수 On
		m_bMainChar_MapPickAttackSw = HT_TRUE;
		//	Target KeyID Init
		m_iMainChar_Target_KeyID = 0;
		return;
	}
	else
	{
		m_bMainChar_MapPickAttackSw = HT_FALSE;
    }

	//	타겥이 지정되어 있지 않다면 본인을 지정
	if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetLevel( m_iMainChar_Target_KeyID ) == 0 )
	{
		m_iMainChar_Target_KeyID = m_iMainChar_KeyID;
		//	원클릭 셋팅
		m_iMainChar_OneClickIndex = ATTACK_ONECLICK;
	}

	//	OneClick 상태인지 체크, 
	if( m_iMainChar_OneClickIndex == ATTACK_NONECLICK )
	{
		//	RockOn Check
		if( g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( m_iMainChar_Target_KeyID ) == 0 )
		{
            return;
		}
	}

	//	공격 가능한 타겥인지 체크
	//if( HT_FAILED( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetCheckCanAttackTargetForSkill( m_bMainChar_TimeCheckForSkillStart, m_iMainChar_Target_KeyID, pPt, 
	//	(HTint)dwSkillID, m_iMainChar_Target_KeyID, m_iMainChar_MemoryTargetKeyID ) ) )
	//	return;
	if( g_cOtherObjectSystem->HT_hrOtherObjectSystem_GetTargetting( m_iMainChar_Target_KeyID ) == HT_FALSE )
	{
		//	타겥팅 불가한 녀석일때면 공격 스킬 사용했을때 스킵
		if( bySkillGoodType == 0 )
			return;
	}
	else
	{
		//	타겥팅 가능한 녀석일때면 좋은 스킬 사용했을때 스킵
		if( bySkillGoodType == 1 )
		{
			//	저장타겥을 공격포인트 이전에 바로 스킬 들어가면 몹으로 공격포인트 이후면 타겥을 메인캐릭터로
			//	현재 타겥을 공격포인트 이전에 바로 메인캐릭터로, 공격포인트 이후면 몹으로
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

	//	액션 스킬 셋팅_적용
	this->HT_vMainChar_SetActionSkillAffect();
}

//	액션 스킬 셋팅_적용
HTvoid HTMainCharacter::HT_vMainChar_SetActionSkillAffect()
{
	//	F1~F10에 의한 스킬 공격 신호가 들어왔느냐?
	m_bMainChar_SetSkillAttackSw = HT_TRUE;

	//	일반공격 없이 오직 스킬로만 하는 공격이냐?
	if( !m_bMainChar_AttackSw )
	{
		m_bMainChar_OnlySkillAttackSw = HT_TRUE;
		m_iMainChar_RealAttackIndex = 1;
	}
	else
	{
		m_bMainChar_OnlySkillAttackSw = HT_FALSE;
	}

	//	목표물에게 다가가기:HT_TRUE, 멀어지기:HT_FALSE
	m_bMainChar_GoTargetIndex = 0;
	//	목표물에게 다가가기 계산한 빈도수
	m_iMainChar_GoTargetCount = 0;
	//	목표물에게 다가가기 계산한 빈도수의 누적
	m_iMainChar_GoTargetAccumulationCount = 0;
	//	일단 먼저 공격중인것은 처리하고 하려면 지금 공격중이 아닐때만
	//	공격 셋팅
	m_bMainChar_AttackSw = HT_TRUE;
	//	데미지 최대값 초기화
	m_iMainChar_MaxDamage = 0;
	//	사정거리 결정
	this->HT_vMainChar_SetAttackRange();

	//----------다른캐릭터 이동을 브로드 캐스팅하기 위한 패킷----------//
	if( m_iMainChar_Target_KeyID != m_iMainChar_KeyID )
	{
		BYTE byMoveInfoState;
		if( m_bMainChar_WalkRun_Sw == HT_FALSE )
			byMoveInfoState = 2;
		else
			byMoveInfoState = 3;

		this->HT_vMainChar_TargetPosCheck();
		//		1. 사정거리 계산
		//		2. 사정거리 이상이면 사정거리 안까지 뛰어감
		//		3. 사정거리 안이면 이동중이면 스톱
		HTvector3 vecMainCharPos = m_cMainCharMove->HT_vecGetPosition();
		HTint nRange = (HTint)HT_extern_fGetDisForTwoPoint( m_vecMainChar_MoveTargetPos, vecMainCharPos );
		if( nRange > (( (m_byMainChar_AttackRange * MAP_CELL_SIZE) + MAP_CELL_SIZE + 5 ) ) )
		{
			//	10셀 단위로 이동 좌표를 서버에 보내주기 위한 함수_실제 서버에 보내주기
			m_vecMainChar_MoveTargetPos = m_vecMainChar_TargetPos;
			//HT_CELL_COORD codCell;
			//g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecMainChar_MoveTargetPos, codCell );
			//this->HT_vNetWork_Send_MSGAction( byMoveInfoState, codCell.x, codCell.y );
			m_vecMainChar_ReqSendMovePos = HTvector3( 0, 0, 0 );
			this->HT_vNetWork_CheckCharMove();
		}
	}
}

//----------액티브 스킬 셋팅----------//
HTvoid HTMainCharacter::HT_vMainChar_SetActiveSkill( DWORD dwSkillIndex )
{
	HTbyte bySkillGoodType = 0;
	g_pParamMgr->HT_bGetPCSkillType( dwSkillIndex, 1, &bySkillGoodType );	//	0:나쁜것, 1:좋은것

	//	안전지역에서는 스킬 시전 못한다.
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
	if( g_pEngineHandler->HT_bIsCellSafeZone( pPt.x, pPt.y, 0 ) &&
		bySkillGoodType == 0 )
	{
		CHTString szMessage;
		// 안전지역에서는 스킬을 사용 할 수 없습니다.
		HT_vMainChar_SetMessage( eMsgSkillUseSaveZoneErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage );
		return;
	}

	//	3159 아수라 사누타 스킬 나의 상태가 스턴이나 슬립일경우는 공격 못함
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
        // 앉은상태에서는 스킬을 사용할 수 없습니다.
		CHTString szMessage;
		HT_vMainChar_SetMessage( eMsgSkillUseSitdownErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		return;
	}

	//	스킬 애니매이션 Ready, Cast, Activate일때는 시전 못함
	if( m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLCAST ||
		m_nMainChar_AniResentState == CHARACTER_ANISTATE_SKILLACTIVATE )
		return;

	//	현재 발동되는 액티브 스킬 INDEX
	m_dwMainChar_ActiveSkillCurIndex = dwSkillIndex;
	//	현재 발동되는 액티브 스킬 Level
	m_byMainChar_ActiveSkillCurLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( m_dwMainChar_ActiveSkillCurIndex );
	//	현재 발동되는 액티브 스킬 타입 구함
	m_dwMainChar_ActiveSkillType = g_pEngineHandler->HT_dwGetSkillType( m_dwMainChar_ActiveSkillCurIndex );
	//	OtherChar에게 이펙트 틀어야 될때 Target이 없거나 자기자신이면 Skip
	//if(	m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOPARTY ||
	//	m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_WITHNEARMONSTER )
	//{
	//	//if( m_dwMainChar_ActiveSkillCurIndex == 3031 &&			//	파티 우마 사마테
	//	//	m_dwMainChar_ActiveSkillCurIndex == 3212 &&			//	파티 로하티 수사르바
	//	//	m_dwMainChar_ActiveSkillCurIndex == 3213 &&			//	파티 비사이야 사르바나
	//	//	m_dwMainChar_ActiveSkillCurIndex == 3217 &&			//	파티 부카 자마
	//	//	m_dwMainChar_ActiveSkillCurIndex == 3320 &&			//	파티 트레타
	//	//	m_dwMainChar_ActiveSkillCurIndex == 3328 )			//	파티 자마
	//	{
	//		if( !m_iMainChar_Target_KeyID || m_iMainChar_Target_KeyID==m_iMainChar_KeyID )
	//			return;
	//	}
	//}

	//	공격중이면 취소
	if( m_bMainChar_AttackSw )
		this->HT_vMainChar_SetAttackCancel( 18 );

	//	캐릭터 정지 셋팅
	this->HT_vMainChar_SetStopMove();

	//	액티브 스킬 인덱스
	m_iMainChar_ActiveSkillIndex = 1;
}

//	액티브 스킬 스케쥴러_Activate/State관리
HTvoid HTMainCharacter::HT_vMainChar_ControlActiveSkill_ActivateAndState()
{
	if( !m_iMainChar_ActiveSkillIndex )
		return;

	HTint iPassTime = GetTickCount();

	switch( m_iMainChar_ActiveSkillIndex )
	{
		case 1 :
			{
				//	캐스팅 애니매이션 틀어준다.
				m_nMainChar_AniResentState	= CHARACTER_ANISTATE_SKILLREADY;
				this->HT_vMainChar_SetChangeAni( 0x01, 1, 0.0f, m_dwMainChar_ActiveSkillCurIndex, 0 );
				//	이펙트 셋팅
				this->HT_vMainChar_StopActiveSkill();
				g_pEngineHandler->HT_hrStartSFX( &m_iMainChar_ActiveSkillEffectID, m_dwMainChar_ActiveSkillCurIndex, HT_SFX_WHEN_READY, m_iMainChar_ModelID, HT_TRUE, m_byMainChar_ActiveSkillCurLevel );
				//	이펙트 시작시간
				m_iMainChar_ActiveSkill_StartTime		= GetTickCount();
				//	Ready 시간을 알아오고
				if( !g_pParamMgr->HT_bGetPCSkillReadyTime( m_dwMainChar_ActiveSkillCurIndex, m_byMainChar_ActiveSkillCurLevel, &m_iMainChar_ActiveSkill_DurationTime ) )
					m_iMainChar_ActiveSkill_DurationTime = 0;
				//	네트윅 상태에 의한 딜레이를 감안하여 0.1초 더해준다.
				m_iMainChar_ActiveSkill_DurationTime += 100;
				//	서버에 액티브 스킬 시작 보내기
				this->HT_vMainChar_CSP_UnitSkill_Start( m_dwMainChar_ActiveSkillCurIndex, m_iMainChar_KeyID, m_cMainCharMove->HT_vecGetPosition(), 2 );
				//	액티브 스킬 인덱스
				m_iMainChar_ActiveSkillIndex = 2;
			}
			break;
		case 2 :
			{
				if( iPassTime > m_iMainChar_ActiveSkill_StartTime+m_iMainChar_ActiveSkill_DurationTime )
				{
					//	퀵슬롯에 셋팅
					g_cQuickSlot->HT_hrSetCoolTime( 0x02, m_dwMainChar_ActiveSkillCurIndex, m_byMainChar_ActiveSkillCurLevel );
					//	액티브 스킬 이펙트 정지
					this->HT_vMainChar_StopActiveSkill();
					//	액티베이트 애니매이션 틀어준다.
					m_nMainChar_AniResentState = CHARACTER_ANISTATE_SKILLACTIVATE;
					this->HT_vMainChar_SetChangeAni( 0x01, 1, 0.0f, m_dwMainChar_ActiveSkillCurIndex, 0 );
					// 액티베이트 이펙트 시전
					HTint iTempEffectID;
					g_pEngineHandler->HT_hrStartSFX( &iTempEffectID, m_dwMainChar_ActiveSkillCurIndex, HT_SFX_WHEN_ACTIVATE, m_iMainChar_ModelID, HT_FALSE, m_byMainChar_ActiveSkillCurLevel );
					//	OtherChar에게 이펙트 틀어야 될때
					if(	m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOPARTY ||
						m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_WITHNEARMONSTER )
					{
						g_cOtherObjectSystem->HT_vOtherObjectSystem_EffectHitAction( m_iMainChar_Target_KeyID, m_dwMainChar_ActiveSkillCurIndex, 0, m_iMainChar_ModelID, m_iMainChar_KeyID );
					}

					//	듀레이션 타임(지속시간)을 구함
					if( !g_pParamMgr->HT_bGetPCSkillDuration( m_dwMainChar_ActiveSkillCurIndex, m_byMainChar_ActiveSkillCurLevel, &m_iMainChar_ActiveSkill_DurationTime ) )
						m_iMainChar_ActiveSkill_DurationTime = 0;
					//	이펙트 시작시간
					m_iMainChar_ActiveSkill_StartTime = GetTickCount();
					
					//	자신주위에 영향을 주는스킬인지 파악해서 범위 스킬로 서버에 날리고 그렇지 않을때는 일반 스킬로 서버에 날림
					HTbool	bExceptionForFX;
					if( m_dwMainChar_ActiveSkillCurIndex == 3028 ||			//	프로스아나 바티아
						m_dwMainChar_ActiveSkillCurIndex == 3029 ||			//	아자카
						m_dwMainChar_ActiveSkillCurIndex == 3043 ||			//	나우티
						m_dwMainChar_ActiveSkillCurIndex == 3061 ||			//	아자카
						m_dwMainChar_ActiveSkillCurIndex == 3017 ||
						m_dwMainChar_ActiveSkillCurIndex == 3361 ||			//	라우티 바티아
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

					//	에너지를 포함한 스킬이면 이펙트 틀지 않는다.
					if( m_dwMainChar_ActiveSkillType != HT_PCSKILLTYPE_ACTIVE_STATE_LOOP_TOME_WITHENERGY )
					{
						//	듀레이션 타임이 있으면 지속 없으면 한방 스킬로 표현한다.
						if( m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME ||
							m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_PERATTACK ||
							m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_PERATTACKED ||
							m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOPARTY ||
							bExceptionForFX == HT_TRUE )
							g_pEngineHandler->HT_hrStartSFX( &m_iMainChar_ActiveSkillEffectID, m_dwMainChar_ActiveSkillCurIndex, HT_SFX_WHEN_STATE, m_iMainChar_ModelID, HT_FALSE, m_byMainChar_ActiveSkillCurLevel );
						else
							g_pEngineHandler->HT_hrStartSFX( &m_iMainChar_ActiveSkillEffectID, m_dwMainChar_ActiveSkillCurIndex, HT_SFX_WHEN_STATE, m_iMainChar_ModelID, HT_TRUE, m_byMainChar_ActiveSkillCurLevel );
					}

					//	액티브 스킬 인덱스
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

					//	액티브 스킬 정지
					this->HT_vMainChar_StopActiveSkill();
					//	액티브 스킬 인덱스
					m_iMainChar_ActiveSkillIndex = 0;
				}
			}
			break;
	}
}

//	액티브 이펙트 켜야 될때_STATE_ONCE_TOME_PERATTACK, PERATTACKED
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

//	액티브 스킬 정지
HTvoid HTMainCharacter::HT_vMainChar_StopActiveSkill()
{
	if( m_iMainChar_ActiveSkillEffectID != 0 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iMainChar_ActiveSkillEffectID );
		m_iMainChar_ActiveSkillEffectID = 0;
	}
}

//----------내가 공격대상인지 파악----------------//
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

//----------공격 받았을때 해줘야 할 일들----------//
HTvoid HTMainCharacter::HT_vMainChar_SetDisAttackCheck( HTint iSkillID, HTint iItemID, HTint iInvadeModelID )
{
	if( m_nMainChar_AniResentState	== CHARACTER_ANISTATE_DIE )
		return;

	//	관련 액티브 스킬 발동중일때 이펙트 틀기 위해_방어스킬등
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

	//	만약 상점모드라면 여기서 스킵
	if( g_cIndividualStore->HT_bIndividualStore_IsStoreMode() )
		return;

	//	자리비움 모드라면 해제한다.
	if( g_pDuelSystem->HT_bDuel_GetWaitMode() == HT_TRUE )
        g_pDuelSystem->HT_vDuel_SetWaitModeCancelFromKeyInput();

	//----------앉아 있었다면 풀기----------//
	if( m_bMainChar_SitSw == HT_TRUE )
	{
		m_bMainChar_SitSw = HT_FALSE;
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		//----------다른캐릭터 이동을 브로드 캐스팅하기 위한 패킷----------//
		HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
		this->HT_vNetWork_Send_MSGAction( 1, pPt.x, pPt.y );
	}

	//	캐릭터 색깔 변화주기
	// 물리 화염 냉기 전격 독 무적 아닐때만
	if( !(m_iMain_Affections&eTNVSAfn_Damage) &&
		!(m_iMain_Affections & eTNVSAfn_Fire) &&
		!(m_iMain_Affections & eTNVSAfn_Cold) &&
		!(m_iMain_Affections & eTNVSAfn_Lightning) &&
        !(m_iMain_Affections & eTNVSAfn_Poison) &&
		!(m_iMain_Affections & eTNVSAfn_ProtectFromPK) )
        this->HT_vMainChar_SetModelColor( 1.0f, 0.1f, 0.0f, 0.4f );

	if( !m_bMainChar_HitEventCanSw )
		return;

	//	단거리 공격이었다면 Skip
	//if( m_iMainChar_AttackRange_ActionSkill <= 1 )
        //return;

	//	0:나쁜것, 1:좋은것
	HTbyte bySkillType = 0;
	if( iSkillID )
        g_pParamMgr->HT_bGetPCSkillType( iSkillID, 1, &bySkillType );

	if( bySkillType == 0 )
	{
		//	플리커
		g_pEngineHandler->HT_hrFlickerObject( m_iMainChar_ModelID, HT_COLOR( 1.00f, 0.20f, 0.10f, 1.0f ), 0.4f );

        if( m_nMainChar_AniResentState != CHARACTER_ANISTATE_WLK && 
			m_nMainChar_AniResentState != CHARACTER_ANISTATE_RUN )
		{
			//	공격 중이었다면
			if( m_bMainChar_AttackSw )
			{
				//	활일때 스킵
				if( m_bMainChar_ItemArrow == HT_TRUE )
					return;

				//	스킬일때
				if( m_bMainChar_ActionSkillIndex )
				{
					//	장거리 스킬일때만 취소
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
			//	캐릭터 정지
			m_cMainCharMove->HT_vMainCharMove_StopMvoe();
		}
	}
	//else
	//{
	//	m_nMainChar_AniResentState = CHARACTER_ANISTATE_MAGIC_DEFENCE;
	//	this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
	//}
}

//	은신
HTvoid HTMainCharacter::HT_vMainChar_SetTransparency( HTbyte byGMMode, __int64 iAffection )
{
	//	투명 모드 실행
	if( ( byGMMode & 0x02 ) != 0x00 ||
		iAffection != 0 ||
		g_bTransparencyMode )
	{
		g_pEngineHandler->HT_hrShowObject( m_iMainChar_ModelID, HT_FALSE );
	}
	//	투명 모드 안 실행
	else
	{
		////	이펙트가 있으면 꺼기
		//if( m_iMain_FXAffections != -1 )
		//	g_pEngineHandler->HT_hrStopSFX( m_iMain_FXAffections );

		g_pEngineHandler->HT_hrShowObject( m_iMainChar_ModelID, HT_TRUE );
		//	나의스킬 원하는 녀석만 Delete 얀카나...ㅡ.ㅡ
		g_pMainBar->HT_vMainBar_MySkillSetDelete( 3103 );
	}
}

//----------서버가 끊어지거나 포탈 이동 요청했을 때----------//
HTvoid HTMainCharacter::HT_vMainChar_SetCanNotMove( HTbool bEffectSw )
{
	//	Move Action On/Off Check
	m_bMainChar_MoveSw = HT_FALSE;

// Affection 을 이용한 FX로 대체 된다.
//	if( bEffectSw &&
//		m_iMain_FaintingstateFX == 0 )
//	{	
//		g_pEngineHandler->HT_hrStartSFX( &m_iMain_FaintingstateFX, HT_FX_FAINTINGSTATE, m_iMainChar_ModelID, HT_TRUE );
//	}

	//----------캐릭터 정지 셋팅----------//
	//	홀더일때는 공격중이 아닐때만 셋팅
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

//----------포탈이동----------//
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
//------------------반환값들-------------------//
//---------------------------------------------//
//	서버에서 내려오는 캐릭터의 각종 상태
HTvoid HTMainCharacter::HT_vMainCHar_SCP_SetAffections( __int64 iAffections )
{
	//	스턴일었을때 풀어주기 실재 공격 인덱스 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	if( m_iMain_Affections & eTNVSAfn_Stun || 
		m_iMain_Affections & eTNVSAfn_Sleep )
        m_iMainChar_RealAttackIndex = 1;

	//	Affections Fx On/Off
	HTdword dwFXID = g_pEngineHandler->HT_dwGetAffectionFXID( iAffections, m_iMain_Affections );
    //if ( iAffections == eTNVSAfn_MoveSpeed140R ) dwFXID = 1010090;//fors_debug 殮쌈립令 劤녁곪
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

	//	눈찌르기
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

	//	현재의 Affections 셋팅
	m_iMain_Affections = iAffections;

	//	은신 체크
	//if( iAffections & eTNVSAfn_Invisible ) //fors_debug 속
	this->HT_vMainChar_SetTransparency( 0x00, m_iMain_Affections & eTNVSAfn_Invisible );

	//	스턴 체크, 슬립 체크, 홀더 체크
	if( m_iMain_Affections & eTNVSAfn_Stun || 
		m_iMain_Affections & eTNVSAfn_Sleep ||
		m_iMain_Affections & eTNVSAfn_Hold ||
		m_iMain_Affections & eTNVSAfn_Hold2 )	g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_TRUE );
	else										g_cMainCharacter->HT_vMainChar_SetCanMove();

	//	마법의 눈
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetWizardEyes( m_iMain_Affections & eTNVSAfn_WizardEyes );

	//	캐릭터 색 관련
	//	지속 데미지류
	CHTString strMsg, szMessage;
	strMsg.HT_hrCleanUp();
	if( m_iMain_Affections & eTNVSAfn_Damage ) // 물리
	{
		this->HT_vMainChar_SetModelColor( 1.0f, 0.0f, 0.0f, 1.0f );	//	빨강
		HT_vMainChar_SetMessage( eMsgCommonSkillPhysics, &strMsg );
	}
    if( m_iMain_Affections & eTNVSAfn_Fire ) // 화염
	{
		this->HT_vMainChar_SetModelColor( 1.0f, 1.0f, 0.0f, 1.0f );	//	노랑
		if( strMsg.HT_bIsEmpty() )
			HT_vMainChar_SetMessage( eMsgCommonSkillBlaze, &strMsg);
		else
		{
			HT_vMainChar_SetMessage( eMsgCommonSkillBlaze, &szMessage);
			strMsg = strMsg + _T(", ") + szMessage;
		}
	}
	if( m_iMain_Affections & eTNVSAfn_Cold ) // 냉기
	{
		this->HT_vMainChar_SetModelColor( 0.0f, 1.0f, 1.0f, 1.0f );	//	청록
		if( strMsg.HT_bIsEmpty() )
			HT_vMainChar_SetMessage( eMsgCommonSkillCold, &strMsg);
		else
		{
			HT_vMainChar_SetMessage( eMsgCommonSkillCold, &szMessage);
			strMsg = strMsg + _T(", ") + szMessage;
		}
	}
	if( m_iMain_Affections & eTNVSAfn_Lightning ) // 전격
	{
		this->HT_vMainChar_SetModelColor( 0.9f, 0.5f, 0.0f, 1.0f );	//	연한 청록
		if( strMsg.HT_bIsEmpty() )
			HT_vMainChar_SetMessage( eMsgCommonSkillLightning, &strMsg);
		else
		{
			HT_vMainChar_SetMessage( eMsgCommonSkillLightning, &szMessage);
			strMsg = strMsg + _T(", ") + szMessage;
		}
	}
	if( m_iMain_Affections & eTNVSAfn_Poison ) // 독
	{
		this->HT_vMainChar_SetModelColor( 0.0f, 1.0f, 0.0f, 1.0f );	//	녹색
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
		// 지속 데미지를 받고 있습니다.
		HT_vMainChar_SetMessage( eMsgCharacterContinuousDamage, &szMessage);
		strMsg = strMsg + _T(" ") + szMessage;

		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
	}

	//	무적 상태
	if( m_iMain_Affections & eTNVSAfn_ProtectFromPK )
	{
		this->HT_vMainChar_SetModelColor( 0.247f, 0.148f, 0.29f, 2.0f );	//	주황
	}
/*
	if(iAffections & eTNVSAfn_Invisible )
	{
		//	WizardEyesSw Check
		if( !(iAffections&eTNVSAfn_WizardEyes) )
		{
			//	은신스킬이 쓰였다면 선택되어진것 전부 풀어준다.
			//this->HT_vOtherObject_SetHideInfomation();
			g_pMainBar->HT_vSetObjectHPOut();
			g_pMainBar->HT_vSetObjectNameOut();
			//	현재 메인캐릭터가 공격하는 캐릭터가 자신이면 공격취소
			//if( g_cMainCharacter->HT_iMainChar_GetAttackTargetKeyID() == m_pObjectInfo->nID )
                g_cMainCharacter->HT_vMainChar_SetAttackCancel( 25 );
		//	this->HT_vOtherObject_SetModelHide( HT_FALSE );
			//	은신만 활성화되고 다른모든것들은 사라지게 처리
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
//	논리적 셀좌표를 반환
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
		case HT_ID_CHARACTER_NAGA:		// 나가
			HT_vMainChar_SetMessage( eMsgCommonTribeNaga, &strTribe); break;
		case HT_ID_CHARACTER_ASURA:		// 아수라
			HT_vMainChar_SetMessage( eMsgCommonTribeAsura, &strTribe); break;
		case HT_ID_CHARACTER_YAKSA:		// 야크샤
			HT_vMainChar_SetMessage( eMsgCommonTribeYaksha, &strTribe); break;
		case HT_ID_CHARACTER_DEVA:		// 데바
			HT_vMainChar_SetMessage( eMsgCommonTribeDeva, &strTribe); break;
		case HT_ID_CHARACTER_KIMNARA:	// 킨나라
			HT_vMainChar_SetMessage( eMsgCommonTribeKimnara, &strTribe); break;
		case HT_ID_CHARACTER_RAKSHASA:	// 락샤샤
			HT_vMainChar_SetMessage( eMsgCommonTribeRakshasa, &strTribe); break;
		case HT_ID_CHARACTER_GANDHARVA: // 간다르바
			HT_vMainChar_SetMessage( eMsgCommonTribeGandharva, &strTribe); break;
		case HT_ID_CHARACTER_GARUDA:	// 가루다
			HT_vMainChar_SetMessage( eMsgCommonTribeGaruda, &strTribe); break;
		case HT_ID_CHARACTER_GM :		// GM
			HT_vMainChar_SetMessage( eMsgCommonTribeGM, &strTribe); break;
		default:						// 운영자
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
	// 최대 HP줄었을 경우 현재 HP 값 조정
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

//	데미지 받는곳->데미지를 받아서 처리
HTvoid HTMainCharacter::HT_nMainChar_SetDemageHP( CHTString strName, HTint iDamageHP )
{
	m_iMainChar_Cur_HP -= iDamageHP;
	if( m_iMainChar_Cur_HP < 0 )
		m_iMainChar_Cur_HP = 0;

	g_pMainBar->HT_vHPUpdate( m_iMainChar_Cur_HP, this->HT_nMainChar_GetMAXHP() );

	//	메시지 뛰움
	CHTString strMessage;
	strMessage.HT_hrCleanUp();
	//char chName[SZNAME_LENGTH];
	//CHTString::HT_hrStringCopy( chName, strName, SZNAME_LENGTH );
	//strMessage.HT_szFormat( "%s에 의해 데미지 %d를(을) 받았습니다.", chName, iDamageHP );
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

	//	status창 HP 값 갱신
	g_pMainBar->HT_vHPUpdate( m_iMainChar_Cur_HP, this->HT_nMainChar_GetMAXHP() );
}

HTvoid HTMainCharacter::HT_vMainChar_SetTotalPrana( HTint iPrana )
{
	// 프라나 획득량 시스템창에 표시
	if( iPrana > m_iMainChar_TotalPrana )
	{
		// 시스템 창에 표시
		HTint iRevPrana = iPrana - m_iMainChar_TotalPrana;
		if( iRevPrana < 0 )
			iRevPrana = 0;
	}
	m_iMainChar_TotalPrana = iPrana;
	//	현재 프라나_UI에 갱신
	g_pMainBar->HT_vPranaUpdate( m_iMainChar_TotalPrana );
}

HTvoid HTMainCharacter::HT_vMainChar_SetBrahman_Rising( PS_SCP_RESP_BRAHMAN_RISING info )
{
	g_oMainCharacterInfo.nBrahmanPoint	=  info->nRisingBrahman;

	// 프라나 획득량 시스템창에 표시
	if( info->nPrana > m_iMainChar_TotalPrana )
	{
		// 시스템 창에 표시
		//HTint nRevPrana = info->nPrana - m_iMainChar_TotalPrana;
		//if( nRevPrana < 0 )
		//	nRevPrana = 0;
		m_iMessageVal = info->nPrana - m_iMainChar_TotalPrana;
		if( m_iMessageVal < 0 )
			m_iMessageVal = 0;

		CHTString szMessage;
		//szMessage.HT_szFormat("프라나 %d을(를) 획득했습니다.", nRevPrana);
		HT_vMainChar_SetMessage( eMsgAttackReceivePrana, &szMessage);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, szMessage );
	}
	m_iMainChar_TotalPrana = info->nPrana;

	//---------정보 셋팅----------//
	g_pMainBar->HT_vHPUpdate(this->HT_nMainChar_GetResentHP(), this->HT_nMainChar_GetMAXHP() );
}

HTvoid HTMainCharacter::HT_vMainChar_NetWork_ChattingMessage( BYTE byType, CHTString strMessage )
{
	//	채팅메시지
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
	//	아이템의 캐스팅 속도를 셋팅
	//	아이템의 공격속도를 셋팅
	HTint iTempValue;
	if( !g_pParamMgr->HT_bGetItemCoolDownTime( dwItemIndex, &iTempValue ) )
		iTempValue = 0;
	m_dwMainChar_AttackItemSpeed = iTempValue;
	//	아이템의 사정거리 셋팅
	if( !g_pParamMgr->HT_bGetItemRange( dwItemIndex, &m_byMainChar_AttackRange_Item ) )
		m_byMainChar_AttackRange_Item = 0;
	//	특별한 아이템에 의한 사정거리 증가가 있는지 체크한다.
	HTint iSpecialRange;
	g_pParamMgr->HT_bGetItemEffect5ID( dwItemIndex, &iSpecialRange );
	if( iSpecialRange == 3160 )		//	Effect No 3160이면 사정거리 증가란다.
	{
		if( g_pParamMgr->HT_bGetItemEffect5Param1( dwItemIndex, &iSpecialRange ) )
			m_byMainChar_AttackRange_Item += iSpecialRange;
	}
    //	아이템의 공격속도 체크
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

	//	활일때는 왼손에 활이 있어야 공격 할수 있다.
	if( CHTParamIDCheck::HT_bIsItemWeaponThrow( dwItemIndex ) )
		m_bMainChar_ItemArrow = HT_TRUE;
	else
		m_bMainChar_ItemArrow = HT_FALSE;

	//	무기에 맞는 애니매이션 셋팅
	this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
}

//----------입는옷 아이템 아이디 셋팅----------------//
HTvoid HTMainCharacter::HT_vMainChar_SetWearItem( DWORD dwItem )
{
	m_dwWearItemID	= dwItem;
}

HTvoid HTMainCharacter::HT_vMainChar_SetWeaponItem( DWORD dwItem )
{
	m_dwWeaponItemID = dwItem;
}

// 캐릭터의 기능성 아이템 유효기간 초기화
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
// 캐릭터의 기능성 아이템의 유효기간
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

//----------캐릭터의 현재 각도를 반환----------------//
HTfloat HTMainCharacter::HT_fMainChar_GetDirectAngle()
{
	return m_cMainCharMove->HT_fGetDirect();
}

//----------랜더 부분----------//
HTvoid HTMainCharacter::HT_vCharRender()
{
	//----------텍스트 랜더 처리----------//
	if( !g_bGamePlayMovieForGlobal )
        HT_vCharRenderText();
}

//----------텍스트 랜더 처리----------//
HTvoid HTMainCharacter::HT_vCharRenderText()
{
	HTvector3 vTextPos = m_cMainCharMove->HT_vecGetPosition();
	vTextPos.y += m_fModelHeight + 3.0f;
	//    -> 색깔 판정
	HTint iColor = 15;
	HT_COLOR cFontColor = HT_COLOR( 0.0f,0.0f,0.0f,0.0f );;
	
	if( m_bMainChar_ShowNameSw ==HT_TRUE &&
		(m_iMain_Affections & eTNVSAfn_Invisible) == 0 )
	{
		//	비류성 지역일때
		if( HT_SUCCEED( HT_IS_BIRYUCASTLE( g_wResentZoneServerID ) ) &&
			m_byMainChar_Clan >= 19 )
		{
			//	수성
			if( m_byMainChar_Clan == 19 )		cFontColor = HT_COLOR( 0.59f, 0.86f, 0.59f, 1.0f );
			//	공성1
			else if( m_byMainChar_Clan == 20 )	cFontColor = HT_COLOR( 0.99f, 0.54f, 0.57f, 1.0f );
			//	공성2
			else if( m_byMainChar_Clan == 21 )	cFontColor = HT_COLOR( 0.99f, 0.74f, 1.00f, 1.0f );
			//	공성3
			else if( m_byMainChar_Clan == 22 )	cFontColor = HT_COLOR( 0.73f, 0.71f, 0.97f, 1.0f );
			//	무소속
			else if( m_byMainChar_Clan == 23 )	cFontColor = HT_COLOR( 0.67f, 0.67f, 0.66f, 1.0f );
		}
		//       -> 카오냐? 		-> 빨강
		else if( g_oMainCharacterInfo.snKarma > 0 )			iColor = 11;
		//       -> 보라돌이냐? 	-> 보라
		else if(m_iMain_Affections & eTNVSAfn_PKAttacker )	iColor = 10;
		//       -> 일반			-> 백색
		else												iColor = 15;
		//	Set Color
		if( cFontColor.a == 0.0f )
            cFontColor = g_ColorTable[iColor];

		/*
		//	PC방 이벤트
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

	//	상점모드
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

//	캐릭터 색깔 변화주기
HTvoid HTMainCharacter::HT_vMainChar_SetModelColor( HTfloat r, HTfloat g, HTfloat b, HTfloat fTime )
{
	//	플리커
    g_pEngineHandler->HT_hrFlickerObject( m_iMainChar_ModelID, HT_COLOR( r, g, b, 1.0f ), fTime );
}

//----------이동경로 저장----------//
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

//----------이동경로 반환----------//
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
// 네트위크와 관련하여
//---------------------------------------------//
//----------서버에서 패킷 내려받기-이동 실패----------//
HTvoid HTMainCharacter::HT_vMainChar_NetWorkMoveFaild( PS_SCP_RESP_CHAR_MOVE info )
{
	m_cMainCharMove->HT_vMainCharMove_NetWorkMoveFaild( info->snX, info->snZ );

	//----------위치와 회전 셋팅----------//
	HTvector3 vecTemp = m_cMainCharMove->HT_vecGetPosition();
	g_pEngineHandler->HT_hrMoveObject( m_iMainChar_ModelID, vecTemp );

	//-----화면이 하얗게 변하는 에러를 막는 변수-----//
	m_bMainChar_WhiteError			= HT_TRUE;
}

HTvoid HTMainCharacter::HT_vNetWork_CheckCharMove()
{
	HT_CELL_COORD codCell;
	float fx, fz;
	HTint iMoveTerm;

	HTvector3 vecTempPos = m_cMainCharMove->HT_vecGetPosition();

	//	이동할 간격 결정
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

	//	지난번 보낸 좌표와 비교해서 적게 이동했으면 보내지 않는다.
	fx = (float)sqrt( double( (vecTempPos.x - m_vecMainChar_ReqSendMovePos.x) * (vecTempPos.x - m_vecMainChar_ReqSendMovePos.x) ) );
	fz = (float)sqrt( double( (vecTempPos.z - m_vecMainChar_ReqSendMovePos.z) * (vecTempPos.z - m_vecMainChar_ReqSendMovePos.z) ) );
	if( fx+fz <  MAP_CELL_SIZE*iMoveTerm )
		return;

	//	타겥 좌표와 비교하여 타겥보다 크면 방향을 계산해서 보내주고 적으면 타갵으로 이동시킨다.
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

	//	서버에 보낸 좌표를 저장해 둔다.
	if( m_bMainChar_WalkRun_Sw == HT_FALSE )
		this->HT_vNetWork_Send_MSGAction( 2, codCell.x, codCell.y );
	else
		this->HT_vNetWork_Send_MSGAction( 3, codCell.x, codCell.y );
	m_vecMainChar_ReqSendMovePos = vecTempPos;
}

//----------캐릭터 이동을 브로드 캐스팅하기 위한 패킷_Send----------//
HTvoid HTMainCharacter::HT_vNetWork_Send_MSGAction( BYTE byEffect, HTint iEndX, HTint iEndZ )
{
	//	Effect of MSG_Action
	if( m_iMain_ActionEffect == 7 )
		return;

	//	도발
	if( byEffect == 8 )
	{
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_PROVOKE;
		this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
	}
	//	인사
	else if( byEffect == 9 )
	{
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_BOW;
		this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
	}
	//	돌격
	else if( byEffect == 10 )
	{
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_CHARGE;
		this->HT_vMainChar_SetChangeAni( 0x00, 1, 0.0f, 0, 0 );
	}

	//	이동 메시지 서버에 올릴때 그때의 위치 저장
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
	////-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MsgAction : x:%d,z:%d-x:%d,z:%d", info->PosX, info->PosY, info->TargetX, info->TargetY );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}

//----------캐릭터 이동을 브로드 캐스팅하기 위한 패킷_Recive----------//
HTvoid HTMainCharacter::HT_vNetWork_Recive_MSGAction( MSG_Action *info )
{
	//	캐릭터 활성화 모드로....
	if( m_iMainChar_Cur_HP != 0 )
        m_bMainChar_Live = HT_TRUE;

	//	우선 Cell 좌표와 Coord 좌표를 구한다.
	HTvector3 vecTempPos;
	HT_CELL_COORD crdCell;
	crdCell.x = info->TargetX;
	crdCell.y = info->TargetY;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( vecTempPos, crdCell );

	//	핸재의 나의 좌표
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();

	//	Effect of MSG_Action
	m_iMain_ActionEffect = info->Effect;

	////	0:앉기
	//if( info->Effect == 0 )
	//{
	//	//	Move Action On/Off Check
	//	m_bMainChar_MoveSw = HT_TRUE;
	//	//	현재 서기모드로 전환해주고,
	//	m_bMainChar_SitSw = HT_FALSE;
	//	//	앉기 셋팅
	//	this->HT_vMainChar_SetSit();
	//}
	////	1:서기
	//else if( info->Effect == 1 )
	//{
	//	//	Move Action On/Off Check
	//	m_bMainChar_MoveSw = HT_TRUE;
	//	//	현재 서기모드로 전환해주고,
	//	m_bMainChar_SitSw = HT_TRUE;
	//	//	앉기 셋팅
	//	this->HT_vMainChar_SetSit();
	//}
	////	2:걷기
	//else if( info->Effect == 2 )
	//{
	//	if( pPt.x != crdCell.x || pPt.y != crdCell.y )
	//	{
	//		m_bMainChar_WalkRun_Sw = HT_TRUE;
	//		this->HT_vMainChar_SetMoveType();
	//		//	Move Action On/Off Check
	//		m_bMainChar_MoveSw = HT_FALSE;
	//		//	캐릭터 이동 관련_맵픽을하여 타겥 지정
	//		this->HT_vMainChar_SetTargetMovePosition( crdCell, HT_TRUE );
	//	}
	//}
	////	3:뛰기
	//else if( info->Effect == 3 )
	//{
	//	if( pPt.x != crdCell.x || pPt.y != crdCell.y )
	//	{
	//		m_bMainChar_WalkRun_Sw = HT_FALSE;
	//		this->HT_vMainChar_SetMoveType();
	//		//	Move Action On/Off Check
	//		m_bMainChar_MoveSw = HT_FALSE;
	//		//	캐릭터 이동 관련_맵픽을하여 타겥 지정
	//		this->HT_vMainChar_SetTargetMovePosition( crdCell, HT_TRUE );
	//	}
	//}
	//	4:날기
	if( info->Effect == 4 )
	{
		//	hmm.....임시로 뛰기모드로 설정
		m_bMainChar_WalkRun_Sw = HT_FALSE;
		this->HT_vMainChar_SetMoveType();
		//	Move Action On/Off Check
		m_bMainChar_MoveSw = HT_FALSE;
		//	캐릭터 이동 관련_맵픽을하여 타겥 지정
		this->HT_vMainChar_SetTargetMovePosition( crdCell, HT_TRUE );
		//	Ani Setting
		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
	}
	//	5:텔레포트
	else if( info->Effect == 5 )
	{
		//	Setting	Targetting
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();
		//	Move Action On/Off Check
		m_bMainChar_MoveSw = HT_TRUE;
		m_cMainCharMove->HT_vMainCharMove_NetWorkMoveFaild( info->TargetX, info->TargetY );
		//	위치와 회전 셋팅
		this->HT_vMainChar_SetCharacterPosition( info->TargetX, info->TargetY, 1 );
		m_bMainChar_SitSw = HT_FALSE;
	}
	//	6:밀리기(knock-back)
	else if( info->Effect == 6 )
	{
		//	공격중이면 취소
		if( m_bMainChar_AttackSw )
			this->HT_vMainChar_SetAttackCancel( 20 );

		//	Move Action On/Off Check
		m_bMainChar_MoveSw = HT_FALSE;
		m_nMainChar_AniResentState = CHARACTER_ANISTATE_HIT;
		this->HT_vMainChar_SetChangeAni( 0x01, 1, 0.0f, 0, 0 );
		m_cMainCharMove->HT_vMainCharMove_CheckTargetCell( vecTempPos, CHARACTER_SPEEDLEVEL_KNOCKBACK );

		//	각도를 방향을 반대로 돌려준다.
		HTfloat fCharAngle = m_cMainCharMove->HT_fGetDirect();
		if( fCharAngle > HT_PIX2 )
			fCharAngle -= HT_PI;
		else
			fCharAngle += HT_PI;
		m_cMainCharMove->HT_fSetDirect( fCharAngle );
	}
	//	7:미끄러지기(이동애니없음)
	else if( info->Effect == 7 )
	{
		m_bMainChar_WalkRun_Sw = HT_FALSE;
		this->HT_vMainChar_SetMoveType();
		//	Move Action On/Off Check
		m_bMainChar_MoveSw = HT_FALSE;
		//	캐릭터 이동 관련_맵픽을하여 타겥 지정
		this->HT_vMainChar_SetTargetMovePosition( crdCell, HT_TRUE );
		//	Ani Setting
		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_STD;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
	}
	//	8:도발
	else if( info->Effect == 8 )
	{
		g_cCommand->HT_vCommand_Provoke();
	}
	//	9:인사
	else if( info->Effect == 9 )
	{
		g_cCommand->HT_vCommand_Greet();
	}
	//	10:돌격
	else if( info->Effect == 10 )
	{
		g_cCommand->HT_vCommand_Rush();
	}
	//	11:가속도 돌진
	else if( info->Effect == 11 )
	{
		///	실재 공격 인덱스 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
		m_iMainChar_RealAttackIndex = 1;
		m_bMainChar_AttackSw = HT_FALSE;
		//	Move Action On/Off Check
		m_bMainChar_MoveSw = HT_FALSE;
		m_bMainChar_WalkRun_Sw = HT_FALSE;
		this->HT_vMainChar_SetMoveType();
		m_nMainChar_AniResentState	= CHARACTER_ANISTATE_RUN;
		this->HT_vMainChar_SetChangeAni( 0x00, -1, 0.0f, 0, 0 );
		m_cMainCharMove->HT_vMainCharMove_CheckTargetCell( vecTempPos, CHARACTER_SPEEDLEVEL_ZUBAS );


		////	실재 공격 인덱스 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
		//m_iMainChar_RealAttackIndex = 1;
		////	기존속도는 저장하고 빠른 속도를 입력한다.
		//m_iMinaChar_TempSpeedForMSGAEffect = m_cMainCharMove->HT_iMainCharMove_GetSpeed( 0x02 );
		//m_cMainCharMove->HT_vSetMiddleMoveSpeed( 40 );

		//m_bMainChar_WalkRun_Sw = HT_FALSE;
		//this->HT_vMainChar_SetMoveType();
		////	Move Action On/Off Check
		//m_bMainChar_MoveSw = HT_FALSE;
		////	캐릭터 이동 관련_맵픽을하여 타겥 지정
		//this->HT_vMainChar_SetTargetMovePosition( crdCell, HT_TRUE );
	}

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Char_MSG_Action MainChar Effect:%d", info->Effect );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid HTMainCharacter::HT_vMainChar_NetWorkDieMotion()
{
	//	이펙트 꺼주기
	if( m_iMain_FaintingstateFX )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iMain_FaintingstateFX );
		m_iMain_FaintingstateFX = 0;
	}

	//	맵 이펙트를 꺼고
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

//----------서버에서 패킷 내려받기-캐릭터 사망시 이닛 리젼요청 결과----------//
HTvoid HTMainCharacter::HT_vMainChar_SCP_INIT_REGEN_CHAR( HTint nX, HTint nZ )
{
	m_bMainChar_Live = HT_TRUE;
	m_bMainChar_SitSw = HT_FALSE;
	m_bMainChar_Reviving = HT_FALSE;	// 사무다바 부활스킬 사용수락중 ESC키를 눌러 확인창이 뜨는걸 막기 위해 사용할 맴버변수
	
	//----------캐릭터의 리젼이나 포탈 이동등으로 바뀐 캐릭터의 위치 지정----------//
	HT_vMainChar_SetCharacterPosition( nX, nZ, 0 );
}

//----------캐릭터의 리젼이나 포탈 이동등으로 바뀐 캐릭터의 위치 지정----------//
HTvoid HTMainCharacter::HT_vMainChar_SetCharacterPosition( HTint nX, HTint nZ, HTint iPosType )
{
	//---------캐릭터 위치 셋팅---------//
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

		//	생성시의 이펙트
		HTint idFx;
		g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWBORN, m_iMainChar_ModelID, HT_FALSE );
	}

	vecPos = HT_vecGetPosition();
	g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_CENTERCHARACTER, vecPos, 0, 0.0f );
	g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_CENTERCHARACTER, vecPos, 0, 0.0f );

	//	BGM 컨트롤 함수
	HTint iMapID = g_wResentZoneServerID + ZONEVALUE_CLIENT_SERVER;
	g_cMapInfo->HT_vBGMControl( iMapID );
}

//	캐릭터가 맵에 갖혔을때 빠져나오기
HTvoid HTMainCharacter::HT_vMainChar_EscapeCharacterFromNotMoveZone()
{
	if( g_iInationalType == INATIONALTYPE_JAPEN )
		return;

	//	알잖아!
    if( m_iMain_Affections & eTNVSAfn_Stun || 
		m_iMain_Affections & eTNVSAfn_Sleep ||
		m_iMain_Affections & eTNVSAfn_Hold )
		return;

	HTvector3 vecPos = m_cMainCharMove->HT_vecGetPosition();

	HTint iCount = 0;

	while(1)
	{
		//	동체크
		if( HT_SUCCEED( m_cMainCharMove->HT_hrMainCharMove_CanPos( HTvector3( vecPos.x+(iCount*MAP_CELL_SIZE), vecPos.y, vecPos.z ) ) ) )
		{
			iCount++;
			vecPos.x += (iCount*MAP_CELL_SIZE);
			break;
		}
		//	서체크
		if( HT_SUCCEED( m_cMainCharMove->HT_hrMainCharMove_CanPos( HTvector3( vecPos.x-(iCount*MAP_CELL_SIZE), vecPos.y, vecPos.z ) ) ) )
		{
			iCount++;
			vecPos.x -= (iCount*MAP_CELL_SIZE);
			break;
		}
		//	남체크
		if( HT_SUCCEED( m_cMainCharMove->HT_hrMainCharMove_CanPos( HTvector3( vecPos.x, vecPos.y, vecPos.z+(iCount*MAP_CELL_SIZE) ) ) ) )
		{
			iCount++;
			vecPos.z += (iCount*MAP_CELL_SIZE);
			break;
		}
		//	북체크
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
	//	셀 위치
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

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Skill_Ready_Start" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );
}

//	Area Skill Start Brodcast
HTvoid HTMainCharacter::HT_vMainChar_CSP_AreaSkill_Start( DWORD dwSkillID, DWORD dwTargetKeyID, HTvector3 vecTargetPos, BYTE bySkillType )
{
	//	셀 위치
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

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Skill_Ready_Start" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );
}

//	서버에 액티브 스킬(단수) 적용 요청
HTvoid HTMainCharacter::HT_vMainChar_CSP_Cast_Unit_Cast()
{
	//	셀 위치
	HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();

	PS_CSP_CAST_UNIT_SKILL info = HT_NULL;
    info = new S_CSP_CAST_UNIT_SKILL;
	memset( info, 0, sizeof(PS_CSP_CAST_UNIT_SKILL) );

	info->snRes = 0;
	info->snSkillID			= (short)m_dwMainChar_ActiveSkillCurIndex;		// cast한 skill ID		
	info->snCasterKeyID		= m_iMainChar_KeyID;					// Caster handle
	info->kTarget.snKeyID	= m_iMainChar_KeyID;					// Target handle
	info->snCasterX			= pPt.x;
	info->snCasterZ			= pPt.y;
	info->snMapX			= pPt.x;
	info->snMapZ			= pPt.y;
	info->snPackCount		= -1;
	g_pNetWorkMgr->RequestSkillCastUnitSkill( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Skill_Cast_Unit_Skill" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	서버에 액티브 스킬(복수) 적용 요청
HTvoid HTMainCharacter::HT_vMainChar_CSP_Cast_Area_Cast()
{
	//	셀 위치
    HTPoint pPt = m_cMainCharMove->HT_ptGetCellPosition();
	HTint	iElement[TN_MAX_TARGET_COUNT];
	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
		iElement[i] = 0;

	//	범위를 구해오고
	HTint iAOE;
	g_pParamMgr->HT_bGetPCSkillAreaOfEffect( m_dwMainChar_ActiveSkillCurIndex, m_byMainChar_ActiveSkillCurLevel, &iAOE );

	//	파티 스킬일때는 파티원 아이디를 넣어준다.
	if( m_dwMainChar_ActiveSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOPARTY )
	{
		g_cParty->HT_vParty_GetPartyMemberKeyID( iElement, (HTfloat)(iAOE*MAP_CELL_SIZE) );
	}
	//	일반 범위일때는 범위내의 오브젝트의 아이디를 넣어준다.
	else
	{
		//	해당 OtherObject들을 구해오고
		HTbyte byGoodType;
		g_pParamMgr->HT_bGetPCSkillType( m_dwMainChar_ActiveSkillCurIndex, 1, &byGoodType );
		g_cOtherObjectSystem->HT_vOtherObjectSystem_GetTerritoryArea( m_cMainCharMove->HT_vecGetPosition(), (HTfloat)(iAOE*MAP_CELL_SIZE), m_dwMainChar_ActiveSkillCurIndex, m_iMainChar_ModelID, m_iMainChar_KeyID, byGoodType, iElement );
	}

	PS_CSP_CAST_AREA_SKILL info = HT_NULL;
    info = new S_CSP_CAST_AREA_SKILL;

    memset( info, 0, sizeof(S_CSP_CAST_AREA_SKILL) );

	info->snRes = 0;
	info->snSkillID			= (short)m_dwMainChar_ActiveSkillCurIndex;		// cast한 skill ID		
	info->snCasterKeyID		= m_iMainChar_KeyID;					// Caster handle
	info->snCasterX			= pPt.x;								// Caster의 현재 x 좌표
	info->snCasterZ			= pPt.y;								// Caster의 현재 y 좌표
	info->snMapX			= pPt.x;								// Map의 현재 x 좌표
	info->snMapZ			= pPt.y;								// Map의 현재 y 좌표

	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
	{
        info->krgTarget[i].snKeyID = iElement[i];
	}

	g_pNetWorkMgr->RequestSkillCastAreaSkill( info );

	//-----디버깅 테스트를 위하여-----//
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

//	서버에서 캐스트스킬(단수) 적용을 알려옴
HTvoid HTMainCharacter::HT_vMainChar_SCP_Skill_CastSkill_Broadcast( PS_CSP_CAST_UNIT_SKILL info )
{
	if( info->snRes != 0 )
		return;

	HTvector3 vecTargetPos;
	vecTargetPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( info->kTarget.snKeyID );

	//	커리티컬힛일때 이펙트
	if( info->kTarget.byRes == 1 )
	{
		HTint iTargetModelID = 0;
		iTargetModelID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( info->kTarget.snKeyID );
		HTint idFx;
		g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_CRITICALIMPACT, iTargetModelID, HT_FALSE );
	}
	//	쿨티암 실패시 메시지 출력후 리턴
	else if( info->kTarget.byRes == 102 )
	{
		//	선미야 메시지 추가다.
		CHTString strMsg;
		strMsg = _T("쿨타임 제한에 의해 적용 실패했습니다.");
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
		return;
	}

	//	0:나쁜것, 1:좋은것
	HTbyte bySkillType = 0;
	if( info->snSkillID )
	{
		g_pParamMgr->HT_bGetPCSkillType( info->snSkillID, 1, &bySkillType );

		//	나의스킬 셋팅
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

	//	숫자 / 메시지 셋팅
	if( info->kTarget.snKeyID != m_iMainChar_KeyID &&
		bySkillType == 0 )
	{
		//	Hit Message Set
		CHTString strMsg;
		if( info->kTarget.byRes == 0 ||
			info->kTarget.byRes == 1 )
		{
			//char* szName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->kTarget.snKeyID );
            // %s에게 데미지 %d를 입혔습니다.", szName,  info->kTarget.iDamage
			m_iMessageVal = info->kTarget.iDamage;
			m_szEnemyName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->kTarget.snKeyID );
			HT_vMainChar_SetMessage( eMsgAttackSendDamage, &strMsg );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strMsg );
		}
		//	회피 메시지
		else if( info->kTarget.byRes == 2 )
		{
			//char* szName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->kTarget.snKeyID );
			m_szEnemyName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->kTarget.snKeyID );
			// %s가 공격을 피했습니다.", szName 
			HT_vMainChar_SetMessage( eMsgAttackEnemyDodge, &strMsg );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
		}
	}
	
	//	화살일때 겟수 카운팅해주기 - 0이면 공격취소
	if( info->snPackCount != -1 )
	{
		if( m_bMainChar_ItemArrow )
		{
			HTdword dwItemKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND );
			g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( dwItemKeyID, (HTbyte)info->snPackCount );
			if( info->snPackCount == 0 )
			{
				// 아이템 인덱스를 원래 아이템을 지우기 전에 구한다.
				HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
				// 모두 사용한 화살 아이템 지우기
				g_cItemSystem->HT_vItemSystem_DeleteItem( dwItemKeyID );

				// 화살 자동 채우기
				if( g_cItemControl->HT_bItemControl_RefillArrow( dwItemKeyID, dwItemIndex ) == HT_FALSE )
				{
					this->HT_vMainChar_SetAttackCancel( 21 ); // 공격상태 취소
					// 왼쪽에 양손아이템 비트맵 그리기
					g_cEquipInventory->HT_vEquipInventory_SetLeftItem( 0 );

					DWORD dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
					if( dwKeyID > 0 )
					{
						DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
						if( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( dwIndex )	|| CHTParamIDCheck::HT_bIsItemWeaponThrow( dwIndex ) )
						{
							// 이미지 그리기
							// 투명바 그리기
						}
					} // end of if( dwKeyID > 0 )
				}
			}
		}
	}

	if( info->kTarget.iHP <= 0 )
	{
		this->HT_vMainChar_SetAttackCancel( 23 );
		//	타켙도 초기화
		m_iMainChar_Target_KeyID = 0;
		//	주신전지역에서 어뷰져의 방지를 위하여 "XX가 XX에게 승리하였씁니다."
		if( SERVEROBJECT_IS_CHARACTER( info->kTarget.snKeyID ) )
		{
			if( HT_FAILED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) &&
				HT_FAILED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
			{
				if( g_cStatus->HT_iGetKarmaPoint() == 0 &&
					g_pDuelSystem->HT_byDuel_GetDuelMode() != eChallenge_Combat )
				{
					// 카르마 포인트를 없애려면 자신보다 강한 몬스터를 사냥해야 합니다.
					if (g_iInationalType != INATIONALTYPE_KOREA)
					{
						//	공지창 켬
						g_pNotifyWindow->HT_vNotify_SetOn();
						CHTString strMessage;

						HT_vMainChar_SetMessage( eMsgCharacterCarmaUp, &strMessage );
						g_pNotifyWindow->HT_vNotify_SetText( strMessage.HT_szGetString() );
					}
					else
					{
						//_DIALOG_PK_NOTICE PK 안내
					}
				}
			}
		}
	}

	//	Cur TP셋팅해 주기
	g_pMainBar->HT_vMainBar_SetCurTP( info->iCasterTP, 0 );

	//	타겥팅해준다.
	 g_cOtherObjectSystem->HT_vOtherObjectSystem_SetAttackTargetting( info->kTarget.snKeyID );

	//	나의 데이타를 셋팅해준다.
	// 이후 info->iCasterAffection 추가 예정
	this->HT_nMainChar_SetCurHP( info->iCasterHP );
	g_pMainBar->HT_vMainBar_SetCurTP( info->iCasterTP, 0 );

	//	타겥의 데이타를 셋팅해준다.
	PS_SCP_RESP_UPDATE_STATUS pData = NULL;
	pData = new S_SCP_RESP_UPDATE_STATUS;
	pData->snKeyID = info->kTarget.snKeyID;
	pData->iHP = info->kTarget.iHP;
	pData->iAffections = info->kTarget.iAffection;
	pData->snKarma = g_cOtherObjectSystem->HT_vOtherObjectSystem_GetKarma( pData->snKeyID );
	if( pData->snKarma < 0 )	pData->snKarma = 0;
	g_cOtherObjectSystem->HT_vOtherObjectSystem_NetworkUpdateStatus( pData );
	HT_DELETE( pData );

	//	밀어내기 스킬이었을경우에 캐릭터 정지하기
	if( info->snSkillID == 3041 )
		this->HT_vMainChar_SetAttackCancel( 24 );
}

//	서버에서 캐스트스킬(복수) 적용을 알려옴
HTvoid HTMainCharacter::HT_vMainChar_SCP_Skill_CastSkill_Broadcast( PS_CSP_CAST_AREA_SKILL info )
{
	if( info->snRes != 0 )
		return;
    
	//	Cur TP셋팅해 주기
	g_pMainBar->HT_vMainBar_SetCurTP( info->iCasterTP, 0 );

    HTvector3 vecTargetPos;
	PS_SCP_RESP_UPDATE_STATUS pData = NULL;
	pData = new S_SCP_RESP_UPDATE_STATUS;
	//	상대방의 좌표 얻어와서 HitCount 셋팅하기
	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; ++i )
	{
		CHTString strTemp;
		strTemp.HT_szFormat( "%d:%d:%d:%d,",i,info->krgTarget[i], info->krgTarget[i].byRes, info->krgTarget[i].iDamage );
		HT_g_vLogFile( strTemp.HT_szGetString() );

		//	상대방이 존재하고 데미지가 있을때만 들어간다.
		//	데이타를 셋팅해준다.
		if( info->krgTarget[i].snKeyID == m_iMainChar_KeyID )
		{
            this->HT_vMainCHar_SCP_SetAffections( info->krgTarget[i].iAffection );
			//	나의스킬 셋팅
			if( info->snSkillID )
			{
				//	0:나쁜것, 1:좋은것
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

//	Network_불꽃놀이
HTvoid HTMainCharacter::HT_vMainChar_SCP_FireFxBroadcast( PS_SCP_FIRE_FX_BROADCAST info )
{
	//	불꽃놀이 이펙트
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

//	버그
//	1.앉아 있는 상태에서 스킬을 장착하면 장착애니매이션이 나오기 때문에 다시 이동 명령을 내리면 서는 장면이 나온다.
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
		// 지역표시
		m_fIndicateTime = 0.0f;
		m_bAreaIndicated = HT_FALSE;
	}
}

//------- 메세지 출력 ----------//
HTvoid HTMainCharacter::HT_vMainChar_SetMessage( HTint idMessage, CHTString* pszMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	
	// 변수가 3개 일 때
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
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vMainChar_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vMainChar_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
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
		case eMsgParamMyName			: // 내 이름
			*pszParam = g_oMainCharacterInfo.szCharName; 
			break;
		
		// 공격 대상 이름
		case eMsgParamTargetEnemyName	:
		// 나를 공격한 대상 이름
		case eMsgParamEnemyName			: 
			*pszParam = m_szEnemyName; 
			break;

		// 상대방에게 준 데미지
		case eMsgParamSpendingDamage	:
		// 내가 받은 데미지
		case eMsgParamReceivedDamage	:
		// 받은 프라나
		case eMsgParamRecoveryPrana		: 
			pszParam->HT_szFormat("%d", m_iMessageVal ); 
			break;
		
			// 인벤확장 기한
		case eMsgParamLimitInvenDate	:
		{
			tm* psTmTime = localtime( &m_timeMainChar_TimeStamp[eTime_Inven] );
			pszParam->HT_szFormat("%d.%d.%d", psTmTime->tm_year+1900, psTmTime->tm_mon+1, psTmTime->tm_mday );
		}
			break;
		// 개인상점 기한
		case eMsgParamLimitPrivateShopDate :
		{
			tm* psTmTime = localtime( &m_timeMainChar_TimeStamp[eTime_Store] );
			pszParam->HT_szFormat("%d.%d.%d", psTmTime->tm_year+1900, psTmTime->tm_mon+1, psTmTime->tm_mday );
		}
			break;
		case eMsgParamUseShopDate : // 만료일
		{
			tm* psTmTime = localtime( &m_timeMainChar_TimeStamp[m_byTimeArrIndex] );
			
			pszParam->HT_szFormat("%4d.%2d.%2d / %2d:%02d", psTmTime->tm_year+1900, psTmTime->tm_mon+1, psTmTime->tm_mday, psTmTime->tm_hour, psTmTime->tm_min );
		}
		default:
			break;
	}
}