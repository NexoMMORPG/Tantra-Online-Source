#ifndef _HTQuest_h_
#define _HTQuest_h_

typedef struct _HT_QUEST
{
	BYTE		byIndex;	// ����Ʈ ��ȣ
	BYTE		byStep;		// ����Ʈ �� ���� ���� �ܰ�
} HT_QUEST;

typedef struct _HT_QUEST_LIST
{
	BYTE		byDlg;		// �ʺ���/�ó�����/�Ƿ� ����
	HT_QUEST	sQuest;

	CHTString	szResult;		
	_HT_QUEST_LIST* pNext;
} HT_QUEST_LIST;

//#define	QUEST_MAX_NUM					60	//37
#define QUEST_DESCRIPTION_MAXNUM		60	// �� ����Ʈ�� �ִ� ���� �ܰ�

#define HT_MOB_COUNT_INDEX_MAX			60	// ���� ���� ���� ����Ʈ �� ���� ���� ���� �����ϴ� ����Ʈ 
#define MOB_COUNT_QUEST_INDEX_START		91	// ��� ���� ���ڸ� ���� �� ���Ǵ� ����Ʈ index
#define MOB_COUNT_QUEST_INDEX_END		94
/*
typedef struct _HT_QUEST_DESCRIPTION
{
	BYTE		byIndex;		// ����Ʈ ��ȣ
	CHTString	szTitle;		// ����Ʈ ����
	HTint		nStepNo;		// �ܰ� ����
	HTint		nStepNum[QUEST_DESCRIPTION_MAXNUM];		// �ܰ�
	CHTString	szStepMsg[QUEST_DESCRIPTION_MAXNUM];	// �ܰ躰 UIâ�� ��Ÿ���� ��
} HT_QUEST_DESCRIPTION;
*/
class HTQuest
{
public:
	HTQuest(void);
	~HTQuest(void);
	HTvoid				HT_vQuest_CleanUp();

	HTvoid				HT_vQuest_Init();
	
	// Ʃ�丮�� �޽��� �ε�
	HTvoid				HT_vQuest_TutorialMsgLoading();

	//	ESC Key ������ â �ݱ�
	HTvoid				HT_vQuest_ESC_CloseWindow();

	//------------------------------------------------
	// ����/��ȯ
	//------------------------------------------------
	// Ȱ��ȭ üũ
	HTbool				HT_bQuest_GetActiveSw()	{	return m_bQuest_WindowActiveSw;	};
	// Ȱ��ȭ / ��Ȱ��ȭ
	HTvoid				HT_vQuest_ActiveSw();
	
	// �ʺ�/�ó�����/�Ƿ� â�� ��ϵ� ��ϰ����� ���´�
	HTint				HT_nQuest_GetListCount(HTint nDlgNo, BYTE byType);
	// ������ ����Ʈ�� �ܰ踦 ��ȯ
	HTvoid				HT_vGetQuestStep(HTint nDlgNo, BYTE byType, HTint nSelect, HTint& nIndex, HTint& nStep);
	//------------------------------------------------
	// ���콺 Ŭ���� ���� â ����
	//------------------------------------------------
	HTvoid				HT_vMouseCheck( HTPoint pPt/*, HTbool bType*/ );
	HTvoid				HT_hrMouseLbuttonDown(HTPoint pPt);
	// ��Ȯ�� �޼��� â
	//HTRESULT			HT_hrQuest_Confirm_Message(HTPoint pPt, HTint iProp);
	HTRESULT			HT_hrQuest_Confirm_Message( HTint iProp, HTint iInductNo, HTint iButtonNo );
	// �Ϸ�޼��� â
	//HTRESULT			HT_hrQuest_DialogBoxCheck(HTPoint pPt, HTint iProp);
	HTRESULT			HT_hrQuest_DialogBoxCheck( HTint iProp, HTint iInductNo );

	HTvoid				HT_vQuest_SetIsInitChar(HTbool bInitChar) { m_bIsInitChar = bInitChar; }

	// ����Ʈ ���â ��ũ��
//	HTvoid				HT_vQuest_QuestTitleScroll(BYTE byType);
	// ���� ����Ʈâ���� ���������� ������ RadioNo�� �����س��´� 
	HTvoid				HT_vSetSelectRadioNo(BYTE byType, HTint nSelect);
	// ���� ����Ʈâ���� ���������� ������ SlideNo�� �����س��´� 
	HTvoid				HT_vSetSlideNo(BYTE byType);

	// �����̵���� Up��ư Ŭ���� ����â ���� ����
	HTbool				HT_vQuest_SlideDown(BYTE byType);
	// �����̵���� Down��ư Ŭ���� ����â ���� ����
	HTbool				HT_vQuest_SlideUp(BYTE byType);

	// ����/�Ϸ� ����Ʈ â�� ��� ����� ����Ѵ�
	HTvoid				HT_vQuest_SetText(BYTE byType);
	// ����Ʈ â�� ����Ʈ ���� ���
	HTvoid				HT_vQuest_SetQuestTitle(BYTE byType, BYTE byQuestIndex, HTint nRadioNo);
	// ������ ����Ʈ�� ���� ���� ����
	HTvoid				HT_vQuest_SetInfoText(HTint nDlgNo, BYTE byType, HTint nIndex, HTint nStep=1);
	
	//---------------------------------------------------
	// ����Ʈâ ������ ����
	//---------------------------------------------------
	HTvoid				HT_vQuest_History_Init( );

	// ��� ����Ʈ �����丮 ������ �����
	HTvoid				HT_vQuest_DeleteAllHistory();
	// ���ο� �����丮�� �������� �ִ´�.
	HTvoid				HT_vQuest_InsertCompleteHistory(HT_QUEST_LIST* pNew);
	HTvoid				HT_vQuest_InsertProgressHistory(HT_QUEST_LIST* pNew);
	// Ư�� �����丮�� �����
	HT_QUEST_LIST*		HT_psQuest_DelProgressHistory(HT_QUEST_LIST* pData);
	
