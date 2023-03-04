//--------------------------------------------------------------------------------//
// ���� : NPC ���� ���(����, �������, ��ũ��/�������Ʈ Ȯ��, ��ǰ���� ��)
// �ۼ����� / �ۼ��� : 2003.4.21 �輱��
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

#define HT_INDEX_REPAIR_QUEST_ITEM		8043	// ���� ����Ʈ ������
#define HT_ITEM_MAKE_MONEY_PENALTY		1.3		// �ֽ������� ������ ���� �� ��� �߰� ���

#define HT_REQ_REFINESCALE_TIME			2.0f	// �峳 ������ �䱸 �ð� ����

#define HT_MAX_LOTTORYNO_CIPHER			8	// ���� ��ȣ �ִ� �ڸ���

//	���� ����
#define NPC_RESENT_NONE					0
#define NPC_RESENT_DIALOG				1
#define NPC_RESENT_ITEM_LIST			2	// ������ ����
#define NPC_RESENT_REFINE				3	// ������ ����
#define NPC_RESENT_FIX					4
#define NPC_RESENT_DISJOINT				5
#define NPC_RESENT_INVENTORY			6	// ��ǰ����
#define NPC_RESENT_SAVEPOSITION			8	// ��ġ���� 
#define NPC_RESENT_PVP_RANK				9	// PVP ���� 
#define NPC_RESENT_TRIMURITI			10	// �ֽ� ����
#define NPC_RESENT_TRIMURITI_SELECT		11
#define NPC_RESENT_TRIMURITI_CHANGE		12	// �ֽ� ����
#define NPC_RESENT_TRIMURITI_POINT		13	// �ֽ� ����Ʈ
#define NPC_RESENT_CREATE_GILD			14	// �ƽ���(���) ����
#define NPC_RESENT_CREATE_GILD_MARK		15	// �ƽ���(���) ��ũ ����
#define NPC_RESENT_CHANGE_JOB2			16
#define NPC_RESENT_REFINE_RATE_UP		17	// �ູ�� �ŷ�
#define NPC_RESENT_TASK_QUEST			18	// �׽�ũ ����Ʈ
#define NPC_RESENT_PREMIUM_ITEM			19	// �����̾� ������ ���� ��� ��û
#define NPC_RESENT_PREMIUM_ITEM2		20	// ��Ű�� �����̾� ������ ���� ��� ��û
#define NPC_RESENT_PREMIUM_ITEM3		21	// �����̾� Ư����� �Ɵ��� ���� ��� ��û
#define NPC_RESENT_REGIST_LOTTERY		51	// �̺�Ʈ ���� - ���� ���
#define NPC_RESENT_CHATURANGA_BOARD		52	// �������� ���� ����
#define NPC_RESENT_QUIZ					53	// ����
#define NPC_RESENT_JOB2_SELECT			54	// 2�� ���� ����
#define NPC_RESENT_EVENTITEM			55	// �̺�Ʈ ������ ���̿��� ������û
#define NPC_RESENT_EVENTCOUPON			56	// �̺�Ʈ ������ ���̿��� ������û

#define	NPC_RESENT_CHAKRA				31
#define	NPC_RESENT_BRAHMAN				32
#define NPC_RESENT_SKILL				33	// ��ų ����Ʈ�� ��û�ϰ� ����� ��ٸ��� ����
#define NPC_RESENT_SKILL_LIST			34
#define NPC_RESENT_SKILL_SELECT			35
#define	NPC_RESENT_SKILL_REMOVE			36
#define NPC_RESENT_EXCHANGE				37	// ������ᱳȯ
#define NPC_RESENT_RESET_CHAKRA			38	// ��ũ����й�

#define NPC_RESENT_USING_ITEM			39	// �����ۻ��

#define NPC_RESENT_PREMIUM_ITEM_BUY		40	// �����̾� ���� ���
#define NPC_RESENT_PREMIUM_2GRADE_INIT	41	// 2�� ���� �ʱ�ȭ

// �޼���â 0:�޼���â�ȶ�,1:�۾��Ϸ�,2:�۾���Ȯ��
#define NPC_MESSAGE_NONE				0
#define NPC_MESSAGE_COMPLETE			1	
#define NPC_MESSAGE_CONFIRM				2

// ���� ��û �ܰ�
#define SERVER_MSG_NONE							0
#define SERVER_MSG_REQ_ITEM_MAKING				1
#define SERVER_MSG_REQ_RESOURCE_BARTER			2

#define SERVER_MSG_RESP_WORK_ITEM_SUB_INIT		8	// �ּ� ���� �ʱ�ȭ
#define SERVER_MSG_RESP_WORK_ITEM_MAIN_INIT		9	// ���� ��� ������ �ʱ�ȭ
#define SERVER_MSG_RESP_WORK_ITEM_REMOVE		10	// ���� ��� ������ �����
#define SERVER_MSG_RESP_WORK_FAIL				11	// ���� ����

#define SERVER_MSG_RESP_ERROR					254	// ����
#define SERVER_MSG_RESP_SUCCESS					255	// ����

// ������ ÷����� ���� ���� 
#define ECONOMY_ADDITEM_ERR_NONE				0	// ÷����� �߰� ���� 
#define	ECONOMY_ADDITEM_ERR_CLASSCOUNT			1	// ÷����� ���� ����
#define	ECONOMY_ADDITEM_ERR_MAIN_OVER			2	// ���� ���� ����
#define	ECONOMY_ADDITEM_ERR_SUB_OVER			3	// ���� ���� ����
#define	ECONOMY_ADDITEM_ERR_IMPOSSIBLE			4	// ÷�� �Ұ��� ����
#define ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM		5	// Ư�� ��� ÷�� �Ұ��� ����
#define ECONOMY_ADDITEM_ERR_ITEMINDEX			6	// �߸��� ������ �ε��� - �������� ã�� ����
#define ECONOMY_ADDITEM_ERR_CANNOT				7	// ���� �ܰ迡���� ���̻� ������ �� ���� ������
#define ECONOMY_ADDITEM_ERR_NEEDNOT				8	// ��ī�� ������Ḧ ����Ͻ� �ʿ䰡 �����ϴ�.

// ����Ʈ �³� ���� ���ð� - Ʃ�丮�� ����Ʈ�� ��� ������ �³���.
#define SELECT_QUEST_OK							0	// ����Ʈ �³�
#define SELECT_QUEST_CANCEL						1	// ����Ʈ �ź�

#define HT_QUIZ_SELECT_NUM						3	// 2�� ���� ����Ʈ�� ���� ���ù� ����

// ������ ���� ���� ���� 
#define RETURN_ITEM_MAKE_FRIENDLY_ERR			-1
#define RETURN_ITEM_MAKE_INFO_ERR				0
#define RETURN_ITEM_MAKE_OK						1
 
// ��ȭ���� ������ �ε���
#define HT_MAIN_REFINE_ILLA_INDEX				6501 // �϶�			
#define HT_MAIN_REFINE_AZISE_INDEX				6502 // ������
#define HT_MAIN_REFINE_SURAPA_INDEX				6503 // ������
#define HT_MAIN_REFINE_DIPAILLA_INDEX			6504 // �����϶�
#define HT_MAIN_REFINE_PRAJATI_INDEX			6505 // ������Ƽ
#define HT_MAIN_REFINE_SAMPAD_INDEX				6506 // ���ĵ�
#define HT_MAIN_REFINE_ZARD_INDEX				6551 // �ڵ�

// ���� �ܰ躰 ���� �޼���
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

// �ֽ� ���� ������ ����
#define HT_TRIMURITI_CHANGE_MONEY1			100000
#define HT_TRIMURITI_CHANGE_MONEY2			1000000
#define HT_TRIMURITI_CHANGE_ITEM			7134
#define HT_TRIMURITI_CHANGE_ITEMNUM			15
#define HT_TRUMURITI_CHANGE_DIVISION_LEVEL	30
// �ֽ� ����Ʈ Ȯ�� ������ ����
#define HT_BRAHMANPOINT_RISING_BRAHMAN		100
#define HT_BRAHMANPOINT_RISING_ITEM			7116
#define HT_BRAHMANPOINT_RISING_ITEMNUM		10
#define HT_BRAHMANPOINT_RISING_MONEY		50000

// �׽�ũ ����Ʈ �ҽ�/���� Ÿ��
typedef enum _eTaskQuestType 
{	
	eTaskQuestTypeNone	= 0,
	eTaskQuestTypeItem,
	eTaskQuestTypeRupiah
};


//----------NPC�������ۺз��� 0:��������,1: ��,2:�׼�����------------//
//HTint g_ItemClass[3] = { 8, 5, 4 };
//---------�������� ������ Ÿ�� ������ ��ȯ ----------//
// 0:�Ѽհ�,1:��հ�, 2:�ܰ�,3:�Ѽյ���,4,�μյ���,5:â,6:����,7:�б�,8:����,9:��ô,10:�Ǻ�,11:����,12:����,13:��Ʈ,14:�Ź�
// 15:����,16:�����,17:�Ͱ���,18:����, 19:����
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

	m_iEconomy_Resent_Item = eEconomy_Item_None;	// ���� ���õ� ������ �з�
	m_byEconomy_Resent_WinIndex = 0;				// ���� ������ â index
	m_iWorkItemCount = 0;

	for(int i = 0 ; i < 8 ; ++i)
	{
		m_Economy_List[i].pInfoHead = m_Economy_List[i].pInfoTail = NULL;
		m_Economy_List[i].vWinCount.clear();
	}

	// ������ ���� ������ KeyID�� ������ �� ��� �ʱ�ȭ
	m_nEconomy_Work_ResRupiah = 0;
	// ������ ���� ������� ������ �� ��� �ʱ�ȭ
	for (HTint i = 0; i<3 ; ++i)
	m_nEconomy_Work_SubItemKeyID[i] = 0;

	// �峳 ���� �ʱ�ȭ
	m_sRefineRateGauge = 0;
	m_bPress_OK_Button = HT_FALSE;
	m_fGaugeTimer = 0;
	for( i = 0 ; i < MAX_ITEM_CONTRIBUTION ; ++i )
		m_iOfferingItemKeyID[i] = 0;
	m_byOfferingItemNum = 0;
	m_dwOfferingRupiah = 0;

	m_pTimer = new CHTTimer;
	m_pTimer->Do( HT_TIMER_START );

	// ��ų
	m_nSkillList_Count = 0;

	// ������ ����
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

	// �峳 ���� �ʱ�ȭ
	m_sRefineRateGauge = 0;
	m_bPress_OK_Button = HT_FALSE;
	m_fGaugeTimer = 0;
	for( HTint i = 0 ; i < MAX_ITEM_CONTRIBUTION ; ++i )
		m_iOfferingItemKeyID[i] = 0;
	m_byOfferingItemNum = 0;
	m_dwOfferingRupiah = 0;
	
	m_pTimer->Do( HT_TIMER_STOP );
	HT_DELETE( m_pTimer );

	// ��ų
	m_nSkillList_Count = 0;
}
 
HTvoid CHTNPCControl::HT_vNPCControl_Active( DWORD dwNPCIndex )
{  
	
	HTint nRes = HT_SCRIPT_NEXTSTEP_SUCCESS;
	switch( dwNPCIndex )
	{
		// ���� ����
		case 1101 :	// ���ٶ�
		case 1109 :	// �ƴ�
		case 1133 :	// ��������
		case 1205 :	// 18�� ���ٶ�
		case 1235 :	// 19�� ���ٶ�
		case 1303 : // ����*# - ���� (īŸ��3)
		{
			m_iEconomy_NPC = m_iEconomy_Resent_Item = eEconomy_Item_Sword;
			// ��ȭ ��ũ��Ʈ ����
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_WEPON);	
		}
			break;

		// �� ����
		case 1102 :	// ���ٶ�
		case 1110 :	// �ƴ�
		case 1127 :	// ��������
		case 1206 :	// 18�� ���ٶ�
		case 1236 :	// 19�� ���ٶ�
		case 1300 : // ������ �����*# - �� (īŸ��3)
		{
			m_iEconomy_NPC = m_iEconomy_Resent_Item = eEconomy_Item_Armor;
			// ��ȭ ��ũ��Ʈ ����
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_DEFENSE);
		}
			break;

		// �׼����� ���� 
		case 1103 :	// ���ٶ�
		case 1111 :	// �ƴ�
		case 1134 :	// ��������
		case 1146 :	// ������
		case 1151 :	// �񽴴� �ֽ���
		case 1152 :	// ����帶 �ֽ���
		case 1153 :	// �ù� �ֽ���
		case 1207 :	// 18�� ���ٶ�
		case 1237 :	// 19�� ���ٶ�
		case 1248 : // ũ�縶(�񽴴�)
		case 1249 : // ũ�縶(����帶)
		case 1250 : // ũ�縶(�ù�)
		case 1331 :	// ��Ÿ��ǰ(�񽴴�)				// �߰� 2005. 11. 15
		case 1332 :	// ��Ÿ��ǰ(����帶)
		case 1333 :	// ��Ÿ��ǰ(�ù�)
		case 1278 :	// ����� ������
		case 1279 :	// ����� ������
		case 1280 :	// ����� ������
		case 1281 :	// ����� ������
		case 1282 :	// ����� ������
		case 1283 :	// ����� ������
		case 1284 :	// ����� ������
		case 1285 :	// ����� ������
		case 1299 : // ����* - �׼����� (īŸ��3)
		case 1304 : // �ϵ� ����� ����
		{
			m_iEconomy_NPC = m_iEconomy_Resent_Item = eEconomy_Item_Bracelet;
			// ��ȭ ��ũ��Ʈ ����
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_ACCESSORY);
		}
			break;

		// �·�
		case 1104 :	// ���ٶ�
		case 1118 :	// ���߶�
		case 1129 :	// ��������
		case 1141 : // ������
		case 1208 :	// 18�� ���ٶ�
		case 1238 :	// 19�� ���ٶ�
		case 1306 : // �ϵ� �޾���
		{ 
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_TEMPLE);
		}
			break;

		//	��ǰ��������
		case 1105 :	// ���ٶ�
		case 1121 :	// �񽴴� �ֽ���
		case 1122 :	// �ù� �ֽ���
		case 1123 :	// ����帶 �ֽ���
		case 1132 :	// ��������
		case 1138 : // ������
		case 1209 :	// 18�� ���ٶ�
		case 1239 :	// 19�� ���ٶ�
		case 1251 : // ũ�縶(�񽴴�)
		case 1252 : // ũ�縶(����帶)
		case 1253 : // ũ�縶(�ù�)
		case 1334 : //	â������(�񽴴�)
		case 1335 : //  â������(����帶)
		case 1336 : //	â������(�ù�)
		case 1301 : //1301	â������ ����
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_WAREHOUSE);
		}
			break;
 
		// �������
		case 1108 :	// ���ٶ� 
		case 1112 :	// ���߶�(�Ƹ���)
		case 1128 : // ��������
		case 1212 : // 18�� ���ٶ�
		case 1242 :	// 19�� ���ٶ�
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_CHIEFGUARD);
		}
			break;

		// ������(����Ʈ)
		case 1106 :	// ���ٶ�
		case 1210 : // 18�� ���ٶ�
		case 1240 :	// 19�� ���ٶ�
//			{
//				if (g_iInationalType != INATIONALTYPE_KOREA)
//					return;
//			}
		case 1257 : // �������� �� �ռ�
		case 1258 : // �������� �� �ռ�
		case 1259 : // �������� �� �ռ�
		case 1260 : // �������� �� �ռ�
		case 1286 : // ����� ������
		case 1287 : // ����� ������
		case 1288 : // ����� ������
		case 1289 : // ����� ������
		case 1290 : // ����� ������
		case 1291 : // ����� ������
		case 1292 : // ����� ������
		case 1293 : // ����� ������
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_POSTHORSE);
		}
			break;
		// �ּ���(���������뿩)
		case 1107 :	// ���ٶ�
		case 1211 :	// 18�� ���ٶ�
		case 1241 :	// 19�� ���ٶ�
		case 1302 : // īŸ��3 ����
		{
			m_iEconomy_NPC = m_iEconomy_Resent_Item = eEconomy_Item_Bracelet;
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_ANIMALLEND);
		}
			break;
		// ����1
		case 1001 :	// ���ٶ�
		case 1113 :	// ���߶�(��ȣ��)
		case 1142 :	// ������ ����� �����
		case 1201 :	// 18�� ���ٶ�
		case 1231 :	// 19�� ���ٶ�
		case 1294 : // ��� ������ ������
		case 1297 : // 1297	����� ������ �߽��� - ETC
		{
			if (!(g_gServerType == SERVERTYPE_MAIN && dwNPCIndex == 1297))
				nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_SOLDIER1);
			else
				return;
		}
			break;
		// ����2
		case 1002 :	// ���ٶ�
		case 1114 :	// ���߶�(�ٹ�)
		case 1143 : // ������ ����� ���
		case 1202 :	// 18�� ���ٶ�
		case 1232 :	// 19�� ���ٶ�
		case 1295 : // ����� ����
		case 1298 : // 1298	���� ���ü� ������ - ETC
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_SOLDIER2);
		}
			break;
		//	���ھ���1
		case 1003 :	// ���ٶ�
		case 1004 :	// �ƴ�
		case 1148 : // ������ ��� �ǳ�
		case 1203 : // 18�� ���ٶ�
		case 1233 : // 19�� ���ٶ�
		case 1307 : // ����� (��Ź���� ������)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_BOY1);
		}
			break;

		//	���ھ���1
		case 1005 :	// ���ٶ�
		case 1006 :	// �ƴ�
		case 1149 : // ������ �Ƴ��� �����
		case 1204 : // 18�� ���ٶ�
		case 1234 : // 19�� ���ٶ�
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_GIRL1);
		}
		break;

		case 1308 : // ����� (��Ź���� �Ǹ���)
		case 1309 : // ����� (��Ź���� �Ǹ���)
		case 1310 : // ����� (��Ź���� �Ǹ���)
		case 1311 : // ����� (��Ź���� �Ǹ���)
		case 1312 : // ����� (��Ź���� �Ǹ���)
		case 1313 : // ����� (��Ź���� �Ǹ���)
		case 1314 : // ����� (��Ź���� �Ǹ���)
		case 1315 : // ����� (��Ź���� �Ǹ���)
		case 1316 : // ����� (��Ź���� �Ǹ���)
		case 1317 : // ����� (��Ź���� �Ǹ���)
		case 1318 : // ����� (��Ź���� �Ǹ���)
		case 1319 : // ����� (��Ź���� �Ǹ���)
		case 1320 : // ����� (��Ź���� �Ǹ���)
		case 1321 : // ����� (��Ź���� �Ǹ���)
		case 1322 : // ����� (��Ź���� �Ǹ���)
		case 1323 : // ����� (��Ź���� �Ǹ���)
		case 1324 : // ����� (��Ź���� �Ǹ���)
		case 1325 : // ����� (��Ź���� �Ǹ���)
		case 1326 : // ����� (��Ź���� �Ǹ���)
		case 1327 : // ����� (��Ź���� �Ǹ���)
		case 1328 : // ����� (��Ź���� �Ǹ���)
		case 1329 : // ����� (��Ź���� �Ǹ���)
		{
			g_cRentalStore->m_iStoreIndex = dwNPCIndex - 1308;
			g_cRentalStore->m_iNPCIndex = dwNPCIndex;
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_GIRL1);
		}
			break;

		// ����Ʈ�� ���� NPC
		case 1115 :	// ���� ����ü
		case 1213 :	// 18�� ���ٶ�
		case 1243 : // 19�� ���ٶ�
		case 1438 : // ���ǳ��� ���� -_-; (īŸ��3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_QUEST_SOLDIER);
		}
			break;
		
		// �������ٴ� ���� NPC
		case 1116 :
		case 1214 : // 18�� ���ٶ�
		case 1244 : // 19�� ���ٶ�
		case 1439 : // ����Ű (īŸ��3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_QUEST_SPORBADA);
		}
			break;

		// �ƹ�Ÿ���� ���� ����
		case 1117 :
		case 1215 : // 18�� ���ٶ�
		case 1245 : // 19�� ���ٶ�
		case 1440 : // ������ ���������� ���� (īŸ��3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_QUEST_BOY);
		}
			break;

		// ������ NPC
		//case 1119 :	// ��ī��
		//case 1216 : // 18�� ���ٶ�
		//case 1246 : // 19�� ���ٶ�
		case 1263 : // ���ٶ� ũ������
		case 1218 :	// ���ٶ� ũ������ 2
		case 1219 : // ���ٶ� ũ������ 3
		case 1264 : // ���߶� ũ������
		case 1265 : // �������� ũ������
		case 1266 : // ������ ũ������
		case 1267 :	// ũ������_����1
		case 1268 :	// ũ������_����2
		case 1269 :	// ũ������_����1
		case 1270 :	// ũ������_����2
		case 1271 :	// ũ������_ũ�縶
		case 1272 :	// ũ������_��������
		case 1273 :	// ũ������_�Ĺ̸�
		case 1274 : // Į���ƴ��� 1
		case 1275 : // Į���ƴ��� 2
		case 1276 : // Į���ƴ��� 3
		case 1277 : // �ϵμ�����
		case 1296 : // �����
		case 1330 : // �����
		case 1340 : // ��������
		{
			// ���� ���μ��� �Ǵ� �ؿ� �߱� �׼������� ũ������ NPC ó���� �����ϴ�. 
			if (!(g_gServerType == SERVERTYPE_TEST && g_iInationalType == INATIONALTYPE_KOREA))
			{
				m_iEconomy_NPC = m_iEconomy_Resent_Item = eEconomy_Item_Bracelet;
				nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_BATTLE);
				break;
			}
			else
				return;
		}

		// ��ġ ����� NPC
		case 1120 :	// ���ٶ� ������
		case 1154 :	// ���߶� ������
		case 1155 :	// ����_1st
		case 1156 :	// ������(����_3rd)
		case 1157 :	// �񽴴� �ֽ���
		case 1158 :	// ����帶 �ֽ���
		case 1159 :	// �ù� �ֽ���
		case 1217 : // 18�� ���ٶ�
		case 1247 : // 19�� ���ٶ�
		case 1254 : // ũ�縶(�񽴴�)
		case 1255 : // ũ�縶(����帶)
		case 1256 : // ũ�縶(�ù�)
		case 1337 : // ������(����)
		case 1338 : // ������(����)
		case 1339 : // ������(����)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_SAVEPOINT);
		}

			break;

		case 1341 : // ���ٶ��� ź �Ҿƹ���
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_EVENTNPC);
		}
		break;

		case 1437 : // ���ٶ��� �������� �̺�Ʈ NPC
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_EXTRA_ETC2);
		}
		break;

		case 1441 : // ������ ����� ���� (īŸ��3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_EXTRA_ETC3);
		}
		break;
		case 1442 : // ���� �ζ��� ���� (īŸ��3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_EXTRA_ETC4);
		}
		break;
		case 1443 : // ���������� ���� (īŸ��3)
		{
			nRes = g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_EXTRA_ETC5);
		}
		break;


		case 9999 :	// ����üũ �� ����üũ���� �����̾� ���� ��ư Ŭ���� ó��
		{
			//m_bPrimium_Button = HT_TRUE;	// �޷��� ������ �ʵ��� ����
			HTint Location = 0;
			if (g_wResentZoneServerID == 1)	// ���ٶ�
				g_cNPCControl->HT_vNPCControl_Active(1263);
			else if (g_wResentZoneServerID == 2) // ���߶�
				g_cNPCControl->HT_vNPCControl_Active(1264);
			else if (g_wResentZoneServerID == 7) // ����
				g_cNPCControl->HT_vNPCControl_Active(1265);
			else if (g_wResentZoneServerID == 9) // ������
				g_cNPCControl->HT_vNPCControl_Active(1266);
			else if (g_wResentZoneServerID == 3) // ũ������_����1
				g_cNPCControl->HT_vNPCControl_Active(1267);
			else if (g_wResentZoneServerID == 4) // ũ������_����2
				g_cNPCControl->HT_vNPCControl_Active(1268);
			else if (g_wResentZoneServerID == 5) // ũ������_����1
				g_cNPCControl->HT_vNPCControl_Active(1269);
			else if (g_wResentZoneServerID == 6) // ũ������_����2
				g_cNPCControl->HT_vNPCControl_Active(1270);
			else if (g_wResentZoneServerID == 10) // ũ�縶
				g_cNPCControl->HT_vNPCControl_Active(1271);
			else if (g_wResentZoneServerID == 11) // ��������
				g_cNPCControl->HT_vNPCControl_Active(1272);
			else if (g_wResentZoneServerID == 8) // �Ĺ̸�
				g_cNPCControl->HT_vNPCControl_Active(1273);
			else if (g_wResentZoneServerID == 13) // Į����1
				g_cNPCControl->HT_vNPCControl_Active(1274);
			else if (g_wResentZoneServerID == 14) // Į����2
				g_cNPCControl->HT_vNPCControl_Active(1275);
			else if (g_wResentZoneServerID == 15) // Į����3
				g_cNPCControl->HT_vNPCControl_Active(1276);
			else if (g_wResentZoneServerID == 12) // �ϵμ�����
				g_cNPCControl->HT_vNPCControl_Active(1277);
			else if (g_wResentZoneServerID == 16) // �����
				g_cNPCControl->HT_vNPCControl_Active(1296);
			else if (g_wResentZoneServerID == 17) // �����
				g_cNPCControl->HT_vNPCControl_Active(1330);
			else if (g_wResentZoneServerID == 18) // ���ٶ�2
				g_cNPCControl->HT_vNPCControl_Active(1218);
			else if (g_wResentZoneServerID == 19) // ���ٶ�3
				g_cNPCControl->HT_vNPCControl_Active(1219);
			else if (g_wResentZoneServerID == 20) // ���ٶ�3
				g_cNPCControl->HT_vNPCControl_Active(1340);
			else
			{
			}
		}

		default :
			return;
	}

	// ��ȭ�� ��ã���� ���
	if( nRes != HT_SCRIPT_NEXTSTEP_SUCCESS )
		return;

	//---------���� NPC�� ���� �ε���---------//
	m_iNPCIndex = dwNPCIndex;
	g_cUIMerchantWindow->m_iNPCIndex = dwNPCIndex;	// v3���� �߰�

	m_byMessageWin = NPC_MESSAGE_NONE;	// �޼��� â �ȶ�����

	// NPC�� �̸�
	//g_pEngineHandler->HT_hrGetNPCName( m_iNPCIndex, &m_szNPCName );
	g_pParamMgr->HT_bGetNPCName( m_iNPCIndex, &m_szNPCName );

	m_pCharPos_Memory = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	m_iResent = NPC_RESENT_DIALOG;
	m_byResent_ServerMsg = SERVER_MSG_NONE;
	m_bNPCActive = HT_TRUE;

	m_nSkillList_Count = 0;
	
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_NPCWINDOW, 1, m_szNPCName );
	
	//if( m_iNPCIndex == 1106 )	// ������ ���ǿ��� ���� ����� ��쿡��
	//{
	//	m_bNextStepByClientEvent = HT_FALSE;
	//	// Ŭ���̾�Ʈ �̺�Ʈ���� �ʱ�ȭ �� �ܰ� ������ �ϱ� ������ ���� ���� ó���Ѵ�.
	//	HT_vNPCControl_ClientEvent();
	//	// Ŭ���̾�Ʈ �̺�Ʈ���� �ʱ�ȭ �� �ܰ� ������ �ȵ��� ��츸 ó��
	//	if( m_bNextStepByClientEvent == HT_FALSE ) 
	//		HT_vNPCControl_ServerEvent();
	//}

	HT_vNPCControl_SetText();		// ȭ�鿡 ������ ��ȭ ���� 

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
	
	// ������ 3�� �� ��
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
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vNPCControl_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vNPCControl_SetParamTextForMessage( sParam2, &szOut2 );
		
		m_szMessage.HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
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
		// �ٸ� ĳ���� �̸�
		case eMsgParamOthercharName	:
			*pszParam = m_szObjectName; break;
		// �ֽ� �̸�
		case eMsgParamTrimuritiName	:
			if( m_iResent == NPC_RESENT_TRIMURITI_SELECT )	// �ֽ� ������ ���
				*pszParam = g_cStatus->HT_szStatus_GetTrimuriti();
			else if( m_iResent == NPC_RESENT_TRIMURITI_CHANGE )	// �ֽ� ���� Ȯ�� �޼���
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
		// ���� �̸�
		case eMsgParamJobName			:
			*pszParam = g_cStatus->HT_szStatus_GetJobName(); break;
		// ������ ������ �̸�
		case eMsgParamBuyItemName		:
			g_pParamMgr->HT_bGetItemName( m_dwBuyItem, pszParam ); break;
		// ����/�Ǹ�/���� ������ �̸�
		case eMsgParamItemName			:
			// ����
			//if( m_iResent == NPC_RESENT_ITEM_LIST )
			//	g_pParamMgr->HT_bGetItemName( m_dwBuyItem, pszParam );
			// ����
			/*else*/ if( m_iResent == NPC_RESENT_REFINE )	
			{
				DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwWorkItem );
				g_pParamMgr->HT_bGetItemName( dwIndex, pszParam );
			}
			// ����/�Ǹ�
			else if( m_iResent == NPC_RESENT_FIX || m_iResent == NPC_RESENT_DISJOINT || m_iResent == NPC_RESENT_ITEM_LIST )
			{
				DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwFixDisjointKeyID );
				g_pParamMgr->HT_bGetItemName( dwIndex, pszParam );
			}
			break;
		// �ʿ��� ������ �̸�
		case eMsgParamNeedItemName	:	
		{
			if( m_iResent == NPC_RESENT_TRIMURITI_CHANGE )		// �ֽ� ����
				g_pParamMgr->HT_bGetItemName( HT_TRIMURITI_CHANGE_ITEM, pszParam );
			else if( m_iResent == NPC_RESENT_TRIMURITI_POINT )	// �ֽ� ����Ʈ ����
				g_pParamMgr->HT_bGetItemName( HT_BRAHMANPOINT_RISING_ITEM, pszParam ); 
		}
			break;
		// ���� ��� ������ �̸�
		case eMsgParamSubItemName		:
		{
			DWORD dwRefineIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[0] );
			if( dwRefineIndex > 0 )
				g_pParamMgr->HT_bGetItemName( dwRefineIndex, pszParam );
		}
			break;

		// �ʿ��� ��
		case eMsgParamNeedMoney		:	
		{
			HTint iRupiah = 0;
			if( m_iResent == NPC_RESENT_ITEM_LIST )	// ����
			{	
				*pszParam = g_cUIManager->HT_strSetRestMark( m_nEconomy_Work_LimitRupiah ); // ��ǥ ó��
			}
			else if( m_iResent == NPC_RESENT_REFINE )	// ����-������ ��
			{
				HTint iRupiah = m_nEconomy_Work_LimitRupiah - g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
				if( iRupiah < 0 )
					iRupiah = 0;
				pszParam->HT_szFormat( "%d", iRupiah );
			}
			else if( m_iResent == NPC_RESENT_TRIMURITI_CHANGE )	// �ֽ� ����
			{
				HTbyte byLevel = g_cStatus->HT_byGetLevel();
				HTfloat fPrice = HT_bNPCControl_CheckTrimuritiChangeCost();

				if( byLevel < HT_TRUMURITI_CHANGE_DIVISION_LEVEL )
					pszParam->HT_szFormat( "%d", (HTint) fPrice );
				else
					pszParam->HT_szFormat( "%d", (HTint) fPrice );
			}
			else if( m_iResent == NPC_RESENT_TRIMURITI_POINT )	// �ֽ� ����Ʈ ����
				pszParam->HT_szFormat( "%d", HT_BRAHMANPOINT_RISING_MONEY );
		}
			break;
		
		// �ʿ��� ��¥
		case eMsgParamNeedDay		:
			break;
		// ���� ��¥
		case eMsgParamRemainDay		:
			break;

		// ���/ȹ���� ��
		case eMsgParamSpendingMoney	:	
			//pszParam->HT_szFormat( "%d", m_iSpendMoney );
			*pszParam = g_cUIManager->HT_strSetRestMark( m_iSpendMoney ); // ��ǥ ó��
			break;
		// ������ ���� ����
		case eMsgParamBuyItemNum		:	
			pszParam->HT_szFormat( "%d", m_iWorkItemCount );
			break;
		// ������ ���� ���� �ִ� ����
		case eMsgParamBuyItemMaxNum	:	
		{
			HTbyte byteMaxCount = 0;
			if( g_pParamMgr->HT_bGetItemMaxCount( m_dwBuyItem, &byteMaxCount ) == true )
				pszParam->HT_szFormat( "%d", byteMaxCount );
		}
			break;
		// ������ ���� �ּ� ����
		case eMsgParamBuyItemMinNum :
			pszParam->HT_szFormat( "%d", m_iWorkItemMinCount );
			break;
		// ��ȭ���� ����
		case eMsgParamMainRefineLevel	:
		{
			HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( m_dwWorkItem );
			pszParam->HT_szFormat( "%d", byLevel );
		}
			break;

		// �ʿ��� ������ ����
		case eMsgParamNeedItemNum		:
			if( m_iResent == NPC_RESENT_TRIMURITI_POINT )	// �ֽ� ����Ʈ ����
				pszParam->HT_szFormat( "%d", HT_BRAHMANPOINT_RISING_ITEMNUM );
			break;
		// �ʿ��� �ֽ� ����Ʈ 
		case eMsgParamNeedTrimuritiPoint :
			pszParam->HT_szFormat( "%d", HT_BRAHMANPOINT_RISING_BRAHMAN );
			break;

		default:
			break;
	}
}

//---------- �����ܰ�� ��ȭ���� ��ȭ �ٲٱ� -----------//
HTvoid CHTNPCControl::HT_vNPCControl_GetNextStep(HTint nSelNum)
{
	HTint res = g_pEngineHandler->HT_nNextStep(nSelNum);

	if( res == HT_SCRIPT_NEXTSTEP_FAIL)
	{
		res = g_pEngineHandler->HT_nSetFirstStep();	// ó�� �ܰ�� �ǵ�����.
	}
 
	if(res == HT_SCRIPT_NEXTSTEP_SUCCESS)	// ���� �ܰ��� ��� ��ȭ ����
	{
		m_bNextStepByClientEvent = HT_FALSE;
		// Ŭ���̾�Ʈ �̺�Ʈ���� �ʱ�ȭ �� �ܰ� ������ �ϱ� ������ ���� ���� ó���Ѵ�.
		HT_vNPCControl_ClientEvent();
		if( m_bNextStepByClientEvent == HT_FALSE ) 
		{	// Ŭ���̾�Ʈ �̺�Ʈ���� �ʱ�ȭ �� �ܰ� ������ �ȵ��� ��츸 ó��
			HT_vNPCControl_SetText();	// ȭ�鿡 ������ ��ȭ ���� 
			HT_vNPCControl_ServerEvent();

		}
	}
	else if( res == HT_SCRIPT_NEXTSTEP_EQUALSTEP ) 
	{
		/* �������� ���/��ũ�� ����Ʈ Ȯ��->���� �� ��� 
	   ���ǹ��� �ʿ���/����� ���� ���� �����ϱ� ���� ���ǹ��� �ٽ� ����. */
		if( m_iResent == NPC_RESENT_CHAKRA || m_iResent == NPC_RESENT_BRAHMAN )
		{
			HTtchar text[HT_SCRIPT_QUE_MAXSIZE] ;
			sprintf(text, m_szQuestion, m_dwNeedValue); // �Ķ���� �� ����
		
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_NPCWINDOW, 2, text);
		}
		// ����/�Ǹ� �����ÿ��� res == HT_SCRIPT_NEXTSTEP_EQUALSTEP �ε� ��ȭâ�� �ٲ� ������ ����.
	}
	else //if( res == HT_SCRIPT_NEXTSTEP_FAIL )	// ó�� �ܰ�� �ǵ����� �͵� ���������Ƿ� ��ȭ ���� �ݱ�
	{
		//	��ȭ���� �ݱ� - NPC�� ���õ� ��� â ����
		HT_vNPCControl_DialogWin_AntiActive();
	}
}

