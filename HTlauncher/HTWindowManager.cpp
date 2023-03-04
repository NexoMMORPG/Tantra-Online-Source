

#include "stdafx.h"
#include "imm.h"
#include "HTextern.h"
#include "HTWin32Window.h"
#include "resource.h"
#include "HTEngineHandler.h"
#include "HTWindowManager.h"
#include "HTConsole.h"
#include <process.h>

#define _STARTUP_FILEPATH	_T("system\\HTStartup.cfg")

#define NATIONALCODE_KOREA		1
#define NATIONALCODE_JAPAN		2
#define NATIONALCODE_CHNIA_1	3

#define NATIONAL_CODE			NATIONALCODE_CHNIA_1


CHTWindowManager::CHTWindowManager()
{
	m_bPrintScreenShot = HT_FALSE;
	m_bEnableCrashSender = HT_TRUE;
	//	IME 관련
	//	제 특수문자 목록의 최대 겟수
	m_iCanMax = 0;
	//	현제의 특수문자 위치
	m_iCandiGroupNumber = 0;
	m_iCandiCharNumber = 1;
	//  특수문자가 들어갈 변수 초기화
	memset(m_szCanText,0,100);
	//	문자를 만들기 위해 입력하는 영문을 저장
	m_strCharSaveForAlpha.HT_hrCleanUp();
	//	조합된 문자
	m_strCompositionString.HT_hrCleanUp();
}

CHTWindowManager::~CHTWindowManager()
{
}

HTRESULT CHTWindowManager::Initialize(  HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, HTint nCmdShow )
{
	m_eh.SetConnectionPoint(this);

	HT_g_vLogFile("CHTWindowManager::Load configuration file...\n");

	g_pCfgSys = new CHTConfigSystem;
	// 설정 파일을 불러옴
	if ( HT_FAILED( g_pCfgSys->HT_hrLoad( _STARTUP_FILEPATH ) ) )
	{
		MessageBox( NULL, "Cannot find HTStartup.cfg!", "HTLauncher", MB_OK );
		return HT_FAIL;
	}

	HT_CHECK( g_pCfgSys->HT_hrGetValue( _T("RENDERER"), _T("windowed"), &m_bWindowed ) );
	// window 생성 및 엔진 초기화 
	if ( HT_FAILED( HT_hrCreate( hInstance, hPrevInstance, HT_NULL, 
												lpCmdLine, nCmdShow ) ) )	
	{
		return HT_FAIL;
	}
	HT_g_vLogFile("HT_hrCreate success!\n");

	//	게임 메니져를 초기화 시켜준다.
    HT_hrGMInit();

    // Load keyboard accelerators
    hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );

	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

	//	IME를 초기화 한다.
	g_cImeMgr.InitInput( g_hWnd );

	HT_g_vLogFile("CHTWindowManager::Initialize success!\n");
   
	return ( HT_OK );
}

//----------게임 클리어 하기----------//
void CHTWindowManager::Finalize()
{
	// 이 값이 TRUE 인 상태에서만 CrashSender 가 작동한다.
	// 종료시에 죽는 클라이언트가 많이 발생하는데 그리 치명적인 문제가 아니라고 판단하여,
	// 종료시 죽는 클라이언트의 Crash를 무시하기 위해 만들었다.
	m_bEnableCrashSender = HT_FALSE;

	//----------로그파일----------//
	HT_g_vLogFile("CHTWindowManager::Finalize start\n");
	// 설정 파일을 저장 (변경 된 내용 등을 저장함)
	g_pCfgSys->HT_hrSave( _T("HTStartup.cfg") );
	HT_DELETE( g_pCfgSys );

	HT_g_vLogFile("CHTWindowManager::Finalize 1\n");
	// 커서를 다시 보이게 한다.
	ShowCursor( TRUE );
	//----------게임 클리어 하기_클라이언트----------//
	HT_g_vLogFile("CHTWindowManager::Finalize 2\n");
	ClientCleanup();
	HT_g_vLogFile("CHTWindowManager::Finalize 3\n");
	//----------엔진----------//
	HT_hrCleanup();
	HT_g_vLogFile("CHTWindowManager::Finalize 4\n");
	//----------로그파일----------//
	HT_g_vLogFile("CHTWindowManager::Finalize success!\n");

	// 다음의 경우는 인트로에서 그냥 나갈때 삭제되지 않는 Objects 을 제거하도록 하기 위함이다. (선영범)
	HT_DELETE(g_pParamMgr);
	HT_DELETE(g_pMessageMgr);
	HT_DELETE(g_BasicLoadingInfo);
	HT_DELETE(g_cLoading);

	HT_DELETE(g_cInterfaceCheck);

	HT_DELETE(g_pCfgSys);
	HT_DELETE(g_cUIManager);
	HT_DELETE(g_poWebLogIn);

	//----------네트웍 초기화----------//
	HT_DELETE( g_pNetWorkMgr );
	HT_DELETE( g_pNetMsg );
}

//----------게임 클리어 하기_클라이언트----------//
void CHTWindowManager::ClientCleanup()
{
}