	// ���ϴ� ����� ���̵��� �����̵� ����
	HTvoid				HT_vQuest_SetSlidePos( HTint nDlgNo, BYTE byType, HTint nRadioNo );
	HTvoid				HT_vQuest_SetSlidePos( HTint nDlgNo, BYTE byType, HTint iSlideVal, HTint nRadioNo );
	
	// ���� ������ ��ƾ��ϴ� ����Ʈ �ܰ��� ��� ���� ���� �� ���� ���� �ʱ�ȭ
	HTvoid				HT_vInit_MonsterCount();

	//-------------------------------------------------------------
	// ��Ʈ��ũ ���� �Լ�
	//-------------------------------------------------------------
	// Ʃ�丮�� ����Ʈ ���� ���θ� ������ ����
	HTvoid				HT_vNetWork_CSP_REQ_Quest_DIALOG(DWORD dwDialogIndex, BYTE byResult);
	// quest history ���� ���� ���
	HTvoid				HT_vNetWork_SCP_RESP_Quest_History(PS_SCP_RESP_QUEST_HISTORY info);
	HTvoid				HT_vNetWork_SCP_RESP_Quest_History( HTbyte byQuest[MAX_EVENT_FLAG] );
	// ĳ������ quest history ��������
	HTvoid				HT_vNetWork_SCP_RESP_Quest_HistoryInfo(PS_QUEST_HISTORY_INFO info, HTint nRemainder);
	// ����Ʈ ���� ���� ����
	HTvoid				HT_vNetWork_SCP_RESP_Quest_Dialog(PS_SCP_QUEST_DIALOG info);

	// ����Ʈ �Ѱ������� �����.���Ŀ� �ٸ� �Ķ���Ͱ� ���ٸ� �����ؾ���.2003.04.17
	// "Ư�� ��ũ�� �ø���" ����Ʈ�� �Ķ���� ����
	HTvoid				HT_vQuest_GetChakraText(CHTString& rszChakra);
	HTvoid				HT_vQuest_SetChakraParam(/*HTint nIndex,*/CHTString& szQuestText, CHTString& rszReturnText);

	HTvoid				HT_vMouseSlideBarMove();
	HTvoid				HT_vMouseSlideBarUp();

public:
	HTbool						m_bQuest_WindowActiveSw;
	HTint						m_nQuest_WindowImageID;
	HTvector3					m_vecQuest_WindowPos;
	
	//----------- ����Ʈ ���� ------------//
	HT_QUEST_LIST*				m_pCompleteQuestHead;	// �Ϸ�� ����Ʈ
	HT_QUEST_LIST*				m_pCompleteQuestTail;
	HTint						m_nCompleteQuestNum;
	// ���� �����丮���� ���̸� �����ϱ� ����
	HTbyte						m_byCompleteQuestAlteration[QUEST_MAX_NUM];
	HTbool						m_bCompleteFx;	// �Ϸ� ����Ʈ�� ��������ϴ���..
	HTint						m_iLastCompleteQuestNum; // ���� �Ϸ� ����Ʈ �ε���

	HT_QUEST_LIST*				m_pProgressQuestHead;	// �������� ����Ʈ
	HT_QUEST_LIST*				m_pProgressQuestTail;
	HTint						m_nProgressQuestNum;
	
	// ������ �����丮�� �ִ� â���� �����ϱ� ���� ���
	//BYTE						m_byLastHistroyIndex;	// ������ �����丮�� ����Ʈ index
	//BYTE						m_byLastHistoryVal;		// ������ �����丮 ����Ʈ step
	
	BYTE						m_byNoviceSelNo;
	BYTE						m_byNoviceSlideNo;
	BYTE						m_byScinarioSelNo;
	BYTE						m_byScinarioSlideNo;
	BYTE						m_byRequestSelNo;
	BYTE						m_byRequestSlideNo;

	HTint						m_nLastDlg;					// ���������� ������ �� ��ȣ(�Ǹ��� Dlg�� �и��Ǿ�����)
	HTint						m_nLastProgressSlideVal;
	HTint						m_nLastCompleteSlideVal;

	HT_QUEST_DESCRIPTION		m_sQuestText[QUEST_MAX_NUM];	// ����Ʈ �̸��� �ܰ躰 ����
	HTint						m_nRemainderNum[HT_MOB_COUNT_INDEX_MAX]; // �� ��� ����Ʈ���� ���� �� ����
	HTint						m_nRemainderNum_2[HT_MOB_COUNT_INDEX_MAX];

	//--------- �޼��� â�� ���� ���� -------------//
	BYTE						m_byMessageWin;			//  ���� �޼���â
	CHTString					m_szMessage;			//  ���� �޼���â�� ������ ����
	BYTE						m_byQuestAgreeTime;		// �ʺ��� ����Ʈ �³����� ���� �޼���â ��� Ƚ��

private:
	HTint						m_iSlideNo;
	HTbool						m_bSlideOn;

	HTbool						m_bIsInitChar;		// �α���/��Ż�̵��� �������� �����丮�� ���� ��ư �������� ���ϱ� ���ؼ�
	// ���� ���� ���� ����Ʈ �� ���� ���� ���� �����ϴ� ����Ʈ ���� ����
	HTbyte						m_byMobCountIndex[HT_MOB_COUNT_INDEX_MAX];
	HTbyte						m_byMobCountVal[HT_MOB_COUNT_INDEX_MAX]; 
	HTbyte						m_byMobCountIndexNum;
};
#endif // #ifndef _HTQuest_h_