//-------------- ȭ�鿡 ������ ��ȭ ���� --------------------//
HTvoid CHTNPCControl::HT_vNPCControl_SetText()
{
	CHTString strTemp;
	
	//	NPC�� ���ǹ�
	ZeroMemory(m_szQuestion, sizeof(HTtchar)*HT_SCRIPT_QUE_MAXSIZE);
	m_byParameter = eNpcParamNone;
	g_pEngineHandler->HT_vGetQuestion( m_szQuestion, &m_byParameter );
 
	if( m_byParameter != eNpcParamNone )
		HT_vNPCControl_SetParameterText();
	
	HTtchar cText[HT_SCRIPT_QUE_MAXSIZE];
	ZeroMemory(cText, sizeof(HTtchar)*HT_SCRIPT_QUE_MAXSIZE);

	if(m_byParameter == eNpcParamNeedPrana || m_byParameter == eNpcParamCashRemain 
		|| m_byParameter == eNpcParamChangeGodReqRupia || m_byParameter == eNpcParamEventItemTotal
		|| m_byParameter == eNpcParamDurgaReceiptofMoney) // �ʿ�������||���� ĳ��
 		wsprintf(cText, m_szQuestion, m_dwNeedValue); // �Ķ���� �� ����
	else if( m_byParameter != eNpcParamNone )
		wsprintf(cText, m_szQuestion, m_szName.HT_szGetString()); // �Ķ���� �� ����
	else
		wsprintf(cText, m_szQuestion);

	HT_RECT Rect; Rect.left = 0; Rect.top = 0; Rect.right = 311; Rect.bottom = 130;
	int strlength = g_pEngineHandler->HT_iGetTextHeight(HT_FONT_GULIM_12, cText, Rect, TEXT_FORMATING_MULTILINE_VTOP_LEFT_CLIP );
	g_cUIManager->HT_SetTextLongLabelControl( _DIALOG_NPCWINDOW, 2, cText);

	g_cUINPCWindow->m_StartPosY = strlength+125;
	//	���ù�
	m_nSelectCount = 0;
	g_cUINPCWindow->HT_vNPCWindow_SetInfo();

	// ECONOMY_RESENT_SKILL_LIST ��쿣 select�� ��ġ�� ��ų ����Ʈ�� �̹� �� ����
	if( (m_iResent != NPC_RESENT_SKILL_LIST && m_iResent != NPC_RESENT_SKILL_REMOVE ) || (m_nSkillList_Count == 0) )	
	{
		//	���ù�_���� ��ư Ŭ�����ϱ�
	}

//	for (HTint i = 1; i <= MAX_SELECT_COUNT; ++i)
//		g_cUIManager->HT_SetButtonEnable(_DIALOG_NPCWINDOW, i, true);

	// ���� �������� ���ǹ��� �ε����� ��� �´�.
	HTint iQuestion = g_pEngineHandler->HT_iGetNowQuestionIndex();
 
	for( HTint i=0 ; i < MAX_SELECT_COUNT ; ++i)
	{
		g_pEngineHandler->HT_vGetSelectText(i, strTemp );

		// �ش� ���ǹ��� ���� ��쿡�� �ش� �������� ��� ���ù��� ����� �����Ѵ�. (�ؿ��������� ������ �ȵǴ� ���� �����Ƿ�.. ) 2004. 12. 1 ������
		if (g_wResentZoneServerID == 17) // ������� �ش�
		{
			if ( !(g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_MAHARAJA && g_pSiege->HT_vSiege_GetOwerOfCastle() == true) && iQuestion == 20001 && i==2 ) 
				continue;

			if (g_pSiege->HT_vSiege_GetOwerOfCastle() == false && iQuestion == 80201 && i==2 )
				continue;

		}
	
		if (g_wResentZoneServerID == 7) // �������� �в����� ���ù��� ���������� ����Ʈ �Ϸ��Ŀ��� ��
			if ( g_cUIQuestWindow->g_bMoonBang != true && iQuestion == 42025 && i == 2) 
				break; 

		if( g_iInationalType == INATIONALTYPE_PHILIPPINE )
		{
			if(iQuestion == 110001) if (i==1) continue;		// ������
			if(iQuestion == 110001) if (i==2) continue;		// ������
		}
		else if( g_iInationalType != INATIONALTYPE_KOREA )
		{
			if(iQuestion == 110001) if (i==2) continue;		// ������
			
			if (g_wResentZoneServerID == 9) // ���������� �ش�
			{
				if(iQuestion == 20210) if (i==2) continue;		// ��ѿ��� ���׷��̵�
				if(iQuestion == 20211) if (i==2) continue;		// ��ѿ��� ���׷��̵�

				if(iQuestion == 20210) if (i==3) continue;		// ��ѿ��� ���׷��̵�
				if(iQuestion == 20211) if (i==3) continue;		// ��ѿ��� ���׷��̵�
			}
		}
		if( g_iInationalType != INATIONALTYPE_KOREA )		// �ѱ��� ������ ���󿡼��� Ÿ�ϱ��� �޴��� ���� ���� (ũ������)
		{
			if(iQuestion == 100001) if (i==6) continue;

		}

		if(strTemp.HT_nGetSize() == 0)	// ���̻� ���ù��� ����
			break;

		g_cUIManager->HT_SetTextLabelControl( _DIALOG_NPCWINDOW, i+m_nSkillList_Count+3, strTemp);

	}
	m_nSelectCount = i;	// ���ù� ����

	if (m_nSelectCount+1 < MAX_SELECT_COUNT)
		for (HTint i = 1; i <= MAX_SELECT_COUNT; ++i)
		{
			CHTString str;
			str = g_cUIManager->HT_GetTextLabelControl(_DIALOG_NPCWINDOW, i+2);
			if (strcmp(str, "") == 0)
				g_cUIManager->HT_SetButtonEnable(_DIALOG_NPCWINDOW, i, false);
		}
}

//------------- ���ǹ��� ������ parameter text���� ---------------//
HTvoid CHTNPCControl::HT_vNPCControl_SetParameterText()
{
	switch( m_byParameter )
	{
		case eNpcParamNeedPrana : // �ʿ�������
			m_dwNeedValue = 0;
			break;
		case eNpcParamCharacterName : // ĳ�����̸�
			m_szName = g_oMainCharacterInfo.szCharName;
			break;
		case eNpcParamSkillName : // ��ų�̸�
			m_szName = HT_szNPCControl_GetSelectSkillName();
			break;
		case eNpcParamChakraName : // ��ũ���̸�
			g_cQuest->HT_vQuest_GetChakraText(m_szName);
			break;
		case eNpcParamTribeName : // �����̸�
			m_szName = g_cMainCharacter->HT_strMainChar_GetTribe();
			break;
		case eNpcParamTrimuritiName : // �ֽ��̸�
		{
			if( g_oMainCharacterInfo.byTrimuriti == 0 ) // �ֽż��� ������
				m_szName.HT_hrCleanUp();
			else
				m_szName = g_cStatus->HT_szStatus_GetTrimuriti();
		}
			break;
		case eNpcParamGuildName : // �ƽ����̸�
			m_szName = g_cGuildSystem->HT_strGuild_GetGuildName();
			break;
		case eNpcParamJobName : // �����̸�
			m_szName = g_cStatus->HT_szStatus_GetJobName();
			break;
		case eNpcParamCashRemain : // ���� ĳ��
			m_dwNeedValue = m_nCash;
			break;
		case eNpcParamInitializeReqRupia : // ��ũ��/��ų �ʱ�ȭ�� �ʿ��� ���Ǿƾ�
			{
				m_nLevel = g_cStatus->HT_byGetLevel();
				m_nNowRupia = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
				m_dwNeedValue = m_nNeedRupia = (int(pow((double)m_nLevel, 2.95)*10 + 990)/100)*100;
				m_szName.HT_szFormat("%d",m_nNeedRupia);
			}
			break;
		case eNpcParamChangeGodReqRupia : // �ֽ� ���濡 �ʿ��� ���ǾƷ� ���
			{
				HTfloat fPrice = HT_bNPCControl_CheckTrimuritiChangeCost();
				m_dwNeedValue = (HTint) fPrice;
			}
			break;
		case eNpcParamEventItemTotal : // �̺�Ʈ ������ ��������
			{
				m_dwNeedValue = m_iEventItem;
			}
			break;
		case eNpcParamDurgaState :
			{ 
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg14, &strString );	//���� ��簡 : [%s]>>�ƺ� ��簡 : [%s]>>�ܹ� ��簡 : [%s]>>���� ��簡 : [%s]
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
				//HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg14, &strString );	//���� ��簡 : [%s]>>�ƺ� ��簡 : [%s]>>�ܹ� ��簡 : [%s]>>���� ��簡 : [%s]
				//m_szName.HT_szFormat(strString, str2);
				m_szName = str2;
			}
			break;
		default : m_szName.HT_hrCleanUp(); break;
	}
}

//-----���� �ܰ迡�� �ؾ��� ���� ��û ����--------//
HTvoid CHTNPCControl::HT_vNPCControl_ServerEvent()
{
	HTshort event = g_pEngineHandler->HT_sGetServerEvent();
	if( event == eNpcSEventReqNone )
		return;
	
	switch( event )
	{
		case eNpcSEventReqItemList : // �����۸���Ʈ��û
			g_cUIMerchantWindow->HT_vMerchantWindow_SetBuyList();
			//HT_vNPCControl_GetItemList();
			break;
		case eNpcSEventReqRank : // ��������Ʈ��û
			// ���� ����Ʈ ��û�ϴ� ��Ʈ�� �Լ� ȣ���ؾ���
			//MessageBox(NULL, "��������Ʈ��û", "��������Ʈ��û", MB_OK);
			break;
		case eNpcSEventReqTrimuritiSelect : // �ֽż��ÿ�û
			m_bTrimutiri = 1;
			HT_vNetWork_CSP_Req_Select_Trimuriti(m_bTrimutiri);
			break;
		case eNpcSEventReqTrimuritiChange : // �ֽź����û
		{
			/*
			// ���Ϻ��� ������� �˸�.
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "��Ȯ�� �ֽź��� ����� �����ϴ� �Ⱓ�Դϴ�.");
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "�ֽź��� ��������� 2005. 3. 16(��) ����10�ú��� �����մϴ�.");
			*/
			// ���� �ֽ������� �������̶�� �ֽ����� ������ �ٽ� �õ����ֽʽÿ�. ��� �޽��� ���
			DWORD dwKeyID, dwindex;
			CHTString strString;
			dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID(0);
			dwindex = g_cItemSystem->HT_dwSystem_GetItemIndex(dwKeyID);
			if (dwindex >= 5379 && dwindex <= 5390) // ���� �ֽ����� �������̶��
			{
				HT_g_Script_SetMessage( eMsgCommonCannotGodChange, &strString );	// �ֽ����� ������ �ٽ� �õ����ֽʽÿ�.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				break;
			}
			
			// ��Ȯ��â ���� - �ֽ��� @@������ �����Ͻðڽ��ϱ�?
			HT_vNPCControl_SetMessage( eMsgTrimuritiChangeQuestion );
			
			m_bMessage_Error = HT_FALSE;	// ����
			m_byMessageWin = NPC_MESSAGE_CONFIRM;

			g_cUINPCWindow->m_MessageBoxNo = 1;
			g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 1);
		}
			break;
		case eNpcSEventReqTrimuritiPoint : // �ֽ�����Ʈ��û
			g_pNetWorkMgr->RequestBrahmanPointRising();
			break;
		case eNpcSEventReqChangeJob : // ������û
			HT_vNetWork_CSP_REQ_Change_Job();
			break;
		case eNpcSEventReqSkillLearn : // ��������û
			m_szName = HT_szNPCControl_GetSelectSkillName(); 
			break;
		case eNpcSEventReqQuestAllow : // ����Ʈ �³� ��û
		{
			BYTE byQuestIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();
			if( byQuestIndex == QUEST_SHAMBALA_14 ) // 2�� ����-���� ����Ʈ�� ���� ����� ���
			{
				if( m_bMessage_Error == HT_FALSE ) // ���� ����
					g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG( byQuestIndex, 1);	// ��� ����
				else // ���� ����
					g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG( byQuestIndex, 2);	// Ʋ��
			}
			else // ��ũ��/��ų �ʱ�ȭ
				g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG( byQuestIndex, SELECT_QUEST_OK);	// �³�
		}
			break;
		case eNpcSEventReqCouponRegister : // ���� ��� ��û
		{
			g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( 0 , /*0,*/ ITEM_PLACE_EVENT, m_szLottoryNum.HT_szGetString()  );
		}
			break;
		//--------- �׽�ũ ����Ʈ ��û ---------//
		case eNpcSEventReqTaskQuest :
		{
			if( HT_bNPCControl_CheckSourceForTaskQuest( m_iTaskQuestID ) )
			{
				// �ӽ� ����
				//if( g_gServerType == SERVERTYPE_MAIN && m_iTaskQuestID >= TASK_QUEST_66_START && m_iTaskQuestID <= TASK_QUEST_67_END)
				//{
				//	// ����Ʈ ���� ��ȭ�� �Ѿ
				//	m_bMessage_Error = HT_TRUE;		// ���� ����
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
				// ����Ʈ ���� ��ȭ�� �Ѿ
				m_bMessage_Error = HT_TRUE;		// ���� ����
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 
			}
		}
			break;
		case eNpcCEventReqExpandInven :	// �κ��丮 Ȯ�� (�����̾� ���)
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqInvenExpandBuy );

				m_bMessage_Error = HT_FALSE;	// ����
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
				//	HT_vNetWork_CSP_Resp_Charge_Function_Item( HT_INDEX_EXPAND_INVEN );
			}
			break;
		case eNpcSEventReqExpandPrivateShop	:// ���λ��� Ȯ�� (�����̾� ���)
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqInvenExpandBuy );

				m_bMessage_Error = HT_FALSE;	// ����
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			} 
			break;
		case eNpcSEventReqCash : // ĳ������ ��û
			HT_vNetWork_CSP_Req_Item_Cash();
			break;
		case eNpcSEventReqInitialize : // ��ų/��ũ�� ��й� ��û
			if( g_iInationalType == INATIONALTYPE_INDONESIA || g_iInationalType == INATIONALTYPE_PHILIPPINE )
                HT_vNetWork_CSP_Req_CharacterInitialize();	// ��û
			break;
		case eNpcSEventReqCharacterInitialize : // ��ų/��ũ�� ��й� ���� ��û (��ũ��)
			if( g_iInationalType == INATIONALTYPE_INDONESIA || g_iInationalType == INATIONALTYPE_PHILIPPINE )
                HT_vNetWork_CSP_Req_CharacterInitialize(1,2);
			break;
		case eNpcSEventReqCharacterInitialize2 :// ��ų/��ũ�� ��й� ���� ��û (��ų)
			if( g_iInationalType == INATIONALTYPE_INDONESIA || g_iInationalType == INATIONALTYPE_PHILIPPINE )
                HT_vNetWork_CSP_Req_CharacterInitialize(1,1);
			break;
		case eNpcSEventReqAutoRouting : // �ڵ� ���ݱ� ��û
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqInvenExpandBuy );

				m_bMessage_Error = HT_FALSE;	// ����
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			}
			break;
		case eNpcSEventReqinitChacra : // ��ũ�� �ʱ�ȭ (�����̾� ���) / 1015
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqChkraInitQuestion );

				m_bMessage_Error = HT_FALSE;	// ����
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			}
			break;
		case eNpcSEventReqinitSkill : // ��ų �ʱ�ȭ (�����̾� ���) / 1016
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqSkillInitQuestion );

				m_bMessage_Error = HT_FALSE;	// ����
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			}
			break;
		case eNpcSEventReqinitChacraSkill : // ��ũ��&��ų �ʱ�ȭ (�����̾� ���) / 1017
			{
				m_iResent = NPC_RESENT_PREMIUM_ITEM_BUY;
				HT_vNPCControl_SetMessage( eMsgPremiumReqChkraSkillQuestion );

				m_bMessage_Error = HT_FALSE;	// ����
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			}
			break;
		case eNpcSEventReqEventItemTotal : // �̺�Ʈ ������ ���̿��� ���� ���� ��û
			{
				m_iResent = NPC_RESENT_EVENTITEM;
				m_iEventItem = 0;
				g_cNPCControl->HT_vNetWork_CSP_Req_CharacterInitialize(1, 5);
				//g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( g_cItemSystem->HT_dwItemSystem_GetKeyIDInPCInventoryForIndex(7073), 0x01 );
			}
			break;
		case eNpcSEventReqDrugaMoneyOut : 
			{
				g_pNetWorkMgr->RequestRefineScale(); // ���� �����ݾ� ��ȸ��û
			}
			break;
		case eNpcSEventReqJopChangeInit : // 2�� ���� �ʱ�ȭ ��û
			// ��Ȯ��â �޽����� ���
			{

				// Step2) �������� ���� �� ���� ���̸� ���з� ó��
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
					// ���н� �ȳ�â ���
					HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// ���� �ܰ�� �Ѿ
					HT_vNPCControl_SetMessage( eMsgPremiumReq2GradeInitErr2 );
					m_bMessage_Error = HT_TRUE;
					m_byMessageWin = NPC_MESSAGE_COMPLETE;
					break;
				}


				// Step1) �̹� 2�������� �ߴٸ� �����Ұ� ó��
				if( g_oMainCharacterInfo.byClass1 != CLASS_LEVEL2 )	// 2�� ������ ��쿡�� ó��
				{

					// ���н� �ȳ�â ���
					HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// ���� �ܰ�� �Ѿ
					HT_vNPCControl_SetMessage( eMsgPremiumReq2GradeInitErr );
					m_bMessage_Error = HT_TRUE;
					m_byMessageWin = NPC_MESSAGE_COMPLETE;
					break;
				}

				m_iResent = NPC_RESENT_PREMIUM_2GRADE_INIT; // ���� ���
				HT_vNPCControl_SetMessage( eMsgPremiumReq2GradeInit ); // �޽��� ���ҽ����� �ҷ�����

				m_bMessage_Error = HT_FALSE;	// (����)
				m_byMessageWin = NPC_MESSAGE_CONFIRM;	// �޽��� ���� ���� (����)

				// �ش�޽����� �ش� ���̾�α׷� ������.
				// ��Ȯ��â�� ������ �����Ͽ� ȭ�鿡 �ѷ��ش�.
				// Ÿ�̸� ����
			}
			break;
		default :
			break;
	}
}

//-----���� �ܰ迡�� �ؾ��� Ŭ���̾�Ʈ �̺�Ʈ--------//
HTvoid CHTNPCControl::HT_vNPCControl_ClientEvent()
{
	HTshort event = g_pEngineHandler->HT_sGetClientEvent();
	if( event == eNpcCEventNone )
		return;
	

	CHTString strTemp;

	switch( event )
	{
		case eNpcCEventDialog : // ��ȭ���
		{
			// �Ϲ� Ŀ���� ����
			if(g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE)
				g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);

			if(m_iResent == NPC_RESENT_ITEM_LIST)
			{
				// ����Ʈ �׸� �����
				HT_vNPCControl_ButtonCheck_List_Delete();
			}

			m_iResent = NPC_RESENT_DIALOG;
			m_dwNeedValue = 0;
			m_szName.HT_hrCleanUp();
		}
			break;
		case eNpcCEventItemMake : // ���Ը��
		{
			g_cUIMerchantWindow->HT_vMerchantWindow_SetBuyList();
			HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);
			m_iResent = NPC_RESENT_ITEM_LIST;
		}
			break;
		case eNpcCEventFix : // �������
		{
			m_iResent = NPC_RESENT_FIX;
			// �κ��丮 â ���
			HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);	

			// ���� ����â�̳� �����̾� â�� �����ִٸ� �ݾ��ش�.
			if (g_cUIManager->HT_isShowWindow(_DIALOG_MERCHANT_PREMIUM) == true)
				g_cUIManager->HT_HideWindow(_DIALOG_MERCHANT_PREMIUM);

			if (g_cUIManager->HT_isShowWindow(_DIALOG_MERCHANT) == true)
				g_cUIManager->HT_HideWindow(_DIALOG_MERCHANT);
		}
			break;
		case eNpcCEventDisjoint : // ��ü���
		{
			m_iResent = NPC_RESENT_DISJOINT;
			// �κ��丮 â ���
			HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);	
		}
			break;
		case eNpcCEventChakraUp : // ��ũ��Ȯ����
		{
			m_iResent = NPC_RESENT_CHAKRA;
			// ĳ���� ����â ����
			HT_vNPCControl_PopUpInventory(_DIALOG_CHARINFO);
		}
			break;
		case eNpcCEventTrimuritiSelect : // �ֽż��ø��
			m_iResent = NPC_RESENT_TRIMURITI;
			m_bySelectPart = 0;
			break;
		// ��� �ּ���(7134) 15��
		case eNpcCEventTrimuritiChange : // �ֽź�����
			m_iResent = NPC_RESENT_TRIMURITI_CHANGE;
			m_bySelectPart = 0;
			break;
		case eNpcCEventCreateGuild : // �ƽ����������
		{
			m_iResent = NPC_RESENT_CREATE_GILD;
			g_cGuildSystem->HT_vGuild_Create();
		}
			break;
		case eNpcCEventCreateGuildMark : // �ƽ�����ũ�������
		{
			m_iResent = NPC_RESENT_CREATE_GILD_MARK;
			// �ƽ��� ��ũ���� â ����
			g_cGuildSystem->HT_vGuild_AmblemMakeActive();
		}
			break;
		case eNpcCEventChangeJob2 : // 2�� �������
			m_iResent = NPC_RESENT_CHANGE_JOB2;
			break;
		case eNpcCEventBramanPointUp : // ���Ȯ����
		{
			m_iResent = NPC_RESENT_BRAHMAN;
			// ĳ���� ����â ����
			HT_vNPCControl_PopUpInventory(_DIALOG_CHARINFO);
		}
			break;
		case eNpcCEventInventory : // ��ǰ�������
		{	
			// NPC Inventory�� �����۵��� ���̰� �Ѵ�.
			m_iResent = NPC_RESENT_INVENTORY;
			
			// ���밡��/�Ұ��� �� ����
			g_cItemSystem->HT_vItemSystem_RenewalPossibleBar(_DIALOG_GOODSKEEPWND);
			g_cUIManager->HT_ShowWindow( _DIALOG_GOODSKEEPWND );
			HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);	// �κ��丮 â ���
		}
			break;
		case eNpcCEventSavePosition : // ��ġ������
		{
			m_iResent = NPC_RESENT_SAVEPOSITION;
			
			// �����Ұ����� ��Ȯ�� �޼��� ����
			// ���� ��ġ�� ���� �Ͻðڽ��ϱ�?
			HT_vNPCControl_SetMessage( eMsgSavePositionQuestion );
			
			m_bMessage_Error = HT_FALSE;	// ����
			m_byMessageWin = NPC_MESSAGE_CONFIRM;
			
			g_cUINPCWindow->m_MessageBoxNo = 0;
			g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW , m_szMessage, 1);
		}
			break;
		case eNpcCEventRank : // �����������
		{
			m_iResent = NPC_RESENT_PVP_RANK;
			//	���� ����Ʈâ ����
			//	��ŷ����� ���� â���ٰ� ����ϰ� ���� ���ºκ�
		}
			break;
		case eNpcCEventEvent : // �̺�Ʈ ��� ���
		{
			m_iResent = NPC_RESENT_REGIST_LOTTERY;
			// ���� ��ȣ ����ϱ� ���� �Է�â ����
			HT_g_Script_SetMessage( eMsgSerialNumber, &strTemp, _T("") );		//	"�Ϸ� ��ȣ"
			HT_g_Script_SetMessage( eMsgEnlistmentNotice, &strTemp, _T("") );		//	"[�Կ� ������]�� "
			HT_g_Script_SetMessage( eMsgSerialNumber, &strTemp, _T("") );		//	"�Ϸ� ��ȣ"
			m_szLottoryNum.HT_hrCleanUp(); // ���� �Է�â �ʱ�ȭ
		}
			break;
		case eNpcCEventChaturangaBoard : // �������� ���� ���� ���
			m_iResent = NPC_RESENT_CHATURANGA_BOARD;
			// �������� ���� ����
			HT_vNPCControl_ActiveChaturangaBoard();
			break;
		case eNpcCEventQuiz : // ����
			m_iResent = NPC_RESENT_QUIZ;
			m_iQuestQuizCount = 0; // ���� ��ȣ
			break;
		case eNpcCEventReqPriItemList : // ���� ��� ��� - ���� ����Ʈ ����� (�����̾� ������)
			m_iResent = NPC_RESENT_PREMIUM_ITEM;
			break;
		case eNpcCEventReqPriItemList2 :// ���� ��� ��� - ���� ����Ʈ ����� (��Ű�� �����̾� ������)
			m_iResent = NPC_RESENT_PREMIUM_ITEM2;
			break;
		case eNpcCEventReqPriItemList3 :// ���� ��� ��� - ���� ����Ʈ ����� (��Ű�� �����̾� ������)
			m_iResent = NPC_RESENT_PREMIUM_ITEM3;
			break;
		case eNpcCEventReqEventItem : // �̺�Ʈ ������ ��� ��û (���̿���, �ĸ���) 3029
			m_iResent = NPC_RESENT_EVENTITEM; 
			// ���� �������� ���� ������ �־�� �����ϵ��� ����.
			// �κ��丮 ���� üũ
			if (g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck() < 1)
			{
				// ���� ������ �����ϸ� ������� ���ϰ� �Ѵ�
				CHTString strString;
				HT_g_Script_SetMessage( eMsgItemCommonInvenLack, &strString );	// �κ��丮 ������ �����մϴ�.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				return;
			}

			g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( g_cItemSystem->HT_dwItemSystem_GetKeyIDInPCInventoryForIndex(7079), 0x01 );
			break;
		case eNpcCEventReqDrugaMoneyIn : 
			m_iDurgaReceiptofMoney = -1;
			g_cEquipInventory->HT_vRupiahWin_Active();		// ���Ǿ� ����ŷ ������ �˾�
			break;
		case eNpcCEventReqYutWindowPopup :		
			g_cGamble->HT_vGamble_WindowPopup();			// ������ ��Ȳ�� �˾�
			break;
		case eNpcCEventReqEventCoupon : // �̺�Ʈ ���� ��� ��û
			//m_iResent = NPC_RESENT_EVENTCOUPON;
			//if( g_iInationalType == INATIONALTYPE_INDONESIA )
				//g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, "Welcome to Tantra World!!!.  Palease Input your coupon number", 5);
			//else
			g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, "źƮ�� ���忡 ���Ű��� ȯ���մϴ�. �����Ͻ� ������ ������ȣ�� �Է��� �ּ���.", 5);
			g_cUINPCWindow->m_MessageBoxNo = 2;
			g_cUIManager->HT_SetEditBoxControlLimitText(_DIALOG_NPCWINDOW+999, 1, 15);	// ����������� �Է¹���
			break;
		case eNpcCEventReqCheckWindowPopup : // �⼮üũ �̺�Ʈ ������ �˾� ��û (3033)
			g_pEventWindow->HT_vEventWindow_ReqAttendance();
			break;
		case eNpcCEventReqComeback : // �Ĺ�(����ȭ) �̺�Ʈ (3034)
			{
				int iSex, iSelectTribe;
				(g_oMainCharacterInfo.snTribe < 4) ? iSex = 0 : iSex = 1;	// 0 = ����, 1 = ����
				iSelectTribe = (g_cUINPCWindow->HT_vGetNPCWindow_ButtonNo()) + (iSex * 4);
				
				g_pEventWindow->HT_vEventWnd_ReqChangeTribe(iSelectTribe);
			}
			break;
		case eNpcCEventReqGetYutMoneyList : // ���ְ� ���� �� �ִ� �� ������ȸ(3035)
			{
				if (g_pSiege->HT_vSiege_GetOwerOfCastle() && g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_MAHARAJA )	// ���� �������� �ƴ��� ����
				{
					g_pSiege->m_iGetMoneyType = 1;	// ������
					g_pSiege->m_iGetMoneyAction = 1;	// ��ȸ
					g_pSiege->HT_vSiege_NetworkCSP_GetMoney();
				}
				else
				{	
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "���ָ��� ������ ������ ���� �� �ֽ��ϴ�.");
					//g_cNPCControl->HT_vNPCControl_GetNextStep(2);
					break;
				}
			}
			break;
		case eNpcCEventReqGetYutMoney : // ���ְ� ���� �� �ִ� �� ���ݿ�û (3036)
			{
				g_pSiege->m_iGetMoneyType = 1;		// ������
				g_pSiege->m_iGetMoneyAction = 2;	// �ޱ�
				g_pSiege->HT_vSiege_NetworkCSP_GetMoney();
			}
			break;
		case eNpcCEventReqQuestEvent1 : // �ϵ��޾��� �̺�Ʈ 
			{			// �ϵ��޾�� ������� �ϰ� ���â�� �ݴ´�.
			}
			break;
		case eNpcCEventReqQuestEvent2 : // �ϵ��޾��� �̺�Ʈ 
			{		// �ϵ��޾�� ������� �ϰ� ���â�� �ݴ´�.
			}
			break;
		case eNpcCEventReqGuildCargoOpenWindow : // ���â�� ����â
			{
				//	�ƽ����� ������ ��ŵ
				if( g_cGuildSystem->HT_iGuild_GetGuildID() == 0 )
					break;
				g_cGuildSystem->HT_vAshram_CSPAshramItem();
			}
			break;
		case eNpcCEventReqGuildCargoShowInfo : // ���â�� ���� ��û
			{
				//	�ƽ����� ������ ��ŵ
				if( g_cGuildSystem->HT_iGuild_GetGuildID() == 0 )
					break;
				//	���϶��ڰ� �ƴϸ� ��ŵ
				if( g_cGuildSystem->HT_byGuild_GetAuthority() != GUILD_AUTHORITY_MAHARAJA )
					break;
				g_cUIManager->HT_ShowWindow(_DIALOG_SANCTIONASHCAGO);
			}
			break;
		case eNpcCEventReqGuildCargoSetPMT : // ���â�� ���� ����
			{
				//	�ƽ����� ������ ��ŵ
				if( g_cGuildSystem->HT_iGuild_GetGuildID() == 0 )
					break;
				//	���϶��ڰ� �ƴϸ� ��ŵ
				if( g_cGuildSystem->HT_byGuild_GetAuthority() != GUILD_AUTHORITY_MAHARAJA )
					break;
				g_cUIManager->HT_ShowWindow(_DIALOG_SETLEVELASHCAGO);
			}
			break;
		// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �Ǹ���Ȳ ����) - 3042 - (�Ǹ� ����Ʈâ �˾�)
		case eNpcCEventReqRentalAdminSellInfo :	
			{
				g_cRentalStore->HT_EventReqRentalAdminSellInfo();
			}
			break;
		// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �����ޱ�) - 3043 - (�������� ������ ã���û ��Ŷ ȣ��)
		case eNpcCEventReqRentalAdminReciveItem	: 
			{
				g_cRentalStore->HT_EventReqRentalAdminReciveItem();
			}
			break;
		// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �������� ����Ʈ ����) - 3044 - (�������� ����Ʈâ �˾�)
		case eNpcCEventReqRentalAdminReciveList	:
			{
				g_cRentalStore->HT_EventReqRentalAdminReciveList();
			}
			break;
		// ����� ��Ź�Ǹ� �Ϲ��� (�Ǹ����� ������ ��Ϻ���) - 3045 (��Ź����â �˾�) - ���Ը��
		case eNpcCEventReqRentalBuyList	:
			{
				g_cRentalStore->HT_EventReqRentalBuyList();
			}
			break;
		// ����� ��Ź�Ǹ� �Ϲ��� (�ڽ��� ������ �Ǹ�) - 3046 (��Ź����â �˾�) - �ǸŸ��
		case eNpcCEventReqRentalSell :
			{
				g_cRentalStore->HT_EventReqRentalSell();
			}
			break;
		// ����� ��Ź�Ǹ� ������ (��Ź�Ǹ� �̿� ���� ����) - 3047 (��ũ��Ʈ�� ���)
		case eNpcCEventReqRentalUsingTex :
			{
				g_cRentalStore->HT_EventReqRentalUsingTex();
			}
			break;
		// ����� ��Ź�Ǹ� ������ (��Ź�Ǹ� ������ ���Ǿ� ����) - 3048 (��ũ��Ʈ�� ���)
		case eNpcCEventReqRentalItemRupia :
			{
				g_cRentalStore->HT_EventReqRentalItemRupia();
			}
			break;
		// ����� ��Ź�Ǹ� ������ (��Ź�Ǹ� �̿� ���� ����) - 3049 (��ũ��Ʈ�� ���)
		case eNpcCEventReqRentalSetTex :
			{
				g_cRentalStore->HT_EventReqRentalSetTex();
			}
			break;
		case eNpcCEventCallPaySystem : // �������� �ý��� ȣ�� 2004. 9. 14 ������
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
							//Ÿ�� ���� ������ �������� �ʽ��ϴ�. ��� �Ŀ� �ٽ� �õ��� �ֽñ� �ٶ��ϴ�.
							HT_vNPCControl_SetMessage( eMsgPremiumPaySystemErr );

							m_bMessage_Error = HT_TRUE;
							// �Ϸ�(����)â
							m_byMessageWin = NPC_MESSAGE_COMPLETE;
						}
						else if ( hResult == 1 )
						{
							// Ÿ�� ���� ���� ������ ���� ���α׷� �ʱ�ȭ�� �����߽��ϴ�.
							// FAILED( CoInitialize( HT_NULL ) )
							HT_vNPCControl_SetMessage( eMsgPremiumPaySystemErr2 );

							m_bMessage_Error = HT_TRUE;
							// �Ϸ�(����)â
							m_byMessageWin = NPC_MESSAGE_COMPLETE;
						}
						else if ( hResult == 2 )
						{
							// Ÿ�� ���� ���� ���� �ʱ�ȭ�� �����߽��ϴ�.
							// FAILED( CoCreateInstance( CLSID_InternetExplorer, HT_NULL, CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (LPVOID*)&m_pWebBrowser ) )
							HT_vNPCControl_SetMessage( eMsgPremiumPaySystemErr3 );

							m_bMessage_Error = HT_TRUE;
							// �Ϸ�(����)â
							m_byMessageWin = NPC_MESSAGE_COMPLETE;
						}
						else if ( hResult == 3 )
						{
							// Ÿ�� ���� ���� ������ ���� ���α׷� �˻��� �����߽��ϴ�.
							// ( m_hWndExplorer = FindWindow( "IEFrame", "Microsoft Internet Explorer" ) ) == NULL
							HT_vNPCControl_SetMessage( eMsgPremiumPaySystemErr4 );

							m_bMessage_Error = HT_TRUE;
							// �Ϸ�(����)â
							m_byMessageWin = NPC_MESSAGE_COMPLETE;
						}
						else
						{
							// Ÿ�� ���� ������ �� �� ���� ������ ��������ϴ�.
							HT_vNPCControl_SetMessage( eMsgPremiumPaySystemErr5 );

							m_bMessage_Error = HT_TRUE;
							// �Ϸ�(����)â
							m_byMessageWin = NPC_MESSAGE_COMPLETE;
						}
					}
				}
				//m_bNextStepByClientEvent = HT_TRUE;
				break;
			}

		case eNpcCEventTransformationShop:	// ���� �̿�� (�����̾�) /3023
			{
				if( g_cUIManager->HT_isShowWindow( _DIALOG_BEAUTYSALON2 ) )
				{
					g_cStatus->HT_vStatus_BeautyBack();	// �������·� ���� ����
					g_cUIManager->HT_HideWindow(_DIALOG_BEAUTYSALON2);
				}
				
				// ���չ̿�� ���̾˷α� ���
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

		case eNpcCEventMuUseInfo: // �� ��� ���� ���� 3026
			{
				// �� ��� ���� ���̾˷α� ���
				g_cUIManager->HT_ShowWindow( _DIALOG_MY_USEINFO_V3 );
				g_cIndividualStore->HT_vIndividualStore_ButtonCheckForUseListOutPut();
				break;
			}


		case eNpcCEventCreatePremiumGuildMark:  // �ƽ��� ��ũ ���� (�����̾�) /3024
			{
				// �ý��� â�� ǥ��
				if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )			g_cGuildSystem->m_iSelectWindow = 1;	// �Ϲ� �ƽ��� ����� â���� ����
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )		g_cGuildSystem->m_iSelectWindow = 2;	// �Ϲ� �ƽ��� ����� â���� ����
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )		g_cGuildSystem->m_iSelectWindow = 3;	// �Ϲ� �ƽ��� ����� â���� ����

				g_cGuildSystem->HT_vGuild_DialogBoxDrawTab(1);
				g_cGuildSystem->HT_bGuild_DialogBoxDrawEmblem(0);
				g_cUIManager->HT_ShowWindow(_DIALOG_AMBLEM);
				break;
			}

		case eNpcCEventJob2Select : // 2�� ���� ���� ���
			m_iResent = NPC_RESENT_JOB2_SELECT;
			break;

		case eNpcCEventCharacterInitialize : // ĳ���� ��ų/��ũ�� �ʱ�ȭ ���� ��û ��� 2004. 8. 27
			{
				if (m_nFirst == 1) // ó���ΰ� �ƴѰ��� ���� �б�
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

		case eNpcCEventInitialize : // ĳ���� ��ų/��ũ�� �ʱ�ȭ ��û ��� 2004. 8. 27
			{
				if (m_nNowRupia >= m_nNeedRupia) // ���ǾƸ� �����Ͽ� �׿� ���� �б��Ѵ�.(�ӽ�)
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
		case eNpcCEventInformationShow : // ���������� ���� �Խ��� ���� �˾�ó�� 2004. 11. 9
			{
				CHTString strString;
				if ( g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenWarning, &strString ) )
				{
					// �ش� ��αװ� ��ü ȭ������ Ȱ��ȭ �˴ϴ�. ����Ͻðڽ��ϱ�?
					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 1 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_PERSONALBOARD;
				}
			}
			break;

		//-------- �׽�ũ ����Ʈ ---------//
		case eNpcCEventTaskQuest : 
			// ���� �׽�ũ �޴��� ��ܰ� ����� ���� ��� �κ��� ���� ���� 
			// �κ��丮 â ���
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;
		case eNpcCEventTaskQuest1 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_1;
			// �κ��丮 â ���
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;

		case eNpcCEventTaskQuest2 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_8;
			// �κ��丮 â ���
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;

		case eNpcCEventTaskQuest3 :
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_15;
			// �κ��丮 â ���
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;
		case eNpcCEventTaskQuest4 : // ī�� �ռ�
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_20;
			// �κ��丮 â ���
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;
		case eNpcCEventTaskQuest5 : // �� �� ���� ����
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_27;
			// �κ��丮 â ���
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;
		case eNpcCEventTaskQuest6 : // ��� ���� ����
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_32;
			// �κ��丮 â ���
			HT_vNPCControl_PopUpInventory( _DIALOG_INVEN );
			break;
		// ���� ���������� 1�� ��� ����
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
		// �� �и��� ���� �κ�ǰ ����
		case eNpcCEventTaskQuest14 : // ����, Ų�����
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
		case eNpcCEventTaskQuest18 : // �Ƽ���, ������ ��
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
		case eNpcCEventTaskQuest22 : // ��ũ��, ���ٸ��� ��
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
		case eNpcCEventTaskQuest26 : // ����, ����� ��
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
		// �κ�ǰ �и��� ���� 1�� ��� ����
		case eNpcCEventTaskQuest30 : // ��Ʈ�ݱ�
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
		case eNpcCEventTaskQuest33 : // ���Ÿ��
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
		case eNpcCEventTaskQuest36 : // �ʹٳ���
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
		case eNpcCEventTaskQuest39 : // ��Ʈ��ī��
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
		// 1�� ���� ���� �� �κ�ǰ ����
		case eNpcCEventTaskQuest42 : // ��Ʈ�ݱ�
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
		case eNpcCEventTaskQuest45 : // ���Ÿ��
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
		case eNpcCEventTaskQuest48 : // �ʹٳ���
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
		case eNpcCEventTaskQuest51 : // ��Ʈ��ī��
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
		// �� ����
		case eNpcCEventTaskQuest54 : // ����, Ų���� ��
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
		case eNpcCEventTaskQuest57 : // �Ƽ���, ������ ��
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
		case eNpcCEventTaskQuest60 : // ��ũ��, ���ٸ��� ��
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
		case eNpcCEventTaskQuest63 : // ����, ����� ��
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
		case eNpcCEventTaskQuest66 :			// �������� ��(1134)�� �׽�ũ ����Ʈ �߰� 2004. 9. 1 ������
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_383;
			break;
		case eNpcCEventTaskQuest67 :			// �������� ��(1134)�� �׽�ũ ����Ʈ �߰� 2004. 9. 1 ������
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_389;
			break;
		case eNpcCEventTaskQuest68 :			// // 10388	���ٶ� �������� ����Ʈ	1120 
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_390;
			break;
		case eNpcCEventTaskQuest69 :			// // 10389	���߶� �������� ����Ʈ	1154
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_391;
			break;
		case eNpcCEventTaskQuest70 :			// // 10390	���� �������� ����Ʈ	1155
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_392;
			break;
		case eNpcCEventTaskQuest71 :			// // 10391	������ �������� ����Ʈ	1156
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_393;
			break;
		case eNpcCEventTaskQuest72 :			// // 10392	����帶 �������� ����Ʈ	1254 (��ũ��Ʈ������ ������ 1254�� �����Ƿ� ���⼭ �ٽ� ��й� ��)
		case eNpcCEventTaskQuest73 :			// // 10393	�񽴴� �������� ����Ʈ	1255
		case eNpcCEventTaskQuest74 :			// // 10394	�ù� �������� ����Ʈ	1256
			switch (m_iNPCIndex)
			{
			case 1254:	// ����帶
				m_iResent = NPC_RESENT_TASK_QUEST;
				m_iTaskQuestID = QUEST_TASK_394;
				break;
			case 1255: // �񽴴�
				m_iResent = NPC_RESENT_TASK_QUEST;
				m_iTaskQuestID = QUEST_TASK_395;
				break;
			case 1256:
				m_iResent = NPC_RESENT_TASK_QUEST;
				m_iTaskQuestID = QUEST_TASK_396;
				break; // �ù�
			}
			break;

		case eNpcCEventTaskQuest75 :			// ũ�������� ����Ʈ �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_397;
			break;

		case eNpcCEventTaskQuest76 :			// ��Ǫ ũ����Ż ���׷��̵� �׽�ũ ����Ʈ 1
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_398;
			break;

		case eNpcCEventTaskQuest77 :			// ��Ǫ ũ����Ż ���׷��̵� �׽�ũ ����Ʈ 2
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_399;
			break;

		case eNpcCEventTaskQuest78 :			// ���� ����ָӴ� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_400;
			break;

		case eNpcCEventTaskQuest79 :			// ������ ����Ʈ (����� �������� ��ǥ)
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_401;
			break;

		case eNpcCEventTaskQuest80 :			// ������ ����Ʈ (����� �������� ��ǥ)
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_402;
			break;

		case eNpcCEventTaskQuest81 :			// ����� ī�콺Ʈ�� ����
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_403;
			break;

		case eNpcCEventTaskQuest82 :			// ����� ī�콺Ʈ���� �̿��� ������ ��ȯ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_404;
			break;

		case eNpcCEventTaskQuest83 :			// ���� ����پ�
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_405;
			break;

		case eNpcCEventTaskQuest84 :			// �� ��Ƽ1
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_406;
			break;

		case eNpcCEventTaskQuest85 :			// �� ��Ƽ2
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_407;
			break;

		case eNpcCEventTaskQuest86 :			// �� ��Ƽ3
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_408;
			break;
		
		case eNpcCEventTaskQuest87 :			// �� ��Ƽ4
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_409;
			break;

		case eNpcCEventTaskQuest88 :			// ���� �Ӽ� ���� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_410;
			break;

		case eNpcCEventTaskQuest89 :			// �϶�Ƽ ���� ����
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_411;
			break;

		case eNpcCEventTaskQuest90 :			// ����� ������ ����
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_412;
			break;

		case eNpcCEventTaskQuest91 :			// ����
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_413;
			break;

		case eNpcCEventTaskQuest92 :			// ���� �������
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_414;
			break;

		case eNpcCEventTaskQuest93 :			// ���� �в���
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_415;
			break;

		case eNpcCEventTaskQuest94 :			// ũ����Ż 12�� ��1
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_416;
			break;

		case eNpcCEventTaskQuest95 :			// ũ����Ż 12�� ��2
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_417;
			break;

		case eNpcCEventTaskQuest96 :			// ũ����Ż 12�� ��3
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_418;
			break;

		case eNpcCEventTaskQuest97 :			// 12�� �÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_419;
			break;

		case eNpcCEventTaskQuest98 :			// ��� ���� �׽�ũ ����Ʈ // ���߶� ��ȣ��
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_420;
			break;

		case eNpcCEventTaskQuest99 :			// ��� ���� �׽�ũ ����Ʈ // �ƴ����� ��ܻ� ���
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_421;
			break;

		case eNpcCEventTaskQuest100 :			// ��� ���� �׽�ũ ����Ʈ // �������� �����·� �̶�����
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_422;
			break;

		case eNpcCEventTaskQuest101 :			// ��� ���� �׽�ũ ����Ʈ // �������� ��ȭ���� ��
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_423;
			break;

		case eNpcCEventTaskQuest102 :			// ��� ���� �׽�ũ ����Ʈ // ������ ����� ���
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_424;
			break;

		case eNpcCEventTaskQuest103 :			// ��� ���� �׽�ũ ����Ʈ // ������ â������ ������
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_425;
			break;

		case eNpcCEventTaskQuest104 :			// ���� �̺�Ʈ ���
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_426;
			break;

		case eNpcCEventTaskQuest105 :			// �÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_427;
			break;

		case eNpcCEventTaskQuest106 :			// �÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_428;
			break;

		case eNpcCEventTaskQuest107 :			// �÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_429;
			break;

		case eNpcCEventTaskQuest108 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = QUEST_TASK_430;
			break;
		case 4117 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ //fors_debug �����￪ʼ����������
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10553;
			break;
		case 4118 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10554;
			break;
		case 4119 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10555;
			break;
		case 4120 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10556;
			break;
		case 4121 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10557;
			break;
		case 4122 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10558;
			break;
		case 4123 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10559;
			break;
		case 4124 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10560;
			break;
		case 4125 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10561;
			break;
		case 4126 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10562;
			break;
		case 4127 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10563;
			break;
		case 4128 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10564;
			break;
		case 4129 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10565;
			break;
		case 4130 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10566;
			break;
		case 4131 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10567;
			break;
		case 4132 :			// 4���÷�Ƽ�� �ٷ��� �̺�Ʈ
			m_iResent = NPC_RESENT_TASK_QUEST;
			m_iTaskQuestID = 10568;
			break;
		//--------- ���� �˻� ---------//
		case eNpcCEventCheckTrimuritiPoint : // �ֽ�����Ʈ���ǰ˻�
		{
			m_iResent = NPC_RESENT_TRIMURITI_POINT;
			m_nSelectCount = 0;
			// ������ ���� ��� Ȯ�θ޼���â�� ó���ϰ� �����ܰ�� �Ѿ��.
			if( HT_bNPCControl_CheckConditionBrahmanPointRising() == HT_TRUE )
			{
				HT_vNPCControl_GetNextStep( m_nSelectCount );
				m_bNextStepByClientEvent = HT_TRUE;
			}
		}
			break;
		case eNpcCEventCheckChangeJob : // �����˻�
		{
			m_nSelectCount = 0;
			if( g_oMainCharacterInfo.byClass1 == CLASS_LEVEL2 )	// ������ ��� ����
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount );
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		case eNpcCEventCheckGuild : // �ƽ����˻�
		{
			m_nSelectCount = 0;
			// �ֽ��� ���õǾ��ִ� ���
			if( g_oMainCharacterInfo.byTrimuriti != 0 )
				HT_vNPCControl_GetNextStep( m_nSelectCount );
			// �ֽ��� �������� ���� ��� �ֽ� ���ø޴��� ��ȯ
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		case eNpcCEventCheckTrimuriti : // �ֽŰ˻�
		{
			m_nSelectCount = 0;
			m_bTrimutiri = 0;
			HT_vNetWork_CSP_Req_Select_Trimuriti(m_bTrimutiri);	// ��ȸ ��û

			// �ֽ��� �����ϱ� �������� �����ϱ� �������� �˻�
			if( g_oMainCharacterInfo.byTrimuriti == 0 )
				HT_vNPCControl_GetNextStep( m_nSelectCount );	// ����
			else
			{
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );	// ����
			}
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		case eNpcCEventCheckChakraInit : // ��ũ�� �ʱ�ȭ ���� �˻�
		{
			m_nSelectCount = 0;
			if( HT_bNPCControl_CheckConditionChakraInit() == HT_TRUE )
				HT_vNPCControl_GetNextStep( m_nSelectCount );
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		case eNpcCEventCheckSkillInit : // ��ų �ʱ�ȭ ���� �˻�
		{
			m_nSelectCount = 0;
			if( HT_bNPCControl_CheckConditionSkillInit() == HT_TRUE )
				HT_vNPCControl_GetNextStep( m_nSelectCount );
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		case eNpcCEventCheckSkillInit2 : // ��ų �ʱ�ȭ �̺�Ʈ
			{
				// �ʱ�ȭ ����
				//m_iNPCIndex = 1106;
				m_nType = 1;
				this->HT_vNetWork_CSP_Req_CharacterInitialize(2, 1);
			}
			break;
		case eNpcCEventCheckJob2ChangeItem : // 2�� ������ ������ �˻�
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
		case eNpcCEventCheckEvent : // �̺�Ʈ ��� ���� �˻�
		{
			m_nSelectCount = 0;
			if( HT_bNPCControl_CheckConditionCoupon() == HT_TRUE )
				HT_vNPCControl_GetNextStep( m_nSelectCount ); // ���� ��� ����
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
			m_bNextStepByClientEvent = HT_TRUE;
		}
			break;
		//--------- �̱��� ----------//
		case eNpcCEventSkillLearn : // ������
		{
			m_nSkillList_Count = 0;	// ���� ������ ��ų ��
			m_dwSkillRegistIndex = 0;
			m_dwSkillRegistType = 0;

			m_iResent = NPC_RESENT_SKILL;
		}
			break;
		case eNpcCEventSkillRemove : // ����������
		{
			m_iResent = NPC_RESENT_SKILL_REMOVE;
			HT_vNPCControl_GetSkillList();	// ���� ������ ��� ����Ʈ ����
		}
			break;
		default : break;
	}

	// ���� �ܰ谡 ����Ʈ �Ǵ� ���� �ܰ迴�� ��� â�� �ݾ��ش�
	if(m_iResent != NPC_RESENT_ITEM_LIST )
	{
		// ����Ʈ â �Ⱥ��̰�..
		HT_vNPCControl_ListAntiActive();
	}
	// ���� �ܰ谡 ��ôܰ迴�� ��� â�� �ݾ��ش�
	if( m_iResent != NPC_RESENT_REFINE && g_cUIManager->HT_isShowWindow( _DIALOG_REFINE ) == HT_TRUE )
	{
		HT_vNPCControl_ButtonCheck_Work_Delete();		
	}

	// ���� �ܰ谡 ��ǰ���� �ܰ迴�� ��� Inventory â�� �ݾ��ش�
	if( (m_iResent != NPC_RESENT_INVENTORY) )
	{
		// ������ ����ŷâ �ݱ�
		g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );
	}
	// ���� �ܰ谡 �������� �ܰ迴�� ��� â�� �ݾ��ش�
	if( (m_iResent != NPC_RESENT_PVP_RANK) )
	{
	}
}

HTvoid CHTNPCControl::HT_vNPCControl_Control()
{
	// NPC�� ��ȭ�� �̰ų� ������ �� ��
	if( m_bNPCActive == HT_TRUE || m_iResent == NPC_RESENT_REFINE )
	{
		// ĳ���� ��ġüũ_ĳ���� �����̸� �ٿ��Ų��
		HT_vNPCControl_CharPos_Check();
	}

	if( m_iResent == NPC_RESENT_REFINE_RATE_UP )
	{
		HTfloat fCurrentTime = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );
		if( fCurrentTime - m_fGaugeTimer >= HT_REQ_REFINESCALE_TIME )
			g_pNetWorkMgr->RequestRefineScale(); // ���� �峳 ������ ��û

		// ĳ���� ��ġüũ_ĳ���� �����̸� �ٿ��Ų��
		HT_vNPCControl_CharPos_Check();
	}
}

