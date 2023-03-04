//--------------------------------------------------------------------------------//
// ���� : NPC ���� ���(����, �������, ��ũ��/�������Ʈ Ȯ��, ��ǰ���� ��)
// �ۼ����� / �ۼ��� : 2003.4.21 �輱��
//--------------------------------------------------------------------------------//
#ifndef __HTNPCCONTROL_H__
#define __HTNPCCONTROL_H__

#include "HTNPC.h"

typedef enum _eEconomy_Item
{
	eEconomy_Item_Sword = 0,	// ��
	eEconomy_Item_Dagger ,		// �ܰ� - 2
	eEconomy_Item_Lance,		// â
	eEconomy_Item_Axe,			// ����
	eEconomy_Item_Mace,			// Ÿ�ݹ��� - 6	
	eEconomy_Item_Glove,		// ��������
	eEconomy_Item_Throw,		// ��ô����
	eEconomy_Item_Magic,		// ��������
	eEconomy_Item_Armor = 10,
	eEconomy_Item_Helmet,		// ����
	eEconomy_Item_Boots,		// �Ź�
	eEconomy_Item_Belt,			// ��Ʈ
	eEconomy_Item_Shield,		// ����
	eEconomy_Item_Bracelet,		// ����
	eEconomy_Item_Necklace,		// �����
	eEconomy_Item_Earring,		// �Ͱ���
//	eEconomy_Item_Ring,			// ����
	eEconomy_Item_Etc,
//	eEconomy_Item_Potion,		// ����
	eEconomy_Item_None
} eEconomy_Item;

typedef struct _ECONOMY_ITEM_INFO
{
	HTint				iIndex;
	HTint				iImageID;
	//BYTE				byFriendly;	// ģ�е� ����
	BYTE				byWinIndex;	// �� ��° ����Ʈ â�� �ִ���(â ������ ��������). 0���� ����
	HTint				iXpos;		// ����Ʈ â������ ��ġ
	HTint				iYpos;
	HTint				iWidth;		// ������ ũ��
	HTint				iLength;
	//HTbool			bSelect;	// �������� ���õƴ°�

	_ECONOMY_ITEM_INFO* pNext;
} ECONOMY_ITEM_INFO;

typedef struct _ECONOMY_LIST
{
//	HTint				iCount;		// ����Ʈ�� ��ϵǾ��ִ� ������ ��
	ECONOMY_ITEM_INFO*	pInfoHead;
	ECONOMY_ITEM_INFO*	pInfoTail;
	vector<BYTE>		vWinCount;	// ����Ʈ â�� ������ ����
} ECONOMY_LIST;

// �ŷ��� ���� ������ ����
//typedef struct _HT_TRADE_ITEM
//{
//	DWORD		dwIndex;		// ������ index
//	DWORD		dwKeyID;		// ������ keyID. 
//	HTshort		snPackCount;	// ��ø����
//	BYTE		byState;		// ���/���� ����
//} HT_TRADE_ITEM;
//
//typedef struct _HT_TRADE_LIST
//{
//	DWORD			dwTradeID;		// �ŷ� ID
//	CHTString		szCharName;		// ����� ĳ���� �̸�
//	CHTString		szTitle;		// �ŷ� ����
//	HTint			nRupiah;		// ���ϴ� �ݾ�
//	BYTE			byItemCount;	// ����� ������ ����. �ִ� 3��
//	HT_TRADE_ITEM	sItem[3];
//} HT_TRADE_LIST;

#define LIST_WIDTH 6	// ����Ʈ X ĭ ��
#define LIST_LENGTH 11	// ����Ʈ Y ĭ ��

#define LIST_WIDTH_PRIMIUM	2	// �����̾� ������ X ĭ ��
#define LIST_LENGTH_PRIMIUM	5	// �����̾� ������ Y ĭ ��

//#define PRODUCTION_RUPIAH_EDITBOX		0

//#define ITEM_MAKE_PREV_BUTTON			2
//#define ITEM_MAKE_NEXT_BUTTON			3

class CHTNPCControl
{
public:
	CHTNPCControl();
	~CHTNPCControl();
	
