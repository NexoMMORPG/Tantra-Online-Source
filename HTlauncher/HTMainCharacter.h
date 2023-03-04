

#ifndef __HTMAINCHARACTER_H__
#define __HTMAINCHARACTER_H__

#define NEWATTACK_SYSTEM

#include "HTMainCharacterMove.h"

class HTMainCharacter
{
public:
	HTMainCharacter();
	~HTMainCharacter();

	//	캐릭터 삭제
	HTvoid						HT_vMainChar_CleanUp();
	//	캐릭터 생성
    HTvoid						HT_vMainChar_Create();
	//	성별 변환을 위한 캐릭터 삭제/생성
    HTvoid						HT_vMainChar_ChangeSexDelCre( HTshort snTribe, HTbyte byHeadType, HTbyte byFaceType );
	//	기본 데이타 셋팅_공격, 이동, 캐스팅
	HTvoid						HT_vMainChar_BasicInfoSetting();
	//	서버에 영향받지 않는 데이타 초기화
	HTRESULT					HT_hrMainCharInitVariable();
	//	서버에서 초기화 받아서 처리하기
	HTRESULT					HT_hrMainCharInit( HTint iKeyID, HTint iX, HTint iZ, DWORD dwGameTime, HTbyte byClan, HTdword dwTimeStamp[MAX_TIMEITEM]);
	//	최초 한번만 업데이트
	HTvoid						HT_vMainChar_OneTimeUpdate();
	//	메인캐릭터 스케쥴러
	HTvoid						HT_vMainChar_Control( HTfloat fElapsedTime );
	//	MouseLbuttonUp으로 들어오는 곳
	HTvoid						HT_vMainChar_MouseLButtonUpCheck( HT_CELL_COORD, HTbool bTargetEffectSw );
	//	나 자신을 클릭했는지 판단
	HTRESULT					HT_vMainCharMyselfClick();
	//	나 자신의 클릭 해제
	HTvoid						HT_vMainCharMyselfUndoClick();
	//	애니매이션 셋팅
	HTvoid						HT_vMainChar_SetChangeAni( BYTE byAniTable, HTint loop, HTfloat fTime, DWORD dwSkillIndex, HTint iAttackAniCount );
	//	애니매이션 온_애니매이션 포이트 체크
	HTvoid						m_vMainChar_AnmPointCheck();

	//----------캐릭터 공격 관련----------//
	//----------공격 셋팅 ----------//
	HTvoid						HT_vMainChar_SetAttackStatus( DWORD dwTargetKeyID, HTint iModelID, HTbool bForAttack );
	HTvoid						HT_vMainChar_SetAttackCancel( HTint iDebugIndex );
	HTvoid						HT_vMainChar_SetCastCancel();
	//----------공격 컨트롤----------//
	HTvoid						HT_vMainChar_AttackControl();
	//	내가 지금 일반공격인지 스킬공격인지 판단, 캐스팅 시간도 파악
	HTvoid						HT_vMainChar_AttackTypeAndCastTimeCheck();
    //----------공격을 위해 움직이기----------//
	HTvoid						HT_vMainChar_AttackMove();
	//	상대 좌표 추적
	HTvoid						HT_vMainChar_TargetPosCheck();
	//	사정거리 결정
    HTvoid						HT_vMainChar_SetAttackRange();
	//	사정거리 체크
    HTvoid						HT_vMainChar_AttackRangeCheck();
	//	걸치기를 막기위해 중간에 장애물이 있는지 검색
	HTRESULT					HT_hrMainChar_ObstacleCenterCheck( HTvector3 vecTargetPos, HTvector3 vecSourcePos );
	//	실제 공격시에 해줄것들
	HTvoid						HT_vMainChar_RealAttackControl();
	//	공격 마시막 시점에서 무엇을 해야할저 결정
	HTvoid						HT_vMainChar_CheckAttackEnd();
	//----------애니매이션 공격 포인트에서 하는일----------//
	HTvoid						HT_vMainChar_AttackAnmAttackPoint();