HTRESULT CHTWindowManager::ReadyGameLoop()
{
	//	Init Intro
	g_cIntroManager	= HT_NULL;
	g_cIntroManager	= new CHTIntroManager;

	//	Set Game Sequnce
	g_iGameSequnce = 1;

	//	Set Logo
	HT_g_vLogFile("CHTWindowManager::ReadyGameLoop start!\n");

	//	인트로 최초 한번 업데이트 -> 내가 코딩한것 같은데 왜 한건지 모르겠다.
	HT_hrReadyGameControl();

	//	Set Logo
	HT_g_vLogFile("HT_hrReadyGameControl 1 \n");

	while (WM_QUIT != msg.message)
	{
		HTRESULT hr = HT_OK;
		// Control for Ready loop
		hr = HT_hrReadyGameControl();

		// 로그인 과정을 모두 마친 경우 다음으로 히행
		if(hr == RETURNTYPE_INTRO_COMPLETE)
			return RETURNTYPE_INTRO_COMPLETE;

		// 로그인에서 exit 한 경우 더이상 실행하지 않고 끝냄
		else if(hr == RETURNTYPE_EXIT_INTRO)
			return RETURNTYPE_EXIT_INTRO;

		// Use PeekMessage() if the app is active, so we can use idle time to
        // render the scene. Else, use GetMessage() to avoid eating CPU time.
		if( HT_bIsActive() )
			bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE )? true: false;
		else
			bGotMsg = GetMessage( &msg, NULL, 0U, 0U )? true: false;

		if( bGotMsg )
		{
			// Translate and dispatch the message
			if( 0 == TranslateAccelerator( m_hWnd, hAccel, &msg ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{
			// Render a frame during idle time (no messages are waiting)
			if ( HT_bIsActive() )
			{
				if( HT_FAILED( HT_hrUpdate() ) )
				{
					MessageBox( HT_NULL, _T("HT_hrUpdate FAIL!"), _T("g_pLauncher"), MB_OK );
					break;
				}

				// 렌더링 순서와 동기화를 맞추는 작업을 하는 것이다.
				if ( m_bPrintScreenShot )
				{
					g_pEngineHandler->HT_hrPrintScreenShot();
					m_bPrintScreenShot = HT_FALSE;
				}

				if( HT_FAILED( HT_hrRender_Ready() ) )
				{
					MessageBox( HT_NULL, _T("HT_hrRender FAIL!"), _T("g_pLauncher"), MB_OK );
					break;
				}
			}
		}
	}

	return HT_OK;
}

HTRESULT CHTWindowManager::MainGameLoop()
{
	g_iGameSequnce = 2;
	HT_g_vLogFile("CHTWindowManager::MainGameLoop start\n");

	//	Set Language
	g_cImeMgr.vImeMgr_SetLanguage( HT_FALSE, IME_CMODE_ALPHANUMERIC );

	// 서버에 캐릭터 초기화 정보를 요청한다_이니트 메인캐릭터,
	// 시간 초기화를 좀 더 비슷하게 하기 위하여 순서를 뒷쪽으로 빼었다. (20030109Tenma)
	g_iRequestCharacterInitCount = 1;
	g_cInitConntion_StartTime = GetTickCount();
	g_byInitConnectType = CONNECT_TYPE_FIRST;
	CHTNetWorkHandle::HT_hrNetWorkInit_InitChar( CONNECT_TYPE_FIRST, 0, g_oMainCharacterInfo.szCharName, _T("") );
	HT_g_vLogFile("-InitRequestChar");

	// 최초 업데이트 : 최초의 타이머 값이 쓰레기값으로 넘어오는 것을 처리한다.
	HT_hrUpdate();

	while (WM_QUIT != msg.message)
	{
		//	Main Logic
		HTRESULT hr = HT_hrMainGameControl();
		if( hr == RETURNTYPE_EXIT_MAINGAME )
			return RETURNTYPE_EXIT_MAINGAME;

		// Render a frame during idle time (no messages are waiting)
		if ( HT_bIsActive() )
		{
			if( g_bMainCharacterInitialized )
			{
				if( HT_FAILED( HT_hrUpdate() ) )
				{
					MessageBox( HT_NULL, _T("HT_hrUpdate FAIL!"), _T("g_pLauncher"), MB_OK );
					break;
				}
			}

			// 렌더링 순서와 동기화를 맞추는 작업을 하는 것이다.
			if ( m_bPrintScreenShot )
			{
				g_pEngineHandler->HT_hrPrintScreenShot();
				m_bPrintScreenShot = HT_FALSE;
			}

			if( HT_FAILED( HT_hrMainGameRender() ) )
			{
				MessageBox( HT_NULL, _T("HT_hrRender FAIL!"), _T("g_pLauncher"), MB_OK );
				break;
			}
		}
		
		// Use PeekMessage() if the app is active, so we can use idle time to
        // render the scene. Else, use GetMessage() to avoid eating CPU time.
		if ( HT_bIsActive() )
		{
			while ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				if ( msg.message == WM_QUIT )
				{
					break;
				}
				// Translate and dispatch the message
				if( 0 == TranslateAccelerator( m_hWnd, hAccel, &msg ) )
				{
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				}
			}
		}
		else
		{
			// Translate and dispatch the message
			if ( GetMessage( &msg, NULL, 0U, 0U ) )
			{
				if ( msg.message == WM_QUIT )
				{
					break;
				}

				if( 0 == TranslateAccelerator( m_hWnd, hAccel, &msg ) )
				{
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				}
			}
		}
	}

	return HT_OK;
}

//====================================================================//
//		    	      윈도우와 관련한 함수		 		           	  //
//====================================================================//
LRESULT CHTWindowManager::HT_OnClose(WPARAM wParam, LPARAM lParam)
{
	HT_g_vLogFile("CHTWindowManager::HT_OnClose success\n");

	//	Close Log File
	HT_g_vCloseDebugFile();

	PostQuitMessage(0);
	// Notify the message was processed
	return 0;
}


LRESULT CHTWindowManager::HT_OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	// Tantra V3 UIManager 우선 처리
	if (g_cUIManager) 
		if (g_cUIManager->OnKeyDown(wParam)) return 0;

	if (wParam == 35) return 0;	// End 키를 누르면 무조건 그냥 리턴한다. (이는 UI 시스템 내부적으로도 필요에 의해 호출하기 때문)

	//g_imsi_button[5] = wParam;
	if( g_bOneTimeUpdate == GAMESEQUNCE_MAINGAME_GMAEPLAY )	
	{
		switch( wParam )
		{
			case VK_CONTROL:
				if( g_bOneTimeUpdate == GAMESEQUNCE_MAINGAME_GMAEPLAY )
					g_cInterfaceCheck->HT_vInterface_SetControlKey( HT_TRUE );
				break;
			case 0x51 : //ALPAHBAT_KEYVALUE_Q :
				// 개발중 모드일 때만 디버그용 문자열을 출력하도록 한다.
				if( g_bDevelopingMode )
				{
					if( g_bHelp_Text == HT_TRUE )
						g_bHelp_Text = HT_FALSE;
					else
						g_bHelp_Text = HT_TRUE;
				}
				break;
			//	기타 특수키들을 게임중에 처리
			default :
				//	채팅창이 활성화 상태가 아닐때
				if( !g_cChatting->HT_bChatting_GetChatEditFocus() )
				{
					if( g_iInationalType != INATIONALTYPE_JAPEN )
					{
						g_cInterfaceCheck->HT_hrInterfaceKeyboard_Input_KeyDown( wParam );
						g_cInterfaceCheck->HT_hrInterfaceKeyboard_Input_FunctionKey(wParam);
					}
				}
				else
				{
					g_cChatting->HT_vChatting_SetHistoryFunction( wParam );
				}
				break;
		}
	}

	// Notify the message was processed
	return 0;
}

