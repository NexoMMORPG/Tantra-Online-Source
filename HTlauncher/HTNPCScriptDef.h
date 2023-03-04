#ifndef _HTNpcScriptDef_h_
#define _HTNpcScriptDef_h_

#define HT_TYPE_QUESTION			1	// ���ǹ�
#define HT_TYPE_SELECT				2	// ���ù�
#define HT_TYPE_STEP				3	// ���ǹ��� ���ù� ����
#define HT_TYPE_QUEST_STEP			4	// �ó����� ����Ʈ ����

//  ���
#define HT_LANGUAGE_KOREAN			_T("Korean")
#define HT_LANGUAGE_CHINESE			_T("Chinese")		// �߱�
#define HT_LANGUAGE_PHILIPPINE		_T("Philippine")	// �ʸ���
#define HT_LANGUAGE_INDONESIA		_T("Indonesia")		// �ε��׽þ�
#define HT_LANGUAGE_JAPANESE		_T("Japanese")		// �Ϻ���

//------------------------------------������ �� �̸�-----------------------------------//
#define HT_NPC_TYPE_NONE			0
#define HT_NPC_TYPE_WEPON			1	// �������
#define HT_NPC_TYPE_DEFENSE			2	// ������
#define HT_NPC_TYPE_ACCESSORY		3	// ��Ÿ��ǰ����
#define HT_NPC_TYPE_TEMPLE			4	// �·�
#define HT_NPC_TYPE_WAREHOUSE		5	// ��ǰ����
#define HT_NPC_TYPE_CHIEFGUARD		6	// �������
#define HT_NPC_TYPE_POSTHORSE		7	// ������
#define HT_NPC_TYPE_ANIMALLEND		8	// �ּ���
#define HT_NPC_TYPE_SOLDIER1		9	// ����1
#define HT_NPC_TYPE_SOLDIER2		10	// ����2
#define HT_NPC_TYPE_BOY1			11	// ���ھ���1
#define HT_NPC_TYPE_GIRL1			12	// ���ھ���1
#define HT_NPC_TYPE_QUEST_SOLDIER	13	// ����Ʈ�� ��������ü ���� NPC
#define HT_NPC_TYPE_QUEST_SPORBADA	14	// ����Ʈ�� �������ٴ� ���� NPC
#define HT_NPC_TYPE_QUEST_BOY		15	// ����Ʈ�� �������ٴ� ����1
#define HT_NPC_TYPE_BATTLE			16	// ������ NPC
#define HT_NPC_TYPE_SAVEPOINT		17	// ��ġ���� NPC
#define HT_NPC_TYPE_EVENTNPC		18	// �̺�Ʈ NPC1
#define	HT_NPC_TYPE_RESERVED		19	// (�̻��)
#define	HT_NPC_TYPE_ETC				20	
#define HT_NPC_TYPE_EXTRA_ETC2		21	// ETC Ȯ�� NPC2
#define HT_NPC_TYPE_EXTRA_ETC3		22	// ETC Ȯ�� NPC3
#define HT_NPC_TYPE_EXTRA_ETC4		23	// ETC Ȯ�� NPC4
#define HT_NPC_TYPE_EXTRA_ETC5		24	// ETC Ȯ�� NPC5
#define HT_NPC_TYPE_EXTRA_ETC6		25	// ETC Ȯ�� NPC6
#define HT_NPC_TYPE_EXTRA_ETC7		26	// ETC Ȯ�� NPC7

#define HT_RES_TABLENAME_SELECT				_T("Select")
#define HT_RES_TABLENAME_WEAPON				_T("Wepon_Que")		//��������
#define HT_RES_TABLENAME_WEAPON_STEP		_T("Wepon_Step")
#define HT_RES_TABLENAME_DEFENSE			_T("Defense_Que")	// ��
#define HT_RES_TABLENAME_DEFENSE_STEP		_T("Defense_Step")
#define HT_RES_TABLENAME_ACCESSORY			_T("Accessory_Que")	// �׼�����
#define HT_RES_TABLENAME_ACCESSORY_STEP		_T("Accessory_Step")
#define HT_RES_TABLENAME_TEMPLE				_T("Temple_Que")	// �·�
#define HT_RES_TABLENAME_TEMPLE_STEP		_T("Temple_Step")
#define HT_RES_TABLENAME_WAREHOUSE			_T("Warehouse_Que")	// ������
#define HT_RES_TABLENAME_WAREHOUSE_STEP		_T("Warehouse_Step")
#define HT_RES_TABLENAME_CHIEFGUARD			_T("Chiefguard_Que")// �������
#define HT_RES_TABLENAME_CHIEFGUARD_STEP	_T("Chiefguard_Step")
#define HT_RES_TABLENAME_POSTHORSE			_T("PostHorse_Que")	// ������
#define HT_RES_TABLENAME_POSTHORSE_STEP		_T("PostHorse_Step")
#define HT_RES_TABLENAME_ANIMALLEND			_T("AnimalLend_Que")// ���������뿩
#define HT_RES_TABLENAME_ANIMALLEND_STEP	_T("AnimalLend_Step")
#define HT_RES_TABLENAME_ETC				_T("Etc_Que")		// ����1,2, ���ھ���1, ���ھ���1, ����Ʈ�� ���� 
#define HT_RES_TABLENAME_ETC_STEP			_T("Etc_Step")
#define HT_RES_TABLENAME_BATTLE				_T("Battle_Que")		// ������ NPC	
#define HT_RES_TABLENAME_BATTLE_STEP		_T("Battle_Step")		
#define HT_RES_TABLENAME_SAVEPOINT			_T("SavePoint_Que")		// ��ġ ���� NPC	
#define HT_RES_TABLENAME_SAVEPOINT_STEP		_T("SavePoint_Step")
#define HT_RES_TABLENAME_QUEST_STEP			_T("Quest_Step")	// �ó����� ����Ʈ ����

// ID
// 10000������ �߰��Ǵ� NPC �ο�

