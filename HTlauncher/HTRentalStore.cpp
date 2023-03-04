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
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_RENTALSTORE, 0, 8, 2, 36, 1400, 276, 6 );
	//	Texture 개인상점
	g_cUIManager->HT_AddTextureControl( _DIALOG_RENTALSTORE, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_RENTALSTORE, 1, eMsgRentalStoreMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_RENTALSTORE, 5, 159, 56, 326, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_RENTALSTORE, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 326, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_RENTALSTORE, 5 );
	
	//	Button 취소
	g_cUIManager->HT_AddButtonControl( _DIALOG_RENTALSTORE, 6, 159, 157, 326, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_RENTALSTORE, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 157, 326, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_RENTALSTORE, 6 );

	//	Button 새로고침
	g_cUIManager->HT_AddButtonControl( _DIALOG_RENTALSTORE, 7, 159, 56, 296, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_RENTALSTORE, 0, eMsgCommonReFresh, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 296, 89, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_RENTALSTORE, 6 );

	//	세로
	for( i=0 ; i<7 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_RENTALSTORE, 0, 1, 33+(i*35), 87, 1400, 3, 176 );
	}
	//	가로
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

//	위탁상점 : 판매는 인벤토리의 아이템 클릭, 구매는 위탁상점내의 아이템 클릭
void CHTRentalStore::HT_vEI_InputCheckForRentalStore(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	Close Button
		if( iTargetID == -1 || iTargetID == 6 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_RENTALSTORE);
		}
		//	확인
		else if( iTargetID == 5 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_RENTALSTORE);
		}
		// 새로고침 (갱신)
		else if( iTargetID == 7 )
		{
			// 어떤 창이 열려있느냐에 따라 다르게 갱신
			switch ( g_cRentalStore->m_nWindowType )
			{
			case 0: // 나의 위탁 아이템 리스트 요청
				g_cRentalStore->HT_EventReqRentalAdminSellInfo();
				break;
			case 1: // 판매중인 아이템 리스트 요청
				g_cRentalStore->HT_EventReqRentalBuyList();
				break;
			case 2:	// 재고 아이템 리스트 요청
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

		//	Rbutton Click이 들어왔을때
		if (iAction == UI_ACTION_MOUSE_L_UP )
		{
			DWORD KeyID = 0;

			if (g_cRentalStore->m_nWindowType == 1)
			{
				// 드래그 시도시에는 판매 모드로 인식 처리 하자
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
			//	윈두우 배경
			if( iTargetID == -2 )
			{ 
				g_cUIManager->HT_RefuseSlotImageMoving();
				return;
			}

			// 위탁상점에 있는 아이템 클릭시 
			if (g_cRentalStore->m_nWindowType == 0)	// 나의 창 정보 보기 상태로 설정시
			{
				//판매 취소 모드
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
			else if (g_cRentalStore->m_nWindowType == 1)	// 나의 창 정보 보기 상태로 설정시
			{
				// 구입 재확인 메시지 박스 띄움
				g_cRentalStore->m_dwIndex = iTargetID - 10;
				g_cRentalStore->m_dwSelectKeyID = g_cRentalStore->m_iStoreItemKeyID[g_cRentalStore->m_dwIndex];

				time_t now; time( &now );

				// 판매시간이 지난 아이템이라면 구입 불가
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
		// 가격 입력 창
		if( g_cRentalStore->m_iStore_MsgBoxType == 1 )
		{
			//	X버튼일때 창 지우기
           	if( iTargetID == 0 )
			{
				return;
			}
			else// 확인 버튼
			{
				g_cRentalStore->m_dwMoney = iTargetID;
				g_cRentalStore->HT_vRentalStore_TimeWin_Active();	// 시간 입력창 띄움
			}
		}
		// 시간 입력 창
		else if( g_cRentalStore->m_iStore_MsgBoxType == 2 )
		{
			//	X버튼일때 창 지우기
           	if( iTargetID == 0 )
			{
				return;
			}
			else// 확인 버튼
			{
				// 시간을 잘못 입력하면 에러메시지 출력
				if (iTargetID < 0 || iTargetID > 24)
				{
					CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreInputFailed, &str );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
					return;
				}

				g_cRentalStore->m_dwHour = iTargetID;
				// 재확인창 띄움
				g_cRentalStore->HT_vRentalStore_TexWin_Active();
			}
		}
		// 판매를 위한 재확인 창
		else if( g_cRentalStore->m_iStore_MsgBoxType == 3 )
		{
			//	X버튼일때 창 지우기
           	if( iTargetID == 3)
			{
				return;
			}
			else// 확인 버튼
			{
				// 돈이 부족하다면 에러메시지 출력후 창 닫기
				if (g_cRentalStore->m_fTotalTex > g_cEquipInventory->HT_iEquipInventory_GetPCMoney())
				{
					CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgCommonServerMoreRupia, &str );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
					return;
				}
	
				// 아이템 위탁 요청
				g_cRentalStore->HT_RequestRentalItemAdd();
				// 갱신
				g_cRentalStore->HT_EventReqRentalBuyList();
			}
		}
		// 판매된 아이템의 적립 루피아 찾기
		else if( g_cRentalStore->m_iStore_MsgBoxType == 4 )
		{
			//	X버튼일때 창 지우기
           	if( iTargetID == 3)
			{
				return;
			}
			else// 확인 버튼
			{
				// 적립된 루피아 찾기 요청
				g_cRentalStore->HT_RequestRentalGetMoney(1);
			}
		}
		// 판매를 위한 재확인 창
		else if( g_cRentalStore->m_iStore_MsgBoxType == 5 )
		{
			//	X버튼일때 창 지우기
           	if( iTargetID == 3)
			{ 
				return;
			}
			else// 확인 버튼
			{
				//구입모드
				//g_cRentalStore->m_dwSelectKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_RENTALSTORE, ITEM_LOCATION_RENTALSTORE_BAG1, g_cRentalStore->m_dwIndex + 10 );
				g_cRentalStore->HT_RequestRentalItemBuy();
			}
		}
		// 위탁중인 아이템 취소
		else if( g_cRentalStore->m_iStore_MsgBoxType == 6 )
		{
			//	X버튼일때 창 지우기
           	if( iTargetID == 3)
			{ 
				return;
			}
			else// 확인 버튼
			{
				//아이템 취소
				g_cRentalStore->HT_RequestRentalItemCancel();
			}
		}
		// 구입 실패시 뜨는 확인창
		else if( g_cRentalStore->m_iStore_MsgBoxType == 7 )
		{
			// 아이템 리스트 재요청
			g_cRentalStore->HT_EventReqRentalBuyList();
			return;
		}
		// 세금 조정 확인창
		else if( g_cRentalStore->m_iStore_MsgBoxType == 8 )
		{
			//	X버튼일때 창 지우기
           	if( iTargetID == 0)
			{ 
				return;
			}
			else// 확인 버튼
			{
				// 세율을 잘못 입력하면 에러메시지 출력
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

// 비류성 위탁판매 관리자 (자신의 아이템 판매현황 보기) - 3042 - 자신의 아이템 판매현황 보기
HTvoid CHTRentalStore::HT_EventReqRentalAdminSellInfo()
{
	//g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );	// 세금 정보를 먼저 요청한다.
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "위탁중인 아이템 목록을 봅니다. 위탁 상점 창의 물품을 클릭하면 해당 물품 위탁을 취소할 수 있습니다.");
	HT_RequestRentalTex(1);	// 세금 조회
	HT_vRequestMyRentalItemList();

	g_cNPCControl->HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);
}

// 비류성 위탁판매 관리자 (자신의 아이템 돌려받기) - 3043 - (보관중인 아이템 찾기요청 패킷 호출)
HTvoid CHTRentalStore::HT_EventReqRentalAdminReciveItem()
{
	CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreMovingItmeMessage1, &str );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
	HT_RequestRentalGetItem();		// <-- 재고 아이템을 찾습니다.
//	g_cUIManager->HT_HideWindow(_DIALOG_RENTALSTORE);
	HT_EventReqRentalAdminReciveList();	// <-- 재고 현황 재요청
}

// 비류성 위탁판매 관리자 (자신의 아이템 돌려받을 리스트 보기) - 3044 - 재고현황 보기
HTvoid CHTRentalStore::HT_EventReqRentalAdminReciveList()
{
	//g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );	// 세금 정보를 먼저 요청한다.
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "기간이 지난 재고 아이템이 있는지 검색합니다.");
	m_iBage = 0;
	HT_RequestRentalTex(1);
	HT_RequestRentalStockItemList();

	g_cNPCControl->HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);
}

// 비류성 위탁판매 일반인 (판매중인 아이템 목록보기) - 3045 (위탁상점창 팝업) - 구입모드
HTvoid CHTRentalStore::HT_EventReqRentalBuyList()
{
	//g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );	// 세금 정보를 먼저 요청한다.
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "위탁상점 창의 물품을 클릭하면 구입 하실 수 있습니다.");
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "아이템 위탁은 자신의 인벤토리 물품을 클릭하세요.");
	HT_RequestRentalTex(1);
	HT_RequestRentalItemList(m_iStoreIndex); // _Msg_RentalItemList - 판매 아이템 리스트 얻기

	g_cNPCControl->HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);
}