LRESULT CHTWindowManager::HT_OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	// Tantra V3 UIManager 우선 처리
	if (g_cUIManager) 
		if (g_cUIManager->OnKeyUp(wParam)) return 0;

	switch ( wParam ) 
	{
		case VK_CONTROL:
			if( g_bOneTimeUpdate == GAMESEQUNCE_MAINGAME_GMAEPLAY )
				g_cInterfaceCheck->HT_vInterface_SetControlKey( HT_FALSE );
			break;
		case VK_SNAPSHOT:
			m_bPrintScreenShot = HT_TRUE;
			break;
		case VK_OEM_AUTO:
			g_cImeMgr.bImeMgr_SetEmForJapan( 1 );
			break;
		case VK_OEM_ENLW:
			g_cImeMgr.bImeMgr_SetEmForJapan( 0 );
			break;
		//case WM_FONTCHANGE:
		//	break;
		default:
			if( g_bOneTimeUpdate == GAMESEQUNCE_MAINGAME_GMAEPLAY )
			{
				//	채팅창이 활성화 상태가 아닐때
				if( !g_cChatting->HT_bChatting_GetChatEditFocus() )
				{
					if( g_iInationalType == INATIONALTYPE_JAPEN )
					{
						g_cInterfaceCheck->HT_hrInterfaceKeyboard_Input_KeyDown( wParam );
						g_cInterfaceCheck->HT_hrInterfaceKeyboard_Input_FunctionKey(wParam);
					}
				}
			}
			break;
	}

	// Notify the message was processed
	return 0;
}

LRESULT CHTWindowManager::HT_OnChar(WPARAM wParam, LPARAM lParam)
{
	// Tantra V3 UIManager 우선 처리
	if (g_cUIManager)
	{
		//	Set ImeMgr
		if( g_cImeMgr.OnChar( wParam, lParam) == 0 )
            g_cImeMgr.InputString();
		
		//if (g_cUIManager->OnChar(wParam)) return 0;
	}

    // Notify the message was processed
	return 0;
}


