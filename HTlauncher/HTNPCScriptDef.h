#ifndef _HTNpcScriptDef_h_
#define _HTNpcScriptDef_h_

#define HT_TYPE_QUESTION			1	// 질의문
#define HT_TYPE_SELECT				2	// 선택문
#define HT_TYPE_STEP				3	// 질의문과 선택문 조합
#define HT_TYPE_QUEST_STEP			4	// 시나리오 퀘스트 스탭

//  언어
#define HT_LANGUAGE_KOREAN			_T("Korean")
#define HT_LANGUAGE_CHINESE			_T("Chinese")		// 중국
#define HT_LANGUAGE_PHILIPPINE		_T("Philippine")	// 필리핀
#define HT_LANGUAGE_INDONESIA		_T("Indonesia")		// 인도네시아
#define HT_LANGUAGE_JAPANESE		_T("Japanese")		// 일본어

//------------------------------------문서의 탭 이름-----------------------------------//
#define HT_NPC_TYPE_NONE			0
#define HT_NPC_TYPE_WEPON			1	// 무기상인
#define HT_NPC_TYPE_DEFENSE			2	// 방어구상인
#define HT_NPC_TYPE_ACCESSORY		3	// 기타용품상인
#define HT_NPC_TYPE_TEMPLE			4	// 승려
#define HT_NPC_TYPE_WAREHOUSE		5	// 물품보관
#define HT_NPC_TYPE_CHIEFGUARD		6	// 수비대장
#define HT_NPC_TYPE_POSTHORSE		7	// 역마꾼
#define HT_NPC_TYPE_ANIMALLEND		8	// 주술사
#define HT_NPC_TYPE_SOLDIER1		9	// 병사1
#define HT_NPC_TYPE_SOLDIER2		10	// 병사2
#define HT_NPC_TYPE_BOY1			11	// 남자아이1
#define HT_NPC_TYPE_GIRL1			12	// 여자아이1
#define HT_NPC_TYPE_QUEST_SOLDIER	13	// 퀘스트용 공동협의체 병사 NPC
#define HT_NPC_TYPE_QUEST_SPORBADA	14	// 퀘스트용 스포르바다 병사 NPC
#define HT_NPC_TYPE_QUEST_BOY		15	// 퀘스트용 스포르바다 아이1
#define HT_NPC_TYPE_BATTLE			16	// 격투장 NPC
#define HT_NPC_TYPE_SAVEPOINT		17	// 위치저장 NPC
#define HT_NPC_TYPE_EVENTNPC		18	// 이벤트 NPC1
#define	HT_NPC_TYPE_RESERVED		19	// (미사용)
#define	HT_NPC_TYPE_ETC				20	
#define HT_NPC_TYPE_EXTRA_ETC2		21	// ETC 확장 NPC2
#define HT_NPC_TYPE_EXTRA_ETC3		22	// ETC 확장 NPC3
#define HT_NPC_TYPE_EXTRA_ETC4		23	// ETC 확장 NPC4
#define HT_NPC_TYPE_EXTRA_ETC5		24	// ETC 확장 NPC5
#define HT_NPC_TYPE_EXTRA_ETC6		25	// ETC 확장 NPC6
#define HT_NPC_TYPE_EXTRA_ETC7		26	// ETC 확장 NPC7

#define HT_RES_TABLENAME_SELECT				_T("Select")
#define HT_RES_TABLENAME_WEAPON				_T("Wepon_Que")		//대장장이
#define HT_RES_TABLENAME_WEAPON_STEP		_T("Wepon_Step")
#define HT_RES_TABLENAME_DEFENSE			_T("Defense_Que")	// 방어구
#define HT_RES_TABLENAME_DEFENSE_STEP		_T("Defense_Step")
#define HT_RES_TABLENAME_ACCESSORY			_T("Accessory_Que")	// 액세서리
#define HT_RES_TABLENAME_ACCESSORY_STEP		_T("Accessory_Step")
#define HT_RES_TABLENAME_TEMPLE				_T("Temple_Que")	// 승려
#define HT_RES_TABLENAME_TEMPLE_STEP		_T("Temple_Step")
#define HT_RES_TABLENAME_WAREHOUSE			_T("Warehouse_Que")	// 교역관
#define HT_RES_TABLENAME_WAREHOUSE_STEP		_T("Warehouse_Step")
#define HT_RES_TABLENAME_CHIEFGUARD			_T("Chiefguard_Que")// 수비대장
#define HT_RES_TABLENAME_CHIEFGUARD_STEP	_T("Chiefguard_Step")
#define HT_RES_TABLENAME_POSTHORSE			_T("PostHorse_Que")	// 역마꾼
#define HT_RES_TABLENAME_POSTHORSE_STEP		_T("PostHorse_Step")
#define HT_RES_TABLENAME_ANIMALLEND			_T("AnimalLend_Que")// 마법동물대여
#define HT_RES_TABLENAME_ANIMALLEND_STEP	_T("AnimalLend_Step")
#define HT_RES_TABLENAME_ETC				_T("Etc_Que")		// 병사1,2, 남자아이1, 여자아이1, 퀘스트용 병사 
#define HT_RES_TABLENAME_ETC_STEP			_T("Etc_Step")
#define HT_RES_TABLENAME_BATTLE				_T("Battle_Que")		// 격투장 NPC	
#define HT_RES_TABLENAME_BATTLE_STEP		_T("Battle_Step")		
#define HT_RES_TABLENAME_SAVEPOINT			_T("SavePoint_Que")		// 위치 저장 NPC	
#define HT_RES_TABLENAME_SAVEPOINT_STEP		_T("SavePoint_Step")
#define HT_RES_TABLENAME_QUEST_STEP			_T("Quest_Step")	// 시나리오 퀘스트 스탭

