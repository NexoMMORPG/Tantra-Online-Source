#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"

#include "HTRentalStore.h"


CHTRentalStore::CHTRentalStore(void)
{
}

CHTRentalStore::~CHTRentalStore(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_RENTALSTORE );
	//g_cUIManager->HT_DeleteWindow( _DIALOG_RENTALSTORE_BLIST );
	//g_cUIManager->HT_DeleteWindow( _DIALOG_RENTALSTORE_SLIST );
	//g_cUIManager->HT_DeleteWindow( _DIALOG_RENTALSTORE_RLIST );
}

HTvoid
CHTRentalStore::HT_vRentalStore_CleanUp()
{
}

HTvoid
CHTRentalStore::HT_vRentalStore_Init()
{
	//	Create Window
	this->HT_vRentalStore_CreateWindow();

	m_iTex = 1;
}

//	Create Window
HTvoid CHTRentalStore::HT_vRentalStore_CreateWindow()
{
	HTint i,j;
	//	[_DIALOG_RENTALSTORE]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_RENTALSTORE, _T(""), 280, 356, g_cRentalStore->HT_vEI_InputCheckForRentalStore, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_RENTALSTORE, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_RENTALSTORE, 0, 8, 2, 36, 1400, 276, 6 );
	//	Texture ���λ���
	g_cUIManager->HT_AddTextureControl( _DIALOG_RENTALSTORE, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_RENTALSTORE, 1, eMsgRentalStoreMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	
	//	Button Ȯ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_RENTALSTORE, 5, 159, 56, 326, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_RENTALSTORE, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 326, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_RENTALSTORE, 5 );
	
	//	Button ���
	g_cUIManager->HT_AddButtonControl( _DIALOG_RENTALSTORE, 6, 159, 157, 326, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_RENTALSTORE, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 157, 326, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_RENTALSTORE, 6 );

	//	Button ���ΰ�ħ
	g_cUIManager->HT_AddButtonControl( _DIALOG_RENTALSTORE, 7, 159, 56, 296, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_RENTALSTORE, 0, eMsgCommonReFresh, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 296, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_RENTALSTORE, 6 );

	//	����
	for( i=0 ; i<7 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_RENTALSTORE, 0, 1, 33+(i*35), 87, 1400, 3, 176 );
	}
	//	����
	for( i=0 ; i<6 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_RENTALSTORE, 0, 2, 33, 87+(i*35), 1400, 212, 3 );
	}
	//	Slot Inven
	for( i=0 ; i<6 ; i++ )
	{
		for( j=0 ; j<5 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_RENTALSTORE, 10+((j*6)+i), 0, 33+(i*35), 87+(j*35) );
			g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_RENTALSTORE, 10+((j*6)+i), HT_TRUE );
		}
	}
}