//----------ĳ���� ��ġüũ_ĳ���� �����̸� â�� �ٿ��Ų��----------//
HTvoid CHTNPCControl::HT_vNPCControl_CharPos_Check()
{
	HTPoint pCheckGet = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	if( m_pCharPos_Memory.x != pCheckGet.x || m_pCharPos_Memory.y != pCheckGet.y )
	{
		//	��ȭ���� �ݱ� - NPC�� ���õ� ��� â ����
		HT_vNPCControl_DialogWin_AntiActive();

		m_bNPCActive = HT_FALSE;
		m_byMessageWin = NPC_MESSAGE_NONE;

	}
}

//----- ��ȭ���� �ݱ� -----//
HTvoid CHTNPCControl::HT_vNPCControl_DialogWin_AntiActive()
{
	// �����̾� â�� ���� �ִ� ��쿡�� â �ݾ���.

	if( g_cUIManager->HT_isShowWindow( _DIALOG_MERCHANT_PREMIUM ))
	{
		g_cUIManager->HT_HideWindow(_DIALOG_MERCHANT_PREMIUM );
	}
	if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ))
	{
		g_cUIManager->HT_HideWindow(_DIALOG_NPCWINDOW );
	}
	//	����Ʈ �ݱ�
	if(g_cUIManager->HT_isShowWindow( _DIALOG_RENTALSTORE ) == HT_TRUE)	
	{
		g_cUIManager->HT_HideWindow(_DIALOG_RENTALSTORE );
	}
	//	����Ʈ �ݱ�
	if(g_cUIManager->HT_isShowWindow( _DIALOG_MERCHANT ) == HT_TRUE)	
	{
		HT_vNPCControl_ButtonCheck_List_Delete();
	}
	//	����â �ݱ�
	if(g_cUIManager->HT_isShowWindow( _DIALOG_REFINE ) == true)
	{
		// ����â���� �̵��ߴ� ������ �̹��� ��� ����
		g_cUIRefineWindow->HT_vRefineWindow_WindowHide();
		HT_vNPCControl_ButtonCheck_Work_Delete();		
	}
	// NPC�κ��丮 �ݱ�
	if(g_cUIManager->HT_isShowWindow( _DIALOG_GOODSKEEPWND ) == HT_TRUE )
	{
		// ������ ����ŷâ �ݱ�
		g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );
	}
	// ���� ��� ���� ���
	if( m_iResent == NPC_RESENT_REGIST_LOTTERY ) 
	{
		// ���� �Է� â �ݱ�
	}
	// �峳 ���� ���
	if( g_cUIManager->HT_isShowWindow(_DIALOG_CHARITYWND1) || g_cUIManager->HT_isShowWindow(_DIALOG_CHARITYWND2) )
	{
		// �峳â ���� �ִ� ������ �̹����� �����
		HT_vNPCControl_Offering_Cancel();
	}
	//	���ֶ� â�� ����
	if( g_cUIManager->HT_isShowWindow( _DIALOG_ASHRAMCAGO ) || g_cUIManager->HT_isShowWindow( _DIALOG_SANCTIONASHCAGO ) || g_cUIManager->HT_isShowWindow( _DIALOG_SETLEVELASHCAGO ) )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_ASHRAMCAGO );
		g_cUIManager->HT_HideWindow( _DIALOG_SANCTIONASHCAGO );
		g_cUIManager->HT_HideWindow( _DIALOG_SETLEVELASHCAGO );
	}

	m_bNPCActive = HT_FALSE;
	m_iNPCIndex = 0;

	m_iEconomy_Resent_Item = eEconomy_Item_None;	// ���� ���õ� ������ �з�
	m_iResent = NPC_RESENT_NONE;
	m_byMessageWin = NPC_MESSAGE_NONE;
	m_byResent_ServerMsg = SERVER_MSG_NONE;
	m_bNextStepByClientEvent = HT_FALSE;

	// �޼���â ���� �Է� �޾����� ���� Ȱ��ȭ�� NPC�� �˻��ϱ� ������...
	g_sNPCSystem->HT_vNPCSystem_AntiActiveNPC();
	g_pEngineHandler->HT_nSetActiveNPC(HT_NPC_TYPE_NONE);
}

//----- ����Ʈ���� �ݱ� -----//
HTvoid CHTNPCControl::HT_vNPCControl_ListAntiActive()
{
	// ������ ����â �ݱ�
	g_cUIManager->HT_HideWindow( _DIALOG_MERCHANT );
}

// �Ϸ�޼��� â
HTRESULT CHTNPCControl::HT_hrNPCControl_Complete_Message( HTint iProp, HTint iInductNo )
{
	if( m_byMessageWin == NPC_MESSAGE_NONE)
		return HT_FAIL;

	// ������Ƽ�� ����
//	switch(iProp)
//	{
//		case _PROP_PUSHBTN_IN_DLG:	// Ȯ��
//		{
			m_byMessageWin = NPC_MESSAGE_NONE;

			// ���۰����� ������ ����Ʈ �䱸 ����� ������ ���
			if(m_iResent == NPC_RESENT_DIALOG)
			{	
				// ��ȭ���� ��ȭ �ٲٱ�
				// ���ù��� ���������� ���ù��� �ƴ� �ٸ� �Է¿� ���� ���� �ܰ�� �Ѿ �� ����ϱ� ���� ���� �ִ�
				// 0~m_nSelectCount-1 : ���ù�, m_nSelectCount : Ȯ��, m_nSelectCount+1 : ���
				// ���콺 Ŭ���� ���� ���� �ܰ�� �Ѿ��.
				HT_vNPCControl_GetNextStep(m_nSelectCount+1);
			}
			// ������ ����
			else if( m_iResent == NPC_RESENT_ITEM_LIST )
			{
				// ������ ���� ���� ���� || �Ǹ� ��� ������ ��� ����Ʈ â �Ⱦ��ش�. 
				if( iInductNo != CONFIRM_NPCCONTROL_ITEM_COUNT && iInductNo != CONFIRM_NPCCONTROL_DISJOINT )
				{
					HT_vNPCControl_ListAntiActive();	// ����Ʈ â �Ⱥ��̰�..
				
					// ��ȭ���� ��ȭ �ٲٱ�
					// ���ù��� ���������� ���ù��� �ƴ� �ٸ� �Է¿� ���� ���� �ܰ�� �Ѿ �� ����ϱ� ���� ���� �ִ�
					// 0~m_nSelectCount-1 : ���ù�, m_nSelectCount : Ȯ��, m_nSelectCount+1 : ���
					// ���콺 Ŭ���� ���� ���� �ܰ�� �Ѿ��.
					HT_vNPCControl_GetNextStep(m_nSelectCount+1);
				}
				m_byResent_ServerMsg = SERVER_MSG_NONE;
			}
			// ������ ����
			else if(m_iResent == NPC_RESENT_REFINE)
			{
				if( m_bMessage_Error == HT_FALSE )	// ������ ���
				{
					//-----���� �̹����� ���ҽ� �����-----//
					HT_vNPCControl_ButtonCheck_Work_Delete();
					m_iResent = NPC_RESENT_NONE;
				}
				else
				{
					// ���ð�� ������ �����
					if( m_byResent_ServerMsg == SERVER_MSG_RESP_WORK_ITEM_REMOVE )
						g_cItemSystem->HT_vItemSystem_DeleteItem(m_dwWorkItem);
					// ���ð�� ��ȭ���� ���� �ʱ�ȭ
					else if( m_byResent_ServerMsg == SERVER_MSG_RESP_WORK_ITEM_MAIN_INIT )
						g_cItemSystem->HT_bItemSystem_SetMainRefineLevel( m_dwWorkItem, 0 );
					// �ּ� ���� �ʱ�ȭ
					else if( m_byResent_ServerMsg == SERVER_MSG_RESP_WORK_ITEM_SUB_INIT )
						g_cItemSystem->HT_bItemSystem_ClearSubRefineItem( m_dwWorkItem );

					// Ŭ���̾�Ʈ���� �˻��� ������ ��� ��� �̹����� �����, �׷��������� ������ �̹���/������ �����
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
			// ����/��ü
			else if( m_iResent == NPC_RESENT_FIX || m_iResent == NPC_RESENT_DISJOINT)
			{
				// ��ȭ���� ��ȭ �ٲٱ�
				// ���ù��� ���������� ���ù��� �ƴ� �ٸ� �Է¿� ���� ���� �ܰ�� �Ѿ �� ����ϱ� ���� ���� �ִ�
				// 0~m_nSelectCount-1 : ���ù�, m_nSelectCount : Ȯ��, m_nSelectCount+1 : ���
				// ���콺 Ŭ���� ���� ���� �ܰ�� �Ѿ��.
				HT_vNPCControl_GetNextStep(m_nSelectCount);
				
				// ���� ���� �� ���콺 ����� �ٲٱ� ���ؼ�
				m_iResent = NPC_RESENT_DIALOG;
			}
			else if( m_iResent == NPC_RESENT_TRIMURITI_CHANGE ) // �ֽ� ����-�����ִ� ���
				HT_vNPCControl_GetNextStep( m_nSelectCount );
			else if( m_iResent == NPC_RESENT_TRIMURITI_POINT )// �ֽ� ����Ʈ Ȯ��-�������� ���
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 
			else if( m_iResent == NPC_RESENT_REGIST_LOTTERY ) 
			{
				if( iInductNo == CONFIRM_NPCCONTROL_COUPON_ERR ) // ���� ��� ����
					HT_vNPCControl_GetNextStep( m_nSelectCount );
				else // ���� ��ȣ ����
				{
					m_szLottoryNum.HT_hrCleanUp(); // ���� �Է�â �ʱ�ȭ
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

// �׽�ũ ����Ʈ ���� ���� ��. 0 : ����, 1 : ����
HTint g_iTaskQuest_QuizResult[]
= { 0, 1, 0,	0, 1, 0,	0, 0, 1,	1, 0, 0,	0, 0, 1, // 1, 2, 3, 4, 5 
	1, 0, 0,	0, 1, 0,	0, 1, 0,	0, 0, 1,	0, 1, 0, // 6, 7, 8, 9, 10
	0, 1, 0,	0, 1, 0,	0, 1, 0,	0, 0, 1,	1, 0, 0, // 11, 12, 13, 14, 15
	0, 1, 0,	0, 0, 1,	0, 1, 0,	1, 0, 0,	1, 0, 0  // 16, 17, 18, 19, 20
};
//-----��ȭ���� üũ-----//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_Dialog(HTPoint pPt)
{
	// ������Ƽ�� ����
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
	// ����Ʈ �ܰ� ���� ó�� - ���� ��ȭ������ ã�� ���ǿ� ������ �ش�.
	//--------------------------------------------------------------------------------//
	if( byQuestLevel == QUEST_STATUS_START)
	{
		// Ʃ�丮�� ����Ʈ�� �ź����� ��� ��ȭ������ ������ ���ù��� "����Ʈ ����"���ù��� �ִ�
		// ���ٶ����� �·����� ���� Ʃ�丮�� ����Ʈ�� �����Ѵ�.
		if( byQuestIndex == 0 )	// Ʃ�丮�� �ź� ����
		{
			// ��ȭ�� ó�� �����Ҷ��� event�� "��ȭ���"�̰� �ٸ� ��쿣 "NULL"			
			if( event == eNpcCEventDialog && nSelectedRadioNo == (m_nSelectCount-1) )
			{
				g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(0x01, SELECT_QUEST_OK);	// �³�
				g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(1, QUEST_STATUS_NONE, QUEST_STATUS_0); // ����Ʈ ����
			}
		} 
		else if( event == eNpcCEventQuestAllow ) // ����Ʈ�³����
		{
			// �׻� 0�� ���ù��� �³�, 1�� ���ù��� �ź�
			if( byQuestIndex <= TUTORIAL_QUEST_END )	// Ʃ�丮���� ��� ������ ����Ʈ�� �ޱ� ������ ����Ʈ ������¸� "����"���� �ٲ۴�
				g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_PROGRESS );	
			else if( byQuestIndex <= SCENARIO_QUEST_6_END )
			{ 
				if( nSelectedRadioNo == SELECT_QUEST_OK )
				{
					if( byQuestIndex == QUEST_SHAMBALA_11 ) // 2�� ���� ���� ����
						g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG( byQuestIndex, m_bySelectPart);
					else
						g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG( byQuestIndex, SELECT_QUEST_OK);	// �³�
					// �� ���� ���� ����Ʈ�� ���
					if( byQuestIndex == QUEST_MANDARA_7 )	
					{
						// �ƹ�Ÿ���� ������ ���� NPC ����
						HTbool bRes = HT_FALSE;
						bRes = g_sNPCSystem->HT_bNPCSystem_DeleteNPC( m_iNPCIndex ); 
						if( bRes == HT_FALSE ) // 18 zone
							bRes = g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1215 ); 
						if( bRes == HT_FALSE ) // 19 zone
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1245 );
					}	
					//	��ȭ���� �ݱ� - NPC�� ���õ� ��� â ����
					HT_vNPCControl_DialogWin_AntiActive();
				}
				else
				{
					// �ó����� ����Ʈ �� ��� ������ �����Ѵ�. 
					// ���� : 2�� ���� ����Ʈ, ���� ����Ʈ ( ����(2004.03.17) ��ũ��/��ų �ʱ�ȭ ����Ʈ ) 
					if( byQuestIndex >= SCENARIO_QUEST_1_START 
						&& byQuestIndex <= SCENARIO_QUEST_6_END && byQuestIndex != QUEST_SHAMBALA_11 )
					{
						g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(byQuestIndex, SELECT_QUEST_CANCEL);		// ����
						g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_REJECTION); // ����Ʈ �ź�
					}
				}
			}
			// ���� ����Ʈ(����(2004.03.17 ��ũ��/��ų �ʱ�ȭ����Ʈ)�� ��� 
			else
			{
				if( nSelectedRadioNo == SELECT_QUEST_OK ) // �³��� ������ ��� ����Ʈ �������� ��ȯ. 
					g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus( byQuestIndex, QUEST_STATUS_NONE, QUEST_STATUS_0 ); // ����Ʈ ����
			}
		} // end of else if( event == eNpcCEventQuestAllow ) // ����Ʈ�³����
		// �ó����� ����Ʈ �³���尡 ������ ���� ����Ʈ ��ȭ�� �� ������ �ʾ��� ���(��ȭ��ħ�� ������ ���)
		else if( byQuestIndex >= SCENARIO_QUEST_1_START && byQuestIndex <= SCENARIO_QUEST_6_END 
					&& nSelectedRadioNo == (m_nSelectCount-1) && nSelectedRadioNo != 0 )
		{
			if( byQuestIndex == QUEST_MANDARA_4 )
			{	// 4��° �ó����� ����Ʈ�� ��쿣 ���� ���� ����Ʈ �³���尡 �ִ�.
				HTfloat fCurTime = HT_fNPCControl_GetCurTime();
				if(0.5 <= fCurTime && fCurTime <= 1)	// ��
				{
					g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(byQuestIndex, SELECT_QUEST_CANCEL);		// ����
					g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_REJECTION); // ����Ʈ �ź�
				}
			}
			else
			{
				if( byQuestIndex != QUEST_SHAMBALA_11 ) // ���� - 2�� ����
				{
					g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(byQuestIndex, SELECT_QUEST_CANCEL);		// ����
					g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_REJECTION); // ����Ʈ �ź�
				}
			}
		}
	} // end of if( byQuestLevel == QUEST_STATUS_START)
	// ����Ʈ�� �Ϸ�/���� ���� ��쿣 ����Ʈ ������¸� "����"���� �ٲ۴�
	else if( byQuestLevel == QUEST_STATUS_SUCCESS || byQuestLevel == QUEST_STATUS_FAIL )
	{
		// �ó����� ����Ʈ
		if( byQuestIndex >= SCENARIO_QUEST_1_START )
		{
			if( event == eNpcCEventQuestOK ) // �Ϸ��ȭ����
			{
				BYTE byQuestLevelTime = g_sNPCSystem->HT_byNPCSystem_GetLastQuestLevelTime();
				// 2�� ����-���� ����Ʈ�� ���� ����� ���
				if( byQuestIndex == QUEST_SHAMBALA_14 && byQuestLevelTime == QUEST_STATUS_1 
														&& m_bMessage_Error == HT_FALSE ) // ��� ����
					HT_vNPCControl_DialogWin_AntiActive();	 //	��ȭ���� �ݱ� - NPC�� ���õ� ��� â ����
				else
					g_sNPCSystem->HT_vNPCSystem_SetNextQuestStatus();
			}
		}
		// Ʃ�丮�� ����Ʈ - ���� : Tutorial 4(�ٳ�Ÿ���� �Ϸ��ȭ�� 2�ܰ�� �Ǿ��ִ� )
		else if( ( byQuestIndex <= TUTORIAL_QUEST_END && byQuestIndex != QUEST_TUTORIAL_4 ) 
						|| ( byQuestIndex == QUEST_TUTORIAL_4 && event == eNpcCEventQuestOK ) ) // �Ϸ��ȭ����
			g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus( byQuestIndex, QUEST_STATUS_NONE, QUEST_STATUS_0 ); // ����Ʈ ����

		// 2�� �Ϸ��� ���� ����Ʈ ������������ ��ȭ(QUEST_STATUS_3)�� �³����� �������
	}
	// �ó����� ����Ʈ�� �ź��ߴٰ� �ٽ� ����Ʈ�� �ް��� �� ��
	else if( byQuestLevel == QUEST_STATUS_REJECTION )
	{
		// ��ȭ������ ������ ���ù��� ����Ʈ�� �ٽ� ���� ���ִ� ���ù��� �ִ�
		if( event == eNpcCEventDialog && nSelectedRadioNo == (m_nSelectCount-1) )
			g_sNPCSystem->HT_vNPCSystem_SetNextQuestStatus();
	} 
	//--------------------------------------------------------------------------------//
	// ��ư ���ÿ� ���� ��ȭ ���� ó��
	//--------------------------------------------------------------------------------//
	// ��ų ���� �ܰ��� ��� ��ų ����Ʈ �������� ��ũ��Ʈ�� ���� ���ñ����� �ִ�.
	// ���ù��� ���������� ���ù��� �ƴ� �ٸ� �Է¿� ���� ���� �ܰ�� �Ѿ�� ����� ���� �ִ�.
	if( (m_iResent == NPC_RESENT_SKILL_LIST || m_iResent == NPC_RESENT_SKILL_REMOVE) 
							&& (m_nSkillList_Count > 0) && nSelectedRadioNo < m_nSkillList_Count)
	{ 
		// ������ ��ų ����
		// ��� ���ʿ��� ��� �̿��� ���ù��� �ִ�
		m_dwSkillRegistIndex = m_nSkillList_Index[nSelectedRadioNo];
		m_dwSkillRegistType = m_nSkillList_Type[nSelectedRadioNo];

		m_iResent = NPC_RESENT_SKILL_SELECT;

		// ���콺 Ŭ���� ���� ���� �ܰ�� �Ѿ��.
		HT_vNPCControl_GetNextStep(m_nSelectCount);
	}
	else if( m_iResent == NPC_RESENT_TRIMURITI )			// �ֽ� ����
	{
		m_bySelectPart = nSelectedRadioNo;
		//m_bTrimutiri = 1;
		//HT_vNetWork_CSP_Req_Select_Trimuriti(m_bTrimutiri);

		// ���콺 Ŭ���� ���� ���� �ܰ�� �Ѿ��.
		HT_vNPCControl_GetNextStep( nSelectedRadioNo );
		// �ֽż��ø�尡 ���������� �����ϱ� ����
		m_iResent = NPC_RESENT_TRIMURITI_SELECT;	
	}
	else if( m_iResent == NPC_RESENT_TRIMURITI_CHANGE )	// �ֽ� ����
	{
		HTbool res = HT_TRUE;

		if (m_bySelectPart == 0)
		{
		// �ֽ� ������ ���� ���� �˻�. ������ �׸�(m_nSelectCount-1) �� �ֽ� ������ �ƴϴ�.
		if( nSelectedRadioNo != m_nSelectCount-1 && g_cUINPCWindow->m_MessageBoxNo != 1)
		{

			// ���� �ֽ��� ������ ������ �ֽŸ� ���ù��� ������ ������
			// 0:����帶, 1:�񽴴�, 2:�ù� �� ��ȯ�Ѵ�.

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
		// ���콺 Ŭ���� ���� ���� �ܰ�� �Ѿ��.
		// ������ �־��� ��� Ȯ�� �޼���â�� ó���ϰ� �����ܰ�� �Ѿ��.
	

		if( res == HT_TRUE )
			HT_vNPCControl_GetNextStep( nSelectedRadioNo );
	}
	// 2�� ���� ���� ���
	else if( m_iResent == NPC_RESENT_JOB2_SELECT )
	{
		if( nSelectedRadioNo == SELECT_QUEST_OK )			// ��Ʈ��, ���Ÿ, ��ī����, �ƺ�ī��
			m_bySelectPart = 0;
		else if( nSelectedRadioNo == SELECT_QUEST_CANCEL )	// �ٳ���, ī����, ���̵��, �縶��Ʈ
			m_bySelectPart = 1;
		HT_vNPCControl_GetNextStep( nSelectedRadioNo );
	}
	// �׽�ũ ����Ʈ ���
	else if( m_iResent == NPC_RESENT_TASK_QUEST )
	{
		// m_iTaskQuestID �� ���� �׽�ũ �з��� ù��° ����Ʈ ���̵�� �����Ǿ��ִ�.
		m_iTaskQuestID += nSelectedRadioNo; // ����Ʈ ���̵� ����
		HT_vNPCControl_GetNextStep( nSelectedRadioNo );
	}
	// �׽�ũ ����Ʈ - ���� ���
	else if( m_iResent == NPC_RESENT_QUIZ )
	{
		// ���� ������ ���� �˾ƺ���. 0:����, 1:����
		if( g_iTaskQuest_QuizResult[ m_iQuestQuizCount*HT_QUIZ_SELECT_NUM + nSelectedRadioNo ] ) 
			m_bMessage_Error = HT_FALSE; // ���� ����
		else
			m_bMessage_Error = HT_TRUE;	// ���� ����
		++m_iQuestQuizCount; // ���� ��ȣ
		HT_vNPCControl_GetNextStep( nSelectedRadioNo );
	}
	else if (m_iResent == NPC_RESENT_FIX && m_bMessage_Error == HT_TRUE)
	{
		m_bMessage_Error = HT_FALSE;
	}
	else // �׿� - ��ų����Ʈ�� ���ù��� ���� �� �ֱ� ������
		HT_vNPCControl_GetNextStep(nSelectedRadioNo-m_nSkillList_Count);
	}
	break;

	if (nSelectedRadioNo == -1)	// ��� ��ư�̶��
	{	
			// �ó����� ����Ʈ �³���尡 ������ ���� ����Ʈ ��ȭ�� �� ������ �ʾ��� ���
			// �³��� ���� ���ù��� ���� ���(m_nSelectCount�� 1������ ��)�� ����
			if( byQuestIndex >= SCENARIO_QUEST_1_START && byQuestLevel == QUEST_STATUS_START && m_nSelectCount > 1 )
			{
				if( byQuestIndex == QUEST_MANDARA_4 )
				{	// 4��° �ó����� ����Ʈ�� ��쿣 ���� ���� ����Ʈ �³���尡 �ִ�.
					HTfloat fCurTime = HT_fNPCControl_GetCurTime();
					if(0.5 <= fCurTime && fCurTime <= 1)	// ��
					{
						g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(byQuestIndex, SELECT_QUEST_CANCEL);		// ����
						g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_REJECTION); // ����Ʈ �ź�
					}
				}
				else
				{
					if( byQuestIndex != QUEST_SHAMBALA_11 ) // ���� - 2�� ����
					{
						g_cQuest->HT_vNetWork_CSP_REQ_Quest_DIALOG(byQuestIndex, SELECT_QUEST_CANCEL);		// ����
						g_sNPCSystem->HT_vNPCSystem_SetLastQuestStatus(byQuestIndex, QUEST_STATUS_REJECTION); // ����Ʈ �ź�
					}
				}
			}
			// ��ȭ���� �ݱ� - NPC�� ���õ� ��� â �ݱ�
			//g_cNPCControl->m_bPrimium_Button = HT_FALSE;
			HT_vNPCControl_DialogWin_AntiActive();

		}
			break;
	}
}