// ID
// 10000단위로 추가되는 NPC 부여

// 300001 ~ 305000		: 선택문

// 200001 ~ 201000	: 무기상인 step
// 201001 ~ 202000	: 방어구상인 step
// 202001 ~ 203000	: 기타용품상인 step
// 203001 ~ 204000	: 승려 step
// 204001 ~ 205000	: 물품관리 step
// 205001 ~ 206000	: 수비대장 step
// 1000단위로 추가되는 NPC step 부여

//질의문
// 1 ~ 10000			: 무기상인
#define HT_ID_WEPON_QUE_START		1
#define HT_ID_WEPON_QUE_END			10000
// 10001 ~ 20000		: 방어구상인
#define HT_ID_DEFENSE_QUE_START		10001
#define HT_ID_DEFENSE_QUE_END		20000
// 20001 ~ 30000		: 기타용품상인
#define HT_ID_ACCESSORY_QUE_START	20001
#define HT_ID_ACCESSORY_QUE_END		30000
// 30001 ~ 40000		: 승려
#define HT_ID_TEMPLE_QUE_START		30001
#define HT_ID_TEMPLE_QUE_END		40000
// 40001 ~ 50000		: 물품관리
#define HT_ID_WAREHOUSE_QUE_START	40001
#define HT_ID_WAREHOUSE_QUE_END		50000
// 50001 ~ 60000		: 수비대장
#define HT_ID_CHIEFGUARD_QUE_START	50001
#define HT_ID_CHIEFGUARD_QUE_END	60000
//역마꾼
#define HT_ID_POSTHORSE_QUE_START	60001
#define HT_ID_POSTHORSE_QUE_END		70000
//주술사
#define HT_ID_ANIMALLEND_QUE_START	70001
#define HT_ID_ANIMALLEND_QUE_END	80000
// Etc
#define HT_ID_ETC_QUE_START			80001
#define HT_ID_ETC_QUE_END			90000
// 격투장
#define HT_ID_BATTLE_QUE_START		100001
#define HT_ID_BATTLE_QUE_END		110000
// 위치 저장
#define HT_ID_SAVEPOINT_QUE_START	110001
#define HT_ID_SAVEPOINT_QUE_END		120000
/*
//병사1
#define HT_ID_SOLDIER1_QUE_START	80001
#define HT_ID_SOLDIER1_QUE_END		81000
//병사2
#define HT_ID_SOLDIER2_QUE_START	81001
#define HT_ID_SOLDIER2_QUE_END		82000
//남자아이1
#define HT_ID_BOY1_QUE_START		82001
#define HT_ID_BOY1_QUE_END			83000
//여자아이1
#define HT_ID_GIRL1_QUE_START		83001
#define HT_ID_GIRL1_QUE_END			84000
// 스포르바다 병사
QUE_START							84001
QUE_END								85000
//길잃은 아이
QUE_START							85001
QUE_END								86000
*/

// 선택문
#define HT_ID_SELECT_START			300001
#define HT_ID_SELECT_END			400000
// step
#define HT_ID_WEPON_STEP_START		200001
#define HT_ID_WEPON_STEP_END		201000

#define HT_ID_DEFENSE_STEP_START	201001
#define HT_ID_DEFENSE_STEP_END		202000

#define HT_ID_ACCESSORY_STEP_START	202001
#define HT_ID_ACCESSORY_STEP_END	203000

#define HT_ID_TEMPLE_STEP_START		203001
#define HT_ID_TEMPLE_STEP_END		204000

#define HT_ID_WAREHOUSE_STEP_START	204001
#define HT_ID_WAREHOUSE_STEP_END	205000

#define HT_ID_CHIEFGUARD_STEP_START	205001
#define HT_ID_CHIEFGUARD_STEP_END	206000

//역마꾼
#define HT_ID_POSTHORSE_STEP_START	206001
#define HT_ID_POSTHORSE_STEP_END	207000
//주술사
#define HT_ID_ANIMALLEND_STEP_START	207001
#define HT_ID_ANIMALLEND_STEP_END	208000
//Etc
#define HT_ID_ETC_STEP_START		208001
#define HT_ID_ETC_STEP_END			220000

/*
//병사1
#define HT_ID_SOLDIER1_STEP_START	208001
#define HT_ID_SOLDIER1_STEP_END		209000
//병사2
#define HT_ID_SOLDIER2_STEP_START	209001
#define HT_ID_SOLDIER2_STEP_END		210000
//남자아이1
#define HT_ID_BOY1_STEP_START		210001
#define HT_ID_BOY1_STEP_END			211000
//여자아이1
#define HT_ID_GIRL1_STEP_START		211001
#define HT_ID_GIRL1_STEP_END		212000
*/

// 시나리오 퀘스트 스탭
#define HT_ID_QUEST_STEP_START		220001
#define HT_ID_QUEST_STEP_END		221000
//격투장
#define HT_ID_BATTLE_STEP_START		225001
#define HT_ID_BATTLE_STEP_END		226000
//위치저장
#define HT_ID_SAVEPOINT_STEP_START	226001
#define HT_ID_SAVEPOINT_STEP_END	227000

