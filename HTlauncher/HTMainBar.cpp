//======================================================================
// HTMainBar.h
// ȭ�� �ϴ��� ���� ��
// (��)�Ѻ�����Ʈ ���Ӱ����� ����		2003.03.07
//======================================================================

#include "stdafx.h"
#include "HTextern.h"
#include "HTControlDef.h"
#include "HTEngineHandler.h"
#include "HTMainBar.h"


CHTMainBar::CHTMainBar()
{
	//	��ų �� ī��Ʈ
	m_nSkillTotalCount = 31;

	m_iActiveSkillID = -1;
	m_iActionSkillID = -1;

	m_strHP.HT_hrCleanUp();
	m_strPRANA.HT_hrCleanUp();

	m_dwNeedPrana = 0;

	// ���ο�UI����(20030728)
	m_iCurChacra	= 0;
	m_iTotalPrana	= 0;

	//	������ ����� �̸�
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
	
	//	������Ʈ ���ڿ� HP�� �׸��� �ʰ� �ϴ�
	this->HT_vSetObjectHPOut();
	//	������Ʈ ���ڿ� Name�� �׸��� �ʰ� �ϴ�
	this->HT_vSetObjectNameOut();

	//	Ÿ�Ľ�
	m_iMainBar_MaxTP = 0;
	m_iMainBar_CurTP = 0;

	//	���� ��ų
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

	// �ػ� ����
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
	//	���ʹ�
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
		g_cUIManager->HT_SetScriptMessage( eMsgMainCheckPrimiumBuy, &strMessage, _T(""), _T("") );	//	�����̾� ������
		g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 1, strMessage );
		g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 1 );
	}
	//	Button Status, Inventory, Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 2, 37, 52-m_iForDelPriminumIconX, 4, 38, 36 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckCharacInfo, &strMessage, _T(""), _T("") );	//	ĳ���� ����(L)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 2, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 2 );
	//	Button Inventory, Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 3, 40, 90-m_iForDelPriminumIconX, 4, 41, 39 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckInventory, &strMessage, _T(""), _T("") );	//	�κ��丮(I)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 3, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 3 );
	//	Button Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 4, 43, 128-m_iForDelPriminumIconX, 4, 44, 42 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckQuest, &strMessage, _T(""), _T("") );	//	����Ʈ(U)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 4, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 4 );
	//	Button Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 5, 46, 166-m_iForDelPriminumIconX, 4, 47, 45 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckSkill, &strMessage, _T(""), _T("") );	//	��ų(K)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 5, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 5 );
	//	Button System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 6, 49, 204-m_iForDelPriminumIconX, 4, 50, 48 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckOption, &strMessage, _T(""), _T("") );	//	�ý���(ESC)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 6, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 6 );
	//	Button Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 7, 52, 242-m_iForDelPriminumIconX, 4, 53, 51 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckCommand, &strMessage, _T(""), _T("") );	//	���(C)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 7, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 7 );
	//	Button PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 8, 55, 280-m_iForDelPriminumIconX, 4, 56, 54 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckPK, &strMessage, _T(""), _T("") );	//	PK
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 8, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 8 );
	//	Button ������
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINBAR, 9, 154, 316-m_iForDelPriminumIconX, 4, 155, 176 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonChangeStyle, &strMessage, _T(""), _T("") );	//	��纯��
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MAINBAR, 9, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MAINBAR, 9 );

	//	[_DIALOG_MINIMAINBAR]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_MINIMAINBAR, _T(""), 188-m_iForDelPriminumIconX, 39, g_pMainBar->HT_vMainBar_InputCheckForMainBar, 0 );
	g_cUIManager->HT_MoveWindow( _DIALOG_MINIMAINBAR, m_iScreenWidth-152, m_iScreenHIGHT-40-16 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_MINIMAINBAR, TRUE, 0,0, 11,38 );
	//	���ʹ�
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
		g_cUIManager->HT_SetScriptMessage( eMsgMainCheckPrimiumBuy, &strMessage, _T(""), _T("") );	//	�����̾� ������
		g_cUIManager->HT_SetButtonToolTip( _DIALOG_MINIMAINBAR, 1, strMessage );
		g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MINIMAINBAR, 1 );
	}
	//	Button Status, Inventory, Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MINIMAINBAR, 3, 40, 52-m_iForDelPriminumIconX, 4, 41, 39 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckInventory, &strMessage, _T(""), _T("") );	//	�κ��丮(I)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MINIMAINBAR, 3, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MINIMAINBAR, 3 );
	//	Button Inventory, Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MINIMAINBAR, 6, 49, 90-m_iForDelPriminumIconX, 4, 50, 48 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckOption, &strMessage, _T(""), _T("") );	//	�ý���(ESC)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MINIMAINBAR, 6, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MINIMAINBAR, 6 );
	//	Button Quest, Skill, System, Command, PK
	g_cUIManager->HT_AddButtonControl( _DIALOG_MINIMAINBAR, 7, 52, 128-m_iForDelPriminumIconX, 4, 53, 51 );
	g_cUIManager->HT_SetScriptMessage( eMsgMainCheckCommand, &strMessage, _T(""), _T("") );	//	���(C)
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MINIMAINBAR, 7, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MINIMAINBAR, 7 );
	//	Button ������
	g_cUIManager->HT_AddButtonControl( _DIALOG_MINIMAINBAR, 9, 154, 164-m_iForDelPriminumIconX, 4, 155, 176 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonChangeStyle, &strMessage, _T(""), _T("") );	//	��纯��
	g_cUIManager->HT_SetButtonToolTip( _DIALOG_MINIMAINBAR, 9, strMessage );
	g_cUIManager->HT_SetButtonToolTipOn( _DIALOG_MINIMAINBAR, 9 );

	//	[MainChar HP Bar]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_MAINCHARHP, _T(""), 169, 74, g_pMainBar->HT_vMainBar_InputCheckForMainCharHP, 0,HT_COLOR( 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 70.0f/100.0f ) );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_MAINCHARHP, TRUE, 3,3, 163, 14 );
	g_cUIManager->HT_MoveWindow( _DIALOG_MAINCHARHP, 38, 0 );
	g_cUIManager->HT_AddButtonControl( _DIALOG_MAINCHARHP, 13, 0, 0, 0, 0, 0, 1500, 169, 72 );
	//	Texture �ܰ� ����
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
	//	Texture �ܰ� ����
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