// �ֽź��� ��� �˻� �Լ�
HTfloat CHTNPCControl::HT_bNPCControl_CheckTrimuritiChangeCost()
{
	m_nLevel = g_cStatus->HT_byGetLevel();		// ���� ���
/*
	BYTE					m_snBrahmaCount;	// ����帶 
	BYTE					m_snVishnuCount;	// �񽴴�
	BYTE					m_snSivaCount;		// �ù�
	HTbool					m_bTrimutiri;		// �ֽ� �������� ��ȸ���� ����
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


// �ֽ� ������ �������� ���� �˻�
HTbool CHTNPCControl::HT_bNPCControl_CheckConditionTrimuritiChange( )
{
	HTbyte byLevel = g_cStatus->HT_byGetLevel();
	HTint iPCMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
	// ��� �ּ����� �ִ��� �˻�
	HTint iItemCount = 0;
	if( byLevel >= HT_TRUMURITI_CHANGE_DIVISION_LEVEL )	// 30���� �̻��϶��� �ʿ���
		iItemCount = g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_TRIMURITI_CHANGE_ITEM );

	// ��� �˻�
	HTfloat fPrice = HT_bNPCControl_CheckTrimuritiChangeCost();
	
	// �峳 ��ᰡ ������ ���
	if( ( byLevel < HT_TRUMURITI_CHANGE_DIVISION_LEVEL && iPCMoney < (HTint) fPrice ) 
			|| ( byLevel >= HT_TRUMURITI_CHANGE_DIVISION_LEVEL 
					&& ( iPCMoney < (HTint) fPrice || iItemCount < HT_TRIMURITI_CHANGE_ITEMNUM ) ) )
	{
		if( byLevel < HT_TRUMURITI_CHANGE_DIVISION_LEVEL )
			HT_vNPCControl_SetMessage( eMsgTrimuritiChangeCondition1 );
			//m_szMessage.HT_szFormat("�ֽ��� �����ϱ� ���ؼ��� %d���Ǿư� �ʿ��մϴ�. �κ��丮���� ���ǾƸ� Ȯ���� ������.", 
			//						HT_TRIMURITI_CHANGE_MONEY1);
		else
			HT_vNPCControl_SetMessage( eMsgTrimuritiChangeCondition2 );
			//m_szMessage.HT_szFormat("�ֽ��� �����ϱ� ���ؼ��� %d���Ǿƿ� ��� �ּ����� �ʿ��մϴ�. �κ��丮�� Ȯ���� ������.", 
			//						HT_TRIMURITI_CHANGE_MONEY2);
		m_bMessage_Error = HT_TRUE;	// ���� ����

		// �Ϸ�â ���
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUINPCWindow->m_MessageBoxNo = -3;
		g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 0);
		HT_vNPCControl_GetNextStep(m_nSelectCount+1);
		return HT_FALSE;
	}
	// �ƽ����� ���ԵǾ� ���� ���
	if( g_cGuildSystem->HT_strGuild_GetGuildName().HT_nGetSize() > 0 )
	{
		//m_szMessage.HT_szFormat("�ƽ����� ���ԵǾ� �ִ� ���¿����� �ֽ��� ������ �� �����ϴ�." );
		HT_vNPCControl_SetMessage( eMsgTrimuritiChangeCondition3 );
		m_bMessage_Error = HT_TRUE;	// ���� ����

		// �Ϸ�â ���
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUINPCWindow->m_MessageBoxNo = -2;
		g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 0);
		return HT_FALSE;
	}
	return HT_TRUE;
}

// �ֽ� ����Ʈ Ȯ���� �������� ���� �˻�
HTbool CHTNPCControl::HT_bNPCControl_CheckConditionBrahmanPointRising()
{
	HTint iPCMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
	// ��� �ּ����� �ִ��� �˻�
	HTint iItemCount = g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_BRAHMANPOINT_RISING_ITEM );

	// ��ȥ�� ����(7116) 10���� 50,000���Ǿ� �ִ��� �˻�
	if( iItemCount < HT_BRAHMANPOINT_RISING_ITEMNUM || iPCMoney < HT_BRAHMANPOINT_RISING_MONEY )
	{
		//m_szMessage.HT_szFormat("�ֽ� ����Ʈ�� ��� ���ؼ��� ��ȥ�� ���� %d���� ���� ��� %d���Ǿư� �ʿ��մϴ�. �κ��丮�� Ȯ���� �ּ���."
		//							, HT_BRAHMANPOINT_RISING_ITEMNUM, HT_BRAHMANPOINT_RISING_MONEY );
		HT_vNPCControl_SetMessage( eMsgTrimuritiPointCondition1 );
		m_bMessage_Error = HT_TRUE;	// ���� ����

		// �Ϸ�â ���
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUINPCWindow->m_MessageBoxNo = -1;
		g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 0);
		return HT_FALSE;
	}
	// �ֽ�����Ʈ�� 100 �̸����� �˻�
	if( g_oMainCharacterInfo.nBrahmanPoint >= HT_BRAHMANPOINT_RISING_BRAHMAN )
	{
		//m_szMessage.HT_szFormat("�峳�� ���� �ֽ� ����Ʈ�� %d�̸��� ��쿡�� �����մϴ�.", HT_BRAHMANPOINT_RISING_BRAHMAN );
		HT_vNPCControl_SetMessage( eMsgTrimuritiPointCondition2 );
		m_bMessage_Error = HT_TRUE;	// ���� ����

		// �Ϸ�â ���
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUINPCWindow->m_MessageBoxNo = -1;
		g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 0);
		return HT_FALSE;
	}

	m_bMessage_Error = HT_FALSE;	// ���� ����
	return HT_TRUE;
}

#define HT_CHAKRA_INIT_CONDITION_BRAMANPOINT	500
#define HT_CHAKRA_INIT_CONDITION_MONEY			50000
// ��ũ�� �ʱ�ȭ ���� �˻�
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
// ��ų �ʱ�ȭ ���� �˻�
HTbool CHTNPCControl::HT_bNPCControl_CheckConditionSkillInit()
{
	if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < HT_SKILL_INIT_CONDITION_MONEY 
		|| g_oMainCharacterInfo.nBrahmanPoint < HT_SKILL_INIT_CONDITION_BRAMANPOINT )
		return HT_FALSE;
	else
		return HT_TRUE;
}

// ���� ��� ���� �˻�
HTbool CHTNPCControl::HT_bNPCControl_CheckConditionCoupon()
{
	// ���� 4��Ʈ�� 2��Ʈ��(10����/20����)�� ����, ���� 4��Ʈ�� 2��Ʈ(10����/20����)�� ���࿩��.
	HTbyte byFlag = g_oMainCharacterInfo.snDummy >> 4 ;
	HTbyte byUse = g_oMainCharacterInfo.snDummy & 0x0F;
	if( (byFlag & 0x02) && !(byUse & 0x02) ) // 10������ ������ ���������� 
		return HT_TRUE;
	else if( (byFlag & 0x01) && !(byUse & 0x01) ) // 20������ ������ ����������
		return HT_TRUE;
	else 
		return HT_FALSE;
}

char g_szEventMsg[6][500] = 
{ 
	"�ȳ��ϼ���. %s��.",
	"���ٶ� ������ ������ ������ ã�ư� ������. ���� �ҽ��� ��ٸ��� �ִ�ϴ�. ����������� �Դ��� ���ϴ� ��簡  �ִٰ� �ϴ±���.",
	"�������: �Կ� ������.",
	"���Ⱓ: 4�� 20�� ���� 5�� 4�� ����.",
	"���ѻ���: 1������ 10����,20���� 2ȸ ����.",
	"Ȩ������ ����: www.tantra-online.co.kr"
};

// ���� ��Ͽ� ���� �޼���â ����
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

	if( byFlag == 0 ) // ���� ���� �޼���â ����
	{
		//	����â ��
		CHTString szMsg;
		HTchar strText[1000];
		ZeroMemory( strText, sizeof(HTchar)*1000 );

		szMsg.HT_szFormat( g_szEventMsg[0], g_oMainCharacterInfo.szCharName );
		sprintf( strText, "%s>> %s>>��>>��%s>>��%s>>��%s>>��>>��%s",
			szMsg.HT_szGetString(), g_szEventMsg[1], g_szEventMsg[2], g_szEventMsg[3], g_szEventMsg[4], g_szEventMsg[5] );

		// ������ �������� ����
		// ���� 4��Ʈ�� 2��Ʈ��(10����/20����)�� ����, ���� 4��Ʈ�� 2��Ʈ(10����/20����)�� ���࿩��.
		byFlag = 0;
		if( byLevel == 20 )
			byFlag |= 0x01;

		else //if( byLevel == 10 )
			byFlag |= 0x02;
		g_oMainCharacterInfo.snDummy |= (byFlag << 4) ;
	}
}

// �׽�ũ 1
HTbool CHTNPCControl::HT_bNPCControl_CheckSourceForTaskQuest( HTint iTaskID )
{
	HTbyte	byteOut = 0;
	HTshort	sOut = 0, sOut1 = 0, sOut2 = 0, sOut3 = 0, sOut4 = 0;
	HTint	iOut;

	short int snNpcIndex = 0;
	// �ӽ� �ڵ� (���ٶ� 2,3 ������ ��ȭ�� �ɾ��� ��� ����Ʈ ������ ���� 1���� index�� ����)

	switch( m_iNPCIndex )
	{
		// ���� ����
	case 1101 :	// ���ٶ�
	case 1205 :	// 18�� ���ٶ�
	case 1235 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1101;
		}
		break;

		// �� ����
	case 1102 :	// ���ٶ�
	case 1206 :	// 18�� ���ٶ�
	case 1236 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1102;
		}
		break;

		// �׼����� ���� 
	case 1103 :	// ���ٶ�
	case 1207 :	// 18�� ���ٶ�
	case 1237 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1103;
		}
		break;

		// �·�
	case 1104 :	// ���ٶ�
	case 1208 :	// 18�� ���ٶ�
	case 1238 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1104;
		}
		break;

		//	��ǰ��������
	case 1105 :	// ���ٶ�
	case 1209 :	// 18�� ���ٶ�
	case 1239 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1105;
		}
		break;

		// �������
	case 1108 :	// ���ٶ� 
	case 1212 : // 18�� ���ٶ�
	case 1242 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1108;
		}
		break;

		// ������(����Ʈ)
	case 1106 :	// ���ٶ�
	case 1210 : // 18�� ���ٶ�
	case 1240 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1106;
		}
		break;
		// �ּ���(���������뿩)
	case 1107 :		// ���ٶ�
	case 1211 :		// 18�� ���ٶ�
	case 1241 :		// 19�� ���ٶ�
		{
			snNpcIndex = 1107;
		}
		break;
		// ����1
	case 1001 :	// ���ٶ�
	case 1201 :	// 18�� ���ٶ�
	case 1231 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1001;
		}
		break;
		// ����2
	case 1002 :	// ���ٶ�
	case 1202 :	// 18�� ���ٶ�
	case 1232 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1002;
		}
		break;
		//	���ھ���1
	case 1003 :	// ���ٶ�
	case 1203 : // 18�� ���ٶ�
	case 1233 : // 19�� ���ٶ�
		{
			snNpcIndex = 1003;
		}
		break;

		//	���ھ���1
	case 1005 :	// ���ٶ�
	case 1204 : // 18�� ���ٶ�
	case 1234 : // 19�� ���ٶ�
		{
			snNpcIndex = 1005;
		}
		break;

		// ����Ʈ�� ���� NPC
	case 1115 :	// ���� ����ü
	case 1213 :	// 18�� ���ٶ�
	case 1243 : // 19�� ���ٶ�
		{
			snNpcIndex = 1115;
		}
		break;

		// �������ٴ� ���� NPC
	case 1116 :
	case 1214 : // 18�� ���ٶ�
	case 1244 : // 19�� ���ٶ�
		{
			snNpcIndex = 1116;
		}
		break;

		// �ƹ�Ÿ���� ���� ����
	case 1117 :
	case 1215 : // 18�� ���ٶ�
	case 1245 : // 19�� ���ٶ�
		{
			snNpcIndex = 1117;
		}
		break;
	default:
		snNpcIndex = m_iNPCIndex;
		break;
	}


	HTbool bRes = HT_TRUE;

	// �� �̺�Ʈ ����Ʈ �׽�ũ�� ��쿡�� ������ �˻����� �ʴ´�.
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
		case eTaskQuestTypeItem : // ������
		{
			HTint iCount = g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( sItemID );
			if( iCount >= iSourceCount )
				bRes = HT_TRUE;
			else
				bRes = HT_FALSE;
		}
			break;
		case eTaskQuestTypeRupiah : // ���Ǿ�
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

// 2�� ������ ������ �˻�
#define HT_CHANGE_JOG2_ITEM_SATYA		8055 // ��Ʈ��
#define HT_CHANGE_JOG2_ITEM_VANARE		8056 // �ٳ���
#define HT_CHANGE_JOG2_ITEM_DRUTA		8057 // ���Ÿ
#define HT_CHANGE_JOG2_ITEM_KARYA		8058 // ī����
#define HT_CHANGE_JOG2_ITEM_NAKAYUDA	8059 // ��ī����
#define HT_CHANGE_JOG2_ITEM_VAIDYA		8060 // ���̵��
#define HT_CHANGE_JOG2_ITEM_ABICARA		8061 // �ƺ�ī��
#define HT_CHANGE_JOG2_ITEM_SAMAVAT		8062 // �縶��Ʈ
HTint CHTNPCControl::HT_iNPCControl_CheckItemForChangeJob2()
{
	HTint iSelNum = -1;
	switch( g_oMainCharacterInfo.snTribe )
	{
		case HT_ID_CHARACTER_NAGA		: // ����
		case HT_ID_CHARACTER_KIMNARA	: // Ų����
		{
			// ��Ʈ��
			if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_SATYA ) )
				iSelNum = 0;
			// �ٳ���
			else if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_VANARE ) )
				iSelNum = 1;
			else
				iSelNum = 8;
		}
			break;
		case HT_ID_CHARACTER_ASURA		: // �Ƽ���
		case HT_ID_CHARACTER_RAKSHASA	: // ��ũ����
		{
			// ���Ÿ
			if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_DRUTA ) )
				iSelNum = 2;
			// ī����
			else if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_KARYA ) )
				iSelNum = 3;
			else
				iSelNum = 8;
		}
			break;
		case HT_ID_CHARACTER_YAKSA		: // ��ũ��
		case HT_ID_CHARACTER_GANDHARVA	: // ���ٸ���
		{
			// ��ī����
			if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_NAKAYUDA ) )
				iSelNum = 4;
			// ���̵��
			else if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_VAIDYA ) )
				iSelNum = 5;
			else
				iSelNum = 8;
		}
			break;
		case HT_ID_CHARACTER_DEVA		: // ����
		case HT_ID_CHARACTER_GARUDA		: // �����
		{
			// �ƺ�ī��
			if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CHANGE_JOG2_ITEM_ABICARA ) )
				iSelNum = 6;
			// �縶��Ʈ
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

// �ƽ��� �������� �� 
HTvoid CHTNPCControl::HT_vNPCControl_Create_Guild( )
{
	if( m_iResent == NPC_RESENT_CREATE_GILD )
	{
		// ��ȭâ ���� �ٲٱ�
		HT_vNPCControl_GetNextStep( m_nSelectCount );
	}
}

// ��帶ũ �������� �� 
HTvoid CHTNPCControl::HT_vNPCControl_Create_GuildMark( )
{
	if( m_iResent == NPC_RESENT_CREATE_GILD_MARK )
	{
		// ��ȭâ ���� �ٲٱ�
		HT_vNPCControl_GetNextStep( m_nSelectCount );
	}
}

// �����̾� �������� �ش���ġ�� ���� ������ �ε��� ������
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

	if (iNo == -1 || m_byResent_ServerMsg != SERVER_MSG_NONE) return HT_FALSE;// Ŭ���� ���Լ���

	HTint iNum = nSelectedRadioNo;
	if (m_iMerchantNo == _DIALOG_PRIMIUM_BUY1) // _DIALOG_PRIMIUM_BUY2 �϶��� +1 ���ʿ�.
		nSelectedRadioNo = nSelectedRadioNo + 1;
	if (m_iMerchantNo == _DIALOG_PRIMIUM_BUY3) // _DIALOG_PRIMIUM_BUY2 �϶��� +1 ���ʿ�.
		nSelectedRadioNo = nSelectedRadioNo + 4;

	iSelectItemIndex = m_PrimiumItem[nSelectedRadioNo][iNo+m_iNowPage*10-10];
	
	if (m_PrimiumItem[nSelectedRadioNo][0] < iNo+m_iNowPage*10-10) return HT_FALSE;	// ��ϵ��� ���� ������ Ŭ���� ����

	return iSelectItemIndex;
}

//----������ ������ ���� ����-----//
HTvoid CHTNPCControl::HT_vNPCControl_ItemMakeCount_SetText()
{
	CHTString str;
	//str.HT_szFormat("%d", m_iWorkItemCount);��ǥ
	str = g_cUIManager->HT_strSetRestMark(m_iWorkItemCount);
}


//--------ESCŰ/X��ư�� �������� ����Ʈâ �ݱ�-----------//
HTvoid CHTNPCControl::HT_vNPCControl_ItemListClose()
{
	// ����Ʈ â �Ⱥ��̰�..
	HT_vNPCControl_ListAntiActive();
	m_dwBuyItem = 0;
	m_iWorkItemCount = 0;	// ������ ������ ���� �ʱ�ȭ
	
	// ��ȭ���� ��ȭ �ٲٱ�
	// ���ù��� ���������� ���ù��� �ƴ� �ٸ� �Է¿� ���� ���� �ܰ�� �Ѿ �� ����ϱ� ���� ���� �ִ�
	// 0~m_nSelectCount-1 : ���ù�, m_nSelectCount : Ȯ��, m_nSelectCount+1 : ���
	// ���콺 Ŭ���� ���� ���� �ܰ�� �Ѿ��.
	HT_vNPCControl_GetNextStep(m_nSelectCount+1);
}

//-----����Ʈ üũ_�׸� �����-----//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_List_Delete()
{
	HTint BnCount = 1;
	//if( m_iEconomy_NPC == eEconomy_Item_Sword)		// ����
	//{
	//	BnCount = g_ItemClass[0];	// ��ư ����
	//}
	//else if( m_iEconomy_NPC == eEconomy_Item_Armor)	// ��
	//{
	//	BnCount = g_ItemClass[1];
	//}
	//else if( m_iEconomy_NPC == eEconomy_Item_Bracelet )// �׼����� ����
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
				// ������ �ʴ� �������� ����
				m_Economy_List[index].pInfoHead = pTemp->pNext;
				delete pTemp;	// ������ ���� 
				
				pTemp = m_Economy_List[index].pInfoHead;	// ���� ������
			}
			m_Economy_List[index].pInfoTail = NULL;
			m_Economy_List[index].vWinCount.clear();
		}	
	} // end of for(int index = 0; index < BnCount ; ++index)

	// ����Ʈ â �Ⱥ��̰�..
	HT_vNPCControl_ListAntiActive();	
}

//--------- ���� ���õ� NPC�� ������ ����Ʈ ��Ȱ��ȭ -----------//
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

//---------������ ����Ʈ â�� ����----------//
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


//		HT_vNPCControl_PrimiumItemListWin_Active(0,0);	// �����̾� ������ ����
		
	}
	else
	{

		m_iResent = NPC_RESENT_ITEM_LIST;
		m_byEconomy_Resent_WinIndex = 0;

		if( m_iEconomy_NPC == eEconomy_Item_Sword)		// ����
		{
			//  ���� ��Ÿ�� ������ �з�
			m_iEconomy_Resent_Item = eEconomy_Item_Sword;
			m_iMerchantNo = _DIALOG_MERCHANT;
		}
		else if( m_iEconomy_NPC == eEconomy_Item_Armor)	// ��
		{
			//  ���� ��Ÿ�� ������ �з�
			m_iEconomy_Resent_Item = eEconomy_Item_Armor;
			m_iMerchantNo = _DIALOG_MERCHANT;
		}
		else											// �׼����� ����, �ּ��� ī��
		{
			//  ���� ��Ÿ�� ������ �з�
			m_iEconomy_Resent_Item = eEconomy_Item_Bracelet;
			m_iMerchantNo = _DIALOG_MERCHANT;
		}
	}

	HT_vNPCControl_PopUpInventory(_DIALOG_INVEN);	// PC �κ��丮 â ���
}

//---------������ �� �ִ� �����̾� ������ ����Ʈ ���ϱ�-------//
#define SEPT_KIND	4001
HTvoid CHTNPCControl::HT_vNPCControl_GetPrimiumItemList()
{
	// ���� �ܰ� ó��
	HT_vNPCControl_GetNextStep(m_nSelectCount);

	// �����̾� ����Ʈ ���� (����� ����)
	// shop list �����
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
					if ( idItem == SEPT_KIND ) // Ư�� ���������� ������ �����Ѵ�.
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
	// �����̾� ����Ʈ ����
	// shop list �����
	//
	if( g_pParamMgr->HT_bLockID( m_iNPCIndex ) == true )
	{
		int iCount = g_pParamMgr->HT_iGetNPCSellingItemCount( );
		HTint idItem = 0, num = 0;

		for ( int i = 0, j = 0; i < iCount; ++i )
			if ( g_pParamMgr->HT_bGetNPCSellingItem( i, &idItem ) )
			{	
				if ( idItem == SEPT_KIND ) // Ư�� ���������� ������ �����Ѵ�.
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
	// �����̾� â Ȱ��ȭ
	HT_vNPCControl_ItemListWin_Active();
}

// �����̾� �ش����� NPCID�� ���´�.
HTint CHTNPCControl::HT_iGetCashNPC(int TabID)
{
	int NPCID = 0;

	if ( g_wResentZoneServerID == 21 )	// ���� �߰���
	{
		NPCID = 1451 + TabID;

		return NPCID;
	}

	if ( g_wResentZoneServerID == 20 )	// ���� �߰���
	{
		NPCID = 1446 + TabID;

		return NPCID;
	}

	// ȣ�� NPC ID ����
	NPCID = 1342 + (g_wResentZoneServerID * 5) + TabID - 5;

	return NPCID;
}

// �����̾� ������ â ���� ���� ȯ�� ���� 
HTvoid CHTNPCControl::HT_vNPCControl_PrimiumItemListWin_Active(HTint iNum, HTint iPage)
{
	CHTString strTemp;

	// Compute Page
	//m_iMaxPage = int((m_PrimiumItem[iNum][0]-1) / maxnum)+1;
	//m_iNowPage = iPage;


	//HTint MaxPr, iPcode = 0;
	//(m_iNowPage == m_iMaxPage) ? MaxPr = ((m_PrimiumItem[iNum][0]-1) % maxnum) + 1 : MaxPr = maxnum;

	// ��� �����
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
		g_cUIMerchantWindow->m_ItemIndex[i] = pos;	// �����̾� �����۰� ȣȯ�� ���� ����
		if (pos <= 0)	
		{	// ���� �������� ����
			g_cUIManager->HT_SetSlotImage(_DIALOG_MERCHANT_PREMIUM, 200+i, 0);
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 200+i, "");
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 300+i, "");
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 400+i, "");
			continue;
		}

		// ����
		g_pParamMgr->HT_bGetItemName(pos, &str );
		g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 200+i, str);

		// ��Ʈ��
		DWORD nXMLID = g_pEngineHandler->HT_dwGetItemUIID(pos);
		g_cUIManager->HT_SetSlotImage(m_iMerchantNo, 200+i, nXMLID);

		// ����
		// 1. ������ ����
		g_pParamMgr->HT_bGetItemDescription(pos, &str );
		if( str == HT_INFO_ITEM_DESCRIPT_NULL )	str.HT_hrCleanUp();

		// 2. ���� ���
		HTint iCash = 0;
		g_pParamMgr->HT_bGetItemCash(pos, &iCash );

		// 3. �ּ� ���� ����
		HTint iMinCount = HT_iNPCControl_GetMinCountForChargeItem( pos );

		// 4. �������� ����
		HTint iDiscountNum = HT_iNPCControl_GetDiscountNumForChargeItem( pos );

		if( g_iInationalType == INATIONALTYPE_KOREA || g_iInationalType == INATIONALTYPE_JAPEN )
		{

			if (iCash < 2300)
			{
				HT_g_Script_SetMessage( eMsgExPlanPremiumItem09, &strTemp, _T("") );		//	"%s \n�ּ� %d�� ����(%d�� ���� �� 20������)"
				sprintf(strText, strTemp, str.HT_szGetString(), iMinCount, iDiscountNum);
			}
			else
			{
				sprintf(strText, "%s", str.HT_szGetString());
			}

		}
		else if( g_iInationalType == INATIONALTYPE_CHINA )
		{
			// �߱��� ��� ó��
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem09, &strTemp, _T("") );		//	"%s \n�ּ� %d�� ����(%d�� ���� �� 20������)"

			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( pos ) )
			{
				if (iCash < 30)
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem22, &strTemp, _T("") );		//	"%s \n�ּ� %d�� ����(%d�� ���� �� 10������)"
			}
			else
			{
				if (iMinCount == 20)
					HT_g_Script_SetMessage( eMsgExPlanPremiumItem22, &strTemp, _T("") );		//	"%s \n�ּ� %d�� ����(%d�� ���� �� 10������)"
			}

			sprintf(strText, strTemp, str.HT_szGetString(), iMinCount, iDiscountNum);
		}
		else
		{
			sprintf(strText, "%s", str.HT_szGetString());
		}

		g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 300+i, strText);
		
		CHTString szMoney = g_cUIManager->HT_strSetRestMark( iCash ); // ��ǥ ó��

		HT_g_Script_SetMessage( eMsgPriceToTaney, &strTemp, _T("") );		//	"����: %s Ÿ��"
		sprintf(strText, strTemp, szMoney.HT_szGetString());
		g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 400+i, strText);
	}

	// Page Output
	str.HT_szFormat("(Page %d/%d)",m_iNowPage, m_iMaxPage);
	//g_cUIManager->HT_SetTextLabelControl(_DIALOG_MERCHANT_PREMIUM, 2, str);
}


//---------������ �� �ִ� ������ ����Ʈ ���ϱ�-------//
HTvoid CHTNPCControl::HT_vNPCControl_GetItemList()
{
	// ������ ����Ʈ ����� ��ٸ��ٰ� �ٸ� �ܰ�� �ٲ��� ��� ����Ʈ�� ó������ �ʴ´�.
	//CHTString event = g_pEngineHandler->HT_szGetClientEvent();
	//if(event != "���Դ����")
	//	return;

	// ���� ������ �������� ������ ��� �ʱ�ȭ
	HT_vNPCControl_ButtonCheck_List_Delete();

	// ���� â ���� ��ȭ
	//-------- ��ȭ���� ��ȭ �ٲٱ� -----------//
	// ���ù��� ���������� ���ù��� �ƴ� �ٸ� �Է¿� ���� ���� �ܰ�� �Ѿ �� ����ϱ� ���� ���� �ִ�
	// 0~m_nSelectCount-1 : ���ù�, m_nSelectCount : Ȯ��, m_nSelectCount+1 : ���
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


// shop list�� ������ �ֱ�
HTvoid CHTNPCControl::HT_vNPCControl_InsertItemInShopList( HTint iIndex )
{
	// ������ ����Ʈ ����� ��ٸ��ٰ� �ٸ� �ܰ�� �ٲ��� ��� ����Ʈ�� ó������ �ʴ´�.
	//if(m_iResent != NPC_RESENT_ITEM_LIST && m_iResent != NPC_RESENT_REFINE)
	//	return;

	//-------------����Ʈ ��ġ ���ϱ�----------//
/*	HTint iBnCount;		// ������ �з� ����
	if( m_iEconomy_NPC == eEconomy_Item_Sword)		// ����
	{
		iBnCount = g_ItemClass[0];	
	}
	else if( m_iEconomy_NPC == eEconomy_Item_Armor)	// ��
	{
		iBnCount = g_ItemClass[1];
	}
	else											// �׼����� ����
	{
		iBnCount = g_ItemClass[2];
	}
*/
	// ���� �߰� �Ǵ� ������ ����
	ECONOMY_ITEM_INFO* pTemp = new ECONOMY_ITEM_INFO;
	pTemp->iIndex = iIndex;
	pTemp->iWidth = 1;
	pTemp->iLength = 1;
	pTemp->pNext = NULL; 

	// ���ο� �������� ����Ʈ�� ���
	HTint iItemClass = 0;
/*	HTbool	bItemClassCheck = HT_FALSE;	// ���ο� �������� ÷���� ������ �з� ã��
	for(iItemClass = 0; iItemClass < iBnCount ; ++iItemClass)
	{
		// �´� ������ �з��� �����ٸ� bItemClassCheck�� HT_FALSE�̴�
		if(m_iEconomy_NPC == eEconomy_Item_Sword)	// ���� ������ NPC�� ���� �����̸�
		{
			HTshort sType = 0;
			if( g_pParamMgr->HT_bGetItemType( pTemp->iIndex, &sType ) == false )
				return;

			// �˰� ������ �Ѽ�/����� �ֱ� ������ +2�� ����.
			if(g_ServerClass[m_iEconomy_NPC+iItemClass] == sType)
				bItemClassCheck = HT_TRUE;
			else
				bItemClassCheck = HT_FALSE;
		}
		else if( m_iEconomy_NPC == eEconomy_Item_Armor ) // �� ����
		{
			// ����
			if( CHTParamIDCheck::HT_bIsItemDefenceArmor(pTemp->iIndex) && iItemClass == _ITEMMAKE_DEFENCE_ARMOR )		
				bItemClassCheck = HT_TRUE;
			// ����
			else if( CHTParamIDCheck::HT_bIsItemDefenceHelmet(pTemp->iIndex) && iItemClass == _ITEMMAKE_DEFENCE_HELMET )
				bItemClassCheck = HT_TRUE;
			// �Ź�
			else if( CHTParamIDCheck::HT_bIsItemDefenceShoes(pTemp->iIndex) && iItemClass == _ITEMMAKE_DEFENCE_SHOES )	
				bItemClassCheck = HT_TRUE;
			// �㸮��
			else if( CHTParamIDCheck::HT_bIsItemDefenceBelt(pTemp->iIndex) && iItemClass == _ITEMMAKE_DEFENCE_BELT )	
				bItemClassCheck = HT_TRUE;
			// ����
			else if( CHTParamIDCheck::HT_bIsItemDefenceShield(pTemp->iIndex) && iItemClass == _ITEMMAKE_DEFENCE_SHIELD )
				bItemClassCheck = HT_TRUE;
			else
				bItemClassCheck = HT_FALSE;
		}
		else	// �׼����� ����
		{
			// �Ҹ𼺾����� - ����/ǥâ/ȭ��
			if( CHTParamIDCheck::HT_bIsItemUsable(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_USABLE )			
				bItemClassCheck = HT_TRUE;
			// ���þ�����
			else if( CHTParamIDCheck::HT_bIsItemRefine(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_REFINE )			
				bItemClassCheck = HT_TRUE;
			// ����
			else if( CHTParamIDCheck::HT_bIsItemAccessoryBracelet(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_BRACELET )	
				bItemClassCheck = HT_TRUE;
			// �����
			else if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_NECKLACE )
				bItemClassCheck = HT_TRUE;
			// �Ͱ���
			else if( CHTParamIDCheck::HT_bIsItemAccessoryEarring(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_EARRING )	
				bItemClassCheck = HT_TRUE;
			// ����
			else if( CHTParamIDCheck::HT_bIsItemAccessoryRing(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_RING )		
				bItemClassCheck = HT_TRUE;
			// �κ��丮Ȯ��
			else if( CHTParamIDCheck::HT_bIsItemAccessoryExpandInven(pTemp->iIndex) && iItemClass == _ITEMMAKE_ACCESSORY_EXPANDINVEN )	
				bItemClassCheck = HT_TRUE;
			else
				bItemClassCheck = HT_FALSE;
		}
 
		if(bItemClassCheck)
*/		{
			if(m_Economy_List[iItemClass].vWinCount.size() == 0)
			{
				m_Economy_List[iItemClass].vWinCount.push_back(1);	// ���� â�� ������ ����
				m_byEconomy_Resent_WinIndex = 0;					// ���� �����ִ� â�� index

				pTemp->byWinIndex = 0;
				pTemp->iXpos = 0;
				pTemp->iYpos = 0;
			}
			else
			{
				// ���� �з����� index�� ���� �������� �ִ��� �˻�
				HTbool res = HT_bNPCControl_CheckItemIndex(iItemClass, pTemp->iIndex);
				if(res == HT_TRUE)	// �̹� ���� �ε����� ������ ������ ������
				{
					HT_DELETE(pTemp);
					return;
				}

				// �������� ��ġ�� ��ǥ ã��
				res = HT_FALSE;
				BYTE byWinCount;
				HTint iXpos, iYpos;	// ����Ʈ ���� x, y��ǥ
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

				if(res == HT_TRUE)	// ���� â�� ���� ������ ������
				{
					++ m_Economy_List[iItemClass].vWinCount[byWinCount];	// ���� â�� ������ ���� ����
					pTemp->byWinIndex = byWinCount;
					pTemp->iXpos = iXpos;
					pTemp->iYpos = iYpos;
				}
				else	 
				{	
					m_Economy_List[iItemClass].vWinCount.push_back(1);	// ���ο� â �߰�
					pTemp->byWinIndex = m_Economy_List[iItemClass].vWinCount.size()-1;	// â index�� 0���� �����Ѵ�..
					pTemp->iXpos = 0;
					pTemp->iYpos = 0;

					// ���� �������� ������ �з��� ��� next ��ư ���̰�..
				}
			}
			
			// �� �������� �̹��� ����
			// ģ�е� ���ǿ� ���� ���� ����/�Ұ��� ����
			//if(pTemp->byFriendly == 0x00)	// ���� ģ�е�����
			//	pTemp->bWorkPossible = HT_TRUE;
			//else	// 0x01	���� ģ�е�����
			//	pTemp->bWorkPossible = HT_FALSE;

			if(m_Economy_List[iItemClass].pInfoHead == NULL)	// ����Ʈ�� �ϳ��� ������ ó���� �ִ´�.
				m_Economy_List[iItemClass].pInfoHead = pTemp;
			else
				m_Economy_List[iItemClass].pInfoTail->pNext = pTemp;	// ����Ʈ �������� ����
			
			m_Economy_List[iItemClass].pInfoTail = pTemp;		// ����Ʈ ������ ��ġ ����
//			break;
		}
//	}
	
	if( /*bItemClassCheck == HT_TRUE &&*/ pTemp->byWinIndex == m_byEconomy_Resent_WinIndex )
	{
		// �� �������� ��Ʈ�� ���
		int nXMLID = g_pEngineHandler->HT_dwGetItemUIID(pTemp->iIndex);
		HTint nToBitmapNo = pTemp->iYpos * LIST_WIDTH + pTemp->iXpos;	// ������ ����Ʈ â������ ĭ ��ȣ
		g_cUIManager->HT_SetSlotImage(_DIALOG_ACCESSORY_MERCHANT, nToBitmapNo, nXMLID);
		// �����Ұ����̸� ������ ���� ������ ǥ���Ѵ�.
	}
}

