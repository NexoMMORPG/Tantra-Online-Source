

#ifndef __HTWINDOWMANAGER_H__
#define __HTWINDOWMANAGER_H__

#include "HTGameManager.h"
#include "HTConfigSystem.h"
#include "HTImeMgr.h"

#include "UnhandledException/ExceptionHandler.h"

class CHTWindowManager : public CHTGameManager, public IExceptionHandler
{
public:
	CHTWindowManager();
	~CHTWindowManager();

	//====================================================================//
	//		    	      윈도우와 관련한 함수		 		           	  //
	//====================================================================//
	LRESULT					HT_OnCreate(WPARAM wParam, LPARAM lParam);
	LRESULT					HT_OnClose(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_OnKeyDown(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_OnKeyUp(WPARAM wParam, LPARAM lParam);
	LRESULT					HT_OnChar(WPARAM wParam, LPARAM lParam);
	LRESULT					HT_OnCommand(WPARAM wParam, LPARAM lParam);
	LRESULT					HT_OnMouseMove(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_OnMouseWheel(WPARAM wParam, LPARAM lParam);
	LRESULT					HT_OnMbuttonUp(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_OnLButtonUp(WPARAM wParam, LPARAM lParam);
	LRESULT					HT_OnLButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_OnRButtonUp(WPARAM wParam, LPARAM lParam);
	LRESULT					HT_OnRButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_OnLButtonDblclk(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_OnRButtonDblclk(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_OnIME_StartComPosition(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_OnIME_EndComPosition(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_OnIME_Compositon(WPARAM wParam, LPARAM lParam);

	LRESULT 				HT_OnIMENotify(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_OnInputLangchange(WPARAM wParam, LPARAM lParam);
    LRESULT 				HT_PowerBroadCast(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_SysCommand(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_SetCursor(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_SetFocus(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_KillFocus(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_EnterMenuLoop(WPARAM wParam, LPARAM lParam);
	LRESULT 				HT_ExitMenuLoop(WPARAM wParam, LPARAM lParam);
	LRESULT					HT_ActivateApp(WPARAM wParam, LPARAM lParam);
	LRESULT					HT_OnNetWorkMessage(WPARAM wParam, LPARAM lParam);
	LRESULT					HT_OnChatNetWorkMessage(WPARAM wParam, LPARAM lParam);

public:

	HTRESULT Initialize(  HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, HTint nCmdShow  ) ;
	//----------게임 클리어 하기----------//
	void Finalize() ;
	//----------게임 클리어 하기_클라이언트----------//
	void ClientCleanup();

	HTRESULT				ReadyGameLoop();
	HTRESULT				MainGameLoop();

	//	Ime를 위하여 지금 입력 가능한 상태인지 체크
	//	이러한 코딩이 삽입된 이유는 IME처리부에서 채팅 입력상태가 아닌데 IME 윈도가 떠는것을 막기 위함이다.
	HTRESULT				HT_rhInputCheckForIme();

	// IExceptionHandler;
	void ExceptionInformation( TCHAR* szInfo, TCHAR* szStackInfo );
	CExceptionHandler m_eh;

private:
	MSG						msg;
	HTbool					bGotMsg;
	HACCEL					hAccel;

	HTfloat					time_limit;
	HTfloat					time_trans;


	//-----프로세스 카운트를 위해서-----//
    HTfloat					m_One_Time;
	HTfloat					m_One_Time_Operation;
	HTfloat					m_PROCESS_TO_TICKCOUNT;
	
	HTfloat					m_fTime_trans;
	HTfloat					m_Process_time_limit;
	HTfloat					m_Frame_time_limit;

	HTbool					m_bPrintScreenShot;

	// 이 값이 TRUE 인 상태에서만 CrashSender 가 작동한다.
	// 종료시에 죽는 클라이언트가 많이 발생하는데 그리 치명적인 문제가 아니라고 판단하여,
	// 종료시 죽는 클라이언트의 Crash를 무시하기 위해 만들었다.
	HTbool					m_bEnableCrashSender;

	//	IME 관련
	//	현재의 IME 설명
	CHTString				m_strDescription;
	//	현제 특수문자 목록의 최대 겟수
	HTint					m_iCanMax;
	//	특수문자를 위한 변수
	HTchar					m_szCanText[200];
	//	현제의 특수문자 위치
	HTint					m_iCandiGroupNumber;
	//	현제의 특수문자 위치
	HTint					m_iCandiCharNumber;
	//	조합된 문자
	CHTString				m_strCompositionString;
	//	문자를 만들기 위해 입력하는 영문을 저장
	CHTString				m_strCharSaveForAlpha;


public:
	HTbool					m_bWindowed;
};


#endif