// 질의문
#define HT_IS_WEPON_QUE( i )			( i >= HT_ID_WEPON_QUE_START ) && ( i <= HT_ID_WEPON_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_DEFENSE_QUE( i )			( i >= HT_ID_DEFENSE_QUE_START ) && ( i <= HT_ID_DEFENSE_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ACCESSORY_QUE( i )			( i >= HT_ID_ACCESSORY_QUE_START ) && ( i <= HT_ID_ACCESSORY_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_TEMPLE_QUE( i )			( i >= HT_ID_TEMPLE_QUE_START ) && ( i <= HT_ID_TEMPLE_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_WAREHOUSE_QUE( i )			( i >= HT_ID_WAREHOUSE_QUE_START ) && ( i <= HT_ID_WAREHOUSE_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_CHIEFGUARD_QUE( i )			( i >= HT_ID_CHIEFGUARD_QUE_START ) && ( i <= HT_ID_CHIEFGUARD_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_POSTHORSE_QUE( i )			( i >= HT_ID_POSTHORSE_QUE_START ) && ( i <= HT_ID_POSTHORSE_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ANIMALLEND_QUE( i )			( i >= HT_ID_ANIMALLEND_QUE_START ) && ( i <= HT_ID_ANIMALLEND_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ETC_QUE( i )					( i >= HT_ID_ETC_QUE_START ) && ( i <= HT_ID_ETC_QUE_END ) ? HT_TRUE : HT_FALSE 
/*
#define HT_IS_SOLDIER1_QUE( i )			( i >= HT_ID_SOLDIER1_QUE_START ) && ( i <= HT_ID_SOLDIER1_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_SOLDIER2_QUE( i )			( i >= HT_ID_SOLDIER2_QUE_START ) && ( i <= HT_ID_SOLDIER2_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_BOY1_QUE( i )				( i >= HT_ID_BOY1_QUE_START ) && ( i <= HT_ID_BOY1_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_GIRL1_QUE( i )			( i >= HT_ID_GIRL1_QUE_START ) && ( i <= HT_ID_GIRL1_QUE_END ) ? HT_TRUE : HT_FALSE
*/
#define HT_IS_BATTLE_QUE( i )				( i >= HT_ID_BATTLE_QUE_START ) && ( i <= HT_ID_BATTLE_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_SAVEPOINT_QUE( i )			( i >= HT_ID_SAVEPOINT_QUE_START ) && ( i <= HT_ID_SAVEPOINT_QUE_END ) ? HT_TRUE : HT_FALSE 

//선택문
#define HT_IS_SELECT( i )				( i >= HT_ID_SELECT_START ) && ( i <= HT_ID_SELECT_END ) ? HT_TRUE : HT_FALSE
// STEP
#define HT_IS_WEPON_STEP( i )			( i >= HT_ID_WEPON_STEP_START ) && ( i <= HT_ID_WEPON_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_DEFENSE_STEP( i )			( i >= HT_ID_DEFENSE_STEP_START ) && ( i <= HT_ID_DEFENSE_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ACCESSORY_STEP( i )		( i >= HT_ID_ACCESSORY_STEP_START ) && ( i <= HT_ID_ACCESSORY_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_TEMPLE_STEP( i )			( i >= HT_ID_TEMPLE_STEP_START ) && ( i <= HT_ID_TEMPLE_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_WAREHOUSE_STEP( i )		( i >= HT_ID_WAREHOUSE_STEP_START ) && ( i <= HT_ID_WAREHOUSE_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_CHIEFGUARD_STEP( i )		( i >= HT_ID_CHIEFGUARD_STEP_START ) && ( i <= HT_ID_CHIEFGUARD_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_POSTHORSE_STEP( i )		( i >= HT_ID_POSTHORSE_STEP_START ) && ( i <= HT_ID_POSTHORSE_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ANIMALLEND_STEP( i )			( i >= HT_ID_ANIMALLEND_STEP_START ) && ( i <= HT_ID_ANIMALLEND_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ETC_STEP( i )				( i >= HT_ID_ETC_STEP_START ) && ( i <= HT_ID_ETC_STEP_END ) ? HT_TRUE : HT_FALSE
/*
#define HT_IS_SOLDIER1_STEP( i )		( i >= HT_ID_SOLDIER1_STEP_START ) && ( i <= HT_ID_SOLDIER1_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_SOLDIER2_STEP( i )			( i >= HT_ID_SOLDIER2_STEP_START ) && ( i <= HT_ID_SOLDIER2_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_BOY1_STEP( i )			( i >= HT_ID_BOY1_STEP_START ) && ( i <= HT_ID_BOY1_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_GIRL1_STEP( i )			( i >= HT_ID_GIRL1_STEP_START ) && ( i <= HT_ID_GIRL1_STEP_END ) ? HT_TRUE : HT_FALSE
*/

#define HT_IS_QUEST_STEP( i )				( i >= HT_ID_ETC_STEP_START ) && ( i <= HT_ID_ETC_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_BATTLE_STEP( i )			( i >= HT_ID_BATTLE_STEP_START ) && ( i <= HT_ID_BATTLE_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_SAVEPOINT_STEP( i )		( i >= HT_ID_SAVEPOINT_STEP_START ) && ( i <= HT_ID_SAVEPOINT_STEP_END ) ? HT_TRUE : HT_FALSE

/***************************************************************************************/
//--------- 입력에 의한 다음단계로 전환할 때 -----------//
#define HT_SCRIPT_NEXTSTEP_FAIL			-1
#define HT_SCRIPT_NEXTSTEP_EQUALSTEP	0
#define HT_SCRIPT_NEXTSTEP_SUCCESS		1

// NPC 관련 스크립트를 실행하기 위해 사용되는 정의
//---------------------------------------------------
// parameter
//---------------------------------------------------
#define HT_NPC_PARAM_START			0
#define HT_NPC_PARAM_END			100