//	��Ź���� : �ǸŴ� �κ��丮�� ������ Ŭ��, ���Ŵ� ��Ź�������� ������ Ŭ��
void CHTRentalStore::HT_vEI_InputCheckForRentalStore(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	Close Button
		if( iTargetID == -1 || iTargetID == 6 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_RENTALSTORE);
		}
		//	Ȯ��
		else if( iTargetID == 5 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_RENTALSTORE);
		}
		// ���ΰ�ħ (����)
		else if( iTargetID == 7 )
		{
			// � â�� �����ִ��Ŀ� ���� �ٸ��� ����
			switch ( g_cRentalStore->m_nWindowType )
			{
			case 0: // ���� ��Ź ������ ����Ʈ ��û
				g_cRentalStore->HT_EventReqRentalAdminSellInfo();
				break;
			case 1: // �Ǹ����� ������ ����Ʈ ��û
				g_cRentalStore->HT_EventReqRentalBuyList();
				break;
			case 2:	// ��� ������ ����Ʈ ��û
				g_cRentalStore->HT_EventReqRentalAdminReciveList();
				break;
			}
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		unsigned int iWIndex, iCIndex;
		int iTextureId;
		g_cUIManager->HT_GetSlotBoxControlSourInfo( iWIndex, iCIndex, iTextureId );

		//	Rbutton Click�� ��������
		if (iAction == UI_ACTION_MOUSE_L_UP )
		{
			DWORD KeyID = 0;

			if (g_cRentalStore->m_nWindowType == 1)
			{
				// �巡�� �õ��ÿ��� �Ǹ� ���� �ν� ó�� ����
				if (iWIndex == _DIALOG_EQUPINVENTORY )
				{
					KeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_PC, ITEM_LOCATION_PC_BAG1, iCIndex);
				}
				else if (iWIndex == _DIALOG_INVENTORY2 )
				{
					KeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_PC, ITEM_LOCATION_PC_BAG2, iCIndex);
				}

				if (iCIndex >= 100)
				{
					g_cRentalStore->HT_vRentalStore_SelectItemForSell( KeyID, iCIndex );
					//return;
				}
			}
			g_cUIManager->HT_RefuseSlotImageMoving();
		}
		else if( iAction == UI_ACTION_MOUSE_LCLK )
		{ 
			//	���ο� ���
			if( iTargetID == -2 )
			{ 
				g_cUIManager->HT_RefuseSlotImageMoving();
				return;
			}

			// ��Ź������ �ִ� ������ Ŭ���� 
			if (g_cRentalStore->m_nWindowType == 0)	// ���� â ���� ���� ���·� ������
			{
				//�Ǹ� ��� ���
				int tindex = g_cRentalStore->m_wIndex[iTargetID - 10];
				g_cRentalStore->m_iStoreIndex = (tindex / MAX_USERRENTALITEM);
				g_cRentalStore->m_dwIndex = (tindex % MAX_USERRENTALITEM);
				g_cRentalStore->m_dwSelectKeyID = g_cRentalStore->m_iStoreItemKeyID[iTargetID - 10];
				//g_cRentalStore->m_dwSelectKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_RENTALSTORE, ITEM_LOCATION_RENTALSTORE_BAG1, g_cRentalStore->m_dwIndex + 10 );

				CHTString str;
				g_cRentalStore->m_iStore_MsgBoxType = 6;
				g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreQuestionCancel, &str );
				g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, str, UI_MESSAGEBOX_RECONFIRM );
			}
			else if (g_cRentalStore->m_nWindowType == 1)	// ���� â ���� ���� ���·� ������
			{
				// ���� ��Ȯ�� �޽��� �ڽ� ���
				g_cRentalStore->m_dwIndex = iTargetID - 10;
				g_cRentalStore->m_dwSelectKeyID = g_cRentalStore->m_iStoreItemKeyID[g_cRentalStore->m_dwIndex];

				time_t now; time( &now );

				// �ǸŽð��� ���� �������̶�� ���� �Ұ�
				if (g_cRentalStore->ItemList[g_cRentalStore->m_dwIndex].dwTime - now <= 0)
				{
					CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalCannotBuyBecauseTimeOver, &str );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
					return;
				}

				CHTString str;
				g_cRentalStore->m_iStore_MsgBoxType = 5;
				g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreQuestionBuy, &str );
				g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, str, UI_MESSAGEBOX_RECONFIRM );
			}
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		// ���� �Է� â
		if( g_cRentalStore->m_iStore_MsgBoxType == 1 )
		{
			//	X��ư�϶� â �����
           	if( iTargetID == 0 )
			{
				return;
			}
			else// Ȯ�� ��ư
			{
				g_cRentalStore->m_dwMoney = iTargetID;
				g_cRentalStore->HT_vRentalStore_TimeWin_Active();	// �ð� �Է�â ���
			}
		}
		// �ð� �Է� â
		else if( g_cRentalStore->m_iStore_MsgBoxType == 2 )
		{
			//	X��ư�϶� â �����
           	if( iTargetID == 0 )
			{
				return;
			}
			else// Ȯ�� ��ư
			{
				// �ð��� �߸� �Է��ϸ� �����޽��� ���
				if (iTargetID < 0 || iTargetID > 24)
				{
					CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreInputFailed, &str );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
					return;
				}

				g_cRentalStore->m_dwHour = iTargetID;
				// ��Ȯ��â ���
				g_cRentalStore->HT_vRentalStore_TexWin_Active();
			}
		}
		// �ǸŸ� ���� ��Ȯ�� â
		else if( g_cRentalStore->m_iStore_MsgBoxType == 3 )
		{
			//	X��ư�϶� â �����
           	if( iTargetID == 3)
			{
				return;
			}
			else// Ȯ�� ��ư
			{
				// ���� �����ϴٸ� �����޽��� ����� â �ݱ�
				if (g_cRentalStore->m_fTotalTex > g_cEquipInventory->HT_iEquipInventory_GetPCMoney())
				{
					CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgCommonServerMoreRupia, &str );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
					return;
				}
	
				// ������ ��Ź ��û
				g_cRentalStore->HT_RequestRentalItemAdd();
				// ����
				g_cRentalStore->HT_EventReqRentalBuyList();
			}
		}
		// �Ǹŵ� �������� ���� ���Ǿ� ã��
		else if( g_cRentalStore->m_iStore_MsgBoxType == 4 )
		{
			//	X��ư�϶� â �����
           	if( iTargetID == 3)
			{
				return;
			}
			else// Ȯ�� ��ư
			{
				// ������ ���Ǿ� ã�� ��û
				g_cRentalStore->HT_RequestRentalGetMoney(1);
			}
		}
		// �ǸŸ� ���� ��Ȯ�� â
		else if( g_cRentalStore->m_iStore_MsgBoxType == 5 )
		{
			//	X��ư�϶� â �����
           	if( iTargetID == 3)
			{ 
				return;
			}
			else// Ȯ�� ��ư
			{
				//���Ը��
				//g_cRentalStore->m_dwSelectKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_RENTALSTORE, ITEM_LOCATION_RENTALSTORE_BAG1, g_cRentalStore->m_dwIndex + 10 );
				g_cRentalStore->HT_RequestRentalItemBuy();
			}
		}
		// ��Ź���� ������ ���
		else if( g_cRentalStore->m_iStore_MsgBoxType == 6 )
		{
			//	X��ư�϶� â �����
           	if( iTargetID == 3)
			{ 
				return;
			}
			else// Ȯ�� ��ư
			{
				//������ ���
				g_cRentalStore->HT_RequestRentalItemCancel();
			}
		}
		// ���� ���н� �ߴ� Ȯ��â
		else if( g_cRentalStore->m_iStore_MsgBoxType == 7 )
		{
			// ������ ����Ʈ ���û
			g_cRentalStore->HT_EventReqRentalBuyList();
			return;
		}
		// ���� ���� Ȯ��â
		else if( g_cRentalStore->m_iStore_MsgBoxType == 8 )
		{
			//	X��ư�϶� â �����
           	if( iTargetID == 0)
			{ 
				return;
			}
			else// Ȯ�� ��ư
			{
				// ������ �߸� �Է��ϸ� �����޽��� ���
				if (iTargetID < 0 || iTargetID > 7)
				{
					CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreInputFailed, &str );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
					return;
				}

				g_cRentalStore->m_iTex = iTargetID;
				g_cRentalStore->HT_RequestRentalTex(2);
			}
			return;
		}
	}
}

