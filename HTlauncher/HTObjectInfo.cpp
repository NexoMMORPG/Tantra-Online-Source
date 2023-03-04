#include "stdafx.h"
#include "htobjectinfo.h"
#include "HTextern.h"
#include "HTEngineHandler.h"

#include <vector>

typedef std::vector<HT_ITEM_DATA*>::iterator vector_It;
typedef std::vector<HT_ITEM_EXPANSION_DATA*>::iterator vector_exp_It;

#define HT_ITEMINFO_DESC_MIN_WIDTH	120 // 설명을 위한 아이템 정보창 최소 크기
#define HT_ITEMINFO_EXTRA_SIZE		20	// 아이템 정보창 여분 크기
#define HT_ITEMINFO_TEXT_SPACE		15	// 현재 폰트 크기가 12(2004.01.20)

#define HT_ITEMINFO_WIDTH_TIMES_CONST		6 // 아이템 정보창의 넓이 보정을 위해 곱해주는 수
#define HT_ITEMINFO_HEIGHT_TIMES_CONST		15 // 아이템 정보창의 높이 보정을 위해 곱해주는 수

HTObjectInfo::HTObjectInfo(void) 
{
}

HTObjectInfo::~HTObjectInfo(void)
{
}

//변수 초기화, 그림 로딩
HTvoid HTObjectInfo::HT_vObjectInfo_Init()
{
	m_iRenderType		= eInfo_None;
	m_bInfoWinImageSw	= HT_FALSE;
	m_iInfoWinImageID	= -1;
}

HTvoid HTObjectInfo::HT_vObjectInfo_InfoCheck(unsigned int iIndex, unsigned int iCIndex )
{
	HTPoint pPt;
	pPt.x = 0; pPt.y = 0;

	nWindowIndex = iIndex;
	nControlIndex = iCIndex;

	HT_vObjectInfo_Active(pPt);
}

//	마우스 포인트를 체크
HTvoid HTObjectInfo::HT_vObjectInfo_MousePtCheck( HTPoint pPt )
{
	HT_vObjectInfo_Active(pPt);
}

// 데이터 모두 지우기
HTvoid HTObjectInfo::HT_vObjectInfo_DeleteAll()
{
	m_stItemInfo.strName.str.HT_hrCleanUp();
	m_stItemInfo.strDescription.str.HT_hrCleanUp();

	vector_It it;
	vector_exp_It exp_it;

	if(m_stItemInfo.vLimitStr.size() > 0)
	{
		it = m_stItemInfo.vLimitStr.begin();
		while ( it != m_stItemInfo.vLimitStr.end() )
		{
			HT_DELETE( *it );
			it = m_stItemInfo.vLimitStr.erase( it );
		}
	}
	
	if(m_stItemInfo.vSourceStr.size() > 0)
	{
		it = m_stItemInfo.vSourceStr.begin();
		while ( it != m_stItemInfo.vSourceStr.end() )
		{
			HT_DELETE( *it );
			it = m_stItemInfo.vSourceStr.erase( it );
		}
	}
	
	if( m_stItemInfo.vAttributeStr.size() > 0)
	{
		exp_it = m_stItemInfo.vAttributeStr.begin();
		while ( exp_it != m_stItemInfo.vAttributeStr.end() )
		{
			HT_DELETE( *exp_it );
			exp_it = m_stItemInfo.vAttributeStr.erase( exp_it );
		}
	}

	if(m_vFixDisjointInfo.size() > 0)
	{
		it = m_vFixDisjointInfo.begin();
		while ( it != m_vFixDisjointInfo.end() )
		{
			HT_DELETE( *it );
			it = m_vFixDisjointInfo.erase( it );
		}
	}
	m_bFixDisjointPossible = HT_TRUE;	// 수리/해체 가능한지

	// 스킬 정보
	m_stSkillInfo.strName.str.HT_hrCleanUp();

	if(m_stSkillInfo.vLimitStr.size() > 0)
	{
		it = m_stSkillInfo.vLimitStr.begin();
		while ( it != m_stSkillInfo.vLimitStr.end() )
		{
			HT_DELETE( *it );
			it = m_stSkillInfo.vLimitStr.erase( it );
		}
	}
	
	if(m_stSkillInfo.vSourceStr.size() > 0)
	{
		it = m_stSkillInfo.vSourceStr.begin();
		while ( it != m_stSkillInfo.vSourceStr.end() )
		{
			HT_DELETE( *it );
			it = m_stSkillInfo.vSourceStr.erase( it );
		}
	}

	if( m_stSkillInfo.vAttributeStr.size() > 0)
	{
		exp_it = m_stSkillInfo.vAttributeStr.begin();
		while ( exp_it != m_stSkillInfo.vAttributeStr.end() )
		{
			HT_DELETE( *exp_it );
			exp_it = m_stSkillInfo.vAttributeStr.erase( exp_it );
		}
	}

	if( m_vSkillNextInfo.size() > 0 )
	{
		it = m_vSkillNextInfo.begin();
		while ( it != m_vSkillNextInfo.end() )
		{
			HT_DELETE( *it );
			it = m_vSkillNextInfo.erase( it );
		}
	}
}