typedef enum _eNpcParam
{
	eNpcParamNone				=	0,
	eNpcParamNeedPrana			=	1,	// 필요한 프라나 
	eNpcParamCharacterName		,	// 캐릭터 이름
	eNpcParamTribeName			,	// 종족 이름
	eNpcParamSkillName			,	// 스킬 이름
	eNpcParamChakraName			,	// 차크라 이름
	eNpcParamTrimuritiName		,	// 주신 이름
	eNpcParamGuildName			,	// 길드 이름
	eNpcParamJobName			,	// 직업 이름
	eNpcParamCashRemain			,	// 남은 캐쉬 
	eNpcParamInitializeReqRupia ,	// 차크라/스킬 초기화에 필요한 루피아
	eNpcParamChangeGodReqRupia	,			// 주신변경에 필요한 루피아
	eNpcParamEventItemTotal		,		// 이벤트 아이템 총 갯수
	eNpcParamDurgaState			= 33,		// 요새전 점령 상황
	eNpcParamDurgaReceiptofMoney,			// 요새전 적립된 루피아
	eNpcParamGetMoneyYut		= 40	// 비류성 윳 적립세금(루피아)
} eNpcParam;

//---------------------------------------------------
// server event
//---------------------------------------------------
#define HT_NPC_SEVENT_START			1001
#define HT_NPC_SEVENT_END			3000

typedef enum _eNpcSEvent
{
	eNpcSEventReqNone			=	0,
	eNpcSEventReqItemList		=	1001,	// 아이템리스트 요청
	eNpcSEventReqRank				,	// 순위리스트 요청
	eNpcSEventReqTrimuritiSelect	,	// 주신선택 요청
	eNpcSEventReqTrimuritiChange	,	// 주신변경 요청
	eNpcSEventReqTrimuritiPoint		,	// 주신포인트 변환 요청
	eNpcSEventReqChangeJob			,	// 전직요청
	eNpcSEventReqSkillLearn			,	// 기술습득 요청
	eNpcSEventReqSkillDelete		,	// 기술삭제 요청
	eNpcSEventReqTaskQuest			,	// 테스크 퀘스트 요청
	eNpcCEventReqExpandInven		,	// 인벤토리 확장 (프리미엄 기능) /1010
	eNpcSEventReqExpandPrivateShop	,	// 개인상점 확장 (프리미엄 기능) /1011
	eNpcSEventReqJopChangeInit		,	// 2차전직 초기화(프리미엄 기능) /1012
	eNpcSEventReqCash				,	// 캐쉬요청 /1013
	eNpcSEventReqAutoRouting		,	// 자동 돈줍기 (프리미엄 기능) / 1014
	eNpcSEventReqinitChacra			,	// 차크라 초기화 (프리미엄 기능) / 1015
	eNpcSEventReqinitSkill			,	// 스킬 초기화 (프리미엄 기능) / 1016
	eNpcSEventReqinitChacraSkill	,	// 차크라&스킬 초기화 (프리미엄 기능) / 1017
	eNpcSEventReqEventItemTotal		,	// 이벤트 아이템 적립갯수 요청 /1018 (아이원잇)
	eNpcSEventReqDrugaMoneyOut		,	// 요새전 적립금액 조회 요청 1019
	
	eNpcSEventReqQuestAllow		=	1121,// 퀘스트 승낙요청
	eNpcSEventReqCouponRegister		,	// 쿠폰 등록 요청

	eNpcSEventReqCharacterInitialize2 = 2998,	// 스킬/차크라 재분배 정보 요청 (스킬)
	eNpcSEventReqInitialize = 2999,				// 스킬/차크라 재분배 요청
	eNpcSEventReqCharacterInitialize = 3000	// 스킬/차크라 재분배 정보 요청 (차크라)
	//eNpcSEventReqSkillList	=	110
} eNpcSEvent;

//---------------------------------------------------
// client event
//---------------------------------------------------
#define HT_NPC_CEVENT_START			3001
#define HT_NPC_CEVENT_END			5000

