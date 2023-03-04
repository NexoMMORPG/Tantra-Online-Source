#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "httutorialsystem.h"

#define TUTORIALSYSTEM_NONE				0
#define TUTORIALSYSTEM_RESERVED			1
#define TUTORIALSYSTEM_END				2

#define _MOVETUTORIAL_DIST				500.0f
#define _VIEWTUTORIAL_ANGLE				0.5f


HTTutorialSystem::HTTutorialSystem()
{
	//	현재의 단계
	m_iTutorialStep			= 0;

	m_bStartMoveTutorial	= HT_FALSE;
	m_fMoveDistance			= 0.0f;
	
	m_bStartViewTutorial	= HT_FALSE;
	m_fLookAngle			= 0.0f;
	m_fPrevAngle			= 0.0f;	
	m_fCurAngle				= 0.0f;

	//	아이콘의 활성화 여부
	m_bTutorial_IconSw = HT_FALSE;
	//	아이콘의 반짝이기
	m_bTutorial_IconShowSw = HT_FALSE;
	//	아이콘의 반짝이는 간격조절
	m_dwTutorial_IconDelay = GetTickCount();
	//	튜토리얼 퀘스트를 수행하는지 여부
	m_bTutorialOn = HT_FALSE;
	//	튜토리얼 시스템을 완료했는지 조사
	m_byTutorialSystem_TrainendSw = TUTORIALSYSTEM_NONE;
	//	헬프 윈도우
	m_bHelpWindowSw = HT_FALSE;
}

HTTutorialSystem::~HTTutorialSystem(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_HELPWND_1 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_HELPWND_2 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_HELPWND_3 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_HELPWND_4 );
	
	// 튜토리얼
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_1 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_2 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_3 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_4 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_5 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_6 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_7 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_8 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_9 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_10 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_11 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_12 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_13 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_TUTORIALWND_14 );
}

//	튜토리얼 시스템 초기 셋팅
HTvoid HTTutorialSystem::HT_vInit()
{
	this->HT_vHelp_CreateWindow();
}

