
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTParty.h"

//	주신, 종족, 계급, ID
HTint	g_nTrimurity_IconIndex[3]	= {	439, 438, 440 };
//	0:나가,1:아수라,2:약샤,3:데바,4:킴나라,5:략샤샤,6:간다르바,7:가루다 -> 원래 인덱스는 +1씩 되지
HTint	g_nTribe_IconIndex[8]		= {	442, 443, 444, 445, 446, 447, 448, 449};
//	수드라1,바이샤1,크샤트리아1,브라만1,아바트라1
HTint	g_nGradeIcon_Index[5]		= {	454, 455, 453, 452, 451 };
//	아이콘 들어가는 셀
HTint	g_nIconCellNo[6][3]		= { 15,16,17,  18,19,20, 21,22,23, 24,25,26, 27,28,29, 30,31,32 };
//	HP Bar Bitmap Image
HTint	g_HPBarBitmapNo[6] = { 33, 34, 35, 36, 37, 38 };

HTint	g_iMiniParty_HPBarImageNumber[7] = { 1, 2, 3, 4, 5, 6, 7 };
//	파티미니창_TP Bar
HTint	g_iMiniParty_TPBarImageNumber[7] = { 8, 9, 10, 11, 12, 13, 14 };

HTParty::HTParty(void)
{
	m_bLoaded = HT_FALSE;
}

HTParty::~HTParty(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_PARTYWND );
	//---------파티원/주소록 항목---------//
	for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; ++i )
	{
		ZeroMemory(&m_Party_Factor[i], sizeof(S_PARTY));
		m_Party_Factor[i].byLevel= 0xff;
		//	UI 컨트롤을 생셩했냐 안햇냐?
		m_byUIControlSet[i] = 0;
	}
}

HTvoid HTParty::HT_vParty_CleanUp()
{
	g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );
}

HTvoid HTParty::HT_vParty_Init()
{
	//	Create Window
	this->HT_vParty_CreateWindow();

	m_nParty_Send_Process			= PARTY_PROCESS_ERRORMESSAGE;
	m_nParty_WindowActiveSw			= HT_FALSE;
	m_nParty_DialogBoxActiveSw		= HT_FALSE;
	m_nParty_ReDialogBoxActiveSw	= HT_FALSE;
	//---------내가 파티장이냐?---------//
	m_Party_Jang = HT_FALSE;
	m_dwParty_JangKeyID = 0;
	m_bParty_Exist = HT_FALSE;
	//---------파티원/주소록 항목---------//
	for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; ++i )
	{
		ZeroMemory(&m_Party_Factor[i], sizeof(S_PARTY));
		m_Party_Factor[i].byLevel= 0xff;
		//	UI 컨트롤을 생셩했냐 안햇냐?
		m_byUIControlSet[i] = 0;
	}
	m_Party_MemberCount = 0;
	m_party_DeleteMember = 0;

	//----------각 파티원들의 주신, 종족, 계급 아이콘 이미지----------//
	//	바이샤3 -> 수드라3 -> 크사트리아3 -> 브라마3 -> 아바타라1
	//for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	//{
	//	// HP Bar
	//	m_nParty_MemberHPBar[i] = -1;
	//}
	m_bLoaded = HT_TRUE;

	//	미니파티창 스위치
	m_bMiniParty_WndSw = HT_FALSE;

	//	파티창 지우기
	g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );

	// 자동분배 모드
	m_bParty_RootingMode = HT_FALSE;
}