//	Ime를 위하여 지금 입력 가능한 상태인지 체크
//	이러한 코딩이 삽입된 이유는 IME처리부에서 채팅 입력상태가 아닌데 IME 윈도가 떠는것을 막기 위함이다.
HTRESULT CHTWindowManager::HT_rhInputCheckForIme()
{
	if( g_cUIManager )
	{
		if( g_cUIManager->HT_isFocusOnEditBoxControl() )
			return HT_OK;
		else
			return HT_FAIL;
	}

    return HT_FAIL;
}

//	IME 처리
LRESULT CHTWindowManager::HT_OnIME_Compositon(WPARAM wParam, LPARAM lParam)
{
	//	이러한 코딩이 삽입된 이유는 IME처리부에서 채팅 입력상태가 아닌데 IME 윈도가 떠는것을 막기 위함이다.
	if( HT_SUCCEED( this->HT_rhInputCheckForIme() ) )
	{
		g_cImeMgr.OnComposition( m_hWnd, wParam, lParam);
		g_cImeMgr.InputString();
		if( g_iInationalType == INATIONALTYPE_KOREA || g_iInationalType == INATIONALTYPE_JAPEN )
			return 0;
		else
			return DefWindowProc( m_hWnd, WM_IME_COMPOSITION, wParam, lParam );
	}
	else
	{
        return 0;
	}
}

LRESULT	CHTWindowManager::HT_OnIME_StartComPosition(WPARAM wParam, LPARAM lParam)
{
	//	이러한 코딩이 삽입된 이유는 IME처리부에서 채팅 입력상태가 아닌데 IME 윈도가 떠는것을 막기 위함이다.
	if( HT_SUCCEED( this->HT_rhInputCheckForIme() ) )
	{
		if( g_iInationalType == INATIONALTYPE_KOREA || g_iInationalType == INATIONALTYPE_JAPEN )
			return 0;
		else
		{
			g_cImeMgr.SetIMEWndPos();
			return DefWindowProc( m_hWnd, WM_IME_STARTCOMPOSITION, wParam, lParam );
		}
	}
	else
	{
		return 0;
	}
}

LRESULT	CHTWindowManager::HT_OnIME_EndComPosition(WPARAM wParam, LPARAM lParam)
{
	//	이러한 코딩이 삽입된 이유는 IME처리부에서 채팅 입력상태가 아닌데 IME 윈도가 떠는것을 막기 위함이다.
	if( HT_SUCCEED( this->HT_rhInputCheckForIme() ) )
	{
		if( g_iInationalType == INATIONALTYPE_KOREA || g_iInationalType == INATIONALTYPE_JAPEN )
			return 0;
		else
            return DefWindowProc( m_hWnd, WM_IME_ENDCOMPOSITION, wParam, lParam );
	}
	else
	{
		return 0;
	}
}

//Put the number of the units that you want
//Put the number of items

LRESULT	CHTWindowManager::HT_OnIMENotify(WPARAM wParam, LPARAM lParam)
{
	if( g_iInationalType == INATIONALTYPE_KOREA || g_iInationalType == INATIONALTYPE_JAPEN )
	{
		//	Set ImeMgr
		LRESULT lRet;
		lRet = g_cImeMgr.OnImeNotify(g_hWnd, wParam, lParam);
		return 0;
		return lRet;
	}
	else
	{
		//	이러한 코딩이 삽입된 이유는 IME처리부에서 채팅 입력상태가 아닌데 IME 윈도가 떠는것을 막기 위함이다.
		if( HT_SUCCEED( this->HT_rhInputCheckForIme() ) )
		{
			return DefWindowProc( m_hWnd, WM_IME_NOTIFY, wParam, lParam );
		}
		else
		{
			return 0;
		}
	}
}

LRESULT	CHTWindowManager::HT_OnInputLangchange(WPARAM wParam, LPARAM lParam)
{
	//	Set ImeMgr
	g_cImeMgr.OnInputLangChange( wParam, lParam );
	//g_cImeMgr.InputString();

	return 0;
}


LRESULT CHTWindowManager::HT_OnCommand(WPARAM wParam, LPARAM lParam)
{
	// Tantra V3 UIManager 우선 처리
	//if (g_cUIManager)
	//	g_cUIManager->OnSysCommand(wParam);

	switch( LOWORD(wParam) )
    {
		case IDM_EXITAPP:
			{
				if( g_iGameSequnce == 2 )
				{
					g_byReStartButtonCode = _BTN_MSG_GAME_END;
					g_pEngineHandler->HT_hrPlaySound(33523, 1);
					//	현재 서버와 연결 끊음
					g_pNetWorkMgr->DisConnect();
				}
				break;
			}
        case IDM_TOGGLESCREEN:
			if( m_bActive )
			{
				// Toggle windowed flag
				m_bWindowed = !m_bWindowed;
				HT_hrToggleScreen();
				break;
			}
		default:
			// Notify the message was not processed
			return 1;
			break;
	}
	
	// Notify the message was processed
	return 0;
}