// 300001 ~ 305000		: ���ù�

// 200001 ~ 201000	: ������� step
// 201001 ~ 202000	: ������ step
// 202001 ~ 203000	: ��Ÿ��ǰ���� step
// 203001 ~ 204000	: �·� step
// 204001 ~ 205000	: ��ǰ���� step
// 205001 ~ 206000	: ������� step
// 1000������ �߰��Ǵ� NPC step �ο�

//���ǹ�
// 1 ~ 10000			: �������
#define HT_ID_WEPON_QUE_START		1
#define HT_ID_WEPON_QUE_END			10000
// 10001 ~ 20000		: ������
#define HT_ID_DEFENSE_QUE_START		10001
#define HT_ID_DEFENSE_QUE_END		20000
// 20001 ~ 30000		: ��Ÿ��ǰ����
#define HT_ID_ACCESSORY_QUE_START	20001
#define HT_ID_ACCESSORY_QUE_END		30000
// 30001 ~ 40000		: �·�
#define HT_ID_TEMPLE_QUE_START		30001
#define HT_ID_TEMPLE_QUE_END		40000
// 40001 ~ 50000		: ��ǰ����
#define HT_ID_WAREHOUSE_QUE_START	40001
#define HT_ID_WAREHOUSE_QUE_END		50000
// 50001 ~ 60000		: �������
#define HT_ID_CHIEFGUARD_QUE_START	50001
#define HT_ID_CHIEFGUARD_QUE_END	60000
//������
#define HT_ID_POSTHORSE_QUE_START	60001
#define HT_ID_POSTHORSE_QUE_END		70000
//�ּ���
#define HT_ID_ANIMALLEND_QUE_START	70001
#define HT_ID_ANIMALLEND_QUE_END	80000
// Etc
#define HT_ID_ETC_QUE_START			80001
#define HT_ID_ETC_QUE_END			90000
// ������
#define HT_ID_BATTLE_QUE_START		100001
#define HT_ID_BATTLE_QUE_END		110000
// ��ġ ����
#define HT_ID_SAVEPOINT_QUE_START	110001
#define HT_ID_SAVEPOINT_QUE_END		120000
/*
//����1
#define HT_ID_SOLDIER1_QUE_START	80001
#define HT_ID_SOLDIER1_QUE_END		81000
//����2
#define HT_ID_SOLDIER2_QUE_START	81001
#define HT_ID_SOLDIER2_QUE_END		82000
//���ھ���1
#define HT_ID_BOY1_QUE_START		82001
#define HT_ID_BOY1_QUE_END			83000
//���ھ���1
#define HT_ID_GIRL1_QUE_START		83001
#define HT_ID_GIRL1_QUE_END			84000
// �������ٴ� ����
QUE_START							84001
QUE_END								85000
//������ ����
QUE_START							85001
QUE_END								86000
*/

// ���ù�
#define HT_ID_SELECT_START			300001
#define HT_ID_SELECT_END			400000
// step
#define HT_ID_WEPON_STEP_START		200001
#define HT_ID_WEPON_STEP_END		201000

#define HT_ID_DEFENSE_STEP_START	201001
#define HT_ID_DEFENSE_STEP_END		202000

#define HT_ID_ACCESSORY_STEP_START	202001
#define HT_ID_ACCESSORY_STEP_END	203000

#define HT_ID_TEMPLE_STEP_START		203001
#define HT_ID_TEMPLE_STEP_END		204000

#define HT_ID_WAREHOUSE_STEP_START	204001
#define HT_ID_WAREHOUSE_STEP_END	205000

#define HT_ID_CHIEFGUARD_STEP_START	205001
#define HT_ID_CHIEFGUARD_STEP_END	206000

//������
#define HT_ID_POSTHORSE_STEP_START	206001
#define HT_ID_POSTHORSE_STEP_END	207000
//�ּ���
#define HT_ID_ANIMALLEND_STEP_START	207001
#define HT_ID_ANIMALLEND_STEP_END	208000
//Etc
#define HT_ID_ETC_STEP_START		208001
#define HT_ID_ETC_STEP_END			220000

/*
//����1
#define HT_ID_SOLDIER1_STEP_START	208001
#define HT_ID_SOLDIER1_STEP_END		209000
//����2
#define HT_ID_SOLDIER2_STEP_START	209001
#define HT_ID_SOLDIER2_STEP_END		210000
//���ھ���1
#define HT_ID_BOY1_STEP_START		210001
#define HT_ID_BOY1_STEP_END			211000
//���ھ���1
#define HT_ID_GIRL1_STEP_START		211001
#define HT_ID_GIRL1_STEP_END		212000
*/

// �ó����� ����Ʈ ����
#define HT_ID_QUEST_STEP_START		220001
#define HT_ID_QUEST_STEP_END		221000
//������
#define HT_ID_BATTLE_STEP_START		225001
#define HT_ID_BATTLE_STEP_END		226000
//��ġ����
#define HT_ID_SAVEPOINT_STEP_START	226001
#define HT_ID_SAVEPOINT_STEP_END	227000