	HTvoid			HT_vNPCControl_Init();
	HTvoid			HT_vNPCControl_CleanUp();

	HTvoid			HT_vNPCControl_Control();

	//-------------------------------------------------------------------
	// â ����/�����
	//-------------------------------------------------------------------
	HTvoid			HT_vNPCControl_Active( DWORD dwNPCIndex/*, DWORD dwKeyID*/);
	// ������ ����Ʈ â
	HTvoid			HT_vNPCControl_ItemListWin_Active();
	// ����â ����
	HTvoid			HT_vNPCControl_ItemWorkWin_Active();
	// �κ��丮 â �˾� : ����/����/��ü�� �������� ��
	HTvoid			HT_vNPCControl_PopUpInventory(HTint nWinIndex);
	// �峳â ����
	HTvoid			HT_vNPCControl_OfferingWin_Active( HTshort sGauge );

	// ĳ���� ��ġüũ_ĳ���� �����̸� â�� �ٿ��Ų��
	HTvoid			HT_vNPCControl_CharPos_Check();
	// ��ȭ���� �ݱ�
	HTvoid			HT_vNPCControl_DialogWin_AntiActive();
	// ����Ʈ���� �ݱ�
	HTvoid			HT_vNPCControl_ListAntiActive();
	// ESCŰ/X��ư�� �������� ����Ʈâ �ݱ�
	HTvoid			HT_vNPCControl_ItemListClose();
	// ESCŰ/X��ư�� �������� ����â �ݱ�
	HTvoid			HT_vNPCControl_ESC_ItemWorkClose();
	// ESC/X��ư�� ���� NPC�κ��丮 ����
	HTvoid			HT_vNPCControl_Inventory_Close();
	// ESCŰ/X��ư�� �������� �峳â �ݱ�
	HTvoid			HT_vNPCControl_ESC_OfferingwinClose();

	//-------------------------------------------------------------------
	// â�� ���� ���콺 �Է� üũ
	//-------------------------------------------------------------------
	//�Ϸ�޼��� â 
	HTRESULT		HT_hrNPCControl_Complete_Message( HTint iProp, HTint iInductNo );
	// ��ȭ���� üũ
	HTvoid			HT_vNPCControl_ButtonCheck_Dialog(HTPoint pPt);
	// ĳ���� ����â���� ���� ��ư Ŭ�� �̺�Ʈ�� ó���Ѵ�
	HTvoid			HT_vNPCControl_IncreaseChakra(HTint iBtnNo);

	//-------------------------------------------------------------------
	// ��ȭ����
	//-------------------------------------------------------------------
	// �����ܰ�� ��ȭ���� ��ȭ �ٲٱ�
	HTvoid			HT_vNPCControl_GetNextStep(HTint nSelNum);
	// ȭ�鿡 ������ ��ȭ ����
	HTvoid			HT_vNPCControl_SetText();
	// ���ǹ��� ������ parameter text����
	HTvoid			HT_vNPCControl_SetParameterText();
	// ���� �ܰ迡�� �ؾ��� ���� ��û ����
	HTvoid			HT_vNPCControl_ServerEvent();
	// ���� �ܰ迡�� �ؾ��� Ŭ���̾�Ʈ �̺�Ʈ
	HTvoid			HT_vNPCControl_ClientEvent();

	//-------------------------------------------------------------------
	// ������ ����
	//-------------------------------------------------------------------
	// shop list �����
	HTvoid			HT_vNPCControl_GetItemList();

	// �����̾� ������ ����Ʈ ����
	HTvoid			HT_vNPCControl_GetPrimiumItemList();

	// �����̾� ���â ����
	HTvoid			HT_vNPCControl_PrimiumItemListWin_Active(HTint iNum, HTint iPage);

	// �����̾� ������ ����Ʈâ ����
	HTdword			HT_vNPCControl_Get_Primium_List_ItemIndex(HTPoint pPt);

	// shop list�� ������ �ֱ�
	HTvoid			HT_vNPCControl_InsertItemInShopList( HTint iIndex );

