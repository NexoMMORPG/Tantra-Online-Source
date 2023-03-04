//---------------------------------------------------------------------------//
// Name: HTWin32Window.cpp
//
// Author:
//		- 2002/03/15, Created by HK, 
//
// Description:
//		- Implimentation of CHTWin32Window
//---------------------------------------------------------------------------//

#include "stdafx.h"
#include "HTWin32Window.h"
#include "HTextern.h"
#include "resource.h"


CHTWin32Window::CHTWin32Window()
{
	m_strClassName = HT_CLASS_NAME;
	m_strTitleName = HT_TITLE_NAME;

	HTint i;
	
	for (i=0; i<HT_MESSAGE_AREA; i++)
		m_arrMessageCallBackFunc[i] = NULL;

	HT_vSetCallBackFunc(WM_CREATE,			HT_OnCreate);
	HT_vSetCallBackFunc(WM_CLOSE,			HT_OnClose);
	HT_vSetCallBackFunc(WM_DESTROY,			HT_OnDestroy);
	HT_vSetCallBackFunc(WM_KEYDOWN,			HT_OnKeyDown);
	HT_vSetCallBackFunc(WM_KEYUP,			HT_OnKeyUp);
	HT_vSetCallBackFunc(WM_CHAR,			HT_OnChar);
	HT_vSetCallBackFunc(WM_KEYUP,			HT_OnKeyUp);
	HT_vSetCallBackFunc(WM_LBUTTONDOWN,		HT_OnLButtonDown);
	HT_vSetCallBackFunc(WM_LBUTTONUP,		HT_OnLButtonUp);
	HT_vSetCallBackFunc(WM_RBUTTONDOWN,		HT_OnRButtonDown);
	HT_vSetCallBackFunc(WM_RBUTTONUP,		HT_OnRButtonUp);
	HT_vSetCallBackFunc(WM_LBUTTONDBLCLK,	HT_OnLButtonDblclk);
	HT_vSetCallBackFunc(WM_RBUTTONDOWN,		HT_OnRButtonDown);
	HT_vSetCallBackFunc(WM_RBUTTONUP,		HT_OnRButtonUp);
	HT_vSetCallBackFunc(WM_RBUTTONDBLCLK,	HT_OnRButtonDblclk);
	HT_vSetCallBackFunc(WM_MOUSEMOVE,		HT_OnMouseMove);
	HT_vSetCallBackFunc(WM_PAINT,			HT_OnPaint);
	HT_vSetCallBackFunc(WM_TIMER,			HT_OnTimer);
	HT_vSetCallBackFunc(0x020A,				HT_OnMouseWheel);		// HK : For WM_MOUSEWHEEL
	HT_vSetCallBackFunc(WM_MBUTTONUP,		HT_OnMbuttonUp);
    HT_vSetCallBackFunc(WM_COMMAND,			HT_OnCommand);
	HT_vSetCallBackFunc(WM_SIZE,			HT_OnSize);
	HT_vSetCallBackFunc(WM_ENTERSIZEMOVE,	HT_OnEnterSizeMove);
	HT_vSetCallBackFunc(WM_EXITSIZEMOVE,	HT_OnExitSizeMove);
	
	HT_vSetCallBackFunc(WM_IME_CONTROL,		HT_OnIMEControl );
	HT_vSetCallBackFunc(WM_IME_STARTCOMPOSITION,	HT_OnIME_StartComPosition);
	HT_vSetCallBackFunc(WM_IME_ENDCOMPOSITION,		HT_OnIME_EndComPosition);
	HT_vSetCallBackFunc(WM_IME_COMPOSITION, HT_OnIME_Compositon);
	HT_vSetCallBackFunc(WM_IME_NOTIFY,		HT_OnIMENotify);
	
	HT_vSetCallBackFunc(WM_INPUTLANGCHANGE,	HT_OnInputLangchange);
	HT_vSetCallBackFunc(WM_POWERBROADCAST,	HT_PowerBroadCast);
	HT_vSetCallBackFunc(WM_SYSCOMMAND,		HT_SysCommand);
	HT_vSetCallBackFunc(WM_SETCURSOR,		HT_SetCursor);
	HT_vSetCallBackFunc(WM_SETFOCUS,		HT_SetFocus);
	HT_vSetCallBackFunc(WM_KILLFOCUS,		HT_KillFocus);
	HT_vSetCallBackFunc(WM_ENTERMENULOOP,	HT_EnterMenuLoop);
	HT_vSetCallBackFunc(WM_EXITMENULOOP,	HT_ExitMenuLoop);
	HT_vSetCallBackFunc(WM_ACTIVATEAPP,		HT_ActivateApp);
	HT_vSetCallBackFunc(WSA_READ,			HT_OnNetWorkMessage);
	HT_vSetCallBackFunc(WSA_READ + 1,		HT_OnChatNetWorkMessage);
}