// ���ǹ�
#define HT_IS_WEPON_QUE( i )			( i >= HT_ID_WEPON_QUE_START ) && ( i <= HT_ID_WEPON_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_DEFENSE_QUE( i )			( i >= HT_ID_DEFENSE_QUE_START ) && ( i <= HT_ID_DEFENSE_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ACCESSORY_QUE( i )			( i >= HT_ID_ACCESSORY_QUE_START ) && ( i <= HT_ID_ACCESSORY_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_TEMPLE_QUE( i )			( i >= HT_ID_TEMPLE_QUE_START ) && ( i <= HT_ID_TEMPLE_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_WAREHOUSE_QUE( i )			( i >= HT_ID_WAREHOUSE_QUE_START ) && ( i <= HT_ID_WAREHOUSE_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_CHIEFGUARD_QUE( i )			( i >= HT_ID_CHIEFGUARD_QUE_START ) && ( i <= HT_ID_CHIEFGUARD_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_POSTHORSE_QUE( i )			( i >= HT_ID_POSTHORSE_QUE_START ) && ( i <= HT_ID_POSTHORSE_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ANIMALLEND_QUE( i )			( i >= HT_ID_ANIMALLEND_QUE_START ) && ( i <= HT_ID_ANIMALLEND_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ETC_QUE( i )					( i >= HT_ID_ETC_QUE_START ) && ( i <= HT_ID_ETC_QUE_END ) ? HT_TRUE : HT_FALSE 
/*
#define HT_IS_SOLDIER1_QUE( i )			( i >= HT_ID_SOLDIER1_QUE_START ) && ( i <= HT_ID_SOLDIER1_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_SOLDIER2_QUE( i )			( i >= HT_ID_SOLDIER2_QUE_START ) && ( i <= HT_ID_SOLDIER2_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_BOY1_QUE( i )				( i >= HT_ID_BOY1_QUE_START ) && ( i <= HT_ID_BOY1_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_GIRL1_QUE( i )			( i >= HT_ID_GIRL1_QUE_START ) && ( i <= HT_ID_GIRL1_QUE_END ) ? HT_TRUE : HT_FALSE
*/
#define HT_IS_BATTLE_QUE( i )				( i >= HT_ID_BATTLE_QUE_START ) && ( i <= HT_ID_BATTLE_QUE_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_SAVEPOINT_QUE( i )			( i >= HT_ID_SAVEPOINT_QUE_START ) && ( i <= HT_ID_SAVEPOINT_QUE_END ) ? HT_TRUE : HT_FALSE 

//���ù�
#define HT_IS_SELECT( i )				( i >= HT_ID_SELECT_START ) && ( i <= HT_ID_SELECT_END ) ? HT_TRUE : HT_FALSE
// STEP
#define HT_IS_WEPON_STEP( i )			( i >= HT_ID_WEPON_STEP_START ) && ( i <= HT_ID_WEPON_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_DEFENSE_STEP( i )			( i >= HT_ID_DEFENSE_STEP_START ) && ( i <= HT_ID_DEFENSE_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ACCESSORY_STEP( i )		( i >= HT_ID_ACCESSORY_STEP_START ) && ( i <= HT_ID_ACCESSORY_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_TEMPLE_STEP( i )			( i >= HT_ID_TEMPLE_STEP_START ) && ( i <= HT_ID_TEMPLE_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_WAREHOUSE_STEP( i )		( i >= HT_ID_WAREHOUSE_STEP_START ) && ( i <= HT_ID_WAREHOUSE_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_CHIEFGUARD_STEP( i )		( i >= HT_ID_CHIEFGUARD_STEP_START ) && ( i <= HT_ID_CHIEFGUARD_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_POSTHORSE_STEP( i )		( i >= HT_ID_POSTHORSE_STEP_START ) && ( i <= HT_ID_POSTHORSE_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ANIMALLEND_STEP( i )			( i >= HT_ID_ANIMALLEND_STEP_START ) && ( i <= HT_ID_ANIMALLEND_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_ETC_STEP( i )				( i >= HT_ID_ETC_STEP_START ) && ( i <= HT_ID_ETC_STEP_END ) ? HT_TRUE : HT_FALSE
/*
#define HT_IS_SOLDIER1_STEP( i )		( i >= HT_ID_SOLDIER1_STEP_START ) && ( i <= HT_ID_SOLDIER1_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_SOLDIER2_STEP( i )			( i >= HT_ID_SOLDIER2_STEP_START ) && ( i <= HT_ID_SOLDIER2_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_BOY1_STEP( i )			( i >= HT_ID_BOY1_STEP_START ) && ( i <= HT_ID_BOY1_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_GIRL1_STEP( i )			( i >= HT_ID_GIRL1_STEP_START ) && ( i <= HT_ID_GIRL1_STEP_END ) ? HT_TRUE : HT_FALSE
*/

#define HT_IS_QUEST_STEP( i )				( i >= HT_ID_ETC_STEP_START ) && ( i <= HT_ID_ETC_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_BATTLE_STEP( i )			( i >= HT_ID_BATTLE_STEP_START ) && ( i <= HT_ID_BATTLE_STEP_END ) ? HT_TRUE : HT_FALSE
#define HT_IS_SAVEPOINT_STEP( i )		( i >= HT_ID_SAVEPOINT_STEP_START ) && ( i <= HT_ID_SAVEPOINT_STEP_END ) ? HT_TRUE : HT_FALSE

/***************************************************************************************/
//--------- �Է¿� ���� �����ܰ�� ��ȯ�� �� -----------//
#define HT_SCRIPT_NEXTSTEP_FAIL			-1
#define HT_SCRIPT_NEXTSTEP_EQUALSTEP	0
#define HT_SCRIPT_NEXTSTEP_SUCCESS		1

// NPC ���� ��ũ��Ʈ�� �����ϱ� ���� ���Ǵ� ����
//---------------------------------------------------
// parameter
//---------------------------------------------------
#define HT_NPC_PARAM_START			0
#define HT_NPC_PARAM_END			100

typedef enum _eNpcParam
{
	eNpcParamNone				=	0,
	eNpcParamNeedPrana			=	1,	// �ʿ��� ���� 
	eNpcParamCharacterName		,	// ĳ���� �̸�
	eNpcParamTribeName			,	// ���� �̸�
	eNpcParamSkillName			,	// ��ų �̸�
	eNpcParamChakraName			,	// ��ũ�� �̸�
	eNpcParamTrimuritiName		,	// �ֽ� �̸�
	eNpcParamGuildName			,	// ��� �̸�
	eNpcParamJobName			,	// ���� �̸�
	eNpcParamCashRemain			,	// ���� ĳ�� 
	eNpcParamInitializeReqRupia ,	// ��ũ��/��ų �ʱ�ȭ�� �ʿ��� ���Ǿ�
	eNpcParamChangeGodReqRupia	,			// �ֽź��濡 �ʿ��� ���Ǿ�
	eNpcParamEventItemTotal		,		// �̺�Ʈ ������ �� ����
	eNpcParamDurgaState			= 33,		// ����� ���� ��Ȳ
	eNpcParamDurgaReceiptofMoney,			// ����� ������ ���Ǿ�
	eNpcParamGetMoneyYut		= 40	// ����� �� ��������(���Ǿ�)
} eNpcParam;

