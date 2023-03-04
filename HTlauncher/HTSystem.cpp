#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTSystem.h"
#include "HTApplication.h"

#define _SYSTEM_GENERAL_SOUND	33531

HTSystem::HTSystem(void)
:m_bMyNameShow(HT_FALSE), m_bNPCNameShow(HT_FALSE),m_bOtherCharNameShow(HT_FALSE),
m_bRootingMode(HT_FALSE), m_bInitUI(HT_FALSE)
{
	m_iSelectSlideNo = -1;
	m_fBright = 0.5;
	m_fStreamVolume = 0.2;
	m_fSampleVolume = 0.5;
}

HTSystem::~HTSystem(void)
{
}

HTvoid HTSystem::HT_vSystem_CleanUp()
{
	m_bSystem_WindowActiveSw = HT_FALSE;
	g_cUIManager->HT_DeleteWindow( _DIALOG_OPTIONWND );
	m_bSystem_ExitSw = HT_FALSE;
}

HTvoid HTSystem::HT_vSystem_Init()
{
	//	Create Window
	this->HT_vSystem_CreateWindow();

	m_vSystem_WindowPos = HTvector3( MAINMENU_POSX, MAINMENU_POSY, 0 );
	m_bSystem_WindowActiveSw = HT_FALSE;

	m_bSystem_ExitSw = HT_FALSE;
	m_bSystem_ActiveSkillEffectSw = HT_FALSE;

	m_bMyNameShow = HT_FALSE; // 본인 이름 표시
	m_bNPCNameShow = HT_FALSE; // 몬스터, NPC 이름 표시
	m_bOtherCharNameShow = HT_FALSE; // 다른 플레이어 이름 표시
	m_bInitUI = HT_FALSE; // UI 초기화
	m_bShopModelMode = HT_FALSE;	//	개인상점 Model 모드
	m_bF1ToF10SlotMode = HT_TRUE;		//	F1-F10까지 슬롯/스킬 모드 변환

	m_bChattingMode = HT_FALSE;
	m_bMinimapMode = HT_TRUE;

	//----------주소록 활성화 / 비활성화----------//
	g_cAddress->HT_vSetOff();
}