	//----------캐릭터 이동 관련_걷기, 뛰기 셋팅----------//
	HTvoid						HT_vMainChar_SetMoveType();
	//	캐릭터 이동 관련_맵픽을하여 타겥 지정
	HTvoid						HT_vMainChar_SetTargetMovePosition( HT_CELL_COORD, HTbool bTargetEffectSw );
	//-----픽 검색_맵에 이펙트 찍기-----//
	HTvoid						HT_vDrawPickMapEffect( HTvector3 );
	//-----픽 검색_맵에 찍은 이펙트 체크하기-----//
	HTvoid						HT_vInterface_Pick_Map_CheckEffect();
	//-----픽 검색_맵에 찍은 이펙트 삭제하기-----//
	HTvoid						HT_vInterface_Pick_Map_DeleteEffect();

	//----------키가 눌러진 상태 체크----------//
    HTvoid						HT_vCharSetKeyDownCheck( HTbool );
	//----------키를 누른상태에서 앞으로 계속 전진----------//
	HTvoid						HT_vCharSetMoveForward_Go( HTfloat fElapsedTime );
	//----------키를 누른상태에서 오른쪽 회전----------//
	HTvoid						HT_vCharSetMoveForward_Right();
	//----------키를 누른상태에서 왼쪽 회전----------//
	HTvoid						HT_vCharSetMoveForward_Left();
    //----------마우스 LButtonDown일때 ----------//
	HTvoid						HT_vMainChar_SetLButtonDown( HTPoint );
	HTvoid						HT_vMainChar_SetLButtonUp( HTPoint );
	HTvoid						HT_vMainChar_SetLButtonMove( HTPoint );
	HTvoid						HT_vMainChar_LButtonDown_Move();
	//----------화면을 중심으로 마우스 포인트의 라디안 값을 구해옴----------//
	HTfloat						HT_vMainChar_GetLButtonDown_Point();

	//----------캐릭터 이동 관련_걷기, 뛰기 관련 애니매이션 셋팅----------//
	HTvoid						HT_vMainChar_SetMoveAnme();
	//----------캐릭터 정지한 상태를 체크하여 정지 애니매이션 셋팅----------//
	HTvoid						HT_vMainChar_StopMoveCheck();
	//----------캐릭터 정지 셋팅----------//
	HTvoid						HT_vMainChar_SetStopMove();
	//----------캐릭터 앉기 관련----------//
	HTvoid						HT_vMainChar_SetSit();
	HTbool						HT_bMainChar_GetSitStatus()			{	return m_bMainChar_SitSw;	};

	//----------이동경로 저장----------//
	HTvoid						HT_vMainChar_MovePathSaved();
	//----------이동경로 반환----------//
	HTvoid						HT_vMainChar_GetMovePath( HTPoint*,  HTint );
	
	//----------아이템 사용 이펙트 셋팅----------//
	HTvoid						HT_vMainChar_SetItemUseEffect();
	//----------방어 애니매이션 셋팅----------//
	HTvoid						HT_vMainChar_SetDefence();

	//--------- 장착한 무기 아이템의 제련에 따른 이펙트 설정 ----------//
	HTvoid						HT_vMainChar_AttachRefineEffect( );

	//	스킬 적용대상 체크
	HTRESULT					HT_bvMainChar_GetPCSkillAllowedTarget( HTint, BYTE );
	//	액션 스킬 셋팅
	HTvoid						HT_vMainChar_SetActionSkill( DWORD dwSkillID );
	//	액션 스킬 셋팅_적용
	HTvoid						HT_vMainChar_SetActionSkillAffect();
	//	액티브 스킬 스케쥴러_StateEffect관리
	HTvoid						HT_vMainChar_ControlActiveSkill_ActivateAndState();
	//	액티브 스킬 셋팅
	HTvoid						HT_vMainChar_SetActiveSkill( DWORD );
	//	액티브 이펙트 켜야 될때_STATE_ONCE_TOME_PERATTACK, PERATTACKED
	HTvoid						HT_vMainChar_SetActiveSkillEffect();
	//	액티브 스킬 정지
	HTvoid						HT_vMainChar_StopActiveSkill();
	
	//----------내가 공격대상인지 파악----------//
	HTvector3					HT_vecMainChar_GetAtkTargetCheck( DWORD );
	//----------공격 받았을때 해줘야 할 일들----------//
	HTvoid						HT_vMainChar_SetDisAttackCheck( HTint iSkillID, HTint iItemID, HTint iInvadeModelID );
	
	HTvoid						HT_vMainChar_ControlAngle( HTfloat fElapsedTime );
	HTvoid						HT_vMainChar_ControlMove( HTfloat fElapsedTime );
	HTvoid						HT_vCharGetInfomation();
	
