#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTQuickSlot.h"

#define HT_COMMAND_QUICKSLOT_MINUS_INDEX		100
#define _SLOT_PREV	100
#define _SLOT_NEXT	101

#define UI_SLOTSTARTVALUE				10

typedef struct _HT_QUICKSLOT_DATA
{
	HTint	iInvenIndex;
	HTint	iIndex;
} _HT_QUICKSLOT_DATA;


HTQuickSlot::HTQuickSlot(void)
{
	m_bQuickSlot_Loaded		= HT_FALSE;
	
	m_bVerSlot				= true;
	m_iPrevSide					= 0;
	m_iSide						= 0;
	//	다른 슬롯에서 넘어오는 텍스쳐 아이디
	m_iSlot_TextureID			= 0;
}

HTQuickSlot::~HTQuickSlot(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_HQUICKSLOT );
	g_cUIManager->HT_DeleteWindow( _DIALOG_WQUICKSLOT );
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vInit()
// D : 퀵슬롯 메모리 초기화
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vInit()
{	
	//	Create Window
	this->HT_vQuick_CreateWindow();
	g_cUIManager->HT_ShowWindow( _DIALOG_HQUICKSLOT );

	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			ZeroMemory(&m_sQuickSlotInfo[i][j], sizeof (HTQuickSlotInfo));
			m_sQuickSlotInfo[i][j].iInvenIndex = -1;	// 아이템일 경우 0부터 시작한다.

			m_dwQuickSlot_StartTimeCoolTime[i][j] = timeGetTime();
			m_fQuickSlot_CoolTime[i][j] = 0;
			m_bQuickSlot_ContinueSw[i][j] = 0;
		}
	}

	//	아이템 사용후 남은 겟수
	m_iUsedItemCount = 0;

	//	Slot No
	m_iSlotNo = 0;

	//	For Continue Item
	for( i=0 ; i<10 ; i++ )
        m_iContinueItemKeyID[i] = 0;
	m_dwContinueItemUseDelay = timeGetTime();
}

