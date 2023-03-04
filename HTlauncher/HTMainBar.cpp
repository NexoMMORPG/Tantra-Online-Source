//======================================================================
// HTMainBar.h
// 화면 하단의 메인 바
// (주)한빛소프트 게임개발팀 서명석		2003.03.07
//======================================================================

#include "stdafx.h"
#include "HTextern.h"
#include "HTControlDef.h"
#include "HTEngineHandler.h"
#include "HTMainBar.h"


CHTMainBar::CHTMainBar()
{
	//	스킬 총 카운트
	m_nSkillTotalCount = 31;

	m_iActiveSkillID = -1;
	m_iActionSkillID = -1;

	m_strHP.HT_hrCleanUp();
	m_strPRANA.HT_hrCleanUp();

	m_dwNeedPrana = 0;

	// 새로운UI수정(20030728)
	m_iCurChacra	= 0;
	m_iTotalPrana	= 0;

	//	선택한 대상의 이름
	m_strPickObjectName.HT_hrCleanUp();
}

CHTMainBar::~CHTMainBar()
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_MAINBAR );
	g_cUIManager->HT_DeleteWindow( _DIALOG_MAINCHARHP );
	g_cUIManager->HT_DeleteWindow( _DIALOG_PRANABAR );
	g_cUIManager->HT_DeleteWindow( _DIALOG_BUFFSKILL );
	g_cUIManager->HT_DeleteWindow( _DIALOG_MINIMAINBAR );
}