// ���� �з����� index�� ���� �������� �ִ��� �˻�
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

// iXpos, iYpos : �˻��� ��ġ
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

// ����â ������ ���� ������ ��� �����
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

//----------������ �����۰� ������Ḧ Ŭ������ ���---------//
HTRESULT CHTNPCControl::HT_hrNPCControl_ItemWork_LButtonClick( DWORD dwItemKeyID )
{
	// 1. ������ �������� ���� �÷����´�.
	// 2. ��ȭ���� �Ǵ� �ּ� ���� �������� �÷����´�.
	// 3. ��ȣõ��� ���� ���� �������� �÷����´�.
	// ������(grecia79@hanbitsoft.co.kr)

	// ===============================
	// Step 1. �ʱ�ȭ �� ���� ó��
	// ===============================

	// A. �̹� ������ �������̸� ��ȭ ����
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, "");
	if( dwItemKeyID == m_dwWorkItem )	return HT_FAIL;

	// A. ������ ������ ID ���
	DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(dwItemKeyID);	

	// B. �ش�������� Ŭ���̾�Ʈ�� ���ٸ� ���� ��ȯ
	if( dwIndex == 0 )	return HT_FAIL;

	// ===============================
	// Step 2. ������ ���п� ���� ó��
	// ===============================

	// (��ȭ���� 6501~6525 || �Ӽ����� 6601~6700 || �������� 6551~6600 || ÷���뿪2 6526~6550 || �ʱ�ȭ������ 6614)
	// 

	// A. ������� ������ ���ý� �̹��� �� ������ ���
	if( CHTParamIDCheck::HT_bIsItemRefine( dwIndex ) || dwIndex == HT_INDEX_INIT_SUB_REFINE )
	{
		if (dwItemKeyID == m_nEconomy_Work_SubItemKeyID[0] ) return HT_FAIL;
		if (m_nEconomy_Work_SubItemKeyID[0] != 0) 
		{
			// �ʿ��� ���Ǿ� ���
			CHTString str;
			str = g_cUIManager->HT_strSetRestMark(m_nEconomy_Work_LimitRupiah);	// ��ǥ
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, str);

			return HT_FAIL;
		}

		// ������ ����� �������� �ö���� �ʾҴٸ� ���� ����� �� �� �����Ƿ� ���� ����
		if (m_dwWorkItem == 0) return HT_FAIL;
		
		// ������ ���� �������� ��ǰ�� �Ӽ������� �Ǿ� �������� ��밡����
		HTbyte byLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( m_dwWorkItem );
		if (byLevel < 1)
		{
			switch (dwIndex)
			{
				case 6624:	//Ÿ�� �󰡸���
				case 6625:	//Ÿ�� �Ҷ󸶴�
				case 6626:	//Ÿ�� �����
				case 6627:	//Ÿ�� ���Ƽ
				case 6628:	//Ÿ�� �� ��Ʈ��
				case 6629:	//Ÿ�� ����Ǫ��
				case 6630:	//Ÿ�� �񽴴�
				case 6631:	//Ÿ�� �Ƴ���Ÿ
				case 6632:	//Ÿ�� ���
					{
						m_bMessage_Error = HT_TRUE;	// ���� ����
						g_cUIRefineWindow->m_nMessageBoxNo = 0;
						// ���� ���ǿ����� �������� ��Ḧ ����� �� �����ϴ�.
						HT_vNPCControl_SetMessage( eMsgItemRefineSubInitWarning2 );

						m_byResent_ServerMsg = SERVER_MSG_NONE;
						m_byMessageWin = NPC_MESSAGE_COMPLETE;
						g_cUIManager->HT_MessageBox(_DIALOG_REFINE, m_szMessage, 0);
					}
					return HT_FAIL;

				default:	// �׿��� �������� �ش���� ����
					break;
			}
		}

		// [���� ��� ÷����]��� �ι�° ������� ��ġ�� ���
		if (CHTParamIDCheck::HT_bIsItemRefineSub2( dwIndex )) //HT_MAIN_REFINE_ZARD_INDEX
		{
			// ���� ��Ʈ�� ����� ���ο� �������� ������ ����
			if (dwItemKeyID == m_nEconomy_Work_SubItemKeyID[1] ) return HT_FAIL;
			m_nEconomy_Work_SubItemKeyID[1] = dwItemKeyID;
			//g_cUIManager->HT_SetSlotImage( _DIALOG_REFINE, 3, 0);

			//HTPoint pSize = g_cItemSystem->HT_ptItemSystem_GetSize(dwItemKeyID); 
			g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, 3, g_pEngineHandler->HT_dwGetItemUIID( dwIndex ) );

			DWORD dwItemID = g_cItemSystem->HT_dwSystem_GetItemIndex(m_nEconomy_Work_SubItemKeyID[1]);
			DWORD dwItemID2 = g_cItemSystem->HT_dwSystem_GetItemIndex(m_nEconomy_Work_SubItemKeyID[0]);

			// [�Ӽ� ���� ������] �̶�� �Ӽ� ���� ������� ���
			if (CHTParamIDCheck::HT_bIsItemRefineSub( dwItemID2 )) 
			{
				m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( 0, m_nItemCost );
			}
			// [��ȭ ���� ������] �̶�� ��ȭ ���� ������� ���
			else 
			{
				HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel(m_dwWorkItem);	// �� �������� ��ȭ���� ���� ���
				//HTint iAttriRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( m_dwWorkItem );// �� �������� �ּ����� ���� ���
			
				m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( byLevel, m_nItemCost );
			}

			// [6552	����Ƽ	�������� ���� ����� �����մϴ�] ���� ��� ÷���� �����Ͽ� ��밨�� �������̸� ���ҽ�Ų��.
			if (dwItemID == 6552)
			{
				HTint iDiscount = 0;

				g_pParamMgr->HT_bGetItemEffect1Param1(dwItemID, &iDiscount);
				m_nEconomy_Work_LimitRupiah = (m_nEconomy_Work_LimitRupiah * (100 - iDiscount)) / 100;
			}

			// �ʿ��� ���Ǿ� ���
			CHTString str;
			str = g_cUIManager->HT_strSetRestMark(m_nEconomy_Work_LimitRupiah);	// ��ǥ
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, str);

			// �κ��丮�� ���Թڽ� �̵� ���� �Ұ��� ó��
			if (g_cUIRefineWindow->m_iWindowIndex[3])
				g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[3], g_cUIRefineWindow->m_iControlIndex[3], true);

			g_cUIRefineWindow->m_iWindowIndex[3] = g_cUIRefineWindow->m_iWindowIndex[0];
			g_cUIRefineWindow->m_iControlIndex[3] = g_cUIRefineWindow->m_iControlIndex[0];
			g_cUIManager->HT_RefuseSlotImageMoving();
			g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[3], g_cUIRefineWindow->m_iControlIndex[3], false);

			return HT_OK;
		}

		// [���� ��� ÷����2]��� ����° ������� ��ġ�� ���
		if (CHTParamIDCheck::HT_bIsItemRefineSub3( dwIndex )) //HT_MAIN_REFINE_ZARD_INDEX
		{
			// ���� ��Ʈ�� ����� ���ο� �������� ������ ����
			if (dwItemKeyID == m_nEconomy_Work_SubItemKeyID[2] ) return HT_FAIL;
			m_nEconomy_Work_SubItemKeyID[2] = dwItemKeyID;
			//g_cUIManager->HT_SetSlotImage( _DIALOG_REFINE, 3, 0);

			//HTPoint pSize = g_cItemSystem->HT_ptItemSystem_GetSize(dwItemKeyID); 
			g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, 4, g_pEngineHandler->HT_dwGetItemUIID( dwIndex ) );

			DWORD dwItemID = g_cItemSystem->HT_dwSystem_GetItemIndex(m_nEconomy_Work_SubItemKeyID[2]);
			DWORD dwItemID2 = g_cItemSystem->HT_dwSystem_GetItemIndex(m_nEconomy_Work_SubItemKeyID[0]);

			// [�Ӽ� ���� ������] �̶�� �Ӽ� ���� ������� ���
			if (CHTParamIDCheck::HT_bIsItemRefineSub( dwItemID2 )) 
			{
				m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( 0, m_nItemCost );
			}
			// [��ȭ ���� ������] �̶�� ��ȭ ���� ������� ���
			else 
			{
				HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel(m_dwWorkItem);	// �� �������� ��ȭ���� ���� ���
				//HTint iAttriRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( m_dwWorkItem );// �� �������� �ּ����� ���� ���
			
				m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( byLevel, m_nItemCost );
			}

			// [6552	����Ƽ	�������� ���� ����� �����մϴ�] ���� ��� ÷���� �����Ͽ� ��밨�� �������̸� ���ҽ�Ų��.
			if (dwItemID == 6526)
			{
				// �ι�°���� ����Ƽ�� ���� ��� ����� �� ����
				if (m_nEconomy_Work_SubItemKeyID[1] == 6552)
					return HT_FAIL;

				HTint iDiscount = 0;

				g_pParamMgr->HT_bGetItemEffect1Param1(dwItemID, &iDiscount);
				m_nEconomy_Work_LimitRupiah = (m_nEconomy_Work_LimitRupiah * (100 - iDiscount)) / 100;
			}

			// �ʿ��� ���Ǿ� ���
			CHTString str;
			str = g_cUIManager->HT_strSetRestMark(m_nEconomy_Work_LimitRupiah);	// ��ǥ
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, str);

			// �κ��丮�� ���Թڽ� �̵� ���� �Ұ��� ó��
			if (g_cUIRefineWindow->m_iWindowIndex[4])
				g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[4], g_cUIRefineWindow->m_iControlIndex[4], true);

			g_cUIRefineWindow->m_iWindowIndex[4] = g_cUIRefineWindow->m_iWindowIndex[0];
			g_cUIRefineWindow->m_iControlIndex[4] = g_cUIRefineWindow->m_iControlIndex[0];
			g_cUIManager->HT_RefuseSlotImageMoving();
			g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[4], g_cUIRefineWindow->m_iControlIndex[4], false);

			return HT_OK;
		}

		// ���� ��Ʈ�� ����� ���ο� �������� ������ ����
		m_nEconomy_Work_SubItemKeyID[0] = dwItemKeyID; // HT_bNPCControl_SetAidItemResource( dwItemKeyID );	
		m_nEconomy_Work_SubItemIndex = dwIndex;

		g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, 2, g_pEngineHandler->HT_dwGetItemUIID( dwIndex ) );

		// =========================================
		// Step 2-1. ������ ���ÿ� �ʿ��� ���� ���
		// =========================================

		// [�Ӽ� ���� ������] �̶�� �Ӽ� ���� ������� ���
		if (CHTParamIDCheck::HT_bIsItemRefineSub( dwIndex )) 
		{
			m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( 0, m_nItemCost );
		}
		// [��ȭ ���� ������] �̶�� ��ȭ ���� ������� ���
		else 
		{
			HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel(m_dwWorkItem);	// �� �������� ��ȭ���� ���� ���
			//HTint iAttriRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( m_dwWorkItem );// �� �������� �ּ����� ���� ���
		
			m_nEconomy_Work_LimitRupiah = g_cItemSystem->HT_iItemSystem_GetRupiahForItemWork( byLevel, m_nItemCost );
		}

		// [6552	����Ƽ	�������� ���� ����� �����մϴ�] ���� ��� ÷���� �����Ͽ� ��밨�� �������̸� ���ҽ�Ų��.
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

		// �ʿ��� ���Ǿ� ���
		CHTString str;
		str = g_cUIManager->HT_strSetRestMark(m_nEconomy_Work_LimitRupiah);	// ��ǥ
		g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, str);

		// �κ��丮�� ���Թڽ� �̵� ���� �Ұ��� ó��
		if (g_cUIRefineWindow->m_iWindowIndex[2])
			g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[2], g_cUIRefineWindow->m_iControlIndex[2], true);

		g_cUIRefineWindow->m_iWindowIndex[2] = g_cUIRefineWindow->m_iWindowIndex[0];
		g_cUIRefineWindow->m_iControlIndex[2] = g_cUIRefineWindow->m_iControlIndex[0];
		g_cUIManager->HT_RefuseSlotImageMoving();
		g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[2], g_cUIRefineWindow->m_iControlIndex[2], false);

		return HT_OK;
	}	
	// ������ �� �ִ� ������(����/��/�׼�����)�� ó��
	else if(( CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) || CHTParamIDCheck::HT_bIsItemDefence( dwIndex )	|| CHTParamIDCheck::HT_bIsItemAccessory( dwIndex ))	)
	{
		// �ʿ��� ���Ǿ� ���
		if (m_nEconomy_Work_SubItemKeyID[0] != 0 || m_nEconomy_Work_SubItemKeyID[1] != 0)
		{
			CHTString str;
			str = g_cUIManager->HT_strSetRestMark(m_nEconomy_Work_LimitRupiah);	// ��ǥ
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE , 1, str);
		}

		// A. ������ �÷����� �������� �־��ٸ� ������ �� ����. (m_dwWorkItem�� ����â �˾��ø��� 0���� �ʱ�ȭ �ʼ�)
		if (m_dwWorkItem != 0) return HT_FAIL;

		// B. �������� ������ ��� �� �� ���ٸ� ���úҰ� �ȳ�
		if( g_pParamMgr->HT_bGetItemRupiah( dwIndex, &m_nItemCost ) == false )
		{
			// ������ �� ���� �������Դϴ�
			HT_vNPCControl_SetMessage( eMsgItemRefineDoNot );

			m_byResent_ServerMsg = SERVER_MSG_NONE;
			m_bMessage_Error = HT_TRUE;	//��������

			m_byMessageWin = NPC_MESSAGE_COMPLETE;
			g_cUIManager->HT_MessageBox(_DIALOG_REFINE, m_szMessage, 0);
			return HT_FAIL;
		}

		m_dwWorkItem = dwItemKeyID;	// ������ �������� KeyID ���

		// ���� ������ ��Ʈ�� ����� ������ ������ �̹��� ����
		g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, 1, g_pEngineHandler->HT_dwGetItemUIID( dwIndex ) );

		g_cUIRefineWindow->m_iWindowIndex[1] = g_cUIRefineWindow->m_iWindowIndex[0];
		g_cUIRefineWindow->m_iControlIndex[1] = g_cUIRefineWindow->m_iControlIndex[0];
		g_cUIManager->HT_RefuseSlotImageMoving();
		g_cUIManager->HT_SetSlotBoxControlEnable(g_cUIRefineWindow->m_iWindowIndex[1], g_cUIRefineWindow->m_iControlIndex[1], false);

		return HT_OK;
	}
	// �׿��� �������� ������ �� �����Ƿ� ���� ��ȯ
	else 
	{
		return HT_FAIL;
	}
}

//----------- ������ ���� ������ Ŭ�� -----------//
HTRESULT CHTNPCControl::HT_hrNPCControl_ClickRefineObject( )
{
	m_iResent = NPC_RESENT_REFINE;
	m_byMessageWin = NPC_MESSAGE_NONE;	// �޼��� â �ȶ�����
	// ���� ĳ������ ��ġ ����
	m_pCharPos_Memory = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	
	// ������ ���� â ����
	HT_vNPCControl_ItemWorkWin_Active();

	return HT_OK;
}

//----------- ����â ���� ---------------//
HTvoid CHTNPCControl::HT_vNPCControl_ItemWorkWin_Active()
{
	// ���� ���� �����찡 �˾��Ǿ� �ִ� ���¶�� �κ��丮 UI �����ϰ� ����
	//if ( g_cUIManager->HT_isShowWindow( _DIALOG_REFINE ) == HT_TRUE )
	g_cNPCControl->HT_vNPCControl_ButtonCheck_Work_Delete();

	g_cUIManager->HT_ShowWindow( _DIALOG_REFINE );
	HT_vNPCControl_PopUpInventory( _DIALOG_EQUPINVENTORY );	// PC �κ��丮 â ���
	g_cUIRefineWindow->m_SetItemNumber = 0;


}

//--------ESCŰ/X��ư�� �������� ����â �ݱ�-----------//
HTvoid CHTNPCControl::HT_vNPCControl_ESC_ItemWorkClose()
{
	HT_vNPCControl_ButtonCheck_Work_Delete();
	m_iResent = NPC_RESENT_NONE;
}

//-----3-1.���� üũ_�̹��� �����-----//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_Work_Delete()
{
	// ������ �̹��� �����
	g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, 1, 0);
	g_cUIRefineWindow->HT_vRefineWindow_WindowHide();

	//----------���� ���� ����---------//
	// ����â ���� �ִ� ��� ������ �̹��� �����.
	HT_vNPCControl_ButtonCheck_Work_TotalCancel();
}

//-----3-3.���� üũ_��ü ĵ��-----//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_Work_TotalCancel()
{
	// ����â�� ������� �̹��� �����
	for (HTint i = 0; i<3; ++i)
		g_cUIManager->HT_SetSlotImage(_DIALOG_REFINE, i + 1, 0);	// UI �̹��� �ʱ�ȭ

	for (HTint j = 0; j<5; ++j)
	{
		m_nEconomy_Work_SubItemKeyID[j] = 0;
		g_cUIRefineWindow->m_iWindowIndex[j] = 0;
	}

	// ������ ���� �ʱ�ȭ
	m_dwWorkItem = 0;
	m_nEconomy_Work_ResRupiah = 0;
	m_nEconomy_Work_LimitRupiah = 0;

	g_cUIManager->HT_SetTextLabelControl(_DIALOG_REFINE, 1, "");
}

//-----3-4.���� üũ_���� Ȯ��-----//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_Work_Ok()
{
	CHTString strName;
	HTint nCheck = ECONOMY_ADDITEM_ERR_NONE;
  
	//-------------- ������ᰡ ÷�� ������ ������ �˻��Ѵ� ----------------//
	if( m_nEconomy_Work_SubItemKeyID[0] == 0 )
	{
		m_bMessage_Error = HT_TRUE;	// ���� ����
		// ���� ��Ḧ �־��ֽʽÿ�
		HT_vNPCControl_SetMessage( eMsgItemRefineSelectMeterial );
	}
	else if( m_dwWorkItem == 0 )
	{
		m_bMessage_Error = HT_TRUE;	// ���� ����
		// ������ �������� �����Ͽ� �ֽʽÿ�.
		HT_vNPCControl_SetMessage( eMsgItemRefineSelectItem );
	}
	else 
	{
		nCheck = HT_nNPCControl_CheckAidItemCondition(strName);	

		if(nCheck == ECONOMY_ADDITEM_ERR_ITEMINDEX)
		{
			m_bMessage_Error = HT_TRUE;	// ���� ����
			// ������ ������ ã�� ���߽��ϴ�.
			HT_vNPCControl_SetMessage( eMsgItemCommonCannotFindInfo );
		}
		else	// ������ ������ ã�Ƽ� �˻��� ���
		{/*
			// ���� �Ӽ����� �������� ��ī���� �ִٸ� ���Ѿ��� ��� ���������� ���� ����
			DWORD dwRefineIndex2 = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[1] );
			if (dwRefineIndex2 == 6555)
			{
				// ���� ������ �˻��Ͽ� OKay ���¶�� ��ī���� ����� �ʿ䰡 ���ٴ� �޽��� ���
				if (nCheck == ECONOMY_ADDITEM_ERR_NONE)
				{
					nCheck = ECONOMY_ADDITEM_ERR_NEEDNOT;
					m_bMessage_Error = HT_TRUE;	// ���� ����
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
					m_bMessage_Error = HT_FALSE;	// ���� ����
				}
			}
*/
			if(nCheck == ECONOMY_ADDITEM_ERR_NEEDNOT)
			{
				m_bMessage_Error = HT_TRUE;	// ���� ����
				HT_vNPCControl_SetMessage( eMsgRefineErr2 );
			}
			else if(nCheck == ECONOMY_ADDITEM_ERR_MAIN_OVER)	// ��ȭ ���� �� Ƚ�� ����
			{
				m_bMessage_Error = HT_TRUE;	// ���� ����
				// ��ȭ ������ �� �� ���� �������Դϴ�.
				HT_vNPCControl_SetMessage( eMsgItemRefineMainCannot );
			}
			else if(nCheck == ECONOMY_ADDITEM_ERR_SUB_OVER) // �ּ� ���� �� Ƚ�� ����
			{
				m_bMessage_Error = HT_TRUE;	// ���� ����
				// �ּ� ������ �� �� ���� �������Դϴ�.
				HT_vNPCControl_SetMessage( eMsgItemRefineSubCannot );
			}
			else if(nCheck == ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM)	// ÷�� �Ұ����� �������
			{
				m_bMessage_Error = HT_TRUE;	// ���� ����
				// %s�� ÷���� �� ���� ��������Դϴ�.
				HT_vNPCControl_SetMessage( eMsgItemRefineMeterialErr );
			}
			else if( nCheck == ECONOMY_ADDITEM_ERR_CANNOT ) // ���� Ȯ�� 0. ������ �� ����
			{
				m_bMessage_Error = HT_TRUE;	// ���� ����
				// �� ���� ���δ� �� �̻� ������ �� �� �����ϴ�. ���� ����� ���� ��Ḧ ����� �ֽñ� �ٶ��ϴ�.							
				HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel1 );
			}
			else //if( nCheck == ECONOMY_ADDITEM_ERR_NONE )	// ÷����� ���� ������ ���� ���
			{
				// �κ��丮 �ȿ� �ִ� ���Ǿ� �˻�
				m_nEconomy_Work_ResRupiah = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();

				if(m_nEconomy_Work_ResRupiah >= m_nEconomy_Work_LimitRupiah )
				{
					// ÷���� �������� �ε���
					HTdword dwRefineIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[0] );
					if( CHTParamIDCheck::HT_bIsItemRefineMain( dwRefineIndex ) ) // ��ȭ���� ���
					{
						HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( m_dwWorkItem );

						HTint iWarning;

						// ����÷���� ���Կ��ο� ���� �޽��� ���漳��
						HTdword dwRefineIndex2 = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[1] );
						if( CHTParamIDCheck::HT_bIsItemRefineSub2( dwRefineIndex2 ) )
						{
							if (byLevel < 5 && dwRefineIndex2 == 6551)	// �ڵ��� ���
							{
								m_bMessage_Error = HT_TRUE;	// ���� ����
								// ���� ���ǿ����� �������� ��Ḧ ����� �� �����ϴ�.
								HT_vNPCControl_SetMessage( eMsgItemRefineSubInitWarning2 );
								
								g_cUIRefineWindow->m_nMessageBoxNo = 0;
								m_byResent_ServerMsg = SERVER_MSG_NONE;
								m_byMessageWin = NPC_MESSAGE_COMPLETE;
								g_cUIManager->HT_MessageBox( _DIALOG_REFINE, m_szMessage, 0);
								return;
							}

							if (byLevel < 4 && dwRefineIndex2 == 6556)	// ����� ���
							{
								m_bMessage_Error = HT_TRUE;	// ���� ����
								// ���� ���ǿ����� �������� ��Ḧ ����� �� �����ϴ�.
								HT_vNPCControl_SetMessage( eMsgItemRefineSubInitWarning2 );
								
								g_cUIRefineWindow->m_nMessageBoxNo = 0;
								m_byResent_ServerMsg = SERVER_MSG_NONE;
								m_byMessageWin = NPC_MESSAGE_COMPLETE;
								g_cUIManager->HT_MessageBox( _DIALOG_REFINE, m_szMessage, 0);
								return;
							}
	
							iWarning = HT_iNPCControl_GetMainRefineWarning( byLevel+1, dwRefineIndex2 );
							
							// ����, �׿��� ����������� �ϰ�쿡�� ��ȭ��������� �޽����� ��� (2006. 3. 30)
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
					else if( dwRefineIndex == HT_INDEX_INIT_SUB_REFINE ) // �ּ����� �ʱ�ȭ ������
					{
						// �ּ� ������ �ʱ�ȭ�Ͻðڽ��ϱ�?
						HT_vNPCControl_SetMessage( eMsgItemRefineSubInitWarning );
					}
					else // �ּ� ���� ���
					{
						DWORD dwRefineIndex2 = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[1] );
						if (dwRefineIndex2 == 6555)
						{
							//���ý� ������ ���õǾ��ִ� �Ӽ��� �������ϴ�. �����Ͻðڽ��ϱ�?"
							HT_vNPCControl_SetMessage( eMsgRefineErr1 );
						}
						else
						{
							// ���� ������ ���� �������� ����� ������ �����Ƿ� �����Ѵ�.
							switch (dwRefineIndex)
							{
								case 6624:	//Ÿ�� �󰡸���
								case 6625:	//Ÿ�� �Ҷ󸶴�
								case 6626:	//Ÿ�� �����
								case 6627:	//Ÿ�� ���Ƽ
								case 6628:	//Ÿ�� �� ��Ʈ��
								case 6629:	//Ÿ�� ����Ǫ��
								case 6630:	//Ÿ�� �񽴴�
								case 6631:	//Ÿ�� �Ƴ���Ÿ
								case 6632:	//Ÿ�� ���
								case 6620:
								case 6621:
								case 6622:
								case 6623:
								case 6633:
								case 6634:
								case 6635:
								case 6636:
									//100%�� �������� ������ �����մϴ�. �Ƚ��ϰ� �����Ͻʽÿ�.
									HT_vNPCControl_SetMessage( eMsgItemRefineWarningLevel8 );
									break;

								default:
									// �������� �����ϴ� �������� ������ �� �ֽ��ϴ�. ������ ���� ���� �� ���� ���� ��ᰡ ������ϴ�.
									HT_vNPCControl_SetMessage( eMsgItemRefineSubWarning );
									break;
							}
						}
					}
					m_bMessage_Error = HT_FALSE; // ���� ����
				}
				else
				{
					// ������ ���ÿ� �ʿ��� ���Ǿư� �����մϴ�.
					HT_vNPCControl_SetMessage( eMsgItemCommonMoneyErr );
					m_bMessage_Error = HT_TRUE;	// ���� ����
				}
			}
		}	// end of else of if(nCheck == -1)
	}

	// ���� ��Ȯ��â
	if(m_bMessage_Error == HT_FALSE)	// ���� ����
	{
		g_cUIRefineWindow->m_nMessageBoxNo = 1;
		m_byMessageWin = NPC_MESSAGE_CONFIRM;
		g_cUIManager->HT_MessageBox( _DIALOG_REFINE, m_szMessage, 1);
	}
	else	// �Ϸ�(����)â 
	{
		g_cUIRefineWindow->m_nMessageBoxNo = 0;
		m_byResent_ServerMsg = SERVER_MSG_NONE;
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUIManager->HT_MessageBox( _DIALOG_REFINE, m_szMessage, 0);
	}
}

//----------- �峳�� ���� ������Ʈ Ŭ�� -----------//
HTRESULT CHTNPCControl::HT_hrNPCControl_ClickOfferingObject(HTint iNum)
{
	m_nOfferingObjectNumber = iNum;

	switch(m_nOfferingObjectNumber)
	{
	case 0:	// ���ٶ��� �Ŵ� 
		m_nOfferingDialogNumber = _DIALOG_CHARITYWND1;
			break;
	case 1: // �ֽ��� �ù�
	case 2: // �ֽ��� �񽴴�
	case 3: // �ֽ��� ����帶
		m_nOfferingDialogNumber = _DIALOG_CHARITYWND2;
			break;
	default:
		m_nOfferingDialogNumber = _DIALOG_CHARITYWND1;
	}

	m_byMessageWin = NPC_MESSAGE_NONE;	// �޼��� â �ȶ�����
	m_pCharPos_Memory = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	
	g_pNetWorkMgr->RequestRefineScale(); // ���� �峳 ������ ��û

	return HT_OK;
}

#define HT_REFINE_RATE_GAUGE_MAX	10000
//----------- �峳â ���� ---------------//
HTvoid CHTNPCControl::HT_vNPCControl_OfferingWin_Active( HTshort sGauge )
{
	if( g_cUIManager->HT_isShowWindow( m_nOfferingDialogNumber ) == HT_FALSE )
	{
		m_iResent = NPC_RESENT_REFINE_RATE_UP;
		m_bPress_OK_Button = HT_FALSE;
		m_byOfferingItemNum = 0;
		m_fGaugeTimer = 0.0f;

		// ������ ����
		HT_vNPCControl_Offering_SetGauge( sGauge );
		// ���Ǿ� ����
		HT_vNPCControl_Offering_SetRupiah( 0 );

		g_cUIManager->HT_ShowWindow( m_nOfferingDialogNumber );

		// PC �κ��丮 â ���
		HT_vNPCControl_PopUpInventory( _DIALOG_EQUPINVENTORY );

		// ���� ĳ������ ��ġ ����
		m_pCharPos_Memory = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	}
}

// �峳�� ����
HTvoid CHTNPCControl::HT_vNPCControl_Offering_SetRupiah( HTdword dwRupiah )
{
	m_dwOfferingRupiah = dwRupiah;

	CHTString str;
	str.HT_szFormat( "%d", dwRupiah );
	g_cUIManager->HT_SetTextLabelControl( m_nOfferingDialogNumber, 1, str.HT_szGetString() );
}

// �峳 ������ ����
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

	// ���ٶ��� �Ŵܿ����� ���� ó��
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

// �峳â �ູ ��ġ ���
HTint CHTNPCControl::HT_iNPCControl_CalRefineRateUpConst( )
{
	if( m_byOfferingItemNum <= 0 )
		return 0;

	HTint iConst = 0; // ������ ����
	HTint iItemIndex = 0, iRupiah = 0; // ������ �ε���, ����
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

//--------- �峳â ��ư üũ -----------//
HTvoid CHTNPCControl::HT_vNPCControl_ButtonCheck_OfferingWin( int iAction, int iTarget, int iTargetID )
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	Cancel
		if( iTargetID == 3 || iTargetID == -1 )
		{
			// �峳â ���� �ִ� ������ �̹����� �����
			HT_vNPCControl_Offering_Cancel();
			m_iResent = NPC_RESENT_NONE;
		}
		//	OK
		else if( iTargetID == 2 )
		{
			if( m_bPress_OK_Button == HT_FALSE && (m_byOfferingItemNum > 0 || m_dwOfferingRupiah > 0) )
			{
				// Ȯ�ι�ư�� �����ִ� ����
				m_bPress_OK_Button = HT_TRUE;
				this->HT_vNetWork_CSP_Req_ItemOffering();
			}
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		//	�ٸ� �����쿡�� ������ ������ ��ŵ
		unsigned int iWIndex, iCIndex;
		int iTextureId;
		g_cUIManager->HT_GetSlotBoxControlSourInfo( iWIndex, iCIndex, iTextureId );
		if( _DIALOG_CHARITYWND1 == iWIndex || _DIALOG_CHARITYWND2 == iWIndex )
		{
			if( _OFFERING_BEGIN <= iTargetID && iTargetID <= _OFFERING_END )
			{
				HTint iPos = iTargetID - _OFFERING_BEGIN ;
				HT_vNPCControl_OfferingItemDelete( iPos ); // ������ �����
			}
		}
		else
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
		}
	}
}

//-------- ESCŰ/X��ư�� �������� �峳â �ݱ�-----------//
HTvoid CHTNPCControl::HT_vNPCControl_ESC_OfferingwinClose()
{
	HT_vNPCControl_Offering_Cancel();
	m_iResent = NPC_RESENT_NONE;
}

//----- �峳 ���-----//
HTvoid CHTNPCControl::HT_vNPCControl_Offering_Cancel()
{
	// �峳â �����
	g_cUIManager->HT_HideWindow( m_nOfferingDialogNumber );

	m_dwOfferingRupiah = 0;
	// ������ �̹��� �����
	HT_vNPCControl_OfferingItemDeleteAll( );
	m_fGaugeTimer = 0.0f;
}

// �峳 ������ �����
HTvoid CHTNPCControl::HT_vNPCControl_OfferingItemDeleteAll( )
{
	for( HTint i = 0 ; i < MAX_ITEM_CONTRIBUTION ; ++i )
	{
		if( m_iOfferingItemKeyID[i] > 0 )
			g_cUIManager->HT_SetSlotImage( m_nOfferingDialogNumber, _OFFERING_BEGIN+i, 0 );
		m_iOfferingItemKeyID[i] = 0;
	}
	m_byOfferingItemNum = 0;

	// Ȯ�ι�ư�� �ȴ����ִ� ����
	m_bPress_OK_Button = HT_FALSE;
}

HTvoid CHTNPCControl::HT_vNPCControl_OfferingItemDelete( HTint iPos )
{
	if( m_iResent != NPC_RESENT_REFINE_RATE_UP || iPos < 0 || iPos >= m_byOfferingItemNum )
		return;

	if( m_iOfferingItemKeyID[iPos] > 0 )
	{
		// �ڿ� �ִ� ������ ��� ������ ����
		HTdword dwItemIndex = 0;
		HTint nXMLID = 0;
		for( HTint i = iPos ; i < (m_byOfferingItemNum-1) ; ++i )
		{
			m_iOfferingItemKeyID[i] = m_iOfferingItemKeyID[i+1];
			m_iOfferingItemPlace[i] = m_iOfferingItemPlace[i+1];
			
			// �̹��� �׸���
			dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_iOfferingItemKeyID[i] );
			nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
			g_cUIManager->HT_SetSlotImage( m_nOfferingDialogNumber, _OFFERING_BEGIN+i, nXMLID );
		}
		m_iOfferingItemKeyID[i] = 0;
		m_iOfferingItemPlace[i] = -1;

		// �̹��� �����
		g_cUIManager->HT_SetSlotImage( m_nOfferingDialogNumber, _OFFERING_BEGIN+i, 0 );
		--m_byOfferingItemNum;
	}
}