//	Create Window
HTvoid HTParty::HT_vParty_CreateWindow()
{
	HTint i;
	CHTString strMessage;
	//	[_DIALOG_PARTYWND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_PARTYWND, _T(""), 200, 300, g_cParty->HT_vParty_InputCheckForParty, 0 );
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_PARTYWND, true );
	g_cUIManager->HT_MoveWindow( _DIALOG_PARTYWND, g_pEngineHandler->HT_iGetScreenWidth()-200, 32 );
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_PARTYWND, 1, 159, 0, 0, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_PARTYWND, 1, eMsgPartyAutoRootingMode, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 0, 79, 19 );//자동분배
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_PARTYWND, 1 );
	g_cUIManager->HT_AddButtonControl( _DIALOG_PARTYWND, 2, 159, 82, 0, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_PARTYWND, 2, eMsgCommonSecede, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 82, 0, 79, 19 );//	탈  퇴
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_PARTYWND, 2 );
	for( i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	{
		g_cUIManager->HT_AddLabelControl( _DIALOG_PARTYWND, 10+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 20+(i*28), 180, 13 );
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_PARTYWND, 10+i, 7 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_PARTYWND, 10+i, 101, 0, 34+(i*28), 1400, 0, 5 );
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_FALSE );
		g_cUIManager->HT_AddTextureControl( _DIALOG_PARTYWND, 20+i, 102, 0, 40+(i*28), 1400, 0, 5 );
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_FALSE );
	}
}
//	입력 메세지 처리
//	AshramInfo
void HTParty::HT_vParty_InputCheckForParty(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == 1 )
		{
			if( g_cParty->HT_bParty_IsPartyJang( g_cMainCharacter->HT_iMainChar_GetKeyID() ) )
			{
				if( g_cParty->m_bParty_RootingMode )	g_cParty->m_bParty_RootingMode = HT_FALSE;
				else									g_cParty->m_bParty_RootingMode = HT_TRUE;
				g_cParty->HT_vNetWork_CSP_Req_Set_Party( g_cParty->m_bParty_RootingMode );
			}
		}
		else if( iTargetID == 2 )
		{
			g_cParty->HT_bParty_Command_PartyWithDraw();
		}
		else if( iTargetID>=10 && iTargetID<=((PARTY_MAX_PERSON-1)+10) )
		{
			//	파티 멤버들을 클릭했는가?
            g_cParty->HT_bParty_MemberClick(iTargetID);
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		//	확인 버튼
		if( iTargetID == 2 )
		{
			//	받은 메시지부터 처리
			if( g_cParty->m_nParty_Receive_Process == PARTY_PROCESS_RECIVEDJOINPARTY )
			{
				//----------컨펌 파티----------//
				g_cParty->HT_vNetWork_CSP_CNF_PARTY();
				g_cParty->m_nParty_Receive_Process = PARTY_PROCESS_ERRORMESSAGE;
				return;
			}

			switch(g_cParty->m_nParty_Send_Process)
			{
				case PARTY_PROCESS_PARTYLEAVE:
					g_cParty->HT_vNetWork_CSP_MSG_RemoveParty( 0x00 );
					break;
				case PARTY_PROCESS_PARTYMEMBERDELETE:
					g_cParty->HT_vNetWork_CSP_MSG_RemoveParty( 0x01 );
					break;
				case PARTY_PROCESS_PARTYDELETE :
					g_cParty->HT_vNetWork_CSP_MSG_RemoveParty( 0x00 );
					break;
				default :
					break;
			}
			g_cParty->m_nParty_Send_Process = PARTY_PROCESS_ERRORMESSAGE;
		}
		//	취소 버튼
		else if( iTargetID == 3 )
		{
			//	보낸 메시지는 그냥 처리
			g_cParty->m_nParty_Send_Process = PARTY_PROCESS_ERRORMESSAGE;
		}
	}
}

//	ESC Key 누르면 파티창 닫기
HTvoid HTParty::HT_vParty_ESC_CloseWindow()
{
	//----------활성화 / 비활성화----------//
	this->HT_vParty_MiniPartyWndSetSw();
}

//----------파티 탈퇴----------//
HTvoid HTParty::HT_vParty_PartyLeave()
{
	//--------- 파티가 만들어 졌느냐?---------//
	if( m_bParty_Exist == HT_FALSE )
		return;

	HTint iInductNo = -1;
	//---------내가 파티장이냐?---------//
	if( m_Party_Jang == HT_TRUE )
	{
		if( m_party_DeleteMember >= 0 && m_party_DeleteMember < 7 )
		{
			// 이분을 파티에서 퇴출시키겠습니까?
			HT_vParty_SetMessage( eMsgPartySecessionMemberQuestion, &m_strDialogBoxMessage );
			m_nParty_Send_Process = PARTY_PROCESS_PARTYMEMBERDELETE;
			iInductNo = RECONFIRM_PARTY_DELETE_MEMBER;
		}
		else 
		{
			// 파티를 해체 하시겠습니까?
			//HT_vParty_SetMessage( eMsgPartyDissolutionQuestion, &m_strDialogBoxMessage );
			// 파티에서 탈퇴 하렵니까?
			HT_vParty_SetMessage( eMsgPartySecessionQuestion, &m_strDialogBoxMessage );
			//m_nParty_Send_Process = PARTY_PROCESS_PARTYDELETE;
			m_nParty_Send_Process = PARTY_PROCESS_PARTYLEAVE;
			iInductNo = RECONFIRM_PARTY_SECESSION;
			//iInductNo = RECONFIRM_PARTY_DISSOLUTION;
		}
	}
	else
	{
		// 파티에서 탈퇴 하렵니까?
		HT_vParty_SetMessage( eMsgPartySecessionQuestion, &m_strDialogBoxMessage );
		m_nParty_Send_Process = PARTY_PROCESS_PARTYLEAVE;
		iInductNo = RECONFIRM_PARTY_SECESSION;
	}
	
	g_cUIManager->HT_MessageBox( _DIALOG_PARTYWND, m_strDialogBoxMessage.HT_szGetString(), 1 );
}