	// ���� ���콺�� ��ġ�� ����Ʈ�� �ִ� ������ ���� �ִ��� �˻�
	HTint			HT_nNPCControl_ItemListMouseCheck_OnItem( HTint nCol, HTint nRow);
	// �׸� �����
	HTvoid			HT_vNPCControl_ButtonCheck_List_Delete();
	// ���� ���õ� NPC�� ������ ����Ʈ ��Ȱ��ȭ 
	HTvoid			HT_vNPCControl_ButtonCheck_ItemList_AntiActive();
	// ����â ������ ���� ������ ��� �����
	HTvoid			HT_vNPCControl_DeleteWorkItemInfo();
	// ���� �з����� index�� ���� �������� �ִ��� �˻�
	HTbool			HT_bNPCControl_CheckItemIndex(HTint iItemClass, DWORD dwIndex);
	// �������� ���� ��ġ �˻�
	HTbool			HT_bNPCControl_ItemListCheck(HTint iItemClass, BYTE byWinCount, HTint nSellX, 
														HTint nSellY, HTint nItemWidth, HTint nItemLength);
	// ������ ������ ���� ����
	HTvoid			HT_vNPCControl_ItemMakeCount_SetText();
	// ���콺 ����Ʈ�� ��ġ�� �������� ���� ������ ���´�
	HTint			HT_nNPCControl_GetItemInfo(HTint iItemIndex, HT_ITEMINFO& vInfo);

	// ����ȭ �������� ���� ���� ���
	HTint			HT_iNPCControl_CalPurchasingPriceForChargeItem( HTint iItemIndex, HTint iCount );
	// ����ȭ �������� �ּ� ���� ����
	HTint			HT_iNPCControl_GetMinCountForChargeItem( HTint iItemIndex );
	// ����ȭ �������� �������� ���� ����
	HTint			HT_iNPCControl_GetDiscountNumForChargeItem( HTint iItemIndex );
	//-------------------------------------------------------------------
	// ������ ����
	//-------------------------------------------------------------------
	// ������ ���� object�� Ŭ���ߴ��� �˻�
	HTRESULT		HT_hrNPCControl_ClickRefineObject( );
	// ������ ������ Ŭ������ ���
	HTRESULT		HT_hrNPCControl_ItemWork_LButtonClick( DWORD dwItemKeyID );
	// ���� �̹��� �����
	HTvoid			HT_vNPCControl_ButtonCheck_Work_Delete();
	// ���� ��ü ĵ��
	HTvoid			HT_vNPCControl_ButtonCheck_Work_TotalCancel();
	// ���� Ȯ��
	HTvoid			HT_vNPCControl_ButtonCheck_Work_Ok();
	// ������ᰡ ÷�� ������ ������ �˻�
	HTint			HT_nNPCControl_CheckAidItemCondition(CHTString& strName);
	// ����â���� ����� �����ڿ� �����
	HTbool			HT_bNPCControl_CancelSupportResource( DWORD dwItemKeyID );
	// �����ڿ� ä���
	HTbool			HT_bNPCControl_SetAidItemResource( DWORD dwItemKeyID );
	
	// ��ȭ���� �ܰ� �� ���� �������� ��� ���ϱ�
	HTint			HT_iNPCControl_GetMainRefineWarning( HTint iRefineLevel, HTdword dwMainRefineIndex );

	//-------------------------------------------------------------------
	// ����/��ü
	//-------------------------------------------------------------------
	HTvoid			HT_vNPCControl_FixDisjoint_LButtonClick( DWORD dwItemKeyID );
	// ����/��ü�� ������ ���������� �Ӽ��� ���� NPC�� �˻��Ѵ�
	HTbool			HT_bNPCControl_CheckItemAttriForFixDisjoint(DWORD dwItemKeyID);

	//-------------------------------------------------------------------
	// ��ų
	//-------------------------------------------------------------------
	// ��� ����Ʈ�� �ޱ� ���� ������ ��� �ʱ�ȭ
	HTvoid			HT_vNPCControl_SkillList_Delete();
	// ������ ��ų �� ���콺�� Ŭ���� ��ų�� �̸�
	CHTString		HT_szNPCControl_GetSelectSkillName() ;
	// ���� ������ ��ų ����Ʈ ��������
	HTvoid			HT_vNPCControl_GetSkillList();