//	Buy List Wnd
void CHTRentalStore::HT_vEI_InputCheckForBuyListWnd(int iAction, int iTarget, int iTargetID)
{
}

// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �Ǹ���Ȳ ����) - 3042 - �ڽ��� ������ �Ǹ���Ȳ ����
HTvoid CHTRentalStore::HT_EventReqRentalAdminSellInfo()
{
	//g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );	// ���� ������ ���� ��û�Ѵ�.
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "��Ź���� ������ ����� ���ϴ�. ��Ź ���� â�� ��ǰ�� Ŭ���ϸ� �ش� ��ǰ ��Ź�� ����� �� �ֽ��ϴ�.");
	HT_RequestRentalTex(1);	// ���� ��ȸ
	HT_vRequestMyRentalItemList();

	g_cNPCControl->HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);
}

// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �����ޱ�) - 3043 - (�������� ������ ã���û ��Ŷ ȣ��)
HTvoid CHTRentalStore::HT_EventReqRentalAdminReciveItem()
{
	CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreMovingItmeMessage1, &str );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
	HT_RequestRentalGetItem();		// <-- ��� �������� ã���ϴ�.
//	g_cUIManager->HT_HideWindow(_DIALOG_RENTALSTORE);
	HT_EventReqRentalAdminReciveList();	// <-- ��� ��Ȳ ���û
}

// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �������� ����Ʈ ����) - 3044 - �����Ȳ ����
HTvoid CHTRentalStore::HT_EventReqRentalAdminReciveList()
{
	//g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );	// ���� ������ ���� ��û�Ѵ�.
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "�Ⱓ�� ���� ��� �������� �ִ��� �˻��մϴ�.");
	m_iBage = 0;
	HT_RequestRentalTex(1);
	HT_RequestRentalStockItemList();

	g_cNPCControl->HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);
}