//	Create Window
HTvoid HTTutorialSystem::HT_vHelp_CreateWindow()
{
	//	메시지 셋팅
	CHTString strMessage;
	CHTString strTemp;
	//	[_DIALOG_HELPWND_1]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_HELPWND_1, _T(""), 329, 465, g_cTutorialSystem->HT_vHelp_InputCheckHelp1, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_HELPWND_1, 5 );
	//	줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_HELPWND_1, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button 행동관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte1, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_1, 1, 9, 17, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_1, 1 );
	//	Button 퀵슬롯바
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte2, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_1, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_1, 2 );
	//	Button 채팅관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte3, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_1, 3, 9, 169, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_1, 3 );
	//	Button 윈도우관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte4, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_1, 4, 9, 245, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_1, 4 );
	//	도움말
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoForward, &strMessage, _T(""), _T("") );	// 전 : W
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 90, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 10,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoLeft, &strMessage, _T(""), _T("") );	// 좌 : A
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 110, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 11,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoRight, &strMessage, _T(""), _T("") );	// 우 : D
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 130, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 12,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoRun, &strMessage, _T(""), _T("") );	// 달리기 / 걷기 : Z
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 150, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 13,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoSitDown, &strMessage, _T(""), _T("") );	// 앉기 / 서기 : X
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 14, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 170, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 14,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoCamera, &strMessage, _T(""), _T("") );	// 카메라 고정 : F12
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 15, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 190, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 15,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoDefaultCamera, &strMessage, _T(""), _T("") );	// 카메라 기본 시점 : Instert, 마우스 휠 버튼
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 16, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 210, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 16,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoPointView, &strMessage, _T(""), _T("") );	// 1인칭,3인칭 전환 : F11
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 17, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 230, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 17,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoZoomIn, &strMessage, _T(""), _T("") );	// 줌 인 -
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 18, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 250, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 18,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoZoomOut, &strMessage, _T(""), _T("") );	// 줌 아웃+
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 19, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 270, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 19,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoLeft2, &strMessage, _T(""), _T("") );	// 카메라 좌 회전 : <-
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 290, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 20,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoRight2, &strMessage, _T(""), _T("") );	// 카메라 우 회전 : ->
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 21, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 310, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 21,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoSelectTarget, &strMessage, _T(""), _T("") );	// 가까운 적 선택 : E
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 22, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 330, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 22,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoAttack, &strMessage, _T(""), _T("") );	// 공격 : R
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 23, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 350, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 23,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoPickUp, &strMessage, _T(""), _T("") );	// 줍기 : F
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 24, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 370, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 24,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoSelectMember, &strMessage, _T(""), _T("") );	// 근접한 동료 선택 : T
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 25, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 390, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 25,  7 );

	//	[_DIALOG_HELPWND_2]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_HELPWND_2, _T(""), 329, 465, g_cTutorialSystem->HT_vHelp_InputCheckHelp2, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_HELPWND_2, 5 );
	//	줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_HELPWND_2, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button 행동관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte1, &strMessage, _T(""), _T("") );	//	행동관련
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_2, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_2, 1 );
	//	Button 퀵슬롯바
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte2, &strMessage, _T(""), _T("") );	//	퀵슬롯바
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_2, 2, 9, 93, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_2, 2 );
	//	Button 채팅관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte3, &strMessage, _T(""), _T("") );	//	채팅관련
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_2, 3, 9, 169, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_2, 3 );
	//	Button 윈도우관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte4, &strMessage, _T(""), _T("") );	//	윈도우관련
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_2, 4, 9, 245, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_2, 4 );
	//	도움말
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoPreviousQuick, &strMessage, _T(""), _T("") );	//	이전퀵바 : Page Up
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 90, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 11,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoNextQuick, &strMessage, _T(""), _T("") );	//	다음퀵바 : Page Down
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 110, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 12,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickBar1, &strMessage, _T(""), _T("") );	//	퀵바 1선택 : F1/Shift+1
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 130, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 13,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickBar2, &strMessage, _T(""), _T("") );	//	퀵바 2선택 : F2/Shift+2
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 14, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 150, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 14,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickBar3, &strMessage, _T(""), _T("") );	//	퀵바 3선택 : F3/Shift+3
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 15, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 170, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 15,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickBar4, &strMessage, _T(""), _T("") );	//	퀵바 4선택 : F4/Shift+4
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 16, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 190, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 16,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickBar5, &strMessage, _T(""), _T("") );	//	퀵바 5선택 : F5/Shift+5
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 17, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 210, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 17,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot1, &strMessage, _T(""), _T("") );	//	퀵바 슬롯1 사용 : 1
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 18, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 230, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 18,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot2, &strMessage, _T(""), _T("") );	//	퀵바 슬롯2 사용 : 2
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 19, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 250, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 19,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot3, &strMessage, _T(""), _T("") );	//	퀵바 슬롯3 사용 : 3
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 270, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 20,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot4, &strMessage, _T(""), _T("") );	//	퀵바 슬롯4 사용 : 4
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 21, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 290, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 21,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot5, &strMessage, _T(""), _T("") );	//	퀵바 슬롯5 사용 : 5
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 22, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 310, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 22,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot6, &strMessage, _T(""), _T("") );	//	퀵바 슬롯6 사용 : 6
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 23, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 330, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 23,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot7, &strMessage, _T(""), _T("") );	//	퀵바 슬롯7 사용 : 7
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 24, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 350, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 24,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot8, &strMessage, _T(""), _T("") );	//	퀵바 슬롯8 사용 : 8
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 25, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 370, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 25,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot9, &strMessage, _T(""), _T("") );	//	퀵바 슬롯9 사용 : 9
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 26, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 390, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 26,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot0, &strMessage, _T(""), _T("") );	//	퀵바 슬롯10 사용 : 10
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 27, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 410, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 27,  7 );

	//	[_DIALOG_HELPWND_3]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_HELPWND_3, _T(""), 329, 465, g_cTutorialSystem->HT_vHelp_InputCheckHelp3, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_HELPWND_3, 5 );
	//	줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_HELPWND_3, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button 행동관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte1, &strMessage, _T(""), _T("") );	//	행동관련
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_3, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_3, 1 );
	//	Button 퀵슬롯바
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte2, &strMessage, _T(""), _T("") );	//	퀵슬롯바
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_3, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_3, 2 );
	//	Button 채팅관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte3, &strMessage, _T(""), _T("") );	//	채팅관련
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_3, 3, 9, 169, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_3, 3 );
	//	Button 윈도우관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte4, &strMessage, _T(""), _T("") );	//	윈도우관련
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_3, 4, 9, 245, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_3, 4 );
	//	도움말
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoWholeChat, &strMessage, _T(""), _T("") );	//	전체대화 : /전체,/전,/s
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 90, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 10,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoWhisper, &strMessage, _T(""), _T("") );	//	귓속말 : /귓,/w
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 110, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 11,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoPartyChat, &strMessage, _T(""), _T("") );	//	파티 대화 : /파티,/파,/g
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 130, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 12,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoAshuramChat, &strMessage, _T(""), _T("") );	//	아쉬람 대화 : /아쉬람,/아,/gc
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 150, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 13,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoRegisterAddress, &strMessage, _T(""), _T("") );	//	친구 등록 : /친구등록 대상
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 14, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 170, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 14,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoResponseWhisper, &strMessage, _T(""), _T("") );	//	귓속말 응답 : /v
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 15, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 190, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 15,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoActiveChat, &strMessage, _T(""), _T("") );	//	채팅창 활성 : Enter
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 16, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 210, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 16,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoAshuramMemberGrade, &strMessage, _T(""), _T("") );	//	아쉬람 구성원 등급 변경 : /아쉬람등급 이름 등급
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 17, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 230, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 17,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoAshuramNotify, &strMessage, _T(""), _T("") );	//	아쉬람 공지 사항 변경 : /공지사항 공지내용
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 18, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 250, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 18,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyChangeChatWndStyle, &strMessage, _T(""), _T("") );	//	채팅창 스타일 변경 : =
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 19, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 270, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 19,  7 );

	//	[_DIALOG_HELPWND_4]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_HELPWND_4, _T(""), 329, 465, g_cTutorialSystem->HT_vHelp_InputCheckHelp4, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_HELPWND_4, 5 );
	//	줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_HELPWND_4, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button 행동관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte1, &strMessage, _T(""), _T("") );	//	행동관련
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_4, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_4, 1 );
	//	Button 퀵슬롯바
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte2, &strMessage, _T(""), _T("") );	//	퀵슬롯바
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_4, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_4, 2 );
	//	Button 채팅관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte3, &strMessage, _T(""), _T("") );	//	채팅관련
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_4, 3, 9, 169, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_4, 3 );
	//	Button 윈도우관련
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte4, &strMessage, _T(""), _T("") );	//	윈도우관련
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_4, 4, 9, 245, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_4, 4 );
	//	도움말
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoCharacterInfo, &strMessage, _T(""), _T("") );	//	스테이터스 : L
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 90, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 10,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoInventory, &strMessage, _T(""), _T("") );	//	인벤토리 : I
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 110, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 11,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuest, &strMessage, _T(""), _T("") );	//	퀘스트 : U
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 130, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 12,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoSkill, &strMessage, _T(""), _T("") );	//	스킬 : K
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 150, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 13,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoOption, &strMessage, _T(""), _T("") );	//	옵션 : O
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 14, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 170, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 14,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoCommand, &strMessage, _T(""), _T("") );	//	커맨드 : C
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 15, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 190, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 15,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoGuild, &strMessage, _T(""), _T("") );	//	길드창 : G
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 16, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 210, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 16,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoAddress, &strMessage, _T(""), _T("") );	//	주소록 : J
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 17, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 230, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 17,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoHelp, &strMessage, _T(""), _T("") );	//	도움말 : H
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 18, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 250, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 18,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoBalloon, &strMessage, _T(""), _T("") );	//	풍선말 전환 : B
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 19, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 270, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 19,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoNameHide, &strMessage, _T(""), _T("") );	//	이름 숨기기 : N
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 290, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 20,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoUIHide, &strMessage, _T(""), _T("") );	//	윈도우 모드 숨기기 : Tab
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 21, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 310, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 21,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoMiniMap, &strMessage, _T(""), _T("") );	//	미니맵 : M
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 22, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 330, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 22,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoScreenShot, &strMessage, _T(""), _T("") );	//	스크린샷 : PrintScreen
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 23, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 350, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 23,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoTrade, &strMessage, _T(""), _T("") );	//	교환 : /교환,/trade,/t
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 24, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 370, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 24,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoCloseWin, &strMessage, _T(""), _T("") );	//	창닫기 : Esc
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 25, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 390, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 25,  7 );

	//	[_DIALOG_TUTORIALWND_1]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_1, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_1, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle1, &strMessage, _T(""), _T("") );	//	첫인사
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_1, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_1, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_1, 1 );
	//	Button 명령 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_1, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand1, &strMessage, _T(""), _T("") );	//	[캐릭터 이동방법을 배운다.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_1, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_1, 2 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_1, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_1, 3, 7 );
	//	Text 설명
	if (g_oMainCharacterInfo.snTribe > 4)
	{
		g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep1_0+((g_oMainCharacterInfo.snTribe-4)*2-1), &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	족의 %s님 만다라 마을에 오신것을 진심으로 환영합니다.
	}
	else
	{
		g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep1_0+((g_oMainCharacterInfo.snTribe-1)*2), &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	족의 %s님 만다라 마을에 오신것을 진심으로 환영합니다.
	}

	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_1, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_1, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep1_8, &strMessage, _T(""), _T("") );	//	신목이 오늘따라 유난히 푸르르다 싶었는데 %s님을 맞이하게 되는군요. 영광입니다.
	strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_1, 5, strTemp.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_1, 5, 7 );

	//	[_DIALOG_TUTORIALWND_2]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_2, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_2, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle2, &strMessage, _T(""), _T("") );	//	캐릭터이동방법
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_2, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_2, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_2, 1 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_2, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_2, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep2_0, &strMessage, _T(""), _T("") );	//	자 그럼 이동 해볼까요?
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_2, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_2, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep2_1, &strMessage, _T(""), _T("") );	//	지면 저 멀리 마우스를 가져가 클릭해 보세요. 클릭을 했을 때 파란문양이 지면에 그려진다면 일단 성공!! 묽은 문얃이 그려진다면 그곳은 갈수 없는 곳이랍니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_2, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 180, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_2, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep2_2, &strMessage, _T(""), _T("") );	//	캐릭터를 이동해 보세요
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_2, 6, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_2, 6, 7 );

	//	[_DIALOG_TUTORIALWND_3]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_3, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_3, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle3, &strMessage, _T(""), _T("") );	//	포탈 정보
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_3, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_3, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_3, 1 );
	//	Button 명령 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_3, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand3, &strMessage, _T(""), _T("") );	//	[시점 변경을 배운다.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_3, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_3, 2 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_3, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_3, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s님 수고하셨습니다.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_3, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_3, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank2, &strMessage, _T(""), _T("") );	//	멋진 컨트롤이었습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_3, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 155, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_3, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep3_0, &strMessage, _T(""), _T("") );	//	달리기와 걷기 변경은 'Z'로 하게 되며 원거리 이동시엔 포탈을 사용하여 공간이동을 합니다. 포탈은 만다라 마을 중앙의 신목 뒤, 역마꾼 라훌에게 가보시면 됩니다. 하지만 먼 지역엔 강한 몬스터가 출현하므로 조심하셔야 합니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_3, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 180, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_3, 6, 7 );

	//	[_DIALOG_TUTORIALWND_4]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_4, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_4, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle4, &strMessage, _T(""), _T("") );	//	시점 변경
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_4, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_4, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_4, 1 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_4, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_4, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep4_0, &strMessage, _T(""), _T("") );	//	탄트라의 아름다운 하늘을 보신 적 있나요?
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_4, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_4, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep4_1, &strMessage, _T(""), _T("") );	//	시점 변경 방법을 배워서 아름다운 하늘을 감상해 보도록 하죠.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_4, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 170, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_4, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep4_2, &strMessage, _T(""), _T("") );	//	마우스 오른쪽 버튼을 누른 상태에서 마우스를 이동해 보세요. 시점을 앞뒤로 변경할 때는 마우스 스크롤 버튼을 돌리시면 됩니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_4, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 210, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_4, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep4_3, &strMessage, _T(""), _T("") );	//	시점을 변경해 보세요.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_4, 7, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_4, 7, 7 );

	//	[_DIALOG_TUTORIALWND_5]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_5, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_5, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle5, &strMessage, _T(""), _T("") );	//	시점 변경 기능키 설명
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_5, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_5, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_5, 1 );
	//	Button 명령 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_5, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand5, &strMessage, _T(""), _T("") );	//	[미니맵 사용법을 배운다.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_5, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_5, 2 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_5, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_5, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s님 수고하셨습니다.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_5, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_5, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank2, &strMessage, _T(""), _T("") );	//	멋진 컨트롤이었습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_5, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 155, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_5, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep5_0, &strMessage, _T(""), _T("") );	//	조금 더 알려 드리자면 'F11'키를 누르시면 1인칭, 3인칭으로 시점전환이 가능합니다. 시점 고정키는 'F12'이며, 마우스 중앙의 스크롤 버튼을 누르시면 기본 시접으로 전환됩니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_5, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_5, 6, 7 );

	//	[_DIALOG_TUTORIALWND_6]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_6, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_6, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle6, &strMessage, _T(""), _T("") );	//	미니맵 사용법
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_6, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_6, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_6, 1 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_6, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_6, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep6_0, &strMessage, _T(""), _T("") );	//	어디가 어딘지 분간이 안되신다구요? 미니맵을 이용하시면 지형을 쉽게 이해하실 수 있습니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_6, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_6, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep6_1, &strMessage, _T(""), _T("") );	//	미니맵에 보이는 화살표가 자신의 위치를 나타내며 진행방향에 따라 화살표가 회전하게 됩니다. 또한 더 큰 지도를 볼 수 있는데 미니맵의 크기를 변경하는 단축키는 키보드 'M'을 눌러 변경할 수 있습니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_6, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_6, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep6_2, &strMessage, _T(""), _T("") );	//	미니맵 크기를 바꿔 보세요.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_6, 6, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_6, 6, 7 );

	//	[_DIALOG_TUTORIALWND_7]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_7, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_7, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle7, &strMessage, _T(""), _T("") );	//	미니맵 아이콘
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_7, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_7, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_7, 1 );
	//	Button 명령 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_7, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand7, &strMessage, _T(""), _T("") );	//	[단축키 설명을 듣는다.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_7, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_7, 2 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_7, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_7, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s님 수고하셨습니다.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_7, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_7, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep7_0, &strMessage, _T(""), _T("") );	//	어디든지 갈수 있겠죠?\n좀더 자세한 설명을 드리자면 미니맵에 보이는 아이콘은 NPC에 대한 특징을 담고 있습니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_7, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 160, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_7, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep7_1, &strMessage, _T(""), _T("") );	//	위와 같은 특징을 가지고 있으므로 찿아 가실때 좀더 쉽게 찿을수 있고 미니맵 상단의 숫자들은 좌표를 표시하므로 참고하시면 친구를 찿을 때 보다 편리하실 것입니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_7, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 270, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_7, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep7_2, &strMessage, _T(""), _T("") );	//	무기점 방어구점  잡화점   창고
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_7, 7, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 245, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_7, 7, 7 );
	//	Image
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 23511, 20, 210 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 23512, 68, 210 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 23513, 115, 210 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 23514, 160,210 );

	//	[_DIALOG_TUTORIALWND_8]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_8, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_8, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle8, &strMessage, _T(""), _T("") );	//	단축키 활용
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_8, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_8, 1 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_8, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep8_0, &strMessage, _T(""), _T("") );	//	게임을 하실 때 자주 사용되는 단축키를 몇가지 설명 드리겠습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_8, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep8_1, &strMessage, _T(""), _T("") );	//	오른쪽 아래 보이는 아이콘은 각 기능의 단축키를 설정해 놓은 아이콘입니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 180, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_8, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep8_2, &strMessage, _T(""), _T("") );	//	'I'키를 눌러 인벤토리 창을 열고 기본무기를 장착해 보세요
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 210, 220, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_8, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep8_3, &strMessage, _T(""), _T("") );	//	아이템을 장착하는 방법은 마우스 커서를 아이템 위에 올려놓고 클릭하여 장착을 할 위치에 다시 클릭해 놓으시면 됩니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_8, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 260, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_8, 7, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep8_4, &strMessage, _T(""), _T("") );	//	기본 무기를 장착해 보세요
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 8, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_8, 8, 7 );
	//	Image
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 41, 22, 208 );

	//	[_DIALOG_TUTORIALWND_9]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_9, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_9, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle9, &strMessage, _T(""), _T("") );	//	단축키정보
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_9, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_9, 1 );
	//	Button 명령 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_9, 2, 159, 18, 425, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand9, &strMessage, _T(""), _T("") );	//	[몬스터 사냥법을 배운다.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 425, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_9, 2 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s님 수고하셨습니다.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 135, 186, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_0, &strMessage, _T(""), _T("") );	//	다른 단축키에 대한 설명을 드리겠습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 150, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_1, &strMessage, _T(""), _T("") );	//	'L'키를 눌러 캐릭터의 상세한 정보를 볼 수 있습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 170, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_2, &strMessage, _T(""), _T("") );	//	'I'키를 눌러 소지품 또는 장착 아이템을 확인 할 수 있습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 205, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 7, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_4, &strMessage, _T(""), _T("") );	//	'U'키를 눌러 퀘스트에 관련된 정보를 볼 수 있습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 8, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 240, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 8, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_3, &strMessage, _T(""), _T("") );	//	'K'키를 눌러 자신이 배운 기술들을 확인 할 수 있습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 9, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 275, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 9, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_6, &strMessage, _T(""), _T("") );	//	'ESC'키로 게임설정 또는 시스템 관련 설정을 변경 할 수 있습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 310, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 10, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_5, &strMessage, _T(""), _T("") );	//	'C'키로 명령어 관련 아이콘을 확인 할 수 있습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 345, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 11, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_7, &strMessage, _T(""), _T("") );	//	"플레이어를 강제적으로 공격할 수 있습니다.(PK는 살인행위이므로 상당한 불이익을 받게 됩니다.)
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 380, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 12, 7 );
	//	Image
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 38, 17, 170 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 41, 17, 205 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 44, 17, 240 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 47, 17, 275 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 50, 17, 310 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 53, 17, 345 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 56, 17, 380 );

	//	[_DIALOG_TUTORIALWND_10]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_10, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_10, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle10, &strMessage, _T(""), _T("") );	//	몬스터 사냥법
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_10, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_10, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_10, 1 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_10, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_10, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep10_0, &strMessage, _T(""), _T("") );	//	자, 몬스터 사냥을 해보시겠습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_10, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_10, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep10_1, &strMessage, _T(""), _T("") );	//	미니맵을 보면 마을 남쪽에 빨간색 화살표가 있습니다. 화살표 아래 길을 따라 마을을 나서면 몬스터들이 출현하는 곳으로 갈 수 있습니다. 몬스터를 한번 클릭하면 몬스터의 정보가 나오며 다시 한번 클릭하면 몬스터를 공격하게 됩니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_10, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_10, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep10_2, &strMessage, _T(""), _T("") );	//	바사붐 1마리를 사냥해 보세요.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_10, 6, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_10, 6, 7 );

	//	[_DIALOG_TUTORIALWND_11]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_11, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_11, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle11, &strMessage, _T(""), _T("") );	//	사냥법 응용
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_11, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_11, 1 );
	//	Button 명령 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_11, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand11, &strMessage, _T(""), _T("") );	//	[ITEM 줍는법을 배운다.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_11, 2 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_11, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s님 수고하셨습니다.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_11, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep11_0, &strMessage, _T(""), _T("") );	//	더 쉽게 사냥하는 방법을 알려드리겠습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 160, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_11, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep11_1, &strMessage, _T(""), _T("") );	//	명령어창을 열어보시면
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 58, 198, 230, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_11, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep11_2, &strMessage, _T(""), _T("") );	//	근접한 적을 찿는 아이콘이 있습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 58, 233, 220, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_11, 7, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep11_3, &strMessage, _T(""), _T("") );	//	아이콘을 클릭해서 퀵바에 올려놓고 근접한 몬스터를 쉽게 찿을 수 있습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 8, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 58, 255, 220, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_11, 8, 7 );
	//	Image
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 53, 22, 180 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 23818, 22, 215 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 23813, 22, 250 );

	//	[_DIALOG_TUTORIALWND_12]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_12, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_12, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle12, &strMessage, _T(""), _T("") );	//	아이템 줍는법
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_12, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_12, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_12, 1 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_12, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_12, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep12_0, &strMessage, _T(""), _T("") );	//	아이템 줍는법을 배워 보도록 하겠습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_12, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_12, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep12_1, &strMessage, _T(""), _T("") );	//	몬스터가 죽고나면 아이템이 떨어집니다. 마우스 커서로 아이템을 클릭하면 집어집니다. 바사붐을 사냥한 후 떨어진는 아이템을 집어보세요
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_12, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 170, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_12, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep12_2, &strMessage, _T(""), _T("") );	//	아이템을 집어보세요
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_12, 6, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_12, 6, 7 );

	//	[_DIALOG_TUTORIALWND_13]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_13, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_13, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle13, &strMessage, _T(""), _T("") );	//	아이템 줍기 응용
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_13, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_13, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_13, 1 );
	//	Button 명령 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_13, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand113, &strMessage, _T(""), _T("") );	//	[튜토리얼을 마치며]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_13, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_13, 2 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_13, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_13, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s님 수고하셨습니다.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_13, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_13, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep13_0, &strMessage, _T(""), _T("") );	//	좀더 쉽게 아이템을 집는 방법을 알려드리겠습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_13, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 160, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_13, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep13_1, &strMessage, _T(""), _T("") );	//	명령어창을 열고 아이템 줍기 아이콘을 퀵바에 올려놓고 해당 번호를 눌러 아이템을 집으면 더욱 더 쉽게 아이템을 집을 수 있습니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_13, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_13, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep13_2, &strMessage, _T(""), _T("") );	//	이젠 모든 튜토리얼 과정을 마치겠습니다.\n긴 시간동안 수고하셨습니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_13, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 270, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_13, 7, 7 );

	//	[_DIALOG_TUTORIALWND_14]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_14, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_14, 6 );
    //	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle14, &strMessage, _T(""), _T("") );	//	GM 설명
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_14, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	줄	제목 사각형 세로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 1, 220, 68, 1400, 3, 45 );
	//	줄	제목 사각형 가로
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 2, 15, 113, 1400, 207, 3 );
	//	버튼 테두리
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_14, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_14, 1 );
	//	Button 명령 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_14, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand114, &strMessage, _T(""), _T("") );	//	[초보자 퀘스트를 한다.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_14, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	//	Text 제목 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	탄트라 월드에 오신 %s님에게...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_14, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_14, 3, 7 );
	//	Text 설명
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep14_0, &strMessage, _T(""), _T("") );	//	이제 꿈과 모험이 가득한 탄트라 월드에서 마라의 무리들과 대적하는 용사로서 갖추어야 할 기본 소양을 마스터 하였습니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_14, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_14, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep14_1, &strMessage, _T(""), _T("") );	//	지금까지 가이드를 한 저는, 이제 GM이라는 이름으로 항상 곁에서 플레이 환경 개선은 물론 난관에 봉착하였을 때 마다 도움을 드리는 도우미가 되겠습니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_14, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_14, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep14_2, &strMessage, _T(""), _T("") );	//	지금까지 학습하신 내용과 그것들의 응용을 실습 할 수 있는 초보자 퀘스트가 준비되어 있습니다. 몰론 초보 단계에 얻기 힘든 아이템들이 보상으로 준비되어 있으니 수행하시길 권합니다.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_14, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 270, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_14, 6, 7 );
}
//	입력함수 처리 선택 도움말1
void HTTutorialSystem::HT_vHelp_InputCheckHelp1(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_HELPWND_1, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			//	도움말 기능_끄기
			g_cTutorialSystem->HT_vTutorial_DelHelpWnd();
		}
		//	Button 채팅관련
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_1);
		}
		//	Button 퀵슬롯바
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_2, iPosX, iPosY );
		}
		//	Button 행동관련
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_3, iPosX, iPosY );
		}
		//	Button 윈도우관련
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_4, iPosX, iPosY );
		}
	}
}
//	입력함수 처리 선택 도움말2
void HTTutorialSystem::HT_vHelp_InputCheckHelp2(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_HELPWND_2, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			//	도움말 기능_끄기
			g_cTutorialSystem->HT_vTutorial_DelHelpWnd();
		}
		//	Button 채팅관련
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_1, iPosX, iPosY );
		}
		//	Button 퀵슬롯바
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_2);
		}
		//	Button 행동관련
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_3, iPosX, iPosY );
		}
		//	Button 윈도우관련
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_4, iPosX, iPosY );
		}
	}
}
//	입력함수 처리 선택 도움말3
void HTTutorialSystem::HT_vHelp_InputCheckHelp3(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_HELPWND_3, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			//	도움말 기능_끄기
			g_cTutorialSystem->HT_vTutorial_DelHelpWnd();
		}
		//	Button 채팅관련
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_1, iPosX, iPosY );
		}
		//	Button 퀵슬롯바
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_2, iPosX, iPosY );
		}
		//	Button 행동관련
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_3);
		}
		//	Button 윈도우관련
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_4, iPosX, iPosY );
		}
	}
}
//	입력함수 처리 선택 도움말4
void HTTutorialSystem::HT_vHelp_InputCheckHelp4(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_HELPWND_4, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			//	도움말 기능_끄기
			g_cTutorialSystem->HT_vTutorial_DelHelpWnd();
		}
		//	Button 채팅관련
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_1, iPosX, iPosY );
		}
		//	Button 퀵슬롯바
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_2, iPosX, iPosY );
		}
		//	Button 행동관련
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_3, iPosX, iPosY );
		}
		//	Button 윈도우관련
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_4);
		}
	}
}