HTvoid CHTMainBar::HT_vLoad()
{
	//	Create Window
	this->HT_vMainBar_CreateWindow();
	g_cUIManager->HT_ShowWindow( _DIALOG_MAINBAR );
	g_cUIManager->HT_ShowWindow( _DIALOG_MAINCHARHP );
	g_cUIManager->HT_ShowWindow( _DIALOG_PRANABAR );
	g_cUIManager->HT_ShowWindow( _DIALOG_BUFFSKILL );
	
	//	오브젝트 상자에 HP를 그리지 않게 하다
	this->HT_vSetObjectHPOut();
	//	오브젝트 상자에 Name를 그리지 않게 하다
	this->HT_vSetObjectNameOut();

	//	타파스
	m_iMainBar_MaxTP = 0;
	m_iMainBar_CurTP = 0;

	//	나의 스킬
	for( HTint i=0 ; i<10 ; i++ )
	{
		m_iMainBar_MySkillID[i] = 0;
		m_iMainBar_MySkillStartTime[i] = 0;
		m_iMainBar_MySkillDurationTime[i] = 0;
	}

	//	PK Button
	m_bMainBar_PKButton = HT_FALSE;
}
HTvoid CHTMainBar::HT_vMainBar_CreateWindow()
{
	CHTString strMessage;

	// 해상도 추출
	m_iScreenWidth	= g_pEngineHandler->HT_iGetScreenWidth();
	m_iScreenHIGHT	= g_pEngineHandler->HT_iGetScreenHeight();

	//	[Main Bar]
	int iForIndex = 0;
	if( g_iInationalType == INATIONALTYPE_TAIWAN )
	{
		m_iForDelPriminumIconX = 38;
		iForIndex = 1;
	}
	else
	{
		m_iForDelPriminumIconX = 0;
		iForIndex = 0;
	}
	
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_MAINBAR, _T(""), 340-m_iForDelPriminumIconX, 39, g_pMainBar->HT_vMainBar_InputCheckForMainBar, 0 );
	g_cUIManager->HT_MoveWindow( _DIALOG_MAINBAR, m_iScreenWidth-(340+m_iForDelPriminumIconX), m_iScreenHIGHT-40-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_MAINBAR, TRUE, 0,0, 11,38 );
	//	왼쪽바
	g_cUIManager->HT_AddTextureControl( _DIALOG_MAINBAR, 0, 173, 0, 1 );
	//	Set Texture
	for( HTint i=0 ; i<(8-iForIndex) ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_MAINBAR, 0, 171, 12+(38*i), 0 );
	}
	if( iForIndex == 0 )
	{
		//	Button Commercial, Status, Inventory, Quest, Skill, System, Command, PK
		g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 1, 34, 14, 4, 35, 33 );
		g_cUIManager->HT_SetScriptMessage( eMsgMainCheckPrimiumBuy, &strMessage, _T(""), _T("") );	//	프리미엄 아이템
		g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 1, strMessage );
		g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 1 );
	}
	//	Button Status, Inventory, Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 2, 37, 52-m_iForDelPriminumIconX, 4, 38, 36 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckCharacInfo, &strMessage, _T(""), _T("") );	//	캐릭터 상태(L)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 2, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 2 );
	//	Button Inventory, Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 3, 40, 90-m_iForDelPriminumIconX, 4, 41, 39 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckInventory, &strMessage, _T(""), _T("") );	//	인벤토리(I)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 3, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 3 );
	//	Button Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 4, 43, 128-m_iForDelPriminumIconX, 4, 44, 42 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckQuest, &strMessage, _T(""), _T("") );	//	퀘스트(U)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 4, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 4 );
	//	Button Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 5, 46, 166-m_iForDelPriminumIconX, 4, 47, 45 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckSkill, &strMessage, _T(""), _T("") );	//	스킬(K)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 5, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 5 );
	//	Button System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 6, 49, 204-m_iForDelPriminumIconX, 4, 50, 48 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckOption, &strMessage, _T(""), _T("") );	//	시스템(ESC)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 6, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 6 );
	//	Button Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 7, 52, 242-m_iForDelPriminumIconX, 4, 53, 51 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckCommand, &strMessage, _T(""), _T("") );	//	명령(C)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 7, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 7 );
	//	Button PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 8, 55, 280-m_iForDelPriminumIconX, 4, 56, 54 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckPK, &strMessage, _T(""), _T("") );	//	PK
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 8, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 8 );
	//	Button 모양번경
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 9, 154, 316-m_iForDelPriminumIconX, 4, 155, 176 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonChangeStyle, &strMessage, _T(""), _T("") );	//	모양변경
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 9, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 9 );

	//	[_DIALOG_MINIMAINBAR]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_MINIMAINBAR, _T(""), 188-m_iForDelPriminumIconX, 39, g_pMainBar->HT_vMainBar_InputCheckForMainBar, 0 );
	g_cUIManager->HT_MoveWindow( _DIALOG_MINIMAINBAR, m_iScreenWidth-152, m_iScreenHIGHT-40-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_MINIMAINBAR, TRUE, 0,0, 11,38 );
	//	왼쪽바
	g_cUIManager->HT_AddTextureControl( _DIALOG_MINIMAINBAR, 0, 173, 0, 1 );
	//	Set Texture
	for( HTint i=0 ; i<4-iForIndex ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_MINIMAINBAR, 0, 171, 12+(38*i), 0 );
	}
	//	Button Commercial, Status, Inventory, Quest, Skill, System, Command, PK
	if( iForIndex == 0 )
	{
		g_cUIManager->HT_AddButtonControl( _DIALOG_MINIMAINBAR, 1, 34, 14, 4, 35, 33 );
		g_cUIManager->HT_SetScriptMessage( eMsgMainCheckPrimiumBuy, &strMessage, _T(""), _T("") );	//	프리미엄 아이템
		g_cUIManager->HT_SetButtonToolTip( _DIALOG_MINIMAINBAR, 1, strMessage );
		g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MINIMAINBAR, 1 );
	}
	//	Button Status, Inventory, Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MINIMAINBAR, 3, 40, 52-m_iForDelPriminumIconX, 4, 41, 39 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckInventory, &strMessage, _T(""), _T("") );	//	인벤토리(I)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MINIMAINBAR, 3, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MINIMAINBAR, 3 );
	//	Button Inventory, Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MINIMAINBAR, 6, 49, 90-m_iForDelPriminumIconX, 4, 50, 48 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckOption, &strMessage, _T(""), _T("") );	//	시스템(ESC)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MINIMAINBAR, 6, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MINIMAINBAR, 6 );
	//	Button Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MINIMAINBAR, 7, 52, 128-m_iForDelPriminumIconX, 4, 53, 51 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckCommand, &strMessage, _T(""), _T("") );	//	명령(C)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MINIMAINBAR, 7, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MINIMAINBAR, 7 );
	//	Button 모양번경
	g_cUIManager->HT_AddButtonControl( _DIALOG_MINIMAINBAR, 9, 154, 164-m_iForDelPriminumIconX, 4, 155, 176 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonChangeStyle, &strMessage, _T(""), _T("") );	//	모양변경
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MINIMAINBAR, 9, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MINIMAINBAR, 9 );

	//	[MainChar HP Bar]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_MAINCHARHP, _T(""), 169, 74, g_pMainBar->HT_vMainBar_InputCheckForMainCharHP, 0,HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 70.0f/100.0f ) );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_MAINCHARHP, TRUE, 3,3, 163, 14 );
	g_cUIManager->HT_MoveWindow( _DIALOG_MAINCHARHP, 38, 0 );
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINCHARHP, 13, 0, 0, 0, 0, 0, 1500, 169, 72 );
	//	Texture 외곽 라인
	g_cUIManager->HT_AddTextureControl( _DIALOG_MAINCHARHP, 1, 1, 0, 0, 1400, 3, 73 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_MAINCHARHP, 2, 1, 167, 0, 1400, 3, 73 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_MAINCHARHP, 3, 2, 0, 0, 1400, 169, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_MAINCHARHP, 5, 2, 0, 16, 1400, 168, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_MAINCHARHP, 5, 2, 0, 49, 1400, 168, 3 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_MAINCHARHP, 6, 2, 0, 73, 1400, 169, 3 );
	//	Texture HP
	g_cUIManager->HT_AddTextureControl( _DIALOG_MAINCHARHP, 10, 105, 3, 20, 1400, 164, 15 );
	//	Texture TP
	g_cUIManager->HT_AddTextureControl( _DIALOG_MAINCHARHP, 11, 104, 3, 35, 1400, 164, 15 );
	//	Texture Object HP
	g_cUIManager->HT_AddTextureControl( _DIALOG_MAINCHARHP, 12, 101, 3, 65, 1402, 164, 8 );
	//	Label MainChar Nmae
	g_cUIManager->HT_AddLabelControl( _DIALOG_MAINCHARHP, 1, g_oMainCharacterInfo.szCharName, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 3, 3, 164, 13 );
	//	Label Other Name
	g_cUIManager->HT_AddLabelControl( _DIALOG_MAINCHARHP, 2,_T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 3, 54, 164, 13 );
	//	Label MainChar HP
	g_cUIManager->HT_AddLabelControl( _DIALOG_MAINCHARHP, 3,_T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 3, 22, 164, 13 );
	//	Label MainChar TP
	g_cUIManager->HT_AddLabelControl( _DIALOG_MAINCHARHP, 4,_T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 3, 38, 164, 13 );
	//	Label Other Name HP
	g_cUIManager->HT_AddLabelControl( _DIALOG_MAINCHARHP, 5,_T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 3, 65, 164, 13 );

	g_cUIManager->HT_WindowArrangement( _DIALOG_MAINCHARHP, 8 );

	//	[_DIALOG_PRANABAR]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_PRANABAR, _T(""), m_iScreenWidth, 16, g_pMainBar->HT_vMainBar_InputCheckForPranaBar, 0 );
	//g_cUIManager->HT_MoveWindow( _DIALOG_PRANABAR, 0, m_iScreenHIGHT-16 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_PRANABAR, 1 );
	//	Texture 외곽 라인
	g_cUIManager->HT_AddTextureControl( _DIALOG_PRANABAR, 0, 107, 0, 0  );
	g_cUIManager->HT_AddTextureControl( _DIALOG_PRANABAR, 0, 108, (int)(m_iScreenWidth-400), 0 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_PRANABAR, 0, 0, 400, 4, HT_COLOR( 0.0f, 0.0f, 0.0f, 1.0f ), (int)(m_iScreenWidth-796), 8 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_PRANABAR, 3, 203, 0, 4, HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ), 0, 6, 1401 );
	//	Label Prana Bar
	g_cUIManager->HT_AddLabelControl( _DIALOG_PRANABAR, 4,_T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), (int)(m_iScreenWidth/2)-24, 0, 48, 13 );
	g_cUIManager->HT_EnableOffWindow( _DIALOG_PRANABAR );

	//	[_DIALOG_BUFFSKILL]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_BUFFSKILL, _T(""), 320, 32, g_pMainBar->HT_vMainBar_InputCheckForBuffSkill, 0 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_BUFFSKILL, TRUE, 0,0, 320, 32 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_BUFFSKILL, 9 );
	for( i=0 ; i<MYSKILL_COUNT ; i++ )
	{
        g_cUIManager->HT_AddSlotBoxControl( _DIALOG_BUFFSKILL, i, 0, (MYSKILL_COUNT-i-1)*32, 0 );
		g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_BUFFSKILL, i, 0, 0 );
		g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_BUFFSKILL, i, HT_TRUE );
	}
}