// 마우스 오버시 몬스터 NPC 등의 캐릭터 이름 출력을 위한 함수
HTvoid HTObjectInfo::HT_vObjectInfo_Active_NPC(int iObjID)
{
	HTvector3 vecObjPos;
	
	m_dwObjectModelID = iObjID;
	m_iRenderType = eInfo_Character;


	// 몬스터 리스트에서 검색
	m_szName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromModelID( m_dwObjectModelID );
	if(m_szName.HT_nGetSize() > 0 )
	{
		HTint iUserKeyId = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyIDFromName( m_szName.HT_szGetString() );
		if( SERVEROBJECT_IS_CHARACTER( iUserKeyId ) )
		{
			HTint iTrimuriti = g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTrimuriti( iUserKeyId );
			if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) &&
				g_oMainCharacterInfo.byTrimuriti != iTrimuriti )
			{
				m_szName.HT_hrCleanUp();
				m_szName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetAshiramNameFromKeyID(iUserKeyId);
				m_szName += " ";
				m_szName += g_cOtherObjectSystem->HT_strOtherObjectSystem_GetCastNameFromKeyID(iUserKeyId);
			}
		}

		vecObjPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCoordPosFromModelID( m_dwObjectModelID );
		vecObjPos.y += 20;
		m_iRenderType = eInfo_Monster;
	}

	// 몬스터 리스트에 없을 경우 NPC 리스트에서 검색
	if(m_szName.HT_nGetSize() == 0 )
	{
		g_sNPCSystem->HT_vNPCSystem_GetNameForModelID( m_dwObjectModelID, m_szName);

		if(m_szName.HT_nGetSize() > 0)
		{
			m_iRenderType = eInfo_NPC;
			vecObjPos = g_sNPCSystem->HT_vNPCSystem_GetCoordFromModelID( m_dwObjectModelID );
			vecObjPos.y += 20;
		}
	}

	m_ptWinSize.x = m_szName.HT_nGetSize()*(HT_ITEMINFO_WIDTH_TIMES_CONST+1);
	if(m_szName.HT_nGetSize())
		m_ptWinSize.y = HT_ITEMINFO_HEIGHT_TIMES_CONST;
	
	g_cUIManager->iRenderNPCPos = vecObjPos;
	g_cUIManager->strRenderNPCName = m_szName;
	//g_pEngineHandler->HT_hrRenderText(HT_FONT_GULIM_12, m_szName.HT_szGetString(), HTvector3(vecObjPos.x, vecObjPos.y, vecObjPos.z), HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR( 0.1f, 0.1f, 0.1f, 0.8f ), 5.0f );
}