LRESULT CHTWindowManager::HT_SysCommand(WPARAM wParam, LPARAM lParam)
{
	switch(wParam){
		case SC_CLOSE:
			PostQuitMessage(0);
			// Notify the message can be processed
            return 0;
			break;

		// Prevent moving/sizing and power loss in fullscreen/window mode			
        case SC_MOVE:
        case SC_SIZE:
        case SC_MAXIMIZE:
        case SC_MONITORPOWER:
            if( false == m_bWindowed )
			// Notify the message cannot be processed
            return -9999;
            break;

		// 메뉴 호출(Alt 키 등)을 막는다 임시로 이렇게 해 놓은 것이며 후에 윈도우 메시지 프로시져를 바꾸며 고칠 것!
		case SC_KEYMENU:
			// Notify the message cannot be processed
            return -9999;

		default:
			// Notify the message was processed
			return 0;
			break;
	}
	// Notify the message was processed
	return 0;
}



LRESULT	CHTWindowManager::HT_OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	//	마우스 이벤트를 현재 쓰레드에 속한 윈도우로 한정한다.
	//SetCapture( m_hWnd );
	// 커서위치 계산
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );

	//	입력을 받음으로 해서 자동 대기모드 취소
	if( g_pDuelSystem )
		g_pDuelSystem->HT_vDuel_SetWaitModeCancelFromKeyInput();

	//	혹시 채팅 활성화이면 비활성화 시킴
	//if( g_cChatting )
	//	g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );

	// Tantra V3 UIManager 우선 처리
	if (g_cUIManager)
		if (g_cUIManager->OnLButtonDown(pPt.x, pPt.y)) return 0;

	if(g_iInterface.bLbuttonDbClk)
	{
		g_iInterface.bLbuttonDbClk = HT_FALSE;
		g_iInterface.iLeftDown = HT_FALSE;
	}
	else
		g_iInterface.iLeftDown = HT_TRUE;

	if( g_bMainCharacterInitialized )
	{
		g_cInterfaceCheck->HT_vInterface_LbuttonDown( pPt );
	}
	else
	{
		if( g_cIntroManager )	g_cIntroManager->HT_hrLButtonDown( pPt.x, pPt.y );
	}

	// Notify the message was processed
	return 0;
}


LRESULT CHTWindowManager::HT_OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	//	마우스 이벤트를 현재 쓰레드에 속한 윈도우에서 풀어준다.
	//ReleaseCapture();

	//	Cancel Ime Mode
	if( g_iInationalType == INATIONALTYPE_JAPEN )
	{
		g_cImeMgr.vImeMgr_SetImeModeCancel();
	}

	if(!g_iInterface.bLbuttonDbClk && g_iInterface.iLeftDown == HT_TRUE)
		g_iInterface.iLeftClick = HT_TRUE;

	g_iInterface.iLeftDown = HT_FALSE;

	// 커서위치 계산
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );

	// Tantra V3 UIManager 우선 처리
	if (g_cUIManager) 
		if (g_cUIManager->OnLButtonUp(pPt.x, pPt.y)) return 0;


	if( g_bMainCharacterInitialized )
	{
		g_cInterfaceCheck->HT_vInterface_LbuttonClick( pPt );
		g_cInterfaceCheck->HT_vInterface_LbuttonUp( pPt );
	}
	else
	{
		if( g_cIntroManager )
            g_cIntroManager->HT_hrLButtonUp( pPt.x, pPt.y );
	}

	// Notify the message was processed
	return 0;
}

LRESULT	CHTWindowManager::HT_OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	// 커서위치 계산
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );

	//	혹시 채팅 활성화이면 비활성화 시킴
	//if( g_cChatting )	g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );

	// Tantra V3 UIManager 우선 처리
	if (g_cUIManager) 
		if (g_cUIManager->OnRButtonDown(pPt.x, pPt.y)) return 0;

//	if(g_iInterface.bRbuttonDbClk)
//		g_iInterface.iRightDown = HT_FALSE;
//	else
		g_iInterface.iRightDown = HT_TRUE;
		

	// 커서 변경
	if( g_cInterfaceCheck )
	{
		if(g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE)
		{
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_RBUTTON);
		}
	}

	if( g_bMainCharacterInitialized )
	{
		g_cInterfaceCheck->HT_vInterface_RButtonDown( pPt );

		// 윈도우 모드일 경우 카메라를 조절하는 동안 커서이동을 클라이 언트 영역으로 한정한다.
		if ( m_bWindowed )
		{
			RECT rcClient;
			GetScreenRect( &rcClient );
			ClipCursor( &rcClient );
		}
	}
	
	// Notify the message was processed
	return 0;
}