//	입력 메세지 처리
//	Main Bar
void CHTMainBar::HT_vMainBar_InputCheckForMainBar(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
       	//	Commercial
		if( iTargetID == 1 )
		{
			if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) )
				g_cUIManager->HT_HideWindow( _DIALOG_NPCWINDOW );
			else
				g_cNPCControl->HT_vNPCControl_Active(9999);
		}
		// Status
		else if( iTargetID == 2 )
		{
			//	죽지 않았을때만
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )		g_cStatus->HT_vStatus_ActiveSw();
		}
		//	Inventory
		else if( iTargetID == 3 )
		{
			//	죽었을때만 죽지않았을때나 모두 처리
			g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
		}
		//	Quest
		else if( iTargetID == 4 )
		{
			//	죽지 않았을때만
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )		g_cQuest->HT_vQuest_ActiveSw();
		}
		//	Skill
		else if( iTargetID == 5 )
		{
			//	죽지 않았을때만
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )		g_cSkillInventory->HT_vSkillInventoryActiveCheck( 0x00 );
		}
		//	System
		else if( iTargetID == 6 )
		{
			//	죽지 않았을때만
	//		if( g_cMainCharacter->HT_vMainChar_GetCharLive() )		
	//		{
	//			g_cSystem->HT_vSystem_ActiveSw();
			if (g_cUIManager->HT_isShowWindow(_DIALOG_OPTIONWND) == true)
				g_cUIManager->HT_HideWindow(_DIALOG_OPTIONWND);
			else
				g_cUIManager->HT_ShowWindow(_DIALOG_OPTIONWND);
	//		}
		}
		//	Command
		else if( iTargetID == 7 )
		{
			//	죽지 않았을때만
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )		g_cCommand->HT_vCommand_WndActiveSw();
		}
		//	PK
		else if( iTargetID == 8 )
		{
			//	주신전 지역에서는 의미가 없다.
			if( HT_SUCCEED( HT_extern_TrimuritiZone( g_wResentZoneServerID ) ) )
				return;
			//	요새전 지역에서는 의미가 없다.
			if( HT_SUCCEED( HT_extern_ForetressZone( g_wResentZoneServerID ) ) )
				return;
			//	For PK Button
			g_pMainBar->HT_vMainBar_GameSystem_SetForPKButton();
		}
		//	모양변경
		else if( iTargetID == 9 )
		{
			HTint iPosX, iPosY;
			if( g_cUIManager->HT_isShowWindow(_DIALOG_MAINBAR) )
			{
				g_cUIManager->HT_GetWindowPos( _DIALOG_MAINBAR, iPosX, iPosY );
				g_cUIManager->HT_HideWindow(_DIALOG_MAINBAR);

				g_cUIManager->HT_ShowWindow(_DIALOG_MINIMAINBAR);
				g_cUIManager->HT_MoveWindow(_DIALOG_MINIMAINBAR, iPosX+152, iPosY );
			}
			else
			{
				g_cUIManager->HT_GetWindowPos( _DIALOG_MINIMAINBAR, iPosX, iPosY );
				g_cUIManager->HT_HideWindow(_DIALOG_MINIMAINBAR);

				g_cUIManager->HT_ShowWindow(_DIALOG_MAINBAR);
				g_cUIManager->HT_MoveWindow(_DIALOG_MAINBAR, iPosX-152, iPosY );
			}
		}
	}
}