HTbool HTParty::HT_bParty_IsClickJoinBn()
{
	if( m_nParty_Send_Process == PARTY_PROCESS_REQJOINPARTY || m_nParty_Send_Process == PARTY_PROCESS_PARTYCREATE )
		return HT_TRUE;
	else
		return HT_FALSE;
}

//----------메인 캐릭터에서 파티 참여 요청----------//
HTRESULT HTParty::HT_vParty_JoinParty( HTint nObject )
{
	DWORD tKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( nObject );
	m_szCharacterName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( tKeyID );

	m_party_DeleteMember = 255;
	for (int i=0; i<7; ++i)	// 다른 사람이 픽될때마다 계속 정보를 갱신해야 한다.
		if (m_Party_Factor[i].nID == tKeyID) { m_party_DeleteMember = i; break;}
	if (m_party_DeleteMember == 255) m_szCharacterName = "";	// 파티가 아닌 사람을 클릭했다면 정보지움

	if( m_nParty_Send_Process != PARTY_PROCESS_REQJOINPARTY &&
		m_nParty_Send_Process != PARTY_PROCESS_PARTYCREATE )
		return HT_FAIL;

	// 파티장이 아니거나 내가 파티를 요청한 캐릭으로부터 답이 안왔거나
	// NPC와 대화중이거나 다른 사람과 트레이드를 하고 있는 중이면 처리 하지 않음
	if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) || g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) == HT_TRUE)
		return HT_FAIL;

	m_dwParty_JoinPartyKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( nObject );
	if( m_dwParty_JoinPartyKeyID == 0 )
	   return HT_FAIL;

	if( m_Party_MemberCount >= (PARTY_MAX_PERSON-1) )
		return HT_FAIL;

	// 커서 변경
	if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
	{
		if( g_cExchangeSystem->HT_vExchange_GetClickTradeButton() == HT_TRUE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_TRADE_ANI);
		else
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
	}

	//	파티 생성 요청
	if( m_nParty_Send_Process == PARTY_PROCESS_PARTYCREATE )
		this->HT_vNetWork_CSP_CREATEJOIN_PARTY();
	//	파티 참여 요청
	else if( m_nParty_Send_Process == PARTY_PROCESS_REQJOINPARTY )
	{
		CHTString strName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(m_dwParty_JoinPartyKeyID);
		if( HT_bParty_IsPartyMember( strName ) ) // 파티원일 경우
		{
			CHTString str;
			// 이미 가입되어있는 캐릭터입니다.
			HT_vParty_SetMessage( eMsgPartyJoinAlreadyMember, &str );
			if( str.HT_bIsEmpty() == HT_FALSE )
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, str );
		}
		else
			this->HT_vNetWork_CSP_CREATEJOIN_PARTY();
	}

	//	파티프로세스 초기화
	m_nParty_Send_Process = PARTY_PROCESS_ERRORMESSAGE;

	return HT_OK;
}

//----------네트워크 관련 함수----------//
//			0x16 Group(Party/Guild/주소록)	101
//----------파티 생성----------//
HTvoid HTParty::HT_vNetWork_CSP_CREATEJOIN_PARTY()
{
	MSG_REQParty* info = HT_NULL;
	info = new MSG_REQParty;
	info->TargetID = m_dwParty_JoinPartyKeyID;
	g_pNetWorkMgr->RequestReqCreateJoinParty( info );

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_REQ_CREATE_PARTY" );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//----------- 파티 참여 요청 받음 --------------//
HTvoid HTParty::HT_vNetWork_SCP_CREATEJOIN_PARTY( MSG_REQParty* info )
{
	//	이미 파티가 만들어져 있거나 NPC와 작업중이거나 
	if( m_bParty_Exist == HT_TRUE || g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW )
								 ||	g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) 
								 ||	g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) 
								 ||	g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) )
	{
		CHTString str;
		// %s님의 파티 참여 요청을 거절했습니다.
		m_szCharacterName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->Leader.nID );
		HT_vParty_SetMessage( eMsgPartyJoinReqReceiveRejection, &str);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ERROR, str );

		return;
	}

	//----------파티장의 키아이디 저장----------//
	m_dwParty_JangKeyID = info->Leader.nID;
	m_strParty_JangName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( m_dwParty_JangKeyID );
	// %s님이 파티맺기를 요청하였습니다
	m_szCharacterName = m_strParty_JangName;
	HT_vParty_SetMessage( eMsgPartyJoinReqReceive, &m_strDialogBoxMessage );
	m_nParty_Receive_Process = PARTY_PROCESS_RECIVEDJOINPARTY;
	g_cUIManager->HT_MessageBox( _DIALOG_PARTYWND, m_strDialogBoxMessage.HT_szGetString(), 1 );
}