//	입력함수 처리 튜토리얼
void HTTutorialSystem::HT_vTutorial_InputCheckTutorialWnd(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == 1 || iTargetID == 2 || iTargetID == -1 )	// 취소 버튼 클릭시 다음단계로 진행
		{
			g_cTutorialSystem->HT_vUpdateUI(g_cTutorialSystem->m_iTutorialStep);
		}
	}
}

//	튜토리얼 시스템 컨트롤
HTbool HTTutorialSystem::HT_bTutorialControl()
{
	if ( !m_bTutorialOn ) return HT_FALSE;

	HTbool bStepOK = HT_FALSE;
	switch(m_iTutorialStep)
	{
		case _DIALOG_TUTORIALWND_2:
			bStepOK = this->HT_bMoveTutorial();
			break;
		case _DIALOG_TUTORIALWND_4:
			bStepOK = this->HT_bChangeViewTutorial();
			break;
		case _DIALOG_TUTORIALWND_6:
			bStepOK = this->HT_bChangeMiniMapTutorial();
			break;
		case _DIALOG_TUTORIALWND_8:
			bStepOK = this->HT_bEquipBasicWeaponTutorial();
			break;	
	}
	if (bStepOK)
	{
		this->HT_vUpdateUI(m_iTutorialStep);
	}

	return HT_TRUE;
}