//	Create Window
HTvoid HTQuickSlot::HT_vQuick_CreateWindow()
{
	HTint i;
	CHTString strTemp;

	//	[_DIALOG_WQUICKSLOT]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_WQUICKSLOT, _T(""), 440, 40, g_cQuickSlot->HT_vQuick_InputCheckHQuickSlot, 0 );
	g_cUIManager->HT_MoveWindow( _DIALOG_WQUICKSLOT, 175, 0 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_WQUICKSLOT, TRUE, 0,0, 11,38 );
	//	상단 바
	g_cUIManager->HT_AddTextureControl( _DIALOG_WQUICKSLOT, 0, 173, 0, 2 );
	//	하단 바
	g_cUIManager->HT_AddTextureControl( _DIALOG_WQUICKSLOT, 0, 174, 402, 3 );
	//	하단 버튼(위)
	g_cUIManager->HT_AddButtonControl( _DIALOG_WQUICKSLOT, 5, 151, 402, 3, 152, 153 );
	//	하단 버튼(아래)
	g_cUIManager->HT_AddButtonControl( _DIALOG_WQUICKSLOT, 6, 60, 402, 25, 61, 62 );
	//	모양변경
	g_cUIManager->HT_AddButtonControl( _DIALOG_WQUICKSLOT, 7, 57, 417, 10, 58, 59 );
	//	Slot Number
	g_cUIManager->HT_AddLabelControl( _DIALOG_WQUICKSLOT, 8, _T("1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 413, 5, 32, 32 );

	//	Loop
	for( i=0 ; i<10 ; i++ )
	{
		//g_cUIManager->HT_AddTextureControl( _DIALOG_WQUICKSLOT, 0, 172, 12+(i*39), 0 );
		g_cUIManager->HT_AddSlotBoxControl( _DIALOG_WQUICKSLOT, UI_SLOTSTARTVALUE+i, 172, 14+(39*i), 2);
		g_cUIManager->HT_SetSlotBoxControlPosImage(_DIALOG_WQUICKSLOT, UI_SLOTSTARTVALUE+i, 4, 4);
		g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_WQUICKSLOT, UI_SLOTSTARTVALUE+i, HT_TRUE );
		//	Slot Sequence
		strTemp.HT_szFormat( "%d", i+1 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_WQUICKSLOT, 0, strTemp.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25+(39*i), 14, 32, 32 );
	}

		//	[_DIALOG_HQUICKSLOT]
	//	Window
	//g_cUIManager->HT_CreateWindow( 555, _T(""), 40, 440, g_cQuickSlot->HT_vQuick_InputCheckHQuickSlot, 0 );
	//g_cUIManager->HT_WindowArrangement( 555, 7 );

	//	[_DIALOG_HQUICKSLOT]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_HQUICKSLOT, _T(""), 40, 440, g_cQuickSlot->HT_vQuick_InputCheckHQuickSlot, 0 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_HQUICKSLOT, 7 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_HQUICKSLOT, TRUE, 0,0, 38,11 );
	//	상단 바
	g_cUIManager->HT_AddTextureControl( _DIALOG_HQUICKSLOT, 0, 170, 1, 0 );
	//	하단 바
	g_cUIManager->HT_AddTextureControl( _DIALOG_HQUICKSLOT, 0, 174, 0, 403 );
	//	하단 버튼(위)
	g_cUIManager->HT_AddButtonControl( _DIALOG_HQUICKSLOT, 1, 151, 0, 402, 152, 153 );
	//	하단 버튼(아래)
	g_cUIManager->HT_AddButtonControl( _DIALOG_HQUICKSLOT, 2, 60, 0, 425, 61, 62 );
	//	모양변경
	g_cUIManager->HT_AddButtonControl( _DIALOG_HQUICKSLOT, 3, 57, 15, 409, 58, 59 );
	//	Slot Number
	g_cUIManager->HT_AddLabelControl( _DIALOG_HQUICKSLOT, 4, _T("1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 11, 405, 32, 32 );

	//	Loop
	for( i=0 ; i<10 ; i++ )
	{
		//g_cUIManager->HT_AddTextureControl( _DIALOG_HQUICKSLOT, 0, 172, 0, 12+(i*39) );
		g_cUIManager->HT_AddSlotBoxControl( _DIALOG_HQUICKSLOT, UI_SLOTSTARTVALUE+i, 172, 2, 14+(i*39));
		g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_HQUICKSLOT, UI_SLOTSTARTVALUE+i, HT_TRUE );
		g_cUIManager->HT_SetSlotBoxControlPosImage(_DIALOG_HQUICKSLOT, UI_SLOTSTARTVALUE+i, 4, 4);
		//	Slot Sequence
		strTemp.HT_szFormat( "%d", i+1 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_HQUICKSLOT, 0, strTemp.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 14, 24+(i*39), 32, 32 );
	}
}

//	명령_입력함수 처리
void HTQuickSlot::HT_vQuick_InputCheckHQuickSlot(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_SLOTBOX )
	{
		//	아이콘을 들고 엉뚱한 곳에 클릭했을때
		if( iTargetID == -2 )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
		//	아이콘을 들고 맵위에 버렸을경우 슬롯 삭제
		else if( iTargetID == -1 )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}

		if( iAction == UI_ACTION_MOUSE_LCLK )
		{
			if( iTargetID>=UI_SLOTSTARTVALUE && iTargetID<=UI_SLOTSTARTVALUE+10 )
			{
				//	control 버튼이 눌려져 있을때는 Delete
				if( GetAsyncKeyState( VK_CONTROL ) < 0 )
					g_cQuickSlot->HT_OnRButtonUp( iTargetID );
				else
                    g_cQuickSlot->HT_vAction( iTargetID-UI_SLOTSTARTVALUE );
			}
		}
		//else if( iAction == UI_ACTION_MOUSE_RCLK )
		//{
		//	g_cQuickSlot->HT_OnRButtonUp( iTargetID );
		//}
		else if( iAction == UI_ACTION_MOUSE_L_UP )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();

			unsigned int iWIndex, iCIndex;
			g_cUIManager->HT_GetSlotBoxControlSourInfo( iWIndex, iCIndex, g_cQuickSlot->m_iSlot_TextureID );

			//	인벤토리에서 넘어온 아이템일때
			if( iWIndex == _DIALOG_EQUPINVENTORY || iWIndex == _DIALOG_INVENTORY2)
			{
				//	Item KeyID를 얻어오고
				HTdword dwType = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation( iCIndex );
				//	PC인벤토리 내에 있을때만 이동 가능
				if( iCIndex>=100 && iCIndex<=200 )
					g_cQuickSlot->HT_bQuickSlot_SetSlot( dwType, g_cItemSystem->HT_dwSystem_GetItemIndex( dwType ), iTargetID-UI_SLOTSTARTVALUE );
			}
			//	스킬 창에서 넘어온 스킬일때
			else if( iWIndex == _DIALOG_SKILL )
			{
				HTdword dwSkillIndex = g_cUISkillWindow->HT_vGetSkillIndex( iCIndex );
				DWORD dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( dwSkillIndex );
				if( dwSkillUseType == HT_PCSKILLTYPE_PASSIVE )
				{	
					CHTString str;
					HT_g_Script_SetMessage( eMsgSkillUsePassiveErr, &str, _T("") );		
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, str);
					return;
				}
				if( g_cUISkillWindow->HT_vGetSkillLevel(dwSkillIndex) <= 0 )
					return;

				g_cQuickSlot->HT_bQuickSlot_SetSlot( 0, g_cUISkillWindow->HT_vGetSkillIndex(iCIndex), iTargetID-UI_SLOTSTARTVALUE );
			}
			//	커맨드 창에서 넘어온 명령일때
			else if( iWIndex == _DIALOG_COMMANDWND )
			{
				if( iCIndex > 0 && iCIndex < 100 )
					g_cQuickSlot->HT_bQuickSlot_SetSlot( -2, iCIndex, iTargetID-UI_SLOTSTARTVALUE );
			}
		}
	}
	else if( iTarget == UI_TARGET_BUTTON )
	{
		//	Button Up
		if( iTargetID == 1 || iTargetID == 5 )
		{
			g_cQuickSlot->HT_vSetSide( _SLOT_PREV );
		}
		//	Button Down
		else if( iTargetID == 2 || iTargetID == 6 )
		{
			g_cQuickSlot->HT_vSetSide( _SLOT_NEXT );
		}
		//	Button Down
		else if( iTargetID == 3 || iTargetID == 7 )
		{
			if( g_cUIManager->HT_isShowWindow( _DIALOG_HQUICKSLOT ) )
			{
				//	현재 인벤토리의 위치를 구해와서 그기에 팝업한다.
				g_cQuickSlot->m_bVerSlot = false;
				HTint iPosX, iPosY;
				g_cUIManager->HT_GetWindowPos( _DIALOG_HQUICKSLOT, iPosX, iPosY );
				g_cUIManager->HT_MoveWindow( _DIALOG_WQUICKSLOT, iPosX, iPosY );
				g_cUIManager->HT_HideWindow( _DIALOG_HQUICKSLOT );
				g_cUIManager->HT_ShowWindow( _DIALOG_WQUICKSLOT );
			}
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_WQUICKSLOT ) )
			{
				g_cQuickSlot->m_bVerSlot = true;
				HTint iPosX, iPosY;
				g_cUIManager->HT_GetWindowPos( _DIALOG_WQUICKSLOT, iPosX, iPosY );
				g_cUIManager->HT_MoveWindow( _DIALOG_HQUICKSLOT, iPosX, iPosY );
				g_cUIManager->HT_HideWindow( _DIALOG_WQUICKSLOT );
				g_cUIManager->HT_ShowWindow( _DIALOG_HQUICKSLOT );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vIconSave()
// D : 퀵슬롯에 등록되어 있는 아이콘을 저장하여 다음 로그인 때 사용할 수 있도록 한다.
//-------------------------------------------------------------------------------------------
HTvoid 
HTQuickSlot::HT_vIconSave()
{
	_HT_QUICKSLOT_DATA sBufferData;

	CHTString szFileName;
	szFileName.HT_szFormat("system\\QuickSlot_%d_%s.sys", g_iConnectServerGroupIndex, g_oMainCharacterInfo.szCharName );

	FILE*	fp;
	fp = fopen( szFileName.HT_szGetString(), "wb" );
	if (!fp) return;

	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			sBufferData.iIndex = m_sQuickSlotInfo[i][j].iIndex;
			sBufferData.iInvenIndex = m_sQuickSlotInfo[i][j].iInvenIndex;
			fwrite( &sBufferData, sizeof(_HT_QUICKSLOT_DATA), 1, fp);
		}
	}
	
	fclose(fp);
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vIconLoad()
// D : 저장된 아이콘 정보를 로드한다.
//-------------------------------------------------------------------------------------------
HTvoid 
HTQuickSlot::HT_vIconLoad()
{
	if( m_bQuickSlot_Loaded )
	{
		// 포탈 등의 이유로 캐릭터 정보를 초기화할 때 
		HT_vQuickSlot_RenewalSlotItemKeyID();
		return;
	}
	
	CHTString szFileName;
	szFileName.HT_szFormat("system\\QuickSlot_%d_%s.sys", g_iConnectServerGroupIndex, g_oMainCharacterInfo.szCharName );

	m_bQuickSlot_Loaded = HT_TRUE;

	_HT_QUICKSLOT_DATA	sBufferData;

    FILE*	fp;
	fp = fopen( szFileName, "rb" );
	if (!fp) return;

	HTint iKeyID = 0;
	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			fread(&sBufferData, sizeof(_HT_QUICKSLOT_DATA), 1, fp);
			iKeyID = 0;
			
			if( sBufferData.iIndex != 0 )
			{
				HT_Trace("HT_vQuickSlot_Load : [%d][%d]%d-%d\n", i, j, sBufferData.iIndex, sBufferData.iInvenIndex );

				//	Command/스킬/아이템 인덱스 비교
				//	Command	일때는 그냥 넘어감
				if( sBufferData.iInvenIndex < -1 )
				{
					iKeyID = -2;
					m_sQuickSlotInfo[i][j].iIndex = sBufferData.iIndex;
					m_sQuickSlotInfo[i][j].iKeyID = iKeyID;
					m_sQuickSlotInfo[i][j].iInvenIndex = sBufferData.iInvenIndex;
				}
				//	스킬일때
				else if( sBufferData.iInvenIndex == -1 )
				{
					iKeyID = 0;
					if( g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( sBufferData.iIndex ) > 0 )
					{
						m_sQuickSlotInfo[i][j].iIndex = sBufferData.iIndex;
						m_sQuickSlotInfo[i][j].iKeyID = iKeyID;
						m_sQuickSlotInfo[i][j].iInvenIndex = sBufferData.iInvenIndex;
					}
				}
				//	아이템일때
				else if( sBufferData.iInvenIndex >= 0 )
				{
					BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, sBufferData.iInvenIndex, iKeyID );
					if( g_cItemSystem->HT_dwSystem_GetItemIndex( iKeyID ) == sBufferData.iIndex )
					{
						m_sQuickSlotInfo[i][j].iIndex = sBufferData.iIndex;
						m_sQuickSlotInfo[i][j].iKeyID = iKeyID;
						m_sQuickSlotInfo[i][j].iInvenIndex = sBufferData.iInvenIndex;
					}
				}
			}
		}
	}

	fclose(fp);

	//	퀵바에 아이콘 설정
	this->HT_vSetAllIcon();
}