//----------컨펌 파티----------//
HTvoid HTParty::HT_vNetWork_CSP_CNF_PARTY()
{
	MSG_CNFParty* info = HT_NULL;
	info = new MSG_CNFParty;
	info->TargetID = m_dwParty_JangKeyID;
	g_pNetWorkMgr->RequestReqCNFParty( info );

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_CFN_PARTY : %d",  info->TargetID );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//----------파티원 추가----------//
HTvoid HTParty::HT_vNetWork_SCP_MSG_AddParty( MSG_AddParty* info )
{

	//	멤버가 모두 찼으면
	if( m_Party_MemberCount >= (PARTY_MAX_PERSON-1) )
		return;

	//	파티가 존재하지 않으면
	if( !m_bParty_Exist )
	{
		//----------파티 구성원 초기화----------//
		this->HT_vParty_InitMember();
		m_bParty_Exist = HT_TRUE;

		//----------시스템 창에 메시지 뛰우기----------//
		CHTString strMessage;
		HT_vParty_SetMessage( eMsgPartyCreateOK, &strMessage ); // 파티가 생성되었습니다.
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, strMessage );

		//	파티창 뛰우기
		m_bMiniParty_WndSw = HT_FALSE;
		this->HT_vParty_MiniPartyWndSetSw();

		// 내가 파티를 처음 생성했을 때 아이템 루팅 모드 표시
		if( info->nLeaderID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
			HT_bParty_SetRootingMode( m_bParty_RootingMode );
	}

	//	파티장의 정보 셋팅
	m_dwParty_JangKeyID			= info->nLeaderID;
	if( info->nLeaderID == g_cMainCharacter->HT_iMainChar_GetKeyID() ) // 내가 파티장일 경우
	{
		m_Party_Jang				= HT_TRUE;
		m_strParty_JangName			= g_oMainCharacterInfo.szCharName;
	}
	else // 다른 사람이 파티장일 경우
	{
		m_Party_Jang				= HT_FALSE;
		m_strParty_JangName			= g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->nLeaderID );
	}

	S_PARTY oData;
	memcpy( &oData, &info->Party, sizeof( S_PARTY ) );
	//----------새로운 멤버 추가하기----------//
	this->HT_vParty_InsertMember( oData );

	// 자동분배 모드
	if( info->Party.nID == m_dwParty_JangKeyID )
	{
		HT_bParty_SetRootingMode( (HTbool)info->Party.byRootingMode );
	}

	//	파티 멤버 보여주기
	this->HT_vParty_PartyMemberDiplay();
}

//----------기존 데이타 변경하기----------//
HTvoid HTParty::HT_vNetWork_SCP_MSG_UpdateParty( PS_SCP_RESP_UPDATE_PARTY info )
{
	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		if( m_Party_Factor[i].nID == info->Party.nID )
		{
			m_Party_Factor[i].byLevel = info->Party.byLevel;
			m_Party_Factor[i].nAffections = info->Party.nAffections;
			m_Party_Factor[i].nCurHP = info->Party.nCurHP;
			m_Party_Factor[i].nCurTP = info->Party.nCurTP;
			m_Party_Factor[i].nMaxHP = info->Party.nMaxHP;
			m_Party_Factor[i].nMaxTP = info->Party.nMaxTP;

			//	Member HP
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_TRUE );
			//	Member TP
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_TRUE );

			//	HP
			HTfloat xPos;
			if( m_Party_Factor[i].nCurHP==0 && m_Party_Factor[i].nMaxHP==0 )
				xPos = 1.0f;
			else
				xPos = (HTfloat)m_Party_Factor[i].nCurHP/(HTfloat)m_Party_Factor[i].nMaxHP;
			if( xPos <= 0.0f || xPos > 1.0f )	xPos = 1.0f;
			g_cUIManager->HT_SetTextureControlScale( _DIALOG_PARTYWND, 10+i, (HTint)(xPos*150), 5 );
			if( m_Party_Factor[i].nCurHP == 0 )		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_FALSE );
			else									g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_TRUE );
			//	TP
			if( m_Party_Factor[i].nCurTP==0 && m_Party_Factor[i].nMaxTP==0 )
				xPos = 1.0f;
			else
				xPos = (HTfloat)m_Party_Factor[i].nCurTP/(HTfloat)m_Party_Factor[i].nMaxTP;
			if( xPos <= 0.0f || xPos > 1.0f )	xPos = 1.0f;
			g_cUIManager->HT_SetTextureControlScale( _DIALOG_PARTYWND, 20+i, (HTint)(xPos*150), 5 );
			if( m_Party_Factor[i].nCurTP == 0 )		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_FALSE );
			else									g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_TRUE );
			return;
		}
	}
}