	HTvoid						HT_vCharSoundControl();


	//	상태가 걸렸을때
	//	은신
	HTvoid						HT_vMainChar_SetTransparency( HTbyte byGMMode, __int64 iAffection );
	//	움직이지 못하게 셋팅
	HTvoid						HT_vMainChar_SetCanNotMove( HTbool bEffectSw );
	//	움직이게 셋팅
	HTvoid						HT_vMainChar_SetCanMove();


	//------------------셋팅 및 반환값들-------------------//
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
	//	일반공격이냐 스킬공격이냐
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

	//	Set 패시브 스킬에 의해 어드밴티지 되는 사정거리
	HTvoid			HT_vMainChar_SetPassiveSkillRange( HTbyte byRange )	{ m_iMainChar_PassiveSkillRange = byRange; };
	//	Set 토템 아이템에 의해 어드밴지지 되는 사정거리
	HTvoid			HT_vMainChar_SetTotemItemRange( HTbyte byRange )	{ m_iMainChar_TotemItemRange = byRange;	};

	HTint						HT_iMainChar_GetAttackPoint();
	HTint						HT_iMainChar_GetDefensePoint();
	
	HTint						HT_nMainChar_GetMAXHP();
	HTvoid						HT_nMainChar_SetMAXHP( HTint nMAXHP );
	HTint						HT_nMainChar_GetResentHP();
	HTvoid						HT_nMainChar_SetDemageHP( CHTString strName, HTint iDemageHP );
	HTvoid						HT_nMainChar_SetCurHP( HTint iCurHP );
	HTfloat						HT_fMainChar_GetDirectAngle();					//----------캐릭터의 현재 각도를 반환----------------//
	BYTE						HT_vMainChar_GetHeadType();

	HTvoid						HT_vMainChar_SetWearItem( DWORD );
	HTvoid						HT_vMainChar_SetArmsType( DWORD );// 아이템 인덱스
	HTvoid						HT_vMainChar_SetWeaponItem( DWORD );
	// 캐릭터의 기능성 아이템 유효기간
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
	//----------랜드----------//
	//-------------------------------//
	HTvoid						HT_vCharRender();
	HTvoid						HT_vCharRenderText();

	//	캐릭터 색깔 변화주기
	HTvoid			HT_vMainChar_SetModelColor( HTfloat r, HTfloat g, HTfloat b, HTfloat fTime );

	//-------------------------------//
	//----------서버와 통신----------//
	//-------------------------------//
	//----------네트윅과 관련하여----------//
	HTvoid				HT_vNetWork_CharSitAndStand();			//----------Move_앉기, 서기 서버에 보내기----------//
	HTvoid				HT_vMainChar_NetWorkMoveFaild( PS_SCP_RESP_CHAR_MOVE );	//	서버에서 이동 실패 내려받기

	HTvoid				HT_vNetWork_CheckCharMove();

	HTvoid				HT_vNetWork_Send_MSGAction( BYTE byDir, HTint iEndX, HTint iEndZ );
	HTvoid				HT_vNetWork_Recive_MSGAction( MSG_Action *info );

	HTvoid				HT_vMainChar_SetBrahman_Rising( PS_SCP_RESP_BRAHMAN_RISING info );
	HTvoid				HT_vMainChar_NetWork_ChattingMessage( BYTE byType, CHTString strMessage );

	//	캐릭터 죽는것 처리
	HTvoid						HT_vMainChar_NetWorkDieMotion();
	HTbool						HT_vMainChar_GetCharLive() { return m_bMainChar_Live; };
	//----------서버에서 패킷 내려받기-캐릭터 사망시 이닛 리젼요청 결과----------//
	HTvoid						HT_vMainChar_SCP_INIT_REGEN_CHAR( HTint nX, HTint nZ );
	
	//----------캐릭터의 리젼이나 포탈 이동등으로 바뀐 캐릭터의 위치 지정----------//
	HTvoid						HT_vMainChar_SetCharacterPosition( HTint nX, HTint nZ, HTint iPosType );

	//	캐릭터가 맵에 갖혔을때 빠져나오기
	HTvoid						HT_vMainChar_EscapeCharacterFromNotMoveZone();

	//--------------------------------------//

