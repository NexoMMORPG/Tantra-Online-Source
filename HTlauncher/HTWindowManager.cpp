

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
	//	IME ����
	//	�� Ư������ ����� �ִ� �ټ�
	m_iCanMax = 0;
	//	������ Ư������ ��ġ
	m_iCandiGroupNumber = 0;
	m_iCandiCharNumber = 1;
	//  Ư�����ڰ� �� ���� �ʱ�ȭ
	memset(m_szCanText,0,100);
	//	���ڸ� ����� ���� �Է��ϴ� ������ ����
	m_strCharSaveForAlpha.HT_hrCleanUp();
	//	���յ� ����
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
	// ���� ������ �ҷ���
	if ( HT_FAILED( g_pCfgSys->HT_hrLoad( _STARTUP_FILEPATH ) ) )
	{
		MessageBox( NULL, "Cannot find HTStartup.cfg!", "HTLauncher", MB_OK );
		return HT_FAIL;
	}

	HT_CHECK( g_pCfgSys->HT_hrGetValue( _T("RENDERER"), _T("windowed"), &m_bWindowed ) );
	// window ���� �� ���� �ʱ�ȭ 
	if ( HT_FAILED( HT_hrCreate( hInstance, hPrevInstance, HT_NULL, 
												lpCmdLine, nCmdShow ) ) )	
	{
		return HT_FAIL;
	}
	HT_g_vLogFile("HT_hrCreate success!\n");

	//	���� �޴����� �ʱ�ȭ �����ش�.
    HT_hrGMInit();

    // Load keyboard accelerators
    hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );

	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

	//	IME�� �ʱ�ȭ �Ѵ�.
	g_cImeMgr.InitInput( g_hWnd );

	HT_g_vLogFile("CHTWindowManager::Initialize success!\n");
   
	return ( HT_OK );
}

//----------���� Ŭ���� �ϱ�----------//
void CHTWindowManager::Finalize()
{
	// �� ���� TRUE �� ���¿����� CrashSender �� �۵��Ѵ�.
	// ����ÿ� �״� Ŭ���̾�Ʈ�� ���� �߻��ϴµ� �׸� ġ������ ������ �ƴ϶�� �Ǵ��Ͽ�,
	// ����� �״� Ŭ���̾�Ʈ�� Crash�� �����ϱ� ���� �������.
	m_bEnableCrashSender = HT_FALSE;

	//----------�α�����----------//
	HT_g_vLogFile("CHTWindowManager::Finalize start\n");
	// ���� ������ ���� (���� �� ���� ���� ������)
	g_pCfgSys->HT_hrSave( _T("HTStartup.cfg") );
	HT_DELETE( g_pCfgSys );

	HT_g_vLogFile("CHTWindowManager::Finalize 1\n");
	// Ŀ���� �ٽ� ���̰� �Ѵ�.
	ShowCursor( TRUE );
	//----------���� Ŭ���� �ϱ�_Ŭ���̾�Ʈ----------//
	HT_g_vLogFile("CHTWindowManager::Finalize 2\n");
	ClientCleanup();
	HT_g_vLogFile("CHTWindowManager::Finalize 3\n");
	//----------����----------//
	HT_hrCleanup();
	HT_g_vLogFile("CHTWindowManager::Finalize 4\n");
	//----------�α�����----------//
	HT_g_vLogFile("CHTWindowManager::Finalize success!\n");

	// ������ ���� ��Ʈ�ο��� �׳� ������ �������� �ʴ� Objects �� �����ϵ��� �ϱ� �����̴�. (������)
	HT_DELETE(g_pParamMgr);
	HT_DELETE(g_pMessageMgr);
	HT_DELETE(g_BasicLoadingInfo);
	HT_DELETE(g_cLoading);

	HT_DELETE(g_cInterfaceCheck);

	HT_DELETE(g_pCfgSys);
	HT_DELETE(g_cUIManager);
	HT_DELETE(g_poWebLogIn);

	//----------��Ʈ�� �ʱ�ȭ----------//
	HT_DELETE( g_pNetWorkMgr );
	HT_DELETE( g_pNetMsg );
}