LRESULT CHTWindowManager::HT_OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	if(!g_iInterface.bRbuttonDbClk && g_iInterface.iRightDown == HT_TRUE)
		g_iInterface.iRightClick = HT_TRUE;

	g_iInterface.iRightDown = HT_FALSE;
	
	// 커서위치 계산
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );


	// Tantra V3 UIManager 우선 처리
	if (g_cUIManager) 
		if (g_cUIManager->OnRButtonUp(pPt.x, pPt.y)) return 0;

	// 커서 변경
	if( g_cInterfaceCheck )
	{
		if(g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE)
		{
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
		}
	}

	if( g_bMainCharacterInitialized )
	{
		g_cInterfaceCheck->HT_vInterface_RButtonUp( pPt );
		g_cInterfaceCheck->HT_vInterface_RButtonClick( pPt );

		// 커서이동을 원래대로 한다
		if ( !m_bWindowed )
		{
			RECT rcClient;
			GetScreenRect( &rcClient );
			ClipCursor( &rcClient );
		}
		else
		{
			ClipCursor( NULL );
		}
	}
		
	// Notify the message was processed
	return 0;
}



LRESULT CHTWindowManager::HT_OnLButtonDblclk(WPARAM wParam, LPARAM lParam)
{
	g_iInterface.bLbuttonDbClk	= HT_TRUE;
	g_iInterface.iLeftDown		= HT_FALSE;
	g_iInterface.iLeftClick		= HT_FALSE;

	// 커서위치 계산
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );

	// Notify the message was processed
	return 0;
}

LRESULT CHTWindowManager::HT_OnRButtonDblclk(WPARAM wParam, LPARAM lParam)
{
	g_iInterface.bRbuttonDbClk	= HT_TRUE;
	g_iInterface.iRightDown		= HT_FALSE;
	g_iInterface.iRightClick	= HT_FALSE;
	
	// 커서위치 계산
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );

    // Notify the message was processed
	return 0;
}


LRESULT CHTWindowManager::HT_OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	// 커서위치 계산
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );

	//	미니맵 이동
	if( g_cMiniMap )
        g_cMiniMap->HT_hrMiniMap_MouseMove();

	// Tantra V3 UIManager 우선 처리
	if (g_cUIManager)
		g_cUIManager->OnMouseMove(pPt.x, pPt.y);


	//	initChar 이후에 마우스 무브 업데이트
	if( g_bMainCharacterInitialized )
	{
		// Mouse가 이동한후의 변화(커서 모양 등)을 처리
		g_cInterfaceCheck->HT_vInterface_MouseMove( pPt );
	}
	g_pEngineHandler->HT_vOnMouseMove( pPt.x, pPt.y );

	// Notify the message was processed
	return 0;
}

LRESULT	CHTWindowManager::HT_OnCreate(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


LRESULT CHTWindowManager::HT_OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	//	wheel rotation 
	// Tantra V3 UIManager 우선 처리
	if (g_cUIManager)
		if (g_cUIManager->OnMouseWheel(wParam, lParam)) return 0;
	
	// 메인 시작하기 전에는 막아야 함
	if( !g_bMainCharacterInitialized )
		return 0;
	
	if( (int)wParam > 0 )
        g_cCamera.HT_vCamera_ZoomInAndOut( 1, g_cInterfaceCheck->HT_fInterface_GetElapsedTime()*2.0f );
	else if( (int)wParam < 0 )
		g_cCamera.HT_vCamera_ZoomInAndOut( -1, g_cInterfaceCheck->HT_fInterface_GetElapsedTime()*2.0f );

	// Notify the message was processed
	return 0;
}

LRESULT CHTWindowManager::HT_OnMbuttonUp(WPARAM wParam, LPARAM lParam)
{
	if( !g_bMainCharacterInitialized )
		return 0;

	//	카메라 초기값 셋팅
	g_cCamera.HT_vCamera_SetInitCameraMode();

	// Notify the message was processed
	return 0;
}

// Process APM Power Management events.
// does no have compatibility with 16-bit Windows-based applications.
LRESULT CHTWindowManager::HT_PowerBroadCast(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		// Accept Power management event
		// Operation resuming after critical suspension.
	case PBT_APMRESUMECRITICAL:
		// Battery power is low.
	case PBT_APMBATTERYLOW:
		// OEM-defined event occurred. 
	case PBT_APMOEMEVENT:
		// Power status has changed. 
	case PBT_APMPOWERSTATUSCHANGE:
		// Suspension request denied.
	case PBT_APMQUERYSUSPENDFAILED:
		break;

        // Deny Power management event
		// Operation resuming after suspension. 
	case PBT_APMRESUMESUSPEND:
		// Request for permission to suspend.
	case PBT_APMQUERYSUSPEND:
		// Operation resuming automatically after event.
	case PBT_APMRESUMEAUTOMATIC:
	case PBT_APMSUSPEND:
	default:
		//deny a request.
		return BROADCAST_QUERY_DENY;
	}

	// grant a request.
	return TRUE;
}

LRESULT CHTWindowManager::HT_SetCursor(WPARAM wParam, LPARAM lParam)
{
	// 윈도우즈 커서를 사용
	if( g_cInterfaceCheck )
	{
		if(g_cInterfaceCheck->m_bUseWindowsCursor)
			SetCursor(LoadCursor(m_hInstance, MAKEINTRESOURCE(IDC_CURSOR1)));
		else
		{
//			ShowCursor( FALSE );
			g_cInterfaceCheck->HT_vRanderCursor();
		}
	}

	return TRUE;
}