//---------------------------------------------------
// server event
//---------------------------------------------------
#define HT_NPC_SEVENT_START			1001
#define HT_NPC_SEVENT_END			3000

typedef enum _eNpcSEvent
{
	eNpcSEventReqNone			=	0,
	eNpcSEventReqItemList		=	1001,	// �����۸���Ʈ ��û
	eNpcSEventReqRank				,	// ��������Ʈ ��û
	eNpcSEventReqTrimuritiSelect	,	// �ֽż��� ��û
	eNpcSEventReqTrimuritiChange	,	// �ֽź��� ��û
	eNpcSEventReqTrimuritiPoint		,	// �ֽ�����Ʈ ��ȯ ��û
	eNpcSEventReqChangeJob			,	// ������û
	eNpcSEventReqSkillLearn			,	// ������� ��û
	eNpcSEventReqSkillDelete		,	// ������� ��û
	eNpcSEventReqTaskQuest			,	// �׽�ũ ����Ʈ ��û
	eNpcCEventReqExpandInven		,	// �κ��丮 Ȯ�� (�����̾� ���) /1010
	eNpcSEventReqExpandPrivateShop	,	// ���λ��� Ȯ�� (�����̾� ���) /1011
	eNpcSEventReqJopChangeInit		,	// 2������ �ʱ�ȭ(�����̾� ���) /1012
	eNpcSEventReqCash				,	// ĳ����û /1013
	eNpcSEventReqAutoRouting		,	// �ڵ� ���ݱ� (�����̾� ���) / 1014
	eNpcSEventReqinitChacra			,	// ��ũ�� �ʱ�ȭ (�����̾� ���) / 1015
	eNpcSEventReqinitSkill			,	// ��ų �ʱ�ȭ (�����̾� ���) / 1016
	eNpcSEventReqinitChacraSkill	,	// ��ũ��&��ų �ʱ�ȭ (�����̾� ���) / 1017
	eNpcSEventReqEventItemTotal		,	// �̺�Ʈ ������ �������� ��û /1018 (���̿���)
	eNpcSEventReqDrugaMoneyOut		,	// ����� �����ݾ� ��ȸ ��û 1019
	
	eNpcSEventReqQuestAllow		=	1121,// ����Ʈ �³���û
	eNpcSEventReqCouponRegister		,	// ���� ��� ��û

	eNpcSEventReqCharacterInitialize2 = 2998,	// ��ų/��ũ�� ��й� ���� ��û (��ų)
	eNpcSEventReqInitialize = 2999,				// ��ų/��ũ�� ��й� ��û
	eNpcSEventReqCharacterInitialize = 3000	// ��ų/��ũ�� ��й� ���� ��û (��ũ��)
	//eNpcSEventReqSkillList	=	110
} eNpcSEvent;

//---------------------------------------------------
// client event
//---------------------------------------------------
#define HT_NPC_CEVENT_START			3001
#define HT_NPC_CEVENT_END			5000

