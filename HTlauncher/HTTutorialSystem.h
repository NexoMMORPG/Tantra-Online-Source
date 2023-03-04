#pragma once

class HTTutorialSystem
{
public:
	HTTutorialSystem(void);
	~HTTutorialSystem(void);

	//--------------------------------------------------------------
	// HTvoid				HT_Tutorial_SetInit()
	// D : Ʃ�丮�� �ý��� �ʱ� ����
	//--------------------------------------------------------------
	HTvoid				HT_vInit();
	//	Create Window
	HTvoid				HT_vHelp_CreateWindow();
	//	�Է��Լ� ó�� ���� ����1
	static void HT_vHelp_InputCheckHelp1(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���� ����2
	static void HT_vHelp_InputCheckHelp2(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���� ����3
	static void HT_vHelp_InputCheckHelp3(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� ���� ����4
	static void HT_vHelp_InputCheckHelp4(int iAction, int iTarget, int iTargetID);

	//	�Է��Լ� ó�� Ʃ�丮��
	static void HT_vTutorial_InputCheckTutorialWnd(int iAction, int iTarget, int iTargetID);

	//	�޽��� �ε�
	//HTvoid				HT_Tutorial_MsgLoading( CHTString strList );
	//	Ʃ�丮�� �ý��� ��Ʈ��
	HTbool				HT_bTutorialControl();
	
	//--------------------------------------------------------------
	// HTvoid	HT_vStartTutorial();
	// D : Ʃ�丮�� �ý����� �����Ѵ�.
	//--------------------------------------------------------------
	HTvoid				HT_vStartTutorial();
	
	//--------------------------------------------------------------
	// HTbool	HT_bTutorial_DlgCheck( HTint iDlgNo, HTPoint pPt)
	// D : Ʃ�丮�� ���̾˷α� �Է� üũ
	// I : iDlgNo - ���̾˷α� ��ȣ, pPt - ��ǥ
	//--------------------------------------------------------------
	HTbool				HT_bTutorial_DlgCheck( HTint iDlgNo, HTPoint pPt);

	//--------------------------------------------------------------
	// HTint				HT_iGetTutorialStep()
	// D : Ʃ�丮�� �ܰ� ���
	// R : Ʃ�丮�� �ܰ�
	//--------------------------------------------------------------
	HTint				HT_iGetTutorialStep() { return m_iTutorialStep; };

	//	Ʃ�丮�� �ܰ� üũ
	HTvoid				HT_Tutorial_StepCheck();

	//	Ʃ�丮�� �ý����� ��� ������ Ʃ�丮�� ����Ʈ�� �ѱ�
	HTvoid				HT_Tutorial_StepCheck_End_Quest();

	//	���� ���_�ѱ�
	HTvoid				HT_vTutorial_SetHelpWnd();
	//	���� ���_����
	HTvoid				HT_vTutorial_DelHelpWnd();

	//========================//
	//	��ȯ��				  //
	//========================//
	BYTE				HT_bTutorial_TrainendSw()	{	return m_byTutorialSystem_TrainendSw;	};
	HTbool				HT_bTutorial_HelpWnd()		{	return m_bHelpWindowSw;					};

	//========================//
	//	�������� �޽��� �ޱ�  //
	//========================//
	//HTvoid				HT_vNetWork_SCP_RESP_Quest_HistoryInfoData_Save( PS_QUEST_HISTORY_INFO info, HTint nRemainder );
	HTvoid				HT_vNetWork_SCP_RESP_Quest_HistoryInfoData_Save( HTbyte byQuest[MAX_EVENT_FLAG] );
	//========================//
private:
	//-------------------------------------------------------
	//HTvoid				HT_vUpdateUI(HTint iStep);
	// D : Step�� ���� UI�� �����Ѵ�.
	// I : Ʃ�丮�� �ܰ�
	//-------------------------------------------------------
	HTvoid				HT_vUpdateUI(HTint iStep);

	//-------------------------------------------------------
	// HTbool				HT_bMoveTutorial();
	// D : �̵��� ���� Ʃ�丮�� ����� �Ϸ� üũ
	//-------------------------------------------------------
	HTbool				HT_bMoveTutorial();

	//-------------------------------------------------------
	// HTbool				HT_bChangeViewTutorial()
	// D : �� ���� Ʃ�丮�� ����� �Ϸ� üũ
	//-------------------------------------------------------
	HTbool				HT_bChangeViewTutorial();

	//-------------------------------------------------------
	// HTbool				HT_bChangeMiniMapTutorial()
	// D : �̴ϸ� ũ�� ���� Ʃ�丮�� ����� �Ϸ� üũ
	//-------------------------------------------------------
	HTbool				HT_bChangeMiniMapTutorial();

	//-------------------------------------------------------
	// HTbool				HT_bEquipBasicWeaponTutorial()
	// D : �⺻���� ���� Ʃ�丮�� ����� �Ϸ� üũ
	//-------------------------------------------------------
	HTbool				HT_bEquipBasicWeaponTutorial();

public:
	//-------------------------------------------------------
	// HTvoid				HT_vAddTutorialStep()
	// D : Ʃ�丮�� �ܰ踦 ������Ų��.
	//-------------------------------------------------------
	HTvoid				HT_vAddTutorialStep(HTint iStep);

public:

	//	������ �ܰ�
	HTint				m_iTutorialStep;

	// [ Move Tutorial ] ���� ������
	HTbool				m_bStartMoveTutorial;
	HTvector3			m_vecStartMovePos;
	HTvector3			m_vecPrevPos;
	HTvector3			m_vecCurPos;
	HTfloat				m_fMoveDistance;

	// [ Change View ] ���� ������
	HTbool				m_bStartViewTutorial;
	HTfloat				m_fLookAngle;
	HTfloat				m_fPrevAngle;
	HTfloat				m_fCurAngle;

	// [ MiniMap ] ���� ����
	HTint				m_iMiniMapStatus;

	CHTString			m_strStepName[29];

	HTbool				m_bTutorial_IconSw;			//	�������� Ȱ��ȭ ����
	HTbool				m_bTutorial_IconShowSw;		//	�������� ��¦�̱�
	DWORD				m_dwTutorial_IconDelay;		//	�������� ��¦�̴� ��������
	BYTE				m_byTutorial_IconShowCount;	//	������ ��¦�̴� Ƚ��

	HTbool				m_bTutorialOn;	//	Ʃ�丮�� �ý����� �����ϴ��� ����
	HTbool				m_bTutorialSystem_TrainStepResult;	//	Ʃ�丮�� �ý����� �ܰ躰 ���� ����
	BYTE				m_byTutorialSystem_TrainendSw;	//	Ʃ�丮�� �ý����� �Ϸ��ߴ��� ���� 0:��������,1:����,2:�Ϸ�
	//	������ȯ ���̵� üũ
	HTfloat				m_fEyeLookAngle;
	HTfloat				m_fEyeLookDistance;
	//	���� ������
	HTbool				m_bHelpWindowSw;
	//	����Ʈ ���� ����1
	HTbyte				m_arrQuestInfo[MAX_EVENT_FLAG];

};
