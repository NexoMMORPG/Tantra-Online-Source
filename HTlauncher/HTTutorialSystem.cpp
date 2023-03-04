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
	//	������ �ܰ�
	m_iTutorialStep			= 0;

	m_bStartMoveTutorial	= HT_FALSE;
	m_fMoveDistance			= 0.0f;
	
	m_bStartViewTutorial	= HT_FALSE;
	m_fLookAngle			= 0.0f;
	m_fPrevAngle			= 0.0f;	
	m_fCurAngle				= 0.0f;

	//	�������� Ȱ��ȭ ����
	m_bTutorial_IconSw = HT_FALSE;
	//	�������� ��¦�̱�
	m_bTutorial_IconShowSw = HT_FALSE;
	//	�������� ��¦�̴� ��������
	m_dwTutorial_IconDelay = GetTickCount();
	//	Ʃ�丮�� ����Ʈ�� �����ϴ��� ����
	m_bTutorialOn = HT_FALSE;
	//	Ʃ�丮�� �ý����� �Ϸ��ߴ��� ����
	m_byTutorialSystem_TrainendSw = TUTORIALSYSTEM_NONE;
	//	���� ������
	m_bHelpWindowSw = HT_FALSE;
}

HTTutorialSystem::~HTTutorialSystem(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_HELPWND_1 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_HELPWND_2 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_HELPWND_3 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_HELPWND_4 );
	
	// Ʃ�丮��
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

//	Ʃ�丮�� �ý��� �ʱ� ����
HTvoid HTTutorialSystem::HT_vInit()
{
	this->HT_vHelp_CreateWindow();
}

