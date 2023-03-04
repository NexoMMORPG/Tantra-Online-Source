#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTquest.h"

//#define TUTORIAL_START_CHAKRA_LIMIT		150 
//#define TUTORIAL_START_BRAHMAN_LIMIT	30

//#define QUEST_DIALOG_POSX	760
//#define QUEST_DIALOG_POSY	420

//#define QUEST_MESSAGE_NONE		0
//#define QUEST_MESSAGE_COMPLETE	1
//#define QUEST_MESSAGE_RECONFIRM	2

//#define TUTORIAL_QUEST_AGREE_1		1	// 초보자 퀘스트 승낙 여부 묻는 메세지창
//#define TUTORIAL_QUEST_AGREE_2		2	// 취소를 눌렀을 경우 다시 묻는 메세지창

#define TUTORIAL_5_TOTAL			10		// 믈렉차 숫자
#define SCENARIO_9_TOTAL			10		// 코브라 숫자
#define SCENARIO_10_TOTAL			10		// 아프라 바라하 라자 숫자
#define SCENARIO_11_1_TOTAL			30		// 울카무카 숫자
#define SCENARIO_11_2_TOTAL			15		// 울카무카 카우라 숫자
#define SCENARIO_14_TOTAL			30		// 헤루카 숫자
#define SCENARIO_24_TOTAL			20		// 아난가 숫자

#define TUTORIAL_5_STEP				3		// 바라하 라자 남은 숫자 보여주는 단계 번호
#define SCENARIO_9_STEP				4		// 마하 울카무카 라자 남은 숫자 보여주는 단계 번호
#define SCENARIO_10_STEP			4		// 마하 아프라 바라하 라자 남은 숫자 보여주는 단계 번호
#define SCENARIO_11_1_STEP			4		// 울카무카 남은 숫자 보여주는 단계 번호
#define SCENARIO_11_2_STEP			7		// 울카무카 카우라 남은 숫자 보여주는 단계 번호
#define SCENARIO_14_STEP			4		// 헤루카 남은 숫자 보여주는 단계 번호
#define SCENARIO_24_STEP			5		// 아난가 남은 숫자 보여주는 단계 번호

// 지나 퀘스트 몹잡는 부분
#define SCENARIO_26_STEP			5		// 자괴 남은 숫자 보여주는 단계 번호
#define SCENARIO_28_1_STEP			5		// 진모인 남은 숫자 보여주는 단계 번호
#define SCENARIO_28_2_STEP			8		// 진모인 거수 남은 숫자 보여주는 단계 번호
#define SCENARIO_30_STEP			8		// 귀화상 남은 숫자 보여주는 단계 번호

#define SCENARIO_26_TOTAL			28		// 자괴의 숫자
#define SCENARIO_28_1_TOTAL			10		// 진모인의 숫자
#define SCENARIO_28_2_TOTAL			15		// 진모인 거수의 숫자
#define SCENARIO_30_TOTAL			30		// 귀화상의 숫자

// 유배지 퀘스트 추가 (몹잡는 부분)
#define SCENARIO_33_STEP_START		5		
#define SCENARIO_33_STEP_END		56		
#define SCENARIO_33_TOTAL			10		

//#define QUEST_BN_FLASH_TIME						15

//#define _QUEST_MSG_FILE_PATH		_T("resource\\UI\\QuestMessage.cfg")

#define _QUEST_GENERAL_SOUND	33531

HTQuest::HTQuest(void) 
: m_pCompleteQuestHead(HT_NULL), m_pCompleteQuestTail(HT_NULL), m_pProgressQuestHead(HT_NULL), m_pProgressQuestTail(HT_NULL),
m_bIsInitChar(HT_FALSE)
{
	//m_iSlideNo	= -1;
	//m_bSlideOn	= HT_FALSE;
}

HTQuest::~HTQuest(void)
{
}