typedef enum _eNpcCEvent
{
	eNpcCEventNone					=	0,
	eNpcCEventDialog				=	3001,	// 대화 모드
	eNpcCEventQuestAllow				,	// 퀘스트 승낙 모드
	eNpcCEventQuestOK					,	// 퀘스트  완료대화종료 모드
	eNpcCEventReqItemList				,	// 구입 대기 모드 - 구입 리스트 만들기
	eNpcCEventItemMake					,	// 구입 모드
	eNpcCEventFix						,	// 수리 모드
	eNpcCEventDisjoint					,	// 해체 모드
	eNpcCEventInventory					,	// 물품보관 모드
	eNpcCEventSavePosition				,	// 위치저장 모드
	eNpcCEventTrimuritiSelect			,	// 주신선택 모드
	eNpcCEventTrimuritiChange			,	// 주신변경 모드
	eNpcCEventCreateGuild				,	// 아쉬람생성 모드
	eNpcCEventCreateGuildMark			,	// 아쉬람마크생성
	eNpcCEventChangeJob2				,	// 2차전직모드
	eNpcCEventReqRank					,	// 순위열람대기모드
	eNpcCEventRank						,	// 순위열람 모드
	eNpcCEventEvent						,	// 이벤트 등록 모드
	eNpcCEventChaturangaBoard			,	// 차투랑가 보드 열람 모드
	eNpcCEventQuiz						,	// 퀴즈 모드 
	eNpcCEventJob2Select				,	// 2차 직업 선택 모드
	eNpcCEventTaskQuest					,	// 테스크 퀘스트 모드 // 3021
	eNpcCEventReqPriItemList			,	// 구입 대기 모드 - 구입 리스트 만들기 (프리미엄 아이템) /3022
	eNpcCEventTransformationShop		,	// 종합 미용실 (프리미엄) /3023
	eNpcCEventCreatePremiumGuildMark	,	// 아쉬람 마크 생성 (프리미엄) /3024
	eNpcCEventCallPaySystem				,	// 전자지불 시스템 호출 (프리미엄) /3025
	eNpcCEventMuUseInfo					,	// 내 사용 내역(프리미엄) /3026
	eNpcCEventReqPriItemList2			,	// 구입 대기 모드 - 구입 리스트 만들기 (프리미엄 패키지 아이템) /3027
	eNpcCEventReqPriItemList3			,	// 구입 대기 모드 - 구입 리스트 만들기 (특수기능 아이템) /3028
	eNpcCEventReqEventItem				,	// 이벤트 아이템 갯수 요청 /3029 (아이원잇)
	eNpcCEventReqEventCoupon			,	// 쿠폰 등록 이벤트 / 3030
	eNpcCEventReqDrugaMoneyIn			,	// 요새전 적립 요청 3031
	eNpcCEventReqYutWindowPopup			,	// 윷놀이 상황판 팝업띄우기 위해 서버로 부터 정보 요청 3032
	eNpcCEventReqCheckWindowPopup		,	// 출석체크 이벤트 윈도우 팝업 요청 (3033)
	eNpcCEventReqComeback				,	// 컴백(초토화) 이벤트 (3034)
	eNpcCEventReqGetYutMoneyList		,	// 성주가 받을 수 있는 윳 세금조회 (3035)
	eNpcCEventReqGetYutMoney			,	// 성주가 받을 수 있는 윳 세금받기 (3036)
	eNpcCEventReqQuestEvent1			,	// 퀘스트 이벤트 북두성군, 북두쭈앙즈 사라짐 처리 (3037)
	eNpcCEventReqQuestEvent2			,	// 퀘스트 이벤트 북두성군, 북두쭈앙즈 사라짐 처리 (3038)
	eNpcCEventReqGuildCargoOpenWindow	,	// 길드창고 팝업요청창1
	eNpcCEventReqGuildCargoShowInfo		,	// 길드창고 팝업요청창2
	eNpcCEventReqGuildCargoSetPMT		,	// 길드창고 팝업요청창3

	eNpcCEventReqRentalAdminSellInfo	,	// 비류성 위탁판매 관리자 (자신의 아이템 판매현황 보기) - 3042 - (판매 리스트창 팝업)
	eNpcCEventReqRentalAdminReciveItem	,	// 비류성 위탁판매 관리자 (자신의 아이템 돌려받기) - 3043 - (보관중인 아이템 찾기요청 패킷 호출)
	eNpcCEventReqRentalAdminReciveList	,	// 비류성 위탁판매 관리자 (자신의 아이템 돌려받을 리스트 보기) - 3044 - (보관중인 리스트창 팝업)
	
	eNpcCEventReqRentalBuyList			,	// 비류성 위탁판매 일반인 (판매중인 아이템 목록보기) - 3045 (위탁상점창 팝업) - 구입모드
	eNpcCEventReqRentalSell				,	// 비류성 위탁판매 일반인 (자신의 아이템 판매) - 3046 (위탁상점창 팝업) - 판매모드
	eNpcCEventReqRentalUsingTex			,	// 비류성 위탁판매 일반인 (위탁판매 이용 세금 설정) - 3047 (스크립트로 출력)
	eNpcCEventReqRentalItemRupia		,	// 비류성 위탁판매 관리자 (위탁판매된 아이템 루피아 보기) - 3048 (스크립트로 출력)
	eNpcCEventReqRentalSetTex		,	// 비류성 위탁판매 일반인 (위탁판매 이용 세금 찾기) - 3049 (스크립트로 출력)

	eNpcCEventCheckTrimuriti		=	3251,	// 주신검사
	eNpcCEventCheckGuild				,	// 아쉬람 검사
	eNpcCEventCheckTrimuritiPoint		,	// 주신포인트 조건검사
	eNpcCEventCheckChangeJob			,	// 전직검사
	eNpcCEventCheckChakraInit			,	// 차크라 초기화 퀘스트 조건 검사
	eNpcCEventCheckSkillInit			,	// 스킬 초기화 퀘스트 조건 검사
	eNpcCEventCheckJob2ChangeItem		,	// 2차 전직용 아이템 검사 // 3257
	eNpcCEventCheckSkillInit2			,	// 스킬 초기화 이벤트 (2006. 1. 9)
	eNpcCEventCheckEvent			=	3259,// 이벤트 등록 조건 검사
		
	eNpcCEventPKStart				=	3260,	// 격투신청
	eNpcCEventPKEnd						,		// 격투취소

	eNpcCEventItemRefine			=	3290,	// 제련모드

	eNpcCEventBramanPointUp				,	// 브라만 포인트 확장
	eNpcCEventChakraUp					,	// 차크라 확장
	eNpcCEventSkillLearn				,	// 기술 습득
	eNpcCEventSkillRemove				,	// 기술 삭제

	eNpcCEventReqUsingItem			=	3295,	// 퀘스트 초기화 NPC 이벤트

	eNpcCEventTaskQuest1			=	4001, // 마라의 혈액류 판매	
	eNpcCEventTaskQuest2				, // 마라 원액 제조		
	eNpcCEventTaskQuest3				, // 파나카류 약품 조제
	eNpcCEventTaskQuest4				, // 카야 합성
	eNpcCEventTaskQuest5				, // 한손 무기 제작
	eNpcCEventTaskQuest6				, // 양손 무기 제작
	// 수집 아이템으로 1차 재료 추출
	eNpcCEventTaskQuest7				, // 가공된 가죽 제작 // 4007
	eNpcCEventTaskQuest8				, // 질긴 가죽끈 제작
	eNpcCEventTaskQuest9				, // 재단용 옷감 제작
	eNpcCEventTaskQuest10				, // 재단용 실 제작
	eNpcCEventTaskQuest11				, // 접착용 아교 제작
	eNpcCEventTaskQuest12				, // 장식용 징1 제작
	eNpcCEventTaskQuest13				, // 장식용 징2 제작 // 4013
	// 방어구 분리를 통한 부분품 추출
	eNpcCEventTaskQuest14				, // 나가, 킨나라용 방어구 분리 // 4014
	eNpcCEventTaskQuest15				,
	eNpcCEventTaskQuest16				,
	eNpcCEventTaskQuest17				, 
	eNpcCEventTaskQuest18				, // 아수라, 락샤샤용 방어구 분리 // 4018
	eNpcCEventTaskQuest19				,
	eNpcCEventTaskQuest20				, 
	eNpcCEventTaskQuest21				,
	eNpcCEventTaskQuest22				, // 야크샤, 간다르바용 방어구 분리 // 4022
	eNpcCEventTaskQuest23				, 
	eNpcCEventTaskQuest24				,
	eNpcCEventTaskQuest25				,
	eNpcCEventTaskQuest26				, // 데바, 가루다용 방어구 분리 // 4026
	eNpcCEventTaskQuest27				,
	eNpcCEventTaskQuest28				,
	eNpcCEventTaskQuest29				,
	// 부분품 분리를 통한 1차 재료 추출
	eNpcCEventTaskQuest30				, // 사트반급 // 4030
	eNpcCEventTaskQuest31				,
	eNpcCEventTaskQuest32				,
	eNpcCEventTaskQuest33				, // 드반타급 // 4033
	eNpcCEventTaskQuest34				,
	eNpcCEventTaskQuest35				,
	eNpcCEventTaskQuest36				, // 너바나급 // 4036
	eNpcCEventTaskQuest37				,
	eNpcCEventTaskQuest38				,
	eNpcCEventTaskQuest39				, // 만트리카급 // 4039
	eNpcCEventTaskQuest40				,
	eNpcCEventTaskQuest41				,
	// 1차 재료로 종족 방어구 부분품 제작
	eNpcCEventTaskQuest42				, // 사트반급 // 4042
	eNpcCEventTaskQuest43				,
	eNpcCEventTaskQuest44				,
	eNpcCEventTaskQuest45				, // 드반타급 // 4045
	eNpcCEventTaskQuest46				,
	eNpcCEventTaskQuest47				,
	eNpcCEventTaskQuest48				, // 너바나급 // 4048
	eNpcCEventTaskQuest49				,
	eNpcCEventTaskQuest50				,
	eNpcCEventTaskQuest51				, // 만트리카급 // 4051
	eNpcCEventTaskQuest52				,
	eNpcCEventTaskQuest53				,
	// 방어구 제작
	eNpcCEventTaskQuest54				, // 나가, 킨나라용 // 4054
	eNpcCEventTaskQuest55				,
	eNpcCEventTaskQuest56				,
	eNpcCEventTaskQuest57				, // 아수라, 락샤샤용 // 4057
	eNpcCEventTaskQuest58				,
	eNpcCEventTaskQuest59				,
	eNpcCEventTaskQuest60				, // 야크샤, 간다르바용 // 4060
	eNpcCEventTaskQuest61				,
	eNpcCEventTaskQuest62				,
	eNpcCEventTaskQuest63				, // 데바, 가루다용 // 4063
	eNpcCEventTaskQuest64				,
	eNpcCEventTaskQuest65				,
	
	// 지나마을 뤼샨 테스크 퀘스트
	eNpcCEventTaskQuest66				,	// 강화제련 향상
	eNpcCEventTaskQuest67				,	// 액세서리 향상

	// 테스크 퀘스트 : 이벤트용 널 퀘스트 
	eNpcCEventTaskQuest68				,	// 10388	만다라 여사제의 퀘스트	1120
	eNpcCEventTaskQuest69				,	// 10389	샴발라 여사제의 퀘스트	1154
	eNpcCEventTaskQuest70				,	// 10390	지나 여사제의 퀘스트	1155
	eNpcCEventTaskQuest71				,	// 10391	유배지 여사제의 퀘스트	1156
	eNpcCEventTaskQuest72				,	// 10392	브라흐마 여사제의 퀘스트	1254
	eNpcCEventTaskQuest73				,	// 10393	비슈누 여사제의 퀘스트	1255
	eNpcCEventTaskQuest74				,	// 10394	시바 여사제의 퀘스트	1256

	// 크리스마스 퀘스트
	eNpcCEventTaskQuest75				,	// 크리스마스 퀘스트 이벤트 

	// 라푸 크리스탈 업그레이드 퀘스트
	eNpcCEventTaskQuest76				,	// 라푸 크리스탈 업그레이드 퀘스트1
	eNpcCEventTaskQuest77				,	// 라푸 크리스탈 업그레이드 퀘스트2

	eNpcCEventTaskQuest78				,	// 라훌 요술주머니 이벤트
	
	eNpcCEventTaskQuest79				,	// 유배지 테퀘 무사용 순례자의 증표
	eNpcCEventTaskQuest80				,	// 유배지 테퀘 술사용 순례자의 증표

	eNpcCEventTaskQuest81				,	// 요새전 만물상 카우스트밤 제작
	eNpcCEventTaskQuest82				,	// 요새전 만물상 카우스트밤을 이용한 아이템 소환

	eNpcCEventTaskQuest83				,	// 라훌 프라다야 교환

	eNpcCEventTaskQuest84				,	// 뤼샨 비르티1 이벤트
	eNpcCEventTaskQuest85				,	// 뤼샨 비르티2 이벤트
	eNpcCEventTaskQuest86				,	// 뤼샨 비르티3 이벤트
	eNpcCEventTaskQuest87				,	// 뤼샨 비르티4 이벤트

	eNpcCEventTaskQuest88				,	// 라훌 속성변경 이벤트
	eNpcCEventTaskQuest89				,	// 라훌 하라티 원석 가공
	
	eNpcCEventTaskQuest90				,	// 요새전 만물상 테퀘

	eNpcCEventTaskQuest91				,	// 라훌

	eNpcCEventTaskQuest92				,	// 북퀘 토용의 장인
	eNpcCEventTaskQuest93				,	// 북퀘 쫑꾸이

	eNpcCEventTaskQuest94				,	// 12차 크리스탈 무기제작 1
	eNpcCEventTaskQuest95				,	// 12차 크리스탈 무기제작 2
	eNpcCEventTaskQuest96				,	// 12차 크리스탈 무기제작 3

	eNpcCEventTaskQuest97				,	// 12월 플래티넘 꾸러미 이벤트

	eNpcCEventTaskQuest98				,	// 드랍 프라나 테스크 퀘스트 // 샴발라성 마호멧
	eNpcCEventTaskQuest99				,	// 드랍 프라나 테스크 퀘스트 // 아누마을 재단사 사라뉴
	eNpcCEventTaskQuest100				,	// 드랍 프라나 테스크 퀘스트 // 지나마을 전투승려 이떵따셔
	eNpcCEventTaskQuest101				,	// 드랍 프라나 테스크 퀘스트 // 지나마을 잡화상인 뤼샨
	eNpcCEventTaskQuest102				,	// 드랍 프라나 테스크 퀘스트 // 유배지 수행승 우쏭
	eNpcCEventTaskQuest103				,	// 드랍 프라나 테스크 퀘스트 // 유배지 창고지기 보오러

	eNpcCEventTaskQuest104				,	// 새해 인사 이벤트

	eNpcCEventTaskQuest105				,	// 1월 플래티넘 꾸러미 이벤트

	eNpcCEventTaskQuest106				,	// 3월 플래티넘 꾸러미 이벤트
	eNpcCEventTaskQuest107				,	// 3월 플래티넘 꾸러미 이벤트(2)
	eNpcCEventTaskQuest108				,	// 4월 플래티넘 꾸러미 이벤트

	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,

	eNpcCEventInformationShow = 4998,		// 여사제에서 정보 게시판 보기
	eNpcCEventInitialize = 4999,
	eNpcCEventCharacterInitialize = 5000

} eNpcCEvent;

