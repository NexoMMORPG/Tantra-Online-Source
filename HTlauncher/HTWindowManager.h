

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
	//		    	      ������� ������ �Լ�		 		           	  //
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
	//----------���� Ŭ���� �ϱ�----------//
	void Finalize() ;
	//----------���� Ŭ���� �ϱ�_Ŭ���̾�Ʈ----------//
	void ClientCleanup();

	HTRESULT				ReadyGameLoop();
	HTRESULT				MainGameLoop();

	//	Ime�� ���Ͽ� ���� �Է� ������ �������� üũ
	//	�̷��� �ڵ��� ���Ե� ������ IMEó���ο��� ä�� �Է»��°� �ƴѵ� IME ������ ���°��� ���� �����̴�.
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


	//-----���μ��� ī��Ʈ�� ���ؼ�-----//
    HTfloat					m_One_Time;
	HTfloat					m_One_Time_Operation;
	HTfloat					m_PROCESS_TO_TICKCOUNT;
	
	HTfloat					m_fTime_trans;
	HTfloat					m_Process_time_limit;
	HTfloat					m_Frame_time_limit;

	HTbool					m_bPrintScreenShot;

	// �� ���� TRUE �� ���¿����� CrashSender �� �۵��Ѵ�.
	// ����ÿ� �״� Ŭ���̾�Ʈ�� ���� �߻��ϴµ� �׸� ġ������ ������ �ƴ϶�� �Ǵ��Ͽ�,
	// ����� �״� Ŭ���̾�Ʈ�� Crash�� �����ϱ� ���� �������.
	HTbool					m_bEnableCrashSender;

	//	IME ����
	//	������ IME ����
	CHTString				m_strDescription;
	//	���� Ư������ ����� �ִ� �ټ�
	HTint					m_iCanMax;
	//	Ư�����ڸ� ���� ����
	HTchar					m_szCanText[200];
	//	������ Ư������ ��ġ
	HTint					m_iCandiGroupNumber;
	//	������ Ư������ ��ġ
	HTint					m_iCandiCharNumber;
	//	���յ� ����
	CHTString				m_strCompositionString;
	//	���ڸ� ����� ���� �Է��ϴ� ������ ����
	CHTString				m_strCharSaveForAlpha;


public:
	HTbool					m_bWindowed;
};


#endif