//	정보창을 활성화 시켜줌
HTvoid HTObjectInfo::HT_vObjectInfo_Active( HTPoint pPt )
{
	m_ptWinSize.x = m_ptWinSize.y = 0;
		
	HTvector3 vecObjPos;		// 캐릭터/몬스터 위치
	HTint nAddSizeY = 0;

	HT_vObjectInfo_DeleteAll();	// 초기화

	// 마우스가 위치한 창 번호 알아오기
//	unsigned int nWindowIndex = 0, nControlIndex = 0;
//	int TextureID = 0;
//	g_cUIManager->HT_GetSlotBoxControlSourInfo(nWindowIndex, nControlIndex, TextureID);
	
	m_dwObjectKeyID = 1;
	m_iEconomy_ItemIndex = 1;

	switch(nWindowIndex)
	{
	case _DIALOG_CHARITYWND1 :	// 축복의 신로 (만다라)
	case _DIALOG_CHARITYWND2 :	// 축복의 신로 (쿠루마)
			m_dwObjectKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_OFFERING, ITEM_LOCATION_OFFERING_ITEM, nControlIndex);
			m_iRenderType = eInfo_Item;
			break;
	case _DIALOG_GOODSKEEPWND:		// 창고창
			m_dwObjectKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_NPC, ITEM_LOCATION_NPC_ITEMSAVED, nControlIndex);
			m_iRenderType = eInfo_Item;
			break;
	case _DIALOG_ASHRAMCAGO:		// 창고창
			m_dwObjectKeyID = g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_ASHRAMCARGO, ITEM_LOCATION_ASHRAMCARGO_BAG1, nControlIndex);
			m_iRenderType = eInfo_Item;
			break;
	case _DIALOG_TRADEWND:			// 교환창
			m_dwObjectKeyID = g_cExchangeSystem->HT_iExchange_GetKeyIDMyTradeItem(nControlIndex);
			m_iRenderType = eInfo_Item;
			break;
	case _DIALOG_INDIVIDUALWND1:	// 개인상점 판매창
			m_dwObjectKeyID = g_cIndividualStore->HT_iIndividualStore_GetKeyIDInSellWin( nControlIndex );
			m_iRenderType = eInfo_Item_Store_Sell; 
			break;
	case _DIALOG_INDIVIDUALWND2:	// 개인상점 구매창
			m_dwObjectKeyID = g_cIndividualStore->HT_iIndividualStore_GetKeyIDInBuyWin( nControlIndex );
			m_iRenderType = eInfo_Item_Store_Buy;
			break;
	case _DIALOG_RENTALSTORE:		// 위탁상점창
			if (nControlIndex > _RENTALSTORE_INVEN_END) return;
			m_dwObjectKeyID = g_cRentalStore->m_iStoreItemKeyID[nControlIndex-_RENTALSTORE_INVEN_BEGIN];
			m_iRenderType = eInfo_Item_RentalStore; 
			break;
	case _DIALOG_EQUPINVENTORY:		// 인벤토리의 경우
	case _DIALOG_INVENTORY2:	// 인벤토리2의 경우

		//	양손 무기일경우에 인덱스를 오른손으로 바꿔준다.
		if( CHTParamIDCheck::HT_bIsItemWeaponTwoHand( g_cItemSystem->HT_dwSystem_GetItemIndex( g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(7) ) ) &&
			nControlIndex == 15 )
		{
			m_dwObjectKeyID = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(7);
		}
		else
		{
			m_dwObjectKeyID = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(nControlIndex);
		}
		
		if (g_cNPCControl->HT_bNPCControl_IsItemFixActive() )
			m_iRenderType = eInfo_Item_Fix;
		else if (g_cNPCControl->HT_bNPCControl_IsItemDisjointActive())
			m_iRenderType = eInfo_Item_Disjoint;
		else if (g_cUIManager->HT_isShowWindow(_DIALOG_REFINE) == true) // 제련중이라면 정보는 제련에 맞는 정보를 출력해준다.
			m_iRenderType = eInfo_Item_Work;
		else
			m_iRenderType = eInfo_Item;

		if (g_cUIManager->HT_isShowWindow(UI_WINDOW_MERCHANT) == true)
		{
			m_iRenderType = eInfo_Item_Store_Sell;
		}
		break;
	case _DIALOG_REFINE:
		if (nControlIndex == 1)
		{
			m_dwObjectKeyID = g_cNPCControl->m_dwWorkItem;
			m_iRenderType = eInfo_Item_Work;
			break;
		}
		else
		{
			m_dwObjectKeyID = 0;
			m_iRenderType = eInfo_Item_Work;
			break;
		}
	case UI_WINDOW_MERCHANT: // 상점창
        m_iRenderType = eInfo_Item_Economy;
		m_iEconomy_ItemIndex = g_cUIMerchantWindow->m_ItemIndex[nControlIndex];
		break;
	case _DIALOG_MERCHANT_PREMIUM: // 프리미엄창
		m_iRenderType = eInfo_Item_Economy;	
		g_cNPCControl->m_iNPCIndex = 1263;
		if (nControlIndex - 200 + g_cUIMerchantWindow->m_iScrollValue > 30) return;
		m_iEconomy_ItemIndex = g_cNPCControl->m_PrimiumItem[g_cUIMerchantWindow->m_iTabNo][nControlIndex - 200 + g_cUIMerchantWindow->m_iScrollValue];
		break;
	case _DIALOG_SKILL:	// 스킬창
		m_iRenderType = eInfo_Skill;
		m_dwObjectKeyID = g_cUISkillWindow->HT_vGetSkillIndex(nControlIndex);
		break;
	case _DIALOG_HQUICKSLOT: // 퀵슬롯창 (새로)
	case _DIALOG_WQUICKSLOT: // 퀵슬롯창 (가로)
		{
			int piKeyID;
			byte pbyType;
			g_cQuickSlot->HT_vQuickSlot_GetKeyIDInSlot( nControlIndex, &piKeyID, &pbyType);
			switch ((int)pbyType)
			{
			case _QUICKSLOT_TYPE_ITEM:
				m_dwObjectKeyID = piKeyID;
				m_iRenderType = eInfo_Item;
				break;
			case _QUICKSLOT_TYPE_SKILL:
				m_iRenderType = eInfo_Skill;
				m_dwObjectKeyID = piKeyID;
				break;
			case _QUICKSLOT_TYPE_NONE:
			case _QUICKSLOT_TYPE_COMMAND:
			default:
				m_dwObjectKeyID = 0;
				break;
			}
		}
		break;
	default:
		m_dwObjectKeyID = 0;
		break;
	}

	if (m_dwObjectKeyID <= 0 || m_iEconomy_ItemIndex <= 0)	// 빈슬롯은 창을 띄우면 안된다.
	{
		g_cUIManager->HT_SetSlotBoxControlTextIndex(nWindowIndex, nControlIndex, 0);
		return;
	}
	if(m_iRenderType == eInfo_Item || m_iRenderType == eInfo_Item_Work || m_iRenderType == eInfo_Item_RentalStore 
		|| m_iRenderType == eInfo_Item_Store_Sell || m_iRenderType == eInfo_Item_Store_Buy )
	{
		// 아이템 정보 가져오기
		if( m_iRenderType == eInfo_Item )
		{
			m_ptWinSize.x = g_cItemSystem->HT_iGetItemInfo(m_dwObjectKeyID, m_stItemInfo); 
		}
		// 판매창 아이템 || 구매창의 판매 아이템
		else if( m_iRenderType == eInfo_Item_Store_Sell || m_iRenderType == eInfo_Item_Store_Buy )
			m_ptWinSize.x = g_cItemSystem->HT_iGetItemInfo( m_dwObjectKeyID, m_stItemInfo, NPC_ITEM_SELL );
		else if( m_iRenderType == eInfo_Item_RentalStore )	// 위탁상점 처리
			m_ptWinSize.x = g_cItemSystem->HT_iGetItemInfo( m_dwObjectKeyID, m_stItemInfo, NPC_ITEM_RENTAL_SELL );
		// 제련할 아이템
		else
			m_ptWinSize.x = g_cItemSystem->HT_iGetItemInfo(m_dwObjectKeyID, m_stItemInfo, NPC_ITEM_REFINING); 

		if( m_ptWinSize.x <= 0 )
		{
			g_cUIManager->HT_SetSlotBoxControlTextIndex(nWindowIndex, nControlIndex, 0);
			return;
		}
	}
	
	else if( m_iRenderType == eInfo_Item_Economy )
	{
		m_ptWinSize.x = g_cNPCControl->HT_nNPCControl_GetItemInfo(m_iEconomy_ItemIndex, m_stItemInfo);
	}
	else if (m_iRenderType == eInfo_Item_Fix)
	{
		// 수리 정보 가져오기
		//m_ptWinSize.x = g_cItemSystem->HT_iGetItemInfo(m_dwObjectKeyID, m_stItemInfo); 
		m_ptWinSize.x = g_cItemSystem->HT_iGetFixInfo(m_dwObjectKeyID, m_vFixDisjointInfo, m_bFixDisjointPossible); 

		// 수리 가능일 경우 아이템의 속성과 현재 NPC를 검사한다
		if(m_bFixDisjointPossible == HT_TRUE)	
			m_bFixDisjointPossible = g_cNPCControl->HT_bNPCControl_CheckItemAttriForFixDisjoint(m_dwObjectKeyID);
	}
	else if(m_iRenderType == eInfo_Item_Disjoint)
	{
		// 해체 정보 가져오기
		m_ptWinSize.x = g_cItemSystem->HT_iGetDisjointInfo(m_dwObjectKeyID, m_vFixDisjointInfo, m_bFixDisjointPossible); 
		// 해체 가능일 경우 아이템의 속성과 현재 NPC를 검사한다
		m_bFixDisjointPossible = HT_TRUE;
		if(m_bFixDisjointPossible == HT_TRUE)	
			m_bFixDisjointPossible = g_cNPCControl->HT_bNPCControl_CheckItemAttriForFixDisjoint(m_dwObjectKeyID);
	}
	else if(m_iRenderType == eInfo_Skill)
	{
		// 스킬 정보 가져오기
		m_ptWinSize.x = g_cSkillSystem->HT_iGetSkillInfo(m_dwObjectKeyID, m_stSkillInfo, m_vSkillNextInfo);	
		if( m_ptWinSize.x <= 0 )
		{
			//g_cUIManager->HT_HideWindow(UI_WINDOW_SLOTINFORMATION);
			return;
		}

	}

	HT_vObjectInfo_SetInfoText();
}