//	UI에 의한 아이콘 체크_최초 튜토리얼 시스템을 할수 있도록 셋팅해준다.
HTvoid HTTutorialSystem::HT_vStartTutorial()
{
	//	튜토리얼 시스템 창
	g_cUIManager->HT_ShowWindow(_DIALOG_TUTORIALWND_1);
	//	현재의 단계
	m_iTutorialStep	= _DIALOG_TUTORIALWND_1;
	m_bTutorialOn	= HT_TRUE;
}

//---------------------------------------------------------
// HTbool	HT_bTutorial_DlgCheck( HTint iDlgNo, HTPoint pPt)
// D : 튜토리얼 다이알로그 입력 체크
// I : iDlgNo - 다이알로그 번호, pPt - 좌표
//---------------------------------------------------------
HTbool HTTutorialSystem::HT_bTutorial_DlgCheck( HTint iDlgNo, HTPoint pPt )
{	
	return HT_TRUE;
}

//	튜토리얼 시스템이 모두 끝내고 튜토리얼 퀘스트로 넘김
HTvoid HTTutorialSystem::HT_Tutorial_StepCheck_End_Quest()
{
	//	튜토리얼 시스템 창
	g_cUIManager->HT_HideWindow(m_iTutorialStep);
	//	튜토리얼 시스템을 완료
	m_byTutorialSystem_TrainendSw = TUTORIALSYSTEM_END;
	//	튜토리얼 퀘스트를 수행하는지 여부
	m_bTutorialOn = HT_FALSE;

	g_cQuest->HT_vNetWork_SCP_RESP_Quest_History( m_arrQuestInfo );
}