// 비류성 위탁판매 일반인 (자신의 아이템 판매) - 3046 (위탁상점창 팝업) - 판매모드
HTvoid CHTRentalStore::HT_EventReqRentalSell()
{
	//g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );	// 세금 정보를 먼저 요청한다.
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "위탁상점 창의 물품을 클릭하면 구입 하실 수 있습니다.");
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, "아이템 위탁은 자신의 인벤토리 물품을 클릭하세요.");
	HT_RequestRentalTex(1);
	HT_RequestRentalItemList(m_iStoreIndex); // _Msg_RentalItemList - 판매 아이템 리스트 얻기

	g_cNPCControl->HT_vNPCControl_PopUpInventory(_DIALOG_EQUPINVENTORY);
}

// 비류성 위탁판매 일반인 (위탁판매 이용 세금 보기) - 3047 (스크립트로 출력)
HTvoid CHTRentalStore::HT_EventReqRentalUsingTex()
{ 
	// 누적 세금 조회 및 찾기

}

// 비류성 위탁판매 일반인 (위탁판매 이용 누적세금 찾기) - 3049 (스크립트로 출력)
HTvoid CHTRentalStore::HT_EventReqRentalSetTex()
{ 
	// 세율 설정하기
	m_iStore_MsgBoxType = 8;
	CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreWantSellTexInput, &str );
	g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, str, UI_MESSAGEBOX_NUMBERINPUT );
}

