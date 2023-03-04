//======================================================================
// HTNotifyWindow.h
// 도움말 윈도우, 내용 등
// (주)한빛소프트 게임개발팀 서명석		2003.02.06
//======================================================================
#pragma once

class CHTNotifyWindow
{
public:
	CHTNotifyWindow();
	~CHTNotifyWindow();

	HTvoid		Load();
	HTvoid		Unload();
	HTbool		isLoaded();

	//	Create Window
	HTvoid		HT_vNotify_CreateWindow();
	//	Equip Notify Wnd
	static void		HT_vNotify_InputCheckForNotifyWnd(int iAction, int iTarget, int iTargetID);

	HTvoid		HT_vNotify_SetOn();
	HTvoid		HT_vNotify_SetOff();
	HTvoid		HT_vNotify_SetText( HTchar* pStr );

	HTvoid		HT_vNotify_SetActive( HTchar* pStr );
	HTvoid		HT_vNotify_SetDelete();
	//	ESC Key 누르면 공지창 닫기
	HTvoid		HT_vNotify_ESC_CloseWindow();

private:
	HTbool		m_bLoaded;

	HTbool		m_bNotify_DlgSw;
};