typedef enum _eNpcCEvent
{
	eNpcCEventNone					=	0,
	eNpcCEventDialog				=	3001,	// ��ȭ ���
	eNpcCEventQuestAllow				,	// ����Ʈ �³� ���
	eNpcCEventQuestOK					,	// ����Ʈ  �Ϸ��ȭ���� ���
	eNpcCEventReqItemList				,	// ���� ��� ��� - ���� ����Ʈ �����
	eNpcCEventItemMake					,	// ���� ���
	eNpcCEventFix						,	// ���� ���
	eNpcCEventDisjoint					,	// ��ü ���
	eNpcCEventInventory					,	// ��ǰ���� ���
	eNpcCEventSavePosition				,	// ��ġ���� ���
	eNpcCEventTrimuritiSelect			,	// �ֽż��� ���
	eNpcCEventTrimuritiChange			,	// �ֽź��� ���
	eNpcCEventCreateGuild				,	// �ƽ������� ���
	eNpcCEventCreateGuildMark			,	// �ƽ�����ũ����
	eNpcCEventChangeJob2				,	// 2���������
	eNpcCEventReqRank					,	// �������������
	eNpcCEventRank						,	// �������� ���
	eNpcCEventEvent						,	// �̺�Ʈ ��� ���
	eNpcCEventChaturangaBoard			,	// �������� ���� ���� ���
	eNpcCEventQuiz						,	// ���� ��� 
	eNpcCEventJob2Select				,	// 2�� ���� ���� ���
	eNpcCEventTaskQuest					,	// �׽�ũ ����Ʈ ��� // 3021
	eNpcCEventReqPriItemList			,	// ���� ��� ��� - ���� ����Ʈ ����� (�����̾� ������) /3022
	eNpcCEventTransformationShop		,	// ���� �̿�� (�����̾�) /3023
	eNpcCEventCreatePremiumGuildMark	,	// �ƽ��� ��ũ ���� (�����̾�) /3024
	eNpcCEventCallPaySystem				,	// �������� �ý��� ȣ�� (�����̾�) /3025
	eNpcCEventMuUseInfo					,	// �� ��� ����(�����̾�) /3026
	eNpcCEventReqPriItemList2			,	// ���� ��� ��� - ���� ����Ʈ ����� (�����̾� ��Ű�� ������) /3027
	eNpcCEventReqPriItemList3			,	// ���� ��� ��� - ���� ����Ʈ ����� (Ư����� ������) /3028
	eNpcCEventReqEventItem				,	// �̺�Ʈ ������ ���� ��û /3029 (���̿���)
	eNpcCEventReqEventCoupon			,	// ���� ��� �̺�Ʈ / 3030
	eNpcCEventReqDrugaMoneyIn			,	// ����� ���� ��û 3031
	eNpcCEventReqYutWindowPopup			,	// ������ ��Ȳ�� �˾����� ���� ������ ���� ���� ��û 3032
	eNpcCEventReqCheckWindowPopup		,	// �⼮üũ �̺�Ʈ ������ �˾� ��û (3033)
	eNpcCEventReqComeback				,	// �Ĺ�(����ȭ) �̺�Ʈ (3034)
	eNpcCEventReqGetYutMoneyList		,	// ���ְ� ���� �� �ִ� �� ������ȸ (3035)
	eNpcCEventReqGetYutMoney			,	// ���ְ� ���� �� �ִ� �� ���ݹޱ� (3036)
	eNpcCEventReqQuestEvent1			,	// ����Ʈ �̺�Ʈ �ϵμ���, �ϵ��޾��� ����� ó�� (3037)
	eNpcCEventReqQuestEvent2			,	// ����Ʈ �̺�Ʈ �ϵμ���, �ϵ��޾��� ����� ó�� (3038)
	eNpcCEventReqGuildCargoOpenWindow	,	// ���â�� �˾���ûâ1
	eNpcCEventReqGuildCargoShowInfo		,	// ���â�� �˾���ûâ2
	eNpcCEventReqGuildCargoSetPMT		,	// ���â�� �˾���ûâ3

	eNpcCEventReqRentalAdminSellInfo	,	// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �Ǹ���Ȳ ����) - 3042 - (�Ǹ� ����Ʈâ �˾�)
	eNpcCEventReqRentalAdminReciveItem	,	// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �����ޱ�) - 3043 - (�������� ������ ã���û ��Ŷ ȣ��)
	eNpcCEventReqRentalAdminReciveList	,	// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �������� ����Ʈ ����) - 3044 - (�������� ����Ʈâ �˾�)
	
	eNpcCEventReqRentalBuyList			,	// ����� ��Ź�Ǹ� �Ϲ��� (�Ǹ����� ������ ��Ϻ���) - 3045 (��Ź����â �˾�) - ���Ը��
	eNpcCEventReqRentalSell				,	// ����� ��Ź�Ǹ� �Ϲ��� (�ڽ��� ������ �Ǹ�) - 3046 (��Ź����â �˾�) - �ǸŸ��
	eNpcCEventReqRentalUsingTex			,	// ����� ��Ź�Ǹ� �Ϲ��� (��Ź�Ǹ� �̿� ���� ����) - 3047 (��ũ��Ʈ�� ���)
	eNpcCEventReqRentalItemRupia		,	// ����� ��Ź�Ǹ� ������ (��Ź�Ǹŵ� ������ ���Ǿ� ����) - 3048 (��ũ��Ʈ�� ���)
	eNpcCEventReqRentalSetTex		,	// ����� ��Ź�Ǹ� �Ϲ��� (��Ź�Ǹ� �̿� ���� ã��) - 3049 (��ũ��Ʈ�� ���)

	eNpcCEventCheckTrimuriti		=	3251,	// �ֽŰ˻�
	eNpcCEventCheckGuild				,	// �ƽ��� �˻�
	eNpcCEventCheckTrimuritiPoint		,	// �ֽ�����Ʈ ���ǰ˻�
	eNpcCEventCheckChangeJob			,	// �����˻�
	eNpcCEventCheckChakraInit			,	// ��ũ�� �ʱ�ȭ ����Ʈ ���� �˻�
	eNpcCEventCheckSkillInit			,	// ��ų �ʱ�ȭ ����Ʈ ���� �˻�
	eNpcCEventCheckJob2ChangeItem		,	// 2�� ������ ������ �˻� // 3257
	eNpcCEventCheckSkillInit2			,	// ��ų �ʱ�ȭ �̺�Ʈ (2006. 1. 9)
	eNpcCEventCheckEvent			=	3259,// �̺�Ʈ ��� ���� �˻�
		
	eNpcCEventPKStart				=	3260,	// ������û
	eNpcCEventPKEnd						,		// �������

	eNpcCEventItemRefine			=	3290,	// ���ø��

	eNpcCEventBramanPointUp				,	// ��� ����Ʈ Ȯ��
	eNpcCEventChakraUp					,	// ��ũ�� Ȯ��
	eNpcCEventSkillLearn				,	// ��� ����
	eNpcCEventSkillRemove				,	// ��� ����

	eNpcCEventReqUsingItem			=	3295,	// ����Ʈ �ʱ�ȭ NPC �̺�Ʈ

	eNpcCEventTaskQuest1			=	4001, // ������ ���׷� �Ǹ�	
	eNpcCEventTaskQuest2				, // ���� ���� ����		
	eNpcCEventTaskQuest3				, // �ĳ�ī�� ��ǰ ����
	eNpcCEventTaskQuest4				, // ī�� �ռ�
	eNpcCEventTaskQuest5				, // �Ѽ� ���� ����
	eNpcCEventTaskQuest6				, // ��� ���� ����
	// ���� ���������� 1�� ��� ����
	eNpcCEventTaskQuest7				, // ������ ���� ���� // 4007
	eNpcCEventTaskQuest8				, // ���� ���ײ� ����
	eNpcCEventTaskQuest9				, // ��ܿ� �ʰ� ����
	eNpcCEventTaskQuest10				, // ��ܿ� �� ����
	eNpcCEventTaskQuest11				, // ������ �Ʊ� ����
	eNpcCEventTaskQuest12				, // ��Ŀ� ¡1 ����
	eNpcCEventTaskQuest13				, // ��Ŀ� ¡2 ���� // 4013
	// �� �и��� ���� �κ�ǰ ����
	eNpcCEventTaskQuest14				, // ����, Ų����� �� �и� // 4014
	eNpcCEventTaskQuest15				,
	eNpcCEventTaskQuest16				,
	eNpcCEventTaskQuest17				, 
	eNpcCEventTaskQuest18				, // �Ƽ���, �������� �� �и� // 4018
	eNpcCEventTaskQuest19				,
	eNpcCEventTaskQuest20				, 
	eNpcCEventTaskQuest21				,
	eNpcCEventTaskQuest22				, // ��ũ��, ���ٸ��ٿ� �� �и� // 4022
	eNpcCEventTaskQuest23				, 
	eNpcCEventTaskQuest24				,
	eNpcCEventTaskQuest25				,
	eNpcCEventTaskQuest26				, // ����, ����ٿ� �� �и� // 4026
	eNpcCEventTaskQuest27				,
	eNpcCEventTaskQuest28				,
	eNpcCEventTaskQuest29				,
	// �κ�ǰ �и��� ���� 1�� ��� ����
	eNpcCEventTaskQuest30				, // ��Ʈ�ݱ� // 4030
	eNpcCEventTaskQuest31				,
	eNpcCEventTaskQuest32				,
	eNpcCEventTaskQuest33				, // ���Ÿ�� // 4033
	eNpcCEventTaskQuest34				,
	eNpcCEventTaskQuest35				,
	eNpcCEventTaskQuest36				, // �ʹٳ��� // 4036
	eNpcCEventTaskQuest37				,
	eNpcCEventTaskQuest38				,
	eNpcCEventTaskQuest39				, // ��Ʈ��ī�� // 4039
	eNpcCEventTaskQuest40				,
	eNpcCEventTaskQuest41				,
	// 1�� ���� ���� �� �κ�ǰ ����
	eNpcCEventTaskQuest42				, // ��Ʈ�ݱ� // 4042
	eNpcCEventTaskQuest43				,
	eNpcCEventTaskQuest44				,
	eNpcCEventTaskQuest45				, // ���Ÿ�� // 4045
	eNpcCEventTaskQuest46				,
	eNpcCEventTaskQuest47				,
	eNpcCEventTaskQuest48				, // �ʹٳ��� // 4048
	eNpcCEventTaskQuest49				,
	eNpcCEventTaskQuest50				,
	eNpcCEventTaskQuest51				, // ��Ʈ��ī�� // 4051
	eNpcCEventTaskQuest52				,
	eNpcCEventTaskQuest53				,
	// �� ����
	eNpcCEventTaskQuest54				, // ����, Ų����� // 4054
	eNpcCEventTaskQuest55				,
	eNpcCEventTaskQuest56				,
	eNpcCEventTaskQuest57				, // �Ƽ���, �������� // 4057
	eNpcCEventTaskQuest58				,
	eNpcCEventTaskQuest59				,
	eNpcCEventTaskQuest60				, // ��ũ��, ���ٸ��ٿ� // 4060
	eNpcCEventTaskQuest61				,
	eNpcCEventTaskQuest62				,
	eNpcCEventTaskQuest63				, // ����, ����ٿ� // 4063
	eNpcCEventTaskQuest64				,
	eNpcCEventTaskQuest65				,
	
	// �������� �� �׽�ũ ����Ʈ
	eNpcCEventTaskQuest66				,	// ��ȭ���� ���
	eNpcCEventTaskQuest67				,	// �׼����� ���

	// �׽�ũ ����Ʈ : �̺�Ʈ�� �� ����Ʈ 
	eNpcCEventTaskQuest68				,	// 10388	���ٶ� �������� ����Ʈ	1120
	eNpcCEventTaskQuest69				,	// 10389	���߶� �������� ����Ʈ	1154
	eNpcCEventTaskQuest70				,	// 10390	���� �������� ����Ʈ	1155
	eNpcCEventTaskQuest71				,	// 10391	������ �������� ����Ʈ	1156
	eNpcCEventTaskQuest72				,	// 10392	����帶 �������� ����Ʈ	1254
	eNpcCEventTaskQuest73				,	// 10393	�񽴴� �������� ����Ʈ	1255
	eNpcCEventTaskQuest74				,	// 10394	�ù� �������� ����Ʈ	1256

	// ũ�������� ����Ʈ
	eNpcCEventTaskQuest75				,	// ũ�������� ����Ʈ �̺�Ʈ 

	// ��Ǫ ũ����Ż ���׷��̵� ����Ʈ
	eNpcCEventTaskQuest76				,	// ��Ǫ ũ����Ż ���׷��̵� ����Ʈ1
	eNpcCEventTaskQuest77				,	// ��Ǫ ũ����Ż ���׷��̵� ����Ʈ2

	eNpcCEventTaskQuest78				,	// ���� ����ָӴ� �̺�Ʈ
	
	eNpcCEventTaskQuest79				,	// ������ ���� ����� �������� ��ǥ
	eNpcCEventTaskQuest80				,	// ������ ���� ����� �������� ��ǥ

	eNpcCEventTaskQuest81				,	// ����� ������ ī�콺Ʈ�� ����
	eNpcCEventTaskQuest82				,	// ����� ������ ī�콺Ʈ���� �̿��� ������ ��ȯ

	eNpcCEventTaskQuest83				,	// ���� ����پ� ��ȯ

	eNpcCEventTaskQuest84				,	// �� ��Ƽ1 �̺�Ʈ
	eNpcCEventTaskQuest85				,	// �� ��Ƽ2 �̺�Ʈ
	eNpcCEventTaskQuest86				,	// �� ��Ƽ3 �̺�Ʈ
	eNpcCEventTaskQuest87				,	// �� ��Ƽ4 �̺�Ʈ

	eNpcCEventTaskQuest88				,	// ���� �Ӽ����� �̺�Ʈ
	eNpcCEventTaskQuest89				,	// ���� �϶�Ƽ ���� ����
	
	eNpcCEventTaskQuest90				,	// ����� ������ ����

	eNpcCEventTaskQuest91				,	// ����

	eNpcCEventTaskQuest92				,	// ���� ����� ����
	eNpcCEventTaskQuest93				,	// ���� �в���

	eNpcCEventTaskQuest94				,	// 12�� ũ����Ż �������� 1
	eNpcCEventTaskQuest95				,	// 12�� ũ����Ż �������� 2
	eNpcCEventTaskQuest96				,	// 12�� ũ����Ż �������� 3

	eNpcCEventTaskQuest97				,	// 12�� �÷�Ƽ�� �ٷ��� �̺�Ʈ

	eNpcCEventTaskQuest98				,	// ��� ���� �׽�ũ ����Ʈ // ���߶� ��ȣ��
	eNpcCEventTaskQuest99				,	// ��� ���� �׽�ũ ����Ʈ // �ƴ����� ��ܻ� ���
	eNpcCEventTaskQuest100				,	// ��� ���� �׽�ũ ����Ʈ // �������� �����·� �̶�����
	eNpcCEventTaskQuest101				,	// ��� ���� �׽�ũ ����Ʈ // �������� ��ȭ���� ��
	eNpcCEventTaskQuest102				,	// ��� ���� �׽�ũ ����Ʈ // ������ ����� ���
	eNpcCEventTaskQuest103				,	// ��� ���� �׽�ũ ����Ʈ // ������ â������ ������

	eNpcCEventTaskQuest104				,	// ���� �λ� �̺�Ʈ

	eNpcCEventTaskQuest105				,	// 1�� �÷�Ƽ�� �ٷ��� �̺�Ʈ

	eNpcCEventTaskQuest106				,	// 3�� �÷�Ƽ�� �ٷ��� �̺�Ʈ
	eNpcCEventTaskQuest107				,	// 3�� �÷�Ƽ�� �ٷ��� �̺�Ʈ(2)
	eNpcCEventTaskQuest108				,	// 4�� �÷�Ƽ�� �ٷ��� �̺�Ʈ

	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,
	//eNpcCEventTaskQuest				,

	eNpcCEventInformationShow = 4998,		// ���������� ���� �Խ��� ����
	eNpcCEventInitialize = 4999,
	eNpcCEventCharacterInitialize = 5000

} eNpcCEvent;