	//-------------------------------------------------------------------
	// �ֽ� ����/����, �ƽ��� ����, �ƽ��� ��ũ ����/����
	//-------------------------------------------------------------------
	// �ֽ� ���� ���� �˻�
	HTbool			HT_bNPCControl_CheckConditionTrimuritiChange( );
	// �ֽ� ����Ʈ Ȯ�� ���� �˻�
	HTbool			HT_bNPCControl_CheckConditionBrahmanPointRising();

	// �ƽ��� ���� �������� �� 
	HTvoid			HT_vNPCControl_Create_Guild( );
	// ��帶ũ ���� �������� �� 
	HTvoid			HT_vNPCControl_Create_GuildMark( );

	// ��ũ�� �ʱ�ȭ ���� �˻�
	HTbool			HT_bNPCControl_CheckConditionChakraInit();
	// ��ų �ʱ�ȭ ���� �˻�
	HTbool			HT_bNPCControl_CheckConditionSkillInit();
	
	// ���� ��� ���� �˻�
	HTbool			HT_bNPCControl_CheckConditionCoupon();
	// ���� ��Ͽ� ���� �޼���â ����
	HTvoid			HT_vNPCControl_SetCouponNotifyMessage( HTbyte byLevel );
	
	//-------------------------------------------------------------------
	// ����Ȯ�� ���-�峳
	//-------------------------------------------------------------------
	// �峳�� ���� object�� Ŭ���ߴ��� �˻�
	HTRESULT		HT_hrNPCControl_ClickOfferingObject(HTint iNum);
	// �峳�� ������ Ŭ������ ���
	HTvoid			HT_vNPCControl_ButtonCheck_OfferingWin( int iAction, int iTarget, int iTargetID );
	// �峳 ������ �����
	HTvoid			HT_vNPCControl_OfferingItemDeleteAll( );
	HTvoid			HT_vNPCControl_OfferingItemDelete( HTint iPos );
	// �峳 ������ �߰�
	HTvoid			HT_vNPCControl_OfferingItemAdd( DWORD dwItemKeyID );
	// �峳 ��ü ���
	HTvoid			HT_vNPCControl_Offering_Cancel();
 	
	// �峳�� ����
	HTvoid			HT_vNPCControl_Offering_SetRupiah( HTdword dwRupiah );
	// �峳 ������ ����
	HTvoid			HT_vNPCControl_Offering_SetGauge( HTshort sGauge );
	// �峳â�� �ִ� ������ KeyID ���ϱ�
	HTint			HT_iNPCControl_GetKeyIDInOfferingWin( HTint iPos );
	// �峳â �ູ ��ġ ���
	HTint			HT_iNPCControl_CalRefineRateUpConst( );

	//-------------------------------------------------------------------
	// ��ȯ �Լ�
	//-------------------------------------------------------------------
	HTint			HT_iNPCControl_ActiveNPCIndex()	{ return m_iNPCIndex; }
	HTbool			HT_bNPCControl_IsItemMake();
	HTbool			HT_bNPCControl_IsItemWorkActive();
	HTbool			HT_bNPCControl_IsItemFixActive();
	HTbool			HT_bNPCControl_IsItemDisjointActive();
	HTbool			HT_bNPCControl_IsChakraUpStep();
	HTbool			HT_bNPCControl_IsBrahmanUpStep();
	HTbool			HT_bNPCControl_IsRegistLotteryActive();
	HTbool			HT_bNPCControl_IsGuilCreateStep();

	// �޼��� �����찡 Ȱ��ȭ�Ǿ��ִ���
	HTbool			HT_bNPCControl_IsMessageWinActive();
	HTbool			HT_bNPCControl_IsCompleteMsgWinActive();
	HTbool			HT_bNPCControl_IsConfirmMsgWinActive();

	// ������ ���� ��û ����� ������ �ִ���(HT_TRUE) ������(HT_FALSE)
	HTbool			HT_bNPCControl_RequestResult() { return m_bMessage_Error; };
	// ���� �ð�(��/���� ���ִ� �ð�)�� ���´�
	HTfloat			HT_fNPCControl_GetCurTime();