// 비류성 위탁판매 관리자 (위탁판매 아이템 루피아 보기) - 3048 (스크립트로 출력)
HTvoid CHTRentalStore::HT_EventReqRentalItemRupia()
{
	HT_RequestRentalGetMoney(0);	// 일단 조회부터 <-- 이함수는 돈을 조회하고 찾기까지 시도합니다.
}

// 위탁상점 구매창 갱신&팝업
HTvoid CHTRentalStore::HT_vRentalStore_PopupWindow()
{
	// 위탁상점 타이틀 셋팅
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

// 인벤토리 클릭시 아이템 위탁판매 시도 함수
HTvoid CHTRentalStore::HT_vRentalStore_SelectItemForSell( HTdword dwItemKeyID, int iInvenID )
{
	m_dwIndex = iInvenID;			// 인벤토리 인덱스
	m_dwSelectKeyID = dwItemKeyID;		// 키아이디

	// 퀘스트 전용 아이템은 상점에 등록하지 못하게 한다.
	HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwItemIndex <= 0 || CHTParamIDCheck::HT_bIsItemQuestOnly( dwItemIndex ) )
		return;

	HTint iCount = g_cItemSystem->HT_iItemSystem_GetItemCount( dwItemKeyID );
	if( iCount < 0 )
		return;

	CHTString strTemp;
	// 일부 아이템은 언패킹 할 수 없다. 2004. 11. 11 선영범 
	if (g_cItemControl->HT_bItemControl_IsItemTimeItem(dwItemIndex) == HT_FALSE)
	{
		// 시간제 아이템은 최대 중첩갯수와 같을때만이 판매가 가능하도록 설정
		if (g_cItemSystem->HT_wItemSystem_GetItemMaxPackCount(dwItemKeyID) == iCount)
		{
			HT_vRentalStore_PriceWin_Active();
		}
		else
		{
			HT_g_Script_SetMessage( eMsgExplanPremiumItem01, &strTemp, _T("") );		//	"사용전의 유효시간을 갖고 있는 아이템만 판매할 수 있습니다."
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
			return;
		}
	}
	else if (dwItemIndex == 7068 || dwItemIndex == 7070)	// 이벤트 우타라 암리타
	{
		// 시간제 아이템은 최대 중첩갯수와 같을때만이 판매가 가능하도록 설정
		if (g_cItemSystem->HT_wItemSystem_GetItemMaxPackCount(dwItemKeyID) == iCount)
		{
			HT_vRentalStore_PriceWin_Active();
		}
		else
		{
			HT_g_Script_SetMessage( eMsgExplanPremiumItem02, &strTemp, _T("") );		//	"최소 한묶음(250개) 단위로만 판매할 수 있습니다"
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
//---------최종 확인 입력 윈도우 띄우기--------//
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


//---------개수 입력 윈도우 띄우기--------//
HTvoid 
CHTRentalStore::HT_vRentalStore_TimeWin_Active()
{
	m_dwHour = 0;
	m_iStore_MsgBoxType = 2;
	g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, eMsgRentalStoreItemMessage6, UI_MESSAGEBOX_NUMBERINPUT );
	
	// 세금 오차를 줄이기 위한 한번더 요청
	HT_RequestRentalTex(1);
}

//---------가격 입력 윈도우 띄우기--------//
HTvoid 
CHTRentalStore::HT_vRentalStore_PriceWin_Active()
{
	m_dwMoney = 0;
	m_iStore_MsgBoxType = 1;
	g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, eMsgCommonInputYouWantRuphia, UI_MESSAGEBOX_NUMBERINPUT );

	// 세금 오차를 줄이기 위한 한번더 요청
	HT_RequestRentalTex(1);
}

//---------현재 저장된 가격 입력 윈도우 받고 돈을 받을지 안받을지 결정창 띄우기--------//
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
// 나의 위탁 아이템 리스트를 요청
HTvoid CHTRentalStore::HT_vRequestMyRentalItemList()
{
	Msg_MyRentalItemList* info = new Msg_MyRentalItemList;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_MyRentalItemList ) );

	g_pNetWorkMgr->RequestMyRentalItemList( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MyRentalItemList...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// 특정 위탁상점의 아이템리스트 요청
HTvoid CHTRentalStore::HT_RequestRentalItemList(DWORD dwStoreIndex)
{
	Msg_RentalItemList* info = new Msg_RentalItemList;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalItemList ) );

	info->dwStoreIndex = dwStoreIndex;

	g_pNetWorkMgr->RequestRentalItemList( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalItemList...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// 아이템을 위탁함
HTvoid CHTRentalStore::HT_RequestRentalItemAdd()
{
	Msg_RentalItemAdd* info = new Msg_RentalItemAdd;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalItemAdd ) );

	info->dwStoreIndex = m_iStoreIndex;
	info->byHour = (BYTE) m_dwHour;
	
	// x, y 축 변경하여 인덱스 계산
	if (m_dwIndex < 124)	// 첫번째 슬롯의 경우
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
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalItemAdd...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// 위탁한 아이템을 취소
HTvoid CHTRentalStore::HT_RequestRentalItemCancel()
{
	Msg_RentalItemCancel* info = new Msg_RentalItemCancel;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalItemCancel ) );

	info->dwStoreIndex = m_iStoreIndex;
	info->dwIndex = m_dwIndex;

	g_pNetWorkMgr->RequestRentalItemCancel( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalItemCancel...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

}