LRESULT CHTWindowManager::HT_SetFocus(WPARAM wParam, LPARAM lParam)
{
	// 포커스가 돌아오는 경우 마우스 커서 위치를 업데이트 한다.
	HTPoint pPt;
	POINT	point;
	
	GetCursorPos( &point);
	g_iInterface.pPt.x = pPt.x = point.x;
	g_iInterface.pPt.y = pPt.y = point.y;

	// Notify the message was processed
	return 0;
}


LRESULT CHTWindowManager::HT_KillFocus(WPARAM wParam, LPARAM lParam)
{
	// Notify the message was processed
	return 0;
}

LRESULT CHTWindowManager::HT_EnterMenuLoop(WPARAM wParam, LPARAM lParam)
{
	// Notify the message was processed
	return 0;
}


LRESULT CHTWindowManager::HT_ExitMenuLoop(WPARAM wParam, LPARAM lParam)
{
	// Notify the message was processed
	return 0;
}

//*****************************************************************************
// CNoCrashApp::ExceptionInformation()
// Purpose : [ 에러가 발생하였을 때 호출되는 가상 함수 입니다. ]
// Parameters :	
// [strInfo] :
// Returns :	none
// Last Update : 2001-06-13
//*****************************************************************************
void CHTWindowManager::ExceptionInformation( TCHAR* szInfo, TCHAR* szStackInfo )
{
	if ( !m_bEnableCrashSender ) return;

	if( g_iInationalType == INATIONALTYPE_KOREA )
	{
		//---------------------------------------------------------------------------
		// version 정보
		char strVersion[100];
		void* pBuffer = HT_NULL; 
		VS_FIXEDFILEINFO *pFixedInfo;
		UINT uVersionLen;
		DWORD dwHandle;     
		DWORD dwDataSize = ::GetFileVersionInfoSize((LPTSTR)"HTLauncher.exe", &dwHandle); 
		pBuffer = malloc(dwDataSize); 
		if (pBuffer)
		{
			GetFileVersionInfo((LPTSTR)"HTLauncher.exe", dwHandle, dwDataSize, pBuffer);
			VerQueryValue(pBuffer,_T("\\"),(void**)&pFixedInfo,(UINT *)&uVersionLen);  
			sprintf(strVersion, "%u.%u.%u.%u", 
				HIWORD (pFixedInfo->dwFileVersionMS),
				LOWORD (pFixedInfo->dwFileVersionMS),
				HIWORD (pFixedInfo->dwFileVersionLS),
				LOWORD (pFixedInfo->dwFileVersionLS)); 
			free(pBuffer);
		}
		//---------------------------------------------------------------------------

		// 마지막에 CHTApplication::HT_hrCleanup() 함수부터는 

		char *args[5];
		char prog[80] = "TantraCrashSender.exe";
		args[0] = "TantraCrashSender";
		args[1] = strVersion;
		args[2] = szStackInfo;
		args[3] = szInfo;
		args[4] = NULL;

		_execv( prog, args );
	}
	else
	{
		// 죄송합니다.\n예기치 못한 오류가 발생하였습니다.\n실행폴더의 Tantra_Crash_~.txt 파일을\n
		// 탄트라 개발팀으로 보내주시면 감사하겠습니다.
		CHTString szMessage;
		if( g_pMessageMgr->HT_bGetMessage( eMsgCommonSystemExeErr, &szMessage ) == true )
			MessageBox(NULL, szMessage.HT_szGetString(), "Tantra", MB_OK);

	
		HT_g_vLogFile( "Tantra_Crash !!!!! \n" );


		//---------------------------------------------------------------------------
		// version 정보를 쓴다.
		void* pBuffer = HT_NULL; 
		VS_FIXEDFILEINFO *pFixedInfo;
		UINT    uVersionLen;

		DWORD dwHandle;     
		DWORD dwDataSize = ::GetFileVersionInfoSize((LPTSTR)"HTLauncher.exe", &dwHandle); 

		pBuffer = malloc(dwDataSize); 

		if (pBuffer)
		{
			GetFileVersionInfo((LPTSTR)"HTLauncher.exe", dwHandle, dwDataSize, pBuffer);
			VerQueryValue(pBuffer,_T("\\"),(void**)&pFixedInfo,(UINT *)&uVersionLen);  

			char strVersion[100];
			sprintf(strVersion, "TANTRA - A Light In The Darkness  ver. %u.%u.%u.%u\n", 
				HIWORD (pFixedInfo->dwFileVersionMS),
				LOWORD (pFixedInfo->dwFileVersionMS),
				HIWORD (pFixedInfo->dwFileVersionLS),
				LOWORD (pFixedInfo->dwFileVersionLS)); 
			
			HT_g_vLogFile( strVersion );

			free(pBuffer);
		}
		//---------------------------------------------------------------------------

		//HT_g_vLogFile( szStackInfo );
		//HT_g_vLogFile( szInfo );
		if ( g_iInationalType != INATIONALTYPE_KOREA && g_iInationalType != INATIONALTYPE_JAPEN )
		{
			if ( g_pDebugFile )
			{
				fprintf( g_pDebugFile, szStackInfo );
				flushall();

				fprintf( g_pDebugFile, szInfo );
				flushall();
			}
		}
		
		HT_g_vCloseDebugFile();
	}
}

