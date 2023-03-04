#pragma once

class HTTutorialSystem
{
public:
	HTTutorialSystem(void);
	~HTTutorialSystem(void);

	//--------------------------------------------------------------
	// HTvoid				HT_Tutorial_SetInit()
	// D : 튜토리얼 시스템 초기 셋팅
	//--------------------------------------------------------------
	HTvoid				HT_vInit();
	//	Create Window
	HTvoid				HT_vHelp_CreateWindow();
	//	입력함수 처리 선택 도움말1
	static void HT_vHelp_InputCheckHelp1(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 선택 도움말2
	static void HT_vHelp_InputCheckHelp2(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 선택 도움말3
	static void HT_vHelp_InputCheckHelp3(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 선택 도움말4
	static void HT_vHelp_InputCheckHelp4(int iAction, int iTarget, int iTargetID);

	//	입력함수 처리 튜토리얼
	static void HT_vTutorial_InputCheckTutorialWnd(int iAction, int iTarget, int iTargetID);

	//	메시지 로딩
	//HTvoid				HT_Tutorial_MsgLoading( CHTString strList );
	//	튜토리얼 시스템 컨트롤
	HTbool				HT_bTutorialControl();
	
	//--------------------------------------------------------------
	// HTvoid	HT_vStartTutorial();
	// D : 튜토리얼 시스템을 시작한다.
	//--------------------------------------------------------------
	HTvoid				HT_vStartTutorial();
	
	//--------------------------------------------------------------
	// HTbool	HT_bTutorial_DlgCheck( HTint iDlgNo, HTPoint pPt)
	// D : 튜토리얼 다이알로그 입력 체크
	// I : iDlgNo - 다이알로그 번호, pPt - 좌표
	//--------------------------------------------------------------
	HTbool				HT_bTutorial_DlgCheck( HTint iDlgNo, HTPoint pPt);

	//--------------------------------------------------------------
	// HTint				HT_iGetTutorialStep()
	// D : 튜토리얼 단계 얻기
	// R : 튜토리얼 단계
	//--------------------------------------------------------------
	HTint				HT_iGetTutorialStep() { return m_iTutorialStep; };

	//	튜토리얼 단계 체크
	HTvoid				HT_Tutorial_StepCheck();

	//	튜토리얼 시스템이 모두 끝내고 튜토리얼 퀘스트로 넘김
	HTvoid				HT_Tutorial_StepCheck_End_Quest();

	//	도움말 기능_켜기
	HTvoid				HT_vTutorial_SetHelpWnd();
	//	도움말 기능_끄기
	HTvoid				HT_vTutorial_DelHelpWnd();

	//========================//
	//	반환값				  //
	//========================//
	BYTE				HT_bTutorial_TrainendSw()	{	return m_byTutorialSystem_TrainendSw;	};
	HTbool				HT_bTutorial_HelpWnd()		{	return m_bHelpWindowSw;					};

	//========================//
	//	서버에서 메시지 받기  //
	//========================//
	//HTvoid				HT_vNetWork_SCP_RESP_Quest_HistoryInfoData_Save( PS_QUEST_HISTORY_INFO info, HTint nRemainder );
	HTvoid				HT_vNetWork_SCP_RESP_Quest_HistoryInfoData_Save( HTbyte byQuest[MAX_EVENT_FLAG] );
	//========================//
private:
	//-------------------------------------------------------
	//HTvoid				HT_vUpdateUI(HTint iStep);
	// D : Step에 따라 UI를 변경한다.
	// I : 튜토리얼 단계
	//-------------------------------------------------------
	HTvoid				HT_vUpdateUI(HTint iStep);

	//-------------------------------------------------------
	// HTbool				HT_bMoveTutorial();
	// D : 이동에 관한 튜토리얼 진행시 완료 체크
	//-------------------------------------------------------
	HTbool				HT_bMoveTutorial();

	//-------------------------------------------------------
	// HTbool				HT_bChangeViewTutorial()
	// D : 뷰 변경 튜토리얼 진행시 완료 체크
	//-------------------------------------------------------
	HTbool				HT_bChangeViewTutorial();

	//-------------------------------------------------------
	// HTbool				HT_bChangeMiniMapTutorial()
	// D : 미니맵 크기 변경 튜토리얼 진행시 완료 체크
	//-------------------------------------------------------
	HTbool				HT_bChangeMiniMapTutorial();

	//-------------------------------------------------------
	// HTbool				HT_bEquipBasicWeaponTutorial()
	// D : 기본무기 장착 튜토리얼 진행시 완료 체크
	//-------------------------------------------------------
	HTbool				HT_bEquipBasicWeaponTutorial();

public:
	//-------------------------------------------------------
	// HTvoid				HT_vAddTutorialStep()
	// D : 튜토리얼 단계를 증가시킨다.
	//-------------------------------------------------------
	HTvoid				HT_vAddTutorialStep(HTint iStep);

public:

	//	현재의 단계
	HTint				m_iTutorialStep;

	// [ Move Tutorial ] 관련 변수들
	HTbool				m_bStartMoveTutorial;
	HTvector3			m_vecStartMovePos;
	HTvector3			m_vecPrevPos;
	HTvector3			m_vecCurPos;
	HTfloat				m_fMoveDistance;

	// [ Change View ] 관련 변수들
	HTbool				m_bStartViewTutorial;
	HTfloat				m_fLookAngle;
	HTfloat				m_fPrevAngle;
	HTfloat				m_fCurAngle;

	// [ MiniMap ] 관련 변수
	HTint				m_iMiniMapStatus;

	CHTString			m_strStepName[29];

	HTbool				m_bTutorial_IconSw;			//	아이콘의 활성화 여부
	HTbool				m_bTutorial_IconShowSw;		//	아이콘의 반짝이기
	DWORD				m_dwTutorial_IconDelay;		//	아이콘의 반짝이는 간격조절
	BYTE				m_byTutorial_IconShowCount;	//	아이콘 반짝이는 횟수

	HTbool				m_bTutorialOn;	//	튜토리얼 시스템을 수행하는지 여부
	HTbool				m_bTutorialSystem_TrainStepResult;	//	튜토리얼 시스템을 단계별 수행 여부
	BYTE				m_byTutorialSystem_TrainendSw;	//	튜토리얼 시스템을 완료했는지 조사 0:하지않음,1:예약,2:완료
	//	시점변환 가이드 체크
	HTfloat				m_fEyeLookAngle;
	HTfloat				m_fEyeLookDistance;
	//	헬프 윈도우
	HTbool				m_bHelpWindowSw;
	//	퀘스트 정보 저장1
	HTbyte				m_arrQuestInfo[MAX_EVENT_FLAG];

};