// �峳 ������ �߰�
HTvoid CHTNPCControl::HT_vNPCControl_OfferingItemAdd( DWORD dwItemKeyID )
{
	if( m_iResent != NPC_RESENT_REFINE_RATE_UP || 
		dwItemKeyID <= 0 || 
		m_byOfferingItemNum >= MAX_ITEM_CONTRIBUTION )
		return;

	HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwItemIndex <= 0 )
		return;

	// �峳 ������ ���������� �˻� - ����Ʈ ���� ������, ����������, ��ø������ �Ұ�
	HTbyte byMaxCount = 0;
	if( CHTParamIDCheck::HT_bIsItemQuestOnly( dwItemIndex ) 
			|| CHTParamIDCheck::HT_bIsItemCollect( dwItemIndex ) 
			|| (g_pParamMgr->HT_bGetItemMaxCount( dwItemIndex, &byMaxCount ) == true && byMaxCount > 2) )
		return;

	if( m_byOfferingItemNum > 0 )	// ���� �������� �ִ��� �˻�
	{
		for(HTint i = 0 ; i < m_byOfferingItemNum ; ++i )
		{
			if( m_iOfferingItemKeyID[i] == dwItemKeyID )
				return;
		}
	}

	// ������ ��ġ
	HT_ITEMSETTING_FLAG sLocRoom;
	if( g_cItemSystem->HT_bItemSystem_GetItemPos( dwItemKeyID, sLocRoom ) == HT_FALSE )
		return;

	m_iOfferingItemKeyID[m_byOfferingItemNum] = dwItemKeyID;
	m_iOfferingItemPlace[m_byOfferingItemNum] = (sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y)
										+ (sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);

	// �̹��� �׸���
	HTint nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
	g_cUIManager->HT_SetSlotImage( m_nOfferingDialogNumber, _OFFERING_BEGIN+m_byOfferingItemNum, nXMLID );

	++m_byOfferingItemNum;
}

// �峳â�� �ִ� ������ KeyID ���ϱ�
HTint CHTNPCControl::HT_iNPCControl_GetKeyIDInOfferingWin( HTint iPos )
{
	if( iPos < 0 || iPos >= m_byOfferingItemNum )
		return 0;

	return m_iOfferingItemKeyID[ iPos ] ;
}


//----------��ȭ���� �ܰ� �� ���� �������� ���� ���� Ȯ�� ���ϱ�-------------//
int HT_REFINE_MAIN_WARNING[7][MAX_REFINE_MAIN_LEVEL]
= { //1		2		3		4		5		6		7		8		9		10		11		12
	{7,		7,		7,		7,		4,		1,		1,		1,		1,		1,		1,		1}, // �϶�
	{8,		8,		5,		5,		6,		6,		6,		2,		1,		1,		1,		1}, // ������
	{8,		8,		8,		8,		6,		6,		6,		2,		2,		2,		1,		1}, // ������
	{3,		3,		3,		1,		1,		1,		1,		1,		1,		1,		1,		1}, // �����϶�
	{8,		8,		8,		8,		8,		8,		8,		9,		9,		2,		2,		2},// ������Ƽ
	{8,		8,		8,		8,		8,		8,		8,		8,		8,		1,		1,		1}, // ���ĵ�
	{10,	10,		10,		10,		10,		10,		10,		11,		11,		11,		11,		11}, // �ڵ�
};
HTint CHTNPCControl::HT_iNPCControl_GetMainRefineWarning( HTint iRefineLevel, HTdword dwMainRefineIndex )
{
	if( iRefineLevel <= 0 || iRefineLevel > MAX_REFINE_MAIN_LEVEL )
		return -1;

	switch( dwMainRefineIndex )
	{
		// �϶�
		case HT_MAIN_REFINE_ILLA_INDEX : return HT_REFINE_MAIN_WARNING[0][iRefineLevel-1];
		// ������
		case HT_MAIN_REFINE_AZISE_INDEX : return HT_REFINE_MAIN_WARNING[1][iRefineLevel-1];
		// ������
		case HT_MAIN_REFINE_SURAPA_INDEX : return HT_REFINE_MAIN_WARNING[2][iRefineLevel-1];
		// ���� �϶�
		case HT_MAIN_REFINE_DIPAILLA_INDEX : return HT_REFINE_MAIN_WARNING[3][iRefineLevel-1];
		// ������Ƽ		
		case HT_MAIN_REFINE_PRAJATI_INDEX : return HT_REFINE_MAIN_WARNING[4][iRefineLevel-1];
		// ���ĵ�
		case HT_MAIN_REFINE_SAMPAD_INDEX : return HT_REFINE_MAIN_WARNING[5][iRefineLevel-1];
		// �ڵ�
		case HT_MAIN_REFINE_ZARD_INDEX : return HT_REFINE_MAIN_WARNING[6][iRefineLevel-1];
		case 6507: return 11;
		case 6556: return 6;
		default : break;
	}

	return -1;
}

//-------------- ������ᰡ ÷�� ������ ������ �˻��Ѵ� ----------------//
// ÷�� �Ұ����� ��ᰡ ���� ��� �� ����� �̸��� strName�� ��ȯ�Ѵ�.
HTint CHTNPCControl::HT_nNPCControl_CheckAidItemCondition(CHTString& strName)
{
	// �������� ������ �ε��� ��� 
	DWORD dwRefineIndex2 = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[1] );

	// ������ ������ �ε���
	DWORD dwWorkIndex = g_cItemSystem->HT_dwSystem_GetItemIndex(m_dwWorkItem);
	if( dwWorkIndex == 0 )
		return ECONOMY_ADDITEM_ERR_ITEMINDEX;

	// ÷���� �������� �ε���
	DWORD dwRefineIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_nEconomy_Work_SubItemKeyID[0] );
	if( dwRefineIndex == 0 )
		return ECONOMY_ADDITEM_ERR_ITEMINDEX;

	// ������ ���� ����
	if( CHTParamIDCheck::HT_bIsItemRefineMain( dwRefineIndex ) ) // ��ȭ����
	{
		HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel(m_dwWorkItem);

		if( byLevel >= MAX_REFINE_MAIN_LEVEL )
			return ECONOMY_ADDITEM_ERR_MAIN_OVER;	// error

		// ��ȭ ���� �ܰ迡 ���� ����Ȯ�� �˻�
		HTint iWarning = HT_iNPCControl_GetMainRefineWarning( byLevel+1, dwRefineIndex );
		if( iWarning == -1 || iWarning == HT_REFINE_WARNING1 )
			return ECONOMY_ADDITEM_ERR_CANNOT;	// error
	}
	else if( CHTParamIDCheck::HT_bIsItemRefineSub( dwRefineIndex )) // �ּ�����
	{
		HTint iAttriRefineLevel = g_cItemSystem->HT_iItemSystem_GetSubRefineLevel( m_dwWorkItem );

		if( dwRefineIndex2 == 6551 || dwRefineIndex2 == 6556 )	// �ڵ带 �ּ� ���ÿ� ����ߴٸ� �����޽��� ����Ͽ� ������� ���ϰ� �Ѵ�.
		{
			return ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM;	// error
		}

		// �ּ����� �ʱ�ȭ ������
		if( dwRefineIndex == HT_INDEX_INIT_SUB_REFINE )
		{
			if( iAttriRefineLevel <= 0 ) 
				return ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM; // error : ÷�� �Ұ���
			else
				return ECONOMY_ADDITEM_ERR_NONE;	// ���� ����
		}
		else if( iAttriRefineLevel >= MAX_REFINE_SUB_LEVEL )
		{

			if (dwRefineIndex2 != 6555) 
			{
				// ���� ������ ���� �������� ����� 10������ �Ѵ��� �����Ѵ�.
				switch (dwRefineIndex)
				{
					case 6624:	//Ÿ�� �󰡸���
					case 6625:	//Ÿ�� �Ҷ󸶴�
					case 6626:	//Ÿ�� �����
					case 6627:	//Ÿ�� ���Ƽ
					case 6628:	//Ÿ�� �� ��Ʈ��
					case 6629:	//Ÿ�� ����Ǫ��
					case 6630:	//Ÿ�� �񽴴�
					case 6631:	//Ÿ�� �Ƴ���Ÿ
					case 6632:	//Ÿ�� ���
						//return ECONOMY_ADDITEM_ERR_NONE;	// ���� ����
						break;

					default:
						return ECONOMY_ADDITEM_ERR_SUB_OVER;	// error
						break;
				}
			}
		}
	}

	HTbool bCheck = HT_TRUE;

	// ÷���� �������� ÷�� ���� ������ ����
	HTint iRefinableType = 0;
	if( g_pParamMgr->HT_bGetItemRefinableItemType( dwRefineIndex, &iRefinableType ) == false || iRefinableType <= 0 )
		return ECONOMY_ADDITEM_ERR_ITEMINDEX;
	
	// ����
	if( CHTParamIDCheck::HT_bIsItemWeapon( dwWorkIndex ) )
	{
		// �� �� ����
		if( CHTParamIDCheck::HT_bIsItemWeaponOneHand( dwWorkIndex )
								&& !BIT_AND( _REFINE_WEPON_ONEHAND, iRefinableType )  )
			bCheck = HT_FALSE;	// ÷�� �Ұ���
		// �� �� ����
		if( ( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( dwWorkIndex ) 
												|| CHTParamIDCheck::HT_bIsItemWeaponThrow( dwWorkIndex ) )
								&& !BIT_AND( _REFINE_WEPON_TWOHAND, iRefinableType )  )
			bCheck = HT_FALSE;	// ÷�� �Ұ���
	}
	// ��
	else if( CHTParamIDCheck::HT_bIsItemDefence( dwWorkIndex ) )
	{
		// �Ǻ�	
		if( CHTParamIDCheck::HT_bIsItemDefenceArmor( dwWorkIndex ) 
								&& !BIT_AND( _REFINE_DEFENCE_ARMOR, iRefinableType ) )					
			bCheck = HT_FALSE;	// ÷�� �Ұ���
		// ����
		if( CHTParamIDCheck::HT_bIsItemDefenceShield( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_SHIELD, iRefinableType ) )	
			bCheck = HT_FALSE;	// ÷�� �Ұ���
		// �㸮��
		if( CHTParamIDCheck::HT_bIsItemDefenceBelt( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_BELT, iRefinableType ) )		
			bCheck = HT_FALSE;	// ÷�� �Ұ���
		// �Ź�
		if( CHTParamIDCheck::HT_bIsItemDefenceShoes( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_SHOES, iRefinableType ) )	
			bCheck = HT_FALSE;	// ÷�� �Ұ���
		// ����
		if( CHTParamIDCheck::HT_bIsItemDefenceHelmet( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_HELMET, iRefinableType ) )	
			bCheck = HT_FALSE;	// ÷�� �Ұ���
		// ����
		if( CHTParamIDCheck::HT_bIsItemDefencePants( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_PANTS, iRefinableType ) )	
			bCheck = HT_FALSE;	// ÷�� �Ұ���
		// �尩
		if( CHTParamIDCheck::HT_bIsItemDefenceGloves( dwWorkIndex )
								&& !BIT_AND( _REFINE_DEFENCE_GLOVES, iRefinableType ) )	
			bCheck = HT_FALSE;	// ÷�� �Ұ���
		// ���� �������� ��� ���� ���� �������� ����� �� ������ ������ ���� ����� ���� �������� ��� �Ұ�
		if( CHTParamIDCheck::HT_bIsItemCharm( dwWorkIndex ))
		{
			switch (dwRefineIndex)
			{
				case 6620:	// ����� ���� ������
				case 6621:	
				case 6622:	
				case 6623:	
				case 6633:
				case 6634:
				case 6635:
				case 6636:
					bCheck = HT_FALSE;	// ÷�� �Ұ���
					break;
			}
		}
	}
	// �׼�����
	else
	{
		// ����
		if( CHTParamIDCheck::HT_bIsItemAccessoryBracelet( dwWorkIndex )	
								&& !BIT_AND( _REFINE_ACCESSORY_BRACELET, iRefinableType ) )	
			bCheck = HT_FALSE;	// ÷�� �Ұ���
		// �Ͱ���
		if( CHTParamIDCheck::HT_bIsItemAccessoryEarring( dwWorkIndex )
								&& !BIT_AND( _REFINE_ACCESSORY_EARRING, iRefinableType ) )	
			bCheck = HT_FALSE;	// ÷�� �Ұ���
		// �����
		if( CHTParamIDCheck::HT_bIsItemAccessoryNecklace( dwWorkIndex )
								&& !BIT_AND( _REFINE_ACCESSORY_NECKLACE, iRefinableType ) )	
			bCheck = HT_FALSE;	// ÷�� �Ұ���
		// ����
		if( CHTParamIDCheck::HT_bIsItemAccessoryRing( dwWorkIndex )
								&& !BIT_AND( _REFINE_ACCESSORY_RING, iRefinableType ) )		
			bCheck = HT_FALSE;	// ÷�� �Ұ���
	}
	
	// ��ī�� ���� ������ ���� �������͸� �Բ� ��� �� �� ����.
	if (dwRefineIndex2 == 6555) 
	{
		// ���� ������ ���� �����۸� ���� ���� (��, ����̴� ����)
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
				case 6601:	//�󰡸���
				case 6602:	//�Ҷ󸶴�
				case 6603:	//�����
				case 6604:	//���Ƽ
				case 6606:	//����Ǫ��
				case 6607:	//�񽴴�
				case 6608:	//�Ƴ���Ÿ
				case 6609:	//���
					bCheck = true;
					break;

				default:
					return ECONOMY_ADDITEM_ERR_SUB_OVER;	// error
					break;
			}
		}
		else
		{
			m_bMessage_Error = HT_TRUE;	// ���� ����
			//HT_vNPCControl_SetMessage( eMsgRefineErr2 );
			return ECONOMY_ADDITEM_ERR_NEEDNOT;
		}
	}

	if( bCheck == HT_FALSE )	// ÷�� �Ұ����� ������ᰡ ����
	{
		// ÷�� �Ұ����� ����� �̸��� ����
		if( g_pParamMgr->HT_bGetItemName( dwRefineIndex, &strName ) == false )
			strName.HT_hrCleanUp();
		return ECONOMY_ADDITEM_ERR_IMPOSSIBLE_ITEM;
	}

	return ECONOMY_ADDITEM_ERR_NONE;	// ���� ����
}

//----------����/��ü---------//
HTvoid CHTNPCControl::HT_vNPCControl_FixDisjoint_LButtonClick( DWORD dwItemKeyID )
{
	HTshort sType = g_cItemSystem->HT_sItemSystem_GetItemType(dwItemKeyID);

	HTbool res = HT_TRUE;
	// ������ ������ ���������� �Ӽ��� ���� NPC�� �˻�
	// �������� NPC�� üũ���� ����
	if( m_iResent == NPC_RESENT_FIX )
		res = HT_bNPCControl_CheckItemAttriForFixDisjoint(dwItemKeyID);

	if( m_iResent == NPC_RESENT_DISJOINT || m_iResent == NPC_RESENT_ITEM_LIST )
	{
		// ����ȭ ���������� �˻��Ͽ� ����ȭ �������� �ǸźҰ����� �˸� (���� ������ �Ǹ� ����) ������ 2004. 9. 16
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
			// �̰����� ������ �� ���� �������Դϴ�.
			HT_vNPCControl_SetMessage( eMsgItemRepairDoNot );

			m_bMessage_Error = HT_TRUE;
			// �Ϸ�(����)â
			//m_byMessageWin = NPC_MESSAGE_NONE;
			g_cUINPCWindow->m_MessageBoxNo = -1;
			g_cUIManager->HT_MessageBox(_DIALOG_NPCWINDOW, m_szMessage, 0);
		}
		else
		{
			// ������ �ʿ��� ���������� �˻�
			HTbool bNeed = g_cItemSystem->HT_bItemSystem_CheckNeedFix( dwItemKeyID );
			// �������� ����� ���
			if( bNeed == HT_TRUE )
				HT_vNetWork_CSP_REQ_ITEM_REPAIR();
			else
			{
				// ������ �ʿ䰡 ���� �������Դϴ�.
				HT_vNPCControl_SetMessage( eMsgItemRepairNeedNot );
				// �ý��� â�� ǥ��
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
			}
		}
	}
	else if( m_iResent == NPC_RESENT_DISJOINT || m_iResent == NPC_RESENT_ITEM_LIST )
	{
		if(res == HT_FALSE)
		{
			// �̰����� �Ǹ��� �� ���� �������Դϴ�.
			HT_vNPCControl_SetMessage( eMsgItemSellDoNot );

			m_bMessage_Error = HT_TRUE;
			m_byMessageWin = NPC_MESSAGE_COMPLETE;
			g_cUIMerchantWindow->m_MessageCode = 1;
			g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, m_szMessage, 0);
		}	
		else
		{
			// ��ü�� ������ ��Ȯ�� �޼��� ����
			// �������� �Ǹ� �Ͻðڽ��ϱ�?
			HT_vNPCControl_SetMessage( eMsgItemSellQuestionItem );

			m_bMessage_Error = HT_FALSE;
			m_byMessageWin = NPC_MESSAGE_CONFIRM;
			g_cUIMerchantWindow->m_MessageCode = 5;
			g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, m_szMessage, 0);
		}
	}
}

// ���� NPC���� ������ ������ ���������� �˻�
HTbool CHTNPCControl::HT_bNPCControl_CheckItemAttriForFixDisjoint(DWORD dwItemKeyID)
{
	HTbool res = HT_TRUE;
	DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwIndex == 0 )
		return HT_FALSE;

	if (g_wResentZoneServerID == 17 || g_wResentZoneServerID == 12)
		return HT_TRUE;

	// ȸ����, �Ҹ� ������, ��� => ���� �ʿ� ����
	if( CHTParamIDCheck::HT_bIsItemRefine( dwIndex ) 
			|| CHTParamIDCheck::HT_bIsItemUsable( dwIndex ) || CHTParamIDCheck::HT_bIsItemCollect( dwIndex ) )
		res = HT_FALSE;
	// ����
	else if( g_wResentZoneServerID != ZONE_JINA3RD
				&& m_iEconomy_NPC == eEconomy_Item_Sword && !CHTParamIDCheck::HT_bIsItemWeapon( dwIndex ) ) 
			res = HT_FALSE;

	// �� : ���� - �ι��� ���� Įĭ(���� ����Ʈ ������)
	else if( g_wResentZoneServerID != ZONE_JINA3RD
				&& m_iEconomy_NPC == eEconomy_Item_Armor && 
		( dwIndex != HT_INDEX_REPAIR_QUEST_ITEM && !CHTParamIDCheck::HT_bIsItemDefence( dwIndex ) ) ) 
		res = HT_FALSE;
	// �׼����� ����
	else if( g_wResentZoneServerID != ZONE_JINA3RD
				&& m_iEconomy_NPC == eEconomy_Item_Bracelet && !CHTParamIDCheck::HT_bIsItemAccessory( dwIndex ) ) 
	{
		if (g_wResentZoneServerID != 16)
			res = HT_FALSE;
	}

	return res;
}

//---------- �κ��丮 â �˾� : ����/����/��ü�� ����������  -----------//
HTvoid CHTNPCControl::HT_vNPCControl_PopUpInventory(HTint nWinIndex)
{  
	if( _DIALOG_EQUPINVENTORY == nWinIndex)
	{
		// �κ��丮 â ����
		if( !g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) )
			g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
	}
	else if( _DIALOG_CHARINFO == nWinIndex )
	{
		// ����â ����
		if( !g_cUIManager->HT_isShowWindow( _DIALOG_STATUS ) )
			g_cStatus->HT_vStatus_ActiveSw();
	}
}