//---------------------------------------------------
// condition
//---------------------------------------------------
#define HT_NPC_CONDITION_START			5001
#define HT_NPC_CONDITION_END			6000

#define HT_NPC_RELATIVE_CONDITION_START			5001
#define HT_NPC_RELATIVE_CONDITION_END			5025

#define HT_NPC_JOB_CONDITION_START				5041
#define HT_NPC_JOB_CONDITION_END				5050

#define HT_NPC_TRIBE_CONDITION_START			5054
#define HT_NPC_TRIBE_CONDITION_END				5070

#define HT_NPC_LEVEL_CONDITION_START			5071
#define HT_NPC_LEVEL_CONDITION_END				5100

typedef enum _eNpcCondition
{
	eNpcConditionNone				=	0,

	// 친밀도
	eNpcConditionRelative1			=	5001,	
	eNpcConditionRelative2				,
	eNpcConditionRelative3				,
	eNpcConditionRelative4				,
	eNpcConditionRelative5				,
	eNpcConditionRelative6				,
	eNpcConditionRelative7				,
	eNpcConditionRelative8				,
	eNpcConditionRelative9				,
	eNpcConditionRelative10				,

	eNpcConditionRelative2Over 		=	5021,// 친밀도2이상
	eNpcConditionRelative3Over 			,	// 친밀도3이상
	eNpcConditionRelative4Over 			,	// 친밀도4이상
	// 시간
	eNpcConditionDay				=	5026,// 낮
	eNpcConditionNight					,	// 밤
	// 서버 요청 결과
	eNpcConditionSuccess			=	5028,// 성공
	eNpcConditionFail					,	// 실패
	// 전직
	eNpcConditionChangeJob1			=	5041,// 1차 전직
	eNpcConditionChangeJob2				,	// 2차 전직
	// 직업
	//eNpcConditionJobSatvan			=	5043,// 전사
	//eNpcConditionJobDhvanta				,	// 암살자
	//eNpcConditionJobNirvana				,	// 격투사
	//eNpcConditionJobMantrika			,	// 법사
	eNpcConditionJobSatya			=	5043,// 사트야
	eNpcConditionJobVanare				,	// 바나르
	eNpcConditionJobDruta				,	// 드루타
	eNpcConditionJobKarya				,	// 카르야
	eNpcConditionJobNakayuda			,	// 나카유다
	eNpcConditionJobVaidya				,	// 바이드야
	eNpcConditionJobAbicara				,	// 아비카라
	eNpcConditionJobSamavat				,	// 사마바트 // 5050

	// 종족
	eNpcConditionBrahma				=	5051,	// 브라흐마
	eNpcConditionVishunu				,	// 비슈누
	eNpcConditionSiva					,	// 시바
	eNpcConditionNaga					,	// 나가		
	eNpcConditionAsura					,	// 아수라
	eNpcConditionYaksa					,	// 야크샤
	eNpcConditionDeva					,	// 데바
	eNpcConditionKimnara				,	// 킨나라
	eNpcConditionRakshasa				,	// 락샤샤
	eNpcConditionGandharva				,	// 간다르바
	eNpcConditionGaruda					,	// 가루다
	// 레벨
	eNpcConditionLevel10Under		=	5071,	// 10레벨 미만
	eNpcConditionLevel10Over			,	// 10레벨 이상
	eNpcConditionLevel30Under			,	// 30레벨 미만
	eNpcConditionLevel30Over			,	// 30레벨 이상
	eNpcConditionLevel45Under			,	// 45레벨 미만
	eNpcConditionLevel45Over			,	// 45레벨 이상
	eNpcConditionLevel1000Under		=	5100	// 1000레벨 미만
} eNpcCondition;