//	Main Char HP
void CHTMainBar::HT_vMainBar_InputCheckForMainCharHP(int iAction, int iTarget, int iTargetID)
{
	//	Object Targeting EFfect off
	g_cOtherObjectSystem->HT_vOtherObjectSystem_HPWindowInit();
	//	Pick Myself
	g_cMainCharacter->HT_vMainCharMyselfClick();
}

//	Prana Bar
void CHTMainBar::HT_vMainBar_InputCheckForPranaBar(int iAction, int iTarget, int iTargetID)
{
}

//	Buff Skill
void CHTMainBar::HT_vMainBar_InputCheckForBuffSkill(int iAction, int iTarget, int iTargetID)
{
	g_cUIManager->HT_RefuseSlotImageMoving();
}

//	Set PK Button
HTvoid CHTMainBar::HT_vMainBar_GameSystem_SetForPKButton()
{
	m_bMainBar_PKButton = !m_bMainBar_PKButton;
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();

	//	PK Button 을 누른것을 서버에 알려줌
	MSG_TOGGLE_BUTTON* info;
	info = new MSG_TOGGLE_BUTTON;
	info->byButton = 1;
	info->byValue = m_bMainBar_PKButton;
	g_pNetWorkMgr->RequestPKToggleButton( info );
	HT_DELETE( info );

	CHTString szMessage;
	if( m_bMainBar_PKButton )
	{
		if( g_cStatus->HT_iGetKarmaPoint() == 0 )
		{
			// [경고]PK를 하면 다른 플레이어로부터 공격 받게되며 경험치와 아이템을 잃게됩니다.
			HT_g_Script_SetMessage( eMsgAttackPKWarning, &szMessage);
			g_cUIManager->HT_MessageBox( _DIALOG_PRANABAR, szMessage.HT_szGetString(), 0 );
		}
		//	Pk Button Turn On
		g_cUIManager->HT_SetButtonControlState( _DIALOG_MAINBAR, 8, 1 );
	}
	else
	{
		// PK 모드가 해제되었습니다.
		HT_g_Script_SetMessage( eMsgAttackPKModeCancel, &szMessage);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		//	Pk Button Turn Off
		g_cUIManager->HT_SetButtonControlState( _DIALOG_MAINBAR, 8, 0 );
	}
}