	//	m_nCash�� ���´�.
	HTint			HT_iNPCControl_GetCash() { return m_nCash; };
	HTint			HT_iGetCashNPC(int TabID);

	//-------------------------------------------------------------------
	// �׽�ũ 
	//-------------------------------------------------------------------
	HTbool			HT_bNPCControl_CheckSourceForTaskQuest( HTint iTaskID );

	//////////////////////////////////////////////////////////////////////////////////
	// ��Ʈ��ũ ���� �Լ�
	//////////////////////////////////////////////////////////////////////////////////
	// ������ ����
	HTvoid			HT_vNetWork_CSP_Req_Item_Buy();
	HTvoid			HT_vNetWork_SCP_Resp_Item_Buy( PS_SCP_RESP_ITEM_BUY info );

	// ������ ����
	HTvoid		HT_vNetWork_CSP_REQ_ITEM_REFINING();
	HTvoid		HT_vNetWork_SCP_RESP_ITEM_REFINING( PS_SCP_RESP_ITEM_REFINING );

	// ������ ����
	HTvoid		HT_vNetWork_CSP_REQ_ITEM_REPAIR();
	HTvoid		HT_vNetWork_SCP_RESP_ITEM_REPAIR( PS_SCP_RESP_ITEM_REPAIR );

	// ������ �Ǹ�
	HTvoid			HT_vNetWork_CSP_Req_Item_Sell();
	HTvoid			HT_vNetWork_SCP_Resp_Item_Sell( PS_SCP_RESP_ITEM_SELL info );

	// ��ũ�� ����Ʈ Ȯ��
	HTvoid      HT_vNetWork_CSP_REQ_Increase_Chakra();

	// ������ ��ũ�� ��й� ��û
	HTvoid		HT_vNetWork_SCP_Resp_ChangeChakraToPrana(PS_SCP_RESP_CHANGE_CKAKRA_TO_PRANA info);
	
	// ���� ��� ����� ���
	HTvoid		HT_vNetWork_RegistLottery(BYTE byResult, DWORD dwKeyID = 0 );

	// ��ġ ����
	HTvoid		HT_vNetWork_SCP_Resp_SavePosition( PS_RESULT info );

	// PVP ���� ����Ʈ ��û
	HTvoid		HT_vNetWork_SCP_Resp_PVP_Rank();

	// �ֽ� ����
	HTvoid		HT_vNetWork_CSP_Req_Select_Trimuriti(BYTE byType);
	HTvoid		HT_vNetWork_SCP_Resp_Select_Trimuriti( MSG_TrimuritySelect* info );

	// �ֽ� ����Ʈ Ȯ��
	HTvoid		HT_vNetWork_SCP_Resp_Rising_Brahman( MSG_TrimurityPoint* info );

	// ����
	HTvoid		HT_vNetWork_CSP_REQ_Change_Job( );
	HTvoid		HT_vNetwork_SCP_Resp_Change_Job(MSG_CLASS* info);

	// ���� �峳 ��ġ ��û ���
	HTvoid		HT_vNetWork_SCP_Resp_RefineScale( MSG_RefineScale* info );

	// �峳 ��û
	HTvoid		HT_vNetWork_CSP_Req_ItemOffering();
	HTvoid		HT_vNetWork_CSP_Req_RupiahOffering(HTint nRupiah);
	HTvoid		HT_vNetWork_SCP_Resp_ItemOffering( MSG_ItemContribution* info );

	// �׽�ũ ��û
	HTvoid		HT_vNetWork_CSP_Req_TaskQuest( HTint iTaskQuest );
	HTvoid		HT_vNetWork_SCP_Resp_TaskQuest( MSG_STANDARDPARM* info );
	
	// ĳ�� ���� ���
	HTvoid			HT_vNetWork_CSP_Req_Item_Cash();
	HTvoid			HT_vNetWork_SCP_Resp_Item_Cash( Msg_Cash* info );