// 슬롯에 등록되어있는 아이템의 KeyID 정보를 갱신한다.
HTvoid HTQuickSlot::HT_vQuickSlot_RenewalSlotItemKeyID()
{
	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			// 등록된 아이템이 있으면
			if( m_sQuickSlotInfo[i][j].iKeyID > 0 )	
			{
				BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, m_sQuickSlotInfo[i][j].iInvenIndex, m_sQuickSlotInfo[i][j].iKeyID );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vAttachIcon( HTint iDlgNo, HTint iType, HTint iCellNo, HTint iIndexID )
// D : 퀵슬롯에 아이콘 붙이기
// I : iDlgNo - 다이알로그 번호, iType - 타입(-2 : 명령, 0 : 스킬, ELSE : UI ITEM), 
//		iCellNo - 퀵슬롯 번호, iIndexID - 아이콘의 인덱스
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vAttachIcon( HTint iDlgNo, HTint iType, HTint iCellNo, HTint iTextureID )
{
	if( iTextureID > 0 )
	{
		//	Set Icon Image
		g_cUIManager->HT_SetSlotImage( _DIALOG_HQUICKSLOT, iCellNo+UI_SLOTSTARTVALUE, iTextureID );
		g_cUIManager->HT_SetSlotImage( _DIALOG_WQUICKSLOT, iCellNo+UI_SLOTSTARTVALUE, iTextureID );
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vSetAllIcon()
// D : 모든 아이콘을 정보에 따라 재설정한다. (정보에 따라 UI만 변경한다.)
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vSetAllIcon()
{
	for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
	{
		if( m_sQuickSlotInfo[m_iSlotNo][j].iInvenIndex < -1 )
		{
			if( m_sQuickSlotInfo[m_iSlotNo][j].iIndex )
                this->HT_vAttachIcon( m_iSlotNo, m_sQuickSlotInfo[m_iSlotNo][j].iKeyID, j, m_sQuickSlotInfo[m_iSlotNo][j].iIndex );
		}
		else if( m_sQuickSlotInfo[m_iSlotNo][j].iInvenIndex == -1 )
		{
			if( m_sQuickSlotInfo[m_iSlotNo][j].iIndex )
                this->HT_vAttachIcon( m_iSlotNo, m_sQuickSlotInfo[m_iSlotNo][j].iKeyID, j, g_cSkillSystem->HT_vSkillSystem_GetSkill_UIIconID( m_sQuickSlotInfo[m_iSlotNo][j].iIndex ) );
		}
		else if( m_sQuickSlotInfo[m_iSlotNo][j].iInvenIndex >= 0 )
		{
			if( m_sQuickSlotInfo[m_iSlotNo][j].iKeyID )
                this->HT_vAttachIcon( m_iSlotNo, m_sQuickSlotInfo[m_iSlotNo][j].iKeyID, j, g_cItemSystem->HT_iItemSystem_GetTextureIDFromKeyID( m_sQuickSlotInfo[m_iSlotNo][j].iKeyID ) );
		}
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vDeleteIcon( HTint iSideNo, HTint iCellNo )
// D : 아이콘 삭제
// I : iSideNo - 퀵바번호, iCellNo - 셀 번호
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vDeleteIcon( HTint iSideNo, HTint iCellNo )
{
	m_sQuickSlotInfo[iSideNo][iCellNo].iIndex = 0;
	m_sQuickSlotInfo[iSideNo][iCellNo].iKeyID = 0;
	m_sQuickSlotInfo[iSideNo][iCellNo].iInvenIndex = -1; // 아이템일 경우 0부터 시작하므로

	//	Icon Image Delete
	if (m_iSide == iSideNo)
	{
		g_cUIManager->HT_SetSlotImage( _DIALOG_HQUICKSLOT, iCellNo+UI_SLOTSTARTVALUE, 0 );
		g_cUIManager->HT_SetSlotImage( _DIALOG_WQUICKSLOT, iCellNo+UI_SLOTSTARTVALUE, 0 );
	}

	//	지속 시간이 설정되어 있다면 초기화
	m_bQuickSlot_ContinueSw[iSideNo][iCellNo] = HT_FALSE;
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vTotalDeleteIcon()
// D : 아이콘 전부삭제
// I : iType - 타입( -2:명령, 0:스킬, 1:UI ITEM), 
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vTotalDeleteIcon( HTint iType )
{
	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			if( m_sQuickSlotInfo[i][j].iKeyID == iType )
                this->HT_vDeleteIcon( i, j );
		}
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vTotalCoolTimeinit()
// D : 현재 돌아가고 있는 쿨타임들 전부 초기화
// I : 
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vTotalCoolTimeInit()
{
	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			//	지속시간 해제
			m_bQuickSlot_ContinueSw[i][j] = HT_FALSE;
			//	쿨타임 시작시간 셋팅
			m_dwQuickSlot_StartTimeCoolTime[i][j] = 0;
			m_fQuickSlot_CoolTime[i][j] = 0;
		}
	}

	for( i=0 ; i<QUICKSLOT_HIGHT ; i++ )
	{
		g_cUIManager->HT_SetSlotBoxCoolTimeCancel( _DIALOG_HQUICKSLOT, i+UI_SLOTSTARTVALUE );
		g_cUIManager->HT_SetSlotBoxCoolTimeCancel( _DIALOG_WQUICKSLOT, i+UI_SLOTSTARTVALUE );
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vDeleteIcon( HTdword dwIndex, HTint iKeyID )
// D : 퀵슬롯에 아이콘 삭제
// I : dwIndex - 인덱스, iKeyID - 키 아이디
//-------------------------------------------------------------------------------------------
HTbool HTQuickSlot::HT_vDeleteIconInResentSlotByIndex( HTdword dwIndex, HTint iKeyID )
{	
	// 2004. 6. 9 추가: 선영범 (스킬시전후 쿨타임시간내에 같은 스킬이 다른 퀵바에서 등록 및 시전 되는 문제 해결)
	// 해결방법 : 모든 퀵바를 조사하여 해당 스킬이 쿨타임 중이라면 아이콘 이동을 취소시킨다.
	for( HTint j = 0 ; j < QUICKSLOT_SIDECOUNT ; ++j )
	{
		for( HTint i = 0 ; i < QUICKSLOT_HIGHT ; ++i )
		{
			if( m_sQuickSlotInfo[j][i].iIndex == dwIndex && m_sQuickSlotInfo[j][i].iKeyID == iKeyID )
			{
				DWORD dwPassTime = timeGetTime();
				if(!(dwPassTime > m_dwQuickSlot_StartTimeCoolTime[j][i]+m_fQuickSlot_CoolTime[j][i]) )
					return HT_FALSE;
			}
		}
	}

	DWORD dwPassTime = timeGetTime();
	if(!(dwPassTime > m_dwQuickSlot_StartTimeCoolTime[m_iSide][m_iSlotNo]+m_fQuickSlot_CoolTime[m_iSide][m_iSlotNo]) )
		return HT_FALSE;

	// 현 퀵바에서 중첩 스킬 아이콘 등록 여부 조사 및 제거
	for( HTint i = 0 ; i < QUICKSLOT_HIGHT ; ++i )
	{
		if( m_sQuickSlotInfo[m_iSide][i].iIndex == dwIndex && m_sQuickSlotInfo[m_iSide][i].iKeyID == iKeyID )
		{
			this->HT_vDeleteIcon( m_iSide, i );
			return HT_TRUE;
		}
	}
	return HT_TRUE;
}

HTvoid HTQuickSlot::HT_vDeleteIconInAllSlotByIndex( HTdword dwIndex, HTint iKeyID )
{	
	for( HTint j = 0 ; j < QUICKSLOT_SIDECOUNT ; ++j )
	{
		for( HTint i = 0 ; i < QUICKSLOT_HIGHT ; ++i )
		{
			if( m_sQuickSlotInfo[j][i].iIndex == dwIndex && m_sQuickSlotInfo[j][i].iKeyID == iKeyID )
			{

				this->HT_vDeleteIcon( j, i );
				// 다른 창에 같은 아이템이 등록되어있을 경우를 위해서 return 하지 않는다.
				//return;
			}
		}
	}
}

//	퀵 슬롯 창 체크
HTvoid HTQuickSlot::HT_vQuickSlot_DlgCheck_LButton( HTPoint pPt, HTbool bVer )
{
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_OnRButtonUp( HTPoint pPt, HTint iDlgNo )
// D : 마우스 오른쪽 버튼이 업 되었을 경우
// I : pPt - 마우스 좌표, iDlgNo - 다이알로그 번호
//-------------------------------------------------------------------------------------------
HTvoid 
HTQuickSlot::HT_OnRButtonUp( HTint iSlotNo )
{
	if( iSlotNo<UI_SLOTSTARTVALUE || m_iSlotNo>=(QUICKSLOT_HIGHT+UI_SLOTSTARTVALUE) ) return;

	// 2004. 6. 10 추가: 선영범 (스킬 시전후 쿨다임중에 아이콘 삭제요청시 삭제되는 버그 수정)
	// 해결방법 : 삭제하려는 퀵바가 쿨다임 중인지를 조사하여 쿨다임 중이면 삭제를 취소시킨다.
	DWORD dwPassTime = timeGetTime();
	DWORD aa = m_dwQuickSlot_StartTimeCoolTime[m_iSide][iSlotNo-QUICKSLOT_HIGHT]+(DWORD)m_fQuickSlot_CoolTime[m_iSide][iSlotNo-QUICKSLOT_HIGHT];
	if(!(dwPassTime > aa) )
		return;

	this->HT_vDeleteIcon( m_iSide, iSlotNo-UI_SLOTSTARTVALUE );
}

// 등록된 아이템의 KeyID 바꾸기
HTbool HTQuickSlot::HT_bChangeIconByKeyID( HTdword dwOldKeyID, HTdword dwNewKeyID )
{
	HTdword dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwNewKeyID );
	// 바꿀 KeyID가 이미 퀵슬롯에 등록되어있을 경우
	if( this->HT_bBeUsedKeyID( dwIndex, dwNewKeyID ) )
	{
		// 다른 슬롯창에 같은 아이템이 등록되어있을 경우를 위해서
		this->HT_vDeleteIconInAllSlotByIndex( dwIndex, (HTint)dwOldKeyID );
		return HT_TRUE;
	}
	else
	{
		HTint iSideCount = 0, i = 0;
		// 등록된 아이템의 PC인벤토리의 위치가 바뀌면 KeyID도 변경된다
		for( iSideCount = 0 ; iSideCount < QUICKSLOT_SIDECOUNT ; ++iSideCount )
		{
			for( i = 0 ; i < QUICKSLOT_HIGHT ; ++i )
			{
				if( m_sQuickSlotInfo[iSideCount][i].iKeyID == dwOldKeyID )
				{
					// 아이템 위치 갱신
					HT_ITEMSETTING_FLAG sLocRoom;
					if( g_cItemSystem->HT_bItemSystem_GetItemPos( dwNewKeyID, sLocRoom ) )
					{
						m_sQuickSlotInfo[iSideCount][i].iInvenIndex = (sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y)
														+ (sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);
						m_sQuickSlotInfo[iSideCount][i].iKeyID = dwNewKeyID;

						m_dwQuickSlot_StartTimeCoolTime[iSideCount][i] = 0;
						m_fQuickSlot_CoolTime[iSideCount][i] = 0;
						// 다른 슬롯창에 같은 아이템이 등록되어있을 경우를 위해서 return하지 않는다.
						//return HT_TRUE;
					}
					else
						return HT_FALSE;
				}
			} // end of for( i = 0 ; i < QUICKSLOT_HIGHT ; ++i )
		} // end of for( iSideCount = 0 ; iSideCount < QUICKSLOT_SIDECOUNT ; ++iSideCount )
	}

	return HT_TRUE;
}

//------------ 네트워크 함수 ------------------//
//	서버에서 퀵스롯에 등록 요청
HTvoid HTQuickSlot::HT_vQuickSlot_ReqRegisterQuickSlot()
{
	//	서버에서 구현이 안되었으니 일단 바로 결과요청을 부른다.
	this->HT_vQuickSlot_ReqRegisterQuickSlot_Result();
}

//	서버에서 퀵스롯에 등록 요청_결과
HTvoid HTQuickSlot::HT_vQuickSlot_ReqRegisterQuickSlot_Result()
{
	// 이미 등록된 명령어/스킬/아이템을 다시 등록할 경우 이전에 등록한 정보 지우기
	if( m_iType == -2 ) // 명령어
		this->HT_vDeleteIconInResentSlotByIndex( g_cCommand->HT_iCommand_GetBitmapImage(), m_iType );
	else				// 스킬/아이템
		if(this->HT_vDeleteIconInResentSlotByIndex( m_iIndexID, m_iType ) == HT_FALSE)
			return;

	//	Command일경우
	if( m_iType == -2 )
	{
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iKeyID = m_iType;
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iIndex = m_iSlot_TextureID;
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iInvenIndex = ( m_iIndexID - HT_COMMAND_QUICKSLOT_MINUS_INDEX );
	}
	//	Skill일 경우
	else if( m_iType == 0 )
	{
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iKeyID = m_iType;
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iIndex = m_iIndexID;
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iInvenIndex = -1;
	}
	//	Item일 경우
	else
	{
		HT_ITEMSETTING_FLAG sLocRoom;
		if( g_cItemSystem->HT_bItemSystem_GetItemPos( m_iType, sLocRoom ) )
		{
			m_sQuickSlotInfo[m_iSide][m_iSlotNo].iInvenIndex = (sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y)
											+ (sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);

			m_sQuickSlotInfo[m_iSide][m_iSlotNo].iKeyID = m_iType;
			m_sQuickSlotInfo[m_iSide][m_iSlotNo].iIndex = m_iIndexID;
		}
	}

	//	이미지 집어넣기
	this->HT_vAttachIcon( m_iSide, m_iType, m_iSlotNo, m_iSlot_TextureID );

	//	Save
	this->HT_vIconSave();
}

//------------------------------------------------------------
//		반환값들
//------------------------------------------------------------
//	슬롯에 정보를 셋팅
//	iType : -2:Command, 0:스킬, ?:ItemKeyID
HTvoid HTQuickSlot::HT_bQuickSlot_SetSlot( HTint iType, HTint iIndexID, HTint iSlotNo )
{
	//	아이템일때 소모성인지 검사
	if( iType > 0 )
	{
		// 화살을 제외한 소모성 아이템만 등록 가능, 유료화 아이템 포함된 차지 아이템도 체크
		if( ( !CHTParamIDCheck::HT_bIsItemUsable( iIndexID ) && !CHTParamIDCheck::HT_bIsItemChargeContinuance( iIndexID )) || 
			  CHTParamIDCheck::HT_bIsItemUsableArrow( iIndexID ) ) 
		{
			CHTString str;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonNotRegistInQuickSlot, &str, _T(""), _T("") );	//	퀵슬롯에 등록불가능한 아이템입니다.
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, str);
            return;
		}
	}

	m_iSlotNo			= iSlotNo;
	if( m_iSlotNo<0 || m_iSlotNo>=QUICKSLOT_HIGHT )
		return;

	m_iType			= iType;
	m_iIndexID		= iIndexID;

	//	서버에서 퀵스롯에 등록 요청
	this->HT_vQuickSlot_ReqRegisterQuickSlot();
}
//	슬롯의 정보를 가져옴
//HTbool HTQuickSlot::HT_bQuickSlot_GetSlot( HTint iSlotNo )
HTbool HTQuickSlot::HT_bBeUsedSlot( HTint iSlotNo )
{
	if( m_sQuickSlotInfo[m_iSide][iSlotNo].iIndex == 0 ) return HT_FALSE;
	return HT_TRUE;
}

//-------------------------------------------------------------------------
// HTbool			HT_bBeUsedKeyID( HTdword dwIndex, HTdword dwKeyID )
// D : 키아이디가 사용되고 있는지 체크
// I : dwIndex - 인덱스, dwKeyID - 키아이디
//-------------------------------------------------------------------------
HTbool 
HTQuickSlot::HT_bBeUsedKeyID( HTdword dwIndex, HTdword dwKeyID )
{
	for( HTint i=0; i<QUICKSLOT_SIDECOUNT; ++i )
	{
		for( HTint j=0; j<QUICKSLOT_HIGHT; ++j )
		{
			if( m_sQuickSlotInfo[i][j].iIndex == dwIndex && m_sQuickSlotInfo[i][j].iKeyID == dwKeyID ) 
				return HT_TRUE;
		}
	}
 
	return HT_FALSE;
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vAction( HTint iSlotNo )
// D : 슬롯에 설정된 기능을 사용
// I : iSlotNo - 슬롯 번호
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vAction( HTint iSlotNo )
{
	//	1. 슬롯이 비었는지 판단
	if( HT_FALSE==this->HT_bBeUsedSlot( iSlotNo ) )	return;

	//	사용 요청한 슬롯의 번호 저장
	m_iQuickSlot_ActionSlotNo = iSlotNo;

	// 퀵바에 등록되어 있는 것을 종류에 따라 분기
	switch(m_sQuickSlotInfo[m_iSide][iSlotNo].iKeyID)
	{
		case -2:
			//	OnChar Message Skip
			g_bSkipMessageOnChar = HT_TRUE;
            g_cCommand->HT_vCommand_SetQuickSlotCmdUse( m_sQuickSlotInfo[m_iSide][iSlotNo].iInvenIndex + HT_COMMAND_QUICKSLOT_MINUS_INDEX );
			break;
		case 0:
			this->HT_vActionskill( iSlotNo );
			break;
		default:
			{
				// 삭제하려는 퀵바가 쿨다임 중인지를 조사하여 쿨다임 중이면 삭제를 취소시킨다.
				//	지속 아이템일 경우 ( 유료화 아이템 )
				if( CHTParamIDCheck::HT_bIsItemChargeContinuance( m_sQuickSlotInfo[m_iSide][iSlotNo].iIndex ) )
				{
					this->HT_vActionItem( iSlotNo );
				}
				else
				{
					DWORD dwPassTime = timeGetTime();
					if( dwPassTime > m_dwQuickSlot_StartTimeCoolTime[m_iSide][iSlotNo]+m_fQuickSlot_CoolTime[m_iSide][iSlotNo] )
					{
						if( !g_cItemControl->HT_vItemControl_GetItemUseSw() )
							this->HT_vActionItem( iSlotNo );
					}
				}
			}
			break;
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vActionItem( HTint iSlotNo)
// D : 슬롯에 있는 아이템 사용
// I : iSlotNo - 슬롯 번호
//-------------------------------------------------------------------------------------------
HTvoid 
HTQuickSlot::HT_vActionItem( HTint iSlotNo )
{
	int i, j;
	HTbool bContinueSw = HT_FALSE;
	HTint iKeyID = m_sQuickSlotInfo[m_iSide][iSlotNo].iKeyID;

	for( i=0 ; i<QUICKSLOT_SIDECOUNT; ++i )
	{
		for( j=0 ; j<QUICKSLOT_HIGHT ; ++j )
		{
			if( m_sQuickSlotInfo[i][j].iKeyID == iKeyID )
			{
				if( m_bQuickSlot_ContinueSw[i][j] == HT_TRUE )
					bContinueSw = HT_TRUE;
			}
		}
	}

	//	지속 시간이 설정되어 있다면 초기화하고 스킵
	if( bContinueSw == HT_TRUE )
	{
		//	남은 아이템 겟수를 구함
		HTint iItemCount = g_cItemSystem->HT_iItemSystem_GetItemCount( iKeyID );
	
		//	아이템이 남아 있지 않을때는 삭제
		if( iItemCount == -1 )
		{
			// 다른 슬롯창에 똑같은 아이템을 등록했을 경우를 위해
			this->HT_vDeleteIconInAllSlotByIndex( m_sQuickSlotInfo[m_iSide][iSlotNo].iIndex, iKeyID );
			//	Save
			this->HT_vIconSave();
		}
		else
		{
			//	퀵바 초기화
			for( i=0 ; i<QUICKSLOT_SIDECOUNT; ++i )
			{
				for( j=0 ; j<QUICKSLOT_HIGHT ; ++j )
				{
					if( m_sQuickSlotInfo[i][j].iKeyID == iKeyID &&
						m_sQuickSlotInfo[i][j].iIndex == m_sQuickSlotInfo[m_iSide][iSlotNo].iIndex )
					{
						g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_HQUICKSLOT, j+UI_SLOTSTARTVALUE, 0, 0 );
						g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_WQUICKSLOT, j+UI_SLOTSTARTVALUE, 0, 0 );
						m_bQuickSlot_ContinueSw[i][j] = HT_FALSE;	//	지속시간 해제
						m_fQuickSlot_CoolTime[i][j] = 0;
						m_dwQuickSlot_StartTimeCoolTime[i][j] = 0;
					}
				}
			}
		}
	}
	//	지속 시간이 설정되어 있지 않을때만 들어감
	else
	{
		g_cItemControl->HT_hrItemControl_ItemUse( iKeyID );
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vResultActionItem( HTdword dwKeyID )
// D : 아이템 사용의 결과
// I : dwKeyID - 키아이디
//-------------------------------------------------------------------------------------------
HTvoid 
HTQuickSlot::HT_vResultActionItem( HTdword dwKeyID )
{
	// 아이템이 등록된 슬롯 위치를 검색한다.
	HTint iSlotSide = -1, iSlotNo = -1;
	if( !this->HT_bBeUsedKeyID( dwKeyID, &iSlotSide, &iSlotNo )  )
	{
		HT_Trace("\nHT_vQuickSlot_SetActionSlot_item_Result-%d(%d,%d)\n ", dwKeyID, iSlotSide, iSlotNo );
		return;
	}

	// 사용한 아이템의 정보
	HTint iIndexID = m_sQuickSlotInfo[iSlotSide][iSlotNo].iIndex;	
	HTint iKeyID = m_sQuickSlotInfo[iSlotSide][iSlotNo].iKeyID;

	//	남은 아이템 겟수를 구함
	m_iUsedItemCount = g_cItemSystem->HT_iItemSystem_GetItemCount( iKeyID );

	//	지속 시간으로 자동으로 아이템을 사용했는가?
	if( m_bQuickSlot_ContinueSw[iSlotSide][iSlotNo] == HT_TRUE )
	{
		//	아이템이 남아 있지 않을때는 삭제
		if( m_iUsedItemCount == -1 )
		{
			// 다른 슬롯창에 똑같은 아이템을 등록했을 경우를 위해
			this->HT_vDeleteIconInAllSlotByIndex( iIndexID, iKeyID );
			//	Save
			this->HT_vIconSave();
		}
		return;
	}

	//	아이템이 남았을때만 쿨다운타임 셋팅
	if( m_iUsedItemCount > 0 )
        this->HT_hrSetCoolTime( 0x01, iIndexID, 1 );

	// 갯수가 남았으면 처리하지 않음
	if( m_iUsedItemCount > 0 )
		return;

	// 같은 종류(인덱스가 같은)의 아이템을 인벤토리에서 찾아서 다시 채운다.
	HTdword dwFindKeyID = 0;		// 찾은 아이템의 KeyID
	HT_ITEMSETTING_FLAG sLocRoom;	// 찾은 아이템의 위치
	g_cItemSystem->HT_vItemSystem_GetItemPos( iIndexID, iKeyID, ITEM_LOCATION_PC, dwFindKeyID, sLocRoom);
	//	지속 아이템일 경우 ( 유료화 아이템 )
	if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iIndexID ) )
	{
		// 다른 슬롯창에 똑같은 아이템을 등록했을 경우를 위해
		this->HT_vDeleteIconInAllSlotByIndex( iIndexID, iKeyID );
		//	Save
		this->HT_vIconSave();
	}
	// 모든 퀵슬롯에 등록되지 않은 같은 종류의 아이템이 있으면
	else if( dwFindKeyID != 0 && this->HT_bBeUsedKeyID( iIndexID, dwFindKeyID ) == HT_FALSE )
	{
		//	다른 슬롯창에 똑같은 아이템을 등록했을 경우를 위해
		this->HT_bChangeIconByKeyID( iKeyID, dwFindKeyID );
		//	쿨타임 재 설정
		this->HT_hrSetCoolTime( 0x01, iIndexID, 1 );
	}
	// 아이템을 모두 사용하였으므로 정보 지우기
	else
	{
		// 다른 슬롯창에 똑같은 아이템을 등록했을 경우를 위해
		this->HT_vDeleteIconInAllSlotByIndex( iIndexID, iKeyID );
		//	Save
		this->HT_vIconSave();
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vActionskill( HTint iSlotNo)
// D : 슬롯에 있는 스킬사용
// I : iSlotNo - 슬롯 번호
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vActionskill( HTint iSlotNo )
{
	if( g_cMainCharacter->HT_nMainChar_GetResentHP() <= 0 )
		return;

	if( g_cMainCharacter->HT_iMainChar_GetAttack_Type() == MAINCHAR_ATTACKTYPE_SKILL )
	{
		return;
	}

	DWORD dwSkillIndex = m_sQuickSlotInfo[m_iSide][iSlotNo].iIndex;
	BYTE byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( dwSkillIndex );
	DWORD dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( dwSkillIndex );

	//	타파스 포인트 체크
	HTint iReqTPPoint;
	g_pParamMgr->HT_bGetPCSkillCostTP( dwSkillIndex, byLevel, &iReqTPPoint );
	if( g_pMainBar->HT_iMainBar_GetCurTP() < iReqTPPoint )
	{
		//TapasPoint가 낮아 스킬을 쓸수 없습니다.
		CHTString szMessage;
		if( g_pMessageMgr->HT_bGetMessage( eMsgQuickSlotUseTPErr, &szMessage ) == true )
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );

		return;
	}
	//	쿨타임 카운트 셋팅
	if( HT_FAILED( this->HT_hrIsCoolTimeOver() ) )
	{
		//CoolTime에 제한이 걸렸습니다.
		CHTString szMessage;
		if( g_pMessageMgr->HT_bGetMessage( eMsgQuickSlotUseCoolTimeErr, &szMessage ) == true )
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );

		return;
	}

	if( dwSkillUseType == HT_PCSKILLTYPE_ACTION )
	{
		//	사무다바 스킬 사용해도 돼냐고 물어보기
		if( dwSkillIndex == HT_SKILLINDEX_SAMUDABA )
		{
			g_cGameSystem->HT_vGameSystem_ReqAnswerUseSamudaba( 1, g_cMainCharacter->HT_iMainChar_GetAttackTargetKeyID(), 0, g_cSkillSystem->HT_vSkillSystem_GetSkillEffect1Param1( dwSkillIndex ) );
			return;
		}

		//----------액션 스킬 셋팅----------//
		g_cMainCharacter->HT_vMainChar_SetActionSkill( dwSkillIndex );
	}
	else if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )
	{
		//----------액티브 스킬 셋팅----------//
		g_cMainCharacter->HT_vMainChar_SetActiveSkill( dwSkillIndex );
	}
}

// 해당 슬롯에 위치한 아이템의 KeyID나 스킬의 Index를 넘겨준다
HTvoid HTQuickSlot::HT_vQuickSlot_GetKeyIDInSlot( HTint iSlotNo, HTint *piKeyID, HTbyte *pbyType )
{
	if( m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iKeyID != 0 )	
	{
		if( m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iKeyID == -2 )// 명령어
		{
			*piKeyID =  m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iInvenIndex + HT_COMMAND_QUICKSLOT_MINUS_INDEX;
			*pbyType = _QUICKSLOT_TYPE_COMMAND;
		}
		else // 아이템
		{
			*piKeyID = m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iKeyID;
			*pbyType = _QUICKSLOT_TYPE_ITEM;
		}
	}
	else if( m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iIndex != 0 )	// 스킬
	{
		*piKeyID = m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iIndex;
		*pbyType = _QUICKSLOT_TYPE_SKILL;
	}
	else
	{
		*piKeyID = 0;
		*pbyType = _QUICKSLOT_TYPE_NONE;
	}
}

//-------------------------------------------------------------------------------------------
// HTbool			HT_bBeUsedKeyID( HTdword dwKeyID, HTint* piSlotSide, HTint* piSlotNo )
// D : 현재 등록되어 있는 키인지 체크하고, 등록되어 있는 Side와 슬롯 번호를 얻음
// I : dwKeyID - 키아이디
// R : piSlotSide - 퀵바의 번호, piSlotNo - 슬롯 번호
//-------------------------------------------------------------------------------------------
HTbool 
HTQuickSlot::HT_bBeUsedKeyID( HTdword dwKeyID, HTint* piSlotSide, HTint* piSlotNo )
{
	for( HTint i = 0 ; i < QUICKSLOT_SIDECOUNT ; ++i )
	{
		for( HTint j = 0 ; j < QUICKSLOT_HIGHT ; ++j )
		{
			if( m_sQuickSlotInfo[i][j].iKeyID == dwKeyID )
			{	
				*piSlotSide = i;
				*piSlotNo = j;
				return HT_TRUE;
			}
		}
	}
	return HT_FALSE;
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vSetSide( HTint iType )
// D : 몇번째 퀵슬롯을 보여줄 것인가 결정한다.
// I : iType - 보여줄 퀵슬롯 ( 100:--, 101:++, 기타:퀵슬롯 번호 )
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vSetSide( HTint iType )
{
	//	Check Slot
	m_iPrevSide = m_iSide;
	switch(iType)
	{
		case _SLOT_PREV:	
			m_iSide--;			break;
		case _SLOT_NEXT:
			m_iSide++;			break;
		default:			
			m_iSide = iType;	break;
	}
	if( m_iSide < 0 )							m_iSide = QUICKSLOT_SIDECOUNT-1;
	else if( m_iSide >= QUICKSLOT_SIDECOUNT )	m_iSide = 0;

	//	Set Slot Number
	CHTString strTemp;
	strTemp.HT_szFormat( "%d", m_iSide+1 );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_HQUICKSLOT, 4, strTemp.HT_szGetString() );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_WQUICKSLOT, 8, strTemp.HT_szGetString() );

	//	Icon Image Delete
	for( HTint i=0 ; i<QUICKSLOT_HIGHT ; i++ )
	{
		g_cUIManager->HT_SetSlotImage( _DIALOG_HQUICKSLOT, i+UI_SLOTSTARTVALUE+1, 0 );
		g_cUIManager->HT_SetSlotImage( _DIALOG_WQUICKSLOT, i+UI_SLOTSTARTVALUE+1, 0 );
	}

	//	아이콘 재 설정
	for( i=0 ; i<QUICKSLOT_HIGHT ; i++ )
	{
		if( 0==m_sQuickSlotInfo[m_iSide][i].iIndex )
		{
			this->HT_vDeleteIcon( m_iSide, i );
		}
		else
		{
			if( m_sQuickSlotInfo[m_iSide][i].iInvenIndex < -1 )
				this->HT_vAttachIcon( m_iSide, m_sQuickSlotInfo[m_iSide][i].iKeyID, i, m_sQuickSlotInfo[m_iSide][i].iIndex );
			else if( m_sQuickSlotInfo[m_iSide][i].iInvenIndex == -1 )
				this->HT_vAttachIcon( m_iSide, m_sQuickSlotInfo[m_iSide][i].iKeyID, i, g_cSkillSystem->HT_vSkillSystem_GetSkill_UIIconID( m_sQuickSlotInfo[m_iSide][i].iIndex ) );
			else if( m_sQuickSlotInfo[m_iSide][i].iInvenIndex >= 0 )
				this->HT_vAttachIcon( m_iSide, m_sQuickSlotInfo[m_iSide][i].iKeyID, i, g_pEngineHandler->HT_dwGetItemUIID( m_sQuickSlotInfo[m_iSide][i].iIndex ) );
		}
	}

	//	About Cool Time
	HTdword dwPassTime = timeGetTime();
	//	쿨타임 재설정
	for (i=0; i<QUICKSLOT_HIGHT; i++)
	{
		if( m_sQuickSlotInfo[m_iSide][i].iIndex != 0 )
		{
			for( HTint j=0 ; j<5 ; j++ )
			{
				for( HTint k=0 ; k<QUICKSLOT_HIGHT ; k++ )
				{
					if( m_sQuickSlotInfo[m_iSide][i].iKeyID == m_sQuickSlotInfo[j][k].iKeyID &&
						m_sQuickSlotInfo[m_iSide][i].iIndex == m_sQuickSlotInfo[j][k].iIndex &&
						m_sQuickSlotInfo[m_iSide][i].iInvenIndex == m_sQuickSlotInfo[j][k].iInvenIndex &&
						dwPassTime < m_dwQuickSlot_StartTimeCoolTime[j][k]+m_fQuickSlot_CoolTime[j][k] )
					{
						m_fQuickSlot_CoolTime[m_iSide][i] = m_fQuickSlot_CoolTime[j][k];
						m_dwQuickSlot_StartTimeCoolTime[m_iSide][i] = m_dwQuickSlot_StartTimeCoolTime[j][k];
						m_bQuickSlot_ContinueSw[m_iSide][i] = m_bQuickSlot_ContinueSw[j][k];
					}
				}
			}
		}
	}
	//	기존의 쿨타임 전부 삭제
    for (i=0; i<QUICKSLOT_HIGHT; i++)
	{
		//	Set UI
		g_cUIManager->HT_SetSlotBoxCoolTimeCancel( _DIALOG_HQUICKSLOT, i+UI_SLOTSTARTVALUE );
		g_cUIManager->HT_SetSlotBoxCoolTimeCancel( _DIALOG_WQUICKSLOT, i+UI_SLOTSTARTVALUE );
	}
	//	현재의 쿨타임 시작
	for (i=0; i<QUICKSLOT_HIGHT; i++)
	{
		//	지속 시간이 설정되어 있을때만 체크
		if( dwPassTime < m_dwQuickSlot_StartTimeCoolTime[m_iSide][i]+m_fQuickSlot_CoolTime[m_iSide][i] )
		{
			HTint iUsedItemCount;
			HTint iCoolTime;
			HTbool bContinue = HT_FALSE;
			HTdword dwTermTime = dwPassTime - m_dwQuickSlot_StartTimeCoolTime[m_iSide][i];
            if( m_sQuickSlotInfo[m_iSide][i].iInvenIndex >= 0 )
			{
				iUsedItemCount = g_cItemSystem->HT_iItemSystem_GetItemCount( m_sQuickSlotInfo[m_iSide][i].iKeyID );
				if( CHTParamIDCheck::HT_bIsItemChargeContinuance( m_sQuickSlotInfo[m_iSide][i].iIndex ) &&
					m_iUsedItemCount > 0 )
				{
					bContinue = HT_TRUE;
				}
			}

			//	지속이 없는 것
            if( !bContinue)
			{
				//	Set UI
				g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_HQUICKSLOT, i+UI_SLOTSTARTVALUE, (HTdword)m_fQuickSlot_CoolTime[m_iSide][i], dwTermTime );
				g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_WQUICKSLOT, i+UI_SLOTSTARTVALUE, (HTdword)m_fQuickSlot_CoolTime[m_iSide][i], dwTermTime );
			}
			//	지속이 있는 것
			else
			{
				//	지속 아이템의 지속 시간은 하드 코딩되어 있다.
				//	남은 아이템 겟수를 이용하여 전체 쿨타임을 구함
				iCoolTime = 59000 * (iUsedItemCount+1);
				//	Set UI
				g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_HQUICKSLOT, i+UI_SLOTSTARTVALUE, iCoolTime, dwTermTime );
				g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_WQUICKSLOT, i+UI_SLOTSTARTVALUE, iCoolTime, dwTermTime );

			}
		}
	}
}