//	�Է� �޼��� ó��
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
			//	���� �ʾ�������
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )		g_cStatus->HT_vStatus_ActiveSw();
		}
		//	Inventory
		else if( iTargetID == 3 )
		{
			//	�׾������� �����ʾ������� ��� ó��
			g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
		}
		//	Quest
		else if( iTargetID == 4 )
		{
			//	���� �ʾ�������
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )		g_cQuest->HT_vQuest_ActiveSw();
		}
		//	Skill
		else if( iTargetID == 5 )
		{
			//	���� �ʾ�������
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )		g_cSkillInventory->HT_vSkillInventoryActiveCheck( 0x00 );
		}
		//	System
		else if( iTargetID == 6 )
		{
			//	���� �ʾ�������
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
			//	���� �ʾ�������
			if( g_cMainCharacter->HT_vMainChar_GetCharLive() )		g_cCommand->HT_vCommand_WndActiveSw();
		}
		//	PK
		else if( iTargetID == 8 )
		{
			//	�ֽ��� ���������� �ǹ̰� ����.
			if( HT_SUCCEED( HT_extern_TrimuritiZone( g_wResentZoneServerID ) ) )
				return;
			//	����� ���������� �ǹ̰� ����.
			if( HT_SUCCEED( HT_extern_ForetressZone( g_wResentZoneServerID ) ) )
				return;
			//	For PK Button
			g_pMainBar->HT_vMainBar_GameSystem_SetForPKButton();
		}
		//	��纯��
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

	//	PK Button �� �������� ������ �˷���
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
			// [���]PK�� �ϸ� �ٸ� �÷��̾�κ��� ���� �ްԵǸ� ����ġ�� �������� �ҰԵ˴ϴ�.
			HT_g_Script_SetMessage( eMsgAttackPKWarning, &szMessage);
			g_cUIManager->HT_MessageBox( _DIALOG_PRANABAR, szMessage.HT_szGetString(), 0 );
		}
		//	Pk Button Turn On
		g_cUIManager->HT_SetButtonControlState( _DIALOG_MAINBAR, 8, 1 );
	}
	else
	{
		// PK ��尡 �����Ǿ����ϴ�.
		HT_g_Script_SetMessage( eMsgAttackPKModeCancel, &szMessage);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		//	Pk Button Turn Off
		g_cUIManager->HT_SetButtonControlState( _DIALOG_MAINBAR, 8, 0 );
	}
}