//----------파티 탈퇴/해체----------//
HTvoid HTParty::HT_vNetWork_CSP_MSG_RemoveParty( HTint iTarget )
{
    MSG_RemoveParty* info = HT_NULL;
	info = new MSG_RemoveParty;
	if( iTarget == 0 )
		info->nTargetID = g_cMainCharacter->HT_iMainChar_GetKeyID();
	else if( iTarget == 1 )
		info->nTargetID = m_Party_Factor[m_party_DeleteMember].nID;
	else if( iTarget == 2 )
		info->nTargetID = MAX_USER;
	g_pNetWorkMgr-> RequestReqRemoveParty( info );

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MSG_RemoveParty : %d",  info->nTargetID );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
HTvoid HTParty::HT_vNetWork_SCP_MSG_RemoveParty( MSG_RemoveParty* info )
{
	CHTString	strTargetName;
	CHTString	strMyName;
	strMyName = g_oMainCharacterInfo.szCharName;
	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		if( info->nTargetID == m_Party_Factor[i].nID )
		{
            strTargetName = m_Party_Factor[i].Name;
			break;
		}
	}

	// 파티장 정보 갱신
	if( info->nLeaderID != m_dwParty_JangKeyID )
	{
		m_dwParty_JangKeyID = info->nLeaderID;
		if( info->nLeaderID == g_cMainCharacter->HT_iMainChar_GetKeyID() ) // 내가 파티장일 경우
		{
			m_Party_Jang				= HT_TRUE;
			m_strParty_JangName			= g_oMainCharacterInfo.szCharName;
		}
		else // 다른 사람이 파티장일 경우
		{
			for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
			{
				if( info->nLeaderID == m_Party_Factor[i].nID )
				{
					m_strParty_JangName = m_Party_Factor[i].Name;
					break;
				}
			}
		}

		//----------시스템 창에 메시지 뛰우기----------//
		CHTString strMessage;
		HT_vParty_SetMessage( eMsgPartyLeaderNotify, &strMessage ); // %s님이 파티장입니다.
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, strMessage );
	}

	if( strMyName.HT_iStringCompare( strTargetName ) == 0 || info->nTargetID == 0 )
	{
		m_bParty_Exist = HT_FALSE;
		//----------파티 해제----------//
		this->HT_vParty_DISBAND();
		// 파티에서 탈퇴되었습니다.
		CHTString szMessage;
		HT_vParty_SetMessage( eMsgPartySecessionOK, &szMessage );
		m_nParty_Receive_Process = PARTY_PROCESS_ERRORMESSAGE;
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, szMessage );

		//	파티창 지우기
		g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );
	}
	else
	{
		HT_vParty_DeleteMember( strTargetName );
		// %s이(가) 파티를 탈퇴하였습니다.
		m_szCharacterName = strTargetName;
		CHTString szMessage;
		HT_vParty_SetMessage( eMsgPartySecessionMemberOK, &szMessage );
		m_nParty_Receive_Process = PARTY_PROCESS_ERRORMESSAGE;
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, szMessage );
		
		// 자기 자신만 남았을 경우 파티창 내용 지우기
		if( m_Party_MemberCount == 0 ) 
		{
			this->HT_vParty_DISBAND();

			//	파티창 지우기
			g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );
		}
	}

	//	파티 멤버 보여주기
	this->HT_vParty_PartyMemberDiplay();
}