//----------���� Ŭ���� �ϱ�_Ŭ���̾�Ʈ----------//
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

	//	��Ʈ�� ���� �ѹ� ������Ʈ -> ���� �ڵ��Ѱ� ������ �� �Ѱ��� �𸣰ڴ�.
	HT_hrReadyGameControl();

	//	Set Logo
	HT_g_vLogFile("HT_hrReadyGameControl 1 \n");

	while (WM_QUIT != msg.message)
	{
		HTRESULT hr = HT_OK;
		// Control for Ready loop
		hr = HT_hrReadyGameControl();

		// �α��� ������ ��� ��ģ ��� �������� ����
		if(hr == RETURNTYPE_INTRO_COMPLETE)
			return RETURNTYPE_INTRO_COMPLETE;

		// �α��ο��� exit �� ��� ���̻� �������� �ʰ� ����
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

				// ������ ������ ����ȭ�� ���ߴ� �۾��� �ϴ� ���̴�.
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

	// ������ ĳ���� �ʱ�ȭ ������ ��û�Ѵ�_�̴�Ʈ ����ĳ����,
	// �ð� �ʱ�ȭ�� �� �� ����ϰ� �ϱ� ���Ͽ� ������ �������� ������. (20030109Tenma)
	g_iRequestCharacterInitCount = 1;
	g_cInitConntion_StartTime = GetTickCount();
	g_byInitConnectType = CONNECT_TYPE_FIRST;
	CHTNetWorkHandle::HT_hrNetWorkInit_InitChar( CONNECT_TYPE_FIRST, 0, g_oMainCharacterInfo.szCharName, _T("") );
	HT_g_vLogFile("-InitRequestChar");

	// ���� ������Ʈ : ������ Ÿ�̸� ���� �����Ⱚ���� �Ѿ���� ���� ó���Ѵ�.
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

			// ������ ������ ����ȭ�� ���ߴ� �۾��� �ϴ� ���̴�.
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
//		    	      ������� ������ �Լ�		 		           	  //
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
	// Tantra V3 UIManager �켱 ó��
	if (g_cUIManager) 
		if (g_cUIManager->OnKeyDown(wParam)) return 0;

	if (wParam == 35) return 0;	// End Ű�� ������ ������ �׳� �����Ѵ�. (�̴� UI �ý��� ���������ε� �ʿ信 ���� ȣ���ϱ� ����)

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
				// ������ ����� ���� ����׿� ���ڿ��� ����ϵ��� �Ѵ�.
				if( g_bDevelopingMode )
				{
					if( g_bHelp_Text == HT_TRUE )
						g_bHelp_Text = HT_FALSE;
					else
						g_bHelp_Text = HT_TRUE;
				}
				break;
			//	��Ÿ Ư��Ű���� �����߿� ó��
			default :
				//	ä��â�� Ȱ��ȭ ���°� �ƴҶ�
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
	// Tantra V3 UIManager �켱 ó��
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
				//	ä��â�� Ȱ��ȭ ���°� �ƴҶ�
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
	// Tantra V3 UIManager �켱 ó��
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


//	Ime�� ���Ͽ� ���� �Է� ������ �������� üũ
//	�̷��� �ڵ��� ���Ե� ������ IMEó���ο��� ä�� �Է»��°� �ƴѵ� IME ������ ���°��� ���� �����̴�.
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

//	IME ó��
LRESULT CHTWindowManager::HT_OnIME_Compositon(WPARAM wParam, LPARAM lParam)
{
	//	�̷��� �ڵ��� ���Ե� ������ IMEó���ο��� ä�� �Է»��°� �ƴѵ� IME ������ ���°��� ���� �����̴�.
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
	//	�̷��� �ڵ��� ���Ե� ������ IMEó���ο��� ä�� �Է»��°� �ƴѵ� IME ������ ���°��� ���� �����̴�.
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
	//	�̷��� �ڵ��� ���Ե� ������ IMEó���ο��� ä�� �Է»��°� �ƴѵ� IME ������ ���°��� ���� �����̴�.
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
		//	�̷��� �ڵ��� ���Ե� ������ IMEó���ο��� ä�� �Է»��°� �ƴѵ� IME ������ ���°��� ���� �����̴�.
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
	// Tantra V3 UIManager �켱 ó��
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
					//	���� ������ ���� ����
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

		// �޴� ȣ��(Alt Ű ��)�� ���´� �ӽ÷� �̷��� �� ���� ���̸� �Ŀ� ������ �޽��� ���ν����� �ٲٸ� ��ĥ ��!
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
	//	���콺 �̺�Ʈ�� ���� �����忡 ���� ������� �����Ѵ�.
	//SetCapture( m_hWnd );
	// Ŀ����ġ ���
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );

	//	�Է��� �������� �ؼ� �ڵ� ����� ���
	if( g_pDuelSystem )
		g_pDuelSystem->HT_vDuel_SetWaitModeCancelFromKeyInput();

	//	Ȥ�� ä�� Ȱ��ȭ�̸� ��Ȱ��ȭ ��Ŵ
	//if( g_cChatting )
	//	g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );

	// Tantra V3 UIManager �켱 ó��
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
	//	���콺 �̺�Ʈ�� ���� �����忡 ���� �����쿡�� Ǯ���ش�.
	//ReleaseCapture();

	//	Cancel Ime Mode
	if( g_iInationalType == INATIONALTYPE_JAPEN )
	{
		g_cImeMgr.vImeMgr_SetImeModeCancel();
	}

	if(!g_iInterface.bLbuttonDbClk && g_iInterface.iLeftDown == HT_TRUE)
		g_iInterface.iLeftClick = HT_TRUE;

	g_iInterface.iLeftDown = HT_FALSE;

	// Ŀ����ġ ���
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );

	// Tantra V3 UIManager �켱 ó��
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
	// Ŀ����ġ ���
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );

	//	Ȥ�� ä�� Ȱ��ȭ�̸� ��Ȱ��ȭ ��Ŵ
	//if( g_cChatting )	g_cChatting->HT_vChatting_SetFocusOff( HT_FALSE );

	// Tantra V3 UIManager �켱 ó��
	if (g_cUIManager) 
		if (g_cUIManager->OnRButtonDown(pPt.x, pPt.y)) return 0;