//	도움말 기능_켜기
HTvoid HTTutorialSystem::HT_vTutorial_SetHelpWnd()
{
	m_bHelpWindowSw = HT_TRUE;
	g_cUIManager->HT_ShowWindow( _DIALOG_HELPWND_1 );
}

//	도움말 기능_끄기
HTvoid HTTutorialSystem::HT_vTutorial_DelHelpWnd()
{
	//	헬프 윈도우
	m_bHelpWindowSw = HT_FALSE;
    g_cUIManager->HT_HideWindow( _DIALOG_HELPWND_1 );
	g_cUIManager->HT_HideWindow( _DIALOG_HELPWND_2 );
	g_cUIManager->HT_HideWindow( _DIALOG_HELPWND_3 );
	g_cUIManager->HT_HideWindow( _DIALOG_HELPWND_4 );
}

//========================//
//	서버에서 메시지 받기  //
//========================//
HTvoid HTTutorialSystem::HT_vNetWork_SCP_RESP_Quest_HistoryInfoData_Save( HTbyte byQuest[MAX_EVENT_FLAG] )
{
	memcpy( m_arrQuestInfo, byQuest, sizeof(HTbyte)*MAX_EVENT_FLAG );
	//	튜토리얼 시스템을 예약
	m_byTutorialSystem_TrainendSw = TUTORIALSYSTEM_RESERVED;
	this->HT_vStartTutorial();
}
//========================//