// ����� ��Ź�Ǹ� �Ϲ��� (�Ǹ����� ������ ��Ϻ���) - 3045 (��Ź����â �˾�) - ���Ը��
HTvoid CHTRentalStore::HT_EventReqRentalBuyList()
{
	//g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );	// ���� ������ ���� ��û�Ѵ�.
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "��Ź���� â�� ��ǰ�� Ŭ���ϸ� ���� �Ͻ� �� �ֽ��ϴ�.");
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "������ ��Ź�� �ڽ��� �κ��丮 ��ǰ�� Ŭ���ϼ���.");
	HT_RequestRentalTex(1);
	HT_RequestRentalItemList(m_iStoreIndex); // _Msg_RentalItemList - �Ǹ� ������ ����Ʈ ���

	g_cNPCControl->HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);
}

// ����� ��Ź�Ǹ� �Ϲ��� (�ڽ��� ������ �Ǹ�) - 3046 (��Ź����â �˾�) - �ǸŸ��
HTvoid CHTRentalStore::HT_EventReqRentalSell()
{
	//g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );	// ���� ������ ���� ��û�Ѵ�.
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "��Ź���� â�� ��ǰ�� Ŭ���ϸ� ���� �Ͻ� �� �ֽ��ϴ�.");
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "������ ��Ź�� �ڽ��� �κ��丮 ��ǰ�� Ŭ���ϼ���.");
	HT_RequestRentalTex(1);
	HT_RequestRentalItemList(m_iStoreIndex); // _Msg_RentalItemList - �Ǹ� ������ ����Ʈ ���

	g_cNPCControl->HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);
}

// ����� ��Ź�Ǹ� �Ϲ��� (��Ź�Ǹ� �̿� ���� ����) - 3047 (��ũ��Ʈ�� ���)
HTvoid CHTRentalStore::HT_EventReqRentalUsingTex()
{ 
	// ���� ���� ��ȸ �� ã��

}

// ����� ��Ź�Ǹ� �Ϲ��� (��Ź�Ǹ� �̿� �������� ã��) - 3049 (��ũ��Ʈ�� ���)
HTvoid CHTRentalStore::HT_EventReqRentalSetTex()
{ 
	// ���� �����ϱ�
	m_iStore_MsgBoxType = 8;
	CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreWantSellTexInput, &str );
	g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, str, UI_MESSAGEBOX_NUMBERINPUT );
}

// ����� ��Ź�Ǹ� ������ (��Ź�Ǹ� ������ ���Ǿ� ����) - 3048 (��ũ��Ʈ�� ���)
HTvoid CHTRentalStore::HT_EventReqRentalItemRupia()
{
	HT_RequestRentalGetMoney(0);	// �ϴ� ��ȸ���� <-- ���Լ��� ���� ��ȸ�ϰ� ã����� �õ��մϴ�.
}

// ��Ź���� ����â ����&�˾�
HTvoid CHTRentalStore::HT_vRentalStore_PopupWindow()
{
	// ��Ź���� Ÿ��Ʋ ����
	CHTString str; 

	if (m_nWindowType == 0)
	{
		g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage, &str );
	}
	else if (m_nWindowType == 1)
	{
		g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage2, &str );
		str.HT_szFormat(str.HT_szGetString(), m_iStoreIndex+1);
	}
	else
	{
		g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage3, &str );
	}
	
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_RENTALSTORE, 1,str);
	g_cUIManager->HT_ShowWindow(_DIALOG_RENTALSTORE);
}