//	정보창을 비활성화 시켜줌
HTvoid HTObjectInfo::HT_vObjectInfo_AntiActive()
{
	if( m_bInfoWinImageSw == HT_TRUE )
	{
		m_iRenderType = eInfo_None;
		m_bInfoWinImageSw = HT_FALSE;

		HT_vObjectInfo_DeleteAll();	// 초기화
	}
}

//	전체 텍스트 랜더 컨트롤
HTvoid HTObjectInfo::HT_vObjectInfo_SetInfoText()
{
	unsigned int row = 0;
	HTint iTotalRow = 1;
	int addRow = 0;
	CHTString str;

		HT_ITEMINFO	stInfo;
		if( m_iRenderType == eInfo_Skill )
			stInfo = m_stSkillInfo;
		else
			stInfo = m_stItemInfo;

		// 이름
		g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, stInfo.strName.str);
		g_cUIManager->HT_SetSlotBoxControlToolTipTextColor(nWindowIndex, nControlIndex, iTotalRow, stInfo.strName.color);
		++iTotalRow;
		
		// 설명
		if( stInfo.strDescription.str.HT_bIsEmpty() == HT_FALSE )
		{
			// 빈줄 추가
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_ITEMINFO, iTotalRow, "");
			g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, "");

			//g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_ITEMINFO, iTotalRow, stInfo.strName.color);
			++iTotalRow;

			//if( m_ptWinSize.x < HT_ITEMINFO_DESC_MIN_WIDTH )	// 설명을 위해 최소 사이즈 설정
			//	m_ptWinSize.x = HT_ITEMINFO_DESC_MIN_WIDTH;
			g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, stInfo.strDescription.str);
			g_cUIManager->HT_SetSlotBoxControlToolTipTextColor(nWindowIndex, nControlIndex, iTotalRow, stInfo.strDescription.color);

			HT_RECT Rect; Rect.left = 0; Rect.top = 0; Rect.right = 311; Rect.bottom = 130;
			int strlength = g_pEngineHandler->HT_iGetTextHeight(HT_FONT_GULIM_12, stInfo.strDescription.str, Rect, TEXT_FORMATING_MULTILINE_VTOP_LEFT_CLIP );
			addRow = (strlength/12); 
			for (int i=iTotalRow+1; i<=iTotalRow+addRow; ++i)
				g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, i, "");

			iTotalRow += addRow;
		}

		// 특성
		if(stInfo.vAttributeStr.size())
		{
			// 빈줄 추가
			//g_cUIManager->HT_SetTextLabelControl(_DIALOG_ITEMINFO, iTotalRow, "");
			g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, "");

			//g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_ITEMINFO, iTotalRow, stInfo.strDescription.color);
			++iTotalRow;
			
			CHTString str;
			for( row = 0 ; row < stInfo.vAttributeStr.size() ; ++row)
			{
				str = stInfo.vAttributeStr[row]->basic.str;
				if(stInfo.vAttributeStr[row]->addtion.str.HT_nGetSize() > 0)	// 추가 속성
				{
					str += stInfo.vAttributeStr[row]->addtion.str;
					//g_cUIManager->HT_SetTextLabelControl(_DIALOG_ITEMINFO, iTotalRow, str);
					//g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_ITEMINFO, iTotalRow, stInfo.vAttributeStr[row]->addtion.color);
					g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, str);
					g_cUIManager->HT_SetSlotBoxControlToolTipTextColor(nWindowIndex, nControlIndex, iTotalRow, stInfo.vAttributeStr[row]->addtion.color);

				}
				else
				{
					//g_cUIManager->HT_SetTextLabelControl(_DIALOG_ITEMINFO, iTotalRow, str);
					//g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_ITEMINFO, iTotalRow, stInfo.vAttributeStr[row]->basic.color);
					g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, str);
					g_cUIManager->HT_SetSlotBoxControlToolTipTextColor(nWindowIndex, nControlIndex, iTotalRow, stInfo.vAttributeStr[row]->basic.color);

				}

				
				++iTotalRow;
			}
		}
		// 제한사항
		if(stInfo.vLimitStr.size())	
		{
			// 빈줄 추가
			//g_cUIManager->HT_SetTextLabelControl(_DIALOG_ITEMINFO, iTotalRow, "");
			g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, "");
			//g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_ITEMINFO, iTotalRow, stInfo.vAttributeStr[row]->basic.color);
			++iTotalRow;

			for( row = 0 ; row < stInfo.vLimitStr.size() ; ++row)
			{
//				g_cUIManager->HT_SetTextLabelControl(_DIALOG_ITEMINFO, iTotalRow, stInfo.vLimitStr[row]->str);
//				g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_ITEMINFO, iTotalRow, stInfo.vLimitStr[row]->color);
				g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, stInfo.vLimitStr[row]->str);
				g_cUIManager->HT_SetSlotBoxControlToolTipTextColor(nWindowIndex, nControlIndex, iTotalRow, stInfo.vLimitStr[row]->color);

				++iTotalRow;
			}
		}
		// 제작정보
		if(stInfo.vSourceStr.size())
		{
			// 빈줄 추가
			//g_cUIManager->HT_SetTextLabelControl(_DIALOG_ITEMINFO, iTotalRow, "");
			g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, "");

			//g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_ITEMINFO, iTotalRow, stInfo.vLimitStr[row]->color);

			++iTotalRow;
			
			for( row = 0 ; row < stInfo.vSourceStr.size() ; ++row)
			{
//				g_cUIManager->HT_SetTextLabelControl(_DIALOG_ITEMINFO, iTotalRow, stInfo.vSourceStr[row]->str);
//				g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_ITEMINFO, iTotalRow, stInfo.vSourceStr[row]->color);
				g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, stInfo.vSourceStr[row]->str);
				g_cUIManager->HT_SetSlotBoxControlToolTipTextColor(nWindowIndex, nControlIndex, iTotalRow, stInfo.vSourceStr[row]->color);

				++iTotalRow;
			}
		}
		// 스킬의 다음레벨 세부 정보
		if( m_iRenderType == eInfo_Skill && m_vSkillNextInfo.size() > 0 )
		{
			// 빈줄 추가
			g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, "");
			++iTotalRow;
			
			for( row = 0 ; row < m_vSkillNextInfo.size() ; ++row)
			{
//				g_cUIManager->HT_SetTextLabelControl(_DIALOG_ITEMINFO, iTotalRow, m_vSkillNextInfo[row]->str);
//				g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_ITEMINFO, iTotalRow, m_vSkillNextInfo[row]->color);
				g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, m_vSkillNextInfo[row]->str);
				g_cUIManager->HT_SetSlotBoxControlToolTipTextColor(nWindowIndex, nControlIndex, iTotalRow, m_vSkillNextInfo[row]->color);

				++iTotalRow;
			}
		}

		// 간격 정리(폰트크기-12)
		// 정보창 크기 재 설정
	
	//수리/해체
	else if( (m_iRenderType == eInfo_Item_Fix || m_iRenderType == eInfo_Item_Disjoint) )
	{
		if (g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) == HT_TRUE || g_cUIManager->HT_isShowWindow( _DIALOG_INVENTORY2 ) == HT_TRUE)
		{
			for( row = 0 ; row < m_vFixDisjointInfo.size() ; ++row)
			{
				//g_cUIManager->HT_vSetText(_DIALOG_ITEMINFO, iTotalRow, m_vFixDisjointInfo[row]->str, m_vFixDisjointInfo[row]->color);
				CHTString str;
				str = m_vFixDisjointInfo[row]->str;
				g_cUIManager->HT_SetSlotBoxControlToolTipText(nWindowIndex, nControlIndex, iTotalRow, m_vFixDisjointInfo[row]->str);
				g_cUIManager->HT_SetSlotBoxControlToolTipTextColor(nWindowIndex, nControlIndex, iTotalRow, m_vFixDisjointInfo[row]->color);
				++iTotalRow;
			}

			if(g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE && m_bFixDisjointPossible == HT_FALSE) // 수리/해체 불가능일 경우
				g_cInterfaceCheck->HT_vSetCursor(CURSOR_REPAIRD);	
		}
	}
	g_cUIManager->HT_SetSlotBoxControlTextIndex(nWindowIndex, nControlIndex, iTotalRow-1);
}