//	Create Window
HTvoid HTSystem::HT_vSystem_CreateWindow()
{
	CHTString strMessage;
	//	[_DIALOG_OPTIONWND]
	//	Window
	g_cUIManager->HT_SetScriptMessage( eMsgOptionTitel, &strMessage, _T(""), _T("") );	//	Option
	g_cUIManager->HT_CreateWindow( _DIALOG_OPTIONWND, strMessage, 330, 466, g_cSystem->HT_vSystem_InputCheckSystem, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_OPTIONWND, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 8, 3, 37, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 8, 3, 92, 1400, 323, 5 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 8, 3, 305, 1400, 323, 5 );
	//	Texture 기본 옵션
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, eMsgOptionBasicOption, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );//기본옵션
	//	Texture 그래픽 옵션
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 9, 39, 88, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, eMsgOptionGraphOption, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 88, 90, 17 );//그래픽옵션
	//	Texture 사운드 옵션
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 9, 39, 300, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, eMsgOptionSoundOption, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 300, 90, 17 );//사운드옵션
	//	Texture 윈도우감마
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 10, 34, 120, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, eMsgOptionWindowAhlpa, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 34, 120, 79, 19 );//윈도우감마
	//	Texture 아이디표시
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 10, 34, 145, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, eMsgOptionShowID, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 34, 145, 79, 19 );//아이디표시
	//	Texture 임팩트
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 10, 34, 170, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, eMsgOptionEffect, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 34, 170, 79, 19 );//이펙트
	//	Texture 개인상점간소화
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 10, 34, 196, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, eMsgOptionSimpleShop, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 34, 196, 79, 19 );//상점간소화
	//	Texture 해상도
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 10, 34, 222, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, eMsgOptionResolution, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 34, 222, 79, 19 );//해상도
	//	Texture F1~F9
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 10, 34, 248, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, _T("F1~F9"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 34, 248, 79, 19 );//F1~F9
	//	Texture Character
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 10, 34, 274, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, _T("Character"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 34, 274, 79, 19 );//F1~F9
	//	Texture 효과음
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 10, 34, 328, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, eMsgOptionEffectSound, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 34, 328, 79, 19 );//Character
	//	Texture 배경음악
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 10, 34, 382, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, eMsgOptionBGM, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 34, 382, 79, 19 );//배경음악
	//	Texture 해상도 값
	// 해상도 추출
	CHTString strTemp;
	strTemp.HT_szFormat( "%dX%d", g_pEngineHandler->HT_iGetScreenWidth(), g_pEngineHandler->HT_iGetScreenHeight() );
	g_cUIManager->HT_AddTextureControl( _DIALOG_OPTIONWND, 0, 11, 115, 222, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 0, strTemp.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 115, 222, 79, 19 );

	//	Button 도움말
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 1, 159, 34, 56, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 1, eMsgSiegeHelp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 34, 56, 64, 19 );//도움말
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 1 );
	//	Button 재시작
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 2, 159, 125, 56, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 2, eMsgOptionReStart, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 125, 56, 64, 19 );//재시작
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 2 );
	//	Button 게임종료
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 3, 159, 217, 56, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 3, eMsgOptionExitGame, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 217, 56, 64, 19 );//게임종료
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 3 );
	//	Button 아이디 표시 On
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 4, 159, 115, 144, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 4, _T("ON"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 115, 144, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 4 );
	////	Button 아이디 표시 Off
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 5, 159, 181, 144, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 5, _T("OFF"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 181, 144, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 5 );
	//	Button 임펙트 표시 On
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 6, 159, 115, 170, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 6, _T("ON"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 115, 170, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 6 );
	//	Button 임펙트 표시 Off
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 7, 159, 181, 170, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 7, _T("OFF"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 181, 170, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 7 );
	//	Button 개인상점 간소화 On
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 8, 159, 115, 196, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 8, _T("ON"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 115, 196, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 8 );
	//	Button 개인상점 간소화 Off
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 9, 159, 181, 196, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 9, _T("OFF"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 181, 196, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 9 );
	//	Button F1~F10 기능 변경 On
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 13, 159, 115, 248, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 13, _T("Slot"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 115, 248, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 13 );
	//	Button F1~F10 기능 변경 Off
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 14, 159, 181, 248, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 14, _T("Skill"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 181, 248, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 14 );
	//	Button Character Show
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 15, 159, 115, 274, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 15, _T("Show"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 115, 274, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 15 );
	//	Button Character Hide
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 16, 159, 181, 274, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 16, _T("Hide"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 181, 274, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 16 );

	//	Button 적용
	g_cUIManager->HT_AddButtonControl( _DIALOG_OPTIONWND, 12, 159, 218, 423, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_OPTIONWND, 12, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 218, 423, 64, 19 );//확인
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_OPTIONWND, 12 );
	//	Scroll 윈도우 감마
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_OPTIONWND, 20, 119, 122, 173, 100, 1 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_OPTIONWND, 20, 34 );
	//	Scroll 효과음
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_OPTIONWND, 21, 34, 353, 173, 11, 1 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_OPTIONWND, 21, 4 );
	//	Scroll 배경음악
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_OPTIONWND, 22, 34, 407, 173, 11, 1 );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_OPTIONWND, 22, 4 );

	// 초기 설정
	g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 4, 1);
	g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 5, 2);

	g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 6, 1);
	g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 7, 2);

	g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 8, 2);
	g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 9, 1);

	m_iOption0 = 34;
	m_bOption1 = true;
	m_bOption2 = true;
	m_bOption3 = true;
	m_iOption4 = 4;
	m_iOption5 = 4;
	m_bOption6 = true;
	m_bOption7 = true;

}

