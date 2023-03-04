#ifndef _HTQuest_h_
#define _HTQuest_h_

typedef struct _HT_QUEST
{
	BYTE		byIndex;	// 퀘스트 번호
	BYTE		byStep;		// 퀘스트 내 현재 진행 단계
} HT_QUEST;

typedef struct _HT_QUEST_LIST
{
	BYTE		byDlg;		// 초보자/시나리오/의뢰 구분
	HT_QUEST	sQuest;

	CHTString	szResult;		
	_HT_QUEST_LIST* pNext;
} HT_QUEST_LIST;

//#define	QUEST_MAX_NUM					60	//37
#define QUEST_DESCRIPTION_MAXNUM		60	// 한 퀘스트의 최대 진행 단계

#define HT_MOB_COUNT_INDEX_MAX			60	// 현재 진행 중인 퀘스트 중 잡은 몬스터 수를 세야하는 퀘스트 
#define MOB_COUNT_QUEST_INDEX_START		91	// 잡는 몹의 숫자를 받을 때 사용되는 퀘스트 index
#define MOB_COUNT_QUEST_INDEX_END		94
/*
typedef struct _HT_QUEST_DESCRIPTION
{
	BYTE		byIndex;		// 퀘스트 번호
	CHTString	szTitle;		// 퀘스트 제목
	HTint		nStepNo;		// 단계 개수
	HTint		nStepNum[QUEST_DESCRIPTION_MAXNUM];		// 단계
	CHTString	szStepMsg[QUEST_DESCRIPTION_MAXNUM];	// 단계별 UI창에 나타내는 말
} HT_QUEST_DESCRIPTION;
*/
class HTQuest
{
public:
	HTQuest(void);
	~HTQuest(void);
	HTvoid				HT_vQuest_CleanUp();

	HTvoid				HT_vQuest_Init();
	
	// 튜토리얼 메시지 로딩
	HTvoid				HT_vQuest_TutorialMsgLoading();

	//	ESC Key 누르면 창 닫기
	HTvoid				HT_vQuest_ESC_CloseWindow();

	//------------------------------------------------
	// 셋팅/반환
	//------------------------------------------------
	// 활성화 체크
	HTbool				HT_bQuest_GetActiveSw()	{	return m_bQuest_WindowActiveSw;	};
	// 활성화 / 비활성화
	HTvoid				HT_vQuest_ActiveSw();
	
	// 초보/시나리오/의뢰 창에 등록된 목록개수를 얻어온다
	HTint				HT_nQuest_GetListCount(HTint nDlgNo, BYTE byType);
	// 선택한 퀘스트의 단계를 반환
	HTvoid				HT_vGetQuestStep(HTint nDlgNo, BYTE byType, HTint nSelect, HTint& nIndex, HTint& nStep);
	//------------------------------------------------
	// 마우스 클릭에 따른 창 관리
	//------------------------------------------------
	HTvoid				HT_vMouseCheck( HTPoint pPt/*, HTbool bType*/ );
	HTvoid				HT_hrMouseLbuttonDown(HTPoint pPt);
	// 재확인 메세지 창
	//HTRESULT			HT_hrQuest_Confirm_Message(HTPoint pPt, HTint iProp);
	HTRESULT			HT_hrQuest_Confirm_Message( HTint iProp, HTint iInductNo, HTint iButtonNo );
	// 완료메세지 창
	//HTRESULT			HT_hrQuest_DialogBoxCheck(HTPoint pPt, HTint iProp);
	HTRESULT			HT_hrQuest_DialogBoxCheck( HTint iProp, HTint iInductNo );

	HTvoid				HT_vQuest_SetIsInitChar(HTbool bInitChar) { m_bIsInitChar = bInitChar; }

	// 퀘스트 목록창 스크롤
//	HTvoid				HT_vQuest_QuestTitleScroll(BYTE byType);
	// 현재 퀘스트창에서 마지막으로 선택한 RadioNo를 저장해놓는다 
	HTvoid				HT_vSetSelectRadioNo(BYTE byType, HTint nSelect);
	// 현재 퀘스트창에서 마지막으로 선택한 SlideNo를 저장해놓는다 
	HTvoid				HT_vSetSlideNo(BYTE byType);

	// 슬라이드바의 Up버튼 클릭시 설명창 내용 갱신
	HTbool				HT_vQuest_SlideDown(BYTE byType);
	// 슬라이드바의 Down버튼 클릭시 설명창 내용 갱신
	HTbool				HT_vQuest_SlideUp(BYTE byType);

	// 진행/완료 퀘스트 창의 모든 목록을 출력한다
	HTvoid				HT_vQuest_SetText(BYTE byType);
	// 퀘스트 창에 퀘스트 제목 출력
	HTvoid				HT_vQuest_SetQuestTitle(BYTE byType, BYTE byQuestIndex, HTint nRadioNo);
	// 선택한 퀘스트에 대한 설명 설정
	HTvoid				HT_vQuest_SetInfoText(HTint nDlgNo, BYTE byType, HTint nIndex, HTint nStep=1);
	
	//---------------------------------------------------
	// 퀘스트창 데이터 관리
	//---------------------------------------------------
	HTvoid				HT_vQuest_History_Init( );

	// 모든 퀘스트 히드토리 정보를 지운다
	HTvoid				HT_vQuest_DeleteAllHistory();
	// 새로운 히스토리를 마지막에 넣는다.
	HTvoid				HT_vQuest_InsertCompleteHistory(HT_QUEST_LIST* pNew);
	HTvoid				HT_vQuest_InsertProgressHistory(HT_QUEST_LIST* pNew);
	// 특정 히스토리를 지운다
	HT_QUEST_LIST*		HT_psQuest_DelProgressHistory(HT_QUEST_LIST* pData);
	