//	Create Window
HTvoid HTTutorialSystem::HT_vHelp_CreateWindow()
{
	//	�޽��� ����
	CHTString strMessage;
	CHTString strTemp;
	//	[_DIALOG_HELPWND_1]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_HELPWND_1, _T(""), 329, 465, g_cTutorialSystem->HT_vHelp_InputCheckHelp1, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_HELPWND_1, 5 );
	//	��
	g_cUIManager->HT_AddTextureControl( _DIALOG_HELPWND_1, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button �ൿ����
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte1, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_1, 1, 9, 17, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_1, 1 );
	//	Button �����Թ�
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte2, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_1, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_1, 2 );
	//	Button ä�ð���
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte3, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_1, 3, 9, 169, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_1, 3 );
	//	Button ���������
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte4, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_1, 4, 9, 245, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_1, 4 );
	//	����
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoForward, &strMessage, _T(""), _T("") );	// �� : W
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 90, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 10,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoLeft, &strMessage, _T(""), _T("") );	// �� : A
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 110, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 11,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoRight, &strMessage, _T(""), _T("") );	// �� : D
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 130, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 12,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoRun, &strMessage, _T(""), _T("") );	// �޸��� / �ȱ� : Z
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 150, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 13,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoSitDown, &strMessage, _T(""), _T("") );	// �ɱ� / ���� : X
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 14, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 170, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 14,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoCamera, &strMessage, _T(""), _T("") );	// ī�޶� ���� : F12
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 15, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 190, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 15,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoDefaultCamera, &strMessage, _T(""), _T("") );	// ī�޶� �⺻ ���� : Instert, ���콺 �� ��ư
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 16, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 210, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 16,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoPointView, &strMessage, _T(""), _T("") );	// 1��Ī,3��Ī ��ȯ : F11
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 17, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 230, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 17,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoZoomIn, &strMessage, _T(""), _T("") );	// �� �� -
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 18, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 250, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 18,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoZoomOut, &strMessage, _T(""), _T("") );	// �� �ƿ�+
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 19, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 270, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 19,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoLeft2, &strMessage, _T(""), _T("") );	// ī�޶� �� ȸ�� : <-
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 290, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 20,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoRight2, &strMessage, _T(""), _T("") );	// ī�޶� �� ȸ�� : ->
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 21, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 310, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 21,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoSelectTarget, &strMessage, _T(""), _T("") );	// ����� �� ���� : E
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 22, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 330, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 22,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoAttack, &strMessage, _T(""), _T("") );	// ���� : R
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 23, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 350, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 23,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoPickUp, &strMessage, _T(""), _T("") );	// �ݱ� : F
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 24, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 370, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 24,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoSelectMember, &strMessage, _T(""), _T("") );	// ������ ���� ���� : T
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_1, 25, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 390, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_1, 25,  7 );

	//	[_DIALOG_HELPWND_2]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_HELPWND_2, _T(""), 329, 465, g_cTutorialSystem->HT_vHelp_InputCheckHelp2, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_HELPWND_2, 5 );
	//	��
	g_cUIManager->HT_AddTextureControl( _DIALOG_HELPWND_2, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button �ൿ����
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte1, &strMessage, _T(""), _T("") );	//	�ൿ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_2, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_2, 1 );
	//	Button �����Թ�
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte2, &strMessage, _T(""), _T("") );	//	�����Թ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_2, 2, 9, 93, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_2, 2 );
	//	Button ä�ð���
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte3, &strMessage, _T(""), _T("") );	//	ä�ð���
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_2, 3, 9, 169, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_2, 3 );
	//	Button ���������
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte4, &strMessage, _T(""), _T("") );	//	���������
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_2, 4, 9, 245, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_2, 4 );
	//	����
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoPreviousQuick, &strMessage, _T(""), _T("") );	//	�������� : Page Up
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 90, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 11,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoNextQuick, &strMessage, _T(""), _T("") );	//	�������� : Page Down
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 110, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 12,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickBar1, &strMessage, _T(""), _T("") );	//	���� 1���� : F1/Shift+1
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 130, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 13,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickBar2, &strMessage, _T(""), _T("") );	//	���� 2���� : F2/Shift+2
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 14, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 150, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 14,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickBar3, &strMessage, _T(""), _T("") );	//	���� 3���� : F3/Shift+3
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 15, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 170, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 15,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickBar4, &strMessage, _T(""), _T("") );	//	���� 4���� : F4/Shift+4
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 16, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 190, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 16,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickBar5, &strMessage, _T(""), _T("") );	//	���� 5���� : F5/Shift+5
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 17, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 210, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 17,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot1, &strMessage, _T(""), _T("") );	//	���� ����1 ��� : 1
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 18, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 230, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 18,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot2, &strMessage, _T(""), _T("") );	//	���� ����2 ��� : 2
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 19, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 250, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 19,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot3, &strMessage, _T(""), _T("") );	//	���� ����3 ��� : 3
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 270, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 20,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot4, &strMessage, _T(""), _T("") );	//	���� ����4 ��� : 4
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 21, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 290, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 21,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot5, &strMessage, _T(""), _T("") );	//	���� ����5 ��� : 5
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 22, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 310, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 22,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot6, &strMessage, _T(""), _T("") );	//	���� ����6 ��� : 6
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 23, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 330, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 23,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot7, &strMessage, _T(""), _T("") );	//	���� ����7 ��� : 7
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 24, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 350, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 24,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot8, &strMessage, _T(""), _T("") );	//	���� ����8 ��� : 8
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 25, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 370, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 25,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot9, &strMessage, _T(""), _T("") );	//	���� ����9 ��� : 9
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 26, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 390, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 26,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuickSlot0, &strMessage, _T(""), _T("") );	//	���� ����10 ��� : 10
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_2, 27, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 410, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_2, 27,  7 );

	//	[_DIALOG_HELPWND_3]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_HELPWND_3, _T(""), 329, 465, g_cTutorialSystem->HT_vHelp_InputCheckHelp3, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_HELPWND_3, 5 );
	//	��
	g_cUIManager->HT_AddTextureControl( _DIALOG_HELPWND_3, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button �ൿ����
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte1, &strMessage, _T(""), _T("") );	//	�ൿ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_3, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_3, 1 );
	//	Button �����Թ�
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte2, &strMessage, _T(""), _T("") );	//	�����Թ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_3, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_3, 2 );
	//	Button ä�ð���
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte3, &strMessage, _T(""), _T("") );	//	ä�ð���
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_3, 3, 9, 169, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_3, 3 );
	//	Button ���������
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte4, &strMessage, _T(""), _T("") );	//	���������
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_3, 4, 9, 245, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_3, 4 );
	//	����
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoWholeChat, &strMessage, _T(""), _T("") );	//	��ü��ȭ : /��ü,/��,/s
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 90, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 10,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoWhisper, &strMessage, _T(""), _T("") );	//	�ӼӸ� : /��,/w
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 110, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 11,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoPartyChat, &strMessage, _T(""), _T("") );	//	��Ƽ ��ȭ : /��Ƽ,/��,/g
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 130, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 12,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoAshuramChat, &strMessage, _T(""), _T("") );	//	�ƽ��� ��ȭ : /�ƽ���,/��,/gc
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 150, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 13,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoRegisterAddress, &strMessage, _T(""), _T("") );	//	ģ�� ��� : /ģ����� ���
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 14, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 170, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 14,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoResponseWhisper, &strMessage, _T(""), _T("") );	//	�ӼӸ� ���� : /v
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 15, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 190, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 15,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoActiveChat, &strMessage, _T(""), _T("") );	//	ä��â Ȱ�� : Enter
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 16, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 210, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 16,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoAshuramMemberGrade, &strMessage, _T(""), _T("") );	//	�ƽ��� ������ ��� ���� : /�ƽ������ �̸� ���
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 17, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 230, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 17,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoAshuramNotify, &strMessage, _T(""), _T("") );	//	�ƽ��� ���� ���� ���� : /�������� ��������
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 18, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 250, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 18,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyChangeChatWndStyle, &strMessage, _T(""), _T("") );	//	ä��â ��Ÿ�� ���� : =
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_3, 19, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 270, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_3, 19,  7 );

	//	[_DIALOG_HELPWND_4]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_HELPWND_4, _T(""), 329, 465, g_cTutorialSystem->HT_vHelp_InputCheckHelp4, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_HELPWND_4, 5 );
	//	��
	g_cUIManager->HT_AddTextureControl( _DIALOG_HELPWND_4, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button �ൿ����
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte1, &strMessage, _T(""), _T("") );	//	�ൿ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_4, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_4, 1 );
	//	Button �����Թ�
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte2, &strMessage, _T(""), _T("") );	//	�����Թ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_4, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_4, 2 );
	//	Button ä�ð���
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte3, &strMessage, _T(""), _T("") );	//	ä�ð���
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_4, 3, 9, 169, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_4, 3 );
	//	Button ���������
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyTilte4, &strMessage, _T(""), _T("") );	//	���������
	g_cUIManager->HT_AddButtonControl( _DIALOG_HELPWND_4, 4, 9, 245, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_HELPWND_4, 4 );
	//	����
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoCharacterInfo, &strMessage, _T(""), _T("") );	//	�������ͽ� : L
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 90, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 10,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoInventory, &strMessage, _T(""), _T("") );	//	�κ��丮 : I
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 110, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 11,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoQuest, &strMessage, _T(""), _T("") );	//	����Ʈ : U
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 130, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 12,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoSkill, &strMessage, _T(""), _T("") );	//	��ų : K
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 150, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 13,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoOption, &strMessage, _T(""), _T("") );	//	�ɼ� : O
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 14, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 170, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 14,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoCommand, &strMessage, _T(""), _T("") );	//	Ŀ�ǵ� : C
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 15, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 190, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 15,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoGuild, &strMessage, _T(""), _T("") );	//	���â : G
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 16, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 210, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 16,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoAddress, &strMessage, _T(""), _T("") );	//	�ּҷ� : J
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 17, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 230, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 17,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoHelp, &strMessage, _T(""), _T("") );	//	���� : H
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 18, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 250, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 18,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoBalloon, &strMessage, _T(""), _T("") );	//	ǳ���� ��ȯ : B
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 19, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 270, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 19,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoNameHide, &strMessage, _T(""), _T("") );	//	�̸� ����� : N
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 290, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 20,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoUIHide, &strMessage, _T(""), _T("") );	//	������ ��� ����� : Tab
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 21, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 310, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 21,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoMiniMap, &strMessage, _T(""), _T("") );	//	�̴ϸ� : M
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 22, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 330, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 22,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoScreenShot, &strMessage, _T(""), _T("") );	//	��ũ���� : PrintScreen
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 23, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 350, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 23,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoTrade, &strMessage, _T(""), _T("") );	//	��ȯ : /��ȯ,/trade,/t
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 24, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 370, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 24,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgHotKeyInfoCloseWin, &strMessage, _T(""), _T("") );	//	â�ݱ� : Esc
	g_cUIManager->HT_AddLabelControl( _DIALOG_HELPWND_4, 25, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 390, 300, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_HELPWND_4, 25,  7 );

	//	[_DIALOG_TUTORIALWND_1]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_1, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_1, 6 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle1, &strMessage, _T(""), _T("") );	//	ù�λ�
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_1, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_1, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_1, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_1, 1 );
	//	Button ��� ��ư
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_1, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand1, &strMessage, _T(""), _T("") );	//	[ĳ���� �̵������ ����.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_1, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_1, 2 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_1, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_1, 3, 7 );
	//	Text ����
	if (g_oMainCharacterInfo.snTribe > 4)
	{
		g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep1_0+((g_oMainCharacterInfo.snTribe-4)*2-1), &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	���� %s�� ���ٶ� ������ ���Ű��� �������� ȯ���մϴ�.
	}
	else
	{
		g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep1_0+((g_oMainCharacterInfo.snTribe-1)*2), &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	���� %s�� ���ٶ� ������ ���Ű��� �������� ȯ���մϴ�.
	}

	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_1, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_1, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep1_8, &strMessage, _T(""), _T("") );	//	�Ÿ��� ���õ��� ������ Ǫ������ �;��µ� %s���� �����ϰ� �Ǵ±���. �����Դϴ�.
	strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_1, 5, strTemp.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_1, 5, 7 );

	//	[_DIALOG_TUTORIALWND_2]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_2, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_2, 6 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle2, &strMessage, _T(""), _T("") );	//	ĳ�����̵����
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_2, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_2, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_2, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_2, 1 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_2, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_2, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep2_0, &strMessage, _T(""), _T("") );	//	�� �׷� �̵� �غ����?
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_2, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_2, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep2_1, &strMessage, _T(""), _T("") );	//	���� �� �ָ� ���콺�� ������ Ŭ���� ������. Ŭ���� ���� �� �Ķ������� ���鿡 �׷����ٸ� �ϴ� ����!! ���� ������ �׷����ٸ� �װ��� ���� ���� ���̶��ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_2, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 180, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_2, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep2_2, &strMessage, _T(""), _T("") );	//	ĳ���͸� �̵��� ������
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_2, 6, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_2, 6, 7 );

	//	[_DIALOG_TUTORIALWND_3]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_3, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_3, 6 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle3, &strMessage, _T(""), _T("") );	//	��Ż ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_3, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_3, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_3, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_3, 1 );
	//	Button ��� ��ư
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_3, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand3, &strMessage, _T(""), _T("") );	//	[���� ������ ����.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_3, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_3, 2 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_3, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_3, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s�� �����ϼ̽��ϴ�.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_3, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_3, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank2, &strMessage, _T(""), _T("") );	//	���� ��Ʈ���̾����ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_3, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 155, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_3, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep3_0, &strMessage, _T(""), _T("") );	//	�޸���� �ȱ� ������ 'Z'�� �ϰ� �Ǹ� ���Ÿ� �̵��ÿ� ��Ż�� ����Ͽ� �����̵��� �մϴ�. ��Ż�� ���ٶ� ���� �߾��� �Ÿ� ��, ������ ���ǿ��� �����ø� �˴ϴ�. ������ �� ������ ���� ���Ͱ� �����ϹǷ� �����ϼž� �մϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_3, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 180, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_3, 6, 7 );

	//	[_DIALOG_TUTORIALWND_4]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_4, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_4, 6 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle4, &strMessage, _T(""), _T("") );	//	���� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_4, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_4, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_4, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_4, 1 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_4, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_4, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep4_0, &strMessage, _T(""), _T("") );	//	źƮ���� �Ƹ��ٿ� �ϴ��� ���� �� �ֳ���?
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_4, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_4, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep4_1, &strMessage, _T(""), _T("") );	//	���� ���� ����� ����� �Ƹ��ٿ� �ϴ��� ������ ������ ����.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_4, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 170, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_4, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep4_2, &strMessage, _T(""), _T("") );	//	���콺 ������ ��ư�� ���� ���¿��� ���콺�� �̵��� ������. ������ �յڷ� ������ ���� ���콺 ��ũ�� ��ư�� �����ø� �˴ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_4, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 210, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_4, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep4_3, &strMessage, _T(""), _T("") );	//	������ ������ ������.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_4, 7, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_4, 7, 7 );

	//	[_DIALOG_TUTORIALWND_5]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_5, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_5, 6 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle5, &strMessage, _T(""), _T("") );	//	���� ���� ���Ű ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_5, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_5, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_5, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_5, 1 );
	//	Button ��� ��ư
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_5, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand5, &strMessage, _T(""), _T("") );	//	[�̴ϸ� ������ ����.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_5, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_5, 2 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_5, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_5, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s�� �����ϼ̽��ϴ�.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_5, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_5, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank2, &strMessage, _T(""), _T("") );	//	���� ��Ʈ���̾����ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_5, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 155, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_5, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep5_0, &strMessage, _T(""), _T("") );	//	���� �� �˷� �帮�ڸ� 'F11'Ű�� �����ø� 1��Ī, 3��Ī���� ������ȯ�� �����մϴ�. ���� ����Ű�� 'F12'�̸�, ���콺 �߾��� ��ũ�� ��ư�� �����ø� �⺻ �������� ��ȯ�˴ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_5, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_5, 6, 7 );

	//	[_DIALOG_TUTORIALWND_6]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_6, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_6, 6 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle6, &strMessage, _T(""), _T("") );	//	�̴ϸ� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_6, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_6, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_6, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_6, 1 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_6, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_6, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep6_0, &strMessage, _T(""), _T("") );	//	��� ����� �а��� �ȵǽŴٱ���? �̴ϸ��� �̿��Ͻø� ������ ���� �����Ͻ� �� �ֽ��ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_6, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_6, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep6_1, &strMessage, _T(""), _T("") );	//	�̴ϸʿ� ���̴� ȭ��ǥ�� �ڽ��� ��ġ�� ��Ÿ���� ������⿡ ���� ȭ��ǥ�� ȸ���ϰ� �˴ϴ�. ���� �� ū ������ �� �� �ִµ� �̴ϸ��� ũ�⸦ �����ϴ� ����Ű�� Ű���� 'M'�� ���� ������ �� �ֽ��ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_6, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_6, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep6_2, &strMessage, _T(""), _T("") );	//	�̴ϸ� ũ�⸦ �ٲ� ������.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_6, 6, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_6, 6, 7 );

	//	[_DIALOG_TUTORIALWND_7]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_7, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_7, 6 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle7, &strMessage, _T(""), _T("") );	//	�̴ϸ� ������
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_7, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_7, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_7, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_7, 1 );
	//	Button ��� ��ư
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_7, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand7, &strMessage, _T(""), _T("") );	//	[����Ű ������ ��´�.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_7, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_7, 2 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_7, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_7, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s�� �����ϼ̽��ϴ�.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_7, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_7, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep7_0, &strMessage, _T(""), _T("") );	//	������ ���� �ְ���?\n���� �ڼ��� ������ �帮�ڸ� �̴ϸʿ� ���̴� �������� NPC�� ���� Ư¡�� ��� �ֽ��ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_7, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 160, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_7, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep7_1, &strMessage, _T(""), _T("") );	//	���� ���� Ư¡�� ������ �����Ƿ� �O�� ���Ƕ� ���� ���� �O���� �ְ� �̴ϸ� ����� ���ڵ��� ��ǥ�� ǥ���ϹǷ� �����Ͻø� ģ���� �O�� �� ���� ���Ͻ� ���Դϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_7, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 270, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_7, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep7_2, &strMessage, _T(""), _T("") );	//	������ ����  ��ȭ��   â��
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
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle8, &strMessage, _T(""), _T("") );	//	����Ű Ȱ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_8, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_8, 1 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_8, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep8_0, &strMessage, _T(""), _T("") );	//	������ �Ͻ� �� ���� ���Ǵ� ����Ű�� ��� ���� �帮�ڽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_8, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep8_1, &strMessage, _T(""), _T("") );	//	������ �Ʒ� ���̴� �������� �� ����� ����Ű�� ������ ���� �������Դϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 180, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_8, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep8_2, &strMessage, _T(""), _T("") );	//	'I'Ű�� ���� �κ��丮 â�� ���� �⺻���⸦ ������ ������
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 210, 220, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_8, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep8_3, &strMessage, _T(""), _T("") );	//	�������� �����ϴ� ����� ���콺 Ŀ���� ������ ���� �÷����� Ŭ���Ͽ� ������ �� ��ġ�� �ٽ� Ŭ���� �����ø� �˴ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_8, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 260, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_8, 7, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep8_4, &strMessage, _T(""), _T("") );	//	�⺻ ���⸦ ������ ������
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_8, 8, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_8, 8, 7 );
	//	Image
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_8, 0, 41, 22, 208 );

	//	[_DIALOG_TUTORIALWND_9]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_9, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_9, 6 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle9, &strMessage, _T(""), _T("") );	//	����Ű����
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_9, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_9, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_9, 1 );
	//	Button ��� ��ư
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_9, 2, 159, 18, 425, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand9, &strMessage, _T(""), _T("") );	//	[���� ��ɹ��� ����.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 425, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_9, 2 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s�� �����ϼ̽��ϴ�.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 135, 186, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_0, &strMessage, _T(""), _T("") );	//	�ٸ� ����Ű�� ���� ������ �帮�ڽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 150, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_1, &strMessage, _T(""), _T("") );	//	'L'Ű�� ���� ĳ������ ���� ������ �� �� �ֽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 170, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_2, &strMessage, _T(""), _T("") );	//	'I'Ű�� ���� ����ǰ �Ǵ� ���� �������� Ȯ�� �� �� �ֽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 205, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 7, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_4, &strMessage, _T(""), _T("") );	//	'U'Ű�� ���� ����Ʈ�� ���õ� ������ �� �� �ֽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 8, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 240, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 8, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_3, &strMessage, _T(""), _T("") );	//	'K'Ű�� ���� �ڽ��� ��� ������� Ȯ�� �� �� �ֽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 9, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 275, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 9, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_6, &strMessage, _T(""), _T("") );	//	'ESC'Ű�� ���Ӽ��� �Ǵ� �ý��� ���� ������ ���� �� �� �ֽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 310, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 10, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_5, &strMessage, _T(""), _T("") );	//	'C'Ű�� ��ɾ� ���� �������� Ȯ�� �� �� �ֽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_9, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 60, 345, 230, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_9, 11, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep9_7, &strMessage, _T(""), _T("") );	//	"�÷��̾ ���������� ������ �� �ֽ��ϴ�.(PK�� ���������̹Ƿ� ����� �������� �ް� �˴ϴ�.)
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
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle10, &strMessage, _T(""), _T("") );	//	���� ��ɹ�
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_10, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_10, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_10, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_10, 1 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_10, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_10, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep10_0, &strMessage, _T(""), _T("") );	//	��, ���� ����� �غ��ðڽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_10, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_10, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep10_1, &strMessage, _T(""), _T("") );	//	�̴ϸ��� ���� ���� ���ʿ� ������ ȭ��ǥ�� �ֽ��ϴ�. ȭ��ǥ �Ʒ� ���� ���� ������ ������ ���͵��� �����ϴ� ������ �� �� �ֽ��ϴ�. ���͸� �ѹ� Ŭ���ϸ� ������ ������ ������ �ٽ� �ѹ� Ŭ���ϸ� ���͸� �����ϰ� �˴ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_10, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_10, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep10_2, &strMessage, _T(""), _T("") );	//	�ٻ�� 1������ ����� ������.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_10, 6, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_10, 6, 7 );

	//	[_DIALOG_TUTORIALWND_11]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_11, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_11, 6 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle11, &strMessage, _T(""), _T("") );	//	��ɹ� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_11, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_11, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_11, 1 );
	//	Button ��� ��ư
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_11, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand11, &strMessage, _T(""), _T("") );	//	[ITEM �ݴ¹��� ����.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_11, 2 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_11, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s�� �����ϼ̽��ϴ�.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_11, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep11_0, &strMessage, _T(""), _T("") );	//	�� ���� ����ϴ� ����� �˷��帮�ڽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 160, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_11, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep11_1, &strMessage, _T(""), _T("") );	//	��ɾ�â�� ����ø�
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 58, 198, 230, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_11, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep11_2, &strMessage, _T(""), _T("") );	//	������ ���� �O�� �������� �ֽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_11, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 58, 233, 220, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_11, 7, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep11_3, &strMessage, _T(""), _T("") );	//	�������� Ŭ���ؼ� ���ٿ� �÷����� ������ ���͸� ���� �O�� �� �ֽ��ϴ�.
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
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle12, &strMessage, _T(""), _T("") );	//	������ �ݴ¹�
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_12, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_12, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_12, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_12, 1 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_12, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_12, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep12_0, &strMessage, _T(""), _T("") );	//	������ �ݴ¹��� ��� ������ �ϰڽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_12, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_12, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep12_1, &strMessage, _T(""), _T("") );	//	���Ͱ� �װ��� �������� �������ϴ�. ���콺 Ŀ���� �������� Ŭ���ϸ� �������ϴ�. �ٻ���� ����� �� �������� �������� �������
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_12, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 170, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_12, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep12_2, &strMessage, _T(""), _T("") );	//	�������� �������
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_12, 6, strMessage, 0, HT_COLOR(1.00f,0.59f,0.00f,10.f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 420, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_12, 6, 7 );

	//	[_DIALOG_TUTORIALWND_13]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_13, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_13, 6 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle13, &strMessage, _T(""), _T("") );	//	������ �ݱ� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_13, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_13, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_13, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_13, 1 );
	//	Button ��� ��ư
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_13, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand113, &strMessage, _T(""), _T("") );	//	[Ʃ�丮���� ��ġ��]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_13, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_13, 2 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_13, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_13, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialThank1, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	%s�� �����ϼ̽��ϴ�.
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_13, 4, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_13, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep13_0, &strMessage, _T(""), _T("") );	//	���� ���� �������� ���� ����� �˷��帮�ڽ��ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_13, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 160, 250, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_13, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep13_1, &strMessage, _T(""), _T("") );	//	��ɾ�â�� ���� ������ �ݱ� �������� ���ٿ� �÷����� �ش� ��ȣ�� ���� �������� ������ ���� �� ���� �������� ���� �� �ֽ��ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_13, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_13, 6, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep13_2, &strMessage, _T(""), _T("") );	//	���� ��� Ʃ�丮�� ������ ��ġ�ڽ��ϴ�.\n�� �ð����� �����ϼ̽��ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_13, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 270, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_13, 7, 7 );

	//	[_DIALOG_TUTORIALWND_14]
    //	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_TUTORIALWND_14, _T(""), 329, 465, g_cTutorialSystem->HT_vTutorial_InputCheckTutorialWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_TUTORIALWND_14, 6 );
    //	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 10, 40, 31, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialSubTitle14, &strMessage, _T(""), _T("") );	//	GM ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_14, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 152, 19 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 1, 15, 68, 1400, 3, 45 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 1, 220, 68, 1400, 3, 45 );
	//	��	���� �簢�� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 2, 15, 65, 1400, 207, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 2, 15, 113, 1400, 207, 3 );
	//	��ư �׵θ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_TUTORIALWND_14, 0, 66, 240, 54, 1400, 67, 69 );
	//	Button GM
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_14, 1, 168, 245, 59, 180, 181, 1500, 60, 62 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_TUTORIALWND_14, 1 );
	//	Button ��� ��ư
	g_cUIManager->HT_AddButtonControl( _DIALOG_TUTORIALWND_14, 2, 159, 18, 420, 160, 161, 1500, 220, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialCommand114, &strMessage, _T(""), _T("") );	//	[�ʺ��� ����Ʈ�� �Ѵ�.]
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_14, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 18, 420, 220, 19 );
	//	Text ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialTitle, &strMessage, g_oMainCharacterInfo.szCharName, _T("") );	//	źƮ�� ���忡 ���� %s�Կ���...
	//strTemp.HT_szFormat( strMessage, g_oMainCharacterInfo.szCharName );
	g_cUIManager->HT_AddLabelControl( _DIALOG_TUTORIALWND_14, 3, strMessage.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 22, 75, 186, 32 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_TUTORIALWND_14, 3, 7 );
	//	Text ����
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep14_0, &strMessage, _T(""), _T("") );	//	���� �ް� ������ ������ źƮ�� ���忡�� ������ ������� �����ϴ� ���μ� ���߾�� �� �⺻ �Ҿ��� ������ �Ͽ����ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_14, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 140, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_14, 4, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep14_1, &strMessage, _T(""), _T("") );	//	���ݱ��� ���̵带 �� ����, ���� GM�̶�� �̸����� �׻� �翡�� �÷��� ȯ�� ������ ���� ������ �����Ͽ��� �� ���� ������ �帮�� ����̰� �ǰڽ��ϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_14, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 200, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_14, 5, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgTutorialStep14_2, &strMessage, _T(""), _T("") );	//	���ݱ��� �н��Ͻ� ����� �װ͵��� ������ �ǽ� �� �� �ִ� �ʺ��� ����Ʈ�� �غ�Ǿ� �ֽ��ϴ�. ���� �ʺ� �ܰ迡 ��� ���� �����۵��� �������� �غ�Ǿ� ������ �����Ͻñ� ���մϴ�.
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_TUTORIALWND_14, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 270, 250, 50 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_TUTORIALWND_14, 6, 7 );
}
//	�Է��Լ� ó�� ���� ����1
void HTTutorialSystem::HT_vHelp_InputCheckHelp1(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_HELPWND_1, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			//	���� ���_����
			g_cTutorialSystem->HT_vTutorial_DelHelpWnd();
		}
		//	Button ä�ð���
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_1);
		}
		//	Button �����Թ�
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_2, iPosX, iPosY );
		}
		//	Button �ൿ����
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_3, iPosX, iPosY );
		}
		//	Button ���������
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_4, iPosX, iPosY );
		}
	}
}
//	�Է��Լ� ó�� ���� ����2
void HTTutorialSystem::HT_vHelp_InputCheckHelp2(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_HELPWND_2, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			//	���� ���_����
			g_cTutorialSystem->HT_vTutorial_DelHelpWnd();
		}
		//	Button ä�ð���
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_1, iPosX, iPosY );
		}
		//	Button �����Թ�
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_2);
		}
		//	Button �ൿ����
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_3, iPosX, iPosY );
		}
		//	Button ���������
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_4, iPosX, iPosY );
		}
	}
}
//	�Է��Լ� ó�� ���� ����3
void HTTutorialSystem::HT_vHelp_InputCheckHelp3(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_HELPWND_3, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			//	���� ���_����
			g_cTutorialSystem->HT_vTutorial_DelHelpWnd();
		}
		//	Button ä�ð���
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_1, iPosX, iPosY );
		}
		//	Button �����Թ�
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_2, iPosX, iPosY );
		}
		//	Button �ൿ����
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_3);
		}
		//	Button ���������
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_4, iPosX, iPosY );
		}
	}
}
//	�Է��Լ� ó�� ���� ����4
void HTTutorialSystem::HT_vHelp_InputCheckHelp4(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_HELPWND_4, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			//	���� ���_����
			g_cTutorialSystem->HT_vTutorial_DelHelpWnd();
		}
		//	Button ä�ð���
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_1);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_1, iPosX, iPosY );
		}
		//	Button �����Թ�
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_2);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_2, iPosX, iPosY );
		}
		//	Button �ൿ����
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_HELPWND_4);
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_3);
			g_cUIManager->HT_MoveWindow(_DIALOG_HELPWND_3, iPosX, iPosY );
		}
		//	Button ���������
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_HELPWND_4);
		}
	}
}