//----------���� ���콺�� ��ġ�� ����Ʈ�� �ִ� ������ ���� �ִ����˻�-----------//
HTint CHTNPCControl::HT_nNPCControl_ItemListMouseCheck_OnItem( HTint nCol, HTint nRow)
{
	if(m_iResent == NPC_RESENT_ITEM_LIST)
	{
		// ���õ� ������ ������ ã������ �̵�
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

#define HT_CHARGE_BUY_DISCOUNT_RATE		20.0f // ����ȭ ������ ������
#define HT_CHARGE_BUY_DISCOUNT_RATE2	10.0f // ����ȭ ������ ������
// ����ȭ �������� ���� ���� ���
HTint CHTNPCControl::HT_iNPCControl_CalPurchasingPriceForChargeItem( HTint iItemIndex, HTint iCount )
{
	// ����ȭ ���������� �˻�
	HTint iCash = 0;
	if( g_pParamMgr->HT_bGetItemCash( iItemIndex, &iCash ) == false || iCash <= 0 )
		return -1;

	// ���� �������� ������� ���� ���� ���� * ���� ���
	double iTotalPrice = iCash * iCount;

	// ���� ������ ������ ����
	HTint iDiscountNum = HT_iNPCControl_GetDiscountNumForChargeItem( iItemIndex );

	switch(g_iInationalType)
	{
	case INATIONALTYPE_KOREA:
	case INATIONALTYPE_JAPEN:
		if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )		// ���� ������
		{
			// ���� ������ 100�� �̸��� ��� 20������ 20%���� ����
			if( iCash < 100 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // ������ ����
			
			// ���� ������ 100�� �̻��� ��� 10������ 20%���� ����
			else if(iCash >= 100 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // ������ ����
		}
		else		// �Ϲ� ������
		{
			// ���� ������ 100�� ������ ��� 40������ 20%���� ����
			if( iCash <= 100 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // ������ ����
			
			// ���� ������ 101~300�� �� ��� 20������ 20%���� ����
			else if( 100 < iCash && iCash <= 300 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // ������ ����
			
			// ���� ������ 301~600�� �� ��� 10������ 20%���� ����
			else if( 300 < iCash && iCash <= 600 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // ������ ����
			
			// ���� ������ 601~1000�� �� ��� 5������ 20%���� ����
			else if( 600 < iCash && iCash <= 1000 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // ������ ����
			
			// ���� ������ 1001�� �̻��� ��� 3������ 20%���� ����
			else if( 1000 < iCash && iCash < 2300 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8);; // ������ ����

		}
		break;
	case INATIONALTYPE_CHINA:
		// ���� ������
		if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )
		{
			// ���� ������ 30Ÿ�� �̸��� ��� 20������ 10%���� ����
			if( iCash < 30 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.9); // ������ ����
			
			// ���� ������ 30�� �̻��� ��� 10������ 20%���� ����
			else if(iCash >= 30 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // ������ ����
		}
		// �Ϲ� ������
		else
		{
			// ���� ������ 14�� ������ ��� 40������ 10%���� ����
			if( iCash <= 14 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.9); // ������ ����
			
			// ���� ������ 15~30�� �� ��� 20������ 20%���� ����
			else if( 14 < iCash && iCash <= 30 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // ������ ����
			
			// ���� ������ 31~100�� �� ��� 10������ 20%���� ����
			else if( 30 < iCash && iCash <= 100 && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // ������ ����
			
			// ���� ������ 101�� �̻��� ��� 3������ 20%���� ����
			else if( 100 < iCash && iCount >= iDiscountNum )
				iTotalPrice = int((double)iTotalPrice * 0.8); // ������ ����
		}
		break;

	default:
		break;
	}

	return (int)iTotalPrice; // ���� ��ȯ
}

// ����ȭ �������� �ּ� ���� ����
HTint CHTNPCControl::HT_iNPCControl_GetMinCountForChargeItem( HTint iItemIndex )
{
	// ����ȭ ���������� �˻�
	HTint iCash = 0, iMinCount = 0;
	if( g_pParamMgr->HT_bGetItemCash( iItemIndex, &iCash ) == false || iCash <= 0 )
		return iMinCount;

	switch(g_iInationalType)
	{
	case INATIONALTYPE_KOREA:
	case INATIONALTYPE_JAPEN:
		// ���� ������
		if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )
		{
			// ���� ������ 100�� �̸��� ���
			if( iCash < 100 )
				iMinCount = 10; 
			// ���� ������ 100�� �̻��� ���
			else
				iMinCount = 5; 
		}
		// �Ϲ� ������
		else
		{
			// ���� ������ 100�� ������ ���
			if( iCash <= 100 )
				iMinCount = 20; 
			// ���� ������ 101~300�� �� ���
			else if( 100 < iCash && iCash <= 300 )
				iMinCount = 10; 
			// ���� ������ 301~600�� �� ���
			else if( 300 < iCash && iCash <= 600 )
				iMinCount = 5; 
			// ���� ������ 601~1000�� �� ���
			else if( 600 < iCash && iCash <= 1000 )
				iMinCount = 2; 
			// ���� ������ 1001�� �̻��� ���
			else
				iMinCount = 1; 
		}
		break;

	case INATIONALTYPE_CHINA:
		if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )		// ���� ������
		{
			iMinCount = 5; 			// ���� ������ 100�� �̸��� ���
		}
		else		// �Ϲ� ������
		{
			// ���� ������ 14�� ������ ���
			if( iCash <= 14 )
				iMinCount = 20; 
			// ���� ������ 15~30�� �� ���
			else if( 14 < iCash && iCash <= 30 )
				iMinCount = 10; 
			// ���� ������ 31~100�� �� ���
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

// ����ȭ �������� �������� ���� ����
HTint CHTNPCControl::HT_iNPCControl_GetDiscountNumForChargeItem( HTint iItemIndex )
{
	// ����ȭ ���������� �˻�
	HTint iCash = 0, iCount = 0;
	if( g_pParamMgr->HT_bGetItemCash( iItemIndex, &iCash ) == false || iCash <= 0 )
		return iCount;

	switch (g_iInationalType)
	{
		case INATIONALTYPE_KOREA:
		case INATIONALTYPE_JAPEN:
		{
			// ���� ������
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )
			{
				// ���� ������ 100�� �̸��� ���
				if( iCash < 100 )
					iCount = 20; 
				// ���� ������ 100�� �̻��� ���
				else
					iCount = 10; 
			}
			// �Ϲ� ������
			else
			{
				// ���� ������ 100�� ������ ���
				if( iCash <= 100 )
					iCount = 40; 
				// ���� ������ 101~300�� �� ���
				else if( 100 < iCash && iCash <= 300 )
					iCount = 20; 
				// ���� ������ 301~600�� �� ���
				else if( 300 < iCash && iCash <= 600 )
					iCount = 10; 
				// ���� ������ 601~1000�� �� ���
				else if( 600 < iCash && iCash <= 1000 )
					iCount = 5; 
				// ���� ������ 1001�� �̻��� ���
				else
					iCount = 3; 
			}
		}
		break;

		case INATIONALTYPE_CHINA:
		{
			// ���� ������
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) )
			{
				// ���� ������ 100�� �̸��� ���
				iCount = 10; 
			}
			// �Ϲ� ������
			else
			{
				// ���� ������ 14�� ������ ���
				if( iCash <= 14 )
					iCount = 40; 
				// ���� ������ 15~30�� �� ���
				else if( 14 < iCash && iCash <= 30 )
					iCount = 20; 
				// ���� ������ 31~100�� �� ���
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

//----------���콺 ����Ʈ�� ��ġ�� �������� ���� ������ ���´�.-----------//
HTint CHTNPCControl::HT_nNPCControl_GetItemInfo(HTint iItemIndex, HT_ITEMINFO& vInfo)
{
	// ������ ���� ������
	HT_ITEM_DATA* pData = HT_NULL;
	HT_ITEM_EXPANSION_DATA* pExtData = HT_NULL;
	CHTString str;
	
	HTint winSizeX = 0;
	// ������ ���� Lock ����
	if( g_pParamMgr->HT_bLockID( iItemIndex ) == false )
		return winSizeX;

	HTbyte byteOut = 0;
	HTint iOut = 0;
	HTshort sOut = 0;
	CHTString strTemp;

	// ������ �̸�
	if( g_pParamMgr->HT_bGetItemName( &str ) == true )
	{
		vInfo.strName.str = str;
		vInfo.strName.color = g_ColorTable[15];		// white
		winSizeX = vInfo.strName.str.HT_nGetSize();
	}

    // ������ ����
	g_pParamMgr->HT_bGetItemDescription( &vInfo.strDescription.str );
	switch (iItemIndex)
	{
		case 7064:	// �����̾� �ٷ��� �����۵��� ���� ������ ���ش�.
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem10, &strTemp, _T("") );	//	"30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� ������ ȿ��"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7065:
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem11, &strTemp, _T("") );	//	"30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. ��Ʈ�� ������ ȿ��"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7066:
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem12, &strTemp, _T("") );	//	"30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� �� ��Ʈ�� ������ ȿ��"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7067:
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem13, &strTemp, _T("") );	//	"��� ������ �ֹ��� 1��\n������ �ֹ��� 20��\n������ ������ 10��\n���� ��ɼ� 5��\n�̺�Ʈ�Ⱓ�� ���� �̺�Ʈ ������ ����\n\n30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� �� ��Ʈ�� ������ ȿ��\n4. ��� ��ũ�� 15 ���"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7069: // ������� ���μ���
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem14, &strTemp, _T("") );	//	"������� 1��\n(�Ĺ̸��������� �������� ���� ��ȯ����)\n�����ġ 2��\n(������� �������� ����������)\n�������� ����� 2��\n(���������� �ٷ� ���尡��)\n�̺�Ʈ ��Ÿ�� �ϸ�Ÿ 250�� 2����\n��� ������ �ֹ��� 2��"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7073:	// ���̿���
			HT_g_Script_SetMessage( eMsgExPlanPremiumItem20, &strTemp, _T("") );	//	"6�� 5õ �÷� LCD / ��� �̾��� '���̿��� TMP-1000'>>http://www.ioneit.com"
			vInfo.strDescription.str.HT_szFormat(strTemp);
			break;
		case 7079:	// �ĸ���
			vInfo.strDescription.str.HT_szFormat("COMRADE GeForce 6600 3.3ns�׷��� ī��>>>>300MHz RAM DAC>>128MB RAM SPEED 400MHz 3.3ns>>DVI-1 ��� ���÷��� ����>>�����Ⱓ: 2��>>>>��뷮 ���߿��� ���� ��, S-Video ���̺�, �ѱۼ���>>>>�� ����ũ�λ���>>http://www.microsound.co.kr>>���ǿ��� ��ϰ���");
			break;
		case 6555: // ��ī��
			vInfo.strDescription.str.HT_szFormat("- �ּ����� �������� ���Ѻ��� ����\n- ���ý� ������ �Ӽ��� �ʱ�ȭ�Ǹ�\n     ÷���� ��������� �Ӽ��� �ο�\n\n- ��� ����, ���� ÷�� ����");
			break;
	}

	if( vInfo.strDescription.str == HT_INFO_ITEM_DESCRIPT_NULL )
		vInfo.strDescription.str.HT_hrCleanUp();
	else
		vInfo.strDescription.color = g_ColorTable[16]; //light grey

	
	// �ٷ��� �������� ���� X����� �ִ��� ������.
	if(iItemIndex >= 7064 && iItemIndex <= 7067 || iItemIndex == 7069 || iItemIndex == 7079 || iItemIndex == 6555)
	{
		winSizeX = 40;
		vInfo.strName.color = g_ColorTable[17];		// white
		vInfo.strDescription.color = g_ColorTable[15]; //light grey
	}


	//���Ǿ�
	HTbool bRes = HT_FALSE;
	if( CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex) ) // �����̾� ������ ���� npc�� ���
	{
		bRes = g_pParamMgr->HT_bGetItemCash( &iOut );
	
		HT_vNPCControl_SetMessage( eMsgItemInfoPrice3 ); // %s ĳ��
	}
	else
	{
		bRes = g_pParamMgr->HT_bGetItemRupiah( &iOut );

		HT_vNPCControl_SetMessage( eMsgItemInfoPrice2 ); // %s ���Ǿ�
		// �ֽ��������� ��ǰ ������ 30% ��������
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
			iOut = HTint(iOut * HT_ITEM_MAKE_MONEY_PENALTY);

		if (m_iNPCIndex == 1302)	// ����� ���� ������ ��� ����� ������ ���� ������ ���Ѵ�.
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
		
		CHTString szMoney = g_cUIManager->HT_strSetRestMark( iOut ); // ��ǥ ó��
		pData->str.HT_szFormat( m_szMessage.HT_szGetString(), szMoney.HT_szGetString() );

		vInfo.vSourceStr.push_back(pData);
		winSizeX = max(winSizeX, pData->str.HT_nGetSize());
	}
	if( CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex) ) // �����̾� ������ ���� npc�� ���
	{
		// �ּ� ���� ����
		HTint iMinCount = HT_iNPCControl_GetMinCountForChargeItem( iItemIndex );
		if( iMinCount > 1 )
		{
			pData = new HT_ITEM_DATA;
			pData->color = HT_COLOR( 1.0f, 0.96f, 0.6f, 1.0f);	// yellow
			
			HT_vNPCControl_SetMessage( eMsgPremiumInfoBuyMinCount ); // �ּ� %d�� ����
			pData->str.HT_szFormat( m_szMessage.HT_szGetString(), iMinCount );

			vInfo.vSourceStr.push_back(pData);
			winSizeX = max(winSizeX, pData->str.HT_nGetSize());
		}

		if (iOut < 2300 && g_iInationalType == INATIONALTYPE_KOREA ||  g_iInationalType == INATIONALTYPE_CHINA 
			|| iOut < 2300 && g_iInationalType == INATIONALTYPE_JAPEN)
		{
			// �������� ����
			pData = new HT_ITEM_DATA;
			pData->color = HT_COLOR( 1.0f, 0.96f, 0.6f, 1.0f);	// yellow
			
			HT_vNPCControl_SetMessage( eMsgPremiumInfoBuyDiscount ); // %d�� ���� �� %d%% ����
			HTint iDiscountNum = HT_iNPCControl_GetDiscountNumForChargeItem( iItemIndex );
			// 2004.09.09 ���� �������� �����ϰ� 20%�� ����ǰ� ����.

			HTfloat Rate = 20.0f;
			
			if( g_iInationalType == INATIONALTYPE_CHINA )
			{
				// �߱��� ��� ó��
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

	// ��ø �ִ� ����
	//if( g_pParamMgr->HT_bGetItemMaxCount( &byteOut ) && byteOut > 1 )
	//{
	//	pExtData = new HT_ITEM_EXPANSION_DATA;
	//	ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
	//	pExtData->basic.color = g_ColorTable[16]; //light grey
	//	//pExtData->basic.str.HT_szFormat("�ִ� ���� ���� %d", byteOut );	
	//	HT_vNPCControl_SetMessage( eMsgItemInfoMaxPackCount );
	//	pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), byteOut );

	//	vInfo.vAttributeStr.push_back(pExtData);
	//	winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize() );
	//}

	HTint iParam1 = 0, iParam2 = 0, iFunction = 0;
	//-----�������ѻ���------//
	if( g_pParamMgr->HT_bGetItemLimitTrimuriti( &iOut ) == true && iOut > 0 )
	{
		HTRESULT trimuriti = HT_FALSE;
		str.HT_hrCleanUp();

		pData = new HT_ITEM_DATA;
		if( BIT_AND( TRIMURITI_BRAHMA, iOut ) )
		{
			//str = "����帶"; 
			HT_vNPCControl_SetMessage( eMsgCommonTrimuritiBrahma );
			pData->str = m_szMessage;
			trimuriti = HT_TRUE;
		}
		if( BIT_AND( TRIMURITI_VISHNU, iOut ) )
		{
			if(trimuriti) //str += ", �񽴴�";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTrimuritiVishunu );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str = "�񽴴�";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTrimuritiVishunu );
				pData->str = m_szMessage;
			}
			trimuriti = HT_TRUE;
		}
		if( BIT_AND( TRIMURITI_SIVA, iOut ) )
		{
			if(trimuriti) //str += ", �ù�";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTrimuritiSiva );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "�ù�";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTrimuritiSiva );
				pData->str = m_szMessage;
			}
			trimuriti = HT_TRUE;
		}

		//str += " ����";
		HT_vNPCControl_SetMessage( eMsgItemInfoPrivateUse );
		pData->str = pData->str + _T(" ") + m_szMessage;

		// �ֽ��� �������� ���� ��� ���� ����
		if( BIT_AND( g_oMainCharacterInfo.byTrimuriti, iOut ) )
			pData->color = g_ColorTable[16]; //light grey
		else 
			pData->color = g_ColorTable[11];	//red

		vInfo.vLimitStr.push_back(pData);
		winSizeX = max(winSizeX, pData->str.HT_nGetSize());
	}
	if( g_pParamMgr->HT_bGetItemLimitTribe( &iOut ) == true && iOut > 0)		// ��������
	{
		HTRESULT tribe = HT_FALSE;
		str.HT_hrCleanUp();

		pData = new HT_ITEM_DATA;
		if( BIT_AND( TRIBE_NAGA, iOut ) )
		{
			//str = "����"; 
			HT_vNPCControl_SetMessage( eMsgCommonTribeNaga );
			pData->str = m_szMessage;
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_ASURA, iOut ) )
		{
			if(tribe) //str += ", �Ƽ���";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeAsura );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str = "�Ƽ���";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeAsura );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_YAKSA, iOut ) )
		{
			if(tribe) //str += ", ��ũ��";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeYaksha );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "��ũ��";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeYaksha );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_DEVA, iOut ) )
		{
			if(tribe) //str += ", ����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeDeva );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeDeva );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_KINNARA, iOut ) )
		{
			if(tribe) //str += ", Ų����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeKimnara );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "Ų����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeKimnara );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_RAKSHASA , iOut ) )
		{
			if(tribe) //str += ", ��ũ����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeRakshasa );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "��ũ����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeRakshasa );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_GANDHARVA, iOut ) )
		{
			if(tribe) //str += ", ���ٸ���";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeGandharva );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "���ٸ���";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeGandharva );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		if( BIT_AND( TRIBE_GARUDA, iOut ) )
		{
			if(tribe) //str += ", �����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeGaruda );
				pData->str = pData->str + _T(", ") + m_szMessage;
			}
			else	//str += "�����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonTribeGaruda );
				pData->str = m_szMessage;
			}
			tribe = HT_TRUE;
		}
		
		//str += " ����";
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
				//pData->str.HT_szFormat("Level %d�ʿ�", byteOut);
				HT_vNPCControl_SetMessage( eMsgItemInfoNeedLevel );
				pData->str.HT_szFormat( m_szMessage.HT_szGetString(), byteOut );
			}
			//else
			//	pData->str.HT_szFormat("Level %d����", byteOut);

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
		//pData->str.HT_szFormat("������ ��ũ�� %d", sOut);		// ������ ��ũ��
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
		//pData->str.HT_szFormat("�Ű��� ��ũ�� %d", sOut);		// �Ű��� ��ũ��
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
		// ������ ��ũ�� %d, sOut		// ������ ��ũ��
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
		// ������ ��ũ�� %d, sOut		// ������ ��ũ��
		HT_vNPCControl_SetMessage( eMsgItemInfoSoulChakra );
		pData->str.HT_szFormat( m_szMessage.HT_szGetString(), sOut );

		if( g_cStatus->HT_nGetPureChakraSoul() >= sOut )
			pData->color = g_ColorTable[16]; //light grey
		else
			pData->color = g_ColorTable[11];	//red

		vInfo.vLimitStr.push_back(pData);
		winSizeX = max(winSizeX, pData->str.HT_nGetSize());
	}
	//--------Ư��---------//
	// ���ý� ������ ������ 
	if( CHTParamIDCheck::HT_bIsItemRefine(iItemIndex) 
						&& g_pParamMgr->HT_bGetItemRefinableItemType(&iOut) == true && iOut > 0 )
	{
		// ÷�� ���� ������ �з�(Bit Set)
		HTRESULT enable = HT_FALSE;
		HTint nCommaCount = 0;

		str.HT_hrCleanUp();
		HTRESULT type = HT_FALSE;
		
		pExtData = new HT_ITEM_EXPANSION_DATA;
		ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
		// ����
		if( BIT_AND( _REFINE_WEPON_ONEHAND, iOut ) )
		{
			//str = "�Ѽչ���"; 
			HT_vNPCControl_SetMessage( eMsgCommonItemClassOneHand );
			pExtData->basic.str = m_szMessage;
			type = HT_TRUE;
		}
		if( BIT_AND( _REFINE_WEPON_TWOHAND , iOut ) )
		{
			if(type)
			{
				//str +=", �μչ���";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassTwoHand );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "�μչ���";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassTwoHand );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		// ��
		if( BIT_AND( _REFINE_DEFENCE_ARMOR , iOut ) )// �Ǻ�
		{
			if(type)
			{
				//str +=", �Ǻ�";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassArmor );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "�Ǻ�";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassArmor );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_PANTS , iOut ) )// ����
		{
			if(type)
			{
				//str +=", ����";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassPants );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassPants );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_GLOVES , iOut ) )// �尩
		{
			if(type)
			{
				//str +=", �尩";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassGloves );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "�尩";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassGloves );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_SHIELD, iOut ) )	// ����
		{
			if(type)
			{
				//str +=", ����";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassShield );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassShield );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_BELT, iOut ) )	// �㸮��
		{
			if(type)
			{
				//str +=", �㸮��";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassBelt );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "�㸮��";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassBelt );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_SHOES, iOut ) )	// �Ź�
		{
			if(type)
			{
				//str +=", �Ź�";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassShoes );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "�Ź�";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassShoes );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		if( BIT_AND( _REFINE_DEFENCE_HELMET, iOut ) )	// ����
		{
			if(type)
			{
				//str +=", ����";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassHelmet );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassHelmet );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
		// �׼�����
		if( BIT_AND( _REFINE_ACCESSORY_EARRING, iOut ) )	
		{
			if(type)
			{
				//str +=", �Ͱ���";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassEarring );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "�Ͱ���";
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
				//str +=", �����";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassNecklace );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "�����";
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
				//str +=", ����";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassBracelet );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "����";
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
				//str +=", ����";
				HT_vNPCControl_SetMessage( eMsgCommonItemClassRing );
				pExtData->basic.str = pExtData->basic.str + _T(", ") + m_szMessage;
				++nCommaCount;
			}
			else		//str += "����";
			{
				HT_vNPCControl_SetMessage( eMsgCommonItemClassRing );
				pExtData->basic.str = m_szMessage;
			}
			type = HT_TRUE;	
		}
			
		//str += "��";
		HT_vNPCControl_SetMessage( eMsgItemInfoUsable );
		pExtData->basic.str = pExtData->basic.str + _T(" ") + m_szMessage;
		pExtData->basic.color = g_ColorTable[16]; //light grey

		vInfo.vAttributeStr.push_back(pExtData);
		winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize()-(HTint)((HTfloat)nCommaCount/2.0 +0.5));
	}
	// ������
	if( g_pParamMgr->HT_bGetItemMaxDurability( &sOut ) == true )
	{
		if( sOut > 0 && sOut != HT_ITEM_INFINITY_DURABILITY ) 
		{
			pExtData = new HT_ITEM_EXPANSION_DATA;
			ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
			
			pExtData->basic.color = g_ColorTable[16]; //light grey

			HTint iMaxDur = sOut/HT_ITEM_DURABILITY_DIVIDING;
			if( sOut % HT_ITEM_DURABILITY_DIVIDING > 0 )
				++iMaxDur; // �ø� ó��
			//pExtData->basic.str.HT_szFormat("������ %d / %d", iMaxDur, iMaxDur );
			HT_vNPCControl_SetMessage( eMsgItemInfoDurability );
			pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iMaxDur, iMaxDur );
			
			vInfo.vAttributeStr.push_back(pExtData);
			winSizeX = max(winSizeX, (pExtData->basic.str.HT_nGetSize()) );
		}
		// ����/�� �� �ı��Ұ�
		else if( sOut == HT_ITEM_INFINITY_DURABILITY && CHTParamIDCheck::HT_bIsItemWeapon( iItemIndex )
							&& CHTParamIDCheck::HT_bIsItemDefence(iItemIndex ) )
		{
			pExtData = new HT_ITEM_EXPANSION_DATA;
			ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			pExtData->basic.color = g_ColorTable[11]; //red
			// �ı��Ұ�
			HT_vNPCControl_SetMessage( eMsgItemInfoUnbreakable );
			pExtData->basic.str = m_szMessage;
			
			vInfo.vAttributeStr.push_back(pExtData);
			winSizeX = max(winSizeX, (pExtData->basic.str.HT_nGetSize()) );
		}
	}
	
	// ����ó�� - ��޾ƴ��ٹ�/�ƴ��ٹ��� ������ ��� Effect�� ǥ������ �ʴ´�.
	if( iItemIndex == HT_INDEX_DAMAGE_UP || iItemIndex == HT_INDEX_SUPERIOR_DAMAGE_UP
										 || iItemIndex == HT_INDEX_SUPERIOR_DAMAGE_UP2 )
	{
		// ������ ���� Lock ����
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

			// ���ӽð� - ����ȿ�� ����ȭ �������� ��� ǥ������ ����
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) == false
				&& g_pParamMgr->HT_bGetItemEffect1Duration( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("   (���ӽð�:%d��)", iOut/HT_ITEM_DURATION_DIVIDING );	
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

			// ���ӽð� - ����ȿ�� ����ȭ �������� ��� ǥ������ ����
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) == false
				&& g_pParamMgr->HT_bGetItemEffect2Duration( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("   (���ӽð�:%d��)", iOut/HT_ITEM_DURATION_DIVIDING );		
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

		if( iItemIndex == 6601 || // ������ �������� ����° Ư�� ��¹��� (�󰡸���, �Ҷ󸶴�, �����, ���Ƽ)
			iItemIndex == 6602 || 
			iItemIndex == 6603 ||
			iItemIndex == 6604 ||
			iItemIndex == 6606 || // �߰� : 2006. 2. 17 (����� ���ü� �߰� : ����Ǫ��, �񽴴�, �Ƴ���Ÿ, ��� )
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

			// ���ӽð� - ����ȿ�� ����ȭ �������� ��� ǥ������ ����
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) == false
				&& g_pParamMgr->HT_bGetItemEffect3Duration( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("   (���ӽð�:%d��)", iOut/HT_ITEM_DURATION_DIVIDING );		
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

			// ���ӽð� - ����ȿ�� ����ȭ �������� ��� ǥ������ ����
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) == false
				&& g_pParamMgr->HT_bGetItemEffect4Duration( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("   (���ӽð�:%d��)", iOut/HT_ITEM_DURATION_DIVIDING );			
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

			// ���ӽð� - ����ȿ�� ����ȭ �������� ��� ǥ������ ����
			if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iItemIndex ) == false
				&& g_pParamMgr->HT_bGetItemEffect5Duration( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				//pExtData->basic.str.HT_szFormat("   (���ӽð�:%d��)", iOut/HT_ITEM_DURATION_DIVIDING );		
				HT_vNPCControl_SetMessage( eMsgItemInfoDuration );
				pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
		}
	}
	// ���� �ӵ�
	if( CHTParamIDCheck::HT_bIsItemWeapon( iItemIndex ) )
	{
		/* �����̳� �߰��� �Ӽ��� ���ؼ� ���ݼӵ� ����ƴ��� �˻��ؾ��� 2003.12.10 ���� */
		if( g_pParamMgr->HT_bGetItemCoolDownTime( &iOut ) == true && iOut > 0 )
		{
			pExtData = new HT_ITEM_EXPANSION_DATA;
			ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );
			
			HTint iSpeed = g_cItemSystem->HT_iItemSystem_CheckItemSpeedRange( iOut );
			pExtData->basic.color = g_ColorTable[16]; //light grey
			switch( iSpeed )
			{
				case HT_ITEM_SPEED_VERY_FAST : // ���� �ӵ� �ſ� ����	
					HT_vNPCControl_SetMessage( eMsgItemInfoAttackSpeedVeryHigh );	break;
				case HT_ITEM_SPEED_FAST		 : // ���� �ӵ� ����
					HT_vNPCControl_SetMessage( eMsgItemInfoAttackSpeedHigh );		break;
				case HT_ITEM_SPEED_NORMAL	 : // ���� �ӵ� ����		
					HT_vNPCControl_SetMessage( eMsgItemInfoAttackSpeedNormal );		break;
				case HT_ITEM_SPEED_SLOW		 : // ���� �ӵ� ����	
					HT_vNPCControl_SetMessage( eMsgItemInfoAttackSpeedLow );		break;
				case HT_ITEM_SPEED_VERY_SLOW : // ���� �ӵ� �ſ� ����	
					HT_vNPCControl_SetMessage( eMsgItemInfoAttackSpeedVeryLow );	break;
				default: pExtData->basic.str.HT_hrCleanUp(); break;
			}
			pExtData->basic.str = m_szMessage; 
			vInfo.vAttributeStr.push_back(pExtData);
			winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
		}
	}
	// �����Ÿ�
	//if( g_pParamMgr->HT_bGetItemRange( &byteOut ) && byteOut > 0 )
	//{
	//	pExtData = new HT_ITEM_EXPANSION_DATA;
	//	ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

	//	pExtData->basic.color = g_ColorTable[16]; //light grey
	//	pExtData->basic.str.HT_szFormat("�����Ÿ� %d", byteOut);		

	//	vInfo.vAttributeStr.push_back(pExtData);
	//	winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
	//}
	// �Ҹ� HP
	if( g_pParamMgr->HT_bGetItemCostHP( &iOut ) == true && iOut > 0 )
	{
		pExtData = new HT_ITEM_EXPANSION_DATA;
		ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

		pExtData->basic.color = g_ColorTable[16]; //light grey
		//pExtData->basic.str.HT_szFormat("�Ҹ� HP %d", iOut);		
		HT_vNPCControl_SetMessage( eMsgItemInfoCostHP );
		pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iOut);	

		vInfo.vAttributeStr.push_back(pExtData);
		winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
	}
	// �Ҹ� TP
	if( g_pParamMgr->HT_bGetItemCostTP( &iOut ) == true && iOut > 0 )
	{
		pExtData = new HT_ITEM_EXPANSION_DATA;
		ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

		pExtData->basic.color = g_ColorTable[16]; //light grey
		//pExtData->basic.str.HT_szFormat("�Ҹ� TP %d", iOut);		
		HT_vNPCControl_SetMessage( eMsgItemInfoCostTP );
		pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), iOut);

		vInfo.vAttributeStr.push_back(pExtData);
		winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
	}
	// �Ҹ� Item
	// �Ҹ� �������� �Ҹ���������� �ڱ� �ڽ��� �� �ִ�.
	if( g_pParamMgr->HT_bGetItemidCostItem( &iOut ) == true && iOut > 0 && iOut != iItemIndex)
	{
		pExtData = new HT_ITEM_EXPANSION_DATA;
		ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

		pExtData->basic.color = g_ColorTable[16]; //light grey
		
		CHTString str;
		g_pParamMgr->HT_bGetItemName( iOut, &str );
		//pExtData->basic.str.HT_szFormat("�Ҹ� Item %s", str.HT_szGetString());		
		HT_vNPCControl_SetMessage( eMsgItemInfoCostItem );
		pExtData->basic.str.HT_szFormat( m_szMessage.HT_szGetString(), str.HT_szGetString() );

		vInfo.vAttributeStr.push_back(pExtData);
		winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
	}

	// ������ ���� Lock ����
	g_pParamMgr->HT_bUnLockID( iItemIndex );

	return winSizeX;
}
 
// �����ڿ� ä���
HTbool CHTNPCControl::HT_bNPCControl_SetAidItemResource( DWORD dwItemKeyID )
{
	m_nEconomy_Work_SubItemKeyID[0] = dwItemKeyID;
	return HT_TRUE;
}

//----------����â���� ����� �����ڿ� �����----------//
HTbool CHTNPCControl::HT_bNPCControl_CancelSupportResource( DWORD dwItemKeyID )
{
	for(HTint i=0; i<3; ++i)
		m_nEconomy_Work_SubItemKeyID[i] = 0;
	return HT_FALSE;
}

// �������� ������ �� ĭ�� �� �ε���
#define HT_CTRG_MAX_PIECE		25
int g_iChaturangaPiece[]
= { 7193, 7194, 7195, 7196, 7197, // 4
	7198, 7199, 7200, 7201, 7202, // 9
	7203, 7204, 7205, 7206, 7207, // 14
	7208, 7209, 7210, 7211, 7212, // 19
	7213, 7214, 7215, 7216, 7217  // 24
};

//���� ��¡
#define HT_CTRG_KING		7205
// �� �д� ���� ���� ����
#define HT_CTRG_SQUAD_TOTAL_PIECE		4
//���� ��� ������ ��¡- ��� ���Ƽ ī��
#define HT_CTRG_BOSS_NORTH		7219
#define HT_CTRG_BOSS_NORTH_START		0
//���� ��� ������ ��¡ - �ٴ� ���Ƽ ī��
#define HT_CTRG_BOSS_SOUTH		7220
#define HT_CTRG_BOSS_SOUTH_START		4
//��� �⺴ - �ƽ��� ī��
#define HT_CTRG_BOSS_CAVALRY	7221
#define HT_CTRG_BOSS_CAVALRY_START		8
//��� ���� - ��� ī��
#define HT_CTRG_BOSS_TANK		7222
#define HT_CTRG_BOSS_TANK_START			12
//��� �� - ���� ī��
#define HT_CTRG_BOSS_CORPORAL	7223
#define HT_CTRG_BOSS_CORPORAL_START		16
//��� ���� - ��Ʈ�� ī��
#define HT_CTRG_BOSS_STAFF		7224
#define HT_CTRG_BOSS_STAFF_START		20
// �� �д� ���� g_iChaturangaPiece������ ��ġ 
byte g_byChaturangaSquadPiece[] 
= { 0, 3, 4, 5,		// ��� ���Ƽ ī��
	19, 20, 21, 24, // �ٴ� ���Ƽ ī��
	2, 10, 14, 22,	// �ƽ��� ī��
	1, 9, 15, 23,	// ��� ī��
	6, 8, 16, 18,	// ���� ī��
	7, 11, 13, 17 };// ��Ʈ�� ī��

// �������� ���� ����
HTvoid CHTNPCControl::HT_vNPCControl_ActiveChaturangaBoard()
{
	// �������� �� ǥ���ϱ�
	// ���� ��¡ - ��� ���� ȹ������
	if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( HT_CTRG_KING ) > 0 )
	{
	}
	else
	{
		// ���� ��� ����
		HT_vNPCControl_SetChaturangaPiece( eChaturangaNorth );
		// ���� ��� ����
		HT_vNPCControl_SetChaturangaPiece( eChaturangaSouth );
		// ��� ���
		HT_vNPCControl_SetChaturangaPiece( eChaturangaCavalry );
		// ��� ����
		HT_vNPCControl_SetChaturangaPiece( eChaturangaTank );
		// ��� ��
		HT_vNPCControl_SetChaturangaPiece( eChaturangaCorporal );
		// ��� ����
		HT_vNPCControl_SetChaturangaPiece( eChaturangaStaff );
	}
}

// �������� ���忡 �� ǥ���ϱ�
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
	// ������Ƽ�� ����
	if( iBtnNo < _CHARINFO_BUTTON_MUSCLE || _CHARINFO_BUTTON_SPIRIT < iBtnNo )
		return;

	CHTString strTemp;
	// ���� ��ư�� Ŭ���� 400 ��ũ���� ��쿡�� ������ ���ϰ� �Ѵ�. (������ ��ũ�� 400 ����) ������ 2004. 10. 25
	HTint iHeart;
	iHeart = g_cStatus->HT_nGetPureChakraHeart();
	if (iBtnNo == 2 && iHeart >= 400)
	{
		HT_g_Script_SetMessage( eMsgChakraCannotUpgrade, &strTemp, _T("") );		//	"��ũ�� ���ѿ� �ɷ� ��ũ�� �ø� �� �����ϴ�."
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
		return;
	}


	// �Ű� ��ư�� Ŭ���� 350 �̻��� ��쿡�� ������ ���ϰ� �Ѵ�. (�Ű��� ��ũ�� 350 ����) ������ 2005. 5. 27
	HTint iNerve;
	iNerve = g_cStatus->HT_nGetChakraNerve();
	if (g_oMainCharacterInfo.snTribe == 4 || g_oMainCharacterInfo.snTribe == 8)
	if (iBtnNo == 1 && iNerve >= 350)
	{
		HT_g_Script_SetMessage( eMsgChakraCannotUpgrade, &strTemp, _T("") );		//	"��ũ�� ���ѿ� �ɷ� ��ũ�� �ø� �� �����ϴ�."
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
		return;
	}

	m_bySelectPart = iBtnNo;

	// ������ ��û
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

//----------- ESC/X��ư�� ���� NPC�κ��丮 ���� --------------//
HTvoid CHTNPCControl::HT_vNPCControl_Inventory_Close()
{
	// ������ �̵����̾��� ���
	g_cItemControl->HT_vItemControl_ESC_ItemAntiActive(/*_DIALOG_GOODSKEEPING*/);
	// ������ ����ŷâ �ݱ�
	g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );
	
	m_bMessage_Error = HT_FALSE;	// ���� ����
	m_iResent = NPC_RESENT_DIALOG;

	// ��ȭ���� ��ȭ �ٲٱ�
	// ���ù��� ���������� ���ù��� �ƴ� �ٸ� �Է¿� ���� ���� �ܰ�� �Ѿ �� ����ϱ� ���� ���� �ִ�
	// 0~m_nSelectCount-1 : ���ù�, m_nSelectCount : Ȯ��, m_nSelectCount+1 : ���
	// ���콺 Ŭ���� ���� ���� �ܰ�� �Ѿ��.
	HT_vNPCControl_GetNextStep(m_nSelectCount);
}

//--------�޼��� �����찡 Ȱ��ȭ�Ǿ��ִ���----------//
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

//-----------���� �ð�(��/���� ���ִ� �ð�)�� ���´�---------//
HTfloat CHTNPCControl::HT_fNPCControl_GetCurTime()
{
	return g_pEngineHandler->HT_fGetCurrentTimeInAllDay();
}

//////////////////////////////////////////////////////////////////////////
// ��Ʈ��ũ ���� �Լ�
//////////////////////////////////////////////////////////////////////////
// ������ ����
HTvoid CHTNPCControl::HT_vNetWork_CSP_Req_Item_Buy()
{/*
	PS_CSP_REQ_ITEM_BUY info = HT_NULL;
	info = new S_CSP_REQ_ITEM_BUY;
	
	info->snNPCIndex = m_iNPCIndex;
	info->snItemIndex = HTshort(m_dwBuyItem - HT_ITEM_INDEX_START);
	// ������ ����
	info->snItemCount = m_iWorkItemCount;	

	// ���Ǿƴ� ������ �κ����� �ڵ����� ����.
	g_pNetWorkMgr->RequestItemBuy( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemBuy : %d:%d-%d��", 
													info->snNPCIndex, info->snItemIndex, info->snItemCount );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );*/
}
 
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Item_Buy( PS_SCP_RESP_ITEM_BUY info )
{
	g_cUIMerchantWindow->HT_vNetWork_SCP_Resp_Item_Buy(info);
}

// ���� �䱸
HTvoid CHTNPCControl::HT_vNetWork_CSP_REQ_ITEM_REPAIR()
{
	PS_CSP_REQ_ITEM_REPAIR info = HT_NULL;
	info = new S_CSP_REQ_ITEM_REPAIR;

	info->snNPCIndex = m_iNPCIndex;	// NPC �ε���
	
	// �������� ��ġ�� ��ҿ� ��ġ index
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
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemRepair : %d:(%d:%d)", 
	//												info->snNPCIndex, info->byPlace, info->byIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
} 
 
// ���� ���
HTvoid CHTNPCControl::HT_vNetWork_SCP_RESP_ITEM_REPAIR( PS_SCP_RESP_ITEM_REPAIR info )
{
	// KeyID ����
	HTint iKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID);
	m_dwFixDisjointKeyID = iKeyID;

	if( info->byResult == 0x00 )
	{
		m_bMessage_Error = HT_FALSE;	// ���� ����

		//---------- �ý���â�� ������ ȹ�� ��� ------------//
		m_iSpendMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney() - info->nMoney;
		if(m_iSpendMoney < 0 )
			m_iSpendMoney = 0;

		if (info->byDummy == 1)	// ���Ǿ� ���
		{
			// %d���ǾƸ� ����ؼ� %s��(��) �����Ǿ����ϴ�.
			HT_vNPCControl_SetMessage( eMsgItemRepairSuccess );
		}
		else
		{
			HT_vNPCControl_SetMessage( eMsgItemRepairOK );
		}
		        
		// �� ����
		if(info->nMoney > 0)
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(info->nMoney);
		else
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(0);

		// ������ �������� �������� �����Ѵ�.
		HTshort sMaxDur = g_cItemSystem->HT_sItemSystem_GetMaxDurability( m_dwFixDisjointKeyID );
		if( 0 <= sMaxDur && sMaxDur < HT_ITEM_INFINITY_DURABILITY )	// ���ѳ������� 255
			g_cItemSystem->HT_dwItemSystem_SetCurDurability( m_dwFixDisjointKeyID, sMaxDur);

		// ���� �������� ���� ���� ǥ��
		g_cItemSystem->HT_vItemSystem_RenewalDurabilityWarning( );

		// ��ȭ���� ��ȭ �ٲٱ�
		// ���ù��� ���������� ���ù��� �ƴ� �ٸ� �Է¿� ���� ���� �ܰ�� �Ѿ �� ����ϱ� ���� ���� �ִ�
		// 0~m_nSelectCount-1 : ���ù�, m_nSelectCount : Ȯ��, m_nSelectCount+1 : ���
		// ���콺 Ŭ���� ���� ���� �ܰ�� �Ѿ��.
		//HT_vNPCControl_GetNextStep(m_nSelectCount);	
	} 
	else 
	{
		// �Ϸ�â�� ������ �޼���
		if( info->byResult == REPLY_ITEM_REPAIR_MONEY_WANT)
            // ������ �ʿ��� ���Ǿư� �����մϴ�. 	
			HT_vNPCControl_SetMessage( eMsgItemCommonMoneyErr );
		else if ( info->byResult == REPLY_ITEM_REPAIR_OUTINDEX )
			// �������� ã�� �� �����ϴ�. 
			HT_vNPCControl_SetMessage( eMsgItemCommonCannotFindInfo );
		else if( info->byResult == REPLY_ITEM_REPAIR_ENOUGH)
			// ������ �ʿ䰡 ���� �������Դϴ�. 
			HT_vNPCControl_SetMessage( eMsgItemRepairNeedNot );
		else
			// �������� �������� ���߽��ϴ�. 
			HT_vNPCControl_SetMessage( eMsgItemRepairFail );

		m_bMessage_Error = HT_TRUE;	// ���� ����
		g_cUINPCWindow->m_MessageBoxNo = -1;
		// �Ϸ�â ���
		//m_byMessageWin = NPC_MESSAGE_COMPLETE;
		g_cUIManager->HT_MessageBox( _DIALOG_NPCWINDOW, m_szMessage, 0);	// �޼���
	}
	// �ý��� â�� ǥ��
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
}

// ��ü �䱸
HTvoid CHTNPCControl::HT_vNetWork_CSP_Req_Item_Sell()
{
	g_cUIMerchantWindow->HT_vNetWork_CSP_Req_Item_Sell();
	/*
	PS_CSP_REQ_ITEM_SELL info = HT_NULL;
	info = new S_CSP_REQ_ITEM_SELL;

	info->snNPCIndex = m_iNPCIndex;	// NPC �ε���

	// �������� ��ġ�� ��ҿ� ��ġ index
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

// ��ü ���
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Item_Sell( PS_SCP_RESP_ITEM_SELL info )
{
	g_cUIMerchantWindow->HT_vNetWork_SCP_Resp_Item_Sell(info);
}

// ��ũ�� Ȯ��
HTvoid CHTNPCControl::HT_vNetWork_CSP_REQ_Increase_Chakra()
{
	PS_CSP_REQ_INCREASE_CHAKRA info = HT_NULL;
	info = new S_CSP_REQ_INCREASE_CHAKRA;
	info->byChakra = m_bySelectPart+1;	// ������ 1���� ����
	
	g_pNetWorkMgr->RequestIncreaseChakra( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RequestIncreaseChakra:%d", info->byChakra );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
// ���� ��û
HTvoid CHTNPCControl::HT_vNetWork_CSP_REQ_ITEM_REFINING()
{
	PS_CSP_REQ_ITEM_REFINING info = HT_NULL;
	info = new S_CSP_REQ_ITEM_REFINING;
	
	// �������� ��ġ�� ��ҿ� ��ġ index
	HT_ITEMSETTING_FLAG sLocRoom;
	sLocRoom.nInventory = sLocRoom.nLocation = -1;
	// ������ ������ ��ġ
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
	// ���ÿ� ���� ������ ��ġ
	//BYTE	bySubPlace[3];											//	Index 0:��,������� 1:���÷���� 2:����
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

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ItemRefining : %d:%d(�������%d:%d) %d, %d", 
	//												info->byPlace, info->byIndex, info->bySubPlace[0], info->bySubIndex[0], info->bySubIndex[1], info->bySubIndex[2]);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );	
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_RESP_ITEM_REFINING( PS_SCP_RESP_ITEM_REFINING info )
{ 
	// ������ ���� ��� ���� ���޾��� ��츦 ����ؼ� ��Ŷ���� ���� ���� ����ؼ� ����� �����Ѵ�. 
	// ���õ� ������ KeyID ����
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

	// ������� ������ KeyID ����
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
		//---------- �ý���â�� ������ ȹ�� ��� ------------//
		//	�������� ������ ��������
		DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwWorkItem );
		if( dwIndex == 0 )
			return;

		HTbyte byLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( m_dwWorkItem );
		// �Ϸ�â�� ������ �޼���
		switch( info->byResult )
		{
			case REPLY_ITEM_REFINING_FAIL :		// ���� ����
			{
				m_bMessage_Error = HT_TRUE;	// ���� ����
				m_byResent_ServerMsg = SERVER_MSG_RESP_WORK_FAIL;

				if( byLevel > 0 )
				{
					// %s+%d ������ �����߽��ϴ�
					HT_vNPCControl_SetMessage( eMsgItemRefineOneOverErr );

					if (!CHTParamIDCheck::HT_bIsItemRefineSub( m_nEconomy_Work_SubItemIndex ))
					if (byLevel > 6)	// 7���� ū���¿��� �̷� �޽����� ��ٸ� �̰��� �ڵ�� ���� ���� ÷������ ����� ����̹Ƿ� +6���� ������ �ش�.
						g_cItemSystem->HT_bItemSystem_SetMainRefineLevel(m_dwWorkItem, 6);
				}
				else
				{
					// %s ������ �����߽��ϴ�.
					HT_vNPCControl_SetMessage( eMsgItemRefineFirstErr );
				}
			}
				break;
			case REPLY_ITEM_REFINING_DISAPPEAR :	// ���� ���� - ������ �Ҹ�
			{
				m_bMessage_Error = HT_TRUE;	// ���� ����
				m_byResent_ServerMsg = SERVER_MSG_RESP_WORK_ITEM_REMOVE;
				g_cItemSystem->HT_vItemSystem_DeleteItem(g_cNPCControl->m_dwWorkItem);

				// �����ϴ� �� �������� ��������ϴ�.
				HT_vNPCControl_SetMessage( eMsgItemRefineDisappear );
			}
				break;
			case REPLY_ITEM_REFINING_INITIALIZE : // ���� ���� - ������ �ʱ�ȭ
			{
				m_bMessage_Error = HT_TRUE;	// ���� ����
				m_byResent_ServerMsg = SERVER_MSG_RESP_WORK_ITEM_MAIN_INIT;

				// �������� �ʱ�ȭ�ǽ��ϴ�.
				g_cItemSystem->HT_bItemSystem_SetMainRefineLevel( g_cNPCControl->m_dwWorkItem, 0 );
				HT_vNPCControl_SetMessage( eMsgItemRefineInitialize );
			}
				break;
			case REPLY_ITEM_SUBREFINING_INITIALIZE :
			{
				m_bMessage_Error = HT_TRUE;	// ���� ����
				m_byResent_ServerMsg = SERVER_MSG_RESP_WORK_ITEM_SUB_INIT;
				// �������� �ʱ�ȭ�ǽ��ϴ�.
				g_cItemSystem->HT_bItemSystem_ClearSubRefineItem( g_cNPCControl->m_dwWorkItem );
				HT_vNPCControl_SetMessage( eMsgItemRefineInitialize );
			}
				break;
			default :	// info->byResylt == 0x00
			{
				m_bMessage_Error = HT_FALSE;	// ���� ����
				m_byResent_ServerMsg = SERVER_MSG_RESP_SUCCESS;

				if( byLevel > 0 )
					// %s+%d ������ �Ϸ�Ǿ����ϴ�.
					HT_vNPCControl_SetMessage( eMsgItemRefineOneOverOK );
				else
					// %s ������ �Ϸ�Ǿ����ϴ�.
					HT_vNPCControl_SetMessage( eMsgItemRefineFirstOK );
			}
			break;
		}

		// �� ����
		if(info->nMoney > 0)
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->nMoney );
		else
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(0);
		
		// ���ÿ� ���� ������� �����
		// 6554	�ƹ�Ƽ	���ý� ��������� �Ҹ��� �����մϴ�
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
		m_bMessage_Error = HT_TRUE;	// ���� ����
		m_byResent_ServerMsg = SERVER_MSG_RESP_ERROR;

		// �Ϸ�â�� ������ �޼���
		if( info->byResult == REPLY_ITEM_REFINING_MONEY_LACK)	// ���Ǿ� ����
		{
			HTint nRupiah = m_nEconomy_Work_LimitRupiah - g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
			// ���Ǿư� %d�����մϴ�.
			HT_vNPCControl_SetMessage( eMsgItemRefineNeedMoneyErr );
		}
		else if( info->byResult == REPLY_ITEM_REFINING_CANNOT)	
			// ÷�� �Ұ����� ��������Դϴ�.
			HT_vNPCControl_SetMessage( eMsgItemRefineMeterialErr );
		else if( info->byResult == REPLY_ITEM_REFINING_OVER)	// 10ȸ ���� ���� or ���� �Ұ����� ������
		{
			if( g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( m_dwWorkItem ) >= MAX_REFINE_MAIN_LEVEL )
				// ��ȭ ������ �� �� ���� �������Դϴ�.
				HT_vNPCControl_SetMessage( eMsgItemRefineMainCannot );
			else
				// �ּ� ������ �� �� ���� �������Դϴ�.");
				HT_vNPCControl_SetMessage( eMsgItemRefineSubCannot );
		}
		else if( info->byResult == REPLY_ITEM_REFINING_OUTINDEX )
			// �������� ã�� �� �����ϴ�.");
			HT_vNPCControl_SetMessage( eMsgItemCommonCannotFindInfo );
		else
			// �������� �������� ���߽��ϴ�.");
			HT_vNPCControl_SetMessage( eMsgItemRefineFail );
	}
	// �ý��� â�� ǥ��
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
/*
	if( m_bMessage_Error == HT_FALSE )	// ������ ���
	{
		//-----���� �̹����� ���ҽ� �����-----//
		HT_vNPCControl_ButtonCheck_Work_Delete();
		m_iResent = NPC_RESENT_NONE;
	}
	else
	{
		// ���ð�� ������ �����
		if( m_byResent_ServerMsg == SERVER_MSG_RESP_WORK_ITEM_REMOVE )
			g_cItemSystem->HT_vItemSystem_DeleteItem(m_dwWorkItem);
		// ���ð�� ��ȭ���� ���� �ʱ�ȭ
		else if( m_byResent_ServerMsg == SERVER_MSG_RESP_WORK_ITEM_MAIN_INITIAL )
			g_cItemSystem->HT_bItemSystem_SetMainRefineLevel( m_dwWorkItem, 0 );

		// Ŭ���̾�Ʈ���� �˻��� ������ ��� ��� �̹����� �����, �׷��������� ������ �̹���/������ �����
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
		m_bMessage_Error = HT_FALSE;	// ���� ����
		
		//HTint nTotalChakra = g_cStatus->HT_nGetTotalChakra();	// ���� �� ��ũ������Ʈ
		//m_szMessage.HT_szFormat("��ũ�� ����Ʈ�� ���󳪷� ȯ���߽��ϴ�"/*, nTotalChakra*/);
		HT_vNPCControl_SetMessage( eMsgChakraConversionOK );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, m_szMessage );

		// ȯ���� ���� ��ũ�� ����Ʈ�� ���� ����
		//HTshort tribe = g_cMainCharacter->HT_sMainChar_GetTribe();

		PS_SCP_RESP_CHAKRA_RISING info2 = HT_NULL;
		info2 = new S_SCP_RESP_CHAKRA_RISING;
		
		info2->nPrana = info->nPrana;
		info2->nChakraPoint = 50;
		//info2->snChakraMuscle = g_ChakraTable[CHAKRA_POINT_MUSCLE][(tribe-1)%4] ;	// ����
		//info2->snChakraNerve = g_ChakraTable[CHAKRA_POINT_NERVE][(tribe-1)%4];	// �Ű�
		//info2->snChakraHeart = g_ChakraTable[CHAKRA_POINT_HEART][(tribe-1)%4];	// ����
		//info2->snChakraSoul = g_ChakraTable[CHAKRA_POINT_SOUL][(tribe-1)%4];		// ����

		g_cStatus->HT_vStatus_SetChakra_Rising( info2 );
		HT_DELETE(info2);	
	}
	else
	{
		m_bMessage_Error = HT_TRUE;		// ���� ����
		
		if( info->byResult == 0x02 )
			// ������ �����ۿ� ���� ���� ȯ���� �����߽��ϴ�.
			HT_vNPCControl_SetMessage( eMsgChakraConversionItemErr );
		else
			// ��ũ�� ���󳪷� ȯ���ϴµ� �����߽��ϴ�.
			HT_vNPCControl_SetMessage( eMsgChakraConversionFail );

		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PRANA, m_szMessage );
	}

	// ��ȭ���� ��ȭ �ٲٱ�
	HT_vNPCControl_GetNextStep(m_nSelectCount);
}

// ���� ��� ����� ���
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
		m_bMessage_Error = HT_FALSE;	// ���� ����
		
		// ���� ����� ���� - 10���� ������ �׻� ���� ����Ѵ�
		// ���� 4��Ʈ�� 2��Ʈ��(10����/20����)�� ����, ���� 4��Ʈ�� 2��Ʈ(10����/20����)�� ���࿩��.
		HTbyte byFlag = g_oMainCharacterInfo.snDummy >> 4 ;
		HTbyte byUse = g_oMainCharacterInfo.snDummy & 0x0F;
		if( (byFlag & 0x02) && !(byUse & 0x02) ) // 10������ ������ ��������� 
			byUse |= 0x02;
		else // 20������ ������ ���������
			byUse |= 0x01;

		g_oMainCharacterInfo.snDummy |= byUse ;
		// ���� ��÷ ����
		switch( byResult )
		{
			case REPLY_COUPONEVENT_1ST:
				m_szMessage.HT_szFormat("�����ĸ� ȹ���߽��ϴ�");
				break;
			case REPLY_COUPONEVENT_2ST:
				m_szMessage.HT_szFormat("�������� ȹ���߽��ϴ�");
				break;
			case REPLY_COUPONEVENT_3ST:
				m_szMessage.HT_szFormat("�������� ȹ���߽��ϴ�");
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				m_szMessage.HT_szFormat("�϶� ȹ���߽��ϴ�");
				break;
			case REPLY_COUPONEVENT_4ST:
				m_szMessage.HT_szFormat("�϶� ȹ���߽��ϴ�");
				break;
			case REPLY_COUPONEVENT_5ST:
				m_szMessage.HT_szFormat("�϶� ȹ���߽��ϴ�");
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				m_szMessage.HT_szFormat("�� ��Ʈ�� ȹ���߽��ϴ�");
				break;
			case REPLY_COUPONEVENT_6ST:
				m_szMessage.HT_szFormat("�� ��Ʈ�� ȹ���߽��ϴ�");
				break;
			case REPLY_COUPONEVENT_7ST:
				m_szMessage.HT_szFormat("��ȭ�������� ȹ���߽��ϴ�");
				break;
			case REPLY_COUPONEVENT_8ST:
				m_szMessage.HT_szFormat("�׷���ī�带 ȹ���߽��ϴ�");
				break;
			case REPLY_COUPONEVENT_9ST:
				m_szMessage.HT_szFormat("<�ʰ��� Ÿ��ƫ��, �������>�� ȹ���߽��ϴ�");
				break;
			case REPLY_COUPONEVENT_10ST:
				m_szMessage.HT_szFormat("<�̲��� ������, �׸�����>�� ȹ���߽��ϴ�");
				break;
			default: // ��
				m_szMessage.HT_szFormat("�ϸ�Ÿ�� ȹ���߽��ϴ�");
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
				m_szMessage.HT_szFormat("�ĳ�ī�� ȹ���߽��ϴ�");
				break;
		}

		// ��ȭ���� ��ȭ �ٲٱ�
		HT_vNPCControl_GetNextStep( m_nSelectCount );
	}
	else
	{
		m_bMessage_Error = HT_TRUE;		// ���� ����

		switch( byResult )
		{
			case REPLY_COUPONEVENT_LACK : // �κ��丮 ���� ����
			{
				HT_vNPCControl_SetMessage( eMsgItemCommonInvenLack );
				
				// �Ϸ�â ���
				m_byMessageWin = NPC_MESSAGE_CONFIRM;
			}
				break;
			case REPLY_COUPONEVENT_UNKNOWN :
				m_szMessage.HT_szFormat("�߸��� ������ȣ�Դϴ�");
				HT_vNPCControl_GetNextStep( m_nSelectCount );
				break;
			default :
				m_szMessage.HT_szFormat("���� ����� �����߽��ϴ�");
				HT_vNPCControl_GetNextStep( m_nSelectCount );
				break;
		}
	}

	if( m_szMessage.HT_bIsEmpty() == HT_FALSE )
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
}

// ��ġ ���� ��û ���
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_SavePosition( PS_RESULT info )
{
	if( info->nResult == 0x00 )
		// ���� ��ġ�� ����Ǿ����ϴ�.
		HT_vNPCControl_SetMessage( eMsgSavePositionOK );
	else
		// ���� ��ġ�� �������� ���߽��ϴ�.
		HT_vNPCControl_SetMessage( eMsgSavePositionFail );

	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, m_szMessage );

	// ��ȭ���� ��ȭ �ٲٱ�
	HT_vNPCControl_GetNextStep(m_nSelectCount);
}

// PVP ���� ����Ʈ ��û ���
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_PVP_Rank()
{
	// ��ȭ���� ��ȭ �ٲٱ�
	HT_vNPCControl_GetNextStep(m_nSelectCount);
}

// �ֽ� ����
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
	
	g_pNetWorkMgr->RequestSelectTrimuriti( info, byType );	// byType = 1�� ����

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_SelectTrimuriti : %s-%d(type = %d)", info->CharName, info->byTrimuriti, info->byType);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );	
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Select_Trimuriti( MSG_TrimuritySelect* info )
{
	if (m_bTrimutiri == 1)	// ����
	{
		// �� ĳ������ �ֽ� ���� ���
		if( strcmp(info->CharName, g_oMainCharacterInfo.szCharName) == 0 )
		{
			// ��� �ø��� ����Ʈ 
			HTint idFx;
			g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_BRAMANUPGRADE, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );

			// �ֽ� ������ ��� ���Ǿư� �Ҹ�ȴ�
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );

			g_oMainCharacterInfo.byTrimuriti = info->byTrimuriti;
			// ĳ���� ����â�� �ֽ� ���� ����
			CHTString szString;
			szString = g_cStatus->HT_szStatus_GetTrimuriti();
/*
			//	�ֽż����� ���� ������
			MSG_Broadcast* pData = HT_NULL;
			pData = new MSG_Broadcast;
			pData->byBgColor		= 14;			    // ä�� �޼��� ����
			pData->byTextColor		= 14;			    // ä�� �޼��� ����
			pData->byMsgType		= 1;
			pData->byTrimuriti		= g_oMainCharacterInfo.byTrimuriti;
			// /���� %s���� %s�ֽ��� �����߽��ϴ�.
			HT_vNPCControl_SetMessage( eMsgTrimuritiChangeOK ); // /���� %s���� %s�ֽ��� �����߽��ϴ�.
			CHTString::HT_hrStringCopy( pData->szMsg, m_szMessage, MAX_NOTIFY_LENGTH ); // MAX_NOTIFY_LENGTH = 1024
			CHTString::HT_hrStringCopy( pData->szName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH ); // SZNAME_LENGTH = 20
			// �޽��� ������ ������ ��û��
			g_pNetWorkMgr->ReqNotifyMessage( pData );
			HT_DELETE( pData );
*/
			//	�ֽ� ��ũ ǥ�� �ϱ� �ϱ�
			g_cGuildSystem->HT_vTrimutiri_MarkOn();

			// �� ĳ������ �ֽż��� ����� ��� ��ȭâ ���� �ٲٱ�
			HT_vNPCControl_GetNextStep( m_nSelectCount );
		}
		else	// �ٸ� ĳ������ �ֽ� ����
		{
			//	�ֽ� ��ũ �����ϱ�
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTrimuritiD( info->CharName, info->byTrimuriti );
			//	�ֽ� ��ũ ǥ���ϱ�
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowTrimuritiMark();
		}
	}
	else	// ��ȸ�� ��쿡�� ���� ����
	{
		m_snBrahmaCount = info->nBrahmaCount;	// ����帶 
		m_snVishnuCount = info->nVishnuCount;	// �񽴴�
		m_snSivaCount = info->nSivaCount;	// �ù�
	}
}

// �ֽ� ����Ʈ Ȯ��
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Rising_Brahman( MSG_TrimurityPoint* info )
{
	// ���Ǿư� �Ҹ�ȴ�
	g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );
	// �ֽ� ����Ʈ
	g_oMainCharacterInfo.nBrahmanPoint = info->nBramanPoint;
	// ĳ���� ����â�� �ֽ�����Ʈ ���� ����
	CHTString strString;
	// %d, g_oMainCharacterInfo.nBrahmanPoint );
	strString = g_cUIManager->HT_strSetRestMark(g_oMainCharacterInfo.nBrahmanPoint);
	// ��ȭâ ���� �ٲٱ�
	HT_vNPCControl_GetNextStep( m_nSelectCount );
}

// ���� ��û
HTvoid CHTNPCControl::HT_vNetWork_CSP_REQ_Change_Job( )
{
	MSG_CLASS* info = HT_NULL;
	info = new MSG_CLASS;
	
	// �������� ������ �� �ִ� ������ �������ֱ� ������ 
	info->byClass1 = g_oMainCharacterInfo.byClass1+1;
	if( g_oMainCharacterInfo.byClass1 == CLASS_LEVEL0 )	// 1�� ������ ���
		info->byClass2 = g_cStatus->HT_iStatus_GetJob1ForTribe();
	else	// 2�� ������ ��� 2������ ����
		info->byClass2 = m_bySelectPart;

	g_pNetWorkMgr->ReqChangeJob( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ChangeJob : %d-%d", info->byClass1, info->byClass2 );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );	
}

HTvoid CHTNPCControl::HT_vNetwork_SCP_Resp_Change_Job( MSG_CLASS* info )
{
	if( info->nID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		if( info->byClass1 == g_oMainCharacterInfo.byClass1 && info->byClass2 == g_oMainCharacterInfo.byClass2 )
			// �������� ���߽��ϴ�.
			HT_vNPCControl_SetMessage( eMsgJobChangeFail );
		else
		{
			g_oMainCharacterInfo.byClass1 = info->byClass1;
			g_oMainCharacterInfo.byClass2 = info->byClass2;

			// %s(��)�� �����߽��ϴ�., g_cStatus->HT_szStatus_GetJobName().HT_szGetString()
			HT_vNPCControl_SetMessage( eMsgJobChangeOK );
		}

		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, m_szMessage );

		// ��ȭ���� ��ȭ �ٲٱ�
		HT_vNPCControl_GetNextStep(m_nSelectCount);
	}
	// �ֺ� ĳ���Ͱ� �������� ���
	else
	{
		if( info->byClass1 > CLASS_LEVEL0 )
		{
			m_szObjectName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(info->nID);
			// %s���� %d�� ������ �߽��ϴ�.,
			//	g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(info->nID).HT_szGetString(), info->byClass1
			HT_vNPCControl_SetMessage( eMsgJobChangeOtherChar );
		}
	}
}

// ���� �峳 ��ġ ��û ���
HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_RefineScale( MSG_RefineScale* info )
{ 
	if (g_wResentZoneServerID == 16)	// ����� ���������� ���� ó��
	{
		m_iDurgaReceiptofMoney = info->dwRupiah; // ������ �ݾ� ����
		HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
	}
	else
	{

		if( m_iResent == NPC_RESENT_REFINE_RATE_UP ) // �ູ ��ġ ������ ����
			HT_vNPCControl_Offering_SetGauge( info->snRefineScale ); 
		else // �峳�� ���� object�� Ŭ������ ���
		{
			// �峳â ����
			HT_vNPCControl_OfferingWin_Active( info->snRefineScale );
		}

		m_fGaugeTimer = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );	// ���� �ð� ����
	}
}

// �峳 ��û
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

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemOffering: %d��-%d���Ǿ�"
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

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemOffering: ����� %d���Ǿ�"
	//														, nRupiah );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_ItemOffering( MSG_ItemContribution* info )
{
	if( info->byResult == 0x00 ) // ����
	{
		if (g_wResentZoneServerID == 16)	// ����� ���������� ���� ó��
		{
			// �� ����
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwRupia );
			// �峳 ����
			HT_vNPCControl_SetMessage( eMsgOfferingOK );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, m_szMessage );
			return;
		}
		else
		{
			HT_vNPCControl_Offering_SetGauge( info->snRefineScale ); // �峳 ������ ����
			m_fGaugeTimer = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );	// ���� �ð� ����
			HT_vNPCControl_Offering_SetRupiah( 0 ); // �峳�� �ʱ�ȭ

			// �� ����
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwRupia );
			// �峳 ����
			HT_vNPCControl_SetMessage( eMsgOfferingOK );
		}
	}
	else
	{
		switch( info->byResult )
		{
			case REPLY_ITEM_CONTRIBUTION_OUTINDEX:
				// �κ��� ���� ������(������ ��ġ ����)
				HT_vNPCControl_SetMessage( eMsgItemCommonNotExistItem );
				break;
			case REPLY_ITEM_CONTRIBUTION_OUTPARAM:
				// ������ ������ ã�� �� ����
				HT_vNPCControl_SetMessage( eMsgItemCommonCannotFindInfo );
				break;
			case REPLY_ITEM_CONTRIBUTION_CANNOT:
				// �峳�� �� ���� ������
				HT_vNPCControl_SetMessage( eMsgOfferingCannot );
				break;
			case REPLY_ITEM_CONTRIBUTION_LACK:
				// �ݾ� ����
				HT_vNPCControl_SetMessage( eMsgItemCommonMoneyErr );
				break;
			default:
				// �峳 ����
				HT_vNPCControl_SetMessage( eMsgOfferingFail );
				break;
		}
	}

	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, m_szMessage );

	// �峳â�� ������ �����
	if (g_wResentZoneServerID != 16)
		HT_vNPCControl_OfferingItemDeleteAll( );
}