//-------------------------------------------------------
//HTvoid				HT_vUpdateUI(HTint iStep);
// D : Step에 따라 UI를 변경한다.
// I : 튜토리얼 단계
//-------------------------------------------------------
HTvoid
HTTutorialSystem::HT_vUpdateUI(HTint iStep)
{
	if( m_iTutorialStep < _DIALOG_TUTORIALWND_14 )
	{
		HTint iNextDlgNo;
		iNextDlgNo = g_cTutorialSystem->m_iTutorialStep+1;
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( m_iTutorialStep, iPosX, iPosY );
		g_cUIManager->HT_HideWindow(m_iTutorialStep);
		g_cUIManager->HT_ShowWindow(iNextDlgNo);
		g_cUIManager->HT_MoveWindow(iNextDlgNo, iPosX, iPosY );
		g_cTutorialSystem->m_iTutorialStep = iNextDlgNo;
	}
	else
	{
		this->HT_Tutorial_StepCheck_End_Quest();
	}
}

//-------------------------------------------------------
// HTbool				HT_bMoveTutorial();
// D : 이동에 관한 튜토리얼 진행시 완료 체크
//-------------------------------------------------------
HTbool
HTTutorialSystem::HT_bMoveTutorial()
{
	if (!m_bStartMoveTutorial)
	{
		m_vecStartMovePos = g_cMainCharacter->HT_vecGetPosition();
		m_vecPrevPos = m_vecCurPos = m_vecStartMovePos;
		m_bStartMoveTutorial = HT_TRUE;
		return HT_FALSE;
	}

	m_vecCurPos = g_cMainCharacter->HT_vecGetPosition();

	// 튜토리얼의 이동거리는 정확한 계산이 필요하지 않으므로 
	// SQRT등의 정확한 계산을 필요로 하지 않는다.
	HTfloat fX = (HTfloat)(fabs(m_vecCurPos.x - m_vecPrevPos.x));
	HTfloat fZ = (HTfloat)(fabs(m_vecCurPos.z - m_vecPrevPos.z));

	m_fMoveDistance += (fX + fZ);

	if (m_fMoveDistance>_MOVETUTORIAL_DIST)
	{	
		//this->HT_vUpdateUI(m_iTutorialStep);
		return HT_TRUE;
	}
	return HT_FALSE;
}