//	메인바_스케쥴러
HTvoid CHTMainBar::HT_vMainBar_Control( HTfloat fElapsedTime )
{
	this->HT_vMainBar_MySkillEndTimeCheck();
}

//	오브젝트 상자에 텍스트를 쓴다.
HTvoid CHTMainBar::HT_vSetObjectTextDraw( CHTString strTemp )
{
	// 아바라카라의 경우 오토방지를 위해 글자 출력안함
	if (strcmp(strTemp, "아바라카라") != 0)
	{
		//	Edit Other Name
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_MAINCHARHP, 2, strTemp.HT_szGetString() );
	}

	//	선택한 대상의 이름
	m_strPickObjectName = strTemp.HT_szGetString();
}

//	오브젝트 상자에 HP를 그린다.
HTvoid CHTMainBar::HT_vSetObjectHPDraw( HTint nResentHP, HTint nMaxHP )
{
	if( HT_SUCCEED( g_cItemSystem->HT_hrItemSystem_GetSameNameCheck( m_strPickObjectName.HT_szGetString() ) ) )
		return;

	if( nResentHP<=0 || nResentHP>nMaxHP || nMaxHP<=0 )
		return;

	//====================================================================================
	// 새로운UI수정(20030728)
	//====================================================================================
	// HP %계산
	//HTvector3 vecScale;
	//vecScale = HTvector3(1.0f, 1.0f, 1.0f);

	HTfloat xPos = (HTfloat)nResentHP/(HTfloat)nMaxHP;
	if( xPos>1.0f)		xPos = 1.0f;
	else if( xPos<0.0f)	xPos = 0.0f;

	// HP 가 있으면 HP의 왼쪽 동그란 HP를 그리고, 아니면 그리지 않는다.
	if (xPos>0.0f)
	{
		//	Texture HP
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_MAINCHARHP, 12, HT_TRUE );
        g_cUIManager->HT_SetTextureControlScale( _DIALOG_MAINCHARHP, 12, 164*xPos, 8 );
	}

	if( g_bDevelopingMode )
	{
		CHTString strHP;
		strHP.HT_szFormat( "%d/%d", nResentHP, nMaxHP );			
		//	Label Other Name HP
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_MAINCHARHP, 5, strHP.HT_szGetString() );
	}
	//====================================================================================
}