	// ��ũ��/��ų �ʱ�ȭ ���� ���
	HTvoid			HT_vNetWork_CSP_Req_CharacterInitialize(HTint iCommand = 2, HTint iType = 0);
	HTvoid			HT_vNetWork_SCP_Resp_Item_CharacterInitialize( Msg_NPCCommand* info );
	
	
	// ��ɼ� ����ȭ ������ ��û
	HTvoid			HT_vNetWork_CSP_Resp_Charge_Function_Item( HTdword dwItemIndex );
	HTvoid			HT_vNetWork_SCP_Resp_Charge_Function_Item( Msg_Time* info );

private:
	HTvoid			HT_vNPCControl_SetMessage( HTint idMessage );
	HTvoid			HT_vNPCControl_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );
	// �׽�ũ ����Ʈ �ҽ� �˻�
	HTbool			HT_bNPCControl_CheckSourceForTaskQuest( HTbyte byType, HTshort sItemID, HTint iSourceCount );
	// 2�� ������ ������ �˻�
	HTint			HT_iNPCControl_CheckItemForChangeJob2();
	//-------------------------------------------------------------------
	// �������� ����
	//-------------------------------------------------------------------
	// �������� ���� ����
	HTvoid			HT_vNPCControl_ActiveChaturangaBoard();
	typedef enum _eChaturangaSquad
	{
		eChaturangaNorth = 0,
		eChaturangaSouth,
		eChaturangaCavalry,
		eChaturangaTank,
		eChaturangaCorporal,
		eChaturangaStaff
	} eChaturangaSquad;

	// �������� ���忡 �� ǥ���ϱ�
	HTvoid			HT_vNPCControl_SetChaturangaPiece( eChaturangaSquad eSquad );