//-------------------------------------------------------------------------------------------
// HTRESULT		HT_hrSetCoolTime( BYTE byType, HTint iIndex, BYTE byLevel )
// D : 쿨다임 설정
//-------------------------------------------------------------------------------------------
HTRESULT 
HTQuickSlot::HT_hrSetCoolTime( BYTE byType, HTint iIndex, BYTE byLevel )
{
	HTint	iCoolTime;
	HTbool	bContinue = HT_FALSE;
	if( byType == 0x01 )
	{
		g_pParamMgr->HT_bGetItemCoolDownTime( iIndex, &iCoolTime );

		//	지속 아이템일 경우 ( 유료화 아이템 )
		if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iIndex ) &&
			m_iUsedItemCount > 0 )
		{
			bContinue = HT_TRUE;
			//	지속 아이템의 지속 시간은 하드 코딩되어 있다.
			iCoolTime = 59000;
		}
	}
	else
	{
		g_pParamMgr->HT_bGetPCSkillCoolDownTime( iIndex, byLevel, &iCoolTime );
		// 서버에서와 클라이언트의 랙때문에 1.1을 곱한다. 추후 개선되도록 해야 한다.
	}

	//	법사 밸런싱 조정
	if( byType = 0x02 && iCoolTime != 59000 )
	{
		if( g_oMainCharacterInfo.snTribe == 4 || g_oMainCharacterInfo.snTribe == 8 )
		{
			float fChakraSoul = (HTfloat)g_cStatus->HT_nGetChakraSoul();
			if( fChakraSoul >= 500 )	fChakraSoul = 500;
			if( fChakraSoul>100 )
			{
				HTint iCurrectTime = (HTint)(iCoolTime*((fChakraSoul-100.0f)/800.0f));
				iCoolTime = iCoolTime - iCurrectTime;
				if( iCoolTime < 0 )
					iCoolTime = 0;
			}
		}
	}

	// 같은 아이템이나 스킬이 여러 슬롯에 등록될 때 쿨타임이 같이 적용되도록 한다.	
	//for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT; ++i )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; ++j )
		{
			if( m_sQuickSlotInfo[m_iSide][j].iIndex == iIndex )
			{
				//	지속이 없는 아이템/스킬 일 경우
				if( bContinue == HT_FALSE )
				{
					m_fQuickSlot_CoolTime[m_iSide][j] = (HTfloat)(iCoolTime);
					m_dwQuickSlot_StartTimeCoolTime[m_iSide][j] = timeGetTime();
					//	Set UI
					g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_HQUICKSLOT, j+UI_SLOTSTARTVALUE, (HTdword)m_fQuickSlot_CoolTime[m_iSide][j], 0 );
					g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_WQUICKSLOT, j+UI_SLOTSTARTVALUE, (HTdword)m_fQuickSlot_CoolTime[m_iSide][j], 0 );
				}
				else
				{
					//	지속시간 셋팅
					m_bQuickSlot_ContinueSw[m_iSide][j] = HT_TRUE;
					//	아이템 1개의 쿨타임을 미리 저장하고
					m_fQuickSlot_CoolTime[m_iSide][j] = (HTfloat)(iCoolTime);
					//	남은 아이템 겟수를 이용하여 전체 쿨타임을 구함
					iCoolTime = iCoolTime * (m_iUsedItemCount+1);
					m_dwQuickSlot_StartTimeCoolTime[m_iSide][j] = timeGetTime();
					//	Set UI
					g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_HQUICKSLOT, j+UI_SLOTSTARTVALUE, iCoolTime, 0 );
					g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_WQUICKSLOT, j+UI_SLOTSTARTVALUE, iCoolTime, 0 );
				}
			}
		}
	}
	return HT_OK;
}