//	if(g_iInterface.bRbuttonDbClk)
//		g_iInterface.iRightDown = HT_FALSE;
//	else
		g_iInterface.iRightDown = HT_TRUE;
		

	// Ŀ�� ����
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

		// ������ ����� ��� ī�޶� �����ϴ� ���� Ŀ���̵��� Ŭ���� ��Ʈ �������� �����Ѵ�.
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
	
	// Ŀ����ġ ���
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );


	// Tantra V3 UIManager �켱 ó��
	if (g_cUIManager) 
		if (g_cUIManager->OnRButtonUp(pPt.x, pPt.y)) return 0;

	// Ŀ�� ����
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

		// Ŀ���̵��� ������� �Ѵ�
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

	// Ŀ����ġ ���
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
	
	// Ŀ����ġ ���
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );

    // Notify the message was processed
	return 0;
}


LRESULT CHTWindowManager::HT_OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	// Ŀ����ġ ���
	HTPoint pPt;
	pPt.x = g_iInterface.pPt.x = LOWORD( lParam );
	pPt.y = g_iInterface.pPt.y = HIWORD( lParam );

	//	�̴ϸ� �̵�
	if( g_cMiniMap )
        g_cMiniMap->HT_hrMiniMap_MouseMove();

	// Tantra V3 UIManager �켱 ó��
	if (g_cUIManager)
		g_cUIManager->OnMouseMove(pPt.x, pPt.y);


	//	initChar ���Ŀ� ���콺 ���� ������Ʈ
	if( g_bMainCharacterInitialized )
	{
		// Mouse�� �̵������� ��ȭ(Ŀ�� ��� ��)�� ó��
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
	// Tantra V3 UIManager �켱 ó��
	if (g_cUIManager)
		if (g_cUIManager->OnMouseWheel(wParam, lParam)) return 0;
	
	// ���� �����ϱ� ������ ���ƾ� ��
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

	//	ī�޶� �ʱⰪ ����
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
	// �������� Ŀ���� ���
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
	// ��Ŀ���� ���ƿ��� ��� ���콺 Ŀ�� ��ġ�� ������Ʈ �Ѵ�.
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
// Purpose : [ ������ �߻��Ͽ��� �� ȣ��Ǵ� ���� �Լ� �Դϴ�. ]
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
		// version ����
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

		// �������� CHTApplication::HT_hrCleanup() �Լ����ʹ� 

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
		// �˼��մϴ�.\n����ġ ���� ������ �߻��Ͽ����ϴ�.\n���������� Tantra_Crash_~.txt ������\n
		// źƮ�� ���������� �����ֽø� �����ϰڽ��ϴ�.
		CHTString szMessage;
		if( g_pMessageMgr->HT_bGetMessage( eMsgCommonSystemExeErr, &szMessage ) == true )
			MessageBox(NULL, szMessage.HT_szGetString(), "Tantra", MB_OK);

	
		HT_g_vLogFile( "Tantra_Crash !!!!! \n" );


		//---------------------------------------------------------------------------
		// version ������ ����.
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
	// ���� �߿��� ���Ӹ� �ض� ��� �ǹ̰� ����ִ�... ( �Ʒ� �κ��� Ǯ�� ���ø����̼��� ��� ������ CPU ��뷮�� �� ��������. )
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
	//	������ ������ ��������.
	if( WSAGETSELECTEVENT(lParam) != FD_READ )
	{			
		g_cCPSock.CloseSocket();
		g_cCPSock.Sock = 0;

		if( g_iGameSequnce == 1 )
		{
			//  ���� ���� ���� ����� ����
			if( g_bReciveBillingServer )
			{
				if (g_cIntroManager)
				{
					CHTString szMessage;
					// �˼��մϴ�. ������ ������ ���������ϴ�. �ٽ� �������ֽʽÿ�.
					if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
						g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
				}
			}
		}
		else
		{
			if( !g_bZoneServerSwitching )
			{
				// ���� �� ������ ������ ������ �����̸� ���α׷��� ����
				if (g_pNetWorkMgr)
				{
					if( g_pNetWorkMgr->GetConnectingState() == STATUS_DISCONNECT )
					{
						CHTString szMessage;
						// �˼��մϴ�. ������ ������ ���������ϴ�. �ٽ� �������ֽʽÿ�.
						if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
							g_cGameSystem->HT_vGameSystem_ServerDisConnect_SetDlg( szMessage );

						//// �߸��� ���·� �������� ������ ������ ���� ������ ������ ���� ä�ü����� ������ ���´�. 2005. 12. 21 ������
						//if (g_pChatNetWorkMgr->GetConnectingState() == STATUS_ALIVE )
						//	g_pChatNetWorkMgr->DisConnect();
					}

				}
			}
		}
	}
    //	��Ʈ�� ���� �߻�
	if( g_cCPSock.Receive()==FALSE )
	{	g_cCPSock.CloseSocket();
		g_cCPSock.Sock=0;
		return 0;
	}
	//	�޽����� �޾� ó��
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
	//	������ ������ ��������.
	if( WSAGETSELECTEVENT(lParam) != FD_READ )
	{			
		g_cChatCPSock.CloseSocket();
		g_cChatCPSock.Sock = 0;

		if( g_iGameSequnce == 1 )
		{
			//  ���� ���� ���� ����� ����
			if( g_bReciveBillingServer )
			{
				if (g_cIntroManager)
				{
					CHTString szMessage;
					// �˼��մϴ�. ������ ������ ���������ϴ�. �ٽ� �������ֽʽÿ�.
					if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
						g_cIntroManager->HT_vIntro_SetShowMessage( szMessage, 5000 );
				}
			}
		}
		else
		{
			if( !g_bZoneServerSwitching )
			{
				// ���� �� ������ ������ ������ �����̸� ���α׷��� ����
				if (g_pNetWorkMgr)
				{
					if( g_pNetWorkMgr->GetConnectingState() == STATUS_DISCONNECT )
					{
						CHTString szMessage;
						// �˼��մϴ�. ������ ������ ���������ϴ�. �ٽ� �������ֽʽÿ�.
						if( g_pMessageMgr && g_pMessageMgr->HT_bGetMessage( eMsgLogInDisconnectServer, &szMessage ) == true )
							g_cGameSystem->HT_vGameSystem_ServerDisConnect_SetDlg( szMessage );
					}
				}
			}
		}
	}
	//	��Ʈ�� ���� �߻�
	if( g_cChatCPSock.Receive()==FALSE )
	{	g_cChatCPSock.CloseSocket();
	g_cChatCPSock.Sock=0;
	return 0;
	}
	//	�޽����� �޾� ó��
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