CHTWin32Window::~CHTWin32Window(){}

HTbool CHTWin32Window::HT_bCreate(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
								  HWND parenthwnd, LPSTR lpszCmdLine, HTint nCmdShow,
								  HTuint nWidth, HTuint nHeight, HTbool bWindowed)
{
	m_hInstance = hInstance;
	HWND hwnd = FindWindow(m_strClassName, m_strTitleName);

	if (hwnd)
	{
		MessageBox( HT_NULL, _T("Application is already running!"), _T("g_pLauncher"), MB_OK );
		SetForegroundWindow( (HWND) (((DWORD)hwnd) | 0x01) );
		return HT_FALSE;
	} //이미 실행되고 있는 경우 처리.

	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),									//UINT       cbSize;
		CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW,	//UINT       style;
		HT_MainWndProc,										//WNDPROC    lpfnWndProc;
		0L,													//int        cbClsExtra;
		0L,													//int        cbWndExtra;
		m_hInstance,										//HINSTANCE  hInstance;
		LoadIcon( m_hInstance, MAKEINTRESOURCE(IDI_ICON1)),	//HICON      hIcon;
		HT_NULL,											//HCURSOR    hCursor;
		(HBRUSH)GetStockObject(BLACK_BRUSH),				//HBRUSH     hbrBackground;
		HT_NULL,											//LPCTSTR    lpszMenuName;
		m_strClassName,										//LPCTSTR    lpszClassName;
		HT_NULL												//HICON      hIconSm;
	};
	RegisterClassEx( &wc );

	m_hParentWnd = parenthwnd;

	RECT rc;
	HTdword dwWindowStyle;
	HTdword dwExWindowStyle;

	dwWindowStyle = WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
	dwExWindowStyle = WS_EX_LEFT;

	// Get the window's initial width
	SetRect( &rc, 0, 0, nWidth, nHeight );
	AdjustWindowRectEx( &rc, dwWindowStyle, false, dwExWindowStyle );

	//m_hWnd = CreateWindowEx
	//(
	//	dwExWindowStyle,
	//	m_strClassName,
	//	m_strTitleName,
	//	dwWindowStyle,
	//	0,
	//	0,
	//	(rc.right - rc.left),
	//	(rc.bottom - rc.top),
	//	HT_NULL,
	//	HT_NULL,
	//	m_hInstance,
	//	HT_NULL
	//);
	g_hInstance = m_hInstance;
	m_hWnd = CreateWindow( m_strClassName, m_strTitleName, WS_POPUP | WS_CLIPCHILDREN, 0, 0, nWidth, nHeight, HT_NULL, HT_NULL, m_hInstance, HT_NULL );	

	// 윈도우 생성에 성공한 경우
	if (m_hWnd)
	{
		// 리소스 등 여러가지 면을 위하여 전역변수로 저장!(필요한 경우 외에 쓰지 말것)
		g_hWnd = m_hWnd;
		SetWindowLong(m_hWnd, GWL_USERDATA, (HTlong) this);
		UpdateWindow(m_hWnd);
		return HT_TRUE;
	}
	// 윈도우 생성에 실패한 경우
	else
	{
		MessageBox( HT_NULL, _T("Window creation failed!"), _T("g_pLauncher"), MB_OK );
		return HT_FALSE;
	}
}