//	���ι�_�����췯
HTvoid CHTMainBar::HT_vMainBar_Control( HTfloat fElapsedTime )
{
	this->HT_vMainBar_MySkillEndTimeCheck();
}

//	������Ʈ ���ڿ� �ؽ�Ʈ�� ����.
HTvoid CHTMainBar::HT_vSetObjectTextDraw( CHTString strTemp )
{
	// �ƹٶ�ī���� ��� ��������� ���� ���� ��¾���
	if (strcmp(strTemp, "�ƹٶ�ī��") != 0)
	{
		//	Edit Other Name
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_MAINCHARHP, 2, strTemp.HT_szGetString() );
	}

	//	������ ����� �̸�
	m_strPickObjectName = strTemp.HT_szGetString();
}

//	������Ʈ ���ڿ� HP�� �׸���.
HTvoid CHTMainBar::HT_vSetObjectHPDraw( HTint nResentHP, HTint nMaxHP )
{
	if( HT_SUCCEED( g_cItemSystem->HT_hrItemSystem_GetSameNameCheck( m_strPickObjectName.HT_szGetString() ) ) )
		return;

	if( nResentHP<=0 || nResentHP>nMaxHP || nMaxHP<=0 )
		return;

	//====================================================================================
	// ���ο�UI����(20030728)
	//====================================================================================
	// HP %���
	//HTvector3 vecScale;
	//vecScale = HTvector3(1.0f, 1.0f, 1.0f);

	HTfloat xPos = (HTfloat)nResentHP/(HTfloat)nMaxHP;
	if( xPos>1.0f)		xPos = 1.0f;
	else if( xPos<0.0f)	xPos = 0.0f;

	// HP �� ������ HP�� ���� ���׶� HP�� �׸���, �ƴϸ� �׸��� �ʴ´�.
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

//	������Ʈ ���ڿ� HP�� �׸��� �ʰ� �ϴ�
HTvoid CHTMainBar::HT_vSetObjectHPOut()
{
	//	Del Texture HP
	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_MAINCHARHP, 12, HT_FALSE );
}

//	������Ʈ ���ڿ� Name�� �׸��� �ʰ� �ϴ�
HTvoid CHTMainBar::HT_vSetObjectNameOut()
{
	//	Edit Other Name
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_MAINCHARHP, 2, _T("") );
}

// ���� ������ ������Ʈ �Ѵ�.
HTvoid CHTMainBar::HT_vPranaUpdate( HTint iTotalPrana )
{
	//	������ ���
	HTfloat fRatio;

	if (m_dwNeedPrana==0) fRatio = 1.0f;
	else fRatio = (HTfloat)iTotalPrana/(HTfloat)m_dwNeedPrana;
	if (fRatio>1.0f)	fRatio = 1.0f;

	// ����
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

// HP ������ ������Ʈ �Ѵ�.
HTvoid CHTMainBar::HT_vHPUpdate(HTint iCurHP, HTint iMaxHP )
{
	//	������ ���
	HTfloat fRatio = (HTfloat)iCurHP/(HTfloat)iMaxHP;
	if( fRatio > 1.0f )			fRatio = 1.0f;
	else if( fRatio < 0.0f )	fRatio = 0.0f;

	// ���࿡ ���� HP ������ ������Ʈ �Ѵ�.
	this->HT_vMainBar_SetCurTransparent( iCurHP, iMaxHP );

	// HP ���� �ؽ�Ʈ �غ�
	CHTString strHP;
	strHP.HT_szFormat( "%d/%d", iCurHP, iMaxHP );
	//	Edit MainChar HP
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_MAINCHARHP, 3, strHP.HT_szGetString() );
}