	//			0x13 Group ? Combat
	HTvoid				HT_vMainChar_CSP_UnitSkill_Start( DWORD dwSkillID, DWORD dwTargetKeyID, HTvector3 vecTargetPos, BYTE bySkillType );
	HTvoid				HT_vMainChar_CSP_AreaSkill_Start( DWORD dwSkillID, DWORD dwTargetKeyID, HTvector3 vecTargetPos, BYTE bySkillType );
	HTvoid				HT_vMainChar_CSP_Cast_Unit_Cast();
	HTvoid				HT_vMainChar_CSP_Cast_Area_Cast();
	HTvoid				HT_vMainChar_SCP_Skill_CastSkill_Broadcast( PS_CSP_CAST_UNIT_SKILL info );
	HTvoid				HT_vMainChar_SCP_Skill_CastSkill_Broadcast( PS_CSP_CAST_AREA_SKILL info );		//	서버에서 캐스트스킬(복수) 적용을 알려옴

	//	Network_불꽃놀이
	HTvoid				HT_vMainChar_SCP_FireFxBroadcast( PS_SCP_FIRE_FX_BROADCAST info );
	//	Set Item Effect
	HTvoid				HT_vMainChar_SCP_SetItemEffect( HTint iItemID );
	
private:
	HTvoid				HT_vShowArea();
	HTvoid				HT_vUpdateAreaIndicate(HTfloat fElapsedTime);
	//--------------------------------------------------------------
	// 메세지 출력
	//--------------------------------------------------------------
	HTvoid				HT_vMainChar_SetMessage( HTint idMessage, CHTString* pszMessage );
	HTvoid				HT_vMainChar_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

private:

	//	전체 프라나
	HTint						m_iMainChar_TotalPrana;
	DWORD						m_dwWearItemID;

	// 메세지 출력을 위한 변수
	CHTString					m_szEnemyName;	// 공격 대상
	HTint						m_iMessageVal;	// 데미지

	//	캐릭터의 현재 상태를 체크
	HTint						m_iMainChar_MAX_HP;
	HTint						m_iMainChar_Cur_HP;

	//-----애니매이션 컨트롤 위해-----//	
	HTint						m_nMainChar_AnmAttackCount;

	//----------캐릭터 이동 관련----------//
	//-----캐릭터 걷기 뛰기 관련 셋팅-----//
	HTbool						m_bMainChar_WalkRun_Sw;			// HT_FALSE:걷기, HT_TRUE:뛰기

	HTbool						m_bTrrainPick_LoopSw;
	HTint						m_nTrrainPick_ModelID;			// 지형 픽했을때 위치 잡아주는 모델
	HTint						m_nTrrainPick_EffectID;			// 지형 픽했을때 보여지는 효과
	
	//	이동시 회전처리
	HTfloat						m_fMainChar_ShowAngle;
	HTint						m_iMainChar_ProgressAngle;

	// 맵 이펙트가 찍히는 위치를 저장
	HTvector3					m_vecPickMapEffect;
	HTbool						m_bShowMapEffect;
	//	캐릭터 앉기 관련
	HTbool						m_bMainChar_SitSw;
	//	Target Position
	HTvector3					m_vecTargetPosition;
	//	Model Hight
	HTfloat						m_fModelHeight;

	//	Time Check For Skill
	HTbool						m_bMainChar_TimeCheckForSkillStart;

	//	For 액션스킬
	HTint						m_iMainChar_OneClickIndex;				//	OneClick 상태인지 체크
	DWORD						m_bMainChar_ActionSkillIndex;			//	퀵슬롯에서 넘어오는 스킬 번호
	HTint 						m_iMainChar_ReservedActionSkillIndex;	//	퀵슬롯에서 넘어오는 스킬을 예약
	HTbool						m_bMainChar_SetSkillAttackSw;			//	퀵슬롯 F1~F10에 의한 스킬 공격 신호가 들어왔느냐?
	HTbool						m_bMainChar_OnlySkillAttackSw;			//	일반공격 없이 오직 스킬로만 하는 공격이냐?
	HTbool						m_bMainChar_MapPickAttackSw;			//	맵픽한곳에 공격하는 스킬이냐?