//	�Է��Լ� ó�� Ʃ�丮��
void HTTutorialSystem::HT_vTutorial_InputCheckTutorialWnd(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == 1 || iTargetID == 2 || iTargetID == -1 )	// ��� ��ư Ŭ���� �����ܰ�� ����
		{
			g_cTutorialSystem->HT_vUpdateUI(g_cTutorialSystem->m_iTutorialStep);
		}
	}
}

//	Ʃ�丮�� �ý��� ��Ʈ��
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

//	UI�� ���� ������ üũ_���� Ʃ�丮�� �ý����� �Ҽ� �ֵ��� �������ش�.
HTvoid HTTutorialSystem::HT_vStartTutorial()
{
	//	Ʃ�丮�� �ý��� â
	g_cUIManager->HT_ShowWindow(_DIALOG_TUTORIALWND_1);
	//	������ �ܰ�
	m_iTutorialStep	= _DIALOG_TUTORIALWND_1;
	m_bTutorialOn	= HT_TRUE;
}

//---------------------------------------------------------
// HTbool	HT_bTutorial_DlgCheck( HTint iDlgNo, HTPoint pPt)
// D : Ʃ�丮�� ���̾˷α� �Է� üũ
// I : iDlgNo - ���̾˷α� ��ȣ, pPt - ��ǥ
//---------------------------------------------------------
HTbool HTTutorialSystem::HT_bTutorial_DlgCheck( HTint iDlgNo, HTPoint pPt )
{	
	return HT_TRUE;
}