	// 원하는 목록이 보이도록 슬라이드 조정
	HTvoid				HT_vQuest_SetSlidePos( HTint nDlgNo, BYTE byType, HTint nRadioNo );
	HTvoid				HT_vQuest_SetSlidePos( HTint nDlgNo, BYTE byType, HTint iSlideVal, HTint nRadioNo );
	
	// 몹을 일정수 잡아야하는 퀘스트 단계일 경우 잡은 몬스터 수 세는 변수 초기화
	HTvoid				HT_vInit_MonsterCount();

	//-------------------------------------------------------------
	// 네트워크 관련 함수
	//-------------------------------------------------------------
	// 튜토리얼 퀘스트 수행 여부를 서버로 전송
	HTvoid				HT_vNetWork_CSP_REQ_Quest_DIALOG(DWORD dwDialogIndex, BYTE byResult);
	// quest history 정보 전송 결과
	HTvoid				HT_vNetWork_SCP_RESP_Quest_History(PS_SCP_RESP_QUEST_HISTORY info);
	HTvoid				HT_vNetWork_SCP_RESP_Quest_History( HTbyte byQuest[MAX_EVENT_FLAG] );
	// 캐릭터의 quest history 세부정보
	HTvoid				HT_vNetWork_SCP_RESP_Quest_HistoryInfo(PS_QUEST_HISTORY_INFO info, HTint nRemainder);
	// 퀘스트 관련 에러 정보
	HTvoid				HT_vNetWork_SCP_RESP_Quest_Dialog(PS_SCP_QUEST_DIALOG info);

	// 퀘스트 한곳에서만 사용함.추후에 다른 파라미터가 들어간다면 수정해야함.2003.04.17
	// "특정 차크라 올리기" 퀘스트의 파라미터 설정
	HTvoid				HT_vQuest_GetChakraText(CHTString& rszChakra);
	HTvoid				HT_vQuest_SetChakraParam(/*HTint nIndex,*/CHTString& szQuestText, CHTString& rszReturnText);

	HTvoid				HT_vMouseSlideBarMove();
	HTvoid				HT_vMouseSlideBarUp();

public:
	HTbool						m_bQuest_WindowActiveSw;
	HTint						m_nQuest_WindowImageID;
	HTvector3					m_vecQuest_WindowPos;
	
	//----------- 퀘스트 관련 ------------//
	HT_QUEST_LIST*				m_pCompleteQuestHead;	// 완료된 퀘스트
	HT_QUEST_LIST*				m_pCompleteQuestTail;
	HTint						m_nCompleteQuestNum;
	// 이전 히스토리와의 차이를 구분하기 위해
	HTbyte						m_byCompleteQuestAlteration[QUEST_MAX_NUM];
	HTbool						m_bCompleteFx;	// 완료 이펙트를 보여줘야하는지..
	HTint						m_iLastCompleteQuestNum; // 이전 완료 퀘스트 인덱스

	HT_QUEST_LIST*				m_pProgressQuestHead;	// 진행중인 퀘스트
	HT_QUEST_LIST*				m_pProgressQuestTail;
	HTint						m_nProgressQuestNum;
	
	// 마지막 히스토리가 있는 창으로 설정하기 위해 사용
	//BYTE						m_byLastHistroyIndex;	// 마지막 히스토리의 퀘스트 index
	//BYTE						m_byLastHistoryVal;		// 마지막 히스토리 퀘스트 step
	
	BYTE						m_byNoviceSelNo;
	BYTE						m_byNoviceSlideNo;
	BYTE						m_byScinarioSelNo;
	BYTE						m_byScinarioSlideNo;
	BYTE						m_byRequestSelNo;
	BYTE						m_byRequestSlideNo;

	HTint						m_nLastDlg;					// 마지막으로 선택한 탭 번호(탭마다 Dlg가 분리되어있음)
	HTint						m_nLastProgressSlideVal;
	HTint						m_nLastCompleteSlideVal;

	HT_QUEST_DESCRIPTION		m_sQuestText[QUEST_MAX_NUM];	// 퀘스트 이름과 단계별 설명
	HTint						m_nRemainderNum[HT_MOB_COUNT_INDEX_MAX]; // 몹 잡기 퀘스트에서 잡은 몹 숫자
	HTint						m_nRemainderNum_2[HT_MOB_COUNT_INDEX_MAX];

	//--------- 메세지 창에 대한 정보 -------------//
	BYTE						m_byMessageWin;			//  현재 메세지창
	CHTString					m_szMessage;			//  현재 메세지창에 보여줄 내용
	BYTE						m_byQuestAgreeTime;		// 초보자 퀘스트 승낙여부 묻는 메세지창 띄운 횟수

private:
	HTint						m_iSlideNo;
	HTbool						m_bSlideOn;

	HTbool						m_bIsInitChar;		// 로그인/포탈이동시 내려오는 히스토리에 의한 버튼 깜박임을 안하기 위해서
	// 현재 진행 중인 퀘스트 중 잡은 몬스터 수를 세야하는 퀘스트 정보 관련
	HTbyte						m_byMobCountIndex[HT_MOB_COUNT_INDEX_MAX];
	HTbyte						m_byMobCountVal[HT_MOB_COUNT_INDEX_MAX]; 
	HTbyte						m_byMobCountIndexNum;
};
#endif // #ifndef _HTQuest_h_