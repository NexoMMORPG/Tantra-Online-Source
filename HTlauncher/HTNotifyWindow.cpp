//======================================================================
// HTNotifyWindow.cpp
// 도움말 윈도우, 내용 등
// (주)한빛소프트 게임개발팀 서명석		2003.02.06
//======================================================================
#include "stdafx.h"
#include "resource.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTNotifyWindow.h"


CHTNotifyWindow::CHTNotifyWindow()
{
	m_bNotify_DlgSw = HT_FALSE;
	m_bLoaded = HT_FALSE;
	//	Create Window
	this->HT_vNotify_CreateWindow();
}

CHTNotifyWindow::~CHTNotifyWindow()
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_NOTIFYWND );
	// If the reosurce is loaded, unload them
	if( this->m_bLoaded ) this->Unload();
}

// Load the resources
HTvoid CHTNotifyWindow::Load()
{
}

// Unload the resources
HTvoid CHTNotifyWindow::Unload()
{
}

// Is the resources loaded?
HTbool CHTNotifyWindow::isLoaded()
{
	return m_bLoaded;
}

//	Create Window
HTvoid CHTNotifyWindow::HT_vNotify_CreateWindow()
{
	CHTString strMessage;
	//	[_DIALOG_NOTIFYWND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_NOTIFYWND, _T("Notice"), 329, 465, g_pNotifyWindow->HT_vNotify_InputCheckForNotifyWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_NOTIFYWND, 7 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_NOTIFYWND, 0, 8, 2, 36, 1400, 325, 6 );
	//	Button Inventory
	g_cUIManager->HT_AddTextureControl( _DIALOG_NOTIFYWND, 0, 10, 40, 31, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_NOTIFYWND, 0, eMsgCommonChatNotice, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 31, 90, 19 );//	[공지]
	//	Long Text
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_NOTIFYWND, 1, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 15, 63, 300, 370 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_NOTIFYWND, 1,  7 );
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_NOTIFYWND, 2, 99, 130, 430, 97, 98, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_NOTIFYWND, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 130, 430, 64, 19 );//	확인
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_NOTIFYWND, 2 );
}

//	Equip Notify Wnd
void CHTNotifyWindow::HT_vNotify_InputCheckForNotifyWnd(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X or OK
		if( iTargetID == -1 ||
			iTargetID == 2 )
		{
			g_pNotifyWindow->HT_vNotify_SetOff();
		}
	}
}

//	공지창 켬
HTvoid CHTNotifyWindow::HT_vNotify_SetOn()
{
	m_bNotify_DlgSw = HT_TRUE;
	g_cUIManager->HT_ShowWindow( _DIALOG_NOTIFYWND );
}
//	공지창 끔
HTvoid CHTNotifyWindow::HT_vNotify_SetOff()
{
	m_bNotify_DlgSw = HT_FALSE;
	g_cUIManager->HT_HideWindow( _DIALOG_NOTIFYWND );
}
//	공지창에 텍스트 셋팅
HTvoid CHTNotifyWindow::HT_vNotify_SetText( HTchar* pStr )
{
	if( pStr )
		g_cUIManager->HT_SetTextLongLabelControl( _DIALOG_NOTIFYWND, 1, pStr );
}

// Set the help window on
HTvoid	CHTNotifyWindow::HT_vNotify_SetActive( HTchar* pStr )
{
	m_bNotify_DlgSw = HT_TRUE;
	g_cUIManager->HT_SetTextLongLabelControl( _DIALOG_NOTIFYWND, 1, pStr );
	g_cUIManager->HT_ShowWindow( _DIALOG_NOTIFYWND );
}

// Set the help window off
HTvoid	CHTNotifyWindow::HT_vNotify_SetDelete()
{
	if( m_bNotify_DlgSw == HT_TRUE )
	{
		m_bNotify_DlgSw = HT_FALSE;
		g_cUIManager->HT_HideWindow( _DIALOG_NOTIFYWND );
	}
}

//	ESC Key 누르면 공지창 닫기
HTvoid	CHTNotifyWindow::HT_vNotify_ESC_CloseWindow()
{
	// Set the help window off
	HT_vNotify_SetDelete();
}
