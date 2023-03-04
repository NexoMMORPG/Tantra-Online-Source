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

//#define TUTORIAL_QUEST_AGREE_1		1	// �ʺ��� ����Ʈ �³� ���� ���� �޼���â
//#define TUTORIAL_QUEST_AGREE_2		2	// ��Ҹ� ������ ��� �ٽ� ���� �޼���â

#define TUTORIAL_5_TOTAL			10		// �ɷ��� ����
#define SCENARIO_9_TOTAL			10		// �ں�� ����
#define SCENARIO_10_TOTAL			10		// ������ �ٶ��� ���� ����
#define SCENARIO_11_1_TOTAL			30		// ��ī��ī ����
#define SCENARIO_11_2_TOTAL			15		// ��ī��ī ī��� ����
#define SCENARIO_14_TOTAL			30		// ���ī ����
#define SCENARIO_24_TOTAL			20		// �Ƴ��� ����

#define TUTORIAL_5_STEP				3		// �ٶ��� ���� ���� ���� �����ִ� �ܰ� ��ȣ
#define SCENARIO_9_STEP				4		// ���� ��ī��ī ���� ���� ���� �����ִ� �ܰ� ��ȣ
#define SCENARIO_10_STEP			4		// ���� ������ �ٶ��� ���� ���� ���� �����ִ� �ܰ� ��ȣ
#define SCENARIO_11_1_STEP			4		// ��ī��ī ���� ���� �����ִ� �ܰ� ��ȣ
#define SCENARIO_11_2_STEP			7		// ��ī��ī ī��� ���� ���� �����ִ� �ܰ� ��ȣ
#define SCENARIO_14_STEP			4		// ���ī ���� ���� �����ִ� �ܰ� ��ȣ
#define SCENARIO_24_STEP			5		// �Ƴ��� ���� ���� �����ִ� �ܰ� ��ȣ

// ���� ����Ʈ ����� �κ�
#define SCENARIO_26_STEP			5		// �ڱ� ���� ���� �����ִ� �ܰ� ��ȣ
#define SCENARIO_28_1_STEP			5		// ������ ���� ���� �����ִ� �ܰ� ��ȣ
#define SCENARIO_28_2_STEP			8		// ������ �ż� ���� ���� �����ִ� �ܰ� ��ȣ
#define SCENARIO_30_STEP			8		// ��ȭ�� ���� ���� �����ִ� �ܰ� ��ȣ

#define SCENARIO_26_TOTAL			28		// �ڱ��� ����
#define SCENARIO_28_1_TOTAL			10		// �������� ����
#define SCENARIO_28_2_TOTAL			15		// ������ �ż��� ����
#define SCENARIO_30_TOTAL			30		// ��ȭ���� ����

// ������ ����Ʈ �߰� (����� �κ�)
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

//---------Ʃ�丮�� �޽��� �ε�----------//
HTvoid HTQuest::HT_vQuest_TutorialMsgLoading()
{
}

//----------Ȱ��ȭ / ��Ȱ��ȭ----------//
HTvoid HTQuest::HT_vQuest_ActiveSw()
{
	if( m_bQuest_WindowActiveSw == HT_TRUE )	
	{
		// ��Ȱ��ȭ
		m_bQuest_WindowActiveSw = HT_FALSE;
		g_cUIManager->HT_HideWindow(_DIALOG_QUEST);
	}
	else
	{
		// ����Ʈ ��ư�� ���ڰŸ��� ������ ����
		g_cUIManager->HT_SetButtonControlState( _DIALOG_MAINBAR, 4, 0 );	// �븻 ���·� �������

		// Ȱ��ȭ
		m_bQuest_WindowActiveSw = HT_TRUE;

		g_cUIManager->HT_ShowWindow(_DIALOG_QUEST);
		g_pEngineHandler->HT_hrPlaySound( _QUEST_GENERAL_SOUND, 1 );	// Click Sound
	}
}

//	ESC Key ������ â �ݱ�
HTvoid HTQuest::HT_vQuest_ESC_CloseWindow()
{
	g_cUIManager->HT_HideWindow(_DIALOG_QUEST);
	/*
	m_bQuest_WindowActiveSw = HT_TRUE;

	HT_vQuest_ActiveSw();
	*/
}

// "Ư�� ��ũ�� �ø���" ����Ʈ�� �Ķ���� ����
HTvoid HTQuest::HT_vQuest_GetChakraText(CHTString& rszChakra)
{/*
	HTshort tribe = g_oMainCharacterInfo.snTribe;
	HTint idMessage = eMsgNone;
	switch( (tribe-1)%4 )
	{
		case 0:	// ����/�䳪��
			idMessage = eMsgCommonChakraMuscle; // ����
			break;
		case 1:	// �Ƽ���/������
			idMessage = eMsgCommonChakraHeart; // ����
			break;
		case 2:	// ���/���޹�
			idMessage = eMsgCommonChakraNerve; // �Ű�
			break;
		case 3:	// ����/�����
			idMessage = eMsgCommonChakraMind; // ����
			break;
		default:
			break;
	}

	if( idMessage != eMsgNone )
		g_pMessageMgr->HT_bGetMessage( idMessage, &rszChakra );*/
}
 