	//	For 액티브 스킬
	HTint						m_iMainChar_ActiveSkillIndex;				//	액티브 스킬 시전 인덱스
	DWORD						m_dwMainChar_ActiveSkillCurIndex;			//	현재 발동되는 액티브 스킬 INDEX
	BYTE						m_byMainChar_ActiveSkillCurLevel;			//	현재 발동되는 액티브 스킬 레벨
	HTint						m_iMainChar_ActiveSkillEffectID;			//	액티브 스킬 이펙트 ID
	HTint						m_iMainChar_ActiveSkill_StartTime;			//	액티브 스킬 이펙트 발동 시작 시간
	HTint						m_iMainChar_ActiveSkill_DurationTime;		//	액티브 스킬 지속 시간
	HTdword						m_dwMainChar_ActiveSkillType;				//	액티브 스킬을 위한 플래그

	//	패시브 스킬 사정거리
	HTint						m_iMainChar_PassiveSkillRange;				//	패시브 시킬로 어드밴티지 돼는 사정거리
	//	토템 아이템 사정거리
	HTint						m_iMainChar_TotemItemRange;					//	토템 아이템으로 어드밴티지 돼는 사정거리

	//-----공격을 위한 인자-----//
	HTbool						m_bMainChar_AttackSw;
	HTbool						m_bMainChar_AttackMoveSw;
    HTint						m_iMainChar_Target_KeyID;
	HTint						m_iMainChar_MemoryTargetKeyID;
	HTvector3					m_vecMainChar_TargetPos;				//	공격 대상의 3D 좌표
	HTPoint						m_pMainChar_TargetPos;					//	공격 대상의 셀 좌표
	HTint						m_nMainChar_Attack_Type;				//	일반공격이냐 스킬공격이냐
	HTint						m_nMainChar_AttackAnm;					//	공격 애니매이션 동작 인덱스
	HTint						m_nMainChar_TargetModelID;				//	공격 대상의 모델 아이디
	DWORD						m_dwMainChar_AttackStartTime;
	DWORD						m_dwMainChar_AttackSendNetworkTime;		//	서버에 공격 메시지 전달
	DWORD						m_dwMainChar_AttackSpeed;
	DWORD						m_dwMainChar_AttackItemSpeed;			//	아이템 기본 공격 속도
	DWORD						m_dwMainChar_AttackItemSpeedUp;			//	보조 재료에 의한 속도
	DWORD						m_dwMainChar_AttackSkillActionSpeed;
	DWORD						m_dwMainChar_AttackSkillActivateSpeed;
	HTint						m_byMainChar_AttackRange;				//	사정거리
	BYTE						m_byMainChar_AttackRange_Item;			//	사정거리_아이템
	HTint						m_iMainChar_AttackRange_ActionSkill;	//	사정거리_스킬
	BYTE						m_byMainChar_AttackRange_ActivateSkill;	//	사정거리_스킬
	P_ATTACK_FACTOR				m_sMainChar_AttackFactor;
	HTint						m_iMainChar_RealAttackIndex;			//	실재 공격 인덱스 1:Ready, 2:Cast, 3:Apply, 4:AttackEnd
	HTint						m_iMainChar_CastEffectID;
	HTint						m_iMainChar_ReadyStartTime;				//	Ready 시작 시간
	HTint						m_iMainChar_ReadyGaterTime;				//	Ready 시간
	HTint						m_iMainChar_CastStartTime;				//	Cast  시작 시간
	HTint						m_iMainChar_CastGaterTime;				//	Cast  시간
	HTint						m_iMainChar_ApplyStartTime;				//	Apply 시작 시간
	HTint						m_iMainChar_ApplyGaterTime;				//	Apply 시간

	HTint						m_iMainChar_CastGaterTime_Item;			//	캐스트 기모아야 될 시간_아이템
	HTint						m_iMainChar_CastGaterTime_ActionSkill;	//	캐스트 기모아야 될 시간_스킬
	DWORD						m_dwMainChar_CastGaterTime_ActivateSkill;//	캐스트 기모아야 될 시간_스킬
	BYTE						m_byMainChar_CriticalHit;
	HTint						m_iMainChar_MaxDamage;
	//	목표물에게 다가가기:1, 멀어지기:2
	HTint						m_bMainChar_GoTargetIndex;
	//	목표물에게 다가가기 계산한 빈도수
	HTint						m_iMainChar_GoTargetCount;
	//	목표물에게 다가가기 계산한 빈도수의 누적
	HTint						m_iMainChar_GoTargetAccumulationCount;
	//	공격대상의 Size
	HTbyte						m_byMainCHer_TargetSize;
	//	Attack Point 수행 여부
	HTbool						m_bMainChar_AttackPointSw;