//	Ʃ�丮�� �ý����� ��� ������ Ʃ�丮�� ����Ʈ�� �ѱ�
HTvoid HTTutorialSystem::HT_Tutorial_StepCheck_End_Quest()
{
	//	Ʃ�丮�� �ý��� â
	g_cUIManager->HT_HideWindow(m_iTutorialStep);
	//	Ʃ�丮�� �ý����� �Ϸ�
	m_byTutorialSystem_TrainendSw = TUTORIALSYSTEM_END;
	//	Ʃ�丮�� ����Ʈ�� �����ϴ��� ����
	m_bTutorialOn = HT_FALSE;

	g_cQuest->HT_vNetWork_SCP_RESP_Quest_History( m_arrQuestInfo );
}

//	���� ���_�ѱ�
HTvoid HTTutorialSystem::HT_vTutorial_SetHelpWnd()
{
	m_bHelpWindowSw = HT_TRUE;
	g_cUIManager->HT_ShowWindow( _DIALOG_HELPWND_1 );
}

//	���� ���_����
HTvoid HTTutorialSystem::HT_vTutorial_DelHelpWnd()
{
	//	���� ������
	m_bHelpWindowSw = HT_FALSE;
    g_cUIManager->HT_HideWindow( _DIALOG_HELPWND_1 );
	g_cUIManager->HT_HideWindow( _DIALOG_HELPWND_2 );
	g_cUIManager->HT_HideWindow( _DIALOG_HELPWND_3 );
	g_cUIManager->HT_HideWindow( _DIALOG_HELPWND_4 );
}