// �κ��丮 Ŭ���� ������ ��Ź�Ǹ� �õ� �Լ�
HTvoid CHTRentalStore::HT_vRentalStore_SelectItemForSell( HTdword dwItemKeyID, int iInvenID )
{
	m_dwIndex = iInvenID;			// �κ��丮 �ε���
	m_dwSelectKeyID = dwItemKeyID;		// Ű���̵�

	// ����Ʈ ���� �������� ������ ������� ���ϰ� �Ѵ�.
	HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwItemIndex <= 0 || CHTParamIDCheck::HT_bIsItemQuestOnly( dwItemIndex ) )
		return;

	HTint iCount = g_cItemSystem->HT_iItemSystem_GetItemCount( dwItemKeyID );
	if( iCount < 0 )
		return;

	CHTString strTemp;
	// �Ϻ� �������� ����ŷ �� �� ����. 2004. 11. 11 ������ 
	if (g_cItemControl->HT_bItemControl_IsItemTimeItem(dwItemIndex) == HT_FALSE)
	{
		// �ð��� �������� �ִ� ��ø������ ���������� �ǸŰ� �����ϵ��� ����
		if (g_cItemSystem->HT_wItemSystem_GetItemMaxPackCount(dwItemKeyID) == iCount)
		{
			HT_vRentalStore_PriceWin_Active();
		}
		else
		{
			HT_g_Script_SetMessage( eMsgExplanPremiumItem01, &strTemp, _T("") );		//	"������� ��ȿ�ð��� ���� �ִ� �����۸� �Ǹ��� �� �ֽ��ϴ�."
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
			return;
		}
	}
	else if (dwItemIndex == 7068 || dwItemIndex == 7070)	// �̺�Ʈ ��Ÿ�� �ϸ�Ÿ
	{
		// �ð��� �������� �ִ� ��ø������ ���������� �ǸŰ� �����ϵ��� ����
		if (g_cItemSystem->HT_wItemSystem_GetItemMaxPackCount(dwItemKeyID) == iCount)
		{
			HT_vRentalStore_PriceWin_Active();
		}
		else
		{
			HT_g_Script_SetMessage( eMsgExplanPremiumItem02, &strTemp, _T("") );		//	"�ּ� �ѹ���(250��) �����θ� �Ǹ��� �� �ֽ��ϴ�"
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
			return;
		}
	}
	else
	{
		m_dwSelectKeyID = dwItemKeyID;
		HT_vRentalStore_PriceWin_Active();
	}
}
//---------���� Ȯ�� �Է� ������ ����--------//
HTvoid 
CHTRentalStore::HT_vRentalStore_TexWin_Active()
{
	m_iStore_MsgBoxType = 3;
	CHTString str;
	DWORD tx;
	
	double dRatio = m_iTex/100.0;
	tx = (DWORD)((m_dwMoney*dRatio)*((m_dwHour/24.0)*1.01-0.01));
	m_fTotalTex = (float)tx;

	if (tx == 0)
	{
		g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage4, &str );
	}
	else
	{
		g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage5, &str );
		str.HT_szFormat(str.HT_szGetString(), int(m_fTotalTex), m_iTex);
	}
	g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, str, UI_MESSAGEBOX_RECONFIRM );
}


//---------���� �Է� ������ ����--------//
HTvoid 
CHTRentalStore::HT_vRentalStore_TimeWin_Active()
{
	m_dwHour = 0;
	m_iStore_MsgBoxType = 2;
	g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, eMsgRentalStoreItemMessage6, UI_MESSAGEBOX_NUMBERINPUT );
	
	// ���� ������ ���̱� ���� �ѹ��� ��û
	HT_RequestRentalTex(1);
}

//---------���� �Է� ������ ����--------//
HTvoid 
CHTRentalStore::HT_vRentalStore_PriceWin_Active()
{
	m_dwMoney = 0;
	m_iStore_MsgBoxType = 1;
	g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, eMsgCommonInputYouWantRuphia, UI_MESSAGEBOX_NUMBERINPUT );

	// ���� ������ ���̱� ���� �ѹ��� ��û
	HT_RequestRentalTex(1);
}

//---------���� ����� ���� �Է� ������ �ް� ���� ������ �ȹ����� ����â ����--------//
HTvoid 
CHTRentalStore::HT_vRentalStore_GetPriceWin_Active()
{
	m_iStore_MsgBoxType = 4;
	
	CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage7, &str );
	str.HT_szFormat(str.HT_szGetString(), m_dwMoney);
	g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, str, UI_MESSAGEBOX_RECONFIRM );
}