// 저장된 나의 돈 찾기
HTvoid CHTRentalStore::HT_RequestRentalGetMoney(int iType)
{
	Msg_RentalGetMoney* info = new Msg_RentalGetMoney;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalGetMoney ) );

	info->byType = iType;	// 1 = 조회, 2 = 찾기

	g_pNetWorkMgr->RequestRentalGetMoney( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalGetMoney...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// 저장된 내 물품 찾기 (기간 지난 아이템들)
HTvoid CHTRentalStore::HT_RequestRentalGetItem()
{
	Msg_RentalGetItem* info = new Msg_RentalGetItem;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalGetItem ) );

	g_pNetWorkMgr->RequestRentalGetItem( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalGetItem...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// 위탁상점의 세율 정함
HTvoid CHTRentalStore::HT_RequestRentalTex(int iType)
{
	Msg_SetRentalTex* info = new Msg_SetRentalTex;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_SetRentalTex ) );

	info->byType = iType;

	if (iType == 2)
		info->byTex = m_iTex;

	g_pNetWorkMgr->RequestRentalTex( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalTex...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

}

// 위탁상점 성주가 닫기
HTvoid CHTRentalStore::HT_RequestRentalStoreClose()
{/*
	Msg_RentalStoreClose* info = new Msg_RentalStoreClose;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalStoreClose ) );

	g_pNetWorkMgr->RequestRentalStoreClose( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalStoreClose...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
	*/
}