// 자동분배 모드
HTvoid HTParty::HT_vNetWork_CSP_Req_Set_Party( HTbool bRootingMode )
{
	MSG_SetParty* info = HT_NULL;
	info = new MSG_SetParty;

	info->byRootingMode = bRootingMode;
	g_pNetWorkMgr->RequestSetParty( info );

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Set_Party : %d",  info->byRootingMode );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid HTParty::HT_vNetWork_SCP_Resp_Set_Party( MSG_SetParty* info )
{
	if( info->byResult == 0x00 )
	{
		HT_bParty_SetRootingMode( (HTbool)info->byRootingMode );
	}
}

//----------파티 구성원 초기화----------//
HTvoid HTParty::HT_vParty_InitMember()
{
	for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	{
		m_Party_Factor[i].byLevel = 0xff;
	}
}

//----------새로운 멤버 추가하기----------//
HTvoid HTParty::HT_vParty_InsertMember( S_PARTY info )
{
	CHTString	strCompare;
	HTint		nIndex = 0;

	//	들어갈 순서를 찾아냄
	for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	{
		//	기존에 있던 캐릭터인지 조사
		strCompare = m_Party_Factor[i].Name;
		if( strCompare.HT_iStringCompare( info.Name ) == 0 )
			return;

		if( m_Party_Factor[i].byLevel == 0xff )
		{
			nIndex = i;
			break;
		}
	}

	//	파티멤버 참여를 OtherCharSystem에 넘김
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetPartyJoineDisband( info.Name, 0x02 );
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();

	memcpy( &m_Party_Factor[nIndex], &info, sizeof(S_PARTY) );
	++m_Party_MemberCount;
}

//----------기존 멤버 삭제하기----------//
HTvoid HTParty::HT_vParty_DeleteMember( CHTString strTemp )
{
	//	파티멤버 참여를 OtherCharSystem에 넘김
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetPartyJoineDisband( strTemp, 0x01 );
	CHTString	strCompare;
	HTvector3	vecTempPos;

	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		strCompare = m_Party_Factor[i].Name;
		if( strCompare.HT_iStringCompare( strTemp ) == 0 )
		{
			//	파티 탈퇴를 셋팅
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetPartyJoin( m_Party_Factor[i].Name, 0x01 );
			//	멤버 빼기
			--m_Party_MemberCount;
			
			// 그 다음 부분부터 위로 당긴다.
			for( HTint j=i ; j<m_Party_MemberCount ; j++ )
			{
				m_Party_Factor[j] = m_Party_Factor[j+1];
				memset( &m_Party_Factor[j+1], 0, sizeof(S_PARTY) );
				m_Party_Factor[j+1].byLevel = 0xff;
			}

			for( j=m_Party_MemberCount ; j<(PARTY_MAX_PERSON-1) ; j++ )
			{
				memset( &m_Party_Factor[j], 0, sizeof(S_PARTY) );
				m_Party_Factor[j].byLevel = 0xff;
			}
			break;
		}
	}
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();
}

//----------파티 해제----------//
HTvoid HTParty::HT_vParty_DISBAND()
{
	//---------내가 파티장이냐?---------//
	m_Party_Jang = HT_FALSE;
	m_dwParty_JangKeyID = 0;
	m_strParty_JangName.HT_hrCleanUp();
	m_bParty_Exist = HT_FALSE;
	m_Party_MemberCount = 0;

	// 자동분배 모드
	m_bParty_RootingMode = HT_FALSE;

	//---------파티원/주소록 항목---------//
	for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	{
		//	파티 탈퇴를 셋팅
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetPartyJoin( m_Party_Factor[i].Name, 0x01 );
		memset( &m_Party_Factor[i], 0, sizeof(S_PARTY) );
		m_Party_Factor[i].byLevel = 0xff;
	}
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();
}

//----------외부에서 파티 해체 및 탈퇴----------//
HTvoid HTParty::HT_vParty_OutSideRequest_LogOut()
{
	if( m_bParty_Exist == HT_FALSE )
		return;

	//---------내가 파티장이냐?---------//
	if( m_Party_Jang == HT_TRUE )
	{
		//----------파티 탈퇴(파티장 또는 파티원에 의해 수행됨)를 요청한다----------//
		this->HT_vNetWork_CSP_MSG_RemoveParty( 0x02 );
	}
	else
	{
		//----------파티 탈퇴(파티장 또는 파티원에 의해 수행됨)를 요청한다----------//
		this->HT_vNetWork_CSP_MSG_RemoveParty( 0x00 );
	}
}

//----------파티 멤버인지 판단----------//
HTbool HTParty::HT_bParty_IsPartyMember( CHTString strName )
{
	if( !m_bParty_Exist )
		return HT_FALSE;

	HTint nCompare;
	for( HTint i=0 ; i<m_Party_MemberCount ; i++ )
	{
		nCompare = strName.HT_iStringCompare( m_Party_Factor[i].Name );
		if( nCompare == 0 )
			return HT_TRUE;
	}

	return HT_FALSE;
}

HTbool HTParty::HT_bPArty_IsPartyMember( DWORD dwCharKeyID )
{
	if( !m_bParty_Exist )
		return HT_FALSE;

	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		if( m_Party_Factor[i].nID == dwCharKeyID )
			return HT_TRUE;
	}

	return HT_FALSE;
}