//-------------------------------------------------------------------------------------------
//	HTRESULT		HT_hrIsCoolTimeOver()
// D : 현재 실행하려는 퀵스킬 등록 아이콘의 쿨타임체크
// R : HT_OK - 쿨타임 초과 ( 사용할 수 있음 )
//		HT_FAIL - 쿨타임 미초과 ( 사용할 수 없음 )
//-------------------------------------------------------------------------------------------
HTRESULT 
HTQuickSlot::HT_hrIsCoolTimeOver()
{
	DWORD dwPassTime = timeGetTime();
	if( dwPassTime > m_dwQuickSlot_StartTimeCoolTime[m_iSide][m_iQuickSlot_ActionSlotNo]+m_fQuickSlot_CoolTime[m_iSide][m_iQuickSlot_ActionSlotNo] )
		return HT_OK;
	else
		return HT_FAIL;
}

//-------------------------------------------------------------------------------------------
// HTvoid		HT_hrContinueTimeCheck()
// D : 지속시간이 설정된 아이템들 체크
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vContinueTimeCheck()
{
	HTint i,j;

	//	Get m_bPotionItemUse_Sw
	if( !g_cItemControl->HT_vItemControl_GetItemUseSw() )
	{
		//	For Continue Item
		for( i=0 ; i<10 ; i++ )
		{
			if( m_iContinueItemKeyID[i] != 0 )
			{
				//	아이템 사용을 계속 요청한다.
				g_cItemControl->HT_hrItemControl_ItemUse( m_iContinueItemKeyID[i] );
				if( g_cItemControl->HT_vItemControl_GetItemUseSw() )
                    m_iContinueItemKeyID[i] = 0;
				return;
			}
		}
	}

	DWORD dwPassTime = timeGetTime();
	for( i=0 ; i<QUICKSLOT_SIDECOUNT; ++i )
	{
		for( j=0 ; j<QUICKSLOT_HIGHT ; ++j )
		{
			//	지속 시간이 설정되어 있을때만 체크
			if( m_bQuickSlot_ContinueSw[i][j] == HT_TRUE )
			{
				if( dwPassTime > m_dwQuickSlot_StartTimeCoolTime[i][j]+m_fQuickSlot_CoolTime[i][j] )
				{
					for( int k=0 ; k<10 ; k++ )
					{
						if( m_iContinueItemKeyID[k] == 0 && 
							m_iContinueItemKeyID[k] != m_sQuickSlotInfo[i][j].iKeyID )
						{
							m_iContinueItemKeyID[k] = m_sQuickSlotInfo[i][j].iKeyID;
							break;
						}
					}
					//g_cItemControl->HT_hrItemControl_ItemUse( m_sQuickSlotInfo[i][j].iKeyID );
					//	쿨타임 시작을 다시 설정 해준다.
					m_dwQuickSlot_StartTimeCoolTime[i][j] = dwPassTime;
					return;
				}
			}
		}
	}
}