// 위탁상점에서 아이템 구입
HTvoid CHTRentalStore::HT_RequestRentalItemBuy()
{
	Msg_RentalItemBuy* info = new Msg_RentalItemBuy;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalItemBuy ) );

	info->dwStoreIndex = m_iStoreIndex;
	info->dwIndex = m_dwIndex;

	// 아이템 정보 실어서 보냄
	info->stItem = ItemList[ m_dwIndex ].stItem;
	//info->stItem = g_cItemSystem->HT_iGetItemInfo( m_dwSelectKeyID );

	g_pNetWorkMgr->RequestRentalItemBuy( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalItemBuy...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// 서버에 재고아이템리스트를 요청한다.
HTvoid CHTRentalStore::HT_RequestRentalStockItemList()
{ 
	Msg_RentalStockItemList* info = new Msg_RentalStockItemList;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_RentalStockItemList ) );

	g_pNetWorkMgr->RequestRentalStockItemList( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_RentalStockItemList...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );

}

// Recive Part
// 나의 위탁 아이템 리스트를 요청 응답
HTvoid CHTRentalStore::HT_vRentalStore_SCP_MyRentalItemList( Msg_MyRentalItemList* info )
{
	m_nWindowType = 0;	// 나의 창 정보 보기 상태로 설정

	HTdword dwItemIndex = 0;
	HTint nXMLID = 0;

	for (int i = 0; i<MAX_USERRENTALITEM; ++i)
	{
		ItemList[i] = info->stItem[i];		// 아이템 정보 저장
		m_wIndex[i] = info->wIndex[i];		// 인덱스 저장

		if( info->stItem[i].stItem.snIndex > 0 )
		{
			// 이미지 갱신
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
	HT_vRentalStore_PopupWindow();	// 위탁상점창 갱신하여 띄움
}

// 특정 위탁상점의 아이템리스트 요청 응답
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalItemList( Msg_RentalItemList* info )
{
	m_nWindowType = 1;	// 상점 창 정보 보기 상태로 설정

	HTdword dwItemIndex = 0;
	HTint nXMLID = 0;

	for (int i = 0; i<MAX_USERRENTALITEM; ++i)
	{
		ItemList[i] = info->stItem[i];

		if( info->stItem[i].stItem.snIndex > 0 )
		{
			// 이미지 갱신
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
	HT_vRentalStore_PopupWindow();	// 위탁상점창 갱신하여 띄움
}

// 아이템을 위탁함 응답
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalItemAdd( Msg_RentalItemAdd* info )
{
	// 성공시
	if (info->byResult == 0)	
	{
		// 자신의 인벤토리 갱신 (루피아)
		g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage8, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);

		// 자신의 인벤토리에서 위탁한 아이템 지움
		g_cItemSystem->HT_vItemSystem_DeleteItem( m_dwSelectKeyID );			// 해체된 아이템 제거
	}
	else
	{
		// 실패 메시지 출력
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage9, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
	}
}

// 위탁한 아이템을 취소 응답
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalItemCancel( Msg_RentalItemCancel* info )
{
	// 성공시
	if (info->byResult == 0)	
	{
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage10, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
		
		// 리스트 갱신 요청
		HT_vRequestMyRentalItemList();

		// 자신의 인벤토리에서 위탁한 아이템 지움
		//g_cItemSystem->HT_vItemSystem_DeleteItem( m_dwSelectKeyID );			// 해체된 아이템 제거
	}
	else
	{
		// 실패 메시지 출력
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage11, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
	}
}

// 저장된 나의 돈 찾기 응답
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalGetMoney( Msg_RentalGetMoney* info )
{
	// 조회시
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
	else	// 찾기시
	{
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage13, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
		g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney + g_cEquipInventory->HT_iEquipInventory_GetPCMoney() );
	}
}

// 저장된 내 물품 찾기 (기간 지난 아이템들) 응답
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalGetItem( Msg_RentalGetItem* info )
{ 
}

// 위탁상점의 세율 정함 응답
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalTex( Msg_SetRentalTex* info )
{
	if (info->byType == 1)	// 조회시
	{ 
		m_iTex = info->byTex;
		// 비류성 UI 쪽 셋팅
		CHTString strTemp;
		strTemp.HT_szFormat( " %d %%", m_iTex );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE4, 11, strTemp.HT_szGetString() );
		g_cUIManager->HT_SetScrollBarControl( _DIALOG_SIEGE4, 1, m_iTex );
	}
	else	// 셋팅시
	{
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage14, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);
		return;
	}
}

// 위탁상점 성주가 닫기 응답
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalStoreClose( Msg_RentalStoreClose* info )
{ 
}

// 위탁상점에서 아이템 구입 응답
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalItemBuy( Msg_RentalItemBuy* info )
{
	// 성공시
	if (info->byResult == 0)	
	{
		// 자신의 인벤토리 갱신 (루피아)
		g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage15, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);

		// 리스트 갱신 요청
		HT_RequestRentalItemList(m_iStoreIndex);
	}
	else
	{
		// 실패 메시지 출력
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgRentalStoreItemMessage16, &str );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, str);

		m_iStore_MsgBoxType = 7;
		g_cUIManager->HT_MessageBox( _DIALOG_RENTALSTORE, eMsgRentalStoreItemMessage17);

	}
}

// 서버에 재고아이템리스트를 요청한다. 응답
HTvoid CHTRentalStore::HT_vRentalStore_SCP_RentalStockItemList( Msg_RentalStockItemList* info )
{
	m_nWindowType = 2;	// 나의 창 정보 보기 상태로 설정

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
			// 이미지 갱신
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
	HT_vRentalStore_PopupWindow();	// 위탁상점창 갱신하여 띄움
}