//---------------------------------------------------
// condition
//---------------------------------------------------
#define HT_NPC_CONDITION_START			5001
#define HT_NPC_CONDITION_END			6000

#define HT_NPC_RELATIVE_CONDITION_START			5001
#define HT_NPC_RELATIVE_CONDITION_END			5025

#define HT_NPC_JOB_CONDITION_START				5041
#define HT_NPC_JOB_CONDITION_END				5050

#define HT_NPC_TRIBE_CONDITION_START			5054
#define HT_NPC_TRIBE_CONDITION_END				5070

#define HT_NPC_LEVEL_CONDITION_START			5071
#define HT_NPC_LEVEL_CONDITION_END				5100

typedef enum _eNpcCondition
{
	eNpcConditionNone				=	0,

	// ģ�е�
	eNpcConditionRelative1			=	5001,	
	eNpcConditionRelative2				,
	eNpcConditionRelative3				,
	eNpcConditionRelative4				,
	eNpcConditionRelative5				,
	eNpcConditionRelative6				,
	eNpcConditionRelative7				,
	eNpcConditionRelative8				,
	eNpcConditionRelative9				,
	eNpcConditionRelative10				,

	eNpcConditionRelative2Over 		=	5021,// ģ�е�2�̻�
	eNpcConditionRelative3Over 			,	// ģ�е�3�̻�
	eNpcConditionRelative4Over 			,	// ģ�е�4�̻�
	// �ð�
	eNpcConditionDay				=	5026,// ��
	eNpcConditionNight					,	// ��
	// ���� ��û ���
	eNpcConditionSuccess			=	5028,// ����
	eNpcConditionFail					,	// ����
	// ����
	eNpcConditionChangeJob1			=	5041,// 1�� ����
	eNpcConditionChangeJob2				,	// 2�� ����
	// ����
	//eNpcConditionJobSatvan			=	5043,// ����
	//eNpcConditionJobDhvanta				,	// �ϻ���
	//eNpcConditionJobNirvana				,	// ������
	//eNpcConditionJobMantrika			,	// ����
	eNpcConditionJobSatya			=	5043,// ��Ʈ��
	eNpcConditionJobVanare				,	// �ٳ���
	eNpcConditionJobDruta				,	// ���Ÿ
	eNpcConditionJobKarya				,	// ī����
	eNpcConditionJobNakayuda			,	// ��ī����
	eNpcConditionJobVaidya				,	// ���̵��
	eNpcConditionJobAbicara				,	// �ƺ�ī��
	eNpcConditionJobSamavat				,	// �縶��Ʈ // 5050

	// ����
	eNpcConditionBrahma				=	5051,	// ����帶
	eNpcConditionVishunu				,	// �񽴴�
	eNpcConditionSiva					,	// �ù�
	eNpcConditionNaga					,	// ����		
	eNpcConditionAsura					,	// �Ƽ���
	eNpcConditionYaksa					,	// ��ũ��
	eNpcConditionDeva					,	// ����
	eNpcConditionKimnara				,	// Ų����
	eNpcConditionRakshasa				,	// ������
	eNpcConditionGandharva				,	// ���ٸ���
	eNpcConditionGaruda					,	// �����
	// ����
	eNpcConditionLevel10Under		=	5071,	// 10���� �̸�
	eNpcConditionLevel10Over			,	// 10���� �̻�
	eNpcConditionLevel30Under			,	// 30���� �̸�
	eNpcConditionLevel30Over			,	// 30���� �̻�
	eNpcConditionLevel45Under			,	// 45���� �̸�
	eNpcConditionLevel45Over			,	// 45���� �̻�
	eNpcConditionLevel1000Under		=	5100	// 1000���� �̸�
} eNpcCondition;