// 파티장인지 검사
HTbool HTParty::HT_bParty_IsPartyJang( DWORD dwCharKeyID )
{
	if( !m_bParty_Exist )
		return HT_FALSE;

	if( m_dwParty_JangKeyID == dwCharKeyID )
		return HT_TRUE;
	else
		return HT_FALSE;
}
// 파티원 이름 반환
CHTString HTParty::HT_szParty_GetPartyMemberName( HTdword dwCharKeyID )
{
	if( !m_bParty_Exist )
		return " ";

	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		if( m_Party_Factor[i].nID == dwCharKeyID )
			return m_Party_Factor[i].Name;
	}

	return " ";
}

//	파티원 아이디 반환
HTvoid HTParty::HT_vParty_GetPartyMemberKeyID( HTint* iMember, HTfloat fRange )
{
	HTfloat	fDis;
	HTvector3 vecPos;
	HTvector3 vecMainPos = g_cMainCharacter->HT_vecGetPosition();
	iMember[0] = g_cMainCharacter->HT_iMainChar_GetKeyID();
	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		//	거리를 구해내고
		vecPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( m_Party_Factor[i].nID );
		fDis = (float)sqrt( double( ( (vecMainPos.x - vecPos.x) * (vecMainPos.x - vecPos.x) ) + ( (vecMainPos.z - vecPos.z) * (vecMainPos.z - vecPos.z) ) ) );
		if( fDis < fRange )
		{
			iMember[i+1] = m_Party_Factor[i].nID;
		}
	}
}

// 자동분배 모드
HTvoid HTParty::HT_bParty_SetRootingMode( HTbool bMode )
{
	if( !m_bParty_Exist )
		return;

	m_bParty_RootingMode = bMode;

	CHTString szMessage;
	// 자동 분배 모드
	if( m_bParty_RootingMode == HT_TRUE )
	{
		HT_vParty_SetMessage( eMsgPartyAutoRootingMode, &szMessage );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_PARTYWND, 1, szMessage );
	}
	// 일반 분배 모드
	else
	{ 
		HT_vParty_SetMessage( eMsgPartyUsualRootingMode, &szMessage );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_PARTYWND, 1, szMessage );
	}
	if( szMessage.HT_bIsEmpty() == HT_FALSE )
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, szMessage );
}

//----------파티 멤버 보여주기----------//
HTvoid HTParty::HT_vParty_PartyMemberDiplay()
{
	CHTString strName;
	HTint i=0;

	//	기존 파티 컨트롤들을 전부 삭제하고
	for( i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	{
		//	Button
		g_cUIManager->HT_DelButtonControl( _DIALOG_PARTYWND, 10+i );
		//	Member Name
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_PARTYWND, 10+i, _T("") );
		//	Member HP
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_FALSE );
		//	Member TP
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_FALSE );
	}

	for( i=0 ; i < m_Party_MemberCount; ++i )
	{
		strName = m_Party_Factor[i].Name;
		if( m_strParty_JangName.HT_iStringCompare( strName ) == 0 )
		{
			CHTString szMessage;
			HT_vParty_SetMessage( eMsgCommonPartyMaster, &szMessage );
			strName += szMessage;
		}

		//	UI Set
		m_byUIControlSet[i] = 1;
		//	Button
		g_cUIManager->HT_AddButtonControl( _DIALOG_PARTYWND, 10+i, 0, 0, 20+(i*28), 9, 0, 1500, 150, 13 );
		//	이름 적어넣기
      	g_cUIManager->HT_SetTextLabelControl( _DIALOG_PARTYWND, 10+i, strName.HT_szGetString() );
		//	HP
		HTfloat xPos;
		if( m_Party_Factor[i].nCurHP==0 && m_Party_Factor[i].nMaxHP==0 )
			xPos = 1.0f;
		else
			xPos = (HTfloat)m_Party_Factor[i].nCurHP/(HTfloat)m_Party_Factor[i].nMaxHP;
		if( xPos <= 0.0f || xPos > 1.0f )	xPos = 1.0f;
		g_cUIManager->HT_SetTextureControlScale( _DIALOG_PARTYWND, 10+i, (HTint)(xPos*150), 5 );
		if( m_Party_Factor[i].nCurHP == 0 )		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_FALSE );
		else									g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_TRUE );
		//	TP
		if( m_Party_Factor[i].nCurTP==0 && m_Party_Factor[i].nMaxTP==0 )
			xPos = 1.0f;
		else
			xPos = (HTfloat)m_Party_Factor[i].nCurTP/(HTfloat)m_Party_Factor[i].nMaxTP;
		if( xPos <= 0.0f || xPos > 1.0f )	xPos = 1.0f;
		g_cUIManager->HT_SetTextureControlScale( _DIALOG_PARTYWND, 20+i, (HTint)(xPos*150), 5 );
		if( m_Party_Factor[i].nCurTP == 0 )		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_FALSE );
		else									g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_TRUE );
	}
	//	영역 재설정
	g_cUIManager->HT_SetMovingRegion( _DIALOG_PARTYWND, TRUE, 0,0, 190, 40+(m_Party_MemberCount*28) );
}