//	입력함수 처리
void HTSystem::HT_vSystem_InputCheckSystem(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cSystem->HT_vSystem_ActiveSw();
		}
		//	Button 도움말
		else if( iTargetID == 1 )
		{
			g_cTutorialSystem->HT_vTutorial_SetHelpWnd();
		}
		//	Button 재시작
		else if( iTargetID == 2 )
		{
			//g_cChatting->HT_vChatting_WorkingMsg();
			g_byReStartButtonCode = _BTN_MSG_RESTART;
			g_pEngineHandler->HT_hrPlaySound(33523, 1);
			//	현재 서버와 연결 끊음
			g_pNetWorkMgr->DisConnect();
		}
		else if( iTargetID == 3 )
		{
			//	이미 서버와 연결이 끊어진 상태라면
			if( g_cGameSystem->HT_bGameSystem_GetServerStatus() == HT_TRUE )
			{
				PostQuitMessage( 0 );
			}
			else
			{
				g_byReStartButtonCode = _BTN_MSG_GAME_END;
				g_pEngineHandler->HT_hrPlaySound(33523, 1);
				//	현재 서버와 연결 끊음
				g_pNetWorkMgr->DisConnect();
			}
        }
		//	Button 아이디 표시 On
		else if( iTargetID == 4 )
		{
			g_cSystem->m_bOption1 = true;
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowName( HT_TRUE );
			g_cMainCharacter->HT_bMainChar_SetShowName( HT_TRUE );

			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 4, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 5, 2);
		}
		//	Button 아이디 표시 Off
		else if( iTargetID == 5 )
		{
			g_cSystem->m_bOption1 = false;
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowName( HT_FALSE );
			g_cMainCharacter->HT_bMainChar_SetShowName( HT_FALSE );

			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 4, 2);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 5, 1);
		}
		//	Button 임펙트 표시 On
		else if( iTargetID == 6 )
		{
			g_cSystem->m_bOption2 = true;
			g_cChatting->HT_vChatting_WorkingMsg();

			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 6, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 7, 2);
		}
		//	Button 임펙트 표시 Off
		else if( iTargetID == 7 )
		{
			g_cSystem->m_bOption2 = false;
			g_cChatting->HT_vChatting_WorkingMsg();

			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 6, 2);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 7, 1);
		}
		//	Button 개인상점 간소화 On
		else if( iTargetID == 8 )
		{
			g_cSystem->m_bOption3 = true;
			if( !g_cSystem->m_bShopModelMode )
			{
				g_cSystem->m_bShopModelMode = HT_TRUE;
				g_cOtherObjectSystem->HT_vOtherObjectSystem_SetChangeShopMode();
				if( g_cIndividualStore->HT_bIndividualStore_IsStoreMode() )
				{
					HTvector3 vecTempPos = g_cMainCharacter->HT_vecGetPosition();
					g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ModelID, HTvector3( vecTempPos.x,vecTempPos.y-200.0f,vecTempPos.z ) );
					g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ShopCharID, vecTempPos );
				}

				g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 8, 1);
				g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 9, 2);
			}
		}
		//	Button 개인상점 간소화 Off
		else if( iTargetID == 9 )
		{
			g_cSystem->m_bOption3 = false;
			if( g_cSystem->m_bShopModelMode )
			{
				g_cSystem->m_bShopModelMode = HT_FALSE;
				g_cOtherObjectSystem->HT_vOtherObjectSystem_SetChangeShopMode();
				if( g_cIndividualStore->HT_bIndividualStore_IsStoreMode() )
				{
					HTvector3 vecTempPos = g_cMainCharacter->HT_vecGetPosition();
					g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ShopCharID, HTvector3( 10,10,10 ) );
					g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ModelID, vecTempPos );
				}

				g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 8, 2);
				g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 9, 1);
			}
		}
		//	Button 확인
		else if( iTargetID == 10 )
		{
			g_cSystem->HT_vSystem_ActiveSw();
		}
		//	Button 취소
		else if( iTargetID == 11 )
		{
			g_cSystem->HT_vSystem_ActiveSw();
		}
		//	Button 적용
		else if( iTargetID == 12 )
		{
			g_cSystem->HT_vSystem_ActiveSw();
		}
		//	Button F1~F10 모드 Slot
		else if( iTargetID == 13 )
		{
			g_cSystem->m_bOption6 = true;
			g_cSystem->m_bF1ToF10SlotMode = HT_TRUE;
			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 13, 1);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 14, 2);
		}
		//	Button F1~F10 모드 Skill
		else if( iTargetID == 14 )
		{
			g_cSystem->m_bOption6 = false;
			g_cSystem->m_bF1ToF10SlotMode = HT_FALSE;
			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 13, 2);
			g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 14, 1);
		}
		//	Button Char Show
		else if( iTargetID  == 15 )
		{
			if( g_iInationalType == INATIONALTYPE_MEXICO )
			{
				g_cSystem->m_bOption7 = true;
				g_cOtherObjectSystem->HT_vOtherObjectSystem_SetObjectShow( TRUE );
				g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 15, 1);
				g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 16, 2);
			}
		}
		//	Button Char Hide
		else if( iTargetID  == 16 )
		{
			if( g_iInationalType == INATIONALTYPE_MEXICO )
			{
				g_cSystem->m_bOption7 = false;
				g_cOtherObjectSystem->HT_vOtherObjectSystem_SetObjectShow( FALSE );
				g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 15, 2);
				g_cUIManager->HT_SetButtonControlState(_DIALOG_OPTIONWND, 16, 1);
			}
		}
	}
	else if( iTarget == UI_TARGET_SCROLLBAR )
	{
		if( iTargetID == 20 )
		{
			g_cSystem->m_iOption0 = g_cUIManager->HT_GetScrollBarValue( _DIALOG_OPTIONWND, 20 );
			g_cUIManager->HT_SetWindowBackgroundColor(g_cSystem->m_iOption0);
			//g_cChatting->HT_vChatting_WorkingMsg();
		}
		else if( iTargetID == 21 )
		{
			g_cSystem->m_iOption4 = g_cUIManager->HT_GetScrollBarValue( _DIALOG_OPTIONWND, 21 );
			g_pEngineHandler->HT_hrSetSampleVolume( float(g_cSystem->m_iOption4) / 10.0f );
		}
		else if( iTargetID == 22 )
		{
			g_cSystem->m_iOption5 = g_cUIManager->HT_GetScrollBarValue( _DIALOG_OPTIONWND, 22 );
			g_pEngineHandler->HT_hrSetStreamVolume( float(g_cSystem->m_iOption5) / 10.0f );
		}
		else if( iTargetID == 23 )
		{
			//g_cChatting->HT_vChatting_WorkingMsg();
			
			//HTint iRate = g_cUIManager->HT_GetScrollBarValue( _DIALOG_OPTIONWND, 23 );
			//g_cUIManager->HT_SetWindowBackgroundColor(iRate);

			//g_pEngineHandler->HT_hrChangeScreenBrightness( 0.4f + (HTfloat)iRate*0.05f );
		}
	}
}

//----------활성화 / 비활성화----------//
HTvoid HTSystem::HT_vSystem_ActiveSw()
{
	if( m_bSystem_WindowActiveSw == HT_TRUE )
	{
		m_bSystem_WindowActiveSw = HT_FALSE;
		g_cUIManager->HT_HideWindow(_DIALOG_OPTIONWND);
	}
	else
	{
		m_bSystem_WindowActiveSw = HT_TRUE;
		g_cUIManager->HT_ShowWindow(_DIALOG_OPTIONWND);
		g_pEngineHandler->HT_hrPlaySound( _SYSTEM_GENERAL_SOUND, 1 );	// Click Sound
	}
}

//	ESC Key 누르면 시스템창 닫기
HTvoid HTSystem::HT_vSystem_ESC_CloseWindow()
{
	m_bSystem_WindowActiveSw = HT_TRUE;
	//----------활성화 / 비활성화----------//
	HT_vSystem_ActiveSw();
}