//---------------------------------------------------
// Quest
//---------------------------------------------------
#define HT_NPC_QUEST_START						6001
#define HT_NPC_QUEST_END						8000

#define HT_NPC_QUEST_PROCESS_START				6001
#define HT_NPC_QUEST_PROCESS_END				6020

#define HT_NPC_QUEST_TUTORIAL_START				6021
#define HT_NPC_QUEST_TUTORIAL_END				6040

#define HT_NPC_QUEST_SCENARIO1_START			6041
#define HT_NPC_QUEST_SCENARIO1_END				6060

#define HT_NPC_QUEST_SCENARIO2_START			6061
#define HT_NPC_QUEST_SCENARIO2_END				6075

#define HT_NPC_QUEST_SCENARIO3_START			6075
#define HT_NPC_QUEST_SCENARIO3_END				6090

#define HT_NPC_QUEST_SCENARIO4_START			6091
#define HT_NPC_QUEST_SCENARIO4_END				6095

typedef enum _eNpcQuest
{
	eNpcQuestNone					=	0,
	// ���� ����
	eNpcQuestStepNone				=	6001, // ����
	eNpcQuestStepStart					, // ����
	eNpcQuestStepProcess				, // ����
	eNpcQuestStepFail					, // ����
	eNpcQuestStepSuccess				, // �Ϸ�
	eNpcQuestStepRejection				, // �ź�
	// ����
	eNpcQuest1st					=	6011, // 1��
	eNpcQuest2nd						, // 2��
	eNpcQuest3rd						, // 3��
	eNpcQuest4th						, // 4��
	eNpcQuest5th						, // 5��
	eNpcQuest6th						, // 6��
	eNpcQuest7th						, // 7��
	eNpcQuest8th						, // 8��
	eNpcQuest9th						, // 9��
	eNpcQuest10th						, // 10��

	// �ʺ���
	eNpcQuestTutorial1				=	6021, // �ʺ���1
	eNpcQuestTutorial2					, // �ʺ���2
	eNpcQuestTutorial3					, // �ʺ���3
	eNpcQuestTutorial4					, // �ʺ���4
	eNpcQuestTutorial5					, // �ʺ���5
	eNpcQuestTutorial6					, // �ʺ���6
	eNpcQuestTutorial7					, // �ʺ���7
	eNpcQuestTutorial8					, // �ʺ���8
	eNpcQuestTutorial9					, // �ʺ���9
	eNpcQuestTutorial10					, // �ʺ���10
	eNpcQuestTutorial0				=	6040, 
	// 1�� �ó�����
	eNpcQuestScenario1				=	6041, // 1�� �ó�����1
	eNpcQuestScenario2					, // 1�� �ó�����2
	eNpcQuestScenario3					, // 1�� �ó�����3
	eNpcQuestScenario4					, // 1�� �ó�����4
	eNpcQuestScenario5					, // 1�� �ó�����5
	eNpcQuestScenario6					, // 1�� �ó�����6
	eNpcQuestScenario7					, // 1�� �ó�����7
	eNpcQuestScenario8					, // 1�� �ó�����8
	eNpcQuestScenario9					, // 1�� �ó�����9
	eNpcQuestScenario10					, // 1�� �ó�����10
	// 2�� �ó�����
	eNpcQuestScenario11				=	6061, // 2�� �ó�����1
	eNpcQuestScenario12					, // 2�� �ó�����2
	eNpcQuestScenario13					, // 2�� �ó�����3
	eNpcQuestScenario14					, // 2�� �ó�����4
	eNpcQuestScenario15					, // 2�� �ó�����5
	eNpcQuestScenario16					, // 2�� �ó�����6
	eNpcQuestScenario17					, // 2�� �ó�����7
	eNpcQuestScenario18					, // 2�� �ó�����8
	eNpcQuestScenario19					, // 2�� �ó�����9
    eNpcQuestScenario20					, // 2�� �ó�����10
	// 2�� ���� ����Ʈ
	eNpcQuestScenario21					, // 2�� ���� ���� ����Ʈ
	eNpcQuestScenario22					, // 2�� ���� - �ı��� ���� 
	eNpcQuestScenario23					, // 2�� ���� - �γ��� ���� 
	eNpcQuestScenario24					, // 2�� ���� - ������ ���� 
	eNpcQuestScenario25					, // 2�� ���� - �Ǹ��� ���� 
	
	// ����
	eNpcQuestScenario26					, // A. ���� �Լ�
	eNpcQuestScenario27					, // B. ø��
	eNpcQuestScenario28					, // C. �ź� ���Ŵ�
	eNpcQuestScenario29					, // D. �����ڰ� �� �ڸŵ�
	eNpcQuestScenario30					, // E. ���ױ�

	// ������
	eNpcQuestScenario31					, // A. ���� ������ �糪��
	eNpcQuestScenario32					, // B. �ǹ� ���� ���
	eNpcQuestScenario33					, // C. ���ڵ��� ���� ���� ���
	eNpcQuestScenario34					, // D. �պ� ���� �׳�
	eNpcQuestScenario35					, // E. ��Ű�� �ڿ� ����ġ�� ��

	// �ϵμ���
	eNpcQuestScenario36					, // A. ������ ����ġ�� �ڵ�
	eNpcQuestScenario37					, // B. ������ ����� ���
	eNpcQuestScenario38					, // C. ���ڵ��� ���� ����
	eNpcQuestScenario39					, // D. �й��� ��ſ��� ���� �����
	eNpcQuestScenario40					, // E. ���� ���� �Ƚ�

	// īŸ��3
	eNpcQuestScenario41					, // A. ���� ������ ����
	eNpcQuestScenario42					, // B. �ƹ����� �Ҿ���� �����
	eNpcQuestScenario43					, // C. ���� ����
	eNpcQuestScenario44					, // D. ������ ����Ű
	eNpcQuestScenario45					, // E. 8���� ����

	eNpcQuestScenario81				=	7001, // ��ũ�� �ʱ�ȭ ����Ʈ 81
	eNpcQuestScenario82					 // ��ų �ʱ�ȭ ����Ʈ 82
} eNpcQuest;

#endif 