LRESULT CALLBACK CHTWin32Window::HT_MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CHTWin32Window *pWin = (CHTWin32Window*)GetWindowLong(hWnd, GWL_USERDATA);

	if(msg >= 0 && msg < HT_MESSAGE_AREA && (m_arrMessageCallBackFunc[msg]!=0) && pWin != HT_NULL)
	{
		HTint res = (pWin->*m_arrMessageCallBackFunc[msg])(wParam, lParam);
		//(*m_arrMessageCallBackFunc[msg])(wParam, lParam);
		// 메뉴 호출(Alt 키 등)을 막는다 임시로 이렇게 해 놓은 것이며 후에 윈도우 메시지 프로시져를 바꾸며 고칠 것!
		if ( msg == WM_SYSCOMMAND && res == -9999 )	return 1;
		if ( res == HT_FALSE ) return 0;

		// 이부분은 윈도우닫기 버튼을 눌러서 종료시 아래의 DefWindowProc에서
		// DestroyWindow를 함으로써 TranslateAccelerator에서 에라가 발생하는
		// 문제를 막기 위함이다.
		if ( msg == WM_CLOSE ) return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void CHTWin32Window::HT_vSetCallBackFunc(UINT msg, LPMESSAGECALLBACKFUNC func)
{
	m_arrMessageCallBackFunc[ msg ] = func;
}

LRESULT CHTWin32Window::HT_OnCreate(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT CHTWin32Window::HT_OnClose(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT CHTWin32Window::HT_OnDestroy(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT CHTWin32Window::HT_OnKeyDown(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT CHTWin32Window::HT_OnChar(WPARAM wParam, LPARAM lParam)				{ return TRUE; }
LRESULT CHTWin32Window::HT_OnKeyUp(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT CHTWin32Window::HT_OnLButtonDown(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
LRESULT CHTWin32Window::HT_OnLButtonUp(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
LRESULT CHTWin32Window::HT_OnRButtonDown(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
LRESULT CHTWin32Window::HT_OnRButtonUp(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
LRESULT CHTWin32Window::HT_OnLButtonDblclk(WPARAM wParam, LPARAM lParam)	{ return TRUE; }
LRESULT CHTWin32Window::HT_OnRButtonDblclk(WPARAM wParam, LPARAM lParam)	{ return TRUE; }
LRESULT CHTWin32Window::HT_OnMouseMove(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
LRESULT CHTWin32Window::HT_OnPaint(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT CHTWin32Window::HT_OnTimer(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT CHTWin32Window::HT_OnMouseWheel(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
LRESULT CHTWin32Window::HT_OnMbuttonUp(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
LRESULT	CHTWin32Window::HT_OnCommand(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT	CHTWin32Window::HT_OnSize(WPARAM wParam, LPARAM lParam)				{ return TRUE; }
LRESULT	CHTWin32Window::HT_OnEnterSizeMove(WPARAM wParam, LPARAM lParam)	{ return TRUE; }
LRESULT	CHTWin32Window::HT_OnExitSizeMove(WPARAM wParam, LPARAM lParam)		{ return TRUE; }

LRESULT CHTWin32Window::HT_OnInputLangchange(WPARAM wParam, LPARAM lParam)	{ return TRUE; }
LRESULT CHTWin32Window::HT_PowerBroadCast(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
LRESULT CHTWin32Window::HT_SysCommand(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT CHTWin32Window::HT_SetCursor(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT CHTWin32Window::HT_SetFocus(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT CHTWin32Window::HT_KillFocus(WPARAM wParam, LPARAM lParam)			{ return TRUE; }
LRESULT CHTWin32Window::HT_EnterMenuLoop(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
LRESULT CHTWin32Window::HT_ExitMenuLoop(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
LRESULT CHTWin32Window::HT_ActivateApp(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
LRESULT CHTWin32Window::HT_OnNetWorkMessage(WPARAM wParam, LPARAM lParam)	{ return TRUE; }
LRESULT CHTWin32Window::HT_OnChatNetWorkMessage(WPARAM wParam, LPARAM lParam) { return TRUE; }

LRESULT CHTWin32Window::HT_OnIMEControl(WPARAM wParam, LPARAM lParam) { return DefWindowProc( m_hWnd, WM_IME_CONTROL, wParam, lParam ); }
LRESULT	CHTWin32Window::HT_OnIME_StartComPosition(WPARAM wParam, LPARAM lParam)	{ return TRUE; }
LRESULT	CHTWin32Window::HT_OnIME_EndComPosition(WPARAM wParam, LPARAM lParam)	{ return TRUE; }
LRESULT	CHTWin32Window::HT_OnIME_Compositon(WPARAM wParam, LPARAM lParam)	{ return TRUE; }
LRESULT CHTWin32Window::HT_OnIMENotify(WPARAM wParam, LPARAM lParam)		{ return TRUE; }