//--------------------------------------//
//			미니파티창					//
//--------------------------------------//
//	파티 미니창_스위치
HTvoid HTParty::HT_vParty_SetWnd()
{
	if (!m_bParty_Exist) return;
	m_bMiniParty_WndSw = HT_TRUE;

	//	파티창 지우기
	g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );

	//	파티 멤버 보여주기
	this->HT_vParty_PartyMemberDiplay();
    
}
HTvoid HTParty::HT_vParty_MiniPartyWndSetSw()
{
	if (!m_bParty_Exist) return;
	//	미니파티창 스위치
	if( m_bMiniParty_WndSw == HT_FALSE )
	{
		m_bMiniParty_WndSw = HT_TRUE;
		g_cUIManager->HT_ShowWindow( _DIALOG_PARTYWND );
		//	파티 멤버 보여주기
		this->HT_vParty_PartyMemberDiplay();

		// 자동 분배 모드
		this->HT_bParty_SetRootingMode( m_bParty_RootingMode );
	}
	else
	{
		m_bMiniParty_WndSw = HT_FALSE;
		g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );
	}
}

//	Command Check_Party
HTvoid HTParty::HT_bParty_Command_Party()
{
	//	만약 프로세스 진행중이었다면 파티프로세스 초기화
	if( m_nParty_Send_Process == PARTY_PROCESS_REQJOINPARTY ||
		m_nParty_Send_Process == PARTY_PROCESS_PARTYCREATE )
	{
        m_nParty_Send_Process = PARTY_PROCESS_ERRORMESSAGE;
		return;
	}

	if( m_bParty_Exist )
	{
		//	그냥 참여 요청
		m_nParty_Send_Process = PARTY_PROCESS_REQJOINPARTY;
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_PARTY_ANI);
	}
	else
	{
		//	파티 창설하면서 요청
		m_nParty_Send_Process = PARTY_PROCESS_PARTYCREATE;
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_PARTY_ANI);
	}
}
//	Command Check_PartyWithDraw
HTvoid HTParty::HT_bParty_Command_PartyWithDraw()
{
	this->HT_vParty_PartyLeave();
}

//----------파티 멤버들을 클릭했는가?----------//
HTbool HTParty::HT_bParty_MemberClick( HTint iBtnNo )
{
	HTbool bMemClick = HT_TRUE;
	m_nParty_Send_Process = PARTY_PROCESS_ERRORMESSAGE;
	m_party_DeleteMember = iBtnNo - 10;

	///	귓속말 상태로 만들어 주고..
	//CHTString strMyName = g_oMainCharacterInfo.szCharName;
	//if( strMyName.HT_iStringCompare( m_Party_Factor[m_party_DeleteMember].Name ) != 0 )
 //       g_cChatting->HT_vChatting_SetWisper( m_Party_Factor[m_party_DeleteMember].Name );

	if (!strcmp(m_Party_Factor[m_party_DeleteMember].Name, _T(""))) bMemClick = HT_FALSE;

	//	전체 정보칭 이닛 처리
	g_cOtherObjectSystem->HT_vOtherObjectSystem_HPWindowInit();
	//	픽처리
	m_szCharacterName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( m_Party_Factor[m_party_DeleteMember].nID );
	HTint iObjectID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( m_Party_Factor[m_party_DeleteMember].nID );
	g_cOtherObjectSystem->HT_iOtherObjectSystem_SRPickIDCheck( iObjectID );
	g_cMainCharacter->HT_vMainChar_SetAttackStatus( m_Party_Factor[m_party_DeleteMember].nID, iObjectID, HT_FALSE );
	bMemClick = HT_FALSE;
	return bMemClick;
}

HTvoid HTParty::HT_vParty_SetMessage( HTint idMessage, CHTString* pszMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	
	// 변수가 3개 일 때
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vParty_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vParty_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vParty_SetParamTextForMessage( sParam3, &szOut3 );

		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vParty_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vParty_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vParty_SetParamTextForMessage( sParam1, &szOut1 );
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pszMessage = szString;
}

HTvoid HTParty::HT_vParty_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// 다른 캐릭터 이름
		case eMsgParamOthercharName	:
			*pszParam = m_szCharacterName; break;
		// 파티장 이름
		case eMsgParamPartyLeaderName :
			*pszParam = m_strParty_JangName; break;

		default:
			break;
	}
}

