//---------------------------------------------------------------------------//
// Name: HTWin32Window.h
//
// Author:
//		- 2002/03/15, Created by HK, 
//
// Description:
//		- Base Class for Win32 Main Window
//		- Data Type redifinition
//---------------------------------------------------------------------------//

#ifndef _HTWin32Window_H_
#define _HTWin32Window_H_

#define	HT_MESSAGE_AREA		0x0500

#define	HT_CLASS_NAME		TEXT("Tantra Launcher")
#define	HT_TITLE_NAME		TEXT("Tantra Launcher")

class	CHTWin32Window;
typedef	LRESULT					(CHTWin32Window::*LPMESSAGECALLBACKFUNC)( WPARAM, LPARAM );
static	LPMESSAGECALLBACKFUNC	m_arrMessageCallBackFunc[HT_MESSAGE_AREA];

class CHTWin32Window
{
public:
								CHTWin32Window();
	virtual						~CHTWin32Window();
	virtual	HTbool				HT_bCreate(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
								HWND parenthwnd, LPSTR lpszCmdLine, HTint nCmdShow,
								HTuint nWidth, HTuint nHeight, HTbool bWindowed);

	static	LRESULT CALLBACK	HT_MainWndProc( HWND hWnd, HTuint uMsg, WPARAM wParam, LPARAM lParam );
			HWND				HT_hGetWindowHandle() { return m_hWnd; };
private:
	static void					HT_vSetCallBackFunc( HTuint msg, LPMESSAGECALLBACKFUNC func );

	virtual	LRESULT				HT_OnCreate(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnClose(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnDestroy(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT				HT_OnChar(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnKeyUp(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnLButtonDblclk(WPARAM wParam, LPARAM lParam);
	virtual LRESULT			    HT_OnRButtonDblclk(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnRButtonDown(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnRButtonUp(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnMouseMove(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnPaint(WPARAM wParam, LPARAM lParam);
	virtual	LRESULT 			HT_OnTimer(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_OnMouseWheel(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_OnMbuttonUp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_OnSize(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_OnEnterSizeMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_OnExitSizeMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT 			HT_OnIME_StartComPosition(WPARAM wParam, LPARAM lParam);
	virtual LRESULT 			HT_OnIME_EndComPosition(WPARAM wParam, LPARAM lParam);
	virtual LRESULT 			HT_OnIME_Compositon(WPARAM wParam, LPARAM lParam);
	virtual LRESULT 			HT_OnIMENotify(WPARAM wParam, LPARAM lParam);
	virtual LRESULT 			HT_OnInputLangchange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_PowerBroadCast(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_SysCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_SetCursor(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_SetFocus(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_KillFocus(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_EnterMenuLoop(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_ExitMenuLoop(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_ActivateApp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_OnNetWorkMessage(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_OnChatNetWorkMessage(WPARAM wParam, LPARAM lParam);
	virtual LRESULT				HT_OnIMEControl(WPARAM wParam, LPARAM lParam);


public:
	HTtchar*					m_strClassName;
	HTtchar*					m_strTitleName;
	HWND						m_hWnd;
	HWND						m_hParentWnd;
	HINSTANCE					m_hInstance;
	HDC							m_hDC;			// 대호 추가 (2002.09.16)
};

#endif
