//--------------------------------------------------------------------------------//
// 설명 : NPC 관련 기능(제조, 기술습득, 차크라/브라만포인트 확장, 물품보관 등)
// 작성일자 / 작성자 : 2003.4.21 김선미
//--------------------------------------------------------------------------------//

#include "stdAfx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"

#include "HTNPCSystem.h"
#include "HTNPCScriptDef.h"
#include "HTNPCScriptMgr.h"		

#include "HTNPCControl.h"
#include "HTQuestIDDef.h"

typedef std::vector<HT_ITEM_DATA*>::iterator vec_It;
typedef std::vector<HT_ITEM_EXPANSION_DATA*>::iterator vec_exp_It;

#define HT_INDEX_REPAIR_QUEST_ITEM		8043	// 수리 퀘스트 아이템
#define HT_ITEM_MAKE_MONEY_PENALTY		1.3		// 주신전에서 아이템 구입 시 드는 추가 비용

#define HT_REQ_REFINESCALE_TIME			2.0f	// 헌납 게이지 요구 시간 간격

#define HT_MAX_LOTTORYNO_CIPHER			8	// 복권 번호 최대 자리수

//	현재 상태
#define NPC_RESENT_NONE					0
#define NPC_RESENT_DIALOG				1
#define NPC_RESENT_ITEM_LIST			2	// 아이템 구입
#define NPC_RESENT_REFINE				3	// 아이템 제련
#define NPC_RESENT_FIX					4
#define NPC_RESENT_DISJOINT				5
#define NPC_RESENT_INVENTORY			6	// 물품보관
#define NPC_RESENT_SAVEPOSITION			8	// 위치저장 
#define NPC_RESENT_PVP_RANK				9	// PVP 순위 
#define NPC_RESENT_TRIMURITI			10	// 주신 선택
#define NPC_RESENT_TRIMURITI_SELECT		11
#define NPC_RESENT_TRIMURITI_CHANGE		12	// 주신 변경
#define NPC_RESENT_TRIMURITI_POINT		13	// 주신 포인트
#define NPC_RESENT_CREATE_GILD			14	// 아슈람(길드) 생성
#define NPC_RESENT_CREATE_GILD_MARK		15	// 아슈람(길드) 마크 생성
#define NPC_RESENT_CHANGE_JOB2			16
#define NPC_RESENT_REFINE_RATE_UP		17	// 축복의 신로
#define NPC_RESENT_TASK_QUEST			18	// 테스크 퀘스트
#define NPC_RESENT_PREMIUM_ITEM			19	// 프리미엄 아이템 구입 대기 요청
#define NPC_RESENT_PREMIUM_ITEM2		20	// 패키지 프리미엄 아이템 구입 대기 요청
#define NPC_RESENT_PREMIUM_ITEM3		21	// 프리미엄 특수기능 아잍템 구입 대기 요청
#define NPC_RESENT_REGIST_LOTTERY		51	// 이벤트 관련 - 복권 등록
#define NPC_RESENT_CHATURANGA_BOARD		52	// 차투랑가 보드 열람
#define NPC_RESENT_QUIZ					53	// 퀴즈
#define NPC_RESENT_JOB2_SELECT			54	// 2차 직업 선택
#define NPC_RESENT_EVENTITEM			55	// 이벤트 아이템 아이원잇 정보요청
#define NPC_RESENT_EVENTCOUPON			56	// 이벤트 아이템 아이원잇 정보요청

#define	NPC_RESENT_CHAKRA				31
#define	NPC_RESENT_BRAHMAN				32
#define NPC_RESENT_SKILL				33	// 스킬 리스트를 요청하고 결과를 기다리는 상태
#define NPC_RESENT_SKILL_LIST			34
#define NPC_RESENT_SKILL_SELECT			35
#define	NPC_RESENT_SKILL_REMOVE			36
#define NPC_RESENT_EXCHANGE				37	// 수집재료교환
#define NPC_RESENT_RESET_CHAKRA			38	// 차크라재분배

#define NPC_RESENT_USING_ITEM			39	// 아이템사용

#define NPC_RESENT_PREMIUM_ITEM_BUY		40	// 프리미엄 구입 모드
#define NPC_RESENT_PREMIUM_2GRADE_INIT	41	// 2차 전직 초기화

// 메세지창 0:메세지창안뜸,1:작업완료,2:작업재확인
#define NPC_MESSAGE_NONE				0
#define NPC_MESSAGE_COMPLETE			1	
#define NPC_MESSAGE_CONFIRM				2

// 서버 요청 단계
#define SERVER_MSG_NONE							0
#define SERVER_MSG_REQ_ITEM_MAKING				1
#define SERVER_MSG_REQ_RESOURCE_BARTER			2

#define SERVER_MSG_RESP_WORK_ITEM_SUB_INIT		8	// 주술 제련 초기화
#define SERVER_MSG_RESP_WORK_ITEM_MAIN_INIT		9	// 제련 결과 아이템 초기화
#define SERVER_MSG_RESP_WORK_ITEM_REMOVE		10	// 제련 결과 아이템 사라짐
#define SERVER_MSG_RESP_WORK_FAIL				11	// 제련 실패

#define SERVER_MSG_RESP_ERROR					254	// 실패
#define SERVER_MSG_RESP_SUCCESS					255	// 성공

// 제조시 첨가재료 관련 에러 
#define ECONOMY_ADDITEM_ERR_NONE				0	// 첨가재료 추가 가능 
#define	ECONOMY_ADDITEM_ERR_CLASSCOUNT			1	// 첨가재료 종류 에러
#define	ECONOMY_ADDITEM_ERR_MAIN_OVER			2	// 제련 레벨 에러
#define	ECONOMY_ADDITEM_ERR_SUB_OVER			3	// 제련 레벨 에러
#define	ECONOMY_ADDITEM_ERR_IMPOSSIBLE			4	// 첨가 불가능 에러
#define ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM		5	// 특정 재료 첨가 불가능 에러
#define ECONOMY_ADDITEM_ERR_ITEMINDEX			6	// 잘못된 아이템 인덱스 - 아이템을 찾지 못함
#define ECONOMY_ADDITEM_ERR_CANNOT				7	// 현제 단계에서는 더이상 제련할 수 없는 아이템
#define ECONOMY_ADDITEM_ERR_NEEDNOT				8	// 비카리 제련재료를 사용하실 필요가 없습니다.

// 퀘스트 승낙 여부 선택값 - 튜토리얼 퀘스트의 경우 무조건 승낙임.
#define SELECT_QUEST_OK							0	// 퀘스트 승낙
#define SELECT_QUEST_CANCEL						1	// 퀘스트 거부

#define HT_QUIZ_SELECT_NUM						3	// 2차 전직 퀘스트의 퀴즈 선택문 개수

// 아이템 구입 관련 에러 
#define RETURN_ITEM_MAKE_FRIENDLY_ERR			-1
#define RETURN_ITEM_MAKE_INFO_ERR				0
#define RETURN_ITEM_MAKE_OK						1
 
// 강화제련 아이템 인덱스
#define HT_MAIN_REFINE_ILLA_INDEX				6501 // 일라			
#define HT_MAIN_REFINE_AZISE_INDEX				6502 // 아지스
#define HT_MAIN_REFINE_SURAPA_INDEX				6503 // 수라파
#define HT_MAIN_REFINE_DIPAILLA_INDEX			6504 // 디파일라
#define HT_MAIN_REFINE_PRAJATI_INDEX			6505 // 프라자티
#define HT_MAIN_REFINE_SAMPAD_INDEX				6506 // 삼파드
#define HT_MAIN_REFINE_ZARD_INDEX				6551 // 자드

// 제련 단계별 에러 메세지
#define HT_REFINE_WARNING1					1	
#define HT_REFINE_WARNING2					2	
#define HT_REFINE_WARNING3					3	
#define HT_REFINE_WARNING4					4	
#define HT_REFINE_WARNING5					5	
#define HT_REFINE_WARNING6					6	
#define HT_REFINE_WARNING7					7	
#define HT_REFINE_WARNING8					8
#define HT_REFINE_WARNING9					9
#define HT_REFINE_WARNING10					10
#define HT_REFINE_WARNING11					11
#define HT_REFINE_WARNING12					12
#define HT_REFINE_WARNING13					13
#define HT_REFINE_WARNING14					14

// 주신 변경 가능한 조건
#define HT_TRIMURITI_CHANGE_MONEY1			100000
#define HT_TRIMURITI_CHANGE_MONEY2			1000000
#define HT_TRIMURITI_CHANGE_ITEM			7134
#define HT_TRIMURITI_CHANGE_ITEMNUM			15
#define HT_TRUMURITI_CHANGE_DIVISION_LEVEL	30
// 주신 포인트 확장 가능한 조건
#define HT_BRAHMANPOINT_RISING_BRAHMAN		100
#define HT_BRAHMANPOINT_RISING_ITEM			7116
#define HT_BRAHMANPOINT_RISING_ITEMNUM		10
#define HT_BRAHMANPOINT_RISING_MONEY		50000

// 테스크 퀘스트 소스/보상 타입
typedef enum _eTaskQuestType 
{	
	eTaskQuestTypeNone	= 0,
	eTaskQuestTypeItem,
	eTaskQuestTypeRupiah
};


//----------NPC별아이템분류수 0:대장장이,1: 방어구,2:액세서리------------//
//HTint g_ItemClass[3] = { 8, 5, 4 };
//---------서버상의 아이템 타입 값으로 변환 ----------//
// 0:한손검,1:양손검, 2:단검,3:한손도끼,4,두손도끼,5:창,6:격투,7:둔기,8:마법,9:투척,10:의복,11:모자,12:방패,13:벨트,14:신발
// 15:팔찌,16:목걸이,17:귀걸이,18:물약, 19:가방
//#define MAX_SERVERCLASS_NUM  8
//HTfloat g_ServerClass[MAX_SERVERCLASS_NUM] = { 0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700, 0x0800,
//									  0x1101, 0x1202, 0x1303, 0x2301, 0x2401, 0x2201, 0x2101,
//									  0x3301, 0x3101, 0x3201, 0x5201, 0x9101}; 
//HTfloat g_ServerClass[MAX_SERVERCLASS_NUM] 
//= { _ITEM_TYPE_WEPON_SWORD, _ITEM_TYPE_WEPON_DAGGER, _ITEM_TYPE_WEPON_LANCE, _ITEM_TYPE_WEPON_AX, 
//	_ITEM_TYPE_WEPON_MACE, _ITEM_TYPE_WEPON_GLOVE, _ITEM_TYPE_WEPON_BOW, _ITEM_TYPE_WEPON_WAND,  			
//	_ITEM_TYPE_DEFENCE_ARMOR, _ITEM_TYPE_DEFENCE_HELMET, _ITEM_TYPE_DEFENCE_SHOES, _ITEM_TYPE_DEFENCE_BELT, _ITEM_TYPE_DEFENCE_SHIELD, 	
//	_ITEM_TYPE_ACCESSORY_BRACELET, _ITEM_TYPE_ACCESSORY_NECKLACE, _ITEM_TYPE_ACCESSORY_EARRING, /*_ITEM_TYPE_ACCESSORY_RING,*/		
//	_ITEM_TYPE_USABLE_POSION, _ITEM_TYPE_ACCESSORY_EXPANDINVEN
//};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CHTNPCControl::CHTNPCControl()
:m_bNPCActive(HT_FALSE), m_iNPCIndex(0), m_iWorkItemCount(0), m_nSkillList_Count(0), 
m_iSpendMoney(0), m_bNextStepByClientEvent(HT_FALSE), m_pTimer(HT_NULL), m_bPress_OK_Button(HT_FALSE), m_dwOfferingRupiah(0)
{
	m_iMerchantNo = -1;
}

CHTNPCControl::~CHTNPCControl()
{
	
}

HTvoid CHTNPCControl::HT_vNPCControl_Init()
{
	m_bNPCActive = HT_FALSE;
	m_iNPCIndex = 0;

	m_iResent = NPC_RESENT_NONE;
	m_byResent_ServerMsg = SERVER_MSG_NONE;
	m_byMessageWin = NPC_MESSAGE_NONE;
	m_dwNeedValue = 0;
	m_iSpendMoney = 0;
	m_bNextStepByClientEvent = HT_FALSE;

	m_iEconomy_Resent_Item = eEconomy_Item_None;	// 현재 선택된 아이템 분류
	m_byEconomy_Resent_WinIndex = 0;				// 현재 보여질 창 index
	m_iWorkItemCount = 0;

	for(int i = 0 ; i < 8 ; ++i)
	{
		m_Economy_List[i].pInfoHead = m_Economy_List[i].pInfoTail = NULL;
		m_Economy_List[i].vWinCount.clear();
	}

	// 제조에 사용된 아이템 KeyID를 저장해 둘 장소 초기화
	m_nEconomy_Work_ResRupiah = 0;
	// 제조에 사용된 보조재료 저장해 둘 장소 초기화
	for (HTint i = 0; i<3 ; ++i)
	m_nEconomy_Work_SubItemKeyID[i] = 0;

	// 헌납 관련 초기화
	m_sRefineRateGauge = 0;
	m_bPress_OK_Button = HT_FALSE;
	m_fGaugeTimer = 0;
	for( i = 0 ; i < MAX_ITEM_CONTRIBUTION ; ++i )
		m_iOfferingItemKeyID[i] = 0;
	m_byOfferingItemNum = 0;
	m_dwOfferingRupiah = 0;

	m_pTimer = new CHTTimer;
	m_pTimer->Do( HT_TIMER_START );

	// 스킬
	m_nSkillList_Count = 0;

	// 페이지 설정
	m_iNowPage = 1;
}

HTvoid CHTNPCControl::HT_vNPCControl_CleanUp()
{
	HT_vNPCControl_ButtonCheck_Work_Delete();
	HT_vNPCControl_ButtonCheck_List_Delete();

	m_bNPCActive = HT_FALSE;
	m_iNPCIndex = 0;

	m_iResent = NPC_RESENT_NONE;
	m_byMessageWin = NPC_MESSAGE_NONE;
	m_byResent_ServerMsg = SERVER_MSG_NONE;
	m_dwNeedValue = 0;
	m_iWorkItemCount = 0;
	m_iSpendMoney = 0;
	m_bNextStepByClientEvent = HT_FALSE;

	// 헌납 관련 초기화
	m_sRefineRateGauge = 0;
	m_bPress_OK_Button = HT_FALSE;
	m_fGaugeTimer = 0;
	for( HTint i = 0 ; i < MAX_ITEM_CONTRIBUTION ; ++i )
		m_iOfferingItemKeyID[i] = 0;
	m_byOfferingItemNum = 0;
	m_dwOfferingRupiah = 0;
	
	m_pTimer->Do( HT_TIMER_STOP );
	HT_DELETE( m_pTimer );

	// 스킬
	m_nSkillList_Count = 0;
}
 
HTvoid CHTNPCControl::HT_vNPCControl_Active( DWORD dwNPCIndex )
{  
	
	HTint nRes = HT_SCRIPT_NEXTSTEP_SUCCESS;
	switch( dwNPCIndex )
	{
		// 무기 상인
		case 1101 :	// 만다라
		case 1109 :	// 아누
		case 1133 :	// 지나마을
		case 1205 :	// 18번 만다라
		case 1235 :	// 19번 만다라
		case 1303 : // 유리*# - 무기 (카타나3)
		{
			m_iEconomy_NPC = m_iEconomy_Resent_Item = eEconomy_Item_Sword;
			// 대화 스크립트 설정
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_WEPON);	
		}
			break;

		// 방어구 상인
		case 1102 :	// 만다라
		case 1110 :	// 아누
		case 1127 :	// 지나마을
		case 1206 :	// 18번 만다라
		case 1236 :	// 19번 만다라
		case 1300 : // 만물상 마모루*# - 방어구 (카타나3)
		{
			m_iEconomy_NPC = m_iEconomy_Resent_Item = eEconomy_Item_Armor;
			// 대화 스크립트 설정
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_DEFENSE);
		}
			break;

		// 액세서리 상인 
		case 1103 :	// 만다라
		case 1111 :	// 아누
		case 1134 :	// 지나마을
		case 1146 :	// 유배지
		case 1151 :	// 비슈누 주신전
		case 1152 :	// 브라흐마 주신전
		case 1153 :	// 시바 주신전
		case 1207 :	// 18번 만다라
		case 1237 :	// 19번 만다라
		case 1248 : // 크루마(비슈누)
		case 1249 : // 크루마(브라흐마)
		case 1250 : // 크루마(시바)
		case 1331 :	// 기타용품(비슈누)				// 추가 2005. 11. 15
		case 1332 :	// 기타용품(브라흐마)
		case 1333 :	// 기타용품(시바)
		case 1278 :	// 요새전 만물상
		case 1279 :	// 요새전 만물상
		case 1280 :	// 요새전 만물상
		case 1281 :	// 요새전 만물상
		case 1282 :	// 요새전 만물상
		case 1283 :	// 요새전 만물상
		case 1284 :	// 요새전 만물상
		case 1285 :	// 요새전 만물상
		case 1299 : // 사토* - 액세서리 (카타나3)
		case 1304 : // 북두 토용의 장인
		{
			m_iEconomy_NPC = m_iEconomy_Resent_Item = eEconomy_Item_Bracelet;
			// 대화 스크립트 설정
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_ACCESSORY);
		}
			break;

		// 승려
		case 1104 :	// 만다라
		case 1118 :	// 샴발라
		case 1129 :	// 지나마을
		case 1141 : // 유배지
		case 1208 :	// 18번 만다라
		case 1238 :	// 19번 만다라
		case 1306 : // 북두 쭈앙즈
		{ 
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_TEMPLE);
		}
			break;

		//	물품보관지기
		case 1105 :	// 만다라
		case 1121 :	// 비슈누 주신전
		case 1122 :	// 시바 주신전
		case 1123 :	// 브라흐마 주신전
		case 1132 :	// 지나마을
		case 1138 : // 유배지
		case 1209 :	// 18번 만다라
		case 1239 :	// 19번 만다라
		case 1251 : // 크루마(비슈누)
		case 1252 : // 크루마(브라흐마)
		case 1253 : // 크루마(시바)
		case 1334 : //	창고지기(비슈누)
		case 1335 : //  창고지기(브라흐마)
		case 1336 : //	창고지기(시바)
		case 1301 : //1301	창고지기 구보
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_WAREHOUSE);
		}
			break;
 
		// 수비대장
		case 1108 :	// 만다라 
		case 1112 :	// 샴발라(아마르)
		case 1128 : // 지나마을
		case 1212 : // 18번 만다라
		case 1242 :	// 19번 만다라
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_CHIEFGUARD);
		}
			break;

		// 역마꾼(게이트)
		case 1106 :	// 만다라
		case 1210 : // 18번 만다라
		case 1240 :	// 19번 만다라
//			{
//				if (g_iInationalType != INATIONALTYPE_KOREA)
//					return;
//			}
		case 1257 : // 차투랑가 말 합성
		case 1258 : // 차투랑가 말 합성
		case 1259 : // 차투랑가 말 합성
		case 1260 : // 차투랑가 말 합성
		case 1286 : // 요새전 관리인
		case 1287 : // 요새전 관리인
		case 1288 : // 요새전 관리인
		case 1289 : // 요새전 관리인
		case 1290 : // 요새전 관리인
		case 1291 : // 요새전 관리인
		case 1292 : // 요새전 관리인
		case 1293 : // 요새전 관리인
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_POSTHORSE);
		}
			break;
		// 주술사(마법동물대여)
		case 1107 :	// 만다라
		case 1211 :	// 18번 만다라
		case 1241 :	// 19번 만다라
		case 1302 : // 카타나3 오다
		{
			m_iEconomy_NPC = m_iEconomy_Resent_Item = eEconomy_Item_Bracelet;
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_ANIMALLEND);
		}
			break;
		// 병사1
		case 1001 :	// 만다라
		case 1113 :	// 샴발라(마호벳)
		case 1142 :	// 유배지 수행승 뤼즈션
		case 1201 :	// 18번 만다라
		case 1231 :	// 19번 만다라
		case 1294 : // 요새 결투장 관리인
		case 1297 : // 1297	비류성 관리인 야스다 - ETC
		{
			if (!(g_gServerType == SERVERTYPE_MAIN && dwNPCIndex == 1297))
				nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_SOLDIER1);
			else
				return;
		}
			break;
		// 병사2
		case 1002 :	// 만다라
		case 1114 :	// 샴발라(바바)
		case 1143 : // 유배지 수행승 우쏭
		case 1202 :	// 18번 만다라
		case 1232 :	// 19번 만다라
		case 1295 : // 요새전 쿠마르
		case 1298 : // 1298	광물 제련소 유메이 - ETC
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_SOLDIER2);
		}
			break;
		//	남자아이1
		case 1003 :	// 만다라
		case 1004 :	// 아누
		case 1148 : // 유배지 농부 션농쓰
		case 1203 : // 18번 만다라
		case 1233 : // 19번 만다라
		case 1307 : // 비류성 (위탁상점 관리인)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_BOY1);
		}
			break;

		//	여자아이1
		case 1005 :	// 만다라
		case 1006 :	// 아누
		case 1149 : // 유배지 아낙네 쑨얼냥
		case 1204 : // 18번 만다라
		case 1234 : // 19번 만다라
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_GIRL1);
		}
		break;

		case 1308 : // 비류성 (위탁상점 판매인)
		case 1309 : // 비류성 (위탁상점 판매인)
		case 1310 : // 비류성 (위탁상점 판매인)
		case 1311 : // 비류성 (위탁상점 판매인)
		case 1312 : // 비류성 (위탁상점 판매인)
		case 1313 : // 비류성 (위탁상점 판매인)
		case 1314 : // 비류성 (위탁상점 판매인)
		case 1315 : // 비류성 (위탁상점 판매인)
		case 1316 : // 비류성 (위탁상점 판매인)
		case 1317 : // 비류성 (위탁상점 판매인)
		case 1318 : // 비류성 (위탁상점 판매인)
		case 1319 : // 비류성 (위탁상점 판매인)
		case 1320 : // 비류성 (위탁상점 판매인)
		case 1321 : // 비류성 (위탁상점 판매인)
		case 1322 : // 비류성 (위탁상점 판매인)
		case 1323 : // 비류성 (위탁상점 판매인)
		case 1324 : // 비류성 (위탁상점 판매인)
		case 1325 : // 비류성 (위탁상점 판매인)
		case 1326 : // 비류성 (위탁상점 판매인)
		case 1327 : // 비류성 (위탁상점 판매인)
		case 1328 : // 비류성 (위탁상점 판매인)
		case 1329 : // 비류성 (위탁상점 판매인)
		{
			g_cRentalStore->m_iStoreIndex = dwNPCIndex - 1308;
			g_cRentalStore->m_iNPCIndex = dwNPCIndex;
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_GIRL1);
		}
			break;

		// 퀘스트용 병사 NPC
		case 1115 :	// 공동 협의체
		case 1213 :	// 18번 만다라
		case 1243 : // 19번 만다라
		case 1438 : // 마실나온 유리 -_-; (카타나3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_QUEST_SOLDIER);
		}
			break;
		
		// 스포르바다 병사 NPC
		case 1116 :
		case 1214 : // 18번 만다라
		case 1244 : // 19번 만다라
		case 1439 : // 나오키 (카타나3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_QUEST_SPORBADA);
		}
			break;

		// 아바타라의 무덤 아이
		case 1117 :
		case 1215 : // 18번 만다라
		case 1245 : // 19번 만다라
		case 1440 : // 전쟁터 폐허지역의 무사 (카타나3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_QUEST_BOY);
		}
			break;

		// 격투장 NPC
		//case 1119 :	// 샹카르
		//case 1216 : // 18번 만다라
		//case 1246 : // 19번 만다라
		case 1263 : // 만다라 크리슈나
		case 1218 :	// 만다라 크리슈나 2
		case 1219 : // 만다라 크리슈나 3
		case 1264 : // 샴발라 크리슈나
		case 1265 : // 지나마을 크리슈나
		case 1266 : // 유배지 크리슈나
		case 1267 :	// 크리슈나_만던1
		case 1268 :	// 크리슈나_만던2
		case 1269 :	// 크리슈나_샴던1
		case 1270 :	// 크리슈나_샴던2
		case 1271 :	// 크리슈나_크루마
		case 1272 :	// 크리슈나_차투랑가
		case 1273 :	// 크리슈나_파미르
		case 1274 : // 칼리아던전 1
		case 1275 : // 칼리아던전 2
		case 1276 : // 칼리아던전 3
		case 1277 : // 북두성군릉
		case 1296 : // 요새전
		case 1330 : // 비류성
		case 1340 : // 저렙던전
		{
			// 국내 메인서버 또는 해외 중국 테섭에서는 크리슈나 NPC 처리가 가능하다. 
			if (!(g_gServerType == SERVERTYPE_TEST && g_iInationalType == INATIONALTYPE_KOREA))
			{
				m_iEconomy_NPC = m_iEconomy_Resent_Item = eEconomy_Item_Bracelet;
				nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_BATTLE);
				break;
			}
			else
				return;
		}

		// 위치 저장용 NPC
		case 1120 :	// 만다라 여사제
		case 1154 :	// 샴발라 여사제
		case 1155 :	// 지나_1st
		case 1156 :	// 유배지(지나_3rd)
		case 1157 :	// 비슈누 주신전
		case 1158 :	// 브라흐마 주신전
		case 1159 :	// 시바 주신전
		case 1217 : // 18번 만다라
		case 1247 : // 19번 만다라
		case 1254 : // 크루마(비슈누)
		case 1255 : // 크루마(브라흐마)
		case 1256 : // 크루마(시바)
		case 1337 : // 여사제(저장)
		case 1338 : // 여사제(저장)
		case 1339 : // 여사제(저장)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_SAVEPOINT);
		}

			break;

		case 1341 : // 만다라마을 탄 할아버지
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_EVENTNPC);
		}
		break;

		case 1437 : // 만다라마을 주정뱅이 이벤트 NPC
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_EXTRA_ETC2);
		}
		break;

		case 1441 : // 버려진 요새의 무사 (카타나3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_EXTRA_ETC3);
		}
		break;
		case 1442 : // 갓파 부락의 무사 (카타나3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_EXTRA_ETC4);
		}
		break;
		case 1443 : // 광산지역의 무사 (카타나3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_EXTRA_ETC5);
		}
		break;


		case 9999 :	// 메인체크 및 서브체크에서 프리미엄 상점 버튼 클릭시 처리
		{
			//m_bPrimium_Button = HT_TRUE;	// 달려도 닫히지 않도록 설정
			HTint Location = 0;
			if (g_wResentZoneServerID == 1)	// 만다라
				g_cNPCControl->HT_vNPCControl_Active(1263);
			else if (g_wResentZoneServerID == 2) // 샴발라
				g_cNPCControl->HT_vNPCControl_Active(1264);
			else if (g_wResentZoneServerID == 7) // 지나
				g_cNPCControl->HT_vNPCControl_Active(1265);
			else if (g_wResentZoneServerID == 9) // 유배지
				g_cNPCControl->HT_vNPCControl_Active(1266);
			else if (g_wResentZoneServerID == 3) // 크리슈나_만던1
				g_cNPCControl->HT_vNPCControl_Active(1267);
			else if (g_wResentZoneServerID == 4) // 크리슈나_만던2
				g_cNPCControl->HT_vNPCControl_Active(1268);
			else if (g_wResentZoneServerID == 5) // 크리슈나_샴던1
				g_cNPCControl->HT_vNPCControl_Active(1269);
			else if (g_wResentZoneServerID == 6) // 크리슈나_샴던2
				g_cNPCControl->HT_vNPCControl_Active(1270);
			else if (g_wResentZoneServerID == 10) // 크루마
				g_cNPCControl->HT_vNPCControl_Active(1271);
			else if (g_wResentZoneServerID == 11) // 차투랑가
				g_cNPCControl->HT_vNPCControl_Active(1272);
			else if (g_wResentZoneServerID == 8) // 파미르
				g_cNPCControl->HT_vNPCControl_Active(1273);
			else if (g_wResentZoneServerID == 13) // 칼리아1
				g_cNPCControl->HT_vNPCControl_Active(1274);
			else if (g_wResentZoneServerID == 14) // 칼리아2
				g_cNPCControl->HT_vNPCControl_Active(1275);
			else if (g_wResentZoneServerID == 15) // 칼리아3
				g_cNPCControl->HT_vNPCControl_Active(1276);
			else if (g_wResentZoneServerID == 12) // 북두성군릉
				g_cNPCControl->HT_vNPCControl_Active(1277);
			else if (g_wResentZoneServerID == 16) // 요새전
				g_cNPCControl->HT_vNPCControl_Active(1296);
			else if (g_wResentZoneServerID == 17) // 비류성
				g_cNPCControl->HT_vNPCControl_Active(1330);
			else if (g_wResentZoneServerID == 18) // 만다라2
				g_cNPCControl->HT_vNPCControl_Active(1218);
			else if (g_wResentZoneServerID == 19) // 만다라3
				g_cNPCControl->HT_vNPCControl_Active(1219);
			else if (g_wResentZoneServerID == 20) // 만다라3
				g_cNPCControl->HT_vNPCControl_Active(1340);
			else
			{
			}
		}

		default :
			return;
	}

	// 대화를 못찾았을 경우
	if( nRes != HT_SCRIPT_NEXTSTEP_SUCCESS )
		return;

	//---------상인 NPC의 고유 인덱스---------//
	m_iNPCIndex = dwNPCIndex;
	g_cUIMerchantWindow->m_iNPCIndex = dwNPCIndex;	// v3에서 추가

	m_byMessageWin = NPC_MESSAGE_NONE;	// 메세지 창 안떠있음

	// NPC의 이름
	//g_pEngineHandler->HT_hrGetNPCName( m_iNPCIndex, &m_szNPCName );
	g_pParamMgr->HT_bGetNPCName( m_iNPCIndex, &m_szNPCName );

	m_pCharPos_Memory = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	m_iResent = NPC_RESENT_DIALOG;
	m_byResent_ServerMsg = SERVER_MSG_NONE;
	m_bNPCActive = HT_TRUE;

	m_nSkillList_Count = 0;
	
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_NPCWINDOW, 1, m_szNPCName );
	
	//if( m_iNPCIndex == 1106 )	// 역마꾼 라훌에게 쿠폰 등록할 경우에만
	//{
	//	m_bNextStepByClientEvent = HT_FALSE;
	//	// 클라이언트 이벤트에서 초기화 및 단계 변경을 하기 때문에 제일 먼저 처리한다.
	//	HT_vNPCControl_ClientEvent();
	//	// 클라이언트 이벤트에서 초기화 및 단계 변경이 안됐을 경우만 처리
	//	if( m_bNextStepByClientEvent == HT_FALSE ) 
	//		HT_vNPCControl_ServerEvent();
	//}

	HT_vNPCControl_SetText();		// 화면에 보여줄 대화 설정 

	g_cUIManager->HT_ShowWindow( _DIALOG_NPCWINDOW );
}

HTvoid CHTNPCControl::HT_vNPCControl_SetMessage( HTint idMessage )
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
		HT_vNPCControl_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vNPCControl_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vNPCControl_SetParamTextForMessage( sParam3, &szOut3 );

		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vNPCControl_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vNPCControl_SetParamTextForMessage( sParam2, &szOut2 );
		
		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vNPCControl_SetParamTextForMessage( sParam1, &szOut1 );
		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		m_szMessage = szString;
}

HTvoid CHTNPCControl::HT_vNPCControl_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		case eMsgParamMyName		:
			pszParam->HT_szFormat( "%s", g_oMainCharacterInfo.szCharName ); break;
		// 다른 캐릭터 이름
		case eMsgParamOthercharName	:
			*pszParam = m_szObjectName; break;
		// 주신 이름
		case eMsgParamTrimuritiName	:
			if( m_iResent == NPC_RESENT_TRIMURITI_SELECT )	// 주신 선택한 결과
				*pszParam = g_cStatus->HT_szStatus_GetTrimuriti();
			else if( m_iResent == NPC_RESENT_TRIMURITI_CHANGE )	// 주신 변경 확인 메세지
			{
				switch( m_bySelectPart )
				{
					case 0 : g_pMessageMgr->HT_bGetMessage( eMsgCommonTrimuritiBrahma, pszParam ); break;
					case 1 : g_pMessageMgr->HT_bGetMessage( eMsgCommonTrimuritiVishunu, pszParam ); break;
					case 2 : g_pMessageMgr->HT_bGetMessage( eMsgCommonTrimuritiSiva, pszParam ); break;
					default: break;
				}
			}
			break;
		// 직업 이름
		case eMsgParamJobName			:
			*pszParam = g_cStatus->HT_szStatus_GetJobName(); break;
		// 구입할 아이템 이름
		case eMsgParamBuyItemName		:
			g_pParamMgr->HT_bGetItemName( m_dwBuyItem, pszParam ); break;
		// 수리/판매/제련 아이템 이름
		case eMsgParamItemName			:
			// 구입
			//if( m_iResent == NPC_RESENT_ITEM_LIST )
			//	g_pParamMgr->HT_bGetItemName( m_dwBuyItem, pszParam );
			// 제련
			/*else*/ if( m_iResent == NPC_RESENT_REFINE )	
			{
				DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwWorkItem );
				g_pParamMgr->HT_bGetItemName( dwIndex, pszParam );
			}
			// 수리/판매
			else if( m_iResent == NPC_RESENT_FIX || m_iResent == NPC_RESENT_DISJOINT || m_iResent == NPC_RESENT_ITEM_LIST )
			{
				DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwFixDisjointKeyID );
				g_pParamMgr->HT_bGetItemName( dwIndex, pszParam );
			}
			break;
		// 필요한 아이템 이름
		case eMsgParamNeedItemName	:	
		{
			if( m_iResent == NPC_RESENT_TRIMURITI_CHANGE )		// 주신 변경
				g_pParamMgr->HT_bGetItemName( HT_TRIMURITI_CHANGE_ITEM, pszParam );
			else if( m_iResent == NPC_RESENT_TRIMURITI_POINT )	// 주신 포인트 변경
				g_pParamMgr->HT_bGetItemName( HT_BRAHMANPOINT_RISING_ITEM, pszParam ); 
		}
			break;
		// 제련 재료 아이템 이름
		case eMsgParamSubItemName		:
		{
			DWORD dwRefineIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[0] );
			if( dwRefineIndex > 0 )
				g_pParamMgr->HT_bGetItemName( dwRefineIndex, pszParam );
		}
			break;

		// 필요한 돈
		case eMsgParamNeedMoney		:	
		{
			HTint iRupiah = 0;
			if( m_iResent == NPC_RESENT_ITEM_LIST )	// 구입
			{	
				*pszParam = g_cUIManager->HT_strSetRestMark( m_nEconomy_Work_LimitRupiah ); // 쉼표 처리
			}
			else if( m_iResent == NPC_RESENT_REFINE )	// 제련-부족한 돈
			{
				HTint iRupiah = m_nEconomy_Work_LimitRupiah - g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
				if( iRupiah < 0 )
					iRupiah = 0;
				pszParam->HT_szFormat( "%d", iRupiah );
			}
			else if( m_iResent == NPC_RESENT_TRIMURITI_CHANGE )	// 주신 변경
			{
				HTbyte byLevel = g_cStatus->HT_byGetLevel();
				HTfloat fPrice = HT_bNPCControl_CheckTrimuritiChangeCost();

				if( byLevel < HT_TRUMURITI_CHANGE_DIVISION_LEVEL )
					pszParam->HT_szFormat( "%d", (HTint) fPrice );
				else
					pszParam->HT_szFormat( "%d", (HTint) fPrice );
			}
			else if( m_iResent == NPC_RESENT_TRIMURITI_POINT )	// 주신 포인트 변경
				pszParam->HT_szFormat( "%d", HT_BRAHMANPOINT_RISING_MONEY );
		}
			break;
		
		// 필요한 날짜
		case eMsgParamNeedDay		:
			break;
		// 남은 날짜
		case eMsgParamRemainDay		:
			break;

		// 사용/획득한 돈
		case eMsgParamSpendingMoney	:	
			//pszParam->HT_szFormat( "%d", m_iSpendMoney );
			*pszParam = g_cUIManager->HT_strSetRestMark( m_iSpendMoney ); // 쉼표 처리
			break;
		// 아이템 구입 개수
		case eMsgParamBuyItemNum		:	
			pszParam->HT_szFormat( "%d", m_iWorkItemCount );
			break;
		// 아이템 구입 가능 최대 개수
		case eMsgParamBuyItemMaxNum	:	
		{
			HTbyte byteMaxCount = 0;
			if( g_pParamMgr->HT_bGetItemMaxCount( m_dwBuyItem, &byteMaxCount ) == true )
				pszParam->HT_szFormat( "%d", byteMaxCount );
		}
			break;
		// 아이템 구입 최소 개수
		case eMsgParamBuyItemMinNum :
			pszParam->HT_szFormat( "%d", m_iWorkItemMinCount );
			break;
		// 강화제련 레벨
		case eMsgParamMainRefineLevel	:
		{
			HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( m_dwWorkItem );
			pszParam->HT_szFormat( "%d", byLevel );
		}
			break;

		// 필요한 아이템 개수
		case eMsgParamNeedItemNum		:
			if( m_iResent == NPC_RESENT_TRIMURITI_POINT )	// 주신 포인트 변경
				pszParam->HT_szFormat( "%d", HT_BRAHMANPOINT_RISING_ITEMNUM );
			break;
		// 필요한 주신 포인트 
		case eMsgParamNeedTrimuritiPoint :
			pszParam->HT_szFormat( "%d", HT_BRAHMANPOINT_RISING_BRAHMAN );
			break;

		default:
			break;
	}
}

//---------- 다음단계로 대화상자 대화 바꾸기 -----------//
HTvoid CHTNPCControl::HT_vNPCControl_GetNextStep(HTint nSelNum)
{
	HTint res = g_pEngineHandler->HT_nNextStep(nSelNum);

	if( res == HT_SCRIPT_NEXTSTEP_FAIL)
	{
		res = g_pEngineHandler->HT_nSetFirstStep();	// 처음 단계로 되돌린다.
	}
 
	if(res == HT_SCRIPT_NEXTSTEP_SUCCESS)	// 같은 단계일 경우 변화 없음
	{
		m_bNextStepByClientEvent = HT_FALSE;
		// 클라이언트 이벤트에서 초기화 및 단계 변경을 하기 때문에 제일 먼저 처리한다.
		HT_vNPCControl_ClientEvent();
		if( m_bNextStepByClientEvent == HT_FALSE ) 
		{	// 클라이언트 이벤트에서 초기화 및 단계 변경이 안됐을 경우만 처리
			HT_vNPCControl_SetText();	// 화면에 보여줄 대화 설정 
			HT_vNPCControl_ServerEvent();

		}
	}
	else if( res == HT_SCRIPT_NEXTSTEP_EQUALSTEP ) 
	{
		/* 연속으로 브라만/차크라 포인트 확장->성공 일 경우 
	   질의문의 필요한/사용한 프라나 양을 갱신하기 위해 질의문만 다시 쓴다. */
		if( m_iResent == NPC_RESENT_CHAKRA || m_iResent == NPC_RESENT_BRAHMAN )
		{
			HTtchar text[HT_SCRIPT_QUE_MAXSIZE] ;
			sprintf(text, m_szQuestion, m_dwNeedValue); // 파라미터 값 설정
		
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_NPCWINDOW, 2, text);
		}
		// 수리/판매 성공시에도 res == HT_SCRIPT_NEXTSTEP_EQUALSTEP 인데 대화창에 바꿀 내용은 없다.
	}
	else //if( res == HT_SCRIPT_NEXTSTEP_FAIL )	// 처음 단계로 되돌리는 것도 실패했으므로 대화 상자 닫기
	{
		//	대화상자 닫기 - NPC와 관련된 모든 창 닫힘
		HT_vNPCControl_DialogWin_AntiActive();
	}
}

//-------------- 화면에 보여줄 대화 설정 --------------------//
HTvoid CHTNPCControl::HT_vNPCControl_SetText()
{
	CHTString strTemp;
	
	//	NPC의 질의문
	ZeroMemory(m_szQuestion, sizeof(HTtchar)*HT_SCRIPT_QUE_MAXSIZE);
	m_byParameter = eNpcParamNone;
	g_pEngineHandler->HT_vGetQuestion( m_szQuestion, &m_byParameter );
 
	if( m_byParameter != eNpcParamNone )
		HT_vNPCControl_SetParameterText();
	
	HTtchar cText[HT_SCRIPT_QUE_MAXSIZE];
	ZeroMemory(cText, sizeof(HTtchar)*HT_SCRIPT_QUE_MAXSIZE);

	if(m_byParameter == eNpcParamNeedPrana || m_byParameter == eNpcParamCashRemain 
		|| m_byParameter == eNpcParamChangeGodReqRupia || m_byParameter == eNpcParamEventItemTotal
		|| m_byParameter == eNpcParamDurgaReceiptofMoney) // 필요한프라나||남은 캐쉬
 		wsprintf(cText, m_szQuestion, m_dwNeedValue); // 파라미터 값 설정
	else if( m_byParameter != eNpcParamNone )
		wsprintf(cText, m_szQuestion, m_szName.HT_szGetString()); // 파라미터 값 설정
	else
		wsprintf(cText, m_szQuestion);

	HT_RECT Rect; Rect.left = 0; Rect.top = 0; Rect.right = 311; Rect.bottom = 130;
	int strlength = g_pEngineHandler->HT_iGetTextHeight(HT_FONT_GULIM_12, cText, Rect, TEXT_FORMATING_MULTILINE_VTOP_LEFT_CLIP );
	g_cUIManager->HT_SetTextLongLabelControl( _DIALOG_NPCWINDOW, 2, cText);

	g_cUINPCWindow->m_StartPosY = strlength+125;
	//	선택문
	m_nSelectCount = 0;
	g_cUINPCWindow->HT_vNPCWindow_SetInfo();

	// ECONOMY_RESENT_SKILL_LIST 경우엔 select문 위치에 스킬 리스트가 이미 들어가 있음
	if( (m_iResent != NPC_RESENT_SKILL_LIST && m_iResent != NPC_RESENT_SKILL_REMOVE ) || (m_nSkillList_Count == 0) )	
	{
		//	선택문_라디오 버튼 클린업하기
	}

//	for (HTint i = 1; i <= MAX_SELECT_COUNT; ++i)
//		g_cUIManager->HT_SetButtonEnable(_DIALOG_NPCWINDOW, i, true);

	// 현재 보여지는 질의문의 인덱스를 얻어 온다.
	HTint iQuestion = g_pEngineHandler->HT_iGetNowQuestionIndex();
 
	for( HTint i=0 ; i < MAX_SELECT_COUNT ; ++i)
	{
		g_pEngineHandler->HT_vGetSelectText(i, strTemp );

		// 해당 질의문이 떳을 경우에는 해당 루프에서 벗어나 선택문의 출력을 제한한다. (해외측에서는 나오면 안되는 것이 있으므로.. ) 2004. 12. 1 선영범
		if (g_wResentZoneServerID == 17) // 비류성에 해당
		{
			if ( !(g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_MAHARAJA && g_pSiege->HT_vSiege_GetOwerOfCastle() == true) && iQuestion == 20001 && i==2 ) 
				continue;

			if (g_pSiege->HT_vSiege_GetOwerOfCastle() == false && iQuestion == 80201 && i==2 )
				continue;

		}
	
		if (g_wResentZoneServerID == 7) // 지나지역 쫑꾸이의 선택문중 마지막것은 퀘스트 완료후에만 뜸
			if ( g_cUIQuestWindow->g_bMoonBang != true && iQuestion == 42025 && i == 2) 
				break; 

		if( g_iInationalType == INATIONALTYPE_PHILIPPINE )
		{
			if(iQuestion == 110001) if (i==1) continue;		// 여사제
			if(iQuestion == 110001) if (i==2) continue;		// 여사제
		}
		else if( g_iInationalType != INATIONALTYPE_KOREA )
		{
			if(iQuestion == 110001) if (i==2) continue;		// 여사제
			
			if (g_wResentZoneServerID == 9) // 유배지에서 해당
			{
				if(iQuestion == 20210) if (i==2) continue;		// 뤼뿌웨이 업그레이드
				if(iQuestion == 20211) if (i==2) continue;		// 뤼뿌웨이 업그레이드

				if(iQuestion == 20210) if (i==3) continue;		// 뤼뿌웨이 업그레이드
				if(iQuestion == 20211) if (i==3) continue;		// 뤼뿌웨이 업그레이드
			}
		}
		if( g_iInationalType != INATIONALTYPE_KOREA )		// 한국을 제외한 나라에서는 타니구입 메뉴가 뜨지 않음 (크리슈나)
		{
			if(iQuestion == 100001) if (i==6) continue;

		}

		if(strTemp.HT_nGetSize() == 0)	// 더이상 선택문이 없음
			break;

		g_cUIManager->HT_SetTextLabelControl( _DIALOG_NPCWINDOW, i+m_nSkillList_Count+3, strTemp);

	}
	m_nSelectCount = i;	// 선택문 개수

	if (m_nSelectCount+1 < MAX_SELECT_COUNT)
		for (HTint i = 1; i <= MAX_SELECT_COUNT; ++i)
		{
			CHTString str;
			str = g_cUIManager->HT_GetTextLabelControl(_DIALOG_NPCWINDOW, i+2);
			if (strcmp(str, "") == 0)
				g_cUIManager->HT_SetButtonEnable(_DIALOG_NPCWINDOW, i, false);
		}
}

//------------- 질의문에 삽입할 parameter text설정 ---------------//
HTvoid CHTNPCControl::HT_vNPCControl_SetParameterText()
{
	switch( m_byParameter )
	{
		case eNpcParamNeedPrana : // 필요한프라나
			m_dwNeedValue = 0;
			break;
		case eNpcParamCharacterName : // 캐릭터이름
			m_szName = g_oMainCharacterInfo.szCharName;
			break;
		case eNpcParamSkillName : // 스킬이름
			m_szName = HT_szNPCControl_GetSelectSkillName();
			break;
		case eNpcParamChakraName : // 차크라이름
			g_cQuest->HT_vQuest_GetChakraText(m_szName);
			break;
		case eNpcParamTribeName : // 종족이름
			m_szName = g_cMainCharacter->HT_strMainChar_GetTribe();
			break;
		case eNpcParamTrimuritiName : // 주신이름
		{
			if( g_oMainCharacterInfo.byTrimuriti == 0 ) // 주신선택 안했음
				m_szName.HT_hrCleanUp();
			else
				m_szName = g_cStatus->HT_szStatus_GetTrimuriti();
		}
			break;
		case eNpcParamGuildName : // 아쉬람이름
			m_szName = g_cGuildSystem->HT_strGuild_GetGuildName();
			break;
		case eNpcParamJobName : // 직업이름
			m_szName = g_cStatus->HT_szStatus_GetJobName();
			break;
		case eNpcParamCashRemain : // 남은 캐쉬
			m_dwNeedValue = m_nCash;
			break;
		case eNpcParamInitializeReqRupia : // 차크라/스킬 초기화에 필요한 루피아양
			{
				m_nLevel = g_cStatus->HT_byGetLevel();
				m_nNowRupia = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
				m_dwNeedValue = m_nNeedRupia = (int(pow((double)m_nLevel, 2.95)*10 + 990)/100)*100;
				m_szName.HT_szFormat("%d",m_nNeedRupia);
			}
			break;
		case eNpcParamChangeGodReqRupia : // 주신 변경에 필요한 루피아량 계산
			{
				HTfloat fPrice = HT_bNPCControl_CheckTrimuritiChangeCost();
				m_dwNeedValue = (HTint) fPrice;
			}
			break;
		case eNpcParamEventItemTotal : // 이벤트 아이템 남은갯수
			{
				m_dwNeedValue = m_iEventItem;
			}
			break;
		case eNpcParamDurgaState :
			{ 
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg14, &strString );	//마히 드루가 : [%s]>>아브 드루가 : [%s]>>단바 드루가 : [%s]>>나르 드루가 : [%s]
				m_szName.HT_szFormat( strString, g_cGuildSystem->m_strStrongGuildName[0].HT_szGetString(), g_cGuildSystem->m_strStrongGuildName[1].HT_szGetString(), g_cGuildSystem->m_strStrongGuildName[2].HT_szGetString(), g_cGuildSystem->m_strStrongGuildName[3].HT_szGetString() );
			}
			break;
		case eNpcParamDurgaReceiptofMoney :
			{
				m_dwNeedValue = m_iDurgaReceiptofMoney;
			}
			break;
		case eNpcParamGetMoneyYut : 
			{
				CHTString strString = g_cUIManager->HT_strSetRestMark(g_pSiege->m_iGetMoneyYut);
				CHTString str2;	str2.HT_szFormat(" %s ", strString.HT_szGetString());
				//HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg14, &strString );	//마히 드루가 : [%s]>>아브 드루가 : [%s]>>단바 드루가 : [%s]>>나르 드루가 : [%s]
				//m_szName.HT_szFormat(strString, str2);
				m_szName = str2;
			}
			break;
		default : m_szName.HT_hrCleanUp(); break;
	}
}

//-----현재 단계에서 해야할 서버 요청 수행--------//
HTvoid CHTNPCControl::HT_vNPCControl_ServerEvent()
{
	HTshort event = g_pEngineHandler->HT_sGetServerEvent();
	if( event == eNpcSEventReqNone )
		return;
	
	switch( event )
	{
		case eNpcSEventReqItemList : // 아이템리스트요청
			g_cUIMerchantWindow->HT_vMerchantWindow_SetBuyList();
			//HT_vNPCControl_GetItemList();
			break;
		case eNpcSEventReqRank : // 순위리스트요청
			// 순위 리스트 요청하는 네트웍 함수 호출해야함
			//MessageBox(NULL, "순위리스트요청", "순위리스트요청", MB_OK);
			break;
		case eNpcSEventReqTrimuritiSelect : // 주신선택요청
			m_bTrimutiri = 1;
			HT_vNetWork_CSP_Req_Select_Trimuriti(m_bTrimutiri);
			break;
		case eNpcSEventReqTrimuritiChange : // 주신변경요청
		{
			/*
			// 내일부터 적용됨을 알림.
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "정확한 주신변경 비용을 수집하는 기간입니다.");
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "주신변경 기능적용은 2005. 3. 16(수) 오전10시부터 가능합니다.");
			*/
			// 만약 주신투구를 착용중이라면 주신투구 해제후 다시 시도해주십시오. 라는 메시지 출력
			DWORD dwKeyID, dwindex;
			CHTString strString;
			dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(0);
			dwindex = g_cItemSystem->HT_dwSystem_GetItemIndex(dwKeyID);
			if (dwindex >= 5379 && dwindex <= 5390) // 만약 주신투구 착용중이라면
			{
				HT_g_Script_SetMessage( eMsgCommonCannotGodChange, &strString );	// 주신투구 해제후 다시 시도해주십시오.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				break;
			}
			
			// 재확인창 띄우기 - 주신을 @@신으로 변경하시겠습니까?
			HT_vNPCControl_SetMessage( eMsgTrimuritiChangeQuestion );
			
			m_bMessage_Error = HT_FALSE;	// 성공
			m_byMessageWin = NPC_MESSAGE_CONFIRM;

			g_cUINPCWindow->m_MessageBoxNo = 1;
			g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 1);
		}
			break;
		case eNpcSEventReqTrimuritiPoint : // 주신포인트요청
			g_pNetWorkMgr->RequestBrahmanPointRising();
			break;
		case eNpcSEventReqChangeJob : // 전직요청
			HT_vNetWork_CSP_REQ_Change_Job();
			break;
		case eNpcSEventReqSkillLearn : // 기술습득요청
			m_szName = HT_szNPCControl_GetSelectSkillName(); 
			break;
		case eNpcSEventReqQuestAllow : // 퀘스트 승낙 요청
		{
			BYTE byQuestIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();
			if( byQuestIndex == QUEST_SHAMBALA_14 ) // 2차 전직-지혜 퀘스트의 퀴즈 결과일 경우
			{
				if( m_bMessage_Error == HT_FALSE ) // 에러 없음
					g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG( byQuestIndex, 1);	// 모두 맞음
				else // 에러 있음
					g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG( byQuestIndex, 2);	// 틀림
			}
			else // 차크라/스킬 초기화
				g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG( byQuestIndex, SELECT_QUEST_OK);	// 승낙
		}
			break;
		case eNpcSEventReqCouponRegister : // 쿠폰 등록 요청
		{
			g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( 0 , /*0,*/ ITEM_PLACE_EVENT, m_szLottoryNum.HT_szGetString()  );
		}
			break;
		//--------- 테스크 퀘스트 요청 ---------//
		case eNpcSEventReqTaskQuest :
		{
			if( HT_bNPCControl_CheckSourceForTaskQuest( m_iTaskQuestID ) )
			{
				// 임시 선언
				//if( g_gServerType == SERVERTYPE_MAIN && m_iTaskQuestID >= TASK_QUEST_66_START && m_iTaskQuestID <= TASK_QUEST_67_END)
				//{
				//	// 퀘스트 실패 대화로 넘어감
				//	m_bMessage_Error = HT_TRUE;		// 에러 있음
				//	HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
				//}
				//else
				//{
					HT_vNetWork_CSP_Req_TaskQuest( m_iTaskQuestID );
				//}
			}
			else
			{
				HT_vNPCControl_SetMessage( eMsgTaskQuestConditionErr );
				if( m_szMessage.HT_bIsEmpty() == HT_FALSE )
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, m_szMessage );
				// 퀘스트 실패 대화로 넘어감
				m_bMessage_Error = HT_TRUE;		// 에러 있음
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 
			}
		}
			break;
		case eNpcCEventReqExpandInven :	// 인벤토리 확장 (프리미엄 기능)
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqInvenExpandBuy );

				m_bMessage_Error = HT_FALSE;	// 성공
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
				//	HT_vNetWork_CSP_Resp_Charge_Function_Item( HT_INDEX_EXPAND_INVEN );
			}
			break;
		case eNpcSEventReqExpandPrivateShop	:// 개인상점 확장 (프리미엄 기능)
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqInvenExpandBuy );

				m_bMessage_Error = HT_FALSE;	// 성공
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			} 
			break;
		case eNpcSEventReqCash : // 캐쉬정보 요청
			HT_vNetWork_CSP_Req_Item_Cash();
			break;
		case eNpcSEventReqInitialize : // 스킬/차크라 재분배 요청
			if( g_iInationalType == INATIONALTYPE_INDONESIA || g_iInationalType == INATIONALTYPE_PHILIPPINE )
                HT_vNetWork_CSP_Req_CharacterInitialize();	// 요청
			break;
		case eNpcSEventReqCharacterInitialize : // 스킬/차크라 재분배 정보 요청 (차크라)
			if( g_iInationalType == INATIONALTYPE_INDONESIA || g_iInationalType == INATIONALTYPE_PHILIPPINE )
                HT_vNetWork_CSP_Req_CharacterInitialize(1,2);
			break;
		case eNpcSEventReqCharacterInitialize2 :// 스킬/차크라 재분배 정보 요청 (스킬)
			if( g_iInationalType == INATIONALTYPE_INDONESIA || g_iInationalType == INATIONALTYPE_PHILIPPINE )
                HT_vNetWork_CSP_Req_CharacterInitialize(1,1);
			break;
		case eNpcSEventReqAutoRouting : // 자동 돈줍기 요청
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqInvenExpandBuy );

				m_bMessage_Error = HT_FALSE;	// 성공
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			}
			break;
		case eNpcSEventReqinitChacra : // 차크라 초기화 (프리미엄 기능) / 1015
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqChkraInitQuestion );

				m_bMessage_Error = HT_FALSE;	// 성공
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			}
			break;
		case eNpcSEventReqinitSkill : // 스킬 초기화 (프리미엄 기능) / 1016
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqSkillInitQuestion );

				m_bMessage_Error = HT_FALSE;	// 성공
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			}
			break;
		case eNpcSEventReqinitChacraSkill : // 차크라&스킬 초기화 (프리미엄 기능) / 1017
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqChkraSkillQuestion );

				m_bMessage_Error = HT_FALSE;	// 성공
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			}
			break;
		case eNpcSEventReqEventItemTotal : // 이벤트 아이템 아이원잇 적립 갯수 요청
			{
				m_iResent = NPC_RESENT_EVENTITEM;
				m_iEventItem = 0;
				g_cNPCControl->HT_vNetWork_CSP_Req_CharacterInitialize(1, 5);
				//g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( g_cItemSystem->HT_dwItemSystem_GetKeyIDInPCInventoryForIndex(7073), 0x01 );
			}
			break;
		case eNpcSEventReqDrugaMoneyOut : 
			{
				g_pNetWorkMgr->RequestRefineScale(); // 현재 적립금액 조회요청
			}
			break;
		case eNpcSEventReqJopChangeInit : // 2차 전직 초기화 요청
			// 재확인창 메시지를 띄움
			{

				// Step2) 아이템을 착용 및 무장 중이면 실패로 처리
				if( (g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_HEAD) + 
					g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_ARMOR) + 
					g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_BELT) + 
					g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_TWO_HAND) + 
					g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_RIGHT_HAND) + 
					g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_LEFT_HAND) + 
					g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_FOOT) + 
					g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_GLOVE) + 
					g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_PANTS)) != 0)
				{
					// 실패시 안내창 띄움
					HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// 다음 단계로 넘어감
					HT_vNPCControl_SetMessage( eMsgPremiumReq2GradeInitErr2 );
					m_bMessage_Error = HT_TRUE;
					m_byMessageWin = NPC_MESSAGE_COMPLETE;
					break;
				}


				// Step1) 이미 2차전직을 했다면 전직불가 처리
				if( g_oMainCharacterInfo.byClass1 != CLASS_LEVEL2 )	// 2차 전직일 경우에만 처리
				{

					// 실패시 안내창 띄움
					HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// 다음 단계로 넘어감
					HT_vNPCControl_SetMessage( eMsgPremiumReq2GradeInitErr );
					m_bMessage_Error = HT_TRUE;
					m_byMessageWin = NPC_MESSAGE_COMPLETE;
					break;
				}

				m_iResent = NPC_RESENT_PREMIUM_2GRADE_INIT; // 상태 기록
				HT_vNPCControl_SetMessage( eMsgPremiumReq2GradeInit ); // 메시지 리소스에서 불러오기

				m_bMessage_Error = HT_FALSE;	// (고정)
				m_byMessageWin = NPC_MESSAGE_CONFIRM;	// 메시지 종류 설정 (고정)

				// 해당메시지를 해당 다이얼로그로 보낸다.
				// 재확인창의 종류를 정의하여 화면에 뿌려준다.
				// 타이머 가동
			}
			break;
		default :
			break;
	}
}

//-----현재 단계에서 해야할 클라이언트 이벤트--------//
HTvoid CHTNPCControl::HT_vNPCControl_ClientEvent()
{
	HTshort event = g_pEngineHandler->HT_sGetClientEvent();
	if( event == eNpcCEventNone )
		return;
	

	CHTString strTemp;

	switch( event )
	{
		case eNpcCEventDialog : // 대화모드
		{
			// 일반 커서로 변경
			if(g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE)
				g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);

			if(m_iResent == NPC_RESENT_ITEM_LIST)
			{
				// 리스트 그림 지우기
				HT_vNPCControl_ButtonCheck_List_Delete();
			}

			m_iResent = NPC_RESENT_DIALOG;
			m_dwNeedValue = 0;
			m_szName.HT_hrCleanUp();
		}
			break;
		case eNpcCEventItemMake : // 구입모드
		{
			g_cUIMerchantWindow->HT_vMerchantWindow_SetBuyList();
			HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);
			m_iResent = NPC_RESENT_ITEM_LIST;
		}
			break;
		case eNpcCEventFix : // 수리모드
		{
			m_iResent = NPC_RESENT_FIX;
			// 인벤토리 창 띄움
			HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);	

			// 만약 마켓창이나 프리미엄 창이 열려있다면 닫아준다.
			if (g_cUIManager->HT_isShowWindow(_DIALOG_MERCHANT_PREMIUM) == true)
				g_cUIManager->HT_HideWindow(_DIALOG_MERCHANT_PREMIUM);

			if (g_cUIManager->HT_isShowWindow(_DIALOG_MERCHANT) == true)
				g_cUIManager->HT_HideWindow(_DIALOG_MERCHANT);
		}
			break;
		case eNpcCEventDisjoint : // 해체모드
		{
			m_iResent = NPC_RESENT_DISJOINT;
			// 인벤토리 창 띄움
			HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);	
		}
			break;
		case eNpcCEventChakraUp : // 차크라확장모드
		{
			m_iResent = NPC_RESENT_CHAKRA;
			// 캐릭터 상태창 띄우기
			HT_vNPCControl_PopUpInventory(_DIALOG_CHARINFO);
		}
			break;
		case eNpcCEventTrimuritiSelect : // 주신선택모드
			m_iResent = NPC_RESENT_TRIMURITI;
			m_bySelectPart = 0;
			break;
		// 고대 주술서(7134) 15개
		case eNpcCEventTrimuritiChange : // 주신변경모드
			m_iResent = NPC_RESENT_TRIMURITI_CHANGE;
			m_bySelectPart = 0;
			break;
		case eNpcCEventCreateGuild : // 아쉬람생성모드
		{
			m_iResent = NPC_RESENT_CREATE_GILD;
			g_cGuildSystem->HT_vGuild_Create();
		}
			break;
		case eNpcCEventCreateGuildMark : // 아쉬람마크생성모드
		{
			m_iResent = NPC_RESENT_CREATE_GILD_MARK;
			// 아쉬람 마크생성 창 띄운다
			g_cGuildSystem->HT_vGuild_AmblemMakeActive();
		}
			break;
		case eNpcCEventChangeJob2 : // 2차 전직모드
			m_iResent = NPC_RESENT_CHANGE_JOB2;
			break;
		case eNpcCEventBramanPointUp : // 브라만확장모드
		{
			m_iResent = NPC_RESENT_BRAHMAN;
			// 캐릭터 상태창 띄우기
			HT_vNPCControl_PopUpInventory(_DIALOG_CHARINFO);
		}
			break;
		case eNpcCEventInventory : // 물품보관모드
		{	
			// NPC Inventory의 아이템들을 보이게 한다.
			m_iResent = NPC_RESENT_INVENTORY;
			
			// 착용가능/불가능 바 갱신
			g_cItemSystem->HT_vItemSystem_RenewalPossibleBar(_DIALOG_GOODSKEEPWND);
			g_cUIManager->HT_ShowWindow( _DIALOG_GOODSKEEPWND );
			HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);	// 인벤토리 창 띄움
		}
			break;
		case eNpcCEventSavePosition : // 위치저장모드
		{
			m_iResent = NPC_RESENT_SAVEPOSITION;
			
			// 저장할것인지 재확인 메세지 띄운다
			// 현재 위치를 저장 하시겠습니까?
			HT_vNPCControl_SetMessage( eMsgSavePositionQuestion );
			
			m_bMessage_Error = HT_FALSE;	// 성공
			m_byMessageWin = NPC_MESSAGE_CONFIRM;
			
			g_cUINPCWindow->m_MessageBoxNo = 0;
			g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW , m_szMessage, 1);
		}
			break;
		case eNpcCEventRank : // 순위열람모드
		{
			m_iResent = NPC_RESENT_PVP_RANK;
			//	순위 리스트창 열기
			//	랭킹결과가 오면 창에다가 등록하고 나서 오는부분
		}
			break;
		case eNpcCEventEvent : // 이벤트 등록 모드
		{
			m_iResent = NPC_RESENT_REGIST_LOTTERY;
			// 쿠폰 번호 등록하기 위한 입력창 띄우기
			HT_g_Script_SetMessage( eMsgSerialNumber, &strTemp, _T("") );		//	"일련 번호"
			HT_g_Script_SetMessage( eMsgEnlistmentNotice, &strTemp, _T("") );		//	"[입영 통지서]의 "
			HT_g_Script_SetMessage( eMsgSerialNumber, &strTemp, _T("") );		//	"일련 번호"
			m_szLottoryNum.HT_hrCleanUp(); // 쿠폰 입력창 초기화
		}
			break;
		case eNpcCEventChaturangaBoard : // 차투랑가 보드 열람 모드
			m_iResent = NPC_RESENT_CHATURANGA_BOARD;
			// 차투랑가 보드 열기
			HT_vNPCControl_ActiveChaturangaBoard();
			break;
		case eNpcCEventQuiz : // 퀴즈
			m_iResent = NPC_RESENT_QUIZ;
			m_iQuestQuizCount = 0; // 퀴즈 번호
			break;
		case eNpcCEventReqPriItemList : // 구입 대기 모드 - 구입 리스트 만들기 (프리미엄 아이템)
			m_iResent = NPC_RESENT_PREMIUM_ITEM;
			break;
		case eNpcCEventReqPriItemList2 :// 구입 대기 모드 - 구입 리스트 만들기 (패키지 프리미엄 아이템)
			m_iResent = NPC_RESENT_PREMIUM_ITEM2;
			break;
		case eNpcCEventReqPriItemList3 :// 구입 대기 모드 - 구입 리스트 만들기 (패키지 프리미엄 아이템)
			m_iResent = NPC_RESENT_PREMIUM_ITEM3;
			break;
		case eNpcCEventReqEventItem : // 이벤트 아이템 사용 요청 (아이원잇, 컴리드) 3029
			m_iResent = NPC_RESENT_EVENTITEM; 
			// 먼저 아이템을 받을 공간이 있어야 가능하도록 설정.
			// 인벤토리 공간 체크
			if (g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck() < 1)
			{
				// 만약 공간이 부족하면 사용하지 못하게 한다
				CHTString strString;
				HT_g_Script_SetMessage( eMsgItemCommonInvenLack, &strString );	// 인벤토리 공간이 부족합니다.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				return;
			}

			g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( g_cItemSystem->HT_dwItemSystem_GetKeyIDInPCInventoryForIndex(7079), 0x01 );
			break;
		case eNpcCEventReqDrugaMoneyIn : 
			m_iDurgaReceiptofMoney = -1;
			g_cEquipInventory->HT_vRupiahWin_Active();		// 루피아 언패킹 윈도우 팝업
			break;
		case eNpcCEventReqYutWindowPopup :		
			g_cGamble->HT_vGamble_WindowPopup();			// 윷놀이 상황판 팝업
			break;
		case eNpcCEventReqEventCoupon : // 이벤트 쿠폰 사용 요청
			//m_iResent = NPC_RESENT_EVENTCOUPON;
			//if( g_iInationalType == INATIONALTYPE_INDONESIA )
				//g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, "Welcome to Tantra World!!!.  Palease Input your coupon number", 5);
			//else
			g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, "탄트라 월드에 오신것을 환영합니다. 소지하신 쿠폰의 쿠폰번호를 입력해 주세요.", 5);
			g_cUINPCWindow->m_MessageBoxNo = 2;
			g_cUIManager->HT_SetEditBoxControlLimitText(_DIALOG_NPCWINDOW+999, 1, 15);	// 억단위까지만 입력받음
			break;
		case eNpcCEventReqCheckWindowPopup : // 출석체크 이벤트 윈도우 팝업 요청 (3033)
			g_pEventWindow->HT_vEventWindow_ReqAttendance();
			break;
		case eNpcCEventReqComeback : // 컴백(초토화) 이벤트 (3034)
			{
				int iSex, iSelectTribe;
				(g_oMainCharacterInfo.snTribe < 4) ? iSex = 0 : iSex = 1;	// 0 = 남자, 1 = 여자
				iSelectTribe = (g_cUINPCWindow->HT_vGetNPCWindow_ButtonNo()) + (iSex * 4);
				
				g_pEventWindow->HT_vEventWnd_ReqChangeTribe(iSelectTribe);
			}
			break;
		case eNpcCEventReqGetYutMoneyList : // 성주가 받을 수 있는 윳 세금조회(3035)
			{
				if (g_pSiege->HT_vSiege_GetOwerOfCastle() && g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_MAHARAJA )	// 먼저 성주인지 아닌지 조사
				{
					g_pSiege->m_iGetMoneyType = 1;	// 윷세금
					g_pSiege->m_iGetMoneyAction = 1;	// 조회
					g_pSiege->HT_vSiege_NetworkCSP_GetMoney();
				}
				else
				{	
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "성주만이 적립된 세금을 받을 수 있습니다.");
					//g_cNPCControl->HT_vNPCControl_GetNextStep(2);
					break;
				}
			}
			break;
		case eNpcCEventReqGetYutMoney : // 성주가 받을 수 있는 윳 세금요청 (3036)
			{
				g_pSiege->m_iGetMoneyType = 1;		// 윷세금
				g_pSiege->m_iGetMoneyAction = 2;	// 받기
				g_pSiege->HT_vSiege_NetworkCSP_GetMoney();
			}
			break;
		case eNpcCEventReqQuestEvent1 : // 북두쭈앙즈 이벤트 
			{			// 북두쭈앙즈를 사라지게 하고 대사창을 닫는다.
			}
			break;
		case eNpcCEventReqQuestEvent2 : // 북두쭈앙즈 이벤트 
			{		// 북두쭈앙즈를 사라지게 하고 대사창을 닫는다.
			}
			break;
		case eNpcCEventReqGuildCargoOpenWindow : // 길드창고 오픈창
			{
				//	아쉬람이 없으면 스킵
				if( g_cGuildSystem->HT_iGuild_GetGuildID() == 0 )
					break;
				g_cGuildSystem->HT_vAshram_CSPAshramItem();
			}
			break;
		case eNpcCEventReqGuildCargoShowInfo : // 길드창고 정보 요청
			{
				//	아쉬람이 없으면 스킵
				if( g_cGuildSystem->HT_iGuild_GetGuildID() == 0 )
					break;
				//	마하라자가 아니면 스킵
				if( g_cGuildSystem->HT_byGuild_GetAuthority() != GUILD_AUTHORITY_MAHARAJA )
					break;
				g_cUIManager->HT_ShowWindow(_DIALOG_SANCTIONASHCAGO);
			}
			break;
		case eNpcCEventReqGuildCargoSetPMT : // 길드창고 권한 설정
			{
				//	아쉬람이 없으면 스킵
				if( g_cGuildSystem->HT_iGuild_GetGuildID() == 0 )
					break;
				//	마하라자가 아니면 스킵
				if( g_cGuildSystem->HT_byGuild_GetAuthority() != GUILD_AUTHORITY_MAHARAJA )
					break;
				g_cUIManager->HT_ShowWindow(_DIALOG_SETLEVELASHCAGO);
			}
			break;
		// 비류성 위탁판매 관리자 (자신의 아이템 판매현황 보기) - 3042 - (판매 리스트창 팝업)
		case eNpcCEventReqRentalAdminSellInfo :	
			{
				g_cRentalStore->HT_EventReqRentalAdminSellInfo();
			}
			break;
		// 비류성 위탁판매 관리자 (자신의 아이템 돌려받기) - 3043 - (보관중인 아이템 찾기요청 패킷 호출)
		case eNpcCEventReqRentalAdminReciveItem	: 
			{
				g_cRentalStore->HT_EventReqRentalAdminReciveItem();
			}
			break;
		// 비류성 위탁판매 관리자 (자신의 아이템 돌려받을 리스트 보기) - 3044 - (보관중인 리스트창 팝업)
		case eNpcCEventReqRentalAdminReciveList	:
			{
				g_cRentalStore->HT_EventReqRentalAdminReciveList();
			}
			break;
		// 비류성 위탁판매 일반인 (판매중인 아이템 목록보기) - 3045 (위탁상점창 팝업) - 구입모드
		case eNpcCEventReqRentalBuyList	:
			{
				g_cRentalStore->HT_EventReqRentalBuyList();
			}
			break;
		// 비류성 위탁판매 일반인 (자신의 아이템 판매) - 3046 (위탁상점창 팝업) - 판매모드
		case eNpcCEventReqRentalSell :
			{
				g_cRentalStore->HT_EventReqRentalSell();
			}
			break;
		// 비류성 위탁판매 관리자 (위탁판매 이용 세금 보기) - 3047 (스크립트로 출력)
		case eNpcCEventReqRentalUsingTex :
			{
				g_cRentalStore->HT_EventReqRentalUsingTex();
			}
			break;
		// 비류성 위탁판매 관리자 (위탁판매 아이템 루피아 보기) - 3048 (스크립트로 출력)
		case eNpcCEventReqRentalItemRupia :
			{
				g_cRentalStore->HT_EventReqRentalItemRupia();
			}
			break;
		// 비류성 위탁판매 관리자 (위탁판매 이용 세금 설정) - 3049 (스크립트로 출력)
		case eNpcCEventReqRentalSetTex :
			{
				g_cRentalStore->HT_EventReqRentalSetTex();
			}
			break;
		case eNpcCEventCallPaySystem : // 전자지불 시스템 호출 2004. 9. 14 선영범
			{
				if( g_iInationalType == INATIONALTYPE_KOREA || 
					g_iInationalType == INATIONALTYPE_CHINA || 
					g_iInationalType == INATIONALTYPE_INDONESIA )
				{
					CHTString strWeb;
					HT_g_Script_SetMessage( eURLfilling_cash, &strWeb, _T("") );
					strWeb += _T("?CashID=");
					strWeb += g_strLoginID;
					strWeb += _T("&CashPass=");
					strWeb += g_strLgoinPasswordMD5;
/*
					CHTString strWeb;
					HT_g_Script_SetMessage( eURLfilling_cash, &strWeb, _T("") );
					strWeb += _T("?CashID=");
					strWeb += g_strLoginID;
					strWeb += _T("&CashPass=");
					strWeb += g_strLgoinPasswordMD5;*/
					HTRESULT hResult = HT_OK;
					if (HT_FAILED( hResult = g_pEngineHandler->JK_hrWebMgr_SetOpenWeb( 0, g_hWnd, strWeb, 10, g_pEngineHandler->HT_iGetScreenWidth()/2-400, g_pEngineHandler->HT_iGetScreenHeight()/2-300, 800, 550 ) ) )
					{
						if ( hResult == HT_FAIL )
						{
							//타니 결제 서버가 응답하지 않습니다. 잠시 후에 다시 시도해 주시기 바랍니다.
							HT_vNPCControl_SetMessage( eMsgPremiumPaySystemErr );

							m_bMessage_Error = HT_TRUE;
							// 완료(에러)창
							m_byMessageWin = NPC_MESSAGE_COMPLETE;
						}
						else if ( hResult == 1 )
						{
							// 타니 결제 서버 연결을 위한 프로그램 초기화에 실패했습니다.
							// FAILED( CoInitialize( HT_NULL ) )
							HT_vNPCControl_SetMessage( eMsgPremiumPaySystemErr2 );

							m_bMessage_Error = HT_TRUE;
							// 완료(에러)창
							m_byMessageWin = NPC_MESSAGE_COMPLETE;
						}
						else if ( hResult == 2 )
						{
							// 타니 결제 서버 연결 초기화에 실패했습니다.
							// FAILED( CoCreateInstance( CLSID_InternetExplorer, HT_NULL, CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (LPVOID*)&m_pWebBrowser ) )
							HT_vNPCControl_SetMessage( eMsgPremiumPaySystemErr3 );

							m_bMessage_Error = HT_TRUE;
							// 완료(에러)창
							m_byMessageWin = NPC_MESSAGE_COMPLETE;
						}
						else if ( hResult == 3 )
						{
							// 타니 결제 서버 연결을 위한 프로그램 검색에 실패했습니다.
							// ( m_hWndExplorer = FindWindow( "IEFrame", "Microsoft Internet Explorer" ) ) == NULL
							HT_vNPCControl_SetMessage( eMsgPremiumPaySystemErr4 );

							m_bMessage_Error = HT_TRUE;
							// 완료(에러)창
							m_byMessageWin = NPC_MESSAGE_COMPLETE;
						}
						else
						{
							// 타니 결제 서버가 알 수 없는 오류를 만들었습니다.
							HT_vNPCControl_SetMessage( eMsgPremiumPaySystemErr5 );

							m_bMessage_Error = HT_TRUE;
							// 완료(에러)창
							m_byMessageWin = NPC_MESSAGE_COMPLETE;
						}
					}
				}
				//m_bNextStepByClientEvent = HT_TRUE;
				break;
			}

		case eNpcCEventTransformationShop:	// 종합 미용실 (프리미엄) /3023
			{
				if( g_cUIManager->HT_isShowWindow( _DIALOG_BEAUTYSALON2 ) )
				{
					g_cStatus->HT_vStatus_BeautyBack();	// 원래상태로 성형 돌림
					g_cUIManager->HT_HideWindow(_DIALOG_BEAUTYSALON2);
				}
				
				// 종합미용실 다이알로그 띄움
				CHTString strName;
				g_cStatus->m_nCharacterTribe = -1;
				g_cStatus->HT_vStatus_Beauty_Render(_DIALOG_BEAUTYSALON);
				g_cUIManager->HT_ShowWindow(_DIALOG_BEAUTYSALON);
				strName.HT_szFormat( "%d", g_cStatus->m_iBuyTany );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_BEAUTYSALON, 3, strName );
				strName.HT_szFormat( "%d", g_cNPCControl->HT_iNPCControl_GetCash() );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_BEAUTYSALON, 4, strName );
				break;
			}

		case eNpcCEventMuUseInfo: // 내 사용 내역 보기 3026
			{
				// 내 사용 내역 다이알로그 띄움
				g_cUIManager->HT_ShowWindow( _DIALOG_MY_USEINFO_V3 );
				g_cIndividualStore->HT_vIndividualStore_ButtonCheckForUseListOutPut();
				break;
			}


		case eNpcCEventCreatePremiumGuildMark:  // 아쉬람 마크 생성 (프리미엄) /3024
			{
				// 시스템 창에 표시
				if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )			g_cGuildSystem->m_iSelectWindow = 1;	// 일반 아쉬람 만들기 창으로 셋팅
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )		g_cGuildSystem->m_iSelectWindow = 2;	// 일반 아쉬람 만들기 창으로 셋팅
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )		g_cGuildSystem->m_iSelectWindow = 3;	// 일반 아쉬람 만들기 창으로 셋팅

				g_cGuildSystem->HT_vGuild_DialogBoxDrawTab(1);
				g_cGuildSystem->HT_bGuild_DialogBoxDrawEmblem(0);
				g_cUIManager->HT_ShowWindow(_DIALOG_AMBLEM);
				break;
			}

		case eNpcCEventJob2Select : // 2차 직업 선택 모드
			m_iResent = NPC_RESENT_JOB2_SELECT;
			break;

		case eNpcCEventCharacterInitialize : // 캐릭터 스킬/차크라 초기화 정보 요청 결과 2004. 8. 27
			{
				if (m_nFirst == 1) // 처음인가 아닌가에 따라 분기
				{
					m_nFirst2 = 1;
					HT_vNPCControl_GetNextStep( m_nSelectCount );
				}
				else 
				{
					m_nFirst2 = 2;
					HT_vNPCControl_GetNextStep( m_nSelectCount+1);
				}
			}
			break;

		case eNpcCEventInitialize : // 캐릭터 스킬/차크라 초기화 요청 결과 2004. 8. 27
			{
				if (m_nNowRupia >= m_nNeedRupia) // 루피아를 추출하여 그에 따라 분기한다.(임시)
				{
					HT_vNPCControl_GetNextStep( m_nSelectCount );
				}
				else
				{
					HT_vNPCControl_GetNextStep( m_nSelectCount+1);
				}
				m_bNextStepByClientEvent = HT_TRUE;
			}
			break;
		case eNpcCEventInformationShow : // 여사제에게 정보 게시판 보기 팝업처리 2004. 11. 9
			{
				CHTString strString;
				if ( g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenWarning, &strString ) )
				{
					// 해당 블로그가 전체 화면으로 활성화 됩니다. 계속하시겠습니까?
					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 1 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_PERSONALBOARD;
				}
			}
			break;

		//-------- 테스크 퀘스트 ---------//
		case eNpcCEventTaskQuest : 
			// 실제 테스크 메뉴가 몇단계 깊숙이 있을 경우 인벤을 열기 위해 
			// 인벤토리 창 띄움
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;
		case eNpcCEventTaskQuest1 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_1;
			// 인벤토리 창 띄움
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;

		case eNpcCEventTaskQuest2 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_8;
			// 인벤토리 창 띄움
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;

		case eNpcCEventTaskQuest3 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_15;
			// 인벤토리 창 띄움
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;
		case eNpcCEventTaskQuest4 : // 카야 합성
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_20;
			// 인벤토리 창 띄움
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;
		case eNpcCEventTaskQuest5 : // 한 손 무기 제작
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_27;
			// 인벤토리 창 띄움
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;
		case eNpcCEventTaskQuest6 : // 양손 무기 제작
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_32;
			// 인벤토리 창 띄움
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;
		// 수집 아이템으로 1차 재료 추출
		case eNpcCEventTaskQuest7 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_38;
			break;
		case eNpcCEventTaskQuest8 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_45;
			break;
		case eNpcCEventTaskQuest9 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_52;
			break;
		case eNpcCEventTaskQuest10 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_58;
			break;
		case eNpcCEventTaskQuest11 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_64;
			break;
		case eNpcCEventTaskQuest12 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_70;
			break;
		case eNpcCEventTaskQuest13 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_76;
			break;
		// 방어구 분리를 통한 부분품 추출
		case eNpcCEventTaskQuest14 : // 나가, 킨나라용
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_82;
			break;
		case eNpcCEventTaskQuest15 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_87;
			break;
		case eNpcCEventTaskQuest16 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_92;
			break;
		case eNpcCEventTaskQuest17 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_97;
			break;
		case eNpcCEventTaskQuest18 : // 아수라, 락샤샤 용
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_102;
			break;
		case eNpcCEventTaskQuest19 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_107;
			break;
		case eNpcCEventTaskQuest20 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_112;
			break;
		case eNpcCEventTaskQuest21 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_117;
			break;
		case eNpcCEventTaskQuest22 : // 야크샤, 간다르바 용
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_122;
			break;
		case eNpcCEventTaskQuest23 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_127;
			break;
		case eNpcCEventTaskQuest24 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_132;
			break;
		case eNpcCEventTaskQuest25 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_137;
			break;
		case eNpcCEventTaskQuest26 : // 데바, 가루다 용
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_142;
			break;
		case eNpcCEventTaskQuest27 : 
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_147;
			break;
		case eNpcCEventTaskQuest28 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_152;
			break;
		case eNpcCEventTaskQuest29 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_157;
			break;
		// 부분품 분리를 통한 1차 재료 추출
		case eNpcCEventTaskQuest30 : // 사트반급
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_162;
			break;
		case eNpcCEventTaskQuest31 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_170;
			break;
		case eNpcCEventTaskQuest32 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_178;
			break;
		case eNpcCEventTaskQuest33 : // 드반타급
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_182;
			break;
		case eNpcCEventTaskQuest34 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_190;
			break;
		case eNpcCEventTaskQuest35 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_198;
			break;
		case eNpcCEventTaskQuest36 : // 너바나급
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_202;
			break;
		case eNpcCEventTaskQuest37 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_210;
			break;
		case eNpcCEventTaskQuest38 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_218;
			break;
		case eNpcCEventTaskQuest39 : // 만트리카급
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_222;
			break;
		case eNpcCEventTaskQuest40 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_230;
			break;
		case eNpcCEventTaskQuest41 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_238;
			break;
		// 1차 재료로 종족 방어구 부분품 제작
		case eNpcCEventTaskQuest42 : // 사트반급
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_242;
			break;
		case eNpcCEventTaskQuest43 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_250;
			break;
		case eNpcCEventTaskQuest44 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_258;
			break;
		case eNpcCEventTaskQuest45 : // 드반타급
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_262;
			break;
		case eNpcCEventTaskQuest46 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_270;
			break;
		case eNpcCEventTaskQuest47 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_278;
			break;
		case eNpcCEventTaskQuest48 : // 너바나급
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_282;
			break;
		case eNpcCEventTaskQuest49 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_290;
			break;
		case eNpcCEventTaskQuest50 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_298;
			break;
		case eNpcCEventTaskQuest51 : // 만트리카급
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_302;
			break;
		case eNpcCEventTaskQuest52 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_310;
			break;
		case eNpcCEventTaskQuest53 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_318;
			break;
		// 방어구 제작
		case eNpcCEventTaskQuest54 : // 나가, 킨나라 용
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_322;
			break;
		case eNpcCEventTaskQuest55 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_327;
			break;
		case eNpcCEventTaskQuest56 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_332;
			break;
		case eNpcCEventTaskQuest57 : // 아수라, 락샤샤 용
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_337;
			break;
		case eNpcCEventTaskQuest58 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_342;
			break;
		case eNpcCEventTaskQuest59 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_347;
			break;
		case eNpcCEventTaskQuest60 : // 야크샤, 간다르바 용
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_352;
			break;
		case eNpcCEventTaskQuest61 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_357;
			break;
		case eNpcCEventTaskQuest62 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_362;
			break;
		case eNpcCEventTaskQuest63 : // 데바, 가루다 용
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_367;
			break;
		case eNpcCEventTaskQuest64 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_372;
			break;
		case eNpcCEventTaskQuest65 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_377;
			break;
		case eNpcCEventTaskQuest66 :			// 지나마을 뤼샨(1134)의 테스크 퀘스트 추가 2004. 9. 1 선영범
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_383;
			break;
		case eNpcCEventTaskQuest67 :			// 지나마을 뤼샨(1134)의 테스크 퀘스트 추가 2004. 9. 1 선영범
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_389;
			break;
		case eNpcCEventTaskQuest68 :			// // 10388	만다라 여사제의 퀘스트	1120 
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_390;
			break;
		case eNpcCEventTaskQuest69 :			// // 10389	샴발라 여사제의 퀘스트	1154
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_391;
			break;
		case eNpcCEventTaskQuest70 :			// // 10390	지나 여사제의 퀘스트	1155
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_392;
			break;
		case eNpcCEventTaskQuest71 :			// // 10391	유배지 여사제의 퀘스트	1156
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_393;
			break;
		case eNpcCEventTaskQuest72 :			// // 10392	브라흐마 여사제의 퀘스트	1254 (스크립트에서는 무조건 1254로 들어오므로 여기서 다시 재분배 함)
		case eNpcCEventTaskQuest73 :			// // 10393	비슈누 여사제의 퀘스트	1255
		case eNpcCEventTaskQuest74 :			// // 10394	시바 여사제의 퀘스트	1256
			switch (m_iNPCIndex)
			{
			case 1254:	// 브라흐마
				m_iResent = NPC_RESENT_TASK_QUEST;
				m_iTaskQuestID = QUEST_TASK_394;
				break;
			case 1255: // 비슈느
				m_iResent = NPC_RESENT_TASK_QUEST;
				m_iTaskQuestID = QUEST_TASK_395;
				break;
			case 1256:
				m_iResent = NPC_RESENT_TASK_QUEST;
				m_iTaskQuestID = QUEST_TASK_396;
				break; // 시바
			}
			break;

		case eNpcCEventTaskQuest75 :			// 크리스마스 퀘스트 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_397;
			break;

		case eNpcCEventTaskQuest76 :			// 라푸 크리스탈 업그레이드 테스크 퀘스트 1
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_398;
			break;

		case eNpcCEventTaskQuest77 :			// 라푸 크리스탈 업그레이드 테스크 퀘스트 2
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_399;
			break;

		case eNpcCEventTaskQuest78 :			// 라훌 요술주머니 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_400;
			break;

		case eNpcCEventTaskQuest79 :			// 유배지 퀘스트 (무사용 순례자의 증표)
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_401;
			break;

		case eNpcCEventTaskQuest80 :			// 유배지 퀘스트 (술사용 순례자의 증표)
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_402;
			break;

		case eNpcCEventTaskQuest81 :			// 요새전 카우스트밤 제작
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_403;
			break;

		case eNpcCEventTaskQuest82 :			// 요새전 카우스트밤을 이용해 아이템 소환
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_404;
			break;

		case eNpcCEventTaskQuest83 :			// 라훌 프라다야
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_405;
			break;

		case eNpcCEventTaskQuest84 :			// 뤼샨 비르티1
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_406;
			break;

		case eNpcCEventTaskQuest85 :			// 뤼샨 비르티2
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_407;
			break;

		case eNpcCEventTaskQuest86 :			// 뤼샨 비르티3
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_408;
			break;
		
		case eNpcCEventTaskQuest87 :			// 뤼샨 비르티4
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_409;
			break;

		case eNpcCEventTaskQuest88 :			// 라훌 속성 변경 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_410;
			break;

		case eNpcCEventTaskQuest89 :			// 하라티 원석 가공
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_411;
			break;

		case eNpcCEventTaskQuest90 :			// 요새전 만물상 테퀘
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_412;
			break;

		case eNpcCEventTaskQuest91 :			// 라훌
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_413;
			break;

		case eNpcCEventTaskQuest92 :			// 북퀘 토용장인
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_414;
			break;

		case eNpcCEventTaskQuest93 :			// 북퀘 쫑꾸이
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_415;
			break;

		case eNpcCEventTaskQuest94 :			// 크리스탈 12차 퀘1
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_416;
			break;

		case eNpcCEventTaskQuest95 :			// 크리스탈 12차 퀘2
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_417;
			break;

		case eNpcCEventTaskQuest96 :			// 크리스탈 12차 퀘3
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_418;
			break;

		case eNpcCEventTaskQuest97 :			// 12월 플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_419;
			break;

		case eNpcCEventTaskQuest98 :			// 드랍 프라나 테스크 퀘스트 // 샴발라성 마호멧
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_420;
			break;

		case eNpcCEventTaskQuest99 :			// 드랍 프라나 테스크 퀘스트 // 아누마을 재단사 사라뉴
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_421;
			break;

		case eNpcCEventTaskQuest100 :			// 드랍 프라나 테스크 퀘스트 // 지나마을 전투승려 이떵따셔
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_422;
			break;

		case eNpcCEventTaskQuest101 :			// 드랍 프라나 테스크 퀘스트 // 지나마을 잡화상인 뤼샨
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_423;
			break;

		case eNpcCEventTaskQuest102 :			// 드랍 프라나 테스크 퀘스트 // 유배지 수행승 우쏭
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_424;
			break;

		case eNpcCEventTaskQuest103 :			// 드랍 프라나 테스크 퀘스트 // 유배지 창고지기 보오러
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_425;
			break;

		case eNpcCEventTaskQuest104 :			// 설날 이벤트 대사
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_426;
			break;

		case eNpcCEventTaskQuest105 :			// 플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_427;
			break;

		case eNpcCEventTaskQuest106 :			// 플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_428;
			break;

		case eNpcCEventTaskQuest107 :			// 플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_429;
			break;

		case eNpcCEventTaskQuest108 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_430;
			break;
		case 4117 :			// 4월플래티넘 꾸러미 이벤트 //fors_debug 닒侶쟁역迦꿨흙劤훨蛟
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10553;
			break;
		case 4118 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10554;
			break;
		case 4119 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10555;
			break;
		case 4120 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10556;
			break;
		case 4121 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10557;
			break;
		case 4122 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10558;
			break;
		case 4123 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10559;
			break;
		case 4124 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10560;
			break;
		case 4125 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10561;
			break;
		case 4126 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10562;
			break;
		case 4127 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10563;
			break;
		case 4128 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10564;
			break;
		case 4129 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10565;
			break;
		case 4130 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10566;
			break;
		case 4131 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10567;
			break;
		case 4132 :			// 4월플래티넘 꾸러미 이벤트
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10568;
			break;
		//--------- 상태 검사 ---------//
		case eNpcCEventCheckTrimuritiPoint : // 주신포인트조건검사
		{
			m_iResent = NPC_RESENT_TRIMURITI_POINT;
			m_nSelectCount = 0;
			// 에러가 있을 경우 확인메세지창을 처리하고 다음단계로 넘어간다.
			if( HT_bNPCControl_CheckConditionBrahmanPointRising() == HT_TRUE )
			{
				HT_vNPCControl_GetNextStep( m_nSelectCount );
				m_bNextStepByClientEvent = HT_TRUE;
			}
		}
			break;
		case eNpcCEventCheckChangeJob : // 전직검사
		{
			m_nSelectCount = 0;
			if( g_oMainCharacterInfo.byClass1 == CLASS_LEVEL2 )	// 전직을 모두 했음
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount );
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		case eNpcCEventCheckGuild : // 아쉬람검사
		{
			m_nSelectCount = 0;
			// 주신이 선택되어있는 경우
			if( g_oMainCharacterInfo.byTrimuriti != 0 )
				HT_vNPCControl_GetNextStep( m_nSelectCount );
			// 주신을 선택하지 않은 경우 주신 선택메뉴로 전환
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		case eNpcCEventCheckTrimuriti : // 주신검사
		{
			m_nSelectCount = 0;
			m_bTrimutiri = 0;
			HT_vNetWork_CSP_Req_Select_Trimuriti(m_bTrimutiri);	// 조회 요청

			// 주신을 선택하기 위함인지 변경하기 위함인지 검사
			if( g_oMainCharacterInfo.byTrimuriti == 0 )
				HT_vNPCControl_GetNextStep( m_nSelectCount );	// 선택
			else
			{
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );	// 변경
			}
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		case eNpcCEventCheckChakraInit : // 차크라 초기화 조건 검사
		{
			m_nSelectCount = 0;
			if( HT_bNPCControl_CheckConditionChakraInit() == HT_TRUE )
				HT_vNPCControl_GetNextStep( m_nSelectCount );
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		case eNpcCEventCheckSkillInit : // 스킬 초기화 조건 검사
		{
			m_nSelectCount = 0;
			if( HT_bNPCControl_CheckConditionSkillInit() == HT_TRUE )
				HT_vNPCControl_GetNextStep( m_nSelectCount );
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		case eNpcCEventCheckSkillInit2 : // 스킬 초기화 이벤트
			{
				// 초기화 실행
				//m_iNPCIndex = 1106;
				m_nType = 1;
				this->HT_vNetWork_CSP_Req_CharacterInitialize(2, 1);
			}
			break;
		case eNpcCEventCheckJob2ChangeItem : // 2차 전직용 아이템 검사
		{
			m_nSelectCount = 0;
			HTint iSel = HT_iNPCControl_CheckItemForChangeJob2();
			if( 0 <= iSel && iSel <= MAX_SELECT_COUNT )
			{
				HT_vNPCControl_GetNextStep( m_nSelectCount+iSel );
				m_bNextStepByClientEvent = HT_TRUE;
			}
		}
			break;
		case eNpcCEventCheckEvent : // 이벤트 등록 조건 검사
		{
			m_nSelectCount = 0;
			if( HT_bNPCControl_CheckConditionCoupon() == HT_TRUE )
				HT_vNPCControl_GetNextStep( m_nSelectCount ); // 쿠폰 등록 모드로
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		//--------- 미구현 ----------//
		case eNpcCEventSkillLearn : // 기술모드
		{
			m_nSkillList_Count = 0;	// 습득 가능한 스킬 수
			m_dwSkillRegistIndex = 0;
			m_dwSkillRegistType = 0;

			m_iResent = NPC_RESENT_SKILL;
		}
			break;
		case eNpcCEventSkillRemove : // 기술삭제모드
		{
			m_iResent = NPC_RESENT_SKILL_REMOVE;
			HT_vNPCControl_GetSkillList();	// 삭제 가능한 기술 리스트 조사
		}
			break;
		default : break;
	}

	// 이전 단계가 리스트 또는 제조 단계였을 경우 창을 닫아준다
	if(m_iResent != NPC_RESENT_ITEM_LIST )
	{
		// 리스트 창 안보이게..
		HT_vNPCControl_ListAntiActive();
	}
	// 이전 단계가 재련단계였을 경우 창을 닫아준다
	if( m_iResent != NPC_RESENT_REFINE && g_cUIManager->HT_isShowWindow( _DIALOG_REFINE ) == HT_TRUE )
	{
		HT_vNPCControl_ButtonCheck_Work_Delete();		
	}

	// 이전 단계가 물품보관 단계였을 경우 Inventory 창을 닫아준다
	if( (m_iResent != NPC_RESENT_INVENTORY) )
	{
		// 아이템 언패킹창 닫기
		g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );
	}
	// 이전 단계가 순위열람 단계였을 경우 창을 닫아준다
	if( (m_iResent != NPC_RESENT_PVP_RANK) )
	{
	}
}

HTvoid CHTNPCControl::HT_vNPCControl_Control()
{
	// NPC와 대화중 이거나 제련중 일 때
	if( m_bNPCActive == HT_TRUE || m_iResent == NPC_RESENT_REFINE )
	{
		// 캐릭터 위치체크_캐릭터 움직이면 다운시킨다
		HT_vNPCControl_CharPos_Check();
	}

	if( m_iResent == NPC_RESENT_REFINE_RATE_UP )
	{
		HTfloat fCurrentTime = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );
		if( fCurrentTime - m_fGaugeTimer >= HT_REQ_REFINESCALE_TIME )
			g_pNetWorkMgr->RequestRefineScale(); // 현재 헌납 게이지 요청

		// 캐릭터 위치체크_캐릭터 움직이면 다운시킨다
		HT_vNPCControl_CharPos_Check();
	}
}

//----------캐릭터 위치체크_캐릭터 움직이면 창을 다운시킨다----------//
HTvoid CHTNPCControl::HT_vNPCControl_CharPos_Check()
{
	HTPoint pCheckGet = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	if( m_pCharPos_Memory.x != pCheckGet.x || m_pCharPos_Memory.y != pCheckGet.y )
	{
		//	대화상자 닫기 - NPC와 관련된 모든 창 닫힘
		HT_vNPCControl_DialogWin_AntiActive();

		m_bNPCActive = HT_FALSE;
		m_byMessageWin = NPC_MESSAGE_NONE;

	}
}

//----- 대화상자 닫기 -----//
HTvoid CHTNPCControl::HT_vNPCControl_DialogWin_AntiActive()
{
	// 프리미엄 창이 열려 있는 경우에도 창 닫아줌.

	if( g_cUIManager->HT_isShowWindow( _DIALOG_MERCHANT_PREMIUM ))
	{
		g_cUIManager->HT_HideWindow(_DIALOG_MERCHANT_PREMIUM );
	}
	if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ))
	{
		g_cUIManager->HT_HideWindow(_DIALOG_NPCWINDOW );
	}
	//	리스트 닫기
	if(g_cUIManager->HT_isShowWindow( _DIALOG_RENTALSTORE ) == HT_TRUE)	
	{
		g_cUIManager->HT_HideWindow(_DIALOG_RENTALSTORE );
	}
	//	리스트 닫기
	if(g_cUIManager->HT_isShowWindow( _DIALOG_MERCHANT ) == HT_TRUE)	
	{
		HT_vNPCControl_ButtonCheck_List_Delete();
	}
	//	제조창 닫기
	if(g_cUIManager->HT_isShowWindow( _DIALOG_REFINE ) == true)
	{
		// 제조창으로 이동했던 아이템 이미지 모두 삭제
		g_cUIRefineWindow->HT_vRefineWindow_WindowHide();
		HT_vNPCControl_ButtonCheck_Work_Delete();		
	}
	// NPC인벤토리 닫기
	if(g_cUIManager->HT_isShowWindow( _DIALOG_GOODSKEEPWND ) == HT_TRUE )
	{
		// 아이템 언패킹창 닫기
		g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );
	}
	// 쿠폰 등록 중일 경우
	if( m_iResent == NPC_RESENT_REGIST_LOTTERY ) 
	{
		// 쿠폰 입력 창 닫기
	}
	// 헌납 중일 경우
	if( g_cUIManager->HT_isShowWindow(_DIALOG_CHARITYWND1) || g_cUIManager->HT_isShowWindow(_DIALOG_CHARITYWND2) )
	{
		// 헌납창 위에 있던 아이템 이미지들 지우기
		HT_vNPCControl_Offering_Cancel();
	}
	//	아휘람 창고 관련
	if( g_cUIManager->HT_isShowWindow( _DIALOG_ASHRAMCAGO ) || g_cUIManager->HT_isShowWindow( _DIALOG_SANCTIONASHCAGO ) || g_cUIManager->HT_isShowWindow( _DIALOG_SETLEVELASHCAGO ) )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_ASHRAMCAGO );
		g_cUIManager->HT_HideWindow( _DIALOG_SANCTIONASHCAGO );
		g_cUIManager->HT_HideWindow( _DIALOG_SETLEVELASHCAGO );
	}

	m_bNPCActive = HT_FALSE;
	m_iNPCIndex = 0;

	m_iEconomy_Resent_Item = eEconomy_Item_None;	// 현재 선택된 아이템 분류
	m_iResent = NPC_RESENT_NONE;
	m_byMessageWin = NPC_MESSAGE_NONE;
	m_byResent_ServerMsg = SERVER_MSG_NONE;
	m_bNextStepByClientEvent = HT_FALSE;

	// 메세지창 관련 입력 받았을때 현재 활성화된 NPC를 검사하기 때문에...
	g_sNPCSystem->HT_vNPCSystem_AntiActiveNPC();
	g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_NONE);
}

//----- 리스트상자 닫기 -----//
HTvoid CHTNPCControl::HT_vNPCControl_ListAntiActive()
{
	// 아이템 정보창 닫기
	g_cUIManager->HT_HideWindow( _DIALOG_MERCHANT );
}

// 완료메세지 창
HTRESULT CHTNPCControl::HT_hrNPCControl_Complete_Message( HTint iProp, HTint iInductNo )
{
	if( m_byMessageWin == NPC_MESSAGE_NONE)
		return HT_FAIL;

	// 프로퍼티를 선택
//	switch(iProp)
//	{
//		case _PROP_PUSHBTN_IN_DLG:	// 확인
//		{
			m_byMessageWin = NPC_MESSAGE_NONE;

			// 제작가능한 아이템 리스트 요구 결과가 에러일 경우
			if(m_iResent == NPC_RESENT_DIALOG)
			{	
				// 대화상자 대화 바꾸기
				// 선택문의 마지막에는 선택문이 아닌 다른 입력에 의해 다음 단계로 넘어갈 때 사용하기 위한 값이 있다
				// 0~m_nSelectCount-1 : 선택문, m_nSelectCount : 확인, m_nSelectCount+1 : 취소
				// 마우스 클릭에 따라서 다음 단계로 넘어간다.
				HT_vNPCControl_GetNextStep(m_nSelectCount+1);
			}
			// 아이템 구입
			else if( m_iResent == NPC_RESENT_ITEM_LIST )
			{
				// 아이템 구입 개수 에러 || 판매 결과 에러일 경우 리스트 창 안없앤다. 
				if( iInductNo != CONFIRM_NPCCONTROL_ITEM_COUNT && iInductNo != CONFIRM_NPCCONTROL_DISJOINT )
				{
					HT_vNPCControl_ListAntiActive();	// 리스트 창 안보이게..
				
					// 대화상자 대화 바꾸기
					// 선택문의 마지막에는 선택문이 아닌 다른 입력에 의해 다음 단계로 넘어갈 때 사용하기 위한 값이 있다
					// 0~m_nSelectCount-1 : 선택문, m_nSelectCount : 확인, m_nSelectCount+1 : 취소
					// 마우스 클릭에 따라서 다음 단계로 넘어간다.
					HT_vNPCControl_GetNextStep(m_nSelectCount+1);
				}
				m_byResent_ServerMsg = SERVER_MSG_NONE;
			}
			// 아이템 제련
			else if(m_iResent == NPC_RESENT_REFINE)
			{
				if( m_bMessage_Error == HT_FALSE )	// 성공일 경우
				{
					//-----제조 이미지와 리소스 지우기-----//
					HT_vNPCControl_ButtonCheck_Work_Delete();
					m_iResent = NPC_RESENT_NONE;
				}
				else
				{
					// 제련결과 아이템 사라짐
					if( m_byResent_ServerMsg == SERVER_MSG_RESP_WORK_ITEM_REMOVE )
						g_cItemSystem->HT_vItemSystem_DeleteItem(m_dwWorkItem);
					// 제련결과 강화제련 레벨 초기화
					else if( m_byResent_ServerMsg == SERVER_MSG_RESP_WORK_ITEM_MAIN_INIT )
						g_cItemSystem->HT_bItemSystem_SetMainRefineLevel( m_dwWorkItem, 0 );
					// 주술 제련 초기화
					else if( m_byResent_ServerMsg == SERVER_MSG_RESP_WORK_ITEM_SUB_INIT )
						g_cItemSystem->HT_bItemSystem_ClearSubRefineItem( m_dwWorkItem );

					// 클라이언트에서 검사한 에러의 경우 재료 이미지만 지우고, 그렇지않으면 아이템 이미지/정보도 지우기
					if( m_byResent_ServerMsg == SERVER_MSG_NONE )	
						HT_vNPCControl_ButtonCheck_Work_TotalCancel();
					else
					{
						HT_vNPCControl_ButtonCheck_Work_Delete();
						m_iResent = NPC_RESENT_NONE;
					}
				}
				m_byResent_ServerMsg = SERVER_MSG_NONE;
			}
			// 수리/해체
			else if( m_iResent == NPC_RESENT_FIX || m_iResent == NPC_RESENT_DISJOINT)
			{
				// 대화상자 대화 바꾸기
				// 선택문의 마지막에는 선택문이 아닌 다른 입력에 의해 다음 단계로 넘어갈 때 사용하기 위한 값이 있다
				// 0~m_nSelectCount-1 : 선택문, m_nSelectCount : 확인, m_nSelectCount+1 : 취소
				// 마우스 클릭에 따라서 다음 단계로 넘어간다.
				HT_vNPCControl_GetNextStep(m_nSelectCount);
				
				// 수리 실패 후 마우스 모양을 바꾸기 위해서
				m_iResent = NPC_RESENT_DIALOG;
			}
			else if( m_iResent == NPC_RESENT_TRIMURITI_CHANGE ) // 주신 변경-에러있는 경우
				HT_vNPCControl_GetNextStep( m_nSelectCount );
			else if( m_iResent == NPC_RESENT_TRIMURITI_POINT )// 주신 포인트 확장-에러있을 경우
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 
			else if( m_iResent == NPC_RESENT_REGIST_LOTTERY ) 
			{
				if( iInductNo == CONFIRM_NPCCONTROL_COUPON_ERR ) // 쿠폰 등록 오류
					HT_vNPCControl_GetNextStep( m_nSelectCount );
				else // 쿠폰 번호 오류
				{
					m_szLottoryNum.HT_hrCleanUp(); // 쿠폰 입력창 초기화
				}
			}
//			else
//				m_iResent = NPC_RESENT_DIALOG;
//		}
			return HT_OK;

//		default:
//			break;
//	}	// end of switch(iProp)

//	return HT_FAIL;
}

// 테스크 퀘스트 상의 퀴즈 답. 0 : 오답, 1 : 정답
HTint g_iTaskQuest_QuizResult[]
= { 0, 1, 0,	0, 1, 0,	0, 0, 1,	1, 0, 0,	0, 0, 1, // 1, 2, 3, 4, 5 
	1, 0, 0,	0, 1, 0,	0, 1, 0,	0, 0, 1,	0, 1, 0, // 6, 7, 8, 9, 10
	0, 1, 0,	0, 1, 0,	0, 1, 0,	0, 0, 1,	1, 0, 0, // 11, 12, 13, 14, 15
	0, 1, 0,	0, 0, 1,	0, 1, 0,	1, 0, 0,	1, 0, 0  // 16, 17, 18, 19, 20
};
//-----대화상자 체크-----//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_Dialog(HTPoint pPt)
{
	// 프로퍼티를 선택
	//HTint iProp = g_cUINPCWindow->HT_vGetNPCWindow_iProp();
	HTint nSelectedRadioNo = -1;
	nSelectedRadioNo = g_cUINPCWindow->HT_vGetNPCWindow_ButtonNo() - 1;

	BYTE byQuestLevel = g_sNPCSystem->HT_byNPCSystem_GetLastQuestLevel();
	BYTE byQuestIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();
	
	switch(1)
	{
	case 1:
		switch(1)
		{
		case 1:
	if( nSelectedRadioNo < 0 )
		return;

	HTshort event = g_pEngineHandler->HT_sGetClientEvent();
	//--------------------------------------------------------------------------------//
	// 퀘스트 단계 변경 처리 - 다음 대화내용을 찾는 조건에 영향을 준다.
	//--------------------------------------------------------------------------------//
	if( byQuestLevel == QUEST_STATUS_START)
	{
		// 튜토리얼 퀘스트를 거부했을 경우 대화상자의 마지막 선택문에 "퀘스트 시작"선택문이 있다
		// 만다라마을의 승려에서 부터 튜토리얼 퀘스트가 시작한다.
		if( byQuestIndex == 0 )	// 튜토리얼 거부 상태
		{
			// 대화를 처음 시작할때만 event가 "대화모드"이고 다른 경우엔 "NULL"			
			if( event == eNpcCEventDialog && nSelectedRadioNo == (m_nSelectCount-1) )
			{
				g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(0x01, SELECT_QUEST_OK);	// 승낙
				g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(1, QUEST_STATUS_NONE, QUEST_STATUS_0); // 퀘스트 없음
			}
		} 
		else if( event == eNpcCEventQuestAllow ) // 퀘스트승낙모드
		{
			// 항상 0번 선택문이 승낙, 1번 선택문이 거부
			if( byQuestIndex <= TUTORIAL_QUEST_END )	// 튜토리얼의 경우 무조건 퀘스트를 받기 때문에 퀘스트 진행상태를 "진행"으로 바꾼다
				g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_PROGRESS );	
			else if( byQuestIndex <= SCENARIO_QUEST_6_END )
			{ 
				if( nSelectedRadioNo == SELECT_QUEST_OK )
				{
					if( byQuestIndex == QUEST_SHAMBALA_11 ) // 2차 전직 직업 선택
						g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG( byQuestIndex, m_bySelectPart);
					else
						g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG( byQuestIndex, SELECT_QUEST_OK);	// 승낙
					// 길 잃은 아이 퀘스트일 경우
					if( byQuestIndex == QUEST_MANDARA_7 )	
					{
						// 아바타라의 무덤의 아이 NPC 삭제
						HTbool bRes = HT_FALSE;
						bRes = g_sNPCSystem->HT_bNPCSystem_DeleteNPC( m_iNPCIndex ); 
						if( bRes == HT_FALSE ) // 18 zone
							bRes = g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1215 ); 
						if( bRes == HT_FALSE ) // 19 zone
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1245 );
					}	
					//	대화상자 닫기 - NPC와 관련된 모든 창 닫힘
					HT_vNPCControl_DialogWin_AntiActive();
				}
				else
				{
					// 시나리오 퀘스트 일 경우 거절을 전송한다. 
					// 예외 : 2차 전직 퀘스트, 독립 퀘스트 ( 현재(2004.03.17) 차크라/스킬 초기화 퀘스트 ) 
					if( byQuestIndex >= SCENARIO_QUEST_1_START 
						&& byQuestIndex <= SCENARIO_QUEST_6_END && byQuestIndex != QUEST_SHAMBALA_11 )
					{
						g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(byQuestIndex, SELECT_QUEST_CANCEL);		// 거절
						g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_REJECTION); // 퀘스트 거부
					}
				}
			}
			// 독립 퀘스트(현재(2004.03.17 차크라/스킬 초기화퀘스트)일 경우 
			else
			{
				if( nSelectedRadioNo == SELECT_QUEST_OK ) // 승낙을 눌렀을 경우 퀘스트 없음으로 전환. 
					g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus( byQuestIndex, QUEST_STATUS_NONE, QUEST_STATUS_0 ); // 퀘스트 없음
			}
		} // end of else if( event == eNpcCEventQuestAllow ) // 퀘스트승낙모드
		// 시나리오 퀘스트 승낙모드가 나오기 전에 퀘스트 대화를 다 끝내지 않았을 경우(대화마침을 눌렀을 경우)
		else if( byQuestIndex >= SCENARIO_QUEST_1_START && byQuestIndex <= SCENARIO_QUEST_6_END 
					&& nSelectedRadioNo == (m_nSelectCount-1) && nSelectedRadioNo != 0 )
		{
			if( byQuestIndex == QUEST_MANDARA_4 )
			{	// 4번째 시나리오 퀘스트의 경우엔 밤일 때만 퀘스트 승낙모드가 있다.
				HTfloat fCurTime = HT_fNPCControl_GetCurTime();
				if(0.5 <= fCurTime && fCurTime <= 1)	// 밤
				{
					g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(byQuestIndex, SELECT_QUEST_CANCEL);		// 거절
					g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_REJECTION); // 퀘스트 거부
				}
			}
			else
			{
				if( byQuestIndex != QUEST_SHAMBALA_11 ) // 예외 - 2차 전직
				{
					g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(byQuestIndex, SELECT_QUEST_CANCEL);		// 거절
					g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_REJECTION); // 퀘스트 거부
				}
			}
		}
	} // end of if( byQuestLevel == QUEST_STATUS_START)
	// 퀘스트를 완료/실패 했을 경우엔 퀘스트 진행상태를 "없음"으로 바꾼다
	else if( byQuestLevel == QUEST_STATUS_SUCCESS || byQuestLevel == QUEST_STATUS_FAIL )
	{
		// 시나리오 퀘스트
		if( byQuestIndex >= SCENARIO_QUEST_1_START )
		{
			if( event == eNpcCEventQuestOK ) // 완료대화종료
			{
				BYTE byQuestLevelTime = g_sNPCSystem->HT_byNPCSystem_GetLastQuestLevelTime();
				// 2차 전직-지혜 퀘스트의 퀴즈 결과일 경우
				if( byQuestIndex == QUEST_SHAMBALA_14 && byQuestLevelTime == QUEST_STATUS_1 
														&& m_bMessage_Error == HT_FALSE ) // 모두 맞음
					HT_vNPCControl_DialogWin_AntiActive();	 //	대화상자 닫기 - NPC와 관련된 모든 창 닫힘
				else
					g_sNPCSystem->HT_vNPCSystem_SetNextQuestStatus();
			}
		}
		// 튜토리얼 퀘스트 - 예외 : Tutorial 4(바난타에서 완료대화가 2단계로 되어있다 )
		else if( ( byQuestIndex <= TUTORIAL_QUEST_END && byQuestIndex != QUEST_TUTORIAL_4 ) 
						|| ( byQuestIndex == QUEST_TUTORIAL_4 && event == eNpcCEventQuestOK ) ) // 완료대화종료
			g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus( byQuestIndex, QUEST_STATUS_NONE, QUEST_STATUS_0 ); // 퀘스트 없음

		// 2차 완료후 다음 퀘스트 시작전까지의 대화(QUEST_STATUS_3)는 승낙모드와 관계없다
	}
	// 시나리오 퀘스트를 거부했다가 다시 퀘스트를 받고자 할 때
	else if( byQuestLevel == QUEST_STATUS_REJECTION )
	{
		// 대화상자의 마지막 선택문에 퀘스트를 다시 받을 수있는 선택문이 있다
		if( event == eNpcCEventDialog && nSelectedRadioNo == (m_nSelectCount-1) )
			g_sNPCSystem->HT_vNPCSystem_SetNextQuestStatus();
	} 
	//--------------------------------------------------------------------------------//
	// 버튼 선택에 따른 대화 변경 처리
	//--------------------------------------------------------------------------------//
	// 스킬 습득 단계일 경우 스킬 리스트 마지막에 스크립트에 의한 선택구문이 있다.
	// 선택문의 마지막에는 선택문이 아닌 다른 입력에 의해 다음 단계로 넘어갈때 사용할 값이 있다.
	if( (m_iResent == NPC_RESENT_SKILL_LIST || m_iResent == NPC_RESENT_SKILL_REMOVE) 
							&& (m_nSkillList_Count > 0) && nSelectedRadioNo < m_nSkillList_Count)
	{ 
		// 선택한 스킬 정보
		// 목록 앞쪽에는 기술 이외의 선택문이 있다
		m_dwSkillRegistIndex = m_nSkillList_Index[nSelectedRadioNo];
		m_dwSkillRegistType = m_nSkillList_Type[nSelectedRadioNo];

		m_iResent = NPC_RESENT_SKILL_SELECT;

		// 마우스 클릭에 따라서 다음 단계로 넘어간다.
		HT_vNPCControl_GetNextStep(m_nSelectCount);
	}
	else if( m_iResent == NPC_RESENT_TRIMURITI )			// 주신 선택
	{
		m_bySelectPart = nSelectedRadioNo;
		//m_bTrimutiri = 1;
		//HT_vNetWork_CSP_Req_Select_Trimuriti(m_bTrimutiri);

		// 마우스 클릭에 따라서 다음 단계로 넘어간다.
		HT_vNPCControl_GetNextStep( nSelectedRadioNo );
		// 주신선택모드가 지나갔음을 구분하기 위해
		m_iResent = NPC_RESENT_TRIMURITI_SELECT;	
	}
	else if( m_iResent == NPC_RESENT_TRIMURITI_CHANGE )	// 주신 변경
	{
		HTbool res = HT_TRUE;

		if (m_bySelectPart == 0)
		{
		// 주신 변경을 위한 조건 검사. 마지막 항목(m_nSelectCount-1) 은 주신 선택이 아니다.
		if( nSelectedRadioNo != m_nSelectCount-1 && g_cUINPCWindow->m_MessageBoxNo != 1)
		{

			// 현재 주신을 제외한 나머지 주신만 선택문에 나오기 때문에
			// 0:브라흐마, 1:비슈누, 2:시바 로 변환한다.

			switch( g_oMainCharacterInfo.byTrimuriti )
			{
				case TRIMURITI_BRAHMA:
					m_bySelectPart = nSelectedRadioNo+1;
					break;
				case TRIMURITI_VISHNU: 
					if( nSelectedRadioNo >= 1 )
						m_bySelectPart = nSelectedRadioNo+1;
					else
						m_bySelectPart = 0;
					break;
				case TRIMURITI_SIVA: 
					m_bySelectPart = nSelectedRadioNo;
					break;
				default: return;
			}

			res = HT_bNPCControl_CheckConditionTrimuritiChange();

		}
		}
		// 마우스 클릭에 따라서 다음 단계로 넘어간다.
		// 에러가 있었을 경우 확인 메세지창을 처리하고 다음단계로 넘어간다.
	

		if( res == HT_TRUE )
			HT_vNPCControl_GetNextStep( nSelectedRadioNo );
	}
	// 2차 직업 선택 모드
	else if( m_iResent == NPC_RESENT_JOB2_SELECT )
	{
		if( nSelectedRadioNo == SELECT_QUEST_OK )			// 사트야, 드루타, 나카유다, 아비카라
			m_bySelectPart = 0;
		else if( nSelectedRadioNo == SELECT_QUEST_CANCEL )	// 바나르, 카르야, 바이드야, 사마바트
			m_bySelectPart = 1;
		HT_vNPCControl_GetNextStep( nSelectedRadioNo );
	}
	// 테스크 퀘스트 모드
	else if( m_iResent == NPC_RESENT_TASK_QUEST )
	{
		// m_iTaskQuestID 는 현재 테스크 분류의 첫번째 퀘스트 아이디로 설정되어있다.
		m_iTaskQuestID += nSelectedRadioNo; // 퀘스트 아이디 설정
		HT_vNPCControl_GetNextStep( nSelectedRadioNo );
	}
	// 테스크 퀘스트 - 퀴즈 모드
	else if( m_iResent == NPC_RESENT_QUIZ )
	{
		// 현재 퀴즈의 답을 알아본다. 0:오답, 1:정답
		if( g_iTaskQuest_QuizResult[ m_iQuestQuizCount*HT_QUIZ_SELECT_NUM + nSelectedRadioNo ] ) 
			m_bMessage_Error = HT_FALSE; // 에러 없음
		else
			m_bMessage_Error = HT_TRUE;	// 에러 있음
		++m_iQuestQuizCount; // 퀴즈 번호
		HT_vNPCControl_GetNextStep( nSelectedRadioNo );
	}
	else if (m_iResent == NPC_RESENT_FIX && m_bMessage_Error == HT_TRUE)
	{
		m_bMessage_Error = HT_FALSE;
	}
	else // 그외 - 스킬리스트가 선택문에 있을 수 있기 때문에
		HT_vNPCControl_GetNextStep(nSelectedRadioNo-m_nSkillList_Count);
	}
	break;

	if (nSelectedRadioNo == -1)	// 취소 버튼이라면
	{	
			// 시나리오 퀘스트 승낙모드가 나오기 전에 퀘스트 대화를 다 끝내지 않았을 경우
			// 승낙을 위한 선택문이 없는 경우(m_nSelectCount가 1이하일 때)는 제외
			if( byQuestIndex >= SCENARIO_QUEST_1_START && byQuestLevel == QUEST_STATUS_START && m_nSelectCount > 1 )
			{
				if( byQuestIndex == QUEST_MANDARA_4 )
				{	// 4번째 시나리오 퀘스트의 경우엔 밤일 때만 퀘스트 승낙모드가 있다.
					HTfloat fCurTime = HT_fNPCControl_GetCurTime();
					if(0.5 <= fCurTime && fCurTime <= 1)	// 밤
					{
						g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(byQuestIndex, SELECT_QUEST_CANCEL);		// 거절
						g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_REJECTION); // 퀘스트 거부
					}
				}
				else
				{
					if( byQuestIndex != QUEST_SHAMBALA_11 ) // 예외 - 2차 전직
					{
						g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(byQuestIndex, SELECT_QUEST_CANCEL);		// 거절
						g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_REJECTION); // 퀘스트 거부
					}
				}
			}
			// 대화상자 닫기 - NPC와 관련된 모든 창 닫기
			//g_cNPCControl->m_bPrimium_Button = HT_FALSE;
			HT_vNPCControl_DialogWin_AntiActive();

		}
			break;
	}
}

// 주신변경 비용 검사 함수
HTfloat CHTNPCControl::HT_bNPCControl_CheckTrimuritiChangeCost()
{
	m_nLevel = g_cStatus->HT_byGetLevel();		// 레벨 얻기
/*
	BYTE					m_snBrahmaCount;	// 브라흐마 
	BYTE					m_snVishnuCount;	// 비슈느
	BYTE					m_snSivaCount;		// 시바
	HTbool					m_bTrimutiri;		// 주신 선택인지 조회인지 구분
*/

	BYTE byFromTri = g_oMainCharacterInfo.byTrimuriti;
	
	BYTE byToTri;
	switch (m_bySelectPart)
	{
		case 0:	byToTri = TRIMURITI_BRAHMA;	break;
		case 1:	byToTri = TRIMURITI_VISHNU;	break;
		case 2:	byToTri = TRIMURITI_SIVA;	break;
		default: return 0;
	}

	HTint snFrom = 0, snTo = 0;

	if(byFromTri == eTNClan_Brahma) snFrom = m_snBrahmaCount;
	else if(byFromTri == eTNClan_Vishnu) snFrom = m_snVishnuCount;
	else if(byFromTri == eTNClan_Siva) snFrom = m_snSivaCount;
	else snFrom = 0;

	if(byToTri == eTNClan_Brahma) snTo = m_snBrahmaCount;
	else if(byToTri == eTNClan_Vishnu) snTo = m_snVishnuCount;
	else if(byToTri == eTNClan_Siva) snTo = m_snSivaCount;
	else snTo = 0;																	
	
	float fRatio = 0;
	if(snFrom <= 0) fRatio = 1;
	else fRatio = (float)snTo/snFrom;

	if(snTo <= 0) fRatio = 1;
	fRatio = (float) pow((double)fRatio, 1.2);

	float fPrice = 10*(float)pow((double)m_nLevel, 3.25 )+990;
	fPrice = (float) (fPrice*fRatio*0.3);

	//HTfloat fPrice = 10*(HTfloat)pow(m_nLevel, 3.25 )+990;

	return fPrice;
}


// 주신 변경이 가능한지 조건 검사
HTbool CHTNPCControl::HT_bNPCControl_CheckConditionTrimuritiChange( )
{
	HTbyte byLevel = g_cStatus->HT_byGetLevel();
	HTint iPCMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
	// 고대 주술서가 있는지 검사
	HTint iItemCount = 0;
	if( byLevel >= HT_TRUMURITI_CHANGE_DIVISION_LEVEL )	// 30레벨 이상일때만 필요함
		iItemCount = g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_TRIMURITI_CHANGE_ITEM );

	// 비용 검사
	HTfloat fPrice = HT_bNPCControl_CheckTrimuritiChangeCost();
	
	// 헌납 재료가 부족한 경우
	if( ( byLevel < HT_TRUMURITI_CHANGE_DIVISION_LEVEL && iPCMoney < (HTint) fPrice ) 
			|| ( byLevel >= HT_TRUMURITI_CHANGE_DIVISION_LEVEL 
					&& ( iPCMoney < (HTint) fPrice || iItemCount < HT_TRIMURITI_CHANGE_ITEMNUM ) ) )
	{
		if( byLevel < HT_TRUMURITI_CHANGE_DIVISION_LEVEL )
			HT_vNPCControl_SetMessage( eMsgTrimuritiChangeCondition1 );
			//m_szMessage.HT_szFormat("주신을 변경하기 위해서는 %d루피아가 필요합니다. 인벤토리에서 루피아를 확인해 보세요.", 
			//						HT_TRIMURITI_CHANGE_MONEY1);
		else
			HT_vNPCControl_SetMessage( eMsgTrimuritiChangeCondition2 );
			//m_szMessage.HT_szFormat("주신을 변경하기 위해서는 %d루피아와 고대 주술서가 필요합니다. 인벤토리를 확인해 보세요.", 
			//						HT_TRIMURITI_CHANGE_MONEY2);
		m_bMessage_Error = HT_TRUE;	// 에러 있음

		// 완료창 띄움
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUINPCWindow->m_MessageBoxNo = -3;
		g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 0);
		HT_vNPCControl_GetNextStep(m_nSelectCount+1);
		return HT_FALSE;
	}
	// 아쉬람에 가입되어 있을 경우
	if( g_cGuildSystem->HT_strGuild_GetGuildName().HT_nGetSize() > 0 )
	{
		//m_szMessage.HT_szFormat("아쉬람에 가입되어 있는 상태에서는 주신을 변경할 수 없습니다." );
		HT_vNPCControl_SetMessage( eMsgTrimuritiChangeCondition3 );
		m_bMessage_Error = HT_TRUE;	// 에러 있음

		// 완료창 띄움
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUINPCWindow->m_MessageBoxNo = -2;
		g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 0);
		return HT_FALSE;
	}
	return HT_TRUE;
}

// 주신 포인트 확장이 가능한지 조건 검사
HTbool CHTNPCControl::HT_bNPCControl_CheckConditionBrahmanPointRising()
{
	HTint iPCMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
	// 고대 주술서가 있는지 검사
	HTint iItemCount = g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_BRAHMANPOINT_RISING_ITEM );

	// 영혼의 구슬(7116) 10개와 50,000루피아 있는지 검사
	if( iItemCount < HT_BRAHMANPOINT_RISING_ITEMNUM || iPCMoney < HT_BRAHMANPOINT_RISING_MONEY )
	{
		//m_szMessage.HT_szFormat("주신 포인트를 얻기 위해서는 영혼의 구슬 %d개와 제사 비용 %d루피아가 필요합니다. 인벤토리를 확인해 주세요."
		//							, HT_BRAHMANPOINT_RISING_ITEMNUM, HT_BRAHMANPOINT_RISING_MONEY );
		HT_vNPCControl_SetMessage( eMsgTrimuritiPointCondition1 );
		m_bMessage_Error = HT_TRUE;	// 에러 있음

		// 완료창 띄움
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUINPCWindow->m_MessageBoxNo = -1;
		g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 0);
		return HT_FALSE;
	}
	// 주신포인트가 100 미만인지 검사
	if( g_oMainCharacterInfo.nBrahmanPoint >= HT_BRAHMANPOINT_RISING_BRAHMAN )
	{
		//m_szMessage.HT_szFormat("헌납을 통한 주신 포인트가 %d미만인 경우에만 가능합니다.", HT_BRAHMANPOINT_RISING_BRAHMAN );
		HT_vNPCControl_SetMessage( eMsgTrimuritiPointCondition2 );
		m_bMessage_Error = HT_TRUE;	// 에러 있음

		// 완료창 띄움
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUINPCWindow->m_MessageBoxNo = -1;
		g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 0);
		return HT_FALSE;
	}

	m_bMessage_Error = HT_FALSE;	// 에러 없음
	return HT_TRUE;
}

#define HT_CHAKRA_INIT_CONDITION_BRAMANPOINT	500
#define HT_CHAKRA_INIT_CONDITION_MONEY			50000
// 차크라 초기화 조건 검사
HTbool CHTNPCControl::HT_bNPCControl_CheckConditionChakraInit()
{
	if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < HT_CHAKRA_INIT_CONDITION_MONEY 
		|| g_oMainCharacterInfo.nBrahmanPoint < HT_CHAKRA_INIT_CONDITION_BRAMANPOINT )
		return HT_FALSE;
	else
		return HT_TRUE;
}

#define HT_SKILL_INIT_CONDITION_BRAMANPOINT	1000
#define HT_SKILL_INIT_CONDITION_MONEY		100000
// 스킬 초기화 조건 검사
HTbool CHTNPCControl::HT_bNPCControl_CheckConditionSkillInit()
{
	if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < HT_SKILL_INIT_CONDITION_MONEY 
		|| g_oMainCharacterInfo.nBrahmanPoint < HT_SKILL_INIT_CONDITION_BRAMANPOINT )
		return HT_FALSE;
	else
		return HT_TRUE;
}

// 쿠폰 등록 조건 검사
HTbool CHTNPCControl::HT_bNPCControl_CheckConditionCoupon()
{
	// 상위 4비트의 2비트는(10레벨/20레벨)는 권한, 하위 4비트의 2비트(10레벨/20레벨)는 수행여부.
	HTbyte byFlag = g_oMainCharacterInfo.snDummy >> 4 ;
	HTbyte byUse = g_oMainCharacterInfo.snDummy & 0x0F;
	if( (byFlag & 0x02) && !(byUse & 0x02) ) // 10레벨의 쿠폰을 사용안했으면 
		return HT_TRUE;
	else if( (byFlag & 0x01) && !(byUse & 0x01) ) // 20레벨의 쿠폰을 사용안했으면
		return HT_TRUE;
	else 
		return HT_FALSE;
}

char g_szEventMsg[6][500] = 
{ 
	"안녕하세요. %s님.",
	"만다라 마을의 역마꾼 라훌을 찾아가 보세요. 좋은 소식이 기다리고 있답니다. 마라토벌단의 입단을 고무하는 행사가  있다고 하는군요.",
	"행사제목: 입영 통지서.",
	"행사기간: 4월 20일 부터 5월 4일 까지.",
	"제한사항: 1계정당 10레벨,20레벨 2회 가능.",
	"홈페이지 참조: www.tantra-online.co.kr"
};

// 쿠폰 등록에 관한 메세지창 띄우기
HTvoid CHTNPCControl::HT_vNPCControl_SetCouponNotifyMessage( HTbyte byLevel )
{
	HTbyte byCoupon = g_oMainCharacterInfo.snDummy >> 4;
	HTbyte byFlag = 0;

	if( byLevel == 20 )
	{
		byFlag = byCoupon & 0x01;
	}
	else if( byLevel == 10 )
	{
		byFlag = byCoupon & 0x02;
	}
	else
		return;

	if( byFlag == 0 ) // 쿠폰 생성 메세지창 띄우기
	{
		//	공지창 켬
		CHTString szMsg;
		HTchar strText[1000];
		ZeroMemory( strText, sizeof(HTchar)*1000 );

		szMsg.HT_szFormat( g_szEventMsg[0], g_oMainCharacterInfo.szCharName );
		sprintf( strText, "%s>> %s>>　>>　%s>>　%s>>　%s>>　>>　%s",
			szMsg.HT_szGetString(), g_szEventMsg[1], g_szEventMsg[2], g_szEventMsg[3], g_szEventMsg[4], g_szEventMsg[5] );

		// 쿠폰이 생겼음을 셋팅
		// 상위 4비트의 2비트는(10레벨/20레벨)는 권한, 하위 4비트의 2비트(10레벨/20레벨)는 수행여부.
		byFlag = 0;
		if( byLevel == 20 )
			byFlag |= 0x01;

		else //if( byLevel == 10 )
			byFlag |= 0x02;
		g_oMainCharacterInfo.snDummy |= (byFlag << 4) ;
	}
}

// 테스크 1
HTbool CHTNPCControl::HT_bNPCControl_CheckSourceForTaskQuest( HTint iTaskID )
{
	HTbyte	byteOut = 0;
	HTshort	sOut = 0, sOut1 = 0, sOut2 = 0, sOut3 = 0, sOut4 = 0;
	HTint	iOut;

	short int snNpcIndex = 0;
	// 임시 코딩 (만다라 2,3 존에서 대화를 걸었을 경우 퀘스트 진행을 위해 1번존 index로 변경)

	switch( m_iNPCIndex )
	{
		// 무기 상인
	case 1101 :	// 만다라
	case 1205 :	// 18번 만다라
	case 1235 :	// 19번 만다라
		{
			snNpcIndex = 1101;
		}
		break;

		// 방어구 상인
	case 1102 :	// 만다라
	case 1206 :	// 18번 만다라
	case 1236 :	// 19번 만다라
		{
			snNpcIndex = 1102;
		}
		break;

		// 액세서리 상인 
	case 1103 :	// 만다라
	case 1207 :	// 18번 만다라
	case 1237 :	// 19번 만다라
		{
			snNpcIndex = 1103;
		}
		break;

		// 승려
	case 1104 :	// 만다라
	case 1208 :	// 18번 만다라
	case 1238 :	// 19번 만다라
		{
			snNpcIndex = 1104;
		}
		break;

		//	물품보관지기
	case 1105 :	// 만다라
	case 1209 :	// 18번 만다라
	case 1239 :	// 19번 만다라
		{
			snNpcIndex = 1105;
		}
		break;

		// 수비대장
	case 1108 :	// 만다라 
	case 1212 : // 18번 만다라
	case 1242 :	// 19번 만다라
		{
			snNpcIndex = 1108;
		}
		break;

		// 역마꾼(게이트)
	case 1106 :	// 만다라
	case 1210 : // 18번 만다라
	case 1240 :	// 19번 만다라
		{
			snNpcIndex = 1106;
		}
		break;
		// 주술사(마법동물대여)
	case 1107 :		// 만다라
	case 1211 :		// 18번 만다라
	case 1241 :		// 19번 만다라
		{
			snNpcIndex = 1107;
		}
		break;
		// 병사1
	case 1001 :	// 만다라
	case 1201 :	// 18번 만다라
	case 1231 :	// 19번 만다라
		{
			snNpcIndex = 1001;
		}
		break;
		// 병사2
	case 1002 :	// 만다라
	case 1202 :	// 18번 만다라
	case 1232 :	// 19번 만다라
		{
			snNpcIndex = 1002;
		}
		break;
		//	남자아이1
	case 1003 :	// 만다라
	case 1203 : // 18번 만다라
	case 1233 : // 19번 만다라
		{
			snNpcIndex = 1003;
		}
		break;

		//	여자아이1
	case 1005 :	// 만다라
	case 1204 : // 18번 만다라
	case 1234 : // 19번 만다라
		{
			snNpcIndex = 1005;
		}
		break;

		// 퀘스트용 병사 NPC
	case 1115 :	// 공동 협의체
	case 1213 :	// 18번 만다라
	case 1243 : // 19번 만다라
		{
			snNpcIndex = 1115;
		}
		break;

		// 스포르바다 병사 NPC
	case 1116 :
	case 1214 : // 18번 만다라
	case 1244 : // 19번 만다라
		{
			snNpcIndex = 1116;
		}
		break;

		// 아바타라의 무덤 아이
	case 1117 :
	case 1215 : // 18번 만다라
	case 1245 : // 19번 만다라
		{
			snNpcIndex = 1117;
		}
		break;
	default:
		snNpcIndex = m_iNPCIndex;
		break;
	}


	HTbool bRes = HT_TRUE;

	// 널 이벤트 퀘스트 테스크의 경우에는 조건을 검사하지 않는다.
	if( iTaskID >= TASK_QUEST_68_START && iTaskID <= TASK_QUEST_74_END) return HT_TRUE;

	if( g_pParamMgr->HT_bLockID( iTaskID ) == true )
	{
		// NPCID
		g_pParamMgr->HT_bGetTaskNPCID( &sOut, &sOut1, &sOut2, &sOut3, &sOut4 );
		if( sOut == snNpcIndex || sOut1 == snNpcIndex || sOut2 == snNpcIndex 
								|| sOut3 == snNpcIndex || sOut4 == snNpcIndex )
			bRes = HT_TRUE;
		else
			bRes = HT_FALSE;
		// Source1
		g_pParamMgr->HT_bGetTaskSource1( &byteOut, &sOut, &iOut );
		if( byteOut > eTaskQuestTypeNone )
			bRes &= HT_bNPCControl_CheckSourceForTaskQuest( byteOut, sOut, iOut );
		// Source2
		g_pParamMgr->HT_bGetTaskSource2( &byteOut, &sOut, &iOut );
		if( byteOut > eTaskQuestTypeNone )
			bRes &= HT_bNPCControl_CheckSourceForTaskQuest( byteOut, sOut, iOut );
		// Source3
		g_pParamMgr->HT_bGetTaskSource3( &byteOut, &sOut, &iOut );
		if( byteOut > eTaskQuestTypeNone )
			bRes &= HT_bNPCControl_CheckSourceForTaskQuest( byteOut, sOut, iOut );
		// Source4
		g_pParamMgr->HT_bGetTaskSource4( &byteOut, &sOut, &iOut );
		if( byteOut > eTaskQuestTypeNone )
			bRes &= HT_bNPCControl_CheckSourceForTaskQuest( byteOut, sOut, iOut );
		// Source5
		g_pParamMgr->HT_bGetTaskSource5( &byteOut, &sOut, &iOut );
		if( byteOut > eTaskQuestTypeNone )
			bRes &= HT_bNPCControl_CheckSourceForTaskQuest( byteOut, sOut, iOut );
		// Source6
		g_pParamMgr->HT_bGetTaskSource6( &byteOut, &sOut, &iOut );
		if( byteOut > eTaskQuestTypeNone )
			bRes &= HT_bNPCControl_CheckSourceForTaskQuest( byteOut, sOut, iOut );

		g_pParamMgr->HT_bUnLockID( iTaskID );
	}
	else
		return HT_FALSE;

	return bRes;
}

HTbool CHTNPCControl::HT_bNPCControl_CheckSourceForTaskQuest( HTbyte byType, HTshort sItemID, HTint iSourceCount )
{
	HTbool bRes = HT_TRUE;

	switch( byType )
	{
		case eTaskQuestTypeItem : // 아이템
		{
			HTint iCount = g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( sItemID );
			if( iCount >= iSourceCount )
				bRes = HT_TRUE;
			else
				bRes = HT_FALSE;
		}
			break;
		case eTaskQuestTypeRupiah : // 루피아
		{
			HTint iRupiah = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
			if( iRupiah >= iSourceCount )
				bRes = HT_TRUE;
			else
				bRes = HT_FALSE;
		}
			break;
		default : 
			bRes = HT_FALSE; 
			break;
	}

	return bRes;
}

// 2차 전직용 아이템 검사
#define HT_CHANGE_JOG2_ITEM_SATYA		8055 // 사트야
#define HT_CHANGE_JOG2_ITEM_VANARE		8056 // 바나르
#define HT_CHANGE_JOG2_ITEM_DRUTA		8057 // 드루타
#define HT_CHANGE_JOG2_ITEM_KARYA		8058 // 카르야
#define HT_CHANGE_JOG2_ITEM_NAKAYUDA	8059 // 나카유다
#define HT_CHANGE_JOG2_ITEM_VAIDYA		8060 // 바이드야
#define HT_CHANGE_JOG2_ITEM_ABICARA		8061 // 아비카라
#define HT_CHANGE_JOG2_ITEM_SAMAVAT		8062 // 사마바트
HTint CHTNPCControl::HT_iNPCControl_CheckItemForChangeJob2()
{
	HTint iSelNum = -1;
	switch( g_oMainCharacterInfo.snTribe )
	{
		case HT_ID_CHARACTER_NAGA		: // 나가
		case HT_ID_CHARACTER_KIMNARA	: // 킨나라
		{
			// 사트야
			if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_SATYA ) )
				iSelNum = 0;
			// 바나르
			else if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_VANARE ) )
				iSelNum = 1;
			else
				iSelNum = 8;
		}
			break;
		case HT_ID_CHARACTER_ASURA		: // 아수라
		case HT_ID_CHARACTER_RAKSHASA	: // 라크샤사
		{
			// 드루타
			if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_DRUTA ) )
				iSelNum = 2;
			// 카르야
			else if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_KARYA ) )
				iSelNum = 3;
			else
				iSelNum = 8;
		}
			break;
		case HT_ID_CHARACTER_YAKSA		: // 야크샤
		case HT_ID_CHARACTER_GANDHARVA	: // 간다르바
		{
			// 나카유다
			if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_NAKAYUDA ) )
				iSelNum = 4;
			// 바이드야
			else if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_VAIDYA ) )
				iSelNum = 5;
			else
				iSelNum = 8;
		}
			break;
		case HT_ID_CHARACTER_DEVA		: // 데바
		case HT_ID_CHARACTER_GARUDA		: // 가루다
		{
			// 아비카라
			if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_ABICARA ) )
				iSelNum = 6;
			// 사마바트
			else if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_SAMAVAT ) )
				iSelNum = 7;
			else
				iSelNum = 8;
		}
			break;
		default							: 
			iSelNum = 8; break;
	}

	return iSelNum;
}

// 아쉬람 생성했을 때 
HTvoid CHTNPCControl::HT_vNPCControl_Create_Guild( )
{
	if( m_iResent == NPC_RESENT_CREATE_GILD )
	{
		// 대화창 내용 바꾸기
		HT_vNPCControl_GetNextStep( m_nSelectCount );
	}
}

// 길드마크 생성했을 때 
HTvoid CHTNPCControl::HT_vNPCControl_Create_GuildMark( )
{
	if( m_iResent == NPC_RESENT_CREATE_GILD_MARK )
	{
		// 대화창 내용 바꾸기
		HT_vNPCControl_GetNextStep( m_nSelectCount );
	}
}

// 프리미엄 윈도우의 해당위치에 따른 아이템 인덱스 얻어오기
#define PRIMIUM_BUTTON_X1	20
#define PRIMIUM_BUTTON_X2	263
#define PRIMIUM_BUTTON_Y1	82
#define PRIMIUM_BUTTON_Y2	167
#define PRIMIUM_BUTTON_Y3	252
#define PRIMIUM_BUTTON_Y4	337
#define PRIMIUM_BUTTON_Y5	422
#define PRIMIUM_BITMAP_SIZE_X	32
#define PRIMIUM_BITMAP_SIZE_Y	32
HTdword CHTNPCControl::HT_vNPCControl_Get_Primium_List_ItemIndex(HTPoint pPt)
{
	HTint nSelectedRadioNo = 0;
	HTint posx = 0, posy = 0;
	//, poswidth, posheight;
	pPt.x -= posx; pPt.y -= posy;
	
	HTint iNo = -1, iSelectItemIndex;
	if (pPt.x >= PRIMIUM_BUTTON_X1 && pPt.x < PRIMIUM_BUTTON_X1 + PRIMIUM_BITMAP_SIZE_X) 
	{
		if (pPt.y >= PRIMIUM_BUTTON_Y1 && pPt.y < PRIMIUM_BUTTON_Y1 + PRIMIUM_BITMAP_SIZE_Y) iNo = 1;
		else if (pPt.y >= PRIMIUM_BUTTON_Y2 && pPt.y < PRIMIUM_BUTTON_Y2 + PRIMIUM_BITMAP_SIZE_Y) iNo = 3;
		else if (pPt.y >= PRIMIUM_BUTTON_Y3 && pPt.y < PRIMIUM_BUTTON_Y3 + PRIMIUM_BITMAP_SIZE_Y) iNo = 5;
		else if (pPt.y >= PRIMIUM_BUTTON_Y4 && pPt.y < PRIMIUM_BUTTON_Y4 + PRIMIUM_BITMAP_SIZE_Y) iNo = 7;
		else if (pPt.y >= PRIMIUM_BUTTON_Y5 && pPt.y < PRIMIUM_BUTTON_Y5 + PRIMIUM_BITMAP_SIZE_Y) iNo = 9;
	}
	else if (pPt.x >= PRIMIUM_BUTTON_X2 && pPt.x < PRIMIUM_BUTTON_X2 + PRIMIUM_BITMAP_SIZE_X)
	{
		if (pPt.y >= PRIMIUM_BUTTON_Y1 && pPt.y < PRIMIUM_BUTTON_Y1 + PRIMIUM_BITMAP_SIZE_Y) iNo = 2;
		else if (pPt.y >= PRIMIUM_BUTTON_Y2 && pPt.y < PRIMIUM_BUTTON_Y2 + PRIMIUM_BITMAP_SIZE_Y) iNo = 4;
		else if (pPt.y >= PRIMIUM_BUTTON_Y3 && pPt.y < PRIMIUM_BUTTON_Y3 + PRIMIUM_BITMAP_SIZE_Y) iNo = 6;
		else if (pPt.y >= PRIMIUM_BUTTON_Y4 && pPt.y < PRIMIUM_BUTTON_Y4 + PRIMIUM_BITMAP_SIZE_Y) iNo = 8;
		else if (pPt.y >= PRIMIUM_BUTTON_Y5 && pPt.y < PRIMIUM_BUTTON_Y5 + PRIMIUM_BITMAP_SIZE_Y) iNo = 10;
	}

	if (iNo == -1 || m_byResent_ServerMsg != SERVER_MSG_NONE) return HT_FALSE;// 클릭시 구입셋팅

	HTint iNum = nSelectedRadioNo;
	if (m_iMerchantNo == _DIALOG_PRIMIUM_BUY1) // _DIALOG_PRIMIUM_BUY2 일때는 +1 불필요.
		nSelectedRadioNo = nSelectedRadioNo + 1;
	if (m_iMerchantNo == _DIALOG_PRIMIUM_BUY3) // _DIALOG_PRIMIUM_BUY2 일때는 +1 불필요.
		nSelectedRadioNo = nSelectedRadioNo + 4;

	iSelectItemIndex = m_PrimiumItem[nSelectedRadioNo][iNo+m_iNowPage*10-10];
	
	if (m_PrimiumItem[nSelectedRadioNo][0] < iNo+m_iNowPage*10-10) return HT_FALSE;	// 등록되지 않은 아이템 클릭시 리턴

	return iSelectItemIndex;
}

//----아이템 구입할 개수 쓰기-----//
HTvoid CHTNPCControl::HT_vNPCControl_ItemMakeCount_SetText()
{
	CHTString str;
	//str.HT_szFormat("%d", m_iWorkItemCount);쉼표
	str = g_cUIManager->HT_strSetRestMark(m_iWorkItemCount);
}


//--------ESC키/X버튼을 눌렀을때 리스트창 닫기-----------//
HTvoid CHTNPCControl::HT_vNPCControl_ItemListClose()
{
	// 리스트 창 안보이게..
	HT_vNPCControl_ListAntiActive();
	m_dwBuyItem = 0;
	m_iWorkItemCount = 0;	// 구입할 아이템 개수 초기화
	
	// 대화상자 대화 바꾸기
	// 선택문의 마지막에는 선택문이 아닌 다른 입력에 의해 다음 단계로 넘어갈 때 사용하기 위한 값이 있다
	// 0~m_nSelectCount-1 : 선택문, m_nSelectCount : 확인, m_nSelectCount+1 : 취소
	// 마우스 클릭에 따라서 다음 단계로 넘어간다.
	HT_vNPCControl_GetNextStep(m_nSelectCount+1);
}

//-----리스트 체크_그림 지우기-----//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_List_Delete()
{
	HTint BnCount = 1;
	//if( m_iEconomy_NPC == eEconomy_Item_Sword)		// 무기
	//{
	//	BnCount = g_ItemClass[0];	// 버튼 개수
	//}
	//else if( m_iEconomy_NPC == eEconomy_Item_Armor)	// 방어구
	//{
	//	BnCount = g_ItemClass[1];
	//}
	//else if( m_iEconomy_NPC == eEconomy_Item_Bracelet )// 액세서리 상인
	//{
	//	BnCount = g_ItemClass[2];
	//}
	//else
	//	return;

	for(int index = 0; index < BnCount ; ++index)
	{
		if(m_Economy_List[index].vWinCount.size() != 0)
		{
			ECONOMY_ITEM_INFO* pTemp = m_Economy_List[index].pInfoHead;
			while( pTemp != NULL )
			{
				// 보이지 않는 아이템은 삭제
				m_Economy_List[index].pInfoHead = pTemp->pNext;
				delete pTemp;	// 아이템 삭제 
				
				pTemp = m_Economy_List[index].pInfoHead;	// 다음 아이템
			}
			m_Economy_List[index].pInfoTail = NULL;
			m_Economy_List[index].vWinCount.clear();
		}	
	} // end of for(int index = 0; index < BnCount ; ++index)

	// 리스트 창 안보이게..
	HT_vNPCControl_ListAntiActive();	
}

//--------- 현재 선택된 NPC의 아이템 리스트 비활성화 -----------//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_ItemList_AntiActive()
{
	if(m_Economy_List[m_iEconomy_Resent_Item - m_iEconomy_NPC].vWinCount.size() != 0)
	{
		ECONOMY_ITEM_INFO* pTemp = m_Economy_List[m_iEconomy_Resent_Item - m_iEconomy_NPC].pInfoHead;
		while( pTemp != NULL )
		{
			pTemp = pTemp->pNext;
		}
	}	
}

//---------아이템 리스트 창을 띄운다----------//
HTvoid CHTNPCControl::HT_vNPCControl_ItemListWin_Active()
{
	if (m_iResent == NPC_RESENT_PREMIUM_ITEM || m_iResent == NPC_RESENT_PREMIUM_ITEM2 || m_iResent == NPC_RESENT_PREMIUM_ITEM3 )
	{
		m_iEconomy_Resent_Item = eEconomy_Item_Bracelet;
		m_iMerchantNo = _DIALOG_MERCHANT_PREMIUM;

		if (m_iResent == NPC_RESENT_PREMIUM_ITEM)
			g_cUIMerchantWindow->m_iTabNo = 1;

		if (m_iResent == NPC_RESENT_PREMIUM_ITEM2)
			g_cUIMerchantWindow->m_iTabNo = 0;

		if (m_iResent == NPC_RESENT_PREMIUM_ITEM3)
			g_cUIMerchantWindow->m_iTabNo = 4;


		m_iResent = NPC_RESENT_ITEM_LIST;
		m_byEconomy_Resent_WinIndex = 0;

		g_cUIMerchantWindow->HT_vMerchantWindow_DrawTab(g_cUIMerchantWindow->m_iTabNo);
		g_cNPCControl->HT_vNPCControl_PrimiumItemListWin_Active(g_cUIMerchantWindow->m_iTabNo, g_cUIMerchantWindow->m_iScrollValue);
		g_cUIManager->HT_ShowWindow(_DIALOG_MERCHANT_PREMIUM);


//		HT_vNPCControl_PrimiumItemListWin_Active(0,0);	// 프리미엄 아이템 셋팅
		
	}
	else
	{

		m_iResent = NPC_RESENT_ITEM_LIST;
		m_byEconomy_Resent_WinIndex = 0;

		if( m_iEconomy_NPC == eEconomy_Item_Sword)		// 무기
		{
			//  현재 나타난 아이템 분류
			m_iEconomy_Resent_Item = eEconomy_Item_Sword;
			m_iMerchantNo = _DIALOG_MERCHANT;
		}
		else if( m_iEconomy_NPC == eEconomy_Item_Armor)	// 방어구
		{
			//  현재 나타난 아이템 분류
			m_iEconomy_Resent_Item = eEconomy_Item_Armor;
			m_iMerchantNo = _DIALOG_MERCHANT;
		}
		else											// 액세서리 상인, 주술사 카란
		{
			//  현재 나타난 아이템 분류
			m_iEconomy_Resent_Item = eEconomy_Item_Bracelet;
			m_iMerchantNo = _DIALOG_MERCHANT;
		}
	}

	HT_vNPCControl_PopUpInventory(_DIALOG_INVEN);	// PC 인벤토리 창 띄움
}

//---------구입할 수 있는 프리미엄 아이템 리스트 구하기-------//
#define SEPT_KIND	4001
HTvoid CHTNPCControl::HT_vNPCControl_GetPrimiumItemList()
{
	// 다음 단계 처리
	HT_vNPCControl_GetNextStep(m_nSelectCount);

	// 프리미엄 리스트 생성 (변경된 로직)
	// shop list 만들기
	//m_iNPCIndex 
	int tempNPCIndex = 0;
	for (int j = 0; j < 5; ++j)
	{
		tempNPCIndex = g_cNPCControl->HT_iGetCashNPC(j);
		if( g_pParamMgr->HT_bLockID( tempNPCIndex ) == true )
		{
			int iCount = g_pParamMgr->HT_iGetNPCSellingItemCount( );
			HTint idItem = 0, num = 0;

			for ( int i = 0; i < iCount; ++i )
				if ( g_pParamMgr->HT_bGetNPCSellingItem( i, &idItem ) )
				{	/*
					if ( idItem == SEPT_KIND ) // 특정 아이템으로 영역을 구분한다.
					{
						m_PrimiumItem[j++][0] = num;
						num = 0;
						continue;
					}
					*/
					m_PrimiumItem[j][++num] = idItem;
				}

			g_pParamMgr->HT_bUnLockID( tempNPCIndex );
		}
	}
/*
	// 프리미엄 리스트 생성
	// shop list 만들기
	//
	if( g_pParamMgr->HT_bLockID( m_iNPCIndex ) == true )
	{
		int iCount = g_pParamMgr->HT_iGetNPCSellingItemCount( );
		HTint idItem = 0, num = 0;

		for ( int i = 0, j = 0; i < iCount; ++i )
			if ( g_pParamMgr->HT_bGetNPCSellingItem( i, &idItem ) )
			{	
				if ( idItem == SEPT_KIND ) // 특정 아이템으로 영역을 구분한다.
				{
					m_PrimiumItem[j++][0] = num;
					num = 0;
					continue;
				}
				
				m_PrimiumItem[j][++num] = idItem;
			}
		g_pParamMgr->HT_bUnLockID( m_iNPCIndex );
	}

	*/
	// 프리미엄 창 활성화
	HT_vNPCControl_ItemListWin_Active();
}

// 프리미엄 해당텝의 NPCID를 얻어온다.
HTint CHTNPCControl::HT_iGetCashNPC(int TabID)
{
	int NPCID = 0;

	if ( g_wResentZoneServerID == 21 )	// 예외 추가됨
	{
		NPCID = 1451 + TabID;

		return NPCID;
	}

	if ( g_wResentZoneServerID == 20 )	// 예외 추가됨
	{
		NPCID = 1446 + TabID;

		return NPCID;
	}

	// 호출 NPC ID 생성
	NPCID = 1342 + (g_wResentZoneServerID * 5) + TabID - 5;

	return NPCID;
}

// 프리미엄 아이템 창 띄우기 전에 환경 셋팅 
HTvoid CHTNPCControl::HT_vNPCControl_PrimiumItemListWin_Active(HTint iNum, HTint iPage)
{
	CHTString strTemp;

	// Compute Page
	//m_iMaxPage = int((m_PrimiumItem[iNum][0]-1) / maxnum)+1;
	//m_iNowPage = iPage;


	//HTint MaxPr, iPcode = 0;
	//(m_iNowPage == m_iMaxPage) ? MaxPr = ((m_PrimiumItem[iNum][0]-1) % maxnum) + 1 : MaxPr = maxnum;

	// 목록 지우기
	for(int i=0 ; i<6 ; i++ )
		for(int j=0 ; j<10 ; j++ )
		{
			g_cUIMerchantWindow->m_ItemIndex[i+(j*6)] = 0;
			g_cUIManager->HT_SetSlotImage( UI_WINDOW_MERCHANT, i+(j*6), 0);
		}

	CHTString str;
	char strText[1000];
	for (int i=1; i<=10; i++)
	{
		int pos = m_PrimiumItem[iNum][iPage+i];
		g_cUIMerchantWindow->m_ItemIndex[i] = pos;	// 프리미엄 아이템과 호환을 위해 적용
		if (pos <= 0)	
		{	// 없는 아이템은 지움
			g_cUIManager->HT_SetSlotImage(_DIALOG_MERCHANT_PREMIUM, 200+i, 0);
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 200+i, "");
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 300+i, "");
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 400+i, "");
			continue;
		}

		// 제목
		g_pParamMgr->HT_bGetItemName(pos, &str );
		g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 200+i, str);

		// 비트맵
		DWORD nXMLID = g_pEngineHandler->HT_dwGetItemUIID(pos);
		g_cUIManager->HT_SetSlotImage(m_iMerchantNo, 200+i, nXMLID);

		// 내용
		// 1. 아이템 설명
		g_pParamMgr->HT_bGetItemDescription(pos, &str );
		if( str == HT_INFO_ITEM_DESCRIPT_NULL )	str.HT_hrCleanUp();

		// 2. 가격 얻기
		HTint iCash = 0;
		g_pParamMgr->HT_bGetItemCash(pos, &iCash );

		// 3. 최소 구입 개수
		HTint iMinCount = HT_iNPCControl_GetMinCountForChargeItem( pos );

		// 4. 할인적용 개수
		HTint iDiscountNum = HT_iNPCControl_GetDiscountNumForChargeItem( pos );

		if( g_iInationalType == INATIONALTYPE_KOREA || g_iInationalType == INATIONALTYPE_JAPEN )
		{

			if (iCash < 2300)
			{
				HT_g_Script_SetMessage( eMsgExPlanPremiumItem09, &strTemp, _T("") );		//	"%s \n최소 %d개 구입(%d개 구입 시 20％할인)"
				sprintf(strText, strTemp, str.HT_szGetString(), iMinCount, iDiscountNum);
			}
			else
			{
				sprintf(strText, "%s", str.HT_szGetString());
			}

		}
		else if( g_iInationalType == INATIONALTYPE_CHINA )
		{
			// 중국의 경우 처리
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem09, &strTemp, _T("") );		//	"%s \n최소 %d개 구입(%d개 구입 시 20％할인)"

			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( pos ) )
			{
				if (iCash < 30)
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem22, &strTemp, _T("") );		//	"%s \n최소 %d개 구입(%d개 구입 시 10％할인)"
			}
			else
			{
				if (iMinCount == 20)
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem22, &strTemp, _T("") );		//	"%s \n최소 %d개 구입(%d개 구입 시 10％할인)"
			}

			sprintf(strText, strTemp, str.HT_szGetString(), iMinCount, iDiscountNum);
		}
		else
		{
			sprintf(strText, "%s", str.HT_szGetString());
		}

		g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 300+i, strText);
		
		CHTString szMoney = g_cUIManager->HT_strSetRestMark( iCash ); // 쉼표 처리

		HT_g_Script_SetMessage( eMsgPriceToTaney, &strTemp, _T("") );		//	"가격: %s 타니"
		sprintf(strText, strTemp, szMoney.HT_szGetString());
		g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 400+i, strText);
	}

	// Page Output
	str.HT_szFormat("(Page %d/%d)",m_iNowPage, m_iMaxPage);
	//g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 2, str);
}


//---------구입할 수 있는 아이템 리스트 구하기-------//
HTvoid CHTNPCControl::HT_vNPCControl_GetItemList()
{
	// 아이템 리스트 결과를 기다리다가 다른 단계로 바꿨을 경우 리스트를 처리하지 않는다.
	//CHTString event = g_pEngineHandler->HT_szGetClientEvent();
	//if(event != "구입대기모드")
	//	return;

	// 제작 가능한 아이템을 저장할 장소 초기화
	HT_vNPCControl_ButtonCheck_List_Delete();

	// 현재 창 상태 변화
	//-------- 대화상자 대화 바꾸기 -----------//
	// 선택문의 마지막에는 선택문이 아닌 다른 입력에 의해 다음 단계로 넘어갈 때 사용하기 위한 값이 있다
	// 0~m_nSelectCount-1 : 선택문, m_nSelectCount : 확인, m_nSelectCount+1 : 취소
	HT_vNPCControl_GetNextStep(m_nSelectCount);

	HT_vNPCControl_ItemListWin_Active();

	if( g_pParamMgr->HT_bLockID( m_iNPCIndex ) == true )
	{
		int iCount = g_pParamMgr->HT_iGetNPCSellingItemCount( );

		int idItem = 0;
		for ( int i = 0; i < iCount; ++i )
		{
			if ( g_pParamMgr->HT_bGetNPCSellingItem( i, &idItem ) )
				HT_vNPCControl_InsertItemInShopList( idItem );
		}

		g_pParamMgr->HT_bUnLockID( m_iNPCIndex );
	}
}


// shop list에 아이템 넣기
HTvoid CHTNPCControl::HT_vNPCControl_InsertItemInShopList( HTint iIndex )
{
	// 아이템 리스트 결과를 기다리다가 다른 단계로 바꿨을 경우 리스트를 처리하지 않는다.
	//if(m_iResent != NPC_RESENT_ITEM_LIST && m_iResent != NPC_RESENT_REFINE)
	//	return;

	//-------------리스트 위치 구하기----------//
/*	HTint iBnCount;		// 아이테 분류 개수
	if( m_iEconomy_NPC == eEconomy_Item_Sword)		// 무기
	{
		iBnCount = g_ItemClass[0];	
	}
	else if( m_iEconomy_NPC == eEconomy_Item_Armor)	// 방어구
	{
		iBnCount = g_ItemClass[1];
	}
	else											// 액세서리 상인
	{
		iBnCount = g_ItemClass[2];
	}
*/
	// 새로 추가 되는 아이템 정보
	ECONOMY_ITEM_INFO* pTemp = new ECONOMY_ITEM_INFO;
	pTemp->iIndex = iIndex;
	pTemp->iWidth = 1;
	pTemp->iLength = 1;
	pTemp->pNext = NULL; 

	// 새로운 아이템을 리스트에 등록
	HTint iItemClass = 0;
/*	HTbool	bItemClassCheck = HT_FALSE;	// 새로운 아이템을 첨가할 아이템 분류 찾기
	for(iItemClass = 0; iItemClass < iBnCount ; ++iItemClass)
	{
		// 맞는 아이템 분류가 없었다면 bItemClassCheck는 HT_FALSE이다
		if(m_iEconomy_NPC == eEconomy_Item_Sword)	// 현재 선택한 NPC가 무기 상인이면
		{
			HTshort sType = 0;
			if( g_pParamMgr->HT_bGetItemType( pTemp->iIndex, &sType ) == false )
				return;

			// 검과 도끼가 한손/양손이 있기 때문에 +2를 했음.
			if(g_ServerClass[m_iEconomy_NPC+iItemClass] == sType)
				bItemClassCheck = HT_TRUE;
			else
				bItemClassCheck = HT_FALSE;
		}
		else if( m_iEconomy_NPC == eEconomy_Item_Armor ) // 방어구 상인
		{
			// 갑옷
			if( CHTParamIDCheck::HT_bIsItemDefenceArmor(pTemp->iIndex) && iItemClass == _ITEMMAKE_DEFENCE_ARMOR )		
				bItemClassCheck = HT_TRUE;
			// 모자
			else if( CHTParamIDCheck::HT_bIsItemDefenceHelmet(pTemp->iIndex) && iItemClass == _ITEMMAKE_DEFENCE_HELMET )
				bItemClassCheck = HT_TRUE;
			// 신발
			else if( CHTParamIDCheck::HT_bIsItemDefenceShoes(pTemp->iIndex) && iItemClass == _ITEMMAKE_DEFENCE_SHOES )	
				bItemClassCheck = HT_TRUE;
			// 허리띠
			else if( CHTParamIDCheck::HT_bIsItemDefenceBelt(pTemp->iIndex) && iItemClass == _ITEMMAKE_DEFENCE_BELT )	
				bItemClassCheck = HT_TRUE;
			// 방패
			else if( CHTParamIDCheck::HT_bIsItemDefenceShield(pTemp->iIndex) && iItemClass == _ITEMMAKE_DEFENCE_SHIELD )
				bItemClassCheck = HT_TRUE;
			else
				bItemClassCheck = HT_FALSE;
		}
		else	// 액세서리 상인
		{
			// 소모성아이템 - 물약/표창/화살
			if( CHTParamIDCheck::HT_bIsItemUsable(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_USABLE )			
				bItemClassCheck = HT_TRUE;
			// 제련아이템
			else if( CHTParamIDCheck::HT_bIsItemRefine(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_REFINE )			
				bItemClassCheck = HT_TRUE;
			// 팔찌
			else if( CHTParamIDCheck::HT_bIsItemAccessoryBracelet(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_BRACELET )	
				bItemClassCheck = HT_TRUE;
			// 목걸이
			else if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_NECKLACE )
				bItemClassCheck = HT_TRUE;
			// 귀걸이
			else if( CHTParamIDCheck::HT_bIsItemAccessoryEarring(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_EARRING )	
				bItemClassCheck = HT_TRUE;
			// 반지
			else if( CHTParamIDCheck::HT_bIsItemAccessoryRing(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_RING )		
				bItemClassCheck = HT_TRUE;
			// 인벤토리확장
			else if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_EXPANDINVEN )	
				bItemClassCheck = HT_TRUE;
			else
				bItemClassCheck = HT_FALSE;
		}
 
		if(bItemClassCheck)
*/		{
			if(m_Economy_List[iItemClass].vWinCount.size() == 0)
			{
				m_Economy_List[iItemClass].vWinCount.push_back(1);	// 현재 창의 아이템 개수
				m_byEconomy_Resent_WinIndex = 0;					// 현재 보여주는 창의 index

				pTemp->byWinIndex = 0;
				pTemp->iXpos = 0;
				pTemp->iYpos = 0;
			}
			else
			{
				// 같은 분류에서 index가 같은 아이템이 있는지 검사
				HTbool res = HT_bNPCControl_CheckItemIndex(iItemClass, pTemp->iIndex);
				if(res == HT_TRUE)	// 이미 같은 인덱스의 아이템 정보가 있으면
				{
					HT_DELETE(pTemp);
					return;
				}

				// 아이템이 위치할 좌표 찾기
				res = HT_FALSE;
				BYTE byWinCount;
				HTint iXpos, iYpos;	// 리스트 내의 x, y좌표
				for( byWinCount = 0; byWinCount < m_Economy_List[iItemClass].vWinCount.size(); ++byWinCount)
				{
					for( iYpos = 0 ; iYpos < LIST_LENGTH ; ++iYpos )
					{
						for( iXpos = 0 ; iXpos < LIST_WIDTH ; ++iXpos )
						{
							res = HT_bNPCControl_ItemListCheck( iItemClass, byWinCount, iXpos, iYpos, 
																		pTemp->iWidth, pTemp->iLength );

							if(res == HT_TRUE)
								break;
						}
						if(res == HT_TRUE)
							break;
					}
					if(res == HT_TRUE)
						break;
				}

				if(res == HT_TRUE)	// 현재 창에 남은 공간이 있으면
				{
					++ m_Economy_List[iItemClass].vWinCount[byWinCount];	// 현재 창의 아이템 개수 증가
					pTemp->byWinIndex = byWinCount;
					pTemp->iXpos = iXpos;
					pTemp->iYpos = iYpos;
				}
				else	 
				{	
					m_Economy_List[iItemClass].vWinCount.push_back(1);	// 새로운 창 추가
					pTemp->byWinIndex = m_Economy_List[iItemClass].vWinCount.size()-1;	// 창 index는 0부터 시작한다..
					pTemp->iXpos = 0;
					pTemp->iYpos = 0;

					// 현재 보여지는 아이템 분류일 경우 next 버튼 보이게..
				}
			}
			
			// 새 아이템의 이미지 셋팅
			// 친밀도 조건에 의해 제조 가능/불가능 설정
			//if(pTemp->byFriendly == 0x00)	// 현재 친밀도레벨
			//	pTemp->bWorkPossible = HT_TRUE;
			//else	// 0x01	상위 친밀도레벨
			//	pTemp->bWorkPossible = HT_FALSE;

			if(m_Economy_List[iItemClass].pInfoHead == NULL)	// 리스트가 하나도 없으면 처음에 넣는다.
				m_Economy_List[iItemClass].pInfoHead = pTemp;
			else
				m_Economy_List[iItemClass].pInfoTail->pNext = pTemp;	// 리스트 마지막에 연결
			
			m_Economy_List[iItemClass].pInfoTail = pTemp;		// 리스트 마지막 위치 갱신
//			break;
		}
//	}
	
	if( /*bItemClassCheck == HT_TRUE &&*/ pTemp->byWinIndex == m_byEconomy_Resent_WinIndex )
	{
		// 새 아이템의 비트맵 등록
		int nXMLID = g_pEngineHandler->HT_dwGetItemUIID(pTemp->iIndex);
		HTint nToBitmapNo = pTemp->iYpos * LIST_WIDTH + pTemp->iXpos;	// 아이템 리스트 창에서의 칸 번호
		g_cUIManager->HT_SetSlotImage(_DIALOG_ACCESSORY_MERCHANT, nToBitmapNo, nXMLID);
		// 제조불가능이면 바탕을 빨간 블럭으로 표시한다.
	}
}

// 같은 분류에서 index가 같은 아이템이 있는지 검사
HTbool CHTNPCControl::HT_bNPCControl_CheckItemIndex(HTint iItemClass, DWORD dwIndex)
{
	ECONOMY_ITEM_INFO* pLoc;
	pLoc = m_Economy_List[iItemClass].pInfoHead;
	
	while(pLoc != NULL)
	{
		if(pLoc->iIndex == dwIndex)
			return HT_TRUE;

		pLoc = pLoc->pNext;
	}
	
	return HT_FALSE;
}

// iXpos, iYpos : 검사할 위치
HTbool CHTNPCControl::HT_bNPCControl_ItemListCheck(HTint iItemClass, BYTE byWinCount, HTint nSellX, HTint nSellY, HTint nItemWidth, HTint nItemLength)
{
	ECONOMY_ITEM_INFO* pLoc;
	pLoc = m_Economy_List[iItemClass].pInfoHead;
	while(pLoc != NULL)
	{
		if(pLoc->byWinIndex == byWinCount)
		{
			for(int x = nSellX; x < (nSellX + nItemWidth) ; ++x)
			{
				for( int y = nSellY; y < (nSellY + nItemLength) ; ++y)
				{
					if(pLoc->iXpos <= x && x < pLoc->iXpos+pLoc->iWidth 
						&& pLoc->iYpos <= y && y < pLoc->iYpos+pLoc->iLength)
					{
						return HT_FALSE;
					}
				}
			}
		}
		pLoc = pLoc->pNext;
	}

	return HT_TRUE;
}

// 제조창 아이템 정보 데이터 모두 지우기
HTvoid CHTNPCControl::HT_vNPCControl_DeleteWorkItemInfo()
{
	m_vItemInfo.strName.str.HT_hrCleanUp();
	vec_It it;

	if(m_vItemInfo.vLimitStr.size() > 0)
	{
		it = m_vItemInfo.vLimitStr.begin();
		while ( it != m_vItemInfo.vLimitStr.end() )
		{
			HT_DELETE( *it );
			it = m_vItemInfo.vLimitStr.erase( it );
		}
	}
	
	if(m_vItemInfo.vSourceStr.size() > 0)
	{
		it = m_vItemInfo.vSourceStr.begin();
		while ( it != m_vItemInfo.vSourceStr.end() )
		{
			HT_DELETE( *it );
			it = m_vItemInfo.vSourceStr.erase( it );
		}
	}
	vec_exp_It exp_it;
	if( m_vItemInfo.vAttributeStr.size() > 0)
	{
		exp_it = m_vItemInfo.vAttributeStr.begin();
		while ( exp_it != m_vItemInfo.vAttributeStr.end() )
		{
			HT_DELETE( *exp_it );
			exp_it = m_vItemInfo.vAttributeStr.erase( exp_it );
		}
	}
}

//----------제조할 아이템과 보조재료를 클릭했을 경우---------//
HTRESULT CHTNPCControl::HT_hrNPCControl_ItemWork_LButtonClick( DWORD dwItemKeyID )
{
	// 1. 제련할 아이템을 먼저 올려놓는다.
	// 2. 강화제련 또는 주술 제련 아이템을 올려놓는다.
	// 3. 수호천사와 같은 제련 아이템을 올려놓는다.
	// 선영범(grecia79@hanbitsoft.co.kr)

	// ===============================
	// Step 1. 초기화 및 예외 처리
	// ===============================

	// A. 이미 선택한 아이템이면 변화 없음
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, "");
	if( dwItemKeyID == m_dwWorkItem )	return HT_FAIL;

	// A. 선택한 아이템 ID 얻기
	DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(dwItemKeyID);	

	// B. 해당아이템이 클라이언트에 없다면 실패 반환
	if( dwIndex == 0 )	return HT_FAIL;

	// ===============================
	// Step 2. 아이템 구분에 따른 처리
	// ===============================

	// (강화제련 6501~6525 || 속성제련 6601~6700 || 보조제련 6551~6600 || 첨가대역2 6526~6550 || 초기화아이템 6614)
	// 

	// A. 제련재료 아이템 선택시 이미지 및 가격을 출력
	if( CHTParamIDCheck::HT_bIsItemRefine( dwIndex ) || dwIndex == HT_INDEX_INIT_SUB_REFINE )
	{
		if (dwItemKeyID == m_nEconomy_Work_SubItemKeyID[0] ) return HT_FAIL;
		if (m_nEconomy_Work_SubItemKeyID[0] != 0) 
		{
			// 필요한 루피아 출력
			CHTString str;
			str = g_cUIManager->HT_strSetRestMark(m_nEconomy_Work_LimitRupiah);	// 쉼표
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, str);

			return HT_FAIL;
		}

		// 이전에 재련할 아이템이 올라오지 않았다면 가격 계산을 할 수 없으므로 루프 나감
		if (m_dwWorkItem == 0) return HT_FAIL;
		
		// 다음과 같은 아이템은 물품에 속성제련이 되어 있을때만 사용가능함
		HTbyte byLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( m_dwWorkItem );
		if (byLevel < 1)
		{
			switch (dwIndex)
			{
				case 6624:	//타루 라가마니
				case 6625:	//타루 닐라마니
				case 6626:	//타루 비사잔
				case 6627:	//타루 루바티
				case 6628:	//타루 옴 얀트라
				case 6629:	//타루 마니푸라
				case 6630:	//타루 비슈다
				case 6631:	//타루 아나하타
				case 6632:	//타루 아즈나
					{
						m_bMessage_Error = HT_TRUE;	// 에러 있음
						g_cUIRefineWindow->m_nMessageBoxNo = 0;
						// 현재 조건에서는 보조제련 재료를 사용할 수 없습니다.
						HT_vNPCControl_SetMessage( eMsgItemRefineSubInitWarning2 );

						m_byResent_ServerMsg = SERVER_MSG_NONE;
						m_byMessageWin = NPC_MESSAGE_COMPLETE;
						g_cUIManager->HT_MessageBox(_DIALOG_REFINE, m_szMessage, 0);
					}
					return HT_FAIL;

				default:	// 그외의 아이템은 해당사항 없음
					break;
			}
		}

		// [보조 재료 첨가제]라면 두번째 제련재료 위치에 출력
		if (CHTParamIDCheck::HT_bIsItemRefineSub2( dwIndex )) //HT_MAIN_REFINE_ZARD_INDEX
		{
			// 이전 비트맵 지우고 새로운 보조제련 아이템 설정
			if (dwItemKeyID == m_nEconomy_Work_SubItemKeyID[1] ) return HT_FAIL;
			m_nEconomy_Work_SubItemKeyID[1] = dwItemKeyID;
			//g_cUIManager->HT_SetSlotImage( _DIALOG_REFINE, 3, 0);

			//HTPoint pSize = g_cItemSystem->HT_ptItemSystem_GetSize(dwItemKeyID); 
			g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, 3, g_pEngineHandler->HT_dwGetItemUIID( dwIndex ) );

			DWORD dwItemID = g_cItemSystem->HT_dwSystem_GetItemIndex(m_nEconomy_Work_SubItemKeyID[1]);
			DWORD dwItemID2 = g_cItemSystem->HT_dwSystem_GetItemIndex(m_nEconomy_Work_SubItemKeyID[0]);

			// [속성 제련 아이템] 이라면 속성 제련 비용으로 계산
			if (CHTParamIDCheck::HT_bIsItemRefineSub( dwItemID2 )) 
			{
				m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( 0, m_nItemCost );
			}
			// [강화 제련 아이템] 이라면 강화 제련 비용으로 계산
			else 
			{
				HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel(m_dwWorkItem);	// 현 아이템의 강화제련 레벨 얻기
				//HTint iAttriRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( m_dwWorkItem );// 현 아이템의 주술제련 레벨 얻기
			
				m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( byLevel, m_nItemCost );
			}

			// [6552	나야티	아이템의 제련 비용을 감소합니다] 보조 재료 첨가제 조사하여 비용감소 아이템이면 감소시킨다.
			if (dwItemID == 6552)
			{
				HTint iDiscount = 0;

				g_pParamMgr->HT_bGetItemEffect1Param1(dwItemID, &iDiscount);
				m_nEconomy_Work_LimitRupiah = (m_nEconomy_Work_LimitRupiah * (100 - iDiscount)) / 100;
			}

			// 필요한 루피아 출력
			CHTString str;
			str = g_cUIManager->HT_strSetRestMark(m_nEconomy_Work_LimitRupiah);	// 쉼표
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, str);

			// 인벤토리의 슬롯박스 이동 가능 불가능 처리
			if (g_cUIRefineWindow->m_iWindowIndex[3])
				g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[3], g_cUIRefineWindow->m_iControlIndex[3], true);

			g_cUIRefineWindow->m_iWindowIndex[3] = g_cUIRefineWindow->m_iWindowIndex[0];
			g_cUIRefineWindow->m_iControlIndex[3] = g_cUIRefineWindow->m_iControlIndex[0];
			g_cUIManager->HT_RefuseSlotImageMoving();
			g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[3], g_cUIRefineWindow->m_iControlIndex[3], false);

			return HT_OK;
		}

		// [보조 재료 첨가제2]라면 세번째 제련재료 위치에 출력
		if (CHTParamIDCheck::HT_bIsItemRefineSub3( dwIndex )) //HT_MAIN_REFINE_ZARD_INDEX
		{
			// 이전 비트맵 지우고 새로운 보조제련 아이템 설정
			if (dwItemKeyID == m_nEconomy_Work_SubItemKeyID[2] ) return HT_FAIL;
			m_nEconomy_Work_SubItemKeyID[2] = dwItemKeyID;
			//g_cUIManager->HT_SetSlotImage( _DIALOG_REFINE, 3, 0);

			//HTPoint pSize = g_cItemSystem->HT_ptItemSystem_GetSize(dwItemKeyID); 
			g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, 4, g_pEngineHandler->HT_dwGetItemUIID( dwIndex ) );

			DWORD dwItemID = g_cItemSystem->HT_dwSystem_GetItemIndex(m_nEconomy_Work_SubItemKeyID[2]);
			DWORD dwItemID2 = g_cItemSystem->HT_dwSystem_GetItemIndex(m_nEconomy_Work_SubItemKeyID[0]);

			// [속성 제련 아이템] 이라면 속성 제련 비용으로 계산
			if (CHTParamIDCheck::HT_bIsItemRefineSub( dwItemID2 )) 
			{
				m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( 0, m_nItemCost );
			}
			// [강화 제련 아이템] 이라면 강화 제련 비용으로 계산
			else 
			{
				HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel(m_dwWorkItem);	// 현 아이템의 강화제련 레벨 얻기
				//HTint iAttriRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( m_dwWorkItem );// 현 아이템의 주술제련 레벨 얻기
			
				m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( byLevel, m_nItemCost );
			}

			// [6552	나야티	아이템의 제련 비용을 감소합니다] 보조 재료 첨가제 조사하여 비용감소 아이템이면 감소시킨다.
			if (dwItemID == 6526)
			{
				// 두번째에도 나야티를 넣을 경우 사용할 수 없음
				if (m_nEconomy_Work_SubItemKeyID[1] == 6552)
					return HT_FAIL;

				HTint iDiscount = 0;

				g_pParamMgr->HT_bGetItemEffect1Param1(dwItemID, &iDiscount);
				m_nEconomy_Work_LimitRupiah = (m_nEconomy_Work_LimitRupiah * (100 - iDiscount)) / 100;
			}

			// 필요한 루피아 출력
			CHTString str;
			str = g_cUIManager->HT_strSetRestMark(m_nEconomy_Work_LimitRupiah);	// 쉼표
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, str);

			// 인벤토리의 슬롯박스 이동 가능 불가능 처리
			if (g_cUIRefineWindow->m_iWindowIndex[4])
				g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[4], g_cUIRefineWindow->m_iControlIndex[4], true);

			g_cUIRefineWindow->m_iWindowIndex[4] = g_cUIRefineWindow->m_iWindowIndex[0];
			g_cUIRefineWindow->m_iControlIndex[4] = g_cUIRefineWindow->m_iControlIndex[0];
			g_cUIManager->HT_RefuseSlotImageMoving();
			g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[4], g_cUIRefineWindow->m_iControlIndex[4], false);

			return HT_OK;
		}

		// 이전 비트맵 지우고 새로운 보조제련 아이템 설정
		m_nEconomy_Work_SubItemKeyID[0] = dwItemKeyID; // HT_bNPCControl_SetAidItemResource( dwItemKeyID );	
		m_nEconomy_Work_SubItemIndex = dwIndex;

		g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, 2, g_pEngineHandler->HT_dwGetItemUIID( dwIndex ) );

		// =========================================
		// Step 2-1. 아이템 제련에 필요한 가격 계산
		// =========================================

		// [속성 제련 아이템] 이라면 속성 제련 비용으로 계산
		if (CHTParamIDCheck::HT_bIsItemRefineSub( dwIndex )) 
		{
			m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( 0, m_nItemCost );
		}
		// [강화 제련 아이템] 이라면 강화 제련 비용으로 계산
		else 
		{
			HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel(m_dwWorkItem);	// 현 아이템의 강화제련 레벨 얻기
			//HTint iAttriRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( m_dwWorkItem );// 현 아이템의 주술제련 레벨 얻기
		
			m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( byLevel, m_nItemCost );
		}

		// [6552	나야티	아이템의 제련 비용을 감소합니다] 보조 재료 첨가제 조사하여 비용감소 아이템이면 감소시킨다.
		DWORD dwItemID = g_cItemSystem->HT_dwSystem_GetItemIndex(m_nEconomy_Work_SubItemKeyID[1]);
		if (dwItemID == 6552)
		{
			HTint iDiscount = 0;

			g_pParamMgr->HT_bGetItemEffect1Param1(dwItemID, &iDiscount);
			m_nEconomy_Work_LimitRupiah = (m_nEconomy_Work_LimitRupiah * (100 - iDiscount)) / 100;
		}

		DWORD dwItemID2 = g_cItemSystem->HT_dwSystem_GetItemIndex(m_nEconomy_Work_SubItemKeyID[2]);
		if (dwItemID2 == 6526)
		{
			HTint iDiscount = 0;

			g_pParamMgr->HT_bGetItemEffect1Param1(dwItemID2, &iDiscount);
			m_nEconomy_Work_LimitRupiah = (m_nEconomy_Work_LimitRupiah * (100 - iDiscount)) / 100;
		}

		// 필요한 루피아 출력
		CHTString str;
		str = g_cUIManager->HT_strSetRestMark(m_nEconomy_Work_LimitRupiah);	// 쉼표
		g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, str);

		// 인벤토리의 슬롯박스 이동 가능 불가능 처리
		if (g_cUIRefineWindow->m_iWindowIndex[2])
			g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[2], g_cUIRefineWindow->m_iControlIndex[2], true);

		g_cUIRefineWindow->m_iWindowIndex[2] = g_cUIRefineWindow->m_iWindowIndex[0];
		g_cUIRefineWindow->m_iControlIndex[2] = g_cUIRefineWindow->m_iControlIndex[0];
		g_cUIManager->HT_RefuseSlotImageMoving();
		g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[2], g_cUIRefineWindow->m_iControlIndex[2], false);

		return HT_OK;
	}	
	// 제련할 수 있는 아이템(무기/방어구/액세서리)의 처리
	else if(( CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) || CHTParamIDCheck::HT_bIsItemDefence( dwIndex )	|| CHTParamIDCheck::HT_bIsItemAccessory( dwIndex ))	)
	{
		// 필요한 루피아 출력
		if (m_nEconomy_Work_SubItemKeyID[0] != 0 || m_nEconomy_Work_SubItemKeyID[1] != 0)
		{
			CHTString str;
			str = g_cUIManager->HT_strSetRestMark(m_nEconomy_Work_LimitRupiah);	// 쉼표
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, str);
		}

		// A. 이전에 올려놓은 아이템이 있었다면 갱신할 수 없다. (m_dwWorkItem는 제련창 팝업시마다 0으로 초기화 필수)
		if (m_dwWorkItem != 0) return HT_FAIL;

		// B. 아이템의 가격을 얻어 올 수 없다면 제련불가 안내
		if( g_pParamMgr->HT_bGetItemRupiah( dwIndex, &m_nItemCost ) == false )
		{
			// 제련할 수 없는 아이템입니다
			HT_vNPCControl_SetMessage( eMsgItemRefineDoNot );

			m_byResent_ServerMsg = SERVER_MSG_NONE;
			m_bMessage_Error = HT_TRUE;	//에러있음

			m_byMessageWin = NPC_MESSAGE_COMPLETE;
			g_cUIManager->HT_MessageBox(_DIALOG_REFINE, m_szMessage, 0);
			return HT_FAIL;
		}

		m_dwWorkItem = dwItemKeyID;	// 제련할 아이템의 KeyID 얻기

		// 이전 아이템 비트맵 지우고 제련할 아이템 이미지 삽입
		g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, 1, g_pEngineHandler->HT_dwGetItemUIID( dwIndex ) );

		g_cUIRefineWindow->m_iWindowIndex[1] = g_cUIRefineWindow->m_iWindowIndex[0];
		g_cUIRefineWindow->m_iControlIndex[1] = g_cUIRefineWindow->m_iControlIndex[0];
		g_cUIManager->HT_RefuseSlotImageMoving();
		g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[1], g_cUIRefineWindow->m_iControlIndex[1], false);

		return HT_OK;
	}
	// 그외의 아이템은 제련할 수 없으므로 실패 반환
	else 
	{
		return HT_FAIL;
	}
}

//----------- 제련을 위한 제단을 클릭 -----------//
HTRESULT CHTNPCControl::HT_hrNPCControl_ClickRefineObject( )
{
	m_iResent = NPC_RESENT_REFINE;
	m_byMessageWin = NPC_MESSAGE_NONE;	// 메세지 창 안떠있음
	// 현재 캐릭터의 위치 저장
	m_pCharPos_Memory = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	
	// 아이템 제련 창 열기
	HT_vNPCControl_ItemWorkWin_Active();

	return HT_OK;
}

//----------- 제련창 띄우기 ---------------//
HTvoid CHTNPCControl::HT_vNPCControl_ItemWorkWin_Active()
{
	// 만약 제련 윈도우가 팝업되어 있는 상태라면 인벤토리 UI 리붓하고 시작
	//if ( g_cUIManager->HT_isShowWindow( _DIALOG_REFINE ) == HT_TRUE )
	g_cNPCControl->HT_vNPCControl_ButtonCheck_Work_Delete();

	g_cUIManager->HT_ShowWindow( _DIALOG_REFINE );
	HT_vNPCControl_PopUpInventory( _DIALOG_EQUPINVENTORY );	// PC 인벤토리 창 띄움
	g_cUIRefineWindow->m_SetItemNumber = 0;


}

//--------ESC키/X버튼을 눌렀을때 제련창 닫기-----------//
HTvoid CHTNPCControl::HT_vNPCControl_ESC_ItemWorkClose()
{
	HT_vNPCControl_ButtonCheck_Work_Delete();
	m_iResent = NPC_RESENT_NONE;
}

//-----3-1.제조 체크_이미지 지우기-----//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_Work_Delete()
{
	// 아이템 이미지 지우기
	g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, 1, 0);
	g_cUIRefineWindow->HT_vRefineWindow_WindowHide();

	//----------제조 정보 삭제---------//
	// 제조창 위에 있던 재료 아이템 이미지 지우기.
	HT_vNPCControl_ButtonCheck_Work_TotalCancel();
}

//-----3-3.제조 체크_전체 캔슬-----//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_Work_TotalCancel()
{
	// 제련창의 보조재료 이미지 지우기
	for (HTint i = 0; i<3; ++i)
		g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, i + 1, 0);	// UI 이미지 초기화

	for (HTint j = 0; j<5; ++j)
	{
		m_nEconomy_Work_SubItemKeyID[j] = 0;
		g_cUIRefineWindow->m_iWindowIndex[j] = 0;
	}

	// 아이템 정보 초기화
	m_dwWorkItem = 0;
	m_nEconomy_Work_ResRupiah = 0;
	m_nEconomy_Work_LimitRupiah = 0;

	g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE, 1, "");
}

//-----3-4.제조 체크_제조 확인-----//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_Work_Ok()
{
	CHTString strName;
	HTint nCheck = ECONOMY_ADDITEM_ERR_NONE;
  
	//-------------- 보조재료가 첨가 가능한 것인지 검사한다 ----------------//
	if( m_nEconomy_Work_SubItemKeyID[0] == 0 )
	{
		m_bMessage_Error = HT_TRUE;	// 에러 있음
		// 보조 재료를 넣어주십시오
		HT_vNPCControl_SetMessage( eMsgItemRefineSelectMeterial );
	}
	else if( m_dwWorkItem == 0 )
	{
		m_bMessage_Error = HT_TRUE;	// 에러 있음
		// 제련할 아이템을 선택하여 주십시오.
		HT_vNPCControl_SetMessage( eMsgItemRefineSelectItem );
	}
	else 
	{
		nCheck = HT_nNPCControl_CheckAidItemCondition(strName);	

		if(nCheck == ECONOMY_ADDITEM_ERR_ITEMINDEX)
		{
			m_bMessage_Error = HT_TRUE;	// 에러 있음
			// 아이템 정보를 찾지 못했습니다.
			HT_vNPCControl_SetMessage( eMsgItemCommonCannotFindInfo );
		}
		else	// 아이템 정보를 찾아서 검사한 결과
		{/*
			// 보조 속성제련 아이템인 비카리가 있다면 제한없이 모든 아이템으로 제련 가능
			DWORD dwRefineIndex2 = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[1] );
			if (dwRefineIndex2 == 6555)
			{
				// 먼저 조건을 검사하여 OKay 상태라면 비카리를 사용할 필요가 없다는 메시지 출력
				if (nCheck == ECONOMY_ADDITEM_ERR_NONE)
				{
					nCheck = ECONOMY_ADDITEM_ERR_NEEDNOT;
					m_bMessage_Error = HT_TRUE;	// 에러 있음
					HT_vNPCControl_SetMessage( eMsgRefineErr2 );

					g_cUIRefineWindow->m_nMessageBoxNo = 0;
					m_byResent_ServerMsg = SERVER_MSG_NONE;
					m_byMessageWin = NPC_MESSAGE_COMPLETE;
					g_cUIManager->HT_MessageBox( _DIALOG_REFINE, m_szMessage, 0);
					return;
				}
				else if (nCheck == ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM)
				{
					nCheck = ECONOMY_ADDITEM_ERR_NONE;
					m_bMessage_Error = HT_FALSE;	// 에러 있음
				}
			}
*/
			if(nCheck == ECONOMY_ADDITEM_ERR_NEEDNOT)
			{
				m_bMessage_Error = HT_TRUE;	// 에러 있음
				HT_vNPCControl_SetMessage( eMsgRefineErr2 );
			}
			else if(nCheck == ECONOMY_ADDITEM_ERR_MAIN_OVER)	// 강화 제련 총 횟수 에러
			{
				m_bMessage_Error = HT_TRUE;	// 에러 있음
				// 강화 제련을 할 수 없는 아이템입니다.
				HT_vNPCControl_SetMessage( eMsgItemRefineMainCannot );
			}
			else if(nCheck == ECONOMY_ADDITEM_ERR_SUB_OVER) // 주술 제련 총 횟수 에러
			{
				m_bMessage_Error = HT_TRUE;	// 에러 있음
				// 주술 제련을 할 수 없는 아이템입니다.
				HT_vNPCControl_SetMessage( eMsgItemRefineSubCannot );
			}
			else if(nCheck == ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM)	// 첨가 불가능한 보조재료
			{
				m_bMessage_Error = HT_TRUE;	// 에러 있음
				// %s는 첨가할 수 없는 보조재료입니다.
				HT_vNPCControl_SetMessage( eMsgItemRefineMeterialErr );
			}
			else if( nCheck == ECONOMY_ADDITEM_ERR_CANNOT ) // 제련 확률 0. 제련할 수 없음
			{
				m_bMessage_Error = HT_TRUE;	// 에러 있음
				// 이 제련 재료로는 더 이상 제련을 할 수 없습니다. 보다 상급의 제련 재료를 사용해 주시기 바랍니다.							
				HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel1 );
			}
			else //if( nCheck == ECONOMY_ADDITEM_ERR_NONE )	// 첨가재료 관련 에러가 없을 경우
			{
				// 인벤토리 안에 있는 루피아 검사
				m_nEconomy_Work_ResRupiah = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();

				if(m_nEconomy_Work_ResRupiah >= m_nEconomy_Work_LimitRupiah )
				{
					// 첨가할 아이템의 인덱스
					HTdword dwRefineIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[0] );
					if( CHTParamIDCheck::HT_bIsItemRefineMain( dwRefineIndex ) ) // 강화제련 경고문
					{
						HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( m_dwWorkItem );

						HTint iWarning;

						// 보조첨가제 삽입여부에 따라 메시지 변경설정
						HTdword dwRefineIndex2 = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[1] );
						if( CHTParamIDCheck::HT_bIsItemRefineSub2( dwRefineIndex2 ) )
						{
							if (byLevel < 5 && dwRefineIndex2 == 6551)	// 자드의 경우
							{
								m_bMessage_Error = HT_TRUE;	// 에러 있음
								// 현재 조건에서는 보조제련 재료를 사용할 수 없습니다.
								HT_vNPCControl_SetMessage( eMsgItemRefineSubInitWarning2 );
								
								g_cUIRefineWindow->m_nMessageBoxNo = 0;
								m_byResent_ServerMsg = SERVER_MSG_NONE;
								m_byMessageWin = NPC_MESSAGE_COMPLETE;
								g_cUIManager->HT_MessageBox( _DIALOG_REFINE, m_szMessage, 0);
								return;
							}

							if (byLevel < 4 && dwRefineIndex2 == 6556)	// 쿤드의 경우
							{
								m_bMessage_Error = HT_TRUE;	// 에러 있음
								// 현재 조건에서는 보조제련 재료를 사용할 수 없습니다.
								HT_vNPCControl_SetMessage( eMsgItemRefineSubInitWarning2 );
								
								g_cUIRefineWindow->m_nMessageBoxNo = 0;
								m_byResent_ServerMsg = SERVER_MSG_NONE;
								m_byMessageWin = NPC_MESSAGE_COMPLETE;
								g_cUIManager->HT_MessageBox( _DIALOG_REFINE, m_szMessage, 0);
								return;
							}
	
							iWarning = HT_iNPCControl_GetMainRefineWarning( byLevel+1, dwRefineIndex2 );
							
							// 만약, 그외의 보조제련재료 일경우에는 강화제련재료의 메시지를 출력 (2006. 3. 30)
							if (iWarning == -1)
								iWarning = HT_iNPCControl_GetMainRefineWarning( byLevel+1, dwRefineIndex );
						}
						else
						{
							iWarning = HT_iNPCControl_GetMainRefineWarning( byLevel+1, dwRefineIndex );
						}
						
						switch( iWarning )
						{
							case HT_REFINE_WARNING2 : 
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel2 ); break; 
							case HT_REFINE_WARNING3 : 
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel3 ); break; 
							case HT_REFINE_WARNING4 : 
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel4 ); break;
							case HT_REFINE_WARNING5 : 
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel5 ); break;
							case HT_REFINE_WARNING6 : 
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel6 ); break;
							case HT_REFINE_WARNING7 : 
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel7 ); break;
							case HT_REFINE_WARNING8 : 
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel8 ); break;
							case HT_REFINE_WARNING9 :
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel9 ); break;
							case HT_REFINE_WARNING10 :
								{
									iWarning = HT_iNPCControl_GetMainRefineWarning( byLevel+1, dwRefineIndex );

									if ( iWarning == HT_REFINE_WARNING8 )
									{
										HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel8 ); break;
									}
									else
									{
										HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel10); break;
									}								
								}
							case HT_REFINE_WARNING11 :
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel11 ); break;
							case HT_REFINE_WARNING12 :
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel11 ); break;
							case HT_REFINE_WARNING13 :
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel11 ); break;
							case HT_REFINE_WARNING14 :
								HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel11 ); break;
							default : HT_vNPCControl_SetMessage( eMsgItemRefineSubWarning ); break;
						}
					}
					else if( dwRefineIndex == HT_INDEX_INIT_SUB_REFINE ) // 주술제련 초기화 아이템
					{
						// 주술 제련을 초기화하시겠습니까?
						HT_vNPCControl_SetMessage( eMsgItemRefineSubInitWarning );
					}
					else // 주술 제련 경고문
					{
						DWORD dwRefineIndex2 = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[1] );
						if (dwRefineIndex2 == 6555)
						{
							//제련시 기존에 제련되어있던 속성은 지워집니다. 제련하시겠습니까?"
							HT_vNPCControl_SetMessage( eMsgRefineErr1 );
						}
						else
						{
							// 만약 다음과 같은 아이템의 경우라면 제한이 없으므로 무시한다.
							switch (dwRefineIndex)
							{
								case 6624:	//타루 라가마니
								case 6625:	//타루 닐라마니
								case 6626:	//타루 비사잔
								case 6627:	//타루 루바티
								case 6628:	//타루 옴 얀트라
								case 6629:	//타루 마니푸라
								case 6630:	//타루 비슈다
								case 6631:	//타루 아나하타
								case 6632:	//타루 아즈나
								case 6620:
								case 6621:
								case 6622:
								case 6623:
								case 6633:
								case 6634:
								case 6635:
								case 6636:
									//100%의 성공률로 제련이 가능합니다. 안심하고 제련하십시오.
									HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel8 );
									break;

								default:
									// 아이템을 제련하는 과정에서 실패할 수 있습니다. 아이템 제련 실패 시 제련 보조 재료가 사라집니다.
									HT_vNPCControl_SetMessage( eMsgItemRefineSubWarning );
									break;
							}
						}
					}
					m_bMessage_Error = HT_FALSE; // 에러 없음
				}
				else
				{
					// 아이템 제련에 필요한 루피아가 부족합니다.
					HT_vNPCControl_SetMessage( eMsgItemCommonMoneyErr );
					m_bMessage_Error = HT_TRUE;	// 에러 있음
				}
			}
		}	// end of else of if(nCheck == -1)
	}

	// 제조 재확인창
	if(m_bMessage_Error == HT_FALSE)	// 에러 없음
	{
		g_cUIRefineWindow->m_nMessageBoxNo = 1;
		m_byMessageWin = NPC_MESSAGE_CONFIRM;
		g_cUIManager->HT_MessageBox( _DIALOG_REFINE, m_szMessage, 1);
	}
	else	// 완료(에러)창 
	{
		g_cUIRefineWindow->m_nMessageBoxNo = 0;
		m_byResent_ServerMsg = SERVER_MSG_NONE;
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUIManager->HT_MessageBox( _DIALOG_REFINE, m_szMessage, 0);
	}
}

//----------- 헌납을 위한 오브젝트 클릭 -----------//
HTRESULT CHTNPCControl::HT_hrNPCControl_ClickOfferingObject(HTint iNum)
{
	m_nOfferingObjectNumber = iNum;

	switch(m_nOfferingObjectNumber)
	{
	case 0:	// 만다라마을 신단 
		m_nOfferingDialogNumber = _DIALOG_CHARITYWND1;
			break;
	case 1: // 주신전 시바
	case 2: // 주신전 비슈느
	case 3: // 주신전 브라흐마
		m_nOfferingDialogNumber = _DIALOG_CHARITYWND2;
			break;
	default:
		m_nOfferingDialogNumber = _DIALOG_CHARITYWND1;
	}

	m_byMessageWin = NPC_MESSAGE_NONE;	// 메세지 창 안떠있음
	m_pCharPos_Memory = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	
	g_pNetWorkMgr->RequestRefineScale(); // 현재 헌납 게이지 요청

	return HT_OK;
}

#define HT_REFINE_RATE_GAUGE_MAX	10000
//----------- 헌납창 띄우기 ---------------//
HTvoid CHTNPCControl::HT_vNPCControl_OfferingWin_Active( HTshort sGauge )
{
	if( g_cUIManager->HT_isShowWindow( m_nOfferingDialogNumber ) == HT_FALSE )
	{
		m_iResent = NPC_RESENT_REFINE_RATE_UP;
		m_bPress_OK_Button = HT_FALSE;
		m_byOfferingItemNum = 0;
		m_fGaugeTimer = 0.0f;

		// 게이지 설정
		HT_vNPCControl_Offering_SetGauge( sGauge );
		// 루피아 설정
		HT_vNPCControl_Offering_SetRupiah( 0 );

		g_cUIManager->HT_ShowWindow( m_nOfferingDialogNumber );

		// PC 인벤토리 창 띄움
		HT_vNPCControl_PopUpInventory( _DIALOG_EQUPINVENTORY );

		// 현재 캐릭터의 위치 저장
		m_pCharPos_Memory = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	}
}

// 헌납액 설정
HTvoid CHTNPCControl::HT_vNPCControl_Offering_SetRupiah( HTdword dwRupiah )
{
	m_dwOfferingRupiah = dwRupiah;

	CHTString str;
	str.HT_szFormat( "%d", dwRupiah );
	g_cUIManager->HT_SetTextLabelControl( m_nOfferingDialogNumber, 1, str.HT_szGetString() );
}

// 헌납 게이지 변경
HTvoid CHTNPCControl::HT_vNPCControl_Offering_SetGauge( HTshort sGauge )
{  
	m_sRefineRateGauge = sGauge;
	HTfloat fMaxNumber = 10000.0f;

	HTfloat fRatio = (HTfloat)sGauge/(HTfloat)fMaxNumber;
	HTfloat fRatio2 = 0.0f;
	
	if( fRatio > 1.0f )
	{ 
		fRatio = 1.0f;
		fRatio2 = ((HTfloat)sGauge - (HTfloat)fMaxNumber) / ((HTfloat)fMaxNumber) ;
		//fRatio2 = ((HTfloat)sGauge - (HTfloat)5000) / (HTfloat)5000 ;

		if( fRatio2 > 1.0f )		fRatio2 = 1.0f;
		else if( fRatio2 < 0.0f )	fRatio2 = 0.0f;
	}
	else if( fRatio < 0.0f )
	{
		fRatio = 0.0f;
	}

	if( fRatio != 0.0f )
	{
		g_cUIManager->HT_SetTextureControlDisplay( m_nOfferingDialogNumber, 4, HT_TRUE );
		g_cUIManager->HT_SetTextureControlScale( m_nOfferingDialogNumber, 4, (HTint)(fRatio*240), 5 );
	}
	else
	{
		g_cUIManager->HT_SetTextureControlDisplay( m_nOfferingDialogNumber, 4, HT_FALSE );
	}

	// 만다라마을 신단에서만 두줄 처리
	if (m_nOfferingDialogNumber == _DIALOG_CHARITYWND1 &&
		fRatio2 != 0.0f )
	{
		g_cUIManager->HT_SetTextureControlDisplay( m_nOfferingDialogNumber, 5, HT_TRUE );
		g_cUIManager->HT_SetTextureControlScale( m_nOfferingDialogNumber, 5, (HTint)(fRatio2*240), 5 );
	}
	else
	{
		g_cUIManager->HT_SetTextureControlDisplay( m_nOfferingDialogNumber, 5, HT_FALSE );
	}
}

// 헌납창 축복 수치 계산
HTint CHTNPCControl::HT_iNPCControl_CalRefineRateUpConst( )
{
	if( m_byOfferingItemNum <= 0 )
		return 0;

	HTint iConst = 0; // 아이템 지수
	HTint iItemIndex = 0, iRupiah = 0; // 아이템 인덱스, 가격
	HTint iAmount = 0;
	
	for( HTint i = 0 ; i < m_byOfferingItemNum ; ++i )
	{
		iItemIndex = (HTint)g_cItemSystem->HT_dwSystem_GetItemIndex( m_iOfferingItemKeyID[i] );
		if( iItemIndex > 0 && g_pParamMgr->HT_bGetItemRupiah( iItemIndex, &iRupiah ) == true )
			iAmount += iRupiah;
		else
			return 0;
	}
	if( iAmount <= 0 )
		return 0;

	iConst = iAmount / 255 ;
	if( iConst < 1 ) iConst = 1;

	return iConst*2 ;
}

//--------- 헌납창 버튼 체크 -----------//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_OfferingWin( int iAction, int iTarget, int iTargetID )
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	Cancel
		if( iTargetID == 3 || iTargetID == -1 )
		{
			// 헌납창 위에 있던 아이템 이미지들 지우기
			HT_vNPCControl_Offering_Cancel();
			m_iResent = NPC_RESENT_NONE;
		}
		//	OK
		else if( iTargetID == 2 )
		{
			if( m_bPress_OK_Button == HT_FALSE && (m_byOfferingItemNum > 0 || m_dwOfferingRupiah > 0) )
			{
				// 확인버튼이 눌려있는 상태
				m_bPress_OK_Button = HT_TRUE;
				this->HT_vNetWork_CSP_Req_ItemOffering();
			}
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		//	다른 윈도우에서 왔으면 아이콘 스킵
		unsigned int iWIndex, iCIndex;
		int iTextureId;
		g_cUIManager->HT_GetSlotBoxControlSourInfo( iWIndex, iCIndex, iTextureId );
		if( _DIALOG_CHARITYWND1 == iWIndex || _DIALOG_CHARITYWND2 == iWIndex )
		{
			if( _OFFERING_BEGIN <= iTargetID && iTargetID <= _OFFERING_END )
			{
				HTint iPos = iTargetID - _OFFERING_BEGIN ;
				HT_vNPCControl_OfferingItemDelete( iPos ); // 아이템 지우기
			}
		}
		else
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
		}
	}
}

//-------- ESC키/X버튼을 눌렀을때 헌납창 닫기-----------//
HTvoid CHTNPCControl::HT_vNPCControl_ESC_OfferingwinClose()
{
	HT_vNPCControl_Offering_Cancel();
	m_iResent = NPC_RESENT_NONE;
}

//----- 헌납 취소-----//
HTvoid CHTNPCControl::HT_vNPCControl_Offering_Cancel()
{
	// 헌납창 지우기
	g_cUIManager->HT_HideWindow( m_nOfferingDialogNumber );

	m_dwOfferingRupiah = 0;
	// 아이템 이미지 지우기
	HT_vNPCControl_OfferingItemDeleteAll( );
	m_fGaugeTimer = 0.0f;
}

// 헌납 아이템 지우기
HTvoid CHTNPCControl::HT_vNPCControl_OfferingItemDeleteAll( )
{
	for( HTint i = 0 ; i < MAX_ITEM_CONTRIBUTION ; ++i )
	{
		if( m_iOfferingItemKeyID[i] > 0 )
			g_cUIManager->HT_SetSlotImage( m_nOfferingDialogNumber, _OFFERING_BEGIN+i, 0 );
		m_iOfferingItemKeyID[i] = 0;
	}
	m_byOfferingItemNum = 0;

	// 확인버튼이 안눌려있는 상태
	m_bPress_OK_Button = HT_FALSE;
}

HTvoid CHTNPCControl::HT_vNPCControl_OfferingItemDelete( HTint iPos )
{
	if( m_iResent != NPC_RESENT_REFINE_RATE_UP || iPos < 0 || iPos >= m_byOfferingItemNum )
		return;

	if( m_iOfferingItemKeyID[iPos] > 0 )
	{
		// 뒤에 있던 아이템 목록 앞으로 당기기
		HTdword dwItemIndex = 0;
		HTint nXMLID = 0;
		for( HTint i = iPos ; i < (m_byOfferingItemNum-1) ; ++i )
		{
			m_iOfferingItemKeyID[i] = m_iOfferingItemKeyID[i+1];
			m_iOfferingItemPlace[i] = m_iOfferingItemPlace[i+1];
			
			// 이미지 그리기
			dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_iOfferingItemKeyID[i] );
			nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
			g_cUIManager->HT_SetSlotImage( m_nOfferingDialogNumber, _OFFERING_BEGIN+i, nXMLID );
		}
		m_iOfferingItemKeyID[i] = 0;
		m_iOfferingItemPlace[i] = -1;

		// 이미지 지우기
		g_cUIManager->HT_SetSlotImage( m_nOfferingDialogNumber, _OFFERING_BEGIN+i, 0 );
		--m_byOfferingItemNum;
	}
}

// 헌납 아이템 추가
HTvoid CHTNPCControl::HT_vNPCControl_OfferingItemAdd( DWORD dwItemKeyID )
{
	if( m_iResent != NPC_RESENT_REFINE_RATE_UP || 
		dwItemKeyID <= 0 || 
		m_byOfferingItemNum >= MAX_ITEM_CONTRIBUTION )
		return;

	HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwItemIndex <= 0 )
		return;

	// 헌납 가능한 아이템인지 검사 - 퀘스트 전용 아이템, 수집아이템, 중첩아이템 불가
	HTbyte byMaxCount = 0;
	if( CHTParamIDCheck::HT_bIsItemQuestOnly( dwItemIndex ) 
			|| CHTParamIDCheck::HT_bIsItemCollect( dwItemIndex ) 
			|| (g_pParamMgr->HT_bGetItemMaxCount( dwItemIndex, &byMaxCount ) == true && byMaxCount > 2) )
		return;

	if( m_byOfferingItemNum > 0 )	// 같은 아이템이 있는지 검사
	{
		for(HTint i = 0 ; i < m_byOfferingItemNum ; ++i )
		{
			if( m_iOfferingItemKeyID[i] == dwItemKeyID )
				return;
		}
	}

	// 아이템 위치
	HT_ITEMSETTING_FLAG sLocRoom;
	if( g_cItemSystem->HT_bItemSystem_GetItemPos( dwItemKeyID, sLocRoom ) == HT_FALSE )
		return;

	m_iOfferingItemKeyID[m_byOfferingItemNum] = dwItemKeyID;
	m_iOfferingItemPlace[m_byOfferingItemNum] = (sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y)
										+ (sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);

	// 이미지 그리기
	HTint nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
	g_cUIManager->HT_SetSlotImage( m_nOfferingDialogNumber, _OFFERING_BEGIN+m_byOfferingItemNum, nXMLID );

	++m_byOfferingItemNum;
}

// 헌납창에 있는 아이템 KeyID 구하기
HTint CHTNPCControl::HT_iNPCControl_GetKeyIDInOfferingWin( HTint iPos )
{
	if( iPos < 0 || iPos >= m_byOfferingItemNum )
		return 0;

	return m_iOfferingItemKeyID[ iPos ] ;
}


//----------강화제련 단계 별 제련 아이템의 제련 성공 확률 구하기-------------//
int HT_REFINE_MAIN_WARNING[7][MAX_REFINE_MAIN_LEVEL]
= { //1		2		3		4		5		6		7		8		9		10		11		12
	{7,		7,		7,		7,		4,		1,		1,		1,		1,		1,		1,		1}, // 일라
	{8,		8,		5,		5,		6,		6,		6,		2,		1,		1,		1,		1}, // 아지스
	{8,		8,		8,		8,		6,		6,		6,		2,		2,		2,		1,		1}, // 수라파
	{3,		3,		3,		1,		1,		1,		1,		1,		1,		1,		1,		1}, // 디파일라
	{8,		8,		8,		8,		8,		8,		8,		9,		9,		2,		2,		2},// 프라자티
	{8,		8,		8,		8,		8,		8,		8,		8,		8,		1,		1,		1}, // 삼파드
	{10,	10,		10,		10,		10,		10,		10,		11,		11,		11,		11,		11}, // 자드
};
HTint CHTNPCControl::HT_iNPCControl_GetMainRefineWarning( HTint iRefineLevel, HTdword dwMainRefineIndex )
{
	if( iRefineLevel <= 0 || iRefineLevel > MAX_REFINE_MAIN_LEVEL )
		return -1;

	switch( dwMainRefineIndex )
	{
		// 일라
		case HT_MAIN_REFINE_ILLA_INDEX : return HT_REFINE_MAIN_WARNING[0][iRefineLevel-1];
		// 아지스
		case HT_MAIN_REFINE_AZISE_INDEX : return HT_REFINE_MAIN_WARNING[1][iRefineLevel-1];
		// 수라파
		case HT_MAIN_REFINE_SURAPA_INDEX : return HT_REFINE_MAIN_WARNING[2][iRefineLevel-1];
		// 디파 일라
		case HT_MAIN_REFINE_DIPAILLA_INDEX : return HT_REFINE_MAIN_WARNING[3][iRefineLevel-1];
		// 프라자티		
		case HT_MAIN_REFINE_PRAJATI_INDEX : return HT_REFINE_MAIN_WARNING[4][iRefineLevel-1];
		// 삼파드
		case HT_MAIN_REFINE_SAMPAD_INDEX : return HT_REFINE_MAIN_WARNING[5][iRefineLevel-1];
		// 자드
		case HT_MAIN_REFINE_ZARD_INDEX : return HT_REFINE_MAIN_WARNING[6][iRefineLevel-1];
		case 6507: return 11;
		case 6556: return 6;
		default : break;
	}

	return -1;
}

//-------------- 보조재료가 첨가 가능한 것인지 검사한다 ----------------//
// 첨가 불가능한 재료가 있을 경우 그 재료의 이름을 strName에 반환한다.
HTint CHTNPCControl::HT_nNPCControl_CheckAidItemCondition(CHTString& strName)
{
	// 보조제련 아이템 인덱스 얻기 
	DWORD dwRefineIndex2 = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[1] );

	// 제련할 아이템 인덱스
	DWORD dwWorkIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(m_dwWorkItem);
	if( dwWorkIndex == 0 )
		return ECONOMY_ADDITEM_ERR_ITEMINDEX;

	// 첨가할 아이템의 인덱스
	DWORD dwRefineIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[0] );
	if( dwRefineIndex == 0 )
		return ECONOMY_ADDITEM_ERR_ITEMINDEX;

	// 아이템 제련 레벨
	if( CHTParamIDCheck::HT_bIsItemRefineMain( dwRefineIndex ) ) // 강화제련
	{
		HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel(m_dwWorkItem);

		if( byLevel >= MAX_REFINE_MAIN_LEVEL )
			return ECONOMY_ADDITEM_ERR_MAIN_OVER;	// error

		// 강화 제련 단계에 따른 성공확률 검사
		HTint iWarning = HT_iNPCControl_GetMainRefineWarning( byLevel+1, dwRefineIndex );
		if( iWarning == -1 || iWarning == HT_REFINE_WARNING1 )
			return ECONOMY_ADDITEM_ERR_CANNOT;	// error
	}
	else if( CHTParamIDCheck::HT_bIsItemRefineSub( dwRefineIndex )) // 주술제련
	{
		HTint iAttriRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( m_dwWorkItem );

		if( dwRefineIndex2 == 6551 || dwRefineIndex2 == 6556 )	// 자드를 주술 제련에 사용했다면 에러메시지 출력하여 사용하지 못하게 한다.
		{
			return ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM;	// error
		}

		// 주술제련 초기화 아이템
		if( dwRefineIndex == HT_INDEX_INIT_SUB_REFINE )
		{
			if( iAttriRefineLevel <= 0 ) 
				return ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM; // error : 첨가 불가능
			else
				return ECONOMY_ADDITEM_ERR_NONE;	// 에러 없음
		}
		else if( iAttriRefineLevel >= MAX_REFINE_SUB_LEVEL )
		{

			if (dwRefineIndex2 != 6555) 
			{
				// 만약 다음과 같은 아이템의 경우라면 10레벨이 넘더라도 진행한다.
				switch (dwRefineIndex)
				{
					case 6624:	//타루 라가마니
					case 6625:	//타루 닐라마니
					case 6626:	//타루 비사잔
					case 6627:	//타루 루바티
					case 6628:	//타루 옴 얀트라
					case 6629:	//타루 마니푸라
					case 6630:	//타루 비슈다
					case 6631:	//타루 아나하타
					case 6632:	//타루 아즈나
						//return ECONOMY_ADDITEM_ERR_NONE;	// 에러 없음
						break;

					default:
						return ECONOMY_ADDITEM_ERR_SUB_OVER;	// error
						break;
				}
			}
		}
	}

	HTbool bCheck = HT_TRUE;

	// 첨가할 아이템의 첨가 가능 아이템 정보
	HTint iRefinableType = 0;
	if( g_pParamMgr->HT_bGetItemRefinableItemType( dwRefineIndex, &iRefinableType ) == false || iRefinableType <= 0 )
		return ECONOMY_ADDITEM_ERR_ITEMINDEX;
	
	// 무기
	if( CHTParamIDCheck::HT_bIsItemWeapon( dwWorkIndex ) )
	{
		// 한 손 무기
		if( CHTParamIDCheck::HT_bIsItemWeaponOneHand( dwWorkIndex )
								&& !BIT_AND( _REFINE_WEPON_ONEHAND, iRefinableType )  )
			bCheck = HT_FALSE;	// 첨가 불가능
		// 두 손 무기
		if( ( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( dwWorkIndex ) 
												|| CHTParamIDCheck::HT_bIsItemWeaponThrow( dwWorkIndex ) )
								&& !BIT_AND( _REFINE_WEPON_TWOHAND, iRefinableType )  )
			bCheck = HT_FALSE;	// 첨가 불가능
	}
	// 방어구
	else if( CHTParamIDCheck::HT_bIsItemDefence( dwWorkIndex ) )
	{
		// 의복	
		if( CHTParamIDCheck::HT_bIsItemDefenceArmor( dwWorkIndex ) 
								&& !BIT_AND( _REFINE_DEFENCE_ARMOR, iRefinableType ) )					
			bCheck = HT_FALSE;	// 첨가 불가능
		// 방패
		if( CHTParamIDCheck::HT_bIsItemDefenceShield( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_SHIELD, iRefinableType ) )	
			bCheck = HT_FALSE;	// 첨가 불가능
		// 허리띠
		if( CHTParamIDCheck::HT_bIsItemDefenceBelt( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_BELT, iRefinableType ) )		
			bCheck = HT_FALSE;	// 첨가 불가능
		// 신발
		if( CHTParamIDCheck::HT_bIsItemDefenceShoes( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_SHOES, iRefinableType ) )	
			bCheck = HT_FALSE;	// 첨가 불가능
		// 모자
		if( CHTParamIDCheck::HT_bIsItemDefenceHelmet( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_HELMET, iRefinableType ) )	
			bCheck = HT_FALSE;	// 첨가 불가능
		// 바지
		if( CHTParamIDCheck::HT_bIsItemDefencePants( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_PANTS, iRefinableType ) )	
			bCheck = HT_FALSE;	// 첨가 불가능
		// 장갑
		if( CHTParamIDCheck::HT_bIsItemDefenceGloves( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_GLOVES, iRefinableType ) )	
			bCheck = HT_FALSE;	// 첨가 불가능
		// 부적 아이템은 모든 방어구와 같은 제련템을 사용할 수 있지만 다음과 같은 목걸이 전용 제련템은 사용 불가
		if( CHTParamIDCheck::HT_bIsItemCharm( dwWorkIndex ))
		{
			switch (dwRefineIndex)
			{
				case 6620:	// 목걸이 전용 제련템
				case 6621:	
				case 6622:	
				case 6623:	
				case 6633:
				case 6634:
				case 6635:
				case 6636:
					bCheck = HT_FALSE;	// 첨가 불가능
					break;
			}
		}
	}
	// 액세서리
	else
	{
		// 팔찌
		if( CHTParamIDCheck::HT_bIsItemAccessoryBracelet( dwWorkIndex )	
								&& !BIT_AND( _REFINE_ACCESSORY_BRACELET, iRefinableType ) )	
			bCheck = HT_FALSE;	// 첨가 불가능
		// 귀걸이
		if( CHTParamIDCheck::HT_bIsItemAccessoryEarring( dwWorkIndex )
								&& !BIT_AND( _REFINE_ACCESSORY_EARRING, iRefinableType ) )	
			bCheck = HT_FALSE;	// 첨가 불가능
		// 목걸이
		if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace( dwWorkIndex )
								&& !BIT_AND( _REFINE_ACCESSORY_NECKLACE, iRefinableType ) )	
			bCheck = HT_FALSE;	// 첨가 불가능
		// 반지
		if( CHTParamIDCheck::HT_bIsItemAccessoryRing( dwWorkIndex )
								&& !BIT_AND( _REFINE_ACCESSORY_RING, iRefinableType ) )		
			bCheck = HT_FALSE;	// 첨가 불가능
	}
	
	// 비카리 사용시 다음과 같은 제련재료와만 함께 사용 할 수 있음.
	if (dwRefineIndex2 == 6555) 
	{
		// 만약 다음과 같은 아이템만 제련 가능 (단, 목걸이는 제외)
		if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace( dwWorkIndex ) ||
			CHTParamIDCheck::HT_bIsItemAccessoryEarring( dwWorkIndex ) ||
			CHTParamIDCheck::HT_bIsItemAccessoryBracelet( dwWorkIndex )	||
			CHTParamIDCheck::HT_bIsItemAccessoryRing( dwWorkIndex ))	
		{
			return ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM;	// error
		}

		if (bCheck == false)
		{
			switch (dwRefineIndex)
			{
				case 6601:	//라가마니
				case 6602:	//닐라마니
				case 6603:	//비사잔
				case 6604:	//루바티
				case 6606:	//마니푸라
				case 6607:	//비슈다
				case 6608:	//아나하타
				case 6609:	//아즈나
					bCheck = true;
					break;

				default:
					return ECONOMY_ADDITEM_ERR_SUB_OVER;	// error
					break;
			}
		}
		else
		{
			m_bMessage_Error = HT_TRUE;	// 에러 있음
			//HT_vNPCControl_SetMessage( eMsgRefineErr2 );
			return ECONOMY_ADDITEM_ERR_NEEDNOT;
		}
	}

	if( bCheck == HT_FALSE )	// 첨가 불가능한 보조재료가 있음
	{
		// 첨가 불가능한 재료의 이름을 저장
		if( g_pParamMgr->HT_bGetItemName( dwRefineIndex, &strName ) == false )
			strName.HT_hrCleanUp();
		return ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM;
	}

	return ECONOMY_ADDITEM_ERR_NONE;	// 에러 없음
}

//----------수리/해체---------//
HTvoid CHTNPCControl::HT_vNPCControl_FixDisjoint_LButtonClick( DWORD dwItemKeyID )
{
	HTshort sType = g_cItemSystem->HT_sItemSystem_GetItemType(dwItemKeyID);

	HTbool res = HT_TRUE;
	// 수리가 가능한 아이템인지 속성과 현재 NPC를 검사
	// 유배지의 NPC는 체크하지 않음
	if( m_iResent == NPC_RESENT_FIX )
		res = HT_bNPCControl_CheckItemAttriForFixDisjoint(dwItemKeyID);

	if( m_iResent == NPC_RESENT_DISJOINT || m_iResent == NPC_RESENT_ITEM_LIST )
	{
		// 유료화 아이템인지 검사하여 유료화 아이템은 판매불가임을 알림 (유료 아이템 판매 금지) 선영범 2004. 9. 16
		HTint iCash = 0;
		HTint iIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(dwItemKeyID);
		if (iIndex <= 0 || g_pParamMgr->HT_bGetItemCash( iIndex, &iCash ) == false)
			return;
		if (iCash > 0) res = HT_FALSE;
	}

	m_dwFixDisjointKeyID = dwItemKeyID;

	if(m_iResent == NPC_RESENT_FIX)
	{
		if(res == HT_FALSE)
		{
			// 이곳에서 수리할 수 없는 아이템입니다.
			HT_vNPCControl_SetMessage( eMsgItemRepairDoNot );

			m_bMessage_Error = HT_TRUE;
			// 완료(에러)창
			//m_byMessageWin = NPC_MESSAGE_NONE;
			g_cUINPCWindow->m_MessageBoxNo = -1;
			g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 0);
		}
		else
		{
			// 수리가 필요한 아이템인지 검사
			HTbool bNeed = g_cItemSystem->HT_bItemSystem_CheckNeedFix( dwItemKeyID );
			// 내구도가 닳았을 경우
			if( bNeed == HT_TRUE )
				HT_vNetWork_CSP_REQ_ITEM_REPAIR();
			else
			{
				// 수리할 필요가 없는 아이템입니다.
				HT_vNPCControl_SetMessage( eMsgItemRepairNeedNot );
				// 시스템 창에 표시
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
			}
		}
	}
	else if( m_iResent == NPC_RESENT_DISJOINT || m_iResent == NPC_RESENT_ITEM_LIST )
	{
		if(res == HT_FALSE)
		{
			// 이곳에서 판매할 수 없는 아이템입니다.
			HT_vNPCControl_SetMessage( eMsgItemSellDoNot );

			m_bMessage_Error = HT_TRUE;
			m_byMessageWin = NPC_MESSAGE_COMPLETE;
			g_cUIMerchantWindow->m_MessageCode = 1;
			g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, m_szMessage, 0);
		}	
		else
		{
			// 해체할 것인지 재확인 메세지 띄운다
			// 아이템을 판매 하시겠습니까?
			HT_vNPCControl_SetMessage( eMsgItemSellQuestionItem );

			m_bMessage_Error = HT_FALSE;
			m_byMessageWin = NPC_MESSAGE_CONFIRM;
			g_cUIMerchantWindow->m_MessageCode = 5;
			g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, m_szMessage, 0);
		}
	}
}

// 현재 NPC에서 수리가 가능한 아이템인지 검사
HTbool CHTNPCControl::HT_bNPCControl_CheckItemAttriForFixDisjoint(DWORD dwItemKeyID)
{
	HTbool res = HT_TRUE;
	DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwIndex == 0 )
		return HT_FALSE;

	if (g_wResentZoneServerID == 17 || g_wResentZoneServerID == 12)
		return HT_TRUE;

	// 회복약, 소모성 아이템, 재료 => 수리 필요 없음
	if( CHTParamIDCheck::HT_bIsItemRefine( dwIndex ) 
			|| CHTParamIDCheck::HT_bIsItemUsable( dwIndex ) || CHTParamIDCheck::HT_bIsItemCollect( dwIndex ) )
		res = HT_FALSE;
	// 무기
	else if( g_wResentZoneServerID != ZONE_JINA3RD
				&& m_iEconomy_NPC == eEconomy_Item_Sword && !CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) ) 
			res = HT_FALSE;

	// 방어구 : 예외 - 부반의 작은 칼칸(수리 퀘스트 아이템)
	else if( g_wResentZoneServerID != ZONE_JINA3RD
				&& m_iEconomy_NPC == eEconomy_Item_Armor && 
		( dwIndex != HT_INDEX_REPAIR_QUEST_ITEM && !CHTParamIDCheck::HT_bIsItemDefence( dwIndex ) ) ) 
		res = HT_FALSE;
	// 액세서리 상인
	else if( g_wResentZoneServerID != ZONE_JINA3RD
				&& m_iEconomy_NPC == eEconomy_Item_Bracelet && !CHTParamIDCheck::HT_bIsItemAccessory( dwIndex ) ) 
	{
		if (g_wResentZoneServerID != 16)
			res = HT_FALSE;
	}

	return res;
}

//---------- 인벤토리 창 팝업 : 제조/수리/해체를 선택했을때  -----------//
HTvoid CHTNPCControl::HT_vNPCControl_PopUpInventory(HTint nWinIndex)
{  
	if( _DIALOG_EQUPINVENTORY == nWinIndex)
	{
		// 인벤토리 창 열기
		if( !g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) )
			g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
	}
	else if( _DIALOG_CHARINFO == nWinIndex )
	{
		// 상태창 열기
		if( !g_cUIManager->HT_isShowWindow( _DIALOG_STATUS ) )
			g_cStatus->HT_vStatus_ActiveSw();
	}
}

//----------현재 마우스의 위치가 리스트에 있는 아이템 위에 있는지검사-----------//
HTint CHTNPCControl::HT_nNPCControl_ItemListMouseCheck_OnItem( HTint nCol, HTint nRow)
{
	if(m_iResent == NPC_RESENT_ITEM_LIST)
	{
		// 선택된 아이템 정보를 찾기위해 이동
		ECONOMY_ITEM_INFO* pTemp = m_Economy_List[m_iEconomy_Resent_Item - m_iEconomy_NPC ].pInfoHead;
		while(pTemp != NULL)
		{
			if(pTemp->byWinIndex == m_byEconomy_Resent_WinIndex)
			{
				if(pTemp->iXpos <= nCol && nCol < pTemp->iXpos+pTemp->iWidth && 
									pTemp->iYpos <= nRow && nRow < pTemp->iYpos+pTemp->iLength )
				{
					return pTemp->iIndex;
				}
			}	// end of if(pTemp->byWinIndex == m_byEconomy_Resent_WinIndex)
			pTemp = pTemp->pNext;
		}	// end of while(pTemp != NULL)
	}
	
	return 0;
}

#define HT_CHARGE_BUY_DISCOUNT_RATE		20.0f // 유료화 아이템 할인율
#define HT_CHARGE_BUY_DISCOUNT_RATE2	10.0f // 유료화 아이템 할인율
// 유료화 아이템의 구입 가격 계산
HTint CHTNPCControl::HT_iNPCControl_CalPurchasingPriceForChargeItem( HTint iItemIndex, HTint iCount )
{
	// 유료화 아이템인지 검사
	HTint iCash = 0;
	if( g_pParamMgr->HT_bGetItemCash( iItemIndex, &iCash ) == false || iCash <= 0 )
		return -1;

	// 먼저 할인율이 적용되지 않은 순수 갯수 * 가격 계산
	double iTotalPrice = iCash * iCount;

	// 할인 가능한 갯수를 구함
	HTint iDiscountNum = HT_iNPCControl_GetDiscountNumForChargeItem( iItemIndex );

	switch(g_iInationalType)
	{
	case INATIONALTYPE_KOREA:
	case INATIONALTYPE_JAPEN:
		if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )		// 지속 아이템
		{
			// 개당 가격이 100원 미만일 경우 20개부터 20%할인 적용
			if( iCash < 100 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // 원단위 절사
			
			// 개당 가격이 100원 이상일 경우 10개부터 20%할인 적용
			else if(iCash >= 100 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // 원단위 절사
		}
		else		// 일반 아이템
		{
			// 개당 가격이 100원 이하일 경우 40개부터 20%할인 적용
			if( iCash <= 100 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // 원단위 절사
			
			// 개당 가격이 101~300원 일 경우 20개부터 20%할인 적용
			else if( 100 < iCash && iCash <= 300 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // 원단위 절사
			
			// 개당 가격이 301~600원 일 경우 10개부터 20%할인 적용
			else if( 300 < iCash && iCash <= 600 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // 원단위 절사
			
			// 개당 가격이 601~1000원 일 경우 5개부터 20%할인 적용
			else if( 600 < iCash && iCash <= 1000 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // 원단위 절사
			
			// 개당 가격이 1001원 이상일 경우 3개부터 20%할인 적용
			else if( 1000 < iCash && iCash < 2300 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8);; // 원단위 절사

		}
		break;
	case INATIONALTYPE_CHINA:
		// 지속 아이템
		if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )
		{
			// 개당 가격이 30타니 미만일 경우 20개부터 10%할인 적용
			if( iCash < 30 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.9); // 원단위 절사
			
			// 개당 가격이 30원 이상일 경우 10개부터 20%할인 적용
			else if(iCash >= 30 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // 원단위 절사
		}
		// 일반 아이템
		else
		{
			// 개당 가격이 14원 이하일 경우 40개부터 10%할인 적용
			if( iCash <= 14 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.9); // 원단위 절사
			
			// 개당 가격이 15~30원 일 경우 20개부터 20%할인 적용
			else if( 14 < iCash && iCash <= 30 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // 원단위 절사
			
			// 개당 가격이 31~100원 일 경우 10개부터 20%할인 적용
			else if( 30 < iCash && iCash <= 100 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // 원단위 절사
			
			// 개당 가격이 101원 이상일 경우 3개부터 20%할인 적용
			else if( 100 < iCash && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // 원단위 절사
		}
		break;

	default:
		break;
	}

	return (int)iTotalPrice; // 가격 반환
}

// 유료화 아이템의 최소 구매 개수
HTint CHTNPCControl::HT_iNPCControl_GetMinCountForChargeItem( HTint iItemIndex )
{
	// 유료화 아이템인지 검사
	HTint iCash = 0, iMinCount = 0;
	if( g_pParamMgr->HT_bGetItemCash( iItemIndex, &iCash ) == false || iCash <= 0 )
		return iMinCount;

	switch(g_iInationalType)
	{
	case INATIONALTYPE_KOREA:
	case INATIONALTYPE_JAPEN:
		// 지속 아이템
		if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )
		{
			// 개당 가격이 100원 미만일 경우
			if( iCash < 100 )
				iMinCount = 10; 
			// 개당 가격이 100원 이상일 경우
			else
				iMinCount = 5; 
		}
		// 일반 아이템
		else
		{
			// 개당 가격이 100원 이하일 경우
			if( iCash <= 100 )
				iMinCount = 20; 
			// 개당 가격이 101~300원 일 경우
			else if( 100 < iCash && iCash <= 300 )
				iMinCount = 10; 
			// 개당 가격이 301~600원 일 경우
			else if( 300 < iCash && iCash <= 600 )
				iMinCount = 5; 
			// 개당 가격이 601~1000원 일 경우
			else if( 600 < iCash && iCash <= 1000 )
				iMinCount = 2; 
			// 개당 가격이 1001원 이상일 경우
			else
				iMinCount = 1; 
		}
		break;

	case INATIONALTYPE_CHINA:
		if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )		// 지속 아이템
		{
			iMinCount = 5; 			// 개당 가격이 100원 미만일 경우
		}
		else		// 일반 아이템
		{
			// 개당 가격이 14원 이하일 경우
			if( iCash <= 14 )
				iMinCount = 20; 
			// 개당 가격이 15~30원 일 경우
			else if( 14 < iCash && iCash <= 30 )
				iMinCount = 10; 
			// 개당 가격이 31~100원 일 경우
			else if( 30 < iCash && iCash <= 100 )
				iMinCount = 5; 
			else
				iMinCount = 1; 
		}
		break;

	default:
		break;
	}

	return iMinCount;
}

// 유료화 아이템의 할인적용 구매 개수
HTint CHTNPCControl::HT_iNPCControl_GetDiscountNumForChargeItem( HTint iItemIndex )
{
	// 유료화 아이템인지 검사
	HTint iCash = 0, iCount = 0;
	if( g_pParamMgr->HT_bGetItemCash( iItemIndex, &iCash ) == false || iCash <= 0 )
		return iCount;

	switch (g_iInationalType)
	{
		case INATIONALTYPE_KOREA:
		case INATIONALTYPE_JAPEN:
		{
			// 지속 아이템
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )
			{
				// 개당 가격이 100원 미만일 경우
				if( iCash < 100 )
					iCount = 20; 
				// 개당 가격이 100원 이상일 경우
				else
					iCount = 10; 
			}
			// 일반 아이템
			else
			{
				// 개당 가격이 100원 이하일 경우
				if( iCash <= 100 )
					iCount = 40; 
				// 개당 가격이 101~300원 일 경우
				else if( 100 < iCash && iCash <= 300 )
					iCount = 20; 
				// 개당 가격이 301~600원 일 경우
				else if( 300 < iCash && iCash <= 600 )
					iCount = 10; 
				// 개당 가격이 601~1000원 일 경우
				else if( 600 < iCash && iCash <= 1000 )
					iCount = 5; 
				// 개당 가격이 1001원 이상일 경우
				else
					iCount = 3; 
			}
		}
		break;

		case INATIONALTYPE_CHINA:
		{
			// 지속 아이템
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )
			{
				// 개당 가격이 100원 미만일 경우
				iCount = 10; 
			}
			// 일반 아이템
			else
			{
				// 개당 가격이 14원 이하일 경우
				if( iCash <= 14 )
					iCount = 40; 
				// 개당 가격이 15~30원 일 경우
				else if( 14 < iCash && iCash <= 30 )
					iCount = 20; 
				// 개당 가격이 31~100원 일 경우
				else if( 30 < iCash && iCash <= 100 )
					iCount = 10; 
				else
					iCount = 3; 
			}
		}
		break;

		default:
			break;
	}
	
	return iCount;
}

//----------마우스 포인트가 위치한 아이템의 제조 정보를 얻어온다.-----------//
HTint CHTNPCControl::HT_nNPCControl_GetItemInfo(HTint iItemIndex, HT_ITEMINFO& vInfo)
{
	// 아이템 정보 얻어오기
	HT_ITEM_DATA* pData = HT_NULL;
	HT_ITEM_EXPANSION_DATA* pExtData = HT_NULL;
	CHTString str;
	
	HTint winSizeX = 0;
	// 아이템 정보 Lock 설정
	if( g_pParamMgr->HT_bLockID( iItemIndex ) == false )
		return winSizeX;

	HTbyte byteOut = 0;
	HTint iOut = 0;
	HTshort sOut = 0;
	CHTString strTemp;

	// 아이템 이름
	if( g_pParamMgr->HT_bGetItemName( &str ) == true )
	{
		vInfo.strName.str = str;
		vInfo.strName.color = g_ColorTable[15];		// white
		winSizeX = vInfo.strName.str.HT_nGetSize();
	}

    // 아이템 설명
	g_pParamMgr->HT_bGetItemDescription( &vInfo.strDescription.str );
	switch (iItemIndex)
	{
		case 7064:	// 프리미엄 꾸러미 아이템들은 세부 설명을 해준다.
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem10, &strTemp, _T("") );	//	"30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 부적의 효과"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7065:
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem11, &strTemp, _T("") );	//	"30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아트만 부적의 효과"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7066:
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem12, &strTemp, _T("") );	//	"30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 및 아트만 부적의 효과"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7067:
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem13, &strTemp, _T("") );	//	"고급 생명의 주문서 1개\n생명의 주문서 20개\n전광판 아이템 10개\n작전 명령서 5개\n이벤트기간에 사용시 이벤트 아이템 지급\n\n30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 및 아트만 부적의 효과\n4. 모든 차크라 15 상승"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7069: // 요술상자 세부설명
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem14, &strTemp, _T("") );	//	"요술램프 1개\n(파미르지역에서 보스몬스터 랜덤 소환가능)\n요술망치 2개\n(장비중인 모든아이템 내구도수리)\n차투랑가 입장권 2개\n(차투랑가로 바로 입장가능)\n이벤트 우타라 암리타 250개 2묶음\n고급 생명의 주문서 2개"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7073:	// 아이원잇
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem20, &strTemp, _T("") );	//	"6만 5천 컬러 LCD / 듀얼 이어폰 '아이원잇 TMP-1000'>>http://www.ioneit.com"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7079:	// 컴리드
			vInfo.strDescription.str.HT_szFormat("COMRADE GeForce 6600 3.3ns그래픽 카드>>>>300MHz RAM DAC>>128MB RAM SPEED 400MHz 3.3ns>>DVI-1 듀얼 디스플레이 지원>>보증기간: 2년>>>>대용량 저발열의 고성능 쿨러, S-Video 케이블, 한글설명서>>>>㈜ 마이크로사운드>>http://www.microsound.co.kr>>라훌에서 등록가능");
			break;
		case 6555: // 비카리
			vInfo.strDescription.str.HT_szFormat("- 주술제련 아이템의 제한부위 해제\n- 제련시 기존의 속성은 초기화되며\n     첨가된 제련재료의 속성을 부여\n\n- 모든 무기, 방어구에 첨가 가능");
			break;
	}

	if( vInfo.strDescription.str == HT_INFO_ITEM_DESCRIPT_NULL )
		vInfo.strDescription.str.HT_hrCleanUp();
	else
		vInfo.strDescription.color = g_ColorTable[16]; //light grey

	
	// 꾸러미 아이템의 경우는 X사이즈를 최대한 넓힌다.
	if(iItemIndex >= 7064 && iItemIndex <= 7067 || iItemIndex == 7069 || iItemIndex == 7079 || iItemIndex == 6555)
	{
		winSizeX = 40;
		vInfo.strName.color = g_ColorTable[17];		// white
		vInfo.strDescription.color = g_ColorTable[15]; //light grey
	}


	//루피아
	HTbool bRes = HT_FALSE;
	if( CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex) ) // 프리미엄 아이템 상점 npc의 경우
	{
		bRes = g_pParamMgr->HT_bGetItemCash( &iOut );
	
		HT_vNPCControl_SetMessage( eMsgItemInfoPrice3 ); // %s 캐쉬
	}
	else
	{
		bRes = g_pParamMgr->HT_bGetItemRupiah( &iOut );

		HT_vNPCControl_SetMessage( eMsgItemInfoPrice2 ); // %s 루피아
		// 주신전에서는 물품 가격이 30% 더해진다
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
			iOut = HTint(iOut * HT_ITEM_MAKE_MONEY_PENALTY);

		if (m_iNPCIndex == 1302)	// 비류성 오다 상인의 경우 적용된 세율에 따라 가격이 변한다.
		{
			HTbyte byteTex = g_pSiege->HT_bySiege_GetMoneyRate();
			double dTex;

			if (byteTex == 0) { dTex = 0;}
			else { dTex = (double)iOut * (double)byteTex/100.0f; }
			iOut += int(dTex);
		}
	}
	if( bRes && iOut > 0 )	
	{
		pData = new HT_ITEM_DATA;
		pData->color = HT_COLOR( 1.0f, 0.96f, 0.6f, 1.0f);	// yellow
		
		CHTString szMoney = g_cUIManager->HT_strSetRestMark( iOut ); // 쉼표 처리
		pData->str.HT_szFormat( m_szMessage.HT_szGetString(), szMoney.HT_szGetString() );

		vInfo.vSourceStr.push_back(pData);
		winSizeX = max(winSizeX, pData->str.HT_nGetSize());
	}
	if( CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex) ) // 프리미엄 아이템 상점 npc의 경우
	{
		// 최소 구입 개수
		HTint iMinCount = HT_iNPCControl_GetMinCountForChargeItem( iItemIndex );
		if( iMinCount > 1 )
		{
			pData = new HT_ITEM_DATA;
			pData->color = HT_COLOR( 1.0f, 0.96f, 0.6f, 1.0f);	// yellow
			
			HT_vNPCControl_SetMessage( eMsgPremiumInfoBuyMinCount ); // 최소 %d개 구입
			pData->str.HT_szFormat( m_szMessage.HT_szGetString(), iMinCount );

			vInfo.vSourceStr.push_back(pData);
			winSizeX = max(winSizeX, pData->str.HT_nGetSize());
		}

		if (iOut < 2300 && g_iInationalType == INATIONALTYPE_KOREA ||  g_iInationalType == INATIONALTYPE_CHINA 
			|| iOut < 2300 && g_iInationalType == INATIONALTYPE_JAPEN)
		{
			// 할인적용 개수
			pData = new HT_ITEM_DATA;
			pData->color = HT_COLOR( 1.0f, 0.96f, 0.6f, 1.0f);	// yellow
			
			HT_vNPCControl_SetMessage( eMsgPremiumInfoBuyDiscount ); // %d개 구입 시 %d%% 할인
			HTint iDiscountNum = HT_iNPCControl_GetDiscountNumForChargeItem( iItemIndex );
			// 2004.09.09 현재 할인율이 일정하게 20%로 적용되고 있음.

			HTfloat Rate = 20.0f;
			
			if( g_iInationalType == INATIONALTYPE_CHINA )
			{
				// 중국의 경우 처리
				if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )
				{
					if (iOut < 30)
						Rate = 10.0f;
				}
				else
				{
					if (iMinCount == 20)
						Rate = 10.0f;
				}
			}

			pData->str.HT_szFormat( m_szMessage.HT_szGetString(), iDiscountNum, HTint(Rate) );

			vInfo.vSourceStr.push_back(pData);
			winSizeX = max(winSizeX, pData->str.HT_nGetSize());
		}
	}

	// 중첩 최대 개수
	//if( g_pParamMgr->HT_bGetItemMaxCount( &byteOut ) && byteOut > 1 )
	//{
	//	pExtData = new HT_ITEM_EXPANSION_DATA;
	//	ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
	//	pExtData->basic.color = g_ColorTable[16]; //light grey
	//	//pExtData->basic.str.HT_szFormat("최대 구입 개수 %d", byteOut );	
	//	HT_vNPCControl_SetMessage( eMsgItemInfoMaxPackCount );
	//	pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), byteOut );

	//	vInfo.vAttributeStr.push_back(pExtData);
	//	winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize() );
	//}

	HTint iParam1 = 0, iParam2 = 0, iFunction = 0;
	//-----착용제한사항------//
	if( g_pParamMgr->HT_bGetItemLimitTrimuriti( &iOut ) == true && iOut > 0 )
	{
		HTRESULT trimuriti = HT_FALSE;
		str.HT_hrCleanUp();

		pData = new HT_ITEM_DATA;
		if( BIT_AND( TRIMURITI_BRAHMA, iOut ) )
		{
			//str = "브라흐마"; 
			HT_vNPCControl_SetMessage( eMsgCommonTrimuritiBrahma );
			pData->str = m_szMessage;
			trimuriti = HT_TRUE;
		}
		if( BIT_AND( TRIMURITI_VISHNU, iOut ) )
		{
			if(trimuriti) //str += ", 비슈누";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTrimuritiVishunu );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str = "비슈누";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTrimuritiVishunu );
				pData->str = m_szMessage;
			}
			trimuriti = HT_TRUE;
		}
		if( BIT_AND( TRIMURITI_SIVA, iOut ) )
		{
			if(trimuriti) //str += ", 시바";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTrimuritiSiva );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "시바";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTrimuritiSiva );
				pData->str = m_szMessage;
			}
			trimuriti = HT_TRUE;
		}

		//str += " 전용";
		HT_vNPCControl_SetMessage( eMsgItemInfoPrivateUse );
		pData->str = pData->str + _T(" ") + m_szMessage;

		// 주신을 선택하지 않은 경우 착용 못함
		if( BIT_AND( g_oMainCharacterInfo.byTrimuriti, iOut ) )
			pData->color = g_ColorTable[16]; //light grey
		else 
			pData->color = g_ColorTable[11];	//red

		vInfo.vLimitStr.push_back(pData);
		winSizeX = max(winSizeX, pData->str.HT_nGetSize());
	}
	if( g_pParamMgr->HT_bGetItemLimitTribe( &iOut ) == true && iOut > 0)		// 종족제한
	{
		HTRESULT tribe = HT_FALSE;
		str.HT_hrCleanUp();

		pData = new HT_ITEM_DATA;
		if( BIT_AND( TRIBE_NAGA, iOut ) )
		{
			//str = "나가"; 
			HT_vNPCControl_SetMessage( eMsgCommonTribeNaga );
			pData->str = m_szMessage;
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_ASURA, iOut ) )
		{
			if(tribe) //str += ", 아수라";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeAsura );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str = "아수라";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeAsura );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_YAKSA, iOut ) )
		{
			if(tribe) //str += ", 야크사";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeYaksha );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "야크사";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeYaksha );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_DEVA, iOut ) )
		{
			if(tribe) //str += ", 데바";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeDeva );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "데바";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeDeva );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_KINNARA, iOut ) )
		{
			if(tribe) //str += ", 킨나라";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeKimnara );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "킨나라";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeKimnara );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_RAKSHASA , iOut ) )
		{
			if(tribe) //str += ", 라크샤사";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeRakshasa );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "라크샤사";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeRakshasa );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_GANDHARVA, iOut ) )
		{
			if(tribe) //str += ", 간다르바";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeGandharva );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "간다르바";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeGandharva );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_GARUDA, iOut ) )
		{
			if(tribe) //str += ", 가루다";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeGaruda );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "가루다";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeGaruda );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		
		//str += " 전용";
		HT_vNPCControl_SetMessage( eMsgItemInfoPrivateUse );
		pData->str = pData->str + _T(" ") + m_szMessage;

		if( BIT_AND( g_cMainCharacter->HT_iMainChar_GetTribeServerCode(), iOut ) )
			pData->color = g_ColorTable[16]; //light grey
		else
			pData->color = g_ColorTable[11];	//red

		vInfo.vLimitStr.push_back(pData);
		winSizeX = max(winSizeX, pData->str.HT_nGetSize());
	}
	if( g_pParamMgr->HT_bGetItemLimitLevel( &byteOut ) == true && byteOut > 0 )
	{
		//HTbyte byItemLevel = 0;
		//if( g_pParamMgr->HT_bGetItemLevel( &byItemLevel ) == true )
		{
			pData = new HT_ITEM_DATA;

			//if( byItemLevel <= 5 )
			{
				//pData->str.HT_szFormat("Level %d필요", byteOut);
				HT_vNPCControl_SetMessage( eMsgItemInfoNeedLevel );
				pData->str.HT_szFormat( m_szMessage.HT_szGetString(), byteOut );
			}
			//else
			//	pData->str.HT_szFormat("Level %d권장", byteOut);

			if( g_cStatus->HT_byGetLevel() >= byteOut )
				pData->color = g_ColorTable[16]; //light grey
			else
				pData->color = g_ColorTable[11];	//red

			vInfo.vLimitStr.push_back(pData);
			winSizeX = max(winSizeX, pData->str.HT_nGetSize());
		}
	}
	if( g_pParamMgr->HT_bGetItemLimitMuscleChakra( &sOut ) == true && sOut > 0 )
	{
		pData = new HT_ITEM_DATA;
		//pData->str.HT_szFormat("근육의 차크라 %d", sOut);		// 근육의 차크라
		HT_vNPCControl_SetMessage( eMsgItemInfoMuscleChakra );
		pData->str.HT_szFormat( m_szMessage.HT_szGetString(), sOut );

		if( g_cStatus->HT_nGetPureChakraMuscle() >= sOut )
			pData->color = g_ColorTable[16]; //light grey
		else
			pData->color = g_ColorTable[11];	//red

		vInfo.vLimitStr.push_back(pData);
		winSizeX = max(winSizeX, pData->str.HT_nGetSize());
	}
	if( g_pParamMgr->HT_bGetItemLimitNerveChakra( &sOut ) == true && sOut > 0 )
	{
		pData = new HT_ITEM_DATA;
		//pData->str.HT_szFormat("신경의 차크라 %d", sOut);		// 신경의 차크라
		HT_vNPCControl_SetMessage( eMsgItemInfoNerveChakra );
		pData->str.HT_szFormat( m_szMessage.HT_szGetString(), sOut );

		if( g_cStatus->HT_nGetPureChakraNerve() >= sOut )
			pData->color = g_ColorTable[16]; //light grey
		else
			pData->color = g_ColorTable[11];	//red

		vInfo.vLimitStr.push_back(pData);
		winSizeX = max(winSizeX, pData->str.HT_nGetSize());
	}
	if( g_pParamMgr->HT_bGetItemLimitHeartChakra( &sOut ) == true && sOut > 0 )
	{
		pData = new HT_ITEM_DATA;
		// 심장의 차크라 %d, sOut		// 심장의 차크라
		HT_vNPCControl_SetMessage( eMsgItemInfoHeartChakra );
		pData->str.HT_szFormat( m_szMessage.HT_szGetString(), sOut );

		if( g_cStatus->HT_nGetPureChakraHeart() >= sOut )
			pData->color = g_ColorTable[16]; //light grey
		else
			pData->color = g_ColorTable[11];	//red

		vInfo.vLimitStr.push_back(pData);
		winSizeX = max(winSizeX, pData->str.HT_nGetSize());
	}
	if( g_pParamMgr->HT_bGetItemLimitSoulChakra( &sOut ) == true && sOut > 0 )
	{
		pData = new HT_ITEM_DATA;
		// 정신의 차크라 %d, sOut		// 정신의 차크라
		HT_vNPCControl_SetMessage( eMsgItemInfoSoulChakra );
		pData->str.HT_szFormat( m_szMessage.HT_szGetString(), sOut );

		if( g_cStatus->HT_nGetPureChakraSoul() >= sOut )
			pData->color = g_ColorTable[16]; //light grey
		else
			pData->color = g_ColorTable[11];	//red

		vInfo.vLimitStr.push_back(pData);
		winSizeX = max(winSizeX, pData->str.HT_nGetSize());
	}
	//--------특성---------//
	// 제련시 가능한 아이템 
	if( CHTParamIDCheck::HT_bIsItemRefine(iItemIndex) 
						&& g_pParamMgr->HT_bGetItemRefinableItemType(&iOut) == true && iOut > 0 )
	{
		// 첨가 가능 아이템 분류(Bit Set)
		HTRESULT enable = HT_FALSE;
		HTint nCommaCount = 0;

		str.HT_hrCleanUp();
		HTRESULT type = HT_FALSE;
		
		pExtData = new HT_ITEM_EXPANSION_DATA;
		ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
		// 무기
		if( BIT_AND( _REFINE_WEPON_ONEHAND, iOut ) )
		{
			//str = "한손무기"; 
			HT_vNPCControl_SetMessage( eMsgCommonItemClassOneHand );
			pExtData->basic.str = m_szMessage;
			type = HT_TRUE;
		}
		if( BIT_AND( _REFINE_WEPON_TWOHAND , iOut ) )
		{
			if(type)
			{
				//str +=", 두손무기";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassTwoHand );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "두손무기";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassTwoHand );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		// 방어구
		if( BIT_AND( _REFINE_DEFENCE_ARMOR , iOut ) )// 의복
		{
			if(type)
			{
				//str +=", 의복";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassArmor );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "의복";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassArmor );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_PANTS , iOut ) )// 바지
		{
			if(type)
			{
				//str +=", 바지";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassPants );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "바지";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassPants );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_GLOVES , iOut ) )// 장갑
		{
			if(type)
			{
				//str +=", 장갑";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassGloves );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "장갑";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassGloves );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_SHIELD, iOut ) )	// 방패
		{
			if(type)
			{
				//str +=", 방패";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassShield );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "방패";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassShield );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_BELT, iOut ) )	// 허리띠
		{
			if(type)
			{
				//str +=", 허리띠";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassBelt );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "허리띠";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassBelt );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_SHOES, iOut ) )	// 신발
		{
			if(type)
			{
				//str +=", 신발";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassShoes );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "신발";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassShoes );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_HELMET, iOut ) )	// 모자
		{
			if(type)
			{
				//str +=", 모자";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassHelmet );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "모자";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassHelmet );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		// 액세서리
		if( BIT_AND( _REFINE_ACCESSORY_EARRING, iOut ) )	
		{
			if(type)
			{
				//str +=", 귀걸이";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassEarring );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "귀걸이";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassEarring );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_ACCESSORY_NECKLACE, iOut ) )	
		{
			if(type)
			{
				//str +=", 목걸이";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassNecklace );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "목걸이";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassNecklace );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_ACCESSORY_BRACELET, iOut ) )	
		{
			if(type)
			{
				//str +=", 팔찌";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassBracelet );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "팔찌";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassBracelet );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_ACCESSORY_RING, iOut ) )	
		{
			if(type)
			{
				//str +=", 반지";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassRing );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "반지";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassRing );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
			
		//str += "용";
		HT_vNPCControl_SetMessage( eMsgItemInfoUsable );
		pExtData->basic.str = pExtData->basic.str + _T(" ") + m_szMessage;
		pExtData->basic.color = g_ColorTable[16]; //light grey

		vInfo.vAttributeStr.push_back(pExtData);
		winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize()-(HTint)((HTfloat)nCommaCount/2.0 +0.5));
	}
	// 내구도
	if( g_pParamMgr->HT_bGetItemMaxDurability( &sOut ) == true )
	{
		if( sOut > 0 && sOut != HT_ITEM_INFINITY_DURABILITY ) 
		{
			pExtData = new HT_ITEM_EXPANSION_DATA;
			ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
			
			pExtData->basic.color = g_ColorTable[16]; //light grey

			HTint iMaxDur = sOut/HT_ITEM_DURABILITY_DIVIDING;
			if( sOut % HT_ITEM_DURABILITY_DIVIDING > 0 )
				++iMaxDur; // 올림 처리
			//pExtData->basic.str.HT_szFormat("내구도 %d / %d", iMaxDur, iMaxDur );
			HT_vNPCControl_SetMessage( eMsgItemInfoDurability );
			pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iMaxDur, iMaxDur );
			
			vInfo.vAttributeStr.push_back(pExtData);
			winSizeX = max(winSizeX, (pExtData->basic.str.HT_nGetSize()) );
		}
		// 무기/방어구 중 파괴불가
		else if( sOut == HT_ITEM_INFINITY_DURABILITY && CHTParamIDCheck::HT_bIsItemWeapon( iItemIndex )
							&& CHTParamIDCheck::HT_bIsItemDefence(iItemIndex ) )
		{
			pExtData = new HT_ITEM_EXPANSION_DATA;
			ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			pExtData->basic.color = g_ColorTable[11]; //red
			// 파괴불가
			HT_vNPCControl_SetMessage( eMsgItemInfoUnbreakable );
			pExtData->basic.str = m_szMessage;
			
			vInfo.vAttributeStr.push_back(pExtData);
			winSizeX = max(winSizeX, (pExtData->basic.str.HT_nGetSize()) );
		}
	}
	
	// 예외처리 - 고급아누바바/아누바바의 부적의 경우 Effect를 표시하지 않는다.
	if( iItemIndex == HT_INDEX_DAMAGE_UP || iItemIndex == HT_INDEX_SUPERIOR_DAMAGE_UP
										 || iItemIndex == HT_INDEX_SUPERIOR_DAMAGE_UP2 )
	{
		// 아이템 정보 Lock 해제
		g_pParamMgr->HT_bUnLockID( iItemIndex );
		return winSizeX;
	}
	
	// Effect 1
	if( g_pParamMgr->HT_bGetItemEffect1ID( &iOut ) == true && iOut > 0 )
	{
		str.HT_hrCleanUp();

		g_pParamMgr->HT_bGetItemEffect1Param1( &iParam1 );
		g_pParamMgr->HT_bGetItemEffect1Param2( &iParam2 );
		g_pParamMgr->HT_bGetItemEffect1Function( &iFunction ); 
		if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction ) == HT_TRUE )
		{
			pExtData = new HT_ITEM_EXPANSION_DATA;
			ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			pExtData->basic.color = g_ColorTable[16]; //light grey
			pExtData->basic.str = str;		

			vInfo.vAttributeStr.push_back(pExtData);
			winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

			// 지속시간 - 지속효과 유료화 아이템일 경우 표시하지 않음
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) == false
				&& g_pParamMgr->HT_bGetItemEffect1Duration( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("   (지속시간:%d초)", iOut/HT_ITEM_DURATION_DIVIDING );	
				HT_vNPCControl_SetMessage( eMsgItemInfoDuration );
				pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
		}
	}
	// Effect 2
	if( g_pParamMgr->HT_bGetItemEffect2ID( &iOut ) == true && iOut > 0 )
	{
		str.HT_hrCleanUp();

		g_pParamMgr->HT_bGetItemEffect2Param1( &iParam1 );
		g_pParamMgr->HT_bGetItemEffect2Param2( &iParam2 );
		g_pParamMgr->HT_bGetItemEffect2Function( &iFunction ); 
		if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction ) == HT_TRUE )
		{
			pExtData = new HT_ITEM_EXPANSION_DATA;
			ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			pExtData->basic.color = g_ColorTable[16]; //light grey
			pExtData->basic.str = str;		

			vInfo.vAttributeStr.push_back(pExtData);
			winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

			// 지속시간 - 지속효과 유료화 아이템일 경우 표시하지 않음
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) == false
				&& g_pParamMgr->HT_bGetItemEffect2Duration( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("   (지속시간:%d초)", iOut/HT_ITEM_DURATION_DIVIDING );		
				HT_vNPCControl_SetMessage( eMsgItemInfoDuration );
				pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
		}
	}
	// Effect 3
	if( g_pParamMgr->HT_bGetItemEffect3ID( &iOut ) == true && iOut > 0 )
	{
		str.HT_hrCleanUp();

		g_pParamMgr->HT_bGetItemEffect3Param1( &iParam1 );
		g_pParamMgr->HT_bGetItemEffect3Param2( &iParam2 );
		g_pParamMgr->HT_bGetItemEffect3Function( &iFunction ); 

		if( iItemIndex == 6601 || // 다음의 아이템은 세번째 특성 출력무시 (라가마니, 닐라마니, 비사잔, 루바티)
			iItemIndex == 6602 || 
			iItemIndex == 6603 ||
			iItemIndex == 6604 ||
			iItemIndex == 6606 || // 추가 : 2006. 2. 17 (목걸이 제련석 추가 : 마니푸라, 비슈다, 아나하타, 아즈나 )
			iItemIndex == 6607 ||
			iItemIndex == 6608 ||
			iItemIndex == 6609 )
		{
		}
		else if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction ) == HT_TRUE )
		{
			pExtData = new HT_ITEM_EXPANSION_DATA;
			ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			pExtData->basic.color = g_ColorTable[16]; //light grey
			pExtData->basic.str = str;		

			vInfo.vAttributeStr.push_back(pExtData);
			winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

			// 지속시간 - 지속효과 유료화 아이템일 경우 표시하지 않음
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) == false
				&& g_pParamMgr->HT_bGetItemEffect3Duration( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("   (지속시간:%d초)", iOut/HT_ITEM_DURATION_DIVIDING );		
				HT_vNPCControl_SetMessage( eMsgItemInfoDuration );
				pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
		}
	}
	// Effect 4
	if( g_pParamMgr->HT_bGetItemEffect4ID( &iOut ) == true && iOut > 0 )
	{
		str.HT_hrCleanUp();

		g_pParamMgr->HT_bGetItemEffect4Param1( &iParam1 );
		g_pParamMgr->HT_bGetItemEffect4Param2( &iParam2 );
		g_pParamMgr->HT_bGetItemEffect4Function( &iFunction ); 
		if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction ) == HT_TRUE )
		{
			pExtData = new HT_ITEM_EXPANSION_DATA;
			ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			pExtData->basic.color = g_ColorTable[16]; //light grey
			pExtData->basic.str = str;		

			vInfo.vAttributeStr.push_back(pExtData);
			winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

			// 지속시간 - 지속효과 유료화 아이템일 경우 표시하지 않음
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) == false
				&& g_pParamMgr->HT_bGetItemEffect4Duration( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("   (지속시간:%d초)", iOut/HT_ITEM_DURATION_DIVIDING );			
				HT_vNPCControl_SetMessage( eMsgItemInfoDuration );
				pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
		}
	}
	// Effect 5
	if( g_pParamMgr->HT_bGetItemEffect5ID( &iOut ) == true && iOut > 0 )
	{
		str.HT_hrCleanUp();

		g_pParamMgr->HT_bGetItemEffect5Param1( &iParam1 );
		g_pParamMgr->HT_bGetItemEffect5Param2( &iParam2 );
		g_pParamMgr->HT_bGetItemEffect5Function( &iFunction ); 
		if( g_cSkillSystem->HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction ) == HT_TRUE )
		{
			pExtData = new HT_ITEM_EXPANSION_DATA;
			ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			pExtData->basic.color = g_ColorTable[16]; //light grey
			pExtData->basic.str = str;		

			vInfo.vAttributeStr.push_back(pExtData);
			winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

			// 지속시간 - 지속효과 유료화 아이템일 경우 표시하지 않음
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) == false
				&& g_pParamMgr->HT_bGetItemEffect5Duration( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("   (지속시간:%d초)", iOut/HT_ITEM_DURATION_DIVIDING );		
				HT_vNPCControl_SetMessage( eMsgItemInfoDuration );
				pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
		}
	}
	// 공격 속도
	if( CHTParamIDCheck::HT_bIsItemWeapon( iItemIndex ) )
	{
		/* 제련이나 추가된 속성에 의해서 공격속도 변경됐는지 검사해야함 2003.12.10 선미 */
		if( g_pParamMgr->HT_bGetItemCoolDownTime( &iOut ) == true && iOut > 0 )
		{
			pExtData = new HT_ITEM_EXPANSION_DATA;
			ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
			
			HTint iSpeed = g_cItemSystem->HT_iItemSystem_CheckItemSpeedRange( iOut );
			pExtData->basic.color = g_ColorTable[16]; //light grey
			switch( iSpeed )
			{
				case HT_ITEM_SPEED_VERY_FAST : // 공격 속도 매우 빠름	
					HT_vNPCControl_SetMessage( eMsgItemInfoAttackSpeedVeryHigh );	break;
				case HT_ITEM_SPEED_FAST		 : // 공격 속도 빠름
					HT_vNPCControl_SetMessage( eMsgItemInfoAttackSpeedHigh );		break;
				case HT_ITEM_SPEED_NORMAL	 : // 공격 속도 보통		
					HT_vNPCControl_SetMessage( eMsgItemInfoAttackSpeedNormal );		break;
				case HT_ITEM_SPEED_SLOW		 : // 공격 속도 느림	
					HT_vNPCControl_SetMessage( eMsgItemInfoAttackSpeedLow );		break;
				case HT_ITEM_SPEED_VERY_SLOW : // 공격 속도 매우 느림	
					HT_vNPCControl_SetMessage( eMsgItemInfoAttackSpeedVeryLow );	break;
				default: pExtData->basic.str.HT_hrCleanUp(); break;
			}
			pExtData->basic.str = m_szMessage; 
			vInfo.vAttributeStr.push_back(pExtData);
			winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
		}
	}
	// 사정거리
	//if( g_pParamMgr->HT_bGetItemRange( &byteOut ) && byteOut > 0 )
	//{
	//	pExtData = new HT_ITEM_EXPANSION_DATA;
	//	ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

	//	pExtData->basic.color = g_ColorTable[16]; //light grey
	//	pExtData->basic.str.HT_szFormat("사정거리 %d", byteOut);		

	//	vInfo.vAttributeStr.push_back(pExtData);
	//	winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
	//}
	// 소모 HP
	if( g_pParamMgr->HT_bGetItemCostHP( &iOut ) == true && iOut > 0 )
	{
		pExtData = new HT_ITEM_EXPANSION_DATA;
		ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

		pExtData->basic.color = g_ColorTable[16]; //light grey
		//pExtData->basic.str.HT_szFormat("소모 HP %d", iOut);		
		HT_vNPCControl_SetMessage( eMsgItemInfoCostHP );
		pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iOut);	

		vInfo.vAttributeStr.push_back(pExtData);
		winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
	}
	// 소모 TP
	if( g_pParamMgr->HT_bGetItemCostTP( &iOut ) == true && iOut > 0 )
	{
		pExtData = new HT_ITEM_EXPANSION_DATA;
		ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

		pExtData->basic.color = g_ColorTable[16]; //light grey
		//pExtData->basic.str.HT_szFormat("소모 TP %d", iOut);		
		HT_vNPCControl_SetMessage( eMsgItemInfoCostTP );
		pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iOut);

		vInfo.vAttributeStr.push_back(pExtData);
		winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
	}
	// 소모 Item
	// 소모성 아이템은 소모아이템으로 자기 자신이 들어가 있다.
	if( g_pParamMgr->HT_bGetItemidCostItem( &iOut ) == true && iOut > 0 && iOut != iItemIndex)
	{
		pExtData = new HT_ITEM_EXPANSION_DATA;
		ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

		pExtData->basic.color = g_ColorTable[16]; //light grey
		
		CHTString str;
		g_pParamMgr->HT_bGetItemName( iOut, &str );
		//pExtData->basic.str.HT_szFormat("소모 Item %s", str.HT_szGetString());		
		HT_vNPCControl_SetMessage( eMsgItemInfoCostItem );
		pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), str.HT_szGetString() );

		vInfo.vAttributeStr.push_back(pExtData);
		winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
	}

	// 아이템 정보 Lock 해제
	g_pParamMgr->HT_bUnLockID( iItemIndex );

	return winSizeX;
}
 
// 보조자원 채우기
HTbool CHTNPCControl::HT_bNPCControl_SetAidItemResource( DWORD dwItemKeyID )
{
	m_nEconomy_Work_SubItemKeyID[0] = dwItemKeyID;
	return HT_TRUE;
}

//----------제조창에서 취소한 보조자원 지우기----------//
HTbool CHTNPCControl::HT_bNPCControl_CancelSupportResource( DWORD dwItemKeyID )
{
	for(HTint i=0; i<3; ++i)
		m_nEconomy_Work_SubItemKeyID[i] = 0;
	return HT_FALSE;
}

// 차투랑가 보드의 각 칸의 말 인덱스
#define HT_CTRG_MAX_PIECE		25
int g_iChaturangaPiece[]
= { 7193, 7194, 7195, 7196, 7197, // 4
	7198, 7199, 7200, 7201, 7202, // 9
	7203, 7204, 7205, 7206, 7207, // 14
	7208, 7209, 7210, 7211, 7212, // 19
	7213, 7214, 7215, 7216, 7217  // 24
};

//왕의 상징
#define HT_CTRG_KING		7205
// 각 분대 구성 말의 개수
#define HT_CTRG_SQUAD_TOTAL_PIECE		4
//북쪽 상급 보병의 상징- 우드 페다티 카야
#define HT_CTRG_BOSS_NORTH		7219
#define HT_CTRG_BOSS_NORTH_START		0
//남쪽 상급 보병의 상징 - 바다 페다티 카야
#define HT_CTRG_BOSS_SOUTH		7220
#define HT_CTRG_BOSS_SOUTH_START		4
//상급 기병 - 아스바 카야
#define HT_CTRG_BOSS_CAVALRY	7221
#define HT_CTRG_BOSS_CAVALRY_START		8
//상급 전차 - 라다 카야
#define HT_CTRG_BOSS_TANK		7222
#define HT_CTRG_BOSS_TANK_START			12
//상급 상병 - 가자 카야
#define HT_CTRG_BOSS_CORPORAL	7223
#define HT_CTRG_BOSS_CORPORAL_START		16
//상급 참모 - 만트리 카야
#define HT_CTRG_BOSS_STAFF		7224
#define HT_CTRG_BOSS_STAFF_START		20
// 각 분대 말의 g_iChaturangaPiece에서의 위치 
byte g_byChaturangaSquadPiece[] 
= { 0, 3, 4, 5,		// 우드 페다티 카야
	19, 20, 21, 24, // 바다 페다티 카야
	2, 10, 14, 22,	// 아스바 카야
	1, 9, 15, 23,	// 라다 카야
	6, 8, 16, 18,	// 가자 카야
	7, 11, 13, 17 };// 만트리 카야

// 차투랑가 보드 열기
HTvoid CHTNPCControl::HT_vNPCControl_ActiveChaturangaBoard()
{
	// 차투랑가 말 표시하기
	// 왕의 상징 - 모든 말을 획득했음
	if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CTRG_KING ) > 0 )
	{
	}
	else
	{
		// 북쪽 상급 보병
		HT_vNPCControl_SetChaturangaPiece( eChaturangaNorth );
		// 남쪽 상급 보명
		HT_vNPCControl_SetChaturangaPiece( eChaturangaSouth );
		// 상급 기명
		HT_vNPCControl_SetChaturangaPiece( eChaturangaCavalry );
		// 상급 전차
		HT_vNPCControl_SetChaturangaPiece( eChaturangaTank );
		// 상급 상병
		HT_vNPCControl_SetChaturangaPiece( eChaturangaCorporal );
		// 상급 참모
		HT_vNPCControl_SetChaturangaPiece( eChaturangaStaff );
	}
}

// 차투랑가 보드에 말 표시하기
HTvoid CHTNPCControl::HT_vNPCControl_SetChaturangaPiece( eChaturangaSquad eSquad )
{
	HTint iPieceLoc = 0;
	HTint nXMLID = 0, iItemIndex = 0; 
	HTint i = 0;

	switch( eSquad )
	{
		case eChaturangaNorth :
			iPieceLoc = HT_CTRG_BOSS_NORTH_START;
			iItemIndex = HT_CTRG_BOSS_NORTH;
			break;
		case eChaturangaSouth :
			iPieceLoc = HT_CTRG_BOSS_SOUTH_START;
			iItemIndex = HT_CTRG_BOSS_SOUTH;
			break;
		case eChaturangaCavalry :
			iPieceLoc = HT_CTRG_BOSS_CAVALRY_START;
			iItemIndex = HT_CTRG_BOSS_CAVALRY;
			break;
		case eChaturangaTank :
			iPieceLoc = HT_CTRG_BOSS_TANK_START;
			iItemIndex = HT_CTRG_BOSS_TANK;
			break;
		case eChaturangaCorporal :
			iPieceLoc = HT_CTRG_BOSS_CORPORAL_START;
			iItemIndex = HT_CTRG_BOSS_CORPORAL;
			break;
		case eChaturangaStaff :
			iPieceLoc = HT_CTRG_BOSS_STAFF_START;
			iItemIndex = HT_CTRG_BOSS_STAFF;
			break;
		default :
			return;
	}

	if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( iItemIndex ) > 0 )
	{
		for( i = iPieceLoc; i < iPieceLoc+HT_CTRG_SQUAD_TOTAL_PIECE; ++i )
		{
			iItemIndex = g_iChaturangaPiece[ g_byChaturangaSquadPiece[i] ];
		}
	}
	else
	{
		for( i = iPieceLoc; i < iPieceLoc+HT_CTRG_SQUAD_TOTAL_PIECE; ++i )
		{
			iItemIndex = g_iChaturangaPiece[ g_byChaturangaSquadPiece[i] ];
		}	
	}
}

HTbool CHTNPCControl::HT_bNPCControl_IsItemMake()
{
	if( m_iResent == NPC_RESENT_ITEM_LIST )
		return HT_TRUE;
	else
		return HT_FALSE;
}

HTbool CHTNPCControl::HT_bNPCControl_IsItemWorkActive()
{
	if(m_iResent == NPC_RESENT_REFINE)
		return HT_TRUE;
	else
		return HT_FALSE;
}

HTbool CHTNPCControl::HT_bNPCControl_IsItemFixActive()
{
	if(m_iResent == NPC_RESENT_FIX)
		return HT_TRUE;
	else
		return HT_FALSE;
}

HTbool CHTNPCControl::HT_bNPCControl_IsItemDisjointActive()
{
	if(m_iResent == NPC_RESENT_DISJOINT)
		return HT_TRUE;
	else
		return HT_FALSE;
}

HTbool CHTNPCControl::HT_bNPCControl_IsRegistLotteryActive()
{
	if(m_iResent == NPC_RESENT_REGIST_LOTTERY)
		return HT_TRUE;
	else
		return HT_FALSE;
}

HTvoid CHTNPCControl::HT_vNPCControl_IncreaseChakra(HTint iBtnNo)
{
	// 프로퍼티를 선택
	if( iBtnNo < _CHARINFO_BUTTON_MUSCLE || _CHARINFO_BUTTON_SPIRIT < iBtnNo )
		return;

	CHTString strTemp;
	// 심장 버튼을 클릭시 400 차크라일 경우에는 누르지 못하게 한다. (심장의 차크라 400 제한) 선영범 2004. 10. 25
	HTint iHeart;
	iHeart = g_cStatus->HT_nGetPureChakraHeart();
	if (iBtnNo == 2 && iHeart >= 400)
	{
		HT_g_Script_SetMessage( eMsgChakraCannotUpgrade, &strTemp, _T("") );		//	"차크라 제한에 걸려 차크라를 올릴 수 없습니다."
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
		return;
	}


	// 신경 버튼을 클릭시 350 이상일 경우에는 누르지 못하게 한다. (신경의 차크라 350 제한) 선영범 2005. 5. 27
	HTint iNerve;
	iNerve = g_cStatus->HT_nGetChakraNerve();
	if (g_oMainCharacterInfo.snTribe == 4 || g_oMainCharacterInfo.snTribe == 8)
	if (iBtnNo == 1 && iNerve >= 350)
	{
		HT_g_Script_SetMessage( eMsgChakraCannotUpgrade, &strTemp, _T("") );		//	"차크라 제한에 걸려 차크라를 올릴 수 없습니다."
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
		return;
	}

	m_bySelectPart = iBtnNo;

	// 서버에 요청
	HT_vNetWork_CSP_REQ_Increase_Chakra();
}

HTbool CHTNPCControl::HT_bNPCControl_IsChakraUpStep()
{
	if( m_iResent == NPC_RESENT_CHAKRA )
		return HT_TRUE;
	else
		return HT_FALSE;
}

HTbool CHTNPCControl::HT_bNPCControl_IsBrahmanUpStep()
{
	if( m_iResent == NPC_RESENT_BRAHMAN )
		return HT_TRUE;
	else
		return HT_FALSE;
}

//----------- ESC/X버튼에 의한 NPC인벤토리 제거 --------------//
HTvoid CHTNPCControl::HT_vNPCControl_Inventory_Close()
{
	// 아이템 이동중이었을 경우
	g_cItemControl->HT_vItemControl_ESC_ItemAntiActive(/*_DIALOG_GOODSKEEPING*/);
	// 아이템 언패킹창 닫기
	g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );
	
	m_bMessage_Error = HT_FALSE;	// 에러 없음
	m_iResent = NPC_RESENT_DIALOG;

	// 대화상자 대화 바꾸기
	// 선택문의 마지막에는 선택문이 아닌 다른 입력에 의해 다음 단계로 넘어갈 때 사용하기 위한 값이 있다
	// 0~m_nSelectCount-1 : 선택문, m_nSelectCount : 확인, m_nSelectCount+1 : 취소
	// 마우스 클릭에 따라서 다음 단계로 넘어간다.
	HT_vNPCControl_GetNextStep(m_nSelectCount);
}

//--------메세지 윈도우가 활성화되어있는지----------//
HTbool CHTNPCControl::HT_bNPCControl_IsMessageWinActive()
{
	if(m_byMessageWin == NPC_MESSAGE_NONE)
		return HT_FALSE;
	else
		return HT_TRUE;
}

HTbool CHTNPCControl::HT_bNPCControl_IsCompleteMsgWinActive()
{
	if(m_byMessageWin == NPC_MESSAGE_COMPLETE)
		return HT_TRUE;
	else
		return HT_FALSE;
}

HTbool CHTNPCControl::HT_bNPCControl_IsConfirmMsgWinActive()
{
	if(m_byMessageWin == NPC_MESSAGE_CONFIRM)
		return HT_TRUE;
	else
		return HT_FALSE;
}

HTbool CHTNPCControl::HT_bNPCControl_IsGuilCreateStep()
{
	if( m_iResent == NPC_RESENT_CREATE_GILD )
		return HT_TRUE;
	else
		return HT_FALSE;
}

//-----------현재 시간(해/달이 떠있는 시간)을 얻어온다---------//
HTfloat CHTNPCControl::HT_fNPCControl_GetCurTime()
{
	return g_pEngineHandler->HT_fGetCurrentTimeInAllDay();
}

//////////////////////////////////////////////////////////////////////////
// 네트워크 관련 함수
//////////////////////////////////////////////////////////////////////////
// 아이템 구입
HTvoid CHTNPCControl::HT_vNetWork_CSP_Req_Item_Buy()
{/*
	PS_CSP_REQ_ITEM_BUY info = HT_NULL;
	info = new S_CSP_REQ_ITEM_BUY;
	
	info->snNPCIndex = m_iNPCIndex;
	info->snItemIndex = HTshort(m_dwBuyItem - HT_ITEM_INDEX_START);
	// 구입할 개수
	info->snItemCount = m_iWorkItemCount;	

	// 루피아는 서버가 인벤에서 자동으로 뺀다.
	g_pNetWorkMgr->RequestItemBuy( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemBuy : %d:%d-%d개", 
													info->snNPCIndex, info->snItemIndex, info->snItemCount );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );*/
}
 
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Item_Buy( PS_SCP_RESP_ITEM_BUY info )
{
	g_cUIMerchantWindow->HT_vNetWork_SCP_Resp_Item_Buy(info);
}

// 수리 요구
HTvoid CHTNPCControl::HT_vNetWork_CSP_REQ_ITEM_REPAIR()
{
	PS_CSP_REQ_ITEM_REPAIR info = HT_NULL;
	info = new S_CSP_REQ_ITEM_REPAIR;

	info->snNPCIndex = m_iNPCIndex;	// NPC 인덱스
	
	// 아이템이 위치한 장소와 위치 index
	HT_ITEMSETTING_FLAG sLocRoom;
	sLocRoom.nInventory = sLocRoom.nLocation = -1;
	g_cItemSystem->HT_bItemSystem_GetItemPos( m_dwFixDisjointKeyID, sLocRoom );
	if( sLocRoom.nInventory == -1 || sLocRoom.nLocation == -1 )
	{
		HT_DELETE( info );
		return;
	}

	if( sLocRoom.nLocation == ITEM_LOCATION_NPC )
	{
		info->byPlace =	ITEM_PLACE_CARGO ; 
		info->byIndex = ( sLocRoom.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + sLocRoom.pCellPos.x )
							+ ( sLocRoom.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT );
	}
	else if( sLocRoom.nLocation == ITEM_LOCATION_EQUIP )
	{
		info->byPlace =	ITEM_PLACE_EQUIP ;
		info->byIndex = sLocRoom.nInventory;
	}
	else //if( sLocRoom.nLocation == ITEM_LOCATION_PC )
	{
		info->byPlace =	ITEM_PLACE_INVEN ;
		info->byIndex = ( sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y )
							+ ( sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT );
	}

	g_pNetWorkMgr->RequestItemRepair( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemRepair : %d:(%d:%d)", 
	//												info->snNPCIndex, info->byPlace, info->byIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
} 
 
// 수리 결과
HTvoid CHTNPCControl::HT_vNetWork_SCP_RESP_ITEM_REPAIR( PS_SCP_RESP_ITEM_REPAIR info )
{
	// KeyID 생성
	HTint iKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID);
	m_dwFixDisjointKeyID = iKeyID;

	if( info->byResult == 0x00 )
	{
		m_bMessage_Error = HT_FALSE;	// 에러 없음

		//---------- 시스템창에 아이템 획득 출력 ------------//
		m_iSpendMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney() - info->nMoney;
		if(m_iSpendMoney < 0 )
			m_iSpendMoney = 0;

		if (info->byDummy == 1)	// 루피아 출력
		{
			// %d루피아를 사용해서 %s이(가) 수리되었습니다.
			HT_vNPCControl_SetMessage( eMsgItemRepairSuccess );
		}
		else
		{
			HT_vNPCControl_SetMessage( eMsgItemRepairOK );
		}
		        
		// 돈 갱신
		if(info->nMoney > 0)
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(info->nMoney);
		else
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(0);

		// 수리된 아이템의 내구도를 갱신한다.
		HTshort sMaxDur = g_cItemSystem->HT_sItemSystem_GetMaxDurability( m_dwFixDisjointKeyID );
		if( 0 <= sMaxDur && sMaxDur < HT_ITEM_INFINITY_DURABILITY )	// 무한내구도는 255
			g_cItemSystem->HT_dwItemSystem_SetCurDurability( m_dwFixDisjointKeyID, sMaxDur);

		// 현재 내구도에 따른 수리 표시
		g_cItemSystem->HT_vItemSystem_RenewalDurabilityWarning( );

		// 대화상자 대화 바꾸기
		// 선택문의 마지막에는 선택문이 아닌 다른 입력에 의해 다음 단계로 넘어갈 때 사용하기 위한 값이 있다
		// 0~m_nSelectCount-1 : 선택문, m_nSelectCount : 확인, m_nSelectCount+1 : 취소
		// 마우스 클릭에 따라서 다음 단계로 넘어간다.
		//HT_vNPCControl_GetNextStep(m_nSelectCount);	
	} 
	else 
	{
		// 완료창에 보여줄 메세지
		if( info->byResult == REPLY_ITEM_REPAIR_MONEY_WANT)
            // 수리에 필요한 루피아가 부족합니다. 	
			HT_vNPCControl_SetMessage( eMsgItemCommonMoneyErr );
		else if ( info->byResult == REPLY_ITEM_REPAIR_OUTINDEX )
			// 아이템을 찾을 수 없습니다. 
			HT_vNPCControl_SetMessage( eMsgItemCommonCannotFindInfo );
		else if( info->byResult == REPLY_ITEM_REPAIR_ENOUGH)
			// 수리할 필요가 없는 아이템입니다. 
			HT_vNPCControl_SetMessage( eMsgItemRepairNeedNot );
		else
			// 아이템을 수리하지 못했습니다. 
			HT_vNPCControl_SetMessage( eMsgItemRepairFail );

		m_bMessage_Error = HT_TRUE;	// 에러 있음
		g_cUINPCWindow->m_MessageBoxNo = -1;
		// 완료창 띄움
		//m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUIManager->HT_MessageBox( _DIALOG_NPCWINDOW, m_szMessage, 0);	// 메세지
	}
	// 시스템 창에 표시
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
}

// 해체 요구
HTvoid CHTNPCControl::HT_vNetWork_CSP_Req_Item_Sell()
{
	g_cUIMerchantWindow->HT_vNetWork_CSP_Req_Item_Sell();
	/*
	PS_CSP_REQ_ITEM_SELL info = HT_NULL;
	info = new S_CSP_REQ_ITEM_SELL;

	info->snNPCIndex = m_iNPCIndex;	// NPC 인덱스

	// 아이템이 위치한 장소와 위치 index
	HT_ITEMSETTING_FLAG sLocRoom;
	sLocRoom.nInventory = sLocRoom.nLocation = -1;
	g_cItemSystem->HT_bItemSystem_GetItemPos( m_dwFixDisjointKeyID, sLocRoom );
	if( sLocRoom.nInventory == -1 || sLocRoom.nLocation == -1 )
	{
		HT_DELETE( info );
		return;
	}

	if( sLocRoom.nLocation == ITEM_LOCATION_NPC )
	{
		info->byPlace =	ITEM_PLACE_CARGO ; 
		info->byIndex = ( sLocRoom.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + sLocRoom.pCellPos.x )
							+ ( sLocRoom.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT );
	}
	else if( sLocRoom.nLocation == ITEM_LOCATION_EQUIP )
	{
		info->byPlace =	ITEM_PLACE_EQUIP ;
		info->byIndex = sLocRoom.nInventory;
	}
	else //if( sLocRoom.nLocation == ITEM_LOCATION_PC )
	{
		info->byPlace =	ITEM_PLACE_INVEN ;
		info->byIndex = ( sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y )
							+ ( sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT );
	}

	g_pNetWorkMgr->RequestItemSell( info );
	
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemSell : %d:(%d:%d)", 
														info->snNPCIndex, info->byPlace, info->byIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );*/
}

// 해체 결과
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Item_Sell( PS_SCP_RESP_ITEM_SELL info )
{
	g_cUIMerchantWindow->HT_vNetWork_SCP_Resp_Item_Sell(info);
}

// 차크라 확장
HTvoid CHTNPCControl::HT_vNetWork_CSP_REQ_Increase_Chakra()
{
	PS_CSP_REQ_INCREASE_CHAKRA info = HT_NULL;
	info = new S_CSP_REQ_INCREASE_CHAKRA;
	info->byChakra = m_bySelectPart+1;	// 서버는 1부터 시작
	
	g_pNetWorkMgr->RequestIncreaseChakra( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RequestIncreaseChakra:%d", info->byChakra );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
// 제련 요청
HTvoid CHTNPCControl::HT_vNetWork_CSP_REQ_ITEM_REFINING()
{
	PS_CSP_REQ_ITEM_REFINING info = HT_NULL;
	info = new S_CSP_REQ_ITEM_REFINING;
	
	// 아이템이 위치한 장소와 위치 index
	HT_ITEMSETTING_FLAG sLocRoom;
	sLocRoom.nInventory = sLocRoom.nLocation = -1;
	// 제련할 아이템 위치
	g_cItemSystem->HT_bItemSystem_GetItemPos( m_dwWorkItem, sLocRoom );
	if( sLocRoom.nInventory == -1 || sLocRoom.nLocation == -1 )
	{
		HT_DELETE( info );
		return;
	}

	if( sLocRoom.nLocation == ITEM_LOCATION_NPC )
	{
		info->byPlace =	ITEM_PLACE_CARGO ; 
		info->byIndex = ( sLocRoom.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + sLocRoom.pCellPos.x )
							+ ( sLocRoom.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT );
	}
	else if( sLocRoom.nLocation == ITEM_LOCATION_EQUIP )
	{
		info->byPlace =	ITEM_PLACE_EQUIP ;
		info->byIndex = sLocRoom.nInventory;
	}
	else //if( sLocRoom.nLocation == ITEM_LOCATION_PC )
	{
		info->byPlace =	ITEM_PLACE_INVEN ;
		info->byIndex = ( sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y )
							+ ( sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT );
	}
	// 제련에 사용될 아이템 위치
	//BYTE	bySubPlace[3];											//	Index 0:주,보조재련 1:재련첨가재 2:미정
	//BYTE	bySubIndex[3];

	for (int i=0;i<3;++i)
	{
		if (m_nEconomy_Work_SubItemKeyID[i] == 0) 
		{
			info->bySubPlace[i] = 0;
			info->bySubIndex[i] = 0;
		}
		else
		{
			sLocRoom.nInventory = sLocRoom.nLocation = -1;
			g_cItemSystem->HT_bItemSystem_GetItemPos( m_nEconomy_Work_SubItemKeyID[i], sLocRoom );
			if( sLocRoom.nInventory == -1 || sLocRoom.nLocation == -1 )
			{
				HT_DELETE( info );	return;
			}

			if( sLocRoom.nLocation == ITEM_LOCATION_NPC )
			{
				info->bySubPlace[i] =	ITEM_PLACE_CARGO ; 
				info->bySubIndex[i] = ( sLocRoom.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + sLocRoom.pCellPos.x )
									+ ( sLocRoom.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT );
			}
			else if( sLocRoom.nLocation == ITEM_LOCATION_EQUIP )
			{
				info->bySubPlace[i] =	ITEM_PLACE_EQUIP ;
				info->bySubIndex[i] = sLocRoom.nInventory;
			}
			else //if( sLocRoom.nLocation == ITEM_LOCATION_PC )
			{
				info->bySubPlace[i] =	ITEM_PLACE_INVEN ;
				info->bySubIndex[i] = ( sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y )
									+ ( sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT );
			}
		}
	}

	g_pNetWorkMgr->RequestItemRefining( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ItemRefining : %d:%d(보조재료%d:%d) %d, %d", 
	//												info->byPlace, info->byIndex, info->bySubPlace[0], info->bySubIndex[0], info->bySubIndex[1], info->bySubIndex[2]);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );	
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_RESP_ITEM_REFINING( PS_SCP_RESP_ITEM_REFINING info )
{ 
	// 서버로 부터 즉시 답을 못받았을 경우를 대비해서 패킷에서 받은 값을 사용해서 결과를 적용한다. 
	// 제련된 아이템 KeyID 생성
	HTint iKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID);
	m_dwWorkItem = iKeyID;
	
	for (int i = 1; i < 4; ++i)
	{
		g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[i], g_cUIRefineWindow->m_iControlIndex[i], true);
	}

	g_cUIRefineWindow->m_iWindowIndex[0] = 0;
	g_cUIRefineWindow->m_iWindowIndex[1] = 0;
	g_cUIRefineWindow->m_iWindowIndex[2] = 0;
	g_cUIRefineWindow->m_iWindowIndex[3] = 0;

	// 보조재료 아이템 KeyID 생성
	//m_nEconomy_Work_SubItemKeyID[0] = 0;
	//m_nEconomy_Work_SubItemKeyID[1] = 0;
	//m_nEconomy_Work_SubItemKeyID[2] = 0;
	//for (HTint i = 0; i < 3; ++i)
	//{
		//BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->bySubPlace[i], info->bySubIndex[i], iKeyID);
		//m_nEconomy_Work_SubItemKeyID[i] = iKeyID;
	//}

	if( info->byResult == 0x00 || info->byResult == REPLY_ITEM_REFINING_FAIL 
							|| info->byResult == REPLY_ITEM_REFINING_DISAPPEAR 
							|| info->byResult == REPLY_ITEM_REFINING_INITIALIZE 
							|| info->byResult == REPLY_ITEM_SUBREFINING_INITIALIZE )
	{
		//---------- 시스템창에 아이템 획득 출력 ------------//
		//	아이템의 정보를 꺼내오고
		DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwWorkItem );
		if( dwIndex == 0 )
			return;

		HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( m_dwWorkItem );
		// 완료창에 보여줄 메세지
		switch( info->byResult )
		{
			case REPLY_ITEM_REFINING_FAIL :		// 제련 실패
			{
				m_bMessage_Error = HT_TRUE;	// 에러 있음
				m_byResent_ServerMsg = SERVER_MSG_RESP_WORK_FAIL;

				if( byLevel > 0 )
				{
					// %s+%d 제련이 실패했습니다
					HT_vNPCControl_SetMessage( eMsgItemRefineOneOverErr );

					if (!CHTParamIDCheck::HT_bIsItemRefineSub( m_nEconomy_Work_SubItemIndex ))
					if (byLevel > 6)	// 7보다 큰상태에서 이런 메시지가 뜬다면 이것은 자드와 같은 보조 첨가제를 사용한 경우이므로 +6으로 셋팅해 준다.
						g_cItemSystem->HT_bItemSystem_SetMainRefineLevel(m_dwWorkItem, 6);
				}
				else
				{
					// %s 제련이 실패했습니다.
					HT_vNPCControl_SetMessage( eMsgItemRefineFirstErr );
				}
			}
				break;
			case REPLY_ITEM_REFINING_DISAPPEAR :	// 제련 실패 - 아이템 소멸
			{
				m_bMessage_Error = HT_TRUE;	// 에러 있음
				m_byResent_ServerMsg = SERVER_MSG_RESP_WORK_ITEM_REMOVE;
				g_cItemSystem->HT_vItemSystem_DeleteItem(g_cNPCControl->m_dwWorkItem);

				// 제련하던 중 아이템이 사라졌습니다.
				HT_vNPCControl_SetMessage( eMsgItemRefineDisappear );
			}
				break;
			case REPLY_ITEM_REFINING_INITIALIZE : // 제련 실패 - 아이템 초기화
			{
				m_bMessage_Error = HT_TRUE;	// 에러 있음
				m_byResent_ServerMsg = SERVER_MSG_RESP_WORK_ITEM_MAIN_INIT;

				// 아이템이 초기화되습니다.
				g_cItemSystem->HT_bItemSystem_SetMainRefineLevel( g_cNPCControl->m_dwWorkItem, 0 );
				HT_vNPCControl_SetMessage( eMsgItemRefineInitialize );
			}
				break;
			case REPLY_ITEM_SUBREFINING_INITIALIZE :
			{
				m_bMessage_Error = HT_TRUE;	// 에러 없음
				m_byResent_ServerMsg = SERVER_MSG_RESP_WORK_ITEM_SUB_INIT;
				// 아이템이 초기화되습니다.
				g_cItemSystem->HT_bItemSystem_ClearSubRefineItem( g_cNPCControl->m_dwWorkItem );
				HT_vNPCControl_SetMessage( eMsgItemRefineInitialize );
			}
				break;
			default :	// info->byResylt == 0x00
			{
				m_bMessage_Error = HT_FALSE;	// 에러 없음
				m_byResent_ServerMsg = SERVER_MSG_RESP_SUCCESS;

				if( byLevel > 0 )
					// %s+%d 제련이 완료되었습니다.
					HT_vNPCControl_SetMessage( eMsgItemRefineOneOverOK );
				else
					// %s 제련이 완료되었습니다.
					HT_vNPCControl_SetMessage( eMsgItemRefineFirstOK );
			}
			break;
		}

		// 돈 갱신
		if(info->nMoney > 0)
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->nMoney );
		else
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(0);
		
		// 제련에 사용된 보조재료 지우기
		// 6554	아바티	제련시 제련재료의 소멸을 방지합니다
		DWORD dwItemID = g_cItemSystem->HT_dwSystem_GetItemIndex(m_nEconomy_Work_SubItemKeyID[1]);
		if (dwItemID == 6554)
		{
			for (HTint i=1; i<3; ++i)
			g_cItemSystem->HT_vItemSystem_DeleteItem( m_nEconomy_Work_SubItemKeyID[i] );
		}
		else
		{
			for (HTint i=0; i<3; ++i)
			g_cItemSystem->HT_vItemSystem_DeleteItem( m_nEconomy_Work_SubItemKeyID[i] );
		}
		g_cNPCControl->HT_vNPCControl_ItemWorkWin_Active();
 	}
	else
	{
		m_bMessage_Error = HT_TRUE;	// 에러 있음
		m_byResent_ServerMsg = SERVER_MSG_RESP_ERROR;

		// 완료창에 보여줄 메세지
		if( info->byResult == REPLY_ITEM_REFINING_MONEY_LACK)	// 루피아 부족
		{
			HTint nRupiah = m_nEconomy_Work_LimitRupiah - g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
			// 루피아가 %d부족합니다.
			HT_vNPCControl_SetMessage( eMsgItemRefineNeedMoneyErr );
		}
		else if( info->byResult == REPLY_ITEM_REFINING_CANNOT)	
			// 첨가 불가능한 보조재료입니다.
			HT_vNPCControl_SetMessage( eMsgItemRefineMeterialErr );
		else if( info->byResult == REPLY_ITEM_REFINING_OVER)	// 10회 제련 했음 or 제련 불가능한 아이템
		{
			if( g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( m_dwWorkItem ) >= MAX_REFINE_MAIN_LEVEL )
				// 강화 제련을 할 수 없는 아이템입니다.
				HT_vNPCControl_SetMessage( eMsgItemRefineMainCannot );
			else
				// 주술 제련을 할 수 없는 아이템입니다.");
				HT_vNPCControl_SetMessage( eMsgItemRefineSubCannot );
		}
		else if( info->byResult == REPLY_ITEM_REFINING_OUTINDEX )
			// 아이템을 찾을 수 없습니다.");
			HT_vNPCControl_SetMessage( eMsgItemCommonCannotFindInfo );
		else
			// 아이템을 제련하지 못했습니다.");
			HT_vNPCControl_SetMessage( eMsgItemRefineFail );
	}
	// 시스템 창에 표시
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
/*
	if( m_bMessage_Error == HT_FALSE )	// 성공일 경우
	{
		//-----제조 이미지와 리소스 지우기-----//
		HT_vNPCControl_ButtonCheck_Work_Delete();
		m_iResent = NPC_RESENT_NONE;
	}
	else
	{
		// 제련결과 아이템 사라짐
		if( m_byResent_ServerMsg == SERVER_MSG_RESP_WORK_ITEM_REMOVE )
			g_cItemSystem->HT_vItemSystem_DeleteItem(m_dwWorkItem);
		// 제련결과 강화제련 레벨 초기화
		else if( m_byResent_ServerMsg == SERVER_MSG_RESP_WORK_ITEM_MAIN_INITIAL )
			g_cItemSystem->HT_bItemSystem_SetMainRefineLevel( m_dwWorkItem, 0 );

		// 클라이언트에서 검사한 에러의 경우 재료 이미지만 지우고, 그렇지않으면 아이템 이미지/정보도 지우기
		if( m_byResent_ServerMsg == SERVER_MSG_NONE )	
			HT_vNPCControl_ButtonCheck_Work_TotalCancel();
		else
		{
			HT_vNPCControl_ButtonCheck_Work_Delete();
			m_iResent = NPC_RESENT_NONE;
		}
	}
	m_byResent_ServerMsg = SERVER_MSG_NONE;
*/
	g_cUIRefineWindow->m_nMessageBoxNo = 0;
	m_byMessageWin = NPC_MESSAGE_COMPLETE;
	g_cUIManager->HT_MessageBox(_DIALOG_REFINE, m_szMessage, 0);

	HT_vNPCControl_ButtonCheck_Work_TotalCancel();
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_ChangeChakraToPrana(PS_SCP_RESP_CHANGE_CKAKRA_TO_PRANA info)
{
	if( info->byResult == 0x00 )
	{
		m_bMessage_Error = HT_FALSE;	// 에러 없음
		
		//HTint nTotalChakra = g_cStatus->HT_nGetTotalChakra();	// 원래 총 차크라포인트
		//m_szMessage.HT_szFormat("차크라 포인트를 프라나로 환산했습니다"/*, nTotalChakra*/);
		HT_vNPCControl_SetMessage( eMsgChakraConversionOK );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, m_szMessage );

		// 환산한 후의 차크라 포인트와 프라나 셋팅
		//HTshort tribe = g_cMainCharacter->HT_sMainChar_GetTribe();

		PS_SCP_RESP_CHAKRA_RISING info2 = HT_NULL;
		info2 = new S_SCP_RESP_CHAKRA_RISING;
		
		info2->nPrana = info->nPrana;
		info2->nChakraPoint = 50;
		//info2->snChakraMuscle = g_ChakraTable[CHAKRA_POINT_MUSCLE][(tribe-1)%4] ;	// 근육
		//info2->snChakraNerve = g_ChakraTable[CHAKRA_POINT_NERVE][(tribe-1)%4];	// 신경
		//info2->snChakraHeart = g_ChakraTable[CHAKRA_POINT_HEART][(tribe-1)%4];	// 심장
		//info2->snChakraSoul = g_ChakraTable[CHAKRA_POINT_SOUL][(tribe-1)%4];		// 정신

		g_cStatus->HT_vStatus_SetChakra_Rising( info2 );
		HT_DELETE(info2);	
	}
	else
	{
		m_bMessage_Error = HT_TRUE;		// 에러 있음
		
		if( info->byResult == 0x02 )
			// 착용한 아이템에 의해 프라나 환산이 실패했습니다.
			HT_vNPCControl_SetMessage( eMsgChakraConversionItemErr );
		else
			// 차크라를 프라나로 환산하는데 실패했습니다.
			HT_vNPCControl_SetMessage( eMsgChakraConversionFail );

		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, m_szMessage );
	}

	// 대화상자 대화 바꾸기
	HT_vNPCControl_GetNextStep(m_nSelectCount);
}

// 복권 등록 결과일 경우
HTvoid CHTNPCControl::HT_vNetWork_RegistLottery( BYTE byResult, DWORD dwKeyID )
{
	if( dwKeyID > 0 )
	{
		DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
		if( dwIndex == 0 )
			return;
	}

	if( byResult <= REPLY_COUPONEVENT_10ST )
	{
		m_bMessage_Error = HT_FALSE;	// 에러 없음
		
		// 쿠폰 사용을 셋팅 - 10레벨 쿠폰을 항상 먼저 사용한다
		// 상위 4비트의 2비트는(10레벨/20레벨)는 권한, 하위 4비트의 2비트(10레벨/20레벨)는 수행여부.
		HTbyte byFlag = g_oMainCharacterInfo.snDummy >> 4 ;
		HTbyte byUse = g_oMainCharacterInfo.snDummy & 0x0F;
		if( (byFlag & 0x02) && !(byUse & 0x02) ) // 10레벨의 쿠폰을 사용했으면 
			byUse |= 0x02;
		else // 20레벨의 쿠폰을 사용했으면
			byUse |= 0x01;

		g_oMainCharacterInfo.snDummy |= byUse ;
		// 쿠폰 당첨 내역
		switch( byResult )
		{
			case REPLY_COUPONEVENT_1ST:
				m_szMessage.HT_szFormat("수라파를 획득했습니다");
				break;
			case REPLY_COUPONEVENT_2ST:
				m_szMessage.HT_szFormat("아지스를 획득했습니다");
				break;
			case REPLY_COUPONEVENT_3ST:
				m_szMessage.HT_szFormat("아지스를 획득했습니다");
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				m_szMessage.HT_szFormat("일라를 획득했습니다");
				break;
			case REPLY_COUPONEVENT_4ST:
				m_szMessage.HT_szFormat("일라를 획득했습니다");
				break;
			case REPLY_COUPONEVENT_5ST:
				m_szMessage.HT_szFormat("일라를 획득했습니다");
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				m_szMessage.HT_szFormat("옴 얀트라를 획득했습니다");
				break;
			case REPLY_COUPONEVENT_6ST:
				m_szMessage.HT_szFormat("옴 얀트라를 획득했습니다");
				break;
			case REPLY_COUPONEVENT_7ST:
				m_szMessage.HT_szFormat("영화관람권을 획득했습니다");
				break;
			case REPLY_COUPONEVENT_8ST:
				m_szMessage.HT_szFormat("그래픽카드를 획득했습니다");
				break;
			case REPLY_COUPONEVENT_9ST:
				m_szMessage.HT_szFormat("<초강력 타란튤라, 로즈헤어>를 획득했습니다");
				break;
			case REPLY_COUPONEVENT_10ST:
				m_szMessage.HT_szFormat("<미끈한 도마뱀, 그린에놀>을 획득했습니다");
				break;
			default: // 꽝
				m_szMessage.HT_szFormat("암리타를 획득했습니다");
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				m_szMessage.HT_szFormat("파나카를 획득했습니다");
				break;
		}

		// 대화상자 대화 바꾸기
		HT_vNPCControl_GetNextStep( m_nSelectCount );
	}
	else
	{
		m_bMessage_Error = HT_TRUE;		// 에러 있음

		switch( byResult )
		{
			case REPLY_COUPONEVENT_LACK : // 인벤토리 공간 부족
			{
				HT_vNPCControl_SetMessage( eMsgItemCommonInvenLack );
				
				// 완료창 띄움
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			}
				break;
			case REPLY_COUPONEVENT_UNKNOWN :
				m_szMessage.HT_szFormat("잘못된 쿠폰번호입니다");
				HT_vNPCControl_GetNextStep( m_nSelectCount );
				break;
			default :
				m_szMessage.HT_szFormat("쿠폰 등록이 실패했습니다");
				HT_vNPCControl_GetNextStep( m_nSelectCount );
				break;
		}
	}

	if( m_szMessage.HT_bIsEmpty() == HT_FALSE )
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
}

// 위치 저장 요청 결과
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_SavePosition( PS_RESULT info )
{
	if( info->nResult == 0x00 )
		// 현재 위치가 저장되었습니다.
		HT_vNPCControl_SetMessage( eMsgSavePositionOK );
	else
		// 현재 위치를 저장하지 못했습니다.
		HT_vNPCControl_SetMessage( eMsgSavePositionFail );

	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, m_szMessage );

	// 대화상자 대화 바꾸기
	HT_vNPCControl_GetNextStep(m_nSelectCount);
}

// PVP 순위 리스트 요청 결과
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_PVP_Rank()
{
	// 대화상자 대화 바꾸기
	HT_vNPCControl_GetNextStep(m_nSelectCount);
}

// 주신 선택
HTvoid CHTNPCControl::HT_vNetWork_CSP_Req_Select_Trimuriti(BYTE byType)
{
	MSG_TrimuritySelect* info = HT_NULL;
	info = new MSG_TrimuritySelect;

	info->byType = byType;
	if (info->byType == 1)
	{
		strcpy( info->CharName, g_oMainCharacterInfo.szCharName );
		switch( m_bySelectPart )
		{
			case 0 : info->byTrimuriti = TRIMURITI_BRAHMA; break;
			case 1 : info->byTrimuriti = TRIMURITI_VISHNU; break;
			case 2 : info->byTrimuriti = TRIMURITI_SIVA; break;
			default: HT_DELETE( info );	return;
		}
	}
	
	g_pNetWorkMgr->RequestSelectTrimuriti( info, byType );	// byType = 1은 실행

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_SelectTrimuriti : %s-%d(type = %d)", info->CharName, info->byTrimuriti, info->byType);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );	
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Select_Trimuriti( MSG_TrimuritySelect* info )
{
	if (m_bTrimutiri == 1)	// 선택
	{
		// 내 캐릭터의 주신 선택 결과
		if( strcmp(info->CharName, g_oMainCharacterInfo.szCharName) == 0 )
		{
			// 브라만 올리는 이펙트 
			HTint idFx;
			g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_BRAMANUPGRADE, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );

			// 주신 변경의 경우 루피아가 소모된다
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );

			g_oMainCharacterInfo.byTrimuriti = info->byTrimuriti;
			// 캐릭터 정보창의 주신 정보 변경
			CHTString szString;
			szString = g_cStatus->HT_szStatus_GetTrimuriti();
/*
			//	주신선택을 존에 공지함
			MSG_Broadcast* pData = HT_NULL;
			pData = new MSG_Broadcast;
			pData->byBgColor		= 14;			    // 채팅 메세지 배경색
			pData->byTextColor		= 14;			    // 채팅 메세지 배경색
			pData->byMsgType		= 1;
			pData->byTrimuriti		= g_oMainCharacterInfo.byTrimuriti;
			// /공지 %s님이 %s주신을 선택했습니다.
			HT_vNPCControl_SetMessage( eMsgTrimuritiChangeOK ); // /공지 %s님이 %s주신을 선택했습니다.
			CHTString::HT_hrStringCopy( pData->szMsg, m_szMessage, MAX_NOTIFY_LENGTH ); // MAX_NOTIFY_LENGTH = 1024
			CHTString::HT_hrStringCopy( pData->szName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH ); // SZNAME_LENGTH = 20
			// 메시지 전송을 서버에 요청함
			g_pNetWorkMgr->ReqNotifyMessage( pData );
			HT_DELETE( pData );
*/
			//	주신 마크 표현 하기 하기
			g_cGuildSystem->HT_vTrimutiri_MarkOn();

			// 내 캐릭터의 주신선택 결과일 경우 대화창 내용 바꾸기
			HT_vNPCControl_GetNextStep( m_nSelectCount );
		}
		else	// 다른 캐릭터의 주신 선택
		{
			//	주신 마크 셋팅하기
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTrimuritiD( info->CharName, info->byTrimuriti );
			//	주신 마크 표현하기
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowTrimuritiMark();
		}
	}
	else	// 조회일 경우에는 값만 저장
	{
		m_snBrahmaCount = info->nBrahmaCount;	// 브라흐마 
		m_snVishnuCount = info->nVishnuCount;	// 비슈느
		m_snSivaCount = info->nSivaCount;	// 시바
	}
}

// 주신 포인트 확장
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Rising_Brahman( MSG_TrimurityPoint* info )
{
	// 루피아가 소모된다
	g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );
	// 주신 포인트
	g_oMainCharacterInfo.nBrahmanPoint = info->nBramanPoint;
	// 캐릭터 정보창의 주신포인트 정보 갱신
	CHTString strString;
	// %d, g_oMainCharacterInfo.nBrahmanPoint );
	strString = g_cUIManager->HT_strSetRestMark(g_oMainCharacterInfo.nBrahmanPoint);
	// 대화창 내용 바꾸기
	HT_vNPCControl_GetNextStep( m_nSelectCount );
}

// 전직 요청
HTvoid CHTNPCControl::HT_vNetWork_CSP_REQ_Change_Job( )
{
	MSG_CLASS* info = HT_NULL;
	info = new MSG_CLASS;
	
	// 종족별로 전직할 수 있는 직업이 정해져있기 때문에 
	info->byClass1 = g_oMainCharacterInfo.byClass1+1;
	if( g_oMainCharacterInfo.byClass1 == CLASS_LEVEL0 )	// 1차 전직일 경우
		info->byClass2 = g_cStatus->HT_iStatus_GetJob1ForTribe();
	else	// 2차 전직일 경우 2가지중 택일
		info->byClass2 = m_bySelectPart;

	g_pNetWorkMgr->ReqChangeJob( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ChangeJob : %d-%d", info->byClass1, info->byClass2 );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );	
}

HTvoid CHTNPCControl::HT_vNetwork_SCP_Resp_Change_Job( MSG_CLASS* info )
{
	if( info->nID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		if( info->byClass1 == g_oMainCharacterInfo.byClass1 && info->byClass2 == g_oMainCharacterInfo.byClass2 )
			// 전직하지 못했습니다.
			HT_vNPCControl_SetMessage( eMsgJobChangeFail );
		else
		{
			g_oMainCharacterInfo.byClass1 = info->byClass1;
			g_oMainCharacterInfo.byClass2 = info->byClass2;

			// %s(으)로 전직했습니다., g_cStatus->HT_szStatus_GetJobName().HT_szGetString()
			HT_vNPCControl_SetMessage( eMsgJobChangeOK );
		}

		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, m_szMessage );

		// 대화상자 대화 바꾸기
		HT_vNPCControl_GetNextStep(m_nSelectCount);
	}
	// 주변 캐릭터가 전직했을 경우
	else
	{
		if( info->byClass1 > CLASS_LEVEL0 )
		{
			m_szObjectName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(info->nID);
			// %s님이 %d차 전직을 했습니다.,
			//	g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(info->nID).HT_szGetString(), info->byClass1
			HT_vNPCControl_SetMessage( eMsgJobChangeOtherChar );
		}
	}
}

// 현재 헌납 수치 요청 결과
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_RefineScale( MSG_RefineScale* info )
{ 
	if (g_wResentZoneServerID == 16)	// 요새전 지역에서는 별도 처리
	{
		m_iDurgaReceiptofMoney = info->dwRupiah; // 적립된 금액 저장
		HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
	}
	else
	{

		if( m_iResent == NPC_RESENT_REFINE_RATE_UP ) // 축복 수치 게이지 변경
			HT_vNPCControl_Offering_SetGauge( info->snRefineScale ); 
		else // 헌납을 위해 object를 클릭했을 경우
		{
			// 헌납창 띄우기
			HT_vNPCControl_OfferingWin_Active( info->snRefineScale );
		}

		m_fGaugeTimer = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );	// 현재 시간 저장
	}
}

// 헌납 요청
HTvoid CHTNPCControl::HT_vNetWork_CSP_Req_ItemOffering()
{
	MSG_ItemContribution* info = HT_NULL;
	info = new MSG_ItemContribution;

	for( HTint i = 0; i < MAX_ITEM_CONTRIBUTION ; ++i )
	{
		if( m_iOfferingItemKeyID[i] > 0 )
		{
			info->byPlace[i] = ITEM_PLACE_INVEN;
			info->byIndex[i] = m_iOfferingItemPlace[i];
		}
		else
		{
			info->byPlace[i] = -1;
			info->byIndex[i] = -1;
		}
	}
	info->dwRupia = m_dwOfferingRupiah;

	g_pNetWorkMgr->RequestItemOffering( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemOffering: %d개-%d루피아"
	//														, m_byOfferingItemNum, m_dwOfferingRupiah );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTNPCControl::HT_vNetWork_CSP_Req_RupiahOffering(HTint nRupiah)
{ 
	MSG_ItemContribution* info = HT_NULL;
	info = new MSG_ItemContribution;

	for( HTint i = 0; i < MAX_ITEM_CONTRIBUTION ; ++i )
	{
		if( m_iOfferingItemKeyID[i] > 0 )
		{
			info->byPlace[i] = ITEM_PLACE_INVEN;
			info->byIndex[i] = m_iOfferingItemPlace[i];
		}
		else
		{
			info->byPlace[i] = -1;
			info->byIndex[i] = -1;
		}
	}
	info->dwRupia = nRupiah;

	g_pNetWorkMgr->RequestItemOffering( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemOffering: 요새전 %d루피아"
	//														, nRupiah );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_ItemOffering( MSG_ItemContribution* info )
{
	if( info->byResult == 0x00 ) // 성공
	{
		if (g_wResentZoneServerID == 16)	// 요새전 지역에서는 별도 처리
		{
			// 돈 갱신
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwRupia );
			// 헌납 성공
			HT_vNPCControl_SetMessage( eMsgOfferingOK );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, m_szMessage );
			return;
		}
		else
		{
			HT_vNPCControl_Offering_SetGauge( info->snRefineScale ); // 헌납 게이지 변경
			m_fGaugeTimer = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );	// 현재 시간 저장
			HT_vNPCControl_Offering_SetRupiah( 0 ); // 헌납액 초기화

			// 돈 갱신
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwRupia );
			// 헌납 성공
			HT_vNPCControl_SetMessage( eMsgOfferingOK );
		}
	}
	else
	{
		switch( info->byResult )
		{
			case REPLY_ITEM_CONTRIBUTION_OUTINDEX:
				// 인벤에 없는 아이템(아이템 위치 오류)
				HT_vNPCControl_SetMessage( eMsgItemCommonNotExistItem );
				break;
			case REPLY_ITEM_CONTRIBUTION_OUTPARAM:
				// 아이템 정보를 찾을 수 없다
				HT_vNPCControl_SetMessage( eMsgItemCommonCannotFindInfo );
				break;
			case REPLY_ITEM_CONTRIBUTION_CANNOT:
				// 헌납할 수 없는 아이템
				HT_vNPCControl_SetMessage( eMsgOfferingCannot );
				break;
			case REPLY_ITEM_CONTRIBUTION_LACK:
				// 금액 부족
				HT_vNPCControl_SetMessage( eMsgItemCommonMoneyErr );
				break;
			default:
				// 헌납 실패
				HT_vNPCControl_SetMessage( eMsgOfferingFail );
				break;
		}
	}

	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, m_szMessage );

	// 헌납창의 아이템 지우기
	if (g_wResentZoneServerID != 16)
		HT_vNPCControl_OfferingItemDeleteAll( );
}

// 테스크 요청
HTvoid CHTNPCControl::HT_vNetWork_CSP_Req_TaskQuest( HTint iTaskQuest )
{
	MSG_STANDARDPARM* info = HT_NULL;
	info = new MSG_STANDARDPARM;

	info->nID = iTaskQuest;		// Task ID

	short int snNpcIndex = 0;
	// 임시 코딩 (만다라 2,3 존에서 대화를 걸었을 경우 퀘스트 진행을 위해 1번존 index로 변경)

	switch( m_iNPCIndex )
	{
		// 무기 상인
	case 1101 :	// 만다라
	case 1205 :	// 18번 만다라
	case 1235 :	// 19번 만다라
		{
			snNpcIndex = 1101;
		}
		break;

		// 방어구 상인
	case 1102 :	// 만다라
	case 1206 :	// 18번 만다라
	case 1236 :	// 19번 만다라
		{
			snNpcIndex = 1102;
		}
		break;

		// 액세서리 상인 
	case 1103 :	// 만다라
	case 1207 :	// 18번 만다라
	case 1237 :	// 19번 만다라
		{
			snNpcIndex = 1103;
		}
		break;

		// 승려
	case 1104 :	// 만다라
	case 1208 :	// 18번 만다라
	case 1238 :	// 19번 만다라
		{
			snNpcIndex = 1104;
		}
		break;

		//	물품보관지기
	case 1105 :	// 만다라
	case 1209 :	// 18번 만다라
	case 1239 :	// 19번 만다라
		{
			snNpcIndex = 1105;
		}
		break;

		// 수비대장
	case 1108 :	// 만다라 
	case 1212 : // 18번 만다라
	case 1242 :	// 19번 만다라
		{
			snNpcIndex = 1108;
		}
		break;

		// 역마꾼(게이트)
	case 1106 :	// 만다라
	case 1210 : // 18번 만다라
	case 1240 :	// 19번 만다라
		{
			snNpcIndex = 1106;
		}
		break;
		// 주술사(마법동물대여)
	case 1107 :		// 만다라
	case 1211 :		// 18번 만다라
	case 1241 :		// 19번 만다라
		{
			snNpcIndex = 1107;
		}
		break;
		// 병사1
	case 1001 :	// 만다라
	case 1201 :	// 18번 만다라
	case 1231 :	// 19번 만다라
		{
			snNpcIndex = 1001;
		}
		break;
		// 병사2
	case 1002 :	// 만다라
	case 1202 :	// 18번 만다라
	case 1232 :	// 19번 만다라
		{
			snNpcIndex = 1002;
		}
		break;
		//	남자아이1
	case 1003 :	// 만다라
	case 1203 : // 18번 만다라
	case 1233 : // 19번 만다라
		{
			snNpcIndex = 1003;
		}
		break;

		//	여자아이1
	case 1005 :	// 만다라
	case 1204 : // 18번 만다라
	case 1234 : // 19번 만다라
		{
			snNpcIndex = 1005;
		}
		break;

		// 퀘스트용 병사 NPC
	case 1115 :	// 공동 협의체
	case 1213 :	// 18번 만다라
	case 1243 : // 19번 만다라
		{
			snNpcIndex = 1115;
		}
		break;

		// 스포르바다 병사 NPC
	case 1116 :
	case 1214 : // 18번 만다라
	case 1244 : // 19번 만다라
		{
			snNpcIndex = 1116;
		}
		break;

		// 아바타라의 무덤 아이
	case 1117 :
	case 1215 : // 18번 만다라
	case 1245 : // 19번 만다라
		{
			snNpcIndex = 1117;
		}
		break;
	default:
		snNpcIndex = m_iNPCIndex;
		break;
	}

	//info->Parm = m_iNPCIndex;	// NPC ID
	info->Parm = snNpcIndex;

	g_pNetWorkMgr->RequestTaskQuest( info );
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_TaskQuest: %d-%d", info->nID, info->Parm );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_TaskQuest( MSG_STANDARDPARM* info )
{
	if( info->Parm == 0x00 ) //  성공
	{
		m_bMessage_Error = HT_FALSE;		// 에러 없음

		// 마라의 혈액류 판매
		if( TASK_QUEST_1_START <= info->nID &&  info->nID <= TASK_QUEST_1_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestMaraBloodSellOK );

		// 마라의 원액 제조
		else if( TASK_QUEST_2_START <= info->nID &&  info->nID <= TASK_QUEST_2_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestMaraSolutionMakingOK );

		// 파나카류 제조
		else if( TASK_QUEST_3_START <= info->nID &&  info->nID <= TASK_QUEST_3_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestPanacaMakingOK );

		// 차투랑가 카야 합성
		else if( TASK_QUEST_4_START <= info->nID &&  info->nID <= TASK_QUEST_4_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestChaturangaPieceOK );

		// 한 손/양손 무기 제작
		else if( TASK_QUEST_5_START <= info->nID &&  info->nID <= TASK_QUEST_6_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestWeaponMakingOK );

		// 아이템 제작 
		// 수집 아이템으로 1차 재료 추출, 1차 재료로 종족 방어구 부분품 제작, 방어구 제작
		else if( (TASK_QUEST_7_START <= info->nID &&  info->nID <= TASK_QUEST_13_END)
				|| (TASK_QUEST_42_START <= info->nID &&  info->nID <= TASK_QUEST_67_END) 
				|| (TASK_QUEST_79_START <= info->nID &&  info->nID <= TASK_QUEST_80_END) )
				
			HT_vNPCControl_SetMessage( eMsgTaskQuestItemMakingOK );

		// 아이템 분리
		// 방어구 분리를 통한 부분품 추출, 부분품 분리를 통한 1차 재료 추출
		else if( TASK_QUEST_14_START <= info->nID &&  info->nID <= TASK_QUEST_41_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestItemSeparationOK );

		// 널 이벤트 성공시
		else if( TASK_QUEST_68_START <= info->nID && info->nID <= TASK_QUEST_74_END)
			HT_vNPCControl_SetMessage( eMsgTaskQuestNullEventOK ); // 이벤트에 당첨 되었습니다.

		// 크리스마스 이벤트
		else if( TASK_QUEST_75_START <= info->nID && info->nID <= TASK_QUEST_75_END)
			HT_vNPCControl_SetMessage( eMsgTaskQuestMerryXMas );

		// 라푸 크리스탈 업그레이드 이벤트 
		else if( TASK_QUEST_76_START <= info->nID && info->nID <= TASK_QUEST_77_END)
			HT_vNPCControl_SetMessage( eMsgTaskQuestWeaponMakingOK );

		// 라훌 요술주머니 이벤트 결과 메시지
		else if( TASK_QUEST_78_START <= info->nID && info->nID <= TASK_QUEST_78_END)
			HT_vNPCControl_SetMessage( eMsgTaskQuestEventBoxOnenOK );

		// 카우스트밤 및 이벤트 아이템 결과 메시지
		else if( TASK_QUEST_81_START <= info->nID && info->nID <= TASK_QUEST_87_END)
			HT_vNPCControl_SetMessage( eMsgTaskQuestItemMakingOK );

		// 프라다야 교환
		else if( TASK_QUEST_83_START <= info->nID && info->nID <= TASK_QUEST_83_END)
			HT_vNPCControl_SetMessage( eMsgTradeSuccess );

		// 속성 변경 이벤트
		else if( TASK_QUEST_88_START <= info->nID && info->nID <= TASK_QUEST_88_END)
			HT_vNPCControl_SetMessage( eMsgTradeSuccess );

		// 교환
		else if( TASK_QUEST_89_START <= info->nID && info->nID <= TASK_QUEST_89_END)
			HT_vNPCControl_SetMessage( eMsgTradeSuccess );

		else if( TASK_QUEST_90_START <= info->nID && info->nID <= 10600)
			HT_vNPCControl_SetMessage( eMsgTradeSuccess );
		
		// 다음 단계로 넘어감
		HT_vNPCControl_GetNextStep( m_nSelectCount ); 
	}
	else
	{
		m_bMessage_Error = HT_TRUE;		// 에러 있음
		switch( info->Parm )
		{
			case 1: // 테스크 인덱스 오류
				HT_vNPCControl_SetMessage( eMsgTaskQuestCannotFindInfo );
				break;
			case 2: // NPC 번호 오류
				HT_vNPCControl_SetMessage( eMsgTaskQuestNPCIDErr );
				break;
			case 3: // 필요한 아이템이 인벤토리에 없음
				HT_vNPCControl_SetMessage( eMsgTaskQuestNeedItemErr );
				break;
			case 4: // 인벤토리 공간이 부족
				HT_vNPCControl_SetMessage( eMsgItemCommonInvenLack );
				break;
			case 5: // 돈 부족
				HT_vNPCControl_SetMessage( eMsgTaskQuestNeedMoneyErr );
				break;
			case 6: // NPC와의 거리가 너무 멀다
				HT_vNPCControl_SetMessage( eMsgCommonDistanceErrToNPC );
				break;
			case 7 : // 확률의 의해 작업이 실패했습니다.
				HT_vNPCControl_SetMessage( eMsgTaskQuestRateErr );
				break;
			case 8 : // 죄송합니다. 아직 이곳에서는 이벤트를 하지 않습니다.
				HT_vNPCControl_SetMessage( eMsgTaskQuestNoEventErr );
			case 9 : // 카르마 수치가 조건에 맞지 않습니다.
				HT_vNPCControl_SetMessage( eMsgTaskQuestKarmaErr );
			case 10 : // 카르마 수치가 조건에 맞지 않습니다.
				HT_vNPCControl_SetMessage( eMsgTaskQuestLevelErr );
			default: // 테스크 퀘스트 실패
				HT_vNPCControl_SetMessage( eMsgTaskQuestFail );
				break;
		}
		// 다음 단계로 넘어감
		HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 
	}

	if( m_szMessage.HT_bIsEmpty() == HT_FALSE)
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, m_szMessage );
}

// 캐쉬 정보 요청
HTvoid CHTNPCControl::HT_vNetWork_CSP_Req_Item_Cash()
{
	Msg_Cash* info = HT_NULL;
	info = new Msg_Cash;
	info->byType = 1;

	g_pNetWorkMgr->RequestItemCash( info );
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Item_Cash");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Item_Cash( Msg_Cash* info )
{
	CHTString strCash;
	strCash.HT_szFormat("%d",info->nCash);
	m_nCash = info->nCash;

	// 프리미엄 아이템 구입
	if( m_iResent == NPC_RESENT_PREMIUM_ITEM || m_iResent == NPC_RESENT_PREMIUM_ITEM2 || m_iResent == NPC_RESENT_PREMIUM_ITEM3)
	{
		// 아이템 구입목록창에 캐쉬 표시
		// 아이템 리스트 구성
		//HT_vNPCControl_GetItemList();
		HT_vNPCControl_GetPrimiumItemList();
	}
	// 그 밖에 프리미엄 서비스 이용시
	else
	{
		// 다음 단계로 넘어감
		HT_vNPCControl_GetNextStep( m_nSelectCount ); 
	}
}

// 스킬/스텟 재분배 요청 2004. 8. 27 
HTvoid	CHTNPCControl::HT_vNetWork_CSP_Req_CharacterInitialize(HTint iCommand, HTint iType)   // 차크라 초기화 정보 요청
{
	// Type  1 = 스킬,  2 = 차크라, 3 = 2차 전직,  4 = 스킬&차크라, 5 = 이벤트 아이템 적립요청
	Msg_NPCCommand* info = HT_NULL;
	info = new Msg_NPCCommand;
	info->nNPCID =  m_iNPCIndex;
	info->byCommand = m_nCommand = iCommand;	// 서버로 부터 정보 조회하기
	info->byType = m_nType;

	switch (iType)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:

		// Type이 3이면 2차전직 초기화를 요청 한다.
		if (iCommand == 2 && iType == 3)
		{
			info->byType = m_nType = iType;		// 2차 전직 초기화 요청
		}
		else if (iCommand == 1)	// Command가 2이면 타입을 얻지 않는다.
		{
			info->byType = m_nType = iType;		// 초기화 정보 가지고 올것이 스킬인지 차크라인지 설정.
		}
		else if (iCommand == 2 && CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex) == HT_TRUE)
		{
			info->byType = m_nType = iType;		// 초기화 요청
		}
		break;

	case 5:	// 이벤트 아이템 적립정보 요청
		info->byType = m_nType = iType;		// 적립 정보 요청
		break;
		}

	g_pNetWorkMgr->RequestCharacterInitialize( info );
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Char_Initialize Type=%d, Command=%d",m_nType, m_nCommand);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}


HTvoid 	CHTNPCControl::HT_vNetWork_SCP_Resp_Item_CharacterInitialize( Msg_NPCCommand* info )
{
 	m_nFirst = info->byFirst;		// 조회할때만 제대로 얻어온다.
	m_nResult = info->byResult;	// 요청할때만 얻어온다.
	m_nRupia = info->nRupia;
	CHTString strTemp;

	switch(m_nType)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:

			if (m_nType == 3)	// 2차 전직 초기화 정보를 받았을 경우
			{
				if (info->byResult == 0)	// 성공시 안내창 띄움
				{
					// 성공시 안내창 띄움
					HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// 다음 단계로 넘어감
					HT_vNPCControl_SetMessage( eMsgPremiumReq2GradeInitOK );
					m_bMessage_Error = HT_TRUE;
					m_byMessageWin = NPC_MESSAGE_COMPLETE;
					g_cUIStatus->m_MessageBoxType = 0;
					g_cUIManager->HT_MessageBox( _DIALOG_BACKGROUND, m_szMessage, 0); 
					return;
				}
				else
				{
					// 실패시 안내창 띄움
					HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// 다음 단계로 넘어감
					HT_vNPCControl_SetMessage( eMsgItemCommonCashErr );
					m_bMessage_Error = HT_TRUE;
					m_byMessageWin = NPC_MESSAGE_COMPLETE;
					g_cUIStatus->m_MessageBoxType = 0;
					g_cUIManager->HT_MessageBox( _DIALOG_BACKGROUND, m_szMessage, 0); 
					return;
				}
			}

/*
			if (info->byResult == 0 || info->byCommand == 1)
			{
				if (m_nCommand == 2 && m_nFirst != 1 && m_nFirst2 == 2)
				{
					g_cEquipInventory->HT_vEquipInventory_SetPCMoney(m_nRupia);
				}
				
				if (CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex) == HT_TRUE)
				{
					switch (m_nType)
					{
						case 1:
							HT_g_Script_SetMessage( eMsgSkillInitialized, &strTemp, _T("") );		//	"스킬이 초기화 되었습니다."
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
							break;
						case 2:
							HT_g_Script_SetMessage( eMsgChakraInitialized, &strTemp, _T("") );		//	"차크라가 초기화 되었습니다."
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
							break;
						case 4:
							HT_g_Script_SetMessage( eMsgSkillChakraInitialized, &strTemp, _T("") );		//	"스킬 및 차크라가 초기화 되었습니다."
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
							break;
					}
					HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
					return;
				}
				HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// 다음 단계로 넘어감
			}
			else
			{*/
				switch(info->byResult)
				{
					case 0:	// 성공
						HT_g_Script_SetMessage( eMsgSkillInitialized, &strTemp, _T("") );		//	"스킬이 초기화 되었습니다."
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
						break;
					case 1:	// 루피아 부족
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "루피아가 부족합니다.");
						break;
					case 2:
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "아이템을 착용하여 작업 실패하였습니다");
						break;
					case 3:
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "초기화가 불가능 합니다.");
						break;
					case 4:
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "이벤트 대상이 아닙니다.");
						break;
					case 5:
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "이미 참여하셨습니다.");
						break;
					default:
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "이벤트 조건에 해당되지 않습니다.");
						break;
//				}

//				HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 	// 다음 단계로 넘어감
				g_cUIManager->HT_HideWindow( _DIALOG_NPCWINDOW );

			}
			return;

		case 5:	// NPC 이벤트 아이템 적립갯수 요청 결과
			m_iEventItem = info->nRupia;
			if (info->byResult != 0)
				HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// 다음 단계로 넘어감
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 	// 다음 단계로 넘어감
			return;
	}
}

// 기능성 유료화 아이템 신청
HTvoid CHTNPCControl::HT_vNetWork_CSP_Resp_Charge_Function_Item( HTdword dwItemIndex )
{
	Msg_Time* info = HT_NULL;
	info = new Msg_Time;
	info->nItemID = dwItemIndex - HT_ITEM_INDEX_START;

	g_pNetWorkMgr->RequestChargeFunctionItem( info );
	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Charge_Function_Item : %d", info->nItemID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Charge_Function_Item( Msg_Time* info )
{
	if( info->byResult == 0x00 )
	{
		// 캐쉬 갱신
		CHTString strCash;
		strCash.HT_szFormat("%d",info->nCash);
		m_nCash = info->nCash;
		
		HTdword dwItemIndex = info->nItemID + HT_ITEM_INDEX_START;
		CHTString szTime;
		switch( dwItemIndex )
		{
			case HT_INDEX_EXPAND_INVEN: // 인벤토리 확장
			{
				// Bag2 사용가능
				g_cEquipInventory->HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH); 
				// 인벤토리가 확장됐습니다.
				HT_vNPCControl_SetMessage( eMsgItemEquipInvenIncOK );
				// 기한 갱신
				g_cMainCharacter->HT_vMainChar_SetTimeStamp( eTime_Inven, info->dwTime );
				//g_cMainCharacter->HT_vMainChar_GetTimeStamp( eTime_Inven, szTime );
			}
				break;
			case HT_INDEX_EXPAND_SHOP: // 개인상점 확장
			{
				// 개인상점이 확장됐습니다.
				HT_vNPCControl_SetMessage( eMsgShopExpandOK );
				// 기한 갱신
				g_cMainCharacter->HT_vMainChar_SetTimeStamp( eTime_Store, info->dwTime );
			}
				break;
			case HT_INDEX_AUTO_ROUTING:	// 자동 돈줍기 적용
			{
				// 자동 돈줍기 기능이 적용되었습니다.
				HT_vNPCControl_SetMessage( eMsgShopAutoRouting );

				// 기한 갱신
				g_cMainCharacter->HT_vMainChar_SetTimeStamp( eTime_AMoneyRoot, info->dwTime );
			}
				break;

			default:
				m_szMessage.HT_hrCleanUp();
				break;
		}

		// 만약 현재 프리미엄 아이템 사용내역이 열려있는 상태라면 갱신한다.
		if (g_cUIManager->HT_isShowWindow( _DIALOG_MY_USEINFO_V3 ) == HT_TRUE)
			g_cIndividualStore->HT_vIndividualStore_ButtonCheckForUseListOutPut();

		// 다음 단계로 넘어감
		HT_vNPCControl_GetNextStep( m_nSelectCount ); 
	}
	else
	{
		m_bMessage_Error = HT_TRUE;	// 에러 있음
 
		if( info->byResult == REPLY_ITEM_BUY_GOLD_WANT)	// 돈 부족
			// 캐쉬가 부족합니다.
			HT_vNPCControl_SetMessage( eMsgItemCommonCashErr );
		else if( info->byResult == REPLY_ITEM_BUY_INVENTORY_LACK)	// 인벤토리 공간 부족
			// 인벤토리 공간이 부족합니다.
			HT_vNPCControl_SetMessage( eMsgItemCommonInvenLack );
		else
			// 서비스 신청이 실패했습니다.
			HT_vNPCControl_SetMessage( eMsgPremiumReqFail );

		//m_byMessageWin = NPC_MESSAGE_COMPLETE;
		
		// 다음 단계로 넘어감
		HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 
	}
	m_byResent_ServerMsg = SERVER_MSG_NONE;
	// 시스템 창에 표시
	if( m_szMessage.HT_bIsEmpty() == HT_FALSE )
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
}

////////////////////////////////////////////////////////////////////////////////////////////
//--------- 나열된 스킬 중 마우스로 클릭한 스킬의 이름 ------------//
CHTString CHTNPCControl::HT_szNPCControl_GetSelectSkillName() 
{
	if(m_dwSkillRegistIndex == 0)	// 선택된 스킬 index가 없으면
		return _T("");

	// 스킬 이름 찾기
	for(int i = 0; i < m_nSkillList_Count; ++i)
	{
		if( m_dwSkillRegistIndex == m_nSkillList_Index[i] )
		{
			return m_szSkillList_Name[i];
		}
	}

	return _T(""); 
};

// 기술 리스트를 받기 전에 저장할 장소 초기화
HTvoid CHTNPCControl::HT_vNPCControl_SkillList_Delete()
{
	m_nSkillList_Count = 0;	// 습득 가능한 스킬 수
	for(int i = 0; i<50; ++i)
	{
		m_szSkillList_Name[i].HT_hrCleanUp();
		m_nSkillList_Index[i] = 0;
		m_nSkillList_Type[i] = 0;
	}
}

//--------- 삭제 가능한 스킬 리스트 가져오기 -----------//
HTvoid CHTNPCControl::HT_vNPCControl_GetSkillList()
{
	// 기술 리스트 저장할 장소 초기화
	m_nSkillList_Count = 0;	// 삭제 가능한 스킬 수
	for(int i = 0; i<50; ++i)
	{
		m_szSkillList_Name[i].HT_hrCleanUp();
		m_nSkillList_Index[i] = 0;
	}
}