// Network Functions
// Request Part
// ���� ��Ź ������ ����Ʈ�� ��û
HTvoid CHTRentalStore::HT_vRequestMyRentalItemList()
{
	Msg_MyRentalItemList* info = new Msg_MyRentalItemList;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_MyRentalItemList ) );

	g_pNetWorkMgr->RequestMyRentalItemList( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MyRentalItemList...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// Ư�� ��Ź������ �����۸���Ʈ ��û
HTvoid CHTRentalStore::HT_RequestRentalItemList(DWORD dwStoreIndex)
{
	Msg_RentalItemList* info = new Msg_RentalItemList;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalItemList ) );

	info->dwStoreIndex = dwStoreIndex;

	g_pNetWorkMgr->RequestRentalItemList( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalItemList...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// �������� ��Ź��
HTvoid CHTRentalStore::HT_RequestRentalItemAdd()
{
	Msg_RentalItemAdd* info = new Msg_RentalItemAdd;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalItemAdd ) );

	info->dwStoreIndex = m_iStoreIndex;
	info->byHour = (BYTE) m_dwHour;
	
	// x, y �� �����Ͽ� �ε��� ���
	if (m_dwIndex < 124)	// ù��° ������ ���
	{
		int x = (m_dwIndex - 100) % MAX_INVEN_X; 
		int y = (m_dwIndex - 100) / MAX_INVEN_X;
		info->dwIndex = y + (x * MAX_INVEN_Y);
	}
	else
	{
		int x = (m_dwIndex - 124) % MAX_INVEN_X; 
		int y = (m_dwIndex - 124) / MAX_INVEN_X;
		info->dwIndex = 24 + y + (x * MAX_INVEN_Y);
	}
	info->dwMoney = m_dwMoney;

	g_pNetWorkMgr->RequestRentalItemAdd( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalItemAdd...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// ��Ź�� �������� ���
HTvoid CHTRentalStore::HT_RequestRentalItemCancel()
{
	Msg_RentalItemCancel* info = new Msg_RentalItemCancel;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalItemCancel ) );

	info->dwStoreIndex = m_iStoreIndex;
	info->dwIndex = m_dwIndex;

	g_pNetWorkMgr->RequestRentalItemCancel( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalItemCancel...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

}

// ����� ���� �� ã��
HTvoid CHTRentalStore::HT_RequestRentalGetMoney(int iType)
{
	Msg_RentalGetMoney* info = new Msg_RentalGetMoney;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalGetMoney ) );

	info->byType = iType;	// 1 = ��ȸ, 2 = ã��

	g_pNetWorkMgr->RequestRentalGetMoney( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalGetMoney...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// ����� �� ��ǰ ã�� (�Ⱓ ���� �����۵�)
HTvoid CHTRentalStore::HT_RequestRentalGetItem()
{
	Msg_RentalGetItem* info = new Msg_RentalGetItem;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalGetItem ) );

	g_pNetWorkMgr->RequestRentalGetItem( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalGetItem...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// ��Ź������ ���� ����
HTvoid CHTRentalStore::HT_RequestRentalTex(int iType)
{
	Msg_SetRentalTex* info = new Msg_SetRentalTex;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_SetRentalTex ) );

	info->byType = iType;

	if (iType == 2)
		info->byTex = m_iTex;

	g_pNetWorkMgr->RequestRentalTex( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalTex...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

}

// ��Ź���� ���ְ� �ݱ�
HTvoid CHTRentalStore::HT_RequestRentalStoreClose()
{/*
	Msg_RentalStoreClose* info = new Msg_RentalStoreClose;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalStoreClose ) );

	g_pNetWorkMgr->RequestRentalStoreClose( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalStoreClose...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
	*/
}

// ��Ź�������� ������ ����
HTvoid CHTRentalStore::HT_RequestRentalItemBuy()
{
	Msg_RentalItemBuy* info = new Msg_RentalItemBuy;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalItemBuy ) );

	info->dwStoreIndex = m_iStoreIndex;
	info->dwIndex = m_dwIndex;

	// ������ ���� �Ǿ ����
	info->stItem = ItemList[ m_dwIndex ].stItem;
	//info->stItem = g_cItemSystem->HT_iGetItemInfo( m_dwSelectKeyID );

	g_pNetWorkMgr->RequestRentalItemBuy( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalItemBuy...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// ������ �������۸���Ʈ�� ��û�Ѵ�.
HTvoid CHTRentalStore::HT_RequestRentalStockItemList()
{ 
	Msg_RentalStockItemList* info = new Msg_RentalStockItemList;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalStockItemList ) );

	g_pNetWorkMgr->RequestRentalStockItemList( info );
	
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalStockItemList...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

}