LRESULT CHTWindowManager::HT_ActivateApp(WPARAM wParam, LPARAM lParam)
{
	// 게임 중에는 게임만 해라 라는 의미가 들어있는... ( 아래 부분을 풀면 어플리케이션이 놀고 있을때 CPU 사용량이 뚝 떨어진다. )
	//if ( wParam == TRUE )	// Activate
	//{
	//	m_bActive = HT_TRUE;
	//}
	//else	// DeActivate
	//{
	//	m_bActive = HT_FALSE;
	//}

	// Notify the message was processed
	return 0;
}




LRESULT CHTWindowManager::HT_OnNetWorkMessage(WPARAM wParam, LPARAM lParam)
{
	//	서버와 연결이 끊어졌다.
	if( WSAGETSELECTEVENT(lParam) != FD_READ )
	{			
		g_cCPSock.CloseSocket();
		g_cCPSock.Sock = 0;

		if( g_iGameSequnce == 1 )
		{
			//  빌링 서버 받은 결과에 따라서
			if( g_bReciveBillingServer )
			{
				if (g_cIntroManager)
				{
					CHTString szMessage;
					// 죄송합니다. 서버와 연결이 끊어졌습니다. 다시 연결해주십시오.
					if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
						g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
				}
			}
		}
		else
		{
			if( !g_bZoneServerSwitching )
			{
				// 현재 존 서버의 연결이 끊어진 상태이면 프로그램을 종료
				if (g_pNetWorkMgr)
				{
					if( g_pNetWorkMgr->GetConnectingState() == STATUS_DISCONNECT )
					{
						CHTString szMessage;
						// 죄송합니다. 서버와 연결이 끊어졌습니다. 다시 연결해주십시오.
						if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
							g_cGameSystem->HT_vGameSystem_ServerDisConnect_SetDlg( szMessage );

						//// 잘못된 상태로 서버와의 연결이 끊어져 게임 진행이 중지된 경우는 채팅서버도 연결을 끊는다. 2005. 12. 21 선영범
						//if (g_pChatNetWorkMgr->GetConnectingState() == STATUS_ALIVE )
						//	g_pChatNetWorkMgr->DisConnect();
					}

				}
			}
		}
	}
    //	네트웍 에러 발생
	if( g_cCPSock.Receive()==FALSE )
	{	g_cCPSock.CloseSocket();
		g_cCPSock.Sock=0;
		return 0;
	}
	//	메시지를 받아 처리
	int Error;
	int ErrorCode;
	do 
	{	char * Msg = g_cCPSock.ReadMessage( &Error, &ErrorCode ); 
       	if ( Msg == NULL ) break;
		if ( Error == 1 || Error == 2 )
		{
			break;
		} 
		CHTNetWorkHandle::HT_hrWorkFunction(Msg);
	} while(1);

	return 0;
}

LRESULT CHTWindowManager::HT_OnChatNetWorkMessage(WPARAM wParam, LPARAM lParam)
{
	//	서버와 연결이 끊어졌다.
	if( WSAGETSELECTEVENT(lParam) != FD_READ )
	{			
		g_cChatCPSock.CloseSocket();
		g_cChatCPSock.Sock = 0;

		if( g_iGameSequnce == 1 )
		{
			//  빌링 서버 받은 결과에 따라서
			if( g_bReciveBillingServer )
			{
				if (g_cIntroManager)
				{
					CHTString szMessage;
					// 죄송합니다. 서버와 연결이 끊어졌습니다. 다시 연결해주십시오.
					if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
						g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
				}
			}
		}
		else
		{
			if( !g_bZoneServerSwitching )
			{
				// 현재 존 서버의 연결이 끊어진 상태이면 프로그램을 종료
				if (g_pNetWorkMgr)
				{
					if( g_pNetWorkMgr->GetConnectingState() == STATUS_DISCONNECT )
					{
						CHTString szMessage;
						// 죄송합니다. 서버와 연결이 끊어졌습니다. 다시 연결해주십시오.
						if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
							g_cGameSystem->HT_vGameSystem_ServerDisConnect_SetDlg( szMessage );
					}
				}
			}
		}
	}
	//	네트웍 에러 발생
	if( g_cChatCPSock.Receive()==FALSE )
	{	g_cChatCPSock.CloseSocket();
	g_cChatCPSock.Sock=0;
	return 0;
	}
	//	메시지를 받아 처리
	int Error;
	int ErrorCode;
	do 
	{	char * Msg = g_cChatCPSock.ReadMessage( &Error, &ErrorCode ); 
	if ( Msg == NULL ) break;
	if ( Error == 1 || Error == 2 )
	{
		break;
	} 
	CHTChatNetWorkHandle::HT_hrWorkFunction(Msg);
	} while(1);

	return 0;
}