HTvoid HTQuest::HT_vQuest_CleanUp()
{
	//HT_vQuest_DeleteAllHistory();
}

HTvoid HTQuest::HT_vQuest_Init()
{
}

//---------튜토리얼 메시지 로딩----------//
HTvoid HTQuest::HT_vQuest_TutorialMsgLoading()
{
}

//----------활성화 / 비활성화----------//
HTvoid HTQuest::HT_vQuest_ActiveSw()
{
	if( m_bQuest_WindowActiveSw == HT_TRUE )	
	{
		// 비활성화
		m_bQuest_WindowActiveSw = HT_FALSE;
		g_cUIManager->HT_HideWindow(_DIALOG_QUEST);
	}
	else
	{
		// 퀘스트 버튼이 깜박거리고 있으면 정지
		g_cUIManager->HT_SetButtonControlState( _DIALOG_MAINBAR, 4, 0 );	// 노말 상태로 만들어줌

		// 활성화
		m_bQuest_WindowActiveSw = HT_TRUE;

		g_cUIManager->HT_ShowWindow(_DIALOG_QUEST);
		g_pEngineHandler->HT_hrPlaySound( _QUEST_GENERAL_SOUND, 1 );	// Click Sound
	}
}

//	ESC Key 누르면 창 닫기
HTvoid HTQuest::HT_vQuest_ESC_CloseWindow()
{
	g_cUIManager->HT_HideWindow(_DIALOG_QUEST);
	/*
	m_bQuest_WindowActiveSw = HT_TRUE;

	HT_vQuest_ActiveSw();
	*/
}

// "특정 차크라 올리기" 퀘스트의 파라미터 설정
HTvoid HTQuest::HT_vQuest_GetChakraText(CHTString& rszChakra)
{/*
	HTshort tribe = g_oMainCharacterInfo.snTribe;
	HTint idMessage = eMsgNone;
	switch( (tribe-1)%4 )
	{
		case 0:	// 나가/긴나라
			idMessage = eMsgCommonChakraMuscle; // 근육
			break;
		case 1:	// 아수라/락샤사
			idMessage = eMsgCommonChakraHeart; // 심장
			break;
		case 2:	// 약샤/간달바
			idMessage = eMsgCommonChakraNerve; // 신경
			break;
		case 3:	// 데바/가루라
			idMessage = eMsgCommonChakraMind; // 정신
			break;
		default:
			break;
	}

	if( idMessage != eMsgNone )
		g_pMessageMgr->HT_bGetMessage( idMessage, &rszChakra );*/
}
 
// 퀘스트 한곳에서만 사용함.추후에 다른 파라미터가 들어간다면 수정해야함.2003.04.17
HTvoid HTQuest::HT_vQuest_SetChakraParam(CHTString& szQuestText, CHTString& rszReturnText)
{
}

//---------선택한 진행퀘스트의 단계를 반환---------//
HTvoid HTQuest::HT_vGetQuestStep(HTint nDlgNo, BYTE byType, HTint nSelect, HTint& nIndex, HTint& nStep)
{
}

// 현재 퀘스트창에서 마지막으로 선택한 RadioNo를 저장해놓는다 
HTvoid HTQuest::HT_vSetSelectRadioNo(BYTE byType, HTint nSelect)
{
}

// 현재 퀘스트창에서 마지막으로 선택한 SlideNo를 저장해놓는다 
HTvoid HTQuest::HT_vSetSlideNo(BYTE byType)
{
}

HTvoid HTQuest::HT_hrMouseLbuttonDown(HTPoint pPt)
{
}

//----------인벤토리 활성화일 때 마우스 체크-마우스가 인벤토리 안에 있는지 체크----------//
HTvoid HTQuest::HT_vMouseCheck( HTPoint pPt )
{
}

// 슬라이드바의 Up버튼 클릭시 설명창 내용 갱신
HTbool HTQuest::HT_vQuest_SlideDown(BYTE byType)
{
	return HT_OK;
}