// ����Ʈ �Ѱ������� �����.���Ŀ� �ٸ� �Ķ���Ͱ� ���ٸ� �����ؾ���.2003.04.17
HTvoid HTQuest::HT_vQuest_SetChakraParam(CHTString& szQuestText, CHTString& rszReturnText)
{
}

//---------������ ��������Ʈ�� �ܰ踦 ��ȯ---------//
HTvoid HTQuest::HT_vGetQuestStep(HTint nDlgNo, BYTE byType, HTint nSelect, HTint& nIndex, HTint& nStep)
{
}

// ���� ����Ʈâ���� ���������� ������ RadioNo�� �����س��´� 
HTvoid HTQuest::HT_vSetSelectRadioNo(BYTE byType, HTint nSelect)
{
}

// ���� ����Ʈâ���� ���������� ������ SlideNo�� �����س��´� 
HTvoid HTQuest::HT_vSetSlideNo(BYTE byType)
{
}

HTvoid HTQuest::HT_hrMouseLbuttonDown(HTPoint pPt)
{
}

//----------�κ��丮 Ȱ��ȭ�� �� ���콺 üũ-���콺�� �κ��丮 �ȿ� �ִ��� üũ----------//
HTvoid HTQuest::HT_vMouseCheck( HTPoint pPt )
{
}

// �����̵���� Up��ư Ŭ���� ����â ���� ����
HTbool HTQuest::HT_vQuest_SlideDown(BYTE byType)
{
	return HT_OK;
}

// �����̵���� Down��ư Ŭ���� ����â ���� ����
HTbool HTQuest::HT_vQuest_SlideUp(BYTE byType)
{
	return HT_OK;
}

// ��Ȯ�� �޼��� â
HTRESULT HTQuest::HT_hrQuest_Confirm_Message( HTint iProp, HTint iInductNo, HTint iButtonNo )
{
	return HT_FAIL;
}

// �Ϸ�޼��� â
HTRESULT HTQuest::HT_hrQuest_DialogBoxCheck( HTint iProp, HTint iInductNo )
{
	return HT_FAIL;
}

//----------����Ʈ â�� ����Ʈ ���� ���----------//
HTvoid HTQuest::HT_vQuest_SetQuestTitle(BYTE byType, BYTE byQuestIndex, HTint nRadioNo)
{
}
 
//---------- ����/�Ϸ� ����Ʈ â�� ���õ� ����� ������ ����Ѵ� ------------//
HTvoid	HTQuest::HT_vQuest_SetText(BYTE byType)
{
}

// ������ ����Ʈ�� ���� ���� ����
HTvoid HTQuest::HT_vQuest_SetInfoText(HTint nDlgNo, BYTE byType, HTint nIndex, HTint nStep)
{
}

//--------- �ʺ�/�ó�����/�Ƿ� â�� ��ϵ� ��ϰ����� ���´� ----------//
HTint HTQuest::HT_nQuest_GetListCount(HTint nDlgNo, BYTE byType)
{
	return 0;
}

//--------- ���ϴ� ����� ���̵��� �����̵� ���� -----------//
HTvoid HTQuest::HT_vQuest_SetSlidePos( HTint nDlgNo, BYTE byType, HTint nRadioNo )
{
}

HTvoid HTQuest::HT_vQuest_SetSlidePos( HTint nDlgNo, BYTE byType, HTint iSlideVal, HTint nRadioNo )
{
}

//----------��� ����Ʈ �����丮 ������ �����----------//
HTvoid HTQuest::HT_vQuest_DeleteAllHistory()
{
}

//----------���ο� �����丮�� �������� �ִ´�.---------//
HTvoid HTQuest::HT_vQuest_InsertCompleteHistory(HT_QUEST_LIST* pNew)
{
}

HTvoid HTQuest::HT_vQuest_InsertProgressHistory(HT_QUEST_LIST* pNew)
{
}

//----------Ư�� �����丮�� �����.-----------//
HT_QUEST_LIST* HTQuest::HT_psQuest_DelProgressHistory(HT_QUEST_LIST* pData)
{
	return 0;
}

//------------- ��Ʈ��ũ ���� ---------------//
// ĳ������ quest history ��������
HTvoid HTQuest::HT_vQuest_History_Init( )
{
}

HTvoid HTQuest::HT_vNetWork_SCP_RESP_Quest_History( HTbyte byQuest[MAX_EVENT_FLAG] )
{
	// v3���� ���� ����
	g_cUIQuestWindow->HT_vNetWork_SCP_RESP_Quest_History(byQuest);
}

//----------Ʃ�丮�� ����Ʈ ���� ���θ� ������ ����---------//
HTvoid HTQuest::HT_vNetWork_CSP_REQ_Quest_DIALOG(DWORD dwDialogIndex, BYTE byResult)
{
	g_cUIQuestWindow->HT_vNetWork_CSP_REQ_Quest_DIALOG(dwDialogIndex, byResult);
}

//-------------����Ʈ ���� ���� ����---------------//
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