// Recive Part
// ���� ��Ź ������ ����Ʈ�� ��û ����
HTvoid CHTRentalStore::HT_vRentalStore_SCP_MyRentalItemList( Msg_MyRentalItemList* info )
{
	m_nWindowType = 0;	// ���� â ���� ���� ���·� ����

	HTdword dwItemIndex = 0;
	HTint nXMLID = 0;

	for (int i = 0; i<MAX_USERRENTALITEM; ++i)
	{
		ItemList[i] = info->stItem[i];		// ������ ���� ����
		m_wIndex[i] = info->wIndex[i];		// �ε��� ����

		if( info->stItem[i].stItem.snIndex > 0 )
		{
			// �̹��� ����
			dwItemIndex = HT_ITEM_INDEX_START + info->stItem[i].stItem.snIndex;
			nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );

			PS_SCP_RESP_ITEM_SET item = new S_SCP_RESP_ITEM_SET;
			item->byType = SET_ITEM_CREATE;
			item->byPlace = ITEM_PLACE_RENTALSTORE;
			item->byIndex = i;
			item->sitem.snIndex = info->stItem[i].stItem.snIndex;
			item->sitem.byCount = info->stItem[i].stItem.byCount;
			item->sitem.byRefineLevel = info->stItem[i].stItem.byRefineLevel;
			item->sitem.snDurability = info->stItem[i].stItem.snDurability;

			for(int j = 0 ; j < MAX_SUBMATERIALSIZE ; ++j )
				item->sitem.bySubRefine[j] = info->stItem[i].stItem.bySubRefine[j];

			g_cItemSystem->HT_vItemSystem_ItemSet( item );
			HT_DELETE( item );

			g_cUIManager->HT_SetSlotImage( _DIALOG_RENTALSTORE, _RENTALSTORE_INVEN_BEGIN+i, nXMLID );
			int iKeyID;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_RENTALSTORE, i, iKeyID);
			m_iStoreItemKeyID[i] = iKeyID;
		}
		else
		{
			g_cUIManager->HT_SetSlotImage( _DIALOG_RENTALSTORE, _RENTALSTORE_INVEN_BEGIN+i, 0 );
			m_iStoreItemKeyID[i] = 0;

		}
	}
	HT_vRentalStore_PopupWindow();	// ��Ź����â �����Ͽ� ���
}

// Ư�� ��Ź������ �����۸���Ʈ ��û ����
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalItemList( Msg_RentalItemList* info )
{
	m_nWindowType = 1;	// ���� â ���� ���� ���·� ����

	HTdword dwItemIndex = 0;
	HTint nXMLID = 0;

	for (int i = 0; i<MAX_USERRENTALITEM; ++i)
	{
		ItemList[i] = info->stItem[i];

		if( info->stItem[i].stItem.snIndex > 0 )
		{
			// �̹��� ����
			dwItemIndex = HT_ITEM_INDEX_START + info->stItem[i].stItem.snIndex;
			nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );

			PS_SCP_RESP_ITEM_SET item = new S_SCP_RESP_ITEM_SET;
			item->byType = SET_ITEM_CREATE;
			item->byPlace = ITEM_PLACE_RENTALSTORE;
			item->byIndex = i;
			item->sitem.snIndex = info->stItem[i].stItem.snIndex;
			item->sitem.byCount = info->stItem[i].stItem.byCount;
			item->sitem.byRefineLevel = info->stItem[i].stItem.byRefineLevel;
			item->sitem.snDurability = info->stItem[i].stItem.snDurability;

			for(int j = 0 ; j < MAX_SUBMATERIALSIZE ; ++j )
				item->sitem.bySubRefine[j] = info->stItem[i].stItem.bySubRefine[j];

			g_cItemSystem->HT_vItemSystem_ItemSet( item );
			HT_DELETE( item );

			g_cUIManager->HT_SetSlotImage( _DIALOG_RENTALSTORE, _RENTALSTORE_INVEN_BEGIN+i, nXMLID );
			int iKeyID;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_RENTALSTORE, i, iKeyID);
			m_iStoreItemKeyID[i] = iKeyID;
		}
		else
		{
			g_cUIManager->HT_SetSlotImage( _DIALOG_RENTALSTORE, _RENTALSTORE_INVEN_BEGIN+i, 0 );
			m_iStoreItemKeyID[i] = 0;

		}
	}
	HT_vRentalStore_PopupWindow();	// ��Ź����â �����Ͽ� ���
}

// �������� ��Ź�� ����
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalItemAdd( Msg_RentalItemAdd* info )
{
	// ������
	if (info->byResult == 0)	
	{
		// �ڽ��� �κ��丮 ���� (���Ǿ�)
		g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage8, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);

		// �ڽ��� �κ��丮���� ��Ź�� ������ ����
		g_cItemSystem->HT_vItemSystem_DeleteItem( m_dwSelectKeyID );			// ��ü�� ������ ����
	}
	else
	{
		// ���� �޽��� ���
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage9, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
	}
}

// ��Ź�� �������� ��� ����
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalItemCancel( Msg_RentalItemCancel* info )
{
	// ������
	if (info->byResult == 0)	
	{
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage10, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
		
		// ����Ʈ ���� ��û
		HT_vRequestMyRentalItemList();

		// �ڽ��� �κ��丮���� ��Ź�� ������ ����
		//g_cItemSystem->HT_vItemSystem_DeleteItem( m_dwSelectKeyID );			// ��ü�� ������ ����
	}
	else
	{
		// ���� �޽��� ���
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage11, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
	}
}