// 슬라이드바의 Down버튼 클릭시 설명창 내용 갱신
HTbool HTQuest::HT_vQuest_SlideUp(BYTE byType)
{
	return HT_OK;
}

// 재확인 메세지 창
HTRESULT HTQuest::HT_hrQuest_Confirm_Message( HTint iProp, HTint iInductNo, HTint iButtonNo )
{
	return HT_FAIL;
}

// 완료메세지 창
HTRESULT HTQuest::HT_hrQuest_DialogBoxCheck( HTint iProp, HTint iInductNo )
{
	return HT_FAIL;
}

//----------퀘스트 창에 퀘스트 제목 출력----------//
HTvoid HTQuest::HT_vQuest_SetQuestTitle(BYTE byType, BYTE byQuestIndex, HTint nRadioNo)
{
}
 
//---------- 진행/완료 퀘스트 창의 선택된 목록의 설명을 출력한다 ------------//
HTvoid	HTQuest::HT_vQuest_SetText(BYTE byType)
{
}

// 선택한 퀘스트에 대한 설명 설정
HTvoid HTQuest::HT_vQuest_SetInfoText(HTint nDlgNo, BYTE byType, HTint nIndex, HTint nStep)
{
}

//--------- 초보/시나리오/의뢰 창에 등록된 목록개수를 얻어온다 ----------//
HTint HTQuest::HT_nQuest_GetListCount(HTint nDlgNo, BYTE byType)
{
	return 0;
}

//--------- 원하는 목록이 보이도록 슬라이드 조정 -----------//
HTvoid HTQuest::HT_vQuest_SetSlidePos( HTint nDlgNo, BYTE byType, HTint nRadioNo )
{
}

HTvoid HTQuest::HT_vQuest_SetSlidePos( HTint nDlgNo, BYTE byType, HTint iSlideVal, HTint nRadioNo )
{
}

//----------모든 퀘스트 히스토리 정보를 지운다----------//
HTvoid HTQuest::HT_vQuest_DeleteAllHistory()
{
}

//----------새로운 히스토리를 마지막에 넣는다.---------//
HTvoid HTQuest::HT_vQuest_InsertCompleteHistory(HT_QUEST_LIST* pNew)
{
}

HTvoid HTQuest::HT_vQuest_InsertProgressHistory(HT_QUEST_LIST* pNew)
{
}

//----------특정 히스토리를 지운다.-----------//
HT_QUEST_LIST* HTQuest::HT_psQuest_DelProgressHistory(HT_QUEST_LIST* pData)
{
	return 0;
}

//------------- 네트워크 관련 ---------------//
// 캐릭터의 quest history 세부정보
HTvoid HTQuest::HT_vQuest_History_Init( )
{
}

HTvoid HTQuest::HT_vNetWork_SCP_RESP_Quest_History( HTbyte byQuest[MAX_EVENT_FLAG] )
{
	// v3에서 따로 읽음
	g_cUIQuestWindow->HT_vNetWork_SCP_RESP_Quest_History(byQuest);
}

//----------튜토리얼 퀘스트 수행 여부를 서버로 전송---------//
HTvoid HTQuest::HT_vNetWork_CSP_REQ_Quest_DIALOG(DWORD dwDialogIndex, BYTE byResult)
{
	g_cUIQuestWindow->HT_vNetWork_CSP_REQ_Quest_DIALOG(dwDialogIndex, byResult);
}

//-------------퀘스트 관련 에러 정보---------------//
HTvoid HTQuest::HT_vNetWork_SCP_RESP_Quest_Dialog( PS_SCP_QUEST_DIALOG info )
{
	g_cUIQuestWindow->HT_vNetWork_SCP_RESP_Quest_Dialog(info);
}

HTvoid HTQuest::HT_vMouseSlideBarMove()
{
}

HTvoid HTQuest::HT_vMouseSlideBarUp()
{
}