//	오브젝트 상자에 HP를 그리지 않게 하다
HTvoid CHTMainBar::HT_vSetObjectHPOut()
{
	//	Del Texture HP
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_MAINCHARHP, 12, HT_FALSE );
}

//	오브젝트 상자에 Name를 그리지 않게 하다
HTvoid CHTMainBar::HT_vSetObjectNameOut()
{
	//	Edit Other Name
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_MAINCHARHP, 2, _T("") );
}

// 프라나 정보를 업데이트 한다.
HTvoid CHTMainBar::HT_vPranaUpdate( HTint iTotalPrana )
{
	//	사이즈 계산
	HTfloat fRatio;

	if (m_dwNeedPrana==0) fRatio = 1.0f;
	else fRatio = (HTfloat)iTotalPrana/(HTfloat)m_dwNeedPrana;
	if (fRatio>1.0f)	fRatio = 1.0f;

	// 프라나
	CHTString strPR;
	HTfloat fPercent;
	fPercent = (HTfloat)iTotalPrana/(HTfloat)m_dwNeedPrana;
	fPercent *= 100.0f;
	strPR.HT_szFormat( "%.2f%s", fPercent, "%" );	

	HTint iWidth = (HTint)(m_iScreenWidth*fRatio);
	//	Texture Prana
	//g_cUIManager->HT_DelTextureControl( _DIALOG_PRANABAR, 3 );
	//g_cUIManager->HT_AddTextureControl( _DIALOG_PRANABAR, 3, 1400, iWidth, 2 );
	g_cUIManager->HT_SetTextureControlScale( _DIALOG_PRANABAR, 3, iWidth, 6 );
    g_cUIManager->HT_SetTextLabelControl( _DIALOG_PRANABAR, 4, strPR.HT_szGetString() );
}

// HP 정보를 업데이트 한다.
HTvoid CHTMainBar::HT_vHPUpdate(HTint iCurHP, HTint iMaxHP )
{
	//	사이즈 계산
	HTfloat fRatio = (HTfloat)iCurHP/(HTfloat)iMaxHP;
	if( fRatio > 1.0f )			fRatio = 1.0f;
	else if( fRatio < 0.0f )	fRatio = 0.0f;

	// 물약에 의한 HP 정보를 업데이트 한다.
	this->HT_vMainBar_SetCurTransparent( iCurHP, iMaxHP );

	// HP 바의 텍스트 준비
	CHTString strHP;
	strHP.HT_szFormat( "%d/%d", iCurHP, iMaxHP );
	//	Edit MainChar HP
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_MAINCHARHP, 3, strHP.HT_szGetString() );
}