public:
	HTbool					m_bNPCActive;
	//---------ĳ���� ��ġ�� ������ ����---------//
	HTPoint					m_pCharPos_Memory;

	//---------- ���� â�� ���� ���� --------------//
	HTint					m_iResent;				// ���� ���� 1:��ȭ����,2:����Ʈ,3:����,4:����,5:��ü
	BYTE					m_byResent_ServerMsg;	// ���� ���� ��û/��� �޼���

	//---------- ������ ���� ���� ���� ------------//
	eEconomy_Item			m_iEconomy_Resent_Item;			//  ���� ��Ÿ�� ������ �з�.
	BYTE					m_byEconomy_Resent_WinIndex;	//  ���� �����ְ� �ִ� ����Ʈ â�� index
	eEconomy_Item			m_iEconomy_NPC;					//  ���� ���õ� NPC(:�Ź� ������ NPC�� �ε����� �����ϱ� �����Ƽ�)
	
	HTint					m_iWorkItemCount;				// ������ ������ ����
	HTint					m_iWorkItemMinCount;			// �ּ� ���԰���
	DWORD					m_dwBuyItem;					// ������ ������ �ε���
	
	CHTString				m_szLottoryNum;					// only event 

	//---------�ƾ��� ���ÿ� ������ ����---------//
	DWORD					m_dwWorkItem;					// ������ ������ �ε���/KeyID
	HT_ITEMINFO				m_vItemInfo;
	
	HTint					m_nEconomy_Work_LimitRupiah;	// �ʿ��� ��
	HTint					m_nEconomy_Work_ResRupiah;		// ���� ������ �ִ� �� (���Ǿ�)
	HTint					m_nCash;						// ���� ������ �ִ� �� (ĳ��)
	HTint					m_nItemCost;					// ������ ������ �⺻ ����
	DWORD					m_nEconomy_Work_SubItemIndex;

	DWORD					m_nEconomy_Work_SubItemKeyID[5];

	//---------�ƾ��� ����/��ü�� ������ ����---------//
	DWORD					m_dwFixDisjointKeyID;	// ����/��ü�� ������ KeyID
	HTint					m_iSpendMoney;			// ����/��ü�� �����/���� ��-Message�� ����ϱ� ���� ����
	BYTE					m_bySelectPart;			// ������ ��ũ��, �ֽ�

	//--------- NPC Dialogâ�� ǥ���� ���� ���� ----------//
	HTint					m_iNPCIndex;		//  ���� NPC�� ���� �ε���

	CHTString				m_szNPCName;			// NPC �̸�
	DWORD					m_dwNeedValue;			// �ʿ��� ����, ���� ĳ�� ��
	CHTString				m_szName;
	HTtchar					m_szQuestion[1000];
	
	HTbyte					m_byParameter;
	HTint					m_nSelectCount;		// ���ù� ����

	HTbool					m_bNextStepByClientEvent; // Ŭ���̾�Ʈ �̺�Ʈ�� ���ؼ� ���� �ܰ�� �Ѿ����..
	HTint					m_Question;

	//--------- �޼��� â�� ���� ���� -------------//
	BYTE					m_byMessageWin;			//  ���� �޼���â
	HTbool					m_bMessage_Error;		//  ���� �޼���â�� ������ ���и޼��� ����..
	CHTString				m_szMessage;			//  ���� �޼���â�� ������ ����
	CHTString				m_szObjectName;			//	�޼����� �����ֱ� ���� Ư�� object �̸�

	//---------- ���� ������ ������ ����Ʈ ���� ------------//
	ECONOMY_LIST			m_Economy_List[8];				// ���� ������ ������ ����

	HTint					m_iMerchantNo;

	HTint					m_iDurgaReceiptofMoney;			// ����� �����ݾ�

	//-------------------------------------------------------------------
	// ��ų
	//-------------------------------------------------------------------
	// ���� ������ ��ų ����Ʈ ����
	HTint					m_nSkillList_Count;			// ���氡���� ��ų ����
	HTint					m_nSkillList_Index[50];		// ���氡���� ��ų �ε���
	CHTString				m_szSkillList_Name[50];		// ���� ������ ��ų�� �̸�
	HTint					m_nSkillList_Type[50];		// ��ų�� ����

	// ��ų ��� �ε���
	DWORD					m_dwSkillRegistIndex;
	BYTE					m_dwSkillRegistType;

	// ��ų/���� ��й� �̺�Ʈ
	HTint					m_nCommand;			// ��й� (��ų=1/��ũ��=2) ���ÿ���
	HTint					m_nType;			// ��й� ��� ���� (0 = ó���ƴ�, 1 = ó��)
	BYTE					m_nFirst;
	BYTE					m_nFirst2;
	HTint					m_nResult;
	HTint					m_nLevel;
	HTint					m_nRupia;
	DWORD					m_nNowRupia;
	DWORD					m_nNeedRupia;

	//-------------------------------------------------------------------
	// �峳 - ����Ȯ�� ��� �۾�
	//-------------------------------------------------------------------
	HTshort					m_sRefineRateGauge;
	HTfloat					m_fGaugeTimer;
	HTint					m_iOfferingItemKeyID[MAX_ITEM_CONTRIBUTION]; // ������ Ű���̵�
	HTint					m_iOfferingItemPlace[MAX_ITEM_CONTRIBUTION]; // ������ ��ġ
	HTbyte					m_byOfferingItemNum;
	HTbool					m_bPress_OK_Button;
	HTdword					m_dwOfferingRupiah;
	HTint					m_nOfferingObjectNumber;
	HTint					m_nOfferingDialogNumber;


	//-------------------------------------------------------------------
	// �׽�ũ 
	//-------------------------------------------------------------------
	HTint					m_iTaskQuestID;
	HTint					m_iQuestQuizCount; // ���� ��ȣ
	HTint					m_iEventItem;	// �̺�Ʈ ������ ���� ����

	// �����̾� ������ ������ ����
	HTint					m_PrimiumItem[5][30];	// 0 = ��Ű��, 1 = ���ݷ�, 2 = ����, 3 = ���Ǽ�, 4 = Ư����
	HTint					m_iMaxPage;
	HTint					m_iNowPage;
	//HTbool					m_bPrimium_Button;		// �����̾� ��ư�� �������� ���� �Ǵ� 

	//-------------------------------------------------------------------
	// �ֽź��� ���
	//-------------------------------------------------------------------
	HTfloat					HT_bNPCControl_CheckTrimuritiChangeCost();	// �ֽź��� ���˻�

	HTint					m_snBrahmaCount;	// ����帶 
	HTint					m_snVishnuCount;	// �񽴴�
	HTint					m_snSivaCount;		// �ù�
	HTbool					m_bTrimutiri;		// �ֽ� �������� ��ȸ���� ����

private:
	CHTTimer*				m_pTimer;
};

#endif