// ���࿡ ���� HP ������ ������Ʈ �Ѵ�.
HTvoid
CHTMainBar::HT_vMainBar_SetCurTransparent( HTint iCurHP, HTint iMaxHP )
{
	if( iCurHP == 0 )
	{
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_MAINCHARHP, 10, HT_FALSE );
	}
	else
	{
		//	������ ���
		HTfloat fRatio = (HTfloat)iCurHP/(HTfloat)iMaxHP;
		if( fRatio > 1.0f )			fRatio = 1.0f;
		else if( fRatio < 0.0f )	fRatio = 0.0f;

		//	Texture HP
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_MAINCHARHP, 10, HT_TRUE );
		g_cUIManager->HT_SetTextureControlScale( _DIALOG_MAINCHARHP, 10, 164*fRatio, 15 );
	}
}

//--------------------------------------------------------------
// D : Ÿ�Ľ�
//--------------------------------------------------------------
//	Cur TP ����
HTvoid
CHTMainBar::HT_vMainBar_SetCurTP( HTint iCurTP, HTint iMaxTP )
{
	if( iMaxTP > 0 ) 
        m_iMainBar_MaxTP = iMaxTP;
	m_iMainBar_CurTP = iCurTP;

	HTvector3 vecScale;
	vecScale = HTvector3(1.0f, 1.0f, 1.0f);

	// TP %���
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

	// TP ���� �ؽ�Ʈ �غ�
	CHTString strTP;
	strTP.HT_szFormat( "%d/%d", m_iMainBar_CurTP, m_iMainBar_MaxTP );
	//	Edit MainChar TP
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_MAINCHARHP, 4, strTP.HT_szGetString() );
}

//	���ǽ�ų ����
//	byActor 1:MainChar,2:OtherObject,3:DuelSystem
HTvoid
CHTMainBar::HT_vMainBar_SetMySkill( HTint iSkillID, BYTE byActor, HTshort snSkillLevel )
{
	HTint iEmptyNo = 99;
	//	������ �O��
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

		//	���ӽð��� ���Ѵ�.
		if( byActor != 3 )
		{
			//HTbyte byLevel;
			//byLevel = 1;
			//if( byActor == 1 )
			//	byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( iSkillID );
			g_pParamMgr->HT_bGetPCSkillDuration( iSkillID, snSkillLevel, &m_iMainBar_MySkillDurationTime[iEmptyNo] );
			m_iMainBar_MySkillStartTime[iEmptyNo] = GetTickCount();

			//	ID ����
			m_iMainBar_MySkillID[iEmptyNo] = iSkillID;
			//	��ų UI������ ID
			iSkill_BitmapID = g_pEngineHandler->HT_dwGetSkillUIID( m_iMainBar_MySkillID[iEmptyNo] );
		}
		else
		{
			m_iMainBar_MySkillStartTime[iEmptyNo] = GetTickCount();
			m_iMainBar_MySkillDurationTime[iEmptyNo] = 1000000;

			//	ID ����
			m_iMainBar_MySkillID[iEmptyNo] = iSkillID;
			//	��ų UI������ ID
			iSkill_BitmapID = iSkillID;
		}

		g_cUIManager->HT_SetSlotImage( _DIALOG_BUFFSKILL, iEmptyNo, iSkill_BitmapID );
		m_bMainBar_MySkillBufWaring[iEmptyNo] = HT_TRUE;
		m_iMainBar_MySkillSaveBufWaringNo[iEmptyNo] = 0;
	}
}

//	���ǽ�ų ������ �ð� Check
HTvoid
CHTMainBar::HT_vMainBar_MySkillEndTimeCheck()
{
	// ���� �ð��� ���Ѵ�.
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

//	���ǽ�ų Init
HTvoid
CHTMainBar::HT_vMainBar_MySkillInit()
{
	//	���� ��ų
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

//	���ǽ�ų ���ϴ� �༮�� Delete
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