//---------------------------------------------------
// Quest
//---------------------------------------------------
#define HT_NPC_QUEST_START						6001
#define HT_NPC_QUEST_END						8000

#define HT_NPC_QUEST_PROCESS_START				6001
#define HT_NPC_QUEST_PROCESS_END				6020

#define HT_NPC_QUEST_TUTORIAL_START				6021
#define HT_NPC_QUEST_TUTORIAL_END				6040

#define HT_NPC_QUEST_SCENARIO1_START			6041
#define HT_NPC_QUEST_SCENARIO1_END				6060

#define HT_NPC_QUEST_SCENARIO2_START			6061
#define HT_NPC_QUEST_SCENARIO2_END				6075

#define HT_NPC_QUEST_SCENARIO3_START			6075
#define HT_NPC_QUEST_SCENARIO3_END				6090

#define HT_NPC_QUEST_SCENARIO4_START			6091
#define HT_NPC_QUEST_SCENARIO4_END				6095

typedef enum _eNpcQuest
{
	eNpcQuestNone					=	0,
	// 진행 상태
	eNpcQuestStepNone				=	6001, // 없음
	eNpcQuestStepStart					, // 시작
	eNpcQuestStepProcess				, // 진행
	eNpcQuestStepFail					, // 실패
	eNpcQuestStepSuccess				, // 완료
	eNpcQuestStepRejection				, // 거부
	// 차수
	eNpcQuest1st					=	6011, // 1차
	eNpcQuest2nd						, // 2차
	eNpcQuest3rd						, // 3차
	eNpcQuest4th						, // 4차
	eNpcQuest5th						, // 5차
	eNpcQuest6th						, // 6차
	eNpcQuest7th						, // 7차
	eNpcQuest8th						, // 8차
	eNpcQuest9th						, // 9차
	eNpcQuest10th						, // 10차

	// 초보자
	eNpcQuestTutorial1				=	6021, // 초보자1
	eNpcQuestTutorial2					, // 초보자2
	eNpcQuestTutorial3					, // 초보자3
	eNpcQuestTutorial4					, // 초보자4
	eNpcQuestTutorial5					, // 초보자5
	eNpcQuestTutorial6					, // 초보자6
	eNpcQuestTutorial7					, // 초보자7
	eNpcQuestTutorial8					, // 초보자8
	eNpcQuestTutorial9					, // 초보자9
	eNpcQuestTutorial10					, // 초보자10
	eNpcQuestTutorial0				=	6040, 
	// 1차 시나리오
	eNpcQuestScenario1				=	6041, // 1차 시나리오1
	eNpcQuestScenario2					, // 1차 시나리오2
	eNpcQuestScenario3					, // 1차 시나리오3
	eNpcQuestScenario4					, // 1차 시나리오4
	eNpcQuestScenario5					, // 1차 시나리오5
	eNpcQuestScenario6					, // 1차 시나리오6
	eNpcQuestScenario7					, // 1차 시나리오7
	eNpcQuestScenario8					, // 1차 시나리오8
	eNpcQuestScenario9					, // 1차 시나리오9
	eNpcQuestScenario10					, // 1차 시나리오10
	// 2차 시나리오
	eNpcQuestScenario11				=	6061, // 2차 시나리오1
	eNpcQuestScenario12					, // 2차 시나리오2
	eNpcQuestScenario13					, // 2차 시나리오3
	eNpcQuestScenario14					, // 2차 시나리오4
	eNpcQuestScenario15					, // 2차 시나리오5
	eNpcQuestScenario16					, // 2차 시나리오6
	eNpcQuestScenario17					, // 2차 시나리오7
	eNpcQuestScenario18					, // 2차 시나리오8
	eNpcQuestScenario19					, // 2차 시나리오9
    eNpcQuestScenario20					, // 2차 시나리오10
	// 2차 전직 퀘스트
	eNpcQuestScenario21					, // 2차 전직 메인 퀘스트
	eNpcQuestScenario22					, // 2차 전직 - 파괴의 시험 
	eNpcQuestScenario23					, // 2차 전직 - 인내의 시험 
	eNpcQuestScenario24					, // 2차 전직 - 지혜의 시험 
	eNpcQuestScenario25					, // 2차 전직 - 의리의 시험 
	
	// 지나
	eNpcQuestScenario26					, // A. 지나 입성
	eNpcQuestScenario27					, // B. 첩자
	eNpcQuestScenario28					, // C. 매복 제거단
	eNpcQuestScenario29					, // D. 도살자가 된 자매들
	eNpcQuestScenario30					, // E. 저항군

	// 유배지
	eNpcQuestScenario31					, // A. 검은 복면의 사나이
	eNpcQuestScenario32					, // B. 의미 없는 희생
	eNpcQuestScenario33					, // C. 망자들을 위한 순례 행렬
	eNpcQuestScenario34					, // D. 왕비 같은 그녀
	eNpcQuestScenario35					, // E. 지키는 자와 파헤치는 자

	// 북두성군
	eNpcQuestScenario36					, // A. 무덤을 파헤치는 자들
	eNpcQuestScenario37					, // B. 인형을 만드는 사람
	eNpcQuestScenario38					, // C. 망자들을 위한 제단
	eNpcQuestScenario39					, // D. 학문의 즐거움은 끝이 없어라
	eNpcQuestScenario40					, // E. 죽은 자의 안식

	// 카타나3
	eNpcQuestScenario41					, // A. 낯선 동방의 나라
	eNpcQuestScenario42					, // B. 아버지를 잃어버린 마모루
	eNpcQuestScenario43					, // C. 라마의 반지
	eNpcQuestScenario44					, // D. 유리와 나오키
	eNpcQuestScenario45					, // E. 8왕의 흔적

	eNpcQuestScenario81				=	7001, // 차크라 초기화 퀘스트 81
	eNpcQuestScenario82					 // 스킬 초기화 퀘스트 82
} eNpcQuest;

#endif 