// 물약에 의한 HP 정보를 업데이트 한다.
HTvoid
CHTMainBar::HT_vMainBar_SetCurTransparent( HTint iCurHP, HTint iMaxHP )
{
	if( iCurHP == 0 )
	{
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_MAINCHARHP, 10, HT_FALSE );
	}
	else
	{
		//	사이즈 계산
		HTfloat fRatio = (HTfloat)iCurHP/(HTfloat)iMaxHP;
		if( fRatio > 1.0f )			fRatio = 1.0f;
		else if( fRatio < 0.0f )	fRatio = 0.0f;

		//	Texture HP
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_MAINCHARHP, 10, HT_TRUE );
		g_cUIManager->HT_SetTextureControlScale( _DIALOG_MAINCHARHP, 10, 164*fRatio, 15 );
	}
}

//--------------------------------------------------------------
// D : 타파스
//--------------------------------------------------------------
//	Cur TP 셋팅
HTvoid
CHTMainBar::HT_vMainBar_SetCurTP( HTint iCurTP, HTint iMaxTP )
{
	if( iMaxTP > 0 ) 
        m_iMainBar_MaxTP = iMaxTP;
	m_iMainBar_CurTP = iCurTP;

	HTvector3 vecScale;
	vecScale = HTvector3(1.0f, 1.0f, 1.0f);

	// TP %계산
	HTfloat xPos = (HTfloat)m_iMainBar_CurTP/(HTfloat)m_iMainBar_MaxTP;
	if (xPos<0.0f || m_iMainBar_MaxTP == 0 )		xPos = 0.0f;
	else if (xPos>1.0f)								xPos = 1.0f;

	//	Texture TP
	if(  iCurTP == 0 )
	{
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_MAINCHARHP, 11, HT_FALSE );
	}
	else
	{
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_MAINCHARHP, 11, HT_TRUE );
		g_cUIManager->HT_SetTextureControlScale( _DIALOG_MAINCHARHP, 11, 164*xPos, 15 );
	}

	// TP 바의 텍스트 준비
	CHTString strTP;
	strTP.HT_szFormat( "%d/%d", m_iMainBar_CurTP, m_iMainBar_MaxTP );
	//	Edit MainChar TP
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_MAINCHARHP, 4, strTP.HT_szGetString() );
}

//	나의스킬 셋팅
//	byActor 1:MainChar,2:OtherObject,3:DuelSystem
HTvoid
CHTMainBar::HT_vMainBar_SetMySkill( HTint iSkillID, BYTE byActor, HTshort snSkillLevel )
{
	HTint iEmptyNo = 99;
	//	같은거 찿기
	for( HTint i=0 ; i<MYSKILL_COUNT ; i++ )
	{
		if( m_iMainBar_MySkillID[i] == iSkillID )
		{
			iEmptyNo = i;
			break;
		}
	}

	if( iEmptyNo == 99 )
	{
		for( i=0 ; i<MYSKILL_COUNT ; i++ )
		{
			if( m_iMainBar_MySkillID[i] == 0 )
			{
				iEmptyNo = i;
				break;
			}
		}
	}

	if( iEmptyNo != 99 )
	{
		HTint iSkill_BitmapID;

		//	지속시간을 구한다.
		if( byActor != 3 )
		{
			//HTbyte byLevel;
			//byLevel = 1;
			//if( byActor == 1 )
			//	byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( iSkillID );
			g_pParamMgr->HT_bGetPCSkillDuration( iSkillID, snSkillLevel, &m_iMainBar_MySkillDurationTime[iEmptyNo] );
			m_iMainBar_MySkillStartTime[iEmptyNo] = GetTickCount();

			//	ID 저장
			m_iMainBar_MySkillID[iEmptyNo] = iSkillID;
			//	스킬 UI아이콘 ID
			iSkill_BitmapID = g_pEngineHandler->HT_dwGetSkillUIID( m_iMainBar_MySkillID[iEmptyNo] );
		}
		else
		{
			m_iMainBar_MySkillStartTime[iEmptyNo] = GetTickCount();
			m_iMainBar_MySkillDurationTime[iEmptyNo] = 1000000;

			//	ID 저장
			m_iMainBar_MySkillID[iEmptyNo] = iSkillID;
			//	스킬 UI아이콘 ID
			iSkill_BitmapID = iSkillID;
		}

		g_cUIManager->HT_SetSlotImage( _DIALOG_BUFFSKILL, iEmptyNo, iSkill_BitmapID );
		m_bMainBar_MySkillBufWaring[iEmptyNo] = HT_TRUE;
		m_iMainBar_MySkillSaveBufWaringNo[iEmptyNo] = 0;
	}
}