//========================//
//	�������� �޽��� �ޱ�  //
//========================//
HTvoid HTTutorialSystem::HT_vNetWork_SCP_RESP_Quest_HistoryInfoData_Save( HTbyte byQuest[MAX_EVENT_FLAG] )
{
	memcpy( m_arrQuestInfo, byQuest, sizeof(HTbyte)*MAX_EVENT_FLAG );
	//	Ʃ�丮�� �ý����� ����
	m_byTutorialSystem_TrainendSw = TUTORIALSYSTEM_RESERVED;
	this->HT_vStartTutorial();
}
//========================//

//-------------------------------------------------------
//HTvoid				HT_vUpdateUI(HTint iStep);
// D : Step�� ���� UI�� �����Ѵ�.
// I : Ʃ�丮�� �ܰ�
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
// D : �̵��� ���� Ʃ�丮�� ����� �Ϸ� üũ
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

	// Ʃ�丮���� �̵��Ÿ��� ��Ȯ�� ����� �ʿ����� �����Ƿ� 
	// SQRT���� ��Ȯ�� ����� �ʿ�� ���� �ʴ´�.
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
// D : �� ���� Ʃ�丮�� ����� �Ϸ� üũ
//-------------------------------------------------------
HTbool
HTTutorialSystem::HT_bChangeViewTutorial()
{
	if (!m_bStartViewTutorial)
	{
		m_fPrevAngle = g_cCamera.HT_fCamera_GetEyeLookAngle();
		m_fCurAngle = m_fPrevAngle;
		m_bStartViewTutorial = HT_TRUE;//View���� ������ �÷���
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
// D : �̴ϸ� ũ�� ���� Ʃ�丮�� ����� �Ϸ� üũ
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
// D : �⺻���� ���� Ʃ�丮�� ����� �Ϸ� üũ
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
// D : Ʃ�丮�� �ܰ踦 ������Ų��.
//-------------------------------------------------------
HTvoid
HTTutorialSystem::HT_vAddTutorialStep(HTint iStep)
{
	this->HT_vUpdateUI(m_iTutorialStep);
}