// ����� ���� �� ã�� ����
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalGetMoney( Msg_RentalGetMoney* info )
{
	// ��ȸ��
	if (info->byType == 0)	
	{
		m_dwMoney = info->dwMoney;

		if (m_dwMoney <= 0)
		{
			CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage12, &str );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
			return;
		}

		HT_vRentalStore_GetPriceWin_Active();
	}
	else	// ã���
	{
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage13, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
		g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney + g_cEquipInventory->HT_iEquipInventory_GetPCMoney() );
	}
}

// ����� �� ��ǰ ã�� (�Ⱓ ���� �����۵�) ����
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalGetItem( Msg_RentalGetItem* info )
{ 
}

// ��Ź������ ���� ���� ����
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalTex( Msg_SetRentalTex* info )
{
	if (info->byType == 1)	// ��ȸ��
	{ 
		m_iTex = info->byTex;
		// ����� UI �� ����
		CHTString strTemp;
		strTemp.HT_szFormat( " %d %%", m_iTex );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE4, 11, strTemp.HT_szGetString() );
		g_cUIManager->HT_SetScrollBarControl( _DIALOG_SIEGE4, 1, m_iTex );
	}
	else	// ���ý�
	{
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage14, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
		return;
	}
}

// ��Ź���� ���ְ� �ݱ� ����
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalStoreClose( Msg_RentalStoreClose* info )
{ 
}

// ��Ź�������� ������ ���� ����
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalItemBuy( Msg_RentalItemBuy* info )
{
	// ������
	if (info->byResult == 0)	
	{
		// �ڽ��� �κ��丮 ���� (���Ǿ�)
		g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage15, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);

		// ����Ʈ ���� ��û
		HT_RequestRentalItemList(m_iStoreIndex);
	}
	else
	{
		// ���� �޽��� ���
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage16, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);

		m_iStore_MsgBoxType = 7;
		g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, eMsgRentalStoreItemMessage17);

	}
}

// ������ �������۸���Ʈ�� ��û�Ѵ�. ����
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalStockItemList( Msg_RentalStockItemList* info )
{
	m_nWindowType = 2;	// ���� â ���� ���� ���·� ����

	m_iBage++;
	if (m_iBage == 2)
	{
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage18, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
		return;
	}
	else if (m_iBage > 2)
	{
		return;
	}

	HTdword dwItemIndex = 0;
	HTint nXMLID = 0;

	for (int i = 0; i<MAX_USERRENTALITEM; ++i)
	{
		//ItemList[i] = info->stItem[i].stItem;

		if( info->stItem[i].stItem.snIndex > 0 )
		{
			// �̹��� ����
			dwItemIndex = HT_ITEM_INDEX_START + info->stItem[i].stItem.snIndex;
			nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );

			PS_SCP_RESP_ITEM_SET item = new S_SCP_RESP_ITEM_SET;
			item->byType = SET_ITEM_CREATE;
			item->byPlace = ITEM_PLACE_RENTALSTORE;
			item->byIndex = i;
			item->sitem.snIndex = info->stItem[i].stItem.snIndex;
			item->sitem.byCount = info->stItem[i].stItem.byCount;
			item->sitem.byRefineLevel = info->stItem[i].stItem.byRefineLevel;
			item->sitem.snDurability = info->stItem[i].stItem.snDurability;

			for(int j = 0 ; j < MAX_SUBMATERIALSIZE ; ++j )
				item->sitem.bySubRefine[j] = info->stItem[i].stItem.bySubRefine[j];

			g_cItemSystem->HT_vItemSystem_ItemSet( item );
			HT_DELETE( item );

			g_cUIManager->HT_SetSlotImage( _DIALOG_RENTALSTORE, _RENTALSTORE_INVEN_BEGIN+i, nXMLID );
			int iKeyID;
			BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_RENTALSTORE, i, iKeyID);
			m_iStoreItemKeyID[i] = iKeyID;
		}
		else
		{
			g_cUIManager->HT_SetSlotImage( _DIALOG_RENTALSTORE, _RENTALSTORE_INVEN_BEGIN+i, 0 );
			m_iStoreItemKeyID[i] = 0;

		}
	}
	HT_vRentalStore_PopupWindow();	// ��Ź����â �����Ͽ� ���
}