//	나의스킬 끝나는 시간 Check
HTvoid
CHTMainBar::HT_vMainBar_MySkillEndTimeCheck()
{
	// 현재 시간을 구한다.
	DWORD dwPassTime = GetTickCount();
	HTint iRestTime;
	for( HTint i=0 ; i<MYSKILL_COUNT ; i++ )
	{
		if( m_iMainBar_MySkillID[i] )
		{
			iRestTime = (HTint)((m_iMainBar_MySkillStartTime[i]+m_iMainBar_MySkillDurationTime[i]) - dwPassTime);
			iRestTime = iRestTime/500;

			if( iRestTime <= 0 )
			{
				g_cUIManager->HT_SetSlotImage( _DIALOG_BUFFSKILL, i, 0 );
				m_iMainBar_MySkillID[i] = 0;
				m_iMainBar_MySkillStartTime[i] = 0;
				m_iMainBar_MySkillDurationTime[i] = 0;
			}
			else if( iRestTime <= 20 )
			{
				if( iRestTime != m_iMainBar_MySkillSaveBufWaringNo[i] )
				{
					m_iMainBar_MySkillSaveBufWaringNo[i] = iRestTime;
					if( m_bMainBar_MySkillBufWaring[i] )
					{
						m_bMainBar_MySkillBufWaring[i] = HT_FALSE;
						g_cUIManager->HT_SetSlotImage( _DIALOG_BUFFSKILL, i, 0 );
					}
					else
					{
						m_bMainBar_MySkillBufWaring[i] = HT_TRUE;
						HTint iSkill_BitmapID = g_pEngineHandler->HT_dwGetSkillUIID( m_iMainBar_MySkillID[i] );
						g_cUIManager->HT_SetSlotImage( _DIALOG_BUFFSKILL, i, iSkill_BitmapID );
					}
				}
			}
		}
	}
}

//	나의스킬 Init
HTvoid
CHTMainBar::HT_vMainBar_MySkillInit()
{
	//	나의 스킬
	for( HTint i=0 ; i<MYSKILL_COUNT ; i++ )
	{
		g_cUIManager->HT_SetSlotImage( _DIALOG_BUFFSKILL, i, 0 );
		m_iMainBar_MySkillID[i] = 0;
		m_iMainBar_MySkillStartTime[i] = 0;
		m_iMainBar_MySkillDurationTime[i] = 0;
		m_bMainBar_MySkillBufWaring[i] = HT_FALSE;
		m_iMainBar_MySkillSaveBufWaringNo[i] = 0;
	}
}

//	나의스킬 원하는 녀석만 Delete
HTvoid
CHTMainBar::HT_vMainBar_MySkillSetDelete( HTint iSkillID )
{
	for( HTint i=0 ; i<MYSKILL_COUNT ; i++ )
	{
		if( m_iMainBar_MySkillID[i] == iSkillID )
		{
			g_cUIManager->HT_SetSlotImage( _DIALOG_BUFFSKILL, i, 0 );
			m_iMainBar_MySkillID[i] = 0;
			m_iMainBar_MySkillStartTime[i] = 0;
			m_iMainBar_MySkillDurationTime[i] = 0;
			m_bMainBar_MySkillBufWaring[i] = HT_FALSE;
			m_iMainBar_MySkillSaveBufWaringNo[i] = 0;
			return;
		}
	}
}