	//	10셀 단위로 이동 좌표를 서버에 보내주기 위한 변수
	HTvector3					m_vecMainChar_MoveTargetPos;
	HTvector3					m_vecMainChar_MoveResentPos;
	HTbool						m_bMainChar_MoveTargetCheckSw;

	HTvector3					m_vecMainChar_ReqSendMovePos;

	//----------마우스 LButtonDown일때 ----------//
	BYTE						m_bMouseLbuttonDownMove_Sw;
	HTfloat						m_fMouseLbuttonDownMove_Angle;
	HTbool						m_bMouseLbuttonDownMove_SettingSw;

	//-----이동경로 저장-----//	
	HTPoint						m_pMainChar_MovePath[1000];
	HTint						m_nMainChar_MoveStart;
	HTint						m_nMainChar_MoveResent;
	HTbool						m_bMainChar_OneTimeRotate;
	HTint						m_nMainChar_MovePathCount;

	//-----공격 받았을 때의 HP 상태 체크-----//	
	HTbool						m_bMinaChar_HitDamage;

	//-----아이들 동작을 위해-----//
	DWORD						m_dwMainChar_IdlTime;

	//-----앉기 동작 딜레이를 위해-----//
	DWORD						m_dwMainChar_sitTime;

	//-----화면이 하얗게 변하는 에러를 막는 변수-----//
	HTbool						m_bMainChar_WhiteError;

	//-----앉아 있을때 맵픽하면 맵픽위치 저장-----//
	HT_CELL_COORD				m_crdSitCell;

	//-----내가친 채팅 메시지-----//
	CHTString					m_strMainChar_ChatMsg;
	DWORD						m_dwMainChar_ChatMsgDelayTime;

	//-----내가친 채팅 메시지-----//
	HTbool						m_bMainChar_ShowNameSw;

		// Area Indicate
	HTint						m_iPrevArea;
	HTint						m_iArea;
	CHTString					m_strAreaName;
	HTfloat						m_fIndicateTime;
	HTbool						m_bAreaIndicated;

	// 무기를 뒤로 찼는지에 대한 플래그
	HTbool						m_bIsWeaponArmed;

	//	맞는 동작을 할 수 있는 경우 체크
	HTbool						m_bMainChar_HitEventCanSw;
	//	서기, 걷기, 뛰기, 쉬기, 맞기, 죽기, 앉기, 일으서기, 공격, 후까시, 스킬준비, 스킬모으기, 스킬시전
	HTint						m_nMainChar_AniResentState;
	//	동작중에 다른 이벤트를 받을수 있는것과 없는것 구별
	HTbool						m_bMainChar_AniEventCanSw;
	//	서기 애니매이션을 체크 해야될 애니일경우
	HTbool						m_bMainChar_AniStdCheckSw;
	//	이동 메시지 서버에 올릴때 그때의 위치 저장
	HTPoint						m_pMainChar_SaveMovePos;

	//	Item이 활 일경우
	HTbool						m_bMainChar_ItemArrow;

	HTint						m_iFootSound;
    HSAMPLE						m_hFoootSound;
	//	기절상태 FX
	HTint						m_iMain_FaintingstateFX;
	//	타겥지정 FX
	HTint						m_iMain_TargettingFx;
	//	서버에서 내려오는 캐릭터 상태
	__int64						m_iMain_Affections;
	//	Affections 상태 FX
	HTint						m_iMain_FXAffections;
	//	액티브 이펙트 켜야 될때_STATE_ONCE_TOME_PERATTACK, PERATTACKED
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

	//-----이동 클래스-----//	
	CHTMainCharMove*			m_cMainCharMove;
	HTint						m_byTimeArrIndex;
	//	메인캐릭터 정보
	HTint						m_iMainChar_KeyID;
	DWORD						m_dwWeaponItemID;
	HTint						m_iMainChar_ModelID;
	HTbool						m_bMainChar_Live;
	HTbool						m_bMainChar_Reviving;
	time_t						m_timeMainChar_TimeStamp[MAX_TIMEITEM];
	HTint						m_iGuildSerial;
	//	상점 캐릭터
	HTint						m_iMainChar_ShopCharID;
};

#endif