// �׽�ũ ��û
HTvoid CHTNPCControl::HT_vNetWork_CSP_Req_TaskQuest( HTint iTaskQuest )
{
	MSG_STANDARDPARM* info = HT_NULL;
	info = new MSG_STANDARDPARM;

	info->nID = iTaskQuest;		// Task ID

	short int snNpcIndex = 0;
	// �ӽ� �ڵ� (���ٶ� 2,3 ������ ��ȭ�� �ɾ��� ��� ����Ʈ ������ ���� 1���� index�� ����)

	switch( m_iNPCIndex )
	{
		// ���� ����
	case 1101 :	// ���ٶ�
	case 1205 :	// 18�� ���ٶ�
	case 1235 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1101;
		}
		break;

		// �� ����
	case 1102 :	// ���ٶ�
	case 1206 :	// 18�� ���ٶ�
	case 1236 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1102;
		}
		break;

		// �׼����� ���� 
	case 1103 :	// ���ٶ�
	case 1207 :	// 18�� ���ٶ�
	case 1237 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1103;
		}
		break;

		// �·�
	case 1104 :	// ���ٶ�
	case 1208 :	// 18�� ���ٶ�
	case 1238 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1104;
		}
		break;

		//	��ǰ��������
	case 1105 :	// ���ٶ�
	case 1209 :	// 18�� ���ٶ�
	case 1239 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1105;
		}
		break;

		// �������
	case 1108 :	// ���ٶ� 
	case 1212 : // 18�� ���ٶ�
	case 1242 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1108;
		}
		break;

		// ������(����Ʈ)
	case 1106 :	// ���ٶ�
	case 1210 : // 18�� ���ٶ�
	case 1240 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1106;
		}
		break;
		// �ּ���(���������뿩)
	case 1107 :		// ���ٶ�
	case 1211 :		// 18�� ���ٶ�
	case 1241 :		// 19�� ���ٶ�
		{
			snNpcIndex = 1107;
		}
		break;
		// ����1
	case 1001 :	// ���ٶ�
	case 1201 :	// 18�� ���ٶ�
	case 1231 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1001;
		}
		break;
		// ����2
	case 1002 :	// ���ٶ�
	case 1202 :	// 18�� ���ٶ�
	case 1232 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1002;
		}
		break;
		//	���ھ���1
	case 1003 :	// ���ٶ�
	case 1203 : // 18�� ���ٶ�
	case 1233 : // 19�� ���ٶ�
		{
			snNpcIndex = 1003;
		}
		break;

		//	���ھ���1
	case 1005 :	// ���ٶ�
	case 1204 : // 18�� ���ٶ�
	case 1234 : // 19�� ���ٶ�
		{
			snNpcIndex = 1005;
		}
		break;

		// ����Ʈ�� ���� NPC
	case 1115 :	// ���� ����ü
	case 1213 :	// 18�� ���ٶ�
	case 1243 : // 19�� ���ٶ�
		{
			snNpcIndex = 1115;
		}
		break;

		// �������ٴ� ���� NPC
	case 1116 :
	case 1214 : // 18�� ���ٶ�
	case 1244 : // 19�� ���ٶ�
		{
			snNpcIndex = 1116;
		}
		break;

		// �ƹ�Ÿ���� ���� ����
	case 1117 :
	case 1215 : // 18�� ���ٶ�
	case 1245 : // 19�� ���ٶ�
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
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_TaskQuest: %d-%d", info->nID, info->Parm );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_TaskQuest( MSG_STANDARDPARM* info )
{
	if( info->Parm == 0x00 ) //  ����
	{
		m_bMessage_Error = HT_FALSE;		// ���� ����

		// ������ ���׷� �Ǹ�
		if( TASK_QUEST_1_START <= info->nID &&  info->nID <= TASK_QUEST_1_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestMaraBloodSellOK );

		// ������ ���� ����
		else if( TASK_QUEST_2_START <= info->nID &&  info->nID <= TASK_QUEST_2_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestMaraSolutionMakingOK );

		// �ĳ�ī�� ����
		else if( TASK_QUEST_3_START <= info->nID &&  info->nID <= TASK_QUEST_3_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestPanacaMakingOK );

		// �������� ī�� �ռ�
		else if( TASK_QUEST_4_START <= info->nID &&  info->nID <= TASK_QUEST_4_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestChaturangaPieceOK );

		// �� ��/��� ���� ����
		else if( TASK_QUEST_5_START <= info->nID &&  info->nID <= TASK_QUEST_6_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestWeaponMakingOK );

		// ������ ���� 
		// ���� ���������� 1�� ��� ����, 1�� ���� ���� �� �κ�ǰ ����, �� ����
		else if( (TASK_QUEST_7_START <= info->nID &&  info->nID <= TASK_QUEST_13_END)
				|| (TASK_QUEST_42_START <= info->nID &&  info->nID <= TASK_QUEST_67_END) 
				|| (TASK_QUEST_79_START <= info->nID &&  info->nID <= TASK_QUEST_80_END) )
				
			HT_vNPCControl_SetMessage( eMsgTaskQuestItemMakingOK );

		// ������ �и�
		// �� �и��� ���� �κ�ǰ ����, �κ�ǰ �и��� ���� 1�� ��� ����
		else if( TASK_QUEST_14_START <= info->nID &&  info->nID <= TASK_QUEST_41_END )
			HT_vNPCControl_SetMessage( eMsgTaskQuestItemSeparationOK );

		// �� �̺�Ʈ ������
		else if( TASK_QUEST_68_START <= info->nID && info->nID <= TASK_QUEST_74_END)
			HT_vNPCControl_SetMessage( eMsgTaskQuestNullEventOK ); // �̺�Ʈ�� ��÷ �Ǿ����ϴ�.

		// ũ�������� �̺�Ʈ
		else if( TASK_QUEST_75_START <= info->nID && info->nID <= TASK_QUEST_75_END)
			HT_vNPCControl_SetMessage( eMsgTaskQuestMerryXMas );

		// ��Ǫ ũ����Ż ���׷��̵� �̺�Ʈ 
		else if( TASK_QUEST_76_START <= info->nID && info->nID <= TASK_QUEST_77_END)
			HT_vNPCControl_SetMessage( eMsgTaskQuestWeaponMakingOK );

		// ���� ����ָӴ� �̺�Ʈ ��� �޽���
		else if( TASK_QUEST_78_START <= info->nID && info->nID <= TASK_QUEST_78_END)
			HT_vNPCControl_SetMessage( eMsgTaskQuestEventBoxOnenOK );

		// ī�콺Ʈ�� �� �̺�Ʈ ������ ��� �޽���
		else if( TASK_QUEST_81_START <= info->nID && info->nID <= TASK_QUEST_87_END)
			HT_vNPCControl_SetMessage( eMsgTaskQuestItemMakingOK );

		// ����پ� ��ȯ
		else if( TASK_QUEST_83_START <= info->nID && info->nID <= TASK_QUEST_83_END)
			HT_vNPCControl_SetMessage( eMsgTradeSuccess );

		// �Ӽ� ���� �̺�Ʈ
		else if( TASK_QUEST_88_START <= info->nID && info->nID <= TASK_QUEST_88_END)
			HT_vNPCControl_SetMessage( eMsgTradeSuccess );

		// ��ȯ
		else if( TASK_QUEST_89_START <= info->nID && info->nID <= TASK_QUEST_89_END)
			HT_vNPCControl_SetMessage( eMsgTradeSuccess );

		else if( TASK_QUEST_90_START <= info->nID && info->nID <= 10600)
			HT_vNPCControl_SetMessage( eMsgTradeSuccess );
		
		// ���� �ܰ�� �Ѿ
		HT_vNPCControl_GetNextStep( m_nSelectCount ); 
	}
	else
	{
		m_bMessage_Error = HT_TRUE;		// ���� ����
		switch( info->Parm )
		{
			case 1: // �׽�ũ �ε��� ����
				HT_vNPCControl_SetMessage( eMsgTaskQuestCannotFindInfo );
				break;
			case 2: // NPC ��ȣ ����
				HT_vNPCControl_SetMessage( eMsgTaskQuestNPCIDErr );
				break;
			case 3: // �ʿ��� �������� �κ��丮�� ����
				HT_vNPCControl_SetMessage( eMsgTaskQuestNeedItemErr );
				break;
			case 4: // �κ��丮 ������ ����
				HT_vNPCControl_SetMessage( eMsgItemCommonInvenLack );
				break;
			case 5: // �� ����
				HT_vNPCControl_SetMessage( eMsgTaskQuestNeedMoneyErr );
				break;
			case 6: // NPC���� �Ÿ��� �ʹ� �ִ�
				HT_vNPCControl_SetMessage( eMsgCommonDistanceErrToNPC );
				break;
			case 7 : // Ȯ���� ���� �۾��� �����߽��ϴ�.
				HT_vNPCControl_SetMessage( eMsgTaskQuestRateErr );
				break;
			case 8 : // �˼��մϴ�. ���� �̰������� �̺�Ʈ�� ���� �ʽ��ϴ�.
				HT_vNPCControl_SetMessage( eMsgTaskQuestNoEventErr );
			case 9 : // ī���� ��ġ�� ���ǿ� ���� �ʽ��ϴ�.
				HT_vNPCControl_SetMessage( eMsgTaskQuestKarmaErr );
			case 10 : // ī���� ��ġ�� ���ǿ� ���� �ʽ��ϴ�.
				HT_vNPCControl_SetMessage( eMsgTaskQuestLevelErr );
			default: // �׽�ũ ����Ʈ ����
				HT_vNPCControl_SetMessage( eMsgTaskQuestFail );
				break;
		}
		// ���� �ܰ�� �Ѿ
		HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 
	}

	if( m_szMessage.HT_bIsEmpty() == HT_FALSE)
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, m_szMessage );
}

// ĳ�� ���� ��û
HTvoid CHTNPCControl::HT_vNetWork_CSP_Req_Item_Cash()
{
	Msg_Cash* info = HT_NULL;
	info = new Msg_Cash;
	info->byType = 1;

	g_pNetWorkMgr->RequestItemCash( info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Item_Cash");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Item_Cash( Msg_Cash* info )
{
	CHTString strCash;
	strCash.HT_szFormat("%d",info->nCash);
	m_nCash = info->nCash;

	// �����̾� ������ ����
	if( m_iResent == NPC_RESENT_PREMIUM_ITEM || m_iResent == NPC_RESENT_PREMIUM_ITEM2 || m_iResent == NPC_RESENT_PREMIUM_ITEM3)
	{
		// ������ ���Ը��â�� ĳ�� ǥ��
		// ������ ����Ʈ ����
		//HT_vNPCControl_GetItemList();
		HT_vNPCControl_GetPrimiumItemList();
	}
	// �� �ۿ� �����̾� ���� �̿��
	else
	{
		// ���� �ܰ�� �Ѿ
		HT_vNPCControl_GetNextStep( m_nSelectCount ); 
	}
}

// ��ų/���� ��й� ��û 2004. 8. 27 
HTvoid	CHTNPCControl::HT_vNetWork_CSP_Req_CharacterInitialize(HTint iCommand, HTint iType)   // ��ũ�� �ʱ�ȭ ���� ��û
{
	// Type  1 = ��ų,  2 = ��ũ��, 3 = 2�� ����,  4 = ��ų&��ũ��, 5 = �̺�Ʈ ������ ������û
	Msg_NPCCommand* info = HT_NULL;
	info = new Msg_NPCCommand;
	info->nNPCID =  m_iNPCIndex;
	info->byCommand = m_nCommand = iCommand;	// ������ ���� ���� ��ȸ�ϱ�
	info->byType = m_nType;

	switch (iType)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:

		// Type�� 3�̸� 2������ �ʱ�ȭ�� ��û �Ѵ�.
		if (iCommand == 2 && iType == 3)
		{
			info->byType = m_nType = iType;		// 2�� ���� �ʱ�ȭ ��û
		}
		else if (iCommand == 1)	// Command�� 2�̸� Ÿ���� ���� �ʴ´�.
		{
			info->byType = m_nType = iType;		// �ʱ�ȭ ���� ������ �ð��� ��ų���� ��ũ������ ����.
		}
		else if (iCommand == 2 && CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex) == HT_TRUE)
		{
			info->byType = m_nType = iType;		// �ʱ�ȭ ��û
		}
		break;

	case 5:	// �̺�Ʈ ������ �������� ��û
		info->byType = m_nType = iType;		// ���� ���� ��û
		break;
		}

	g_pNetWorkMgr->RequestCharacterInitialize( info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Char_Initialize Type=%d, Command=%d",m_nType, m_nCommand);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}


HTvoid 	CHTNPCControl::HT_vNetWork_SCP_Resp_Item_CharacterInitialize( Msg_NPCCommand* info )
{
 	m_nFirst = info->byFirst;		// ��ȸ�Ҷ��� ����� ���´�.
	m_nResult = info->byResult;	// ��û�Ҷ��� ���´�.
	m_nRupia = info->nRupia;
	CHTString strTemp;

	switch(m_nType)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:

			if (m_nType == 3)	// 2�� ���� �ʱ�ȭ ������ �޾��� ���
			{
				if (info->byResult == 0)	// ������ �ȳ�â ���
				{
					// ������ �ȳ�â ���
					HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// ���� �ܰ�� �Ѿ
					HT_vNPCControl_SetMessage( eMsgPremiumReq2GradeInitOK );
					m_bMessage_Error = HT_TRUE;
					m_byMessageWin = NPC_MESSAGE_COMPLETE;
					g_cUIStatus->m_MessageBoxType = 0;
					g_cUIManager->HT_MessageBox( _DIALOG_BACKGROUND, m_szMessage, 0); 
					return;
				}
				else
				{
					// ���н� �ȳ�â ���
					HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// ���� �ܰ�� �Ѿ
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
							HT_g_Script_SetMessage( eMsgSkillInitialized, &strTemp, _T("") );		//	"��ų�� �ʱ�ȭ �Ǿ����ϴ�."
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
							break;
						case 2:
							HT_g_Script_SetMessage( eMsgChakraInitialized, &strTemp, _T("") );		//	"��ũ�� �ʱ�ȭ �Ǿ����ϴ�."
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
							break;
						case 4:
							HT_g_Script_SetMessage( eMsgSkillChakraInitialized, &strTemp, _T("") );		//	"��ų �� ��ũ�� �ʱ�ȭ �Ǿ����ϴ�."
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
							break;
					}
					HT_vNPCControl_GetNextStep( m_nSelectCount+1 );
					return;
				}
				HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// ���� �ܰ�� �Ѿ
			}
			else
			{*/
				switch(info->byResult)
				{
					case 0:	// ����
						HT_g_Script_SetMessage( eMsgSkillInitialized, &strTemp, _T("") );		//	"��ų�� �ʱ�ȭ �Ǿ����ϴ�."
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
						break;
					case 1:	// ���Ǿ� ����
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "���Ǿư� �����մϴ�.");
						break;
					case 2:
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "�������� �����Ͽ� �۾� �����Ͽ����ϴ�");
						break;
					case 3:
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "�ʱ�ȭ�� �Ұ��� �մϴ�.");
						break;
					case 4:
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "�̺�Ʈ ����� �ƴմϴ�.");
						break;
					case 5:
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "�̹� �����ϼ̽��ϴ�.");
						break;
					default:
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "�̺�Ʈ ���ǿ� �ش���� �ʽ��ϴ�.");
						break;
//				}

//				HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 	// ���� �ܰ�� �Ѿ
				g_cUIManager->HT_HideWindow( _DIALOG_NPCWINDOW );

			}
			return;

		case 5:	// NPC �̺�Ʈ ������ �������� ��û ���
			m_iEventItem = info->nRupia;
			if (info->byResult != 0)
				HT_vNPCControl_GetNextStep( m_nSelectCount ); 	// ���� �ܰ�� �Ѿ
			else
				HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 	// ���� �ܰ�� �Ѿ
			return;
	}
}

// ��ɼ� ����ȭ ������ ��û
HTvoid CHTNPCControl::HT_vNetWork_CSP_Resp_Charge_Function_Item( HTdword dwItemIndex )
{
	Msg_Time* info = HT_NULL;
	info = new Msg_Time;
	info->nItemID = dwItemIndex - HT_ITEM_INDEX_START;

	g_pNetWorkMgr->RequestChargeFunctionItem( info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Charge_Function_Item : %d", info->nItemID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid CHTNPCControl::HT_vNetWork_SCP_Resp_Charge_Function_Item( Msg_Time* info )
{
	if( info->byResult == 0x00 )
	{
		// ĳ�� ����
		CHTString strCash;
		strCash.HT_szFormat("%d",info->nCash);
		m_nCash = info->nCash;
		
		HTdword dwItemIndex = info->nItemID + HT_ITEM_INDEX_START;
		CHTString szTime;
		switch( dwItemIndex )
		{
			case HT_INDEX_EXPAND_INVEN: // �κ��丮 Ȯ��
			{
				// Bag2 ��밡��
				g_cEquipInventory->HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH); 
				// �κ��丮�� Ȯ��ƽ��ϴ�.
				HT_vNPCControl_SetMessage( eMsgItemEquipInvenIncOK );
				// ���� ����
				g_cMainCharacter->HT_vMainChar_SetTimeStamp( eTime_Inven, info->dwTime );
				//g_cMainCharacter->HT_vMainChar_GetTimeStamp( eTime_Inven, szTime );
			}
				break;
			case HT_INDEX_EXPAND_SHOP: // ���λ��� Ȯ��
			{
				// ���λ����� Ȯ��ƽ��ϴ�.
				HT_vNPCControl_SetMessage( eMsgShopExpandOK );
				// ���� ����
				g_cMainCharacter->HT_vMainChar_SetTimeStamp( eTime_Store, info->dwTime );
			}
				break;
			case HT_INDEX_AUTO_ROUTING:	// �ڵ� ���ݱ� ����
			{
				// �ڵ� ���ݱ� ����� ����Ǿ����ϴ�.
				HT_vNPCControl_SetMessage( eMsgShopAutoRouting );

				// ���� ����
				g_cMainCharacter->HT_vMainChar_SetTimeStamp( eTime_AMoneyRoot, info->dwTime );
			}
				break;

			default:
				m_szMessage.HT_hrCleanUp();
				break;
		}

		// ���� ���� �����̾� ������ ��볻���� �����ִ� ���¶�� �����Ѵ�.
		if (g_cUIManager->HT_isShowWindow( _DIALOG_MY_USEINFO_V3 ) == HT_TRUE)
			g_cIndividualStore->HT_vIndividualStore_ButtonCheckForUseListOutPut();

		// ���� �ܰ�� �Ѿ
		HT_vNPCControl_GetNextStep( m_nSelectCount ); 
	}
	else
	{
		m_bMessage_Error = HT_TRUE;	// ���� ����
 
		if( info->byResult == REPLY_ITEM_BUY_GOLD_WANT)	// �� ����
			// ĳ���� �����մϴ�.
			HT_vNPCControl_SetMessage( eMsgItemCommonCashErr );
		else if( info->byResult == REPLY_ITEM_BUY_INVENTORY_LACK)	// �κ��丮 ���� ����
			// �κ��丮 ������ �����մϴ�.
			HT_vNPCControl_SetMessage( eMsgItemCommonInvenLack );
		else
			// ���� ��û�� �����߽��ϴ�.
			HT_vNPCControl_SetMessage( eMsgPremiumReqFail );

		//m_byMessageWin = NPC_MESSAGE_COMPLETE;
		
		// ���� �ܰ�� �Ѿ
		HT_vNPCControl_GetNextStep( m_nSelectCount+1 ); 
	}
	m_byResent_ServerMsg = SERVER_MSG_NONE;
	// �ý��� â�� ǥ��
	if( m_szMessage.HT_bIsEmpty() == HT_FALSE )
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
}

////////////////////////////////////////////////////////////////////////////////////////////
//--------- ������ ��ų �� ���콺�� Ŭ���� ��ų�� �̸� ------------//
CHTString CHTNPCControl::HT_szNPCControl_GetSelectSkillName() 
{
	if(m_dwSkillRegistIndex == 0)	// ���õ� ��ų index�� ������
		return _T("");

	// ��ų �̸� ã��
	for(int i = 0; i < m_nSkillList_Count; ++i)
	{
		if( m_dwSkillRegistIndex == m_nSkillList_Index[i] )
		{
			return m_szSkillList_Name[i];
		}
	}

	return _T(""); 
};

// ��� ����Ʈ�� �ޱ� ���� ������ ��� �ʱ�ȭ
HTvoid CHTNPCControl::HT_vNPCControl_SkillList_Delete()
{
	m_nSkillList_Count = 0;	// ���� ������ ��ų ��
	for(int i = 0; i<50; ++i)
	{
		m_szSkillList_Name[i].HT_hrCleanUp();
		m_nSkillList_Index[i] = 0;
		m_nSkillList_Type[i] = 0;
	}
}

//--------- ���� ������ ��ų ����Ʈ �������� -----------//
HTvoid CHTNPCControl::HT_vNPCControl_GetSkillList()
{
	// ��� ����Ʈ ������ ��� �ʱ�ȭ
	m_nSkillList_Count = 0;	// ���� ������ ��ų ��
	for(int i = 0; i<50; ++i)
	{
		m_szSkillList_Name[i].HT_hrCleanUp();
		m_nSkillList_Index[i] = 0;
	}
}