//-------------------------------------------------------
// HTbool				HT_bChangeViewTutorial()
// D : 뷰 변경 튜토리얼 진행시 완료 체크
//-------------------------------------------------------
HTbool
HTTutorialSystem::HT_bChangeViewTutorial()
{
	if (!m_bStartViewTutorial)
	{
		m_fPrevAngle = g_cCamera.HT_fCamera_GetEyeLookAngle();
		m_fCurAngle = m_fPrevAngle;
		m_bStartViewTutorial = HT_TRUE;//View변경 시작의 플래그
		return HT_FALSE;
	}
	m_fCurAngle = g_cCamera.HT_fCamera_GetEyeLookAngle();
	m_fLookAngle += (HTfloat)(fabs(m_fCurAngle - m_fPrevAngle));
	m_fPrevAngle = m_fCurAngle;

	if (m_fLookAngle>_VIEWTUTORIAL_ANGLE)
	{	
		//this->HT_vUpdateUI(m_iTutorialStep);
		return HT_TRUE;
	}
	return HT_FALSE;
}

//-------------------------------------------------------
// HTbool				HT_bChangeMiniMapTutorial()
// D : 미니맵 크기 변경 튜토리얼 진행시 완료 체크
//-------------------------------------------------------
HTbool
HTTutorialSystem::HT_bChangeMiniMapTutorial()
{
	HTint iMiniMapStatus = 0;
	if( g_cUIManager->HT_isShowWindow(_DIALOG_MINIMAPSMALL) )	iMiniMapStatus = _DIALOG_MINIMAPSMALL;
	if( g_cUIManager->HT_isShowWindow(_DIALOG_MINIMAPBIG) )		iMiniMapStatus = _DIALOG_MINIMAPBIG;

	if (iMiniMapStatus!=m_iMiniMapStatus) return HT_TRUE;
	return HT_FALSE;
}

//-------------------------------------------------------
// HTbool				HT_bEquipBasicWeaponTutorial()
// D : 기본무기 장착 튜토리얼 진행시 완료 체크
//-------------------------------------------------------
HTbool
HTTutorialSystem::HT_bEquipBasicWeaponTutorial()
{
	if (g_cItemSystem)
	{
		if (g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(ITEM_LOCATION_EQUIP_RIGHT_HAND))
			return HT_TRUE;
	}
	return HT_FALSE;
}


//-------------------------------------------------------
// HTvoid				HT_vAddTutorialStep()
// D : 튜토리얼 단계를 증가시킨다.
//-------------------------------------------------------
HTvoid
HTTutorialSystem::HT_vAddTutorialStep(HTint iStep)
{
	this->HT_vUpdateUI(m_iTutorialStep);
}


